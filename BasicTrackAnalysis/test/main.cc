int main (int argc, char * argv[])
{
    TApplication * rootapp = new TApplication ("test", &argc, argv);
    if (rootapp->Argc() <= 2)
    {
        cout << "Please give as arguments:" << endl
             << "- the path the the file containing the tree," << endl
             << "- and the max nb of entries (0 means everything)." << endl;
        return EXIT_FAILURE;
    }
    TrackAnalysis * ta = new TrackAnalysis (rootapp->Argv(1)); // recall: a second argument can be given to specify wether the file is a data file or a montecarlo file (default is MC)
    ta->Loop(atoi(rootapp->Argv(2))); // TODO: find more root-suitable conversion
    rootapp->Terminate();
    cout << rootapp->Argv(0) << " ended." << endl;
    return EXIT_SUCCESS;
}
