//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon May 11 11:43:21 2015 by ROOT version 6.02/05
// from TTree MinBiasData/MinBiasData
// found on file: trackanalysis_output.root
//////////////////////////////////////////////////////////

#ifndef TrackAnalysis_h
#define TrackAnalysis_h

#include <iostream>

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include "../plugins/struct.h"

// Header file for the classes stored in the TTree if any.

using namespace std;

class TrackAnalysis
{
    TTree          *fChain;   //!pointer to the analyzed TTree or TChain
    Int_t           fCurrent; //!current Tree number in a TChain
    const TString path_to_tree;

    // Fixed size dimensions of array or collections stored in the TTree if any.

    // Declaration of leaf types
    MyBeamSpot BS;
    MyEvtId EI;
    MyRecoVertices RV;
    MyRecoTracks RT;

    //vector<Double_t> * RecoVertices_x       ;
    //vector<Double_t> * RecoVertices_y       ;
    //vector<Double_t> * RecoVertices_z       ;
    //vector<Double_t> * RecoVertices_xError  ;
    //vector<Double_t> * RecoVertices_yError  ;
    //vector<Double_t> * RecoVertices_zError  ;
    //vector<Double_t> * RecoVertices_chi2    ;
    //vector<Double_t> * RecoVertices_ndof    ;
    //vector<Bool_t  > * RecoVertices_isFake  ;
    //vector<Bool_t  > * RecoVertices_isValid ;

    //vector<Double_t> * RecoTracks_px        ;
    //vector<Double_t> * RecoTracks_py        ;
    //vector<Double_t> * RecoTracks_pz        ;
    //vector<Int_t   > * RecoTracks_charge    ;

    // List of branches
    TBranch * b_BeamSpot;   //!
    TBranch * b_EvtId;   //!
    TBranch * b_RecoVertices_size;   //!
    TBranch * b_RecoVertices_x;   //!
    TBranch * b_RecoVertices_y;   //!
    TBranch * b_RecoVertices_z;   //!
    TBranch * b_RecoVertices_xError;   //!
    TBranch * b_RecoVertices_yError;   //!
    TBranch * b_RecoVertices_zError;   //!
    TBranch * b_RecoVertices_chi2;   //!
    TBranch * b_RecoVertices_ndof;   //!
    TBranch * b_RecoVertices_isFake;   //!
    TBranch * b_RecoVertices_isValid;   //!
    TBranch * b_RecoTracks_size;   //!
    TBranch * b_RecoTracks_px;   //!
    TBranch * b_RecoTracks_py;   //!
    TBranch * b_RecoTracks_pz;   //!
    TBranch * b_RecoTracks_charge;   //!

public:
    TrackAnalysis(TTree *tree = 0x0);
    virtual ~TrackAnalysis();
    virtual Int_t    Cut(Long64_t entry);
    virtual Int_t    GetEntry(Long64_t entry);
    virtual Long64_t LoadTree(Long64_t entry);
    virtual void     Init(TTree *tree);
    virtual void     Loop();
    virtual Bool_t   Notify();
    virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef TrackAnalysis_cxx
TrackAnalysis::TrackAnalysis(TTree *tree) 
    :   fChain(0x0) 
    ,   path_to_tree("/afs/desy.de/user/c/connorpa/CMSSW/CMSSW_7_4_0/src/MinBias/BasicTrackAnalysis/data/trackanalysis_output.root")
{
    // if parameter tree is not specified (or zero), connect the file
    // used to generate this class and read the Tree.
    if (tree == 0) {
        TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(path_to_tree);
        if (!f || !f->IsOpen()) {
            f = new TFile(path_to_tree);
        }
        TDirectory * dir = (TDirectory*)f->Get(path_to_tree + ":/minbiasdata");
        dir->GetObject("MinBiasData",tree);

    }
    Init(tree);
}

TrackAnalysis::~TrackAnalysis()
{
    if (!fChain) return;
    delete fChain->GetCurrentFile();
}

Int_t TrackAnalysis::GetEntry(Long64_t entry)
{
    // Read contents of entry.
    if (!fChain) return 0;
    return fChain->GetEntry(entry);
}
Long64_t TrackAnalysis::LoadTree(Long64_t entry)
{
    // Set the environment to read one entry
    if (!fChain) return -5;
    Long64_t centry = fChain->LoadTree(entry);
    if (centry < 0) return centry;
    if (fChain->GetTreeNumber() != fCurrent) {
        fCurrent = fChain->GetTreeNumber();
        Notify();
    }
    return centry;
}

void TrackAnalysis::Init(TTree *tree)
{
    // The Init() function is called when the selector needs to initialize
    // a new tree or chain. Typically here the branch addresses and branch
    // pointers of the tree will be set.
    // It is normally not necessary to make changes to the generated
    // code, but the routine can be extended by the user if needed.
    // Init() will be called many times when running on PROOF
    // (once per file to be processed).

    // Set branch addresses and branch pointers
    if (!tree) return;
    fChain = tree;
    fCurrent = -1;
    fChain->SetMakeClass(1);

    // nice
    fChain->SetBranchAddress("BeamSpot", &BS, &b_BeamSpot);
    fChain->SetBranchAddress("EvtId", &EI, &b_EvtId);
    // less nice
    fChain->SetBranchAddress("RecoVertices.x"      , &RV.x      , &b_RecoVertices_x      );
    fChain->SetBranchAddress("RecoVertices.y"      , &RV.y      , &b_RecoVertices_y      );
    fChain->SetBranchAddress("RecoVertices.z"      , &RV.z      , &b_RecoVertices_z      );
    fChain->SetBranchAddress("RecoVertices.xError" , &RV.xError , &b_RecoVertices_xError );
    fChain->SetBranchAddress("RecoVertices.yError" , &RV.yError , &b_RecoVertices_yError );
    fChain->SetBranchAddress("RecoVertices.zError" , &RV.zError , &b_RecoVertices_zError );
    fChain->SetBranchAddress("RecoVertices.chi2"   , &RV.chi2   , &b_RecoVertices_chi2   );
    fChain->SetBranchAddress("RecoVertices.ndof"   , &RV.ndof   , &b_RecoVertices_ndof   );
    fChain->SetBranchAddress("RecoVertices.isFake" , &RV.isFake , &b_RecoVertices_isFake );
    fChain->SetBranchAddress("RecoVertices.isValid", &RV.isValid, &b_RecoVertices_isValid);
    fChain->SetBranchAddress("RecoTracks.px"    , &RT.px    , &b_RecoTracks_px    );
    fChain->SetBranchAddress("RecoTracks.py"    , &RT.py    , &b_RecoTracks_py    );
    fChain->SetBranchAddress("RecoTracks.pz"    , &RT.pz    , &b_RecoTracks_pz    );
    fChain->SetBranchAddress("RecoTracks.charge", &RT.charge, &b_RecoTracks_charge);
    Notify();
}

Bool_t TrackAnalysis::Notify()
{
    // The Notify() function is called when a new file is opened. This
    // can be either for a new TTree in a TChain or when when a new TTree
    // is started when using PROOF. It is normally not necessary to make changes
    // to the generated code, but the routine can be extended by the
    // user if needed. The return value is currently not used.

    return kTRUE;
}

void TrackAnalysis::Show(Long64_t entry)
{
    // Print contents of entry.
    // If entry is not specified, print current entry
    if (!fChain) return;
    fChain->Show(entry);
}
Int_t TrackAnalysis::Cut(Long64_t entry)
{
    // This function may be called from Loop.
    // returns  1 if entry is accepted.
    // returns -1 otherwise.
    return 1;
}
#endif // #ifdef TrackAnalysis_cxx
