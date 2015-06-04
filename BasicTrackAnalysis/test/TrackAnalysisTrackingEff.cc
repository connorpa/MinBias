/**************************************************************************************/
/* Author: Patrick L.S. Connor & Juan M. Grados Luyando (DESY CMS group)                                       */
/* Date: May 2015                                                                     */
/* Purpose: read and extract histograms from the ntuples given by the TreeProducer.cc */
/* Note: this code was started from the TTree::MakeClass()                            */
/**************************************************************************************/
#define TrackAnalysis_cxx
#include "TrackAnalysis.h"
#include <cstdlib>
#include <TApplication.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>

#define PI TMath::Pi()

void TrackAnalysis::Loop(Long64_t maxentries)
{
    if (fChain == 0x0) return;

    /********************** CUTOFFS & CONSTANTS ***************************/

    const double minpt  = 0.1, // GeV
                 maxtracketa = 2.4, // no unit
                 minRHeta = 3,
                 maxRHeta = 5,
                 Ecut  = 5.0, //HF Energy cut [GeV]
                 CTcut = 5.0; //CaloTower energy cut [GeV]
    const unsigned short int NKIN = 4; // KINematics, plus multiplicity
                             //ETABIN = 4; // 4 eta bins of width 0.6 
                             //NDIR = 3; // DIRections
    //const double ETABINWIDTH = maxtracketa/((double) NETABIN);

    /************************* BOOKING HISTOGRAMS *****************************/

    cout << "Booking histograms..." << endl;

    //Bin with of eta and pt histograms
    double binWidth   = 4.8/50.0,
           binWidthpt = 5.0/50.0;


    // those variables are defined to take advantage of the maps
    // i.e. the map can be looped only over a small section of
    // we define constant proto histograms, whose purpose is only to be cloned, to ensure to have always the same structure
    //TH1D * h = new TH1D (name, title, nbins, xlow, xup);
   
     const TH1D * proto_tracks2[NKIN] = {new const TH1D ("eta", "pseudorapidity;#eta;#entries",  50,  -2.4,  2.4),
                                         new const TH1D ("pt" , "transverse momentum;p_T/GeV;#entries",   50,     0,   5),
                                         new const TH1D ("M"  , "multiplicity;M;#enitres",       300,     0,  300),
                                         new const TH1D ("EtotHF", "Total HF energy;E_HF_tot/GeV;#entries",1000,0.,1000.)};


               
              
    
    map<TString, TH1D *> hist1D; // i.e. map["string"] = histogram (use "iterators" to run over a map--see below)
    //map<TString, TH2D *> hist2D;
    // reconstructed tracks
        //Reco tracks of events selected at detector level(CaloTowers)
        for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
        {
            TString name = TString::Format("RT_HFAnd_tower_%s", proto_tracks2[ikin]->GetName());
            hist1D[name] = (TH1D *) proto_tracks2[ikin]->Clone(name);
            hist1D[name]->SetTitle(TString::Format("%s of the reconstructed tracks with HFAnd(det) selection", proto_tracks2[ikin]->GetTitle()));
            hist1D[name]->SetXTitle(proto_tracks2[ikin]->GetXaxis()->GetTitle());
            hist1D[name]->SetYTitle(proto_tracks2[ikin]->GetYaxis()->GetTitle());
        }
        for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
        {
            TString name = TString::Format("RT_HFXor_tower_%s", proto_tracks2[ikin]->GetName());
            hist1D[name] = (TH1D *) proto_tracks2[ikin]->Clone(name);
            hist1D[name]->SetTitle(TString::Format("%s of the reconstructed tracks with HFXor(det) selection", proto_tracks2[ikin]->GetTitle()));
            hist1D[name]->SetXTitle(proto_tracks2[ikin]->GetXaxis()->GetTitle());
            hist1D[name]->SetYTitle(proto_tracks2[ikin]->GetYaxis()->GetTitle());
        }
        for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
        {
            TString name = TString::Format("RT_HFOr_tower_%s", proto_tracks2[ikin]->GetName());
            hist1D[name] = (TH1D *) proto_tracks2[ikin]->Clone(name);
            hist1D[name]->SetTitle(TString::Format("%s of the reconstructed tracks with HFOr(det) selection", proto_tracks2[ikin]->GetTitle()));
            hist1D[name]->SetXTitle(proto_tracks2[ikin]->GetXaxis()->GetTitle());
            hist1D[name]->SetYTitle(proto_tracks2[ikin]->GetYaxis()->GetTitle());
        }
        for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
        {
            TString name = TString::Format("RT_NoHF_tower_%s", proto_tracks2[ikin]->GetName());
            hist1D[name] = (TH1D *) proto_tracks2[ikin]->Clone(name);
            hist1D[name]->SetTitle(TString::Format("%s of the reconstructed tracks with NoHF(det) selection", proto_tracks2[ikin]->GetTitle()));
            hist1D[name]->SetXTitle(proto_tracks2[ikin]->GetXaxis()->GetTitle());
            hist1D[name]->SetYTitle(proto_tracks2[ikin]->GetYaxis()->GetTitle());
        }

        //Reco tracks of events selected at gen level(4vector)
        for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
        {
            TString name = TString::Format("RT_HFAnd_4vector_%s", proto_tracks2[ikin]->GetName());
            hist1D[name] = (TH1D *) proto_tracks2[ikin]->Clone(name);
            hist1D[name]->SetTitle(TString::Format("%s of the reconstructed tracks with HFAnd(4vector) selection", proto_tracks2[ikin]->GetTitle()));
            hist1D[name]->SetXTitle(proto_tracks2[ikin]->GetXaxis()->GetTitle());
            hist1D[name]->SetYTitle(proto_tracks2[ikin]->GetYaxis()->GetTitle());
        }
        for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
        {
            TString name = TString::Format("RT_HFXor_4vector_%s", proto_tracks2[ikin]->GetName());
            hist1D[name] = (TH1D *) proto_tracks2[ikin]->Clone(name);
            hist1D[name]->SetTitle(TString::Format("%s of the reconstructed tracks with HFXor(4vector) selection", proto_tracks2[ikin]->GetTitle()));
            hist1D[name]->SetXTitle(proto_tracks2[ikin]->GetXaxis()->GetTitle());
            hist1D[name]->SetYTitle(proto_tracks2[ikin]->GetYaxis()->GetTitle());
        }
        for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
        {
            TString name = TString::Format("RT_HFOr_4vector_%s", proto_tracks2[ikin]->GetName());
            hist1D[name] = (TH1D *) proto_tracks2[ikin]->Clone(name);
            hist1D[name]->SetTitle(TString::Format("%s of the reconstructed tracks with HFOr(4vector) selection", proto_tracks2[ikin]->GetTitle()));
            hist1D[name]->SetXTitle(proto_tracks2[ikin]->GetXaxis()->GetTitle());
            hist1D[name]->SetYTitle(proto_tracks2[ikin]->GetYaxis()->GetTitle());
        }
        for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
        {
            TString name = TString::Format("RT_NoHF_4vector_%s", proto_tracks2[ikin]->GetName());
            hist1D[name] = (TH1D *) proto_tracks2[ikin]->Clone(name);
            hist1D[name]->SetTitle(TString::Format("%s of the reconstructed tracks with NoHF(4vector) selection", proto_tracks2[ikin]->GetTitle()));
            hist1D[name]->SetXTitle(proto_tracks2[ikin]->GetXaxis()->GetTitle());
            hist1D[name]->SetYTitle(proto_tracks2[ikin]->GetYaxis()->GetTitle());
        }
    
    // the same at gen level
    if (kContainsGenLevel)
    {   // create histograms for gen level with the exact same structure

        // generated tracks of events selected at detector level(CaloTower)
        for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
        {
            TString name = TString::Format("GT_HFAnd_tower_%s", proto_tracks2[ikin]->GetName());
            hist1D[name] = (TH1D *) proto_tracks2[ikin]->Clone(name);
            hist1D[name]->SetTitle(TString::Format("%s of the generated tracks with HFAnd(det) selection", proto_tracks2[ikin]->GetTitle()));
            hist1D[name]->SetXTitle(proto_tracks2[ikin]->GetXaxis()->GetTitle());
            hist1D[name]->SetYTitle(proto_tracks2[ikin]->GetYaxis()->GetTitle());
        }
        for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
        {
            TString name = TString::Format("GT_HFXor_tower_%s", proto_tracks2[ikin]->GetName());
            hist1D[name] = (TH1D *) proto_tracks2[ikin]->Clone(name);
            hist1D[name]->SetTitle(TString::Format("%s of the generated tracks with HFXor(det) selection", proto_tracks2[ikin]->GetTitle()));
            hist1D[name]->SetXTitle(proto_tracks2[ikin]->GetXaxis()->GetTitle());
            hist1D[name]->SetYTitle(proto_tracks2[ikin]->GetYaxis()->GetTitle());
        }
        for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
        {
            TString name = TString::Format("GT_HFOr_tower_%s", proto_tracks2[ikin]->GetName());
            hist1D[name] = (TH1D *) proto_tracks2[ikin]->Clone(name);
            hist1D[name]->SetTitle(TString::Format("%s of the generated tracks with HFOr(det) selection", proto_tracks2[ikin]->GetTitle()));
            hist1D[name]->SetXTitle(proto_tracks2[ikin]->GetXaxis()->GetTitle());
            hist1D[name]->SetYTitle(proto_tracks2[ikin]->GetYaxis()->GetTitle());
        }
        for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
        {
            TString name = TString::Format("GT_NoHF_tower_%s", proto_tracks2[ikin]->GetName());
            hist1D[name] = (TH1D *) proto_tracks2[ikin]->Clone(name);
            hist1D[name]->SetTitle(TString::Format("%s of the generated tracks with NoHF(det) selection", proto_tracks2[ikin]->GetTitle()));
            hist1D[name]->SetXTitle(proto_tracks2[ikin]->GetXaxis()->GetTitle());
            hist1D[name]->SetYTitle(proto_tracks2[ikin]->GetYaxis()->GetTitle());
        }
    

        // generated tracks of events selected at gene level(4vector)
        for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
        {
            TString name = TString::Format("GT_HFAnd_4vector_%s", proto_tracks2[ikin]->GetName());
            hist1D[name] = (TH1D *) proto_tracks2[ikin]->Clone(name);
            hist1D[name]->SetTitle(TString::Format("%s of the generated tracks with HFAnd(4vector) selection", proto_tracks2[ikin]->GetTitle()));
            hist1D[name]->SetXTitle(proto_tracks2[ikin]->GetXaxis()->GetTitle());
            hist1D[name]->SetYTitle(proto_tracks2[ikin]->GetYaxis()->GetTitle());
        }
        for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
        {
            TString name = TString::Format("GT_HFXor_4vector_%s", proto_tracks2[ikin]->GetName());
            hist1D[name] = (TH1D *) proto_tracks2[ikin]->Clone(name);
            hist1D[name]->SetTitle(TString::Format("%s of the generated tracks with HFXor(4vector) selection", proto_tracks2[ikin]->GetTitle()));
            hist1D[name]->SetXTitle(proto_tracks2[ikin]->GetXaxis()->GetTitle());
            hist1D[name]->SetYTitle(proto_tracks2[ikin]->GetYaxis()->GetTitle());
        }
        for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
        {
            TString name = TString::Format("GT_HFOr_4vector_%s", proto_tracks2[ikin]->GetName());
            hist1D[name] = (TH1D *) proto_tracks2[ikin]->Clone(name);
            hist1D[name]->SetTitle(TString::Format("%s of the generated tracks with HFOr(4vector) selection", proto_tracks2[ikin]->GetTitle()));
            hist1D[name]->SetXTitle(proto_tracks2[ikin]->GetXaxis()->GetTitle());
            hist1D[name]->SetYTitle(proto_tracks2[ikin]->GetYaxis()->GetTitle());
        }
        for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
        {
            TString name = TString::Format("GT_NoHF_4vector_%s", proto_tracks2[ikin]->GetName());
            hist1D[name] = (TH1D *) proto_tracks2[ikin]->Clone(name);
            hist1D[name]->SetTitle(TString::Format("%s of the generated tracks with NoHF(4vector) selection", proto_tracks2[ikin]->GetTitle()));
            hist1D[name]->SetXTitle(proto_tracks2[ikin]->GetXaxis()->GetTitle());
            hist1D[name]->SetYTitle(proto_tracks2[ikin]->GetYaxis()->GetTitle());
        }
    
    }
    // energy deposit in the forward calorimeter
    //hist1D["forward_energy"] = new TH1D ("forward_energy", "forward energy deposit;E/GeV;#entries", 100, 0, 100);
    //hist1D["rechit_energy"]  = new TH1D ("rechit_energy" ,  "rechit energy deposit;E/GeV;#entries", 100, 0, 100);

    // this macro is used to define 2d histogram using the 1d histogram corresponding to the axes
/*
#define DEFINE2DHIST(XNAME, YNAME, TITLE) \
    hist2D[XNAME "_VS_" YNAME] = new TH2D (#XNAME "_VS_" #YNAME, TITLE, \
                                            hist1D[XNAME]->GetNbinsX(), hist1D[XNAME]->GetXaxis()->GetXmin(), hist1D[XNAME]->GetXaxis()->GetXmax(), \
                                            hist1D[YNAME]->GetNbinsX(), hist1D[YNAME]->GetXaxis()->GetXmin(), hist1D[YNAME]->GetXaxis()->GetXmax())
//    DEFINE2DHIST("GT_HFAnd_EtotHF", "GT_HFAnd_M" , "Total Energy in HF VS Generated multiplicity for HFAnd   ;E/GeV;M      ;#entries");
//    DEFINE2DHIST("GT_HFXor_EtotHF", "GT_HFXor_M" , "Total Energy in HF VS Generated multiplicity for HFXor   ;E/GeV;M      ;#entries");
//    DEFINE2DHIST("GT_HFOr_EtotHF",  "GT_HFOr_M"  , "Total Energy in HF VS Generated multiplicity for HFOr    ;E/GeV;M      ;#entries");
//    DEFINE2DHIST("GT_NoHF_EtotHF",  "GT_NoHF_M"  , "Total Energy in HF VS Generated multiplicity for NoHF    ;E/GeV;M      ;#entries");
//    DEFINE2DHIST("RT_HFAnd_EtotHF", "RT_HFAnd_M" , "Total Energy in HF VS Reconstructed multiplicity for HFAnd   ;E/GeV;M      ;#entries");
//    DEFINE2DHIST("RT_HFXor_EtotHF", "RT_HFXor_M" , "Total Energy in HF VS Reconstructed multiplicity for HFXor   ;E/GeV;M      ;#entries");
//    DEFINE2DHIST("RT_HFOr_EtotHF",  "RT_HFOr_M"  , "Total Energy in HF VS Reconstructed multiplicity for HFOr    ;E/GeV;M      ;#entries");
//    DEFINE2DHIST("RT_NoHF_EtotHF",  "RT_NoHF_M"  , "Total Energy in HF VS Reconstructed multiplicity for NoHF    ;E/GeV;M      ;#entries");
//    
//    DEFINE2DHIST("GT_HFAnd_EtotHF", "GT_HFAnd_pt" , "Total Energy in HF VS Generated multiplicity for HFAnd   ;E/GeV;Pt/GeV      ;#entries");
//    DEFINE2DHIST("GT_HFXor_EtotHF", "GT_HFXor_pt" , "Total Energy in HF VS Generated multiplicity for HFXor   ;E/GeV;Pt/GeV      ;#entries");
//    DEFINE2DHIST("GT_HFOr_EtotHF",  "GT_HFOr_pt"  , "Total Energy in HF VS Generated multiplicity for HFOr    ;E/GeV;Pt/GeV      ;#entries");
//    DEFINE2DHIST("GT_NoHF_EtotHF",  "GT_NoHF_pt"  , "Total Energy in HF VS Generated multiplicity for NoHF    ;E/GeV;Pt/GeV      ;#entries");
//    DEFINE2DHIST("RT_HFAnd_EtotHF", "RT_HFAnd_pt" , "Total Energy in HF VS Reconstructed multiplicity for HFAnd   ;E/GeV;Pt/GeV      ;#entries");
//    DEFINE2DHIST("RT_HFXor_EtotHF", "RT_HFXor_pt" , "Total Energy in HF VS Reconstructed multiplicity for HFXor   ;E/GeV;Pt/GeV      ;#entries");
//    DEFINE2DHIST("RT_HFOr_EtotHF",  "RT_HFOr_pt"  , "Total Energy in HF VS Reconstructed multiplicity for HFOr    ;E/GeV;Pt/GeV      ;#entries");
//    DEFINE2DHIST("RT_NoHF_EtotHF",  "RT_NoHF_pt"  , "Total Energy in HF VS Reconstructed multiplicity for NoHF    ;E/GeV;Pt/GeV      ;#entries");
//    
//    DEFINE2DHIST("RT_HFAnd_M", "GT_HFAnd_M" , "Reconstructed multiplicity VS Generated multiplicity for HFAnd   ;M reco;M gen      ;#entries");
//    DEFINE2DHIST("RT_HFXor_M", "GT_HFXor_M" , "Reconstructed multiplicity VS Generated multiplicity for HFXor   ;M reco;M gen      ;#entries");
//    DEFINE2DHIST("RT_HFOr_M", "GT_HFOr_M" , "Reconstructed multiplicity VS Generated multiplicity for HFOr   ;M reco;M gen      ;#entries");
//    DEFINE2DHIST("RT_NoHF_M", "GT_NoHF_M" , "Reconstructed multiplicity VS Generated multiplicity for NoHF   ;M reco;M gen      ;#entries");
#undef DEFINE2DHIST
*/


//Container histograms to chose the histogram to fill after the eventselection

     TH1D* histofill_GT_tower_eta          = 0x0;    // Pointer histogram to select the histogram we want for ETA 
     TH1D* histofill_GT_tower_pt           = 0x0;    // Pointer histogram to select the histogram we want for ETA 
     TH1D* histofill_GT_tower_multi        = 0x0; 
     TH1D* histofill_GT_tower_EtotHF       = 0x0; 
     
     TH1D* histofill_GT_4vector_eta          = 0x0;    // Pointer histogram to select the histogram we want for ETA 
     TH1D* histofill_GT_4vector_pt           = 0x0;    // Pointer histogram to select the histogram we want for ETA 
     TH1D* histofill_GT_4vector_multi        = 0x0; 
     TH1D* histofill_GT_4vector_EtotHF       = 0x0; 
//     TH2D* histofill_GT_EtotHF_VS_M  = 0x0;
//     TH2D* histofill_GT_EtotHF_VS_pt = 0x0;
                    
     TH1D* histofill_RT_tower_eta          = 0x0;    // Pointer histogram to select the histogram we want for ETA 
     TH1D* histofill_RT_tower_pt           = 0x0;    // Pointer histogram to select the histogram we want for ETA 
     TH1D* histofill_RT_tower_multi        = 0x0; 
     TH1D* histofill_RT_tower_EtotHF       = 0x0; 
     
     TH1D* histofill_RT_4vector_eta          = 0x0;    // Pointer histogram to select the histogram we want for ETA 
     TH1D* histofill_RT_4vector_pt           = 0x0;    // Pointer histogram to select the histogram we want for ETA 
     TH1D* histofill_RT_4vector_multi        = 0x0; 
     TH1D* histofill_RT_4vector_EtotHF       = 0x0; 
//     TH2D* histofill_RT_EtotHF_VS_M  = 0x0;
//     TH2D* histofill_RT_EtotHF_VS_pt = 0x0;


    /******************* RUNNING OVER THE TREE ***********************/

    // counters
    const Long64_t nentries = (maxentries <= 0) ? fChain->GetEntriesFast() : min(fChain->GetEntriesFast(),maxentries);
    unsigned int progress = 0;  // counter  to see the progress of the loop
    Long64_t nbytes = 0, nb = 0; // dunno the use of this... (given by TTree::MakeClass())

    
//    unsigned int ngentracksout = 0; // #tracks passing the cutoffs
    
//    bool   GTisHFAnd   = 0,
//           GTisHFXor   = 0,
//           RTisHFAnd   = 0,
//           RTisHFXor   = 0;

    //Variables to be used through the full program, like inside particle loops and then at the end for normalizations, etc. 
    unsigned int nrectracks = 0; // #tracks passing the cutoffs
    
    double RT_dxy  = 0.,
           RT_sdxy = 0.,
           RT_dz   = 0.,
           RT_sdz  = 0.; 
    
  
    double NGAnd = 0,
           NGXor = 0,
           NGNo  = 0,  
           NRAnd = 0,
           NRXor = 0,
           NRNo  = 0;
    //---------------------------------------------------------


    cout << "Running over " << nentries << " entries..." << endl;
    for (Long64_t jentry=0; jentry<nentries;jentry++)
    {
        // just a counter to see the progress of the loop
        if ((100*jentry)/nentries != progress)
        {
            progress = (100*jentry)/nentries;
            cout << "Loop: " << progress << "%" << endl;
        }

        // load the entry
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;
        // if (Cut(ientry) < 0) continue; // currently, the Cut method has not been implemented (and is likely not going to be)

//*********************** RecoVertexs loop ***************************//
//TODO: For data is needed to include the matching with primary vertex (the first one of the vertex collection)

    //To see the number of Reco/Gen vertices
   // cout<<"Number GenVertices =  "<<GV.x->size()<<endl;
   // cout<<"Number RecoVertices = "<<RV.x->size()<<endl;
    




//*********************** RecoTracks loop ***************************//
   
    //Maximum energy deposition value in HF sides per event    
    double CTmaxHFminus = 0.,
           CTmaxHFplus  = 0.;

    //Total energy deposition in HF sides per event
    double CTtotHFminus = 0.,
           CTtotHFplus  = 0.;
        
    double RV_x = RV.x->at(0),
           RV_y = RV.y->at(0),
           RV_dxy = sqrt(pow(RV_x,2)+pow(RV_y,2));

    if(    fabs(RV.z->at(0)) < 20   //Less than 20cm from nominal interaction point along Z
        && RV_dxy < 0.2             //Less than 0.2cm from nominal beam line     
        && RT.pt->size() > 3 )     //At least 3 tracks in the vertex
        {



            //RT maximum CaloTower energy in HF+/- for following event selection
            for (unsigned int itrack = 0 ; itrack < CT.energy->size() ; itrack++)
            { 
               
                //HF plus
                if (   CT.eta->at(itrack) > minRHeta
                    && CT.eta->at(itrack) < maxRHeta)
                {
                    CTmaxHFplus = max(CTmaxHFplus, CT.energy->at(itrack));
                    CTtotHFplus += CT.energy->at(itrack);
                }

                //HF minus
                if (   CT.eta->at(itrack) < -minRHeta
                    && CT.eta->at(itrack) > -maxRHeta)
                {
                    CTmaxHFminus = max(CTmaxHFminus, CT.energy->at(itrack));
                    CTtotHFminus += CT.energy->at(itrack);
                }
            }



           //RT event selection
                //HF_Or selection, at least one side of HF
                if(CTmaxHFminus>CTcut || CTmaxHFplus>CTcut){
                    
                    //Note that HF_Xor and HF_And are inside HF_Or since they are a subgroup
                    //HF_Xor selection, only one side of HF
                    if((CTmaxHFminus>CTcut && CTmaxHFplus<CTcut) || (CTmaxHFminus<CTcut && CTmaxHFplus>CTcut)){
                        
                        NRXor++; //Counter for normalization 
//                        RTisHFXor = 1;
                        histofill_RT_tower_eta          = hist1D["RT_HFXor_tower_eta"];
                        histofill_RT_tower_pt           = hist1D["RT_HFXor_tower_pt"];
                        histofill_RT_tower_multi        = hist1D["RT_HFXor_tower_M"];
                        histofill_RT_tower_EtotHF       = hist1D["RT_HFXor_tower_EtotHF"];
//                        histofill_RT_EtotHF_VS_M  = hist2D["RT_HFXor_EtotHF_VS_RT_HFXor_M"];
//                        histofill_RT_EtotHF_VS_pt = hist2D["RT_HFXor_EtotHF_VS_RT_HFXor_pt"];
                  
                        //Events selected at detector level but filling at gen level
                    if (kContainsGenLevel){
                        histofill_GT_tower_eta          = hist1D["GT_HFXor_tower_eta"];
                        histofill_GT_tower_pt           = hist1D["GT_HFXor_tower_pt"];
                        histofill_GT_tower_multi        = hist1D["GT_HFXor_tower_M"];
                        histofill_GT_tower_EtotHF       = hist1D["GT_HFXor_tower_EtotHF"];
                    } 
                    }
        
                    //HF_And selection, both sides of HF always.  
                    else if(CTmaxHFminus>CTcut && CTmaxHFplus>CTcut){
        
                        NRAnd++;   //Counter for normalization 
//                        RTisHFAnd = 1;
                        histofill_RT_tower_eta          = hist1D["RT_HFAnd_tower_eta"];
                        histofill_RT_tower_pt           = hist1D["RT_HFAnd_tower_pt"];
                        histofill_RT_tower_multi        = hist1D["RT_HFAnd_tower_M"];
                        histofill_RT_tower_EtotHF       = hist1D["RT_HFAnd_tower_EtotHF"];
//                        histofill_RT_EtotHF_VS_M  = hist2D["RT_HFAnd_EtotHF_VS_RT_HFAnd_M"];
//                        histofill_RT_EtotHF_VS_pt = hist2D["RT_HFAnd_EtotHF_VS_RT_HFAnd_pt"];
                   
                        //Events selected at detector level but filling at gen level
                    if (kContainsGenLevel){
                        histofill_GT_tower_eta    = hist1D["GT_HFAnd_tower_eta"];
                        histofill_GT_tower_pt     = hist1D["GT_HFAnd_tower_pt"];
                        histofill_GT_tower_multi  = hist1D["GT_HFAnd_tower_M"];
                        histofill_GT_tower_EtotHF = hist1D["GT_HFAnd_tower_EtotHF"];
                    } 
                    }
                }
                
                else {
                        NRNo++;
                        histofill_RT_tower_eta          = hist1D["RT_NoHF_tower_eta"];
                        histofill_RT_tower_pt           = hist1D["RT_NoHF_tower_pt"];
                        histofill_RT_tower_multi        = hist1D["RT_NoHF_tower_M"];
                        histofill_RT_tower_EtotHF       = hist1D["RT_NoHF_tower_EtotHF"];
//                        histofill_RT_EtotHF_VS_M  = hist2D["RT_NoHF_EtotHF_VS_RT_NoHF_M"];
//                        histofill_RT_EtotHF_VS_pt = hist2D["RT_NoHF_EtotHF_VS_RT_NoHF_pt"];
               
                        //Events selected at detector level but filling at gen level
                    if (kContainsGenLevel){
                        histofill_GT_tower_eta    = hist1D["GT_NoHF_tower_eta"];
                        histofill_GT_tower_pt     = hist1D["GT_NoHF_tower_pt"];
                        histofill_GT_tower_multi  = hist1D["GT_NoHF_tower_M"];
                        histofill_GT_tower_EtotHF = hist1D["GT_NoHF_tower_EtotHF"];
                    }
                }

    }//End vertex quality "if"


//**********************  For GenParticles ************************//

        if (kContainsGenLevel)
        {

            // test GT
            unsigned int ngentracks = 0; // #tracks passing the cutoffs

            double EmaxHFminus = 0.,
                   EmaxHFplus  = 0.;

            double EtotHFminus = 0.,
                   EtotHFplus  = 0.;

           
            //GT maximum energy in HF+/- for following event selection
            for (unsigned int itrack = 0 ; itrack < GT.pt->size() ; itrack++)
            { 
             //Only final state particles will continue
             if(GT.status->at(itrack)!=1) continue; 

                //HF plus
                if (   GT.eta->at(itrack) > minRHeta
                    && GT.eta->at(itrack) < maxRHeta)
                {
                    EmaxHFplus = max(EmaxHFplus, GT.energy->at(itrack));
                    EtotHFplus += GT.energy->at(itrack);
                }

                //HF minus
                if (   GT.eta->at(itrack) < -minRHeta
                    && GT.eta->at(itrack) > -maxRHeta)
                {
                    EmaxHFminus = max(EmaxHFminus, GT.energy->at(itrack));
                    EtotHFminus += GT.energy->at(itrack);
                }
            }
           

           //GT event selection
                //HF_Or selection, at least one side of HF
                if(EmaxHFminus>Ecut || EmaxHFplus>Ecut){
                    
                    //Note that HF_Xor and HF_And are inside HF_Or since they are a subgroup
                    //HF_Xor selection, only one side of HF
                    if((EmaxHFminus>Ecut && EmaxHFplus<Ecut) || (EmaxHFminus<Ecut && EmaxHFplus>Ecut)){
                        
                        NGXor++; //Counter for normalization 
//                        GTisHFXor = 1;
                        histofill_GT_4vector_eta          = hist1D["GT_HFXor_4vector_eta"];
                        histofill_GT_4vector_pt           = hist1D["GT_HFXor_4vector_pt"];
                        histofill_GT_4vector_multi        = hist1D["GT_HFXor_4vector_M"];
                        histofill_GT_4vector_EtotHF       = hist1D["GT_HFXor_4vector_EtotHF"];
                      //  histofill_GT_EtotHF_VS_M  = hist2D["GT_HFXor_EtotHF_VS_GT_HFXor_M"];
                      //  histofill_GT_EtotHF_VS_pt = hist2D["GT_HFXor_EtotHF_VS_GT_HFXor_pt"]; 
                        
                        //Events selected at gen level but to be filled at reco level
                        histofill_RT_4vector_eta          = hist1D["RT_HFXor_4vector_eta"];
                        histofill_RT_4vector_pt           = hist1D["RT_HFXor_4vector_pt"];
                        histofill_RT_4vector_multi        = hist1D["RT_HFXor_4vector_M"];
                        histofill_RT_4vector_EtotHF       = hist1D["RT_HFXor_4vector_EtotHF"];
                    }
        
                    //HF_And selection, both sides of HF always.  
                    else if(EmaxHFminus>Ecut && EmaxHFplus>Ecut){
        
                        NGAnd++;   //Counter for normalization 
//                        GTisHFAnd = 1;
                        histofill_GT_4vector_eta    = hist1D["GT_HFAnd_4vector_eta"];
                        histofill_GT_4vector_pt     = hist1D["GT_HFAnd_4vector_pt"];
                        histofill_GT_4vector_multi  = hist1D["GT_HFAnd_4vector_M"];
                        histofill_GT_4vector_EtotHF = hist1D["GT_HFAnd_4vector_EtotHF"];
                     //   histofill_GT_EtotHF_VS_M = hist2D["GT_HFAnd_EtotHF_VS_GT_HFAnd_M"];
                     //   histofill_GT_EtotHF_VS_pt = hist2D["GT_HFAnd_EtotHF_VS_GT_HFAnd_pt"];
                        
                        //Events selected at gen level but to be filled at reco level
                        histofill_RT_4vector_eta          = hist1D["RT_HFAnd_4vector_eta"];
                        histofill_RT_4vector_pt           = hist1D["RT_HFAnd_4vector_pt"];
                        histofill_RT_4vector_multi        = hist1D["RT_HFAnd_4vector_M"];
                        histofill_RT_4vector_EtotHF       = hist1D["RT_HFAnd_4vector_EtotHF"];
                    }
                }
                
                else {
                        NGNo++;
                        histofill_GT_4vector_eta    = hist1D["GT_NoHF_4vector_eta"];
                        histofill_GT_4vector_pt     = hist1D["GT_NoHF_4vector_pt"];
                        histofill_GT_4vector_multi  = hist1D["GT_NoHF_4vector_M"];
                        histofill_GT_4vector_EtotHF = hist1D["GT_NoHF_4vector_EtotHF"];
                     //   histofill_GT_EtotHF_VS_M = hist2D["GT_NoHF_EtotHF_VS_GT_NoHF_M"];
                     //   histofill_GT_EtotHF_VS_pt = hist2D["GT_NoHF_EtotHF_VS_GT_NoHF_pt"];
                        
                        //Events selected at gen level but to be filled at reco level
                        histofill_RT_4vector_eta          = hist1D["RT_NoHF_4vector_eta"];
                        histofill_RT_4vector_pt           = hist1D["RT_NoHF_4vector_pt"];
                        histofill_RT_4vector_multi        = hist1D["RT_NoHF_4vector_M"];
                        histofill_RT_4vector_EtotHF       = hist1D["RT_NoHF_4vector_EtotHF"];
                }
       
//################################ FILLING HISTOGRAMS #########################################

       

            //GT loop
            for (unsigned int itrack = 0 ; itrack < GT.pt->size() ; itrack++)
            {




                if (       GT.pt ->at(itrack)  > minpt          //Minimum quiality pt (for this analysis should be 0.1 or 0.2GeV
                    && abs(GT.eta->at(itrack)) < maxtracketa    //Only particles in the tracker acceptance 
                    && abs(GT.charge->at(itrack))==1            //Only charged particles 
                    && GT.status->at(itrack)==1)                //Only final state stable particles
                {
                    ngentracks++; 
                    if(histofill_GT_tower_eta != 0x0) histofill_GT_tower_eta->Fill(GT.eta->at(itrack));
                    if(histofill_GT_4vector_eta != 0x0) histofill_GT_4vector_eta->Fill(GT.eta->at(itrack));
                    if(histofill_GT_tower_pt != 0x0) histofill_GT_tower_pt->Fill(GT.pt->at(itrack));
                    if(histofill_GT_4vector_pt != 0x0) histofill_GT_4vector_pt->Fill(GT.pt->at(itrack));
//                    if(histofill_GT_EtotHF_VS_pt != 0x0) histofill_GT_EtotHF_VS_pt->Fill(EtotHFminus+EtotHFplus,GT.pt->at(itrack) );
                }
            }
           
            //Once per event
            if(histofill_GT_tower_multi != 0x0) histofill_GT_tower_multi->Fill(ngentracks);
            if(histofill_GT_4vector_multi != 0x0) histofill_GT_4vector_multi->Fill(ngentracks);
            if(histofill_GT_tower_EtotHF != 0x0) histofill_GT_tower_EtotHF->Fill(EtotHFminus+EtotHFplus);
            if(histofill_GT_4vector_EtotHF != 0x0) histofill_GT_4vector_EtotHF->Fill(EtotHFminus+EtotHFplus);
//            if(histofill_GT_EtotHF_VS_M != 0x0) histofill_GT_EtotHF_VS_M->Fill(EtotHFminus+EtotHFplus, ngentracks); 
//            ngentracksout = ngentracks;

           }//End "if" for only when there is Generator level
            
        
        //RT loop    
            for (unsigned int itrack = 0 ; itrack < RT.pt->size() ; itrack++)
            {


                //For track quality
                RT_dxy  = RT.dxy      -> at(itrack);  
                RT_sdxy = RT.dxyError -> at(itrack); 
                RT_dz   = RT.dz       -> at(itrack); 
                RT_sdz  = RT.dzError  -> at(itrack); 
               // if(RT_dxy/RT_sdxy>3 || RT_dz/RT_sdz>3) continue;  //Track quality selection
                //--

                if (   RT.pt ->at(itrack) > minpt   
                    && abs(RT.eta->at(itrack)) < maxtracketa
                    && abs(RT.charge->at(itrack))==1
                    && RT_dxy/RT_sdxy<3
                    && RT_dz/RT_sdz<3) 
                {
                    nrectracks++; 
                    if(histofill_RT_tower_eta != 0x0) histofill_RT_tower_eta->Fill(RT.eta->at(itrack));
                    if(histofill_RT_4vector_eta != 0x0) histofill_RT_4vector_eta->Fill(RT.eta->at(itrack));
                    if(histofill_RT_tower_pt != 0x0) histofill_RT_tower_pt->Fill(RT.pt->at(itrack));
                    if(histofill_RT_4vector_pt != 0x0) histofill_RT_4vector_pt->Fill(RT.pt->at(itrack));
//                    if(histofill_RT_EtotHF_VS_pt != 0x0) histofill_RT_EtotHF_VS_pt->Fill(CTtotHFminus+CTtotHFplus,RT.pt->at(itrack) );
                }
            }


            //Once per event 
            if(histofill_RT_tower_multi != 0x0) histofill_RT_tower_multi->Fill(nrectracks);
            if(histofill_RT_4vector_multi != 0x0) histofill_RT_4vector_multi->Fill(nrectracks);
            if(histofill_RT_tower_EtotHF != 0x0) histofill_RT_tower_EtotHF->Fill(CTtotHFminus+CTtotHFplus);
            if(histofill_RT_4vector_EtotHF != 0x0) histofill_RT_4vector_EtotHF->Fill(CTtotHFminus+CTtotHFplus);
//            if(histofill_RT_EtotHF_VS_M != 0x0) histofill_RT_EtotHF_VS_M->Fill(CTtotHFminus+CTtotHFplus, nrectracks); 
//
//
//            //Multiplicity responce matrix
//            if(GTisHFAnd == 1 && RTisHFAnd == 1){
//                hist2D["RT_HFAnd_M_VS_GT_HFAnd_M"]->Fill(nrectracks,ngentracksout);
//                hist2D["RT_HFOr_M_VS_GT_HFOr_M"]->Fill(nrectracks,ngentracksout);
//            }
//            if(GTisHFXor == 1 && RTisHFXor == 1){
//                hist2D["RT_HFXor_M_VS_GT_HFXor_M"]->Fill(nrectracks,ngentracksout);
//                hist2D["RT_HFOr_M_VS_GT_HFOr_M"]->Fill(nrectracks,ngentracksout);
//            }
            //if((GTisHFAnd == 1 && RTisHFAnd == 1) || (GTisHFXor == 1 && RTisHFXor == 1))hist2D["RT_HFOr_M_VS_GT_HFOr_M"]->Fill(nrectracks,ngentracksout);
    }
    cout << "Loop: 100%!!" << endl;


    /*************** Adding And+Xor histograms to create Or histograms *****************************/
        
    if (kContainsGenLevel){
        //GT
        for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
        {
            TString name = TString::Format("GT_HFOr_tower_%s", proto_tracks2[ikin]->GetName());
            hist1D[name]->Add   (hist1D[TString::Format("GT_HFAnd_tower_%s",proto_tracks2[ikin]->GetName())]);   
            hist1D[name]->Add   (hist1D[TString::Format("GT_HFXor_tower_%s",proto_tracks2[ikin]->GetName())]);   
            
            name = TString::Format("GT_HFOr_4vector_%s", proto_tracks2[ikin]->GetName());
            hist1D[name]->Add   (hist1D[TString::Format("GT_HFAnd_4vector_%s",proto_tracks2[ikin]->GetName())]);   
            hist1D[name]->Add   (hist1D[TString::Format("GT_HFXor_4vector_%s",proto_tracks2[ikin]->GetName())]);   
        }
    

//            TString name = TString::Format("GT_HFOr_EtotHF_VS_GT_HFOr_M");
//            hist2D[name]->Add   (hist2D[TString::Format("GT_HFAnd_EtotHF_VS_GT_HFAnd_M")]);   
//            hist2D[name]->Add   (hist2D[TString::Format("GT_HFXor_EtotHF_VS_GT_HFXor_M")]);   
//
//            name = TString::Format("GT_HFOr_EtotHF_VS_GT_HFOr_pt");
//            hist2D[name]->Add   (hist2D[TString::Format("GT_HFAnd_EtotHF_VS_GT_HFAnd_pt")]);   
//            hist2D[name]->Add   (hist2D[TString::Format("GT_HFXor_EtotHF_VS_GT_HFXor_pt")]);   
    }


        //RT
        for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
        {
            TString name = TString::Format("RT_HFOr_tower_%s", proto_tracks2[ikin]->GetName());
            hist1D[name]->Add   (hist1D[TString::Format("RT_HFAnd_tower_%s",proto_tracks2[ikin]->GetName())]);   
            hist1D[name]->Add   (hist1D[TString::Format("RT_HFXor_tower_%s",proto_tracks2[ikin]->GetName())]);   
            
            name = TString::Format("RT_HFOr_4vector_%s", proto_tracks2[ikin]->GetName());
            hist1D[name]->Add   (hist1D[TString::Format("RT_HFAnd_4vector_%s",proto_tracks2[ikin]->GetName())]);   
            hist1D[name]->Add   (hist1D[TString::Format("RT_HFXor_4vector_%s",proto_tracks2[ikin]->GetName())]);   
        }

//            name = TString::Format("RT_HFOr_EtotHF_VS_RT_HFOr_M");
//            hist2D[name]->Add   (hist2D[TString::Format("RT_HFAnd_EtotHF_VS_RT_HFAnd_M")]);   
//            hist2D[name]->Add   (hist2D[TString::Format("RT_HFXor_EtotHF_VS_RT_HFXor_M")]);   
//
//            name = TString::Format("RT_HFOr_EtotHF_VS_RT_HFOr_pt");
//            hist2D[name]->Add   (hist2D[TString::Format("RT_HFAnd_EtotHF_VS_RT_HFAnd_pt")]);   
//            hist2D[name]->Add   (hist2D[TString::Format("RT_HFXor_EtotHF_VS_RT_HFXor_pt")]);   
    
    /*************** NORMALIZATION OF HISTOGRAMS *****************************/
    //Normalizing to the number of selected events
    //NGAnd/Xor/Or = Number of HFAnd/Xor/Or events for GenParticles
    //NRAnd/Xor/Or = Number of HFAnd/Xor/Or events for RecTracks
   
    //Scaling factor for bin as deffined at the top of the file.


        //GT and RT in a single loop. Bin whith and # of selected events 
//        for (unsigned int ikin = 0 ; ikin < 1 ; ikin++) //Just for eta destribution.
//        {
//            TString name = TString::Format("GT_HFOr_%s", proto_tracks2[ikin]->GetName());
//            hist1D[name]->Scale(1.0/(binWidth*(NGAnd+NGXor)));   
//            name = TString::Format("RT_HFOr_%s", proto_tracks2[ikin]->GetName());
//            hist1D[name]->Scale(1.0/(binWidth*(NRAnd+NRXor)));   
//           
//            name = TString::Format("GT_HFAnd_%s", proto_tracks2[ikin]->GetName());
//            hist1D[name]->Scale(1.0/(binWidth*NGAnd));   
//            name = TString::Format("RT_HFAnd_%s", proto_tracks2[ikin]->GetName());
//            hist1D[name]->Scale(1.0/(binWidth*NRAnd));   
//            
//            name = TString::Format("GT_HFXor_%s", proto_tracks2[ikin]->GetName());
//            hist1D[name]->Scale(1.0/(binWidth*NGXor));   
//            name = TString::Format("RT_HFXor_%s", proto_tracks2[ikin]->GetName());
//            hist1D[name]->Scale(1.0/(binWidth*NRXor));   
//        }


        for (unsigned int ikin = 0 ; ikin < 1 ; ikin++) //Just for eta  destributions.
        {
            
            
        if (kContainsGenLevel){
            TString name = TString::Format("GT_HFOr_tower_%s", proto_tracks2[ikin]->GetName());
            hist1D[name]->Scale(1.0/(binWidth));   
            
            name = TString::Format("GT_HFAnd_tower_%s", proto_tracks2[ikin]->GetName());
            hist1D[name]->Scale(1.0/(binWidth));   
            
            name = TString::Format("GT_HFXor_tower_%s", proto_tracks2[ikin]->GetName());
            hist1D[name]->Scale(1.0/(binWidth));   
            
            name = TString::Format("GT_HFOr_4vector_%s", proto_tracks2[ikin]->GetName());
            hist1D[name]->Scale(1.0/(binWidth));   
            
            name = TString::Format("GT_HFAnd_4vector_%s", proto_tracks2[ikin]->GetName());
            hist1D[name]->Scale(1.0/(binWidth));   
            
            name = TString::Format("GT_HFXor_4vector_%s", proto_tracks2[ikin]->GetName());
            hist1D[name]->Scale(1.0/(binWidth));   
        }    
            
            
            TString  name1 = TString::Format("RT_HFOr_tower_%s", proto_tracks2[ikin]->GetName());
            hist1D[name1]->Scale(1.0/(binWidth));   
           
            name1 = TString::Format("RT_HFAnd_tower_%s", proto_tracks2[ikin]->GetName());
            hist1D[name1]->Scale(1.0/(binWidth));   
            
            name1 = TString::Format("RT_HFXor_tower_%s", proto_tracks2[ikin]->GetName());
            hist1D[name1]->Scale(1.0/(binWidth));   
            
            name1 = TString::Format("RT_HFOr_4vector_%s", proto_tracks2[ikin]->GetName());
            hist1D[name1]->Scale(1.0/(binWidth));   
           
            name1 = TString::Format("RT_HFAnd_4vector_%s", proto_tracks2[ikin]->GetName());
            hist1D[name1]->Scale(1.0/(binWidth));   
            
            name1 = TString::Format("RT_HFXor_4vector_%s", proto_tracks2[ikin]->GetName());
            hist1D[name1]->Scale(1.0/(binWidth));   
        }

        for (unsigned int ikin = 1 ; ikin < 2 ; ikin++) //Just for pt destributions.
        {
        
        if (kContainsGenLevel){
            
            TString name = TString::Format("GT_HFOr_tower_%s", proto_tracks2[ikin]->GetName());
            hist1D[name]->Scale(1.0/(binWidthpt));   
            
            name = TString::Format("GT_HFAnd_tower_%s", proto_tracks2[ikin]->GetName());
            hist1D[name]->Scale(1.0/(binWidthpt));   
            
            name = TString::Format("GT_HFXor_tower_%s", proto_tracks2[ikin]->GetName());
            hist1D[name]->Scale(1.0/(binWidthpt));   
           
            name = TString::Format("GT_HFOr_4vector_%s", proto_tracks2[ikin]->GetName());
            hist1D[name]->Scale(1.0/(binWidthpt));   

            name = TString::Format("GT_HFAnd_4vector_%s", proto_tracks2[ikin]->GetName());
            hist1D[name]->Scale(1.0/(binWidthpt));   

            name = TString::Format("GT_HFXor_4vector_%s", proto_tracks2[ikin]->GetName());
            hist1D[name]->Scale(1.0/(binWidthpt));   
        }


            TString name1 = TString::Format("RT_HFOr_tower_%s", proto_tracks2[ikin]->GetName());
            hist1D[name1]->Scale(1.0/(binWidthpt));   
           
            name1 = TString::Format("RT_HFAnd_tower_%s", proto_tracks2[ikin]->GetName());
            hist1D[name1]->Scale(1.0/(binWidthpt));   
            
            name1 = TString::Format("RT_HFXor_tower_%s", proto_tracks2[ikin]->GetName());
            hist1D[name1]->Scale(1.0/(binWidthpt));   
            
            name1 = TString::Format("RT_HFOr_4vector_%s", proto_tracks2[ikin]->GetName());
            hist1D[name1]->Scale(1.0/(binWidthpt));   
           
            name1 = TString::Format("RT_HFAnd_4vector_%s", proto_tracks2[ikin]->GetName());
            hist1D[name1]->Scale(1.0/(binWidthpt));   
            
            name1 = TString::Format("RT_HFXor_4vector_%s", proto_tracks2[ikin]->GetName());
            hist1D[name1]->Scale(1.0/(binWidthpt));   
        }

    /*************** EFFICIENCIES AND RATIOS *****************************/
//
//
//    if  (kContainsGenLevel)
//    {
//        cout << "Computing ratios" << endl;
//        // ratio of generated tracks over reconstructed tracks
//        for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
//        {
//            TString name = TString::Format("ratio_tracks_HFAnd_%s", proto_tracks2[ikin]->GetName());
//            hist1D[name] = (TH1D *) proto_tracks2[ikin]->Clone(name);
//            hist1D[name]->SetTitle(TString::Format("%s efficiency", proto_tracks2[ikin]->GetTitle()));
//            hist1D[name]->SetYTitle("gen/reco");
//            hist1D[name]->Add   (hist1D[TString::Format("GT_HFAnd_%s",proto_tracks2[ikin]->GetName())]);   // numerator   = RECO
//            hist1D[name]->Divide(hist1D[TString::Format("RT_HFAnd_%s",proto_tracks2[ikin]->GetName())]);   // denominator = GEN 
//        }
//        for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
//        {
//            TString name = TString::Format("ratio_tracks_HFXor_%s", proto_tracks2[ikin]->GetName());
//            hist1D[name] = (TH1D *) proto_tracks2[ikin]->Clone(name);
//            hist1D[name]->SetTitle(TString::Format("%s efficiency", proto_tracks2[ikin]->GetTitle()));
//            hist1D[name]->SetYTitle("gen/reco");
//            hist1D[name]->Add   (hist1D[TString::Format("GT_HFXor_%s",proto_tracks2[ikin]->GetName())]);   // numerator   = RECO
//            hist1D[name]->Divide(hist1D[TString::Format("RT_HFXor_%s",proto_tracks2[ikin]->GetName())]);   // denominator = GEN 
//        }
//        for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
//        {
//            TString name = TString::Format("ratio_tracks_HFOr_%s", proto_tracks2[ikin]->GetName());
//            hist1D[name] = (TH1D *) proto_tracks2[ikin]->Clone(name);
//            hist1D[name]->SetTitle(TString::Format("%s efficiency", proto_tracks2[ikin]->GetTitle()));
//            hist1D[name]->SetYTitle("gen/reco");
//            hist1D[name]->Add   (hist1D[TString::Format("GT_HFOr_%s",proto_tracks2[ikin]->GetName())]);   // numerator   = RECO
//            hist1D[name]->Divide(hist1D[TString::Format("RT_HFOr_%s",proto_tracks2[ikin]->GetName())]);   // denominator = GEN 
//        }
//
//
//        //2D histo ratios
//
//            //HFAnd
//            TString name = TString::Format("ratio_HFAnd_EtotHF_VS_M");
//            hist2D[name] = (TH2D *) hist2D["RT_HFAnd_EtotHF_VS_RT_HFAnd_M"]->Clone(name); 
//            hist2D[name]->Divide   (hist2D["GT_HFAnd_EtotHF_VS_GT_HFAnd_M"]);   
//            hist2D[name]->SetTitle(TString::Format("(Reco EtotHF_vs_M)/(Gen EtotHF_vs_M) for HFAnd"));
//            hist2D[name]->SetYTitle("EtotHF reco/gen");
//            hist2D[name]->SetXTitle("M reco/gen");
//
//            //HFXor
//            name = TString::Format("ratio_HFXor_EtotHF_VS_M");
//            hist2D[name] = (TH2D *) hist2D["RT_HFXor_EtotHF_VS_RT_HFXor_M"]->Clone(name); 
//            hist2D[name]->Divide   (hist2D["GT_HFXor_EtotHF_VS_GT_HFXor_M"]);   
//            hist2D[name]->SetTitle(TString::Format("(Reco EtotHF_vs_M)/(Gen EtotHF_vs_M) for HFXor"));
//            hist2D[name]->SetYTitle("EtotHF reco/gen");
//            hist2D[name]->SetXTitle("M reco/gen");
//
//            //HFOr
//            name = TString::Format("ratio_HFOr_EtotHF_VS_M");
//            hist2D[name] = (TH2D *) hist2D["RT_HFOr_EtotHF_VS_RT_HFOr_M"]->Clone(name); 
//            hist2D[name]->Divide   (hist2D["GT_HFOr_EtotHF_VS_GT_HFOr_M"]);  
//            hist2D[name]->SetTitle(TString::Format("(Reco EtotHF_vs_M)/(Gen EtotHF_vs_M) for HFOr"));
//            hist2D[name]->SetYTitle("EtotHF reco/gen");
//            hist2D[name]->SetXTitle("M reco/gen");
//
//
//        // same in the particular case of pt in eta bins
//        for (unsigned int ieta = 0 ; ieta < NETABIN ; ieta++)
//        {
//            TString name = TString::Format("ratio_tracks_pt_%d", ieta);
//            hist1D[name] = (TH1D *) proto_tracks[0]->Clone(name); // 0 = pt
//            hist1D[name]->SetTitle(TString::Format("transverse momentum of the reconstructed tracks in %f < |#eta| < %f", ieta*ETABINWIDTH, (ieta+1)*ETABINWIDTH));
//            hist1D[name]->SetYTitle("gen/reco");
//            hist1D[name]->Add   (hist1D[TString::Format("RT_pt_%d",ieta)]);   // numerator   = RECO
//            hist1D[name]->Divide(hist1D[TString::Format("GT_pt_%d",ieta)]);   // denominator = GEN 
//        }
//    }

    /************************* TERMINAL MESSAGES  *******************************/
   
    
        cout<<"------------------------------------------------------"<<endl;
        cout<<"Number of events   = "<<nentries<<" (100%)"<<endl;
        cout<<"------------------------------------------------------"<<endl;
        cout<<"Number of GenHFAnd = "<<NGAnd<<" ("<<100.0*NGAnd/nentries<<"%)"<<endl;
        cout<<"Number of GenHFXor = "<<NGXor<<" ("<<100.0*NGXor/nentries<<"%)"<<endl;
        cout<<"Number of GenHFOr  = "<<NGAnd+NGXor<<" ("<<100.0*(NGXor+NGAnd)/nentries<<"%)"<<endl;
        cout<<"Number of GenNoHF  = "<<NGNo<<" ("<<100.0*NGNo/nentries<<"%)"<<endl;
        cout<<"------------------------------------------------------"<<endl;
        cout<<"Number of RecHFAnd = "<<NRAnd<<" ("<<100.0*NRAnd/nentries<<"%)"<<endl;
        cout<<"Number of RecHFXor = "<<NRXor<<" ("<<100.0*NRXor/nentries<<"%)"<<endl;
        cout<<"Number of RecHFOr  = "<<NRAnd+NRXor<<" ("<<100.0*(NRAnd+NRXor)/nentries<<"%)"<<endl;
        cout<<"Number of RecNoHF  = "<<NRNo<<" ("<<100.0*NRNo/nentries<<"%)"<<endl;
        cout<<"------------------------------------------------------"<<endl;
        cout<<"--------------------- RATIOS -------------------------"<<endl;
        cout<<"-------------------- Rec/Gen -------------------------"<<endl;
        cout<<"And  -> "<<NRAnd/NGAnd<<endl;
        cout<<"Xor  -> "<<NRXor/NGXor<<endl;
        cout<<"Or   -> "<<(NRAnd+NRXor)/(NGAnd+NGXor)<<endl;
        cout<<"NoHF -> "<<NRNo/NGNo<<endl;
        cout<<"------------------------------------------------------"<<endl;
    
    /************************* SAVING *******************************/

    TString outputfilename = TString::Format("_" __FILE__ "_pt_gt_%.2f_eta_st_%.2f", minpt, maxtracketa); // 1) it should include the phase space
    outputfilename.ReplaceAll(".", "_"); // replace . by _ in the given values of the phase space
    outputfilename = path_to_tree + outputfilename; // it should specify the name of the input file
    outputfilename.ReplaceAll("bonsai", "plots"); // but without the .root that would appear in the middle...
    outputfilename += ".root"; // and add .root at the end of the filename
    cout << "Saving histograms into " << outputfilename << endl;

    TFile * f = new TFile (outputfilename, "RECREATE");
    // this loop just runs over all the TH1D to save them
    // (note: here we use an iterator to run over the map)
#define WRITE(HISTOTYPE, HISTOMAP) for (map<TString,HISTOTYPE *>::iterator it_hist = HISTOMAP.begin() ; it_hist != HISTOMAP.end() ; it_hist++) it_hist->second->Write();
    WRITE(TH1D, hist1D);
    //WRITE(TH2D, hist2D);
#undef WRITE
    f->Close();
    cout << "File closed." << endl;

    /*********************** PRINTING *************************/

    // NOT HERE
    // TODO: later in different file... (e.g. plotfast_*.C in the data directory)
}

#include "main.cc"
