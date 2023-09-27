//Xianglei Zhu 
//Skeleton embedding MuDST analysis macro with StMuDSTMaker 
//Run it with the wrapper in ACLIC mode, CINT mode for debug ONLY

#ifndef __CINT__
#include "TROOT.h"
#include "TSystem.h"
#include <iostream>
#include <fstream>
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TTreeHelper.h"
#include "TDatime.h"
#include "TMath.h"
#include "StarRoot/TUnixTime.h"
#include "StChain.h"
#include "StMessMgr.h"
#include "StMuDSTMaker/COMMON/StMuDstMaker.h"
#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include "StMuDSTMaker/COMMON/StMuTrack.h"
#include "StMuDSTMaker/COMMON/StMuMcTrack.h"
#include "StMuDSTMaker/COMMON/StMuMcVertex.h"
#include "StMuDSTMaker/COMMON/StMuPrimaryVertex.h"
//05022022(start)
#include "StMuDSTMaker/COMMON/StMuBTofPidTraits.h"
#include "StMuDSTMaker/COMMON/StMuBTofPidTraits.h"
//05022022(finish)
#include "StBTofHeader.h"
#include "StThreeVectorF.hh"
#include "StPhysicalHelixD.hh"

#include "RunNo.h"

#endif

//05102021(start)
// void makeMuDstQA(TString InputFileList, Int_t nFiles = 1, Int_t nEvents = 0, TString OutputFile = "test.histo.root", const int PID = 8);

// void makeMuDstQA(TString InputFileList, Int_t nFiles, Int_t nEvents, TString OutputFile, const int PID) 
void makeMuDstQA(TString InputFileList, Int_t nFiles = 1, Int_t nEvents = 0, TString OutputFile = "test.histo.root", const int PID = 8, double dca_cut = 10., int nHitsFits_cut = 20, string thisNameRuZr = "Ru");//dca_cut will be divided by 10 later

void makeMuDstQA(TString InputFileList, Int_t nFiles, Int_t nEvents, TString OutputFile, const int PID, double dca_cut, int nHitsFits_cut, string thisNameRuZr) 
//05102021(finish)
{

  //05102021(start)
  dca_cut = dca_cut/10.;
  cout<<"dca_cut = "<<dca_cut<<endl;
  cout<<"nHitsFits_cut = "<<nHitsFits_cut<<endl;
  //05102021(finish)

  if(PID == 8) cout<<"PID is pi+: "<<PID<<endl;
  else if(PID == 9) cout<<"PID is pi-: "<<PID<<endl;
  else if(PID == 11) cout<<"PID is K+: "<<PID<<endl;
  else if(PID == 12) cout<<"PID is K-: "<<PID<<endl;
  else if(PID == 14) cout<<"PID is Proton: "<<PID<<endl;
  else if(PID == 15) cout<<"PID is anti-Proton: "<<PID<<endl;
  else {cout<<"ERROR: Check your PID!"<<endl; return;}

  cout<<"And the file list is "<<InputFileList<<endl;
  
  // Load libraries for CINT mode
#ifdef __CINT__
  gROOT   -> Macro("loadMuDst.C");
#endif

  ifstream myfile_in;
  myfile_in.open(InputFileList);
  string dummy;
  ofstream myfile_out;
  myfile_out.open(InputFileList+"_goodonesonly");
  TFile *f_tester;
  while(myfile_in>>dummy){
    // cout<<dummy<<endl;
    // if(!gSystem->AccessPathName(dummy.c_str())) myfile_out<<dummy<<endl;
    f_tester = new TFile(dummy.c_str());
    if(f_tester->IsZombie()){cout<<dummy<<" Is Zombie"<<endl;}
    else if(f_tester->TestBit(TFile::kRecovered)){cout<<dummy<<" Is recovered"<<endl;}
    else if(!f_tester->GetListOfKeys()->Contains("MuDst")){cout<<dummy<<" has no MuDST"<<endl;}
    else {myfile_out<<dummy<<endl;}
    f_tester->Close();
    delete f_tester;
  }

  // List of member links in the chain
  StChain*                    chain  =  new StChain ;

  //27042022(start)
  // StMuDstMaker*          muDstMaker  =  new StMuDstMaker(0,0,"",InputFileList,"MuDst",nFiles) ;
  StMuDstMaker*          muDstMaker  =  new StMuDstMaker(0,0,"",InputFileList+"_goodonesonly","MuDst",nFiles) ;
  //27042022(finish)

  // ---------------- modify here according to your QA purpose --------------------------
  // Turn off everything but Primary tracks in order to speed up the analysis and eliminate IO
  muDstMaker -> SetStatus("*",0) ;               // Turn off all branches
  muDstMaker -> SetStatus("MuEvent",1) ;         // Turn on the Event data (esp. Event number)
  muDstMaker -> SetStatus("PrimaryVertices",1) ;    // Turn on the primary track data
  muDstMaker -> SetStatus("PrimaryTracks",1) ;    // Turn on the primary track data
  muDstMaker -> SetStatus("GlobalTracks",1) ;    // Turn on the global track data
  muDstMaker -> SetStatus("CovGlobTrack",1);   // to fix the refmult in Run14!!!
  muDstMaker -> SetStatus("MCAll",1) ;          // Turn on the McVertex/McTrack data
  muDstMaker -> SetStatus("BTofHit",1) ;    // Turn on the btof data
  muDstMaker -> SetStatus("BTofRawHit",1) ;    // Turn on the btof data
  muDstMaker -> SetStatus("BTofHeader",1) ;    // Turn on the btof data
  muDstMaker -> SetDebug(0) ;                    // Turn off Debug information

  // if ( nEvents == 0 )  nEvents = 10000000 ;       // Take all events in nFiles if nEvents = 0
  if ( nEvents == 0 )  nEvents =  muDstMaker->chain()->GetEntries();       // Take all events in nFiles if nEvents = 0
  cout<<"Number of events: "<<nEvents<<endl;

  // ---------------- modify here according to your QA purpose --------------------------
  TFile *tags_output = new TFile( OutputFile, "recreate" ) ;
  tags_output->cd();

  const int Nocent = 10;
  const int Nmultbin = 2000;
  //https://drive.google.com/file/d/1TPrAanuiBoMcvw8FedtL8aNHgW8j8H1M/view?usp=sharing
  int cent_ref[11];
  cent_ref[0] = Nmultbin;
  cent_ref[1] = 500;
  if(thisNameRuZr == "Ru"){
    cent_ref[2] = 258;//0-5%                                                                                        
    cent_ref[3] = 216;//5-10%                                                                                       
    cent_ref[4] = 151;//10-20%                                                                                      
    cent_ref[5] = 103;//20-30%                                                                                      
    cent_ref[6] =  69;//30-40%                                                                                      
    cent_ref[7] =  44;//40-50%                                                                                      
    cent_ref[8] =  26;//50-60%                                                                                      
    cent_ref[9] =  15;//60-70%                                                                                      
    cent_ref[10] =  8;//70-80%                                                                                      
  }
  if(thisNameRuZr == "Zr"){
    cent_ref[2] =  256;//0-5%                                                                                       
    cent_ref[3] =  213;//5-10%                                                                                      
    cent_ref[4] =  147;//10-20%                                                                                     
    cent_ref[5] =  100;//20-30%                                                                                     
    cent_ref[6] =   65;//30-40%                                                                                     
    cent_ref[7] =   41;//40-50%                                                                                     
    cent_ref[8] =   25;//50-60%                                                                                     
    cent_ref[9] =   14;//60-70%                                                                                     
    cent_ref[10] =  7;//70-80%                                                                                      
  }

  double vz[6+1];
  for(int i_vz = 0 ; i_vz < 6 ; i_vz++){vz[i_vz] = -35 + i_vz*10;}
  vz[1] = 25;

  TH2F *h2_y_pt_p[Nocent][6];
  TH2F *h2_y_pt_m[Nocent][6];
  TH2F *h2_y_pt_mc_p[Nocent][6];
  TH2F *h2_y_pt_mc_m[Nocent][6];
  TH2F *h2_y_pt_eff_p[Nocent][6];
  TH2F *h2_y_pt_eff_m[Nocent][6];

  for(int i_cent = 0 ; i_cent < Nocent ; i_cent++){
    for(int i_vz = 0 ; i_vz < 6 ; i_vz++){
      h2_y_pt_p[i_cent][i_vz] = new TH2F(Form("h2_y_pt_p_cent_%d_vz_%d", i_cent, i_vz), Form("Plus. y vs p_{T}, refmult: [%d, %d),  %2.0f <= vz < %2.0f", cent_ref[i_cent+1], cent_ref[i_cent], vz[i_vz], vz[i_vz+1]), 400, -2.0, 2.0, 500, 0.0, 5.0);
      h2_y_pt_m[i_cent][i_vz] = new TH2F(Form("h2_y_pt_m_cent_%d_vz_%d", i_cent, i_vz), Form("Minus. y vs p_{T}, refmult: [%d, %d),  %2.0f <= vz < %2.0f", cent_ref[i_cent+1], cent_ref[i_cent], vz[i_vz], vz[i_vz+1]), 400, -2.0, 2.0, 500, 0.0, 5.0);

      h2_y_pt_mc_p[i_cent][i_vz] = new TH2F(Form("h2_y_pt_mc_p_cent_%d_vz_%d", i_cent, i_vz), Form("MC. Plus. y vs p_{T}, refmult: [%d, %d),  %2.0f <= vz < %2.0f", cent_ref[i_cent+1], cent_ref[i_cent], vz[i_vz], vz[i_vz+1]), 400, -2.0, 2.0, 500, 0.0, 5.0);
      h2_y_pt_mc_m[i_cent][i_vz] = new TH2F(Form("h2_y_pt_mc_m_cent_%d_vz_%d", i_cent, i_vz), Form("MC. Minus. y vs p_{T}, refmult: [%d, %d),  %2.0f <= vz < %2.0f", cent_ref[i_cent+1], cent_ref[i_cent], vz[i_vz], vz[i_vz+1]), 400, -2.0, 2.0, 500, 0.0, 5.0);

      h2_y_pt_eff_p[i_cent][i_vz] = new TH2F(Form("h2_y_pt_eff_p_cent_%d_vz_%d", i_cent, i_vz), Form("EFF. Plus. y vs p_{T}, refmult: [%d, %d),  %2.0f <= vz < %2.0f", cent_ref[i_cent+1], cent_ref[i_cent], vz[i_vz], vz[i_vz+1]), 400, -2.0, 2.0, 500, 0.0, 5.0);
      h2_y_pt_eff_m[i_cent][i_vz] = new TH2F(Form("h2_y_pt_eff_m_cent_%d_vz_%d", i_cent, i_vz), Form("EFF. Minus. y vs p_{T}, refmult: [%d, %d),  %2.0f <= vz < %2.0f", cent_ref[i_cent+1], cent_ref[i_cent], vz[i_vz], vz[i_vz+1]), 400, -2.0, 2.0, 500, 0.0, 5.0);

      h2_y_pt_p[i_cent][i_vz]->GetXaxis()->SetTitle("y");
      h2_y_pt_m[i_cent][i_vz]->GetXaxis()->SetTitle("y");
      h2_y_pt_mc_p[i_cent][i_vz]->GetXaxis()->SetTitle("y");
      h2_y_pt_mc_m[i_cent][i_vz]->GetXaxis()->SetTitle("y");
      h2_y_pt_eff_p[i_cent][i_vz]->GetXaxis()->SetTitle("y");
      h2_y_pt_eff_m[i_cent][i_vz]->GetXaxis()->SetTitle("y");

      h2_y_pt_p[i_cent][i_vz]->GetYaxis()->SetTitle("p_{T}");
      h2_y_pt_m[i_cent][i_vz]->GetYaxis()->SetTitle("p_{T}");
      h2_y_pt_mc_p[i_cent][i_vz]->GetYaxis()->SetTitle("p_{T}");
      h2_y_pt_mc_m[i_cent][i_vz]->GetYaxis()->SetTitle("p_{T}");
      h2_y_pt_eff_p[i_cent][i_vz]->GetYaxis()->SetTitle("p_{T}");
      h2_y_pt_eff_m[i_cent][i_vz]->GetYaxis()->SetTitle("p_{T}");

      h2_y_pt_p[i_cent][i_vz]->Sumw2();
      h2_y_pt_m[i_cent][i_vz]->Sumw2();
      h2_y_pt_mc_p[i_cent][i_vz]->Sumw2();
      h2_y_pt_mc_m[i_cent][i_vz]->Sumw2();
      h2_y_pt_eff_p[i_cent][i_vz]->Sumw2();
      h2_y_pt_eff_m[i_cent][i_vz]->Sumw2();
    }//for(int i_vz = 0 ; i_vz < 6 ; i_vz++)
  }//for(int i_cent = 0 ; i_cent < Nocent ; i_cent++){
  //19042022(finish)

  TH2D *h2_vr = new TH2D("h2_vr", "h2_vr", 100, -10, 10, 100, -10, 10);
  TH1D *h1_vz = new TH1D("h1_vz", "h1_vz", 100, -50, 50);
  TH1D *h1_vpd = new TH1D("h1_vpd", "h1_vpd", 100, -50, 50);
  TH1D *h1_vzvpd = new TH1D("h1_vzvpd", "h1_vzvpd", 100, -50, 50);

    // cout<<"hey -5"<<endl;

  // variables //
  const double MPROTON  = 0.93827;//GeV
  double E_P = -999.;//Energy to calculate rapidity (P)
  double y_P = -999.;//rapidity (P)

  double E_P_mc = -999.;//Energy to calculate rapidity (P)
  double y_P_mc = -999.;//rapidity (P)
  
  // ---------------- end of histogram and tree booking --------------------------------

  // Loop over the links in the chain
  Int_t iInit = chain -> Init() ;
  if (iInit) chain->FatalErr(iInit,"on init");
  
  // chain -> EventLoop(1,nEvents) ;  //will output lots of useless debugging info.
  Int_t istat = 0, i = 1;
  while (i <= nEvents && istat != 2) {
    if(i%10000==0)cout << endl << "== Event " << i << " start ==" << endl;
    chain->Clear();
    istat = chain->Make(i);

    // cout<<"hey -4"<<endl;
    if (istat == 2)
      cout << "Last  event processed. Status = " << istat << endl;
    if (istat == 3)
      cout << "Error event processed. Status = " << istat << endl;
    i++;

    if(istat != kStOK)continue; //skip those suspectible events
     
    // ---------------- modify here according to your QA purpose --------------------------
    //cout<<"In event #. "<<i-1<<" Maker status "<<istat<<endl;

    // cout<<"hey -3"<<endl;
    StMuDst* mMuDst = muDstMaker->muDst();
    if(!mMuDst) {
      LOG_WARN << " No MuDst " << endm; continue;
    }

    StMuEvent* mMuEvent = mMuDst->event();
    if(!mMuEvent) {
      LOG_WARN << " No MuEvent " << endm; continue;
    }

    int CurrRun = mMuEvent->runId();
    // cout<<"CurrRun = "<<CurrRun<<endl;

    // cout<<"hey -1"<<endl;
    //check if runNo is for Zr or Ru
    bool IsRunZr = false;
    bool IsRunRu = false;
    string NameRuZr;
    for(int i_runNo = 0 ; i_runNo < nRunId_Zr ; i_runNo++){//Zr
      if (CurrRun != IsobarRunId_Zr[i_runNo]) continue;
      else if (CurrRun == IsobarRunId_Zr[i_runNo]) {// cout<<Form("runNo %d is Zr run", CurrRun)<<endl;
	IsRunZr = true; NameRuZr = "Zr"; break;}
    }
    for(int i_runNo = 0 ; i_runNo < nRunId_Ru ; i_runNo++){//Ru
      if (CurrRun != IsobarRunId_Ru[i_runNo]) continue;
      else if (CurrRun == IsobarRunId_Ru[i_runNo]) {// cout<<Form("runNo %d is Ru run", CurrRun)<<endl;
	IsRunRu = true;  NameRuZr ="Ru"; break;}
    }
    if(IsRunZr == false && IsRunRu == false) {// cout<<Form("CANNOT FIND runNo %d's identity!! Zr = false RU = false", CurrRun)<<endl;
      abort();}
    else if(IsRunZr == true && IsRunRu == true) {// cout<<Form("CANNOT FIND runNo %d's identity!! Zr = true RU = true", CurrRun)<<endl;
      abort();}

    // cout<<"hey 0"<<endl;
    //-----------------------------------------------------------------------------
    //vertex selection
    int const originalVertexId = mMuDst->currentVertexIndex();
    StMuPrimaryVertex* selectedVertex = nullptr;
    // choose the default vertex, i.e. the first vertex
    mMuDst->setVertexIndex(0);
    selectedVertex = mMuDst->primaryVertex();
    // fall back to default vertex if no vertex is selected in the algorithm above.
    // should skip this event in the event cuts below.
    if ( ! selectedVertex ){
      LOG_INFO << "Vertex is not valid" << endm;
      //cout<<originalVertexId<<endl;
      mMuDst->setVertexIndex(originalVertexId);
    }
    //end of vertex selection
    //------------------------------------------------------------------------------

    //vertex is not selected
    if ( ! selectedVertex ) continue;

    //trigger
    if ( ! mMuEvent->triggerIdCollection().nominal().isTrigger(600001) && ! mMuEvent->triggerIdCollection().nominal().isTrigger(600011) && ! mMuEvent->triggerIdCollection().nominal().isTrigger(600021) && ! mMuEvent->triggerIdCollection().nominal().isTrigger(600031)) continue ;

    h2_vr->Fill(mMuEvent->primaryVertexPosition().x(), mMuEvent->primaryVertexPosition().y());
    h1_vz->Fill(mMuEvent->primaryVertexPosition().z());
    h1_vpd->Fill(mMuEvent->vpdVz ());
    h1_vzvpd->Fill(mMuEvent->primaryVertexPosition().z() - mMuEvent->vpdVz ());//StMuDst::btofHeader()->vpdVz()

    //Vr
    if ( !(TMath::Sqrt(TMath::Power(mMuEvent->primaryVertexPosition().x(), 2) + TMath::Power(mMuEvent->primaryVertexPosition().y(), 2)) < 2.0) ) continue ;
    //Vz
    if (!(mMuEvent->primaryVertexPosition().z() > -35. && mMuEvent->primaryVertexPosition().z() < 25.)) continue ;

    // //TPC Vz vs VPD Vz
    // if (!(TMath::Abs(mMuEvent->primaryVertexPosition().z() - mMuEvent->vpdVz ()) < 3.)) continue ;//30082022: no vpdvz is stored!!

    //The MC arrays in MuDST
    TClonesArray *MuMcVertices   = mMuDst->mcArray(0);
    Int_t NoMuMcVertices = MuMcVertices->GetEntriesFast();
    TClonesArray *MuMcTracks     = mMuDst->mcArray(1); 
    Int_t NoMuMcTracks = MuMcTracks->GetEntriesFast();
    // LOG_INFO <<"# of MC tracks = "<< NoMuMcTracks <<" # of MC vertices = "<< NoMuMcVertices << endm;
    if (! NoMuMcVertices || ! NoMuMcTracks) {
      LOG_WARN << "Ev. " << i  << " has no MC information ==> skip it" << endm;
      continue;
    }

    //fill Event QA histograms
    TObjArray* tracks = muDstMaker->muDst()->primaryTracks() ;
    TObjArrayIter GetTracks(tracks) ;
    StMuTrack* ptrack ;
    // cout<<"hey 1"<<endl;
    while ( ( ptrack = (StMuTrack*)GetTracks.Next() ) )
      {
	if (ptrack->idTruth() <= 0 || ptrack->idTruth() > NoMuMcTracks) {//idTruth(): MC track id. 
	  //cout << "Illegal idTruth " << ptrack->idTruth() << " The track is ignored" << endl;
	  continue;
	}
	StMuMcTrack *mcTrack = (StMuMcTrack *) MuMcTracks->UncheckedAt(ptrack->idTruth()-1);
	if (!mcTrack) {
	  LOG_WARN << "Inconsistency in mcArray(1), ignored" << endm;
	  continue;
	}
	if (mcTrack->Id() != ptrack->idTruth()) {
	  LOG_WARN << "Mismatched idTruth " << ptrack->idTruth() << " and mcTrack Id " <<  mcTrack->Id() 
		   << " this track is ignored" <<  endm;
	}
	Int_t idMcVx = mcTrack->IdVx();
	while (idMcVx != 1) {
	  StMuMcVertex *mcVertex = (StMuMcVertex *) MuMcVertices->UncheckedAt(idMcVx-1);
	  Int_t idMcTrack = mcVertex->IdParTrk();
	  if (! idMcTrack) break;
	  StMuMcTrack *mcTrackP = (StMuMcTrack *) MuMcTracks->UncheckedAt(idMcTrack-1);
	  idMcVx = mcTrackP->IdVx();
	  if (! idMcVx) break;
	}

	if (idMcVx != 1) continue; //this MC track is not eventually originated from PV

	if(mcTrack->GePid() != PID) continue;//k+: 11. k-: 12, proton: 14, anti-proton: 15, pi+: 8, pi-:9
	if(mcTrack->IdVx() != 1) {
	  LOG_WARN<<"mc track may not directly originate from PV!"<<endm;
	  continue;//27092022
	}
	if(ptrack->qaTruth()<50.) continue; //qaTruth(): MC track quality (percentage of hits coming from corresponding MC track) 
	// if(ptrack->nHits()<=15)continue;

	if(!(ptrack->nHitsFit() > nHitsFits_cut))continue;

	if(!(ptrack->nHitsDedx()>5)) continue;

	if(!( 1.0*(ptrack->nHitsFit()) / (ptrack->nHitsPoss()) >0.52)) continue;

	if(!(ptrack->dcaGlobal().mag() < dca_cut))continue;//Guannan

	if(ptrack->flag()<=0)continue;
	if(abs(ptrack->charge())!=1) continue;

	StThreeVectorF p = ptrack->p();

	// variables//
	E_P  = TMath::Sqrt(p.mag2() + MPROTON*MPROTON);

	y_P  = 0.5*TMath::Log( (E_P  + p.z()) / (E_P  - p.z()) );
	// cout<<"Proton, ref3 = "<<ref3<<", y_P = "<<y_P<<", pT = "<<p.perp()<<endl;
    // cout<<"hey 2"<<endl;

	if(mcTrack->GePid() == PID){
	  if(ptrack->charge() > 0){
	    if(PID == 14) {//P
	      bool shouldBreak = false;
	      for(int i_cent = 0 ; i_cent < Nocent ; i_cent++){
		for(int i_vz = 0 ; i_vz < 6 ; i_vz++){
		  if(mMuEvent->refMult() >= cent_ref[i_cent+1] && mMuEvent->refMult() < cent_ref[i_cent]) {
		    if(mMuEvent->primaryVertexPosition().z() >= vz[i_vz] && mMuEvent->primaryVertexPosition().z() < vz[i_vz+1]){
		      h2_y_pt_p[i_cent][i_vz]->Fill(y_P, p.perp()); 
    // cout<<"hey 3"<<endl;
		      shouldBreak = true;
		      break;
		    }//if(mMuEvent->primaryVertexPosition().z() >= vz[i_vz] && mMuEvent->primaryVertexPosition().z() < vz[i_vz+1]){
		  }//if(mMuEvent->refMult() >= cent_ref[i_cent+1] && mMuEvent->refMult() < cent_ref[i_cent]) {
		  if (shouldBreak) break;
		}//for(int i_vz = 0 ; i_vz < 6 ; i_vz++){
		if (shouldBreak) break;
	      }//for(int i_cent = 0 ; i_cent < Nocent ; i_cent++){
	    }//if(PID == 14) {
	  }//if(ptrack->charge() > 0)
	  else if(ptrack->charge() < 0){
	    if(PID == 15) {//P
	      bool shouldBreak = false;
	      for(int i_cent = 0 ; i_cent < Nocent ; i_cent++){
		for(int i_vz = 0 ; i_vz < 6 ; i_vz++){
		  if(mMuEvent->refMult() >= cent_ref[i_cent+1] && mMuEvent->refMult() < cent_ref[i_cent]) {
		    if(mMuEvent->primaryVertexPosition().z() >= vz[i_vz] && mMuEvent->primaryVertexPosition().z() < vz[i_vz+1]){
		      h2_y_pt_m[i_cent][i_vz]->Fill(y_P, p.perp()); 
		      shouldBreak = true;
		      break;
		    }//if(mMuEvent->primaryVertexPosition().z() >= vz[i_vz] && mMuEvent->primaryVertexPosition().z() < vz[i_vz+1]){
		  }//if(mMuEvent->refMult() >= cent_ref[i_cent+1] && mMuEvent->refMult() < cent_ref[i_cent]) {
		  if (shouldBreak) break;
		}//for(int i_vz = 0 ; i_vz < 6 ; i_vz++){
		if (shouldBreak) break;
	      }//for(int i_cent = 0 ; i_cent < Nocent ; i_cent++){
	    }//if(PID == 15)
	  }//else if(ptrack->charge() < 0){
	}//end of mcTrack->GePid() == PID statement 
      }//while ( ( ptrack = (StMuTrack*)GetTracks.Next() ) )...{

    ///////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////

    Int_t nMc = 0;
    // Loop for MC tracks
    for(Int_t itrk=0; itrk<NoMuMcTracks; itrk++){
      StMuMcTrack *mcTrack = (StMuMcTrack *) MuMcTracks->UncheckedAt(itrk);
      if (! mcTrack) continue;

      // Select only Triggered Mc Vertex, i.e. the MC track should originate from PV (IdVx=1)
      Int_t IdVx = mcTrack->IdVx();
      if (IdVx != 1) continue;

      // variables mc//
      E_P_mc  = TMath::Sqrt(mcTrack->Pxyz().mag2() + MPROTON*MPROTON);

      y_P_mc  = 0.5*TMath::Log( (E_P_mc  + mcTrack->Pxyz().z()) / (E_P_mc  - mcTrack->Pxyz().z()) );
     
      const int Gid = mcTrack->GePid();


      nMc++;  // # of MC tracks
      if(Gid==PID){//k+: 11. k-: 12, proton: 14, anti-proton: 15, pi+: 8, pi-:9

	if(mcTrack->Charge() > 0){
	  if(PID == 14) {//P
	    bool shouldBreak = false;
	    for(int i_cent = 0 ; i_cent < Nocent ; i_cent++){
	      for(int i_vz = 0 ; i_vz < 6 ; i_vz++){
		if(mMuEvent->refMult() >= cent_ref[i_cent+1] && mMuEvent->refMult() < cent_ref[i_cent]) {
		  if(mMuEvent->primaryVertexPosition().z() >= vz[i_vz] && mMuEvent->primaryVertexPosition().z() < vz[i_vz+1]){
		    h2_y_pt_mc_p[i_cent][i_vz]->Fill(y_P_mc, mcTrack->Pxyz().perp()); 
		    shouldBreak = true;   
		    break;
		  }//if(mMuEvent->primaryVertexPosition().z() >= vz[i_vz] && mMuEvent->primaryVertexPosition().z() < vz[i_vz+1]){
		}//if(mMuEvent->refMult() >= cent_ref[i_cent+1] && mMuEvent->refMult() < cent_ref[i_cent]) {
		if (shouldBreak) break; 
	      }//for(int i_vz = 0 ; i_vz < 6 ; i_vz++){
	      if (shouldBreak) break; 
	    }//for(int i_cent = 0 ; i_cent < Nocent ; i_cent++){
	  }//if(PID == 14) {
	}//if(mcTrack->Charge() > 0){
	else if(mcTrack->Charge() < 0){
	  if(PID == 15) {//P
	    bool shouldBreak = false;
	    for(int i_cent = 0 ; i_cent < Nocent ; i_cent++){
	      for(int i_vz = 0 ; i_vz < 6 ; i_vz++){
		if(mMuEvent->refMult() >= cent_ref[i_cent+1] && mMuEvent->refMult() < cent_ref[i_cent]) {
		  if(mMuEvent->primaryVertexPosition().z() >= vz[i_vz] && mMuEvent->primaryVertexPosition().z() < vz[i_vz+1]){
		    h2_y_pt_mc_m[i_cent][i_vz]->Fill(y_P_mc, mcTrack->Pxyz().perp()); 
		    shouldBreak = true;   
		    break;
		  }//if(mMuEvent->primaryVertexPosition().z() >= vz[i_vz] && mMuEvent->primaryVertexPosition().z() < vz[i_vz+1]){
		}//if(mMuEvent->refMult() >= cent_ref[i_cent+1] && mMuEvent->refMult() < cent_ref[i_cent]) {
		if (shouldBreak) break; 
	      }//for(int i_vz = 0 ; i_vz < 6 ; i_vz++){
	      if (shouldBreak) break; 
	    }//for(int i_cent = 0 ; i_cent < Nocent ; i_cent++){
	  }//if(PID == 15) {
	}//else if(mcTrack->Charge() < 0){
      }//if(Gid==PID){
      else {
	LOG_WARN << "Gid: "<<Gid<<" in Ev. "<<i<<endm;
      }
    }//for(Int_t itrk=0; itrk<NoMuMcTracks; itrk++){
  }//while (i <= nEvents && istat != 2) {
  for(int i_cent = 0 ; i_cent < Nocent ; i_cent++){
    for(int i_vz = 0 ; i_vz < 2 ; i_vz++){
      h2_y_pt_eff_p[i_cent][i_vz]->Divide(h2_y_pt_p[i_cent][i_vz], h2_y_pt_mc_p[i_cent][i_vz], 1., 1., "B");
      h2_y_pt_eff_m[i_cent][i_vz]->Divide(h2_y_pt_m[i_cent][i_vz], h2_y_pt_mc_m[i_cent][i_vz], 1., 1., "B");
    }//for(int i_cent = 0 ; i_cent < Nocent ; i_cent++)
  }//for(int i_cent = 0 ; i_cent < Nocent ; i_cent++){

  if (nEvents > 1) chain -> Finish() ;

  if(tags_output!=NULL) tags_output -> Write() ;
  if(tags_output!=NULL) tags_output -> Close() ;
  //flush(tags_output);
  delete tags_output;

  // Cleanup
  delete chain ;
}
