//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon May 11 11:43:21 2015 by ROOT version 6.02/05
// from TTree MinBiasData/MinBiasData
// found on file: trackanalysis_output.root
//////////////////////////////////////////////////////////

#ifndef TrackAnalysis_h
#define TrackAnalysis_h

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include "../plugins/struct.h"

// Header file for the classes stored in the TTree if any.

using namespace std;

class TrackAnalysis // TODO: handle the cases where only certain branches are present
{
    TTree          *fChain;   //!pointer to the analyzed TTree or TChain
    Int_t           fCurrent; //!current Tree number in a TChain
    const TString path_to_tree;
    const bool kContainsGenLevel;

    // Fixed size dimensions of array or collections stored in the TTree if any.

    // Declaration of branch objects (see struct.h)
    MyBeamSpot      BS;
    MyEvtId         EI;
    MyGenVertices   GV;
    MyGenTracks     GT;
    MyRecoVertices  RV;
    MyRecoTracks    RT;
    MyCaloTower     CT;
    MyRecHit        RH_EE, RH_EB, RH_HBHE, RH_HO, RH_HF;

    // List of branches
    TBranch * b_BeamSpot;   //!
    TBranch * b_EvtId;   //!
    TBranch * b_GenVertices_x;   //!
    TBranch * b_GenVertices_y;   //!
    TBranch * b_GenVertices_z;   //!
    TBranch * b_GenTracks_pt;   //!
    TBranch * b_GenTracks_eta;   //!
    TBranch * b_GenTracks_phi;   //!
    TBranch * b_GenTracks_charge;   //!
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
    TBranch * b_RecoTracks_pt;   //!
    TBranch * b_RecoTracks_eta;   //!
    TBranch * b_RecoTracks_phi;   //!
    TBranch * b_RecoTracks_ptError;   //!
    TBranch * b_RecoTracks_etaError;   //!
    TBranch * b_RecoTracks_phiError;   //!
    TBranch * b_RecoTracks_charge;   //!
    TBranch * b_RecoTracks_dxy;      //!
    TBranch * b_RecoTracks_dxyError;    //!
    TBranch * b_RecoTracks_dz;       //!
    TBranch * b_RecoTracks_dzError;    //!
    TBranch * b_HFRecHitEE_energy;
    TBranch * b_HFRecHitEB_energy;
    TBranch * b_HFRecHitHBHE_energy;
    TBranch * b_HFRecHitHO_energy;
    TBranch * b_HFRecHitHF_energy;
    TBranch * b_HFCaloTower_energy;   //!
    TBranch * b_HFCaloTower_energyInHE;   //!
    TBranch * b_HFCaloTower_energyInHB;   //!
    TBranch * b_HFCaloTower_energyInHO;   //!
    TBranch * b_HFCaloTower_energyInHF;   //!
    TBranch * b_HFCaloTower_emEnergy;   //!
    TBranch * b_HFCaloTower_hadEnergy;   //!
    TBranch * b_HFCaloTower_eta;   //!
    TBranch * b_HFCaloTower_phi;   //!

public:
    TrackAnalysis(TTree * tree,
                  bool kGenLevel);
    TrackAnalysis(TString treefilename,
                  bool kGenLevel);
    virtual ~TrackAnalysis();
    virtual Int_t    Cut(Long64_t entry);
    virtual Int_t    GetEntry(Long64_t entry);
    virtual Long64_t LoadTree(Long64_t entry);
    virtual void     Init(TTree *tree);
    virtual void     Loop(Long64_t maxentries = 0);
    virtual Bool_t   Notify();
    virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef TrackAnalysis_cxx
TrackAnalysis::TrackAnalysis(TTree *tree,
                             bool kGenLevel) 
    :   fChain(0x0) 
    ,   kContainsGenLevel(kGenLevel)
{
    Init(tree);
}

TrackAnalysis::TrackAnalysis(TString treefilename,
                             bool kGenLevel) 
    :   fChain(0x0) 
    ,   path_to_tree (treefilename)
    ,   kContainsGenLevel(kGenLevel)
{
    // if parameter tree is not specified (or zero), connect the file
    // used to generate this class and read the Tree.
    cout << "Opening " << path_to_tree << endl;
    TFile * f = new TFile(path_to_tree);
    Init((TTree *) ((TDirectory*) f->Get(path_to_tree + ":/minbiasdata"))->Get("MinBiasData"));
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
    //fChain->SetMakeClass(1);

    // nice
    fChain->SetBranchAddress("BeamSpot", &BS, &b_BeamSpot);
    fChain->SetBranchAddress("EvtId", &EI, &b_EvtId);
    // less nice (TODO: replace multi-definition by object-like definition)
    if (kContainsGenLevel)
    {
        fChain->SetBranchAddress("GenVertices.x", &GV.x, &b_GenVertices_x);
        fChain->SetBranchAddress("GenVertices.y", &GV.y, &b_GenVertices_y);
        fChain->SetBranchAddress("GenVertices.z", &GV.z, &b_GenVertices_z);
        fChain->SetBranchAddress("GenTracks.pt"    , &GT.pt    , &b_GenTracks_pt    );
        fChain->SetBranchAddress("GenTracks.eta"   , &GT.eta   , &b_GenTracks_eta   );
        fChain->SetBranchAddress("GenTracks.phi"   , &GT.phi   , &b_GenTracks_phi   );
        fChain->SetBranchAddress("GenTracks.charge", &GT.charge, &b_GenTracks_charge);
    }
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
    fChain->SetBranchAddress("RecoTracks.pt"      , &RT.pt      , &b_RecoTracks_pt      );
    fChain->SetBranchAddress("RecoTracks.eta"     , &RT.eta     , &b_RecoTracks_eta     );
    fChain->SetBranchAddress("RecoTracks.phi"     , &RT.phi     , &b_RecoTracks_phi     );
    fChain->SetBranchAddress("RecoTracks.ptError" , &RT.ptError , &b_RecoTracks_ptError );
    fChain->SetBranchAddress("RecoTracks.etaError", &RT.etaError, &b_RecoTracks_etaError);
    fChain->SetBranchAddress("RecoTracks.phiError", &RT.phiError, &b_RecoTracks_phiError);
    fChain->SetBranchAddress("RecoTracks.charge"  , &RT.charge  , &b_RecoTracks_charge  );
    fChain->SetBranchAddress("RecoTracks.dxy"     , &RT.dxy     , &b_RecoTracks_dxy     ); 
    fChain->SetBranchAddress("RecoTracks.dxyError", &RT.dxyError, &b_RecoTracks_dxyError);
    fChain->SetBranchAddress("RecoTracks.dz"      , &RT.dz      , &b_RecoTracks_dz      );
    fChain->SetBranchAddress("RecoTracks.dzError" , &RT.dzError , &b_RecoTracks_dzError );
    fChain->SetBranchAddress("HFRecHitEE.energy"  , &RH_EE.energy  , &b_HFRecHitEE_energy);
    fChain->SetBranchAddress("HFRecHitEB.energy"  , &RH_EB.energy  , &b_HFRecHitEB_energy);
    fChain->SetBranchAddress("HFRecHitHBHE.energy", &RH_HBHE.energy, &b_HFRecHitHBHE_energy);
    fChain->SetBranchAddress("HFRecHitHO.energy"  , &RH_HO.energy  , &b_HFRecHitHO_energy);
    fChain->SetBranchAddress("HFRecHitHF.energy"  , &RH_HF.energy  , &b_HFRecHitHF_energy);
    fChain->SetBranchAddress("HFCaloTower.energy"    , &CT.energy    , &b_HFCaloTower_energy    ); // TODO: automate the recognition of the branch present in the tree
    fChain->SetBranchAddress("HFCaloTower.energyInHB", &CT.energyInHB, &b_HFCaloTower_energyInHB);
    fChain->SetBranchAddress("HFCaloTower.energyInHE", &CT.energyInHE, &b_HFCaloTower_energyInHE);
    fChain->SetBranchAddress("HFCaloTower.energyInHO", &CT.energyInHO, &b_HFCaloTower_energyInHO);
    fChain->SetBranchAddress("HFCaloTower.energyInHF", &CT.energyInHF, &b_HFCaloTower_energyInHF);
    fChain->SetBranchAddress("HFCaloTower.emEnergy"  , &CT.emEnergy  , &b_HFCaloTower_emEnergy  );
    fChain->SetBranchAddress("HFCaloTower.hadEnergy" , &CT.hadEnergy , &b_HFCaloTower_hadEnergy );
    fChain->SetBranchAddress("HFCaloTower.eta"       , &CT.eta       , &b_HFCaloTower_eta       );
    fChain->SetBranchAddress("HFCaloTower.phi"       , &CT.phi       , &b_HFCaloTower_phi       );

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
