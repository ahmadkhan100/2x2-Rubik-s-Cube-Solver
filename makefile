# makefile

all: solver scrambler

solver: solver.cpp Row.h Row.cpp Side.h Side.cpp Cube.h Cube.cpp
	g++ -g -o solver solver.cpp Row.h Row.cpp Side.h Side.cpp Cube.h Cube.cpp

scrambler: scrambler.cpp Row.h Row.cpp Side.h Side.cpp Cube.h Cube.cpp
	g++ -g -o scrambler scrambler.cpp Row.h Row.cpp Side.h Side.cpp Cube.h Cube.cpp

clean:
	rm -f solver scrambler

.PHONY: all clean
