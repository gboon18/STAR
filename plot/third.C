
void drawLine(double x1=0., double y1=0., double x2=0., double y2=1., int lineWidth=1, int lineStyle=1, int lineColor=1)

{
  TLine *la = new TLine(x1,y1,x2,y2);
  la->SetLineWidth(lineWidth);
  la->SetLineStyle(lineStyle);
  la->SetLineColor(lineColor);
  la->Draw("same");
}
void drawBox(double x1=0., double y1=0., double x2=0., double y2=1., int fillColor=1, double fillAlpha=1.)
{
  TBox *la = new TBox(x1,y1,x2,y2);
  la->SetLineColorAlpha(0,0);
  la->SetFillColorAlpha(fillColor, fillAlpha);
  la->Draw("same");
}

void third(int merge_counter = 4, bool scale = true){
  
  float pp_scale = 0.9;
  float iso_scale = (1.-0.14);
  if(!scale){pp_scale = 1.; iso_scale = 1.;}
  
  ifstream myfile_in;

  myfile_in.open("input/pp_Jan2023_Ratio_C4C2.txt");
  const int n = 12-2;
  
  double xx[n];
  double yc4[n], eyc4[n], syc4[n];
  for(int i=0; i<n; i++){
    myfile_in>>xx[i]>>yc4[i]>>eyc4[i]>>syc4[i];
    xx[i] *= pp_scale; 
  }
  myfile_in.close();
  TGraphErrors *gr_pp_CR_4_2 = new TGraphErrors(n, xx, yc4, 0, eyc4);
  TGraphErrors *gr_pp_CR_4_2_sys = new TGraphErrors(n, xx, yc4, 0, syc4);
  gr_pp_CR_4_2->SetMarkerStyle(34);    gr_pp_CR_4_2->SetMarkerSize(1.15);    gr_pp_CR_4_2->SetMarkerColor(kAzure-3);    gr_pp_CR_4_2->SetLineWidth(2);    gr_pp_CR_4_2->SetLineColor(12);
  gr_pp_CR_4_2_sys->SetMarkerStyle(28);    gr_pp_CR_4_2_sys->SetMarkerSize(1.15);    gr_pp_CR_4_2_sys->SetMarkerColor(kAzure-3);    gr_pp_CR_4_2_sys->SetLineWidth(1);    gr_pp_CR_4_2_sys->SetLineColorAlpha(kAzure-3, 0.25); gr_pp_CR_4_2_sys->SetLineWidth(2); gr_pp_CR_4_2_sys->SetFillStyle(3000);

  
  TGraphErrors *gr_pp_CR_4_2_CBWC, *gr_pp_CR_4_2_sys_CBWC;
  const Double_t mxc4[1]={6.92655*pp_scale};  const Double_t myc4[1]={0.879491};  const Double_t myc4e[1]={0.0006627};  const Double_t myc4s[1]={0.00790745};
  gr_pp_CR_4_2_CBWC = new TGraphErrors(1, mxc4, myc4, 0, myc4e); 
  gr_pp_CR_4_2_CBWC->SetMarkerStyle(34);    gr_pp_CR_4_2_CBWC->SetMarkerSize(1.7);    gr_pp_CR_4_2_CBWC->SetMarkerColor(kCyan+3);    gr_pp_CR_4_2_CBWC->SetLineWidth(1);    gr_pp_CR_4_2_CBWC->SetLineColor(12);
  gr_pp_CR_4_2_sys_CBWC = new TGraphErrors(1, mxc4, myc4, 0, myc4s); 
  gr_pp_CR_4_2_sys_CBWC->SetMarkerStyle(34);    gr_pp_CR_4_2_sys_CBWC->SetMarkerSize(1.95);    gr_pp_CR_4_2_sys_CBWC->SetMarkerColor(12);    gr_pp_CR_4_2_sys_CBWC->SetLineWidth(1);    gr_pp_CR_4_2_sys_CBWC->SetFillColorAlpha(kAzure-3, 0.5);

  
  myfile_in.open("input/pp_cr42_Feb2022.txt");
  const int n_pp_feb22 = 8;
  double xx_feb22[n];
  double yc4_feb22[n], eyc4_feb22[n], syc4_feb22[n];
  for(int i=0; i<n_pp_feb22; i++){
    myfile_in>>xx_feb22[i]>>yc4_feb22[i]>>eyc4_feb22[i]>>syc4_feb22[i];
  }
  myfile_in.close();
  TGraphErrors *gr_pp_CR_4_2_feb22 = new TGraphErrors(n_pp_feb22, xx_feb22, yc4_feb22, 0, eyc4_feb22);
  TGraphErrors *gr_pp_CR_4_2_sys_feb22 = new TGraphErrors(n_pp_feb22, xx_feb22, yc4_feb22, 0, syc4_feb22);
  gr_pp_CR_4_2_feb22->SetMarkerStyle(8);    gr_pp_CR_4_2_feb22->SetMarkerSize(1.15);    gr_pp_CR_4_2_feb22->SetMarkerColor(12);    gr_pp_CR_4_2_feb22->SetLineWidth(2);    gr_pp_CR_4_2_feb22->SetLineColor(12);
  gr_pp_CR_4_2_sys_feb22->SetMarkerStyle(4);    gr_pp_CR_4_2_sys_feb22->SetMarkerSize(1.15);    gr_pp_CR_4_2_sys_feb22->SetMarkerColor(2);    gr_pp_CR_4_2_sys_feb22->SetLineWidth(1);    gr_pp_CR_4_2_sys_feb22->SetFillColorAlpha(kAzure-3, 0.5);

  TGraphErrors *gr_pp_CR_4_2_CBWC_feb22, *gr_pp_CR_4_2_sys_CBWC_feb22;
  const Double_t mxc4_feb22[1]={7.12864};  const Double_t myc4_feb22[1]={0.875238};  const Double_t myc4e_feb22[1]={0.000952124};  const Double_t myc4s_feb22[1]={0.01097}; 
  gr_pp_CR_4_2_CBWC_feb22 = new TGraphErrors(1, mxc4_feb22, myc4_feb22, 0, myc4e_feb22); 
  gr_pp_CR_4_2_CBWC_feb22->SetMarkerStyle(8);    gr_pp_CR_4_2_CBWC_feb22->SetMarkerSize(1.7);    gr_pp_CR_4_2_CBWC_feb22->SetMarkerColor(kCyan+3);    gr_pp_CR_4_2_CBWC_feb22->SetLineWidth(1);    gr_pp_CR_4_2_CBWC_feb22->SetLineColor(12);
  gr_pp_CR_4_2_sys_CBWC_feb22 = new TGraphErrors(1, mxc4_feb22, myc4_feb22, 0, myc4s_feb22); 
  gr_pp_CR_4_2_sys_CBWC_feb22->SetMarkerStyle(4);    gr_pp_CR_4_2_sys_CBWC_feb22->SetMarkerSize(1.95);    gr_pp_CR_4_2_sys_CBWC_feb22->SetMarkerColor(12);    gr_pp_CR_4_2_sys_CBWC_feb22->SetLineWidth(1);    gr_pp_CR_4_2_sys_CBWC_feb22->SetFillColorAlpha(kAzure-3, 0.5);
  
  
  
  int na_cr_4_2=9-merge_counter;
  const int na=5;
  double xa[na_cr_4_2], yac4[na_cr_4_2], eyac4[na_cr_4_2], syac4[na_cr_4_2];
  
  myfile_in.open("input/auau_cr42_from_Ashish_31012023_1.txt");
  for(int i=0; i<na_cr_4_2; i++)
    { 
      
      
      myfile_in>>xa[i]>>yac4[i]>>eyac4[i]>>syac4[i];
      
    }
  myfile_in.close();
  TGraphErrors *gr_auau_CR_4_2 = new TGraphErrors(na_cr_4_2, xa, yac4, 0, eyac4); 
  gr_auau_CR_4_2->SetMarkerStyle(26);    gr_auau_CR_4_2->SetMarkerSize(1.5);    gr_auau_CR_4_2->SetMarkerColor(2);    gr_auau_CR_4_2->SetLineWidth(1);    gr_auau_CR_4_2->SetLineColor(2);
  
  TGraphErrors *gr_auau_CR_4_2_sys = new TGraphErrors(na_cr_4_2, xa, yac4, 0, syac4); 
  gr_auau_CR_4_2_sys->SetMarkerStyle(26);    gr_auau_CR_4_2_sys->SetMarkerSize(1.5);    gr_auau_CR_4_2_sys->SetMarkerColor(2);    gr_auau_CR_4_2_sys->SetLineWidth(4); gr_auau_CR_4_2_sys->SetLineColorAlpha(kRed, 0.2); gr_auau_CR_4_2_sys->SetFillStyle(3000);
  
  
  
  int nru=9-merge_counter;
  double xru[nru], yruc4[nru], eyruc4[nru], syruc4[nru];
  
  myfile_in.open("./output/files/third/ru_cr42_4.txt");
  for(int i=0; i<nru; i++)
    { 
      myfile_in>>xru[i]>>yruc4[i]>>eyruc4[i]>>syruc4[i];
      xru[i] *= iso_scale; 
      
      
      
    }
  myfile_in.close();
  TGraphErrors *gr_ru_CR_4_2 = new TGraphErrors(nru, xru, yruc4, 0, eyruc4); 
  TGraphErrors *gr_ru_CR_4_2_sys = new TGraphErrors(nru, xru, yruc4, 0, syruc4); 
  gr_ru_CR_4_2->SetMarkerStyle(8);    gr_ru_CR_4_2->SetMarkerSize(1.5);    gr_ru_CR_4_2->SetMarkerColor(1);    gr_ru_CR_4_2->SetLineWidth(1);    gr_ru_CR_4_2->SetLineColor(1);
  gr_ru_CR_4_2_sys->SetMarkerStyle(8);    gr_ru_CR_4_2_sys->SetMarkerSize(1.5);    gr_ru_CR_4_2_sys->SetMarkerColor(1);    gr_ru_CR_4_2_sys->SetLineWidth(4); gr_ru_CR_4_2_sys->SetLineColorAlpha(kGray+3, 0.5); gr_ru_CR_4_2_sys->SetFillStyle(3000);
  
  int nzr=9-merge_counter;
  double xzr[nzr], yzrc4[nzr], eyzrc4[nzr], syzrc4[nzr];
  
  myfile_in.open("./output/files/third/zr_cr42_4.txt");
  for(int i=0; i<nzr; i++)
    { 
      myfile_in>>xzr[i]>>yzrc4[i]>>eyzrc4[i]>>syzrc4[i];
      xzr[i] *= iso_scale; 
      
      
    }
  myfile_in.close();
  TGraphErrors *gr_zr_CR_4_2 = new TGraphErrors(nzr, xzr, yzrc4, 0, eyzrc4); 
  TGraphErrors *gr_zr_CR_4_2_sys = new TGraphErrors(nzr, xzr, yzrc4, 0, syzrc4); 
  gr_zr_CR_4_2->SetMarkerStyle(4);    gr_zr_CR_4_2->SetMarkerSize(1.5);    gr_zr_CR_4_2->SetMarkerColor(1);    gr_zr_CR_4_2->SetLineWidth(1);    gr_zr_CR_4_2->SetLineColor(1);
  gr_zr_CR_4_2_sys->SetMarkerStyle(4);    gr_zr_CR_4_2_sys->SetMarkerSize(1.5);    gr_zr_CR_4_2_sys->SetMarkerColor(1);    gr_zr_CR_4_2_sys->SetLineWidth(4); gr_zr_CR_4_2_sys->SetLineColorAlpha(kGray+3, 0.5); gr_zr_CR_4_2_sys->SetFillStyle(3000);

  
  gr_pp_CR_4_2->GetXaxis()->SetLimits(3, 1e3);
  
  gr_pp_CR_4_2->GetYaxis()->SetRangeUser(0.05, 1.12);
  gr_pp_CR_4_2->GetXaxis()->SetLimits(2.5, 2000);
  gr_pp_CR_4_2->SetTitle("C_{4}/C_{2}");
  gr_pp_CR_4_2->GetYaxis()->CenterTitle();
  gr_pp_CR_4_2->GetXaxis()->CenterTitle();
  gr_pp_CR_4_2->GetYaxis()->SetTitleOffset(.8);
  gr_pp_CR_4_2->GetXaxis()->SetTitleOffset(.9);
  gr_pp_CR_4_2->GetYaxis()->SetTitleSize(0.06);
  gr_pp_CR_4_2->GetXaxis()->SetTitleSize(0.055);
  
  
  gr_pp_CR_4_2->GetXaxis()->SetTitle("<Charged Particle Multiplicity>");
  
  
  gr_pp_CR_4_2->GetXaxis()->SetNoExponent();
  gr_pp_CR_4_2->GetXaxis()->SetLabelSize(0.05);
  gr_pp_CR_4_2->GetYaxis()->SetLabelSize(0.05);
  TCanvas *c_buff = new TCanvas("c_buff","c_buff",700,500);
  c_buff->cd();
  gr_pp_CR_4_2->Draw("AP");
  gr_pp_CR_4_2_sys->Draw("P SAME");
  
  gr_auau_CR_4_2->Draw("P SAME");
  gr_ru_CR_4_2->Draw("P SAME");
  gr_ru_CR_4_2_sys->Draw("2 SAME");
  gr_zr_CR_4_2->Draw("P SAME");
  gr_zr_CR_4_2_sys->Draw("2 SAME");
  
  TLine *l_CR_4_2_CBWC_ref3_HRG = new TLine(0, 0.997, gr_pp_CR_4_2->GetXaxis()->GetXmax(), 0.997);
  l_CR_4_2_CBWC_ref3_HRG->SetLineStyle(9);
  l_CR_4_2_CBWC_ref3_HRG->SetLineWidth(1);
  l_CR_4_2_CBWC_ref3_HRG->Draw("SAME");
  
  TBox *box_CR_4_2_lQCD = new TBox(700, 0.65, 1800, 0.77);
  box_CR_4_2_lQCD->SetFillColorAlpha(kRed+2, 1.0); box_CR_4_2_lQCD->SetLineColorAlpha(kRed+2, 1.0); box_CR_4_2_lQCD->Draw("SAME");

  TBox *box_cr42_frg = new TBox(700, 0.56699950, 1800, 0.66877324); 
  box_cr42_frg->SetFillColorAlpha(kGreen+3, 0.8); box_cr42_frg->SetLineColorAlpha(kGreen+3, 1.0);

  TPaveText *SP_topright = new TPaveText(.48,.72,.88,.99, "NDC NB");
  SP_topright->SetTextColor(2); SP_topright->AddText("STAR Preliminary"); SP_topright->SetFillColorAlpha(0, 0);
  TPaveText *SP_topleft = new TPaveText(.11,.85,.51,0.95, "NDC NB");
  SP_topleft->SetTextColor(2); SP_topleft->AddText("STAR Preliminary"); SP_topleft->SetFillColorAlpha(0, 0);
  
  
  TPaveText *Info1_topleft = new TPaveText(.34,.225,.75,.375, "NDC NB");
  
  Info1_topleft->AddText("#sqrt{s_{NN}} = 200 GeV");
  Info1_topleft->SetFillColorAlpha(0, 0);
  
  TPaveText *Info1_bottommid = new TPaveText(.06,.25,.8,.38, "NDC NB");
  Info1_bottommid->AddText("Net-Proton, |y| < 0.5");
  Info1_bottommid->AddText("0.4 < p_{T} < 2.0 GeV/c");
  
  Info1_bottommid->SetFillColorAlpha(0, 0);

  
  double xp1=5,   xp2=35;    
  
  

  double xa1=16,  xa2=32,   xa3=68,   xa4=120,   xa5=196,   xa6=1180;
  double ya1=.62,   ya2=.64;
  drawLine(xa1,ya1,xa2,ya1,1,1,7);  drawLine(xa1,ya1,xa1,ya2,1,1,7);  drawLine(xa2,ya1,xa2,ya2,1,1,7);
  drawLine(xa2,ya1,xa3,ya1,1,1,7);  drawLine(xa3,ya1,xa3,ya2,1,1,7); 
  drawLine(xa4,ya1,xa3,ya1,1,1,7);  drawLine(xa4,ya1,xa4,ya2,1,1,7); 
  drawLine(xa4,ya1,xa5,ya1,1,1,7);  drawLine(xa5,ya1,xa5,ya2,1,1,7); 
  drawLine(xa6,ya1,xa5,ya1,1,1,7);  drawLine(xa6,ya1,xa6,ya2,1,1,7);

  double xru1=13,  xru2=25,   xru3=44,   xru4=73,   xru5=116,   xru6=175,   xru7=256,   xru8=367,   xru9=440,   xru10=700;
  
  double yru1=.18,   yru2=.20;
  drawLine(xru1,yru1,xru2,yru1,1,1,9);  drawLine(xru1,yru1,xru1,yru2,1,1,9);  drawLine(xru2,yru1,xru2,yru2,1,1,9);
  drawLine(xru2,yru1,xru3,yru1,1,1,9);  drawLine(xru3,yru1,xru3,yru2,1,1,9); 
  drawLine(xru4,yru1,xru3,yru1,1,1,9);  drawLine(xru4,yru1,xru4,yru2,1,1,9); 
  drawLine(xru4,yru1,xru5,yru1,1,1,9);  drawLine(xru5,yru1,xru5,yru2,1,1,9); 
  drawLine(xru5,yru1,xru6,yru1,1,1,9);  drawLine(xru6,yru1,xru6,yru2,1,1,9);
  drawLine(xru6,yru1,xru7,yru1,1,1,9);  drawLine(xru7,yru1,xru7,yru2,1,1,9);
  drawLine(xru7,yru1,xru8,yru1,1,1,9);  drawLine(xru8,yru1,xru8,yru2,1,1,9);
  
  drawLine(xru6,yru1,xru7,yru1,1,1,9);
  drawLine(xru7,yru1,xru8,yru1,1,1,9);
  drawLine(xru8,yru1,xru9,yru1,1,1,9);
  drawLine(xru9,yru1,xru10,yru1,1,1,9);  drawLine(xru10,yru1,xru10,yru2,1,1,9);

  TLatex*latex = new TLatex();
  latex->SetTextAlign(30);   latex->SetTextFont(82);   latex->SetTextSize(0.035);   latex->SetTextAngle(25); 
  latex->DrawLatex(25,0.59,"70-80%"); 
  latex->DrawLatex(50,0.59,"60-70%"); 
  latex->DrawLatex(90,0.59,"50-60%"); 
  latex->DrawLatex(180,0.59,"40-50%"); 
  latex->DrawLatex(650,0.59,"0-40%");

  latex->SetTextAlign(30);   latex->SetTextFont(82);   latex->SetTextSize(0.025);   latex->SetTextAngle(25); 
  latex->DrawLatex(0.5*(13+25),0.45,"70-80%"); 
  latex->DrawLatex(0.5*(25+43),0.45,"60-70%"); 
  latex->DrawLatex(0.5*(43+72),0.45,"50-60%"); 
  latex->DrawLatex(0.5*(72+114),0.45,"40-50%"); 
  latex->DrawLatex(0.5*(114+173),0.45,"30-40%");
  
  
  
  latex->DrawLatex(0.5*(439+800),0.45,"0-5%");

  latex->SetTextSize(0.04);     latex->SetTextFont(42);  latex->SetTextColor(kCyan+2);   latex->SetTextAngle(0);
  latex->DrawLatex(25-13,0.61,"Au+Au: ");
  latex->SetTextSize(0.04);     latex->SetTextFont(42);  latex->SetTextColor(9);   latex->SetTextAngle(0);
  latex->DrawLatex(25-13-2, 0.47,"Zr#oplusRu: ");
  

  TBox *box_CR_4_2 = new TBox(gr_pp_CR_4_2->GetXaxis()->GetXmin(), -1.45, gr_pp_CR_4_2->GetXaxis()->GetXmax(),0);
  box_CR_4_2->SetFillColorAlpha(kCyan-10, 0.25);
  

  
  double x21 = 6.894-3.993, x22 = 6.894+3.993, y01 = 0.986;
  
  
  drawLine(x21,y01,x22,y01,5,1,41);

  TBox *line_pythia = new TBox();
  line_pythia->SetLineColor(41);
  line_pythia->SetFillColor(41);
  
  TLegend *leg_CR_4_2 = new TLegend(0.1, 0.12, 0.4, 0.47);
  
  leg_CR_4_2->AddEntry(gr_pp_CR_4_2, "p+p", "p");
  
  leg_CR_4_2->AddEntry(gr_auau_CR_4_2, "Au+Au", "p"); 
  
  
  leg_CR_4_2->AddEntry(gr_zr_CR_4_2, "Zr+Zr", "p");
  leg_CR_4_2->AddEntry(gr_ru_CR_4_2, "Ru+Ru", "p");
  
  leg_CR_4_2->SetFillColorAlpha(kCyan-10, 0.0);
  leg_CR_4_2->SetLineColorAlpha(0, 0);
  leg_CR_4_2->Draw("SAME");
  
  myfile_in.open("input/pp_Jan2023_Ratio_C5C1.txt");
  double yc5[n], eyc5[n], syc5[n];
  for(int i=0; i<n; i++){
    myfile_in>>xx[i]>>yc5[i]>>eyc5[i]>>syc5[i];
    xx[i] *= pp_scale; 
  }
  myfile_in.close();
  TGraphErrors *gr_pp_CR_5_1 = new TGraphErrors(n, xx, yc5, 0, eyc5);
  TGraphErrors *gr_pp_CR_5_1_sys = new TGraphErrors(n, xx, yc5, 0, syc5);
  gr_pp_CR_5_1->SetMarkerStyle(34);    gr_pp_CR_5_1->SetMarkerSize(1.15);    gr_pp_CR_5_1->SetMarkerColor(kAzure-3);    gr_pp_CR_5_1->SetLineWidth(2);    gr_pp_CR_5_1->SetLineColor(12);
  gr_pp_CR_5_1_sys->SetMarkerStyle(28);    gr_pp_CR_5_1_sys->SetMarkerSize(1.15);    gr_pp_CR_5_1_sys->SetMarkerColor(kAzure-3);    gr_pp_CR_5_1_sys->SetLineWidth(1);    gr_pp_CR_5_1_sys->SetLineColorAlpha(kAzure-3, 0.25); gr_pp_CR_5_1_sys->SetLineWidth(2); gr_pp_CR_5_1_sys->SetFillStyle(3000);

  
  TGraphErrors *gr_pp_CR_5_1_CBWC, *gr_pp_CR_5_1_sys_CBWC;
  const Double_t mxc5[1]={6.92655*pp_scale};  const Double_t myc5[1]={0.51666};  const Double_t myc5e[1]={0.0101024};  const Double_t myc5s[1]={0.0403578};
  gr_pp_CR_5_1_CBWC = new TGraphErrors(1, mxc5, myc5, 0, myc5e); 
  gr_pp_CR_5_1_CBWC->SetMarkerStyle(34);    gr_pp_CR_5_1_CBWC->SetMarkerSize(1.7);    gr_pp_CR_5_1_CBWC->SetMarkerColor(kCyan+3);    gr_pp_CR_5_1_CBWC->SetLineWidth(1);    gr_pp_CR_5_1_CBWC->SetLineColor(12);
  gr_pp_CR_5_1_sys_CBWC = new TGraphErrors(1, mxc5, myc5, 0, myc5s); 
  gr_pp_CR_5_1_sys_CBWC->SetMarkerStyle(34);    gr_pp_CR_5_1_sys_CBWC->SetMarkerSize(1.95);    gr_pp_CR_5_1_sys_CBWC->SetMarkerColor(12);    gr_pp_CR_5_1_sys_CBWC->SetLineWidth(1);    gr_pp_CR_5_1_sys_CBWC->SetFillColorAlpha(kAzure-3, 0.5);

  
  myfile_in.open("input/pp_cr51_Feb2022.txt");
  double yc5_feb22[n], eyc5_feb22[n], syc5_feb22[n];
  for(int i=0; i<n_pp_feb22; i++){
    myfile_in>>xx_feb22[i]>>yc5_feb22[i]>>eyc5_feb22[i]>>syc5_feb22[i];
  }
  myfile_in.close();
  TGraphErrors *gr_pp_CR_5_1_feb22 = new TGraphErrors(n_pp_feb22, xx_feb22, yc5_feb22, 0, eyc5_feb22);
  TGraphErrors *gr_pp_CR_5_1_sys_feb22 = new TGraphErrors(n_pp_feb22, xx_feb22, yc5_feb22, 0, syc5_feb22);
  gr_pp_CR_5_1_feb22->SetMarkerStyle(8);    gr_pp_CR_5_1_feb22->SetMarkerSize(1.15);    gr_pp_CR_5_1_feb22->SetMarkerColor(12);    gr_pp_CR_5_1_feb22->SetLineWidth(2);    gr_pp_CR_5_1_feb22->SetLineColor(12);
  gr_pp_CR_5_1_sys_feb22->SetMarkerStyle(4);    gr_pp_CR_5_1_sys_feb22->SetMarkerSize(1.15);    gr_pp_CR_5_1_sys_feb22->SetMarkerColor(2);    gr_pp_CR_5_1_sys_feb22->SetLineWidth(1);    gr_pp_CR_5_1_sys_feb22->SetFillColorAlpha(kAzure-3, 0.5); 

  TGraphErrors *gr_pp_CR_5_1_CBWC_feb22, *gr_pp_CR_5_1_sys_CBWC_feb22;
  const Double_t mxc5_feb22[1]={7.12864};  const Double_t myc5_feb22[1]={0.504759};  const Double_t myc5e_feb22[1]={0.015358};  const Double_t myc5s_feb22[1]={0.0604613}; 
  gr_pp_CR_5_1_CBWC_feb22 = new TGraphErrors(1, mxc5_feb22, myc5_feb22, 0, myc5e_feb22); 
  gr_pp_CR_5_1_CBWC_feb22->SetMarkerStyle(8);    gr_pp_CR_5_1_CBWC_feb22->SetMarkerSize(1.7);    gr_pp_CR_5_1_CBWC_feb22->SetMarkerColor(kCyan+3);    gr_pp_CR_5_1_CBWC_feb22->SetLineWidth(1);    gr_pp_CR_5_1_CBWC_feb22->SetLineColor(12);
  gr_pp_CR_5_1_sys_CBWC_feb22 = new TGraphErrors(1, mxc5_feb22, myc5_feb22, 0, myc5s_feb22); 
  gr_pp_CR_5_1_sys_CBWC_feb22->SetMarkerStyle(4);    gr_pp_CR_5_1_sys_CBWC_feb22->SetMarkerSize(1.95);    gr_pp_CR_5_1_sys_CBWC_feb22->SetMarkerColor(12);    gr_pp_CR_5_1_sys_CBWC_feb22->SetLineWidth(1);    gr_pp_CR_4_2_sys_CBWC_feb22->SetFillColorAlpha(kAzure-3, 0.5);
  

  
  double yac5[na], eyac5[na], syac5[na];
  
  myfile_in.open("input/auau_cr51_from_Ashish_31012023_1.txt");
  for(int i=0; i<na; i++)
    { 
      
      
      myfile_in>>xa[i]>>yac5[i]>>eyac5[i]>>syac5[i];
      
    }
  myfile_in.close();
  TGraphErrors *gr_auau_CR_5_1 = new TGraphErrors(na, xa, yac5, 0, eyac5); 
  gr_auau_CR_5_1->SetMarkerStyle(26);    gr_auau_CR_5_1->SetMarkerSize(1.5);    gr_auau_CR_5_1->SetMarkerColor(2);    gr_auau_CR_5_1->SetLineWidth(1);    gr_auau_CR_5_1->SetLineColor(2);
  
  TGraphErrors *gr_auau_CR_5_1_sys = new TGraphErrors(na, xa, yac5, 0, syac5); 
  gr_auau_CR_5_1_sys->SetMarkerStyle(26);    gr_auau_CR_5_1_sys->SetMarkerSize(1.5);    gr_auau_CR_5_1_sys->SetMarkerColor(2);    gr_auau_CR_5_1_sys->SetLineWidth(4); gr_auau_CR_5_1_sys->SetLineColorAlpha(kRed, 0.2); gr_auau_CR_5_1_sys->SetFillStyle(3000);
  
  
  
  double yruc5[nru], eyruc5[nru], syruc5[nru];
  
  myfile_in.open("./output/files/third/ru_cr51_4.txt");
  for(int i=0; i<nru; i++)
    { 
      myfile_in>>xru[i]>>yruc5[i]>>eyruc5[i]>>syruc5[i];
      xru[i] *= iso_scale; 
      
    }
  myfile_in.close();
  TGraphErrors *gr_ru_CR_5_1 = new TGraphErrors(nru, xru, yruc5, 0, eyruc5); 
  TGraphErrors *gr_ru_CR_5_1_sys = new TGraphErrors(nru, xru, yruc5, 0, syruc5); 
  gr_ru_CR_5_1->SetMarkerStyle(8);    gr_ru_CR_5_1->SetMarkerSize(1.5);    gr_ru_CR_5_1->SetMarkerColor(1);    gr_ru_CR_5_1->SetLineWidth(1);    gr_ru_CR_5_1->SetLineColor(1);
  gr_ru_CR_5_1_sys->SetMarkerStyle(8);    gr_ru_CR_5_1_sys->SetMarkerSize(1.5);    gr_ru_CR_5_1_sys->SetMarkerColor(1);    gr_ru_CR_5_1_sys->SetLineWidth(4); gr_ru_CR_5_1_sys->SetLineColorAlpha(kGray+3, 0.5); gr_ru_CR_5_1_sys->SetFillStyle(3000);
  
  myfile_in.open("./output/files/third/zr_cr51_4.txt");
  for(int i=0; i<nzr; i++)
    { 
      myfile_in>>xzr[i]>>yzrc4[i]>>eyzrc4[i]>>syzrc4[i];
      xzr[i] *= iso_scale; 
      
      
    }
  myfile_in.close();
  TGraphErrors *gr_zr_CR_5_1 = new TGraphErrors(nzr, xzr, yzrc4, 0, eyzrc4); 
  gr_zr_CR_5_1->SetName("gr_zr_CR_5_1");
  TGraphErrors *gr_zr_CR_5_1_sys = new TGraphErrors(nzr, xzr, yzrc4, 0, syzrc4); 
  gr_zr_CR_5_1->SetMarkerStyle(4);    gr_zr_CR_5_1->SetMarkerSize(1.5);    gr_zr_CR_5_1->SetMarkerColor(1);    gr_zr_CR_5_1->SetLineWidth(1);    gr_zr_CR_5_1->SetLineColor(1);
  gr_zr_CR_5_1_sys->SetMarkerStyle(4);    gr_zr_CR_5_1_sys->SetMarkerSize(1.5);    gr_zr_CR_5_1_sys->SetMarkerColor(1);    gr_zr_CR_5_1_sys->SetLineWidth(4); gr_zr_CR_5_1_sys->SetLineColorAlpha(kGray+3, 0.5); gr_zr_CR_5_1_sys->SetFillStyle(3000);

  

  gr_pp_CR_5_1->GetXaxis()->SetLimits(3, 1e3);
  
  gr_pp_CR_5_1->GetYaxis()->SetRangeUser(-5.5, 2.4);
  gr_pp_CR_5_1->GetXaxis()->SetLimits(2.5, 2000);
  gr_pp_CR_5_1->SetTitle("C_{5}/C_{1}");
  gr_pp_CR_5_1->GetYaxis()->CenterTitle();
  gr_pp_CR_5_1->GetXaxis()->CenterTitle();
  gr_pp_CR_5_1->GetYaxis()->SetTitleOffset(.8);
  gr_pp_CR_5_1->GetXaxis()->SetTitleOffset(.9);
  gr_pp_CR_5_1->GetYaxis()->SetTitleSize(0.06);
  gr_pp_CR_5_1->GetXaxis()->SetTitleSize(0.055);
  
  
  gr_pp_CR_5_1->GetXaxis()->SetTitle("<Charged Particle Multiplicity>");
  gr_pp_CR_5_1->GetXaxis()->SetNoExponent();
  gr_pp_CR_5_1->GetXaxis()->SetLabelSize(0.05);
  gr_pp_CR_5_1->GetYaxis()->SetLabelSize(0.05);
  gr_pp_CR_5_1->Draw("AP");
  gr_pp_CR_5_1_sys->Draw("2 SAME");
  
  gr_auau_CR_5_1->Draw("P SAME");
  gr_ru_CR_5_1->Draw("P SAME");
  gr_ru_CR_5_1_sys->Draw("2 SAME");
  gr_zr_CR_5_1->Draw("P SAME");
  gr_zr_CR_5_1_sys->Draw("2 SAME");


  TPaveText *SP_bottomleft = new TPaveText(.18,.15,.58,.25, "NDC NB");
  SP_bottomleft->SetTextColor(2); SP_bottomleft->AddText("STAR Preliminary"); SP_bottomleft->SetFillColorAlpha(0, 0);
  

  TLine *l_CR_5_1_CBWC_ref3_HRG = new TLine(gr_pp_CR_5_1->GetXaxis()->GetXmin(), 0.997, gr_pp_CR_5_1->GetXaxis()->GetXmax(), 0.997);
  l_CR_5_1_CBWC_ref3_HRG->SetLineStyle(9);
  l_CR_5_1_CBWC_ref3_HRG->SetLineWidth(1);
  l_CR_5_1_CBWC_ref3_HRG->Draw("SAME");

  TBox *box_CR_5_1_lQCD = new TBox(700, -0.7, 1800, -0.15);
  box_CR_5_1_lQCD->SetFillColorAlpha(kRed+2, 1.0); box_CR_5_1_lQCD->SetLineColorAlpha(kRed+2, 1.0); box_CR_5_1_lQCD->Draw("SAME");

  TBox *box_cr51_frg = new TBox(700, -0.32834068 , 1800, -0.17837307); 
  box_cr51_frg->SetFillColorAlpha(kGreen+3, 0.8); box_cr51_frg->SetLineColorAlpha(kGreen+3, 1.0);

  TBox *box_CR_5_1 = new TBox(gr_pp_CR_5_1->GetXaxis()->GetXmin(), -5.5, gr_pp_CR_5_1->GetXaxis()->GetXmax(),0);
  box_CR_5_1->SetFillColorAlpha(kCyan-10, 0.25);
  box_CR_5_1->Draw("SAME");

  myfile_in.open("input/pp_Jan2023_Ratio_C6C2.txt");
  double yc6[n], eyc6[n], syc6[n];
  for(int i=0; i<n; i++){
    myfile_in>>xx[i]>>yc6[i]>>eyc6[i]>>syc6[i];
    xx[i] *= pp_scale; 
  }
  myfile_in.close();
  TGraphErrors *gr_pp_CR_6_2 = new TGraphErrors(n, xx, yc6, 0, eyc6);
  TGraphErrors *gr_pp_CR_6_2_sys = new TGraphErrors(n, xx, yc6, 0, syc6);
  gr_pp_CR_6_2->SetMarkerStyle(34);    gr_pp_CR_6_2->SetMarkerSize(1.15);    gr_pp_CR_6_2->SetMarkerColor(kAzure-3);    gr_pp_CR_6_2->SetLineWidth(2);    gr_pp_CR_6_2->SetLineColor(12);
  gr_pp_CR_6_2_sys->SetMarkerStyle(28);    gr_pp_CR_6_2_sys->SetMarkerSize(1.15);    gr_pp_CR_6_2_sys->SetMarkerColor(kAzure-3);    gr_pp_CR_6_2_sys->SetLineWidth(1);    gr_pp_CR_6_2_sys->SetLineColorAlpha(kAzure-3, 0.25); gr_pp_CR_6_2_sys->SetLineWidth(2); gr_pp_CR_6_2_sys->SetFillStyle(3000);

  
  TGraphErrors *gr_pp_CR_6_2_CBWC, *gr_pp_CR_6_2_sys_CBWC;
  const Double_t mxc6[1]={6.92655*pp_scale}, myc6[1]={0.465303},  myc6e[1]={0.00468346},  myc6s[1]={0.0388945};
  gr_pp_CR_6_2_CBWC = new TGraphErrors(1, mxc6, myc6, 0, myc6e); 
  gr_pp_CR_6_2_CBWC->SetMarkerStyle(34);    gr_pp_CR_6_2_CBWC->SetMarkerSize(1.7);    gr_pp_CR_6_2_CBWC->SetMarkerColor(kCyan+3);    gr_pp_CR_6_2_CBWC->SetLineWidth(1);    gr_pp_CR_6_2_CBWC->SetLineColor(12);
  gr_pp_CR_6_2_sys_CBWC = new TGraphErrors(1, mxc6, myc6, 0, myc6s); 
  gr_pp_CR_6_2_sys_CBWC->SetMarkerStyle(34);    gr_pp_CR_6_2_sys_CBWC->SetMarkerSize(1.96);    gr_pp_CR_6_2_sys_CBWC->SetMarkerColor(12);    gr_pp_CR_6_2_sys_CBWC->SetLineWidth(1);    gr_pp_CR_6_2_sys_CBWC->SetFillColorAlpha(kAzure-3, 0.5);
 
  
  myfile_in.open("input/pp_cr62_Feb2022.txt");
  double yc6_feb22[n], eyc6_feb22[n], syc6_feb22[n];
  for(int i=0; i<n_pp_feb22; i++){
    myfile_in>>xx_feb22[i]>>yc6_feb22[i]>>eyc6_feb22[i]>>syc6_feb22[i];
  }
  myfile_in.close();
  TGraphErrors *gr_pp_CR_6_2_feb22 = new TGraphErrors(n_pp_feb22, xx_feb22, yc6_feb22, 0, eyc6_feb22);
  TGraphErrors *gr_pp_CR_6_2_sys_feb22 = new TGraphErrors(n_pp_feb22, xx_feb22, yc6_feb22, 0, syc6_feb22);
  gr_pp_CR_6_2_feb22->SetMarkerStyle(8);    gr_pp_CR_6_2_feb22->SetMarkerSize(1.15);    gr_pp_CR_6_2_feb22->SetMarkerColor(12);    gr_pp_CR_6_2_feb22->SetLineWidth(2);    gr_pp_CR_6_2_feb22->SetLineColor(12);
  gr_pp_CR_6_2_sys_feb22->SetMarkerStyle(4);    gr_pp_CR_6_2_sys_feb22->SetMarkerSize(1.15);    gr_pp_CR_6_2_sys_feb22->SetMarkerColor(2);    gr_pp_CR_6_2_sys_feb22->SetLineWidth(1);    gr_pp_CR_6_2_sys_feb22->SetFillColorAlpha(kAzure-3, 0.5);

  TGraphErrors *gr_pp_CR_6_2_CBWC_feb22, *gr_pp_CR_6_2_sys_CBWC_feb22;
  const Double_t mxc6_feb22[1]={7.12864};  const Double_t myc6_feb22[1]={0.458085};  const Double_t myc6e_feb22[1]={0.00631099};  const Double_t myc6s_feb22[1]={0.0559384}; 
  gr_pp_CR_6_2_CBWC_feb22 = new TGraphErrors(1, mxc6_feb22, myc6_feb22, 0, myc6e_feb22); 
  gr_pp_CR_6_2_CBWC_feb22->SetMarkerStyle(8);    gr_pp_CR_6_2_CBWC_feb22->SetMarkerSize(1.7);    gr_pp_CR_6_2_CBWC_feb22->SetMarkerColor(kCyan+3);    gr_pp_CR_6_2_CBWC_feb22->SetLineWidth(1);    gr_pp_CR_6_2_CBWC_feb22->SetLineColor(12);
  gr_pp_CR_6_2_sys_CBWC_feb22 = new TGraphErrors(1, mxc6_feb22, myc6_feb22, 0, myc6s_feb22); 
  gr_pp_CR_6_2_sys_CBWC_feb22->SetMarkerStyle(4);    gr_pp_CR_6_2_sys_CBWC_feb22->SetMarkerSize(1.95);    gr_pp_CR_6_2_sys_CBWC_feb22->SetMarkerColor(12);    gr_pp_CR_6_2_sys_CBWC_feb22->SetLineWidth(1);    gr_pp_CR_4_2_sys_CBWC_feb22->SetFillColorAlpha(kAzure-3, 0.5);
  

  
  double yac6[na], eyac6[na], syac6[na];
  
  
  myfile_in.open("auau_cr62_from_Ashish_31012023_1.txt");
  for(int i=0; i<na; i++)
    { 
      
      
      myfile_in>>xa[i]>>yac6[i]>>eyac6[i]>>syac6[i];
      cout<<xa[i]<<", "<<yac6[i]<<", "<<eyac6[i]<<", "<<syac6[i]<<endl;
      
    }
  myfile_in.close();
  TGraphErrors *gr_auau_CR_6_2 = new TGraphErrors(na, xa, yac6, 0, eyac6); 
  gr_auau_CR_6_2->SetMarkerStyle(26);    gr_auau_CR_6_2->SetMarkerSize(1.5);    gr_auau_CR_6_2->SetMarkerColor(2);    gr_auau_CR_6_2->SetLineWidth(1);    gr_auau_CR_6_2->SetLineColor(2);
  
  TGraphErrors *gr_auau_CR_6_2_sys = new TGraphErrors(na, xa, yac6, 0, syac6); 
  gr_auau_CR_6_2_sys->SetMarkerStyle(26);    gr_auau_CR_6_2_sys->SetMarkerSize(1.5);    gr_auau_CR_6_2_sys->SetMarkerColor(2);    gr_auau_CR_6_2_sys->SetLineWidth(4); gr_auau_CR_6_2_sys->SetLineColorAlpha(kRed, 0.2); gr_auau_CR_6_2_sys->SetFillStyle(3000);
  
  
  
  double yruc6[nru], eyruc6[nru], syruc6[nru];
  
  myfile_in.open("./output/files/third/ru_cr62_4.txt");
  for(int i=0; i<nru; i++)
    { 
      myfile_in>>xru[i]>>yruc6[i]>>eyruc6[i]>>syruc6[i];
      xru[i] *= iso_scale; 
      
    }
  myfile_in.close();
  TGraphErrors *gr_ru_CR_6_2 = new TGraphErrors(nru, xru, yruc6, 0, eyruc6); 
  TGraphErrors *gr_ru_CR_6_2_sys = new TGraphErrors(nru, xru, yruc6, 0, syruc6); 
  gr_ru_CR_6_2->SetMarkerStyle(8);    gr_ru_CR_6_2->SetMarkerSize(1.5);    gr_ru_CR_6_2->SetMarkerColor(1);    gr_ru_CR_6_2->SetLineWidth(1);    gr_ru_CR_6_2->SetLineColor(1);
  gr_ru_CR_6_2_sys->SetMarkerStyle(8);    gr_ru_CR_6_2_sys->SetMarkerSize(1.5);    gr_ru_CR_6_2_sys->SetMarkerColor(1);    gr_ru_CR_6_2_sys->SetLineWidth(4); gr_ru_CR_6_2_sys->SetLineColorAlpha(kGray+3, 0.5); gr_ru_CR_6_2_sys->SetFillStyle(3000);

  myfile_in.open("./output/files/third/zr_cr62_4.txt");
  for(int i=0; i<nzr; i++)
    { 
      myfile_in>>xzr[i]>>yzrc4[i]>>eyzrc4[i]>>syzrc4[i];
      xzr[i] *= iso_scale; 
      
      
    }
  myfile_in.close();
  TGraphErrors *gr_zr_CR_6_2 = new TGraphErrors(nzr, xzr, yzrc4, 0, eyzrc4); 
  TGraphErrors *gr_zr_CR_6_2_sys = new TGraphErrors(nzr, xzr, yzrc4, 0, syzrc4); 
  gr_zr_CR_6_2->SetMarkerStyle(4);    gr_zr_CR_6_2->SetMarkerSize(1.5);    gr_zr_CR_6_2->SetMarkerColor(1);    gr_zr_CR_6_2->SetLineWidth(1);    gr_zr_CR_6_2->SetLineColor(1);
  gr_zr_CR_6_2_sys->SetMarkerStyle(4);    gr_zr_CR_6_2_sys->SetMarkerSize(1.5);    gr_zr_CR_6_2_sys->SetMarkerColor(1);    gr_zr_CR_6_2_sys->SetLineWidth(4);    gr_zr_CR_6_2_sys->SetLineColorAlpha(kGray+3, 0.5); gr_zr_CR_6_2_sys->SetFillStyle(3000);

  


  gr_pp_CR_6_2->GetXaxis()->SetLimits(3, 1e3);
  if(merge_counter == 0) gr_pp_CR_6_2->GetYaxis()->SetRangeUser(-6.5, 4.5);
  else gr_pp_CR_6_2->GetYaxis()->SetRangeUser(-6.5, 2.2);
  gr_pp_CR_6_2->GetXaxis()->SetLimits(2.5, 2000);
  gr_pp_CR_6_2->SetTitle("C_{6}/C_{2}");
  gr_pp_CR_6_2->GetYaxis()->CenterTitle();
  gr_pp_CR_6_2->GetXaxis()->CenterTitle();
  gr_pp_CR_6_2->GetYaxis()->SetTitleOffset(.8);
  gr_pp_CR_6_2->GetXaxis()->SetTitleOffset(.9);
  gr_pp_CR_6_2->GetYaxis()->SetTitleSize(0.06);
  gr_pp_CR_6_2->GetXaxis()->SetTitleSize(0.055);
  
  
  gr_pp_CR_6_2->GetXaxis()->SetTitle("<Charged Particle Multiplicity>");
  gr_pp_CR_6_2->GetXaxis()->SetNoExponent();
  gr_pp_CR_6_2->GetXaxis()->SetLabelSize(0.05);
  gr_pp_CR_6_2->GetYaxis()->SetLabelSize(0.05);
  gr_pp_CR_6_2->Draw("AP");
  gr_pp_CR_6_2_sys->Draw("P SAME");
  
  gr_auau_CR_6_2->Draw("P SAME");
  gr_ru_CR_6_2->Draw("P SAME");
  gr_ru_CR_6_2_sys->Draw("2 SAME");
  gr_zr_CR_6_2->Draw("P SAME");
  gr_zr_CR_6_2_sys->Draw("2 SAME");

  TLine *l_CR_6_2_CBWC_ref3_HRG = new TLine(gr_pp_CR_6_2->GetXaxis()->GetXmin(), 0.997, gr_pp_CR_6_2->GetXaxis()->GetXmax(), 0.997);
  l_CR_6_2_CBWC_ref3_HRG->SetLineStyle(9);
  l_CR_6_2_CBWC_ref3_HRG->SetLineWidth(1);
  l_CR_6_2_CBWC_ref3_HRG->Draw("SAME");
  
  TBox *box_CR_6_2_lQCD = new TBox(700, -0.875, 1800, -0.25);
  box_CR_6_2_lQCD->SetFillColorAlpha(kRed+2, 1.0); box_CR_6_2_lQCD->SetLineColorAlpha(kRed+2, 1.0); box_CR_6_2_lQCD->Draw("SAME");

  TBox *box_cr62_frg = new TBox(700, -0.33768557, 1800, -0.18311826); 
  box_cr62_frg->SetFillColorAlpha(kGreen+3, 0.8); box_cr62_frg->SetLineColorAlpha(kGreen+3, 1.0);

  TBox *box_CR_6_2 = new TBox(gr_pp_CR_6_2->GetXaxis()->GetXmin(), -6.5, gr_pp_CR_6_2->GetXaxis()->GetXmax(),0);
  box_CR_6_2->SetFillColorAlpha(kCyan-10, 0.25);
  box_CR_6_2->Draw("SAME");
  int nurqmd=9-merge_counter;
  double xurqmd[nurqmd], yurqmdc4[nurqmd], eyurqmdc4[nurqmd], syurqmdc4[nurqmd];
  myfile_in.open(Form("/Users/hosanko/playground/star/anal/Coll/isobar/ZrZrRuRu200_2018/charge/paper_plots/QM2022/output/Risa_cr42_Zr_ref3_urqmd_%d_03032022_1.txt", merge_counter));
  for(int i=0; i<nurqmd - merge_counter; i++)
    { 
      myfile_in>>xurqmd[i]>>yurqmdc4[i]>>eyurqmdc4[i]>>syurqmdc4[i];
      cout<<xurqmd[i]<<" "<<yurqmdc4[i]<<" "<<eyurqmdc4[i]<<" "<<syurqmdc4[i]<<endl;
      
    }
  myfile_in.close();
  TGraphErrors *gr_zr_urqmd_CR_4_2 = new TGraphErrors(nurqmd-merge_counter, xurqmd, yurqmdc4, 0, eyurqmdc4); 
  gr_zr_urqmd_CR_4_2->SetMarkerStyle(25); gr_zr_urqmd_CR_4_2->SetMarkerColorAlpha(kCyan+2, 1); gr_zr_urqmd_CR_4_2->SetMarkerSize(1.5); gr_zr_urqmd_CR_4_2->SetFillStyle(3005); gr_zr_urqmd_CR_4_2->SetFillColorAlpha(kCyan+2, 1); gr_zr_urqmd_CR_4_2->SetLineColor(kCyan+2);

  myfile_in.open(Form("/Users/hosanko/playground/star/anal/Coll/isobar/ZrZrRuRu200_2018/charge/paper_plots/QM2022/output/Risa_cr42_Ru_ref3_urqmd_%d_03032022_1.txt", merge_counter));
  for(int i=0; i<nurqmd - merge_counter; i++)
    { 
      myfile_in>>xurqmd[i]>>yurqmdc4[i]>>eyurqmdc4[i]>>syurqmdc4[i];
      cout<<xurqmd[i]<<" "<<yurqmdc4[i]<<" "<<eyurqmdc4[i]<<" "<<syurqmdc4[i]<<endl;
      
    }
  myfile_in.close();
  TGraphErrors *gr_ru_urqmd_CR_4_2 = new TGraphErrors(nurqmd-merge_counter, xurqmd, yurqmdc4, 0, eyurqmdc4); 
  gr_ru_urqmd_CR_4_2->SetMarkerStyle(21); gr_ru_urqmd_CR_4_2->SetMarkerColorAlpha(kMagenta+2, 1); gr_ru_urqmd_CR_4_2->SetMarkerSize(1.5); gr_ru_urqmd_CR_4_2->SetFillStyle(3004); gr_ru_urqmd_CR_4_2->SetFillColorAlpha(kMagenta+2, 1); gr_ru_urqmd_CR_4_2->SetLineColor(kMagenta+2);
  
  
  myfile_in.open(Form("/Users/hosanko/playground/star/anal/Coll/isobar/ZrZrRuRu200_2018/charge/paper_plots/QM2022/output/Risa_cr51_Zr_ref3_urqmd_%d_03032022_1.txt", merge_counter));
  for(int i=0; i<nurqmd - merge_counter; i++)
    { 
      myfile_in>>xurqmd[i]>>yurqmdc4[i]>>eyurqmdc4[i]>>syurqmdc4[i];
      cout<<xurqmd[i]<<" "<<yurqmdc4[i]<<" "<<eyurqmdc4[i]<<" "<<syurqmdc4[i]<<endl;
      
    }
  myfile_in.close();
  TGraphErrors *gr_zr_urqmd_CR_5_1 = new TGraphErrors(nurqmd-merge_counter, xurqmd, yurqmdc4, 0, eyurqmdc4); 
  gr_zr_urqmd_CR_5_1->SetMarkerStyle(25); gr_zr_urqmd_CR_5_1->SetMarkerColorAlpha(kCyan+2, 1); gr_zr_urqmd_CR_5_1->SetMarkerSize(1.5); gr_zr_urqmd_CR_5_1->SetFillStyle(3005); gr_zr_urqmd_CR_5_1->SetFillColorAlpha(kCyan+2, 1); gr_zr_urqmd_CR_5_1->SetLineColor(kCyan+2);
  
  myfile_in.open(Form("/Users/hosanko/playground/star/anal/Coll/isobar/ZrZrRuRu200_2018/charge/paper_plots/QM2022/output/Risa_cr51_Ru_ref3_urqmd_%d_03032022_1.txt", merge_counter));
  for(int i=0; i<nurqmd - merge_counter; i++)
    { 
      myfile_in>>xurqmd[i]>>yurqmdc4[i]>>eyurqmdc4[i]>>syurqmdc4[i];
      cout<<xurqmd[i]<<" "<<yurqmdc4[i]<<" "<<eyurqmdc4[i]<<" "<<syurqmdc4[i]<<endl;
      
    }
  myfile_in.close();
  TGraphErrors *gr_ru_urqmd_CR_5_1 = new TGraphErrors(nurqmd-merge_counter, xurqmd, yurqmdc4, 0, eyurqmdc4); 
  gr_ru_urqmd_CR_5_1->SetMarkerStyle(25); gr_ru_urqmd_CR_5_1->SetMarkerColorAlpha(kMagenta+2, 1); gr_ru_urqmd_CR_5_1->SetMarkerSize(1.5); gr_ru_urqmd_CR_5_1->SetFillStyle(3004); gr_ru_urqmd_CR_5_1->SetFillColorAlpha(kMagenta+2, 1); gr_ru_urqmd_CR_5_1->SetLineColor(kMagenta+2);
  
  
  myfile_in.open(Form("/Users/hosanko/playground/star/anal/Coll/isobar/ZrZrRuRu200_2018/charge/paper_plots/QM2022/output/Risa_cr62_Zr_ref3_urqmd_%d_03032022_1.txt", merge_counter));
  for(int i=0; i<nurqmd - merge_counter; i++)
    { 
      myfile_in>>xurqmd[i]>>yurqmdc4[i]>>eyurqmdc4[i]>>syurqmdc4[i];
      cout<<xurqmd[i]<<" "<<yurqmdc4[i]<<" "<<eyurqmdc4[i]<<" "<<syurqmdc4[i]<<endl;
      
    }
  myfile_in.close();
  TGraphErrors *gr_zr_urqmd_CR_6_2 = new TGraphErrors(nurqmd-merge_counter, xurqmd, yurqmdc4, 0, eyurqmdc4); 
  gr_zr_urqmd_CR_6_2->SetMarkerStyle(25); gr_zr_urqmd_CR_6_2->SetMarkerColorAlpha(kCyan+2, 1); gr_zr_urqmd_CR_6_2->SetMarkerSize(1.5); gr_zr_urqmd_CR_6_2->SetFillStyle(3005); gr_zr_urqmd_CR_6_2->SetFillColorAlpha(kCyan+2, 1); gr_zr_urqmd_CR_6_2->SetLineColor(kCyan+2);

  myfile_in.open(Form("/Users/hosanko/playground/star/anal/Coll/isobar/ZrZrRuRu200_2018/charge/paper_plots/QM2022/output/Risa_cr62_Ru_ref3_urqmd_%d_03032022_1.txt", merge_counter));
  for(int i=0; i<nurqmd - merge_counter; i++)
    { 
      myfile_in>>xurqmd[i]>>yurqmdc4[i]>>eyurqmdc4[i]>>syurqmdc4[i];
      cout<<xurqmd[i]<<" "<<yurqmdc4[i]<<" "<<eyurqmdc4[i]<<" "<<syurqmdc4[i]<<endl;
      
    }
  myfile_in.close();
  TGraphErrors *gr_ru_urqmd_CR_6_2 = new TGraphErrors(nurqmd-merge_counter, xurqmd, yurqmdc4, 0, eyurqmdc4); 
  gr_ru_urqmd_CR_6_2->SetMarkerStyle(21); gr_ru_urqmd_CR_6_2->SetMarkerColorAlpha(kMagenta+2, 1); gr_ru_urqmd_CR_6_2->SetMarkerSize(1.5); gr_ru_urqmd_CR_6_2->SetFillStyle(3004); gr_ru_urqmd_CR_6_2->SetFillColorAlpha(kMagenta+2, 1); gr_ru_urqmd_CR_6_2->SetLineColor(kMagenta+2);

  gr_pp_CR_4_2->Draw("AP");
  gr_pp_CR_4_2_sys->Draw("P SAME");
  
  gr_pp_CR_4_2_sys_CBWC->Draw("psame"); gr_pp_CR_4_2_CBWC->Draw("psame");
  gr_auau_CR_4_2->Draw("P SAME");
  gr_auau_CR_4_2_sys->Draw("2 SAME");
  gr_ru_CR_4_2->Draw("P SAME");
  gr_ru_CR_4_2_sys->Draw("2 SAME");
  l_CR_4_2_CBWC_ref3_HRG->Draw("SAME");
  
  
  
  
  gr_zr_CR_4_2->Draw("P SAME");
  gr_zr_CR_4_2_sys->Draw("2 SAME");
  box_CR_4_2_lQCD->Draw("SAME");

  gr_zr_urqmd_CR_4_2->GetYaxis()->SetTitleOffset(1.5);
  gr_zr_urqmd_CR_4_2->GetXaxis()->SetLimits(3, 1e3);
  gr_zr_urqmd_CR_4_2->GetYaxis()->SetRangeUser(0.05, 1.12);
  gr_zr_urqmd_CR_4_2->GetXaxis()->SetLimits(2.5, 2000);
  gr_zr_urqmd_CR_4_2->SetTitle("C_{4}/C_{2}");
  gr_zr_urqmd_CR_4_2->GetYaxis()->CenterTitle();
  gr_zr_urqmd_CR_4_2->GetXaxis()->CenterTitle();
  gr_zr_urqmd_CR_4_2->GetYaxis()->SetTitleOffset(.8);
  gr_zr_urqmd_CR_4_2->GetXaxis()->SetTitleOffset(.9);
  gr_zr_urqmd_CR_4_2->GetYaxis()->SetTitleSize(0.06);
  gr_zr_urqmd_CR_4_2->GetXaxis()->SetTitleSize(0.055);
  gr_zr_urqmd_CR_4_2->GetXaxis()->SetTitle("<Charged Particle Multiplicity>");
  gr_zr_urqmd_CR_4_2->GetXaxis()->SetNoExponent();
  gr_zr_urqmd_CR_4_2->GetXaxis()->SetLabelSize(0.05);
  gr_zr_urqmd_CR_4_2->GetYaxis()->SetLabelSize(0.05);
  
  Info1_topleft->Draw("SAME");
  
  leg_CR_4_2->Draw("SAME");

  ya1=0.57,   ya2=0.59;
  yru1=0.47,   yru2=0.49;
  drawLine(xa1,ya1,xa2,ya1,1,1,7);  drawLine(xa1,ya1,xa1,ya2,1,1,7);  drawLine(xa2,ya1,xa2,ya2,1,1,7);
  drawLine(xa2,ya1,xa3,ya1,1,1,7);  drawLine(xa3,ya1,xa3,ya2,1,1,7); 
  drawLine(xa4,ya1,xa3,ya1,1,1,7);  drawLine(xa4,ya1,xa4,ya2,1,1,7); 
  drawLine(xa4,ya1,xa5,ya1,1,1,7);  drawLine(xa5,ya1,xa5,ya2,1,1,7); 
  drawLine(xa6,ya1,xa5,ya1,1,1,7);  drawLine(xa6,ya1,xa6,ya2,1,1,7);

  drawLine(xru1,yru1,xru2,yru1,1,1,9);  drawLine(xru1,yru1,xru1,yru2,1,1,9);  drawLine(xru2,yru1,xru2,yru2,1,1,9);
  drawLine(xru2,yru1,xru3,yru1,1,1,9);  drawLine(xru3,yru1,xru3,yru2,1,1,9);
  drawLine(xru4,yru1,xru3,yru1,1,1,9);  drawLine(xru4,yru1,xru4,yru2,1,1,9);
  drawLine(xru4,yru1,xru5,yru1,1,1,9);  drawLine(xru5,yru1,xru5,yru2,1,1,9);
  drawLine(xru5,yru1,xru6,yru1,1,1,9);  
  
  
  
  drawLine(xru6,yru1,xru7,yru1,1,1,9);
  drawLine(xru7,yru1,xru8,yru1,1,1,9);
  drawLine(xru8,yru1,xru9,yru1,1,1,9);
  drawLine(xru9,yru1,xru10,yru1,1,1,9);  drawLine(xru10,yru1,xru10,yru2,1,1,9);

  x21 = 6.894-3.993, x22 = 6.894+3.993, y01 = 0.986;
  drawLine(x21,y01,x22,y01,5,1,41); 
  

  latex->SetTextSize(0.04);     latex->SetTextFont(42);  latex->SetTextColor(kCyan+2);   latex->SetTextAngle(0);
  latex->DrawLatex(25-13,ya1,"Au+Au: ");
  latex->SetTextSize(0.04);     latex->SetTextFont(42);  latex->SetTextColor(9);   latex->SetTextAngle(0);
  latex->DrawLatex(25-13, yru1,"Zr#oplusRu: ");
  
  SP_topleft->Draw("SAME");
  
  gr_pp_CR_5_1->Draw("AP");
  gr_pp_CR_5_1_sys->Draw("2 SAME");
  
  
  gr_pp_CR_5_1_sys_CBWC->Draw("psame"); gr_pp_CR_5_1_CBWC->Draw("psame");
  gr_auau_CR_5_1->Draw("P SAME");
  gr_auau_CR_5_1_sys->Draw("2 SAME");
  gr_ru_CR_5_1->Draw("P SAME");
  gr_ru_CR_5_1_sys->Draw("2 SAME");
  gr_zr_CR_5_1->Draw("P SAME");
  gr_zr_CR_5_1_sys->Draw("2 SAME");
  

  gr_zr_urqmd_CR_5_1->GetYaxis()->SetTitleOffset(1.5);
  gr_zr_urqmd_CR_5_1->GetXaxis()->SetLimits(3, 1e3);
  gr_zr_urqmd_CR_5_1->GetYaxis()->SetRangeUser(-5.5, 2.4);
  gr_zr_urqmd_CR_5_1->GetXaxis()->SetLimits(2.5, 2000);
  gr_zr_urqmd_CR_5_1->SetTitle("C_{5}/C_{1}");
  gr_zr_urqmd_CR_5_1->GetYaxis()->CenterTitle();
  gr_zr_urqmd_CR_5_1->GetXaxis()->CenterTitle();
  gr_zr_urqmd_CR_5_1->GetYaxis()->SetTitleOffset(.8);
  gr_zr_urqmd_CR_5_1->GetXaxis()->SetTitleOffset(.9);
  gr_zr_urqmd_CR_5_1->GetYaxis()->SetTitleSize(0.06);
  gr_zr_urqmd_CR_5_1->GetXaxis()->SetTitleSize(0.055);
  gr_zr_urqmd_CR_5_1->GetXaxis()->SetTitle("<Charged Particle Multiplicity>");
  gr_zr_urqmd_CR_5_1->GetXaxis()->SetNoExponent();
  gr_zr_urqmd_CR_5_1->GetXaxis()->SetLabelSize(0.05);
  gr_zr_urqmd_CR_5_1->GetYaxis()->SetLabelSize(0.05);
  
  
  l_CR_5_1_CBWC_ref3_HRG->Draw("SAME");
  
  
  
  
  box_CR_5_1_lQCD->Draw("SAME");
  box_CR_5_1->Draw("SAME");
  

  ya1=-1.2,   ya2=-1.1;
  yru1=-1.5,   yru2=-1.4;
  drawLine(xa1,ya1,xa2,ya1,1,1,7);  drawLine(xa1,ya1,xa1,ya2,1,1,7);  drawLine(xa2,ya1,xa2,ya2,1,1,7);
  drawLine(xa2,ya1,xa3,ya1,1,1,7);  drawLine(xa3,ya1,xa3,ya2,1,1,7); 
  drawLine(xa4,ya1,xa3,ya1,1,1,7);  drawLine(xa4,ya1,xa4,ya2,1,1,7); 
  drawLine(xa4,ya1,xa5,ya1,1,1,7);  drawLine(xa5,ya1,xa5,ya2,1,1,7); 
  drawLine(xa6,ya1,xa5,ya1,1,1,7);  drawLine(xa6,ya1,xa6,ya2,1,1,7);

  drawLine(xru1,yru1,xru2,yru1,1,1,9);  drawLine(xru1,yru1,xru1,yru2,1,1,9);  drawLine(xru2,yru1,xru2,yru2,1,1,9);
  drawLine(xru2,yru1,xru3,yru1,1,1,9);  drawLine(xru3,yru1,xru3,yru2,1,1,9);
  drawLine(xru4,yru1,xru3,yru1,1,1,9);  drawLine(xru4,yru1,xru4,yru2,1,1,9);
  drawLine(xru4,yru1,xru5,yru1,1,1,9);  drawLine(xru5,yru1,xru5,yru2,1,1,9);
  drawLine(xru5,yru1,xru6,yru1,1,1,9); 
  
  
  
  drawLine(xru6,yru1,xru7,yru1,1,1,9);
  drawLine(xru7,yru1,xru8,yru1,1,1,9);
  drawLine(xru8,yru1,xru9,yru1,1,1,9);
  drawLine(xru9,yru1,xru10,yru1,1,1,9);  drawLine(xru10,yru1,xru10,yru2,1,1,9);

  x21 = 6.894-3.993, x22 = 6.894+3.993, y01 = 0.934;
  drawLine(x21,y01,x22,y01,5,1,41); 


  latex->SetTextSize(0.04);     latex->SetTextFont(42);  latex->SetTextColor(kCyan+2);   latex->SetTextAngle(0);
  latex->DrawLatex(25-13,ya1,"Au+Au: ");
  latex->SetTextSize(0.04);     latex->SetTextFont(42);  latex->SetTextColor(9);   latex->SetTextAngle(0);
  latex->DrawLatex(25-13-2, yru1,"Zr#oplusRu: ");
  
  TLegend *leg_CR_5_1 = new TLegend(0.13, 0.22, 0.46, 0.45);
  
  
  
  leg_CR_5_1->AddEntry(line_pythia, "Pythia (8.2)", "f");
  leg_CR_5_1->AddEntry(box_CR_5_1_lQCD, "LGT", "f");
  leg_CR_5_1->AddEntry(box_cr51_frg, "FRG", "f");
  leg_CR_5_1->SetFillColorAlpha(kCyan-10, 0.);
  leg_CR_5_1->SetLineColorAlpha(0, 0);
  leg_CR_5_1->Draw("SAME");

  SP_topright->Draw("SAME");
  

  gr_pp_CR_6_2->Draw("AP");
  gr_pp_CR_6_2_sys->Draw("P SAME");
  
  gr_pp_CR_6_2_sys_CBWC->Draw("psame"); gr_pp_CR_6_2_CBWC->Draw("psame");
  gr_auau_CR_6_2->Draw("P SAME");
  gr_auau_CR_6_2_sys->Draw("2 SAME");
  gr_ru_CR_6_2->Draw("P SAME");
  gr_ru_CR_6_2_sys->Draw("2 SAME");
  gr_zr_CR_6_2->Draw("P SAME");
  gr_zr_CR_6_2_sys->Draw("2 SAME");
  

  gr_zr_urqmd_CR_6_2->GetYaxis()->SetTitleOffset(1.5);
  gr_zr_urqmd_CR_6_2->GetXaxis()->SetLimits(3, 1e3);
  gr_zr_urqmd_CR_6_2->GetYaxis()->SetRangeUser(-6.5, 2);
  gr_zr_urqmd_CR_6_2->GetXaxis()->SetLimits(2.5, 2000);
  gr_zr_urqmd_CR_6_2->SetTitle("C_{5}/C_{1}");
  gr_zr_urqmd_CR_6_2->GetYaxis()->CenterTitle();
  gr_zr_urqmd_CR_6_2->GetXaxis()->CenterTitle();
  gr_zr_urqmd_CR_6_2->GetYaxis()->SetTitleOffset(.8);
  gr_zr_urqmd_CR_6_2->GetXaxis()->SetTitleOffset(.9);
  gr_zr_urqmd_CR_6_2->GetYaxis()->SetTitleSize(0.06);
  gr_zr_urqmd_CR_6_2->GetXaxis()->SetTitleSize(0.055);
  gr_zr_urqmd_CR_6_2->GetXaxis()->SetTitle("<Charged Particle Multiplicity>");
  gr_zr_urqmd_CR_6_2->GetXaxis()->SetNoExponent();
  gr_zr_urqmd_CR_6_2->GetXaxis()->SetLabelSize(0.05);
  gr_zr_urqmd_CR_6_2->GetYaxis()->SetLabelSize(0.05);

  l_CR_6_2_CBWC_ref3_HRG->Draw("SAME");
  
  box_CR_6_2_lQCD->Draw("SAME");
  box_CR_6_2->Draw("SAME");
  SP_bottomleft->Draw("SAME");

  TLegend *leg_CR_6_2_urqmd = new TLegend(0.2, 0.25, 0.6, 0.45);
  leg_CR_6_2_urqmd->AddEntry(gr_zr_urqmd_CR_6_2, "UrQMD: Zr+Zr", "f");
  leg_CR_6_2_urqmd->AddEntry(gr_ru_urqmd_CR_6_2, "UrQMD: Ru+Ru", "f");
  leg_CR_6_2_urqmd->SetFillColorAlpha(kCyan-10, 0.);
  leg_CR_6_2_urqmd->SetLineColorAlpha(0, 0);
  


  ya1=-1.0,   ya2=-0.9;
  yru1=-2,   yru2=-1.9;
  drawLine(xa1,ya1,xa2,ya1,1,1,7);  drawLine(xa1,ya1,xa1,ya2,1,1,7);  drawLine(xa2,ya1,xa2,ya2,1,1,7);
  drawLine(xa2,ya1,xa3,ya1,1,1,7);  drawLine(xa3,ya1,xa3,ya2,1,1,7); 
  drawLine(xa4,ya1,xa3,ya1,1,1,7);  drawLine(xa4,ya1,xa4,ya2,1,1,7); 
  drawLine(xa4,ya1,xa5,ya1,1,1,7);  drawLine(xa5,ya1,xa5,ya2,1,1,7); 
  drawLine(xa6,ya1,xa5,ya1,1,1,7);  drawLine(xa6,ya1,xa6,ya2,1,1,7);

  drawLine(xru1,yru1,xru2,yru1,1,1,9);  drawLine(xru1,yru1,xru1,yru2,1,1,9);  drawLine(xru2,yru1,xru2,yru2,1,1,9);
  drawLine(xru2,yru1,xru3,yru1,1,1,9);  drawLine(xru3,yru1,xru3,yru2,1,1,9);
  drawLine(xru4,yru1,xru3,yru1,1,1,9);  drawLine(xru4,yru1,xru4,yru2,1,1,9);
  drawLine(xru4,yru1,xru5,yru1,1,1,9);  drawLine(xru5,yru1,xru5,yru2,1,1,9);
  drawLine(xru5,yru1,xru6,yru1,1,1,9);  
  
  
  
  drawLine(xru6,yru1,xru7,yru1,1,1,9);
  drawLine(xru7,yru1,xru8,yru1,1,1,9);
  drawLine(xru8,yru1,xru9,yru1,1,1,9);
  drawLine(xru9,yru1,xru10,yru1,1,1,9);  drawLine(xru10,yru1,xru10,yru2,1,1,9);

  x21 = 6.894-3.993, x22 = 6.894+3.993, y01 = 0.798;
  drawLine(x21,y01,x22,y01,5,1,41); 

  latex->SetTextColor(1);
  latex->SetTextAlign(30);   latex->SetTextFont(82);   latex->SetTextSize(0.035);   latex->SetTextAngle(25);
  latex->DrawLatex(25,ya1-0.2,"70-80%");
  latex->DrawLatex(50,ya1-0.2,"60-70%");
  latex->DrawLatex(90,ya1-0.2,"50-60%");
  latex->DrawLatex(180,ya1-0.2,"40-50%");
  latex->DrawLatex(650,ya1-0.2,"0-40%");

  latex->SetTextAlign(30);   latex->SetTextFont(82);   latex->SetTextSize(0.03);   latex->SetTextAngle(25);
  latex->DrawLatex(0.5*(13+25),yru1-0.2,"70-80%");
  latex->DrawLatex(0.5*(25+43),yru1-0.2,"60-70%");
  latex->DrawLatex(0.5*(43+72),yru1-0.2,"50-60%");
  latex->DrawLatex(0.5*(72+114),yru1-0.2,"40-50%");
  latex->DrawLatex(0.5*(114+700),yru1-0.2,"0-40%");
  
  
  

  latex->SetTextSize(0.04);     latex->SetTextFont(42);  latex->SetTextColor(kCyan+2);   latex->SetTextAngle(0);
  latex->DrawLatex(25-13,ya1,"Au+Au: ");
  latex->SetTextSize(0.04);     latex->SetTextFont(42);  latex->SetTextColor(9);   latex->SetTextAngle(0);
  latex->DrawLatex(25-13-2, yru1,"Zr#oplusRu: ");

  TPad *p_cr42 = new TPad("p_cr42", "p_cr42", 0.00+0.*1.0/3., 0.0, 0.00+1.*1.0/3.-(-1.0)*0.001, 0.99);                    p_cr42->SetLeftMargin(0.09); p_cr42->SetRightMargin(0.009); p_cr42->SetTopMargin(0.); p_cr42->SetBottomMargin(0.105);
  TPad *p_cr51 = new TPad("p_cr51", "p_cr51", 0.00+1.*1.0/3.+(-1.0)*0.001/2., 0.0, 0.00+2.*1.0/3.-(-1.0)*0.001/2., 0.99); p_cr51->SetLeftMargin(0.09); p_cr51->SetRightMargin(0.009); p_cr51->SetTopMargin(0.); p_cr51->SetBottomMargin(0.105);
  TPad *p_cr62 = new TPad("p_cr62", "p_cr62", 0.00+2.*1.0/3.+(-1.0)*0.001, 0.0, 0.00+3.*1.0/3., 0.99);                    p_cr62->SetLeftMargin(0.09); p_cr62->SetRightMargin(0.009); p_cr62->SetTopMargin(0.); p_cr62->SetBottomMargin(0.105);
  TPaveText *t_cr42 = new TPaveText(.13-0.17,.87,.64-0.17,.94, "NDC"); t_cr42->AddText("C_{4}/C_{2}"); t_cr42->SetFillColorAlpha(0, 0);
  TPaveText *t_cr51 = new TPaveText(.13-0.17,.87,.64-0.17,.94, "NDC"); t_cr51->AddText("C_{5}/C_{1}"); t_cr51->SetFillColorAlpha(0, 0);
  TPaveText *t_cr62 = new TPaveText(.13-0.17,.87,.64-0.17,.94, "NDC"); t_cr62->AddText("C_{6}/C_{2}"); t_cr62->SetFillColorAlpha(0, 0);
  gr_pp_CR_4_2->GetXaxis()->SetLabelSize(0.06);
  gr_pp_CR_5_1->GetXaxis()->SetLabelSize(0.06);
  gr_pp_CR_6_2->GetXaxis()->SetLabelSize(0.06);
  gr_pp_CR_4_2->GetYaxis()->SetLabelSize(0.06);
  gr_pp_CR_5_1->GetYaxis()->SetLabelSize(0.06);
  gr_pp_CR_6_2->GetYaxis()->SetLabelSize(0.06);
  gr_pp_CR_4_2->GetXaxis()->SetTitle("");
  gr_pp_CR_5_1->GetXaxis()->SetTitle("");
  gr_pp_CR_6_2->GetXaxis()->SetTitle("");
  gr_pp_CR_4_2->GetYaxis()->SetTitleOffset(.95);
  
  gr_pp_CR_4_2->GetYaxis()->SetLabelOffset(0.0125);
  gr_pp_CR_5_1->GetYaxis()->SetLabelOffset(0.0125);
  gr_pp_CR_6_2->GetYaxis()->SetLabelOffset(0.0125);
  gr_pp_CR_4_2->GetYaxis()->SetRangeUser(0.05, 1.299);
  gr_pp_CR_5_1->GetYaxis()->SetRangeUser(-5.5, 2.4);
  gr_pp_CR_6_2->GetYaxis()->SetRangeUser(-6.5, 3.35);
  gr_pp_CR_4_2->GetYaxis()->SetNdivisions(010);
  gr_pp_CR_5_1->GetYaxis()->SetNdivisions(010);
  gr_pp_CR_6_2->GetYaxis()->SetNdivisions(010);

  TCanvas *c_CR_3tot_pad = new TCanvas("c_CR_3tot_pad", "c_CR_3tot_pad", 1700, 500); c_CR_3tot_pad->cd();
  p_cr42->Draw(); p_cr51->Draw(); p_cr62->Draw();
  p_cr42->cd(); p_cr42->SetLogx(1); p_cr42->SetTickx(1);  p_cr42->SetTicky(1); 
  
  gr_pp_CR_4_2->SetTitle("");
  gr_pp_CR_4_2->Draw("AXgoff");
  box_CR_4_2_lQCD->Draw("SAME");
  l_CR_4_2_CBWC_ref3_HRG->Draw("SAME");
  Info1_topleft->Draw("SAME");

  ya1=0.6,   ya2=0.62;
  yru1=0.45,   yru2=0.47;
  drawLine(xa1,ya1,xa2,ya1,1,1,7);  drawLine(xa1,ya1,xa1,ya2,1,1,7);  drawLine(xa2,ya1,xa2,ya2,1,1,7);
  drawLine(xa2,ya1,xa3,ya1,1,1,7);  drawLine(xa3,ya1,xa3,ya2,1,1,7); 
  drawLine(xa4,ya1,xa3,ya1,1,1,7);  drawLine(xa4,ya1,xa4,ya2,1,1,7); 
  drawLine(xa4,ya1,xa5,ya1,1,1,7);  drawLine(xa5,ya1,xa5,ya2,1,1,7); 
  drawLine(xa6,ya1,xa5,ya1,1,1,7);  drawLine(xa6,ya1,xa6,ya2,1,1,7);

  drawLine(xru1,yru1,xru2,yru1,1,1,9);  drawLine(xru1,yru1,xru1,yru2,1,1,9);  drawLine(xru2,yru1,xru2,yru2,1,1,9);
  drawLine(xru2,yru1,xru3,yru1,1,1,9);  drawLine(xru3,yru1,xru3,yru2,1,1,9);
  drawLine(xru4,yru1,xru3,yru1,1,1,9);  drawLine(xru4,yru1,xru4,yru2,1,1,9);
  drawLine(xru4,yru1,xru5,yru1,1,1,9);  drawLine(xru5,yru1,xru5,yru2,1,1,9);
  drawLine(xru5,yru1,xru6,yru1,1,1,9);  
  
  
  
  drawLine(xru6,yru1,xru7,yru1,1,1,9);
  drawLine(xru7,yru1,xru8,yru1,1,1,9);
  drawLine(xru8,yru1,xru9,yru1,1,1,9);
  drawLine(xru9,yru1,xru10,yru1,1,1,9);  drawLine(xru10,yru1,xru10,yru2,1,1,9);

  x21 = 6.894-3.993, x22 = 6.894+3.993, y01 = 0.986;
  
  

  t_cr42->Draw("SAME");

  ya1 = 0.575;
  latex->SetTextColor(1);
  latex->SetTextAlign(30);   latex->SetTextFont(82);   latex->SetTextSize(0.035);   latex->SetTextAngle(45);
  latex->DrawLatex(25,ya1,"70-80%");
  latex->DrawLatex(50,ya1,"60-70%");
  latex->DrawLatex(90,ya1,"50-60%");
  latex->DrawLatex(180,ya1,"40-50%");
  
  latex->DrawLatex(400,ya1-0.01,"0-40%");

  gr_pp_CR_4_2->Draw("P SAME");
  gr_pp_CR_4_2_sys->Draw("P SAME");
  
  
  gr_pp_CR_4_2_sys_CBWC->Draw("psame"); gr_pp_CR_4_2_CBWC->Draw("psame");
  
  gr_auau_CR_4_2_sys->Draw("2 SAME");
  gr_auau_CR_4_2->Draw("P SAME");
  gr_ru_CR_4_2_sys->Draw("2 SAME");
  gr_ru_CR_4_2->Draw("P SAME");
  gr_zr_CR_4_2_sys->Draw("2 SAME");
  gr_zr_CR_4_2->Draw("P SAME");

  p_cr51->cd(); p_cr51->SetLogx(1); p_cr51->SetTickx(1);  p_cr51->SetTicky(1); 
  gr_pp_CR_5_1->SetTitle("");
  gr_pp_CR_5_1->Draw("AXgoff");
  box_CR_5_1->Draw("SAME");
  box_CR_5_1_lQCD->Draw("SAME");

  ya1=-1.1,   ya2=-1.0;
  yru1=-1.4,   yru2=-1.3;
  drawLine(xa1,ya1,xa2,ya1,1,1,7);  drawLine(xa1,ya1,xa1,ya2,1,1,7);  drawLine(xa2,ya1,xa2,ya2,1,1,7);
  drawLine(xa2,ya1,xa3,ya1,1,1,7);  drawLine(xa3,ya1,xa3,ya2,1,1,7); 
  drawLine(xa4,ya1,xa3,ya1,1,1,7);  drawLine(xa4,ya1,xa4,ya2,1,1,7); 
  drawLine(xa4,ya1,xa5,ya1,1,1,7);  drawLine(xa5,ya1,xa5,ya2,1,1,7); 
  drawLine(xa6,ya1,xa5,ya1,1,1,7);  drawLine(xa6,ya1,xa6,ya2,1,1,7);

  drawLine(xru1,yru1,xru2,yru1,1,1,9);  drawLine(xru1,yru1,xru1,yru2,1,1,9);  drawLine(xru2,yru1,xru2,yru2,1,1,9);
  drawLine(xru2,yru1,xru3,yru1,1,1,9);  drawLine(xru3,yru1,xru3,yru2,1,1,9);
  drawLine(xru4,yru1,xru3,yru1,1,1,9);  drawLine(xru4,yru1,xru4,yru2,1,1,9);
  drawLine(xru4,yru1,xru5,yru1,1,1,9);  drawLine(xru5,yru1,xru5,yru2,1,1,9);
  drawLine(xru5,yru1,xru6,yru1,1,1,9); 
  
  
  
  drawLine(xru6,yru1,xru7,yru1,1,1,9);
  drawLine(xru7,yru1,xru8,yru1,1,1,9);
  drawLine(xru8,yru1,xru9,yru1,1,1,9);
  drawLine(xru9,yru1,xru10,yru1,1,1,9);  drawLine(xru10,yru1,xru10,yru2,1,1,9);

  x21 = 6.894-3.993, x22 = 6.894+3.993, y01 = 0.934;
  

  t_cr51->Draw("SAME");

  l_CR_5_1_CBWC_ref3_HRG->Draw("SAME");

  gr_pp_CR_5_1->Draw("P SAME");
  gr_pp_CR_5_1_sys->Draw("P SAME");
  
  
  gr_pp_CR_5_1_sys_CBWC->Draw("psame"); gr_pp_CR_5_1_CBWC->Draw("psame");
  
  gr_auau_CR_5_1_sys->Draw("2 SAME");
  gr_auau_CR_5_1->Draw("P SAME");
  gr_ru_CR_5_1_sys->Draw("2 SAME");
  gr_ru_CR_5_1->Draw("P SAME");
  gr_zr_CR_5_1_sys->Draw("2 SAME");
  gr_zr_CR_5_1->Draw("P SAME");
  
  p_cr62->cd(); p_cr62->SetLogx(1); p_cr62->SetTickx(1);  p_cr62->SetTicky(1); 
  gr_pp_CR_6_2->SetTitle("");
  gr_pp_CR_6_2->Draw("Axgoff");
  box_CR_6_2->Draw("SAME");
  box_CR_6_2_lQCD->Draw("SAME");
  l_CR_6_2_CBWC_ref3_HRG->Draw("SAME");
  

  ya1=-1.4,   ya2=-1.3;
  yru1=-2.1,   yru2=-2.0;
  drawLine(xa1,ya1,xa2,ya1,1,1,7);  drawLine(xa1,ya1,xa1,ya2,1,1,7);  drawLine(xa2,ya1,xa2,ya2,1,1,7);
  drawLine(xa2,ya1,xa3,ya1,1,1,7);  drawLine(xa3,ya1,xa3,ya2,1,1,7); 
  drawLine(xa4,ya1,xa3,ya1,1,1,7);  drawLine(xa4,ya1,xa4,ya2,1,1,7); 
  drawLine(xa4,ya1,xa5,ya1,1,1,7);  drawLine(xa5,ya1,xa5,ya2,1,1,7); 
  drawLine(xa6,ya1,xa5,ya1,1,1,7);  drawLine(xa6,ya1,xa6,ya2,1,1,7);

  drawLine(xru1,yru1,xru2,yru1,1,1,9);  drawLine(xru1,yru1,xru1,yru2,1,1,9);  drawLine(xru2,yru1,xru2,yru2,1,1,9);
  drawLine(xru2,yru1,xru3,yru1,1,1,9);  drawLine(xru3,yru1,xru3,yru2,1,1,9);
  drawLine(xru4,yru1,xru3,yru1,1,1,9);  drawLine(xru4,yru1,xru4,yru2,1,1,9);
  drawLine(xru4,yru1,xru5,yru1,1,1,9);  drawLine(xru5,yru1,xru5,yru2,1,1,9);
  drawLine(xru5,yru1,xru6,yru1,1,1,9);  
  
  
  
  drawLine(xru6,yru1,xru7,yru1,1,1,9);
  drawLine(xru7,yru1,xru8,yru1,1,1,9);
  drawLine(xru8,yru1,xru9,yru1,1,1,9);
  drawLine(xru9,yru1,xru10,yru1,1,1,9);  drawLine(xru10,yru1,xru10,yru2,1,1,9);

  x21 = 6.894-3.993, x22 = 6.894+3.993, y01 = 0.798;
  
  latex->SetTextSize(0.04);     latex->SetTextFont(42);  latex->SetTextColor(kCyan+2);   latex->SetTextAngle(0);
  latex->DrawLatex(25-13,ya1-0.05,"Au+Au: ");
  latex->SetTextSize(0.04);     latex->SetTextFont(42);  latex->SetTextColor(9);   latex->SetTextAngle(0);
  latex->DrawLatex(25-13-2, yru1-0.05,"Zr#oplusRu: ");

  t_cr62->Draw("SAME");

  
  TLegend *leg_CR_6_2_1 = new TLegend(0.15, 0.15, 0.45, 0.44);
  leg_CR_6_2_1->SetFillColorAlpha(kCyan-10, 0);
  leg_CR_6_2_1->SetLineColorAlpha(0, 0);
  leg_CR_6_2_1->AddEntry(gr_pp_CR_6_2_CBWC, "p+p", "p");
  leg_CR_6_2_1->AddEntry(gr_auau_CR_6_2, "Au+Au", "p");
  leg_CR_6_2_1->Draw("SAME");
  TLegend *leg_CR_6_2_2 = new TLegend(0.45, 0.15, 0.75, 0.45);
  leg_CR_6_2_2->SetFillColorAlpha(kCyan-10, 0);
  leg_CR_6_2_2->SetLineColorAlpha(0, 0);
  leg_CR_6_2_2->AddEntry(gr_zr_CR_6_2, "Zr+Zr", "p");
  leg_CR_6_2_2->AddEntry(gr_ru_CR_6_2, "Ru+Ru", "p");
  leg_CR_6_2_2->Draw("SAME");

  gr_pp_CR_6_2->Draw("P SAME");
  gr_pp_CR_6_2_sys->Draw("P SAME");
  
  
  gr_pp_CR_6_2_sys_CBWC->Draw("psame"); gr_pp_CR_6_2_CBWC->Draw("psame");
  
  gr_auau_CR_6_2_sys->Draw("2 SAME");
  gr_auau_CR_6_2->Draw("P SAME");
  gr_ru_CR_6_2_sys->Draw("2 SAME");
  gr_ru_CR_6_2->Draw("P SAME");
  gr_zr_CR_6_2_sys->Draw("2 SAME");
  gr_zr_CR_6_2->Draw("P SAME");

  

  TMultiGraph *mg_CR_4_2_zr = new TMultiGraph();
  mg_CR_4_2_zr->Add(gr_zr_CR_4_2); mg_CR_4_2_zr->Add(gr_zr_CR_4_2_sys);
  TMultiGraph *mg_CR_5_1_zr = new TMultiGraph();
  mg_CR_5_1_zr->Add(gr_zr_CR_5_1); mg_CR_5_1_zr->Add(gr_zr_CR_5_1_sys);
  TMultiGraph *mg_CR_6_2_zr = new TMultiGraph();
  mg_CR_6_2_zr->Add(gr_zr_CR_6_2); mg_CR_6_2_zr->Add(gr_zr_CR_6_2_sys);

  TMultiGraph *mg_CR_4_2_ru = new TMultiGraph();
  mg_CR_4_2_ru->Add(gr_ru_CR_4_2); mg_CR_4_2_ru->Add(gr_ru_CR_4_2_sys);
  TMultiGraph *mg_CR_5_1_ru = new TMultiGraph();
  mg_CR_5_1_ru->Add(gr_ru_CR_5_1); mg_CR_5_1_ru->Add(gr_ru_CR_5_1_sys);
  TMultiGraph *mg_CR_6_2_ru = new TMultiGraph();
  mg_CR_6_2_ru->Add(gr_ru_CR_6_2); mg_CR_6_2_ru->Add(gr_ru_CR_6_2_sys);

  TMultiGraph *mg_CR_4_2_ruzr = new TMultiGraph();
  mg_CR_4_2_ruzr->Add(gr_ru_CR_4_2); mg_CR_4_2_ruzr->Add(gr_ru_CR_4_2_sys); mg_CR_4_2_ruzr->Add(gr_zr_CR_4_2); mg_CR_4_2_ruzr->Add(gr_zr_CR_4_2_sys);
  TMultiGraph *mg_CR_5_1_ruzr = new TMultiGraph();
  mg_CR_5_1_ruzr->Add(gr_ru_CR_5_1); mg_CR_5_1_ruzr->Add(gr_ru_CR_5_1_sys); mg_CR_5_1_ruzr->Add(gr_zr_CR_5_1); mg_CR_5_1_ruzr->Add(gr_zr_CR_5_1_sys);
  TMultiGraph *mg_CR_6_2_ruzr = new TMultiGraph();
  mg_CR_6_2_ruzr->Add(gr_ru_CR_6_2); mg_CR_6_2_ruzr->Add(gr_ru_CR_6_2_sys); mg_CR_6_2_ruzr->Add(gr_zr_CR_6_2); mg_CR_6_2_ruzr->Add(gr_zr_CR_6_2_sys);

  TMultiGraph *mg_CR_4_2_all = new TMultiGraph();
  
  mg_CR_4_2_all->Add(gr_pp_CR_4_2_CBWC_feb22); mg_CR_4_2_all->Add(gr_pp_CR_4_2_sys_CBWC_feb22);
  mg_CR_4_2_all->Add(gr_auau_CR_4_2); mg_CR_4_2_all->Add(gr_auau_CR_4_2_sys);
  mg_CR_4_2_all->Add(gr_ru_CR_4_2); mg_CR_4_2_all->Add(gr_ru_CR_4_2_sys); mg_CR_4_2_all->Add(gr_zr_CR_4_2); mg_CR_4_2_all->Add(gr_zr_CR_4_2_sys);
  TMultiGraph *mg_CR_5_1_all = new TMultiGraph();
  
  mg_CR_5_1_all->Add(gr_pp_CR_5_1_CBWC_feb22); mg_CR_5_1_all->Add(gr_pp_CR_5_1_sys_CBWC_feb22);
  mg_CR_5_1_all->Add(gr_auau_CR_5_1); mg_CR_5_1_all->Add(gr_auau_CR_5_1_sys);
  mg_CR_5_1_all->Add(gr_ru_CR_5_1); mg_CR_5_1_all->Add(gr_ru_CR_5_1_sys); mg_CR_5_1_all->Add(gr_zr_CR_5_1); mg_CR_5_1_all->Add(gr_zr_CR_5_1_sys);
  TMultiGraph *mg_CR_6_2_all = new TMultiGraph();
  
  mg_CR_6_2_all->Add(gr_pp_CR_6_2_CBWC_feb22); mg_CR_6_2_all->Add(gr_pp_CR_6_2_sys_CBWC_feb22);
  mg_CR_6_2_all->Add(gr_auau_CR_6_2); mg_CR_6_2_all->Add(gr_auau_CR_6_2_sys);
  mg_CR_6_2_all->Add(gr_ru_CR_6_2); mg_CR_6_2_all->Add(gr_ru_CR_6_2_sys); mg_CR_6_2_all->Add(gr_zr_CR_6_2); mg_CR_6_2_all->Add(gr_zr_CR_6_2_sys);

  TMultiGraph *mg_CR_4_2_allppold = new TMultiGraph();
  mg_CR_4_2_allppold->Add(gr_pp_CR_4_2); mg_CR_4_2_allppold->Add(gr_pp_CR_4_2_sys);
  
  mg_CR_4_2_allppold->Add(gr_auau_CR_4_2); mg_CR_4_2_allppold->Add(gr_auau_CR_4_2_sys);
  mg_CR_4_2_allppold->Add(gr_ru_CR_4_2); mg_CR_4_2_allppold->Add(gr_ru_CR_4_2_sys); mg_CR_4_2_allppold->Add(gr_zr_CR_4_2); mg_CR_4_2_allppold->Add(gr_zr_CR_4_2_sys);
  TMultiGraph *mg_CR_5_1_allppold = new TMultiGraph();
  mg_CR_5_1_allppold->Add(gr_pp_CR_5_1); mg_CR_5_1_allppold->Add(gr_pp_CR_5_1_sys);
  
  mg_CR_5_1_allppold->Add(gr_auau_CR_5_1); mg_CR_5_1_allppold->Add(gr_auau_CR_5_1_sys);
  mg_CR_5_1_allppold->Add(gr_ru_CR_5_1); mg_CR_5_1_allppold->Add(gr_ru_CR_5_1_sys); mg_CR_5_1_allppold->Add(gr_zr_CR_5_1); mg_CR_5_1_allppold->Add(gr_zr_CR_5_1_sys);
  TMultiGraph *mg_CR_6_2_allppold = new TMultiGraph();
  mg_CR_6_2_allppold->Add(gr_pp_CR_6_2); mg_CR_6_2_allppold->Add(gr_pp_CR_6_2_sys);
  
  mg_CR_6_2_allppold->Add(gr_auau_CR_6_2); mg_CR_6_2_allppold->Add(gr_auau_CR_6_2_sys);
  mg_CR_6_2_allppold->Add(gr_ru_CR_6_2); mg_CR_6_2_allppold->Add(gr_ru_CR_6_2_sys); mg_CR_6_2_allppold->Add(gr_zr_CR_6_2); mg_CR_6_2_allppold->Add(gr_zr_CR_6_2_sys);

  TF1 *f1_CR_4_2_zr = new TF1("f1_CR_4_2_zr", "pol1", 2, 2000); f1_CR_4_2_zr->SetLineColor(6); f1_CR_4_2_zr->SetLineStyle(2);
  TF1 *f1_CR_4_2_ru = new TF1("f1_CR_4_2_ru", "pol1", 2, 2000); f1_CR_4_2_ru->SetLineColor(4); f1_CR_4_2_ru->SetLineStyle(2);
  TF1 *f1_CR_5_1_zr = new TF1("f1_CR_5_1_zr", "pol1", 2, 2000); f1_CR_5_1_zr->SetLineColor(6); f1_CR_5_1_zr->SetLineStyle(2);
  TF1 *f1_CR_5_1_ru = new TF1("f1_CR_5_1_ru", "pol1", 2, 2000); f1_CR_5_1_ru->SetLineColor(4); f1_CR_5_1_ru->SetLineStyle(2);
  TF1 *f1_CR_6_2_zr = new TF1("f1_CR_6_2_zr", "pol1", 2, 2000); f1_CR_6_2_zr->SetLineColor(6); f1_CR_6_2_zr->SetLineStyle(2);
  TF1 *f1_CR_6_2_ru = new TF1("f1_CR_6_2_ru", "pol1", 2, 2000); f1_CR_6_2_ru->SetLineColor(4); f1_CR_6_2_ru->SetLineStyle(2);

  cout<<"===========cr42 zr fit results below==========="<<endl;
  mg_CR_4_2_zr->Fit(f1_CR_4_2_zr, "FR");
  
   TGraphErrors *grint_cr_4_2_zr = new TGraphErrors();
   grint_cr_4_2_zr->SetTitle("Fitted line with .682 conf. band");
   
   grint_cr_4_2_zr->SetPoint(0, 900, 0);
   grint_cr_4_2_zr->SetPoint(1, 1000, 0);
   grint_cr_4_2_zr->SetPoint(2, 1500, 0);
   grint_cr_4_2_zr->SetPoint(3, 1600, 0);
   grint_cr_4_2_zr->SetPoint(4, 1700, 0);
   grint_cr_4_2_zr->SetPoint(5, 1800, 0);
   grint_cr_4_2_zr->SetPoint(6, 1900, 0);
   
   
   (TVirtualFitter::GetFitter())->GetConfidenceIntervals(grint_cr_4_2_zr, 0.682);
   
   p_cr42->cd();
   grint_cr_4_2_zr->SetLineWidth(2);
   grint_cr_4_2_zr->SetLineColor(kMagenta);
   grint_cr_4_2_zr->SetLineStyle(2);
   grint_cr_4_2_zr->SetFillStyle(3004);
   grint_cr_4_2_zr->SetFillColorAlpha(kMagenta, 0.9);
   grint_cr_4_2_zr->Draw("3 same");
  

  cout<<"===========cr42 ru fit results below==========="<<endl;
  mg_CR_4_2_ru->Fit(f1_CR_4_2_ru, "FR");
  
   TGraphErrors *grint_cr_4_2_ru = new TGraphErrors();
   grint_cr_4_2_ru->SetTitle("Fitted line with .682 conf. band");
   for (int i_cent=0; i_cent < 7; i_cent++)
      grint_cr_4_2_ru->SetPoint(i_cent, i_cent*100 + 900, 0);
   
   (TVirtualFitter::GetFitter())->GetConfidenceIntervals(grint_cr_4_2_ru, 0.682);
   
   
   
   p_cr42->cd();
   grint_cr_4_2_ru->SetLineWidth(2);
   grint_cr_4_2_ru->SetLineColor(kBlue);
   grint_cr_4_2_ru->SetLineStyle(2);
   grint_cr_4_2_ru->SetFillStyle(3005);
   grint_cr_4_2_ru->SetFillColorAlpha(kBlue, 0.9);
   grint_cr_4_2_ru->Draw("3 same");
  

  cout<<"===========cr51 zr fit results below==========="<<endl;
  mg_CR_5_1_zr->Fit(f1_CR_5_1_zr, "FR");
  
   TGraphErrors *grint_cr_5_1_zr = new TGraphErrors();
   grint_cr_5_1_zr->SetTitle("Fitted line with .682 conf. band");
   
   
   
   grint_cr_5_1_zr->SetPoint(0, 900, 0);
   grint_cr_5_1_zr->SetPoint(1, 1000, 0);
   grint_cr_5_1_zr->SetPoint(2, 1500, 0);
   grint_cr_5_1_zr->SetPoint(3, 1600, 0);
   grint_cr_5_1_zr->SetPoint(4, 1700, 0);
   grint_cr_5_1_zr->SetPoint(5, 1800, 0);
   grint_cr_5_1_zr->SetPoint(6, 1900, 0);
   
   
   (TVirtualFitter::GetFitter())->GetConfidenceIntervals(grint_cr_5_1_zr, 0.682);
   
   

   
   p_cr51->cd();
   grint_cr_5_1_zr->SetLineWidth(2);
   grint_cr_5_1_zr->SetLineColor(kMagenta);
   grint_cr_5_1_zr->SetLineStyle(2);
   grint_cr_5_1_zr->SetFillStyle(3004);
   grint_cr_5_1_zr->SetFillColorAlpha(kMagenta, 0.9);
   grint_cr_5_1_zr->Draw("3 same");
  

  cout<<"===========cr51 ru fit results below==========="<<endl;
  mg_CR_5_1_ru->Fit(f1_CR_5_1_ru, "FR");
  
   TGraphErrors *grint_cr_5_1_ru = new TGraphErrors();
   grint_cr_5_1_ru->SetTitle("Fitted line with .682 conf. band");
   for (int i_cent=0; i_cent < 7; i_cent++)
      grint_cr_5_1_ru->SetPoint(i_cent, i_cent*100 + 900, 0);
   
   (TVirtualFitter::GetFitter())->GetConfidenceIntervals(grint_cr_5_1_ru, 0.682);
   
   
   
   p_cr51->cd();
   grint_cr_5_1_ru->SetLineWidth(2);
   grint_cr_5_1_ru->SetLineColor(kBlue);
   grint_cr_5_1_ru->SetLineStyle(2);
   grint_cr_5_1_ru->SetFillStyle(3005);
   grint_cr_5_1_ru->SetFillColorAlpha(kBlue, 0.9);
   grint_cr_5_1_ru->Draw("3 same");
  

  cout<<"===========cr62 zr fit results below==========="<<endl;
   mg_CR_6_2_zr->Fit(f1_CR_6_2_zr, "FR");
  
   TGraphErrors *grint_cr_6_2_zr = new TGraphErrors();
   grint_cr_6_2_zr->SetTitle("Fitted line with .682 conf. band");
   for (int i_cent=0; i_cent < 7; i_cent++)
      grint_cr_6_2_zr->SetPoint(i_cent, i_cent*100 + 900, 0);
   
   (TVirtualFitter::GetFitter())->GetConfidenceIntervals(grint_cr_6_2_zr, 0.682);
   
   
   
   p_cr62->cd();
   grint_cr_6_2_zr->SetLineWidth(2);
   grint_cr_6_2_zr->SetLineColor(kMagenta);
   grint_cr_6_2_zr->SetLineStyle(2);
   grint_cr_6_2_zr->SetFillStyle(3004);
   grint_cr_6_2_zr->SetFillColorAlpha(kMagenta, 0.9);
   grint_cr_6_2_zr->Draw("3 same");
  

  cout<<"===========cr62 ru fit results below==========="<<endl;
   mg_CR_6_2_ru->Fit(f1_CR_6_2_ru, "FR");
  
   TGraphErrors *grint_cr_6_2_ru = new TGraphErrors();
   grint_cr_6_2_ru->SetTitle("Fitted line with .682 conf. band");
   for (int i_cent=0; i_cent < 7; i_cent++)
      grint_cr_6_2_ru->SetPoint(i_cent, i_cent*100 + 900, 0);
   
   (TVirtualFitter::GetFitter())->GetConfidenceIntervals(grint_cr_6_2_ru, 0.682);
   
   
   
   p_cr62->cd();
   grint_cr_6_2_ru->SetLineWidth(2);
   grint_cr_6_2_ru->SetLineColor(kBlue);
   grint_cr_6_2_ru->SetLineStyle(2);
   grint_cr_6_2_ru->SetFillStyle(3005);
   grint_cr_6_2_ru->SetFillColorAlpha(kBlue, 0.9);
   grint_cr_6_2_ru->Draw("3 same");
  
  
  TF1 *f1_CR_4_2_ruzr = new TF1("f1_CR_4_2_ruzr", "pol1", 2, 2000); f1_CR_4_2_ruzr->SetLineColor(12); f1_CR_4_2_ruzr->SetLineStyle(1);
  TF1 *f1_CR_5_1_ruzr = new TF1("f1_CR_5_1_ruzr", "pol1", 2, 2000); f1_CR_5_1_ruzr->SetLineColor(12); f1_CR_5_1_ruzr->SetLineStyle(1);
  TF1 *f1_CR_6_2_ruzr = new TF1("f1_CR_6_2_ruzr", "pol1", 2, 2000); f1_CR_6_2_ruzr->SetLineColor(12); f1_CR_6_2_ruzr->SetLineStyle(1);

  
  
  cout<<"===========cr42 ruzr fit results below==========="<<endl;
  mg_CR_4_2_ruzr->Fit(f1_CR_4_2_ruzr, "FR");
  
   TGraphErrors *grint_cr_4_2_ruzr = new TGraphErrors();
   grint_cr_4_2_ruzr->SetTitle("Fitted line with .682 conf. band");
   for (int i_cent=0; i_cent < 7; i_cent++)
      grint_cr_4_2_ruzr->SetPoint(i_cent, i_cent*100 + 900, 0);
   
   (TVirtualFitter::GetFitter())->GetConfidenceIntervals(grint_cr_4_2_ruzr, 0.682);
   
   
   
   p_cr51->cd();
   grint_cr_4_2_ruzr->SetLineWidth(2);
   grint_cr_4_2_ruzr->SetLineColor(12);
   grint_cr_4_2_ruzr->SetLineStyle(2);
   grint_cr_4_2_ruzr->SetFillStyle(3006);
   grint_cr_4_2_ruzr->SetFillColorAlpha(12, 0.9);
   grint_cr_4_2_ruzr->Draw("3 same");
  

  cout<<"===========cr51 ruzr fit results below==========="<<endl;
  mg_CR_5_1_ruzr->Fit(f1_CR_5_1_ruzr, "FR");
  
   TGraphErrors *grint_cr_5_1_ruzr = new TGraphErrors();
   grint_cr_5_1_ruzr->SetTitle("Fitted line with .682 conf. band");
   for (int i_cent=0; i_cent < 7; i_cent++)
      grint_cr_5_1_ruzr->SetPoint(i_cent, i_cent*100 + 900, 0);
   
   (TVirtualFitter::GetFitter())->GetConfidenceIntervals(grint_cr_5_1_ruzr, 0.682);
   
   
   
   p_cr51->cd();
   grint_cr_5_1_ruzr->SetLineWidth(2);
   grint_cr_5_1_ruzr->SetLineColor(12);
   grint_cr_5_1_ruzr->SetLineStyle(2);
   grint_cr_5_1_ruzr->SetFillStyle(3006);
   grint_cr_5_1_ruzr->SetFillColorAlpha(12, 0.9);
   grint_cr_5_1_ruzr->Draw("3 same");
  

  cout<<"===========cr62 ruzr fit results below==========="<<endl;
  mg_CR_6_2_ruzr->Fit(f1_CR_6_2_ruzr, "FR");
  
   TGraphErrors *grint_cr_6_2_ruzr = new TGraphErrors();
   grint_cr_6_2_ruzr->SetTitle("Fitted line with .682 conf. band");
   for (int i_cent=0; i_cent < 7; i_cent++)
      grint_cr_6_2_ruzr->SetPoint(i_cent, i_cent*100 + 900, 0);
   
   (TVirtualFitter::GetFitter())->GetConfidenceIntervals(grint_cr_6_2_ruzr, 0.682);
   
   
   
   p_cr62->cd();
   grint_cr_6_2_ruzr->SetLineWidth(2);
   grint_cr_6_2_ruzr->SetLineColor(12);
   grint_cr_6_2_ruzr->SetLineStyle(2);
   grint_cr_6_2_ruzr->SetFillStyle(3006);
   grint_cr_6_2_ruzr->SetFillColorAlpha(12, 0.9);
   grint_cr_6_2_ruzr->Draw("3 same");
  

  
  TF1 *f1_CR_4_2_all = new TF1("f1_CR_4_2_all", "pol1", 2, 2000); f1_CR_4_2_all->SetLineColor(2); f1_CR_4_2_all->SetLineStyle(1);
  TF1 *f1_CR_5_1_all = new TF1("f1_CR_5_1_all", "pol1", 2, 2000); f1_CR_5_1_all->SetLineColor(2); f1_CR_5_1_all->SetLineStyle(1);
  TF1 *f1_CR_6_2_all = new TF1("f1_CR_6_2_all", "pol1", 2, 2000); f1_CR_6_2_all->SetLineColor(2); f1_CR_6_2_all->SetLineStyle(1);

  
  
  TF1 *f1_CR_4_2_allppold = new TF1("f1_CR_4_2_allppold", "pol1", 2, 2000); f1_CR_4_2_allppold->SetLineColor(2); f1_CR_4_2_allppold->SetLineStyle(2);
  TF1 *f1_CR_5_1_allppold = new TF1("f1_CR_5_1_allppold", "pol1", 2, 2000); f1_CR_5_1_allppold->SetLineColor(2); f1_CR_5_1_allppold->SetLineStyle(2);
  TF1 *f1_CR_6_2_allppold = new TF1("f1_CR_6_2_allppold", "pol1", 2, 2000); f1_CR_6_2_allppold->SetLineColor(2); f1_CR_6_2_allppold->SetLineStyle(2);

  cout<<"===========cr42 all fit results below==========="<<endl;
  mg_CR_4_2_allppold->Fit(f1_CR_4_2_allppold, "FR");
  
   TGraphErrors *grint_cr_4_2_allppold = new TGraphErrors();
   grint_cr_4_2_allppold->SetTitle("Fitted line with .682 conf. band");
   for (int i_cent=0; i_cent < 7; i_cent++)
      grint_cr_4_2_allppold->SetPoint(i_cent, i_cent*100 + 900, 0);
   
   (TVirtualFitter::GetFitter())->GetConfidenceIntervals(grint_cr_4_2_allppold, 0.682);
   
   
   
   p_cr51->cd();
   grint_cr_4_2_allppold->SetLineWidth(2);
   grint_cr_4_2_allppold->SetLineColor(kRed);
   grint_cr_4_2_allppold->SetLineStyle(2);
   grint_cr_4_2_allppold->SetFillStyle(3007);
   grint_cr_4_2_allppold->SetFillColorAlpha(kRed, 0.9);
   grint_cr_4_2_allppold->Draw("3 same");
  

  cout<<"===========cr51 all fit results below==========="<<endl;
  mg_CR_5_1_allppold->Fit(f1_CR_5_1_allppold, "FR");
  
   TGraphErrors *grint_cr_5_1_allppold = new TGraphErrors();
   grint_cr_5_1_allppold->SetTitle("Fitted line with .682 conf. band");
   for (int i_cent=0; i_cent < 7; i_cent++)
      grint_cr_5_1_allppold->SetPoint(i_cent, i_cent*100 + 900, 0);
   
   (TVirtualFitter::GetFitter())->GetConfidenceIntervals(grint_cr_5_1_allppold, 0.682);
   
   
   
   p_cr51->cd();
   grint_cr_5_1_allppold->SetLineWidth(2);
   grint_cr_5_1_allppold->SetLineColor(kRed);
   grint_cr_5_1_allppold->SetLineStyle(2);
   grint_cr_5_1_allppold->SetFillStyle(3007);
   grint_cr_5_1_allppold->SetFillColorAlpha(kRed, 0.9);
   grint_cr_5_1_allppold->Draw("3 same");
  

  cout<<"===========cr62 all fit results below==========="<<endl;
  mg_CR_6_2_allppold->Fit(f1_CR_6_2_allppold, "FR");
  
   TGraphErrors *grint_cr_6_2_allppold = new TGraphErrors();
   grint_cr_6_2_allppold->SetTitle("Fitted line with .682 conf. band");
   for (int i_cent=0; i_cent < 7; i_cent++)
      grint_cr_6_2_allppold->SetPoint(i_cent, i_cent*100 + 500, 0);
   
   (TVirtualFitter::GetFitter())->GetConfidenceIntervals(grint_cr_6_2_allppold, 0.682);
   
   
   
   p_cr62->cd();
   grint_cr_6_2_allppold->SetLineWidth(2);
   grint_cr_6_2_allppold->SetLineColor(kRed);
   grint_cr_6_2_allppold->SetLineStyle(2);
   grint_cr_6_2_allppold->SetFillStyle(3007);
   grint_cr_6_2_allppold->SetFillColorAlpha(kRed, 0.9);
   grint_cr_6_2_allppold->Draw("3 same");
  
  
  p_cr42->cd(); f1_CR_4_2_zr->Draw("SAME"); f1_CR_4_2_ru->Draw("SAME"); f1_CR_4_2_allppold->Draw("SAME"); f1_CR_4_2_ruzr->Draw("SAME");
  p_cr51->cd(); f1_CR_5_1_zr->Draw("SAME"); f1_CR_5_1_ru->Draw("SAME"); f1_CR_5_1_allppold->Draw("SAME"); f1_CR_5_1_ruzr->Draw("SAME");
   
  p_cr62->cd(); f1_CR_6_2_zr->Draw("SAME"); f1_CR_6_2_ru->Draw("SAME");  f1_CR_6_2_allppold->Draw("SAME"); f1_CR_6_2_ruzr->Draw("SAME");
  

  p_cr51->cd();
  TLegend *leg_fit = new TLegend(0.5, 0.15, 0.99, 0.5, "", "NDC NB");  leg_fit->SetBorderSize(0); leg_fit->SetFillColorAlpha(0,0);
  leg_fit->AddEntry(f1_CR_5_1_zr, "Zr+Zr", "l");
  leg_fit->AddEntry(f1_CR_5_1_ru, "Ru+Ru", "l");
  leg_fit->AddEntry(f1_CR_5_1_ruzr, "Zr#oplusRu", "l");
  leg_fit->AddEntry(f1_CR_5_1_allppold, "All systems", "l");
  leg_fit->Draw("same");

  if(!scale){
    c_CR_3tot_pad->Print(Form("./output/pics/money_plot_fit_std.png"));
  }
  else{
    c_CR_3tot_pad->Print(Form("./output/pics/money_plot_fit_std.png"));
  }
  
  
  
  
  
  
  
  
  
  
  
  
  gr_pp_CR_4_2->GetYaxis()->SetRangeUser(0.75, 1.08);
  gr_pp_CR_5_1->GetYaxis()->SetRangeUser(-0.5, 3.1);
  gr_pp_CR_6_2->GetYaxis()->SetRangeUser(-0.15, 1.57);
  gr_pp_CR_4_2->GetXaxis()->SetLimits(3, 50);
  gr_pp_CR_5_1->GetXaxis()->SetLimits(3, 50);
  gr_pp_CR_6_2->GetXaxis()->SetLimits(3, 50);
  TPad *p_ppnewold_cr42 = new TPad("p_ppnewold_cr42", "p_ppnewold_cr42", 0.00+0.*1.0/3., 0.0, 0.00+1.*1.0/3.-(-1.0)*0.001, 0.99);                    p_ppnewold_cr42->SetLeftMargin(0.11); p_ppnewold_cr42->SetRightMargin(0.009); p_ppnewold_cr42->SetTopMargin(0.); p_ppnewold_cr42->SetBottomMargin(0.105);
  TPad *p_ppnewold_cr51 = new TPad("p_ppnewold_cr51", "p_ppnewold_cr51", 0.00+1.*1.0/3.+(-1.0)*0.001/2., 0.0, 0.00+2.*1.0/3.-(-1.0)*0.001/2., 0.99); p_ppnewold_cr51->SetLeftMargin(0.09); p_ppnewold_cr51->SetRightMargin(0.009); p_ppnewold_cr51->SetTopMargin(0.); p_ppnewold_cr51->SetBottomMargin(0.105);
  TPad *p_ppnewold_cr62 = new TPad("p_ppnewold_cr62", "p_ppnewold_cr62", 0.00+2.*1.0/3.+(-1.0)*0.001, 0.0, 0.00+3.*1.0/3., 0.99);                    p_ppnewold_cr62->SetLeftMargin(0.09); p_ppnewold_cr62->SetRightMargin(0.009); p_ppnewold_cr62->SetTopMargin(0.); p_ppnewold_cr62->SetBottomMargin(0.105);
  gr_pp_CR_4_2->Draw("AP");
  gr_pp_CR_4_2_sys->Draw("P SAME");
  gr_pp_CR_4_2_feb22->Draw("P SAME");
  gr_pp_CR_4_2_sys_feb22->Draw("P SAME");
  gr_pp_CR_4_2_sys_CBWC->Draw("psame"); gr_pp_CR_4_2_CBWC->Draw("psame");
  gr_pp_CR_4_2_sys_CBWC_feb22->Draw("psame"); gr_pp_CR_4_2_CBWC_feb22->Draw("psame");
  t_cr42->Draw("SAME");
  TLine *l_CR_4_2_CBWC_ref3_HRG_ppnewold = new TLine(gr_pp_CR_4_2->GetXaxis()->GetXmin(), 0.997, gr_pp_CR_4_2->GetXaxis()->GetXmax(), 0.997);
  l_CR_4_2_CBWC_ref3_HRG_ppnewold->SetLineStyle(9);
  l_CR_4_2_CBWC_ref3_HRG_ppnewold->SetLineWidth(1);
  l_CR_4_2_CBWC_ref3_HRG_ppnewold->Draw("SAME");
  p_ppnewold_cr51->cd(); p_ppnewold_cr51->SetLogx(1); p_ppnewold_cr51->SetTickx(1);  p_ppnewold_cr51->SetTicky(1);
  gr_pp_CR_5_1_sys->Draw("2 SAME");
  gr_pp_CR_5_1->Draw("AP");
  gr_pp_CR_5_1_feb22->Draw("P SAME");
  gr_pp_CR_5_1_sys_feb22->Draw("P SAME");
  gr_pp_CR_5_1_sys_CBWC->Draw("psame"); gr_pp_CR_5_1_CBWC->Draw("psame");
  gr_pp_CR_5_1_sys_CBWC_feb22->Draw("psame"); gr_pp_CR_5_1_CBWC_feb22->Draw("psame");
  t_cr51->Draw("SAME");
  TLine *l_CR_5_1_CBWC_ref3_HRG_ppnewold = new TLine(gr_pp_CR_5_1->GetXaxis()->GetXmin(), 0.997, gr_pp_CR_5_1->GetXaxis()->GetXmax(), 0.997);
  l_CR_5_1_CBWC_ref3_HRG_ppnewold->SetLineStyle(9);
  l_CR_5_1_CBWC_ref3_HRG_ppnewold->SetLineWidth(1);
  l_CR_5_1_CBWC_ref3_HRG_ppnewold->Draw("SAME");
  p_ppnewold_cr62->cd(); p_ppnewold_cr62->SetLogx(1); p_ppnewold_cr62->SetTickx(1);  p_ppnewold_cr62->SetTicky(1);
  gr_pp_CR_6_2->Draw("AP");
  gr_pp_CR_6_2_sys->Draw("P SAME");
  gr_pp_CR_6_2_feb22->Draw("P SAME");
  gr_pp_CR_6_2_sys_feb22->Draw("P SAME");
  gr_pp_CR_6_2_sys_CBWC->Draw("psame"); gr_pp_CR_6_2_CBWC->Draw("psame");
  gr_pp_CR_6_2_sys_CBWC_feb22->Draw("psame"); gr_pp_CR_6_2_CBWC_feb22->Draw("psame");
  t_cr62->Draw("SAME");
  TLine *l_CR_6_2_CBWC_ref3_HRG_ppnewold = new TLine(gr_pp_CR_6_2->GetXaxis()->GetXmin(), 0.997, gr_pp_CR_6_2->GetXaxis()->GetXmax(), 0.997);
  l_CR_6_2_CBWC_ref3_HRG_ppnewold->SetLineStyle(9);
  l_CR_6_2_CBWC_ref3_HRG_ppnewold->SetLineWidth(1);
  l_CR_6_2_CBWC_ref3_HRG_ppnewold->Draw("SAME");
  

  
  double x_trend[2]; x_trend[0] = 1; x_trend[1] = 2;

  double CR_trend_ru[2]; CR_trend_ru[0] = f1_CR_5_1_ru->GetParameter(1); CR_trend_ru[1] = f1_CR_6_2_ru->GetParameter(1);
  double CR_trend_err_ru[2]; CR_trend_err_ru[0] = f1_CR_5_1_ru->GetParError(1); CR_trend_err_ru[1] = f1_CR_6_2_ru->GetParError(1);
  double x_shift = 0.2;
  x_trend[0] = 1-x_shift; x_trend[1] = 2-x_shift;
  TGraphErrors *gr_CR_trend_ru = new TGraphErrors(2, x_trend, CR_trend_ru, 0, CR_trend_err_ru); gr_CR_trend_ru->SetMarkerStyle(8); gr_CR_trend_ru->SetMarkerSize(1.5);

  double CR_trend_zr[2]; CR_trend_zr[0] = f1_CR_5_1_zr->GetParameter(1); CR_trend_zr[1] = f1_CR_6_2_zr->GetParameter(1);
  double CR_trend_err_zr[2]; CR_trend_err_zr[0] = f1_CR_5_1_zr->GetParError(1); CR_trend_err_zr[1] = f1_CR_6_2_zr->GetParError(1);
  x_shift = 0.1;
  x_trend[0] = 1-x_shift; x_trend[1] = 2-x_shift;
  TGraphErrors *gr_CR_trend_zr = new TGraphErrors(2, x_trend, CR_trend_zr, 0, CR_trend_err_zr); gr_CR_trend_zr->SetMarkerStyle(4); gr_CR_trend_zr->SetMarkerSize(1.5);

  double CR_trend_ruzr[2]; CR_trend_ruzr[0] = f1_CR_5_1_ruzr->GetParameter(1); CR_trend_ruzr[1] = f1_CR_6_2_ruzr->GetParameter(1);
  double CR_trend_err_ruzr[2]; CR_trend_err_ruzr[0] = f1_CR_5_1_ruzr->GetParError(1); CR_trend_err_ruzr[1] = f1_CR_6_2_ruzr->GetParError(1);
  x_shift = -0.1;
  x_trend[0] = 1-x_shift; x_trend[1] = 2-x_shift;
  TGraphErrors *gr_CR_trend_ruzr = new TGraphErrors(2, x_trend, CR_trend_ruzr, 0, CR_trend_err_ruzr); gr_CR_trend_ruzr->SetMarkerStyle(33); gr_CR_trend_ruzr->SetMarkerSize(1.5);

  double CR_trend_all[2]; CR_trend_all[0] = f1_CR_5_1_all->GetParameter(1); CR_trend_all[1] = f1_CR_6_2_all->GetParameter(1);
  double CR_trend_err_all[2]; CR_trend_err_all[0] = f1_CR_5_1_all->GetParError(1); CR_trend_err_all[1] = f1_CR_6_2_all->GetParError(1);
  x_shift = 0.0;
  x_trend[0] = 1-x_shift; x_trend[1] = 2-x_shift;
  TGraphErrors *gr_CR_trend_all = new TGraphErrors(2, x_trend, CR_trend_all, 0, CR_trend_err_all); gr_CR_trend_all->SetMarkerStyle(29); gr_CR_trend_all->SetMarkerColor(2); gr_CR_trend_all->SetMarkerStyle(29); gr_CR_trend_all->SetMarkerSize(1.5);

  double CR_trend_allppold[2]; CR_trend_allppold[0] = f1_CR_5_1_allppold->GetParameter(1); CR_trend_allppold[1] = f1_CR_6_2_allppold->GetParameter(1);
  double CR_trend_err_allppold[2]; CR_trend_err_allppold[0] = f1_CR_5_1_allppold->GetParError(1); CR_trend_err_allppold[1] = f1_CR_6_2_allppold->GetParError(1);
  x_shift = -0.2;
  x_trend[0] = 1-x_shift; x_trend[1] = 2-x_shift;
  TGraphErrors *gr_CR_trend_allppold = new TGraphErrors(2, x_trend, CR_trend_allppold, 0, CR_trend_err_allppold); gr_CR_trend_allppold->SetMarkerStyle(30); gr_CR_trend_allppold->SetMarkerColor(2); gr_CR_trend_allppold->SetMarkerStyle(30); gr_CR_trend_allppold->SetMarkerSize(1.5);

  
  gr_CR_trend_zr->GetXaxis()->SetLimits(-0.5, 3);
  TLine *line_trend_0 = new TLine(gr_CR_trend_zr->GetXaxis()->GetXmin(), 0., gr_CR_trend_zr->GetXaxis()->GetXmax(), 0.);
  line_trend_0->SetLineColor(6);  line_trend_0->SetLineStyle(9);
  
  gr_CR_trend_zr->SetTitle("");
  gr_CR_trend_zr->GetYaxis()->SetTitle("slope");
  gr_CR_trend_zr->GetYaxis()->SetRangeUser(-0.009, 0.007);
  gr_CR_trend_zr->Draw("apx");
  gr_CR_trend_zr->Draw("p same");
  gr_CR_trend_ru->Draw("p x same");
  gr_CR_trend_ru->Draw("p same");
  gr_CR_trend_ruzr->Draw("p x same");
  gr_CR_trend_ruzr->Draw("p same");
  
  
  gr_CR_trend_allppold->Draw("p x same");
  gr_CR_trend_allppold->Draw("p same");
  line_trend_0->Draw("same");
  
  double pad_side_title_buff = 0.02;
  TPad *p_cr42_2 = new TPad("p_cr42_2", "p_cr42_2", 0.00+0.*1.0/3. + 3 * pad_side_title_buff, 0.0, 0.00+1.*1.0/3.-(-1.0)*0.001 + 2 * pad_side_title_buff, 0.99);                    p_cr42_2->SetLeftMargin(0.09); p_cr42_2->SetRightMargin(0.009); p_cr42_2->SetTopMargin(0.); p_cr42_2->SetBottomMargin(0.2); 
  TPad *p_cr51_2 = new TPad("p_cr51_2", "p_cr51_2", 0.00+1.*1.0/3.+(-1.0)*0.001/2. + 2 * pad_side_title_buff, 0.0, 0.00+2.*1.0/3.-(-1.0)*0.001/2. + 1 * pad_side_title_buff, 0.99); p_cr51_2->SetLeftMargin(0.09); p_cr51_2->SetRightMargin(0.009); p_cr51_2->SetTopMargin(0.); p_cr51_2->SetBottomMargin(0.2); 
  TPad *p_cr62_2 = new TPad("p_cr62_2", "p_cr62_2", 0.00+2.*1.0/3.+(-1.0)*0.001 + 1 * pad_side_title_buff, 0.0, 0.00+3.*1.0/3., 0.99);                    p_cr62_2->SetLeftMargin(0.09); p_cr62_2->SetRightMargin(0.009); p_cr62_2->SetTopMargin(0.); p_cr62_2->SetBottomMargin(0.2); 
  gr_pp_CR_4_2->GetXaxis()->SetLabelSize(0.06);
  gr_pp_CR_5_1->GetXaxis()->SetLabelSize(0.06);
  gr_pp_CR_6_2->GetXaxis()->SetLabelSize(0.06);
  gr_pp_CR_4_2->GetYaxis()->SetLabelSize(0.06);
  gr_pp_CR_5_1->GetYaxis()->SetLabelSize(0.06);
  gr_pp_CR_6_2->GetYaxis()->SetLabelSize(0.06);
  gr_pp_CR_4_2->GetXaxis()->SetTitle("");
  gr_pp_CR_5_1->GetXaxis()->SetTitle("");
  gr_pp_CR_6_2->GetXaxis()->SetTitle("");
  gr_pp_CR_4_2->GetYaxis()->SetTitleOffset(.95);
  
  gr_pp_CR_4_2->GetYaxis()->SetLabelOffset(0.0125);
  gr_pp_CR_5_1->GetYaxis()->SetLabelOffset(0.0125);
  gr_pp_CR_6_2->GetYaxis()->SetLabelOffset(0.0125);
  gr_pp_CR_4_2->GetYaxis()->SetRangeUser(0.05, 1.299);
  gr_pp_CR_5_1->GetYaxis()->SetRangeUser(-5.5, 2.4);
  gr_pp_CR_6_2->GetYaxis()->SetRangeUser(-6.5, 3.35);
  gr_pp_CR_4_2->GetYaxis()->SetNdivisions(010);
  gr_pp_CR_5_1->GetYaxis()->SetNdivisions(010);
  gr_pp_CR_6_2->GetYaxis()->SetNdivisions(010);
  gr_pp_CR_4_2->GetXaxis()->SetLimits(2.5, 2000);
  gr_pp_CR_5_1->GetXaxis()->SetLimits(2.5, 2000);
  gr_pp_CR_6_2->GetXaxis()->SetLimits(2.5, 2000);
  TCanvas *c_CR_3tot_pad_2 = new TCanvas("c_CR_3tot_pad_2", "c_CR_3tot_pad_2", 1800, 600); c_CR_3tot_pad_2->cd();

  c_CR_3tot_pad_2->cd();
  TPad *p_tit_vertical = new TPad("p_c_tit_vertical","p_c_tit_vertical", 0.0, 0.11, 0.00+0.*1.0/3. + 3 * pad_side_title_buff, 0.99); p_tit_vertical->Draw();  
  TPaveText *pt_tit_vertical = new TPaveText(0.01, 0.01, 0.99, 0.99, "NDC NB"); pt_tit_vertical->SetFillColorAlpha(0,0);
  TText *t_tit_vertical = pt_tit_vertical->AddText("Cumulant Ratios");
  t_tit_vertical->SetTextAngle(90);
  t_tit_vertical->SetTextAlign(22);
  t_tit_vertical->SetTextSize(0.45);
  p_tit_vertical->cd();
  pt_tit_vertical->Draw();

  c_CR_3tot_pad_2->cd();
  p_cr42_2->Draw(); p_cr51_2->Draw(); p_cr62_2->Draw();
  p_cr42_2->cd(); p_cr42_2->SetLogx(1); p_cr42_2->SetTickx(1);  p_cr42_2->SetTicky(1); 
  

  gr_pp_CR_4_2->SetTitle("");
  gr_pp_CR_4_2->Draw("A X goff");
  box_CR_4_2_lQCD->Draw("SAME");
  box_cr42_frg->Draw("same");
  l_CR_4_2_CBWC_ref3_HRG->Draw("SAME");
  Info1_topleft->Draw("SAME");

  ya1=0.55-0.02,   ya2=0.57-0.02;
  yru1=0.4-0.04,   yru2=0.42-0.04;
  drawLine(xa1,ya1,xa2,ya1,1,1,7);  drawLine(xa1,ya1,xa1,ya2,1,1,7);  drawLine(xa2,ya1,xa2,ya2,1,1,7);
  drawLine(xa2,ya1,xa3,ya1,1,1,7);  drawLine(xa3,ya1,xa3,ya2,1,1,7); 
  drawLine(xa4,ya1,xa3,ya1,1,1,7);  drawLine(xa4,ya1,xa4,ya2,1,1,7); 
  drawLine(xa4,ya1,xa5,ya1,1,1,7);  drawLine(xa5,ya1,xa5,ya2,1,1,7); 
  drawLine(xa6,ya1,xa5,ya1,1,1,7);  drawLine(xa6,ya1,xa6,ya2,1,1,7);

  drawLine(xru1,yru1,xru2,yru1,1,1,9);  drawLine(xru1,yru1,xru1,yru2,1,1,9);  drawLine(xru2,yru1,xru2,yru2,1,1,9);
  drawLine(xru2,yru1,xru3,yru1,1,1,9);  drawLine(xru3,yru1,xru3,yru2,1,1,9);
  drawLine(xru4,yru1,xru3,yru1,1,1,9);  drawLine(xru4,yru1,xru4,yru2,1,1,9);
  drawLine(xru4,yru1,xru5,yru1,1,1,9);  drawLine(xru5,yru1,xru5,yru2,1,1,9);
  drawLine(xru5,yru1,xru6,yru1,1,1,9);  
  
  
  
  drawLine(xru6,yru1,xru7,yru1,1,1,9);
  drawLine(xru7,yru1,xru8,yru1,1,1,9);
  drawLine(xru8,yru1,xru9,yru1,1,1,9);
  drawLine(xru9,yru1,xru10,yru1,1,1,9);  drawLine(xru10,yru1,xru10,yru2,1,1,9);

  

  double x_pythia[1], cr42_pythia[1],cr42err_pythia[1];
  x_pythia[0] = 6.894; cr42_pythia[0] = 0.986126; cr42err_pythia[0] = 0.000348293;
  TGraphErrors *gr_cr42_pythia = new TGraphErrors(1, x_pythia, cr42_pythia, 0, cr42err_pythia); gr_cr42_pythia->SetMarkerStyle(21); gr_cr42_pythia->SetMarkerColor(41); gr_cr42_pythia->SetLineColor(41);  gr_cr42_pythia->SetMarkerSize(1.5);
  gr_cr42_pythia->Draw("psame");

  latex->SetTextSize(0.04);     latex->SetTextFont(42);  latex->SetTextColor(kCyan+2);   latex->SetTextAngle(0);
  latex->DrawLatex(25-13,ya1-0.01,"Au+Au: ");
  latex->SetTextSize(0.04);     latex->SetTextFont(42);  latex->SetTextColor(9);   latex->SetTextAngle(0);
  latex->DrawLatex(25-13, yru1-0.01,"Zr#oplusRu: ");
  
  

  t_cr42->Draw("SAME");

  ya1 -= 0.025+0.01;
  latex->SetTextColor(1);
  latex->SetTextAlign(30);   latex->SetTextFont(82);   latex->SetTextSize(0.035);   latex->SetTextAngle(45);
  latex->DrawLatex(25+2,ya1,"70-80%");
  latex->DrawLatex(50+2,ya1,"60-70%");
  latex->DrawLatex(90+2,ya1,"50-60%");
  latex->DrawLatex(180-5,ya1,"40-50%");
  
  latex->DrawLatex(400,ya1-0.01,"0-40%");

  
  gr_pp_CR_4_2_sys->Draw("2 SAME");
  gr_pp_CR_4_2->Draw("P SAME");
  gr_pp_CR_4_2_sys_CBWC->Draw("psame"); gr_pp_CR_4_2_CBWC->Draw("psame");
  gr_auau_CR_4_2_sys->Draw("2 SAME");
  gr_auau_CR_4_2->Draw("P SAME");
  gr_ru_CR_4_2_sys->Draw("2 SAME");
  gr_ru_CR_4_2->Draw("P SAME");
  gr_zr_CR_4_2_sys->Draw("2 SAME");
  gr_zr_CR_4_2->Draw("P SAME");

  p_cr51_2->cd(); p_cr51_2->SetLogx(1); p_cr51_2->SetTickx(1);  p_cr51_2->SetTicky(1); 
  gr_pp_CR_5_1->GetYaxis()->SetRangeUser(-5.5, 2.99);
  gr_pp_CR_5_1->SetTitle("");
  gr_pp_CR_5_1->Draw("A X goff");
  box_CR_5_1->Draw("SAME");
  box_CR_5_1_lQCD->Draw("SAME");
  box_cr51_frg->Draw("same");

  ya1=-1.8,   ya2=-1.7;
  yru1=-2.7,   yru2=-2.6;
  drawLine(xa1,ya1,xa2,ya1,1,1,7);  drawLine(xa1,ya1,xa1,ya2,1,1,7);  drawLine(xa2,ya1,xa2,ya2,1,1,7);
  drawLine(xa2,ya1,xa3,ya1,1,1,7);  drawLine(xa3,ya1,xa3,ya2,1,1,7); 
  drawLine(xa4,ya1,xa3,ya1,1,1,7);  drawLine(xa4,ya1,xa4,ya2,1,1,7); 
  drawLine(xa4,ya1,xa5,ya1,1,1,7);  drawLine(xa5,ya1,xa5,ya2,1,1,7); 
  drawLine(xa6,ya1,xa5,ya1,1,1,7);  drawLine(xa6,ya1,xa6,ya2,1,1,7);

  drawLine(xru1,yru1,xru2,yru1,1,1,9);  drawLine(xru1,yru1,xru1,yru2,1,1,9);  drawLine(xru2,yru1,xru2,yru2,1,1,9);
  drawLine(xru2,yru1,xru3,yru1,1,1,9);  drawLine(xru3,yru1,xru3,yru2,1,1,9);
  drawLine(xru4,yru1,xru3,yru1,1,1,9);  drawLine(xru4,yru1,xru4,yru2,1,1,9);
  drawLine(xru4,yru1,xru5,yru1,1,1,9);  drawLine(xru5,yru1,xru5,yru2,1,1,9);
  drawLine(xru5,yru1,xru6,yru1,1,1,9); 
  
  
  
  drawLine(xru6,yru1,xru7,yru1,1,1,9);
  drawLine(xru7,yru1,xru8,yru1,1,1,9);
  drawLine(xru8,yru1,xru9,yru1,1,1,9);
  drawLine(xru9,yru1,xru10,yru1,1,1,9);  drawLine(xru10,yru1,xru10,yru2,1,1,9);

  latex->SetTextSize(0.04);     latex->SetTextFont(42);  latex->SetTextColor(kCyan+2);   latex->SetTextAngle(0);
  latex->DrawLatex(25-13,ya1-0.05,"Au+Au: ");
  latex->SetTextSize(0.04);     latex->SetTextFont(42);  latex->SetTextColor(9);   latex->SetTextAngle(0);
  latex->DrawLatex(25-13-2, yru1-0.05,"Zr#oplusRu: ");
  leg_CR_5_1->Draw("SAME");

  

  t_cr51->Draw("SAME");

  l_CR_5_1_CBWC_ref3_HRG->Draw("SAME");

  x21 = 6.894-3.993, x22 = 6.894+3.993, y01 = 0.828961;
  double cr51_pythia[1],cr51err_pythia[1];
  cr51_pythia[0] = 0.828961; cr51err_pythia[0] = 0.0146119;;
  TGraphErrors *gr_cr51_pythia = new TGraphErrors(1, x_pythia, cr51_pythia, 0, cr51err_pythia); gr_cr51_pythia->SetMarkerStyle(21); gr_cr51_pythia->SetMarkerColor(41); gr_cr51_pythia->SetLineColor(41);  gr_cr51_pythia->SetMarkerSize(1.5);
  gr_cr51_pythia->Draw("psame");

  
  
  TLegend *leg_CR_6_2_3 = new TLegend(0.44, 0.22, 0.74, 0.45);
  leg_CR_6_2_3->SetFillColorAlpha(kCyan-10, 0);
  leg_CR_6_2_3->SetLineColorAlpha(0, 0);
  leg_CR_6_2_3->AddEntry(l_CR_5_1_CBWC_ref3_HRG, "HRG GCE", "l");
  TGraphErrors *gr_pp_CR_6_2_leg = (TGraphErrors*)gr_pp_CR_6_2->Clone("gr_pp_CR_6_2_leg"); gr_pp_CR_6_2_leg->SetMarkerSize(2);
  TGraphErrors *gr_pp_CR_6_2_CBWC_leg = (TGraphErrors*)gr_pp_CR_6_2_CBWC->Clone("gr_pp_CR_6_2_CBWC_leg"); gr_pp_CR_6_2_CBWC_leg->SetMarkerSize(2.2);
  leg_CR_6_2_3->AddEntry(gr_pp_CR_6_2_leg, "p+p", "p");
  leg_CR_6_2_3->AddEntry(gr_pp_CR_6_2_CBWC_leg, "p+p avg", "p");
  leg_CR_6_2_3->SetTextSize(0.045);
  
  leg_CR_6_2_3->Draw("SAME");
  TLegend *leg_CR_6_2_4 = new TLegend(0.72, 0.22, 1.02, 0.45);
  leg_CR_6_2_4->SetFillColorAlpha(kCyan-10, 0);
  leg_CR_6_2_4->SetLineColorAlpha(0, 0);
  leg_CR_6_2_4->AddEntry(gr_zr_CR_6_2, "Zr+Zr", "p");
  leg_CR_6_2_4->AddEntry(gr_ru_CR_6_2, "Ru+Ru", "p");
  leg_CR_6_2_4->AddEntry(gr_auau_CR_6_2, "Au+Au", "p");
  leg_CR_6_2_4->Draw("SAME");

  gr_pp_CR_5_1_sys->Draw("2 SAME");
  gr_pp_CR_5_1->Draw("P SAME");
  gr_pp_CR_5_1_sys_CBWC->Draw("psame");
  gr_pp_CR_5_1_CBWC->Draw("psame");
  gr_auau_CR_5_1_sys->Draw("2 SAME");
  gr_auau_CR_5_1->Draw("P SAME");
  gr_ru_CR_5_1_sys->Draw("2 SAME");
  gr_ru_CR_5_1->Draw("P SAME");
  gr_zr_CR_5_1_sys->Draw("2 SAME");
  gr_zr_CR_5_1->Draw("P SAME");
  
  p_cr62_2->cd(); p_cr62_2->SetLogx(1); p_cr62_2->SetTickx(1);  p_cr62_2->SetTicky(1); 
  gr_pp_CR_6_2->SetTitle("");
  gr_pp_CR_6_2->Draw("A X goff");
  box_CR_6_2->Draw("SAME");
  box_CR_6_2_lQCD->Draw("SAME");
  box_cr62_frg->Draw("same");
  
  l_CR_6_2_CBWC_ref3_HRG->Draw("SAME");
  

  ya1=-2.5,   ya2=-2.4;
  yru1=-3.5,   yru2=-3.4;
  drawLine(xa1,ya1,xa2,ya1,1,1,7);  drawLine(xa1,ya1,xa1,ya2,1,1,7);  drawLine(xa2,ya1,xa2,ya2,1,1,7);
  drawLine(xa2,ya1,xa3,ya1,1,1,7);  drawLine(xa3,ya1,xa3,ya2,1,1,7); 
  drawLine(xa4,ya1,xa3,ya1,1,1,7);  drawLine(xa4,ya1,xa4,ya2,1,1,7); 
  drawLine(xa4,ya1,xa5,ya1,1,1,7);  drawLine(xa5,ya1,xa5,ya2,1,1,7); 
  drawLine(xa6,ya1,xa5,ya1,1,1,7);  drawLine(xa6,ya1,xa6,ya2,1,1,7);

  drawLine(xru1,yru1,xru2,yru1,1,1,9);  drawLine(xru1,yru1,xru1,yru2,1,1,9);  drawLine(xru2,yru1,xru2,yru2,1,1,9);
  drawLine(xru2,yru1,xru3,yru1,1,1,9);  drawLine(xru3,yru1,xru3,yru2,1,1,9);
  drawLine(xru4,yru1,xru3,yru1,1,1,9);  drawLine(xru4,yru1,xru4,yru2,1,1,9);
  drawLine(xru4,yru1,xru5,yru1,1,1,9);  drawLine(xru5,yru1,xru5,yru2,1,1,9);
  drawLine(xru5,yru1,xru6,yru1,1,1,9);  
  
  
  
  drawLine(xru6,yru1,xru7,yru1,1,1,9);
  drawLine(xru7,yru1,xru8,yru1,1,1,9);
  drawLine(xru8,yru1,xru9,yru1,1,1,9);
  drawLine(xru9,yru1,xru10,yru1,1,1,9);  drawLine(xru10,yru1,xru10,yru2,1,1,9);

  x21 = 6.894-3.993, x22 = 6.894+3.993, y01 = 0.93979;
  double cr62_pythia[1],cr62err_pythia[1];
  cr62_pythia[0] = 0.93979; cr62err_pythia[0] = 0.0030201;
  TGraphErrors *gr_cr62_pythia = new TGraphErrors(1, x_pythia, cr62_pythia, 0, cr62err_pythia); gr_cr62_pythia->SetMarkerStyle(21); gr_cr62_pythia->SetMarkerColor(41); gr_cr62_pythia->SetLineColor(41);  gr_cr62_pythia->SetMarkerSize(1.5);
  gr_cr62_pythia->Draw("psame");


  latex->SetTextSize(0.04);     latex->SetTextFont(42);  latex->SetTextColor(kCyan+2);   latex->SetTextAngle(0);
  latex->DrawLatex(25-13,ya1-0.05,"Au+Au: ");
  latex->SetTextSize(0.04);     latex->SetTextFont(42);  latex->SetTextColor(9);   latex->SetTextAngle(0);
  latex->DrawLatex(25-13-2, yru1-0.05,"Zr#oplusRu: ");

  t_cr62->Draw("SAME");


  gr_pp_CR_6_2_sys->Draw("2 SAME");
  gr_pp_CR_6_2->Draw("P SAME");
  gr_pp_CR_6_2_sys_CBWC->Draw("psame"); gr_pp_CR_6_2_CBWC->Draw("psame");
  gr_auau_CR_6_2_sys->Draw("2 SAME");
  gr_auau_CR_6_2->Draw("P SAME");
  gr_ru_CR_6_2_sys->Draw("2 SAME");
  gr_ru_CR_6_2->Draw("P SAME");
  gr_zr_CR_6_2_sys->Draw("2 SAME");
  gr_zr_CR_6_2->Draw("P SAME");

  Info1_bottommid->Draw("SAME");

  c_CR_3tot_pad_2->cd();
  TPad *p_tit_2 = new TPad("p_tit_2", "p_tit_2", 0.00+0.*1.0/3. + 3 * pad_side_title_buff, 0.0, 0.9, 0.11); p_tit_2->SetFillColorAlpha(0,0); p_tit_2->SetLeftMargin(0.0); p_tit_2->SetRightMargin(0.); p_tit_2->SetTopMargin(0.); p_tit_2->SetBottomMargin(0.);
  TPaveText *pt_tit = new TPaveText(0.235, 0.1, 0.9, 0.9, "NDC NB"); pt_tit->SetFillColorAlpha(0,0);
  pt_tit->AddText("Charged Particle Multiplicity");
  p_tit_2->Draw();
  p_tit_2->cd();
  pt_tit->Draw();
  
  
  if(!scale){
    c_CR_3tot_pad_2->Print("./output/pics/money_plot_noscale.pdf");
    c_CR_3tot_pad_2->Print("./output/pics/money_plot_noscale.png");
  }
  else {
    c_CR_3tot_pad_2->Print("./output/pics/money_plot.pdf");
    c_CR_3tot_pad_2->Print("./output/pics/money_plot.png");
  }
    
  c_buff->Clear();  delete c_buff;
  c_CR_3tot_pad->Clear(); delete c_CR_3tot_pad;
  return;
}
