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

int main(int argc, char *argv[]) {
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
        printf("command is: %s \n", command);
    }
    else {
        printf("%s$ ", getprogname());
        while (fgets(input, sizeof(input), stdin)!= NULL) {
            printf("%s$ ", getprogname());
            input[strlen(input) - 1] = '\0'; // overwrite newline character
            //execute(input);
            printf("input is: %s \n", input);
        }
    }

    return EXIT_SUCCESS;
}


//#ifdef __linux__
//#include <bsd/stdlib.h>
//#include <bsd/string.h>
//#endif
////diff
//
//#include <sys/stat.h>
//
//#include <err.h>
//#include <errno.h>
//#include <fcntl.h>
//#include <limits.h>
//#include <signal.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <unistd.h>
//#include <sys/wait.h>
//
//#include "builtins.h"
//
//#define UNUSED(x) (void)(x)
//#define MAX_TOKENS 256 // TODO: research system limits
//
//
//int x_flag;
//int retcode;
//int is_executing; // whether sish is executing a command
//
//static void handle_sigint(int);
//static char *prompt(char *, size_t);
//static void execute(char *);
//int main(int, char *[]);
//
//
//// diff: didn't fully implement
//static void
//handle_sigint(int signo) {
//
//    UNUSED(signo); // ignore unused parameter warning
//
//    (void)printf("\n");
//
//    if (!is_executing) {
//        printf("%s$ ", getprogname());
//        if (fflush(stdout) == EOF) {
//            err(EXIT_FAILURE, "fflush");
//        }
//    }
//}
//
//static char *
//prompt(char *buffer, size_t buffer_size) {
//    printf("%s$ ", getprogname());
//    return fgets(buffer, buffer_size, stdin);
//}
//
//
//int
//main(int argc, char *argv[]) {
//    char progpath[PATH_MAX + 1];
//    char *command;
//    char opt;
//
//    setprogname(argv[0]); //diff: try to remove this line  and replace all getprogname with "sish$"
//
//    if (realpath(getprogname(), progpath) == NULL) {
//        err(EXIT_FAILURE, "realpath");
//    }
//
//    if (setenv("SHELL", progpath, 1) == -1) {
//        err(EXIT_FAILURE, "setenv");
//    }
//
//    if (signal(SIGINT, handle_sigint) == SIG_ERR) {
//        err(EXIT_FAILURE, "signal error");
//    }
//
//    command = NULL;
//    while ((opt = getopt(argc, argv, "xc:")) != -1) {
//        switch (opt) {
//            case 'x':
//                x_flag = 1;
//                break;
//            case 'c':
//                command = optarg;
//                break;
//            default:
//                (void)fprintf(stderr, "usage: %s [-x] [-c command]\n",
//                              getprogname());
//                exit(EXIT_FAILURE);
//        }
//    }
//
//    if (command == NULL) {
//        char input[BUFSIZ];
//        while (prompt(input, sizeof(input)) != NULL) {
//            input[strlen(input) - 1] = '\0'; // overwrite newline character
//            execute(input);
//        }
//    } else {
//        //execute(command);
//        printf("command is: %s \n", command);
//    }
//
//    return retcode; //diff
//}
//
