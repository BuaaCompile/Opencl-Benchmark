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

__kernel void kernel_exp_withDD1(__global float* result_exp, int N)
{
  float t1 = -9999.99;
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat128(t1 = exp(t1 / (t1 + 0.01)););
  }
  *result_exp = t1;
}

__kernel void kernel_exp_withDD2(__global float* result_exp, int N)
{
  float t1 = -9999.99;
  float2 t2 = t1 + (float2)(0);
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat64(t2 = exp(t2 / (t2 + 0.01)););
  }
  *result_exp = t2.s0 + t2.s1;
}

__kernel void kernel_exp_withDD4(__global float* result_exp, int N)
{
  float t1 = -9999.99;
  float4 t2 = t1 + (float4)(0);
  int i = 0;
  for(i = 0; i < N; i++) {
      repeat16(t2 = exp(t2 / (t2 + 0.01)););
  }
  *result_exp =t2.s0 + t2.s1 + t2.s2 + t2.s3;
}

__kernel void kernel_exp_withDD8(__global float* result_exp, int N)
{
  float t1 = -9999.99;
  float8 t2 = t1 + (float8)(0);
  int i = 0;
  for(i = 0; i < N; i++) {
      repeat16(t2 = exp(t2 / (t2 + 0.01)););
  }
  *result_exp = t2.s0 + t2.s1 + t2.s2 + t2.s3 + t2.s4 + t2.s5 + t2.s6 +t2.s7;
}

__kernel void kernel_exp_withDD16(__global float* result_exp, int N)
{
  float t1 = -9999.99;
  float16 t2 = t1 + (float16)(0);
  int i = 0;
  for(i = 0; i < N; i++) {
      repeat16(t2 = exp(t2 / (t2 + 0.01)););
  }
  *result_exp = t2.s0 + t2.s1 + t2.s2 + t2.s3 + t2.s4 + t2.s5 + t2.s6 +t2.s7+t2.s8+t2.s9+t2.sa+t2.sb+t2.sc+t2.sd+t2.se+t2.sf;
}

__kernel void kernel_exp_withoutDD1(__global float* result_exp, int N)
{
  float  t1 = 1.1;
  float  t2 = 1.1;
  float  t3 = t1;
  float  t4 = t3;
  float  t5 = t4;
  float  t6 = t5;
  float  t7 = t6;
  float  t8 = t7;
  float  t9 = t8;
  float  t10 = t9;
  float  t11 = 1.1;
  float  t12 = 1.1;

  float p = 0.0;
  for(p = 0.0; p < 0.0256 * N; p = p + 0.0001) {
    t1 += exp(p);
    t2 += exp(p + 0.01);
    t3 += exp(p + 0.02);
    t4 += exp(p + 0.03);
    t5 += exp(p + 0.04);
    t6 += exp(p + 0.05);
    t7 += exp(p + 0.06);
    t8 += exp(p + 0.07);
    t9 += exp(p + 0.08);
    t10 += exp(p + 0.09);
    t11 += exp(p + 0.11);
    t12 += exp(p + 0.12);
  }
  *result_exp = t1 + t2 + t3 + t4 + t5 + t6 + t7 + t8 + t9 + t10 + t11 + t12;
}

__kernel void kernel_exp_withoutDD2(__global float* result_exp, int N)
{
  float2  t1 = 1.1+(float2)(0);
  float2  t2 = 1.1+(float2)(0);
  float2  t3 = t1;
  float2  t4 = t3;
  float2  t5 = t4;
  float2  t6 = t5;
  float2  t7 = t6;
  float2  t8 = t7;
  float2  t9 = t8;
  float2  t10 = t9;
  float2  t11 = 1.1+(float2)(0);
  float2  t12 = 1.1+(float2)(0);

  float2 p = 0.0+(float2)(0);
  for(p.s0 = 0.0; p.s0 < 0.0128 * N; p = p + 0.0001) {
    t1 += exp(p);
    t2 += exp(p + 0.01);
    t3 += exp(p + 0.02);
    t4 += exp(p + 0.03);
    t5 += exp(p + 0.04);
    t6 += exp(p + 0.05);
    t7 += exp(p + 0.06);
    t8 += exp(p + 0.07);
    t9 += exp(p + 0.08);
    t10 += exp(p + 0.09);
    t11 += exp(p + 0.11);
    t12 += exp(p + 0.12);
  }
  *result_exp = t1.s0+t1.s1 + t2.s0+t2.s1 + t3.s0+t3.s1 + t4.s0+t4.s1 + t5.s0+t5.s1 + t6.s0+t6.s1 + t7.s0+t7.s1 + t8.s0+t8.s1 + t9.s0+t9.s1+ t10.s0+t10.s1 + t11.s0+t11.s1 + t12.s0+t12.s1;
}


__kernel void kernel_exp_withoutDD4(__global float* result_exp, int N)
{
  float4  t1 = 1.1+ (float4)(0);
  float4  t2 = 1.1+ (float4)(0);
  float4  t3 = t1;
  float4  t4 = t3;
  float4  t5 = t4;
  float4  t6 = t5;
  float4  t7 = t6;
  float4  t8 = t7;
  float4  t9 = t8;
  float4  t10 = t9;
  float4  t11 = 1.1+ (float4)(0);
  float4  t12 = 1.1+ (float4)(0);

  float4 p = 0.0+(float4)(0);
  for(p.s0 = 0.0; p.s0 < 0.0128 * N; p = p + 0.0001) {
    t1 += exp(p);
    t2 += exp(p + 0.01);
    t3 += exp(p + 0.02);
    t4 += exp(p + 0.03);
    t5 += exp(p + 0.04);
    t6 += exp(p + 0.05);
    t7 += exp(p + 0.06);
    t8 += exp(p + 0.07);
    t9 += exp(p + 0.08);
    t10 += exp(p + 0.09);
    t11 += exp(p + 0.11);
    t12 += exp(p + 0.12);
  }
  *result_exp = t1.s0+t1.s1+t1.s2+t1.s3 + t2.s0+t2.s1+t2.s2+t2.s3
		+ t3.s0+t3.s1+t3.s2+t3.s3 + t4.s0+t4.s1+t4.s2+t4.s3
		+ t5.s0+t5.s1+t5.s2+t5.s3 + t6.s0+t6.s1+t6.s2+t6.s3
		+ t7.s0+t7.s1+t7.s2+t7.s3 + t8.s0+t8.s1+t8.s2+t8.s3
		+ t9.s0+t9.s1+t9.s2+t9.s3 + t10.s0+t10.s1+t10.s2+t10.s3
		+ t11.s0+t11.s1+t11.s2+t11.s3 + t12.s0+t12.s1+t12.s2+t12.s3;
}

__kernel void kernel_exp_withoutDD8(__global float* result_exp, int N)
{
  float8  t1 = 1.1+ (float8)(0);
  float8  t2 = 1.1+ (float8)(0);
  float8  t3 = t1;
  float8  t4 = t3;
  float8  t5 = t4;
  float8  t6 = t5;
  float8  t7 = t6;
  float8  t8 = t7;
  float8  t9 = t8;
  float8  t10 = t9;
  float8  t11 = 1.1+ (float8)(0);
  float8  t12 = 1.1+ (float8)(0);

  float8 p = 0.0+(float8)(0);
  for(p.s0 = 0.0; p.s0 < 0.0128 * N; p = p + 0.0001) {
    t1 += exp(p);
    t2 += exp(p + 0.01);
    t3 += exp(p + 0.02);
    t4 += exp(p + 0.03);
    t5 += exp(p + 0.04);
    t6 += exp(p + 0.05);
    t7 += exp(p + 0.06);
    t8 += exp(p + 0.07);
    t9 += exp(p + 0.08);
    t10 += exp(p + 0.09);
    t11 += exp(p + 0.11);
    t12 += exp(p + 0.12);
  }
  *result_exp = t1.s0+t1.s1+t1.s2+t1.s3+t1.s4+t1.s5+t1.s6+t1.s7
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
  		+ t12.s0+t12.s1+t12.s2+t12.s3+t12.s4+t12.s5+t12.s6+t12.s7 ;
}

__kernel void kernel_exp_withoutDD16(__global float* result_exp, int N)
{
  float16  t1 = 1.1+ (float16)(0);
  float16  t2 = 1.1+ (float16)(0);
  float16  t3 = t1;
  float16  t4 = t3;
  float16  t5 = t4;
  float16  t6 = t5;
  float16  t7 = t6;
  float16  t8 = t7;
  float16  t9 = t8;
  float16  t10 = t9;
  float16  t11 = 1.1+ (float16)(0);
  float16  t12 = 1.1+ (float16)(0);

  float16 p = 0.0+(float16)(0);
  for(p.s0 = 0.0; p.s0 < 0.0032 * N; p = p + 0.0001) {
    t1 += exp(p);
    t2 += exp(p + 0.01);
    t3 += exp(p + 0.02);
    t4 += exp(p + 0.03);
    t5 += exp(p + 0.04);
    t6 += exp(p + 0.05);
    t7 += exp(p + 0.06);
    t8 += exp(p + 0.07);
    t9 += exp(p + 0.08);
    t10 += exp(p + 0.09);
    t11 += exp(p + 0.11);
    t12 += exp(p + 0.12);
  }
  *result_exp =  t1.s0+t1.s1+t1.s2+t1.s3+t1.s4+t1.s5+t1.s6+t1.s7+t1.s8+t1.s9+t1.sa+t1.sb+t1.sc+t1.sd+t1.se+t1.sf
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
  		+ t12.s0+t12.s1+t12.s2+t12.s3+t12.s4+t12.s5+t12.s6+t12.s7+t12.s8+t12.s9+t12.sa+t12.sb+t12.sc+t12.sd+t12.se+t12.sf;
}

__kernel void kernel_rsqrt_withDD1(__global float* result_rsqrt, int N)
{
  float t1 = 23456.234;
  int i = 0;
  for(i = 0; i <  N; i++) {
    repeat128(t1 = rsqrt(t1););
  }
  *result_rsqrt = t1;
}

__kernel void kernel_rsqrt_withDD2(__global float* result_rsqrt, int N)
{
  float t1 = 23456.234;
  float2 t2 = t1 + (float2)(0.1,0.2);
  int i = 0;
  for(i = 0; i <  N; i++) {
    repeat64(t2 = rsqrt(t2););
  }
  *result_rsqrt = t2.s0 + t2.s1;
}

__kernel void kernel_rsqrt_withDD4(__global float* result_rsqrt, int N)
{
  float t1 = 23456.234;
  float4 t2 = t1 + (float4)(0);
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat16(t2 = rsqrt(t2););
  }
  *result_rsqrt =t2.s0 + t2.s1 + t2.s2 + t2.s3;
}

__kernel void kernel_rsqrt_withDD8(__global float* result_rsqrt, int N)
{
  float t1 = 23456.234;
  float8 t2 = t1 + (float8)(1,1,1,0,1,0,1,1.1);
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat8(t2 = rsqrt(t2););
  }
  *result_rsqrt = t2.s0 + t2.s1 + t2.s2 + t2.s3 + t2.s4 + t2.s5 + t2.s6 +t2.s7;
}

__kernel void kernel_rsqrt_withDD16(__global float* result_rsqrt, int N)
{
  float t1 = 23456.234;
  float16 t2 = t1 + (float16)(0,0,0,1,0,0,1,0,1);
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat8(t2 = rsqrt(t2););
  }
  *result_rsqrt = t2.s0 + t2.s1 + t2.s2 + t2.s3 + t2.s4 + t2.s5 + t2.s6 +t2.s7+t2.s8+t2.s9+t2.sa+t2.sb+t2.sc+t2.sd+t2.se+t2.sf;
}

__kernel void kernel_rsqrt_withoutDD1(__global float* result_rsqrt, int N)
{
  float  t1 = 1.1;
  float  t2 = 1.1;
  float  t3 = t1;
  float  t4 = t3;
  float  t5 = t4;
  float  t6 = t5;
  float  t7 = t6;
  float  t8 = t7;
  float  t9 = t8;
  float  t10 = t9;

  float i = 0.01;

  for(i = 0.01; i <= 25.6 * N; i = i + 0.01) {
    t1 = rsqrt(i);
    t2 = rsqrt(i+0.01);
    t3 = rsqrt(i+0.02);
    t4 = rsqrt(i+0.03);
    t5 = rsqrt(i+0.04);
    t6 = rsqrt(i+0.05);
    t7 = rsqrt(i+0.06);
    t8 = rsqrt(i+0.07);
    t9 = rsqrt(i+0.08);
    t10 = rsqrt(i+0.09);
  }
  *result_rsqrt = t1 + t2 + t3 + t4 + t5 + t6 + t7 + t8 + t9 + t10;
}

__kernel void kernel_rsqrt_withoutDD2(__global float* result_rsqrt, int N)
{
  float2  t1 = 1.1+(float2)(0);
  float2  t2 = 1.1+(float2)(0);
  float2  t3 = t1;
  float2  t4 = t3;
  float2  t5 = t4;
  float2  t6 = t5;
  float2  t7 = t6;
  float2  t8 = t7;
  float2  t9 = t8;
  float2  t10 = t9;

  float2 i = 0.01+(float2)(0);

  for(i.s0 = 0.01; i.s0 <25.6 * N+0.01; i = i + 0.01) {
    t1 = rsqrt(i);
    t2 = rsqrt(i+0.01);
    t3 = rsqrt(i+0.02);
    t4 = rsqrt(i+0.03);
    t5 = rsqrt(i+0.04);
    t6 = rsqrt(i+0.05);
    t7 = rsqrt(i+0.06);
    t8 = rsqrt(i+0.07);
    t9 = rsqrt(i+0.08);
    t10 = rsqrt(i+0.09);
  }
  *result_rsqrt =  t1.s0+t1.s1 + t2.s0+t2.s1 + t3.s0+t3.s1 + t4.s0+t4.s1 + t5.s0+t5.s1 + t6.s0+t6.s1 + t7.s0+t7.s1 + t8.s0+t8.s1 + t9.s0+t9.s1+ t10.s0+t10.s1;
}


__kernel void kernel_rsqrt_withoutDD4(__global float* result_rsqrt, int N)
{
  float4  t1 = 1.1+(float4)(0);
  float4  t2 = 1.1+(float4)(0);
  float4  t3 = t1;
  float4  t4 = t3;
  float4  t5 = t4;
  float4  t6 = t5;
  float4  t7 = t6;
  float4  t8 = t7;
  float4  t9 = t8;
  float4  t10 = t9;

  float4 i = 0.01+(float4)(0);

  for(i.s0 = 0.01; i.s0 <25.6 * N+0.01; i = i + 0.01) {
    t1 = rsqrt(i);
    t2 = rsqrt(i+0.01);
    t3 = rsqrt(i+0.02);
    t4 = rsqrt(i+0.03);
    t5 = rsqrt(i+0.04);
    t6 = rsqrt(i+0.05);
    t7 = rsqrt(i+0.06);
    t8 = rsqrt(i+0.07);
    t9 = rsqrt(i+0.08);
    t10 = rsqrt(i+0.09);
  }
  *result_rsqrt = t1.s0+t1.s1+t1.s2+t1.s3 + t2.s0+t2.s1+t2.s2+t2.s3
	    	+ t3.s0+t3.s1+t3.s2+t3.s3 + t4.s0+t4.s1+t4.s2+t4.s3
		+ t5.s0+t5.s1+t5.s2+t5.s3 + t6.s0+t6.s1+t6.s2+t6.s3
		+ t7.s0+t7.s1+t7.s2+t7.s3 + t8.s0+t8.s1+t8.s2+t8.s3
		+ t9.s0+t9.s1+t9.s2+t9.s3 + t10.s0+t10.s1+t10.s2+t10.s3;
}

__kernel void kernel_rsqrt_withoutDD8(__global float* result_rsqrt, int N)
{
  float8  t1 = 1.1+(float8)(0);
  float8  t2 = 1.1+(float8)(0);
  float8  t3 = t1;
  float8  t4 = t3;
  float8  t5 = t4;
  float8  t6 = t5;
  float8  t7 = t6;
  float8  t8 = t7;
  float8  t9 = t8;
  float8  t10 = t9;

  float8 i = 0.01+(float8)(0);

  for(i.s0 = 0.01; i.s0 <6.4 * N+0.01; i = i + 0.01) {
    t1 = rsqrt(i);
    t2 = rsqrt(i+0.01);
    t3 = rsqrt(i+0.02);
    t4 = rsqrt(i+0.03);
    t5 = rsqrt(i+0.04);
    t6 = rsqrt(i+0.05);
    t7 = rsqrt(i+0.06);
    t8 = rsqrt(i+0.07);
    t9 = rsqrt(i+0.08);
    t10 = rsqrt(i+0.09);
  }
  *result_rsqrt = t1.s0+t1.s1+t1.s2+t1.s3+t1.s4+t1.s5+t1.s6+t1.s7
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

__kernel void kernel_rsqrt_withoutDD16(__global float* result_rsqrt, int N)
{
  float16  t1 = 1.1+(float16)(0);
  float16  t2 = 1.1+(float16)(0);
  float16  t3 = t1;
  float16  t4 = t3;
  float16  t5 = t4;
  float16  t6 = t5;
  float16  t7 = t6;
  float16  t8 = t7;
  float16  t9 = t8;
  float16  t10 = t9;

  float16 i = 0.01+(float16)(0);

  for(i.s0 = 0.01; i.s0 <0.4 * N+0.01; i = i + 0.01) {
    t1 = rsqrt(i);
    t2 = rsqrt(i+0.01);
    t3 = rsqrt(i+0.02);
    t4 = rsqrt(i+0.03);
    t5 = rsqrt(i+0.04);
    t6 = rsqrt(i+0.05);
    t7 = rsqrt(i+0.06);
    t8 = rsqrt(i+0.07);
    t9 = rsqrt(i+0.08);
    t10 = rsqrt(i+0.09);
  }
  *result_rsqrt =  t1.s0+t1.s1+t1.s2+t1.s3+t1.s4+t1.s5+t1.s6+t1.s7+t1.s8+t1.s9+t1.sa+t1.sb+t1.sc+t1.sd+t1.se+t1.sf
  		+ t2.s0+t2.s1+t2.s2+t2.s3+t2.s4+t2.s5+t2.s6+t2.s7+t2.s8+t2.s9+t2.sa+t2.sb+t2.sc+t2.sd+t2.se+t2.sf
  		+ t3.s0+t3.s1+t3.s2+t3.s3+t3.s4+t3.s5+t3.s6+t3.s7+t3.s8+t3.s9+t3.sa+t3.sb+t3.sc+t3.sd+t3.se+t3.sf
  		+ t4.s0+t4.s1+t4.s2+t4.s3+t4.s4+t4.s5+t4.s6+t4.s7+t4.s8+t4.s9+t4.sa+t4.sb+t4.sc+t4.sd+t4.se+t4.sf 
  		+ t5.s0+t5.s1+t5.s2+t5.s3+t5.s4+t5.s5+t5.s6+t5.s7+t5.s8+t5.s9+t5.sa+t5.sb+t5.sc+t5.sd+t5.se+t5.sf 
  		+ t6.s0+t6.s1+t6.s2+t6.s3+t6.s4+t6.s5+t6.s6+t6.s7+t6.s8+t6.s9+t6.sa+t6.sb+t6.sc+t6.sd+t6.se+t6.sf 
  		+ t7.s0+t7.s1+t7.s2+t7.s3+t7.s4+t7.s5+t7.s6+t7.s7+t7.s8+t7.s9+t7.sa+t7.sb+t7.sc+t7.sd+t7.se+t7.sf 
  		+ t8.s0+t8.s1+t8.s2+t8.s3+t8.s4+t8.s5+t8.s6+t8.s7+t8.s8+t8.s9+t8.sa+t8.sb+t8.sc+t8.sd+t8.se+t8.sf 
  		+ t9.s0+t9.s1+t9.s2+t9.s3+t9.s4+t9.s5+t9.s6+t9.s7+t9.s8+t9.s9+t9.sa+t9.sb+t9.sc+t9.sd+t9.se+t9.sf 
  		+ t10.s0+t10.s1+t10.s2+t10.s3+t10.s4+t10.s5+t10.s6+t10.s7+t10.s8+t10.s9+t10.sa+t10.sb+t10.sc+t10.sd+t10.se+t10.sf  ;
}


__kernel void kernel_log_withDD1(__global float* result_log, int N)
{
  float t1 = 9999.999;
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat256(t1 = log((t1 + 0.1) / t1););
  }
  *result_log = t1;
}

__kernel void kernel_log_withDD2(__global float* result_log, int N)
{
  float2 t1 = 9999.999+(float2)(0);
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat128(t1 = log((t1 + 0.1) / t1););
  }
  *result_log = t1.s0 + t1.s1;
}


__kernel void kernel_log_withDD4(__global float* result_log, int N)
{
  float4 t1 = 9999.999+(float4)(0);
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat128(t1 = log((t1 + 0.1) / t1););
  }
  *result_log = t1.s0 + t1.s1 + t1.s2 + t1.s3;
}

__kernel void kernel_log_withDD8(__global float* result_log, int N)
{
  float8 t1 = 9999.999+(float8)(0);
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat128(t1 = log((t1 + 0.1) / t1););
  }
  *result_log = t1.s0 + t1.s1 + t1.s2 + t1.s3 + t1.s4 + t1.s5 + t1.s6 +t1.s7;
}

__kernel void kernel_log_withDD16(__global float* result_log, int N)
{
  float16 t1 = 9999.999+(float16)(0);
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat128(t1 = log((t1 + 0.1) / t1););
  }
  *result_log = t1.s0 + t1.s1 + t1.s2 + t1.s3 + t1.s4 + t1.s5 + t1.s6 +t1.s7+t1.s8+t1.s9+t1.sa+t1.sb+t1.sc+t1.sd+t1.se+t1.sf;
}

__kernel void kernel_log_withoutDD1(__global float* result_log, int N)
{
  float  t1 = 0.0;
  float  t2 = 0.0;
  float  t3 = t1;
  float  t4 = t3;
  float  t5 = t4;
  float  t6 = t5;
  float  t7 = t6;
  float  t8 = t7;
  float  t9 = t8;
  float  t10 = t9;
  float  t11 = 0.0;
  float  t12 = 0.0;

  float i = 1.0;
  float p = 256 * N;

  for(i = 1.0; i <= p; i = i + 1.0) {
    t1 += log(i);
    t2 += log(i);
    t3 += log(i);
    t4 += log(i);
    t5 += log(i);
    t6 += log(i);
    t7 += log(i);
    t8 += log(i);
    t9 += log(i);
    t10 += log(i);
    t11 += log(i);
    t12 += log(i);
  }

  *result_log = t1 + t2 + t3 + t4 + t5 + t6 + t7 + t8 + t9 + t10 + t11 + t12;
}


__kernel void kernel_log_withoutDD2(__global float* result_log, int N)
{
  float2  t1 = 0.0+(float2)(0);
  float2  t2 = 0.0+(float2)(0);
  float2  t3 = t1;
  float2  t4 = t3;
  float2  t5 = t4;
  float2  t6 = t5;
  float2  t7 = t6;
  float2  t8 = t7;
  float2  t9 = t8;
  float2  t10 = t9;
  float2  t11 = 0.0+(float2)(0);
  float2  t12 = 0.0+(float2)(0);

  float2 i = 1.0+(float2)(0);
  float p = 64 * N;

  for(i.s0 = 1.0; i.s0 < p+1.0; i = i + 1.0) {
    t1 += log(i);
    t2 += log(i);
    t3 += log(i);
    t4 += log(i);
    t5 += log(i);
    t6 += log(i);
    t7 += log(i);
    t8 += log(i);
    t9 += log(i);
    t10 += log(i);
    t11 += log(i);
    t12 += log(i);
  }

  *result_log = t1.s0+t1.s1 + t2.s0+t2.s1 + t3.s0+t3.s1 + t4.s0+t4.s1 + t5.s0+t5.s1 + t6.s0+t6.s1 + t7.s0+t7.s1 + t8.s0+t8.s1 + t9.s0+t9.s1+ t10.s0+t10.s1 + t11.s0+t11.s1 + t12.s0+t12.s1;
}


__kernel void kernel_log_withoutDD4(__global float* result_log, int N)
{
  float4  t1 = 0.0+(float4)(0);
  float4  t2 = 0.0+(float4)(0);
  float4  t3 = t1;
  float4  t4 = t3;
  float4  t5 = t4;
  float4  t6 = t5;
  float4  t7 = t6;
  float4  t8 = t7;
  float4  t9 = t8;
  float4  t10 = t9;
  float4  t11 = 0.0+(float4)(0);
  float4  t12 = 0.0+(float4)(0);

  float4 i = 1.0+(float4)(0);
  float p = 64 * N;

  for(i.s0 = 1.0; i.s0 < p+1.0; i = i + 1.0) {
    t1 += log(i);
    t2 += log(i);
    t3 += log(i);
    t4 += log(i);
    t5 += log(i);
    t6 += log(i);
    t7 += log(i);
    t8 += log(i);
    t9 += log(i);
    t10 += log(i);
    t11 += log(i);
    t12 += log(i);
  }

  *result_log =  t1.s0+t1.s1+t1.s2+t1.s3 + t2.s0+t2.s1+t2.s2+t2.s3
	        + t3.s0+t3.s1+t3.s2+t3.s3 + t4.s0+t4.s1+t4.s2+t4.s3
		+ t5.s0+t5.s1+t5.s2+t5.s3 + t6.s0+t6.s1+t6.s2+t6.s3
		+ t7.s0+t7.s1+t7.s2+t7.s3 + t8.s0+t8.s1+t8.s2+t8.s3
		+ t9.s0+t9.s1+t9.s2+t9.s3 + t10.s0+t10.s1+t10.s2+t10.s3
		+ t11.s0+t11.s1+t11.s2+t11.s3 + t12.s0+t12.s1+t12.s2+t12.s3;
}

__kernel void kernel_log_withoutDD8(__global float* result_log, int N)
{
  float8  t1 = 0.0+(float8)(0);
  float8  t2 = 0.0+(float8)(0);
  float8  t3 = t1;
  float8  t4 = t3;
  float8  t5 = t4;
  float8  t6 = t5;
  float8  t7 = t6;
  float8  t8 = t7;
  float8  t9 = t8;
  float8  t10 = t9;
  float8  t11 = 0.0+(float8)(0);
  float8  t12 = 0.0+(float8)(0);

  float8 i =1.0+(float8)(0);
  float p = 32 * N;

  for(i.s0 = 1.0; i.s0 < p+1.0; i = i + 1.0) {
    t1 += log(i);
    t2 += log(i);
    t3 += log(i);
    t4 += log(i);
    t5 += log(i);
    t6 += log(i);
    t7 += log(i);
    t8 += log(i);
    t9 += log(i);
    t10 += log(i);
    t11 += log(i);
    t12 += log(i);
  }

  *result_log = t1.s0+t1.s1+t1.s2+t1.s3+t1.s4+t1.s5+t1.s6+t1.s7
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
  		+ t12.s0+t12.s1+t12.s2+t12.s3+t12.s4+t12.s5+t12.s6+t12.s7;
}

__kernel void kernel_log_withoutDD16(__global float* result_log, int N)
{
  float16  t1 = 0.0+(float16)(0);
  float16  t2 = 0.0+(float16)(0);
  float16  t3 = t1;
  float16  t4 = t3;
  float16  t5 = t4;
  float16  t6 = t5;
  float16  t7 = t6;
  float16  t8 = t7;
  float16  t9 = t8;
  float16  t10 = t9;
  float16  t11 = 0.0+(float16)(0);
  float16  t12 = 0.0+(float16)(0);

  float16 i = 1.0+(float16)(0);
  float p = 16 * N;

  for(i.s0 = 1.0; i.s0 < p+1.0; i = i + 1.0) {
    t1 += log(i);
    t2 += log(i);
    t3 += log(i);
    t4 += log(i);
    t5 += log(i);
    t6 += log(i);
    t7 += log(i);
    t8 += log(i);
    t9 += log(i);
    t10 += log(i);
    t11 += log(i);
    t12 += log(i);
  }

  *result_log = t1.s0+t1.s1+t1.s2+t1.s3+t1.s4+t1.s5+t1.s6+t1.s7+t1.s8+t1.s9+t1.sa+t1.sb+t1.sc+t1.sd+t1.se+t1.sf
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
  		+ t12.s0+t12.s1+t12.s2+t12.s3+t12.s4+t12.s5+t12.s6+t12.s7+t12.s8+t12.s9+t12.sa+t12.sb+t12.sc+t12.sd+t12.se+t12.sf;
}














