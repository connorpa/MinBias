# Working

How to write a new analyser?

First, the two next files should be generic:
- main.cc contains the TApplication, to use the ROOT as a library within a standalone executable
- TrackAnalysis.h contains all the headers necessary to run over a TTree

Moreover, there are
- TrackAnalysisTest.cc, which is a bare reader to check the content of the file directly in the shell
- TrackAnalysisTemplate.cc, which is a template of the Loop method, to be copied for any new analyser
- TrackAnalysisControlPlots, which is an example code to plot basic quantities,
- ...

Finally, there is a makefile: for any new application, just add the compilation instructions.
Please try respecting the conventions of the name:
- *.exe for the executables,
- TrackAnalysis*.exe for the different analysers.
