#include "MakeMCPileupDistribution.h"

//C++ includes
#include <sys/stat.h>

//ROOT includes
#include "TH1F.h"

using namespace std;

void MakeMCPileupDistribution::Analyze(bool isData, int option, string outFileName, string label, string pileupWeightName)
{
  //initialization: create one TTree for each analysis box 
  cout << "Initializing..." << endl;
  if (outFileName.empty()){
    cout << "MakeMCPileupDistribution: Output filename not specified!" << endl << "Using default output name MCPileupDistribution.root" << endl;
    outFileName = "MCPileupDistribution.root";
  }
  TFile outFile(outFileName.c_str(), "UPDATE");
  
  string Label = label;
  if (label != "") Label = "_"+label;
    
  TH1F* histPUMean =  new TH1F( ("PUMean"+Label).c_str(),";nPUMean;Number of Events", 200, -0.5, 199.5);
  TH1F* histPU =  new TH1F( ("PU"+Label).c_str(),";nPU;Number of Events", 200, -0.5, 199.5);
    
  //begin loop
  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntries();
  Long64_t nbytes = 0, nb = 0;


  cout << "Total Events: " << nentries << "\n";
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    //begin event
    if(jentry % 10000 == 0) cout << "Processing entry " << jentry << endl;
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    
    //fill normalization histogram
    histPUMean->Fill(Pileup_nTrueInt);
    histPU->Fill(Pileup_nPU);

  }//end of event loop
  
  cout << "Writing output ..." << endl;  
  outFile.WriteTObject(histPUMean, ("PUMean"+Label).c_str(), "WriteDelete");
  outFile.WriteTObject(histPU, ("PU"+Label).c_str(), "WriteDelete");
  outFile.Close();
}
