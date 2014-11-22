#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <fstream>
#include <stdlib.h>

#define ARRAY_SIZE 65536
#define NUM_THREADS 256

float a[ARRAY_SIZE];
float b[ARRAY_SIZE];
float c[ARRAY_SIZE];
int g_index = 0;

void* slave (void* index)
{
	int partsum =0;
	int localindex = (int) index * ARRAY_SIZE/NUM_THREADS;
	int i;
	for(int j=0;j<1000;j++){
		for(i=0; i< ARRAY_SIZE/NUM_THREADS; i++)
			c[localindex+i] =a[localindex+i]+b[localindex+i];
	}
}

int main ()
{
	int i;
	pthread_t thread[NUM_THREADS];
	
	for (i=0;i<ARRAY_SIZE;i++){
		a[i]=i+1;
		b[i]=i+1;
	}
	double time=0;
	int circle;
for(circle=0;circle<100;circle++){
	for (i=0;i<NUM_THREADS;i++)
	{
		if(pthread_create(&thread[i], NULL, slave, (void*)i))
			perror("Pthread Create Fails");
	}
 	struct timeval tStart, tEnd;
	gettimeofday(&tStart, NULL);
	for (i=0;i<NUM_THREADS;i++)
	{
		if(pthread_join(thread[i], NULL))
			perror("Pthread Join Fails");
	}
	gettimeofday(&tEnd, NULL);
 	time+=(tEnd.tv_sec - tStart.tv_sec) * 1000 + (tEnd.tv_usec - tStart.tv_usec) / (float)1000; 
}
  	printf("NUM_THREADS:%d\t Time:%.3f ms\n",NUM_THREADS,time);
	printf("--------------------------------------------------\n");
	//for (i=0;i<ARRAY_SIZE;i++)
	//	printf("%f\t",c[i]);
	
	return 0;
}

//g++ vector_add.cpp -lpthread -o vector_add
//./vector_add
