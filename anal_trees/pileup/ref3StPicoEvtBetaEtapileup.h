//refmult3 from StPicoEvent pileup removal
// x: nbtofmatch, y: multiplicity
// =============StPicoEvent's ref3 params=============
#include <iostream>
#include <fstream>
using namespace std;
Bool_t ref3StPicoEvtBetaEtapileup(UShort_t refMult, UShort_t beta_eta1, string NameRuZr){
  /* double p0_up = 0., p1_up = 0.; */
  double p0_low = 0., p1_low = 0.;
  

  //pile up obtained from Zr and Ru combined distribution
  if(NameRuZr == "Zr"){
    /* p0_up = 19.7674, p1_up = 1.51163; */
    p0_low = -8, p1_low = 0.38;
  }
  if(NameRuZr == "Ru"){
    /* p0_up = 19.7674, p1_up = 1.51163; */
    p0_low = -8, p1_low = 0.38;
  }

  /* double refmultmax = 0.; */
  double refmultmin = 0.;

  /* refmultmax = ( p0_up  + p1_up*(refMult) ); */
  refmultmin = ( p0_low + p1_low*(refMult) );

  /* return (beta_eta1<refmultmax && beta_eta1>refmultmin); */
  return (beta_eta1>refmultmin);
}
