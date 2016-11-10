#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <sys/stat.h>

static void sigfxn(int s) {
	if (s == SIGINT) {
		umask(000);
		int fd = open("log.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);
		char *msg = "SIGINT exit\n";
		write(fd, msg, sizeof(char) * strlen(msg));
		close(fd);
		exit(-1);
	} else if (s == SIGUSR1) {
		printf("Parent PID: %d\n", getppid());
	}
}

int main() {
	signal(SIGINT, sigfxn);
	signal(SIGUSR1, sigfxn);

	while (1) {
		printf("PID: %d\n", getpid());
		sleep(1);
	}

	return 0;
}