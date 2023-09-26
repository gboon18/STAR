//refmult3 from StPicoEvent pileup removal
// x: nbtofmatch, y: multiplicity
// =============StPicoEvent's ref3 params=============
#include <iostream>
#include <fstream>
using namespace std;
Bool_t ref3StPicoEvtisNotPileUp(UShort_t btofMatched, UShort_t refMult, string NameRuZr){
  double a0=0., a1=0., a2=0., a3=0., a4=0.;
  double b0=0., b1=0., b2=0., b3=0., b4=0.;
  double c0=0., c1=0., c2=0., c3=0., c4=0.;

  //=============StPicoEvent ref3 linear cut param=============
  /* if (btofMatched >= 450) */
  double p0_up = 0., p1_up = 0.;
  /* if (btofMatched >= 500)  */
  double p0_low = 0., p1_low = 0.;
  

  //pile up obtained from Zr and Ru combined distribution
  if(NameRuZr == "Zr"){
    a0 = 0.383155, a1 = 1.5744, a2 = -0.000803728, a3 = 2.09246e-06, a4 = -2.44575e-09;
    b0 = 41.0932, b1 = 1.51482, b2 = 0.000746628, b3 = -1.54576e-06, b4 = -1.01965e-09;
    c0 = -13.0068, c1 = 1.11895, c2 = 0.000940213, c3 = -2.6137e-06, c4 = 2.92931e-09;
    //=============StPicoEvent ref3 linear cut param=============
    p0_up = 19.7674, p1_up = 1.51163;
    p0_low = -16.2222, p1_low = 1.31111;
  }
  if(NameRuZr == "Ru"){
    a0 = 0.383155, a1 = 1.5744, a2 = -0.000803728, a3 = 2.09246e-06, a4 = -2.44575e-09;
    b0 = 41.0932, b1 = 1.51482, b2 = 0.000746628, b3 = -1.54576e-06, b4 = -1.01965e-09;
    c0 = -13.0068, c1 = 1.11895, c2 = 0.000940213, c3 = -2.6137e-06, c4 = 2.92931e-09;
    //=============StPicoEvent ref3 linear cut param=============
    p0_up = 19.7674, p1_up = 1.51163;
    p0_low = -16.2222, p1_low = 1.31111;
  }

  double refmultmax = 0.;//( b0 + b1*(btofMatched) + b2*pow(btofMatched,2) + b3*pow(btofMatched,3) + b4*pow(btofMatched,4) );
  double refmultmin = 0.;//( c0 + c1*(btofMatched) + c2*pow(btofMatched,2) + c3*pow(btofMatched,3) + c4*pow(btofMatched,4) );

  if(btofMatched >= 450){
    refmultmax = ( p0_up  + p1_up*(btofMatched) );
  }
  if(btofMatched < 450){
    refmultmax = ( b0 + b1*(btofMatched) + b2*pow(btofMatched,2) + b3*pow(btofMatched,3) + b4*pow(btofMatched,4) );
  }

  if(btofMatched >= 500){
    refmultmin = ( p0_low + p1_low*(btofMatched) );
  }
  if(btofMatched < 500){
    refmultmin = ( c0 + c1*(btofMatched) + c2*pow(btofMatched,2) + c3*pow(btofMatched,3) + c4*pow(btofMatched,4) );
  }

  return (refMult<refmultmax && refMult>refmultmin);
}
