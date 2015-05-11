CXX = g++ -g -Wall
CFLAGS = $(shell root-config --cflags)
LIBS = $(shell root-config --libs)
GLIBS = $(shell root-config --glibs)
RPATH = ../../../../lib/slc6_amd64_gcc491/

test: TrackAnalysis.o
	${CXX} -o $@ $^ ${LIBS} -Wl,-rpath=${PWD}

TrackAnalysis.o: TrackAnalysis.cc TrackAnalysis.h
	${CXX} -c $^ ${CFLAGS}
	
clean:
	rm -rf *.o

.PHONY: clean
