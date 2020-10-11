#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUF_SIZE 1024
#define NUM_SIZE 16

int count = 0;

void clear (char * numb) {
	int i;
	for (i = 0; i < NUM_SIZE; ++i) {
		numb[i] = '\0';
	}
}

void count_children(int pid) {
	count++;
	char path[256];
	sprintf(path, "/proc/%d/task/%d/children", pid, pid);
	char buf[BUF_SIZE];
	int f = open(path, O_RDONLY);
	if (read(f, buf, BUF_SIZE) == 0) {
		return;
	}
	close(f);
	int chpid;
	int i = 0;
	int j = 0;
	char numb[NUM_SIZE];
	while (buf[i] != '\0') {
		if (buf[i] == ' ') {
			j = 0;
			sscanf(numb, "%d", &chpid);
			clear(numb);
			count_children(chpid);
		}
		numb[j++] = buf[i++];
	}
}

int main(int argc, char *argv[]) {
	int pid;
	sscanf(argv[1], "%d", &pid);
	count_children(pid);
	printf("%d\n", count);
	return 0;
}
