void vz_corr(){

  TFile *f_zr = new TFile("input/merged_hist_Zr_good123/Zr_mTerms_f_mergedFile.root", "read");
  TFile *f_ru = new TFile("input/merged_hist_Ru_good123/Ru_mTerms_f_mergedFile.root", "read");

  TH1D *h1_refMult3StPicoEvt_lumicorr_zr[30];
  TH1D *h1_refMult3StPicoEvt_lumicorr_ru[30];
  TF1 *f_erf_zr[30];
  TF1 *f_erf_ru[30];
  float vz[30];//center point of the vz bin
  float par_erf_zr[30];
  float par_erf_ru[30];
  for(int i_vz = 0 ; i_vz < 30 ; i_vz++){
    vz[i_vz] = -34 + 2*i_vz;
    cout<<i_vz<<", "<<vz[i_vz]<<endl;
    h1_refMult3StPicoEvt_lumicorr_zr[i_vz] = (TH1D*)f_zr->Get(Form("h1_refMult3StPicoEvt_lumicorr_%d", i_vz));
    h1_refMult3StPicoEvt_lumicorr_ru[i_vz] = (TH1D*)f_ru->Get(Form("h1_refMult3StPicoEvt_lumicorr_%d", i_vz));
    h1_refMult3StPicoEvt_lumicorr_zr[i_vz]->Scale(1./h1_refMult3StPicoEvt_lumicorr_zr[i_vz]->Integral());
    h1_refMult3StPicoEvt_lumicorr_ru[i_vz]->Scale(1./h1_refMult3StPicoEvt_lumicorr_ru[i_vz]->Integral());
    h1_refMult3StPicoEvt_lumicorr_zr[i_vz]->SetMarkerColor(i_vz+1);
    h1_refMult3StPicoEvt_lumicorr_zr[i_vz]->SetLineColor(i_vz+1);
    h1_refMult3StPicoEvt_lumicorr_ru[i_vz]->SetMarkerColor(i_vz+1);
    h1_refMult3StPicoEvt_lumicorr_ru[i_vz]->SetLineColor(i_vz+1);
    h1_refMult3StPicoEvt_lumicorr_zr[i_vz]->SetTitle("Zr+Zr");
    h1_refMult3StPicoEvt_lumicorr_zr[i_vz]->GetXaxis()->SetTitle("RefMult3");
    h1_refMult3StPicoEvt_lumicorr_ru[i_vz]->SetTitle("Ru+Ru");
    h1_refMult3StPicoEvt_lumicorr_ru[i_vz]->GetXaxis()->SetTitle("RefMult3");

    f_erf_zr[i_vz] = new TF1(Form("f_erf_zr_%d", i_vz), "[0]*TMath::Erf(-[1]*(x - [2])) + [0]", 450, 600);
    f_erf_ru[i_vz] = new TF1(Form("f_erf_ru_%d", i_vz), "[0]*TMath::Erf(-[1]*(x - [2])) + [0]", 450, 600);
    f_erf_zr[i_vz]->SetParLimits(1, -0.1, 0.1);
    f_erf_zr[i_vz]->SetParLimits(2, 450, 600);
    f_erf_ru[i_vz]->SetParLimits(1, -0.1, 0.1);
    f_erf_ru[i_vz]->SetParLimits(2, 450, 600);

    h1_refMult3StPicoEvt_lumicorr_zr[i_vz]->Fit(f_erf_zr[i_vz], "R Q");
    h1_refMult3StPicoEvt_lumicorr_ru[i_vz]->Fit(f_erf_ru[i_vz], "R Q");

    par_erf_zr[i_vz] = f_erf_zr[i_vz]->GetParameter(2);
    par_erf_ru[i_vz] = f_erf_ru[i_vz]->GetParameter(2);
  }

  TGraph *gr_vz_erf_zr = new TGraph(30, vz, par_erf_zr); gr_vz_erf_zr->SetMarkerStyle(8); gr_vz_erf_zr->SetMarkerColor(1); gr_vz_erf_zr->SetTitle("Zr+Zr"); gr_vz_erf_zr->GetXaxis()->SetTitle("Vz [cm]");
  TGraph *gr_vz_erf_ru = new TGraph(30, vz, par_erf_ru); gr_vz_erf_ru->SetMarkerStyle(8); gr_vz_erf_ru->SetMarkerColor(1); gr_vz_erf_ru->SetTitle("Ru+Ru"); gr_vz_erf_ru->GetXaxis()->SetTitle("Vz [cm]");

  //Vz correction//////////
  //normalize by the parameter at Vz=0
  float par_erf_corr_zr[30];
  float par_erf_corr_ru[30];
  cout<<"par_erf_zr at "<<vz[17]<<": "<<par_erf_zr[17]<<endl;
  cout<<"par_erf_ru at "<<vz[17]<<": "<<par_erf_ru[17]<<endl;
  ofstream myfile_zr_out, myfile_ru_out;
  myfile_zr_out.open("output/zr_vzcorr_par.txt"); myfile_ru_out.open("output/ru_vzcorr_par.txt");
  cout<<"Vz normlization factor by value at Vz=0"<<endl;
  for(int i_vz = 0 ; i_vz < 30 ; i_vz++){
    par_erf_corr_zr[i_vz] = par_erf_zr[17]/par_erf_zr[i_vz];
    par_erf_corr_ru[i_vz] = par_erf_ru[17]/par_erf_ru[i_vz];
    cout<<vz[i_vz]<<", "<<par_erf_zr[i_vz]<<", "<<par_erf_corr_zr[i_vz]<<", "<<par_erf_ru[i_vz]<<", "<<par_erf_corr_ru[i_vz]<<endl;
    myfile_zr_out<<std::setprecision(8)<<par_erf_corr_zr[i_vz]<<endl;
    myfile_ru_out<<std::setprecision(8)<<par_erf_corr_ru[i_vz]<<endl;
  }
  TGraph *gr_vz_erf_corr_zr = new TGraph(30, vz, par_erf_corr_zr); gr_vz_erf_corr_zr->SetMarkerStyle(8); gr_vz_erf_corr_zr->SetMarkerColor(2); gr_vz_erf_corr_zr->SetTitle("Zr+Zr corr factor"); gr_vz_erf_corr_zr->GetXaxis()->SetTitle("Vz [cm]");
  TGraph *gr_vz_erf_corr_ru = new TGraph(30, vz, par_erf_corr_ru); gr_vz_erf_corr_ru->SetMarkerStyle(8); gr_vz_erf_corr_ru->SetMarkerColor(2); gr_vz_erf_corr_ru->SetTitle("Ru+Ru corr factor"); gr_vz_erf_corr_ru->GetXaxis()->SetTitle("Vz [cm]");

  /////////////////////////

  TCanvas *c_lumi = new TCanvas("c_lumi", "c_lumi", 1200, 500);
  c_lumi->Divide(2,1);
  for(int i_vz = 0 ; i_vz < 30 ; i_vz++){
    c_lumi->cd(1); gPad->SetLogy(1);
    if(i_vz == 0) {h1_refMult3StPicoEvt_lumicorr_zr[i_vz]->Draw("hist e"); f_erf_zr[i_vz]->Draw("same");}
    else {h1_refMult3StPicoEvt_lumicorr_zr[i_vz]->Draw("hist same e"); f_erf_zr[i_vz]->Draw("same");}
    c_lumi->cd(2); gPad->SetLogy(1);
    if(i_vz == 0) {h1_refMult3StPicoEvt_lumicorr_ru[i_vz]->Draw("hist e"); f_erf_ru[i_vz]->Draw("same");}
    else {h1_refMult3StPicoEvt_lumicorr_ru[i_vz]->Draw("hist same e"); f_erf_ru[i_vz]->Draw("same");}
  }

  TCanvas *c_vz_erf = new TCanvas("c_vz_erf", "c_vz_erf", 1200, 1000);
  c_vz_erf->Divide(2,2);
  c_vz_erf->cd(1); gPad->SetGridy(1);
  gr_vz_erf_zr->Draw("ap");
  /* gr_vz_erf_corr_zr->Draw("p same"); */
  c_vz_erf->cd(2); gPad->SetGridy(1);
  gr_vz_erf_ru->Draw("ap");
  /* gr_vz_erf_corr_ru->Draw("p same"); */
  c_vz_erf->cd(3); gPad->SetGridy(1);
  gr_vz_erf_corr_zr->Draw("ap");
  c_vz_erf->cd(4); gPad->SetGridy(1);
  gr_vz_erf_corr_ru->Draw("ap");

  TFile *f_out = new TFile("/Users/hosanko/playground/star/anal/Coll/isobar/ZrZrRuRu200_2018/charge/multCorr/22052023_forvzcorr/output/erf.root" , "recreate");
  f_out->cd();
  gr_vz_erf_zr->Write("gr_vz_erf_zr");
  gr_vz_erf_ru->Write("gr_vz_erf_ru");
  f_out->Write();
  f_out->Close();
}
