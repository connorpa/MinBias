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
    if (fChain == 0x0) return;

    /********************** CUTOFFS & CONSTANTS ***************************/

    const double minpt  = 0.1, // GeV
                 maxtracketa = 2.4; // no unit
                 //minRHeta = 3,
                 //maxRHeta = 5;
    const unsigned short int NETABIN = 4, // 4 eta bins of width 0.6 
                             NKIN = 4, // KINematics, plus multiplicity
                             NDIR = 3; // DIRections
    const double ETABINWIDTH = maxtracketa/((double) NETABIN);
    TString outputfilename = TString::Format("pt_gt_%f_eta_st_%f", minpt, maxtracketa); // it should include the phase space
    outputfilename.ReplaceAll(".", "_"); // replace . by _ in the given values of the phase space
    outputfilename = path_to_tree + outputfilename; // it should specify the name of the input file
    outputfilename.ReplaceAll(".root", ""); // but without the .root that would appear in the middle...
    outputfilename += ".root"; // and add .root at the end of the filename

    /************************* BOOKING HISTOGRAMS *****************************/

    cout << "Booking histograms..." << endl;

    // those variables are defined to take advantage of the maps
    // i.e. the map can be looped only over a small section of
    // we define constant proto histograms, whose purpose is only to be cloned, to ensure to have always the same structure
    //TH1D * h = new TH1D (name, title, nbins, xlow, xup);
    const TH1D * proto_tracks[NKIN] = { new const TH1D ("pt" , "transverse momentum;p_T/GeV;#entries",   50,     0,   5),
                                        new const TH1D ("eta", "pseudorapidity     ;#eta   ;#entries",   50,  -2.5,  2.5),
                                        new const TH1D ("phi", "azimuthal angle    ;#phi   ;#entries",   20,   -PI,   PI),
                                        new const TH1D ("M"  , "multiplicity       ;M      ;#enitres",  300,     0,  300)},
               * proto_vertices[NDIR]   = { new const TH1D ("x", "x-position;x/mm;#entries", 100,  0.2, 0.4),
                                            new const TH1D ("y", "y-position;x/mm;#entries", 100,  0.3, 0.5),
                                            new const TH1D ("z", "z-position;x/mm;#entries", 100,  -20, 20) };

    map<TString, TH1D *> hist1D; // i.e. map["string"] = histogram (use "iterators" to run over a map--see below)
    map<TString, TH2D *> hist2D;
    // reconstructed vertices
    for (unsigned int idir = 0 ; idir < NDIR ; idir++)
    {
        TString name = TString::Format("RV_%s", proto_vertices[idir]->GetName());
        hist1D[name] = (TH1D *) proto_vertices[idir]->Clone(name);
        hist1D[name]->SetTitle(TString::Format("%s of the reconstructed vertices", proto_vertices[idir]->GetTitle()));
        hist1D[name]->SetXTitle(proto_vertices[idir]->GetXaxis()->GetTitle());
        hist1D[name]->SetYTitle(proto_vertices[idir]->GetYaxis()->GetTitle());
    }
    // reconstructed tracks
    for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
    {
        TString name = TString::Format("RT_%s", proto_tracks[ikin]->GetName());
        hist1D[name] = (TH1D *) proto_tracks[ikin]->Clone(name);
        hist1D[name]->SetTitle(TString::Format("%s of the reconstructed tracks", proto_tracks[ikin]->GetTitle()));
        hist1D[name]->SetXTitle(proto_tracks[ikin]->GetXaxis()->GetTitle());
        hist1D[name]->SetYTitle(proto_tracks[ikin]->GetYaxis()->GetTitle());
    }
    // p_t in eta bin
    for (unsigned int ieta = 0 ; ieta < NETABIN ; ieta++)
    {
        TString name = TString::Format("RT_pt_%d", ieta);
        hist1D[name] = (TH1D *) proto_tracks[0]->Clone(name); // 0 = pt
        hist1D[name]->SetTitle(TString::Format("transverse momentum of the reconstructed tracks in %f < |#eta| < %f", ieta*ETABINWIDTH, (ieta+1)*ETABINWIDTH));
        hist1D[name]->SetXTitle(proto_tracks[0]->GetXaxis()->GetTitle());
        hist1D[name]->SetYTitle(proto_tracks[0]->GetYaxis()->GetTitle());
    }
    // the same at gen level
    if (kContainsGenLevel)
    {   // create histograms for gen level with the exact same structure

        // generated vertices
        for (unsigned int idir = 0 ; idir < NDIR ; idir++)
        {
            TString name = TString::Format("GV_%s", proto_vertices[idir]->GetName());
            hist1D[name] = (TH1D *) proto_vertices[idir]->Clone(name);
            hist1D[name]->SetTitle(TString::Format("%s of the generated vertices", proto_vertices[idir]->GetTitle()));
            hist1D[name]->SetXTitle(proto_vertices[idir]->GetXaxis()->GetTitle());
            hist1D[name]->SetYTitle(proto_vertices[idir]->GetYaxis()->GetTitle());
        }
        // generated tracks (charged particles might be a more appropriate term)
        for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
        {
            TString name = TString::Format("GT_%s", proto_tracks[ikin]->GetName());
            hist1D[name] = (TH1D *) proto_tracks[ikin]->Clone(name);
            hist1D[name]->SetTitle(TString::Format("%s of the generated tracks", proto_tracks[ikin]->GetTitle()));
            hist1D[name]->SetXTitle(proto_tracks[ikin]->GetXaxis()->GetTitle());
            hist1D[name]->SetYTitle(proto_tracks[ikin]->GetYaxis()->GetTitle());
        }
        for (unsigned int ieta = 0 ; ieta < NETABIN ; ieta++)
        {
            TString name = TString::Format("GT_pt_%d", ieta);
            hist1D[name] = (TH1D *) proto_tracks[0]->Clone(name); // 0 = pt
            hist1D[name]->SetTitle(TString::Format("transverse momentum of the reconstructed tracks in %f < |#eta| < %f", ieta*ETABINWIDTH, (ieta+1)*ETABINWIDTH));
            hist1D[name]->SetXTitle(proto_tracks[0]->GetXaxis()->GetTitle());
            hist1D[name]->SetYTitle(proto_tracks[0]->GetYaxis()->GetTitle());
        }
    }
    // energy deposit in the forward calorimeter
    //hist1D["rechit_energy"] = new TH1D ("rechit_energy", "rechit energy deposit;E/GeV;#entries", 100, 0, 100);

    // this macro is used to define 2d histogram using the 1d histogram corresponding to the axes
//#define DEFINE2DHIST(XNAME, YNAME, TITLE) \
//    hist2D[XNAME "_VS_" YNAME] = new TH2D (XNAME "_VS_" YNAME, TITLE, \
//                                            hist1D[XNAME]->GetNbinsX(), hist1D[XNAME]->GetXaxis()->GetXmin(), hist1D[XNAME]->GetXaxis()->GetXmax(), \
//                                            hist1D[YNAME]->GetNbinsX(), hist1D[YNAME]->GetXaxis()->GetXmin(), hist1D[YNAME]->GetXaxis()->GetXmax())
//    DEFINE2DHIST("forward_energy", "GT_M" , "forward energy deposit VS generated multiplicity       ;E/GeV;M      ;#entries");
//    DEFINE2DHIST("forward_energy", "GT_pt", "forward energy deposit VS generated transverse momentum;E/GeV;p_T/GeV;#entries");
//    DEFINE2DHIST("rechit_energy", "RT_M" , "rechit energy deposit VS reconstructed multiplicity       ;E/GeV;M      ;#entries");
//    DEFINE2DHIST("rechit_energy", "RT_pt", "rechit energy deposit VS reconstructed transverse momentum;E/GeV;p_T/GeV;#entries");
//#undef DEFINE2DHIST

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

        if (kContainsGenLevel)
        {
            // test GV
            for (unsigned int ivertex = 0 ; ivertex < GV.x->size() ; ivertex++)
            {
                // basic plots
                hist1D["GV_x"]->Fill(GV.x->at(ivertex));
                hist1D["GV_y"]->Fill(GV.y->at(ivertex));
                hist1D["GV_z"]->Fill(GV.z->at(ivertex));
            }

            // test GT
            unsigned int ngentracks = 0; // #tracks passing the cutoffs
            //double genRHenergy = 0.,
            //       leading_GT_pt = 0.;
            for (unsigned int itrack = 0 ; itrack < GT.pt->size() ; itrack++)
            {
                // basic plots
                if (       GT.pt ->at(itrack)  > minpt   
                    && abs(GT.eta->at(itrack)) < maxtracketa) 
                {
                    hist1D["GT_pt" ]->Fill(GT.pt ->at(itrack));
                    hist1D["GT_eta"]->Fill(GT.eta->at(itrack));
                    hist1D["GT_phi"]->Fill(GT.phi->at(itrack));
                    ngentracks++;
                    //// rechit vs leading pt
                    //leading_GT_pt = max(leading_GT_pt, GT.pt->at(itrack));
                    // pt in eta bins
                    hist1D[TString::Format("GT_pt_%d", (int) abs(GT.eta->at(itrack)/ETABINWIDTH))]->Fill(GT.pt->at(itrack)); 
                }
                //if (   fabs(RT.eta->at(itrack)) > minRHeta
                //    && fabs(RT.eta->at(itrack)) < maxRHeta)
                //    genRHenergy += RT.energy->at(itrack);
            }
            hist1D["GT_M"]->Fill(ngentracks);
            //// mimic rechit
            //hist2D["forward_energy_VS_GT_M"]->Fill(genRHenergy, ngentracks);
            //hist2D["forward_energy_VS_leading_GT_pt"]->Fill(genRHenergy, leading_GT_pt);
        }

        // test RV
        for (unsigned int ivertex = 0 ; ivertex < RV.x->size() ; ivertex++)
        {
            // basic plots
            hist1D["RV_x"]->Fill(RV.x->at(ivertex));
            hist1D["RV_y"]->Fill(RV.y->at(ivertex));
            hist1D["RV_z"]->Fill(RV.z->at(ivertex));
        }

        // test RT
        unsigned int nrectracks = 0; // #tracks passing the cutoffs
        //double leading_RT_pt = 0.,
        //       recHFenergy = 0.; // total energy deposit in the forward calorimeter
        for (unsigned int itrack = 0 ; itrack < RT.pt->size() ; itrack++)
        {
            // basic plots
            if (        RT.pt ->at(itrack)  > minpt      
                && fabs(RT.eta->at(itrack)) < maxtracketa)
            {
                hist1D["RT_pt" ]->Fill(RT.pt ->at(itrack));
                hist1D["RT_eta"]->Fill(RT.eta->at(itrack));
                hist1D["RT_phi"]->Fill(RT.phi->at(itrack));
                nrectracks++;
                //// rechit vs leading pt
                //leading_RT_pt = max(leading_RT_pt, RT.pt->at(itrack));
                // pt in eta bins
                hist1D[TString::Format("RT_pt_%d", (int) abs(RT.eta->at(itrack)/ETABINWIDTH))]->Fill(RT.pt->at(itrack)); 
            }
        }
        hist1D["RT_M"]->Fill(nrectracks);
        //for (unsigned short int irechit = 0 ; irechit < RH.energy->size() ; irechit++)
        //    recHFenergy += RH.energy->at(irechit) ;
        //hist2D["rechit_energy_VS_RT_M"]->Fill(recHFenergy, nrectracks);
        //hist2D["rechit_energy_VS_leading_RT_pt"]->Fill(recHFenergy, leading_RT_pt);
    }
    cout << "Loop: 100%!!" << endl;

    /*************** EFFICIENCIES AND RATIOS *****************************/

    if  (kContainsGenLevel)
    {
        cout << "Computing ratios" << endl;
        // ratio of generated tracks over reconstructed tracks
        for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
        {
            TString name = TString::Format("ratio_tracks_%s", proto_tracks[ikin]->GetName());
            hist1D[name] = (TH1D *) proto_tracks[ikin]->Clone(name);
            hist1D[name]->SetTitle(TString::Format("%s efficiency", proto_tracks[ikin]->GetTitle()));
            hist1D[name]->SetYTitle("gen/reco");
            hist1D[name]->Add   (hist1D[TString::Format("RT_%s",proto_tracks[ikin]->GetName())]);   // numerator   = RECO
            hist1D[name]->Divide(hist1D[TString::Format("GT_%s",proto_tracks[ikin]->GetName())]);   // denominator = GEN 
        }
        // same in the particular case of pt in eta bins
        for (unsigned int ieta = 0 ; ieta < NETABIN ; ieta++)
        {
            TString name = TString::Format("ratio_tracks_pt_%d", ieta);
            hist1D[name] = (TH1D *) proto_tracks[0]->Clone(name); // 0 = pt
            hist1D[name]->SetTitle(TString::Format("transverse momentum of the reconstructed tracks in %f < |#eta| < %f", ieta*ETABINWIDTH, (ieta+1)*ETABINWIDTH));
            hist1D[name]->SetYTitle("gen/reco");
            hist1D[name]->Add   (hist1D[TString::Format("RT_pt_%d",ieta)]);   // numerator   = RECO
            hist1D[name]->Divide(hist1D[TString::Format("GT_pt_%d",ieta)]);   // denominator = GEN 
        }
    }

    /************************* SAVING *******************************/

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

    /* PRINTING */

    // TODO: later in different file... (see plotfast.C in the data directory)
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
int main (int argc, char * argv[])
{
    TApplication * rootapp = new TApplication ("controlplots", &argc, argv);
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