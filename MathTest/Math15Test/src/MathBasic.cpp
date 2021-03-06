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
   	std::stringstream ss(s);
    	ss << "kernel_erfc_withDD";
   	ss << vectorSize;
	// Create the cKermel_kernel_erfc_withDD
	kernel[0]  = clCreateKernel(program, ss.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_erfc_withDD)");
	
	std::stringstream erfc_withoutDD(s);
	erfc_withoutDD << "kernel_erfc_withoutDD";
	erfc_withoutDD << vectorSize;
	//dumpPTXCode(context,program,erfc_withoutDD.str().c_str());
	// Create the cKermel_kernel_erfc_withoutDD
	kernel[1]  = clCreateKernel(program, erfc_withoutDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_erfc_withoutDD)");

	std::stringstream erf_withDD(s);
	erf_withDD << "kernel_erf_withDD";
	erf_withDD << vectorSize;
	//dumpPTXCode(context,program,erf_withDD.str().c_str());
	// Create the cKermel_kernel_erf_withDD
	kernel[2]  = clCreateKernel(program, erf_withDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_erf_withDD)");

	std::stringstream erf_withoutDD(s);
	erf_withoutDD << "kernel_erf_withoutDD";
	erf_withoutDD << vectorSize;
	//dumpPTXCode(context,program,erf_withoutDD.str().c_str());
	// Create the cKermel_kernel_erf_withoutDD
	kernel[3]  = clCreateKernel(program, erf_withoutDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_erf_withoutDD)");

	std::stringstream expm1_withDD(s);
	expm1_withDD << "kernel_expm1_withDD";
	expm1_withDD << vectorSize;
	//dumpPTXCode(context,program,expm1_withDD.str().c_str());
	// Create the cKermel_kernel_expm1_withDD
	kernel[4]  = clCreateKernel(program, expm1_withDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_expm1_withDD)");

	std::stringstream expm1_withoutDD(s);
	expm1_withoutDD << "kernel_expm1_withoutDD";
	expm1_withoutDD << vectorSize;
	//dumpPTXCode(context,program,expm1_withoutDD.str().c_str());
	// Create the cKermel_kernel_expm1_withoutDD
	kernel[5]  = clCreateKernel(program, expm1_withoutDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_expm1_withoutDD)");

	std::stringstream exp10_withDD(s);
	exp10_withDD << "kernel_exp10_withDD";
	exp10_withDD << vectorSize;
	//dumpPTXCode(context,program,exp10_withDD.str().c_str());
	// Create the cKermel_kernel_exp10_withDD
	kernel[6]  = clCreateKernel(program, exp10_withDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_exp10_withDD)");

	std::stringstream exp10_withoutDD(s);
	exp10_withoutDD << "kernel_exp10_withoutDD";
	exp10_withoutDD << vectorSize;
	//dumpPTXCode(context,program,exp10_withoutDD.str().c_str());
	// Create the cKermel_kernel_exp10_withoutDD
	kernel[7]  = clCreateKernel(program, exp10_withoutDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_exp10_withoutDD)")
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
	cl_event event_erfc_withDD, event_erfc_withoutDD;
	cl_event event_erf_withDD, event_erf_withoutDD;
	cl_event event_expm1_withDD, event_expm1_withoutDD;
	cl_event event_exp10_withDD, event_exp10_withoutDD;

	//Create Variable for story result reading from device to host
	void *erfc_withDD_num, *erfc_withoutDD_num;
	void *erf_withDD_num, *erf_withoutDD_num;
	void *expm1_withDD_num, *expm1_withoutDD_num;
	void *exp10_withDD_num, *exp10_withoutDD_num;

	erfc_withDD_num = (void *) malloc(sizeof(cl_float));
	erfc_withoutDD_num = (void *) malloc(sizeof(cl_float));
	erf_withDD_num = (void *) malloc(sizeof(cl_float));
	erf_withoutDD_num = (void *) malloc(sizeof(cl_float));
	expm1_withDD_num = (void *) malloc(sizeof(cl_float));
	expm1_withoutDD_num = (void *) malloc(sizeof(cl_float));
	exp10_withDD_num = (void *) malloc(sizeof(cl_float));
	exp10_withoutDD_num = (void *) malloc(sizeof(cl_float));

	float erfc_withDD_maxGflops = 0.0;
	float erfc_withoutDD_maxGflops = 0.0;
	float erf_withDD_maxGflops = 0.0;
	float erf_withoutDD_maxGflops = 0.0;
	float expm1_withDD_maxGflops = 0.0;
	float expm1_withoutDD_maxGflops = 0.0;
	float exp10_withDD_maxGflops = 0.0;
	float exp10_withoutDD_maxGflops = 0.0;

	//create buffer

	cl_mem result_erfc_withDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_erfc_withoutDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_erf_withDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_erf_withoutDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_expm1_withDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_expm1_withoutDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_exp10_withDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_exp10_withoutDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);

	//set kernel_erfc_withDD Argument
	status |= clSetKernelArg(kernel[0] , 0, sizeof(cl_mem),
			(void*) &result_erfc_withDD);
	status |= clSetKernelArg(kernel[0] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_erfc_withDD)");
	
	//set kernel_erfc_withoutDD Argument
	status |= clSetKernelArg(kernel[1] , 0, sizeof(cl_mem),
			(void*) &result_erfc_withoutDD);
	status |= clSetKernelArg(kernel[1] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_erfc_withoutDD)");

	//set kernel_erf_withDD Argument
	status |= clSetKernelArg(kernel[2] , 0, sizeof(cl_mem),
			(void*) &result_erf_withDD);
	status |= clSetKernelArg(kernel[2] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_erf_withDD)");

	//set kernel_erf_withoutDD Argument
	status |= clSetKernelArg(kernel[3] , 0, sizeof(cl_mem),
			(void*) &result_erf_withoutDD);
	status |= clSetKernelArg(kernel[3] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_erf_withoutDD)");

	//set kernel_expm1_withDD Argument
	status |= clSetKernelArg(kernel[4] , 0, sizeof(cl_mem),
			(void*) &result_expm1_withDD);
	status |= clSetKernelArg(kernel[4] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_expm1_withDD)");

	//set kernel_expm1_withoutDD Argument
	status |= clSetKernelArg(kernel[5] , 0, sizeof(cl_mem),
			(void*) &result_expm1_withoutDD);
	status |= clSetKernelArg(kernel[5] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_expm1_withoutDD)");

	//set kernel_exp10_withDD Argument
	status |= clSetKernelArg(kernel[6] , 0, sizeof(cl_mem),
			(void*) &result_exp10_withDD);
	status |= clSetKernelArg(kernel[6] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_exp10_withDD)");
	
	//set kernel_exp10_withoutDD Argument
	status |= clSetKernelArg(kernel[7] , 0, sizeof(cl_mem),
			(void*) &result_exp10_withoutDD);
	status |= clSetKernelArg(kernel[7] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_exp10_withoutDD)");

	int i = 0;
	int gws, lws;
	for (gws = 1024; gws <= 65536 * 8; gws *= 2)
		for (lws = 64; lws <= 256; lws *= 2) {
			
			float executionTime_erfc_withDD_max = 0.0;
			float executionTime_erfc_withDD_avg = 0.0;
			float executionTime_erfc_withDD_min = 999999999.0;

			float executionTime_erfc_withoutDD_max = 0.0;
			float executionTime_erfc_withoutDD_avg = 0.0;
			float executionTime_erfc_withoutDD_min = 999999999.0;

			float executionTime_erf_withDD_max = 0.0;
			float executionTime_erf_withDD_avg = 0.0;
			float executionTime_erf_withDD_min = 999999999.0;

			float executionTime_erf_withoutDD_max = 0.0;
			float executionTime_erf_withoutDD_avg = 0.0;
			float executionTime_erf_withoutDD_min = 999999999.0;

			float executionTime_expm1_withDD_max = 0.0;
			float executionTime_expm1_withDD_avg = 0.0;
			float executionTime_expm1_withDD_min = 999999999.0;

			float executionTime_expm1_withoutDD_max = 0.0;
			float executionTime_expm1_withoutDD_avg = 0.0;
			float executionTime_expm1_withoutDD_min = 999999999.0;

			float executionTime_exp10_withDD_max = 0.0;
			float executionTime_exp10_withDD_avg = 0.0;
			float executionTime_exp10_withDD_min = 999999999.0;

			float executionTime_exp10_withoutDD_max = 0.0;
			float executionTime_exp10_withoutDD_avg = 0.0;
			float executionTime_exp10_withoutDD_min = 999999999.0;

			szGlobalWorkSize = gws;
			szLocalWorkSize = lws;
			printf("-----------------------------------------------------\n");
			printf("Set gws = %d , lws = %d\n", gws, lws);
			
			//launch kernel_erfc_withDD
			if (!strcmp(kernelname.c_str(), "erfc_withDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str()<< vectorSize <<std::endl;
				printf("Begin to launch kernel_erfc_withDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[0] ,
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_erfc_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time kernel_erfc
					status = clWaitForEvents(1, &event_erfc_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_erfc_withDD, end_erfc_withDD;
					status = clGetEventProfilingInfo(event_erfc_withDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_erfc_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_erfc_withDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_erfc_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					float executionTime_erfc_withDD = (end_erfc_withDD
							- start_erfc_withDD);
					if (executionTime_erfc_withDD_max
							< executionTime_erfc_withDD) {
						executionTime_erfc_withDD_max = executionTime_erfc_withDD;
					}
					if (executionTime_erfc_withDD_min
							> executionTime_erfc_withDD) {
						executionTime_erfc_withDD_min = executionTime_erfc_withDD;
					}
					executionTime_erfc_withDD_avg += executionTime_erfc_withDD;

				}
				executionTime_erfc_withDD_avg = (executionTime_erfc_withDD_avg
						- executionTime_erfc_withDD_max
						- executionTime_erfc_withDD_min) / (iterations - 2);
				size_t time_erfc_withDD=0;
				time_erfc_withDD= 128 * szForNum * vectorSize;
				float Gflops_erfc_withDD =
						(time_erfc_withDD * szGlobalWorkSize)
								/ executionTime_erfc_withDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_erfc_withDD,
						CL_TRUE, 0, sizeof(cl_mem), erfc_withDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-erfc_withDD : %f\n", Gflops_erfc_withDD);
				printf("Result-erfc_withDD   :   %f\n\n", *((float*)erfc_withDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_erfc_withDD > erfc_withDD_maxGflops){
						erfc_withDD_maxGflops = Gflops_erfc_withDD;
				}
			}

			//launch kernel_erfc_withoutDD
			if (!strcmp(kernelname.c_str(), "erfc_withoutDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str()<< vectorSize <<std::endl;
				printf("Begin to launch kernel_erfc_withoutDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[1] ,
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_erfc_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time kernel_erfc
					status = clWaitForEvents(1, &event_erfc_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_erfc_withoutDD, end_erfc_withoutDD;
					status = clGetEventProfilingInfo(event_erfc_withoutDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_erfc_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_erfc_withoutDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_erfc_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					float executionTime_erfc_withoutDD = (end_erfc_withoutDD
							- start_erfc_withoutDD);
					if (executionTime_erfc_withoutDD_max
							< executionTime_erfc_withoutDD) {
						executionTime_erfc_withoutDD_max = executionTime_erfc_withoutDD;
					}
					if (executionTime_erfc_withoutDD_min
							> executionTime_erfc_withoutDD) {
						executionTime_erfc_withoutDD_min = executionTime_erfc_withoutDD;
					}
					executionTime_erfc_withoutDD_avg += executionTime_erfc_withoutDD;

				}
				executionTime_erfc_withoutDD_avg = (executionTime_erfc_withoutDD_avg
						- executionTime_erfc_withoutDD_max
						- executionTime_erfc_withoutDD_min) / (iterations - 2);
				size_t time_erfc_withoutDD=0;
				time_erfc_withoutDD= 7 * 10 * szForNum * vectorSize;
				float Gflops_erfc_withoutDD =
						(time_erfc_withoutDD * szGlobalWorkSize)
								/ executionTime_erfc_withoutDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_erfc_withoutDD,
						CL_TRUE, 0, sizeof(cl_mem), erfc_withoutDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-erfc_withoutDD : %f\n", Gflops_erfc_withoutDD);
				printf("Result-erfc_withoutDD   :   %f\n\n", *((float*)erfc_withoutDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_erfc_withoutDD > erfc_withoutDD_maxGflops){
						erfc_withoutDD_maxGflops = Gflops_erfc_withoutDD;
				}
			}

			//launch kernel_erf_withDD
			if (!strcmp(kernelname.c_str(), "erf_withDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str()<< vectorSize <<std::endl;
				printf("Begin to launch kernel_erf_withDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[2] ,
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_erf_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time kernel_erf
					status = clWaitForEvents(1, &event_erf_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_erf_withDD, end_erf_withDD;
					status = clGetEventProfilingInfo(event_erf_withDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_erf_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_erf_withDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_erf_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					float executionTime_erf_withDD = (end_erf_withDD
							- start_erf_withDD);
					if (executionTime_erf_withDD_max
							< executionTime_erf_withDD) {
						executionTime_erf_withDD_max = executionTime_erf_withDD;
					}
					if (executionTime_erf_withDD_min
							> executionTime_erf_withDD) {
						executionTime_erf_withDD_min = executionTime_erf_withDD;
					}
					executionTime_erf_withDD_avg += executionTime_erf_withDD;

				}
				executionTime_erf_withDD_avg = (executionTime_erf_withDD_avg
						- executionTime_erf_withDD_max
						- executionTime_erf_withDD_min) / (iterations - 2);
				size_t time_erf_withDD=0;
				if(vectorSize!=16)
					time_erf_withDD= 64 * szForNum * vectorSize;
				else
					time_erf_withDD= 32 * szForNum * vectorSize;
				float Gflops_erf_withDD =
						(time_erf_withDD * szGlobalWorkSize)
								/ executionTime_erf_withDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_erf_withDD,
						CL_TRUE, 0, sizeof(cl_mem), erf_withDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-erf_withDD : %f\n", Gflops_erf_withDD);
				printf("Result-erf_withDD   :   %f\n\n", *((float*)erf_withDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_erf_withDD > erf_withDD_maxGflops){
						erf_withDD_maxGflops = Gflops_erf_withDD;
				}
			}

			//launch kernel_erf_withoutDD
			if (!strcmp(kernelname.c_str(), "erf_withoutDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str()<< vectorSize <<std::endl;
				printf("Begin to launch kernel_erf_withoutDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[3] ,
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_erf_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time kernel_erf
					status = clWaitForEvents(1, &event_erf_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_erf_withoutDD, end_erf_withoutDD;
					status = clGetEventProfilingInfo(event_erf_withoutDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_erf_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_erf_withoutDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_erf_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					float executionTime_erf_withoutDD = (end_erf_withoutDD
							- start_erf_withoutDD);
					if (executionTime_erf_withoutDD_max
							< executionTime_erf_withoutDD) {
						executionTime_erf_withoutDD_max = executionTime_erf_withoutDD;
					}
					if (executionTime_erf_withoutDD_min
							> executionTime_erf_withoutDD) {
						executionTime_erf_withoutDD_min = executionTime_erf_withoutDD;
					}
					executionTime_erf_withoutDD_avg += executionTime_erf_withoutDD;

				}
				executionTime_erf_withoutDD_avg = (executionTime_erf_withoutDD_avg
						- executionTime_erf_withoutDD_max
						- executionTime_erf_withoutDD_min) / (iterations - 2);
				size_t time_erf_withoutDD=0;
				time_erf_withoutDD= 7 * 10* szForNum * vectorSize;
				float Gflops_erf_withoutDD =
						(time_erf_withoutDD * szGlobalWorkSize)
								/ executionTime_erf_withoutDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_erf_withoutDD,
						CL_TRUE, 0, sizeof(cl_mem), erf_withoutDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-erf_withoutDD : %f\n", Gflops_erf_withoutDD);
				printf("Result-erf_withoutDD   :   %f\n\n", *((float*)erf_withoutDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_erf_withoutDD > erf_withoutDD_maxGflops){
						erf_withoutDD_maxGflops = Gflops_erf_withoutDD;
				}

			}

			//launch kernel_expm1_withDD
			if (!strcmp(kernelname.c_str(), "expm1_withDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str()<< vectorSize <<std::endl;
				printf("Begin to launch kernel_expm1_withDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[4] ,
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_expm1_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time kernel_expm1
					status = clWaitForEvents(1, &event_expm1_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_expm1_withDD, end_expm1_withDD;
					status = clGetEventProfilingInfo(event_expm1_withDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_expm1_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_expm1_withDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_expm1_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					float executionTime_expm1_withDD = (end_expm1_withDD
							- start_expm1_withDD);
					if (executionTime_expm1_withDD_max
							< executionTime_expm1_withDD) {
						executionTime_expm1_withDD_max = executionTime_expm1_withDD;
					}
					if (executionTime_expm1_withDD_min
							> executionTime_expm1_withDD) {
						executionTime_expm1_withDD_min = executionTime_expm1_withDD;
					}
					executionTime_expm1_withDD_avg += executionTime_expm1_withDD;

				}
				executionTime_expm1_withDD_avg = (executionTime_expm1_withDD_avg
						- executionTime_expm1_withDD_max
						- executionTime_expm1_withDD_min) / (iterations - 2);
				size_t time_expm1_withDD=0;
					time_expm1_withDD= 32*10*szForNum * vectorSize;
				float Gflops_expm1_withDD =
						(time_expm1_withDD * szGlobalWorkSize)
								/ executionTime_expm1_withDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_expm1_withDD,
						CL_TRUE, 0, sizeof(cl_mem), expm1_withDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-expm1_withDD : %f\n", Gflops_expm1_withDD);
				printf("Result-expm1_withDD   :   %f\n\n", *((float*)expm1_withDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_expm1_withDD > expm1_withDD_maxGflops){
						expm1_withDD_maxGflops = Gflops_expm1_withDD;
				}
			}

			//launch kernel_expm1_withoutDD
			if (!strcmp(kernelname.c_str(), "expm1_withoutDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str()<< vectorSize <<std::endl;
				printf("Begin to launch kernel_expm1_withoutDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[5] ,
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_expm1_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time kernel_expm1
					status = clWaitForEvents(1, &event_expm1_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_expm1_withoutDD, end_expm1_withoutDD;
					status = clGetEventProfilingInfo(event_expm1_withoutDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_expm1_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_expm1_withoutDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_expm1_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					float executionTime_expm1_withoutDD = (end_expm1_withoutDD
							- start_expm1_withoutDD);
					if (executionTime_expm1_withoutDD_max
							< executionTime_expm1_withoutDD) {
						executionTime_expm1_withoutDD_max = executionTime_expm1_withoutDD;
					}
					if (executionTime_expm1_withoutDD_min
							> executionTime_expm1_withoutDD) {
						executionTime_expm1_withoutDD_min = executionTime_expm1_withoutDD;
					}
					executionTime_expm1_withoutDD_avg += executionTime_expm1_withoutDD;

				}
				executionTime_expm1_withoutDD_avg = (executionTime_expm1_withoutDD_avg
						- executionTime_expm1_withoutDD_max
						- executionTime_expm1_withoutDD_min) / (iterations - 2);
				size_t time_expm1_withoutDD=0;
				if(vectorSize==1||vectorSize==2||vectorSize==4||vectorSize==8)
					time_expm1_withoutDD=  7*10* vectorSize;
				if(vectorSize==16)
					time_expm1_withoutDD=  7*10 * vectorSize;
				float Gflops_expm1_withoutDD =
						(time_expm1_withoutDD * szGlobalWorkSize)
								/ executionTime_expm1_withoutDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_expm1_withoutDD,
						CL_TRUE, 0, sizeof(cl_mem), expm1_withoutDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-expm1_withoutDD : %f\n", Gflops_expm1_withoutDD);
				printf("Result-expm1_withoutDD   :   %f\n\n", *((float*)expm1_withoutDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_expm1_withoutDD > expm1_withoutDD_maxGflops){
						expm1_withoutDD_maxGflops = Gflops_expm1_withoutDD;
				}

			}

			//launch kernel_exp10_withDD
			if (!strcmp(kernelname.c_str(), "exp10_withDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str()<< vectorSize <<std::endl;
				printf("Begin to launch kernel_exp10_withDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[6] ,
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_exp10_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time kernel_exp10
					status = clWaitForEvents(1, &event_exp10_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_exp10_withDD, end_exp10_withDD;
					status = clGetEventProfilingInfo(event_exp10_withDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_exp10_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_exp10_withDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_exp10_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					float executionTime_exp10_withDD = (end_exp10_withDD
							- start_exp10_withDD);
					if (executionTime_exp10_withDD_max
							< executionTime_exp10_withDD) {
						executionTime_exp10_withDD_max = executionTime_exp10_withDD;
					}
					if (executionTime_exp10_withDD_min
							> executionTime_exp10_withDD) {
						executionTime_exp10_withDD_min = executionTime_exp10_withDD;
					}
					executionTime_exp10_withDD_avg += executionTime_exp10_withDD;

				}
				executionTime_exp10_withDD_avg = (executionTime_exp10_withDD_avg
						- executionTime_exp10_withDD_max
						- executionTime_exp10_withDD_min) / (iterations - 2);
				size_t time_exp10_withDD=0;
				time_exp10_withDD= 32 * szForNum * vectorSize;
				float Gflops_exp10_withDD =
						(time_exp10_withDD * szGlobalWorkSize)
								/ executionTime_exp10_withDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_exp10_withDD,
						CL_TRUE, 0, sizeof(cl_mem), exp10_withDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-exp10_withDD : %f\n", Gflops_exp10_withDD);
				printf("Result-exp10_withDD   :   %f\n\n", *((float*)exp10_withDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_exp10_withDD > exp10_withDD_maxGflops){
						exp10_withDD_maxGflops = Gflops_exp10_withDD;
				}
			}

			//launch kernel_exp10_withoutDD
			if (!strcmp(kernelname.c_str(), "exp10_withoutDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str()<< vectorSize <<std::endl;
				printf("Begin to launch kernel_exp10_withoutDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[7] ,
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_exp10_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time kernel_exp10
					status = clWaitForEvents(1, &event_exp10_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_exp10_withoutDD, end_exp10_withoutDD;
					status = clGetEventProfilingInfo(event_exp10_withoutDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_exp10_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_exp10_withoutDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_exp10_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					float executionTime_exp10_withoutDD = (end_exp10_withoutDD
							- start_exp10_withoutDD);
					if (executionTime_exp10_withoutDD_max
							< executionTime_exp10_withoutDD) {
						executionTime_exp10_withoutDD_max = executionTime_exp10_withoutDD;
					}
					if (executionTime_exp10_withoutDD_min
							> executionTime_exp10_withoutDD) {
						executionTime_exp10_withoutDD_min = executionTime_exp10_withoutDD;
					}
					executionTime_exp10_withoutDD_avg += executionTime_exp10_withoutDD;

				}
				executionTime_exp10_withoutDD_avg = (executionTime_exp10_withoutDD_avg
						- executionTime_exp10_withoutDD_max
						- executionTime_exp10_withoutDD_min) / (iterations - 2);
				size_t time_exp10_withoutDD=0;
				time_exp10_withoutDD= 10 * 7  * vectorSize;
				float Gflops_exp10_withoutDD =
						(time_exp10_withoutDD * szGlobalWorkSize)
								/ executionTime_exp10_withoutDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_exp10_withoutDD,
						CL_TRUE, 0, sizeof(cl_mem), exp10_withoutDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-exp10_withoutDD : %f\n", Gflops_exp10_withoutDD);
				printf("Result-exp10_withoutDD   :   %f\n\n", *((float*)exp10_withoutDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_exp10_withoutDD > exp10_withoutDD_maxGflops){
						exp10_withoutDD_maxGflops = Gflops_exp10_withoutDD;
				}
			}

	}	
	printf("erfc_withDD_maxGflops = %f\n",erfc_withDD_maxGflops);
	printf("erfc_withoutDD_maxGflops = %f\n",erfc_withoutDD_maxGflops);
	printf("erf_withDD_maxGflops = %f\n",erf_withDD_maxGflops);
	printf("erf_withoutDD_maxGflops = %f\n",erf_withoutDD_maxGflops);
	printf("expm1_withDD_maxGflops = %f\n",expm1_withDD_maxGflops);
	printf("expm1_withoutDD_maxGflops = %f\n",expm1_withoutDD_maxGflops);
	printf("exp10_withDD_maxGflops = %f\n",exp10_withDD_maxGflops);
	printf("exp10_withoutDD_maxGflops = %f\n",exp10_withoutDD_maxGflops);
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


