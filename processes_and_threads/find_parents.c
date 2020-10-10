#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF_SIZE 50

int main(int argc, char *argv[]) {
	int pid, ppid = 1;
	char path[256];
	sprintf(path, "/proc/%s/stat", argv[1]);
	char buf[BUF_SIZE], dummy[BUF_SIZE];
	while (ppid) {
		int f = open(path, O_RDONLY);
		read(f, buf, BUF_SIZE);
		close(f);
		sscanf(buf, "%d %s %s %d", &pid, dummy, dummy, &ppid);
		printf("%d\n", pid);
		sprintf(path, "/proc/%d/stat", ppid);
	}
	return 0;
}