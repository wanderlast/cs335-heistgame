CFLAGS = -I ./include
##LIB    = ./lib/fmod/libfmodex64.so
LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm #-lXrandr

all: snake

snake: snake.cpp ppm.cpp log.cpp lianneL.cpp
	g++ $(CFLAGS) snake.cpp ppm.cpp log.cpp lianneL.cpp libggfonts.a \
	-Wall -Wextra $(LFLAGS) -o snake

clean:
	rm -f snake
	rm -f *.o

