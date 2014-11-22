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
	// create a CL program 
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
	std::stringstream fdim_withDD(s);
	fdim_withDD << "kernel_fdim_withDD";
	fdim_withDD << vectorSize;
	//dumpPTXCode(context,program,fdim_withDD.str().c_str());
	// Create the cKermel_kernel_fdim_withDD
	kernel[0]  = clCreateKernel(program, fdim_withDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_fdim_withDD)");

    	std::stringstream fdim_withoutDD(s);
	fdim_withoutDD << "kernel_fdim_withDD";
	fdim_withoutDD << vectorSize;
	//dumpPTXCode(context,program,fdim_withDD.str().c_str());
	// Create the cKermel_kernel_fdim_withDD
	kernel[1]  = clCreateKernel(program, fdim_withoutDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_fdim_withoutDD)");

    	std::stringstream floor_withDD(s);
	floor_withDD << "kernel_floor_withDD";
	floor_withDD << vectorSize;
	//dumpPTXCode(context,program,floor_withDD.str().c_str());
	// Create the cKermel_kernel_floor_withDD
	kernel[2]  = clCreateKernel(program, floor_withDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_floor_withDD)");

    	std::stringstream floor_withoutDD(s);
	floor_withoutDD << "kernel_floor_withoutDD";
	floor_withoutDD << vectorSize;
	//dumpPTXCode(context,program,floor_withoutDD.str().c_str());
	// Create the cKermel_kernel_floor_withoutDD
	kernel[3]  = clCreateKernel(program, floor_withoutDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_floor_withoutDD)");

	std::stringstream fma_withDD(s);
	fma_withDD << "kernel_fma_withDD";
	fma_withDD << vectorSize;
	//dumpPTXCode(context,program,fma_withDD.str().c_str());
	// Create the cKermel_kernel_fma_withDD
	kernel[4]  = clCreateKernel(program, fma_withDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_fma_withDD)");

	std::stringstream fma_withoutDD(s);
	fma_withoutDD << "kernel_fma_withoutDD";
	fma_withoutDD << vectorSize;
	//dumpPTXCode(context,program,fma_withoutDD.str().c_str());
	// Create the cKermel_kernel_fma_withoutDD
	kernel[5]  = clCreateKernel(program, fma_withoutDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_fma_withoutDD)");

	std::stringstream fmod_withDD(s);
	fmod_withDD << "kernel_fmod_withDD";
	fmod_withDD << vectorSize;
	//dumpPTXCode(context,program,fmod_withDD.str().c_str());
	// Create the cKermel_kernel_fmod_withDD
	kernel[6]  = clCreateKernel(program, fmod_withDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_fmod_withDD)");

	std::stringstream fmod_withoutDD(s);
	fmod_withoutDD << "kernel_fmod_withoutDD";
	fmod_withoutDD << vectorSize;
	//dumpPTXCode(context,program,fmod_withoutDD.str().c_str());
	// Create the cKermel_kernel_fmod_withoutDD
	kernel[7]  = clCreateKernel(program, fmod_withoutDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_fmod_withoutDD)");

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
	cl_event event_fdim_withDD,event_fdim_withoutDD;
	cl_event event_floor_withDD,event_floor_withoutDD;
	cl_event event_fma_withDD,event_fma_withoutDD;
	cl_event event_fmod_withDD,event_fmod_withoutDD;

	//Create Variable for story result reading from device to host
	void *fdim_withDD_num,*fdim_withoutDD_num;
	void *floor_withDD_num,*floor_withoutDD_num;
	void *fma_withDD_num,*fma_withoutDD_num;
	void *fmod_withDD_num,*fmod_withoutDD_num;

	fdim_withDD_num = (void *) malloc(sizeof(cl_float));
	fdim_withoutDD_num = (void *) malloc(sizeof(cl_float));
	floor_withDD_num = (void *) malloc(sizeof(cl_float));
	floor_withoutDD_num = (void *) malloc(sizeof(cl_float));
	fma_withDD_num = (void *) malloc(sizeof(cl_float));
	fma_withoutDD_num = (void *) malloc(sizeof(cl_float));
	fmod_withDD_num = (void *) malloc(sizeof(cl_float));
	fmod_withoutDD_num = (void *) malloc(sizeof(cl_float));	

	float fdim_withDD_maxGflops = 0.0;
	float fdim_withoutDD_maxGflops = 0.0;
	float floor_withDD_maxGflops = 0.0;
	float floor_withoutDD_maxGflops = 0.0;
	float fma_withDD_maxGflops = 0.0;
	float fma_withoutDD_maxGflops = 0.0;
	float fmod_withDD_maxGflops = 0.0;
	float fmod_withoutDD_maxGflops = 0.0;

	//create buffer
	cl_mem result_fdim_withDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_fdim_withoutDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_floor_withDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_floor_withoutDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_fma_withDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_fma_withoutDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_fmod_withDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_fmod_withoutDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);

	//set kernel_fdim_withDD Argument
	status |= clSetKernelArg(kernel[0] , 0, sizeof(cl_mem),
			(void*) &result_fdim_withDD);
	status |= clSetKernelArg(kernel[0] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_fdim_withDD)");

	//set kernel_fdim_withoutDD Argument
	status |= clSetKernelArg(kernel[1] , 0, sizeof(cl_mem),
			(void*) &result_fdim_withoutDD);
	status |= clSetKernelArg(kernel[1] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_fdim_withoutDD)");

	//set kernel_floor_withDD Argument
	status |= clSetKernelArg(kernel[2] , 0, sizeof(cl_mem),
			(void*) &result_floor_withDD);
	status |= clSetKernelArg(kernel[2] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_floor_withDD)");

	//set kernel_floor_withoutDD Argument
	status |= clSetKernelArg(kernel[3] , 0, sizeof(cl_mem),
			(void*) &result_floor_withoutDD);
	status |= clSetKernelArg(kernel[3] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_floor_withoutDD)");

	//set kernel_fma_withDD Argument
	status |= clSetKernelArg(kernel[4] , 0, sizeof(cl_mem),
			(void*) &result_fma_withDD);
	status |= clSetKernelArg(kernel[4] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_fma_withDD)");

	//set kernel_fma_withoutDD Argument
	status |= clSetKernelArg(kernel[5] , 0, sizeof(cl_mem),
			(void*) &result_fma_withoutDD);
	status |= clSetKernelArg(kernel[5] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_fma_withoutDD)");

	//set kernel_fmod_withDD Argument
	status |= clSetKernelArg(kernel[6] , 0, sizeof(cl_mem),
			(void*) &result_fmod_withDD);
	status |= clSetKernelArg(kernel[6] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_fmod_withDD)");

	//set kernel_fmod_withoutDD Argument
	status |= clSetKernelArg(kernel[7] , 0, sizeof(cl_mem),
			(void*) &result_fmod_withoutDD);
	status |= clSetKernelArg(kernel[7] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_fmod_withoutDD)");

	int i = 0;
	int gws, lws;
	for (gws = 1024; gws <= 65536 * 8; gws *= 2)
		for (lws = 64; lws <= 256; lws *= 2) {

			float executionTime_fdim_withDD_max = 0.0;
			float executionTime_fdim_withDD_avg = 0.0;
			float executionTime_fdim_withDD_min = 999999999.0;

			float executionTime_fdim_withoutDD_max = 0.0;
			float executionTime_fdim_withoutDD_avg = 0.0;
			float executionTime_fdim_withoutDD_min = 999999999.0;

			float executionTime_floor_withDD_max = 0.0;
			float executionTime_floor_withDD_avg = 0.0;
			float executionTime_floor_withDD_min = 999999999.0;

            		float executionTime_floor_withoutDD_max = 0.0;
			float executionTime_floor_withoutDD_avg = 0.0;
			float executionTime_floor_withoutDD_min = 999999999.0;

			float executionTime_fma_withDD_max = 0.0;
			float executionTime_fma_withDD_avg = 0.0;
			float executionTime_fma_withDD_min = 999999999.0;

			float executionTime_fma_withoutDD_max = 0.0;
			float executionTime_fma_withoutDD_avg = 0.0;
			float executionTime_fma_withoutDD_min = 999999999.0;

			float executionTime_fmod_withDD_max = 0.0;
			float executionTime_fmod_withDD_avg = 0.0;
			float executionTime_fmod_withDD_min = 999999999.0;

			float executionTime_fmod_withoutDD_max = 0.0;
			float executionTime_fmod_withoutDD_avg = 0.0;
			float executionTime_fmod_withoutDD_min = 999999999.0;

			szGlobalWorkSize = gws;
			szLocalWorkSize = lws;
			printf("-----------------------------------------------------\n");
			printf("Set gws = %d , lws = %d\n", gws, lws);

		    	//launch kernel_fdim_withDD
			if (!strcmp(kernelname.c_str(), "fdim_withDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str()<< vectorSize <<std::endl;
				printf("Begin to launch kernel_fdim_withDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[0] ,
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_fdim_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time kernel_fdim
					status = clWaitForEvents(1, &event_fdim_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_fdim_withDD, end_fdim_withDD;
					status = clGetEventProfilingInfo(event_fdim_withDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_fdim_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_fdim_withDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_fdim_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					float executionTime_fdim_withDD = (end_fdim_withDD
							- start_fdim_withDD);
					if (executionTime_fdim_withDD_max
							< executionTime_fdim_withDD) {
						executionTime_fdim_withDD_max = executionTime_fdim_withDD;
					}
					if (executionTime_fdim_withDD_min
							> executionTime_fdim_withDD) {
						executionTime_fdim_withDD_min = executionTime_fdim_withDD;
					}
					executionTime_fdim_withDD_avg += executionTime_fdim_withDD;

				}
				executionTime_fdim_withDD_avg = (executionTime_fdim_withDD_avg
						- executionTime_fdim_withDD_max
						- executionTime_fdim_withDD_min) / (iterations - 2);
				size_t time_fdim_withDD=0;
				if(vectorSize==1||vectorSize==2||vectorSize==4||vectorSize==8||vectorSize==16)
					time_fdim_withDD= 128 * szForNum * vectorSize;
				float Gflops_fdim_withDD =
						(time_fdim_withDD * szGlobalWorkSize)
								/ executionTime_fdim_withDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_fdim_withDD,
						CL_TRUE, 0, sizeof(cl_mem), fdim_withDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-fdim_withDD : %f\n", Gflops_fdim_withDD);
				printf("Result-fdim_withDD   :   %f\n\n", *((float*)fdim_withDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_fdim_withDD > fdim_withDD_maxGflops)
				{		
						fdim_withDD_maxGflops = Gflops_fdim_withDD;
				}
			}

		
		    	//launch kernel_fdim_withoutDD
			if (!strcmp(kernelname.c_str(), "fdim_withoutDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str()<< vectorSize <<std::endl;
				printf("Begin to launch kernel_fdim_withoutDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[1] ,
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_fdim_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time kernel_fdim
					status = clWaitForEvents(1, &event_fdim_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_fdim_withoutDD, end_fdim_withoutDD;
					status = clGetEventProfilingInfo(event_fdim_withoutDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_fdim_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_fdim_withoutDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_fdim_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					float executionTime_fdim_withoutDD = (end_fdim_withoutDD
							- start_fdim_withoutDD);
					if (executionTime_fdim_withoutDD_max
							< executionTime_fdim_withoutDD) {
						executionTime_fdim_withoutDD_max = executionTime_fdim_withoutDD;
					}
					if (executionTime_fdim_withoutDD_min
							> executionTime_fdim_withoutDD) {
						executionTime_fdim_withoutDD_min = executionTime_fdim_withoutDD;
					}
					executionTime_fdim_withoutDD_avg += executionTime_fdim_withoutDD;

				}
				executionTime_fdim_withoutDD_avg = (executionTime_fdim_withoutDD_avg
						- executionTime_fdim_withoutDD_max
						- executionTime_fdim_withoutDD_min) / (iterations - 2);
				size_t time_fdim_withoutDD=0;
				if(vectorSize==1||vectorSize==2||vectorSize==4||vectorSize==8||vectorSize==16)
					time_fdim_withoutDD= 7 * 10 * szForNum * vectorSize;
				float Gflops_fdim_withoutDD =
						(time_fdim_withoutDD * szGlobalWorkSize)
								/ executionTime_fdim_withoutDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_fdim_withoutDD,
						CL_TRUE, 0, sizeof(cl_mem), fdim_withoutDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-fdim_withoutDD : %f\n", Gflops_fdim_withoutDD);
				printf("Result-fdim_withoutDD   :   %f\n\n", *((float*)fdim_withoutDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_fdim_withoutDD > fdim_withoutDD_maxGflops)
				{
						fdim_withoutDD_maxGflops = Gflops_fdim_withoutDD;
				}
			}

		    	//launch kernel_floor_withDD
			if (!strcmp(kernelname.c_str(), "floor_withDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str()<< vectorSize <<std::endl;
				printf("Begin to launch kernel_floor_withDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[2] ,
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_floor_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time kernel_floor
					status = clWaitForEvents(1, &event_floor_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_floor_withDD, end_floor_withDD;
					status = clGetEventProfilingInfo(event_floor_withDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_floor_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_floor_withDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_floor_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					float executionTime_floor_withDD = (end_floor_withDD
							- start_floor_withDD);
					if (executionTime_floor_withDD_max
							< executionTime_floor_withDD) {
						executionTime_floor_withDD_max = executionTime_floor_withDD;
					}
					if (executionTime_floor_withDD_min
							> executionTime_floor_withDD) {
						executionTime_floor_withDD_min = executionTime_floor_withDD;
					}
					executionTime_floor_withDD_avg += executionTime_floor_withDD;

				}
				executionTime_floor_withDD_avg = (executionTime_floor_withDD_avg
						- executionTime_floor_withDD_max
						- executionTime_floor_withDD_min) / (iterations - 2);
				size_t time_floor_withDD=0;
				if(vectorSize==1||vectorSize==2||vectorSize==4||vectorSize==8||vectorSize==16)
					time_floor_withDD= 256 * szForNum * vectorSize;
				float Gflops_floor_withDD =
						(time_floor_withDD * szGlobalWorkSize)
								/ executionTime_floor_withDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_floor_withDD,
						CL_TRUE, 0, sizeof(cl_mem), floor_withDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-floor_withDD : %f\n", Gflops_floor_withDD);
				printf("Result-floor_withDD   :   %f\n\n", *((float*)floor_withDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_floor_withDD > floor_withDD_maxGflops)
				{	
						floor_withDD_maxGflops = Gflops_floor_withDD;
				}
			}

            		//launch kernel_floor_withoutDD
			if (!strcmp(kernelname.c_str(), "floor_withoutDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str()<< vectorSize <<std::endl;
				printf("Begin to launch kernel_floor_withoutDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[3] ,
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_floor_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time kernel_floor
					status = clWaitForEvents(1, &event_floor_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_floor_withoutDD, end_floor_withoutDD;
					status = clGetEventProfilingInfo(event_floor_withoutDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_floor_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_floor_withoutDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_floor_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					float executionTime_floor_withoutDD = (end_floor_withoutDD
							- start_floor_withoutDD);
					if (executionTime_floor_withoutDD_max
							< executionTime_floor_withoutDD) {
						executionTime_floor_withoutDD_max = executionTime_floor_withoutDD;
					}
					if (executionTime_floor_withoutDD_min
							> executionTime_floor_withoutDD) {
						executionTime_floor_withoutDD_min = executionTime_floor_withoutDD;
					}
					executionTime_floor_withoutDD_avg += executionTime_floor_withoutDD;

				}
				executionTime_floor_withoutDD_avg = (executionTime_floor_withoutDD_avg
						- executionTime_floor_withoutDD_max
						- executionTime_floor_withoutDD_min) / (iterations - 2);
				size_t time_floor_withoutDD=0;
				if(vectorSize==1)
					time_floor_withoutDD= 0.256 * 40 * 1000 * szForNum * vectorSize;
				if(vectorSize==2)
					time_floor_withoutDD= 0.128 * 40 * 1000 * szForNum * vectorSize;
                		if(vectorSize==4)
					time_floor_withoutDD= 0.01 * 30 * 1000 * szForNum * vectorSize;
                		if(vectorSize==8||vectorSize==16)
					time_floor_withoutDD= 0.004 * 30 * 1000 * szForNum * vectorSize;
				float Gflops_floor_withoutDD =
						(time_floor_withoutDD * szGlobalWorkSize)
								/ executionTime_floor_withoutDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_floor_withoutDD,
						CL_TRUE, 0, sizeof(cl_mem), floor_withoutDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-floor_withoutDD : %f\n", Gflops_floor_withoutDD);
				printf("Result-floor_withoutDD   :   %f\n\n", *((float*)floor_withoutDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_floor_withoutDD > floor_withoutDD_maxGflops)
				{		
						floor_withoutDD_maxGflops = Gflops_floor_withoutDD;
				}
			}

		    	//launch kernel_fma_withDD
			if (!strcmp(kernelname.c_str(), "fma_withDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str()<< vectorSize <<std::endl;
				printf("Begin to launch kernel_fma_withDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[4] ,
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_fma_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time kernel_fma
					status = clWaitForEvents(1, &event_fma_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_fma_withDD, end_fma_withDD;
					status = clGetEventProfilingInfo(event_fma_withDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_fma_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_fma_withDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_fma_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					float executionTime_fma_withDD = (end_fma_withDD
							- start_fma_withDD);
					if (executionTime_fma_withDD_max
							< executionTime_fma_withDD) {
						executionTime_fma_withDD_max = executionTime_fma_withDD;
					}
					if (executionTime_fma_withDD_min
							> executionTime_fma_withDD) {
						executionTime_fma_withDD_min = executionTime_fma_withDD;
					}
					executionTime_fma_withDD_avg += executionTime_fma_withDD;

				}
				executionTime_fma_withDD_avg = (executionTime_fma_withDD_avg
						- executionTime_fma_withDD_max
						- executionTime_fma_withDD_min) / (iterations - 2);
				size_t time_fma_withDD=0;
				if(vectorSize==1||vectorSize==2||vectorSize==4||vectorSize==8||vectorSize==16)
					time_fma_withDD= 128 * szForNum * vectorSize;
				float Gflops_fma_withDD =
						(time_fma_withDD * szGlobalWorkSize)
								/ executionTime_fma_withDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_fma_withDD,
						CL_TRUE, 0, sizeof(cl_mem), fma_withDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-fma_withDD : %f\n", Gflops_fma_withDD);
				printf("Result-fma_withDD   :   %f\n\n", *((float*)fma_withDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_fma_withDD > fma_withDD_maxGflops)
				{		
						fma_withDD_maxGflops = Gflops_fma_withDD;
				}
			}

            		//launch kernel_fma_withoutDD
			if (!strcmp(kernelname.c_str(), "fma_withoutDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str()<< vectorSize <<std::endl;
				printf("Begin to launch kernel_fma_withoutDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[5] ,
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_fma_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time kernel_fma
					status = clWaitForEvents(1, &event_fma_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_fma_withoutDD, end_fma_withoutDD;
					status = clGetEventProfilingInfo(event_fma_withoutDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_fma_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_fma_withoutDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_fma_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					float executionTime_fma_withoutDD = (end_fma_withoutDD
							- start_fma_withoutDD);
					if (executionTime_fma_withoutDD_max
							< executionTime_fma_withoutDD) {
						executionTime_fma_withoutDD_max = executionTime_fma_withoutDD;
					}
					if (executionTime_fma_withoutDD_min
							> executionTime_fma_withoutDD) {
						executionTime_fma_withoutDD_min = executionTime_fma_withoutDD;
					}
					executionTime_fma_withoutDD_avg += executionTime_fma_withoutDD;

				}
				executionTime_fma_withoutDD_avg = (executionTime_fma_withoutDD_avg
						- executionTime_fma_withoutDD_max
						- executionTime_fma_withoutDD_min) / (iterations - 2);
				size_t time_fma_withoutDD=0;
				if(vectorSize==1||vectorSize==2||vectorSize==4||vectorSize==8||vectorSize==16)
					time_fma_withoutDD= 10 * szForNum * vectorSize;
				float Gflops_fma_withoutDD =
						(time_fma_withoutDD * szGlobalWorkSize)
								/ executionTime_fma_withoutDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_fma_withoutDD,
						CL_TRUE, 0, sizeof(cl_mem), fma_withoutDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-fma_withoutDD : %f\n", Gflops_fma_withoutDD);
				printf("Result-fma_withoutDD   :   %f\n\n", *((float*)fma_withoutDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_fma_withoutDD > fma_withoutDD_maxGflops)
				{		
						fma_withoutDD_maxGflops = Gflops_fma_withoutDD;
				}
			}

		    	//launch kernel_fmod_withDD
			if (!strcmp(kernelname.c_str(), "fmod_withDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str()<< vectorSize <<std::endl;
				printf("Begin to launch kernel_fmod_withDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[6] ,
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_fmod_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time kernel_fmod
					status = clWaitForEvents(1, &event_fmod_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_fmod_withDD, end_fmod_withDD;
					status = clGetEventProfilingInfo(event_fmod_withDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_fmod_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_fmod_withDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_fmod_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					float executionTime_fmod_withDD = (end_fmod_withDD
							- start_fmod_withDD);
					if (executionTime_fmod_withDD_max
							< executionTime_fmod_withDD) {
						executionTime_fmod_withDD_max = executionTime_fmod_withDD;
					}
					if (executionTime_fmod_withDD_min
							> executionTime_fmod_withDD) {
						executionTime_fmod_withDD_min = executionTime_fmod_withDD;
					}
					executionTime_fmod_withDD_avg += executionTime_fmod_withDD;

				}
				executionTime_fmod_withDD_avg = (executionTime_fmod_withDD_avg
						- executionTime_fmod_withDD_max
						- executionTime_fmod_withDD_min) / (iterations - 2);
				size_t time_fmod_withDD=0;
				if(vectorSize==1||vectorSize==2||vectorSize==4||vectorSize==8||vectorSize==16)
					time_fmod_withDD= 16 * szForNum * vectorSize;
				float Gflops_fmod_withDD =
						(time_fmod_withDD * szGlobalWorkSize)
								/ executionTime_fmod_withDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_fmod_withDD,
						CL_TRUE, 0, sizeof(cl_mem), fmod_withDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-fmod_withDD : %f\n", Gflops_fmod_withDD);
				printf("Result-fmod_withDD   :   %f\n\n", *((float*)fmod_withDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_fmod_withDD > fmod_withDD_maxGflops)
				{		
						fmod_withDD_maxGflops = Gflops_fmod_withDD;
				}
			}

		    	//launch kernel_fmod_withoutDD
			if (!strcmp(kernelname.c_str(), "fmod_withoutDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str()<< vectorSize <<std::endl;
				printf("Begin to launch kernel_fmod_withoutDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[7] ,
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_fmod_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time kernel_fmod
					status = clWaitForEvents(1, &event_fmod_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_fmod_withoutDD, end_fmod_withoutDD;
					status = clGetEventProfilingInfo(event_fmod_withoutDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_fmod_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_fmod_withoutDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_fmod_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					float executionTime_fmod_withoutDD = (end_fmod_withoutDD
							- start_fmod_withoutDD);
					if (executionTime_fmod_withoutDD_max
							< executionTime_fmod_withoutDD) {
						executionTime_fmod_withoutDD_max = executionTime_fmod_withoutDD;
					}
					if (executionTime_fmod_withoutDD_min
							> executionTime_fmod_withoutDD) {
						executionTime_fmod_withoutDD_min = executionTime_fmod_withoutDD;
					}
					executionTime_fmod_withoutDD_avg += executionTime_fmod_withoutDD;

				}
				executionTime_fmod_withoutDD_avg = (executionTime_fmod_withoutDD_avg
						- executionTime_fmod_withoutDD_max
						- executionTime_fmod_withoutDD_min) / (iterations - 2);
				size_t time_fmod_withoutDD=0;
				time_fmod_withoutDD= 10 *10 *szForNum * vectorSize;
				float Gflops_fmod_withoutDD =
						(time_fmod_withoutDD * szGlobalWorkSize)
								/ executionTime_fmod_withoutDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_fmod_withoutDD,
						CL_TRUE, 0, sizeof(cl_mem), fmod_withoutDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-fmod_withoutDD : %f\n", Gflops_fmod_withoutDD);
				printf("Result-fmod_withoutDD   :   %f\n\n", *((float*)fmod_withoutDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_fmod_withoutDD > fmod_withoutDD_maxGflops)
				{		
						fmod_withoutDD_maxGflops = Gflops_fmod_withoutDD;
				}
		}


	}	
	printf("fdim_withDD_maxGflops = %f\n",fdim_withDD_maxGflops);
	printf("fdim_withoutDD_maxGflops = %f\n",fdim_withoutDD_maxGflops);
	printf("floor_withDD_maxGflops = %f\n",floor_withDD_maxGflops);
	printf("floor_withoutDD_maxGflops = %f\n",floor_withoutDD_maxGflops);
	printf("fma_withDD_maxGflops = %f\n",fma_withDD_maxGflops);
	printf("fma_withoutDD_maxGflops = %f\n",fma_withoutDD_maxGflops);
	printf("fmod_withDD_maxGflops = %f\n",fmod_withDD_maxGflops);
	printf("fmod_withoutDD_maxGflops = %f\n",fmod_withoutDD_maxGflops);
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


