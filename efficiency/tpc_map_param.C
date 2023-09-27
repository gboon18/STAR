//Let's try to make a tpc efficiency map in Multiplicity vs pT
  static int ncent = 10;
const int maxmult = 700;

  TFile *f_tpc_pP; TFile *f_tpc_pM;
  TFile *f_tof_pP; TFile *f_tof_pM;

  TH1D *h1_y_pt_eff_tpc_pP[10];
  TH1D *h1_y_pt_eff_tpc_pM[10];
  TH1D *h1_y_pt_eff_tof_pP[10];
  TH1D *h1_y_pt_eff_tof_pM[10];

  TGraph *gr_eff_tpc_pP, *gr_eff_tpc_pM;
  TGraph *gr_eff_tof_pP, *gr_eff_tof_pM;

  double ref3_avg[10];
  double eff_tpc_pP[10], eff_tpc_pM[10];
  double eff_tof_pP[10], eff_tof_pM[10];


void tpc_map_param(const char* NameRuZr = "Ru", const double dca = 1.0, const int nhf = 20, const double nsp = 2.0){
  gStyle->SetOptStat(00000000);

  int i_sys = -999;
  if(dca == 0.8 && nhf == 20 && nsp == 2.0) i_sys = 0;
  if(dca == 0.9 && nhf == 20 && nsp == 2.0) i_sys = 1;
  if(dca == 1.0 && nhf == 15 && nsp == 2.0) i_sys = 2;
  if(dca == 1.0 && nhf == 18 && nsp == 2.0) i_sys = 3;
  if(dca == 1.0 && nhf == 20 && nsp == 1.6) i_sys = 4;
  if(dca == 1.0 && nhf == 20 && nsp == 1.8) i_sys = 5;
  if(dca == 1.0 && nhf == 20 && nsp == 2.0) i_sys = 6;
  if(dca == 1.0 && nhf == 20 && nsp == 2.2) i_sys = 7;
  if(dca == 1.0 && nhf == 20 && nsp == 2.5) i_sys = 8;
  if(dca == 1.0 && nhf == 22 && nsp == 2.0) i_sys = 9;
  if(dca == 1.0 && nhf == 25 && nsp == 2.0) i_sys = 10;
  if(dca == 1.1 && nhf == 20 && nsp == 2.0) i_sys = 11;
  if(dca == 1.2 && nhf == 20 && nsp == 2.0) i_sys = 12;
  cout<<"i_sys = "<<i_sys<<", dca = "<<dca<<", nhf = "<<nhf<<", nsp = "<<nsp<<endl;
  int cent_ref3[11];
  cent_ref3[0] = 1000;
  cent_ref3[1] = 700;

  //adopted from ~/playground/star/anal/Coll/isobar/ZrZrRuRu200_2018/charge/sys_unc/cum/2_CBWC/Cum.cpp in 23122022
  if(string(NameRuZr) == "Ru") {
    // data: /Users/hosanko/playground/star/anal/Coll/isobar/ZrZrRuRu200_2018/charge/sys_unc/cum/output/net_proton/mean/ypt/10102022/10102022_1/merged_hist_Ru_good123/Ru_hist_mergedFile_dca_10_nhitsfit_20_nsp_20_m2low_60_m2up_120_ptmax_20_ymax_5_detefflow_err_100_deteffhigh_err_100.root
    // sim: /Users/hosanko/playground/star/anal/Coll/isobar/ZrZrRuRu200_2018/charge/GlauberFit/output/ref3/Ru/03082021/03082021_1/Ratio_npp4.100_k4.000_x0.123_eff0.031.root
    // root cendiv.C\(\"/Users/hosanko/playground/star/anal/Coll/isobar/ZrZrRuRu200_2018/charge/paper_plots/an/ch2/output/Ru_hybrid.root\",\"h1_ref3_hyb_ru\"\)
    cent_ref3[2] = 441;
    cent_ref3[3] = 369;
    cent_ref3[4] = 259;
    cent_ref3[5] = 179;
    cent_ref3[6] = 119;
    cent_ref3[7] = 76;
    cent_ref3[8] = 46;
    cent_ref3[9] = 27;
    cent_ref3[10] = 15;
  }
  if(string(NameRuZr) == "Zr") {
    // data: /Users/hosanko/playground/star/anal/Coll/isobar/ZrZrRuRu200_2018/charge/sys_unc/cum/output/net_proton/mean/ypt/10102022/10102022_1/merged_hist_Zr_good123/Zr_hist_mergedFile_dca_10_nhitsfit_20_nsp_20_m2low_60_m2up_120_ptmax_20_ymax_5_detefflow_err_100_deteffhigh_err_100.root
    // sim: /Users/hosanko/playground/star/anal/Coll/isobar/ZrZrRuRu200_2018/charge/GlauberFit/output/ref3/Zr/03082021/03082021_1/Ratio_npp4.100_k4.000_x0.123_eff0.031.root
    // root cendiv.C\(\"/Users/hosanko/playground/star/anal/Coll/isobar/ZrZrRuRu200_2018/charge/paper_plots/an/ch2/output/Zr_hybrid.root\",\"h1_ref3_hyb_zr\"\)
    cent_ref3[2] = 437;
    cent_ref3[3] = 364;
    cent_ref3[4] = 253;
    cent_ref3[5] = 172;
    cent_ref3[6] = 113;
    cent_ref3[7] = 72;
    cent_ref3[8] = 43;
    cent_ref3[9] = 25;
    cent_ref3[10] = 14;
  }

  
  double tpc_p_p0_one_lopt_par0, tpc_p_p0_one_lopt_par1, tpc_p_p1_one_lopt_par0, tpc_p_p1_one_lopt_par1, tpc_p_p2_one_lopt_par0, tpc_p_p2_one_lopt_par1, tpc_p_p0_one_hipt_par0, tpc_p_p0_one_hipt_par1, tpc_p_p1_one_hipt_par0, tpc_p_p1_one_hipt_par1;
  double tpc_ap_p0_one_lopt_par0, tpc_ap_p0_one_lopt_par1, tpc_ap_p1_one_lopt_par0, tpc_ap_p1_one_lopt_par1, tpc_ap_p2_one_lopt_par0, tpc_ap_p2_one_lopt_par1, tpc_ap_p0_one_hipt_par0, tpc_ap_p0_one_hipt_par1, tpc_ap_p1_one_hipt_par0, tpc_ap_p1_one_hipt_par1;
  double tof_p_p0_one_par0, tof_p_p0_one_par1, tof_p_p0_one_par2, tof_p_p1_one_par0, tof_p_p1_one_par1, tof_p_p1_one_par2, tof_p_p2_one_par0, tof_p_p2_one_par1, tof_p_p2_one_par2;
  double tof_ap_p0_one_par0, tof_ap_p0_one_par1, tof_ap_p0_one_par2, tof_ap_p1_one_par0, tof_ap_p1_one_par1, tof_ap_p1_one_par2, tof_ap_p2_one_par0, tof_ap_p2_one_par1, tof_ap_p2_one_par2;

  double dummy1;

  /* cout<<Form("%1.1f, %d, %d, %1.1f", dca, (int) (10.*dca), nhf, nsp)<<endl; */
  
  ifstream myfile_in;
  myfile_in.open(Form("output/TPC/file/eff_pt_dep_cent_fit_oneybin_%s_%s_dca_%d_nhitsfit_%d.txt", "Proton", NameRuZr, (int) (10.*dca), nhf));
  myfile_in>>dummy1>>dummy1>>tpc_p_p0_one_lopt_par0>>tpc_p_p0_one_lopt_par1>>tpc_p_p1_one_lopt_par0>>tpc_p_p1_one_lopt_par1>>tpc_p_p2_one_lopt_par0>>tpc_p_p2_one_lopt_par1>>tpc_p_p0_one_hipt_par0>>tpc_p_p0_one_hipt_par1>>tpc_p_p1_one_hipt_par0>>tpc_p_p1_one_hipt_par1;
  myfile_in.close();
  /* cout<<dummy1<<", "<<dummy1<<", "<<tpc_p_p0_one_lopt_par0<<", "<<tpc_p_p0_one_lopt_par1<<", "<<tpc_p_p1_one_lopt_par0<<", "<<tpc_p_p1_one_lopt_par1<<", "<<tpc_p_p2_one_lopt_par0<<", "<<tpc_p_p2_one_lopt_par1<<", "<<tpc_p_p0_one_hipt_par0<<", "<<tpc_p_p0_one_hipt_par1<<", "<<tpc_p_p1_one_hipt_par0<<", "<<tpc_p_p1_one_hipt_par1<<endl; */
  
  myfile_in.open(Form("output/TPC/file/eff_pt_dep_cent_fit_oneybin_%s_%s_dca_%d_nhitsfit_%d.txt", "AntiProton", NameRuZr, (int) (10.*dca), nhf));
  myfile_in>>dummy1>>dummy1>>tpc_ap_p0_one_lopt_par0>>tpc_ap_p0_one_lopt_par1>>tpc_ap_p1_one_lopt_par0>>tpc_ap_p1_one_lopt_par1>>tpc_ap_p2_one_lopt_par0>>tpc_ap_p2_one_lopt_par1>>tpc_ap_p0_one_hipt_par0>>tpc_ap_p0_one_hipt_par1>>tpc_ap_p1_one_hipt_par0>>tpc_ap_p1_one_hipt_par1;
  myfile_in.close();
  
  myfile_in.open(Form("output/TOF/1D/file/eff_pt_dep_cent_fit_oneybin_%s_%s_dca_%1.1f_nhf_%d_nsp_%1.1f.txt", "Proton", NameRuZr, dca, nhf, nsp));
  /* cout<<Form("output/TOF/1D/file/eff_pt_dep_cent_fit_oneybin_%s_%s_dca_%1.1f_nhf_%d_nsp_%1.1f.txt", "Proton", NameRuZr, dca, nhf, nsp)<<endl; */
  myfile_in>>dummy1>>dummy1>>tof_p_p0_one_par0>>tof_p_p0_one_par1>>tof_p_p0_one_par2>>tof_p_p1_one_par0>>tof_p_p1_one_par1>>tof_p_p1_one_par2>>tof_p_p2_one_par0>>tof_p_p2_one_par1>>tof_p_p2_one_par2;
  myfile_in.close();
  /* cout<<dummy1<<", "<<dummy1<<", "<<tof_p_p0_one_par0<<", "<<tof_p_p0_one_par1<<", "<<tof_p_p0_one_par2<<", "<<tof_p_p1_one_par0<<", "<<tof_p_p1_one_par1<<", "<<tof_p_p1_one_par2<<", "<<tof_p_p2_one_par0<<", "<<tof_p_p2_one_par1<<", "<<tof_p_p2_one_par2<<endl; */
  
  myfile_in.open(Form("output/TOF/1D/file/eff_pt_dep_cent_fit_oneybin_%s_%s_dca_%1.1f_nhf_%d_nsp_%1.1f.txt", "AntiProton", NameRuZr, dca, nhf, nsp));
  myfile_in>>dummy1>>dummy1>>tof_ap_p0_one_par0>>tof_ap_p0_one_par1>>tof_ap_p0_one_par2>>tof_ap_p1_one_par0>>tof_ap_p1_one_par1>>tof_ap_p1_one_par2>>tof_ap_p2_one_par0>>tof_ap_p2_one_par1>>tof_ap_p2_one_par2;
  myfile_in.close();

  TF1 *f_tpc_p_p0_lopt  = new TF1("f_tpc_p_p0_lopt", "pol1", 0, maxmult); TF1 *f_tpc_p_p0_hipt  = new TF1("f_tpc_p_p0_hipt", "pol1", 0, maxmult);
  TF1 *f_tpc_p_p1_lopt  = new TF1("f_tpc_p_p1_lopt", "pol1", 0, maxmult); TF1 *f_tpc_p_p1_hipt  = new TF1("f_tpc_p_p1_hipt", "pol1", 0, maxmult);
  TF1 *f_tpc_p_p2_lopt  = new TF1("f_tpc_p_p2_lopt", "pol1", 0, maxmult); // TF1 *f_tpc_p_p2_hipt  = new TF1("f_tpc_p_p2_hipt", "pol1", 0, maxmult);
  f_tpc_p_p0_lopt->SetParameter(0, tpc_p_p0_one_lopt_par0); f_tpc_p_p0_lopt->SetParameter(1, tpc_p_p0_one_lopt_par1);
  f_tpc_p_p1_lopt->SetParameter(0, tpc_p_p1_one_lopt_par0); f_tpc_p_p1_lopt->SetParameter(1, tpc_p_p1_one_lopt_par1);
  f_tpc_p_p2_lopt->SetParameter(0, tpc_p_p2_one_lopt_par0); f_tpc_p_p2_lopt->SetParameter(1, tpc_p_p2_one_lopt_par1);
  f_tpc_p_p0_hipt->SetParameter(0, tpc_p_p0_one_hipt_par0); f_tpc_p_p0_hipt->SetParameter(1, tpc_p_p0_one_hipt_par1);
  f_tpc_p_p1_hipt->SetParameter(0, tpc_p_p1_one_hipt_par0); f_tpc_p_p1_hipt->SetParameter(1, tpc_p_p1_one_hipt_par1);
  TF1 *f_tpc_ap_p0_lopt  = new TF1("f_tpc_ap_p0_lopt", "pol1", 0, maxmult); TF1 *f_tpc_ap_p0_hipt  = new TF1("f_tpc_ap_p0_hipt", "pol1", 0, maxmult);
  TF1 *f_tpc_ap_p1_lopt  = new TF1("f_tpc_ap_p1_lopt", "pol1", 0, maxmult); TF1 *f_tpc_ap_p1_hipt  = new TF1("f_tpc_ap_p1_hipt", "pol1", 0, maxmult);
  TF1 *f_tpc_ap_p2_lopt  = new TF1("f_tpc_ap_p2_lopt", "pol1", 0, maxmult); // TF1 *f_tpc_ap_p2_hipt  = new TF1("f_tpc_ap_p2_hipt", "pol1", 0, maxmult);
  f_tpc_ap_p0_lopt->SetParameter(0, tpc_ap_p0_one_lopt_par0); f_tpc_ap_p0_lopt->SetParameter(1, tpc_ap_p0_one_lopt_par1);
  f_tpc_ap_p1_lopt->SetParameter(0, tpc_ap_p1_one_lopt_par0); f_tpc_ap_p1_lopt->SetParameter(1, tpc_ap_p1_one_lopt_par1);
  f_tpc_ap_p2_lopt->SetParameter(0, tpc_ap_p2_one_lopt_par0); f_tpc_ap_p2_lopt->SetParameter(1, tpc_ap_p2_one_lopt_par1);
  f_tpc_ap_p0_hipt->SetParameter(0, tpc_ap_p0_one_hipt_par0); f_tpc_ap_p0_hipt->SetParameter(1, tpc_ap_p0_one_hipt_par1);
  f_tpc_ap_p1_hipt->SetParameter(0, tpc_ap_p1_one_hipt_par0); f_tpc_ap_p1_hipt->SetParameter(1, tpc_ap_p1_one_hipt_par1);

  TF1 *f_tof_p_p0  = new TF1("f_tof_p_p0", "pol2", 0, maxmult); TF1 *f_tof_ap_p0  = new TF1("f_tof_ap_p0", "pol2", 0, maxmult);
  TF1 *f_tof_p_p1  = new TF1("f_tof_p_p1", "pol2", 0, maxmult); TF1 *f_tof_ap_p1  = new TF1("f_tof_ap_p1", "pol2", 0, maxmult);
  TF1 *f_tof_p_p2  = new TF1("f_tof_p_p2", "pol2", 0, maxmult); TF1 *f_tof_ap_p2  = new TF1("f_tof_ap_p2", "pol2", 0, maxmult);
  f_tof_p_p0->SetParameter(0, tof_p_p0_one_par0); f_tof_ap_p0->SetParameter(0, tof_ap_p0_one_par0);
  f_tof_p_p0->SetParameter(1, tof_p_p0_one_par1); f_tof_ap_p0->SetParameter(1, tof_ap_p0_one_par1);
  f_tof_p_p0->SetParameter(2, tof_p_p0_one_par2); f_tof_ap_p0->SetParameter(2, tof_ap_p0_one_par2);
  f_tof_p_p1->SetParameter(0, tof_p_p1_one_par0); f_tof_ap_p1->SetParameter(0, tof_ap_p1_one_par0);
  f_tof_p_p1->SetParameter(1, tof_p_p1_one_par1); f_tof_ap_p1->SetParameter(1, tof_ap_p1_one_par1);
  f_tof_p_p1->SetParameter(2, tof_p_p1_one_par2); f_tof_ap_p1->SetParameter(2, tof_ap_p1_one_par2);
  f_tof_p_p2->SetParameter(0, tof_p_p2_one_par0); f_tof_ap_p2->SetParameter(0, tof_ap_p2_one_par0);
  f_tof_p_p2->SetParameter(1, tof_p_p2_one_par1); f_tof_ap_p2->SetParameter(1, tof_ap_p2_one_par1);
  f_tof_p_p2->SetParameter(2, tof_p_p2_one_par2); f_tof_ap_p2->SetParameter(2, tof_ap_p2_one_par2);


  /* TCanvas *c_tpc_p_p012 = new TCanvas("c_tpc_p_p012", "c_tpc_p_p012", 1700, 1000); c_tpc_p_p012->Divide(3,2); */
  /* c_tpc_p_p012->cd(1);  f_tpc_p_p0_lopt->Draw(); */
  /* c_tpc_p_p012->cd(2);  f_tpc_p_p1_lopt->Draw(); */
  /* c_tpc_p_p012->cd(3);  f_tpc_p_p2_lopt->Draw(); */
  /* c_tpc_p_p012->cd(4);  f_tpc_p_p0_hipt->Draw(); */
  /* c_tpc_p_p012->cd(5);  f_tpc_p_p1_hipt->Draw(); */
  
  TF1 *f_tpc_p = new TF1("f_tpc_p", "pol2(0) + pol1(3)", 0.0, 2.0); TF1 *f_tpc_ap = new TF1("f_tpc_ap", "pol2(0) + pol1(3)", 0.0, 2.0);
  TF1 *f_tpc_p_lopt = new TF1("f_tpc_p_lopt", "pol2", 0.0, 0.8); TF1 *f_tpc_ap_lopt = new TF1("f_tpc_ap_lopt", "pol2", 0.0, 0.8);
  TF1 *f_tpc_p_hipt = new TF1("f_tpc_p_hipt", "pol1", 0.8, 2.0); TF1 *f_tpc_ap_hipt = new TF1("f_tpc_ap_hipt", "pol1", 0.8, 2.0);
  TF1 *f_tof_p = new TF1("f_tof_p", "pol2", 0.8, 2.0); TF1 *f_tof_ap = new TF1("f_tof_ap", "pol2", 0.8, 2.0);

  f_tpc_p_lopt->SetLineColor(kRed); f_tpc_ap_lopt->SetLineColor(kBlue);
  f_tpc_p_hipt->SetLineColor(kRed); f_tpc_ap_hipt->SetLineColor(kBlue);
  f_tof_p->SetLineColor(kRed);      f_tof_ap->SetLineColor(kBlue);

  TH2D *h2_tpc_pP = new TH2D("h2_tpc_pP","h2_tpc_pP",100,0,1000,201,0,2);// h2_tpc_pP->GetZaxis()->SetRangeUser(0,1); h2_tpc_pP->GetXaxis()->SetTitle("RefMult3"); h2_tpc_pP->GetYaxis()->SetTitle("p_{T} [GeV]");
  TH2D *h2_tpc_pM = new TH2D("h2_tpc_pM","h2_tpc_pM",100,0,1000,201,0,2);// h2_tpc_pM->GetZaxis()->SetRangeUser(0,1); h2_tpc_pM->GetXaxis()->SetTitle("RefMult3"); h2_tpc_pM->GetYaxis()->SetTitle("p_{T} [GeV]");
  TH2D *h2_tof_pP = new TH2D("h2_tof_pP","h2_tof_pP",100,0,1000,201,0,2);// h2_tof_pP->GetZaxis()->SetRangeUser(0,1); h2_tof_pP->GetXaxis()->SetTitle("RefMult3"); h2_tof_pP->GetYaxis()->SetTitle("p_{T} [GeV]");
  TH2D *h2_tof_pM = new TH2D("h2_tof_pM","h2_tof_pM",100,0,1000,201,0,2);// h2_tof_pM->GetZaxis()->SetRangeUser(0,1); h2_tof_pM->GetXaxis()->SetTitle("RefMult3"); h2_tof_pM->GetYaxis()->SetTitle("p_{T} [GeV]");

  for(int i_ref3 = 0 ; i_ref3 < 100 ; i_ref3++){
    double ref3 = 1.*i_ref3*10;
    /* f_tpc_p->SetParameter(0, f_tpc_p_p0_lopt->Eval(ref3)); */
    /*   f_tpc_p->SetParameter(1, f_tpc_p_p1_lopt->Eval(ref3)); */
    /*   f_tpc_p->SetParameter(2, f_tpc_p_p2_lopt->Eval(ref3)); */
    /*   f_tpc_p->SetParameter(3, f_tpc_p_p0_hipt->Eval(ref3)); */
    /*   f_tpc_p->SetParameter(4, f_tpc_p_p1_hipt->Eval(ref3)); */
    f_tpc_p_lopt->SetParameter(0, f_tpc_p_p0_lopt->Eval(ref3)); f_tpc_ap_lopt->SetParameter(0, f_tpc_ap_p0_lopt->Eval(ref3));
    f_tpc_p_lopt->SetParameter(1, f_tpc_p_p1_lopt->Eval(ref3)); f_tpc_ap_lopt->SetParameter(1, f_tpc_ap_p1_lopt->Eval(ref3));
    f_tpc_p_lopt->SetParameter(2, f_tpc_p_p2_lopt->Eval(ref3)); f_tpc_ap_lopt->SetParameter(2, f_tpc_ap_p2_lopt->Eval(ref3));
    f_tpc_p_hipt->SetParameter(0, f_tpc_p_p0_hipt->Eval(ref3)); f_tpc_ap_hipt->SetParameter(0, f_tpc_ap_p0_hipt->Eval(ref3));
    f_tpc_p_hipt->SetParameter(1, f_tpc_p_p1_hipt->Eval(ref3)); f_tpc_ap_hipt->SetParameter(1, f_tpc_ap_p1_hipt->Eval(ref3));
    f_tof_p->SetParameter(0, f_tof_p_p0->Eval(ref3)); f_tof_ap->SetParameter(0, f_tof_ap_p0->Eval(ref3));
    f_tof_p->SetParameter(1, f_tof_p_p1->Eval(ref3)); f_tof_ap->SetParameter(1, f_tof_ap_p1->Eval(ref3));
    f_tof_p->SetParameter(2, f_tof_p_p2->Eval(ref3)); f_tof_ap->SetParameter(2, f_tof_ap_p2->Eval(ref3));
    for(int i_pt = 0 ; i_pt < 200 ; i_pt++){
      double pT = 1.*i_pt/100;
      if(pT >= 0.4 && pT < 0.8){
	h2_tpc_pP->Fill(ref3, pT, f_tpc_p_lopt->Eval(pT));
	h2_tpc_pM->Fill(ref3, pT, f_tpc_ap_lopt->Eval(pT));
      }
      if(pT >= 0.8 && pT < 2.0){
	h2_tpc_pP->Fill(ref3, pT, f_tpc_p_hipt->Eval(pT));
	h2_tpc_pM->Fill(ref3, pT, f_tpc_ap_hipt->Eval(pT));
      }
      h2_tof_pP->Fill(ref3, pT, f_tof_p->Eval(pT));
      h2_tof_pM->Fill(ref3, pT, f_tof_ap->Eval(pT));
    }// for(int i_pt = 0 ; i_pt < 200 ; i_pt++){
  }// for(int i_ref3 = 0 ; i_ref3 < 100 ; i_ref3++){

  /* f_tpc_p_lopt->GetXaxis()->SetLimits(0., 2.0); */

  TCanvas *c_eff = new TCanvas("c_eff", "c_eff", 1200, 1000); c_eff->Divide(2,2);
  c_eff->cd(1); f_tpc_p->Draw(""); f_tpc_p_lopt->Draw("same"); f_tpc_p_hipt->Draw("same"); f_tpc_ap_lopt->Draw("same"); f_tpc_ap_hipt->Draw("same");
  c_eff->cd(2); f_tof_p->Draw(""); f_tof_ap->Draw("same");

  /* cout<<f_tpc_p_lopt->Eval(0.8)<<", "<<f_tpc_p_hipt->Eval(0.8)<<endl; */

    TCanvas *c_ = new TCanvas("c_","c_",1200,1000); c_->Divide(2,2);
  c_->cd(1); gPad->SetGridx(1); gPad->SetGridy(1); // gPad->SetLogz(1);
  h2_tpc_pP->SetTitle(Form("TPC proton %s, dca = %.1f cm, nhf = %d, nsp = %.1f", NameRuZr, dca, nhf, nsp)); 
  h2_tpc_pP->Draw("colz");
  c_->cd(2); gPad->SetGridx(1); gPad->SetGridy(1); // gPad->SetLogz(1);
  h2_tpc_pM->SetTitle(Form("TPC antiproton %s, dca = %.1f cm, nhf = %d, nsp = %.1f", NameRuZr, dca, nhf, nsp)); 
  h2_tpc_pM->Draw("colz");
  c_->cd(3); gPad->SetGridx(1); gPad->SetGridy(1); // gPad->SetLogz(1);
  h2_tof_pP->SetTitle(Form("TOF proton %s, dca = %.1f cm, nhf = %d, nsp = %.1f", NameRuZr, dca, nhf, nsp)); 
  h2_tof_pP->Draw("colz");
  c_->cd(4); gPad->SetGridx(1); gPad->SetGridy(1); // gPad->SetLogz(1);
  h2_tof_pM->SetTitle(Form("TOF antiproton %s, dca = %.1f cm, nhf = %d, nsp = %.1f", NameRuZr, dca, nhf, nsp)); 
  h2_tof_pM->Draw("colz");

  c_->Print(Form("output/eff_param_read_test/c_%s_%1.1f_%d_%1.1f.pdf",NameRuZr, dca, nhf, nsp));

  int tpc_bin_pt04 = h2_tpc_pP->GetYaxis()->FindBin(0.4);
  int tpc_bin_pt08 = h2_tpc_pP->GetYaxis()->FindBin(0.8);
  int tpc_bin_pt20 = h2_tpc_pP->GetYaxis()->FindBin(2.0);
  int tof_bin_pt08 = h2_tof_pP->GetYaxis()->FindBin(0.8);
  int tof_bin_pt20 = h2_tof_pP->GetYaxis()->FindBin(2.0);

  int nbin_tpc_lopt = tpc_bin_pt08 - tpc_bin_pt04 + 1;
  int nbin_tpc_hipt = tpc_bin_pt20 - tpc_bin_pt08 + 1;
  int nbin_tof_hipt = tof_bin_pt20 - tof_bin_pt08 + 1;
  
  TH1D *h_tpc_pP_lopt = (TH1D*)h2_tpc_pP->ProjectionX("h_tpc_pP_lopt", tpc_bin_pt04, tpc_bin_pt08); h_tpc_pP_lopt->SetLineColor(kRed); h_tpc_pP_lopt->Scale(1./nbin_tpc_lopt);
  TH1D *h_tpc_pM_lopt = (TH1D*)h2_tpc_pM->ProjectionX("h_tpc_pM_lopt", tpc_bin_pt04, tpc_bin_pt08); h_tpc_pM_lopt->SetLineColor(kBlue); h_tpc_pM_lopt->Scale(1./nbin_tpc_lopt);
  TH1D *h_tpc_pP_hipt = (TH1D*)h2_tpc_pP->ProjectionX("h_tpc_pP_hipt", tpc_bin_pt08, tpc_bin_pt20); h_tpc_pP_hipt->SetLineColor(kRed); h_tpc_pP_hipt->Scale(1./nbin_tpc_hipt);
  TH1D *h_tpc_pM_hipt = (TH1D*)h2_tpc_pM->ProjectionX("h_tpc_pM_hipt", tpc_bin_pt08, tpc_bin_pt20); h_tpc_pM_hipt->SetLineColor(kBlue); h_tpc_pM_hipt->Scale(1./nbin_tpc_hipt);
  TH1D *h_tof_pP_hipt = (TH1D*)h2_tof_pP->ProjectionX("h_tof_pP_hipt", tpc_bin_pt08, tpc_bin_pt20); h_tof_pP_hipt->SetLineColor(kRed); h_tof_pP_hipt->Scale(1./nbin_tof_hipt);
  TH1D *h_tof_pM_hipt = (TH1D*)h2_tof_pM->ProjectionX("h_tof_pM_hipt", tpc_bin_pt08, tpc_bin_pt20); h_tof_pM_hipt->SetLineColor(kBlue); h_tof_pM_hipt->Scale(1./nbin_tof_hipt);

  h_tpc_pP_lopt->GetYaxis()->SetRangeUser(0.7, 0.895);
  h_tpc_pP_hipt->GetYaxis()->SetRangeUser(0.7, 0.895);
  h_tof_pP_hipt->GetYaxis()->SetRangeUser(0.6, 0.755);

  h_tpc_pP_lopt->SetTitle(Form("%s TPC efficiency low p_{T}", NameRuZr));
  h_tpc_pP_hipt->SetTitle(Form("%s TPC efficiency high p_{T}", NameRuZr));
  h_tof_pP_hipt->SetTitle(Form("%s TOF efficiency high p_{T}", NameRuZr));
  
  TCanvas *c_1d_1 = new TCanvas("c_1d_1","c_1d_1",1700,500); c_1d_1->Divide(3,1);
  c_1d_1->cd(1); gPad->SetGridx(1); gPad->SetGridy(1); // gPad->SetLogz(1);
  h_tpc_pP_lopt->Draw("hist"); h_tpc_pM_lopt->Draw("same hist");
  c_1d_1->cd(2); gPad->SetGridx(1); gPad->SetGridy(1); // gPad->SetLogz(1);
  h_tpc_pP_hipt->Draw("hist"); h_tpc_pM_hipt->Draw("same hist");
  c_1d_1->cd(3); gPad->SetGridx(1); gPad->SetGridy(1); // gPad->SetLogz(1);
  h_tof_pP_hipt->Draw("hist"); h_tof_pM_hipt->Draw("same hist");

  TLegend *leg_1d = new TLegend(0.5, 0.7, 0.9, 0.9);
  leg_1d->AddEntry(h_tpc_pP_lopt, "proton", "l");
  leg_1d->AddEntry(h_tpc_pM_lopt, "anti-proton", "l");
  c_1d_1->cd(1);
  leg_1d->Draw("same");

  c_1d_1->Print(Form("output/eff_param_read_test/1d/c_%s_%1.1f_%d_%1.1f.pdf",NameRuZr, dca, nhf, nsp));


  /* TH1D *h_tpc_pM_lopt_y_150_250 = (TH1D*)h2_tpc_pM->ProjectionY("h_tpc_pM_lopt_y_150_250", h2_tpc_pM->GetXaxis()->FindBin(150), h2_tpc_pM->GetXaxis()->FindBin(250)); h_tpc_pM_lopt_y_150_250->SetLineColor(kBlue); h_tpc_pM_lopt_y_150_250->Scale(1./(h2_tpc_pM->GetXaxis()->FindBin(250)-h2_tpc_pM->GetXaxis()->FindBin(150)+1)); h_tpc_pM_lopt_y_150_250->SetLineColor(1); */
  /* TH1D *h_tpc_pM_lopt_y_250_350 = (TH1D*)h2_tpc_pM->ProjectionY("h_tpc_pM_lopt_y_250_350", h2_tpc_pM->GetXaxis()->FindBin(250), h2_tpc_pM->GetXaxis()->FindBin(350)); h_tpc_pM_lopt_y_250_350->SetLineColor(kBlue); h_tpc_pM_lopt_y_250_350->Scale(1./(h2_tpc_pM->GetXaxis()->FindBin(350)-h2_tpc_pM->GetXaxis()->FindBin(250)+1)); h_tpc_pM_lopt_y_250_350->SetLineColor(2); */
  /* TH1D *h_tpc_pM_lopt_y_350_450 = (TH1D*)h2_tpc_pM->ProjectionY("h_tpc_pM_lopt_y_350_450", h2_tpc_pM->GetXaxis()->FindBin(350), h2_tpc_pM->GetXaxis()->FindBin(450)); h_tpc_pM_lopt_y_350_450->SetLineColor(kBlue); h_tpc_pM_lopt_y_350_450->Scale(1./(h2_tpc_pM->GetXaxis()->FindBin(450)-h2_tpc_pM->GetXaxis()->FindBin(350)+1)); h_tpc_pM_lopt_y_350_450->SetLineColor(3); */

  /* TCanvas *c_1d_2 = new TCanvas("c_1d_2","c_1d_2",700,500); */
  /* c_1d_2->cd(1); gPad->SetGridx(1); gPad->SetGridy(1); // gPad->SetLogz(1); */
  /* h_tpc_pM_lopt_y_150_250->Draw("hist"); h_tpc_pM_lopt_y_250_350->Draw("hist same"); h_tpc_pM_lopt_y_350_450->Draw("hist same"); */

  TH1D *h_tpc_pP_cent[ncent-1], *h_tpc_pM_cent[ncent-1], *h_tof_pP_cent[ncent-1], *h_tof_pM_cent[ncent-1];
  for(int i_cent = 0 ; i_cent < ncent-1 ; i_cent++){
    h_tpc_pP_cent[i_cent] = (TH1D*)h2_tpc_pP->ProjectionY(Form("h_tpc_pP_cent_%d", i_cent), h2_tpc_pP->GetXaxis()->FindBin(cent_ref3[i_cent+2]), h2_tpc_pP->GetXaxis()->FindBin(cent_ref3[i_cent+1])); h_tpc_pP_cent[i_cent]->SetLineColor(kOrange); h_tpc_pP_cent[i_cent]->SetLineWidth(2); h_tpc_pP_cent[i_cent]->Scale(1./(h2_tpc_pP->GetXaxis()->FindBin(cent_ref3[i_cent+1]) - h2_tpc_pP->GetXaxis()->FindBin(cent_ref3[i_cent+2]) + 1));
    h_tpc_pM_cent[i_cent] = (TH1D*)h2_tpc_pM->ProjectionY(Form("h_tpc_pM_cent_%d", i_cent), h2_tpc_pM->GetXaxis()->FindBin(cent_ref3[i_cent+2]), h2_tpc_pM->GetXaxis()->FindBin(cent_ref3[i_cent+1])); h_tpc_pM_cent[i_cent]->SetLineColor(kCyan); h_tpc_pM_cent[i_cent]->SetLineWidth(2); h_tpc_pM_cent[i_cent]->Scale(1./(h2_tpc_pM->GetXaxis()->FindBin(cent_ref3[i_cent+1]) - h2_tpc_pM->GetXaxis()->FindBin(cent_ref3[i_cent+2]) + 1));
    h_tof_pP_cent[i_cent] = (TH1D*)h2_tof_pP->ProjectionY(Form("h_tof_pP_cent_%d", i_cent), h2_tof_pP->GetXaxis()->FindBin(cent_ref3[i_cent+2]), h2_tof_pP->GetXaxis()->FindBin(cent_ref3[i_cent+1])); h_tof_pP_cent[i_cent]->SetLineColor(kOrange); h_tof_pP_cent[i_cent]->SetLineWidth(2); h_tof_pP_cent[i_cent]->Scale(1./(h2_tof_pP->GetXaxis()->FindBin(cent_ref3[i_cent+1]) - h2_tof_pP->GetXaxis()->FindBin(cent_ref3[i_cent+2]) + 1));
    h_tof_pM_cent[i_cent] = (TH1D*)h2_tof_pM->ProjectionY(Form("h_tof_pM_cent_%d", i_cent), h2_tof_pM->GetXaxis()->FindBin(cent_ref3[i_cent+2]), h2_tof_pM->GetXaxis()->FindBin(cent_ref3[i_cent+1])); h_tof_pM_cent[i_cent]->SetLineColor(kCyan); h_tof_pM_cent[i_cent]->SetLineWidth(2); h_tof_pM_cent[i_cent]->Scale(1./(h2_tof_pM->GetXaxis()->FindBin(cent_ref3[i_cent+1]) - h2_tof_pM->GetXaxis()->FindBin(cent_ref3[i_cent+2]) + 1));
  }

  TFile *fin_tpc_p, *fin_tpc_ap, *fin_tof_p, *fin_tof_ap;
  TH1D *h1_tpc_p[ncent-1], *h1_tpc_ap[ncent-1];
  TH1D *h1_tof_p[ncent-1], *h1_tof_ap[ncent-1];
  fin_tpc_p  = new TFile(Form("output/TPC/file/root/%s_%s_dca_%d_nhitsfit_%d.root", "Proton", NameRuZr, (int) (10*dca), nhf), "read");
  fin_tpc_ap = new TFile(Form("output/TPC/file/root/%s_%s_dca_%d_nhitsfit_%d.root", "AntiProton", NameRuZr, (int) (10*dca), nhf), "read");
  fin_tof_p  = new TFile(Form("output/TOF/1D/file/root/%s_%s_dca_%1.1f_nhf_%d_nsp_%1.1f.root", "Proton", NameRuZr, dca, nhf, nsp), "read");
  fin_tof_ap = new TFile(Form("output/TOF/1D/file/root/%s_%s_dca_%1.1f_nhf_%d_nsp_%1.1f.root", "AntiProton", NameRuZr, dca, nhf, nsp), "read");

  TCanvas *c_tpc = new TCanvas("c_tpc", "c_tpc", 2500, 1000); c_tpc->Divide(5,2);
  TCanvas *c_tof = new TCanvas("c_tof", "c_tof", 2500, 1000); c_tof->Divide(5,2);
  
  for(int i_cent = 0 ; i_cent < ncent - 1 ; i_cent++){
    /* h1_tpc_p[i_cent] = (TH1D*)fin_tpc_p->Get(Form("h1_y_pt_eff_one_%d", i_cent)); h1_tpc_p[i_cent]->SetLineColor(kRed); h1_tpc_p[i_cent]->SetMarkerColor(kRed); h1_tpc_p[i_cent]->SetMarkerStyle(8); */
    /* h1_tpc_ap[i_cent] = (TH1D*)fin_tpc_ap->Get(Form("h1_y_pt_eff_one_%d", i_cent)); h1_tpc_ap[i_cent]->SetLineColor(kBlue); h1_tpc_ap[i_cent]->SetMarkerColor(kBlue); h1_tpc_ap[i_cent]->SetMarkerStyle(8); */
    /* h1_tof_p[i_cent] = (TH1D*)fin_tof_p->Get(Form("h1_y_pt_eff_one_pP_%d", i_cent)); h1_tof_p[i_cent]->SetLineColor(kRed); h1_tof_p[i_cent]->SetMarkerColor(kRed); h1_tof_p[i_cent]->SetMarkerStyle(8); */
    /* h1_tof_ap[i_cent] = (TH1D*)fin_tof_ap->Get(Form("h1_y_pt_eff_one_pM_%d", i_cent)); h1_tof_ap[i_cent]->SetLineColor(kBlue); h1_tof_ap[i_cent]->SetMarkerColor(kBlue); h1_tof_ap[i_cent]->SetMarkerStyle(8); */
    h1_tpc_p[i_cent] = (TH1D*)fin_tpc_p->Get(Form("h1_y_pt_eff_one_%d", i_cent+1)); h1_tpc_p[i_cent]->SetLineColor(kRed); h1_tpc_p[i_cent]->SetMarkerColor(kRed); h1_tpc_p[i_cent]->SetMarkerStyle(8); h1_tpc_p[i_cent]->SetMarkerSize(1.25);
    h1_tpc_ap[i_cent] = (TH1D*)fin_tpc_ap->Get(Form("h1_y_pt_eff_one_%d", i_cent+1)); h1_tpc_ap[i_cent]->SetLineColor(kBlue); h1_tpc_ap[i_cent]->SetMarkerColor(kBlue); h1_tpc_ap[i_cent]->SetMarkerStyle(8); h1_tpc_ap[i_cent]->SetMarkerSize(1.25);
    h1_tof_p[i_cent] = (TH1D*)fin_tof_p->Get(Form("h1_y_pt_eff_one_pP_%d_sys_%d", i_cent+1, i_sys)); h1_tof_p[i_cent]->SetLineColor(kRed); h1_tof_p[i_cent]->SetMarkerColor(kRed); h1_tof_p[i_cent]->SetMarkerStyle(8); h1_tof_p[i_cent]->SetMarkerSize(1.25);
    h1_tof_ap[i_cent] = (TH1D*)fin_tof_ap->Get(Form("h1_y_pt_eff_one_pM_%d_sys_%d", i_cent+1, i_sys)); h1_tof_ap[i_cent]->SetLineColor(kBlue); h1_tof_ap[i_cent]->SetMarkerColor(kBlue); h1_tof_ap[i_cent]->SetMarkerStyle(8); h1_tof_ap[i_cent]->SetMarkerSize(1.25);

    h1_tpc_p[i_cent]->SetTitle(Form("TPC %s [%d, %d)", NameRuZr, cent_ref3[i_cent+2], cent_ref3[i_cent+1]));
    h1_tpc_p[i_cent]->GetXaxis()->SetTitle("p_{T} [GeV/c]");
    /* h1_tpc_p[i_cent]->GetYaxis()->SetRangeUser(0.55, 0.95); */
    h1_tpc_p[i_cent]->GetYaxis()->SetRangeUser(-0.1, 1.1);
    
    h1_tof_p[i_cent]->SetTitle(Form("TOF %s [%d, %d)", NameRuZr, cent_ref3[i_cent+2], cent_ref3[i_cent+1]));
    h1_tof_p[i_cent]->GetXaxis()->SetTitle("p_{T} [GeV/c]");
    /* h1_tof_p[i_cent]->GetYaxis()->SetRangeUser(0.55, 0.95); */
    h1_tof_p[i_cent]->GetYaxis()->SetRangeUser(0.4, 1.1);
    h1_tof_p[i_cent]->GetXaxis()->SetRangeUser(0.8, 2.0);
    /* h1_tof_ap[i_cent]->GetYaxis()->SetRangeUser(0.55, 0.95); */
    h1_tof_ap[i_cent]->GetYaxis()->SetRangeUser(0.4, 1.1);
    h1_tof_ap[i_cent]->GetXaxis()->SetRangeUser(0.8, 2.0);
    
    c_tpc->cd(i_cent+1); gPad->SetGridx(1); gPad->SetGridy(1);
    /* h1_tpc_p[i_cent]->Draw("p hist"); h_tpc_pP_cent[i_cent]->Draw("hist same"); */
    /* h1_tpc_ap[i_cent]->Draw("p hist same"); h_tpc_pM_cent[i_cent]->Draw("hist same"); */
    h1_tpc_p[i_cent]->GetYaxis()->SetRangeUser(0.55, 0.95); // 08032023
    h1_tpc_p[i_cent]->Draw("");
    h_tpc_pP_cent[i_cent]->Draw("hist same"); h1_tpc_p[i_cent]->Draw("same");
    h_tpc_pM_cent[i_cent]->Draw("hist same"); h1_tpc_ap[i_cent]->Draw("same");

    c_tof->cd(i_cent+1); gPad->SetGridx(1); gPad->SetGridy(1);
    /* h1_tof_p[i_cent]->Draw("p hist"); h_tof_pP_cent[i_cent]->Draw("hist same"); */
    /* h1_tof_ap[i_cent]->Draw("p hist same"); h_tof_pM_cent[i_cent]->Draw("hist same"); */
    h1_tof_p[i_cent]->GetYaxis()->SetRangeUser(0.55, 0.95); // 08032023
    h1_tof_p[i_cent]->Draw("");
    h_tof_pP_cent[i_cent]->Draw("hist same"); h1_tof_p[i_cent]->Draw("same");
    h_tof_pM_cent[i_cent]->Draw("hist same"); h1_tof_ap[i_cent]->Draw("same");

  }

  TLegend *leg = new TLegend(0.1, 0.1, 0.9, 0.9);
  leg->AddEntry(h1_tpc_p[0], "Proton eff", "p");
  leg->AddEntry(h1_tpc_ap[0], "AntiProton eff", "p");
  leg->AddEntry(h_tpc_pP_cent[0], "Proton eff param", "l");
  leg->AddEntry(h_tpc_pM_cent[0], "AntiProton eff param", "l");
  c_tpc->cd(10); leg->Draw();
  c_tof->cd(10); leg->Draw();


  c_tpc->Print(Form("output/eff_param_read_test/1d/c_tpc_%s_%1.1f_%d_%1.1f.pdf",NameRuZr, dca, nhf, nsp));
  c_tof->Print(Form("output/eff_param_read_test/1d/c_tof_%s_%1.1f_%d_%1.1f.pdf",NameRuZr, dca, nhf, nsp));
}
