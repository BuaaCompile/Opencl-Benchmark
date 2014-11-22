/**********************************************************************
Copyright (c) 2014,BUAA COMPILER LAB;
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
- Neither the name of the BUAA COMPILER LAB; nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
********************************************************************/
__kernel void rowReadTest(__global const float* a, __global float* c, int iNumElements)
{
	int j = get_global_id(0); 
	int i = get_global_id(1); 
	volatile float tmp=1.0;
	for (int iy = 0; iy < 1; iy++) {
		
		for ( int i0=0;i0<iNumElements;i0++){
			tmp=a[i*1024+j*iNumElements+i0];//read
		}
	}		
}

__kernel void rowWriteTest(__global const float* a, __global float* c, int iNumElements)
{
	int j = get_global_id(0); 
	int i = get_global_id(1); 
	volatile float tmp=1.0;
	for (int iy = 0; iy < 1; iy++) {
		
		for ( int i0=0;i0<iNumElements;i0++){
			c[i*1024+j*1+i0]=tmp;
		}
	}		

}

__kernel void columnReadTest(__global const float* a, __global float* c, int iNumElements)
{
	int j = get_global_id(0); 
	int i = get_global_id(1); 
	volatile float tmp=1.0;

	for (int iy = 0; iy < 1; iy++) {
	 		
		for ( int i0=0;i0<iNumElements;i0++){
			tmp=a[(j*iNumElements+i0)*1024+i];
		}
	}
}

__kernel void columnWriteTest(__global const float* a, __global float* c, int iNumElements)
{
	int j = get_global_id(0); 
	int i = get_global_id(1); 
	volatile float tmp=1.0;
	for (int iy = 0; iy < 1; iy++) {
	 		
		for ( int i0=0;i0<iNumElements;i0++){
			c[(j*iNumElements+i0)*1024+i]=tmp; 
		}
	}

}


    
