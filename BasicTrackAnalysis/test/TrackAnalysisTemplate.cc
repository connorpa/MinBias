/**************************************************************************************/
/* Author: Patrick L.S. Connor (DESY CMS group)                                       */
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

    // TODO: define cutoffs here
    const double minpt  = 0.1, // GeV
                 maxtracketa = 2.4; // no unit
                 //minRHeta = 3,
                 //maxRHeta = 5;

    /************************* BOOKING HISTOGRAMS *****************************/

    cout << "Booking histograms..." << endl;

    // The first variables are template histograms, whose purpose is just to be copied to ensure compatible
    // dimensions and size between similar quantities
    // TODO: adapt proto histograms upon purpose
    // Remember: TH1D * h = new TH1D (name, title, nbins, xlow, xup);
    const unsigned short int NKIN = 4, // KINematics, plus multiplicity
                             NDIR = 3; // DIRections
    const TH1D * proto_tracks[NKIN] = { new const TH1D ("pt" , "transverse momentum;p_T/GeV;#entries",   50,     0,   5),
                                        new const TH1D ("eta", "pseudorapidity     ;#eta   ;#entries",   50,  -2.5,  2.5),
                                        new const TH1D ("phi", "azimuthal angle    ;#phi   ;#entries",   20,   -PI,   PI),
                                        new const TH1D ("M"  , "multiplicity       ;M      ;#enitres",  300,     0,  300)},
               * proto_vertices[NDIR]   = { new const TH1D ("x", "x-position;x/mm;#entries", 100,  0.2, 0.4),
                                            new const TH1D ("y", "y-position;x/mm;#entries", 100,  0.3, 0.5),
                                            new const TH1D ("z", "z-position;x/mm;#entries", 100,  -20, 20) };

    // The next variables are defined to take advantage of the maps
    // i.e. the map can be looped only over a small section of
    map<TString, TH1D *> hist1D; // i.e. map["string"] = histogram (use "iterators" to run over a map--see below)
    map<TString, TH2D *> hist2D; // or take advantage of the regular names given to histograms
    // reconstructed tracks (EXAMPLE!!) // TODO: modify if need be)
    for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
    {
        TString name = TString::Format("RT_%s", proto_tracks[ikin]->GetName());
        hist1D[name] = (TH1D *) proto_tracks[ikin]->Clone(name);
        hist1D[name]->SetTitle(TString::Format("%s of the reconstructed tracks", proto_tracks[ikin]->GetTitle()));
        hist1D[name]->SetXTitle(proto_tracks[ikin]->GetXaxis()->GetTitle());
        hist1D[name]->SetYTitle(proto_tracks[ikin]->GetYaxis()->GetTitle());
    }
    // the same at gen level
    if (kContainsGenLevel)
    {   // create histograms for gen level with the exact same structure
        // TODO: do similar for gen level if appropriate
    }

    /******************* RUNNING OVER THE TREE ***********************/

    // counters
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

        // TODO: insert proper event storage here
    }
    cout << "Loop: 100%!!" << endl;

    /*************** EFFICIENCIES AND RATIOS *****************************/

    // TODO: insert operations between the different filled histograms

    /************************* SAVING *******************************/

    // TODO: the filename is determined as function of the input files and the applied cutoffs
    // => if you create a new cutoff, do not forget to include it in the name
    TString outputfilename = TString::Format("_" __FILE__ "_pt_gt_%f_eta_st_%f", minpt, maxtracketa); // 1) it should include the phase space
    outputfilename.ReplaceAll(".", "_"); // 1bis) but replace . by _ in the given values of the phase space
    outputfilename = path_to_tree + outputfilename; // 2) it should specify the name of the input file
    outputfilename.ReplaceAll(".root", ""); // 2bis) but without the .root that would appear in the middle...
    outputfilename.ReplaceAll("bonsai", "plots"); // and replacing the initial keywork to identify the kind of object that are stored in the file
    outputfilename += ".root"; // 3) and add .root at the end of the filename
    
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
