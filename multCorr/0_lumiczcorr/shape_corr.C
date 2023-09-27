void shape_corr(){

  TFile *f_zr = new TFile("input/merged_hist_Zr_good123/Zr_mTerms_f_mergedFile.root", "read");
  /* TFile *f_zr = new TFile("Zr_hist_19105042.root", "read"); */
  TFile *f_ru = new TFile("input/merged_hist_Ru_good123/Ru_mTerms_f_mergedFile.root", "read");

  TH1D *h1_refMult3StPicoEvt_vzlumicorr_zr[30];
  TH1D *h1_refMult3StPicoEvt_vzlumicorr_ru[30];
  TF1 *f_erf_zr[30];
  TF1 *f_erf_ru[30];
  float vz[30];//center point of the vz bin
  float par_erf_zr[30];
  float par_erf_ru[30];
  float scale_fac_zr[30];
  float scale_fac_ru[30];
  for(int i_vz = 0 ; i_vz < 30 ; i_vz++){
    vz[i_vz] = -35 + 2*i_vz;
    cout<<i_vz<<", "<<vz[i_vz]<<endl;
    /* h1_refMult3StPicoEvt_vzlumicorr_zr[i_vz] = (TH1D*)f_zr->Get(Form("h1_refMult3StPicoEvt_raw_%d", i_vz)); // h1_refMult3StPicoEvt_vzlumicorr_zr[i_vz]->RebinX(5); */
    h1_refMult3StPicoEvt_vzlumicorr_zr[i_vz] = (TH1D*)f_zr->Get(Form("h1_refMult3StPicoEvt_vzlumicorr_%d", i_vz)); // h1_refMult3StPicoEvt_vzlumicorr_zr[i_vz]->RebinX(5);
    h1_refMult3StPicoEvt_vzlumicorr_ru[i_vz] = (TH1D*)f_ru->Get(Form("h1_refMult3StPicoEvt_vzlumicorr_%d", i_vz)); // h1_refMult3StPicoEvt_vzlumicorr_ru[i_vz]->RebinX(5);
    scale_fac_zr[i_vz] = h1_refMult3StPicoEvt_vzlumicorr_zr[i_vz]->Integral();
    scale_fac_ru[i_vz] = h1_refMult3StPicoEvt_vzlumicorr_ru[i_vz]->Integral();
    h1_refMult3StPicoEvt_vzlumicorr_zr[i_vz]->Scale(1./h1_refMult3StPicoEvt_vzlumicorr_zr[i_vz]->Integral());
    h1_refMult3StPicoEvt_vzlumicorr_ru[i_vz]->Scale(1./h1_refMult3StPicoEvt_vzlumicorr_ru[i_vz]->Integral());
    h1_refMult3StPicoEvt_vzlumicorr_zr[i_vz]->SetMarkerColor(i_vz+1);
    h1_refMult3StPicoEvt_vzlumicorr_zr[i_vz]->SetLineColor(i_vz+1);
    h1_refMult3StPicoEvt_vzlumicorr_ru[i_vz]->SetMarkerColor(i_vz+1);
    h1_refMult3StPicoEvt_vzlumicorr_ru[i_vz]->SetLineColor(i_vz+1);
    h1_refMult3StPicoEvt_vzlumicorr_zr[i_vz]->SetTitle("Zr+Zr");
    h1_refMult3StPicoEvt_vzlumicorr_zr[i_vz]->GetXaxis()->SetTitle("RefMult3");
    h1_refMult3StPicoEvt_vzlumicorr_ru[i_vz]->SetTitle("Ru+Ru");
    h1_refMult3StPicoEvt_vzlumicorr_ru[i_vz]->GetXaxis()->SetTitle("RefMult3");

    f_erf_zr[i_vz] = new TF1(Form("f_erf_zr_%d", i_vz), "[0]*TMath::Erf(-[1]*(x - [2])) + [0]", 450, 600);
    f_erf_ru[i_vz] = new TF1(Form("f_erf_ru_%d", i_vz), "[0]*TMath::Erf(-[1]*(x - [2])) + [0]", 450, 600);
    f_erf_zr[i_vz]->SetParLimits(1, -0.1, 0.1);
    f_erf_zr[i_vz]->SetParLimits(2, 450, 600);
    f_erf_ru[i_vz]->SetParLimits(1, -0.1, 0.1);
    f_erf_ru[i_vz]->SetParLimits(2, 450, 600);

    h1_refMult3StPicoEvt_vzlumicorr_zr[i_vz]->Fit(f_erf_zr[i_vz], "R Q");
    h1_refMult3StPicoEvt_vzlumicorr_ru[i_vz]->Fit(f_erf_ru[i_vz], "R Q");

    par_erf_zr[i_vz] = f_erf_zr[i_vz]->GetParameter(2);
    par_erf_ru[i_vz] = f_erf_ru[i_vz]->GetParameter(2);
  }

  TGraph *gr_vz_erf_zr = new TGraph(30, vz, par_erf_zr); gr_vz_erf_zr->SetMarkerStyle(8); gr_vz_erf_zr->SetMarkerColor(2); gr_vz_erf_zr->SetTitle("Zr+Zr"); gr_vz_erf_zr->GetXaxis()->SetTitle("Vz [cm]");
  TGraph *gr_vz_erf_ru = new TGraph(30, vz, par_erf_ru); gr_vz_erf_ru->SetMarkerStyle(8); gr_vz_erf_ru->SetMarkerColor(2); gr_vz_erf_ru->SetTitle("Ru+Ru"); gr_vz_erf_ru->GetXaxis()->SetTitle("Vz [cm]");

  TFile *f_erf_precorr = new TFile("output/erf.root", "read");
  TGraph *gr_vz_erf_precorr_zr = (TGraph*)f_erf_precorr->Get("gr_vz_erf_zr");
  TGraph *gr_vz_erf_precorr_ru = (TGraph*)f_erf_precorr->Get("gr_vz_erf_ru");


  TCanvas *c_lumi = new TCanvas("c_lumi", "c_lumi", 1200, 1000);
  c_lumi->Divide(2,2);
  for(int i_vz = 0 ; i_vz < 30 ; i_vz++){
    c_lumi->cd(1); gPad->SetLogy(1);
    if(i_vz == 0) {h1_refMult3StPicoEvt_vzlumicorr_zr[i_vz]->Draw("hist e"); /* f_erf_zr[i_vz]->Draw("same"); */}
    else {h1_refMult3StPicoEvt_vzlumicorr_zr[i_vz]->Draw("hist same e"); /* f_erf_zr[i_vz]->Draw("same"); */}
    c_lumi->cd(2); gPad->SetLogy(1);
    if(i_vz == 0) {h1_refMult3StPicoEvt_vzlumicorr_ru[i_vz]->Draw("hist e"); /* f_erf_ru[i_vz]->Draw("same"); */}
    else {h1_refMult3StPicoEvt_vzlumicorr_ru[i_vz]->Draw("hist same e"); /* f_erf_ru[i_vz]->Draw("same"); */}
  }

  TCanvas *c_vz_erf = new TCanvas("c_vz_erf", "c_vz_erf", 1200, 500);
  c_vz_erf->Divide(2,1);
  c_vz_erf->cd(1); gPad->SetGridy(1);
  gr_vz_erf_precorr_zr->Draw("ap"); gr_vz_erf_zr->Draw("psame");
  c_vz_erf->cd(2); gPad->SetGridy(1);
  gr_vz_erf_precorr_ru->Draw("ap"); gr_vz_erf_ru->Draw("psame");

  /////////Shape correction///////////
  cout<<"Merge bins from "<<vz[13]<<" cm to "<<vz[22]<<" cm to use it as central value"<<endl; // Whatch out vz[22] is from 9 cm to 11 cm so we use up to vz[21]
  TH1D *h1_refMult3StPicoEvt_central_zr =(TH1D*) h1_refMult3StPicoEvt_vzlumicorr_zr[13]->Clone("h1_refMult3StPicoEvt_central_zr");
  TH1D *h1_refMult3StPicoEvt_central_ru =(TH1D*) h1_refMult3StPicoEvt_vzlumicorr_ru[13]->Clone("h1_refMult3StPicoEvt_central_ru");
  for(int i_vz = 14 ; i_vz < 22 ; i_vz++){
    h1_refMult3StPicoEvt_central_zr->Add(h1_refMult3StPicoEvt_vzlumicorr_zr[i_vz]);
    h1_refMult3StPicoEvt_central_ru->Add(h1_refMult3StPicoEvt_vzlumicorr_ru[i_vz]);
  }

  TH1D *h1_refMult3StPicoEvt_shape_zr[30];
  TH1D *h1_refMult3StPicoEvt_shape_ru[30];
  TH1D *h1_refMult3StPicoEvt_shapecorr_zr[30];
  TH1D *h1_refMult3StPicoEvt_shapecorr_ru[30];
  TH1D *h1_refMult3StPicoEvt_corrshape_zr[30];
  TH1D *h1_refMult3StPicoEvt_corrshape_ru[30];
  float shapecorr_zr[30][1000];
  float shapecorr_ru[30][1000];
  for(int i_vz = 0 ; i_vz < 30 ; i_vz++){
    h1_refMult3StPicoEvt_shape_zr[i_vz] = (TH1D*)h1_refMult3StPicoEvt_vzlumicorr_zr[i_vz]->Clone(Form("h1_refMult3StPicoEvt_shape_zr_%d", i_vz)); h1_refMult3StPicoEvt_shape_zr[i_vz]->Divide(h1_refMult3StPicoEvt_central_zr);
    h1_refMult3StPicoEvt_shape_ru[i_vz] = (TH1D*)h1_refMult3StPicoEvt_vzlumicorr_ru[i_vz]->Clone(Form("h1_refMult3StPicoEvt_shape_ru_%d", i_vz)); h1_refMult3StPicoEvt_shape_ru[i_vz]->Divide(h1_refMult3StPicoEvt_central_ru);

    h1_refMult3StPicoEvt_corrshape_zr[i_vz] = (TH1D*)h1_refMult3StPicoEvt_vzlumicorr_zr[i_vz]->Clone(Form("h1_refMult3StPicoEvt_shape_zr_%d", i_vz));
    h1_refMult3StPicoEvt_corrshape_ru[i_vz] = (TH1D*)h1_refMult3StPicoEvt_vzlumicorr_ru[i_vz]->Clone(Form("h1_refMult3StPicoEvt_shape_ru_%d", i_vz));
    for(int i_mult = 0 ; i_mult < 1000 ; i_mult++){
      if(h1_refMult3StPicoEvt_vzlumicorr_zr[i_vz]->GetBinContent(i_mult+1) != 0) {
	h1_refMult3StPicoEvt_corrshape_zr[i_vz]->SetBinContent(i_mult+1, 1.0 * h1_refMult3StPicoEvt_vzlumicorr_zr[i_vz]->GetBinContent(i_mult+1) * h1_refMult3StPicoEvt_central_zr->GetBinContent(i_mult+1) / h1_refMult3StPicoEvt_vzlumicorr_zr[i_vz]->GetBinContent(i_mult+1));
	shapecorr_zr[i_vz][i_mult] = h1_refMult3StPicoEvt_central_zr->GetBinContent(i_mult+1) / h1_refMult3StPicoEvt_vzlumicorr_zr[i_vz]->GetBinContent(i_mult+1);
      }
      else {
	h1_refMult3StPicoEvt_corrshape_zr[i_vz]->SetBinContent(i_mult+1,  h1_refMult3StPicoEvt_central_zr->GetBinContent(i_mult+1));
	shapecorr_zr[i_vz][i_mult] = h1_refMult3StPicoEvt_central_zr->GetBinContent(i_mult+1);
      }
      if(h1_refMult3StPicoEvt_vzlumicorr_ru[i_vz]->GetBinContent(i_mult+1) != 0) {
	h1_refMult3StPicoEvt_corrshape_ru[i_vz]->SetBinContent(i_mult+1, 1.0 * h1_refMult3StPicoEvt_vzlumicorr_ru[i_vz]->GetBinContent(i_mult+1) * h1_refMult3StPicoEvt_central_ru->GetBinContent(i_mult+1) / h1_refMult3StPicoEvt_vzlumicorr_ru[i_vz]->GetBinContent(i_mult+1));
	shapecorr_ru[i_vz][i_mult] = h1_refMult3StPicoEvt_central_ru->GetBinContent(i_mult+1) / h1_refMult3StPicoEvt_vzlumicorr_ru[i_vz]->GetBinContent(i_mult+1);
      }
      else {
	h1_refMult3StPicoEvt_corrshape_ru[i_vz]->SetBinContent(i_mult+1,  h1_refMult3StPicoEvt_central_ru->GetBinContent(i_mult+1));
	shapecorr_ru[i_vz][i_mult] = h1_refMult3StPicoEvt_central_ru->GetBinContent(i_mult+1);
      }
    }
    /* h1_refMult3StPicoEvt_corrshape_zr[i_vz]->Divide(h1_refMult3StPicoEvt_central_zr); */
    /* h1_refMult3StPicoEvt_corrshape_ru[i_vz]->Divide(h1_refMult3StPicoEvt_central_ru); */
  }
  TCanvas *c_shape = new TCanvas("c_shape", "c_shape", 1200, 1500);
  c_shape->Divide(2,3);
  for(int i_vz = 0 ; i_vz < 30 ; i_vz++){
    c_shape->cd(1);// gPad->SetLogy(1);
    if(i_vz == 0) {h1_refMult3StPicoEvt_shape_zr[i_vz]->Draw("hist e");}
    else {h1_refMult3StPicoEvt_shape_zr[i_vz]->Draw("hist same e");}
    c_shape->cd(2);// gPad->SetLogy(1);
    if(i_vz == 0) {h1_refMult3StPicoEvt_shape_ru[i_vz]->Draw("hist e");}
    else {h1_refMult3StPicoEvt_shape_ru[i_vz]->Draw("hist same e");}
    c_shape->cd(5); gPad->SetLogy(1);
    if(i_vz == 0) {h1_refMult3StPicoEvt_corrshape_zr[i_vz]->Draw("hist e");}
    else {h1_refMult3StPicoEvt_corrshape_zr[i_vz]->Draw("hist same e");}
    c_shape->cd(6); gPad->SetLogy(1);
    if(i_vz == 0) {h1_refMult3StPicoEvt_corrshape_ru[i_vz]->Draw("hist e");}
    else {h1_refMult3StPicoEvt_corrshape_ru[i_vz]->Draw("hist same e");}
    c_lumi->cd(3); gPad->SetLogy(1);
    if(i_vz == 0) {h1_refMult3StPicoEvt_corrshape_zr[i_vz]->Draw("hist e"); /* f_erf_zr[i_vz]->Draw("same"); */}
    else {h1_refMult3StPicoEvt_corrshape_zr[i_vz]->Draw("hist same e"); /* f_erf_zr[i_vz]->Draw("same"); */}
    c_lumi->cd(4); gPad->SetLogy(1);
    if(i_vz == 0) {h1_refMult3StPicoEvt_corrshape_ru[i_vz]->Draw("hist e"); /* f_erf_ru[i_vz]->Draw("same"); */}
    else {h1_refMult3StPicoEvt_corrshape_ru[i_vz]->Draw("hist same e"); /* f_erf_ru[i_vz]->Draw("same"); */}
  }

  for(int i_vz = 0 ; i_vz < 30 ; i_vz++){
    h1_refMult3StPicoEvt_shapecorr_zr[i_vz] = (TH1D*)h1_refMult3StPicoEvt_corrshape_zr[i_vz]->Clone(Form("h1_refMult3StPicoEvt_shapecorr_zr_%d", i_vz)); h1_refMult3StPicoEvt_shapecorr_zr[i_vz]->Divide(h1_refMult3StPicoEvt_central_zr);
    h1_refMult3StPicoEvt_shapecorr_ru[i_vz] = (TH1D*)h1_refMult3StPicoEvt_corrshape_ru[i_vz]->Clone(Form("h1_refMult3StPicoEvt_shapecorr_ru_%d", i_vz)); h1_refMult3StPicoEvt_shapecorr_ru[i_vz]->Divide(h1_refMult3StPicoEvt_central_ru);
  }
  TH1D *h1_refMult3StPicoEvt_corrshape_tot_zr = new TH1D("h1_refMult3StPicoEvt_corrshape_tot_zr", "h1_refMult3StPicoEvt_corrshape_tot_zr", h1_refMult3StPicoEvt_corrshape_zr[0]->GetNbinsX(), h1_refMult3StPicoEvt_corrshape_zr[0]->GetXaxis()->GetXmin(), h1_refMult3StPicoEvt_corrshape_zr[0]->GetXaxis()->GetXmax());
  TH1D *h1_refMult3StPicoEvt_corrshape_tot_ru = new TH1D("h1_refMult3StPicoEvt_corrshape_tot_ru", "h1_refMult3StPicoEvt_corrshape_tot_ru", h1_refMult3StPicoEvt_corrshape_ru[0]->GetNbinsX(), h1_refMult3StPicoEvt_corrshape_ru[0]->GetXaxis()->GetXmin(), h1_refMult3StPicoEvt_corrshape_ru[0]->GetXaxis()->GetXmax());


  for(int i_vz = 0 ; i_vz < 30 ; i_vz++){
    h1_refMult3StPicoEvt_corrshape_tot_zr->Add(h1_refMult3StPicoEvt_corrshape_zr[i_vz], scale_fac_zr[i_vz]);
    h1_refMult3StPicoEvt_corrshape_tot_ru->Add(h1_refMult3StPicoEvt_corrshape_ru[i_vz], scale_fac_ru[i_vz]);

    /* for(int i_mult = 0 ; i_mult < 1000 ; i_mult++){ */
    /*   if(h1_refMult3StPicoEvt_vzlumicorr_zr[i_vz]->GetBinContent(i_mult+1) != 0) { */
    /* 	h1_refMult3StPicoEvt_corrshape_tot_zr->Fill(i_mult, 1.0 * h1_refMult3StPicoEvt_vzlumicorr_zr[i_vz]->GetBinContent(i_mult+1) * h1_refMult3StPicoEvt_central_zr->GetBinContent(i_mult+1) / h1_refMult3StPicoEvt_vzlumicorr_zr[i_vz]->GetBinContent(i_mult+1)); */
    /*   } */
    /*   else { */
    /* 	h1_refMult3StPicoEvt_corrshape_tot_zr->Fill(i_mult, h1_refMult3StPicoEvt_central_zr->GetBinContent(i_mult+1)); */
    /*   } */
    /*   if(h1_refMult3StPicoEvt_vzlumicorr_ru[i_vz]->GetBinContent(i_mult+1) != 0) { */
    /* 	h1_refMult3StPicoEvt_corrshape_tot_ru->Fill(i_mult, 1.0 * h1_refMult3StPicoEvt_vzlumicorr_ru[i_vz]->GetBinContent(i_mult+1) * h1_refMult3StPicoEvt_central_ru->GetBinContent(i_mult+1) / h1_refMult3StPicoEvt_vzlumicorr_ru[i_vz]->GetBinContent(i_mult+1)); */
    /*   } */
    /*   else { */
    /* 	h1_refMult3StPicoEvt_corrshape_tot_ru->Fill(i_mult, h1_refMult3StPicoEvt_central_ru->GetBinContent(i_mult+1)); */
    /*   } */
    /* } */
  }

  /* c_shape->cd(5); gPad->SetLogy(1); */
  /* h1_refMult3StPicoEvt_corrshape_tot_zr->Scale(1./h1_refMult3StPicoEvt_corrshape_tot_zr->Integral()); */
  /* h1_refMult3StPicoEvt_corrshape_tot_zr->Draw(); */
  /* c_shape->cd(6); gPad->SetLogy(1); */
  /* h1_refMult3StPicoEvt_corrshape_tot_ru->Scale(1./h1_refMult3StPicoEvt_corrshape_tot_ru->Integral()); */
  /* h1_refMult3StPicoEvt_corrshape_tot_ru->Draw(); */
  for(int i_vz = 0 ; i_vz < 30 ; i_vz++){
    c_shape->cd(3);// gPad->SetLogy(1);
    if(i_vz == 0) {h1_refMult3StPicoEvt_shapecorr_zr[i_vz]->Draw("hist e");}
    else {h1_refMult3StPicoEvt_shapecorr_zr[i_vz]->Draw("hist same e");}
    c_shape->cd(4);// gPad->SetLogy(1);
    if(i_vz == 0) {h1_refMult3StPicoEvt_shapecorr_ru[i_vz]->Draw("hist e");}
    else {h1_refMult3StPicoEvt_shapecorr_ru[i_vz]->Draw("hist same e");}
  }
  TFile *f_out = new TFile("output/ref3_shapecorr.root", "recreate");
  f_out->cd();
  h1_refMult3StPicoEvt_corrshape_tot_zr->Write("ref3_zr");
  h1_refMult3StPicoEvt_corrshape_tot_ru->Write("ref3_ru");
  f_out->Write();
  f_out->Close();
  
}
