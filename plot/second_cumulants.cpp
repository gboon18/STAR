const int ncent = 9;
const int mergedN = 2;
const int mergedNau = 4;

void second_cumulants(){

  TFile *f_dat_in = new TFile(Form("output/files/cum_npart_%d.root",0), "read");
  TFile *f_dat_in_c5c6 = new TFile(Form("output/files/cum_npart_%d.root",mergedN), "read");
  TFile *f_urqmd_in = new TFile(Form("model/urqmd_%d.root", 0), "read");
  TFile *f_urqmd_in_au = new TFile(Form("model/urqmd_%d.root", mergedNau), "read");
  TFile *f_urqmd_in_c5c6 = new TFile(Form("model/urqmd_%d.root", mergedN), "read");


  TGraphErrors *gr_dat_c1_dummy = (TGraphErrors*)f_dat_in->Get("gr_npart_c1_dummy");
  TGraphErrors *gr_dat_c2_dummy = (TGraphErrors*)f_dat_in->Get("gr_npart_c2_dummy");
  TGraphErrors *gr_dat_c3_dummy = (TGraphErrors*)f_dat_in->Get("gr_npart_c3_dummy");
  TGraphErrors *gr_dat_c4_dummy = (TGraphErrors*)f_dat_in->Get("gr_npart_c4_dummy");
  TGraphErrors *gr_dat_c5_dummy = (TGraphErrors*)f_dat_in_c5c6->Get("gr_npart_c5_dummy");
  TGraphErrors *gr_dat_c6_dummy = (TGraphErrors*)f_dat_in_c5c6->Get("gr_npart_c6_dummy");
  TGraphErrors *gr_dat_cr21_dummy = (TGraphErrors*)f_dat_in->Get("gr_npart_cr21_dummy"); gr_dat_cr21_dummy->GetXaxis()->SetLimits(-10, 225);
  TGraphErrors *gr_dat_cr32_dummy = (TGraphErrors*)f_dat_in->Get("gr_npart_cr32_dummy"); gr_dat_cr32_dummy->GetXaxis()->SetLimits(-10, 225);
  TGraphErrors *gr_dat_cr42_dummy = (TGraphErrors*)f_dat_in->Get("gr_npart_cr42_dummy"); gr_dat_cr42_dummy->GetXaxis()->SetLimits(-10, 225);
  TGraphErrors *gr_dat_cr51_dummy = (TGraphErrors*)f_dat_in_c5c6->Get("gr_npart_cr51_dummy"); gr_dat_cr51_dummy->GetXaxis()->SetLimits(-10, 225);
  TGraphErrors *gr_dat_cr62_dummy = (TGraphErrors*)f_dat_in_c5c6->Get("gr_npart_cr62_dummy"); gr_dat_cr62_dummy->GetXaxis()->SetLimits(-10, 225);

  TGraphErrors *gr_dat_c1_zr = (TGraphErrors*)f_dat_in->Get("gr_npart_c1_zr"); TGraphErrors *gr_dat_c1_ru = (TGraphErrors*)f_dat_in->Get("gr_npart_c1_ru");
  TGraphErrors *gr_dat_c2_zr = (TGraphErrors*)f_dat_in->Get("gr_npart_c2_zr"); TGraphErrors *gr_dat_c2_ru = (TGraphErrors*)f_dat_in->Get("gr_npart_c2_ru");
  TGraphErrors *gr_dat_c3_zr = (TGraphErrors*)f_dat_in->Get("gr_npart_c3_zr"); TGraphErrors *gr_dat_c3_ru = (TGraphErrors*)f_dat_in->Get("gr_npart_c3_ru");
  TGraphErrors *gr_dat_c4_zr = (TGraphErrors*)f_dat_in->Get("gr_npart_c4_zr"); TGraphErrors *gr_dat_c4_ru = (TGraphErrors*)f_dat_in->Get("gr_npart_c4_ru");
  TGraphErrors *gr_dat_c5_zr = (TGraphErrors*)f_dat_in_c5c6->Get("gr_npart_c5_zr"); TGraphErrors *gr_dat_c5_ru_c5c6 = (TGraphErrors*)f_dat_in->Get("gr_npart_c5_ru");
  TGraphErrors *gr_dat_c6_zr = (TGraphErrors*)f_dat_in_c5c6->Get("gr_npart_c6_zr"); TGraphErrors *gr_dat_c6_ru_c5c6 = (TGraphErrors*)f_dat_in->Get("gr_npart_c6_ru");
  TGraphErrors *gr_dat_cr21_zr = (TGraphErrors*)f_dat_in->Get("gr_npart_cr21_zr"); TGraphErrors *gr_dat_cr21_ru = (TGraphErrors*)f_dat_in->Get("gr_npart_cr21_ru");
  TGraphErrors *gr_dat_cr32_zr = (TGraphErrors*)f_dat_in->Get("gr_npart_cr32_zr"); TGraphErrors *gr_dat_cr32_ru = (TGraphErrors*)f_dat_in->Get("gr_npart_cr32_ru");
  TGraphErrors *gr_dat_cr42_zr = (TGraphErrors*)f_dat_in->Get("gr_npart_cr42_zr"); TGraphErrors *gr_dat_cr42_ru = (TGraphErrors*)f_dat_in->Get("gr_npart_cr42_ru");
  TGraphErrors *gr_dat_cr51_zr = (TGraphErrors*)f_dat_in_c5c6->Get("gr_npart_cr51_zr"); TGraphErrors *gr_dat_cr51_ru = (TGraphErrors*)f_dat_in_c5c6->Get("gr_npart_cr51_ru");
  TGraphErrors *gr_dat_cr62_zr = (TGraphErrors*)f_dat_in_c5c6->Get("gr_npart_cr62_zr"); TGraphErrors *gr_dat_cr62_ru = (TGraphErrors*)f_dat_in_c5c6->Get("gr_npart_cr62_ru");

  TGraphErrors *gr_dat_c1_zr_sys = (TGraphErrors*)f_dat_in->Get("gr_npart_c1_zr_sys"); TGraphErrors *gr_dat_c1_ru_sys = (TGraphErrors*)f_dat_in->Get("gr_npart_c1_ru_sys");
  TGraphErrors *gr_dat_c2_zr_sys = (TGraphErrors*)f_dat_in->Get("gr_npart_c2_zr_sys"); TGraphErrors *gr_dat_c2_ru_sys = (TGraphErrors*)f_dat_in->Get("gr_npart_c2_ru_sys");
  TGraphErrors *gr_dat_c3_zr_sys = (TGraphErrors*)f_dat_in->Get("gr_npart_c3_zr_sys"); TGraphErrors *gr_dat_c3_ru_sys = (TGraphErrors*)f_dat_in->Get("gr_npart_c3_ru_sys");
  TGraphErrors *gr_dat_c4_zr_sys = (TGraphErrors*)f_dat_in->Get("gr_npart_c4_zr_sys"); TGraphErrors *gr_dat_c4_ru_sys = (TGraphErrors*)f_dat_in->Get("gr_npart_c4_ru_sys");
  TGraphErrors *gr_dat_c5_zr_sys = (TGraphErrors*)f_dat_in_c5c6->Get("gr_npart_c5_zr_sys"); TGraphErrors *gr_dat_c5_ru_sys = (TGraphErrors*)f_dat_in_c5c6->Get("gr_npart_c5_ru_sys");
  TGraphErrors *gr_dat_c6_zr_sys = (TGraphErrors*)f_dat_in_c5c6->Get("gr_npart_c6_zr_sys"); TGraphErrors *gr_dat_c6_ru_sys = (TGraphErrors*)f_dat_in_c5c6->Get("gr_npart_c6_ru_sys");
  TGraphErrors *gr_dat_cr21_zr_sys = (TGraphErrors*)f_dat_in->Get("gr_npart_c7_zr_sys"); TGraphErrors *gr_dat_cr21_ru_sys = (TGraphErrors*)f_dat_in->Get("gr_npart_c7_ru_sys");
  TGraphErrors *gr_dat_cr32_zr_sys = (TGraphErrors*)f_dat_in->Get("gr_npart_c9_zr_sys"); TGraphErrors *gr_dat_cr32_ru_sys = (TGraphErrors*)f_dat_in->Get("gr_npart_c9_ru_sys");
  TGraphErrors *gr_dat_cr42_zr_sys = (TGraphErrors*)f_dat_in->Get("gr_npart_c10_zr_sys"); TGraphErrors *gr_dat_cr42_ru_sys = (TGraphErrors*)f_dat_in->Get("gr_npart_c10_ru_sys");
  TGraphErrors *gr_dat_cr51_zr_sys = (TGraphErrors*)f_dat_in_c5c6->Get("gr_npart_c11_zr_sys"); TGraphErrors *gr_dat_cr51_ru_sys = (TGraphErrors*)f_dat_in_c5c6->Get("gr_npart_c11_ru_sys");
  TGraphErrors *gr_dat_cr62_zr_sys = (TGraphErrors*)f_dat_in_c5c6->Get("gr_npart_c12_zr_sys"); TGraphErrors *gr_dat_cr62_ru_sys = (TGraphErrors*)f_dat_in_c5c6->Get("gr_npart_c12_ru_sys");

  TGraphErrors *gr_dat_c1_au = (TGraphErrors*)f_dat_in->Get("gr_npart_c1_au"); TGraphErrors *gr_dat_c1_au_sys = (TGraphErrors*)f_dat_in->Get("gr_npart_c1_au_sys");
  TGraphErrors *gr_dat_c2_au = (TGraphErrors*)f_dat_in->Get("gr_npart_c2_au"); TGraphErrors *gr_dat_c2_au_sys = (TGraphErrors*)f_dat_in->Get("gr_npart_c2_au_sys");
  TGraphErrors *gr_dat_c3_au = (TGraphErrors*)f_dat_in->Get("gr_npart_c3_au"); TGraphErrors *gr_dat_c3_au_sys = (TGraphErrors*)f_dat_in->Get("gr_npart_c3_au_sys");
  TGraphErrors *gr_dat_c4_au = (TGraphErrors*)f_dat_in->Get("gr_npart_c4_au"); TGraphErrors *gr_dat_c4_au_sys = (TGraphErrors*)f_dat_in->Get("gr_npart_c4_au_sys");
  TGraphErrors *gr_dat_cr21_au = (TGraphErrors*)f_dat_in->Get("gr_npart_cr21_au"); TGraphErrors *gr_dat_cr21_au_sys = (TGraphErrors*)f_dat_in->Get("gr_npart_cr21_au_sys");
  TGraphErrors *gr_dat_cr32_au = (TGraphErrors*)f_dat_in->Get("gr_npart_cr32_au"); TGraphErrors *gr_dat_cr32_au_sys = (TGraphErrors*)f_dat_in->Get("gr_npart_cr32_au_sys");
  TGraphErrors *gr_dat_cr42_au = (TGraphErrors*)f_dat_in->Get("gr_npart_cr42_au"); TGraphErrors *gr_dat_cr42_au_sys = (TGraphErrors*)f_dat_in->Get("gr_npart_cr42_au_sys");

  if(mergedNau == 4){
    
    
    gr_dat_cr21_au->SetPoint(4,
			     
			     
			     207, 
			     6.92651 
			     );
    gr_dat_cr21_au->SetPoint(3,
			     -999,
			     -999
			     );
    gr_dat_cr21_au->SetPoint(2,
			     -999,
			     -999
			     );
    gr_dat_cr21_au->SetPoint(1,
			     -999,
			     -999
			     );
    gr_dat_cr21_au->SetPoint(0,
			     -999,
			     -999
			     );
    
    gr_dat_cr21_au->SetPointError(4,
				  0,
				  
				  
				  
				  
				  
				  0.00250938 
				  );
    gr_dat_cr21_au->SetPointError(3,
				  0,
				  gr_dat_cr21_au->GetErrorY(4)
				  );
    gr_dat_cr21_au->SetPointError(2,
				  0,
				  gr_dat_cr21_au->GetErrorY(4)
				  );
    gr_dat_cr21_au->SetPointError(1,
				  0,
				  gr_dat_cr21_au->GetErrorY(4)
				  );
    gr_dat_cr21_au->SetPointError(0,
				  0,
				  gr_dat_cr21_au->GetErrorY(4)
				  );


    gr_dat_cr21_au_sys->SetPoint(4,
				 
				 
				 207, 
				 6.92651 
				 );
    gr_dat_cr21_au_sys->SetPoint(3,
				 -999,
				 -999
				 );
    gr_dat_cr21_au_sys->SetPoint(2,
				 -999,
				 -999
				 );
    gr_dat_cr21_au_sys->SetPoint(1,
				 -999,
				 -999
				 );
    gr_dat_cr21_au_sys->SetPoint(0,
				 -999,
				 -999
				 );
    
    gr_dat_cr21_au_sys->SetPointError(4,
				      0,
				      
				      
				      
				      
				      
				      0.0923046 
				      );
    gr_dat_cr21_au_sys->SetPointError(3,
				      0,
				      gr_dat_cr21_au_sys->GetErrorY(4)
				      );
    gr_dat_cr21_au_sys->SetPointError(2,
				      0,
				      gr_dat_cr21_au_sys->GetErrorY(4)
				      );
    gr_dat_cr21_au_sys->SetPointError(1,
				      0,
				      gr_dat_cr21_au_sys->GetErrorY(4)
				      );
    gr_dat_cr21_au_sys->SetPointError(0,
				      0,
				      gr_dat_cr21_au_sys->GetErrorY(4)
				      );

    
				       
    gr_dat_cr32_au->SetPoint(4,
			     
			     
			     207, 
			     0.124356 
			     );
    gr_dat_cr32_au->SetPoint(3,
			     -999,
			     -999
			     );
    gr_dat_cr32_au->SetPoint(2,
			     -999,
			     -999
			     );
    gr_dat_cr32_au->SetPoint(1,
			     -999,
			     -999
			     );
    gr_dat_cr32_au->SetPoint(0,
			     -999,
			     -999
			     );
    
    gr_dat_cr32_au->SetPointError(4,
				  0,
				  
				  
				  
				  
				  
				  0.00283313 
				  );
    gr_dat_cr32_au->SetPointError(3,
				  0,
				  gr_dat_cr32_au->GetErrorY(4)
				  );
    gr_dat_cr32_au->SetPointError(2,
				  0,
				  gr_dat_cr32_au->GetErrorY(4)
				  );
    gr_dat_cr32_au->SetPointError(1,
				  0,
				  gr_dat_cr32_au->GetErrorY(4)
				  );
    gr_dat_cr32_au->SetPointError(0,
				  0,
				  gr_dat_cr32_au->GetErrorY(4)
				  );


    gr_dat_cr32_au_sys->SetPoint(4,
				 
				 
				 207, 
				 0.124356 
				 );
    gr_dat_cr32_au_sys->SetPoint(3,
				 -999,
				 -999
				 );
    gr_dat_cr32_au_sys->SetPoint(2,
				 -999,
				 -999
				 );
    gr_dat_cr32_au_sys->SetPoint(1,
				 -999,
				 -999
				 );
    gr_dat_cr32_au_sys->SetPoint(0,
				 -999,
				 -999
				 );
    
    gr_dat_cr32_au_sys->SetPointError(4,
				      0,
				      
				      
				      
				      
				      
				      0.00603565 
				      );
    gr_dat_cr32_au_sys->SetPointError(3,
				      0,
				      gr_dat_cr32_au_sys->GetErrorY(4)
				      );
    gr_dat_cr32_au_sys->SetPointError(2,
				      0,
				      gr_dat_cr32_au_sys->GetErrorY(4)
				      );
    gr_dat_cr32_au_sys->SetPointError(1,
				      0,
				      gr_dat_cr32_au_sys->GetErrorY(4)
				      );
    gr_dat_cr32_au_sys->SetPointError(0,
				      0,
				      gr_dat_cr32_au_sys->GetErrorY(4)
				      );

    
    gr_dat_cr42_au->SetPoint(4,
			     
			     
			     207, 
			     0.823374
			     );
    gr_dat_cr42_au->SetPoint(3,
			     -999,
			     -999
			     );
    gr_dat_cr42_au->SetPoint(2,
			     -999,
			     -999
			     );
    gr_dat_cr42_au->SetPoint(1,
			     -999,
			     -999
			     );
    gr_dat_cr42_au->SetPoint(0,
			     -999,
			     -999
			     );
    
    gr_dat_cr42_au->SetPointError(4,
				  0,
				  
				  
				  
				  
				  
				  0.0397841
				  );
    gr_dat_cr42_au->SetPointError(3,
				  0,
				  gr_dat_cr42_au->GetErrorY(4)
				  );
    gr_dat_cr42_au->SetPointError(2,
				  0,
				  gr_dat_cr42_au->GetErrorY(4)
				  );
    gr_dat_cr42_au->SetPointError(1,
				  0,
				  gr_dat_cr42_au->GetErrorY(4)
				  );
    gr_dat_cr42_au->SetPointError(0,
				  0,
				  gr_dat_cr42_au->GetErrorY(4)
				  );


    gr_dat_cr42_au_sys->SetPoint(4,
				 
				 
				 207, 
				 0.823374
				 );
    gr_dat_cr42_au_sys->SetPoint(3,
				 -999,
				 -999
				 );
    gr_dat_cr42_au_sys->SetPoint(2,
				 -999,
				 -999
				 );
    gr_dat_cr42_au_sys->SetPoint(1,
				 -999,
				 -999
				 );
    gr_dat_cr42_au_sys->SetPoint(0,
				 -999,
				 -999
				 );
    
    gr_dat_cr42_au_sys->SetPointError(4,
				      0,
				      
				      
				      
				      
				      
				      0.0697127
				      );
    gr_dat_cr42_au_sys->SetPointError(3,
				      0,
				      gr_dat_cr42_au_sys->GetErrorY(4)
				      );
    gr_dat_cr42_au_sys->SetPointError(2,
				      0,
				      gr_dat_cr42_au_sys->GetErrorY(4)
				      );
    gr_dat_cr42_au_sys->SetPointError(1,
				      0,
				      gr_dat_cr42_au_sys->GetErrorY(4)
				      );
    gr_dat_cr42_au_sys->SetPointError(0,
				      0,
				      gr_dat_cr42_au_sys->GetErrorY(4)
				      );

  }

  TGraphErrors *gr_urqmd_c1_zr = (TGraphErrors*)f_urqmd_in->Get("gr_urqmd_c1_zr"); TGraphErrors *gr_urqmd_c1_ru = (TGraphErrors*)f_urqmd_in->Get("gr_urqmd_c1_ru");
  TGraphErrors *gr_urqmd_c2_zr = (TGraphErrors*)f_urqmd_in->Get("gr_urqmd_c2_zr"); TGraphErrors *gr_urqmd_c2_ru = (TGraphErrors*)f_urqmd_in->Get("gr_urqmd_c2_ru");
  TGraphErrors *gr_urqmd_c3_zr = (TGraphErrors*)f_urqmd_in->Get("gr_urqmd_c3_zr"); TGraphErrors *gr_urqmd_c3_ru = (TGraphErrors*)f_urqmd_in->Get("gr_urqmd_c3_ru");
  TGraphErrors *gr_urqmd_c4_zr = (TGraphErrors*)f_urqmd_in->Get("gr_urqmd_c4_zr"); TGraphErrors *gr_urqmd_c4_ru = (TGraphErrors*)f_urqmd_in->Get("gr_urqmd_c4_ru");
  TGraphErrors *gr_urqmd_c5_zr = (TGraphErrors*)f_urqmd_in_c5c6->Get("gr_urqmd_c5_zr"); TGraphErrors *gr_urqmd_c5_ru = (TGraphErrors*)f_urqmd_in_c5c6->Get("gr_urqmd_c5_ru");
  TGraphErrors *gr_urqmd_c6_zr = (TGraphErrors*)f_urqmd_in_c5c6->Get("gr_urqmd_c6_zr"); TGraphErrors *gr_urqmd_c6_ru = (TGraphErrors*)f_urqmd_in_c5c6->Get("gr_urqmd_c6_ru");
  TGraphErrors *gr_urqmd_cr21_zr = (TGraphErrors*)f_urqmd_in->Get("gr_urqmd_cr21_zr"); TGraphErrors *gr_urqmd_cr21_ru = (TGraphErrors*)f_urqmd_in->Get("gr_urqmd_cr21_ru");
  TGraphErrors *gr_urqmd_cr32_zr = (TGraphErrors*)f_urqmd_in->Get("gr_urqmd_cr32_zr"); TGraphErrors *gr_urqmd_cr32_ru = (TGraphErrors*)f_urqmd_in->Get("gr_urqmd_cr32_ru");
  TGraphErrors *gr_urqmd_cr42_zr = (TGraphErrors*)f_urqmd_in->Get("gr_urqmd_cr42_zr"); TGraphErrors *gr_urqmd_cr42_ru = (TGraphErrors*)f_urqmd_in->Get("gr_urqmd_cr42_ru");
  TGraphErrors *gr_urqmd_cr51_zr = (TGraphErrors*)f_urqmd_in_c5c6->Get("gr_urqmd_cr51_zr"); TGraphErrors *gr_urqmd_cr51_ru = (TGraphErrors*)f_urqmd_in_c5c6->Get("gr_urqmd_cr51_ru");
  TGraphErrors *gr_urqmd_cr62_zr = (TGraphErrors*)f_urqmd_in_c5c6->Get("gr_urqmd_cr62_zr"); TGraphErrors *gr_urqmd_cr62_ru = (TGraphErrors*)f_urqmd_in_c5c6->Get("gr_urqmd_cr62_ru");

  TGraphErrors *gr_urqmd_c1_au = (TGraphErrors*)f_urqmd_in_au->Get("gr_urqmd_c1_au");
  TGraphErrors *gr_urqmd_c2_au = (TGraphErrors*)f_urqmd_in_au->Get("gr_urqmd_c2_au");
  TGraphErrors *gr_urqmd_c3_au = (TGraphErrors*)f_urqmd_in_au->Get("gr_urqmd_c3_au");
  TGraphErrors *gr_urqmd_c4_au = (TGraphErrors*)f_urqmd_in_au->Get("gr_urqmd_c4_au");
  TGraphErrors *gr_urqmd_cr21_au = (TGraphErrors*)f_urqmd_in_au->Get("gr_urqmd_cr21_au");
  TGraphErrors *gr_urqmd_cr32_au = (TGraphErrors*)f_urqmd_in_au->Get("gr_urqmd_cr32_au");
  TGraphErrors *gr_urqmd_cr42_au = (TGraphErrors*)f_urqmd_in_au->Get("gr_urqmd_cr42_au");
  TGraphErrors *gr_urqmd_cr51_au = (TGraphErrors*)f_urqmd_in_au->Get("gr_urqmd_cr51_au");
  TGraphErrors *gr_urqmd_cr62_au = (TGraphErrors*)f_urqmd_in_au->Get("gr_urqmd_cr62_au");
  
  
  
  
  
  
  
  
  
  
  
  

  
  
  
  
  
  
  


  

  
  
  
  
  
  
  
  
  
  
  
  

  gr_dat_c1_zr_sys->SetFillStyle(3001); gr_dat_c1_zr_sys->SetFillColorAlpha(kOrange-6, 0.7); gr_dat_c1_ru_sys->SetFillStyle(3001); gr_dat_c1_ru_sys->SetFillColorAlpha(kCyan+3, 0.7);
  gr_dat_c2_zr_sys->SetFillStyle(3001); gr_dat_c2_zr_sys->SetFillColorAlpha(kOrange-6, 0.7); gr_dat_c2_ru_sys->SetFillStyle(3001); gr_dat_c2_ru_sys->SetFillColorAlpha(kCyan+3, 0.7);
  gr_dat_c3_zr_sys->SetFillStyle(3001); gr_dat_c3_zr_sys->SetFillColorAlpha(kOrange-6, 0.7); gr_dat_c3_ru_sys->SetFillStyle(3001); gr_dat_c3_ru_sys->SetFillColorAlpha(kCyan+3, 0.7);
  gr_dat_c4_zr_sys->SetFillStyle(3001); gr_dat_c4_zr_sys->SetFillColorAlpha(kOrange-6, 0.7); gr_dat_c4_ru_sys->SetFillStyle(3001); gr_dat_c4_ru_sys->SetFillColorAlpha(kCyan+3, 0.7);
  gr_dat_c5_zr_sys->SetFillStyle(3001); gr_dat_c5_zr_sys->SetFillColorAlpha(kOrange-6, 0.7); gr_dat_c5_ru_sys->SetFillStyle(3001); gr_dat_c5_ru_sys->SetFillColorAlpha(kCyan+3, 0.7);
  gr_dat_c6_zr_sys->SetFillStyle(3001); gr_dat_c6_zr_sys->SetFillColorAlpha(kOrange-6, 0.7); gr_dat_c6_ru_sys->SetFillStyle(3001); gr_dat_c6_ru_sys->SetFillColorAlpha(kCyan+3, 0.7);
  gr_dat_cr21_zr_sys->SetFillStyle(3001); gr_dat_cr21_zr_sys->SetFillColorAlpha(kOrange-6, 0.7); gr_dat_cr21_ru_sys->SetFillStyle(3001); gr_dat_cr21_ru_sys->SetFillColorAlpha(kCyan+3, 0.7);
  gr_dat_cr32_zr_sys->SetFillStyle(3001); gr_dat_cr32_zr_sys->SetFillColorAlpha(kOrange-6, 0.7); gr_dat_cr32_ru_sys->SetFillStyle(3001); gr_dat_cr32_ru_sys->SetFillColorAlpha(kCyan+3, 0.7);
  gr_dat_cr42_zr_sys->SetFillStyle(3001); gr_dat_cr42_zr_sys->SetFillColorAlpha(kOrange-6, 0.7); gr_dat_cr42_ru_sys->SetFillStyle(3001); gr_dat_cr42_ru_sys->SetFillColorAlpha(kCyan+3, 0.7);
  gr_dat_cr51_zr_sys->SetFillStyle(3001); gr_dat_cr51_zr_sys->SetFillColorAlpha(kOrange-6, 0.7); gr_dat_cr51_ru_sys->SetFillStyle(3001); gr_dat_cr51_ru_sys->SetFillColorAlpha(kCyan+3, 0.7);
  gr_dat_cr62_zr_sys->SetFillStyle(3001); gr_dat_cr62_zr_sys->SetFillColorAlpha(kOrange-6, 0.7); gr_dat_cr62_ru_sys->SetFillStyle(3001); gr_dat_cr62_ru_sys->SetFillColorAlpha(kCyan+3, 0.7);

  gr_dat_c1_au->SetLineColorAlpha(kRed, 1.0);
  gr_dat_c2_au->SetLineColorAlpha(kRed, 1.0);
  gr_dat_c3_au->SetLineColorAlpha(kRed, 1.0);
  gr_dat_c4_au->SetLineColorAlpha(kRed, 1.0);
  gr_dat_cr21_au->SetLineColorAlpha(kRed, 1.0);
  gr_dat_cr32_au->SetLineColorAlpha(kRed, 1.0);
  gr_dat_cr42_au->SetLineColorAlpha(kRed, 1.0);
  
  gr_dat_c1_au_sys->SetFillStyle(3000); gr_dat_c1_au_sys->SetLineWidth(4);
  gr_dat_c1_au_sys->SetFillColorAlpha(kRed-3, 0.3); gr_dat_c1_au_sys->SetLineColorAlpha(kRed-3, 0.3);
  gr_dat_c2_au_sys->SetFillStyle(3000); gr_dat_c2_au_sys->SetLineWidth(4);
  gr_dat_c2_au_sys->SetFillColorAlpha(kRed-3, 0.3); gr_dat_c2_au_sys->SetLineColorAlpha(kRed-3, 0.3);
  gr_dat_c3_au_sys->SetFillStyle(3000); gr_dat_c3_au_sys->SetLineWidth(4);
  gr_dat_c3_au_sys->SetFillColorAlpha(kRed-3, 0.3); gr_dat_c3_au_sys->SetLineColorAlpha(kRed-3, 0.3);
  gr_dat_c4_au_sys->SetFillStyle(3000); gr_dat_c4_au_sys->SetLineWidth(4);
  gr_dat_c4_au_sys->SetFillColorAlpha(kRed-3, 0.3); gr_dat_c4_au_sys->SetLineColorAlpha(kRed-3, 0.3);
  gr_dat_cr21_au_sys->SetFillStyle(3000); gr_dat_cr21_au_sys->SetLineWidth(4);
  gr_dat_cr21_au_sys->SetFillColorAlpha(kRed-3, 0.3); gr_dat_cr21_au_sys->SetLineColorAlpha(kRed-3, 0.3);
  gr_dat_cr32_au_sys->SetFillStyle(3000); gr_dat_cr32_au_sys->SetLineWidth(4);
  gr_dat_cr32_au_sys->SetFillColorAlpha(kRed-3, 0.3); gr_dat_cr32_au_sys->SetLineColorAlpha(kRed-3, 0.3);
  gr_dat_cr42_au_sys->SetFillStyle(3000); gr_dat_cr42_au_sys->SetLineWidth(4);
  gr_dat_cr42_au_sys->SetFillColorAlpha(kRed-3, 0.3); gr_dat_cr42_au_sys->SetLineColorAlpha(kRed-3, 0.3);

  TGraphErrors *gr_dat_cr21_au_sys_draw = new TGraphErrors(ncent-mergedNau);
  TGraphErrors *gr_dat_cr32_au_sys_draw = new TGraphErrors(ncent-mergedNau);
  TGraphErrors *gr_dat_cr42_au_sys_draw = new TGraphErrors(ncent-mergedNau);
  for(int i_cent = 0+mergedNau ; i_cent < ncent ; i_cent++){
    gr_dat_cr21_au_sys_draw->SetPoint(i_cent-mergedNau,
				      gr_dat_cr21_au_sys->GetPointX(i_cent),
				      gr_dat_cr21_au_sys->GetPointY(i_cent)
				      );
    gr_dat_cr21_au_sys_draw->SetPointError(i_cent-mergedNau,
					   0,
					   gr_dat_cr21_au_sys->GetErrorY(i_cent)
					   );
    gr_dat_cr32_au_sys_draw->SetPoint(i_cent-mergedNau,
				      gr_dat_cr32_au_sys->GetPointX(i_cent),
				      gr_dat_cr32_au_sys->GetPointY(i_cent)
				      );
    gr_dat_cr32_au_sys_draw->SetPointError(i_cent-mergedNau,
					   0,
					   gr_dat_cr32_au_sys->GetErrorY(i_cent)
					   );
    gr_dat_cr42_au_sys_draw->SetPoint(i_cent-mergedNau,
				      gr_dat_cr42_au_sys->GetPointX(i_cent),
				      gr_dat_cr42_au_sys->GetPointY(i_cent)
				      );
    gr_dat_cr42_au_sys_draw->SetPointError(i_cent-mergedNau,
					   0,
					   gr_dat_cr42_au_sys->GetErrorY(i_cent)
					   );
  }
  gr_dat_cr21_au_sys_draw->SetMarkerStyle(26); gr_dat_cr21_au_sys_draw->SetMarkerColor(kRed); gr_dat_cr21_au_sys_draw->SetMarkerSize(1.5); gr_dat_cr21_au_sys_draw->SetLineColorAlpha(kRed-3, 0.35); gr_dat_cr21_au_sys_draw->SetFillColorAlpha(kRed-3, 0.3); gr_dat_cr21_au_sys_draw->SetFillStyle(3000); gr_dat_cr21_au_sys_draw->SetLineWidth(7);
  gr_dat_cr32_au_sys_draw->SetMarkerStyle(26); gr_dat_cr32_au_sys_draw->SetMarkerColor(kRed); gr_dat_cr32_au_sys_draw->SetMarkerSize(1.5); gr_dat_cr32_au_sys_draw->SetLineColorAlpha(kRed-3, 0.35); gr_dat_cr32_au_sys_draw->SetFillColorAlpha(kRed-3, 0.3); gr_dat_cr32_au_sys_draw->SetFillStyle(3000); gr_dat_cr32_au_sys_draw->SetLineWidth(7);
  gr_dat_cr42_au_sys_draw->SetMarkerStyle(26); gr_dat_cr42_au_sys_draw->SetMarkerColor(kRed); gr_dat_cr42_au_sys_draw->SetMarkerSize(1.5); gr_dat_cr42_au_sys_draw->SetLineColorAlpha(kRed-3, 0.35); gr_dat_cr42_au_sys_draw->SetFillColorAlpha(kRed-3, 0.3); gr_dat_cr42_au_sys_draw->SetFillStyle(3000); gr_dat_cr42_au_sys_draw->SetLineWidth(7);

  gr_urqmd_c1_zr->SetFillStyle(3001); gr_urqmd_c1_zr->SetFillColorAlpha(kOrange, 0.5); gr_urqmd_c1_ru->SetFillStyle(3001); gr_urqmd_c1_ru->SetFillColorAlpha(kCyan, 0.5);
  gr_urqmd_c2_zr->SetFillStyle(3001); gr_urqmd_c2_zr->SetFillColorAlpha(kOrange, 0.5); gr_urqmd_c2_ru->SetFillStyle(3001); gr_urqmd_c2_ru->SetFillColorAlpha(kCyan, 0.5);
  gr_urqmd_c3_zr->SetFillStyle(3001); gr_urqmd_c3_zr->SetFillColorAlpha(kOrange, 0.5); gr_urqmd_c3_ru->SetFillStyle(3001); gr_urqmd_c3_ru->SetFillColorAlpha(kCyan, 0.5);
  gr_urqmd_c4_zr->SetFillStyle(3001); gr_urqmd_c4_zr->SetFillColorAlpha(kOrange, 0.5); gr_urqmd_c4_ru->SetFillStyle(3001); gr_urqmd_c4_ru->SetFillColorAlpha(kCyan, 0.5);
  gr_urqmd_c5_zr->SetFillStyle(3001); gr_urqmd_c5_zr->SetFillColorAlpha(kOrange, 0.5); gr_urqmd_c5_ru->SetFillStyle(3001); gr_urqmd_c5_ru->SetFillColorAlpha(kCyan, 0.5);
  gr_urqmd_c6_zr->SetFillStyle(3001); gr_urqmd_c6_zr->SetFillColorAlpha(kOrange, 0.5); gr_urqmd_c6_ru->SetFillStyle(3001); gr_urqmd_c6_ru->SetFillColorAlpha(kCyan, 0.5);
  gr_urqmd_cr21_zr->SetFillStyle(3001); gr_urqmd_cr21_zr->SetFillColorAlpha(kOrange, 0.5); gr_urqmd_cr21_ru->SetFillStyle(3001); gr_urqmd_cr21_ru->SetFillColorAlpha(kCyan, 0.5);
  gr_urqmd_cr32_zr->SetFillStyle(3001); gr_urqmd_cr32_zr->SetFillColorAlpha(kOrange, 0.5); gr_urqmd_cr32_ru->SetFillStyle(3001); gr_urqmd_cr32_ru->SetFillColorAlpha(kCyan, 0.5);
  gr_urqmd_cr42_zr->SetFillStyle(3001); gr_urqmd_cr42_zr->SetFillColorAlpha(kOrange, 0.5); gr_urqmd_cr42_ru->SetFillStyle(3001); gr_urqmd_cr42_ru->SetFillColorAlpha(kCyan, 0.5);
  gr_urqmd_cr51_zr->SetFillStyle(3001); gr_urqmd_cr51_zr->SetFillColorAlpha(kOrange, 0.5); gr_urqmd_cr51_ru->SetFillStyle(3001); gr_urqmd_cr51_ru->SetFillColorAlpha(kCyan, 0.5);
  gr_urqmd_cr62_zr->SetFillStyle(3001); gr_urqmd_cr62_zr->SetFillColorAlpha(kOrange, 0.5); gr_urqmd_cr62_ru->SetFillStyle(3001); gr_urqmd_cr62_ru->SetFillColorAlpha(kCyan, 0.5);
  gr_urqmd_c1_au->SetFillStyle(3001); gr_urqmd_c1_au->SetFillColorAlpha(kRed, 0.5);
  gr_urqmd_c2_au->SetFillStyle(3001); gr_urqmd_c2_au->SetFillColorAlpha(kRed, 0.5);
  gr_urqmd_c3_au->SetFillStyle(3001); gr_urqmd_c3_au->SetFillColorAlpha(kRed, 0.5);
  gr_urqmd_c4_au->SetFillStyle(3001); gr_urqmd_c4_au->SetFillColorAlpha(kRed, 0.5);
  gr_urqmd_cr21_au->SetFillStyle(3001); gr_urqmd_cr21_au->SetFillColorAlpha(kRed, 0.5);
  gr_urqmd_cr32_au->SetFillStyle(3001); gr_urqmd_cr32_au->SetFillColorAlpha(kRed, 0.5);
  gr_urqmd_cr42_au->SetFillStyle(3001); gr_urqmd_cr42_au->SetFillColorAlpha(kRed, 0.5);
  gr_urqmd_cr51_au->SetFillStyle(3001); gr_urqmd_cr51_au->SetFillColorAlpha(kRed, 0.5);
  gr_urqmd_cr62_au->SetFillStyle(3001); gr_urqmd_cr62_au->SetFillColorAlpha(kRed, 0.5);
  
  gr_dat_cr21_dummy->GetYaxis()->SetLabelSize(0.1); gr_dat_cr21_dummy->GetYaxis()->SetLabelOffset(0.0125); gr_dat_cr21_dummy->GetYaxis()->SetNdivisions(505);
  gr_dat_cr32_dummy->GetYaxis()->SetLabelSize(0.1); gr_dat_cr32_dummy->GetYaxis()->SetLabelOffset(0.0125); gr_dat_cr32_dummy->GetYaxis()->SetNdivisions(505);
  gr_dat_cr42_dummy->GetYaxis()->SetLabelSize(0.09); gr_dat_cr42_dummy->GetYaxis()->SetLabelOffset(0.0125); gr_dat_cr42_dummy->GetYaxis()->SetNdivisions(505);

  gr_dat_cr51_dummy->GetYaxis()->SetLabelSize(0.1); gr_dat_cr51_dummy->GetYaxis()->SetLabelOffset(0.0125); gr_dat_cr51_dummy->GetYaxis()->SetNdivisions(505);
  gr_dat_cr62_dummy->GetYaxis()->SetLabelSize(0.09); gr_dat_cr62_dummy->GetYaxis()->SetLabelOffset(0.0125); gr_dat_cr62_dummy->GetYaxis()->SetNdivisions(505);

  
  
  

  gr_dat_cr42_dummy->GetXaxis()->SetTitle(""); gr_dat_cr42_dummy->GetXaxis()->SetLabelSize(0.1); gr_dat_cr42_dummy->GetXaxis()->SetLabelOffset(0.012); gr_dat_cr42_dummy->GetXaxis()->SetNdivisions(505);
  gr_dat_cr62_dummy->GetXaxis()->SetTitle(""); gr_dat_cr62_dummy->GetXaxis()->SetLabelSize(0.1); gr_dat_cr62_dummy->GetXaxis()->SetLabelOffset(0.012); gr_dat_cr62_dummy->GetXaxis()->SetNdivisions(505);
  


  gr_dat_cr21_dummy->SetTitle("");
  gr_dat_cr32_dummy->SetTitle("");
  gr_dat_cr42_dummy->SetTitle("");
  gr_dat_cr51_dummy->SetTitle("");
  gr_dat_cr62_dummy->SetTitle("");
  
  

  if(mergedNau == 0){
    gr_dat_cr21_dummy->GetYaxis()->SetRangeUser(3.1, 8.99);
    
    
    gr_dat_cr32_dummy->GetYaxis()->SetRangeUser(0.051, 0.32);
    gr_dat_cr42_dummy->GetYaxis()->SetRangeUser(0.41, 1.35);
    gr_dat_cr51_dummy->GetYaxis()->SetRangeUser(-1.9, 5);
    gr_dat_cr62_dummy->GetYaxis()->SetRangeUser(-7.9, 12);
  }
  if(mergedNau == 4){
    gr_dat_cr21_dummy->GetYaxis()->SetRangeUser(3.6, 9.7);
    
    
    gr_dat_cr32_dummy->GetYaxis()->SetRangeUser(0.051, 0.32);
    gr_dat_cr42_dummy->GetYaxis()->SetRangeUser(0.61, 1.09);
    
    gr_dat_cr51_dummy->GetYaxis()->SetRangeUser(-2.8, 3.4);
    gr_dat_cr62_dummy->GetYaxis()->SetRangeUser(-7.9, 6.1);
  }

  
  double pad_side_title_buff = 0.04;
  double pad_bottom_buff = 0.1;
  double bottom_axis_margin = 0.02;
  TCanvas *c_cr_2 = new TCanvas("c_cr_2", "c_cr_2", 1100, 1000); c_cr_2->cd();
  TPad *p_cr21_2     = new TPad("p_cr21_2",     "p_cr21_2",                      0.01 + 2 * pad_side_title_buff, 2 * (1 - 0.01 - pad_bottom_buff) / 3 + pad_bottom_buff + bottom_axis_margin/2, 0.50 + pad_side_title_buff, 0.99); p_cr21_2->Draw();
  p_cr21_2->SetTopMargin(0); p_cr21_2->SetBottomMargin(0); p_cr21_2->SetLeftMargin(0.1); p_cr21_2->SetRightMargin(0.07);
  TPad *p_cr21_urqmd_2     = new TPad("p_cr21_urqmd_2",     "p_cr21_urqmd_2",                      0.50 + pad_side_title_buff, 2 * (1 - 0.01 - pad_bottom_buff) / 3 + pad_bottom_buff + bottom_axis_margin/2, 0.99, 0.99); p_cr21_urqmd_2->Draw();

  TPad *p_cr21     = new TPad("p_cr21",     "p_cr21",                      0.01 + 2 * pad_side_title_buff, 2 * (1 - 0.01 - pad_bottom_buff) / 3 + pad_bottom_buff + bottom_axis_margin/2, 0.50 + pad_side_title_buff, 0.99); p_cr21->Draw();
  TPad *p_cr32     = new TPad("p_cr32",     "p_cr32",                      0.01 + 2 * pad_side_title_buff, 1 * (1 - 0.01 - pad_bottom_buff) / 3 + pad_bottom_buff + bottom_axis_margin, 0.50 + pad_side_title_buff, 2 * (1 - 0.01 - pad_bottom_buff) / 3 + pad_bottom_buff + bottom_axis_margin/2); p_cr32->Draw();
  TPad *p_cr42     = new TPad("p_cr42",     "p_cr42",                      0.01 + 2 * pad_side_title_buff, 0 * (1 - 0.01 - pad_bottom_buff) / 3 + pad_bottom_buff, 0.50 + pad_side_title_buff, 1 * (1 - 0.01 - pad_bottom_buff) / 3 + pad_bottom_buff + bottom_axis_margin); p_cr42->Draw();
  TPad *p_cr51     = new TPad("p_cr51",     "p_cr51",                      0.50 + pad_side_title_buff, 1 * (1 - 0.01 - pad_bottom_buff) / 3 + pad_bottom_buff + bottom_axis_margin/2, 0.99, 2 * (1 - 0.01 - pad_bottom_buff) / 3 + pad_bottom_buff + bottom_axis_margin/2); p_cr51->Draw();
  TPad *p_cr62     = new TPad("p_cr62",     "p_cr62",                      0.50 + pad_side_title_buff, 0 * (1 - 0.01 - pad_bottom_buff) / 3 + pad_bottom_buff, 0.99, 1 * (1 - 0.01 - pad_bottom_buff) / 3 + pad_bottom_buff + bottom_axis_margin); p_cr62->Draw();

  TPad *p_tit_left = new TPad("p_tit_left","p_tit_left", 0.01, 0.01, 0.50, 0 * (1 - 0.01 - pad_bottom_buff) / 3 + pad_bottom_buff); p_tit_left->Draw();
  TPad *p_tit_right = new TPad("p_tit_right","p_tit_right", 0.50, 0.01, 0.99, 0 * (1 - 0.01 - pad_bottom_buff) / 3 + pad_bottom_buff); p_tit_right->Draw();
  TPad *p_tit_mid = new TPad("p_tit_mid","p_tit_mid", 0.01 + pad_side_title_buff, 0.01, 0.99, 0 * (1 - 0.01 - pad_bottom_buff) / 3 + pad_bottom_buff); p_tit_mid->Draw();

  p_cr21->SetTopMargin(0); p_cr21->SetBottomMargin(0); p_cr21->SetLeftMargin(0.1); p_cr21->SetRightMargin(0.07);
  p_cr32->SetTopMargin(0); p_cr32->SetBottomMargin(0); p_cr32->SetLeftMargin(0.1); p_cr32->SetRightMargin(0.07);
  p_cr42->SetTopMargin(0); p_cr42->SetBottomMargin(0.1); p_cr42->SetLeftMargin(0.1); p_cr42->SetRightMargin(0.07);
  
  p_cr51->SetTopMargin(0); p_cr51->SetBottomMargin(0); p_cr51->SetLeftMargin(0.07); p_cr51->SetRightMargin(0.1);
  p_cr62->SetTopMargin(0); p_cr62->SetBottomMargin(0.1); p_cr62->SetLeftMargin(0.07); p_cr62->SetRightMargin(0.1);

  p_cr21->cd();
  gr_dat_cr21_dummy->Draw("ap"); 
  gr_urqmd_cr21_au->Draw("3 same");  gr_urqmd_cr21_zr->Draw("3 same"); gr_urqmd_cr21_ru->Draw("3 same");
  gr_dat_cr21_au_sys_draw->Draw("2 same");
  gr_dat_cr21_au->Draw("psame"); gr_dat_cr21_zr_sys->Draw("2 same"); gr_dat_cr21_zr->Draw("p same"); gr_dat_cr21_ru_sys->Draw("2 same"); gr_dat_cr21_ru->Draw("p same");

  p_cr32->cd();
  gr_dat_cr32_dummy->Draw("ap"); 
  gr_urqmd_cr32_au->Draw("3 same");  gr_urqmd_cr32_zr->Draw("3 same"); gr_urqmd_cr32_ru->Draw("3 same");
  
  gr_dat_cr32_au_sys_draw->Draw("2 same");
  gr_dat_cr32_au->Draw("psame"); gr_dat_cr32_zr_sys->Draw("2 same"); gr_dat_cr32_zr->Draw("p same"); gr_dat_cr32_ru_sys->Draw("2 same"); gr_dat_cr32_ru->Draw("p same");
  p_cr42->cd();
  gr_dat_cr42_dummy->Draw("ap"); 
  gr_urqmd_cr42_au->Draw("3 same");  gr_urqmd_cr42_zr->Draw("3 same"); gr_urqmd_cr42_ru->Draw("3 same");
  
  gr_dat_cr42_au_sys_draw->Draw("2 same");
  gr_dat_cr42_au->Draw("psame"); gr_dat_cr42_zr_sys->Draw("2 same"); gr_dat_cr42_zr->Draw("p same"); gr_dat_cr42_ru_sys->Draw("2 same"); gr_dat_cr42_ru->Draw("p same");
  p_cr51->cd();
  gr_dat_cr51_dummy->Draw("ap");
  gr_urqmd_cr51_au->Draw("3 same"); gr_urqmd_cr51_zr->Draw("3 same"); gr_urqmd_cr51_ru->Draw("3 same");
  
  p_cr62->cd();
  gr_dat_cr62_dummy->Draw("ap");
  gr_urqmd_cr62_au->Draw("3 same"); gr_urqmd_cr62_zr->Draw("3 same"); gr_urqmd_cr62_ru->Draw("3 same");
  
  double npart_cr51[ncent-mergedNau], cr51_cr51[ncent-mergedNau], cr51_cr51_sta[ncent-mergedNau], cr51_cr51_sys[ncent-mergedNau];
  npart_cr51[0] =  gr_dat_cr42_au->GetPointX(4); 
  npart_cr51[1] = gr_dat_cr42_au->GetPointX(5);
  npart_cr51[2] = gr_dat_cr42_au->GetPointX(6);;
  npart_cr51[3] = gr_dat_cr42_au->GetPointX(7);;
  npart_cr51[4] = gr_dat_cr42_au->GetPointX(8);;
  
  cr51_cr51[0] = -0.35823; cr51_cr51_sta[0] = 1.64457; cr51_cr51_sys[0] = 2.040898;
  cr51_cr51[1] = -0.394257; cr51_cr51_sta[1] = 0.414392; cr51_cr51_sys[1] = 0.333806;
  cr51_cr51[2] = 0.0953091; cr51_cr51_sta[2] = 0.205011; cr51_cr51_sys[2] = 0.122779;
  cr51_cr51[3] = 0.370974; cr51_cr51_sta[3] = 0.106474; cr51_cr51_sys[3] = 0.057323;
  cr51_cr51[4] = 0.382616; cr51_cr51_sta[4] = 0.0635642; cr51_cr51_sys[4] = 0.0444453;

  TGraphErrors *gr_cr51_cr51     = new TGraphErrors(ncent-mergedNau, npart_cr51, cr51_cr51, 0, cr51_cr51_sta);
  gr_cr51_cr51->SetMarkerStyle(26); gr_cr51_cr51->SetMarkerColor(kRed); gr_cr51_cr51->SetLineColor(kRed); gr_cr51_cr51->SetMarkerSize(1.5); 

  TGraphErrors *gr_cr51_cr51_sys = new TGraphErrors(ncent-mergedNau, npart_cr51, cr51_cr51, 0, cr51_cr51_sys);
  gr_cr51_cr51_sys->SetMarkerStyle(26); gr_cr51_cr51_sys->SetMarkerColor(kRed); gr_cr51_cr51_sys->SetMarkerSize(1.5); gr_cr51_cr51_sys->SetLineColorAlpha(kRed-3, 0.35); gr_cr51_cr51_sys->SetFillColorAlpha(kRed-3, 0.3); gr_cr51_cr51_sys->SetFillStyle(3000); gr_cr51_cr51_sys->SetLineWidth(7);
  p_cr51->cd();
  gr_cr51_cr51_sys->Draw("2 same");
  gr_cr51_cr51->Draw("p same");
  gr_dat_cr51_zr_sys->Draw("2 same"); gr_dat_cr51_zr->Draw("p same"); gr_dat_cr51_ru_sys->Draw("2 same"); gr_dat_cr51_ru->Draw("p same");

  
  double npart_cr62[ncent-mergedNau], cr62_cr62[ncent-mergedNau], cr62_cr62_sta[ncent-mergedNau], cr62_cr62_sys[ncent-mergedNau];
  npart_cr62[0] =  gr_dat_cr42_au->GetPointX(4); 
  npart_cr62[1] = gr_dat_cr42_au->GetPointX(5);
  npart_cr62[2] = gr_dat_cr42_au->GetPointX(6);;
  npart_cr62[3] = gr_dat_cr42_au->GetPointX(7);;
  npart_cr62[4] = gr_dat_cr42_au->GetPointX(8);;
  
  cr62_cr62[0] = -5.382717; cr62_cr62_sta[0] = 3.869256; cr62_cr62_sys[0] = 4.388961;
  cr62_cr62[1] = -0.574947; cr62_cr62_sta[1] = 0.400686; cr62_cr62_sys[1] = 0.259967;
  cr62_cr62[2] = -0.219302; cr62_cr62_sta[2] = 0.141346; cr62_cr62_sys[2] = 0.106994;
  cr62_cr62[3] = 0.168945; cr62_cr62_sta[3] = 0.0676932; cr62_cr62_sys[3] = 0.0341284;
  cr62_cr62[4] = 0.319113; cr62_cr62_sta[4] = 0.0304251; cr62_cr62_sys[4] = 0.0201758;

  TGraphErrors *gr_cr62_cr62     = new TGraphErrors(ncent-mergedNau, npart_cr62, cr62_cr62, 0, cr62_cr62_sta);
  gr_cr62_cr62->SetMarkerStyle(26); gr_cr62_cr62->SetMarkerColor(kRed); gr_cr62_cr62->SetLineColor(kRed); gr_cr62_cr62->SetMarkerSize(1.5); 

  TGraphErrors *gr_cr62_cr62_sys = new TGraphErrors(ncent-mergedNau, npart_cr62, cr62_cr62, 0, cr62_cr62_sys);
  gr_cr62_cr62_sys->SetMarkerStyle(26); gr_cr62_cr62_sys->SetMarkerColor(kRed); gr_cr62_cr62_sys->SetMarkerSize(1.5); gr_cr62_cr62_sys->SetLineColorAlpha(kRed-3, 0.35); gr_cr62_cr62_sys->SetFillColorAlpha(kRed-3, 0.3); gr_cr62_cr62_sys->SetFillStyle(3000); gr_cr62_cr62_sys->SetLineWidth(7);
  p_cr62->cd();
  gr_cr62_cr62_sys->Draw("2 same");
  gr_cr62_cr62->Draw("p same");
  gr_dat_cr62_zr_sys->Draw("2 same"); gr_dat_cr62_zr->Draw("p same"); gr_dat_cr62_ru_sys->Draw("2 same"); gr_dat_cr62_ru->Draw("p same");

  
  double cr62_zr = gr_dat_cr62_zr->GetPointY(0+mergedN);
  double cr62_zr_sta = gr_dat_cr62_zr->GetErrorY(0+mergedN);
  double cr62_zr_sys = gr_dat_cr62_zr_sys->GetErrorY(0+mergedN);
  double cr62_zr_unc = sqrt(cr62_zr_sta*cr62_zr_sta + cr62_zr_sys*cr62_zr_sys);
  double t_cr62_zr = (cr62_zr - 0)/cr62_zr_unc;
  
  
  
  double pval_cr62_zr = 0.5 * TMath::Erfc(t_cr62_zr / sqrt(2.0));
 
  if (pval_cr62_zr < 0.046) cout << "Reject null hypothesis. C6/C2 of Zr+Zr is significantly different from zero. pval="<<pval_cr62_zr << endl;
  else cout << "Cannot reject null hypothesis. C6/C2 of Zr+Zr is not significantly different from zero. pval="<<pval_cr62_zr << endl;
  cout<<"confidence level = "<<2*(0.5-pval_cr62_zr)<<endl;
  double cr51_zr = gr_dat_cr51_zr->GetPointY(0+mergedN);
  double cr51_zr_sta = gr_dat_cr51_zr->GetErrorY(0+mergedN);
  double cr51_zr_sys = gr_dat_cr51_zr_sys->GetErrorY(0+mergedN);
  double cr51_zr_unc = sqrt(cr51_zr_sta*cr51_zr_sta + cr51_zr_sys*cr51_zr_sys);
  double t_cr51_zr = (cr51_zr - 0)/cr51_zr_unc;
  
  double pval_cr51_zr = 0.5 * TMath::Erfc(t_cr51_zr / sqrt(2.0));
  if (pval_cr51_zr < 0.046) cout << "Reject null hypothesis. C5/C1 of Zr+Zr is significantly different from zero. pval="<<pval_cr51_zr << endl;
  else cout << "Cannot reject null hypothesis. C5/C1 of Zr+Zr is not significantly different from zero. pval="<<pval_cr51_zr << endl;
  cout<<"confidence level = "<<2*(0.5-pval_cr51_zr)<<endl;
  p_cr62->cd();
  gr_dat_cr62_zr_sys->Draw("2 same"); gr_dat_cr62_zr->Draw("p same"); gr_dat_cr62_ru_sys->Draw("2 same"); gr_dat_cr62_ru->Draw("p same");
  TPaveText *pt_tit_left = new TPaveText(0.1, 0.15, 0.9, 0.75, "NDC NB"); pt_tit_left->SetFillColorAlpha(0,0);
  pt_tit_left->AddText("Number of Participating Nucleons N_{part}");
  p_tit_mid->cd();
  pt_tit_left->Draw();

  TPaveText *pt_cr21 = new TPaveText(0.8 - 0.025, 0.84, 0.95 - 0.025, 0.99, "NDC NB"); pt_cr21->SetFillColorAlpha(0,0); pt_cr21->AddText("C_{2}/C_{1}"); p_cr21->cd(); pt_cr21->Draw("same");
  TPaveText *pt_cr32 = new TPaveText(0.8 - 0.025, 0.84, 0.95 - 0.025, 0.99, "NDC NB"); pt_cr32->SetFillColorAlpha(0,0); pt_cr32->AddText("C_{3}/C_{2}"); p_cr32->cd(); pt_cr32->Draw("same");
  TPaveText *pt_cr42 = new TPaveText(0.8 - 0.025, 0.84, 0.95 - 0.025, 0.99, "NDC NB"); pt_cr42->SetFillColorAlpha(0,0); pt_cr42->AddText("C_{4}/C_{2}"); p_cr42->cd(); pt_cr42->Draw("same");
  TPaveText *pt_cr51 = new TPaveText(0.75 - 0.005, 0.84, 0.90 - 0.005, 0.99, "NDC NB"); pt_cr51->SetFillColorAlpha(0,0); pt_cr51->AddText("C_{5}/C_{1}"); p_cr51->cd(); pt_cr51->Draw("same");
  TPaveText *pt_cr62 = new TPaveText(0.75 - 0.005, 0.84, 0.90 - 0.005, 0.99, "NDC NB"); pt_cr62->SetFillColorAlpha(0,0); pt_cr62->AddText("C_{6}/C_{2}"); p_cr62->cd(); pt_cr62->Draw("same");
 
  TLegend *l_cr_sim = new TLegend(0.375, 0.3, 0.925, 0.99, "", "NDC NB"); l_cr_sim->SetFillColorAlpha(0,0); l_cr_sim->SetBorderSize(0);
  l_cr_sim->AddEntry(gr_urqmd_cr21_zr, "Zr+Zr", "f");
  l_cr_sim->AddEntry(gr_urqmd_cr21_ru, "Ru+Ru", "f");
  l_cr_sim->AddEntry(gr_urqmd_cr21_au, "Au+Au", "f");

  TLine *l_cr42_hrg = new TLine(gr_dat_cr42_dummy->GetXaxis()->GetXmin(), 0.997, gr_dat_cr42_dummy->GetXaxis()->GetXmax(), 0.997); l_cr42_hrg->SetLineStyle(9); l_cr42_hrg->SetLineWidth(1);
  TLine *l_cr51_hrg = new TLine(gr_dat_cr51_dummy->GetXaxis()->GetXmin(), 0.997, gr_dat_cr51_dummy->GetXaxis()->GetXmax(), 0.997); l_cr51_hrg->SetLineStyle(9); l_cr51_hrg->SetLineWidth(1);
  TLine *l_cr62_hrg = new TLine(gr_dat_cr62_dummy->GetXaxis()->GetXmin(), 0.997, gr_dat_cr62_dummy->GetXaxis()->GetXmax(), 0.997); l_cr62_hrg->SetLineStyle(9); l_cr62_hrg->SetLineWidth(1);
  p_cr42->cd(); l_cr42_hrg->Draw("same");
  p_cr51->cd(); l_cr51_hrg->Draw("same");
  p_cr62->cd(); l_cr62_hrg->Draw("same");
  
  TLegend *l_hrg = new TLegend(0.1, 0.8, 0.55, 0.99, "", "NDC NB"); l_hrg->SetFillColorAlpha(0,0); l_hrg->SetBorderSize(0);
  l_hrg->AddEntry(l_cr42_hrg, "HRG GCE", "l");
  p_cr62->cd();
  l_hrg->Draw("same");
  

  
  c_cr_2->cd();
  p_cr32->Draw();
  p_cr42->Draw();
  p_cr51->Draw();
  p_cr62->Draw();

  
  
  p_tit_mid->Draw();

  c_cr_2->cd();
  TPad *p_tit_vertical = new TPad("p_c_tit_vertical","p_c_tit_vertical", 0.01, 0 * (1 - 0.01 - pad_bottom_buff) / 3 + pad_bottom_buff, 0.01 + 2 * pad_side_title_buff, 0.99); p_tit_vertical->Draw();  
  TPaveText *pt_tit_vertical = new TPaveText(0.01, 0.01, 0.99, 0.99, "NDC NB"); pt_tit_vertical->SetFillColorAlpha(0,0);
  TText *t_tit_vertical = pt_tit_vertical->AddText("Net-Proton Cumulant Ratios");
  t_tit_vertical->SetTextAngle(90);
  t_tit_vertical->SetTextAlign(22);
  t_tit_vertical->SetTextSize(0.55);
  p_tit_vertical->cd();
  pt_tit_vertical->Draw();
  
  p_cr21_2->cd();
  gr_dat_cr21_dummy->Draw("ap"); 
  gr_urqmd_cr21_au->Draw("3 same");  gr_urqmd_cr21_zr->Draw("3 same"); gr_urqmd_cr21_ru->Draw("3 same");
  
  
  gr_dat_cr21_au_sys_draw->Draw("2 same");
  gr_dat_cr21_au->Draw("psame"); gr_dat_cr21_zr_sys->Draw("2 same"); gr_dat_cr21_zr->Draw("p same"); gr_dat_cr21_ru_sys->Draw("2 same"); gr_dat_cr21_ru->Draw("p same");

  pt_cr21->Draw("same");

  
  TGraphErrors *gr_leg_zr = new TGraphErrors(); gr_leg_zr->SetMarkerColorAlpha(kBlack, 1.); gr_leg_zr->SetMarkerStyle(4);  gr_leg_zr->SetMarkerSize(2.5);
  TGraphErrors *gr_leg_ru = new TGraphErrors(); gr_leg_ru->SetMarkerColorAlpha(kBlack, 1.); gr_leg_ru->SetMarkerStyle(8);  gr_leg_ru->SetMarkerSize(2.5);
  TGraphErrors *gr_leg_au = new TGraphErrors(); gr_leg_au->SetMarkerColorAlpha(kRed, 1.);   gr_leg_au->SetMarkerStyle(26); gr_leg_au->SetMarkerSize(2.5);
  
  TLegend *l_cr_2_1= new TLegend(0.12+0.*(0.95-0.01)/3, 0.49, 0.12+1.*(0.95-0.01)/3, 0.79, "", "NDC NB"); l_cr_2_1->SetFillColorAlpha(0,0); l_cr_2_1->SetBorderSize(0);
  gr_dat_cr21_zr->SetNameTitle("","");
  l_cr_2_1->AddEntry(gr_leg_zr, "", "p");
  TLegend *l_cr_2_2= new TLegend(0.10+1.*(0.95-0.01)/3, 0.49, 0.10+2.*(0.95-0.01)/3, 0.79, "", "NDC NB"); l_cr_2_2->SetFillColorAlpha(0,0); l_cr_2_2->SetBorderSize(0);
  gr_dat_cr21_ru->SetNameTitle("","");
  l_cr_2_2->AddEntry(gr_leg_ru, "", "p");
  TLegend *l_cr_2_3= new TLegend(0.11+2.*(0.95-0.01)/3, 0.49, 0.11+3.*(0.95-0.01)/3, 0.79, "", "NDC NB"); l_cr_2_3->SetFillColorAlpha(0,0); l_cr_2_3->SetBorderSize(0);
  gr_dat_cr21_au->SetNameTitle("","");
  l_cr_2_3->AddEntry(gr_leg_au, "", "p");
  
  TPaveText *pt_cr_2_1 = new TPaveText(0.01, 0.69, 0.95, 0.99, "NDC NB"); pt_cr_2_1->SetFillColorAlpha(0,0);
  pt_cr_2_1->AddText("Zr+Zr  Ru+Ru  Au+Au");
  TPaveText *pt_cr_2_2 = new TPaveText(0.01, 0.01, 0.95, 0.49, "NDC NB"); pt_cr_2_2->SetFillColorAlpha(0,0);
  
  pt_cr_2_2->AddText("Collisions at #sqrt{s_{NN}} = 200 GeV");
  
  
  pt_cr_2_2->AddText("|y| < 0.5, 0.4 < p_{T} < 2.0 GeV/c");
  p_cr21_urqmd_2->cd(); pt_cr_2_1->Draw("same"); pt_cr_2_2->Draw("same"); l_cr_2_1->Draw("same"); l_cr_2_2->Draw("same"); l_cr_2_3->Draw("same");

  TLegend *l_cr32_1 = new TLegend(0.15, 0.53, 0.5, 0.95, "UrQMD", "NDC NB"); l_cr32_1->SetFillColorAlpha(0,0); l_cr32_1->SetBorderSize(0);
  l_cr32_1->AddEntry(gr_urqmd_cr21_zr, "Zr+Zr", "f");
  l_cr32_1->AddEntry(gr_urqmd_cr21_ru, "Ru+Ru", "f");
  l_cr32_1->AddEntry(gr_urqmd_cr21_au, "Au+Au", "f");
  
  p_cr32->cd();
  l_cr32_1->Draw("same");

  
  p_cr32->cd();

  c_cr_2->Print("output/pics/c_cr_with_urqmd_2.png");

}
