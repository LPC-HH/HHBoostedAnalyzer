#include "JetNtupler.h"
#include "JetTree.h"

//C++ includes

//ROOT includes
#include "TH1F.h"

using namespace std;

void JetNtupler::Analyze(bool isData, int Option, string outputfilename, string label)
{
 
    cout << "Initializing..." << endl;
    string outfilename = outputfilename;
    if (outfilename == "") outfilename = "JetNtuple.root";
    TFile *outFile = new TFile(outfilename.c_str(), "RECREATE");    
    JetTree *jetTree = new JetTree;
    jetTree->CreateTree();
    jetTree->tree_->SetAutoFlush(0);
    
    cout << "Run With Option = " << Option << "\n";
    
    UInt_t NJetsFilled = 0;
 
    //begin loop
    if (fChain == 0) return;
    UInt_t nentries = fChain->GetEntries();
    Long64_t nbytes = 0, nb = 0;

    cout << "nentries = " << nentries << "\n";
    for (UInt_t jentry=0; jentry<nentries;jentry++) {
      //begin event
      if(jentry % 10000 == 0) cout << "Processing entry " << jentry << endl;
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      //****************************************
      //Tree entries based on reco objects
      //****************************************
      if (Option < 10 ) {

	for(int i = 0; i < nFatJet; i++){
    
	  //***********************
	  //Fill Jet Variables
	  //***********************
  
	  jetTree->weight = 1;
	  jetTree->run = run;
	  jetTree->lumi = luminosityBlock;
	  jetTree->event = event;
	  jetTree->pt = FatJet_pt[i];
	  jetTree->eta = FatJet_eta[i];
	  jetTree->phi = FatJet_phi[i];

	  //Match to Gen Jet
	  // int matchedIndex = -1;
	  // float minDR = 9999;

	  // for(int j = 0; j < nGenJets; j++){
	  //   double tmpDR = deltaR( genJetEta[j],genJetPhi[j], jetEta[i],jetPhi[i]);
	  //   if ( tmpDR < 0.4
	  // 	 && tmpDR < minDR
	  // 	 ) {		
	  //     matchedIndex = j;
	  //     minDR = tmpDR;
	  //   }
	  // }

	  //***********************
	  //Fill Jet
	  //***********************
	  NJetsFilled++;
	  jetTree->tree_->Fill();
	}
      }
    }//end of event loop

    cout << "Filled Total of " << NJetsFilled << " Jets\n";
    cout << "Writing output trees..." << endl;
    outFile->Write();
    outFile->Close();

}



