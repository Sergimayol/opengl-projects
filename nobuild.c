#define NOBUILD_IMPLEMENTATION
#include "./nobuild.h"

#define CFLAGS "-Wall", "-Wextra", "-Werror", "-std=c99", "-lglut", "-lGLU", "-lGL", "-lm"
#define EXTRA_FLAGS "-I/usr/include", "-L/path/to/assimp/lib", "-lassimp"
#define COMPILER "gcc"
#define BUILD_DIR "build"
#define BUILD_PATH(path) BUILD_DIR "/" path

int main(int argc, char **argv)
{
	GO_REBUILD_URSELF(argc, argv);
	MKDIRS(BUILD_DIR);
	//CMD(COMPILER, "-o", BUILD_PATH("etapa1"), "./src/Etapa1/etapa1.c", CFLAGS);
	//CMD(COMPILER, "-o", BUILD_PATH("etapa2"), "./src/Etapa2/etapa2.c", CFLAGS);
	//CMD(COMPILER, "-o", BUILD_PATH("pendulo"), "./src/Etapa2/pendulo.c", CFLAGS);
	//CMD(COMPILER, "-o", BUILD_PATH("etapa3"), "./src/Etapa3/etapa3.c", CFLAGS);
	//CMD(COMPILER, "-o", BUILD_PATH("etapa4"), "./src/Etapa4/etapa4.c", "./src/Etapa4/AxisAndPlanes.c", "./src/Etapa4/figures.c", "./src/Etapa4/camera.c", CFLAGS);
	//CMD(COMPILER, "-o", BUILD_PATH("etapa5"), "./src/Etapa5/etapa5.c", "./src/Etapa5/AxisAndPlanes.c", "./src/Etapa5/figures.c", "./src/Etapa5/light.c", CFLAGS);
	CMD(COMPILER, "-O3", "-o", BUILD_PATH("etapa6"), "./src/Etapa6/etapa6.c", "./src/Etapa6/AxisAndPlanes.c", "./src/Etapa6/figures.c", "./src/Etapa6/light.c", "./src/Etapa6/camera.c", "./src/Etapa6/object.c", "./src/Etapa6/texture.c", "./src/Etapa6/map.c", CFLAGS, EXTRA_FLAGS);
	//CMD(COMPILER, "-o", BUILD_PATH("base"), "./src/templates/base.c", CFLAGS);
	return 0;
}
