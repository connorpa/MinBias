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
#include <TGraph.h>

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
   // const unsigned short int NKIN = 4; // KINematics, plus multiplicity
                             //ETABIN = 4; // 4 eta bins of width 0.6 
                             //NDIR = 3; // DIRections
    //const double ETABINWIDTH = maxtracketa/((double) NETABIN);

    /************************* BOOKING HISTOGRAMS *****************************/

    cout << "Booking histograms..." << endl;

    // those variables are defined to take advantage of the maps
    // i.e. the map can be looped only over a small section of
    // we define constant proto histograms, whose purpose is only to be cloned, to ensure to have always the same structure
    //TH1D * h = new TH1D (name, title, nbins, xlow, xup);
   
//     const TH1D * proto_tracks2[NKIN] = {new const TH1D ("eta", "pseudorapidity;#eta;#entries",  50,  -2.4,  2.4),
//                                         new const TH1D ("pt" , "transverse momentum;p_T/GeV;#entries",   50,     0,   5),
//                                         new const TH1D ("M"  , "multiplicity;M;#enitres",       300,     0,  300),
//                                         new const TH1D ("EtotHF", "Total HF energy;E_HF_tot/GeV;#entries",1000,0.,1000.)};


    
    map<TString, TH1D *> hist1D; // i.e. map["string"] = histogram (use "iterators" to run over a map--see below)
    map<TString, TH2D *> hist2D;
    map<TString, TGraph *> graph;
    // reconstructed tracks

//        for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
//        {
//            TString name = TString::Format("RT_HFAnd_%s", proto_tracks2[ikin]->GetName());
//            hist1D[name] = (TH1D *) proto_tracks2[ikin]->Clone(name);
//            hist1D[name]->SetTitle(TString::Format("%s of the reconstructed tracks with HFAnd(det) selection", proto_tracks2[ikin]->GetTitle()));
//            hist1D[name]->SetXTitle(proto_tracks2[ikin]->GetXaxis()->GetTitle());
//            hist1D[name]->SetYTitle(proto_tracks2[ikin]->GetYaxis()->GetTitle());
//        }



    
    // the same at gen level
//    if (kContainsGenLevel)
//    {   // create histograms for gen level with the exact same structure
//
//    }
    // energy deposit in the forward calorimeter
    //hist1D["forward_energy"] = new TH1D ("forward_energy", "forward energy deposit;E/GeV;#entries", 100, 0, 100);
    //hist1D["rechit_energy"]  = new TH1D ("rechit_energy" ,  "rechit energy deposit;E/GeV;#entries", 100, 0, 100);

    hist1D["GT_E_leading_HFminus"] = new TH1D ("GT_E_leading_HFminus", "Leading E particle in HFminus;Energy/GeV;#entries", 100, 0, 100);
    hist1D["GT_E_leading_HFplus"] = new TH1D ("GT_E_leading_HFplus", "Leading E particle in HFplus;Energy/GeV;#entries", 100, 0, 100);
    hist1D["RT_E_leading_HFminus"] = new TH1D ("RT_E_leading_HFminus", "Leading E particle in HFminus;Energy/GeV;#entries", 100, 0, 100);
    hist1D["RT_E_leading_HFplus"] = new TH1D ("RT_E_leading_HFplus", "Leading E particle in HFplus;Energy/GeV;#entries", 100, 0, 100);
    hist1D["GT_E_leading_HF"] = new TH1D ("GT_E_leading_HF", "Leading E particle in HF;Energy/GeV;#entries", 100, 0, 100);
    hist1D["RT_E_leading_HF"] = new TH1D ("RT_E_leading_HF", "Leading E particle in HF;Energy/GeV;#entries", 100, 0, 100);


    graph["g_RT_E_leading_HFminus_VS_GT_E_leading_HFminus"] = new TGraph();
    graph["g_RT_E_leading_HFplus_VS_GT_E_leading_HFplus"]   = new TGraph();
    graph["g_RT_E_leading_HF_VS_GT_E_leading_HF"]           = new TGraph();


    // this macro is used to define 2d histogram using the 1d histogram corresponding to the axes
#define DEFINE2DHIST(XNAME, YNAME, TITLE) \
    hist2D[XNAME "_VS_" YNAME] = new TH2D (#XNAME "_VS_" #YNAME, TITLE, \
                                            hist1D[XNAME]->GetNbinsX(), hist1D[XNAME]->GetXaxis()->GetXmin(), hist1D[XNAME]->GetXaxis()->GetXmax(), \
                                            hist1D[YNAME]->GetNbinsX(), hist1D[YNAME]->GetXaxis()->GetXmin(), hist1D[YNAME]->GetXaxis()->GetXmax())
  //  DEFINE2DHIST("RT_NoHF_M", "GT_NoHF_M" , "Reconstructed multiplicity VS Generated multiplicity for NoHF   ;M reco;M gen      ;#entries");
    DEFINE2DHIST("RT_E_leading_HFminus", "GT_E_leading_HFminus" , "Leading E tower VS leading E particle, for HFminus;Leading tower;Leading particle");
    DEFINE2DHIST("RT_E_leading_HFplus", "GT_E_leading_HFplus" , "Leading E tower VS leading E particle, for HFplus;Leading tower;Leading particle");
    DEFINE2DHIST("RT_E_leading_HF", "GT_E_leading_HF" , "Leading E tower VS leading E particle in HF;Leading tower;Leading particle");
#undef DEFINE2DHIST




    /******************* RUNNING OVER THE TREE ***********************/

    // counters
    const Long64_t nentries = (maxentries <= 0) ? fChain->GetEntriesFast() : min(fChain->GetEntriesFast(),maxentries);
    unsigned int progress = 0;  // counter  to see the progress of the loop
    Long64_t nbytes = 0, nb = 0; // dunno the use of this... (given by TTree::MakeClass())

    
   



     double NGAnd = 0,
            NGXor = 0,
            NGNo  = 0,  
            NRAnd = 0,
            NRXor = 0,
            NRNo  = 0;
    
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

//*********************** RecoTracks loop ***************************//

            //RT
            unsigned int nrectracks = 0; // #tracks passing the cutoffs
            double CTmaxHFminus = 0.,
                   CTmaxHFplus  = 0.;

            double CTtotHFminus = 0.,
                   CTtotHFplus  = 0.;
            
            //GT global variables
            double EmaxHFminus = 0.,
                   EmaxHFplus  = 0.;



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
                    if((CTmaxHFminus>CTcut && CTmaxHFplus<CTcut) || (CTmaxHFminus<CTcut && CTmaxHFplus>CTcut))  NRXor++; //Counter for normalization 
                    
                    //HF_And selection, both sides of HF always.  
                    else if(CTmaxHFminus>CTcut && CTmaxHFplus>CTcut)   NRAnd++;   //Counter for normalization 
                    
                }
                
                else  NRNo++;

                

            for (unsigned int itrack = 0 ; itrack < RT.pt->size() ; itrack++)
            {

                if (       RT.pt ->at(itrack)  > minpt   
                    && abs(RT.eta->at(itrack)) < maxtracketa
                    && abs(RT.charge->at(itrack))==1) 
                {
                    nrectracks++; 
                }
            }

//**********************  For GenParticles ************************//

        if (kContainsGenLevel)
        {

            // test GT
            unsigned int ngentracks = 0; // #tracks passing the cutoffs


            double EtotHFminus = 0.,
                   EtotHFplus  = 0.;

           
            //GT maximum energy in HF+/- for following event selection
            for (unsigned int itrack = 0 ; itrack < GT.pt->size() ; itrack++)
            { 

                //cout<<"Pt = "<< GT.pt->at(itrack)<<endl;

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
                    if((EmaxHFminus>Ecut && EmaxHFplus<Ecut) || (EmaxHFminus<Ecut && EmaxHFplus>Ecut))   NGXor++; //Counter for normalization 
        
                    //HF_And selection, both sides of HF always.  
                    else if(EmaxHFminus>Ecut && EmaxHFplus>Ecut)  NGAnd++;   //Counter for normalization 
                }
                
                else  NGNo++;
        


        
            for (unsigned int itrack = 0 ; itrack < GT.pt->size() ; itrack++)
            {

                if (       GT.pt ->at(itrack)  > minpt   
                    && abs(GT.eta->at(itrack)) < maxtracketa
                    && abs(GT.charge->at(itrack))==1) 
                {
                    ngentracks++; 
                
                }
            }
           

        }

    //Once per event
    //Leading energetic particles, filling histograms
     hist1D["GT_E_leading_HFminus"]->Fill(EmaxHFminus);
     hist1D["GT_E_leading_HFplus"]->Fill(EmaxHFplus);
     hist1D["RT_E_leading_HFminus"]->Fill(CTmaxHFminus);
     hist1D["RT_E_leading_HFplus"]->Fill(CTmaxHFplus);
     hist2D["RT_E_leading_HFminus_VS_GT_E_leading_HFminus"]->Fill(CTmaxHFminus,EmaxHFminus);
     hist2D["RT_E_leading_HFplus_VS_GT_E_leading_HFplus"]  ->Fill(CTmaxHFplus,EmaxHFplus);
    // graph["g_RT_E_leading_HFminus_VS_GT_E_leading_HFminus"] ->SetPoint(jentry,CTmaxHFminus,EmaxHFminus);
    // graph["g_RT_E_leading_HFplus_VS_GT_E_leading_HFplus"]   ->SetPoint(jentry,CTmaxHFplus,EmaxHFplus);
        //TODO: fix the implementation of the graphs  
    }
     cout << "Loop: 100%!!" << endl;


    /******* Adding And+Xor histograms to create Or histograms ************/

    hist2D["RT_E_leading_HF_VS_GT_E_leading_HF"] ->Add (hist2D["RT_E_leading_HFminus_VS_GT_E_leading_HFminus"]);
    hist2D["RT_E_leading_HF_VS_GT_E_leading_HF"] ->Add (hist2D["RT_E_leading_HFplus_VS_GT_E_leading_HFplus"]);
    
    //graph["g_RT_E_leading_HF_VS_GT_E_leading_HF"] -          
    /*************** NORMALIZATION OF HISTOGRAMS **************************/
    
    
    /***************** EFFICIENCIES AND RATIOS ****************************/



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
        cout<<"-------------------- Gen/Rec -------------------------"<<endl;
        cout<<"And  -> "<<NGAnd/NRAnd<<endl;
        cout<<"Xor  -> "<<NGXor/NRXor<<endl;
        cout<<"Or   -> "<<(NGAnd+NGXor)/(NRAnd+NRXor)<<endl;
        cout<<"NoHF -> "<<NGNo/NRNo<<endl;
        cout<<"------------------------------------------------------"<<endl;
 
        //To write an output file
 //       cout<<NGAnd/NRAnd<<endl;
 //       cout<<NGXor/NRXor<<endl;
 //       cout<<(NGAnd+NGXor)/(NRAnd+NRXor)<<endl;
    
    /************************* SAVING *******************************/

    TString outputfilename = TString::Format("_" __FILE__ "_pt_gt_%f_eta_st_%f", minpt, maxtracketa); // 1) it should include the phase space
    outputfilename.ReplaceAll(".", "_"); // replace . by _ in the given values of the phase space
    outputfilename = path_to_tree + outputfilename; // it should specify the name of the input file
    outputfilename.ReplaceAll("bonsai", "plots"); // but without the .root that would appear in the middle...
    outputfilename.ReplaceAll(".root", ""); // but without the .root that would appear in the middle...
    outputfilename += ".root"; // and add .root at the end of the filename
    cout << "Saving histograms into " << outputfilename << endl;

    TFile * f = new TFile (outputfilename, "RECREATE");
    // this loop just runs over all the TH1D to save them
    // (note: here we use an iterator to run over the map)
#define WRITE(HISTOTYPE, HISTOMAP) for (map<TString,HISTOTYPE *>::iterator it_hist = HISTOMAP.begin() ; it_hist != HISTOMAP.end() ; it_hist++) it_hist->second->Write();
    WRITE(TH1D, hist1D);
    WRITE(TH2D, hist2D);
    WRITE(TGraph, graph);
#undef WRITE
    f->Close();
    cout << "File closed." << endl;

    /*********************** PRINTING *************************/

    // NOT HERE
    // TODO: later in different file... (e.g. plotfast_*.C in the data directory)
}

#include "main.cc"
