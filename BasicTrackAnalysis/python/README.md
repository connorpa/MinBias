# Config files

Here are the usual config python file of CMSSW.
They are only used to run the Tree producer, while the proper analysis (see ../test/) is made in standalone executables.

The produce_ntuples_*.py files contain
- the input files (possibly online),
- the output file containing the ntuple (should be in ../data/), 
- and the input tags, that change according to the source...
Note that there is a produce_ntuples_template.py file.

CAUTION: the input tags might not be up to date (e.g. Annas files) but the template should be right...
