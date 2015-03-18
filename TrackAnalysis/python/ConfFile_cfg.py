import FWCore.ParameterSet.Config as cms

process = cms.Process("TrackAnalysis") # just a name
# it would be added at the name of new branches for instance
# if we would produce n-tuples

# FWCore -> basic python files
process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-42) )


# input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'file:/afs/desy.de/user/c/connorpa/CMSSW/CMSSW_7_4_0_pre8/src/MinBias/TrackAnalysis/test/file_track_test.root'
    )
)

# ouput
process.TFileService = cms.Service("TFileService",
        fileName = cms.string("/afs/desy.de/user/c/connorpa/CMSSW/CMSSW_7_4_0_pre8/src/MinBias/TrackAnalysis/test/trackanalysis_output.root")
        #closeFileFast = cms.untracked.bool(True)
        )

process.trackanalysis = cms.EDAnalyzer('TrackAnalysis',
                                       generalTrack_label = cms.InputTag("generalTracks", "", "RECO")
)


process.p = cms.Path(process.trackanalysis)
