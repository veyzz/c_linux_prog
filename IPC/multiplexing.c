#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF_SIZE 16

int main() {
	int fds[2];

	if ((fds[0] = open("./in1", O_RDONLY | O_NONBLOCK)) < 0) {
		return 1;
	}
	if ((fds[1] = open("./in2", O_RDONLY | O_NONBLOCK)) < 0) {
		return 1;
	}

	int maxfd = fds[0] > fds[1] ? fds[0] : fds[1];

	fd_set read_fd, watch_fd;
	FD_ZERO(&watch_fd);
	FD_SET(fds[0], &watch_fd);
	FD_SET(fds[1], &watch_fd);

	char buf[BUF_SIZE];
	int bytes, num, summ = 0;
	

	while (FD_ISSET(fds[0], &watch_fd) || FD_ISSET(fds[1], &watch_fd)) {
		read_fd = watch_fd;

		if (select(maxfd + 1, &read_fd, NULL, NULL, NULL) < 0) {
			return 1;
		}

		for (int i = 0; i < 2; ++i) {
			if (FD_ISSET(fds[i], &read_fd)) {
				bytes = read(fds[i], buf, BUF_SIZE - 1);
				if (bytes < 0) {
					return 1;
				}
				if (!bytes) {
					FD_CLR(fds[i], &watch_fd);
					close(fds[i]);
				} else {
					sscanf(buf, "%d", &num);
					summ += num;
				}
			}
		}
	}
	printf("%d\n", summ);
	return 0;
}
