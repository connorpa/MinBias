// -*- C++ -*-
//
// Package:    MinBias/BasicTrackAnalysis
// Class:      TreeProducer
// 
/**\class TreeProducer TreeProducer.cc MinBias/BasicTrackAnalysis/plugins/TreeProducer.cc

Description: create a tree describing the min bias tracks

Implementation:
1) originally, we would have liked to have a single branch with several leaf for each kind of object 
(e.g. one branch for the reconstructed tracks with leafs for the pt, eta, ...)
but it happens that the use of vectors of user-defined objects requires the use of dictionaries,
which is a big mess
SO we mimic the use of object in the name of the objects to postpone this step
BUT we still use objects before the filling of the ntuple
2) the objects are
- defined in struct.h, and are rather simple
- declared as members of the class TreeProducer (here...)
- linked to the tree in the beginJob() method
- cleared and filled at each call of the analyze() method
3) the input tags are initialised in the constructor,
with good control on the filling of the tree from the python file
(there should be no need to recompile this class to create other ntuples with possibly missing branches)
*/
//
// Original Author:  Patrick Connor
//         Created:  Fri, 08 May 2015 10:00:47 GMT
//
//


// system include files
#include <memory>
#include <vector>

/// user include files

// pre-included (by mkedanlzr command)
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
//#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

// TFileService
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

//#include "DataFormats/Candidate/interface/Candidate.h"
//#include "DataFormats/Candidate/interface/CandidateFwd.h"
// beam spot
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
// event id
#include "DataFormats/Luminosity/interface/LumiSummary.h"
#include "DataFormats/Luminosity/interface/LumiDetails.h"
#include "DataFormats/Provenance/interface/Timestamp.h"
//vertex
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
// track
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
// gen particles
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "SimGeneral/HepPDTRecord/interface/ParticleDataTable.h"
// rec hit
//#include "DataFormats/HcalDetId/interface/HcalDetId.h"
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
//#include "DataFormats/CaloRecHit/interface/CaloRecHit.h"
// calo tower
#include "DataFormats/CaloTowers/interface/CaloTower.h"
#include "DataFormats/CaloTowers/interface/CaloTowerFwd.h"
#include "DataFormats/CaloTowers/interface/CaloTowerDetId.h"


// ROOT
#include <TFile.h>
#include <TTree.h>

// personal types
#include "struct.h"

using namespace std;

//
// class declaration
//

class TreeProducer : public edm::EDAnalyzer {
public:
    explicit TreeProducer(const edm::ParameterSet&); // TODO: initialise collections
    ~TreeProducer();  // nothing TODO, apparently

    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions); // TODO: ??????


private:
    virtual void beginJob() override;
    virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
    virtual void endJob() override;

    //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
    //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
    //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
    //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

    // ----------member data ---------------------------
    edm::Service<TFileService> fs;
    TTree * tree;

    // CAUTION: the My* object (stored in struct.h) are not in one-to-one correspondance with the InputTags
    const bool StoreBeamSpot              ;    edm::InputTag BeamSpotInputTag              ;    MyBeamSpot      BS;
    const bool StoreLumiProducer          ;    edm::InputTag LumiProducerInputTag          ;    MyEvtId         EI;
    const bool StoreOfflinePrimaryVertices;    edm::InputTag OfflinePrimaryVerticesInputTag;    MyRecoVertices  RV;
    const bool StoreGeneralTracks         ;    edm::InputTag GeneralTracksInputTag         ;    MyRecoTracks    RT;
    const bool StoreHFRecHit              ;    edm::InputTag HFRecHitInputTag              ;    MyHFRecHit      RH;
    const bool StoreCaloTower             ;    edm::InputTag CaloTowerInputTag             ;    MyHFCaloTower   CT;
    const bool StoreGenParticles          ;    edm::InputTag GenParticlesInputTag          ;    MyGenVertices   GV;
                                                                                                MyGenTracks     GT;
    // TODO trigger?
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
TreeProducer::TreeProducer(const edm::ParameterSet& iConfig)
#define GETPARAM(Object) Store##Object (iConfig.getParameter<bool>("Store" #Object))
    :   GETPARAM(BeamSpot)
    ,   GETPARAM(LumiProducer)
    ,   GETPARAM(OfflinePrimaryVertices)
    ,   GETPARAM(GeneralTracks)
    ,   GETPARAM(HFRecHit) 
    ,   GETPARAM(CaloTower)      
    ,   GETPARAM(GenParticles)
#undef GETEPARAM
{
#define GETINPUTTAG(Object) if (Store##Object) Object##InputTag = iConfig.getParameter<edm::InputTag>(#Object)
    GETINPUTTAG(BeamSpot);
    GETINPUTTAG(LumiProducer);
    GETINPUTTAG(OfflinePrimaryVertices);
    GETINPUTTAG(GeneralTracks);
    GETINPUTTAG(HFRecHit);
    GETINPUTTAG(CaloTower);
    GETINPUTTAG(GenParticles);
#undef GETINPUTTAG
}


TreeProducer::~TreeProducer()
{
    delete tree;
    // do anything here that needs to be done at desctruction time
    // (e.g. close files, deallocate resources etc.)
}


//
// member functions
//

// ------------ method called for each event  ------------
void TreeProducer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    // EVENT ID

    // no Handle to define, this information is already in iEvent

	EI.Run       = iEvent.id().run();   
	EI.Evt       = iEvent.id().event();
	EI.LumiBlock = iEvent.luminosityBlock();
	EI.Time      = iEvent.time().value(); 
	EI.IsData    = iEvent.isRealData();
	EI.ExpType   = iEvent.experimentType();
	EI.Bunch     = iEvent.bunchCrossing();
	EI.Orbit     = iEvent.orbitNumber();
	if (StoreLumiProducer && iEvent.isRealData())
    {
		edm::Handle<LumiSummary> lumiSummary;
        iEvent.getLuminosityBlock().getByLabel(LumiProducerInputTag, lumiSummary);
		EI.IstLumi = (lumiSummary.product())->avgInsDelLumi();

		edm::Handle<LumiDetails> lumiDetail;
        iEvent.getLuminosityBlock().getByLabel(LumiProducerInputTag, lumiDetail );
		EI.IstLumiPerBX = lumiDetail->lumiValue(LumiDetails::kOCC1,iEvent.bunchCrossing());
		EI.IstLumiErr   = lumiDetail->lumiError(LumiDetails::kOCC1,iEvent.bunchCrossing());
	}

    // BEAM SPOT
    if (StoreBeamSpot)
    {
        edm::Handle<reco::BeamSpot> BShandle;
        iEvent.getByLabel(BeamSpotInputTag,BShandle);

        BS.positionX       = BShandle.product()->position().x();    
        BS.positionY       = BShandle.product()->position().y();    
        BS.positionZ       = BShandle.product()->position().z();    
        BS.x0Error         = BShandle.product()->x0Error();
        BS.y0Error         = BShandle.product()->y0Error();
        BS.z0Error         = BShandle.product()->z0Error();
        BS.sigmaZ          = BShandle.product()->sigmaZ();
        BS.dxdz            = BShandle.product()->dxdz();
        BS.dydz            = BShandle.product()->dydz();
        BS.sigmaZ0Error    = BShandle.product()->sigmaZ0Error();
        BS.dxdzError       = BShandle.product()->dxdzError();
        BS.dydzError       = BShandle.product()->dydzError();
        BS.BeamWidthX      = BShandle.product()->BeamWidthX();
        BS.BeamWidthY      = BShandle.product()->BeamWidthY();
        BS.BeamWidthXError = BShandle.product()->BeamWidthXError();
        BS.BeamWidthYError = BShandle.product()->BeamWidthYError();
    }

    // GENERATED PARTICLES
    // + SIMULATED VERTEX (TODO: check...)
    if (StoreGenParticles)
    {
        edm::Handle<reco::GenParticleCollection> genParticles;
        iEvent.getByLabel(GenParticlesInputTag, genParticles);

        GT.energy->clear();
        GT.pt    ->clear();
        GT.eta   ->clear();
        GT.phi   ->clear();
        GT.charge->clear();
        GV.x->clear();
        GV.y->clear();
        GV.z->clear();
        for (unsigned int itrack = 0 ; itrack < genParticles->size() ; itrack++)
        {
            if ((genParticles->at(itrack)).status() != 1) continue; // TODO: check
            GT.energy->push_back( (genParticles->at(itrack)).energy() );
            GT.pt    ->push_back( (genParticles->at(itrack)).pt()     ); 
            GT.eta   ->push_back( (genParticles->at(itrack)).eta()    );
            GT.phi   ->push_back( (genParticles->at(itrack)).phi()    );
            //TODO: pdgId, status
            GT.charge->push_back( (genParticles->at(itrack)).charge() );

            math::XYZPoint vertex = (genParticles->at(2)).vertex();
            if (GV.x->size() == 0 ||
                    (vertex.X() != GV.x->back() ||
                     vertex.Y() != GV.y->back() ||
                     vertex.Z() != GV.z->back()))
            {
                GV.x->push_back(vertex.X());
                GV.y->push_back(vertex.Y());
                GV.z->push_back(vertex.Z());
            }
        }
    }

    // RECONSTRUCTED VERTEX
    if (StoreOfflinePrimaryVertices)
    {
        edm::Handle<reco::VertexCollection> generalverticescollection; // typedef std::vector<Track> TrackCollection; 
        iEvent.getByLabel(OfflinePrimaryVerticesInputTag,generalverticescollection);

        RV.x       ->clear();
        RV.y       ->clear();
        RV.z       ->clear();
        RV.xError  ->clear();
        RV.yError  ->clear();
        RV.zError  ->clear();
        RV.chi2    ->clear();
        RV.ndof    ->clear();
        RV.isFake  ->clear();
        RV.isValid ->clear();
        for (unsigned int ivertex = 0 ; ivertex < generalverticescollection->size() ; ivertex++)
        {
            RV.x       ->push_back( (generalverticescollection->at(ivertex)).x()        );
            RV.y       ->push_back( (generalverticescollection->at(ivertex)).y()        );
            RV.z       ->push_back( (generalverticescollection->at(ivertex)).z()        );
            RV.xError  ->push_back( (generalverticescollection->at(ivertex)).xError()   );
            RV.yError  ->push_back( (generalverticescollection->at(ivertex)).yError()   );
            RV.zError  ->push_back( (generalverticescollection->at(ivertex)).zError()   );
            RV.chi2    ->push_back( (generalverticescollection->at(ivertex)).chi2()     );
            RV.ndof    ->push_back( (generalverticescollection->at(ivertex)).ndof()     );
            RV.isFake  ->push_back( (generalverticescollection->at(ivertex)).isFake()   );
            RV.isValid ->push_back( (generalverticescollection->at(ivertex)).isValid()  );
        }
    }

    // RECONSTRUCTED TRACKS
    if (StoreGeneralTracks)
    {
        edm::Handle<reco::TrackCollection> trackcollection; // typedef std::vector<Track> TrackCollection; 
        iEvent.getByLabel(GeneralTracksInputTag,trackcollection);

        //RT.energy  ->clear();
        RT.pt      ->clear();
        RT.eta     ->clear();
        RT.phi     ->clear();
        RT.ptError ->clear();
        RT.etaError->clear();
        RT.phiError->clear();
        RT.dxy     ->clear();
        RT.dxyError->clear();
        RT.dz      ->clear();
        RT.dzError ->clear();
        RT.charge  ->clear();
        for (unsigned int itrack = 0 ; itrack < trackcollection->size() ; itrack++)
        {
            //RT.energy  ->push_back( (trackcollection->at(itrack)). // TODO ???
            RT.pt      ->push_back( (trackcollection->at(itrack)).pt()       ); 
            RT.eta     ->push_back( (trackcollection->at(itrack)).eta()      );
            RT.phi     ->push_back( (trackcollection->at(itrack)).phi()      );
            RT.ptError ->push_back( (trackcollection->at(itrack)).ptError()  ); 
            RT.etaError->push_back( (trackcollection->at(itrack)).etaError() );
            RT.phiError->push_back( (trackcollection->at(itrack)).phiError() );
            RT.dxy     ->push_back( (trackcollection->at(itrack)).dxy()      );
            RT.dxyError->push_back( (trackcollection->at(itrack)).dxyError() );
            RT.dz      ->push_back( (trackcollection->at(itrack)).dz()       );
            RT.dzError ->push_back( (trackcollection->at(itrack)).dzError()  );
            RT.charge  ->push_back( (trackcollection->at(itrack)).charge()   );
        }
    }

    // REC HIT
    if (StoreHFRecHit)
    {
        edm::Handle<HFRecHitCollection> hfrechitcollection;
        iEvent.getByLabel(HFRecHitInputTag,hfrechitcollection);

        RH.energy->clear();
        for(HFRecHitCollection::const_iterator it_rechit = hfrechitcollection->begin(); it_rechit != hfrechitcollection->end(); it_rechit++)
        {
            RH.energy->push_back(it_rechit->energy());
        //    double signal = (hfrechitcollection->at(irechit)).energy(); // TODO
        //    if(signal < Erhmin) Erhmin = signal;

        //    hHFsignal->Fill(signal);
        //    if(IsSD) hHFsignal_SD->Fill(signal);
        //    if(!IsSD) hHFsignal_NSD->Fill(signal);

        //    for(int nsig = 0; nsig < NSIGMA; nsig++) {
        //        double threshold = (nsig+1); 
        //        //-- at least one hf digi above threshold
        //        if((signal > threshold) && data_type) IsHF[nsig] = true;
        }
    }

    // CALO TOWER
    if (StoreCaloTower)
    {
        edm::Handle<CaloTowerCollection> calotowercollection;
        iEvent.getByLabel(CaloTowerInputTag,calotowercollection);

        CT.energy   ->clear();
        CT.emEnergy ->clear();
        CT.hadEnergy->clear();
        CT.eta      ->clear();
        CT.phi      ->clear();
        //for (unsigned int ical = 0 ; ical < calotowercollection
        for (CaloTowerCollection::const_iterator it_calo = calotowercollection->begin() ; it_calo != calotowercollection->end() ; it_calo++)
        {
            // the calo tower must belong to the HF
            if (! CaloTowerDetId::validDetId (it_calo->eta(),it_calo->phi())) continue;

            CT.energy   ->push_back(it_calo->energy   ());
            CT.emEnergy ->push_back(it_calo->emEnergy ());
            CT.hadEnergy->push_back(it_calo->hadEnergy());
            CT.eta      ->push_back(it_calo->eta      ());
            CT.phi      ->push_back(it_calo->phi      ());
        }
    }

    tree->Fill();
}


// ------------ method called once each job just before starting event loop  ------------
void TreeProducer::beginJob()
{
    tree = fs->make<TTree>("MinBiasData", "MinBiasData");

    // EVENT ID
    if (StoreLumiProducer)
        tree->Branch("EvtId", &EI, "Run/i:Evt/i:LumiBlock/i:Time/l:IsData/O:ExpType/i:Bunch/I:Orbit/I:IstLumi/F:IstLumiErr/F:IstLumiPerBX/F");
    else
        tree->Branch("EvtId", &EI, "Run/i:Evt/i:LumiBlock/i:Time/l:IsData/O:ExpType/i:Bunch/I:Orbit/I");

    // BEAM SPOT
    if (StoreBeamSpot)
        tree->Branch("BeamSpot", &BS, "positionX/D:positionY/D:positionZ/D:x0Error/D:y0Error/D:z0Error/D:sigmaZ/D:dxdz/D:dydz/D:sigmaZ0Error/D:dxdzError/D:dydzError/D:BeamWidthX/D:BeamWidthY/D:BeamWidthXError/D:BeamWidthYError/D");

    if (StoreGenParticles)
    {
        // GENERATED PARTICLES  TODO: leafs
        tree->Branch("GenTracks.energy", &GT.energy); 
        tree->Branch("GenTracks.pt"    , &GT.pt    ); 
        tree->Branch("GenTracks.eta"   , &GT.eta   ); 
        tree->Branch("GenTracks.phi"   , &GT.phi   ); 
        tree->Branch("GenTracks.charge", &GT.charge); 
                             
        // SIMULATED VERTEX     TODO: leafs
        tree->Branch("GenVertices.x" , &GV.x); 
        tree->Branch("GenVertices.y" , &GV.y); 
        tree->Branch("GenVertices.z" , &GV.z); 
    }
                       
    // RECONSTRUCTED VERTEX TODO: leafs
    if (StoreOfflinePrimaryVertices)
    {
        tree->Branch("RecoVertices.x"       , &RV.x       ); 
        tree->Branch("RecoVertices.y"       , &RV.y       ); 
        tree->Branch("RecoVertices.z"       , &RV.z       ); 
        tree->Branch("RecoVertices.xError"  , &RV.xError  );
        tree->Branch("RecoVertices.yError"  , &RV.yError  );
        tree->Branch("RecoVertices.zError"  , &RV.zError  );
        tree->Branch("RecoVertices.chi2"    , &RV.chi2    );
        tree->Branch("RecoVertices.ndof"    , &RV.ndof    );
        tree->Branch("RecoVertices.isFake"  , &RV.isFake  );
        tree->Branch("RecoVertices.isValid" , &RV.isValid );
    }
                     
    // RECONSTRUCTED TRACKS TODO: leafs
    if (StoreGeneralTracks)
    {
        //tree->Branch("RecoTracks.energy"  , &RT.energy  ); 
        tree->Branch("RecoTracks.pt"      , &RT.pt      ); 
        tree->Branch("RecoTracks.eta"     , &RT.eta     ); 
        tree->Branch("RecoTracks.phi"     , &RT.phi     ); 
        tree->Branch("RecoTracks.ptError" , &RT.ptError ); 
        tree->Branch("RecoTracks.etaError", &RT.etaError); 
        tree->Branch("RecoTracks.phiError", &RT.phiError); 
        tree->Branch("RecoTracks.dxy"     , &RT.dxy     );
        tree->Branch("RecoTracks.dxyError", &RT.dxyError);
        tree->Branch("RecoTracks.dz"      , &RT.dz      );
        tree->Branch("RecoTracks.dzError" , &RT.dzError );
        tree->Branch("RecoTracks.charge"  , &RT.charge  ); 
    }

    // REC HIT TODO: leafs
    if (StoreHFRecHit)
        tree->Branch("HFRecHit.energy"    , &RH.energy);

    // CALO TOWER TODO: leafs
    if (StoreCaloTower)
    {
        tree->Branch("HFCaloTower.energy"   , &CT.energy   );
        tree->Branch("HFCaloTower.emEnergy" , &CT.emEnergy );
        tree->Branch("HFCaloTower.hadEnergy", &CT.hadEnergy);
        tree->Branch("HFCaloTower.eta"      , &CT.eta      );
        tree->Branch("HFCaloTower.phi"      , &CT.phi      );
    }
}

// ------------ method called once each job just after ending the event loop  ------------
void TreeProducer::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
/*
   void 
   TreeProducer::beginRun(edm::Run const&, edm::EventSetup const&)
   {
   }
   */

// ------------ method called when ending the processing of a run  ------------
/*
   void 
   TreeProducer::endRun(edm::Run const&, edm::EventSetup const&)
   {
   }
   */

// ------------ method called when starting to processes a luminosity block  ------------
/*
   void 
   TreeProducer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
   {
   }
   */

// ------------ method called when ending the processing of a luminosity block  ------------
/*
   void 
   TreeProducer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
   {
   }
   */

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void TreeProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
    //The following says we do not know what parameters are allowed so do no validation
    // Please change this to state exactly what you do use, even if it is no parameters
    edm::ParameterSetDescription desc;
    desc.setUnknown();
    descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TreeProducer);