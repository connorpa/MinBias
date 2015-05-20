import FWCore.ParameterSet.Config as cms

process = cms.Process("TreeProducer")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100000) )

#################################################################
# (un)comment the source file according to the requested source #
# the name of the output must also be *un)commented             #
#################################################################
## test file
#process.source = cms.Source("PoolSource",
#    fileNames = cms.untracked.vstring(
#        'file:/afs/desy.de/user/c/connorpa/CMSSW/CMSSW_7_4_0/src/MinBias/BasicTrackAnalysis/data/hftrigger_rereco_step2_hcaldigi_th_12.root'
#    )
#)
#process.TFileService = cms.Service("TFileService",
#        fileName = cms.string("/afs/desy.de/user/c/connorpa/CMSSW/CMSSW_7_4_0/src/MinBias/BasicTrackAnalysis/data/bonsai.root")
#)
## Anna's Pythia 8 (min bias tracking?) --> cannot access
#process.source = cms.Source("PoolSource",
#    fileNames = cms.untracked.vstring(
#        'root://xrootd-cms.infn.it//store/user/azsigmon/MinBias_TuneZ2star_13TeV-pythia6/MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO/150320_082018/0000/step3_RAW2DIGI_L1Reco_RECO_1.root',
#        'root://xrootd-cms.infn.it//store/user/azsigmon/MinBias_TuneZ2star_13TeV-pythia6/MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO/150320_082018/0000/step3_RAW2DIGI_L1Reco_RECO_2.root',
#        'root://xrootd-cms.infn.it//store/user/azsigmon/MinBias_TuneZ2star_13TeV-pythia6/MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO/150320_082018/0000/step3_RAW2DIGI_L1Reco_RECO_3.root',
#        'root://xrootd-cms.infn.it//store/user/azsigmon/MinBias_TuneZ2star_13TeV-pythia6/MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO/150320_082018/0000/step3_RAW2DIGI_L1Reco_RECO_4.root',
#        'root://xrootd-cms.infn.it//store/user/azsigmon/MinBias_TuneZ2star_13TeV-pythia6/MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO/150320_082018/0000/step3_RAW2DIGI_L1Reco_RECO_5.root',
#        'root://xrootd-cms.infn.it//store/user/azsigmon/MinBias_TuneZ2star_13TeV-pythia6/MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO/150320_082018/0000/step3_RAW2DIGI_L1Reco_RECO_6.root',
#        'root://xrootd-cms.infn.it//store/user/azsigmon/MinBias_TuneZ2star_13TeV-pythia6/MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO/150320_082018/0000/step3_RAW2DIGI_L1Reco_RECO_7.root',
#        'root://xrootd-cms.infn.it//store/user/azsigmon/MinBias_TuneZ2star_13TeV-pythia6/MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO/150320_082018/0000/step3_RAW2DIGI_L1Reco_RECO_8.root',
#        'root://xrootd-cms.infn.it//store/user/azsigmon/MinBias_TuneZ2star_13TeV-pythia6/MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO/150320_082018/0000/step3_RAW2DIGI_L1Reco_RECO_9.root'
#        'root://xrootd-cms.infn.it//store/user/azsigmon/MinBias_TuneZ2star_13TeV-pythia6/MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO/150320_082018/0000/step3_RAW2DIGI_L1Reco_RECO_10.root',
#    )
#)
#process.TFileService = cms.Service("TFileService",
#        fileName = cms.string("/afs/desy.de/user/c/connorpa/CMSSW/CMSSW_7_4_0/src/MinBias/BasicTrackAnalysis/data/MinBias_TuneZ2star_13TeV-pythia6_MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO.root")
#)
## Anna's Pythia 8 (min bias tracking?) --> cannot access
#process.source = cms.Source("PoolSource",
#    fileNames = cms.untracked.vstring(
#        'root://xrootd-cms.infn.it//store/user/azsigmon/MinBias_TuneMonash13_13TeV-pythia8/MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO/150317_211242/0000/step3_RAW2DIGI_L1Reco_RECO_1.root',
#        'root://xrootd-cms.infn.it//store/user/azsigmon/MinBias_TuneMonash13_13TeV-pythia8/MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO/150317_211242/0000/step3_RAW2DIGI_L1Reco_RECO_10.root',
#        'root://xrootd-cms.infn.it//store/user/azsigmon/MinBias_TuneMonash13_13TeV-pythia8/MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO/150317_211242/0000/step3_RAW2DIGI_L1Reco_RECO_2.root',
#        'root://xrootd-cms.infn.it//store/user/azsigmon/MinBias_TuneMonash13_13TeV-pythia8/MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO/150317_211242/0000/step3_RAW2DIGI_L1Reco_RECO_3.root',
#        'root://xrootd-cms.infn.it//store/user/azsigmon/MinBias_TuneMonash13_13TeV-pythia8/MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO/150317_211242/0000/step3_RAW2DIGI_L1Reco_RECO_4.root',
#        'root://xrootd-cms.infn.it//store/user/azsigmon/MinBias_TuneMonash13_13TeV-pythia8/MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO/150317_211242/0000/step3_RAW2DIGI_L1Reco_RECO_5.root',
#        'root://xrootd-cms.infn.it//store/user/azsigmon/MinBias_TuneMonash13_13TeV-pythia8/MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO/150317_211242/0000/step3_RAW2DIGI_L1Reco_RECO_6.root',
#        'root://xrootd-cms.infn.it//store/user/azsigmon/MinBias_TuneMonash13_13TeV-pythia8/MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO/150317_211242/0000/step3_RAW2DIGI_L1Reco_RECO_7.root',
#        'root://xrootd-cms.infn.it//store/user/azsigmon/MinBias_TuneMonash13_13TeV-pythia8/MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO/150317_211242/0000/step3_RAW2DIGI_L1Reco_RECO_8.root',
#        'root://xrootd-cms.infn.it//store/user/azsigmon/MinBias_TuneMonash13_13TeV-pythia8/MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO/150317_211242/0000/step3_RAW2DIGI_L1Reco_RECO_9.root'
#    )
#)
#process.TFileService = cms.Service("TFileService",
#        fileName = cms.string("/afs/desy.de/user/c/connorpa/CMSSW/CMSSW_7_4_0/src/MinBias/BasicTrackAnalysis/data/MinBias_TuneMonash13_13TeV-pythia8_MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO.root")
#)
# Anna's EPOS 8 (min bias tracking?) --> no gen level
#process.source = cms.Source("PoolSource",
#    fileNames = cms.untracked.vstring(
#        'root://xrootd-cms.infn.it//store/user/azsigmon/ReggeGribovPartonMC_13TeV-EPOS/MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO/150320_081623/0000/step3_RAW2DIGI_L1Reco_RECO_1.root',
#        'root://xrootd-cms.infn.it//store/user/azsigmon/ReggeGribovPartonMC_13TeV-EPOS/MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO/150320_081623/0000/step3_RAW2DIGI_L1Reco_RECO_10.root',
#        'root://xrootd-cms.infn.it//store/user/azsigmon/ReggeGribovPartonMC_13TeV-EPOS/MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO/150320_081623/0000/step3_RAW2DIGI_L1Reco_RECO_2.root',
#        'root://xrootd-cms.infn.it//store/user/azsigmon/ReggeGribovPartonMC_13TeV-EPOS/MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO/150320_081623/0000/step3_RAW2DIGI_L1Reco_RECO_3.root',
#        'root://xrootd-cms.infn.it//store/user/azsigmon/ReggeGribovPartonMC_13TeV-EPOS/MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO/150320_081623/0000/step3_RAW2DIGI_L1Reco_RECO_4.root',
#        'root://xrootd-cms.infn.it//store/user/azsigmon/ReggeGribovPartonMC_13TeV-EPOS/MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO/150320_081623/0000/step3_RAW2DIGI_L1Reco_RECO_5.root',
#        'root://xrootd-cms.infn.it//store/user/azsigmon/ReggeGribovPartonMC_13TeV-EPOS/MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO/150320_081623/0000/step3_RAW2DIGI_L1Reco_RECO_6.root',
#        'root://xrootd-cms.infn.it//store/user/azsigmon/ReggeGribovPartonMC_13TeV-EPOS/MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO/150320_081623/0000/step3_RAW2DIGI_L1Reco_RECO_7.root',
#        'root://xrootd-cms.infn.it//store/user/azsigmon/ReggeGribovPartonMC_13TeV-EPOS/MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO/150320_081623/0000/step3_RAW2DIGI_L1Reco_RECO_8.root',
#        'root://xrootd-cms.infn.it//store/user/azsigmon/ReggeGribovPartonMC_13TeV-EPOS/MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO/150320_081623/0000/step3_RAW2DIGI_L1Reco_RECO_9.root'
#    )
#)
#process.TFileService = cms.Service("TFileService",
#        fileName = cms.string("/afs/desy.de/user/c/connorpa/CMSSW/CMSSW_7_4_0/src/MinBias/BasicTrackAnalysis/data/ReggeGribovPartonMC_13TeV-EPOS_MCRUN2_74_V7-v1-GEN-SIM-RAW-RECO.root")
#)
## Benoit's file GEN-SIM-RAW
#process.source = cms.Source("PoolSource",
#    fileNames = cms.untracked.vstring(
#        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/GEN-SIM-RAW/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/0012773F-F6BF-E311-88A4-00259073E4D4.root',
#        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/GEN-SIM-RAW/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/003C7B7F-FBBF-E311-9C9B-0025907B4F80.root',
#        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/GEN-SIM-RAW/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/004F1455-E8BF-E311-977A-002590D0B066.root',
#        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/GEN-SIM-RAW/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/0050E044-F4BF-E311-9822-20CF305B0590.root',
#        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/GEN-SIM-RAW/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/00535452-E8BF-E311-9069-20CF300E9ECF.root',
#        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/GEN-SIM-RAW/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/0076CE9A-02C0-E311-AFCD-485B39800C1C.root',
#        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/GEN-SIM-RAW/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/00811D1F-F2BF-E311-9D1F-002590D0B022.root',
#        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/GEN-SIM-RAW/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/008AC516-EFBF-E311-BDAC-E0CB4E553677.root',
#        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/GEN-SIM-RAW/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/00D58901-EBBF-E311-ACAE-0025907B4F80.root',
#        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/GEN-SIM-RAW/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/00ED1E95-04C0-E311-A14B-E0CB4EA0A929.root',
#        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/GEN-SIM-RAW/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/00F97911-F4BF-E311-83D5-00259073E322.root',
#        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/GEN-SIM-RAW/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/02055655-E9BF-E311-9DD8-E0CB4E29C4DB.root',
#        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/GEN-SIM-RAW/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/020FACDD-00C0-E311-93DD-485B39800BF3.root',
#        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/GEN-SIM-RAW/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/0256F7E1-F1BF-E311-BC38-20CF3027A5ED.root',
#        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/GEN-SIM-RAW/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/026D4851-F7BF-E311-961C-20CF3027A5E5.root',
#        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/GEN-SIM-RAW/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/027ADD2A-FEBF-E311-B270-002590574A44.root',
#        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/GEN-SIM-RAW/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/02C2285B-03C0-E311-BE3B-0025907277BE.root',
#        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/GEN-SIM-RAW/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/040EA0D5-EBBF-E311-B259-20CF305B0591.root',
#        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/GEN-SIM-RAW/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/044A922D-06C0-E311-9A7F-00259073E53E.root',
#        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/GEN-SIM-RAW/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/048962F8-03C0-E311-935A-E0CB4E1A1186.root'
#    )
#)
#process.TFileService = cms.Service("TFileService",
#        fileName = cms.string("/afs/desy.de/user/c/connorpa/CMSSW/CMSSW_7_4_0/src/MinBias/BasicTrackAnalysis/data/MinBias_TuneZ2star_13TeV_pythia6_GEN-SIM-RAW.root")
#)
## Benoit's file AOD
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/02E11892-E4C0-E311-B178-00259073E316.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/02EDD6C8-EDC0-E311-AD29-485B39800C14.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/02F64AD4-E7C0-E311-8F08-0025907B4FAC.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/0476A9E8-E8C0-E311-9918-E0CB4E553659.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/0491940B-EDC0-E311-A6B6-E0CB4E1A116B.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/06508647-E5C0-E311-BCFC-E0CB4E553659.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/0873B7B4-E5C0-E311-8FDE-00261834B55F.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/0A403FD1-E5C0-E311-B110-E0CB4E4408E9.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/0C7C828D-E4C0-E311-A910-90E6BA19A241.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/0E4DE1AC-E8C0-E311-84E6-002590D0AFA8.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/0EA367C0-EEC0-E311-958A-E0CB4E1A116B.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/0EBC454A-EBC0-E311-91E8-00261834B55F.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/10755E3A-E6C0-E311-B066-E0CB4E553691.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/12AADEB4-F0C0-E311-850C-002590D0B0CC.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/12EC8789-EAC0-E311-9B1F-001EC9D82BAF.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/12FF35DF-ECC0-E311-AF49-001EC9D7FA24.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/145B5EF9-E7C0-E311-A815-20CF305B057A.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/16034D4E-F0C0-E311-B2A0-00259074AE3C.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/169500C2-E6C0-E311-91BD-E0CB4E553677.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/1A086E3A-F3C0-E311-AAFE-00259074AEAC.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/1AEB532F-EFC0-E311-87A5-00259073E510.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/1C076A92-FDC0-E311-B611-20CF3056171C.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/1C936DF4-EDC0-E311-A5F6-90E6BAE8CC13.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/1CDCAE51-E8C0-E311-8173-00259074AEAE.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/1EEFDC44-E4C0-E311-8F48-90E6BA442F07.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/2081D139-F3C0-E311-BA71-0025907B4FB6.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/20BED23C-F3C0-E311-BC07-00261834B51B.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/20CA778D-E2C0-E311-8987-90E6BA442F07.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/22D5CEE8-E6C0-E311-A3D8-00259073E32A.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/24AC9A67-E6C0-E311-A7F1-002590D0B0D6.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/24D04BE9-EEC0-E311-A108-485B39800C14.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/24FC8459-E7C0-E311-A78B-002590D0AFFC.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/2601C34A-E8C0-E311-A79D-E0CB4E19F982.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/26AF138B-EAC0-E311-BF0F-0025907B4F4A.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/26AFE40E-F0C0-E311-9E31-001EC9D7FA24.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/26E232B6-E5C0-E311-9CC4-E0CB4E553637.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/28B45069-E6C0-E311-BF28-20CF300E9EB6.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/28C8AD31-E9C0-E311-BDCB-E0CB4E19F982.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/2A5237E4-E4C0-E311-A69B-E0CB4E19F965.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/2ABACB91-EAC0-E311-870B-001EC9D7FA24.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/2AE07375-E3C0-E311-A261-E0CB4E19F965.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/2C8BC01D-E7C0-E311-BA00-E0CB4E553659.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/2CCC4301-E5C0-E311-86C8-E0CB4E4408E9.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/2CD73F3F-E6C0-E311-8B7E-90E6BA0D09AB.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/2CEEF33D-EFC0-E311-8820-001EC9D7FA24.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/2E4FCF9C-EDC0-E311-B56A-20CF3027A631.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/2E6526D0-E8C0-E311-8671-002590747E40.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/300AF699-E9C0-E311-821E-002590D0AFFC.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/30C6A954-E7C0-E311-930D-20CF300E9ED6.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/30D93B3F-E9C0-E311-AC05-002590D0B0D6.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/3448A40A-EDC0-E311-AA1E-00261834B524.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/349606D0-E5C0-E311-9C25-90E6BA0D09C2.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/34AE48E1-EDC0-E311-A0A6-002590D0B008.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/34CFD54C-E8C0-E311-BE69-485B39897225.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/38F41B41-F3C0-E311-8402-002590D0B09A.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/3ADD8249-FDC0-E311-8E57-00259073E4DA.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/3C752B84-E4C0-E311-AA37-002590D0B03A.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/3C7AE9BC-E8C0-E311-A5AA-E0CB4E553691.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/3E78E68B-EAC0-E311-8FEA-20CF3027A5D5.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/3ED27477-E4C0-E311-A78A-002590D0B052.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/40212141-EBC0-E311-9954-00259074E196.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/40EE286C-E6C0-E311-9939-20CF305B057E.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/44616587-E5C0-E311-B146-002590D0B032.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/44B71702-E5C0-E311-8966-E0CB4E553677.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/44F9963D-E8C0-E311-A93C-00259073E32A.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/44FF939F-E2C0-E311-82CF-E0CB4E19F965.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/46EB2C3D-EBC0-E311-B9D6-E0CB4E4408EF.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/48164E27-EAC0-E311-A3F6-90E6BA442F1F.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/48464CC4-E7C0-E311-8EB1-90E6BA442F15.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/4882AC17-E4C0-E311-801D-E0CB4E4408E9.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/4A1CAF52-E7C0-E311-8647-002590D0B0D6.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/4A84C026-EFC0-E311-9FC4-0025907B4FD6.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/4CD4DCE0-E4C0-E311-9A60-E0CB4E553637.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/4E12357C-E8C0-E311-B47E-002590D0B00A.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/4E3354BB-E6C0-E311-BD4B-0025907B4F14.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/4EA369D7-E5C0-E311-BC35-E0CB4E553677.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/4EF7F2E3-ECC0-E311-8F1C-002590D0AF7C.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/524021D6-EDC0-E311-BDC0-20CF305B051B.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/54481B1F-ECC0-E311-A5B0-E0CB4E29C4E5.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/549AC4B2-E4C0-E311-A616-0025907B4FAC.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/54A92EDA-E9C0-E311-888E-20CF3027A5C4.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/562A9FAA-E9C0-E311-9F15-485B39800BFB.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/5694A5E1-E7C0-E311-8207-002590D0B022.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/5698B411-E6C0-E311-B59D-002590747E40.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/581B1C8C-E8C0-E311-8F3A-E0CB4E29C4CB.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/5A2E944F-E8C0-E311-A31E-002590D60134.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/5CC9E30D-EDC0-E311-A36C-00261834B51D.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/5EBA4278-EAC0-E311-A110-BCAEC50971E2.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/5EEBB220-ECC0-E311-97AE-E0CB4E4408EF.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/608C4E38-E6C0-E311-A1BB-0025907B5038.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/62111EAC-EEC0-E311-BA61-002590D0B0CC.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/623EEB3D-EFC0-E311-9048-20CF3027A5D5.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/648CC131-E9C0-E311-8A58-20CF300E9EB6.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/6643B85F-E8C0-E311-A56E-002590D0AFFC.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/668D0C79-EAC0-E311-97F4-002590D0AF8E.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/68A8B849-ECC0-E311-AC27-20CF305B051B.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/6A4F20E8-ECC0-E311-AC46-00259073E2F2.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/6C965581-E9C0-E311-8D1C-00259074AEAE.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/70F8903D-EBC0-E311-862B-E0CB4E29C4E5.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/72667B84-E5C0-E311-8AA8-90E6BA19A206.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/727E13BC-EEC0-E311-A063-E0CB4E29C514.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/7432EBFD-ECC0-E311-B7C6-002590747E1C.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/743450A4-EEC0-E311-90A9-E0CB4E553691.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/748A6429-E6C0-E311-A39D-0025907B4FAC.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/74AFE688-E9C0-E311-845C-90E6BA442F15.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/7617EA1F-EAC0-E311-9D78-E0CB4E5536EF.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/76ECF42A-E6C0-E311-AC40-E0CB4E553659.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/7ACACBB7-F0C0-E311-BD33-20CF305B0572.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/7AF7D156-E7C0-E311-81B6-002590747E40.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/7C5E85A1-E9C0-E311-9F4D-E0CB4E29C4E5.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/7C95D941-E1C0-E311-85F0-0025907B4FC4.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/7CBE5E05-EDC0-E311-A6A4-E0CB4E19F975.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/7E1CABEB-E1C0-E311-A0FD-E0CB4E55367B.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/7EBCD6DD-ECC0-E311-8274-20CF3027A5D5.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/7EDF1494-E9C0-E311-B8CF-E0CB4E4408EF.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/8661F932-E6C0-E311-A85F-00259074AE32.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/88B7CADD-E4C0-E311-9BF6-002590747E40.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/8A585E75-EEC0-E311-8E6C-20CF3027A5D5.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/8CE7528F-EFC0-E311-9A06-90E6BAE8CC13.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/8E281B23-E7C0-E311-903F-20CF3027A626.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/8EA696CF-E6C0-E311-9866-20CF305B057A.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/8EAFEC8A-EAC0-E311-A9C7-002590D0AFA8.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/9052C359-EBC0-E311-BD3E-001EC9D7FA24.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/90859F22-E1C0-E311-9EEB-0025907B4F3E.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/90ADB162-EEC0-E311-A081-90E6BAE8CC13.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/90B851F8-E4C0-E311-912C-90E6BA0D09C2.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/9218D060-ECC0-E311-897C-002590D0AFFC.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/98A5B637-E7C0-E311-888B-20CF300E9EB6.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/9A608DCB-E7C0-E311-ADDE-E0CB4E553691.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/9AB222E9-E7C0-E311-8444-0025907B4F14.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/9C188382-E5C0-E311-9B53-00259073E32A.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/9C4FCC6A-EBC0-E311-B7DA-20CF3027A5D5.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/9EC7DA1E-F0C0-E311-A5B8-E0CB4E1A116B.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/A056D358-EBC0-E311-B663-002590D0AFFC.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/A05820AD-EDC0-E311-8AF2-E0CB4E553691.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/A0B2CDD2-EDC0-E311-B09B-00261834B561.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/A868AF37-E9C0-E311-93E4-20CF305B0591.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/A86ABFD8-E5C0-E311-A972-20CF305B057A.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/AA0544B9-E3C0-E311-991E-90E6BA442F0D.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/AA553868-F0C0-E311-A3DE-00259073E53E.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/ACA72DAD-EEC0-E311-9F60-002590D0AF92.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/ACFE116E-E3C0-E311-B162-90E6BA442F07.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/AE1202EC-E1C0-E311-A9B3-0025907B4FB6.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/AE7C470B-F0C0-E311-8B13-20CF3027A5D5.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/AEC2B48F-EAC0-E311-8089-00259073E536.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/B05F1EE2-E4C0-E311-894B-90E6BA442F2D.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/B0B2E25B-EFC0-E311-83B3-90E6BAE8CC13.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/B253B204-EDC0-E311-A829-E0CB4E4408EF.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/B27A94E0-E4C0-E311-A895-20CF305B057A.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/B2D6FEBC-ECC0-E311-BBDF-20CF3027A631.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/B42DDAF2-E1C0-E311-85E6-E0CB4E1A1150.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/B43E33D1-FDC0-E311-8A6C-00259073E32A.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/B45D167F-E4C0-E311-9DFD-00259074AE32.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/B4AED721-E4C0-E311-AE6E-E0CB4E553677.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/B4BA6DBF-E5C0-E311-BA0A-90E6BA442F2D.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/B60C4AEC-E7C0-E311-BC73-20CF3027A626.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/B88B324B-E8C0-E311-B855-20CF305616EC.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/B89B5BDE-E4C0-E311-ABA1-0025907B4F14.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/BA1AE8C9-F0C0-E311-B1DD-90E6BA442F3E.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/BA51FE33-E9C0-E311-A381-20CF305B057E.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/BC62879B-EFC0-E311-A121-00259074AE40.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/BC6EEA96-E9C0-E311-9422-002590D0AFA8.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/BCBCFB29-E8C0-E311-9642-20CF300E9EB6.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/BCD72866-EBC0-E311-98A7-001EC9D82BAF.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/C02E3A43-E8C0-E311-B336-20CF300E9ED6.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/C06E4AE2-E4C0-E311-BDAE-002590D0B0D6.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/C204B076-E4C0-E311-ACE2-00259073E3FC.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/C211CA58-E5C0-E311-9DC1-002590D0B022.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/C42E0CF2-E0C0-E311-96F1-002590D0AFD8.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/C483B272-E7C0-E311-AD2A-E0CB4E19F965.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/C48F4C17-EDC0-E311-BF91-002590D0B0CC.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/C496CB4A-E8C0-E311-9196-002590D0B0D6.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/C4AAAFA2-EDC0-E311-A156-001EC9D7FA24.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/C4E8757A-E4C0-E311-9437-90E6BA19A214.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/C6907D5E-EAC0-E311-A45D-20CF305B051B.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/C81248DE-E4C0-E311-AF0D-00261834B55F.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/CA0EEB33-E9C0-E311-A90A-485B39897225.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/CAAB3D60-EBC0-E311-AE50-E0CB4E553691.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/CC024C51-E8C0-E311-9E0E-002590D0B0AE.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/D4CC61D5-E5C0-E311-8E96-0025907B4F14.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/D6E0EDD9-E4C0-E311-B609-0025907B5038.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/D84DB39B-E9C0-E311-999B-002590D0B00A.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/DC2846AC-EEC0-E311-A2B9-002590D0B01E.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/DC51B1E0-E4C0-E311-8ABB-E0CB4E4408CD.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/DC9FF541-E7C0-E311-A5BF-20CF305B057E.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/DE582662-EAC0-E311-8B52-E0CB4E553691.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/DE95702F-E6C0-E311-AB4D-90E6BA442F15.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/DEC8F69F-EEC0-E311-ADFD-00259073E53E.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/DEEAB8F9-ECC0-E311-B9ED-20CF3027A5B9.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/E200D724-E4C0-E311-9CE6-90E6BA0D09C2.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/E63B5243-E8C0-E311-BF42-E0CB4E19F965.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/E6708E6A-E6C0-E311-BF63-20CF3027A626.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/E6843DB6-E6C0-E311-AF56-E0CB4E4408E9.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/E89E64E9-E8C0-E311-99C5-002590747E28.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/E8C62497-E9C0-E311-AE96-BCAEC50971E2.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/EA3360C0-EDC0-E311-A8FD-00261834B51D.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/EACF0E7A-E4C0-E311-AE93-90E6BA19A214.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/EC0DEF80-EAC0-E311-90A3-002590D0AFFC.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/EC210069-E7C0-E311-B06B-002590747E28.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/EC35B994-E4C0-E311-AA80-00259073E4DA.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/EC69E5DC-E6C0-E311-9FAB-002590D0B022.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/F0C62C0B-E8C0-E311-8D8D-E0CB4E553659.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/F42939A6-EDC0-E311-ABED-20CF3027A5D5.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/F466A470-EEC0-E311-A3F7-001EC9D7FA24.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/F4EADDE1-ECC0-E311-8C8E-002590D0B01E.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/F65EBE59-E7C0-E311-8786-002590D60134.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/F6ADB440-E8C0-E311-9D1D-20CF305B057E.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/FAA09557-E5C0-E311-98F9-E0CB4E553691.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/FC64CF1D-EDC0-E311-878E-00259074E196.root',
        'root://xrootd-cms.infn.it//store/mc/Fall13dr/MinBias_TuneZ2star_13TeV_pythia6/AODSIM/castor_tsg_NoPileUp_POSTLS162_V1-v1/00000/FE39B072-EAC0-E311-B821-00261834B55F.root'
    )
)
process.TFileService = cms.Service("TFileService",
        fileName = cms.string("/afs/desy.de/user/c/connorpa/CMSSW/CMSSW_7_4_0/src/MinBias/BasicTrackAnalysis/data/MinBias_TuneZ2star_13TeV_pythia6_AODSIM_castor_tsg_NoPileUp_POSTLS162_V1-v1.root")
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
