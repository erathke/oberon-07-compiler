#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>

typedef void (*Callee)(int);

static jmp_buf cpus[10];
static int cpusCount;


static void pushCPU() {
	cpusCount++;
}

static void popCPU() {
	cpusCount--;
}


jmp_buf* getCurrentCPU() {
	return &cpus[cpusCount];
}

static void pcall(int *err, Callee func, int param) {
	pushCPU();
	jmp_buf *cpu = getCurrentCPU();
	
	if (setjmp(*cpu) == 0) {
		func(param);
		*err = 0;
	}
	else {
		*err = 1 + cpusCount;	
	}
	
	popCPU();
}

void showException(int err) {
	if (err > 0) {
		printf("error code: %d\n", err);
	}
}

static void divErr(int param) {
	puts("division error");
	jmp_buf *cpu = getCurrentCPU();
	longjmp(*cpu, 1);
}


static void assertErr(int param) {
	puts("assert passed!");
	
	int err;
	pcall(&err, divErr, 10);
	showException(err);
	
	jmp_buf *cpu = getCurrentCPU();
	longjmp(*cpu, 1);
}



int main() {
	cpusCount = -1;
	
	int err;
	pcall(&err, assertErr, 10);
	showException(err);
	
	return 0;
}
