//-- system include files
#include <memory>
#include <string>
#include <iostream>
   
//-- user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/BeamSpot/interface/BeamSpot.h"

#include "./TrackAnalysisTree.h"

TrackAnalysisTree::TrackAnalysisTree(const edm::ParameterSet& iConfig) {
  
  //-- do what ever initialization is needed

  //-- Modules to execute 
  //StoreGenKine = iConfig.getParameter<bool>("StoreGenKine");
  StoreGenPart = iConfig.getParameter<bool>("StoreGenPart");
  //StoreGenJet = iConfig.getParameter<bool>("StoreGenJet");
  //StoreCastorDigi = iConfig.getParameter<bool>("StoreCastorDigi");
  //StoreCastorJet = iConfig.getParameter<bool>("StoreCastorJet");

  //-- define Collection
  genPartColl_       = iConfig.getParameter<edm::InputTag>("genParticles");
  vertexColl_        = iConfig.getParameter<edm::InputTag>("offlinePrimaryVertices");
  generalTracksColl_ = iConfig.getParameter<edm::InputTag>("generalTracks");
  //hepMCColl_ = iConfig.getParameter<edm::InputTag>("hepMCColl");

  //L1GT_TrigMenuLite_Prov_ = iConfig.getParameter<bool>("L1GT_TrigMenuLite_Prov");
  //L1GT_TrigMenuLite_ = iConfig.getParameter<edm::InputTag>("L1GT_TrigMenuLite");
  //L1GT_ObjectMap_ = iConfig.getParameter<edm::InputTag>("L1GT_ObjectMap");

  //CastorDigiColl_ = iConfig.getParameter<edm::InputTag>("CastorDigiColl");
  //CastorRecHitColl_ = iConfig.getParameter<edm::InputTag>("CastorRecHitColl");
  //CastorTower_ = iConfig.getParameter<edm::InputTag>("CastorTowerColl");
  //BasicJet_ = iConfig.getParameter<edm::InputTag>("BasicJet");
  //CastorJetID_ = iConfig.getParameter<edm::InputTag>("CastorJetID");
 
  //PFJetColl_ = iConfig.getParameter<edm::InputTag>("PFJetColl");
  //CaloJetColl_ = iConfig.getParameter<edm::InputTag>("CaloJetColl");
  //CaloJetId_ = iConfig.getParameter<edm::InputTag>("CaloJetId");
  //TrackJetColl_  = iConfig.getParameter<edm::InputTag>("TrackJetColl");

  //GenJetColl_  = iConfig.getParameter<edm::InputTag>("GenJetColl");
  //ChargedGenJetColl_  = iConfig.getParameter<edm::InputTag>("ChargedGenJetColl");

  ////-- needed to retrieve JEC
  //PFJetJEC_ = iConfig.getParameter<string>("PFJetJEC");
  //CaloJetJEC_ = iConfig.getParameter<string>("CaloJetJEC");
  //TrackJetJEC_ = iConfig.getParameter<string>("TrackJetJEC");

  ////-- needed to retrieve JEC uncertainty
  //PFJetJECunc_ = iConfig.getParameter<string>("PFJetJECunc");
  //CaloJetJECunc_ = iConfig.getParameter<string>("CaloJetJECunc");
  //TrackJetJECunc_ = iConfig.getParameter<string>("TrackJetJECunc");

  ////-- central jet selection
  //ParaSetTightPFJetID_ = iConfig.getParameter<edm::ParameterSet>("TightPFJetID_Parameters");
  //ParaSetLooseCaloJetID_ = iConfig.getParameter<edm::ParameterSet>("LooseCaloJetID_Parameters");
  //ParaSetTightCaloJetID_ = iConfig.getParameter<edm::ParameterSet>("TightCaloJetID_Parameters");
  //jetPtCut_ = iConfig.getParameter<double>("JetPtCut");
  //jetEtaCut_ = iConfig.getParameter<double>("JetEtaCut");

  //-- CaloTower Information
  //CaloTower_ = iConfig.getParameter<edm::InputTag>("CaloTowerColl");

  //-- HLT triggers requested by user
  //hlt_bits = iConfig.getParameter<vector<string> >("requested_hlt_bits"); // QUESTION

  //-- filter triggers requested by user
  //filter_bits = iConfig.getParameter<vector<string> >("requested_filter_bits");

  //-- needed to retrieve HLT triggers
  //isValidHLTConfig_ = false;

  //-- needed to read Filter results
  //FilterResults_ = iConfig.getParameter<edm::InputTag>("FilterResults");
}


TrackAnalysisTree::~TrackAnalysisTree() {
   //-- do anything here that needs to be done at destruction time  // nothing TODO, apparently
   //-- e.g. close files, deallocate resources etc.
}


//-- member functions

//-- method called once each job just before starting the event loop 
void TrackAnalysisTree::beginJob() {

  tree = fs->make<TTree>("TrackAnalysisTree","TrackAnalysisTree");

  //-- General Information
  tree->Branch("EvtId",&EvtId);
  //tree->Branch("L1Trig",&L1Trig);
  //tree->Branch("HLTrig",&HLTrig);

  //-- MC Information
  //if(StoreGenKine) tree->Branch("GenKin",&GenKin);
  if(StoreGenPart)
  {
      tree->Branch("GenPart"  ,&GenPart  ); // vector<MyGenPart>
      tree->Branch("simVertex",&simVertex); // MySimVector
  }
  tree->Branch("RecoTrack", &RecoTrack);    // vector<MyTrack>
  //if(StoreGenJet) tree->Branch("GenJet",&GenJet);
  //if(StoreGenJet) tree->Branch("ChargedGenJet",&ChargedGenJet);

  //-- Reco Vertex Information
  tree->Branch("beamSpot",&beamSpot);       // MyBeamSpot
  tree->Branch("primaryVertex",&primaryVertex);  // vector<MyVertex>

  //-- Castor Information
  //if(StoreCastorDigi) tree->Branch("castorDigi",&castorDigi);
  //if(StoreCastorJet) tree->Branch("castorRecHit",&castorRecHit);
  //tree->Branch("castorTower",&castorTower);
  //tree->Branch("castorJet",&castorJet);
 
  ////-- Central Jet Information 
  //tree->Branch("pfJet",&pfJet);
  //tree->Branch("caloJet",&caloJet);
  //tree->Branch("trackJet",&trackJet);

  //tree->Branch("pfDiJet",&pfDiJet);
  //tree->Branch("caloDiJet",&caloDiJet);

  //-- CaloTower Information
  //tree->Branch("caloTower",&caloTower);
}

//-- method called to for each event
void TrackAnalysisTree::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
   
  using namespace edm;

  if(StoreGenPart)  GetGenPart (iEvent); // includes simVertex getter
  GetBeamSpot  (iEvent);
  GetEvtId(iEvent);
  GetRecoVertex(iEvent);
  GetRecoTrack (iEvent);
  
  //-- General Information
  //GetL1Trig(iEvent,iSetup);
  //GetHLTrig(iEvent,iSetup);
  
  //-- MC Information
  //if(StoreGenKine) GetGenKin(iEvent);
  //if(StoreGenJet) GetGenJet(iEvent,GenJetColl_,GenJet);
  //if(StoreGenJet) GetGenJet(iEvent,ChargedGenJetColl_,ChargedGenJet);

  //-- Reco Vertex and Track Information
  //GetRecoVertex(iEvent,"offlinePrimaryVertices",primaryVertex);

  //-- Castor Information
  //if(StoreCastorDigi) GetCastorDigi(iEvent,iSetup,castorDigi);
  //GetCastorRecHit(iEvent,castorRecHit);
  //GetCastorTower(iEvent,castorTower);
  //if(StoreCastorJet) GetCastorJet(iEvent,castorJet);
  
  //-- Central Jet Information
  //GetRecoPFJet(iEvent,iSetup,pfJet);
  //GetCentralPFDiJet(pfJet,pfDiJet);
  //
  //GetRecoCaloJet(iEvent,iSetup,caloJet);
  //GetCentralCaloDiJet(caloJet,caloDiJet);

  //GetRecoTrackJet(iEvent,iSetup,trackJet);
  
  //-- CaloTower Information
  //GetCaloTower(iEvent,caloTower);
  
  //-- Filling of the tree
  //-- Add here some event selection if needed 
  tree->Fill();
}


//-- method called to for each run
//void TrackAnalysisTree::beginRun(edm::Run const & iRun, edm::EventSetup const& iSetup){
//  using namespace std;
//  using namespace edm;
//
//  bool changed = true;
//  isValidHLTConfig_ = hltConfig.init(iRun,iSetup,"HLT",changed); // QUESTION
//}



//-- method called once each job just after ending the event loop
void TrackAnalysisTree::endJob() {

}

//define this as a plug-in
DEFINE_FWK_MODULE(TrackAnalysisTree);
