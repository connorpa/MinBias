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

#include "DataFormats/Provenance/interface/Timestamp.h"
// EVENT ID
struct MyEvtId
{
    UInt_t      Run,
                Evt,
                LumiBlock;
    edm::TimeValue_t Time;
    Bool_t      IsData;
    UInt_t      ExpType;
    Int_t       Bunch,
                Orbit;
    Float_t     IstLumi,
                IstLumiErr,
                IstLumiPerBX;   
};

struct MyRecoVertices
{
    vector<Double_t> * x     ,
                     * y     ,
                     * z     ,
                     * xError,
                     * yError,
                     * zError,
                     * chi2  ,
                     * ndof  ;
    vector<Bool_t  > * isFake ,
                     * isValid;

    MyRecoVertices ()
        :   x      (0x0)
        ,   y      (0x0)
        ,   z      (0x0)
        ,   xError (0x0)
        ,   yError (0x0)
        ,   zError (0x0)
        ,   chi2   (0x0)
        ,   ndof   (0x0)
        ,   isFake (0x0)
        ,   isValid(0x0)
    {}
};

struct MyRecoTracks
{
    vector<Double_t> * px,
                     * py,
                     * pz;
    vector<Int_t> * charge;
    MyRecoTracks ()
    :   px    (0x0)
    ,   py    (0x0)
    ,   pz    (0x0)
    ,   charge(0x0)
    {}
};
