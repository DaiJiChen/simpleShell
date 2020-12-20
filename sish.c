#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "builtins.h"

/* constants */
int MAX_COMMAND_LEN = 512;

/* global var */
int is_executing;
int x_flag;
char *command;

void handle_SIGINT(int sigNo) {
    sigNo = sigNo;
    printf("\n");
}

void parse_opt(int argc, char *argv[]) {
    char opt;
    while ((opt = getopt(argc, argv, "cx:")) != -1) {
        switch (opt) {
            case 'x':
                x_flag = 1;
                break;
            case 'c':
                command = optarg;
                break;
            default:
                fprintf(stderr, "usage: %s [-x] [-c command]\n", "./sish");
                exit(EXIT_FAILURE);
        }
    }
}

int main(int argc, char *argv[]) {;
    char input[MAX_COMMAND_LEN];
    char path[PATH_MAX];

    printf("PASS");

    if(realpath(argv[0], path) == NULL) {
        fprintf(stderr, "cannot solve path");
        exit(EXIT_FAILURE);
    }

    printf("PASS");

    setprogname("sish");

    if(setenv("myShell", path, 1) == -1) {
        fprintf(stderr, "cannot solve path");
        exit(EXIT_FAILURE);
    }

    printf("PASS");

    /* change the behavior of interrupt signal */
    if(signal(SIGINT, handle_SIGINT) == SIG_ERR) {
        fprintf(stderr, "failed to handle SIGINT");
        exit(EXIT_FAILURE);
    }

    printf("PASS");

    command = NULL;
    parse_opt(argc, argv);

    printf("PASS");

    if(command != NULL) {
        //execute(command);
        printf("%s \n", command);
    }
    else {
        printf("%s$ ", getprogname());
        while (fgets(input, sizeof(input), stdin)!= NULL) {
            printf("%s$ ", getprogname());
            input[strlen(input) - 1] = '\0'; // overwrite newline character
            //execute(input);
            printf("%s \n", command);
        }
    }

    return EXIT_SUCCESS;
}
