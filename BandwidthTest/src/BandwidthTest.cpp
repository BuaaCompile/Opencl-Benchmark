/**********************************************************************
Copyright (c) 2014,BUAA COMPILER LAB;
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
- Neither the name of the BUAA COMPILER LAB; nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
********************************************************************/
#include "BandwidthTest.hpp"
#include <string>


//Separator
std::string sep = "-----------------------------------------";

int
Bandwidth::setupCL(void)
{
    cl_int status = 0;
    cl_device_type dType;
    
    if(deviceType.compare("cpu") == 0)
    {
        dType = CL_DEVICE_TYPE_CPU;
    }
    else //deviceType = "gpu" 
    {
        dType = CL_DEVICE_TYPE_GPU;
        if(isThereGPU() == false)
        {
            std::cout << "GPU not found. Falling back to CPU device" << std::endl;
            dType = CL_DEVICE_TYPE_CPU;
        }
    }

    /*
     * Have a look at the available platforms and pick either
     * the AMD one if available or a reasonable default.
     */

    cl_platform_id platform = NULL;
    int retValue = sampleCommon->getPlatform(platform, platformId, isPlatformEnabled());
    CHECK_ERROR(retValue, SDK_SUCCESS, "sampleCommon::getPlatform() failed");

    // Display available devices.
    retValue = sampleCommon->displayDevices(platform, dType);
    CHECK_ERROR(retValue, SDK_SUCCESS, "sampleCommon::displayDevices() failed");

    /*
     * If we could find our platform, use it. Otherwise use just available platform.
     */

    cl_context_properties cps[3] = 
    {
        CL_CONTEXT_PLATFORM, 
        (cl_context_properties)platform, 
        0
    };

    context = clCreateContextFromType(cps,
                                      dType,
                                      NULL,
                                      NULL,
                                      &status);
    CHECK_OPENCL_ERROR(status, "clCreateContextFromType failed.");

    // getting device on which to run the sample
    status = sampleCommon->getDevices(context, &devices, deviceId, isDeviceIdEnabled());
    CHECK_ERROR(status, SDK_SUCCESS, "sampleCommon::getDevices() failed");

    //Set device info of given cl_device_id
    retValue = deviceInfo.setDeviceInfo(devices[deviceId]);
    CHECK_ERROR(retValue, SDK_SUCCESS, "SDKDeviceInfo::setDeviceInfo() failed");

    std::string deviceStr(deviceInfo.deviceVersion);
    size_t vStart = deviceStr.find(" ", 0);
    size_t vEnd = deviceStr.find(" ", vStart + 1);
    std::string vStrVal = deviceStr.substr(vStart + 1, vEnd - vStart - 1);

#ifdef CL_VERSION_1_1
    if(vStrVal.compare("1.0") >  0)
    {
        char openclVersion[1024];
        status = clGetDeviceInfo(devices[deviceId],
                                 CL_DEVICE_OPENCL_C_VERSION,
                                 sizeof(openclVersion),
                                 openclVersion,
                                 0);
        CHECK_OPENCL_ERROR(status, "clGetDeviceInfo failed.");
        
        std::string tempStr(deviceInfo.openclCVersion);
        size_t dotPos = tempStr.find_first_of(".");
        size_t spacePos = tempStr.find_last_of(" ");
        tempStr = tempStr.substr(dotPos + 1, spacePos - dotPos);
        int minorVersion = atoi(tempStr.c_str());
        // OpenCL 1.1 has inbuilt support for vec3 data types
        if(minorVersion < 1 && vec3 == true)
        {
            OPENCL_EXPECTED_ERROR("Device doesn't support built-in 3 component vectors!");
        }
    }
    else
    {
        // OpenCL 1.1 has inbuilt support for vec3 data types
        if(vec3 == true)
        {
            OPENCL_EXPECTED_ERROR("Device doesn't support built-in 3 component vectors!");
        }
    }
#else
    // OpenCL 1.1 has inbuilt support for vec3 data types
    if(vec3 == true)
    {
        OPENCL_EXPECTED_ERROR("Device doesn't support built-in 3 component vectors!");
    }
#endif

    return SDK_SUCCESS;
}

int
Bandwidth::bandwidth(cl_kernel &kernel)
{
    cl_int status;
    
    // Check group size against kernelWorkGroupSize 
    status = clGetKernelWorkGroupInfo(kernel,
                                      devices[deviceId],
                                      CL_KERNEL_WORK_GROUP_SIZE,
                                      sizeof(size_t),
                                      &kernelWorkGroupSize,
                                      0);
    CHECK_OPENCL_ERROR(status, "clGetKernelWorkGroupInfo failed.");

    if(localThreads > kernelWorkGroupSize)
        localThreads = kernelWorkGroupSize;

    // Set appropriate arguments to the kernel 
    int argIndex = 0;

    if(dynamiArgFlag)
    {
        cl_uint index = 0;
        status = clSetKernelArg(kernel,
                                argIndex++,
                                sizeof(cl_uint), 
                                (void *)&index);
        CHECK_OPENCL_ERROR(status, "clSetKernelArg failed.(index)");
    }
    
    status = clSetKernelArg(kernel,
                            argIndex++,
                            sizeof(cl_mem), 
                            (void *)&constantBuffer);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg failed.(constantBuffer)");

    status = clSetKernelArg(kernel,
                            argIndex++,
                            sizeof(cl_mem), 
                            (void *)&outputBuffer);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg failed.(outputBuffer)");

    if(randomArgFlag)
    {
         status = clSetKernelArg(kernel,
                                 argIndex++,
                                 sizeof(cl_mem), 
                                 (void *)&randomIndicesBuffer);
        CHECK_OPENCL_ERROR(status, "clSetKernelArg failed.(randomIndicesBuffer)");
    }

    double sec = 0;
    int iter = iterations;
    if(verify)
        iter = 1;


    // Run the kernel for a number of iterations
    for(int i = 0; i < iter; i++)
    {
        //Enqueue a kernel run call
        cl_event ndrEvt;
        status = clEnqueueNDRangeKernel(commandQueue,
                                        kernel,
                                        1,
                                        NULL,
                                        &globalThreads,
                                        &localThreads,
                                        0,
                                        NULL,
                                        &ndrEvt);
        CHECK_OPENCL_ERROR(status, "clEnqueueNDRangeKernel failed.");

        // wait for the kernel call to finish execution
        status = clWaitForEvents(1, &ndrEvt);
        CHECK_OPENCL_ERROR(status, "clWaitForEvents failed.");

        // Calculate performance
        cl_ulong startTime;
        cl_ulong endTime;
        
        // Get kernel profiling info 
        status = clGetEventProfilingInfo(ndrEvt,
                                         CL_PROFILING_COMMAND_START,
                                         sizeof(cl_ulong),
                                         &startTime,
                                         0);
        CHECK_OPENCL_ERROR(status, "clGetEventProfilingInfo failed.(startTime)");

        status = clGetEventProfilingInfo(ndrEvt,
                                         CL_PROFILING_COMMAND_END,
                                         sizeof(cl_ulong),
                                         &endTime,
                                         0);
        CHECK_OPENCL_ERROR(status, "clGetEventProfilingInfo failed.(endTime)");

        // Cumulate time for each iteration
        sec += 1e-9 * (endTime - startTime);

        status = clReleaseEvent(ndrEvt);
        CHECK_OPENCL_ERROR(status, "clRelease Event Failed");
    }

    // Copy bytes
    int bytesPerThread = 0;
    if(vec3 == true)
        bytesPerThread = NUM_READS * 3 * sizeof(cl_float);
    else
        bytesPerThread = NUM_READS * vectorSize * sizeof(cl_float);
    double bytes = (double)(iter * bytesPerThread);
    double perf = (bytes / sec) * 1e-9;
    perf *= globalThreads;

    std::cout << ": " << perf << " GB/s" << std::endl;

    // Enqueue readBuffer
    status = clEnqueueReadBuffer(commandQueue,
                                 outputBuffer,
                                 CL_TRUE,
                                 0,
                                 length * sizeof(cl_float) * vectorSize,
                                 output,
                                 0,
                                 NULL,
                                 0);
    CHECK_OPENCL_ERROR(status, "clEnqueueReadBuffer failed.");

    return SDK_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
//  Create command queue for the selected device
///////////////////////////////////////////////////////////////////////////////
int 
Bandwidth::createQueue(unsigned int device)
{
	cl_int status = 0;
	// Release if there previous is already one
	if(commandQueue) 
	{
		clReleaseCommandQueue(commandQueue);
	}

	cl_command_queue_properties prop = 0;
	prop |= CL_QUEUE_PROFILING_ENABLE;
	 
	commandQueue = clCreateCommandQueue(context, 
                                         devices[device], 
                                         prop, 
                                         &status);
	CHECK_OPENCL_ERROR(status, "clCreateCommandQueue failed.");
	return SDK_SUCCESS;
}


///////////////////////////////////////////////////////////////////////////////
//  Run a bandwidth test
///////////////////////////////////////////////////////////////////////////////
void
Bandwidth::testBandwidth(memcpyKind kind)
{
	switch(mode)
	{
	case QUICK_MODE:
		testBandwidthQuick( DEFAULT_SIZE, kind);
		break;
	case RANGE_MODE:
		testBandwidthRange(start, end, increment, kind);
		break;
	case SHMOO_MODE: 
		testBandwidthShmoo(kind);
		break;
	default:  
		break;
	}

}
//////////////////////////////////////////////////////////////////////
//  Run a quick mode bandwidth test
//////////////////////////////////////////////////////////////////////
void
Bandwidth::testBandwidthQuick(unsigned int size, memcpyKind kind)
{
	testBandwidthRange(size, size, DEFAULT_INCREMENT, kind);
}

///////////////////////////////////////////////////////////////////////
//  Run a range mode bandwidth test
//////////////////////////////////////////////////////////////////////
void
Bandwidth::testBandwidthRange(unsigned int start, unsigned int end, unsigned int increment, memcpyKind kind)
{
	//count the number of copies we're going to run
	unsigned int count = 1 + ((end - start) / increment);

	unsigned int * memSizes = (unsigned int *)malloc(count * sizeof( unsigned int ));
	double* bandwidths = (double*)malloc(count * sizeof(double));

	// Before calculating the cumulative bandwidth, initialize bandwidths array to NULL
	for (unsigned int i = 0; i < count; i++)
		bandwidths[i] = 0.0;

	// Use the device asked by the user
	for (int currentDevice = startDevice; currentDevice <= endDevice; currentDevice++)
	{
		// Allocate command queue for the device (dealloc first if already allocated)
		createQueue(currentDevice);

		//run each of the copies
		for(unsigned int i = 0; i < count; i++)
		{
			memSizes[i] = start + i * increment;
			switch(kind)
			{
			case DEVICE_TO_HOST:    bandwidths[i] += testDeviceToHostTransfer(memSizes[i]);
				break;
			case HOST_TO_DEVICE:    bandwidths[i] += testHostToDeviceTransfer(memSizes[i]);
				break;
			case DEVICE_TO_DEVICE:  bandwidths[i] += testDeviceToDeviceTransfer(memSizes[i]);
				break;
			}
		}
	} // Complete the bandwidth computation on all the devices

	//print results

	printResultsReadable(memSizes, bandwidths, count, kind, (1 + endDevice - startDevice));

	//clean up
	free(memSizes);
	free(bandwidths);
}
/////////////////////////////////////////////////////////
//print results in an easily read format
////////////////////////////////////////////////////////
void Bandwidth::printResultsReadable(unsigned int *memSizes, double* bandwidths, unsigned int count, memcpyKind kind, int iNumDevs)
{
	// log config information 
	if (kind == DEVICE_TO_DEVICE)
	{
		printf("Device to Device Bandwidth, %i Device(s)\n", iNumDevs);
	}
	else 
	{
		if (kind == DEVICE_TO_HOST)
		{
			printf("Device to Host Bandwidth, %i Device(s), ", iNumDevs);
		}
		else if (kind == HOST_TO_DEVICE)
		{
			printf("Host to Device Bandwidth, %i Device(s), ", iNumDevs);
		}
		if(memoryMode.compare("pageable") == 0)
		{
			printf("Paged memory");
		}
		else if (memoryMode.compare("pinned") == 0)
		{
			printf("Pinned memory");
		}
		if(accessMode.compare("direct") == 0)
		{
			printf(", direct access\n");
		}
		else if (accessMode.compare("mapped") == 0)
		{
			printf(", mapped access\n");
		}
	}

	printf("   Transfer Size (Bytes)\tBandwidth(MB/s)\n");
	unsigned int i; 
	for(i = 0; i < (count - 1); i++)
	{
		printf("   %u\t\t\t%s%.1f\n", memSizes[i], (memSizes[i] < 10000)? "\t" : "", bandwidths[i]);
	}
	printf("   %u\t\t\t%s%.1f\n\n", memSizes[i], (memSizes[i] < 10000)? "\t" : "", bandwidths[i]);
}


//////////////////////////////////////////////////////////////////////////////
// Intense shmoo mode - covers a large range of values with varying increments
//////////////////////////////////////////////////////////////////////////////
void Bandwidth::testBandwidthShmoo(memcpyKind kind)
{
	//count the number of copies to make
	unsigned int count = 1 + (SHMOO_LIMIT_20KB  / SHMOO_INCREMENT_1KB)
		+ ((SHMOO_LIMIT_50KB - SHMOO_LIMIT_20KB) / SHMOO_INCREMENT_2KB)
		+ ((SHMOO_LIMIT_100KB - SHMOO_LIMIT_50KB) / SHMOO_INCREMENT_10KB)
		+ ((SHMOO_LIMIT_1MB - SHMOO_LIMIT_100KB) / SHMOO_INCREMENT_100KB)
		+ ((SHMOO_LIMIT_16MB - SHMOO_LIMIT_1MB) / SHMOO_INCREMENT_1MB)
		+ ((SHMOO_LIMIT_32MB - SHMOO_LIMIT_16MB) / SHMOO_INCREMENT_2MB)
		+ ((SHMOO_MEMSIZE_MAX - SHMOO_LIMIT_32MB) / SHMOO_INCREMENT_4MB);

	unsigned int *memSizes = (unsigned int *)malloc(count * sizeof(unsigned int));
	double* bandwidths = (double*)malloc(count * sizeof(double));

	// Before calculating the cumulative bandwidth, initialize bandwidths array to NULL
	for (unsigned int i = 0; i < count; i++)
		bandwidths[i] = 0.0;

	// Use the device asked by the user
	for (int currentDevice = startDevice; currentDevice <= endDevice; currentDevice++)
	{
		// Allocate command queue for the device (dealloc first if already allocated)
		createQueue(currentDevice);

		//Run the shmoo
		int iteration = 0;
		unsigned int memSize = 0;
		while(memSize <= SHMOO_MEMSIZE_MAX )
		{
			if(memSize < SHMOO_LIMIT_20KB )
			{
				memSize += SHMOO_INCREMENT_1KB;
			}
			else if( memSize < SHMOO_LIMIT_50KB)
			{
				memSize += SHMOO_INCREMENT_2KB;
			}
			else if( memSize < SHMOO_LIMIT_100KB)
			{
				memSize += SHMOO_INCREMENT_10KB;
			}
			else if( memSize < SHMOO_LIMIT_1MB)
			{
				memSize += SHMOO_INCREMENT_100KB;
			}
			else if( memSize < SHMOO_LIMIT_16MB)
			{
				memSize += SHMOO_INCREMENT_1MB;
			}
			else if( memSize < SHMOO_LIMIT_32MB)
			{
				memSize += SHMOO_INCREMENT_2MB;
			}
			else 
			{
				memSize += SHMOO_INCREMENT_4MB;
			}

			memSizes[iteration] = memSize;
			switch(kind)
			{
			case DEVICE_TO_HOST:    bandwidths[iteration] += testDeviceToHostTransfer(memSizes[iteration]);
				break;
			case HOST_TO_DEVICE:    bandwidths[iteration] += testHostToDeviceTransfer(memSizes[iteration]);
				break;
			case DEVICE_TO_DEVICE:  bandwidths[iteration] += testDeviceToDeviceTransfer(memSizes[iteration]);
				break;
			}
			iteration++;
			printf(".");
		}
	} // Complete the bandwidth computation on all the devices

	//print results
	printf("\n");
	printResultsReadable(memSizes, bandwidths, count, kind, (endDevice - startDevice));

	//clean up
	free(memSizes);
	free(bandwidths);
}

///////////////////////////////////////////////////////////////////////////////
//  test the bandwidth of a device to host memcopy of a specific size
///////////////////////////////////////////////////////////////////////////////
double Bandwidth::testDeviceToHostTransfer(unsigned int memSize)
{
	double elapsedTimeInSec = 0.0;
	double bandwidthInMBs = 0.0;
	unsigned char *h_data = NULL;
	cl_mem cmPinnedData = NULL;
	cl_mem cmDevData = NULL;
	cl_int status = 0;

	//allocate and init host memory, pinned or conventional
	if(memoryMode.compare("pinned") == 0)
	{
		// Create a host buffer
		cmPinnedData = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR, memSize, NULL, &status);
		CHECK_OPENCL_ERROR(status, "clCreateBuffer failed.");

		// Get a mapped pointer
		h_data = (unsigned char*)clEnqueueMapBuffer(commandQueue, cmPinnedData, CL_TRUE, CL_MAP_WRITE, 0, memSize, 0, NULL, NULL, &status);
		CHECK_OPENCL_ERROR(status, "clEnqueueMapBuffer failed.");

		//initialize 
		for(unsigned int i = 0; i < memSize/sizeof(unsigned char); i++)
		{
			h_data[i] = (unsigned char)(i & 0xff);
		}

		// unmap and make data in the host buffer valid
		status = clEnqueueUnmapMemObject(commandQueue, cmPinnedData, (void*)h_data, 0, NULL, NULL);
		CHECK_OPENCL_ERROR(status, "clEnqueueUnmapMemObject failed.");
	}
	else 
	{
		// standard host alloc
		h_data = (unsigned char *)malloc(memSize);

		//initialize 
		for(unsigned int i = 0; i < memSize/sizeof(unsigned char); i++)
		{
			h_data[i] = (unsigned char)(i & 0xff);
		}
	}

	// allocate device memory 
	cmDevData = clCreateBuffer(context, CL_MEM_READ_WRITE, memSize, NULL, &status);
	CHECK_OPENCL_ERROR(status, "clCreateBuffer failed.");

	// initialize device memory 
	if(memoryMode.compare("pinned") == 0)
	{
		// Get a mapped pointer
		h_data = (unsigned char*)clEnqueueMapBuffer(commandQueue, cmPinnedData, CL_TRUE, CL_MAP_WRITE, 0, memSize, 0, NULL, NULL, &status);	        

		status = clEnqueueWriteBuffer(commandQueue, cmDevData, CL_FALSE, 0, memSize, h_data, 0, NULL, NULL);
		CHECK_OPENCL_ERROR(status, "clEnqueueWriteBuffer failed.");
	}
	else
	{
		status = clEnqueueWriteBuffer(commandQueue, cmDevData, CL_FALSE, 0, memSize, h_data, 0, NULL, NULL);
		CHECK_OPENCL_ERROR(status, "clEnqueueWriteBuffer failed.");
	}

	// Sync queue to host, start timer 0, and copy data from GPU to Host
	status = clFinish(commandQueue);
	CHECK_OPENCL_ERROR(status, "clFinish failed.");

	int timer = sampleCommon->createTimer();
	sampleCommon->resetTimer(timer);
	sampleCommon->startTimer(timer);

	if(accessMode.compare("direct") == 0)
	{ 
		// DIRECT:  API access to device buffer 
		for(unsigned int i = 0; i < MEMCOPY_ITERATIONS; i++)
		{
			status = clEnqueueReadBuffer(commandQueue, cmDevData, CL_FALSE, 0, memSize, h_data, 0, NULL, NULL);
			CHECK_OPENCL_ERROR(status, "clEnqueueReadBuffer failed.");
		}
		status = clFinish(commandQueue);
		CHECK_OPENCL_ERROR(status, "clFinish failed.");
	} 
	else 
	{
		// MAPPED: mapped pointers to device buffer for conventional pointer access
		void* dm_idata = clEnqueueMapBuffer(commandQueue, cmDevData, CL_TRUE, CL_MAP_WRITE, 0, memSize, 0, NULL, NULL, &status);
		CHECK_OPENCL_ERROR(status, "clEnqueueMapBuffer failed.");
		for(unsigned int i = 0; i < MEMCOPY_ITERATIONS; i++)
		{
			memcpy(h_data, dm_idata, memSize);
		}
		status = clEnqueueUnmapMemObject(commandQueue, cmDevData, dm_idata, 0, NULL, NULL);
		CHECK_OPENCL_ERROR(status, "clEnqueueUnmapMemObject failed.");
	}

	//get the the elapsed time in seconds
	sampleCommon->stopTimer(timer);
	elapsedTimeInSec = (cl_double)sampleCommon->readTimer(timer);

	//calculate bandwidth in MB/s
	bandwidthInMBs = ((double)memSize * (double)MEMCOPY_ITERATIONS) / (elapsedTimeInSec * (double)(1 << 20));

	//clean up memory
	if(cmDevData)clReleaseMemObject(cmDevData);
	if(cmPinnedData) 
	{
		clEnqueueUnmapMemObject(commandQueue, cmPinnedData, (void*)h_data, 0, NULL, NULL);	
		clReleaseMemObject(cmPinnedData);	
	}
	h_data = NULL;

	return bandwidthInMBs;
}
///////////////////////////////////////////////////////////////////////////////
//  test the bandwidth of a device to host memcopy of a specific size
///////////////////////////////////////////////////////////////////////////////
double Bandwidth::testHostToDeviceTransfer(unsigned int memSize)
{
	double elapsedTimeInSec = 0.0;
	double bandwidthInMBs = 0.0;
	unsigned char* h_data = NULL;
	cl_mem cmPinnedData = NULL;
	cl_mem cmDevData = NULL;
	cl_int status = CL_SUCCESS;

	// Allocate and init host memory, pinned or conventional
	if(memoryMode.compare("pinned") == 0)
	{
		// Create a host buffer
		cmPinnedData = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR, memSize, NULL, &status);
		CHECK_OPENCL_ERROR(status, "something failed.");

		// Get a mapped pointer
		h_data = (unsigned char*)clEnqueueMapBuffer(commandQueue, cmPinnedData, CL_TRUE, CL_MAP_WRITE, 0, memSize, 0, NULL, NULL, &status);
		CHECK_OPENCL_ERROR(status, "something failed.");

		//initialize 
		for(unsigned int i = 0; i < memSize/sizeof(unsigned char); i++)
		{
			h_data[i] = (unsigned char)(i & 0xff);
		}

		// unmap and make data in the host buffer valid
		status = clEnqueueUnmapMemObject(commandQueue, cmPinnedData, (void*)h_data, 0, NULL, NULL);
		CHECK_OPENCL_ERROR(status, "something failed.");
	}
	else 
	{
		// standard host alloc
		h_data = (unsigned char *)malloc(memSize);

		//initialize 
		for(unsigned int i = 0; i < memSize/sizeof(unsigned char); i++)
		{
			h_data[i] = (unsigned char)(i & 0xff);
		}
	}

	// allocate device memory 
	cmDevData = clCreateBuffer(context, CL_MEM_READ_WRITE, memSize, NULL, &status);
	CHECK_OPENCL_ERROR(status, "something failed.");

	// Sync queue to host, start timer 0, and copy data from Host to GPU
	clFinish(commandQueue);
	int timer = sampleCommon->createTimer();
	sampleCommon->resetTimer(timer);
	sampleCommon->startTimer(timer);
	if(accessMode.compare("direct") == 0)
	{ 
		if(memoryMode.compare("pinned") == 0) 
		{
			// Get a mapped pointer
			h_data = (unsigned char*)clEnqueueMapBuffer(commandQueue, cmPinnedData, CL_TRUE, CL_MAP_WRITE, 0, memSize, 0, NULL, NULL, &status);
			CHECK_OPENCL_ERROR(status, "something failed.");
		}

		// DIRECT:  API access to device buffer 
		for(unsigned int i = 0; i < MEMCOPY_ITERATIONS; i++)
		{
			status = clEnqueueWriteBuffer(commandQueue, cmDevData, CL_FALSE, 0, memSize, h_data, 0, NULL, NULL);
			CHECK_OPENCL_ERROR(status, "something failed.");
		}
		status = clFinish(commandQueue);
		CHECK_OPENCL_ERROR(status, "something failed.");
	} 
	else 
	{
		// MAPPED: mapped pointers to device buffer and conventional pointer access
		void* dm_idata = clEnqueueMapBuffer(commandQueue, cmDevData, CL_TRUE, CL_MAP_READ, 0, memSize, 0, NULL, NULL, &status);
		for(unsigned int i = 0; i < MEMCOPY_ITERATIONS; i++)
		{
			memcpy(dm_idata, h_data, memSize);
		}
		status = clEnqueueUnmapMemObject(commandQueue, cmDevData, dm_idata, 0, NULL, NULL);
		CHECK_OPENCL_ERROR(status, "something failed.");
	}

	//get the the elapsed time in seconds
	sampleCommon->stopTimer(timer);
	elapsedTimeInSec = (cl_double)sampleCommon->readTimer(timer);


	//calculate bandwidth in MB/s
	bandwidthInMBs = ((double)memSize * (double)MEMCOPY_ITERATIONS)/(elapsedTimeInSec * (double)(1 << 20));

	//clean up memory
	if(cmDevData)clReleaseMemObject(cmDevData);
	if(cmPinnedData) 
	{
		clEnqueueUnmapMemObject(commandQueue, cmPinnedData, (void*)h_data, 0, NULL, NULL);
		clReleaseMemObject(cmPinnedData);
	}
	h_data = NULL;

	return bandwidthInMBs;
}
///////////////////////////////////////////////////////////////////////////////
//  test the bandwidth of a device to host memcopy of a specific size
///////////////////////////////////////////////////////////////////////////////
double Bandwidth::testDeviceToDeviceTransfer(unsigned int memSize)
{
	double elapsedTimeInSec = 0.0;
	double bandwidthInMBs = 0.0;
	unsigned char* h_idata = NULL;
	cl_int status = CL_SUCCESS;

	//allocate host memory
	h_idata = (unsigned char *)malloc( memSize );

	//initialize the memory
	for(unsigned int i = 0; i < memSize/sizeof(unsigned char); i++)
	{
		h_idata[i] = (unsigned char) (i & 0xff);
	}

	// allocate device input and output memory and initialize the device input memory
	cl_mem d_idata = clCreateBuffer(context, CL_MEM_READ_ONLY, memSize, NULL, &status);
	CHECK_OPENCL_ERROR(status, "something failed.");
	cl_mem d_odata = clCreateBuffer(context, CL_MEM_WRITE_ONLY, memSize, NULL, &status);         
	CHECK_OPENCL_ERROR(status, "something failed.");
	status = clEnqueueWriteBuffer(commandQueue, d_idata, CL_TRUE, 0, memSize, h_idata, 0, NULL, NULL);
	CHECK_OPENCL_ERROR(status, "something failed.");

	// Sync queue to host, start timer 0, and copy data from one GPU buffer to another GPU bufffer
	clFinish(commandQueue);
	int timer = sampleCommon->createTimer();
	sampleCommon->resetTimer(timer);
	sampleCommon->startTimer(timer);

	for(unsigned int i = 0; i < MEMCOPY_ITERATIONS; i++)
	{
		status = clEnqueueCopyBuffer(commandQueue, d_idata, d_odata, 0, 0, memSize, 0, NULL, NULL);                
		CHECK_OPENCL_ERROR(status, "something failed.");
	}    

	// Sync with GPU
	clFinish(commandQueue);

	//get the the elapsed time in seconds
	sampleCommon->stopTimer(timer);
	elapsedTimeInSec = (cl_double)sampleCommon->readTimer(timer);

	// Calculate bandwidth in MB/s 
	//      This is for kernels that read and write GMEM simultaneously 
	//      Obtained Throughput for unidirectional block copies will be 1/2 of this #
	bandwidthInMBs = 2.0 * ((double)memSize * (double)MEMCOPY_ITERATIONS)/(elapsedTimeInSec * (double)(1 << 20));

	//clean up memory on host and device
	free(h_idata);
	clReleaseMemObject(d_idata);
	clReleaseMemObject(d_odata);

	return bandwidthInMBs;
}

int 
Bandwidth::runCLKernels(void)
{
    int status;

    if(vec3 == true)
        std::cout << "\nAccessType\t: single(static index)\nVectorElements\t: 3" << std::endl;
    else
        std::cout << "\nAccessType\t: single(static index)\nVectorElements\t: " << vectorSize << std::endl;

    std::cout << "Bandwidth\t";

    // Measure bandwidth of single reads(static index) from constant buffer 
    status = bandwidth(kernel[0]);
    if(status != SDK_SUCCESS)
        return SDK_FAILURE;

    if(verify)
    {
        int size = length * vectorSize * sizeof(cl_float);
        // Verify result for single access 
        memset(verificationOutput, 0, size);

        int index = 0;
        for(int i = 0; i < (int)length; i++)
        {
            for(int j = 0; j < NUM_READS; j++)
            {
                for(int k = 0; k < vectorSize; k++)
                    verificationOutput[i * vectorSize + k] += input[(index + j) * vectorSize + k];
            }
        }

        if(!memcmp(output, verificationOutput, size))
        {
            std::cout << "Passed!\n" << std::endl;
        }
        else
        {
            std::cout << "Failed!\n" << std::endl;
            return SDK_FAILURE;
        }
    }

    if(vec3 == true)
        std::cout << "\nAccessType\t: single(dynamic index)\nVectorElements\t: 3" << std::endl;
    else
        std::cout << "\nAccessType\t: single(dynamic index)\nVectorElements\t: " << vectorSize << std::endl;

    std::cout << "Bandwidth\t";
    dynamiArgFlag = true;

    // Measure bandwidth of single(dynamic index) reads from constant buffer 
    status = bandwidth(kernel[1]);
    if(status != SDK_SUCCESS)
        return SDK_FAILURE;

    if(verify)
    {
        int size = length * vectorSize * sizeof(cl_float);
        // Verify result for single access 
        if(!memcmp(output, verificationOutput, size))
        {
            std::cout << "Passed!\n" << std::endl;
        }
        else
        {
            std::cout << "Failed!\n" << std::endl;
            return SDK_FAILURE;
        }
    }

    if(vec3 == true)
        std::cout << "\nAccessType\t: linear\nVectorElements\t: 3" << std::endl;
    else
        std::cout << "\nAccessType\t: linear\nVectorElements\t: " << vectorSize << std::endl;

    std::cout << "Bandwidth\t";

    dynamiArgFlag = false;
    // Measure bandwidth of linear reads from constant buffer
    status = bandwidth(kernel[2]);
    if(status != SDK_SUCCESS)
        return SDK_FAILURE;

    if(verify)
    {
        int size = length * vectorSize * sizeof(cl_float);
        memset(verificationOutput, 0, size);
        // Verify result for Linear access
        for(int i = 0; i < (int)length; i++)
        {
            int index = i % 64;
            for(int j = 0; j < NUM_READS; j++)
            {
                for(int k = 0; k < vectorSize; k++)
                {
                    verificationOutput[i * vectorSize + k] += input[(index + j) * vectorSize + k];
                }
            }
        }

        if(!memcmp(output, verificationOutput, size))
        {
            std::cout << "Passed!\n" << std::endl;
        }
        else
        {
            std::cout << "Failed!\n" << std::endl;
            return SDK_FAILURE;
        }
    }

    std::cout << "\nAccessType\t: random\nVectorElements\t: " << vectorSize << std::endl;
    std::cout << "Bandwidth\t";

    randomArgFlag = true;
    // Measure bandwidth of linear reads from constant buffer 
    status = bandwidth(kernel[3]);
    if(status != SDK_SUCCESS)
        return SDK_FAILURE;

    if(verify)
    {
        int size = length * vectorSize * sizeof(cl_float);
        memset(verificationOutput, 0, size);

        // Verify result for Random access 
        for(int i = 0; i < (int)length; i++)
        {
            int index = i % GROUP_SIZE;
            for(int j = 0; j < NUM_READS; j++)
            {
                int temp = randomIndices[index + j];
                for(int k = 0; k < vectorSize; k++)
                {
                    verificationOutput[i * vectorSize + k] += input[temp * vectorSize + k];
                }
            }
        }

        if(!memcmp(output, verificationOutput, size))
        {
            std::cout << "Passed!\n" << std::endl;
            return SDK_SUCCESS;
        }
        else
        {
            std::cout << "Failed!\n" << std::endl;
            return SDK_FAILURE;
        }
    }
    return SDK_SUCCESS;
}


int 
Bandwidth::initialize()
{
    // Call base class Initialize to get default configuration
    if(this->Benchmark::initialize() != SDK_SUCCESS)
        return SDK_FAILURE;

    streamsdk::Option* mode_access = new streamsdk::Option;
    CHECK_ALLOCATION(mode_access, "Memory Allocation failed (mode_access)");

    mode_access->_sVersion = "";
    mode_access->_lVersion = "access";
    mode_access->_description = "Specify which memory access mode to use";
	mode_access->_type = streamsdk::CA_ARG_STRING;
    mode_access->_value = &accessMode;

    sampleArgs->AddOption(mode_access);
    delete mode_access;

    streamsdk::Option* mode_memory = new streamsdk::Option;
    CHECK_ALLOCATION(mode_memory, "Memory Allocation failed (mode_memory)");

    mode_memory->_sVersion = "";
    mode_memory->_lVersion = "memory";
    mode_memory->_description = "Specify which memory mode to use";
    mode_memory->_type = streamsdk::CA_ARG_STRING;
    mode_memory->_value = &memoryMode;

    sampleArgs->AddOption(mode_memory);
    delete mode_memory;

	streamsdk::Option* mode_test = new streamsdk::Option;
    CHECK_ALLOCATION(mode_test, "Memory Allocation failed (mode_test)");

    mode_test->_sVersion = "";
    mode_test->_lVersion = "mode";
    mode_test->_description = "Specify the mode to use";
    mode_test->_type = streamsdk::CA_ARG_STRING;
    mode_test->_value = &testMode;

    sampleArgs->AddOption(mode_test);
    delete mode_test;

	streamsdk::Option* htodOption = new streamsdk::Option;
	CHECK_ALLOCATION(htodOption, "Memory Allocation failed (mode_test)");

	htodOption->_sVersion = "";
	htodOption->_lVersion = "htod";
	htodOption->_description = "Measure host to device transfers";
	htodOption->_type = streamsdk::CA_NO_ARGUMENT;
	htodOption->_value = &testMode;

	sampleArgs->AddOption(htodOption);
	delete htodOption;

	streamsdk::Option* dtodOption = new streamsdk::Option;
	CHECK_ALLOCATION(dtodOption, "Memory Allocation failed (mode_test)");

	dtodOption->_sVersion = "";
	dtodOption->_lVersion = "dtod";
	dtodOption->_description = "Measure device to host transfers";
	dtodOption->_type = streamsdk::CA_NO_ARGUMENT;
	dtodOption->_value = &testMode;

	sampleArgs->AddOption(dtodOption);
	delete dtodOption;

	streamsdk::Option* dtohOption = new streamsdk::Option;
	CHECK_ALLOCATION(dtohOption, "Memory Allocation failed (mode_test)");

	dtohOption->_sVersion = "";
	dtohOption->_lVersion = "dtoh";
	dtohOption->_description = "Measure device to device transfers";
	dtohOption->_type = streamsdk::CA_NO_ARGUMENT;
	dtohOption->_value = &testMode;

	sampleArgs->AddOption(dtohOption);
	delete dtohOption;

    return SDK_SUCCESS;
}

int Bandwidth::parseCommandLine(int argc, char **argv)
{
	// Call base class Initialize to get default configuration
	if(this->Benchmark::parseCommandLine(argc, argv) != SDK_SUCCESS)
		return SDK_FAILURE;

	if(!((memoryMode.compare("pageable") == 0 ) || (memoryMode.compare("pinned") ==0)))
	{
		std::cout << "Invalid memory mode - valid modes are pageable or pinned.\n\n";
		usage();
		return SDK_FAILURE;
	}
	if(!((accessMode.compare("direct") == 0 ) || (accessMode.compare("mapped") ==0)))
	{
		std::cout << "Invalid access mode - valid modes are direct or mapped.\n\n";
		usage();
		return SDK_FAILURE;
	}
	int index = testMode.find_first_of('#');
	if (index == std::string::npos)
	{
		index = testMode.length();
	}
	std::string tmp = testMode.substr(0,index);
	if(!((tmp.compare("quick") == 0 ) || (tmp.compare("shmoo") ==0) || (tmp.compare("range") ==0)))
	{
		std::cout << "Invalid mode - valid modes are quick or shmoo or range.\n\n";
		usage();
		return SDK_FAILURE;
	}
	else if(tmp.compare("quick") == 0)
	{
		mode = QUICK_MODE;
	}
	else if(tmp.compare("shmoo") == 0)
	{
		mode = SHMOO_MODE;
	}
	else if(tmp.compare("range") == 0)
	{
		mode = RANGE_MODE;
		int index1 = testMode.find_first_of('#',index);
		start = atoi(testMode.substr(index,index1).c_str());
		int index2 = testMode.find_first_of('#',index1);
		end = atoi(testMode.substr(index1,index2).c_str());
		increment = atoi(testMode.substr(index2,testMode.length()).c_str());
		if( start <= 0 )
		{
			std::cout << "Illegal argument\nplease set a start must be greater than zero\n";
			return SDK_FAILURE;
		}
		if(end <= 0)
		{
			std::cout << "Illegal argument\nplease set a end must be greater than zero\n";
			return SDK_FAILURE;
		}
		if(start > end)
		{
			std::cout << "Illegal argument\n start is greater than end\n";
			return SDK_FAILURE;
		}

		if(increment <= 0)
		{
			std::cout << "Illegal argument\nplease set an increment must be greater than zero\n";
			return SDK_FAILURE;
		}
	}


	if(sampleArgs->isArgSet("htod",false))
		htod = true;
	if(sampleArgs->isArgSet("dtoh",false))
		dtoh = true;
	if(sampleArgs->isArgSet("dtod",false))
		dtod = true;

	if(!sampleArgs->isArgSet("htod",false) && !sampleArgs->isArgSet("dtoh",false) && !sampleArgs->isArgSet("dtod",false))
	{
		htod = true;
		dtoh = true;
		dtod = true;
	}
	return SDK_SUCCESS;
}

int 
Bandwidth::setup()
{
    //if(setupConstantBandwidth() != SDK_SUCCESS)
   //     return SDK_FAILURE;

    int timer = sampleCommon->createTimer();
    sampleCommon->resetTimer(timer);
    sampleCommon->startTimer(timer);

    int status = setupCL();
    if(status != SDK_SUCCESS)
    {
        if(status == SDK_EXPECTED_FAILURE)
            return SDK_EXPECTED_FAILURE;
        
        return SDK_FAILURE;
    }

    sampleCommon->stopTimer(timer);
    setupTime = (cl_double)sampleCommon->readTimer(timer);
    return SDK_SUCCESS;
}


int 
Bandwidth::run()
{
	
    int timer = sampleCommon->createTimer();
    sampleCommon->resetTimer(timer);
    sampleCommon->startTimer(timer);

	if(htod)
	{
		testBandwidth(HOST_TO_DEVICE);
	}                       
	if(dtoh)
	{
		testBandwidth(DEVICE_TO_HOST);
	}                       
	if(dtod)
	{
		testBandwidth(DEVICE_TO_DEVICE);
	}                

    sampleCommon->stopTimer(timer);
    totalKernelTime = (double)(sampleCommon->readTimer(timer));

    return SDK_SUCCESS;
}

int 
Bandwidth::verifyResults()
{
    return SDK_SUCCESS;
}


int 
Bandwidth::cleanup()
{
    // Releases OpenCL resources (Context, Memory etc.)
    cl_int status;

    //for(int i = 0; i < NUM_KERNELS; i++)
    //{
    //    status = clReleaseKernel(kernel[i]);
    //    CHECK_OPENCL_ERROR(status, "clReleaseKernel failed.");
    //}

    //status = clReleaseProgram(program);
    //CHECK_OPENCL_ERROR(status, "clReleaseProgram failed.");
 
    //status = clReleaseMemObject(constantBuffer);
    //CHECK_OPENCL_ERROR(status, "clReleaseMemObject failed.");

    //status = clReleaseMemObject(outputBuffer);
    //CHECK_OPENCL_ERROR(status, "clReleaseMemObject failed.");

    //status = clReleaseMemObject(randomIndicesBuffer);
    //CHECK_OPENCL_ERROR(status, "clReleaseMemObject failed.");

    status = clReleaseCommandQueue(commandQueue);
     CHECK_OPENCL_ERROR(status, "clReleaseCommandQueue failed.");

    status = clReleaseContext(context);
    CHECK_OPENCL_ERROR(status, "clReleaseContext failed.");

    // release program resources (input memory etc.)
    FREE(input);

    FREE(output);

    FREE(verificationOutput);

    // release device list
   FREE(devices);

    return SDK_SUCCESS;
}

int 
main(int argc, char * argv[])
{
    cl_int status = 0;
    Bandwidth clBandwidth("BandWidth benchmark");

    if(clBandwidth.initialize() != SDK_SUCCESS)
        return SDK_FAILURE;

    if(clBandwidth.parseCommandLine(argc, argv) != SDK_SUCCESS)
        return SDK_FAILURE;


	/*
    if(clBandwidth.isDumpBinaryEnabled())
    {
        return clBandwidth.genBinaryImage();
    }
*/
    status = clBandwidth.setup();
    if(status != SDK_SUCCESS)
    {
        if(status == SDK_EXPECTED_FAILURE)
            return SDK_SUCCESS;

        return SDK_FAILURE;
    }

    if(clBandwidth.run() != SDK_SUCCESS)
        return SDK_FAILURE;

    if(clBandwidth.verifyResults() != SDK_SUCCESS)
        return SDK_FAILURE;
    
    if(clBandwidth.cleanup() != SDK_SUCCESS)
        return SDK_FAILURE;

    return SDK_SUCCESS;
}
