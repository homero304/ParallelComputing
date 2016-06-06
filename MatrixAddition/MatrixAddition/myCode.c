#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
DWORD WINAPI threadRoutine(LPVOID p) {
	int *myStartingRowIndx = (int *)p;
	int i,j;
	int rowOffset = *myStartingRowIndx*dimension;
	for (i=0;i<dimension;i++) 
		for (j=0;j<amountOfRowsPerThread;j++) {
			C[rowOffset+i*dimension+j]=A[rowOffset+i*dimension+j]+B[rowOffset+i*dimension+j];
		}	
	
}
const int dimension=5000;
int *A=NULL;
int *B=NULL;
int *C=NULL;
int main() {
	int i,j;
	int result=1;
	time_t start,end;

	size_t datasize=sizeof(int)*dimension*dimension;
	A=(int *)malloc(datasize);
	B=(int *)malloc(datasize);
	C=(int *)malloc(datasize);

	for (i=0;i<dimension;i++)
		for (j=0;j<dimension;j++) {
			A[i*dimension+j]=i+j;
			B[i*dimension+j]=i+j;
		}
	
	start=clock();
	for (i=0;i<dimension;i++)
		for (j=0;j<dimension;j++)
			
	end=clock();

	for (i=0;i<dimension;i++) 
		for (j=0;j<dimension;j++) {
			if(C[i*dimension+j]!=((i+j)*2)) {
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
