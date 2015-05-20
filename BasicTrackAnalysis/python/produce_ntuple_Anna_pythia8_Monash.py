import FWCore.ParameterSet.Config as cms

process = cms.Process("TreeProducer")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100000) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'root://xrootd-cms.infn.it//store/user/azsigmon/MinBias_TuneMonash13_13TeV-pythia8/MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO/150317_211242/0000/step3_RAW2DIGI_L1Reco_RECO_1.root',
        'root://xrootd-cms.infn.it//store/user/azsigmon/MinBias_TuneMonash13_13TeV-pythia8/MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO/150317_211242/0000/step3_RAW2DIGI_L1Reco_RECO_10.root',
        'root://xrootd-cms.infn.it//store/user/azsigmon/MinBias_TuneMonash13_13TeV-pythia8/MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO/150317_211242/0000/step3_RAW2DIGI_L1Reco_RECO_2.root',
        'root://xrootd-cms.infn.it//store/user/azsigmon/MinBias_TuneMonash13_13TeV-pythia8/MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO/150317_211242/0000/step3_RAW2DIGI_L1Reco_RECO_3.root',
        'root://xrootd-cms.infn.it//store/user/azsigmon/MinBias_TuneMonash13_13TeV-pythia8/MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO/150317_211242/0000/step3_RAW2DIGI_L1Reco_RECO_4.root',
        'root://xrootd-cms.infn.it//store/user/azsigmon/MinBias_TuneMonash13_13TeV-pythia8/MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO/150317_211242/0000/step3_RAW2DIGI_L1Reco_RECO_5.root',
        'root://xrootd-cms.infn.it//store/user/azsigmon/MinBias_TuneMonash13_13TeV-pythia8/MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO/150317_211242/0000/step3_RAW2DIGI_L1Reco_RECO_6.root',
        'root://xrootd-cms.infn.it//store/user/azsigmon/MinBias_TuneMonash13_13TeV-pythia8/MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO/150317_211242/0000/step3_RAW2DIGI_L1Reco_RECO_7.root',
        'root://xrootd-cms.infn.it//store/user/azsigmon/MinBias_TuneMonash13_13TeV-pythia8/MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO/150317_211242/0000/step3_RAW2DIGI_L1Reco_RECO_8.root',
        'root://xrootd-cms.infn.it//store/user/azsigmon/MinBias_TuneMonash13_13TeV-pythia8/MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO/150317_211242/0000/step3_RAW2DIGI_L1Reco_RECO_9.root'
    )
)
process.TFileService = cms.Service("TFileService",
        fileName = cms.string("/afs/desy.de/user/c/connorpa/CMSSW/CMSSW_7_4_0/src/MinBias/BasicTrackAnalysis/data/MinBias_TuneMonash13_13TeV-pythia8_MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO.root")
)


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
