#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <dlfcn.h>
#include <stdlib.h>

int (*someSecretFunctionPrototype)(int );

bool init_library(const char *libname, const char *funcname) {
    void *hdl = dlopen(libname, RTLD_LAZY);
    if (hdl == NULL) {return false;}
    someSecretFunctionPrototype = (int (*)(int ))dlsym(hdl, funcname);
    if (someSecretFunctionPrototype == NULL) {return false;}
    return true;
}

int main(int argc, char **argv) {
    if (init_library(argv[1], argv[2])) {
        printf("%d\n", someSecretFunctionPrototype(atoi(argv[3])));
    }
    else {
        printf("Error\n");
    }
    return 0;
}