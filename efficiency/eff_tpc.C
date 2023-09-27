// cp eff2.C eff_tpc.C
void eff_tpc(const char* NamePPiK = "Proton", const char* NameRuZr = "Ru", int dca_cut = 10, int nhf_cut = 20){

  const int ncent = 10;
  const int nphi = 1;
  int nxbin = 50;
  //04082022(start)
  int nybin = 5;
  /* int nybin = 50;//to make it more closer to Ashish's */
  //04082022(finish)

  //https://drive.google.com/file/d/1TPrAanuiBoMcvw8FedtL8aNHgW8j8H1M/view?usp=sharing
  //RefMult, not RefMult3
  int cent_ref[11];
  cent_ref[0] = 800;
  cent_ref[1] = 500;
  if(string(NameRuZr) == "Ru"){
    cent_ref[2] = 258;//0-5%
    cent_ref[3] = 216;//5-10%
    cent_ref[4] = 151;//10-20%
    cent_ref[5] = 103;//20-30%
    cent_ref[6] =  69;//30-40%
    cent_ref[7] =  44;//40-50%
    cent_ref[8] =  26;//50-60%
    cent_ref[9] =  15;//60-70%
    cent_ref[10] =  8;//70-80%
  }
  if(string(NameRuZr) == "Zr"){
    cent_ref[2] =  256;//0-5%
    cent_ref[3] =  213;//5-10%
    cent_ref[4] =  147;//10-20%
    cent_ref[5] =  100;//20-30%
    cent_ref[6] =   65;//30-40%
    cent_ref[7] =   41;//40-50%
    cent_ref[8] =   25;//50-60%
    cent_ref[9] =   14;//60-70%
    cent_ref[10] =  7;//70-80%
  }

  /* /Users/hosanko/playground/star/anal/Coll/isobar/ZrZrRuRu200_2018/charge/GlauberFit/draw */
  /* ./cendiv.py output/hybrid/ref3/Ru_hybrid.root h1_ref3_hyb_ru  */
  /* ./cendiv.py output/hybrid/ref3/Zr_hybrid.root h1_ref3_hyb_zr  */
  /* from mult_data_sim_hybrid_net_proton_ref3.C */

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

  /* TFile *f_glauber_hyb = new TFile(Form("/Users/hosanko/playground/star/anal/Coll/isobar/ZrZrRuRu200_2018/charge/GlauberFit/draw/output/ref3/file/%s.root", NameRuZr), "READ"); */  TFile *f_glauber_hyb = new TFile(Form("/Users/hosanko/playground/star/anal/Coll/isobar/ZrZrRuRu200_2018/charge/GlauberFit/draw/output/hybrid/ref3/%s_hybrid.root", NameRuZr), "READ");
  TH1D *h1_ref3_hyb;
  if(string(NameRuZr) == "Ru") h1_ref3_hyb = (TH1D*)f_glauber_hyb->Get("h1_ref3_hyb_ru");
  if(string(NameRuZr) == "Zr") h1_ref3_hyb = (TH1D*)f_glauber_hyb->Get("h1_ref3_hyb_zr");
  double ref3_avg = 0.;
  double ref3_avg_arr[ncent];
  double cent_evt[ncent];
  for(int i_cent = 0 ; i_cent < ncent ; i_cent++){
    ref3_avg_arr[i_cent] = 0.;
    cent_evt[i_cent] = 0.;
    ref3_avg = 0.;
    for(int i_mult = cent_ref3[i_cent+1] ; i_mult < cent_ref3[i_cent] ; i_mult++){
      /* ref3_avg += i_mult * h1_ref3_hyb->GetBinContent(h1_ref3_hyb->FindBin(i_mult));// / (h1_ref3_hyb->Integral(cent_ref3[i_cent+1], cent_ref3[i_cent])); */
      /* ref3_avg_arr[i_cent] += i_mult * h1_ref3_hyb->GetBinContent(h1_ref3_hyb->FindBin(i_mult)); */
      /* cent_evt[i_cent] += h1_ref3_hyb->GetBinContent(h1_ref3_hyb->FindBin(i_mult)); */
      /* cout<<i_mult<<endl; */
      ref3_avg_arr[i_cent] += i_mult * h1_ref3_hyb->GetBinContent(i_mult);
      cent_evt[i_cent] += h1_ref3_hyb->GetBinContent(i_mult);
 
    }
    /* ref3_avg_arr[i_cent] = ref3_avg; */
    cout<<ref3_avg_arr[i_cent]<<"/"<<cent_evt[i_cent]<<" = "<<ref3_avg_arr[i_cent]/cent_evt[i_cent]<<endl;
    ref3_avg_arr[i_cent] /= cent_evt[i_cent];
    if(isnan(ref3_avg)) ref3_avg_arr[i_cent] = 0.;
  }//for(int i_cent = 0 ; i_cent < ncent ; i_cent++){
  
  /* //////////ONLY TO GET AVG MULT for each CENT START/////////// */
  /* //from /Users/hosanko/playground/star/anal/Coll/isobar/ZrZrRuRu200_2018/charge/sys_unc/efficiency/draw/12042022/1/eff.C */
  /* static const int NyBin = 1; */
  /* static const int NptBin = 2; */
  /* TH1D *h1_ref_mc_p[2], *h1_ref_mc_m[2];//0.4 < pT < 0.8 GeV/c && 0.8 < pT < 2.0 GeV/c */
  /* TH1D *h1_ref_p[2], *h1_ref_m[2]; */
  /* TH1D *h1_ref_tpceff_p[2], *h1_ref_tpceff_m[2]; // for(int i = 0 ; i < 2 ; i++) {h1_ref_tpceff_p[i]->Sumw2(); h1_ref_tpceff_m[i]->Sumw2();} */

  /* TFile *f_tpc_p = new TFile(Form("/Users/hosanko/playground/star/anal/Coll/isobar/ZrZrRuRu200_2018/charge/sys_unc/efficiency/net_proton/TPC/26032022/26032022_1/%s_%s_dca_%d_nhitsfit_%d.root", NamePPiK, NameRuZr, dca_cut, nhf_cut), "READ"); */

  /* for(int i_y = 0 ; i_y < NyBin ; i_y++){ */
  /*   for(int i_pt = 0 ; i_pt < NptBin ; i_pt++){ */
  /*     if(string(NamePPiK) == "Proton" || string(NamePPiK) == "Piplus" || string(NamePPiK) == "Kplus"){ */
  /* 	h1_ref_mc_p[NptBin*i_y + i_pt] = (TH1D*)f_tpc_p->Get(Form("h1_ref_mc_P_%d", NptBin*i_y + i_pt)); */
  /* 	/\* h1_ref_mc_m[NptBin*i_y + i_pt] = (TH1D*)f_tpc_m->Get(Form("h1_ref_mc_M_%d", NptBin*i_y + i_pt)); *\/ */
  /* 	h1_ref_p[NptBin*i_y + i_pt] = (TH1D*)f_tpc_p->Get(Form("h1_ref_P_%d", NptBin*i_y + i_pt)); */
  /* 	/\* h1_ref_m[NptBin*i_y + i_pt] = (TH1D*)f_tpc_m->Get(Form("h1_ref_M_%d", NptBin*i_y + i_pt)); *\/ */
  /* 	h1_ref_tpceff_p[NptBin*i_y + i_pt] = (TH1D*)h1_ref_p[NptBin*i_y + i_pt]->Clone(); */
  /* 	h1_ref_tpceff_p[NptBin*i_y + i_pt]->Divide(h1_ref_mc_p[NptBin*i_y + i_pt]); */
  /* 	/\* h1_ref_tpceff_m[NptBin*i_y + i_pt] = (TH1D*)h1_ref_m[NptBin*i_y + i_pt]->Clone(); *\/ */
  /* 	/\* h1_ref_tpceff_m[NptBin*i_y + i_pt]->Divide(h1_ref_mc_m[NptBin*i_y + i_pt]); *\/ */
  /*     } */
  /*     else if(string(NamePPiK) == "AntiProton" || string(NamePPiK) == "Piminus" || string(NamePPiK) == "Kminus"){ */
  /* 	h1_ref_mc_p[NptBin*i_y + i_pt] = (TH1D*)f_tpc_p->Get(Form("h1_ref_mc_M_%d", NptBin*i_y + i_pt)); */
  /* 	h1_ref_p[NptBin*i_y + i_pt] = (TH1D*)f_tpc_p->Get(Form("h1_ref_M_%d", NptBin*i_y + i_pt)); */
  /* 	h1_ref_tpceff_p[NptBin*i_y + i_pt] = (TH1D*)h1_ref_p[NptBin*i_y + i_pt]->Clone(); */
  /* 	h1_ref_tpceff_p[NptBin*i_y + i_pt]->Divide(h1_ref_mc_p[NptBin*i_y + i_pt]); */
  /*     } */
  /*   } */
  /* } */
  /* double ref_avg = 0., ref_tpceff_avg = 0., ref_tpceff_avg2 = 0., ref_tpceff_err = 0.; */
  /* double ref_avg_arr[9], ref_tpceff_avg_arr[9], ref_tpceff_avg2_arr[9], ref_tpceff_err_arr[9]; */
  /* /\* cout<<"Proton ref tpc low-pT eff"<<endl; *\/ */
  /* for(int i_cent = 0 ; i_cent < ncent ; i_cent++){ */
  /*   ref_avg = 0.; ref_tpceff_avg = 0.; ref_tpceff_avg2 = 0.; ref_tpceff_err = 0.; */
  /*   /\* int i_cent = 0; *\/ */
  /*   for(int i_mult = cent_ref[i_cent+1] ; i_mult < cent_ref[i_cent] ; i_mult++){ */
  /*     ref_avg += i_mult * h1_ref_mc_p[0]->GetBinContent(h1_ref_mc_p[0]->FindBin(i_mult)) / (h1_ref_mc_p[0]->Integral(cent_ref[i_cent+1], cent_ref[i_cent])); */
  /*     cout<<h1_ref_mc_p[0]->GetBinContent(h1_ref_mc_p[0]->FindBin(i_mult)) / (h1_ref_mc_p[0]->Integral(cent_ref[i_cent+1], cent_ref[i_cent]))<<endl; */

  /*     ref_tpceff_avg += h1_ref_tpceff_p[0]->GetBinContent(h1_ref_tpceff_p[0]->FindBin(i_mult)) * h1_ref_mc_p[0]->GetBinContent(h1_ref_mc_p[0]->FindBin(i_mult)) / (h1_ref_mc_p[0]->Integral(cent_ref[i_cent+1]+1, cent_ref[i_cent])); */

  /*     ref_tpceff_err += pow(h1_ref_tpceff_p[0]->GetBinError(h1_ref_tpceff_p[0]->FindBin(i_mult)), 2) / pow((cent_ref[i_cent] - cent_ref[i_cent+1]) + 1, 2); */
  /*   } */
  /*   ref_avg_arr[i_cent] = ref_avg; ref_tpceff_avg_arr[i_cent] = ref_tpceff_avg; ref_tpceff_avg2_arr[i_cent] = ref_tpceff_avg2; ref_tpceff_err_arr[i_cent] = sqrt(ref_tpceff_err); */
  /*   if(isnan(ref_avg)) ref_avg_arr[i_cent] = 0; */
  /* } */
  /* //////////ONLY TO GET AVG MULT for each CENT FINISH/////////// */



  /* TFile *f_in = new TFile(Form("/Users/hosanko/playground/star/anal/Coll/isobar/ZrZrRuRu200_2018/charge/sys_unc/efficiency/net_proton/TPC/22062022/22062022_1/%s_%s_dca_%d_nhitsfit_%d.root", NamePPiK, NameRuZr, dca_cut, nhf_cut), "READ"); */
  TFile *f_in = new TFile(Form("/Users/hosanko/playground/star/anal/Coll/isobar/ZrZrRuRu200_2018/charge/sys_unc/efficiency/net_proton/TPC/27092022/27092022_1/%s_%s_dca_%d_nhitsfit_%d.root", NamePPiK, NameRuZr, dca_cut, nhf_cut), "READ");

  TH2D *h2_y_pt_dat[ncent][nphi];
  TH2D *h2_y_pt_dat_phiInt[ncent];
  /* TH2D *h2_eta_phi_dat[ncent][nphi]; */
  /* TH2D *h2_eta_phi_dat_phiInt[ncent]; */

  TH2D *h2_y_pt_mc[ncent][nphi];
  TH2D *h2_y_pt_mc_phiInt[ncent];
  /* TH2D *h2_eta_phi_mc[ncent][nphi]; */
  /* TH2D *h2_eta_phi_mc_phiInt[ncent]; */

  TH2D *h2_y_pt_eff[ncent][nphi];
  TH2D *h2_y_pt_eff_phiInt[ncent];
  /* TH2D *h2_eta_phi_eff[ncent][nphi]; */
  /* TH2D *h2_eta_phi_eff_phiInt[ncent]; */

  for(int i_cent = 0 ; i_cent < ncent ; i_cent++){
    for(int i_phi = 0 ; i_phi < nphi ; i_phi++){
      if(string(NamePPiK) == "Proton" || string(NamePPiK) == "Piplus" || string(NamePPiK) == "Kplus"){
	/* h2_y_pt_eff[i_cent][i_phi] = (TH2D*)f_in->Get(Form("h2_y_pt_eff_p_cent_%d", i_cent)); */
	/* h2_eta_phi_eff[i_cent][i_phi] = (TH2D*)f_in->Get(Form("h2_eta_phi_eff_p_cent_%d", i_cent)); */
	h2_y_pt_dat[i_cent][i_phi] = (TH2D*)f_in->Get(Form("h2_y_pt_p_cent_%d", i_cent)); h2_y_pt_dat[i_cent][i_phi]->RebinX(nxbin); h2_y_pt_dat[i_cent][i_phi]->RebinY(nybin);
	/* h2_eta_phi_dat[i_cent][i_phi] = (TH2D*)f_in->Get(Form("h2_eta_phi_p_cent_%d", i_cent)); h2_eta_phi_dat[i_cent][i_phi]->RebinX(nxbin); h2_eta_phi_dat[i_cent][i_phi]->RebinY(nybin); */
	h2_y_pt_mc[i_cent][i_phi] = (TH2D*)f_in->Get(Form("h2_y_pt_mc_p_cent_%d", i_cent)); h2_y_pt_mc[i_cent][i_phi]->RebinX(nxbin); h2_y_pt_mc[i_cent][i_phi]->RebinY(nybin);
	/* h2_eta_phi_mc[i_cent][i_phi] = (TH2D*)f_in->Get(Form("h2_eta_phi_mc_p_cent_%d", i_cent)); h2_eta_phi_mc[i_cent][i_phi]->RebinX(nxbin); h2_eta_phi_mc[i_cent][i_phi]->RebinY(nybin); */

	/* h2_y_pt_eff[i_cent][i_phi]->Sumw2(); */
	/* h2_eta_phi_eff[i_cent][i_phi]->Sumw2(); */
	h2_y_pt_eff[i_cent][i_phi] = (TH2D*)h2_y_pt_dat[i_cent][i_phi]->Clone(Form("h2_y_pt_eff_p_cent_%d", i_cent)); h2_y_pt_eff[i_cent][i_phi]->Divide(h2_y_pt_mc[i_cent][i_phi]);
	/* h2_eta_phi_eff[i_cent][i_phi] = (TH2D*)h2_eta_phi_dat[i_cent][i_phi]->Clone(Form("h2_eta_phi_eff_p_cent_%d", i_cent)); h2_eta_phi_eff[i_cent][i_phi]->Divide(h2_eta_phi_mc[i_cent][i_phi]); */
      }
      else if(string(NamePPiK) == "AntiProton" || string(NamePPiK) == "Piminus" || string(NamePPiK) == "Kminus"){
	/* h2_y_pt_eff[i_cent][i_phi] = (TH2D*)f_in->Get(Form("h2_y_pt_eff_m_cent_%d", i_cent)); */
	/* h2_eta_phi_eff[i_cent][i_phi] = (TH2D*)f_in->Get(Form("h2_eta_phi_eff_m_cent_%d", i_cent)); */
	h2_y_pt_dat[i_cent][i_phi] = (TH2D*)f_in->Get(Form("h2_y_pt_m_cent_%d", i_cent)); h2_y_pt_dat[i_cent][i_phi]->RebinX(nxbin); h2_y_pt_dat[i_cent][i_phi]->RebinY(nybin);
	/* h2_eta_phi_dat[i_cent][i_phi] = (TH2D*)f_in->Get(Form("h2_eta_phi_m_cent_%d", i_cent)); h2_eta_phi_dat[i_cent][i_phi]->RebinX(nxbin); h2_eta_phi_dat[i_cent][i_phi]->RebinY(nybin); */
	h2_y_pt_mc[i_cent][i_phi] = (TH2D*)f_in->Get(Form("h2_y_pt_mc_m_cent_%d", i_cent)); h2_y_pt_mc[i_cent][i_phi]->RebinX(nxbin); h2_y_pt_mc[i_cent][i_phi]->RebinY(nybin);
	/* h2_eta_phi_mc[i_cent][i_phi] = (TH2D*)f_in->Get(Form("h2_eta_phi_mc_m_cent_%d", i_cent)); h2_eta_phi_mc[i_cent][i_phi]->RebinX(nxbin); h2_eta_phi_mc[i_cent][i_phi]->RebinY(nybin); */

	h2_y_pt_eff[i_cent][i_phi] = (TH2D*)h2_y_pt_dat[i_cent][i_phi]->Clone(Form("h2_y_pt_eff_m_cent_%d", i_cent)); h2_y_pt_eff[i_cent][i_phi]->Divide(h2_y_pt_mc[i_cent][i_phi]);
	/* h2_eta_phi_eff[i_cent][i_phi] = (TH2D*)h2_eta_phi_dat[i_cent][i_phi]->Clone(Form("h2_eta_phi_eff_m_cent_%d", i_cent)); h2_eta_phi_eff[i_cent][i_phi]->Divide(h2_eta_phi_mc[i_cent][i_phi]); */
      }
    }

    /* h2_y_pt_eff_phiInt[i_cent] = new TH2D(Form("h2_y_pt_eff_cent_%d_phiInt", i_cent), Form("h2_y_pt_eff_cent_[%d, %d)_phiInt", cent_ref[i_cent+1], cent_ref[i_cent]), h2_y_pt_eff[0][0]->GetXaxis()->GetNbins(), h2_y_pt_eff[0][0]->GetXaxis()->GetXmin(), h2_y_pt_eff[0][0]->GetXaxis()->GetXmax(), h2_y_pt_eff[0][0]->GetYaxis()->GetNbins(), h2_y_pt_eff[0][0]->GetYaxis()->GetXmin(), h2_y_pt_eff[0][0]->GetYaxis()->GetXmax()); h2_y_pt_eff_phiInt[i_cent]->Sumw2(); */
    /* h2_eta_phi_eff_phiInt[i_cent] = new TH2D(Form("h2_eta_phi_eff_cent_%d_phiInt", i_cent), Form("h2_eta_phi_eff_cent_[%d, %d)_phiInt", cent_ref[i_cent+1], cent_ref[i_cent]), h2_eta_phi_eff[0][0]->GetXaxis()->GetNbins(), h2_eta_phi_eff[0][0]->GetXaxis()->GetXmin(), h2_eta_phi_eff[0][0]->GetXaxis()->GetXmax(), h2_eta_phi_eff[0][0]->GetYaxis()->GetNbins(), h2_eta_phi_eff[0][0]->GetYaxis()->GetXmin(), h2_eta_phi_eff[0][0]->GetYaxis()->GetXmax()); h2_eta_phi_eff_phiInt[i_cent]->Sumw2(); */

    h2_y_pt_dat_phiInt[i_cent] = new TH2D(Form("h2_y_pt_dat_cent_%d_phiInt", i_cent), Form("h2_y_pt_dat_cent_[%d, %d)_phiInt", cent_ref[i_cent+1], cent_ref[i_cent]), h2_y_pt_dat[0][0]->GetXaxis()->GetNbins(), h2_y_pt_dat[0][0]->GetXaxis()->GetXmin(), h2_y_pt_dat[0][0]->GetXaxis()->GetXmax(), h2_y_pt_dat[0][0]->GetYaxis()->GetNbins(), h2_y_pt_dat[0][0]->GetYaxis()->GetXmin(), h2_y_pt_dat[0][0]->GetYaxis()->GetXmax()); h2_y_pt_dat_phiInt[i_cent]->Sumw2();
    /* h2_eta_phi_dat_phiInt[i_cent] = new TH2D(Form("h2_eta_phi_dat_cent_%d_phiInt", i_cent), Form("h2_eta_phi_dat_cent_[%d, %d)_phiInt", cent_ref[i_cent+1], cent_ref[i_cent]), h2_eta_phi_dat[0][0]->GetXaxis()->GetNbins(), h2_eta_phi_dat[0][0]->GetXaxis()->GetXmin(), h2_eta_phi_dat[0][0]->GetXaxis()->GetXmax(), h2_eta_phi_dat[0][0]->GetYaxis()->GetNbins(), h2_eta_phi_dat[0][0]->GetYaxis()->GetXmin(), h2_eta_phi_dat[0][0]->GetYaxis()->GetXmax()); h2_eta_phi_dat_phiInt[i_cent]->Sumw2(); */

    h2_y_pt_mc_phiInt[i_cent] = new TH2D(Form("h2_y_pt_mc_cent_%d_phiInt", i_cent), Form("h2_y_pt_mc_cent_[%d, %d)_phiInt", cent_ref[i_cent+1], cent_ref[i_cent]), h2_y_pt_mc[0][0]->GetXaxis()->GetNbins(), h2_y_pt_mc[0][0]->GetXaxis()->GetXmin(), h2_y_pt_mc[0][0]->GetXaxis()->GetXmax(), h2_y_pt_mc[0][0]->GetYaxis()->GetNbins(), h2_y_pt_mc[0][0]->GetYaxis()->GetXmin(), h2_y_pt_mc[0][0]->GetYaxis()->GetXmax()); h2_y_pt_mc_phiInt[i_cent]->Sumw2();
    /* h2_eta_phi_mc_phiInt[i_cent] = new TH2D(Form("h2_eta_phi_mc_cent_%d_phiInt", i_cent), Form("h2_eta_phi_mc_cent_[%d, %d)_phiInt", cent_ref[i_cent+1], cent_ref[i_cent]), h2_eta_phi_mc[0][0]->GetXaxis()->GetNbins(), h2_eta_phi_mc[0][0]->GetXaxis()->GetXmin(), h2_eta_phi_mc[0][0]->GetXaxis()->GetXmax(), h2_eta_phi_mc[0][0]->GetYaxis()->GetNbins(), h2_eta_phi_mc[0][0]->GetYaxis()->GetXmin(), h2_eta_phi_mc[0][0]->GetYaxis()->GetXmax()); h2_eta_phi_mc_phiInt[i_cent]->Sumw2(); */

  }

  //Add
  for(int i_cent = 0 ; i_cent < ncent ; i_cent++){
    for(int i_phi = 0 ; i_phi < nphi ; i_phi++){
      /* h2_y_pt_eff_phiInt[i_cent]->Add(h2_y_pt_eff[i_cent][i_phi], 1./nphi); */
      /* h2_eta_phi_eff_phiInt[i_cent]->Add(h2_eta_phi_eff[i_cent][i_phi], 1./nphi); */
      /* h2_y_pt_eff_phiInt[i_cent]->Add(h2_y_pt_eff[i_cent][i_phi]); */
      /* h2_eta_phi_eff_phiInt[i_cent]->Add(h2_eta_phi_eff[i_cent][i_phi]); */

      /* if(h2_y_pt_dat[i_cent][i_phi]->GetEntries() > 0) */
      h2_y_pt_dat_phiInt[i_cent]->Add(h2_y_pt_dat[i_cent][i_phi]);
      /* if(h2_eta_phi_dat[i_cent][i_phi]->GetEntries() > 0) */
      /* h2_eta_phi_dat_phiInt[i_cent]->Add(h2_eta_phi_dat[i_cent][i_phi]); */
      /* if(h2_y_pt_mc[i_cent][i_phi]->GetEntries() > 0) */
      h2_y_pt_mc_phiInt[i_cent]->Add(h2_y_pt_mc[i_cent][i_phi]);
      /* if(h2_eta_phi_mc[i_cent][i_phi]->GetEntries() > 0) */
      /* h2_eta_phi_mc_phiInt[i_cent]->Add(h2_eta_phi_mc[i_cent][i_phi]); */
    }
    h2_y_pt_eff_phiInt[i_cent] = (TH2D*)h2_y_pt_dat_phiInt[i_cent]->Clone(Form("h2_y_pt_eff_cent_%d_phiInt", i_cent));
    /* h2_eta_phi_eff_phiInt[i_cent] = (TH2D*)h2_eta_phi_dat_phiInt[i_cent]->Clone(Form("h2_eta_phi_eff_cent_%d_phiInt", i_cent)); */
    h2_y_pt_eff_phiInt[i_cent]->Reset();
    h2_y_pt_eff_phiInt[i_cent]->Sumw2();
    /* h2_eta_phi_eff_phiInt[i_cent]->Reset(); */
    /* h2_eta_phi_eff_phiInt[i_cent]->Sumw2(); */
    h2_y_pt_eff_phiInt[i_cent]->Divide(h2_y_pt_dat_phiInt[i_cent], h2_y_pt_mc_phiInt[i_cent], 1., 1., "B");
    /* h2_eta_phi_eff_phiInt[i_cent]->Divide(h2_eta_phi_dat_phiInt[i_cent], h2_eta_phi_mc_phiInt[i_cent], 1., 1., "B"); */
  }

  //Fit [0]*exp(-1*pow([1]/x, [2]))
  const int ny = h2_y_pt_eff_phiInt[0]->GetXaxis()->GetNbins();
  TF1* f_y_pt_phiInt[ncent][ny];
  double p0[ncent][ny], p1[ncent][ny], p2[ncent][ny];
  double p0_err[ncent][ny],  p1_err[ncent][ny], p2_err[ncent][ny];
  TH1D *h1_y_pt_eff_phiInt[ncent][ny];

  //25062022(start)
  /* double ybin[21] = { */
  /*   -2., -1.8, -1.6, -1.4, -1.2, */
  /*   -1., -0.8, -0.6, -0.4, -0.2, */
  /*   0., 0.2, 0.4, 0.6, 0.8, */
  /*   1., 1.2, 1.4, 1.6, 1.8, */
  /*   2. */
  /* }; */
  double ybin[9] = {-2., -1.5, -1., -0.5, 0., 0.5, 1., 1.5, 2.};
  //25062022(finish)
  
  for(int i_cent = 0 ; i_cent < ncent ; i_cent++){
    for(int i_y = 0 ; i_y < ny ; i_y++){
      p0[i_cent][i_y] = 0.; p1[i_cent][i_y] = 0.; p2[i_cent][i_y] = 0.;
      p0_err[i_cent][i_y] = 0.; p1_err[i_cent][i_y] = 0.; p2_err[i_cent][i_y] = 0.;

      /* h1_y_pt_eff_phiInt[i_cent][i_y] = (TH1D*)h2_y_pt_eff_phiInt[i_cent]->ProjectionY(Form("h1_y_pt_eff_cent_%d_y_%d_phiInt", i_cent, i_y), i_y, i_y+1, "e"); */
      h1_y_pt_eff_phiInt[i_cent][i_y] = (TH1D*)h2_y_pt_eff_phiInt[i_cent]->ProjectionY(Form("h1_y_pt_eff_cent_%d_y_%d_phiInt", i_cent, i_y), i_y+1, i_y+1, "e");
      h1_y_pt_eff_phiInt[i_cent][i_y]->SetTitle(Form("h1_y_pt_eff_cent_[%d, %d)_y_[%1.1f, %1.1f)_phiInt", cent_ref[i_cent+1], cent_ref[i_cent], ybin[i_y], ybin[i_y+1]));

      f_y_pt_phiInt[i_cent][i_y] = new TF1(Form("f_y_pt_cent_%d_y_%d_phiInt", i_cent, i_y), "[0]*exp(-1*pow([1]/x, [2]))", 0, 5);
      /* f_y_pt_phiInt[i_cent][i_y]->SetParLimits(0, 0.1, 1); */
      /* f_y_pt_phiInt[i_cent][i_y]->SetParLimits(1, 0.1, 1); */
      /* f_y_pt_phiInt[i_cent][i_y]->SetParLimits(2, 0.1, 10); */

      h1_y_pt_eff_phiInt[i_cent][i_y]->Fit(f_y_pt_phiInt[i_cent][i_y], "R0 ");

      p0[i_cent][i_y] = f_y_pt_phiInt[i_cent][i_y]->GetParameter(0);
      p1[i_cent][i_y] = f_y_pt_phiInt[i_cent][i_y]->GetParameter(1);
      p2[i_cent][i_y] = f_y_pt_phiInt[i_cent][i_y]->GetParameter(2);
      p0_err[i_cent][i_y] = f_y_pt_phiInt[i_cent][i_y]->GetParError(0);
      p1_err[i_cent][i_y] = f_y_pt_phiInt[i_cent][i_y]->GetParError(1);
      p2_err[i_cent][i_y] = f_y_pt_phiInt[i_cent][i_y]->GetParError(2);
    }
  }  

  //Fit parameters plotted with respect to centrality
  TGraphErrors *gr_y_pt_eff_phiInt_p0[ny], *gr_y_pt_eff_phiInt_p1[ny], *gr_y_pt_eff_phiInt_p2[ny];
  double p0_cent[ncent], p1_cent[ncent], p2_cent[ncent];
  double p0_err_cent[ncent], p1_err_cent[ncent], p2_err_cent[ncent];

  TF1 *f1_p0_cent[ny], *f1_p1_cent[ny], *f1_p2_cent[ny];
  double p0_par0[ny], p0_par1[ny];
  double p1_par0[ny], p1_par1[ny];
  double p2_par0[ny], p2_par1[ny];
  
  for(int i_y = 0 ; i_y < ny ; i_y++){
    f1_p0_cent[i_y] = new TF1(Form("f1_p0_cent_y_%d", i_y), "pol1", 5, 500);//0 is at 0 so avoid!
    f1_p1_cent[i_y] = new TF1(Form("f1_p1_cent_y_%d", i_y), "pol1", 5, 500);
    f1_p2_cent[i_y] = new TF1(Form("f1_p2_cent_y_%d", i_y), "pol1", 5, 500);
    
    for(int i_cent = 0 ; i_cent < ncent ; i_cent++) {
      p0_cent[i_cent] = p0[i_cent][i_y]; p1_cent[i_cent] = p1[i_cent][i_y]; p2_cent[i_cent] = p2[i_cent][i_y];
      p0_err_cent[i_cent] = p0_err[i_cent][i_y]; p1_err_cent[i_cent] = p1_err[i_cent][i_y]; p2_err_cent[i_cent] = p2_err[i_cent][i_y];
    }
    gr_y_pt_eff_phiInt_p0[i_y] = new TGraphErrors(ncent, ref3_avg_arr, p0_cent, 0, p0_err_cent);
    gr_y_pt_eff_phiInt_p1[i_y] = new TGraphErrors(ncent, ref3_avg_arr, p1_cent, 0, p1_err_cent);
    gr_y_pt_eff_phiInt_p2[i_y] = new TGraphErrors(ncent, ref3_avg_arr, p2_cent, 0, p2_err_cent);
    gr_y_pt_eff_phiInt_p0[i_y]->SetMarkerStyle(8);
    gr_y_pt_eff_phiInt_p1[i_y]->SetMarkerStyle(8);
    gr_y_pt_eff_phiInt_p2[i_y]->SetMarkerStyle(8);
    gr_y_pt_eff_phiInt_p0[i_y]->SetTitle(Form("p0, y_[%1.1f, %1.1f)", ybin[i_y], ybin[i_y+1]));
    gr_y_pt_eff_phiInt_p1[i_y]->SetTitle(Form("p1, y_[%1.1f, %1.1f)", ybin[i_y], ybin[i_y+1]));
    gr_y_pt_eff_phiInt_p2[i_y]->SetTitle(Form("p2, y_[%1.1f, %1.1f)", ybin[i_y], ybin[i_y+1]));

    gr_y_pt_eff_phiInt_p0[i_y]->Fit(f1_p0_cent[i_y], "F R "); p0_par0[i_y] = f1_p0_cent[i_y]->GetParameter(0); p0_par1[i_y] = f1_p0_cent[i_y]->GetParameter(1);
    gr_y_pt_eff_phiInt_p1[i_y]->Fit(f1_p1_cent[i_y], "F R "); p1_par0[i_y] = f1_p1_cent[i_y]->GetParameter(0); p1_par1[i_y] = f1_p1_cent[i_y]->GetParameter(1);
    gr_y_pt_eff_phiInt_p2[i_y]->Fit(f1_p2_cent[i_y], "F R "); p2_par0[i_y] = f1_p2_cent[i_y]->GetParameter(0); p2_par1[i_y] = f1_p2_cent[i_y]->GetParameter(1);
    /* for(int i_cent = 0 ; i_cent < ncent ; i_cent++) cout<<i_y<<", "<<ref3_avg_arr[i_cent]<<", "<<p0_cent[i_cent]<<", "<<p0_err_cent[i_cent]<<endl;; */
    cout<<"["<<ybin[i_y]<<", "<<ybin[i_y+1]<<"). p0: "<<p0_par0[i_y]<<", "<<p0_par1[i_y]<<", p1: "<<p1_par0[i_y]<<", "<<p1_par1[i_y]<<", p2: "<<p2_par0[i_y]<<", "<<p2_par1[i_y]<<endl;
  }

  
  /* TCanvas *c_eta_phi_1 = new TCanvas("c_eta_phi_1", "c_eta_phi_1", 3000, 1800); */
  /* c_eta_phi_1->Divide(ncent,6); */
  /* for(int i_cent = 0 ; i_cent < ncent ; i_cent++){ */
  /*   for(int i_phi = 0 ; i_phi < nphi ; i_phi++){ */
  /*     /\* c_eta_phi_1->cd(i_phi + nphi*i_cent + 1); *\/ */
  /*     c_eta_phi_1->cd(i_cent + ncent*i_phi + 1); */
  /*     // h2_y_pt_eff[i_cent][i_phi]; */
  /*     h2_eta_phi_eff[i_cent][i_phi]->Draw("colz"); */
  /*   } */
  /* } */

  TCanvas *c_y_pt_1 = new TCanvas("c_y_pt_1", "c_y_pt_1", 3000, 1800);
  c_y_pt_1->Divide(ncent,6);
  for(int i_cent = 0 ; i_cent < ncent ; i_cent++){
    for(int i_phi = 0 ; i_phi < nphi ; i_phi++){
      /* c_y_pt_1->cd(i_phi + nphi*i_cent + 1); */
      c_y_pt_1->cd(i_cent + ncent*i_phi + 1);
      h2_y_pt_eff[i_cent][i_phi]->Draw("colz");
    }
  }

  /* TCanvas *c_eta_phi_phiInt_1 = new TCanvas("c_eta_phi_phiInt_1", "c_eta_phi_phiInt_1", 5000, 2000); */
  /* c_eta_phi_phiInt_1->Divide(5,2); */
  /* for(int i_cent = 0 ; i_cent < ncent ; i_cent++){ */
  /*   c_eta_phi_phiInt_1->cd(i_cent + 1); */
  /*   h2_eta_phi_eff_phiInt[i_cent]->Draw("colz"); */
  /* } */

  TCanvas *c_y_pt_phiInt_1 = new TCanvas("c_y_pt_phiInt_1", "c_y_pt_phiInt_1", 5000, 2000);
  c_y_pt_phiInt_1->Divide(5,2);
  for(int i_cent = 0 ; i_cent < ncent ; i_cent++){
    c_y_pt_phiInt_1->cd(i_cent + 1);
    h2_y_pt_eff_phiInt[i_cent]->Draw("colz");
  }

  TCanvas *c_y_pt_phiInt_2 = new TCanvas("c_y_pt_phiInt_2", "c_y_pt_phiInt_2", 5000, 2000);
  c_y_pt_phiInt_2->Divide(5,2);
  for(int i_y = 0 ; i_y < ny ; i_y++){
    for(int i_cent = 0 ; i_cent < ncent ; i_cent++){
      c_y_pt_phiInt_2->cd(i_cent + 1);
      h1_y_pt_eff_phiInt[i_cent][i_y]->Draw();
    }
    cout<<i_y<<", "<<ny<<endl;
    if(i_y == 0)c_y_pt_phiInt_2->Print(Form("output/TPC/c_y_pt_phiInt_2_%s_%s_dca_%d_nhitsfit_%d.pdf(", NamePPiK, NameRuZr, dca_cut, nhf_cut), "pdf");
    else if(i_y < ny-1) c_y_pt_phiInt_2->Print(Form("output/TPC/c_y_pt_phiInt_2_%s_%s_dca_%d_nhitsfit_%d.pdf", NamePPiK, NameRuZr, dca_cut, nhf_cut), "pdf");
    else c_y_pt_phiInt_2->Print(Form("output/TPC/c_y_pt_phiInt_2_%s_%s_dca_%d_nhitsfit_%d.pdf)", NamePPiK, NameRuZr, dca_cut, nhf_cut), "pdf");
  }

  TCanvas *c_y_pt_p0_cent_1 = new TCanvas("c_y_pt_p0_cent_1", "c_y_pt_p0_cent_1", 2000, 1000);
  c_y_pt_p0_cent_1->Divide(4,2);
  for(int i_y = 0 ; i_y < ny ; i_y++){
    c_y_pt_p0_cent_1->cd(i_y+1);
    gr_y_pt_eff_phiInt_p0[i_y]->Draw("AP");
  }
  TCanvas *c_y_pt_p1_cent_1 = new TCanvas("c_y_pt_p1_cent_1", "c_y_pt_p1_cent_1", 2000, 1000);
  c_y_pt_p1_cent_1->Divide(4,2);
  for(int i_y = 0 ; i_y < ny ; i_y++){
    c_y_pt_p1_cent_1->cd(i_y+1);
    gr_y_pt_eff_phiInt_p1[i_y]->Draw("AP");
  }
  TCanvas *c_y_pt_p2_cent_1 = new TCanvas("c_y_pt_p2_cent_1", "c_y_pt_p2_cent_1", 2000, 1000);
  c_y_pt_p2_cent_1->Divide(4,2);
  for(int i_y = 0 ; i_y < ny ; i_y++){
    c_y_pt_p2_cent_1->cd(i_y+1);
    gr_y_pt_eff_phiInt_p2[i_y]->Draw("AP");
  }

  c_y_pt_p0_cent_1->Print(Form("output/TPC/c_y_pt_p0_cent_1_%s_%s_dca_%d_nhitsfit_%d.pdf", NamePPiK, NameRuZr, dca_cut, nhf_cut));
  c_y_pt_p1_cent_1->Print(Form("output/TPC/c_y_pt_p1_cent_1_%s_%s_dca_%d_nhitsfit_%d.pdf", NamePPiK, NameRuZr, dca_cut, nhf_cut));
  c_y_pt_p2_cent_1->Print(Form("output/TPC/c_y_pt_p2_cent_1_%s_%s_dca_%d_nhitsfit_%d.pdf", NamePPiK, NameRuZr, dca_cut, nhf_cut));
  
  ofstream myfile;
  myfile.open(Form("output/TPC/file/eff_pt_dep_cent_fit_ybin_%s_%s_dca_%d_nhitsfit_%d.txt", NamePPiK, NameRuZr, dca_cut, nhf_cut));
  myfile<<"ybinlow\tybinhi\tp0_par0\tp0_par1\tp1_par0\tp1_par1\tp2_par0\tp2_par1"<<endl;
  for(int i_y = 0 ; i_y < ny ; i_y++){
    /* if(i_y>6 && i_y<13){ */
    myfile<<ybin[i_y]<<"\t"<<ybin[i_y+1]<<"\t"<<p0_par0[i_y]<<"\t"<<p0_par1[i_y]<<"\t"<<p1_par0[i_y]<<"\t"<<p1_par1[i_y]<<"\t"<<p2_par0[i_y]<<"\t"<<p2_par1[i_y]<<endl;
    /* } */
  }
  myfile.close();

  //25062022(start)
  //What I want: y: -0.5 ~ 0.5 just one bin!
  TF1* f_y_pt_one_lopt[ncent], *f_y_pt_one_hipt[ncent];// *f_y_pt_one_merg[ncent];
  TF1* f_y_pt_one_lopt_draw[ncent], *f_y_pt_one_hipt_draw[ncent];

  double p0_one_lopt[ncent], p1_one_lopt[ncent], p2_one_lopt[ncent];
  double p0_one_lopt_err[ncent],  p1_one_lopt_err[ncent], p2_one_lopt_err[ncent];
  double p0_one_hipt[ncent], p1_one_hipt[ncent];//, p2_one_hipt[ncent];
  double p0_one_hipt_err[ncent],  p1_one_hipt_err[ncent];//, p2_one_hipt_err[ncent];

  /* double p0_one_merg[ncent], p1_one_merg[ncent], p2_one_merg[ncent], p3_one_merg[ncent], p4_one_merg[ncent], p5_one_merg[ncent]; */
  /* double p0_one_merg_err[ncent], p1_one_merg_err[ncent], p2_one_merg_err[ncent], p3_one_merg_err[ncent], p4_one_merg_err[ncent], p5_one_merg_err[ncent]; */
  /* TH1D *h1_y_pt_dat_one_old[ncent], *h1_y_pt_mc_one_old[ncent];; */
  TH1D *h1_y_pt_dat_one[ncent], *h1_y_pt_mc_one[ncent];;
  /* TH1D *h1_y_pt_eff_one[ncent]; */
  /* TEfficiency *h1_y_pt_eff_one[ncent]; */
  TH1D *h1_y_pt_eff_one[ncent];
  for(int i_cent = 0 ; i_cent < ncent ; i_cent++){
    /* h1_y_pt_dat_one_old[i_cent] = (TH1D*)h2_y_pt_dat_phiInt[i_cent]->ProjectionY(Form("h1_y_pt_dat_one_cent_%d", i_cent), 3+1, 4+1, "e"); */
    /* h1_y_pt_dat_one_old[i_cent]->SetTitle(Form("h1_y_pt_dat_cent_[%d, %d)_y_[%1.1f, %1.1f)", cent_ref[i_cent+1], cent_ref[i_cent], ybin[3], ybin[4+1])); */
    /* h1_y_pt_dat_one_old[i_cent]->Sumw2(); */
    /* h1_y_pt_mc_one_old[i_cent] = (TH1D*)h2_y_pt_mc_phiInt[i_cent]->ProjectionY(Form("h1_y_pt_mc_one_cent_%d", i_cent), 3+1, 4+1, "e"); */
    /* h1_y_pt_mc_one_old[i_cent]->SetTitle(Form("h1_y_pt_mc_cent_[%d, %d)_y_[%1.1f, %1.1f)", cent_ref[i_cent+1], cent_ref[i_cent], ybin[3], ybin[4+1])); */
    /* h1_y_pt_mc_one_old[i_cent]->Sumw2(); */

    h1_y_pt_dat_one[i_cent] = (TH1D*)h2_y_pt_dat_phiInt[i_cent]->ProjectionY(Form("h1_y_pt_dat_one_cent_%d", i_cent), 3+1, 4+1, "e");
    h1_y_pt_dat_one[i_cent]->SetTitle(Form("h1_y_pt_dat_cent_[%d, %d)_y_[%1.1f, %1.1f)", cent_ref[i_cent+1], cent_ref[i_cent], ybin[3], ybin[4+1]));
    h1_y_pt_dat_one[i_cent]->Sumw2();
    h1_y_pt_mc_one[i_cent] = (TH1D*)h2_y_pt_mc_phiInt[i_cent]->ProjectionY(Form("h1_y_pt_mc_one_cent_%d", i_cent), 3+1, 4+1, "e");
    h1_y_pt_mc_one[i_cent]->SetTitle(Form("h1_y_pt_mc_cent_[%d, %d)_y_[%1.1f, %1.1f)", cent_ref[i_cent+1], cent_ref[i_cent], ybin[3], ybin[4+1]));
    h1_y_pt_mc_one[i_cent]->Sumw2();

    /* h1_y_pt_dat_one[i_cent] = new TH1D(Form("h1_y_pt_dat_one_%d", i_cent), Form("h1_y_pt_dat_cent_[%d, %d)_y_[%1.1f, %1.1f)", cent_ref[i_cent+1], cent_ref[i_cent], ybin[3], ybin[4+1]), h1_y_pt_dat_one_old[i_cent]->GetNbinsX()*(2./(h1_y_pt_dat_one_old[i_cent]->GetXaxis()->GetXmax() - h1_y_pt_dat_one_old[i_cent]->GetXaxis()->GetXmin())), 0, 2); */
    /* h1_y_pt_mc_one[i_cent] = new TH1D(Form("h1_y_pt_mc_one_%d", i_cent), Form("h1_y_pt_mc_cent_[%d, %d)_y_[%1.1f, %1.1f)", cent_ref[i_cent+1], cent_ref[i_cent], ybin[3], ybin[4+1]), h1_y_pt_mc_one_old[i_cent]->GetNbinsX()*(2./(h1_y_pt_mc_one_old[i_cent]->GetXaxis()->GetXmax() - h1_y_pt_mc_one_old[i_cent]->GetXaxis()->GetXmin())), 0, 2); */

    /* for(int i_bin = 0 ; i_bin < h1_y_pt_dat_one[i_cent]->GetNbinsX() ; i_bin++){ */
    /*   h1_y_pt_dat_one[i_cent]->SetBinContent(i_bin+1, h1_y_pt_dat_one_old[i_cent]->GetBinContent(i_bin+1)); */
    /* } */
    /* for(int i_bin = 0 ; i_bin < h1_y_pt_mc_one[i_cent]->GetNbinsX() ; i_bin++){ */
    /*   h1_y_pt_mc_one[i_cent]->SetBinContent(i_bin+1, h1_y_pt_mc_one_old[i_cent]->GetBinContent(i_bin+1)); */
    /* } */
    
    /*   TFile *f_out = new TFile("hey.root", "RECREATE"); */
    /*   f_out->cd(); */
    /*   for(int i_cent = 0 ; i_cent < ncent ; i_cent++){ */
    /*     h1_y_pt_dat_one[i_cent]->Write(); */
    /*     h1_y_pt_mc_one[i_cent]->Write(); */
    /*   } */
    /*   f_out->Write(); */
    /*   f_out->Close(); */
    /* } */

    /* h1_y_pt_eff_one[i_cent] = new TH1D(Form("h1_y_pt_eff_one_cent_%d", i_cent), Form("h1_y_pt_eff_cent_[%d, %d)_y_[%1.1f, %1.1f)", cent_ref[i_cent+1], cent_ref[i_cent], ybin[3], ybin[4+1]), h1_y_pt_dat_one[i_cent][3]->GetXaxis()->GetNbins(), h1_y_pt_dat_one[i_cent][3]->GetXaxis()->GetXmin(), h1_y_pt_dat_one[i_cent][3]->GetXaxis()->GetXmax()); */
    /* h1_y_pt_eff_one[i_cent]->Divide */
    h1_y_pt_eff_one[i_cent] = 0;
    h1_y_pt_eff_one[i_cent] = new TH1D(Form("h1_y_pt_eff_one_%d", i_cent), Form("h1_y_pt_eff_cent_[%d, %d)_y_[%1.1f, %1.1f)", cent_ref[i_cent+1], cent_ref[i_cent], ybin[3], ybin[4+1]), h1_y_pt_dat_one[i_cent]->GetXaxis()->GetNbins(), h1_y_pt_dat_one[i_cent]->GetXaxis()->GetXmin(), h1_y_pt_dat_one[i_cent]->GetXaxis()->GetXmax());
    //04082022(start)
    h1_y_pt_dat_one[i_cent]->ClearUnderflowAndOverflow(); h1_y_pt_mc_one[i_cent]->ClearUnderflowAndOverflow();//Sumw2 is also cleared, since there is no more content in the bins.
    h1_y_pt_dat_one[i_cent]->Sumw2(); h1_y_pt_mc_one[i_cent]->Sumw2();
    //04082022(finish)
    /* if(TEfficiency::CheckConsistency(*h1_y_pt_dat_one[i_cent], *h1_y_pt_mc_one[i_cent])) */
    /*   { */
    /* 	h1_y_pt_eff_one[i_cent] = new TEfficiency(*h1_y_pt_dat_one[i_cent], *h1_y_pt_mc_one[i_cent]); */
    /* 	h1_y_pt_eff_one[i_cent]->SetTitle(Form("h1_y_pt_eff_cent_[%d, %d)_y_[%1.1f, %1.1f)", cent_ref[i_cent+1], cent_ref[i_cent], ybin[3], ybin[4+1])); */
    /*   } */
    /* h1_y_pt_eff_one[i_cent]->SetTotalHistogram(*h1_y_pt_mc_one[i_cent], "f"); */
    /* h1_y_pt_eff_one[i_cent]->SetPassedHistogram(*h1_y_pt_dat_one[i_cent], "f"); */

    h1_y_pt_eff_one[i_cent]->Divide(h1_y_pt_dat_one[i_cent], h1_y_pt_mc_one[i_cent], 1, 1, "B");
    
    /* /\* h1_y_pt_eff_one[i_cent] = (TH1D*)h1_y_pt_eff_phiInt[i_cent][3]->Clone(Form("h1_y_pt_eff_one_cent_%d", i_cent)); *\/ */
    /* /\* h1_y_pt_eff_one[i_cent]->Add(h1_y_pt_eff_phiInt[i_cent][4]); *\/ */
    /* /\* h1_y_pt_eff_one[i_cent]->Scale(2.); *\/ */
    /* /\* h1_y_pt_eff_one[i_cent]->SetTitle(Form("h1_y_pt_eff_cent_[%d, %d)_y_[%1.1f, %1.1f)", cent_ref[i_cent+1], cent_ref[i_cent], ybin[3], ybin[4+1])); *\/ */
    /* h1_y_pt_eff_phiInt[i_cent][3]->SetBit(TH1::kIsAverage); */
    /* h1_y_pt_eff_phiInt[i_cent][3]->SetBit(TH1::kIsAverage); */
    /* h1_y_pt_eff_one[i_cent] = new TH1D(Form("h1_y_pt_eff_one_cent_%d", i_cent), Form("h1_y_pt_eff_cent_[%d, %d)_y_[%1.1f, %1.1f)", cent_ref[i_cent+1], cent_ref[i_cent], ybin[3], ybin[4+1]), h1_y_pt_eff_phiInt[i_cent][3]->GetXaxis()->GetNbins(), h1_y_pt_eff_phiInt[i_cent][3]->GetXaxis()->GetXmin(), h1_y_pt_eff_phiInt[i_cent][3]->GetXaxis()->GetXmax()); */
    /* h1_y_pt_eff_one[i_cent]->SetBit(TH1::kIsAverage); */
    /* h1_y_pt_eff_one[i_cent]->Add(h1_y_pt_eff_phiInt[i_cent][3], h1_y_pt_eff_phiInt[i_cent][4], 1., 1.); */

    f_y_pt_one_lopt[i_cent] = new TF1(Form("f_y_pt_one_lopt_cent_%d", i_cent), "pol2", 0.4, 0.8);
    f_y_pt_one_hipt[i_cent] = new TF1(Form("f_y_pt_one_hipt_cent_%d", i_cent), "pol1", 0.8, 2.0);
    /* f_y_pt_one_merg[i_cent] = new TF1(Form("f_y_pt_one_merg_cent_%d", i_cent), "pol2(0) + pol1(3)", 0.25, 2.0); */
    /* f_y_pt_one_lopt_draw[i_cent] = new TF1(Form("f_y_pt_one_lopt_draw_cent_%d", i_cent), "[0]*exp(-1*pow([1]/x, [2]))", 0, 0.8); f_y_pt_one_lopt_draw[i_cent]->SetLineColor(2); */
    /* f_y_pt_one_hipt_draw[i_cent] = new TF1(Form("f_y_pt_one_hipt_draw_cent_%d", i_cent), "[0]*exp(-1*pow([1]/x, [2]))", 0.8, 2.0); f_y_pt_one_hipt_draw[i_cent]->SetLineColor(4); */
    f_y_pt_one_lopt_draw[i_cent] = new TF1(Form("f_y_pt_one_lopt_draw_cent_%d", i_cent), "pol2", 0, 0.8); f_y_pt_one_lopt_draw[i_cent]->SetLineColor(2);
    f_y_pt_one_hipt_draw[i_cent] = new TF1(Form("f_y_pt_one_hipt_draw_cent_%d", i_cent), "pol1", 0.8, 2.0); f_y_pt_one_hipt_draw[i_cent]->SetLineColor(4);
    /* f_y_pt_one_lopt[i_cent]->SetParLimits(0, 0.5, 1); */
    /* f_y_pt_one_lopt[i_cent]->SetParLimits(1, 0.1, 1); */
    /* f_y_pt_one_lopt[i_cent]->SetParLimits(2, 0, 10); */
    /* f_y_pt_one_hipt[i_cent]->SetParLimits(0, 0.5, 1); */
    /* f_y_pt_one_hipt[i_cent]->SetParLimits(1, 0.1, 1); */
    /* f_y_pt_one_hipt[i_cent]->SetParLimits(2, 0, 10); */

    h1_y_pt_eff_one[i_cent]->Fit(f_y_pt_one_lopt[i_cent], "R0 ");
    h1_y_pt_eff_one[i_cent]->Fit(f_y_pt_one_hipt[i_cent], "R0 +");

    /* p0_one_merg[i_cent] = f_y_pt_one_lopt[i_cent]->GetParameter(0); */
    /* p1_one_merg[i_cent] = f_y_pt_one_lopt[i_cent]->GetParameter(1); */
    /* p2_one_merg[i_cent] = f_y_pt_one_lopt[i_cent]->GetParameter(2); */
    /* p3_one_merg[i_cent] = f_y_pt_one_hipt[i_cent]->GetParameter(0); */
    /* p4_one_merg[i_cent] = f_y_pt_one_hipt[i_cent]->GetParameter(1); */
    /* /\* p5_one_merg[i_cent] = f_y_pt_one_hipt[i_cent]->GetParameter(2); *\/ */

    /* f_y_pt_one_merg[i_cent]->SetParameter(0, p0_one_merg[i_cent]); */
    /* f_y_pt_one_merg[i_cent]->SetParameter(1, p1_one_merg[i_cent]); */
    /* f_y_pt_one_merg[i_cent]->SetParameter(2, p2_one_merg[i_cent]); */
    /* f_y_pt_one_merg[i_cent]->SetParameter(3, p3_one_merg[i_cent]); */
    /* f_y_pt_one_merg[i_cent]->SetParameter(4, p4_one_merg[i_cent]); */
    /* /\* f_y_pt_one_merg[i_cent]->SetParameter(5, p5_one_merg[i_cent]); *\/ */

    /* h1_y_pt_eff_one[i_cent]->Fit(f_y_pt_one_merg[i_cent], "R +"); */

    p0_one_lopt[i_cent] = f_y_pt_one_lopt[i_cent]->GetParameter(0);
    p1_one_lopt[i_cent] = f_y_pt_one_lopt[i_cent]->GetParameter(1);
    p2_one_lopt[i_cent] = f_y_pt_one_lopt[i_cent]->GetParameter(2);
    p0_one_lopt_err[i_cent] = f_y_pt_one_lopt[i_cent]->GetParError(0);
    p1_one_lopt_err[i_cent] = f_y_pt_one_lopt[i_cent]->GetParError(1);
    p2_one_lopt_err[i_cent] = f_y_pt_one_lopt[i_cent]->GetParError(2);

    p0_one_hipt[i_cent] = f_y_pt_one_hipt[i_cent]->GetParameter(0);
    p1_one_hipt[i_cent] = f_y_pt_one_hipt[i_cent]->GetParameter(1);
    /* p2_one_hipt[i_cent] = f_y_pt_one_hipt[i_cent]->GetParameter(2); */
    p0_one_hipt_err[i_cent] = f_y_pt_one_hipt[i_cent]->GetParError(0);
    p1_one_hipt_err[i_cent] = f_y_pt_one_hipt[i_cent]->GetParError(1);
    /* p2_one_hipt_err[i_cent] = f_y_pt_one_hipt[i_cent]->GetParError(2); */

    f_y_pt_one_lopt_draw[i_cent]->SetParameter(0, f_y_pt_one_lopt[i_cent]->GetParameter(0));
    f_y_pt_one_lopt_draw[i_cent]->SetParameter(1, f_y_pt_one_lopt[i_cent]->GetParameter(1));
    f_y_pt_one_lopt_draw[i_cent]->SetParameter(2, f_y_pt_one_lopt[i_cent]->GetParameter(2));
    f_y_pt_one_hipt_draw[i_cent]->SetParameter(0, f_y_pt_one_hipt[i_cent]->GetParameter(0));
    f_y_pt_one_hipt_draw[i_cent]->SetParameter(1, f_y_pt_one_hipt[i_cent]->GetParameter(1));
    /* f_y_pt_one_hipt_draw[i_cent]->SetParameter(2, f_y_pt_one_hipt[i_cent]->GetParameter(2)); */

  }

  //Fit parameters plotted with respect to centrality
  TGraphErrors *gr_y_pt_eff_one_lopt_p0, *gr_y_pt_eff_one_lopt_p1, *gr_y_pt_eff_one_lopt_p2;
  double p0_one_lopt_cent[ncent], p1_one_lopt_cent[ncent], p2_one_lopt_cent[ncent];
  double p0_one_lopt_err_cent[ncent], p1_one_lopt_err_cent[ncent], p2_one_lopt_err_cent[ncent];

  TGraphErrors *gr_y_pt_eff_one_hipt_p0, *gr_y_pt_eff_one_hipt_p1;//, *gr_y_pt_eff_one_hipt_p2;
  double p0_one_hipt_cent[ncent], p1_one_hipt_cent[ncent];//, p2_one_hipt_cent[ncent];
  double p0_one_hipt_err_cent[ncent], p1_one_hipt_err_cent[ncent];//, p2_one_hipt_err_cent[ncent];

  TF1 *f1_p0_one_lopt_cent, *f1_p1_one_lopt_cent, *f1_p2_one_lopt_cent;
  TF1 *f1_p0_one_lopt_cent_draw, *f1_p1_one_lopt_cent_draw, *f1_p2_one_lopt_cent_draw;

  TF1 *f1_p0_one_hipt_cent, *f1_p1_one_hipt_cent;//, *f1_p2_one_hipt_cent;
  TF1 *f1_p0_one_hipt_cent_draw, *f1_p1_one_hipt_cent_draw;//, *f1_p2_one_hipt_cent_draw;

  double p0_one_lopt_par0, p0_one_lopt_par1;
  double p1_one_lopt_par0, p1_one_lopt_par1;
  double p2_one_lopt_par0, p2_one_lopt_par1;

  double p0_one_hipt_par0, p0_one_hipt_par1;
  double p1_one_hipt_par0, p1_one_hipt_par1;
  /* double p2_one_hipt_par0, p2_one_hipt_par1; */

  f1_p0_one_lopt_cent = new TF1("f1_p0_one_lopt_cent", "pol1", 5, 500);
  f1_p1_one_lopt_cent = new TF1("f1_p1_one_lopt_cent", "pol1", 5, 500);
  f1_p2_one_lopt_cent = new TF1("f1_p2_one_lopt_cent", "pol1", 5, 500);
  f1_p0_one_lopt_cent_draw = new TF1("f1_p0_one_lopt_cent_draw", "pol1", 5, 500); f1_p0_one_lopt_cent_draw->SetLineColor(4);
  f1_p1_one_lopt_cent_draw = new TF1("f1_p1_one_lopt_cent_draw", "pol1", 5, 500); f1_p1_one_lopt_cent_draw->SetLineColor(4);
  f1_p2_one_lopt_cent_draw = new TF1("f1_p2_one_lopt_cent_draw", "pol1", 5, 500); f1_p2_one_lopt_cent_draw->SetLineColor(4);

  f1_p0_one_hipt_cent = new TF1("f1_p0_one_hipt_cent", "pol1", 5, 500);
  f1_p1_one_hipt_cent = new TF1("f1_p1_one_hipt_cent", "pol1", 5, 500);
  /* f1_p2_one_hipt_cent = new TF1("f1_p2_one_hipt_cent", "pol1", 5, 500); */
  f1_p0_one_hipt_cent_draw = new TF1("f1_p0_one_hipt_cent_draw", "pol1", 5, 500); f1_p0_one_hipt_cent_draw->SetLineColor(4);
  f1_p1_one_hipt_cent_draw = new TF1("f1_p1_one_hipt_cent_draw", "pol1", 5, 500); f1_p1_one_hipt_cent_draw->SetLineColor(4);
  /* f1_p2_one_hipt_cent_draw = new TF1("f1_p2_one_hipt_cent_draw", "pol1", 5, 500); f1_p2_one_hipt_cent_draw->SetLineColor(4); */

  for(int i_cent = 0 ; i_cent < ncent ; i_cent++) {
    p0_one_lopt_cent[i_cent] = p0_one_lopt[i_cent]; p1_one_lopt_cent[i_cent] = p1_one_lopt[i_cent]; p2_one_lopt_cent[i_cent] = p2_one_lopt[i_cent];
    p0_one_lopt_err_cent[i_cent] = p0_one_lopt_err[i_cent]; p1_one_lopt_err_cent[i_cent] = p1_one_lopt_err[i_cent]; p2_one_lopt_err_cent[i_cent] = p2_one_lopt_err[i_cent];
    p0_one_hipt_cent[i_cent] = p0_one_hipt[i_cent]; p1_one_hipt_cent[i_cent] = p1_one_hipt[i_cent]; // p2_one_hipt_cent[i_cent] = p2_one_hipt[i_cent];
    p0_one_hipt_err_cent[i_cent] = p0_one_hipt_err[i_cent]; p1_one_hipt_err_cent[i_cent] = p1_one_hipt_err[i_cent]; // p2_one_hipt_err_cent[i_cent] = p2_one_hipt_err[i_cent];
  }
  //Just for better drawing, nothing else (start)
    p0_one_lopt_cent[0] = p0_one_lopt[1]; p1_one_lopt_cent[0] = p1_one_lopt[1]; p2_one_lopt_cent[0] = p2_one_lopt[1];
    p0_one_lopt_err_cent[0] = p0_one_lopt_err[1]; p1_one_lopt_err_cent[0] = p1_one_lopt_err[1]; p2_one_lopt_err_cent[0] = p2_one_lopt_err[1];
    p0_one_hipt_cent[0] = p0_one_hipt[1]; p1_one_hipt_cent[0] = p1_one_hipt[1]; // p2_one_hipt_cent[0] = p2_one_hipt[1];
    p0_one_hipt_err_cent[0] = p0_one_hipt_err[1]; p1_one_hipt_err_cent[0] = p1_one_hipt_err[1]; // p2_one_hipt_err_cent[0] = p2_one_hipt_err[1];
  //Just for better drawing, nothing else (finish)
  
  gr_y_pt_eff_one_lopt_p0 = new TGraphErrors(ncent, ref3_avg_arr, p0_one_lopt_cent, 0, p0_one_lopt_err_cent);
  gr_y_pt_eff_one_lopt_p1 = new TGraphErrors(ncent, ref3_avg_arr, p1_one_lopt_cent, 0, p1_one_lopt_err_cent);
  gr_y_pt_eff_one_lopt_p2 = new TGraphErrors(ncent, ref3_avg_arr, p2_one_lopt_cent, 0, p2_one_lopt_err_cent);
  gr_y_pt_eff_one_lopt_p0->SetMarkerStyle(8);
  gr_y_pt_eff_one_lopt_p1->SetMarkerStyle(8);
  gr_y_pt_eff_one_lopt_p2->SetMarkerStyle(8);
  gr_y_pt_eff_one_lopt_p0->SetTitle(Form("p0, y: [%1.1f, %1.1f), 0.4 #leq p_{T} < 0.8 GeV/c", ybin[3], ybin[4+1]));
  gr_y_pt_eff_one_lopt_p1->SetTitle(Form("p1, y: [%1.1f, %1.1f), 0.4 #leq p_{T} < 0.8 GeV/c", ybin[3], ybin[4+1]));
  gr_y_pt_eff_one_lopt_p2->SetTitle(Form("p2, y: [%1.1f, %1.1f), 0.4 #leq p_{T} < 0.8 GeV/c", ybin[3], ybin[4+1]));
  gr_y_pt_eff_one_lopt_p0->GetXaxis()->SetTitle("RefMult3");
  gr_y_pt_eff_one_lopt_p1->GetXaxis()->SetTitle("RefMult3");
  gr_y_pt_eff_one_lopt_p2->GetXaxis()->SetTitle("RefMult3");
  gr_y_pt_eff_one_lopt_p0->GetXaxis()->SetRangeUser(-100, 600);
  gr_y_pt_eff_one_lopt_p1->GetXaxis()->SetRangeUser(-100, 600);
  gr_y_pt_eff_one_lopt_p2->GetXaxis()->SetRangeUser(-100, 600);

  gr_y_pt_eff_one_hipt_p0 = new TGraphErrors(ncent, ref3_avg_arr, p0_one_hipt_cent, 0, p0_one_hipt_err_cent);
  gr_y_pt_eff_one_hipt_p1 = new TGraphErrors(ncent, ref3_avg_arr, p1_one_hipt_cent, 0, p1_one_hipt_err_cent);
  /* gr_y_pt_eff_one_hipt_p2 = new TGraphErrors(ncent, ref3_avg_arr, p2_one_hipt_cent, 0, p2_one_hipt_err_cent); */
  gr_y_pt_eff_one_hipt_p0->SetMarkerStyle(8);
  gr_y_pt_eff_one_hipt_p1->SetMarkerStyle(8);
  /* gr_y_pt_eff_one_hipt_p2->SetMarkerStyle(8); */
  gr_y_pt_eff_one_hipt_p0->SetTitle(Form("p0, y: [%1.1f, %1.1f), 0.8 #leq p_{T} < 2.0 GeV/c", ybin[3], ybin[4+1]));
  gr_y_pt_eff_one_hipt_p1->SetTitle(Form("p1, y: [%1.1f, %1.1f), 0.8 #leq p_{T} < 2.0 GeV/c", ybin[3], ybin[4+1]));
  /* gr_y_pt_eff_one_hipt_p2->SetTitle(Form("p2, y: [%1.1f, %1.1f)", ybin[3], ybin[4+1])); */
  gr_y_pt_eff_one_hipt_p0->GetXaxis()->SetTitle("RefMult3");
  gr_y_pt_eff_one_hipt_p1->GetXaxis()->SetTitle("RefMult3");
  gr_y_pt_eff_one_hipt_p0->GetXaxis()->SetRangeUser(-100, 600);
  gr_y_pt_eff_one_hipt_p1->GetXaxis()->SetRangeUser(-100, 600);

  gr_y_pt_eff_one_lopt_p0->Fit(f1_p0_one_lopt_cent, "FR"); //p0_one_lopt_par0 = f1_p0_one_lopt_cent->GetParameter(0); p0_one_lopt_par1 = f1_p0_one_lopt_cent->GetParameter(1);
  gr_y_pt_eff_one_lopt_p1->Fit(f1_p1_one_lopt_cent, "FR"); //p1_one_lopt_par0 = f1_p1_one_lopt_cent->GetParameter(0); p1_one_lopt_par1 = f1_p1_one_lopt_cent->GetParameter(1);
  gr_y_pt_eff_one_lopt_p2->Fit(f1_p2_one_lopt_cent, "FR"); //p2_one_lopt_par0 = f1_p2_one_lopt_cent->GetParameter(0); p2_one_lopt_par1 = f1_p2_one_lopt_cent->GetParameter(1);

  gr_y_pt_eff_one_hipt_p0->Fit(f1_p0_one_hipt_cent, "FR"); //p0_one_hipt_par0 = f1_p0_one_hipt_cent->GetParameter(0); p0_one_hipt_par1 = f1_p0_one_hipt_cent->GetParameter(1);
  gr_y_pt_eff_one_hipt_p1->Fit(f1_p1_one_hipt_cent, "FR"); //p1_one_hipt_par0 = f1_p1_one_hipt_cent->GetParameter(0); p1_one_hipt_par1 = f1_p1_one_hipt_cent->GetParameter(1);
  /* gr_y_pt_eff_one_hipt_p2->Fit(f1_p2_one_hipt_cent, "FR"); //p2_one_hipt_par0 = f1_p2_one_hipt_cent->GetParameter(0); p2_one_hipt_par1 = f1_p2_one_hipt_cent->GetParameter(1); */

  /* //11082022(start): hand fitting for bad children */
  /* if(string(NamePPiK) == "AntiProton" && string(NameRuZr) == "Ru" && dca_cut == 10 && nhf_cut == 15){ */
  /*   cout<<"\n\n ####### HAND FITTING FOR BAD CHILDREN ###### "<<endl; */
  /*   f1_p2_one_lopt_cent->SetParameter(0, 10.1087); f1_p2_one_lopt_cent->SetParError(0, 11.6432); */
  /*   f1_p2_one_lopt_cent->SetParameter(1, -0.000139251); f1_p2_one_lopt_cent->SetParError(1, 0.0339505); */
  /* } */
  /* if(string(NamePPiK) == "AntiProton" && string(NameRuZr) == "Ru" && dca_cut == 8 && nhf_cut == 20){ */
  /*   cout<<"\n\n ####### HAND FITTING FOR BAD CHILDREN ###### "<<endl; */
  /*   f1_p2_one_lopt_cent->SetParameter(0, 10.1087); f1_p2_one_lopt_cent->SetParError(0, 11.6432); */
  /*   f1_p2_one_lopt_cent->SetParameter(1, -0.000139251); f1_p2_one_lopt_cent->SetParError(1, 0.0339505); */
  /* } */
  /* if(string(NamePPiK) == "AntiProton" && string(NameRuZr) == "Zr" && dca_cut == 8 && nhf_cut == 20){ */
  /*   cout<<"\n\n ####### HAND FITTING FOR BAD CHILDREN ###### "<<endl; */
  /*   f1_p2_one_lopt_cent->SetParameter(0, 10.1087); f1_p2_one_lopt_cent->SetParError(0, 11.6432); */
  /*   f1_p2_one_lopt_cent->SetParameter(1, -0.000139251); f1_p2_one_lopt_cent->SetParError(1, 0.0339505); */
  /* } */
  /* if(string(NamePPiK) == "AntiProton" && string(NameRuZr) == "Ru" && dca_cut == 11 && nhf_cut == 20){ */
  /*   cout<<"\n\n ####### HAND FITTING FOR BAD CHILDREN ###### "<<endl; */
  /*   f1_p2_one_lopt_cent->SetParameter(0, 9.99899); f1_p2_one_lopt_cent->SetParError(0, 8.11662); */
  /*   f1_p2_one_lopt_cent->SetParameter(1, 2.28749e-06); f1_p2_one_lopt_cent->SetParError(1, 0.025711); */
  /* } */

  f1_p0_one_lopt_cent_draw->SetParameter(0, f1_p0_one_lopt_cent->GetParameter(0)); f1_p0_one_lopt_cent_draw->SetParError(0, f1_p0_one_lopt_cent->GetParError(0));
  f1_p0_one_lopt_cent_draw->SetParameter(1, f1_p0_one_lopt_cent->GetParameter(1)); f1_p0_one_lopt_cent_draw->SetParError(1, f1_p0_one_lopt_cent->GetParError(1));
  f1_p1_one_lopt_cent_draw->SetParameter(0, f1_p1_one_lopt_cent->GetParameter(0)); f1_p1_one_lopt_cent_draw->SetParError(0, f1_p1_one_lopt_cent->GetParError(0));
  f1_p1_one_lopt_cent_draw->SetParameter(1, f1_p1_one_lopt_cent->GetParameter(1)); f1_p1_one_lopt_cent_draw->SetParError(1, f1_p1_one_lopt_cent->GetParError(1));
  f1_p2_one_lopt_cent_draw->SetParameter(0, f1_p2_one_lopt_cent->GetParameter(0)); f1_p2_one_lopt_cent_draw->SetParError(0, f1_p2_one_lopt_cent->GetParError(0));
  f1_p2_one_lopt_cent_draw->SetParameter(1, f1_p2_one_lopt_cent->GetParameter(1)); f1_p2_one_lopt_cent_draw->SetParError(1, f1_p2_one_lopt_cent->GetParError(1));
  p0_one_lopt_par0 = f1_p0_one_lopt_cent->GetParameter(0); p0_one_lopt_par1 = f1_p0_one_lopt_cent->GetParameter(1);
  p1_one_lopt_par0 = f1_p1_one_lopt_cent->GetParameter(0); p1_one_lopt_par1 = f1_p1_one_lopt_cent->GetParameter(1);
  p2_one_lopt_par0 = f1_p2_one_lopt_cent->GetParameter(0); p2_one_lopt_par1 = f1_p2_one_lopt_cent->GetParameter(1);

  f1_p0_one_hipt_cent_draw->SetParameter(0, f1_p0_one_hipt_cent->GetParameter(0)); f1_p0_one_hipt_cent_draw->SetParError(0, f1_p0_one_hipt_cent->GetParError(0));
  f1_p0_one_hipt_cent_draw->SetParameter(1, f1_p0_one_hipt_cent->GetParameter(1)); f1_p0_one_hipt_cent_draw->SetParError(1, f1_p0_one_hipt_cent->GetParError(1));
  f1_p1_one_hipt_cent_draw->SetParameter(0, f1_p1_one_hipt_cent->GetParameter(0)); f1_p1_one_hipt_cent_draw->SetParError(0, f1_p1_one_hipt_cent->GetParError(0));
  f1_p1_one_hipt_cent_draw->SetParameter(1, f1_p1_one_hipt_cent->GetParameter(1)); f1_p1_one_hipt_cent_draw->SetParError(1, f1_p1_one_hipt_cent->GetParError(1));
  /* f1_p2_one_hipt_cent_draw->SetParameter(0, f1_p2_one_hipt_cent->GetParameter(0)); f1_p2_one_hipt_cent_draw->SetParError(0, f1_p2_one_hipt_cent->GetParError(0)); */
  /* f1_p2_one_hipt_cent_draw->SetParameter(1, f1_p2_one_hipt_cent->GetParameter(1)); f1_p2_one_hipt_cent_draw->SetParError(1, f1_p2_one_hipt_cent->GetParError(1)); */
  p0_one_hipt_par0 = f1_p0_one_hipt_cent->GetParameter(0); p0_one_hipt_par1 = f1_p0_one_hipt_cent->GetParameter(1);
  p1_one_hipt_par0 = f1_p1_one_hipt_cent->GetParameter(0); p1_one_hipt_par1 = f1_p1_one_hipt_cent->GetParameter(1);
  /* p2_one_hipt_par0 = f1_p2_one_hipt_cent->GetParameter(0); p2_one_hipt_par1 = f1_p2_one_hipt_cent->GetParameter(1); */
  //11082022(finish)

  TCanvas *c_y_pt_oney = new TCanvas("c_y_pt_oney", "c_y_pt_oney", 5000, 2000);
  c_y_pt_oney->Divide(5,2);
  for(int i_cent = 0 ; i_cent < ncent ; i_cent++){
    c_y_pt_oney->cd(i_cent + 1);
    h1_y_pt_eff_one[i_cent]->GetXaxis()->SetRangeUser(0.4, 2.0);
    h1_y_pt_eff_one[i_cent]->Draw();
    f_y_pt_one_lopt_draw[i_cent]->Draw("SAME");
    f_y_pt_one_hipt_draw[i_cent]->Draw("SAME");
  }
  c_y_pt_oney->Print(Form("output/TPC/c_y_pt_oney_%s_%s_dca_%d_nhitsfit_%d.pdf", NamePPiK, NameRuZr, dca_cut, nhf_cut));

  TCanvas *c_y_pt_p012_oney_cent = new TCanvas("c_y_pt_p012_oney_cent", "c_y_pt_p012_oney_cent", 1500, 1000);
  c_y_pt_p012_oney_cent->Divide(3,2);
  c_y_pt_p012_oney_cent->cd(1); gr_y_pt_eff_one_lopt_p0->Draw("AP"); f1_p0_one_lopt_cent_draw->Draw("same");
  c_y_pt_p012_oney_cent->cd(2); gr_y_pt_eff_one_lopt_p1->Draw("AP"); f1_p1_one_lopt_cent_draw->Draw("same");
  c_y_pt_p012_oney_cent->cd(3); gr_y_pt_eff_one_lopt_p2->Draw("AP"); f1_p2_one_lopt_cent_draw->Draw("same");
  c_y_pt_p012_oney_cent->cd(4); gr_y_pt_eff_one_hipt_p0->Draw("AP"); f1_p0_one_hipt_cent_draw->Draw("same");
  c_y_pt_p012_oney_cent->cd(5); gr_y_pt_eff_one_hipt_p1->Draw("AP"); f1_p1_one_hipt_cent_draw->Draw("same");
  /* c_y_pt_p012_oney_cent->cd(6); gr_y_pt_eff_one_hipt_p2->Draw("AP"); f1_p2_one_hipt_cent_draw->Draw("same"); */

  c_y_pt_p012_oney_cent->Print(Form("output/TPC/c_y_pt_p012_oney_cent_%s_%s_dca_%d_nhitsfit_%d.pdf", NamePPiK, NameRuZr, dca_cut, nhf_cut));

  /* myfile.open(Form("output/TPC/file/eff_pt_dep_cent_fit_oneybin_%s_%s_dca_%d_nhitsfit_%d.txt", NamePPiK, NameRuZr, dca_cut, nhf_cut)); */
  /* myfile<<"ybinlow\tybinhi\tp0_par0\tp0_par1\tp1_par0\tp1_par1\tp2_par0\tp2_par1"<<endl; */
  /* myfile<<ybin[3]<<"\t"<<ybin[4+1]<<"\t"<<p0_one_lopt_par0<<"\t"<<p0_one_lopt_par1<<"\t"<<p1_one_lopt_par0<<"\t"<<p1_one_lopt_par1<<"\t"<<p2_one_lopt_par0<<"\t"<<p2_one_lopt_par1<<endl; */
  /* myfile.close(); */

  myfile.open(Form("output/TPC/file/eff_pt_dep_cent_fit_oneybin_%s_%s_dca_%d_nhitsfit_%d.txt", NamePPiK, NameRuZr, dca_cut, nhf_cut));
  /* myfile<<"ybinlow\tybinhi\tp0_lopt_par0\tp0_lopt_par1\tp1_lopt_par0\tp1_lopt_par1\tp2_lopt_par0\tp2_lopt_par1\tp0_hipt_par0\tp0_hipt_par1\tp1_hipt_par0\tp1_hipt_par1"<<endl; */
  myfile<<ybin[3]<<"\t"<<ybin[4+1]<<"\t"<<p0_one_lopt_par0<<"\t"<<p0_one_lopt_par1<<"\t"<<p1_one_lopt_par0<<"\t"<<p1_one_lopt_par1<<"\t"<<p2_one_lopt_par0<<"\t"<<p2_one_lopt_par1<<"\t"<<p0_one_hipt_par0<<"\t"<<p0_one_hipt_par1<<"\t"<<p1_one_hipt_par0<<"\t"<<p1_one_hipt_par1<<endl;
  myfile.close();
  //25062022(finish)

  TFile *f_out = new TFile(Form("output/TPC/file/root/%s_%s_dca_%d_nhitsfit_%d.root", NamePPiK, NameRuZr, dca_cut, nhf_cut), "RECREATE");
  f_out->cd();

  for(int i_cent = 0 ; i_cent < ncent ; i_cent++){
    h1_y_pt_dat_one[i_cent]->Write();
    h1_y_pt_mc_one[i_cent]->Write();
    h1_y_pt_eff_one[i_cent]->Write();
  }
  f_out->Write();
  f_out->Close();
  

  TCanvas *c_emb_dat = new TCanvas("c_emb_dat", "c_emb_dat", 5000, 2000);
  c_emb_dat->Divide(5,2);
  for(int i_cent = 0 ; i_cent < ncent ; i_cent++){
    c_emb_dat->cd(i_cent + 1);
    h1_y_pt_mc_one[i_cent]->SetMarkerColor(2); h1_y_pt_mc_one[i_cent]->SetLineColor(2);
    h1_y_pt_dat_one[i_cent]->SetMarkerColor(4); h1_y_pt_dat_one[i_cent]->SetLineColor(4);
    h1_y_pt_mc_one[i_cent]->GetXaxis()->SetRangeUser(0.4, 2.0);
    h1_y_pt_mc_one[i_cent]->Draw();
    h1_y_pt_dat_one[i_cent]->Draw("SAME");
  }
  c_emb_dat->Print(Form("output/TPC/c_emb_dat_%s_%s_dca_%d_nhitsfit_%d.pdf", NamePPiK, NameRuZr, dca_cut, nhf_cut));

  double mc_entries = 0.;
  double dat_entries = 0.;
  double eff_entries = 0.;
  double tpc_mc_lopt[ncent];
  double tpc_dat_lopt[ncent];
  double tpc_eff_lopt[ncent];
  for(int i_cent = 0 ; i_cent < ncent ; i_cent++){
    mc_entries = 0.;
    dat_entries = 0.;
    eff_entries = 0.;
    for(int i_bin = 0 ; i_bin < h1_y_pt_mc_one[i_cent]->GetNbinsX() ; i_bin++){
      /* for(int i_bin = 0 ; i_bin < h1_y_pt_mc_one[3]->GetNbinsX() ; i_bin++){ */
      if(i_bin >= h1_y_pt_mc_one[i_cent]->GetXaxis()->FindBin(0.4) && i_bin < h1_y_pt_mc_one[i_cent]->GetXaxis()->FindBin(0.8)){
	mc_entries += h1_y_pt_mc_one[i_cent]->GetBinContent(i_bin);
	dat_entries += h1_y_pt_dat_one[i_cent]->GetBinContent(i_bin);
      }
    }// for(int i_bin = 0 ; i_bin < h1_y_pt_mc_one[i_cent]->GetNbinsX() ; i_bin++){
    eff_entries = dat_entries/mc_entries;
    tpc_mc_lopt[i_cent] = mc_entries;
    tpc_dat_lopt[i_cent] = dat_entries;
    tpc_eff_lopt[i_cent] = eff_entries;
    cout<<"i_cent = "<<i_cent<<", "<<dat_entries<<"/"<<mc_entries<<" = "<<eff_entries<<endl;
  }// for(int i_cent = 0 ; i_cent < ncent ; i_cent++){

  TGraph *gr_tpc_mc_lopt = new TGraph(ncent, ref3_avg_arr, tpc_mc_lopt); gr_tpc_mc_lopt->SetMarkerStyle(8); gr_tpc_mc_lopt->SetMarkerColor(2);
  TGraph *gr_tpc_dat_lopt = new TGraph(ncent, ref3_avg_arr, tpc_dat_lopt); gr_tpc_dat_lopt->SetMarkerStyle(8); gr_tpc_dat_lopt->SetMarkerColor(4);
  TGraph *gr_tpc_eff_lopt = new TGraph(ncent, ref3_avg_arr, tpc_eff_lopt); gr_tpc_eff_lopt->SetMarkerStyle(8); gr_tpc_eff_lopt->SetMarkerColor(1);

  TCanvas *c_tpc_eff = new TCanvas("c_tpc_eff", "c_tpc_eff", 1200, 500); c_tpc_eff->Divide(2,1);
  c_tpc_eff->cd(1); gPad->SetGridx(1); gPad->SetGridy(1);
  gr_tpc_mc_lopt->Draw("ap"); gr_tpc_dat_lopt->Draw("psame");
  c_tpc_eff->cd(2); gPad->SetGridx(1); gPad->SetGridy(1);
  gr_tpc_eff_lopt->Draw("ap");
}
