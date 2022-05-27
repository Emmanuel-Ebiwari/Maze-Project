all:
	gcc -I src/include -L src/lib -Wall -Wextra -Werror -pedantic -o main main.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lOpenGL32 -lglu32 -lfreeGLUT