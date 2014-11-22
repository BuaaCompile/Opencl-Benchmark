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
// Copyright 1993-2009 NVIDIA Corporation
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
    	ss << "kernel_add_withDD";
   	ss << vectorSize;

	// Create the cKermel_kernel_add_withDD
	kernel[0]  = clCreateKernel(program, ss.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_add_withDD)");
	
	std::stringstream add_withoutDD(s);
	add_withoutDD << "kernel_add_withoutDD";
	add_withoutDD << vectorSize;
	//dumpPTXCode(context,program,add_withoutDD.str().c_str());
	// Create the cKermel_kernel_add_withoutDD
	
	kernel[1]  = clCreateKernel(program, add_withoutDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_add_withoutDD)");
	
	std::stringstream sub_withDD(s);
	sub_withDD << "kernel_sub_withDD";
	sub_withDD << vectorSize;
	// Create the cKermel_kernel_sub_withDD
	kernel[2]  = clCreateKernel(program, sub_withDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_sub_withDD)");
	
	std::stringstream sub_withoutDD(s);
	sub_withoutDD << "kernel_sub_withoutDD";
	sub_withoutDD << vectorSize;
	// Create the cKermel_kernel_sub_withoutDD
	kernel[3]  = clCreateKernel(program, sub_withoutDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_sub_withoutDD)");
	
	std::stringstream multi_withDD(s);
	multi_withDD << "kernel_multi_withDD";
	multi_withDD << vectorSize;
	// Create the cKermel_kernel_multi_withDD
	kernel[4] = clCreateKernel(program, multi_withDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_multi_withDD)");
	
	std::stringstream multi_withoutDD(s);
	multi_withoutDD << "kernel_multi_withoutDD";
	multi_withoutDD << vectorSize;	
	// Create the cKermel_kernel_multi_withoutDD
	kernel[5] = clCreateKernel(program, multi_withoutDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status,
			"clCreateKernel failed.(kernel_multi_withoutDD)");
	
	std::stringstream div_withDD(s);
	div_withDD << "kernel_div_withDD";
	div_withDD << vectorSize;
	// Create the cKernel_kernel_div_withDD
	kernel[6] = clCreateKernel(program, div_withDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_div_withDD)");
	
	std::stringstream div_withoutDD(s);
	div_withoutDD << "kernel_div_withoutDD";
	div_withoutDD << vectorSize;
	// Create the cKermel_kernel_div_withoutDD
	kernel[7] = clCreateKernel(program, div_withoutDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_div_withoutDD)");
	
	std::stringstream mad_withDD(s);
	mad_withDD << "kernel_mad_withDD";
	mad_withDD << vectorSize;
	// Create the cKermel_kernel_mad_withDD
	kernel[8] = clCreateKernel(program, mad_withDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_mad_withDD)");
	std::stringstream mad_withoutDD(s);
	mad_withoutDD << "kernel_mad_withoutDD";
	mad_withoutDD << vectorSize;
	// Create the cKermel_kernel_mad_withoutDD
	kernel[9] = clCreateKernel(program, mad_withoutDD.str().c_str(), &status);
	CHECK_OPENCL_ERROR(status, "clCreateKernel failed.(kernel_mad_withoutDD)");

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
	cl_event event_add_withDD, event_add_withoutDD;
	cl_event event_sub_withDD, event_sub_withoutDD;
	cl_event event_multi_withDD, event_multi_withoutDD;
	cl_event event_div_withDD, event_div_withoutDD;
	cl_event event_mad_withDD, event_mad_withoutDD;

	//Create Variable for story result reading from device to host
	void *sub_withDD_num, *sub_withoutDD_num;
	void *multi_withDD_num, *multi_withoutDD_num;
	void *div_withDD_num, *div_withoutDD_num;
	void *add_withDD_num, *add_withoutDD_num;
	void *mad_withDD_num, *mad_withoutDD_num;

	add_withDD_num = (void *) malloc(sizeof(cl_float));
	add_withoutDD_num = (void *) malloc(sizeof(cl_float));

	sub_withDD_num = (void *) malloc(sizeof(cl_float));
	sub_withoutDD_num = (void *) malloc(sizeof(cl_float));

	multi_withDD_num = (void *) malloc(sizeof(cl_float));
	multi_withoutDD_num = (void *) malloc(sizeof(cl_float));

	div_withDD_num = (void *) malloc(sizeof(cl_float));
	div_withoutDD_num = (void *) malloc(sizeof(cl_float));

	mad_withDD_num = (void *) malloc(sizeof(cl_float));
	mad_withoutDD_num = (void *) malloc(sizeof(cl_float));

	float add_withDD_maxGflops = 0.0;
	float add_withoutDD_maxGflops = 0.0;
	float sub_withDD_maxGflops = 0.0;
	float sub_withoutDD_maxGflops = 0.0;
	float multi_withDD_maxGflops = 0.0;
	float multi_withoutDD_maxGflops = 0.0;
	float div_withDD_maxGflops = 0.0;
	float div_withoutDD_maxGflops = 0.0;
	float mad_withDD_maxGflops = 0.0;
	float mad_withoutDD_maxGflops = 0.0;
	
	//create buffer

	cl_mem result_add_withDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_add_withoutDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_sub_withDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_sub_withoutDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_multi_withDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_multi_withoutDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_div_withDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_div_withoutDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_mad_withDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);
	cl_mem result_mad_withoutDD = clCreateBuffer(context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, NULL);

	float p1 = 0.0;

	//set kernel_add_withDD Argument
	status |= clSetKernelArg(kernel[0] , 0, sizeof(cl_mem),
			(void*) &result_add_withDD);
	status |= clSetKernelArg(kernel[0] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_add_withDD)");

	//set kernel_add_withoutDD Argument
	status |= clSetKernelArg(kernel[1] , 0, sizeof(cl_mem),
			(void*) &result_add_withoutDD);
	status |= clSetKernelArg(kernel[1] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_add_withoutDD)");
	
	//set kernel_sub_withDD Argument
	status |= clSetKernelArg(kernel[2] , 0, sizeof(cl_mem),
			(void*) &result_sub_withDD);
	status |= clSetKernelArg(kernel[2] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_sub_withDD)");
	
	//set kernel_sub_withoutDD Argument
	status |= clSetKernelArg(kernel[3] , 0, sizeof(cl_mem),
			(void*) &result_sub_withoutDD);
	status |= clSetKernelArg(kernel[3] , 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_sub_withoutDD)");
	
	//set kernel_multi_withDD  Argument
	p1 = 1.0000;
	status = clSetKernelArg(kernel[4], 0, sizeof(float), (void*) &p1);
	status |= clSetKernelArg(kernel[4], 1, sizeof(cl_mem),
			(void*) &result_multi_withDD);
	status |= clSetKernelArg(kernel[4], 2, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_multi_withDD)");
	
	//set kernel_multi_withoutDD Argument
	status |= clSetKernelArg(kernel[5], 0, sizeof(cl_mem),
			(void*) &result_multi_withoutDD);
	status |= clSetKernelArg(kernel[5], 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status,
			"clSetKernelArg failed. (kernel_multi_withoutDD)");
	
	//set kernel_div_withDD Argument
	p1 = 1.0000;
	status = clSetKernelArg(kernel[6], 0, sizeof(float), (void*) &p1);
	status |= clSetKernelArg(kernel[6], 1, sizeof(cl_mem),
			(void*) &result_div_withDD);
	status |= clSetKernelArg(kernel[6], 2, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_div_withDD)");

	//set kernel_div_withoutDD Argument
	status |= clSetKernelArg(kernel[7], 0, sizeof(cl_mem),
			(void*) &result_div_withoutDD);
	status |= clSetKernelArg(kernel[7], 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_div_withoutDD)");

	//set kernel_mad_withDD Argument
	status |= clSetKernelArg(kernel[8], 0, sizeof(cl_mem),
			(void*) &result_mad_withDD);
	status |= clSetKernelArg(kernel[8], 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_mad_withDD)");
	
	//Set kernel_mad_withoutDD Argument
	status |= clSetKernelArg(kernel[9], 0, sizeof(cl_mem),
			(void*) &result_mad_withoutDD);
	status |= clSetKernelArg(kernel[9], 1, sizeof(size_t), (void*) &szForNum);
	CHECK_OPENCL_ERROR(status, "clSetKernelArg failed. (kernel_mad_withoutDD)");

	int i = 0;
	int gws, lws;
	for (gws = 1024; gws <= 65536 * 8; gws *= 2)
		for (lws = 64; lws <= 256; lws *= 2) {
			
			float executionTime_add_withDD_max = 0.0;
			float executionTime_add_withDD_avg = 0.0;
			float executionTime_add_withDD_min = 999999999.0;

			float executionTime_add_withoutDD_max = 0.0;
			float executionTime_add_withoutDD_avg = 0.0;
			float executionTime_add_withoutDD_min = 999999999.0;

			float executionTime_sub_withDD_max = 0.0;
			float executionTime_sub_withDD_avg = 0.0;
			float executionTime_sub_withDD_min = 999999999.0;

			float executionTime_sub_withoutDD_max = 0.0;
			float executionTime_sub_withoutDD_avg = 0.0;
			float executionTime_sub_withoutDD_min = 999999999.0;

			float executionTime_multi_withDD_max = 0.0;
			float executionTime_multi_withDD_avg = 0.0;
			float executionTime_multi_withDD_min = 999999999.0;

			float executionTime_multi_withoutDD_max = 0.0;
			float executionTime_multi_withoutDD_avg = 0.0;
			float executionTime_multi_withoutDD_min = 999999999.0;

			float executionTime_div_withDD_max = 0.0;
			float executionTime_div_withDD_avg = 0.0;
			float executionTime_div_withDD_min = 999999999.0;

			float executionTime_div_withoutDD_max = 0.0;
			float executionTime_div_withoutDD_avg = 0.0;
			float executionTime_div_withoutDD_min = 999999999.0;

			float executionTime_mad_withDD_max = 0.0;
			float executionTime_mad_withDD_avg = 0.0;
			float executionTime_mad_withDD_min = 999999999.0;

			float executionTime_mad_withoutDD_max = 0.0;
			float executionTime_mad_withoutDD_avg = 0.0;
			float executionTime_mad_withoutDD_min = 999999999.0;
			szGlobalWorkSize = gws;
			szLocalWorkSize = lws;
			printf("-----------------------------------------------------\n");
			printf("Set gws = %d , lws = %d\n", gws, lws);
		
			//launch kernel_add_withDD
			if (!strcmp(kernelname.c_str(), "add_withDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str()<< vectorSize <<std::endl;
				printf("Begin to launch kernel_add_withDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[0] ,
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_add_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time kernel_add
					status = clWaitForEvents(1, &event_add_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_add_withDD, end_add_withDD;
					status = clGetEventProfilingInfo(event_add_withDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_add_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_add_withDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_add_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					float executionTime_add_withDD = (end_add_withDD
							- start_add_withDD);
					if (executionTime_add_withDD_max
							< executionTime_add_withDD) {
						executionTime_add_withDD_max = executionTime_add_withDD;
					}
					if (executionTime_add_withDD_min
							> executionTime_add_withDD) {
						executionTime_add_withDD_min = executionTime_add_withDD;
					}
					executionTime_add_withDD_avg += executionTime_add_withDD;

				}
				executionTime_add_withDD_avg = (executionTime_add_withDD_avg
						- executionTime_add_withDD_max
						- executionTime_add_withDD_min) / (iterations - 2);
				size_t time_add_withDD = 512 * szForNum * vectorSize;
				float Gflops_add_withDD =
						(time_add_withDD * szGlobalWorkSize)
								/ executionTime_add_withDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_add_withDD,
						CL_TRUE, 0, sizeof(cl_mem), add_withDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-Add_withDD : %f\n", Gflops_add_withDD);
				printf("Result-Add_withDD   :   %f\n\n", *((float*)add_withDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_add_withDD > add_withDD_maxGflops)
					add_withDD_maxGflops = Gflops_add_withDD;

			}

			//launch kernel_add_withoutDD
			if (!strcmp(kernelname.c_str(), "add_withoutDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str()<< vectorSize <<std::endl;
				printf("Begin to launch kernel_add_withoutDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[1] ,
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_add_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time
					status = clWaitForEvents(1, &event_add_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_add_withoutDD, end_add_withoutDD;
					status = clGetEventProfilingInfo(event_add_withoutDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_add_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_add_withoutDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_add_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					float executionTime_add_withoutDD = (end_add_withoutDD
							- start_add_withoutDD);
					if (executionTime_add_withoutDD_max
							< executionTime_add_withoutDD) {
						executionTime_add_withoutDD_max =
								executionTime_add_withoutDD;
					}
					if (executionTime_add_withoutDD_min
							> executionTime_add_withoutDD) {
						executionTime_add_withoutDD_min =
								executionTime_add_withoutDD;
					}

					executionTime_add_withoutDD_avg +=
							executionTime_add_withoutDD;
				}
				executionTime_add_withoutDD_avg /= iterations;
				float time_add_without=  15* szForNum * vectorSize;
				float Gflops_add_withoutDD = (time_add_without
						* szGlobalWorkSize) / executionTime_add_withoutDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_add_withoutDD,
						CL_TRUE, 0, sizeof(cl_mem), add_withoutDD_num, NULL,
						NULL, NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				
				printf("GFLOPs-Add_withoutDD : %f\n",Gflops_add_withoutDD);
				printf("Result-Add_withoutDD : %f\n",*((float*) add_withoutDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_add_withoutDD > add_withoutDD_maxGflops)
					add_withoutDD_maxGflops = Gflops_add_withoutDD;
			}
			
			//launch kernel_sub_withDD
			if (!strcmp(kernelname.c_str(), "sub_withDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str() << vectorSize<<std::endl;
				printf("Begin to launch kernel_sub_withDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[2] , 1,
							NULL, &szGlobalWorkSize, &szLocalWorkSize, 0, NULL,
							&event_sub_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					//record time kernel2 with 10 blocks,each block has one thread
					status = clWaitForEvents(1, &event_sub_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_sub_withDD, end_sub_withDD;
					status = clGetEventProfilingInfo(event_sub_withDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_sub_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_sub_withDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_sub_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					float executionTime_sub_withDD = end_sub_withDD
							- start_sub_withDD;
					if (executionTime_sub_withDD_max
							< executionTime_sub_withDD) {
						executionTime_sub_withDD_max = executionTime_sub_withDD;
					}
					if (executionTime_sub_withDD_min
							> executionTime_sub_withDD) {
						executionTime_sub_withDD_min = executionTime_sub_withDD;
					}
					executionTime_sub_withDD_avg += executionTime_sub_withDD;
				}
				executionTime_sub_withDD_avg /= iterations;
				float Gflops_sub_withDD = (512 * szForNum * vectorSize * szGlobalWorkSize)
						/ executionTime_sub_withDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_sub_withDD,
						CL_TRUE, 0, sizeof(cl_mem), sub_withDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");

				printf("GFLOPs_sub_withDD : %f\n", Gflops_sub_withDD);
				printf("Result-Sub_withDD : %f\n",*((float*) sub_withDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_sub_withDD > sub_withDD_maxGflops)
					sub_withDD_maxGflops = Gflops_sub_withDD;
			}
			
			//launch sub_withoutDD
			if (!strcmp(kernelname.c_str(), "sub_withoutDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str() << vectorSize<<std::endl;
				printf("Begin to launch kernel_sub_withoutDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[3] , 1,
							NULL, &szGlobalWorkSize, &szLocalWorkSize, 0, NULL,
							&event_sub_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					//record sub_withoutDD time
					status = clWaitForEvents(1, &event_sub_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_sub_withoutDD, end_sub_withoutDD;
					status = clGetEventProfilingInfo(event_sub_withoutDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_sub_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_sub_withoutDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_sub_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					float executionTime_sub_withoutDD = end_sub_withoutDD
							- start_sub_withoutDD;
					if (executionTime_sub_withoutDD_max
							< executionTime_sub_withoutDD) {
						executionTime_sub_withoutDD_max =
								executionTime_sub_withoutDD;
					}
					if (executionTime_sub_withoutDD_min
							> executionTime_sub_withoutDD) {
						executionTime_sub_withoutDD_min =
								executionTime_sub_withoutDD;
					}
					executionTime_sub_withoutDD_avg +=
							executionTime_sub_withoutDD;

				}
				executionTime_sub_withoutDD_avg /= iterations;
				float time_sub_without=0.0;
				if(vectorSize==1||vectorSize==2)
					time_sub_without = 30 * 50 * szForNum *vectorSize;
				if(vectorSize==4)
					time_sub_without = 15 * 10 * szForNum *vectorSize;
				if(vectorSize==8||vectorSize==16)
					time_sub_without = 10 * szForNum *vectorSize;
				float Gflops_sub_withoutDD = (time_sub_without
						* szGlobalWorkSize) / executionTime_sub_withoutDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_sub_withoutDD,
						CL_TRUE, 0, sizeof(cl_mem), sub_withoutDD_num, NULL,
						NULL, NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");

				printf("GFLOPs_sub_withoutDD : %f\n",Gflops_sub_withoutDD);
				printf("Result-Sub_withoutDD : %f\n",*((float*) sub_withoutDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_sub_withoutDD > sub_withoutDD_maxGflops)
					sub_withoutDD_maxGflops = Gflops_sub_withoutDD;
			}
			
			//launch kernel_multi_withDD
			if (!strcmp(kernelname.c_str(), "multi_withDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str() << vectorSize<<std::endl;
				printf("Begin to launch kernel_multi_withDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[4],
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_multi_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time for kernel_multi
					status = clWaitForEvents(1, &event_multi_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_multi_withDD, end_multi_withDD;
					status = clGetEventProfilingInfo(event_multi_withDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_multi_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_multi_withDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_multi_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					float executionTime_multi_withDD = (end_multi_withDD
							- start_multi_withDD);
					if (executionTime_multi_withDD_max
							< executionTime_multi_withDD) {
						executionTime_multi_withDD_max =
								executionTime_multi_withDD;
					}
					if (executionTime_multi_withDD_min
							> executionTime_multi_withDD) {
						executionTime_multi_withDD_min =
								executionTime_multi_withDD;
					}
					executionTime_multi_withDD_avg +=
							executionTime_multi_withDD;
				}
				executionTime_multi_withDD_avg /= iterations;
				float Gflops_multi_withDD = (szForNum * 512 * vectorSize*szGlobalWorkSize)
						/ executionTime_multi_withDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_multi_withDD,
						CL_TRUE, 0, sizeof(cl_mem), multi_withDD_num, NULL,
						NULL, NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");

				printf("Result-multi_withDD :   %f\n",*((float*) multi_withDD_num));
				printf("Gflops_multi_withDD :   %f\n",Gflops_multi_withDD);
				printf("-----------------------------------------------------\n");
				if (Gflops_multi_withDD > multi_withDD_maxGflops)
					multi_withDD_maxGflops = Gflops_multi_withDD;
			}
			
			//launch kernel_multi_withoutDD
			if (!strcmp(kernelname.c_str(), "multi_withoutDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str() << vectorSize<<std::endl;
				printf("Begin to launch kernel_multi_withoutDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[5],
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_multi_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time for kernel_multi
					status = clWaitForEvents(1, &event_multi_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_multi_withoutDD, end_multi_withoutDD;
					status = clGetEventProfilingInfo(event_multi_withoutDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_multi_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_multi_withoutDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_multi_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					float executionTime_multi_withoutDD = (end_multi_withoutDD
							- start_multi_withoutDD);
					if (executionTime_multi_withoutDD_max
							< executionTime_multi_withoutDD) {
						executionTime_multi_withoutDD_max =
								executionTime_multi_withoutDD;
					}
					if (executionTime_multi_withoutDD_min
							> executionTime_multi_withoutDD) {
						executionTime_multi_withoutDD_min =
								executionTime_multi_withoutDD;
					}
					executionTime_multi_withoutDD_avg +=
							executionTime_multi_withoutDD;
				}
				executionTime_multi_withoutDD_avg /= iterations;
				int time_multi_withoutDD = 30 * szForNum *vectorSize;
				float Gflops_multi_withoutDD = (time_multi_withoutDD
						* szGlobalWorkSize) / executionTime_multi_withoutDD_avg;
				status = clEnqueueReadBuffer(commandQueue,
						result_multi_withoutDD, CL_TRUE, 0, sizeof(cl_mem),
						multi_withoutDD_num, NULL, NULL, NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-Multi_withoutDD : %f\n",Gflops_multi_withoutDD);
				printf("Result-Multi_withoutDD : %f\n\n",*((float*) multi_withoutDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_multi_withoutDD > multi_withoutDD_maxGflops)
					multi_withoutDD_maxGflops = Gflops_multi_withoutDD;
			}
			
			//launch kernel_div_withDD
			if (!strcmp(kernelname.c_str(), "div_withDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str() << vectorSize<<std::endl;
				printf("Begin to launch kernel_div_withDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[6],
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_div_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					//record time
					status = clWaitForEvents(1, &event_div_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_div_withDD, end_div_withDD;
					status = clGetEventProfilingInfo(event_div_withDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_div_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_div_withDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_div_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					float executionTime_div_withDD = (end_div_withDD
							- start_div_withDD);
					if (executionTime_div_withDD_max
							< executionTime_div_withDD) {
						executionTime_div_withDD_max = executionTime_div_withDD;
					}
					if (executionTime_div_withDD_min
							> executionTime_div_withDD) {
						executionTime_div_withDD_min = executionTime_div_withDD;
					}
					executionTime_div_withDD_avg += executionTime_div_withDD;
				}
				executionTime_div_withDD_avg /= iterations;
				float Gflops_div_withDD = ( 64 * szForNum * vectorSize * szGlobalWorkSize)
						/ executionTime_div_withDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_div_withDD,
						CL_TRUE, 0, sizeof(cl_mem), div_withDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("Result-Div_withDD : %f\n",*((float*) div_withDD_num));
				printf("GFLOPs_div_withDD : %f\n", Gflops_div_withDD);
				printf("-----------------------------------------------------\n");
				if (Gflops_div_withDD > div_withDD_maxGflops)
					div_withDD_maxGflops = Gflops_div_withDD;
			}
			
			//launch kernel_div_withoutDD
			if (!strcmp(kernelname.c_str(), "div_withoutDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str() << vectorSize<<std::endl;
				printf("Begin to launch kernel_div_withoutDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[7],
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_div_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record time
					status = clWaitForEvents(1, &event_div_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_div_withoutDD, end_div_withoutDD;
					status = clGetEventProfilingInfo(event_div_withoutDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_div_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_div_withoutDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_div_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					float executionTime_div_withoutDD = (end_div_withoutDD
							- start_div_withoutDD);
					if (executionTime_div_withoutDD_max
							< executionTime_div_withoutDD) {
						executionTime_div_withoutDD_max =
								executionTime_div_withoutDD;
					}
					if (executionTime_div_withoutDD_min
							> executionTime_div_withoutDD) {
						executionTime_div_withoutDD_min =
								executionTime_div_withoutDD;
					}
					executionTime_div_withoutDD_avg +=
							executionTime_div_withoutDD;
				}
				executionTime_div_withoutDD_avg /= iterations;

				int time_div_withoutDD;
				if(vectorSize==1)
					time_div_withoutDD = 30 * 50 * szForNum *vectorSize;
				if(vectorSize==2||vectorSize==4||vectorSize==8||vectorSize==16)
					time_div_withoutDD = 30 * szForNum *vectorSize;
				
				float Gflops_div_withoutDD = (time_div_withoutDD
						* szGlobalWorkSize) / executionTime_div_withoutDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_div_withoutDD,
						CL_TRUE, 0, sizeof(cl_mem), div_withoutDD_num, NULL,
						NULL, NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");

				printf("GFLOPs_div_withoutDD : %f\n",Gflops_div_withoutDD);
				printf("Result-Div_withoutDD : %f\n",	(*(float*) div_withoutDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_div_withoutDD > div_withoutDD_maxGflops)
					div_withoutDD_maxGflops = Gflops_div_withoutDD;
			}
			
			//launch kernel_mad_withDD
			if (!strcmp(kernelname.c_str(), "mad_withDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str() << vectorSize<<std::endl;
				printf("Begin to launch kernel_mad_withDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[8],
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_mad_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");

					//record kernel_mad time
					status = clWaitForEvents(1, &event_mad_withDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_mad_withDD, end_mad_withDD;
					status = clGetEventProfilingInfo(event_mad_withDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_mad_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_mad_withDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_mad_withDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					float executionTime_mad_withDD = (end_mad_withDD
							- start_mad_withDD);
					if (executionTime_mad_withDD_max
							< executionTime_mad_withDD) {
						executionTime_mad_withDD_max = executionTime_mad_withDD;
					}
					if (executionTime_mad_withDD_min
							> executionTime_mad_withDD) {
						executionTime_mad_withDD_min = executionTime_mad_withDD;
					}
					executionTime_mad_withDD_avg += executionTime_mad_withDD;
				}
				executionTime_mad_withDD_avg /= iterations;
				float Gflops_mad_withDD = (szForNum * 512 * szGlobalWorkSize * vectorSize * 2)
						/ executionTime_mad_withDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_mad_withDD,
						CL_TRUE, 0, sizeof(cl_mem), mad_withDD_num, NULL, NULL,
						NULL);
				CHECK_OPENCL_ERROR(status,
						"clEnqueueNDRangeKernel failed. (kernel_none)");
				printf("GFLOPs-Mad_withDD : %f\n", Gflops_mad_withDD);
				printf("Result-Mad_withDD : %f\n",(*(float*) mad_withDD_num));
				printf("-----------------------------------------------------\n");
				if (Gflops_mad_withDD > mad_withDD_maxGflops)
					mad_withDD_maxGflops = Gflops_mad_withDD;
			}

			//launch kernel_mad_withoutDD
			if (!strcmp(kernelname.c_str(), "mad_withoutDD")
					|| !strcmp(kernelname.c_str(), "all_kernels")) {
				std::cout << "KERNEL NAME:" <<kernelname.c_str() << vectorSize<<std::endl;
				printf("Begin to launch kernel_mad_withoutDD\n");
				for (i = 0; i < iterations; i++) {
					status = clEnqueueNDRangeKernel(commandQueue, kernel[9],
							WorkDim, NULL, &szGlobalWorkSize, &szLocalWorkSize,
							0, NULL, &event_mad_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					//record time
					status = clWaitForEvents(1, &event_mad_withoutDD);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					cl_ulong start_mad_withoutDD, end_mad_withoutDD;
					status = clGetEventProfilingInfo(event_mad_withoutDD,
							CL_PROFILING_COMMAND_START, sizeof(cl_ulong),
							&start_mad_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					status = clGetEventProfilingInfo(event_mad_withoutDD,
							CL_PROFILING_COMMAND_END, sizeof(cl_ulong),
							&end_mad_withoutDD, NULL);
					CHECK_OPENCL_ERROR(status,
							"clEnqueueNDRangeKernel failed. (kernel_none)");
					float executionTime_mad_withoutDD = (end_mad_withoutDD
							- start_mad_withoutDD);
					if (executionTime_mad_withoutDD_max
							< executionTime_mad_withoutDD) {
						executionTime_mad_withoutDD_max =
								executionTime_mad_withoutDD;
					}
					if (executionTime_mad_withoutDD_min
							> executionTime_mad_withoutDD) {
						executionTime_mad_withoutDD_min =
								executionTime_mad_withoutDD;
					}
					executionTime_mad_withoutDD_avg +=
							executionTime_mad_withoutDD;
				}
				executionTime_mad_withoutDD_avg /= iterations;
				int time_mad_withoutDD = 0;
				if(vectorSize==1||vectorSize==2)
					time_mad_withoutDD = 512 * 15 * szForNum * vectorSize;
				if(vectorSize==4)
						time_mad_withoutDD = 128 * 15 * szForNum * vectorSize;
				if(vectorSize==8)
						time_mad_withoutDD = 16 * 15 * szForNum * vectorSize;
				if(vectorSize==16)
						time_mad_withoutDD = 8 * 15 * szForNum * vectorSize;

				float Gflops_mad_withoutDD = (time_mad_withoutDD
						* szGlobalWorkSize) / executionTime_mad_withoutDD_avg;
				status = clEnqueueReadBuffer(commandQueue, result_mad_withoutDD,
						CL_TRUE, 0, sizeof(cl_mem), mad_withoutDD_num, NULL,
						NULL, NULL);
				if (status != CL_SUCCESS) {
					printf("Error in read result_mad, Error num:%d \n", status);
				}

				printf("GFLOPs-mad_withoutDD : %f\n",Gflops_mad_withoutDD);
				printf("Result-Mad_withoutDD : %f\n",	*(float*) mad_withoutDD_num);
				printf("-----------------------------------------------------\n");
				if (Gflops_mad_withoutDD > mad_withoutDD_maxGflops)
					mad_withoutDD_maxGflops = Gflops_mad_withoutDD;
			}

		}
	printf("add_withDD_maxGflops = %f\n",add_withDD_maxGflops);
	printf("add_withoutDD_maxGflops = %f\n",add_withoutDD_maxGflops);
	printf("sub_withDD_maxGflops = %f\n",sub_withDD_maxGflops);
	printf("sub_withoutDD_maxGflops = %f\n",sub_withoutDD_maxGflops);
	printf("multi_withDD_maxGflops = %f\n",multi_withDD_maxGflops);
	printf("multi_withoutDD_maxGflops = %f\n",multi_withoutDD_maxGflops);
	printf("div_withDD_maxGflops = %f\n",div_withDD_maxGflops);
	printf("div_withoutDD_maxGflops = %f\n",div_withoutDD_maxGflops);
	printf("mad_withDD_maxGflops = %f\n",mad_withDD_maxGflops);
	printf("mad_withoutDD_maxGflops = %f\n",mad_withoutDD_maxGflops);
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


