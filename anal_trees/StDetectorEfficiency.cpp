#include <iostream>
#include <fstream>
#include "StDetectorEfficiency.h"

// #include "TApplication.h"
#include "TFile.h"
// #include "TH2D.h"
#include "TF1.h"
// //29072021(start)
// //Temp while TPC eff map res is low
// #include "TGraph2D.h"
// //29072021(finish)

#include "TGraphErrors.h"//04082022
#include "TGraph.h"//13082022
#include "TH1D.h"//13082022

using namespace std;

StDetectorEfficiency::StDetectorEfficiency()
{
}

StDetectorEfficiency::~StDetectorEfficiency(){

  for(int i_cent = 0 ; i_cent < ncent ; i_cent++){
    delete h1_y_pt_eff_tpc_pP[i_cent];
    delete h1_y_pt_eff_tpc_pM[i_cent];
    delete h1_y_pt_eff_tof_pP[i_cent];
    delete h1_y_pt_eff_tof_pM[i_cent];
  }

  delete gr_eff_tpc_pP;
  delete gr_eff_tpc_pM;
  delete gr_eff_tof_pP;
  delete gr_eff_tof_pM;

  delete f_tpc_pP;
  delete f_tpc_pM;
  delete f_tof_pP;
  delete f_tof_pM;

  delete f_tpc_p_p0_lopt; delete f_tpc_p_p0_hipt;
  delete f_tpc_p_p1_lopt; delete f_tpc_p_p1_hipt;
  delete f_tpc_p_p2_lopt;
  delete f_tpc_ap_p0_lopt; delete f_tpc_ap_p0_hipt;
  delete f_tpc_ap_p1_lopt; delete f_tpc_ap_p1_hipt;
  delete f_tpc_ap_p2_lopt;

  delete f_tof_p_p0; delete f_tof_ap_p0;
  delete f_tof_p_p1; delete f_tof_ap_p1;
  delete f_tof_p_p2; delete f_tof_ap_p2;

  // delete f_tpc_p; delete f_tpc_ap;
  delete f_tpc_p_lopt; delete f_tpc_ap_lopt;
  delete f_tpc_p_hipt; delete f_tpc_ap_hipt;
  delete f_tof_p; delete f_tof_ap;

}

void StDetectorEfficiency::Init_DetEff(const char* tpc_eff_p, const char* tpc_eff_m, const char* tof_eff_p, const char* tof_eff_m, const char* NameRuZr)
{
  cout<<"StDetectorEfficiency::StDetectorEfficiency() Get Detector Efficiency maps! ";
  cout<<Form("%s run!", NameRuZr)<<endl;

  int maxmult = 1000;

  double tpc_p_p0_one_lopt_par0, tpc_p_p0_one_lopt_par1, tpc_p_p1_one_lopt_par0, tpc_p_p1_one_lopt_par1, tpc_p_p2_one_lopt_par0, tpc_p_p2_one_lopt_par1, tpc_p_p0_one_hipt_par0, tpc_p_p0_one_hipt_par1, tpc_p_p1_one_hipt_par0, tpc_p_p1_one_hipt_par1;
  double tpc_ap_p0_one_lopt_par0, tpc_ap_p0_one_lopt_par1, tpc_ap_p1_one_lopt_par0, tpc_ap_p1_one_lopt_par1, tpc_ap_p2_one_lopt_par0, tpc_ap_p2_one_lopt_par1, tpc_ap_p0_one_hipt_par0, tpc_ap_p0_one_hipt_par1, tpc_ap_p1_one_hipt_par0, tpc_ap_p1_one_hipt_par1;
  double tof_p_p0_one_par0, tof_p_p0_one_par1, tof_p_p0_one_par2, tof_p_p1_one_par0, tof_p_p1_one_par1, tof_p_p1_one_par2, tof_p_p2_one_par0, tof_p_p2_one_par1, tof_p_p2_one_par2;
  double tof_ap_p0_one_par0, tof_ap_p0_one_par1, tof_ap_p0_one_par2, tof_ap_p1_one_par0, tof_ap_p1_one_par1, tof_ap_p1_one_par2, tof_ap_p2_one_par0, tof_ap_p2_one_par1, tof_ap_p2_one_par2;

  double dummy1;

  ifstream myfile_in;

  myfile_in.open(tpc_eff_p);
  myfile_in>>dummy1>>dummy1>>tpc_p_p0_one_lopt_par0>>tpc_p_p0_one_lopt_par1>>tpc_p_p1_one_lopt_par0>>tpc_p_p1_one_lopt_par1>>tpc_p_p2_one_lopt_par0>>tpc_p_p2_one_lopt_par1>>tpc_p_p0_one_hipt_par0>>tpc_p_p0_one_hipt_par1>>tpc_p_p1_one_hipt_par0>>tpc_p_p1_one_hipt_par1;
  myfile_in.close();
  cout<<"TPC proton params: "<<dummy1<<", "<<dummy1<<", "<<tpc_p_p0_one_lopt_par0<<", "<<tpc_p_p0_one_lopt_par1<<", "<<tpc_p_p1_one_lopt_par0<<", "<<tpc_p_p1_one_lopt_par1<<", "<<tpc_p_p2_one_lopt_par0<<", "<<tpc_p_p2_one_lopt_par1<<", "<<tpc_p_p0_one_hipt_par0<<", "<<tpc_p_p0_one_hipt_par1<<", "<<tpc_p_p1_one_hipt_par0<<", "<<tpc_p_p1_one_hipt_par1<<endl;

  myfile_in.open(tpc_eff_m);
  myfile_in>>dummy1>>dummy1>>tpc_ap_p0_one_lopt_par0>>tpc_ap_p0_one_lopt_par1>>tpc_ap_p1_one_lopt_par0>>tpc_ap_p1_one_lopt_par1>>tpc_ap_p2_one_lopt_par0>>tpc_ap_p2_one_lopt_par1>>tpc_ap_p0_one_hipt_par0>>tpc_ap_p0_one_hipt_par1>>tpc_ap_p1_one_hipt_par0>>tpc_ap_p1_one_hipt_par1;
  myfile_in.close();
  cout<<"TPC antiproton params: "<<dummy1<<", "<<dummy1<<", "<<tpc_ap_p0_one_lopt_par0<<", "<<tpc_ap_p0_one_lopt_par1<<", "<<tpc_ap_p1_one_lopt_par0<<", "<<tpc_ap_p1_one_lopt_par1<<", "<<tpc_ap_p2_one_lopt_par0<<", "<<tpc_ap_p2_one_lopt_par1<<", "<<tpc_ap_p0_one_hipt_par0<<", "<<tpc_ap_p0_one_hipt_par1<<", "<<tpc_ap_p1_one_hipt_par0<<", "<<tpc_ap_p1_one_hipt_par1<<endl;

  myfile_in.open(tof_eff_p);
  myfile_in>>dummy1>>dummy1>>tof_p_p0_one_par0>>tof_p_p0_one_par1>>tof_p_p0_one_par2>>tof_p_p1_one_par0>>tof_p_p1_one_par1>>tof_p_p1_one_par2>>tof_p_p2_one_par0>>tof_p_p2_one_par1>>tof_p_p2_one_par2;
  myfile_in.close();
  cout<<"TOF proton params: "<<dummy1<<", "<<dummy1<<", "<<tof_p_p0_one_par0<<", "<<tof_p_p0_one_par1<<", "<<tof_p_p0_one_par2<<", "<<tof_p_p1_one_par0<<", "<<tof_p_p1_one_par1<<", "<<tof_p_p1_one_par2<<", "<<tof_p_p2_one_par0<<", "<<tof_p_p2_one_par1<<", "<<tof_p_p2_one_par2<<endl;

  myfile_in.open(tof_eff_m);
  myfile_in>>dummy1>>dummy1>>tof_ap_p0_one_par0>>tof_ap_p0_one_par1>>tof_ap_p0_one_par2>>tof_ap_p1_one_par0>>tof_ap_p1_one_par1>>tof_ap_p1_one_par2>>tof_ap_p2_one_par0>>tof_ap_p2_one_par1>>tof_ap_p2_one_par2;
  myfile_in.close();
  cout<<"TOF antiproton params: "<<dummy1<<", "<<dummy1<<", "<<tof_ap_p0_one_par0<<", "<<tof_ap_p0_one_par1<<", "<<tof_ap_p0_one_par2<<", "<<tof_ap_p1_one_par0<<", "<<tof_ap_p1_one_par1<<", "<<tof_ap_p1_one_par2<<", "<<tof_ap_p2_one_par0<<", "<<tof_ap_p2_one_par1<<", "<<tof_ap_p2_one_par2<<endl;


  f_tpc_p_p0_lopt  = new TF1("f_tpc_p_p0_lopt", "pol1", 0, maxmult); f_tpc_p_p0_hipt  = new TF1("f_tpc_p_p0_hipt", "pol1", 0, maxmult);
  f_tpc_p_p1_lopt  = new TF1("f_tpc_p_p1_lopt", "pol1", 0, maxmult); f_tpc_p_p1_hipt  = new TF1("f_tpc_p_p1_hipt", "pol1", 0, maxmult);
  f_tpc_p_p2_lopt  = new TF1("f_tpc_p_p2_lopt", "pol1", 0, maxmult); // f_tpc_p_p2_hipt  = new TF1("f_tpc_p_p2_hipt", "pol1", 0, maxmult);                                                                                                                            
  f_tpc_p_p0_lopt->SetParameter(0, tpc_p_p0_one_lopt_par0); f_tpc_p_p0_lopt->SetParameter(1, tpc_p_p0_one_lopt_par1);
  f_tpc_p_p1_lopt->SetParameter(0, tpc_p_p1_one_lopt_par0); f_tpc_p_p1_lopt->SetParameter(1, tpc_p_p1_one_lopt_par1);
  f_tpc_p_p2_lopt->SetParameter(0, tpc_p_p2_one_lopt_par0); f_tpc_p_p2_lopt->SetParameter(1, tpc_p_p2_one_lopt_par1);
  f_tpc_p_p0_hipt->SetParameter(0, tpc_p_p0_one_hipt_par0); f_tpc_p_p0_hipt->SetParameter(1, tpc_p_p0_one_hipt_par1);
  f_tpc_p_p1_hipt->SetParameter(0, tpc_p_p1_one_hipt_par0); f_tpc_p_p1_hipt->SetParameter(1, tpc_p_p1_one_hipt_par1);
  f_tpc_ap_p0_lopt  = new TF1("f_tpc_ap_p0_lopt", "pol1", 0, maxmult); f_tpc_ap_p0_hipt  = new TF1("f_tpc_ap_p0_hipt", "pol1", 0, maxmult);
  f_tpc_ap_p1_lopt  = new TF1("f_tpc_ap_p1_lopt", "pol1", 0, maxmult); f_tpc_ap_p1_hipt  = new TF1("f_tpc_ap_p1_hipt", "pol1", 0, maxmult);
  f_tpc_ap_p2_lopt  = new TF1("f_tpc_ap_p2_lopt", "pol1", 0, maxmult); // f_tpc_ap_p2_hipt  = new TF1("f_tpc_ap_p2_hipt", "pol1", 0, maxmult);                                                                                                                        
  f_tpc_ap_p0_lopt->SetParameter(0, tpc_ap_p0_one_lopt_par0); f_tpc_ap_p0_lopt->SetParameter(1, tpc_ap_p0_one_lopt_par1);
  f_tpc_ap_p1_lopt->SetParameter(0, tpc_ap_p1_one_lopt_par0); f_tpc_ap_p1_lopt->SetParameter(1, tpc_ap_p1_one_lopt_par1);
  f_tpc_ap_p2_lopt->SetParameter(0, tpc_ap_p2_one_lopt_par0); f_tpc_ap_p2_lopt->SetParameter(1, tpc_ap_p2_one_lopt_par1);
  f_tpc_ap_p0_hipt->SetParameter(0, tpc_ap_p0_one_hipt_par0); f_tpc_ap_p0_hipt->SetParameter(1, tpc_ap_p0_one_hipt_par1);
  f_tpc_ap_p1_hipt->SetParameter(0, tpc_ap_p1_one_hipt_par0); f_tpc_ap_p1_hipt->SetParameter(1, tpc_ap_p1_one_hipt_par1);

  f_tof_p_p0  = new TF1("f_tof_p_p0", "pol2", 0, maxmult); f_tof_ap_p0  = new TF1("f_tof_ap_p0", "pol2", 0, maxmult);
  f_tof_p_p1  = new TF1("f_tof_p_p1", "pol2", 0, maxmult); f_tof_ap_p1  = new TF1("f_tof_ap_p1", "pol2", 0, maxmult);
  f_tof_p_p2  = new TF1("f_tof_p_p2", "pol2", 0, maxmult); f_tof_ap_p2  = new TF1("f_tof_ap_p2", "pol2", 0, maxmult);
  f_tof_p_p0->SetParameter(0, tof_p_p0_one_par0); f_tof_ap_p0->SetParameter(0, tof_ap_p0_one_par0);
  f_tof_p_p0->SetParameter(1, tof_p_p0_one_par1); f_tof_ap_p0->SetParameter(1, tof_ap_p0_one_par1);
  f_tof_p_p0->SetParameter(2, tof_p_p0_one_par2); f_tof_ap_p0->SetParameter(2, tof_ap_p0_one_par2);
  f_tof_p_p1->SetParameter(0, tof_p_p1_one_par0); f_tof_ap_p1->SetParameter(0, tof_ap_p1_one_par0);
  f_tof_p_p1->SetParameter(1, tof_p_p1_one_par1); f_tof_ap_p1->SetParameter(1, tof_ap_p1_one_par1);
  f_tof_p_p1->SetParameter(2, tof_p_p1_one_par2); f_tof_ap_p1->SetParameter(2, tof_ap_p1_one_par2);
  f_tof_p_p2->SetParameter(0, tof_p_p2_one_par0); f_tof_ap_p2->SetParameter(0, tof_ap_p2_one_par0);
  f_tof_p_p2->SetParameter(1, tof_p_p2_one_par1); f_tof_ap_p2->SetParameter(1, tof_ap_p2_one_par1);
  f_tof_p_p2->SetParameter(2, tof_p_p2_one_par2); f_tof_ap_p2->SetParameter(2, tof_ap_p2_one_par2);

  // f_tpc_p = new TF1("f_tpc_p", "pol2(0) + pol1(3)", 0.0, 2.0); f_tpc_ap = new TF1("f_tpc_ap", "pol2(0) + pol1(3)", 0.0, 2.0);
  f_tpc_p_lopt = new TF1("f_tpc_p_lopt", "pol2", 0.0, 0.8); f_tpc_ap_lopt = new TF1("f_tpc_ap_lopt", "pol2", 0.0, 0.8);
  f_tpc_p_hipt = new TF1("f_tpc_p_hipt", "pol1", 0.8, 2.0); f_tpc_ap_hipt = new TF1("f_tpc_ap_hipt", "pol1", 0.8, 2.0);
  f_tof_p = new TF1("f_tof_p", "pol2", 0.8, 2.0); f_tof_ap = new TF1("f_tof_ap", "pol2", 0.8, 2.0);


  cout<<"StDetectorEfficiency::StDetectorEfficiency() Got the Detector Efficiency maps!"<<endl;
}
// void StDetectorEfficiency::Clear_DetEff(){
//   //delete stuffs

//   // f_TOF->Clear();
//   f_eff->Clear();
  
//   for(int i = 0 ; i < nPID ; i++) {
//     // f_TPC[i]->Clear();
//     h2_Eff_TPC[i]->Clear();
//     h2_Eff_TOF[i]->Clear();
//   }

// }

// bool StDetectorEfficiency::GetAcc(int charge, double p, double pT, double eta){
bool StDetectorEfficiency::GetAcc(double pT, double y){

  // bool acc = false;
  y_cut = TMath::Abs(y) < 0.5;
  pT_cut  = pT > 0.4 && pT < 2.0;
  
  // if(y_cut && pT_cut)	acc = true;
  // else acc = false;

  // return acc;
  return (y_cut && pT_cut);
}

double StDetectorEfficiency::GetEff(int pid, int charge, double pT, double y, double m2, double ref3, double detefflow_err, double deteffhigh_err){

  //pT cuts for TOF usage 
  PiPtTOF = pT < 0.5;
  KPtTOF = pT < 0.4;
  //28092022(start): to mach AS
  // PPtTOF = pT < 0.8;
  PPtTOF = pT <= 0.8;
  //28092022(finish): to mach AS

  double eff = 0.;


  f_tpc_p_lopt->SetParameter(0, f_tpc_p_p0_lopt->Eval(ref3)); f_tpc_ap_lopt->SetParameter(0, f_tpc_ap_p0_lopt->Eval(ref3));
  f_tpc_p_lopt->SetParameter(1, f_tpc_p_p1_lopt->Eval(ref3)); f_tpc_ap_lopt->SetParameter(1, f_tpc_ap_p1_lopt->Eval(ref3));
  f_tpc_p_lopt->SetParameter(2, f_tpc_p_p2_lopt->Eval(ref3)); f_tpc_ap_lopt->SetParameter(2, f_tpc_ap_p2_lopt->Eval(ref3));

  f_tpc_p_hipt->SetParameter(0, f_tpc_p_p0_hipt->Eval(ref3)); f_tpc_ap_hipt->SetParameter(0, f_tpc_ap_p0_hipt->Eval(ref3));
  f_tpc_p_hipt->SetParameter(1, f_tpc_p_p1_hipt->Eval(ref3)); f_tpc_ap_hipt->SetParameter(1, f_tpc_ap_p1_hipt->Eval(ref3));

  f_tof_p->SetParameter(0, f_tof_p_p0->Eval(ref3)); f_tof_ap->SetParameter(0, f_tof_ap_p0->Eval(ref3));
  f_tof_p->SetParameter(1, f_tof_p_p1->Eval(ref3)); f_tof_ap->SetParameter(1, f_tof_ap_p1->Eval(ref3));
  f_tof_p->SetParameter(2, f_tof_p_p2->Eval(ref3)); f_tof_ap->SetParameter(2, f_tof_ap_p2->Eval(ref3));

  if(GetAcc(pT, y)){
    if(pid == -2) {// cout<<"StDetectorEfficiency::GetEff using GetPID. It's neither Pi, K, nor P (out of nSigma range)"<<endl;
      return -2;}
    else if(pid == 100 || pid == 101 || pid == 110 || pid == 111){//pi
      if(PiPtTOF){
	if(charge == 1){//pi+
	}
	else if(charge == -1){//pi-
	}
      }
      else if(!PiPtTOF){//TOF cut applied
	if(charge == 1){//pi+
	}
	else if(charge == -1){//pi-
	}
      }
    }//pid
    else if(pid == 10 || pid == 11 || pid == 110 || pid == 111){//k
      if(KPtTOF){
	if(charge == 1){//k+
	}
	else if(charge == -1){//k-
	}
      }
      else if(!KPtTOF){//TOF cut applied
	if(charge == 1){//k+
	}
	else if(charge == -1){//k-
	}
      }
    }//pid
    else if(pid == 1 || pid == 11 || pid == 101 || pid == 111){//proton
      if(PPtTOF){
	if(charge == 1){//proton
	  eff = f_tpc_p_lopt->Eval(pT);
	  eff *= detefflow_err;
	}
	else if(charge == -1){//anti-proton
	  eff = f_tpc_ap_lopt->Eval(pT);
	  eff *= detefflow_err;
	}
      }
      else if(!PPtTOF){
	if(charge == 1){//proton
	  eff = (f_tpc_p_hipt->Eval(pT))*(f_tof_p->Eval(pT));
	  eff *= deteffhigh_err;
	  // cout<<Form("StDetectorEfficiency::GetEff, pT = %f, ref3 = %f, proton tpc eff = %f, tof eff = %f, tot eff = %f", pT, ref3, f_tpc_p_hipt->Eval(pT), f_tof_p->Eval(pT), eff)<<endl;
	}
	else if(charge == -1){//anti-proton
	  eff = (f_tpc_ap_hipt->Eval(pT))*(f_tof_ap->Eval(pT));
	  eff *= deteffhigh_err;
	}
      }
    }//pid
    else {cout<<"StDetectorEfficiency::GetEff Cannat tell what particle it is..."<<endl; return -1;}
    if (eff == 0.) {cout<<Form("StDetectorEfficiency::GetEff. eff = %1.2f pid = %d, charge = %d, pT = %1.2f, y = %1.2f, ref = %3.1f", eff, pid, charge, pT, y, ref3)<<endl; return -1;}

    // return eff;
  }//acceptance statment ends
  else {// cout<<Form("StDetectorEfficiency::GetEff Out of acceptance. eff = %1.2f pid = %d, charge = %d, p = %1.2f, pT = %1.2f, eta = %1.2f", eff, pid, charge, p, pT, eta)<<endl;
    return -2;}

  // delete f1_tpc_p;
  // delete f1_tpc_m;
  // delete f1_tof_p;
  // delete f1_tof_m;

  return eff;
}
