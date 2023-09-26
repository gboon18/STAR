#ifndef STAR_picoMaker
#define STAR_picoMaker
#include "StMaker.h"
#include "StarClassLibrary/StThreeVectorF.hh"
#include "StarClassLibrary/StThreeVectorD.hh"
#include "TString.h"
#include "TVector3.h"

class StPicoBTofPidTraits;
class StPicoDst;
class StPicoTrack;
class StPicoEvent;
class StPicoDstMaker;
class StEpdUtil;
class TFile;
class TTree;
class TDirectory;

class StQAMaker : public StMaker {
public:
  StQAMaker(const char *name, StPicoDstMaker *picoMaker, const char *outName = "qa", const char *jobID = "01");
  virtual ~StQAMaker();

  virtual int Init();
  virtual int Make();
  virtual void  Clear(Option_t *opt="");
  virtual int Finish();
private:
  StPicoDstMaker *mPicoDstMaker;
  StPicoDst      *mPicoDst;
  StPicoEvent    *mPicoEvent;
  StPicoTrack    *mPicoTrack;

  int CurrRun=0;
  int EventID=0;

  TString mOutputName;
  TFile *outfile;
  const char* OutDir;

  string NameRuZr;
  TString mMeanName;

  //GeV
  const float MELECTRON  = 0.000511;
  const float MMUON  = 0.105658;
  const float MPION  = 0.13957;
  const float MKAON  = 0.493677;
  const float MPROTON  = 0.93827;

  //Save in tree
  //Filled in event level
  float ZDCx_t;
  float vz_t;
  float vpdz_t;
  int nBTOFMatch_t;
  float refMult3StPicoEvt_t;
  int beta_eta1_t;
  float avgDCAxy_t[9];
  float avgDCAz_t[9];

  //Filled in track level
  vector<float> dca_t;
  vector<int> nHitsFit_t;
  vector<float> nSP_t;
  vector<float> m2_t;
  vector<int> charge_t;
  vector<float> yP_t;
  vector<float> pT_t;
  vector<float> dedx_t;

  //Filled in event level.
  TTree *t_event;

  ClassDef(StQAMaker,1)
};

#endif
