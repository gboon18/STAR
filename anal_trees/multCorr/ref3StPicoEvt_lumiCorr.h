//Multiplicity luminosity correction
#include <iostream>
#include <fstream>
using namespace std;
double ref3StPicoEvt_lumiCorr(double ZDCx, double mult, string NameRuZr){

  double a = 0.;
  double b = 0.;
  double b_prime = 0.;

  if(NameRuZr == "Zr"){
    a = 1.19406e-06 ;
    b = 171.295;
    b_prime = 171.167;
  }
  if(NameRuZr == "Ru"){
    a = -0.00022314;
    b = 175.001;
    b_prime = 172.639;
  }

  double f_zdcx = a * ZDCx + b;
  double lumi_corr = b_prime / f_zdcx;
  double mult_lumicorr = mult * lumi_corr;  

  return mult_lumicorr;
}
