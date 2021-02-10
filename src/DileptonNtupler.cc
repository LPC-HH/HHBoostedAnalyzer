#include "DileptonNtupler.h"
#include "JetTree.h"

//C++ includes

//ROOT includes
#include "TH1F.h"

using namespace std;

void DileptonNtupler::Analyze(bool isData, int Option, string outputfilename, string label, string pileupWeightName)
{
 
    cout << "Initializing..." << endl;
    string outfilename = outputfilename;
    if (outfilename == "") outfilename = "HHTo4BNtuple.root";
    TFile *outFile = new TFile(outfilename.c_str(), "RECREATE");    
 
    //histogram containing total number of processed events (for normalization)
    TH1F *NEvents = new TH1F("NEvents", "NEvents", 1, 1, 2);

    //output TTree
    TTree *outputTree = new TTree("tree", "");
 
    //------------------------
    //declare branch variables
    //------------------------
    float weight = 0;
    float genZ_Pt = 0;
    float genZ_Eta = 0;
    int lep1Id = 0;
    float lep1Pt = -1;
    float lep1Eta = -1;
    float lep1Phi = -1;
    int lep2Id = 0;
    float lep2Pt = -1;
    float lep2Eta = -1;
    float lep2Phi = -1;
    float dileptonMass = -1;
    float MET = -1;
    int NJets = 0;
    int NBTags = 0;

    //------------------------
    //set branches on big tree
    //------------------------
    outputTree->Branch("weight", &weight, "weight/F");
    outputTree->Branch("genZ_Pt", &genZ_Pt, "genZ_Pt/F");
    outputTree->Branch("genZ_Eta", &genZ_Eta, "genZ_Eta/F");
  //   outputTree->Branch("lep1Id", &lep1Id, "lep1Id/I");
  //   outputTree->Branch("lep1Pt", &lep1Pt, "lep1Pt/F");
  //   outputTree->Branch("lep1Eta", &lep1Eta, "lep1Eta/F");
  //   outputTree->Branch("lep1Phi", &lep1Phi, "lep1Phi/F");
  //   outputTree->Branch("lep2Id", &lep2Id, "lep2Id/I");
  //   outputTree->Branch("lep2Pt", &lep2Pt, "lep2Pt/F");
  //   outputTree->Branch("lep2Eta", &lep2Eta, "lep2Eta/F");
  //   outputTree->Branch("lep2Phi", &lep2Phi, "lep2Phi/F");
  //   outputTree->Branch("dileptonMass", &dileptonMass, "dileptonMass/F");
  //   outputTree->Branch("MET", &MET, "MET/F");
  //   outputTree->Branch("NJets", &NJets, "NJets/I");
  //   outputTree->Branch("NBTags", &NBTags, "NBTags/I");

  //   outputTree->Branch("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ",                                        &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ,                                       "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ/O");
  // outputTree->Branch("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL",                                        &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL,                                       "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL/O");
  // outputTree->Branch("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL",                                        &HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL,                                       "HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL/O");
  // outputTree->Branch("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ",                                        &HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ,                                       "HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ/O");
  // outputTree->Branch("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ",                                        &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ,                                       "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ/O");
  // outputTree->Branch("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL",                                        &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL,                                       "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL/O");

    cout << "Run With Option = " << Option << "\n";
    
    UInt_t NEventsFilled = 0;
 
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

      //fill normalization histogram
      weight = genWeight / fabs(genWeight);
      NEvents->SetBinContent( 1, NEvents->GetBinContent(1) + weight);


      //reset tree variables
      genZ_Pt = 0;
      genZ_Eta = 0;
      lep1Id = 0;
      lep1Pt = -1;
      lep1Eta = -1;
      lep1Phi = -1;
      lep2Id = 0;
      lep2Pt = -1;
      lep2Eta = -1;
      lep2Phi = -1;
      dileptonMass = -1;
      MET = -1;
      NJets = 0;
      NBTags = 0;
      
      //***********************
      //Gen Z
      //***********************
      
      for(int i = 0; i < nGenPart; i++) {		
	if ( abs(GenPart_pdgId[i]) == 23 
	     && GenPart_status[i] == 62 
	     ) {
	  genZ_Pt = GenPart_pt[i];
	  genZ_Eta = GenPart_eta[i];
	}
      }
      
      //***********************
      //Select Leptons
      //***********************
      vector<TLorentzVector> GoodLeptons;
      vector<int> GoodLeptonId; 
      vector<float> GoodLeptonPt; 
      vector<float> GoodLeptonEta; 
      vector<float> GoodLeptonPhi; 

      for(int i = 0; i < nMuon; i++){	
	if(Muon_pt[i] < 20) continue;
	if(abs(Muon_eta[i]) > 2.4) continue;	
	if (!( Muon_tightId[i] && Muon_pfRelIso03_all[i] < 0.25)) continue;
	GoodLeptonId.push_back(13 * Muon_charge[i]);
	GoodLeptonPt.push_back(Muon_pt[i]);
	GoodLeptonEta.push_back(Muon_eta[i]);
	GoodLeptonPhi.push_back(Muon_phi[i]);
	TLorentzVector thisMuon; thisMuon.SetPtEtaPhiM(Muon_pt[i], Muon_eta[i], Muon_phi[i], 0.106);
	GoodLeptons.push_back(thisMuon);
      }
      
      for(int i = 0; i < nElectron;  i++){	
	if(Electron_pt[i] < 20) continue;
	if(abs(Electron_eta[i]) > 2.5) continue;	
	if (!( Electron_mvaFall17V2Iso_WP80[i] )) continue;
	GoodLeptonId.push_back(11 * Electron_charge[i]);
	GoodLeptonPt.push_back(Electron_pt[i]);
	GoodLeptonEta.push_back(Electron_eta[i]);
	GoodLeptonPhi.push_back(Electron_phi[i]);
	TLorentzVector thisElectron; thisElectron.SetPtEtaPhiM(Electron_pt[i], Electron_eta[i], Electron_phi[i], 0.0005);
	GoodLeptons.push_back(thisElectron);
      }

      TLorentzVector lep1;
      TLorentzVector lep2;
      for (int i=0; i<GoodLeptonId.size();i++) {

	if (i==0) {
	  lep1Id = GoodLeptonId[i];
	  lep1Pt = GoodLeptonPt[i];
	  lep1Eta = GoodLeptonEta[i];
	  lep1Phi = GoodLeptonPhi[i];
	  lep1 = GoodLeptons[i];
	}
	if (i==1) {
	  lep2Id = GoodLeptonId[i];
	  lep2Pt = GoodLeptonPt[i];
	  lep2Eta = GoodLeptonEta[i];
	  lep2Phi = GoodLeptonPhi[i];
	  lep2 = GoodLeptons[i];
	}
	
      }

      dileptonMass = (lep1+lep2).M();
      MET = MET_pt;
      
      for(int i = 0; i < nJet ; i++) {
	if (Jet_pt[i] > 30 && fabs(Jet_eta[i]) < 2.5) NJets++;
	if (Jet_pt[i] > 30 && Jet_btagCSVV2[i] > 0.5803) NBTags++;
      }
     

      //***********************
      //Fill Event
      //***********************
      NEventsFilled++;
      outputTree->Fill();      
    }//end of event loop

    cout << "Filled Total of " << NEventsFilled << " Events\n";
    cout << "Writing output trees..." << endl;
    outFile->Write();
    outFile->Close();

}



