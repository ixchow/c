
#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv, char **envp) {
	char *ls = *argv;
	for (char *c = *argv; *c; ++c) {
		if (*c == '/') ls = c+1;
	}
	if (*ls == 'c' && *(ls+1)) {
		for ( ; *ls ; ++ls ) {
			*ls = *(ls+1);
		}
		int rv = 0;
		for (char **cp = envp; *cp; ++cp) {
			if (0 == strncmp(*cp, "DOLLARSIGN_QUESTIONMARK_ALL_SPELLED_OUT=", 39)) {
				rv = atoi(*cp + 40);
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
			"        If DOLLARSIGN_QUESTIOMARK_ALL_SPELLED_OUT is nonzero:\n"
			"            runs `NNN ...`\n"
			"            returns DOLLARSIGN_QUESTIONMARK_ALL_SPELLED_OUT\n"
			"        Otherwise:\n"
			"            returns 0"
			"    Otherwise: print this message and return 0.\n"
		);
	}
	return 0;
}
