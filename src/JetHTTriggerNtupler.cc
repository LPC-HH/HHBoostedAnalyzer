#include "JetHTTriggerNtupler.h"
#include "JetTree.h"

//C++ includes

//ROOT includes
#include "TH1F.h"

using namespace std;

void JetHTTriggerNtupler::Analyze(bool isData, int Option, string outputfilename, string label, string pileupWeightName)
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
    float rho = -99;
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
 
    outputTree->Branch("rho", &rho, "rho/F");
    outputTree->Branch("fatJet1Pt", &fatJet1Pt, "fatJet1Pt/F");
    outputTree->Branch("fatJet1Eta", &fatJet1Eta, "fatJet1Eta/F");
    outputTree->Branch("fatJet1Phi", &fatJet1Phi, "fatJet1Phi/F");
    outputTree->Branch("fatJet1MassSD", &fatJet1MassSD, "fatJet1MassSD/F");
    outputTree->Branch("fatJet1DDBTagger", &fatJet1DDBTagger, "fatJet1DDBTagger/F");
    outputTree->Branch("fatJet1PNetXbb", &fatJet1PNetXbb, "fatJet1PNetXbb/F");
    outputTree->Branch("fatJet1Tau3OverTau2", &fatJet1Tau3OverTau2, "fatJet1Tau3OverTau2/F");
    outputTree->Branch("fatJet2Pt", &fatJet2Pt, "fatJet2Pt/F");
    outputTree->Branch("fatJet2Eta", &fatJet2Eta, "fatJet2Eta/F");
    outputTree->Branch("fatJet2Phi", &fatJet2Phi, "fatJet2Phi/F");
    outputTree->Branch("fatJet2MassSD", &fatJet2MassSD, "fatJet2MassSD/F");
    outputTree->Branch("fatJet2DDBTagger", &fatJet2DDBTagger, "fatJet2DDBTagger/F");
    outputTree->Branch("fatJet2PNetXbb", &fatJet2PNetXbb, "fatJet2PNetXbb/F");
    outputTree->Branch("fatJet2Tau3OverTau2", &fatJet2Tau3OverTau2, "fatJet2Tau3OverTau2/F");
  
    outputTree->Branch("HLT_PFHT1050",                                        &HLT_PFHT1050,                                       "HLT_PFHT1050/O");
    outputTree->Branch("HLT_AK8PFJet360_TrimMass30",                          &HLT_AK8PFJet360_TrimMass30,                         "HLT_AK8PFJet360_TrimMass30/O");
    outputTree->Branch("HLT_AK8PFJet380_TrimMass30",                          &HLT_AK8PFJet380_TrimMass30,                         "HLT_AK8PFJet380_TrimMass30/O");
    outputTree->Branch("HLT_AK8PFJet400_TrimMass30",                          &HLT_AK8PFJet400_TrimMass30,                         "HLT_AK8PFJet400_TrimMass30/O");
    outputTree->Branch("HLT_AK8PFJet420_TrimMass30",                          &HLT_AK8PFJet420_TrimMass30,                         "HLT_AK8PFJet420_TrimMass30/O");
    outputTree->Branch("HLT_AK8PFHT750_TrimMass50",                           &HLT_AK8PFHT750_TrimMass50,                          "HLT_AK8PFHT750_TrimMass50/O");
    outputTree->Branch("HLT_AK8PFHT800_TrimMass50",                           &HLT_AK8PFHT800_TrimMass50,                          "HLT_AK8PFHT800_TrimMass50/O");
    outputTree->Branch("HLT_AK8PFHT850_TrimMass50",                           &HLT_AK8PFHT850_TrimMass50,                          "HLT_AK8PFHT850_TrimMass50/O");
    outputTree->Branch("HLT_AK8PFHT900_TrimMass50",                           &HLT_AK8PFHT900_TrimMass50,                          "HLT_AK8PFHT900_TrimMass50/O");
    outputTree->Branch("HLT_PFJet450",                                        &HLT_PFJet450,                                       "HLT_PFJet450/O");
    outputTree->Branch("HLT_PFJet500",                                        &HLT_PFJet500,                                       "HLT_PFJet500/O");
    outputTree->Branch("HLT_PFJet550",                                        &HLT_PFJet550,                                       "HLT_PFJet550/O");
    outputTree->Branch("HLT_AK8PFJet450",                                     &HLT_AK8PFJet450,                                    "HLT_AK8PFJet450/O");
    outputTree->Branch("HLT_AK8PFJet500",                                     &HLT_AK8PFJet500,                                    "HLT_AK8PFJet500/O");
    outputTree->Branch("HLT_AK8PFJet550",                                     &HLT_AK8PFJet550,                                    "HLT_AK8PFJet550/O");
    outputTree->Branch("HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17",     &HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17,    "HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17/O");
    outputTree->Branch("HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1",      &HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1,     "HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1/O");
    outputTree->Branch("HLT_AK8PFJet330_PFAK8BTagCSV_p17",                    &HLT_AK8PFJet330_PFAK8BTagCSV_p17,                   "HLT_AK8PFJet330_PFAK8BTagCSV_p17/O");
    outputTree->Branch("HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02",  &HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02, "HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02/O");
    outputTree->Branch("HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2",  &HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2, "HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2/O");
    outputTree->Branch("HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4",  &HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4, "HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4/O"); 
    outputTree->Branch("HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p20",        &HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p20,       "HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p20/O");
    outputTree->Branch("HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p087",       &HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p087,      "HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p087/O");
    outputTree->Branch("HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p087",       &HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p087,      "HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p087/O");
    outputTree->Branch("HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20",     &HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20,    "HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20/O");
    outputTree->Branch("HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20",        &HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20,       "HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20/O");
    outputTree->Branch("HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20",        &HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20,       "HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20/O");	
    outputTree->Branch("HLT_IsoMu27", &HLT_IsoMu27, "HLT_IsoMu27/O");
    outputTree->Branch("HLT_IsoMu30", &HLT_IsoMu30, "HLT_IsoMu30/O");
    outputTree->Branch("HLT_Mu27", &HLT_Mu27, "HLT_Mu27/O");
    outputTree->Branch("HLT_Mu50", &HLT_Mu50, "HLT_Mu50/O");
    outputTree->Branch("HLT_Mu55", &HLT_Mu55, "HLT_Mu55/O");
        
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
      rho = fixedGridRhoFastjetAll;

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
      //-------find muon------------
      //------------------------------
      int muonIndex = -1;
      double tmpMuonPt = -999;

      //select highest pt muon passing ID+Iso
      for(unsigned int q = 0; q < nMuon; q++ ) {  
	if (!(Muon_pt[q] > 30)) continue;
	if (!(fabs(Muon_eta[q]) < 2.1)) continue;
	if (!Muon_tightId[q]) continue;
	if (!(Muon_pfRelIso03_all[q] / Muon_pt[q] < 0.15)) continue;
	
	if (Muon_pt[q] > tmpMuonPt) {
	  muonIndex = q;
	  tmpMuonPt = Muon_pt[q];
	}
      }

      //------------------------------
      //-------find leading fatJet------------
      //------------------------------
      int fatJetIndex = -1;
      int fatJet2Index = -1;
      double tmpFatJetPt = -999;
      double tmpFatJet2Pt = -999;

      for(unsigned int i = 0; i < nFatJet; i++ ) {       
	//Hbb fat jet pre-selection
	if (FatJet_pt[i] < 200) continue;
	if (!(muonIndex >= 0)) continue;
	if (deltaR(FatJet_eta[i], FatJet_phi[i], Muon_eta[muonIndex], Muon_phi[muonIndex]) < 1.5) continue;
	
	if (FatJet_pt[i] > tmpFatJetPt) {
	  fatJet2Index = fatJetIndex;
	  tmpFatJet2Pt = tmpFatJetPt;
	  fatJetIndex = i;
	  tmpFatJetPt = FatJet_pt[i];	  
	} else if (FatJet_pt[i] > tmpFatJet2Pt) {
	  fatJet2Index = i;
	  tmpFatJet2Pt = FatJet_pt[i];
	}
      }
     
      fatJet1Pt = FatJet_pt[fatJetIndex];
      fatJet1Eta = FatJet_eta[fatJetIndex];
      fatJet1Phi = FatJet_phi[fatJetIndex];
      fatJet1Mass = FatJet_mass[fatJetIndex];
      fatJet1MassSD = FatJet_msoftdrop[fatJetIndex];
      fatJet1DDBTagger = FatJet_btagDDBvL[fatJetIndex];
      fatJet1PNetXbb = FatJet_ParticleNetMD_probXbb[fatJetIndex]/(1.0 - FatJet_ParticleNetMD_probXcc[fatJetIndex] - FatJet_ParticleNetMD_probXqq[fatJetIndex]);
      fatJet1Tau3OverTau2 = FatJet_tau3[fatJetIndex] /  FatJet_tau2[fatJetIndex];
      fatJet2Pt = FatJet_pt[fatJet2Index];
      fatJet2Eta = FatJet_eta[fatJet2Index];
      fatJet2Phi = FatJet_phi[fatJet2Index];
      fatJet2Mass = FatJet_mass[fatJet2Index];
      fatJet2MassSD = FatJet_msoftdrop[fatJet2Index];
      fatJet2DDBTagger = FatJet_btagDDBvL[fatJet2Index];
      fatJet2PNetXbb = FatJet_ParticleNetMD_probXbb[fatJet2Index]/(1.0 - FatJet_ParticleNetMD_probXcc[fatJet2Index] - FatJet_ParticleNetMD_probXqq[fatJet2Index]);
      fatJet2Tau3OverTau2 = FatJet_tau3[fatJet2Index] /  FatJet_tau2[fatJet2Index];

      //****************************************************
      //Fill Event - skim for events with two jets found
      //****************************************************
      if (muonIndex>=0 && fatJetIndex >= 0) {
	NEventsFilled++;            
	outputTree->Fill();      
      }
    }//end of event loop

    cout << "Filled Total of " << NEventsFilled << " Events\n";
    cout << "Writing output trees..." << endl;
    outFile->Write();
    outFile->Close();

}



