//================================================================================================
//
// Simple Example
//
//root -l macros/SelectTTBarDileptonControlSample.C+
//
//________________________________________________________________________________________________


#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TROOT.h>                  // access to gROOT, entry point to ROOT system
#include <TSystem.h>                // interface to OS
#include <TFile.h>                  // file handle class
#include <TTree.h>                  // class to access ntuples
#include <TClonesArray.h>           // ROOT array class
#include <vector>                   // STL vector class
#include <iostream>                 // standard I/O
#include <iomanip>                  // functions to format standard I/O
#include <fstream>                  // functions for file I/O
#include <string>                   // C++ string class
#include <sstream>                  // class for parsing strings
#include <TH1D.h>                
#include <TH1F.h>                
#include <TH2F.h>                
#include <TCanvas.h>                
#include <TLegend.h> 
#include <THStack.h> 

#include "HHBoostedAnalyzer/macros/tdrstyle.C"
#include "HHBoostedAnalyzer/macros/CMS_lumi.C"
#include "HHBoostedAnalyzer/macros/EfficiencyUtils.hh"

#endif



//=== MAIN MACRO ================================================================================================= 


void RunMeasureJetHTTriggerEfficiency(  vector<string> datafiles, double lumi, string option, int channelOption = -1, string label = "") {
  
  string Label = "";
  if (label != "") Label = "_" + label;

  //--------------------------------------------------------------------------------------------------------------
  // Settings 
  //============================================================================================================== 

  //*****************************************************************************************
  //Make some histograms
  //*****************************************************************************************

  TH2F *histJetPtMass_Denominator = new TH2F("histJetPtMass_Denominator", "; AK8 Mass [GeV] ; AK8 Jet p_{T} [GeV] ; Efficiency", 15, 0, 300, 200, 0, 1000);
  TH2F *histJetPtMass_Denominator_Xbb0p0To0p9 = new TH2F("histJetPtMass_Denominator_Xbb0p0To0p9", "; AK8 Mass [GeV] ; AK8 Jet p_{T} [GeV] ; Efficiency", 15, 0, 300, 200, 0, 1000);
  TH2F *histJetPtMass_Denominator_Xbb0p9To0p95 = new TH2F("histJetPtMass_Denominator_Xbb0p9To0p95", "; AK8 Mass [GeV] ; AK8 Jet p_{T} [GeV] ; Efficiency", 15, 0, 300, 200, 0, 1000);
  TH2F *histJetPtMass_Denominator_Xbb0p95To0p98 = new TH2F("histJetPtMass_Denominator_Xbb0p95To0p98", "; AK8 Mass [GeV] ; AK8 Jet p_{T} [GeV] ; Efficiency", 15, 0, 300, 200, 0, 1000);
  TH2F *histJetPtMass_Denominator_Xbb0p98To1p0 = new TH2F("histJetPtMass_Denominator_Xbb0p98To1p0", "; AK8 Mass [GeV] ; AK8 Jet p_{T} [GeV] ; Efficiency", 15, 0, 300, 200, 0, 1000);
  TH1F *histJetPt_Denominator = new TH1F("histJetPt_Denominator", "; AK8 Jet p_{T} [GeV] ; Efficiency", 100, 0, 1000);
  TH1F *histJetMass_Denominator = new TH1F("histJetMass_Denominator", "; AK8 Mass [GeV] ; Efficiency", 100, 0, 500);
  TH1F *histJetPNetXbb_Denominator = new TH1F("histJetPNetXbb_Denominator", "; AK8 Jet PNet Xbb Prob ; Efficiency", 100, 0, 1.0);

  TH2F *histJetPtMass_Numerator = new TH2F("histJetPtMass_Numerator", "; AK8 Mass [GeV] ; AK8 Jet p_{T} [GeV] ; Efficiency", 15, 0, 300, 200, 0, 1000);
  TH2F *histJetPtMass_Numerator_Xbb0p0To0p9 = new TH2F("histJetPtMass_Numerator_Xbb0p0To0p9", "; AK8 Mass [GeV] ; AK8 Jet p_{T} [GeV] ; Efficiency", 15, 0, 300, 200, 0, 1000);
  TH2F *histJetPtMass_Numerator_Xbb0p9To0p95 = new TH2F("histJetPtMass_Numerator_Xbb0p9To0p95", "; AK8 Mass [GeV] ; AK8 Jet p_{T} [GeV] ; Efficiency", 15, 0, 300, 200, 0, 1000);
  TH2F *histJetPtMass_Numerator_Xbb0p95To0p98 = new TH2F("histJetPtMass_Numerator_Xbb0p95To0p98", "; AK8 Mass [GeV] ; AK8 Jet p_{T} [GeV] ; Efficiency", 15, 0, 300, 200, 0, 1000);
  TH2F *histJetPtMass_Numerator_Xbb0p98To1p0 = new TH2F("histJetPtMass_Numerator_Xbb0p98To1p0", "; AK8 Mass [GeV] ; AK8 Jet p_{T} [GeV] ; Efficiency", 15, 0, 300, 200, 0, 1000);
  TH1F *histJetPt_Numerator = new TH1F("histJetPt_Numerator", "; AK8 Jet p_{T} [GeV] ; Efficiency", 100, 0, 1000);
  TH1F *histJetMass_Numerator = new TH1F("histJetMass_Numerator", "; AK8 Mass [GeV] ; Efficiency", 100, 0, 500);
  TH1F *histJetPNetXbb_Numerator = new TH1F("histJetPNetXbb_Numerator", "; AK8 Jet PNet Xbb Prob ; Efficiency", 100, 0, 1.0);

  histJetPt_Denominator->Sumw2();
  histJetMass_Denominator->Sumw2();
  histJetPNetXbb_Denominator->Sumw2();
  histJetPtMass_Denominator->Sumw2();
  histJetPtMass_Denominator_Xbb0p0To0p9->Sumw2();
  histJetPtMass_Denominator_Xbb0p9To0p95->Sumw2();
  histJetPtMass_Denominator_Xbb0p95To0p98->Sumw2();
  histJetPtMass_Denominator_Xbb0p98To1p0->Sumw2();
  histJetPt_Numerator->Sumw2();
  histJetMass_Numerator->Sumw2();
  histJetPNetXbb_Numerator->Sumw2();
  histJetPtMass_Numerator->Sumw2();
  histJetPtMass_Numerator_Xbb0p0To0p9->Sumw2();
  histJetPtMass_Numerator_Xbb0p9To0p95->Sumw2();
  histJetPtMass_Numerator_Xbb0p95To0p98->Sumw2();
  histJetPtMass_Numerator_Xbb0p98To1p0->Sumw2();

  //*******************************************************************************************
  //Read file
  //*******************************************************************************************                
  for (uint i=0; i < datafiles.size(); ++i) {
    
    TFile *file = new TFile(datafiles[i].c_str(),"READ");
    TTree *tree = 0;
    if (!file) {
      cout << "Input file " << datafiles[i] << " could not be opened\n"; 
      continue;
    } else {
      tree = (TTree*)file->Get("tree");
    }
    if (!tree) {
      cout << "Tree could not be found in input file " << datafiles[i] << "\n"; 
      continue;
    }
    
    float weight = 0;
    float MET = 0;
    float fatJet1Pt = 0;
    float fatJet1Eta = 0;
    float fatJet1MassSD = 0;
    float fatJet1DDBTagger = 0;
    float fatJet1PNetXbb = -99;
    float fatJet1PNetQCDb = -99;
    float fatJet1PNetQCDbb = -99;
    float fatJet1PNetQCDothers = -99;
    float fatJet1Tau3OverTau2 = -99;
    bool fatJet1HasMuon = 0;
    bool fatJet1HasElectron = 0;
    bool fatJet1HasBJetCSVLoose = 0;
    bool fatJet1HasBJetCSVMedium = 0;
    bool fatJet1HasBJetCSVTight = 0;      
    float fatJet2Pt = 0;
    float fatJet2MassSD = 0;
    float fatJet2DDBTagger = 0;
    float fatJet2PNetXbb = -99;
    float fatJet2PNetQCDb = -99;
    float fatJet2PNetQCDbb = -99;
    float fatJet2PNetQCDothers = -99;
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

    bool HLT_PFHT790 = false;                                     
    bool HLT_PFHT890 = false;                                     
    bool HLT_PFHT1050 = false;                                     
    bool HLT_AK8PFJet360_TrimMass30 = false;                             
    bool HLT_AK8PFJet380_TrimMass30 = false;                             
    bool HLT_AK8PFJet400_TrimMass30 = false;                             
    bool HLT_AK8PFJet420_TrimMass30 = false;                             
    bool HLT_AK8PFHT750_TrimMass50 = false;                         
    bool HLT_AK8PFHT800_TrimMass50 = false;                         
    bool HLT_AK8PFHT850_TrimMass50 = false;                         
    bool HLT_AK8PFHT900_TrimMass50 = false;                         
    bool HLT_PFJet450 = false;                                           
    bool HLT_PFJet500 = false;                                           
    bool HLT_PFJet550 = false;                                           
    bool HLT_AK8PFJet400 = false;                                   
    bool HLT_AK8PFJet450 = false;                                   
    bool HLT_AK8PFJet500 = false;                                   
    bool HLT_AK8PFJet550 = false;                                   
    bool HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17 = false;   
    bool HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1 = false;    
    bool HLT_AK8PFJet330_PFAK8BTagCSV_p1 = false;                  
    bool HLT_AK8PFJet330_PFAK8BTagCSV_p17 = false;                  
    bool HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02 = false; 
    bool HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2 = false;      
    bool HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4 = false;
    bool HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p20 = false;
    bool HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p087 = false;
    bool HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p087 = false;
    bool HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20 = false;
    bool HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20 = false;
    bool HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20	 = false;
    bool HLT_IsoMu27 = false;
    bool HLT_IsoMu30 = false;
    bool HLT_Mu27 = false;
    bool HLT_Mu50 = false;
    bool HLT_Mu55 = false;
 

    tree->SetBranchAddress("weight",&weight);                                       
    tree->SetBranchAddress("MET",&MET);                                       
    tree->SetBranchAddress("fatJet1Pt",&fatJet1Pt);                                       
    tree->SetBranchAddress("fatJet1Eta",&fatJet1Eta);                                       
    tree->SetBranchAddress("fatJet1MassSD",&fatJet1MassSD);                                       
    tree->SetBranchAddress("fatJet1DDBTagger",&fatJet1DDBTagger);
    tree->SetBranchAddress("fatJet1PNetXbb",&fatJet1PNetXbb); 
    tree->SetBranchAddress("fatJet1PNetQCDb",&fatJet1PNetQCDb); 
    tree->SetBranchAddress("fatJet1PNetQCDbb",&fatJet1PNetQCDbb); 
    tree->SetBranchAddress("fatJet1PNetQCDothers",&fatJet1PNetQCDothers);
    tree->SetBranchAddress("fatJet1Tau3OverTau2",&fatJet1Tau3OverTau2);
    tree->SetBranchAddress("fatJet1HasMuon",&fatJet1HasMuon);
    tree->SetBranchAddress("fatJet1HasElectron",&fatJet1HasElectron);
    tree->SetBranchAddress("fatJet1HasBJetCSVLoose",&fatJet1HasBJetCSVLoose);
    tree->SetBranchAddress("fatJet1HasBJetCSVMedium",&fatJet1HasBJetCSVMedium);
    tree->SetBranchAddress("fatJet1HasBJetCSVTight",&fatJet1HasBJetCSVTight);
    tree->SetBranchAddress("fatJet2Pt",&fatJet2Pt);                                       
    tree->SetBranchAddress("fatJet2MassSD",&fatJet2MassSD);                                       
    tree->SetBranchAddress("fatJet2DDBTagger",&fatJet2DDBTagger);
    tree->SetBranchAddress("fatJet2PNetXbb",&fatJet2PNetXbb); 
    tree->SetBranchAddress("fatJet2PNetQCDb",&fatJet2PNetQCDb); 
    tree->SetBranchAddress("fatJet2PNetQCDbb",&fatJet2PNetQCDbb); 
    tree->SetBranchAddress("fatJet2PNetQCDothers",&fatJet2PNetQCDothers);
    tree->SetBranchAddress("fatJet2Tau3OverTau2",&fatJet2Tau3OverTau2);
    tree->SetBranchAddress("fatJet2HasMuon",&fatJet2HasMuon);
    tree->SetBranchAddress("fatJet2HasElectron",&fatJet2HasElectron);
    tree->SetBranchAddress("fatJet2HasBJetCSVLoose",&fatJet2HasBJetCSVLoose);
    tree->SetBranchAddress("fatJet2HasBJetCSVMedium",&fatJet2HasBJetCSVMedium);
    tree->SetBranchAddress("fatJet2HasBJetCSVTight",&fatJet2HasBJetCSVTight);
    tree->SetBranchAddress("hh_pt", &hh_pt);
    tree->SetBranchAddress("hh_eta", &hh_eta);
    tree->SetBranchAddress("hh_phi", &hh_phi);
    tree->SetBranchAddress("hh_mass", &hh_mass);        
    tree->SetBranchAddress("fatJet1PtOverMHH", &fatJet1PtOverMHH);
    tree->SetBranchAddress("fatJet1PtOverMSD", &fatJet1PtOverMSD);
    tree->SetBranchAddress("fatJet2PtOverMHH", &fatJet2PtOverMHH);
    tree->SetBranchAddress("fatJet2PtOverMSD", &fatJet2PtOverMSD);
    tree->SetBranchAddress("deltaEta_j1j2", &deltaEta_j1j2);
    tree->SetBranchAddress("deltaPhi_j1j2", &deltaPhi_j1j2);
    tree->SetBranchAddress("deltaR_j1j2", &deltaR_j1j2);    
    tree->SetBranchAddress("ptj2_over_ptj1", &ptj2_over_ptj1);
    tree->SetBranchAddress("mj2_over_mj1", &mj2_over_mj1);
    tree->SetBranchAddress("HLT_PFHT790",                                        &HLT_PFHT790);                             
    tree->SetBranchAddress("HLT_PFHT890",                                        &HLT_PFHT890);                             
    tree->SetBranchAddress("HLT_PFHT1050",                                        &HLT_PFHT1050);                             
    tree->SetBranchAddress("HLT_AK8PFJet360_TrimMass30",                          &HLT_AK8PFJet360_TrimMass30);                             
    tree->SetBranchAddress("HLT_AK8PFJet380_TrimMass30",                          &HLT_AK8PFJet380_TrimMass30);                             
    tree->SetBranchAddress("HLT_AK8PFJet400_TrimMass30",                          &HLT_AK8PFJet400_TrimMass30);                             
    tree->SetBranchAddress("HLT_AK8PFJet420_TrimMass30",                          &HLT_AK8PFJet420_TrimMass30);                             
    tree->SetBranchAddress("HLT_AK8PFHT750_TrimMass50",                           &HLT_AK8PFHT750_TrimMass50);                         
    tree->SetBranchAddress("HLT_AK8PFHT800_TrimMass50",                           &HLT_AK8PFHT800_TrimMass50);                         
    tree->SetBranchAddress("HLT_AK8PFHT850_TrimMass50",                           &HLT_AK8PFHT850_TrimMass50);                         
    tree->SetBranchAddress("HLT_AK8PFHT900_TrimMass50",                           &HLT_AK8PFHT900_TrimMass50);                         
    tree->SetBranchAddress("HLT_PFJet450",                                        &HLT_PFJet450);                                           
    tree->SetBranchAddress("HLT_PFJet500",                                        &HLT_PFJet500);                                       
    tree->SetBranchAddress("HLT_PFJet550",                                        &HLT_PFJet550);                                       
    tree->SetBranchAddress("HLT_AK8PFJet450",                                     &HLT_AK8PFJet450);                                    
    tree->SetBranchAddress("HLT_AK8PFJet500",                                     &HLT_AK8PFJet500);                                    
    tree->SetBranchAddress("HLT_AK8PFJet550",                                     &HLT_AK8PFJet550);                                    
    tree->SetBranchAddress("HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17",     &HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17);    
    tree->SetBranchAddress("HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1",      &HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1);     
    tree->SetBranchAddress("HLT_AK8PFJet330_PFAK8BTagCSV_p1",                     &HLT_AK8PFJet330_PFAK8BTagCSV_p1);                   
    tree->SetBranchAddress("HLT_AK8PFJet330_PFAK8BTagCSV_p17",                    &HLT_AK8PFJet330_PFAK8BTagCSV_p17);                   
    tree->SetBranchAddress("HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02",  &HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02); 
    tree->SetBranchAddress("HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2",  &HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2); 
    tree->SetBranchAddress("HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4",  &HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4); 
    tree->SetBranchAddress("HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p20",        &HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p20);
    tree->SetBranchAddress("HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p087",       &HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p087);
    tree->SetBranchAddress("HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p087",       &HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p087);
    tree->SetBranchAddress("HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20",     &HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20);
    tree->SetBranchAddress("HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20",        &HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20);
    tree->SetBranchAddress("HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20",        &HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20);
 
    tree->SetBranchAddress("HLT_IsoMu27", &HLT_IsoMu27);
    tree->SetBranchAddress("HLT_IsoMu30", &HLT_IsoMu30);
    tree->SetBranchAddress("HLT_Mu27", &HLT_Mu27);
    tree->SetBranchAddress("HLT_Mu50", &HLT_Mu50);
    tree->SetBranchAddress("HLT_Mu55", &HLT_Mu55);
 

    cout << "file " << datafiles[i] << " | Total Entries: " << tree->GetEntries() << "\n";

    for(UInt_t ientry=0; ientry < tree->GetEntries(); ientry++) {       	
      tree->GetEntry(ientry);
      
      if (ientry % 100000 == 0) cout << "Event " << ientry << endl;      
    
      //******************************
      //Reference Trigger Selection
      //******************************
      if (!(HLT_IsoMu27 || HLT_IsoMu30 || HLT_Mu27 || HLT_Mu50 || HLT_Mu55)) continue;
      
      if (!(fabs(fatJet1Eta) < 2.4)) continue;
      //if (!(fabs(fatJet2Pt) > 250)) continue;
 
      //******************************
      //Trigger Selection
      //******************************
      bool passTrigger;
      	if (option == "2016") {
	  passTrigger = 
	    (0 == 1)
	    || HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20
	    || HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20
	    || HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20	 	    
	    || HLT_AK8PFJet360_TrimMass30
	    || HLT_AK8PFJet450 
	    || HLT_PFJet450    
	    || HLT_PFHT790
	    || HLT_PFHT890
	    || HLT_PFHT1050
	    ;       
	}
	if (option == "2017") {
	  passTrigger = 
	    (0 == 1) 
	    || HLT_PFJet450    
	    || HLT_PFJet500    
	    || HLT_AK8PFJet400 
	    || HLT_AK8PFJet500 
	    || HLT_PFHT1050
	    || HLT_AK8PFJet360_TrimMass30
	    || HLT_AK8PFJet380_TrimMass30
	    || HLT_AK8PFJet400_TrimMass30   
	    || HLT_AK8PFHT800_TrimMass50 
	    || HLT_AK8PFHT750_TrimMass50 
	    || HLT_AK8PFJet330_PFAK8BTagCSV_p17	  
	    ;       
	}
	if (option == "2018") {
	  passTrigger = 
	    (0 == 1) 
	    || HLT_PFHT1050
	    || HLT_PFJet500  
	    || HLT_AK8PFJet500 
	    || HLT_AK8PFJet400_TrimMass30 
	    || HLT_AK8PFHT800_TrimMass50     
	    || HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4 
	    ;    	   
	}


	//******************************
	//Fill histograms
	//******************************
	histJetPtMass_Denominator->Fill(fatJet1MassSD,fatJet1Pt);
	if (passTrigger) {
	  histJetPtMass_Numerator->Fill(fatJet1MassSD,fatJet1Pt);
	}

	if(fatJet1PNetXbb < 0.9) {
	  histJetPtMass_Denominator_Xbb0p0To0p9->Fill(fatJet1MassSD,fatJet1Pt);
	  if (passTrigger) {
	    histJetPtMass_Numerator_Xbb0p0To0p9->Fill(fatJet1MassSD,fatJet1Pt);
	  }
	}
	if(fatJet1PNetXbb >= 0.9 && fatJet1PNetXbb < 0.95 ) {
	  histJetPtMass_Denominator_Xbb0p9To0p95->Fill(fatJet1MassSD,fatJet1Pt);
	  if (passTrigger) {
	    histJetPtMass_Numerator_Xbb0p9To0p95->Fill(fatJet1MassSD,fatJet1Pt);
	  }
	}
	if(fatJet1PNetXbb >= 0.95 && fatJet1PNetXbb < 0.98 ) {
	  histJetPtMass_Denominator_Xbb0p95To0p98->Fill(fatJet1MassSD,fatJet1Pt);
	  if (passTrigger) {
	    histJetPtMass_Numerator_Xbb0p95To0p98->Fill(fatJet1MassSD,fatJet1Pt);
	  }
	}
	if(fatJet1PNetXbb >= 0.98 ) {
	  histJetPtMass_Denominator_Xbb0p98To1p0->Fill(fatJet1MassSD,fatJet1Pt);
	  if (passTrigger) {
	    histJetPtMass_Numerator_Xbb0p98To1p0->Fill(fatJet1MassSD,fatJet1Pt);
	  }
	}

	
	if (fatJet1MassSD > 30) {
	  histJetPt_Denominator ->Fill(fatJet1Pt);
	  if (passTrigger) {
	    histJetPt_Numerator ->Fill(fatJet1Pt);
	  }
	}

	if (fatJet1Pt > 600) {
	  histJetMass_Denominator->Fill(fatJet1MassSD);
	  if (passTrigger) {
	    histJetMass_Numerator->Fill(fatJet1MassSD);
	  }
	}

	if (fatJet1MassSD > 30 && fatJet1Pt > 300 && fatJet1Pt < 400) {
	  histJetPNetXbb_Denominator->Fill(fatJet1PNetXbb);
	  if (passTrigger) {	 	  
	    histJetPNetXbb_Numerator->Fill(fatJet1PNetXbb);
	  }
	}		
	
    } //loop over events
  } //loop over input files

  //--------------------------------------------------------------------------------------------------------------
  // Compute Efficiencies
  //==============================================================================================================
  vector<double> ptbins;
  ptbins.push_back(250);
  ptbins.push_back(275); 
  ptbins.push_back(300); 
  ptbins.push_back(325); 
  ptbins.push_back(350); 
  ptbins.push_back(375); 
  ptbins.push_back(400); 
  ptbins.push_back(450); 
  ptbins.push_back(500); 
  ptbins.push_back(600); 
  ptbins.push_back(700);
  vector<double> massbins;  
  massbins.push_back(0);
  massbins.push_back(20);
  massbins.push_back(40);
  massbins.push_back(60);
  massbins.push_back(80);
  massbins.push_back(100);
  massbins.push_back(120);
  massbins.push_back(140);
  massbins.push_back(160);
  massbins.push_back(180);
  massbins.push_back(200);
  massbins.push_back(220);
  massbins.push_back(240);

  TGraphAsymmErrors *efficiency_pt = createEfficiencyGraph(histJetPt_Numerator, histJetPt_Denominator, "Efficiency_Pt" , vector<double>() ,  -99, -99, 0, 1);
  TGraphAsymmErrors *efficiency_mass = createEfficiencyGraph(histJetMass_Numerator, histJetMass_Denominator, "Efficiency_Mass" , vector<double>() ,  -99, -99, 0, 1);
  TGraphAsymmErrors *efficiency_PNetXbb = createEfficiencyGraph(histJetPNetXbb_Numerator, histJetPNetXbb_Denominator, "Efficiency_PNetXbb" , vector<double>() ,  -99, -99, 0, 1);
  TH2F *efficiency_ptmass = createEfficiencyHist2D(histJetPtMass_Numerator, histJetPtMass_Denominator, "Efficiency_PtMass" , massbins, ptbins);  
  TH2F *efficiency_ptmass_Xbb0p0To0p9 = createEfficiencyHist2D(histJetPtMass_Numerator_Xbb0p0To0p9, histJetPtMass_Denominator_Xbb0p0To0p9, "Efficiency_PtMass_Xbb0p0To0p9" , massbins, ptbins);  
  TH2F *efficiency_ptmass_Xbb0p9To0p95 = createEfficiencyHist2D(histJetPtMass_Numerator_Xbb0p9To0p95, histJetPtMass_Denominator_Xbb0p9To0p95, "Efficiency_PtMass_Xbb0p9To0p95" , massbins, ptbins);  
  TH2F *efficiency_ptmass_Xbb0p95To0p98 = createEfficiencyHist2D(histJetPtMass_Numerator_Xbb0p95To0p98, histJetPtMass_Denominator_Xbb0p95To0p98, "Efficiency_PtMass_Xbb0p95To0p98" , massbins, ptbins);  
  TH2F *efficiency_ptmass_Xbb0p98To1p0 = createEfficiencyHist2D(histJetPtMass_Numerator_Xbb0p98To1p0, histJetPtMass_Denominator_Xbb0p98To1p0, "Efficiency_PtMass_Xbb0p98To1p0" , massbins, ptbins);  

 //--------------------------------------------------------------------------------------------------------------
  // Draw
  //==============================================================================================================
  gStyle->SetPaintTextFormat(".3f");

  TCanvas *cv =0;

  cv = new TCanvas("cv","cv",800,600);
  efficiency_pt->Draw("AP");
  efficiency_pt->SetTitle("");
  efficiency_pt->GetYaxis()->SetRangeUser(0.0,1.0);
  efficiency_pt->GetXaxis()->SetTitle("AK8 Jet p_{T} [GeV]");
  efficiency_pt->GetYaxis()->SetTitle("Efficiency");
  efficiency_pt->GetYaxis()->SetTitleOffset(1.2);
  efficiency_pt->SetLineWidth(3);  
  cv->SaveAs(("JetHTTriggerEfficiency"+Label+"_Pt.gif").c_str());

  cv = new TCanvas("cv","cv",800,600);
  efficiency_mass->Draw("AP");
  efficiency_mass->SetTitle("");
  efficiency_mass->GetYaxis()->SetRangeUser(0.0,1.0);
  efficiency_mass->GetXaxis()->SetTitle("AK8 Jet Mass [GeV]");
  efficiency_mass->GetYaxis()->SetTitle("Efficiency");
  efficiency_mass->GetYaxis()->SetTitleOffset(1.2);
  efficiency_mass->SetLineWidth(3);  
  cv->SaveAs(("JetHTTriggerEfficiency"+Label+"_Mass.gif").c_str());

  cv = new TCanvas("cv","cv",800,600);
  efficiency_PNetXbb->Draw("AP");
  efficiency_PNetXbb->SetTitle("");
  efficiency_PNetXbb->GetYaxis()->SetRangeUser(0.0,1.0);
  efficiency_PNetXbb->GetXaxis()->SetTitle("AK8 Jet PNetXbb Prob");
  efficiency_PNetXbb->GetYaxis()->SetTitle("Efficiency");
  efficiency_PNetXbb->GetYaxis()->SetTitleOffset(1.2);
  efficiency_PNetXbb->SetLineWidth(3);  
  cv->SaveAs(("JetHTTriggerEfficiency"+Label+"_PNetXbb.gif").c_str());

  cv = new TCanvas("cv","cv",800,600);
  cv->SetRightMargin(0.15);
  efficiency_ptmass->Draw("colztext");
  efficiency_ptmass->SetStats(0);
  efficiency_ptmass->SetTitle("");
  efficiency_ptmass->GetYaxis()->SetTitle("AK8 Jet p_{T} [GeV]");
  efficiency_ptmass->GetXaxis()->SetTitle("AK8 Jet Mass [GeV]");
  efficiency_ptmass->GetYaxis()->SetTitleOffset(1.2);
  efficiency_ptmass->GetZaxis()->SetTitle("Trigger Efficiency");
  //efficiency_ptmass->GetZaxis()->SetRangeUser(0.0,1.0);
  efficiency_ptmass->SetLineWidth(3);  
  cv->SaveAs(("JetHTTriggerEfficiency"+Label+"_ptmass.gif").c_str());
  cv->SaveAs(("JetHTTriggerEfficiency"+Label+"_ptmass.pdf").c_str());

  cv = new TCanvas("cv","cv",800,600);
  cv->SetRightMargin(0.15);
  efficiency_ptmass_Xbb0p0To0p9->Draw("colztext");
  efficiency_ptmass_Xbb0p0To0p9->SetStats(0);
  efficiency_ptmass_Xbb0p0To0p9->SetTitle("");
  efficiency_ptmass_Xbb0p0To0p9->GetYaxis()->SetTitle("AK8 Jet p_{T} [GeV]");
  efficiency_ptmass_Xbb0p0To0p9->GetXaxis()->SetTitle("AK8 Jet Mass [GeV]");
  efficiency_ptmass_Xbb0p0To0p9->GetYaxis()->SetTitleOffset(1.2);
  efficiency_ptmass_Xbb0p0To0p9->GetZaxis()->SetTitle("Trigger Efficiency");
  efficiency_ptmass_Xbb0p0To0p9->SetLineWidth(3);  
  cv->SaveAs(("JetHTTriggerEfficiency_Xbb0p0To0p9"+Label+"_ptmass.gif").c_str());
  cv->SaveAs(("JetHTTriggerEfficiency_Xbb0p0To0p9"+Label+"_ptmass.pdf").c_str());

  cv = new TCanvas("cv","cv",800,600);
  cv->SetRightMargin(0.15);
  efficiency_ptmass_Xbb0p9To0p95->Draw("colztext");
  efficiency_ptmass_Xbb0p9To0p95->SetStats(0);
  efficiency_ptmass_Xbb0p9To0p95->SetTitle("");
  efficiency_ptmass_Xbb0p9To0p95->GetYaxis()->SetTitle("AK8 Jet p_{T} [GeV]");
  efficiency_ptmass_Xbb0p9To0p95->GetXaxis()->SetTitle("AK8 Jet Mass [GeV]");
  efficiency_ptmass_Xbb0p9To0p95->GetYaxis()->SetTitleOffset(1.2);
  efficiency_ptmass_Xbb0p9To0p95->GetZaxis()->SetTitle("Trigger Efficiency");
  efficiency_ptmass_Xbb0p9To0p95->SetLineWidth(3);  
  cv->SaveAs(("JetHTTriggerEfficiency_Xbb0p9To0p95"+Label+"_ptmass.gif").c_str());
  cv->SaveAs(("JetHTTriggerEfficiency_Xbb0p9To0p95"+Label+"_ptmass.pdf").c_str());

  cv = new TCanvas("cv","cv",800,600);
  cv->SetRightMargin(0.15);
  efficiency_ptmass_Xbb0p95To0p98->Draw("colztext");
  efficiency_ptmass_Xbb0p95To0p98->SetStats(0);
  efficiency_ptmass_Xbb0p95To0p98->SetTitle("");
  efficiency_ptmass_Xbb0p95To0p98->GetYaxis()->SetTitle("AK8 Jet p_{T} [GeV]");
  efficiency_ptmass_Xbb0p95To0p98->GetXaxis()->SetTitle("AK8 Jet Mass [GeV]");
  efficiency_ptmass_Xbb0p95To0p98->GetYaxis()->SetTitleOffset(1.2);
  efficiency_ptmass_Xbb0p95To0p98->GetZaxis()->SetTitle("Trigger Efficiency");
  efficiency_ptmass_Xbb0p95To0p98->SetLineWidth(3);  
  cv->SaveAs(("JetHTTriggerEfficiency_Xbb0p95To0p98"+Label+"_ptmass.gif").c_str());
  cv->SaveAs(("JetHTTriggerEfficiency_Xbb0p95To0p98"+Label+"_ptmass.pdf").c_str());

  cv = new TCanvas("cv","cv",800,600);
  cv->SetRightMargin(0.15);
  efficiency_ptmass_Xbb0p98To1p0->Draw("colztext");
  efficiency_ptmass_Xbb0p98To1p0->SetStats(0);
  efficiency_ptmass_Xbb0p98To1p0->SetTitle("");
  efficiency_ptmass_Xbb0p98To1p0->GetYaxis()->SetTitle("AK8 Jet p_{T} [GeV]");
  efficiency_ptmass_Xbb0p98To1p0->GetXaxis()->SetTitle("AK8 Jet Mass [GeV]");
  efficiency_ptmass_Xbb0p98To1p0->GetYaxis()->SetTitleOffset(1.2);
  efficiency_ptmass_Xbb0p98To1p0->GetZaxis()->SetTitle("Trigger Efficiency");
  efficiency_ptmass_Xbb0p98To1p0->SetLineWidth(3);  
  cv->SaveAs(("JetHTTriggerEfficiency_Xbb0p98To1p0"+Label+"_ptmass.gif").c_str());
  cv->SaveAs(("JetHTTriggerEfficiency_Xbb0p98To1p0"+Label+"_ptmass.pdf").c_str());

   //--------------------------------------------------------------------------------------------------------------
  // Output
  //==============================================================================================================
  TFile *file = TFile::Open(("JetHTTriggerEfficiency"+Label+".root").c_str(), "UPDATE");
  file->cd();

  file->WriteTObject(efficiency_pt, "efficiency_pt", "WriteDelete");
  file->WriteTObject(efficiency_mass, "efficiency_mass", "WriteDelete");
  file->WriteTObject(efficiency_PNetXbb, "efficiency_PNetXbb", "WriteDelete");
  file->WriteTObject(efficiency_ptmass, "efficiency_ptmass", "WriteDelete");
  file->WriteTObject(efficiency_ptmass_Xbb0p0To0p9, "efficiency_ptmass_Xbb0p0To0p9", "WriteDelete");
  file->WriteTObject(efficiency_ptmass_Xbb0p9To0p95, "efficiency_ptmass_Xbb0p9To0p95", "WriteDelete");
  file->WriteTObject(efficiency_ptmass_Xbb0p95To0p98, "efficiency_ptmass_Xbb0p95To0p98", "WriteDelete");
  file->WriteTObject(efficiency_ptmass_Xbb0p98To1p0, "efficiency_ptmass_Xbb0p98To1p0", "WriteDelete");
  
  file->Close();
  delete file;       

}







void JetHTTriggerEfficiency( int option = 0) {

  vector<string> datafiles;
  if (option == 0) {
    datafiles.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/JetHTTriggerNtupler/20210225/2016/SingleMuon_2016B-ver2.root");
    datafiles.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/JetHTTriggerNtupler/20210225/2016/SingleMuon_2016C.root");
    datafiles.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/JetHTTriggerNtupler/20210225/2016/SingleMuon_2016D.root");
    datafiles.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/JetHTTriggerNtupler/20210225/2016/SingleMuon_2016E.root");
    datafiles.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/JetHTTriggerNtupler/20210225/2016/SingleMuon_2016F.root");
    datafiles.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/JetHTTriggerNtupler/20210225/2016/SingleMuon_2016G.root");
    datafiles.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/JetHTTriggerNtupler/20210225/2016/SingleMuon_2016H.root");    
  } else if (option == 1) {
    datafiles.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/JetHTTriggerNtupler/20210225/2017/SingleMuon_2017B.root");
    datafiles.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/JetHTTriggerNtupler/20210225/2017/SingleMuon_2017C.root");
    datafiles.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/JetHTTriggerNtupler/20210225/2017/SingleMuon_2017D.root");
    datafiles.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/JetHTTriggerNtupler/20210225/2017/SingleMuon_2017E.root");
    datafiles.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/JetHTTriggerNtupler/20210225/2017/SingleMuon_2017F.root ");     
  } else if (option == 2) {
    datafiles.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/JetHTTriggerNtupler/20210225/2018/SingleMuon_2018A.root");
    datafiles.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/JetHTTriggerNtupler/20210225/2018/SingleMuon_2018B.root");
    datafiles.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/JetHTTriggerNtupler/20210225/2018/SingleMuon_2018C.root");
    datafiles.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/JetHTTriggerNtupler/20210225/2018/SingleMuon_2018D.root");
  }
  


  if (option == 10) {
    datafiles.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/JetHTTriggerNtupler/20210225/2016/TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8.root");
    datafiles.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/JetHTTriggerNtupler/20210225/2016/WJetsToQQ_HT-800toInf_qc19_3j_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");
    datafiles.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/JetHTTriggerNtupler/20210225/2016/WJetsToQQ_HT400to600_qc19_3j_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");
    datafiles.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/JetHTTriggerNtupler/20210225/2016/WJetsToQQ_HT600to800_qc19_3j_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");
  } else if (option == 11) {
    datafiles.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/JetHTTriggerNtupler/20210225/2017/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8.root");
    datafiles.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/JetHTTriggerNtupler/20210225/2017/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8_new_pmx.root");
    datafiles.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/JetHTTriggerNtupler/20210225/2017/TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8.root");
    datafiles.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/JetHTTriggerNtupler/20210225/2017/WJetsToQQ_HT-800toInf_qc19_3j_TuneCP5_13TeV-madgraphMLM-pythia8.root");
    datafiles.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/JetHTTriggerNtupler/20210225/2017/WJetsToQQ_HT400to600_qc19_3j_TuneCP5_13TeV-madgraphMLM-pythia8.root");
    datafiles.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/JetHTTriggerNtupler/20210225/2017/WJetsToQQ_HT600to800_qc19_3j_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  } else if (option == 12) {
    datafiles.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/JetHTTriggerNtupler/20210225/2018/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8-ext3.root");
    datafiles.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/JetHTTriggerNtupler/20210225/2018/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8.root");
    datafiles.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/JetHTTriggerNtupler/20210225/2018/WJetsToQQ_HT-800toInf_qc19_3j_TuneCP5_13TeV-madgraphMLM-pythia8.root");
    datafiles.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/JetHTTriggerNtupler/20210225/2018/WJetsToQQ_HT400to600_qc19_3j_TuneCP5_13TeV-madgraphMLM-pythia8.root");
    datafiles.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/JetHTTriggerNtupler/20210225/2018/WJetsToQQ_HT600to800_qc19_3j_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  }


  double lumi = 0;
  string yearlabel = "";
  string optionString = "";
  if (option == 0) {
    lumi = 35922;
    yearlabel = "2016";
    optionString = "2016";
  } 
  if (option == 1) {
    lumi = 41480;
    yearlabel = "2017";   
    optionString = "2017"; 
  } 
  if (option == 2) {
    lumi = 59741;
    yearlabel = "2018";
    optionString = "2018";
  } 
  if (option == 10) {
    lumi = 35922;
    yearlabel = "Summer16";
    optionString = "2016";
  } 
  if (option == 11) {
    lumi = 41480;
    yearlabel = "Fall17"; 
    optionString = "2017";   
  } 
  if (option == 12) {
    lumi = 59741;
    yearlabel = "Fall18";
    optionString = "2018";
  } 
 
  //*********************************************************************
  //Measure 
  //********************************************************************* 
  RunMeasureJetHTTriggerEfficiency(datafiles, lumi, optionString,1,yearlabel);

 
}


//**********************************
//E-Mu Yields :
//**********************************

//MuEG Triggers ( 30 - 20 )
// Data: 148
// MC: 156.16
