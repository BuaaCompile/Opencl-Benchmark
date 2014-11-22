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
	std::stringstream sinpi_withDD(s);
	sinpi_withDD << "kernel_sinpi_withDD";
	sinpi_withDD << vectorSize;
	//dumpPTXCode(context,program,sinpi_withDD.str().c_str());
	// Create the cKermel_kernel_sinpi_withDD
	kernel[0]  = clCreateKernel(program, sinpi_withDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_sinpi_withDD)");

	std::stringstream sinpi_withoutDD(s);
	sinpi_withoutDD << "kernel_sinpi_withoutDD";
	sinpi_withoutDD << vectorSize;
	//dumpPTXCode(context,program,sinpi_withoutDD.str().c_str());
	// Create the cKermel_kernel_sinpi_withoutDD
	kernel[1]  = clCreateKernel(program, sinpi_withoutDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_sinpi_withoutDD)");

	std::stringstream cospi_withDD(s);
	cospi_withDD << "kernel_cospi_withDD";
	cospi_withDD << vectorSize;
	//dumpPTXCode(context,program,cospi_withDD.str().c_str());
	// Create the cKermel_kernel_cospi_withDD
	kernel[2]  = clCreateKernel(program, cospi_withDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_cospi_withDD)");

	std::stringstream cospi_withoutDD(s);
	cospi_withoutDD << "kernel_cospi_withoutDD";
	cospi_withoutDD << vectorSize;
	//dumpPTXCode(context,program,cospi_withoutDD.str().c_str());
	// Create the cKermel_kernel_cospi_withoutDD
	kernel[3]  = clCreateKernel(program, cospi_withoutDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_cospi_withoutDD)");

	std::stringstream tanpi_withDD(s);
	tanpi_withDD << "kernel_tanpi_withDD";
	tanpi_withDD << vectorSize;
	//dumpPTXCode(context,program,tanpi_withDD.str().c_str());
	// Create the cKermel_kernel_tanpi_withDD
	kernel[4]  = clCreateKernel(program, tanpi_withDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_tanpi_withDD)");

	std::stringstream tanpi_withoutDD(s);
	tanpi_withoutDD << "kernel_tanpi_withoutDD";
	tanpi_withoutDD << vectorSize;
	//dumpPTXCode(context,program,tanpi_withoutDD.str().c_str());
	// Create the cKermel_kernel_tanpi_withoutDD
	kernel[5]  = clCreateKernel(program, tanpi_withoutDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_tanpi_withoutDD)");

	std::stringstream sincos_withDD(s);
	sincos_withDD << "kernel_sincos_withDD";
	sincos_withDD << vectorSize;
	//dumpPTXCode(context,program,sincos_withDD.str().c_str());
	// Create the cKermel_kernel_sincos_withDD
	kernel[6]  = clCreateKernel(program, sincos_withDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_sincos_withDD)");

	std::stringstream sincos_withoutDD(s);
	sincos_withoutDD << "kernel_sincos_withoutDD";
	sincos_withoutDD << vectorSize;
	//dumpPTXCode(context,program,sincos_withoutDD.str().c_str());
	// Create the cKermel_kernel_sincos_withoutDD
	kernel[7]  = clCreateKernel(program, sincos_withoutDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_sincos_withoutDD)");

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
	cl_event event_sinpi_withDD, event_sinpi_withoutDD;
	cl_event event_cospi_withDD, event_cospi_withoutDD;
	cl_event event_tanpi_withDD, event_tanpi_withoutDD;
	cl_event event_sincos_withDD, event_sincos_withoutDD;

	//Create Variable for story result reading from device to host
	void *sinpi_withDD_num, *sinpi_withoutDD_num;
	void *cospi_withDD_num, *cospi_withoutDD_num;
	void *tanpi_withDD_num, *tanpi_withoutDD_num;
	void *sincos_withDD_num, *sincos_withoutDD_num;

	sinpi_withDD_num = (void *) malloc(sizeof(cl_float));
	sinpi_withoutDD_num = (void *) malloc(sizeof(cl_float));
	cospi_withDD_num = (void *) malloc(sizeof(cl_float));
	cospi_withoutDD_num = (void *) malloc(sizeof(cl_float));
	tanpi_withDD_num = (void *) malloc(sizeof(cl_float));
	tanpi_withoutDD_num = (void *) malloc(sizeof(cl_float));
	sincos_withDD_num = (void *) malloc(sizeof(cl_float));
	sincos_withoutDD_num = (void *) malloc(sizeof(cl_float));

	float sinpi_withDD_maxGflops = 0.0;
	float sinpi_withoutDD_maxGflops = 0.0;
	float cospi_withDD_maxGflops = 0.0;
	float cospi_withoutDD_maxGflops = 0.0;
	float tanpi_withDD_maxGflops = 0.0;
	float tanpi_withoutDD_maxGflops = 0.0;
	float sincos_withDD_maxGflops = 0.0;
	float sincos_withoutDD_maxGflops = 0.0;

	//create buffer
	cl_mem result_sinpi_withDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_sinpi_withoutDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_cospi_withDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_cospi_withoutDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_tanpi_withDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_tanpi_withoutDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_sincos_withDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_sincos_withoutDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);


	//set kernel_sinpi_withDD Argument
	status |= clSetKernelArg(kernel[0] , 0, sizeof(cl_mem),
			(void*) &result_sinpi_withDD);
	status |= clSetKernelArg(kernel[0] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_sinpi_withDD)");
	
	//set kernel_sinpi_withoutDD Argument
	status |= clSetKernelArg(kernel[1] , 0, sizeof(cl_mem),
			(void*) &result_sinpi_withoutDD);
	status |= clSetKernelArg(kernel[1] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_sinpi_withoutDD)");

	//set kernel_cospi_withDD Argument
	status |= clSetKernelArg(kernel[2] , 0, sizeof(cl_mem),
			(void*) &result_cospi_withDD);
	status |= clSetKernelArg(kernel[2] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_cospi_withDD)");

	//set kernel_cospi_withoutDD Argument
	status |= clSetKernelArg(kernel[3] , 0, sizeof(cl_mem),
			(void*) &result_cospi_withoutDD);
	status |= clSetKernelArg(kernel[3] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_cospi_withoutDD)");

	//set kernel_tanpi_withDD Argument
	status |= clSetKernelArg(kernel[4] , 0, sizeof(cl_mem),
			(void*) &result_tanpi_withDD);
	status |= clSetKernelArg(kernel[4] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_tanpi_withDD)");

	//set kernel_tanpi_withoutDD Argument
	status |= clSetKernelArg(kernel[5] , 0, sizeof(cl_mem),
			(void*) &result_tanpi_withoutDD);
	status |= clSetKernelArg(kernel[5] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_tanpi_withoutDD)");


	//set kernel_sincos_withDD Argument
	status |= clSetKernelArg(kernel[6] , 0, sizeof(cl_mem),
			(void*) &result_sincos_withDD);
	status |= clSetKernelArg(kernel[6] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_sincos_withDD)");

	//set kernel_sincos_withoutDD Argument
	status |= clSetKernelArg(kernel[7] , 0, sizeof(cl_mem),
			(void*) &result_sincos_withoutDD);
	status |= clSetKernelArg(kernel[7] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_sincos_withoutDD)");



	int i = 0;
	int gws, lws;
	for (gws = 1024; gws <= 65536 * 8; gws *= 2)
		for (lws = 64; lws <= 256; lws *= 2) {
			
			float executionTime_sinpi_withDD_max = 0.0;
			float executionTime_sinpi_withDD_avg = 0.0;
			float executionTime_sinpi_withDD_min = 999999999.0;

			float executionTime_sinpi_withoutDD_max = 0.0;
			float executionTime_sinpi_withoutDD_avg = 0.0;
			float executionTime_sinpi_withoutDD_min = 999999999.0;

			float executionTime_cospi_withDD_max = 0.0;
			float executionTime_cospi_withDD_avg = 0.0;
			float executionTime_cospi_withDD_min = 999999999.0;

			float executionTime_cospi_withoutDD_max = 0.0;
			float executionTime_cospi_withoutDD_avg = 0.0;
			float executionTime_cospi_withoutDD_min = 999999999.0;

			float executionTime_tanpi_withDD_max = 0.0;
			float executionTime_tanpi_withDD_avg = 0.0;
			float executionTime_tanpi_withDD_min = 999999999.0;

			float executionTime_tanpi_withoutDD_max = 0.0;
			float executionTime_tanpi_withoutDD_avg = 0.0;
			float executionTime_tanpi_withoutDD_min = 999999999.0;

			float executionTime_sincos_withDD_max = 0.0;
			float executionTime_sincos_withDD_avg = 0.0;
			float executionTime_sincos_withDD_min = 999999999.0;

			float executionTime_sincos_withoutDD_max = 0.0;
			float executionTime_sincos_withoutDD_avg = 0.0;
			float executionTime_sincos_withoutDD_min = 999999999.0;

			szGlobalWorkSize = gws;
			szLocalWorkSize = lws;
			printf("-----------------------------------------------------\n");
			printf("Set gws = %d , lws = %d\n", gws, lws);

			//launch kernel_sinpi_withDD
			if (!strcmp(kernelname.c_str(), "sinpi_withDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str()<< vectorSize <<std::endl;
				printf("Begin to launch kernel_sinpi_withDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[0] ,
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_sinpi_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time kernel_sinpi
					status = clWaitForEvents(1, &event_sinpi_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_sinpi_withDD, end_sinpi_withDD;
					status = clGetEventProfilingInfo(event_sinpi_withDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_sinpi_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_sinpi_withDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_sinpi_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					float executionTime_sinpi_withDD = (end_sinpi_withDD
							- start_sinpi_withDD);
					if (executionTime_sinpi_withDD_max
							< executionTime_sinpi_withDD) {
						executionTime_sinpi_withDD_max = executionTime_sinpi_withDD;
					}
					if (executionTime_sinpi_withDD_min
							> executionTime_sinpi_withDD) {
						executionTime_sinpi_withDD_min = executionTime_sinpi_withDD;
					}
					executionTime_sinpi_withDD_avg += executionTime_sinpi_withDD;

				}
				executionTime_sinpi_withDD_avg = (executionTime_sinpi_withDD_avg
						- executionTime_sinpi_withDD_max
						- executionTime_sinpi_withDD_min) / (iterations - 2);
				size_t time_sinpi_withDD=0;
					time_sinpi_withDD= 64*szForNum * vectorSize;
				float Gflops_sinpi_withDD =
						(time_sinpi_withDD * szGlobalWorkSize)
								/ executionTime_sinpi_withDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_sinpi_withDD,
						CL_TRUE, 0, sizeof(cl_mem), sinpi_withDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-sinpi_withDD : %f\n", Gflops_sinpi_withDD);
				printf("Result-sinpi_withDD   :   %f\n\n", *((float*)sinpi_withDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_sinpi_withDD > sinpi_withDD_maxGflops){
						sinpi_withDD_maxGflops = Gflops_sinpi_withDD;

				}
			}

			//launch kernel_sinpi_withoutDD
			if (!strcmp(kernelname.c_str(), "sinpi_withoutDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str()<< vectorSize <<std::endl;
				printf("Begin to launch kernel_sinpi_withoutDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[1] ,
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_sinpi_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time kernel_sinpi
					status = clWaitForEvents(1, &event_sinpi_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_sinpi_withoutDD, end_sinpi_withoutDD;
					status = clGetEventProfilingInfo(event_sinpi_withoutDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_sinpi_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_sinpi_withoutDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_sinpi_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					float executionTime_sinpi_withoutDD = (end_sinpi_withoutDD
							- start_sinpi_withoutDD);
					if (executionTime_sinpi_withoutDD_max
							< executionTime_sinpi_withoutDD) {
						executionTime_sinpi_withoutDD_max = executionTime_sinpi_withoutDD;
					}
					if (executionTime_sinpi_withoutDD_min
							> executionTime_sinpi_withoutDD) {
						executionTime_sinpi_withoutDD_min = executionTime_sinpi_withoutDD;
					}
					executionTime_sinpi_withoutDD_avg += executionTime_sinpi_withoutDD;

				}
				executionTime_sinpi_withoutDD_avg = (executionTime_sinpi_withoutDD_avg
						- executionTime_sinpi_withoutDD_max
						- executionTime_sinpi_withoutDD_min) / (iterations - 2);
				size_t time_sinpi_withoutDD=0;
				//if(vectorSize==1||vectorSize==2||vectorSize==4||vectorSize==8)
					time_sinpi_withoutDD=  10 * 10  *szForNum*vectorSize;
				/*if(vectorSize==8)
					time_sinpi_withoutDD=  640 * 10 * szForNum * vectorSize;*/
				//if(vectorSize==16)
				//	time_sinpi_withoutDD=  10 * 10 * szForNum * vectorSize;
				float Gflops_sinpi_withoutDD =
						(time_sinpi_withoutDD * szGlobalWorkSize)
								/ executionTime_sinpi_withoutDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_sinpi_withoutDD,
						CL_TRUE, 0, sizeof(cl_mem), sinpi_withoutDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-sinpi_withoutDD : %f\n", Gflops_sinpi_withoutDD);
				printf("Result-sinpi_withoutDD   :   %f\n\n", *((float*)sinpi_withoutDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_sinpi_withoutDD > sinpi_withoutDD_maxGflops){
						sinpi_withoutDD_maxGflops = Gflops_sinpi_withoutDD;

				}

			}

			//launch kernel_cospi_withDD
			if (!strcmp(kernelname.c_str(), "cospi_withDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str()<< vectorSize <<std::endl;
				printf("Begin to launch kernel_cospi_withDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[2] ,
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_cospi_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time kernel_cospi
					status = clWaitForEvents(1, &event_cospi_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_cospi_withDD, end_cospi_withDD;
					status = clGetEventProfilingInfo(event_cospi_withDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_cospi_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_cospi_withDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_cospi_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					float executionTime_cospi_withDD = (end_cospi_withDD
							- start_cospi_withDD);
					if (executionTime_cospi_withDD_max
							< executionTime_cospi_withDD) {
						executionTime_cospi_withDD_max = executionTime_cospi_withDD;
					}
					if (executionTime_cospi_withDD_min
							> executionTime_cospi_withDD) {
						executionTime_cospi_withDD_min = executionTime_cospi_withDD;
					}
					executionTime_cospi_withDD_avg += executionTime_cospi_withDD;

				}
				executionTime_cospi_withDD_avg = (executionTime_cospi_withDD_avg
						- executionTime_cospi_withDD_max
						- executionTime_cospi_withDD_min) / (iterations - 2);
				size_t time_cospi_withDD=0;
				/*if(vectorSize==1||vectorSize==2)
					time_cospi_withDD= 64 * szForNum * vectorSize;
				if(vectorSize==4)
					time_cospi_withDD= 32 * szForNum * vectorSize;
				if(vectorSize==8||vectorSize==16)*/
					time_cospi_withDD= 64 * szForNum * vectorSize;
				float Gflops_cospi_withDD =
						(time_cospi_withDD * szGlobalWorkSize)
								/ executionTime_cospi_withDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_cospi_withDD,
						CL_TRUE, 0, sizeof(cl_mem), cospi_withDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-cospi_withDD : %f\n", Gflops_cospi_withDD);
				printf("Result-cospi_withDD   :   %f\n\n", *((float*)cospi_withDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_cospi_withDD > cospi_withDD_maxGflops){
						cospi_withDD_maxGflops = Gflops_cospi_withDD;

				}
			}

			//launch kernel_cospi_withoutDD
			if (!strcmp(kernelname.c_str(), "cospi_withoutDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str()<< vectorSize <<std::endl;
				printf("Begin to launch kernel_cospi_withoutDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[3] ,
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_cospi_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time kernel_cospi
					status = clWaitForEvents(1, &event_cospi_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_cospi_withoutDD, end_cospi_withoutDD;
					status = clGetEventProfilingInfo(event_cospi_withoutDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_cospi_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_cospi_withoutDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_cospi_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					float executionTime_cospi_withoutDD = (end_cospi_withoutDD
							- start_cospi_withoutDD);
					if (executionTime_cospi_withoutDD_max
							< executionTime_cospi_withoutDD) {
						executionTime_cospi_withoutDD_max = executionTime_cospi_withoutDD;
					}
					if (executionTime_cospi_withoutDD_min
							> executionTime_cospi_withoutDD) {
						executionTime_cospi_withoutDD_min = executionTime_cospi_withoutDD;
					}
					executionTime_cospi_withoutDD_avg += executionTime_cospi_withoutDD;

				}
				executionTime_cospi_withoutDD_avg = (executionTime_cospi_withoutDD_avg
						- executionTime_cospi_withoutDD_max
						- executionTime_cospi_withoutDD_min) / (iterations - 2);
				size_t time_cospi_withoutDD=0;
				//if(vectorSize==1)
					time_cospi_withoutDD= 10 * 10 * szForNum * vectorSize;
				/*if(vectorSize==2||vectorSize==4)
					time_cospi_withoutDD= 128 * 12 * szForNum * vectorSize;
				if(vectorSize==8)
					time_cospi_withoutDD= 16 * 12 * szForNum * vectorSize;
				if(vectorSize==16)
					time_cospi_withoutDD= 8 * 12  * szForNum * vectorSize;*/
				float Gflops_cospi_withoutDD =
						(time_cospi_withoutDD * szGlobalWorkSize)
								/ executionTime_cospi_withoutDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_cospi_withoutDD,
						CL_TRUE, 0, sizeof(cl_mem), cospi_withoutDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-cospi_withoutDD : %f\n", Gflops_cospi_withoutDD);
				printf("Result-cospi_withoutDD   :   %f\n\n", *((float*)cospi_withoutDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_cospi_withoutDD > cospi_withoutDD_maxGflops){
						cospi_withoutDD_maxGflops = Gflops_cospi_withoutDD;

				}
			}

			//launch kernel_tanpi_withDD
			if (!strcmp(kernelname.c_str(), "tanpi_withDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str()<< vectorSize <<std::endl;
				printf("Begin to launch kernel_tanpi_withDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[4] ,
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_tanpi_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time kernel_tanpi
					status = clWaitForEvents(1, &event_tanpi_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_tanpi_withDD, end_tanpi_withDD;
					status = clGetEventProfilingInfo(event_tanpi_withDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_tanpi_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_tanpi_withDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_tanpi_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					float executionTime_tanpi_withDD = (end_tanpi_withDD
							- start_tanpi_withDD);
					if (executionTime_tanpi_withDD_max
							< executionTime_tanpi_withDD) {
						executionTime_tanpi_withDD_max = executionTime_tanpi_withDD;
					}
					if (executionTime_tanpi_withDD_min
							> executionTime_tanpi_withDD) {
						executionTime_tanpi_withDD_min = executionTime_tanpi_withDD;
					}
					executionTime_tanpi_withDD_avg += executionTime_tanpi_withDD;

				}
				executionTime_tanpi_withDD_avg = (executionTime_tanpi_withDD_avg
						- executionTime_tanpi_withDD_max
						- executionTime_tanpi_withDD_min) / (iterations - 2);
				size_t time_tanpi_withDD=0;
					time_tanpi_withDD= 64 * szForNum * vectorSize;
				float Gflops_tanpi_withDD =
						(time_tanpi_withDD * szGlobalWorkSize)
								/ executionTime_tanpi_withDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_tanpi_withDD,
						CL_TRUE, 0, sizeof(cl_mem), tanpi_withDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-tanpi_withDD : %f\n", Gflops_tanpi_withDD);
				printf("Result-tanpi_withDD   :   %f\n\n", *((float*)tanpi_withDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_tanpi_withDD > tanpi_withDD_maxGflops){
						tanpi_withDD_maxGflops = Gflops_tanpi_withDD;

				}
			}

			//launch kernel_tanpi_withoutDD
			if (!strcmp(kernelname.c_str(), "tanpi_withoutDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str()<< vectorSize <<std::endl;
				printf("Begin to launch kernel_tanpi_withoutDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[5] ,
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_tanpi_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time kernel_tanpi
					status = clWaitForEvents(1, &event_tanpi_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_tanpi_withoutDD, end_tanpi_withoutDD;
					status = clGetEventProfilingInfo(event_tanpi_withoutDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_tanpi_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_tanpi_withoutDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_tanpi_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					float executionTime_tanpi_withoutDD = (end_tanpi_withoutDD
							- start_tanpi_withoutDD);
					if (executionTime_tanpi_withoutDD_max
							< executionTime_tanpi_withoutDD) {
						executionTime_tanpi_withoutDD_max = executionTime_tanpi_withoutDD;
					}
					if (executionTime_tanpi_withoutDD_min
							> executionTime_tanpi_withoutDD) {
						executionTime_tanpi_withoutDD_min = executionTime_tanpi_withoutDD;
					}
					executionTime_tanpi_withoutDD_avg += executionTime_tanpi_withoutDD;

				}
				executionTime_tanpi_withoutDD_avg = (executionTime_tanpi_withoutDD_avg
						- executionTime_tanpi_withoutDD_max
						- executionTime_tanpi_withoutDD_min) / (iterations - 2);
				size_t time_tanpi_withoutDD=0;
				time_tanpi_withoutDD= 10 * 10* szForNum * vectorSize;
				float Gflops_tanpi_withoutDD =
						(time_tanpi_withoutDD * szGlobalWorkSize)
								/ executionTime_tanpi_withoutDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_tanpi_withoutDD,
						CL_TRUE, 0, sizeof(cl_mem), tanpi_withoutDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-tanpi_withoutDD : %f\n", Gflops_tanpi_withoutDD);
				printf("Result-tanpi_withoutDD   :   %f\n\n", *((float*)tanpi_withoutDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_tanpi_withoutDD > tanpi_withoutDD_maxGflops){
						tanpi_withoutDD_maxGflops = Gflops_tanpi_withoutDD;

				}

			}

			//launch kernel_sincos_withDD
			if (!strcmp(kernelname.c_str(), "sincos_withDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str()<< vectorSize <<std::endl;
				printf("Begin to launch kernel_sincos_withDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[6] ,
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_sincos_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time kernel_sincos
					status = clWaitForEvents(1, &event_sincos_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_sincos_withDD, end_sincos_withDD;
					status = clGetEventProfilingInfo(event_sincos_withDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_sincos_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_sincos_withDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_sincos_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					float executionTime_sincos_withDD = (end_sincos_withDD
							- start_sincos_withDD);
					if (executionTime_sincos_withDD_max
							< executionTime_sincos_withDD) {
						executionTime_sincos_withDD_max = executionTime_sincos_withDD;
					}
					if (executionTime_sincos_withDD_min
							> executionTime_sincos_withDD) {
						executionTime_sincos_withDD_min = executionTime_sincos_withDD;
					}
					executionTime_sincos_withDD_avg += executionTime_sincos_withDD;

				}
				executionTime_sincos_withDD_avg = (executionTime_sincos_withDD_avg
						- executionTime_sincos_withDD_max
						- executionTime_sincos_withDD_min) / (iterations - 2);
				size_t time_sincos_withDD=0;
					time_sincos_withDD= 64*szForNum * vectorSize;
				float Gflops_sincos_withDD =
						(time_sincos_withDD * szGlobalWorkSize)
								/ executionTime_sincos_withDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_sincos_withDD,
						CL_TRUE, 0, sizeof(cl_mem), sincos_withDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-sincos_withDD : %f\n", Gflops_sincos_withDD);
				printf("Result-sincos_withDD   :   %f\n\n", *((float*)sincos_withDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_sincos_withDD > sincos_withDD_maxGflops){
						sincos_withDD_maxGflops = Gflops_sincos_withDD;

				}
			}

			//launch kernel_sincos_withoutDD
			if (!strcmp(kernelname.c_str(), "sincos_withoutDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str()<< vectorSize <<std::endl;
				printf("Begin to launch kernel_sincos_withoutDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[7] ,
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_sincos_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time kernel_sincos
					status = clWaitForEvents(1, &event_sincos_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_sincos_withoutDD, end_sincos_withoutDD;
					status = clGetEventProfilingInfo(event_sincos_withoutDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_sincos_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_sincos_withoutDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_sincos_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					float executionTime_sincos_withoutDD = (end_sincos_withoutDD
							- start_sincos_withoutDD);
					if (executionTime_sincos_withoutDD_max
							< executionTime_sincos_withoutDD) {
						executionTime_sincos_withoutDD_max = executionTime_sincos_withoutDD;
					}
					if (executionTime_sincos_withoutDD_min
							> executionTime_sincos_withoutDD) {
						executionTime_sincos_withoutDD_min = executionTime_sincos_withoutDD;
					}
					executionTime_sincos_withoutDD_avg += executionTime_sincos_withoutDD;

				}
				executionTime_sincos_withoutDD_avg = (executionTime_sincos_withoutDD_avg
						- executionTime_sincos_withoutDD_max
						- executionTime_sincos_withoutDD_min) / (iterations - 2);
				size_t time_sincos_withoutDD=0;
				//if(vectorSize==1||vectorSize==2||vectorSize==4||vectorSize==8)
					time_sincos_withoutDD= 10 * 10 * szForNum * vectorSize;
				/*if(vectorSize==8)
					time_sincos_withoutDD=  640 * 10 * szForNum * vectorSize;*/
				//if(vectorSize==16)
				//	time_sincos_withoutDD=  10 * 10 * szForNum * vectorSize;
				float Gflops_sincos_withoutDD =
						(time_sincos_withoutDD * szGlobalWorkSize)
								/ executionTime_sincos_withoutDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_sincos_withoutDD,
						CL_TRUE, 0, sizeof(cl_mem), sincos_withoutDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-sincos_withoutDD : %f\n", Gflops_sincos_withoutDD);
				printf("Result-sincos_withoutDD   :   %f\n\n", *((float*)sincos_withoutDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_sincos_withoutDD > sincos_withoutDD_maxGflops){
						sincos_withoutDD_maxGflops = Gflops_sincos_withoutDD;

				}

			}

	}	
	printf("sinpi_withDD_maxGflops = %f\n",sinpi_withDD_maxGflops);
	printf("sinpi_withoutDD_maxGflops = %f\n",sinpi_withoutDD_maxGflops);
	printf("cospi_withDD_maxGflops = %f\n",cospi_withDD_maxGflops);
	printf("cospi_withoutDD_maxGflops = %f\n",cospi_withoutDD_maxGflops);
	printf("tanpi_withDD_maxGflops = %f\n",tanpi_withDD_maxGflops);
	printf("tanpi_withoutDD_maxGflops = %f\n",tanpi_withoutDD_maxGflops);
	printf("sincos_withDD_maxGflops = %f\n",sincos_withDD_maxGflops);
	printf("sincos_withoutDD_maxGflops = %f\n",sincos_withoutDD_maxGflops);

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


