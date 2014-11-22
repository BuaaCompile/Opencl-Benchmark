/**********************************************************************
Copyright (c) 2014,BUAA COMPILER LAB;
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
- Neither the name of the BUAA COMPILER LAB; nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
********************************************************************/
#define repeat16(S) S S S S S S S S S S S S S S S S
#define repeat32(S) S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S
#define repeat64(S) S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S
#define repeat128(S)  S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S
//if the kernel use too much time, you can replace repeat128 of all kernels with repeat16,repeat32 or repeat64


#pragma OPENCL EXTENSION cl_khr_global_int32_base_atomics : enable
#pragma OPENCL EXTENSION cl_khr_local_int32_base_atomics : enable
//#pragma OPENCL EXTENSION cl_khr_int64_base_atomics : enable

constant int array[32] = {0, 1, 2, 3, 4, 5, 6, 7,
						  8, 9, 10,11,12,13,14,15,
						  16,17,18,19,20,21,22,23,
						  24,25,26,27,28,29,30,31};


//kernel without branch
__kernel void non_branch(__global int* out)
{
	int lid = get_local_id(0);
	int gid = get_global_id(0);
	int id = lid % 32;
	int t1 = id;
	int t2 = 1;

	repeat128(t1/=t2; t2%=t1;)

	out[gid] = t1 + t2;
	barrier(CLK_GLOBAL_MEM_FENCE);
}


//kernel with 4 branchs
__kernel void with_branch4(__global int* out)
{
	int lid = get_local_id(0);
	int gid = get_global_id(0);
	int id = lid % 32;
	int t1 = id;
	int t2 = 1;

	if(id == 0||id == 1||id == 2||id == 3||id == 4||id == 5||id == 6||id == 7) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 8||id == 9||id == 10||id == 11||id == 12||id == 13||id == 14||id == 15) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 16||id == 17||id == 18||id == 19||id == 20||id == 21||id == 22||id == 23) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 24||id == 25||id == 26||id == 27||id == 28||id == 29||id == 30||id == 31) {
		repeat128(t1/=t2; t2%=t1;)
	}

	out[gid] = t1 + t2;
	barrier(CLK_GLOBAL_MEM_FENCE);
	
}

//kernel with 16 branchs
__kernel void with_branch16(__global int* out)
{
	int lid = get_local_id(0);
	int gid = get_global_id(0);
	int id = lid % 32;
	int t1 = id;
	int t2 = 1;

	if(id == 0||id == 1) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 2||id == 3) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 4||id == 5) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 6||id == 7) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 8||id == 9) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 10||id == 11) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 12||id == 13) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 14||id == 15) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 16||id == 17) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 18||id == 19) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 20||id == 21) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 22||id == 23) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 24||id == 25) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 26||id == 27) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 28||id == 29) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 30||id == 31) {
		repeat128(t1/=t2; t2%=t1;)
	}
	out[gid] = t1 + t2;
	barrier(CLK_GLOBAL_MEM_FENCE);
	
}

//kernel with 32 branchs
__kernel void with_branch32(__global int* out)
{
	int lid = get_local_id(0);
	int gid = get_global_id(0);
	int id = lid % 32;
	int t1 = id;
	int t2 = 1;

	if(id == 0) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 1) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 2) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 3) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 4) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 5) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 6) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 7) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 8) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 9) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 10) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 11) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 12) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 13) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 14) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 15) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 16) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 17) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 18) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 19) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 20) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 21) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 22) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 23) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 24) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 25) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 26) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 27) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 28) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 29) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 30) {
		repeat128(t1/=t2; t2%=t1;)
	}
	else if(id == 31) {
		repeat128(t1/=t2; t2%=t1;)
	}

	out[gid] = t1 + t2;
	barrier(CLK_GLOBAL_MEM_FENCE);
	
}
