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
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
//#include "Fireworks/Core/interface/FWBeamSpot.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"


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
    edm::InputTag beamSpot_label;
    edm::InputTag offlinePrimaryVertex_label;

    // define histogram
    edm::Service<TFileService> fs;
    TTree * t_track;
    TH1D * h_pt,
         * h_eta,
         * h_phi,
         * h_n,
#define NB_MULT_BINS 15
#define MULT_BINS_SIZE 10
         * h_pt_n[NB_MULT_BINS];
    TGraphErrors * g_pt_n;

    // TRACKS
    int TrackN;
    vector<bool> TrackQualityIsLoose,
                 TrackQualityIsTight,
                 TrackQualityIsHighPurity;
    vector<int> TrackCharge,
                TrackQuality;
    vector<double> TrackPt      ,
                   TrackEta     ,
                   TrackPhi     ,
                   TrackPtError ,
                   TrackEtaError,
                   TrackPhiError,
                   TrackChi2,
                   TrackNdof,
                   TrackNormChi2, // TODO
                   TrackVertexX,
                   TrackVertexY,
                   TrackVertexZ,
                   TrackDxy,
                   TrackDz ,
                   TrackSxy,
                   TrackSz;
    // VERTICES
    int VertexN;
    vector<double> VertexX,
                   VertexY,
                   VertexZ,
                   VertexXError,
                   VertexYError,
                   VertexZError,
                   VertexChi2,
                   VertexNdof,
                   VertexNormChi2;
    vector<int> VertexNTracks;
    vector<bool> VertexIsValid,
                 VertexIsFake;

    // BEAMSPOT
    vector<double> BeamSpotX,
                   BeamSpotY,
                   BeamSpotZ;
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
    :   TrackN(0),
        VertexN(0)
{
    //now do what ever initialization is needed

    // example of how to retrieve information form python configuration file
    generalTrack_label = iConfig.getParameter<edm::InputTag>("generalTrack_label");
    beamSpot_label     = iConfig.getParameter<edm::InputTag>("beamSpot_label"    );
    offlinePrimaryVertex_label = iConfig.getParameter<edm::InputTag>("offlinePrimaryVertex_label");



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

    t_track = new TTree("t_track", "Track Analysis");
    t_track->Branch("TrackN       ", &TrackN       );  // TODO: check 3rd argument
    t_track->Branch("TrackQualityIsLoose     ", &TrackQualityIsLoose     );
    t_track->Branch("TrackQualityIsTight     ", &TrackQualityIsTight     ); 
    t_track->Branch("TrackQualityIsHighPurity", &TrackQualityIsHighPurity);
    t_track->Branch("TrackPt      ", &TrackPt      );
    t_track->Branch("TrackEta     ", &TrackEta     );
    t_track->Branch("TrackPhi     ", &TrackPhi     );
    t_track->Branch("TrackPtError ", &TrackPtError );
    t_track->Branch("TrackEtaError", &TrackEtaError);
    t_track->Branch("TrackPhiError", &TrackPhiError);
    t_track->Branch("TrackCharge  ", &TrackCharge  );
    t_track->Branch("TrackQuality ", &TrackQuality );
    t_track->Branch("TrackChi2    ", &TrackChi2    );
    t_track->Branch("TrackVertexX ", &TrackVertexX );
    t_track->Branch("TrackVertexY ", &TrackVertexY );
    t_track->Branch("TrackVertexZ ", &TrackVertexZ );
    t_track->Branch("TrackDxy     ", &TrackDxy     );
    t_track->Branch("TrackDz      ", &TrackDz      );
    t_track->Branch("TrackSxy     ", &TrackSxy     );
    t_track->Branch("TrackSz      ", &TrackSz      );

    t_track->Branch("VertexN       ", &VertexN        );
    t_track->Branch("VertexX       ", &VertexX        );
    t_track->Branch("VertexY       ", &VertexY        );
    t_track->Branch("VertexZ       ", &VertexZ        );
    t_track->Branch("VertexXError  ", &VertexXError   );
    t_track->Branch("VertexYError  ", &VertexYError   );
    t_track->Branch("VertexZError  ", &VertexZError   );
    t_track->Branch("VertexChi2    ", &VertexChi2     );
    t_track->Branch("VertexNdof    ", &VertexNdof     );
    t_track->Branch("VertexNormChi2", &VertexNormChi2 );
    t_track->Branch("VertexNTracks ", &VertexNTracks  );
    t_track->Branch("VertexIsValid ", &VertexIsValid  );
    t_track->Branch("VertexIsFake  ", &VertexIsFake   );
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
    Handle<reco::TrackCollection > trackcollection ;
    Handle<reco::BeamSpot        > beamspot        ;
    Handle<reco::VertexCollection> vertexcollection;
    iEvent.getByLabel(generalTrack_label,         trackcollection );
    iEvent.getByLabel(beamSpot_label            , beamspot        );
    iEvent.getByLabel(offlinePrimaryVertex_label, vertexcollection);

    double event_weight = 1.;

    // TRACKS
    // clear
    TrackQualityIsLoose     .clear();
    TrackQualityIsTight     .clear();
    TrackQualityIsHighPurity.clear();
    TrackPt      .clear();
    TrackEta     .clear();
    TrackPhi     .clear();
    TrackPtError .clear();
    TrackEtaError.clear();
    TrackPhiError.clear();
    TrackCharge  .clear();
    TrackQuality .clear();
    TrackChi2    .clear();
    TrackNdof    .clear();
    TrackDxy     .clear();
    TrackDz      .clear();
    TrackVertexX .clear();
    TrackVertexY .clear();
    TrackVertexZ .clear();
    // filling
    TrackN = trackcollection->size();
    for (reco::TrackCollection::const_iterator itrack = trackcollection->begin() ; itrack != trackcollection->end() ; itrack++)
    {
        double track_weight = 1.;
        // filling fs TH1D for integrated kinematics
        h_pt ->Fill(itrack->pt() , track_weight*event_weight);
        h_eta->Fill(itrack->eta(), track_weight*event_weight);
        h_phi->Fill(itrack->phi(), track_weight*event_weight);

        // filling the vectors that will be filled into the TTree
        TrackQualityIsLoose     .push_back(itrack->quality(reco::TrackBase::qualityByName("loose"     )));
        TrackQualityIsTight     .push_back(itrack->quality(reco::TrackBase::qualityByName("tight"     )));
        TrackQualityIsHighPurity.push_back(itrack->quality(reco::TrackBase::qualityByName("highPurity")));
        TrackPt      .push_back(itrack->pt      ());
        TrackEta     .push_back(itrack->eta     ());
        TrackPhi     .push_back(itrack->phi     ());
        TrackPtError .push_back(itrack->ptError ());
        TrackEtaError.push_back(itrack->etaError());
        TrackPhiError.push_back(itrack->phiError());
        TrackCharge  .push_back(itrack->charge  ());
        TrackChi2    .push_back(itrack->chi2    ());
        TrackNdof    .push_back(itrack->ndof    ());
        TrackVertexX .push_back(itrack->vx      ());
        TrackVertexY .push_back(itrack->vy      ());
        TrackVertexZ .push_back(itrack->vz      ());
        TrackDxy     .push_back(itrack->dxy     ()); // TODO: beam spot / vertex correction
        TrackDz      .push_back(itrack->dz      ()); // TODO: beam spot / vertex correction
        TrackSxy     .push_back(itrack->dxyError());
        TrackSz      .push_back(itrack->dzError ());
        // pt distribution in multiplicity bins
        h_pt_n[(trackcollection->size()/MULT_BINS_SIZE < NB_MULT_BINS-1) ? trackcollection->size()/MULT_BINS_SIZE : NB_MULT_BINS-1]->Fill(itrack->pt(), track_weight*event_weight);
    }
    // filling fs TH1D for multiplicity
    h_n->Fill(trackcollection->size(), event_weight);

    // VERTICES
    // clear
    VertexX       .clear();
    VertexY       .clear();
    VertexZ       .clear();
    VertexXError  .clear();
    VertexYError  .clear();
    VertexZError  .clear();
    VertexChi2    .clear();
    VertexNdof    .clear();
    VertexNormChi2.clear();
    VertexNTracks .clear();
    VertexIsValid .clear();
    VertexIsFake  .clear();
    // filling
    VertexN = vertexcollection->size();
    for (reco::VertexCollection::const_iterator ivertex = vertexcollection->begin() ; ivertex != vertexcollection->end() ; ivertex++)
    {
        VertexX       .push_back(ivertex->x             ());
        VertexY       .push_back(ivertex->y             ());
        VertexZ       .push_back(ivertex->z             ());
        VertexXError  .push_back(ivertex->xError        ());
        VertexYError  .push_back(ivertex->yError        ());
        VertexZError  .push_back(ivertex->zError        ());
        VertexChi2    .push_back(ivertex->chi2          ());
        VertexNdof    .push_back(ivertex->ndof          ());
        VertexNormChi2.push_back(ivertex->normalizedChi2());
        VertexNTracks .push_back(ivertex->nTracks       ());
        VertexIsValid .push_back(ivertex->isValid       ());
        VertexIsFake  .push_back(ivertex->isFake        ());
    }

    // fill the TTree
    t_track->Fill();
}

// ------------ method called once each job just before starting event loop  ------------
void TrackAnalysis::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void TrackAnalysis::endJob() 
{
    // produce the graph for <n> vs. <pt>
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
