#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define PNAME "(genenv)"
#define BUF_SIZE 50

int main() {
	char buf[BUF_SIZE];
	char stat_file[256];
	char pname[256];
	int pid, count = 0;
	DIR * dir = opendir("/proc/");
	struct dirent * entry;
	while ((entry = readdir(dir)) != NULL) {
		if (entry->d_type != DT_DIR) {
			continue;
		}
		pid = -1;
		sscanf(entry->d_name, "%d", &pid);
		if (pid == -1) {
			continue;
		}
		sprintf(stat_file, "/proc/%d/%s", pid, "stat");
		int f = open(stat_file, O_RDONLY);
		read(f, buf, BUF_SIZE);
		sscanf(buf, "%d %s", &pid, pname);
		if (pname == PNAME) {
			++count;
		}
	}
	printf("%d\n", count);
	return 0;
}