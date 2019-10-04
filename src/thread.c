#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <pthread.h>

#include "devel.h"
#include "thread.h"

void *ThreadReadSTDINFunc(void *argp) {
	char *buffer;
	size_t bufsz;
	while (!mainloop_end) {
		getline(&buffer, &bufsz, stdin);
		if (buffer[0] == '\n')
			continue;
		else
			buffer[strlen(buffer)-1] = '\0';

		if (strcmp(buffer, "exit")==0 || strcmp(buffer, "quit")==0 || strcmp(buffer, "qw")==0)
			mainloop_end = 1;
	}

	return NULL;
}

void ThreadReadSTDINStart(void) {
	pthread_t thr;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&thr, &attr, ThreadReadSTDINFunc, NULL);
	pthread_detach(thr);
	pthread_attr_destroy(&attr);
}

