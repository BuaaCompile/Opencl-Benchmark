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
#define repeat128(S) S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S
#define repeat256(S) S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S
#define repeat512(S) S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S
#define repeat2048(S) S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S

__kernel void kernel_fmax_withDD1( __global float* result_fmax, int N)
{
  float t1 = 1.0;
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat256(t1 = fmax(t1,t1););
  }
  *result_fmax = t1;
}

__kernel void kernel_fmax_withDD2( __global float* result_fmax, int N)
{
	float t1 = 1.0;
	float2 t2 = t1 + (float2)(0,0.1);
	int i = 0;
	for(i = 0; i < N; i++){
		repeat256(t2 = fmax(t2, t2););
	}
	*result_fmax = t2.s0 + t2.s1;
}

__kernel void kernel_fmax_withDD4( __global float* result_fmax, int N)
{
	float t1 = 1.0;
	float4 t2 = t1 + (float4)(0,0.1,0.2,0.3);
	int i = 0;
	for(i = 0; i < N; i++){
		repeat256(t2 = fmax(t2, t2););
	}
	*result_fmax = t2.s0 + t2.s1 + t2.s2 + t2.s3;
}

__kernel void kernel_fmax_withDD8( __global float* result_fmax, int N)
{
	float t1 = 1.0;
	float8 t2 = t1 + (float8)(0,0.1,0.2,0.3,0.4,0.5,0.6,0.7);
	int i = 0;
	for(i = 0; i < N; i++){
		repeat256(t2 = fmax(t2, t2););
	}
	*result_fmax = t2.s0 + t2.s1 + t2.s2 + t2.s3 + t2.s4 + t2.s5 + t2.s6 +t2.s7;
}

__kernel void kernel_fmax_withDD16( __global float* result_fmax, int N)
{
	float t1 = 1.0;
	float16 t2 = t1 + (float16)(0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5);
	int i = 0;
	for(i = 0; i < N; i++){
		repeat256(t2 = fmax(t2, t2););
	}
	*result_fmax = t2.s0 + t2.s1 + t2.s2 + t2.s3 + t2.s4 + t2.s5 + t2.s6 +t2.s7+t2.s8+t2.s9+t2.sa+t2.sb+t2.sc+t2.sd+t2.se+t2.sf;
}

__kernel void kernel_fmax_withoutDD1( __global float* result_fmax, int N)
{
  float  t1 = -1;
  float  t2 = -1;
  float  t3 = t1;
  float  t4 = t3;
  float  t5 = t4;
  float  t6 = t5;
  float  t7 = t6;
  float  t8 = t7;
  float  t9 = t8;
  float  t10 = t9;
  float  t11 = -1;
  float  t12 = -1;
  float  t13 = t1;
  float  t14 = t3;
  float  t15 = t4;
  float  t16 = t5;
  float  t17 = t6;
  float  t18 = t7;
  float  t19 = t8;
  float  t20 = t9;
  float  t21 = -1;
  float  t22 = -1;
  float  t23 = t1;
  float  t24 = t3;
  float  t25 = t4;
  float  t26 = t5;
  float  t27 = t6;
  float  t28 = t7;
  float  t29 = t8;
  float  t30 = t9;

  float i = 0;

  int j = 0;
  for(j = 0; j < 100 * N; j++) {
    t1 += fmax(t1, i);
    t2 += fmax(t2, i);
    t3 += fmax(t3, i);
    t4 += fmax(t4, i);
    t5 += fmax(t5, i);
    t6 += fmax(t6, i);
    t7 += fmax(t7, i);
    t8 += fmax(t8, i);
    t9 += fmax(t9, i);
    t10 += fmax(t10, i);
    t11 += fmax(t11, i);
    t12 += fmax(t12, i);
    t13 += fmax(t13, i);
    t14 += fmax(t14, i);
    t15 += fmax(t15, i);
    t16 += fmax(t16, i);
    t17 += fmax(t17, i);
    t18 += fmax(t18, i);
    t19 += fmax(t19, i);
    t20 += fmax(t20, i);
    t21 += fmax(t21, i);
    t22 += fmax(t22, i);
    t22 += fmax(t23, i);
    t24 += fmax(t24, i);
    t25 += fmax(t25, i);
    t26 += fmax(t26, i);
    t27 += fmax(t27, i);
    t28 += fmax(t28, i);
    t29 += fmax(t29, i);
    t30 += fmax(t30, i);
  }
  *result_fmax = t1 + t2 + t3 + t4 + t5 + t6 + t7 + t8 + t9 + t10 + t11 + t12 + t13 + t14 + t15 + t16 + t17 + t18 + t19 + t20 + t21 + t22 + t23 + t24 + t25 + t26 + t27 + t28 + t29 + t30;

}

__kernel void kernel_fmax_withoutDD2(__global float * result_fmax, int N)
{
  float2  t1 = -1 + (float2)(0);
  float2  t2 = -1 + (float2)(0);
  float2  t3 = t1;
  float2  t4 = t3;
  float2  t5 = t4;
  float2  t6 = t5;
  float2  t7 = t6;
  float2  t8 = t7;
  float2  t9 = t8;
  float2  t10 = t9;
  float2  t11 = -1 + (float2)(0);
  float2  t12 = -1 + (float2)(0);
  float2  t13 = t1;
  float2  t14 = t3;
  float2  t15 = t4;
  float2  t16 = t5;
  float2  t17 = t6;
  float2  t18 = t7;
  float2  t19 = t8;
  float2  t20 = t9;
  float2  t21 = -1;
  float2  t22 = -1;
  float2  t23 = t1;
  float2  t24 = t3;
  float2  t25 = t4;
  float2  t26 = t5;
  float2  t27 = t6;
  float2  t28 = t7;
  float2  t29 = t8;
  float2  t30 = t9;

  float2 i = 0+ (float2)(0);

  int j = 0;
  for(j = 0; j < 100 * N; j++) {
    t1 += fmax(t1, i);
    t2 += fmax(t2, i);
    t3 += fmax(t3, i);
    t4 += fmax(t4, i);
    t5 += fmax(t5, i);
    t6 += fmax(t6, i);
    t7 += fmax(t7, i);
    t8 += fmax(t8, i);
    t9 += fmax(t9, i);
    t10 += fmax(t10, i);
    t11 += fmax(t11, i);
    t12 += fmax(t12, i);
    t13 += fmax(t13, i);
    t14 += fmax(t14, i);
    t15 += fmax(t15, i);
    t16 += fmax(t16, i);
    t17 += fmax(t17, i);
    t18 += fmax(t18, i);
    t19 += fmax(t19, i);
    t20 += fmax(t20, i);
    t21 += fmax(t21, i);
    t22 += fmax(t22, i);
    t22 += fmax(t23, i);
    t24 += fmax(t24, i);
    t25 += fmax(t25, i);
    t26 += fmax(t26, i);
    t27 += fmax(t27, i);
    t28 += fmax(t28, i);
    t29 += fmax(t29, i);
    t30 += fmax(t30, i);
  }
  *result_fmax = t1.s0+t1.s1 + t2.s0+t2.s1 + t3.s0+t3.s1 + t4.s0+t4.s1 + t5.s0+t5.s1 + t6.s0+t6.s1 + t7.s0+t7.s1 + t8.s0+t8.s1 + t9.s0+t9.s1+ t10.s0+t10.s1 + t11.s0+t11.s1 + t12.s0+t12.s1+ t13.s0+t13.s1 + t14.s0+t14.s1 + t15.s0+t15.s1+ t16.s0+t16.s1+ t17.s0+t17.s1 + t18.s0+t18.s1 + t19.s0+t19.s1+ t20.s0+t20.s1+ t21.s0+t21.s1 + t22.s0+t22.s1 + t23.s0+t23.s1 + t24.s0+t24.s1 + t25.s0+t25.s1 + t26.s0+t26.s1 + t27.s0+t27.s1 + t28.s0+t28.s1 + t29.s0+t29.s1 + t30.s0+t30.s1;
}

__kernel void kernel_fmax_withoutDD4(__global float * result_fmax, int N)
{
  float4  t1 = -1 + (float4)(0);
  float4  t2 = -1 + (float4)(0);
  float4  t3 = t1;
  float4  t4 = t3;
  float4  t5 = t4;
  float4  t6 = t5;
  float4  t7 = t6;
  float4  t8 = t7;
  float4  t9 = t8;
  float4  t10 = t9;
  float4  t11 = -1 + (float4)(0);
  float4  t12 = -1 + (float4)(0);
  float4  t13 = t1;
  float4  t14 = t3;
  float4  t15 = t4;
  float4  t16 = t5;
  float4  t17 = t6;
  float4  t18 = t7;
  float4  t19 = t8;
  float4  t20 = t9;
  float4  t21 = -1;
  float4  t22 = -1;
  float4  t23 = t1;
  float4  t24 = t3;
  float4  t25 = t4;
  float4  t26 = t5;
  float4  t27 = t6;
  float4  t28 = t7;
  float4  t29 = t8;
  float4  t30 = t9;

  float4 i = 0+ (float4)(0);

  int j = 0;
  for(j = 0; j < 10 * N; j++) {
    t1 += fmax(t1, i);
    t2 += fmax(t2, i);
    t3 += fmax(t3, i);
    t4 += fmax(t4, i);
    t5 += fmax(t5, i);
    t6 += fmax(t6, i);
    t7 += fmax(t7, i);
    t8 += fmax(t8, i);
    t9 += fmax(t9, i);
    t10 += fmax(t10, i);
    t11 += fmax(t11, i);
    t12 += fmax(t12, i);
    t13 += fmax(t13, i);
    t14 += fmax(t14, i);
    t15 += fmax(t15, i);
    t16 += fmax(t16, i);
    t17 += fmax(t17, i);
    t18 += fmax(t18, i);
    t19 += fmax(t19, i);
    t20 += fmax(t20, i);
    t21 += fmax(t21, i);
    t22 += fmax(t22, i);
    t22 += fmax(t23, i);
    t24 += fmax(t24, i);
    t25 += fmax(t25, i);
    t26 += fmax(t26, i);
    t27 += fmax(t27, i);
    t28 += fmax(t28, i);
    t29 += fmax(t29, i);
    t30 += fmax(t30, i);
  }
  *result_fmax = t1.s0+t1.s1+t1.s2+t1.s3 + t2.s0+t2.s1+t2.s2+t2.s3 + t3.s0+t3.s1+t3.s2+t3.s3 + t4.s0+t4.s1+t4.s2+t4.s3 + t5.s0+t5.s1+t5.s2+t5.s3 + t6.s0+t6.s1+t6.s2+t6.s3 + t7.s0+t7.s1+t7.s2+t7.s3 + t8.s0+t8.s1+t8.s2+t8.s3 + t9.s0+t9.s1+t9.s2+t9.s3 + t10.s0+t10.s1+t10.s2+t10.s3 + t11.s0+t11.s1+t11.s2+t11.s3 + t12.s0+t12.s1+t12.s2+t12.s3 + t13.s0+t13.s1+t13.s2+t13.s3 + t14.s0+t14.s1+t14.s2+t14.s3 + t15.s0+t15.s1+t15.s2+t15.s3 + t16.s0+t16.s1+t16.s2+t16.s3 + t17.s0+t17.s1+t17.s2+t17.s3 + t18.s0+t18.s1+t18.s2+t18.s3 + t19.s0+t19.s1+t19.s2+t19.s3 + t20.s0+t20.s1+t20.s2+t20.s3 + t21.s0+t21.s1+t21.s2+t21.s3 + t22.s0+t22.s1+t22.s2+t22.s3 + t23.s0+t23.s1+t23.s2+t23.s3 + t24.s0+t24.s1+t24.s2+t24.s3 + t25.s0+t25.s1+t25.s2+t25.s3 + t26.s0+t26.s1+t26.s2+t26.s3 + t27.s0+t27.s1+t27.s2+t27.s3 + t28.s0+t28.s1+t28.s2+t28.s3 + t29.s0+t29.s1+t29.s2+t29.s3 + t30.s0+t30.s1+t30.s2+t30.s3;
}


__kernel void kernel_fmax_withoutDD8(__global float * result_fmax, int N)
{
  float8  t1 = -1 + (float8)(0);
  float8  t2 = -1 + (float8)(0);
  float8  t3 = t1;
  float8  t4 = t3;
  float8  t5 = t4;
  float8  t6 = t5;
  float8  t7 = t6;
  float8  t8 = t7;
  float8  t9 = t8;
  float8  t10 = t9;
  float8  t11 = -1 + (float8)(0);
  float8  t12 = -1 + (float8)(0);
  float8  t13 = t1;
  float8  t14 = t3;
  float8  t15 = t4;
  float8  t16 = t5;
  float8  t17 = t6;
  float8  t18 = t7;
  float8  t19 = t8;
  float8  t20 = t9;
  float8  t21 = -1;
  float8  t22 = -1;
  float8  t23 = t1;
  float8  t24 = t3;
  float8  t25 = t4;
  float8  t26 = t5;
  float8  t27 = t6;
  float8  t28 = t7;
  float8  t29 = t8;
  float8  t30 = t9;

  float8 i = 0+ (float8)(0);

  int j = 0;
  for(j = 0; j <  N; j++) {
    t1 += fmax(t1, i);
    t2 += fmax(t2, i);
    t3 += fmax(t3, i);
    t4 += fmax(t4, i);
    t5 += fmax(t5, i);
    t6 += fmax(t6, i);
    t7 += fmax(t7, i);
    t8 += fmax(t8, i);
    t9 += fmax(t9, i);
    t10 += fmax(t10, i);
    t11 += fmax(t11, i);
    t12 += fmax(t12, i);
    t13 += fmax(t13, i);
    t14 += fmax(t14, i);
    t15 += fmax(t15, i);
    t16 += fmax(t16, i);
    t17 += fmax(t17, i);
    t18 += fmax(t18, i);
    t19 += fmax(t19, i);
    t20 += fmax(t20, i);
    t21 += fmax(t21, i);
    t22 += fmax(t22, i);
    t22 += fmax(t23, i);
    t24 += fmax(t24, i);
    t25 += fmax(t25, i);
    t26 += fmax(t26, i);
    t27 += fmax(t27, i);
    t28 += fmax(t28, i);
    t29 += fmax(t29, i);
    t30 += fmax(t30, i);
  }
  *result_fmax = t1.s0+t1.s1+t1.s2+t1.s3+t1.s4+t1.s5+t1.s6+t1.s7
  			  + t2.s0+t2.s1+t2.s2+t2.s3+t2.s4+t2.s5+t2.s6+t2.s7
  			  + t3.s0+t3.s1+t3.s2+t3.s3+t3.s4+t3.s5+t3.s6+t3.s7 
  			  + t4.s0+t4.s1+t4.s2+t4.s3+t4.s4+t4.s5+t4.s6+t4.s7 
  			  + t5.s0+t5.s1+t5.s2+t5.s3+t5.s4+t5.s5+t5.s6+t5.s7 
  			  + t6.s0+t6.s1+t6.s2+t6.s3+t6.s4+t6.s5+t6.s6+t6.s7 
  			  + t7.s0+t7.s1+t7.s2+t7.s3+t7.s4+t7.s5+t7.s6+t7.s7 
  			  + t8.s0+t8.s1+t8.s2+t8.s3+t8.s4+t8.s5+t8.s6+t8.s7 
  			  + t9.s0+t9.s1+t9.s2+t9.s3+t9.s4+t9.s5+t9.s6+t9.s7 
  			  + t10.s0+t10.s1+t10.s2+t10.s3+t10.s4+t10.s5+t10.s6+t10.s7 
  			  + t11.s0+t11.s1+t11.s2+t11.s3+t11.s4+t11.s5+t11.s6+t11.s7 
  			  + t12.s0+t12.s1+t12.s2+t12.s3+t12.s4+t12.s5+t12.s6+t12.s7 
  			  + t13.s0+t13.s1+t13.s2+t13.s3+t13.s4+t13.s5+t13.s6+t13.s7 
  			  + t14.s0+t14.s1+t14.s2+t14.s3+t14.s4+t14.s5+t14.s6+t14.s7 
  			  + t15.s0+t15.s1+t15.s2+t15.s3+t15.s4+t15.s5+t15.s6+t15.s7 
  			  + t16.s0+t16.s1+t16.s2+t16.s3+t16.s4+t16.s5+t16.s6+t16.s7 
  			  + t17.s0+t17.s1+t17.s2+t17.s3+t17.s4+t17.s5+t17.s6+t17.s7 
  			  + t18.s0+t18.s1+t18.s2+t18.s3+t18.s4+t18.s5+t18.s6+t18.s7 
  			  + t19.s0+t19.s1+t19.s2+t19.s3+t19.s4+t19.s5+t19.s6+t19.s7 
  			  + t20.s0+t20.s1+t20.s2+t20.s3+t20.s4+t20.s5+t20.s6+t20.s7 
  			  + t21.s0+t21.s1+t21.s2+t21.s3+t21.s4+t21.s5+t21.s6+t21.s7 
  			  + t22.s0+t22.s1+t22.s2+t22.s3+t22.s4+t22.s5+t22.s6+t22.s7 
  			  + t23.s0+t23.s1+t23.s2+t23.s3+t23.s4+t23.s5+t23.s6+t23.s7 
  			  + t24.s0+t24.s1+t24.s2+t24.s3+t24.s4+t24.s5+t24.s6+t24.s7 
  			  + t25.s0+t25.s1+t25.s2+t25.s3+t25.s4+t25.s5+t25.s6+t25.s7 
  			  + t26.s0+t26.s1+t26.s2+t26.s3+t26.s4+t26.s5+t26.s6+t26.s7 
  			  + t27.s0+t27.s1+t27.s2+t27.s3+t27.s4+t27.s5+t27.s6+t27.s7 
  			  + t28.s0+t28.s1+t28.s2+t28.s3+t28.s4+t28.s5+t28.s6+t28.s7 
  			  + t29.s0+t29.s1+t29.s2+t29.s3+t29.s4+t29.s5+t29.s6+t29.s7 
  			  + t30.s0+t30.s1+t30.s2+t30.s3+t30.s4+t30.s5+t30.s6+t30.s7;
}

__kernel void kernel_fmax_withoutDD16(__global float * result_fmax, int N)
{
  float16  t1 = -1 + (float16)(0);
  float16  t2 = -1 + (float16)(0);
  float16  t3 = t1;
  float16  t4 = t3;
  float16  t5 = t4;
  float16  t6 = t5;
  float16  t7 = t6;
  float16  t8 = t7;
  float16  t9 = t8;
  float16  t10 = t9;
  float16  t11 = -1 + (float16)(0);
  float16  t12 = -1 + (float16)(0);
  float16  t13 = t1;
  float16  t14 = t3;
  float16  t15 = t4;
  float16  t16 = t5;
  float16  t17 = t6;
  float16  t18 = t7;
  float16  t19 = t8;
  float16  t20 = t9;
  float16  t21 = -1;
  float16  t22 = -1;
  float16  t23 = t1;
  float16  t24 = t3;
  float16  t25 = t4;
  float16  t26 = t5;
  float16  t27 = t6;
  float16  t28 = t7;
  float16  t29 = t8;
  float16  t30 = t9;

  float16 i = 0+ (float16)(0);

  int j = 0;
  for(j = 0; j <  N; j++) {
    t1 += fmax(t1, i);
    t2 += fmax(t2, i);
    t3 += fmax(t3, i);
    t4 += fmax(t4, i);
    t5 += fmax(t5, i);
    t6 += fmax(t6, i);
    t7 += fmax(t7, i);
    t8 += fmax(t8, i);
    t9 += fmax(t9, i);
    t10 += fmax(t10, i);
    t11 += fmax(t11, i);
    t12 += fmax(t12, i);
    t13 += fmax(t13, i);
    t14 += fmax(t14, i);
    t15 += fmax(t15, i);
    t16 += fmax(t16, i);
    t17 += fmax(t17, i);
    t18 += fmax(t18, i);
    t19 += fmax(t19, i);
    t20 += fmax(t20, i);
    t21 += fmax(t21, i);
    t22 += fmax(t22, i);
    t22 += fmax(t23, i);
    t24 += fmax(t24, i);
    t25 += fmax(t25, i);
    t26 += fmax(t26, i);
    t27 += fmax(t27, i);
    t28 += fmax(t28, i);
    t29 += fmax(t29, i);
    t30 += fmax(t30, i);
  }
  *result_fmax = t1.s0+t1.s1+t1.s2+t1.s3+t1.s4+t1.s5+t1.s6+t1.s7+t1.s8+t1.s9+t1.sa+t1.sb+t1.sc+t1.sd+t1.se+t1.sf
  			  + t2.s0+t2.s1+t2.s2+t2.s3+t2.s4+t2.s5+t2.s6+t2.s7+t2.s8+t2.s9+t2.sa+t2.sb+t2.sc+t2.sd+t2.se+t2.sf
  			  + t3.s0+t3.s1+t3.s2+t3.s3+t3.s4+t3.s5+t3.s6+t3.s7+t3.s8+t3.s9+t3.sa+t3.sb+t3.sc+t3.sd+t3.se+t3.sf
  			  + t4.s0+t4.s1+t4.s2+t4.s3+t4.s4+t4.s5+t4.s6+t4.s7+t4.s8+t4.s9+t4.sa+t4.sb+t4.sc+t4.sd+t4.se+t4.sf 
  			  + t5.s0+t5.s1+t5.s2+t5.s3+t5.s4+t5.s5+t5.s6+t5.s7+t5.s8+t5.s9+t5.sa+t5.sb+t5.sc+t5.sd+t5.se+t5.sf 
  			  + t6.s0+t6.s1+t6.s2+t6.s3+t6.s4+t6.s5+t6.s6+t6.s7+t6.s8+t6.s9+t6.sa+t6.sb+t6.sc+t6.sd+t6.se+t6.sf 
  			  + t7.s0+t7.s1+t7.s2+t7.s3+t7.s4+t7.s5+t7.s6+t7.s7+t7.s8+t7.s9+t7.sa+t7.sb+t7.sc+t7.sd+t7.se+t7.sf 
  			  + t8.s0+t8.s1+t8.s2+t8.s3+t8.s4+t8.s5+t8.s6+t8.s7+t8.s8+t8.s9+t8.sa+t8.sb+t8.sc+t8.sd+t8.se+t8.sf 
  			  + t9.s0+t9.s1+t9.s2+t9.s3+t9.s4+t9.s5+t9.s6+t9.s7+t9.s8+t9.s9+t9.sa+t9.sb+t9.sc+t9.sd+t9.se+t9.sf 
  			  + t10.s0+t10.s1+t10.s2+t10.s3+t10.s4+t10.s5+t10.s6+t10.s7+t10.s8+t10.s9+t10.sa+t10.sb+t10.sc+t10.sd+t10.se+t10.sf 
  			  + t11.s0+t11.s1+t11.s2+t11.s3+t11.s4+t11.s5+t11.s6+t11.s7+t11.s8+t11.s9+t11.sa+t11.sb+t11.sc+t11.sd+t11.se+t11.sf 
  			  + t12.s0+t12.s1+t12.s2+t12.s3+t12.s4+t12.s5+t12.s6+t12.s7+t12.s8+t12.s9+t12.sa+t12.sb+t12.sc+t12.sd+t12.se+t12.sf 
  			  + t13.s0+t13.s1+t13.s2+t13.s3+t13.s4+t13.s5+t13.s6+t13.s7+t13.s8+t13.s9+t13.sa+t13.sb+t13.sc+t13.sd+t13.se+t13.sf 
  			  + t14.s0+t14.s1+t14.s2+t14.s3+t14.s4+t14.s5+t14.s6+t14.s7+t14.s8+t14.s9+t14.sa+t14.sb+t14.sc+t14.sd+t14.se+t14.sf 
  			  + t15.s0+t15.s1+t15.s2+t15.s3+t15.s4+t15.s5+t15.s6+t15.s7+t15.s8+t15.s9+t15.sa+t15.sb+t15.sc+t15.sd+t15.se+t15.sf 
  			  + t16.s0+t16.s1+t16.s2+t16.s3+t16.s4+t16.s5+t16.s6+t16.s7+t16.s8+t16.s9+t16.sa+t16.sb+t16.sc+t16.sd+t16.se+t16.sf 
  			  + t17.s0+t17.s1+t17.s2+t17.s3+t17.s4+t17.s5+t17.s6+t17.s7+t17.s8+t17.s9+t17.sa+t17.sb+t17.sc+t17.sd+t17.se+t17.sf 
  			  + t18.s0+t18.s1+t18.s2+t18.s3+t18.s4+t18.s5+t18.s6+t18.s7+t18.s8+t18.s9+t18.sa+t18.sb+t18.sc+t18.sd+t18.se+t18.sf 
  			  + t19.s0+t19.s1+t19.s2+t19.s3+t19.s4+t19.s5+t19.s6+t19.s7+t19.s8+t19.s9+t19.sa+t19.sb+t19.sc+t19.sd+t19.se+t19.sf 
  			  + t20.s0+t20.s1+t20.s2+t20.s3+t20.s4+t20.s5+t20.s6+t20.s7+t20.s8+t20.s9+t20.sa+t20.sb+t20.sc+t20.sd+t20.se+t20.sf 
  			  + t21.s0+t21.s1+t21.s2+t21.s3+t21.s4+t21.s5+t21.s6+t21.s7+t21.s8+t21.s9+t21.sa+t21.sb+t21.sc+t21.sd+t21.se+t21.sf 
  			  + t22.s0+t22.s1+t22.s2+t22.s3+t22.s4+t22.s5+t22.s6+t22.s7+t22.s8+t22.s9+t22.sa+t22.sb+t22.sc+t22.sd+t22.se+t22.sf 
  			  + t23.s0+t23.s1+t23.s2+t23.s3+t23.s4+t23.s5+t23.s6+t23.s7+t23.s8+t23.s9+t23.sa+t23.sb+t23.sc+t23.sd+t23.se+t23.sf 
  			  + t24.s0+t24.s1+t24.s2+t24.s3+t24.s4+t24.s5+t24.s6+t24.s7+t24.s8+t24.s9+t24.sa+t24.sb+t24.sc+t24.sd+t24.se+t24.sf 
  			  + t25.s0+t25.s1+t25.s2+t25.s3+t25.s4+t25.s5+t25.s6+t25.s7+t25.s8+t25.s9+t25.sa+t25.sb+t25.sc+t25.sd+t25.se+t25.sf 
  			  + t26.s0+t26.s1+t26.s2+t26.s3+t26.s4+t26.s5+t26.s6+t26.s7+t26.s8+t26.s9+t26.sa+t26.sb+t26.sc+t26.sd+t26.se+t26.sf 
  			  + t27.s0+t27.s1+t27.s2+t27.s3+t27.s4+t27.s5+t27.s6+t27.s7+t27.s8+t27.s9+t27.sa+t27.sb+t27.sc+t27.sd+t27.se+t27.sf 
  			  + t28.s0+t28.s1+t28.s2+t28.s3+t28.s4+t28.s5+t28.s6+t28.s7+t28.s8+t28.s9+t28.sa+t28.sb+t28.sc+t28.sd+t28.se+t28.sf 
  			  + t29.s0+t29.s1+t29.s2+t29.s3+t29.s4+t29.s5+t29.s6+t29.s7+t29.s8+t29.s9+t29.sa+t29.sb+t29.sc+t29.sd+t29.se+t29.sf 
  			  + t30.s0+t30.s1+t30.s2+t30.s3+t30.s4+t30.s5+t30.s6+t30.s7+t30.s8+t30.s9+t30.sa+t30.sb+t30.sc+t30.sd+t30.se+t30.sf;
}

__kernel void kernel_fmin_withDD1(__global float* result_fmin, int N)
{
  float t1 = 1.0;
  float t2 = 0;
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat256(t2 = fmin(t1, t2););
  }
  *result_fmin = t2;
}

__kernel void kernel_fmin_withDD2(__global float* result_fmin, int N)
{
  float2 t1 = 1.0+(float2)(0);
  float2 t2 = 0+(float2)(0);
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat256(t2 = fmin(t1, t2););
  }
  *result_fmin = t2.s0 + t2.s1;
}

__kernel void kernel_fmin_withDD4(__global float* result_fmin, int N)
{
  float4 t1 = 1.0+(float4)(0);
  float4 t2 = 0+(float4)(0);
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat256(t2 = fmin(t1, t2););
  }
  *result_fmin = t2.s0 + t2.s1 + t2.s2 + t2.s3;
}

__kernel void kernel_fmin_withDD8(__global float* result_fmin, int N)
{
  float8 t1 = 1.0+(float8)(0);
  float8 t2 = 0+(float8)(0);
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat256(t2 = fmin(t1, t2););
  }
  *result_fmin = t2.s0 + t2.s1 + t2.s2 + t2.s3 + t2.s4 + t2.s5 + t2.s6 +t2.s7;
}

__kernel void kernel_fmin_withDD16(__global float* result_fmin, int N)
{
  float16 t1 = 1.0+(float16)(0);
  float16 t2 = 0+(float16)(0);
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat256(t2 = fmin(t1, t2););
  }
  *result_fmin = t2.s0 + t2.s1 + t2.s2 + t2.s3 + t2.s4 + t2.s5 + t2.s6 +t2.s7+t2.s8+t2.s9+t2.sa+t2.sb+t2.sc+t2.sd+t2.se+t2.sf;
}

__kernel void kernel_fmin_withoutDD1(__global float* result_fmin, int N)
{
  float  t1 = 0.234;
  float  t2 = 0.235;
  float  t3 = t1;
  float  t4 = t3;
  float  t5 = t4;
  float  t6 = t5;
  float  t7 = t6;
  float  t8 = t7;
  float  t9 = t8;
  float  t10 = t9;
  float  t11 = 0.234;
  float  t12 = 0.235;
  float  t13 = t1;
  float  t14 = t3;
  float  t15 = t4;
  float  t16 = t5;
  float  t17 = t6;
  float  t18 = t7;
  float  t19 = t8;
  float  t20 = t9;
  float  t21 = 0.234;
  float  t22 = 0.235;
  float  t23 = t1;
  float  t24 = t3;
  float  t25 = t4;
  float  t26 = t5;
  float  t27 = t6;
  float  t28 = t7;
  float  t29 = t8;
  float  t30 = t9;

  float i = 0.01;

  int j = 0;
  for(j = 0; j <= 100 * N; j++) {
    t1 += fmin(t1, i);
    t2 += fmin(t2, i);
    t3 += fmin(t3, i);
    t4 += fmin(t4, i);
    t5 += fmin(t5, i);
    t6 += fmin(t6, i);
    t7 += fmin(t7, i);
    t8 += fmin(t8, i);
    t9 += fmin(t9, i);
    t10 += fmin(t10, i);
    t11 += fmin(t11, i);
    t12 += fmin(t12, i);
    t13 += fmin(t13, i);
    t14 += fmin(t14, i);
    t15 += fmin(t15, i);
    t16 += fmin(t16, i);
    t17 += fmin(t17, i);
    t18 += fmin(t18, i);
    t19 += fmin(t19, i);
    t20 += fmin(t20, i);
    t21 += fmin(t21, i);
    t22 += fmin(t22, i);
    t23 += fmin(t23, i);
    t24 += fmin(t24, i);
    t25 += fmin(t25, i);
    t26 += fmin(t26, i);
    t27 += fmin(t27, i);
    t28 += fmin(t28, i);
    t29 += fmin(t29, i);
    t30 += fmin(t30, i);
 }
  *result_fmin = t1 + t2 + t3 + t4 + t5 + t6 + t7 + t8 + t9 + t10 + t11 + t12 + t13 + t14 + t15 + t16 + t17 + t18 + t19 + t20 + t21 + t22 + t23 + t24 + t25 + t26 + t27 + t28 + t29 + t30;
}

__kernel void kernel_fmin_withoutDD2(__global float* result_fmin, int N)
{
  float2  t1 = 0.234+(float2)(0);
  float2  t2 = 0.235+(float2)(0);
  float2  t3 = t1;
  float2  t4 = t3;
  float2  t5 = t4;
  float2  t6 = t5;
  float2  t7 = t6;
  float2  t8 = t7;
  float2  t9 = t8;
  float2  t10 = t9;
  float2  t11 = 0.234+(float2)(0);
  float2  t12 = 0.235+(float2)(0);
  float2  t13 = t1;
  float2  t14 = t3;
  float2  t15 = t4;
  float2  t16 = t5;
  float2  t17 = t6;
  float2  t18 = t7;
  float2  t19 = t8;
  float2  t20 = t9;
  float2  t21 = 0.234+(float2)(0);
  float2  t22 = 0.235+(float2)(0);
  float2  t23 = t1;
  float2  t24 = t3;
  float2  t25 = t4;
  float2  t26 = t5;
  float2  t27 = t6;
  float2  t28 = t7;
  float2  t29 = t8;
  float2  t30 = t9;

  float2 i = 0.01+(float2)(0);

  int j = 0;
  for(j = 0; j <= 100 * N; j++) {
    t1 += fmin(t1, i);
    t2 += fmin(t2, i);
    t3 += fmin(t3, i);
    t4 += fmin(t4, i);
    t5 += fmin(t5, i);
    t6 += fmin(t6, i);
    t7 += fmin(t7, i);
    t8 += fmin(t8, i);
    t9 += fmin(t9, i);
    t10 += fmin(t10, i);
    t11 += fmin(t11, i);
    t12 += fmin(t12, i);
    t13 += fmin(t13, i);
    t14 += fmin(t14, i);
    t15 += fmin(t15, i);
    t16 += fmin(t16, i);
    t17 += fmin(t17, i);
    t18 += fmin(t18, i);
    t19 += fmin(t19, i);
    t20 += fmin(t20, i);
    t21 += fmin(t21, i);
    t22 += fmin(t22, i);
    t23 += fmin(t23, i);
    t24 += fmin(t24, i);
    t25 += fmin(t25, i);
    t26 += fmin(t26, i);
    t27 += fmin(t27, i);
    t28 += fmin(t28, i);
    t29 += fmin(t29, i);
    t30 += fmin(t30, i);
  }
  *result_fmin = t1.s0+t1.s1 + t2.s0+t2.s1 + t3.s0+t3.s1 + t4.s0+t4.s1 + t5.s0+t5.s1 + t6.s0+t6.s1 + t7.s0+t7.s1 + t8.s0+t8.s1 + t9.s0+t9.s1+ t10.s0+t10.s1 + t11.s0+t11.s1 + t12.s0+t12.s1+ t13.s0+t13.s1 + t14.s0+t14.s1 + t15.s0+t15.s1+ t16.s0+t16.s1+ t17.s0+t17.s1 + t18.s0+t18.s1 + t19.s0+t19.s1+ t20.s0+t20.s1+ t21.s0+t21.s1 + t22.s0+t22.s1 + t23.s0+t23.s1 + t24.s0+t24.s1 + t25.s0+t25.s1 + t26.s0+t26.s1 + t27.s0+t27.s1 + t28.s0+t28.s1 + t29.s0+t29.s1 + t30.s0+t30.s1;
}

__kernel void kernel_fmin_withoutDD4(__global float* result_fmin, int N)
{
  float4 t1 = 0.234+(float4)(0);
  float4 t2 = 0.235+(float4)(0);
  float4 t3 = t1;
  float4 t4 = t3;
  float4 t5 = t4;
  float4 t6 = t5;
  float4 t7 = t6;
  float4 t8 = t7;
  float4 t9 = t8;
  float4 t10 = t9;
  float4 t11 = 0.234+(float4)(0);
  float4 t12 = 0.235+(float4)(0);
  float4 t13 = t1;
  float4 t14 = t3;
  float4 t15 = t4;
  float4 t16 = t5;
  float4 t17 = t6;
  float4 t18 = t7;
  float4 t19 = t8;
  float4 t20 = t9;
  float4 t21 = 0.234+(float4)(0);
  float4 t22 = 0.235+(float4)(0);
  float4 t23 = t1;
  float4 t24 = t3;
  float4 t25 = t4;
  float4 t26 = t5;
  float4 t27 = t6;
  float4 t28 = t7;
  float4 t29 = t8;
  float4 t30 = t9;

  float4 i = 0.01+(float4)(0);

  int j = 0;
  for(j = 0; j <= 100 * N; j++) {
    t1 += fmin(t1, i);
    t2 += fmin(t2, i);
    t3 += fmin(t3, i);
    t4 += fmin(t4, i);
    t5 += fmin(t5, i);
    t6 += fmin(t6, i);
    t7 += fmin(t7, i);
    t8 += fmin(t8, i);
    t9 += fmin(t9, i);
    t10 += fmin(t10, i);
    t11 += fmin(t11, i);
    t12 += fmin(t12, i);
    t13 += fmin(t13, i);
    t14 += fmin(t14, i);
    t15 += fmin(t15, i);
    t16 += fmin(t16, i);
    t17 += fmin(t17, i);
    t18 += fmin(t18, i);
    t19 += fmin(t19, i);
    t20 += fmin(t20, i);
    t21 += fmin(t21, i);
    t22 += fmin(t22, i);
    t23 += fmin(t23, i);
    t24 += fmin(t24, i);
    t25 += fmin(t25, i);
    t26 += fmin(t26, i);
    t27 += fmin(t27, i);
    t28 += fmin(t28, i);
    t29 += fmin(t29, i);
    t30 += fmin(t30, i);
  }
  *result_fmin = t1.s0+t1.s1+t1.s2+t1.s3 + t2.s0+t2.s1+t2.s2+t2.s3
		      + t3.s0+t3.s1+t3.s2+t3.s3 + t4.s0+t4.s1+t4.s2+t4.s3
			  + t5.s0+t5.s1+t5.s2+t5.s3 + t6.s0+t6.s1+t6.s2+t6.s3
			  + t7.s0+t7.s1+t7.s2+t7.s3 + t8.s0+t8.s1+t8.s2+t8.s3
			  + t9.s0+t9.s1+t9.s2+t9.s3 + t10.s0+t10.s1+t10.s2+t10.s3
			  + t11.s0+t11.s1+t11.s2+t11.s3 + t12.s0+t12.s1+t12.s2+t12.s3
			  + t13.s0+t13.s1+t13.s2+t13.s3 + t14.s0+t14.s1+t14.s2+t14.s3
			  + t15.s0+t15.s1+t15.s2+t15.s3;
}

__kernel void kernel_fmin_withoutDD8(__global float* result_fmin, int N)
{
  float8 t1 = 0.234+(float8)(0);
  float8 t2 = 0.235+(float8)(0);
  float8 t3 = t1;
  float8 t4 = t3;
  float8 t5 = t4;
  float8 t6 = t5;
  float8 t7 = t6;
  float8 t8 = t7;
  float8 t9 = t8;
  float8 t10 = t9;
  float8 t11 = 0.234+(float8)(0);
  float8 t12 = 0.235+(float8)(0);
  float8 t13 = t1;
  float8 t14 = t3;
  float8 t15 = t4;
  float8 t16 = t5;
  float8 t17 = t6;
  float8 t18 = t7;
  float8 t19 = t8;
  float8 t20 = t9;
  float8 t21 = 0.234+(float8)(0);
  float8 t22 = 0.235+(float8)(0);
  float8 t23 = t1;
  float8 t24 = t3;
  float8 t25 = t4;
  float8 t26 = t5;
  float8 t27 = t6;
  float8 t28 = t7;
  float8 t29 = t8;
  float8 t30 = t9;

  float8 i = 0.01+(float8)(0);

  int j = 0;
  for(j = 0; j <= 10 * N; j++) {
    t1 += fmin(t1, i);
    t2 += fmin(t2, i);
    t3 += fmin(t3, i);
    t4 += fmin(t4, i);
    t5 += fmin(t5, i);
    t6 += fmin(t6, i);
    t7 += fmin(t7, i);
    t8 += fmin(t8, i);
    t9 += fmin(t9, i);
    t10 += fmin(t10, i);
    t11 += fmin(t11, i);
    t12 += fmin(t12, i);
    t13 += fmin(t13, i);
    t14 += fmin(t14, i);
    t15 += fmin(t15, i);
    t16 += fmin(t16, i);
    t17 += fmin(t17, i);
    t18 += fmin(t18, i);
    t19 += fmin(t19, i);
    t20 += fmin(t20, i);
    t21 += fmin(t21, i);
    t22 += fmin(t22, i);
    t23 += fmin(t23, i);
    t24 += fmin(t24, i);
    t25 += fmin(t25, i);
    t26 += fmin(t26, i);
    t27 += fmin(t27, i);
    t28 += fmin(t28, i);
    t29 += fmin(t29, i);
    t30 += fmin(t30, i);
  }
  *result_fmin = t1.s0+t1.s1+t1.s2+t1.s3+t1.s4+t1.s5+t1.s6+t1.s7 + t2.s0+t2.s1+t2.s2+t2.s3+t2.s4+t2.s5+t2.s6+t2.s7 
+ t3.s0+t3.s1+t3.s2+t3.s3+t3.s4+t3.s5+t3.s6+t3.s7 + t4.s0+t4.s1+t4.s2+t4.s3+t4.s4+t4.s5+t4.s6+t4.s7
+ t5.s0+t5.s1+t5.s2+t5.s3+t5.s4+t5.s5+t5.s6+t5.s7 + t6.s0+t6.s1+t6.s2+t6.s3+t6.s4+t6.s5+t6.s6+t6.s7
+ t7.s0+t7.s1+t7.s2+t7.s3+t7.s4+t7.s5+t7.s6+t7.s7 + t8.s0+t8.s1+t8.s2+t8.s3+t8.s4+t8.s5+t8.s6+t8.s7 
+ t9.s0+t9.s1+t9.s2+t9.s3+t9.s4+t9.s5+t9.s6+t9.s7 + t10.s0+t10.s1+t10.s2+t10.s3+t10.s4+t10.s5+t10.s6+t10.s7 
 + t11.s0+t11.s1+t11.s2+t11.s3+t11.s4+t11.s5+t11.s6+t11.s7 + t12.s0+t12.s1+t12.s2+t12.s3+t12.s4+t12.s5+t12.s6+t12.s7 
 + t13.s0+t13.s1+t13.s2+t13.s3+t13.s4+t13.s5+t13.s6+t13.s7 + t14.s0+t14.s1+t14.s2+t14.s3+t13.s4+t13.s5+t13.s6+t13.s7 
+ t15.s0+t15.s1+t15.s2+t15.s3+t15.s4+t15.s5+t15.s6+t15.s7;
}

__kernel void kernel_fmin_withoutDD16(__global float* result_fmin, int N)
{
  float16 t1 = 0.234+(float16)(0);
  float16 t2 = 0.235+(float16)(0);
  float16 t3 = t1;
  float16 t4 = t3;
  float16 t5 = t4;
  float16 t6 = t5;
  float16 t7 = t6;
  float16 t8 = t7;
  float16 t9 = t8;
  float16 t10 = t9;
  float16 t11 = 0.234+(float16)(0);
  float16 t12 = 0.235+(float16)(0);
  float16 t13 = t1;
  float16 t14 = t3;
  float16 t15 = t4;
  float16 t16 = t5;
  float16 t17 = t6;
  float16 t18 = t7;
  float16 t19 = t8;
  float16 t20 = t9;
  float16 t21 = 0.234+(float16)(0);
  float16 t22 = 0.235+(float16)(0);
  float16 t23 = t1;
  float16 t24 = t3;
  float16 t25 = t4;
  float16 t26 = t5;
  float16 t27 = t6;
  float16 t28 = t7;
  float16 t29 = t8;
  float16 t30 = t9;

  float16 i = 0.01+(float16)(0);

  int j = 0;
  for(j = 0; j <=  N; j++) {
    t1 += fmin(t1, i);
    t2 += fmin(t2, i);
    t3 += fmin(t3, i);
    t4 += fmin(t4, i);
    t5 += fmin(t5, i);
    t6 += fmin(t6, i);
    t7 += fmin(t7, i);
    t8 += fmin(t8, i);
    t9 += fmin(t9, i);
    t10 += fmin(t10, i);
    t11 += fmin(t11, i);
    t12 += fmin(t12, i);
    t13 += fmin(t13, i);
    t14 += fmin(t14, i);
    t15 += fmin(t15, i);
    t16 += fmin(t16, i);
    t17 += fmin(t17, i);
    t18 += fmin(t18, i);
    t19 += fmin(t19, i);
    t20 += fmin(t20, i);
    t21 += fmin(t21, i);
    t22 += fmin(t22, i);
    t23 += fmin(t23, i);
    t24 += fmin(t24, i);
    t25 += fmin(t25, i);
    t26 += fmin(t26, i);
    t27 += fmin(t27, i);
    t28 += fmin(t28, i);
    t29 += fmin(t29, i);
    t30 += fmin(t30, i);
  }
    *result_fmin =  t1.s0+t1.s1+t1.s2+t1.s3+t1.s4+t1.s5+t1.s6+t1.s7+t1.s8+t1.s9+t1.sa+t1.sb+t1.sc+t1.sd+t1.se+t1.sf
  			  + t2.s0+t2.s1+t2.s2+t2.s3+t2.s4+t2.s5+t2.s6+t2.s7+t2.s8+t2.s9+t2.sa+t2.sb+t2.sc+t2.sd+t2.se+t2.sf
  			  + t3.s0+t3.s1+t3.s2+t3.s3+t3.s4+t3.s5+t3.s6+t3.s7+t3.s8+t3.s9+t3.sa+t3.sb+t3.sc+t3.sd+t3.se+t3.sf
  			  + t4.s0+t4.s1+t4.s2+t4.s3+t4.s4+t4.s5+t4.s6+t4.s7+t4.s8+t4.s9+t4.sa+t4.sb+t4.sc+t4.sd+t4.se+t4.sf 
  			  + t5.s0+t5.s1+t5.s2+t5.s3+t5.s4+t5.s5+t5.s6+t5.s7+t5.s8+t5.s9+t5.sa+t5.sb+t5.sc+t5.sd+t5.se+t5.sf 
  			  + t6.s0+t6.s1+t6.s2+t6.s3+t6.s4+t6.s5+t6.s6+t6.s7+t6.s8+t6.s9+t6.sa+t6.sb+t6.sc+t6.sd+t6.se+t6.sf 
  			  + t7.s0+t7.s1+t7.s2+t7.s3+t7.s4+t7.s5+t7.s6+t7.s7+t7.s8+t7.s9+t7.sa+t7.sb+t7.sc+t7.sd+t7.se+t7.sf 
  			  + t8.s0+t8.s1+t8.s2+t8.s3+t8.s4+t8.s5+t8.s6+t8.s7+t8.s8+t8.s9+t8.sa+t8.sb+t8.sc+t8.sd+t8.se+t8.sf 
  			  + t9.s0+t9.s1+t9.s2+t9.s3+t9.s4+t9.s5+t9.s6+t9.s7+t9.s8+t9.s9+t9.sa+t9.sb+t9.sc+t9.sd+t9.se+t9.sf 
  			  + t10.s0+t10.s1+t10.s2+t10.s3+t10.s4+t10.s5+t10.s6+t10.s7+t10.s8+t10.s9+t10.sa+t10.sb+t10.sc+t10.sd+t10.se+t10.sf 
  			  + t11.s0+t11.s1+t11.s2+t11.s3+t11.s4+t11.s5+t11.s6+t11.s7+t11.s8+t11.s9+t11.sa+t11.sb+t11.sc+t11.sd+t11.se+t11.sf 
  			  + t12.s0+t12.s1+t12.s2+t12.s3+t12.s4+t12.s5+t12.s6+t12.s7+t12.s8+t12.s9+t12.sa+t12.sb+t12.sc+t12.sd+t12.se+t12.sf 
  			  + t13.s0+t13.s1+t13.s2+t13.s3+t13.s4+t13.s5+t13.s6+t13.s7+t13.s8+t13.s9+t13.sa+t13.sb+t13.sc+t13.sd+t13.se+t13.sf 
  			  + t14.s0+t14.s1+t14.s2+t14.s3+t14.s4+t14.s5+t14.s6+t14.s7+t14.s8+t14.s9+t14.sa+t14.sb+t14.sc+t14.sd+t14.se+t14.sf 
  			  + t15.s0+t15.s1+t15.s2+t15.s3+t15.s4+t15.s5+t15.s6+t15.s7+t15.s8+t15.s9+t15.sa+t15.sb+t15.sc+t15.sd+t15.se+t15.sf;
}


