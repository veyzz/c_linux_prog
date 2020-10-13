#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void sigurg(int signo) {
	exit(0);
}

int main() {
	pid_t pid = fork();
	if (pid) {
		printf("%d\n", pid);
		return 0;
	}
	chdir("/");
	setsid();
	close(fileno(stdin));
	close(fileno(stdout));
	close(fileno(stderr));
	signal(SIGURG, sigurg);
	while (1);
	return 0;
}
