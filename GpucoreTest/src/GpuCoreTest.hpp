/**********************************************************************
Copyright (c) 2014,BUAA COMPILER LAB;
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
- Neither the name of the BUAA COMPILER LAB; nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
********************************************************************/
#ifndef BRANCHTEST_H_
#define BRANCHTEST_H_

#define GROUP_SIZE 64
#define NUM_READS 256
#define WAVEFRONT 64

//Header Files
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "SDKCommon.hpp"
#include "Application.hpp"
#include "CommandArgs.hpp"
#include "File.hpp"



#define NO_USE 3
#define MAX_TIME 999999999.0
#define profile

/**
 * Bandwidth 
 * Class implements OpenCL Constant Buffer Bandwidth sample
 * Derived from Benchmark base class
 */

class GpuCore : public Benchmark
{
    cl_double           setupTime;      /**< Time for setting up OpenCL */
    cl_double     totalKernelTime;      /**< Time for kernel execution */
    cl_double    totalProgramTime;      /**< Time for program execution */
    cl_context            context;      /**< CL context */
    cl_device_id         *devices;      /**< CL device list */
    cl_mem			   srcABuffer;      /**< CL memory buffer */
    cl_mem	           srcBBuffer;      /**< CL memory buffer */
    cl_mem              dstBuffer;      /**< CL memory buffer */
    cl_command_queue commandQueue;      /**< CL command queue */
    cl_program            program;      /**< CL program */
    cl_kernel			   kernel;      /**< CL kernel */
    size_t          globalThreads;      /**< Specify the value of GlobalWorkSize, default = 65536 */
	int                    numMin;
	int                    numMax;
	int                   sizeMin;
	int                   sizeMax;
    //size_t           localThreads;      /**< Specify the value of LocalWorkSize, default = GROUP_SIZE */

    //size_t    kernelWorkGroupSize;      /**< Group Size returned by kernel */
    //int                iterations;      /**< Number of iterations for kernel execution */
    //int                vectorSize;      /**< Number of vector elements, default = 1 */
	
    //bool dynamiArgFlag;
    //bool randomArgFlag;
    //bool vec3;
    streamsdk::SDKDeviceInfo deviceInfo;  /**< Structure to store device information*/
    

    // Initialize constant buffer array with random data for random access test
    //cl_uint randomIndices[NUM_READS + GROUP_SIZE];
 
public:
    /** 
     * Constructor 
     * Initialize member variables
     * @param name name of sample (string)
     */
    GpuCore(std::string name): Benchmark(name)
    {
		setupTime = 0;
		totalKernelTime = 0;
		globalThreads = 8388608;//1024 * 32 * 256;
		numMin = 1;
		numMax = 65536;//1024 * 64;
		sizeMin = 8; 
		sizeMax = 1024; 
		commandQueue = NULL;
	}

    /** 
     * Constructor 
     * Initialize member variables
     * @param name name of sample (const char*)
     */
    GpuCore(const char* name): Benchmark(name)
    {
		setupTime = 0;
		totalKernelTime = 0;
		globalThreads = 8388608;//1024 * 32 * 256;
		numMin = 1;
		numMax = 65536;//1024 * 64;
		sizeMin = 8; 
		sizeMax = 1024; 
		commandQueue = NULL;
	}

    /**
     * Allocate and initialize host memory array with random values
     * @return SDK_SUCCESS on success and SDK_FAILURE on failure
     */
    //int setupConstantBandwidth();

    /**
     * OpenCL related initialisations. 
     * Set up Context, Device list, Command Queue, Memory buffers
     * Build CL kernel program executable
     * @return SDK_SUCCESS on success and SDK_FAILURE on failure
     */
    int setupCL();

    /**
     * Override from Benchmark. Initialize 
     * command line parser, add custom options
     * @return SDK_SUCCESS on success and SDK_FAILURE on failure
     */
    int initialize();

    /**
     * Override from Benchmark, Generate binary image of given kernel 
     * and exit application
     * @return SDK_SUCCESS on success and SDK_FAILURE on failure
     */
   // int genBinaryImage();

    /**
     * Override from Benchmark, adjust width and height 
     * of execution domain, perform all sample setup
     * @return SDK_SUCCESS on success and SDK_FAILURE on failure
     */
    int setup();

    /**
     * Override from Benchmark
     * @return SDK_SUCCESS on success and SDK_FAILURE on failure
     */
    int run();

	/**
     * Set values for kernels' arguments, enqueue calls to the kernels
     * on to the command queue, wait till end of kernel execution.
     * Get kernel start and end time if timing is enabled
     * @return SDK_SUCCESS on success and SDK_FAILURE on failure
     */
    int runCLKernels(int WorkGroupNums, int WorkGroupSize,int size);
    /**
     * Override from Benchmark
     * Cleanup memory allocations
     * @return SDK_SUCCESS on success and SDK_FAILURE on failure
     */
    int cleanup();

    /**
     * Override from Benchmark
     * Verify against reference implementation
     * @return SDK_SUCCESS on success and SDK_FAILURE on failure
     */
	int verifyResults();

	void printStats();

	double executionTime(cl_event &event);
};


#endif
