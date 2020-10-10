#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF_SIZE 50

int main() {
	int f = open("/proc/self/stat", O_RDONLY);
	char buf[BUF_SIZE];
	read(f, buf, BUF_SIZE);
	close(f);
	int ppid;
	char dummy[BUF_SIZE];
	sscanf(buf, "%d %s %s %d", &ppid, dummy, dummy, &ppid);
	printf("%d\n", ppid);
	return 0;
}