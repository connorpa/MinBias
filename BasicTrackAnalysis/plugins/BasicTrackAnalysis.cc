// -*- C++ -*-
//
// Package:    MinBias/BasicTrackAnalysis
// Class:      BasicTrackAnalysis
// 
/**\class BasicTrackAnalysis BasicTrackAnalysis.cc MinBias/BasicTrackAnalysis/plugins/BasicTrackAnalysis.cc

Description: create a tree describing the min bias tracks

Implementation:
[Notes on implementation]
*/
//
// Original Author:  Patrick Connor
//         Created:  Fri, 08 May 2015 10:00:47 GMT
//
//


// system include files
#include <memory>
//#include <vector>

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

//#include "DataFormats/Common/interface/Handle.h"
//#include "DataFormats/Candidate/interface/Candidate.h"
//#include "DataFormats/Candidate/interface/CandidateFwd.h"
// beam spot
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
// event id
#include "DataFormats/Luminosity/interface/LumiSummary.h"
#include "DataFormats/Luminosity/interface/LumiDetails.h"
#include "DataFormats/Provenance/interface/Timestamp.h"
//vertex
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
// track
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"

// ROOT
#include <TFile.h>
#include <TTree.h>

using namespace std;

//
// class declaration
//

class BasicTrackAnalysis : public edm::EDAnalyzer {
public:
    explicit BasicTrackAnalysis(const edm::ParameterSet&); // TODO: initialise collections
    ~BasicTrackAnalysis();  // nothing TODO, apparently

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
    edm::InputTag //genPartInputTag,
                  generalTracksInputTag,
                  generalVerticesInputTag;
    edm::Service<TFileService> fs;
    TTree* tree;

    // the names of the methods have been respected (modulo the case)

#include "struct.h"

    MyBeamSpot BS;
    MyEvtId EI;
    // unfortunately, using struct with arrays is not that easy...
    // so temporarily (?), we are not using struct for vertices and tracks

    // GENERATED PARTICLES
    
    // SIMULATED VERTEX

    // RECONSTRUCTED VERTEX
#define RecoVertices_maxsize 516
    UInt_t RecoVertices_size;
    Double_t RecoVertices_x         [RecoVertices_maxsize];
    Double_t RecoVertices_y         [RecoVertices_maxsize];
    Double_t RecoVertices_z         [RecoVertices_maxsize];
    Double_t RecoVertices_xError    [RecoVertices_maxsize];
    Double_t RecoVertices_yError    [RecoVertices_maxsize];
    Double_t RecoVertices_zError    [RecoVertices_maxsize];
    Double_t RecoVertices_chi2      [RecoVertices_maxsize];
    Double_t RecoVertices_ndof      [RecoVertices_maxsize];
    Bool_t   RecoVertices_isFake    [RecoVertices_maxsize];
    Bool_t   RecoVertices_isValid   [RecoVertices_maxsize];

    // RECONSTRUCTED TRACKS
#define RecoTracks_maxsize 516
    UInt_t RecoTracks_size;
    Double_t RecoTracks_px    [RecoTracks_maxsize];
    Double_t RecoTracks_py    [RecoTracks_maxsize];
    Double_t RecoTracks_pz    [RecoTracks_maxsize];
    Int_t    RecoTracks_charge[RecoTracks_maxsize];

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
BasicTrackAnalysis::BasicTrackAnalysis(const edm::ParameterSet& iConfig)
    :   generalTracksInputTag    (iConfig.getParameter<edm::InputTag>("generalTracks")         )
    ,   generalVerticesInputTag  (iConfig.getParameter<edm::InputTag>("offlinePrimaryVertices"))
{
    //now do what ever initialization is needed
    //cout << __FILE__ << ":" << __LINE__ << ":" << __func__ << endl;

}


BasicTrackAnalysis::~BasicTrackAnalysis()
{
    //cout << __FILE__ << ":" << __LINE__ << ":" << __func__ << endl;
    // do anything here that needs to be done at desctruction time
    // (e.g. close files, deallocate resources etc.)
}


//
// member functions
//

// ------------ method called for each event  ------------
void BasicTrackAnalysis::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    //cout << __FILE__ << ":" << __LINE__ << ":" << __func__ << endl;

    // BEAM SPOT

    edm::Handle<reco::BeamSpot> BShandle;
    iEvent.getByLabel("offlineBeamSpot",BShandle);  // TODO: connect to python config file

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

    // EVENT ID

	EI.Run       = iEvent.id().run();   
	EI.Evt       = iEvent.id().event();
	EI.LumiBlock = iEvent.luminosityBlock();
	EI.Time      = iEvent.time().value(); 
	EI.IsData    = iEvent.isRealData();
	EI.ExpType   = iEvent.experimentType();
	EI.Bunch     = iEvent.bunchCrossing();
	EI.Orbit     = iEvent.orbitNumber();
	if (iEvent.isRealData())
    {   // TODO: do not hard code "lumiProducer", use python file instead...
		edm::Handle<LumiSummary> lumiSummary;
        iEvent.getLuminosityBlock().getByLabel("lumiProducer", lumiSummary);
		EI.IstLumi = (lumiSummary.product())->avgInsDelLumi();

		edm::Handle<LumiDetails> lumiDetail;
        iEvent.getLuminosityBlock().getByLabel("lumiProducer", lumiDetail );
		EI.IstLumiPerBX = lumiDetail->lumiValue(LumiDetails::kOCC1,iEvent.bunchCrossing());
		EI.IstLumiErr   = lumiDetail->lumiError(LumiDetails::kOCC1,iEvent.bunchCrossing());
	}

    // GENERATED PARTICLES
    
    // SIMULATED VERTEX

    // RECONSTRUCTED VERTEX

    edm::Handle<reco::VertexCollection> vertexcollection; // typedef std::vector<Track> TrackCollection; 
    iEvent.getByLabel(generalVerticesInputTag,vertexcollection);
    RecoVertices_size = vertexcollection->size() ;   // UInt_t
    if (RecoVertices_size > RecoVertices_maxsize)
    {
        cout << "WARNING: RecoVertices_size = " << RecoVertices_size << endl;
        RecoVertices_size = RecoVertices_maxsize;
    }

    for (unsigned int ivertex = 0 ; ivertex < vertexcollection->size() ; ivertex++)
    {
        RecoVertices_x       [ivertex] = (vertexcollection->at(ivertex)).x(); 
        RecoVertices_y       [ivertex] = (vertexcollection->at(ivertex)).y();
        RecoVertices_z       [ivertex] = (vertexcollection->at(ivertex)).z();
        RecoVertices_xError  [ivertex] = (vertexcollection->at(ivertex)).xError();
        RecoVertices_yError  [ivertex] = (vertexcollection->at(ivertex)).yError();
        RecoVertices_zError  [ivertex] = (vertexcollection->at(ivertex)).zError();
        RecoVertices_chi2    [ivertex] = (vertexcollection->at(ivertex)).chi2();
        RecoVertices_ndof    [ivertex] = (vertexcollection->at(ivertex)).ndof();
        RecoVertices_isFake  [ivertex] = (vertexcollection->at(ivertex)).isFake();
        RecoVertices_isValid [ivertex] = (vertexcollection->at(ivertex)).isValid();
     //myvertex.ex        = pv->xError();
     //myvertex.ey        = pv->yError();
     //myvertex.ez        = pv->zError();

     //myvertex.validity  = pv->isValid();
     //myvertex.fake      = pv->isFake();

     // if(!myvertex.fake) myvertex.chi2n = pv->normalizedChi2();
     // else myvertex.chi2n = -99.;
    
     // if(!myvertex.fake) myvertex.ndof = pv->ndof();
     // else myvertex.ndof = -99.;
    }

    // RECONSTRUCTED TRACKS

    edm::Handle<reco::TrackCollection> trackcollection; // typedef std::vector<Track> TrackCollection; 
    iEvent.getByLabel(generalTracksInputTag,trackcollection);
    RecoTracks_size = trackcollection->size() ;   // UInt_t
    if (RecoTracks_size > RecoTracks_maxsize)
    {
        cout << "WARNING: RecoTracks_size = " << RecoTracks_size << endl;
        RecoTracks_size = RecoTracks_maxsize;
    }
    //RT.size = RecoTracks_size;

    //for(reco::TrackCollection::const_iterator p = trackcollection->begin(); p != trackcollection->end(); ++ p)
    for (unsigned int itrack = 0 ; itrack < trackcollection->size() ; itrack++)
    {
        RecoTracks_px    [itrack] = (trackcollection->at(itrack)).px(); 
        RecoTracks_py    [itrack] = (trackcollection->at(itrack)).py();
        RecoTracks_pz    [itrack] = (trackcollection->at(itrack)).pz();
        RecoTracks_charge[itrack] = (trackcollection->at(itrack)).charge();
        //RT.px    [itrack] = (trackcollection->at(itrack)).px(); 
        //RT.py    [itrack] = (trackcollection->at(itrack)).py();
        //RT.pz    [itrack] = (trackcollection->at(itrack)).pz();
        //RT.charge[itrack] = (trackcollection->at(itrack)).charge();
        //RT.px    .push_back( (trackcollection->at(itrack)).px()     ); 
        //RT.py    .push_back( (trackcollection->at(itrack)).py()     );
        //RT.pz    .push_back( (trackcollection->at(itrack)).pz()     );
        //RT.charge.push_back( (trackcollection->at(itrack)).charge() );
    }

    tree->Fill();
}


// ------------ method called once each job just before starting event loop  ------------
void BasicTrackAnalysis::beginJob()
{
    //cout << __FILE__ << ":" << __LINE__ << ":" << __func__ << endl;
    tree = fs->make<TTree>("MinBiasData", "MinBiasData");

    // BEAM SPOT

    tree->Branch("BeamSpot", &BS, "positionX/D:positionY/D:positionZ/D:x0Error/D:y0Error/D:z0Error/D:sigmaZ/D:dxdz/D:dydz/D:sigmaZ0Error/D:dxdzError/D:dydzError/D:BeamWidthX/D:BeamWidthY/D:BeamWidthXError/D:BeamWidthYError/D");
    //cout << __FILE__ << ":" << __LINE__ << ":" << __func__ << endl;
    
    //tree->Branch("BS_positionX"      ,&BS_positionX      ,"BS_positionX/D"      );
    //tree->Branch("BS_positionY"      ,&BS_positionY      ,"BS_positionY/D"      );
    //tree->Branch("BS_positionZ"      ,&BS_positionZ      ,"BS_positionZ/D"      );
    //tree->Branch("BS_x0Error"        ,&BS_x0Error        ,"BS_x0Error/D"        );
    //tree->Branch("BS_y0Error"        ,&BS_y0Error        ,"BS_y0Error/D"        );
    //tree->Branch("BS_z0Error"        ,&BS_z0Error        ,"BS_z0Error/D"        );
    //tree->Branch("BS_sigmaZ"         ,&BS_sigmaZ         ,"BS_sigmaZ/D"         );
    //tree->Branch("BS_dxdz"           ,&BS_dxdz           ,"BS_dxdz/D"           );
    //tree->Branch("BS_dydz"           ,&BS_dydz           ,"BS_dydz/D"           );
    //tree->Branch("BS_sigmaZ0Error"   ,&BS_sigmaZ0Error   ,"BS_sigmaZ0Error/D"   );
    //tree->Branch("BS_dxdzError"      ,&BS_dxdzError      ,"BS_dxdzError/D"      );
    //tree->Branch("BS_dydzError"      ,&BS_dydzError      ,"BS_dydzError/D"      );
    //tree->Branch("BS_BeamWidthX"     ,&BS_BeamWidthX     ,"BS_BeamWidthX/D"     );
    //tree->Branch("BS_BeamWidthY"     ,&BS_BeamWidthY     ,"BS_BeamWidthY/D"     );
    //tree->Branch("BS_BeamWidthXError",&BS_BeamWidthXError,"BS_BeamWidthXError/D");
    //tree->Branch("BS_BeamWidthYError",&BS_BeamWidthYError,"BS_BeamWidthYError/D");

    // EVENT ID             TODO
                           
    tree->Branch("EvtId", &EI, "EvtId_Run/i:EvtId_Evt/i:EvtId_LumiBlock/i:EvtId_Time/l:EvtId_IsData/O:EvtId_ExpType/i:EvtId_Bunch/I:EvtId_Orbit/I:EvtId_IstLumi/F:EvtId_IstLumiErr/F:EvtId_IstLumiPerBX/F");
    //tree->Branch("EvtId_Run"         ,&EvtId_Run         ,"EvtId_Run/i"         );
    //tree->Branch("EvtId_Evt"         ,&EvtId_Evt         ,"EvtId_Evt/i"         );
    //tree->Branch("EvtId_LumiBlock"   ,&EvtId_LumiBlock   ,"EvtId_LumiBlock/i"   );
    //tree->Branch("EvtId_Time"        ,&EvtId_Time        ,"EvtId_Time/i"        );
    //tree->Branch("EvtId_IsData"      ,&EvtId_IsData      ,"EvtId_IsData/O"      );
    //tree->Branch("EvtId_ExpType"     ,&EvtId_ExpType     ,"EvtId_ExpType/i"     );
    //tree->Branch("EvtId_Bunch"       ,&EvtId_Bunch       ,"EvtId_Bunch/I"       );
    //tree->Branch("EvtId_Orbit"       ,&EvtId_Orbit       ,"EvtId_Orbit/I"       );
    //tree->Branch("EvtId_IstLumi"     ,&EvtId_IstLumi     ,"EvtId_IstLumi/F"     );
    //tree->Branch("EvtId_IstLumiErr"  ,&EvtId_IstLumiErr  ,"EvtId_IstLumiErr/F"  );
    //tree->Branch("EvtId_IstLumiPerBX",&EvtId_IstLumiPerBX,"EvtId_IstLumiPerBX/F");

    // GENERATED PARTICLES  TODO
                         
    // SIMULATED VERTEX     TODO
                       
    // RECONSTRUCTED VERTEX TODO
    tree->Branch("RecoVertices_size"   , &RecoVertices_size   , "RecoVertices_size/i"                     ); 
    tree->Branch("RecoVertices_x"      ,  RecoVertices_x      , "RecoVertices_x[RecoVertices_size]/D"     ); 
    tree->Branch("RecoVertices_y"      ,  RecoVertices_y      , "RecoVertices_y[RecoVertices_size]/D"     ); 
    tree->Branch("RecoVertices_z"      ,  RecoVertices_z      , "RecoVertices_z[RecoVertices_size]/D"     ); 
    tree->Branch("RecoVertices_xError" ,  RecoVertices_xError , "RecoVertices_xError[RecoVertices_size]/D" );
    tree->Branch("RecoVertices_yError" ,  RecoVertices_yError , "RecoVertices_yError[RecoVertices_size]/D" );
    tree->Branch("RecoVertices_zError" ,  RecoVertices_zError , "RecoVertices_zError[RecoVertices_size]/D" );
    tree->Branch("RecoVertices_chi2"   ,  RecoVertices_chi2   , "RecoVertices_chi2[RecoVertices_size]/D"   );
    tree->Branch("RecoVertices_ndof"   ,  RecoVertices_ndof   , "RecoVertices_ndof[RecoVertices_size]/D"   );
    tree->Branch("RecoVertices_isFake" ,  RecoVertices_isFake , "RecoVertices_isFake[RecoVertices_size]/O" );
    tree->Branch("RecoVertices_isValid",  RecoVertices_isValid, "RecoVertices_isValid[RecoVertices_size]/O");
                     
    // RECONSTRUCTED TRACKS TODO

    tree->Branch("RecoTracks_size"  , &RecoTracks_size   , "RecoTracks_size/i"                   ); 
    tree->Branch("RecoTracks_px"    ,  RecoTracks_px     , "RecoTracks_px[RecoTracks_size]/D"    ); 
    tree->Branch("RecoTracks_py"    ,  RecoTracks_py     , "RecoTracks_py[RecoTracks_size]/D"    ); 
    tree->Branch("RecoTracks_pz"    ,  RecoTracks_pz     , "RecoTracks_pz[RecoTracks_size]/D"    ); 
    tree->Branch("RecoTracks_charge",  RecoTracks_charge , "RecoTracks_charge[RecoTracks_size]/I"); 
    //tree->Branch("RecoTracks", &RT, "px/D:py/D:pz/D:charge/I");
    //tree->Branch("RecoTracks", &RT, "size/i:px[size]/D:py[size]/D:pz[size]/D:charge[size]/I");
    //cout << __FILE__ << ":" << __LINE__ << ":" << __func__ << endl;

}

// ------------ method called once each job just after ending the event loop  ------------
void BasicTrackAnalysis::endJob() 
{
    //cout << __FILE__ << ":" << __LINE__ << ":" << __func__ << endl;
}

// ------------ method called when starting to processes a run  ------------
/*
   void 
   BasicTrackAnalysis::beginRun(edm::Run const&, edm::EventSetup const&)
   {
   }
   */

// ------------ method called when ending the processing of a run  ------------
/*
   void 
   BasicTrackAnalysis::endRun(edm::Run const&, edm::EventSetup const&)
   {
   }
   */

// ------------ method called when starting to processes a luminosity block  ------------
/*
   void 
   BasicTrackAnalysis::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
   {
   }
   */

// ------------ method called when ending the processing of a luminosity block  ------------
/*
   void 
   BasicTrackAnalysis::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
   {
   }
   */

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void BasicTrackAnalysis::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
    //The following says we do not know what parameters are allowed so do no validation
    // Please change this to state exactly what you do use, even if it is no parameters
    edm::ParameterSetDescription desc;
    desc.setUnknown();
    descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(BasicTrackAnalysis);
