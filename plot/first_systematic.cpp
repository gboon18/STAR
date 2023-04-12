#include <iostream>
#include <fstream>
#include "TROOT.h"
#include "TStyle.h"
#include "TFile.h"
#include "TF1.h"
#include "TMath.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TProfile.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TPaveText.h"
#include "TLine.h"

#include "TGraphAsymmErrors.h"
#include "TSystem.h"

#include <math.h>
#include <vector>

static const int NsysVar = 20;
static const int NdcaVar = 4;
static const int NnhfVar = 4;
static const int NnspVar = 4;
static const int Nm2Var = 4;
static const int NeffVar = 4;

  int mergedN = 2;
  const int mergedNzoom = 2;
  const int ncent = 9;

TGraphErrors *gr_c1_zr;
TGraphErrors *gr_c2_zr;
TGraphErrors *gr_c3_zr;
TGraphErrors *gr_c4_zr;
TGraphErrors *gr_c5_zr;
TGraphErrors *gr_c6_zr;
TGraphErrors *gr_c5_zr_zoom;
TGraphErrors *gr_c6_zr_zoom;
TGraphErrors *gr_cr21_zr;
TGraphErrors *gr_cr31_zr;
TGraphErrors *gr_cr32_zr;
TGraphErrors *gr_cr42_zr;
TGraphErrors *gr_cr51_zr;
TGraphErrors *gr_cr62_zr;

TGraphErrors *gr_c1_ru;
TGraphErrors *gr_c2_ru;
TGraphErrors *gr_c3_ru;
TGraphErrors *gr_c4_ru;
TGraphErrors *gr_c5_ru;
TGraphErrors *gr_c6_ru;
TGraphErrors *gr_c5_ru_zoom;
TGraphErrors *gr_c6_ru_zoom;
TGraphErrors *gr_cr21_ru;
TGraphErrors *gr_cr31_ru;
TGraphErrors *gr_cr32_ru;
TGraphErrors *gr_cr42_ru;
TGraphErrors *gr_cr51_ru;
TGraphErrors *gr_cr62_ru;

using namespace std;

bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

bool barlow(TH1D *h){

  int counter = 0;
  bool tf = false;

  if(abs(h->GetMean()) < 0.3) counter++;
  if(h->GetStdDev() < 1.3) counter++;
  if(h->Integral(h->FindBin(h->GetMean() - 1.*h->GetStdDev()), h->FindBin(h->GetMean() + 1.*h->GetStdDev()))/h->GetEntries() > 0.55 && h->Integral(h->FindBin(h->GetMean() - 1.*h->GetStdDev()), h->FindBin(h->GetMean() + 1.*h->GetStdDev()))/h->GetEntries() < 0.68) counter++;
  if(h->Integral(h->FindBin(h->GetMean() - 2.*h->GetStdDev()), h->FindBin(h->GetMean() + 2.*h->GetStdDev()))/h->GetEntries() > 0.80 && h->Integral(h->FindBin(h->GetMean() - 2.*h->GetStdDev()), h->FindBin(h->GetMean() + 2.*h->GetStdDev()))/h->GetEntries() < 0.95) counter++;
  
  if(counter >= 3) tf = true;
  else if(counter < 3) tf = false;

  return tf;
}

double *sys_unc(TGraphErrors* gr_org, TGraphErrors* gr_sys[NsysVar], const char* name){

  static double sys_unc_arr[ncent*5];
  for(int i_sys = 0 ; i_sys < ncent*5 ; i_sys++) sys_unc_arr[i_sys] = 0.;

  
  TProfile *hP_dca = new TProfile("hP_dca", "hP_dca", ncent, -0.5, ncent-0.5);
  TProfile *hP_nhf = new TProfile("hP_nhf", "hP_nhf", ncent, -0.5, ncent-0.5);
  TProfile *hP_nsp = new TProfile("hP_nsp", "hP_nsp", ncent, -0.5, ncent-0.5);
  TProfile *hP_m2  = new TProfile("hP_m2",  "hP_m2",  ncent, -0.5, ncent-0.5);
  TProfile *hP_def = new TProfile("hP_def", "hP_def", ncent, -0.5, ncent-0.5);

  TProfile *hP_dca_bar = new TProfile("hP_dca_bar", "hP_dca_bar", ncent, -0.5, ncent-0.5);//for barlow test
  TProfile *hP_nhf_bar = new TProfile("hP_nhf_bar", "hP_nhf_bar", ncent, -0.5, ncent-0.5);
  TProfile *hP_nsp_bar = new TProfile("hP_nsp_bar", "hP_nsp_bar", ncent, -0.5, ncent-0.5);
  TProfile *hP_m2_bar = new TProfile("hP_m2_bar",  "hP_m2_bar",  ncent, -0.5, ncent-0.5);
  TProfile *hP_def_bar = new TProfile("hP_def_bar", "hP_def_bar", ncent, -0.5, ncent-0.5);

  TH1D *h1_dca_bar = new TH1D("h1_dca_bar", "h1_dca_bar", 1e6, -1e3, 1e3);
  TH1D *h1_nhf_bar = new TH1D("h1_nhf_bar", "h1_nhf_bar", 1e6, -1e3, 1e3);
  TH1D *h1_nsp_bar = new TH1D("h1_nsp_bar", "h1_nsp_bar", 1e6, -1e3, 1e3);
  TH1D*h1_m2_bar  = new TH1D("h1_m2_bar",  "h1_m2_bar",  1e6, -1e3, 1e3);
  TH1D *h1_def_bar = new TH1D("h1_def_bar", "h1_def_bar", 1e6, -1e3, 1e3);

  TH1D *h1_dca_bar_show = new TH1D("h1_dca_bar_show", "h1_dca_bar_show", 80, -20, 20);
  TH1D *h1_nhf_bar_show = new TH1D("h1_nhf_bar_show", "h1_nhf_bar_show", 80, -20, 20);
  TH1D *h1_nsp_bar_show = new TH1D("h1_nsp_bar_show", "h1_nsp_bar_show", 80, -20, 20);
  TH1D *h1_m2_bar_show  = new TH1D("h1_m2_bar_show",  "h1_m2_bar_show",  80, -20, 20);
  TH1D *h1_def_bar_show = new TH1D("h1_def_bar_show", "h1_def_bar_show", 80, -20, 20);

  double dca_counter[2];//for barlow test 0: 1 sigma, 1: 2 sigma
  double nhf_counter[2];//for barlow test 0: 1 sigma, 1: 2 sigma
  double nsp_counter[2];//for barlow test 0: 1 sigma, 1: 2 sigma
  double m2_counter[2];//for barlow test 0: 1 sigma, 1: 2 sigma
  double eff_counter[2];//for barlow test 0: 1 sigma, 1: 2 sigma

  for(int i = 0 ; i < 2 ; i++){
    dca_counter[i] = 0.;
    nhf_counter[i] = 0.;
    nsp_counter[i] = 0.;
    m2_counter[i] = 0.;
    eff_counter[i] = 0.;
  }

  double std_sys[ncent], std_dca[ncent], std_nhf[ncent], std_nsp[ncent], std_m2[ncent], std_def[ncent];
  for(int i_cent = 0 ; i_cent < ncent ; i_cent++) {
    std_sys[i_cent] = 0.;
    std_dca[i_cent] = 0.;
    std_nhf[i_cent] = 0.;
    std_nsp[i_cent] = 0.;
    std_m2[i_cent] = 0.;
    std_def[i_cent] = 0.;
  }

  for(int i_cent = 0+mergedN ; i_cent < ncent ; i_cent++){//from central to peripheral

    for(int i_dca = 0 ; i_dca < NdcaVar ; i_dca++){

      std_dca[i_cent] += pow(gr_org->GetPointY(i_cent) - gr_sys[i_dca]->GetPointY(i_cent), 2)/NdcaVar;

      hP_dca->Fill(i_cent, gr_org->GetPointY(i_cent) - gr_sys[i_dca]->GetPointY(i_cent));
      hP_dca_bar->Fill(0., (gr_org->GetPointY(i_cent) - gr_sys[i_dca]->GetPointY(i_cent)) / sqrt( abs ( pow(gr_org->GetErrorY(i_cent),2) - pow(gr_sys[i_dca]->GetErrorY(i_cent),2)  ) ) );
      h1_dca_bar->Fill((gr_org->GetPointY(i_cent) - gr_sys[i_dca]->GetPointY(i_cent)) / sqrt( abs ( pow(gr_org->GetErrorY(i_cent),2) - pow(gr_sys[i_dca]->GetErrorY(i_cent),2)  ) ) );
      h1_dca_bar_show->Fill((gr_org->GetPointY(i_cent) - gr_sys[i_dca]->GetPointY(i_cent)) / sqrt( abs ( pow(gr_org->GetErrorY(i_cent),2) - pow(gr_sys[i_dca]->GetErrorY(i_cent),2)  ) ) );
      if(abs( (gr_org->GetPointY(i_cent) - gr_sys[i_dca]->GetPointY(i_cent)) / sqrt( abs ( pow(gr_org->GetErrorY(i_cent),2) -  pow(gr_sys[i_dca]->GetErrorY(i_cent),2) ) )) < 1) dca_counter[0]+=1./NdcaVar/ncent;
      if(abs( (gr_org->GetPointY(i_cent) - gr_sys[i_dca]->GetPointY(i_cent)) / sqrt( abs ( pow(gr_org->GetErrorY(i_cent),2) -  pow(gr_sys[i_dca]->GetErrorY(i_cent),2) ) )) < 2) dca_counter[1]+=1./NdcaVar/ncent;
    }
    
    for(int i_nhf = 0 ; i_nhf < NnhfVar ; i_nhf++){

      std_nhf[i_cent] += pow(gr_org->GetPointY(i_cent) - gr_sys[i_nhf+NdcaVar]->GetPointY(i_cent), 2)/NnhfVar;

      hP_nhf->Fill(i_cent, gr_org->GetPointY(i_cent) - gr_sys[i_nhf+NdcaVar]->GetPointY(i_cent));
      hP_nhf_bar->Fill(0., (gr_org->GetPointY(i_cent) - gr_sys[i_nhf+NdcaVar]->GetPointY(i_cent)) / sqrt( abs ( pow(gr_org->GetErrorY(i_cent),2) - pow(gr_sys[i_nhf+NdcaVar]->GetErrorY(i_cent),2)  ) ) );
      h1_nhf_bar->Fill((gr_org->GetPointY(i_cent) - gr_sys[i_nhf+NdcaVar]->GetPointY(i_cent)) / sqrt( abs ( pow(gr_org->GetErrorY(i_cent),2) - pow(gr_sys[i_nhf+NdcaVar]->GetErrorY(i_cent),2)  ) ) );
      h1_nhf_bar_show->Fill((gr_org->GetPointY(i_cent) - gr_sys[i_nhf+NdcaVar]->GetPointY(i_cent)) / sqrt( abs ( pow(gr_org->GetErrorY(i_cent),2) - pow(gr_sys[i_nhf+NdcaVar]->GetErrorY(i_cent),2)  ) ) );
      if(abs( (gr_org->GetPointY(i_cent) - gr_sys[i_nhf+NdcaVar]->GetPointY(i_cent)) / sqrt( abs ( pow(gr_org->GetErrorY(i_cent),2) -  pow(gr_sys[i_nhf+NdcaVar]->GetErrorY(i_cent),2) ) )) < 1) nhf_counter[0]+=1./NnhfVar/ncent;
      if(abs( (gr_org->GetPointY(i_cent) - gr_sys[i_nhf+NdcaVar]->GetPointY(i_cent)) / sqrt( abs ( pow(gr_org->GetErrorY(i_cent),2) -  pow(gr_sys[i_nhf+NdcaVar]->GetErrorY(i_cent),2) ) )) < 2) nhf_counter[1]+=1./NnhfVar/ncent;
    }
    for(int i_nsp = 0 ; i_nsp < NnspVar ; i_nsp++){

      std_nsp[i_cent] += pow(gr_org->GetPointY(i_cent) - gr_sys[i_nsp+NdcaVar+NnspVar]->GetPointY(i_cent), 2)/NnspVar;

      hP_nsp->Fill(i_cent, gr_org->GetPointY(i_cent) - gr_sys[i_nsp+NdcaVar+NnspVar]->GetPointY(i_cent));
      hP_nsp_bar->Fill(0., (gr_org->GetPointY(i_cent) - gr_sys[i_nsp+NdcaVar+NnspVar]->GetPointY(i_cent)) / sqrt( abs ( pow(gr_org->GetErrorY(i_cent),2) - pow(gr_sys[i_nsp+NdcaVar+NnhfVar]->GetErrorY(i_cent),2)  ) ) );
      h1_nsp_bar->Fill((gr_org->GetPointY(i_cent) - gr_sys[i_nsp+NdcaVar+NnspVar]->GetPointY(i_cent)) / sqrt( abs ( pow(gr_org->GetErrorY(i_cent),2) - pow(gr_sys[i_nsp+NdcaVar+NnhfVar]->GetErrorY(i_cent),2)  ) ) );
      h1_nsp_bar_show->Fill((gr_org->GetPointY(i_cent) - gr_sys[i_nsp+NdcaVar+NnspVar]->GetPointY(i_cent)) / sqrt( abs ( pow(gr_org->GetErrorY(i_cent),2) - pow(gr_sys[i_nsp+NdcaVar+NnhfVar]->GetErrorY(i_cent),2)  ) ) );
      if(abs( (gr_org->GetPointY(i_cent) - gr_sys[i_nsp+NdcaVar+NnspVar]->GetPointY(i_cent)) / sqrt( abs ( pow(gr_org->GetErrorY(i_cent),2) -  pow(gr_sys[i_nsp+NdcaVar+NnspVar]->GetErrorY(i_cent),2) ) )) < 1) nsp_counter[0]+=1./NnspVar/ncent;
      if(abs( (gr_org->GetPointY(i_cent) - gr_sys[i_nsp+NdcaVar+NnspVar]->GetPointY(i_cent)) / sqrt( abs ( pow(gr_org->GetErrorY(i_cent),2) -  pow(gr_sys[i_nsp+NdcaVar+NnspVar]->GetErrorY(i_cent),2) ) )) < 2) nsp_counter[1]+=1./NnspVar/ncent;
    }
    for(int i_m2 = 0 ; i_m2 < Nm2Var ; i_m2++){

      std_m2[i_cent] += pow(gr_org->GetPointY(i_cent) - gr_sys[i_m2+NdcaVar+NnspVar+Nm2Var]->GetPointY(i_cent), 2)/Nm2Var;

      hP_m2->Fill(i_cent, gr_org->GetPointY(i_cent) - gr_sys[i_m2+NdcaVar+NnspVar+Nm2Var]->GetPointY(i_cent));
      hP_m2_bar->Fill(0., (gr_org->GetPointY(i_cent) - gr_sys[i_m2+NdcaVar+NnspVar+Nm2Var]->GetPointY(i_cent)) / sqrt( abs ( pow(gr_org->GetErrorY(i_cent),2) - pow(gr_sys[i_m2+NdcaVar+NnhfVar+NnspVar]->GetErrorY(i_cent),2)  ) ) );
      h1_m2_bar->Fill((gr_org->GetPointY(i_cent) - gr_sys[i_m2+NdcaVar+NnspVar+Nm2Var]->GetPointY(i_cent)) / sqrt( abs ( pow(gr_org->GetErrorY(i_cent),2) - pow(gr_sys[i_m2+NdcaVar+NnhfVar+NnspVar]->GetErrorY(i_cent),2)  ) ) );
      h1_m2_bar_show->Fill((gr_org->GetPointY(i_cent) - gr_sys[i_m2+NdcaVar+NnspVar+Nm2Var]->GetPointY(i_cent)) / sqrt( abs ( pow(gr_org->GetErrorY(i_cent),2) - pow(gr_sys[i_m2+NdcaVar+NnhfVar+NnspVar]->GetErrorY(i_cent),2)  ) ) );
      if(abs( (gr_org->GetPointY(i_cent) - gr_sys[i_m2+NdcaVar+NnspVar+Nm2Var]->GetPointY(i_cent)) / sqrt( abs ( pow(gr_org->GetErrorY(i_cent),2) -  pow(gr_sys[i_m2+NdcaVar+NnspVar+Nm2Var]->GetErrorY(i_cent),2) ) )) < 1) m2_counter[0]+=1./Nm2Var/ncent;
      if(abs( (gr_org->GetPointY(i_cent) - gr_sys[i_m2+NdcaVar+NnspVar+Nm2Var]->GetPointY(i_cent)) / sqrt( abs ( pow(gr_org->GetErrorY(i_cent),2) -  pow(gr_sys[i_m2+NdcaVar+NnspVar+Nm2Var]->GetErrorY(i_cent),2) ) )) < 2) m2_counter[1]+=1./Nm2Var/ncent;
    }
    for(int i_def = 0 ; i_def < NeffVar ; i_def++){

      std_def[i_cent] += pow(gr_org->GetPointY(i_cent) - gr_sys[i_def+NdcaVar+NnspVar+Nm2Var+NeffVar]->GetPointY(i_cent), 2)/NeffVar;

      hP_def->Fill(i_cent, gr_org->GetPointY(i_cent) - gr_sys[i_def+NdcaVar+NnspVar+Nm2Var+NeffVar]->GetPointY(i_cent));
      hP_def_bar->Fill(0., (gr_org->GetPointY(i_cent) - gr_sys[i_def+NdcaVar+NnspVar+Nm2Var+NeffVar]->GetPointY(i_cent)) / sqrt( abs ( pow(gr_org->GetErrorY(i_cent),2) - pow(gr_sys[i_def+NdcaVar+NnhfVar+NnspVar+Nm2Var]->GetErrorY(i_cent),2)  ) ) );
      h1_def_bar->Fill((gr_org->GetPointY(i_cent) - gr_sys[i_def+NdcaVar+NnspVar+Nm2Var+NeffVar]->GetPointY(i_cent)) / sqrt( abs ( pow(gr_org->GetErrorY(i_cent),2) - pow(gr_sys[i_def+NdcaVar+NnhfVar+NnspVar+Nm2Var]->GetErrorY(i_cent),2)  ) ) );
      h1_def_bar_show->Fill((gr_org->GetPointY(i_cent) - gr_sys[i_def+NdcaVar+NnspVar+Nm2Var+NeffVar]->GetPointY(i_cent)) / sqrt( abs ( pow(gr_org->GetErrorY(i_cent),2) - pow(gr_sys[i_def+NdcaVar+NnhfVar+NnspVar+Nm2Var]->GetErrorY(i_cent),2)  ) ) );
      if(abs( (gr_org->GetPointY(i_cent) - gr_sys[i_def+NdcaVar+NnspVar+Nm2Var+NeffVar]->GetPointY(i_cent)) / sqrt( abs ( pow(gr_org->GetErrorY(i_cent),2) -  pow(gr_sys[i_def+NdcaVar+NnspVar+Nm2Var+NeffVar]->GetErrorY(i_cent),2) ) )) < 1) eff_counter[0]+=1./NeffVar/ncent;
      if(abs( (gr_org->GetPointY(i_cent) - gr_sys[i_def+NdcaVar+NnspVar+Nm2Var+NeffVar]->GetPointY(i_cent)) / sqrt( abs ( pow(gr_org->GetErrorY(i_cent),2) -  pow(gr_sys[i_def+NdcaVar+NnspVar+Nm2Var+NeffVar]->GetErrorY(i_cent),2) ) )) < 2) eff_counter[1]+=1./NeffVar/ncent;
    }

  }

  ofstream myfile_out;
  myfile_out.open(Form("output/barlow/%s_%d.txt", name,mergedN));
  if( barlow(h1_dca_bar) ) {cout<<name<<" !!!!!!!!!!!!!!!!!! dca passed barlow"<<endl; myfile_out<<"dca"<<endl;}
  if( barlow(h1_nhf_bar) ) {cout<<name<<" !!!!!!!!!!!!!!!!!! nhf passed barlow"<<endl; myfile_out<<"nhf"<<endl;}
  if( barlow(h1_nsp_bar) ) {cout<<name<<" !!!!!!!!!!!!!!!!!! nsp passed barlow"<<endl; myfile_out<<"nsp"<<endl;}
  if( barlow(h1_m2_bar)  ) {cout<<name<<" !!!!!!!!!!!!!!!!!! m2 passed barlow"<<endl; myfile_out<<"m2"<<endl;}
  if( barlow(h1_def_bar) ) {cout<<name<<" !!!!!!!!!!!!!!!!!! eff passed barlow"<<endl; myfile_out<<"def"<<endl;}
  myfile_out.close();


  if(!fileExists(Form("output/barlow/%s_%d.txt", name,0))) {cout<<Form("output/barlow/%s_%d.txt does not exists! Try running with mergedN = 0 first! And re-run", name,0)<<endl; exit(0);}
  ifstream myfile_barlow_in;
  myfile_barlow_in.open(Form("output/barlow/%s_%d.txt", name,0));
  vector<string> passNopass;
  string pass_str;
  int pass_ctr = 0;
  pass_ctr = 0;
  while(myfile_barlow_in>>pass_str) {passNopass.push_back(pass_str); pass_ctr++;}
  myfile_barlow_in.close();
  for(int i_cent = 0+mergedN ; i_cent < ncent ; i_cent++){
    if(std::find(passNopass.begin(), passNopass.end(), "dca") == passNopass.end()) {sys_unc_arr[i_cent] = sqrt(std_dca[i_cent]); if(i_cent == ncent-1) cout<<Form("%s Quoting dca", name)<<endl;}
    if(std::find(passNopass.begin(), passNopass.end(), "nhf") == passNopass.end()) {sys_unc_arr[i_cent+ncent] = sqrt(std_nhf[i_cent]); if(i_cent == ncent-1) cout<<Form("%s Quoting nhf", name)<<endl;}
    if(std::find(passNopass.begin(), passNopass.end(), "nsp") == passNopass.end()) {sys_unc_arr[i_cent+ncent*2] = sqrt(std_nsp[i_cent]); if(i_cent == ncent-1) cout<<Form("%s Quoting nsp", name)<<endl;}
    if(std::find(passNopass.begin(), passNopass.end(), "m2")  == passNopass.end()) {sys_unc_arr[i_cent+ncent*3] = sqrt(std_m2[i_cent]); if(i_cent == ncent-1) cout<<Form("%s Quoting m2", name)<<endl;}
    if(std::find(passNopass.begin(), passNopass.end(), "def") == passNopass.end()) {sys_unc_arr[i_cent+ncent*4] = sqrt(std_def[i_cent]); if(i_cent == ncent-1) cout<<Form("%s Quoting def", name)<<endl;}
    
  }
  passNopass.clear();

  TFile *f_out = new TFile(Form("output/barlow/%s_%d.root",name,mergedN), "RECREATE");
  f_out->cd();
  hP_dca->Write();
  hP_nhf->Write();
  hP_nsp->Write();
  hP_m2->Write();
  hP_def->Write();
  hP_dca_bar->Write();
  hP_nhf_bar->Write();
  hP_nsp_bar->Write();
  hP_m2_bar->Write();
  hP_def_bar->Write();
  h1_dca_bar->Write();
  h1_nhf_bar->Write();
  h1_nsp_bar->Write();
  h1_m2_bar->Write();
  h1_def_bar->Write();

  h1_dca_bar_show->Write();
  h1_nhf_bar_show->Write();
  h1_nsp_bar_show->Write();
  h1_m2_bar_show->Write();
  h1_def_bar_show->Write();

  f_out->Write();
  f_out->Close();

  delete hP_dca;
  delete hP_nhf;
  delete hP_nsp;
  delete hP_m2;
  delete hP_def;
  delete hP_dca_bar;
  delete hP_nhf_bar;
  delete hP_nsp_bar;
  delete hP_m2_bar;
  delete hP_def_bar;
  delete h1_dca_bar;
  delete h1_nhf_bar;
  delete h1_nsp_bar;
  delete h1_m2_bar;
  delete h1_def_bar;

  delete h1_dca_bar_show;
  delete h1_nhf_bar_show;
  delete h1_nsp_bar_show;
  delete h1_m2_bar_show;
  delete h1_def_bar_show;

  delete f_out;
  return sys_unc_arr;

}

std::vector<TGraphErrors*> load_sys(){
  int dca_cuts[5] = {8, 9, 11, 12, 10};

  int nhitsfit_cuts[5] = {15, 18, 22, 25, 20};
  int nsp_cuts[5] = {16, 18, 22, 25, 20};
  int m2low_cuts[5] = {50, 50, 65, 70, 60};
  int m2up_cuts[5] = {110, 115, 125, 130, 120};

  int ptmax_cuts[2] = {10, 20};
  int ymax_cuts[2] = {1, 5};

  int detefflow_err[3] = {95, 105, 100};
  int deteffhigh_err[3] = {95, 105, 100};

  TFile *f_sys_ru[20], *f_sys_zr[20];
  
  for(int i_dca = 0 ; i_dca < 4 ; i_dca++){
    f_sys_ru[i_dca] = new TFile(Form("../calcum/output/Ru_cbwc_dca_%d_nhf_%d_nsp_%d_m2low_%d_m2up_%d_ptmx_%d_ymax_%d_detlow_%d_deghi_%d_%d.root", dca_cuts[i_dca], nhitsfit_cuts[4], nsp_cuts[4], m2low_cuts[4], m2up_cuts[4], ptmax_cuts[1], ymax_cuts[1], detefflow_err[2], deteffhigh_err[2], mergedN), "READ");
    f_sys_zr[i_dca] = new TFile(Form("../calcum/output/Zr_cbwc_dca_%d_nhf_%d_nsp_%d_m2low_%d_m2up_%d_ptmx_%d_ymax_%d_detlow_%d_deghi_%d_%d.root", dca_cuts[i_dca], nhitsfit_cuts[4], nsp_cuts[4], m2low_cuts[4], m2up_cuts[4], ptmax_cuts[1], ymax_cuts[1], detefflow_err[2], deteffhigh_err[2], mergedN), "READ");
  }

  for(int i_nhf = 0 ; i_nhf < 4 ; i_nhf++){
    f_sys_ru[i_nhf+4] = new TFile(Form("../calcum/output/Ru_cbwc_dca_%d_nhf_%d_nsp_%d_m2low_%d_m2up_%d_ptmx_%d_ymax_%d_detlow_%d_deghi_%d_%d.root", dca_cuts[4], nhitsfit_cuts[i_nhf], nsp_cuts[4], m2low_cuts[4], m2up_cuts[4], ptmax_cuts[1], ymax_cuts[1], detefflow_err[2], deteffhigh_err[2], mergedN), "READ");
    f_sys_zr[i_nhf+4] = new TFile(Form("../calcum/output/Zr_cbwc_dca_%d_nhf_%d_nsp_%d_m2low_%d_m2up_%d_ptmx_%d_ymax_%d_detlow_%d_deghi_%d_%d.root", dca_cuts[4], nhitsfit_cuts[i_nhf], nsp_cuts[4], m2low_cuts[4], m2up_cuts[4], ptmax_cuts[1], ymax_cuts[1], detefflow_err[2], deteffhigh_err[2], mergedN), "READ");
  }
  for(int i_nsp = 0 ; i_nsp < 4 ; i_nsp++){
    f_sys_ru[i_nsp+4*2] = new TFile(Form("../calcum/output/Ru_cbwc_dca_%d_nhf_%d_nsp_%d_m2low_%d_m2up_%d_ptmx_%d_ymax_%d_detlow_%d_deghi_%d_%d.root", dca_cuts[4], nhitsfit_cuts[4], nsp_cuts[i_nsp], m2low_cuts[4], m2up_cuts[4], ptmax_cuts[1], ymax_cuts[1], detefflow_err[2], deteffhigh_err[2], mergedN), "READ");
    f_sys_zr[i_nsp+4*2] = new TFile(Form("../calcum/output/Zr_cbwc_dca_%d_nhf_%d_nsp_%d_m2low_%d_m2up_%d_ptmx_%d_ymax_%d_detlow_%d_deghi_%d_%d.root", dca_cuts[4], nhitsfit_cuts[4], nsp_cuts[i_nsp], m2low_cuts[4], m2up_cuts[4], ptmax_cuts[1], ymax_cuts[1], detefflow_err[2], deteffhigh_err[2], mergedN), "READ");
  }
  for(int i_m2 = 0 ; i_m2 < 4 ; i_m2++){
    f_sys_ru[i_m2+4*3] = new TFile(Form("../calcum/output/Ru_cbwc_dca_%d_nhf_%d_nsp_%d_m2low_%d_m2up_%d_ptmx_%d_ymax_%d_detlow_%d_deghi_%d_%d.root", dca_cuts[4], nhitsfit_cuts[4], nsp_cuts[4], m2low_cuts[i_m2], m2up_cuts[i_m2], ptmax_cuts[1], ymax_cuts[1], detefflow_err[2], deteffhigh_err[2], mergedN), "READ");
    f_sys_zr[i_m2+4*3] = new TFile(Form("../calcum/output/Zr_cbwc_dca_%d_nhf_%d_nsp_%d_m2low_%d_m2up_%d_ptmx_%d_ymax_%d_detlow_%d_deghi_%d_%d.root", dca_cuts[4], nhitsfit_cuts[4], nsp_cuts[4], m2low_cuts[i_m2], m2up_cuts[i_m2], ptmax_cuts[1], ymax_cuts[1], detefflow_err[2], deteffhigh_err[2], mergedN), "READ");
  }
  f_sys_ru[16] = new TFile(Form("../calcum/output/Ru_cbwc_dca_%d_nhf_%d_nsp_%d_m2low_%d_m2up_%d_ptmx_%d_ymax_%d_detlow_%d_deghi_%d_%d.root", dca_cuts[4], nhitsfit_cuts[4], nsp_cuts[4], m2low_cuts[4], m2up_cuts[4], ptmax_cuts[1], ymax_cuts[1], detefflow_err[1], deteffhigh_err[1], mergedN), "READ");
  f_sys_ru[17] = new TFile(Form("../calcum/output/Ru_cbwc_dca_%d_nhf_%d_nsp_%d_m2low_%d_m2up_%d_ptmx_%d_ymax_%d_detlow_%d_deghi_%d_%d.root", dca_cuts[4], nhitsfit_cuts[4], nsp_cuts[4], m2low_cuts[4], m2up_cuts[4], ptmax_cuts[1], ymax_cuts[1], detefflow_err[0], deteffhigh_err[0], mergedN), "READ");
  f_sys_ru[18] = new TFile(Form("../calcum/output/Ru_cbwc_dca_%d_nhf_%d_nsp_%d_m2low_%d_m2up_%d_ptmx_%d_ymax_%d_detlow_%d_deghi_%d_%d.root", dca_cuts[4], nhitsfit_cuts[4], nsp_cuts[4], m2low_cuts[4], m2up_cuts[4], ptmax_cuts[1], ymax_cuts[1], detefflow_err[1], deteffhigh_err[0], mergedN), "READ");
  f_sys_ru[19] = new TFile(Form("../calcum/output/Ru_cbwc_dca_%d_nhf_%d_nsp_%d_m2low_%d_m2up_%d_ptmx_%d_ymax_%d_detlow_%d_deghi_%d_%d.root", dca_cuts[4], nhitsfit_cuts[4], nsp_cuts[4], m2low_cuts[4], m2up_cuts[4], ptmax_cuts[1], ymax_cuts[1], detefflow_err[0], deteffhigh_err[1], mergedN), "READ");
  f_sys_zr[16] = new TFile(Form("../calcum/output/Zr_cbwc_dca_%d_nhf_%d_nsp_%d_m2low_%d_m2up_%d_ptmx_%d_ymax_%d_detlow_%d_deghi_%d_%d.root", dca_cuts[4], nhitsfit_cuts[4], nsp_cuts[4], m2low_cuts[4], m2up_cuts[4], ptmax_cuts[1], ymax_cuts[1], detefflow_err[1], deteffhigh_err[1], mergedN), "READ");
  f_sys_zr[17] = new TFile(Form("../calcum/output/Zr_cbwc_dca_%d_nhf_%d_nsp_%d_m2low_%d_m2up_%d_ptmx_%d_ymax_%d_detlow_%d_deghi_%d_%d.root", dca_cuts[4], nhitsfit_cuts[4], nsp_cuts[4], m2low_cuts[4], m2up_cuts[4], ptmax_cuts[1], ymax_cuts[1], detefflow_err[0], deteffhigh_err[0], mergedN), "READ");
  f_sys_zr[18] = new TFile(Form("../calcum/output/Zr_cbwc_dca_%d_nhf_%d_nsp_%d_m2low_%d_m2up_%d_ptmx_%d_ymax_%d_detlow_%d_deghi_%d_%d.root", dca_cuts[4], nhitsfit_cuts[4], nsp_cuts[4], m2low_cuts[4], m2up_cuts[4], ptmax_cuts[1], ymax_cuts[1], detefflow_err[1], deteffhigh_err[0], mergedN), "READ");
  f_sys_zr[19] = new TFile(Form("../calcum/output/Zr_cbwc_dca_%d_nhf_%d_nsp_%d_m2low_%d_m2up_%d_ptmx_%d_ymax_%d_detlow_%d_deghi_%d_%d.root", dca_cuts[4], nhitsfit_cuts[4], nsp_cuts[4], m2low_cuts[4], m2up_cuts[4], ptmax_cuts[1], ymax_cuts[1], detefflow_err[0], deteffhigh_err[1], mergedN), "READ");

  TGraphErrors *gr_c1_sys_ru[20], *gr_c2_sys_ru[20], *gr_c3_sys_ru[20], *gr_c4_sys_ru[20], *gr_c5_sys_ru[20], *gr_c6_sys_ru[20];
  TGraphErrors *gr_cr21_sys_ru[20], *gr_cr31_sys_ru[20], *gr_cr32_sys_ru[20], *gr_cr42_sys_ru[20], *gr_cr51_sys_ru[20], *gr_cr62_sys_ru[20];
  TGraphErrors *gr_c1_sys_zr[20], *gr_c2_sys_zr[20], *gr_c3_sys_zr[20], *gr_c4_sys_zr[20], *gr_c5_sys_zr[20], *gr_c6_sys_zr[20];
  TGraphErrors *gr_cr21_sys_zr[20], *gr_cr31_sys_zr[20], *gr_cr32_sys_zr[20], *gr_cr42_sys_zr[20], *gr_cr51_sys_zr[20], *gr_cr62_sys_zr[20];

  for(int i_dca = 0 ; i_dca < 4 ; i_dca++){
    gr_c1_sys_ru[i_dca] = (TGraphErrors*)f_sys_ru[i_dca]->Get("proton_C_1"); gr_c1_sys_ru[i_dca]->SetMarkerColor(i_dca+1); gr_c1_sys_ru[i_dca]->SetMarkerStyle(21); gr_c1_sys_ru[i_dca]->SetMarkerSize(1.5);
    gr_c2_sys_ru[i_dca] = (TGraphErrors*)f_sys_ru[i_dca]->Get("proton_C_2"); gr_c2_sys_ru[i_dca]->SetMarkerColor(i_dca+1); gr_c2_sys_ru[i_dca]->SetMarkerStyle(21); gr_c2_sys_ru[i_dca]->SetMarkerSize(1.5);
    gr_c3_sys_ru[i_dca] = (TGraphErrors*)f_sys_ru[i_dca]->Get("proton_C_3"); gr_c3_sys_ru[i_dca]->SetMarkerColor(i_dca+1); gr_c3_sys_ru[i_dca]->SetMarkerStyle(21); gr_c3_sys_ru[i_dca]->SetMarkerSize(1.5);
    gr_c4_sys_ru[i_dca] = (TGraphErrors*)f_sys_ru[i_dca]->Get("proton_C_4"); gr_c4_sys_ru[i_dca]->SetMarkerColor(i_dca+1); gr_c4_sys_ru[i_dca]->SetMarkerStyle(21); gr_c4_sys_ru[i_dca]->SetMarkerSize(1.5);
    gr_c5_sys_ru[i_dca] = (TGraphErrors*)f_sys_ru[i_dca]->Get("proton_C_5"); gr_c5_sys_ru[i_dca]->SetMarkerColor(i_dca+1); gr_c5_sys_ru[i_dca]->SetMarkerStyle(21); gr_c5_sys_ru[i_dca]->SetMarkerSize(1.5);
    gr_c6_sys_ru[i_dca] = (TGraphErrors*)f_sys_ru[i_dca]->Get("proton_C_6"); gr_c6_sys_ru[i_dca]->SetMarkerColor(i_dca+1); gr_c6_sys_ru[i_dca]->SetMarkerStyle(21); gr_c6_sys_ru[i_dca]->SetMarkerSize(1.5);
    gr_cr21_sys_ru[i_dca] = (TGraphErrors*)f_sys_ru[i_dca]->Get("proton_CR_2_1"); gr_cr21_sys_ru[i_dca]->SetMarkerColor(i_dca+1); gr_cr21_sys_ru[i_dca]->SetMarkerStyle(21); gr_cr21_sys_ru[i_dca]->SetMarkerSize(1.5);
    gr_cr31_sys_ru[i_dca] = (TGraphErrors*)f_sys_ru[i_dca]->Get("proton_CR_3_1"); gr_cr31_sys_ru[i_dca]->SetMarkerColor(i_dca+1); gr_cr31_sys_ru[i_dca]->SetMarkerStyle(21); gr_cr31_sys_ru[i_dca]->SetMarkerSize(1.5);
    gr_cr32_sys_ru[i_dca] = (TGraphErrors*)f_sys_ru[i_dca]->Get("proton_CR_3_2"); gr_cr32_sys_ru[i_dca]->SetMarkerColor(i_dca+1); gr_cr32_sys_ru[i_dca]->SetMarkerStyle(21); gr_cr32_sys_ru[i_dca]->SetMarkerSize(1.5);
    gr_cr42_sys_ru[i_dca] = (TGraphErrors*)f_sys_ru[i_dca]->Get("proton_CR_4_2"); gr_cr42_sys_ru[i_dca]->SetMarkerColor(i_dca+1); gr_cr42_sys_ru[i_dca]->SetMarkerStyle(21); gr_cr42_sys_ru[i_dca]->SetMarkerSize(1.5);
    gr_cr51_sys_ru[i_dca] = (TGraphErrors*)f_sys_ru[i_dca]->Get("proton_CR_5_1"); gr_cr51_sys_ru[i_dca]->SetMarkerColor(i_dca+1); gr_cr51_sys_ru[i_dca]->SetMarkerStyle(21); gr_cr51_sys_ru[i_dca]->SetMarkerSize(1.5);
    gr_cr62_sys_ru[i_dca] = (TGraphErrors*)f_sys_ru[i_dca]->Get("proton_CR_6_2"); gr_cr62_sys_ru[i_dca]->SetMarkerColor(i_dca+1); gr_cr62_sys_ru[i_dca]->SetMarkerStyle(21); gr_cr62_sys_ru[i_dca]->SetMarkerSize(1.5);
    gr_c1_sys_zr[i_dca] = (TGraphErrors*)f_sys_zr[i_dca]->Get("proton_C_1"); gr_c1_sys_zr[i_dca]->SetMarkerColor(i_dca+1); gr_c1_sys_zr[i_dca]->SetMarkerStyle(25); gr_c1_sys_zr[i_dca]->SetMarkerSize(1.5);
    gr_c2_sys_zr[i_dca] = (TGraphErrors*)f_sys_zr[i_dca]->Get("proton_C_2"); gr_c2_sys_zr[i_dca]->SetMarkerColor(i_dca+1); gr_c2_sys_zr[i_dca]->SetMarkerStyle(25); gr_c2_sys_zr[i_dca]->SetMarkerSize(1.5);
    gr_c3_sys_zr[i_dca] = (TGraphErrors*)f_sys_zr[i_dca]->Get("proton_C_3"); gr_c3_sys_zr[i_dca]->SetMarkerColor(i_dca+1); gr_c3_sys_zr[i_dca]->SetMarkerStyle(25); gr_c3_sys_zr[i_dca]->SetMarkerSize(1.5);
    gr_c4_sys_zr[i_dca] = (TGraphErrors*)f_sys_zr[i_dca]->Get("proton_C_4"); gr_c4_sys_zr[i_dca]->SetMarkerColor(i_dca+1); gr_c4_sys_zr[i_dca]->SetMarkerStyle(25); gr_c4_sys_zr[i_dca]->SetMarkerSize(1.5);
    gr_c5_sys_zr[i_dca] = (TGraphErrors*)f_sys_zr[i_dca]->Get("proton_C_5"); gr_c5_sys_zr[i_dca]->SetMarkerColor(i_dca+1); gr_c5_sys_zr[i_dca]->SetMarkerStyle(25); gr_c5_sys_zr[i_dca]->SetMarkerSize(1.5);
    gr_c6_sys_zr[i_dca] = (TGraphErrors*)f_sys_zr[i_dca]->Get("proton_C_6"); gr_c6_sys_zr[i_dca]->SetMarkerColor(i_dca+1); gr_c6_sys_zr[i_dca]->SetMarkerStyle(25); gr_c6_sys_zr[i_dca]->SetMarkerSize(1.5);
    gr_cr21_sys_zr[i_dca] = (TGraphErrors*)f_sys_zr[i_dca]->Get("proton_CR_2_1"); gr_cr21_sys_zr[i_dca]->SetMarkerColor(i_dca+1); gr_cr21_sys_zr[i_dca]->SetMarkerStyle(25); gr_cr21_sys_zr[i_dca]->SetMarkerSize(1.5);
    gr_cr31_sys_zr[i_dca] = (TGraphErrors*)f_sys_zr[i_dca]->Get("proton_CR_3_1"); gr_cr31_sys_zr[i_dca]->SetMarkerColor(i_dca+1); gr_cr31_sys_zr[i_dca]->SetMarkerStyle(25); gr_cr31_sys_zr[i_dca]->SetMarkerSize(1.5);
    gr_cr32_sys_zr[i_dca] = (TGraphErrors*)f_sys_zr[i_dca]->Get("proton_CR_3_2"); gr_cr32_sys_zr[i_dca]->SetMarkerColor(i_dca+1); gr_cr32_sys_zr[i_dca]->SetMarkerStyle(25); gr_cr32_sys_zr[i_dca]->SetMarkerSize(1.5);
    gr_cr42_sys_zr[i_dca] = (TGraphErrors*)f_sys_zr[i_dca]->Get("proton_CR_4_2"); gr_cr42_sys_zr[i_dca]->SetMarkerColor(i_dca+1); gr_cr42_sys_zr[i_dca]->SetMarkerStyle(25); gr_cr42_sys_zr[i_dca]->SetMarkerSize(1.5);
    gr_cr51_sys_zr[i_dca] = (TGraphErrors*)f_sys_zr[i_dca]->Get("proton_CR_5_1"); gr_cr51_sys_zr[i_dca]->SetMarkerColor(i_dca+1); gr_cr51_sys_zr[i_dca]->SetMarkerStyle(25); gr_cr51_sys_zr[i_dca]->SetMarkerSize(1.5);
    gr_cr62_sys_zr[i_dca] = (TGraphErrors*)f_sys_zr[i_dca]->Get("proton_CR_6_2"); gr_cr62_sys_zr[i_dca]->SetMarkerColor(i_dca+1); gr_cr62_sys_zr[i_dca]->SetMarkerStyle(25); gr_cr62_sys_zr[i_dca]->SetMarkerSize(1.5);
    for(int i_cent = 0+mergedN ; i_cent < ncent ; i_cent++){
      gr_c1_sys_ru[i_dca]->SetPointX(i_cent, gr_c1_sys_ru[i_dca]->GetPointX(i_cent) + 10*i_dca);
      gr_c2_sys_ru[i_dca]->SetPointX(i_cent, gr_c2_sys_ru[i_dca]->GetPointX(i_cent) + 10*i_dca);
      gr_c3_sys_ru[i_dca]->SetPointX(i_cent, gr_c3_sys_ru[i_dca]->GetPointX(i_cent) + 10*i_dca);
      gr_c4_sys_ru[i_dca]->SetPointX(i_cent, gr_c4_sys_ru[i_dca]->GetPointX(i_cent) + 10*i_dca);
      gr_c5_sys_ru[i_dca]->SetPointX(i_cent, gr_c5_sys_ru[i_dca]->GetPointX(i_cent) + 10*i_dca);
      gr_c6_sys_ru[i_dca]->SetPointX(i_cent, gr_c6_sys_ru[i_dca]->GetPointX(i_cent) + 10*i_dca);
      gr_cr21_sys_ru[i_dca]->SetPointX(i_cent, gr_cr21_sys_ru[i_dca]->GetPointX(i_cent) + 10*i_dca);
      gr_cr31_sys_ru[i_dca]->SetPointX(i_cent, gr_cr31_sys_ru[i_dca]->GetPointX(i_cent) + 10*i_dca);
      gr_cr32_sys_ru[i_dca]->SetPointX(i_cent, gr_cr32_sys_ru[i_dca]->GetPointX(i_cent) + 10*i_dca);
      gr_cr42_sys_ru[i_dca]->SetPointX(i_cent, gr_cr42_sys_ru[i_dca]->GetPointX(i_cent) + 10*i_dca);
      gr_cr51_sys_ru[i_dca]->SetPointX(i_cent, gr_cr51_sys_ru[i_dca]->GetPointX(i_cent) + 10*i_dca);
      gr_cr62_sys_ru[i_dca]->SetPointX(i_cent, gr_cr62_sys_ru[i_dca]->GetPointX(i_cent) + 10*i_dca);
      gr_c1_sys_zr[i_dca]->SetPointX(i_cent, gr_c1_sys_zr[i_dca]->GetPointX(i_cent) + 10*i_dca);
      gr_c2_sys_zr[i_dca]->SetPointX(i_cent, gr_c2_sys_zr[i_dca]->GetPointX(i_cent) + 10*i_dca);
      gr_c3_sys_zr[i_dca]->SetPointX(i_cent, gr_c3_sys_zr[i_dca]->GetPointX(i_cent) + 10*i_dca);
      gr_c4_sys_zr[i_dca]->SetPointX(i_cent, gr_c4_sys_zr[i_dca]->GetPointX(i_cent) + 10*i_dca);
      gr_c5_sys_zr[i_dca]->SetPointX(i_cent, gr_c5_sys_zr[i_dca]->GetPointX(i_cent) + 10*i_dca);
      gr_c6_sys_zr[i_dca]->SetPointX(i_cent, gr_c6_sys_zr[i_dca]->GetPointX(i_cent) + 10*i_dca);
      gr_cr21_sys_zr[i_dca]->SetPointX(i_cent, gr_cr21_sys_zr[i_dca]->GetPointX(i_cent) + 10*i_dca);
      gr_cr31_sys_zr[i_dca]->SetPointX(i_cent, gr_cr31_sys_zr[i_dca]->GetPointX(i_cent) + 10*i_dca);
      gr_cr32_sys_zr[i_dca]->SetPointX(i_cent, gr_cr32_sys_zr[i_dca]->GetPointX(i_cent) + 10*i_dca);
      gr_cr42_sys_zr[i_dca]->SetPointX(i_cent, gr_cr42_sys_zr[i_dca]->GetPointX(i_cent) + 10*i_dca);
      gr_cr51_sys_zr[i_dca]->SetPointX(i_cent, gr_cr51_sys_zr[i_dca]->GetPointX(i_cent) + 10*i_dca);
      gr_cr62_sys_zr[i_dca]->SetPointX(i_cent, gr_cr62_sys_zr[i_dca]->GetPointX(i_cent) + 10*i_dca);
    }
  }
  for(int i_nhf = 0 ; i_nhf < 4 ; i_nhf++){
    gr_c1_sys_ru[i_nhf+4] = (TGraphErrors*)f_sys_ru[i_nhf+4]->Get("proton_C_1"); gr_c1_sys_ru[i_nhf+4]->SetMarkerColor(i_nhf+1); gr_c1_sys_ru[i_nhf+4]->SetMarkerStyle(22); gr_c1_sys_ru[i_nhf+4]->SetMarkerSize(1.5);
    gr_c2_sys_ru[i_nhf+4] = (TGraphErrors*)f_sys_ru[i_nhf+4]->Get("proton_C_2"); gr_c2_sys_ru[i_nhf+4]->SetMarkerColor(i_nhf+1); gr_c2_sys_ru[i_nhf+4]->SetMarkerStyle(22); gr_c2_sys_ru[i_nhf+4]->SetMarkerSize(1.5);
    gr_c3_sys_ru[i_nhf+4] = (TGraphErrors*)f_sys_ru[i_nhf+4]->Get("proton_C_3"); gr_c3_sys_ru[i_nhf+4]->SetMarkerColor(i_nhf+1); gr_c3_sys_ru[i_nhf+4]->SetMarkerStyle(22); gr_c3_sys_ru[i_nhf+4]->SetMarkerSize(1.5);
    gr_c4_sys_ru[i_nhf+4] = (TGraphErrors*)f_sys_ru[i_nhf+4]->Get("proton_C_4"); gr_c4_sys_ru[i_nhf+4]->SetMarkerColor(i_nhf+1); gr_c4_sys_ru[i_nhf+4]->SetMarkerStyle(22); gr_c4_sys_ru[i_nhf+4]->SetMarkerSize(1.5);
    gr_c5_sys_ru[i_nhf+4] = (TGraphErrors*)f_sys_ru[i_nhf+4]->Get("proton_C_5"); gr_c5_sys_ru[i_nhf+4]->SetMarkerColor(i_nhf+1); gr_c5_sys_ru[i_nhf+4]->SetMarkerStyle(22); gr_c5_sys_ru[i_nhf+4]->SetMarkerSize(1.5);
    gr_c6_sys_ru[i_nhf+4] = (TGraphErrors*)f_sys_ru[i_nhf+4]->Get("proton_C_6"); gr_c6_sys_ru[i_nhf+4]->SetMarkerColor(i_nhf+1); gr_c6_sys_ru[i_nhf+4]->SetMarkerStyle(22); gr_c6_sys_ru[i_nhf+4]->SetMarkerSize(1.5);
    gr_cr21_sys_ru[i_nhf+4] = (TGraphErrors*)f_sys_ru[i_nhf+4]->Get("proton_CR_2_1"); gr_cr21_sys_ru[i_nhf+4]->SetMarkerColor(i_nhf+1); gr_cr21_sys_ru[i_nhf+4]->SetMarkerStyle(22); gr_cr21_sys_ru[i_nhf+4]->SetMarkerSize(1.5);
    gr_cr31_sys_ru[i_nhf+4] = (TGraphErrors*)f_sys_ru[i_nhf+4]->Get("proton_CR_3_1"); gr_cr31_sys_ru[i_nhf+4]->SetMarkerColor(i_nhf+1); gr_cr31_sys_ru[i_nhf+4]->SetMarkerStyle(22); gr_cr31_sys_ru[i_nhf+4]->SetMarkerSize(1.5);
    gr_cr32_sys_ru[i_nhf+4] = (TGraphErrors*)f_sys_ru[i_nhf+4]->Get("proton_CR_3_2"); gr_cr32_sys_ru[i_nhf+4]->SetMarkerColor(i_nhf+1); gr_cr32_sys_ru[i_nhf+4]->SetMarkerStyle(22); gr_cr32_sys_ru[i_nhf+4]->SetMarkerSize(1.5);
    gr_cr42_sys_ru[i_nhf+4] = (TGraphErrors*)f_sys_ru[i_nhf+4]->Get("proton_CR_4_2"); gr_cr42_sys_ru[i_nhf+4]->SetMarkerColor(i_nhf+1); gr_cr42_sys_ru[i_nhf+4]->SetMarkerStyle(22); gr_cr42_sys_ru[i_nhf+4]->SetMarkerSize(1.5);
    gr_cr51_sys_ru[i_nhf+4] = (TGraphErrors*)f_sys_ru[i_nhf+4]->Get("proton_CR_5_1"); gr_cr51_sys_ru[i_nhf+4]->SetMarkerColor(i_nhf+1); gr_cr51_sys_ru[i_nhf+4]->SetMarkerStyle(22); gr_cr51_sys_ru[i_nhf+4]->SetMarkerSize(1.5);
    gr_cr62_sys_ru[i_nhf+4] = (TGraphErrors*)f_sys_ru[i_nhf+4]->Get("proton_CR_6_2"); gr_cr62_sys_ru[i_nhf+4]->SetMarkerColor(i_nhf+1); gr_cr62_sys_ru[i_nhf+4]->SetMarkerStyle(22); gr_cr62_sys_ru[i_nhf+4]->SetMarkerSize(1.5);
    gr_c1_sys_zr[i_nhf+4] = (TGraphErrors*)f_sys_zr[i_nhf+4]->Get("proton_C_1"); gr_c1_sys_zr[i_nhf+4]->SetMarkerColor(i_nhf+1); gr_c1_sys_zr[i_nhf+4]->SetMarkerStyle(26); gr_c1_sys_zr[i_nhf+4]->SetMarkerSize(1.5);
    gr_c2_sys_zr[i_nhf+4] = (TGraphErrors*)f_sys_zr[i_nhf+4]->Get("proton_C_2"); gr_c2_sys_zr[i_nhf+4]->SetMarkerColor(i_nhf+1); gr_c2_sys_zr[i_nhf+4]->SetMarkerStyle(26); gr_c2_sys_zr[i_nhf+4]->SetMarkerSize(1.5);
    gr_c3_sys_zr[i_nhf+4] = (TGraphErrors*)f_sys_zr[i_nhf+4]->Get("proton_C_3"); gr_c3_sys_zr[i_nhf+4]->SetMarkerColor(i_nhf+1); gr_c3_sys_zr[i_nhf+4]->SetMarkerStyle(26); gr_c3_sys_zr[i_nhf+4]->SetMarkerSize(1.5);
    gr_c4_sys_zr[i_nhf+4] = (TGraphErrors*)f_sys_zr[i_nhf+4]->Get("proton_C_4"); gr_c4_sys_zr[i_nhf+4]->SetMarkerColor(i_nhf+1); gr_c4_sys_zr[i_nhf+4]->SetMarkerStyle(26); gr_c4_sys_zr[i_nhf+4]->SetMarkerSize(1.5);
    gr_c5_sys_zr[i_nhf+4] = (TGraphErrors*)f_sys_zr[i_nhf+4]->Get("proton_C_5"); gr_c5_sys_zr[i_nhf+4]->SetMarkerColor(i_nhf+1); gr_c5_sys_zr[i_nhf+4]->SetMarkerStyle(26); gr_c5_sys_zr[i_nhf+4]->SetMarkerSize(1.5);
    gr_c6_sys_zr[i_nhf+4] = (TGraphErrors*)f_sys_zr[i_nhf+4]->Get("proton_C_6"); gr_c6_sys_zr[i_nhf+4]->SetMarkerColor(i_nhf+1); gr_c6_sys_zr[i_nhf+4]->SetMarkerStyle(26); gr_c6_sys_zr[i_nhf+4]->SetMarkerSize(1.5);
    gr_cr21_sys_zr[i_nhf+4] = (TGraphErrors*)f_sys_zr[i_nhf+4]->Get("proton_CR_2_1"); gr_cr21_sys_zr[i_nhf+4]->SetMarkerColor(i_nhf+1); gr_cr21_sys_zr[i_nhf+4]->SetMarkerStyle(26); gr_cr21_sys_zr[i_nhf+4]->SetMarkerSize(1.5);
    gr_cr31_sys_zr[i_nhf+4] = (TGraphErrors*)f_sys_zr[i_nhf+4]->Get("proton_CR_3_1"); gr_cr31_sys_zr[i_nhf+4]->SetMarkerColor(i_nhf+1); gr_cr31_sys_zr[i_nhf+4]->SetMarkerStyle(26); gr_cr31_sys_zr[i_nhf+4]->SetMarkerSize(1.5);
    gr_cr32_sys_zr[i_nhf+4] = (TGraphErrors*)f_sys_zr[i_nhf+4]->Get("proton_CR_3_2"); gr_cr32_sys_zr[i_nhf+4]->SetMarkerColor(i_nhf+1); gr_cr32_sys_zr[i_nhf+4]->SetMarkerStyle(26); gr_cr32_sys_zr[i_nhf+4]->SetMarkerSize(1.5);
    gr_cr42_sys_zr[i_nhf+4] = (TGraphErrors*)f_sys_zr[i_nhf+4]->Get("proton_CR_4_2"); gr_cr42_sys_zr[i_nhf+4]->SetMarkerColor(i_nhf+1); gr_cr42_sys_zr[i_nhf+4]->SetMarkerStyle(26); gr_cr42_sys_zr[i_nhf+4]->SetMarkerSize(1.5);
    gr_cr51_sys_zr[i_nhf+4] = (TGraphErrors*)f_sys_zr[i_nhf+4]->Get("proton_CR_5_1"); gr_cr51_sys_zr[i_nhf+4]->SetMarkerColor(i_nhf+1); gr_cr51_sys_zr[i_nhf+4]->SetMarkerStyle(26); gr_cr51_sys_zr[i_nhf+4]->SetMarkerSize(1.5);
    gr_cr62_sys_zr[i_nhf+4] = (TGraphErrors*)f_sys_zr[i_nhf+4]->Get("proton_CR_6_2"); gr_cr62_sys_zr[i_nhf+4]->SetMarkerColor(i_nhf+1); gr_cr62_sys_zr[i_nhf+4]->SetMarkerStyle(26); gr_cr62_sys_zr[i_nhf+4]->SetMarkerSize(1.5);
    for(int i_cent = 0+mergedN ; i_cent < ncent ; i_cent++){
      gr_c1_sys_ru[i_nhf+4]->SetPointX(i_cent, gr_c1_sys_ru[i_nhf+4]->GetPointX(i_cent) + 10*i_nhf);
      gr_c2_sys_ru[i_nhf+4]->SetPointX(i_cent, gr_c2_sys_ru[i_nhf+4]->GetPointX(i_cent) + 10*i_nhf);
      gr_c3_sys_ru[i_nhf+4]->SetPointX(i_cent, gr_c3_sys_ru[i_nhf+4]->GetPointX(i_cent) + 10*i_nhf);
      gr_c4_sys_ru[i_nhf+4]->SetPointX(i_cent, gr_c4_sys_ru[i_nhf+4]->GetPointX(i_cent) + 10*i_nhf);
      gr_c5_sys_ru[i_nhf+4]->SetPointX(i_cent, gr_c5_sys_ru[i_nhf+4]->GetPointX(i_cent) + 10*i_nhf);
      gr_c6_sys_ru[i_nhf+4]->SetPointX(i_cent, gr_c6_sys_ru[i_nhf+4]->GetPointX(i_cent) + 10*i_nhf);
      gr_cr21_sys_ru[i_nhf+4]->SetPointX(i_cent, gr_cr21_sys_ru[i_nhf+4]->GetPointX(i_cent) + 10*i_nhf);
      gr_cr31_sys_ru[i_nhf+4]->SetPointX(i_cent, gr_cr31_sys_ru[i_nhf+4]->GetPointX(i_cent) + 10*i_nhf);
      gr_cr32_sys_ru[i_nhf+4]->SetPointX(i_cent, gr_cr32_sys_ru[i_nhf+4]->GetPointX(i_cent) + 10*i_nhf);
      gr_cr42_sys_ru[i_nhf+4]->SetPointX(i_cent, gr_cr42_sys_ru[i_nhf+4]->GetPointX(i_cent) + 10*i_nhf);
      gr_cr51_sys_ru[i_nhf+4]->SetPointX(i_cent, gr_cr51_sys_ru[i_nhf+4]->GetPointX(i_cent) + 10*i_nhf);
      gr_cr62_sys_ru[i_nhf+4]->SetPointX(i_cent, gr_cr62_sys_ru[i_nhf+4]->GetPointX(i_cent) + 10*i_nhf);
      gr_c1_sys_zr[i_nhf+4]->SetPointX(i_cent, gr_c1_sys_zr[i_nhf+4]->GetPointX(i_cent) + 10*i_nhf);
      gr_c2_sys_zr[i_nhf+4]->SetPointX(i_cent, gr_c2_sys_zr[i_nhf+4]->GetPointX(i_cent) + 10*i_nhf);
      gr_c3_sys_zr[i_nhf+4]->SetPointX(i_cent, gr_c3_sys_zr[i_nhf+4]->GetPointX(i_cent) + 10*i_nhf);
      gr_c4_sys_zr[i_nhf+4]->SetPointX(i_cent, gr_c4_sys_zr[i_nhf+4]->GetPointX(i_cent) + 10*i_nhf);
      gr_c5_sys_zr[i_nhf+4]->SetPointX(i_cent, gr_c5_sys_zr[i_nhf+4]->GetPointX(i_cent) + 10*i_nhf);
      gr_c6_sys_zr[i_nhf+4]->SetPointX(i_cent, gr_c6_sys_zr[i_nhf+4]->GetPointX(i_cent) + 10*i_nhf);
      gr_cr21_sys_zr[i_nhf+4]->SetPointX(i_cent, gr_cr21_sys_zr[i_nhf+4]->GetPointX(i_cent) + 10*i_nhf);
      gr_cr31_sys_zr[i_nhf+4]->SetPointX(i_cent, gr_cr31_sys_zr[i_nhf+4]->GetPointX(i_cent) + 10*i_nhf);
      gr_cr32_sys_zr[i_nhf+4]->SetPointX(i_cent, gr_cr32_sys_zr[i_nhf+4]->GetPointX(i_cent) + 10*i_nhf);
      gr_cr42_sys_zr[i_nhf+4]->SetPointX(i_cent, gr_cr42_sys_zr[i_nhf+4]->GetPointX(i_cent) + 10*i_nhf);
      gr_cr51_sys_zr[i_nhf+4]->SetPointX(i_cent, gr_cr51_sys_zr[i_nhf+4]->GetPointX(i_cent) + 10*i_nhf);
      gr_cr62_sys_zr[i_nhf+4]->SetPointX(i_cent, gr_cr62_sys_zr[i_nhf+4]->GetPointX(i_cent) + 10*i_nhf);
    }
  }
  for(int i_nsp = 0 ; i_nsp < 4 ; i_nsp++){
    gr_c1_sys_ru[i_nsp+4*2] = (TGraphErrors*)f_sys_ru[i_nsp+4*2]->Get("proton_C_1"); gr_c1_sys_ru[i_nsp+4*2]->SetMarkerColor(i_nsp+1); gr_c1_sys_ru[i_nsp+4*2]->SetMarkerStyle(23); gr_c1_sys_ru[i_nsp+4*2]->SetMarkerSize(1.5);
    gr_c2_sys_ru[i_nsp+4*2] = (TGraphErrors*)f_sys_ru[i_nsp+4*2]->Get("proton_C_2"); gr_c2_sys_ru[i_nsp+4*2]->SetMarkerColor(i_nsp+1); gr_c2_sys_ru[i_nsp+4*2]->SetMarkerStyle(23); gr_c2_sys_ru[i_nsp+4*2]->SetMarkerSize(1.5);
    gr_c3_sys_ru[i_nsp+4*2] = (TGraphErrors*)f_sys_ru[i_nsp+4*2]->Get("proton_C_3"); gr_c3_sys_ru[i_nsp+4*2]->SetMarkerColor(i_nsp+1); gr_c3_sys_ru[i_nsp+4*2]->SetMarkerStyle(23); gr_c3_sys_ru[i_nsp+4*2]->SetMarkerSize(1.5);
    gr_c4_sys_ru[i_nsp+4*2] = (TGraphErrors*)f_sys_ru[i_nsp+4*2]->Get("proton_C_4"); gr_c4_sys_ru[i_nsp+4*2]->SetMarkerColor(i_nsp+1); gr_c4_sys_ru[i_nsp+4*2]->SetMarkerStyle(23); gr_c4_sys_ru[i_nsp+4*2]->SetMarkerSize(1.5);
    gr_c5_sys_ru[i_nsp+4*2] = (TGraphErrors*)f_sys_ru[i_nsp+4*2]->Get("proton_C_5"); gr_c5_sys_ru[i_nsp+4*2]->SetMarkerColor(i_nsp+1); gr_c5_sys_ru[i_nsp+4*2]->SetMarkerStyle(23); gr_c5_sys_ru[i_nsp+4*2]->SetMarkerSize(1.5);
    gr_c6_sys_ru[i_nsp+4*2] = (TGraphErrors*)f_sys_ru[i_nsp+4*2]->Get("proton_C_6"); gr_c6_sys_ru[i_nsp+4*2]->SetMarkerColor(i_nsp+1); gr_c6_sys_ru[i_nsp+4*2]->SetMarkerStyle(23); gr_c6_sys_ru[i_nsp+4*2]->SetMarkerSize(1.5);
    gr_cr21_sys_ru[i_nsp+4*2] = (TGraphErrors*)f_sys_ru[i_nsp+4*2]->Get("proton_CR_2_1"); gr_cr21_sys_ru[i_nsp+4*2]->SetMarkerColor(i_nsp+1); gr_cr21_sys_ru[i_nsp+4*2]->SetMarkerStyle(23); gr_cr21_sys_ru[i_nsp+4*2]->SetMarkerSize(1.5);
    gr_cr31_sys_ru[i_nsp+4*2] = (TGraphErrors*)f_sys_ru[i_nsp+4*2]->Get("proton_CR_3_1"); gr_cr31_sys_ru[i_nsp+4*2]->SetMarkerColor(i_nsp+1); gr_cr31_sys_ru[i_nsp+4*2]->SetMarkerStyle(23); gr_cr31_sys_ru[i_nsp+4*2]->SetMarkerSize(1.5);
    gr_cr32_sys_ru[i_nsp+4*2] = (TGraphErrors*)f_sys_ru[i_nsp+4*2]->Get("proton_CR_3_2"); gr_cr32_sys_ru[i_nsp+4*2]->SetMarkerColor(i_nsp+1); gr_cr32_sys_ru[i_nsp+4*2]->SetMarkerStyle(23); gr_cr32_sys_ru[i_nsp+4*2]->SetMarkerSize(1.5);
    gr_cr42_sys_ru[i_nsp+4*2] = (TGraphErrors*)f_sys_ru[i_nsp+4*2]->Get("proton_CR_4_2"); gr_cr42_sys_ru[i_nsp+4*2]->SetMarkerColor(i_nsp+1); gr_cr42_sys_ru[i_nsp+4*2]->SetMarkerStyle(23); gr_cr42_sys_ru[i_nsp+4*2]->SetMarkerSize(1.5);
    gr_cr51_sys_ru[i_nsp+4*2] = (TGraphErrors*)f_sys_ru[i_nsp+4*2]->Get("proton_CR_5_1"); gr_cr51_sys_ru[i_nsp+4*2]->SetMarkerColor(i_nsp+1); gr_cr51_sys_ru[i_nsp+4*2]->SetMarkerStyle(23); gr_cr51_sys_ru[i_nsp+4*2]->SetMarkerSize(1.5);
    gr_cr62_sys_ru[i_nsp+4*2] = (TGraphErrors*)f_sys_ru[i_nsp+4*2]->Get("proton_CR_6_2"); gr_cr62_sys_ru[i_nsp+4*2]->SetMarkerColor(i_nsp+1); gr_cr62_sys_ru[i_nsp+4*2]->SetMarkerStyle(23); gr_cr62_sys_ru[i_nsp+4*2]->SetMarkerSize(1.5);
    gr_c1_sys_zr[i_nsp+4*2] = (TGraphErrors*)f_sys_zr[i_nsp+4*2]->Get("proton_C_1"); gr_c1_sys_zr[i_nsp+4*2]->SetMarkerColor(i_nsp+1); gr_c1_sys_zr[i_nsp+4*2]->SetMarkerStyle(23); gr_c1_sys_zr[i_nsp+4*2]->SetMarkerSize(1.5);
    gr_c2_sys_zr[i_nsp+4*2] = (TGraphErrors*)f_sys_zr[i_nsp+4*2]->Get("proton_C_2"); gr_c2_sys_zr[i_nsp+4*2]->SetMarkerColor(i_nsp+1); gr_c2_sys_zr[i_nsp+4*2]->SetMarkerStyle(23); gr_c2_sys_zr[i_nsp+4*2]->SetMarkerSize(1.5);
    gr_c3_sys_zr[i_nsp+4*2] = (TGraphErrors*)f_sys_zr[i_nsp+4*2]->Get("proton_C_3"); gr_c3_sys_zr[i_nsp+4*2]->SetMarkerColor(i_nsp+1); gr_c3_sys_zr[i_nsp+4*2]->SetMarkerStyle(23); gr_c3_sys_zr[i_nsp+4*2]->SetMarkerSize(1.5);
    gr_c4_sys_zr[i_nsp+4*2] = (TGraphErrors*)f_sys_zr[i_nsp+4*2]->Get("proton_C_4"); gr_c4_sys_zr[i_nsp+4*2]->SetMarkerColor(i_nsp+1); gr_c4_sys_zr[i_nsp+4*2]->SetMarkerStyle(23); gr_c4_sys_zr[i_nsp+4*2]->SetMarkerSize(1.5);
    gr_c5_sys_zr[i_nsp+4*2] = (TGraphErrors*)f_sys_zr[i_nsp+4*2]->Get("proton_C_5"); gr_c5_sys_zr[i_nsp+4*2]->SetMarkerColor(i_nsp+1); gr_c5_sys_zr[i_nsp+4*2]->SetMarkerStyle(23); gr_c5_sys_zr[i_nsp+4*2]->SetMarkerSize(1.5);
    gr_c6_sys_zr[i_nsp+4*2] = (TGraphErrors*)f_sys_zr[i_nsp+4*2]->Get("proton_C_6"); gr_c6_sys_zr[i_nsp+4*2]->SetMarkerColor(i_nsp+1); gr_c6_sys_zr[i_nsp+4*2]->SetMarkerStyle(23); gr_c6_sys_zr[i_nsp+4*2]->SetMarkerSize(1.5);
    gr_cr21_sys_zr[i_nsp+4*2] = (TGraphErrors*)f_sys_zr[i_nsp+4*2]->Get("proton_CR_2_1"); gr_cr21_sys_zr[i_nsp+4*2]->SetMarkerColor(i_nsp+1); gr_cr21_sys_zr[i_nsp+4*2]->SetMarkerStyle(23); gr_cr21_sys_zr[i_nsp+4*2]->SetMarkerSize(1.5);
    gr_cr31_sys_zr[i_nsp+4*2] = (TGraphErrors*)f_sys_zr[i_nsp+4*2]->Get("proton_CR_3_1"); gr_cr31_sys_zr[i_nsp+4*2]->SetMarkerColor(i_nsp+1); gr_cr31_sys_zr[i_nsp+4*2]->SetMarkerStyle(23); gr_cr31_sys_zr[i_nsp+4*2]->SetMarkerSize(1.5);
    gr_cr32_sys_zr[i_nsp+4*2] = (TGraphErrors*)f_sys_zr[i_nsp+4*2]->Get("proton_CR_3_2"); gr_cr32_sys_zr[i_nsp+4*2]->SetMarkerColor(i_nsp+1); gr_cr32_sys_zr[i_nsp+4*2]->SetMarkerStyle(23); gr_cr32_sys_zr[i_nsp+4*2]->SetMarkerSize(1.5);
    gr_cr42_sys_zr[i_nsp+4*2] = (TGraphErrors*)f_sys_zr[i_nsp+4*2]->Get("proton_CR_4_2"); gr_cr42_sys_zr[i_nsp+4*2]->SetMarkerColor(i_nsp+1); gr_cr42_sys_zr[i_nsp+4*2]->SetMarkerStyle(23); gr_cr42_sys_zr[i_nsp+4*2]->SetMarkerSize(1.5);
    gr_cr51_sys_zr[i_nsp+4*2] = (TGraphErrors*)f_sys_zr[i_nsp+4*2]->Get("proton_CR_5_1"); gr_cr51_sys_zr[i_nsp+4*2]->SetMarkerColor(i_nsp+1); gr_cr51_sys_zr[i_nsp+4*2]->SetMarkerStyle(23); gr_cr51_sys_zr[i_nsp+4*2]->SetMarkerSize(1.5);
    gr_cr62_sys_zr[i_nsp+4*2] = (TGraphErrors*)f_sys_zr[i_nsp+4*2]->Get("proton_CR_6_2"); gr_cr62_sys_zr[i_nsp+4*2]->SetMarkerColor(i_nsp+1); gr_cr62_sys_zr[i_nsp+4*2]->SetMarkerStyle(23); gr_cr62_sys_zr[i_nsp+4*2]->SetMarkerSize(1.5);

    for(int i_cent = 0+mergedN ; i_cent < ncent ; i_cent++){
      gr_c1_sys_ru[i_nsp+4*2]->SetPointX(i_cent, gr_c1_sys_ru[i_nsp+4*2]->GetPointX(i_cent) + 10*i_nsp);
      gr_c2_sys_ru[i_nsp+4*2]->SetPointX(i_cent, gr_c2_sys_ru[i_nsp+4*2]->GetPointX(i_cent) + 10*i_nsp);
      gr_c3_sys_ru[i_nsp+4*2]->SetPointX(i_cent, gr_c3_sys_ru[i_nsp+4*2]->GetPointX(i_cent) + 10*i_nsp);
      gr_c4_sys_ru[i_nsp+4*2]->SetPointX(i_cent, gr_c4_sys_ru[i_nsp+4*2]->GetPointX(i_cent) + 10*i_nsp);
      gr_c5_sys_ru[i_nsp+4*2]->SetPointX(i_cent, gr_c5_sys_ru[i_nsp+4*2]->GetPointX(i_cent) + 10*i_nsp);
      gr_c6_sys_ru[i_nsp+4*2]->SetPointX(i_cent, gr_c6_sys_ru[i_nsp+4*2]->GetPointX(i_cent) + 10*i_nsp);
      gr_cr21_sys_ru[i_nsp+4*2]->SetPointX(i_cent, gr_cr21_sys_ru[i_nsp+4*2]->GetPointX(i_cent) + 10*i_nsp);
      gr_cr31_sys_ru[i_nsp+4*2]->SetPointX(i_cent, gr_cr31_sys_ru[i_nsp+4*2]->GetPointX(i_cent) + 10*i_nsp);
      gr_cr32_sys_ru[i_nsp+4*2]->SetPointX(i_cent, gr_cr32_sys_ru[i_nsp+4*2]->GetPointX(i_cent) + 10*i_nsp);
      gr_cr42_sys_ru[i_nsp+4*2]->SetPointX(i_cent, gr_cr42_sys_ru[i_nsp+4*2]->GetPointX(i_cent) + 10*i_nsp);
      gr_cr51_sys_ru[i_nsp+4*2]->SetPointX(i_cent, gr_cr51_sys_ru[i_nsp+4*2]->GetPointX(i_cent) + 10*i_nsp);
      gr_cr62_sys_ru[i_nsp+4*2]->SetPointX(i_cent, gr_cr62_sys_ru[i_nsp+4*2]->GetPointX(i_cent) + 10*i_nsp);
      gr_c1_sys_zr[i_nsp+4*2]->SetPointX(i_cent, gr_c1_sys_zr[i_nsp+4*2]->GetPointX(i_cent) + 10*i_nsp);
      gr_c2_sys_zr[i_nsp+4*2]->SetPointX(i_cent, gr_c2_sys_zr[i_nsp+4*2]->GetPointX(i_cent) + 10*i_nsp);
      gr_c3_sys_zr[i_nsp+4*2]->SetPointX(i_cent, gr_c3_sys_zr[i_nsp+4*2]->GetPointX(i_cent) + 10*i_nsp);
      gr_c4_sys_zr[i_nsp+4*2]->SetPointX(i_cent, gr_c4_sys_zr[i_nsp+4*2]->GetPointX(i_cent) + 10*i_nsp);
      gr_c5_sys_zr[i_nsp+4*2]->SetPointX(i_cent, gr_c5_sys_zr[i_nsp+4*2]->GetPointX(i_cent) + 10*i_nsp);
      gr_c6_sys_zr[i_nsp+4*2]->SetPointX(i_cent, gr_c6_sys_zr[i_nsp+4*2]->GetPointX(i_cent) + 10*i_nsp);
      gr_cr21_sys_zr[i_nsp+4*2]->SetPointX(i_cent, gr_cr21_sys_zr[i_nsp+4*2]->GetPointX(i_cent) + 10*i_nsp);
      gr_cr31_sys_zr[i_nsp+4*2]->SetPointX(i_cent, gr_cr31_sys_zr[i_nsp+4*2]->GetPointX(i_cent) + 10*i_nsp);
      gr_cr32_sys_zr[i_nsp+4*2]->SetPointX(i_cent, gr_cr32_sys_zr[i_nsp+4*2]->GetPointX(i_cent) + 10*i_nsp);
      gr_cr42_sys_zr[i_nsp+4*2]->SetPointX(i_cent, gr_cr42_sys_zr[i_nsp+4*2]->GetPointX(i_cent) + 10*i_nsp);
      gr_cr51_sys_zr[i_nsp+4*2]->SetPointX(i_cent, gr_cr51_sys_zr[i_nsp+4*2]->GetPointX(i_cent) + 10*i_nsp);
      gr_cr62_sys_zr[i_nsp+4*2]->SetPointX(i_cent, gr_cr62_sys_zr[i_nsp+4*2]->GetPointX(i_cent) + 10*i_nsp);
    }
  }
  for(int i_m2 = 0 ; i_m2 < 4 ; i_m2++){
    gr_c1_sys_ru[i_m2+4*3] = (TGraphErrors*)f_sys_ru[i_m2+4*3]->Get("proton_C_1"); gr_c1_sys_ru[i_m2+4*3]->SetMarkerColor(i_m2+1); gr_c1_sys_ru[i_m2+4*3]->SetMarkerStyle(33); gr_c1_sys_ru[i_m2+4*3]->SetMarkerSize(1.5);
    gr_c2_sys_ru[i_m2+4*3] = (TGraphErrors*)f_sys_ru[i_m2+4*3]->Get("proton_C_2"); gr_c2_sys_ru[i_m2+4*3]->SetMarkerColor(i_m2+1); gr_c2_sys_ru[i_m2+4*3]->SetMarkerStyle(33); gr_c2_sys_ru[i_m2+4*3]->SetMarkerSize(1.5);
    gr_c3_sys_ru[i_m2+4*3] = (TGraphErrors*)f_sys_ru[i_m2+4*3]->Get("proton_C_3"); gr_c3_sys_ru[i_m2+4*3]->SetMarkerColor(i_m2+1); gr_c3_sys_ru[i_m2+4*3]->SetMarkerStyle(33); gr_c3_sys_ru[i_m2+4*3]->SetMarkerSize(1.5);
    gr_c4_sys_ru[i_m2+4*3] = (TGraphErrors*)f_sys_ru[i_m2+4*3]->Get("proton_C_4"); gr_c4_sys_ru[i_m2+4*3]->SetMarkerColor(i_m2+1); gr_c4_sys_ru[i_m2+4*3]->SetMarkerStyle(33); gr_c4_sys_ru[i_m2+4*3]->SetMarkerSize(1.5);
    gr_c5_sys_ru[i_m2+4*3] = (TGraphErrors*)f_sys_ru[i_m2+4*3]->Get("proton_C_5"); gr_c5_sys_ru[i_m2+4*3]->SetMarkerColor(i_m2+1); gr_c5_sys_ru[i_m2+4*3]->SetMarkerStyle(33); gr_c5_sys_ru[i_m2+4*3]->SetMarkerSize(1.5);
    gr_c6_sys_ru[i_m2+4*3] = (TGraphErrors*)f_sys_ru[i_m2+4*3]->Get("proton_C_6"); gr_c6_sys_ru[i_m2+4*3]->SetMarkerColor(i_m2+1); gr_c6_sys_ru[i_m2+4*3]->SetMarkerStyle(33); gr_c6_sys_ru[i_m2+4*3]->SetMarkerSize(1.5);
    gr_cr21_sys_ru[i_m2+4*3] = (TGraphErrors*)f_sys_ru[i_m2+4*3]->Get("proton_CR_2_1"); gr_cr21_sys_ru[i_m2+4*3]->SetMarkerColor(i_m2+1); gr_cr21_sys_ru[i_m2+4*3]->SetMarkerStyle(33); gr_cr21_sys_ru[i_m2+4*3]->SetMarkerSize(1.5);
    gr_cr31_sys_ru[i_m2+4*3] = (TGraphErrors*)f_sys_ru[i_m2+4*3]->Get("proton_CR_3_1"); gr_cr31_sys_ru[i_m2+4*3]->SetMarkerColor(i_m2+1); gr_cr31_sys_ru[i_m2+4*3]->SetMarkerStyle(33); gr_cr31_sys_ru[i_m2+4*3]->SetMarkerSize(1.5);
    gr_cr32_sys_ru[i_m2+4*3] = (TGraphErrors*)f_sys_ru[i_m2+4*3]->Get("proton_CR_3_2"); gr_cr32_sys_ru[i_m2+4*3]->SetMarkerColor(i_m2+1); gr_cr32_sys_ru[i_m2+4*3]->SetMarkerStyle(33); gr_cr32_sys_ru[i_m2+4*3]->SetMarkerSize(1.5);
    gr_cr42_sys_ru[i_m2+4*3] = (TGraphErrors*)f_sys_ru[i_m2+4*3]->Get("proton_CR_4_2"); gr_cr42_sys_ru[i_m2+4*3]->SetMarkerColor(i_m2+1); gr_cr42_sys_ru[i_m2+4*3]->SetMarkerStyle(33); gr_cr42_sys_ru[i_m2+4*3]->SetMarkerSize(1.5);
    gr_cr51_sys_ru[i_m2+4*3] = (TGraphErrors*)f_sys_ru[i_m2+4*3]->Get("proton_CR_5_1"); gr_cr51_sys_ru[i_m2+4*3]->SetMarkerColor(i_m2+1); gr_cr51_sys_ru[i_m2+4*3]->SetMarkerStyle(33); gr_cr51_sys_ru[i_m2+4*3]->SetMarkerSize(1.5);
    gr_cr62_sys_ru[i_m2+4*3] = (TGraphErrors*)f_sys_ru[i_m2+4*3]->Get("proton_CR_6_2"); gr_cr62_sys_ru[i_m2+4*3]->SetMarkerColor(i_m2+1); gr_cr62_sys_ru[i_m2+4*3]->SetMarkerStyle(33); gr_cr62_sys_ru[i_m2+4*3]->SetMarkerSize(1.5);
    gr_c1_sys_zr[i_m2+4*3] = (TGraphErrors*)f_sys_zr[i_m2+4*3]->Get("proton_C_1"); gr_c1_sys_zr[i_m2+4*3]->SetMarkerColor(i_m2+1); gr_c1_sys_zr[i_m2+4*3]->SetMarkerStyle(27); gr_c1_sys_zr[i_m2+4*3]->SetMarkerSize(1.5);
    gr_c2_sys_zr[i_m2+4*3] = (TGraphErrors*)f_sys_zr[i_m2+4*3]->Get("proton_C_2"); gr_c2_sys_zr[i_m2+4*3]->SetMarkerColor(i_m2+1); gr_c2_sys_zr[i_m2+4*3]->SetMarkerStyle(27); gr_c2_sys_zr[i_m2+4*3]->SetMarkerSize(1.5);
    gr_c3_sys_zr[i_m2+4*3] = (TGraphErrors*)f_sys_zr[i_m2+4*3]->Get("proton_C_3"); gr_c3_sys_zr[i_m2+4*3]->SetMarkerColor(i_m2+1); gr_c3_sys_zr[i_m2+4*3]->SetMarkerStyle(27); gr_c3_sys_zr[i_m2+4*3]->SetMarkerSize(1.5);
    gr_c4_sys_zr[i_m2+4*3] = (TGraphErrors*)f_sys_zr[i_m2+4*3]->Get("proton_C_4"); gr_c4_sys_zr[i_m2+4*3]->SetMarkerColor(i_m2+1); gr_c4_sys_zr[i_m2+4*3]->SetMarkerStyle(27); gr_c4_sys_zr[i_m2+4*3]->SetMarkerSize(1.5);
    gr_c5_sys_zr[i_m2+4*3] = (TGraphErrors*)f_sys_zr[i_m2+4*3]->Get("proton_C_5"); gr_c5_sys_zr[i_m2+4*3]->SetMarkerColor(i_m2+1); gr_c5_sys_zr[i_m2+4*3]->SetMarkerStyle(27); gr_c5_sys_zr[i_m2+4*3]->SetMarkerSize(1.5);
    gr_c6_sys_zr[i_m2+4*3] = (TGraphErrors*)f_sys_zr[i_m2+4*3]->Get("proton_C_6"); gr_c6_sys_zr[i_m2+4*3]->SetMarkerColor(i_m2+1); gr_c6_sys_zr[i_m2+4*3]->SetMarkerStyle(27); gr_c6_sys_zr[i_m2+4*3]->SetMarkerSize(1.5);
    gr_cr21_sys_zr[i_m2+4*3] = (TGraphErrors*)f_sys_zr[i_m2+4*3]->Get("proton_CR_2_1"); gr_cr21_sys_zr[i_m2+4*3]->SetMarkerColor(i_m2+1); gr_cr21_sys_zr[i_m2+4*3]->SetMarkerStyle(27); gr_cr21_sys_zr[i_m2+4*3]->SetMarkerSize(1.5);
    gr_cr31_sys_zr[i_m2+4*3] = (TGraphErrors*)f_sys_zr[i_m2+4*3]->Get("proton_CR_3_1"); gr_cr31_sys_zr[i_m2+4*3]->SetMarkerColor(i_m2+1); gr_cr31_sys_zr[i_m2+4*3]->SetMarkerStyle(27); gr_cr31_sys_zr[i_m2+4*3]->SetMarkerSize(1.5);
    gr_cr32_sys_zr[i_m2+4*3] = (TGraphErrors*)f_sys_zr[i_m2+4*3]->Get("proton_CR_3_2"); gr_cr32_sys_zr[i_m2+4*3]->SetMarkerColor(i_m2+1); gr_cr32_sys_zr[i_m2+4*3]->SetMarkerStyle(27); gr_cr32_sys_zr[i_m2+4*3]->SetMarkerSize(1.5);
    gr_cr42_sys_zr[i_m2+4*3] = (TGraphErrors*)f_sys_zr[i_m2+4*3]->Get("proton_CR_4_2"); gr_cr42_sys_zr[i_m2+4*3]->SetMarkerColor(i_m2+1); gr_cr42_sys_zr[i_m2+4*3]->SetMarkerStyle(27); gr_cr42_sys_zr[i_m2+4*3]->SetMarkerSize(1.5);
    gr_cr51_sys_zr[i_m2+4*3] = (TGraphErrors*)f_sys_zr[i_m2+4*3]->Get("proton_CR_5_1"); gr_cr51_sys_zr[i_m2+4*3]->SetMarkerColor(i_m2+1); gr_cr51_sys_zr[i_m2+4*3]->SetMarkerStyle(27); gr_cr51_sys_zr[i_m2+4*3]->SetMarkerSize(1.5);
    gr_cr62_sys_zr[i_m2+4*3] = (TGraphErrors*)f_sys_zr[i_m2+4*3]->Get("proton_CR_6_2"); gr_cr62_sys_zr[i_m2+4*3]->SetMarkerColor(i_m2+1); gr_cr62_sys_zr[i_m2+4*3]->SetMarkerStyle(27); gr_cr62_sys_zr[i_m2+4*3]->SetMarkerSize(1.5);

    for(int i_cent = 0+mergedN ; i_cent < ncent ; i_cent++){
      gr_c1_sys_ru[i_m2+4*3]->SetPointX(i_cent, gr_c1_sys_ru[i_m2+4*3]->GetPointX(i_cent) + 10*i_m2);
      gr_c2_sys_ru[i_m2+4*3]->SetPointX(i_cent, gr_c2_sys_ru[i_m2+4*3]->GetPointX(i_cent) + 10*i_m2);
      gr_c3_sys_ru[i_m2+4*3]->SetPointX(i_cent, gr_c3_sys_ru[i_m2+4*3]->GetPointX(i_cent) + 10*i_m2);
      gr_c4_sys_ru[i_m2+4*3]->SetPointX(i_cent, gr_c4_sys_ru[i_m2+4*3]->GetPointX(i_cent) + 10*i_m2);
      gr_c5_sys_ru[i_m2+4*3]->SetPointX(i_cent, gr_c5_sys_ru[i_m2+4*3]->GetPointX(i_cent) + 10*i_m2);
      gr_c6_sys_ru[i_m2+4*3]->SetPointX(i_cent, gr_c6_sys_ru[i_m2+4*3]->GetPointX(i_cent) + 10*i_m2);
      gr_cr21_sys_ru[i_m2+4*3]->SetPointX(i_cent, gr_cr21_sys_ru[i_m2+4*3]->GetPointX(i_cent) + 10*i_m2);
      gr_cr31_sys_ru[i_m2+4*3]->SetPointX(i_cent, gr_cr31_sys_ru[i_m2+4*3]->GetPointX(i_cent) + 10*i_m2);
      gr_cr32_sys_ru[i_m2+4*3]->SetPointX(i_cent, gr_cr32_sys_ru[i_m2+4*3]->GetPointX(i_cent) + 10*i_m2);
      gr_cr42_sys_ru[i_m2+4*3]->SetPointX(i_cent, gr_cr42_sys_ru[i_m2+4*3]->GetPointX(i_cent) + 10*i_m2);
      gr_cr51_sys_ru[i_m2+4*3]->SetPointX(i_cent, gr_cr51_sys_ru[i_m2+4*3]->GetPointX(i_cent) + 10*i_m2);
      gr_cr62_sys_ru[i_m2+4*3]->SetPointX(i_cent, gr_cr62_sys_ru[i_m2+4*3]->GetPointX(i_cent) + 10*i_m2);
      gr_c1_sys_zr[i_m2+4*3]->SetPointX(i_cent, gr_c1_sys_zr[i_m2+4*3]->GetPointX(i_cent) + 10*i_m2);
      gr_c2_sys_zr[i_m2+4*3]->SetPointX(i_cent, gr_c2_sys_zr[i_m2+4*3]->GetPointX(i_cent) + 10*i_m2);
      gr_c3_sys_zr[i_m2+4*3]->SetPointX(i_cent, gr_c3_sys_zr[i_m2+4*3]->GetPointX(i_cent) + 10*i_m2);
      gr_c4_sys_zr[i_m2+4*3]->SetPointX(i_cent, gr_c4_sys_zr[i_m2+4*3]->GetPointX(i_cent) + 10*i_m2);
      gr_c5_sys_zr[i_m2+4*3]->SetPointX(i_cent, gr_c5_sys_zr[i_m2+4*3]->GetPointX(i_cent) + 10*i_m2);
      gr_c6_sys_zr[i_m2+4*3]->SetPointX(i_cent, gr_c6_sys_zr[i_m2+4*3]->GetPointX(i_cent) + 10*i_m2);
      gr_cr21_sys_zr[i_m2+4*3]->SetPointX(i_cent, gr_cr21_sys_zr[i_m2+4*3]->GetPointX(i_cent) + 10*i_m2);
      gr_cr31_sys_zr[i_m2+4*3]->SetPointX(i_cent, gr_cr31_sys_zr[i_m2+4*3]->GetPointX(i_cent) + 10*i_m2);
      gr_cr32_sys_zr[i_m2+4*3]->SetPointX(i_cent, gr_cr32_sys_zr[i_m2+4*3]->GetPointX(i_cent) + 10*i_m2);
      gr_cr42_sys_zr[i_m2+4*3]->SetPointX(i_cent, gr_cr42_sys_zr[i_m2+4*3]->GetPointX(i_cent) + 10*i_m2);
      gr_cr51_sys_zr[i_m2+4*3]->SetPointX(i_cent, gr_cr51_sys_zr[i_m2+4*3]->GetPointX(i_cent) + 10*i_m2);
      gr_cr62_sys_zr[i_m2+4*3]->SetPointX(i_cent, gr_cr62_sys_zr[i_m2+4*3]->GetPointX(i_cent) + 10*i_m2);
    }
  }
  for(int i_def = 0 ; i_def < 4 ; i_def++){
    gr_c1_sys_ru[i_def+4*4] = (TGraphErrors*)f_sys_ru[i_def+4*4]->Get("proton_C_1"); gr_c1_sys_ru[i_def+4*4]->SetMarkerColor(i_def+1); gr_c1_sys_ru[i_def+4*4]->SetMarkerStyle(34); gr_c1_sys_ru[i_def+4*4]->SetMarkerSize(1.5);
    gr_c2_sys_ru[i_def+4*4] = (TGraphErrors*)f_sys_ru[i_def+4*4]->Get("proton_C_2"); gr_c2_sys_ru[i_def+4*4]->SetMarkerColor(i_def+1); gr_c2_sys_ru[i_def+4*4]->SetMarkerStyle(34); gr_c2_sys_ru[i_def+4*4]->SetMarkerSize(1.5);
    gr_c3_sys_ru[i_def+4*4] = (TGraphErrors*)f_sys_ru[i_def+4*4]->Get("proton_C_3"); gr_c3_sys_ru[i_def+4*4]->SetMarkerColor(i_def+1); gr_c3_sys_ru[i_def+4*4]->SetMarkerStyle(34); gr_c3_sys_ru[i_def+4*4]->SetMarkerSize(1.5);
    gr_c4_sys_ru[i_def+4*4] = (TGraphErrors*)f_sys_ru[i_def+4*4]->Get("proton_C_4"); gr_c4_sys_ru[i_def+4*4]->SetMarkerColor(i_def+1); gr_c4_sys_ru[i_def+4*4]->SetMarkerStyle(34); gr_c4_sys_ru[i_def+4*4]->SetMarkerSize(1.5);
    gr_c5_sys_ru[i_def+4*4] = (TGraphErrors*)f_sys_ru[i_def+4*4]->Get("proton_C_5"); gr_c5_sys_ru[i_def+4*4]->SetMarkerColor(i_def+1); gr_c5_sys_ru[i_def+4*4]->SetMarkerStyle(34); gr_c5_sys_ru[i_def+4*4]->SetMarkerSize(1.5);
    gr_c6_sys_ru[i_def+4*4] = (TGraphErrors*)f_sys_ru[i_def+4*4]->Get("proton_C_6"); gr_c6_sys_ru[i_def+4*4]->SetMarkerColor(i_def+1); gr_c6_sys_ru[i_def+4*4]->SetMarkerStyle(34); gr_c6_sys_ru[i_def+4*4]->SetMarkerSize(1.5);
    gr_cr21_sys_ru[i_def+4*4] = (TGraphErrors*)f_sys_ru[i_def+4*4]->Get("proton_CR_2_1"); gr_cr21_sys_ru[i_def+4*4]->SetMarkerColor(i_def+1); gr_cr21_sys_ru[i_def+4*4]->SetMarkerStyle(34); gr_cr21_sys_ru[i_def+4*4]->SetMarkerSize(1.5);
    gr_cr31_sys_ru[i_def+4*4] = (TGraphErrors*)f_sys_ru[i_def+4*4]->Get("proton_CR_3_1"); gr_cr31_sys_ru[i_def+4*4]->SetMarkerColor(i_def+1); gr_cr31_sys_ru[i_def+4*4]->SetMarkerStyle(34); gr_cr31_sys_ru[i_def+4*4]->SetMarkerSize(1.5);
    gr_cr32_sys_ru[i_def+4*4] = (TGraphErrors*)f_sys_ru[i_def+4*4]->Get("proton_CR_3_2"); gr_cr32_sys_ru[i_def+4*4]->SetMarkerColor(i_def+1); gr_cr32_sys_ru[i_def+4*4]->SetMarkerStyle(34); gr_cr32_sys_ru[i_def+4*4]->SetMarkerSize(1.5);
    gr_cr42_sys_ru[i_def+4*4] = (TGraphErrors*)f_sys_ru[i_def+4*4]->Get("proton_CR_4_2"); gr_cr42_sys_ru[i_def+4*4]->SetMarkerColor(i_def+1); gr_cr42_sys_ru[i_def+4*4]->SetMarkerStyle(34); gr_cr42_sys_ru[i_def+4*4]->SetMarkerSize(1.5);
    gr_cr51_sys_ru[i_def+4*4] = (TGraphErrors*)f_sys_ru[i_def+4*4]->Get("proton_CR_5_1"); gr_cr51_sys_ru[i_def+4*4]->SetMarkerColor(i_def+1); gr_cr51_sys_ru[i_def+4*4]->SetMarkerStyle(34); gr_cr51_sys_ru[i_def+4*4]->SetMarkerSize(1.5);
    gr_cr62_sys_ru[i_def+4*4] = (TGraphErrors*)f_sys_ru[i_def+4*4]->Get("proton_CR_6_2"); gr_cr62_sys_ru[i_def+4*4]->SetMarkerColor(i_def+1); gr_cr62_sys_ru[i_def+4*4]->SetMarkerStyle(34); gr_cr62_sys_ru[i_def+4*4]->SetMarkerSize(1.5);
    gr_c1_sys_zr[i_def+4*4] = (TGraphErrors*)f_sys_zr[i_def+4*4]->Get("proton_C_1"); gr_c1_sys_zr[i_def+4*4]->SetMarkerColor(i_def+1); gr_c1_sys_zr[i_def+4*4]->SetMarkerStyle(28); gr_c1_sys_zr[i_def+4*4]->SetMarkerSize(1.5);
    gr_c2_sys_zr[i_def+4*4] = (TGraphErrors*)f_sys_zr[i_def+4*4]->Get("proton_C_2"); gr_c2_sys_zr[i_def+4*4]->SetMarkerColor(i_def+1); gr_c2_sys_zr[i_def+4*4]->SetMarkerStyle(28); gr_c2_sys_zr[i_def+4*4]->SetMarkerSize(1.5);
    gr_c3_sys_zr[i_def+4*4] = (TGraphErrors*)f_sys_zr[i_def+4*4]->Get("proton_C_3"); gr_c3_sys_zr[i_def+4*4]->SetMarkerColor(i_def+1); gr_c3_sys_zr[i_def+4*4]->SetMarkerStyle(28); gr_c3_sys_zr[i_def+4*4]->SetMarkerSize(1.5);
    gr_c4_sys_zr[i_def+4*4] = (TGraphErrors*)f_sys_zr[i_def+4*4]->Get("proton_C_4"); gr_c4_sys_zr[i_def+4*4]->SetMarkerColor(i_def+1); gr_c4_sys_zr[i_def+4*4]->SetMarkerStyle(28); gr_c4_sys_zr[i_def+4*4]->SetMarkerSize(1.5);
    gr_c5_sys_zr[i_def+4*4] = (TGraphErrors*)f_sys_zr[i_def+4*4]->Get("proton_C_5"); gr_c5_sys_zr[i_def+4*4]->SetMarkerColor(i_def+1); gr_c5_sys_zr[i_def+4*4]->SetMarkerStyle(28); gr_c5_sys_zr[i_def+4*4]->SetMarkerSize(1.5);
    gr_c6_sys_zr[i_def+4*4] = (TGraphErrors*)f_sys_zr[i_def+4*4]->Get("proton_C_6"); gr_c6_sys_zr[i_def+4*4]->SetMarkerColor(i_def+1); gr_c6_sys_zr[i_def+4*4]->SetMarkerStyle(28); gr_c6_sys_zr[i_def+4*4]->SetMarkerSize(1.5);
    gr_cr21_sys_zr[i_def+4*4] = (TGraphErrors*)f_sys_zr[i_def+4*4]->Get("proton_CR_2_1"); gr_cr21_sys_zr[i_def+4*4]->SetMarkerColor(i_def+1); gr_cr21_sys_zr[i_def+4*4]->SetMarkerStyle(28); gr_cr21_sys_zr[i_def+4*4]->SetMarkerSize(1.5);
    gr_cr31_sys_zr[i_def+4*4] = (TGraphErrors*)f_sys_zr[i_def+4*4]->Get("proton_CR_3_1"); gr_cr31_sys_zr[i_def+4*4]->SetMarkerColor(i_def+1); gr_cr31_sys_zr[i_def+4*4]->SetMarkerStyle(28); gr_cr31_sys_zr[i_def+4*4]->SetMarkerSize(1.5);
    gr_cr32_sys_zr[i_def+4*4] = (TGraphErrors*)f_sys_zr[i_def+4*4]->Get("proton_CR_3_2"); gr_cr32_sys_zr[i_def+4*4]->SetMarkerColor(i_def+1); gr_cr32_sys_zr[i_def+4*4]->SetMarkerStyle(28); gr_cr32_sys_zr[i_def+4*4]->SetMarkerSize(1.5);
    gr_cr42_sys_zr[i_def+4*4] = (TGraphErrors*)f_sys_zr[i_def+4*4]->Get("proton_CR_4_2"); gr_cr42_sys_zr[i_def+4*4]->SetMarkerColor(i_def+1); gr_cr42_sys_zr[i_def+4*4]->SetMarkerStyle(28); gr_cr42_sys_zr[i_def+4*4]->SetMarkerSize(1.5);
    gr_cr51_sys_zr[i_def+4*4] = (TGraphErrors*)f_sys_zr[i_def+4*4]->Get("proton_CR_5_1"); gr_cr51_sys_zr[i_def+4*4]->SetMarkerColor(i_def+1); gr_cr51_sys_zr[i_def+4*4]->SetMarkerStyle(28); gr_cr51_sys_zr[i_def+4*4]->SetMarkerSize(1.5);
    gr_cr62_sys_zr[i_def+4*4] = (TGraphErrors*)f_sys_zr[i_def+4*4]->Get("proton_CR_6_2"); gr_cr62_sys_zr[i_def+4*4]->SetMarkerColor(i_def+1); gr_cr62_sys_zr[i_def+4*4]->SetMarkerStyle(28); gr_cr62_sys_zr[i_def+4*4]->SetMarkerSize(1.5);

    for(int i_cent = 0+mergedN ; i_cent < ncent ; i_cent++){
      gr_c1_sys_ru[i_def+4*4]->SetPointX(i_cent, gr_c1_sys_ru[i_def+4*4]->GetPointX(i_cent) + 10*i_def);
      gr_c2_sys_ru[i_def+4*4]->SetPointX(i_cent, gr_c2_sys_ru[i_def+4*4]->GetPointX(i_cent) + 10*i_def);
      gr_c3_sys_ru[i_def+4*4]->SetPointX(i_cent, gr_c3_sys_ru[i_def+4*4]->GetPointX(i_cent) + 10*i_def);
      gr_c4_sys_ru[i_def+4*4]->SetPointX(i_cent, gr_c4_sys_ru[i_def+4*4]->GetPointX(i_cent) + 10*i_def);
      gr_c5_sys_ru[i_def+4*4]->SetPointX(i_cent, gr_c5_sys_ru[i_def+4*4]->GetPointX(i_cent) + 10*i_def);
      gr_c6_sys_ru[i_def+4*4]->SetPointX(i_cent, gr_c6_sys_ru[i_def+4*4]->GetPointX(i_cent) + 10*i_def);
      gr_cr21_sys_ru[i_def+4*4]->SetPointX(i_cent, gr_cr21_sys_ru[i_def+4*4]->GetPointX(i_cent) + 10*i_def);
      gr_cr31_sys_ru[i_def+4*4]->SetPointX(i_cent, gr_cr31_sys_ru[i_def+4*4]->GetPointX(i_cent) + 10*i_def);
      gr_cr32_sys_ru[i_def+4*4]->SetPointX(i_cent, gr_cr32_sys_ru[i_def+4*4]->GetPointX(i_cent) + 10*i_def);
      gr_cr42_sys_ru[i_def+4*4]->SetPointX(i_cent, gr_cr42_sys_ru[i_def+4*4]->GetPointX(i_cent) + 10*i_def);
      gr_cr51_sys_ru[i_def+4*4]->SetPointX(i_cent, gr_cr51_sys_ru[i_def+4*4]->GetPointX(i_cent) + 10*i_def);
      gr_cr62_sys_ru[i_def+4*4]->SetPointX(i_cent, gr_cr62_sys_ru[i_def+4*4]->GetPointX(i_cent) + 10*i_def);
      gr_c1_sys_zr[i_def+4*4]->SetPointX(i_cent, gr_c1_sys_zr[i_def+4*4]->GetPointX(i_cent) + 10*i_def);
      gr_c2_sys_zr[i_def+4*4]->SetPointX(i_cent, gr_c2_sys_zr[i_def+4*4]->GetPointX(i_cent) + 10*i_def);
      gr_c3_sys_zr[i_def+4*4]->SetPointX(i_cent, gr_c3_sys_zr[i_def+4*4]->GetPointX(i_cent) + 10*i_def);
      gr_c4_sys_zr[i_def+4*4]->SetPointX(i_cent, gr_c4_sys_zr[i_def+4*4]->GetPointX(i_cent) + 10*i_def);
      gr_c5_sys_zr[i_def+4*4]->SetPointX(i_cent, gr_c5_sys_zr[i_def+4*4]->GetPointX(i_cent) + 10*i_def);
      gr_c6_sys_zr[i_def+4*4]->SetPointX(i_cent, gr_c6_sys_zr[i_def+4*4]->GetPointX(i_cent) + 10*i_def);
      gr_cr21_sys_zr[i_def+4*4]->SetPointX(i_cent, gr_cr21_sys_zr[i_def+4*4]->GetPointX(i_cent) + 10*i_def);
      gr_cr31_sys_zr[i_def+4*4]->SetPointX(i_cent, gr_cr31_sys_zr[i_def+4*4]->GetPointX(i_cent) + 10*i_def);
      gr_cr32_sys_zr[i_def+4*4]->SetPointX(i_cent, gr_cr32_sys_zr[i_def+4*4]->GetPointX(i_cent) + 10*i_def);
      gr_cr42_sys_zr[i_def+4*4]->SetPointX(i_cent, gr_cr42_sys_zr[i_def+4*4]->GetPointX(i_cent) + 10*i_def);
      gr_cr51_sys_zr[i_def+4*4]->SetPointX(i_cent, gr_cr51_sys_zr[i_def+4*4]->GetPointX(i_cent) + 10*i_def);
      gr_cr62_sys_zr[i_def+4*4]->SetPointX(i_cent, gr_cr62_sys_zr[i_def+4*4]->GetPointX(i_cent) + 10*i_def);
    }
  }
  TGraphErrors *gr_c1_sysunc_ru = (TGraphErrors*)gr_c1_ru->Clone("gr_c1_sysunc_ru");
  TGraphErrors *gr_c2_sysunc_ru = (TGraphErrors*)gr_c2_ru->Clone("gr_c2_sysunc_ru");
  TGraphErrors *gr_c3_sysunc_ru = (TGraphErrors*)gr_c3_ru->Clone("gr_c3_sysunc_ru");
  TGraphErrors *gr_c4_sysunc_ru = (TGraphErrors*)gr_c4_ru->Clone("gr_c4_sysunc_ru");
  TGraphErrors *gr_c5_sysunc_ru = (TGraphErrors*)gr_c5_ru->Clone("gr_c5_sysunc_ru");
  TGraphErrors *gr_c6_sysunc_ru = (TGraphErrors*)gr_c6_ru->Clone("gr_c6_sysunc_ru");
  TGraphErrors *gr_cr21_sysunc_ru = (TGraphErrors*)gr_cr21_ru->Clone("gr_cr21_sysunc_ru");
  TGraphErrors *gr_cr31_sysunc_ru = (TGraphErrors*)gr_cr31_ru->Clone("gr_cr31_sysunc_ru");
  TGraphErrors *gr_cr32_sysunc_ru = (TGraphErrors*)gr_cr32_ru->Clone("gr_cr32_sysunc_ru");
  TGraphErrors *gr_cr42_sysunc_ru = (TGraphErrors*)gr_cr42_ru->Clone("gr_cr42_sysunc_ru");
  TGraphErrors *gr_cr51_sysunc_ru = (TGraphErrors*)gr_cr51_ru->Clone("gr_cr51_sysunc_ru");
  TGraphErrors *gr_cr62_sysunc_ru = (TGraphErrors*)gr_cr62_ru->Clone("gr_cr62_sysunc_ru");
  TGraphErrors *gr_c1_sysunc_zr = (TGraphErrors*)gr_c1_zr->Clone("gr_c1_sysunc_zr");
  TGraphErrors *gr_c2_sysunc_zr = (TGraphErrors*)gr_c2_zr->Clone("gr_c2_sysunc_zr");
  TGraphErrors *gr_c3_sysunc_zr = (TGraphErrors*)gr_c3_zr->Clone("gr_c3_sysunc_zr");
  TGraphErrors *gr_c4_sysunc_zr = (TGraphErrors*)gr_c4_zr->Clone("gr_c4_sysunc_zr");
  TGraphErrors *gr_c5_sysunc_zr = (TGraphErrors*)gr_c5_zr->Clone("gr_c5_sysunc_zr");
  TGraphErrors *gr_c6_sysunc_zr = (TGraphErrors*)gr_c6_zr->Clone("gr_c6_sysunc_zr");
  TGraphErrors *gr_cr21_sysunc_zr = (TGraphErrors*)gr_cr21_zr->Clone("gr_cr21_sysunc_zr");
  TGraphErrors *gr_cr31_sysunc_zr = (TGraphErrors*)gr_cr31_zr->Clone("gr_cr31_sysunc_zr");
  TGraphErrors *gr_cr32_sysunc_zr = (TGraphErrors*)gr_cr32_zr->Clone("gr_cr32_sysunc_zr");
  TGraphErrors *gr_cr42_sysunc_zr = (TGraphErrors*)gr_cr42_zr->Clone("gr_cr42_sysunc_zr");
  TGraphErrors *gr_cr51_sysunc_zr = (TGraphErrors*)gr_cr51_zr->Clone("gr_cr51_sysunc_zr");
  TGraphErrors *gr_cr62_sysunc_zr = (TGraphErrors*)gr_cr62_zr->Clone("gr_cr62_sysunc_zr");


  
  static TGraphErrors *gr[12*2];
  gr[0] = (TGraphErrors*)gr_c1_sysunc_zr->Clone("gr_c1_sysunc_zr");
  gr[1] = (TGraphErrors*)gr_c2_sysunc_zr->Clone("gr_c2_sysunc_zr");
  gr[2] = (TGraphErrors*)gr_c3_sysunc_zr->Clone("gr_c3_sysunc_zr");
  gr[3] = (TGraphErrors*)gr_c4_sysunc_zr->Clone("gr_c4_sysunc_zr");
  gr[4] = (TGraphErrors*)gr_c5_sysunc_zr->Clone("gr_c5_sysunc_zr");
  gr[5] = (TGraphErrors*)gr_c6_sysunc_zr->Clone("gr_c6_sysunc_zr");
  
  gr[6] = (TGraphErrors*)gr_cr21_sysunc_zr->Clone("gr_cr21_sysunc_zr");
  gr[7] = (TGraphErrors*)gr_cr31_sysunc_zr->Clone("gr_cr31_sysunc_zr");
  gr[8] = (TGraphErrors*)gr_cr32_sysunc_zr->Clone("gr_cr32_sysunc_zr");
  gr[9] = (TGraphErrors*)gr_cr42_sysunc_zr->Clone("gr_cr42_sysunc_zr");
  gr[10] = (TGraphErrors*)gr_cr51_sysunc_zr->Clone("gr_cr51_sysunc_zr");
  gr[11] = (TGraphErrors*)gr_cr62_sysunc_zr->Clone("gr_cr62_sysunc_zr");
  
  gr[0+12] = (TGraphErrors*)gr_c1_sysunc_ru->Clone("gr_c1_sysunc_ru");
  gr[1+12] = (TGraphErrors*)gr_c2_sysunc_ru->Clone("gr_c2_sysunc_ru");
  gr[2+12] = (TGraphErrors*)gr_c3_sysunc_ru->Clone("gr_c3_sysunc_ru");
  gr[3+12] = (TGraphErrors*)gr_c4_sysunc_ru->Clone("gr_c4_sysunc_ru");
  gr[4+12] = (TGraphErrors*)gr_c5_sysunc_ru->Clone("gr_c5_sysunc_ru");
  gr[5+12] = (TGraphErrors*)gr_c6_sysunc_ru->Clone("gr_c6_sysunc_ru");
  
  gr[6+12] = (TGraphErrors*)gr_cr21_sysunc_ru->Clone("gr_cr21_sysunc_ru");
  gr[7+12] = (TGraphErrors*)gr_cr31_sysunc_ru->Clone("gr_cr31_sysunc_ru");
  gr[8+12] = (TGraphErrors*)gr_cr32_sysunc_ru->Clone("gr_cr32_sysunc_ru");
  gr[9+12] = (TGraphErrors*)gr_cr42_sysunc_ru->Clone("gr_cr42_sysunc_ru");
  gr[10+12] = (TGraphErrors*)gr_cr51_sysunc_ru->Clone("gr_cr51_sysunc_ru");
  gr[11+12] = (TGraphErrors*)gr_cr62_sysunc_ru->Clone("gr_cr62_sysunc_ru");

  std::vector<TGraphErrors*> gr_vec;
  for(int i_sys = 0 ; i_sys < 12*2 ; i_sys++) gr_vec.push_back(gr[i_sys]);
  TFile *f_out = new TFile(Form("output/files/sys_%d.root",mergedN), "recreate");
  f_out->cd();
  for(int i_sys = 0 ; i_sys < 20 ; i_sys++) {
    gr_c1_sys_zr[i_sys]->SetName(Form("c1_sys_zr_%d", i_sys)); gr_c1_sys_ru[i_sys]->SetName(Form("c1_sys_ru_%d", i_sys));
    gr_c2_sys_zr[i_sys]->SetName(Form("c2_sys_zr_%d", i_sys)); gr_c2_sys_ru[i_sys]->SetName(Form("c2_sys_ru_%d", i_sys));
    gr_c3_sys_zr[i_sys]->SetName(Form("c3_sys_zr_%d", i_sys)); gr_c3_sys_ru[i_sys]->SetName(Form("c3_sys_ru_%d", i_sys));
    gr_c4_sys_zr[i_sys]->SetName(Form("c4_sys_zr_%d", i_sys)); gr_c4_sys_ru[i_sys]->SetName(Form("c4_sys_ru_%d", i_sys));
    gr_c5_sys_zr[i_sys]->SetName(Form("c5_sys_zr_%d", i_sys)); gr_c5_sys_ru[i_sys]->SetName(Form("c5_sys_ru_%d", i_sys));
    gr_c6_sys_zr[i_sys]->SetName(Form("c6_sys_zr_%d", i_sys)); gr_c6_sys_ru[i_sys]->SetName(Form("c6_sys_ru_%d", i_sys));
    gr_cr21_sys_zr[i_sys]->SetName(Form("cr21_sys_zr_%d", i_sys)); gr_cr21_sys_ru[i_sys]->SetName(Form("cr21_sys_ru_%d", i_sys));
    gr_cr31_sys_zr[i_sys]->SetName(Form("cr31_sys_zr_%d", i_sys)); gr_cr31_sys_ru[i_sys]->SetName(Form("cr31_sys_ru_%d", i_sys));
    gr_cr32_sys_zr[i_sys]->SetName(Form("cr32_sys_zr_%d", i_sys)); gr_cr32_sys_ru[i_sys]->SetName(Form("cr32_sys_ru_%d", i_sys));
    gr_cr42_sys_zr[i_sys]->SetName(Form("cr42_sys_zr_%d", i_sys)); gr_cr42_sys_ru[i_sys]->SetName(Form("cr42_sys_ru_%d", i_sys));
    gr_cr51_sys_zr[i_sys]->SetName(Form("cr51_sys_zr_%d", i_sys)); gr_cr51_sys_ru[i_sys]->SetName(Form("cr51_sys_ru_%d", i_sys));
    gr_cr62_sys_zr[i_sys]->SetName(Form("cr62_sys_zr_%d", i_sys)); gr_cr62_sys_ru[i_sys]->SetName(Form("cr62_sys_ru_%d", i_sys));
    gr_c1_sys_zr[i_sys]->Write(Form("c1_sys_zr_%d", i_sys)); gr_c1_sys_ru[i_sys]->Write(Form("c1_sys_ru_%d", i_sys));
    gr_c2_sys_zr[i_sys]->Write(Form("c2_sys_zr_%d", i_sys)); gr_c2_sys_ru[i_sys]->Write(Form("c2_sys_ru_%d", i_sys));
    gr_c3_sys_zr[i_sys]->Write(Form("c3_sys_zr_%d", i_sys)); gr_c3_sys_ru[i_sys]->Write(Form("c3_sys_ru_%d", i_sys));
    gr_c4_sys_zr[i_sys]->Write(Form("c4_sys_zr_%d", i_sys)); gr_c4_sys_ru[i_sys]->Write(Form("c4_sys_ru_%d", i_sys));
    gr_c5_sys_zr[i_sys]->Write(Form("c5_sys_zr_%d", i_sys)); gr_c5_sys_ru[i_sys]->Write(Form("c5_sys_ru_%d", i_sys));
    gr_c6_sys_zr[i_sys]->Write(Form("c6_sys_zr_%d", i_sys)); gr_c6_sys_ru[i_sys]->Write(Form("c6_sys_ru_%d", i_sys));
    gr_cr21_sys_zr[i_sys]->Write(Form("cr21_sys_zr_%d", i_sys)); gr_cr21_sys_ru[i_sys]->Write(Form("cr21_sys_ru_%d", i_sys));
    gr_cr31_sys_zr[i_sys]->Write(Form("cr31_sys_zr_%d", i_sys)); gr_cr31_sys_ru[i_sys]->Write(Form("cr31_sys_ru_%d", i_sys));
    gr_cr32_sys_zr[i_sys]->Write(Form("cr32_sys_zr_%d", i_sys)); gr_cr32_sys_ru[i_sys]->Write(Form("cr32_sys_ru_%d", i_sys));
    gr_cr42_sys_zr[i_sys]->Write(Form("cr42_sys_zr_%d", i_sys)); gr_cr42_sys_ru[i_sys]->Write(Form("cr42_sys_ru_%d", i_sys));
    gr_cr51_sys_zr[i_sys]->Write(Form("cr51_sys_zr_%d", i_sys)); gr_cr51_sys_ru[i_sys]->Write(Form("cr51_sys_ru_%d", i_sys));
    gr_cr62_sys_zr[i_sys]->Write(Form("cr62_sys_zr_%d", i_sys)); gr_cr62_sys_ru[i_sys]->Write(Form("cr62_sys_ru_%d", i_sys));
  }
  f_out->Write();
  f_out->Close();
  delete f_out;
  return gr_vec;

}



void sys_cum(){
  double Npart_ru[ncent], Npart_zr[ncent];
  double Npart_ref3_auau[ncent];

  
  Npart_ru[0] = 167.383;
  Npart_ru[1] = 145.648;
  Npart_ru[2] = 115.744;
  Npart_ru[3] = 84.1156;
  Npart_ru[4] = 59.6432;
  Npart_ru[5] = 40.7537;
  Npart_ru[6] = 26.6392;
  Npart_ru[7] = 16.7077;
  Npart_ru[8] = 9.95946;
  Npart_zr[0] = 166.511;
  Npart_zr[1] = 144.621;
  Npart_zr[2] = 114.421;
  Npart_zr[3] = 82.334;
  Npart_zr[4] = 57.6936;
  Npart_zr[5] = 39.1169;
  Npart_zr[6] = 25.3659;
  Npart_zr[7] = 15.6751;
  Npart_zr[8] = 9.29664;

  if(mergedN == 1){//0-10%
    Npart_ru[0] = -999;
    Npart_ru[1] = 156.208;
    Npart_zr[0] = -999;
    Npart_zr[1] = 155.326;
  }
  if(mergedN == 2){//0-20%
    Npart_ru[0] = -999;
    Npart_ru[1] = -999;
    Npart_ru[2] = 135.873;
    Npart_zr[0] = -999;
    Npart_zr[1] = -999;
    Npart_zr[2] = 134.859;
  }
  if(mergedN == 3){//0-30%
    Npart_ru[0] = -999;
    Npart_ru[1] = -999;
    Npart_ru[2] = -999;
    Npart_ru[3] = 118.656;
    Npart_zr[0] = -999;
    Npart_zr[1] = -999;
    Npart_zr[2] = -999;
    Npart_zr[3] = 117.343;
  }
  if(mergedN == 4){//0-40%
    Npart_ru[0] = -999;
    Npart_ru[1] = -999;
    Npart_ru[2] = -999;
    Npart_ru[3] = -999;
    Npart_ru[4] = 103.698;
    Npart_zr[0] = -999;
    Npart_zr[1] = -999;
    Npart_zr[2] = -999;
    Npart_zr[3] = -999;
    Npart_zr[4] = 102.341;
  }

  Npart_ref3_auau[0] = 351;
  Npart_ref3_auau[1] = 299.0;
  Npart_ref3_auau[2] = 234.0;
  Npart_ref3_auau[3] = 168.0;
  Npart_ref3_auau[4] = 117.0;
  Npart_ref3_auau[5] = 78.0;
  Npart_ref3_auau[6] = 49.0;
  Npart_ref3_auau[7] = 29.0;
  Npart_ref3_auau[8] = 16.0;

  double c1_ref3_auau[9], c2_ref3_auau[9], c3_ref3_auau[9], c4_ref3_auau[9];//cum
  double c1_ref3_auau_sta[9], c2_ref3_auau_sta[9], c3_ref3_auau_sta[9], c4_ref3_auau_sta[9];//cum stat. unc.
  double c1_ref3_auau_sys[9], c2_ref3_auau_sys[9], c3_ref3_auau_sys[9], c4_ref3_auau_sys[9];//cum sys. unc.
  double cr21_ref3_auau[9], cr32_ref3_auau[9], cr42_ref3_auau[9];//cum ratio
  double cr21_ref3_auau_sta[9], cr32_ref3_auau_sta[9], cr42_ref3_auau_sta[9];//cum ratio stat. unc.
  double cr21_ref3_auau_sys[9], cr32_ref3_auau_sys[9], cr42_ref3_auau_sys[9];//cum ratio sys. unc.
  c1_ref3_auau[0] = 4.5662; c1_ref3_auau_sta[0] = 0.0022804; c1_ref3_auau_sys[0] = 0.38998;
  c1_ref3_auau[1] = 3.9192; c1_ref3_auau_sta[1] = 0.0017691; c1_ref3_auau_sys[1] = 0.31148;
  c1_ref3_auau[2] = 2.9838; c1_ref3_auau_sta[2] = 0.001061; c1_ref3_auau_sys[2] = 0.21968;
  c1_ref3_auau[3] = 1.9922; c1_ref3_auau_sta[3] = 0.00085263; c1_ref3_auau_sys[3] = 0.13624;
  c1_ref3_auau[4] = 1.2684; c1_ref3_auau_sta[4] = 0.00068125; c1_ref3_auau_sys[4] = 0.083097;
  c1_ref3_auau[5] = 0.76427; c1_ref3_auau_sta[5] = 0.00053579; c1_ref3_auau_sys[5] = 0.049767;
  c1_ref3_auau[6] = 0.42691; c1_ref3_auau_sta[6] = 0.00040705; c1_ref3_auau_sys[6] = 0.02865;
  c1_ref3_auau[7] = 0.2207; c1_ref3_auau_sta[7] = 0.00031292; c1_ref3_auau_sys[7] = 0.015637;
  c1_ref3_auau[8] = 0.10961; c1_ref3_auau_sta[8] = 0.00026165; c1_ref3_auau_sys[8] = 0.0083462;

  c2_ref3_auau[0] = 30.192; c2_ref3_auau_sta[0] = 0.026632; c2_ref3_auau_sys[0] = 2.4232;
  c2_ref3_auau[1] = 25.92; c2_ref3_auau_sta[1] = 0.018592; c2_ref3_auau_sys[1] = 1.9179;
  c2_ref3_auau[2] = 19.879; c2_ref3_auau_sta[2] = 0.0094641; c2_ref3_auau_sys[2] = 1.3419;
  c2_ref3_auau[3] = 13.562; c2_ref3_auau_sta[3] = 0.0060436; c2_ref3_auau_sys[3] = 0.84942;
  c2_ref3_auau[4] = 8.9083; c2_ref3_auau_sta[4] = 0.003809; c2_ref3_auau_sys[4] = 0.53884;
  c2_ref3_auau[5] = 5.5793; c2_ref3_auau_sta[5] = 0.0023348; c2_ref3_auau_sys[5] = 0.33441;
  c2_ref3_auau[6] = 3.2442; c2_ref3_auau_sta[6] = 0.0013524; c2_ref3_auau_sys[6] = 0.19424;
  c2_ref3_auau[7] = 1.7383; c2_ref3_auau_sta[7] = 0.00077629; c2_ref3_auau_sys[7] = 0.1045;
  c2_ref3_auau[8] = 0.87301; c2_ref3_auau_sta[8] = 0.0004857; c2_ref3_auau_sys[8] = 0.053022;

  c3_ref3_auau[0] = 3.6926; c3_ref3_auau_sta[0] = 0.38235; c3_ref3_auau_sys[0] = 0.39034;
  c3_ref3_auau[1] = 3.3892; c3_ref3_auau_sta[1] = 0.24108; c3_ref3_auau_sys[1] = 0.39914;
  c3_ref3_auau[2] = 2.4272; c3_ref3_auau_sta[2] = 0.10463; c3_ref3_auau_sys[2] = 0.22016;
  c3_ref3_auau[3] = 1.7145; c3_ref3_auau_sta[3] = 0.053311; c3_ref3_auau_sys[3] = 0.13396;
  c3_ref3_auau[4] = 1.0537; c3_ref3_auau_sta[4] = 0.026592; c3_ref3_auau_sys[4] = 0.057335;
  c3_ref3_auau[5] = 0.62048; c3_ref3_auau_sta[5] = 0.012796; c3_ref3_auau_sys[5] = 0.032255;
  c3_ref3_auau[6] = 0.33491; c3_ref3_auau_sta[6] = 0.0057194; c3_ref3_auau_sys[6] = 0.017207;
  c3_ref3_auau[7] = 0.1818; c3_ref3_auau_sta[7] = 0.0024965; c3_ref3_auau_sys[7] = 0.010978;
  c3_ref3_auau[8] = 0.089961; c3_ref3_auau_sta[8] = 0.0011864; c3_ref3_auau_sys[8] = 0.0059958;

  c4_ref3_auau[0] = 27.193; c4_ref3_auau_sta[0] = 6.3467; c4_ref3_auau_sys[0] = 4.8917;
  c4_ref3_auau[1] = 27.993; c4_ref3_auau_sta[1] = 3.6318; c4_ref3_auau_sys[1] = 3.3801;
  c4_ref3_auau[2] = 12.828; c4_ref3_auau_sta[2] = 1.3502; c4_ref3_auau_sys[2] = 1.7153;
  c4_ref3_auau[3] = 10.187; c4_ref3_auau_sta[3] = 0.55301; c4_ref3_auau_sys[3] = 0.58254;
  c4_ref3_auau[4] = 6.3352; c4_ref3_auau_sta[4] = 0.21753; c4_ref3_auau_sys[4] = 0.26416;
  c4_ref3_auau[5] = 3.9955; c4_ref3_auau_sta[5] = 0.083183; c4_ref3_auau_sys[5] = 0.14777;
  c4_ref3_auau[6] = 2.3981; c4_ref3_auau_sta[6] = 0.028913; c4_ref3_auau_sys[6] = 0.10197;
  c4_ref3_auau[7] = 1.312; c4_ref3_auau_sta[7] = 0.0097892; c4_ref3_auau_sys[7] = 0.058195;
  c4_ref3_auau[8] = 0.68511; c4_ref3_auau_sta[8] = 0.0036791; c4_ref3_auau_sys[8] = 0.03324;

  cr21_ref3_auau[0] = 6.6121; cr21_ref3_auau_sta[0] = 0.0066653; cr21_ref3_auau_sys[0] = 0.089992;
  cr21_ref3_auau[1] = 6.6137; cr21_ref3_auau_sta[1] = 0.0055669; cr21_ref3_auau_sys[1] = 0.086097;
  cr21_ref3_auau[2] = 6.6622; cr21_ref3_auau_sta[2] = 0.0039144; cr21_ref3_auau_sys[2] = 0.11388;
  cr21_ref3_auau[3] = 6.8074; cr21_ref3_auau_sta[3] = 0.0041667; cr21_ref3_auau_sys[3] = 0.12908;
  cr21_ref3_auau[4] = 7.023; cr21_ref3_auau_sta[4] = 0.0047925; cr21_ref3_auau_sys[4] = 0.11498;
  cr21_ref3_auau[5] = 7.3002; cr21_ref3_auau_sta[5] = 0.0059539; cr21_ref3_auau_sys[5] = 0.087384;
  cr21_ref3_auau[6] = 7.5993; cr21_ref3_auau_sta[6] = 0.007954; cr21_ref3_auau_sys[6] = 0.072038;
  cr21_ref3_auau[7] = 7.8761; cr21_ref3_auau_sta[7] = 0.011814; cr21_ref3_auau_sys[7] = 0.098462;
  cr21_ref3_auau[8] = 7.965; cr21_ref3_auau_sta[8] = 0.019585; cr21_ref3_auau_sys[8] = 0.15617;

  cr32_ref3_auau[0] = 0.1223; cr32_ref3_auau_sta[0] = 0.012597; cr32_ref3_auau_sys[0] = 0.010899;
  cr32_ref3_auau[1] = 0.13076; cr32_ref3_auau_sta[1] = 0.009238; cr32_ref3_auau_sys[1] = 0.01605;
  cr32_ref3_auau[2] = 0.1221; cr32_ref3_auau_sta[2] = 0.0051337; cr32_ref3_auau_sys[2] = 0.01281;
  cr32_ref3_auau[3] = 0.12642; cr32_ref3_auau_sta[3] = 0.0038281; cr32_ref3_auau_sys[3] = 0.010484;
  cr32_ref3_auau[4] = 0.11828; cr32_ref3_auau_sta[4] = 0.0028999; cr32_ref3_auau_sys[4] = 0.0045273;
  cr32_ref3_auau[5] = 0.11121; cr32_ref3_auau_sta[5] = 0.0022155; cr32_ref3_auau_sys[5] = 0.0024926;
  cr32_ref3_auau[6] = 0.10323; cr32_ref3_auau_sta[6] = 0.0016908; cr32_ref3_auau_sys[6] = 0.0018131;
  cr32_ref3_auau[7] = 0.10458; cr32_ref3_auau_sta[7] = 0.0013689; cr32_ref3_auau_sys[7] = 0.0011027;
  cr32_ref3_auau[8] = 0.10305; cr32_ref3_auau_sta[8] = 0.0013015; cr32_ref3_auau_sys[8] = 0.0020362;

  cr42_ref3_auau[0] = 0.90067; cr42_ref3_auau_sta[0] = 0.20846; cr42_ref3_auau_sys[0] = 0.13936;
  cr42_ref3_auau[1] = 1.08; cr42_ref3_auau_sta[1] = 0.1387; cr42_ref3_auau_sys[1] = 0.095264;
  cr42_ref3_auau[2] = 0.64534; cr42_ref3_auau_sta[2] = 0.06544; cr42_ref3_auau_sys[2] = 0.10845;
  cr42_ref3_auau[3] = 0.75119; cr42_ref3_auau_sta[3] = 0.039159; cr42_ref3_auau_sys[3] = 0.055729;
  cr42_ref3_auau[4] = 0.71116; cr42_ref3_auau_sta[4] = 0.023371; cr42_ref3_auau_sys[4] = 0.037974;
  cr42_ref3_auau[5] = 0.71613; cr42_ref3_auau_sta[5] = 0.014106; cr42_ref3_auau_sys[5] = 0.025189;
  cr42_ref3_auau[6] = 0.7392; cr42_ref3_auau_sta[6] = 0.0083332; cr42_ref3_auau_sys[6] = 0.01551;
  cr42_ref3_auau[7] = 0.75479; cr42_ref3_auau_sta[7] = 0.0051847; cr42_ref3_auau_sys[7] = 0.013222;
  cr42_ref3_auau[8] = 0.78476; cr42_ref3_auau_sta[8] = 0.0038362; cr42_ref3_auau_sys[8] = 0.011062;

  TGraphErrors *gr_proton_c1_ref3_auau_sta_cent = new TGraphErrors(ncent, Npart_ref3_auau, c1_ref3_auau, 0, c1_ref3_auau_sta);
  TGraphErrors *gr_proton_c2_ref3_auau_sta_cent = new TGraphErrors(ncent, Npart_ref3_auau, c2_ref3_auau, 0, c2_ref3_auau_sta);
  TGraphErrors *gr_proton_c3_ref3_auau_sta_cent = new TGraphErrors(ncent, Npart_ref3_auau, c3_ref3_auau, 0, c3_ref3_auau_sta);
  TGraphErrors *gr_proton_c4_ref3_auau_sta_cent = new TGraphErrors(ncent, Npart_ref3_auau, c4_ref3_auau, 0, c4_ref3_auau_sta);
  TGraphErrors *gr_proton_c1_ref3_auau_sys_cent = new TGraphErrors(ncent, Npart_ref3_auau, c1_ref3_auau, 0, c1_ref3_auau_sys);
  TGraphErrors *gr_proton_c2_ref3_auau_sys_cent = new TGraphErrors(ncent, Npart_ref3_auau, c2_ref3_auau, 0, c2_ref3_auau_sys);
  TGraphErrors *gr_proton_c3_ref3_auau_sys_cent = new TGraphErrors(ncent, Npart_ref3_auau, c3_ref3_auau, 0, c3_ref3_auau_sys);
  TGraphErrors *gr_proton_c4_ref3_auau_sys_cent = new TGraphErrors(ncent, Npart_ref3_auau, c4_ref3_auau, 0, c4_ref3_auau_sys);

  TGraphErrors *gr_proton_cr21_ref3_auau_sta_cent = new TGraphErrors(ncent, Npart_ref3_auau, cr21_ref3_auau, 0, cr21_ref3_auau_sta);
  TGraphErrors *gr_proton_cr32_ref3_auau_sta_cent = new TGraphErrors(ncent, Npart_ref3_auau, cr32_ref3_auau, 0, cr32_ref3_auau_sta);
  TGraphErrors *gr_proton_cr42_ref3_auau_sta_cent = new TGraphErrors(ncent, Npart_ref3_auau, cr42_ref3_auau, 0, cr42_ref3_auau_sta);
  TGraphErrors *gr_proton_cr21_ref3_auau_sys_cent = new TGraphErrors(ncent, Npart_ref3_auau, cr21_ref3_auau, 0, cr21_ref3_auau_sys);
  TGraphErrors *gr_proton_cr32_ref3_auau_sys_cent = new TGraphErrors(ncent, Npart_ref3_auau, cr32_ref3_auau, 0, cr32_ref3_auau_sys);
  TGraphErrors *gr_proton_cr42_ref3_auau_sys_cent = new TGraphErrors(ncent, Npart_ref3_auau, cr42_ref3_auau, 0, cr42_ref3_auau_sys);

  gr_proton_c1_ref3_auau_sta_cent->SetMarkerSize(1.5);
  gr_proton_c1_ref3_auau_sta_cent->SetMarkerStyle(26);
  gr_proton_c1_ref3_auau_sta_cent->SetMarkerColor(2);
  gr_proton_c1_ref3_auau_sta_cent->SetLineColor(2);
  gr_proton_c2_ref3_auau_sta_cent->SetMarkerSize(1.5);
  gr_proton_c2_ref3_auau_sta_cent->SetMarkerStyle(26);
  gr_proton_c2_ref3_auau_sta_cent->SetMarkerColor(2);
  gr_proton_c2_ref3_auau_sta_cent->SetLineColor(2);
  gr_proton_c3_ref3_auau_sta_cent->SetMarkerSize(1.5);
  gr_proton_c3_ref3_auau_sta_cent->SetMarkerStyle(26);
  gr_proton_c3_ref3_auau_sta_cent->SetMarkerColor(2);
  gr_proton_c3_ref3_auau_sta_cent->SetLineColor(2);
  gr_proton_c4_ref3_auau_sta_cent->SetMarkerSize(1.5);
  gr_proton_c4_ref3_auau_sta_cent->SetMarkerStyle(26);
  gr_proton_c4_ref3_auau_sta_cent->SetMarkerColor(2);
  gr_proton_c4_ref3_auau_sta_cent->SetLineColor(2);
  gr_proton_c1_ref3_auau_sys_cent->SetMarkerSize(1.5);
  gr_proton_c1_ref3_auau_sys_cent->SetMarkerStyle(26);
  gr_proton_c1_ref3_auau_sys_cent->SetMarkerColor(2);
  gr_proton_c1_ref3_auau_sys_cent->SetLineColor(2);
  gr_proton_c1_ref3_auau_sys_cent->SetFillColorAlpha(kRed, 0.5);
  gr_proton_c1_ref3_auau_sys_cent->SetFillStyle(3001);
  gr_proton_c2_ref3_auau_sys_cent->SetMarkerSize(1.5);
  gr_proton_c2_ref3_auau_sys_cent->SetMarkerStyle(26);
  gr_proton_c2_ref3_auau_sys_cent->SetMarkerColor(2);
  gr_proton_c2_ref3_auau_sys_cent->SetLineColor(2);
  gr_proton_c2_ref3_auau_sys_cent->SetFillColorAlpha(kRed, 0.5);
  gr_proton_c2_ref3_auau_sys_cent->SetFillStyle(3001);
  gr_proton_c3_ref3_auau_sys_cent->SetMarkerSize(1.5);
  gr_proton_c3_ref3_auau_sys_cent->SetMarkerStyle(26);
  gr_proton_c3_ref3_auau_sys_cent->SetMarkerColor(2);
  gr_proton_c3_ref3_auau_sys_cent->SetLineColor(2);
  gr_proton_c3_ref3_auau_sys_cent->SetFillColorAlpha(kRed, 0.5);
  gr_proton_c3_ref3_auau_sys_cent->SetFillStyle(3001);
  gr_proton_c4_ref3_auau_sys_cent->SetMarkerSize(1.5);
  gr_proton_c4_ref3_auau_sys_cent->SetMarkerStyle(26);
  gr_proton_c4_ref3_auau_sys_cent->SetMarkerColor(2);
  gr_proton_c4_ref3_auau_sys_cent->SetLineColor(2);
  gr_proton_c4_ref3_auau_sys_cent->SetFillColorAlpha(kRed, 0.5);
  gr_proton_c4_ref3_auau_sys_cent->SetFillStyle(3001);


  gr_proton_cr21_ref3_auau_sta_cent->SetMarkerSize(1.5);
  gr_proton_cr21_ref3_auau_sta_cent->SetMarkerStyle(26);
  gr_proton_cr21_ref3_auau_sta_cent->SetMarkerColor(2);
  gr_proton_cr21_ref3_auau_sta_cent->SetLineColor(2);
  gr_proton_cr32_ref3_auau_sta_cent->SetMarkerSize(1.5);
  gr_proton_cr32_ref3_auau_sta_cent->SetMarkerStyle(26);
  gr_proton_cr32_ref3_auau_sta_cent->SetMarkerColor(2);
  gr_proton_cr32_ref3_auau_sta_cent->SetLineColor(2);
  gr_proton_cr42_ref3_auau_sta_cent->SetMarkerSize(1.5);
  gr_proton_cr42_ref3_auau_sta_cent->SetMarkerStyle(26);
  gr_proton_cr42_ref3_auau_sta_cent->SetMarkerColor(2);
  gr_proton_cr42_ref3_auau_sta_cent->SetLineColor(2);
  gr_proton_cr21_ref3_auau_sys_cent->SetMarkerSize(1.5);
  gr_proton_cr21_ref3_auau_sys_cent->SetMarkerStyle(26);
  gr_proton_cr21_ref3_auau_sys_cent->SetMarkerColor(2);
  gr_proton_cr21_ref3_auau_sys_cent->SetLineColor(2);
  gr_proton_cr21_ref3_auau_sys_cent->SetFillColorAlpha(kRed, 0.5);
  gr_proton_cr21_ref3_auau_sys_cent->SetFillStyle(3001);
  gr_proton_cr32_ref3_auau_sys_cent->SetMarkerSize(1.5);
  gr_proton_cr32_ref3_auau_sys_cent->SetMarkerStyle(26);
  gr_proton_cr32_ref3_auau_sys_cent->SetMarkerColor(2);
  gr_proton_cr32_ref3_auau_sys_cent->SetLineColor(2);
  gr_proton_cr32_ref3_auau_sys_cent->SetFillColorAlpha(kRed, 0.5);
  gr_proton_cr32_ref3_auau_sys_cent->SetFillStyle(3001);
  gr_proton_cr42_ref3_auau_sys_cent->SetMarkerSize(1.5);
  gr_proton_cr42_ref3_auau_sys_cent->SetMarkerStyle(26);
  gr_proton_cr42_ref3_auau_sys_cent->SetMarkerColor(2);
  gr_proton_cr42_ref3_auau_sys_cent->SetLineColor(2);
  gr_proton_cr42_ref3_auau_sys_cent->SetFillColorAlpha(kRed, 0.5);
  gr_proton_cr42_ref3_auau_sys_cent->SetFillStyle(3001);

  TFile *_filezr = TFile::Open(Form("../calcum/output/Zr_cbwc_dca_10_nhf_20_nsp_20_m2low_60_m2up_120_ptmx_20_ymax_5_detlow_100_deghi_100_%d.root",mergedN), "read");
  TFile *_fileru = TFile::Open(Form("../calcum/output/Ru_cbwc_dca_10_nhf_20_nsp_20_m2low_60_m2up_120_ptmx_20_ymax_5_detlow_100_deghi_100_%d.root",mergedN), "read");
  TFile *_filezr_zoom = TFile::Open(Form("../calcum/output/Zr_cbwc_dca_10_nhf_20_nsp_20_m2low_60_m2up_120_ptmx_20_ymax_5_detlow_100_deghi_100_%d.root",mergedNzoom), "read");
  TFile *_fileru_zoom = TFile::Open(Form("../calcum/output/Ru_cbwc_dca_10_nhf_20_nsp_20_m2low_60_m2up_120_ptmx_20_ymax_5_detlow_100_deghi_100_%d.root",mergedNzoom), "read");

  gr_c1_zr = (TGraphErrors*)_filezr->Get("proton_C_1"); gr_c1_zr->SetMarkerStyle(4); gr_c1_zr->SetMarkerSize(1.5);
  gr_c2_zr = (TGraphErrors*)_filezr->Get("proton_C_2"); gr_c2_zr->SetMarkerStyle(4); gr_c2_zr->SetMarkerSize(1.5);
  gr_c3_zr = (TGraphErrors*)_filezr->Get("proton_C_3"); gr_c3_zr->SetMarkerStyle(4); gr_c3_zr->SetMarkerSize(1.5);
  gr_c4_zr = (TGraphErrors*)_filezr->Get("proton_C_4"); gr_c4_zr->SetMarkerStyle(4); gr_c4_zr->SetMarkerSize(1.5);
  gr_c5_zr = (TGraphErrors*)_filezr->Get("proton_C_5"); gr_c5_zr->SetMarkerStyle(4); gr_c5_zr->SetMarkerSize(1.5);
  gr_c6_zr = (TGraphErrors*)_filezr->Get("proton_C_6"); gr_c6_zr->SetMarkerStyle(4); gr_c6_zr->SetMarkerSize(1.5);
  gr_c5_zr_zoom = (TGraphErrors*)_filezr_zoom->Get("proton_C_5"); gr_c5_zr_zoom->SetMarkerStyle(4); gr_c5_zr_zoom->SetMarkerSize(1.5);
  gr_c6_zr_zoom = (TGraphErrors*)_filezr_zoom->Get("proton_C_6"); gr_c6_zr_zoom->SetMarkerStyle(4); gr_c6_zr_zoom->SetMarkerSize(1.5);
  gr_cr21_zr = (TGraphErrors*)_filezr->Get("proton_CR_2_1"); gr_cr21_zr->SetMarkerStyle(4); gr_cr21_zr->SetMarkerSize(1.5); /* gr_cr21_zr->GetXaxis()->SetRangeUser(-20, 520); */ gr_cr21_zr->GetYaxis()->SetRangeUser(6.61, 8.9);
  gr_cr31_zr = (TGraphErrors*)_filezr->Get("proton_CR_3_1"); gr_cr31_zr->SetMarkerStyle(4); gr_cr31_zr->SetMarkerSize(1.5); /* gr_cr31_zr->GetXaxis()->SetRangeUser(-20, 520); */
  gr_cr32_zr = (TGraphErrors*)_filezr->Get("proton_CR_3_2"); gr_cr32_zr->SetMarkerStyle(4); gr_cr32_zr->SetMarkerSize(1.5); gr_cr32_zr->GetXaxis()->SetRangeUser(-20, 520); gr_cr32_zr->GetYaxis()->SetRangeUser(0.091, 0.116);
  gr_cr42_zr = (TGraphErrors*)_filezr->Get("proton_CR_4_2"); gr_cr42_zr->SetMarkerStyle(4); gr_cr42_zr->SetMarkerSize(1.5); /* gr_cr42_zr->GetXaxis()->SetRangeUser(-20, 520); */
  gr_cr51_zr = (TGraphErrors*)_filezr->Get("proton_CR_5_1"); gr_cr51_zr->SetMarkerStyle(4); gr_cr51_zr->SetMarkerSize(1.5); gr_cr51_zr->GetXaxis()->SetRangeUser(-20, 520); gr_cr51_zr->GetYaxis()->SetRangeUser(-1.1, 2.4);
  gr_cr62_zr = (TGraphErrors*)_filezr->Get("proton_CR_6_2"); gr_cr62_zr->SetMarkerStyle(4); gr_cr62_zr->SetMarkerSize(1.5); /* gr_cr62_zr->GetXaxis()->SetRangeUser(-20, 520); */
  gr_c1_ru = (TGraphErrors*)_fileru->Get("proton_C_1"); gr_c1_ru->SetMarkerStyle(8); gr_c1_ru->SetMarkerSize(1.5);
  gr_c2_ru = (TGraphErrors*)_fileru->Get("proton_C_2"); gr_c2_ru->SetMarkerStyle(8); gr_c2_ru->SetMarkerSize(1.5);
  gr_c3_ru = (TGraphErrors*)_fileru->Get("proton_C_3"); gr_c3_ru->SetMarkerStyle(8); gr_c3_ru->SetMarkerSize(1.5);
  gr_c4_ru = (TGraphErrors*)_fileru->Get("proton_C_4"); gr_c4_ru->SetMarkerStyle(8); gr_c4_ru->SetMarkerSize(1.5);
  gr_c5_ru = (TGraphErrors*)_fileru->Get("proton_C_5"); gr_c5_ru->SetMarkerStyle(8); gr_c5_ru->SetMarkerSize(1.5);
  gr_c6_ru = (TGraphErrors*)_fileru->Get("proton_C_6"); gr_c6_ru->SetMarkerStyle(8); gr_c6_ru->SetMarkerSize(1.5);
  gr_c5_ru_zoom = (TGraphErrors*)_fileru_zoom->Get("proton_C_5"); gr_c5_ru_zoom->SetMarkerStyle(8); gr_c5_ru_zoom->SetMarkerSize(1.5);
  gr_c6_ru_zoom = (TGraphErrors*)_fileru_zoom->Get("proton_C_6"); gr_c6_ru_zoom->SetMarkerStyle(8); gr_c6_ru_zoom->SetMarkerSize(1.5);
  gr_cr21_ru = (TGraphErrors*)_fileru->Get("proton_CR_2_1"); gr_cr21_ru->SetMarkerStyle(8); gr_cr21_ru->SetMarkerSize(1.5);
  gr_cr31_ru = (TGraphErrors*)_fileru->Get("proton_CR_3_1"); gr_cr31_ru->SetMarkerStyle(8); gr_cr31_ru->SetMarkerSize(1.5);
  gr_cr32_ru = (TGraphErrors*)_fileru->Get("proton_CR_3_2"); gr_cr32_ru->SetMarkerStyle(8); gr_cr32_ru->SetMarkerSize(1.5);
  gr_cr42_ru = (TGraphErrors*)_fileru->Get("proton_CR_4_2"); gr_cr42_ru->SetMarkerStyle(8); gr_cr42_ru->SetMarkerSize(1.5);
  gr_cr51_ru = (TGraphErrors*)_fileru->Get("proton_CR_5_1"); gr_cr51_ru->SetMarkerStyle(8); gr_cr51_ru->SetMarkerSize(1.5);
  gr_cr62_ru = (TGraphErrors*)_fileru->Get("proton_CR_6_2"); gr_cr62_ru->SetMarkerStyle(8); gr_cr62_ru->SetMarkerSize(1.5);

  double x_dummy[1] = {0};
  double y_dummy[1] = {0};

  TGraph *gr_c1_dummy = new TGraph(1, x_dummy, y_dummy); gr_c1_dummy->SetTitle(""); gr_c1_dummy->GetXaxis()->SetTitle(""); gr_c1_dummy->GetXaxis()->SetLimits(-20, 720); gr_c1_dummy->GetYaxis()->SetRangeUser(-0.2, 3.9);
  TGraph *gr_c2_dummy = new TGraph(1, x_dummy, y_dummy); gr_c2_dummy->SetTitle(""); gr_c2_dummy->GetXaxis()->SetTitle(""); gr_c2_dummy->GetXaxis()->SetLimits(-20, 720); gr_c2_dummy->GetYaxis()->SetRangeUser(-1, 22);
  TGraph *gr_c3_dummy = new TGraph(1, x_dummy, y_dummy); gr_c3_dummy->SetTitle(""); gr_c3_dummy->GetXaxis()->SetTitle(""); gr_c3_dummy->GetXaxis()->SetLimits(-20, 720); gr_c3_dummy->GetYaxis()->SetRangeUser(-0.2, 3.4);
  TGraph *gr_c4_dummy = new TGraph(1, x_dummy, y_dummy); gr_c4_dummy->SetTitle(""); gr_c4_dummy->GetXaxis()->SetTitle(""); gr_c4_dummy->GetXaxis()->SetLimits(-20, 720); gr_c4_dummy->GetYaxis()->SetRangeUser(-1, 19);
  TGraph *gr_c5_dummy = new TGraph(1, x_dummy, y_dummy); gr_c5_dummy->SetTitle(""); gr_c5_dummy->GetXaxis()->SetTitle(""); gr_c5_dummy->GetXaxis()->SetLimits(-20, 720); gr_c5_dummy->GetYaxis()->SetRangeUser(-149, 90);
  TGraph *gr_c6_dummy = new TGraph(1, x_dummy, y_dummy); gr_c6_dummy->SetTitle(""); gr_c6_dummy->GetXaxis()->SetTitle(""); gr_c6_dummy->GetXaxis()->SetLimits(-20, 720); gr_c6_dummy->GetYaxis()->SetRangeUser(-1449, 650);

  TGraph *gr_c5_dummy_zoom = new TGraph(1, x_dummy, y_dummy); gr_c5_dummy_zoom->SetTitle(""); gr_c5_dummy_zoom->GetXaxis()->SetTitle(""); gr_c5_dummy_zoom->GetXaxis()->SetLimits(15, 600); gr_c5_dummy_zoom->GetYaxis()->SetRangeUser(-0.5, 1.4);
  gr_c5_dummy_zoom->GetYaxis()->SetLabelSize(0.18);
  gr_c5_dummy_zoom->GetYaxis()->SetLabelOffset(0.02);
  gr_c5_dummy_zoom->GetYaxis()->SetNdivisions(502);
  gr_c5_dummy_zoom->GetXaxis()->SetTitleOffset(0.7);
  gr_c5_dummy_zoom->GetXaxis()->SetTitleSize(0.1);
  gr_c5_dummy_zoom->GetXaxis()->SetLabelSize(0.18);
  gr_c5_dummy_zoom->GetXaxis()->SetLabelOffset(0.025);
  gr_c5_dummy_zoom->GetXaxis()->SetNoExponent(kTRUE);

  gr_c5_dummy_zoom->GetXaxis()->SetMoreLogLabels(kTRUE);
  gr_c5_dummy_zoom->GetXaxis()->ChangeLabel(1, -1, 0.);
  gr_c5_dummy_zoom->GetXaxis()->SetTickLength(0.07); 
  
  TGraph *gr_c6_dummy_zoom = new TGraph(1, x_dummy, y_dummy); gr_c6_dummy_zoom->SetTitle(""); gr_c6_dummy_zoom->GetXaxis()->SetTitle(""); gr_c6_dummy_zoom->GetXaxis()->SetLimits(15, 600); gr_c6_dummy_zoom->GetYaxis()->SetRangeUser(-9.9, 21);
  gr_c6_dummy_zoom->GetYaxis()->SetLabelSize(0.16);
  gr_c6_dummy_zoom->GetYaxis()->SetLabelOffset(0.02);
  gr_c6_dummy_zoom->GetYaxis()->SetNdivisions(503);
  gr_c6_dummy_zoom->GetXaxis()->SetTitleOffset(0.7);
  gr_c6_dummy_zoom->GetXaxis()->SetTitleSize(0.1);
  gr_c6_dummy_zoom->GetXaxis()->SetLabelSize(0.16);
  gr_c6_dummy_zoom->GetXaxis()->SetLabelOffset(0.025);
  gr_c6_dummy_zoom->GetXaxis()->SetNoExponent(kTRUE);
  gr_c6_dummy_zoom->GetXaxis()->SetNdivisions(502);
  
  gr_c6_dummy_zoom->GetXaxis()->SetMoreLogLabels(kTRUE);
  gr_c6_dummy_zoom->GetXaxis()->ChangeLabel(1, -1, 0.);
  gr_c6_dummy_zoom->GetXaxis()->SetTickLength(0.06); 

  TGraph *gr_cr21_dummy = new TGraph(1, x_dummy, y_dummy); gr_cr21_dummy->SetTitle(""); gr_cr21_dummy->GetXaxis()->SetTitle(""); gr_cr21_dummy->GetXaxis()->SetLimits(-20, 720); gr_cr21_dummy->GetYaxis()->SetRangeUser(6.1, 9.6);
  TGraph *gr_cr32_dummy = new TGraph(1, x_dummy, y_dummy); gr_cr32_dummy->SetTitle(""); gr_cr32_dummy->GetXaxis()->SetTitle(""); gr_cr32_dummy->GetXaxis()->SetLimits(-20, 720); gr_cr32_dummy->GetYaxis()->SetRangeUser(0.005, 0.32);
  TGraph *gr_cr42_dummy = new TGraph(1, x_dummy, y_dummy); gr_cr42_dummy->SetTitle(""); gr_cr42_dummy->GetXaxis()->SetTitle(""); gr_cr42_dummy->GetXaxis()->SetLimits(-20, 720); gr_cr42_dummy->GetYaxis()->SetRangeUser(-1.8, 3.6);
  TGraph *gr_cr51_dummy = new TGraph(1, x_dummy, y_dummy); gr_cr51_dummy->SetTitle(""); gr_cr51_dummy->GetXaxis()->SetTitle(""); gr_cr51_dummy->GetXaxis()->SetLimits(-20, 720); gr_cr51_dummy->GetYaxis()->SetRangeUser(-50-9, 50+9);
  TGraph *gr_cr62_dummy = new TGraph(1, x_dummy, y_dummy); gr_cr62_dummy->SetTitle(""); gr_cr62_dummy->GetXaxis()->SetTitle(""); gr_cr62_dummy->GetXaxis()->SetLimits(-20, 720); gr_cr62_dummy->GetYaxis()->SetRangeUser(-100-20, 100+20);

  TGraph *gr_npart_c1_dummy = new TGraph(1, x_dummy, y_dummy); gr_npart_c1_dummy->SetTitle("C_{1}"); gr_npart_c1_dummy->GetXaxis()->SetTitle("#LT N_{part} #GT");
  if(mergedN == 0) gr_npart_c1_dummy->GetXaxis()->SetLimits(-10, 380);
  if(mergedN == 2) gr_npart_c1_dummy->GetXaxis()->SetLimits(-10, 250);
  gr_npart_c1_dummy->GetYaxis()->SetRangeUser(-0.2, 3.9);
  TGraph *gr_npart_c2_dummy = new TGraph(1, x_dummy, y_dummy); gr_npart_c2_dummy->SetTitle("C_{2}"); gr_npart_c2_dummy->GetXaxis()->SetTitle("#LT N_{part} #GT");
  if(mergedN == 0) gr_npart_c2_dummy->GetXaxis()->SetLimits(-10, 380);
  if(mergedN == 2) gr_npart_c2_dummy->GetXaxis()->SetLimits(-10, 250);
  gr_npart_c2_dummy->GetYaxis()->SetRangeUser(-2, 22);
  TGraph *gr_npart_c3_dummy = new TGraph(1, x_dummy, y_dummy); gr_npart_c3_dummy->SetTitle("C_{3}"); gr_npart_c3_dummy->GetXaxis()->SetTitle("#LT N_{part} #GT");
  if(mergedN == 0) gr_npart_c3_dummy->GetXaxis()->SetLimits(-10, 380);
  if(mergedN == 2) gr_npart_c3_dummy->GetXaxis()->SetLimits(-10, 250);
  gr_npart_c3_dummy->GetYaxis()->SetRangeUser(-0.2, 3.5);
  TGraph *gr_npart_c4_dummy = new TGraph(1, x_dummy, y_dummy); gr_npart_c4_dummy->SetTitle("C_{4}"); gr_npart_c4_dummy->GetXaxis()->SetTitle("#LT N_{part} #GT");
  if(mergedN == 0) gr_npart_c4_dummy->GetXaxis()->SetLimits(-10, 380);
  if(mergedN == 2) gr_npart_c4_dummy->GetXaxis()->SetLimits(-10, 250);
  gr_npart_c4_dummy->GetYaxis()->SetRangeUser(-1, 19);
  TGraph *gr_npart_c5_dummy = new TGraph(1, x_dummy, y_dummy); gr_npart_c5_dummy->SetTitle("C_{5}"); gr_npart_c5_dummy->GetXaxis()->SetTitle("#LT N_{part} #GT");
  if(mergedN == 0) gr_npart_c5_dummy->GetXaxis()->SetLimits(-5, 190);
  if(mergedN == 2) gr_npart_c5_dummy->GetXaxis()->SetLimits(-5, 250);
  gr_npart_c5_dummy->GetYaxis()->SetRangeUser(-90, 90);
  TGraph *gr_npart_c6_dummy = new TGraph(1, x_dummy, y_dummy); gr_npart_c6_dummy->SetTitle("C_{6}"); gr_npart_c6_dummy->GetXaxis()->SetTitle("#LT N_{part} #GT");
  if(mergedN == 0) gr_npart_c6_dummy->GetXaxis()->SetLimits(-5, 190);
  if(mergedN == 2) gr_npart_c6_dummy->GetXaxis()->SetLimits(-5, 250);
  gr_npart_c6_dummy->GetYaxis()->SetRangeUser(-1e3-100, 1e3+100);
  TGraph *gr_npart_cr21_dummy = new TGraph(1, x_dummy, y_dummy); gr_npart_cr21_dummy->SetTitle("C_{2}/C_{1}"); gr_npart_cr21_dummy->GetXaxis()->SetTitle("#LT N_{part} #GT");
  if(mergedN == 0) gr_npart_cr21_dummy->GetXaxis()->SetLimits(-10, 380);
  if(mergedN == 2) gr_npart_cr21_dummy->GetXaxis()->SetLimits(-10, 250);
  gr_npart_cr21_dummy->GetYaxis()->SetRangeUser(6.1, 9.6);
  TGraph *gr_npart_cr32_dummy = new TGraph(1, x_dummy, y_dummy); gr_npart_cr32_dummy->SetTitle("C_{3}/C_{2}"); gr_npart_cr32_dummy->GetXaxis()->SetTitle("#LT N_{part} #GT");
  if(mergedN == 0) gr_npart_cr32_dummy->GetXaxis()->SetLimits(-10, 380);
  if(mergedN == 2) gr_npart_cr32_dummy->GetXaxis()->SetLimits(-10, 250);
  gr_npart_cr32_dummy->GetYaxis()->SetRangeUser(0.015, 0.31);
  TGraph *gr_npart_cr42_dummy = new TGraph(1, x_dummy, y_dummy); gr_npart_cr42_dummy->SetTitle("C_{4}/C_{2}"); gr_npart_cr42_dummy->GetXaxis()->SetTitle("#LT N_{part} #GT");
  if(mergedN == 0) gr_npart_cr42_dummy->GetXaxis()->SetLimits(-10, 380);
  if(mergedN == 2) gr_npart_cr42_dummy->GetXaxis()->SetLimits(-10, 250);
  gr_npart_cr42_dummy->GetYaxis()->SetRangeUser(-1.8, 3.6);
  TGraph *gr_npart_cr51_dummy = new TGraph(1, x_dummy, y_dummy); gr_npart_cr51_dummy->SetTitle("C_{5}/C_{1}"); gr_npart_cr51_dummy->GetXaxis()->SetTitle("#LT N_{part} #GT");
  gr_npart_cr51_dummy->GetXaxis()->SetLimits(-5, 190);
  gr_npart_cr51_dummy->GetYaxis()->SetRangeUser(-50-10, 50+10);
  TGraph *gr_npart_cr62_dummy = new TGraph(1, x_dummy, y_dummy); gr_npart_cr62_dummy->SetTitle("C_{6}/C_{2}"); gr_npart_cr62_dummy->GetXaxis()->SetTitle("#LT N_{part} #GT");
  gr_npart_cr62_dummy->GetXaxis()->SetLimits(-5, 190);
  gr_npart_cr62_dummy->GetYaxis()->SetRangeUser(-100-20, 100+20);

  std::vector<TGraphErrors*> gr_vec, gr_npart_vec, gr_pap_vec;
  gr_vec = load_sys();
  gr_npart_vec = load_sys();
  gr_pap_vec = load_sys();
  TGraphErrors *gr[12*2], *gr_npart[12*2], *gr_pap[12*2];
  for(int i_sys = 0 ; i_sys < 12*2 ; i_sys++){
    gr[i_sys] = (TGraphErrors*)gr_vec[i_sys];

    
    
    gr_npart[i_sys] = (TGraphErrors*)gr_npart_vec[i_sys];
    gr_pap[i_sys] = (TGraphErrors*)gr_pap_vec[i_sys];
  }
  TFile *f_ref3 = new TFile(Form("output/files/cum_%d.root",mergedN), "recreate");
  f_ref3->cd();
  for(int i_sys = 0  ; i_sys < 12 ; i_sys++) gr[i_sys]->Write(Form("gr_c%d_zr_sys", i_sys+1));
  for(int i_sys = 12 ; i_sys < 24 ; i_sys++) gr[i_sys]->Write(Form("gr_c%d_ru_sys", i_sys-12+1));
  f_ref3->Write();
  f_ref3->Close();
  delete f_ref3;
  
  TGraphErrors *gr_npart_c1_zr = (TGraphErrors*)_filezr->Get("proton_C_1"); gr_npart_c1_zr->SetMarkerStyle(4); gr_npart_c1_zr->GetXaxis()->SetTitle("#LT N_{part} #GT"); gr_npart_c1_zr->SetMarkerSize(1.5);
  TGraphErrors *gr_npart_c2_zr = (TGraphErrors*)_filezr->Get("proton_C_2"); gr_npart_c2_zr->SetMarkerStyle(4); gr_npart_c2_zr->GetXaxis()->SetTitle("#LT N_{part} #GT"); gr_npart_c2_zr->SetMarkerSize(1.5);
  TGraphErrors *gr_npart_c3_zr = (TGraphErrors*)_filezr->Get("proton_C_3"); gr_npart_c3_zr->SetMarkerStyle(4); gr_npart_c3_zr->GetXaxis()->SetTitle("#LT N_{part} #GT"); gr_npart_c3_zr->SetMarkerSize(1.5);
  TGraphErrors *gr_npart_c4_zr = (TGraphErrors*)_filezr->Get("proton_C_4"); gr_npart_c4_zr->SetMarkerStyle(4); gr_npart_c4_zr->GetXaxis()->SetTitle("#LT N_{part} #GT"); gr_npart_c4_zr->SetMarkerSize(1.5);
  TGraphErrors *gr_npart_c5_zr = (TGraphErrors*)_filezr->Get("proton_C_5"); gr_npart_c5_zr->SetMarkerStyle(4); gr_npart_c5_zr->GetXaxis()->SetTitle("#LT N_{part} #GT"); gr_npart_c5_zr->SetMarkerSize(1.5);
  TGraphErrors *gr_npart_c6_zr = (TGraphErrors*)_filezr->Get("proton_C_6"); gr_npart_c6_zr->SetMarkerStyle(4); gr_npart_c6_zr->GetXaxis()->SetTitle("#LT N_{part} #GT"); gr_npart_c6_zr->SetMarkerSize(1.5);
  TGraphErrors *gr_npart_cr21_zr = (TGraphErrors*)_filezr->Get("proton_CR_2_1"); gr_npart_cr21_zr->SetMarkerStyle(4); gr_npart_cr21_zr->GetXaxis()->SetTitle("#LT N_{part} #GT"); gr_npart_cr21_zr->SetMarkerSize(1.5);
  TGraphErrors *gr_npart_cr31_zr = (TGraphErrors*)_filezr->Get("proton_CR_3_1"); gr_npart_cr31_zr->SetMarkerStyle(4); gr_npart_cr31_zr->GetXaxis()->SetTitle("#LT N_{part} #GT"); gr_npart_cr31_zr->SetMarkerSize(1.5);
  TGraphErrors *gr_npart_cr32_zr = (TGraphErrors*)_filezr->Get("proton_CR_3_2"); gr_npart_cr32_zr->SetMarkerStyle(4); gr_npart_cr32_zr->GetXaxis()->SetTitle("#LT N_{part} #GT"); gr_npart_cr32_zr->SetMarkerSize(1.5);
  TGraphErrors *gr_npart_cr42_zr = (TGraphErrors*)_filezr->Get("proton_CR_4_2"); gr_npart_cr42_zr->SetMarkerStyle(4); gr_npart_cr42_zr->GetXaxis()->SetTitle("#LT N_{part} #GT"); gr_npart_cr42_zr->SetMarkerSize(1.5);
  TGraphErrors *gr_npart_cr51_zr = (TGraphErrors*)_filezr->Get("proton_CR_5_1"); gr_npart_cr51_zr->SetMarkerStyle(4); gr_npart_cr51_zr->GetXaxis()->SetTitle("#LT N_{part} #GT"); gr_npart_cr51_zr->SetMarkerSize(1.5);
  TGraphErrors *gr_npart_cr62_zr = (TGraphErrors*)_filezr->Get("proton_CR_6_2"); gr_npart_cr62_zr->SetMarkerStyle(4); gr_npart_cr62_zr->GetXaxis()->SetTitle("#LT N_{part} #GT"); gr_npart_cr62_zr->SetMarkerSize(1.5);

  TGraphErrors *gr_npart_c1_ru = (TGraphErrors*)_fileru->Get("proton_C_1"); gr_npart_c1_ru->SetMarkerStyle(8); gr_npart_c1_ru->GetXaxis()->SetTitle("#LT N_{part} #GT"); gr_npart_c1_ru->SetMarkerSize(1.5);
  TGraphErrors *gr_npart_c2_ru = (TGraphErrors*)_fileru->Get("proton_C_2"); gr_npart_c2_ru->SetMarkerStyle(8); gr_npart_c2_ru->GetXaxis()->SetTitle("#LT N_{part} #GT"); gr_npart_c2_ru->SetMarkerSize(1.5);
  TGraphErrors *gr_npart_c3_ru = (TGraphErrors*)_fileru->Get("proton_C_3"); gr_npart_c3_ru->SetMarkerStyle(8); gr_npart_c3_ru->GetXaxis()->SetTitle("#LT N_{part} #GT"); gr_npart_c3_ru->SetMarkerSize(1.5);
  TGraphErrors *gr_npart_c4_ru = (TGraphErrors*)_fileru->Get("proton_C_4"); gr_npart_c4_ru->SetMarkerStyle(8); gr_npart_c4_ru->GetXaxis()->SetTitle("#LT N_{part} #GT"); gr_npart_c4_ru->SetMarkerSize(1.5);
  TGraphErrors *gr_npart_c5_ru = (TGraphErrors*)_fileru->Get("proton_C_5"); gr_npart_c5_ru->SetMarkerStyle(8); gr_npart_c5_ru->GetXaxis()->SetTitle("#LT N_{part} #GT"); gr_npart_c5_ru->SetMarkerSize(1.5);
  TGraphErrors *gr_npart_c6_ru = (TGraphErrors*)_fileru->Get("proton_C_6"); gr_npart_c6_ru->SetMarkerStyle(8); gr_npart_c6_ru->GetXaxis()->SetTitle("#LT N_{part} #GT"); gr_npart_c6_ru->SetMarkerSize(1.5);
  TGraphErrors *gr_npart_cr21_ru = (TGraphErrors*)_fileru->Get("proton_CR_2_1"); gr_npart_cr21_ru->SetMarkerStyle(8); gr_npart_cr21_ru->GetXaxis()->SetTitle("#LT N_{part} #GT"); gr_npart_cr21_ru->SetMarkerSize(1.5);
  TGraphErrors *gr_npart_cr31_ru = (TGraphErrors*)_fileru->Get("proton_CR_3_1"); gr_npart_cr31_ru->SetMarkerStyle(8); gr_npart_cr31_ru->GetXaxis()->SetTitle("#LT N_{part} #GT"); gr_npart_cr31_ru->SetMarkerSize(1.5);
  TGraphErrors *gr_npart_cr32_ru = (TGraphErrors*)_fileru->Get("proton_CR_3_2"); gr_npart_cr32_ru->SetMarkerStyle(8); gr_npart_cr32_ru->GetXaxis()->SetTitle("#LT N_{part} #GT"); gr_npart_cr32_ru->SetMarkerSize(1.5);
  TGraphErrors *gr_npart_cr42_ru = (TGraphErrors*)_fileru->Get("proton_CR_4_2"); gr_npart_cr42_ru->SetMarkerStyle(8); gr_npart_cr42_ru->GetXaxis()->SetTitle("#LT N_{part} #GT"); gr_npart_cr42_ru->SetMarkerSize(1.5);
  TGraphErrors *gr_npart_cr51_ru = (TGraphErrors*)_fileru->Get("proton_CR_5_1"); gr_npart_cr51_ru->SetMarkerStyle(8); gr_npart_cr51_ru->GetXaxis()->SetTitle("#LT N_{part} #GT"); gr_npart_cr51_ru->SetMarkerSize(1.5);
  TGraphErrors *gr_npart_cr62_ru = (TGraphErrors*)_fileru->Get("proton_CR_6_2"); gr_npart_cr62_ru->SetMarkerStyle(8); gr_npart_cr62_ru->GetXaxis()->SetTitle("#LT N_{part} #GT"); gr_npart_cr62_ru->SetMarkerSize(1.5);

  for(int i_cent = 0+mergedN ; i_cent < ncent ; i_cent++){
    gr_npart_c1_ru->SetPointX(i_cent, Npart_ru[i_cent]); /* gr_npart_c1_ru->SetPointError(i_cent, 2, gr_npart_c1_ru->GetErrorY(i_cent)); */ gr_npart_c1_zr->SetPointX(i_cent, Npart_zr[i_cent]); /* gr_npart_c1_zr->SetPointError(i_cent, 2, gr_npart_c1_zr->GetErrorY(i_cent)); */
    gr_npart_c2_ru->SetPointX(i_cent, Npart_ru[i_cent]); /* gr_npart_c2_ru->SetPointError(i_cent, 2, gr_npart_c2_ru->GetErrorY(i_cent)); */ gr_npart_c2_zr->SetPointX(i_cent, Npart_zr[i_cent]); /* gr_npart_c2_zr->SetPointError(i_cent, 2, gr_npart_c2_zr->GetErrorY(i_cent)); */
    gr_npart_c3_ru->SetPointX(i_cent, Npart_ru[i_cent]); /* gr_npart_c3_ru->SetPointError(i_cent, 2, gr_npart_c3_ru->GetErrorY(i_cent)); */ gr_npart_c3_zr->SetPointX(i_cent, Npart_zr[i_cent]); /* gr_npart_c3_zr->SetPointError(i_cent, 2, gr_npart_c3_zr->GetErrorY(i_cent)); */
    gr_npart_c4_ru->SetPointX(i_cent, Npart_ru[i_cent]); /* gr_npart_c4_ru->SetPointError(i_cent, 2, gr_npart_c4_ru->GetErrorY(i_cent)); */ gr_npart_c4_zr->SetPointX(i_cent, Npart_zr[i_cent]); /* gr_npart_c4_zr->SetPointError(i_cent, 2, gr_npart_c4_zr->GetErrorY(i_cent)); */
    gr_npart_c5_ru->SetPointX(i_cent, Npart_ru[i_cent]); /* gr_npart_c5_ru->SetPointError(i_cent, 2, gr_npart_c5_ru->GetErrorY(i_cent)); */ gr_npart_c5_zr->SetPointX(i_cent, Npart_zr[i_cent]); /* gr_npart_c5_zr->SetPointError(i_cent, 2, gr_npart_c5_zr->GetErrorY(i_cent)); */
    gr_npart_c6_ru->SetPointX(i_cent, Npart_ru[i_cent]); /* gr_npart_c6_ru->SetPointError(i_cent, 2, gr_npart_c6_ru->GetErrorY(i_cent)); */ gr_npart_c6_zr->SetPointX(i_cent, Npart_zr[i_cent]); /* gr_npart_c6_zr->SetPointError(i_cent, 2, gr_npart_c6_zr->GetErrorY(i_cent)); */
    gr_npart_cr21_ru->SetPointX(i_cent, Npart_ru[i_cent]); /* gr_npart_cr21_ru->SetPointError(i_cent, 2, gr_npart_cr21_ru->GetErrorY(i_cent)); */ gr_npart_cr21_zr->SetPointX(i_cent, Npart_zr[i_cent]); /* gr_npart_cr21_zr->SetPointError(i_cent, 2, gr_npart_cr21_zr->GetErrorY(i_cent)); */
    gr_npart_cr31_ru->SetPointX(i_cent, Npart_ru[i_cent]); /* gr_npart_cr31_ru->SetPointError(i_cent, 2, gr_npart_cr31_ru->GetErrorY(i_cent)); */ gr_npart_cr31_zr->SetPointX(i_cent, Npart_zr[i_cent]); /* gr_npart_cr31_zr->SetPointError(i_cent, 2, gr_npart_cr31_zr->GetErrorY(i_cent)); */
    gr_npart_cr32_ru->SetPointX(i_cent, Npart_ru[i_cent]); /* gr_npart_cr32_ru->SetPointError(i_cent, 2, gr_npart_cr32_ru->GetErrorY(i_cent)); */ gr_npart_cr32_zr->SetPointX(i_cent, Npart_zr[i_cent]); /* gr_npart_cr32_zr->SetPointError(i_cent, 2, gr_npart_cr32_zr->GetErrorY(i_cent)); */
    gr_npart_cr42_ru->SetPointX(i_cent, Npart_ru[i_cent]); /* gr_npart_cr42_ru->SetPointError(i_cent, 2, gr_npart_cr42_ru->GetErrorY(i_cent)); */ gr_npart_cr42_zr->SetPointX(i_cent, Npart_zr[i_cent]); /* gr_npart_cr42_zr->SetPointError(i_cent, 2, gr_npart_cr42_zr->GetErrorY(i_cent)); */
    gr_npart_cr51_ru->SetPointX(i_cent, Npart_ru[i_cent]); /* gr_npart_cr51_ru->SetPointError(i_cent, 2, gr_npart_cr51_ru->GetErrorY(i_cent)); */ gr_npart_cr51_zr->SetPointX(i_cent, Npart_zr[i_cent]); /* gr_npart_cr51_zr->SetPointError(i_cent, 2, gr_npart_cr51_zr->GetErrorY(i_cent)); */
    gr_npart_cr62_ru->SetPointX(i_cent, Npart_ru[i_cent]); /* gr_npart_cr62_ru->SetPointError(i_cent, 2, gr_npart_cr62_ru->GetErrorY(i_cent)); */ gr_npart_cr62_zr->SetPointX(i_cent, Npart_zr[i_cent]); /* gr_npart_cr62_zr->SetPointError(i_cent, 2, gr_npart_cr62_zr->GetErrorY(i_cent)); */
    for(int i_sys = 0 ; i_sys < 12 ; i_sys++) {gr_npart[i_sys]->SetPointX(i_cent, Npart_zr[i_cent]); gr_npart[i_sys]->SetPointError(i_cent, 2, gr_npart[i_sys]->GetErrorY(i_cent));}
    for(int i_sys = 12 ; i_sys < 24 ; i_sys++) {gr_npart[i_sys]->SetPointX(i_cent, Npart_ru[i_cent]); gr_npart[i_sys]->SetPointError(i_cent, 2, gr_npart[i_sys]->GetErrorY(i_cent));}
    gr_proton_c1_ref3_auau_sys_cent->SetPointError(i_cent, 2, gr_proton_c1_ref3_auau_sys_cent->GetErrorY(i_cent));
    gr_proton_c2_ref3_auau_sys_cent->SetPointError(i_cent, 2, gr_proton_c2_ref3_auau_sys_cent->GetErrorY(i_cent));
    gr_proton_c3_ref3_auau_sys_cent->SetPointError(i_cent, 2, gr_proton_c3_ref3_auau_sys_cent->GetErrorY(i_cent));
    gr_proton_c4_ref3_auau_sys_cent->SetPointError(i_cent, 2, gr_proton_c4_ref3_auau_sys_cent->GetErrorY(i_cent));
    gr_proton_cr21_ref3_auau_sys_cent->SetPointError(i_cent, 2, gr_proton_cr21_ref3_auau_sys_cent->GetErrorY(i_cent));
    gr_proton_cr32_ref3_auau_sys_cent->SetPointError(i_cent, 2, gr_proton_cr32_ref3_auau_sys_cent->GetErrorY(i_cent));
    gr_proton_cr42_ref3_auau_sys_cent->SetPointError(i_cent, 2, gr_proton_cr42_ref3_auau_sys_cent->GetErrorY(i_cent));
  }
  gr_npart_c1_ru->SetFillStyle(3001); gr_npart_c1_zr->SetFillStyle(3001); gr_npart_c1_ru->SetFillColorAlpha(kCyan, 0.5); gr_npart_c1_zr->SetFillColorAlpha(kOrange, 0.5);
  gr_npart_c2_ru->SetFillStyle(3001); gr_npart_c2_zr->SetFillStyle(3001); gr_npart_c2_ru->SetFillColorAlpha(kCyan, 0.5); gr_npart_c2_zr->SetFillColorAlpha(kOrange, 0.5);
  gr_npart_c3_ru->SetFillStyle(3001); gr_npart_c3_zr->SetFillStyle(3001); gr_npart_c3_ru->SetFillColorAlpha(kCyan, 0.5); gr_npart_c3_zr->SetFillColorAlpha(kOrange, 0.5);
  gr_npart_c4_ru->SetFillStyle(3001); gr_npart_c4_zr->SetFillStyle(3001); gr_npart_c4_ru->SetFillColorAlpha(kCyan, 0.5); gr_npart_c4_zr->SetFillColorAlpha(kOrange, 0.5);
  gr_npart_c5_ru->SetFillStyle(3001); gr_npart_c5_zr->SetFillStyle(3001); gr_npart_c5_ru->SetFillColorAlpha(kCyan, 0.5); gr_npart_c5_zr->SetFillColorAlpha(kOrange, 0.5);
  gr_npart_c6_ru->SetFillStyle(3001); gr_npart_c6_zr->SetFillStyle(3001); gr_npart_c6_ru->SetFillColorAlpha(kCyan, 0.5); gr_npart_c6_zr->SetFillColorAlpha(kOrange, 0.5);
  gr_npart_cr21_ru->SetFillStyle(3001); gr_npart_cr21_zr->SetFillStyle(3001); gr_npart_cr21_ru->SetFillColorAlpha(kCyan, 0.5); gr_npart_cr21_zr->SetFillColorAlpha(kOrange, 0.5);
  gr_npart_cr31_ru->SetFillStyle(3001); gr_npart_cr31_zr->SetFillStyle(3001); gr_npart_cr31_ru->SetFillColorAlpha(kCyan, 0.5); gr_npart_cr31_zr->SetFillColorAlpha(kOrange, 0.5);
  gr_npart_cr32_ru->SetFillStyle(3001); gr_npart_cr32_zr->SetFillStyle(3001); gr_npart_cr32_ru->SetFillColorAlpha(kCyan, 0.5); gr_npart_cr32_zr->SetFillColorAlpha(kOrange, 0.5);
  gr_npart_cr42_ru->SetFillStyle(3001); gr_npart_cr42_zr->SetFillStyle(3001); gr_npart_cr42_ru->SetFillColorAlpha(kCyan, 0.5); gr_npart_cr42_zr->SetFillColorAlpha(kOrange, 0.5);
  gr_npart_cr51_ru->SetFillStyle(3001); gr_npart_cr51_zr->SetFillStyle(3001); gr_npart_cr51_ru->SetFillColorAlpha(kCyan, 0.5); gr_npart_cr51_zr->SetFillColorAlpha(kOrange, 0.5);
  gr_npart_cr62_ru->SetFillStyle(3001); gr_npart_cr62_zr->SetFillStyle(3001); gr_npart_cr62_ru->SetFillColorAlpha(kCyan, 0.5); gr_npart_cr62_zr->SetFillColorAlpha(kOrange, 0.5);
  for(int i_sys = 12 ; i_sys < 24 ; i_sys++) {gr_npart[i_sys]->SetFillStyle(3001); gr_npart[i_sys]->SetFillColorAlpha(kCyan, 0.5);}
  for(int i_sys = 0 ; i_sys < 12 ; i_sys++) {gr_npart[i_sys]->SetFillStyle(3001); gr_npart[i_sys]->SetFillColorAlpha(kOrange, 0.5);}
   
  gr_c1_zr->GetYaxis()->SetRangeUser(-0.1, 2.39);
  gr_c2_zr->GetYaxis()->SetRangeUser(-1, 16);
  gr_c3_zr->GetYaxis()->SetRangeUser(-0.1, 1.79);
  gr_c4_zr->GetYaxis()->SetRangeUser(-1, 11);
  gr_c5_zr->GetYaxis()->SetRangeUser(-6, 6);
  gr_c6_zr->GetYaxis()->SetRangeUser(-120, 120);
  
  gr_npart_c1_zr->GetYaxis()->SetRangeUser(-0.1, 2.39);
  gr_npart_c2_zr->GetYaxis()->SetRangeUser(-1, 16);
  gr_npart_c3_zr->GetYaxis()->SetRangeUser(-0.1, 1.99);
  gr_npart_c4_zr->GetYaxis()->SetRangeUser(-1, 11);
  gr_npart_c5_zr->GetYaxis()->SetRangeUser(-2.9, 5.1);
  gr_npart_c6_zr->GetYaxis()->SetRangeUser(-62, 139);

  gr_npart_cr21_zr->GetYaxis()->SetRangeUser(6.5, 8.9);
  gr_npart_cr32_zr->GetYaxis()->SetRangeUser(0.091, 0.141);
  gr_npart_cr42_zr->GetYaxis()->SetRangeUser(0.629, 0.819);
  gr_npart_cr51_zr->GetYaxis()->SetRangeUser(-1.4, 2.3);

  TFile *_fmultzr = TFile::Open(Form("../calcum/output/Zr_dca_10_nhf_20_nsp_20_m2low_60_m2up_120_ptmx_20_ymax_5_detlow_100_deghi_100_%d.root",mergedN), "read");
  TFile *_fmultru = TFile::Open(Form("../calcum/output/Ru_dca_10_nhf_20_nsp_20_m2low_60_m2up_120_ptmx_20_ymax_5_detlow_100_deghi_100_%d.root",mergedN), "read");
  TH1D *h_c1_zr = (TH1D*)_fmultzr->Get("hB_C1_proton_ref3"); h_c1_zr->SetLineColorAlpha(kCyan, 0.5); h_c1_zr->SetMarkerColorAlpha(kCyan, 0.5); h_c1_zr->SetMarkerStyle(25);
  TH1D *h_c2_zr = (TH1D*)_fmultzr->Get("hB_C2_proton_ref3"); h_c2_zr->SetLineColorAlpha(kCyan, 0.5); h_c2_zr->SetMarkerColorAlpha(kCyan, 0.5); h_c2_zr->SetMarkerStyle(25);
  TH1D *h_c3_zr = (TH1D*)_fmultzr->Get("hB_C3_proton_ref3"); h_c3_zr->SetLineColorAlpha(kCyan, 0.5); h_c3_zr->SetMarkerColorAlpha(kCyan, 0.5); h_c3_zr->SetMarkerStyle(25);
  TH1D *h_c4_zr = (TH1D*)_fmultzr->Get("hB_C4_proton_ref3"); h_c4_zr->SetLineColorAlpha(kCyan, 0.5); h_c4_zr->SetMarkerColorAlpha(kCyan, 0.5); h_c4_zr->SetMarkerStyle(25);
  TH1D *h_c5_zr = (TH1D*)_fmultzr->Get("hB_C5_proton_ref3"); h_c5_zr->SetLineColorAlpha(kCyan, 0.5); h_c5_zr->SetMarkerColorAlpha(kCyan, 0.5); h_c5_zr->SetMarkerStyle(25);
  TH1D *h_c6_zr = (TH1D*)_fmultzr->Get("hB_C6_proton_ref3"); h_c6_zr->SetLineColorAlpha(kCyan, 0.5); h_c6_zr->SetMarkerColorAlpha(kCyan, 0.5); h_c6_zr->SetMarkerStyle(25);
  TH1D *h_cr21_zr = (TH1D*)_fmultzr->Get("hB_C7_proton_ref3"); h_cr21_zr->SetLineColorAlpha(kCyan, 0.5); h_cr21_zr->SetMarkerColorAlpha(kCyan, 0.5); h_cr21_zr->SetMarkerStyle(25);
  TH1D *h_cr31_zr = (TH1D*)_fmultzr->Get("hB_C8_proton_ref3"); h_cr31_zr->SetLineColorAlpha(kCyan, 0.5); h_cr31_zr->SetMarkerColorAlpha(kCyan, 0.5); h_cr31_zr->SetMarkerStyle(25);
  TH1D *h_cr32_zr = (TH1D*)_fmultzr->Get("hB_C9_proton_ref3"); h_cr32_zr->SetLineColorAlpha(kCyan, 0.5); h_cr32_zr->SetMarkerColorAlpha(kCyan, 0.5); h_cr32_zr->SetMarkerStyle(25);
  TH1D *h_cr42_zr = (TH1D*)_fmultzr->Get("hB_C10_proton_ref3"); h_cr42_zr->SetLineColorAlpha(kCyan, 0.5); h_cr42_zr->SetMarkerColorAlpha(kCyan, 0.5); h_cr42_zr->SetMarkerStyle(25);
  TH1D *h_cr51_zr = (TH1D*)_fmultzr->Get("hB_C11_proton_ref3"); h_cr51_zr->SetLineColorAlpha(kCyan, 0.5); h_cr51_zr->SetMarkerColorAlpha(kCyan, 0.5); h_cr51_zr->SetMarkerStyle(25);
  TH1D *h_cr62_zr = (TH1D*)_fmultzr->Get("hB_C12_proton_ref3"); h_cr62_zr->SetLineColorAlpha(kCyan, 0.5); h_cr62_zr->SetMarkerColorAlpha(kCyan, 0.5); h_cr62_zr->SetMarkerStyle(25);
  TH1D *h_c1_ru = (TH1D*)_fmultru->Get("hB_C1_proton_ref3"); h_c1_ru->SetLineColorAlpha(kOrange, 0.5); h_c1_ru->SetMarkerColorAlpha(kOrange, 0.5); h_c1_ru->SetMarkerStyle(25);
  TH1D *h_c2_ru = (TH1D*)_fmultru->Get("hB_C2_proton_ref3"); h_c2_ru->SetLineColorAlpha(kOrange, 0.5); h_c2_ru->SetMarkerColorAlpha(kOrange, 0.5); h_c2_ru->SetMarkerStyle(25);
  TH1D *h_c3_ru = (TH1D*)_fmultru->Get("hB_C3_proton_ref3"); h_c3_ru->SetLineColorAlpha(kOrange, 0.5); h_c3_ru->SetMarkerColorAlpha(kOrange, 0.5); h_c3_ru->SetMarkerStyle(25);
  TH1D *h_c4_ru = (TH1D*)_fmultru->Get("hB_C4_proton_ref3"); h_c4_ru->SetLineColorAlpha(kOrange, 0.5); h_c4_ru->SetMarkerColorAlpha(kOrange, 0.5); h_c4_ru->SetMarkerStyle(25);
  TH1D *h_c5_ru = (TH1D*)_fmultru->Get("hB_C5_proton_ref3"); h_c5_ru->SetLineColorAlpha(kOrange, 0.5); h_c5_ru->SetMarkerColorAlpha(kOrange, 0.5); h_c5_ru->SetMarkerStyle(25);
  TH1D *h_c6_ru = (TH1D*)_fmultru->Get("hB_C6_proton_ref3"); h_c6_ru->SetLineColorAlpha(kOrange, 0.5); h_c6_ru->SetMarkerColorAlpha(kOrange, 0.5); h_c6_ru->SetMarkerStyle(25);
  TH1D *h_cr21_ru = (TH1D*)_fmultru->Get("hB_C7_proton_ref3"); h_cr21_ru->SetLineColorAlpha(kOrange, 0.5); h_cr21_ru->SetMarkerColorAlpha(kOrange, 0.5); h_cr21_ru->SetMarkerStyle(25);
  TH1D *h_cr31_ru = (TH1D*)_fmultru->Get("hB_C8_proton_ref3"); h_cr31_ru->SetLineColorAlpha(kOrange, 0.5); h_cr31_ru->SetMarkerColorAlpha(kOrange, 0.5); h_cr31_ru->SetMarkerStyle(25);
  TH1D *h_cr32_ru = (TH1D*)_fmultru->Get("hB_C9_proton_ref3"); h_cr32_ru->SetLineColorAlpha(kOrange, 0.5); h_cr32_ru->SetMarkerColorAlpha(kOrange, 0.5); h_cr32_ru->SetMarkerStyle(25);
  TH1D *h_cr42_ru = (TH1D*)_fmultru->Get("hB_C10_proton_ref3"); h_cr42_ru->SetLineColorAlpha(kOrange, 0.5); h_cr42_ru->SetMarkerColorAlpha(kOrange, 0.5); h_cr42_ru->SetMarkerStyle(25);
  TH1D *h_cr51_ru = (TH1D*)_fmultru->Get("hB_C11_proton_ref3"); h_cr51_ru->SetLineColorAlpha(kOrange, 0.5); h_cr51_ru->SetMarkerColorAlpha(kOrange, 0.5); h_cr51_ru->SetMarkerStyle(25);
  TH1D *h_cr62_ru = (TH1D*)_fmultru->Get("hB_C12_proton_ref3"); h_cr62_ru->SetLineColorAlpha(kOrange, 0.5); h_cr62_ru->SetMarkerColorAlpha(kOrange, 0.5); h_cr62_ru->SetMarkerStyle(25);


  TCanvas *c_c = new TCanvas("c_c", "c_c", 1700, 1000); c_c->Divide(3,2);
  c_c->cd(1);
  gr_c1_dummy->Draw("ap"); h_c1_zr->Draw("same"); h_c1_ru->Draw("same"); gr_c1_zr->Draw("psame"); gr_c1_ru->Draw("psame");
  c_c->cd(2);
  gr_c2_dummy->Draw("ap"); h_c2_zr->Draw("same"); h_c2_ru->Draw("same"); gr_c2_zr->Draw("psame"); gr_c2_ru->Draw("psame");
  c_c->cd(3);
  gr_c3_dummy->Draw("ap"); h_c3_zr->Draw("same"); h_c3_ru->Draw("same"); gr_c3_zr->Draw("psame"); gr_c3_ru->Draw("psame");
  c_c->cd(4);
  gr_c4_dummy->Draw("ap"); h_c4_zr->Draw("same"); h_c4_ru->Draw("same"); gr_c4_zr->Draw("psame"); gr_c4_ru->Draw("psame");
  c_c->cd(5);
  gr_c5_dummy->Draw("ap"); h_c5_zr->Draw("same"); h_c5_ru->Draw("same"); gr_c5_zr->Draw("psame"); gr_c5_ru->Draw("psame");
  c_c->cd(6);
  gr_c6_dummy->Draw("ap"); h_c6_zr->Draw("same"); h_c6_ru->Draw("same"); gr_c6_zr->Draw("psame"); gr_c6_ru->Draw("psame");

  TLegend *l_c = new TLegend(0.1, 0.5, 0.5, 0.9, "", "NDC");
  l_c->AddEntry(h_c1_zr, "Zr+Zr");
  l_c->AddEntry(h_c1_ru, "Ru+Ru");
  l_c->AddEntry(gr_c1_zr, "Zr+Zr w/ CBWC");
  l_c->AddEntry(gr_c1_ru, "Ru+Ru w/ CBWC");
  c_c->cd(1);
  l_c->Draw("same");

  double pad_bottom_buff = 0.1;
  double pad_side_buff = -0.005;
  double pad_side_title_buff = 0.04;
  double bottom_axis_margin = 0.02;
  TCanvas *c_cr_pad = new TCanvas("c_cr_pad", "c_cr_pad", 1000, 1500); c_cr_pad->cd();

  TPaveText *pt_tit_left = new TPaveText(0.1, 0.15, 0.9, 0.75, "NDC NB"); pt_tit_left->SetFillColorAlpha(0,0);
  pt_tit_left->AddText("Charged Particle Multiplicity");
  pt_tit_left->Draw();
  pt_tit_left->Draw();
  gr_c1_dummy->GetYaxis()->SetLabelSize(0.1); gr_c1_dummy->GetYaxis()->SetLabelOffset(0.015); gr_c1_dummy->GetYaxis()->SetNdivisions(505);
  gr_c2_dummy->GetYaxis()->SetLabelSize(0.1); gr_c2_dummy->GetYaxis()->SetLabelOffset(0.015); gr_c2_dummy->GetYaxis()->SetNdivisions(505);
  gr_c3_dummy->GetYaxis()->SetLabelSize(0.09); gr_c3_dummy->GetYaxis()->SetLabelOffset(0.015); gr_c3_dummy->GetYaxis()->SetNdivisions(505);

  gr_c4_dummy->GetYaxis()->SetLabelSize(0.1); gr_c4_dummy->GetYaxis()->SetLabelOffset(0.009); gr_c4_dummy->GetYaxis()->SetNdivisions(505);
  gr_c5_dummy->GetYaxis()->SetLabelSize(0.1); gr_c5_dummy->GetYaxis()->SetLabelOffset(0.009); gr_c5_dummy->GetYaxis()->SetNdivisions(505);
  gr_c6_dummy->GetYaxis()->SetLabelSize(0.09); gr_c6_dummy->GetYaxis()->SetLabelOffset(0.009); gr_c6_dummy->GetYaxis()->SetNdivisions(505);

  gr_c3_dummy->GetXaxis()->SetTitle(""); gr_c3_dummy->GetXaxis()->SetLabelSize(0.1); gr_c3_dummy->GetXaxis()->SetLabelOffset(0.012); gr_c3_dummy->GetXaxis()->SetNdivisions(505);
  gr_c6_dummy->GetXaxis()->SetTitle(""); gr_c6_dummy->GetXaxis()->SetLabelSize(0.1); gr_c6_dummy->GetXaxis()->SetLabelOffset(0.012); gr_c6_dummy->GetXaxis()->SetNdivisions(505);

  TCanvas *c_c_pad = new TCanvas("c_c_pad", "c_c_pad", 1100, 1000); c_c_pad->cd();
  TPad *p_c4     = new TPad("p_c4",     "p_c4",                      0.50 - pad_side_buff-0.05 + pad_side_title_buff, 2 * (1 - 0.01 - pad_bottom_buff) / 3 + pad_bottom_buff + bottom_axis_margin/2, 0.99, 0.99); p_c4->Draw();
  TPad *p_c5     = new TPad("p_c5",     "p_c5",                      0.50 - pad_side_buff-0.05 + pad_side_title_buff, 1 * (1 - 0.01 - pad_bottom_buff) / 3 + pad_bottom_buff + bottom_axis_margin, 0.99, 2 * (1 - 0.01 - pad_bottom_buff) / 3 + pad_bottom_buff + bottom_axis_margin/2); p_c5->Draw();
  TPad *p_c6     = new TPad("p_c6",     "p_c6",                      0.50 - pad_side_buff-0.05 + pad_side_title_buff, 0 * (1 - 0.01 - pad_bottom_buff) / 3 + pad_bottom_buff, 0.99, 1 * (1 - 0.01 - pad_bottom_buff) / 3 + pad_bottom_buff + bottom_axis_margin); p_c6->Draw();
  TPad *p_c1     = new TPad("p_c1",     "p_c1",                      0.01 + 2 * pad_side_title_buff, 2 * (1 - 0.01 - pad_bottom_buff) / 3 + pad_bottom_buff + bottom_axis_margin/2, 0.50 + pad_side_buff - 0.03 + pad_side_title_buff, 0.99); p_c1->Draw();
  TPad *p_c2     = new TPad("p_c2",     "p_c2",                      0.01 + 2 * pad_side_title_buff, 1 * (1 - 0.01 - pad_bottom_buff) / 3 + pad_bottom_buff + bottom_axis_margin, 0.50 + pad_side_buff - 0.03 + pad_side_title_buff, 2 * (1 - 0.01 - pad_bottom_buff) / 3 + pad_bottom_buff + bottom_axis_margin/2); p_c2->Draw();
  TPad *p_c3     = new TPad("p_c3",     "p_c3",                      0.01 + 2 * pad_side_title_buff, 0 * (1 - 0.01 - pad_bottom_buff) / 3 + pad_bottom_buff, 0.50 + pad_side_buff - 0.03 + pad_side_title_buff, 1 * (1 - 0.01 - pad_bottom_buff) / 3 + pad_bottom_buff + bottom_axis_margin); p_c3->Draw();

  TPad *p_c_tit_vertical = new TPad("p_c_tit_vertical","p_c_tit_vertical", 0.01, 0 * (1 - 0.01 - pad_bottom_buff) / 3 + pad_bottom_buff, 0.01 + 2 * pad_side_title_buff, 0.99); p_c_tit_vertical->Draw();
  TPad *p_c_tit_mid = new TPad("p_c_tit_mid","p_c_tit_mid", 0.01 + pad_side_title_buff, 0.01, 0.99, 0 * (1 - 0.01 - pad_bottom_buff) / 3 + pad_bottom_buff); p_c_tit_mid->Draw();
  
  p_c1->SetTopMargin(0); p_c1->SetBottomMargin(0); p_c1->SetLeftMargin(0.1); p_c1->SetRightMargin(0.01);
  p_c2->SetTopMargin(0); p_c2->SetBottomMargin(0); p_c2->SetLeftMargin(0.1); p_c2->SetRightMargin(0.01);
  p_c3->SetTopMargin(0); p_c3->SetBottomMargin(0.1); p_c3->SetLeftMargin(0.1); p_c3->SetRightMargin(0.01);
  
  p_c4->SetTopMargin(0); p_c4->SetBottomMargin(0); p_c4->SetLeftMargin(0.156); p_c4->SetRightMargin(0.1);
  p_c5->SetTopMargin(0); p_c5->SetBottomMargin(0); p_c5->SetLeftMargin(0.156); p_c5->SetRightMargin(0.1);
  p_c6->SetTopMargin(0); p_c6->SetBottomMargin(0.1); p_c6->SetLeftMargin(0.156); p_c6->SetRightMargin(0.1);

  p_c1->cd();
  gr_c1_dummy->Draw("ap"); h_c1_zr->Draw("same"); h_c1_ru->Draw("same"); gr_c1_zr->Draw("psame"); gr_c1_ru->Draw("psame");
  p_c2->cd();
  gr_c2_dummy->Draw("ap"); h_c2_zr->Draw("same"); h_c2_ru->Draw("same"); gr_c2_zr->Draw("psame"); gr_c2_ru->Draw("psame");
  p_c3->cd();
  gr_c3_dummy->Draw("ap"); h_c3_zr->Draw("same"); h_c3_ru->Draw("same"); gr_c3_zr->Draw("psame"); gr_c3_ru->Draw("psame");
  p_c4->cd();
  gr_c4_dummy->Draw("ap"); h_c4_zr->Draw("same"); h_c4_ru->Draw("same"); gr_c4_zr->Draw("psame"); gr_c4_ru->Draw("psame");
  p_c5->cd();
  gr_c5_dummy->Draw("ap"); h_c5_zr->Draw("same"); h_c5_ru->Draw("same"); gr_c5_zr->Draw("psame"); gr_c5_ru->Draw("psame");
  p_c6->cd();
  gr_c6_dummy->Draw("ap"); h_c6_zr->Draw("same"); h_c6_ru->Draw("same"); gr_c6_zr->Draw("psame"); gr_c6_ru->Draw("psame");


  TFile *f_inset;
  TGraphErrors *gr_zoom_buff[12*2];
  if(gSystem->AccessPathName(Form("output/files/cum_%d.root",mergedNzoom))){
    cout<<Form("output/files/cum_%d.root Does not exist!",mergedNzoom)<<endl;
    cout<<Form("Try running first by setting the mergedN = mergedNzoom and re-run")<<endl;
    return;
  }
  else{
    f_inset = new TFile(Form("output/files/cum_%d.root",mergedNzoom), "READ");
    for(int i_sys = 0 ; i_sys < 12 ; i_sys++){
      gr_zoom_buff[i_sys] = (TGraphErrors*)f_inset->Get(Form("gr_c%d_zr_sys", i_sys+1));
      gr_zoom_buff[i_sys]->SetFillStyle(3001); gr_zoom_buff[i_sys]->SetFillColorAlpha(kOrange-6, 0.7); gr_zoom_buff[i_sys]->SetLineWidth(6); gr_zoom_buff[i_sys]->SetLineColorAlpha(kOrange-3, 0.5);
    }
    for(int i_sys = 12 ; i_sys < 12*2 ; i_sys++){
      gr_zoom_buff[i_sys] = (TGraphErrors*)f_inset->Get(Form("gr_c%d_ru_sys", i_sys-12+1));
      gr_zoom_buff[i_sys]->SetFillStyle(3001); gr_zoom_buff[i_sys]->SetFillColorAlpha(kCyan+3, 0.7); gr_zoom_buff[i_sys]->SetLineWidth(6); gr_zoom_buff[i_sys]->SetLineColorAlpha(kCyan+3, 0.5);
    }
  }

  
  p_c5->cd();
  TPad *p_c5_zoom = new TPad("p_c5_zoom", "p_c5_zoom", 0.1+0.055, 0.1-0.05-0.05, 0.6+0.0, 0.1-0.05-0.05+0.45-0.01); p_c5_zoom->SetFillStyle(0); p_c5_zoom->SetFillColorAlpha(0,0); p_c5_zoom->Draw();
  p_c5_zoom->SetTopMargin(0); p_c5_zoom->SetBottomMargin(0.25); p_c5_zoom->SetLeftMargin(0.155); p_c5_zoom->SetRightMargin(0); p_c5_zoom->SetLogx(1);
  p_c5_zoom->cd();
  gr_c5_dummy_zoom->Draw("ap"); if(!gSystem->AccessPathName(Form("output/files/cum_%d.root",mergedNzoom))) {gr_zoom_buff[4]->Draw("5 same"); gr_zoom_buff[4+12]->Draw("5 same");} gr_c5_zr_zoom->Draw("psame"); gr_c5_ru_zoom->Draw("psame"); 
  
  p_c6->cd();
  TPad *p_c6_zoom = new TPad("p_c6_zoom", "p_c6_zoom", 0.1+0.05+0.02, 0.1+0.05-0.05, 0.6-0.01, 0.1+0.05-0.05+0.475+0.001); p_c6_zoom->SetFillStyle(0); p_c6_zoom->SetFillColorAlpha(0,0); p_c6_zoom->Draw();
  p_c6_zoom->SetTopMargin(0.05); p_c6_zoom->SetBottomMargin(0.25); p_c6_zoom->SetLeftMargin(0.2); p_c6_zoom->SetRightMargin(0.01); p_c6_zoom->SetLogx(1);
  p_c6_zoom->cd();
  gr_c6_dummy_zoom->Draw("ap"); if(!gSystem->AccessPathName(Form("output/files/cum_%d.root",mergedNzoom))) {gr_zoom_buff[5]->Draw("5 same"); gr_zoom_buff[5+12]->Draw("5 same");} gr_c6_zr_zoom->Draw("psame"); gr_c6_ru_zoom->Draw("psame");

  TLine *l_c5_zoom = new TLine(gr_c5_dummy_zoom->GetXaxis()->GetXmin(), 0, gr_c5_dummy_zoom->GetXaxis()->GetXmax(), 0); l_c5_zoom->SetLineStyle(2);
  p_c5_zoom->cd(); l_c5_zoom->Draw("same");
  TLine *l_c6_zoom = new TLine(gr_c6_dummy_zoom->GetXaxis()->GetXmin(), 0, gr_c6_dummy_zoom->GetXaxis()->GetXmax(), 0); l_c6_zoom->SetLineStyle(2);
  p_c6_zoom->cd(); l_c6_zoom->Draw("same");


  TMultiGraph *mg_c5_zr = new TMultiGraph(); mg_c5_zr->Add(gr_c5_zr_zoom); mg_c5_zr->Add(gr_zoom_buff[4]); 
  TMultiGraph *mg_c5_ru = new TMultiGraph(); mg_c5_ru->Add(gr_c5_ru_zoom); mg_c5_ru->Add(gr_zoom_buff[4+12]); 
  TMultiGraph *mg_c6_zr = new TMultiGraph(); mg_c6_zr->Add(gr_c6_zr_zoom); mg_c6_zr->Add(gr_zoom_buff[5]); 
  TMultiGraph *mg_c6_ru = new TMultiGraph(); mg_c6_ru->Add(gr_c6_ru_zoom); mg_c6_ru->Add(gr_zoom_buff[5+12]); 

  TF1 *f_c5_zr, *f_c5_ru, *f_c6_zr, *f_c6_ru;
  f_c5_zr = new TF1("f_c5_zr", "pol1", 0, 1000); f_c5_zr->SetLineColor(6); f_c5_zr->SetLineColor(2);
  f_c5_ru = new TF1("f_c5_ru", "pol1", 0, 1000); f_c5_ru->SetLineColor(4); f_c5_ru->SetLineColor(2);
  f_c6_zr = new TF1("f_c6_zr", "pol1", 0, 1000); f_c6_zr->SetLineColor(6); f_c6_zr->SetLineColor(2);
  f_c6_ru = new TF1("f_c6_ru", "pol1", 0, 1000); f_c6_ru->SetLineColor(4); f_c6_ru->SetLineColor(2);

  mg_c5_zr->Fit(f_c5_zr, "F"); mg_c5_ru->Fit(f_c5_ru, "F"); mg_c6_zr->Fit(f_c6_zr, "F"); mg_c6_ru->Fit(f_c6_ru, "F");
  p_c5_zoom->cd(); f_c5_zr->Draw("same"); f_c5_ru->Draw("same"); p_c6_zoom->cd(); f_c6_zr->Draw("same"); f_c6_ru->Draw("same");
  
  TPaveText *pt_tit_vertical = new TPaveText(0.01, 0.01, 0.99, 0.99, "NDC NB"); pt_tit_vertical->SetFillColorAlpha(0,0);
  TText *t_tit_vertical = pt_tit_vertical->AddText("Net-Proton Cumulants");
  t_tit_vertical->SetTextAngle(90);
  t_tit_vertical->SetTextAlign(22);
  t_tit_vertical->SetTextSize(0.55);

  p_c_tit_vertical->cd();
  pt_tit_vertical->Draw();
  
  p_c_tit_mid->cd();
  pt_tit_left->Draw();

  TPaveText *pt_c1 = new TPaveText(0.5 - 0.005 - 0.35, 0.85, 0.6 - 0.005 - 0.35, 0.99, "NDC NB"); pt_c1->SetFillColorAlpha(0,0); pt_c1->AddText("C_{1}"); p_c1->cd(); pt_c1->Draw("same");
  TPaveText *pt_c2 = new TPaveText(0.5 - 0.005 - 0.35, 0.85, 0.6 - 0.005 - 0.35, 0.99, "NDC NB"); pt_c2->SetFillColorAlpha(0,0); pt_c2->AddText("C_{2}"); p_c2->cd(); pt_c2->Draw("same");
  TPaveText *pt_c3 = new TPaveText(0.5 - 0.005 - 0.35+0.005, 0.85+0.005, 0.6 - 0.005 - 0.35-0.005, 0.99-0.005, "NDC NB"); pt_c3->SetFillColorAlpha(0,0); pt_c3->AddText("C_{3}"); p_c3->cd(); pt_c3->Draw("same");
  TPaveText *pt_c4 = new TPaveText(0.5 - 0.005 - 0.305, 0.85, 0.6 - 0.005 - 0.305, 0.99, "NDC NB"); pt_c4->SetFillColorAlpha(0,0); pt_c4->AddText("C_{4}"); p_c4->cd(); pt_c4->Draw("same");
  TPaveText *pt_c5 = new TPaveText(0.5 - 0.005 - 0.305, 0.85, 0.6 - 0.005 - 0.305, 0.99, "NDC NB"); pt_c5->SetFillColorAlpha(0,0); pt_c5->AddText("C_{5}"); p_c5->cd(); pt_c5->Draw("same");
  TPaveText *pt_c6 = new TPaveText(0.5 - 0.005 - 0.305+0.005, 0.85+0.005, 0.6 - 0.005 - 0.305-0.005, 0.99-0.005, "NDC NB"); pt_c6->SetFillColorAlpha(0,0); pt_c6->AddText("C_{6}"); p_c6->cd(); pt_c6->Draw("same");
  
  TPaveText *pt_c2_2_2 = new TPaveText(0.1254855,0.6713586,0.9089473,0.873317, "NDC NB"); pt_c2_2_2->SetFillColorAlpha(0,0);
  TPaveText *pt_c2_2_3 = new TPaveText(0.1298747-0.1298747+0.1254855,0.5501836,0.7004631-0.1298747+0.1254855,0.752142, "NDC NB"); pt_c2_2_3->SetFillColorAlpha(0,0);
  pt_c2_2_2->AddText("Zr+Zr & Ru+Ru Collisions at #sqrt{s_{NN}} = 200 GeV");
  pt_c2_2_3->AddText("|y| < 0.5, 0.4 < p_{T} < 2.0 GeV/c");
  p_c1->cd(); 
  pt_c2_2_2->Draw("same"); pt_c2_2_3->Draw("same");

  
  TLegend *l_c1_1 = new TLegend(0.3+0.25-0.075, 0.62-0.5-0.01, 0.7+0.3+0.075, 0.85-0.5-0.01, "", "NDC NB"); l_c1_1->SetFillColorAlpha(0,0); l_c1_1->SetBorderSize(0);
  l_c1_1->AddEntry(gr_c1_zr, "Zr+Zr /w CBWC", "p");
  l_c1_1->AddEntry(gr_c1_ru, "Ru+Ru /w CBWC", "p");
  p_c1->cd();
  l_c1_1->Draw("same");

  TLegend *l_c4_1 = new TLegend(0.2, 0.55, 0.5, 0.85, "", "NDC NB"); l_c4_1->SetFillColorAlpha(0,0); l_c4_1->SetBorderSize(0);
  h_c1_zr->SetFillColorAlpha(kCyan, 0.5);
  h_c1_ru->SetFillColorAlpha(kOrange, 0.5);
  l_c4_1->AddEntry(h_c1_zr, "Zr+Zr", "f");
  l_c4_1->AddEntry(h_c1_ru, "Ru+Ru", "f");
  p_c4->cd();
  l_c4_1->Draw("same");

  c_c_pad->Print("output/pics/cumulants.pdf");
  

  TFile *f_npart = new TFile(Form("output/files/cum_npart_%d.root",mergedN), "recreate");
  f_npart->cd();
  gr_npart_c1_dummy->Write("gr_npart_c1_dummy");
  gr_npart_c2_dummy->Write("gr_npart_c2_dummy");
  gr_npart_c3_dummy->Write("gr_npart_c3_dummy");
  gr_npart_c4_dummy->Write("gr_npart_c4_dummy");
  gr_npart_c5_dummy->Write("gr_npart_c5_dummy");
  gr_npart_c6_dummy->Write("gr_npart_c6_dummy");
  gr_npart_cr21_dummy->Write("gr_npart_cr21_dummy");
  gr_npart_cr32_dummy->Write("gr_npart_cr32_dummy");
  gr_npart_cr42_dummy->Write("gr_npart_cr42_dummy");
  gr_npart_cr51_dummy->Write("gr_npart_cr51_dummy");
  gr_npart_cr62_dummy->Write("gr_npart_cr62_dummy");

  for(int i_sys = 0  ; i_sys < 12 ; i_sys++) gr_npart[i_sys]->Write(Form("gr_npart_c%d_zr_sys", i_sys+1));
  for(int i_sys = 12 ; i_sys < 24 ; i_sys++) gr_npart[i_sys]->Write(Form("gr_npart_c%d_ru_sys", i_sys-12+1));

  gr_npart_c1_zr->Write("gr_npart_c1_zr"); gr_npart_c1_ru->Write("gr_npart_c1_ru");
  gr_npart_c2_zr->Write("gr_npart_c2_zr"); gr_npart_c2_ru->Write("gr_npart_c2_ru");
  gr_npart_c3_zr->Write("gr_npart_c3_zr"); gr_npart_c3_ru->Write("gr_npart_c3_ru");
  gr_npart_c4_zr->Write("gr_npart_c4_zr"); gr_npart_c4_ru->Write("gr_npart_c4_ru");
  gr_npart_c5_zr->Write("gr_npart_c5_zr"); gr_npart_c5_ru->Write("gr_npart_c5_ru");
  gr_npart_c6_zr->Write("gr_npart_c6_zr"); gr_npart_c6_ru->Write("gr_npart_c6_ru");
  gr_npart_cr21_zr->Write("gr_npart_cr21_zr"); gr_npart_cr21_ru->Write("gr_npart_cr21_ru");
  gr_npart_cr31_zr->Write("gr_npart_cr31_zr"); gr_npart_cr31_ru->Write("gr_npart_cr31_ru");
  gr_npart_cr32_zr->Write("gr_npart_cr32_zr"); gr_npart_cr32_ru->Write("gr_npart_cr32_ru");
  gr_npart_cr42_zr->Write("gr_npart_cr42_zr"); gr_npart_cr42_ru->Write("gr_npart_cr42_ru");
  gr_npart_cr51_zr->Write("gr_npart_cr51_zr"); gr_npart_cr51_ru->Write("gr_npart_cr51_ru");
  gr_npart_cr62_zr->Write("gr_npart_cr62_zr"); gr_npart_cr62_ru->Write("gr_npart_cr62_ru");
  gr_proton_c1_ref3_auau_sys_cent->Write("gr_npart_c1_au_sys"); gr_proton_c1_ref3_auau_sta_cent->Write("gr_npart_c1_au");
  gr_proton_c2_ref3_auau_sys_cent->Write("gr_npart_c2_au_sys"); gr_proton_c2_ref3_auau_sta_cent->Write("gr_npart_c2_au");
  gr_proton_c3_ref3_auau_sys_cent->Write("gr_npart_c3_au_sys"); gr_proton_c3_ref3_auau_sta_cent->Write("gr_npart_c3_au");
  gr_proton_c4_ref3_auau_sys_cent->Write("gr_npart_c4_au_sys"); gr_proton_c4_ref3_auau_sta_cent->Write("gr_npart_c4_au");
  gr_proton_cr21_ref3_auau_sys_cent->Write("gr_npart_cr21_au_sys"); gr_proton_cr21_ref3_auau_sta_cent->Write("gr_npart_cr21_au");
  gr_proton_cr32_ref3_auau_sys_cent->Write("gr_npart_cr32_au_sys"); gr_proton_cr32_ref3_auau_sta_cent->Write("gr_npart_cr32_au");
  gr_proton_cr42_ref3_auau_sys_cent->Write("gr_npart_cr42_au_sys"); gr_proton_cr42_ref3_auau_sta_cent->Write("gr_npart_cr42_au");
  f_npart->Write();
  f_npart->Close();
  delete f_npart;

  ofstream myfile_out_zr, myfile_out_ru;
  myfile_out_zr.open(Form("output/files/third/zr_cr42_%d.txt", mergedN)); myfile_out_ru.open(Form("output/files/third/ru_cr42_%d.txt", mergedN));
  for(int i_cent = 0+mergedN ; i_cent < ncent ; i_cent++){
    myfile_out_zr<<gr_cr42_zr->GetPointX(i_cent)<<"\t"<<gr_npart_cr42_zr->GetPointY(i_cent)<<"\t"<<gr_npart_cr42_zr->GetErrorY(i_cent)<<"\t"<<gr_npart[9]->GetErrorY(i_cent)<<endl;
    myfile_out_ru<<gr_cr42_ru->GetPointX(i_cent)<<"\t"<<gr_npart_cr42_ru->GetPointY(i_cent)<<"\t"<<gr_npart_cr42_ru->GetErrorY(i_cent)<<"\t"<<gr_npart[9+12]->GetErrorY(i_cent)<<endl;
  }
  myfile_out_zr.close(); myfile_out_ru.close();

  myfile_out_zr.open(Form("output/files/third/zr_cr51_%d.txt", mergedN)); myfile_out_ru.open(Form("output/files/third/ru_cr51_%d.txt", mergedN));
  for(int i_cent = 0+mergedN ; i_cent < ncent ; i_cent++){
    myfile_out_zr<<gr_cr51_zr->GetPointX(i_cent)<<"\t"<<gr_npart_cr51_zr->GetPointY(i_cent)<<"\t"<<gr_npart_cr51_zr->GetErrorY(i_cent)<<"\t"<<gr_npart[10]->GetErrorY(i_cent)<<endl;
    myfile_out_ru<<gr_cr51_ru->GetPointX(i_cent)<<"\t"<<gr_npart_cr51_ru->GetPointY(i_cent)<<"\t"<<gr_npart_cr51_ru->GetErrorY(i_cent)<<"\t"<<gr_npart[10+12]->GetErrorY(i_cent)<<endl;
  }
  myfile_out_zr.close(); myfile_out_ru.close();

  myfile_out_zr.open(Form("output/files/third/zr_cr62_%d.txt", mergedN)); myfile_out_ru.open(Form("output/files/third/ru_cr62_%d.txt", mergedN));
  for(int i_cent = 0+mergedN ; i_cent < ncent ; i_cent++){
    myfile_out_zr<<gr_cr62_zr->GetPointX(i_cent)<<"\t"<<gr_npart_cr62_zr->GetPointY(i_cent)<<"\t"<<gr_npart_cr62_zr->GetErrorY(i_cent)<<"\t"<<gr_npart[11]->GetErrorY(i_cent)<<endl;
    myfile_out_ru<<gr_cr62_ru->GetPointX(i_cent)<<"\t"<<gr_npart_cr62_ru->GetPointY(i_cent)<<"\t"<<gr_npart_cr62_ru->GetErrorY(i_cent)<<"\t"<<gr_npart[11+12]->GetErrorY(i_cent)<<endl;
  }
  myfile_out_zr.close(); myfile_out_ru.close();

  return;
}


int main(int argc, char** argv){

  mergedN = atoi(argv[1]);
  sys_cum();
}
