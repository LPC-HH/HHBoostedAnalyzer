//C++ includes
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

// ROOT includes
#include <TROOT.h>
#include <TFile.h>
#include <TString.h>
#include <TTree.h>
#include <TChain.h>

#include <HHTo4BNtupler.h>

using namespace std;

std::string ParseCommandLine( int argc, char* argv[], std::string opt )
{
  for (int i = 1; i < argc; i++ )
    {
      std::string tmp( argv[i] );
      if ( tmp.find( opt ) != std::string::npos )
        {
          if ( tmp.find( "=" )  != std::string::npos ) return tmp.substr( tmp.find_last_of("=") + 1 );
	  if ( tmp.find( "--" ) != std::string::npos ) return "yes";
	}
    }
  
  return "";
};

void usage()
{
  std::cerr << "Usage: RunJetNtupler  <input list>  [options]\n[options]:\n"
	    << "    --isData=<yes/no>\n"
	    << "    --outputFile=<output filename> (optional)\n"
	    << "    --optionNumber=<option number> (optional)\n"
	    << "    --year=<year> (optional)\n" 
	    << "    --pileupWeightName=<sampleName> (optional)\n" 
	    << "    --startEventNumber=<startEventNumber> (optional)\n" 
	    << "    --endEventNumber=<endEventNumber> (optional)\n" 
	    << "-h  --help"
	    << std::endl;
};

int main(int argc, char* argv[]){

  //get input files and analysis type from command line
  if ( ParseCommandLine( argc, argv, "--help" ) != ""  || ParseCommandLine( argc, argv, "-h" ) != ""  || argc < 2 )
    {
      usage();
      return -1;
    }
  
  //----------------------------------------
  //Getting <input list> and <analysis type>
  //----------------------------------------
  string inputFileName(argv[1]);
  
  //--------------------------------
  //G e t t i n g   d a t a  f l a g 
  //--------------------------------
  std::string _isData = ParseCommandLine( argc, argv, "--isData" );
  std::string _d = ParseCommandLine( argc, argv, "-d" );
  bool isData = false;
  if ( _isData == "yes" || _d == "yes" ) isData = true;

  //---------------------------------------------
  //G e t t i n g   o u t p u t F i l e   N a m e  
  //---------------------------------------------
  std::string _outFile = ParseCommandLine( argc, argv, "--outputFile=" );
  std::string _f = ParseCommandLine( argc, argv, "-f=" );
  string outputFileName = "";
  if ( _outFile != "" )
    {
      outputFileName = _outFile;
    }
  else if ( _f != "" )
    {
      outputFileName = _f;
    }
  else
    {
      std::cerr << "[WARNING]: output ROOT file not provided, using default output" << std::endl;
    }
  
  //-----------------------------------------
  //G e t t i n g   o p t i o n   n u m b e r
  //-----------------------------------------
  int option = -1;
  std::string _optionNumber = ParseCommandLine( argc, argv, "--optionNumber=" );
  std::string _n = ParseCommandLine( argc, argv, "-n=" );
  if ( _optionNumber != "" )
    {
      option = atoi( _optionNumber.c_str() );
    }
  else if ( _n != "" )
    {
      option = atoi( _n.c_str() );
    } 
  else
    {
      std::cerr << "[WARNING]: option number not provided, using default option number" << std::endl;
    }
  
  string year = "";
  std::string _year = ParseCommandLine( argc, argv, "--year=" );
  if ( _year != "" ) 
    {
      year = _year;
    }
  else
    {
      std::cerr << "[WARNING]: optional year not provided, using default year 2017" << std::endl;
    }

  string pileupWeightName = "";
  std::string _pileupWeightName = ParseCommandLine( argc, argv, "--pileupWeightName=" );
  if ( _pileupWeightName != "" ) 
    {
      pileupWeightName = _pileupWeightName;
    }
  else
    {
      std::cerr << "[WARNING]: pileupWeightName not provided, using default empty pileupWeightName" << std::endl;
    }
 

  //-----------------------------------------
  //Get Start and End Event Number
  //-----------------------------------------
  int numberOfJobs = 1;
  int jobIndex = 0;
  std::string _numberOfJobs = ParseCommandLine( argc, argv, "--numberOfJobs=" );
  if ( _numberOfJobs != "" )
    {
      numberOfJobs = atoi( _numberOfJobs.c_str() );
    }  
  std::string _jobIndex = ParseCommandLine( argc, argv, "--jobIndex=" );
  if ( _jobIndex != "" )
    {
      jobIndex = atoi( _jobIndex.c_str() );
    }  
  




  std::cout << "[INFO]: <input list> --> " << inputFileName << std::endl;
  std::cout << "[INFO]: isData --> " << isData << std::endl;
  std::cout << "[INFO]: outputFileName --> " << outputFileName << std::endl;
  std::cout << "[INFO]: option --> " << option << std::endl;
  std::cout << "[INFO]: year --> " << year << std::endl;
  std::cout << "[INFO]: pileupWeightName --> " << pileupWeightName << std::endl;
  std::cout << "[INFO]: numberOfJobs --> " << numberOfJobs << std::endl;
  std::cout << "[INFO]: jobIndex --> " << jobIndex << std::endl;
  
    //build the TChain
    //tree name is set give the structure in the first root file, see while loop below
    TChain* theChain = new TChain();
    string curFileName;
    ifstream inputFile(inputFileName.c_str());
    int NFilesLoaded = 0;
    if ( !inputFile ){
      cerr << "Error: input file not found!" << endl;
      return -1;
    }
    
    while ( getline(inputFile, curFileName) ) {
      if ( NFilesLoaded == 0 ) {	   
	TFile* f_0 = TFile::Open( curFileName.c_str() );
	theChain->SetName("Events");
	theChain->Add( curFileName.c_str() );
	delete f_0;
      } else {
	//Addind remaining files after file structure is decided
	theChain->Add( curFileName.c_str() );
      }
      NFilesLoaded++;
    }
    std::cout << "Loaded Total of " << NFilesLoaded << " files\n";
    if ( theChain == NULL ) return -1;
    
    HHTo4BNtupler analyzer(theChain);
    
    //------ EXECUTE ------//
    cout << "Executing HHTo4BNtupler..." << endl;
    //analyzer.EnableAll();
    analyzer.Analyze(isData, numberOfJobs, jobIndex, option, outputFileName, year, pileupWeightName);
    cout << "Process completed!" << endl;
    cerr << "------------------------------" << endl; //present so that an empty .err file corresponds to a failed job
    
    return 0;
}
