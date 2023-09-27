//Let's try to make a tpc efficiency map in Multiplicity vs pT
  static int ncent = 10;

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

void _init(const char* NameRuZr = "Ru", const int dca = 9, const int nhf = 20, const int nsp = 20){
  
  f_tpc_pP = new TFile(Form("/Users/hosanko/playground/star/anal/Coll/isobar/ZrZrRuRu200_2018/charge/sys_unc/efficiency/draw/27092022/27092022_1/output/TPC/file/root/Proton_Ru_dca_%d_nhitsfit_%d.root", dca, nhf), "READ");
  f_tpc_pM = new TFile(Form("/Users/hosanko/playground/star/anal/Coll/isobar/ZrZrRuRu200_2018/charge/sys_unc/efficiency/draw/27092022/27092022_1/output/TPC/file/root/AntiProton_Ru_dca_%d_nhitsfit_%d.root", dca, nhf), "READ");
  f_tof_pP = new TFile(Form("/Users/hosanko/playground/star/anal/Coll/isobar/ZrZrRuRu200_2018/charge/sys_unc/efficiency/draw/27092022/27092022_1/output/TOF/1D/file/root/Proton_Ru_dca_%.1f_nhf_%d_nsp_%.1f.root", 0.1*dca, nhf, 0.1*nsp), "READ");
  f_tof_pM = new TFile(Form("/Users/hosanko/playground/star/anal/Coll/isobar/ZrZrRuRu200_2018/charge/sys_unc/efficiency/draw/27092022/27092022_1/output/TOF/1D/file/root/AntiProton_Ru_dca_%.1f_nhf_%d_nsp_%.1f.root", 0.1*dca, nhf, 0.1*nsp), "READ");

  for(int i_cent = 0 ; i_cent < ncent ; i_cent++){
    h1_y_pt_eff_tpc_pP[i_cent] = (TH1D *)f_tpc_pP->Get(Form("h1_y_pt_eff_one_%d", i_cent));
    h1_y_pt_eff_tpc_pM[i_cent] = (TH1D *)f_tpc_pM->Get(Form("h1_y_pt_eff_one_%d", i_cent));
    h1_y_pt_eff_tof_pP[i_cent] = (TH1D *)f_tof_pP->Get(Form("h1_y_pt_eff_one_pP_%d", i_cent));
    h1_y_pt_eff_tof_pM[i_cent] = (TH1D *)f_tof_pM->Get(Form("h1_y_pt_eff_one_pM_%d", i_cent));
  }

  gr_eff_tpc_pP = new TGraph(ncent);//, ref3_avg, eff_tpc_pP);
  gr_eff_tpc_pM = new TGraph(ncent);//, ref3_avg, eff_tpc_pM);
  gr_eff_tof_pP = new TGraph(ncent);//, ref3_avg, eff_tof_pP);
  gr_eff_tof_pM = new TGraph(ncent);//, ref3_avg, eff_tof_pM);

    if(string(NameRuZr) == "Ru"){
    //31082022: updated. check /Users/hosanko/playground/star/anal/Coll/isobar/ZrZrRuRu200_2018/charge/sys_unc/efficiency/draw/30082022/30082022_1/eff_read_test.C              
    ref3_avg[0] = 767.840348;
    ref3_avg[1] = 489.404492;
    ref3_avg[2] = 401.237349;
    ref3_avg[3] = 308.975633;
    ref3_avg[4] = 215.502012;
    ref3_avg[5] = 145.928319;
    ref3_avg[6] = 94.773705;
    ref3_avg[7] = 58.471495;
    ref3_avg[8] = 34.275493;
    ref3_avg[9] = 18.978456;
  }
  if(string(NameRuZr) == "Zr"){
    //31082022: updated. check /Users/hosanko/playground/star/anal/Coll/isobar/ZrZrRuRu200_2018/charge/sys_unc/efficiency/draw/30082022/30082022_1/eff_read_test.C              
    ref3_avg[0] = 767.985594;
    ref3_avg[1] = 485.728196;
    ref3_avg[2] = 397.282974;
    ref3_avg[3] = 303.860336;
    ref3_avg[4] = 208.879138;
    ref3_avg[5] = 139.964043;
    ref3_avg[6] = 90.207695;
    ref3_avg[7] = 54.948073;
    ref3_avg[8] = 31.774110;
    ref3_avg[9] = 17.525293;
  }
  for(int i_cent = 0 ; i_cent < ncent ; i_cent++){
    cout<<"ref3_avg["<<i_cent<<"] = "<<ref3_avg[i_cent]<<endl;
  }

}


void tpc_map(const char* NameRuZr = "Ru", const int dca = 9, const int nhf = 20, const int nsp = 20){
  gStyle->SetOptStat(00000000);
  _init(NameRuZr, dca, nhf, nsp);
  TH2D *h2_tpc_pP = new TH2D("h2_tpc_pP","h2_tpc_pP",100,0,1000,201,0,2); h2_tpc_pP->GetZaxis()->SetRangeUser(0,1); h2_tpc_pP->GetXaxis()->SetTitle("RefMult3"); h2_tpc_pP->GetYaxis()->SetTitle("p_{T} [GeV]");
  TH2D *h2_tpc_pM = new TH2D("h2_tpc_pM","h2_tpc_pM",100,0,1000,201,0,2); h2_tpc_pM->GetZaxis()->SetRangeUser(0,1); h2_tpc_pM->GetXaxis()->SetTitle("RefMult3"); h2_tpc_pM->GetYaxis()->SetTitle("p_{T} [GeV]");
  TH2D *h2_tof_pP = new TH2D("h2_tof_pP","h2_tof_pP",100,0,1000,201,0,2); h2_tof_pP->GetZaxis()->SetRangeUser(0,1); h2_tof_pP->GetXaxis()->SetTitle("RefMult3"); h2_tof_pP->GetYaxis()->SetTitle("p_{T} [GeV]");
  TH2D *h2_tof_pM = new TH2D("h2_tof_pM","h2_tof_pM",100,0,1000,201,0,2); h2_tof_pM->GetZaxis()->SetRangeUser(0,1); h2_tof_pM->GetXaxis()->SetTitle("RefMult3"); h2_tof_pM->GetYaxis()->SetTitle("p_{T} [GeV]");
  for(int i_ref3 = 0 ; i_ref3 < 100 ; i_ref3++){
    for(int i_pt = 0 ; i_pt < 200 ; i_pt++){
      if(i_pt == 0 && i_ref3%100==0) cout<<i_ref3<<", "<<i_pt<<endl;

      double ref3 = 1.*i_ref3*10;
      double pT = 1.*i_pt/100;
      /* cout<<"pT = "<<pT<<endl; */
  
      for(int i_cent = 0 ; i_cent < ncent ; i_cent++){
	// eff_tpc_pP[i_cent] = h1_y_pt_eff_tpc_pP[i_cent]->GetEfficiency(h1_y_pt_eff_tpc_pP[i_cent]->FindFixBin(pT));                                                            
	eff_tpc_pP[i_cent] = h1_y_pt_eff_tpc_pP[i_cent]->Interpolate(pT);
	// eff_tpc_pM[i_cent] = h1_y_pt_eff_tpc_pM[i_cent]->GetEfficiency(h1_y_pt_eff_tpc_pM[i_cent]->FindFixBin(pT));                                                            
	eff_tpc_pM[i_cent] = h1_y_pt_eff_tpc_pM[i_cent]->Interpolate(pT);
	// eff_tof_pP[i_cent] = h1_y_pt_eff_tof_pP[i_cent]->GetEfficiency(h1_y_pt_eff_tof_pP[i_cent]->FindFixBin(pT));                                                            
	eff_tof_pP[i_cent] = h1_y_pt_eff_tof_pP[i_cent]->Interpolate(pT);
	// eff_tof_pM[i_cent] = h1_y_pt_eff_tof_pM[i_cent]->GetEfficiency(h1_y_pt_eff_tof_pM[i_cent]->FindFixBin(pT));                                                            
	eff_tof_pM[i_cent] = h1_y_pt_eff_tof_pM[i_cent]->Interpolate(pT);
      }
      eff_tpc_pP[0] = eff_tpc_pP[1];
      eff_tpc_pM[0] = eff_tpc_pM[1];
      eff_tof_pP[0] = eff_tof_pP[1];
      eff_tof_pM[0] = eff_tof_pM[1];

      for(int i_cent = 0 ; i_cent < ncent ; i_cent++){
	gr_eff_tpc_pP->SetPoint(i_cent, ref3_avg[i_cent], eff_tpc_pP[i_cent]);
	gr_eff_tpc_pM->SetPoint(i_cent, ref3_avg[i_cent], eff_tpc_pM[i_cent]);
	gr_eff_tof_pP->SetPoint(i_cent, ref3_avg[i_cent], eff_tof_pP[i_cent]);
	gr_eff_tof_pM->SetPoint(i_cent, ref3_avg[i_cent], eff_tof_pM[i_cent]);
      }
      /* if(pT == 1.14) cout<<ref3<<", "<<pT<<", "<<gr_eff_tpc_pP->Eval(ref3)<<endl; */
      /* if(pT == 1.15) cout<<ref3<<", "<<pT<<", "<<gr_eff_tpc_pP->Eval(ref3)<<endl; */
      /* if(pT == 1.16) cout<<ref3<<", "<<pT<<", "<<gr_eff_tpc_pP->Eval(ref3)<<endl; */
      /* if(pT == 1.17) cout<<ref3<<", "<<pT<<", "<<gr_eff_tpc_pP->Eval(ref3)<<endl; */
      /* if(pT == 1.18) cout<<ref3<<", "<<pT<<", "<<gr_eff_tpc_pP->Eval(ref3)<<endl; */
      /* h2_tpc_pP->Fill(ref3, pT, gr_eff_tpc_pP->Eval(ref3,0,"S")); */
      /* h2_tpc_pM->Fill(ref3, pT, gr_eff_tpc_pM->Eval(ref3,0,"S")); */
      /* h2_tof_pP->Fill(ref3, pT, gr_eff_tof_pP->Eval(ref3,0,"S")); */
      /* h2_tof_pM->Fill(ref3, pT, gr_eff_tof_pM->Eval(ref3,0,"S")); */
      h2_tpc_pP->Fill(ref3, pT, gr_eff_tpc_pP->Eval(ref3));
      h2_tpc_pM->Fill(ref3, pT, gr_eff_tpc_pM->Eval(ref3));
      h2_tof_pP->Fill(ref3, pT, gr_eff_tof_pP->Eval(ref3));
      h2_tof_pM->Fill(ref3, pT, gr_eff_tof_pM->Eval(ref3));
    }//for(int i_pt = 0 ; i_pt < 200 ; i_pt++){
  }//for(int i_ref3 = 0 ; i_ref3 < 1000 ; i_ref3++){

  TCanvas *c_ = new TCanvas("c_","c_",1200,1000); c_->Divide(2,2);
  c_->cd(1); gPad->SetGridx(1); gPad->SetGridy(1); // gPad->SetLogz(1);
  h2_tpc_pP->SetTitle(Form("TPC proton %s, dca = %.1f cm, nhf = %d, nsp = %.1f", NameRuZr, 0.1*dca, nhf, 0.1*nsp)); 
  h2_tpc_pP->Draw("colz");
  c_->cd(2); gPad->SetGridx(1); gPad->SetGridy(1); // gPad->SetLogz(1);
  h2_tpc_pM->SetTitle(Form("TPC antiproton %s, dca = %.1f cm, nhf = %d, nsp = %.1f", NameRuZr, 0.1*dca, nhf, 0.1*nsp)); 
  h2_tpc_pM->Draw("colz");
  c_->cd(3); gPad->SetGridx(1); gPad->SetGridy(1); // gPad->SetLogz(1);
  h2_tof_pP->SetTitle(Form("TOF proton %s, dca = %.1f cm, nhf = %d, nsp = %.1f", NameRuZr, 0.1*dca, nhf, 0.1*nsp)); 
  h2_tof_pP->Draw("colz");
  c_->cd(4); gPad->SetGridx(1); gPad->SetGridy(1); // gPad->SetLogz(1);
  h2_tof_pM->SetTitle(Form("TOF antiproton %s, dca = %.1f cm, nhf = %d, nsp = %.1f", NameRuZr, 0.1*dca, nhf, 0.1*nsp)); 
  h2_tof_pM->Draw("colz");

  c_->Print(Form("output/eff_read_test/c_%s_%d_%d_%d.pdf",NameRuZr, dca, nhf, nsp));

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

  h_tpc_pP_lopt->GetYaxis()->SetRangeUser(0.765, 0.895);
  h_tpc_pP_hipt->GetYaxis()->SetRangeUser(0.765, 0.895);
  h_tof_pP_hipt->GetYaxis()->SetRangeUser(0.685, 0.755);

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

  c_1d_1->Print(Form("output/eff_read_test/1d/c_%s_%d_%d_%d.pdf",NameRuZr, dca, nhf, nsp));


  TH1D *h_tpc_pM_lopt_y_150_250 = (TH1D*)h2_tpc_pM->ProjectionY("h_tpc_pM_lopt_y_150_250", h2_tpc_pM->GetXaxis()->FindBin(150), h2_tpc_pM->GetXaxis()->FindBin(250)); h_tpc_pM_lopt_y_150_250->SetLineColor(kBlue); h_tpc_pM_lopt_y_150_250->Scale(1./(h2_tpc_pM->GetXaxis()->FindBin(250)-h2_tpc_pM->GetXaxis()->FindBin(150)+1)); h_tpc_pM_lopt_y_150_250->SetLineColor(1);
  TH1D *h_tpc_pM_lopt_y_250_350 = (TH1D*)h2_tpc_pM->ProjectionY("h_tpc_pM_lopt_y_250_350", h2_tpc_pM->GetXaxis()->FindBin(250), h2_tpc_pM->GetXaxis()->FindBin(350)); h_tpc_pM_lopt_y_250_350->SetLineColor(kBlue); h_tpc_pM_lopt_y_250_350->Scale(1./(h2_tpc_pM->GetXaxis()->FindBin(350)-h2_tpc_pM->GetXaxis()->FindBin(250)+1)); h_tpc_pM_lopt_y_250_350->SetLineColor(2);
  TH1D *h_tpc_pM_lopt_y_350_450 = (TH1D*)h2_tpc_pM->ProjectionY("h_tpc_pM_lopt_y_350_450", h2_tpc_pM->GetXaxis()->FindBin(350), h2_tpc_pM->GetXaxis()->FindBin(450)); h_tpc_pM_lopt_y_350_450->SetLineColor(kBlue); h_tpc_pM_lopt_y_350_450->Scale(1./(h2_tpc_pM->GetXaxis()->FindBin(450)-h2_tpc_pM->GetXaxis()->FindBin(350)+1)); h_tpc_pM_lopt_y_350_450->SetLineColor(3);

  TCanvas *c_1d_2 = new TCanvas("c_1d_2","c_1d_2",700,500);
  c_1d_2->cd(1); gPad->SetGridx(1); gPad->SetGridy(1); // gPad->SetLogz(1);
  h_tpc_pM_lopt_y_150_250->Draw("hist"); h_tpc_pM_lopt_y_250_350->Draw("hist same"); h_tpc_pM_lopt_y_350_450->Draw("hist same");


}
