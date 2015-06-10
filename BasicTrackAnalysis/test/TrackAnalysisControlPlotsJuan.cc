/**************************************************************************************/
/* Author: Patrick L.S. Connor (DESY CMS group)                                       */
/* Date: May 2015                                                                     */
/* Purpose: read and extract histograms from the ntuples given by the TreeProducer.cc */
/* Note: this code was started from the TTree::MakeClass()                            */
/**************************************************************************************/
#define TrackAnalysis_cxx
#include "TrackAnalysis.h"
#include <cstdlib>
#include <TApplication.h>
#include <TH2.h>
#include <TProfile.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>

#define PI TMath::Pi()

void TrackAnalysis::Loop(Long64_t maxentries)
{
    if (fChain == 0x0) return;

    /********************** CUTOFFS & CONSTANTS ***************************/

    const double minpt  = 0.1, // GeV
                 maxtracketa = 2.4, // no unit
                 minRHeta = 3,
                 maxRHeta = 5;
    const unsigned short int NETABIN = 4, // 4 eta bins of width 0.6 
                             NKIN = 17, 
                             NDIR = 6; 
    const double ETABINWIDTH = maxtracketa/((double) NETABIN);

    /************************* Global variables  *****************************/
    
    //For normalization
    double nselevents = 0.; //Number of selected events
    double NofVertexEvents = 0;
    /************************* BOOKING HISTOGRAMS *****************************/

    cout << "Booking histograms..." << endl;

    // those variables are defined to take advantage of the maps
    // i.e. the map can be looped only over a small section of
    // we define constant proto histograms, whose purpose is only to be cloned, to ensure to have always the same structure
    //TH1D * h = new TH1D (name, title, nbins, xlow, xup);
    const TH1D * proto_tracks[NKIN] = { new const TH1D ("pt" , "transverse momentum;p_T/GeV;#entries",   50,     0,   5),
                                        new const TH1D ("eta", "pseudorapidity;#eta;#entries",   50,  -2.5,  2.5),
                                        new const TH1D ("phi", "azimuthal angle;#phi;#entries",   20,   -PI,   PI),
                                        new const TH1D ("M"  , "multiplicity;M;#enitres",  500,     0,  500),
                                        new const TH1D ("M_withcuts"  , "multiplicity with track quality cuts;M;#enitres",  300,     0,  300),
                                        new const TH1D ("NHits"  , "Number of hits;Number of hits;Fraction of tracks",  50, 0,  50),
                                        new const TH1D ("chi2_ndof"  , "chi2ndof;chi2/ndof;a.u.",  100,     0,  5),
                                        new const TH1D ("dxy","d_{xy};d_{xy};Fraction of tracks",200,-10.0,10.0),
                                        new const TH1D ("errxy","sigma_{xy};#sigma_{xy};Fraction of tracks",100,0.0,1.0),
                                        new const TH1D ("dxy_errxy","d_{xy}/#sigma_{xy};d_{xy}/#sigma_{xy};Fraction of tracks",2000,-200.0,200.0),
                                        new const TH1D ("dz","d_{z};d_{z};Fraction of tracks",1600,-80.0,80.0),
                                        new const TH1D ("errz","#sigma_{z};#sigma_{z};Fraction of tracks",100,0.0,10.0),
                                        new const TH1D ("pt_errpt","sigma_{pt}/p_{t};#sigma_{pt}/p_{t};Fraction of tracks",100,0.0,0.1),
                                        new const TH1D ("dz_errz","d_{z}/#sigma_{z};d_{z}/#sigma_{z};Fraction of tracks",2000,-200.0,200.0),
                                        new const TH1D ("Diffvxx"  , "Difference PrimVx trackvx;VPx-Vx[cm];#enitres",  200,     0,  10),
                                        new const TH1D ("Diffvyy"  , "Difference PrimVy trackvy;VPy-Vy[cm];#enitres",  200,     0,  10),
                                        new const TH1D ("Diffvzz"  , "Difference PrimVz trackvz;VPz-Vz[cm];#enitres",  400,     0,  20)},

               * proto_vertices[NDIR]   = { new const TH1D ("x", "x-position;x/cm;#entries", 100,  0.2, 0.4),
                                            new const TH1D ("y", "y-position;y/cm;#entries", 100,  0.3, 0.5),
                                            new const TH1D ("z", "z-position;z/cm;#entries", 100,  -20, 20 ),
                                            new const TH1D ("chi2ndof", "chi2ndof;#chi^{2}/ndof;#entries", 100,  -20, 20 ),
                                            new const TH1D ("z_for_tests", "z-position;z/cm;#entries", 100,  -0.1, 0.1 ),
                                            new const TH1D ("Nvertices", "Number of vertices;Number of vertices;nevents", 100, 0, 100)};


    map<TString, TH1D *> hist1D; // i.e. map["string"] = histogram (use "iterators" to run over a map--see below)
    map<TString, TH2D *> hist2D;
    map<TString, TProfile *> profile;
    // reconstructed vertices
    for (unsigned int idir = 0 ; idir < NDIR ; idir++)
    {
        TString name = TString::Format("RV_%s", proto_vertices[idir]->GetName());
        hist1D[name] = (TH1D *) proto_vertices[idir]->Clone(name);
        hist1D[name]->SetTitle(TString::Format("%s of the reconstructed vertices", proto_vertices[idir]->GetTitle()));
        hist1D[name]->SetXTitle(proto_vertices[idir]->GetXaxis()->GetTitle());
        hist1D[name]->SetYTitle(proto_vertices[idir]->GetYaxis()->GetTitle());
    }
    // reconstructed tracks
    for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
    {
        TString name = TString::Format("RT_%s", proto_tracks[ikin]->GetName());
        hist1D[name] = (TH1D *) proto_tracks[ikin]->Clone(name);
        hist1D[name]->SetTitle(TString::Format("%s of the reconstructed tracks", proto_tracks[ikin]->GetTitle()));
        hist1D[name]->SetXTitle(proto_tracks[ikin]->GetXaxis()->GetTitle());
        hist1D[name]->SetYTitle(proto_tracks[ikin]->GetYaxis()->GetTitle());
    }
    // p_t in eta bin
    for (unsigned int ieta = 0 ; ieta < NETABIN ; ieta++)
    {
        TString name = TString::Format("RT_pt_%d", ieta);
        hist1D[name] = (TH1D *) proto_tracks[0]->Clone(name); // 0 = pt
        hist1D[name]->SetTitle(TString::Format("transverse momentum of the reconstructed tracks in %f < |#eta| < %f", ieta*ETABINWIDTH, (ieta+1)*ETABINWIDTH));
        hist1D[name]->SetXTitle(proto_tracks[0]->GetXaxis()->GetTitle());
        hist1D[name]->SetYTitle(proto_tracks[0]->GetYaxis()->GetTitle());
    }
    hist1D["rechit_energy" ] = new TH1D ("rechit_energy" ,  "rechit energy deposit;E/GeV;#entries", 100, 0, 100);
    
    
    // the same at gen level
    if (kContainsGenLevel)
    {   // create histograms for gen level with the exact same structure

        // generated vertices
        for (unsigned int idir = 0 ; idir < NDIR ; idir++)
        {
            TString name = TString::Format("GV_%s", proto_vertices[idir]->GetName());
            hist1D[name] = (TH1D *) proto_vertices[idir]->Clone(name);
            hist1D[name]->SetTitle(TString::Format("%s of the generated vertices", proto_vertices[idir]->GetTitle()));
            hist1D[name]->SetXTitle(proto_vertices[idir]->GetXaxis()->GetTitle());
            hist1D[name]->SetYTitle(proto_vertices[idir]->GetYaxis()->GetTitle());
        }
        // generated tracks (charged particles might be a more appropriate term)
        for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
        {
            TString name = TString::Format("GT_%s", proto_tracks[ikin]->GetName());
            hist1D[name] = (TH1D *) proto_tracks[ikin]->Clone(name);
            hist1D[name]->SetTitle(TString::Format("%s of the generated tracks", proto_tracks[ikin]->GetTitle()));
            hist1D[name]->SetXTitle(proto_tracks[ikin]->GetXaxis()->GetTitle());
            hist1D[name]->SetYTitle(proto_tracks[ikin]->GetYaxis()->GetTitle());
        }
        for (unsigned int ieta = 0 ; ieta < NETABIN ; ieta++)
        {
            TString name = TString::Format("GT_pt_%d", ieta);
            hist1D[name] = (TH1D *) proto_tracks[0]->Clone(name); // 0 = pt
            hist1D[name]->SetTitle(TString::Format("transverse momentum of the reconstructed tracks in %f < |#eta| < %f", ieta*ETABINWIDTH, (ieta+1)*ETABINWIDTH));
            hist1D[name]->SetXTitle(proto_tracks[0]->GetXaxis()->GetTitle());
            hist1D[name]->SetYTitle(proto_tracks[0]->GetYaxis()->GetTitle());
        }
        // energy deposit in the forward calorimeter
        hist1D["forward_energy"] = new TH1D ("forward_energy", "forward energy deposit;E/GeV;#entries", 100, 0, 100);
        
        
        
        
        // this macro is used to define 2d histogram using the 1d histogram corresponding to the axes
#define DEFINE2DHIST(XNAME, YNAME, TITLE) \
        hist2D[XNAME "_VS_" YNAME] = new TH2D (XNAME "_VS_" YNAME, TITLE, \
                hist1D[XNAME]->GetNbinsX(), hist1D[XNAME]->GetXaxis()->GetXmin(), hist1D[XNAME]->GetXaxis()->GetXmax(), \
                hist1D[YNAME]->GetNbinsX(), hist1D[YNAME]->GetXaxis()->GetXmin(), hist1D[YNAME]->GetXaxis()->GetXmax())
        DEFINE2DHIST("forward_energy", "GT_pt", "forward energy deposit VS leading generated transverse momentum;E/GeV;p_T/GeV;#entries");
        DEFINE2DHIST("forward_energy", "GT_M" , "forward energy deposit VS generated multiplicity               ;E/GeV;M      ;#entries");
    }
    DEFINE2DHIST("RT_eta", "RT_phi" , "#eta VS #phi ;#eta;#phi;#entries");
    DEFINE2DHIST("RV_z", "RV_chi2ndof" , "VZ VS #chi^{2} ;Vz ;#chi^{2}/ndof;#entries");
    DEFINE2DHIST("rechit_energy", "RT_pt", "rechit energy deposit VS leading reconstructed transverse momentum;E/GeV;p_T/GeV;#entries");
    DEFINE2DHIST("rechit_energy", "RT_M" , "rechit energy deposit VS reconstructed multiplicity             ;E/GeV;M      ;#entries");
#undef DEFINE2DHIST
    //TProfile for the 2D histograms but taking the mean value per bin in Y axis
    profile["RT_dxy_errxy_VS_eta"] = new TProfile("RT_dxy_errxy_VS_eta","d_{xy}/#sigma_{xy} VS #eta",600,-3.0,3.0);
    profile["RT_dz_errz_VS_eta"] = new TProfile("RT_dz_errz_VS_eta","d_{z}/#sigma_{z} VS #eta",600,-3.0,3.0);
    profile["RT_errpt_pt_VS_eta"] = new TProfile("RT_errpt_pt_VS_eta","#sigma_{pt}/p_{t} VS #eta",600,-3.0,3.0);

    /******************* RUNNING OVER THE TREE ***********************/

    // counters
    const Long64_t nentries = (maxentries <= 0) ? fChain->GetEntriesFast() : min(fChain->GetEntriesFast(),maxentries);
    unsigned short int progress = 0;  // counter  to see the progress of the loop
    Long64_t nbytes = 0, nb = 0; // dunno the use of this... (given by TTree::MakeClass())

    cout << "Running over " << nentries << " entries..." << endl;
    for (Long64_t jentry=0; jentry<nentries;jentry++)
    {
        // just a counter to see the progress of the loop
        if ((100*jentry)/nentries != progress)
        {
            progress = (100*jentry)/nentries;
            cout << "Loop: " << progress << "%" << endl;
        }

        // load the entry
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;
        // if (Cut(ientry) < 0) continue; // currently, the Cut method has not been implemented (and is likely not going to be)

        //LumiBlock selection
       // cout<<"LumiBlock = "<<EI.LumiBlock<<", Run = "<<EI.Run<<", bunch = "<<EI.Bunch <<endl;
        //if(EI.Bunch==208 || EI.Bunch==408 || EI.Bunch==1993 || EI.Bunch==2193) cout<<"bunch = "<<EI.Bunch <<endl;
        if(EI.LumiBlock<88) continue; 
        if(!(EI.Bunch==208 || EI.Bunch==408 || EI.Bunch==1993 || EI.Bunch==2193)) continue;
        //cout<<"LumiBlock = "<<EI.LumiBlock<<", Run = "<<EI.Run<<", bunch = "<<EI.Bunch <<endl;
//--------------------------------------------------------------------------------
 /*       if (kContainsGenLevel)
        {
            // test GV
            for (unsigned int ivertex = 0 ; ivertex < GV.x->size() ; ivertex++)
            {
                // basic plots
                hist1D["GV_x"]->Fill(GV.x->at(ivertex));
                hist1D["GV_y"]->Fill(GV.y->at(ivertex));
                hist1D["GV_z"]->Fill(GV.z->at(ivertex));
            }
            hist1D["GV_Nvertices"]->Fill(GV.x->size());

            // test GT
            unsigned int ngentracks = 0; // #tracks passing the cutoffs
            double genRHenergy = 0.,
                   leading_GT_pt = 0.;
            for (unsigned int itrack = 0 ; itrack < GT.pt->size() ; itrack++)
            {
                if (GT.status->at(itrack) != 1) continue;
                // basic plots
                if (       GT.pt ->at(itrack)  > minpt   
                    && abs(GT.eta->at(itrack)) < maxtracketa)
                {
                    hist1D["GT_pt" ]->Fill(GT.pt ->at(itrack));
                    hist1D["GT_eta"]->Fill(GT.eta->at(itrack));
                    hist1D["GT_phi"]->Fill(GT.phi->at(itrack));
                    ngentracks++;
                    // mimiced rechit vs leading pt
                    leading_GT_pt = max(leading_GT_pt, GT.pt->at(itrack));
                    // pt in eta bins
                    hist1D[TString::Format("GT_pt_%d", (int) abs(GT.eta->at(itrack)/ETABINWIDTH))]->Fill(GT.pt->at(itrack)); 
                }
                if (   fabs(GT.eta->at(itrack)) > minRHeta
                    && fabs(GT.eta->at(itrack)) < maxRHeta)
                {
                    genRHenergy += GT.energy->at(itrack);
                }
            }
            hist1D["GT_M"]->Fill(ngentracks);
            // mimic rechit
            hist1D["forward_energy"]->Fill(genRHenergy);
            hist2D["forward_energy_VS_GT_M"]->Fill(genRHenergy, ngentracks);
            hist2D["forward_energy_VS_GT_pt"]->Fill(genRHenergy, leading_GT_pt);
        }

*/

//--------------------------------------------------------------------------------

       //Initializing variable to select good wiality vertex         
       bool   isGoodVertex = false; 
    
       
        //At least one vertex
        if(RV.z->size()<1) continue;

        hist2D["RV_z_VS_RV_chi2ndof"] -> Fill(RV.z->at(0), (RV.chi2->at(0)/RV.ndof->at(0)));

        
    
    
        // test RT
        // looping over the reconstructed tracks and counting how many pass the cuts
        unsigned int nrectracks = 0,        // #tracks passing the basic cutoffs
                     nrecQualitytracks = 0; // #tracks passing the full quality cutoffs
        for (unsigned int itrack = 0 ; itrack < RT.eta->size() ; itrack++)
        {
            if (  //  RT.pt ->at(itrack)  > minpt
                  //   fabs(RT.charge->at(itrack))==1 
                     fabs(RT.eta->at(itrack)) < maxtracketa){
                nrectracks++;
                hist2D["RT_eta_VS_RT_phi"]->Fill(RT.eta->at(itrack),RT.phi->at(itrack));
 
            }
        }
        //cout<<"Multi = "<<nrectracks<<endl;
        //getchar(); 
       

             //   cout<<"Primary vertex position = ("<<RV.x->at(0)<<","<<RV.y->at(0)<<","<<RV.z->at(0)<<")"<<endl;
             //if(fabs(RV.z->at(ivertex))<1) cout<<"Z-Vertex position = "<<RV.z->at(ivertex)<<endl;
            NofVertexEvents++;
            hist1D["RV_Nvertices"]->Fill(RV.x->size());
//        }


        //Only if primary vertex has |z|<20cm & sqrt(x^2 + y^2)<0.2cm 
        double RVdxy = sqrt(pow(RV.x->at(0),2)+pow(RV.y->at(0),2)); //Selection with primiry vertex (first one of the RV sample)
        if(fabs(RV.z->at(0)) > 20 || RVdxy > 0.2) continue;  
        nselevents++;
        //--

        double leading_RT_pt = 0.,
               recHFenergy = 0.; // total energy deposit in the forward calorimeter
        
        for (unsigned int itrack = 0 ; itrack < RT.pt->size() ; itrack++)
        {
    
            
            
            // basic plots
            if (   fabs(RT.eta->at(itrack)) < maxtracketa
                && fabs(RT.charge->at(itrack))==1    
                && nrectracks > 2)
            {
               

               hist1D["RT_Diffvxx"]->Fill(RT.vx->at(itrack)-RV.x->at(0)); 
               hist1D["RT_Diffvyy"]->Fill(RT.vy->at(itrack)-RV.y->at(0)); 
               hist1D["RT_Diffvzz"]->Fill(RT.vz->at(itrack)-RV.z->at(0)); 
          
               //Only taking the particles which are close to the primary vertex per event.
               //if(fabs(RT.vz->at(itrack)-RV.z->at(0))>0.15) continue;
                //cout<<"dz = "<<fabs(RT.vz->at(itrack)-RV.z->at(0))<<endl;


                //Applying all quality criteria, since the variables of this histograms are not in the cuts
               if(         fabs(RT.dxy->at(itrack))/RT.dxyError->at(itrack) < 3
                       &&  fabs(RT.dz->at(itrack)-RV.z->at(0))/RT.dzError->at(itrack) < 3)  
                       &&  RT.pt ->at(itrack) > minpt                    
                       &&  RT.ptError->at(itrack)/RT.pt->at(itrack) < 0.1)
               {           
                   hist1D["RT_phi"]       ->Fill(RT.phi->at(itrack));
                   hist1D["RT_eta"]       ->Fill(RT.eta->at(itrack));
                   hist1D["RT_chi2_ndof"] ->Fill(RT.chi2->at(itrack)/RT.ndof->at(itrack));
                   hist1D["RT_NHits"]     ->Fill(RT.numberOfValidHits->at(itrack));
                   isGoodVertex = true;  //Requiring the full quiality cuts in the (at least) 3 tracks per vertex 
                   nrecQualitytracks++;  //Counter of quality tracks for multiplicity of quality tracks 
                   // cout<<"ETA = "<< RT.eta->at(itrack)<<endl;
               }
                
               

                //Removing variable cuts dxy, sigma(xy) since this histogrmas depend on those variables
               if(   fabs(RT.dz->at(itrack)-RV.z->at(0))/RT.dzError->at(itrack) < 3)  
                       && RT.pt ->at(itrack) > minpt
                       && RT.ptError->at(itrack)/RT.pt->at(itrack) < 0.1)
               {           
                   hist1D["RT_dxy_errxy"] ->Fill((RT.dxy->at(itrack))/RT.dxyError->at(itrack)); 
                   hist1D["RT_dxy"]       ->Fill(RT.dxy->at(itrack)); 
                   hist1D["RT_errxy"]     ->Fill(RT.dxyError->at(itrack)); 
                   profile["RT_dxy_errxy_VS_eta"] ->Fill(RT.eta->at(itrack),(fabs(RT.dxy->at(itrack)))/RT.dxyError->at(itrack));
               }



                //Removing variable cuts dz, sigma(z) since this histogrmas depend on those variables
               if(   fabs(RT.dxy->at(itrack))/RT.dxyError->at(itrack) < 3 )
                       && RT.pt ->at(itrack) > minpt
                       && RT.ptError->at(itrack)/RT.pt->at(itrack) < 0.1)
               {           
                   hist1D["RT_dz_errz"]   ->Fill((RT.dz->at(itrack)-RV.z->at(0))/(RT.dzError->at(itrack))); 
                   hist1D["RT_dz"]        ->Fill(RT.dz->at(itrack)-RV.z->at(0)); 
                   hist1D["RT_errz"]      ->Fill(RT.dzError->at(itrack)); 
                   profile["RT_dz_errz_VS_eta"]   ->Fill(RT.eta->at(itrack),fabs((RT.dz->at(itrack))-(RV.z->at(0)))/(RT.dzError->at(itrack)));
               }



                //Removing variable cuts pt, sigma(pt) since this histogrmas depend on those variables
               if(      fabs(RT.dxy->at(itrack))/RT.dxyError->at(itrack) < 3
                       &&  fabs(RT.dz->at(itrack)-RV.z->at(0))/RT.dzError->at(itrack) < 3)  
               {           
                   hist1D["RT_pt_errpt"]  ->Fill((RT.ptError->at(itrack))/RT.pt->at(itrack)); 
                   hist1D["RT_pt" ]       ->Fill(RT.pt ->at(itrack));
                   profile["RT_errpt_pt_VS_eta"]  ->Fill(RT.eta->at(itrack),(RT.ptError->at(itrack))/RT.pt->at(itrack));

                   // pt in eta bins
                   hist1D[TString::Format("RT_pt_%d", (int) abs(RT.eta->at(itrack)/ETABINWIDTH))]->Fill(RT.pt->at(itrack)); 
               }



                // rechit vs leading pt
                leading_RT_pt = max(leading_RT_pt, RT.pt->at(itrack));
                
            }
        }

        if(isGoodVertex){ 
            hist1D["RV_x"]->Fill(RV.x->at(0));
            hist1D["RV_y"]->Fill(RV.y->at(0));
            hist1D["RV_z"]->Fill(RV.z->at(0));
        }
        if(nrectracks>2){
           // cout<<"N tracks = "<<nrectracks<<endl;
           // cout<<"Nsel tracks = "<<nrecQualitytracks<<endl;
            hist1D["RT_M"]->Fill(nrectracks);
            hist1D["RT_M_withcuts"]->Fill(nrecQualitytracks);
        }
    }
    cout << "Loop: 100%!!" << endl;

    /*************** EFFICIENCIES AND RATIOS *****************************/
//
//    if  (kContainsGenLevel)
//    {
//        cout << "Computing ratios" << endl;
//        // ratio of generated tracks over reconstructed tracks
//        for (unsigned int ikin = 0 ; ikin < NKIN ; ikin++)
//        {
//            TString name = TString::Format("ratio_tracks_%s", proto_tracks[ikin]->GetName());
//            hist1D[name] = (TH1D *) proto_tracks[ikin]->Clone(name);
//            hist1D[name]->SetTitle(TString::Format("%s efficiency", proto_tracks[ikin]->GetTitle()));
//            hist1D[name]->SetYTitle("gen/reco");
//            hist1D[name]->Add   (hist1D[TString::Format("RT_%s",proto_tracks[ikin]->GetName())]);   // numerator   = RECO
//            hist1D[name]->Divide(hist1D[TString::Format("GT_%s",proto_tracks[ikin]->GetName())]);   // denominator = GEN 
//        }
//        // same in the particular case of pt in eta bins
//        for (unsigned int ieta = 0 ; ieta < NETABIN ; ieta++)
//        {
//            TString name = TString::Format("ratio_tracks_pt_%d", ieta);
//            hist1D[name] = (TH1D *) proto_tracks[0]->Clone(name); // 0 = pt
//            hist1D[name]->SetTitle(TString::Format("transverse momentum of the reconstructed tracks in %f < |#eta| < %f", ieta*ETABINWIDTH, (ieta+1)*ETABINWIDTH));
//            hist1D[name]->SetYTitle("gen/reco");
//            hist1D[name]->Add   (hist1D[TString::Format("RT_pt_%d",ieta)]);   // numerator   = RECO
//            hist1D[name]->Divide(hist1D[TString::Format("GT_pt_%d",ieta)]);   // denominator = GEN 
//        }
//    }

    /*************** NORMALIZATION OF HISTOGRAMS *****************************/
    double totaltracks = hist1D["RT_M"]->Integral();
//    double NofGoodEntries = hist1D["RT_M_withcuts"]->GetEntries(); 
 
    //RT
    //To the total number of tracks in all the events
    hist1D["RT_dxy_errxy"] -> Scale(1.0/((double)totaltracks));
    hist1D["RT_dxy"]       -> Scale(1.0/((double)totaltracks));
    hist1D["RT_errxy"]     -> Scale(1.0/((double)totaltracks));
    hist1D["RT_dz_errz"]   -> Scale(1.0/((double)totaltracks));
    hist1D["RT_dz"]        -> Scale(1.0/((double)totaltracks));
    hist1D["RT_errz"]      -> Scale(1.0/((double)totaltracks));
    hist1D["RT_pt_errpt"]  -> Scale(1.0/((double)totaltracks));
    hist1D["RT_NHits"]     -> Scale(1.0/((double)totaltracks));  
    
    //Number of events: nentries(number of total events), nselevents = number of selected events
    hist1D["RT_eta"] -> Scale(1.0/nselevents);  
    hist1D["RT_eta"] -> Scale(1.0/0.1);
    hist1D["RT_pt"]  -> Scale(1.0/nselevents);  
    hist1D["RT_pt"]  -> Scale(1.0/0.1);
    hist1D["RT_M"]   -> Scale(1.0/nselevents);  
    hist1D["RT_M_withcuts"]   -> Scale(1.0/nselevents);  
    hist1D["RT_phi"] -> Scale(1.0/nselevents);
    hist1D["RT_phi"] -> Scale(1.0/(PI/10.0));
    hist1D["RT_chi2_ndof"] -> Scale(1.0/nselevents);
    hist1D["RV_Nvertices"]->Scale(1.0/NofVertexEvents);

    hist1D["RV_z"]-> Scale(1.0/((double)nentries));
    hist2D["RT_eta_VS_RT_phi"] -> Scale(1.0/((double)nentries)); 
        
    for (unsigned int ieta = 0 ; ieta < NETABIN ; ieta++)
    {
        TString name = TString::Format("RT_pt_%d", ieta);
        hist1D[name] -> Scale(1.0/nselevents); 
        hist1D[name] -> Scale(1.0/0.1); 
    }

    //GT
    //To the total number of tracks in all the events
//    hist1D["GT_dxy_errxy"] -> Scale(1.0/((double)totaltracks));
//    hist1D["GT_dz_errz"]   -> Scale(1.0/((double)totaltracks));
//    hist1D["GT_pt_errpt"]  -> Scale(1.0/((double)totaltracks));
//    
//    //Number of events: nentries
//    hist1D["GT_eta"] -> Scale(1.0/nselevents);  
//    hist1D["GT_eta"] -> Scale(1.0/0.1);
//    hist1D["GT_pt"]  -> Scale(1.0/nselevents);  
//    hist1D["GT_pt"]  -> Scale(1.0/0.1);
//    //hist1D["GT_M"]   -> Scale(1.0/((double)nentries));  
//    hist1D["GT_phi"] -> Scale(1.0/nselevents);
//    hist1D["GT_phi"] -> Scale(1.0/(PI/10.0));

    /************************* SAVING *******************************/

   // TString outputfilename = TString::Format("_" __FILE__ "_pt_gt_%f_eta_st_%f", minpt, maxtracketa); // 1) it should include the phase space
   // outputfilename.ReplaceAll(".", "_"); // replace . by _ in the given values of the phase space
   // outputfilename = path_to_tree + outputfilename; // it should specify the name of the input file
   // outputfilename.ReplaceAll(".root", ""); // but without the .root that would appear in the middle...
   // outputfilename.ReplaceAll("bonsai", "plots"); // and replacing the initial keywork to identify the kind of object that are stored in the file
   // outputfilename += ".root"; // and add .root at the end of the filename
   // cout << "Saving histograms into " << outputfilename << endl;

    //TFile * f = new TFile (outputfilename, "RECREATE");
    TFile * f = new TFile ("../data/TEST_CP_0T_data_7June__13TeV_NoCuts_1vertex.root", "RECREATE");
    // this loop just runs over all the TH1D to save them
    // (note: here we use an iterator to run over the map)
#define WRITE(HISTOTYPE, HISTOMAP) for (map<TString,HISTOTYPE *>::iterator it_hist = HISTOMAP.begin() ; it_hist != HISTOMAP.end() ; it_hist++) it_hist->second->Write();
    WRITE(TH1D, hist1D);
    WRITE(TH2D, hist2D);
    WRITE(TProfile, profile);
#undef WRITE
    f->Close();
    cout << "File closed." << endl;

    /*********************** PRINTING *************************/

    // NOT HERE
    // TODO: later in different file... (e.g. plotfast_*.C in the data directory)
}

#include "main.cc"
