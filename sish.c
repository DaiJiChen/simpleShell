#ifdef __linux__
#include <bsd/stdlib.h>
#include <bsd/string.h>
#endif

#include <sys/stat.h>
#include <sys/wait.h>

#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "builtins.h"

#define UNUSED(x) (void)(x)


int x_flag;
int retcode;
int is_executing; // whether sish is executing a command


// diff: didn't fully implement
static void
handle_SIGINT(int signo) {

    UNUSED(signo); // ignore unused parameter warning

    (void)printf("\n");

    if (!is_executing) {
        printf("%s$ ", getprogname());
        if (fflush(stdout) == EOF) {
            err(EXIT_FAILURE, "fflush");
        }
    }
}

static char *
prompt(char *buffer, size_t buffer_size) {
    printf("%s$ ", getprogname());
    return fgets(buffer, buffer_size, stdin);
}


int
main(int argc, char *argv[]) {
    char progpath[PATH_MAX + 1];
    char *command;
    char opt;

    setprogname(argv[0]); //diff: try to remove this line  and replace all getprogname with "sish$"

    if (realpath(getprogname(), progpath) == NULL) {
        err(EXIT_FAILURE, "realpath");
    }

    if (setenv("SHELL", progpath, 1) == -1) {
        err(EXIT_FAILURE, "setenv");
    }

    if (signal(SIGINT, handle_SIGINT) == SIG_ERR) {
        err(EXIT_FAILURE, "signal error");
    }

    command = NULL;
    while ((opt = getopt(argc, argv, "xc:")) != -1) {
        switch (opt) {
            case 'x':
                x_flag = 1;
                break;
            case 'c':
                command = optarg;
                break;
            default:
                (void)fprintf(stderr, "usage: %s [-x] [-c command]\n",
                              getprogname());
                exit(EXIT_FAILURE);
        }
    }

    if (command == NULL) {
        char input[BUFSIZ];
        while (prompt(input, sizeof(input)) != NULL) {
            input[strlen(input) - 1] = '\0'; // overwrite newline character
            //execute(input);
            printf("input is: %s \n", input);
        }
    } else {
        //execute(command);
        printf("command is: %s \n", command);
    }

    return retcode; //diff
}

