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
        fileName = cms.string("/afs/desy.de/user/c/connorpa/CMSSW/CMSSW_7_4_0/src/MinBias/BasicTrackAnalysis/data/bonsai_MC_TODO.root")
)

# TODO: adapt the input tags according to the content of the input files
process.minbiasdata = cms.EDAnalyzer('TreeProducer'
    , StoreBeamSpot        = cms.bool(True ) , BeamSpot        = cms.InputTag("offlineBeamSpot"       , ""             , "RECO")
    , StoreLumiProducer    = cms.bool(False) , LumiProducer    = cms.InputTag("lumiProducer"          , ""             , ""    )
    , StorePrimaryVertices = cms.bool(True ) , PrimaryVertices = cms.InputTag("offlinePrimaryVertices", ""             , "RECO")
    , StoreGeneralTracks   = cms.bool(True ) , GeneralTracks   = cms.InputTag("generalTracks"         , ""             , "RECO")
    , StoreEBRecHit        = cms.bool(True ) , EBRecHit        = cms.InputTag("ecalRecHit"            , "EcalRecHitsEB", "RECO")
    , StoreEERecHit        = cms.bool(True ) , EERecHit        = cms.InputTag("ecalRecHit"            , "EcalRecHitsEE", "RECO")
    , StoreHBHERecHit      = cms.bool(True ) , HBHERecHit      = cms.InputTag("hbhereco"              , ""             , "RECO")
    , StoreHORecHit        = cms.bool(True ) , HORecHit        = cms.InputTag("horeco"                , ""             , "RECO")
    , StoreHFRecHit        = cms.bool(True ) , HFRecHit        = cms.InputTag("hfreco"                , ""             , "RECO")
    , StoreCaloTower       = cms.bool(True ) , CaloTower       = cms.InputTag("towerMaker"            , ""             , "RECO")
    , StoreGenParticles    = cms.bool(True ) , GenParticles    = cms.InputTag("genParticles"          , ""             , "HLT" )
)


process.p = cms.Path(process.minbiasdata)
