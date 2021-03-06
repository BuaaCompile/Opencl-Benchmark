/**********************************************************************
Copyright (c) 2014,BUAA COMPILER LAB;
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
- Neither the name of the BUAA COMPILER LAB; nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
********************************************************************/
#ifndef BANDWIDTH_H_
#define BANDWIDTH_H_

#define GROUP_SIZE 64
#define NUM_READS 256
#define WAVEFRONT 64
#define NUM_KERNELS 4

//Header Files
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "SDKCommon.hpp"
#include "Application.hpp"
#include "CommandArgs.hpp"
#include "File.hpp"



//enums, project
enum tMode { QUICK_MODE, RANGE_MODE, SHMOO_MODE };
enum memcpyKind { DEVICE_TO_HOST, HOST_TO_DEVICE, DEVICE_TO_DEVICE };

// defines, project
#define MEMCOPY_ITERATIONS  100
#define DEFAULT_SIZE        ( 32 * ( 1 << 20 ) )    //32 M
#define DEFAULT_INCREMENT   (1 << 22)               //4 M
#define CACHE_CLEAR_SIZE    (1 << 24)               //16 M

//shmoo mode defines
#define SHMOO_MEMSIZE_MAX     (1 << 26)         //64 M
#define SHMOO_MEMSIZE_START   (1 << 10)         //1 KB
#define SHMOO_INCREMENT_1KB   (1 << 10)         //1 KB
#define SHMOO_INCREMENT_2KB   (1 << 11)         //2 KB
#define SHMOO_INCREMENT_10KB  (10 * (1 << 10))  //10KB
#define SHMOO_INCREMENT_100KB (100 * (1 << 10)) //100 KB
#define SHMOO_INCREMENT_1MB   (1 << 20)         //1 MB
#define SHMOO_INCREMENT_2MB   (1 << 21)         //2 MB
#define SHMOO_INCREMENT_4MB   (1 << 22)         //4 MB
#define SHMOO_LIMIT_20KB      (20 * (1 << 10))  //20 KB
#define SHMOO_LIMIT_50KB      (50 * (1 << 10))  //50 KB
#define SHMOO_LIMIT_100KB     (100 * (1 << 10)) //100 KB
#define SHMOO_LIMIT_1MB       (1 << 20)         //1 MB
#define SHMOO_LIMIT_16MB      (1 << 24)         //16 MB
#define SHMOO_LIMIT_32MB      (1 << 25)         //32 MB

/**
 * Bandwidth 
 * Class implements OpenCL Constant Buffer Bandwidth sample
 * Derived from Benchmark base class
 */

class Bandwidth : public Benchmark
{
    cl_double           setupTime;      /**< Time for setting up OpenCL */
    cl_double     totalKernelTime;      /**< Time for kernel execution */
    cl_double    totalProgramTime;      /**< Time for program execution */
    cl_uint                length;      /**< Length of the input data */
    cl_float               *input;      /**< Input array */
    cl_float              *output;      /**< Output array */
    cl_float  *verificationOutput;      /**< host output array */
    cl_context            context;      /**< CL context */
    cl_device_id         *devices;      /**< CL device list */
    cl_mem         constantBuffer;      /**< CL memory buffer */
    cl_mem           outputBuffer;      /**< CL memory buffer */
    cl_mem    randomIndicesBuffer;      /**< CL memory buffer */
    cl_command_queue commandQueue;      /**< CL command queue */
    cl_program            program;      /**< CL program */
    cl_kernel kernel[NUM_KERNELS];      /**< CL kernel */
    size_t          globalThreads;
    size_t           localThreads;

    size_t    kernelWorkGroupSize;      /**< Group Size returned by kernel */
    int                iterations;      /**< Number of iterations for kernel execution */
    int                vectorSize;      /**< Number of vector elements, default = 1 */
	std::string        accessMode;      /**< Specify which memory access mode to use, default = direct */
	std::string        memoryMode;      /**< Specify which memory mode to use, default = pageable */
	std::string          testMode;      /**< Specify the mode to use, default = quick */
	tMode                    mode;
	int                     start;
	int                       end;
	int                 increment;
	int               startDevice;
	int                 endDevice;
	bool                     htod;
	bool                     dtoh;
	bool                     dtod;
    bool dynamiArgFlag;
    bool randomArgFlag;
    bool vec3;
    streamsdk::SDKDeviceInfo deviceInfo;  /**< Structure to store device information*/
    

    // Initialize constant buffer array with random data for random access test
    cl_uint randomIndices[NUM_READS + GROUP_SIZE];
 
public:
    /** 
     * Constructor 
     * Initialize member variables
     * @param name name of sample (string)
     */
    Bandwidth(std::string name): Benchmark(name)
    {
            input = NULL;
            output = NULL;
            verificationOutput = NULL;
            setupTime = 0;
            totalKernelTime = 0;
            //iterations = 500;
            length = 1024 * 1024;
            //vectorSize = 4;
            globalThreads = length;
            localThreads = GROUP_SIZE;
            dynamiArgFlag = false;
            randomArgFlag = false;
            vec3 = false;

			start = DEFAULT_SIZE;
			end = DEFAULT_SIZE;
			increment = DEFAULT_INCREMENT;
			testMode = "quick";
			bool htod = false;
			bool dtoh = false;
			bool dtod = false;
			memoryMode = "pinned";//pageable  pinned
			accessMode = "direct";//direct mapped
			startDevice = 0;
			endDevice = 0;
			commandQueue = NULL;
        }

    /** 
     * Constructor 
     * Initialize member variables
     * @param name name of sample (const char*)
     */
    Bandwidth(const char* name): Benchmark(name)
    {
            input = NULL;
            output = NULL;
            verificationOutput = NULL;
            setupTime = 0;
            totalKernelTime = 0;
            //iterations = 500;
            length = 1024 * 1024;
            //vectorSize = 4;
            globalThreads = length;
            localThreads = GROUP_SIZE;
            dynamiArgFlag = false;
            randomArgFlag = false;
            vec3 = false;

			start = DEFAULT_SIZE;
			end = DEFAULT_SIZE;
			increment = DEFAULT_INCREMENT;
			testMode = "quick";
			bool htod = true;
			bool dtoh = true;
			bool dtod = true;
			memoryMode = "pinned";//pageable  pinned
			accessMode = "direct";//direct mapped
			startDevice = 0;
			endDevice = 0;
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
     * Set values for kernels' arguments, enqueue calls to the kernels
     * on to the command queue, wait till end of kernel execution.
     * Get kernel start and end time if timing is enabled
     * @return SDK_SUCCESS on success and SDK_FAILURE on failure
     */
    int runCLKernels();

    /**
     * Run bandwidth kernel and write values to output
     * @return SDK_SUCCESS on success and SDK_FAILURE on failure
     */
    int bandwidth(cl_kernel &kernel);

    /**
     * Override from Benchmark. Initialize 
     * command line parser, add custom options
     * @return SDK_SUCCESS on success and SDK_FAILURE on failure
     */
    int initialize();
	/**
     * Override from Benchmark. Initialize 
	 * parses the command line options given by user
	 * @param argc Number of elements in cmd line input
	 * @param argv array of char* storing the CmdLine Options
	 * @return 0 on success Positive if expected and Non-zero on failure
	 */
	int parseCommandLine(int argc, char **argv);

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

	int createQueue(unsigned int device);
	void testBandwidth(memcpyKind kind);
	void testBandwidthQuick(unsigned int size, memcpyKind kind);
	void testBandwidthRange(unsigned int start, unsigned int end, unsigned int increment, memcpyKind kind);
	void testBandwidthShmoo(memcpyKind kind);
	double testDeviceToHostTransfer(unsigned int memSize);
	double testHostToDeviceTransfer(unsigned int memSize);
	double testDeviceToDeviceTransfer(unsigned int memSize);
	void printResultsReadable(unsigned int *memSizes, double* bandwidths, unsigned int count, memcpyKind kind, int iNumDevs);
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
};


#endif
