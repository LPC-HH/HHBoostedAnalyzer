#include "JetNtupler.h"
#include "JetTree.h"

//C++ includes

//ROOT includes
#include "TH1F.h"

using namespace std;

void JetNtupler::Analyze(bool isData, int Option, string outputfilename, string label, string pileupWeightName)
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
	  jetTree->msoftdrop = FatJet_msoftdrop[i];
	  jetTree->area = FatJet_area[i];
	  jetTree->btagDDBvL = FatJet_btagDDBvL[i];
	  jetTree->btagHbb = FatJet_btagHbb[i];
	  jetTree->deepTagHbb = FatJet_deepTagHbb[i];
	  jetTree->deepTagHqqqq = FatJet_deepTagHqqqq[i];
	  jetTree->deepTagMDHbb = FatJet_deepTagMDHbb[i];
	  jetTree->deepTagMDHqqqq = FatJet_deepTagMDHqqqq[i];
	  jetTree->deepTagMDQCDbb = FatJet_deepTagMDQCDbb[i];
	  
	  //cout << "jet: " << FatJet_pt[i] << " " << FatJet_eta[i] << " " << FatJet_phi[i] << "\n";

	  //****************************************************
	  //Match to Higgs
	  //****************************************************
	  jetTree->matchedGenMass = -999;
	  jetTree->matchedGenPt = -999;
	  jetTree->matchedGenEta = -999;
	  jetTree->matchedGenPhi = -999;

	  int matchedIndex = -1;
	  float minDR = 9999;
	  for(int j = 0; j < nGenPart; j++){
	    if (abs(GenPart_pdgId[j]) == 25 && GenPart_status[j] == 62) {
	      double tmpDR = deltaR( GenPart_eta[j],GenPart_phi[j], FatJet_eta[i],FatJet_phi[i]);
	      if ( tmpDR < 1.0 && tmpDR < minDR ) {		
		matchedIndex = j;
		minDR = tmpDR;
		//cout << "Matched Higgs: " << tmpDR << " : " << minDR << "\n";
	      }
	    }
	  }

	  string matchType = "";

	  //declare a match if it's within 0.2
	  if (matchedIndex >= 0 && minDR < 0.8) {

	    jetTree->matchedGenMass = GenPart_mass[matchedIndex];
	    jetTree->matchedGenPt = GenPart_pt[matchedIndex];
	    jetTree->matchedGenEta = GenPart_eta[matchedIndex];
	    jetTree->matchedGenPhi = GenPart_phi[matchedIndex];
	    

	    //find daughters of the matched Higgs
	    //NOTE: We need to add the requirement that the daughters fall within the cone for HBB, and that granddaughters fall within the cone for HVV->qqqq
	    int daughter1Index = -1;
	    int daughter2Index = -1;
	    bool daughter1InCone = false;
	    bool daughter2InCone = false;
	    int daughterId = 0;
	    for(int j = 0; j < nGenPart; j++) {
	      if (GenPart_genPartIdxMother[j] == matchedIndex) {
		if (daughter1Index < 0) {
		  daughter1Index = j;
		  daughterId = abs(GenPart_pdgId[j]);
		  if (deltaR( GenPart_eta[j],GenPart_phi[j], FatJet_eta[i],FatJet_phi[i]) < 0.8) daughter1InCone = true;
		} else if (daughter2Index < 0) {
		  daughter2Index = j;
		  if (deltaR( GenPart_eta[j],GenPart_phi[j], FatJet_eta[i],FatJet_phi[i]) < 0.8) daughter2InCone = true;
		}
	      }
	    }
	    //cout << "daughter: " << daughterId << " | " << daughter1Index << " , " << daughter2Index << "\n";
	    
	    if (daughterId == 5 && daughter1InCone && daughter2InCone) {
	      matchType = "HBB";	      
	    } else if (daughterId == 24 || daughterId == 23) {
	      
	      //find granddaughters
	      int daughter1_daughterId = 0;
	      int daughter2_daughterId = 0;
	      int grandDaughter1_1_Index = -1;
	      int grandDaughter1_2_Index = -1;
	      int grandDaughter2_1_Index = -1;
	      int grandDaughter2_2_Index = -1;
	      bool grandDaughter1_1_InCone = false;
	      bool grandDaughter1_2_InCone = false;
	      bool grandDaughter2_1_InCone = false;
	      bool grandDaughter2_2_InCone = false;
	      
	      for(int j = 0; j < nGenPart; j++) {
		if (GenPart_genPartIdxMother[j] == daughter1Index) {
		  daughter1_daughterId = abs(GenPart_pdgId[j]);
		  if (grandDaughter1_1_Index < 0) {
		    grandDaughter1_1_Index = j;
		    if (deltaR( GenPart_eta[j],GenPart_phi[j], FatJet_eta[i],FatJet_phi[i]) < 0.8) grandDaughter1_1_InCone = true;	
		  } else if (grandDaughter1_2_Index < 0) {
		    grandDaughter1_2_Index = j;
		    if (deltaR( GenPart_eta[j],GenPart_phi[j], FatJet_eta[i],FatJet_phi[i]) < 0.8) grandDaughter1_2_InCone = true;	
		  }
		}
		if (GenPart_genPartIdxMother[j] == daughter2Index) {
		  daughter2_daughterId = abs(GenPart_pdgId[j]);
		  if (grandDaughter2_1_Index < 0) {
		    grandDaughter2_1_Index = j;
		    if (deltaR( GenPart_eta[j],GenPart_phi[j], FatJet_eta[i],FatJet_phi[i]) < 0.8) grandDaughter2_1_InCone = true;	
		  } else if (grandDaughter2_2_Index < 0) {
		    grandDaughter2_2_Index = j;
		    if (deltaR( GenPart_eta[j],GenPart_phi[j], FatJet_eta[i],FatJet_phi[i]) < 0.8) grandDaughter2_2_InCone = true;	
		  }
		}
	      }

	      //cout << "granddaughter: " << daughter1_daughterId << " " << daughter2_daughterId << "\n";
	    
	      if (daughter1_daughterId >= 1 && daughter1_daughterId <= 5
		  && daughter2_daughterId >= 1 && daughter2_daughterId <= 5
		  && grandDaughter1_1_InCone
		  && grandDaughter1_2_InCone
		  && grandDaughter2_1_InCone
		  && grandDaughter2_2_InCone
		  ) {
		if (daughterId == 24) {
		  matchType = "HWWqqqq";
		} else {
		  matchType = "HZZqqqq";
		}
	      } else if (
			 (daughter1_daughterId >= 1 && daughter1_daughterId <= 5 && !(daughter2_daughterId >= 1 && daughter2_daughterId <= 5))
			 ||
			 (daughter2_daughterId >= 1 && daughter2_daughterId <= 5 && !(daughter1_daughterId >= 1 && daughter1_daughterId <= 5))
			 )
		{
		  if (daughterId == 24) {
		    matchType = "HWWlnuqq";
		  } 
		}
	    }	    	    
	  }
	  
	  //cout << "matchType = " << matchType << "\n";
	  jetTree->matchedToHbb = false;
	  jetTree->matchedToHWWqqqq = false;
	  jetTree->matchedToHZZqqqq = false;
	  jetTree->matchedToHWWlnuqq = false;

	  if (matchType == "HBB") {
	    jetTree->matchedToHbb = true;
	  }
	  if (matchType == "HWWqqqq") {
	    jetTree->matchedToHWWqqqq = true;
	  }
	  if (matchType == "HZZqqqq") {
	    jetTree->matchedToHZZqqqq = true;
	  }
	  if (matchType == "HWWlnuqq") {
	    jetTree->matchedToHWWlnuqq = true;
	  }
	  //cout << "matched : " << jetTree->matchedToHbb << " " << jetTree->matchedToHWWlnuqq << "\n";
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



