import FWCore.ParameterSet.Config as cms

process = cms.Process("TreeProducer")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-42) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/005C8F6F-1A0D-E511-A77D-02163E0142BC.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/005C8F6F-1A0D-E511-A77D-02163E0142BC.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/02924E03-3A0D-E511-82EC-02163E01283A.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/04A0CC3F-1A0D-E511-9DE4-02163E014711.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/04BBDD9D-170D-E511-900F-02163E01446B.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/064ADBFB-390D-E511-B821-02163E0138F6.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/0CCF7303-140D-E511-A982-02163E011BB0.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/0E2073E4-170D-E511-B506-02163E0144F5.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/0E91829B-170D-E511-A867-02163E011B86.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/10A1621B-0F0D-E511-AB9D-02163E01446B.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/123204AA-0F0D-E511-8D0E-02163E01369F.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/126FCC85-100D-E511-BDCD-02163E011BAC.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/127E11D8-190D-E511-8454-02163E0143CF.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/16D7D55A-250D-E511-9855-02163E0138F6.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/1C115493-100D-E511-821D-02163E0134D5.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/1C6C7389-1D0D-E511-8D78-02163E01257B.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/1E44709C-100D-E511-9087-02163E011E08.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/1E7D7CC1-0A0D-E511-897B-02163E0133BE.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/1EB0AED1-170D-E511-893D-02163E01463F.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/2025E6FA-170D-E511-8410-02163E0145CC.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/22CD974E-180D-E511-8544-02163E01456E.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/2489E398-0F0D-E511-8183-02163E014409.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/2613E9CA-0A0D-E511-9D9D-02163E0136A3.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/266D2B11-140D-E511-9E79-02163E014569.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/2698FCC3-190D-E511-84ED-02163E0142BB.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/2A1EC7F8-170D-E511-98C1-02163E012462.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/3082CF1B-140D-E511-AE5E-02163E013949.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/32DAE4D8-0A0D-E511-91E8-02163E014790.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/342EF78B-170D-E511-BC0D-02163E0142F8.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/362B31D8-190D-E511-8846-02163E01440B.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/3A024FDA-0A0D-E511-9D73-02163E0142EA.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/3E1776FA-130D-E511-9A8D-02163E0143D5.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/4019E36A-140D-E511-9436-02163E01438B.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/404B85BD-0B0D-E511-B394-02163E01424A.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/407C9A28-140D-E511-8B1D-02163E014472.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/44C999A9-100D-E511-9305-02163E012355.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/48E5D936-0F0D-E511-A0F8-02163E0126EB.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/4EA9FCC0-100D-E511-86E4-02163E011BE1.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/503BB75C-0D0D-E511-9AF0-02163E01369F.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/52C66698-170D-E511-8087-02163E0136A3.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/546362D7-100D-E511-B7F5-02163E012325.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/5803DFA2-100D-E511-9714-02163E012925.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/5C367D41-1A0D-E511-8E8C-02163E01440B.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/5C5C1F2A-140D-E511-B0C3-02163E0136B6.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/5E4F37F0-130D-E511-B10F-02163E013952.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/5EE2C79E-0F0D-E511-B273-02163E012133.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/62B4E69B-130D-E511-894A-02163E01417A.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/64F312E8-180D-E511-9144-02163E011EB6.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/64FD36B3-0B0D-E511-9F3C-02163E0133BE.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/6C285DC3-100D-E511-823B-02163E01441E.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/6EF3FAD6-0A0D-E511-9445-02163E013644.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/72ADDA02-140D-E511-BE79-02163E011D3A.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/769208D7-0A0D-E511-A632-02163E0145B1.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/7C2C1BBA-0B0D-E511-AD94-02163E0136A3.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/7E25D301-0C0D-E511-A51B-02163E01438B.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/7EDAC114-140D-E511-B586-02163E01475C.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/848B80A5-170D-E511-9BFE-02163E0145E3.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/868601DA-190D-E511-91CD-02163E0139A3.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/86FFEAFA-130D-E511-A524-02163E014204.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/8E317B93-100D-E511-90B3-02163E014204.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/8EC02B6A-090D-E511-8F27-02163E0121DA.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/90D5FF79-130D-E511-AC72-02163E0138F6.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/90E0147F-160D-E511-9696-02163E0145AE.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/945452B8-0E0D-E511-9599-02163E014565.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/949C47E8-0A0D-E511-816C-02163E01441E.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/9855E6D7-0A0D-E511-BE47-02163E0120CB.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/9CD1AAA1-100D-E511-9379-02163E014204.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/9EF61809-140D-E511-B0D7-02163E012355.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/A07D83FC-130D-E511-892F-02163E014672.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/A252D90E-110D-E511-A517-02163E014613.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/A41C82FB-130D-E511-883C-02163E0142EA.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/A46E2596-100D-E511-AE7A-02163E01295D.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/A4A5C5D7-100D-E511-A5FD-02163E0138F3.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/A6F75767-090D-E511-93BB-02163E01410A.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/AEB41082-160D-E511-A8C3-02163E014218.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/B021B9B1-0B0D-E511-8393-02163E0119CE.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/B05DA918-0F0D-E511-A3A9-02163E012377.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/B09696D3-0F0D-E511-86D0-02163E01467B.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/B80E53BF-0A0D-E511-A000-02163E0145B1.root',
        #'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/B87B1992-040D-E511-B975-02163E0134F5.root',# bad
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/BA8C5C48-1B0D-E511-A35E-02163E013454.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/BCF05DA5-100D-E511-A370-02163E0121C5.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/C041F4D2-100D-E511-83D1-02163E0133BE.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/C0C7B006-180D-E511-B1FF-02163E0143AB.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/C215215C-250D-E511-9F27-02163E011B86.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/C224387C-200D-E511-801C-02163E013727.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/C22AA4B5-0B0D-E511-B2FF-02163E01441E.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/C477480A-140D-E511-B421-02163E0146F6.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/C4C9789F-100D-E511-9AD0-02163E014790.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/C89FA8FB-130D-E511-85AE-02163E013768.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/CE82B194-100D-E511-95EA-02163E0133BE.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/D04CD2F9-130D-E511-B157-02163E014147.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/D05DE606-140D-E511-9716-02163E014384.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/D0610CD6-100D-E511-87C7-02163E013644.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/D455B288-100D-E511-B440-02163E013949.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/D4C78170-0F0D-E511-9349-02163E0138AC.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/D6DDA7E5-0B0D-E511-9E48-02163E011BE1.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/D81EAD93-100D-E511-A3D0-02163E0143FB.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/D84524A5-100D-E511-8203-02163E012377.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/DA43257E-130D-E511-826E-02163E013952.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/DC2A38B7-0B0D-E511-9BC7-02163E014120.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/E2008FAC-100D-E511-8EA0-02163E013729.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/E2E7E6AA-0F0D-E511-B03B-02163E0146AC.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/E2FC15D0-0A0D-E511-B622-02163E0146A9.root',
        #'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/E6A6BC65-070D-E511-8DCA-02163E0133BE.root',# bad
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/E6C16CD2-100D-E511-A437-02163E01453F.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/EA3615A0-170D-E511-8A8B-02163E0120CB.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/EAA17BFA-130D-E511-84A8-02163E011EB6.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/EC4552F1-130D-E511-891C-02163E0138F6.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/EE0E81F7-130D-E511-8E65-02163E012951.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/F24FB4D7-100D-E511-9DB4-02163E013684.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/F45CA393-100D-E511-A290-02163E01446B.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/F6970ABB-170D-E511-B0A0-02163E011D25.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/F6D82CE7-140D-E511-84E4-02163E013671.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/FA39FDA7-0F0D-E511-A9FC-02163E0143E9.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/FA73610E-0B0D-E511-B92D-02163E012462.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/FAFAE7FC-130D-E511-8061-02163E013729.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/FC8E0DBA-090D-E511-8ECF-02163E0119DC.root',
        'root://xrootd-cms.infn.it//store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/324/00000/FE6B8B97-100D-E511-B2E4-02163E012A7A.root'

    )
)
process.TFileService = cms.Service("TFileService",
        fileName = cms.string("/nfs/dust/cms/user/connorpa/dndeta_analysis_samples/bonsai_data_Ferenc_8_Jun_2015.root")
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
    , StoreGenParticles    = cms.bool(False) , GenParticles    = cms.InputTag("genParticles"          , ""             , "HLT" )
)


process.p = cms.Path(process.minbiasdata)
