# makefile

all: solver scrambler

solver: solver.cpp row.h row.cpp side.h side.cpp cube.h cube.cpp
	g++ -g -o solver solver.cpp row.cpp side.cpp cube.cpp

scrambler: scrambler.cpp row.h row.cpp side.h side.cpp cube.h cube.cpp
	g++ -g -o scrambler scrambler.cpp row.cpp side.cpp cube.cpp

clean:
	rm -f solver scrambler

.PHONY: all clean
