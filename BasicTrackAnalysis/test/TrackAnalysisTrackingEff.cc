/**************************************************************************************/
/* Author: Patrick L.S. Connor & Juan M. Grados Luyando (DESY CMS group)                                       */
/* Date: May 2015                                                                     */
/* Purpose: read and extract histograms from the ntuples given by the TreeProducer.cc */
/* Note: this code was started from the TTree::MakeClass()                            */
/**************************************************************************************/
#define TrackAnalysis_cxx
#include "TrackAnalysis.h"
#include <cstdio>
#include <TH2.h>
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
                 CTcut = 5.0, //CaloTower energy cut [GeV]
                 vertex_max_z = 20, // cm
                 vertex_max_r = 0.2, // cm
                 max_relative_dxy = 3,
                 max_relative_dz  = 3;
    const unsigned short int NKIN        = 4, // KINematics, plus multiplicity
                             NLEVELS     = kContainsGenLevel ? 2 : 1,
                             NSELECTIONS = 4,
                             NTYPES      = kContainsGenLevel ? 2 : 1;

    /************************* BOOKING HISTOGRAMS *****************************/

    cout << "Booking histograms and counters..." << endl;

    // prototype histograms used as models
    //TH1D * h = new TH1D (name, title, nbins, xlow, xup);
    const TH1D * proto_tracks[NKIN] = {new const TH1D ("eta", "pseudorapidity;#eta;#entries",  50,  -2.4,  2.4),
                                       new const TH1D ("pt" , "transverse momentum;p_T/GeV;#entries",   50,     0,   5),
                                       new const TH1D ("M"  , "multiplicity;M;#enitres",       300,     0,  300),
                                       new const TH1D ("EtotHF", "Total HF energy;E_HF_tot/GeV;#entries",1000,0.,1000.)};
    map<TString, TH1D *> hist1D; // i.e. map["string"] = histogram (use "iterators" to run over a map--see below)

    // for each combination of the following values, a histogram will be created
    // -> later in the loop, the selection will deliver the name of the histogram(s) to be filled
    TString levels    [NLEVELS    ] /*= kGenLevel ? {"GT", "RT"} : {"RT"}*/,  // CAUTION
            selections[NSELECTIONS] = {"HFAnd", "HFXor", "HFOr", "NoHF"},     // DO NOT CHANGE THE ORDER ARBTRARILY!!
            types     [NTYPES     ] /*= {"tower", "4vector"}*/;               // TODO: find a more robust way
    // the levels depends on whether we tresat MC or data
    levels[0] = "RT"   ;   if (NLEVELS > 1) levels[1] = "GT"     ;
    types[0]  = "tower";   if (NTYPES  > 1) types[1]  = "4vector";

    // counters (for the different types of selection possible)
    map<TString, unsigned long> counters;
    for (unsigned short int ilevel = 0 ; ilevel < NLEVELS ; ilevel++)
        for (unsigned short int iselection = 0 ; iselection < NSELECTIONS ; iselection++)
            counters[levels[ilevel] + selections[iselection]] = 0;

    // given the prototype histograms, the levels, the selections, and the types, we now properly book the histograms
    // note the smart use of the loops :-)
    for (unsigned short int ikin = 0 ; ikin < NKIN ; ikin++)
    {
        for (unsigned short int ilevel = 0 ; ilevel < NLEVELS ; ilevel++)
        {
            for (unsigned short int iselection = 0 ; iselection < NSELECTIONS ; iselection++)
            {
                for (unsigned short int itype = 0 ; itype < NTYPES ; itype++)
                {
                    TString name = TString::Format("%s_%s_%s_%s", levels[ilevel].Data(), selections[iselection].Data(), types[itype].Data(), proto_tracks[ikin]->GetName());
                    cout << "Booking " << name << endl;
                    hist1D[name] = (TH1D *) proto_tracks[ikin]->Clone(name);
                    hist1D[name]->SetTitle(TString::Format("%s of the %s with %s (%s) selection", proto_tracks[ikin]->GetTitle(), levels[ilevel].Data(), selections[iselection].Data(), types[itype].Data()));
                    hist1D[name]->SetXTitle(proto_tracks[ikin]->GetXaxis()->GetTitle());
                    hist1D[name]->SetYTitle(proto_tracks[ikin]->GetYaxis()->GetTitle());
                }
            }
        }
    }

    /******************* RUNNING OVER THE TREE ***********************/

    // running counters
    const Long64_t nentries = (maxentries <= 0) ? fChain->GetEntriesFast() : min(fChain->GetEntriesFast(),maxentries);
    unsigned int progress = 0;  // counter  to see the progress of the loop
    Long64_t nbytes = 0, nb = 0; // dunno the use of this... (given by TTree::MakeClass())
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

        //*********************** RecoTracks loop ***************************//

        if(   fabs(RV.z->at(0))                           < vertex_max_z  // less than 20cm from nominal interaction point along Z
           && sqrt(pow(RV.x->at(0),2)+pow(RV.y->at(0),2)) < vertex_max_r  // less than 0.2cm from nominal beam line     
           && RV.isValid->at(0)                                         ) // TODO: check with Juan
        {
            //Maximum energy deposition value in HF sides per event    
            double CTmaxHFminus = 0.,
                   CTmaxHFplus  = 0.;

            //RT maximum CaloTower energy in HF+/- for following event selection
            for (unsigned int icalo = 0 ; icalo < CT.energy->size() ; icalo++)
            { 
                //HF plus
                if (   CT.eta->at(icalo) > minRHeta
                    && CT.eta->at(icalo) < maxRHeta)
                    CTmaxHFplus = max(CTmaxHFplus, CT.energy->at(icalo));
                //HF minus
                if (   CT.eta->at(icalo) < -minRHeta
                    && CT.eta->at(icalo) > -maxRHeta)
                    CTmaxHFminus = max(CTmaxHFminus, CT.energy->at(icalo));
            }

            //RT event **selection** (but filling RT and GT **levels**)
            //HF_Or selection, at least one side of HF

            unsigned short int irecselection = 3; // NoHF by default
            if(CTmaxHFminus>CTcut || CTmaxHFplus>CTcut) // Or
            {
                if((CTmaxHFminus>CTcut && CTmaxHFplus<CTcut) || (CTmaxHFminus<CTcut && CTmaxHFplus>CTcut)) // Xor
                    irecselection = 1;
                else if(CTmaxHFminus>CTcut && CTmaxHFplus>CTcut)  // And
                    irecselection = 0;
                // Or = And + Xor -> treated at the end of the Loop method
            }
            counters["RT" + selections[irecselection]]++;

            // filling of the rec histograms satisfying the selection
            for (unsigned short int itype = 0 ; itype < NTYPES ; itype++)
            {
                const TString rec_histo_to_fill = "RT_" + selections[irecselection] + "_" + types[itype] + "_";
                unsigned long int nrectracks = 0; // multiplicity
                double CTtotHF = 0.; // measure the deposit of energy at rec level in the HF region
                for (unsigned int itrack = 0 ; itrack < RT.pt->size() ; itrack++)
                {
                    // kinematics plus multiplicity
                    if (        RT.pt ->at(itrack)  > minpt   
                        && fabs(RT.eta->at(itrack)) < maxtracketa
                        && fabs(RT.charge->at(itrack)) == 1
                        && RT.dxy->at(itrack)/RT.dxyError->at(itrack) < max_relative_dz   // TODO: put cutoff values into the header of the method
                        && RT.dz ->at(itrack)/RT.dzError ->at(itrack) < max_relative_dxy) 
                    {
                        hist1D[rec_histo_to_fill + "pt" ]->Fill(RT.pt ->at(itrack));
                        hist1D[rec_histo_to_fill + "eta"]->Fill(RT.eta->at(itrack));
                        nrectracks++;
                    }
                }
                hist1D[rec_histo_to_fill + "M"]->Fill(nrectracks);
                // forward energy deposit
                for (unsigned int icalo = 0 ; icalo < CT.energy->size() ; icalo++)
                    if (   fabs(CT.eta->at(icalo)) > minRHeta
                        && fabs(CT.eta->at(icalo)) < maxRHeta)
                        CTtotHF += CT.energy->at(icalo);
                hist1D[rec_histo_to_fill + "EtotHF"]->Fill(CTtotHF);
            }
        }//End vertex quality "if"

        if (kContainsGenLevel)
        {
            double EmaxHFminus = 0.,
                   EmaxHFplus  = 0.;

            //GT maximum energy in HF+/- for following event selection
            for (unsigned int itrack = 0 ; itrack < GT.pt->size() ; itrack++)
            { 
                //Only final state particles will continue
                if(GT.status->at(itrack) != 1) continue; 

                //HF plus
                if (   GT.eta->at(itrack) > minRHeta
                    && GT.eta->at(itrack) < maxRHeta)
                    EmaxHFplus = max(EmaxHFplus, GT.energy->at(itrack));
                //HF minus
                if (   GT.eta->at(itrack) < -minRHeta
                    && GT.eta->at(itrack) > -maxRHeta)
                    EmaxHFminus = max(EmaxHFminus, GT.energy->at(itrack));
            }


            //GT event selection
            //HF_Or selection, at least one side of HF
            unsigned short int igenselection = 3; // NoHF by default
            if(EmaxHFminus>Ecut || EmaxHFplus>Ecut)
            {
                //Note that HF_Xor and HF_And are inside HF_Or since they are a subgroup
                //HF_Xor selection, only one side of HF
                if((EmaxHFminus>Ecut && EmaxHFplus<Ecut) || (EmaxHFminus<Ecut && EmaxHFplus>Ecut))
                    igenselection = 1;
                else if(EmaxHFminus>Ecut && EmaxHFplus>Ecut)
                    igenselection = 0;
            }
            counters["GT" + selections[igenselection]]++;

            // filling of the gen histograms satisfying the selection
            for (unsigned short int itype = 0 ; itype < NTYPES ; itype++)
            {
                const TString gen_histo_to_fill = "GT_" + selections[igenselection] + "_" + types[itype] + "_";
                unsigned long int ngentracks = 0; // multiplicity
                double EtotHF = 0.; // measure the deposit of energy at gen level in the HF region
                for (unsigned int itrack = 0 ; itrack < GT.pt->size() ; itrack++)
                {
                    //Only final state particles will continue
                    if(GT.status->at(itrack) != 1) continue; 

                    // kinematics plus multiplicity
                    if (        GT.pt ->at(itrack)  > minpt   
                        && fabs(GT.eta->at(itrack)) < maxtracketa
                        && fabs(GT.charge->at(itrack)) == 1) 
                    {
                        hist1D[gen_histo_to_fill + "pt" ]->Fill(GT.pt ->at(itrack));
                        hist1D[gen_histo_to_fill + "eta"]->Fill(GT.eta->at(itrack));
                        ngentracks++;
                    }
                    // forward energy deposit
                    if (   fabs(GT.eta->at(itrack)) > minRHeta
                        && fabs(GT.eta->at(itrack)) < maxRHeta)
                        EtotHF += GT.energy->at(itrack);
                }
                hist1D[gen_histo_to_fill + "M"     ]->Fill(ngentracks);
                hist1D[gen_histo_to_fill + "EtotHF"]->Fill(EtotHF    );
            }
        }
    }
    cout << "Loop: 100%!!" << endl;


    /*************** ADDING AND+XOR HISTOGRAMS TO CREATE OR HISTOGRAMS  AND NORMALISING*****************************/

    // here we are mainly normalising histograms
    // and moreover computing the or-histograms
    // recall that filling or-selection is equivalent to filling both in and- and xor-selection
    // => let's add the and-histograms and the xor-histograms to determine the or-histograms
    for (unsigned short int ikin = 0 ; ikin < NKIN ; ikin++)
    {
        const double scale_factor = 1./(proto_tracks[ikin]->GetBinWidth(1));
        for (unsigned short int ilevel = 0 ; ilevel < NLEVELS ; ilevel++)
        {
            for (unsigned short int iselection = 0 ; iselection < NSELECTIONS ; iselection++)
            {
                for (unsigned short int itype = 0 ; itype < NTYPES ; itype++)
                {
                    TString name = TString::Format("%s_%s_%s_%s", levels[ilevel].Data(), selections[iselection].Data(), types[itype].Data(), proto_tracks[ikin]->GetName());
                    if (iselection == 2) // i.e. for HFOr
                    {
                        // add HFAnd and HFXor
                        hist1D[name]->Add(hist1D[TString::Format("%s_%s_%s_%s", levels[ilevel].Data(), selections[0].Data(), types[itype].Data(), proto_tracks[ikin]->GetName())]);
                        hist1D[name]->Add(hist1D[TString::Format("%s_%s_%s_%s", levels[ilevel].Data(), selections[1].Data(), types[itype].Data(), proto_tracks[ikin]->GetName())]);
                        counters[levels[ilevel] + selections[2]] = counters[levels[ilevel] + selections[0]] + counters[levels[ilevel] + selections[1]];
                    }
                    cout << "Normalising " << name << endl;
                    hist1D[name]->Scale(scale_factor);
                }
            }
        }
    }


    /************************* TERMINAL MESSAGES  *******************************/

#define BREAKLINE "------------------------------------------------------"
    cout << BREAKLINE << endl
         << "Number of events\t=\t" << nentries << " (100%)" << endl;
    // give absolute values and percentages
    for (unsigned short int ilevel = 0 ; ilevel < NLEVELS ; ilevel++)
    {
        cout << BREAKLINE << endl;
        for (unsigned short int iselection = 0 ; iselection < NSELECTIONS ; iselection++)
            cout << "Number of " << levels[ilevel] << selections[iselection] << "\t=\t"
                 << counters[levels[ilevel] + selections[iselection]]
                 << "\t(" << 100.*((double)counters[levels[ilevel] + selections[iselection]])/((double)nentries) << " %)" << endl;
    }
    if (kContainsGenLevel)
    {
        cout << BREAKLINE << endl;
        // ratios rec/gen
        for (unsigned short int iselection = 0 ; iselection < NSELECTIONS ; iselection++)
            cout << "Ratio rec/gen of " << selections[iselection] << "\t=\t" << ((double)counters["RT" + selections[iselection]])/((double)counters["GT" + selections[iselection]]) << endl;
    }
    cout << BREAKLINE << endl
         << "Note: you can get those value from the histograms that have been created." << endl
         << BREAKLINE << endl;
#undef BREAKLINE

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
#undef WRITE
    f->Close();
    cout << "File closed." << endl;

    /*********************** PRINTING *************************/

    // NOT HERE
    // TODO: later in different file... (e.g. plotfast_*.C in the data directory)
}

#include "main.cc"
