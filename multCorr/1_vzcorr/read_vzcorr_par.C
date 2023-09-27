void read_vzcorr_par(){

  ifstream myfile_zr_in,  myfile_ru_in;
  double vz[30+1], par_vzcorr_zr[30], par_vzcorr_ru[30];
  for(int i_vz = 0 ; i_vz < 30 ; i_vz++){ vz[i_vz] = -35 + i_vz*2;} vz[30] = 25;
  myfile_zr_in.open("output/zr_vzcorr_par.txt"); myfile_ru_in.open("output/ru_vzcorr_par.txt");
  for(int i_vz = 0 ; i_vz < 30 ; i_vz++){
    myfile_zr_in>>par_vzcorr_zr[i_vz];
    myfile_ru_in>>par_vzcorr_ru[i_vz];
    cout<<"["<<vz[i_vz]<<","<<vz[i_vz+1]<<"]: "<<par_vzcorr_zr[i_vz]<<", "<<par_vzcorr_ru[i_vz]<<endl;
  }
  myfile_zr_in.close();
  myfile_ru_in.close();

}
