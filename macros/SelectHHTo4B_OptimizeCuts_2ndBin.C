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

#endif


std::vector<double> makeCutSet ( double pt1Low, double pt2Low, double Xbb1Low, double Xbb2Low, double mass1Low, double mass1High,
				 double disc_qcd_2017_basic0  = -99,
				 double disc_qcd_2017_basic1  = -99,
				 double disc_qcd_2017_basic2  = -99,
				 double disc_qcd_2017_enhanced  = -99,
				 double disc_qcd_2017_enhanced_v2  = -99,
				 double disc_ttbar_2017_basic0  = -99,
				 double disc_ttbar_2017_basic1  = -99,
				 double disc_ttbar_2017_basic2  = -99,
				 double disc_ttbar_2017_enhanced  = -99,
				 double disc_ttbar_2017_enhanced_v2  = -99,
				 double disc_qcd_and_ttbar_2017_basic0  = -99,
				 double disc_qcd_and_ttbar_2017_basic1  = -99,
				 double disc_qcd_and_ttbar_2017_basic2  = -99,
				 double disc_qcd_and_ttbar_2017_enhanced  = -99,
				 double disc_qcd_and_ttbar_2017_enhanced_v2  = -99,
				 double disc_qcd_and_ttbar_2017_enhanced_v5  = -99,
				 double disc_qcd_and_ttbar_2017_enhanced_v6  = -99,
				 double disc_qcd_and_ttbar_2017_enhanced_v7  = -99,
				 double disc_qcd_and_ttbar_2017_enhanced_v8  = -99,
				 double disc_qcd_and_ttbar_2017_enhanced_v10  = -99
				 ) {
  std::vector<double> newCutSet;
  newCutSet.push_back( pt1Low );
  newCutSet.push_back( pt2Low );
  newCutSet.push_back( Xbb1Low );
  newCutSet.push_back( Xbb2Low );
  newCutSet.push_back( mass1Low );
  newCutSet.push_back( mass1High );
  newCutSet.push_back( disc_qcd_2017_basic0  );
  newCutSet.push_back( disc_qcd_2017_basic1  );
  newCutSet.push_back( disc_qcd_2017_basic2  );
  newCutSet.push_back( disc_qcd_2017_enhanced  );
  newCutSet.push_back( disc_qcd_2017_enhanced_v2  );
  newCutSet.push_back( disc_ttbar_2017_basic0  );
  newCutSet.push_back( disc_ttbar_2017_basic1  );
  newCutSet.push_back( disc_ttbar_2017_basic2  );
  newCutSet.push_back( disc_ttbar_2017_enhanced  );
  newCutSet.push_back( disc_ttbar_2017_enhanced_v2  );
  newCutSet.push_back( disc_qcd_and_ttbar_2017_basic0  );
  newCutSet.push_back( disc_qcd_and_ttbar_2017_basic1  );
  newCutSet.push_back( disc_qcd_and_ttbar_2017_basic2  );
  newCutSet.push_back( disc_qcd_and_ttbar_2017_enhanced );
  newCutSet.push_back( disc_qcd_and_ttbar_2017_enhanced_v2 );
  newCutSet.push_back( disc_qcd_and_ttbar_2017_enhanced_v5 );
  newCutSet.push_back( disc_qcd_and_ttbar_2017_enhanced_v6 );
  newCutSet.push_back( disc_qcd_and_ttbar_2017_enhanced_v7 );
  newCutSet.push_back( disc_qcd_and_ttbar_2017_enhanced_v8 );
  newCutSet.push_back( disc_qcd_and_ttbar_2017_enhanced_v10 );
  return newCutSet;  
}

void Plot( TH1F *hist , string varName, double lumi ) {

  TCanvas *cv =0;
  TLegend *legend = 0;

  cv = new TCanvas("cv","cv", 800,700);
  // cv->SetHighLightColor(2);
  // cv->SetFillColor(0);
  // cv->SetBorderMode(0);
  // cv->SetBorderSize(2);
  // cv->SetLeftMargin(0.16);
  // cv->SetRightMargin(0.3);
  // cv->SetTopMargin(0.07);
  // cv->SetBottomMargin(0.12);
  // cv->SetFrameBorderMode(0);  

  hist->SetStats(0);
  hist->Draw("e1");
  hist->GetYaxis()->SetTitleOffset(1.0);
  hist->GetYaxis()->SetTitleSize(0.05);
  hist->GetXaxis()->SetTitleSize(0.15);
  hist->SetMaximum( 1.2*(fmax(hist->GetMaximum(),hist->GetMaximum())));
  hist->SetMinimum( 0.0 );
  hist->SetLineWidth(2);
  hist->SetLineColor(kBlack);


   //****************************
  //Add CMS and Lumi Labels
  //****************************
  // lumi_13TeV = "42 pb^{-1}";
  // lumi_13TeV = Form("%.1f fb^{-1}", lumi/1000.0);
  // writeExtraText = true;
  // relPosX = 0.13;
  // CMS_lumi(pad1,4,0);

  // cv->cd();
  // cv->Update();

  cv->SaveAs(Form("HHTo4B_OptimizeCuts_SR_%s.png",varName.c_str()));
  cv->SaveAs(Form("HHTo4B_OptimizeCuts_SR_%s.pdf",varName.c_str())); 

}



//=== MAIN MACRO ================================================================================================= 


std::vector<std::pair<double,double> > RunSelectHHTo4B(  std::vector<std::vector<double> > cutSets, std::vector<std::string> datafiles, std::vector<std::string> sigfiles, double lumi, string year) {
  
  //--------------------------------------------------------------------------------------------------------------
  // Settings 
  //============================================================================================================== 
  assert(cutSets.size() == 21);
 
  //*****************************************************************************************
  //Make some histograms
  //*****************************************************************************************
  std::vector<std::vector<std::string> > inputfiles;
  std::vector<std::string> processLabels;
 
  inputfiles.push_back(datafiles);
  processLabels.push_back("Data");
 
  inputfiles.push_back(sigfiles);
  processLabels.push_back("HH");
     
  for (int i=0; i < int(inputfiles.size()); ++i) {
    cout << processLabels[i] << "\n";
  }


  std::vector<TH1F*> histJet2Mass_data;
  std::vector<TH1F*> histJet2Mass_signal;

  assert (inputfiles.size() == processLabels.size());
  for (uint i=0; i < cutSets.size(); ++i) {
    histJet2Mass_data.push_back(new TH1F(Form("histJet2Mass_data_CutSet%d",i), "; Jet2 Mass [GeV] ; Number of Events", 25, 15, 515));
    histJet2Mass_signal.push_back(new TH1F(Form("histJet2Mass_signal_CutSet%d",i), "; Jet2 Mass [GeV] ; Number of Events", 25, 15, 515));  
    histJet2Mass_data[i]->Sumw2();
    histJet2Mass_signal[i]->Sumw2();
  }
 
  //*******************************************************************************************
  //Read file
  //*******************************************************************************************                
  for (uint j=0; j < inputfiles.size(); ++j) {
    for (uint k=0; k < inputfiles[j].size(); ++k) {

      TFile *file = new TFile(inputfiles[j][k].c_str(),"READ");
      TTree *tree = 0;
      if (!file) {
	cout << "Input file " << inputfiles[j][k] << " could not be opened\n"; 
	continue;
      } else {
	tree = (TTree*)file->Get("tree");
      }
      if (!tree) {
	cout << "Tree could not be found in input file " << inputfiles[j][k] << "\n"; 
	continue;
      }

      float weight = 0;
      float triggerEffWeight = 0;
      float pileupWeight = 0;
      float MET = 0;
      float fatJet1Pt = 0;
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
      float disc_qcd_2017_basic0  = -99;
      float disc_qcd_2017_basic1  = -99;
      float disc_qcd_2017_basic2  = -99;
      float disc_qcd_2017_enhanced  = -99;
      float disc_qcd_2017_enhanced_v2  = -99;
      float disc_ttbar_2017_basic0  = -99;
      float disc_ttbar_2017_basic1  = -99;
      float disc_ttbar_2017_basic2  = -99;
      float disc_ttbar_2017_enhanced = -99; 
      float disc_ttbar_2017_enhanced_v2 = -99; 
      float disc_qcd_and_ttbar_2017_basic0  = -99;
      float disc_qcd_and_ttbar_2017_basic1  = -99;
      float disc_qcd_and_ttbar_2017_basic2  = -99;
      float disc_qcd_and_ttbar_2017_enhanced  = -99;     
      float disc_qcd_and_ttbar_2017_enhanced_v2  = -99;     
      float disc_qcd_and_ttbar_2017_enhanced_v5  = -99;     
      float disc_qcd_and_ttbar_2017_enhanced_v6  = -99;     
      float disc_qcd_and_ttbar_2017_enhanced_v7  = -99;     
      float disc_qcd_and_ttbar_2017_enhanced_v8  = -99;     
      float disc_qcd_and_ttbar_2017_enhanced_v10  = -99;     
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

      tree->SetBranchAddress("weight",&weight);                                       
      tree->SetBranchAddress("triggerEffWeight",&triggerEffWeight);
      tree->SetBranchAddress("pileupWeight",&pileupWeight);
      tree->SetBranchAddress("MET",&MET);                                       
      tree->SetBranchAddress("fatJet1Pt",&fatJet1Pt);                                       
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
      tree->SetBranchAddress("disc_qcd_2017_basic0", &disc_qcd_2017_basic0);
      tree->SetBranchAddress("disc_qcd_2017_basic1", &disc_qcd_2017_basic1);
      tree->SetBranchAddress("disc_qcd_2017_basic2", &disc_qcd_2017_basic2);
      tree->SetBranchAddress("disc_qcd_2017_enhanced", &disc_qcd_2017_enhanced);
      tree->SetBranchAddress("disc_qcd_2017_enhanced_v2", &disc_qcd_2017_enhanced_v2);
      tree->SetBranchAddress("disc_ttbar_2017_basic0", &disc_ttbar_2017_basic0);
      tree->SetBranchAddress("disc_ttbar_2017_basic1", &disc_ttbar_2017_basic1);
      tree->SetBranchAddress("disc_ttbar_2017_basic2", &disc_ttbar_2017_basic2);
      tree->SetBranchAddress("disc_ttbar_2017_enhanced", &disc_ttbar_2017_enhanced);
      tree->SetBranchAddress("disc_ttbar_2017_enhanced_v2", &disc_ttbar_2017_enhanced_v2);
      tree->SetBranchAddress("disc_qcd_and_ttbar_2017_basic0", &disc_qcd_and_ttbar_2017_basic0);
      tree->SetBranchAddress("disc_qcd_and_ttbar_2017_basic1", &disc_qcd_and_ttbar_2017_basic1);
      tree->SetBranchAddress("disc_qcd_and_ttbar_2017_basic2", &disc_qcd_and_ttbar_2017_basic2);
      tree->SetBranchAddress("disc_qcd_and_ttbar_2017_enhanced", &disc_qcd_and_ttbar_2017_enhanced);
      tree->SetBranchAddress("disc_qcd_and_ttbar_2017_enhanced_v2", &disc_qcd_and_ttbar_2017_enhanced_v2);
      //tree->SetBranchAddress("disc_qcd_and_ttbar_2017_enhanced_v5", &disc_qcd_and_ttbar_2017_enhanced_v5);
      tree->SetBranchAddress("disc_qcd_and_ttbar_Run2_enhanced_v5p2", &disc_qcd_and_ttbar_2017_enhanced_v5);
      //tree->SetBranchAddress("disc_qcd_and_ttbar_Run2_enhanced_v5p3", &disc_qcd_and_ttbar_2017_enhanced_v5);
      tree->SetBranchAddress("disc_qcd_and_ttbar_2017_enhanced_v6", &disc_qcd_and_ttbar_2017_enhanced_v6);
      tree->SetBranchAddress("disc_qcd_and_ttbar_2017_enhanced_v7", &disc_qcd_and_ttbar_2017_enhanced_v7);
      //tree->SetBranchAddress("disc_qcd_and_ttbar_2017_enhanced_v8", &disc_qcd_and_ttbar_2017_enhanced_v8);
      //tree->SetBranchAddress("disc_qcd_and_ttbar_Run2_enhanced_v8p2", &disc_qcd_and_ttbar_2017_enhanced_v8);
      tree->SetBranchAddress("disc_qcd_and_ttbar_Run2_enhanced_v24", &disc_qcd_and_ttbar_2017_enhanced_v8);
            //tree->SetBranchAddress("disc_qcd_and_ttbar_Run2_enhanced_v8p3", &disc_qcd_and_ttbar_2017_enhanced_v8);
      //tree->SetBranchAddress("disc_qcd_and_ttbar_2017_enhanced_v10", &disc_qcd_and_ttbar_2017_enhanced_v10);
      //tree->SetBranchAddress("disc_qcd_and_ttbar_Run2_enhanced_v10p2", &disc_qcd_and_ttbar_2017_enhanced_v10);
      //tree->SetBranchAddress("disc_qcd_and_ttbar_Run2_enhanced_v10p3", &disc_qcd_and_ttbar_2017_enhanced_v10);
      //tree->SetBranchAddress("disc_qcd_and_ttbar_Run2_enhanced_v16", &disc_qcd_and_ttbar_2017_enhanced_v10);
      tree->SetBranchAddress("fatJet1PtOverMHH", &fatJet1PtOverMHH);
      tree->SetBranchAddress("fatJet1PtOverMSD", &fatJet1PtOverMSD);
      tree->SetBranchAddress("fatJet2PtOverMHH", &fatJet2PtOverMHH);
      tree->SetBranchAddress("fatJet2PtOverMSD", &fatJet2PtOverMSD);
      tree->SetBranchAddress("deltaEta_j1j2", &deltaEta_j1j2);
      tree->SetBranchAddress("deltaPhi_j1j2", &deltaPhi_j1j2);
      tree->SetBranchAddress("deltaR_j1j2", &deltaR_j1j2);    
      tree->SetBranchAddress("ptj2_over_ptj1", &ptj2_over_ptj1);
      tree->SetBranchAddress("mj2_over_mj1", &mj2_over_mj1);
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
 

      bool isData = false;
      if ( processLabels[j] == "Data") isData = true;
    
      cout << "process: " << processLabels[j] << " | file " << inputfiles[j][k] << " | Total Entries: " << tree->GetEntries() << "\n";

      for(UInt_t ientry=0; ientry < tree->GetEntries(); ientry++) {       	
	tree->GetEntry(ientry);
      
	if (ientry % 100000 == 0) cout << "Event " << ientry << endl;      

	double myWeight = 1;
	if (!isData) {	 
	  //myWeight = lumi * weight * triggerEffWeight ;
	  myWeight = lumi * weight * triggerEffWeight * pileupWeight ;
	  //cout << "scaleFactors: " << scaleFactors[i] << "\n";
	}

	//******************************
	//Trigger Selection
	//******************************
	bool passTrigger = false;
	if (year == "2016") {
	  passTrigger = 
	    (0 == 1)
	    || HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20
	    || HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20
	    || HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20	 	    
	    ;       	 	  
	}
	if (year == "2017") {
	  passTrigger = 
	    (0 == 1) 
	    || HLT_PFJet500    
	    || HLT_AK8PFJet500 
	    || HLT_AK8PFJet360_TrimMass30
	    || HLT_AK8PFJet380_TrimMass30
	    || HLT_AK8PFJet400_TrimMass30   
	    || HLT_AK8PFHT800_TrimMass50 
	    || HLT_AK8PFJet330_PFAK8BTagCSV_p17	  
	    ;       
	}
	if (year == "2018") {
	  passTrigger = 
	    (0 == 1) 
	    || HLT_AK8PFJet400_TrimMass30 
	    || HLT_AK8PFHT800_TrimMass50     
	    || HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4 
	    ;    
	}
	if (!isData) passTrigger = true;
	if (!passTrigger) continue;	

	//******************************
	//Pre-Selection Cuts 
	//******************************
	if ( !(fatJet1Pt > 250 )) continue;
	if ( !(fatJet2Pt > 250 )) continue;
	if ( !(fatJet1MassSD > 50)) continue;
	if ( !(fatJet2MassSD > 50)) continue;
       
	for (uint i=0; i < cutSets.size(); ++i) {


	  //******************************
	  //Define Cuts
	  //******************************
	  double pt1Low    = cutSets[i][0];
	  double pt2Low    = cutSets[i][1];
	  double Xbb1Low   = cutSets[i][2];
	  double Xbb2Low   = cutSets[i][3];
	  double mass1Low  = cutSets[i][4];
	  double mass1High = cutSets[i][5];
	  double disc_qcd_basic0_low  = cutSets[i][6];
	  double disc_qcd_basic1_low  = cutSets[i][7];
	  double disc_qcd_basic2_low  = cutSets[i][8];
	  double disc_qcd_enhanced_low  = cutSets[i][9];
	  double disc_qcd_enhanced_v2_low  = cutSets[i][10];
	  double disc_ttbar_basic0_low  = cutSets[i][11];
	  double disc_ttbar_basic1_low  = cutSets[i][12];
	  double disc_ttbar_basic2_low  = cutSets[i][13];
	  double disc_ttbar_enhanced_low = cutSets[i][14]; 
	  double disc_ttbar_enhanced_v2_low = cutSets[i][15]; 
	  double disc_qcd_and_ttbar_basic0_low  = cutSets[i][16];
	  double disc_qcd_and_ttbar_basic1_low  = cutSets[i][17];
	  double disc_qcd_and_ttbar_basic2_low  = cutSets[i][18];
	  double disc_qcd_and_ttbar_enhanced_low  = cutSets[i][19]; 
	  double disc_qcd_and_ttbar_enhanced_v2_low  = cutSets[i][20]; 
	  double disc_qcd_and_ttbar_enhanced_v5_low  = cutSets[i][21]; 
	  double disc_qcd_and_ttbar_enhanced_v6_low  = cutSets[i][22]; 
	  double disc_qcd_and_ttbar_enhanced_v7_low  = cutSets[i][23]; 
	  double disc_qcd_and_ttbar_enhanced_v8_low  = cutSets[i][24]; 
	  double disc_qcd_and_ttbar_enhanced_v10_low  = cutSets[i][25]; 


	  //SR selection
	  // if ( !(fatJet1Pt > pt1Low || fatJet2Pt > pt1Low)) continue;
	  // if ( !(fatJet1Pt > pt2Low && fatJet2Pt > pt2Low )) continue;
	  if ( !(fatJet1PNetXbb > Xbb1Low)) continue;
	  if ( !(fatJet2PNetXbb > Xbb2Low)) continue;
	  // if ( !(fatJet1MassSD > mass1Low && fatJet1MassSD < mass1High)) continue;

	  //*************************************************************************
	  //Enhanced V8p2 BDT Analysis - 
	  //BDT trained with ntuples where jet1/2 are selected based on Xbb ordering
	  //*************************************************************************
	  //Exclude the first bin 
	  // if ( (fatJet2PNetXbb > 0.980 && disc_qcd_and_ttbar_2017_enhanced_v8 > 0.43) ) continue;

	  // //Exclude 2nd bin
	  // if ( (fatJet1PNetXbb > 0.985 && fatJet2PNetXbb > 0.985 && disc_qcd_and_ttbar_2017_enhanced_v8 > 0.069) ) continue;
	  // if ( ( disc_qcd_and_ttbar_2017_enhanced_v8 > 0.11 && fatJet2PNetXbb > 0.980)
	  //      || 
	  //      ( disc_qcd_and_ttbar_2017_enhanced_v8 > 0.43 && fatJet2PNetXbb > 0.950)
	  //      )  continue;


	  // // //Exclude 3nd bin
	  // if ( (fatJet1PNetXbb > 0.975 && fatJet2PNetXbb > 0.975 && disc_qcd_and_ttbar_2017_enhanced_v8 > 0.0063) ) continue;
 	 

	  //*************************************************************************
	  //Enhanced V24 BDT Analysis - 
	  //BDT trained with ntuples where jet1/2 are selected based on Xbb ordering
	  //*************************************************************************
	  //Exclude the first bin 
	  if ( (fatJet1PNetXbb > 0.985 && fatJet2PNetXbb > 0.985 && disc_qcd_and_ttbar_2017_enhanced_v8 > 0.029) ) continue;
	  //Exclude 2nd bin
	  if ( (fatJet1PNetXbb > 0.975 && fatJet2PNetXbb > 0.975 		  
		&& disc_qcd_and_ttbar_2017_enhanced_v8 > 0.0118) ) continue;

	  //Exclude 3nd bin
	  if ( ( (fatJet1PNetXbb > 0.955 && fatJet2PNetXbb > 0.985) 
		 || 
		 (fatJet1PNetXbb > 0.985 && fatJet2PNetXbb > 0.955) 
		 ) && disc_qcd_and_ttbar_2017_enhanced_v8 > 0.0063) continue;
 	 

	

	  // if ( !(disc_qcd_2017_basic0 > disc_qcd_basic0_low) ) continue;
	  // if ( !(disc_qcd_2017_basic1 > disc_qcd_basic1_low) ) continue;
	  // if ( !(disc_qcd_2017_basic2 > disc_qcd_basic2_low) ) continue;
	  // if ( !(disc_qcd_2017_enhanced > disc_qcd_enhanced_low) ) continue;
	  //if ( !(disc_qcd_2017_enhanced_v2 > disc_qcd_enhanced_v2_low) ) continue;
	  // if ( !(disc_ttbar_2017_basic0 > disc_ttbar_basic0_low) ) continue;
	  // if ( !(disc_ttbar_2017_basic1 > disc_ttbar_basic1_low) ) continue;
	  // if ( !(disc_ttbar_2017_basic2 > disc_ttbar_basic2_low) ) continue;
	  //if ( !(disc_ttbar_2017_enhanced > disc_ttbar_enhanced_low) ) continue;
	  //if ( !(disc_ttbar_2017_enhanced_v2 > disc_ttbar_enhanced_v2_low) ) continue;
	  //if ( !(disc_qcd_and_ttbar_2017_basic0 > disc_qcd_and_ttbar_basic0_low) ) continue;
	   //if ( !(disc_qcd_and_ttbar_2017_basic1 > disc_qcd_and_ttbar_basic1_low) ) continue;
	   //if ( !(disc_qcd_and_ttbar_2017_basic2 > disc_qcd_and_ttbar_basic2_low) ) continue;
	  //if ( !(disc_qcd_and_ttbar_2017_enhanced > disc_qcd_and_ttbar_enhanced_low) ) continue;
	  // if ( !(disc_qcd_and_ttbar_2017_enhanced_v2 > disc_qcd_and_ttbar_enhanced_v2_low) ) continue;
	  //if ( !(disc_qcd_and_ttbar_2017_enhanced_v5 > disc_qcd_and_ttbar_enhanced_v5_low) ) continue;
	  //if ( !(disc_qcd_and_ttbar_2017_enhanced_v6 > disc_qcd_and_ttbar_enhanced_v6_low) ) continue;
	  //if ( !(disc_qcd_and_ttbar_2017_enhanced_v7 > disc_qcd_and_ttbar_enhanced_v7_low) ) continue;
	  if ( !(disc_qcd_and_ttbar_2017_enhanced_v8 > disc_qcd_and_ttbar_enhanced_v8_low) ) continue;
	  //if ( !(disc_qcd_and_ttbar_2017_enhanced_v10 > disc_qcd_and_ttbar_enhanced_v10_low) ) continue;
 
	  //Data sideband selection
	  if (isData) {
	    if ( (fatJet2MassSD > 95 && fatJet2MassSD < 135)) continue;
	  } else {
	    if ( !(fatJet2MassSD > 95 && fatJet2MassSD < 135)) continue;
	  }	

	  //******************************
	  //Fill histograms
	  //******************************
	  if (isData) {
	    histJet2Mass_data[i]->Fill(fatJet2MassSD);      
	  } else {
	    histJet2Mass_signal[i]->Fill(fatJet2MassSD, myWeight);      	 
	  }

	}// loop over cutsets


      } //loop over events
    } //loop over input files
  } //loop over processes



 //--------------------------------------------------------------------------------------------------------------
  // Compute Figure out Merit
  //==============================================================================================================
  std::vector<std::pair<double,double> > result;
  for (uint i=0; i < cutSets.size(); ++i) {    
    double tmpSignalYield =  0;
    double tmpBkgYield = 0;
    tmpSignalYield = histJet2Mass_signal[i]->Integral();
    tmpBkgYield = histJet2Mass_data[i]->GetBinContent(4) + histJet2Mass_data[i]->GetBinContent(7);
    std::pair<double,double> tmpResult(tmpSignalYield, tmpBkgYield);
    result.push_back(tmpResult);
  }

  //--------------------------------------------------------------------------------------------------------------
  // Make Plots
  //==============================================================================================================
  // for (uint i=0; i < cutSets.size(); ++i) {
  //   Plot( histJet2Mass_data[i], Form("Jet2_Mass_data_cutSet%d",i), lumi);
  //   Plot( histJet2Mass_signal[i], Form("Jet2_Mass_signal_cutSet%d",i), lumi);
  // }

  //--------------------------------------------------------------------------------------------------------------
  // Output
  //==============================================================================================================
  TFile *file = TFile::Open("HHTo4BPlots_OptimizeCuts.root", "UPDATE");
  file->cd();

  for(int i=0; i<int(cutSets.size()); i++) {
    file->WriteTObject(histJet2Mass_data[i], Form("histJet2Mass_data_CutSet%d",i), "WriteDelete");
    file->WriteTObject(histJet2Mass_signal[i], Form("histJet2Mass_signal_CutSet%d",i), "WriteDelete");
  }
  
  file->Close();
  delete file;       

  return result;
}






void SelectHHTo4B_OptimizeCuts_2ndBin(int option = 0) {

  //Cuts are defined in this fixed sequence: 
  //pt1Low, pt2Low, Xbb1Low, Xbb2Low, mass1Low, mass1High,  
  std::vector<std::vector<double> > cutSets;

 
  for (int i=0; i<300; i++) {
    double cut = 0.00 + i * ( 0.0001);
 
    cutSets.push_back( makeCutSet( -999, -999, 0.940, 0.940, -999, 999, -999, -999, -999, -999 , -999, -999, -999, -999, -999, -999, -999, -999, -999, -999, -999, -999, -999, -999, cut, -999 ) );  //v24      
    //cutSets.push_back( makeCutSet( -999, -999, -999, 0.95, -999, 999, -999, -999, -999, -999 , -999, -999, -999, -999, -999, -999, -999, -999, -999, -999, -999, -999, -999, -999, cut, -999 ) );  //v8p2      
    
  }

 

  std::vector<std::string> datafiles_2016; 
  std::vector<std::string> datafiles_2017; 
  std::vector<std::string> datafiles_2018; 
  std::vector<std::string> sigfiles_2016;
  std::vector<std::string> sigfiles_2017;
  std::vector<std::string> sigfiles_2018;

  datafiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/HHTo4BNtupler/20201117/option5/combined/BDT/Jet2Xbb0p8Skim/2016/JetHT_2016_GoodLumi_BDTs_Jet2Xbb0p8Skim.root");     
  sigfiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/HHTo4BNtupler/20201117/option5/combined/BDT/Jet2Xbb0p8Skim/2016/GluGluToHHTo4B_node_cHHH1_TuneCUETP8M1_PSWeights_13TeV-powheg-pythia8_1pb_weighted_Testing_BDTs_Jet2Xbb0p8Skim.root");
  
  datafiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/HHTo4BNtupler/20201117/option5/combined/BDT/Jet2Xbb0p8Skim/2017/JetHT_2017_GoodLumi_BDTs_Jet2Xbb0p8Skim.root");    
  sigfiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/HHTo4BNtupler/20201117/option5/combined/BDT/Jet2Xbb0p8Skim/2017/GluGluToHHTo4B_node_cHHH1_TuneCP5_PSWeights_13TeV-powheg-pythia8_1pb_weighted_Testing_BDTs_Jet2Xbb0p8Skim.root");    

  datafiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/HHTo4BNtupler/20201117/option5/combined/BDT/Jet2Xbb0p8Skim/2018/JetHT_2018_GoodLumi_BDTs_Jet2Xbb0p8Skim.root");  
  sigfiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/HHTo4BNtupler/20201117/option5/combined/BDT/Jet2Xbb0p8Skim/2018/GluGluToHHTo4B_node_cHHH1_TuneCP5_PSWeights_13TeV-powheg-pythia8_1pb_weighted_Testing_BDTs_Jet2Xbb0p8Skim.root");   

  double lumi_2016 = 35922;
  double lumi_2017 = 41480;
  double lumi_2018 = 59741;
   
  //*********************************************************************
  //SR Selection
  //********************************************************************* 
  std::pair<double,double> tmpPair = std::pair<double,double>(0,0);
  std::vector<std::pair<double,double> > result_2016;
  std::vector<std::pair<double,double> > result_2017;
  std::vector<std::pair<double,double> > result_2018;

  for (uint i=0; i < cutSets.size(); ++i) {
    result_2016.push_back(tmpPair);
    result_2017.push_back(tmpPair);
    result_2018.push_back(tmpPair);
  }

  result_2016 = RunSelectHHTo4B(cutSets, datafiles_2016, sigfiles_2016, lumi_2016, "2016");
  result_2017 = RunSelectHHTo4B(cutSets, datafiles_2017, sigfiles_2017, lumi_2017, "2017");
  result_2018 = RunSelectHHTo4B(cutSets, datafiles_2018, sigfiles_2018, lumi_2018, "2018");
  
  //--------------------------------------------------------------------------------------------------------------
  // Compute Figure out Merit
  //==============================================================================================================

  int bestWP = -1;
  double bestWPFOM = 9999;
  double bestWPSignal = 9999;
  double bestWPBkg = 9999;
  for (uint i=0; i < cutSets.size(); ++i) {    
    double tmpSignalYield = result_2016[i].first + result_2017[i].first + result_2018[i].first;
    double tmpBkgYield = result_2016[i].second + result_2017[i].second + result_2018[i].second;
    double figureOfMerit = 2 * sqrt(tmpBkgYield) / tmpSignalYield;    
    cout << "CutSet " << i << " : Sig = " << tmpSignalYield << " , Bkg = " << tmpBkgYield 
    << " | Exp Limit = " << figureOfMerit << "\n";

    if (figureOfMerit < bestWPFOM ) {
      bestWP = i;
      bestWPFOM = figureOfMerit;
      bestWPSignal = tmpSignalYield;
      bestWPBkg = tmpBkgYield;
    }

  }

  cout << "Best WP: " << bestWP << " | " 
       << " Sig = " << bestWPSignal << " , Bkg = " << bestWPBkg 
       << " | Exp Limit = " << bestWPFOM << "\n";

}


//**********************************
//E-Mu Yields :
//**********************************

//MuEG Triggers ( 30 - 20 )
// Data: 148
// MC: 156.16
