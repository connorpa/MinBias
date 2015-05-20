# MinBias
Developing CMS dn/deta track analysis within CMSSW_7_4_0 (ROOT 6)

Packages:
- TrackAnalysis: the tree producer does not work yet due to a misuse of the dictionaries with root
- BasicTrackAnalysis: this package aims at the same analysis but trying avoiding these issues

Current state:
- the tree producer is works is is relatively robust (in BasicTrackAnalysis/plugings/)
- the tree analysers are independent C++ applications using root as a library, under development but already delivering plots (in BasicTrackAnalysis/test/)
- the plotters are just root scripts, stored in data, where the ntuples are supposed to lay

Developers: Patrick Connor, Juan Manuel Grados Luyando, Benoît Roland (DESY CMS group)
