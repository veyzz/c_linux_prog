#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int u1 = 0;
int u2 = 0;

void sigusr1(int signo) {
	u1++;
}

void sigusr2(int signo) {
	u2++;
}

void sigterm(int signo) {
	printf("%d %d\n", u1, u2);
	exit(0);
}

int main() {
	signal(SIGUSR1, sigusr1);
	signal(SIGUSR2, sigusr2);
	signal(SIGTERM, sigterm);
	while (1) {
		usleep(50000);
	}
	return 0;
}
