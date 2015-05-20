import FWCore.ParameterSet.Config as cms

process = cms.Process("TreeProducer")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100000) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        # TODO: write list of input files
    )
)
process.TFileService = cms.Service("TFileService",
        fileName = cms.string("/afs/desy.de/user/c/connorpa/CMSSW/CMSSW_7_4_0/src/MinBias/BasicTrackAnalysis/data/bonsai.root")
)

# TODO: adapt the input tags according to the content of the input files
process.minbiasdata = cms.EDAnalyzer('TreeProducer'
    , StoreBeamSpot               = cms.bool(True)   , BeamSpot               = cms.InputTag("offlineBeamSpot"       , "", "RECO")
    , StoreLumiProducer           = cms.bool(False)  , LumiProducer           = cms.InputTag("lumiProducer"          ) #,   , "") # TODO
    , StoreGenParticles           = cms.bool(True)   , GenParticles           = cms.InputTag("genParticles"          , "", "SIM" )
    , StoreCaloTower              = cms.bool(False)  , CaloTower              = cms.InputTag("towerMaker"            ) #,   , "RECO")
    , StoreGeneralTracks          = cms.bool(True)   , GeneralTracks          = cms.InputTag("generalTracks"         , "", "RECO")
    , StoreOfflinePrimaryVertices = cms.bool(True)   , OfflinePrimaryVertices = cms.InputTag("offlinePrimaryVertices", "", "RECO")
    , StoreHFRecHit               = cms.bool(False)  , HFRecHit               = cms.InputTag("hfreco"                , "", "RECO")
)


process.p = cms.Path(process.minbiasdata)
