CFLAGS = -I ./include

LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm

all: Scoreboard

scoreboard: scoreboard.cpp main.cpp
	g++ $(CFLAGS) scoreboard.cpp main.cpp \
	-Wall -Wextra -o scoreboard

clean:
	rm -f scoreboard
	rm -f *.o
