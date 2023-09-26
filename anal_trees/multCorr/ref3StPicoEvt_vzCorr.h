//Multiplicity luminosity correction
#include <iostream>
#include <fstream>
#include "TMath.h"
#include "TGraph.h"
using namespace std;
double ref3StPicoEvt_vzCorr(double Vz, double mult, string NameRuZr){

  double p0 = 0., p1 = 0., p2 = 0., p3 = 0., p4 = 0., p5 = 0., p6 = 0.;

  if(NameRuZr == "Zr"){
    p0 = 512.751;
    p1 = 0.0931099;
    p2 = -0.00560097;
    p3 = 9.45105e-05;
    p4 = 7.30438e-06;
    p5 = -9.47235e-08;
    p6 = -6.00799e-09;
  }
  if(NameRuZr == "Ru"){
    p0 = 514.56;
    p1 = 0.108917;
    p2 = -0.00478876;
    p3 = -1.11905e-05;
    p4 = 5.34282e-06;
    p5 = 3.09103e-08;
    p6 = -3.42707e-09;
  }

  double f_vz = p0 + p1*Vz + p2*TMath::Power(Vz, 2) + p3*TMath::Power(Vz, 3) + p4*TMath::Power(Vz, 4) + p5*TMath::Power(Vz, 5) + p6*TMath::Power(Vz, 6);
  double vz_corr = p0 / f_vz;
  double mult_vzcorr = mult * vz_corr;

  return mult_vzcorr;
}
double ref3StPicoEvt_vzCorr_vz0norm(double Vz, double mult, string NameRuZr){

  ifstream myfile_in;
  double vz[30+1], par_vzcorr_arr[30], par_vzcorr;
  double vz_cent[30];
  for(int i_vz = 0 ; i_vz < 30 ; i_vz++){
    vz[i_vz] = -35 + i_vz*2;
    vz_cent[i_vz] = -34 + i_vz*2;
  }
  vz[30] = 25;

  if(NameRuZr == "Zr"){
    myfile_in.open("/star/u/hsko/pwg/anal/Coll/isobar/ZrZrRuRu200_2018/charge/code_qa/anal_trees/multCorr/zr_vzcorr_par.txt");
    for(int i_vz = 0 ; i_vz < 30 ; i_vz++){
      myfile_in>>par_vzcorr_arr[i_vz];
      /* cout<<"ref3StPicoEvt_vzCorr_vz0norm: "<<NameRuZr<<", "<< */
    }
    myfile_in.close();
  }
  if(NameRuZr == "Ru"){
    myfile_in.open("/star/u/hsko/pwg/anal/Coll/isobar/ZrZrRuRu200_2018/charge/code_qa/anal_trees/multCorr/ru_vzcorr_par.txt");
    for(int i_vz = 0 ; i_vz < 30 ; i_vz++){
      myfile_in>>par_vzcorr_arr[i_vz];
    }
    myfile_in.close();
  }

  TGraph *gr = new TGraph(30, vz_cent, par_vzcorr_arr);
  par_vzcorr = gr->Eval(Vz);

  double mult_vzcorr = mult * par_vzcorr;

  return mult_vzcorr;
}
