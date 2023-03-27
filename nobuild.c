#define NOBUILD_IMPLEMENTATION
#include "./nobuild.h"

#define CFLAGS "-Wall", "-Wextra", "-Werror", "-std=c99"
#define COMPILER "cc"
#define BUILD_DIR "build"
#define BUILD_PATH(path) BUILD_DIR "/" path

void compile_programs() 
{
    CMD(COMPILER, CFLAGS, "-o", BUILD_PATH("hello"), "hello.c");
}

void clean_output_exes()
{
    CMD("rm", "-f", BUILD_PATH("hello"));
}

void run_programs()
{
    CMD(BUILD_PATH("hello"));
}

int main(int argc, char **argv)
{
    GO_REBUILD_URSELF(argc, argv);
    MKDIRS(BUILD_DIR);
    compile_programs();
    run_programs();
    clean_output_exes();
    return 0;
}