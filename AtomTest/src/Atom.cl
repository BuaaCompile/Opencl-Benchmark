/**********************************************************************
Copyright (c) 2014,BUAA COMPILER LAB;
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
- Neither the name of the BUAA COMPILER LAB; nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
********************************************************************/
#define repeat64(S) S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S

#define repeat128(S)  S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S

#define repeat256(S)  S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S

#define repeat512(S)  S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S

#pragma OPENCL EXTENSION cl_khr_global_int32_base_atomics : enable
#pragma OPENCL EXTENSION cl_khr_local_int32_base_atomics : enable

__kernel void atomTest1(__global int* out
					 	)
{
	int gid = get_global_id(0);
	int lid = get_local_id(0);
	__local int test[6];
	if(lid < 6)
		test[lid] = 0;

	int a = 1;
	int t1 = atomic_add(&out[0], a);
	int t2 = atomic_add(&test[0], a);
	out[1] = test[0];

 	int t3 = atomic_sub(&out[2], a);
	int t4 = atomic_sub(&test[1], a);
	out[3] = test[1];

	int t5 = atomic_xchg(&out[4], t1);
	int t6 = atomic_xchg(&test[2], t2);
	out[5] = test[2];

	int t7 = atomic_inc(&out[6]);
	int t8 = atomic_inc(&test[3]);
	out[7] = test[3];

	int t9 = atomic_dec(&out[8]);
	int t10 = atomic_dec(&test[4]);
	out[9] = test[4];

	int t11 = atomic_cmpxchg(&out[10], gid, gid-1);
	int t12 = atomic_cmpxchg(&test[5], lid, lid-1);
	out[11] = test[5];

}


#pragma OPENCL EXTENSION cl_khr_global_int32_extended_atomics : enable
#pragma OPENCL EXTENSION cl_khr_local_int32_extended_atomics : enable

__kernel void atomTest2(__global int* out
						)
{
	int gid = get_global_id(0);
    int lid = get_local_id(0);
    __local int test[6];
    if(lid < 6)
        test[lid] = 0;

    int a = 1;
    int t1 = atomic_min(&out[0], gid);
    int t2 = atomic_min(&test[0], lid);
    out[1] = test[0];

    int t3 = atomic_max(&out[2], gid);
    int t4 = atomic_max(&test[1], lid);
    out[3] = test[1];

    int t5 = atomic_and(&out[4], a);
    int t6 = atomic_and(&test[2], a);
    out[5] = test[2];

    int t7 = atomic_or(&out[6], t1);
    int t8 = atomic_or(&test[3], t2);
    out[7] = test[3];

    int t9 = atomic_xor(&out[8], t1);
    int t10 = atomic_xor(&test[4], t2);
    out[9] = test[4];
}
    
__kernel void atomTest3(__global int* out
					 	)
{
	int lid = get_local_id(0);
	int t1 = atomic_add(&out[0], lid);
}


__kernel void atomTest4(__global int* out
					 	)
{
	int lid = get_local_id(0);
	out[0] = out[0] + lid;
}

__kernel void atomTest5(__global int* out
					   )
{
	int t1 = atomic_inc(&out[0]);
}

__kernel void atomTest6(__global int* out
						)
{
	out[0]++;
}


/*
__kernel void atomTest7(__global int* out
						)
{
	int lid = get_global_id(0);
	//int t1 = atom_cmpxchg(&out[0], lid, lid-1);
}

__kernel void atomTest8(__global int* out
						)
{
	int lid = get_global_id(0);
	out[0] = (out[0] == lid)?(lid-1):lid;
}
*/
