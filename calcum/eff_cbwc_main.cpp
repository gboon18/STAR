#include <iostream>

#include "Cum.h"

#include "TFile.h"

using namespace std;

void calcum(const char* NameRuZr, int dca_cut, int nhitsfit_cut, int nsp_cut, int m2low_cut, int m2up_cut, int ptmax_cut, int ymax_cut, int detefflow_err, int deteffhigh_err, int MergeTopCent = 0, const char* fnameCorr = "", const char* ref3corr = "", const char* outputCorr_multbymult = "", const char* outputCorr_cbwc = ""){
  int maxMult_ref3 = 700;
  Cum *cum = new Cum(maxMult_ref3, NameRuZr, MergeTopCent);

  cout<<"fnameCorr = "<<fnameCorr<<endl;
  cout<<"ref3corr = "<<ref3corr<<endl;


  cum->GetRefMult3Means(fnameCorr, NameRuZr, ref3corr);
    
  cum->CalculateEffCorrRefMult3Cum(NameRuZr, dca_cut, nhitsfit_cut, nsp_cut, m2low_cut, m2up_cut, ptmax_cut, ymax_cut, detefflow_err, deteffhigh_err, outputCorr_multbymult);
  cum->CalculateRefMult3CBWCcum(NameRuZr, dca_cut, nhitsfit_cut, nsp_cut, m2low_cut, m2up_cut, ptmax_cut, ymax_cut, detefflow_err, deteffhigh_err, outputCorr_cbwc);


  delete cum;

  return;
}

int main(int argc, char** argv){


  // 1ru||zr, 2dca_cut, 3nhf_cut, 4nsp_cut, 5m2low, 6m2up, 7ptmax, 8ymax, 9detlow, 10dethi, 11mergebin, 12corrin, 13ref3corr, 14outcorr, 15outcorr_cbwc
  calcum(argv[1], atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7]), atoi(argv[8]), atoi(argv[9]), atoi(argv[10]), atoi(argv[11]), argv[12], argv[13], argv[14], argv[15]);

  
  return 0;
}
