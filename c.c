
#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char **argv, char **envp) {
	char *ls = *argv;
	for (char *c = *argv; *c; ++c) {
		if (*c == '/') ls = c+1;
	}
	if (*ls == 'c' && *(ls+1)) {
		for ( ; *ls ; ++ls ) {
			*ls = *(ls+1);
		}
		int rv = INT_MIN;
		for (char **cp = envp; *cp; ++cp) {
			if (0 == strncmp(*cp, "DOLLARSIGN_QUESTIONMARK_ALL_SPELLED_OUT=", 39)) {
				rv = atoi(*cp + 40);
			}
		}
		if (rv == INT_MIN) {
			rv = 0;
			//variable was not set, check kernel support:
			int fd = open("/proc/flags/cf", O_RDONLY);
			if (fd != -1) {
				char c;
				if (read(fd, &c, 1) == 1 && c == '1') {
					rv = 1;
				}
			}
		}
		if (rv == 0) {
			if (!fork()) {
				execvpe(*argv, argv, envp);
				printf("c error executing '%s': %s\n", *argv, strerror(errno));
				return 0;
			}
			wait(NULL);
		}
		return rv;
	} else {
		puts(
			"Usage:\n"
			"    If called as `cNNN ...`:\n"
			"        If DOLLARSIGN_QUESTIOMARK_ALL_SPELLED_OUT is set...\n"
			"            ...and zero:\n"
			"                runs `NNN ...` and returns 0\n"
			"            ...otherwise:\n"
			"                returns DOLLARSIGN_QUESTIONMARK_ALL_SPELLED_OUT\n"
			"        Otherwise if /proc/flags/cf exists and does not contain '1':\n"
			"            runs `NNN ...` and returns 0\n"
			"        Otherwise:\n"
			"            returns 0\n"
			"    Otherwise: prints this message and return 0."
		);
	}
	return 0;
}
