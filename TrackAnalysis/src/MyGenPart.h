#ifndef __MyGenPart_H__
#define __MyGenPart_H__

#include "MyPart.h"

class MyGenPart : public MyPart {

    public :
        MyGenPart();
        virtual ~MyGenPart();

        void Print();

        Int_t pdgId,status;

    private:

        ClassDef (MyGenPart,1)
};

#endif

