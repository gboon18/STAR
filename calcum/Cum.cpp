//Based on arXiv:1702.07106v3

#include <iostream>
#include "Cum.h"

#include "TH1D.h"
#include "TFile.h"
#include "TKey.h"
#include "TProfile.h"
#include "TMath.h"
#include "TGraphErrors.h"

#include "CalCum.h"

#include <map>

using namespace std;
Cum::Cum(int maxmult_ref3, const char* NameRuZr, int mergetopcent) : maxMult_ref3(maxmult_ref3), MergeTopCent(mergetopcent) {

  //Storing number of events per multiplicity
  hB_Nevt_ref3 = new TH1D(Form("hB_Nevt_%s_ref3", "proton"), Form("hB_Nevt_%s_ref3", "proton"), maxMult_ref3, 0, maxMult_ref3);
  hB_Nevt_ref3->GetXaxis()->SetTitle("RefMult3");

  //Storing cumulants and errors
  for(int i_cum = 0 ; i_cum < Ncums_noErr ; i_cum++ ) {
    hB_C_ref3[i_cum] = new TH1D(Form("hB_C%d_%s_ref3", i_cum+1, "proton"), Form("hB_C%d_%s_ref3", i_cum+1, "proton"), maxMult_ref3, 0, maxMult_ref3);
    hB_C_ref3[i_cum]->GetXaxis()->SetTitle("RefMult3");
    hB_C_ref3_err[i_cum] = new TH1D(Form("hB_C%d_%s_ref3_err", i_cum+1, "proton"), Form("hB_C%d_%s_ref3_err", i_cum+1, "proton"), maxMult_ref3, 0, maxMult_ref3);
    hB_C_ref3_err[i_cum]->GetXaxis()->SetTitle("RefMult3");
    hB_C_ref3_err[i_cum]->GetYaxis()->SetTitle(cum_term_name_noErr[i_cum]);
  }

  //Storing bin merged (CBWC) cumulants
  for(int i_CRK = 0 ; i_CRK < N_CRK_noErr ; i_CRK++){
    grB_C_ref3[i_CRK] = new TGraphErrors(Ncent);
    grB_C_ref3[i_CRK]->SetName(Form("%s_%s", "proton", CRK_name_noErr[i_CRK]));
    grB_C_ref3[i_CRK]->SetTitle(CRK_label_noErr[i_CRK]);
    grB_C_ref3[i_CRK]->SetMarkerStyle(20);
    grB_C_ref3[i_CRK]->GetXaxis()->SetTitle("RefMult3");
    grB_C_ref3[i_CRK]->GetYaxis()->SetTitle(CRK_label_noErr[i_CRK]);
  }

}

Cum::~Cum(){
  //delete stuffs
  delete hB_Nevt_ref3;
  for(int i_cum = 0 ; i_cum < Ncums_noErr ; i_cum++){
    delete hB_C_ref3[i_cum];
    delete hB_C_ref3_err[i_cum];
  }
  
  for(int i_CRK = 0 ; i_CRK < N_CRK_noErr ; i_CRK++){
      delete grB_C_ref3[i_CRK];
    }
}

//////////////////////////////////////////
void Cum::GetRefMult3Means(const char* inFile, const char* NameRuZr, const char* ref3corr){
  //get terms in Eq. 62 ~ 67 & 69 in arXiv:1702.07106v3
  TFile *f_in = new TFile(inFile, "READ");
  std::map<const char*, TProfile*>::iterator iter;
  TIter nextkeyB(f_in->GetListOfKeys());
  TKey *keyB;
  while((keyB = (TKey*)nextkeyB())){
    TString strName = keyB->ReadObj()->GetName();
    if(strName.Contains(Form("%s_%s", "proton", ref3corr))){
      strName.Replace(0, strlen(Form("%s_%s", "proton", ref3corr))+1,"");
    } else {
      continue;
    }
    int iT = 0;
    while (true) {
      if(iT == N_mean_term_noErr) {
	std::cout<<"In Cum::GetRefMult3Means"<<std::endl;
	std::cout<<"Found bad terms"<<std::endl;
	abort();
      }
      if(strcmp(strName, mean_term_name_noErr[iT])==0){
	h_mean_qB_ref3_[iT] = (TProfile*) keyB->ReadObj()->Clone();
	break;
      } else {
	iT++;
      }
    }
  }

  TProfile* entB = (TProfile*)f_in->Get(Form("%s_%s_q01_01","proton",ref3corr));
  for(int i=1;i<entB->GetNbinsX();++i) {
    hB_Nevt_ref3->SetBinContent(i, entB->GetBinEntries(i));//getting No. of Evt per multiplicity
  }
}

//////////////////////////////////////////

void Cum::CalculateEffCorrRefMult3Cum(const char* NameRuZr, int dca_cut, int nhitsfit_cut, int nsp_cut, int m2low_cut, int m2up_cut, int ptmax_cut, int ymax_cut, int detefflow_err, int deteffhigh_err, const char* outputCorr_multbymult){
  //calculate eff corr cumulant

  //proton
  double C_B_1, C_B_2, C_B_3, C_B_4, C_B_5, C_B_6;
  double k_B_1, k_B_2, k_B_3, k_B_4, k_B_5, k_B_6;
  double Cerr_B_1, Cerr_B_2, Cerr_B_3, Cerr_B_4, Cerr_B_5, Cerr_B_6;
  double kerr_B_1, kerr_B_2, kerr_B_3, kerr_B_4, kerr_B_5, kerr_B_6;
  double CRerr_B_21, CRerr_B_31, CRerr_B_32, CRerr_B_42, CRerr_B_51, CRerr_B_62;
  double kRerr_B_21, kRerr_B_31, kRerr_B_32, kRerr_B_41, kRerr_B_43, kRerr_B_51, kRerr_B_54, kRerr_B_61, kRerr_B_65;

  double mean_qB_ref3_[N_mean_term_noErr];

  CalCum *mCalCumB = new CalCum();//proton
  
  for(int i_RM = 0 ; i_RM < maxMult_ref3 ; i_RM++){
    mCalCumB->Init();
    cout<<"Cum::CalculateEffCorrRefMult3Cum(). Multiplicity: "<<i_RM<<"/"<<maxMult_ref3<<endl;
    C_B_1 = C_B_2 = C_B_3 = C_B_4 = C_B_5 = C_B_6 = 0. ;
    k_B_1 = k_B_2 = k_B_3 = k_B_4 = k_B_5 = k_B_6 = 0. ;
    Cerr_B_1 = Cerr_B_2 = Cerr_B_3 = Cerr_B_4 = Cerr_B_5 = Cerr_B_6 = 0. ;
    kerr_B_1 = kerr_B_2 = kerr_B_3 = kerr_B_4 = kerr_B_5 = kerr_B_6 = 0. ;
    CRerr_B_21 = CRerr_B_31 = CRerr_B_32 = CRerr_B_42 = CRerr_B_51 = CRerr_B_62 = 0. ;
    kRerr_B_21 = kRerr_B_31 = kRerr_B_32 = kRerr_B_41 = kRerr_B_43 = kRerr_B_51 = kRerr_B_54 = kRerr_B_61 = kRerr_B_65 = 0. ;

    int Nevt = h_mean_qB_ref3_[0]->GetBinEntries(i_RM);
    if(Nevt < 1) continue;

    for(int i_term = 0 ; i_term < N_mean_term_noErr ; i_term++){
      mean_qB_ref3_[i_term] = h_mean_qB_ref3_[i_term]->GetBinContent(i_RM);
      mCalCumB->SetMean(mean_qB_ref3_[i_term], i_term);
    }

    mCalCumB->SetCums( Nevt );

    C_B_1 = mCalCumB->Get_tc1();
    C_B_2 = mCalCumB->Get_tc2();
    C_B_3 = mCalCumB->Get_tc3();
    C_B_4 = mCalCumB->Get_tc4();
    C_B_5 = mCalCumB->Get_tc5();
    C_B_6 = mCalCumB->Get_tc6();

    k_B_1 = mCalCumB->Get_tk1();
    k_B_2 = mCalCumB->Get_tk2();
    k_B_3 = mCalCumB->Get_tk3();
    k_B_4 = mCalCumB->Get_tk4();
    k_B_5 = mCalCumB->Get_tk5();
    k_B_6 = mCalCumB->Get_tk6();

    Cerr_B_1 = mCalCumB->Get_etc1();
    Cerr_B_2 = mCalCumB->Get_etc2();
    Cerr_B_3 = mCalCumB->Get_etc3();
    Cerr_B_4 = mCalCumB->Get_etc4();
    Cerr_B_5 = mCalCumB->Get_etc5();
    Cerr_B_6 = mCalCumB->Get_etc6();

    kerr_B_1 = mCalCumB->Get_etk1();
    kerr_B_2 = mCalCumB->Get_etk2();
    kerr_B_3 = mCalCumB->Get_etk3();
    kerr_B_4 = mCalCumB->Get_etk4();
    kerr_B_5 = mCalCumB->Get_etk5();
    kerr_B_6 = mCalCumB->Get_etk6();

    if(C_B_1 != 0) CRerr_B_21 = mCalCumB->Get_er21();
    if(C_B_1 != 0) CRerr_B_31 = mCalCumB->Get_er31();
    if(C_B_2 != 0) CRerr_B_32 = mCalCumB->Get_er32();
    if(C_B_2 != 0) CRerr_B_42 = mCalCumB->Get_er42();
    if(C_B_1 != 0) CRerr_B_51 = mCalCumB->Get_er51();
    if(C_B_2 != 0) CRerr_B_62 = mCalCumB->Get_er62();

    if(k_B_1 != 0) kRerr_B_21 = mCalCumB->Get_ek21();
    if(k_B_1 != 0) kRerr_B_31 = mCalCumB->Get_ek31();
    if(k_B_2 != 0) kRerr_B_32 = mCalCumB->Get_ek32();
    if(k_B_1 != 0) kRerr_B_41 = mCalCumB->Get_ek41();
    if(k_B_3 != 0) kRerr_B_43 = mCalCumB->Get_ek43();
    if(k_B_1 != 0) kRerr_B_51 = mCalCumB->Get_ek51();
    if(k_B_4 != 0) kRerr_B_54 = mCalCumB->Get_ek54();
    if(k_B_1 != 0) kRerr_B_61 = mCalCumB->Get_ek61();
    if(k_B_5 != 0) kRerr_B_65 = mCalCumB->Get_ek65();

    //Fill it
    hB_C_ref3[0]->SetBinContent(i_RM, C_B_1);//C1
    hB_C_ref3[1]->SetBinContent(i_RM, C_B_2);//C2
    hB_C_ref3[2]->SetBinContent(i_RM, C_B_3);//C3
    hB_C_ref3[3]->SetBinContent(i_RM, C_B_4);//C4
    hB_C_ref3[4]->SetBinContent(i_RM, C_B_5);//C5
    hB_C_ref3[5]->SetBinContent(i_RM, C_B_6);//C6
    hB_C_ref3[0]->SetBinError(i_RM, mCalCumB->Get_etc1());//C1
    hB_C_ref3[1]->SetBinError(i_RM, mCalCumB->Get_etc2());//C2
    hB_C_ref3[2]->SetBinError(i_RM, mCalCumB->Get_etc3());//C3
    hB_C_ref3[3]->SetBinError(i_RM, mCalCumB->Get_etc4());//C4
    hB_C_ref3[4]->SetBinError(i_RM, mCalCumB->Get_etc5());//C5
    hB_C_ref3[5]->SetBinError(i_RM, mCalCumB->Get_etc6());//C6

    if(C_B_1 != 0) {
      hB_C_ref3[6]->SetBinContent(i_RM, C_B_2/C_B_1);// C2/C1
      hB_C_ref3[6]->SetBinError(i_RM, mCalCumB->Get_er21());// C2/C1
    }
    if(C_B_1 != 0) {
      hB_C_ref3[7]->SetBinContent(i_RM, C_B_3/C_B_1);// C3/C1
      hB_C_ref3[7]->SetBinError(i_RM, mCalCumB->Get_er31());// C3/C1
    }
    if(C_B_2 != 0) {
      hB_C_ref3[8]->SetBinContent(i_RM, C_B_3/C_B_2);// C3/C2
      hB_C_ref3[8]->SetBinError(i_RM, mCalCumB->Get_er32());// C3/C2
    }
    if(C_B_2 != 0) {
      hB_C_ref3[9]->SetBinContent(i_RM, C_B_4/C_B_2);// C4/C2
      hB_C_ref3[9]->SetBinError(i_RM, mCalCumB->Get_er42());// C4/C2
    }
    if(C_B_1 != 0){
      hB_C_ref3[10]->SetBinContent(i_RM, C_B_5/C_B_1);// C5/C1
      hB_C_ref3[10]->SetBinError(i_RM, mCalCumB->Get_er51());// C5/C1
    }
    if(C_B_2 != 0){
      hB_C_ref3[11]->SetBinContent(i_RM, C_B_6/C_B_2);// C6/C2
      hB_C_ref3[11]->SetBinError(i_RM, mCalCumB->Get_er62());// C6/C2
    }

    hB_C_ref3[12]->SetBinContent(i_RM,  k_B_1);//k1
    hB_C_ref3[13]->SetBinContent(i_RM,  k_B_2);//k2
    hB_C_ref3[14]->SetBinContent(i_RM,  k_B_3);//k3
    hB_C_ref3[15]->SetBinContent(i_RM,  k_B_4);//k4
    hB_C_ref3[16]->SetBinContent(i_RM, k_B_5);//k5
    hB_C_ref3[17]->SetBinContent(i_RM, k_B_6);//k6

    if(k_B_1 != 0) {hB_C_ref3[18]->SetBinContent(i_RM, k_B_2/k_B_1); hB_C_ref3[18]->SetBinError(i_RM, mCalCumB->Get_ek21());}// k2/k1
    if(k_B_1 != 0) {hB_C_ref3[19]->SetBinContent(i_RM, k_B_3/k_B_1); hB_C_ref3[19]->SetBinError(i_RM, mCalCumB->Get_ek31());}// k3/k1
    if(k_B_2 != 0) {hB_C_ref3[20]->SetBinContent(i_RM, k_B_3/k_B_2); hB_C_ref3[20]->SetBinError(i_RM, mCalCumB->Get_ek32());}// k3/k2
    if(k_B_1 != 0) {hB_C_ref3[21]->SetBinContent(i_RM, k_B_4/k_B_1); hB_C_ref3[21]->SetBinError(i_RM, mCalCumB->Get_ek41());}// k4/k1
    if(k_B_3 != 0) {hB_C_ref3[22]->SetBinContent(i_RM, k_B_4/k_B_3); hB_C_ref3[22]->SetBinError(i_RM, mCalCumB->Get_ek43());}// k4/k3
    if(k_B_1 != 0) {hB_C_ref3[23]->SetBinContent(i_RM, k_B_5/k_B_1); hB_C_ref3[23]->SetBinError(i_RM, mCalCumB->Get_ek51());}// k5/k1
    if(k_B_4 != 0) {hB_C_ref3[24]->SetBinContent(i_RM, k_B_5/k_B_4); hB_C_ref3[24]->SetBinError(i_RM, mCalCumB->Get_ek54());}// k5/k4
    if(k_B_1 != 0) {hB_C_ref3[25]->SetBinContent(i_RM, k_B_6/k_B_1); hB_C_ref3[25]->SetBinError(i_RM, mCalCumB->Get_ek61());}// k6/k1
    if(k_B_5 != 0) {hB_C_ref3[26]->SetBinContent(i_RM, k_B_6/k_B_5); hB_C_ref3[26]->SetBinError(i_RM, mCalCumB->Get_ek65());}// k6/k5

    ///////
    //Err//
    ///////
    hB_C_ref3_err[0]->SetBinContent(i_RM, Cerr_B_1);//c_err1
    hB_C_ref3_err[1]->SetBinContent(i_RM, Cerr_B_2);//c_err2
    hB_C_ref3_err[2]->SetBinContent(i_RM, Cerr_B_3);//c_err3
    hB_C_ref3_err[3]->SetBinContent(i_RM, Cerr_B_4);//c_err4
    hB_C_ref3_err[4]->SetBinContent(i_RM, Cerr_B_5);//c_err5
    hB_C_ref3_err[5]->SetBinContent(i_RM, Cerr_B_6);//c_err6

    hB_C_ref3_err[6]->SetBinContent(i_RM, kerr_B_1);//k_err1
    hB_C_ref3_err[7]->SetBinContent(i_RM, kerr_B_2);//k_err2
    hB_C_ref3_err[8]->SetBinContent(i_RM, kerr_B_3);//k_err3
    hB_C_ref3_err[9]->SetBinContent(i_RM, kerr_B_4);//k_err4
    hB_C_ref3_err[10]->SetBinContent(i_RM, kerr_B_5);//k_err5
    hB_C_ref3_err[11]->SetBinContent(i_RM, kerr_B_6);//k_err6

    hB_C_ref3_err[12]->SetBinContent(i_RM, CRerr_B_21);//CR_err21
    hB_C_ref3_err[13]->SetBinContent(i_RM, CRerr_B_31);//CR_err31
    hB_C_ref3_err[14]->SetBinContent(i_RM, CRerr_B_32);//CR_err32
    hB_C_ref3_err[15]->SetBinContent(i_RM, CRerr_B_42);//CR_err42
    hB_C_ref3_err[16]->SetBinContent(i_RM, CRerr_B_51);//CR_err51
    hB_C_ref3_err[17]->SetBinContent(i_RM, CRerr_B_62);//CR_err62

    hB_C_ref3_err[18]->SetBinContent(i_RM, kRerr_B_21);//kR_err21
    hB_C_ref3_err[19]->SetBinContent(i_RM, kRerr_B_31);//kR_err31
    hB_C_ref3_err[20]->SetBinContent(i_RM, kRerr_B_32);//kR_err32
    hB_C_ref3_err[21]->SetBinContent(i_RM, kRerr_B_41);//kR_err41
    hB_C_ref3_err[22]->SetBinContent(i_RM, kRerr_B_43);//kR_err43
    hB_C_ref3_err[23]->SetBinContent(i_RM, kRerr_B_51);//kR_err51
    hB_C_ref3_err[24]->SetBinContent(i_RM, kRerr_B_54);//kR_err54
    hB_C_ref3_err[25]->SetBinContent(i_RM, kRerr_B_61);//kR_err61
    hB_C_ref3_err[26]->SetBinContent(i_RM, kRerr_B_65);//kR_err65

  }//refMult loop ends

  WriteEffCorrRefMult3Cum(outputCorr_multbymult);
  
  delete mCalCumB;
}

//////////////////////////////////////////

void Cum::WriteEffCorrRefMult3Cum(const char* outFile){

  TFile *f_out = new TFile(outFile, "RECREATE");
  f_out->cd();
  for(int i = 0 ; i < Ncums_noErr ; i++){
    hB_C_ref3[i]->Write();
    hB_C_ref3_err[i]->Write();
  }

  hB_Nevt_ref3->Write();
  f_out->Close();
  
}

//RefMult3
void Cum::CalculateRefMult3CBWCcum(const char* NameRuZr, int dca_cut, int nhitsfit_cut, int nsp_cut, int m2low_cut, int m2up_cut, int ptmax_cut, int ymax_cut, int detefflow_err, int deteffhigh_err, const char* outputCorr_cbwc){

  double CentEvent[Ncent] = {0.};
  double AvgCent[Ncent] = {0.};
  double CumSumB[Ncent] = {0.};
  double CumErrSumB[Ncent] = {0.};

  for(int i_CRK = 0 ; i_CRK < N_CRK_noErr ; i_CRK++){

    int Nevt = 0;

    for(int i_cent = 0 ; i_cent < Ncent ; i_cent++){
      CentEvent[i_cent] = 0.;
      AvgCent[i_cent] = 0.;
      CumSumB[i_cent] = 0.;
      CumErrSumB[i_cent] = 0.;
    }//centrality bin loop ends

    for(int i_mult = 0 ; i_mult < maxMult_ref3 ; i_mult++){
      Nevt = hB_Nevt_ref3->GetBinContent(i_mult+1);
      int CentBin = getRefMult3Cent(i_mult, NameRuZr);

      if(CentBin == -1) continue;
	CentEvent[CentBin] += Nevt;//denominator

	AvgCent[CentBin] += i_mult*Nevt;

	CumSumB[CentBin] += (hB_C_ref3[i_CRK]->GetBinContent(i_mult+1) * Nevt);//numerator

	if(!isnan(hB_C_ref3[i_CRK]->GetBinError(i_mult+1))) CumErrSumB[CentBin] += TMath::Power(hB_C_ref3[i_CRK]->GetBinError(i_mult+1) * Nevt, 2);
    }//mult loop ends
    for(int i_cent = 0 ; i_cent < Ncent ; i_cent++){
      AvgCent[i_cent] /= CentEvent[i_cent];
      CumSumB[i_cent] /= CentEvent[i_cent];
      CumErrSumB[i_cent] = ( TMath::Sqrt(CumErrSumB[i_cent]) / CentEvent[i_cent] );
      if(i_cent < MergeTopCent) {AvgCent[i_cent] = -999; CumSumB[i_cent] = -999; CumErrSumB[i_cent] = 0;}
	grB_C_ref3[i_CRK]->SetPoint(i_cent, AvgCent[i_cent], CumSumB[i_cent]);
	if(!isnan(CumErrSumB[i_cent])) grB_C_ref3[i_CRK]->SetPointError(i_cent, 0, CumErrSumB[i_cent]);
    }//centrality bin loop ends

  }//CRK loop ends
  WriteRefMult3CBWCcum(outputCorr_cbwc);
}

//////////////////////////////////////////

void Cum::WriteRefMult3CBWCcum(const char* outFile){
    TFile *f_out = new TFile(outFile, "RECREATE");
    f_out->cd();
    // for(int i = 0 ; i < Ncums ; i++){
    for(int i = 0 ; i < N_CRK_noErr ; i++){
      grB_C_ref3[i]->Write();
    }
    f_out->Close();

}

int Cum::getRefMult3Cent(int mult, const char* NameRuZr){

  if(string(NameRuZr) == "Ru") {
    centrality_ref3[0] = 441;
    centrality_ref3[1] = 369;
    centrality_ref3[2] = 259;
    centrality_ref3[3] = 179;
    centrality_ref3[4] = 119;
    centrality_ref3[5] = 76;
    centrality_ref3[6] = 46;
    centrality_ref3[7] = 27;
    centrality_ref3[8] = 15;
  }
  if(string(NameRuZr) == "Zr") {
    centrality_ref3[0] = 437;
    centrality_ref3[1] = 364;
    centrality_ref3[2] = 253;
    centrality_ref3[3] = 172;
    centrality_ref3[4] = 113;
    centrality_ref3[5] = 72;
    centrality_ref3[6] = 43;
    centrality_ref3[7] = 25;
    centrality_ref3[8] = 14;
  }
  if(string(NameRuZr) == "RuZr") {
    centrality_ref3[0] = 437;
    centrality_ref3[1] = 365;
    centrality_ref3[2] = 255;
    centrality_ref3[3] = 174;
    centrality_ref3[4] = 115;
    centrality_ref3[5] = 73;
    centrality_ref3[6] = 44;
    centrality_ref3[7] = 25;
    centrality_ref3[8] = 13;
  }
  int topcentmerged[Ncent];
  for(int i_cent = 0 ; i_cent < Ncent ; i_cent++){
    topcentmerged[i_cent] = (i_cent < MergeTopCent) ? MergeTopCent : i_cent;
  }  
  if      (mult>=centrality_ref3[0] && mult<maxMult_ref3) return topcentmerged[0];    // 0-5%
  else if (mult>=centrality_ref3[1] && mult<centrality_ref3[0]) return topcentmerged[1];   // 5-10%
  else if (mult>=centrality_ref3[2] && mult<centrality_ref3[1]) return topcentmerged[2];    // 10-20%
  else if (mult>=centrality_ref3[3] && mult<centrality_ref3[2]) return topcentmerged[3];    // 20-30%
  else if (mult>=centrality_ref3[4] && mult<centrality_ref3[3]) return topcentmerged[4];    // 30-40%
  else if (mult>=centrality_ref3[5] && mult<centrality_ref3[4]) return topcentmerged[5];    // 40-50%
  else if (mult>=centrality_ref3[6] && mult<centrality_ref3[5]) return topcentmerged[6];    // 50-60%
  else if (mult>=centrality_ref3[7] && mult<centrality_ref3[6]) return topcentmerged[7];    // 60-70%
  else if (mult>=centrality_ref3[8] && mult<centrality_ref3[7]) return topcentmerged[8];    // 70-80%
  else    return -1;

}


