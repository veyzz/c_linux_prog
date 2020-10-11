#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

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
	while (1);
	return 0;
}
