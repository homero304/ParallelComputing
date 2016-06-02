#include <stdio.h>
#include <Windows.h>
DWORD WINAPI myThreadRoutine(LPVOID);
void main() {
	int i;
	int vIs[8];
	HANDLE vtHandle[8];
	for(i=0;i<8;i++) {
		vIs[i] = i;
		vtHandle[i] = CreateThread(NULL, 0, &myThreadRoutine, &vIs[i] , 0,NULL);
	}
	WaitForMultipleObjects(8,&vtHandle[0], TRUE, INFINITE);
	//for(i=0;i<8;i++) {
	//	WaitForSingleObject(vtHandle[i], INFINITE);
	//}
	printf("hello there single threaded\n");
}
DWORD WINAPI myThreadRoutine(LPVOID parameter) {
	int *myThreadNumber = (int *) parameter;
	printf(">>>hello, I am the Thread #%d\n", *myThreadNumber);
}