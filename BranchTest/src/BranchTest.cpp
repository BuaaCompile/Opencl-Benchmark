/**********************************************************************
Copyright (c) 2014,BUAA COMPILER LAB;
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
- Neither the name of the BUAA COMPILER LAB; nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
********************************************************************/
#include "BranchTest.hpp"
#include <stdio.h>
#include <stdlib.h>
int 
Branch::initialize()
{
	// Call base class Initialize to get default configuration
	if(this->Benchmark::initialize() != SDK_SUCCESS)
		return SDK_FAILURE;

	streamsdk::Option* opt_n = new streamsdk::Option;
	CHECK_ALLOCATION(opt_n, "Memory Allocation failed (opt_n)");

	opt_n->_sVersion = "N";
	opt_n->_lVersion = "";
	opt_n->_description = "Number of iterations for kernel execution";
	opt_n->_type = streamsdk::CA_ARG_INT;
	opt_n->_value = &iterations;

	sampleArgs->AddOption(opt_n);
	delete opt_n;

	streamsdk::Option* opt_gws = new streamsdk::Option;
	CHECK_ALLOCATION(opt_gws, "Memory Allocation failed (opt_gws)");

	opt_gws->_sVersion = "G";
	opt_gws->_lVersion = "GWS";
	opt_gws->_description = "Specify the value of GlobalWorkSize, default = 65536";
	opt_gws->_type = streamsdk::CA_ARG_INT;
	opt_gws->_value = &globalThreads;

	sampleArgs->AddOption(opt_gws);
	delete opt_gws;

	streamsdk::Option* opt_lws = new streamsdk::Option;
	CHECK_ALLOCATION(opt_lws, "Memory Allocation failed (opt_lws)");

	opt_lws->_sVersion = "L";
	opt_lws->_lVersion = "LWS";
	opt_lws->_description = "Specify the value of LocalWorkSize, default = GROUP_SIZE";
	opt_lws->_type = streamsdk::CA_ARG_INT;
	opt_lws->_value = &localThreads;

	sampleArgs->AddOption(opt_lws);
	delete opt_lws;

	return SDK_SUCCESS;
	
}

int
Branch::setupCL(void)
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

	outNonBranchBuffer = clCreateBuffer(
		context, 
		CL_MEM_READ_WRITE, 
		globalThreads * sizeof(cl_int), 
		NULL, 
		&status);
	CHECK_OPENCL_ERROR(status, "clCreateBuffer failed. (outNonBranchBuffer)");

	incnumBuffer = clCreateBuffer(
		context, 
		CL_MEM_READ_WRITE, 
		sizeof(cl_int), 
		NULL, 
		&status);
	CHECK_OPENCL_ERROR(status, "clCreateBuffer failed. (incnumBuffer)");

    // create a CL program using the kernel source
    streamsdk::buildProgramData buildData;
    buildData.kernelName = std::string("branch.cl");
    buildData.devices = devices;
    buildData.deviceId = deviceId;
    buildData.flagsStr = std::string("");
    if(isLoadBinaryEnabled())
        buildData.binaryName = std::string(loadBinary.c_str());

    if(isComplierFlagsSpecified())
        buildData.flagsFileName = std::string(flags.c_str());

    retValue = sampleCommon->buildOpenCLProgram(program, context, buildData);
    CHECK_ERROR(retValue, SDK_SUCCESS, "sampleCommon::buildOpenCLProgram() failed");
 
    // Create the cKernel_non_branch
    kernel[0] = clCreateKernel(program, "non_branch", &status);
    CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(non_branch)");
 
    // Create the cKernel_with_branch
    kernel[1] = clCreateKernel(program, "with_branch4", &status);
    CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(with_branch)");

    // Create the cKernel_with_branch
    kernel[2] = clCreateKernel(program, "with_branch16", &status);
    CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(with_branch)");

    // Create the cKernel_with_branch
    kernel[3] = clCreateKernel(program, "with_branch32", &status);
    CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(with_branch)");



    return SDK_SUCCESS;
}

int 
Branch::setup()
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
Branch::executionTime(cl_event &event)
{
	cl_ulong start, end;
	cl_int status = 0;

	status  = clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end, NULL);
	status |= clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start, NULL);

	CHECK_OPENCL_ERROR(status, "clGetEventProfilingInfo failed. (event)");

	return (double)1.0e-6*(end - start); // convert nanoseconds to min seconds on return
}

int 
Branch::runCLKernels(int iter)
{
    cl_int status = 0;

    // Set required input
    cl_event writeEvt;
	int hnum[] = {0};
	status = clEnqueueWriteBuffer(
		commandQueue,
		incnumBuffer, 
		CL_FALSE, 
		0, 
		sizeof(int), 
		(int*)hnum, 
		0, 
		NULL, 
		&writeEvt);
	CHECK_OPENCL_ERROR(status, "clEnqueueWriteBuffer failed. (incnumBuffer)");

    status = clFlush(commandQueue);
    CHECK_OPENCL_ERROR(status, "clFlush failed.");

    status = sampleCommon->waitForEventAndRelease(&writeEvt);
    CHECK_ERROR(status, SDK_SUCCESS, "WaitForEventAndRelease(writeEvt) Failed");

    // first argument for kernel[0] - outNonBranchBuffer
	status = clSetKernelArg(
					kernel[0], 
					0, 
					sizeof(cl_mem), 
					(void *)&outNonBranchBuffer);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (outNonBranchBuffer)");

    cl_mem outWithBranchBuffer4 = clCreateBuffer(
		context, 
		CL_MEM_READ_WRITE, 
		globalThreads * sizeof(cl_int), 
		NULL, 
		&status);
	CHECK_OPENCL_ERROR(status, "clCreateBuffer failed. (outWithBranchBuffer4)");
    // first argument for kernel[1]- outWithBranch4Buffer
    status = clSetKernelArg(
                    kernel[1], 
                    0, 
                    sizeof(cl_mem), 
                    (void *)&outWithBranchBuffer4);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (outWithBranchBuffer4)");

  cl_mem outWithBranchBuffer16 = clCreateBuffer(
		context, 
		CL_MEM_READ_WRITE, 
		globalThreads * sizeof(cl_int), 
		NULL, 
		&status);
	CHECK_OPENCL_ERROR(status, "clCreateBuffer failed. (outWithBranchBuffer16)");
    // first argument for kernel[2]- outWithBranch16Buffer
    status = clSetKernelArg(
                    kernel[2], 
                    0, 
                    sizeof(cl_mem), 
                    (void *)&outWithBranchBuffer16);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (outWithBranchBuffer16)");

  cl_mem outWithBranchBuffer32 = clCreateBuffer(
		context, 
		CL_MEM_READ_WRITE, 
		globalThreads * sizeof(cl_int), 
		NULL, 
		&status);
	CHECK_OPENCL_ERROR(status, "clCreateBuffer failed. (outWithBranchBuffer32)");
    // first argument for kernel[2]- outWithBranch32Buffer
    status = clSetKernelArg(
                    kernel[2], 
                    0, 
                    sizeof(cl_mem), 
                    (void *)&outWithBranchBuffer32);
    CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (outWithBranchBuffer32)");

/*
	// Run first kernel for iter time(s)
	std::cout << "Kernel null branch:" <<std::endl;
	cl_event event_null_branch;
	double eTime_null_branch_max = 0.0;
	double eTime_null_branch_avg = 0.0;
	double eTime_null_branch_min = MAX_TIME;
	double eTime_null_branch = 0.0;
        for (int i = 0; i < iter; i++)
        {
		status=clEnqueueNDRangeKernel(commandQueue,
					kernel[0],
					1, 
					NULL,
					&globalThreads,
					&localThreads,
					0, 
					NULL,
					&event_null_branch);
		CHECK_OPENCL_ERROR(status, "clEnqueueNDRangeKernel failed.");
   
		//record kernel_none time
		status=clWaitForEvents(1, &event_null_branch);
		CHECK_OPENCL_ERROR(status, "clWaitForEvents failed. ((event_null_branch))");

		eTime_null_branch = executionTime(event_null_branch);

		if(eTime_null_branch_max < eTime_null_branch) {
			eTime_null_branch_max = eTime_null_branch;
		}

		if(eTime_null_branch_min > eTime_null_branch) {
			eTime_null_branch_min = eTime_null_branch;
		}

		eTime_null_branch_avg += eTime_null_branch;
#ifdef profile
		if(i == iter - 1) {
			int* Output = (int *)malloc(globalThreads * sizeof(int));
			status = clEnqueueReadBuffer(commandQueue, outNullBranchBuffer, CL_TRUE, 0, globalThreads* sizeof(int), 
				Output, 0, NULL, NULL);
			CHECK_OPENCL_ERROR(status, "clEnqueueReadBuffer failed. (outNullBranchBuffer)");

			FILE* out = fopen("null_branch_out.dat", "w");

			for(int i = 0; i < globalThreads; i++){
				if( i != 0 && i%8 == 0)
					fprintf(out, "\n");
				fprintf(out, "%d\t", Output[i]);
			}

			fclose(out);
			free(Output);
		}
#endif
	}
	status = clReleaseMemObject(outNullBranchBuffer);
	CHECK_OPENCL_ERROR(status, "clReleaseMemObject failed.(outNullBranchBuffer)");

	printf("\n\neTime_null_branch_avg is %f ms\n", eTime_null_branch_avg/(iter*1.0));	
	printf("\neTime_null_branch_max is %f ms\n", eTime_null_branch_max);	
	printf("\neTime_null_branch_min is %f ms\n\n", eTime_null_branch_min);	
	std::cout << "-------------------------------------------" << std::endl;
*/
	//////////////////////////////
	// Run first kernel for iter time(s)-
	std::cout << "Kernel non branch:" <<std::endl;
	cl_event event_non_branch;
	double eTime_non_branch_max = 0.0;
	double eTime_non_branch_avg = 0.0;
	double eTime_non_branch_min = MAX_TIME;
	double eTime_non_branch = 0.0;
	for (int i = 0; i < iter; i++)
	{
		status=clEnqueueNDRangeKernel(commandQueue,
			kernel[1],
			1, 
			NULL,
			&globalThreads,
			&localThreads,
			0, 
			NULL,
			&event_non_branch);
		CHECK_OPENCL_ERROR(status, "clEnqueueNDRangeKernel failed.");

		//record kernel_none time
		status=clWaitForEvents(1, &event_non_branch);
		CHECK_OPENCL_ERROR(status, "clWaitForEvents failed. ((event_non_branch))");

		eTime_non_branch = executionTime(event_non_branch);

		if(eTime_non_branch_max < eTime_non_branch) {
			eTime_non_branch_max = eTime_non_branch;
		}

		if(eTime_non_branch_min > eTime_non_branch) {
			eTime_non_branch_min = eTime_non_branch;
		}

		eTime_non_branch_avg += eTime_non_branch;
#ifdef profile
		if(i == iter - 1) {
			int* Output = (int *)malloc(globalThreads * sizeof(int));
			status = clEnqueueReadBuffer(commandQueue, outNonBranchBuffer, CL_TRUE, 0, globalThreads* sizeof(int), 
				Output, 0, NULL, NULL);
			CHECK_OPENCL_ERROR(status, "clEnqueueReadBuffer failed. (outNonBranchBuffer)");

			FILE* out = fopen("non_branch_out.dat", "w");

			for(int i = 0; i < globalThreads; i++){
				if( i != 0 && i%8 == 0)
					fprintf(out, "\n");
				fprintf(out, "%d\t", Output[i]);
			}

			fclose(out);
			free(Output);
		}
#endif
	}
	status = clReleaseMemObject(outNonBranchBuffer);
	CHECK_OPENCL_ERROR(status, "clReleaseMemObject failed.(outNonBranchBuffer)");
	printf("\n\neTime_non_branch_avg is %f ms\n", eTime_non_branch_avg/(iter * 1.0));	
	printf("\neTime_non_branch_max is %f ms\n", eTime_non_branch_max);	
	printf("\neTime_non_branch_min is %f ms\n\n", eTime_non_branch_min);
	std::cout << "-------------------------------------------" << std::endl;
	//////////////////////////////
	// Run second kernel for iter time(s)
	std::cout << "Kernel with 4 branch:" <<std::endl;

	cl_event event_with_branch4;
	double eTime_with_branch_max = 0.0;
	double eTime_with_branch_avg = 0.0;
	double eTime_with_branch_min = MAX_TIME;
	double eTime_with_branch = 0.0;
	for (int i = 0; i < iter; i++)
	{
		status=clEnqueueNDRangeKernel(commandQueue,
			kernel[1],
			1, 
			NULL,
			&globalThreads,
			&localThreads,
			0, 
			NULL,
			&event_with_branch4);
		CHECK_OPENCL_ERROR(status, "clEnqueueNDRangeKernel failed.");

		//record kernel_none time
		status=clWaitForEvents(1, &event_with_branch4);
		CHECK_OPENCL_ERROR(status, "clWaitForEvents failed. ((event_with_branch4))");

		eTime_with_branch = executionTime(event_with_branch4);

		if(eTime_with_branch_max < eTime_with_branch) {
			eTime_with_branch_max = eTime_with_branch;
		}

		if(eTime_with_branch_min > eTime_with_branch) {
			eTime_with_branch_min = eTime_with_branch;
		}

		eTime_with_branch_avg += eTime_with_branch;
#ifdef profile
		if(i == iter - 1) {
			int* Output = (int *)malloc(globalThreads * sizeof(int));
			status = clEnqueueReadBuffer(commandQueue, outWithBranchBuffer4, CL_TRUE, 0, globalThreads* sizeof(int), 
				Output, 0, NULL, NULL);
			CHECK_OPENCL_ERROR(status, "clEnqueueReadBuffer failed. (outWithBranchBuffer)");

			FILE* out = fopen("with_branch_out4.dat", "w");

			for(int i = 0; i < globalThreads; i++){
				if( i != 0 && i%8 == 0)
					fprintf(out, "\n");
				fprintf(out, "%d\t", Output[i]);
			}

			fclose(out);
			free(Output);
		}
#endif
	}
	status = clReleaseMemObject(outWithBranchBuffer4);
	CHECK_OPENCL_ERROR(status, "clReleaseMemObject failed.(outWithBranchBuffer4)");
	printf("\n\neTime_with_branch4_avg is %f ms\n", eTime_with_branch_avg/(iter*1.0));	
	printf("\neTime_with_branch4_max is %f ms\n", eTime_with_branch_max);	
	printf("\neTime_with_branch4_min is %f ms\n\n", eTime_with_branch_min);
	std::cout << "-------------------------------------------" << std::endl;
	//////////////////////////////
	// Run third kernel for iter time(s)
	std::cout << "Kernel with 16 branch:" <<std::endl;

	cl_event event_with_branch16;
	eTime_with_branch_max = 0.0;
	eTime_with_branch_avg = 0.0;
	eTime_with_branch_min = MAX_TIME;
	eTime_with_branch = 0.0;
	for (int i = 0; i < iter; i++)
	{
		status=clEnqueueNDRangeKernel(commandQueue,
			kernel[2],
			1, 
			NULL,
			&globalThreads,
			&localThreads,
			0, 
			NULL,
			&event_with_branch16);
		CHECK_OPENCL_ERROR(status, "clEnqueueNDRangeKernel failed.");

		//record kernel_none time
		status=clWaitForEvents(1, &event_with_branch16);
		CHECK_OPENCL_ERROR(status, "clWaitForEvents failed. ((event_with_branch))");

		eTime_with_branch = executionTime(event_with_branch16);

		if(eTime_with_branch_max < eTime_with_branch) {
			eTime_with_branch_max = eTime_with_branch;
		}

		if(eTime_with_branch_min > eTime_with_branch) {
			eTime_with_branch_min = eTime_with_branch;
		}

		eTime_with_branch_avg += eTime_with_branch;
#ifdef profile
		if(i == iter - 1) {
			int* Output = (int *)malloc(globalThreads * sizeof(int));
			status = clEnqueueReadBuffer(commandQueue, outWithBranchBuffer16, CL_TRUE, 0, globalThreads* sizeof(int), 
				Output, 0, NULL, NULL);
			CHECK_OPENCL_ERROR(status, "clEnqueueReadBuffer failed. (outWithBranchBuffer16)");

			FILE* out = fopen("with_branch_out16.dat", "w");

			for(int i = 0; i < globalThreads; i++){
				if( i != 0 && i%8 == 0)
					fprintf(out, "\n");
				fprintf(out, "%d\t", Output[i]);
			}

			fclose(out);
			free(Output);
		}
#endif
	}
	status = clReleaseMemObject(outWithBranchBuffer16);
	CHECK_OPENCL_ERROR(status, "clReleaseMemObject failed.(outWithBranchBuffer16)");
	printf("\n\neTime_with_branch16_avg is %f ms\n", eTime_with_branch_avg/(iter*1.0));	
	printf("\neTime_with_branch16_max is %f ms\n", eTime_with_branch_max);	
	printf("\neTime_with_branch16_min is %f ms\n\n", eTime_with_branch_min);
	std::cout << "-------------------------------------------" << std::endl;
	//////////////////////////////
	// Run forth kernel for iter time(s)
	std::cout << "Kernel with 32 branch:" <<std::endl;

	cl_event event_with_branch32;
	eTime_with_branch_max = 0.0;
	eTime_with_branch_avg = 0.0;
	eTime_with_branch_min = MAX_TIME;
	eTime_with_branch = 0.0;
	for (int i = 0; i < iter; i++)
	{
		status=clEnqueueNDRangeKernel(commandQueue,
			kernel[2],
			1, 
			NULL,
			&globalThreads,
			&localThreads,
			0, 
			NULL,
			&event_with_branch32);
		CHECK_OPENCL_ERROR(status, "clEnqueueNDRangeKernel failed.");

		//record kernel_none time
		status=clWaitForEvents(1, &event_with_branch32);
		CHECK_OPENCL_ERROR(status, "clWaitForEvents failed. ((event_with_branch))");

		eTime_with_branch = executionTime(event_with_branch32);

		if(eTime_with_branch_max < eTime_with_branch) {
			eTime_with_branch_max = eTime_with_branch;
		}

		if(eTime_with_branch_min > eTime_with_branch) {
			eTime_with_branch_min = eTime_with_branch;
		}

		eTime_with_branch_avg += eTime_with_branch;
#ifdef profile
		if(i == iter - 1) {
			int* Output = (int *)malloc(globalThreads * sizeof(int));
			status = clEnqueueReadBuffer(commandQueue, outWithBranchBuffer32, CL_TRUE, 0, globalThreads* sizeof(int), 
				Output, 0, NULL, NULL);
			CHECK_OPENCL_ERROR(status, "clEnqueueReadBuffer failed. (outWithBranchBuffer32)");

			FILE* out = fopen("with_branch_out32.dat", "w");

			for(int i = 0; i < globalThreads; i++){
				if( i != 0 && i%8 == 0)
					fprintf(out, "\n");
				fprintf(out, "%d\t", Output[i]);
			}

			fclose(out);
			free(Output);
		}
#endif
	}
	status = clReleaseMemObject(outWithBranchBuffer32);
	CHECK_OPENCL_ERROR(status, "clReleaseMemObject failed.(outWithBranchBuffer32)");
	printf("\n\neTime_with_branch32_avg is %f ms\n", eTime_with_branch_avg/(iter*1.0));	
	printf("\neTime_with_branch32_max is %f ms\n", eTime_with_branch_max);	
	printf("\neTime_with_branch32_min is %f ms\n\n", eTime_with_branch_min);

    	return SDK_SUCCESS;
}

int 
Branch::run()
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
	std::cout << "Executing kernel for " << iterations 
		<< " iterations" << std::endl;
	std::cout << "-------------------------------------------" << std::endl;

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
Branch::cleanup()
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

	status = clReleaseMemObject(outNullBranchBuffer);
	CHECK_OPENCL_ERROR(status, "clReleaseMemObject failed.(outNullBranchBuffer)");

	status = clReleaseMemObject(outNonBranchBuffer);
	CHECK_OPENCL_ERROR(status, "clReleaseMemObject failed.(outNonBranchBuffer)");

	status = clReleaseMemObject(outWithBranchBuffer);
	CHECK_OPENCL_ERROR(status, "clReleaseMemObject failed.(outWithBranchBuffer)");

	status = clReleaseMemObject(incnumBuffer);
	CHECK_OPENCL_ERROR(status, "clReleaseMemObject failed.(incnumBuffer)");

	status = clReleaseMemObject(outSeqBranchBuffer);
	CHECK_OPENCL_ERROR(status, "clReleaseMemObject failed.(outSeqBranchBuffer)");

	status = clReleaseMemObject(outLidSeqBranchBuffer);
	CHECK_OPENCL_ERROR(status, "clReleaseMemObject failed.(outLidSeqBranchBuffer)");

	status = clReleaseMemObject(outGidSeqBranchBuffer);
	CHECK_OPENCL_ERROR(status, "clReleaseMemObject failed.(outGidSeqBranchBuffer)");

	status = clReleaseCommandQueue(commandQueue);
	CHECK_OPENCL_ERROR(status, "clReleaseCommandQueue failed.(commandQueue)");

	status = clReleaseContext(context);
	CHECK_OPENCL_ERROR(status, "clReleaseContext failed.(context)");

	FREE(devices);
	return SDK_SUCCESS;
}

int 
Branch::verifyResults()
{
	return SDK_SUCCESS;
}

void 
Branch::printStats()
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

	Branch clBranch("BranchTest benchmark");
	
	if (clBranch.initialize() != SDK_SUCCESS)
		return SDK_FAILURE;

	if(clBranch.parseCommandLine(argc, argv) != SDK_SUCCESS)
		return SDK_FAILURE;

	status = clBranch.setup();
	if(status != SDK_SUCCESS)
	{
		if(status == SDK_EXPECTED_FAILURE)
			return SDK_SUCCESS;

		return SDK_FAILURE;
	}

	if(clBranch.run()!=SDK_SUCCESS)
		return SDK_FAILURE;

	if(clBranch.verifyResults()!=SDK_SUCCESS)
		return SDK_FAILURE;

	if(clBranch.cleanup()!=SDK_SUCCESS)
		return SDK_FAILURE;

	clBranch.printStats();

	return SDK_SUCCESS;
}
