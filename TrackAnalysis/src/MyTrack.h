#ifndef __MyTrack_H__
#define __MyTrack_H__

#include "TLorentzVector.h"

class MyTrack : public TVector3 {
  
 public :
  MyTrack();
  virtual ~MyTrack();

  virtual void Reset();
  virtual void Print();
  
  Double_t charge;
  
 private:
  
  ClassDef (MyTrack,1)
};

#endif


