#include <stdio.h>
#include <time.h>
#include <Windows.h>
long cantidadIntervalos = 1000000000;
double baseIntervalo;
CRITICAL_SECTION cs;
double acum;
long nOfBlocksPerThread;
clock_t start,end;
DWORD WINAPI threadRoutine(LPVOID);
void main() {
	int num1=0, num2=1;
	int nOfThreads=2;
	HANDLE th1, th2;
	baseIntervalo = 1.0/cantidadIntervalos;
	start = clock();
	InitializeCriticalSection(&cs);
	nOfBlocksPerThread = cantidadIntervalos/nOfThreads;
	th1 = CreateThread(NULL, 0, &threadRoutine, &num1, 0, NULL);
	th2 = CreateThread(NULL, 0, &threadRoutine, &num2, 0, NULL);
	WaitForSingleObject(th1, INFINITE);
	WaitForSingleObject(th2, INFINITE);
	DeleteCriticalSection(&cs);
	end=clock();
	printf("Resultado = %20.18lf (%ld)\n",acum,end-start);
}
DWORD WINAPI threadRoutine(LPVOID param) {
	int *myThreadNumber = (int *)param;
	double fdx;
	double x;
	long i;
	double localAcum = 0.0;
	if(*myThreadNumber == 0) {
		x = 0;
	}
	else {
		x = 0.5;
	}
	printf("MyThreadNumber is ... %d\n", *myThreadNumber);
	for (i=0;i<nOfBlocksPerThread;i++) {
		fdx=4/(1+x*x);
		localAcum =localAcum+(fdx*baseIntervalo);
		x=x+baseIntervalo;
	}
	EnterCriticalSection(&cs);
	acum+=localAcum;
	LeaveCriticalSection(&cs);
}