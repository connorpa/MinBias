#define TrackAnalysis_cxx
#include "TrackAnalysis.h"
#include <TApplication.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void TrackAnalysis::Loop()
{
    //   In a ROOT session, you can do:
    //      root> .L TrackAnalysis.C
    //      root> TrackAnalysis t
    //      root> t.GetEntry(12); // Fill t data members with entry number 12
    //      root> t.Show();       // Show values of entry 12
    //      root> t.Show(16);     // Read and show values of entry 16
    //      root> t.Loop();       // Loop on all entries
    //

    //     This is the loop skeleton where:
    //    jentry is the global entry number in the chain
    //    ientry is the entry number in the current Tree
    //  Note that the argument to GetEntry must be:
    //    jentry for TChain::GetEntry
    //    ientry for TTree::GetEntry and TBranch::GetEntry
    //
    //       To read only selected branches, Insert statements like:
    // METHOD1:
    //    fChain->SetBranchStatus("*",0);  // disable all branches
    //    fChain->SetBranchStatus("branchname",1);  // activate branchname
    // METHOD2: replace line
    //    fChain->GetEntry(jentry);       //read all branches
    //by  b_branchname->GetEntry(ientry); //read only this branch
    if (fChain == 0) return;

    Long64_t nentries = fChain->GetEntriesFast();

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;
        // if (Cut(ientry) < 0) continue;

        // test BS and EI
        cout << __FILE__ << ":" << __func__ << ":" << __LINE__ << ":" << jentry << ":\tBS.position = (" << BS.positionX << "," << BS.positionY << "," << BS.positionZ << ")" << endl;
        cout << __FILE__ << ":" << __func__ << ":" << __LINE__ << ":" << jentry << ":\tEI.Run = " << EI.Run << endl;

        // test GV
        cout << __FILE__ << ":" << __func__ << ":" << __LINE__ << ":" << jentry << ":\tGV.x->size() = " << GV.x->size() << endl;
        for (UInt_t ivertex = 0 ; ivertex < GV.x->size() ; ivertex++)
            cout << __FILE__ << ":" << __func__ << ":" << __LINE__ << ":" << jentry << ":\tVertex(" << ivertex << ") = (" << GV.x->at(ivertex) << "," << GV.y->at(ivertex) << "," << GV.z->at(ivertex) << ")" << endl;

        // test GT
        cout << __FILE__ << ":" << __func__ << ":" << __LINE__ << ":" << jentry << ":\tGT.pt->size() = " << GT.pt->size() << endl;
        for (UInt_t itrack = 0 ; itrack < GT.pt->size() ; itrack++)
            cout << __FILE__ << ":" << __func__ << ":" << __LINE__ << ":" << jentry << ":\tTrack(" << itrack << ") = (" << GT.pt->at(itrack) << "," << GT.eta->at(itrack) << "," << GT.phi->at(itrack) << ")" << endl;

        // test RV
        cout << __FILE__ << ":" << __func__ << ":" << __LINE__ << ":" << jentry << ":\tRV.x->size() = " << RV.x->size() << endl;
        for (UInt_t ivertex = 0 ; ivertex < RV.x->size() ; ivertex++)
            cout << __FILE__ << ":" << __func__ << ":" << __LINE__ << ":" << jentry << ":\tVertex(" << ivertex << ") = (" << RV.x->at(ivertex) << "," << RV.y->at(ivertex) << "," << RV.z->at(ivertex) << ")" << endl;

        // test RT
        cout << __FILE__ << ":" << __func__ << ":" << __LINE__ << ":" << jentry << ":\tRT.pt->size() = " << RT.pt->size() << endl;
        for (UInt_t itrack = 0 ; itrack < RT.pt->size() ; itrack++)
            cout << __FILE__ << ":" << __func__ << ":" << __LINE__ << ":" << jentry << ":\tTrack(" << itrack << ") = (" << RT.pt->at(itrack) << "," << RT.eta->at(itrack) << "," << RT.phi->at(itrack) << ")" << endl;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
int main (int argc, char * argv[])
{
    TApplication * rootapp = new TApplication ("tapp", &argc, argv);
    //if (rootapp->Argc() < 1)
    //    return EXIT_FAILURE;
    TrackAnalysis * ta = new TrackAnalysis ();
    //cp->Show(2);
    ta->Loop();//(rootapp->Argc() > 1 ? (Long64_t) atoi(rootapp->Argv(1)) : 0);
    rootapp->Terminate();
    return EXIT_SUCCESS;
}
