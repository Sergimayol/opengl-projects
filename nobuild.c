#define NOBUILD_IMPLEMENTATION
#include "./nobuild.h"

#define CFLAGS "-Wall", "-Wextra", "-Werror", "-std=c99", "-lglut", "-lGLU", "-lGL"
#define COMPILER "gcc"
#define BUILD_DIR "build"
#define BUILD_PATH(path) BUILD_DIR "/" path

void compile_programs()
{
    CMD(COMPILER, "-o", BUILD_PATH("etapa1"), "./src/etapa1.c", CFLAGS);
    CMD(COMPILER, "-o", BUILD_PATH("etapa2"), "./src/etapa2.c", CFLAGS);
}

void clean_output_exes()
{
    CMD("rm", "-f", BUILD_PATH("etapa1"));
    CMD("rm", "-f", BUILD_PATH("etapa2"));
}

void run_programs()
{
    CMD(BUILD_PATH("etapa1"));
    CMD(BUILD_PATH("etapa2"));
}

int main(int argc, char **argv)
{
    GO_REBUILD_URSELF(argc, argv);
    MKDIRS(BUILD_DIR);
    compile_programs();
    //    run_programs();
    //    clean_output_exes();
    return 0;
}
