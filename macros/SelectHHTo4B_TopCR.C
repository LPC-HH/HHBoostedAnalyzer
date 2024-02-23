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


double TopTagSF( string workingPoint, string year, double pt ) {
  double result = 1.0;
  if (workingPoint == "0.46") {
    if (year == "2016") {
      if (pt > 600) {
	result = 1.00;
      } else if (pt > 480) { 
	result = 0.988;
      } else if (pt > 400) { 
	result = 0.976;
      } else if (pt > 300) { 
	result = 0.93;
      } else {
	result = 0.93; //this isn't measured, so we take the value of the last bin measured. 
      }      
    } 
    else if (year == "2017") {
      if (pt > 600) {
	result = 0.87;
      } else if (pt > 480) { 
	result = 0.89;
      } else if (pt > 400) { 
	result = 0.95;
      } else if (pt > 300) { 
	result = 0.93;
      } else {
	result = 0.93; //this isn't measured, so we take the value of the last bin measured. 
      }      
    } 
    else if (year == "2018") {
      if (pt > 600) {
	result = 0.847;
      } else if (pt > 480) { 
	result = 0.93;
      } else if (pt > 400) { 
	result = 0.976;
      } else if (pt > 300) { 
	result = 0.93;
      } else {
	result = 0.93; //this isn't measured, so we take the value of the last bin measured. 
      }      
    } 
    else {
      cout << "[TopTagSF] Warning: year=" << year << " is not supported\n";
    }
  }  else {
    cout << "[TopTagSF] Warning: workingPoint=" << workingPoint << " is not supported\n";
  }
  return result;   
}

void PlotDataAndStackedBkg( vector<TH1D*> hist , vector<string> processLabels, vector<int> color,  bool hasData, string varName, double lumi, string label ) {

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

  THStack *stack = new THStack();
  TH1D *histDataOverMC = (TH1D*)hist[0]->Clone("histDataOverMC");

  if (hasData) {
    for (int i = hist.size()-1; i >= 1; --i) {
      hist[i]->SetFillColor(color[i]);
      hist[i]->SetFillStyle(1001);
      
      if ( hist[i]->Integral() > 0) {
  	stack->Add(hist[i]);
      }
    }
  } else {
    for (int i = hist.size()-1; i >= 0; --i) {
      hist[i]->SetFillColor(color[i]);
      hist[i]->SetFillStyle(1001);
      
      if ( hist[i]->Integral() > 0) {
  	stack->Add(hist[i]);
      }
    }
  }

  for (uint i = 0 ; i < hist.size(); ++i) {
    if (hasData && i==0) {
      legend->AddEntry(hist[i],(processLabels[i]).c_str(), "LP");
    } else {
      legend->AddEntry(hist[i],(processLabels[i]).c_str(), "F");
    }
  }

  if (stack->GetHists()->GetEntries() > 0) {
    stack->Draw("hist");
    stack->GetHistogram()->GetXaxis()->SetTitle(((TH1D*)(stack->GetHists()->At(0)))->GetXaxis()->GetTitle());
    stack->GetHistogram()->GetYaxis()->SetTitle(((TH1D*)(stack->GetHists()->At(0)))->GetYaxis()->GetTitle());    
    stack->GetHistogram()->GetYaxis()->SetTitleOffset(1.0);
    stack->GetHistogram()->GetYaxis()->SetTitleSize(0.05);
    stack->GetHistogram()->GetXaxis()->SetTitleSize(0.15);
    stack->SetMaximum( 1.2* fmax( stack->GetMaximum(), hist[0]->GetMaximum()) );
    stack->SetMinimum( 0.1 );

    if (hasData) {
     hist[0]->SetMarkerStyle(20);      
      hist[0]->SetMarkerSize(1);
      hist[0]->SetLineWidth(1);
      hist[0]->SetLineColor(color[0]);
      hist[0]->Draw("pesame");
    }
    legend->Draw();
 }

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
    
  for (int b=0; b<histDataOverMC->GetXaxis()->GetNbins()+2; ++b) {
    double data = 0;
    if (hasData) {
      data = hist[0]->GetBinContent(b);
    }
    double MC = 0;
    double MCErrSqr = 0;
    if (hasData) {
      for (uint i = 1 ; i < hist.size(); ++i) {
	MC += hist[i]->GetBinContent(b);
	MCErrSqr += pow(hist[i]->GetBinError(b),2);
      }
    } else {
      MC = 1;
    }
      
    if (MC > 0) {
      histDataOverMC->SetBinContent(b, data / MC);
      histDataOverMC->SetBinError(b, (data / MC)*sqrt(1/data + MCErrSqr/pow(MC,2) ));
    } else {
      histDataOverMC->SetBinContent(b, 0);
      histDataOverMC->SetBinError(b, 0);
    }
    //cout << "bin " << b << " : " << histDataOverMC->GetBinContent(b) << " " << histDataOverMC->GetBinError(b) << "\n";
  }

  histDataOverMC->GetYaxis()->SetTitle("Data/MC");
  histDataOverMC->GetYaxis()->SetNdivisions(306);
  histDataOverMC->GetYaxis()->SetTitleSize(0.10);
  histDataOverMC->GetYaxis()->SetTitleOffset(0.3);
  histDataOverMC->GetYaxis()->SetRangeUser(0.5,1.5);
  histDataOverMC->GetYaxis()->SetLabelSize(0.10);
  histDataOverMC->GetXaxis()->SetLabelSize(0.125);
  histDataOverMC->GetXaxis()->SetTitleSize(0.15);
  histDataOverMC->GetXaxis()->SetTitleOffset(1.0);
  histDataOverMC->SetLineColor(kBlack);
  histDataOverMC->SetMarkerStyle(20);      
  histDataOverMC->SetMarkerSize(1);
  histDataOverMC->SetStats(false);
  histDataOverMC->Draw("pe");

  pad1->SetLogy(false);
  cv->SaveAs(Form("HHTo4B_TopCR_%s%s.png",varName.c_str(), label.c_str()));
  cv->SaveAs(Form("HHTo4B_TopCR_%s%s.pdf",varName.c_str(), label.c_str()));
  
  pad1->SetLogy(true);
  cv->SaveAs(Form("HHTo4B_TopCR_%s%s_Logy.png",varName.c_str(),label.c_str()));
  cv->SaveAs(Form("HHTo4B_TopCR_%s%s_Logy.pdf",varName.c_str(),label.c_str()));


 

}



//=== MAIN MACRO ================================================================================================= 


void RunSelectHHTo4B(  vector<string> datafiles, vector<vector<string> > bkgfiles, vector<string> bkgLabels, vector<int> bkgColors, vector<float> bkgScaleFactors,double lumi, string option, int channelOption = -1, string label = "") {
  
  string Label = "";
  if (label != "") Label = "_" + label;

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
  vector<vector<string> > inputfiles;
  vector<string> processLabels;
  vector<int> color;
  vector<float> scaleFactors;

  inputfiles.push_back(datafiles);
  processLabels.push_back("Data");
  color.push_back(kBlack);
  scaleFactors.push_back(1.0);

  assert(bkgfiles.size() == bkgLabels.size());
  assert(bkgfiles.size() == bkgColors.size());
  assert(bkgfiles.size() == bkgScaleFactors.size());
  for (int i=0; i < int(bkgfiles.size()); ++i) {
    inputfiles.push_back(bkgfiles[i]);
    processLabels.push_back(bkgLabels[i]);
    color.push_back(bkgColors[i]);
    scaleFactors.push_back(bkgScaleFactors[i]);
   
  }
  for (int i=0; i < int(inputfiles.size()); ++i) {
    cout << processLabels[i] << " : " << scaleFactors[i] << "\n";
  }


  vector<TH1D*> histMET;
  vector<TH1D*> histNLeptons;
  vector<TH1D*> histNJetsHaveLeptons;
  vector<TH1D*> histJet1Mass;
  vector<TH1D*> histJet1Pt;
  vector<TH1D*> histJet1DDB;
  vector<TH1D*> histJet1PNetXbb;
  vector<TH1D*> histJet1Tau3OverTau2;
  vector<TH1D*> histJet2Mass;
  vector<TH1D*> histJet2Pt;
  vector<TH1D*> histJet2DDB;
  vector<TH1D*> histJet2PNetXbb;
  vector<TH1D*> histJet2Tau3OverTau2;
  vector<TH1D*> histHHPt;
  vector<TH1D*> histHHMass;

  assert (inputfiles.size() == processLabels.size());
  for (uint i=0; i < inputfiles.size(); ++i) {
    histMET.push_back(new TH1D(Form("histMET_%s",processLabels[i].c_str()), "; MET [GeV] ; Number of Events", 25, 0, 200));
    histNLeptons.push_back(new TH1D(Form("histNLeptons_%s",processLabels[i].c_str()), "; NLeptons ; Number of Events", 10, -0.5, 9.5));
    histNJetsHaveLeptons.push_back(new TH1D(Form("histNJetsHaveLeptons_%s",processLabels[i].c_str()), "; NJetsHaveLeptons ; Number of Events", 3, -0.5, 2.5));
    histJet1Mass.push_back(new TH1D(Form("histJet1Mass_%s",processLabels[i].c_str()), "; Jet1 Mass [GeV] ; Number of Events", 25, 0, 500));
    histJet1Pt.push_back(new TH1D(Form("histJet1Pt_%s",processLabels[i].c_str()), "; Jet1 p_{T} [GeV] ; Number of Events", 25, 0, 2000));
    histJet1DDB.push_back(new TH1D(Form("histJet1DDB_%s",processLabels[i].c_str()), "; Jet1 DDB ; Number of Events", 25, 0, 1.0));
    histJet1PNetXbb.push_back(new TH1D(Form("histJet1PNetXbb_%s",processLabels[i].c_str()), "; Jet1 PNetXbb ; Number of Events", 25, 0, 1.0));
    histJet1Tau3OverTau2.push_back(new TH1D(Form("histJet1Tau3OverTau2_%s",processLabels[i].c_str()), "; Jet1 Tau3OverTau2 ; Number of Events", 25, 0, 1.0));
    histJet2Mass.push_back(new TH1D(Form("histJet2Mass_%s",processLabels[i].c_str()), "; Jet2 Mass [GeV] ; Number of Events", 25, 0, 500));
    histJet2Pt.push_back(new TH1D(Form("histJet2Pt_%s",processLabels[i].c_str()), "; Jet2 p_{T} [GeV] ; Number of Events", 25, 0, 1000));
    histJet2DDB.push_back(new TH1D(Form("histJet1DDB_%s",processLabels[i].c_str()), "; Jet2 DDB ; Number of Events", 25, 0, 1.0));
    histJet2PNetXbb.push_back(new TH1D(Form("histJet2PNetXbb_%s",processLabels[i].c_str()), "; Jet2 PNetXbb ; Number of Events", 25, 0, 1.0));
    histJet2Tau3OverTau2.push_back(new TH1D(Form("histJet1Tau3OverTau2_%s",processLabels[i].c_str()), "; Jet2 Tau3OverTau2 ; Number of Events", 25, 0, 1.0));
    histHHPt.push_back(new TH1D(Form("histHHPt_%s",processLabels[i].c_str()), "; HH p_{T} [GeV] ; Number of Events", 25, 0, 1000));
    histHHMass.push_back(new TH1D(Form("histHHMass_%s",processLabels[i].c_str()), "; HH Mass [GeV] ; Number of Events", 50, 0, 3000));

    histMET[i]->Sumw2();
    histNLeptons[i]->Sumw2();
    histNJetsHaveLeptons[i]->Sumw2();
    histJet1Mass[i]->Sumw2();
    histJet1Pt[i]->Sumw2();
    histJet1DDB[i]->Sumw2();
    histJet1PNetXbb[i]->Sumw2();
    histJet1Tau3OverTau2[i]->Sumw2();
    histJet2Mass[i]->Sumw2();
    histJet2Pt[i]->Sumw2();
    histJet2DDB[i]->Sumw2();
    histJet2PNetXbb[i]->Sumw2();
    histJet2Tau3OverTau2[i]->Sumw2();
    histHHPt[i]->Sumw2();
    histHHMass[i]->Sumw2();
  }
 
  double dataYield = 0;
  double MCYield = 0;
  double SignalYield = 0;
  double testYield = 0;

  //*******************************************************************************************
  //Read file
  //*******************************************************************************************                
  for (uint i=0; i < inputfiles.size(); ++i) {

    //for duplicate event checking
    map<pair<uint,uint>, bool > processedRunEvents;

    for (uint j=0; j < inputfiles[i].size(); ++j) {

      TFile *file = new TFile(inputfiles[i][j].c_str(),"READ");
      TTree *tree = 0;
      if (!file) {
	cout << "Input file " << inputfiles[i][j] << " could not be opened\n"; 
	continue;
      } else {
	tree = (TTree*)file->Get("tree");
      }
      if (!tree) {
	cout << "Tree could not be found in input file " << inputfiles[i][j] << "\n"; 
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


      bool isData = false;
      if ( processLabels[i] == "Data") isData = true;
    
      cout << "process: " << processLabels[i] << " | file " << inputfiles[i][j] << " | Total Entries: " << tree->GetEntries() << "\n";

      for(UInt_t ientry=0; ientry < tree->GetEntries(); ientry++) {       	
	tree->GetEntry(ientry);
      

	if (ientry % 100000 == 0) cout << "Event " << ientry << endl;      

	double puWeight = 1;      
	double myWeight = 1;
	if (!isData) {	 
	  myWeight = lumi * weight * scaleFactors[i];
	  //cout << "scaleFactors: " << scaleFactors[i] << "\n";
	}

	//******************************
	//Selection Cuts 
	//******************************
	if ( !(fatJet1Pt > 500 )) continue;
	if ( !(fatJet2Pt > 300 )) continue;
	if ( !(fatJet1MassSD > 50)) continue;
	if ( !(fatJet2MassSD > 30)) continue;


	//******************************
	//Trigger Selection
	//******************************
	bool passTrigger = false;

	if (option == "2016") {
	  passTrigger = 
	    (0 == 1)
	    || HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20
	    || HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20
	    || HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20	 	    
	    ;       

	  // apply trigger efficiency correction for some triggers that were not enabled for full run
	  if (!isData) {
	    // double triggerSF = 1.0;
	    // if (HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20)                         triggerSF = 1.0;
	    // else if (HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20 
	    // 	     || HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20)                 triggerSF = 19.9 / 35.9;	      
	    // else                                                                      triggerSF = 0;
	    // myWeight = myWeight * triggerSF;	  

	    double triggerEff = 1.0 - 
	      (1 - getTriggerEff( triggerEff2016Hist , fatJet1Pt, fatJet1MassSD )) * 
	      (1 - getTriggerEff( triggerEff2016Hist , fatJet2Pt, fatJet2MassSD ))
	      ;
	    myWeight = myWeight * triggerEff;

	  }

	}
	if (option == "2017") {
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
	    // double triggerSF = 1.0;
	    // if (HLT_PFJet500 || HLT_AK8PFJet500)                                    triggerSF = 1.0;
	    // else {
	    //   //cout << "fail\n";
	    //   if (HLT_AK8PFJet400_TrimMass30 || HLT_AK8PFHT800_TrimMass50)          triggerSF = 36.42 / 41.48;
	    //   else if (HLT_AK8PFJet380_TrimMass30)                                    triggerSF = 31.15 / 41.48;            
	    //   else if (HLT_AK8PFJet360_TrimMass30)                                    triggerSF = 28.23 / 41.48;
	    //   else if (HLT_AK8PFJet330_PFAK8BTagCSV_p17)                              triggerSF = 7.73 / 41.48;	    
	    //   else                                                                    triggerSF = 0;
	    //   //cout << "triggerSF = " << triggerSF << "\n";
	    // }
	    // myWeight = myWeight * triggerSF;	  

	    passTrigger = true;
	    double triggerEff = 1.0 - 
	      (1 - getTriggerEff( triggerEff2017Hist , fatJet1Pt, fatJet1MassSD )) * 
	      (1 - getTriggerEff( triggerEff2017Hist , fatJet2Pt, fatJet2MassSD ))
	      ;
	    myWeight = myWeight * triggerEff;

	  }


	}


	if (option == "2018") {
	  passTrigger = 
	     (0 == 1) 
	    || HLT_AK8PFJet400_TrimMass30 
	    || HLT_AK8PFHT800_TrimMass50     
	    || HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4 
	    ;    


	  // apply trigger efficiency correction for some triggers that were not enabled for full run
	  if (!isData) {
	    // double triggerSF = 1.0;
	    // if (HLT_AK8PFJet400_TrimMass30 || HLT_AK8PFHT800_TrimMass50)              triggerSF = 1.0;
	    // else if (HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4)              triggerSF = 54.5 / 59.7;	        
	    // else                                                                      triggerSF = 0;
	    // myWeight = myWeight * triggerSF;	  

	    double triggerEff = 1.0 - 
	      (1 - getTriggerEff( triggerEff2018Hist , fatJet1Pt, fatJet1MassSD )) * 
	      (1 - getTriggerEff( triggerEff2018Hist , fatJet2Pt, fatJet2MassSD ))
	      ;
	    myWeight = myWeight * triggerEff;
	  }
   
	}

	if (!passTrigger) continue;



	// QCD enriched CR
	if (channelOption == 10) {
	  if (!(fatJet1Tau3OverTau2 > 0.46)) continue;
	  if (!(fatJet2Tau3OverTau2 > 0.46)) continue;
	  if (fatJet1HasBJetCSVMedium) continue;
	  if (fatJet2HasBJetCSVMedium) continue;

	}

	//TTbar Hadronic CR
	if (channelOption == 20) {
	  if (!(fatJet1Tau3OverTau2 < 0.46)) continue;
	  if (!(fatJet2Tau3OverTau2 < 0.46)) continue;
	  //if (!(fatJet1PNetXbb > 0.3)) continue;
	  //if (!(fatJet2PNetXbb > 0.3)) continue;
	  if (!fatJet1HasBJetCSVLoose) continue;
	  if (!fatJet2HasBJetCSVLoose) continue;

	  if (processLabels[i] == "TTJets") {
	    double fatJet1TopTagSF = TopTagSF("0.46", option, fatJet1Pt);
	    double fatJet2TopTagSF = TopTagSF("0.46", option, fatJet2Pt);
	    myWeight = myWeight * fatJet1TopTagSF * fatJet2TopTagSF;
	  }
	}
 
	//TTbar Semi-leptonic CR
	if (channelOption == 21) {
	  if (!( 
		((fatJet1HasMuon||fatJet1HasElectron) && fatJet2Tau3OverTau2 < 0.54) ||
		((fatJet2HasMuon||fatJet2HasElectron) && fatJet1Tau3OverTau2 < 0.54)
		 )) continue;
	  if (!fatJet1HasBJetCSVLoose) continue;
	  if (!fatJet2HasBJetCSVLoose) continue;
	}          

	//******************************
	//Fill histograms
	//******************************
	int NJetsHaveLeptons = 0;
	if (fatJet1HasMuon || fatJet1HasElectron) NJetsHaveLeptons++;
	if (fatJet2HasMuon || fatJet2HasElectron) NJetsHaveLeptons++;

	if (isData) {
	  dataYield += 1.0;
	  histMET[i]->Fill(MET);    
	  histNLeptons[i]->Fill(0.0);   
	  histNJetsHaveLeptons[i]->Fill(NJetsHaveLeptons);   
	  histJet1Mass[i]->Fill(fatJet1MassSD);      
	  histJet1Pt[i]->Fill(fatJet1Pt);
	  histJet1DDB[i]->Fill(fatJet1DDBTagger);
	  histJet1PNetXbb[i]->Fill(fatJet1PNetXbb);
	  histJet1Tau3OverTau2[i]->Fill(fatJet1Tau3OverTau2);
	  histJet2Mass[i]->Fill(fatJet2MassSD);      
	  histJet2Pt[i]->Fill(fatJet2Pt);
	  histJet2DDB[i]->Fill(fatJet2DDBTagger);
	  histJet2PNetXbb[i]->Fill(fatJet2PNetXbb);
	  histJet2Tau3OverTau2[i]->Fill(fatJet2Tau3OverTau2);
	  histHHPt[i]->Fill(hh_pt);    
	  histHHMass[i]->Fill(hh_mass);    
	} else {

	  if (processLabels[i] == "HH") {
	    SignalYield += myWeight;
	  } else {
	    MCYield += myWeight;
	  }
	  histMET[i]->Fill(MET, myWeight);    
	  histNLeptons[i]->Fill(0.0, myWeight);   
	  histNJetsHaveLeptons[i]->Fill(NJetsHaveLeptons, myWeight);   
	  histJet1Mass[i]->Fill(fatJet1MassSD, myWeight);      
	  histJet1Pt[i]->Fill(fatJet1Pt, myWeight);
	  histJet1DDB[i]->Fill(fatJet1DDBTagger, myWeight);
	  histJet1PNetXbb[i]->Fill(fatJet1PNetXbb, myWeight);
	  histJet1Tau3OverTau2[i]->Fill(fatJet1Tau3OverTau2, myWeight);
	  histJet2Mass[i]->Fill(fatJet2MassSD, myWeight);      
	  histJet2Pt[i]->Fill(fatJet2Pt, myWeight);
	  histJet2DDB[i]->Fill(fatJet2DDBTagger, myWeight);
	  histJet2PNetXbb[i]->Fill(fatJet2PNetXbb, myWeight);
	  histJet2Tau3OverTau2[i]->Fill(fatJet2Tau3OverTau2, myWeight);
	  histHHPt[i]->Fill(hh_pt, myWeight);    
	  histHHMass[i]->Fill(hh_mass, myWeight);    
	}
      } //loop over events
    } //loop over input files
  } //loop over input process type

  //--------------------------------------------------------------------------------------------------------------
  // Make Plots
  //==============================================================================================================


  //--------------------------------------------------------------------------------------------------------------
  // Draw
  //==============================================================================================================
  TCanvas *cv =0;
  TLegend *legend = 0;

  //*******************************************************************************************
  //MR
  //*******************************************************************************************
  PlotDataAndStackedBkg( histMET, processLabels, color, true, "MET", lumi, Label);
  PlotDataAndStackedBkg( histNLeptons, processLabels, color, true, "NLeptons", lumi, Label);
  PlotDataAndStackedBkg( histNJetsHaveLeptons, processLabels, color, true, "NJetsHaveLeptons", lumi, Label);
  PlotDataAndStackedBkg( histJet1Mass, processLabels, color, true, "Jet1_Mass", lumi, Label);
  PlotDataAndStackedBkg( histJet1Pt, processLabels, color, true, "Jet1_Pt", lumi, Label);
  PlotDataAndStackedBkg( histJet1DDB, processLabels, color, true, "Jet1_DDB", lumi, Label);
  PlotDataAndStackedBkg( histJet1PNetXbb, processLabels, color, true, "Jet1_PNetXbb", lumi, Label);
  PlotDataAndStackedBkg( histJet1Tau3OverTau2, processLabels, color, true, "Jet1_Tau3OverTau2", lumi, Label);
  PlotDataAndStackedBkg( histJet2Mass, processLabels, color, true, "Jet2_Mass", lumi, Label);
  PlotDataAndStackedBkg( histJet2Pt, processLabels, color, true, "Jet2_Pt", lumi, Label);
  PlotDataAndStackedBkg( histJet2DDB, processLabels, color, true, "Jet2_DDB", lumi, Label);
  PlotDataAndStackedBkg( histJet2PNetXbb, processLabels, color, true, "Jet2_PNetXbb", lumi, Label);
  PlotDataAndStackedBkg( histJet2Tau3OverTau2, processLabels, color, true, "Jet2_Tau3OverTau2", lumi, Label);
  PlotDataAndStackedBkg( histHHPt, processLabels, color, true, "HHPt", lumi, Label);
  PlotDataAndStackedBkg( histHHMass, processLabels, color, true, "HHMass", lumi, Label);


  //--------------------------------------------------------------------------------------------------------------
  // Tables
  //==============================================================================================================
  cout << "For Luminosity = " << lumi << " pb^-1\n";
 
  cout << "Selected Event Yield \n";
  cout << "Data: " << dataYield << "\n";
  cout << "MC: " << MCYield << "\n";
  cout << "Signal: " << SignalYield << "\n";
  cout << "test: " << testYield << "\n";

  // //--------------------------------------------------------------------------------------------------------------
  // // Output
  // //==============================================================================================================
  TFile *file = TFile::Open(("HHTo4BPlots"+Label+".root").c_str(), "UPDATE");
  file->cd();

  for(int i=0; i<int(inputfiles.size()); i++) {
    file->WriteTObject(histJet1Mass[i], Form("histJet1Mass_%s",processLabels[i].c_str()), "WriteDelete");
    file->WriteTObject(histJet1Pt[i], Form("histJet1Pt_%s",processLabels[i].c_str()), "WriteDelete");
    file->WriteTObject(histJet2Mass[i], Form("histJet2Mass_%s",processLabels[i].c_str()), "WriteDelete");
    file->WriteTObject(histJet2Pt[i], Form("histJet2Pt_%s",processLabels[i].c_str()), "WriteDelete");
    file->WriteTObject(histNJetsHaveLeptons[i], Form("histNJetsHaveLeptons_%s",processLabels[i].c_str()), "WriteDelete");
    file->WriteTObject(histMET[i], Form("histMET_%s",processLabels[i].c_str()), "WriteDelete");
  } 
  
  file->Close();
  delete file;       

}







void SelectHHTo4B_TopCR( int option = 0) {

  vector<string> datafiles;
  vector<vector<string> > bkgfiles;
  vector<string> processLabels;
  vector<int> colors;
  vector<float> scaleFactors;

  string datafile = "";


  vector<string> bkgfiles_ttbar;
  vector<string> bkgfiles_H;
  vector<string> bkgfiles_VH;
  vector<string> bkgfiles_ttH;  
  vector<string> bkgfiles_qcd; 
  vector<string> bkgfiles_HH; 

  string dataDir = "/eos/cms/store/group/phys_susy/razor/Run3Analysis/HH/HHTo4BNtupler/option10/nano/run3/combined/";


  if (option == 0) {
    datafiles.push_back(dataDir + "2022/JetHTMET_2022.root");
    bkgfiles_ttbar.push_back(dataDir + "2016/TTto4Q_postEE_1pb_weighted.root");  
    bkgfiles_ttbar.push_back(dataDir + "2016/TTtoLNu2Q_PostEE_1pb_weighted.root");  
    bkgfiles_H.push_back(dataDir + "2016/ggHto2B_Pt200ToInf_PostEE_1pb_weighted.root");
    bkgfiles_H.push_back(dataDir + "2016/VBFHto2B_PostEE_1pb_weighted.root");
    bkgfiles_VH.push_back(dataDir + "2016/WminusH_Hto2B_Wto2Q_PostEE_1pb_weighted.root");
    bkgfiles_VH.push_back(dataDir + "2016/WplusH_Hto2B_Wto2Q_PostEE_1pb_weighted.root");
    bkgfiles_VH.push_back(dataDir + "2016/ZH_Hto2B_Zto2Q_PostEE_1pb_weighted.root");
    bkgfiles_VH.push_back(dataDir + "2016/ggZH_Hto2B_Zto2Q_PostEE_1pb_weighted.root");
    bkgfiles_ttH.push_back(dataDir + "2016/ttH_Hto2B_PostEE_1pb_weighted.root");
    bkgfiles_qcd.push_back(dataDir + "2016/QCDPt80to120_postEE_1pb_weighted.root");
    bkgfiles_qcd.push_back(dataDir + "2016/QCDPt120to170_postEE_1pb_weighted.root");
    bkgfiles_qcd.push_back(dataDir + "2016/QCDPt170to300_postEE_1pb_weighted.root");
    bkgfiles_qcd.push_back(dataDir + "2016/QCDPt300to470_postEE_1pb_weighted.root");
    bkgfiles_qcd.push_back(dataDir + "2016/QCDPt470to600_postEE_1pb_weighted.root");
    bkgfiles_qcd.push_back(dataDir + "2016/QCDPt600to800_postEE_1pb_weighted.root");
    bkgfiles_qcd.push_back(dataDir + "2016/QCDPt800to1000_postEE_1pb_weighted.root");
    bkgfiles_qcd.push_back(dataDir + "2016/QCDPt1000to1400_postEE_1pb_weighted.root");
    bkgfiles_qcd.push_back(dataDir + "2016/QCDPt1400to1800_postEE_1pb_weighted.root");
    bkgfiles_qcd.push_back(dataDir + "2016/QCDPt1800to2400_postEE_1pb_weighted.root");
    bkgfiles_qcd.push_back(dataDir + "2016/QCDPt2400to3200_postEE_1pb_weighted.root");
    bkgfiles_qcd.push_back(dataDir + "2016/QCDPt3200toInf_postEE_1pb_weighted.root");
    bkgfiles_HH.push_back(dataDir + "2016/ggHH_cHHH_1_TSG_1pb_weighted.root");
  }



  bkgfiles.push_back(bkgfiles_qcd);
  bkgfiles.push_back(bkgfiles_ttbar);
  bkgfiles.push_back(bkgfiles_H);
  bkgfiles.push_back(bkgfiles_VH);
  bkgfiles.push_back(bkgfiles_ttH);
  bkgfiles.push_back(bkgfiles_HH);

  processLabels.push_back("QCD");
  processLabels.push_back("TTJets");  
  processLabels.push_back("H");
  processLabels.push_back("VH");
  processLabels.push_back("ttH");
  processLabels.push_back("HH");

  colors.push_back(kRed);
  colors.push_back(kAzure+10);
  colors.push_back(kGreen+2);
  colors.push_back(kGray);
  colors.push_back(kBlue);
  colors.push_back(kMagenta+2);
 
  scaleFactors.push_back(0.72);
  scaleFactors.push_back(1.0);
  scaleFactors.push_back(1.0);
  scaleFactors.push_back(1.0);
  scaleFactors.push_back(1.0);
  scaleFactors.push_back(1.0);

  double lumi = 0;
  string yearlabel = "";
  if (option == 0) {
    lumi = 35922;
    yearlabel = "2022";
  } 
  if (option == 1) {
    lumi = 41480;    
    yearlabel = "2023";    
  } 
  
  //*********************************************************************
  //TTBAR CR Selection
  //********************************************************************* 
  RunSelectHHTo4B(datafiles, bkgfiles,processLabels, colors, scaleFactors,lumi,yearlabel,20,yearlabel);

  cout << "Year: " << yearlabel << "\n";

}


