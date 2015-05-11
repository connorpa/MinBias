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
        'file:/afs/desy.de/user/c/connorpa/CMSSW/CMSSW_7_4_0_pre8/src/MinBias/TrackAnalysis/data/file_track_test.root'
    )
)

# magnetic field
#process.load('Configuration.StandardSequences.MagneticField_38T_cff') #TODO


# require primary vertex
process.oneGoodVertexFilter = cms.EDFilter("VertexSelector",
   src = cms.InputTag("offlinePrimaryVertices"),
   cut = cms.string("!isFake && ndof >= 4 && abs(z) <= 15 && position.Rho <= 2"), # tracksSize() > 3 for the older cut
   filter = cms.bool(True),   # otherwise it won't filter the events, just produce an empty vertex collection.
)

# communicate with the DB
#process.load('Configuration.StandardSequences.Services_cff')
#process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
#process.GlobalTag.globaltag = 'START311_V2::All' # to be used for reprocessing of 2009 and 2010 data (update JEC to Spring10 V8)


# ouput
process.TFileService = cms.Service("TFileService",
        fileName = cms.string("/afs/desy.de/user/c/connorpa/CMSSW/CMSSW_7_4_0/src/MinBias/TrackAnalysis/data/trackanalysis_output.root")
        #closeFileFast = cms.untracked.bool(True)
        )

process.trackanalysistree = cms.EDAnalyzer('TrackAnalysisTree',

   #StoreGenKine = cms.bool(True),
   StoreGenPart  = cms.bool(True),


   # input tag for L1GtTriggerMenuLite retrieved from provenance
   #L1GT_TrigMenuLite_Prov = cms.bool(True),
   # input tag for L1GtTriggerMenuLite explicitly given
   #L1GT_TrigMenuLite = cms.InputTag('l1GtTriggerMenuLite'),

   #L1GT_ObjectMap = cms.InputTag('hltL1GtObjectMap','','HLT'),

   #hepMCColl = cms.InputTag('generator','','HLT'),
   genParticles           = cms.InputTag("genParticles"          , "", "SIM" ),
   generalTracks          = cms.InputTag("generalTracks"         , "", "RECO"),
   offlinePrimaryVertices = cms.InputTag("offlinePrimaryVertices", "", "RECO")

   #CastorTowerColl = cms.InputTag('CastorTowerReco', '','RECO'),
   #CastorDigiColl = cms.InputTag('castorDigis', '','RECO'),
   #CastorRecHitColl = cms.InputTag('castorreco','','RECO'),
   #BasicJet = cms.InputTag('ak7BasicJets','','RECO'),
   #CastorJetID = cms.InputTag('ak7CastorJetID','','RECO'),

   #PFJetColl = cms.InputTag('ak5PFJets', '', 'RECO'),
   #PFJetJEC = cms.string('ak5PFL2L3Residual'),    # L2L3Residual JEC should be applied to data only
  # PFJetJECunc = cms.string('AK5PF'),
  #
  # CaloJetColl = cms.InputTag('ak5CaloJets','','RECO'),
  # CaloJetId = cms.InputTag('ak5JetID','','RECO'),
  # CaloJetJEC = cms.string('ak5CaloL2L3Residual'), # L2L3Residual JEC should be applied to data only
  # CaloJetJECunc = cms.string('AK5Calo'),

  # CaloTowerColl = cms.InputTag('towerMaker','','RECO'),
  #
  # TightPFJetID_Parameters = TightPFJetID_Parameters7TeV_Ref,
  # LooseCaloJetID_Parameters = LooseCaloJetID_Parameters_Ref,
  # TightCaloJetID_Parameters = TightCaloJetID_Parameters_Ref,
  # JetPtCut = cms.double(20.0), # Jet Pt > 8 GeV at 900 GeV and 2.36 TeV and 20 GeV for 7 TeV
  # JetEtaCut = cms.double(2.5),

  # requested_hlt_bits = cms.vstring('HLT_L1Tech_BSC_minBias','HLT_L1Tech_BSC_minBias_OR')
)


process.p = cms.Path(process.trackanalysistree)
