import FWCore.ParameterSet.Config as cms

process = cms.Process("TreeProducer")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100000) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        # TODO: write list of input files
        # root://xrootd-cms.infn.it/
    )
)
process.TFileService = cms.Service("TFileService",
        fileName = cms.string("/afs/desy.de/user/c/connorpa/CMSSW/CMSSW_7_4_0/src/MinBias/BasicTrackAnalysis/data/bonsai_MC_TODO.root")
)

# TODO: find right global tag
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'MCRUN2_74_V8::All'


# TODO: adapt the input tags according to the content of the input files
# recall: in the TTree, there is by convention (?) a 4-component name: [cpptype]_[label]_[instance]_[processname]
# where the first is the CMSSW type to be used to read the object (including the possible namespace),
# and the three other are the options of edm::InputTag (std::string const &label, std::string const &instance, std::string const &processName="")
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
    # TODO: find right triggers (run the code with just 1 event to see the list of existing triggers
    , StoreL1GT            = cms.bool(True ) , L1GT            = cms.InputTag("gtDigis"               , ""             , "RECO")
                                             , L1TT_requested  = cms.vstring('L1Tech_BSC_minBias_threshold1.v0',
                                                                             'L1Tech_BSC_minBias_threshold2.v0',
                                                                             'L1Tech_BPTX_plus_AND_minus.v0')
    , StoreHLT             = cms.bool(True ) , HLT             = cms.InputTag("TriggerResults"        , ""             , "HLT" )
                                             , HLT_requested   = cms.vstring('HLT_ZeroBias_v1')
)



process.p = cms.Path(process.minbiasdata)
