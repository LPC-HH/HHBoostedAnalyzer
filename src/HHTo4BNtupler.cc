#include "HHTo4BNtupler.h"
#include "JetTree.h"

//C++ includes

//ROOT includes
#include "TH1F.h"

using namespace std;

void HHTo4BNtupler::Analyze(bool isData, int Option, string outputfilename, string label)
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

    float genHiggs1Pt = -1;
    float genHiggs1Eta = -1;
    float genHiggs1Phi = -1;
    float genHiggs2Pt = -1;
    float genHiggs2Eta = -1;
    float genHiggs2Phi = -1;
    float genHH_pt = -99;
    float genHH_eta = -99;
    float genHH_phi = -99;
    float genHH_mass = -99;
 
    int NJets = -1;
    float MET = -1;
    float fatJet1Pt = -99;
    float fatJet1Eta = -99;
    float fatJet1Phi = -99;
    float fatJet1Mass = -99;
    float fatJet1MassSD = -99;
    float fatJet1DDBTagger = -99;
    float fatJet1PNetXbb = -99;
    float fatJet1PNetQCDb = -99;
    float fatJet1PNetQCDbb = -99;
    float fatJet1PNetQCDothers = -99;
    int   fatJet1GenMatchIndex = -99;
    float fatJet1Tau3OverTau2 = -99;
    bool fatJet1HasMuon = 0;
    bool fatJet1HasElectron = 0;
    bool fatJet1HasBJetCSVLoose = 0;
    bool fatJet1HasBJetCSVMedium = 0;
    bool fatJet1HasBJetCSVTight = 0;
    float fatJet2Pt = -99;
    float fatJet2Eta = -99;
    float fatJet2Phi = -99;
    float fatJet2Mass = -99;
    float fatJet2MassSD = -99;
    float fatJet2DDBTagger = -99;
    float fatJet2PNetXbb = -99;
    float fatJet2PNetQCDb = -99;
    float fatJet2PNetQCDbb = -99;
    float fatJet2PNetQCDothers = -99;
    int   fatJet2GenMatchIndex = -99;
    float fatJet2Tau3OverTau2 = -99;
    bool fatJet2HasMuon = 0;
    bool fatJet2HasElectron = 0;
    bool fatJet2HasBJetCSVLoose = 0;
    bool fatJet2HasBJetCSVMedium = 0;
    bool fatJet2HasBJetCSVTight = 0;
    float hh_pt = -99;
    float hh_eta = -99;
    float hh_phi = -99;
    float hh_mass = -99;        
    float fatJet1PtOverMHH = -99;
    float fatJet1PtOverMSD = -99;
    float fatJet2PtOverMHH = -99;
    float fatJet2PtOverMSD = -99;
    float deltaEta_j1j2 = -99;
    float deltaPhi_j1j2 = -99;
    float deltaR_j1j2 = -99;    
    float ptj2_over_ptj1 = -99;
    float mj2_over_mj1 = -99;
   

    //------------------------
    //set branches on big tree
    //------------------------
    outputTree->Branch("weight", &weight, "weight/F");
    outputTree->Branch("run", &run, "run/i");
    outputTree->Branch("lumi", &luminosityBlock, "lumi/i");
    outputTree->Branch("event", &event, "event/l");
 
    outputTree->Branch("genHiggs1Pt", &genHiggs1Pt, "genHiggs1Pt/F");
    outputTree->Branch("genHiggs1Eta", &genHiggs1Eta, "genHiggs1Eta/F");
    outputTree->Branch("genHiggs1Phi", &genHiggs1Phi, "genHiggs1Phi/F");
    outputTree->Branch("genHiggs2Pt", &genHiggs2Pt, "genHiggs2Pt/F");
    outputTree->Branch("genHiggs2Eta", &genHiggs2Eta, "genHiggs2Eta/F");
    outputTree->Branch("genHiggs2Phi", &genHiggs2Phi, "genHiggs2Phi/F");
    outputTree->Branch("genHH_pt",      &genHH_pt,     "genHH_pt/F");
    outputTree->Branch("genHH_eta",     &genHH_eta,    "genHH_eta/F");
    outputTree->Branch("genHH_phi",     &genHH_phi,    "genHH_phi/F");
    outputTree->Branch("genHH_mass",    &genHH_mass,   "genHH_mass/F");
	
    outputTree->Branch("NJets", &NJets, "NJets/I");
    outputTree->Branch("MET", &MET, "MET/F");
    outputTree->Branch("fatJet1Pt", &fatJet1Pt, "fatJet1Pt/F");
    outputTree->Branch("fatJet1Eta", &fatJet1Eta, "fatJet1Eta/F");
    outputTree->Branch("fatJet1Phi", &fatJet1Phi, "fatJet1Phi/F");
    outputTree->Branch("fatJet1Mass", &fatJet1Mass, "fatJet1Mass/F");
    outputTree->Branch("fatJet1MassSD", &fatJet1MassSD, "fatJet1MassSD/F");
    outputTree->Branch("fatJet1DDBTagger", &fatJet1DDBTagger, "fatJet1DDBTagger/F");
    outputTree->Branch("fatJet1PNetXbb", &fatJet1PNetXbb, "fatJet1PNetXbb/F");
    outputTree->Branch("fatJet1PNetQCDb", &fatJet1PNetQCDb, "fatJet1PNetQCDb/F");
    outputTree->Branch("fatJet1PNetQCDbb", &fatJet1PNetQCDbb, "fatJet1PNetQCDbb/F");
    outputTree->Branch("fatJet1PNetQCDothers", &fatJet1PNetQCDothers, "fatJet1PNetQCDothers/F");
    outputTree->Branch("fatJet1GenMatchIndex", &fatJet1GenMatchIndex, "fatJet1GenMatchIndex/I");
    outputTree->Branch("fatJet1Tau3OverTau2", &fatJet1Tau3OverTau2, "fatJet1Tau3OverTau2/F");
    outputTree->Branch("fatJet1HasMuon", &fatJet1HasMuon, "fatJet1HasMuon/O");
    outputTree->Branch("fatJet1HasElectron", &fatJet1HasElectron, "fatJet1HasElectron/O");
    outputTree->Branch("fatJet1HasBJetCSVLoose", &fatJet1HasBJetCSVLoose, "fatJet1HasBJetCSVLoose/O");
    outputTree->Branch("fatJet1HasBJetCSVMedium", &fatJet1HasBJetCSVMedium, "fatJet1HasBJetCSVMedium/O");
    outputTree->Branch("fatJet1HasBJetCSVTight", &fatJet1HasBJetCSVTight, "fatJet1HasBJetCSVTight/O");
    outputTree->Branch("fatJet2Pt", &fatJet2Pt, "fatJet2Pt/F");
    outputTree->Branch("fatJet2Eta", &fatJet2Eta, "fatJet2Eta/F");
    outputTree->Branch("fatJet2Phi", &fatJet2Phi, "fatJet2Phi/F"); 
    outputTree->Branch("fatJet2Mass", &fatJet2Mass, "fatJet2Mass/F");
    outputTree->Branch("fatJet2MassSD", &fatJet2MassSD, "fatJet2MassSD/F");
    outputTree->Branch("fatJet2DDBTagger", &fatJet2DDBTagger, "fatJet2DDBTagger/F");
    outputTree->Branch("fatJet2PNetXbb", &fatJet2PNetXbb, "fatJet2PNetXbb/F");
    outputTree->Branch("fatJet2PNetQCDb", &fatJet2PNetQCDb, "fatJet2PNetQCDb/F");
    outputTree->Branch("fatJet2PNetQCDbb", &fatJet2PNetQCDbb, "fatJet2PNetQCDbb/F");
    outputTree->Branch("fatJet2PNetQCDothers", &fatJet2PNetQCDothers, "fatJet2PNetQCDothers/F");
    outputTree->Branch("fatJet2GenMatchIndex", &fatJet2GenMatchIndex, "fatJet2GenMatchIndex/I");
    outputTree->Branch("fatJet2Tau3OverTau2", &fatJet2Tau3OverTau2, "fatJet2Tau3OverTau2/F");
    outputTree->Branch("fatJet2HasMuon", &fatJet2HasMuon, "fatJet2HasMuon/O");
    outputTree->Branch("fatJet2HasElectron", &fatJet2HasElectron, "fatJet2HasElectron/O");
    outputTree->Branch("fatJet2HasBJetCSVLoose", &fatJet2HasBJetCSVLoose, "fatJet2HasBJetCSVLoose/O");
    outputTree->Branch("fatJet2HasBJetCSVMedium", &fatJet2HasBJetCSVMedium, "fatJet2HasBJetCSVMedium/O");
    outputTree->Branch("fatJet2HasBJetCSVTight", &fatJet2HasBJetCSVTight, "fatJet2HasBJetCSVTight/O");
    outputTree->Branch("hh_pt",      &hh_pt,     "hh_pt/F");
    outputTree->Branch("hh_eta",     &hh_eta,    "hh_eta/F");
    outputTree->Branch("hh_phi",     &hh_phi,    "hh_phi/F");
    outputTree->Branch("hh_mass",    &hh_mass,   "hh_mass/F");
    outputTree->Branch("fatJet1PtOverMHH",    &fatJet1PtOverMHH,   "fatJet1PtOverMHH/F");
    outputTree->Branch("fatJet1PtOverMSD",    &fatJet1PtOverMSD,   "fatJet1PtOverMSD/F");
    outputTree->Branch("fatJet2PtOverMHH",    &fatJet2PtOverMHH,   "fatJet2PtOverMHH/F");
    outputTree->Branch("fatJet2PtOverMSD",    &fatJet2PtOverMSD,   "fatJet2PtOverMSD/F");
    outputTree->Branch("deltaEta_j1j2",    &deltaEta_j1j2,   "deltaEta_j1j2/F");
    outputTree->Branch("deltaPhi_j1j2",    &deltaPhi_j1j2,   "deltaPhi_j1j2/F");
    outputTree->Branch("deltaR_j1j2",    &deltaR_j1j2,   "deltaR_j1j2/F");
    outputTree->Branch("ptj2_over_ptj1",    &ptj2_over_ptj1,   "ptj2_over_ptj1/F");
    outputTree->Branch("mj2_over_mj1",    &mj2_over_mj1,   "mj2_over_mj1/F");
  
    //PFHT800 and PFHT900 only exists in 2016 data
    // outputTree->Branch("HLT_PFHT800",                                        &HLT_PFHT800,                                       "HLT_PFHT800/O");
    // outputTree->Branch("HLT_PFHT900",                                        &HLT_PFHT900,                                       "HLT_PFHT900/O");
    outputTree->Branch("HLT_PFHT1050",                                        &HLT_PFHT1050,                                       "HLT_PFHT1050/O");
    outputTree->Branch("HLT_AK8PFJet360_TrimMass30",                          &HLT_AK8PFJet360_TrimMass30,                         "HLT_AK8PFJet360_TrimMass30/O");
    outputTree->Branch("HLT_AK8PFJet380_TrimMass30",                          &HLT_AK8PFJet380_TrimMass30,                         "HLT_AK8PFJet380_TrimMass30/O");
    outputTree->Branch("HLT_AK8PFJet400_TrimMass30",                          &HLT_AK8PFJet400_TrimMass30,                         "HLT_AK8PFJet400_TrimMass30/O");
    outputTree->Branch("HLT_AK8PFJet420_TrimMass30",                          &HLT_AK8PFJet420_TrimMass30,                         "HLT_AK8PFJet420_TrimMass30/O");
    outputTree->Branch("HLT_AK8PFHT800_TrimMass50",                           &HLT_AK8PFHT800_TrimMass50,                          "HLT_AK8PFHT800_TrimMass50/O");
    outputTree->Branch("HLT_PFJet450",                                        &HLT_PFJet450,                                       "HLT_PFJet450/O");
    outputTree->Branch("HLT_PFJet500",                                        &HLT_PFJet500,                                       "HLT_PFJet500/O");
    outputTree->Branch("HLT_AK8PFJet500",                                     &HLT_AK8PFJet500,                                    "HLT_AK8PFJet500/O");
    outputTree->Branch("HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17",     &HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17,    "HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17/O");
    outputTree->Branch("HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1",      &HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1,     "HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1/O");
    outputTree->Branch("HLT_AK8PFJet330_PFAK8BTagCSV_p17",                    &HLT_AK8PFJet330_PFAK8BTagCSV_p17,                   "HLT_AK8PFJet330_PFAK8BTagCSV_p17/O");
    outputTree->Branch("HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02",                    &HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02,                   "HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02/O");
    outputTree->Branch("HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2",                    &HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2,                   "HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2/O");
    outputTree->Branch("HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4",                    &HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4,                   "HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4/O");
  
    cout << "Run With Option = " << Option << "\n";
    
    if (Option == 1) cout << "Option = 1 : Select FatJets with pT > 200 GeV and DDB > 0.8 only\n";
    if (Option == 10) cout << "Option = 10 : Select FatJets with pT > 200 GeV and tau3/tau2 < 0.54 only\n";

    UInt_t NEventsFilled = 0;
 
    //begin loop
    if (fChain == 0) return;
    UInt_t nentries = fChain->GetEntries();
    Long64_t nbytes = 0, nb = 0;

    cout << "nentries = " << nentries << "\n";
    for (UInt_t jentry=0; jentry<nentries;jentry++) {
      //begin event
      if(jentry % 1000 == 0) cout << "Processing entry " << jentry << endl;
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;


      //fill normalization histogram
      weight = genWeight / fabs(genWeight);
      NEvents->SetBinContent( 1, NEvents->GetBinContent(1) + weight);


      //reset tree variables
      genHiggs1Pt = -99.0;
      genHiggs1Eta = -99.0;
      genHiggs1Phi = -99.0;
      genHiggs2Pt = -99.0;
      genHiggs2Eta = -99.0;
      genHiggs2Phi = -99.0;
      genHH_pt = -99;
      genHH_eta = -99;
      genHH_phi = -99;
      genHH_mass = -99;   
      NJets = -1;
      MET = -99.0;

      fatJet1Pt = -99.0;
      fatJet1Eta = -99.0;
      fatJet1Phi = -99.0;
      fatJet1Mass = -99.0;
      fatJet1MassSD = -99.0;
      fatJet1DDBTagger = -99.0;
      fatJet1PNetXbb = -99;
      fatJet1PNetQCDb = -99;
      fatJet1PNetQCDbb = -99;
      fatJet1PNetQCDothers = -99;
      fatJet1GenMatchIndex = -99.0;
      fatJet1Tau3OverTau2 = -99;
      fatJet1HasMuon = 0;
      fatJet1HasElectron = 0;
      fatJet1HasBJetCSVLoose = 0;
      fatJet1HasBJetCSVMedium = 0;
      fatJet1HasBJetCSVTight = 0;
      fatJet2Pt = -99.0;
      fatJet2Eta = -99.0;
      fatJet2Phi = -99.0;
      fatJet2Mass = -99.0;
      fatJet2MassSD = -99.0;
      fatJet2DDBTagger = -99.0;
      fatJet2PNetXbb = -99;
      fatJet2PNetQCDb = -99;
      fatJet2PNetQCDbb = -99;
      fatJet2PNetQCDothers = -99;
      fatJet2GenMatchIndex = -99.0;
      fatJet2Tau3OverTau2 = -99;
      fatJet2HasMuon = 0;
      fatJet2HasElectron = 0;
      fatJet2HasBJetCSVLoose = 0;
      fatJet2HasBJetCSVMedium = 0;
      fatJet2HasBJetCSVTight = 0;
      hh_pt = -99;
      hh_eta = -99;
      hh_phi = -99;
      hh_mass = -99;
      fatJet1PtOverMHH = -99;
      fatJet1PtOverMSD = -99;
      fatJet2PtOverMHH = -99;
      fatJet2PtOverMSD = -99;
      deltaEta_j1j2 = -99;
      deltaPhi_j1j2 = -99;
      deltaR_j1j2 = -99;    
      ptj2_over_ptj1 = -99;
      mj2_over_mj1 = -99;
              

      //------------------------------
      //----Event variables------------
      //------------------------------
      MET = MET_pt;

      //------------------------------
      //----find gen-higgs------------
      //------------------------------
      int current_mIndex = -1;
      std::vector< TLorentzVector > genHiggsVector;
      if (!isData) {

	for(int i = 0; i < nGenPart; i++) {
	  if( abs(GenPart_pdgId[i]) == 5  && GenPart_pdgId[GenPart_genPartIdxMother[i]] == 25 && current_mIndex != GenPart_genPartIdxMother[i] ) {
	    //std::cout << GenPart_genPartIdxMother[i] << std::endl;
	    // std::cout << "mother: " << GenPart_pdgId[GenPart_genPartIdxMother[i]]
	    // << " PT: " << GenPart_pt[GenPart_genPartIdxMother[i]]
	    // << " eta: " << GenPart_eta[GenPart_genPartIdxMother[i]]
	    // << " phi: " << GenPart_phi[GenPart_genPartIdxMother[i]] << std::endl;
	    TLorentzVector h;
	    h.SetPtEtaPhiM( GenPart_pt[GenPart_genPartIdxMother[i]], GenPart_eta[GenPart_genPartIdxMother[i]], GenPart_phi[GenPart_genPartIdxMother[i]], GenPart_mass[GenPart_genPartIdxMother[i]] );
	    genHiggsVector.push_back(h);
	    current_mIndex = GenPart_genPartIdxMother[i];
	  }
	}

	if(genHiggsVector.size() >= 1) {
	  //filling tree_out variables
	  genHiggs1Pt = genHiggsVector[0].Pt();
	  genHiggs1Eta = genHiggsVector[0].Eta();
	  genHiggs1Phi = genHiggsVector[0].Phi();
	  //
	  if(genHiggsVector.size() >= 2) {
	    genHiggs2Pt = genHiggsVector[1].Pt();
	    genHiggs2Eta = genHiggsVector[1].Eta();
	    genHiggs2Phi = genHiggsVector[1].Phi();	
	  }
	}

	//gen level
	if(genHiggsVector.size() > 1) { 
	  genHH_pt = (genHiggsVector[0]+genHiggsVector[1]).Pt();
	  genHH_eta = (genHiggsVector[0]+genHiggsVector[1]).Eta();
	  genHH_phi = (genHiggsVector[0]+genHiggsVector[1]).Phi();
	  genHH_mass= (genHiggsVector[0]+genHiggsVector[1]).M();
	}
      
      } //end if !data

      //------------------------------
      //-------find fatJet------------
      //------------------------------
      vector<int> selectedFatJetIndices;

      for(unsigned int i = 0; i < nAK15Puppi; i++ ) {       
	//Hbb fat jet pre-selection
	if (AK15Puppi_pt[i] < 200) continue;

	//Select signal region with jets having DDB > 0.8
	// if (Option == 1) {
	//   if (!(FatJet_btagDDBvL[i] > 0.80)) continue;
	// } 
	if (Option == 2) {
	  if (!(AK15Puppi_ParticleNetMD_probXbb[i]/(1.0 - AK15Puppi_ParticleNetMD_probXcc[i] - AK15Puppi_ParticleNetMD_probXqq[i]) > 0.80)) continue;
	} 
	
	//Select ttbar control region with jets 
	if (Option == 10) {
	  if (!(AK15Puppi_tau3[i] / AK15Puppi_tau2[i] < 0.54 )) continue;
	} 
	selectedFatJetIndices.push_back(i);
      }

      //------------------------------------------------------
      //----------select the two H candidates with largest pT
      //------------------------------------------------------
      int fatJet1Index = -1;
      int fatJet2Index = -1;
      double tmpfatJet1Pt = -999;
      double tmpfatJet2Pt = -999;
      for(unsigned int i = 0; i < selectedFatJetIndices.size(); i++ ) {
	if (AK15Puppi_pt[selectedFatJetIndices[i]] > tmpfatJet1Pt) {
	  tmpfatJet2Pt = fatJet1Pt;
	  fatJet2Index = fatJet1Index;
	  tmpfatJet1Pt = AK15Puppi_pt[selectedFatJetIndices[i]];
	  fatJet1Index = selectedFatJetIndices[i];
	} else if (AK15Puppi_pt[selectedFatJetIndices[i]] > tmpfatJet2Pt) {
	  tmpfatJet2Pt = AK15Puppi_pt[selectedFatJetIndices[i]];
	  fatJet2Index = selectedFatJetIndices[i];
	}
      }

      //------------------------------------------------------
      //----------Fill higgs candidate information
      //------------------------------------------------------
   
      TLorentzVector Higgs1Jet;
      Higgs1Jet.SetPtEtaPhiM(AK15Puppi_pt[fatJet1Index],AK15Puppi_eta[fatJet1Index],AK15Puppi_phi[fatJet1Index],AK15Puppi_msoftdrop[fatJet1Index]);
      float Higgs1MinDR = 999.;
      int Higgs1_match_idx = -1;
      for( int j = 0; j < genHiggsVector.size(); j++) {
	if(Higgs1Jet.DeltaR(genHiggsVector[j]) < Higgs1MinDR) {
	  Higgs1MinDR = Higgs1Jet.DeltaR(genHiggsVector[j]);
	  Higgs1_match_idx = j;
	}
      }
      fatJet1Pt = AK15Puppi_pt[fatJet1Index];
      fatJet1Eta = AK15Puppi_eta[fatJet1Index];
      fatJet1Phi = AK15Puppi_phi[fatJet1Index];
      fatJet1Mass = AK15Puppi_mass[fatJet1Index];
      fatJet1MassSD = AK15Puppi_msoftdrop[fatJet1Index];
      // fatJet1DDBTagger = FatJet_btagDDBvL[fatJet1Index];
      fatJet1PNetXbb = AK15Puppi_ParticleNetMD_probXbb[fatJet1Index]/(1.0 - AK15Puppi_ParticleNetMD_probXcc[fatJet1Index] - AK15Puppi_ParticleNetMD_probXqq[fatJet1Index]);
      // fatJet1PNetQCDb = AK15Puppi_ParticleNetMD_probQCDb[fatJet1Index];
      // fatJet1PNetQCDbb = AK15Puppi_ParticleNetMD_probQCDbb[fatJet1Index];
      fatJet1PNetQCDothers = AK15Puppi_ParticleNetMD_probQCD[fatJet1Index];

      if(Higgs1MinDR < 0.4) {
	fatJet1GenMatchIndex = Higgs1_match_idx;
      }
      fatJet1Tau3OverTau2 = AK15Puppi_tau3[fatJet1Index] /  AK15Puppi_tau2[fatJet1Index];
      //find muon inside jet
      for(unsigned int q = 0; q < nMuon; q++ ) {       
	if (Muon_looseId[q] && 
	    deltaR(fatJet1Eta , fatJet1Phi, Muon_eta[q], Muon_phi[q]) < 1.5
	    ) {
	  fatJet1HasMuon = true;
	  break;
	}
      }
      //find electron inside jet
      for(unsigned int q = 0; q < nElectron; q++ ) {       
	if (Electron_mvaFall17V2noIso_WP90[q] && 
	    deltaR(fatJet1Eta , fatJet1Phi, Electron_eta[q], Electron_phi[q]) < 1.5
	    ) {
	  fatJet1HasElectron = true;
	  break;
	}
      }
      //find loose b-tagged jet inside jet
      for(unsigned int q = 0; q < nJet; q++ ) {       
	if (Jet_btagDeepB[q] > 0.0521 && 
	    deltaR(fatJet1Eta , fatJet1Phi, Jet_eta[q], Jet_phi[q]) < 1.5
	    ) {
	  fatJet1HasBJetCSVLoose = true;
	  break;
	}
      }
     //find medium b-tagged jet inside jet
      for(unsigned int q = 0; q < nJet; q++ ) {       
	if (Jet_btagDeepB[q] > 0.3033 && 
	    deltaR(fatJet1Eta , fatJet1Phi, Jet_eta[q], Jet_phi[q]) < 1.5
	    ) {
	  fatJet1HasBJetCSVMedium = true;
	  break;
	}
      }
      //find tight b-tagged jet inside jet
      for(unsigned int q = 0; q < nJet; q++ ) {       
	if (Jet_btagDeepB[q] > 0.7489 && 
	    deltaR(fatJet1Eta , fatJet1Phi, Jet_eta[q], Jet_phi[q]) < 1.5
	    ) {
	  fatJet1HasBJetCSVTight = true;
	  break;
	}
      }



      TLorentzVector Higgs2Jet;
      Higgs2Jet.SetPtEtaPhiM(FatJet_pt[fatJet2Index],FatJet_eta[fatJet2Index],FatJet_phi[fatJet2Index],FatJet_msoftdrop[fatJet2Index]);
      float Higgs2MinDR = 999.;
      int Higgs2_match_idx = -1;
      for( int j = 0; j < genHiggsVector.size(); j++) {
	if(Higgs2Jet.DeltaR(genHiggsVector[j]) < Higgs2MinDR) {
	  Higgs2MinDR = Higgs2Jet.DeltaR(genHiggsVector[j]);
	  Higgs2_match_idx = j;
	}
      }
     
      fatJet2Pt = AK15Puppi_pt[fatJet2Index];
      fatJet2Eta = AK15Puppi_eta[fatJet2Index];
      fatJet2Phi = AK15Puppi_phi[fatJet2Index];
      fatJet2Mass = AK15Puppi_mass[fatJet2Index];
      fatJet2MassSD = AK15Puppi_msoftdrop[fatJet2Index];
      // fatJet2DDBTagger = AK15Puppi_btagDDBvL[fatJet2Index];
      fatJet2PNetXbb = AK15Puppi_ParticleNetMD_probXbb[fatJet2Index]/(1.0 - AK15Puppi_ParticleNetMD_probXcc[fatJet2Index] - AK15Puppi_ParticleNetMD_probXqq[fatJet2Index]);
      // fatJet2PNetQCDb = AK15Puppi_ParticleNetMD_probQCDb[fatJet2Index];
      // fatJet2PNetQCDbb = AK15Puppi_ParticleNetMD_probQCDbb[fatJet2Index];
      fatJet2PNetQCDothers = AK15Puppi_ParticleNetMD_probQCD[fatJet2Index];

      if(Higgs2MinDR < 0.4) {
	fatJet2GenMatchIndex = Higgs2_match_idx;
      }
      fatJet2Tau3OverTau2 = AK15Puppi_tau3[fatJet2Index] /  AK15Puppi_tau2[fatJet2Index];
      
      //find muon inside jet
      for(unsigned int q = 0; q < nMuon; q++ ) {       
	if (Muon_looseId[q] && 
	    deltaR(fatJet2Eta , fatJet2Phi, Muon_eta[q], Muon_phi[q]) < 1.5
	    ) {
	  fatJet2HasMuon = true;
	  break;
	}
      }
      //find electron inside jet
      for(unsigned int q = 0; q < nElectron; q++ ) {       
	if (Electron_mvaFall17V2noIso_WP90[q] && 
	    deltaR(fatJet2Eta , fatJet2Phi, Electron_eta[q], Electron_phi[q]) < 1.5
	    ) {
	  fatJet2HasElectron = true;
	  break;
	}
      }
      //find loose b-tagged jet inside jet
      for(unsigned int q = 0; q < nJet; q++ ) {       
	if (Jet_btagDeepB[q] > 0.0521 && 
	    deltaR(fatJet2Eta , fatJet2Phi, Jet_eta[q], Jet_phi[q]) < 1.5
	    ) {
	  fatJet2HasBJetCSVLoose = true;
	  break;
	}
      }
      //find medium b-tagged jet inside jet
      for(unsigned int q = 0; q < nJet; q++ ) {       
	if (Jet_btagDeepB[q] > 0.3033 && 
	    deltaR(fatJet2Eta , fatJet2Phi, Jet_eta[q], Jet_phi[q]) < 1.5
	    ) {
	  fatJet2HasBJetCSVMedium = true;
	  break;
	}
      }
      //find tight b-tagged jet inside jet
      for(unsigned int q = 0; q < nJet; q++ ) {       
	if (Jet_btagDeepB[q] > 0.7489 && 
	    deltaR(fatJet2Eta , fatJet2Phi, Jet_eta[q], Jet_phi[q]) < 1.5
	    ) {
	  fatJet2HasBJetCSVTight = true;
	  break;
	}
      }

      //filling hh candidate variable
      hh_pt = (Higgs1Jet+Higgs2Jet).Pt();
      hh_eta = (Higgs1Jet+Higgs2Jet).Eta();
      hh_phi = (Higgs1Jet+Higgs2Jet).Phi();
      hh_mass = (Higgs1Jet+Higgs2Jet).M();      
    
      fatJet1PtOverMHH = fatJet1Pt / hh_mass;
      fatJet1PtOverMSD = fatJet1Pt / fatJet1MassSD;
      fatJet2PtOverMHH = fatJet2Pt / hh_mass;
      fatJet2PtOverMSD = fatJet2Pt / fatJet1MassSD;
      deltaEta_j1j2 = fabs(fatJet1Eta - fatJet2Eta);
      deltaPhi_j1j2 = deltaPhi(fatJet1Phi, fatJet2Phi);
      deltaR_j1j2 = deltaR(fatJet1Eta, fatJet1Phi, fatJet2Eta, fatJet2Phi);
      ptj2_over_ptj1 = fatJet2Pt / fatJet1Pt;
      mj2_over_mj1 = fatJet2MassSD / fatJet1MassSD;             


      //***********************
      //Count additional jets 
      //***********************
      for(int i = 0; i < nJet; i++) {
	if (Jet_pt[i] > 30 && fabs(Jet_eta[i]) < 2.5
	    && deltaR(Jet_eta[i] , Jet_phi[i], fatJet1Eta, fatJet1Phi) > 1.5
	    && deltaR(Jet_eta[i] , Jet_phi[i], fatJet2Eta, fatJet2Phi) > 1.5
	    ) {
	  NJets++;
	}
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



