/**********************************************************************
Copyright (c) 2014,BUAA COMPILER LAB;
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
- Neither the name of the BUAA COMPILER LAB; nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
********************************************************************/
#include "MathBasic.hpp"

// ****************************************************************************
// Method:  oclGetProgBinary
//
// Purpose:
//   Get the binary (PTX) of the program associated with the device
//
// Arguments:
//       cpProgram    OpenCL program
//       cdDevice     device of interest
//       binary       returned code
//       length       length of returned code
//
// Copyright 1993-2013 NVIDIA Corporation
//
// ****************************************************************************
inline void
oclGetProgBinary (cl_program cpProgram, cl_device_id cdDevice, char** binary, size_t* length)
{
    // Grab the number of devices associated witht the program
    cl_uint num_devices;
    clGetProgramInfo(cpProgram, CL_PROGRAM_NUM_DEVICES, sizeof(cl_uint), &num_devices, NULL);

    // Grab the device ids
    cl_device_id* devices = (cl_device_id*) malloc(num_devices * sizeof(cl_device_id));
    clGetProgramInfo(cpProgram, CL_PROGRAM_DEVICES, num_devices * sizeof(cl_device_id), devices, 0);

    // Grab the sizes of the binaries
    size_t* binary_sizes = (size_t*)malloc(num_devices * sizeof(size_t));
    clGetProgramInfo(cpProgram, CL_PROGRAM_BINARY_SIZES, num_devices * sizeof(size_t), binary_sizes, NULL);

    // Now get the binaries
    char** ptx_code = (char**) malloc(num_devices * sizeof(char*));
    for( unsigned int i=0; i<num_devices; ++i) {
        ptx_code[i]= (char*)malloc(binary_sizes[i]);
    }
    clGetProgramInfo(cpProgram, CL_PROGRAM_BINARIES, 0, ptx_code, NULL);

    // Find the index of the device of interest
    unsigned int idx = 0;
    while( idx<num_devices && devices[idx] != cdDevice ) ++idx;

    // If it is associated prepare the result
    if( idx < num_devices )
    {
        *binary = ptx_code[idx];
        *length = binary_sizes[idx];
    }

    // Cleanup
    free( devices );
    free( binary_sizes );
    for( unsigned int i=0; i<num_devices; ++i) {
        if( i != idx ) free(ptx_code[i]);
    }
    free( ptx_code );
}

// ****************************************************************************
// Method:  oclGetFirstDev
//
// Purpose:
//   Gets the id of the first device from the context
//
// Arguments:
//       cxMainContext         OpenCL context
//
// Copyright 1993-2013 NVIDIA Corporation
//
// ****************************************************************************
inline cl_device_id
oclGetFirstDev(cl_context cxMainContext)
{
    size_t szParmDataBytes;
    cl_device_id* cdDevices;

    // get the list of GPU devices associated with context
    clGetContextInfo(cxMainContext, CL_CONTEXT_DEVICES, 0, NULL, &szParmDataBytes);
    cdDevices = (cl_device_id*) malloc(szParmDataBytes);

    clGetContextInfo(cxMainContext, CL_CONTEXT_DEVICES, szParmDataBytes, cdDevices, NULL);

    cl_device_id first = cdDevices[0];
    free(cdDevices);

    return first;
}


// ****************************************************************************
// Method:  dumpPTXCode
//
// Purpose:
//
//
// Arguments:
//   ctx          context
//   prg          program
//   name         file name prefix to output to
//
// Programmer:  Gabriel Marin
// Creation:    July 14, 2009
//
// ****************************************************************************
inline bool
dumpPTXCode (cl_context ctx, cl_program prog, const char *name)
{
    std::cout << "Dumping the PTX code" << std::endl;
    size_t ptx_length;
    char* ptx_code;
    char buf[64];
    oclGetProgBinary (prog, oclGetFirstDev(ctx), &ptx_code, &ptx_length);

    FILE* ptxFile = NULL;
    sprintf (buf, "%.59s.ptx", name);
#ifdef WIN32
    fopen_s (&ptxFile, buf, "w");
#else
    ptxFile = fopen (buf,"w");
#endif
    if (ptxFile)
    {
        fwrite (ptx_code, ptx_length, 1, ptxFile);
        fclose (ptxFile);
    }
    free (ptx_code);
    return (ptx_code!=0);
}



int MathBenchmark::initialize() {
	// Call base class Initialize to get default configuration
	if (this->Benchmark::initialize() != SDK_SUCCESS)
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

	streamsdk::Option* opt_f = new streamsdk::Option;
	CHECK_ALLOCATION(opt_f, "Memory Allocation failed (opt_f)");

	opt_f->_sVersion = "F";
	opt_f->_lVersion = "F";
	opt_f->_description = "Number of iterations in each kernel";
	opt_f->_type = streamsdk::CA_ARG_INT;
	opt_f->_value = &repeat;

	sampleArgs->AddOption(opt_f);
	delete opt_f;

	streamsdk::Option* opt_gws = new streamsdk::Option;
	CHECK_ALLOCATION(opt_gws, "Memory Allocation failed (opt_gws)");

	opt_gws->_sVersion = "";
	opt_gws->_lVersion = "GWS";
	opt_gws->_description = "Specify the GlobalWorkSize";
	opt_gws->_type = streamsdk::CA_ARG_INT;
	opt_gws->_value = &globalThreads;

	sampleArgs->AddOption(opt_gws);
	delete opt_gws;

	streamsdk::Option* opt_lws = new streamsdk::Option;
	CHECK_ALLOCATION(opt_lws, "Memory Allocation failed (opt_lws)");

	opt_lws->_sVersion = "";
	opt_lws->_lVersion = "LWS";
	opt_lws->_description = "Specify the localThreads";
	opt_lws->_type = streamsdk::CA_ARG_INT;
	opt_lws->_value = &localThreads;

	sampleArgs->AddOption(opt_lws);
	delete opt_lws;

	streamsdk::Option* opt_kernel = new streamsdk::Option;
	CHECK_ALLOCATION(opt_kernel, "Memory Allocation failed (opt_lws)");

	opt_kernel->_sVersion = "K";
	opt_kernel->_lVersion = "K";
	opt_kernel->_description = "Specify the kernel want to execute";
	opt_kernel->_type = streamsdk::CA_ARG_STRING;
	opt_kernel->_value = &kernelname;

	sampleArgs->AddOption(opt_kernel);
	delete opt_kernel;

	streamsdk::Option* opt_vector = new streamsdk::Option;
	CHECK_ALLOCATION(opt_vector, "Memory Allocation failed (opt_vector)");

	opt_vector->_sVersion = "";
	opt_vector->_lVersion = "v";
	opt_vector->_description = "Specify the kernel vectorsize want to execute[1|2|4|8|16]";
	opt_vector->_type = streamsdk::CA_ARG_INT;
	opt_vector->_value = &vectorSize;

	sampleArgs->AddOption(opt_vector);
	delete opt_vector;
	return SDK_SUCCESS;

}

int MathBenchmark::setupMemory(void) {
	unsigned int memSize = 64 * 1024 * 1024; //default
	length = memSize / sizeof(float);
	cl_uint size = length * sizeof(cl_float);

	// Allocate memory 
	input = (cl_float*) malloc(size);
	CHECK_ALLOCATION(input, "Failed to allocate host memory. (input)");

	// random initialisation of input
	sampleCommon->fillRandom<cl_float>(input, length, 1, 0, 32);

	return SDK_SUCCESS;

}

int MathBenchmark::setupCL(void) {
	cl_int status = 0;
	cl_device_type dType;

	if (deviceType.compare("cpu") == 0) {
		dType = CL_DEVICE_TYPE_CPU;
	} else //deviceType = "gpu"
	{
		dType = CL_DEVICE_TYPE_GPU;
		if (isThereGPU() == false) {
			std::cout << "GPU not found. Falling back to CPU device"
					<< std::endl;
			dType = CL_DEVICE_TYPE_CPU;
		}
	}

	/*
	 * Have a look at the available platforms and pick either
	 * the AMD one if available or a reasonable default.
	 */

	cl_platform_id platform = NULL;
	int retValue = sampleCommon->getPlatform(platform, platformId,
			isPlatformEnabled());
	CHECK_ERROR(retValue, SDK_SUCCESS, "sampleCommon::getPlatform() failed");

	// Display available devices.
	retValue = sampleCommon->displayDevices(platform, dType);
	CHECK_ERROR(retValue, SDK_SUCCESS, "sampleCommon::displayDevices() failed");

	/*
	 * If we could find our platform, use it. Otherwise use just available platform.
	 */

	cl_context_properties cps[3] = { CL_CONTEXT_PLATFORM,
			(cl_context_properties) platform, 0 };

	context = clCreateContextFromType(cps, dType, NULL, NULL, &status);
	CHECK_OPENCL_ERROR(status, "clCreateContextFromType failed.");
	
	// getting device on which to run the sample
	status = sampleCommon->getDevices(context, &devices, deviceId,
			isDeviceIdEnabled());
	CHECK_ERROR(status, SDK_SUCCESS, "sampleCommon::getDevices() failed");
	
	//Set device info of given cl_device_id
	retValue = deviceInfo.setDeviceInfo(devices[deviceId]);
	CHECK_ERROR(retValue, SDK_SUCCESS, "SDKDeviceInfo::setDeviceInfo() failed");

	maxWorkGroup = deviceInfo.maxWorkGroupSize;
	max_mem_alloc_size = deviceInfo.maxMemAllocSize;
	while (maxMemSize <= (unsigned int) (max_mem_alloc_size)) {
		maxMemSize *= 2;
	}
	maxMemSize /= 2;

	if (maxMemSize > 134217728 && dType == CL_DEVICE_TYPE_CPU) {
		maxMemSize = 134217728;
	}

	std::cout << "CL_DEVICE_MAX_WORK_GROUP_SIZE:\t" << maxWorkGroup
			<< std::endl;
	std::cout << "MaxMemSize:\t" << maxMemSize / (1024 * 1024) << "MB"
			<< std::endl;
	{
		// The block is to move the declaration of prop closer to its use
		cl_command_queue_properties prop = 0;
		prop |= CL_QUEUE_PROFILING_ENABLE;
		commandQueue = clCreateCommandQueue(context, devices[deviceId], prop,
				&status);
		CHECK_OPENCL_ERROR(status, "clCreateCommandQueue failed.");
	}
	// create a CL program using the kernel source
	streamsdk::buildProgramData buildData;
	buildData.kernelName = std::string("mathoper.cl");
	buildData.devices = devices;
	buildData.deviceId = deviceId;
	buildData.flagsStr = std::string("");
	if (isLoadBinaryEnabled())
		buildData.binaryName = std::string(loadBinary.c_str());

	if (isComplierFlagsSpecified())
		buildData.flagsFileName = std::string(flags.c_str());

	retValue = sampleCommon->buildOpenCLProgram(program, context, buildData);
	CHECK_ERROR(retValue, SDK_SUCCESS,
			"sampleCommon::buildOpenCLProgram() failed");
	
	
    	std::string s;
	std::stringstream acospi_withDD(s);
	acospi_withDD << "kernel_acospi_withDD";
	acospi_withDD << vectorSize;
	//dumpPTXCode(context,program,acospi_withDD.str().c_str());
	// Create the cKermel_kernel_acospi_withDD
	kernel[0]  = clCreateKernel(program, acospi_withDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_acospi_withDD)");

	std::stringstream acospi_withoutDD(s);
	acospi_withoutDD << "kernel_acospi_withoutDD";
	acospi_withoutDD << vectorSize;
	//dumpPTXCode(context,program,acospi_withoutDD.str().c_str());
	// Create the cKermel_kernel_acospi_withoutDD
	kernel[1]  = clCreateKernel(program, acospi_withoutDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_acospi_withoutDD)");

	std::stringstream atanpi_withDD(s);
	atanpi_withDD << "kernel_atanpi_withDD";
	atanpi_withDD << vectorSize;
	//dumpPTXCode(context,program,atanpi_withDD.str().c_str());
	// Create the cKermel_kernel_atanpi_withDD
	kernel[2]  = clCreateKernel(program, atanpi_withDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_atanpi_withDD)");

	std::stringstream atanpi_withoutDD(s);
	atanpi_withoutDD << "kernel_atanpi_withoutDD";
	atanpi_withoutDD << vectorSize;
	//dumpPTXCode(context,program,atanpi_withoutDD.str().c_str());
	// Create the cKermel_kernel_atanpi_withoutDD
	kernel[3]  = clCreateKernel(program, atanpi_withoutDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_atanpi_withoutDD)");

	std::stringstream atan2_withDD(s);
	atan2_withDD << "kernel_atan2_withDD";
	atan2_withDD << vectorSize;
	//dumpPTXCode(context,program,atan2_withDD.str().c_str());
	// Create the cKermel_kernel_atan2_withDD
	kernel[4]  = clCreateKernel(program, atan2_withDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_atan2_withDD)");

	std::stringstream atan2_withoutDD(s);
	atan2_withoutDD << "kernel_atan2_withoutDD";
	atan2_withoutDD << vectorSize;
	//dumpPTXCode(context,program,atan2_withoutDD.str().c_str());
	// Create the cKermel_kernel_atan2_withoutDD
	kernel[5]  = clCreateKernel(program, atan2_withoutDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_atan2_withoutDD)");

	std::stringstream atan2pi_withDD(s);
	atan2pi_withDD << "kernel_atan2pi_withDD";
	atan2pi_withDD << vectorSize;
	//dumpPTXCode(context,program,atan2pi_withDD.str().c_str());
	// Create the cKermel_kernel_atan2pi_withDD
	kernel[6]  = clCreateKernel(program, atan2pi_withDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_atan2pi_withDD)");

	std::stringstream atan2pi_withoutDD(s);
	atan2pi_withoutDD << "kernel_atan2pi_withoutDD";
	atan2pi_withoutDD << vectorSize;
	//dumpPTXCode(context,program,atan2pi_withoutDD.str().c_str());
	// Create the cKermel_kernel_atan2pi_withoutDD
	kernel[7]  = clCreateKernel(program, atan2pi_withoutDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_atan2pi_withoutDD)");

	return SDK_SUCCESS;
}

int MathBenchmark::setup() {
	//if (setupMemory() != SDK_SUCCESS)
	//	return SDK_FAILURE;

	int timer = sampleCommon->createTimer();
	sampleCommon->resetTimer(timer);
	sampleCommon->startTimer(timer);

	int status = setupCL();
	if (status != SDK_SUCCESS) {
		if (status == SDK_EXPECTED_FAILURE)
			return SDK_EXPECTED_FAILURE;

		return SDK_FAILURE;
	}

	sampleCommon->stopTimer(timer);
	setupTime = (cl_double) sampleCommon->readTimer(timer);
	return SDK_SUCCESS;
}

double MathBenchmark::executionTime(cl_event &event) {
	cl_ulong start, end;
	cl_int status = 0;

	status = clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END,
			sizeof(cl_ulong), &end, NULL);
	status |= clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START,
			sizeof(cl_ulong), &start, NULL);

	CHECK_OPENCL_ERROR(status, "clGetEventProfilingInfo failed. (event)");

	return (double) 1.0e-6 * (end - start); // convert nanoseconds to min seconds on return
}

int MathBenchmark::runCLKernels() {
	cl_int status = 0;
	size_t WorkDim = 1;
	size_t szGlobalWorkSize = globalThreads;
	size_t szLocalWorkSize = localThreads;
	size_t szForNum = repeat;

	//create event to record time
	cl_event event_acospi_withDD, event_acospi_withoutDD;
	cl_event event_atanpi_withDD, event_atanpi_withoutDD;
	cl_event event_atan2_withDD, event_atan2_withoutDD;
	cl_event event_atan2pi_withDD, event_atan2pi_withoutDD;

	//Create Variable for story result reading from device to host
	void *acospi_withDD_num, *acospi_withoutDD_num;
	void *atanpi_withDD_num, *atanpi_withoutDD_num;
	void *atan2_withDD_num, *atan2_withoutDD_num;
	void *atan2pi_withDD_num, *atan2pi_withoutDD_num;

	acospi_withDD_num = (void *) malloc(sizeof(cl_float));
	acospi_withoutDD_num = (void *) malloc(sizeof(cl_float));
	atanpi_withDD_num = (void *) malloc(sizeof(cl_float));
	atanpi_withoutDD_num = (void *) malloc(sizeof(cl_float));
	atan2_withDD_num = (void *) malloc(sizeof(cl_float));
	atan2_withoutDD_num = (void *) malloc(sizeof(cl_float));
	atan2pi_withDD_num = (void *) malloc(sizeof(cl_float));
	atan2pi_withoutDD_num = (void *) malloc(sizeof(cl_float));

	float acospi_withDD_maxGflops = 0.0;
	float acospi_withoutDD_maxGflops = 0.0;
	float atanpi_withDD_maxGflops = 0.0;
	float atanpi_withoutDD_maxGflops = 0.0;
	float atan2_withDD_maxGflops = 0.0;
	float atan2_withoutDD_maxGflops = 0.0;
	float atan2pi_withDD_maxGflops = 0.0;
	float atan2pi_withoutDD_maxGflops = 0.0;

	//create buffer

	cl_mem result_acospi_withDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_acospi_withoutDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_atanpi_withDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_atanpi_withoutDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_atan2_withDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_atan2_withoutDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_atan2pi_withDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_atan2pi_withoutDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);

	//set kernel_acospi_withDD Argument
	status |= clSetKernelArg(kernel[0] , 0, sizeof(cl_mem),
			(void*) &result_acospi_withDD);
	status |= clSetKernelArg(kernel[0] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_acospi_withDD)");

	//set kernel_acospi_withoutDD Argument
	status |= clSetKernelArg(kernel[1] , 0, sizeof(cl_mem),
			(void*) &result_acospi_withoutDD);
	status |= clSetKernelArg(kernel[1] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_acospi_withoutDD)");

	//set kernel_atanpi_withDD Argument
	status |= clSetKernelArg(kernel[2] , 0, sizeof(cl_mem),
			(void*) &result_atanpi_withDD);
	status |= clSetKernelArg(kernel[2] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_atanpi_withDD)");

	//set kernel_atanpi_withoutDD Argument
	status |= clSetKernelArg(kernel[3] , 0, sizeof(cl_mem),
			(void*) &result_atanpi_withoutDD);
	status |= clSetKernelArg(kernel[3] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_atanpi_withoutDD)");

	//set kernel_atan2_withDD Argument
	status |= clSetKernelArg(kernel[4] , 0, sizeof(cl_mem),
			(void*) &result_atan2_withDD);
	status |= clSetKernelArg(kernel[4] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_atan2_withDD)");

	//set kernel_atan2_withoutDD Argument
	status |= clSetKernelArg(kernel[5] , 0, sizeof(cl_mem),
			(void*) &result_atan2_withoutDD);
	status |= clSetKernelArg(kernel[5] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_atan2_withoutDD)");

	//set kernel_atan2pi_withDD Argument
	status |= clSetKernelArg(kernel[6] , 0, sizeof(cl_mem),
			(void*) &result_atan2pi_withDD);
	status |= clSetKernelArg(kernel[6] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_atan2pi_withDD)");

	//set kernel_atan2pi_withoutDD Argument
	status |= clSetKernelArg(kernel[7] , 0, sizeof(cl_mem),
			(void*) &result_atan2pi_withoutDD);
	status |= clSetKernelArg(kernel[7] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_atan2pi_withoutDD)");

	int i = 0;
	int gws, lws;
	for (gws = 1024; gws <= 65536 * 8; gws *= 2)
		for (lws = 64; lws <= 256; lws *= 2) {

			float executionTime_acospi_withDD_max = 0.0;
			float executionTime_acospi_withDD_avg = 0.0;
			float executionTime_acospi_withDD_min = 999999999.0;

			float executionTime_acospi_withoutDD_max = 0.0;
			float executionTime_acospi_withoutDD_avg = 0.0;
			float executionTime_acospi_withoutDD_min = 999999999.0;

			float executionTime_atanpi_withDD_max = 0.0;
			float executionTime_atanpi_withDD_avg = 0.0;
			float executionTime_atanpi_withDD_min = 999999999.0;

			float executionTime_atanpi_withoutDD_max = 0.0;
			float executionTime_atanpi_withoutDD_avg = 0.0;
			float executionTime_atanpi_withoutDD_min = 999999999.0;

			float executionTime_atan2_withDD_max = 0.0;
			float executionTime_atan2_withDD_avg = 0.0;
			float executionTime_atan2_withDD_min = 999999999.0;

			float executionTime_atan2_withoutDD_max = 0.0;
			float executionTime_atan2_withoutDD_avg = 0.0;
			float executionTime_atan2_withoutDD_min = 999999999.0;

			float executionTime_atan2pi_withDD_max = 0.0;
			float executionTime_atan2pi_withDD_avg = 0.0;
			float executionTime_atan2pi_withDD_min = 999999999.0;

			float executionTime_atan2pi_withoutDD_max = 0.0;
			float executionTime_atan2pi_withoutDD_avg = 0.0;
			float executionTime_atan2pi_withoutDD_min = 999999999.0;

			szGlobalWorkSize = gws;
			szLocalWorkSize = lws;
			printf("-----------------------------------------------------\n");
			printf("Set gws = %d , lws = %d\n", gws, lws);
			//launch kernel_acospi_withDD
			if (!strcmp(kernelname.c_str(), "acospi_withDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str()<< vectorSize <<std::endl;
				printf("Begin to launch kernel_acospi_withDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[0] ,
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_acospi_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time kernel_acospi
					status = clWaitForEvents(1, &event_acospi_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_acospi_withDD, end_acospi_withDD;
					status = clGetEventProfilingInfo(event_acospi_withDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_acospi_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_acospi_withDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_acospi_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					float executionTime_acospi_withDD = (end_acospi_withDD
							- start_acospi_withDD);
					if (executionTime_acospi_withDD_max
							< executionTime_acospi_withDD) {
						executionTime_acospi_withDD_max = executionTime_acospi_withDD;
					}
					if (executionTime_acospi_withDD_min
							> executionTime_acospi_withDD) {
						executionTime_acospi_withDD_min = executionTime_acospi_withDD;
					}
					executionTime_acospi_withDD_avg += executionTime_acospi_withDD;

				}
				executionTime_acospi_withDD_avg = (executionTime_acospi_withDD_avg
						- executionTime_acospi_withDD_max
						- executionTime_acospi_withDD_min) / (iterations - 2);
				size_t time_acospi_withDD=0;
					time_acospi_withDD= 64 * szForNum * vectorSize;
				float Gflops_acospi_withDD =
						(time_acospi_withDD * szGlobalWorkSize)
								/ executionTime_acospi_withDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_acospi_withDD,
						CL_TRUE, 0, sizeof(cl_mem), acospi_withDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-acospi_withDD : %f\n", Gflops_acospi_withDD);
				printf("Result-acospi_withDD   :   %f\n\n", *((float*)acospi_withDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_acospi_withDD > acospi_withDD_maxGflops){
						acospi_withDD_maxGflops = Gflops_acospi_withDD;
				}
			}

			//launch kernel_acospi_withoutDD
			if (!strcmp(kernelname.c_str(), "acospi_withoutDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str()<< vectorSize <<std::endl;
				printf("Begin to launch kernel_acospi_withoutDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[1] ,
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_acospi_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time kernel_acospi
					status = clWaitForEvents(1, &event_acospi_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_acospi_withoutDD, end_acospi_withoutDD;
					status = clGetEventProfilingInfo(event_acospi_withoutDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_acospi_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_acospi_withoutDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_acospi_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					float executionTime_acospi_withoutDD = (end_acospi_withoutDD
							- start_acospi_withoutDD);
					if (executionTime_acospi_withoutDD_max
							< executionTime_acospi_withoutDD) {
						executionTime_acospi_withoutDD_max = executionTime_acospi_withoutDD;
					}
					if (executionTime_acospi_withoutDD_min
							> executionTime_acospi_withoutDD) {
						executionTime_acospi_withoutDD_min = executionTime_acospi_withoutDD;
					}
					executionTime_acospi_withoutDD_avg += executionTime_acospi_withoutDD;

				}
				executionTime_acospi_withoutDD_avg = (executionTime_acospi_withoutDD_avg
						- executionTime_acospi_withoutDD_max
						- executionTime_acospi_withoutDD_min) / (iterations - 2);
				size_t time_acospi_withoutDD=0;
				switch(vectorSize){
					case 1:time_acospi_withoutDD= 20000 * 10 * vectorSize;break;
					case 2:time_acospi_withoutDD= 2000 * 10 * vectorSize;break;
					case 4:time_acospi_withoutDD= 20 * 10 * vectorSize;break;
					case 8:time_acospi_withoutDD= 20 * 10 * vectorSize;break;
					case 16:time_acospi_withoutDD= 20 * 10 * vectorSize;break;
				}				

				float Gflops_acospi_withoutDD =
						(time_acospi_withoutDD * szGlobalWorkSize)
								/ executionTime_acospi_withoutDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_acospi_withoutDD,
						CL_TRUE, 0, sizeof(cl_mem), acospi_withoutDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-acospi_withoutDD : %f\n", Gflops_acospi_withoutDD);
				printf("Result-acospi_withoutDD   :   %f\n\n", *((float*)acospi_withoutDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_acospi_withoutDD > acospi_withoutDD_maxGflops){
						acospi_withoutDD_maxGflops = Gflops_acospi_withoutDD;
				}

			}

			//launch kernel_atanpi_withDD
			if (!strcmp(kernelname.c_str(), "atanpi_withDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str()<< vectorSize <<std::endl;
				printf("Begin to launch kernel_atanpi_withDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[2] ,
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_atanpi_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time kernel_atanpi
					status = clWaitForEvents(1, &event_atanpi_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_atanpi_withDD, end_atanpi_withDD;
					status = clGetEventProfilingInfo(event_atanpi_withDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_atanpi_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_atanpi_withDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_atanpi_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					float executionTime_atanpi_withDD = (end_atanpi_withDD
							- start_atanpi_withDD);
					if (executionTime_atanpi_withDD_max
							< executionTime_atanpi_withDD) {
						executionTime_atanpi_withDD_max = executionTime_atanpi_withDD;
					}
					if (executionTime_atanpi_withDD_min
							> executionTime_atanpi_withDD) {
						executionTime_atanpi_withDD_min = executionTime_atanpi_withDD;
					}
					executionTime_atanpi_withDD_avg += executionTime_atanpi_withDD;

				}
				executionTime_atanpi_withDD_avg = (executionTime_atanpi_withDD_avg
						- executionTime_atanpi_withDD_max
						- executionTime_atanpi_withDD_min) / (iterations - 2);
				size_t time_atanpi_withDD=0;
					time_atanpi_withDD= 64*szForNum * vectorSize;
				float Gflops_atanpi_withDD =
						(time_atanpi_withDD * szGlobalWorkSize)
								/ executionTime_atanpi_withDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_atanpi_withDD,
						CL_TRUE, 0, sizeof(cl_mem), atanpi_withDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-atanpi_withDD : %f\n", Gflops_atanpi_withDD);
				printf("Result-atanpi_withDD   :   %f\n\n", *((float*)atanpi_withDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_atanpi_withDD > atanpi_withDD_maxGflops){
						atanpi_withDD_maxGflops = Gflops_atanpi_withDD;
				}
			}

			//launch kernel_atanpi_withoutDD
			if (!strcmp(kernelname.c_str(), "atanpi_withoutDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str()<< vectorSize <<std::endl;
				printf("Begin to launch kernel_atanpi_withoutDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[3] ,
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_atanpi_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time kernel_atanpi
					status = clWaitForEvents(1, &event_atanpi_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_atanpi_withoutDD, end_atanpi_withoutDD;
					status = clGetEventProfilingInfo(event_atanpi_withoutDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_atanpi_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_atanpi_withoutDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_atanpi_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					float executionTime_atanpi_withoutDD = (end_atanpi_withoutDD
							- start_atanpi_withoutDD);
					if (executionTime_atanpi_withoutDD_max
							< executionTime_atanpi_withoutDD) {
						executionTime_atanpi_withoutDD_max = executionTime_atanpi_withoutDD;
					}
					if (executionTime_atanpi_withoutDD_min
							> executionTime_atanpi_withoutDD) {
						executionTime_atanpi_withoutDD_min = executionTime_atanpi_withoutDD;
					}
					executionTime_atanpi_withoutDD_avg += executionTime_atanpi_withoutDD;

				}
				executionTime_atanpi_withoutDD_avg = (executionTime_atanpi_withoutDD_avg
						- executionTime_atanpi_withoutDD_max
						- executionTime_atanpi_withoutDD_min) / (iterations - 2);
				size_t time_atanpi_withoutDD=0;
				//if(vectorSize==1||vectorSize==2||vectorSize==4||vectorSize==8)
					time_atanpi_withoutDD=  10 * 10 *szForNum* vectorSize;
				/*if(vectorSize==8)
					time_atanpi_withoutDD=  640 * 10 * szForNum * vectorSize;*/
				//if(vectorSize==16)
				//	time_atanpi_withoutDD=  10 * 10 * szForNum * vectorSize;
				float Gflops_atanpi_withoutDD =
						(time_atanpi_withoutDD * szGlobalWorkSize)
								/ executionTime_atanpi_withoutDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_atanpi_withoutDD,
						CL_TRUE, 0, sizeof(cl_mem), atanpi_withoutDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-atanpi_withoutDD : %f\n", Gflops_atanpi_withoutDD);
				printf("Result-atanpi_withoutDD   :   %f\n\n", *((float*)atanpi_withoutDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_atanpi_withoutDD > atanpi_withoutDD_maxGflops){
						atanpi_withoutDD_maxGflops = Gflops_atanpi_withoutDD;

				}

			}

			//launch kernel_atan2_withDD
			if (!strcmp(kernelname.c_str(), "atan2_withDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str()<< vectorSize <<std::endl;
				printf("Begin to launch kernel_atan2_withDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[4] ,
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_atan2_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time kernel_atan2
					status = clWaitForEvents(1, &event_atan2_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_atan2_withDD, end_atan2_withDD;
					status = clGetEventProfilingInfo(event_atan2_withDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_atan2_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_atan2_withDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_atan2_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					float executionTime_atan2_withDD = (end_atan2_withDD
							- start_atan2_withDD);
					if (executionTime_atan2_withDD_max
							< executionTime_atan2_withDD) {
						executionTime_atan2_withDD_max = executionTime_atan2_withDD;
					}
					if (executionTime_atan2_withDD_min
							> executionTime_atan2_withDD) {
						executionTime_atan2_withDD_min = executionTime_atan2_withDD;
					}
					executionTime_atan2_withDD_avg += executionTime_atan2_withDD;

				}
				executionTime_atan2_withDD_avg = (executionTime_atan2_withDD_avg
						- executionTime_atan2_withDD_max
						- executionTime_atan2_withDD_min) / (iterations - 2);
				size_t time_atan2_withDD=0;
				/*if(vectorSize==1||vectorSize==2)
					time_atan2_withDD= 64 * szForNum * vectorSize;
				if(vectorSize==4)
					time_atan2_withDD= 32 * szForNum * vectorSize;
				if(vectorSize==8||vectorSize==16)*/
					time_atan2_withDD= 64 * szForNum * vectorSize;
				float Gflops_atan2_withDD =
						(time_atan2_withDD * szGlobalWorkSize)
								/ executionTime_atan2_withDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_atan2_withDD,
						CL_TRUE, 0, sizeof(cl_mem), atan2_withDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-atan2_withDD : %f\n", Gflops_atan2_withDD);
				printf("Result-atan2_withDD   :   %f\n\n", *((float*)atan2_withDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_atan2_withDD > atan2_withDD_maxGflops){
						atan2_withDD_maxGflops = Gflops_atan2_withDD;
				}
			}

			//launch kernel_atan2_withoutDD
			if (!strcmp(kernelname.c_str(), "atan2_withoutDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str()<< vectorSize <<std::endl;
				printf("Begin to launch kernel_atan2_withoutDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[5] ,
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_atan2_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time kernel_atan2
					status = clWaitForEvents(1, &event_atan2_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_atan2_withoutDD, end_atan2_withoutDD;
					status = clGetEventProfilingInfo(event_atan2_withoutDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_atan2_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_atan2_withoutDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_atan2_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					float executionTime_atan2_withoutDD = (end_atan2_withoutDD
							- start_atan2_withoutDD);
					if (executionTime_atan2_withoutDD_max
							< executionTime_atan2_withoutDD) {
						executionTime_atan2_withoutDD_max = executionTime_atan2_withoutDD;
					}
					if (executionTime_atan2_withoutDD_min
							> executionTime_atan2_withoutDD) {
						executionTime_atan2_withoutDD_min = executionTime_atan2_withoutDD;
					}
					executionTime_atan2_withoutDD_avg += executionTime_atan2_withoutDD;

				}
				executionTime_atan2_withoutDD_avg = (executionTime_atan2_withoutDD_avg
						- executionTime_atan2_withoutDD_max
						- executionTime_atan2_withoutDD_min) / (iterations - 2);
				size_t time_atan2_withoutDD=0;
				//if(vectorSize==1)
					time_atan2_withoutDD= 10 * 10 * szForNum * vectorSize;
				/*if(vectorSize==2||vectorSize==4)
					time_atan2_withoutDD= 128 * 12 * szForNum * vectorSize;
				if(vectorSize==8)
					time_atan2_withoutDD= 16 * 12 * szForNum * vectorSize;
				if(vectorSize==16)
					time_atan2_withoutDD= 8 * 12  * szForNum * vectorSize;*/
				float Gflops_atan2_withoutDD =
						(time_atan2_withoutDD * szGlobalWorkSize)
								/ executionTime_atan2_withoutDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_atan2_withoutDD,
						CL_TRUE, 0, sizeof(cl_mem), atan2_withoutDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-atan2_withoutDD : %f\n", Gflops_atan2_withoutDD);
				printf("Result-atan2_withoutDD   :   %f\n\n", *((float*)atan2_withoutDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_atan2_withoutDD > atan2_withoutDD_maxGflops){
						atan2_withoutDD_maxGflops = Gflops_atan2_withoutDD;
				}
			}

			//launch kernel_atan2pi_withDD
			if (!strcmp(kernelname.c_str(), "atan2pi_withDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str()<< vectorSize <<std::endl;
				printf("Begin to launch kernel_atan2pi_withDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[6] ,
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_atan2pi_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time kernel_atan2pi
					status = clWaitForEvents(1, &event_atan2pi_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_atan2pi_withDD, end_atan2pi_withDD;
					status = clGetEventProfilingInfo(event_atan2pi_withDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_atan2pi_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_atan2pi_withDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_atan2pi_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					float executionTime_atan2pi_withDD = (end_atan2pi_withDD
							- start_atan2pi_withDD);
					if (executionTime_atan2pi_withDD_max
							< executionTime_atan2pi_withDD) {
						executionTime_atan2pi_withDD_max = executionTime_atan2pi_withDD;
					}
					if (executionTime_atan2pi_withDD_min
							> executionTime_atan2pi_withDD) {
						executionTime_atan2pi_withDD_min = executionTime_atan2pi_withDD;
					}
					executionTime_atan2pi_withDD_avg += executionTime_atan2pi_withDD;

				}
				executionTime_atan2pi_withDD_avg = (executionTime_atan2pi_withDD_avg
						- executionTime_atan2pi_withDD_max
						- executionTime_atan2pi_withDD_min) / (iterations - 2);
				size_t time_atan2pi_withDD=0;
					time_atan2pi_withDD= 64 * szForNum * vectorSize;
				float Gflops_atan2pi_withDD =
						(time_atan2pi_withDD * szGlobalWorkSize)
								/ executionTime_atan2pi_withDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_atan2pi_withDD,
						CL_TRUE, 0, sizeof(cl_mem), atan2pi_withDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-atan2pi_withDD : %f\n", Gflops_atan2pi_withDD);
				printf("Result-atan2pi_withDD   :   %f\n\n", *((float*)atan2pi_withDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_atan2pi_withDD > atan2pi_withDD_maxGflops){
						atan2pi_withDD_maxGflops = Gflops_atan2pi_withDD;
				}
			}

			//launch kernel_atan2pi_withoutDD
			if (!strcmp(kernelname.c_str(), "atan2pi_withoutDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str()<< vectorSize <<std::endl;
				printf("Begin to launch kernel_atan2pi_withoutDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[7] ,
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_atan2pi_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time kernel_atan2pi
					status = clWaitForEvents(1, &event_atan2pi_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_atan2pi_withoutDD, end_atan2pi_withoutDD;
					status = clGetEventProfilingInfo(event_atan2pi_withoutDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_atan2pi_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_atan2pi_withoutDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_atan2pi_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					float executionTime_atan2pi_withoutDD = (end_atan2pi_withoutDD
							- start_atan2pi_withoutDD);
					if (executionTime_atan2pi_withoutDD_max
							< executionTime_atan2pi_withoutDD) {
						executionTime_atan2pi_withoutDD_max = executionTime_atan2pi_withoutDD;
					}
					if (executionTime_atan2pi_withoutDD_min
							> executionTime_atan2pi_withoutDD) {
						executionTime_atan2pi_withoutDD_min = executionTime_atan2pi_withoutDD;
					}
					executionTime_atan2pi_withoutDD_avg += executionTime_atan2pi_withoutDD;

				}
				executionTime_atan2pi_withoutDD_avg = (executionTime_atan2pi_withoutDD_avg
						- executionTime_atan2pi_withoutDD_max
						- executionTime_atan2pi_withoutDD_min) / (iterations - 2);
				size_t time_atan2pi_withoutDD=0;
				time_atan2pi_withoutDD= 10 * 10* szForNum * vectorSize;
				float Gflops_atan2pi_withoutDD =
						(time_atan2pi_withoutDD * szGlobalWorkSize)
								/ executionTime_atan2pi_withoutDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_atan2pi_withoutDD,
						CL_TRUE, 0, sizeof(cl_mem), atan2pi_withoutDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-atan2pi_withoutDD : %f\n", Gflops_atan2pi_withoutDD);
				printf("Result-atan2pi_withoutDD   :   %f\n\n", *((float*)atan2pi_withoutDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_atan2pi_withoutDD > atan2pi_withoutDD_maxGflops){
						atan2pi_withoutDD_maxGflops = Gflops_atan2pi_withoutDD;

				}

			}
	}	
	printf("acospi_withDD_maxGflops = %f\n",acospi_withDD_maxGflops);
	printf("acospi_withoutDD_maxGflops = %f\n",acospi_withoutDD_maxGflops);
	printf("atanpi_withDD_maxGflops = %f\n",atanpi_withDD_maxGflops);
	printf("atanpi_withoutDD_maxGflops = %f\n",atanpi_withoutDD_maxGflops);
	printf("atan2_withDD_maxGflops = %f\n",atan2_withDD_maxGflops);
	printf("atan2_withoutDD_maxGflops = %f\n",atan2_withoutDD_maxGflops);
	printf("atan2pi_withDD_maxGflops = %f\n",atan2pi_withDD_maxGflops);
	printf("atan2pi_withoutDD_maxGflops = %f\n",atan2pi_withoutDD_maxGflops);

	return SDK_SUCCESS;
}

int MathBenchmark::run() {
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
	if (runCLKernels() != SDK_SUCCESS)
		return SDK_FAILURE;
	sampleCommon->stopTimer(timer);
	totalKernelTime = (double) sampleCommon->readTimer(timer);

	//if(!quiet) {
	//	sampleCommon->printArray<cl_float>("Output", eigenIntervals[1], 2*length, 1);
	//}

	return SDK_SUCCESS;
}

int MathBenchmark::cleanup() {
	// Releases OpenCL resources (Context, Memory etc.)
	cl_int status;

	for (int i = 0; i < NUM_KERNELS; i++) {
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

int MathBenchmark::verifyResults() {
	return SDK_SUCCESS;
}

void MathBenchmark::printStats() {
	std::string strArray[3] = { "DiagonalLength", "Time(sec)",
			"[Transfer+Kernel]Time(sec)" };
	std::string stats[3];

	totalTime = setupTime + totalKernelTime;

	stats[0] = sampleCommon->toString(1410, std::dec);
	stats[1] = sampleCommon->toString(totalTime, std::dec);
	stats[2] = sampleCommon->toString(totalKernelTime, std::dec);

	this->Benchmark::printStats(strArray, stats, 3);
}

int main(int argc, char *argv[]) {
	cl_int status = 0;

	MathBenchmark clMath("Math1 benchmark");

	if (clMath.initialize() != SDK_SUCCESS)
		return SDK_FAILURE;

	if (clMath.parseCommandLine(argc, argv) != SDK_SUCCESS)
		return SDK_FAILURE;

	status = clMath.setup();
	if (status != SDK_SUCCESS) {
		if (status == SDK_EXPECTED_FAILURE)
			return SDK_SUCCESS;

		return SDK_FAILURE;
	}

	if (clMath.run() != SDK_SUCCESS)
		return SDK_FAILURE;

	if (clMath.verifyResults() != SDK_SUCCESS)
		return SDK_FAILURE;

	if (clMath.cleanup() != SDK_SUCCESS)
		return SDK_FAILURE;

	clMath.printStats();

	return SDK_SUCCESS;
}


