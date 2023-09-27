void interpolate(){

  TFile *f_in = new TFile("gr_AntiProton_Zr_sys_6.root", "READ");
  TGraphErrors *gr_y_pt_eff_one_pP_p0 = (TGraphErrors*)f_in->Get("gr_y_pt_eff_one_pP_p0");// gr_y_pt_eff_one_pP_p0->RemovePoint(0);
  TGraphErrors *gr_y_pt_eff_one_pP_p1 = (TGraphErrors*)f_in->Get("gr_y_pt_eff_one_pP_p1");// gr_y_pt_eff_one_pP_p1->RemovePoint(0);
  TGraphErrors *gr_y_pt_eff_one_pP_p2 = (TGraphErrors*)f_in->Get("gr_y_pt_eff_one_pP_p2");// gr_y_pt_eff_one_pP_p2->RemovePoint(0);

  TCanvas *c1= new TCanvas("c1", "c1", 1500, 500); c1->Divide(3,1);
  c1->cd(1); gr_y_pt_eff_one_pP_p0->Draw("ap");
  c1->cd(2); gr_y_pt_eff_one_pP_p1->Draw("ap");
  c1->cd(3); gr_y_pt_eff_one_pP_p2->Draw("ap");

  double x[1000], y_pP_0[1000], y_pP_1[1000], y_pP_2[1000];

  for(int i = 0 ; i < 1000 ; i++){
    x[i] = i;
    y_pP_0[i] = gr_y_pt_eff_one_pP_p0->Eval(i, 0, "");
    y_pP_1[i] = gr_y_pt_eff_one_pP_p1->Eval(i, 0, "");
    y_pP_2[i] = gr_y_pt_eff_one_pP_p2->Eval(i, 0, "");
  }

  TGraph *gr_pP_p0 = new TGraph(1000, x, y_pP_0);
  TGraph *gr_pP_p1 = new TGraph(1000, x, y_pP_1);
  TGraph *gr_pP_p2 = new TGraph(1000, x, y_pP_2);

  TCanvas *c2= new TCanvas("c2", "c2", 1500, 500); c2->Divide(3,1);
  c2->cd(1); gr_pP_p0->Draw("ap");
  c2->cd(2); gr_pP_p1->Draw("ap");
  c2->cd(3); gr_pP_p2->Draw("ap");

  TF1 *f1_pP[9], *f2_pP[9];
  f1_pP[0] = new TF1("f1_pP_0", "pol2", 0.8, 2.);
  f1_pP[1] = new TF1("f1_pP_1", "pol2", 0.8, 2.);
  f1_pP[2] = new TF1("f1_pP_2", "pol2", 0.8, 2.);
  f1_pP[3] = new TF1("f1_pP_3", "pol2", 0.8, 2.);
  f1_pP[4] = new TF1("f1_pP_4", "pol2", 0.8, 2.);
  f1_pP[5] = new TF1("f1_pP_5", "pol2", 0.8, 2.);
  f1_pP[6] = new TF1("f1_pP_6", "pol2", 0.8, 2.);
  f1_pP[7] = new TF1("f1_pP_7", "pol2", 0.8, 2.);
  f1_pP[8] = new TF1("f1_pP_8", "pol2", 0.8, 2.);
  f2_pP[0] = new TF1("f2_pP_0", "pol2", 0.8, 2.);
  f2_pP[1] = new TF1("f2_pP_1", "pol2", 0.8, 2.);
  f2_pP[2] = new TF1("f2_pP_2", "pol2", 0.8, 2.);
  f2_pP[3] = new TF1("f2_pP_3", "pol2", 0.8, 2.);
  f2_pP[4] = new TF1("f2_pP_4", "pol2", 0.8, 2.);
  f2_pP[5] = new TF1("f2_pP_5", "pol2", 0.8, 2.);
  f2_pP[6] = new TF1("f2_pP_6", "pol2", 0.8, 2.);
  f2_pP[7] = new TF1("f2_pP_7", "pol2", 0.8, 2.);
  f2_pP[8] = new TF1("f2_pP_8", "pol2", 0.8, 2.);
  f1_pP[0]->SetTitle("at 256");
  f1_pP[1]->SetTitle("at 213");
  f1_pP[2]->SetTitle("at 147");
  f1_pP[3]->SetTitle("at 100");
  f1_pP[4]->SetTitle("at  65");
  f1_pP[5]->SetTitle("at  41");
  f1_pP[6]->SetTitle("at  25");
  f1_pP[7]->SetTitle("at  14");
  f1_pP[8]->SetTitle("at   7");
  f2_pP[0]->SetTitle("at 500");
  f2_pP[1]->SetTitle("at 256");
  f2_pP[2]->SetTitle("at 213");
  f2_pP[3]->SetTitle("at 147");
  f2_pP[4]->SetTitle("at 100");
  f2_pP[5]->SetTitle("at  65");
  f2_pP[6]->SetTitle("at  41");
  f2_pP[7]->SetTitle("at  25");
  f2_pP[8]->SetTitle("at  14");
  f1_pP[0]->SetParameter(0, gr_y_pt_eff_one_pP_p0->Eval(256, 0, ""));
  f1_pP[0]->SetParameter(1, gr_y_pt_eff_one_pP_p1->Eval(256, 0, ""));
  f1_pP[0]->SetParameter(2, gr_y_pt_eff_one_pP_p2->Eval(256, 0, ""));
  f1_pP[1]->SetParameter(0, gr_y_pt_eff_one_pP_p0->Eval(213, 0, ""));
  f1_pP[1]->SetParameter(1, gr_y_pt_eff_one_pP_p1->Eval(213, 0, ""));
  f1_pP[1]->SetParameter(2, gr_y_pt_eff_one_pP_p2->Eval(213, 0, ""));
  f1_pP[2]->SetParameter(0, gr_y_pt_eff_one_pP_p0->Eval(147, 0, ""));
  f1_pP[2]->SetParameter(1, gr_y_pt_eff_one_pP_p1->Eval(147, 0, ""));
  f1_pP[2]->SetParameter(2, gr_y_pt_eff_one_pP_p2->Eval(147, 0, ""));
  f1_pP[3]->SetParameter(0, gr_y_pt_eff_one_pP_p0->Eval(100, 0, ""));
  f1_pP[3]->SetParameter(1, gr_y_pt_eff_one_pP_p1->Eval(100, 0, ""));
  f1_pP[3]->SetParameter(2, gr_y_pt_eff_one_pP_p2->Eval(100, 0, ""));
  f1_pP[4]->SetParameter(0, gr_y_pt_eff_one_pP_p0->Eval(65, 0, ""));
  f1_pP[4]->SetParameter(1, gr_y_pt_eff_one_pP_p1->Eval(65, 0, ""));
  f1_pP[4]->SetParameter(2, gr_y_pt_eff_one_pP_p2->Eval(65, 0, ""));
  f1_pP[5]->SetParameter(0, gr_y_pt_eff_one_pP_p0->Eval(41, 0, ""));
  f1_pP[5]->SetParameter(1, gr_y_pt_eff_one_pP_p1->Eval(41, 0, ""));
  f1_pP[5]->SetParameter(2, gr_y_pt_eff_one_pP_p2->Eval(41, 0, ""));
  f1_pP[6]->SetParameter(0, gr_y_pt_eff_one_pP_p0->Eval(25, 0, ""));
  f1_pP[6]->SetParameter(1, gr_y_pt_eff_one_pP_p1->Eval(25, 0, ""));
  f1_pP[6]->SetParameter(2, gr_y_pt_eff_one_pP_p2->Eval(25, 0, ""));
  f1_pP[7]->SetParameter(0, gr_y_pt_eff_one_pP_p0->Eval(14, 0, ""));
  f1_pP[7]->SetParameter(1, gr_y_pt_eff_one_pP_p1->Eval(14, 0, ""));
  f1_pP[7]->SetParameter(2, gr_y_pt_eff_one_pP_p2->Eval(14, 0, ""));
  f1_pP[8]->SetParameter(0, gr_y_pt_eff_one_pP_p0->Eval(7, 0, ""));
  f1_pP[8]->SetParameter(1, gr_y_pt_eff_one_pP_p1->Eval(7, 0, ""));
  f1_pP[8]->SetParameter(2, gr_y_pt_eff_one_pP_p2->Eval(7, 0, ""));
  f2_pP[0]->SetParameter(0, gr_y_pt_eff_one_pP_p0->Eval(500, 0, ""));
  f2_pP[0]->SetParameter(1, gr_y_pt_eff_one_pP_p1->Eval(500, 0, ""));
  f2_pP[0]->SetParameter(2, gr_y_pt_eff_one_pP_p2->Eval(500, 0, ""));
  f2_pP[1]->SetParameter(0, gr_y_pt_eff_one_pP_p0->Eval(256, 0, ""));
  f2_pP[1]->SetParameter(1, gr_y_pt_eff_one_pP_p1->Eval(256, 0, ""));
  f2_pP[1]->SetParameter(2, gr_y_pt_eff_one_pP_p2->Eval(256, 0, ""));
  f2_pP[2]->SetParameter(0, gr_y_pt_eff_one_pP_p0->Eval(213, 0, ""));
  f2_pP[2]->SetParameter(1, gr_y_pt_eff_one_pP_p1->Eval(213, 0, ""));
  f2_pP[2]->SetParameter(2, gr_y_pt_eff_one_pP_p2->Eval(213, 0, ""));
  f2_pP[3]->SetParameter(0, gr_y_pt_eff_one_pP_p0->Eval(147, 0, ""));
  f2_pP[3]->SetParameter(1, gr_y_pt_eff_one_pP_p1->Eval(147, 0, ""));
  f2_pP[3]->SetParameter(2, gr_y_pt_eff_one_pP_p2->Eval(147, 0, ""));
  f2_pP[4]->SetParameter(0, gr_y_pt_eff_one_pP_p0->Eval(100, 0, ""));
  f2_pP[4]->SetParameter(1, gr_y_pt_eff_one_pP_p1->Eval(100, 0, ""));
  f2_pP[4]->SetParameter(2, gr_y_pt_eff_one_pP_p2->Eval(100, 0, ""));
  f2_pP[5]->SetParameter(0, gr_y_pt_eff_one_pP_p0->Eval(65, 0, ""));
  f2_pP[5]->SetParameter(1, gr_y_pt_eff_one_pP_p1->Eval(65, 0, ""));
  f2_pP[5]->SetParameter(2, gr_y_pt_eff_one_pP_p2->Eval(65, 0, ""));
  f2_pP[6]->SetParameter(0, gr_y_pt_eff_one_pP_p0->Eval(41, 0, ""));
  f2_pP[6]->SetParameter(1, gr_y_pt_eff_one_pP_p1->Eval(41, 0, ""));
  f2_pP[6]->SetParameter(2, gr_y_pt_eff_one_pP_p2->Eval(41, 0, ""));
  f2_pP[7]->SetParameter(0, gr_y_pt_eff_one_pP_p0->Eval(25, 0, ""));
  f2_pP[7]->SetParameter(1, gr_y_pt_eff_one_pP_p1->Eval(25, 0, ""));
  f2_pP[7]->SetParameter(2, gr_y_pt_eff_one_pP_p2->Eval(25, 0, ""));
  f2_pP[8]->SetParameter(0, gr_y_pt_eff_one_pP_p0->Eval(14, 0, ""));
  f2_pP[8]->SetParameter(1, gr_y_pt_eff_one_pP_p1->Eval(14, 0, ""));
  f2_pP[8]->SetParameter(2, gr_y_pt_eff_one_pP_p2->Eval(14, 0, ""));

  TCanvas *c3= new TCanvas("c3", "c3", 2000, 1000); c3->Divide(5,2);
  for(int i_cent = 0 ; i_cent < 9 ; i_cent++){
    c3->cd(i_cent + 2);
    /* f1_pP[i_cent]->GetXaxis()->SetRangeUser(0.8, 2); */
    f1_pP[i_cent]->GetYaxis()->SetRangeUser(0.7, 0.8);
    f1_pP[i_cent]->Draw();
    f2_pP[i_cent]->SetLineColor(4);
    f2_pP[i_cent]->Draw("same");
  }
}
