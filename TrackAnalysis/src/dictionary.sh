#!/bin/bash
rootcint -f eventdict.cc -c -I${PWD}/../../../ \
         -p \
    	    ./MyEvtId.h \
            ./MyPart.h \
            ./MyGenPart.h \
            ./MyTrack.h \
            ./MyVertex.h \
            ./MySimVertex.h \
            ./MyBeamSpot.h \
            ../interface/LinkDef.h
