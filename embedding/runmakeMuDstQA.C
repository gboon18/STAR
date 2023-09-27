#include <ctime>

//wrapper to makeMuDstQA.C
//for ACLiC mode
//05102021(start)
// void runmakeMuDstQA(TString InputFileList,Int_t nfiles,Int_t nevents,TString OutputFile, const Int_t PID)
void runmakeMuDstQA(TString InputFileList,Int_t nfiles,Int_t nevents,TString OutputFile, const Int_t PID, double dca_cut, int nHitsFits_cut, string thisNameRuZr)
//05102021(finish)
{
  // current date/time based on current system
  time_t now = time(0); 
  
  gROOT->Reset();
  gROOT->Macro("loadMuDst.C");
  gROOT->LoadMacro("makeMuDstQA.C+");
//05102021(start)
  // makeMuDstQA(InputFileList,nfiles,nevents,OutputFile, PID);
  makeMuDstQA(InputFileList,nfiles,nevents,OutputFile, PID, dca_cut, nHitsFits_cut, thisNameRuZr);
//05102021(finish)

  // current date/time based on current system
  time_t then = time(0);
  time_t diff = then - now;
  // convert now to string form
  char* dt = ctime(&diff);
  // convert now to tm struct for UTC
  tm* gmtm = gmtime(&diff);
  dt = asctime(gmtm);
  cout << "****************************************** " << endl;
  cout << "It took :"<< dt <<"for the job to be done."  << endl;
  cout << "****************************************** " << endl;
}
