/**********************************************************************
Copyright (c) 2014,BUAA COMPILER LAB;
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
- Neither the name of the BUAA COMPILER LAB; nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
********************************************************************/
#include "AtomTest.hpp"
#define profile
int 
Atom::initialize()
{
	// Call base class Initialize to get default configuration
	if(this->Benchmark::initialize() != SDK_SUCCESS)
		return SDK_FAILURE;

	return SDK_SUCCESS;
	
}

int 
Atom::setupAtom()
{
	// Allocate the memory for input array
	input1 = (cl_int*)malloc(12 * sizeof(cl_int));
	CHECK_ALLOCATION(input1, "Allocation failed(input1)");

	input2 = (cl_int*)malloc(10 * sizeof(cl_int));
	CHECK_ALLOCATION(input2, "Allocation failed(input1)");

	input3 = (cl_int*)malloc(sizeof(cl_int));
	CHECK_ALLOCATION(input3, "Allocation failed(input1)");

	input4 = (cl_int*)malloc(sizeof(cl_int));
	CHECK_ALLOCATION(input4, "Allocation failed(input1)");

	input5 = (cl_int*)malloc(sizeof(cl_int));
	CHECK_ALLOCATION(input5, "Allocation failed(input1)");

	input6 = (cl_int*)malloc(sizeof(cl_int));
	CHECK_ALLOCATION(input6, "Allocation failed(input1)");

	// Set the input data 
	memset(input1, 0, (12 * sizeof(cl_int)));
	memset(input2, 0, (10 * sizeof(cl_int)));
	memset(input3, 0, sizeof(cl_int));
	memset(input4, 0, sizeof(cl_int));
	memset(input5, 0, sizeof(cl_int));
	memset(input6, 0, sizeof(cl_int));

	return SDK_SUCCESS;
}

int
Atom::setupCL(void)
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
	
    atomTest1_mem = clCreateBuffer(
		context, 
		CL_MEM_READ_WRITE, 
		12 * sizeof(cl_int), 
		NULL, 
		&status);
	CHECK_OPENCL_ERROR(status, "clCreateBuffer failed. (atomTest1_mem)");

	atomTest2_mem = clCreateBuffer(
		context, 
		CL_MEM_READ_WRITE, 
		10 * sizeof(cl_int), 
		NULL, 
		&status);
	CHECK_OPENCL_ERROR(status, "clCreateBuffer failed. (atomTest2_mem)");

	atomTest3_mem = clCreateBuffer(
		context, 
		CL_MEM_READ_WRITE, 
		sizeof(cl_int), 
		NULL, 
		&status);
	CHECK_OPENCL_ERROR(status, "clCreateBuffer failed. (atomTest3_mem)");

	atomTest4_mem = clCreateBuffer(
		context, 
		CL_MEM_READ_WRITE, 
		sizeof(cl_int), 
		NULL, 
		&status);
	CHECK_OPENCL_ERROR(status, "clCreateBuffer failed. (atomTest4_mem)");

	atomTest5_mem = clCreateBuffer(
		context, 
		CL_MEM_READ_WRITE, 
		sizeof(cl_int), 
		NULL, 
		&status);
	CHECK_OPENCL_ERROR(status, "clCreateBuffer failed. (atomTest5_mem)");

	atomTest6_mem = clCreateBuffer(
		context, 
		CL_MEM_READ_WRITE, 
		sizeof(cl_int), 
		NULL, 
		&status);
	CHECK_OPENCL_ERROR(status, "clCreateBuffer failed. (atomTest6_mem)");

	// Set up data for input array
	cl_event writeEvt1,writeEvt2,writeEvt3,writeEvt4,writeEvt5,writeEvt6;
	status = clEnqueueWriteBuffer(
		commandQueue,
		atomTest1_mem,
		CL_FALSE,
		0,
		12 * sizeof(cl_int),
		input1,
		0,
		NULL,
		&writeEvt1);
	CHECK_OPENCL_ERROR(status, "clEnqueueWriteBuffer(atomTest1_mem) failed..");

	status = clEnqueueWriteBuffer(
		commandQueue,
		atomTest2_mem,
		CL_FALSE,
		0,
		10 * sizeof(cl_int),
		input2,
		0,
		NULL,
		&writeEvt2);
	CHECK_OPENCL_ERROR(status, "clEnqueueWriteBuffer(atomTest2_mem) failed..");

	status = clEnqueueWriteBuffer(
		commandQueue,
		atomTest3_mem,
		CL_FALSE,
		0,
		sizeof(cl_int),
		input3,
		0,
		NULL,
		&writeEvt3);
	CHECK_OPENCL_ERROR(status, "clEnqueueWriteBuffer(atomTest3_mem) failed..");

	status = clEnqueueWriteBuffer(
		commandQueue,
		atomTest4_mem,
		CL_FALSE,
		0,
		sizeof(cl_int),
		input4,
		0,
		NULL,
		&writeEvt4);
	CHECK_OPENCL_ERROR(status, "clEnqueueWriteBuffer(atomTest4_mem) failed..");

	status = clEnqueueWriteBuffer(
		commandQueue,
		atomTest5_mem,
		CL_FALSE,
		0,
		sizeof(cl_int),
		input5,
		0,
		NULL,
		&writeEvt5);
	CHECK_OPENCL_ERROR(status, "clEnqueueWriteBuffer(atomTest5_mem) failed..");

	status = clEnqueueWriteBuffer(
		commandQueue,
		atomTest6_mem,
		CL_FALSE,
		0,
		sizeof(cl_int),
		input6,
		0,
		NULL,
		&writeEvt6);
	CHECK_OPENCL_ERROR(status, "clEnqueueWriteBuffer(atomTest6_mem) failed..");

	status = clFlush(commandQueue);
	CHECK_OPENCL_ERROR(status, "clFlush(commandQueue) failed.");
 
    // create a CL program using the kernel source
    streamsdk::buildProgramData buildData;
    buildData.kernelName = std::string("Atom.cl");
    buildData.devices = devices;
    buildData.deviceId = deviceId;
    buildData.flagsStr = std::string("");
    if(isLoadBinaryEnabled())
        buildData.binaryName = std::string(loadBinary.c_str());

    if(isComplierFlagsSpecified())
        buildData.flagsFileName = std::string(flags.c_str());

    retValue = sampleCommon->buildOpenCLProgram(program, context, buildData);
    CHECK_ERROR(retValue, SDK_SUCCESS, "sampleCommon::buildOpenCLProgram() failed");
     
	// Create the atomTest1
    kernel[0] = clCreateKernel(program, "atomTest1", &status);
    CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(atomTest1)");
 
	// Create the cKernel_non_branch
    kernel[1] = clCreateKernel(program, "atomTest2", &status);
    CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(atomTest2)");
 
    // Create the cKernel_with_branch
    kernel[2] = clCreateKernel(program, "atomTest3", &status);
    CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(atomTest3)");
 
    // Create the cKernel_seq_branch
    kernel[3] = clCreateKernel(program, "atomTest4", &status);
    CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(atomTest4)");

    // Create the atomTest5
    kernel[4] = clCreateKernel(program, "atomTest5", &status);
    CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(atomTest5)");

    // Create the atomTest6
    kernel[5] = clCreateKernel(program, "atomTest6", &status);
    CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(atomTest6)");

    // Wait for event and release event
    status = sampleCommon->waitForEventAndRelease(&writeEvt1);
    CHECK_OPENCL_ERROR(status, "waitForEventAndRelease(writeEvt1) failed.");

    status = sampleCommon->waitForEventAndRelease(&writeEvt2);
    CHECK_OPENCL_ERROR(status, "waitForEventAndRelease(writeEvt2) failed.");

    status = sampleCommon->waitForEventAndRelease(&writeEvt3);
    CHECK_OPENCL_ERROR(status, "waitForEventAndRelease(writeEvt3) failed.");

    status = sampleCommon->waitForEventAndRelease(&writeEvt4);
    CHECK_OPENCL_ERROR(status, "waitForEventAndRelease(writeEvt4) failed.");

    status = sampleCommon->waitForEventAndRelease(&writeEvt5);
    CHECK_OPENCL_ERROR(status, "waitForEventAndRelease(writeEvt5) failed.");

    status = sampleCommon->waitForEventAndRelease(&writeEvt6);
    CHECK_OPENCL_ERROR(status, "waitForEventAndRelease(writeEvt6) failed.");

    return SDK_SUCCESS;
}

int 
Atom::setup()
{
	//Setup application data
	if(setupAtom() != SDK_SUCCESS)
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
Atom::executionTime(cl_event &event)
{
	cl_ulong start, end;
	cl_int status = 0;

	status  = clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end, NULL);
	status |= clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start, NULL);

	CHECK_OPENCL_ERROR(status, "clGetEventProfilingInfo failed. (event)");

	return (double)1.0e-6*(end - start); // convert nanoseconds to min seconds on return
}

int 
Atom::runCLKernels(int iter)
{
    cl_int status = 0;

	globalThreads = 1024;
	localThreads = 128;

    // Set appropriate arguments to the kernel

    // first argument for kernel[0] - atomTest1_mem
    status = clSetKernelArg(
                    kernel[0], 
                    0, 
                    sizeof(cl_mem), 
                    (void *)&atomTest1_mem);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (atomTest1_mem)");

    // first argument for kernel[1] - atomTest2_mem
	status = clSetKernelArg(
					kernel[1], 
					0, 
					sizeof(cl_mem), 
					(void *)&atomTest2_mem);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (atomTest2_mem)");

    // first argument for kernel[2]- atomTest3_mem
    status = clSetKernelArg(
                    kernel[2], 
                    0, 
                    sizeof(cl_mem), 
                    (void *)&atomTest3_mem);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (atomTest3_mem)");

    // first argument for kernel[3] - atomTest4_mem
    status = clSetKernelArg(
                    kernel[3], 
                    0, 
                    sizeof(cl_mem), 
                    (void *)&atomTest4_mem);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (atomTest4_mem)");

    // first argument for kernel[4] - atomTest5_mem
    status = clSetKernelArg(
                    kernel[4], 
                    0, 
                    sizeof(cl_mem), 
                    (void *)&atomTest5_mem);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (atomTest5_mem)");

    // first argument for kernel[3] - atomTest6_mem
    status = clSetKernelArg(
                    kernel[5], 
                    0, 
                    sizeof(cl_mem), 
                    (void *)&atomTest6_mem);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (atomTest6_mem)");

	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "Run Atom test 1..." << std::endl;
	// Run first kernel for iter time(s)
	cl_event runEvt1;
	status=clEnqueueNDRangeKernel(commandQueue,
				kernel[0],
				1, 
				NULL,
				&globalThreads,
				&localThreads,
				0, 
				NULL,
				&runEvt1);
	CHECK_OPENCL_ERROR(status, "clEnqueueNDRangeKernel failed.");
   
	status = sampleCommon->waitForEventAndRelease(&runEvt1);
	CHECK_OPENCL_ERROR(status, "waitForEventAndRelease(writeEvt1) failed.");

	output1 = (int *)malloc(12 * sizeof(int));

	status = clEnqueueReadBuffer(commandQueue, atomTest1_mem, CL_TRUE, 0,  12 * sizeof(int), output1, 0, NULL, NULL);
	CHECK_OPENCL_ERROR(status, "clEnqueueReadBuffer(atomTest1_mem) failed.");

#ifdef profile
	for(int i = 0; i < 12; i++){
		printf("%d\t", output1[i]);
	}
	printf("\n");
#endif

	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "Run Atom test 2..." << std::endl;
	// Run first kernel for iter time(s)
	cl_event runEvt2;
	status=clEnqueueNDRangeKernel(commandQueue,
		kernel[1],
		1, 
		NULL,
		&globalThreads,
		&localThreads,
		0, 
		NULL,
		&runEvt2);
	CHECK_OPENCL_ERROR(status, "clEnqueueNDRangeKernel failed.");

	status = sampleCommon->waitForEventAndRelease(&runEvt2);
	CHECK_OPENCL_ERROR(status, "waitForEventAndRelease(writeEvt1) failed.");

	output2 = (int *)malloc(10 * sizeof(int));

	status = clEnqueueReadBuffer(commandQueue, atomTest2_mem, CL_TRUE, 0,  10 * sizeof(int), output2, 0, NULL, NULL);
	CHECK_OPENCL_ERROR(status, "clEnqueueReadBuffer(atomTest1_mem) failed.");

#ifdef profile
	for(int i = 0; i < 10; i++){
		printf("%d\t", output2[i]);
	}
	printf("\n");
#endif
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "Run Atom test 3..." << std::endl;
	// Run first kernel for iter time(s)
	cl_event runEvt3;
	status=clEnqueueNDRangeKernel(commandQueue,
		kernel[2],
		1, 
		NULL,
		&globalThreads,
		&localThreads,
		0, 
		NULL,
		&runEvt3);
	CHECK_OPENCL_ERROR(status, "clEnqueueNDRangeKernel failed.");

	status = sampleCommon->waitForEventAndRelease(&runEvt3);
	CHECK_OPENCL_ERROR(status, "waitForEventAndRelease(writeEvt1) failed.");

	output3 = (int *)malloc(sizeof(int));

	status = clEnqueueReadBuffer(commandQueue, atomTest1_mem, CL_TRUE, 0,  12 * sizeof(int), output1, 0, NULL, NULL);
	CHECK_OPENCL_ERROR(status, "clEnqueueReadBuffer(atomTest1_mem) failed.");

#ifdef profile
	printf("%d\n", output3[0]);
#endif
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "Run Atom test 4..." << std::endl;
	// Run first kernel for iter time(s)
	cl_event runEvt4;
	status=clEnqueueNDRangeKernel(commandQueue,
		kernel[3],
		1, 
		NULL,
		&globalThreads,
		&localThreads,
		0, 
		NULL,
		&runEvt4);
	CHECK_OPENCL_ERROR(status, "clEnqueueNDRangeKernel failed.");

	status = sampleCommon->waitForEventAndRelease(&runEvt4);
	CHECK_OPENCL_ERROR(status, "waitForEventAndRelease(writeEvt1) failed.");

	output4 = (int *)malloc(sizeof(int));

	status = clEnqueueReadBuffer(commandQueue, atomTest4_mem, CL_TRUE, 0, sizeof(int), output4, 0, NULL, NULL);
	CHECK_OPENCL_ERROR(status, "clEnqueueReadBuffer(atomTest1_mem) failed.");

#ifdef profile
	printf("%d\n", output4[0]);
#endif
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "Run Atom test 5..." << std::endl;
	// Run first kernel for iter time(s)
	cl_event runEvt5;
	status=clEnqueueNDRangeKernel(commandQueue,
		kernel[4],
		1, 
		NULL,
		&globalThreads,
		&localThreads,
		0, 
		NULL,
		&runEvt5);
	CHECK_OPENCL_ERROR(status, "clEnqueueNDRangeKernel failed.");

	status = sampleCommon->waitForEventAndRelease(&runEvt5);
	CHECK_OPENCL_ERROR(status, "waitForEventAndRelease(writeEvt1) failed.");

	output5 = (int *)malloc(sizeof(int));

	status = clEnqueueReadBuffer(commandQueue, atomTest1_mem, CL_TRUE, 0,  sizeof(int), output5, 0, NULL, NULL);
	CHECK_OPENCL_ERROR(status, "clEnqueueReadBuffer(atomTest1_mem) failed.");

#ifdef profile
	printf("%d\n", output5[0]);
#endif
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "Run Atom test 6..." << std::endl;
	// Run first kernel for iter time(s)
	cl_event runEvt6;
	status=clEnqueueNDRangeKernel(commandQueue,
		kernel[5],
		1, 
		NULL,
		&globalThreads,
		&localThreads,
		0, 
		NULL,
		&runEvt6);
	CHECK_OPENCL_ERROR(status, "clEnqueueNDRangeKernel failed.");

	status = sampleCommon->waitForEventAndRelease(&runEvt6);
	CHECK_OPENCL_ERROR(status, "waitForEventAndRelease(writeEvt1) failed.");

	output6 = (int *)malloc(sizeof(int));

	status = clEnqueueReadBuffer(commandQueue, atomTest6_mem, CL_TRUE, 0, sizeof(int), output6, 0, NULL, NULL);
	CHECK_OPENCL_ERROR(status, "clEnqueueReadBuffer(atomTest1_mem) failed.");

#ifdef profile
	printf("%d\n", output6[0]);
#endif
	std::cout << "-------------------------------------------" << std::endl;
    return SDK_SUCCESS;
}

int 
Atom::run()
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

	// Arguments are set and execution call is enqueued on command buffer 
	if(runCLKernels(iterations) != SDK_SUCCESS)
		return SDK_FAILURE;

	sampleCommon->stopTimer(timer);
	totalKernelTime = (double)(sampleCommon->readTimer(timer)) / iterations;

	//if(!quiet) {
	//	sampleCommon->printArray<cl_float>("Output", eigenIntervals[1], 2*length, 1);
	//}

	return SDK_SUCCESS;
}

int 
Atom::cleanup()
{
	// Releases OpenCL resources (Context, Memory etc.)
	cl_int status;

	for(cl_uint i=0; i < NUM_KERNELS; ++i)
	{
		status = clReleaseKernel(kernel[i]);
		CHECK_OPENCL_ERROR(status, "clReleaseKernel failed.");
	}

	status = clReleaseProgram(program);
	CHECK_OPENCL_ERROR(status, "clReleaseProgram failed.(program)");

	status = clReleaseMemObject(atomTest1_mem);
	CHECK_OPENCL_ERROR(status, "clReleaseMemObject failed.(outNullBranchBuffer)");

	status = clReleaseMemObject(atomTest2_mem);
	CHECK_OPENCL_ERROR(status, "clReleaseMemObject failed.(outNonBranchBuffer)");

	status = clReleaseMemObject(atomTest3_mem);
	CHECK_OPENCL_ERROR(status, "clReleaseMemObject failed.(outWithBranchBuffer)");

	status = clReleaseMemObject(atomTest4_mem);
	CHECK_OPENCL_ERROR(status, "clReleaseMemObject failed.(incnumBuffer)");

	status = clReleaseMemObject(atomTest5_mem);
	CHECK_OPENCL_ERROR(status, "clReleaseMemObject failed.(outSeqBranchBuffer)");

	status = clReleaseMemObject(atomTest6_mem);
	CHECK_OPENCL_ERROR(status, "clReleaseMemObject failed.(outLidSeqBranchBuffer)");

	status = clReleaseCommandQueue(commandQueue);
	CHECK_OPENCL_ERROR(status, "clReleaseCommandQueue failed.(commandQueue)");

	status = clReleaseContext(context);
	CHECK_OPENCL_ERROR(status, "clReleaseContext failed.(context)");

	FREE(devices);

	free(input1);
	free(input2);
	free(input3);
	free(input4);
	free(input5);
	free(input6);
	free(output1);
	free(output2);
	free(output3);
	free(output4);
	free(output5);
	free(output6);
	return SDK_SUCCESS;
}

int 
Atom::verifyResults()
{
	return SDK_SUCCESS;
}

void 
Atom::printStats()
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

	Atom clAtom("AtomTest benchmark");
	
	if (clAtom.initialize() != SDK_SUCCESS)
		return SDK_FAILURE;

	if(clAtom.parseCommandLine(argc, argv) != SDK_SUCCESS)
		return SDK_FAILURE;

	status = clAtom.setup();
	if(status != SDK_SUCCESS)
	{
		if(status == SDK_EXPECTED_FAILURE)
			return SDK_SUCCESS;

		return SDK_FAILURE;
	}

	if(clAtom.run()!=SDK_SUCCESS)
		return SDK_FAILURE;

	if(clAtom.verifyResults()!=SDK_SUCCESS)
		return SDK_FAILURE;

	if(clAtom.cleanup()!=SDK_SUCCESS)
		return SDK_FAILURE;

	clAtom.printStats();

	return SDK_SUCCESS;
}
