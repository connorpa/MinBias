CXX = g++ -g -Wall
CFLAGS = $(shell root-config --cflags)
LIBS = $(shell root-config --libs)
GLIBS = $(shell root-config --glibs)
RPATH = ../../../../lib/slc6_amd64_gcc491/

ControlPlots.exe: TrackAnalysisControlPlots.o
	${CXX} -o $@ $^ ${LIBS} -Wl,-rpath=${PWD}

TrackAnalysisControlPlots.o: TrackAnalysisControlPlots.cc TrackAnalysis.h
	${CXX} -c $^ ${CFLAGS}
	
Test.exe: TrackAnalysisTest.o
	${CXX} -o $@ $^ ${LIBS} -Wl,-rpath=${PWD}

TrackAnalysisTest.o: TrackAnalysisTest.cc TrackAnalysis.h
	${CXX} -c $^ ${CFLAGS}
	
clean:
	rm -rf *.o *.exe

.PHONY: clean