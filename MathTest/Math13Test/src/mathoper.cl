/**********************************************************************
Copyright (c) 2014,BUAA COMPILER LAB;
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
- Neither the name of the BUAA COMPILER LAB; nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
********************************************************************/
#define repeat8(S) S S S S S S S S
#define repeat16(S) S S S S S S S S S S S S S S S S
#define repeat32(S) S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S
#define repeat64(S) S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S
#define repeat128(S) S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S
#define repeat256(S) S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S
#define repeat512(S) S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S
#define repeat2048(S) S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S S

__kernel void kernel_log1p_withDD1(__global float* result_log1p, int N)
{
  float t1 = 2.1;
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat32(t1 = log1p(t1););
  }
  *result_log1p = t1;
}

__kernel void kernel_log1p_withDD2(__global float* result_log1p, int N)
{
  float2 t1 = 2.1+(float2)(0);
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat32(t1 = log1p(t1););
  }
  *result_log1p = t1.s0 + t1.s1;
}

__kernel void kernel_log1p_withDD4(__global float* result_log1p, int N)
{
  float4 t1 = 2.1+(float4)(0);
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat32(t1 = log1p(t1););
  }
  *result_log1p = t1.s0 + t1.s1 + t1.s2 + t1.s3;
}

__kernel void kernel_log1p_withDD8(__global float* result_log1p, int N)
{
  float8 t1 = 2.1+(float8)(0);
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat32(t1 = log1p(t1););
  }
  *result_log1p = t1.s0 + t1.s1 + t1.s2 + t1.s3 + t1.s4 + t1.s5 + t1.s6 +t1.s7;
}

__kernel void kernel_log1p_withDD16(__global float* result_log1p, int N)
{
  float16 t1 = 2.1+(float16)(0);
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat32(t1 = log1p(t1););
  }
  *result_log1p = t1.s0 + t1.s1 + t1.s2 + t1.s3 + t1.s4 + t1.s5 + t1.s6 +t1.s7+t1.s8+t1.s9+t1.sa+t1.sb+t1.sc+t1.sd+t1.se+t1.sf;
}

__kernel void kernel_log1p_withoutDD1(__global float* result_log1p, int N)
{
  float t1;
  float t2;
  float t3;
  float t4;
  float t5;
  float t6;
  float t7;

  float i = 0.0;
  float n = 100 * N;
  for(i = 0.0; i < n; i = i + 1.0) {
    t1 = log1p(i);
    t2 = log1p(i);
    t3 = log1p(i);
    t4 = log1p(i);
    t5 = log1p(i);
    t6 = log1p(i);
    t7 = log1p(i);

  }
  *result_log1p = t1 + t2 + t3 + t4 + t5 + t6 + t7;
}

__kernel void kernel_log1p_withoutDD2(__global float* result_log1p, int N)
{
  float2 t1;
  float2 t2;
  float2 t3;
  float2 t4;
  float2 t5;
  float2 t6;
  float2 t7;

  float2 i = 0.0+(float2)(0); 
  float n = 100 * N;
  for(i.s0 = 0.0; i.s0 < n; i = i + 1.0) {
    t1 = log1p(i);
    t2 = log1p(i);
    t3 = log1p(i);
    t4 = log1p(i);
    t5 = log1p(i);
    t6 = log1p(i);
    t7 = log1p(i);

  }
  *result_log1p =t1.s0+t1.s1 + t2.s0+t2.s1 + t3.s0+t3.s1 + t4.s0+t4.s1 + t5.s0+t5.s1 + t6.s0+t6.s1 + t7.s0+t7.s1;
}


__kernel void kernel_log1p_withoutDD4(__global float* result_log1p, int N)
{
  float4 t1;
  float4 t2;
  float4 t3;
  float4 t4;
  float4 t5;
  float4 t6;
  float4 t7;

  float4 i = 0.0+(float4)(0); 
  float n = 100 * N;
  for(i.s0 = 0.0; i.s0 < n; i = i + 1.0) {
    t1 = log1p(i);
    t2 = log1p(i);
    t3 = log1p(i);
    t4 = log1p(i);
    t5 = log1p(i);
    t6 = log1p(i);
    t7 = log1p(i);

  }
  *result_log1p =t1.s0+t1.s1+t1.s2+t1.s3 + t2.s0+t2.s1+t2.s2+t2.s3
	    	+ t3.s0+t3.s1+t3.s2+t3.s3 + t4.s0+t4.s1+t4.s2+t4.s3
		+ t5.s0+t5.s1+t5.s2+t5.s3 + t6.s0+t6.s1+t6.s2+t6.s3
		+ t7.s0+t7.s1+t7.s2+t7.s3;
}

__kernel void kernel_log1p_withoutDD8(__global float* result_log1p, int N)
{
  float8 t1;
  float8 t2;
  float8 t3;
  float8 t4;
  float8 t5;
  float8 t6;
  float8 t7;

  float8 i = 0.0+(float8)(0); 
  float n = 100 * N;
  for(i.s0 = 0.0; i.s0 < n; i = i + 1.0) {
    t1 = log1p(i);
    t2 = log1p(i);
    t3 = log1p(i);
    t4 = log1p(i);
    t5 = log1p(i);
    t6 = log1p(i);
    t7 = log1p(i);

  }
  *result_log1p =t1.s0+t1.s1+t1.s2+t1.s3+t1.s4+t1.s5+t1.s6+t1.s7
  		+ t2.s0+t2.s1+t2.s2+t2.s3+t2.s4+t2.s5+t2.s6+t2.s7
  		+ t3.s0+t3.s1+t3.s2+t3.s3+t3.s4+t3.s5+t3.s6+t3.s7 
  		+ t4.s0+t4.s1+t4.s2+t4.s3+t4.s4+t4.s5+t4.s6+t4.s7 
  		+ t5.s0+t5.s1+t5.s2+t5.s3+t5.s4+t5.s5+t5.s6+t5.s7 
  		+ t6.s0+t6.s1+t6.s2+t6.s3+t6.s4+t6.s5+t6.s6+t6.s7 
  		+ t7.s0+t7.s1+t7.s2+t7.s3+t7.s4+t7.s5+t7.s6+t7.s7;
}

__kernel void kernel_log1p_withoutDD16(__global float* result_log1p, int N)
{
  float16 t1;
  float16 t2;
  float16 t3;
  float16 t4;
  float16 t5;
  float16 t6;
  float16 t7;

  float16 i = 0.0+(float16)(0); 
  float n = 40 * N;
  for(i.s0 = 0.0; i.s0 < n; i = i + 1.0) {
    t1 = log1p(i);
    t2 = log1p(i);
    t3 = log1p(i);
    t4 = log1p(i);
    t5 = log1p(i);
    t6 = log1p(i);
    t7 = log1p(i);

  }
  *result_log1p =t1.s0+t1.s1+t1.s2+t1.s3+t1.s4+t1.s5+t1.s6+t1.s7+t1.s8+t1.s9+t1.sa+t1.sb+t1.sc+t1.sd+t1.se+t1.sf
  		+ t2.s0+t2.s1+t2.s2+t2.s3+t2.s4+t2.s5+t2.s6+t2.s7+t2.s8+t2.s9+t2.sa+t2.sb+t2.sc+t2.sd+t2.se+t2.sf
  		+ t3.s0+t3.s1+t3.s2+t3.s3+t3.s4+t3.s5+t3.s6+t3.s7+t3.s8+t3.s9+t3.sa+t3.sb+t3.sc+t3.sd+t3.se+t3.sf
  		+ t4.s0+t4.s1+t4.s2+t4.s3+t4.s4+t4.s5+t4.s6+t4.s7+t4.s8+t4.s9+t4.sa+t4.sb+t4.sc+t4.sd+t4.se+t4.sf 
  		+ t5.s0+t5.s1+t5.s2+t5.s3+t5.s4+t5.s5+t5.s6+t5.s7+t5.s8+t5.s9+t5.sa+t5.sb+t5.sc+t5.sd+t5.se+t5.sf 
  		+ t6.s0+t6.s1+t6.s2+t6.s3+t6.s4+t6.s5+t6.s6+t6.s7+t6.s8+t6.s9+t6.sa+t6.sb+t6.sc+t6.sd+t6.se+t6.sf 
  		+ t7.s0+t7.s1+t7.s2+t7.s3+t7.s4+t7.s5+t7.s6+t7.s7+t7.s8+t7.s9+t7.sa+t7.sb+t7.sc+t7.sd+t7.se+t7.sf;
}

__kernel void kernel_logb_withDD1(__global float* result_logb, int N)
{
  float t1 = 10.0;

  int i = 0;
  for(i = 0; i < N; i++) {
    repeat64(t1 = 4.0 + logb(t1););
  }
  *result_logb = t1;
}

__kernel void kernel_logb_withDD2(__global float* result_logb, int N)
{
  float2 t1 = 10.0+(float2)(0); 

  int i = 0;
  for(i = 0; i < N; i++) {
    repeat64(t1 = 4.0 + logb(t1););
  }
  *result_logb = t1.s0 + t1.s1;
}

__kernel void kernel_logb_withDD4(__global float* result_logb, int N)
{
  float4 t1 = 10.0+(float4)(0);  

  int i = 0;
  for(i = 0; i < N; i++) {
    repeat64(t1 = 4.0 + logb(t1););
  }
  *result_logb = t1.s0 + t1.s1 + t1.s2 + t1.s3;
}

__kernel void kernel_logb_withDD8(__global float* result_logb, int N)
{
  float8 t1 = 10.0+(float8)(0);  

  int i = 0;
  for(i = 0; i < N; i++) {
    repeat64(t1 = 4.0 + logb(t1););
  }
  *result_logb = t1.s0 + t1.s1 + t1.s2 + t1.s3 + t1.s4 + t1.s5 + t1.s6 +t1.s7;
}

__kernel void kernel_logb_withDD16(__global float* result_logb, int N)
{
  float16 t1 = 10.0+(float16)(0);  

  int i = 0;
  for(i = 0; i < N; i++) {
    repeat64(t1 = 4.0 + logb(t1););
  }
  *result_logb = t1.s0 + t1.s1 + t1.s2 + t1.s3 + t1.s4 + t1.s5 + t1.s6 +t1.s7
		+t1.s8+t1.s9+t1.sa+t1.sb+t1.sc+t1.sd+t1.se+t1.sf;
}

__kernel void kernel_logb_withoutDD1(__global float* result_logb, int N)
{
  float t1;
  float t2;
  float t3;
  float t4;
  float t5;
  float t6;
  float t7;
  float t8;
  float t9;
  float t10;

  float i = 0.0;
  float n = 30.0 * (float)(N);

  for(i = 0.0; i < n; i = i + 1.0) {
    t1 = logb(i);
    t2 = logb(i);
    t3 = logb(i);
    t4 = logb(i);
    t5 = logb(i);
    t6 = logb(i);
    t7 = logb(i);
    t8 = logb(i);
    t9 = logb(i);
    t10 = logb(i);
  }
  *result_logb = t1 + t2 + t3 + t4 + t5 + t6 + t7 + t8 + t9 + t10;
}

__kernel void kernel_logb_withoutDD2(__global float* result_logb, int N)
{
  float2 t1;
  float2 t2;
  float2 t3;
  float2 t4;
  float2 t5;
  float2 t6;
  float2 t7;
  float2 t8;
  float2 t9;
  float2 t10;

  float2 i = 0.0+(float2)(0); 
  float n = 30.0 * (float)(N);

  for(i.s0 = 0.0; i.s0 < n; i = i + 1.0) {
    t1 = logb(i);
    t2 = logb(i);
    t3 = logb(i);
    t4 = logb(i);
    t5 = logb(i);
    t6 = logb(i);
    t7 = logb(i);
    t8 = logb(i);
    t9 = logb(i);
    t10 = logb(i);
  }
  *result_logb =  t1.s0+t1.s1 + t2.s0+t2.s1 + t3.s0+t3.s1 + t4.s0+t4.s1 + t5.s0+t5.s1 + t6.s0+t6.s1 + t7.s0+t7.s1
		     + t8.s0+t8.s1 + t9.s0+t9.s1+ t10.s0+t10.s1;
}


__kernel void kernel_logb_withoutDD4(__global float* result_logb, int N)
{
  float4 t1;
  float4 t2;
  float4 t3;
  float4 t4;
  float4 t5;
  float4 t6;
  float4 t7;
  float4 t8;
  float4 t9;
  float4 t10;

  float4 i = 0.0+(float4)(0); 
  float n = 30.0 * (float)(N);

  for(i.s0 = 0.0; i.s0 < n; i = i + 1.0) {
    t1 = logb(i);
    t2 = logb(i);
    t3 = logb(i);
    t4 = logb(i);
    t5 = logb(i);
    t6 = logb(i);
    t7 = logb(i);
    t8 = logb(i);
    t9 = logb(i);
    t10 = logb(i);
  }
  *result_logb = t1.s0+t1.s1+t1.s2+t1.s3 + t2.s0+t2.s1+t2.s2+t2.s3
	    	+ t3.s0+t3.s1+t3.s2+t3.s3 + t4.s0+t4.s1+t4.s2+t4.s3
		+ t5.s0+t5.s1+t5.s2+t5.s3 + t6.s0+t6.s1+t6.s2+t6.s3
		+ t7.s0+t7.s1+t7.s2+t7.s3 + t8.s0+t8.s1+t8.s2+t8.s3
		+ t9.s0+t9.s1+t9.s2+t9.s3 + t10.s0+t10.s1+t10.s2+t10.s3;
}

__kernel void kernel_logb_withoutDD8(__global float* result_logb, int N)
{
  float8 t1;
  float8 t2;
  float8 t3;
  float8 t4;
  float8 t5;
  float8 t6;
  float8 t7;
  float8 t8;
  float8 t9;
  float8 t10;

  float8 i = 0.0+(float8)(0); 
  float n = 30.0 * (float)(N);

  for(i.s0 = 0.0; i.s0 < n; i = i + 1.0) {
    t1 = logb(i);
    t2 = logb(i);
    t3 = logb(i);
    t4 = logb(i);
    t5 = logb(i);
    t6 = logb(i);
    t7 = logb(i);
    t8 = logb(i);
    t9 = logb(i);
    t10 = logb(i);
  }
  *result_logb = t1.s0+t1.s1+t1.s2+t1.s3+t1.s4+t1.s5+t1.s6+t1.s7
  		+ t2.s0+t2.s1+t2.s2+t2.s3+t2.s4+t2.s5+t2.s6+t2.s7
  		+ t3.s0+t3.s1+t3.s2+t3.s3+t3.s4+t3.s5+t3.s6+t3.s7 
  		+ t4.s0+t4.s1+t4.s2+t4.s3+t4.s4+t4.s5+t4.s6+t4.s7 
  		+ t5.s0+t5.s1+t5.s2+t5.s3+t5.s4+t5.s5+t5.s6+t5.s7 
  		+ t6.s0+t6.s1+t6.s2+t6.s3+t6.s4+t6.s5+t6.s6+t6.s7 
  		+ t7.s0+t7.s1+t7.s2+t7.s3+t7.s4+t7.s5+t7.s6+t7.s7 
  		+ t8.s0+t8.s1+t8.s2+t8.s3+t8.s4+t8.s5+t8.s6+t8.s7 
  		+ t9.s0+t9.s1+t9.s2+t9.s3+t9.s4+t9.s5+t9.s6+t9.s7 
  		+ t10.s0+t10.s1+t10.s2+t10.s3+t10.s4+t10.s5+t10.s6+t10.s7;
}

__kernel void kernel_logb_withoutDD16(__global float* result_logb, int N)
{
  float16 t1;
  float16 t2;
  float16 t3;
  float16 t4;
  float16 t5;
  float16 t6;
  float16 t7;
  float16 t8;
  float16 t9;
  float16 t10;

  float16 i = 0.0+(float16)(0); 
  float n = 30.0 * (float)(N);

  for(i.s0 = 0.0; i.s0 < n; i = i + 1.0) {
    t1 = logb(i);
    t2 = logb(i);
    t3 = logb(i);
    t4 = logb(i);
    t5 = logb(i);
    t6 = logb(i);
    t7 = logb(i);
    t8 = logb(i);
    t9 = logb(i);
    t10 = logb(i);
  }
  *result_logb =t1.s0+t1.s1+t1.s2+t1.s3+t1.s4+t1.s5+t1.s6+t1.s7+t1.s8+t1.s9+t1.sa+t1.sb+t1.sc+t1.sd+t1.se+t1.sf
  		+ t2.s0+t2.s1+t2.s2+t2.s3+t2.s4+t2.s5+t2.s6+t2.s7+t2.s8+t2.s9+t2.sa+t2.sb+t2.sc+t2.sd+t2.se+t2.sf
  		+ t3.s0+t3.s1+t3.s2+t3.s3+t3.s4+t3.s5+t3.s6+t3.s7+t3.s8+t3.s9+t3.sa+t3.sb+t3.sc+t3.sd+t3.se+t3.sf
  		+ t4.s0+t4.s1+t4.s2+t4.s3+t4.s4+t4.s5+t4.s6+t4.s7+t4.s8+t4.s9+t4.sa+t4.sb+t4.sc+t4.sd+t4.se+t4.sf 
  		+ t5.s0+t5.s1+t5.s2+t5.s3+t5.s4+t5.s5+t5.s6+t5.s7+t5.s8+t5.s9+t5.sa+t5.sb+t5.sc+t5.sd+t5.se+t5.sf 
  		+ t6.s0+t6.s1+t6.s2+t6.s3+t6.s4+t6.s5+t6.s6+t6.s7+t6.s8+t6.s9+t6.sa+t6.sb+t6.sc+t6.sd+t6.se+t6.sf 
  		+ t7.s0+t7.s1+t7.s2+t7.s3+t7.s4+t7.s5+t7.s6+t7.s7+t7.s8+t7.s9+t7.sa+t7.sb+t7.sc+t7.sd+t7.se+t7.sf 
  		+ t8.s0+t8.s1+t8.s2+t8.s3+t8.s4+t8.s5+t8.s6+t8.s7+t8.s8+t8.s9+t8.sa+t8.sb+t8.sc+t8.sd+t8.se+t8.sf 
  		+ t9.s0+t9.s1+t9.s2+t9.s3+t9.s4+t9.s5+t9.s6+t9.s7+t9.s8+t9.s9+t9.sa+t9.sb+t9.sc+t9.sd+t9.se+t9.sf 
  		+ t10.s0+t10.s1+t10.s2+t10.s3+t10.s4+t10.s5+t10.s6+t10.s7+t10.s8+t10.s9+t10.sa+t10.sb+t10.sc+t10.sd+t10.se+t10.sf;
}

__kernel void kernel_modf_withDD1(__global float* result_modf, int N)
{
  float t1 = 1.2;
  float t2;
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat128(t1 = modf(t1, &t2););
  }
  *result_modf = t1;
}

__kernel void kernel_modf_withDD2(__global float* result_modf, int N)
{
  float2 t1 = 1.2+(float2)(0);
  float2 t2;
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat128(t1 = modf(t1, &t2););
  }
  *result_modf = t1.s0 + t1.s1;
}

__kernel void kernel_modf_withDD4(__global float* result_modf, int N)
{
  float4 t1 = 1.2+(float4)(0);
  float4 t2;
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat128(t1 = modf(t1, &t2););
  }
  *result_modf = t1.s0 + t1.s1 + t1.s2 + t1.s3;
}

__kernel void kernel_modf_withDD8(__global float* result_modf, int N)
{
  float8 t1 = 1.2+(float8)(0);
  float8 t2;
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat128(t1 = modf(t1, &t2););
  }
  *result_modf = t1.s0 + t1.s1 + t1.s2 + t1.s3 + t1.s4 + t1.s5 + t1.s6 +t1.s7;
}

__kernel void kernel_modf_withDD16(__global float* result_modf, int N)
{
  float16 t1 = 1.2+(float16)(0);
  float16 t2;
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat128(t1 = modf(t1, &t2););
  }
  *result_modf = t1.s0 + t1.s1 + t1.s2 + t1.s3 + t1.s4 + t1.s5 + t1.s6 
		+t1.s7+t1.s8+t1.s9+t1.sa+t1.sb+t1.sc+t1.sd+t1.se+t1.sf;
}

__kernel void kernel_modf_withoutDD1(__global float* result_modf, int N)
{
  float t1;
  float t2;
  float t3;
  float t4;
  float t5;
  float t6;
  float t7;
  float t8;
  float t9;
  float t10;

  float i = 0.0;
  float j;
  float n = 0.3 * (float)(N);

  for(i = 0.0; i < n; i = i + 0.01) {
    t1 = modf(i, &j);
    t2 = modf(i, &j);
    t3 = modf(i, &j);
    t4 = modf(i, &j);
    t5 = modf(i, &j);
    t6 = modf(i, &j);
    t7 = modf(i, &j);
    t8 = modf(i, &j);
    t9 = modf(i, &j);
    t10 = modf(i, &j);
  }
  *result_modf = t1 + t2 + t3 + t4 + t5 + t6 + t7 + t8 + t9 + t10;
}

__kernel void kernel_modf_withoutDD2(__global float* result_modf, int N)
{
  float2 t1;
  float2 t2;
  float2 t3;
  float2 t4;
  float2 t5;
  float2 t6;
  float2 t7;
  float2 t8;
  float2 t9;
  float2 t10;

  float2 i = 0.0+(float2)(0);
  float2 j;
  float n = 0.3 * (float)(N);

  for(i.s0 = 0.0; i.s0 < n; i = i + 0.01) {
    t1 = modf(i, &j);
    t2 = modf(i, &j);
    t3 = modf(i, &j);
    t4 = modf(i, &j);
    t5 = modf(i, &j);
    t6 = modf(i, &j);
    t7 = modf(i, &j);
    t8 = modf(i, &j);
    t9 = modf(i, &j);
    t10 = modf(i, &j);
  }
  *result_modf = t1.s0+t1.s1 + t2.s0+t2.s1 + t3.s0+t3.s1 + t4.s0+t4.s1 + t5.s0+t5.s1 + t6.s0+t6.s1 + t7.s0+t7.s1
		     + t8.s0+t8.s1 + t9.s0+t9.s1+ t10.s0+t10.s1;
}

__kernel void kernel_modf_withoutDD4(__global float* result_modf, int N)
{
  float4 t1;
  float4 t2;
  float4 t3;
  float4 t4;
  float4 t5;
  float4 t6;
  float4 t7;
  float4 t8;
  float4 t9;
  float4 t10;

  float4 i = 0.0+(float4)(0);
  float4 j;
  float n = 0.3 * (float)(N);

  for(i.s0 = 0.0; i.s0 < n; i = i + 0.01) {
    t1 = modf(i, &j);
    t2 = modf(i, &j);
    t3 = modf(i, &j);
    t4 = modf(i, &j);
    t5 = modf(i, &j);
    t6 = modf(i, &j);
    t7 = modf(i, &j);
    t8 = modf(i, &j);
    t9 = modf(i, &j);
    t10 = modf(i, &j);
  }
  *result_modf = t1.s0+t1.s1+t1.s2+t1.s3 + t2.s0+t2.s1+t2.s2+t2.s3
	    	+ t3.s0+t3.s1+t3.s2+t3.s3 + t4.s0+t4.s1+t4.s2+t4.s3
		+ t5.s0+t5.s1+t5.s2+t5.s3 + t6.s0+t6.s1+t6.s2+t6.s3
		+ t7.s0+t7.s1+t7.s2+t7.s3 + t8.s0+t8.s1+t8.s2+t8.s3
		+ t9.s0+t9.s1+t9.s2+t9.s3 + t10.s0+t10.s1+t10.s2+t10.s3;
}

__kernel void kernel_modf_withoutDD8(__global float* result_modf, int N)
{
  float8 t1;
  float8 t2;
  float8 t3;
  float8 t4;
  float8 t5;
  float8 t6;
  float8 t7;
  float8 t8;
  float8 t9;
  float8 t10;

  float8 i = 0.0+(float8)(0);
  float8 j;
  float n = 0.3 * (float)(N);

  for(i.s0 = 0.0; i.s0 < n; i = i + 0.01) {
    t1 = modf(i, &j);
    t2 = modf(i, &j);
    t3 = modf(i, &j);
    t4 = modf(i, &j);
    t5 = modf(i, &j);
    t6 = modf(i, &j);
    t7 = modf(i, &j);
    t8 = modf(i, &j);
    t9 = modf(i, &j);
    t10 = modf(i, &j);
  }
  *result_modf =t1.s0+t1.s1+t1.s2+t1.s3+t1.s4+t1.s5+t1.s6+t1.s7
  		+ t2.s0+t2.s1+t2.s2+t2.s3+t2.s4+t2.s5+t2.s6+t2.s7
  		+ t3.s0+t3.s1+t3.s2+t3.s3+t3.s4+t3.s5+t3.s6+t3.s7 
  		+ t4.s0+t4.s1+t4.s2+t4.s3+t4.s4+t4.s5+t4.s6+t4.s7 
  		+ t5.s0+t5.s1+t5.s2+t5.s3+t5.s4+t5.s5+t5.s6+t5.s7 
  		+ t6.s0+t6.s1+t6.s2+t6.s3+t6.s4+t6.s5+t6.s6+t6.s7 
  		+ t7.s0+t7.s1+t7.s2+t7.s3+t7.s4+t7.s5+t7.s6+t7.s7 
  		+ t8.s0+t8.s1+t8.s2+t8.s3+t8.s4+t8.s5+t8.s6+t8.s7 
  		+ t9.s0+t9.s1+t9.s2+t9.s3+t9.s4+t9.s5+t9.s6+t9.s7 
  		+ t10.s0+t10.s1+t10.s2+t10.s3+t10.s4+t10.s5+t10.s6+t10.s7;
}

__kernel void kernel_modf_withoutDD16(__global float* result_modf, int N)
{
  float16 t1;
  float16 t2;
  float16 t3;
  float16 t4;
  float16 t5;
  float16 t6;
  float16 t7;
  float16 t8;
  float16 t9;
  float16 t10;

  float16 i = 0.0+(float16)(0);
  float16 j;
  float n = 0.3 * (float)(N);

  for(i.s0 = 0.0; i.s0 < n; i = i + 0.01) {
    t1 = modf(i, &j);
    t2 = modf(i, &j);
    t3 = modf(i, &j);
    t4 = modf(i, &j);
    t5 = modf(i, &j);
    t6 = modf(i, &j);
    t7 = modf(i, &j);
    t8 = modf(i, &j);
    t9 = modf(i, &j);
    t10 = modf(i, &j);
  }
  *result_modf =t1.s0+t1.s1+t1.s2+t1.s3+t1.s4+t1.s5+t1.s6+t1.s7+t1.s8+t1.s9+t1.sa+t1.sb+t1.sc+t1.sd+t1.se+t1.sf
  		+ t2.s0+t2.s1+t2.s2+t2.s3+t2.s4+t2.s5+t2.s6+t2.s7+t2.s8+t2.s9+t2.sa+t2.sb+t2.sc+t2.sd+t2.se+t2.sf
  		+ t3.s0+t3.s1+t3.s2+t3.s3+t3.s4+t3.s5+t3.s6+t3.s7+t3.s8+t3.s9+t3.sa+t3.sb+t3.sc+t3.sd+t3.se+t3.sf
  		+ t4.s0+t4.s1+t4.s2+t4.s3+t4.s4+t4.s5+t4.s6+t4.s7+t4.s8+t4.s9+t4.sa+t4.sb+t4.sc+t4.sd+t4.se+t4.sf 
  		+ t5.s0+t5.s1+t5.s2+t5.s3+t5.s4+t5.s5+t5.s6+t5.s7+t5.s8+t5.s9+t5.sa+t5.sb+t5.sc+t5.sd+t5.se+t5.sf 
  		+ t6.s0+t6.s1+t6.s2+t6.s3+t6.s4+t6.s5+t6.s6+t6.s7+t6.s8+t6.s9+t6.sa+t6.sb+t6.sc+t6.sd+t6.se+t6.sf 
  		+ t7.s0+t7.s1+t7.s2+t7.s3+t7.s4+t7.s5+t7.s6+t7.s7+t7.s8+t7.s9+t7.sa+t7.sb+t7.sc+t7.sd+t7.se+t7.sf 
  		+ t8.s0+t8.s1+t8.s2+t8.s3+t8.s4+t8.s5+t8.s6+t8.s7+t8.s8+t8.s9+t8.sa+t8.sb+t8.sc+t8.sd+t8.se+t8.sf 
  		+ t9.s0+t9.s1+t9.s2+t9.s3+t9.s4+t9.s5+t9.s6+t9.s7+t9.s8+t9.s9+t9.sa+t9.sb+t9.sc+t9.sd+t9.se+t9.sf 
  		+ t10.s0+t10.s1+t10.s2+t10.s3+t10.s4+t10.s5+t10.s6+t10.s7+t10.s8+t10.s9+t10.sa+t10.sb+t10.sc+t10.sd+t10.se+t10.sf;
}

__kernel void kernel_lgamma_withDD1(__global float* result_lgamma, int N)
{
  float t1 = 0.2;

  int i = 0;
  for(i = 0; i < N; i++) {
    repeat32(t1 = lgamma(t1) - 1.3;);
  }

  *result_lgamma = t1;
}

__kernel void kernel_lgamma_withDD2(__global float* result_lgamma, int N)
{
  float2 t1 = 0.2+(float2)(0);

  int i = 0;
  for(i = 0; i < N; i++) {
    repeat32(t1 = lgamma(t1) - 1.3;);
  }

  *result_lgamma = t1.s0 + t1.s1;
}

__kernel void kernel_lgamma_withDD4(__global float* result_lgamma, int N)
{
  float4 t1 = 0.2+(float4)(0);

  int i = 0;
  for(i = 0; i < N; i++) {
    repeat32(t1 = lgamma(t1) - 1.3;);
  }

  *result_lgamma = t1.s0 + t1.s1 + t1.s2 + t1.s3;
}

__kernel void kernel_lgamma_withDD8(__global float* result_lgamma, int N)
{
  float8 t1 = 0.2+(float8)(0);

  int i = 0;
  for(i = 0; i < N; i++) {
    repeat32(t1 = lgamma(t1) - 1.3;);
  }

  *result_lgamma = t1.s0 + t1.s1 + t1.s2 + t1.s3 + t1.s4 + t1.s5 + t1.s6 +t1.s7;
}

__kernel void kernel_lgamma_withDD16(__global float* result_lgamma, int N)
{
  float16 t1 = 0.2+(float16)(0);

  int i = 0;
  for(i = 0; i < N; i++) {
    repeat32(t1 = lgamma(t1) - 1.3;);
  }

  *result_lgamma = t1.s0 + t1.s1 + t1.s2 + t1.s3 + t1.s4 + t1.s5 + t1.s6 
		  +t1.s7+t1.s8+t1.s9+t1.sa+t1.sb+t1.sc+t1.sd+t1.se+t1.sf;
}

__kernel void kernel_lgamma_withoutDD1(__global float* result_lgamma, int N)
{
  float t1;
  float t2;
  float t3;
  float t4;
  float t5;
  float t6;
  float t7;
  float t8;
  float t9;
  float t10;

  float i = 0.0;

  for(i = 0.0; i < 1.0; i = i + 0.1) {
    t1 = lgamma(i);
    t2 = lgamma(i + 0.01);
    t3 = lgamma(i + 0.02);
    t4 = lgamma(i + 0.03);
    t5 = lgamma(i + 0.04);
    t6 = lgamma(i + 0.05);
    t7 = lgamma(i + 0.06);
    t8 = lgamma(i + 0.07);
    t9 = lgamma(i + 0.08);
    t10 = lgamma(i + 0.09);
  }
  *result_lgamma = t1 + t2 + t3 + t4 + t5 + t6 + t7 + t8 + t9 + t10;
}

__kernel void kernel_lgamma_withoutDD2(__global float* result_lgamma, int N)
{
  float2 t1;
  float2 t2;
  float2 t3;
  float2 t4;
  float2 t5;
  float2 t6;
  float2 t7;
  float2 t8;
  float2 t9;
  float2 t10;

  float2 i = 0.0+(float2)(0);

  for(i.s0 = 0.0; i.s0 < 1.0; i = i + 0.1) {
    t1 = lgamma(i);
    t2 = lgamma(i + 0.01);
    t3 = lgamma(i + 0.02);
    t4 = lgamma(i + 0.03);
    t5 = lgamma(i + 0.04);
    t6 = lgamma(i + 0.05);
    t7 = lgamma(i + 0.06);
    t8 = lgamma(i + 0.07);
    t9 = lgamma(i + 0.08);
    t10 = lgamma(i + 0.09);
  }
  *result_lgamma = t1.s0+t1.s1 + t2.s0+t2.s1 + t3.s0+t3.s1 + t4.s0+t4.s1 + t5.s0+t5.s1 + t6.s0+t6.s1 + t7.s0+t7.s1
		     + t8.s0+t8.s1 + t9.s0+t9.s1+ t10.s0+t10.s1;
}

__kernel void kernel_lgamma_withoutDD4(__global float* result_lgamma, int N)
{
  float4 t1;
  float4 t2;
  float4 t3;
  float4 t4;
  float4 t5;
  float4 t6;
  float4 t7;
  float4 t8;
  float4 t9;
  float4 t10;

  float4 i = 0.0+(float4)(0);

  for(i.s0 = 0.0; i.s0 < 1.0; i = i + 0.1) {
    t1 = lgamma(i);
    t2 = lgamma(i + 0.01);
    t3 = lgamma(i + 0.02);
    t4 = lgamma(i + 0.03);
    t5 = lgamma(i + 0.04);
    t6 = lgamma(i + 0.05);
    t7 = lgamma(i + 0.06);
    t8 = lgamma(i + 0.07);
    t9 = lgamma(i + 0.08);
    t10 = lgamma(i + 0.09);
  }
  *result_lgamma = t1.s0+t1.s1+t1.s2+t1.s3 + t2.s0+t2.s1+t2.s2+t2.s3
	    	+ t3.s0+t3.s1+t3.s2+t3.s3 + t4.s0+t4.s1+t4.s2+t4.s3
		+ t5.s0+t5.s1+t5.s2+t5.s3 + t6.s0+t6.s1+t6.s2+t6.s3
		+ t7.s0+t7.s1+t7.s2+t7.s3 + t8.s0+t8.s1+t8.s2+t8.s3
		+ t9.s0+t9.s1+t9.s2+t9.s3 + t10.s0+t10.s1+t10.s2+t10.s3;
}

__kernel void kernel_lgamma_withoutDD8(__global float* result_lgamma, int N)
{
  float8 t1;
  float8 t2;
  float8 t3;
  float8 t4;
  float8 t5;
  float8 t6;
  float8 t7;
  float8 t8;
  float8 t9;
  float8 t10;

  float8 i = 0.0+(float8)(0);

  for(i.s0 = 0.0; i.s0 < 1.0; i = i + 0.1) {
    t1 = lgamma(i);
    t2 = lgamma(i + 0.01);
    t3 = lgamma(i + 0.02);
    t4 = lgamma(i + 0.03);
    t5 = lgamma(i + 0.04);
    t6 = lgamma(i + 0.05);
    t7 = lgamma(i + 0.06);
    t8 = lgamma(i + 0.07);
    t9 = lgamma(i + 0.08);
    t10 = lgamma(i + 0.09);
  }
  *result_lgamma = t1.s0+t1.s1+t1.s2+t1.s3+t1.s4+t1.s5+t1.s6+t1.s7
  		+ t2.s0+t2.s1+t2.s2+t2.s3+t2.s4+t2.s5+t2.s6+t2.s7
  		+ t3.s0+t3.s1+t3.s2+t3.s3+t3.s4+t3.s5+t3.s6+t3.s7 
  		+ t4.s0+t4.s1+t4.s2+t4.s3+t4.s4+t4.s5+t4.s6+t4.s7 
  		+ t5.s0+t5.s1+t5.s2+t5.s3+t5.s4+t5.s5+t5.s6+t5.s7 
  		+ t6.s0+t6.s1+t6.s2+t6.s3+t6.s4+t6.s5+t6.s6+t6.s7 
  		+ t7.s0+t7.s1+t7.s2+t7.s3+t7.s4+t7.s5+t7.s6+t7.s7 
  		+ t8.s0+t8.s1+t8.s2+t8.s3+t8.s4+t8.s5+t8.s6+t8.s7 
  		+ t9.s0+t9.s1+t9.s2+t9.s3+t9.s4+t9.s5+t9.s6+t9.s7 
  		+ t10.s0+t10.s1+t10.s2+t10.s3+t10.s4+t10.s5+t10.s6+t10.s7;
}

__kernel void kernel_lgamma_withoutDD16(__global float* result_lgamma, int N)
{
  float16 t1;
  float16 t2;
  float16 t3;
  float16 t4;
  float16 t5;
  float16 t6;
  float16 t7;
  float16 t8;
  float16 t9;
  float16 t10;

  float16 i = 0.0+(float16)(0);

  for(i.s0 = 0.0; i.s0 < 1.0; i = i + 0.1) {
    t1 = lgamma(i);
    t2 = lgamma(i + 0.01);
    t3 = lgamma(i + 0.02);
    t4 = lgamma(i + 0.03);
    t5 = lgamma(i + 0.04);
    t6 = lgamma(i + 0.05);
    t7 = lgamma(i + 0.06);
    t8 = lgamma(i + 0.07);
    t9 = lgamma(i + 0.08);
    t10 = lgamma(i + 0.09);
  }
  *result_lgamma =t1.s0+t1.s1+t1.s2+t1.s3+t1.s4+t1.s5+t1.s6+t1.s7+t1.s8+t1.s9+t1.sa+t1.sb+t1.sc+t1.sd+t1.se+t1.sf
  		+ t2.s0+t2.s1+t2.s2+t2.s3+t2.s4+t2.s5+t2.s6+t2.s7+t2.s8+t2.s9+t2.sa+t2.sb+t2.sc+t2.sd+t2.se+t2.sf
  		+ t3.s0+t3.s1+t3.s2+t3.s3+t3.s4+t3.s5+t3.s6+t3.s7+t3.s8+t3.s9+t3.sa+t3.sb+t3.sc+t3.sd+t3.se+t3.sf
  		+ t4.s0+t4.s1+t4.s2+t4.s3+t4.s4+t4.s5+t4.s6+t4.s7+t4.s8+t4.s9+t4.sa+t4.sb+t4.sc+t4.sd+t4.se+t4.sf 
  		+ t5.s0+t5.s1+t5.s2+t5.s3+t5.s4+t5.s5+t5.s6+t5.s7+t5.s8+t5.s9+t5.sa+t5.sb+t5.sc+t5.sd+t5.se+t5.sf 
  		+ t6.s0+t6.s1+t6.s2+t6.s3+t6.s4+t6.s5+t6.s6+t6.s7+t6.s8+t6.s9+t6.sa+t6.sb+t6.sc+t6.sd+t6.se+t6.sf 
  		+ t7.s0+t7.s1+t7.s2+t7.s3+t7.s4+t7.s5+t7.s6+t7.s7+t7.s8+t7.s9+t7.sa+t7.sb+t7.sc+t7.sd+t7.se+t7.sf 
  		+ t8.s0+t8.s1+t8.s2+t8.s3+t8.s4+t8.s5+t8.s6+t8.s7+t8.s8+t8.s9+t8.sa+t8.sb+t8.sc+t8.sd+t8.se+t8.sf 
  		+ t9.s0+t9.s1+t9.s2+t9.s3+t9.s4+t9.s5+t9.s6+t9.s7+t9.s8+t9.s9+t9.sa+t9.sb+t9.sc+t9.sd+t9.se+t9.sf 
  		+ t10.s0+t10.s1+t10.s2+t10.s3+t10.s4+t10.s5+t10.s6+t10.s7+t10.s8+t10.s9+t10.sa+t10.sb+t10.sc+t10.sd+t10.se+t10.sf;
}


