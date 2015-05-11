// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME eventdict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "./MyEvtId.h"
#include "./MyPart.h"
#include "./MyGenPart.h"
#include "./MyTrack.h"
#include "./MyVertex.h"
#include "./MySimVertex.h"
#include "./MyBeamSpot.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_MyPart(void *p = 0);
   static void *newArray_MyPart(Long_t size, void *p);
   static void delete_MyPart(void *p);
   static void deleteArray_MyPart(void *p);
   static void destruct_MyPart(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MyPart*)
   {
      ::MyPart *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::MyPart >(0);
      static ::ROOT::TGenericClassInfo 
         instance("MyPart", ::MyPart::Class_Version(), "MyPart.h", 6,
                  typeid(::MyPart), DefineBehavior(ptr, ptr),
                  &::MyPart::Dictionary, isa_proxy, 4,
                  sizeof(::MyPart) );
      instance.SetNew(&new_MyPart);
      instance.SetNewArray(&newArray_MyPart);
      instance.SetDelete(&delete_MyPart);
      instance.SetDeleteArray(&deleteArray_MyPart);
      instance.SetDestructor(&destruct_MyPart);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MyPart*)
   {
      return GenerateInitInstanceLocal((::MyPart*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::MyPart*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_MyEvtId(void *p = 0);
   static void *newArray_MyEvtId(Long_t size, void *p);
   static void delete_MyEvtId(void *p);
   static void deleteArray_MyEvtId(void *p);
   static void destruct_MyEvtId(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MyEvtId*)
   {
      ::MyEvtId *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::MyEvtId >(0);
      static ::ROOT::TGenericClassInfo 
         instance("MyEvtId", ::MyEvtId::Class_Version(), "MyEvtId.h", 8,
                  typeid(::MyEvtId), DefineBehavior(ptr, ptr),
                  &::MyEvtId::Dictionary, isa_proxy, 4,
                  sizeof(::MyEvtId) );
      instance.SetNew(&new_MyEvtId);
      instance.SetNewArray(&newArray_MyEvtId);
      instance.SetDelete(&delete_MyEvtId);
      instance.SetDeleteArray(&deleteArray_MyEvtId);
      instance.SetDestructor(&destruct_MyEvtId);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MyEvtId*)
   {
      return GenerateInitInstanceLocal((::MyEvtId*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::MyEvtId*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_MyGenPart(void *p = 0);
   static void *newArray_MyGenPart(Long_t size, void *p);
   static void delete_MyGenPart(void *p);
   static void deleteArray_MyGenPart(void *p);
   static void destruct_MyGenPart(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MyGenPart*)
   {
      ::MyGenPart *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::MyGenPart >(0);
      static ::ROOT::TGenericClassInfo 
         instance("MyGenPart", ::MyGenPart::Class_Version(), "MyGenPart.h", 6,
                  typeid(::MyGenPart), DefineBehavior(ptr, ptr),
                  &::MyGenPart::Dictionary, isa_proxy, 4,
                  sizeof(::MyGenPart) );
      instance.SetNew(&new_MyGenPart);
      instance.SetNewArray(&newArray_MyGenPart);
      instance.SetDelete(&delete_MyGenPart);
      instance.SetDeleteArray(&deleteArray_MyGenPart);
      instance.SetDestructor(&destruct_MyGenPart);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MyGenPart*)
   {
      return GenerateInitInstanceLocal((::MyGenPart*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::MyGenPart*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_MyTrack(void *p = 0);
   static void *newArray_MyTrack(Long_t size, void *p);
   static void delete_MyTrack(void *p);
   static void deleteArray_MyTrack(void *p);
   static void destruct_MyTrack(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MyTrack*)
   {
      ::MyTrack *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::MyTrack >(0);
      static ::ROOT::TGenericClassInfo 
         instance("MyTrack", ::MyTrack::Class_Version(), "MyTrack.h", 6,
                  typeid(::MyTrack), DefineBehavior(ptr, ptr),
                  &::MyTrack::Dictionary, isa_proxy, 4,
                  sizeof(::MyTrack) );
      instance.SetNew(&new_MyTrack);
      instance.SetNewArray(&newArray_MyTrack);
      instance.SetDelete(&delete_MyTrack);
      instance.SetDeleteArray(&deleteArray_MyTrack);
      instance.SetDestructor(&destruct_MyTrack);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MyTrack*)
   {
      return GenerateInitInstanceLocal((::MyTrack*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::MyTrack*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_MyBeamSpot(void *p = 0);
   static void *newArray_MyBeamSpot(Long_t size, void *p);
   static void delete_MyBeamSpot(void *p);
   static void deleteArray_MyBeamSpot(void *p);
   static void destruct_MyBeamSpot(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MyBeamSpot*)
   {
      ::MyBeamSpot *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::MyBeamSpot >(0);
      static ::ROOT::TGenericClassInfo 
         instance("MyBeamSpot", ::MyBeamSpot::Class_Version(), "MyBeamSpot.h", 6,
                  typeid(::MyBeamSpot), DefineBehavior(ptr, ptr),
                  &::MyBeamSpot::Dictionary, isa_proxy, 4,
                  sizeof(::MyBeamSpot) );
      instance.SetNew(&new_MyBeamSpot);
      instance.SetNewArray(&newArray_MyBeamSpot);
      instance.SetDelete(&delete_MyBeamSpot);
      instance.SetDeleteArray(&deleteArray_MyBeamSpot);
      instance.SetDestructor(&destruct_MyBeamSpot);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MyBeamSpot*)
   {
      return GenerateInitInstanceLocal((::MyBeamSpot*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::MyBeamSpot*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_MyVertex(void *p = 0);
   static void *newArray_MyVertex(Long_t size, void *p);
   static void delete_MyVertex(void *p);
   static void deleteArray_MyVertex(void *p);
   static void destruct_MyVertex(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MyVertex*)
   {
      ::MyVertex *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::MyVertex >(0);
      static ::ROOT::TGenericClassInfo 
         instance("MyVertex", ::MyVertex::Class_Version(), "MyVertex.h", 6,
                  typeid(::MyVertex), DefineBehavior(ptr, ptr),
                  &::MyVertex::Dictionary, isa_proxy, 4,
                  sizeof(::MyVertex) );
      instance.SetNew(&new_MyVertex);
      instance.SetNewArray(&newArray_MyVertex);
      instance.SetDelete(&delete_MyVertex);
      instance.SetDeleteArray(&deleteArray_MyVertex);
      instance.SetDestructor(&destruct_MyVertex);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MyVertex*)
   {
      return GenerateInitInstanceLocal((::MyVertex*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::MyVertex*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_MySimVertex(void *p = 0);
   static void *newArray_MySimVertex(Long_t size, void *p);
   static void delete_MySimVertex(void *p);
   static void deleteArray_MySimVertex(void *p);
   static void destruct_MySimVertex(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MySimVertex*)
   {
      ::MySimVertex *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::MySimVertex >(0);
      static ::ROOT::TGenericClassInfo 
         instance("MySimVertex", ::MySimVertex::Class_Version(), "MySimVertex.h", 6,
                  typeid(::MySimVertex), DefineBehavior(ptr, ptr),
                  &::MySimVertex::Dictionary, isa_proxy, 4,
                  sizeof(::MySimVertex) );
      instance.SetNew(&new_MySimVertex);
      instance.SetNewArray(&newArray_MySimVertex);
      instance.SetDelete(&delete_MySimVertex);
      instance.SetDeleteArray(&deleteArray_MySimVertex);
      instance.SetDestructor(&destruct_MySimVertex);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MySimVertex*)
   {
      return GenerateInitInstanceLocal((::MySimVertex*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::MySimVertex*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr MyPart::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MyPart::Class_Name()
{
   return "MyPart";
}

//______________________________________________________________________________
const char *MyPart::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MyPart*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MyPart::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MyPart*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MyPart::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MyPart*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MyPart::Class()
{
   if (!fgIsA) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MyPart*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr MyEvtId::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MyEvtId::Class_Name()
{
   return "MyEvtId";
}

//______________________________________________________________________________
const char *MyEvtId::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MyEvtId*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MyEvtId::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MyEvtId*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MyEvtId::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MyEvtId*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MyEvtId::Class()
{
   if (!fgIsA) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MyEvtId*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr MyGenPart::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MyGenPart::Class_Name()
{
   return "MyGenPart";
}

//______________________________________________________________________________
const char *MyGenPart::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MyGenPart*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MyGenPart::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MyGenPart*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MyGenPart::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MyGenPart*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MyGenPart::Class()
{
   if (!fgIsA) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MyGenPart*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr MyTrack::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MyTrack::Class_Name()
{
   return "MyTrack";
}

//______________________________________________________________________________
const char *MyTrack::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MyTrack*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MyTrack::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MyTrack*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MyTrack::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MyTrack*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MyTrack::Class()
{
   if (!fgIsA) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MyTrack*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr MyBeamSpot::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MyBeamSpot::Class_Name()
{
   return "MyBeamSpot";
}

//______________________________________________________________________________
const char *MyBeamSpot::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MyBeamSpot*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MyBeamSpot::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MyBeamSpot*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MyBeamSpot::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MyBeamSpot*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MyBeamSpot::Class()
{
   if (!fgIsA) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MyBeamSpot*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr MyVertex::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MyVertex::Class_Name()
{
   return "MyVertex";
}

//______________________________________________________________________________
const char *MyVertex::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MyVertex*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MyVertex::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MyVertex*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MyVertex::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MyVertex*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MyVertex::Class()
{
   if (!fgIsA) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MyVertex*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr MySimVertex::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MySimVertex::Class_Name()
{
   return "MySimVertex";
}

//______________________________________________________________________________
const char *MySimVertex::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MySimVertex*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MySimVertex::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MySimVertex*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MySimVertex::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MySimVertex*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MySimVertex::Class()
{
   if (!fgIsA) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MySimVertex*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void MyPart::Streamer(TBuffer &R__b)
{
   // Stream an object of class MyPart.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(MyPart::Class(),this);
   } else {
      R__b.WriteClassBuffer(MyPart::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_MyPart(void *p) {
      return  p ? new(p) ::MyPart : new ::MyPart;
   }
   static void *newArray_MyPart(Long_t nElements, void *p) {
      return p ? new(p) ::MyPart[nElements] : new ::MyPart[nElements];
   }
   // Wrapper around operator delete
   static void delete_MyPart(void *p) {
      delete ((::MyPart*)p);
   }
   static void deleteArray_MyPart(void *p) {
      delete [] ((::MyPart*)p);
   }
   static void destruct_MyPart(void *p) {
      typedef ::MyPart current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::MyPart

//______________________________________________________________________________
void MyEvtId::Streamer(TBuffer &R__b)
{
   // Stream an object of class MyEvtId.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(MyEvtId::Class(),this);
   } else {
      R__b.WriteClassBuffer(MyEvtId::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_MyEvtId(void *p) {
      return  p ? new(p) ::MyEvtId : new ::MyEvtId;
   }
   static void *newArray_MyEvtId(Long_t nElements, void *p) {
      return p ? new(p) ::MyEvtId[nElements] : new ::MyEvtId[nElements];
   }
   // Wrapper around operator delete
   static void delete_MyEvtId(void *p) {
      delete ((::MyEvtId*)p);
   }
   static void deleteArray_MyEvtId(void *p) {
      delete [] ((::MyEvtId*)p);
   }
   static void destruct_MyEvtId(void *p) {
      typedef ::MyEvtId current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::MyEvtId

//______________________________________________________________________________
void MyGenPart::Streamer(TBuffer &R__b)
{
   // Stream an object of class MyGenPart.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(MyGenPart::Class(),this);
   } else {
      R__b.WriteClassBuffer(MyGenPart::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_MyGenPart(void *p) {
      return  p ? new(p) ::MyGenPart : new ::MyGenPart;
   }
   static void *newArray_MyGenPart(Long_t nElements, void *p) {
      return p ? new(p) ::MyGenPart[nElements] : new ::MyGenPart[nElements];
   }
   // Wrapper around operator delete
   static void delete_MyGenPart(void *p) {
      delete ((::MyGenPart*)p);
   }
   static void deleteArray_MyGenPart(void *p) {
      delete [] ((::MyGenPart*)p);
   }
   static void destruct_MyGenPart(void *p) {
      typedef ::MyGenPart current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::MyGenPart

//______________________________________________________________________________
void MyTrack::Streamer(TBuffer &R__b)
{
   // Stream an object of class MyTrack.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(MyTrack::Class(),this);
   } else {
      R__b.WriteClassBuffer(MyTrack::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_MyTrack(void *p) {
      return  p ? new(p) ::MyTrack : new ::MyTrack;
   }
   static void *newArray_MyTrack(Long_t nElements, void *p) {
      return p ? new(p) ::MyTrack[nElements] : new ::MyTrack[nElements];
   }
   // Wrapper around operator delete
   static void delete_MyTrack(void *p) {
      delete ((::MyTrack*)p);
   }
   static void deleteArray_MyTrack(void *p) {
      delete [] ((::MyTrack*)p);
   }
   static void destruct_MyTrack(void *p) {
      typedef ::MyTrack current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::MyTrack

//______________________________________________________________________________
void MyBeamSpot::Streamer(TBuffer &R__b)
{
   // Stream an object of class MyBeamSpot.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(MyBeamSpot::Class(),this);
   } else {
      R__b.WriteClassBuffer(MyBeamSpot::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_MyBeamSpot(void *p) {
      return  p ? new(p) ::MyBeamSpot : new ::MyBeamSpot;
   }
   static void *newArray_MyBeamSpot(Long_t nElements, void *p) {
      return p ? new(p) ::MyBeamSpot[nElements] : new ::MyBeamSpot[nElements];
   }
   // Wrapper around operator delete
   static void delete_MyBeamSpot(void *p) {
      delete ((::MyBeamSpot*)p);
   }
   static void deleteArray_MyBeamSpot(void *p) {
      delete [] ((::MyBeamSpot*)p);
   }
   static void destruct_MyBeamSpot(void *p) {
      typedef ::MyBeamSpot current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::MyBeamSpot

//______________________________________________________________________________
void MyVertex::Streamer(TBuffer &R__b)
{
   // Stream an object of class MyVertex.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(MyVertex::Class(),this);
   } else {
      R__b.WriteClassBuffer(MyVertex::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_MyVertex(void *p) {
      return  p ? new(p) ::MyVertex : new ::MyVertex;
   }
   static void *newArray_MyVertex(Long_t nElements, void *p) {
      return p ? new(p) ::MyVertex[nElements] : new ::MyVertex[nElements];
   }
   // Wrapper around operator delete
   static void delete_MyVertex(void *p) {
      delete ((::MyVertex*)p);
   }
   static void deleteArray_MyVertex(void *p) {
      delete [] ((::MyVertex*)p);
   }
   static void destruct_MyVertex(void *p) {
      typedef ::MyVertex current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::MyVertex

//______________________________________________________________________________
void MySimVertex::Streamer(TBuffer &R__b)
{
   // Stream an object of class MySimVertex.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(MySimVertex::Class(),this);
   } else {
      R__b.WriteClassBuffer(MySimVertex::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_MySimVertex(void *p) {
      return  p ? new(p) ::MySimVertex : new ::MySimVertex;
   }
   static void *newArray_MySimVertex(Long_t nElements, void *p) {
      return p ? new(p) ::MySimVertex[nElements] : new ::MySimVertex[nElements];
   }
   // Wrapper around operator delete
   static void delete_MySimVertex(void *p) {
      delete ((::MySimVertex*)p);
   }
   static void deleteArray_MySimVertex(void *p) {
      delete [] ((::MySimVertex*)p);
   }
   static void destruct_MySimVertex(void *p) {
      typedef ::MySimVertex current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::MySimVertex

namespace ROOT {
   static TClass *vectorlEMyVertexgR_Dictionary();
   static void vectorlEMyVertexgR_TClassManip(TClass*);
   static void *new_vectorlEMyVertexgR(void *p = 0);
   static void *newArray_vectorlEMyVertexgR(Long_t size, void *p);
   static void delete_vectorlEMyVertexgR(void *p);
   static void deleteArray_vectorlEMyVertexgR(void *p);
   static void destruct_vectorlEMyVertexgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<MyVertex>*)
   {
      vector<MyVertex> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<MyVertex>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<MyVertex>", -2, "vector", 214,
                  typeid(vector<MyVertex>), DefineBehavior(ptr, ptr),
                  &vectorlEMyVertexgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<MyVertex>) );
      instance.SetNew(&new_vectorlEMyVertexgR);
      instance.SetNewArray(&newArray_vectorlEMyVertexgR);
      instance.SetDelete(&delete_vectorlEMyVertexgR);
      instance.SetDeleteArray(&deleteArray_vectorlEMyVertexgR);
      instance.SetDestructor(&destruct_vectorlEMyVertexgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<MyVertex> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<MyVertex>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEMyVertexgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<MyVertex>*)0x0)->GetClass();
      vectorlEMyVertexgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEMyVertexgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEMyVertexgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<MyVertex> : new vector<MyVertex>;
   }
   static void *newArray_vectorlEMyVertexgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<MyVertex>[nElements] : new vector<MyVertex>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEMyVertexgR(void *p) {
      delete ((vector<MyVertex>*)p);
   }
   static void deleteArray_vectorlEMyVertexgR(void *p) {
      delete [] ((vector<MyVertex>*)p);
   }
   static void destruct_vectorlEMyVertexgR(void *p) {
      typedef vector<MyVertex> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<MyVertex>

namespace ROOT {
   static TClass *vectorlEMyTrackgR_Dictionary();
   static void vectorlEMyTrackgR_TClassManip(TClass*);
   static void *new_vectorlEMyTrackgR(void *p = 0);
   static void *newArray_vectorlEMyTrackgR(Long_t size, void *p);
   static void delete_vectorlEMyTrackgR(void *p);
   static void deleteArray_vectorlEMyTrackgR(void *p);
   static void destruct_vectorlEMyTrackgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<MyTrack>*)
   {
      vector<MyTrack> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<MyTrack>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<MyTrack>", -2, "vector", 214,
                  typeid(vector<MyTrack>), DefineBehavior(ptr, ptr),
                  &vectorlEMyTrackgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<MyTrack>) );
      instance.SetNew(&new_vectorlEMyTrackgR);
      instance.SetNewArray(&newArray_vectorlEMyTrackgR);
      instance.SetDelete(&delete_vectorlEMyTrackgR);
      instance.SetDeleteArray(&deleteArray_vectorlEMyTrackgR);
      instance.SetDestructor(&destruct_vectorlEMyTrackgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<MyTrack> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<MyTrack>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEMyTrackgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<MyTrack>*)0x0)->GetClass();
      vectorlEMyTrackgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEMyTrackgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEMyTrackgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<MyTrack> : new vector<MyTrack>;
   }
   static void *newArray_vectorlEMyTrackgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<MyTrack>[nElements] : new vector<MyTrack>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEMyTrackgR(void *p) {
      delete ((vector<MyTrack>*)p);
   }
   static void deleteArray_vectorlEMyTrackgR(void *p) {
      delete [] ((vector<MyTrack>*)p);
   }
   static void destruct_vectorlEMyTrackgR(void *p) {
      typedef vector<MyTrack> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<MyTrack>

namespace ROOT {
   static TClass *vectorlEMyGenPartgR_Dictionary();
   static void vectorlEMyGenPartgR_TClassManip(TClass*);
   static void *new_vectorlEMyGenPartgR(void *p = 0);
   static void *newArray_vectorlEMyGenPartgR(Long_t size, void *p);
   static void delete_vectorlEMyGenPartgR(void *p);
   static void deleteArray_vectorlEMyGenPartgR(void *p);
   static void destruct_vectorlEMyGenPartgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<MyGenPart>*)
   {
      vector<MyGenPart> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<MyGenPart>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<MyGenPart>", -2, "vector", 214,
                  typeid(vector<MyGenPart>), DefineBehavior(ptr, ptr),
                  &vectorlEMyGenPartgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<MyGenPart>) );
      instance.SetNew(&new_vectorlEMyGenPartgR);
      instance.SetNewArray(&newArray_vectorlEMyGenPartgR);
      instance.SetDelete(&delete_vectorlEMyGenPartgR);
      instance.SetDeleteArray(&deleteArray_vectorlEMyGenPartgR);
      instance.SetDestructor(&destruct_vectorlEMyGenPartgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<MyGenPart> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<MyGenPart>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEMyGenPartgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<MyGenPart>*)0x0)->GetClass();
      vectorlEMyGenPartgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEMyGenPartgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEMyGenPartgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<MyGenPart> : new vector<MyGenPart>;
   }
   static void *newArray_vectorlEMyGenPartgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<MyGenPart>[nElements] : new vector<MyGenPart>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEMyGenPartgR(void *p) {
      delete ((vector<MyGenPart>*)p);
   }
   static void deleteArray_vectorlEMyGenPartgR(void *p) {
      delete [] ((vector<MyGenPart>*)p);
   }
   static void destruct_vectorlEMyGenPartgR(void *p) {
      typedef vector<MyGenPart> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<MyGenPart>

namespace {
  void TriggerDictionaryInitialization_eventdict_Impl() {
    static const char* headers[] = {
"./MyEvtId.h",
"./MyPart.h",
"./MyGenPart.h",
"./MyTrack.h",
"./MyVertex.h",
"./MySimVertex.h",
"./MyBeamSpot.h",
0
    };
    static const char* includePaths[] = {
"/afs/desy.de/user/c/connorpa/CMSSW/CMSSW_7_4_0/src/MinBias/TrackAnalysis/src/../../../",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/lcg/root/6.02.00-odfocd/include",
"/afs/desy.de/user/c/connorpa/CMSSW/CMSSW_7_4_0/src/MinBias/TrackAnalysis/src/",
0
    };
    static const char* fwdDeclCode = 
R"DICTFWDDCLS(
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$./MyPart.h")))  MyPart;
class __attribute__((annotate("$clingAutoload$./MyEvtId.h")))  MyEvtId;
class __attribute__((annotate("$clingAutoload$./MyGenPart.h")))  MyGenPart;
namespace std{template <typename _Tp> class __attribute__((annotate("$clingAutoload$string")))  allocator;
}
class __attribute__((annotate("$clingAutoload$./MyTrack.h")))  MyTrack;
class __attribute__((annotate("$clingAutoload$./MyBeamSpot.h")))  MyBeamSpot;
class __attribute__((annotate("$clingAutoload$./MyVertex.h")))  MyVertex;
class __attribute__((annotate("$clingAutoload$./MySimVertex.h")))  MySimVertex;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "./MyEvtId.h"
#include "./MyPart.h"
#include "./MyGenPart.h"
#include "./MyTrack.h"
#include "./MyVertex.h"
#include "./MySimVertex.h"
#include "./MyBeamSpot.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"MyBeamSpot", payloadCode, "@",
"MyEvtId", payloadCode, "@",
"MyGenPart", payloadCode, "@",
"MyPart", payloadCode, "@",
"MySimVertex", payloadCode, "@",
"MyTrack", payloadCode, "@",
"MyVertex", payloadCode, "@",
"vector<MyGenPart>", payloadCode, "@",
"vector<MyTrack>", payloadCode, "@",
"vector<MyVertex>", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("eventdict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_eventdict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_eventdict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_eventdict() {
  TriggerDictionaryInitialization_eventdict_Impl();
}
