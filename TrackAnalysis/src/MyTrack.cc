#include "./MyTrack.h"
#include <iostream>
using namespace std;

ClassImp(MyTrack)

MyTrack::MyTrack(){
    this->Reset();
}

//    MyTrack::MyTrack(Double_t x, Double_t y, Double_t z)
//:   TVector3(x,y,z)
//{}

MyTrack::~MyTrack(){}

void MyTrack::Reset(){
    this->SetPtEtaPhi(0,0,0);
    charge = 0;
}

void MyTrack::Print(){
    cout << "px     : " << this->Px()   << endl;
    cout << "py     : " << this->Py()   << endl;
    cout << "pz     : " << this->Pz()   << endl;
    cout << "pt     : " << this->Pt()   << endl;
    if(this->Pt()>0)  cout << "eta    : " << this->Eta()  << endl;
    cout << "phi    : " << this->Phi()  << endl;
    cout << "charge : " << this->charge << endl;
}



