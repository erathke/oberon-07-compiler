#include <signal.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static jmp_buf* buf;

void setjmp_buf(jmp_buf *userbuf) {
	//printf("buf addr: %p\n", userbuf);
	buf = userbuf;
}

static void segfault_sigaction(int signal, siginfo_t *si, void *arg) {
	printf("Caught segfault at address %p, %p\n", si->si_addr, arg);
	//longjmp(*buf, 1);
	exit(0);
}

void setupCanary() {
	printf("setup canary... ");
	struct sigaction sa;
	memset(&sa, 0, sizeof(struct sigaction));
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = segfault_sigaction;
	sa.sa_flags   = SA_SIGINFO;
	if (sigaction(SIGSEGV, &sa, NULL) == -1) {
	} 
	else
		puts("done!");
}

/*
int main(void) {
	int *foo = NULL;
	jmp_buf buf;

	setjmp_buf(&buf);
	setupCanary();

	if (setjmp(buf) == 0) {
		// Cause a seg fault
		*foo = 1;
	} else {
		printf("back from the error!\n");
	}

	return 0;
}
*/
