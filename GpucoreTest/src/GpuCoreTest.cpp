/**********************************************************************
Copyright (c) 2014,BUAA COMPILER LAB;
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
- Neither the name of the BUAA COMPILER LAB; nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
********************************************************************/
#include "GpuCoreTest.hpp"

int GpuCore::initialize()
{
	// Call base class Initialize to get default configuration
	if(this->Benchmark::initialize() != SDK_SUCCESS)
		return SDK_FAILURE;

	streamsdk::Option* opt_gws = new streamsdk::Option;
	CHECK_ALLOCATION(opt_gws, "Memory Allocation failed (opt_gws)");

	opt_gws->_sVersion = "G";
	opt_gws->_lVersion = "GWS";
	opt_gws->_description = "Specify the value of GlobalWorkSize, default = 65536";
	opt_gws->_type = streamsdk::CA_ARG_INT;
	opt_gws->_value = &globalThreads;

	sampleArgs->AddOption(opt_gws);
	delete opt_gws;

	streamsdk::Option* opt_NumMin = new streamsdk::Option;
	CHECK_ALLOCATION(opt_NumMin, "Memory Allocation failed (opt_NumMin)");

	opt_NumMin->_sVersion = "";
	opt_NumMin->_lVersion = "NumMin";
	opt_NumMin->_description = "Define the minimum number of WorkGroup";
	opt_NumMin->_type = streamsdk::CA_ARG_INT;
	opt_NumMin->_value = &numMin;

	sampleArgs->AddOption(opt_NumMin);
	delete opt_NumMin;

	streamsdk::Option* opt_NumMax = new streamsdk::Option;
	CHECK_ALLOCATION(opt_NumMax, "Memory Allocation failed (opt_NumMax)");

	opt_NumMax->_sVersion = "";
	opt_NumMax->_lVersion = "NumMax";
	opt_NumMax->_description = "Define the maximum number of WorkGroup";
	opt_NumMax->_type = streamsdk::CA_ARG_INT;
	opt_NumMax->_value = &numMin;

	sampleArgs->AddOption(opt_NumMax);
	delete opt_NumMax;

	streamsdk::Option* opt_SizeMin = new streamsdk::Option;
	CHECK_ALLOCATION(opt_SizeMin, "Memory Allocation failed (opt_SizeMin)");

	opt_SizeMin->_sVersion = "";
	opt_SizeMin->_lVersion = "SizeMin";
	opt_SizeMin->_description = "Define the maximum number of WorkGroup";
	opt_SizeMin->_type = streamsdk::CA_ARG_INT;
	opt_SizeMin->_value = &sizeMin;

	sampleArgs->AddOption(opt_SizeMin);
	delete opt_SizeMin;

	streamsdk::Option* opt_SizeMax = new streamsdk::Option;
	CHECK_ALLOCATION(opt_SizeMax, "Memory Allocation failed (opt_SizeMax)");

	opt_SizeMax->_sVersion = "";
	opt_SizeMax->_lVersion = "SizeMax";
	opt_SizeMax->_description = "Define the maximum number of WorkGroup";
	opt_SizeMax->_type = streamsdk::CA_ARG_INT;
	opt_SizeMax->_value = &sizeMax;

	sampleArgs->AddOption(opt_SizeMax);
	delete opt_SizeMax;

	return SDK_SUCCESS;
	
}

int
GpuCore::setupCL(void)
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
      /*  if(isThereGPU() == false)
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
    buildData.kernelName = std::string("GpuCore.cl");
    buildData.devices = devices;
    buildData.deviceId = deviceId;
    buildData.flagsStr = std::string("");
    if(isLoadBinaryEnabled())
        buildData.binaryName = std::string(loadBinary.c_str());

    if(isComplierFlagsSpecified())
        buildData.flagsFileName = std::string(flags.c_str());

    retValue = sampleCommon->buildOpenCLProgram(program, context, buildData);
    CHECK_ERROR(retValue, SDK_SUCCESS, "sampleCommon::buildOpenCLProgram() failed");
     
	// Create the cKernel_null_branch
    kernel = clCreateKernel(program, "gpuCoreTest", &status);
    CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(gpuCoreTest)");
 
    return SDK_SUCCESS;
}

int 
GpuCore::setup()
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
GpuCore::executionTime(cl_event &event)
{
	cl_ulong start, end;
	cl_int status = 0;

	status  = clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end, NULL);
	status |= clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start, NULL);

	CHECK_OPENCL_ERROR(status, "clGetEventProfilingInfo failed. (event)");

	return (double)1.0e-6*(end - start); // convert nanoseconds to min seconds on return
}

int 
GpuCore::runCLKernels(int WorkGroupNums, int WorkGroupSize, int size)
{
    cl_int status = 0;
	cl_uint inputSizeBytes;
	int length = WorkGroupNums * WorkGroupSize;

	// allocate and init memory used by host 
	inputSizeBytes = length * sizeof(cl_float);
	cl_float* srcA = (cl_float *) malloc(inputSizeBytes);
	CHECK_ALLOCATION(srcA, "Failed to allocate host memory. (srcA)/ User failed to allocate host Memory");

	cl_float* srcB = (cl_float *) malloc(inputSizeBytes);
	CHECK_ALLOCATION(srcB, "Failed to allocate host memory. (srcB)/ User failed to allocate host Memory");

	cl_float* dst = (cl_float *) malloc(inputSizeBytes);
	CHECK_ALLOCATION(dst, "Failed to allocate host memory. (dst)/ User failed to allocate host Memory");

	// random initialisation of input
	sampleCommon->fillRandom<cl_float>(srcA, length, 1, 0, 255);
	
  	cl_mem gpuCoreTest1_SrcA = clCreateBuffer(context, CL_MEM_READ_WRITE, length * sizeof(cl_float), NULL, &status); 
  	CHECK_OPENCL_ERROR(status, "clCreateBuffer failed. (gpuCoreTest1_SrcA)");
	
  	cl_mem gpuCoreTest1_SrcB = clCreateBuffer(context, CL_MEM_READ_WRITE, length * sizeof(cl_float), NULL, &status); 
  	CHECK_OPENCL_ERROR(status, "clCreateBuffer failed. (gpuCoreTest1_SrcB)");

  	cl_mem gpuCoreTest1_Dst = clCreateBuffer(context, CL_MEM_READ_WRITE, length * sizeof(cl_float), NULL, &status); 
  	CHECK_OPENCL_ERROR(status, "clCreateBuffer failed. (gpuCoreTest1_Dst)");


    status = clEnqueueWriteBuffer(commandQueue, gpuCoreTest1_SrcA, CL_FALSE, 0, sizeof(cl_float) * length, srcA, 0, NULL, NULL);
	CHECK_OPENCL_ERROR(status, "clEnqueueWriteBuffer failed. (gpuCoreTest1_SrcA)");

    status |= clEnqueueWriteBuffer(commandQueue, gpuCoreTest1_SrcB, CL_FALSE, 0, sizeof(cl_float) * length, srcB, 0, NULL, NULL);
    CHECK_OPENCL_ERROR(status, "clEnqueueWriteBuffer failed. (gpuCoreTest1_SrcB)");

	// Set appropriate arguments to the kernel

	// first argument for kernel - gpuCoreTest1_SrcA
	status = clSetKernelArg(
		kernel, 
		0, 
		sizeof(cl_mem), 
		(void *)&gpuCoreTest1_SrcA);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (gpuCoreTest1_SrcA)");
	// second argument for kernel - gpuCoreTest1_SrcA
	status = clSetKernelArg(
		kernel, 
		1, 
		sizeof(cl_mem), 
		(void *)&gpuCoreTest1_SrcB);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (gpuCoreTest1_SrcB)");
	// third argument for kernel - gpuCoreTest1_SrcA
	status = clSetKernelArg(
		kernel, 
		2, 
		sizeof(cl_mem), 
		(void *)&gpuCoreTest1_Dst);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (gpuCoreTest1_Dst)");
	// forth argument for kernel - length
	
	status = clSetKernelArg(
		kernel, 
		3, 
		sizeof(cl_int), 
		(void *)&size);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (gpuCoreTest1_SrcA)");


	size_t szGpuCore_GlobalWorkSize = size;
	cl_event event_GpuCore1;	

	status=clEnqueueNDRangeKernel(commandQueue,
		kernel,
		1, 
		NULL,
		&szGpuCore_GlobalWorkSize,
		NULL,
		0, 
		NULL,
		&event_GpuCore1);

	CHECK_OPENCL_ERROR(status, "clEnqueueNDRangeKernel failed.");

    status=clWaitForEvents(1, &event_GpuCore1);
    CHECK_OPENCL_ERROR(status, "clWaitForEvents failed. ((event_null_branch))"); 

    int threadNum = szGpuCore_GlobalWorkSize;
    double eTime_GCore1 = 0.0;
	eTime_GCore1 = executionTime(event_GpuCore1);
	printf("%f ms\n", eTime_GCore1);

	status = clEnqueueReadBuffer(commandQueue, gpuCoreTest1_Dst, CL_TRUE, 0,  length * sizeof(cl_float), dst, 0, NULL, NULL);	
	CHECK_OPENCL_ERROR(status, "clEnqueueReadBuffer failed. ((gpuCoreTest1_Dst))"); 

	free(srcA);
	free(srcB);
	free(dst);

    clReleaseEvent(event_GpuCore1);
    clReleaseMemObject(gpuCoreTest1_SrcA);
    clReleaseMemObject(gpuCoreTest1_SrcB);
    clReleaseMemObject(gpuCoreTest1_Dst);

    return SDK_SUCCESS;
}

int 
GpuCore::run()
{
	int i;
	int WGSize = 1024;
	int WGNums = 64;

	int timer = sampleCommon->createTimer();
	sampleCommon->resetTimer(timer);
	sampleCommon->startTimer(timer);  
	printf("Thread num\tTime\n",i);
	for(i=1;i<=65536;i=i*2){
		printf("%d\t\t",i);
		if(runCLKernels(WGNums, WGSize,i) != SDK_SUCCESS)
			return SDK_FAILURE;
	}	
	sampleCommon->stopTimer(timer);
	totalKernelTime = (double)sampleCommon->readTimer(timer);

	return SDK_SUCCESS;
}

int 
GpuCore::cleanup()
{
	// Releases OpenCL resources (Context, Memory etc.)
	cl_int status;

	status = clReleaseKernel(kernel);
	CHECK_OPENCL_ERROR(status, "clReleaseKernel failed.");

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
GpuCore::verifyResults()
{
	return SDK_SUCCESS;
}

void 
GpuCore::printStats()
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

	GpuCore clGpuCore("GpuCoreTest benchmark");
	
	if (clGpuCore.initialize() != SDK_SUCCESS)
		return SDK_FAILURE;

	if(clGpuCore.parseCommandLine(argc, argv) != SDK_SUCCESS)
		return SDK_FAILURE;

	status = clGpuCore.setup();
	if(status != SDK_SUCCESS)
	{
		if(status == SDK_EXPECTED_FAILURE)
			return SDK_SUCCESS;

		return SDK_FAILURE;
	}

	if(clGpuCore.run()!=SDK_SUCCESS)
		return SDK_FAILURE;

	if(clGpuCore.verifyResults()!=SDK_SUCCESS)
		return SDK_FAILURE;

	if(clGpuCore.cleanup()!=SDK_SUCCESS)
		return SDK_FAILURE;

	clGpuCore.printStats();

	return SDK_SUCCESS;
}
