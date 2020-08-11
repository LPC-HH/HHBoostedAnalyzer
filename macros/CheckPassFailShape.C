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

//*************************************************************************************************
//Normalize Hist
//*************************************************************************************************
void NormalizeHist(TH1 *hist) {
  Double_t norm = 0;
  for (UInt_t b=0; int(b)<hist->GetXaxis()->GetNbins()+2; ++b) {
    norm += hist->GetBinContent(b);
  }
  for (UInt_t b=0; int(b)<hist->GetXaxis()->GetNbins()+2; ++b) {
    hist->SetBinContent(b,hist->GetBinContent(b) / norm);
    hist->SetBinError(b,hist->GetBinError(b) / norm);
  }
}

TH1F* MakePassOverFailRatio( TH1F* pass, TH1F* fail ) {

  TH1F *ratioHist = (TH1F*)pass->Clone("histJet2Mass_PassOverFailRatio");
  
  for (UInt_t b=0; int(b)<ratioHist->GetXaxis()->GetNbins()+2; ++b) {
    double ratio = 1;
    double ratioErr = 0;
    if ( fail->GetBinContent(b) > 0 ) {
      ratio = pass->GetBinContent(b)/fail->GetBinContent(b);
      ratioErr = sqrt( pow( pass->GetBinError(b) / pass->GetBinContent(b) , 2) + 
		       pow( fail->GetBinError(b) / fail->GetBinContent(b) , 2));
    }
    ratioHist->SetBinContent(b,ratio);
    ratioHist->SetBinError(b,ratioErr);    
  }
 
  return ratioHist;
}


double getTriggerEff( TH2F *trigEffHist , double pt, double mass ) {
  double result = 0.0;
  double tmpMass = 0;
  double tmpPt = 0;

  if (trigEffHist) {
      // constrain to histogram bounds
      if( mass > trigEffHist->GetXaxis()->GetXmax() * 0.999 ) {
	tmpMass = trigEffHist->GetXaxis()->GetXmax() * 0.999;
      } else if ( mass < 0 ) {
	tmpMass = 0.001;
	//cout << "Warning: mass=" << mass << " is negative and unphysical\n";
      } else {
	tmpMass = mass;
      }

      if( pt > trigEffHist->GetYaxis()->GetXmax() * 0.999 ) {
	tmpPt = trigEffHist->GetYaxis()->GetXmax() * 0.999;
      } else if (pt < 0) {
	tmpPt = 0.001;
	cout << "Warning: pt=" << pt << " is negative and unphysical\n";
      } else {
	tmpPt = pt;
      }

      result = trigEffHist->GetBinContent(
				 trigEffHist->GetXaxis()->FindFixBin( tmpMass ),
				 trigEffHist->GetYaxis()->FindFixBin( tmpPt )
				 );  
         
  } else {
    std::cout << "Error: expected a histogram, got a null pointer" << std::endl;
    return 0;
  }
  
  //cout << "mass = " << mass << " , pt = " << pt << " : trigEff = " << result << "\n";

  return result; 
}

void PlotPassVsFail( TH1F* histPass, TH1F* histFail, TH1F* ratio, double lumi, string label ) {

  TCanvas *cv =0;
  TLegend *legend = 0;

  cv = new TCanvas("cv","cv", 800,700);
  cv->SetHighLightColor(2);
  cv->SetFillColor(0);
  cv->SetBorderMode(0);
  cv->SetBorderSize(2);
  cv->SetLeftMargin(0.16);
  cv->SetRightMargin(0.3);
  cv->SetTopMargin(0.07);
  cv->SetBottomMargin(0.12);
  cv->SetFrameBorderMode(0);  

  TPad *pad1 = new TPad("pad1","pad1", 0,0.25,1,1);
  pad1->SetBottomMargin(0.0);
  pad1->SetRightMargin(0.04);
  pad1->Draw();
  pad1->cd();

  legend = new TLegend(0.60,0.50,0.90,0.84);
  legend->SetTextSize(0.04);
  legend->SetBorderSize(0);
  legend->SetFillStyle(0);
  legend->AddEntry(histPass,"Pass", "LP");
  legend->AddEntry(histFail,"Fail", "LP");

  histFail->SetStats(0);
  histFail->Draw("hist");
  histFail->GetYaxis()->SetTitleOffset(1.0);
  histFail->GetYaxis()->SetTitleSize(0.05);
  histFail->GetXaxis()->SetTitleSize(0.15);
  histFail->SetMaximum( 1.2*(fmax(histPass->GetMaximum(),histFail->GetMaximum())));
  histFail->SetMinimum( 0.0 );
  histFail->SetLineWidth(2);
  histFail->SetLineColor(kBlue);

  histPass->SetLineWidth(2);
  histPass->SetLineColor(kRed);
  histPass->Draw("e1,same");

  legend->Draw();

  //****************************
  //Add CMS and Lumi Labels
  //****************************
  // lumi_13TeV = "42 pb^{-1}";
  lumi_13TeV = Form("%.1f fb^{-1}", lumi/1000.0);
  writeExtraText = true;
  relPosX = 0.13;
  CMS_lumi(pad1,4,0);

  cv->cd();
  cv->Update();


  TPad *pad2 = new TPad("pad2","pad2", 0,0,1,0.25);
  pad2->SetTopMargin(0.01);
  pad2->SetBottomMargin(0.37);
  pad2->SetRightMargin(0.04);
  pad2->SetGridy();
  pad2->Draw();
  pad2->cd();
    
  ratio->GetYaxis()->SetTitle("Ratio");
  ratio->GetYaxis()->SetNdivisions(306);
  ratio->GetYaxis()->SetTitleSize(0.10);
  ratio->GetYaxis()->SetTitleOffset(0.3);
  // ratio->GetYaxis()->SetRangeUser( 0.2+ratio->GetMaximum(), -0.2 + ratio->GetMinimum() );
  ratio->GetYaxis()->SetRangeUser( 0.5, 1.5);
  ratio->GetYaxis()->SetLabelSize(0.10);
  ratio->GetXaxis()->SetLabelSize(0.125);
  ratio->GetXaxis()->SetTitleSize(0.15);
  ratio->GetXaxis()->SetTitleOffset(1.0);
  ratio->SetLineColor(kBlack);
  ratio->SetMarkerStyle(20);      
  ratio->SetMarkerSize(1);
  ratio->SetStats(false);
  ratio->Draw("pe");

  pad1->SetLogy(false);
  cv->SaveAs(Form("HHTo4B_PassFail_%s.png", label.c_str()));
  cv->SaveAs(Form("HHTo4B_PassFail_%s.pdf", label.c_str()));
  
}



//=== MAIN MACRO ================================================================================================= 


void RunCheckPassFailShape(  vector<string> datafiles, double lumi, string yearLabel, int channelOption = -1, string label = "") {
  
  //--------------------------------------------------------------------------------------------------------------
  // Settings 
  //============================================================================================================== 
  TFile *triggerEff2016File = new TFile("/afs/cern.ch/work/s/sixie/public/releases/run2/analysis/CMSSW_10_6_8/src/HHBoostedAnalyzer/data/JetHTTriggerEfficiency_2016.root","READ");
  TFile *triggerEff2017File = new TFile("/afs/cern.ch/work/s/sixie/public/releases/run2/analysis/CMSSW_10_6_8/src/HHBoostedAnalyzer/data/JetHTTriggerEfficiency_2017.root","READ");
  TFile *triggerEff2018File = new TFile("/afs/cern.ch/work/s/sixie/public/releases/run2/analysis/CMSSW_10_6_8/src/HHBoostedAnalyzer/data/JetHTTriggerEfficiency_2018.root","READ");
  TH2F *triggerEff2016Hist = (TH2F*)triggerEff2016File->Get("efficiency_ptmass");
  TH2F *triggerEff2017Hist = (TH2F*)triggerEff2017File->Get("efficiency_ptmass");
  TH2F *triggerEff2018Hist = (TH2F*)triggerEff2018File->Get("efficiency_ptmass");

  //*****************************************************************************************
  //Make some histograms
  //*****************************************************************************************

  TH1F *histJet2Mass_Pass = new TH1F(Form("histJet2Mass_Pass_%s",label.c_str()), "; Jet2 Mass [GeV] ; Number of Events", 30, 0, 300);
  TH1F *histJet2Mass_Fail = new TH1F(Form("histJet2Mass_Fail_%s",label.c_str()), "; Jet2 Mass [GeV] ; Number of Events", 30, 0, 300);
  histJet2Mass_Pass->Sumw2();
  histJet2Mass_Fail->Sumw2();
  

  //*******************************************************************************************
  //Read file
  //*******************************************************************************************                
  for (uint j=0; j < datafiles.size(); ++j) {

    TFile *file = new TFile(datafiles[j].c_str(),"READ");
    TTree *tree = 0;
    if (!file) {
      cout << "Input file " << datafiles[j] << " could not be opened\n"; 
      continue;
    } else {
      tree = (TTree*)file->Get("tree");
    }
    if (!tree) {
      cout << "Tree could not be found in input file " << datafiles[j] << "\n"; 
      continue;
    }

    float weight = 0;
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
 
    
    cout << "file " << datafiles[j] << " | Total Entries: " << tree->GetEntries() << "\n";

    for(UInt_t ientry=0; ientry < tree->GetEntries(); ientry++) {       	
      tree->GetEntry(ientry);
      
      bool isData = false;
      if (channelOption == 0 || channelOption == 1 || channelOption == 2) isData = true;

      if (ientry % 100000 == 0) cout << "Event " << ientry << endl;      

      double puWeight = 1;      
      double myWeight = 1;
      if (!isData) {	 
	myWeight = lumi * weight;
      }

      //******************************
      //Trigger Selection
      //******************************
      bool passTrigger = false;

      if (yearLabel == "2016") {
	passTrigger = 
	  (0 == 1)
	  || HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20
	  || HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20
	  || HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20	 	    
	  ;       

	// apply trigger efficiency correction for some triggers that were not enabled for full run
	if (!isData) {	 
	  passTrigger = true;
	  double triggerEff = 1.0 - 
	    (1 - getTriggerEff( triggerEff2016Hist , fatJet1Pt, fatJet1MassSD )) * 
	    (1 - getTriggerEff( triggerEff2016Hist , fatJet2Pt, fatJet2MassSD ))
	    ;
	  myWeight = myWeight * triggerEff;
	}

      }
      if (yearLabel == "2017") {
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

	// apply trigger efficiency correction for some triggers that were not enabled for full run
	if (!isData) {	 
	  passTrigger = true;
	  double triggerEff = 1.0 - 
	    (1 - getTriggerEff( triggerEff2017Hist , fatJet1Pt, fatJet1MassSD )) * 
	    (1 - getTriggerEff( triggerEff2017Hist , fatJet2Pt, fatJet2MassSD ))
	    ;
	  myWeight = myWeight * triggerEff;
	}

      }


      if (yearLabel == "2018") {
	passTrigger = 
	  (0 == 1) 
	  || HLT_AK8PFJet400_TrimMass30 
	  || HLT_AK8PFHT800_TrimMass50     
	  || HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4 
	  ;    

	// apply trigger efficiency correction for some triggers that were not enabled for full run
	if (!isData) {	  	  
	  passTrigger = true;
	  double triggerEff = 1.0 - 
	    (1 - getTriggerEff( triggerEff2018Hist , fatJet1Pt, fatJet1MassSD )) * 
	    (1 - getTriggerEff( triggerEff2018Hist , fatJet2Pt, fatJet2MassSD ))
	    ;
	  myWeight = myWeight * triggerEff;
	}   
      }
      
      if (!passTrigger) continue;

      //******************************
      //Selection Cuts 
      //******************************
      if ( !(fatJet1Pt > 300 )) continue;
      if ( !(fatJet2Pt > 300 )) continue;
      if ( !(fatJet1MassSD > 50)) continue;
      if ( !(fatJet2MassSD > 50)) continue;
   
      //Sideband-SR selection
      if (channelOption == 0) {
	if ( !(fatJet1Pt > 350 || fatJet2Pt > 350)) continue;
	if ( !(fatJet1Pt > 300 && fatJet2Pt > 300 )) continue;
	//if ( !(fatJet1PNetXbb > 0.975)) continue;
	//if ( !(fatJet1MassSD > 100 && fatJet1MassSD < 140)) continue;
	if ( (fatJet2MassSD > 95 && fatJet2MassSD < 135)) continue;
      }

      //TT-CR selection
      if (channelOption == 1) {
	if ( !(fatJet1Pt > 350 || fatJet2Pt > 350)) continue;
	if ( !(fatJet1Pt > 300 && fatJet2Pt > 300 )) continue;
	if ( !(fatJet1Tau3OverTau2 < 0.46)) continue;
	if ( !(fatJet2Tau3OverTau2 < 0.46)) continue;
	if ( !fatJet1HasBJetCSVLoose) continue;
	if ( !fatJet2HasBJetCSVLoose) continue;
	// if ( !(fatJet1PNetXbb > 0.5)) continue;
	// if ( !(fatJet2PNetXbb > 0.5)) continue;
	//if ( !(fatJet1MassSD > 100 && fatJet1MassSD < 140)) continue;
      }

      //QCD-CR selection
      if (channelOption == 2) {
	if ( !(fatJet1Pt > 350 || fatJet2Pt > 350)) continue;
	if ( !(fatJet1Pt > 300 && fatJet2Pt > 300 )) continue;
	if ( !(fatJet1Tau3OverTau2 > 0.46)) continue;
	if ( !(fatJet2Tau3OverTau2 > 0.46)) continue;
	if ( !(fatJet1PNetXbb < 0.9)) continue;
	if ( !(fatJet1MassSD > 100 && fatJet1MassSD < 140)) continue;
      }

      //TT-MC selection
      if (channelOption ==6) {
	if ( !(fatJet1Pt > 350 || fatJet2Pt > 350)) continue;
	if ( !(fatJet1Pt > 300 && fatJet2Pt > 300 )) continue;
	if ( !(fatJet1PNetXbb > 0.975)) continue;
	if ( !(fatJet1MassSD > 100 && fatJet1MassSD < 140)) continue;
      }
      //QCD-MC selection
      if (channelOption ==7) {
	if ( !(fatJet1Pt > 350 || fatJet2Pt > 350)) continue;
	if ( !(fatJet1Pt > 300 && fatJet2Pt > 300 )) continue;
	// if ( !(fatJet1PNetXbb > 0.975)) continue;
	// if ( !(fatJet1MassSD > 100 && fatJet1MassSD < 140)) continue;	
      }
      //WHZH-MC selection
      if (channelOption ==8) {
	if ( !(fatJet1Pt > 350 || fatJet2Pt > 350)) continue;
	if ( !(fatJet1Pt > 300 && fatJet2Pt > 300 )) continue;
	if ( !(fatJet1PNetXbb > 0.975)) continue;
	if ( !(fatJet1MassSD > 100 && fatJet1MassSD < 140)) continue;
      }

      //******************************
      //Fill histograms
      //******************************
      if (fatJet2PNetXbb > 0.975) {
	histJet2Mass_Pass->Fill(fatJet2MassSD);
      } else {
	histJet2Mass_Fail->Fill(fatJet2MassSD);      
      }
     
    } //loop over events
  } //loop over input files
 
  //--------------------------------------------------------------------------------------------------------------
  // Normalize
  //==============================================================================================================
  NormalizeHist( histJet2Mass_Pass);
  NormalizeHist( histJet2Mass_Fail);

  //--------------------------------------------------------------------------------------------------------------
  // Make Pass/Fail Ratio Plot
  //==============================================================================================================
  TH1F *histJet2Mass_PassOverFailRatio = MakePassOverFailRatio(histJet2Mass_Pass, histJet2Mass_Fail);

  //--------------------------------------------------------------------------------------------------------------
  // Draw
  //==============================================================================================================
  TCanvas *cv =0;
  TLegend *legend = 0;

  //*******************************************************************************************
  //MR
  //*******************************************************************************************
  PlotPassVsFail( histJet2Mass_Pass, histJet2Mass_Fail, histJet2Mass_PassOverFailRatio, lumi, label);


  //--------------------------------------------------------------------------------------------------------------
  // Tables
  //==============================================================================================================
  cout << "For Luminosity = " << lumi << " pb^-1\n";
 
  // //--------------------------------------------------------------------------------------------------------------
  // // Output
  // //==============================================================================================================
  TFile *file = TFile::Open("CheckPassFailShape.root", "UPDATE");
  file->cd();
  file->WriteTObject(histJet2Mass_Pass, Form("histJet2Mass_Pass_%s",label.c_str()), "WriteDelete");
  file->WriteTObject(histJet2Mass_Fail, Form("histJet2Mass_Fail_%s",label.c_str()), "WriteDelete");  
  file->WriteTObject(histJet2Mass_PassOverFailRatio, Form("histJet2Mass_PassOverFailRatio_%s",label.c_str()), "WriteDelete");  
  
  file->Close();
  delete file;       

}







void CheckPassFailShape( int option = 0) {

  vector<string> files_data;
  vector<string> files_TT;
  vector<string> files_QCD;
  vector<string> files_WHZH;

  if (option == 0 ) {
    files_data.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2016/JetHT_2016B-ver2.root");
    files_data.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2016/JetHT_2016C.root");
    files_data.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2016/JetHT_2016D.root");
    files_data.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2016/JetHT_2016E.root");
    files_data.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2016/JetHT_2016F.root");
    files_data.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2016/JetHT_2016H.root");

    files_TT.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2016/TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8_1pb_weighted.root");
    files_TT.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2016/TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8_1pb_weighted.root");

    files_QCD.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2016/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-combined_1pb_weighted.root");
    files_QCD.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2016/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-combined_1pb_weighted.root");
    files_QCD.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2016/QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-combined_1pb_weighted.root");
    files_QCD.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2016/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-combined_1pb_weighted.root");
    files_QCD.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2016/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-combined_1pb_weighted.root");
    files_QCD.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2016/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-combined_1pb_weighted.root");

    files_WHZH.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2016/ZH_HToBB_ZToQQ_M125_13TeV_powheg_pythia8_1pb_weighted.root");
  }

  if (option == 1 ) {
    files_data.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2017/JetHT_2017B.root");
    files_data.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2017/JetHT_2017C.root");
    files_data.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2017/JetHT_2017D.root");
    files_data.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2017/JetHT_2017E.root");
    files_data.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2017/JetHT_2017F.root");

    files_TT.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2017/TTToHadronic_TuneCP5_13TeV-powheg-pythia8_1pb_weighted.root");
    files_TT.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2017/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8_1pb_weighted.root");

    files_QCD.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2017/QCD_HT300to500_TuneCP5_13TeV-madgraph-pythia8_1pb_weighted.root");
    files_QCD.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2017/QCD_HT500to700_TuneCP5_13TeV-madgraph-pythia8_1pb_weighted.root");
    files_QCD.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2017/QCD_HT700to1000_TuneCP5_13TeV-madgraph-pythia8_1pb_weighted.root");
    files_QCD.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2017/QCD_HT1000to1500_TuneCP5_13TeV-madgraph-pythia8_1pb_weighted.root");
    files_QCD.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2017/QCD_HT1500to2000_TuneCP5_13TeV-madgraph-pythia8_1pb_weighted.root");
    files_QCD.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2017/QCD_HT2000toInf_TuneCP5_13TeV-madgraph-pythia8_1pb_weighted.root");

    files_WHZH.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2017/ZH_HToBB_ZToQQ_M125_13TeV_powheg_pythia8_1pb_weighted.root");
    files_WHZH.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2017/WminusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8_1pb_weighted.root");
    files_WHZH.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2017/WplusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8_1pb_weighted.root");
  }
 
  if (option == 2) {
    files_data.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2018/JetHT_2018A.root");
    files_data.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2018/JetHT_2018B.root");
    files_data.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2018/JetHT_2018C.root");
    files_data.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2018/JetHT_2018D.root");

    files_TT.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2018/TTToHadronic_TuneCP5_13TeV-powheg-pythia8-combined_1pb_weighted.root");
    files_TT.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2018/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8-combined_1pb_weighted.root");

    files_QCD.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2018/QCD_HT300to500_TuneCP5_13TeV-madgraphMLM-pythia8_1pb_weighted.root");
    files_QCD.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2018/QCD_HT500to700_TuneCP5_13TeV-madgraphMLM-pythia8_1pb_weighted.root");
    files_QCD.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2018/QCD_HT700to1000_TuneCP5_13TeV-madgraphMLM-pythia8_1pb_weighted.root");
    files_QCD.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2018/QCD_HT1000to1500_TuneCP5_13TeV-madgraphMLM-pythia8_1pb_weighted.root");
    files_QCD.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2018/QCD_HT1500to2000_TuneCP5_13TeV-madgraphMLM-pythia8_1pb_weighted.root");
    files_QCD.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2018/QCD_HT2000toInf_TuneCP5_13TeV-madgraphMLM-pythia8_1pb_weighted.root"); 

    files_WHZH.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2018/ZH_HToBB_ZToQQ_M125_13TeV_powheg_pythia8_1pb_weighted.root");
    files_WHZH.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2018/WminusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8_1pb_weighted.root");
    files_WHZH.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/v11/combined/2018/WplusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8_1pb_weighted.root");
  }


  double lumi = 0;
  string yearlabel = "";
  if (option == 0 ) {
    lumi = 35922;
    yearlabel = "2016";
  } 
  if (option == 1 ) {
    lumi = 41480;
    yearlabel = "2017";    
  } 
  if (option == 2 ) {
    lumi = 59741;
    yearlabel = "2018";
  } 
  
  //*********************************************************************
  //Plotter
  //********************************************************************* 
  //RunCheckPassFailShape(files_data,lumi,yearlabel,0, "SidebandSR_"+yearlabel); //sideband SR
  //RunCheckPassFailShape(files_data,lumi,yearlabel,1, "TTCR_"+yearlabel); //TT CR
  // RunCheckPassFailShape(files_data,lumi,yearlabel,2, "QCDCR_"+yearlabel); //QCD CR
  //RunCheckPassFailShape(files_TT,lumi,yearlabel,6, "TTMC_"+yearlabel);   //TT MC
  // RunCheckPassFailShape(files_QCD,lumi,yearlabel,7, "QCDMC_"+yearlabel);  //QCD MC
  RunCheckPassFailShape(files_WHZH,lumi,yearlabel,8, "WHZHMC_"+yearlabel); //WHZH MC

}


//**********************************
//E-Mu Yields :
//**********************************

//MuEG Triggers ( 30 - 20 )
// Data: 148
// MC: 156.16
