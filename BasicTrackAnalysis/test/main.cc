int main (int argc, char * argv[])
{
    // declaring TApplication (needed to use the full power of Root as a library)
    TApplication * rootapp = new TApplication ("test", &argc, argv);

    // checking the given arguments to the standalone application
    if (rootapp->Argc() <= 2)
    {
        cout << "Please give as arguments:" << endl
             << "- the path the the file containing the tree," << endl
             << "- and the max nb of entries (0 means everything)." << endl;
        return EXIT_FAILURE;
    }

    // global arguments of the analysis: filename, MC/data, nevents
    const TString applicationname = rootapp->Argv(0),
                  filename        = rootapp->Argv(1);
    const Long64_t maxevents = atoi(rootapp->Argv(2)); // TODO: find a more proper conversion
    const bool kGenLevel = filename.Contains("MC");

    // working
    TrackAnalysis * ta = new TrackAnalysis (filename, kGenLevel); // recall: a second argument can be given to specify wether the file is a data file or a montecarlo file (default is MC)
    ta->Loop(maxevents); // TODO: find more root-suitable conversion
    rootapp->Terminate();

    // ending
    cout << filename << " ended." << endl;
    return EXIT_SUCCESS;
}
