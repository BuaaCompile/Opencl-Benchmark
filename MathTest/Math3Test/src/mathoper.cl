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

__kernel void kernel_sin_withDD1(__global float* result_sin, int N)
{
  float t1 = 1.0;
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat16(t1 = sin(t1););
  }
  *result_sin = t1;
}

__kernel void kernel_sin_withDD2(__global float* result_sin, int N)
{
  float t1 = 1.0;
  float2 t2 = t1 + (float2)(0,0.1);
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat512(t2 = sin(t2););
  }
  *result_sin = t2.s0 + t2.s1;
}

__kernel void kernel_sin_withDD4(__global float* result_sin, int N)
{
  float t1 = 1.0;
  float4 t2 = t1 + (float4)(0,0.1,0.2,0.3);
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat128(t2 = sin(t2););
  }
  *result_sin =t2.s0 + t2.s1 + t2.s2 + t2.s3;
}

__kernel void kernel_sin_withDD8(__global float* result_sin, int N)
{
  float t1 = 1.0;
  float8 t2 = t1 + (float8)(0,0.1,0.2,0.3,0.4,0.5,0.6,0.7);
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat128(t2 = sin(t2););
  }
  *result_sin = t2.s0 + t2.s1 + t2.s2 + t2.s3 + t2.s4 + t2.s5 + t2.s6 +t2.s7;
}

__kernel void kernel_sin_withDD16(__global float* result_sin, int N)
{
  float t1 = 1.0;
  float16 t2 = t1 + (float16)(0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5);
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat32(t2 = sin(t2););
  }
  *result_sin = t2.s0 + t2.s1 + t2.s2 + t2.s3 + t2.s4 + t2.s5 + t2.s6 +t2.s7+t2.s8+t2.s9+t2.sa+t2.sb+t2.sc+t2.sd+t2.se+t2.sf;
}

__kernel void kernel_sin_withoutDD1(__global float* result_sin, int N)
{
  float  t1 = 1.23;
  float  t2 = 1.23;
  float  t3 = 1.2;
  float  t4 = 1.2;
  float  t5 = 1.2;
  float  t6 = 1.2;
  float  t7 = 1.2;
  float  j = 0.0;

  for(j = 0.0; j < 10 * N; j = j + 1.0) {
    t1 = sin(j);
    t2 = sin(j);
    t3 = sin(j);
    t4 = sin(j);
    t5 = sin(j);
    t6 = sin(j);
    t7 = sin(j);
  }
  *result_sin = t1 + t2 + t3 + t4 + t5 + t6 + t7;
}

__kernel void kernel_sin_withoutDD2(__global float* result_sin, int N)
{
  float2  t1 = (float2)(0);
  float2  t2 = (float2)(0);
  float2  t3 = (float2)(0);
  float2  t4 = (float2)(0);
  float2  t5 = (float2)(0);
  float2  t6 = (float2)(0);
  float2  t7 = (float2)(0);
  float2  j = 0.0+(float2)(0);
  float  i = 0.0;

  for(i = 0.0; i < 10 * N; i=i+1,j = j + 1.0) {
    t1 = sin(j);
    t2 = sin(j);
    t3 = sin(j);
    t4 = sin(j);
    t5 = sin(j);
    t6 = sin(j);
    t7 = sin(j);
  }
  *result_sin = t1.s0+t1.s1 + t2.s0+t2.s1 + t3.s0+t3.s1 + t4.s0+t4.s1 + t5.s0+t5.s1 + t6.s0+t6.s1 + t7.s0+t7.s1;
}

__kernel void kernel_sin_withoutDD4(__global float* result_sin, int N)
{
  float4  t1 = 1.23+(float4)(0,0.1,0,0.1);
  float4  t2 = 1.23+(float4)(0,0.1,0,0.1);
  float4  t3 = 1.2+(float4)(0,0.1,0,0.1);
  float4  t4 = 1.2+(float4)(0,0.1,0,0.1);
  float4  t5 = 1.2+(float4)(0,0.1,0,0.1);
  float4  t6 = 1.2+(float4)(0,0.1,0,0.1);
  float4  t7 = 1.2+(float4)(0,0.1,0,0.1);
  float4  j = 0.0+(float4)(0);
  float  i = 0.0;

  for(i = 0.0; i < 10 * N; i=i+1,j = j + 1.0) {
    t1 = sin(j);
    t2 = sin(j);
    t3 = sin(j);
    t4 = sin(j);
    t5 = sin(j);
    t6 = sin(j);
    t7 = sin(j);
  }
  *result_sin =  t1.s0+t1.s1+t1.s2+t1.s3 + t2.s0+t2.s1+t2.s2+t2.s3
		      + t3.s0+t3.s1+t3.s2+t3.s3 + t4.s0+t4.s1+t4.s2+t4.s3
			  + t5.s0+t5.s1+t5.s2+t5.s3 + t6.s0+t6.s1+t6.s2+t6.s3
			  + t7.s0+t7.s1+t7.s2+t7.s3;
}

__kernel void kernel_sin_withoutDD8(__global float* result_sin, int N)
{
  float8  t1 = 1.23+(float8)(0,0.1,0,0.1,0,0.1,0,0.1);
  float8  t2 = 1.23+(float8)(0,0.1,0,0.1,0,0.1,0,0.1);
  float8  t3 = 1.2+(float8)(0,0.1,0,0.1,0,0.1,0,0.1);
  float8  t4 = 1.2+(float8)(0,0.1,0,0.1,0,0.1,0,0.1);
  float8  t5 = 1.2+(float8)(0,0.1,0,0.1,0,0.1,0,0.1);
  float8  t6 = 1.2+(float8)(0,0.1,0,0.1,0,0.1,0,0.1);
  float8  t7 = 1.2+(float8)(0,0.1,0,0.1,0,0.1,0,0.1);
  float8  j = 0.0+(float8)(0);
  float  i = 0.0;

  for(i = 0.0; i < 10 * N; i=i+1,j = j + 1.0) {
    t1 = sin(j);
    t2 = sin(j);
    t3 = sin(j);
    t4 = sin(j);
    t5 = sin(j);
    t6 = sin(j);
    t7 = sin(j);
  }
  *result_sin =  t1.s0+t1.s1+t1.s2+t1.s3+t1.s4+t1.s5+t1.s6+t1.s7 + t2.s0+t2.s1+t2.s2+t2.s3+t2.s4+t2.s5+t2.s6+t2.s7 
+ t3.s0+t3.s1+t3.s2+t3.s3+t3.s4+t3.s5+t3.s6+t3.s7 + t4.s0+t4.s1+t4.s2+t4.s3+t4.s4+t4.s5+t4.s6+t4.s7
+ t5.s0+t5.s1+t5.s2+t5.s3+t5.s4+t5.s5+t5.s6+t5.s7 + t6.s0+t6.s1+t6.s2+t6.s3+t6.s4+t6.s5+t6.s6+t6.s7
+ t7.s0+t7.s1+t7.s2+t7.s3+t7.s4+t7.s5+t7.s6+t7.s7;
}

__kernel void kernel_sin_withoutDD16(__global float* result_sin, int N)
{
  float16  t1 = 1.23+(float16)(0,0.1,0,0.1,0,0.1,0,0.1,0,0.1,0,0.1,0,0.1,0,0.1);
  float16  t2 = 1.23+(float16)(0,0.1,0,0.1,0,0.1,0,0.1,0,0.1,0,0.1,0,0.1,0,0.1);
  float16  t3 = 1.2+(float16)(0,0.1,0,0.1,0,0.1,0,0.1,0,0.1,0,0.1,0,0.1,0,0.1);
  float16  t4 = 1.2+(float16)(0,0.1,0,0.1,0,0.1,0,0.1,0,0.1,0,0.1,0,0.1,0,0.1);
  float16  t5 = 1.2+(float16)(0,0.1,0,0.1,0,0.1,0,0.1,0,0.1,0,0.1,0,0.1,0,0.1);
  float16  t6 = 1.2+(float16)(0,0.1,0,0.1,0,0.1,0,0.1,0,0.1,0,0.1,0,0.1,0,0.1);
  float16  t7 = 1.2+(float16)(0,0.1,0,0.1,0,0.1,0,0.1,0,0.1,0,0.1,0,0.1,0,0.1);
  float16  j = 0.0+(float16)(0);
  float  i = 0.0;

  for(i = 0.0; i < 3 * N; i=i+1,j = j + 1.0) {
    t1 = sin(j);
    t2 = sin(j);
    t3 = sin(j);
    t4 = sin(j);
    t5 = sin(j);
    t6 = sin(j);
    t7 = sin(j);
  }
  *result_sin =   t1.s0+t1.s1+t1.s2+t1.s3+t1.s4+t1.s5+t1.s6+t1.s7+t1.s8+t1.s9+t1.sa+t1.sb+t1.sc+t1.sd+t1.se+t1.sf
  			  + t2.s0+t2.s1+t2.s2+t2.s3+t2.s4+t2.s5+t2.s6+t2.s7+t2.s8+t2.s9+t2.sa+t2.sb+t2.sc+t2.sd+t2.se+t2.sf
  			  + t3.s0+t3.s1+t3.s2+t3.s3+t3.s4+t3.s5+t3.s6+t3.s7+t3.s8+t3.s9+t3.sa+t3.sb+t3.sc+t3.sd+t3.se+t3.sf
  			  + t4.s0+t4.s1+t4.s2+t4.s3+t4.s4+t4.s5+t4.s6+t4.s7+t4.s8+t4.s9+t4.sa+t4.sb+t4.sc+t4.sd+t4.se+t4.sf 
  			  + t5.s0+t5.s1+t5.s2+t5.s3+t5.s4+t5.s5+t5.s6+t5.s7+t5.s8+t5.s9+t5.sa+t5.sb+t5.sc+t5.sd+t5.se+t5.sf 
  			  + t6.s0+t6.s1+t6.s2+t6.s3+t6.s4+t6.s5+t6.s6+t6.s7+t6.s8+t6.s9+t6.sa+t6.sb+t6.sc+t6.sd+t6.se+t6.sf 
  			  + t7.s0+t7.s1+t7.s2+t7.s3+t7.s4+t7.s5+t7.s6+t7.s7+t7.s8+t7.s9+t7.sa+t7.sb+t7.sc+t7.sd+t7.se+t7.sf;
}

__kernel void kernel_asin_withDD1(__global float* result_asin, int N)
{
  float t1 = 0.0;
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat512(t1 = asin(t1););
  }
  *result_asin = t1;
}

__kernel void kernel_asin_withDD2(__global float* result_asin, int N)
{
  float2 t1 = 0.0+ (float2)(0);
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat64(t1 = asin(t1););
  }
  *result_asin = t1.s0+t1.s1;
}

__kernel void kernel_asin_withDD4(__global float* result_asin, int N)
{
  float4 t1 = 0.0+ (float4)(0);
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat64(t1 = asin(t1););
  }
  *result_asin = t1.s0 + t1.s1 + t1.s2 + t1.s3;
}

__kernel void kernel_asin_withDD8(__global float* result_asin, int N)
{
  float8 t1 = 0.0+ (float8)(0);
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat64(t1 = asin(t1););
  }
  *result_asin = t1.s0 + t1.s1 + t1.s2 + t1.s3 + t1.s4 + t1.s5 + t1.s6 +t1.s7;
}

__kernel void kernel_asin_withDD16(__global float* result_asin, int N)
{
  float16 t1 = 0.0+ (float16)(0);
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat64(t1 = asin(t1););
  }
  *result_asin = t1.s0 + t1.s1 + t1.s2 + t1.s3 + t1.s4 + t1.s5 + t1.s6 +t1.s7+t1.s8+t1.s9+t1.sa+t1.sb+t1.sc+t1.sd+t1.se+t1.sf;
}

__kernel void kernel_asin_withoutDD1(__global float* result_asin, int N)
{
  float  t1 = 1.0;
  float  t2 = 1.1;
  float  t3 = 1.2;
  float  t4 = 1.3;
  float  t5 = 1.4;
  float  t6 = 1.5;
  float  t7 = 1.6;
  float  t8 = 1.6;
  float  t9 = 1.7;
  float  t10 = 1.8;

  float p1 = 0.0;
  for(p1 = 0.0; p1 < 1.0; p1 = p1 + 0.0001) {
    t1 += asin(p1);
    t2 += asin(p1 - 0.00001);
    t3 += asin(p1 - 0.00002);
    t4 += asin(p1 - 0.00003);
    t5 += asin(p1 - 0.00003);
    t6 += asin(p1 - 0.00003);
    t7 += asin(p1 - 0.00003);
    t8 += asin(p1 - 0.00003);
  }
  *result_asin = t1 + t2 + t3 + t4 + t5 + t6 + t7 + t8 + t9 + t10;
}

__kernel void kernel_asin_withoutDD2(__global float* result_asin, int N)
{
  float2  t1 = 1.0+(float2)(0);
  float2  t2 = 1.1+(float2)(0);
  float2  t3 = 1.2+(float2)(0);
  float2  t4 = 1.3+(float2)(0);
  float2  t5 = 1.4+(float2)(0);
  float2  t6 = 1.5+(float2)(0);
  float2  t7 = 1.6+(float2)(0);
  float2  t8 = 1.6+(float2)(0);
  float2  t9 = 1.7+(float2)(0);
  float2  t10 = 1.8+(float2)(0);

  float2 p1 = 0.0+(float2)(0);
  int i;
  for(i=0; i<5000; i++,p1 = p1 + 0.0001){
    t1 += asin(p1);
    t2 += asin(p1 - 0.00001);
    t3 += asin(p1 - 0.00002);
    t4 += asin(p1 - 0.00003);
    t5 += asin(p1 - 0.00003);
    t6 += asin(p1 - 0.00003);
    t7 += asin(p1 - 0.00003);
    t8 += asin(p1 - 0.00003);
  }
  *result_asin = t1.s0+t1.s1 + t2.s0+t2.s1 + t3.s0+t3.s1 + t4.s0+t4.s1 + t5.s0+t5.s1 + t6.s0+t6.s1 + t7.s0+t7.s1 + t8.s0+t8.s1 + t9.s0+t9.s1+ t10.s0+t10.s1;
}

__kernel void kernel_asin_withoutDD4(__global float* result_asin, int N)
{
  float4  t1 = 1.0+(float4)(0);
  float4  t2 = 1.1+(float4)(0);
  float4  t3 = 1.2+(float4)(0);
  float4  t4 = 1.3+(float4)(0);
  float4  t5 = 1.4+(float4)(0);
  float4  t6 = 1.5+(float4)(0);
  float4  t7 = 1.6+(float4)(0);
  float4  t8 = 1.6+(float4)(0);
  float4  t9 = 1.7+(float4)(0);
  float4  t10 = 1.8+(float4)(0);

  float4 p1 = 0.0+(float4)(0);
  int i;
  for(i=0; i<2500; i++, p1 = p1 + 0.0001) {
    t1 += asin(p1);
    t2 += asin(p1 - 0.00001);
    t3 += asin(p1 - 0.00002);
    t4 += asin(p1 - 0.00003);
    t5 += asin(p1 - 0.00003);
    t6 += asin(p1 - 0.00003);
    t7 += asin(p1 - 0.00003);
    t8 += asin(p1 - 0.00003);
  }
  *result_asin =  t1.s0+t1.s1+t1.s2+t1.s3 + t2.s0+t2.s1+t2.s2+t2.s3
		      + t3.s0+t3.s1+t3.s2+t3.s3 + t4.s0+t4.s1+t4.s2+t4.s3
			  + t5.s0+t5.s1+t5.s2+t5.s3 + t6.s0+t6.s1+t6.s2+t6.s3
			  + t7.s0+t7.s1+t7.s2+t7.s3+ t8.s0+t8.s1+t8.s2+t8.s3;
}

__kernel void kernel_asin_withoutDD8(__global float* result_asin, int N)
{
  float8  t1 = 1.0+(float8)(0);
  float8  t2 = 1.1+(float8)(0);
  float8  t3 = 1.2+(float8)(0);
  float8  t4 = 1.3+(float8)(0);
  float8  t5 = 1.4+(float8)(0);
  float8  t6 = 1.5+(float8)(0);
  float8  t7 = 1.6+(float8)(0);
  float8  t8 = 1.6+(float8)(0);
  float8  t9 = 1.7+(float8)(0);
  float8  t10 = 1.8+(float8)(0);

  float8 p1 = 0.0+(float8)(0);
  int i;
  for(i=0; i<500; i++, p1 = p1 + 0.0001) {
    t1 += asin(p1);
    t2 += asin(p1 - 0.00001);
    t3 += asin(p1 - 0.00002);
    t4 += asin(p1 - 0.00003);
    t5 += asin(p1 - 0.00003);
    t6 += asin(p1 - 0.00003);
    t7 += asin(p1 - 0.00003);
    t8 += asin(p1 - 0.00003);
  }
  *result_asin =  t1.s0+t1.s1+t1.s2+t1.s3+t1.s4+t1.s5+t1.s6+t1.s7 + t2.s0+t2.s1+t2.s2+t2.s3+t2.s4+t2.s5+t2.s6+t2.s7 
+ t3.s0+t3.s1+t3.s2+t3.s3+t3.s4+t3.s5+t3.s6+t3.s7 + t4.s0+t4.s1+t4.s2+t4.s3+t4.s4+t4.s5+t4.s6+t4.s7
+ t5.s0+t5.s1+t5.s2+t5.s3+t5.s4+t5.s5+t5.s6+t5.s7 + t6.s0+t6.s1+t6.s2+t6.s3+t6.s4+t6.s5+t6.s6+t6.s7
+ t7.s0+t7.s1+t7.s2+t7.s3+t7.s4+t7.s5+t7.s6+t7.s7 + t8.s0+t8.s1+t8.s2+t8.s3+t8.s4+t8.s5+t8.s6+t8.s7 
+ t9.s0+t9.s1+t9.s2+t9.s3+t9.s4+t9.s5+t9.s6+t9.s7 + t10.s0+t10.s1+t10.s2+t10.s3+t10.s4+t10.s5+t10.s6+t10.s7;
}

__kernel void kernel_asin_withoutDD16(__global float* result_asin, int N)
{
  float16  t1 = 1.0+(float16)(0);
  float16  t2 = 1.1+(float16)(0);
  float16  t3 = 1.2+(float16)(0);
  float16  t4 = 1.3+(float16)(0);
  float16  t5 = 1.4+(float16)(0);
  float16  t6 = 1.5+(float16)(0);
  float16  t7 = 1.6+(float16)(0);
  float16  t8 = 1.6+(float16)(0);
  float16  t9 = 1.7+(float16)(0);
  float16  t10 = 1.8+(float16)(0);

  float16 p1 = 0.0+(float16)(0);
  int i;
  for(i=0; i<200; i++, p1 = p1 + 0.0001) {
    t1 += asin(p1);
    t2 += asin(p1 - 0.00001);
    t3 += asin(p1 - 0.00002);
    t4 += asin(p1 - 0.00003);
    t5 += asin(p1 - 0.00003);
    t6 += asin(p1 - 0.00003);
    t7 += asin(p1 - 0.00003);
    t8 += asin(p1 - 0.00003);
  }
  *result_asin = t1.s0+t1.s1+t1.s2+t1.s3+t1.s4+t1.s5+t1.s6+t1.s7+t1.s8+t1.s9+t1.sa+t1.sb+t1.sc+t1.sd+t1.se+t1.sf
  			  + t2.s0+t2.s1+t2.s2+t2.s3+t2.s4+t2.s5+t2.s6+t2.s7+t2.s8+t2.s9+t2.sa+t2.sb+t2.sc+t2.sd+t2.se+t2.sf
  			  + t3.s0+t3.s1+t3.s2+t3.s3+t3.s4+t3.s5+t3.s6+t3.s7+t3.s8+t3.s9+t3.sa+t3.sb+t3.sc+t3.sd+t3.se+t3.sf
  			  + t4.s0+t4.s1+t4.s2+t4.s3+t4.s4+t4.s5+t4.s6+t4.s7+t4.s8+t4.s9+t4.sa+t4.sb+t4.sc+t4.sd+t4.se+t4.sf 
  			  + t5.s0+t5.s1+t5.s2+t5.s3+t5.s4+t5.s5+t5.s6+t5.s7+t5.s8+t5.s9+t5.sa+t5.sb+t5.sc+t5.sd+t5.se+t5.sf 
  			  + t6.s0+t6.s1+t6.s2+t6.s3+t6.s4+t6.s5+t6.s6+t6.s7+t6.s8+t6.s9+t6.sa+t6.sb+t6.sc+t6.sd+t6.se+t6.sf 
  			  + t7.s0+t7.s1+t7.s2+t7.s3+t7.s4+t7.s5+t7.s6+t7.s7+t7.s8+t7.s9+t7.sa+t7.sb+t7.sc+t7.sd+t7.se+t7.sf 
  			  + t8.s0+t8.s1+t8.s2+t8.s3+t8.s4+t8.s5+t8.s6+t8.s7+t8.s8+t8.s9+t8.sa+t8.sb+t8.sc+t8.sd+t8.se+t8.sf 
  			  + t9.s0+t9.s1+t9.s2+t9.s3+t9.s4+t9.s5+t9.s6+t9.s7+t9.s8+t9.s9+t9.sa+t9.sb+t9.sc+t9.sd+t9.se+t9.sf 
  			  + t10.s0+t10.s1+t10.s2+t10.s3+t10.s4+t10.s5+t10.s6+t10.s7+t10.s8+t10.s9+t10.sa+t10.sb+t10.sc+t10.sd+t10.se+t10.sf ;
}

__kernel void kernel_cos_withDD1(__global float* result_cos, int N)
{
  float t1 = 1.23;
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat64(t1 = cos(t1););
  }
  *result_cos = t1;
}

__kernel void kernel_cos_withDD2(__global float* result_cos, int N)
{
  float2 t1 = 1.23+ (float2)(0);
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat64(t1 = cos(t1););
  }
  *result_cos = t1.s0+t1.s1;
}

__kernel void kernel_cos_withDD4(__global float* result_cos, int N)
{
  float4 t1 = 1.23+ (float4)(0);
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat64(t1 = cos(t1););
  }
  *result_cos =t1.s0 + t1.s1 + t1.s2 + t1.s3;
}

__kernel void kernel_cos_withDD8(__global float* result_cos, int N)
{
  float8 t1 = 1.23+ (float8)(0);
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat64(t1 = cos(t1););
  }
  *result_cos = t1.s0 + t1.s1 + t1.s2 + t1.s3 + t1.s4 + t1.s5 + t1.s6 +t1.s7;
}

__kernel void kernel_cos_withDD16(__global float* result_cos, int N)
{
  float16 t1 = 1.23+(float16)(0);
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat16(t1 = cos(t1););
  }
  *result_cos = t1.s0 + t1.s1 + t1.s2 + t1.s3 + t1.s4 + t1.s5 + t1.s6 +t1.s7+t1.s8+t1.s9+t1.sa+t1.sb+t1.sc+t1.sd+t1.se+t1.sf;
}

__kernel void kernel_cos_withoutDD1(__global float* result_cos, int N)
{
  float  t1 = 1.23;
  float  t2 = 1.23;
  float  t3 = t1;
  float  t4 = t3;
  float  t5 = t4;
  float  t6 = t5;
  float  t7 = t6;
  float j = 0.0;
  for(j = 0.0; j < 10 * N; j = j + 1.0) {
    t1 = cos(j);
    t2 = cos(j);
    t3 = cos(j);
    t4 = cos(j);
    t5 = cos(j);
    t6 = cos(j);
    t7 = cos(j);
  }
  *result_cos = t1 + t2 + t3 + t4 + t5 + t6 + t7;
}

__kernel void kernel_cos_withoutDD2(__global float* result_cos, int N)
{
  float2  t1 = 1.23+(float2)(0);
  float2  t2 = 1.23+(float2)(0);
  float2  t3 = t1;
  float2  t4 = t3;
  float2  t5 = t4;
  float2  t6 = t5;
  float2  t7 = t6;
  float2 p1 =(float2)(0);
  float j = 0.0;
  for(j = 0.0; j < 10 * N; j = j + 1.0,p1=p1+1.0) {
    t1 = cos(p1);
    t2 = cos(p1);
    t3 = cos(p1);
    t4 = cos(p1);
    t5 = cos(p1);
    t6 = cos(p1);
    t7 = cos(p1);
  }
  *result_cos = t1.s0+t1.s1 + t2.s0+t2.s1 + t3.s0+t3.s1 + t4.s0+t4.s1 + t5.s0+t5.s1 + t6.s0+t6.s1 + t7.s0+t7.s1;
}


__kernel void kernel_cos_withoutDD4(__global float* result_cos, int N)
{
  float4  t1 = 1.23+(float4)(0);
  float4  t2 = 1.23+(float4)(0);
  float4  t3 = t1;
  float4  t4 = t3;
  float4  t5 = t4;
  float4  t6 = t5;
  float4  t7 = t6;
  float4 p1 = 0.0+(float4)(0);
  float j = 0.0;
  for(j = 0.0; j < 10 * N; j = j + 1.0,p1 = p1+1.0) {
    t1 = cos(p1);
    t2 = cos(p1);
    t3 = cos(p1);
    t4 = cos(p1);
    t5 = cos(p1);
    t6 = cos(p1);
    t7 = cos(p1);
  }
  *result_cos = t1.s0+t1.s1+t1.s2+t1.s3 + t2.s0+t2.s1+t2.s2+t2.s3
		+ t3.s0+t3.s1+t3.s2+t3.s3 + t4.s0+t4.s1+t4.s2+t4.s3
		+ t5.s0+t5.s1+t5.s2+t5.s3 + t6.s0+t6.s1+t6.s2+t6.s3
		+ t7.s0+t7.s1+t7.s2+t7.s3;
}

__kernel void kernel_cos_withoutDD8(__global float* result_cos, int N)
{
  float8  t1 = 1.23+(float8)(0);
  float8  t2 = 1.23+(float8)(0);
  float8  t3 = t1;
  float8  t4 = t3;
  float8  t5 = t4;
  float8  t6 = t5;
  float8  t7 = t6;
  float8 p1 = 0.0+(float8)(0);
  float j = 0.0;
  for(j = 0.0; j < 10 * N; j = j + 1.0,p1 = p1+1.0) {
    t1 = cos(p1);
    t2 = cos(p1);
    t3 = cos(p1);
    t4 = cos(p1);
    t5 = cos(p1);
    t6 = cos(p1);
    t7 = cos(p1);
  }
  *result_cos = t1.s0+t1.s1+t1.s2+t1.s3+t1.s4+t1.s5+t1.s6+t1.s7 
		+ t2.s0+t2.s1+t2.s2+t2.s3+t2.s4+t2.s5+t2.s6+t2.s7 
		+ t3.s0+t3.s1+t3.s2+t3.s3+t3.s4+t3.s5+t3.s6+t3.s7 
		+ t4.s0+t4.s1+t4.s2+t4.s3+t4.s4+t4.s5+t4.s6+t4.s7
		+ t5.s0+t5.s1+t5.s2+t5.s3+t5.s4+t5.s5+t5.s6+t5.s7
		+ t6.s0+t6.s1+t6.s2+t6.s3+t6.s4+t6.s5+t6.s6+t6.s7
		+ t7.s0+t7.s1+t7.s2+t7.s3+t7.s4+t7.s5+t7.s6+t7.s7;
}

__kernel void kernel_cos_withoutDD16(__global float* result_cos, int N)
{
  float16  t1 = 1.23+(float16)(0);
  float16  t2 = 1.23+(float16)(0);
  float16  t3 = t1;
  float16  t4 = t3;
  float16  t5 = t4;
  float16  t6 = t5;
  float16  t7 = t6;
  float16 p1 = 0.0+(float16)(0);
  float j = 0.0;
  for(j = 0.0; j < 3 * N; j = j + 1.0,p1 = p1+1.0) {
    t1 = cos(p1);
    t2 = cos(p1);
    t3 = cos(p1);
    t4 = cos(p1);
    t5 = cos(p1);
    t6 = cos(p1);
    t7 = cos(p1);
  }
  *result_cos = t1.s0+t1.s1+t1.s2+t1.s3+t1.s4+t1.s5+t1.s6+t1.s7+t1.s8+t1.s9+t1.sa+t1.sb+t1.sc+t1.sd+t1.se+t1.sf
  		+ t2.s0+t2.s1+t2.s2+t2.s3+t2.s4+t2.s5+t2.s6+t2.s7+t2.s8+t2.s9+t2.sa+t2.sb+t2.sc+t2.sd+t2.se+t2.sf
  		+ t3.s0+t3.s1+t3.s2+t3.s3+t3.s4+t3.s5+t3.s6+t3.s7+t3.s8+t3.s9+t3.sa+t3.sb+t3.sc+t3.sd+t3.se+t3.sf
  		+ t4.s0+t4.s1+t4.s2+t4.s3+t4.s4+t4.s5+t4.s6+t4.s7+t4.s8+t4.s9+t4.sa+t4.sb+t4.sc+t4.sd+t4.se+t4.sf 
  		+ t5.s0+t5.s1+t5.s2+t5.s3+t5.s4+t5.s5+t5.s6+t5.s7+t5.s8+t5.s9+t5.sa+t5.sb+t5.sc+t5.sd+t5.se+t5.sf 
  		+ t6.s0+t6.s1+t6.s2+t6.s3+t6.s4+t6.s5+t6.s6+t6.s7+t6.s8+t6.s9+t6.sa+t6.sb+t6.sc+t6.sd+t6.se+t6.sf 
  		+ t7.s0+t7.s1+t7.s2+t7.s3+t7.s4+t7.s5+t7.s6+t7.s7+t7.s8+t7.s9+t7.sa+t7.sb+t7.sc+t7.sd+t7.se+t7.sf; 
}


