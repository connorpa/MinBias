/**************************************************************************************/
/* Author: Patrick L.S. Connor (DESY CMS group)                                       */
/* Date: May 2015                                                                     */
/* Purpose: read and extract histograms from the ntuples given by the TreeProducer.cc */
/* Note: this code was started from the TTree::MakeClass()                            */
/**************************************************************************************/
#define TrackAnalysis_cxx
#include "TrackAnalysis.h"
#include <algorithm>
#include <TH2.h>
#include <TProfile.h>
#include <TMath.h>

#define PI TMath::Pi()

void TrackAnalysis::Loop(Long64_t maxentries)
{
    if (fChain == 0x0) return;

    if (!kContainsGenLevel)
    {
        cout << "This analyser is only intended for MC samples. Abort." << endl;
        return;
    }

    cout << "This analyser is intended to understand the meaning of the value of the reconstructed pt while reconstructing at 0T." << endl;  // TODO: complete description

    /********************** CUTOFFS & CONSTANTS ***************************/

    // TODO: define cutoffs here
    const double minpt  = 0.0, // GeV
                 maxtracketa = 2.4, // no unit
                 maxdR = 0.1,  // no unit
                 maxvz = 20, // cm
                 maxvxy = 0.2; // cm

    /************************* BOOKING HISTOGRAMS *****************************/

    cout << "Booking histograms..." << endl;
    // The first variables are template histograms, whose purpose is just to be copied to ensure compatible
    // dimensions and size between similar quantities
    // TODO: adapt proto histograms upon purpose
    // Remember: TH1D * h = new TH1D (name, title, nbins, xlow, xup);
    const unsigned short int NKIN = 2; // KINematics, plus multiplicity
    const TH1D * proto_tracks[NKIN] = { new const TH1D ("pt" , "transverse momentum;p_T/GeV;#entries",   50,     0,   5 ),
                                        new const TH1D ("eta", "pseudorapidity;#eta;#entries"        ,   50,  -2.5,  2.5)};
    //                                    new const TH1D ("phi", "azimuthal angle;#phi;#entries"       ,   20,   -PI,   PI),
    //                                    new const TH1D ("M"  , "multiplicity;M;#entries"             ,  300,     0,  300)};
    //           * proto_vertices[NDIR]   = { new const TH1D ("x", "x-position;x/mm;#entries", 100,  0.2, 0.4),
    //                                        new const TH1D ("y", "y-position;x/mm;#entries", 100,  0.3, 0.5),
    //                                        new const TH1D ("z", "z-position;x/mm;#entries", 100,  -20, 20) };
    const TH1D * proto_dr = new const TH1D ("dR" , "angular separation;dR;#nentries", 200, 0, 1);

    // The next variables are defined to take advantage of the maps
    // i.e. the map can be looped only over a small section of
    map<TString, TH1D *> hist1D; // i.e. map["string"] = histogram (use "iterators" to run over a map--see below)
    map<TString, TH2D *> hist2D; // or take advantage of the regular names given to histograms
    // reconstructed tracks (EXAMPLE!!) // TODO: modify if need be)
    const unsigned short int NSELECTIONS = 2;
    const TString selections[NSELECTIONS] = {"RS", "GS"}; // for reco-selection and gen-selection (because in both case, we will fill with gen pt
    for (unsigned short int iselection = 0 ; iselection < NSELECTIONS ; iselection++)
    {
        for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
        {
            TString name = TString::Format("%s_%s", selections[iselection].Data(), proto_tracks[ikin]->GetName());
            hist1D[name] = (TH1D *) proto_tracks[ikin]->Clone(name);
            hist1D[name]->SetTitle(TString::Format("%s of the %s", proto_tracks[ikin]->GetTitle(), selections[iselection].Data()));
            hist1D[name]->SetXTitle(proto_tracks[ikin]->GetXaxis()->GetTitle());
            hist1D[name]->SetYTitle(proto_tracks[ikin]->GetYaxis()->GetTitle());
        }
    }
    // additional histograms
    hist1D["corr_dr_smallest_dR"] = (TH1D *) proto_dr->Clone("corr_dr_smallest_dR");
    hist1D["corr_dr_smallest_dR"]->SetTitle("angular separation of only gen-rec couple of closest #DeltaR per event;dR;#tracks");

    hist2D["corr_pt_eta"] = new TH2D ("corr_pt_eta", "understand the reco eta from the gen pt;gen pt;reco eta",
                                    proto_tracks[0]->GetNbinsX(), proto_tracks[0]->GetXaxis()->GetXmin(), proto_tracks[0]->GetXaxis()->GetXmax(),
                                    proto_tracks[1]->GetNbinsX(), proto_tracks[1]->GetXaxis()->GetXmin(), proto_tracks[1]->GetXaxis()->GetXmax());
    hist2D["corr_eta_eta"] = new TH2D ("corr_eta_eta", "understand the meaning of the values of the reco eta;generated value;reconstructed value",
                                         proto_tracks[1]->GetNbinsX(), proto_tracks[1]->GetXaxis()->GetXmin(), proto_tracks[1]->GetXaxis()->GetXmax(),
                                         proto_tracks[1]->GetNbinsX(), proto_tracks[1]->GetXaxis()->GetXmin(), proto_tracks[1]->GetXaxis()->GetXmax());
    hist2D["corr_pt_pt"] = new TH2D ("corr_pt_pt", "understand the meaning of the values of the reco pt;generated value;reconstructed value",
                                       proto_tracks[0]->GetNbinsX(), proto_tracks[0]->GetXaxis()->GetXmin(), proto_tracks[0]->GetXaxis()->GetXmax(),
                                       proto_tracks[0]->GetNbinsX(), proto_tracks[0]->GetXaxis()->GetXmin(), proto_tracks[0]->GetXaxis()->GetXmax());
#define DEFINE2DHIST(XNAME, YNAME, TITLE) \
    hist2D[XNAME "_VS_" YNAME] = new TH2D (XNAME "_VS_" YNAME, TITLE, \
            hist1D[XNAME]->GetNbinsX(), hist1D[XNAME]->GetXaxis()->GetXmin(), hist1D[XNAME]->GetXaxis()->GetXmax(), \
            hist1D[YNAME]->GetNbinsX(), hist1D[YNAME]->GetXaxis()->GetXmin(), hist1D[YNAME]->GetXaxis()->GetXmax())
    DEFINE2DHIST("RS_pt", "RS_eta" , "reco-selected gen p_t VS reco-selected gen #eta;p_t/GeV;#eta;#entries");
    DEFINE2DHIST("GS_pt", "GS_eta" , "gen-selected gen p_t VS gen-selected gen #eta;p_t/GeV;#eta;#entries");
#undef DEFINE2DHIST
    hist2D["eff_pt_eta"] = new TH2D ("eff_pt_eta", "eff(gen #eta, gen p_t);gen pt;gen #eta",
                                    proto_tracks[0]->GetNbinsX(), proto_tracks[0]->GetXaxis()->GetXmin(), proto_tracks[0]->GetXaxis()->GetXmax(),
                                    proto_tracks[1]->GetNbinsX(), proto_tracks[1]->GetXaxis()->GetXmin(), proto_tracks[1]->GetXaxis()->GetXmax());

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

        // draw dR
        vector<unsigned int> irec_to_reject; // reject the reco tracks that have already been associated to a gen track
        for (unsigned int igen = 0 ; igen < GT.pt->size() ; igen++)
        {
            if (        GT.status->at(igen)  != 1
                ||      GT.pt    ->at(igen)  <  minpt
                || fabs(GT.eta   ->at(igen)) >  maxtracketa
                ||      GT.charge->at(igen)  == 0           )
                continue;

            // TODO: implement selection of proton, kaon and pion only (pdgId)

            unsigned int irec_smallest_dR = 0, // keep the index of the smallest-dR reco track to the current gen track
                         recmultiplicity = 0; // counts whether any event has passed the selection
            bool flag_dR = false; // used to fill the RS histo according to dR criterion
            for (unsigned int irec = 0 ; irec < VRT.pt->size() ; irec++)
            {
                // consider only the primary vertex
                if (VRT.ivertex->at(irec) > 0) // TODO: fix this cutoff
                    continue;
                // vertex cutoff (vertices outside this region would populate only the central region of the dn/deta) --> TODO: check
                if(    RV.z->at(0) > maxvz
                   || sqrt(pow(RV.x->at(0),2)+pow(RV.y->at(0),2)) > maxvxy)
                    continue;
                // kinematical cutoffs
                if (        VRT.pt ->at(irec)  < minpt
                    || fabs(VRT.eta->at(irec)) > maxtracketa)
                    continue;

                // do not consider already-associated particles
                if (find(irec_to_reject.begin(), irec_to_reject.end(), irec) != irec_to_reject.end())
                    continue;

                // look for smallest dR
                const double dR_igen_irec             = sqrt( pow( GT.eta->at(igen) - VRT.eta->at(irec            ) ,2) + pow( GT.phi->at(igen) - VRT.phi->at(irec            ) ,2) ),
                             dR_igen_irec_smallest_dR = sqrt( pow( GT.eta->at(igen) - VRT.eta->at(irec_smallest_dR) ,2) + pow( GT.phi->at(igen) - VRT.phi->at(irec_smallest_dR) ,2) );
                if (dR_igen_irec < dR_igen_irec_smallest_dR)
                {
                    irec_smallest_dR = irec;
                }

            // filling and incrementing multiplicity
                recmultiplicity++;
                if (dR_igen_irec  < maxdR)  
                {
                    flag_dR = true;
                }
            }
            hist1D["GS_pt" ]->Fill(GT.pt ->at(igen));
            hist1D["GS_eta"]->Fill(GT.eta->at(igen));
            hist2D["GS_pt_VS_GS_eta"]->Fill(GT.pt->at(igen), GT.eta->at(igen));
            if (recmultiplicity > 0)
            {
                hist1D["corr_dr_smallest_dR"]->Fill( sqrt( pow( GT.eta->at(igen) - VRT.eta->at(irec_smallest_dR) ,2) + pow( GT.phi->at(igen) - VRT.phi->at(irec_smallest_dR) ,2) ) );
                if (flag_dR) // i.e. if any track has passed the cut AND if one of them is close enough in term of dR
                {
                    hist1D["RS_pt"] ->Fill(GT.pt ->at(igen));
                    hist1D["RS_eta"]->Fill(GT.eta->at(igen));
                    hist2D["RS_pt_VS_RS_eta"]->Fill(GT.pt->at(igen), GT.eta->at(igen));
                    hist2D["corr_pt_pt"  ]->Fill(GT.pt ->at(igen), VRT.pt ->at(irec_smallest_dR));
                    hist2D["corr_pt_eta" ]->Fill(GT.pt ->at(igen), VRT.eta->at(irec_smallest_dR));
                    hist2D["corr_eta_eta"]->Fill(GT.eta->at(igen), VRT.eta->at(irec_smallest_dR));
                    irec_to_reject.push_back(irec_smallest_dR);
                }
            }
        }
    }
    cout << "Loop: 100%!!" << endl;

    /*************** EFFICIENCIES AND RATIOS *****************************/

    cout << "Computing ratios" << endl;
    // ratio of generated tracks over reconstructed tracks
    for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
    {
        TString name = TString::Format("eff_%s", proto_tracks[ikin]->GetName());
        hist1D[name] = (TH1D *) proto_tracks[ikin]->Clone(name);
        hist1D[name]->SetTitle(TString::Format("%s efficiency", proto_tracks[ikin]->GetTitle()));
        hist1D[name]->SetYTitle("efficiency");
        hist1D[name]->Add   (hist1D[TString::Format("RS_%s",proto_tracks[ikin]->GetName())]);   // numerator   = RECO
        hist1D[name]->Divide(hist1D[TString::Format("GS_%s",proto_tracks[ikin]->GetName())]);   // denominator = GEN 
    }
    hist2D["eff_pt_eta"] = (TH2D *) hist2D["RS_pt_VS_RS_eta"]->Clone("eff_pt_eta");
    hist2D["eff_pt_eta"]->SetTitle("2D efficiency");
    hist2D["eff_pt_eta"]->Divide(hist2D["GS_pt_VS_GS_eta"]);

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
