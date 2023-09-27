//Follow what eff_tpc.C does
/* void eff_tof(const char* NamePPiK = "Proton", const char* NameRuZr = "Ru", int dca_cut = 10, int nhf_cut = 20){ */
void eff_tof(const char* NamePPiK = "Proton", const char* NameRuZr = "Ru"){//, int dca_cut = 10, int nhf_cut = 20){

  const int ncent = 10;
  const int nsys = 13;// 3 cuts with 5 variable ( -1 nominal cut): 3 * (5-1) + 1(nominal cut) = 13

  int nxbin = 50;
  int nybin = 5;

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

  TFile *f_glauber_hyb = new TFile(Form("/Users/hosanko/playground/star/anal/Coll/isobar/ZrZrRuRu200_2018/charge/GlauberFit/draw/output/hybrid/ref3/%s_hybrid.root", NameRuZr), "READ");
  TH1D *h1_ref3_hyb;
  if(string(NameRuZr) == "Ru") h1_ref3_hyb = (TH1D*)f_glauber_hyb->Get("h1_ref3_hyb_ru");
  if(string(NameRuZr) == "Zr") h1_ref3_hyb = (TH1D*)f_glauber_hyb->Get("h1_ref3_hyb_zr");
  double ref3_avg = 0.;
  double ref3_avg_arr[ncent];
  for(int i_cent = 0 ; i_cent < ncent ; i_cent++){
    ref3_avg = 0.;
    for(int i_mult = cent_ref3[i_cent+1] ; i_mult < cent_ref3[i_cent] ; i_mult++){
      ref3_avg += i_mult * h1_ref3_hyb->GetBinContent(h1_ref3_hyb->FindBin(i_mult)) / (h1_ref3_hyb->Integral(cent_ref3[i_cent+1], cent_ref3[i_cent]));
    }
    ref3_avg_arr[i_cent] = ref3_avg;
    if(isnan(ref3_avg)) ref3_avg_arr[i_cent] = 0.;
  }//for(int i_cent = 0 ; i_cent < ncent ; i_cent++){

  double dca_cuts[5] = {0.8, 0.9, 1.0, 1.1, 1.2};
  int nhf_cuts[5] = {15, 18, 20, 22, 25};
  double nsp_cuts[5] = {1.6, 1.8, 2.0, 2.2, 2.5};

  double dca_sys[nsys], nsp_sys[nsys];
  int nhf_sys[nsys];

  int cut_counter = 0;
  for(int i_dca = 0 ; i_dca < 5 ; i_dca++){
    for(int i_nhf = 0 ; i_nhf < 5 ; i_nhf++){
      for(int i_nsp = 0 ; i_nsp < 5 ; i_nsp++){
	if(
	   (!(i_dca == 2) && i_nhf == 2 && i_nsp == 2)
	   ||
	   (i_dca == 2 && !(i_nhf == 2) && i_nsp == 2)
	   ||
	   (i_dca == 2 && i_nhf == 2 && !(i_nsp == 2))
	   ||
	   (i_dca == 2 && i_nhf == 2 && i_nsp == 2)
	   ){
	  dca_sys[cut_counter] = dca_cuts[i_dca];
	  nhf_sys[cut_counter] = nhf_cuts[i_nhf];
	  nsp_sys[cut_counter] = nsp_cuts[i_nsp];
	  cout<<cut_counter<<", "<<dca_cuts[i_dca]<<", "<<nhf_cuts[i_nhf]<<", "<<nsp_cuts[i_nsp]<<endl;
	  cut_counter++;
	}//if statement ends
      }//nsp loop ends
    }//nhf loop ends
  }//dca loop ends
  
  /* TFile *f_in = new TFile(Form("/Users/hosanko/Downloads/QA_test_01_hist.root"), "READ"); */
  TFile *f_in = new TFile(Form("/Users/hosanko/playground/star/anal/Coll/isobar/ZrZrRuRu200_2018/charge/sys_unc/efficiency/net_proton/TOF/14022023/14022023_1/Merged_%s_incomplete/mergedFile.root", NameRuZr), "READ");
  TH2F *h2_y_pT_TPC_pP[ncent][nsys];
  TH2F *h2_y_pT_TPC_pM[ncent][nsys];
  TH2F *h2_y_pT_TOF_pP[ncent][nsys];
  TH2F *h2_y_pT_TOF_pM[ncent][nsys];

  TH2F *h2_y_pT_eff_pP[ncent][nsys];
  TH2F *h2_y_pT_eff_pM[ncent][nsys];

  for(int i_cent = 0 ; i_cent < ncent ; i_cent++){
    for(int i_sys = 0 ; i_sys < nsys ; i_sys++){
      h2_y_pT_TPC_pP[i_cent][i_sys] = (TH2F*)f_in->Get(Form("h2_y_pT_TPC_pP_cent_%d_sys_%d", i_cent, i_sys)); h2_y_pT_TPC_pP[i_cent][i_sys]->SetTitle(Form("y vs p_{T}. TPC pP. cent: [%d, %d), dca_cut = %1.1f, nhf_cut = %d, nsp_cut = %1.1f", cent_ref[i_cent+1], cent_ref[i_cent], dca_sys[i_sys], nhf_sys[i_sys], nsp_sys[i_sys]));
      h2_y_pT_TPC_pM[i_cent][i_sys] = (TH2F*)f_in->Get(Form("h2_y_pT_TPC_pM_cent_%d_sys_%d", i_cent, i_sys)); h2_y_pT_TPC_pM[i_cent][i_sys]->SetTitle(Form("y vs p_{T}. TPC pM. cent: [%d, %d), dca_cut = %1.1f, nhf_cut = %d, nsp_cut = %1.1f", cent_ref[i_cent+1], cent_ref[i_cent], dca_sys[i_sys], nhf_sys[i_sys], nsp_sys[i_sys]));
      h2_y_pT_TOF_pP[i_cent][i_sys] = (TH2F*)f_in->Get(Form("h2_y_pT_TOF_pP_cent_%d_sys_%d", i_cent, i_sys)); h2_y_pT_TOF_pP[i_cent][i_sys]->SetTitle(Form("y vs p_{T}. TOF pP. cent: [%d, %d), dca_cut = %1.1f, nhf_cut = %d, nsp_cut = %1.1f", cent_ref[i_cent+1], cent_ref[i_cent], dca_sys[i_sys], nhf_sys[i_sys], nsp_sys[i_sys]));
      h2_y_pT_TOF_pM[i_cent][i_sys] = (TH2F*)f_in->Get(Form("h2_y_pT_TOF_pM_cent_%d_sys_%d", i_cent, i_sys)); h2_y_pT_TOF_pM[i_cent][i_sys]->SetTitle(Form("y vs p_{T}. TOF pM. cent: [%d, %d), dca_cut = %1.1f, nhf_cut = %d, nsp_cut = %1.1f", cent_ref[i_cent+1], cent_ref[i_cent], dca_sys[i_sys], nhf_sys[i_sys], nsp_sys[i_sys]));

      h2_y_pT_TPC_pP[i_cent][i_sys]->RebinX(nxbin); h2_y_pT_TPC_pP[i_cent][i_sys]->RebinY(nybin);
      h2_y_pT_TPC_pM[i_cent][i_sys]->RebinX(nxbin); h2_y_pT_TPC_pM[i_cent][i_sys]->RebinY(nybin);
      h2_y_pT_TOF_pP[i_cent][i_sys]->RebinX(nxbin); h2_y_pT_TOF_pP[i_cent][i_sys]->RebinY(nybin);
      h2_y_pT_TOF_pM[i_cent][i_sys]->RebinX(nxbin); h2_y_pT_TOF_pM[i_cent][i_sys]->RebinY(nybin);
      
      /* h2_y_pT_eff_pP[i_cent][i_sys]->Sumw2(); */
      /* h2_y_pT_eff_pM[i_cent][i_sys]->Sumw2(); */
      h2_y_pT_eff_pP[i_cent][i_sys] = (TH2F*)h2_y_pT_TOF_pP[i_cent][i_sys]->Clone(Form("h2_y_pT_eff_pP_cent_%d_sys_%d", i_cent, i_sys));
      h2_y_pT_eff_pP[i_cent][i_sys]->Reset();
      h2_y_pT_eff_pP[i_cent][i_sys]->Sumw2();
      h2_y_pT_eff_pP[i_cent][i_sys]->Divide(h2_y_pT_TOF_pP[i_cent][i_sys], h2_y_pT_TPC_pP[i_cent][i_sys], 1., 1., "B");
      h2_y_pT_eff_pM[i_cent][i_sys] = (TH2F*)h2_y_pT_TOF_pM[i_cent][i_sys]->Clone(Form("h2_y_pT_eff_pM_cent_%d_sys_%d", i_cent, i_sys));
      h2_y_pT_eff_pM[i_cent][i_sys]->Reset();
      h2_y_pT_eff_pM[i_cent][i_sys]->Sumw2();
      h2_y_pT_eff_pM[i_cent][i_sys]->Divide(h2_y_pT_TOF_pM[i_cent][i_sys], h2_y_pT_TPC_pM[i_cent][i_sys], 1., 1., "B");
      
      /* cout<<Form("cent: [%d, %d), dca_cut = %1.1f, nhf_cut = %d, nsp_cut = %1.1f", cent_ref[i_cent+1], cent_ref[i_cent], dca_sys[i_sys], nhf_sys[i_sys], nsp_sys[i_sys])<<endl; */
      /* if(i_sys == 6) */
      cout<<Form("i_sys = %d, cent: [%d, %d), dca_cut = %1.1f, nhf_cut = %d, nsp_cut = %1.1f", i_sys, cent_ref[i_cent+1], cent_ref[i_cent], dca_sys[i_sys], nhf_sys[i_sys], nsp_sys[i_sys])<<endl;
    }
  }

  //Projection
  const int ny = h2_y_pT_eff_pP[0][0]->GetXaxis()->GetNbins();
  
  TF1 *f_y_pT_pP[ncent][nsys][ny], *f_y_pT_pM[ncent][nsys][ny];
  double p0_pP[ncent][nsys][ny], p1_pP[ncent][nsys][ny], p2_pP[ncent][nsys][ny], p0_pM[ncent][nsys][ny], p1_pM[ncent][nsys][ny], p2_pM[ncent][nsys][ny];
  double p0_err_pP[ncent][nsys][ny], p1_err_pP[ncent][nsys][ny], p2_err_pP[ncent][nsys][ny], p0_err_pM[ncent][nsys][ny], p1_err_pM[ncent][nsys][ny], p2_err_pM[ncent][nsys][ny];

  /* TH1F *h1_y_pT_TPC_pP[ncent][nsys][ny]; */
  /* TH1F *h1_y_pT_TPC_pM[ncent][nsys][ny]; */
  /* TH1F *h1_y_pT_TOF_pP[ncent][nsys][ny]; */
  /* TH1F *h1_y_pT_TOF_pM[ncent][nsys][ny]; */

  TH1F *h1_y_pT_eff_pP[ncent][nsys][ny];
  TH1F *h1_y_pT_eff_pM[ncent][nsys][ny];

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

  for(int i_sys = 0 ; i_sys < nsys ; i_sys++){
    for(int i_cent = 0 ; i_cent < ncent ; i_cent++){
      for(int i_y = 0 ; i_y < ny ; i_y++){
	p0_pP[i_cent][i_sys][i_y] = 0.; p1_pP[i_cent][i_sys][i_y] = 0.; p2_pP[i_cent][i_sys][i_y] = 0.; p0_pM[i_cent][i_sys][i_y] = 0.; p1_pM[i_cent][i_sys][i_y] = 0.; p2_pM[i_cent][i_sys][i_y] = 0.;
	p0_err_pP[i_cent][i_sys][i_y] = 0.; p1_err_pP[i_cent][i_sys][i_y] = 0.; p2_err_pP[i_cent][i_sys][i_y] = 0.; p0_err_pM[i_cent][i_sys][i_y] = 0.; p1_err_pM[i_cent][i_sys][i_y] = 0.; p2_err_pM[i_cent][i_sys][i_y] = 0.;
	
	h1_y_pT_eff_pP[i_cent][i_sys][i_y] = (TH1F*)h2_y_pT_eff_pP[i_cent][i_sys]->ProjectionY(Form("h1_y_pT_eff_pP_cent_%d_sys_%d_y_%d", i_cent, i_sys, i_y), i_y+1, i_y+1, "e");
	h1_y_pT_eff_pP[i_cent][i_sys][i_y]->SetTitle(Form("h1_y_pT_eff_pP_cent_[%d, %d)_y: [%1.1f, %1.1f), dca_cut = %1.1f, nhf_cut = %d, nsp_cut = %1.1f", cent_ref[i_cent+1], cent_ref[i_cent], ybin[i_y], ybin[i_y+1], dca_sys[i_sys], nhf_sys[i_sys], nsp_sys[i_sys]));
	h1_y_pT_eff_pM[i_cent][i_sys][i_y] = (TH1F*)h2_y_pT_eff_pM[i_cent][i_sys]->ProjectionY(Form("h1_y_pT_eff_pM_cent_%d_sys_%d_y_%d", i_cent, i_sys, i_y), i_y+1, i_y+1, "e");
	h1_y_pT_eff_pM[i_cent][i_sys][i_y]->SetTitle(Form("h1_y_pT_eff_pM_cent_[%d, %d)_y: [%1.1f, %1.1f), dca_cut = %1.1f, nhf_cut = %d, nsp_cut = %1.1f", cent_ref[i_cent+1], cent_ref[i_cent], ybin[i_y], ybin[i_y+1], dca_sys[i_sys], nhf_sys[i_sys], nsp_sys[i_sys]));

	f_y_pT_pP[i_cent][i_sys][i_y] = new TF1(Form("f_y_pT_pP_cent_%d_sys_%d_y_%d_phiInt", i_cent, i_sys, i_y), "pol2", 0.8, 3);
	/* f_y_pT_pP[i_cent][i_sys][i_y]->SetParLimits(0, 0.1, 1); */
	/* f_y_pT_pP[i_cent][i_sys][i_y]->SetParLimits(1, 0.1, 1); */
	/* f_y_pT_pP[i_cent][i_sys][i_y]->SetParLimits(2, 0.1, 10); */
	f_y_pT_pM[i_cent][i_sys][i_y] = new TF1(Form("f_y_pT_pM_cent_%d_sys_%d_y_%d_phiInt", i_cent, i_sys, i_y), "pol2", 0.8, 3);
	/* f_y_pT_pM[i_cent][i_sys][i_y]->SetParLimits(0, 0.1, 1); */
	/* f_y_pT_pM[i_cent][i_sys][i_y]->SetParLimits(1, 0.1, 1); */
	/* f_y_pT_pM[i_cent][i_sys][i_y]->SetParLimits(2, 0.1, 10); */

	h1_y_pT_eff_pP[i_cent][i_sys][i_y]->GetYaxis()->SetRangeUser(0, 1);
	h1_y_pT_eff_pM[i_cent][i_sys][i_y]->GetYaxis()->SetRangeUser(0, 1);
	h1_y_pT_eff_pP[i_cent][i_sys][i_y]->Fit(f_y_pT_pP[i_cent][i_sys][i_y], "R");
	h1_y_pT_eff_pM[i_cent][i_sys][i_y]->Fit(f_y_pT_pM[i_cent][i_sys][i_y], "R");

	p0_pP[i_cent][i_sys][i_y] = f_y_pT_pP[i_cent][i_sys][i_y]->GetParameter(0);
	p1_pP[i_cent][i_sys][i_y] = f_y_pT_pP[i_cent][i_sys][i_y]->GetParameter(1);
	p2_pP[i_cent][i_sys][i_y] = f_y_pT_pP[i_cent][i_sys][i_y]->GetParameter(2);
	p0_err_pP[i_cent][i_sys][i_y] = f_y_pT_pP[i_cent][i_sys][i_y]->GetParError(0);
	p1_err_pP[i_cent][i_sys][i_y] = f_y_pT_pP[i_cent][i_sys][i_y]->GetParError(1);
	p2_err_pP[i_cent][i_sys][i_y] = f_y_pT_pP[i_cent][i_sys][i_y]->GetParError(2);

	p0_pM[i_cent][i_sys][i_y] = f_y_pT_pM[i_cent][i_sys][i_y]->GetParameter(0);
	p1_pM[i_cent][i_sys][i_y] = f_y_pT_pM[i_cent][i_sys][i_y]->GetParameter(1);
	p2_pM[i_cent][i_sys][i_y] = f_y_pT_pM[i_cent][i_sys][i_y]->GetParameter(2);
	p0_err_pM[i_cent][i_sys][i_y] = f_y_pT_pM[i_cent][i_sys][i_y]->GetParError(0);
	p1_err_pM[i_cent][i_sys][i_y] = f_y_pT_pM[i_cent][i_sys][i_y]->GetParError(1);
	p2_err_pM[i_cent][i_sys][i_y] = f_y_pT_pM[i_cent][i_sys][i_y]->GetParError(2);
      }
    }
  }

  //Fit parameters plotted with respect to centrality
  TGraphErrors *gr_y_pT_pP_p0[nsys][ny], *gr_y_pT_pP_p1[nsys][ny], *gr_y_pT_pP_p2[nsys][ny];
  TGraphErrors *gr_y_pT_pM_p0[nsys][ny], *gr_y_pT_pM_p1[nsys][ny], *gr_y_pT_pM_p2[nsys][ny];

  double p0_pP_cent[ncent], p1_pP_cent[ncent], p2_pP_cent[ncent];
  double p0_err_pP_cent[ncent], p1_err_pP_cent[ncent], p2_err_pP_cent[ncent];
  double p0_pM_cent[ncent], p1_pM_cent[ncent], p2_pM_cent[ncent];
  double p0_err_pM_cent[ncent], p1_err_pM_cent[ncent], p2_err_pM_cent[ncent];

  TF1 *f1_p0_pP_cent[nsys][ny], *f1_p1_pP_cent[nsys][ny], *f1_p2_pP_cent[nsys][ny];
  TF1 *f1_p0_pM_cent[nsys][ny], *f1_p1_pM_cent[nsys][ny], *f1_p2_pM_cent[nsys][ny];

  double p0_par0_pP[nsys][ny], p0_par1_pP[nsys][ny];
  double p1_par0_pP[nsys][ny], p1_par1_pP[nsys][ny];
  double p2_par0_pP[nsys][ny], p2_par1_pP[nsys][ny];

  double p0_par0_pM[nsys][ny], p0_par1_pM[nsys][ny];
  double p1_par0_pM[nsys][ny], p1_par1_pM[nsys][ny];
  double p2_par0_pM[nsys][ny], p2_par1_pM[nsys][ny];

  for(int i_sys = 0 ; i_sys < nsys ; i_sys++){
    /* if(i_sys == 6){ */
    for(int i_y = 0 ; i_y < ny ; i_y++){
      f1_p0_pP_cent[i_sys][i_y] = new TF1(Form("f1_p0_pP_cent_sys_%d_y_%d", i_sys, i_y), "pol1", 5, 500);//0 is at 0 so avoid!
      f1_p1_pP_cent[i_sys][i_y] = new TF1(Form("f1_p1_pP_cent_sys_%d_y_%d", i_sys, i_y), "pol1", 5, 500);
      f1_p2_pP_cent[i_sys][i_y] = new TF1(Form("f1_p2_pP_cent_sys_%d_y_%d", i_sys, i_y), "pol1", 5, 500);

      f1_p0_pM_cent[i_sys][i_y] = new TF1(Form("f1_p0_pM_cent_sys_%d_y_%d", i_sys, i_y), "pol1", 5, 500);//0 is at 0 so avoid!
      f1_p1_pM_cent[i_sys][i_y] = new TF1(Form("f1_p1_pM_cent_sys_%d_y_%d", i_sys, i_y), "pol1", 5, 500);
      f1_p2_pM_cent[i_sys][i_y] = new TF1(Form("f1_p2_pM_cent_sys_%d_y_%d", i_sys, i_y), "pol1", 5, 500);

      for(int i_cent = 0 ; i_cent < ncent ; i_cent++) {
	p0_pP_cent[i_cent] = p0_pP[i_cent][i_sys][i_y];
	p1_pP_cent[i_cent] = p1_pP[i_cent][i_sys][i_y];
	p2_pP_cent[i_cent] = p2_pP[i_cent][i_sys][i_y];
	p0_err_pP_cent[i_cent] = p0_err_pP[i_cent][i_sys][i_y];
	p1_err_pP_cent[i_cent] = p1_err_pP[i_cent][i_sys][i_y];
	p2_err_pP_cent[i_cent] = p2_err_pP[i_cent][i_sys][i_y];
	p0_pM_cent[i_cent] = p0_pM[i_cent][i_sys][i_y];
	p1_pM_cent[i_cent] = p1_pM[i_cent][i_sys][i_y];
	p2_pM_cent[i_cent] = p2_pM[i_cent][i_sys][i_y];
	p0_err_pM_cent[i_cent] = p0_err_pM[i_cent][i_sys][i_y];
	p1_err_pM_cent[i_cent] = p1_err_pM[i_cent][i_sys][i_y];
	p2_err_pM_cent[i_cent] = p2_err_pM[i_cent][i_sys][i_y];
	/* cout<<"!!!!!!!!!!!!! i_y = "<<i_y<<", p1_err_pP_cent["<<i_cent<<"] = "<<p1_err_pP_cent[i_cent]<<endl; */
	/* cout<<"!!!!!!!!!!!!! i_y = "<<i_y<<", p1_err_pM_cent["<<i_cent<<"] = "<<p1_err_pM_cent[i_cent]<<endl; */
      }//for(int i_cent = 0 ; i_cent < ncent ; i_cent++) {
      gr_y_pT_pP_p0[i_sys][i_y] = new TGraphErrors(ncent, ref3_avg_arr, p0_pP_cent, 0, p0_err_pP_cent);
      gr_y_pT_pP_p1[i_sys][i_y] = new TGraphErrors(ncent, ref3_avg_arr, p1_pP_cent, 0, p1_err_pP_cent);
      gr_y_pT_pP_p2[i_sys][i_y] = new TGraphErrors(ncent, ref3_avg_arr, p2_pP_cent, 0, p2_err_pP_cent);
      gr_y_pT_pP_p0[i_sys][i_y]->SetMarkerStyle(8);
      gr_y_pT_pP_p1[i_sys][i_y]->SetMarkerStyle(8);
      gr_y_pT_pP_p2[i_sys][i_y]->SetMarkerStyle(8);
      gr_y_pT_pM_p0[i_sys][i_y] = new TGraphErrors(ncent, ref3_avg_arr, p0_pM_cent, 0, p0_err_pM_cent);
      gr_y_pT_pM_p1[i_sys][i_y] = new TGraphErrors(ncent, ref3_avg_arr, p1_pM_cent, 0, p1_err_pM_cent);
      gr_y_pT_pM_p2[i_sys][i_y] = new TGraphErrors(ncent, ref3_avg_arr, p2_pM_cent, 0, p2_err_pM_cent);
      gr_y_pT_pM_p0[i_sys][i_y]->SetMarkerStyle(8);
      gr_y_pT_pM_p1[i_sys][i_y]->SetMarkerStyle(8);
      gr_y_pT_pM_p2[i_sys][i_y]->SetMarkerStyle(8);

      /* cout<<"!!!!!!!!!!!!! i_cent = "<<i_cent<<", gr_y_pT_pP_p1["<<i_sys<<"]["<<i_y<<"] = "<<gr_y_pT_pP_p1[i_sys][i_y]->GetErrorY(<<endl; */
	

      gr_y_pT_pP_p0[i_sys][i_y]->SetName(Form("gr_y_pT_pP_p0_sys_%d_y_%d", i_sys, i_y));
      gr_y_pT_pP_p1[i_sys][i_y]->SetName(Form("gr_y_pT_pP_p1_sys_%d_y_%d", i_sys, i_y));
      gr_y_pT_pP_p2[i_sys][i_y]->SetName(Form("gr_y_pT_pP_p2_sys_%d_y_%d", i_sys, i_y));
      gr_y_pT_pM_p0[i_sys][i_y]->SetName(Form("gr_y_pT_pM_p0_sys_%d_y_%d", i_sys, i_y));
      gr_y_pT_pM_p1[i_sys][i_y]->SetName(Form("gr_y_pT_pM_p1_sys_%d_y_%d", i_sys, i_y));
      gr_y_pT_pM_p2[i_sys][i_y]->SetName(Form("gr_y_pT_pM_p2_sys_%d_y_%d", i_sys, i_y));

      gr_y_pT_pP_p0[i_sys][i_y]->SetTitle(Form("pP, p0, y: [%1.1f, %1.1f), dca_cut = %1.1f, nhf_cut = %d, nsp_cut = %1.1f", ybin[i_y], ybin[i_y+1], dca_sys[i_sys], nhf_sys[i_sys], nsp_sys[i_sys]));
      gr_y_pT_pP_p1[i_sys][i_y]->SetTitle(Form("pP, p1, y: [%1.1f, %1.1f), dca_cut = %1.1f, nhf_cut = %d, nsp_cut = %1.1f", ybin[i_y], ybin[i_y+1], dca_sys[i_sys], nhf_sys[i_sys], nsp_sys[i_sys]));
      gr_y_pT_pP_p2[i_sys][i_y]->SetTitle(Form("pP, p2, y: [%1.1f, %1.1f), dca_cut = %1.1f, nhf_cut = %d, nsp_cut = %1.1f", ybin[i_y], ybin[i_y+1], dca_sys[i_sys], nhf_sys[i_sys], nsp_sys[i_sys]));
      gr_y_pT_pM_p0[i_sys][i_y]->SetTitle(Form("pM, p0, y: [%1.1f, %1.1f), dca_cut = %1.1f, nhf_cut = %d, nsp_cut = %1.1f", ybin[i_y], ybin[i_y+1], dca_sys[i_sys], nhf_sys[i_sys], nsp_sys[i_sys]));
      gr_y_pT_pM_p1[i_sys][i_y]->SetTitle(Form("pM, p1, y: [%1.1f, %1.1f), dca_cut = %1.1f, nhf_cut = %d, nsp_cut = %1.1f", ybin[i_y], ybin[i_y+1], dca_sys[i_sys], nhf_sys[i_sys], nsp_sys[i_sys]));
      gr_y_pT_pM_p2[i_sys][i_y]->SetTitle(Form("pM, p2, y: [%1.1f, %1.1f), dca_cut = %1.1f, nhf_cut = %d, nsp_cut = %1.1f", ybin[i_y], ybin[i_y+1], dca_sys[i_sys], nhf_sys[i_sys], nsp_sys[i_sys]));

      /* f1_p0_pP_cent[i_sys][i_y]->SetParLimits(0, -3, 3); */
      /* f1_p0_pP_cent[i_sys][i_y]->SetParLimits(1, -3, 3); */
      /* f1_p0_pP_cent[i_sys][i_y]->SetParLimits(2, -3, 3); */
      /* f1_p1_pP_cent[i_sys][i_y]->SetParLimits(0, -3, 3); */
      /* f1_p1_pP_cent[i_sys][i_y]->SetParLimits(1, -3, 3); */
      /* f1_p1_pP_cent[i_sys][i_y]->SetParLimits(2, -3, 3); */
      /* f1_p2_pP_cent[i_sys][i_y]->SetParLimits(0, -3, 3); */
      /* f1_p2_pP_cent[i_sys][i_y]->SetParLimits(1, -3, 3); */
      /* f1_p2_pP_cent[i_sys][i_y]->SetParLimits(2, -3, 3); */

      /* f1_p0_pM_cent[i_sys][i_y]->SetParLimits(0, -3, 3); */
      /* f1_p0_pM_cent[i_sys][i_y]->SetParLimits(1, -3, 3); */
      /* f1_p0_pM_cent[i_sys][i_y]->SetParLimits(2, -3, 3); */
      /* f1_p1_pM_cent[i_sys][i_y]->SetParLimits(0, -3, 3); */
      /* f1_p1_pM_cent[i_sys][i_y]->SetParLimits(1, -3, 3); */
      /* f1_p1_pM_cent[i_sys][i_y]->SetParLimits(2, -3, 3); */
      /* f1_p2_pM_cent[i_sys][i_y]->SetParLimits(0, -3, 3); */
      /* f1_p2_pM_cent[i_sys][i_y]->SetParLimits(1, -3, 3); */
      /* f1_p2_pM_cent[i_sys][i_y]->SetParLimits(2, -3, 3); */
      
      gr_y_pT_pP_p0[i_sys][i_y]->Fit(f1_p0_pP_cent[i_sys][i_y], "F R");
      p0_par0_pP[i_sys][i_y] = f1_p0_pP_cent[i_sys][i_y]->GetParameter(0);
      p0_par1_pP[i_sys][i_y] = f1_p0_pP_cent[i_sys][i_y]->GetParameter(1);
      gr_y_pT_pP_p1[i_sys][i_y]->Fit(f1_p1_pP_cent[i_sys][i_y], "F R");
      p1_par0_pP[i_sys][i_y] = f1_p1_pP_cent[i_sys][i_y]->GetParameter(0);
      p1_par1_pP[i_sys][i_y] = f1_p1_pP_cent[i_sys][i_y]->GetParameter(1);
      gr_y_pT_pP_p2[i_sys][i_y]->Fit(f1_p2_pP_cent[i_sys][i_y], "F R");
      p2_par0_pP[i_sys][i_y] = f1_p2_pP_cent[i_sys][i_y]->GetParameter(0);
      p2_par1_pP[i_sys][i_y] = f1_p2_pP_cent[i_sys][i_y]->GetParameter(1);

      gr_y_pT_pM_p0[i_sys][i_y]->Fit(f1_p0_pM_cent[i_sys][i_y], "F R");
      p0_par0_pM[i_sys][i_y] = f1_p0_pM_cent[i_sys][i_y]->GetParameter(0);
      p0_par1_pM[i_sys][i_y] = f1_p0_pM_cent[i_sys][i_y]->GetParameter(1);
      gr_y_pT_pM_p1[i_sys][i_y]->Fit(f1_p1_pM_cent[i_sys][i_y], "F R");
      p1_par0_pM[i_sys][i_y] = f1_p1_pM_cent[i_sys][i_y]->GetParameter(0);
      p1_par1_pM[i_sys][i_y] = f1_p1_pM_cent[i_sys][i_y]->GetParameter(1);
      gr_y_pT_pM_p2[i_sys][i_y]->Fit(f1_p2_pM_cent[i_sys][i_y], "F R");
      p2_par0_pM[i_sys][i_y] = f1_p2_pM_cent[i_sys][i_y]->GetParameter(0);
      p2_par1_pM[i_sys][i_y] = f1_p2_pM_cent[i_sys][i_y]->GetParameter(1);
    }//for(int i_y = 0 ; i_y < ny ; i_y++){
    /* }//if(i_sys == 6){ */
  }//for(int i_sys = 0 ; i_sys < nsys ; i_sys++){

  TCanvas *c_y_pt_eff_pP_1[nsys], *c_y_pt_eff_pM_1[nsys];
  for(int i_sys = 0 ; i_sys < nsys ; i_sys++){
    /* if(i_sys == 6){ */
    c_y_pt_eff_pP_1[i_sys] = new TCanvas(Form("c_y_pt_eff_pP_sys_%d_1", i_sys), Form("c_y_pt_eff_pP_sys_%d_1", i_sys), 5000, 2000);
    c_y_pt_eff_pM_1[i_sys] = new TCanvas(Form("c_y_pt_eff_pM_sys_%d_1", i_sys), Form("c_y_pt_eff_pM_sys_%d_1", i_sys), 5000, 2000);
    c_y_pt_eff_pP_1[i_sys]->Divide(5,2);
    c_y_pt_eff_pM_1[i_sys]->Divide(5,2);

    for(int i_cent = 0 ; i_cent < ncent ; i_cent++){
      c_y_pt_eff_pP_1[i_sys]->cd(i_cent + 1);
      h2_y_pT_eff_pP[i_cent][i_sys]->Draw("colz");
      c_y_pt_eff_pM_1[i_sys]->cd(i_cent + 1);
      h2_y_pT_eff_pM[i_cent][i_sys]->Draw("colz");
    }
    c_y_pt_eff_pP_1[i_sys]->Print(Form("output/TOF/c_y_pt_eff_pP_%s_%s_sys_%d_1.pdf", NamePPiK, NameRuZr, i_sys));
    c_y_pt_eff_pM_1[i_sys]->Print(Form("output/TOF/c_y_pt_eff_pM_%s_%s_sys_%d_1.pdf", NamePPiK, NameRuZr, i_sys));
    /* }//if(i_sys == 6){ */
  }

  TFile *f_out[nsys];
  for(int i_sys = 0 ; i_sys < nsys ; i_sys++){
    f_out[i_sys] = new TFile(Form("output/TOF/TOF_%s_%s_dca_%1.1f_nhf_%d_nsp_%1.1f.root", NamePPiK, NameRuZr, dca_sys[i_sys], nhf_sys[i_sys], nsp_sys[i_sys]), "RECREATE");
    for(int i_cent = 0 ; i_cent < ncent ; i_cent++){
      h2_y_pT_TPC_pP[i_cent][i_sys]->Write(Form("h2_y_pT_TPC_pP_cent_%d", i_cent));
      h2_y_pT_TPC_pM[i_cent][i_sys]->Write(Form("h2_y_pT_TPC_pM_cent_%d", i_cent));
      h2_y_pT_TOF_pP[i_cent][i_sys]->Write(Form("h2_y_pT_TOF_pP_cent_%d", i_cent));
      h2_y_pT_TOF_pM[i_cent][i_sys]->Write(Form("h2_y_pT_TOF_pM_cent_%d", i_cent));
      h2_y_pT_eff_pP[i_cent][i_sys]->Write(Form("h2_y_pT_eff_pP_cent_%d", i_cent));
      h2_y_pT_eff_pM[i_cent][i_sys]->Write(Form("h2_y_pT_eff_pM_cent_%d", i_cent));
      for(int i_y = 0 ; i_y < ny ; i_y++){
	gr_y_pT_pP_p0[i_sys][i_y]->Write();
	gr_y_pT_pP_p1[i_sys][i_y]->Write();
	gr_y_pT_pP_p2[i_sys][i_y]->Write();
	gr_y_pT_pM_p0[i_sys][i_y]->Write();
	gr_y_pT_pM_p1[i_sys][i_y]->Write();
	gr_y_pT_pM_p2[i_sys][i_y]->Write();
      }
    }
    f_out[i_sys]->Write();
    f_out[i_sys]->Close();
  }
  

  TCanvas *c_y_pt_pP_1D[nsys], *c_y_pt_pM_1D[nsys];
  for(int i_sys = 0 ; i_sys < nsys ; i_sys++){
    /* if(i_sys == 6){ */
    c_y_pt_pP_1D[i_sys] = new TCanvas(Form("c_y_pt_pP_1D_sys_%d", i_sys), Form("c_y_pt_pP_1D_sys_%d", i_sys), 5000, 2000);
    c_y_pt_pP_1D[i_sys]->Divide(5,2);
    c_y_pt_pM_1D[i_sys] = new TCanvas(Form("c_y_pt_pM_1D_sys_%d", i_sys), Form("c_y_pt_pM_1D_sys_%d", i_sys), 5000, 2000);
    c_y_pt_pM_1D[i_sys]->Divide(5,2);
    for(int i_y = 0 ; i_y < ny ; i_y++){
      for(int i_cent = 0 ; i_cent < ncent ; i_cent++){
	c_y_pt_pP_1D[i_sys]->cd(i_cent + 1);
	h1_y_pT_eff_pP[i_cent][i_sys][i_y]->Draw();
	c_y_pt_pM_1D[i_sys]->cd(i_cent + 1);
	h1_y_pT_eff_pM[i_cent][i_sys][i_y]->Draw();
      }
      if(i_y == 0) {
	c_y_pt_pP_1D[i_sys]->Print(Form("output/TOF/1D/c_y_pt_pP_1D_%s_%s_sys_%d.pdf(",NamePPiK, NameRuZr, i_sys));
	c_y_pt_pM_1D[i_sys]->Print(Form("output/TOF/1D/c_y_pt_pM_1D_%s_%s_sys_%d.pdf(",NamePPiK, NameRuZr, i_sys));
      }
      if(i_y == ny - 1) {
	c_y_pt_pP_1D[i_sys]->Print(Form("output/TOF/1D/c_y_pt_pP_1D_%s_%s_sys_%d.pdf)",NamePPiK, NameRuZr, i_sys));
	c_y_pt_pM_1D[i_sys]->Print(Form("output/TOF/1D/c_y_pt_pM_1D_%s_%s_sys_%d.pdf)",NamePPiK, NameRuZr, i_sys));
      }
      else {
	c_y_pt_pP_1D[i_sys]->Print(Form("output/TOF/1D/c_y_pt_pP_1D_%s_%s_sys_%d.pdf",NamePPiK, NameRuZr, i_sys));
	c_y_pt_pM_1D[i_sys]->Print(Form("output/TOF/1D/c_y_pt_pM_1D_%s_%s_sys_%d.pdf",NamePPiK, NameRuZr, i_sys));
      }
    }
    /* }//if(i_sys == 6){ */
  }

  TCanvas *c_y_pt_cent_pP_1D[nsys], *c_y_pt_cent_pM_1D[nsys];
  for(int i_sys = 0 ; i_sys < nsys ; i_sys++){
    /* if(i_sys == 6){ */
    c_y_pt_cent_pP_1D[i_sys] = new TCanvas(Form("c_y_pt_cent_pP_1D_sys_%d", i_sys), Form("c_y_pt_cent_pP_1D_sys_%d", i_sys), 2000, 1000);
    c_y_pt_cent_pP_1D[i_sys]->Divide(4,2);
    c_y_pt_cent_pM_1D[i_sys] = new TCanvas(Form("c_y_pt_cent_pM_1D_sys_%d", i_sys), Form("c_y_pt_cent_pM_1D_sys_%d", i_sys), 2000, 1000);
    c_y_pt_cent_pM_1D[i_sys]->Divide(4,2);
    for(int i_p = 0 ; i_p < 3 ; i_p++){
      if(i_p == 0){
	for(int i_y = 0 ; i_y < ny ; i_y++){
	  c_y_pt_cent_pP_1D[i_sys]->cd(i_y + 1);
	  gr_y_pT_pP_p0[i_sys][i_y]->GetYaxis()->SetRangeUser(0, 1.9);
	  if(i_y == 6 || i_y == 13) gr_y_pT_pP_p0[i_sys][i_y]->GetYaxis()->SetRangeUser(-10, 10);
	  gr_y_pT_pP_p0[i_sys][i_y]->Draw("AP");
	  c_y_pt_cent_pM_1D[i_sys]->cd(i_y + 1);
	  gr_y_pT_pM_p0[i_sys][i_y]->GetYaxis()->SetRangeUser(0, 1.9);
	  if(i_y == 6 || i_y == 13) gr_y_pT_pM_p0[i_sys][i_y]->GetYaxis()->SetRangeUser(-10, 10);
	  gr_y_pT_pM_p0[i_sys][i_y]->Draw("AP");
	}
	c_y_pt_cent_pP_1D[i_sys]->Print(Form("output/TOF/1D/c_y_pt_cent_pP_1D_%s_%s_sys_%d.pdf(",NamePPiK, NameRuZr, i_sys));
	c_y_pt_cent_pM_1D[i_sys]->Print(Form("output/TOF/1D/c_y_pt_cent_pM_1D_%s_%s_sys_%d.pdf(",NamePPiK, NameRuZr, i_sys));
      }
      else if(i_p == 1){
	for(int i_y = 0 ; i_y < ny ; i_y++){
	  c_y_pt_cent_pP_1D[i_sys]->cd(i_y + 1);
	  gr_y_pT_pP_p1[i_sys][i_y]->GetYaxis()->SetRangeUser(-0.17, 0.02);
	  if(i_y == 6 || i_y == 13) gr_y_pT_pP_p1[i_sys][i_y]->GetYaxis()->SetRangeUser(-10, 10);
	  gr_y_pT_pP_p1[i_sys][i_y]->Draw("AP");
	  c_y_pt_cent_pM_1D[i_sys]->cd(i_y + 1);
	  gr_y_pT_pM_p1[i_sys][i_y]->GetYaxis()->SetRangeUser(-0.17, 0.02);
	  if(i_y == 6 || i_y == 13) gr_y_pT_pM_p1[i_sys][i_y]->GetYaxis()->SetRangeUser(-10, 10);
	  gr_y_pT_pM_p1[i_sys][i_y]->Draw("AP");
	}
	c_y_pt_cent_pP_1D[i_sys]->Print(Form("output/TOF/1D/c_y_pt_cent_pP_1D_%s_%s_sys_%d.pdf",NamePPiK, NameRuZr, i_sys));
	c_y_pt_cent_pM_1D[i_sys]->Print(Form("output/TOF/1D/c_y_pt_cent_pM_1D_%s_%s_sys_%d.pdf",NamePPiK, NameRuZr, i_sys));
      }
      else if(i_p == 2){
	for(int i_y = 0 ; i_y < ny ; i_y++){
	  c_y_pt_cent_pP_1D[i_sys]->cd(i_y + 1);
	  gr_y_pT_pP_p2[i_sys][i_y]->GetYaxis()->SetRangeUser(0, 0.08);
	  if(i_y == 6 || i_y == 13) gr_y_pT_pP_p2[i_sys][i_y]->GetYaxis()->SetRangeUser(-10, 10);
	  gr_y_pT_pP_p2[i_sys][i_y]->Draw("AP");
	  c_y_pt_cent_pM_1D[i_sys]->cd(i_y + 1);
	  gr_y_pT_pM_p2[i_sys][i_y]->GetYaxis()->SetRangeUser(0, 0.08);
	  if(i_y == 6 || i_y == 13) gr_y_pT_pM_p2[i_sys][i_y]->GetYaxis()->SetRangeUser(-10, 10);
	  gr_y_pT_pM_p2[i_sys][i_y]->Draw("AP");
	}
	c_y_pt_cent_pP_1D[i_sys]->Print(Form("output/TOF/1D/c_y_pt_cent_pP_1D_%s_%s_sys_%d.pdf)",NamePPiK, NameRuZr, i_sys));
	c_y_pt_cent_pM_1D[i_sys]->Print(Form("output/TOF/1D/c_y_pt_cent_pM_1D_%s_%s_sys_%d.pdf)",NamePPiK, NameRuZr, i_sys));
      }
    }
    /* }//if(i_sys == 6){ */
  }

  ofstream myfile;
  for(int i_sys = 0 ; i_sys < nsys ; i_sys++){
    myfile.open(Form("output/TOF/1D/file/eff_pt_dep_cent_fit_ybin_%s_%s_dca_%1.1f_nhf_%d_nsp_%1.1f.txt", NamePPiK, NameRuZr, dca_sys[i_sys], nhf_sys[i_sys], nsp_sys[i_sys]));
    myfile<<"ybinlow\tybinhi\tp0_par0\tp0_par1\tp1_par0\tp1_par1\tp2_par0\tp2_par1"<<endl;
    for(int i_y = 0 ; i_y < ny ; i_y++){
      if(string(NamePPiK) == "Proton" || string(NamePPiK) == "Piplus" || string(NamePPiK) == "Kplus"){
	myfile<<ybin[i_y]<<"\t"<<ybin[i_y+1]<<"\t"<<p0_par0_pP[i_sys][i_y]<<"\t"<<p0_par1_pP[i_sys][i_y]<<"\t"<<p1_par0_pP[i_sys][i_y]<<"\t"<<p1_par1_pP[i_sys][i_y]<<"\t"<<p2_par0_pP[i_sys][i_y]<<"\t"<<p2_par1_pP[i_sys][i_y]<<endl;
      }
      else if(string(NamePPiK) == "AntiProton" || string(NamePPiK) == "Piminus" || string(NamePPiK) == "Kminus"){
	myfile<<ybin[i_y]<<"\t"<<ybin[i_y+1]<<"\t"<<p0_par0_pM[i_sys][i_y]<<"\t"<<p0_par1_pM[i_sys][i_y]<<"\t"<<p1_par0_pM[i_sys][i_y]<<"\t"<<p1_par1_pM[i_sys][i_y]<<"\t"<<p2_par0_pM[i_sys][i_y]<<"\t"<<p2_par1_pM[i_sys][i_y]<<endl;
      }
    }
    myfile.close();
  }
  
  //25062022(start)
  //What I want: y: -0.5 ~ 0.5 just one bin!
  TF1 *f_y_pt_one_pP[ncent][nsys], *f_y_pt_one_pM[ncent][nsys];
  TF1 *f_y_pt_one_draw_pP[ncent][nsys], *f_y_pt_one_draw_pM[ncent][nsys];
  double p0_one_pP[ncent][nsys], p1_one_pP[ncent][nsys], p2_one_pP[ncent][nsys];
  double p0_one_pM[ncent][nsys], p1_one_pM[ncent][nsys], p2_one_pM[ncent][nsys];
  double p0_one_err_pP[ncent][nsys],  p1_one_err_pP[ncent][nsys], p2_one_err_pP[ncent][nsys];
  double p0_one_err_pM[ncent][nsys],  p1_one_err_pM[ncent][nsys], p2_one_err_pM[ncent][nsys];
  TH1D *h1_y_pt_TOF_one_pP[ncent][nsys], *h1_y_pt_TPC_one_pP[ncent][nsys];;
  TH1D *h1_y_pt_TOF_one_pM[ncent][nsys], *h1_y_pt_TPC_one_pM[ncent][nsys];;
  /* TH1 *h1_y_pt_eff_one_pP[ncent][nsys]; */
  /* TEfficiency *h1_y_pt_eff_one_pP[ncent][nsys]; */
  /* TEfficiency *h1_y_pt_eff_one_pM[ncent][nsys]; */
  TH1 *h1_y_pt_eff_one_pP[ncent][nsys];
  TH1 *h1_y_pt_eff_one_pM[ncent][nsys];
  //04082022(start):reliable cheating
  double cheat_p0, cheat_p1, cheat_p2;
  double cheat_p0_err, cheat_p1_err, cheat_p2_err;
  /* for(int i_sys = 0 ; i_sys < nsys ; i_sys++){ */
  for(int i_sys = nsys-1 ; i_sys >= 0 ; i_sys--){
    //04082022(finish):reliable cheating
    for(int i_cent = 0 ; i_cent < ncent ; i_cent++){
      h1_y_pt_TOF_one_pP[i_cent][i_sys] = (TH1D*)h2_y_pT_TOF_pP[i_cent][i_sys]->ProjectionY(Form("h1_y_pt_TOF_one_pP_cent_%d_sys_%d", i_cent, i_sys), 3+1, 4+1, "e");
      h1_y_pt_TOF_one_pP[i_cent][i_sys]->SetTitle(Form("h1_y_pt_TOF_pP_cent_[%d, %d)_y: [%1.1f, %1.1f)", cent_ref[i_cent+1], cent_ref[i_cent], ybin[3], ybin[4+1]));
      h1_y_pt_TOF_one_pP[i_cent][i_sys]->Sumw2();
      h1_y_pt_TPC_one_pP[i_cent][i_sys] = (TH1D*)h2_y_pT_TPC_pP[i_cent][i_sys]->ProjectionY(Form("h1_y_pt_TPC_one_pP_cent_%d_sys_%d", i_cent, i_sys), 3+1, 4+1, "e");
      h1_y_pt_TPC_one_pP[i_cent][i_sys]->SetTitle(Form("h1_y_pt_TPC_pP_cent_[%d, %d)_y: [%1.1f, %1.1f)", cent_ref[i_cent+1], cent_ref[i_cent], ybin[3], ybin[4+1]));
      h1_y_pt_TPC_one_pP[i_cent][i_sys]->Sumw2();

      h1_y_pt_TOF_one_pM[i_cent][i_sys] = (TH1D*)h2_y_pT_TOF_pM[i_cent][i_sys]->ProjectionY(Form("h1_y_pt_TOF_one_pM_cent_%d_sys_%d", i_cent, i_sys), 3+1, 4+1, "e");
      h1_y_pt_TOF_one_pM[i_cent][i_sys]->SetTitle(Form("h1_y_pt_TOF_pM_cent_[%d, %d)_y: [%1.1f, %1.1f)", cent_ref[i_cent+1], cent_ref[i_cent], ybin[3], ybin[4+1]));
      h1_y_pt_TOF_one_pM[i_cent][i_sys]->Sumw2();
      h1_y_pt_TPC_one_pM[i_cent][i_sys] = (TH1D*)h2_y_pT_TPC_pM[i_cent][i_sys]->ProjectionY(Form("h1_y_pt_TPC_one_pM_cent_%d_sys_%d", i_cent, i_sys), 3+1, 4+1, "e");
      h1_y_pt_TPC_one_pM[i_cent][i_sys]->SetTitle(Form("h1_y_pt_TPC_pM_cent_[%d, %d)_y: [%1.1f, %1.1f)", cent_ref[i_cent+1], cent_ref[i_cent], ybin[3], ybin[4+1]));
      h1_y_pt_TPC_one_pM[i_cent][i_sys]->Sumw2();

      h1_y_pt_eff_one_pP[i_cent][i_sys] = 0;
      h1_y_pt_eff_one_pM[i_cent][i_sys] = 0;
      /* if(TEfficiency::CheckConsistency(*h1_y_pt_TOF_one_pP[i_cent][i_sys], *h1_y_pt_TPC_one_pP[i_cent][i_sys])) */
      /* 	{ */
      /* 	  h1_y_pt_eff_one_pP[i_cent][i_sys] = new TEfficiency(*h1_y_pt_TOF_one_pP[i_cent][i_sys], *h1_y_pt_TPC_one_pP[i_cent][i_sys]); */
      /* 	  h1_y_pt_eff_one_pP[i_cent][i_sys]->SetTitle(Form("h1_y_pt_eff_pP_cent_[%d, %d)_y: [%1.1f, %1.1f)", cent_ref[i_cent+1], cent_ref[i_cent], ybin[3], ybin[4+1])); */
      /* 	} */
      /* if(TEfficiency::CheckConsistency(*h1_y_pt_TOF_one_pM[i_cent][i_sys], *h1_y_pt_TPC_one_pM[i_cent][i_sys])) */
      /* 	{ */
      /* 	  h1_y_pt_eff_one_pM[i_cent][i_sys] = new TEfficiency(*h1_y_pt_TOF_one_pM[i_cent][i_sys], *h1_y_pt_TPC_one_pM[i_cent][i_sys]); */
      /* 	  h1_y_pt_eff_one_pM[i_cent][i_sys]->SetTitle(Form("h1_y_pt_eff_pM_cent_[%d, %d)_y: [%1.1f, %1.1f)", cent_ref[i_cent+1], cent_ref[i_cent], ybin[3], ybin[4+1])); */
      /* 	} */

      h1_y_pt_eff_one_pP[i_cent][i_sys] = new TH1D(Form("h1_y_pt_eff_one_pP2_%d_sys_%d", i_cent, i_sys), Form("h1_y_pt_eff_one_pP_cent_[%d, %d)_y: [%1.1f, %1.1f)", cent_ref[i_cent+1], cent_ref[i_cent], ybin[3], ybin[4+1]), h1_y_pt_TOF_one_pM[i_cent][i_sys]->GetXaxis()->GetNbins(), h1_y_pt_TOF_one_pM[i_cent][i_sys]->GetXaxis()->GetXmin(), h1_y_pt_TOF_one_pM[i_cent][i_sys]->GetXaxis()->GetXmax());
      h1_y_pt_eff_one_pM[i_cent][i_sys] = new TH1D(Form("h1_y_pt_eff_one_pM2_%d_sys_%d", i_cent, i_sys), Form("h1_y_pt_eff_one_pM_cent_[%d, %d)_y: [%1.1f, %1.1f)", cent_ref[i_cent+1], cent_ref[i_cent], ybin[3], ybin[4+1]), h1_y_pt_TOF_one_pM[i_cent][i_sys]->GetXaxis()->GetNbins(), h1_y_pt_TOF_one_pM[i_cent][i_sys]->GetXaxis()->GetXmin(), h1_y_pt_TOF_one_pM[i_cent][i_sys]->GetXaxis()->GetXmax());

      h1_y_pt_eff_one_pP[i_cent][i_sys]->Divide(h1_y_pt_TOF_one_pP[i_cent][i_sys], h1_y_pt_TPC_one_pP[i_cent][i_sys], 1, 1, "B");
      h1_y_pt_eff_one_pM[i_cent][i_sys]->Divide(h1_y_pt_TOF_one_pM[i_cent][i_sys], h1_y_pt_TPC_one_pM[i_cent][i_sys], 1, 1, "B");

      /* if((string(NamePPiK) == "Proton" && string(NameRuZr) == "Ru" && i_cent == 9) && (i_sys == 2 || i_sys == 1)) f_y_pt_one_pP[i_cent][i_sys] = new TF1(Form("f_y_pt_one_pP_cent_%d_sys_%d", i_cent, i_sys), "pol2", 0.6, 1.5); */
      /* else */
      f_y_pt_one_pP[i_cent][i_sys] = new TF1(Form("f_y_pt_one_pP_cent_%d_sys_%d", i_cent, i_sys), "pol2", 0.6, 2.4);
      f_y_pt_one_draw_pP[i_cent][i_sys] = new TF1(Form("f_y_pt_one_draw_pP_cent_%d_sys_%d", i_cent, i_sys), "pol2", 0.6, 2.0); f_y_pt_one_draw_pP[i_cent][i_sys]->SetLineColor(4);
      f_y_pt_one_pP[i_cent][i_sys]->SetParLimits(0, 0.1, 1);
      f_y_pt_one_pP[i_cent][i_sys]->SetParLimits(1, -1, 1);
      f_y_pt_one_pP[i_cent][i_sys]->SetParLimits(2, -1, 1);
      /* if((string(NamePPiK) == "Proton" && string(NameRuZr) == "Ru" && i_cent == 9) && (i_sys == 2 || i_sys == 1)) f_y_pt_one_pM[i_cent][i_sys] = new TF1(Form("f_y_pt_one_pM_cent_%d_sys_%d", i_cent, i_sys), "pol2", 0.6, 1.5); */
      /* else */
      f_y_pt_one_pM[i_cent][i_sys] = new TF1(Form("f_y_pt_one_pM_cent_%d_sys_%d", i_cent, i_sys), "pol2", 0.6, 2.4);
      f_y_pt_one_draw_pM[i_cent][i_sys] = new TF1(Form("f_y_pt_one_draw_pM_cent_%d_sys_%d", i_cent, i_sys), "pol2", 0.6, 2.0); f_y_pt_one_draw_pM[i_cent][i_sys]->SetLineColor(4);
      f_y_pt_one_pM[i_cent][i_sys]->SetParLimits(0, 0.1, 1);
      f_y_pt_one_pM[i_cent][i_sys]->SetParLimits(1, -1, 1);
      f_y_pt_one_pM[i_cent][i_sys]->SetParLimits(2, -1, 1);

      /* h1_y_pt_eff_one_pP[i_cent][i_sys] = hE_y_pt_eff_one_pP[i_cent][i_sys]->GetCopyTotalHisto(); */
      h1_y_pt_eff_one_pP[i_cent][i_sys]->Fit(f_y_pt_one_pP[i_cent][i_sys], "R ");
      h1_y_pt_eff_one_pM[i_cent][i_sys]->Fit(f_y_pt_one_pM[i_cent][i_sys], "R ");

      //04082022(start):reliable cheating
      /* if((string(NamePPiK) == "Proton" && string(NameRuZr) == "Ru" && i_cent == 9) && (i_sys == 3)){ */
      if((string(NameRuZr) == "Ru" && i_cent == 9) && (i_sys == 3)){
	cheat_p0 = f_y_pt_one_pP[i_cent][i_sys]->GetParameter(0);
	cheat_p1 = f_y_pt_one_pP[i_cent][i_sys]->GetParameter(1);
	cheat_p2 = f_y_pt_one_pP[i_cent][i_sys]->GetParameter(2);
	cheat_p0_err = f_y_pt_one_pP[i_cent][i_sys]->GetParError(0);
	cheat_p1_err = f_y_pt_one_pP[i_cent][i_sys]->GetParError(1);
	cheat_p2_err = f_y_pt_one_pP[i_cent][i_sys]->GetParError(2);
      }
      /* if((string(NamePPiK) == "Proton" && string(NameRuZr) == "Ru" && i_cent == 9) && (i_sys == 1 || i_sys == 2)){ */
      if((string(NameRuZr) == "Ru" && i_cent == 9) && (i_sys == 1 || i_sys == 2)){
	f_y_pt_one_pP[i_cent][i_sys]->SetParameter(0, cheat_p0);
	f_y_pt_one_pP[i_cent][i_sys]->SetParameter(1, cheat_p1);
	f_y_pt_one_pP[i_cent][i_sys]->SetParameter(2, cheat_p2);
	f_y_pt_one_pP[i_cent][i_sys]->SetParError(0, cheat_p0_err);
	f_y_pt_one_pP[i_cent][i_sys]->SetParError(1, cheat_p1_err);
	f_y_pt_one_pP[i_cent][i_sys]->SetParError(2, cheat_p2_err);
      }
      //04082022(finish):reliable cheating
      
      p0_one_pP[i_cent][i_sys] = f_y_pt_one_pP[i_cent][i_sys]->GetParameter(0);
      p1_one_pP[i_cent][i_sys] = f_y_pt_one_pP[i_cent][i_sys]->GetParameter(1);
      p2_one_pP[i_cent][i_sys] = f_y_pt_one_pP[i_cent][i_sys]->GetParameter(2);
      p0_one_err_pP[i_cent][i_sys] = f_y_pt_one_pP[i_cent][i_sys]->GetParError(0);
      p1_one_err_pP[i_cent][i_sys] = f_y_pt_one_pP[i_cent][i_sys]->GetParError(1);
      p2_one_err_pP[i_cent][i_sys] = f_y_pt_one_pP[i_cent][i_sys]->GetParError(2);

      f_y_pt_one_draw_pP[i_cent][i_sys]->SetParameter(0, f_y_pt_one_pP[i_cent][i_sys]->GetParameter(0));
      f_y_pt_one_draw_pP[i_cent][i_sys]->SetParameter(1, f_y_pt_one_pP[i_cent][i_sys]->GetParameter(1));
      f_y_pt_one_draw_pP[i_cent][i_sys]->SetParameter(2, f_y_pt_one_pP[i_cent][i_sys]->GetParameter(2));
	
      p0_one_pM[i_cent][i_sys] = f_y_pt_one_pM[i_cent][i_sys]->GetParameter(0);
      p1_one_pM[i_cent][i_sys] = f_y_pt_one_pM[i_cent][i_sys]->GetParameter(1);
      p2_one_pM[i_cent][i_sys] = f_y_pt_one_pM[i_cent][i_sys]->GetParameter(2);
      p0_one_err_pM[i_cent][i_sys] = f_y_pt_one_pM[i_cent][i_sys]->GetParError(0);
      p1_one_err_pM[i_cent][i_sys] = f_y_pt_one_pM[i_cent][i_sys]->GetParError(1);
      p2_one_err_pM[i_cent][i_sys] = f_y_pt_one_pM[i_cent][i_sys]->GetParError(2);

      f_y_pt_one_draw_pM[i_cent][i_sys]->SetParameter(0, f_y_pt_one_pM[i_cent][i_sys]->GetParameter(0));
      f_y_pt_one_draw_pM[i_cent][i_sys]->SetParameter(1, f_y_pt_one_pM[i_cent][i_sys]->GetParameter(1));
      f_y_pt_one_draw_pM[i_cent][i_sys]->SetParameter(2, f_y_pt_one_pM[i_cent][i_sys]->GetParameter(2));
    }
  }
  //Fit parameters plotted with respect to centrality
  TGraphErrors *gr_y_pt_eff_one_pP_p0[nsys], *gr_y_pt_eff_one_pP_p1[nsys], *gr_y_pt_eff_one_pP_p2[nsys];
  TGraphErrors *gr_y_pt_eff_one_pM_p0[nsys], *gr_y_pt_eff_one_pM_p1[nsys], *gr_y_pt_eff_one_pM_p2[nsys];
  double p0_one_pP_cent[ncent], p1_one_pP_cent[ncent], p2_one_pP_cent[ncent];
  double p0_one_err_pP_cent[ncent], p1_one_err_pP_cent[ncent], p2_one_err_pP_cent[ncent];
  double p0_one_pM_cent[ncent], p1_one_pM_cent[ncent], p2_one_pM_cent[ncent];
  double p0_one_err_pM_cent[ncent], p1_one_err_pM_cent[ncent], p2_one_err_pM_cent[ncent];

  TF1 *f1_p0_one_pP_cent[nsys], *f1_p1_one_pP_cent[nsys], *f1_p2_one_pP_cent[nsys];
  TF1 *f1_p0_one_pM_cent[nsys], *f1_p1_one_pM_cent[nsys], *f1_p2_one_pM_cent[nsys];
  double p0_one_par0_pP[nsys], p0_one_par1_pP[nsys], p0_one_par2_pP[nsys];
  double p1_one_par0_pP[nsys], p1_one_par1_pP[nsys], p1_one_par2_pP[nsys];
  double p2_one_par0_pP[nsys], p2_one_par1_pP[nsys], p2_one_par2_pP[nsys];
  double p0_one_par0_pM[nsys], p0_one_par1_pM[nsys], p0_one_par2_pM[nsys];
  double p1_one_par0_pM[nsys], p1_one_par1_pM[nsys], p1_one_par2_pM[nsys];
  double p2_one_par0_pM[nsys], p2_one_par1_pM[nsys], p2_one_par2_pM[nsys];
  
  for(int i_sys = 0 ; i_sys < nsys ; i_sys++){

    /* f1_p0_one_pP_cent[i_sys] = new TF1(Form("f1_p0_one_pP_cent_sys_%d", i_sys), "pol1", 0, 500); */
    /* f1_p1_one_pP_cent[i_sys] = new TF1(Form("f1_p1_one_pP_cent_sys_%d", i_sys), "pol1", 0, 500); */
    /* f1_p2_one_pP_cent[i_sys] = new TF1(Form("f1_p2_one_pP_cent_sys_%d", i_sys), "pol1", 0, 500); */
    /* f1_p0_one_pM_cent[i_sys] = new TF1(Form("f1_p0_one_pM_cent_sys_%d", i_sys), "pol1", 0, 500); */
    /* f1_p1_one_pM_cent[i_sys] = new TF1(Form("f1_p1_one_pM_cent_sys_%d", i_sys), "pol1", 0, 500); */
    /* f1_p2_one_pM_cent[i_sys] = new TF1(Form("f1_p2_one_pM_cent_sys_%d", i_sys), "pol1", 0, 500); */

    f1_p0_one_pP_cent[i_sys] = new TF1(Form("f1_p0_one_pP_cent_sys_%d", i_sys), "pol2", 0, 500);
    f1_p1_one_pP_cent[i_sys] = new TF1(Form("f1_p1_one_pP_cent_sys_%d", i_sys), "pol2", 0, 500);
    f1_p2_one_pP_cent[i_sys] = new TF1(Form("f1_p2_one_pP_cent_sys_%d", i_sys), "pol2", 0, 500);
    f1_p0_one_pM_cent[i_sys] = new TF1(Form("f1_p0_one_pM_cent_sys_%d", i_sys), "pol2", 0, 500);
    f1_p1_one_pM_cent[i_sys] = new TF1(Form("f1_p1_one_pM_cent_sys_%d", i_sys), "pol2", 0, 500);
    f1_p2_one_pM_cent[i_sys] = new TF1(Form("f1_p2_one_pM_cent_sys_%d", i_sys), "pol2", 0, 500);

    for(int i_cent = 0 ; i_cent < ncent ; i_cent++) {
      p0_one_pP_cent[i_cent] = p0_one_pP[i_cent][i_sys]; p1_one_pP_cent[i_cent] = p1_one_pP[i_cent][i_sys]; p2_one_pP_cent[i_cent] = p2_one_pP[i_cent][i_sys];
      p0_one_err_pP_cent[i_cent] = p0_one_err_pP[i_cent][i_sys]; p1_one_err_pP_cent[i_cent] = p1_one_err_pP[i_cent][i_sys]; p2_one_err_pP_cent[i_cent] = p2_one_err_pP[i_cent][i_sys];
      p0_one_pM_cent[i_cent] = p0_one_pM[i_cent][i_sys]; p1_one_pM_cent[i_cent] = p1_one_pM[i_cent][i_sys]; p2_one_pM_cent[i_cent] = p2_one_pM[i_cent][i_sys];
      p0_one_err_pM_cent[i_cent] = p0_one_err_pM[i_cent][i_sys]; p1_one_err_pM_cent[i_cent] = p1_one_err_pM[i_cent][i_sys]; p2_one_err_pM_cent[i_cent] = p2_one_err_pM[i_cent][i_sys];
    }
    gr_y_pt_eff_one_pP_p0[i_sys] = new TGraphErrors(ncent, ref3_avg_arr, p0_one_pP_cent, 0, p0_one_err_pP_cent); gr_y_pt_eff_one_pP_p0[i_sys]->RemovePoint(0);
    gr_y_pt_eff_one_pP_p1[i_sys] = new TGraphErrors(ncent, ref3_avg_arr, p1_one_pP_cent, 0, p1_one_err_pP_cent); gr_y_pt_eff_one_pP_p1[i_sys]->RemovePoint(0);
    gr_y_pt_eff_one_pP_p2[i_sys] = new TGraphErrors(ncent, ref3_avg_arr, p2_one_pP_cent, 0, p2_one_err_pP_cent); gr_y_pt_eff_one_pP_p2[i_sys]->RemovePoint(0);
    gr_y_pt_eff_one_pP_p0[i_sys]->SetMarkerStyle(8);
    gr_y_pt_eff_one_pP_p1[i_sys]->SetMarkerStyle(8);
    gr_y_pt_eff_one_pP_p2[i_sys]->SetMarkerStyle(8);
    gr_y_pt_eff_one_pP_p0[i_sys]->SetTitle(Form("p0, pP, y: [%1.1f, %1.1f), dca_cut = %1.1f, nhf_cut = %d, nsp_cut = %1.1f", ybin[3], ybin[4+1], dca_sys[i_sys], nhf_sys[i_sys], nsp_sys[i_sys]));;
    gr_y_pt_eff_one_pP_p1[i_sys]->SetTitle(Form("p1, pP, y: [%1.1f, %1.1f), dca_cut = %1.1f, nhf_cut = %d, nsp_cut = %1.1f", ybin[3], ybin[4+1], dca_sys[i_sys], nhf_sys[i_sys], nsp_sys[i_sys]));;
    gr_y_pt_eff_one_pP_p2[i_sys]->SetTitle(Form("p2, pP, y: [%1.1f, %1.1f), dca_cut = %1.1f, nhf_cut = %d, nsp_cut = %1.1f", ybin[3], ybin[4+1], dca_sys[i_sys], nhf_sys[i_sys], nsp_sys[i_sys]));;
    gr_y_pt_eff_one_pP_p0[i_sys]->GetXaxis()->SetTitle("RefMult3");
    gr_y_pt_eff_one_pP_p1[i_sys]->GetXaxis()->SetTitle("RefMult3");
    gr_y_pt_eff_one_pP_p2[i_sys]->GetXaxis()->SetTitle("RefMult3");
    gr_y_pt_eff_one_pM_p0[i_sys] = new TGraphErrors(ncent, ref3_avg_arr, p0_one_pM_cent, 0, p0_one_err_pM_cent); gr_y_pt_eff_one_pM_p0[i_sys]->RemovePoint(0);
    gr_y_pt_eff_one_pM_p1[i_sys] = new TGraphErrors(ncent, ref3_avg_arr, p1_one_pM_cent, 0, p1_one_err_pM_cent); gr_y_pt_eff_one_pM_p1[i_sys]->RemovePoint(0);
    gr_y_pt_eff_one_pM_p2[i_sys] = new TGraphErrors(ncent, ref3_avg_arr, p2_one_pM_cent, 0, p2_one_err_pM_cent); gr_y_pt_eff_one_pM_p2[i_sys]->RemovePoint(0);
    gr_y_pt_eff_one_pM_p0[i_sys]->SetMarkerStyle(8);
    gr_y_pt_eff_one_pM_p1[i_sys]->SetMarkerStyle(8);
    gr_y_pt_eff_one_pM_p2[i_sys]->SetMarkerStyle(8);
    gr_y_pt_eff_one_pM_p0[i_sys]->SetTitle(Form("p0, pM, y: [%1.1f, %1.1f), dca_cut = %1.1f, nhf_cut = %d, nsp_cut = %1.1f", ybin[3], ybin[4+1], dca_sys[i_sys], nhf_sys[i_sys], nsp_sys[i_sys]));;
    gr_y_pt_eff_one_pM_p1[i_sys]->SetTitle(Form("p1, pM, y: [%1.1f, %1.1f), dca_cut = %1.1f, nhf_cut = %d, nsp_cut = %1.1f", ybin[3], ybin[4+1], dca_sys[i_sys], nhf_sys[i_sys], nsp_sys[i_sys]));;
    gr_y_pt_eff_one_pM_p2[i_sys]->SetTitle(Form("p2, pM, y: [%1.1f, %1.1f), dca_cut = %1.1f, nhf_cut = %d, nsp_cut = %1.1f", ybin[3], ybin[4+1], dca_sys[i_sys], nhf_sys[i_sys], nsp_sys[i_sys]));;
    gr_y_pt_eff_one_pM_p0[i_sys]->GetXaxis()->SetTitle("RefMult3");
    gr_y_pt_eff_one_pM_p1[i_sys]->GetXaxis()->SetTitle("RefMult3");
    gr_y_pt_eff_one_pM_p2[i_sys]->GetXaxis()->SetTitle("RefMult3");

    gr_y_pt_eff_one_pP_p0[i_sys]->Fit(f1_p0_one_pP_cent[i_sys], "FR"); p0_one_par0_pP[i_sys] = f1_p0_one_pP_cent[i_sys]->GetParameter(0); p0_one_par1_pP[i_sys] = f1_p0_one_pP_cent[i_sys]->GetParameter(1); p0_one_par2_pP[i_sys] = f1_p0_one_pP_cent[i_sys]->GetParameter(2);
    gr_y_pt_eff_one_pP_p1[i_sys]->Fit(f1_p1_one_pP_cent[i_sys], "FR"); p1_one_par0_pP[i_sys] = f1_p1_one_pP_cent[i_sys]->GetParameter(0); p1_one_par1_pP[i_sys] = f1_p1_one_pP_cent[i_sys]->GetParameter(1); p1_one_par2_pP[i_sys] = f1_p1_one_pP_cent[i_sys]->GetParameter(2);
    gr_y_pt_eff_one_pP_p2[i_sys]->Fit(f1_p2_one_pP_cent[i_sys], "FR"); p2_one_par0_pP[i_sys] = f1_p2_one_pP_cent[i_sys]->GetParameter(0); p2_one_par1_pP[i_sys] = f1_p2_one_pP_cent[i_sys]->GetParameter(1); p2_one_par2_pP[i_sys] = f1_p2_one_pP_cent[i_sys]->GetParameter(2);

    gr_y_pt_eff_one_pM_p0[i_sys]->Fit(f1_p0_one_pM_cent[i_sys], "FR"); p0_one_par0_pM[i_sys] = f1_p0_one_pM_cent[i_sys]->GetParameter(0); p0_one_par1_pM[i_sys] = f1_p0_one_pM_cent[i_sys]->GetParameter(1); p0_one_par2_pM[i_sys] = f1_p0_one_pM_cent[i_sys]->GetParameter(2);
    gr_y_pt_eff_one_pM_p1[i_sys]->Fit(f1_p1_one_pM_cent[i_sys], "FR"); p1_one_par0_pM[i_sys] = f1_p1_one_pM_cent[i_sys]->GetParameter(0); p1_one_par1_pM[i_sys] = f1_p1_one_pM_cent[i_sys]->GetParameter(1); p1_one_par2_pM[i_sys] = f1_p1_one_pM_cent[i_sys]->GetParameter(2);
    gr_y_pt_eff_one_pM_p2[i_sys]->Fit(f1_p2_one_pM_cent[i_sys], "FR"); p2_one_par0_pM[i_sys] = f1_p2_one_pM_cent[i_sys]->GetParameter(0); p2_one_par1_pM[i_sys] = f1_p2_one_pM_cent[i_sys]->GetParameter(1); p2_one_par2_pM[i_sys] = f1_p2_one_pM_cent[i_sys]->GetParameter(2);

  }//for(int i_sys = 0 ; i_sys < nsys ; i_sys++){

  TCanvas *c_y_pt_pP_oney[nsys], *c_y_pt_pM_oney[nsys];
  for(int i_sys = 0 ; i_sys < nsys ; i_sys++){
    /* if(i_sys == 6){ */
    c_y_pt_pP_oney[i_sys] = new TCanvas(Form("c_y_pt_pP_oney_sys_%d", i_sys), Form("c_y_pt_pP_oney_sys_%d", i_sys), 5000, 2000);
    c_y_pt_pP_oney[i_sys]->Divide(5,2);
    c_y_pt_pM_oney[i_sys] = new TCanvas(Form("c_y_pt_pM_oney_sys_%d", i_sys), Form("c_y_pt_pM_oney_sys_%d", i_sys), 5000, 2000);
    c_y_pt_pM_oney[i_sys]->Divide(5,2);
    for(int i_cent = 0 ; i_cent < ncent ; i_cent++){
      c_y_pt_pP_oney[i_sys]->cd(i_cent + 1);
      /* h1_y_pt_eff_one_pP[i_cent][i_sys]->GetYaxis()->SetRangeUser(0.7, 0.8); */
      h1_y_pt_eff_one_pP[i_cent][i_sys]->GetXaxis()->SetRangeUser(0.8, 2.0);
      h1_y_pt_eff_one_pP[i_cent][i_sys]->Draw();
      f_y_pt_one_draw_pP[i_cent][i_sys]->Draw("SAME");
      c_y_pt_pM_oney[i_sys]->cd(i_cent + 1);
      h1_y_pt_eff_one_pM[i_cent][i_sys]->GetXaxis()->SetRangeUser(0.8, 2.0);
      h1_y_pt_eff_one_pM[i_cent][i_sys]->Draw();
      f_y_pt_one_draw_pM[i_cent][i_sys]->Draw("SAME");
    }
    c_y_pt_pP_oney[i_sys]->Print(Form("output/TOF/1D/c_y_pt_pP_oney_%s_%s_sys_%d.pdf", NamePPiK, NameRuZr, i_sys));
    c_y_pt_pM_oney[i_sys]->Print(Form("output/TOF/1D/c_y_pt_pM_oney_%s_%s_sys_%d.pdf", NamePPiK, NameRuZr, i_sys));
    /* }//if(i_sys == 6){  */
  }
  
  TCanvas *c_y_pt_p012_oney_cent_pP[nsys], *c_y_pt_p012_oney_cent_pM[nsys];
  for(int i_sys = 0 ; i_sys < nsys ; i_sys++){
    /* if(i_sys == 6){ */
    c_y_pt_p012_oney_cent_pP[i_sys] = new TCanvas(Form("c_y_pt_p012_oney_cent_pP_sys_%d", i_sys), Form("c_y_pt_p012_oney_cent_pP_sys_%d", i_sys), 1500, 500);
    c_y_pt_p012_oney_cent_pP[i_sys]->Divide(3,1);
    c_y_pt_p012_oney_cent_pP[i_sys]->cd(1); gr_y_pt_eff_one_pP_p0[i_sys]->Draw("AP");
    c_y_pt_p012_oney_cent_pP[i_sys]->cd(2); gr_y_pt_eff_one_pP_p1[i_sys]->Draw("AP");
    c_y_pt_p012_oney_cent_pP[i_sys]->cd(3); gr_y_pt_eff_one_pP_p2[i_sys]->Draw("AP");

    c_y_pt_p012_oney_cent_pM[i_sys] = new TCanvas(Form("c_y_pt_p012_oney_cent_pM_sys_%d", i_sys), Form("c_y_pt_p012_oney_cent_pM_sys_%d", i_sys), 1500, 500);
    c_y_pt_p012_oney_cent_pM[i_sys]->Divide(3,1);
    c_y_pt_p012_oney_cent_pM[i_sys]->cd(1); gr_y_pt_eff_one_pM_p0[i_sys]->Draw("AP");
    c_y_pt_p012_oney_cent_pM[i_sys]->cd(2); gr_y_pt_eff_one_pM_p1[i_sys]->Draw("AP");
    c_y_pt_p012_oney_cent_pM[i_sys]->cd(3); gr_y_pt_eff_one_pM_p2[i_sys]->Draw("AP");

    c_y_pt_p012_oney_cent_pP[i_sys]->Print(Form("output/TOF/1D/c_y_pt_p012_oney_cent_pP_%s_%s_sys_%d.pdf", NamePPiK, NameRuZr, i_sys));
    c_y_pt_p012_oney_cent_pM[i_sys]->Print(Form("output/TOF/1D/c_y_pt_p012_oney_cent_pM_%s_%s_sys_%d.pdf", NamePPiK, NameRuZr, i_sys));

    f_out[i_sys] = new TFile(Form("output/TOF/1D/file/gr/gr_%s_%s_dca_%1.1f_nhf_%d_nsp_%1.1f.root", NamePPiK, NameRuZr, dca_sys[i_sys], nhf_sys[i_sys], nsp_sys[i_sys]), "RECREATE");
    /* f_out[i_sys] = new TFile(Form("output/TOF/1D/file/gr/gr_%s_%s_sys_%d.root", NamePPiK, NameRuZr, i_sys), "RECREATE"); */
    gr_y_pt_eff_one_pP_p0[i_sys]->Write("gr_y_pt_eff_one_pP_p0");
    gr_y_pt_eff_one_pP_p1[i_sys]->Write("gr_y_pt_eff_one_pP_p1");
    gr_y_pt_eff_one_pP_p2[i_sys]->Write("gr_y_pt_eff_one_pP_p2");
    gr_y_pt_eff_one_pM_p0[i_sys]->Write("gr_y_pt_eff_one_pM_p0");
    gr_y_pt_eff_one_pM_p1[i_sys]->Write("gr_y_pt_eff_one_pM_p1");
    gr_y_pt_eff_one_pM_p2[i_sys]->Write("gr_y_pt_eff_one_pM_p2");
    f_out[i_sys]->Write();
    f_out[i_sys]->Close();
    /* }//if(i_sys == 6){  */
  }

  
  for(int i_sys = 0 ; i_sys < nsys ; i_sys++){
    /* if(i_sys == 6){ */
    myfile.open(Form("output/TOF/1D/file/eff_pt_dep_cent_fit_oneybin_%s_%s_dca_%1.1f_nhf_%d_nsp_%1.1f.txt", NamePPiK, NameRuZr, dca_sys[i_sys], nhf_sys[i_sys], nsp_sys[i_sys]));
    /* myfile<<"ybinlow\tybinhi\tp0_par0\tp0_par1\tp0_par2\tp1_par0\tp1_par1\tp1_par2\tp2_par0\tp2_par1\tp2_par2"<<endl; */
    if(string(NamePPiK) == "Proton" || string(NamePPiK) == "Piplus" || string(NamePPiK) == "Kplus"){
      myfile<<ybin[3]<<"\t"<<ybin[4+1]<<"\t"<<p0_one_par0_pP[i_sys]<<"\t"<<p0_one_par1_pP[i_sys]<<"\t"<<p0_one_par2_pP[i_sys]<<"\t"<<p1_one_par0_pP[i_sys]<<"\t"<<p1_one_par1_pP[i_sys]<<"\t"<<p1_one_par2_pP[i_sys]<<"\t"<<p2_one_par0_pP[i_sys]<<"\t"<<p2_one_par1_pP[i_sys]<<"\t"<<p2_one_par2_pP[i_sys]<<endl;
    }
    else if(string(NamePPiK) == "AntiProton" || string(NamePPiK) == "Piminus" || string(NamePPiK) == "Kminus"){
      myfile<<ybin[3]<<"\t"<<ybin[4+1]<<"\t"<<p0_one_par0_pM[i_sys]<<"\t"<<p0_one_par1_pM[i_sys]<<"\t"<<p0_one_par2_pM[i_sys]<<"\t"<<p1_one_par0_pM[i_sys]<<"\t"<<p1_one_par1_pM[i_sys]<<"\t"<<p1_one_par2_pM[i_sys]<<"\t"<<p2_one_par0_pM[i_sys]<<"\t"<<p2_one_par1_pM[i_sys]<<"\t"<<p2_one_par2_pM[i_sys]<<endl;
    }
    myfile.close();
    /* }//if(i_sys == 6){  */
  }
  //25062022(finish)

  TH1D *h1_y_pt_eff_one_pP2[ncent][nsys], *h1_y_pt_eff_one_pM2[ncent][nsys];
  for(int i_sys = 0 ; i_sys < nsys ; i_sys++){
    for(int i_cent = 0 ; i_cent < ncent ; i_cent++){
      h1_y_pt_eff_one_pP2[i_cent][i_sys] = new TH1D(Form("h1_y_pt_eff_one_pP_%d_sys_%d", i_cent, i_sys), Form("h1_y_pt_eff_one_pP_cent_[%d, %d)_y: [%1.1f, %1.1f)", cent_ref[i_cent+1], cent_ref[i_cent], ybin[3], ybin[4+1]), h1_y_pt_TOF_one_pM[i_cent][i_sys]->GetXaxis()->GetNbins(), h1_y_pt_TOF_one_pM[i_cent][i_sys]->GetXaxis()->GetXmin(), h1_y_pt_TOF_one_pM[i_cent][i_sys]->GetXaxis()->GetXmax());
      h1_y_pt_eff_one_pM2[i_cent][i_sys] = new TH1D(Form("h1_y_pt_eff_one_pM_%d_sys_%d", i_cent, i_sys), Form("h1_y_pt_eff_one_pM_cent_[%d, %d)_y: [%1.1f, %1.1f)", cent_ref[i_cent+1], cent_ref[i_cent], ybin[3], ybin[4+1]), h1_y_pt_TOF_one_pM[i_cent][i_sys]->GetXaxis()->GetNbins(), h1_y_pt_TOF_one_pM[i_cent][i_sys]->GetXaxis()->GetXmin(), h1_y_pt_TOF_one_pM[i_cent][i_sys]->GetXaxis()->GetXmax());

      h1_y_pt_eff_one_pP2[i_cent][i_sys]->Divide(h1_y_pt_TOF_one_pP[i_cent][i_sys], h1_y_pt_TPC_one_pP[i_cent][i_sys], 1, 1, "B");
      h1_y_pt_eff_one_pM2[i_cent][i_sys]->Divide(h1_y_pt_TOF_one_pM[i_cent][i_sys], h1_y_pt_TPC_one_pM[i_cent][i_sys], 1, 1, "B");
    }
  }
  for(int i_sys = 0 ; i_sys < nsys ; i_sys++){
    f_out[i_sys] = new TFile(Form("output/TOF/1D/file/root/%s_%s_dca_%1.1f_nhf_%d_nsp_%1.1f.root", NamePPiK, NameRuZr, dca_sys[i_sys], nhf_sys[i_sys], nsp_sys[i_sys]), "RECREATE");
    for(int i_cent = 0 ; i_cent < ncent ; i_cent++){

      /* h1_y_pt_eff_one_pP[i_cent][i_sys]->Write(); */
      /* h1_y_pt_eff_one_pM[i_cent][i_sys]->Write(); */
      /* h1_y_pt_eff_one_pP2[i_cent][i_sys]->Write(Form("h1_y_pt_eff_one_pP_%d", i_cent)); */
      /* h1_y_pt_eff_one_pM2[i_cent][i_sys]->Write(Form("h1_y_pt_eff_one_pM_%d", i_cent)); */
      h1_y_pt_eff_one_pP2[i_cent][i_sys]->Write();
      h1_y_pt_eff_one_pM2[i_cent][i_sys]->Write();
      h1_y_pt_TOF_one_pP[i_cent][i_sys]->Write();
      h1_y_pt_TPC_one_pP[i_cent][i_sys]->Write();
    }
    f_out[i_sys]->Write();
    f_out[i_sys]->Close();
  }

  }

