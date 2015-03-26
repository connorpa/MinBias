#ifndef __MyTrack_H__
#define __MyTrack_H__

#include "TVector3.h"

class MyTrack : public TVector3 {

    public :
        MyTrack();
        //MyTrack(Double_t x, Double_t y, Double_t z);
        virtual ~MyTrack();

        virtual void Reset();
        virtual void Print();

        Double_t charge;

    private:

        ClassDef (MyTrack,1)
};

#endif


