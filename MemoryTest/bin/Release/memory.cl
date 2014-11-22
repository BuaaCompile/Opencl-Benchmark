/**********************************************************************
Copyright (c) 2014,BUAA COMPILER LAB;
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
- Neither the name of the BUAA COMPILER LAB; nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
********************************************************************/
__kernel void readGlobalMemory(__global float *data, __global float *output, int size,int stride)
{
    int gid = get_global_id(0);
    int j = 0;
    float sum = 0;
    int s = gid * stride;
    for (j=0 ; j<1024 ; ++j) {
       float a0 = data[(s+0)&(size-1)];
       float a1 = data[(s+15360)&(size-1)];
       float a2 = data[(s+30720)&(size-1)];
       float a3 = data[(s+46080)&(size-1)];
       float a4 = data[(s+61440)&(size-1)];
       float a5 = data[(s+76800)&(size-1)];
       float a6 = data[(s+92160)&(size-1)];
       float a7 = data[(s+107520)&(size-1)];
       float a8 = data[(s+122880)&(size-1)];
       float a9 = data[(s+138240)&(size-1)];
       float a10 = data[(s+153600)&(size-1)];
       float a11 = data[(s+168960)&(size-1)];
       float a12 = data[(s+184320)&(size-1)];
       float a13 = data[(s+199680)&(size-1)];
       float a14 = data[(s+215040)&(size-1)];
       float a15 = data[(s+230400)&(size-1)];
       sum += a0+a1+a2+a3+a4+a5+a6+a7+a8+a9+a10+a11+a12+a13+a14+a15;
       s = (s+245760)&(size-1);
    }
    output[gid] = sum;
}

__kernel void writeGlobalMemory(__global float *output, int size, int stride)
{
    int gid = get_global_id(0);
    int j = 0;
    int s = gid * stride;
    for (j=0 ; j<1024 ; ++j) {
      output[(s+0)&(size-1)] = gid;
       output[(s+15360)&(size-1)] = gid;
       output[(s+30720)&(size-1)] = gid;
       output[(s+46080)&(size-1)] = gid;
       output[(s+61440)&(size-1)] = gid;
       output[(s+76800)&(size-1)] = gid;
       output[(s+92160)&(size-1)] = gid;
       output[(s+107520)&(size-1)] = gid;
       output[(s+122880)&(size-1)] = gid;
       output[(s+138240)&(size-1)] = gid;
       output[(s+153600)&(size-1)] = gid;
       output[(s+168960)&(size-1)] = gid;
       output[(s+184320)&(size-1)] = gid;
       output[(s+199680)&(size-1)] = gid;
       output[(s+215040)&(size-1)] = gid;
       output[(s+230400)&(size-1)] = gid;
       s = (s+245760)&(size-1);
    }
}

__kernel void readLocalMemory(__global const float *data, __global float *output, int size, 
							  int stride)
{
    int gid = get_global_id(0), num_thr = get_global_size(0), grpid=get_group_id(0), j = 0;
    float sum = 0;
    int tid=get_local_id(0), localSize=get_local_size(0), litems=4096/localSize, goffset=localSize*grpid+tid*litems;
    int s = tid;
    __local float lbuf[4096];
    for ( ; j<litems && j<(size-goffset) ; ++j)
       lbuf[tid*litems+j] = data[goffset+j];
    for (int i=0 ; j<litems ; ++j,++i)
       lbuf[tid*litems+j] = data[i];
    barrier(CLK_LOCAL_MEM_FENCE);
    for (j=0 ; j<3000 ; ++j) {
       float a0 = lbuf[(s*2+0)&(4095)];
       float a1 = lbuf[(s*2+1)&(4095)];
       float a2 = lbuf[(s*2+2)&(4095)];
       float a3 = lbuf[(s*2+3)&(4095)];
       float a4 = lbuf[(s*2+4)&(4095)];
       float a5 = lbuf[(s*2+5)&(4095)];
       float a6 = lbuf[(s*2+6)&(4095)];
       float a7 = lbuf[(s*2+7)&(4095)];
       float a8 = lbuf[(s*2+8)&(4095)];
       float a9 = lbuf[(s*2+9)&(4095)];
       float a10 = lbuf[(s*2+10)&(4095)];
       float a11 = lbuf[(s*2+11)&(4095)];
       float a12 = lbuf[(s*2+12)&(4095)];
       float a13 = lbuf[(s*2+13)&(4095)];
       float a14 = lbuf[(s*2+14)&(4095)];
       float a15 = lbuf[(s*2+15)&(4095)];
       sum += a0+a1+a2+a3+a4+a5+a6+a7+a8+a9+a10+a11+a12+a13+a14+a15;
       s = (s+16)&(4095);
    }
    output[gid] = sum;
}



__kernel void writeLocalMemory(__global float *output, 
							  int size, 
							  int stride)
{
    int gid = get_global_id(0);
	int j = 0;
    int tid=get_local_id(0), localSize=get_local_size(0), litems=2048/localSize;
    int s = tid;
	int baseIndex = (s>>4)<<4; 
    __local float lbuf[2048];

    for (j=0 ; j<3000 ; ++j)
    {
       lbuf[(stride*s+baseIndex+0)&(2047)] = gid;
       lbuf[(stride*s+baseIndex+1)&(2047)] = gid;
       lbuf[(stride*s+baseIndex+2)&(2047)] = gid;
       lbuf[(stride*s+baseIndex+3)&(2047)] = gid;
       lbuf[(stride*s+baseIndex+4)&(2047)] = gid;
       lbuf[(stride*s+baseIndex+5)&(2047)] = gid;
       lbuf[(stride*s+baseIndex+6)&(2047)] = gid;
       lbuf[(stride*s+baseIndex+7)&(2047)] = gid;
       lbuf[(stride*s+baseIndex+8)&(2047)] = gid;
       lbuf[(stride*s+baseIndex+9)&(2047)] = gid;
       lbuf[(stride*s+baseIndex+10)&(2047)] = gid;
       lbuf[(stride*s+baseIndex+11)&(2047)] = gid;
       lbuf[(stride*s+baseIndex+12)&(2047)] = gid;
       lbuf[(stride*s+baseIndex+13)&(2047)] = gid;
       lbuf[(stride*s+baseIndex+14)&(2047)] = gid;
       lbuf[(stride*s+baseIndex+15)&(2047)] = gid;
       s = (s+16)&(2047);
    }
    barrier(CLK_LOCAL_MEM_FENCE);
    for (j=0 ; j<litems ; ++j)
       output[gid] = lbuf[tid];
}

const sampler_t smplr = CLK_NORMALIZED_COORDS_FALSE | CLK_ADDRESS_NONE | CLK_FILTER_NEAREST;

// Simple Repeated Read from texture memory
__kernel void readImg2D(__read_only image2d_t img, 
						__global float *d_out, 
						int n,
						int width)
{
	
    int idx_x = get_global_id(0);
    int idx_y = get_global_id(1);
    int localsizex = get_local_size(0);
    int localsizey = get_local_size(1);
    int out_idx = idx_y * (localsizex * localsizey)  + idx_x;
    float sum = 0.0f;

	float4 v;	
	int2 coord;
	coord.y = idx_y;
	coord.x = idx_x;


    //int width_bits = width-1;
    for (int i = 0; i < n; i++)
    {
         v = read_imagef(img, smplr, coord);
		 sum += v.x;
    }
    d_out[out_idx] = sum;
	
}


// Simple Repeated Write from texture memory
__kernel void writeImg2D(__write_only image2d_t img, 
						int n)
{
	
    int idx_x = get_global_id(0);
    int idx_y = get_global_id(1);
	int localsizex = get_local_size(0);
	int localsizey = get_local_size(1);
    int out_idx = idx_y * (localsizex * localsizey)  + idx_x;
    float sum = 0.0f;
	
	float4 v = (float4)((float)idx_x, (float)idx_y, (float)out_idx, sum);	
	int2 coord;
	coord.y = idx_y;
	coord.x = idx_x;

    for (int i = 0; i < n; i++)
    {
		write_imagef(img, coord, v);
    }
	
}

