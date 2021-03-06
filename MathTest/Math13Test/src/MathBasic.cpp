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
	std::stringstream log1p_withDD(s);
	log1p_withDD << "kernel_log1p_withDD";
	log1p_withDD << vectorSize;
	//dumpPTXCode(context,program,log1p_withDD.str().c_str());
	// Create the cKermel_kernel_log1p_withDD
	kernel[0]  = clCreateKernel(program, log1p_withDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_log1p_withDD)");

	std::stringstream log1p_withoutDD(s);
	log1p_withoutDD << "kernel_log1p_withoutDD";
	log1p_withoutDD << vectorSize;
	//dumpPTXCode(context,program,log1p_withoutDD.str().c_str());
	// Create the cKermel_kernel_log1p_withoutDD
	kernel[1]  = clCreateKernel(program, log1p_withoutDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_log1p_withoutDD)");

	std::stringstream logb_withDD(s);
	logb_withDD << "kernel_logb_withDD";
	logb_withDD << vectorSize;
	//dumpPTXCode(context,program,logb_withDD.str().c_str());
	// Create the cKermel_kernel_logb_withDD
	kernel[2]  = clCreateKernel(program, logb_withDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_logb_withDD)");

	std::stringstream logb_withoutDD(s);
	logb_withoutDD << "kernel_logb_withoutDD";
	logb_withoutDD << vectorSize;
	//dumpPTXCode(context,program,logb_withoutDD.str().c_str());
	// Create the cKermel_kernel_logb_withoutDD
	kernel[3]  = clCreateKernel(program, logb_withoutDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_logb_withoutDD)");

	std::stringstream modf_withDD(s);
	modf_withDD << "kernel_modf_withDD";
	modf_withDD << vectorSize;
	//dumpPTXCode(context,program,modf_withDD.str().c_str());
	// Create the cKermel_kernel_modf_withDD
	kernel[4]  = clCreateKernel(program, modf_withDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_modf_withDD)");

	std::stringstream modf_withoutDD(s);
	modf_withoutDD << "kernel_modf_withoutDD";
	modf_withoutDD << vectorSize;
	//dumpPTXCode(context,program,modf_withoutDD.str().c_str());
	// Create the cKermel_kernel_modf_withoutDD
	kernel[5]  = clCreateKernel(program, modf_withoutDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_modf_withoutDD)");

	std::stringstream lgamma_withDD(s);
	lgamma_withDD << "kernel_lgamma_withDD";
	lgamma_withDD << vectorSize;
	//dumpPTXCode(context,program,lgamma_withDD.str().c_str());
	// Create the cKermel_kernel_lgamma_withDD
	kernel[6]  = clCreateKernel(program, lgamma_withDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_lgamma_withDD)");

	std::stringstream lgamma_withoutDD(s);
	lgamma_withoutDD << "kernel_lgamma_withoutDD";
	lgamma_withoutDD << vectorSize;
	//dumpPTXCode(context,program,lgamma_withoutDD.str().c_str());
	// Create the cKermel_kernel_lgamma_withoutDD
	kernel[7]  = clCreateKernel(program, lgamma_withoutDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_lgamma_withoutDD)");

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
	cl_event event_log1p_withDD, event_log1p_withoutDD;
	cl_event event_logb_withDD, event_logb_withoutDD;
	cl_event event_modf_withDD, event_modf_withoutDD;
	cl_event event_lgamma_withDD, event_lgamma_withoutDD;

	//Create Variable for story result reading from device to host
	void *log1p_withDD_num, *log1p_withoutDD_num;
	void *logb_withDD_num, *logb_withoutDD_num;
	void *modf_withDD_num, *modf_withoutDD_num;
	void *lgamma_withDD_num, *lgamma_withoutDD_num;

	log1p_withDD_num = (void *) malloc(sizeof(cl_float));
	log1p_withoutDD_num = (void *) malloc(sizeof(cl_float));
	logb_withDD_num = (void *) malloc(sizeof(cl_float));
	logb_withoutDD_num = (void *) malloc(sizeof(cl_float));
	modf_withDD_num = (void *) malloc(sizeof(cl_float));
	modf_withoutDD_num = (void *) malloc(sizeof(cl_float));
	lgamma_withDD_num = (void *) malloc(sizeof(cl_float));
	lgamma_withoutDD_num = (void *) malloc(sizeof(cl_float));

	float log1p_withDD_maxGflops = 0.0;
	float log1p_withoutDD_maxGflops = 0.0;
	float logb_withDD_maxGflops = 0.0;
	float logb_withoutDD_maxGflops = 0.0;
	float modf_withDD_maxGflops = 0.0;
	float modf_withoutDD_maxGflops = 0.0;
	float lgamma_withDD_maxGflops = 0.0;
	float lgamma_withoutDD_maxGflops = 0.0;

	//create buffer
	cl_mem result_log1p_withDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_log1p_withoutDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_logb_withDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_logb_withoutDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_modf_withDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_modf_withoutDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_lgamma_withDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_lgamma_withoutDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);

	//set kernel_log1p_withDD Argument
	status |= clSetKernelArg(kernel[0] , 0, sizeof(cl_mem),
			(void*) &result_log1p_withDD);
	status |= clSetKernelArg(kernel[0] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_log1p_withDD)");

	//set kernel_log1p_withoutDD Argument
	status |= clSetKernelArg(kernel[1] , 0, sizeof(cl_mem),
			(void*) &result_log1p_withoutDD);
	status |= clSetKernelArg(kernel[1] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_log1p_withoutDD)");

	//set kernel_logb_withDD Argument
	status |= clSetKernelArg(kernel[2] , 0, sizeof(cl_mem),
			(void*) &result_logb_withDD);
	status |= clSetKernelArg(kernel[2] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_logb_withDD)");

	//set kernel_logb_withoutDD Argument
	status |= clSetKernelArg(kernel[3] , 0, sizeof(cl_mem),
			(void*) &result_logb_withoutDD);
	status |= clSetKernelArg(kernel[3] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_logb_withoutDD)");

	//set kernel_modf_withDD Argument
	status |= clSetKernelArg(kernel[4] , 0, sizeof(cl_mem),
			(void*) &result_modf_withDD);
	status |= clSetKernelArg(kernel[4] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_modf_withDD)");

	//set kernel_modf_withoutDD Argument
	status |= clSetKernelArg(kernel[5] , 0, sizeof(cl_mem),
			(void*) &result_modf_withoutDD);
	status |= clSetKernelArg(kernel[5] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_modf_withoutDD)");

	//set kernel_lgamma_withDD Argument
	status |= clSetKernelArg(kernel[6] , 0, sizeof(cl_mem),
			(void*) &result_lgamma_withDD);
	status |= clSetKernelArg(kernel[6] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_lgamma_withDD)");

	//set kernel_lgamma_withoutDD Argument
	status |= clSetKernelArg(kernel[7] , 0, sizeof(cl_mem),
			(void*) &result_lgamma_withoutDD);
	status |= clSetKernelArg(kernel[7] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_lgamma_withoutDD)");

	int i = 0;
	int gws, lws;
	for (gws = 1024; gws <= 65536 * 8; gws *= 2)
		for (lws = 64; lws <= 256; lws *= 2) {
			float executionTime_log1p_withDD_max = 0.0;
			float executionTime_log1p_withDD_avg = 0.0;
			float executionTime_log1p_withDD_min = 999999999.0;

			float executionTime_log1p_withoutDD_max = 0.0;
			float executionTime_log1p_withoutDD_avg = 0.0;
			float executionTime_log1p_withoutDD_min = 999999999.0;

			float executionTime_logb_withDD_max = 0.0;
			float executionTime_logb_withDD_avg = 0.0;
			float executionTime_logb_withDD_min = 999999999.0;

			float executionTime_logb_withoutDD_max = 0.0;
			float executionTime_logb_withoutDD_avg = 0.0;
			float executionTime_logb_withoutDD_min = 999999999.0;

			float executionTime_modf_withDD_max = 0.0;
			float executionTime_modf_withDD_avg = 0.0;
			float executionTime_modf_withDD_min = 999999999.0;

			float executionTime_modf_withoutDD_max = 0.0;
			float executionTime_modf_withoutDD_avg = 0.0;
			float executionTime_modf_withoutDD_min = 999999999.0;

			float executionTime_lgamma_withDD_max = 0.0;
			float executionTime_lgamma_withDD_avg = 0.0;
			float executionTime_lgamma_withDD_min = 999999999.0;

			float executionTime_lgamma_withoutDD_max = 0.0;
			float executionTime_lgamma_withoutDD_avg = 0.0;
			float executionTime_lgamma_withoutDD_min = 999999999.0;

			szGlobalWorkSize = gws;
			szLocalWorkSize = lws;
			printf("-----------------------------------------------------\n");
			printf("Set gws = %d , lws = %d\n", gws, lws);

			//launch kernel_log1p_withDD
			if (!strcmp(kernelname.c_str(), "log1p_withDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str()<< vectorSize <<std::endl;
				printf("Begin to launch kernel_log1p_withDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[0] ,
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_log1p_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time kernel_log1p
					status = clWaitForEvents(1, &event_log1p_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_log1p_withDD, end_log1p_withDD;
					status = clGetEventProfilingInfo(event_log1p_withDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_log1p_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_log1p_withDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_log1p_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					float executionTime_log1p_withDD = (end_log1p_withDD
							- start_log1p_withDD);
					if (executionTime_log1p_withDD_max
							< executionTime_log1p_withDD) {
						executionTime_log1p_withDD_max = executionTime_log1p_withDD;
					}
					if (executionTime_log1p_withDD_min
							> executionTime_log1p_withDD) {
						executionTime_log1p_withDD_min = executionTime_log1p_withDD;
					}
					executionTime_log1p_withDD_avg += executionTime_log1p_withDD;

				}
				executionTime_log1p_withDD_avg = (executionTime_log1p_withDD_avg
						- executionTime_log1p_withDD_max
						- executionTime_log1p_withDD_min) / (iterations - 2);
				size_t time_log1p_withDD=0;
					time_log1p_withDD= 32 * szForNum * vectorSize;
				float Gflops_log1p_withDD =
						(time_log1p_withDD * szGlobalWorkSize)
								/ executionTime_log1p_withDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_log1p_withDD,
						CL_TRUE, 0, sizeof(cl_mem), log1p_withDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-log1p_withDD : %f\n", Gflops_log1p_withDD);
				printf("Result-log1p_withDD   :   %f\n\n", *((float*)log1p_withDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_log1p_withDD > log1p_withDD_maxGflops){
						log1p_withDD_maxGflops = Gflops_log1p_withDD;
				}
			}

			//launch kernel_log1p_withoutDD
			if (!strcmp(kernelname.c_str(), "log1p_withoutDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str()<< vectorSize <<std::endl;
				printf("Begin to launch kernel_log1p_withoutDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[1] ,
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_log1p_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time kernel_log1p
					status = clWaitForEvents(1, &event_log1p_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_log1p_withoutDD, end_log1p_withoutDD;
					status = clGetEventProfilingInfo(event_log1p_withoutDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_log1p_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_log1p_withoutDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_log1p_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					float executionTime_log1p_withoutDD = (end_log1p_withoutDD
							- start_log1p_withoutDD);
					if (executionTime_log1p_withoutDD_max
							< executionTime_log1p_withoutDD) {
						executionTime_log1p_withoutDD_max = executionTime_log1p_withoutDD;
					}
					if (executionTime_log1p_withoutDD_min
							> executionTime_log1p_withoutDD) {
						executionTime_log1p_withoutDD_min = executionTime_log1p_withoutDD;
					}
					executionTime_log1p_withoutDD_avg += executionTime_log1p_withoutDD;

				}
				executionTime_log1p_withoutDD_avg = (executionTime_log1p_withoutDD_avg
						- executionTime_log1p_withoutDD_max
						- executionTime_log1p_withoutDD_min) / (iterations - 2);
				size_t time_log1p_withoutDD=0;
				if(vectorSize!=16)
					time_log1p_withoutDD= 7 * 100 * vectorSize;
				else
					time_log1p_withoutDD= 7 * 40 * vectorSize;
				float Gflops_log1p_withoutDD =
						(time_log1p_withoutDD * szGlobalWorkSize)
								/ executionTime_log1p_withoutDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_log1p_withoutDD,
						CL_TRUE, 0, sizeof(cl_mem), log1p_withoutDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-log1p_withoutDD : %f\n", Gflops_log1p_withoutDD);
				printf("Result-log1p_withoutDD   :   %f\n\n", *((float*)log1p_withoutDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_log1p_withoutDD > log1p_withoutDD_maxGflops){
						log1p_withoutDD_maxGflops = Gflops_log1p_withoutDD;
				}

			}

			//launch kernel_logb_withDD
			if (!strcmp(kernelname.c_str(), "logb_withDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str()<< vectorSize <<std::endl;
				printf("Begin to launch kernel_logb_withDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[2] ,
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_logb_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time kernel_logb
					status = clWaitForEvents(1, &event_logb_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_logb_withDD, end_logb_withDD;
					status = clGetEventProfilingInfo(event_logb_withDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_logb_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_logb_withDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_logb_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					float executionTime_logb_withDD = (end_logb_withDD
							- start_logb_withDD);
					if (executionTime_logb_withDD_max
							< executionTime_logb_withDD) {
						executionTime_logb_withDD_max = executionTime_logb_withDD;
					}
					if (executionTime_logb_withDD_min
							> executionTime_logb_withDD) {
						executionTime_logb_withDD_min = executionTime_logb_withDD;
					}
					executionTime_logb_withDD_avg += executionTime_logb_withDD;

				}
				executionTime_logb_withDD_avg = (executionTime_logb_withDD_avg
						- executionTime_logb_withDD_max
						- executionTime_logb_withDD_min) / (iterations - 2);
				size_t time_logb_withDD=0;
					time_logb_withDD= 64*szForNum * vectorSize;
				float Gflops_logb_withDD =
						(time_logb_withDD * szGlobalWorkSize)
								/ executionTime_logb_withDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_logb_withDD,
						CL_TRUE, 0, sizeof(cl_mem), logb_withDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-logb_withDD : %f\n", Gflops_logb_withDD);
				printf("Result-logb_withDD   :   %f\n\n", *((float*)logb_withDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_logb_withDD > logb_withDD_maxGflops){
						logb_withDD_maxGflops = Gflops_logb_withDD;
				}
			}

			//launch kernel_logb_withoutDD
			if (!strcmp(kernelname.c_str(), "logb_withoutDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str()<< vectorSize <<std::endl;
				printf("Begin to launch kernel_logb_withoutDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[3] ,
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_logb_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time kernel_logb
					status = clWaitForEvents(1, &event_logb_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_logb_withoutDD, end_logb_withoutDD;
					status = clGetEventProfilingInfo(event_logb_withoutDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_logb_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_logb_withoutDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_logb_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					float executionTime_logb_withoutDD = (end_logb_withoutDD
							- start_logb_withoutDD);
					if (executionTime_logb_withoutDD_max
							< executionTime_logb_withoutDD) {
						executionTime_logb_withoutDD_max = executionTime_logb_withoutDD;
					}
					if (executionTime_logb_withoutDD_min
							> executionTime_logb_withoutDD) {
						executionTime_logb_withoutDD_min = executionTime_logb_withoutDD;
					}
					executionTime_logb_withoutDD_avg += executionTime_logb_withoutDD;

				}
				executionTime_logb_withoutDD_avg = (executionTime_logb_withoutDD_avg
						- executionTime_logb_withoutDD_max
						- executionTime_logb_withoutDD_min) / (iterations - 2);
				size_t time_logb_withoutDD=0;
				time_logb_withoutDD=  30 * 10 *szForNum* vectorSize;

				float Gflops_logb_withoutDD =
						(time_logb_withoutDD * szGlobalWorkSize)
								/ executionTime_logb_withoutDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_logb_withoutDD,
						CL_TRUE, 0, sizeof(cl_mem), logb_withoutDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-logb_withoutDD : %f\n", Gflops_logb_withoutDD);
				printf("Result-logb_withoutDD   :   %f\n\n", *((float*)logb_withoutDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_logb_withoutDD > logb_withoutDD_maxGflops){
						logb_withoutDD_maxGflops = Gflops_logb_withoutDD;
				}

			}

			//launch kernel_modf_withDD
			if (!strcmp(kernelname.c_str(), "modf_withDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str()<< vectorSize <<std::endl;
				printf("Begin to launch kernel_modf_withDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[4] ,
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_modf_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time kernel_modf
					status = clWaitForEvents(1, &event_modf_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_modf_withDD, end_modf_withDD;
					status = clGetEventProfilingInfo(event_modf_withDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_modf_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_modf_withDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_modf_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					float executionTime_modf_withDD = (end_modf_withDD
							- start_modf_withDD);
					if (executionTime_modf_withDD_max
							< executionTime_modf_withDD) {
						executionTime_modf_withDD_max = executionTime_modf_withDD;
					}
					if (executionTime_modf_withDD_min
							> executionTime_modf_withDD) {
						executionTime_modf_withDD_min = executionTime_modf_withDD;
					}
					executionTime_modf_withDD_avg += executionTime_modf_withDD;

				}
				executionTime_modf_withDD_avg = (executionTime_modf_withDD_avg
						- executionTime_modf_withDD_max
						- executionTime_modf_withDD_min) / (iterations - 2);
				size_t time_modf_withDD=0;
				time_modf_withDD= 128 * szForNum * vectorSize;
				float Gflops_modf_withDD =
						(time_modf_withDD * szGlobalWorkSize)
								/ executionTime_modf_withDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_modf_withDD,
						CL_TRUE, 0, sizeof(cl_mem), modf_withDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-modf_withDD : %f\n", Gflops_modf_withDD);
				printf("Result-modf_withDD   :   %f\n\n", *((float*)modf_withDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_modf_withDD > modf_withDD_maxGflops){
						modf_withDD_maxGflops = Gflops_modf_withDD;
				}
			}

			//launch kernel_modf_withoutDD
			if (!strcmp(kernelname.c_str(), "modf_withoutDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str()<< vectorSize <<std::endl;
				printf("Begin to launch kernel_modf_withoutDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[5] ,
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_modf_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time kernel_modf
					status = clWaitForEvents(1, &event_modf_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_modf_withoutDD, end_modf_withoutDD;
					status = clGetEventProfilingInfo(event_modf_withoutDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_modf_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_modf_withoutDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_modf_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					float executionTime_modf_withoutDD = (end_modf_withoutDD
							- start_modf_withoutDD);
					if (executionTime_modf_withoutDD_max
							< executionTime_modf_withoutDD) {
						executionTime_modf_withoutDD_max = executionTime_modf_withoutDD;
					}
					if (executionTime_modf_withoutDD_min
							> executionTime_modf_withoutDD) {
						executionTime_modf_withoutDD_min = executionTime_modf_withoutDD;
					}
					executionTime_modf_withoutDD_avg += executionTime_modf_withoutDD;

				}
				executionTime_modf_withoutDD_avg = (executionTime_modf_withoutDD_avg
						- executionTime_modf_withoutDD_max
						- executionTime_modf_withoutDD_min) / (iterations - 2);
				size_t time_modf_withoutDD=0;
				time_modf_withoutDD= 30 * 10 * szForNum * vectorSize;
				float Gflops_modf_withoutDD =
						(time_modf_withoutDD * szGlobalWorkSize)
								/ executionTime_modf_withoutDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_modf_withoutDD,
						CL_TRUE, 0, sizeof(cl_mem), modf_withoutDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-modf_withoutDD : %f\n", Gflops_modf_withoutDD);
				printf("Result-modf_withoutDD   :   %f\n\n", *((float*)modf_withoutDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_modf_withoutDD > modf_withoutDD_maxGflops){
						modf_withoutDD_maxGflops = Gflops_modf_withoutDD;
				}
			}

			//launch kernel_lgamma_withDD
			if (!strcmp(kernelname.c_str(), "lgamma_withDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str()<< vectorSize <<std::endl;
				printf("Begin to launch kernel_lgamma_withDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[6] ,
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_lgamma_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time kernel_lgamma
					status = clWaitForEvents(1, &event_lgamma_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_lgamma_withDD, end_lgamma_withDD;
					status = clGetEventProfilingInfo(event_lgamma_withDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_lgamma_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_lgamma_withDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_lgamma_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					float executionTime_lgamma_withDD = (end_lgamma_withDD
							- start_lgamma_withDD);
					if (executionTime_lgamma_withDD_max
							< executionTime_lgamma_withDD) {
						executionTime_lgamma_withDD_max = executionTime_lgamma_withDD;
					}
					if (executionTime_lgamma_withDD_min
							> executionTime_lgamma_withDD) {
						executionTime_lgamma_withDD_min = executionTime_lgamma_withDD;
					}
					executionTime_lgamma_withDD_avg += executionTime_lgamma_withDD;

				}
				executionTime_lgamma_withDD_avg = (executionTime_lgamma_withDD_avg
						- executionTime_lgamma_withDD_max
						- executionTime_lgamma_withDD_min) / (iterations - 2);
				size_t time_lgamma_withDD=0;
					time_lgamma_withDD= 32 * szForNum * vectorSize;
				float Gflops_lgamma_withDD =
						(time_lgamma_withDD * szGlobalWorkSize)
								/ executionTime_lgamma_withDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_lgamma_withDD,
						CL_TRUE, 0, sizeof(cl_mem), lgamma_withDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-lgamma_withDD : %f\n", Gflops_lgamma_withDD);
				printf("Result-lgamma_withDD   :   %f\n\n", *((float*)lgamma_withDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_lgamma_withDD > lgamma_withDD_maxGflops){
						lgamma_withDD_maxGflops = Gflops_lgamma_withDD;
				}
			}

			//launch kernel_lgamma_withoutDD
			if (!strcmp(kernelname.c_str(), "lgamma_withoutDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str()<< vectorSize <<std::endl;
				printf("Begin to launch kernel_lgamma_withoutDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[7] ,
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_lgamma_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time kernel_lgamma
					status = clWaitForEvents(1, &event_lgamma_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_lgamma_withoutDD, end_lgamma_withoutDD;
					status = clGetEventProfilingInfo(event_lgamma_withoutDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_lgamma_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_lgamma_withoutDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_lgamma_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					float executionTime_lgamma_withoutDD = (end_lgamma_withoutDD
							- start_lgamma_withoutDD);
					if (executionTime_lgamma_withoutDD_max
							< executionTime_lgamma_withoutDD) {
						executionTime_lgamma_withoutDD_max = executionTime_lgamma_withoutDD;
					}
					if (executionTime_lgamma_withoutDD_min
							> executionTime_lgamma_withoutDD) {
						executionTime_lgamma_withoutDD_min = executionTime_lgamma_withoutDD;
					}
					executionTime_lgamma_withoutDD_avg += executionTime_lgamma_withoutDD;

				}
				executionTime_lgamma_withoutDD_avg = (executionTime_lgamma_withoutDD_avg
						- executionTime_lgamma_withoutDD_max
						- executionTime_lgamma_withoutDD_min) / (iterations - 2);
				size_t time_lgamma_withoutDD=0;
				time_lgamma_withoutDD= 10 * 10 * vectorSize;
				float Gflops_lgamma_withoutDD =
						(time_lgamma_withoutDD * szGlobalWorkSize)
								/ executionTime_lgamma_withoutDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_lgamma_withoutDD,
						CL_TRUE, 0, sizeof(cl_mem), lgamma_withoutDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-lgamma_withoutDD : %f\n", Gflops_lgamma_withoutDD);
				printf("Result-lgamma_withoutDD   :   %f\n\n", *((float*)lgamma_withoutDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_lgamma_withoutDD > lgamma_withoutDD_maxGflops){
						lgamma_withoutDD_maxGflops = Gflops_lgamma_withoutDD;
				}

			}
	}	
	printf("log1p_withDD_maxGflops = %f\n",log1p_withDD_maxGflops);
	printf("log1p_withoutDD_maxGflops = %f\n",log1p_withoutDD_maxGflops);
	printf("logb_withDD_maxGflops = %f\n",logb_withDD_maxGflops);
	printf("logb_withoutDD_maxGflops = %f\n",logb_withoutDD_maxGflops);
	printf("modf_withDD_maxGflops = %f\n",modf_withDD_maxGflops);
	printf("modf_withoutDD_maxGflops = %f\n",modf_withoutDD_maxGflops);
	printf("lgamma_withDD_maxGflops = %f\n",lgamma_withDD_maxGflops);
	printf("lgamma_withoutDD_maxGflops = %f\n",lgamma_withoutDD_maxGflops);

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


