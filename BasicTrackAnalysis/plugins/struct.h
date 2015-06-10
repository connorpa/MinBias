#include <vector>
#include <string>
#include <Rtypes.h>

// BEAM SPOT
struct MyBeamSpot
{
    Double_t positionX,
             positionY,
             positionZ,
             x0Error,
             y0Error,
             z0Error,
             sigmaZ,
             dxdz,
             dydz,
             sigmaZ0Error,
             dxdzError,
             dydzError,
             BeamWidthX,
             BeamWidthY,
             BeamWidthXError,
             BeamWidthYError;
};

// EVENT ID
struct MyEvtId
{
    UInt_t      Run,
                Evt,
                LumiBlock;
    ULong64_t    Time;
    //edm::TimeValue_t    Time;
    Bool_t      IsData;
    UInt_t      ExpType;
    Int_t       Bunch,
                Orbit;
    Float_t     IstLumi,
                IstLumiErr,
                IstLumiPerBX;   
};

struct MyGenVertices
{
    std::vector<Double_t> * x,
                          * y,
                          * z;

    // TODO: include iterator or ref (or anything of the kind) to the tracks

    MyGenVertices ()
        :   x      (0x0)
        ,   y      (0x0)
        ,   z      (0x0)
    {}

    void clear ()
    {
        x      ->clear();
        y      ->clear();
        z      ->clear();
    }
};

struct MyRecoVertices : public MyGenVertices
{
    std::vector<Double_t> * xError  ,
                          * yError  ,
                          * zError  ,
                          * chi2    ,
                          * ndof    ;
    std::vector<Bool_t> * isFake ,
                        * isValid;
    std::vector<UInt_t> * nTracks;

    MyRecoVertices ()
        :   MyGenVertices()
        ,   xError  (0x0)
        ,   yError  (0x0)
        ,   zError  (0x0)
        ,   chi2    (0x0)
        ,   ndof    (0x0)
        ,   isFake  (0x0)
        ,   isValid (0x0)
        ,   nTracks (0x0)
    {}

    void clear ()
    {
        MyGenVertices::clear();
        xError ->clear();
        yError ->clear();
        zError ->clear();
        chi2   ->clear();
        ndof   ->clear();
        isFake ->clear();
        isValid->clear();
        nTracks->clear();
    }
};

struct MyTrackBase
{
    std::vector<Double_t> * pt ,
                          * eta,
                          * phi;
    std::vector<Int_t> * charge;
    MyTrackBase ()
        :   pt    (0x0)
        ,   eta   (0x0)
        ,   phi   (0x0)
        ,   charge(0x0)
    {}

    void clear ()
    {
        pt    ->clear();
        eta   ->clear();
        phi   ->clear();
        charge->clear();
    }
};

struct MyGenTracks : public MyTrackBase
{
    std::vector<Double_t> * energy;
    std::vector<Int_t> * status,
                       * pdgId;
    MyGenTracks ()
        :   MyTrackBase()
        ,   energy(0x0)
        ,   status(0x0)
        ,   pdgId (0x0)
    {}

    void clear()
    {
        MyTrackBase::clear();
        energy->clear();
        status->clear();
        pdgId ->clear();
    }
};

struct MyRecoTracks : public MyTrackBase
{
    std::vector<Double_t> * ptError ,
                          * etaError,
                          * phiError,
                          * dxy     ,
                          * dxyError,
                          * dz      ,
                          * dzError ,
                          * dsz     ,
                          * dszError,
                          * chi2    ,
                          * ndof    ,
                          * vx      ,
                          * vy      ,
                          * vz      ;
    std::vector<Int_t> * quality          ,
                       * numberOfValidHits,
                       * numberOfLostHits ;

    MyRecoTracks ()
        :   MyTrackBase()
        ,   ptError          (0x0)
        ,   etaError         (0x0)
        ,   phiError         (0x0)
        ,   dxy              (0x0)
        ,   dxyError         (0x0)
        ,   dz               (0x0)
        ,   dzError          (0x0)
        ,   dsz              (0x0)
        ,   dszError         (0x0)
        ,   chi2             (0x0)
        ,   ndof             (0x0)
        ,   vx               (0x0)
        ,   vy               (0x0)
        ,   vz               (0x0)
        ,   quality          (0x0)
        ,   numberOfValidHits(0x0)
        ,   numberOfLostHits (0x0)
    {}

    void clear()
    {
        MyTrackBase::clear();
        ptError          ->clear();
        etaError         ->clear();
        phiError         ->clear();
        dxy              ->clear();
        dxyError         ->clear();
        dz               ->clear();
        dzError          ->clear();
        dsz              ->clear();
        dszError         ->clear();
        chi2             ->clear();
        ndof             ->clear();
        vx               ->clear();
        vy               ->clear();
        vz               ->clear();
        quality          ->clear();
        numberOfValidHits->clear();
        numberOfLostHits ->clear();
    }
};

struct MyRecHit
{
    std::vector<Float_t> * energy;
    
    MyRecHit ()
        :   energy (0x0)
    {}

    void clear ()
    {
        energy->clear();
    }
};

struct MyCaloTower
{
    std::vector<Double_t> * energy,
                          * energyInHE,
                          * energyInHB,
                          * energyInHO,
                          * energyInHF,
                          * emEnergy,
                          * hadEnergy,
                          * eta,
                          * phi;

    MyCaloTower ()
        :   energy      (0x0)
        ,   energyInHE  (0x0)
        ,   energyInHB  (0x0)
        ,   energyInHO  (0x0)
        ,   energyInHF  (0x0)
        ,   emEnergy    (0x0)
        ,   hadEnergy   (0x0)
        ,   eta         (0x0)
        ,   phi         (0x0)
    {}

    void clear ()
    {
        energy    ->clear();
        energyInHE->clear();
        energyInHB->clear();
        energyInHO->clear();
        energyInHF->clear();
        emEnergy  ->clear();
        hadEnergy ->clear();
        eta       ->clear();
        phi       ->clear();
    }
};

struct MyTriggerBase
{
    std::vector<std::string> * name;
    std::vector<bool> * decision;

    MyTriggerBase ()
        :   name    (0x0)
        ,   decision(0x0)
    {}

    void clear ()
    {
        name    ->clear();
        decision->clear();
    }
};

struct MyL1T : public MyTriggerBase
{
    std::vector<int> * bit;

    MyL1T ()
        :   MyTriggerBase()
        ,   bit(0x0)
    {}
    
    void clear ()
    {
        MyTriggerBase::clear();
        bit->clear();
    }
};

struct MyHLT : public MyTriggerBase
{
    std::vector<unsigned int> * index;
    std::vector<int> * HLTprescale, // ??
                     * L1prescale;  // ??

    MyHLT ()
        :   MyTriggerBase()
        ,   index      (0x0)
        ,   HLTprescale(0x0)
        ,   L1prescale (0x0)
    {}

    void clear ()
    {
        MyTriggerBase::clear();
        index      ->clear();
        HLTprescale->clear();
        L1prescale ->clear();
    }
};
