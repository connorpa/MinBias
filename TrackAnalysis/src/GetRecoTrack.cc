//-- Description: Function to retrieve Generated particles from HEPEVT (original author: Patrick & Juan)

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

//-- DataFormats
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
//#include "SimGeneral/HepPDTRecord/interface/ParticleDataTable.h"
//#include "HepPDT/ParticleDataTable.h"

#include "./TrackAnalysisTree.h"

bool RecoTrackDebug = false;

void TrackAnalysisTree::GetRecoTrack(const edm::Event& iEvent)
{
    using namespace std;
    using namespace edm;
    using namespace reco;

    RecoTrack.clear();

    Handle<TrackCollection> trackcollection;
    iEvent.getByLabel(generalTracksColl_,trackcollection);

    //if (!trackcollection.isValid()) {
    //    cerr << "TrackAnalysisTree::GetGenPart] Error: non valid GenParticleCollection " << endl;
    //    return;
    //}

    //-- Loop on generated particle and store if status = 1
    if(RecoTrackDebug) cout << "number of reco tracks: "<<trackcollection->size()<<endl;

    for(TrackCollection::const_iterator p = trackcollection->begin(); p != trackcollection->end(); ++ p)
    {
        //MyTrack track(p->px(),p->py(),p->pz());
        MyTrack track;
        track.SetXYZ(p->px(),p->py(),p->pz());
        track.charge  = p->charge();
        RecoTrack.push_back(track);
        if(RecoTrackDebug)   track.Print();
    }
}
