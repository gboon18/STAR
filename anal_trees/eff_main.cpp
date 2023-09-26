#include <iostream>
#include <fstream>

#include "TROOT.h"
#include "TFile.h"
#include "TCutG.h"
#include "TTree.h"
#include "TChain.h"
#include "TF1.h"
#include "TRandom.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TMath.h"

#include "RunNo.h"
#include "StDetectorEfficiency.h"
#include "Mean.h"

#include "pileup/ref3StPicoEvtpileup.h"
#include "pileup/ref3StPicoEvtBetaEtapileup.h"
#include "multCorr/ref3StPicoEvt_lumiCorr.h"                                                                                                                                                                                                                                                                                                     
#include "multCorr/ref3StPicoEvt_vzCorr.h"   

#include <ctime> //to cout run time 

using namespace std;

int main(int argc, char** argv){

  if(argc != 12) {cout<<"Need 11 arguments!: ./job/Data/runNo/file.list dca_cut, nhitsfit_cut, nsp_cut, m2low_cut, m2up_cut, ptmax_cut, ymax_cut, detefflow_err, deteffhigh_err, test_flag"<<endl; return -1;}

  // current date/time based on current system
  time_t now = time(0);
  
  //Get them tree
  TChain *t_data = new TChain("t_event");

  ifstream myfile;
  myfile.open(argv[1]);
  int runNo = 0;
  while(myfile>>runNo){cout<<"The runNo is "<<runNo<<endl;}
  myfile.close();

  if(atoi(argv[11]) == 0) t_data->Add(Form("/star/u/hsko/pwg/anal/Coll/isobar/ZrZrRuRu200_2018/charge/QA_tree_light2/output/net_proton/10032023/10032023_1/output/tree/%d*_tree.root", runNo));
  else if(atoi(argv[11]) == 1) t_data->Add("../make_trees/QA_test_01_tree.root");
  else {cout<<"Improper test_flag, 0: real run, 1: test run"<<endl; return 0;}

  //check if runNo is for Zr or Ru
  bool IsRunZr = false;
  bool IsRunRu = false;
  string NameRuZr;
  const char* NameRuZr_c;
  for(int i_runNo = 0 ; i_runNo < nRunId_Zr ; i_runNo++){//Zr
    if (runNo != IsobarRunId_Zr[i_runNo]) continue;
    else if (runNo == IsobarRunId_Zr[i_runNo]) {IsRunZr = true; NameRuZr = "Zr"; NameRuZr_c = NameRuZr.c_str(); cout<<Form("runNo %d is %s run", runNo, NameRuZr_c)<<endl; break;}
  }
  for(int i_runNo = 0 ; i_runNo < nRunId_Ru ; i_runNo++){//Ru
    if (runNo != IsobarRunId_Ru[i_runNo]) continue;
    else if (runNo == IsobarRunId_Ru[i_runNo]) {IsRunRu = true;  NameRuZr ="Ru"; NameRuZr_c = NameRuZr.c_str(); cout<<Form("runNo %d is %s run", runNo, NameRuZr_c)<<endl; break;}
  }
  if(IsRunZr == false && IsRunRu == false) {cout<<Form("CANNOT FIND runNo %d's identity!! Zr = false RU = false", runNo)<<endl; abort();}
  else if(IsRunZr == true && IsRunRu == true) {cout<<Form("CANNOT FIND runNo %d's identity!! Zr = true RU = true", runNo)<<endl; abort();}
  t_data->SetBranchStatus("*", 0);

  //event level
  t_data->SetBranchStatus("ZDCx_t", 1);
  t_data->SetBranchStatus("vz_t", 1);
  t_data->SetBranchStatus("vpdz_t", 1);
  t_data->SetBranchStatus("nBTOFMatch_t", 1);
  t_data->SetBranchStatus("refMult3StPicoEvt_t", 1);
  t_data->SetBranchStatus("beta_eta1_t", 1);

  // t_data->SetBranchStatus("avgDCAxy_t", 1);
  // t_data->SetBranchStatus("avgDCAz_t", 1);

  //track level
  t_data->SetBranchStatus("dca_t", 1);
  t_data->SetBranchStatus("nHitsFit_t", 1);
  t_data->SetBranchStatus("nSP_t", 1);
  t_data->SetBranchStatus("m2_t", 1);
  t_data->SetBranchStatus("charge_t", 1);
  t_data->SetBranchStatus("yP_t", 1);
  t_data->SetBranchStatus("pT_t", 1);
  t_data->SetBranchStatus("dedx_t", 1);

  //event level
  //pile-up removed
  float ZDCx_t; t_data->SetBranchAddress("ZDCx_t", &ZDCx_t);
  float vz_t; t_data->SetBranchAddress("vz_t", &vz_t);
  float vpdz_t; t_data->SetBranchAddress("vpdz_t", &vpdz_t);
  int nBTOFMatch_t; t_data->SetBranchAddress("nBTOFMatch_t", &nBTOFMatch_t);
  float refMult3StPicoEvt_tt; t_data->SetBranchAddress("refMult3StPicoEvt_t", &refMult3StPicoEvt_tt);
  int beta_eta1_t; t_data->SetBranchAddress("beta_eta1_t", &beta_eta1_t);
  
  //track level
  vector<float> *dca_t = 0; TBranch *dca_b = 0; t_data->SetBranchAddress("dca_t", &dca_t, &dca_b);
  vector<int> *nHitsFit_t = 0; TBranch *nHitsFit_b = 0; t_data->SetBranchAddress("nHitsFit_t", &nHitsFit_t, &nHitsFit_b);
  vector<float> *nSP_t = 0; TBranch *nSP_b = 0; t_data->SetBranchAddress("nSP_t", &nSP_t, &nSP_b);
  vector<float> *m2_t = 0; TBranch *m2_b = 0; t_data->SetBranchAddress("m2_t", &m2_t, &m2_b);
  vector<int> *charge_t = 0; TBranch *charge_b = 0; t_data->SetBranchAddress("charge_t", &charge_t, &charge_b);
  vector<float> *yP_t = 0; TBranch *yP_b = 0; t_data->SetBranchAddress("yP_t", &yP_t, &yP_b);
  vector<float> *pT_t = 0; TBranch *pT_b = 0; t_data->SetBranchAddress("pT_t", &pT_t, &pT_b);
  vector<float> *dedx_t = 0; TBranch *dedx_b = 0;  t_data->SetBranchAddress("dedx_t", &dedx_t, &dedx_b);

  int maxMult = 1000;

  StDetectorEfficiency *DetEff = new StDetectorEfficiency();

  float dca_cut = atof(argv[2]);
  int nhitsfit_cut = atoi(argv[3]);
  float nsp_cut = atof(argv[4]);
  float m2low_cut = atof(argv[5]);
  float m2up_cut = atof(argv[6]);
  cout<<"dca_cut = "<<dca_cut<<endl;
  cout<<"nhitsfit_cut = "<<nhitsfit_cut<<endl;
  cout<<"nsp_cut = "<<nsp_cut<<endl;
  cout<<"m2low_cut = "<<m2low_cut<<endl;
  cout<<"m2up_cut = "<<m2up_cut<<endl;

  float ptmax_cut = atof(argv[7]);
  float ymax_cut = atof(argv[8]);
  cout<<"ptmax_cut = "<<ptmax_cut<<endl;
  cout<<"ymax_cut = "<<ymax_cut<<endl;

  double detefflow_err = atof(argv[9]);
  double deteffhigh_err = atof(argv[10]);
  cout<<"detefflow_err = "<<detefflow_err<<endl;
  cout<<"deteffhigh_err = "<<deteffhigh_err<<endl;

  DetEff->Init_DetEff(Form("/star/u/hsko/pwg/anal/Coll/isobar/ZrZrRuRu200_2018/charge/sys_unc/det_eff/27092022/23122022_1_parameterize/TPC/eff_pt_dep_cent_fit_oneybin_Proton_%s_dca_%d_nhitsfit_%d.txt", NameRuZr_c, (int) (10*dca_cut), nhitsfit_cut), Form("/star/u/hsko/pwg/anal/Coll/isobar/ZrZrRuRu200_2018/charge/sys_unc/det_eff/27092022/23122022_1_parameterize/TPC/eff_pt_dep_cent_fit_oneybin_AntiProton_%s_dca_%d_nhitsfit_%d.txt", NameRuZr_c, (int) (10*dca_cut), nhitsfit_cut), Form("/star/u/hsko/pwg/anal/Coll/isobar/ZrZrRuRu200_2018/charge/sys_unc/det_eff/14022023/14022023_1_parameterize/TOF/eff_pt_dep_cent_fit_oneybin_Proton_%s_dca_%1.1f_nhf_%d_nsp_%1.1f.txt", NameRuZr_c, dca_cut, nhitsfit_cut, nsp_cut), Form("/star/u/hsko/pwg/anal/Coll/isobar/ZrZrRuRu200_2018/charge/sys_unc/det_eff/14022023/14022023_1_parameterize/TOF/eff_pt_dep_cent_fit_oneybin_AntiProton_%s_dca_%1.1f_nhf_%d_nsp_%1.1f.txt", NameRuZr_c, dca_cut, nhitsfit_cut, nsp_cut), NameRuZr_c);

  Mean *mean = new Mean(maxMult);

  //set variables
  int Nevt = t_data->GetEntries();
  cout<<"Number of event entries: "<<Nevt<<endl;

  double deteff = -2.;

  double refMult3StPicoEvt_t = 0.;
  double refMult3StPicoEvt_lumicorr = 0.;
  double refMult3StPicoEvt_vzlumicorr = 0.;

  // //A(start)
  // TF1* ref3_fc= new TF1("ref3_fc","pol6",-50,50);
  // ref3_fc->SetParameters(514.56,0.108917,-0.00478876,-1.11905e-05,5.34282e-06,3.09103e-08,-3.42707e-09);
  // TF1* lumino_fc= new TF1("lumino_fc","pol1",0,15000);
  // lumino_fc->SetParameters(175.001,-0.00022314);
  // //A(finish)

  for(int i_evt = 0 ; i_evt < Nevt ; i_evt++){//event by event
    t_data->GetEntry(i_evt);
    if(i_evt%100000 == 0) {
      cout<<Form("%d / %d", i_evt, Nevt)<<endl;
    }

    if(!(TMath::Abs(vz_t - vpdz_t) < 3.)) continue;

    if(!ref3StPicoEvtisNotPileUp(nBTOFMatch_t, refMult3StPicoEvt_tt, NameRuZr)) continue;
    if(!ref3StPicoEvtBetaEtapileup(refMult3StPicoEvt_tt, beta_eta1_t, NameRuZr)) continue;

    refMult3StPicoEvt_t = (double)refMult3StPicoEvt_tt - 0.5 + gRandom->Rndm();
    //A(start)
    refMult3StPicoEvt_lumicorr = ref3StPicoEvt_lumiCorr(ZDCx_t, refMult3StPicoEvt_t, NameRuZr);
    refMult3StPicoEvt_vzlumicorr = ref3StPicoEvt_vzCorr_vz0norm(vz_t, refMult3StPicoEvt_lumicorr, NameRuZr);
    // float ref3_zeropar=514.56;
    // float lumino_zeropar=172.639;
    // float Vz_factor=(ref3_zeropar/ref3_fc->Eval(vz_t));
    // float lumino_factor=(lumino_zeropar/lumino_fc->Eval(ZDCx_t));
    // refMult3StPicoEvt_vzlumicorr = 1.*round(( (refMult3StPicoEvt_t+gRandom->Rndm()) * Vz_factor  * lumino_factor )); //round the # to the nearest integer
    //A(finish)

    mean->Init();//initialize q_rs

    for(int i_trk = 0 ; (unsigned) i_trk < charge_t->size() ; i_trk++) {//track by track
      deteff = -2.;//initialize
      if(!(TMath::Abs(dca_t->at(i_trk)) < dca_cut)) continue;
      if(!(nHitsFit_t->at(i_trk) > nhitsfit_cut)) continue;
      if(
	 !(
	   (TMath::Abs(nSP_t->at(i_trk)) < nsp_cut)
	   &&
	   (
	    (pT_t->at(i_trk) < 0.8)
	    ||
	    ((!(pT_t->at(i_trk) < 0.8)) && (m2_t->at(i_trk) > m2low_cut && m2_t->at(i_trk) < m2up_cut))
	    )
	   )
	 ) continue;

      if(pT_t->at(i_trk) < 0.) continue;

      
      if(!(pT_t->at(i_trk) < ptmax_cut)) continue;
      if(!(TMath::Abs(yP_t->at(i_trk)) < ymax_cut)) continue;

      deteff = DetEff->GetEff(1/*pid*/, charge_t->at(i_trk), pT_t->at(i_trk), yP_t->at(i_trk), m2_t->at(i_trk), refMult3StPicoEvt_t, detefflow_err, deteffhigh_err);
      if(deteff == -1) return -1;
      if(deteff == -2) continue;
      mean->TrackCorr(charge_t->at(i_trk), 1/*pid*/, deteff);//Efficiency corected
      mean->TrackUnCorr(charge_t->at(i_trk), 1/*pid*/, deteff);//Efficiency uncorrected

    }//end of track loop

    mean->CalculateMeanRefMult3StPicoEvt(refMult3StPicoEvt_vzlumicorr);//Efficiency corrected, refmult3 corrected
  }//end of event loop

  // //A(start)
  // delete ref3_fc;
  // delete lumino_fc;
  // //A(finish)

  if(atoi(argv[11]) == 0) mean->WriteRefMult3StPicoEvt(Form("./test_output/%s_mTerms_f_%d_dca_%d_nhitsfit_%d_nsp_%d_m2low_%d_m2up_%d_ptmax_%d_ymax_%d_detefflow_err_%d_deteffhigh_err_%d.root", NameRuZr_c, runNo, (int) (10*dca_cut), nhitsfit_cut, (int) (10*nsp_cut), (int) (100*m2low_cut), (int) (100*m2up_cut), (int) (10*ptmax_cut), (int) (10*ymax_cut), (int) (100*detefflow_err), (int) (100*deteffhigh_err)));//Saving only the efficiency corrected, refmult3 corrected
  else if(atoi(argv[11]) == 1) mean->WriteRefMult3StPicoEvt(Form("./test_output/%s_test_dca_%d_nhitsfit_%d_nsp_%d_m2low_%d_m2up_%d_ptmax_%d_ymax_%d_detefflow_err_%d_deteffhigh_err_%d.root", NameRuZr_c, (int) (10*dca_cut), nhitsfit_cut, (int) (10*nsp_cut), (int) (100*m2low_cut), (int) (100*m2up_cut), (int) (10*ptmax_cut), (int) (10*ymax_cut), (int) (100*detefflow_err), (int) (100*deteffhigh_err)));//Saving only the efficiency corrected, refmult3 corrected


  t_data->ResetBranchAddresses();
  time_t then = time(0);
  time_t diff = then - now;
  char* dt = ctime(&diff);
  tm* gmtm = gmtime(&diff);
  dt = asctime(gmtm);
  cout << "****************************************** " << endl;
  cout << "It took :"<< dt <<"for the job to be done."  << endl;
  cout << "****************************************** " << endl;
  return 0;
}
