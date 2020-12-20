//
// Created by Jichen Dai on 12/20/20.
//

#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "builtins.h"

int
cd(size_t argc, char **argv) {
    argc = argc;
    argv = argv;
    return 0;
}


int
echo(size_t argc, char **argv, int retcode) {
    argc = argc;
    argv = argv;
    retcode = 0;
    return 0;
}
