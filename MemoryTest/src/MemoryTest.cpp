/**********************************************************************
Copyright (c) 2014,BUAA COMPILER LAB;
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
- Neither the name of the BUAA COMPILER LAB; nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
********************************************************************/
#include "MemoryTest.hpp"

inline int min(int x, int y) {
    if (x < y)
        return x;
    else
        return y;
}


int 
Memory::initialize()
{
	// Call base class Initialize to get default configuration
	if(this->Benchmark::initialize() != SDK_SUCCESS)
		return SDK_FAILURE;

	streamsdk::Option* opt_n = new streamsdk::Option;
	CHECK_ALLOCATION(opt_n, "Memory Allocation failed (opt_n)");

	opt_n->_sVersion = "N";
	opt_n->_lVersion = "N";
	opt_n->_description = "Number of iterations for kernel execution";
	opt_n->_type = streamsdk::CA_ARG_INT;
	opt_n->_value = &iterations;

	sampleArgs->AddOption(opt_n);
	delete opt_n;

	streamsdk::Option* opt_mode = new streamsdk::Option;
	CHECK_ALLOCATION(opt_mode, "Memory Allocation failed (opt_mode)");

	opt_mode->_sVersion = "";
	opt_mode->_lVersion = "memory";
	opt_mode->_description = "Specify which memory mode to use";
	opt_mode->_type = streamsdk::CA_ARG_STRING;
	opt_mode->_value = &mKind;

	sampleArgs->AddOption(opt_mode);
	delete opt_mode;

	return SDK_SUCCESS;
	
}

int
Memory::setupCL(void)
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
        /*if(isThereGPU() == false)
        {
            std::cout << "GPU not found. Falling back to CPU device" << std::endl;
            dType = CL_DEVICE_TYPE_CPU;
        }*/
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

    // The block is to move the declaration of prop closer to its use
	cl_command_queue_properties prop = 0;
	prop |= CL_QUEUE_PROFILING_ENABLE;

	commandQueue = clCreateCommandQueue(context,
											 devices[deviceId], 
											 prop, 
											 &status);
	CHECK_OPENCL_ERROR(status, "clCreateCommandQueue failed.");
	 
    // create a CL program using the kernel source
    streamsdk::buildProgramData buildData;
    buildData.kernelName = std::string("memory.cl");
    buildData.devices = devices;
    buildData.deviceId = deviceId;
    buildData.flagsStr = std::string("-cl-opt-disable");
    if(isLoadBinaryEnabled())
        buildData.binaryName = std::string(loadBinary.c_str());

    if(isComplierFlagsSpecified())
        buildData.flagsFileName = std::string(flags.c_str());

    retValue = sampleCommon->buildOpenCLProgram(program, context, buildData);
    CHECK_ERROR(retValue, SDK_SUCCESS, "sampleCommon::buildOpenCLProgram() failed");
     
    // Create the readGlobalMemory
    kernel[0] = clCreateKernel(program, "readGlobalMemory", &status);
    CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(readGlobalMemory)");

    // Create the readGlobalMemory
    kernel[1] = clCreateKernel(program, "writeGlobalMemory", &status);
    CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(writeGlobalMemory)");

    // Create the readGlobalMemory
    kernel[2] = clCreateKernel(program, "readLocalMemory", &status);
    CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(readLocalMemory)");

    // Create the readGlobalMemory
    kernel[3] = clCreateKernel(program, "writeLocalMemory", &status);
    CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(writeLocalMemory)");

   // Create the cKermel_readImg2D_mem
   kernel[4] = clCreateKernel(program, "readImg2D", &status);
   CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(readImg2D)");

   // Create the kernel_writeImg2D_mem
   kernel[5] = clCreateKernel(program, "writeImg2D", &status);
   CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(writeImg2D)");

   return SDK_SUCCESS;
}

int 
Memory::setup()
{
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

double 
Memory::executionTime(cl_event &event)
{
	cl_ulong start, end;
	cl_int status = 0;

	status  = clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end, NULL);
	status |= clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start, NULL);

	CHECK_OPENCL_ERROR(status, "clGetEventProfilingInfo failed. (event)");

	//return (double)1.0e-6*(end - start); // convert nanoseconds to min seconds on return
	return end - start;
}

int 
Memory::run()
{
	/*
	// Warm up
	for(int i = 0; i < 2 && iterations != 1; i++)
	{
		// Arguments are set and execution call is enqueued on command buffer
		if(runCLKernels() != SDK_SUCCESS)
			return SDK_FAILURE;
	}
	*/
	int timer = sampleCommon->createTimer();
	sampleCommon->resetTimer(timer);
	sampleCommon->startTimer(timer);

	if ( (mKind.compare("all") == 0) || (mKind.compare("global") == 0) )
	{
		if (runCLGlobalKernels() != SDK_SUCCESS)
		{
			return SDK_FAILURE;
		}
	}

	if ( (mKind.compare("all") == 0) || (mKind.compare("local") == 0) )
	{
		if (runCLLocalKernels() != SDK_SUCCESS)
		{
			return SDK_FAILURE;
		}
	}
	if ( (mKind.compare("all") == 0) || (mKind.compare("image") == 0) )
	{
		if (runCLImageKernels() != SDK_SUCCESS)
		{
			return SDK_FAILURE;
		}
	}

	
	sampleCommon->stopTimer(timer);
	totalKernelTime = (double)sampleCommon->readTimer(timer);

	//if(!quiet) {
	//	sampleCommon->printArray<cl_float>("Output", eigenIntervals[1], 2*length, 1);
	//}

	return SDK_SUCCESS;
}
int
Memory::runCLGlobalKernels()
{
	int minGroupSize = 32;
	size_t maxGroupSize = 0;
	int numSMs = deviceInfo.maxComputeUnits;
	if(deviceType.compare("cpu") == 0)
	{
	   minGroupSize = 256;
	}

	int memSize = 64*1024*1024;  // 64MB buffer
	const long availMem = deviceInfo.maxMemAllocSize;
	while (memSize*2 > availMem)
	{
	   memSize >>= 1;   // keep it a power of 2
	}
	// find the maximum allowed group size
	if (!maxGroupSize)
	{
		maxGroupSize = min(deviceInfo.maxWorkGroupSize, 512);
	}
	const int numWordsFloat = memSize / sizeof(float);
	size_t numWarps = numSMs * 16;  // use 8 times as many warps as the number of compute units
	size_t globalWorkSize = numSMs * maxGroupSize * 5;
	int elemSize = sizeof(float);

	printf(">> running the readGlobalMemory kernel");
	printf("-------------------------------------------------------------");
	printf("-------------------------------------------------------------\n");
	printf("stride  GB/s\n");
	//test global memory read with stride from 0 to 16
	for(int stride = 0 ; stride <=16; stride++)
	{
		double maxBW = 0;
		// initialize host memory
		float *hostMemFloat = new float[numWordsFloat];
		float *outMemFloat = new float[numWordsFloat];
		srand48(8650341L);
		for (int i=0 ; i<numWordsFloat ; ++i)
		{
			hostMemFloat[i] = (float)(drand48()*numWordsFloat);
		}

		// Allocate some device memory
		int err;
		cl_mem mem1, mem2;
		mem1 = clCreateBuffer(context, CL_MEM_READ_WRITE,
					 sizeof(cl_float)*(numWordsFloat),
					 NULL, &err);
		CHECK_OPENCL_ERROR(err, "clCreateBuffer(mem1) failed.");
		cl_event evDownloadPrime;
		err = clEnqueueWriteBuffer(commandQueue, mem1, false, 0,
					 (numWordsFloat)*sizeof(float),
					 hostMemFloat,
					 0, NULL,
					 &evDownloadPrime);
		CHECK_OPENCL_ERROR(err, "clEnqueueWriteBuffer(mem1) failed.");
		err = clWaitForEvents(1, &evDownloadPrime);
		CHECK_OPENCL_ERROR(err, "clWaitForEvents(evDownloadPrime) failed.");

		mem2 = clCreateBuffer(context, CL_MEM_READ_WRITE,
					 sizeof(cl_float)*(numWordsFloat),
					 NULL, &err);
		CHECK_OPENCL_ERROR(err, "clCreateBuffer(mem2) failed.");
		cl_event evDownloadPrime2;
		err = clEnqueueWriteBuffer(commandQueue, mem2, false, 0,
					 (numWordsFloat)*sizeof(float),
					 hostMemFloat,
					 0, NULL,
					 &evDownloadPrime2);
		CHECK_OPENCL_ERROR(err, "clEnqueueWriteBuffer(mem2) failed.");
		err = clWaitForEvents(1, &evDownloadPrime2);
		CHECK_OPENCL_ERROR(err, "clWaitForEvents(evDownloadPrime2) failed.");

		err = clSetKernelArg(kernel[0], 0 , sizeof(cl_mem), (void*)&mem1);
		err |= clSetKernelArg(kernel[0], 1 , sizeof(cl_mem), (void*)&mem2);
		err |= clSetKernelArg(kernel[0], 2, sizeof(cl_int), (void*)&numWordsFloat);
		err |= clSetKernelArg(kernel[0], 3, sizeof(cl_int), (void*)&stride);
		CHECK_OPENCL_ERROR(err, "clSetKernelArg(kernel[0]) failed.");
		
		// Run the kernel for each group size
		for (size_t wsize=minGroupSize ; wsize<=maxGroupSize ; wsize*=2)
		{
			size_t localWorkSize = wsize;
			numWarps = globalWorkSize / localWorkSize;
			//std::cout << ">> globalWorkSize=" << globalWorkSize
			//	 << ", localWorkSize=" << localWorkSize << " and number of groups=" << numWarps << "\n";

			for (int pas=0 ; pas<10 ; ++pas)
			{
				cl_event evKernel;
				err = clEnqueueNDRangeKernel(commandQueue,
						kernel[0], 1, NULL,
						&globalWorkSize, &localWorkSize,
						0, NULL, &evKernel);
				CHECK_OPENCL_ERROR(err, "clEnqueueNDRangeKernel failed.");

				// Wait for the kernel to finish
				err = clWaitForEvents(1, &evKernel);
				CHECK_OPENCL_ERROR(err, "clWaitForEvents(evKernel) failed.");

				// Read the result device memory back to the host
				cl_event evReadback;
				err = clEnqueueReadBuffer(commandQueue, mem2, false, 0,
						 numWordsFloat*sizeof(float), outMemFloat,
						 0, NULL, &evReadback);
				CHECK_OPENCL_ERROR(err, "clEnqueueReadBuffer failed.");
				err = clWaitForEvents(1, &evReadback);
				CHECK_OPENCL_ERROR(err, "clWaitForEvents(evReadback) failed.");
				double evTime = executionTime(evKernel);

				double bdwth = ((double)globalWorkSize*1024*16*elemSize)
					 / evTime;
				if(bdwth > maxBW)
					maxBW = bdwth;
				//printf("%.2f GB/s\t", bdwth);
			}
			//printf("\n");
		}
		printf("%d       %.2f\n",stride,maxBW);
		err = clReleaseMemObject(mem1);
		//CL_CHECK_ERROR(err);
		err = clReleaseMemObject(mem2);
		// CL_CHECK_ERROR(err);
		//printf ("\n\n");
		delete[] hostMemFloat;
		delete[] outMemFloat;
	}


	printf(">> running the writeGlobalMemory kernel");
	printf("-------------------------------------------------------------");
	printf("-------------------------------------------------------------\n");
	printf("stride  GB/s\n");
	//test global memory write with stride from 0 to 16
	for(int stride = 0 ; stride <=16; stride++)
	{
		double maxWDB = 0;
		// initialize host memory
		float *hostMemFloat = new float[numWordsFloat];
		float *outMemFloat = new float[numWordsFloat];
		srand48(8650341L);
		for (int i=0 ; i<numWordsFloat ; ++i)
		{
			hostMemFloat[i] = (float)(drand48()*numWordsFloat);
		}

		// Allocate some device memory
		int err;
		cl_mem mem2;

		mem2 = clCreateBuffer(context, CL_MEM_READ_WRITE,
					 sizeof(cl_float)*(numWordsFloat),
					 NULL, &err);
		CHECK_OPENCL_ERROR(err, "clCreateBuffer(mem2) failed.");
		cl_event evDownloadPrime2;
		err = clEnqueueWriteBuffer(commandQueue, mem2, false, 0,
					 (numWordsFloat)*sizeof(float),
					 hostMemFloat,
					 0, NULL,
					 &evDownloadPrime2);
		CHECK_OPENCL_ERROR(err, "clEnqueueWriteBuffer(mem2) failed.");
		err = clWaitForEvents(1, &evDownloadPrime2);
		CHECK_OPENCL_ERROR(err, "clWaitForEvents(evDownloadPrime2) failed.");

		err = clSetKernelArg(kernel[1], 0 , sizeof(cl_mem), (void*)&mem2);
		err |= clSetKernelArg(kernel[1], 1, sizeof(cl_int), (void*)&numWordsFloat);
		err |= clSetKernelArg(kernel[1], 2, sizeof(cl_int), (void*)&stride);
		CHECK_OPENCL_ERROR(err, "clSetKernelArg(kernel[0]) failed.");

		// Run the kernel for each group size
		for (size_t wsize=minGroupSize ; wsize<=maxGroupSize ; wsize*=2)
		{
			size_t localWorkSize = wsize;
			numWarps = globalWorkSize / localWorkSize;
			//std::cout << ">> globalWorkSize=" << globalWorkSize
			//	 << ", localWorkSize=" << localWorkSize << " and number of groups=" << numWarps << "\n";

			for (int pas=0 ; pas<10 ; ++pas)
			{
				cl_event evKernel;
				err = clEnqueueNDRangeKernel(commandQueue,
						kernel[1], 1, NULL,
						&globalWorkSize, &localWorkSize,
						0, NULL, &evKernel);
				CHECK_OPENCL_ERROR(err, "clEnqueueNDRangeKernel failed.");

				// Wait for the kernel to finish
				err = clWaitForEvents(1, &evKernel);
				CHECK_OPENCL_ERROR(err, "clWaitForEvents(evKernel) failed.");

				// Read the result device memory back to the host
				cl_event evReadback;
				err = clEnqueueReadBuffer(commandQueue, mem2, false, 0,
						 numWordsFloat*sizeof(float), outMemFloat,
						 0, NULL, &evReadback);
				CHECK_OPENCL_ERROR(err, "clEnqueueReadBuffer failed.");
				err = clWaitForEvents(1, &evReadback);
				CHECK_OPENCL_ERROR(err, "clWaitForEvents(evReadback) failed.");
				double evTime = executionTime(evKernel);

				double bdwth = ((double)globalWorkSize*1024*16*elemSize)
					 / evTime;
				if(bdwth > maxWDB)
					maxWDB = bdwth;
				//printf("%.2f GB/s\t", bdwth);
			}
			//printf("\n");
		}
		printf("%d       %.2f \n",stride,maxWDB);
		err = clReleaseMemObject(mem2);
		// CL_CHECK_ERROR(err);
		//printf ("\n\n");
		delete[] hostMemFloat;
		delete[] outMemFloat;
	}

	return SDK_SUCCESS;
}

int
Memory::runCLLocalKernels()
{
	int minGroupSize = 32;
	size_t maxGroupSize = 0;
	int numSMs = deviceInfo.maxComputeUnits;
	if(deviceType.compare("cpu") == 0)
	{
	   minGroupSize = 256;
	}

	int memSize = 64*1024*1024;  // 64MB buffer
	const long availMem = deviceInfo.maxMemAllocSize;
	while (memSize*2 > availMem)
	{
	   memSize >>= 1;   // keep it a power of 2
	}
	// find the maximum allowed group size
	if (!maxGroupSize)
	{
		maxGroupSize = min(deviceInfo.maxWorkGroupSize, 512);
	}
	const int numWordsFloat = memSize / sizeof(float);
	size_t numWarps = numSMs * 16;  // use 8 times as many warps as the number of compute units
	size_t globalWorkSize = numSMs * maxGroupSize * 5;
	int elemSize = sizeof(float);

	printf(">> running the readLocalMemory kernel\n");
	printf("-------------------------------------------------------------");
	printf("-------------------------------------------------------------\n");
	printf("stride  GB/s\n");
	//test global memory read with stride from 0 to 16
	for(int stride = 0 ; stride <=16; stride++)
	{
		double maxBW = 0;
		// initialize host memory
		float *hostMemFloat = new float[numWordsFloat];
		float *outMemFloat = new float[numWordsFloat];
		srand48(8650341L);
		for (int i=0 ; i<numWordsFloat ; ++i)
		{
			hostMemFloat[i] = (float)(drand48()*numWordsFloat);
		}

		// Allocate some device memory
		int err;
		cl_mem mem1, mem2;
		mem1 = clCreateBuffer(context, CL_MEM_READ_WRITE,
					 sizeof(cl_float)*(numWordsFloat),
					 NULL, &err);
		CHECK_OPENCL_ERROR(err, "clCreateBuffer(mem1) failed.");
		cl_event evDownloadPrime;
		err = clEnqueueWriteBuffer(commandQueue, mem1, false, 0,
					 (numWordsFloat)*sizeof(float),
					 hostMemFloat,
					 0, NULL,
					 &evDownloadPrime);
		CHECK_OPENCL_ERROR(err, "clEnqueueWriteBuffer(mem1) failed.");
		err = clWaitForEvents(1, &evDownloadPrime);
		CHECK_OPENCL_ERROR(err, "clWaitForEvents(evDownloadPrime) failed.");

		mem2 = clCreateBuffer(context, CL_MEM_READ_WRITE,
					 sizeof(cl_float)*(numWordsFloat),
					 NULL, &err);
		CHECK_OPENCL_ERROR(err, "clCreateBuffer(mem2) failed.");
		cl_event evDownloadPrime2;
		err = clEnqueueWriteBuffer(commandQueue, mem2, false, 0,
					 (numWordsFloat)*sizeof(float),
					 hostMemFloat,
					 0, NULL,
					 &evDownloadPrime2);
		CHECK_OPENCL_ERROR(err, "clEnqueueWriteBuffer(mem2) failed.");
		err = clWaitForEvents(1, &evDownloadPrime2);
		CHECK_OPENCL_ERROR(err, "clWaitForEvents(evDownloadPrime2) failed.");

		err = clSetKernelArg(kernel[2], 0 , sizeof(cl_mem), (void*)&mem1);
		err |= clSetKernelArg(kernel[2], 1 , sizeof(cl_mem), (void*)&mem2);
		err |= clSetKernelArg(kernel[2], 2, sizeof(cl_int), (void*)&numWordsFloat);
		err |= clSetKernelArg(kernel[2], 3, sizeof(cl_int), (void*)&stride);
		CHECK_OPENCL_ERROR(err, "clSetKernelArg(kernel[0]) failed.");

		// Run the kernel for each group size
		for (size_t wsize=minGroupSize ; wsize<=maxGroupSize ; wsize*=2)
		{
			size_t localWorkSize = wsize;
			numWarps = globalWorkSize / localWorkSize;
			//std::cout << ">> globalWorkSize=" << globalWorkSize
			//	 << ", localWorkSize=" << localWorkSize << "\n";

			for (int pas=0 ; pas<10 ; ++pas)
			{
				cl_event evKernel;
				err = clEnqueueNDRangeKernel(commandQueue,
						kernel[2], 1, NULL,
						&globalWorkSize, &localWorkSize,
						0, NULL, &evKernel);
				CHECK_OPENCL_ERROR(err, "clEnqueueNDRangeKernel failed.");

				// Wait for the kernel to finish
				err = clWaitForEvents(1, &evKernel);
				CHECK_OPENCL_ERROR(err, "clWaitForEvents(evKernel) failed.");

				// Read the result device memory back to the host
				cl_event evReadback;
				err = clEnqueueReadBuffer(commandQueue, mem2, false, 0,
						 numWordsFloat*sizeof(float), outMemFloat,
						 0, NULL, &evReadback);
				CHECK_OPENCL_ERROR(err, "clEnqueueReadBuffer failed.");
				err = clWaitForEvents(1, &evReadback);
				CHECK_OPENCL_ERROR(err, "clWaitForEvents(evReadback) failed.");
				double evTime = executionTime(evKernel);

				double bdwth = ((double)globalWorkSize*3000*16*elemSize)
					 / evTime;
				if(bdwth > maxBW)
					maxBW = bdwth;
				//printf("%.2f GB/s\t", bdwth);
			}
			//printf("\n");
		}
		printf("%d       %.2f\n",stride,maxBW);
		err = clReleaseMemObject(mem1);
		//CL_CHECK_ERROR(err);
		err = clReleaseMemObject(mem2);
		// CL_CHECK_ERROR(err);
		//printf ("\n\n");
		delete[] hostMemFloat;
		delete[] outMemFloat;
	}


	printf(">> running the writeLocalMemory kernel");
	printf("-------------------------------------------------------------");
	printf("-------------------------------------------------------------\n");
	printf("stride  GB/s\n");
	//test global memory write with stride from 0 to 16
	for(int stride = 0 ; stride <=16; stride++)
	{
		double maxBW = 0;
		// initialize host memory
		float *hostMemFloat = new float[numWordsFloat];
		float *outMemFloat = new float[numWordsFloat];
		srand48(8650341L);
		for (int i=0 ; i<numWordsFloat ; ++i)
		{
			hostMemFloat[i] = (float)(drand48()*numWordsFloat);
		}

		// Allocate some device memory
		int err;
		cl_mem mem2;

		mem2 = clCreateBuffer(context, CL_MEM_READ_WRITE,
					 sizeof(cl_float)*(numWordsFloat),
					 NULL, &err);
		CHECK_OPENCL_ERROR(err, "clCreateBuffer(mem2) failed.");
		cl_event evDownloadPrime2;
		err = clEnqueueWriteBuffer(commandQueue, mem2, false, 0,
					 (numWordsFloat)*sizeof(float),
					 hostMemFloat,
					 0, NULL,
					 &evDownloadPrime2);
		CHECK_OPENCL_ERROR(err, "clEnqueueWriteBuffer(mem2) failed.");
		err = clWaitForEvents(1, &evDownloadPrime2);
		CHECK_OPENCL_ERROR(err, "clWaitForEvents(evDownloadPrime2) failed.");

		err = clSetKernelArg(kernel[3], 0 , sizeof(cl_mem), (void*)&mem2);
		err |= clSetKernelArg(kernel[3], 1, sizeof(cl_int), (void*)&numWordsFloat);
		err |= clSetKernelArg(kernel[3], 2, sizeof(cl_int), (void*)&stride);
		CHECK_OPENCL_ERROR(err, "clSetKernelArg(kernel[3]) failed.");

		// Run the kernel for each group size
		for (size_t wsize=minGroupSize ; wsize<=maxGroupSize ; wsize*=2)
		{
			size_t localWorkSize = wsize;
			numWarps = globalWorkSize / localWorkSize;
			//std::cout << ">> globalWorkSize=" << globalWorkSize
			//	 << ", localWorkSize=" << localWorkSize << "\n";

			for (int pas=0 ; pas<10 ; ++pas)
			{
				cl_event evKernel;
				err = clEnqueueNDRangeKernel(commandQueue,
						kernel[3], 1, NULL,
						&globalWorkSize, &localWorkSize,
						0, NULL, &evKernel);
				CHECK_OPENCL_ERROR(err, "clEnqueueNDRangeKernel failed.");

				// Wait for the kernel to finish
				err = clWaitForEvents(1, &evKernel);
				CHECK_OPENCL_ERROR(err, "clWaitForEvents(evKernel) failed.");

				// Read the result device memory back to the host
				cl_event evReadback;
				err = clEnqueueReadBuffer(commandQueue, mem2, false, 0,
						 numWordsFloat*sizeof(float), outMemFloat,
						 0, NULL, &evReadback);
				CHECK_OPENCL_ERROR(err, "clEnqueueReadBuffer failed.");
				err = clWaitForEvents(1, &evReadback);
				CHECK_OPENCL_ERROR(err, "clWaitForEvents(evReadback) failed.");
				double evTime = executionTime(evKernel);

				double bdwth = ((double)globalWorkSize*3000*16*elemSize)
					 / evTime;
				if(bdwth > maxBW)
					maxBW = bdwth;
				//printf("%.2f GB/s\t", bdwth);
			}
			//printf("\n");
		}
		printf("%d       %.2f\n",stride,maxBW);
		err = clReleaseMemObject(mem2);
		// CL_CHECK_ERROR(err);
		//printf ("\n\n");
		delete[] hostMemFloat;
		delete[] outMemFloat;
	}

	return SDK_SUCCESS;
}

int 
Memory::runCLImageKernels()
{
	cl_int status = 0;
	int repeat = 1024;
	int nsizes = 5;
	int sizes[] = {16, 64, 256, 1024, 4096};
	/************************* Image2D read ***************************/
	std::cout << "-----------------------------------------" << std::endl << std::endl;
	std::cout << "Read Image2DBuffer Test....." << std::endl;
	for( int i = 0; i < nsizes; i++) 
	{
		int size = 1024 * sizes[i];
		length = size / sizeof(float);
		cl_uint outLength = size / sizeof(cl_float4);

		// Allocate memory 
		cl_float* input = (cl_float*)malloc(length * sizeof(cl_float));
		CHECK_ALLOCATION(input, "Failed to allocate host memory. (input)");

		// random initialisation of input
		sampleCommon->fillRandom<cl_float>(input,length,1,0,32);

		//create buffer
		//cl_mem input_readLocal_mem = clCreateBuffer(context, CL_MEM_READ_WRITE, length*sizeof(float), NULL, &status);
		//CHECK_OPENCL_ERROR(status, "clCreateBuffer failed. (input_readLocal_mem)");

		cl_mem output_readImg2D_mem = clCreateBuffer(context, CL_MEM_READ_WRITE, outLength*sizeof(float), NULL, &status);
		CHECK_OPENCL_ERROR(status, "clCreateBuffer failed. (output_readLocal_mem)");

		size_t height, width;
		size_t h = (int)( (log10(double(outLength)) / log10(2.0)) + 0.5);
		height = 1 << (h >> 1);
		size_t minHeight = height>>2;
		size_t maxHeight = height<<2;

		for(height = minHeight; height <= maxHeight; height*=2) 
		{
			width = outLength / height;
			size_t ImgOrigin[3] = {0, 0, 0};
			size_t ImgRegion[3] = {width, height, 1};
			size_t ImgRP = 4 * width * sizeof(float);
			size_t ImgSP = 0;

			// create image object 
			cl_image_format format;
			format.image_channel_order = CL_RGBA;
			format.image_channel_data_type = CL_FLOAT;

			cl_mem Img2D = clCreateImage2D(context, CL_MEM_READ_WRITE, &format, width,height,0, NULL, &status);
			CHECK_OPENCL_ERROR(status, "clCreateImage failed. (Img2D)");
			
			status = clEnqueueWriteImage(commandQueue, Img2D, CL_TRUE, ImgOrigin, 
				ImgRegion,ImgRP, ImgSP,(void*)input,0, NULL, NULL);
			CHECK_OPENCL_ERROR(status, "clEnqueueWriteBuffer failed. (input_readLocal_mem)");

			// Set appropriate arguments to the kernel
			// first argument for kernel - input_readLocal_mem
			status = clSetKernelArg(
				kernel[4], 
				0, 
				sizeof(cl_mem), 
				(void *)&Img2D);
			CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (input_readLocal_mem)");
			// second argument for kernel - output_readLocal_mem
			status = clSetKernelArg(
				kernel[4], 
				1, 
				sizeof(cl_mem), 
				(void *)&output_readImg2D_mem);
			CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (output_readLocal_mem)");
			// third argument for kernel - repeat
			status = clSetKernelArg(
				kernel[4], 
				2, 
				sizeof(cl_int), 
				(void *)&repeat);
			CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (length)");
			// forth argument for kernel - width
			status = clSetKernelArg(
				kernel[4], 
				3, 
				sizeof(cl_int), 
				(void *)&width);
			CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (repeat)");

			//launch kernel_none
			double eTime_readImg2D_max = 0.0;
			double eTime_readImg2D_avg = 0.0;
			double eTime_readImg2D_min = MAX_TIME;
			//cl_event event_readImg2D_mem;
			size_t szImgLocalWorkSize[] = {8, 8};
			size_t szImgGlobalWorkSize[] = {width, height};	
			double t = 0.0;
			double bdwth = 0.0;

			for(int j = 0; j < iterations; j++) 
			{
				cl_event event_readImg2D_mem;
				status=clEnqueueNDRangeKernel(commandQueue,
					kernel[4],
					2, 
					NULL,
					szImgGlobalWorkSize,
					szImgLocalWorkSize,
					0, 
					NULL,
					&event_readImg2D_mem);
				CHECK_OPENCL_ERROR(status, "clEnqueueNDRangeKernel failed.");

				status=clWaitForEvents(1, &event_readImg2D_mem);
				CHECK_OPENCL_ERROR(status, "clWaitForEvents failed. ((event_readImg2D_mem))"); 

				double eTime_readImg2D = executionTime(event_readImg2D_mem);
				clReleaseEvent(event_readImg2D_mem);
				if(eTime_readImg2D_max < eTime_readImg2D) { 
					eTime_readImg2D_max = eTime_readImg2D;
				}	

				if(eTime_readImg2D_min > eTime_readImg2D) {
					eTime_readImg2D_min = eTime_readImg2D;
				}
				eTime_readImg2D_avg += eTime_readImg2D;
			}
			t = eTime_readImg2D_avg/(iterations*1.0);
			bdwth = ((double)size * (double)repeat) / (t);
			printf("memSize = %dKB\tnumFloat4 = %d\theight = %d\twidth = %d\t",sizes[i], outLength,  height, width);
			printf("readImg2D_BW = %f GB/s\n", bdwth);
#ifdef profile
			printf("\nRead Iamge2DBuffer is %f ms\n", eTime_readImg2D_avg/(iterations*1.0));	
			printf("\neTime_readImg2D_max is %f ms\n", eTime_readImg2D_max);	
			printf("\neTime_readImg2D_min is %f ms\n", eTime_readImg2D_min);	
#endif
			clReleaseMemObject(Img2D);
		}
		clReleaseMemObject(output_readImg2D_mem);
		free(input);
	}

	/************************* Image2D write ***************************/
	std::cout << "-----------------------------------------" << std::endl << std::endl;
	std::cout << "Write Image2DBuffer Test....." << std::endl;
	for( int i = 0; i < nsizes; i++) 
	{
		int size = 1024 * sizes[i];
		length = size / sizeof(float);
		cl_uint outLength = size / sizeof(cl_float4);

		size_t height, width;
		size_t h = (int)( (log10(double(outLength)) / log10(2.0)) + 0.5);
		height = 1 << (h >> 1);
		size_t minHeight = height>>2;
		size_t maxHeight = height<<2;

		for(height = minHeight; height <= maxHeight; height*=2) 
		{
			width = outLength / height;
			size_t ImgOrigin[3] = {0, 0, 0};
			size_t ImgRegion[3] = {width, height, 1};
			size_t ImgRP = 4 * width * sizeof(float);
			size_t ImgSP = 0;

			// create image object 
			cl_image_format format;
			format.image_channel_order = CL_RGBA;
			format.image_channel_data_type = CL_FLOAT;

			cl_mem Img2D = clCreateImage2D(context, CL_MEM_READ_WRITE, &format, width,height,0, NULL, &status);
			CHECK_OPENCL_ERROR(status, "clCreateImage failed. (Img2D)");
			CHECK_OPENCL_ERROR(status, "clCreateImage failed. (Img2D)");

			// Set appropriate arguments to the kernel
			// first argument for kernel - input_readLocal_mem
			status = clSetKernelArg(
				kernel[5], 
				0, 
				sizeof(cl_mem), 
				(void *)&Img2D);
			CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (Img2D)");
			// second argument for kernel - repeat
			status = clSetKernelArg(
				kernel[5], 
				1, 
				sizeof(cl_int), 
				(void *)&repeat);
			CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (length)");

			//launch kernel_none
			double eTime_writeImg2D_max = 0.0;
			double eTime_writeImg2D_avg = 0.0;
			double eTime_writeImg2D_min = MAX_TIME;
			cl_event event_writeImg2D_mem;

			size_t szImgLocalWorkSize[] = {8, 8};
			size_t szImgGlobalWorkSize[] = {width, height};	
			double t = 0.0;
			double bdwth = 0.0;

			for(int j = 0; j < iterations; j++) 
			{
				status=clEnqueueNDRangeKernel(commandQueue,
					kernel[5],
					2, 
					NULL,
					szImgGlobalWorkSize,
					szImgLocalWorkSize,
					0, 
					NULL,
					&event_writeImg2D_mem);
				CHECK_OPENCL_ERROR(status, "clEnqueueNDRangeKernel failed.");

				status=clWaitForEvents(1, &event_writeImg2D_mem);
				CHECK_OPENCL_ERROR(status, "clWaitForEvents failed. ((event_readImg2D_mem))"); 

				double eTime_writeImg2D = executionTime(event_writeImg2D_mem);

				if(eTime_writeImg2D_max < eTime_writeImg2D) { 
					eTime_writeImg2D_max = eTime_writeImg2D;
				}	

				if(eTime_writeImg2D_min > eTime_writeImg2D) {
					eTime_writeImg2D_min = eTime_writeImg2D;
				}
				eTime_writeImg2D_avg += eTime_writeImg2D;
			}
			t = eTime_writeImg2D_avg/(iterations*1.0);
			bdwth = ((double)size * (double)repeat) / (t);
			printf("memSize = %dKB\tnumFloat4 = %d\theight = %d\twidth = %d\t",sizes[i], outLength,  height, width);
			printf("readImg2D_BW = %f GB/s\n", bdwth);
#ifdef profile
			printf("\nRead Iamge2DBuffer is %f ms\n", eTime_writeImg2D_avg/(iterations*1.0));	
			printf("\neTime_readImg2D_max is %f ms\n", eTime_writeImg2D_max);	
			printf("\neTime_readImg2D_min is %f ms\n", eTime_writeImg2D_min);	
#endif
			clReleaseMemObject(Img2D);
		}
	}

	return SDK_SUCCESS;
}



int 
Memory::cleanup()
{
	// Releases OpenCL resources (Context, Memory etc.)
	cl_int status;

	for (int i = 0; i < NUM_KERNELS; i++)
	{
		status = clReleaseKernel(kernel[i]);
		CHECK_OPENCL_ERROR(status, "clReleaseKernel failed.");
	}

	status = clReleaseProgram(program);
	CHECK_OPENCL_ERROR(status, "clReleaseProgram failed.(program)");

	status = clReleaseCommandQueue(commandQueue);
	CHECK_OPENCL_ERROR(status, "clReleaseCommandQueue failed.(commandQueue)");

	status = clReleaseContext(context);
	CHECK_OPENCL_ERROR(status, "clReleaseContext failed.(context)");

	FREE(devices);
	return SDK_SUCCESS;
}

int 
Memory::verifyResults()
{
	return SDK_SUCCESS;
}

void 
Memory::printStats()
{
	std::string strArray[3] = {"DiagonalLength", "Time(sec)", "[Transfer+Kernel]Time(sec)"};
	std::string stats[3];

	totalTime = setupTime + totalKernelTime;

	stats[0] = sampleCommon->toString(1410, std::dec);
	stats[1] = sampleCommon->toString(totalTime, std::dec);
	stats[2] = sampleCommon->toString(totalKernelTime, std::dec);

	this->Benchmark::printStats(strArray, stats, 3);
}

int main(int argc, char *argv[])
{
	cl_int status = 0;

	Memory clMemory("MemoryTest benchmark");
	
	if (clMemory.initialize() != SDK_SUCCESS)
		return SDK_FAILURE;

	if(clMemory.parseCommandLine(argc, argv) != SDK_SUCCESS)
		return SDK_FAILURE;

	status = clMemory.setup();
	if(status != SDK_SUCCESS)
	{
		if(status == SDK_EXPECTED_FAILURE)
			return SDK_SUCCESS;

		return SDK_FAILURE;
	}

	if(clMemory.run()!=SDK_SUCCESS)
		return SDK_FAILURE;

	if(clMemory.verifyResults()!=SDK_SUCCESS)
		return SDK_FAILURE;

	if(clMemory.cleanup()!=SDK_SUCCESS)
		return SDK_FAILURE;

	clMemory.printStats();

	return SDK_SUCCESS;
}
