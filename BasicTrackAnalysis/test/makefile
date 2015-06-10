CXX = g++ -g -Wall
CFLAGS = $(shell root-config --cflags)
LIBS = $(shell root-config --libs)
GLIBS = $(shell root-config --glibs)
RPATH = ../../../../lib/slc6_amd64_gcc491/


Template.exe: TrackAnalysisTemplate.o
	${CXX} -o $@ $^ ${LIBS} -Wl,-rpath=${PWD}

TrackAnalysisTemplate.o: TrackAnalysisTemplate.cc TrackAnalysis.h
	${CXX} -c $^ ${CFLAGS}


DR.exe: TrackAnalysisDR.o
	${CXX} -o $@ $^ ${LIBS} -Wl,-rpath=${PWD}

TrackAnalysisDR.o: TrackAnalysisDR.cc TrackAnalysis.h
	${CXX} -c $^ ${CFLAGS}


ControlPlots.exe: TrackAnalysisControlPlots.o
	${CXX} -o $@ $^ ${LIBS} -Wl,-rpath=${PWD}

TrackAnalysisControlPlots.o: TrackAnalysisControlPlots.cc TrackAnalysis.h
	${CXX} -c $^ ${CFLAGS}


Test.exe: TrackAnalysisTest.o
	${CXX} -o $@ $^ ${LIBS} -Wl,-rpath=${PWD}

TrackAnalysisTest.o: TrackAnalysisTest.cc TrackAnalysis.h
	${CXX} -c $^ ${CFLAGS}


BPIX.exe: TrackAnalysisBPIX.o
	${CXX} -o $@ $^ ${LIBS} -Wl,-rpath=${PWD}

TrackAnalysisBPIX.o: TrackAnalysisBPIX.cc TrackAnalysis.h
	${CXX} -c $^ ${CFLAGS}

EventSelection.exe: TrackAnalysisEventSelection.o
	${CXX} -o $@ $^ ${LIBS} -Wl,-rpath=${PWD}

TrackAnalysisEventSelection.o: TrackAnalysisEventSelection.cc TrackAnalysis.h
	${CXX} -c $^ ${CFLAGS}


CorrectionFactor.exe: TrackAnalysisCorrectionFactor.o
	${CXX} -o $@ $^ ${LIBS} -Wl,-rpath=${PWD}

TrackAnalysisCorrectionFactor.o: TrackAnalysisCorrectionFactor.cc TrackAnalysis.h
	${CXX} -c $^ ${CFLAGS}


HFselection.exe: TrackAnalysisHFselection.o
	${CXX} -o $@ $^ ${LIBS} -Wl,-rpath=${PWD}

TrackAnalysisHFselection.o: TrackAnalysisHFselection.cc TrackAnalysis.h
	${CXX} -c $^ ${CFLAGS}


TrackingEff.exe: TrackAnalysisTrackingEff.o
	${CXX} -o $@ $^ ${LIBS} -Wl,-rpath=${PWD}

TrackAnalysisTrackingEff.o: TrackAnalysisTrackingEff.cc TrackAnalysis.h
	${CXX} -c $^ ${CFLAGS}


dNdEta.exe: TrackAnalysisdNdEta.o
	${CXX} -o $@ $^ ${LIBS} -Wl,-rpath=${PWD}

TrackAnalysisdNdEta.o: TrackAnalysisdNdEta.cc TrackAnalysis.h
	${CXX} -c $^ ${CFLAGS}


clean:
	rm -rf *.o *.exe *.h.gch

.PHONY: clean
