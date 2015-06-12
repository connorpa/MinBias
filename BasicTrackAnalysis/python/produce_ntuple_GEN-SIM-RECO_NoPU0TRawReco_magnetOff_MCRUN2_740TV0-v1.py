import FWCore.ParameterSet.Config as cms

process = cms.Process("TreeProducer")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100000) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/0AB11284-FD0F-E511-87DD-0002C90B7472.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/0C5D3898-6510-E511-8100-782BCB284437.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/14DBCFDE-FC0F-E511-AC97-008CFA197D48.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/14E713D0-6510-E511-8D4D-782BCB63EBF5.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/1C3E30FB-1E10-E511-BF86-0002C94CD040.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/1E9F1DA4-FD0F-E511-895D-0025907859C4.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/1EF51C5E-F80F-E511-BA59-0002C90F80DA.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/202F97A8-FC0F-E511-88F2-B8CA3A70BAC8.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/208D9D09-FB0F-E511-ACFF-0CC47A4129F4.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/20EB434C-6810-E511-BB6E-00266CFFCD00.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/24B579CF-FA0F-E511-9A04-0CC47A4DED5A.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/26577102-5410-E511-85A5-20CF3019DF13.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/2A5B1F95-6510-E511-B170-001E67398110.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/30EC305D-5410-E511-B1D1-00259048A86E.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/3639C3A8-FB0F-E511-A4E2-0002C92A1020.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/3A0A2B27-FA0F-E511-A928-A0369F301924.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/3AC1FF03-FB0F-E511-80EA-B8CA3A70A410.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/3C93B1A2-0310-E511-BF90-782BCB1612C0.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/42EFD759-FB0F-E511-92CA-0002C90F7FEA.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/46422E17-FA0F-E511-9C5C-0002C92DB44E.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/467D0C5C-FB0F-E511-90C8-B8CA3A70A520.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/489134CB-FD0F-E511-B3E7-0002C94D552A.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/48BBF32B-FA0F-E511-B95B-0025907D2000.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/4A410D61-FB0F-E511-8314-D4AE526A1687.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/4C25B8C9-6510-E511-9A95-00259021A4C2.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/4C7A1718-FF0F-E511-B2B6-1CC1DE18CFF6.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/4CDE84A8-FC0F-E511-8839-F45214C748D0.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/4E319EC2-FB0F-E511-896D-20CF305B058C.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/5207CE7B-5610-E511-8214-1CC1DE18D052.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/52AAA019-FD0F-E511-8DCD-0002C90B7FD6.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/5EA99BE5-F80F-E511-AE88-0002C92DB464.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/605A0DBF-FA0F-E511-856E-002590747DE2.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/62C3FD44-6410-E511-95F8-0015C5F82D94.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/6857CC02-FD0F-E511-B72E-0002C94D5614.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/6EADBEA5-FC0F-E511-8803-0025902009BC.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/74100F81-F90F-E511-8527-F45214C748D2.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/7CCB8152-FC0F-E511-AF7B-002590D9D8C4.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/84831EBC-FE0F-E511-BAD0-0002C90B7F1A.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/86CFF5CC-FA0F-E511-B00A-20CF3027A577.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/8CFD77C5-FB0F-E511-98D1-0025907D1D6C.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/925CAF60-FB0F-E511-BBED-0CC47A4129F4.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/9A1E95E0-F80F-E511-9121-00259073E3CA.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/9E2C279C-F80F-E511-8689-B8CA3A70A410.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/AECBF79A-F70F-E511-9424-0025901FB188.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/B01F2C31-FF0F-E511-B7A8-001E68654246.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/B0EB4D61-FF0F-E511-90A3-0002C94D552A.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/B2C9AABA-FA0F-E511-B201-0002C92DB44E.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/B46B221C-FB0F-E511-B1D3-842B2B7609C0.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/B6DC0B9B-F70F-E511-A961-0002C90A3564.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/BA54C21F-FA0F-E511-9B15-00259074AE9A.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/BA7352AA-FC0F-E511-ADB2-0002C92958E8.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/BC9BA8EA-F50F-E511-95B7-A0040420FE80.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/BED24965-FB0F-E511-82A2-00259075D70C.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/C0093B9E-FC0F-E511-A11E-001EC9AE0215.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/C8EB16EC-6510-E511-8A92-A0040420FE80.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/CA9BAF97-FC0F-E511-BA80-002590D9D976.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/CAF274C6-6510-E511-A30E-00259073E3AC.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/D072F219-FB0F-E511-A5F1-002590D9D89C.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/D2191A32-FE0F-E511-922C-00304867FE1B.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/D4251F27-0510-E511-B0B3-A0040420FE80.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/D86C74C6-6510-E511-8609-0CC47A13CEAC.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/DA37F69A-FC0F-E511-BEC0-F45214C748C4.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/DC4387BF-6510-E511-BFD6-90B11CBCFFD0.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/E0B495D7-6510-E511-91DB-B083FED16468.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/E40E00D7-FD0F-E511-B98A-00259029ED1A.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/F04A4BD1-6510-E511-B831-00259029ED64.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/F07C5046-F60F-E511-B409-003048947BAA.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/F0A05126-0510-E511-A936-B8CA3A70BAC8.root',
    'root://xrootd-cms.infn.it//store/mc/RunIISpring15DR74/MinBias_TuneMBR_13TeV-pythia8/GEN-SIM-RECO/NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1/00000/F6AD3FB1-FB0F-E511-B0EA-0002C92A1024.root'
    )
)
process.TFileService = cms.Service("TFileService",
        fileName = cms.string("/afs/desy.de/user/c/connorpa/nfs/dndeta_analysis_samples/bonsai_MC_GEN-SIM-RECO_NoPU0TRawReco_magnetOff_MCRUN2_740TV0-v1.root")
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
