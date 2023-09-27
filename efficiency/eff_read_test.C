void eff_read_test(const char* NamePPiK = "Proton", const char* NameRuZr = "Ru"){//, int dca_cut = 10, int nhf_cut = 20){
  const int ncent = 10;
  const int nsys = 13;// 3 cuts with 5 variable ( -1 nominal cut): 3 * (5-1) + 1(nominal cut) = 13

  int cent_ref3[11];
  cent_ref3[0] = 1000;
  cent_ref3[1] = 700;
  if(string(NameRuZr) == "Ru"){
    cent_ref3[2] = 439;//0-5%
    cent_ref3[3] = 367;//5-10%
    cent_ref3[4] = 258;//10-20%
    cent_ref3[5] = 178;//20-30%
    cent_ref3[6] = 118;//30-40%
    cent_ref3[7] =  75;//40-50%
    cent_ref3[8] =  45;//50-60%
    cent_ref3[9] =  26;//60-70%
    cent_ref3[10] = 14;//70-80%
  }
  if(string(NameRuZr) == "Zr"){
    cent_ref3[2] =  435;//0-5%
    cent_ref3[3] =  363;//5-10%
    cent_ref3[4] =  252;//10-20%
    cent_ref3[5] =  171;//20-30%
    cent_ref3[6] =  113;//30-40%
    cent_ref3[7] =   71;//40-50%
    cent_ref3[8] =   42;//50-60%
    cent_ref3[9] =   24;//60-70%
    cent_ref3[10] =  13;//70-80%
  }

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
	  cut_counter++;}//if statement ends
      }//nsp loop ends
    }//nhf loop ends
  }//dca loop ends
  
  TFile *f_glauber_hyb = new TFile(Form("/Users/hosanko/playground/star/anal/Coll/isobar/ZrZrRuRu200_2018/charge/GlauberFit/draw/output/hybrid/ref3/%s_hybrid.root", NameRuZr), "READ");
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
      ref3_avg_arr[i_cent] += i_mult * h1_ref3_hyb->GetBinContent(i_mult);
      cent_evt[i_cent] += h1_ref3_hyb->GetBinContent(i_mult);
 
    }
    cout<<ref3_avg_arr[i_cent]<<"/"<<cent_evt[i_cent]<<" = "<<ref3_avg_arr[i_cent]/cent_evt[i_cent]<<endl;
    ref3_avg_arr[i_cent] /= cent_evt[i_cent];
    if(isnan(ref3_avg)) ref3_avg_arr[i_cent] = 0.;
  }//for(int i_cent = 0 ; i_cent < ncent ; i_cent++){

  cout<<Form("double ref3_avg_%s[ncent];", NameRuZr)<<endl;
  for(int i_cent = 0 ; i_cent < ncent ; i_cent++){
    cout<<Form("ref3_avg_%s[%d] = %f;",NameRuZr, i_cent, ref3_avg_arr[i_cent])<<endl;
  }

  
  /* TFile *f_tpc_in = new TFile("output/TPC/file/root/AntiProton_Ru_dca_10_nhitsfit_15.root", "READ"); */
  TFile *f_tpc_in = new TFile(Form("../../Ashish/25082022/25082022_1/output/TPC/file/root/%s_%s_dca_10_nhitsfit_20.root", NamePPiK, NameRuZr), "READ");
  TFile *f_tpc_in_hs = new TFile(Form("output/TPC/file/root/%s_%s_dca_10_nhitsfit_20.root", NamePPiK, NameRuZr), "READ");
  f_tpc_in->cd();
  TGraphAsymmErrors *h1_y_pt_eff_tpc[ncent];
  TH1D *h1_y_pt_eff_tpc_hs[ncent];
  for(int i_cent = 0 ; i_cent < ncent ; i_cent++){
    h1_y_pt_eff_tpc[i_cent] = (TGraphAsymmErrors * )f_tpc_in->Get(Form("h1_y_pt_eff_one_%d", i_cent));
    h1_y_pt_eff_tpc_hs[i_cent] = (TH1D * )f_tpc_in_hs->Get(Form("h1_y_pt_eff_one_%d", i_cent));
  }

  TFile *f_tof_in[nsys];
  TH1D *h1_y_pt_eff_tof_pP[ncent][nsys];
  TH1D *h1_y_pt_eff_tof_pM[ncent][nsys];
  for(int i_sys = 0 ; i_sys < nsys ; i_sys++){
    f_tof_in[i_sys] = new TFile(Form("output/TOF/1D/file/root/%s_%s_dca_%1.1f_nhf_%d_nsp_%1.1f.root", NamePPiK, NameRuZr, dca_sys[i_sys], nhf_sys[i_sys], nsp_sys[i_sys]), "READ");
    for(int i_cent = 0 ; i_cent < ncent ; i_cent++){
      h1_y_pt_eff_tof_pP[i_cent][i_sys] = (TH1D *)f_tof_in[i_sys]->Get(Form("h1_y_pt_eff_one_pP_%d", i_cent));
      h1_y_pt_eff_tof_pM[i_cent][i_sys] = (TH1D *)f_tof_in[i_sys]->Get(Form("h1_y_pt_eff_one_pM_%d", i_cent));
    }
  }
  
  cout<<"\n\n ################# TPC TEST #################"<<endl;
  const int npt = 500;
  double x1[ncent][npt];
  double y1[ncent][npt];
  double y1_hs[ncent][npt];
  for(int i_pt = 0 ; i_pt < npt ; i_pt++){
    for(int i_cent = 0 ; i_cent < ncent ; i_cent++){
      /* cout<<h1_y_pt_eff_tpc[1]->GetBinContent(h1_y_pt_eff_tpc[1]->FindBin(1.0*i_pt/100))<<endl; */
      x1[i_cent][i_pt] = 1.0*i_pt/100;
      /* y1[i_cent][i_pt] = h1_y_pt_eff_tpc[i_cent]->GetBinContent(h1_y_pt_eff_tpc[i_cent]->FindBin(1.0*i_pt/100)); */
      y1[i_cent][i_pt] = h1_y_pt_eff_tpc[i_cent]->Eval(1.0*i_pt/100);
      y1_hs[i_cent][i_pt] = h1_y_pt_eff_tpc_hs[i_cent]->Interpolate(1.0*i_pt/100);
    }
  }

  /* TGraph *gr1 = new TGraph(npt, x1, y1); */
  TGraph *gr1[ncent];
  TGraph *gr1_hs[ncent];
  for(int i_cent = 0 ; i_cent < ncent ; i_cent++){
    gr1[i_cent] = new TGraph(npt, x1[i_cent], y1[i_cent]);
    gr1_hs[i_cent] = new TGraph(npt, x1[i_cent], y1_hs[i_cent]);
    gr1[i_cent]->SetTitle(Form("RefMult3: [%d, %d)", cent_ref3[i_cent+1], cent_ref3[i_cent]));
    gr1[i_cent]->GetXaxis()->SetTitle("p_{T} [GeV/c]");
    gr1[i_cent]->SetMarkerStyle(8);
    gr1[i_cent]->SetMarkerSize(0.5);
    gr1_hs[i_cent]->SetMarkerStyle(8);
    gr1[i_cent]->SetMarkerColor(2);
    gr1_hs[i_cent]->SetMarkerColor(1);
    gr1_hs[i_cent]->SetMarkerSize(0.5);
  }

  
  TFile *f_compare_ashish[10];// = new TFile(Form("output/compare_Ashish/file/eff_ref3_%d.root", 32), "READ");
  TF1 *f1_tpc_p_ashish[10];// = (TF1*)f_compare_ashish->Get("f1_tpc_p_ashish");
  TF1 *f1_tpc_m_ashish[10];// = (TF1*)f_compare_ashish->Get("f1_tpc_m_ashish");
  TF1 *f1_tof_p_ashish[10];// = (TF1*)f_compare_ashish->Get("f1_tof_p_ashish");
  TF1 *f1_tof_m_ashish[10];// = (TF1*)f_compare_ashish->Get("f1_tof_m_ashish");
  //  f_compare_ashish->Close();

  f_compare_ashish[0] = new TFile(Form("output/compare_Ashish/file/eff_ref3_%d.root", 768), "READ");
  f_compare_ashish[1] = new TFile(Form("output/compare_Ashish/file/eff_ref3_%d.root", 489), "READ");
  f_compare_ashish[2] = new TFile(Form("output/compare_Ashish/file/eff_ref3_%d.root", 401), "READ");
  f_compare_ashish[3] = new TFile(Form("output/compare_Ashish/file/eff_ref3_%d.root", 309), "READ");
  f_compare_ashish[4] = new TFile(Form("output/compare_Ashish/file/eff_ref3_%d.root", 216), "READ");
  f_compare_ashish[5] = new TFile(Form("output/compare_Ashish/file/eff_ref3_%d.root", 146), "READ");
  f_compare_ashish[6] = new TFile(Form("output/compare_Ashish/file/eff_ref3_%d.root",  95), "READ");
  f_compare_ashish[7] = new TFile(Form("output/compare_Ashish/file/eff_ref3_%d.root",  58), "READ");
  f_compare_ashish[8] = new TFile(Form("output/compare_Ashish/file/eff_ref3_%d.root",  34), "READ");
  f_compare_ashish[9] = new TFile(Form("output/compare_Ashish/file/eff_ref3_%d.root",  19), "READ");
  for(int i_cent = 0 ; i_cent < ncent ; i_cent++){
    f1_tpc_p_ashish[i_cent] = (TF1*)f_compare_ashish[i_cent]->Get("f1_tpc_p_ashish"); f1_tpc_p_ashish[i_cent]->SetLineWidth(1);
    f1_tpc_m_ashish[i_cent] = (TF1*)f_compare_ashish[i_cent]->Get("f1_tpc_m_ashish"); f1_tpc_m_ashish[i_cent]->SetLineWidth(1);
    f1_tof_p_ashish[i_cent] = (TF1*)f_compare_ashish[i_cent]->Get("f1_tof_p_ashish"); f1_tof_p_ashish[i_cent]->SetLineWidth(1);
    f1_tof_m_ashish[i_cent] = (TF1*)f_compare_ashish[i_cent]->Get("f1_tof_m_ashish"); f1_tof_m_ashish[i_cent]->SetLineWidth(1);
    f_compare_ashish[i_cent]->Close();
  }

  double eff_diff_ashish[ncent][npt];
  double eff_diff_hosan[ncent][npt];
  double eff_diff_as_hs[ncent][npt];
  double int_diff_aspar_hs_ncent[ncent];
  double int_diff_as_hs_ncent[ncent];
  double int_aspar[ncent];
  double int_as[ncent];
  double int_hs[ncent];
  for(int i_cent = 0 ; i_cent < ncent ; i_cent++){
    double int_diff_aspar_hs = 0;
    double int_diff_as_hs = 0;
    double int_aspar_ = 0;
    double int_as_ = 0;
    double int_hs_ = 0;
    double denome = 0;
    for(int i_pt = 0 ; i_pt < npt ; i_pt++){
      if(string(NamePPiK) == "Proton"){
	eff_diff_ashish[i_cent][i_pt] = f1_tpc_p_ashish[i_cent]->Eval(1.0*i_pt/100) - gr1[i_cent]->Eval(1.0*i_pt/100);
	eff_diff_hosan[i_cent][i_pt] = f1_tpc_p_ashish[i_cent]->Eval(1.0*i_pt/100) - gr1_hs[i_cent]->Eval(1.0*i_pt/100);
	int_diff_aspar_hs += (f1_tpc_p_ashish[i_cent]->Eval(1.0*i_pt/100) - gr1_hs[i_cent]->Eval(1.0*i_pt/100))*1./100.;
	if(1.0*i_pt/100 >= 0.4 && 1.0*i_pt/100 < 2.0){
	  int_aspar_ += (f1_tpc_p_ashish[i_cent]->Eval(1.0*i_pt/100))*1./100.;
	}
      }
      else if(string(NamePPiK) == "AntiProton"){
	eff_diff_ashish[i_cent][i_pt] = f1_tpc_m_ashish[i_cent]->Eval(1.0*i_pt/100) - gr1[i_cent]->Eval(1.0*i_pt/100);
	eff_diff_hosan[i_cent][i_pt] = f1_tpc_m_ashish[i_cent]->Eval(1.0*i_pt/100) - gr1_hs[i_cent]->Eval(1.0*i_pt/100);
	int_diff_aspar_hs += (f1_tpc_m_ashish[i_cent]->Eval(1.0*i_pt/100) - gr1_hs[i_cent]->Eval(1.0*i_pt/100))*1./100.;
	if(1.0*i_pt/100 >= 0.4 && 1.0*i_pt/100 < 2.0){
	  int_aspar_ += (f1_tpc_m_ashish[i_cent]->Eval(1.0*i_pt/100))*1./100.;
	}
      }
      eff_diff_as_hs[i_cent][i_pt] = gr1[i_cent]->Eval(1.0*i_pt/100) - gr1_hs[i_cent]->Eval(1.0*i_pt/100);
      if(1.0*i_pt/100 >= 0.4 && 1.0*i_pt/100 < 2.0){
	int_diff_as_hs += (gr1[i_cent]->Eval(1.0*i_pt/100) - gr1_hs[i_cent]->Eval(1.0*i_pt/100))*1./100.;
	int_as_ += gr1[i_cent]->Eval(1.0*i_pt/100)*1./100.;
	int_hs_ += gr1_hs[i_cent]->Eval(1.0*i_pt/100)*1./100.;
	denome += 1./100.;
      }
    }
    /* cout<<int_diff_as_hs/denome<<", "<<int_diff_aspar_hs/denome<<endl; */
    int_diff_aspar_hs_ncent[i_cent] = int_diff_aspar_hs/denome;
    int_diff_as_hs_ncent[i_cent] = int_diff_as_hs/denome;
    int_aspar[i_cent] = int_aspar_/denome;
    int_as[i_cent] = int_as_/denome;
    int_hs[i_cent] = int_hs_/denome;
    cout<<i_cent<<", "<<int_aspar[i_cent]<<", "<<int_as[i_cent]<<", "<<int_hs[i_cent]<<endl;
  }
  TGraph *gr_diff_ashish[ncent];
  TGraph *gr_diff_hosan[ncent];
  TGraph *gr_diff_as_hs[ncent];
  for(int i_cent = 0 ; i_cent < ncent ; i_cent++){
    gr_diff_ashish[i_cent] = new TGraph(npt, x1[i_cent], eff_diff_ashish[i_cent]);
    gr_diff_ashish[i_cent]->SetTitle(Form("RefMult3: [%d, %d)", cent_ref3[i_cent+1], cent_ref3[i_cent]));
    gr_diff_ashish[i_cent]->GetXaxis()->SetRangeUser(0.2, 2.2);
    gr_diff_ashish[i_cent]->GetXaxis()->SetTitle("p_{T} [GeV/c]");
    gr_diff_ashish[i_cent]->SetMarkerStyle(8);
    gr_diff_ashish[i_cent]->SetMarkerSize(0.5);
    gr_diff_ashish[i_cent]->SetMarkerColor(1);
    gr_diff_hosan[i_cent] = new TGraph(npt, x1[i_cent], eff_diff_hosan[i_cent]);
    gr_diff_hosan[i_cent]->SetTitle(Form("RefMult3: [%d, %d)", cent_ref3[i_cent+1], cent_ref3[i_cent]));
    gr_diff_hosan[i_cent]->GetXaxis()->SetRangeUser(0.2, 2.2);
    gr_diff_hosan[i_cent]->GetXaxis()->SetTitle("p_{T} [GeV/c]");
    gr_diff_hosan[i_cent]->SetMarkerStyle(4);
    gr_diff_hosan[i_cent]->SetMarkerSize(0.1);
    gr_diff_hosan[i_cent]->SetMarkerColor(2);
    gr_diff_as_hs[i_cent] = new TGraph(npt, x1[i_cent], eff_diff_as_hs[i_cent]);
    gr_diff_as_hs[i_cent]->SetTitle(Form("RefMult3: [%d, %d)", cent_ref3[i_cent+1], cent_ref3[i_cent]));
    gr_diff_as_hs[i_cent]->GetXaxis()->SetRangeUser(0.4, 2.0);
    gr_diff_as_hs[i_cent]->GetXaxis()->SetTitle("p_{T} [GeV/c]");
    gr_diff_as_hs[i_cent]->SetMarkerStyle(4);
    gr_diff_as_hs[i_cent]->SetMarkerSize(0.1);
    gr_diff_as_hs[i_cent]->SetMarkerColor(4);
  }
  

  TCanvas *c_test_tpc_ncent = new TCanvas("c_test_tpc_ncent", "c_test_tpc_ncent", 2700, 1000); c_test_tpc_ncent->Divide(5,2);
  for(int i_cent = 0 ; i_cent < ncent ; i_cent++){
    c_test_tpc_ncent->cd(i_cent+1);
    /* gr1[i_cent]->GetXaxis()->SetRangeUser(0.3, 2.1); */
    /* gr1[i_cent]->GetYaxis()->SetRangeUser(0.4, 1.0); */
    /* gr1[i_cent]->Draw("ap"); */
    /* gr1_hs[i_cent]->Draw("p same"); */
    /* if(string(NamePPiK) == "Proton") f1_tpc_p_ashish[i_cent]->Draw("same"); */
    /* else if(string(NamePPiK) == "AntiProton") f1_tpc_m_ashish[i_cent]->Draw("same"); */
    h1_y_pt_eff_tpc[i_cent]->GetXaxis()->SetRangeUser(0.3,2.0);
    h1_y_pt_eff_tpc[i_cent]->Draw();
    h1_y_pt_eff_tpc_hs[i_cent]->SetMarkerStyle(8);
    h1_y_pt_eff_tpc_hs[i_cent]->SetMarkerColor(4);
    h1_y_pt_eff_tpc_hs[i_cent]->Draw("same0");
  }
  TLegend *leg_test_tpc_ncent = new TLegend(0.1, 0.1, 0.9, 0.9);
  gr1[0]->SetMarkerSize(2);
  gr1_hs[0]->SetMarkerSize(2);
  f1_tpc_p_ashish[0]->SetLineWidth(2);
  /* leg_test_tpc_ncent->AddEntry(gr1[0], "Ashish", "pl"); */
  /* leg_test_tpc_ncent->AddEntry(gr1_hs[0], "Hosan", "pl"); */
  /* leg_test_tpc_ncent->AddEntry(f1_tpc_p_ashish[0], "Ashish param.", "pl"); */
  leg_test_tpc_ncent->AddEntry(h1_y_pt_eff_tpc[0], "Ashish", "pl");
  leg_test_tpc_ncent->AddEntry(h1_y_pt_eff_tpc_hs[0], "Hosan", "pl");
  c_test_tpc_ncent->cd(1);
  leg_test_tpc_ncent->Draw("same");
  c_test_tpc_ncent->Print(Form("output/eff_read_test_old/c_test_tpc_ncent_%s_%s.pdf", NamePPiK, NameRuZr));

  TLine *l_diff_aspar_hs_ncent[ncent], *l_diff_as_hs_ncent[ncent];

  TLine *l_test_tpc_diff_ncent_1 = new TLine(0.4, 0, 2.0, 0);
  l_test_tpc_diff_ncent_1->SetLineColor(6);
  
  TCanvas *c_test_tpc_diff_ncent = new TCanvas("c_test_tpc_diff_ncent", "c_test_tpc_diff_ncent", 2700, 1000); c_test_tpc_diff_ncent->Divide(5,2);
  for(int i_cent = 0 ; i_cent < ncent ; i_cent++){
    c_test_tpc_diff_ncent->cd(i_cent+1);

    l_diff_aspar_hs_ncent[i_cent] = new TLine(2, int_diff_aspar_hs_ncent[i_cent], 2.4, int_diff_aspar_hs_ncent[i_cent]);
    l_diff_as_hs_ncent[i_cent] = new TLine(2, int_diff_as_hs_ncent[i_cent], 2.4, int_diff_as_hs_ncent[i_cent]);
    l_diff_aspar_hs_ncent[i_cent]->SetLineColor(2);
    l_diff_as_hs_ncent[i_cent]->SetLineColor(4);
    l_diff_aspar_hs_ncent[i_cent]->SetLineWidth(2);
    l_diff_as_hs_ncent[i_cent]->SetLineWidth(2);
    
    /* gr_diff_ashish[i_cent]->Draw("ap"); */
    /* gr_diff_hosan[i_cent]->Draw("p same"); */
    gr_diff_as_hs[i_cent]->GetYaxis()->SetRangeUser(-0.1, 0.1);
    gr_diff_as_hs[i_cent]->Draw("ap");
    /* l_test_tpc_diff_ncent_1->Draw("same"); */

    /* l_diff_aspar_hs_ncent[i_cent]->Draw("same"); */
    /* l_diff_as_hs_ncent[i_cent]->Draw("same"); */
  }

  gr_diff_ashish[0]->SetMarkerSize(2);
  gr_diff_hosan[0]->SetMarkerSize(2);
  gr_diff_as_hs[0]->SetMarkerSize(2);
  TLegend *leg_test_tpc_diff_ncent = new TLegend(0.1, 0.1, 0.9, 0.9);
  /* leg_test_tpc_diff_ncent->AddEntry(gr_diff_ashish[0], "Ashish param - Ashish interpolated", "pl"); */
  /* leg_test_tpc_diff_ncent->AddEntry(gr_diff_hosan[0], "Ashish param - HS interpolated", "pl"); */
  leg_test_tpc_diff_ncent->AddEntry(gr_diff_as_hs[0], "Ashish - HS", "pl");
  /* leg_test_tpc_diff_ncent->AddEntry(l_diff_aspar_hs_ncent[0], "Ashish param - HS interpolated int. over p_{T}: 0.4 ~ 2.0 GeV/c", "l"); */
  /* leg_test_tpc_diff_ncent->AddEntry(l_diff_as_hs_ncent[0], "Ashish interpolated - HS interpolated int. over p_{T}: 0.4 ~ 2.0 GeV/c", "l"); */
  c_test_tpc_diff_ncent->cd(1);
  leg_test_tpc_diff_ncent->Draw("same");
  
  c_test_tpc_diff_ncent->Print(Form("output/eff_read_test_old/c_test_tpc_diff_ncent_%s_%s.pdf", NamePPiK, NameRuZr));

  /* double x2[ncent]; */
  double y2_1[ncent], y2_2[ncent], y2_3[ncent], y2_4[ncent];
  for(int i_cent = 0 ; i_cent < ncent ; i_cent++){
    /* x2[i_cent] = 55.*(i_cent+1); */
    y2_1[i_cent] = h1_y_pt_eff_tpc_hs[i_cent]->GetBinContent(h1_y_pt_eff_tpc_hs[i_cent]->FindBin(0.4));
    /* y2_1[i_cent] = h1_y_pt_eff_tpc[i_cent]->Eval(0.4); */
    y2_2[i_cent] = h1_y_pt_eff_tpc_hs[i_cent]->GetBinContent(h1_y_pt_eff_tpc_hs[i_cent]->FindBin(0.871667));
    /* y2_2[i_cent] = h1_y_pt_eff_tpc[i_cent]->Eval(0.871667); */
    y2_3[i_cent] = h1_y_pt_eff_tpc_hs[i_cent]->GetBinContent(h1_y_pt_eff_tpc_hs[i_cent]->FindBin(1.427760));
    /* y2_3[i_cent] = h1_y_pt_eff_tpc[i_cent]->Eval(1.427760); */
    y2_4[i_cent] = h1_y_pt_eff_tpc_hs[i_cent]->GetBinContent(h1_y_pt_eff_tpc_hs[i_cent]->FindBin(2.0));
    /* y2_4[i_cent] = h1_y_pt_eff_tpc[i_cent]->Eval(2.0); */
    /* cout<<y2_4[0]<<endl; */
    /* if(i_cent == 0) cout<<h1_y_pt_eff_tpc[i_cent]->FindBin(2.0)<<endl; */
  }
  ////////////////////
  cout<<"======Changing the max mult eff from 0 to the most central bin's center value's======"<<endl;
  cout<<y2_1[0]<<endl;
  y2_1[0] = y2_1[1];
  y2_2[0] = y2_2[1];
  y2_3[0] = y2_3[1];
  y2_4[0] = y2_4[1];
  cout<<"====================================================================================="<<endl;
  ////////////////////
  /* TGraph *gr2 = new TGraph(ncent, x2, y2_2); gr2->SetMarkerStyle(8); */
  TGraph *gr2_1 = new TGraph(ncent, ref3_avg_arr, y2_1); gr2_1->SetMarkerStyle(8); gr2_1->SetMarkerColor(1);
  TGraph *gr2_2 = new TGraph(ncent, ref3_avg_arr, y2_2); gr2_2->SetMarkerStyle(8); gr2_2->SetMarkerColor(2);
  TGraph *gr2_3 = new TGraph(ncent, ref3_avg_arr, y2_3); gr2_3->SetMarkerStyle(8); gr2_3->SetMarkerColor(4);
  TGraph *gr2_4 = new TGraph(ncent, ref3_avg_arr, y2_4); gr2_4->SetMarkerStyle(8); gr2_4->SetMarkerColor(5);
  cout<<gr2_1->Eval(20)<<endl;
  cout<<gr2_2->Eval(439)<<endl;
  cout<<gr2_3->Eval(537.000000)<<endl;
  TCanvas *c_test_tpc = new TCanvas("c_test_tpc", "c_test_tpc", 700, 500); c_test_tpc->cd();
  gr2_1->SetTitle(Form("%s, %s, TPC", NamePPiK, NameRuZr));
  gr2_1->GetXaxis()->SetTitle("RefMult3");
  gr2_1->GetXaxis()->SetLimits(0, 800);
  gr2_1->GetYaxis()->SetRangeUser (0.55, 0.99);
  gr2_1->Draw("ap");
  gr2_2->Draw("p same");
  gr2_3->Draw("p same");
  gr2_4->Draw("p same");

  /* TFile *f_test = new TFile("f_test.root", "recreate"); */
  /* f_test->cd(); */
  /* gr2_1->Write("gr1"); */
  /* gr2_2->Write("gr2"); */
  /* gr2_3->Write("gr3"); */
  /* gr2_4->Write("gr4"); */
  /* f_test->Write(); */
  /* f_test->Close(); */

  TLegend *leg_test_tpc = new TLegend(0.1, 0.1, 0.45, 0.35);
  leg_test_tpc->AddEntry(gr2_1, "p_{T} = 0.4 GeV/c", "p");
  leg_test_tpc->AddEntry(gr2_2, "p_{T} = 0.87 GeV/c", "p");
  leg_test_tpc->AddEntry(gr2_3, "p_{T} = 1.43 GeV/c", "p");
  leg_test_tpc->AddEntry(gr2_4, "p_{T} = 2.0 GeV/c", "p");
  leg_test_tpc->Draw("same");

  const int nmult = 800;
  double x3[nmult];
  double y3_1[nmult], y3_2[nmult], y3_3[nmult], y3_4[nmult];
  for(int i_mult = 0 ; i_mult < nmult ; i_mult++){
    x3[i_mult] = i_mult;
    y3_1[i_mult] = gr2_1->Eval(i_mult);
    y3_2[i_mult] = gr2_2->Eval(i_mult);
    y3_3[i_mult] = gr2_3->Eval(i_mult);
    y3_4[i_mult] = gr2_4->Eval(i_mult);
  }
  TGraph *gr3_1 = new TGraph(nmult, x3, y3_1); gr3_1->SetMarkerColor(1);
  TGraph *gr3_2 = new TGraph(nmult, x3, y3_2); gr3_2->SetMarkerColor(2);
  TGraph *gr3_3 = new TGraph(nmult, x3, y3_3); gr3_3->SetMarkerColor(4);
  TGraph *gr3_4 = new TGraph(nmult, x3, y3_4); gr3_4->SetMarkerColor(5);

  /* TF1 *f3_1 = new TF1("f3_1", "pol1", 10, 500); gr3_1->Fit(f3_1, "R"); TF1 *f3_draw_1 = new TF1("f3_draw_1", "pol1", 0, 1000); f3_draw_1->SetParameter(0, f3_1->GetParameter(0)); f3_draw_1->SetParameter(1, f3_1->GetParameter(1)); f3_draw_1->SetLineColor(1); */
  /* TF1 *f3_2 = new TF1("f3_2", "pol1", 10, 500); gr3_2->Fit(f3_2, "R"); TF1 *f3_draw_2 = new TF1("f3_draw_2", "pol1", 0, 1000); f3_draw_2->SetParameter(0, f3_2->GetParameter(0)); f3_draw_2->SetParameter(1, f3_2->GetParameter(1)); f3_draw_2->SetLineColor(2); */
  /* TF1 *f3_3 = new TF1("f3_3", "pol1", 10, 500); gr3_3->Fit(f3_3, "R"); TF1 *f3_draw_3 = new TF1("f3_draw_3", "pol1", 0, 1000); f3_draw_3->SetParameter(0, f3_3->GetParameter(0)); f3_draw_3->SetParameter(1, f3_3->GetParameter(1)); f3_draw_3->SetLineColor(4); */
  /* TF1 *f3_4 = new TF1("f3_4", "pol1", 10, 500); gr3_4->Fit(f3_4, "R"); TF1 *f3_draw_4 = new TF1("f3_draw_4", "pol1", 0, 1000); f3_draw_4->SetParameter(0, f3_4->GetParameter(0)); f3_draw_4->SetParameter(1, f3_4->GetParameter(1)); f3_draw_4->SetLineColor(5); */
  
  gr3_1->Draw("p same");
  gr3_2->Draw("p same");
  gr3_3->Draw("p same");
  gr3_4->Draw("p same");
  /* f3_draw_1->Draw("same"); */
  /* f3_draw_2->Draw("same"); */
  /* f3_draw_3->Draw("same"); */
  /* f3_draw_4->Draw("same"); */

  c_test_tpc->Print("output/eff_read_test_old/c_test_tpc.pdf");

  cout<<"\n\n ################# TOF TEST #################"<<endl;
  double xP1[ncent][nsys][npt];
  double yP1[ncent][nsys][npt];
  double xM1[ncent][nsys][npt];
  double yM1[ncent][nsys][npt];

  for(int i_sys = 0 ; i_sys < nsys ; i_sys++){
    for(int i_cent = 0 ; i_cent < ncent ; i_cent++){
      for(int i_pt = 0 ; i_pt < npt ; i_pt++){
	xP1[i_cent][i_sys][i_pt] = 1.0*i_pt/100;
	/* yP1[i_cent][i_sys][i_pt] = h1_y_pt_eff_tof_pP[i_cent][i_sys]->GetBinContent(h1_y_pt_eff_tof_pP[i_cent][i_sys]->FindBin(1.0*i_pt/100)); */
	yP1[i_cent][i_sys][i_pt] = h1_y_pt_eff_tof_pP[i_cent][i_sys]->Interpolate(1.0*i_pt/100);
	xM1[i_cent][i_sys][i_pt] = 1.0*i_pt/100;
	/* yM1[i_cent][i_sys][i_pt] = h1_y_pt_eff_tof_pM[i_cent][i_sys]->GetBinContent(h1_y_pt_eff_tof_pM[i_cent][i_sys]->FindBin(1.0*i_pt/100)); */
	yM1[i_cent][i_sys][i_pt] = h1_y_pt_eff_tof_pM[i_cent][i_sys]->Interpolate(1.0*i_pt/100);
	/* h1_y_pt_eff_tof_pM[i_cent][i_sys]; */
      }
    }
  }

  TGraph *grP1[ncent][nsys];
  TGraph *grM1[ncent][nsys];
  for(int i_sys = 0 ; i_sys < nsys ; i_sys++){
    for(int i_cent = 0 ; i_cent < ncent ; i_cent++){
      grP1[i_cent][i_sys] = new TGraph(npt, xP1[i_cent][i_sys], yP1[i_cent][i_sys]);
      grM1[i_cent][i_sys] = new TGraph(npt, xM1[i_cent][i_sys], yM1[i_cent][i_sys]);
      grP1[i_cent][i_sys]->SetTitle(Form("RefMult3: [%d, %d)", cent_ref3[i_cent+1], cent_ref3[i_cent]));
      grP1[i_cent][i_sys]->GetXaxis()->SetTitle("p_{T} [GeV/c]");
      grP1[i_cent][i_sys]->SetMarkerStyle(8);
      grP1[i_cent][i_sys]->SetMarkerSize(0.5);
      grM1[i_cent][i_sys]->SetTitle(Form("RefMult3: [%d, %d)", cent_ref3[i_cent+1], cent_ref3[i_cent]));
      grM1[i_cent][i_sys]->GetXaxis()->SetTitle("p_{T} [GeV/c]");
      grM1[i_cent][i_sys]->SetMarkerStyle(8);
      grM1[i_cent][i_sys]->SetMarkerSize(0.5);
    }
  }
  TCanvas *c_test_tof_ncentP = new TCanvas("c_test_tof_ncentP", "c_test_tof_ncentP", 2700, 1000); c_test_tof_ncentP->Divide(5,2);
  TCanvas *c_test_tof_ncentM = new TCanvas("c_test_tof_ncentM", "c_test_tof_ncentM", 2700, 1000); c_test_tof_ncentM->Divide(5,2);
  for(int i_cent = 0 ; i_cent < ncent ; i_cent++){
    c_test_tof_ncentP->cd(i_cent+1);
    grP1[i_cent][6]->GetXaxis()->SetLimits(0.7, 2.1);
    grP1[i_cent][6]->Draw("ap");
    c_test_tof_ncentM->cd(i_cent+1);
    grM1[i_cent][6]->GetXaxis()->SetLimits(0.7, 2.1);
    grM1[i_cent][6]->Draw("ap");
  }
  c_test_tof_ncentP->Print("output/eff_read_test_old/c_test_tof_ncentP.pdf");
  c_test_tof_ncentM->Print("output/eff_read_test_old/c_test_tof_ncentM.pdf");
  
  double yP2_1[nsys][ncent], yP2_2[nsys][ncent], yP2_3[nsys][ncent], yP2_4[nsys][ncent];
  double yM2_1[nsys][ncent], yM2_2[nsys][ncent], yM2_3[nsys][ncent], yM2_4[nsys][ncent];
  for(int i_sys = 0 ; i_sys < nsys ; i_sys++){
    for(int i_cent = 0 ; i_cent < ncent ; i_cent++){
      /* x2[i_sys][i_cent] = 55.*(i_cent+1); */
      /* yP2_1[i_sys][i_cent] = h1_y_pt_eff_tof_pP[i_cent][i_sys]->GetBinContent(h1_y_pt_eff_tof_pP[i_cent][i_sys]->FindBin(0.4)); */
      yP2_1[i_sys][i_cent] = h1_y_pt_eff_tof_pP[i_cent][i_sys]->Interpolate(0.4);
      /* yP2_2[i_sys][i_cent] = h1_y_pt_eff_tof_pP[i_cent][i_sys]->GetBinContent(h1_y_pt_eff_tof_pP[i_cent][i_sys]->FindBin(0.871667)); */
      yP2_2[i_sys][i_cent] = h1_y_pt_eff_tof_pP[i_cent][i_sys]->Interpolate(0.871667);
      /* yP2_3[i_sys][i_cent] = h1_y_pt_eff_tof_pP[i_cent][i_sys]->GetBinContent(h1_y_pt_eff_tof_pP[i_cent][i_sys]->FindBin(1.427760)); */
      yP2_3[i_sys][i_cent] = h1_y_pt_eff_tof_pP[i_cent][i_sys]->Interpolate(1.427760);
      /* yP2_4[i_sys][i_cent] = h1_y_pt_eff_tof_pP[i_cent][i_sys]->GetBinContent(h1_y_pt_eff_tof_pP[i_cent][i_sys]->FindBin(2.0)); */
      yP2_4[i_sys][i_cent] = h1_y_pt_eff_tof_pP[i_cent][i_sys]->Interpolate(2.0);

      /* yM2_1[i_sys][i_cent] = h1_y_pt_eff_tof_pM[i_cent][i_sys]->GetBinContent(h1_y_pt_eff_tof_pM[i_cent][i_sys]->FindBin(0.4)); */
      yM2_1[i_sys][i_cent] = h1_y_pt_eff_tof_pM[i_cent][i_sys]->Interpolate(0.4);
      /* yM2_2[i_sys][i_cent] = h1_y_pt_eff_tof_pM[i_cent][i_sys]->GetBinContent(h1_y_pt_eff_tof_pM[i_cent][i_sys]->FindBin(0.871667)); */
      yM2_2[i_sys][i_cent] = h1_y_pt_eff_tof_pM[i_cent][i_sys]->Interpolate(0.871667);
      /* yM2_3[i_sys][i_cent] = h1_y_pt_eff_tof_pM[i_cent][i_sys]->GetBinContent(h1_y_pt_eff_tof_pM[i_cent][i_sys]->FindBin(1.427760)); */
      yM2_3[i_sys][i_cent] = h1_y_pt_eff_tof_pM[i_cent][i_sys]->Interpolate(1.427760);
      /* yM2_4[i_sys][i_cent] = h1_y_pt_eff_tof_pM[i_cent][i_sys]->GetBinContent(h1_y_pt_eff_tof_pM[i_cent][i_sys]->FindBin(2.0)); */
      yM2_4[i_sys][i_cent] = h1_y_pt_eff_tof_pM[i_cent][i_sys]->Interpolate(2.0);
    }
  }

  ////////////////////
  cout<<"======Changing the max mult eff from 0 to the most central bin's center value's======"<<endl;
  for(int i_sys = 0 ; i_sys < nsys ; i_sys++){
    /* cout<<yP2_1[i_sys][0]<<endl; */
    yP2_1[i_sys][0] = yP2_1[i_sys][1];
    yP2_2[i_sys][0] = yP2_2[i_sys][1];
    yP2_3[i_sys][0] = yP2_3[i_sys][1];
    yP2_4[i_sys][0] = yP2_4[i_sys][1];

    yM2_1[i_sys][0] = yM2_1[i_sys][1];
    yM2_2[i_sys][0] = yM2_2[i_sys][1];
    yM2_3[i_sys][0] = yM2_3[i_sys][1];
    yM2_4[i_sys][0] = yM2_4[i_sys][1];
  }
  cout<<"====================================================================================="<<endl;
  ////////////////////

  TGraph *grP2_1[nsys];
  TGraph *grP2_2[nsys];
  TGraph *grP2_3[nsys];
  TGraph *grP2_4[nsys];
  TGraph *grM2_1[nsys];
  TGraph *grM2_2[nsys];
  TGraph *grM2_3[nsys];
  TGraph *grM2_4[nsys];
  for(int i_sys = 0 ; i_sys < nsys ; i_sys++){
    grP2_1[i_sys] = new TGraph(ncent, ref3_avg_arr, yP2_1[i_sys]); grP2_1[i_sys]->SetMarkerStyle(8); grP2_1[i_sys]->SetMarkerColor(1);
    grP2_2[i_sys] = new TGraph(ncent, ref3_avg_arr, yP2_2[i_sys]); grP2_2[i_sys]->SetMarkerStyle(8); grP2_2[i_sys]->SetMarkerColor(2);
    grP2_3[i_sys] = new TGraph(ncent, ref3_avg_arr, yP2_3[i_sys]); grP2_3[i_sys]->SetMarkerStyle(8); grP2_3[i_sys]->SetMarkerColor(4);
    grP2_4[i_sys] = new TGraph(ncent, ref3_avg_arr, yP2_4[i_sys]); grP2_4[i_sys]->SetMarkerStyle(8); grP2_4[i_sys]->SetMarkerColor(5);
    grM2_1[i_sys] = new TGraph(ncent, ref3_avg_arr, yM2_1[i_sys]); grM2_1[i_sys]->SetMarkerStyle(8); grM2_1[i_sys]->SetMarkerColor(1);
    grM2_2[i_sys] = new TGraph(ncent, ref3_avg_arr, yM2_2[i_sys]); grM2_2[i_sys]->SetMarkerStyle(8); grM2_2[i_sys]->SetMarkerColor(2);
    grM2_3[i_sys] = new TGraph(ncent, ref3_avg_arr, yM2_3[i_sys]); grM2_3[i_sys]->SetMarkerStyle(8); grM2_3[i_sys]->SetMarkerColor(4);
    grM2_4[i_sys] = new TGraph(ncent, ref3_avg_arr, yM2_4[i_sys]); grM2_4[i_sys]->SetMarkerStyle(8); grM2_4[i_sys]->SetMarkerColor(5);
  }
  cout<<grP2_2[6]->Eval(439.000000)<<endl;
  cout<<grP2_3[6]->Eval(537.000000)<<endl;
  TCanvas *c_test_tof = new TCanvas("c_test_tof", "c_test_tof", 1200, 500); c_test_tof->Divide(2,1);
  c_test_tof->cd(1);
  grP2_1[6]->SetTitle(Form("%s, %s, TOF", "Proton", NameRuZr));
  grP2_1[6]->GetXaxis()->SetTitle("RefMult3");
  grP2_1[6]->GetXaxis()->SetLimits(0, 800);
  grP2_1[6]->GetYaxis()->SetRangeUser(0.69,0.79);
  grP2_1[6]->Draw("ap");
  grP2_2[6]->Draw("p same");
  grP2_3[6]->Draw("p same");
  grP2_4[6]->Draw("p same");
  c_test_tof->cd(2);
  grM2_1[6]->SetTitle(Form("%s, %s, TOF", "Anti-proton", NameRuZr));
  grM2_1[6]->GetXaxis()->SetTitle("RefMult3");
  grM2_1[6]->GetXaxis()->SetLimits(0, 800);
  grM2_1[6]->GetYaxis()->SetRangeUser(0.63, 0.77);
  grM2_1[6]->Draw("ap");
  grM2_2[6]->Draw("p same");
  grM2_3[6]->Draw("p same");
  grM2_4[6]->Draw("p same");

  TLegend *leg_test_tof = new TLegend(0.55, 0.55, 0.9, 0.9);
  leg_test_tof->AddEntry(grP2_1[6], "p_{T} = 0.4 GeV/c", "p");
  leg_test_tof->AddEntry(grP2_2[6], "p_{T} = 0.87 GeV/c", "p");
  leg_test_tof->AddEntry(grP2_3[6], "p_{T} = 1.43 GeV/c", "p");
  leg_test_tof->AddEntry(grP2_4[6], "p_{T} = 2.0 GeV/c", "p");
  c_test_tof->cd(1);
  leg_test_tof->Draw("same");

  double xP3[nsys][nmult];
  double yP3_1[nsys][nmult], yP3_2[nsys][nmult], yP3_3[nsys][nmult], yP3_4[nsys][nmult];
  double xM3[nsys][nmult];
  double yM3_1[nsys][nmult], yM3_2[nsys][nmult], yM3_3[nsys][nmult], yM3_4[nsys][nmult];

  TGraph *grP3_1[nsys], *grP3_2[nsys], *grP3_3[nsys], *grP3_4[nsys];
  TGraph *grM3_1[nsys], *grM3_2[nsys], *grM3_3[nsys], *grM3_4[nsys];

  for(int i_sys = 0 ; i_sys < nsys ; i_sys++){
    for(int i_mult = 0 ; i_mult < nmult ; i_mult++){
      xP3[i_sys][i_mult] = i_mult;
      yP3_1[i_sys][i_mult] = grP2_1[i_sys]->Eval(i_mult);
      yP3_2[i_sys][i_mult] = grP2_2[i_sys]->Eval(i_mult);
      yP3_3[i_sys][i_mult] = grP2_3[i_sys]->Eval(i_mult);
      yP3_4[i_sys][i_mult] = grP2_4[i_sys]->Eval(i_mult);
      xM3[i_sys][i_mult] = i_mult;
      yM3_1[i_sys][i_mult] = grM2_1[i_sys]->Eval(i_mult);
      yM3_2[i_sys][i_mult] = grM2_2[i_sys]->Eval(i_mult);
      yM3_3[i_sys][i_mult] = grM2_3[i_sys]->Eval(i_mult);
      yM3_4[i_sys][i_mult] = grM2_4[i_sys]->Eval(i_mult);
    }
    grP3_1[i_sys] = new TGraph(nmult, xP3[i_sys], yP3_1[i_sys]);; grP3_1[i_sys]->SetMarkerColor(1);
    grP3_2[i_sys] = new TGraph(nmult, xP3[i_sys], yP3_2[i_sys]);; grP3_2[i_sys]->SetMarkerColor(2);
    grP3_3[i_sys] = new TGraph(nmult, xP3[i_sys], yP3_3[i_sys]);; grP3_3[i_sys]->SetMarkerColor(4);
    grP3_4[i_sys] = new TGraph(nmult, xP3[i_sys], yP3_4[i_sys]);; grP3_4[i_sys]->SetMarkerColor(5);
    grM3_1[i_sys] = new TGraph(nmult, xM3[i_sys], yM3_1[i_sys]);; grM3_1[i_sys]->SetMarkerColor(1);
    grM3_2[i_sys] = new TGraph(nmult, xM3[i_sys], yM3_2[i_sys]);; grM3_2[i_sys]->SetMarkerColor(2);
    grM3_3[i_sys] = new TGraph(nmult, xM3[i_sys], yM3_3[i_sys]);; grM3_3[i_sys]->SetMarkerColor(4);
    grM3_4[i_sys] = new TGraph(nmult, xM3[i_sys], yM3_4[i_sys]);; grM3_4[i_sys]->SetMarkerColor(5);
  }
  /* for(int i_sys = 0 ; i_sys < nsys ; i_sys++){ */
  /* } */
  c_test_tof->cd(1);
  grP3_1[6]->Draw("p same");
  grP3_2[6]->Draw("p same");
  grP3_3[6]->Draw("p same");
  grP3_4[6]->Draw("p same");
  c_test_tof->cd(2);
  grM3_1[6]->Draw("p same");
  grM3_2[6]->Draw("p same");
  grM3_3[6]->Draw("p same");
  grM3_4[6]->Draw("p same");

  c_test_tof->Print("output/eff_read_test_old/c_test_tof.pdf");

}
