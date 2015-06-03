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
                 Ecut  = 7.0, //HF Energy cut [GeV]
                 CTcut = 5.0; //CaloTower energy cut [GeV]
    const unsigned short int NKIN = 1; // KINematics, plus multiplicity
                             //ETABIN = 4; // 4 eta bins of width 0.6 
                             //NDIR = 3; // DIRections
    //const double ETABINWIDTH = maxtracketa/((double) NETABIN);

    /************************* BOOKING HISTOGRAMS *****************************/

    cout << "Booking histograms..." << endl;

    //Bin with of eta and pt histograms
    double binWhith   = 4.8/50.0; //bin whith of the eta histogram TODO: check the binwhith of TOTEM analysis


    // those variables are defined to take advantage of the maps
    // i.e. the map can be looped only over a small section of
    // we define constant proto histograms, whose purpose is only to be cloned, to ensure to have always the same structure
    //TH1D * h = new TH1D (name, title, nbins, xlow, xup);
   
     const TH1D * proto_tracks2[NKIN] = {new const TH1D ("eta", "pseudorapidity;#eta;#entries",  50,  -2.4,  2.4)};


               
              
    
    map<TString, TH1D *> hist1D; // i.e. map["string"] = histogram (use "iterators" to run over a map--see below)
    map<TString, TH2D *> hist2D;
    // reconstructed tracks

        for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
        {
            TString name = TString::Format("RT_HFAnd_%s", proto_tracks2[ikin]->GetName());
            hist1D[name] = (TH1D *) proto_tracks2[ikin]->Clone(name);
            hist1D[name]->SetTitle(TString::Format("%s of the reconstructed tracks with HFAnd(det) selection", proto_tracks2[ikin]->GetTitle()));
            hist1D[name]->SetXTitle(proto_tracks2[ikin]->GetXaxis()->GetTitle());
            hist1D[name]->SetYTitle(proto_tracks2[ikin]->GetYaxis()->GetTitle());
        }
        for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
        {
            TString name = TString::Format("RT_HFXor_%s", proto_tracks2[ikin]->GetName());
            hist1D[name] = (TH1D *) proto_tracks2[ikin]->Clone(name);
            hist1D[name]->SetTitle(TString::Format("%s of the reconstructed tracks with HFXor(det) selection", proto_tracks2[ikin]->GetTitle()));
            hist1D[name]->SetXTitle(proto_tracks2[ikin]->GetXaxis()->GetTitle());
            hist1D[name]->SetYTitle(proto_tracks2[ikin]->GetYaxis()->GetTitle());
        }
        for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
        {
            TString name = TString::Format("RT_HFOr_%s", proto_tracks2[ikin]->GetName());
            hist1D[name] = (TH1D *) proto_tracks2[ikin]->Clone(name);
            hist1D[name]->SetTitle(TString::Format("%s of the reconstructed tracks with HFOr(det) selection", proto_tracks2[ikin]->GetTitle()));
            hist1D[name]->SetXTitle(proto_tracks2[ikin]->GetXaxis()->GetTitle());
            hist1D[name]->SetYTitle(proto_tracks2[ikin]->GetYaxis()->GetTitle());
        }
        for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
        {
            TString name = TString::Format("RT_NoHF_%s", proto_tracks2[ikin]->GetName());
            hist1D[name] = (TH1D *) proto_tracks2[ikin]->Clone(name);
            hist1D[name]->SetTitle(TString::Format("%s of the reconstructed tracks with NoHF(det) selection", proto_tracks2[ikin]->GetTitle()));
            hist1D[name]->SetXTitle(proto_tracks2[ikin]->GetXaxis()->GetTitle());
            hist1D[name]->SetYTitle(proto_tracks2[ikin]->GetYaxis()->GetTitle());
        }


    
    // the same at gen level
    if (kContainsGenLevel)
    {   // create histograms for gen level with the exact same structure

        // generated tracks (charged particles might be a more appropriate term)
        for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
        {
            TString name = TString::Format("GT_HFAnd_%s", proto_tracks2[ikin]->GetName());
            hist1D[name] = (TH1D *) proto_tracks2[ikin]->Clone(name);
            hist1D[name]->SetTitle(TString::Format("%s of the generated tracks with HFAnd(det) selection", proto_tracks2[ikin]->GetTitle()));
            hist1D[name]->SetXTitle(proto_tracks2[ikin]->GetXaxis()->GetTitle());
            hist1D[name]->SetYTitle(proto_tracks2[ikin]->GetYaxis()->GetTitle());
        }
        for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
        {
            TString name = TString::Format("GT_HFXor_%s", proto_tracks2[ikin]->GetName());
            hist1D[name] = (TH1D *) proto_tracks2[ikin]->Clone(name);
            hist1D[name]->SetTitle(TString::Format("%s of the generated tracks with HFXor(det) selection", proto_tracks2[ikin]->GetTitle()));
            hist1D[name]->SetXTitle(proto_tracks2[ikin]->GetXaxis()->GetTitle());
            hist1D[name]->SetYTitle(proto_tracks2[ikin]->GetYaxis()->GetTitle());
        }
        for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
        {
            TString name = TString::Format("GT_HFOr_%s", proto_tracks2[ikin]->GetName());
            hist1D[name] = (TH1D *) proto_tracks2[ikin]->Clone(name);
            hist1D[name]->SetTitle(TString::Format("%s of the generated tracks with HFOr(det) selection", proto_tracks2[ikin]->GetTitle()));
            hist1D[name]->SetXTitle(proto_tracks2[ikin]->GetXaxis()->GetTitle());
            hist1D[name]->SetYTitle(proto_tracks2[ikin]->GetYaxis()->GetTitle());
        }
        for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
        {
            TString name = TString::Format("GT_NoHF_%s", proto_tracks2[ikin]->GetName());
            hist1D[name] = (TH1D *) proto_tracks2[ikin]->Clone(name);
            hist1D[name]->SetTitle(TString::Format("%s of the generated tracks with NoHF(det) selection", proto_tracks2[ikin]->GetTitle()));
            hist1D[name]->SetXTitle(proto_tracks2[ikin]->GetXaxis()->GetTitle());
            hist1D[name]->SetYTitle(proto_tracks2[ikin]->GetYaxis()->GetTitle());
        }
    }




    // this macro is used to define 2d histogram using the 1d histogram corresponding to the axes
#define DEFINE2DHIST(XNAME, YNAME, TITLE) \
    hist2D[XNAME "_VS_" YNAME] = new TH2D (#XNAME "_VS_" #YNAME, TITLE, \
                                            hist1D[XNAME]->GetNbinsX(), hist1D[XNAME]->GetXaxis()->GetXmin(), hist1D[XNAME]->GetXaxis()->GetXmax(), \
                                            hist1D[YNAME]->GetNbinsX(), hist1D[YNAME]->GetXaxis()->GetXmin(), hist1D[YNAME]->GetXaxis()->GetXmax())
//    DEFINE2DHIST("GT_HFAnd_EtotHF", "GT_HFAnd_M" , "Total Energy in HF VS Generated multiplicity for HFAnd   ;E/GeV;M      ;#entries");
#undef DEFINE2DHIST



//Container histograms to chose the histogram to fill after the eventselection

     TH1D* histofill_GT_eta          = 0x0;    // Pointer histogram to select the histogram we want for ETA 
     TH1D* histofill_RT_eta          = 0x0;    // Pointer histogram to select the histogram we want for ETA 


    /******************* RUNNING OVER THE TREE ***********************/

    // counters
    const Long64_t nentries = (maxentries <= 0) ? fChain->GetEntriesFast() : min(fChain->GetEntriesFast(),maxentries);
    unsigned int progress = 0;  // counter  to see the progress of the loop
    Long64_t nbytes = 0, nb = 0; // dunno the use of this... (given by TTree::MakeClass())

    
//    unsigned int ngentracksout = 0; // #tracks passing the cutoffs
    

    unsigned int NGAnd = 0,
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
                        histofill_RT_eta          = hist1D["RT_HFXor_eta"];
                    }
        
                    //HF_And selection, both sides of HF always.  
                    else if(CTmaxHFminus>CTcut && CTmaxHFplus>CTcut){
        
                        NRAnd++;   //Counter for normalization 
                        histofill_RT_eta          = hist1D["RT_HFAnd_eta"];
                    }
                }
                
                else {
                        NRNo++;
                        histofill_RT_eta          = hist1D["RT_NoHF_eta"];
                }

                

            for (unsigned int itrack = 0 ; itrack < RT.pt->size() ; itrack++)
            {

                if (       RT.pt ->at(itrack)  > minpt   
                    && abs(RT.eta->at(itrack)) < maxtracketa
                    && abs(RT.charge->at(itrack))==1) 
                {
                    nrectracks++; 
                    if(histofill_RT_eta != 0x0) histofill_RT_eta->Fill(RT.eta->at(itrack));
                }
            }

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
                    if((EmaxHFminus>Ecut && EmaxHFplus<Ecut) || (EmaxHFminus<Ecut && EmaxHFplus>Ecut)){
                        
                        NGXor++; //Counter for normalization 
                        histofill_GT_eta          = hist1D["GT_HFXor_eta"];
                    }
        
                    //HF_And selection, both sides of HF always.  
                    else if(EmaxHFminus>Ecut && EmaxHFplus>Ecut){
        
                        NGAnd++;   //Counter for normalization 
                        histofill_GT_eta   = hist1D["GT_HFAnd_eta"];
                    }
                }
                
                else {
                        NGNo++;
                        histofill_GT_eta   = hist1D["GT_NoHF_eta"];
                }
        
        
            for (unsigned int itrack = 0 ; itrack < GT.pt->size() ; itrack++)
            {

                if (       GT.pt ->at(itrack)  > minpt   
                    && abs(GT.eta->at(itrack)) < maxtracketa
                    && abs(GT.charge->at(itrack))==1) 
                {
                    ngentracks++; 
                    if(histofill_GT_eta != 0x0) histofill_GT_eta->Fill(GT.eta->at(itrack));
                }
            }
           
        }



           
    //********** Once per event *****************//
    }
    cout << "Loop: 100%!!" << endl;


    /*************** Adding And+Xor histograms to create Or histograms *****************************/

        //GT
        for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
        {
            TString name = TString::Format("GT_HFOr_%s", proto_tracks2[ikin]->GetName());
            hist1D[name]->Add   (hist1D[TString::Format("GT_HFAnd_%s",proto_tracks2[ikin]->GetName())]);   
            hist1D[name]->Add   (hist1D[TString::Format("GT_HFXor_%s",proto_tracks2[ikin]->GetName())]);   
        }

        
        //RT
        for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
        {
            TString name = TString::Format("RT_HFOr_%s", proto_tracks2[ikin]->GetName());
            hist1D[name]->Add   (hist1D[TString::Format("RT_HFAnd_%s",proto_tracks2[ikin]->GetName())]);   
            hist1D[name]->Add   (hist1D[TString::Format("RT_HFXor_%s",proto_tracks2[ikin]->GetName())]);   
        }

    
    /*************** NORMALIZATION OF HISTOGRAMS *****************************/
    //Normalizing to the number of selected events
    //NGAnd/Xor/Or = Number of HFAnd/Xor/Or events for GenParticles
    //NRAnd/Xor/Or = Number of HFAnd/Xor/Or events for RecTracks
   
    //Scaling factor for bin as deffined at the top of the file.


        //GT and RT in a single loop. Bin whith and # of selected events 
//        for (unsigned int ikin = 0 ; ikin < 1 ; ikin++) //Just for eta destribution.
//        {
//            TString name = TString::Format("GT_HFOr_%s", proto_tracks2[ikin]->GetName());
//            hist1D[name]->Scale(1.0/(binWhith*(NGAnd+NGXor)));   
//            name = TString::Format("RT_HFOr_%s", proto_tracks2[ikin]->GetName());
//            hist1D[name]->Scale(1.0/(binWhith*(NRAnd+NRXor)));   
//           
//            name = TString::Format("GT_HFAnd_%s", proto_tracks2[ikin]->GetName());
//            hist1D[name]->Scale(1.0/(binWhith*NGAnd));   
//            name = TString::Format("RT_HFAnd_%s", proto_tracks2[ikin]->GetName());
//            hist1D[name]->Scale(1.0/(binWhith*NRAnd));   
//            
//            name = TString::Format("GT_HFXor_%s", proto_tracks2[ikin]->GetName());
//            hist1D[name]->Scale(1.0/(binWhith*NGXor));   
//            name = TString::Format("RT_HFXor_%s", proto_tracks2[ikin]->GetName());
//            hist1D[name]->Scale(1.0/(binWhith*NRXor));   
//        }
    
        //GT and RT in a single loop. Bin whith  
        for (unsigned int ikin = 0 ; ikin < 1 ; ikin++) //Just for eta destribution.
        {
            TString name = TString::Format("GT_HFOr_%s", proto_tracks2[ikin]->GetName());
            hist1D[name]->Scale(1.0/(binWhith));   
            name = TString::Format("RT_HFOr_%s", proto_tracks2[ikin]->GetName());
            hist1D[name]->Scale(1.0/(binWhith));   
           
            name = TString::Format("GT_HFAnd_%s", proto_tracks2[ikin]->GetName());
            hist1D[name]->Scale(1.0/(binWhith));   
            name = TString::Format("RT_HFAnd_%s", proto_tracks2[ikin]->GetName());
            hist1D[name]->Scale(1.0/(binWhith));   
            
            name = TString::Format("GT_HFXor_%s", proto_tracks2[ikin]->GetName());
            hist1D[name]->Scale(1.0/(binWhith));   
            name = TString::Format("RT_HFXor_%s", proto_tracks2[ikin]->GetName());
            hist1D[name]->Scale(1.0/(binWhith));   
        }
 

    /*************** EFFICIENCIES AND RATIOS *****************************/


    if  (kContainsGenLevel)
    {
        cout << "Computing ratios" << endl;
        // ratio of generated tracks over reconstructed tracks
        for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
        {
            TString name = TString::Format("ratio_tracks_HFAnd_%s", proto_tracks2[ikin]->GetName());
            hist1D[name] = (TH1D *) proto_tracks2[ikin]->Clone(name);
            hist1D[name]->SetTitle(TString::Format("%s efficiency", proto_tracks2[ikin]->GetTitle()));
            hist1D[name]->SetYTitle("gen/reco");
            hist1D[name]->Add   (hist1D[TString::Format("GT_HFAnd_%s",proto_tracks2[ikin]->GetName())]);   // numerator   = RECO
            hist1D[name]->Divide(hist1D[TString::Format("RT_HFAnd_%s",proto_tracks2[ikin]->GetName())]);   // denominator = GEN 
        }
        for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
        {
            TString name = TString::Format("ratio_tracks_HFXor_%s", proto_tracks2[ikin]->GetName());
            hist1D[name] = (TH1D *) proto_tracks2[ikin]->Clone(name);
            hist1D[name]->SetTitle(TString::Format("%s efficiency", proto_tracks2[ikin]->GetTitle()));
            hist1D[name]->SetYTitle("gen/reco");
            hist1D[name]->Add   (hist1D[TString::Format("GT_HFXor_%s",proto_tracks2[ikin]->GetName())]);   // numerator   = RECO
            hist1D[name]->Divide(hist1D[TString::Format("RT_HFXor_%s",proto_tracks2[ikin]->GetName())]);   // denominator = GEN 
        }
        for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
        {
            TString name = TString::Format("ratio_tracks_HFOr_%s", proto_tracks2[ikin]->GetName());
            hist1D[name] = (TH1D *) proto_tracks2[ikin]->Clone(name);
            hist1D[name]->SetTitle(TString::Format("%s efficiency", proto_tracks2[ikin]->GetTitle()));
            hist1D[name]->SetYTitle("gen/reco");
            hist1D[name]->Add   (hist1D[TString::Format("GT_HFOr_%s",proto_tracks2[ikin]->GetName())]);   // numerator   = RECO
            hist1D[name]->Divide(hist1D[TString::Format("RT_HFOr_%s",proto_tracks2[ikin]->GetName())]);   // denominator = GEN 
        }


    }

    /************************* TERMINAL MESSAGES  *******************************/
   
        cout<<"------------------------------------------------------"<<endl;
        cout<<"Number of events   = "<<nentries<<" (100%)"<<endl;
        cout<<"------------------------------------------------------"<<endl;
        cout<<"Number of GenHFAnd = "<<NGAnd<<" ("<<100.0*NGAnd/nentries<<"%)"<<endl;
        cout<<"Number of GenHFXor = "<<NGXor<<" ("<<100.0*NGXor/nentries<<"%)"<<endl;
        cout<<"Number of GenHFOr  = "<<NGAnd+NGXor<<" ("<<100.0*(NGXor+NGAnd)/nentries<<"%)"<<endl;
        cout<<"Number of GenNoHF  = "<<NGNo<<" ("<<100.0*NGNo/nentries<<"%)"<<endl;
        cout<<"------------------------------------------------------"<<endl;
        cout<<"------------ Used to normalize data ------------------"<<endl;
        cout<<"Number of RecHFAnd = "<<NRAnd<<" ("<<100.0*NRAnd/nentries<<"%)"<<endl;
        cout<<"Number of RecHFXor = "<<NRXor<<" ("<<100.0*NRXor/nentries<<"%)"<<endl;
        cout<<"Number of RecHFOr  = "<<NRAnd+NRXor<<" ("<<100.0*(NRAnd+NRXor)/nentries<<"%)"<<endl;
        cout<<"Number of RecNoHF  = "<<NRNo<<" ("<<100.0*NRNo/nentries<<"%)"<<endl;
        cout<<"------------------------------------------------------"<<endl;
    
    
    /************************* SAVING *******************************/

    TString outputfilename = TString::Format("_" __FILE__ "_pt_gt_%.2f_eta_st_%.2f", minpt, maxtracketa); // 1) it should include the phase space
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
#undef WRITE
    f->Close();
    cout << "File closed." << endl;

    /*********************** PRINTING *************************/

    // NOT HERE
    // TODO: later in different file... (e.g. plotfast_*.C in the data directory)
}

#include "main.cc"
