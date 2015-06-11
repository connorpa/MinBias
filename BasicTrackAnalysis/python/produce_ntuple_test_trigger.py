import FWCore.ParameterSet.Config as cms

process = cms.Process("TreeProducer")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'root://xrootd-cms.infn.it//store/relval/CMSSW_7_4_4/RelValMinBias_13/GEN-SIM-RECO/MCRUN2_740TV1_0Tv2-v1/00000/18B37DA5-EB07-E511-98E2-0025905A6138.root',
        'root://xrootd-cms.infn.it//store/relval/CMSSW_7_4_4/RelValMinBias_13/GEN-SIM-RECO/MCRUN2_740TV1_0Tv2-v1/00000/40FE47E4-F107-E511-80AC-0025905B860C.root',
        'root://xrootd-cms.infn.it//store/relval/CMSSW_7_4_4/RelValMinBias_13/GEN-SIM-RECO/MCRUN2_740TV1_0Tv2-v1/00000/44C8D48B-EA07-E511-B23A-0025905B8582.root',
        'root://xrootd-cms.infn.it//store/relval/CMSSW_7_4_4/RelValMinBias_13/GEN-SIM-RECO/MCRUN2_740TV1_0Tv2-v1/00000/526E0C31-EB07-E511-9386-0025905A48FC.root',
        'root://xrootd-cms.infn.it//store/relval/CMSSW_7_4_4/RelValMinBias_13/GEN-SIM-RECO/MCRUN2_740TV1_0Tv2-v1/00000/5816BB2F-EA07-E511-BD80-0025905A6056.root',
        'root://xrootd-cms.infn.it//store/relval/CMSSW_7_4_4/RelValMinBias_13/GEN-SIM-RECO/MCRUN2_740TV1_0Tv2-v1/00000/78F988CE-ED07-E511-AA3B-0025905A60F2.root',
        'root://xrootd-cms.infn.it//store/relval/CMSSW_7_4_4/RelValMinBias_13/GEN-SIM-RECO/MCRUN2_740TV1_0Tv2-v1/00000/945CCB30-F207-E511-8B09-003048FF9AC6.root',
        'root://xrootd-cms.infn.it//store/relval/CMSSW_7_4_4/RelValMinBias_13/GEN-SIM-RECO/MCRUN2_740TV1_0Tv2-v1/00000/F0E315A2-E907-E511-9082-0025905A60A0.root'
    )
)
process.TFileService = cms.Service("TFileService",
        fileName = cms.string("/afs/desy.de/user/c/connorpa/nfs/dndeta_analysis_samples/bonsai_MC_RelValMinBias_13_test.root")
)

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
    , StoreL1GT            = cms.bool(True ) , L1GT            = cms.InputTag("gtDigis"               , ""             , "RECO")
                                             , L1TT_requested  = cms.vstring('L1Tech_BSC_minBias_threshold1.v0',
                                                                             'L1Tech_BSC_minBias_threshold2.v0',
                                                                             'L1Tech_BPTX_plus_AND_minus.v0')
    , StoreHLT             = cms.bool(True ) , HLT             = cms.InputTag("TriggerResults"        , ""             , "HLT" )
                                             , HLT_requested   = cms.vstring('HLT_ZeroBias_v2')
)



process.p = cms.Path(process.minbiasdata)
