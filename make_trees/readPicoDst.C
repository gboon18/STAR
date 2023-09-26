#include <TSystem>

#include <ctime> //to cout run time

class StMaker;
class StChain;
class StPicoDstMaker;
class StPicoEvent;
class StEpdUtil;
class StQAMaker; 
StChain *chain;
void readPicoDst(const Char_t *inputFile = "test.list", const Char_t *outputFile = "QA_test_", const Char_t *JobID = "01")
{
  // int nEvents = 15000000;
  int nEvents = 10;
  // int nEvents = 130000;
  // current date/time based on current system
  time_t now = time(0);

  gROOT->LoadMacro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");
  loadSharedLibraries();

  gSystem->Load("StUtilities");    
  gSystem->Load("StPicoEvent");
  gSystem->Load("StPicoDstMaker");
  gSystem->Load("StEpdUtil");
  gSystem->Load("StQAMaker");
  // gSystem->Load("StDetectorEfficiency");

  chain = new StChain();

  StPicoDstMaker *picoMaker = new StPicoDstMaker(2, inputFile, "picoDst"); //1: write, 2: read.
  StQAMaker *anaMaker = new StQAMaker("ana",picoMaker, outputFile, JobID);

  chain->Init();
  cout << "chain->Init();" << endl;
  int total = picoMaker->chain()->GetEntries();
  cout << " Total entries = " << total << endl;

  // cout << " We are using only " << nEvents << " entries" << endl;
  // for (int i = 0; i < nEvents; i++)
  for (int i = 0; i < total; i++)
    {
      if (i % 10000 == 0)
	cout << "Working on eventNumber " << i << endl;

      chain->Clear();
      // cout<<"Clear"<<endl;
      int iret = chain->Make(i);
      // cout<<"Make"<<endl;

      if (iret)
	{
	  cout << "Bad return code!" << iret << endl;
	  break;
	}

      // total++;

    }

  cout << "****************************************** " << endl;
  cout << "Work done... now its time to close up shop!" << endl;
  cout << "****************************************** " << endl;
  chain->Finish();
  cout << "****************************************** " << endl;
  // cout << "total number of events  " << nEvents << endl;
  cout << "total number of events  " << total << endl;
  cout << "****************************************** " << endl;

  // current date/time based on current system
  time_t then = time(0);
  time_t diff = then - now;
  // convert now to string form
  char* dt = ctime(&diff);
  // convert now to tm struct for UTC
  tm* gmtm = gmtime(&diff);
  dt = asctime(gmtm);
  cout << "****************************************** " << endl;
  cout << "It took :"<< dt <<"for the job to be done."  << endl;
  cout << "****************************************** " << endl;

  delete chain;

}
