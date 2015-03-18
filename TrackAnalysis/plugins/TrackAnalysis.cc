// -*- C++ -*-
//
// Package:    MinBias/TrackAnalysis
// Class:      TrackAnalysis
// 
/**\class TrackAnalysis TrackAnalysis.cc MinBias/TrackAnalysis/plugins/TrackAnalysis.cc

Description: [one line class summary]

Implementation:
[Notes on implementation]
*/
//
// Original Author:  Patrick Connor
//         Created:  Tue, 17 Mar 2015 08:21:40 GMT
//
//


// system include files
#include <memory>
#include <algorithm>
#include <vector>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"    // basics (...)
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h" // iConfig

// supplementary
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"

// TFileService 
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

// Root
#include "TTree.h"
#include "TH1D.h"
#include "TGraphErrors.h"
#include "TMath.h"
#include "TString.h"

//
// class declaration
//

using namespace std;

class TrackAnalysis : public edm::EDAnalyzer
{
public:
    explicit TrackAnalysis(const edm::ParameterSet&);
    ~TrackAnalysis();

    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


private:
    virtual void beginJob();
    virtual void analyze(const edm::Event&, const edm::EventSetup&);
    virtual void endJob();

    //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
    //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
    //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
    //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

    // ----------member data ---------------------------
    edm::InputTag generalTrack_label;

    // define histogram
    edm::Service<TFileService> fs;
    TTree * t_tracks;
    TH1D * h_pt,
         * h_eta,
         * h_phi,
         * h_n,
#define NB_MULT_BINS 15
#define MULT_BINS_SIZE 10
         * h_pt_n[NB_MULT_BINS];
    TGraphErrors * g_pt_n;

    int nTrack;
    vector<double> track_pt ,
                   track_eta,
                   track_phi;

};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
TrackAnalysis::TrackAnalysis(const edm::ParameterSet& iConfig)
    :   nTrack(0)
{
    //now do what ever initialization is needed

    generalTrack_label = iConfig.getParameter<edm::InputTag>("generalTrack_label"); // example of how to retrieve information form ph=ython configuration file


    // no pointer between <.>
    h_pt  = fs->make<TH1D>("h_pt ", "Track Pt "         , 100,        0   ,        10  );
    h_eta = fs->make<TH1D>("h_eta", "Track eta"         , 100,       -2.5 ,         2.5);
    h_phi = fs->make<TH1D>("h_phi", "Track phi"         , 100, TMath::Pi(), TMath::Pi());
    h_n   = fs->make<TH1D>("h_n  ", "Track multiplicity", 100,        0   ,       100  );
    for (unsigned int i = 0 ; i < NB_MULT_BINS ; i++)
        h_pt_n[i] = fs->make<TH1D>(TString::Format("h_pt_%d", i),
                                    "Track pt in multiplicity bins",
                                    100,//h_pt->GetNbinsX()
                                    0,  //h_pt->GetXaxis()->GetXmin(),
                                    10);//h_pt->GetXaxis()->GetXmax());

    t_tracks = new TTree("t_tracks", "Track Analysis");
    t_tracks->Branch("TracksN  ", &nTrack   );
    t_tracks->Branch("TracksPt ", &track_pt );
    t_tracks->Branch("TracksEta", &track_eta);
    t_tracks->Branch("TracksPhi", &track_phi);
}


TrackAnalysis::~TrackAnalysis()
{

    // do anything here that needs to be done at desctruction time
    // (e.g. close files, deallocate resources etc.)
}


//
// member functions
//

// ------------ method called for each event  ------------
void TrackAnalysis::analyze(const edm::Event& iEvent,      // contains event by event information
                            const edm::EventSetup& iSetup) // contains the overall the information, as nb of event, lumi, etc.
{
    using namespace edm;

    Handle<reco::TrackCollection> trackcollection;
    iEvent.getByLabel(generalTrack_label,trackcollection);

    double event_weight = 1.;
    track_pt.clear();
    track_eta.clear();
    track_phi.clear();
    for (reco::TrackCollection::const_iterator itrack = trackcollection->begin() ; itrack != trackcollection->end() ; itrack++)
    {
        double track_weight = 1.;
        h_pt ->Fill(itrack->pt() , track_weight*event_weight);
        h_eta->Fill(itrack->eta(), track_weight*event_weight);
        h_phi->Fill(itrack->phi(), track_weight*event_weight);

        track_pt .push_back(itrack->pt ());
        track_eta.push_back(itrack->eta());
        track_phi.push_back(itrack->phi());

        h_pt_n[(trackcollection->size()/MULT_BINS_SIZE < NB_MULT_BINS-1) ? trackcollection->size()/MULT_BINS_SIZE : NB_MULT_BINS-1]->Fill(itrack->pt(), track_weight*event_weight);
    }
    h_n->Fill(trackcollection->size(), event_weight);

    t_tracks->Fill();
}

// ------------ method called once each job just before starting event loop  ------------
void TrackAnalysis::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void TrackAnalysis::endJob() 
{
    Double_t mult_indices[NB_MULT_BINS],
             mult_sigma[NB_MULT_BINS],
             pt_mean[NB_MULT_BINS],
             pt_sigma[NB_MULT_BINS];
    for (unsigned int i = 0 ; i < NB_MULT_BINS-1 ; i++)
    {
        mult_indices[i] = (i+1)*10 - 5;
        mult_sigma[i] = sqrt(5.);
        pt_mean[i] = h_pt_n[i]->GetMean();
        pt_sigma[i] = h_pt_n[i]->GetRMS();

    }
    g_pt_n = fs->make<TGraphErrors>(NB_MULT_BINS, mult_indices, pt_mean, mult_sigma, pt_sigma);
    g_pt_n->SetTitle(";<n>;<pt>");
}

// ------------ method called when starting to processes a run  ------------
/*
   void TrackAnalysis::beginRun(edm::Run const&, edm::EventSetup const&)
   {
   }
   */

// ------------ method called when ending the processing of a run  ------------
/*
   void TrackAnalysis::endRun(edm::Run const&, edm::EventSetup const&)
   {
   }
   */

// ------------ method called when starting to processes a luminosity block  ------------
/*
   void TrackAnalysis::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
   {
   }
   */

// ------------ method called when ending the processing of a luminosity block  ------------
/*
   void TrackAnalysis::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
   {
   }
   */
// NOTE: a luminosity block is the lowest amount of integrated luminosity at CMS

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void TrackAnalysis::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
    //The following says we do not know what parameters are allowed so do no validation
    // Please change this to state exactly what you do use, even if it is no parameters
    edm::ParameterSetDescription desc;
    desc.setUnknown();
    descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TrackAnalysis);
