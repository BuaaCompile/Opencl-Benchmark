/**********************************************************************
Copyright (c) 2014,BUAA COMPILER LAB;
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
- Neither the name of the BUAA COMPILER LAB; nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
********************************************************************/
#include "MemoryCacheTest.hpp"


int 
MemoryCache::initialize()
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
MemoryCache::setupMemory(void)
{ 
// 	unsigned int memSize = 64*1024*1024;//default
// 	length = memSize / sizeof(float);
// 	cl_uint size = length * sizeof(cl_float);
// 
// 	// Allocate memory 
// 	input = (cl_float*)malloc(size);
// 	CHECK_ALLOCATION(input, "Failed to allocate host memory. (input)");
// 
// 	// random initialisation of input
// 	sampleCommon->fillRandom<cl_float>(input,length,1,0,32);

	return SDK_SUCCESS;

}

int
MemoryCache::setupCL(void)
{
    cl_int status = 0;
    cl_device_type dType;

	size_t seqGlobalWorkSize = 32;
    
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

	{
		// The block is to move the declaration of prop closer to its use
		cl_command_queue_properties prop = 0;
		prop |= CL_QUEUE_PROFILING_ENABLE;

		commandQueue = clCreateCommandQueue(context, 
											 devices[deviceId], 
											 prop, 
											 &status);
		CHECK_OPENCL_ERROR(status, "clCreateCommandQueue failed.");
	}

    // create a CL program using the kernel source
    streamsdk::buildProgramData buildData;
    buildData.kernelName = std::string("memoryCache.cl");
    buildData.devices = devices;
    buildData.deviceId = deviceId;
    buildData.flagsStr = std::string("");
    if(isLoadBinaryEnabled())
        buildData.binaryName = std::string(loadBinary.c_str());

    if(isComplierFlagsSpecified())
        buildData.flagsFileName = std::string(flags.c_str());

    retValue = sampleCommon->buildOpenCLProgram(program, context, buildData);
    CHECK_ERROR(retValue, SDK_SUCCESS, "sampleCommon::buildOpenCLProgram() failed");

   	// Create the MemCache
    	kernel[0] = clCreateKernel(program, "MemCache", &status);
    	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(MemCache)");

	// Create the ConMemCache
	kernel[1] = clCreateKernel(program, "ConMemCache", &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(ConMemCache)");

	// Create the LocalMemCache
	kernel[2] = clCreateKernel(program, "LocalMemCache", &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(LocalMemCache)");

    return SDK_SUCCESS;
}

int 
MemoryCache::setup()
{
	if(setupMemory() != SDK_SUCCESS)
		return SDK_FAILURE;

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
MemoryCache::executionTime(cl_event &event)
{
	cl_ulong start, end;
	cl_int status = 0;

	status  = clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end, NULL);
	status |= clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start, NULL);

	CHECK_OPENCL_ERROR(status, "clGetEventProfilingInfo failed. (event)");

	return (double)(end - start); // convert nanoseconds to min seconds on return
}

int
MemoryCache::runCLConstantKernels()
{
	cl_int status = 0;
	int stride;
	/************************* constant cache ****************************/
	std::cout << "-----------------------------------------" << std::endl;
	std::cout << "Constant Memory Cache Test....." << std::endl;
	length =32768/2;
	input = (int *)malloc((length) * sizeof(int));
	CHECK_ALLOCATION(input, "Failed to allocate host memory. (input)");
	//input[length] = 0;

	std::cout << "Stride\t" ;
#ifdef profile
	std::cout << "Out\t";
#endif
	std::cout << "Time(ns)" << std::endl;
	for(stride = 1; stride <= 256; stride=stride++)
	{
		for(int i = 0; i < length; i++) 
			input[i] = ((i + stride) % length);

		cl_mem ConMemCache_mem = clCreateBuffer(context, CL_MEM_READ_WRITE, (length)*sizeof(int), NULL, &status);
		CHECK_OPENCL_ERROR(status, "clCreateBuffer failed. (ConMemCache_mem)");

		cl_mem out_ConMemCache_mem = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(int), NULL, &status);
		CHECK_OPENCL_ERROR(status, "clCreateBuffer failed. (out_ConMemCache_mem)");

		status = clEnqueueWriteBuffer(commandQueue, ConMemCache_mem, CL_FALSE, 
			0,(length)*sizeof(int), (int*)input, 0, NULL, NULL);
		CHECK_OPENCL_ERROR(status, "clEnqueueWriteBuffer failed. (ConMemCache_mem)");

		// Set appropriate arguments to the kernel
		// first argument for kernel - ConMemCache_mem
		status = clSetKernelArg(
			kernel[1], 
			0, 
			sizeof(cl_mem), 
			(void *)&ConMemCache_mem);
		CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (ConMemCache_mem)");
		// second argument for kernel - out_ConMemCache_mem
		status = clSetKernelArg(
			kernel[1], 
			1, 
			sizeof(cl_mem), 
			(void *)&out_ConMemCache_mem);
		CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (out_ConMemCache_mem)");
		// third argument for kernel - length
		status = clSetKernelArg(
			kernel[1], 
			2, 
			sizeof(cl_int), 
			(void *)&length);
		CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (length)");

		double eTime_ConMemCache_max = 0.0;
		double eTime_ConMemCache_avg = 0.0;
		double eTime_ConMemCache_min = MAX_TIME;

		cl_event  event_ConMemCache;

		globalThreads = 32768/2;
		localThreads = 256;
		double time=0;
		int i;
		for (i = 0; i < iterations; i++)
		{
			status=clEnqueueNDRangeKernel(commandQueue,
				kernel[1],
				1, 
				NULL,
				&globalThreads,
				&localThreads,
				0, 
				NULL,
				&event_ConMemCache);

			CHECK_OPENCL_ERROR(status, "clEnqueueNDRangeKernel failed.");
			status=clWaitForEvents(1, &event_ConMemCache);
			CHECK_OPENCL_ERROR(status, "clWaitForEvents failed. ((event_ConMemCache))"); 
			if(i>9){
				double eTime_ConMemCache = executionTime(event_ConMemCache);

				if(eTime_ConMemCache_max < eTime_ConMemCache) {
					eTime_ConMemCache_max = eTime_ConMemCache;
				}

				if(eTime_ConMemCache_min > eTime_ConMemCache) {
					eTime_ConMemCache_min = eTime_ConMemCache;
				}
				eTime_ConMemCache_avg += eTime_ConMemCache;
			}
			time=time+executionTime(event_ConMemCache);
		}

		std::cout <<stride << "\t";
#ifdef profile

		if(i == iterations - 1) {
			int* Output = (int *)malloc(sizeof(int));
			status = clEnqueueReadBuffer(commandQueue, out_ConMemCache_mem, CL_TRUE, 0, sizeof(int), 
				Output, 0, NULL, NULL);
			CHECK_OPENCL_ERROR(status, "clEnqueueReadBuffer failed. ((out_ConMemCache_mem))"); 
			printf("%d\t", Output[0]);
			free(Output);
		}
#endif
		//std::cout <<eTime_ConMemCache_avg /((iterations * 512))<<std::endl;
		double bdwth = ((double)globalThreads*sizeof(int)*512*iterations)/time;//eTime_ConMemCache_avg;
		printf("%.2lf\n",bdwth);
		clReleaseMemObject(ConMemCache_mem);
		clReleaseMemObject(out_ConMemCache_mem);
		clReleaseEvent(event_ConMemCache);
	}
	free(input);
	return SDK_SUCCESS;
}

int 
MemoryCache::runCLGlobalKernels()
{
	cl_int status = 0;
	int stride;
	/********************** global cache ****************************/
	std::cout << "-----------------------------------------" << std::endl;
	std::cout << "Global Memory Cache Test....." << std::endl;
   
	length = 256 * 256;
	input = (int *)malloc((length + 1) * sizeof(int));
	CHECK_ALLOCATION(input, "Failed to allocate host memory. (input)");
	input[length] = 0;

	std::cout << "Stride\tTime(ns)" << std::endl;
	for(stride = 1; stride <= 256; stride++)
	{
		for(int i = 0; i < length; i++) 
			input[i] = ((i + stride) % length);
		

		cl_mem GlobalMemCache_mem = clCreateBuffer(context, CL_MEM_READ_WRITE, (length+1)*sizeof(int), NULL, &status);
		CHECK_OPENCL_ERROR(status, "clCreateBuffer failed. (GlobalMemCache_mem)");

		status = clEnqueueWriteBuffer(commandQueue, GlobalMemCache_mem, CL_FALSE, 
			0,(length+1)*sizeof(int), (int*)input, 0, NULL, NULL);
		CHECK_OPENCL_ERROR(status, "clEnqueueWriteBuffer failed. (input_readGlobalOffset_mem)");

		// Set appropriate arguments to the kernel
		// first argument for kernel - input_readGlobalOffset_mem
		status = clSetKernelArg(
			kernel[0], 
			0, 
			sizeof(cl_mem), 
			(void *)&GlobalMemCache_mem);
		CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (input_readGlobalOffset_mem)");
		// second argument for kernel - length
		status = clSetKernelArg(
			kernel[0], 
			1, 
			sizeof(cl_int), 
			(void *)&length);
		CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (length)");
		
		double eTime_GlobalMemCache_max = 0.0;
		double eTime_GlobalMemCache_avg = 0.0;
		double eTime_GlobalMemCache_min = MAX_TIME;
		
		cl_event  event_GlobalMemCache;

		globalThreads = 1;
		localThreads = 1;

		for (int i = 0; i < iterations; i++)
		{
			status=clEnqueueNDRangeKernel(commandQueue,
				kernel[0],
				1, 
				NULL,
				&globalThreads,
				&localThreads,
				0, 
				NULL,
				&event_GlobalMemCache);
			CHECK_OPENCL_ERROR(status, "clEnqueueNDRangeKernel failed.");

			status=clWaitForEvents(1, &event_GlobalMemCache);
			CHECK_OPENCL_ERROR(status, "clWaitForEvents failed. ((event_GlobalMemCache))"); 

			double eTime_GlobalMemCache = executionTime(event_GlobalMemCache);

			if(eTime_GlobalMemCache_max < eTime_GlobalMemCache) { 
				eTime_GlobalMemCache_max = eTime_GlobalMemCache;
			}

			if(eTime_GlobalMemCache_min > eTime_GlobalMemCache) {
				eTime_GlobalMemCache_min = eTime_GlobalMemCache;
			}
			eTime_GlobalMemCache_avg += eTime_GlobalMemCache;
		}
		std::cout <<stride << "\t";
		std::cout <<eTime_GlobalMemCache_avg /((iterations * 512))<<std::endl;	
		clReleaseMemObject(GlobalMemCache_mem);
		clReleaseEvent(event_GlobalMemCache);
	}
	free(input);
    return SDK_SUCCESS;
}

int 
MemoryCache::runCLLocalKernels()
{
	cl_int status = 0;
	int stride;
	/************************** Local cache ****************************/
	std::cout << "-----------------------------------------" << std::endl;
	std::cout << "Local Memory Cache Test....." << std::endl;

	length = 1 * 1024;
	input = (int *)malloc((length + 1) * sizeof(int));
	CHECK_ALLOCATION(input, "Failed to allocate host memory. (input)");
	input[length] = 0;
	std::cout << "Stride\t" ;
#ifdef profile
	std::cout << "Out\t";
#endif
	std::cout << "Time(ns)" << std::endl;
	for(stride = 1; stride <= 256; stride++)
	{
		for(int i = 0; i < length; i++) 
			input[i] = ((i + stride) % length);


		cl_mem LocalMemCache_mem = clCreateBuffer(context, CL_MEM_READ_WRITE, (length+1)*sizeof(int), NULL, &status);
		CHECK_OPENCL_ERROR(status, "clCreateBuffer failed. (GlobalMemCache_mem)");

		status = clEnqueueWriteBuffer(commandQueue, LocalMemCache_mem, CL_FALSE, 
			0,(length+1)*sizeof(int), (int*)input, 0, NULL, NULL);
		CHECK_OPENCL_ERROR(status, "clEnqueueWriteBuffer failed. (LocalMemCache_mem)");

		// Set appropriate arguments to the kernel
		// first argument for kernel - LocalMemCache_mem
		status = clSetKernelArg(
			kernel[2], 
			0, 
			sizeof(cl_mem), 
			(void *)&LocalMemCache_mem);
		CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (input_readGlobalOffset_mem)");
		// second argument for kernel - length
		status = clSetKernelArg(
			kernel[2], 
			1, 
			sizeof(cl_int), 
			(void *)&length);
		CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (length)");

		double eTime_LocalMemCache_max = 0.0;
		double eTime_LocalMemCache_avg = 0.0;
		double eTime_LocalMemCache_min = MAX_TIME;
		cl_event  event_LocalMemCache;

		globalThreads = 512;
		localThreads = 256; //6850��512����
		int i;
		for ( i = 0; i < iterations; i++)
		{
			status=clEnqueueNDRangeKernel(commandQueue,
				kernel[2],
				1, 
				NULL,
				&globalThreads,
				&localThreads,
				0, 
				NULL,
				&event_LocalMemCache);
			CHECK_OPENCL_ERROR(status, "clEnqueueNDRangeKernel failed.");

			status=clWaitForEvents(1, &event_LocalMemCache);
			CHECK_OPENCL_ERROR(status, "clWaitForEvents failed. ((event_GlobalMemCache))"); 

			double eTime_LocalMemCache = executionTime(event_LocalMemCache);

			if(eTime_LocalMemCache_max < eTime_LocalMemCache) { 
				eTime_LocalMemCache_max = eTime_LocalMemCache;
			}

			if(eTime_LocalMemCache_min > eTime_LocalMemCache) {
				eTime_LocalMemCache_min = eTime_LocalMemCache;
			}
			eTime_LocalMemCache_avg += eTime_LocalMemCache;
		}
		std::cout << stride << "\t";
#ifdef profile

		if(i == iterations - 1) {
			int* Output = (int *)malloc((length + 1)  * sizeof(int));
			status = clEnqueueReadBuffer(commandQueue, LocalMemCache_mem, CL_TRUE, 0, (length + 1)* sizeof(int), 
				Output, 0, NULL, NULL);
			CHECK_OPENCL_ERROR(status, "clEnqueueReadBuffer failed. (LocalMemCache_mem)");

			FILE* out = fopen("LocalMemCache_out.dat", "w");

			for(int i = 0; i < (length + 1); i++){
				if( i!=0 && i%8 == 0)
					fprintf(out, "\n");
				fprintf(out, "%d\t", Output[i]);
			}
			printf("%d\t", Output[length]);
			fclose(out);
			free(Output);
		}
#endif

		std::cout <<eTime_LocalMemCache_avg /((iterations * 512))<<std::endl;	
		clReleaseMemObject(LocalMemCache_mem);
		clReleaseEvent(event_LocalMemCache);
	}
	free(input);

	return SDK_SUCCESS;
}



int 
MemoryCache::run()
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

	if ( (mKind.compare("all") == 0) || (mKind.compare("constant") == 0) )
	{
		if (runCLConstantKernels() != SDK_SUCCESS)
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
MemoryCache::cleanup()
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
MemoryCache::verifyResults()
{
	return SDK_SUCCESS;
}

void 
MemoryCache::printStats()
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

	MemoryCache clMemoryCache("GpuCoreTest benchmark");
	
	if (clMemoryCache.initialize() != SDK_SUCCESS)
		return SDK_FAILURE;

	if(clMemoryCache.parseCommandLine(argc, argv) != SDK_SUCCESS)
		return SDK_FAILURE;

	status = clMemoryCache.setup();
	if(status != SDK_SUCCESS)
	{
		if(status == SDK_EXPECTED_FAILURE)
			return SDK_SUCCESS;

		return SDK_FAILURE;
	}

	if(clMemoryCache.run()!=SDK_SUCCESS)
		return SDK_FAILURE;

	if(clMemoryCache.verifyResults()!=SDK_SUCCESS)
		return SDK_FAILURE;

	if(clMemoryCache.cleanup()!=SDK_SUCCESS)
		return SDK_FAILURE;

	clMemoryCache.printStats();

	return SDK_SUCCESS;
}
