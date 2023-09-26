#include <fstream>
#include <vector>
#include <algorithm>

#include "StQAMaker.h"

#include "StPicoEvent/StPicoDst.h"
#include "StPicoEvent/StPicoTrack.h"
#include "StPicoDstMaker/StPicoDstMaker.h"
#include "StPicoEvent/StPicoEvent.h"
#include "StPicoEvent/StPicoBTofPidTraits.h"
#include "StBTofUtil/tofPathLength.hh"
#include "StThreeVectorF.hh"
#include "Stiostream.h"
#include "PhysicalConstants.h"
#include "phys_constants.h"

#include "pileup/ref3StPicoEvtpileup.h"
#include "pileup/ref3StPicoEvtBetaEtapileup.h"

#include <TMath.h>
#include "TFile.h"
#include "TTree.h"

#include "RunNo.h"

ClassImp(StQAMaker)

StQAMaker::StQAMaker(const char* name, StPicoDstMaker *picoMaker, const char* outName, const char* jobID)
  : StMaker(name){
    mPicoDstMaker = picoMaker;
    mPicoDst = 0;
    TString fileName = "";
    fileName.Append(outName);
    fileName.Append(jobID);
    OutDir = outName;
    mOutputName = fileName+ "_tree.root";
  }

StQAMaker::~StQAMaker(){}

int StQAMaker::Init()
{
  EventID=0;

  outfile = new TFile(mOutputName,"RECREATE");
  t_event = new TTree("t_event", "QA. Filled in event level");
  //event level
  t_event->Branch("ZDCx_t", &ZDCx_t, "ZDCx/F");
  t_event->Branch("vz_t", &vz_t, "vz/F");
  t_event->Branch("vpdz_t", &vpdz_t, "vpdz/F");
  t_event->Branch("nBTOFMatch_t", &nBTOFMatch_t, "nBTOFMatch/I");
  t_event->Branch("refMult3StPicoEvt_t", &refMult3StPicoEvt_t, "refMult3StPicoEvt/F");
  t_event->Branch("beta_eta1_t", &beta_eta1_t, "beta_eta1_t/I");
  t_event->Branch("avgDCAxy_t", &avgDCAxy_t, "avgDCAxy_t[9]/F");
  t_event->Branch("avgDCAz_t", &avgDCAz_t, "avgDCAz_t[9]/F");
  //track level
  t_event->Branch("dca_t", &dca_t);
  t_event->Branch("nHitsFit_t", &nHitsFit_t);
  t_event->Branch("nSP_t", &nSP_t);
  t_event->Branch("m2_t", &m2_t);
  t_event->Branch("charge_t", &charge_t);
  t_event->Branch("yP_t", &yP_t);
  t_event->Branch("pT_t", &pT_t);
  t_event->Branch("dedx_t", &dedx_t);

  return kStOK;
}

int StQAMaker::Make() {

  if(!mPicoDstMaker) {
    LOG_WARN << " No PicoDstMaker! Skip! " << endm;
    return kStWarn;
  }

  mPicoDst = mPicoDstMaker->picoDst();

  if(!mPicoDst) {
    LOG_WARN << " No PicoDst! Skip! " << endm;
    return kStWarn;
  }

  mPicoEvent = (StPicoEvent*) mPicoDst->event();

  if(!mPicoEvent) return 0; 
  if(!(mPicoEvent->isTrigger(600001) || mPicoEvent->isTrigger(600011) || mPicoEvent->isTrigger(600021) || mPicoEvent->isTrigger(600031))) return 0;

  CurrRun = mPicoEvent->runId();
  //check if runNo is for Zr or Ru
  bool IsRunZr = false;
  bool IsRunRu = false;
  for(int i_runNo = 0 ; i_runNo < nRunId_Zr ; i_runNo++){//Zr
    if (CurrRun != IsobarRunId_Zr[i_runNo]) continue;
    else if (CurrRun == IsobarRunId_Zr[i_runNo]) {
      IsRunZr = true; NameRuZr = "Zr"; break;}
  }
  for(int i_runNo = 0 ; i_runNo < nRunId_Ru ; i_runNo++){//Ru
    if (CurrRun != IsobarRunId_Ru[i_runNo]) continue;
    else if (CurrRun == IsobarRunId_Ru[i_runNo]) {
      IsRunRu = true;  NameRuZr ="Ru"; break;}
  }
  if(IsRunZr == false && IsRunRu == false) {
    abort();}
  else if(IsRunZr == true && IsRunRu == true) {
    abort();}

  //event level
  //variables
  int centrality_ref3[9];
  if(NameRuZr == "Ru"){
    centrality_ref3[0] = 441;
    centrality_ref3[1] = 369;
    centrality_ref3[2] = 259;
    centrality_ref3[3] = 179;
    centrality_ref3[4] = 119;
    centrality_ref3[5] = 76;
    centrality_ref3[6] = 46;
    centrality_ref3[7] = 27;
    centrality_ref3[8] = 15;
  }
  else if(NameRuZr == "Zr"){
    centrality_ref3[0] = 437;
    centrality_ref3[1] = 364;
    centrality_ref3[2] = 253;
    centrality_ref3[3] = 172;
    centrality_ref3[4] = 113;
    centrality_ref3[5] = 72;
    centrality_ref3[6] = 43;
    centrality_ref3[7] = 25;
    centrality_ref3[8] = 14;
  }
  TVector3 vertex3 = mPicoEvent->primaryVertex();
  float bField = mPicoEvent->bField();;

  double ZDCx = 0.;

  int refMult3StPicoEvt = 0;

  if(!(TMath::Sqrt( TMath::Power((vertex3.X() + 0.), 2) + TMath::Power((vertex3.Y() + 0.), 2)) < 2.)) return 0;
  if(!(vertex3.Z() > -35. && vertex3.Z() < 25.)) return 0;
  if(!(TMath::Abs(vertex3.Z() - mPicoEvent->vzVpd()) < 3.)) return 0;

  //track level
  //variables
  int nPrimaryTrack = 0;
  int charge = 0;
  StPicoPhysicalHelix helix;
  float dca = 0.;
  float sgnDCAxy = 0.;
  float sgnDCAz = 0.;

  int nPrimaryTrack_Cut[9];
  int counterP[9];
  int counterAP[9];
  float avgDCAxy[9];
  float avgDCAz[9];

  for(int i_cent = 0 ; i_cent < 9 ; i_cent++){
    nPrimaryTrack_Cut[i_cent] = 0;
    counterP[i_cent] = 0;
    counterAP[i_cent] = 0;
    avgDCAxy[i_cent] = 0.;
    avgDCAz[i_cent] = 0.;
  }

  int nHitsFit = 0;
  int nHitsMax = 0;
  float nHitsRatio = 0.;
  int nHitsDedx = 0;
  float dEdx = 0.;
  TVector3 momentum;
  float E_P = 0.; 
  float eta = 0.;
  float y_P = 0.;
  float nSigmaProton = 0.;

  int pid = 0;

  //TOF
  StPicoBTofPidTraits *bTOFpid;
  int bTOFindex = 0;
  int bTOFmatchFlag = 0;
  float bTOFyLocal = 0.;
  float bTOFzLocal = 0.;
  float bTOFbeta = 0.;
  float m2 = 0.;
  int bTOFmult = mPicoEvent->btofTrayMultiplicity(); //No. of hits in TOF trays.
  int nBTOFMatch = mPicoEvent->nBTOFMatch(); //No. of hits in TOF trays.
  int beta_eta1 = 0;

  //cuts and booleans
  bool eta_cut = false;
  bool PnS = false;
  bool PPt = false;
  bool PPtTOF = false;
  bool PM2 = false;
  
  //Tree branches are filled in event level.
  //Initialize track variables
  dca_t.clear();
  nHitsFit_t.clear();
  nSP_t.clear();
  m2_t.clear();
  charge_t.clear();
  yP_t.clear();
  pT_t.clear();
  dedx_t.clear();

  ZDCx = mPicoEvent->ZDCx();
  refMult3StPicoEvt = mPicoEvent->refMult3();

  //track level only for beta_eta_1 calculation
  int nTracks = mPicoDst->numberOfTracks();
  for(int i=0;i<nTracks;i++){
    mPicoTrack = mPicoDst->track(i);
    if(!mPicoTrack) continue;
    if(!mPicoTrack->isPrimary()) continue;
    nPrimaryTrack++;

    //DCA
    dca =  mPicoTrack->gDCA(vertex3.X(), vertex3.Y(), vertex3.Z());

    //nhitsfit
    nHitsFit = mPicoTrack->nHitsFit();

    //momentum
    momentum = mPicoTrack->pMom();

    //eta
    eta = momentum.PseudoRapidity();

    //TOF
    bTOFindex = mPicoTrack->bTofPidTraitsIndex();
    bTOFmatchFlag = 0;
    bTOFbeta = 0.;
    bTOFyLocal = -999.;
    bTOFzLocal = -999.;
    if(bTOFindex>=0){
      bTOFpid = mPicoDst->btofPidTraits(bTOFindex);    
      bTOFmatchFlag = bTOFpid->btofMatchFlag();
      if(bTOFpid) {
  	bTOFbeta = bTOFpid->btofBeta();
  	bTOFyLocal = bTOFpid->btofYLocal();
  	bTOFzLocal = bTOFpid->btofZLocal();
      }
    }

    if(!(bTOFmatchFlag > 0 && bTOFbeta > 0 && TMath::Abs(bTOFyLocal) < 1.6 && TMath::Abs(bTOFzLocal) < 3.0)){
      bTOFbeta = -999.;
    }
    if(bTOFbeta > 0.1 && TMath::Abs(eta) < 1 && dca < 3 && nHitsFit > 10) beta_eta1++;
  }//track loop for beta_eta1 ends

  // track level
  nTracks = mPicoDst->numberOfTracks();
  for(int i=0;i<nTracks;i++){
    mPicoTrack = mPicoDst->track(i);
    if(!mPicoTrack) continue;
    if(!mPicoTrack->isPrimary()) continue;
    nPrimaryTrack++;

    //charge
    charge = mPicoTrack->charge();

    //DCA
    dca =  mPicoTrack->gDCA(vertex3.X(), vertex3.Y(), vertex3.Z());
    helix = mPicoTrack->helix(bField);
    sgnDCAxy = helix.geometricSignedDistance(vertex3.X(), vertex3.Y());
    sgnDCAz = mPicoTrack->gDCAz(vertex3.Z());

    //nhitsfit
    nHitsFit = mPicoTrack->nHitsFit();
    //nHitsMax
    nHitsMax = mPicoTrack->nHitsMax();
    //nHitsRatio
    nHitsRatio = 1.*nHitsFit/nHitsMax;
    //nHitsDedx
    nHitsDedx = mPicoTrack->nHitsDedx();
    //dEdx
    dEdx = mPicoTrack->dEdx();

    //momentum
    momentum = mPicoTrack->pMom();
    E_P = TMath::Sqrt(momentum.Mag2() + MPROTON*MPROTON);

    //eta
    eta = momentum.PseudoRapidity();

    //eta cut
    eta_cut = TMath::Abs(eta) < 0.5;//BES-I

    //y
    //collider mode
    y_P = 0.5*TMath::Log( (E_P + momentum.Pz()) / (E_P - momentum.Pz()) );

    //nSigma
    nSigmaProton = mPicoTrack->nSigmaProton();

    //TOF
    bTOFindex = mPicoTrack->bTofPidTraitsIndex();
    bTOFmatchFlag = 0;
    bTOFbeta = 0.;
    bTOFyLocal = -999.;
    bTOFzLocal = -999.;
    if(bTOFindex>=0){
      bTOFpid = mPicoDst->btofPidTraits(bTOFindex);    
      bTOFmatchFlag = bTOFpid->btofMatchFlag();
      if(bTOFpid) {
  	bTOFbeta = bTOFpid->btofBeta();
  	bTOFyLocal = bTOFpid->btofYLocal();
  	bTOFzLocal = bTOFpid->btofZLocal();
      }
    }

    m2 = momentum.Mag2()*( 1./(bTOFbeta*bTOFbeta) - 1 );

    if(!(bTOFmatchFlag > 0 && bTOFbeta > 0 && TMath::Abs(bTOFyLocal) < 1.6 && TMath::Abs(bTOFzLocal) < 3.0)){
      bTOFbeta = -999.;
      m2 = -999.;
    }
    if(bTOFbeta > 0.1 && TMath::Abs(eta) < 1 && dca < 3 && nHitsFit > 10) beta_eta1++;

    //nSigma cuts
    PnS = TMath::Abs(nSigmaProton) < 2.5;//highest limit for sys. unc. studies

    //pT cuts for TOF usage
    PPtTOF = momentum.Perp() < 0.8;

    //mass cuts
    PM2 = m2 > 0.5 && m2 < 1.3;//highest limit for sys. unc. studies

    if(!(nHitsFit > 10)) continue;//lowest limit for sys. unc. studies
    if(!(nHitsDedx > 5)) continue;
    if(!(nHitsRatio > 0.52)) continue;
    if(!(TMath::Abs(dca) < 1.2)) continue;//highest limit for sys. unc. studies

    if(ref3StPicoEvtisNotPileUp(nBTOFMatch, refMult3StPicoEvt, NameRuZr)
       &&
       ref3StPicoEvtBetaEtapileup(refMult3StPicoEvt, beta_eta1, NameRuZr)
       ) {
      if(refMult3StPicoEvt >= centrality_ref3[0] && refMult3StPicoEvt < 700){
	nPrimaryTrack_Cut[0]++;
	avgDCAxy[0] += sgnDCAxy;
	avgDCAz[0] += sgnDCAz;
      }
      else if(refMult3StPicoEvt >= centrality_ref3[1] && refMult3StPicoEvt < centrality_ref3[0]){
	nPrimaryTrack_Cut[1]++;
	avgDCAxy[1] += sgnDCAxy;
	avgDCAz[1] += sgnDCAz;
      }
      else if(refMult3StPicoEvt >= centrality_ref3[2] && refMult3StPicoEvt < centrality_ref3[1]){
	nPrimaryTrack_Cut[2]++;
	avgDCAxy[2] += sgnDCAxy;
	avgDCAz[2] += sgnDCAz;
      }
      else if(refMult3StPicoEvt >= centrality_ref3[3] && refMult3StPicoEvt < centrality_ref3[2]){
	nPrimaryTrack_Cut[3]++;
	avgDCAxy[3] += sgnDCAxy;
	avgDCAz[3] += sgnDCAz;
      }
      else if(refMult3StPicoEvt >= centrality_ref3[4] && refMult3StPicoEvt < centrality_ref3[3]){
	nPrimaryTrack_Cut[4]++;
	avgDCAxy[4] += sgnDCAxy;
	avgDCAz[4] += sgnDCAz;
      }
      else if(refMult3StPicoEvt >= centrality_ref3[5] && refMult3StPicoEvt < centrality_ref3[4]){
	nPrimaryTrack_Cut[5]++;
	avgDCAxy[5] += sgnDCAxy;
	avgDCAz[5] += sgnDCAz;
      }
      else if(refMult3StPicoEvt >= centrality_ref3[6] && refMult3StPicoEvt < centrality_ref3[5]){
	nPrimaryTrack_Cut[6]++;
	avgDCAxy[6] += sgnDCAxy;
	avgDCAz[6] += sgnDCAz;
      }
      else if(refMult3StPicoEvt >= centrality_ref3[7] && refMult3StPicoEvt < centrality_ref3[6]){
	nPrimaryTrack_Cut[7]++;
	avgDCAxy[7] += sgnDCAxy;
	avgDCAz[7] += sgnDCAz;
      }
      else if(refMult3StPicoEvt >= centrality_ref3[8] && refMult3StPicoEvt < centrality_ref3[7]){
	nPrimaryTrack_Cut[8]++;
	avgDCAxy[8] += sgnDCAxy;
	avgDCAz[8] += sgnDCAz;
      }
    }//pileup

    //proton
    if(
       (PnS)
       &&
       (
  	(PPtTOF)
  	||
  	((!PPtTOF) && PM2 && bTOFbeta > 0.1)
  	)
       ) {
      pid = 1;
      dca_t.push_back(dca);
      nHitsFit_t.push_back(nHitsFit);
      nSP_t.push_back(nSigmaProton);
      m2_t.push_back(m2);
      charge_t.push_back(charge);
      yP_t.push_back(y_P);
      pT_t.push_back(momentum.Perp());
      dedx_t.push_back(dEdx);
    }//end of proton if

  }//track loop ends

  //set tree variable
  //event level
  ZDCx_t = ZDCx;
  vz_t = vertex3.Z();
  vpdz_t = mPicoEvent->vzVpd();
  nBTOFMatch_t = nBTOFMatch;
  refMult3StPicoEvt_t = refMult3StPicoEvt;

  beta_eta1_t = beta_eta1;

  for(int i_cent = 0 ; i_cent < 9 ; i_cent++){
    if(nPrimaryTrack_Cut[i_cent] != 0){
      avgDCAxy_t[i_cent] = avgDCAxy[i_cent]/nPrimaryTrack_Cut[i_cent];
      avgDCAz_t[i_cent] = avgDCAz[i_cent]/nPrimaryTrack_Cut[i_cent];
    }
    else{
      avgDCAxy_t[i_cent] = -999;
      avgDCAz_t[i_cent] = -999;
    }
  }
  if(beta_eta1 == 0) return 0;

  //Fill tree in event level
  t_event->Fill();

  EventID++;
  return kStOK;
}

void StQAMaker::Clear(Option_t *opt) {}

int StQAMaker::Finish() {
  outfile->cd();
  outfile->Write();
  outfile->Close();

  return kStOK;
}
