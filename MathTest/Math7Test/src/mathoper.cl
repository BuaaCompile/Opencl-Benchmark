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

__kernel void kernel_cbrt_withDD1(__global float *result_cbrt, int N)
{
  float p1 = 345.634;
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat32(p1 = cbrt(p1););
  }
  *result_cbrt = p1;
}

__kernel void kernel_cbrt_withDD2(__global float *result_cbrt, int N)
{
  float2 p1 = 345.634+(float2)(0);
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat32(p1 = cbrt(p1););
  }
  *result_cbrt = p1.s0+p1.s1;
}
__kernel void kernel_cbrt_withDD4(__global float *result_cbrt, int N)
{
  float4 p1 = 345.634+(float4)(0);
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat32(p1 = cbrt(p1););
  }
  *result_cbrt = p1.s0 + p1.s1 + p1.s2 + p1.s3;;
}
__kernel void kernel_cbrt_withDD8(__global float *result_cbrt, int N)
{
  float8 p1= 345.634+(float8)(0);
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat32(p1 = cbrt(p1););
  }
  *result_cbrt = p1.s0 + p1.s1 + p1.s2 + p1.s3 + p1.s4 + p1.s5 + p1.s6 +p1.s7;
}
__kernel void kernel_cbrt_withDD16(__global float *result_cbrt, int N)
{
  float16 p1 = 345.634+(float16)(0);
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat16(p1 = cbrt(p1););
  }
  *result_cbrt = p1.s0 + p1.s1 + p1.s2 + p1.s3 + p1.s4 + p1.s5 + p1.s6 +p1.s7+p1.s8+p1.s9+p1.sa+p1.sb+p1.sc+p1.sd+p1.se+p1.sf;
}

__kernel void kernel_cbrt_withoutDD1(__global float *result_cbrt, int n)
{
  float p1 = 1.0;
  float p2 = 1.0;
  float p3 = 1.0;
  float p4 = 1.0;
  float p5 = 1.0;
  float p6 = 1.0;
  float p7 = 1.0;
  float p8 = 1.0;
  float p9 = 1.0;
  float p10 = 1.0;

  float i = 0.0;
  float N = 3 * (float)(n);

  for(i = 0.0; i < N; i = i + 1.0) {
    p1 = cbrt(i + 0.01);
    p2 = cbrt(i + 0.02);
    p3 = cbrt(i + 0.03);
    p4 = cbrt(i + 0.04);
    p5 = cbrt(i + 0.05);
    p6 = cbrt(i + 0.06);
    p7 = cbrt(i + 0.07);
    p8 = cbrt(i + 0.08);
    p9 = cbrt(i + 0.09);
    p10 = cbrt(i + 0.1);
  }
  *result_cbrt = p1 + p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9 + p10;
}

__kernel void kernel_cbrt_withoutDD2(__global float *result_cbrt, int n)
{
  float2 p1 = 1.0+(float2)(0);
  float2 p2 = 1.0+(float2)(0);
  float2 p3 = 1.0+(float2)(0);
  float2 p4 = 1.0+(float2)(0);
  float2 p5 = 1.0+(float2)(0);
  float2 p6 = 1.0+(float2)(0);
  float2 p7 = 1.0+(float2)(0);
  float2 p8 = 1.0+(float2)(0);
  float2 p9 = 1.0+(float2)(0);
  float2 p10 = 1.0+(float2)(0);

  float2 i = 0.0+(float2)(0);
  float N = 3 * (float)(n);

  int j=0;
  for(j=0;j<N;j++,i=i+1){
    p1 = cbrt(i + 0.01);
    p2 = cbrt(i + 0.02);
    p3 = cbrt(i + 0.03);
    p4 = cbrt(i + 0.04);
    p5 = cbrt(i + 0.05);
    p6 = cbrt(i + 0.06);
    p7 = cbrt(i + 0.07);
    p8 = cbrt(i + 0.08);
    p9 = cbrt(i + 0.09);
    p10 = cbrt(i + 0.1);
  }
  *result_cbrt = p1.s0+p1.s1 + p2.s0+p2.s1 + p3.s0+p3.s1 + p4.s0+p4.s1 + p5.s0+p5.s1 + p6.s0+p6.s1 + p7.s0+p7.s1 + p8.s0+p8.s1 + p9.s0+p9.s1+ p10.s0+p10.s1 ;
}

__kernel void kernel_cbrt_withoutDD4(__global float *result_cbrt, int n)
{
  float4 p1 = 1.0+(float4)(0);
  float4 p2 = 1.0+(float4)(0);
  float4 p3 = 1.0+(float4)(0);
  float4 p4 = 1.0+(float4)(0);
  float4 p5 = 1.0+(float4)(0);
  float4 p6 = 1.0+(float4)(0);
  float4 p7 = 1.0+(float4)(0);
  float4 p8 = 1.0+(float4)(0);
  float4 p9 = 1.0+(float4)(0);
  float4 p10 = 1.0+(float4)(0);

  float4 i = 0.0+(float4)(0);
  float N = 3 * (float)(n);

  int j=0;
  for(j=0;j<N;j++,i=i+1) {
    p1 = cbrt(i + 0.01);
    p2 = cbrt(i + 0.02);
    p3 = cbrt(i + 0.03);
    p4 = cbrt(i + 0.04);
    p5 = cbrt(i + 0.05);
    p6 = cbrt(i + 0.06);
    p7 = cbrt(i + 0.07);
    p8 = cbrt(i + 0.08);
    p9 = cbrt(i + 0.09);
    p10 = cbrt(i + 0.1);
  }
  *result_cbrt =  p1.s0+p1.s1+p1.s2+p1.s3 + p2.s0+p2.s1+p2.s2+p2.s3 + p3.s0+p3.s1+p3.s2+p3.s3 + p4.s0+p4.s1+p4.s2+p4.s3 + p5.s0+p5.s1+p5.s2+p5.s3 + p6.s0+p6.s1+p6.s2+p6.s3 + p7.s0+p7.s1+p7.s2+p7.s3 + p8.s0+p8.s1+p8.s2+p8.s3 + p9.s0+p9.s1+p9.s2+p9.s3 + p10.s0+p10.s1+p10.s2+p10.s3;
}

__kernel void kernel_cbrt_withoutDD8(__global float *result_cbrt, int n)
{
  float8 p1 = 1.0+(float8)(0);
  float8 p2 = 1.0+(float8)(0);
  float8 p3 = 1.0+(float8)(0);
  float8 p4 = 1.0+(float8)(0);
  float8 p5 = 1.0+(float8)(0);
  float8 p6 = 1.0+(float8)(0);
  float8 p7 = 1.0+(float8)(0);
  float8 p8 = 1.0+(float8)(0);
  float8 p9 = 1.0+(float8)(0);
  float8 p10 = 1.0+(float8)(0);

  float8 i = 0.0+(float8)(0);
  float N = 3 * (float)(n);

  int j=0;
  for(j=0;j<N;j++,i=i+1) {
    p1 = cbrt(i + 0.01);
    p2 = cbrt(i + 0.02);
    p3 = cbrt(i + 0.03);
    p4 = cbrt(i + 0.04);
    p5 = cbrt(i + 0.05);
    p6 = cbrt(i + 0.06);
    p7 = cbrt(i + 0.07);
    p8 = cbrt(i + 0.08);
    p9 = cbrt(i + 0.09);
    p10 = cbrt(i + 0.1);
  }
  *result_cbrt = p1.s0+p1.s1+p1.s2+p1.s3+p1.s4+p1.s5+p1.s6+p1.s7
  			  + p2.s0+p2.s1+p2.s2+p2.s3+p2.s4+p2.s5+p2.s6+p2.s7
  			  + p3.s0+p3.s1+p3.s2+p3.s3+p3.s4+p3.s5+p3.s6+p3.s7 
  			  + p4.s0+p4.s1+p4.s2+p4.s3+p4.s4+p4.s5+p4.s6+p4.s7 
  			  + p5.s0+p5.s1+p5.s2+p5.s3+p5.s4+p5.s5+p5.s6+p5.s7 
  			  + p6.s0+p6.s1+p6.s2+p6.s3+p6.s4+p6.s5+p6.s6+p6.s7 
  			  + p7.s0+p7.s1+p7.s2+p7.s3+p7.s4+p7.s5+p7.s6+p7.s7 
  			  + p8.s0+p8.s1+p8.s2+p8.s3+p8.s4+p8.s5+p8.s6+p8.s7 
  			  + p9.s0+p9.s1+p9.s2+p9.s3+p9.s4+p9.s5+p9.s6+p9.s7 
  			  + p10.s0+p10.s1+p10.s2+p10.s3+p10.s4+p10.s5+p10.s6+p10.s7 ;
}

__kernel void kernel_cbrt_withoutDD16(__global float *result_cbrt, int n)
{
  float16 p1 = 1.0+(float16)(0);
  float16 p2 = 1.0+(float16)(0);
  float16 p3 = 1.0+(float16)(0);
  float16 p4 = 1.0+(float16)(0);
  float16 p5 = 1.0+(float16)(0);
  float16 p6 = 1.0+(float16)(0);
  float16 p7 = 1.0+(float16)(0);
  float16 p8 = 1.0+(float16)(0);
  float16 p9 = 1.0+(float16)(0);
  float16 p10 = 1.0+(float16)(0);

  float16 i = 0.0+(float16)(0);
  float N = 3 * (float)(n);

  int j=0;
  for(j=0;j<N;j++,i=i+1) {
    p1 = cbrt(i + 0.01);
    p2 = cbrt(i + 0.02);
    p3 = cbrt(i + 0.03);
    p4 = cbrt(i + 0.04);
    p5 = cbrt(i + 0.05);
    p6 = cbrt(i + 0.06);
    p7 = cbrt(i + 0.07);
    p8 = cbrt(i + 0.08);
    p9 = cbrt(i + 0.09);
    p10 = cbrt(i + 0.1);
  }
  *result_cbrt =  p1.s0+p1.s1+p1.s2+p1.s3+p1.s4+p1.s5+p1.s6+p1.s7+p1.s8+p1.s9+p1.sa+p1.sb+p1.sc+p1.sd+p1.se+p1.sf
  			  + p2.s0+p2.s1+p2.s2+p2.s3+p2.s4+p2.s5+p2.s6+p2.s7+p2.s8+p2.s9+p2.sa+p2.sb+p2.sc+p2.sd+p2.se+p2.sf
  			  + p3.s0+p3.s1+p3.s2+p3.s3+p3.s4+p3.s5+p3.s6+p3.s7+p3.s8+p3.s9+p3.sa+p3.sb+p3.sc+p3.sd+p3.se+p3.sf
  			  + p4.s0+p4.s1+p4.s2+p4.s3+p4.s4+p4.s5+p4.s6+p4.s7+p4.s8+p4.s9+p4.sa+p4.sb+p4.sc+p4.sd+p4.se+p4.sf 
  			  + p5.s0+p5.s1+p5.s2+p5.s3+p5.s4+p5.s5+p5.s6+p5.s7+p5.s8+p5.s9+p5.sa+p5.sb+p5.sc+p5.sd+p5.se+p5.sf 
  			  + p6.s0+p6.s1+p6.s2+p6.s3+p6.s4+p6.s5+p6.s6+p6.s7+p6.s8+p6.s9+p6.sa+p6.sb+p6.sc+p6.sd+p6.se+p6.sf 
  			  + p7.s0+p7.s1+p7.s2+p7.s3+p7.s4+p7.s5+p7.s6+p7.s7+p7.s8+p7.s9+p7.sa+p7.sb+p7.sc+p7.sd+p7.se+p7.sf 
  			  + p8.s0+p8.s1+p8.s2+p8.s3+p8.s4+p8.s5+p8.s6+p8.s7+p8.s8+p8.s9+p8.sa+p8.sb+p8.sc+p8.sd+p8.se+p8.sf 
  			  + p9.s0+p9.s1+p9.s2+p9.s3+p9.s4+p9.s5+p9.s6+p9.s7+p9.s8+p9.s9+p9.sa+p9.sb+p9.sc+p9.sd+p9.se+p9.sf 
  			  + p10.s0+p10.s1+p10.s2+p10.s3+p10.s4+p10.s5+p10.s6+p10.s7+p10.s8+p10.s9+p10.sa+p10.sb+p10.sc+p10.sd+p10.se+p10.sf ;
}

__kernel void kernel_ceil_withDD1(__global float*result_ceil, int N)
{
  float p1 = -0.25;
  int i = 0;
  for(i = 0; i < N; i = i + 1) {
    repeat64(p1 += ceil(p1););
  }
  *result_ceil = p1;
}

__kernel void kernel_ceil_withDD2(__global float*result_ceil, int N)
{
  float2 p1 = -0.25+ (float2)(0);
  int i = 0;
  for(i = 0; i < N; i = i + 1) {
    repeat64(p1 += ceil(p1););
  }
  *result_ceil = p1.s0 + p1.s1;
}

__kernel void kernel_ceil_withDD4(__global float*result_ceil, int N)
{
  float4 p1 = -0.25 + (float4)(0);
  int i = 0;
  for(i = 0; i < N; i = i + 1) {
    repeat64(p1 += ceil(p1););
  }
  *result_ceil = p1.s0 + p1.s1 + p1.s2 + p1.s3;
}

__kernel void kernel_ceil_withDD8(__global float*result_ceil, int N)
{
  float8 p1 = -0.25 + (float8)(0);
  int i = 0;
  for(i = 0; i < N; i = i + 1) {
    repeat64(p1 += ceil(p1););
  }
  *result_ceil = p1.s0 + p1.s1 + p1.s2 + p1.s3 + p1.s4 + p1.s5 + p1.s6 +p1.s7;
}

__kernel void kernel_ceil_withDD16(__global float*result_ceil, int N)
{
  float16 p1 = -0.25 + (float16)(0);
  int i = 0;
  for(i = 0; i < N; i = i + 1) {
    repeat64(p1 += ceil(p1););
  }
  *result_ceil = p1.s0 + p1.s1 + p1.s2 + p1.s3 + p1.s4 + p1.s5 + p1.s6 +p1.s7+p1.s8+p1.s9+p1.sa+p1.sb+p1.sc+p1.sd+p1.se+p1.sf;
}
__kernel void kernel_ceil_withoutDD1(__global float*result_ceil, int n)
{
  float p1 = 1.23;
  float p2 = 1.23;
  float p3 = 1.23;
  float p4 = 1.23;
  float p5 = 1.23;
  float p6 = 1.23;
  float p7 = 1.23;
  float p8 = 1.23;
  float p9 = 1.23;
  float p10 = 1.23;
  float p11 = 1.23;
  float p12 = 1.23;
  float p13 = 1.23;
  float p14 = 1.23;
  float p15 = 1.23;
  float p16 = 1.23;
  float p17 = 1.23;
  float p18 = 1.23;
  float p19 = 1.23;
  float p20 = 1.23;
  float p21 = 1.23;
  float p22 = 1.23;
  float p23 = 1.23;
  float p24 = 1.23;
  float p25 = 1.23;
  float p26 = 1.23;
  float p27 = 1.23;
  float p28 = 1.23;
  float p29 = 1.23;
  float p30 = 1.23;
  float p31 = 1.23;
  float p32 = 1.23;
  float p33 = 1.23;
  float p34 = 1.23;
  float p35 = 1.23;
  float p36 = 1.23;
  float p37 = 1.23;
  float p38 = 1.23;
  float p39 = 1.23;
  float p40 = 1.23;

  float i = 0.0;
  float N = 256.0 * n;

  for(i = 0.0; i < N; i = i + 1.0) {
    p1 += ceil(i + 0.001);
    p2 += ceil(i + 0.002);
    p3 += ceil(i + 0.003);
    p4 += ceil(i + 0.005);
    p5 += ceil(i + 0.006);
    p6 += ceil(i + 0.007);
    p7 += ceil(i + 0.008);
    p8 += ceil(i + 0.009);
    p9 += ceil(i + 0.012);
    p10 += ceil(i + 0.031);
    p11 += ceil(i + 0.001);
    p12 += ceil(i + 0.002);
    p13 += ceil(i + 0.003);
    p14 += ceil(i + 0.005);
    p15 += ceil(i + 0.006);
    p16 += ceil(i + 0.007);
    p17 += ceil(i + 0.008);
    p18 += ceil(i + 0.009);
    p19 += ceil(i + 0.012);
    p20 += ceil(i + 0.031);
    p21 += ceil(i + 0.001);
    p22 += ceil(i + 0.002);
    p23 += ceil(i + 0.003);
    p24 += ceil(i + 0.005);
    p25 += ceil(i + 0.006);
    p26 += ceil(i + 0.007);
    p27 += ceil(i + 0.008);
    p28 += ceil(i + 0.009);
    p29 += ceil(i + 0.012);
    p30 += ceil(i + 0.031);
    p31 += ceil(i + 0.001);
    p32 += ceil(i + 0.002);
    p33 += ceil(i + 0.003);
    p34 += ceil(i + 0.005);
    p35 += ceil(i + 0.006);
    p36 += ceil(i + 0.007);
    p37 += ceil(i + 0.008);
    p38 += ceil(i + 0.009);
    p39 += ceil(i + 0.012);
    p40 += ceil(i + 0.031);
  }
  *result_ceil = p1 + p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9 + p10 + p11 + p12 + p13 + p14 + p15 + p16 + p17 + p18 + p19 + p20 + p21 + p22 + p23 + p24 + p25 + p26 + p27 + p28 + p29 + p30 + p31 + p32 + p33 + p34 + p35 + p36 + p37 + p38 + p39 + p40;
}

__kernel void kernel_ceil_withoutDD2(__global float*result_ceil, int n)
{
 float2 p1 = 1.23+(float2)(0);
  float2 p2 = 1.23+(float2)(0);
  float2 p3 = 1.23+(float2)(0);
  float2 p4 = 1.23+(float2)(0);
  float2 p5 = 1.23+(float2)(0);
  float2 p6 = 1.23+(float2)(0);
  float2 p7 = 1.23+(float2)(0);
  float2 p8 = 1.23+(float2)(0);
  float2 p9 = 1.23+(float2)(0);
  float2 p10 = 1.23+(float2)(0);
  float2 p11 = 1.23+(float2)(0);
  float2 p12 = 1.23+(float2)(0);
  float2 p13 = 1.23+(float2)(0);
  float2 p14 = 1.23+(float2)(0);
  float2 p15 = 1.23+(float2)(0);
  float2 p16 = 1.23+(float2)(0);
  float2 p17 = 1.23+(float2)(0);
  float2 p18 = 1.23+(float2)(0);
  float2 p19 = 1.23+(float2)(0);
  float2 p20 = 1.23+(float2)(0);
  float2 p21 = 1.23+(float2)(0);
  float2 p22 = 1.23+(float2)(0);
  float2 p23 = 1.23+(float2)(0);
  float2 p24 = 1.23+(float2)(0);
  float2 p25 = 1.23+(float2)(0);
  float2 p26 = 1.23+(float2)(0);
  float2 p27 = 1.23+(float2)(0);
  float2 p28 = 1.23+(float2)(0);
  float2 p29 = 1.23+(float2)(0);
  float2 p30 = 1.23+(float2)(0);
  float2 p31 = 1.23+(float2)(0);
  float2 p32 = 1.23+(float2)(0);
  float2 p33 = 1.23+(float2)(0);
  float2 p34 = 1.23+(float2)(0);
  float2 p35 = 1.23+(float2)(0);
  float2 p36 = 1.23+(float2)(0);
  float2 p37 = 1.23+(float2)(0);
  float2 p38 = 1.23+(float2)(0);
  float2 p39 = 1.23+(float2)(0);
  float2 p40 = 1.23+(float2)(0);

  float2 i = 0.0+(float2)(0);
  float N = 128.0 * n;

  int j=0;
  for(j=0;j<N;j++,i=i+1) {
    p1 += ceil(i + 0.001);
    p2 += ceil(i + 0.002);
    p3 += ceil(i + 0.003);
    p4 += ceil(i + 0.005);
    p5 += ceil(i + 0.006);
    p6 += ceil(i + 0.007);
    p7 += ceil(i + 0.008);
    p8 += ceil(i + 0.009);
    p9 += ceil(i + 0.012);
    p10 += ceil(i + 0.031);
    p11 += ceil(i + 0.001);
    p12 += ceil(i + 0.002);
    p13 += ceil(i + 0.003);
    p14 += ceil(i + 0.005);
    p15 += ceil(i + 0.006);
    p16 += ceil(i + 0.007);
    p17 += ceil(i + 0.008);
    p18 += ceil(i + 0.009);
    p19 += ceil(i + 0.012);
    p20 += ceil(i + 0.031);
    p21 += ceil(i + 0.001);
    p22 += ceil(i + 0.002);
    p23 += ceil(i + 0.003);
    p24 += ceil(i + 0.005);
    p25 += ceil(i + 0.006);
    p26 += ceil(i + 0.007);
    p27 += ceil(i + 0.008);
    p28 += ceil(i + 0.009);
    p29 += ceil(i + 0.012);
    p30 += ceil(i + 0.031);
    p31 += ceil(i + 0.001);
    p32 += ceil(i + 0.002);
    p33 += ceil(i + 0.003);
    p34 += ceil(i + 0.005);
    p35 += ceil(i + 0.006);
    p36 += ceil(i + 0.007);
    p37 += ceil(i + 0.008);
    p38 += ceil(i + 0.009);
    p39 += ceil(i + 0.012);
    p40 += ceil(i + 0.031);
  }
  *result_ceil = p1.s0+p1.s1 + p2.s0+p2.s1 + p3.s0+p3.s1 + p4.s0+p4.s1 + p5.s0+p5.s1 + p6.s0+p6.s1 + p7.s0+p7.s1 + p8.s0 
                 + p8.s1 + p9.s0+p9.s1+ p10.s0+p10.s1 + p11.s0+p11.s1 + p12.s0+p12.s1+ p13.s0+p13.s1 + p14.s0+p14.s1 
		 + p15.s0+p15.s1+ p16.s0+p16.s1+ p17.s0+p17.s1 + p18.s0+p18.s1 + p19.s0+p19.s1+ p20.s0+p20.s1+ p21.s0
		 +p21.s1 + p22.s0+p22.s1 + p23.s0+p23.s1 + p24.s0+p24.s1 + p25.s0+p25.s1 + p26.s0+p26.s1 + p27.s0+p27.s1 
		 + p28.s0+p28.s1 + p29.s0+p29.s1 + p30.s0+p30.s1+ p31.s0+p31.s1 + p32.s0+p32.s1 + p33.s0+p33.s1 + p34.s0
		 +p34.s1 + p35.s0+p35.s1 + p36.s0+p36.s1 + p37.s0+p37.s1 + p38.s0+p38.s1 + p39.s0+p39.s1+p40.s0+p40.s1;
}

__kernel void kernel_ceil_withoutDD4(__global float*result_ceil, int n)
{
  float4 p1 = 1.23+(float4)(0);
  float4 p2 = 1.23+(float4)(0);
  float4 p3 = 1.23+(float4)(0);
  float4 p4 = 1.23+(float4)(0);
  float4 p5 = 1.23+(float4)(0);
  float4 p6 = 1.23+(float4)(0);
  float4 p7 = 1.23+(float4)(0);
  float4 p8 = 1.23+(float4)(0);
  float4 p9 = 1.23+(float4)(0);
  float4 p10 = 1.23+(float4)(0);
  float4 p11 = 1.23+(float4)(0);
  float4 p12 = 1.23+(float4)(0);
  float4 p13 = 1.23+(float4)(0);
  float4 p14 = 1.23+(float4)(0);
  float4 p15 = 1.23+(float4)(0);
  float4 p16 = 1.23+(float4)(0);
  float4 p17 = 1.23+(float4)(0);
  float4 p18 = 1.23+(float4)(0);
  float4 p19 = 1.23+(float4)(0);
  float4 p20 = 1.23+(float4)(0);
  float4 p21 = 1.23+(float4)(0);
  float4 p22 = 1.23+(float4)(0);
  float4 p23 = 1.23+(float4)(0);
  float4 p24 = 1.23+(float4)(0);
  float4 p25 = 1.23+(float4)(0);
  float4 p26 = 1.23+(float4)(0);
  float4 p27 = 1.23+(float4)(0);
  float4 p28 = 1.23+(float4)(0);
  float4 p29 = 1.23+(float4)(0);
  float4 p30 = 1.23+(float4)(0);
  float4 p31 = 1.23+(float4)(0);
  float4 p32 = 1.23+(float4)(0);
  float4 p33 = 1.23+(float4)(0);
  float4 p34 = 1.23+(float4)(0);
  float4 p35 = 1.23+(float4)(0);
  float4 p36 = 1.23+(float4)(0);
  float4 p37 = 1.23+(float4)(0);
  float4 p38 = 1.23+(float4)(0);
  float4 p39 = 1.23+(float4)(0);
  float4 p40 = 1.23+(float4)(0);

  float4 i = 0.0+(float4)(0);
  float N = 16.0 * n;

  int j=0;
  for(j=0;j<N;j++,i=i+1) {
    p1 += ceil(i + 0.001);
    p2 += ceil(i + 0.002);
    p3 += ceil(i + 0.003);
    p4 += ceil(i + 0.005);
    p5 += ceil(i + 0.006);
    p6 += ceil(i + 0.007);
    p7 += ceil(i + 0.008);
    p8 += ceil(i + 0.009);
    p9 += ceil(i + 0.012);
    p10 += ceil(i + 0.031);
    p11 += ceil(i + 0.001);
    p12 += ceil(i + 0.002);
    p13 += ceil(i + 0.003);
    p14 += ceil(i + 0.005);
    p15 += ceil(i + 0.006);
    p16 += ceil(i + 0.007);
    p17 += ceil(i + 0.008);
    p18 += ceil(i + 0.009);
    p19 += ceil(i + 0.012);
    p20 += ceil(i + 0.031);
    p21 += ceil(i + 0.001);
    p22 += ceil(i + 0.002);
    p23 += ceil(i + 0.003);
    p24 += ceil(i + 0.005);
    p25 += ceil(i + 0.006);
    p26 += ceil(i + 0.007);
    p27 += ceil(i + 0.008);
    p28 += ceil(i + 0.009);
    p29 += ceil(i + 0.012);
    p30 += ceil(i + 0.031);
    p31 += ceil(i + 0.001);
    p32 += ceil(i + 0.002);
    p33 += ceil(i + 0.003);
    p34 += ceil(i + 0.005);
    p35 += ceil(i + 0.006);
    p36 += ceil(i + 0.007);
    p37 += ceil(i + 0.008);
    p38 += ceil(i + 0.009);
    p39 += ceil(i + 0.012);
    p40 += ceil(i + 0.031);
  }
  *result_ceil =p1.s0+p1.s1+p1.s2+p1.s3 + p2.s0+p2.s1+p2.s2+p2.s3 + p3.s0+p3.s1+p3.s2+p3.s3 + p4.s0+p4.s1+p4.s2+p4.s3 + p5.s0+p5.s1+p5.s2+p5.s3 + p6.s0+p6.s1+p6.s2+p6.s3 + p7.s0+p7.s1+p7.s2+p7.s3 + p8.s0+p8.s1+p8.s2+p8.s3 
                + p9.s0+p9.s1+p9.s2+p9.s3 + p10.s0+p10.s1+p10.s2+p10.s3 + p11.s0+p11.s1+p11.s2+p11.s3 + p12.s0+p12.s1+p12.s2+p12.s3 + p13.s0+p13.s1+p13.s2+p13.s3 + p14.s0+p14.s1+p14.s2+p14.s3 + p15.s0+p15.s1+p15.s2+p15.s3 
		+ p16.s0+p16.s1+p16.s2+p16.s3 + p17.s0+p17.s1+p17.s2+p17.s3 + p18.s0+p18.s1+p18.s2+p18.s3 + p19.s0+p19.s1+p19.s2+p19.s3 + p20.s0+p20.s1+p20.s2+p20.s3 + p21.s0+p21.s1+p21.s2+p21.s3 + p22.s0+p22.s1+p22.s2+p22.s3 
		+ p23.s0+p23.s1+p23.s2+p23.s3 + p24.s0+p24.s1+p24.s2+p24.s3 + p25.s0+p25.s1+p25.s2+p25.s3 + p26.s0+p26.s1+p26.s2+p26.s3 + p27.s0+p27.s1+p27.s2+p27.s3 + p28.s0+p28.s1+p28.s2+p28.s3 + p29.s0+p29.s1+p29.s2+p29.s3 
		+ p30.s0+p30.s1+p30.s2+p30.s3+p31.s0+p31.s1+p31.s2+p31.s3 + p32.s0+p32.s1+p32.s2+p32.s3 + p33.s0+p33.s1+p33.s2+p33.s3 + p34.s0+p34.s1+p34.s2+p34.s3 + p35.s0+p35.s1+p35.s2+p35.s3 + p36.s0+p36.s1+p36.s2+p36.s3 
		+ p37.s0+p37.s1+p37.s2+p37.s3 + p38.s0+p38.s1+p38.s2+p38.s3 + p39.s0+p39.s1+p39.s2+p39.s3 + p40.s0+p40.s1+p40.s2+p40.s3;
 }
__kernel void kernel_ceil_withoutDD8(__global float*result_ceil, int n)
{
  float8 p1 = 1.23+(float8)(0);
  float8 p2 = 1.23+(float8)(0);
  float8 p3 = 1.23+(float8)(0);
  float8 p4 = 1.23+(float8)(0);
  float8 p5 = 1.23+(float8)(0);
  float8 p6 = 1.23+(float8)(0);
  float8 p7 = 1.23+(float8)(0);
  float8 p8 = 1.23+(float8)(0);
  float8 p9 = 1.23+(float8)(0);
  float8 p10 = 1.23+(float8)(0);
  float8 p11 = 1.23+(float8)(0);
  float8 p12 = 1.23+(float8)(0);
  float8 p13 = 1.23+(float8)(0);
  float8 p14 = 1.23+(float8)(0);
  float8 p15 = 1.23+(float8)(0);
  float8 p16 = 1.23+(float8)(0);
  float8 p17 = 1.23+(float8)(0);
  float8 p18 = 1.23+(float8)(0);
  float8 p19 = 1.23+(float8)(0);
  float8 p20 = 1.23+(float8)(0);
  float8 p21 = 1.23+(float8)(0);
  float8 p22 = 1.23+(float8)(0);
  float8 p23 = 1.23+(float8)(0);
  float8 p24 = 1.23+(float8)(0);
  float8 p25 = 1.23+(float8)(0);
  float8 p26 = 1.23+(float8)(0);
  float8 p27 = 1.23+(float8)(0);
  float8 p28 = 1.23+(float8)(0);
  float8 p29 = 1.23+(float8)(0);
  float8 p30 = 1.23+(float8)(0);
  float8 p31 = 1.23+(float8)(0);
  float8 p32 = 1.23+(float8)(0);
  float8 p33 = 1.23+(float8)(0);
  float8 p34 = 1.23+(float8)(0);
  float8 p35 = 1.23+(float8)(0);
  float8 p36 = 1.23+(float8)(0);
  float8 p37 = 1.23+(float8)(0);
  float8 p38 = 1.23+(float8)(0);
  float8 p39 = 1.23+(float8)(0);
  float8 p40 = 1.23+(float8)(0);

  float8 i = 0.0+(float8)(0);

  float N = 8.0 * n;

  int j=0;
  for(j=0;j<N;j++,i=i+1) {
    p1 += ceil(i + 0.001);
    p2 += ceil(i + 0.002);
    p3 += ceil(i + 0.003);
    p4 += ceil(i + 0.005);
    p5 += ceil(i + 0.006);
    p6 += ceil(i + 0.007);
    p7 += ceil(i + 0.008);
    p8 += ceil(i + 0.009);
    p9 += ceil(i + 0.012);
    p10 += ceil(i + 0.031);
    p11 += ceil(i + 0.001);
    p12 += ceil(i + 0.002);
    p13 += ceil(i + 0.003);
    p14 += ceil(i + 0.005);
    p15 += ceil(i + 0.006);
    p16 += ceil(i + 0.007);
    p17 += ceil(i + 0.008);
    p18 += ceil(i + 0.009);
    p19 += ceil(i + 0.012);
    p20 += ceil(i + 0.031);
    p21 += ceil(i + 0.001);
    p22 += ceil(i + 0.002);
    p23 += ceil(i + 0.003);
    p24 += ceil(i + 0.005);
    p25 += ceil(i + 0.006);
    p26 += ceil(i + 0.007);
    p27 += ceil(i + 0.008);
    p28 += ceil(i + 0.009);
    p29 += ceil(i + 0.012);
    p30 += ceil(i + 0.031);
    p31 += ceil(i + 0.001);
    p32 += ceil(i + 0.002);
    p33 += ceil(i + 0.003);
    p34 += ceil(i + 0.005);
    p35 += ceil(i + 0.006);
    p36 += ceil(i + 0.007);
    p37 += ceil(i + 0.008);
    p38 += ceil(i + 0.009);
    p39 += ceil(i + 0.012);
    p40 += ceil(i + 0.031);
  }
  *result_ceil = p1.s0+p1.s1+p1.s2+p1.s3+p1.s4+p1.s5+p1.s6+p1.s7
  			  + p2.s0+p2.s1+p2.s2+p2.s3+p2.s4+p2.s5+p2.s6+p2.s7
  			  + p3.s0+p3.s1+p3.s2+p3.s3+p3.s4+p3.s5+p3.s6+p3.s7 
  			  + p4.s0+p4.s1+p4.s2+p4.s3+p4.s4+p4.s5+p4.s6+p4.s7 
  			  + p5.s0+p5.s1+p5.s2+p5.s3+p5.s4+p5.s5+p5.s6+p5.s7 
  			  + p6.s0+p6.s1+p6.s2+p6.s3+p6.s4+p6.s5+p6.s6+p6.s7 
  			  + p7.s0+p7.s1+p7.s2+p7.s3+p7.s4+p7.s5+p7.s6+p7.s7 
  			  + p8.s0+p8.s1+p8.s2+p8.s3+p8.s4+p8.s5+p8.s6+p8.s7 
  			  + p9.s0+p9.s1+p9.s2+p9.s3+p9.s4+p9.s5+p9.s6+p9.s7 
  			  + p10.s0+p10.s1+p10.s2+p10.s3+p10.s4+p10.s5+p10.s6+p10.s7 
  			  + p11.s0+p11.s1+p11.s2+p11.s3+p11.s4+p11.s5+p11.s6+p11.s7 
  			  + p12.s0+p12.s1+p12.s2+p12.s3+p12.s4+p12.s5+p12.s6+p12.s7 
  			  + p13.s0+p13.s1+p13.s2+p13.s3+p13.s4+p13.s5+p13.s6+p13.s7 
  			  + p14.s0+p14.s1+p14.s2+p14.s3+p14.s4+p14.s5+p14.s6+p14.s7 
  			  + p15.s0+p15.s1+p15.s2+p15.s3+p15.s4+p15.s5+p15.s6+p15.s7 
  			  + p16.s0+p16.s1+p16.s2+p16.s3+p16.s4+p16.s5+p16.s6+p16.s7 
  			  + p17.s0+p17.s1+p17.s2+p17.s3+p17.s4+p17.s5+p17.s6+p17.s7 
  			  + p18.s0+p18.s1+p18.s2+p18.s3+p18.s4+p18.s5+p18.s6+p18.s7 
  			  + p19.s0+p19.s1+p19.s2+p19.s3+p19.s4+p19.s5+p19.s6+p19.s7 
  			  + p20.s0+p20.s1+p20.s2+p20.s3+p20.s4+p20.s5+p20.s6+p20.s7 
  			  + p21.s0+p21.s1+p21.s2+p21.s3+p21.s4+p21.s5+p21.s6+p21.s7 
  			  + p22.s0+p22.s1+p22.s2+p22.s3+p22.s4+p22.s5+p22.s6+p22.s7 
  			  + p23.s0+p23.s1+p23.s2+p23.s3+p23.s4+p23.s5+p23.s6+p23.s7 
  			  + p24.s0+p24.s1+p24.s2+p24.s3+p24.s4+p24.s5+p24.s6+p24.s7 
  			  + p25.s0+p25.s1+p25.s2+p25.s3+p25.s4+p25.s5+p25.s6+p25.s7 
  			  + p26.s0+p26.s1+p26.s2+p26.s3+p26.s4+p26.s5+p26.s6+p26.s7 
  			  + p27.s0+p27.s1+p27.s2+p27.s3+p27.s4+p27.s5+p27.s6+p27.s7 
  			  + p28.s0+p28.s1+p28.s2+p28.s3+p28.s4+p28.s5+p28.s6+p28.s7 
  			  + p29.s0+p29.s1+p29.s2+p29.s3+p29.s4+p29.s5+p29.s6+p29.s7 
  			  + p30.s0+p30.s1+p30.s2+p30.s3+p30.s4+p30.s5+p30.s6+p30.s7
			  + p31.s0+p31.s1+p31.s2+p31.s3+p31.s4+p31.s5+p31.s6+p31.s7
  			  + p32.s0+p32.s1+p32.s2+p32.s3+p32.s4+p32.s5+p32.s6+p32.s7
  			  + p33.s0+p33.s1+p33.s2+p33.s3+p33.s4+p33.s5+p33.s6+p33.s7 
  			  + p34.s0+p34.s1+p34.s2+p34.s3+p34.s4+p34.s5+p34.s6+p34.s7 
  			  + p35.s0+p35.s1+p35.s2+p35.s3+p35.s4+p35.s5+p35.s6+p35.s7 
  			  + p36.s0+p36.s1+p36.s2+p36.s3+p36.s4+p36.s5+p36.s6+p36.s7 
  			  + p37.s0+p37.s1+p37.s2+p37.s3+p37.s4+p37.s5+p37.s6+p37.s7 
  			  + p38.s0+p38.s1+p38.s2+p38.s3+p38.s4+p38.s5+p38.s6+p38.s7 
  			  + p39.s0+p39.s1+p39.s2+p39.s3+p39.s4+p39.s5+p39.s6+p39.s7 
  			  + p40.s0+p40.s1+p40.s2+p40.s3+p40.s4+p40.s5+p40.s6+p40.s7;
 }

__kernel void kernel_ceil_withoutDD16(__global float*result_ceil, int n)
{
  float16 p1 = 1.23+(float16)(0);
  float16 p2 = 1.23+(float16)(0);
  float16 p3 = 1.23+(float16)(0);
  float16 p4 = 1.23+(float16)(0);
  float16 p5 = 1.23+(float16)(0);
  float16 p6 = 1.23+(float16)(0);
  float16 p7 = 1.23+(float16)(0);
  float16 p8 = 1.23+(float16)(0);
  float16 p9 = 1.23+(float16)(0);
  float16 p10 = 1.23+(float16)(0);
  float16 p11 = 1.23+(float16)(0);
  float16 p12 = 1.23+(float16)(0);
  float16 p13 = 1.23+(float16)(0);
  float16 p14 = 1.23+(float16)(0);
  float16 p15 = 1.23+(float16)(0);
  float16 p16 = 1.23+(float16)(0);
  float16 p17 = 1.23+(float16)(0);
  float16 p18 = 1.23+(float16)(0);
  float16 p19 = 1.23+(float16)(0);
  float16 p20 = 1.23+(float16)(0);
  float16 p21 = 1.23+(float16)(0);
  float16 p22 = 1.23+(float16)(0);
  float16 p23 = 1.23+(float16)(0);
  float16 p24 = 1.23+(float16)(0);
  float16 p25 = 1.23+(float16)(0);
  float16 p26 = 1.23+(float16)(0);
  float16 p27 = 1.23+(float16)(0);
  float16 p28 = 1.23+(float16)(0);
  float16 p29 = 1.23+(float16)(0);
  float16 p30 = 1.23+(float16)(0);
  float16 p31 = 1.23+(float16)(0);
  float16 p32 = 1.23+(float16)(0);
  float16 p33 = 1.23+(float16)(0);
  float16 p34 = 1.23+(float16)(0);
  float16 p35 = 1.23+(float16)(0);
  float16 p36 = 1.23+(float16)(0);
  float16 p37 = 1.23+(float16)(0);
  float16 p38 = 1.23+(float16)(0);
  float16 p39 = 1.23+(float16)(0);
  float16 p40 = 1.23+(float16)(0);

  float16 i = 0.0+(float16)(0);
  			  
  float N = 2.0 * n;

  int j=0;
  for(j=0;j<N;j++,i=i+1) {
    p1 += ceil(i + 0.001);
    p2 += ceil(i + 0.002);
    p3 += ceil(i + 0.003);
    p4 += ceil(i + 0.005);
    p5 += ceil(i + 0.006);
    p6 += ceil(i + 0.007);
    p7 += ceil(i + 0.008);
    p8 += ceil(i + 0.009);
    p9 += ceil(i + 0.012);
    p10 += ceil(i + 0.031);
    p11 += ceil(i + 0.001);
    p12 += ceil(i + 0.002);
    p13 += ceil(i + 0.003);
    p14 += ceil(i + 0.005);
    p15 += ceil(i + 0.006);
    p16 += ceil(i + 0.007);
    p17 += ceil(i + 0.008);
    p18 += ceil(i + 0.009);
    p19 += ceil(i + 0.012);
    p20 += ceil(i + 0.031);
    p21 += ceil(i + 0.001);
    p22 += ceil(i + 0.002);
    p23 += ceil(i + 0.003);
    p24 += ceil(i + 0.005);
    p25 += ceil(i + 0.006);
    p26 += ceil(i + 0.007);
    p27 += ceil(i + 0.008);
    p28 += ceil(i + 0.009);
    p29 += ceil(i + 0.012);
    p30 += ceil(i + 0.031);
    p31 += ceil(i + 0.001);
    p32 += ceil(i + 0.002);
    p33 += ceil(i + 0.003);
    p34 += ceil(i + 0.005);
    p35 += ceil(i + 0.006);
    p36 += ceil(i + 0.007);
    p37 += ceil(i + 0.008);
    p38 += ceil(i + 0.009);
    p39 += ceil(i + 0.012);
    p40 += ceil(i + 0.031);
  }
  *result_ceil = p1.s0+p1.s1+p1.s2+p1.s3+p1.s4+p1.s5+p1.s6+p1.s7+p1.s8+p1.s9+p1.sa+p1.sb+p1.sc+p1.sd+p1.se+p1.sf
  			  + p2.s0+p2.s1+p2.s2+p2.s3+p2.s4+p2.s5+p2.s6+p2.s7+p2.s8+p2.s9+p2.sa+p2.sb+p2.sc+p2.sd+p2.se+p2.sf
  			  + p3.s0+p3.s1+p3.s2+p3.s3+p3.s4+p3.s5+p3.s6+p3.s7+p3.s8+p3.s9+p3.sa+p3.sb+p3.sc+p3.sd+p3.se+p3.sf
  			  + p4.s0+p4.s1+p4.s2+p4.s3+p4.s4+p4.s5+p4.s6+p4.s7+p4.s8+p4.s9+p4.sa+p4.sb+p4.sc+p4.sd+p4.se+p4.sf 
  			  + p5.s0+p5.s1+p5.s2+p5.s3+p5.s4+p5.s5+p5.s6+p5.s7+p5.s8+p5.s9+p5.sa+p5.sb+p5.sc+p5.sd+p5.se+p5.sf 
  			  + p6.s0+p6.s1+p6.s2+p6.s3+p6.s4+p6.s5+p6.s6+p6.s7+p6.s8+p6.s9+p6.sa+p6.sb+p6.sc+p6.sd+p6.se+p6.sf 
  			  + p7.s0+p7.s1+p7.s2+p7.s3+p7.s4+p7.s5+p7.s6+p7.s7+p7.s8+p7.s9+p7.sa+p7.sb+p7.sc+p7.sd+p7.se+p7.sf 
  			  + p8.s0+p8.s1+p8.s2+p8.s3+p8.s4+p8.s5+p8.s6+p8.s7+p8.s8+p8.s9+p8.sa+p8.sb+p8.sc+p8.sd+p8.se+p8.sf 
  			  + p9.s0+p9.s1+p9.s2+p9.s3+p9.s4+p9.s5+p9.s6+p9.s7+p9.s8+p9.s9+p9.sa+p9.sb+p9.sc+p9.sd+p9.se+p9.sf 
  			  + p10.s0+p10.s1+p10.s2+p10.s3+p10.s4+p10.s5+p10.s6+p10.s7+p10.s8+p10.s9+p10.sa+p10.sb+p10.sc+p10.sd+p10.se+p10.sf 
  			  + p11.s0+p11.s1+p11.s2+p11.s3+p11.s4+p11.s5+p11.s6+p11.s7+p11.s8+p11.s9+p11.sa+p11.sb+p11.sc+p11.sd+p11.se+p11.sf 
  			  + p12.s0+p12.s1+p12.s2+p12.s3+p12.s4+p12.s5+p12.s6+p12.s7+p12.s8+p12.s9+p12.sa+p12.sb+p12.sc+p12.sd+p12.se+p12.sf 
  			  + p13.s0+p13.s1+p13.s2+p13.s3+p13.s4+p13.s5+p13.s6+p13.s7+p13.s8+p13.s9+p13.sa+p13.sb+p13.sc+p13.sd+p13.se+p13.sf 
  			  + p14.s0+p14.s1+p14.s2+p14.s3+p14.s4+p14.s5+p14.s6+p14.s7+p14.s8+p14.s9+p14.sa+p14.sb+p14.sc+p14.sd+p14.se+p14.sf 
  			  + p15.s0+p15.s1+p15.s2+p15.s3+p15.s4+p15.s5+p15.s6+p15.s7+p15.s8+p15.s9+p15.sa+p15.sb+p15.sc+p15.sd+p15.se+p15.sf 
  			  + p16.s0+p16.s1+p16.s2+p16.s3+p16.s4+p16.s5+p16.s6+p16.s7+p16.s8+p16.s9+p16.sa+p16.sb+p16.sc+p16.sd+p16.se+p16.sf 
  			  + p17.s0+p17.s1+p17.s2+p17.s3+p17.s4+p17.s5+p17.s6+p17.s7+p17.s8+p17.s9+p17.sa+p17.sb+p17.sc+p17.sd+p17.se+p17.sf 
  			  + p18.s0+p18.s1+p18.s2+p18.s3+p18.s4+p18.s5+p18.s6+p18.s7+p18.s8+p18.s9+p18.sa+p18.sb+p18.sc+p18.sd+p18.se+p18.sf 
  			  + p19.s0+p19.s1+p19.s2+p19.s3+p19.s4+p19.s5+p19.s6+p19.s7+p19.s8+p19.s9+p19.sa+p19.sb+p19.sc+p19.sd+p19.se+p19.sf 
  			  + p20.s0+p20.s1+p20.s2+p20.s3+p20.s4+p20.s5+p20.s6+p20.s7+p20.s8+p20.s9+p20.sa+p20.sb+p20.sc+p20.sd+p20.se+p20.sf 
  			  + p21.s0+p21.s1+p21.s2+p21.s3+p21.s4+p21.s5+p21.s6+p21.s7+p21.s8+p21.s9+p21.sa+p21.sb+p21.sc+p21.sd+p21.se+p21.sf 
  			  + p22.s0+p22.s1+p22.s2+p22.s3+p22.s4+p22.s5+p22.s6+p22.s7+p22.s8+p22.s9+p22.sa+p22.sb+p22.sc+p22.sd+p22.se+p22.sf 
  			  + p23.s0+p23.s1+p23.s2+p23.s3+p23.s4+p23.s5+p23.s6+p23.s7+p23.s8+p23.s9+p23.sa+p23.sb+p23.sc+p23.sd+p23.se+p23.sf 
  			  + p24.s0+p24.s1+p24.s2+p24.s3+p24.s4+p24.s5+p24.s6+p24.s7+p24.s8+p24.s9+p24.sa+p24.sb+p24.sc+p24.sd+p24.se+p24.sf 
  			  + p25.s0+p25.s1+p25.s2+p25.s3+p25.s4+p25.s5+p25.s6+p25.s7+p25.s8+p25.s9+p25.sa+p25.sb+p25.sc+p25.sd+p25.se+p25.sf 
  			  + p26.s0+p26.s1+p26.s2+p26.s3+p26.s4+p26.s5+p26.s6+p26.s7+p26.s8+p26.s9+p26.sa+p26.sb+p26.sc+p26.sd+p26.se+p26.sf 
  			  + p27.s0+p27.s1+p27.s2+p27.s3+p27.s4+p27.s5+p27.s6+p27.s7+p27.s8+p27.s9+p27.sa+p27.sb+p27.sc+p27.sd+p27.se+p27.sf 
  			  + p28.s0+p28.s1+p28.s2+p28.s3+p28.s4+p28.s5+p28.s6+p28.s7+p28.s8+p28.s9+p28.sa+p28.sb+p28.sc+p28.sd+p28.se+p28.sf 
  			  + p29.s0+p29.s1+p29.s2+p29.s3+p29.s4+p29.s5+p29.s6+p29.s7+p29.s8+p29.s9+p29.sa+p29.sb+p29.sc+p29.sd+p29.se+p29.sf 
  			  + p30.s0+p30.s1+p30.s2+p30.s3+p30.s4+p30.s5+p30.s6+p30.s7+p30.s8+p30.s9+p30.sa+p30.sb+p30.sc+p30.sd+p30.se+p30.sf
			  + p31.s0+p31.s1+p31.s2+p31.s3+p31.s4+p31.s5+p31.s6+p31.s7+p31.s8+p31.s9+p31.sa+p31.sb+p31.sc+p31.sd+p31.se+p31.sf
  			  + p32.s0+p32.s1+p32.s2+p32.s3+p32.s4+p32.s5+p32.s6+p32.s7+p32.s8+p32.s9+p32.sa+p32.sb+p32.sc+p32.sd+p32.se+p32.sf
  			  + p33.s0+p33.s1+p33.s2+p33.s3+p33.s4+p33.s5+p33.s6+p33.s7+p33.s8+p33.s9+p33.sa+p33.sb+p33.sc+p33.sd+p33.se+p33.sf
  			  + p34.s0+p34.s1+p34.s2+p34.s3+p34.s4+p34.s5+p34.s6+p34.s7+p34.s8+p34.s9+p34.sa+p34.sb+p34.sc+p34.sd+p34.se+p34.sf 
  			  + p35.s0+p35.s1+p35.s2+p35.s3+p35.s4+p35.s5+p35.s6+p35.s7+p35.s8+p35.s9+p35.sa+p35.sb+p35.sc+p35.sd+p35.se+p35.sf 
  			  + p36.s0+p36.s1+p36.s2+p36.s3+p36.s4+p36.s5+p36.s6+p36.s7+p36.s8+p36.s9+p36.sa+p36.sb+p36.sc+p36.sd+p36.se+p36.sf 
  			  + p37.s0+p37.s1+p37.s2+p37.s3+p37.s4+p37.s5+p37.s6+p37.s7+p37.s8+p37.s9+p37.sa+p37.sb+p37.sc+p37.sd+p37.se+p37.sf 
  			  + p38.s0+p38.s1+p38.s2+p38.s3+p38.s4+p38.s5+p38.s6+p38.s7+p38.s8+p38.s9+p38.sa+p38.sb+p38.sc+p38.sd+p38.se+p38.sf 
  			  + p39.s0+p39.s1+p39.s2+p39.s3+p39.s4+p39.s5+p39.s6+p39.s7+p39.s8+p39.s9+p39.sa+p39.sb+p39.sc+p39.sd+p39.se+p39.sf 
			  + p40.s0+p40.s1+p40.s2+p40.s3+p40.s4+p40.s5+p40.s6+p40.s7+p40.s8+p40.s9+p40.sa+p40.sb+p40.sc+p40.sd+p40.se+p40.sf;
}

__kernel void kernel_copysign_withDD1(__global float* result_copysign, int N)
{
  float p1 = 1.2;
  float p2 = -3.4;
  float p3 = 0.0;
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat256(p3 += copysign(p1, p2); p2 += copysign(p2, p1); p1 += copysign(p2, p3););
  }
  *result_copysign = p1 + p2 + p3;
}

__kernel void kernel_copysign_withDD2(__global float* result_copysign, int N)
{
  float2 p1 = 1.2+(float2)(0);
  float2 p2 = -3.4+(float2)(0);
  float2 p3 = 0.0+(float2)(0);
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat256(p3 += copysign(p1, p2); p2 += copysign(p2, p1); p1 += copysign(p2, p3););
  }
  *result_copysign = p1.s0 + p1.s1 + p2.s0 + p2.s1 + p3.s0 + p3.s1;
}

__kernel void kernel_copysign_withDD4(__global float* result_copysign, int N)
{
  float4 p1 = 1.2+(float4)(0);
  float4 p2 = -3.4+(float4)(0);
  float4 p3 = 0.0+(float4)(0);
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat256(p3 += copysign(p1, p2); p2 += copysign(p2, p1); p1 += copysign(p2, p3););
  }
  *result_copysign = p1.s0 + p1.s1 + p1.s2 + p1.s3+p2.s0 + p2.s1 + p2.s2 + p2.s3+p3.s0 + p3.s1 + p3.s2 + p3.s3;
}

__kernel void kernel_copysign_withDD8(__global float* result_copysign, int N)
{
  float8 p1 = 1.2+(float8)(0);
  float8 p2 = -3.4+(float8)(0);
  float8 p3 = 0.0+(float8)(0);
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat256(p3 += copysign(p1, p2); p2 += copysign(p2, p1); p1 += copysign(p2, p3););
  }
  *result_copysign =p1.s0+p1.s1+p1.s2+p1.s3+p1.s4+p1.s5+p1.s6+p1.s7
  			  + p2.s0+p2.s1+p2.s2+p2.s3+p2.s4+p2.s5+p2.s6+p2.s7
  			  + p3.s0+p3.s1+p3.s2+p3.s3+p3.s4+p3.s5+p3.s6+p3.s7;
}

__kernel void kernel_copysign_withDD16(__global float* result_copysign, int N)
{
  float16 p1 = 1.2+(float16)(0);
  float16 p2 = -3.4+(float16)(0);
  float16 p3 = 0.0+(float16)(0); 
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat256(p3 += copysign(p1, p2); p2 += copysign(p2, p1); p1 += copysign(p2, p3););
  }
  *result_copysign =  p1.s0+p1.s1+p1.s2+p1.s3+p1.s4+p1.s5+p1.s6+p1.s7+p1.s8+p1.s9+p1.sa+p1.sb+p1.sc+p1.sd+p1.se+p1.sf
  			  + p2.s0+p2.s1+p2.s2+p2.s3+p2.s4+p2.s5+p2.s6+p2.s7+p2.s8+p2.s9+p2.sa+p2.sb+p2.sc+p2.sd+p2.se+p2.sf
  			  + p3.s0+p3.s1+p3.s2+p3.s3+p3.s4+p3.s5+p3.s6+p3.s7+p3.s8+p3.s9+p3.sa+p3.sb+p3.sc+p3.sd+p3.se+p3.sf;
}

__kernel void kernel_copysign_withoutDD1(__global float* result_copysign, int n)
{
  float p1 = 1.2;
  float p2 = 1.2;
  float p3 = 1.2;
  float p4 = 1.2;
  float p5 = 1.2;
  float p6 = 1.2;
  float p7 = 1.2;
  float p8 = 1.2;
  float p9 = 1.2;
  float p10 = 1.2;
  float p11 = 1.2;
  float p12 = 1.2;
  float p13 = 1.2;
  float p14 = 1.2;
  float p15 = 1.2;
  float p16 = 1.2;
  float p17 = 1.2;
  float p18 = 1.2;
  float p19 = 1.2;
  float p20 = 1.2;
  float p21 = 1.2;
  float p22 = 1.2;
  float p23 = 1.2;
  float p24 = 1.2;
  float p25 = 1.2;
  float p26 = 1.2;
  float p27 = 1.2;
  float p28 = 1.2;
  float p29 = 1.2;
  float p30 = 1.2;

  float i = 1.0;
  float j = 2.2;
  float N = 100.0 * (float)(n);

  for(i = 1.0; i < N; i = i + 1.0) {
    p1 += copysign(i - 345, j);
    p2 += copysign(i - 234, j);
    p3 += copysign(i - 23, j);
    p4 += copysign(i - 24, j);
    p5 += copysign(i - 25, j);
    p6 += copysign(i - 64, j);
    p7 += copysign(i - 57, j);
    p8 += copysign(i - 22, j);
    p9 += copysign(i - 256, j);
    p10 += copysign(i - 46, j);
    p11 += copysign(i - 345, j);
    p12 += copysign(i - 234, j);
    p13 += copysign(i - 23, j);
    p14 += copysign(i - 24, j);
    p15 += copysign(i - 25, j);
    p16 += copysign(i - 64, j);
    p17 += copysign(i - 57, j);
    p18 += copysign(i - 22, j);
    p19 += copysign(i - 256, j);
    p20 += copysign(i - 46, j);
    p21 += copysign(i - 345, j);
    p22 += copysign(i - 234, j);
    p23 += copysign(i - 23, j);
    p24 += copysign(i - 24, j);
    p25 += copysign(i - 25, j);
    p26 += copysign(i - 64, j);
    p27 += copysign(i - 57, j);
    p28 += copysign(i - 22, j);
    p29 += copysign(i - 256, j);
    p30 += copysign(i - 46, j);
  }
  *result_copysign = p1 + p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9 + p10 + p11 + p12 + p13 + p14 + p15 + p16 + p17 + p18 + p19 + p20 + p21 + p22 + p23 + p24 + p25 + p26 + p27 + p28 + p29 + p30;
}

__kernel void kernel_copysign_withoutDD2(__global float* result_copysign, int n)
{
  float2 p1 = 1.2+(float2)(0);
  float2 p2 = 1.2+(float2)(0);
  float2 p3 = 1.2+(float2)(0);
  float2 p4 = 1.2+(float2)(0);
  float2 p5 = 1.2+(float2)(0);
  float2 p6 = 1.2+(float2)(0);
  float2 p7 = 1.2+(float2)(0);
  float2 p8 = 1.2+(float2)(0);
  float2 p9 = 1.2+(float2)(0);
  float2 p10 = 1.2+(float2)(0);
  float2 p11 = 1.2+(float2)(0);
  float2 p12 = 1.2+(float2)(0);
  float2 p13 = 1.2+(float2)(0);
  float2 p14 = 1.2+(float2)(0);
  float2 p15 = 1.2+(float2)(0);
  float2 p16 = 1.2+(float2)(0);
  float2 p17 = 1.2+(float2)(0);
  float2 p18 = 1.2+(float2)(0);
  float2 p19 = 1.2+(float2)(0);
  float2 p20 = 1.2+(float2)(0);
  float2 p21 = 1.2+(float2)(0);
  float2 p22 = 1.2+(float2)(0);
  float2 p23 = 1.2+(float2)(0);
  float2 p24 = 1.2+(float2)(0);
  float2 p25 = 1.2+(float2)(0);
  float2 p26 = 1.2+(float2)(0);
  float2 p27 = 1.2+(float2)(0);
  float2 p28 = 1.2+(float2)(0);
  float2 p29 = 1.2+(float2)(0);
  float2 p30 = 1.2+(float2)(0);

  float2 i = 1.0+(float2)(0);
  float2 j = 2.2+(float2)(0);
  float N = 100.0 * (float)(n);

  int k;
  for(k = 1; k < N;k++,i=i+1 ) {
    p1 += copysign(i - 345, j);
    p2 += copysign(i - 234, j);
    p3 += copysign(i - 23, j);
    p4 += copysign(i - 24, j);
    p5 += copysign(i - 25, j);
    p6 += copysign(i - 64, j);
    p7 += copysign(i - 57, j);
    p8 += copysign(i - 22, j);
    p9 += copysign(i - 256, j);
    p10 += copysign(i - 46, j);
    p11 += copysign(i - 345, j);
    p12 += copysign(i - 234, j);
    p13 += copysign(i - 23, j);
    p14 += copysign(i - 24, j);
    p15 += copysign(i - 25, j);
    p16 += copysign(i - 64, j);
    p17 += copysign(i - 57, j);
    p18 += copysign(i - 22, j);
    p19 += copysign(i - 256, j);
    p20 += copysign(i - 46, j);
    p21 += copysign(i - 345, j);
    p22 += copysign(i - 234, j);
    p23 += copysign(i - 23, j);
    p24 += copysign(i - 24, j);
    p25 += copysign(i - 25, j);
    p26 += copysign(i - 64, j);
    p27 += copysign(i - 57, j);
    p28 += copysign(i - 22, j);
    p29 += copysign(i - 256, j);
    p30 += copysign(i - 46, j);
  }
  *result_copysign = p1.s0+p1.s1 + p2.s0+p2.s1 + p3.s0+p3.s1 + p4.s0+p4.s1 + p5.s0+p5.s1 + p6.s0+p6.s1 + p7.s0+p7.s1 + p8.s0+p8.s1 + p9.s0+p9.s1+ p10.s0+p10.s1 + p11.s0+p11.s1 + p12.s0+p12.s1+ p13.s0+p13.s1 + p14.s0+p14.s1 + p15.s0+p15.s1+ p16.s0+p16.s1+ p17.s0+p17.s1 + p18.s0+p18.s1 + p19.s0+p19.s1+ p20.s0+p20.s1+ p21.s0+p21.s1 + p22.s0+p22.s1 + p23.s0+p23.s1 + p24.s0+p24.s1 + p25.s0+p25.s1 + p26.s0+p26.s1 + p27.s0+p27.s1 + p28.s0+p28.s1 + p29.s0+p29.s1 + p30.s0+p30.s1;
}

__kernel void kernel_copysign_withoutDD4(__global float* result_copysign, int n)
{
  float4 p1 = 1.2+(float4)(0);
  float4 p2 = 1.2+(float4)(0);
  float4 p3 = 1.2+(float4)(0);
  float4 p4 = 1.2+(float4)(0);
  float4 p5 = 1.2+(float4)(0);
  float4 p6 = 1.2+(float4)(0);
  float4 p7 = 1.2+(float4)(0);
  float4 p8 = 1.2+(float4)(0);
  float4 p9 = 1.2+(float4)(0);
  float4 p10 = 1.2+(float4)(0);
  float4 p11 = 1.2+(float4)(0);
  float4 p12 = 1.2+(float4)(0);
  float4 p13 = 1.2+(float4)(0);
  float4 p14 = 1.2+(float4)(0);
  float4 p15 = 1.2+(float4)(0);
  float4 p16 = 1.2+(float4)(0);
  float4 p17 = 1.2+(float4)(0);
  float4 p18 = 1.2+(float4)(0);
  float4 p19 = 1.2+(float4)(0);
  float4 p20 = 1.2+(float4)(0);
  float4 p21 = 1.2+(float4)(0);
  float4 p22 = 1.2+(float4)(0);
  float4 p23 = 1.2+(float4)(0);
  float4 p24 = 1.2+(float4)(0);
  float4 p25 = 1.2+(float4)(0);
  float4 p26 = 1.2+(float4)(0);
  float4 p27 = 1.2+(float4)(0);
  float4 p28 = 1.2+(float4)(0);
  float4 p29 = 1.2+(float4)(0);
  float4 p30 = 1.2+(float4)(0);

  float4 i = 1.0+(float4)(0);
  float4 j = 2.2+(float4)(0);
  float N = 25.0 * (float)(n);

  int k;
  for(k = 1; k < N;k++,i=i+1 ) {
    p1 += copysign(i - 345, j);
    p2 += copysign(i - 234, j);
    p3 += copysign(i - 23, j);
    p4 += copysign(i - 24, j);
    p5 += copysign(i - 25, j);
    p6 += copysign(i - 64, j);
    p7 += copysign(i - 57, j);
    p8 += copysign(i - 22, j);
    p9 += copysign(i - 256, j);
    p10 += copysign(i - 46, j);
    p11 += copysign(i - 345, j);
    p12 += copysign(i - 234, j);
    p13 += copysign(i - 23, j);
    p14 += copysign(i - 24, j);
    p15 += copysign(i - 25, j);
    p16 += copysign(i - 64, j);
    p17 += copysign(i - 57, j);
    p18 += copysign(i - 22, j);
    p19 += copysign(i - 256, j);
    p20 += copysign(i - 46, j);
    p21 += copysign(i - 345, j);
    p22 += copysign(i - 234, j);
    p23 += copysign(i - 23, j);
    p24 += copysign(i - 24, j);
    p25 += copysign(i - 25, j);
    p26 += copysign(i - 64, j);
    p27 += copysign(i - 57, j);
    p28 += copysign(i - 22, j);
    p29 += copysign(i - 256, j);
    p30 += copysign(i - 46, j);
  }
  *result_copysign = p1.s0+p1.s1+p1.s2+p1.s3 + p2.s0+p2.s1+p2.s2+p2.s3 + p3.s0+p3.s1+p3.s2+p3.s3 + p4.s0+p4.s1+p4.s2+p4.s3 + p5.s0+p5.s1+p5.s2+p5.s3 + p6.s0+p6.s1+p6.s2+p6.s3 + p7.s0+p7.s1+p7.s2+p7.s3 + p8.s0+p8.s1+p8.s2+p8.s3 + p9.s0+p9.s1+p9.s2+p9.s3 + p10.s0+p10.s1+p10.s2+p10.s3 + p11.s0+p11.s1+p11.s2+p11.s3 + p12.s0+p12.s1+p12.s2+p12.s3 + p13.s0+p13.s1+p13.s2+p13.s3 + p14.s0+p14.s1+p14.s2+p14.s3 + p15.s0+p15.s1+p15.s2+p15.s3 + p16.s0+p16.s1+p16.s2+p16.s3 + p17.s0+p17.s1+p17.s2+p17.s3 + p18.s0+p18.s1+p18.s2+p18.s3 + p19.s0+p19.s1+p19.s2+p19.s3 + p20.s0+p20.s1+p20.s2+p20.s3 + p21.s0+p21.s1+p21.s2+p21.s3 + p22.s0+p22.s1+p22.s2+p22.s3 + p23.s0+p23.s1+p23.s2+p23.s3 + p24.s0+p24.s1+p24.s2+p24.s3 + p25.s0+p25.s1+p25.s2+p25.s3 + p26.s0+p26.s1+p26.s2+p26.s3 + p27.s0+p27.s1+p27.s2+p27.s3 + p28.s0+p28.s1+p28.s2+p28.s3 + p29.s0+p29.s1+p29.s2+p29.s3 + p30.s0+p30.s1+p30.s2+p30.s3;
}

__kernel void kernel_copysign_withoutDD8(__global float* result_copysign, int n)
{
  float8 p1 = 1.2+(float8)(0);
  float8 p2 = 1.2+(float8)(0);
  float8 p3 = 1.2+(float8)(0);
  float8 p4 = 1.2+(float8)(0);
  float8 p5 = 1.2+(float8)(0);
  float8 p6 = 1.2+(float8)(0);
  float8 p7 = 1.2+(float8)(0);
  float8 p8 = 1.2+(float8)(0);
  float8 p9 = 1.2+(float8)(0);
  float8 p10 = 1.2+(float8)(0);
  float8 p11 = 1.2+(float8)(0);
  float8 p12 = 1.2+(float8)(0);
  float8 p13 = 1.2+(float8)(0);
  float8 p14 = 1.2+(float8)(0);
  float8 p15 = 1.2+(float8)(0);
  float8 p16 = 1.2+(float8)(0);
  float8 p17 = 1.2+(float8)(0);
  float8 p18 = 1.2+(float8)(0);
  float8 p19 = 1.2+(float8)(0);
  float8 p20 = 1.2+(float8)(0);
  float8 p21 = 1.2+(float8)(0);
  float8 p22 = 1.2+(float8)(0);
  float8 p23 = 1.2+(float8)(0);
  float8 p24 = 1.2+(float8)(0);
  float8 p25 = 1.2+(float8)(0);
  float8 p26 = 1.2+(float8)(0);
  float8 p27 = 1.2+(float8)(0);
  float8 p28 = 1.2+(float8)(0);
  float8 p29 = 1.2+(float8)(0);
  float8 p30 = 1.2+(float8)(0);

  float8 i = 1.0+(float8)(0);
  float8 j = 2.2+(float8)(0);
  float N = 6 * (float)(n);

  int k;
  for(k = 1; k < N;k++,i=i+1 ) {
    p1 += copysign(i - 345, j);
    p2 += copysign(i - 234, j);
    p3 += copysign(i - 23, j);
    p4 += copysign(i - 24, j);
    p5 += copysign(i - 25, j);
    p6 += copysign(i - 64, j);
    p7 += copysign(i - 57, j);
    p8 += copysign(i - 22, j);
    p9 += copysign(i - 256, j);
    p10 += copysign(i - 46, j);
    p11 += copysign(i - 345, j);
    p12 += copysign(i - 234, j);
    p13 += copysign(i - 23, j);
    p14 += copysign(i - 24, j);
    p15 += copysign(i - 25, j);
    p16 += copysign(i - 64, j);
    p17 += copysign(i - 57, j);
    p18 += copysign(i - 22, j);
    p19 += copysign(i - 256, j);
    p20 += copysign(i - 46, j);
    p21 += copysign(i - 345, j);
    p22 += copysign(i - 234, j);
    p23 += copysign(i - 23, j);
    p24 += copysign(i - 24, j);
    p25 += copysign(i - 25, j);
    p26 += copysign(i - 64, j);
    p27 += copysign(i - 57, j);
    p28 += copysign(i - 22, j);
    p29 += copysign(i - 256, j);
    p30 += copysign(i - 46, j);
  }
  *result_copysign = p1.s0+p1.s1+p1.s2+p1.s3+p1.s4+p1.s5+p1.s6+p1.s7
  			  + p2.s0+p2.s1+p2.s2+p2.s3+p2.s4+p2.s5+p2.s6+p2.s7
  			  + p3.s0+p3.s1+p3.s2+p3.s3+p3.s4+p3.s5+p3.s6+p3.s7 
  			  + p4.s0+p4.s1+p4.s2+p4.s3+p4.s4+p4.s5+p4.s6+p4.s7 
  			  + p5.s0+p5.s1+p5.s2+p5.s3+p5.s4+p5.s5+p5.s6+p5.s7 
  			  + p6.s0+p6.s1+p6.s2+p6.s3+p6.s4+p6.s5+p6.s6+p6.s7 
  			  + p7.s0+p7.s1+p7.s2+p7.s3+p7.s4+p7.s5+p7.s6+p7.s7 
  			  + p8.s0+p8.s1+p8.s2+p8.s3+p8.s4+p8.s5+p8.s6+p8.s7 
  			  + p9.s0+p9.s1+p9.s2+p9.s3+p9.s4+p9.s5+p9.s6+p9.s7 
  			  + p10.s0+p10.s1+p10.s2+p10.s3+p10.s4+p10.s5+p10.s6+p10.s7 
  			  + p11.s0+p11.s1+p11.s2+p11.s3+p11.s4+p11.s5+p11.s6+p11.s7 
  			  + p12.s0+p12.s1+p12.s2+p12.s3+p12.s4+p12.s5+p12.s6+p12.s7 
  			  + p13.s0+p13.s1+p13.s2+p13.s3+p13.s4+p13.s5+p13.s6+p13.s7 
  			  + p14.s0+p14.s1+p14.s2+p14.s3+p14.s4+p14.s5+p14.s6+p14.s7 
  			  + p15.s0+p15.s1+p15.s2+p15.s3+p15.s4+p15.s5+p15.s6+p15.s7 
  			  + p16.s0+p16.s1+p16.s2+p16.s3+p16.s4+p16.s5+p16.s6+p16.s7 
  			  + p17.s0+p17.s1+p17.s2+p17.s3+p17.s4+p17.s5+p17.s6+p17.s7 
  			  + p18.s0+p18.s1+p18.s2+p18.s3+p18.s4+p18.s5+p18.s6+p18.s7 
  			  + p19.s0+p19.s1+p19.s2+p19.s3+p19.s4+p19.s5+p19.s6+p19.s7 
  			  + p20.s0+p20.s1+p20.s2+p20.s3+p20.s4+p20.s5+p20.s6+p20.s7 
  			  + p21.s0+p21.s1+p21.s2+p21.s3+p21.s4+p21.s5+p21.s6+p21.s7 
  			  + p22.s0+p22.s1+p22.s2+p22.s3+p22.s4+p22.s5+p22.s6+p22.s7 
  			  + p23.s0+p23.s1+p23.s2+p23.s3+p23.s4+p23.s5+p23.s6+p23.s7 
  			  + p24.s0+p24.s1+p24.s2+p24.s3+p24.s4+p24.s5+p24.s6+p24.s7 
  			  + p25.s0+p25.s1+p25.s2+p25.s3+p25.s4+p25.s5+p25.s6+p25.s7 
  			  + p26.s0+p26.s1+p26.s2+p26.s3+p26.s4+p26.s5+p26.s6+p26.s7 
  			  + p27.s0+p27.s1+p27.s2+p27.s3+p27.s4+p27.s5+p27.s6+p27.s7 
  			  + p28.s0+p28.s1+p28.s2+p28.s3+p28.s4+p28.s5+p28.s6+p28.s7 
  			  + p29.s0+p29.s1+p29.s2+p29.s3+p29.s4+p29.s5+p29.s6+p29.s7 
  			  + p30.s0+p30.s1+p30.s2+p30.s3+p30.s4+p30.s5+p30.s6+p30.s7;
}

__kernel void kernel_copysign_withoutDD16(__global float* result_copysign, int n)
{
  float16 p1 = 1.2+(float16)(0);
  float16 p2 = 1.2+(float16)(0);
  float16 p3 = 1.2+(float16)(0);
  float16 p4 = 1.2+(float16)(0);
  float16 p5 = 1.2+(float16)(0);
  float16 p6 = 1.2+(float16)(0);
  float16 p7 = 1.2+(float16)(0);
  float16 p8 = 1.2+(float16)(0);
  float16 p9 = 1.2+(float16)(0);
  float16 p10 = 1.2+(float16)(0);
  float16 p11 = 1.2+(float16)(0);
  float16 p12 = 1.2+(float16)(0);
  float16 p13 = 1.2+(float16)(0);
  float16 p14 = 1.2+(float16)(0);
  float16 p15 = 1.2+(float16)(0);
  float16 p16 = 1.2+(float16)(0);
  float16 p17 = 1.2+(float16)(0);
  float16 p18 = 1.2+(float16)(0);
  float16 p19 = 1.2+(float16)(0);
  float16 p20 = 1.2+(float16)(0);
  float16 p21 = 1.2+(float16)(0);
  float16 p22 = 1.2+(float16)(0);
  float16 p23 = 1.2+(float16)(0);
  float16 p24 = 1.2+(float16)(0);
  float16 p25 = 1.2+(float16)(0);
  float16 p26 = 1.2+(float16)(0);
  float16 p27 = 1.2+(float16)(0);
  float16 p28 = 1.2+(float16)(0);
  float16 p29 = 1.2+(float16)(0);
  float16 p30 = 1.2+(float16)(0);

  float16 i = 1.0+(float16)(0);
  float16 j = 2.2+(float16)(0);
  float N = 3.0 * (float)(n);

  int k;
  for(k = 1; k < N;k++,i=i+1 ) {
    p1 += copysign(i - 345, j);
    p2 += copysign(i - 234, j);
    p3 += copysign(i - 23, j);
    p4 += copysign(i - 24, j);
    p5 += copysign(i - 25, j);
    p6 += copysign(i - 64, j);
    p7 += copysign(i - 57, j);
    p8 += copysign(i - 22, j);
    p9 += copysign(i - 256, j);
    p10 += copysign(i - 46, j);
    p11 += copysign(i - 345, j);
    p12 += copysign(i - 234, j);
    p13 += copysign(i - 23, j);
    p14 += copysign(i - 24, j);
    p15 += copysign(i - 25, j);
    p16 += copysign(i - 64, j);
    p17 += copysign(i - 57, j);
    p18 += copysign(i - 22, j);
    p19 += copysign(i - 256, j);
    p20 += copysign(i - 46, j);
    p21 += copysign(i - 345, j);
    p22 += copysign(i - 234, j);
    p23 += copysign(i - 23, j);
    p24 += copysign(i - 24, j);
    p25 += copysign(i - 25, j);
    p26 += copysign(i - 64, j);
    p27 += copysign(i - 57, j);
    p28 += copysign(i - 22, j);
    p29 += copysign(i - 256, j);
    p30 += copysign(i - 46, j);
  }
  *result_copysign = p1.s0+p1.s1+p1.s2+p1.s3+p1.s4+p1.s5+p1.s6+p1.s7+p1.s8+p1.s9+p1.sa+p1.sb+p1.sc+p1.sd+p1.se+p1.sf
  			  + p2.s0+p2.s1+p2.s2+p2.s3+p2.s4+p2.s5+p2.s6+p2.s7+p2.s8+p2.s9+p2.sa+p2.sb+p2.sc+p2.sd+p2.se+p2.sf
  			  + p3.s0+p3.s1+p3.s2+p3.s3+p3.s4+p3.s5+p3.s6+p3.s7+p3.s8+p3.s9+p3.sa+p3.sb+p3.sc+p3.sd+p3.se+p3.sf
  			  + p4.s0+p4.s1+p4.s2+p4.s3+p4.s4+p4.s5+p4.s6+p4.s7+p4.s8+p4.s9+p4.sa+p4.sb+p4.sc+p4.sd+p4.se+p4.sf 
  			  + p5.s0+p5.s1+p5.s2+p5.s3+p5.s4+p5.s5+p5.s6+p5.s7+p5.s8+p5.s9+p5.sa+p5.sb+p5.sc+p5.sd+p5.se+p5.sf 
  			  + p6.s0+p6.s1+p6.s2+p6.s3+p6.s4+p6.s5+p6.s6+p6.s7+p6.s8+p6.s9+p6.sa+p6.sb+p6.sc+p6.sd+p6.se+p6.sf 
  			  + p7.s0+p7.s1+p7.s2+p7.s3+p7.s4+p7.s5+p7.s6+p7.s7+p7.s8+p7.s9+p7.sa+p7.sb+p7.sc+p7.sd+p7.se+p7.sf 
  			  + p8.s0+p8.s1+p8.s2+p8.s3+p8.s4+p8.s5+p8.s6+p8.s7+p8.s8+p8.s9+p8.sa+p8.sb+p8.sc+p8.sd+p8.se+p8.sf 
  			  + p9.s0+p9.s1+p9.s2+p9.s3+p9.s4+p9.s5+p9.s6+p9.s7+p9.s8+p9.s9+p9.sa+p9.sb+p9.sc+p9.sd+p9.se+p9.sf 
  			  + p10.s0+p10.s1+p10.s2+p10.s3+p10.s4+p10.s5+p10.s6+p10.s7+p10.s8+p10.s9+p10.sa+p10.sb+p10.sc+p10.sd+p10.se+p10.sf 
  			  + p11.s0+p11.s1+p11.s2+p11.s3+p11.s4+p11.s5+p11.s6+p11.s7+p11.s8+p11.s9+p11.sa+p11.sb+p11.sc+p11.sd+p11.se+p11.sf 
  			  + p12.s0+p12.s1+p12.s2+p12.s3+p12.s4+p12.s5+p12.s6+p12.s7+p12.s8+p12.s9+p12.sa+p12.sb+p12.sc+p12.sd+p12.se+p12.sf 
  			  + p13.s0+p13.s1+p13.s2+p13.s3+p13.s4+p13.s5+p13.s6+p13.s7+p13.s8+p13.s9+p13.sa+p13.sb+p13.sc+p13.sd+p13.se+p13.sf 
  			  + p14.s0+p14.s1+p14.s2+p14.s3+p14.s4+p14.s5+p14.s6+p14.s7+p14.s8+p14.s9+p14.sa+p14.sb+p14.sc+p14.sd+p14.se+p14.sf 
  			  + p15.s0+p15.s1+p15.s2+p15.s3+p15.s4+p15.s5+p15.s6+p15.s7+p15.s8+p15.s9+p15.sa+p15.sb+p15.sc+p15.sd+p15.se+p15.sf 
  			  + p16.s0+p16.s1+p16.s2+p16.s3+p16.s4+p16.s5+p16.s6+p16.s7+p16.s8+p16.s9+p16.sa+p16.sb+p16.sc+p16.sd+p16.se+p16.sf 
  			  + p17.s0+p17.s1+p17.s2+p17.s3+p17.s4+p17.s5+p17.s6+p17.s7+p17.s8+p17.s9+p17.sa+p17.sb+p17.sc+p17.sd+p17.se+p17.sf 
  			  + p18.s0+p18.s1+p18.s2+p18.s3+p18.s4+p18.s5+p18.s6+p18.s7+p18.s8+p18.s9+p18.sa+p18.sb+p18.sc+p18.sd+p18.se+p18.sf 
  			  + p19.s0+p19.s1+p19.s2+p19.s3+p19.s4+p19.s5+p19.s6+p19.s7+p19.s8+p19.s9+p19.sa+p19.sb+p19.sc+p19.sd+p19.se+p19.sf 
  			  + p20.s0+p20.s1+p20.s2+p20.s3+p20.s4+p20.s5+p20.s6+p20.s7+p20.s8+p20.s9+p20.sa+p20.sb+p20.sc+p20.sd+p20.se+p20.sf 
  			  + p21.s0+p21.s1+p21.s2+p21.s3+p21.s4+p21.s5+p21.s6+p21.s7+p21.s8+p21.s9+p21.sa+p21.sb+p21.sc+p21.sd+p21.se+p21.sf 
  			  + p22.s0+p22.s1+p22.s2+p22.s3+p22.s4+p22.s5+p22.s6+p22.s7+p22.s8+p22.s9+p22.sa+p22.sb+p22.sc+p22.sd+p22.se+p22.sf 
  			  + p23.s0+p23.s1+p23.s2+p23.s3+p23.s4+p23.s5+p23.s6+p23.s7+p23.s8+p23.s9+p23.sa+p23.sb+p23.sc+p23.sd+p23.se+p23.sf 
  			  + p24.s0+p24.s1+p24.s2+p24.s3+p24.s4+p24.s5+p24.s6+p24.s7+p24.s8+p24.s9+p24.sa+p24.sb+p24.sc+p24.sd+p24.se+p24.sf 
  			  + p25.s0+p25.s1+p25.s2+p25.s3+p25.s4+p25.s5+p25.s6+p25.s7+p25.s8+p25.s9+p25.sa+p25.sb+p25.sc+p25.sd+p25.se+p25.sf 
  			  + p26.s0+p26.s1+p26.s2+p26.s3+p26.s4+p26.s5+p26.s6+p26.s7+p26.s8+p26.s9+p26.sa+p26.sb+p26.sc+p26.sd+p26.se+p26.sf 
  			  + p27.s0+p27.s1+p27.s2+p27.s3+p27.s4+p27.s5+p27.s6+p27.s7+p27.s8+p27.s9+p27.sa+p27.sb+p27.sc+p27.sd+p27.se+p27.sf 
  			  + p28.s0+p28.s1+p28.s2+p28.s3+p28.s4+p28.s5+p28.s6+p28.s7+p28.s8+p28.s9+p28.sa+p28.sb+p28.sc+p28.sd+p28.se+p28.sf 
  			  + p29.s0+p29.s1+p29.s2+p29.s3+p29.s4+p29.s5+p29.s6+p29.s7+p29.s8+p29.s9+p29.sa+p29.sb+p29.sc+p29.sd+p29.se+p29.sf 
  			  + p30.s0+p30.s1+p30.s2+p30.s3+p30.s4+p30.s5+p30.s6+p30.s7+p30.s8+p30.s9+p30.sa+p30.sb+p30.sc+p30.sd+p30.se+p30.sf;
}

__kernel void kernel_fabs_withDD1(__global float * result_fabs, int N)
{
  float p1 = 0.0;
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat512(p1 += fabs(p1););
  }
  *result_fabs = p1;
}

__kernel void kernel_fabs_withDD2(__global float * result_fabs, int N)
{
  float2 p1 = 0.0 + (float2)(0);
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat512(p1 += fabs(p1););
  }
  *result_fabs = p1.s0+p1.s1;
}

__kernel void kernel_fabs_withDD4(__global float * result_fabs, int N)
{
  float4 p1 = 0.0 + (float4)(0);
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat512(p1 += fabs(p1););
  }
  *result_fabs = p1.s0 + p1.s1 + p1.s2 + p1.s3;
}

__kernel void kernel_fabs_withDD8(__global float * result_fabs, int N)
{
  float8 p1 = 0.0 + (float8)(0);
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat512(p1 += fabs(p1););
  }
  *result_fabs = p1.s0 + p1.s1 + p1.s2 + p1.s3 + p1.s4 + p1.s5 + p1.s6 +p1.s7;
}

__kernel void kernel_fabs_withDD16(__global float * result_fabs, int N)
{
  float16 p1 = 0.0 + (float16)(0);
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat512(p1 += fabs(p1););
  }
  *result_fabs = p1.s0 + p1.s1 + p1.s2 + p1.s3 + p1.s4 + p1.s5 + p1.s6 +p1.s7+p1.s8+p1.s9+p1.sa+p1.sb+p1.sc+p1.sd+p1.se+p1.sf;;
}

__kernel void kernel_fabs_withoutDD1(__global float * result_fabs, int n)
{
  float p1 = -2.3;
  float p2 = -2.3;
  float p3 = -2.3;
  float p4 = -2.3;
  float p5 = -2.3;
  float p6 = -2.3;
  float p7 = -2.3;
  float p8 = -2.3;
  float p9 = -2.3;
  float p10 = -2.3;
  float p11 = -2.3;
  float p12 = -2.3;
  float p13 = -2.3;
  float p14 = -2.3;
  float p15 = -2.3;
  float p16 = -2.3;
  float p17 = -2.3;
  float p18 = -2.3;
  float p19 = -2.3;
  float p20 = -2.3;
  float p21 = -2.3;
  float p22 = -2.3;
  float p23 = -2.3;
  float p24 = -2.3;
  float p25 = -2.3;
  float p26 = -2.3;
  float p27 = -2.3;
  float p28 = -2.3;
  float p29 = -2.3;
  float p30 = -2.3;

  float i = 0.0;
  float N = 256.0 * (float)(n);
  for(i = 0.0; i < N; i = i + 1.0) {
    p1 += fabs(i);
    p2 += fabs(i - 0.34);
    p3 += fabs(i - 36);
    p4 += fabs(i - 57);
    p5 += fabs(i - 24);
    p6 += fabs(i - 26);
    p7 += fabs(i - 36);
    p8 += fabs(i - 44);
    p9 += fabs(i - 26);
    p10 += fabs(i - 22);
    p11 += fabs(i);
    p12 += fabs(i - 0.34);
    p13 += fabs(i - 36);
    p14 += fabs(i - 57);
    p15 += fabs(i - 24);
    p16 += fabs(i - 26);
    p17 += fabs(i - 36);
    p18 += fabs(i - 44);
    p19 += fabs(i - 26);
    p20 += fabs(i - 22);
    p21 += fabs(i - 8);
    p22 += fabs(i - 0.34);
    p23 += fabs(i - 36);
    p24 += fabs(i - 57);
    p25 += fabs(i - 24);
    p26 += fabs(i - 26);
    p27 += fabs(i - 36);
    p28 += fabs(i - 44);
    p29 += fabs(i - 26);
    p30 += fabs(i - 22);
  }
  *result_fabs = p1 + p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9 + p10 + p11 + p12 + p13 + p14 + p15 + p16 + p17 + p18 + p19 + p20 + p21 + p22 + p23 + p24 + p25 + p26 + p27 + p28 + p29 + p30;
}

__kernel void kernel_fabs_withoutDD2(__global float * result_fabs, int n)
{
  float2 p1 = -2.3+(float2)(0);
  float2 p2 = -2.3+(float2)(0);
  float2 p3 = -2.3+(float2)(0);
  float2 p4 = -2.3+(float2)(0);
  float2 p5 = -2.3+(float2)(0);
  float2 p6 = -2.3+(float2)(0);
  float2 p7 = -2.3+(float2)(0);
  float2 p8 = -2.3+(float2)(0);
  float2 p9 = -2.3+(float2)(0);
  float2 p10 = -2.3+(float2)(0);
  float2 p11 = -2.3+(float2)(0);
  float2 p12 = -2.3+(float2)(0);
  float2 p13 = -2.3+(float2)(0);
  float2 p14 = -2.3+(float2)(0);
  float2 p15 = -2.3+(float2)(0);
  float2 p16 = -2.3+(float2)(0);
  float2 p17 = -2.3+(float2)(0);
  float2 p18 = -2.3+(float2)(0);
  float2 p19 = -2.3+(float2)(0);
  float2 p20 = -2.3+(float2)(0);
  float2 p21 = -2.3+(float2)(0);
  float2 p22 = -2.3+(float2)(0);
  float2 p23 = -2.3+(float2)(0);
  float2 p24 = -2.3+(float2)(0);
  float2 p25 = -2.3+(float2)(0);
  float2 p26 = -2.3+(float2)(0);
  float2 p27 = -2.3+(float2)(0);
  float2 p28 = -2.3+(float2)(0);
  float2 p29 = -2.3+(float2)(0);
  float2 p30 = -2.3+(float2)(0);

  float2 i = 0.0+(float2)(0);
  float N = 256.0 * (float)(n);

  int j;
  for(j = 0; j < N; j++,i = i + 1.0) {
    p1 += fabs(i);
    p2 += fabs(i - 0.34);
    p3 += fabs(i - 36);
    p4 += fabs(i - 57);
    p5 += fabs(i - 24);
    p6 += fabs(i - 26);
    p7 += fabs(i - 36);
    p8 += fabs(i - 44);
    p9 += fabs(i - 26);
    p10 += fabs(i - 22);
    p11 += fabs(i);
    p12 += fabs(i - 0.34);
    p13 += fabs(i - 36);
    p14 += fabs(i - 57);
    p15 += fabs(i - 24);
    p16 += fabs(i - 26);
    p17 += fabs(i - 36);
    p18 += fabs(i - 44);
    p19 += fabs(i - 26);
    p20 += fabs(i - 22);
    p21 += fabs(i - 8);
    p22 += fabs(i - 0.34);
    p23 += fabs(i - 36);
    p24 += fabs(i - 57);
    p25 += fabs(i - 24);
    p26 += fabs(i - 26);
    p27 += fabs(i - 36);
    p28 += fabs(i - 44);
    p29 += fabs(i - 26);
    p30 += fabs(i - 22);
  }
  *result_fabs = p1.s0+p1.s1 + p2.s0+p2.s1 + p3.s0+p3.s1 + p4.s0+p4.s1 + p5.s0+p5.s1 + p6.s0+p6.s1 + p7.s0+p7.s1 + p8.s0+p8.s1 + p9.s0+p9.s1+ p10.s0+p10.s1 + p11.s0+p11.s1 + p12.s0+p12.s1+ p13.s0+p13.s1 + p14.s0+p14.s1 + p15.s0+p15.s1+ p16.s0+p16.s1+ p17.s0+p17.s1 + p18.s0+p18.s1 + p19.s0+p19.s1+ p20.s0+p20.s1+ p21.s0+p21.s1 + p22.s0+p22.s1 + p23.s0+p23.s1 + p24.s0+p24.s1 + p25.s0+p25.s1 + p26.s0+p26.s1 + p27.s0+p27.s1 + p28.s0+p28.s1 + p29.s0+p29.s1 + p30.s0+p30.s1;
}

__kernel void kernel_fabs_withoutDD4(__global float * result_fabs, int n)
{
  float4 p1 = -2.3+(float4)(0);
  float4 p2 = -2.3+(float4)(0);
  float4 p3 = -2.3+(float4)(0);
  float4 p4 = -2.3+(float4)(0);
  float4 p5 = -2.3+(float4)(0);
  float4 p6 = -2.3+(float4)(0);
  float4 p7 = -2.3+(float4)(0);
  float4 p8 = -2.3+(float4)(0);
  float4 p9 = -2.3+(float4)(0);
  float4 p10 = -2.3+(float4)(0);
  float4 p11 = -2.3+(float4)(0);
  float4 p12 = -2.3+(float4)(0);
  float4 p13 = -2.3+(float4)(0);
  float4 p14 = -2.3+(float4)(0);
  float4 p15 = -2.3+(float4)(0);
  float4 p16 = -2.3+(float4)(0);
  float4 p17 = -2.3+(float4)(0);
  float4 p18 = -2.3+(float4)(0);
  float4 p19 = -2.3+(float4)(0);
  float4 p20 = -2.3+(float4)(0);
  float4 p21 = -2.3+(float4)(0);
  float4 p22 = -2.3+(float4)(0);
  float4 p23 = -2.3+(float4)(0);
  float4 p24 = -2.3+(float4)(0);
  float4 p25 = -2.3+(float4)(0);
  float4 p26 = -2.3+(float4)(0);
  float4 p27 = -2.3+(float4)(0);
  float4 p28 = -2.3+(float4)(0);
  float4 p29 = -2.3+(float4)(0);
  float4 p30 = -2.3+(float4)(0);

  float4 i = 0.0+(float4)(0);
  float N = 16.0 * (float)(n);

  int j;
  for(j = 0; j < N; j++,i = i + 1.0) {
    p1 += fabs(i);
    p2 += fabs(i - 0.34);
    p3 += fabs(i - 36);
    p4 += fabs(i - 57);
    p5 += fabs(i - 24);
    p6 += fabs(i - 26);
    p7 += fabs(i - 36);
    p8 += fabs(i - 44);
    p9 += fabs(i - 26);
    p10 += fabs(i - 22);
    p11 += fabs(i);
    p12 += fabs(i - 0.34);
    p13 += fabs(i - 36);
    p14 += fabs(i - 57);
    p15 += fabs(i - 24);
    p16 += fabs(i - 26);
    p17 += fabs(i - 36);
    p18 += fabs(i - 44);
    p19 += fabs(i - 26);
    p20 += fabs(i - 22);
    p21 += fabs(i - 8);
    p22 += fabs(i - 0.34);
    p23 += fabs(i - 36);
    p24 += fabs(i - 57);
    p25 += fabs(i - 24);
    p26 += fabs(i - 26);
    p27 += fabs(i - 36);
    p28 += fabs(i - 44);
    p29 += fabs(i - 26);
    p30 += fabs(i - 22);
  }
  *result_fabs = p1.s0+p1.s1+p1.s2+p1.s3 + p2.s0+p2.s1+p2.s2+p2.s3 + p3.s0+p3.s1+p3.s2+p3.s3 + p4.s0+p4.s1+p4.s2+p4.s3 + p5.s0+p5.s1+p5.s2+p5.s3 + p6.s0+p6.s1+p6.s2+p6.s3 + p7.s0+p7.s1+p7.s2+p7.s3 + p8.s0+p8.s1+p8.s2+p8.s3 + p9.s0+p9.s1+p9.s2+p9.s3 + p10.s0+p10.s1+p10.s2+p10.s3 + p11.s0+p11.s1+p11.s2+p11.s3 + p12.s0+p12.s1+p12.s2+p12.s3 + p13.s0+p13.s1+p13.s2+p13.s3 + p14.s0+p14.s1+p14.s2+p14.s3 + p15.s0+p15.s1+p15.s2+p15.s3 + p16.s0+p16.s1+p16.s2+p16.s3 + p17.s0+p17.s1+p17.s2+p17.s3 + p18.s0+p18.s1+p18.s2+p18.s3 + p19.s0+p19.s1+p19.s2+p19.s3 + p20.s0+p20.s1+p20.s2+p20.s3 + p21.s0+p21.s1+p21.s2+p21.s3 + p22.s0+p22.s1+p22.s2+p22.s3 + p23.s0+p23.s1+p23.s2+p23.s3 + p24.s0+p24.s1+p24.s2+p24.s3 + p25.s0+p25.s1+p25.s2+p25.s3 + p26.s0+p26.s1+p26.s2+p26.s3 + p27.s0+p27.s1+p27.s2+p27.s3 + p28.s0+p28.s1+p28.s2+p28.s3 + p29.s0+p29.s1+p29.s2+p29.s3 + p30.s0+p30.s1+p30.s2+p30.s3;
}

__kernel void kernel_fabs_withoutDD8(__global float * result_fabs, int n)
{
  float8 p1 = -2.3+(float8)(0);
  float8 p2 = -2.3+(float8)(0);
  float8 p3 = -2.3+(float8)(0);
  float8 p4 = -2.3+(float8)(0);
  float8 p5 = -2.3+(float8)(0);
  float8 p6 = -2.3+(float8)(0);
  float8 p7 = -2.3+(float8)(0);
  float8 p8 = -2.3+(float8)(0);
  float8 p9 = -2.3+(float8)(0);
  float8 p10 = -2.3+(float8)(0);
  float8 p11 = -2.3+(float8)(0);
  float8 p12 = -2.3+(float8)(0);
  float8 p13 = -2.3+(float8)(0);
  float8 p14 = -2.3+(float8)(0);
  float8 p15 = -2.3+(float8)(0);
  float8 p16 = -2.3+(float8)(0);
  float8 p17 = -2.3+(float8)(0);
  float8 p18 = -2.3+(float8)(0);
  float8 p19 = -2.3+(float8)(0);
  float8 p20 = -2.3+(float8)(0);
  float8 p21 = -2.3+(float8)(0);
  float8 p22 = -2.3+(float8)(0);
  float8 p23 = -2.3+(float8)(0);
  float8 p24 = -2.3+(float8)(0);
  float8 p25 = -2.3+(float8)(0);
  float8 p26 = -2.3+(float8)(0);
  float8 p27 = -2.3+(float8)(0);
  float8 p28 = -2.3+(float8)(0);
  float8 p29 = -2.3+(float8)(0);
  float8 p30 = -2.3+(float8)(0);

  float8 i = 0.0+(float8)(0);
  float N = 8.0 * (float)(n);

  int j;
  for(j = 0; j < N; j++,i = i + 1.0) {
    p1 += fabs(i);
    p2 += fabs(i - 0.34);
    p3 += fabs(i - 36);
    p4 += fabs(i - 57);
    p5 += fabs(i - 24);
    p6 += fabs(i - 26);
    p7 += fabs(i - 36);
    p8 += fabs(i - 44);
    p9 += fabs(i - 26);
    p10 += fabs(i - 22);
    p11 += fabs(i);
    p12 += fabs(i - 0.34);
    p13 += fabs(i - 36);
    p14 += fabs(i - 57);
    p15 += fabs(i - 24);
    p16 += fabs(i - 26);
    p17 += fabs(i - 36);
    p18 += fabs(i - 44);
    p19 += fabs(i - 26);
    p20 += fabs(i - 22);
    p21 += fabs(i - 8);
    p22 += fabs(i - 0.34);
    p23 += fabs(i - 36);
    p24 += fabs(i - 57);
    p25 += fabs(i - 24);
    p26 += fabs(i - 26);
    p27 += fabs(i - 36);
    p28 += fabs(i - 44);
    p29 += fabs(i - 26);
    p30 += fabs(i - 22);
  }
  *result_fabs = p1.s0+p1.s1+p1.s2+p1.s3+p1.s4+p1.s5+p1.s6+p1.s7
  			  + p2.s0+p2.s1+p2.s2+p2.s3+p2.s4+p2.s5+p2.s6+p2.s7
  			  + p3.s0+p3.s1+p3.s2+p3.s3+p3.s4+p3.s5+p3.s6+p3.s7 
  			  + p4.s0+p4.s1+p4.s2+p4.s3+p4.s4+p4.s5+p4.s6+p4.s7 
  			  + p5.s0+p5.s1+p5.s2+p5.s3+p5.s4+p5.s5+p5.s6+p5.s7 
  			  + p6.s0+p6.s1+p6.s2+p6.s3+p6.s4+p6.s5+p6.s6+p6.s7 
  			  + p7.s0+p7.s1+p7.s2+p7.s3+p7.s4+p7.s5+p7.s6+p7.s7 
  			  + p8.s0+p8.s1+p8.s2+p8.s3+p8.s4+p8.s5+p8.s6+p8.s7 
  			  + p9.s0+p9.s1+p9.s2+p9.s3+p9.s4+p9.s5+p9.s6+p9.s7 
  			  + p10.s0+p10.s1+p10.s2+p10.s3+p10.s4+p10.s5+p10.s6+p10.s7 
  			  + p11.s0+p11.s1+p11.s2+p11.s3+p11.s4+p11.s5+p11.s6+p11.s7 
  			  + p12.s0+p12.s1+p12.s2+p12.s3+p12.s4+p12.s5+p12.s6+p12.s7 
  			  + p13.s0+p13.s1+p13.s2+p13.s3+p13.s4+p13.s5+p13.s6+p13.s7 
  			  + p14.s0+p14.s1+p14.s2+p14.s3+p14.s4+p14.s5+p14.s6+p14.s7 
  			  + p15.s0+p15.s1+p15.s2+p15.s3+p15.s4+p15.s5+p15.s6+p15.s7 
  			  + p16.s0+p16.s1+p16.s2+p16.s3+p16.s4+p16.s5+p16.s6+p16.s7 
  			  + p17.s0+p17.s1+p17.s2+p17.s3+p17.s4+p17.s5+p17.s6+p17.s7 
  			  + p18.s0+p18.s1+p18.s2+p18.s3+p18.s4+p18.s5+p18.s6+p18.s7 
  			  + p19.s0+p19.s1+p19.s2+p19.s3+p19.s4+p19.s5+p19.s6+p19.s7 
  			  + p20.s0+p20.s1+p20.s2+p20.s3+p20.s4+p20.s5+p20.s6+p20.s7 
  			  + p21.s0+p21.s1+p21.s2+p21.s3+p21.s4+p21.s5+p21.s6+p21.s7 
  			  + p22.s0+p22.s1+p22.s2+p22.s3+p22.s4+p22.s5+p22.s6+p22.s7 
  			  + p23.s0+p23.s1+p23.s2+p23.s3+p23.s4+p23.s5+p23.s6+p23.s7 
  			  + p24.s0+p24.s1+p24.s2+p24.s3+p24.s4+p24.s5+p24.s6+p24.s7 
  			  + p25.s0+p25.s1+p25.s2+p25.s3+p25.s4+p25.s5+p25.s6+p25.s7 
  			  + p26.s0+p26.s1+p26.s2+p26.s3+p26.s4+p26.s5+p26.s6+p26.s7 
  			  + p27.s0+p27.s1+p27.s2+p27.s3+p27.s4+p27.s5+p27.s6+p27.s7 
  			  + p28.s0+p28.s1+p28.s2+p28.s3+p28.s4+p28.s5+p28.s6+p28.s7 
  			  + p29.s0+p29.s1+p29.s2+p29.s3+p29.s4+p29.s5+p29.s6+p29.s7 
  			  + p30.s0+p30.s1+p30.s2+p30.s3+p30.s4+p30.s5+p30.s6+p30.s7;

 }
__kernel void kernel_fabs_withoutDD16(__global float * result_fabs, int n)
{
  float16 p1 = -2.3+(float16)(0);
  float16 p2 = -2.3+(float16)(0);
  float16 p3 = -2.3+(float16)(0);
  float16 p4 = -2.3+(float16)(0);
  float16 p5 = -2.3+(float16)(0);
  float16 p6 = -2.3+(float16)(0);
  float16 p7 = -2.3+(float16)(0);
  float16 p8 = -2.3+(float16)(0);
  float16 p9 = -2.3+(float16)(0);
  float16 p10 = -2.3+(float16)(0);
  float16 p11 = -2.3+(float16)(0);
  float16 p12 = -2.3+(float16)(0);
  float16 p13 = -2.3+(float16)(0);
  float16 p14 = -2.3+(float16)(0);
  float16 p15 = -2.3+(float16)(0);
  float16 p16 = -2.3+(float16)(0);
  float16 p17 = -2.3+(float16)(0);
  float16 p18 = -2.3+(float16)(0);
  float16 p19 = -2.3+(float16)(0);
  float16 p20 = -2.3+(float16)(0);
  float16 p21 = -2.3+(float16)(0);
  float16 p22 = -2.3+(float16)(0);
  float16 p23 = -2.3+(float16)(0);
  float16 p24 = -2.3+(float16)(0);
  float16 p25 = -2.3+(float16)(0);
  float16 p26 = -2.3+(float16)(0);
  float16 p27 = -2.3+(float16)(0);
  float16 p28 = -2.3+(float16)(0);
  float16 p29 = -2.3+(float16)(0);
  float16 p30 = -2.3+(float16)(0);

  float16 i = 0.0+(float16)(0);
  float N = 4.0 * (float)(n);

  int j;
  for(j = 0; j < N; j++,i = i + 1.0) {
    p1 += fabs(i);
    p2 += fabs(i - 0.34);
    p3 += fabs(i - 36);
    p4 += fabs(i - 57);
    p5 += fabs(i - 24);
    p6 += fabs(i - 26);
    p7 += fabs(i - 36);
    p8 += fabs(i - 44);
    p9 += fabs(i - 26);
    p10 += fabs(i - 22);
    p11 += fabs(i);
    p12 += fabs(i - 0.34);
    p13 += fabs(i - 36);
    p14 += fabs(i - 57);
    p15 += fabs(i - 24);
    p16 += fabs(i - 26);
    p17 += fabs(i - 36);
    p18 += fabs(i - 44);
    p19 += fabs(i - 26);
    p20 += fabs(i - 22);
    p21 += fabs(i - 8);
    p22 += fabs(i - 0.34);
    p23 += fabs(i - 36);
    p24 += fabs(i - 57);
    p25 += fabs(i - 24);
    p26 += fabs(i - 26);
    p27 += fabs(i - 36);
    p28 += fabs(i - 44);
    p29 += fabs(i - 26);
    p30 += fabs(i - 22);
  }
  *result_fabs =  p1.s0+p1.s1+p1.s2+p1.s3+p1.s4+p1.s5+p1.s6+p1.s7+p1.s8+p1.s9+p1.sa+p1.sb+p1.sc+p1.sd+p1.se+p1.sf
  			  + p2.s0+p2.s1+p2.s2+p2.s3+p2.s4+p2.s5+p2.s6+p2.s7+p2.s8+p2.s9+p2.sa+p2.sb+p2.sc+p2.sd+p2.se+p2.sf
  			  + p3.s0+p3.s1+p3.s2+p3.s3+p3.s4+p3.s5+p3.s6+p3.s7+p3.s8+p3.s9+p3.sa+p3.sb+p3.sc+p3.sd+p3.se+p3.sf
  			  + p4.s0+p4.s1+p4.s2+p4.s3+p4.s4+p4.s5+p4.s6+p4.s7+p4.s8+p4.s9+p4.sa+p4.sb+p4.sc+p4.sd+p4.se+p4.sf 
  			  + p5.s0+p5.s1+p5.s2+p5.s3+p5.s4+p5.s5+p5.s6+p5.s7+p5.s8+p5.s9+p5.sa+p5.sb+p5.sc+p5.sd+p5.se+p5.sf 
  			  + p6.s0+p6.s1+p6.s2+p6.s3+p6.s4+p6.s5+p6.s6+p6.s7+p6.s8+p6.s9+p6.sa+p6.sb+p6.sc+p6.sd+p6.se+p6.sf 
  			  + p7.s0+p7.s1+p7.s2+p7.s3+p7.s4+p7.s5+p7.s6+p7.s7+p7.s8+p7.s9+p7.sa+p7.sb+p7.sc+p7.sd+p7.se+p7.sf 
  			  + p8.s0+p8.s1+p8.s2+p8.s3+p8.s4+p8.s5+p8.s6+p8.s7+p8.s8+p8.s9+p8.sa+p8.sb+p8.sc+p8.sd+p8.se+p8.sf 
  			  + p9.s0+p9.s1+p9.s2+p9.s3+p9.s4+p9.s5+p9.s6+p9.s7+p9.s8+p9.s9+p9.sa+p9.sb+p9.sc+p9.sd+p9.se+p9.sf 
  			  + p10.s0+p10.s1+p10.s2+p10.s3+p10.s4+p10.s5+p10.s6+p10.s7+p10.s8+p10.s9+p10.sa+p10.sb+p10.sc+p10.sd+p10.se+p10.sf 
  			  + p11.s0+p11.s1+p11.s2+p11.s3+p11.s4+p11.s5+p11.s6+p11.s7+p11.s8+p11.s9+p11.sa+p11.sb+p11.sc+p11.sd+p11.se+p11.sf 
  			  + p12.s0+p12.s1+p12.s2+p12.s3+p12.s4+p12.s5+p12.s6+p12.s7+p12.s8+p12.s9+p12.sa+p12.sb+p12.sc+p12.sd+p12.se+p12.sf 
  			  + p13.s0+p13.s1+p13.s2+p13.s3+p13.s4+p13.s5+p13.s6+p13.s7+p13.s8+p13.s9+p13.sa+p13.sb+p13.sc+p13.sd+p13.se+p13.sf 
  			  + p14.s0+p14.s1+p14.s2+p14.s3+p14.s4+p14.s5+p14.s6+p14.s7+p14.s8+p14.s9+p14.sa+p14.sb+p14.sc+p14.sd+p14.se+p14.sf 
  			  + p15.s0+p15.s1+p15.s2+p15.s3+p15.s4+p15.s5+p15.s6+p15.s7+p15.s8+p15.s9+p15.sa+p15.sb+p15.sc+p15.sd+p15.se+p15.sf 
  			  + p16.s0+p16.s1+p16.s2+p16.s3+p16.s4+p16.s5+p16.s6+p16.s7+p16.s8+p16.s9+p16.sa+p16.sb+p16.sc+p16.sd+p16.se+p16.sf 
  			  + p17.s0+p17.s1+p17.s2+p17.s3+p17.s4+p17.s5+p17.s6+p17.s7+p17.s8+p17.s9+p17.sa+p17.sb+p17.sc+p17.sd+p17.se+p17.sf 
  			  + p18.s0+p18.s1+p18.s2+p18.s3+p18.s4+p18.s5+p18.s6+p18.s7+p18.s8+p18.s9+p18.sa+p18.sb+p18.sc+p18.sd+p18.se+p18.sf 
  			  + p19.s0+p19.s1+p19.s2+p19.s3+p19.s4+p19.s5+p19.s6+p19.s7+p19.s8+p19.s9+p19.sa+p19.sb+p19.sc+p19.sd+p19.se+p19.sf 
  			  + p20.s0+p20.s1+p20.s2+p20.s3+p20.s4+p20.s5+p20.s6+p20.s7+p20.s8+p20.s9+p20.sa+p20.sb+p20.sc+p20.sd+p20.se+p20.sf 
  			  + p21.s0+p21.s1+p21.s2+p21.s3+p21.s4+p21.s5+p21.s6+p21.s7+p21.s8+p21.s9+p21.sa+p21.sb+p21.sc+p21.sd+p21.se+p21.sf 
  			  + p22.s0+p22.s1+p22.s2+p22.s3+p22.s4+p22.s5+p22.s6+p22.s7+p22.s8+p22.s9+p22.sa+p22.sb+p22.sc+p22.sd+p22.se+p22.sf 
  			  + p23.s0+p23.s1+p23.s2+p23.s3+p23.s4+p23.s5+p23.s6+p23.s7+p23.s8+p23.s9+p23.sa+p23.sb+p23.sc+p23.sd+p23.se+p23.sf 
  			  + p24.s0+p24.s1+p24.s2+p24.s3+p24.s4+p24.s5+p24.s6+p24.s7+p24.s8+p24.s9+p24.sa+p24.sb+p24.sc+p24.sd+p24.se+p24.sf 
  			  + p25.s0+p25.s1+p25.s2+p25.s3+p25.s4+p25.s5+p25.s6+p25.s7+p25.s8+p25.s9+p25.sa+p25.sb+p25.sc+p25.sd+p25.se+p25.sf 
  			  + p26.s0+p26.s1+p26.s2+p26.s3+p26.s4+p26.s5+p26.s6+p26.s7+p26.s8+p26.s9+p26.sa+p26.sb+p26.sc+p26.sd+p26.se+p26.sf 
  			  + p27.s0+p27.s1+p27.s2+p27.s3+p27.s4+p27.s5+p27.s6+p27.s7+p27.s8+p27.s9+p27.sa+p27.sb+p27.sc+p27.sd+p27.se+p27.sf 
  			  + p28.s0+p28.s1+p28.s2+p28.s3+p28.s4+p28.s5+p28.s6+p28.s7+p28.s8+p28.s9+p28.sa+p28.sb+p28.sc+p28.sd+p28.se+p28.sf 
  			  + p29.s0+p29.s1+p29.s2+p29.s3+p29.s4+p29.s5+p29.s6+p29.s7+p29.s8+p29.s9+p29.sa+p29.sb+p29.sc+p29.sd+p29.se+p29.sf 
  			  + p30.s0+p30.s1+p30.s2+p30.s3+p30.s4+p30.s5+p30.s6+p30.s7+p30.s8+p30.s9+p30.sa+p30.sb+p30.sc+p30.sd+p30.se+p30.sf;
 }


