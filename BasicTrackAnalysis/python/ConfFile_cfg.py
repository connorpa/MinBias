import FWCore.ParameterSet.Config as cms

process = cms.Process("TrackTree")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:/afs/desy.de/user/c/connorpa/CMSSW/CMSSW_7_4_0_pre8/src/MinBias/TrackAnalysis/data/file_track_test.root'
    )
)

process.TFileService = cms.Service("TFileService",
        fileName = cms.string("/afs/desy.de/user/c/connorpa/CMSSW/CMSSW_7_4_0/src/MinBias/BasicTrackAnalysis/data/trackanalysis_output.root")
    )

process.minbiasdata = cms.EDAnalyzer('BasicTrackAnalysis'
   #, storeGenPart  = cms.bool(True),
   #, genParticles           = cms.InputTag("genParticles"          , "", "SIM" )
    , generalTracks          = cms.InputTag("generalTracks"         , "", "RECO")
    , offlinePrimaryVertices = cms.InputTag("offlinePrimaryVertices", "", "RECO")
)


process.p = cms.Path(process.minbiasdata)
