/* class TApplication; */
class TFile;
/* class TH2D; */
class TF1;
/* //29072021(start) */
/* //Temp while TPC eff map res is low */
/* class TGraph2D; */
/* //29072021(finish) */

class TGraphErrors;//04082022
class TGraph;//13082022
class TH1D;//13082022

class StDetectorEfficiency {

 public:
  // StDetectorEfficiency(const char*, const char*, const char*, const char*, const char*, const char*);
  // StDetectorEfficiency(const char*);
  StDetectorEfficiency();
  // StDetectorEfficiency(const char*, const char*);
  ~StDetectorEfficiency();

  //29072021(start)
  //Temp while TPC eff map res is low
  /* void Init_DetEff(const char*); */
  void Init_DetEff(const char*, const char*, const char*, const char*, const char*);
  /* void Init_DetEff(const char*, const char*); */
  //29072021(finish)

  // void Clear_DetEff();
  // //charge, p(to decide tof match), pt, y_pi, y_K, y_P 
  // bool GetAcc(int, double, double, double);
  //pid, charge, p(to decide tof match), pt, y_pi, y_K, y_P
  //pT, y
  bool GetAcc(double, double);
  //charge, p(to decide tof match), pt, eta, nSPi, nSK, nSP
  // double GetEff(int, double, double, double, double, double, double, double);
  //charge, p(to decide tof match), pt, eta, y_pi, y_K, y_P,  nSPi, nSK, nSP
  //pid, charge, pT, y, m2
  /* double GetEff(int, int, double, double, double); */
  //pid, charge, pT, y, m2, ref3
  //27012022(start)
  // double GetEff(int, int, double, double, double, double);
  double GetEff(int, int, double, double, double, double, double, double);
  //27012022(finish)
  //pid, charge, pT, y, m2, ref3, NameRuZr ("Ru" || "Zr")
  /* double GetEff(int, int, double, double, double, double, string); */

 private:

  static const int ncent = 10;//17082022
  static const int NyBin = 30;
  static const int NptBin = 10;
  static const int yBinMerge = 5;// 30/6
  static const int ptBinMerge = 2;// 10/5
        
  static const int nPID = 6;//pi+, pi-, k+, k-, proton, anti-proton
 
  /* static const int ny = 20; //24062022 */
  static const int ny = 1; //24062022

 // TFile *f_TPC[nPID];//pi+, pi-, k+, k-, proton, anti-proton
  // TFile *f_TOF;
  /* TFile *f_eff; */
  
  /* TH2D *h2_Eff_TPC[nPID];//pi+, pi-, k+, k-, proton, anti-proton */
  /* TH2D *h2_Eff_TOF[nPID];//pi+, pi-, k+, k-, proton, anti-proton */

  /* double y_range[NyBin/yBinMerge+1]; */
  /* double pt_range[NptBin/ptBinMerge+1]; */

  /* TF1* f1_pol1_TPC_P_eff2[NyBin*NptBin/yBinMerge/ptBinMerge]; */
  /* TF1* f1_pol1_TPC_M_eff2[NyBin*NptBin/yBinMerge/ptBinMerge]; */
  /* TF1* f1_pol1_TOF_P_eff2[NyBin*NptBin/yBinMerge/ptBinMerge]; */
  /* TF1* f1_pol1_TOF_M_eff2[NyBin*NptBin/yBinMerge/ptBinMerge]; */

  /* double y_range[7]; */
  /* double pt_range[6]; */

  /* double TPC_P_p0[NyBin/yBinMerge][NptBin/ptBinMerge], TPC_P_p1[NyBin/yBinMerge][NptBin/ptBinMerge], TPC_M_p0[NyBin/yBinMerge][NptBin/ptBinMerge], TPC_M_p1[NyBin/yBinMerge][NptBin/ptBinMerge]; */
  /* double TOF_P_p0[NyBin/yBinMerge][NptBin/ptBinMerge], TOF_P_p1[NyBin/yBinMerge][NptBin/ptBinMerge], TOF_M_p0[NyBin/yBinMerge][NptBin/ptBinMerge], TOF_M_p1[NyBin/yBinMerge][NptBin/ptBinMerge]; */

  TFile *f_tpc_pP; TFile *f_tpc_pM;
  TFile *f_tof_pP; TFile *f_tof_pM;

  //13082022(start)
  TH1D *h1_y_pt_eff_tpc_pP[ncent];
  TH1D *h1_y_pt_eff_tpc_pM[ncent];
  TH1D *h1_y_pt_eff_tof_pP[ncent];
  TH1D *h1_y_pt_eff_tof_pM[ncent];

  double ref3_avg[ncent];
  double eff_tpc_pP[ncent], eff_tpc_pM[ncent];
  double eff_tof_pP[ncent], eff_tof_pM[ncent];

  TGraph *gr_eff_tpc_pP, *gr_eff_tpc_pM;
  TGraph *gr_eff_tof_pP, *gr_eff_tof_pM;
  //13082022(finish)

  /* double para_low_ru[4][3] = { */
  /*   {0.893693, -0.000118462, 0}, */
  /*   {0.839426, -7.90703e-05, 0}, */
  /*   {0.756135, -6.26262e-05, 0}, */
  /*   {0.707712, -5.23131e-05, 0}, */
  /* }; */
  /* double para_high_ru[4][3] = { */
  /*   {0.883726, -8.0754e-05, 0}, */
  /*   {0.858948, -5.57002e-05, 0}, */
  /*   {0.758978, -7.95924e-05, 0}, */
  /*   {0.743305, -7.77935e-05, 0}, */
  /* }; */
  /* double para_low_zr[4][3] = { */
  /*   {0.88851, -0.000103228, 0}, */
  /*   {0.8512, -0.000103001, 0}, */
  /*   {0.756403, -6.24269e-05, 0}, */
  /*   {0.707903, -5.23395e-05, 0}, */
  /* }; */
  /* double para_high_zr[4][3] = { */
  /*   {0.885343, -8.03316e-05, 0}, */
  /*   {0.861873, -7.00942e-05, 0}, */
  /*   {0.759659, -7.99157e-05, 0}, */
  /*   {0.74391, -7.79897e-05, 0}, */
  /* }; */

  /* double para_low[4][3]; */
  /* double para_high[4][3]; */

  TF1 *f_tpc_p_p0_lopt; TF1 *f_tpc_p_p0_hipt;
  TF1 *f_tpc_p_p1_lopt; TF1 *f_tpc_p_p1_hipt;
  TF1 *f_tpc_p_p2_lopt;
  TF1 *f_tpc_ap_p0_lopt; TF1 *f_tpc_ap_p0_hipt;
  TF1 *f_tpc_ap_p1_lopt; TF1 *f_tpc_ap_p1_hipt;
  TF1 *f_tpc_ap_p2_lopt;

  TF1 *f_tof_p_p0; TF1 *f_tof_ap_p0;
  TF1 *f_tof_p_p1; TF1 *f_tof_ap_p1;
  TF1 *f_tof_p_p2; TF1 *f_tof_ap_p2;

  /* TF1 *f_tpc_p; TF1 *f_tpc_ap; */
  TF1 *f_tpc_p_lopt; TF1 *f_tpc_ap_lopt;
  TF1 *f_tpc_p_hipt; TF1 *f_tpc_ap_hipt;
  TF1 *f_tof_p; TF1 *f_tof_ap;

  /* //29072021(start) */
  /* //Temp while TPC eff map res is low */
  /*   TFile *f_eff_smear; */
  /*   TGraph2D *gr_Eff_TPC[nPID]; */
  /* //29072021(finish) */

  //variables
  // double eff; // just delcare inside the class
  // bool eta_cut;
  bool y_cut;
  bool pT_cut;

  bool PinS;
  bool KnS;
  bool PnS;
  double PinS_v;
  double KnS_v;
  double PnS_v;

  bool PiPtTOF;  
  bool KPtTOF;
  bool PPtTOF;

  bool PiM2;
  bool KM2;
  bool PM2;

};
