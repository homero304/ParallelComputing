#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
DWORD WINAPI myThreadRoutine(LPVOID parameter);
const int elements=50000000;
#define nOfThreads 8
typedef struct threadRoutineParameters {
int *A;	
int *B;
int *C;
int indx;
};
int main() {
int *A=NULL;	
int *B=NULL;
int *C=NULL;
	int i;
	int result=1;
	time_t start,end;
	int vIs[nOfThreads]; 
 	HANDLE vtHandle[nOfThreads]; 
	size_t datasize=sizeof(int)*elements;

	A=(int *)malloc(datasize);
	B=(int *)malloc(datasize);
	C=(int *)malloc(datasize);

	for (i=0;i<elements;i++) {
		A[i]=i;
		B[i]=i;
	}
	
	start=clock();
	for (i=0;i<nOfThreads;i++) {
		vIs[i] = i;
		vtHandle[i] = CreateThread(NULL, 0, &myThreadRoutine, &vIs[i] , 0,NULL);
		//C[i]=A[i]+B[i];
	}
	WaitForMultipleObjects(nOfThreads,&vtHandle[0], TRUE, INFINITE);
	end=clock();

	for (i=0;i<elements;i++) {
		if(C[i]!=i+i) {
			result=0;
			break;
		}
	}
	if(result) {
		printf("Results verified!!! (%ld)\n",end-start);
	} else {
		printf("Wrong results!!!\n");
	}
	free(A);
	free(B);
	free(C);

	return 0;
}
DWORD WINAPI myThreadRoutine(LPVOID parameter) { 
 	int *myThreadNumber = (int *) parameter;
	threadRoutineParameters myParameters = (threadRoutineParameters *)parameter;
	int i;
	int local = (elements/nOfThreads)*(*myThreadNumber);

 	for (i=0;i<elements/nOfThreads;i++) { 
		C[i+local]=A[i+local]+B[i+local];
	}
 } 
