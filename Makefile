CFLAGS = -I ./include
##LIB    = ./lib/fmod/libfmodex64.so
LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm #-lXrandr

all: main

main: main.cpp ppm.cpp log.cpp lianneL.cpp kevinB.cpp sergioA.cpp
	g++ $(CFLAGS) main.cpp ppm.cpp log.cpp lianneL.cpp kevinB.cpp sergioA.cpp libggfonts.a /usr/lib/x86_64-linux-gnu/libopenal.so \
	/usr/lib/libalut.so \
	-Wall -Wextra $(LFLAGS) -o main

clean:
	rm -f main
	rm -f *.o

