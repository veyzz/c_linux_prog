#include <stdio.h>

#define CMD_SIZE 256

int main(int argc, char * argv[]) {
	char cmd[CMD_SIZE];
	if (argc != 3) {
		return 1;
	}
	sprintf(cmd, "%s %s", argv[1], argv[2]);
	FILE * pipe = popen(cmd, "r");
	int count = 0;
	char c;
	while ((c = fgetc(pipe)) != EOF) {
		if (c == '0') {
			count++;
		}
	}
	printf("%d\n", count);
	pclose(pipe);
	return 0;
}
