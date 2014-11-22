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

__kernel void kernel_erfc_withDD1(__global float* result_erfc, int N)
{
  float t1 = 1.0;
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat64(t1 = erfc(t1););
  }
  *result_erfc = t1;
}

__kernel void kernel_erfc_withDD2(__global float* result_erfc, int N)
{
  float2 t1 = 1.0+(float2)(0); 
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat64(t1 = erfc(t1););
  }
  *result_erfc = t1.s0 + t1.s1;
}

__kernel void kernel_erfc_withDD4(__global float* result_erfc, int N)
{
  float4 t1 = 1.0+(float4)(0); 
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat64(t1 = erfc(t1););
  }
  *result_erfc = t1.s0 + t1.s1 + t1.s2 + t1.s3;
}

__kernel void kernel_erfc_withDD8(__global float* result_erfc, int N)
{
  float8 t1 = 1.0+(float8)(0); 
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat64(t1 = erfc(t1););
  }
  *result_erfc = t1.s0 + t1.s1 + t1.s2 + t1.s3 + t1.s4 + t1.s5 + t1.s6 +t1.s7;
}

__kernel void kernel_erfc_withDD16(__global float* result_erfc, int N)
{
  float16 t1 = 1.0+(float16)(0); 
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat64(t1 = erfc(t1););
  }
  *result_erfc = t1.s0 + t1.s1 + t1.s2 + t1.s3 + t1.s4 + t1.s5 + t1.s6 +t1.s7+t1.s8+t1.s9+t1.sa+t1.sb+t1.sc+t1.sd+t1.se+t1.sf;
}

__kernel void kernel_erfc_withoutDD1(__global float* result_erfc, int N)
{
  float  t1 = 1.0;
  float  t2 = 1.0;
  float  t3 = 1.0;
  float  t4 = 1.0;
  float  t5 = 1.0;
  float  t6 = 1.0;
  float  t7 = 1.0;
  float  t8 = 1.0;
  float  t9 = 1.0;
  float  t10 = 1.0;

  float i = 0.0;
  float j;
  float n = 7 * N;

  for(i = 0.0; i < n; i = i + 1.0) {
     t1 = erfc(i);
     t2 =  erfc(i);
     t3 =  erfc(i);
     t4 =  erfc(i);
     t5 =  erfc(i);
     t6 =  erfc(i);
     t7 =  erfc(i);
     t8 =  erfc(i);
     t9 =  erfc(i);
     t10 =  erfc(i);
  }
  *result_erfc =  t1 +  t2 +  t3 +  t4 +  t5 +  t6 +  t7 +  t8 +  t9 +  t10;
}

__kernel void kernel_erfc_withoutDD2(__global float* result_erfc, int N)
{
  float2  t1 = 1.0+(float2)(0); 
  float2  t2 = 1.0+(float2)(0); 
  float2  t3 = 1.0+(float2)(0); 
  float2  t4 = 1.0+(float2)(0); 
  float2  t5 = 1.0+(float2)(0); 
  float2  t6 = 1.0+(float2)(0); 
  float2  t7 = 1.0+(float2)(0); 
  float2  t8 = 1.0+(float2)(0); 
  float2  t9 = 1.0+(float2)(0); 
  float2  t10 = 1.0+(float2)(0); 

  float2 i = 0.0+(float2)(0); 
  float2 j; 
  float n = 7 * N;

  for(i.s0 = 0.0; i.s0 < n; i = i + 1.0) {
     t1 =  erfc(i);
     t2 =  erfc(i);
     t3 =  erfc(i);
     t4 =  erfc(i);
     t5 =  erfc(i);
     t6 =  erfc(i);
     t7 =  erfc(i);
     t8 =  erfc(i);
     t9 =  erfc(i);
     t10 =  erfc(i);
  }
  *result_erfc =  t1.s0+t1.s1 + t2.s0+t2.s1 + t3.s0+t3.s1 + t4.s0+t4.s1 + 
		   t5.s0+t5.s1 + t6.s0+t6.s1 + t7.s0+t7.s1 + t8.s0+t8.s1 + 
		   t9.s0+t9.s1+ t10.s0+t10.s1;
}


__kernel void kernel_erfc_withoutDD4(__global float* result_erfc, int N)
{
  float4  t1 = 1.0+(float4)(0); 
  float4  t2 = 1.0+(float4)(0); 
  float4  t3 = 1.0+(float4)(0); 
  float4  t4 = 1.0+(float4)(0); 
  float4  t5 = 1.0+(float4)(0); 
  float4  t6 = 1.0+(float4)(0); 
  float4  t7 = 1.0+(float4)(0); 
  float4  t8 = 1.0+(float4)(0); 
  float4  t9 = 1.0+(float4)(0); 
  float4  t10 = 1.0+(float4)(0); 

  float4 i = 0.0+(float4)(0); 
  float4 j; 
  float n = 7 * N;

  for(i.s0 = 0.0; i.s0 < n; i = i + 1.0) {
     t1 =  erfc(i);
     t2 =  erfc(i);
     t3 =  erfc(i);
     t4 =  erfc(i);
     t5 =  erfc(i);
     t6 =  erfc(i);
     t7 =  erfc(i);
     t8 =  erfc(i);
     t9 =  erfc(i);
     t10 =  erfc(i);
  }
  *result_erfc =  t1.s0+t1.s1+t1.s2+t1.s3 + t2.s0+t2.s1+t2.s2+t2.s3
	    	 + t3.s0+t3.s1+t3.s2+t3.s3 + t4.s0+t4.s1+t4.s2+t4.s3
		 + t5.s0+t5.s1+t5.s2+t5.s3 + t6.s0+t6.s1+t6.s2+t6.s3
		 + t7.s0+t7.s1+t7.s2+t7.s3 + t8.s0+t8.s1+t8.s2+t8.s3
		 + t9.s0+t9.s1+t9.s2+t9.s3 + t10.s0+t10.s1+t10.s2+t10.s3;
}

__kernel void kernel_erfc_withoutDD8(__global float* result_erfc, int N)
{
  float8  t1 = 1.0+(float8)(0); 
  float8  t2 = 1.0+(float8)(0); 
  float8  t3 = 1.0+(float8)(0); 
  float8  t4 = 1.0+(float8)(0); 
  float8  t5 = 1.0+(float8)(0); 
  float8  t6 = 1.0+(float8)(0); 
  float8  t7 = 1.0+(float8)(0); 
  float8  t8 = 1.0+(float8)(0); 
  float8  t9 = 1.0+(float8)(0); 
  float8  t10 = 1.0+(float8)(0); 

  float8 i = 0.0+(float8)(0); 
  float8 j; 
  float n = 7 * N;

  for(i.s0 = 0.0; i.s0 < n; i = i + 1.0) {
     t1 =  erfc(i);
     t2 =  erfc(i);
     t3 =  erfc(i);
     t4 =  erfc(i);
     t5 =  erfc(i);
     t6 =  erfc(i);
     t7 =  erfc(i);
     t8 =  erfc(i);
     t9 =  erfc(i);
     t10 =  erfc(i);
  }
  *result_erfc =  t1.s0+t1.s1+t1.s2+t1.s3+t1.s4+t1.s5+t1.s6+t1.s7
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

__kernel void kernel_erfc_withoutDD16(__global float* result_erfc, int N)
{
  float16  t1 = 1.0+(float16)(0); 
  float16  t2 = 1.0+(float16)(0); 
  float16  t3 = 1.0+(float16)(0); 
  float16  t4 = 1.0+(float16)(0); 
  float16  t5 = 1.0+(float16)(0); 
  float16  t6 = 1.0+(float16)(0); 
  float16  t7 = 1.0+(float16)(0); 
  float16  t8 = 1.0+(float16)(0); 
  float16  t9 = 1.0+(float16)(0); 
  float16  t10 = 1.0+(float16)(0); 

  float16 i = 0.0+(float16)(0); 
  float16 j; 
  float n = 7 * N;

  for(i.s0 = 0.0; i.s0 < n; i = i + 1.0) {
     t1 =  erfc(i);
     t2 =  erfc(i);
     t3 =  erfc(i);
     t4 =  erfc(i);
     t5 =  erfc(i);
     t6 =  erfc(i);
     t7 =  erfc(i);
     t8 =  erfc(i);
     t9 =  erfc(i);
     t10 =  erfc(i);
  }
  *result_erfc = t1.s0+t1.s1+t1.s2+t1.s3+t1.s4+t1.s5+t1.s6+t1.s7+t1.s8+t1.s9+t1.sa+t1.sb+t1.sc+t1.sd+t1.se+t1.sf
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

__kernel void kernel_erf_withDD1(__global float* result_erf, int N)
{
  float t1 = 1.1;
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat64(t1 = erf(t1););
  }
  *result_erf = t1;
}

__kernel void kernel_erf_withDD2(__global float* result_erf, int N)
{
  float2 t1 = 1.1+(float2)(0);
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat64(t1 = erf(t1););
  }
  *result_erf = t1.s0 + t1.s1;
}
 
__kernel void kernel_erf_withDD4(__global float* result_erf, int N)
{
  float4 t1 = 1.1+(float4)(0);
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat64(t1 = erf(t1););
  }
  *result_erf = t1.s0 + t1.s1 + t1.s2 + t1.s3;
}

__kernel void kernel_erf_withDD8(__global float* result_erf, int N)
{
  float8 t1 = 1.1+(float8)(0);
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat64(t1 = erf(t1););
  }
  *result_erf = t1.s0 + t1.s1 + t1.s2 + t1.s3 + t1.s4 + t1.s5 + t1.s6 +t1.s7;
}

__kernel void kernel_erf_withDD16(__global float* result_erf, int N)
{
  float16 t1 = 1.1+(float16)(0);
  int i = 0;
  for(i = 0; i < N; i++) {
	repeat32(t1 = erf(t1););
  }
  *result_erf = t1.s0 + t1.s1 + t1.s2 + t1.s3 + t1.s4 + t1.s5 + t1.s6 +t1.s7+t1.s8+t1.s9+t1.sa+t1.sb+t1.sc+t1.sd+t1.se+t1.sf;
}

__kernel void kernel_erf_withoutDD1(__global float* result_erf, int N)
{
  float t1 = 1.23;
  float t2 = 1.23;
  float t3 = 1.23;
  float t4 = 1.23;
  float t5 = 1.23;
  float t6 = 1.23;
  float t7 = 1.23;

  float i = 1.0;
  for(i = 1.0; i < N; i = i + 1.0) {
    t1 = erf(i + 0.1);
    t2 = erf(i + 0.2);
    t3 = erf(i + 0.3);
    t4 = erf(i + 0.4);
    t5 = erf(i + 0.5);
    t6 = erf(i + 0.6);
    t7 = erf(i + 0.7);
  }
  *result_erf = t1 + t2 + t3 + t4 + t5 + t6 + t7;
}

__kernel void kernel_erf_withoutDD2(__global float* result_erf, int N)
{
  float2 t1;
  float2 t2;
  float2 t3;
  float2 t4;
  float2 t5;
  float2 t6;
  float2 t7;

  float2 i = (float2)(1.0);

  for(i.s0 = 1.0; i.s0< N; i = i + 1.0) {
    t1 = erf(i + 0.1);
    t2 = erf(i + 0.2);
    t3 = erf(i + 0.3);
    t4 = erf(i + 0.4);
    t5 = erf(i + 0.5);
    t6 = erf(i + 0.6);
    t7 = erf(i + 0.7);
  }
  *result_erf = t1.s0+t1.s1 + t2.s0+t2.s1 + t3.s0+t3.s1 + t4.s0+t4.s1 + t5.s0+t5.s1 + t6.s0+t6.s1 + t7.s0+t7.s1;
}


__kernel void kernel_erf_withoutDD4(__global float* result_erf, int N)
{
  float4 t1;
  float4 t2;
  float4 t3;
  float4 t4;
  float4 t5;
  float4 t6;
  float4 t7;

  float4 i = (float4)(1.0);

  for(i.s0 = 1.0; i.s0< N; i = i + 1.0) {
    t1 = erf(i + 0.1);
    t2 = erf(i + 0.2);
    t3 = erf(i + 0.3);
    t4 = erf(i + 0.4);
    t5 = erf(i + 0.5);
    t6 = erf(i + 0.6);
    t7 = erf(i + 0.7);

  }
  *result_erf = t1.s0+t1.s1+t1.s2+t1.s3 + t2.s0+t2.s1+t2.s2+t2.s3
	    	+ t3.s0+t3.s1+t3.s2+t3.s3 + t4.s0+t4.s1+t4.s2+t4.s3
		+ t5.s0+t5.s1+t5.s2+t5.s3 + t6.s0+t6.s1+t6.s2+t6.s3
		+ t7.s0+t7.s1+t7.s2+t7.s3;
}

__kernel void kernel_erf_withoutDD8(__global float* result_erf, int N)
{
  float8 t1;
  float8 t2;
  float8 t3;
  float8 t4;
  float8 t5;
  float8 t6;
  float8 t7;

  float8 i = (float8)(1.0);

  for(i.s0 = 1.0; i.s0< N; i = i + 1.0) {
    t1 = erf(i + 0.1);
    t2 = erf(i + 0.2);
    t3 = erf(i + 0.3);
    t4 = erf(i + 0.4);
    t5 = erf(i + 0.5);
    t6 = erf(i + 0.6);
    t7 = erf(i + 0.7);

  }
  *result_erf = t1.s0+t1.s1+t1.s2+t1.s3+t1.s4+t1.s5+t1.s6+t1.s7
  		+ t2.s0+t2.s1+t2.s2+t2.s3+t2.s4+t2.s5+t2.s6+t2.s7
  		+ t3.s0+t3.s1+t3.s2+t3.s3+t3.s4+t3.s5+t3.s6+t3.s7 
  		+ t4.s0+t4.s1+t4.s2+t4.s3+t4.s4+t4.s5+t4.s6+t4.s7 
  		+ t5.s0+t5.s1+t5.s2+t5.s3+t5.s4+t5.s5+t5.s6+t5.s7 
  		+ t6.s0+t6.s1+t6.s2+t6.s3+t6.s4+t6.s5+t6.s6+t6.s7 
  		+ t7.s0+t7.s1+t7.s2+t7.s3+t7.s4+t7.s5+t7.s6+t7.s7;
}

__kernel void kernel_erf_withoutDD16(__global float* result_erf, int N)
{
  float16 t1;
  float16 t2;
  float16 t3;
  float16 t4;
  float16 t5;
  float16 t6;
  float16 t7;


  float16 i = (float16)(1.0);

  for(i.s0 = 1.0; i.s0< N; i = i + 1.0) {
    t1 = erf(i + 0.1);
    t2 = erf(i + 0.2);
    t3 = erf(i + 0.3);
    t4 = erf(i + 0.4);
    t5 = erf(i + 0.5);
    t6 = erf(i + 0.6);
    t7 = erf(i + 0.7);

  }
  *result_erf = t1.s0+t1.s1+t1.s2+t1.s3+t1.s4+t1.s5+t1.s6+t1.s7+t1.s8+t1.s9+t1.sa+t1.sb+t1.sc+t1.sd+t1.se+t1.sf
  		+ t2.s0+t2.s1+t2.s2+t2.s3+t2.s4+t2.s5+t2.s6+t2.s7+t2.s8+t2.s9+t2.sa+t2.sb+t2.sc+t2.sd+t2.se+t2.sf
  		+ t3.s0+t3.s1+t3.s2+t3.s3+t3.s4+t3.s5+t3.s6+t3.s7+t3.s8+t3.s9+t3.sa+t3.sb+t3.sc+t3.sd+t3.se+t3.sf
  		+ t4.s0+t4.s1+t4.s2+t4.s3+t4.s4+t4.s5+t4.s6+t4.s7+t4.s8+t4.s9+t4.sa+t4.sb+t4.sc+t4.sd+t4.se+t4.sf 
  		+ t5.s0+t5.s1+t5.s2+t5.s3+t5.s4+t5.s5+t5.s6+t5.s7+t5.s8+t5.s9+t5.sa+t5.sb+t5.sc+t5.sd+t5.se+t5.sf 
  		+ t6.s0+t6.s1+t6.s2+t6.s3+t6.s4+t6.s5+t6.s6+t6.s7+t6.s8+t6.s9+t6.sa+t6.sb+t6.sc+t6.sd+t6.se+t6.sf 
  		+ t7.s0+t7.s1+t7.s2+t7.s3+t7.s4+t7.s5+t7.s6+t7.s7+t7.s8+t7.s9+t7.sa+t7.sb+t7.sc+t7.sd+t7.se+t7.sf;
}

__kernel void kernel_expm1_withDD1(__global float* result_expm1, int N)
{
  float t1 = 0.0;
  int i = 0;
  for(i = 0; i < 10 * N; i++) {
    repeat32(t1 = expm1(t1) - 1.0;);
  }
  *result_expm1 = t1;
}

__kernel void kernel_expm1_withDD2(__global float* result_expm1, int N)
{
  float2 t1 = 0.0+(float2)(0);
  int i = 0;
  for(i = 0; i < 10 * N; i++) {
    repeat32(t1 = expm1(t1) - 1.0;);
  }
  *result_expm1 = t1.s0 + t1.s1;
}

__kernel void kernel_expm1_withDD4(__global float* result_expm1, int N)
{
  float4 t1 = 0.0+(float4)(0);
  int i = 0;
  for(i = 0; i < 10 * N; i++) {
    repeat32(t1 = expm1(t1) - 1.0;);
  }
  *result_expm1 = t1.s0 + t1.s1 + t1.s2 + t1.s3;
}

__kernel void kernel_expm1_withDD8(__global float* result_expm1, int N)
{
  float8 t1 = 0.0+(float8)(0);
  int i = 0;
  for(i = 0; i < 10 * N; i++) {
    repeat32(t1 = expm1(t1) - 1.0;);
  }
  *result_expm1 = t1.s0 + t1.s1 + t1.s2 + t1.s3 + t1.s4 + t1.s5 + t1.s6 +t1.s7;
}

__kernel void kernel_expm1_withDD16(__global float* result_expm1, int N)
{
  float16 t1 = 0.0+(float16)(0);
  int i = 0;
  for(i = 0; i < 10 * N; i++) {
    repeat32(t1 = expm1(t1) - 1.0;);
  }
  *result_expm1 = t1.s0 + t1.s1 + t1.s2 + t1.s3 + t1.s4 + t1.s5 + t1.s6 +t1.s7+t1.s8+t1.s9+t1.sa+t1.sb+t1.sc+t1.sd+t1.se+t1.sf;
}

__kernel void kernel_expm1_withoutDD1(__global float* result_expm1, int N)
{
  float t1 = 1.2;
  float t2 = 1.2;
  float t3 = 1.2;
  float t4 = 1.2;
  float t5 = 1.2;
  float t6 = 1.2;
  float t7 = 1.2;
  float t8 = 1.2;
  float t9 = 1.2;
  float t10 = 1.2;

  float i = 1.0;
  float n = 0.07 * (float)(N);
  for(i = 1.0; i < n; i = i + 0.01) {

    t1 = expm1(i + 0.1);
    t2 = expm1(i + 0.2);
    t3 = expm1(i + 0.3);
    t4 = expm1(i + 0.4);
    t5 = expm1(i + 0.5);
    t6 = expm1(i + 0.6);
    t7 += expm1(i + 0.6);
    t8 += expm1(i + 0.7);
    t9 += expm1(i + 0.8);
    t10 += expm1(i + 0.9);
  }
  *result_expm1 = t1 + t2 + t3 + t4 + t5 + t6 + t7 + t8 + t9 + t10;
}

__kernel void kernel_expm1_withoutDD2(__global float* result_expm1, int N)
{
  float2 t1 = 1.2+(float2)(0);
  float2 t2 = 1.2+(float2)(0);
  float2 t3 = 1.2+(float2)(0);
  float2 t4 = 1.2+(float2)(0);
  float2 t5 = 1.2+(float2)(0);
  float2 t6 = 1.2+(float2)(0);
  float2 t7 = 1.2+(float2)(0);
  float2 t8 = 1.2+(float2)(0);
  float2 t9 = 1.2+(float2)(0);
  float2 t10 = 1.2+(float2)(0);

  float2 i = 1.0+(float2)(0);
  float2 j = 0.0+(float2)(0);
  float n = 0.07 * (float)(N);
  for(i.s0 = 1.0; i.s0 < n; i = i + 0.01) {

    t1 = expm1(i + 0.1);
    t2 = expm1(i + 0.2);
    t3 = expm1(i + 0.3);
    t4 = expm1(i + 0.4);
    t5 = expm1(i + 0.5);
    t6 = expm1(i + 0.6);
    t7 += expm1(i + 0.6);
    t8 += expm1(i + 0.7);
    t9 += expm1(i + 0.8);
    t10 += expm1(i + 0.9);
  }
  *result_expm1 = t1.s0+t1.s1 + t2.s0+t2.s1 + t3.s0+t3.s1 + t4.s0+t4.s1 + t5.s0+t5.s1 + t6.s0+t6.s1 + t7.s0+t7.s1 + t8.s0+t8.s1 + t9.s0+t9.s1+ t10.s0+t10.s1;
}

__kernel void kernel_expm1_withoutDD4(__global float* result_expm1, int N)
{
  float4 t1 = 1.2+(float4)(0);
  float4 t2 = 1.2+(float4)(0);
  float4 t3 = 1.2+(float4)(0);
  float4 t4 = 1.2+(float4)(0);
  float4 t5 = 1.2+(float4)(0);
  float4 t6 = 1.2+(float4)(0);
  float4 t7 = 1.2+(float4)(0);
  float4 t8 = 1.2+(float4)(0);
  float4 t9 = 1.2+(float4)(0);
  float4 t10 = 1.2+(float4)(0);

  float4 i = 1.0+(float4)(0);
  float4 j = 0.0+(float4)(0);
  float n = 0.07 * (float)(N);
  for(i.s0 = 1.0; i.s0 < n; i = i + 0.01) {

    t1 = expm1(i + 0.1);
    t2 = expm1(i + 0.2);
    t3 = expm1(i + 0.3);
    t4 = expm1(i + 0.4);
    t5 = expm1(i + 0.5);
    t6 = expm1(i + 0.6);
    t7 += expm1(i + 0.6);
    t8 += expm1(i + 0.7);
    t9 += expm1(i + 0.8);
    t10 += expm1(i + 0.9);
  }
  *result_expm1 = t1.s0+t1.s1+t1.s2+t1.s3 + t2.s0+t2.s1+t2.s2+t2.s3
	    	+ t3.s0+t3.s1+t3.s2+t3.s3 + t4.s0+t4.s1+t4.s2+t4.s3
		+ t5.s0+t5.s1+t5.s2+t5.s3 + t6.s0+t6.s1+t6.s2+t6.s3
		+ t7.s0+t7.s1+t7.s2+t7.s3 + t8.s0+t8.s1+t8.s2+t8.s3
		+ t9.s0+t9.s1+t9.s2+t9.s3 + t10.s0+t10.s1+t10.s2+t10.s3;
}

__kernel void kernel_expm1_withoutDD8(__global float* result_expm1, int N)
{
  float8 t1 = 1.2+(float8)(0);
  float8 t2 = 1.2+(float8)(0);
  float8 t3 = 1.2+(float8)(0);
  float8 t4 = 1.2+(float8)(0);
  float8 t5 = 1.2+(float8)(0);
  float8 t6 = 1.2+(float8)(0);
  float8 t7 = 1.2+(float8)(0);
  float8 t8 = 1.2+(float8)(0);
  float8 t9 = 1.2+(float8)(0);
  float8 t10 = 1.2+(float8)(0);

  float8 i = 1.0+(float8)(0);
  float8 j = 0.0+(float8)(0);
  float n = 0.07 * (float)(N);
  for(i.s0 = 1.0; i.s0 < n; i = i + 0.01) {

    t1 = expm1(i + 0.1);
    t2 = expm1(i + 0.2);
    t3 = expm1(i + 0.3);
    t4 = expm1(i + 0.4);
    t5 = expm1(i + 0.5);
    t6 = expm1(i + 0.6);
    t7 += expm1(i + 0.6);
    t8 += expm1(i + 0.7);
    t9 += expm1(i + 0.8);
    t10 += expm1(i + 0.9);
  }
  *result_expm1 = t1.s0+t1.s1+t1.s2+t1.s3+t1.s4+t1.s5+t1.s6+t1.s7
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

__kernel void kernel_expm1_withoutDD16(__global float* result_expm1, int N)
{
  float16 t1 = 1.2+(float16)(0);
  float16 t2 = 1.2+(float16)(0);
  float16 t3 = 1.2+(float16)(0);
  float16 t4 = 1.2+(float16)(0);
  float16 t5 = 1.2+(float16)(0);
  float16 t6 = 1.2+(float16)(0);
  float16 t7 = 1.2+(float16)(0);
  float16 t8 = 1.2+(float16)(0);
  float16 t9 = 1.2+(float16)(0);
  float16 t10 = 1.2+(float16)(0);

  float16 i = 1.0+(float16)(0);
  float16 j = 0.0+(float16)(0);
  float n = 0.07 * (float)(N);
  for(i.s0 = 1.0; i.s0 < n; i = i + 0.01) {

    t1 = expm1(i + 0.1);
    t2 = expm1(i + 0.2);
    t3 = expm1(i + 0.3);
    t4 = expm1(i + 0.4);
    t5 = expm1(i + 0.5);
    t6 = expm1(i + 0.6);
    t7 += expm1(i + 0.6);
    t8 += expm1(i + 0.7);
    t9 += expm1(i + 0.8);
    t10 += expm1(i + 0.9);
  }
  *result_expm1 = t1.s0+t1.s1+t1.s2+t1.s3+t1.s4+t1.s5+t1.s6+t1.s7+t1.s8+t1.s9+t1.sa+t1.sb+t1.sc+t1.sd+t1.se+t1.sf
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

__kernel void kernel_exp10_withDD1(__global float* result_exp10, int N)
{
  float t1 = 2.0;
  int i = 0;
  for(i = 0; i < N; i++) {
    repeat32(t1 = ext10((t1 + 0.1) / t1););
  }
  *result_exp10 = t1;
}

__kernel void kernel_exp10_withDD2(__global float* result_exp10, int N)
{
  float2 t1 = 2.0+(float2)(0); 

  int i = 0;
  for(i = 0; i < N; i++) {
    repeat32(t1 = ext10((t1 + 0.1) / t1););
  }
  *result_exp10 = t1.s0 + t1.s1;
}

__kernel void kernel_exp10_withDD4(__global float* result_exp10, int N)
{
  float4 t1 = 2.0+(float4)(0); 

  int i = 0;
  for(i = 0; i < N; i++) {
    repeat32(t1 = ext10((t1 + 0.1) / t1););
  }
  *result_exp10 = t1.s0 + t1.s1 + t1.s2 + t1.s3;
}

__kernel void kernel_exp10_withDD8(__global float* result_exp10, int N)
{
  float8 t1 = 2.0+(float8)(0); 

  int i = 0;
  for(i = 0; i < N; i++) {
    repeat32(t1 = ext10((t1 + 0.1) / t1););
  }
  *result_exp10 = t1.s0 + t1.s1 + t1.s2 + t1.s3 + t1.s4 + t1.s5 + t1.s6 +t1.s7;
}

__kernel void kernel_exp10_withDD16(__global float* result_exp10, int N)
{
  float16 t1 = 2.0+(float16)(0); 

  int i = 0;
  for(i = 0; i < N; i++) {
    repeat32(t1 = ext10((t1 + 0.1) / t1););
  }
  *result_exp10 = t1.s0 + t1.s1 + t1.s2 + t1.s3 + t1.s4 + t1.s5 + t1.s6 +t1.s7+t1.s8+t1.s9+t1.sa+t1.sb+t1.sc+t1.sd+t1.se+t1.sf;
}

__kernel void kernel_exp10_withoutDD1(__global float* result_exp10, int N)
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

  float k1 = 0.1;
  float k2 = 0.2;
  float k3 = 0.3;
  float k4 = 0.4;
  float k5 = 0.5;
  float k6 = 0.6;
  float k7 = 0.7;
  float k8 = 0.8;
  float k9 = 0.9;
  float k10 = 0.11;

  float i = 0.0;
  float n = 7 * (float)(N);
  for(i = 0.0; i < n; i = i + 1.0) {
    t1 += exp10(-(i + k1) / i);
    t2 += exp10(-(i + k2) / i);
    t3 += exp10(-(i + k3) / i);
    t4 += exp10(-(i + k4) / i);
    t5 += ext10(-(i + k5) / i);
    t6 += exp10(-(i + k6) / i);
    t7 += exp10(-(i + k7) / i);
    t8 += exp10(-(i + k8) / i);
    t9 += exp10(-(i + k9) / i);
    t10 += exp10(-(i + k10) / i);
  }
  *result_exp10 = t1 + t2 + t3 + t4 + t5 + t6 + t7 + t8 + t9 + t10;
}

__kernel void kernel_exp10_withoutDD2(__global float* result_exp10, int N)
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

  float k1 = 0.1;
  float k2 = 0.2;
  float k3 = 0.3;
  float k4 = 0.4;
  float k5 = 0.5;
  float k6 = 0.6;
  float k7 = 0.7;
  float k8 = 0.8;
  float k9 = 0.9;
  float k10 = 0.11;

  float2 i = 0.0+(float2)(0);
  float n = 7 * (float)(N);
  for(i.s0 = 0; i.s0 < n; i = i + 1.0) {
    t1 += exp10(-(i + k1) / i);
    t2 += exp10(-(i + k2) / i);
    t3 += exp10(-(i + k3) / i);
    t4 += exp10(-(i + k4) / i);
    t5 += ext10(-(i + k5) / i);
    t6 += exp10(-(i + k6) / i);
    t7 += exp10(-(i + k7) / i);
    t8 += exp10(-(i + k8) / i);
    t9 += exp10(-(i + k9) / i);
    t10 += exp10(-(i + k10) / i);
  }
  *result_exp10 = t1.s0+t1.s1 + t2.s0+t2.s1 + t3.s0+t3.s1 + t4.s0+t4.s1 + t5.s0+t5.s1 + t6.s0+t6.s1 + t7.s0+t7.s1 + t8.s0+t8.s1 + t9.s0+t9.s1+ t10.s0+t10.s1;
}

__kernel void kernel_exp10_withoutDD4(__global float* result_exp10, int N)
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

  float k1 = 0.1;
  float k2 = 0.2;
  float k3 = 0.3;
  float k4 = 0.4;
  float k5 = 0.5;
  float k6 = 0.6;
  float k7 = 0.7;
  float k8 = 0.8;
  float k9 = 0.9;
  float k10 = 0.11;

  float4 i = 0+(float4)(0);
  float n = 7 * (float)(N);
  for(i.s0 = 0; i.s0 < n; i = i + 1.0) {
    t1 += exp10(-(i + k1) / i);
    t2 += exp10(-(i + k2) / i);
    t3 += exp10(-(i + k3) / i);
    t4 += exp10(-(i + k4) / i);
    t5 += ext10(-(i + k5) / i);
    t6 += exp10(-(i + k6) / i);
    t7 += exp10(-(i + k7) / i);
    t8 += exp10(-(i + k8) / i);
    t9 += exp10(-(i + k9) / i);
    t10 += exp10(-(i + k10) / i);
  }
  *result_exp10 = t1.s0+t1.s1+t1.s2+t1.s3 + t2.s0+t2.s1+t2.s2+t2.s3
	    	+ t3.s0+t3.s1+t3.s2+t3.s3 + t4.s0+t4.s1+t4.s2+t4.s3
		+ t5.s0+t5.s1+t5.s2+t5.s3 + t6.s0+t6.s1+t6.s2+t6.s3
		+ t7.s0+t7.s1+t7.s2+t7.s3 + t8.s0+t8.s1+t8.s2+t8.s3
		+ t9.s0+t9.s1+t9.s2+t9.s3 + t10.s0+t10.s1+t10.s2+t10.s3;
}

__kernel void kernel_exp10_withoutDD8(__global float* result_exp10, int N)
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

  float k1 = 0.1;
  float k2 = 0.2;
  float k3 = 0.3;
  float k4 = 0.4;
  float k5 = 0.5;
  float k6 = 0.6;
  float k7 = 0.7;
  float k8 = 0.8;
  float k9 = 0.9;
  float k10 = 0.11;

  float8 i = 0+(float8)(0);
  float n = 7 * (float)(N);
  for(i.s0 = 0; i.s0 < n; i = i + 1.0) {
    t1 += exp10(-(i + k1) / i);
    t2 += exp10(-(i + k2) / i);
    t3 += exp10(-(i + k3) / i);
    t4 += exp10(-(i + k4) / i);
    t5 += ext10(-(i + k5) / i);
    t6 += exp10(-(i + k6) / i);
    t7 += exp10(-(i + k7) / i);
    t8 += exp10(-(i + k8) / i);
    t9 += exp10(-(i + k9) / i);
    t10 += exp10(-(i + k10) / i);
  }
  *result_exp10 = t1.s0+t1.s1+t1.s2+t1.s3+t1.s4+t1.s5+t1.s6+t1.s7
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

__kernel void kernel_exp10_withoutDD16(__global float* result_exp10, int N)
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

  float k1 = 0.1;
  float k2 = 0.2;
  float k3 = 0.3;
  float k4 = 0.4;
  float k5 = 0.5;
  float k6 = 0.6;
  float k7 = 0.7;
  float k8 = 0.8;
  float k9 = 0.9;
  float k10 = 0.11;

  float16 i = 0+(float16)(0);

  float n = 7 * (float)(N);
  for(i.s0 = 0; i.s0 < n; i = i + 1.0) {
    t1 += exp10(-(i + k1) / i);
    t2 += exp10(-(i + k2) / i);
    t3 += exp10(-(i + k3) / i);
    t4 += exp10(-(i + k4) / i);
    t5 += ext10(-(i + k5) / i);
    t6 += exp10(-(i + k6) / i);
    t7 += exp10(-(i + k7) / i);
    t8 += exp10(-(i + k8) / i);
    t9 += exp10(-(i + k9) / i);
    t10 += exp10(-(i + k10) / i);
  }
  *result_exp10 = t1.s0+t1.s1+t1.s2+t1.s3+t1.s4+t1.s5+t1.s6+t1.s7+t1.s8+t1.s9+t1.sa+t1.sb+t1.sc+t1.sd+t1.se+t1.sf
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


