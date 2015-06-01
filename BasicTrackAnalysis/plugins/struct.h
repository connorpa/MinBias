#include <vector>
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
    MyGenVertices ()
        :   x(0x0)
        ,   y(0x0)
        ,   z(0x0)
    {}
};

struct MyRecoVertices : public MyGenVertices
{
    std::vector<Double_t> * xError  ,
                          * yError  ,
                          * zError  ,
                          * chi2    ,
                          * ndof    ;
    std::vector<Bool_t  > * isFake ,
                          * isValid;

    MyRecoVertices ()
        :   MyGenVertices()
        ,   xError  (0x0)
        ,   yError  (0x0)
        ,   zError  (0x0)
        ,   chi2    (0x0)
        ,   ndof    (0x0)
        ,   isFake  (0x0)
        ,   isValid (0x0)
    {}
};

struct MyGenTracks
{
    std::vector<Double_t> * energy,
                          * pt ,
                          * eta,
                          * phi;
    std::vector<Int_t> * charge,
                       * status,
                       * pdgId;
    MyGenTracks ()
        :   energy(0x0)
        ,   pt    (0x0)
        ,   eta   (0x0)
        ,   phi   (0x0)
        ,   charge(0x0)
        ,   pdgId (0x0)
    {}
};

struct MyRecoTracks : public MyGenTracks
{
    std::vector<Double_t> * ptError ,
                          * etaError,
                          * phiError,
                          * dxy     ,
                          * dxyError,
                          * dz      ,
                          * dzError ,
                          * chi2    ;
    std::vector<Int_t> * ndof;
    MyRecoTracks ()
        :   MyGenTracks()
        ,   ptError (0x0)
        ,   etaError(0x0)
        ,   phiError(0x0)
        ,   dxy     (0x0)
        ,   dxyError(0x0)
        ,   dz      (0x0)
        ,   dzError (0x0)
        ,   chi2    (0x0)
        ,   ndof    (0x0)
    {}
};

struct MyRecHit
{
    std::vector<Float_t> * energy;
    
    MyRecHit ()
        :   energy (0x0)
    {}
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
};
