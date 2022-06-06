all:
	gcc -I src/include -I src/headers -L src/lib -Wall -Wextra -Werror -pedantic -o main src/*.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image