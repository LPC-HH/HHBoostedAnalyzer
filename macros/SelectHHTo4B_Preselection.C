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

  TH1D *histSignal = 0;

  cout << "hist[] size : " << hist.size() << "\n";

  if (hasData) {
    cout << "hasData\n";
    for (int i = hist.size()-1; i >= 1; --i) {
      hist[i]->SetFillColor(color[i]);
      hist[i]->SetFillStyle(1001);
      hist[i]->SetLineColor(color[i]);
      
      cout << processLabels[i] << " : " << hist[i]->Integral() << "\n";

      if ( hist[i]->Integral() > 0) {

	if (processLabels[i] == "HH") {
	  histSignal = hist[i];
	}

	if ((processLabels[i] == "HH") || (processLabels[i] == "HHkl0") || processLabels[i] == "HHkl2p45" || processLabels[i] == "HHkl6") continue;
	cout << "Add : " << i << processLabels[i] << "\n";
  	stack->Add(hist[i]);
        
      }
    }
  } else {
    cout << "noData\n";
    for (int i = hist.size()-1; i >= 0; --i) {
      hist[i]->SetFillColor(color[i]);
      hist[i]->SetFillStyle(1001);
      
      if ( hist[i]->Integral() > 0) {
	if (processLabels[i] == "HH") {
	  histSignal = hist[i];
	}
	
	if ((processLabels[i] == "HH") || (processLabels[i] == "HHkl0") || processLabels[i] == "HHkl2p45" || processLabels[i] == "HHkl6") continue;
  	stack->Add(hist[i]);
      }
    }
  }

  for (uint i = 0 ; i < hist.size(); ++i) {
    if (hasData && i==0) {
      legend->AddEntry(hist[i],(processLabels[i]).c_str(), "LP");
    } 
    if ((processLabels[i] == "HH") || (processLabels[i] == "HHkl0") || processLabels[i] == "HHkl2p45" || processLabels[i] == "HHkl6") {
      legend->AddEntry(hist[i],"HH x100000", "L");
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

    if (histSignal) {
      histSignal->SetLineWidth(3);
      histSignal->SetFillStyle(0);
      histSignal->Draw("histsame");
    }

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
	if ((processLabels[i] == "HH") || (processLabels[i] == "HHkl0") || processLabels[i] == "HHkl2p45" || processLabels[i] == "HHkl6") continue;
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
  cv->SaveAs(Form("HHTo4B_Preselection_%s%s.png",varName.c_str(), label.c_str()));
  cv->SaveAs(Form("HHTo4B_Preselection_%s%s.pdf",varName.c_str(), label.c_str()));
  
  pad1->SetLogy(true);
  cv->SaveAs(Form("HHTo4B_Preselection_%s%s_Logy.png",varName.c_str(),label.c_str()));
  cv->SaveAs(Form("HHTo4B_Preselection_%s%s_Logy.pdf",varName.c_str(),label.c_str()));


 

}



//=== MAIN MACRO ================================================================================================= 


void RunSelectHHTo4B(  std::vector<std::pair<std::vector<std::string>,std::string > > datafiles, std::vector<std::vector<std::pair<std::vector<std::string>,std::string > > > bkgfiles, std::vector<std::string> bkgLabels, std::vector<int> bkgColors, std::vector<float> bkgScaleFactors, int channelOption = 1, double totalLumi = 0, std::string label = "") {
  
  std::string Label = "";
  if (label != "") Label = "_" + label;

  //--------------------------------------------------------------------------------------------------------------
  // Settings 
  //============================================================================================================== 
  // TFile *triggerEff2016File = new TFile("/afs/cern.ch/work/s/sixie/public/releases/run2/analysis/CMSSW_10_6_8/src/HHBoostedAnalyzer/data/JetHTTriggerEfficiency_2016.root","READ");
  // TFile *triggerEff2017File = new TFile("/afs/cern.ch/work/s/sixie/public/releases/run2/analysis/CMSSW_10_6_8/src/HHBoostedAnalyzer/data/JetHTTriggerEfficiency_2017.root","READ");
  // TFile *triggerEff2018File = new TFile("/afs/cern.ch/work/s/sixie/public/releases/run2/analysis/CMSSW_10_6_8/src/HHBoostedAnalyzer/data/JetHTTriggerEfficiency_2018.root","READ");
  // TH2F *triggerEff2016Hist = (TH2F*)triggerEff2016File->Get("efficiency_ptmass");
  // TH2F *triggerEff2017Hist = (TH2F*)triggerEff2017File->Get("efficiency_ptmass");
  // TH2F *triggerEff2018Hist = (TH2F*)triggerEff2018File->Get("efficiency_ptmass");

  //*****************************************************************************************
  //Set up for input files 
  //*****************************************************************************************
  std::vector<std::vector<std::pair<std::vector<std::string>,std::string > > > inputfiles;
  std::vector<std::string> processLabels;
  std::vector<int> color;
  std::vector<float> scaleFactors;

  //*****************************************************************************************
  //Add data files
  //*****************************************************************************************
  inputfiles.push_back(datafiles);
  processLabels.push_back("Data");
  color.push_back(kBlack);
  scaleFactors.push_back(1.0);


  //*****************************************************************************************
  //Add bkg files
  //*****************************************************************************************
  //check all vector sizes are correct
  if (!(
	bkgfiles.size() == bkgLabels.size()
	&& bkgfiles.size() == bkgColors.size()
	&& bkgfiles.size() == bkgScaleFactors.size()
	)) {
    cout << "Error: Vector size mismatch. bkgfiles.size() = " << bkgfiles.size() << " , bkgLabels.size() = " << bkgLabels.size() << " , "
	 << "bkgColors.size() = " << bkgColors.size() << " , "
	 << "bkgScaleFactors.size() = " << bkgScaleFactors.size() << " , "
	 << "\n";
    return;
  }
  for (int i=0; i < int(bkgfiles.size()); ++i) {
    inputfiles.push_back(bkgfiles[i]);
    processLabels.push_back(bkgLabels[i]);
    color.push_back(bkgColors[i]);
    scaleFactors.push_back(bkgScaleFactors[i]);
  }
  
  for (int i=0; i < int(inputfiles.size()); ++i) {
    cout << processLabels[i] << " : " << scaleFactors[i] << "\n";
  }
 
  //*****************************************************************************************
  //Make some histograms
  //*****************************************************************************************
  std::vector<TH1D*> histMET;
  std::vector<TH1D*> histNLeptons;
  std::vector<TH1D*> histNJetsHaveLeptons;
  std::vector<TH1D*> histJet1Mass;
  std::vector<TH1D*> histJet1Pt;
  std::vector<TH1D*> histJet1DDB;
  std::vector<TH1D*> histJet1PNetXbb;
  std::vector<TH1D*> histJet1Tau3OverTau2;
  std::vector<TH1D*> histJet2Mass;
  std::vector<TH1D*> histJet2Pt;
  std::vector<TH1D*> histJet2DDB;
  std::vector<TH1D*> histJet2PNetXbb;
  std::vector<TH1D*> histJet2Tau3OverTau2;
  std::vector<TH1D*> histHHPt;
  std::vector<TH1D*> histHHMass;

  assert (inputfiles.size() == processLabels.size());
  for (uint i=0; i < inputfiles.size(); ++i) {
    histMET.push_back(new TH1D(Form("histMET_%s",processLabels[i].c_str()), "; MET [GeV] ; Number of Events", 25, 0, 200));
    histNLeptons.push_back(new TH1D(Form("histNLeptons_%s",processLabels[i].c_str()), "; NLeptons ; Number of Events", 10, -0.5, 9.5));
    histNJetsHaveLeptons.push_back(new TH1D(Form("histNJetsHaveLeptons_%s",processLabels[i].c_str()), "; NJetsHaveLeptons ; Number of Events", 3, -0.5, 2.5));
    histJet1Mass.push_back(new TH1D(Form("histJet1Mass_%s",processLabels[i].c_str()), "; Jet1 Soft-drop Mass [GeV] ; Number of Events", 25, 0, 500));
    histJet1Pt.push_back(new TH1D(Form("histJet1Pt_%s",processLabels[i].c_str()), "; Jet1 p_{T} [GeV] ; Number of Events", 25, 0, 2000));
    histJet1DDB.push_back(new TH1D(Form("histJet1DDB_%s",processLabels[i].c_str()), "; Jet1 DDB ; Number of Events", 25, 0, 1.0));
    histJet1PNetXbb.push_back(new TH1D(Form("histJet1PNetXbb_%s",processLabels[i].c_str()), "; Jet1 PNetXbb ; Number of Events", 25, 0, 1.0));
    histJet1Tau3OverTau2.push_back(new TH1D(Form("histJet1Tau3OverTau2_%s",processLabels[i].c_str()), "; Jet1 Tau3OverTau2 ; Number of Events", 25, 0, 1.0));
    histJet2Mass.push_back(new TH1D(Form("histJet2Mass_%s",processLabels[i].c_str()), "; Jet2 Soft-drop Mass [GeV] ; Number of Events", 25, 15, 515));
    histJet2Pt.push_back(new TH1D(Form("histJet2Pt_%s",processLabels[i].c_str()), "; Jet2 p_{T} [GeV] ; Number of Events", 25, 0, 1000));
    histJet2DDB.push_back(new TH1D(Form("histJet1DDB_%s",processLabels[i].c_str()), "; Jet2 DDB ; Number of Events", 25, 0, 1.0));
    histJet2PNetXbb.push_back(new TH1D(Form("histJet2PNetXbb_%s",processLabels[i].c_str()), "; Jet2 PNetXbb ; Number of Events", 25, 0, 1.0));
    histJet2Tau3OverTau2.push_back(new TH1D(Form("histJet1Tau3OverTau2_%s",processLabels[i].c_str()), "; Jet2 Tau3OverTau2 ; Number of Events", 25, 0, 1.0));
    histHHPt.push_back(new TH1D(Form("histHHPt_%s",processLabels[i].c_str()), "; HH p_{T} [GeV] ; Number of Events", 25, 0, 1000));
    histHHMass.push_back(new TH1D(Form("histHHMass_%s",processLabels[i].c_str()), "; m_{HH} [GeV] ; Number of Events", 25, 0, 2000));


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
  double BkgYield = 0;
  double SignalYield_kl1 = 0;
  double SignalYield_kl0 = 0;
  double SignalYield_kl2p45 = 0;
  double SignalYield_kl5 = 0;

  //*******************************************************************************************
  //Loop over all input processes
  //*******************************************************************************************                
  for (uint i=0; i < inputfiles.size(); ++i) {

    //for duplicate event checking
    map<pair<uint,uint>, bool > processedRunEvents;

    //loop over dataset years
    for (uint y=0; y < inputfiles[i].size(); ++y) {

      //inputfiles[i][y] is a pair < vector<string> , string >
      string year = inputfiles[i][y].second;
      double lumi = 0;
      if (year == "2022") {
	lumi = 35182;
      } 
      if (year == "2023") {
	lumi = 41480;
      } 
      if (year == "2024") {
	lumi = 59741;
      }      

      //loop over files for the process and dataset-year
      for (uint j=0; j < (inputfiles[i][y].first).size(); ++j) {

	TFile *file = new TFile((inputfiles[i][y].first)[j].c_str(),"READ");
	TTree *tree = 0;
	if (!file) {
	  cout << "Input file " << (inputfiles[i][y].first)[j] << " could not be opened\n"; 
	  continue;
	} else {
	  tree = (TTree*)file->Get("tree");
	}
	if (!tree) {
	  cout << "Tree could not be found in input file " << (inputfiles[i][y].first)[j] << "\n"; 
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
	float disc_v8p2  = -99;
	float disc_v24  = -99; 
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
	bool HLT_AK8DiPFJet250_250_MassSD30 = false; 
	bool HLT_AK8DiPFJet250_250_MassSD50 = false; 
	bool HLT_AK8DiPFJet260_260_MassSD30 = false; 
	bool HLT_AK8DiPFJet270_270_MassSD30 = false; 
	bool HLT_QuadPFJet70_50_40_30 = false;
	bool HLT_QuadPFJet70_50_40_30_PFBTagParticleNet_2BTagSum0p65 = false;
	bool HLT_QuadPFJet70_50_40_35_PFBTagParticleNet_2BTagSum0p65 = false;
	bool HLT_QuadPFJet70_50_45_35_PFBTagParticleNet_2BTagSum0p65 = false;
	bool HLT_AK8PFJet230_SoftDropMass40 = false;
	bool HLT_AK8PFJet230_SoftDropMass40_PFAK8ParticleNetBB0p35 = false;
	bool HLT_AK8PFJet250_SoftDropMass40_PFAK8ParticleNetBB0p35 = false;
	bool HLT_AK8PFJet275_SoftDropMass40_PFAK8ParticleNetBB0p35 = false;
	bool HLT_AK8PFJet400_SoftDropMass40 = false;
	bool HLT_AK8PFJet425_SoftDropMass40 = false;
	bool HLT_AK8PFJet450_SoftDropMass40 = false;
	bool HLT_AK8PFJet230_SoftDropMass40_PFAK8ParticleNetTauTau0p30 = false;
	bool HLT_AK8PFJet250_SoftDropMass40_PFAK8ParticleNetTauTau0p30 = false;
	bool HLT_AK8PFJet275_SoftDropMass40_PFAK8ParticleNetTauTau0p30 = false;
	bool HLT_IsoMu50_AK8PFJet230_SoftDropMass40 = false;
	bool HLT_IsoMu50_AK8PFJet230_SoftDropMass40_PFAK8ParticleNetBB0p35 = false;
	bool HLT_Ele50_CaloIdVT_GsfTrkIdT_AK8PFJet230_SoftDropMass40 = false;
	bool HLT_Ele50_CaloIdVT_GsfTrkIdT_AK8PFJet230_SoftDropMass40_PFAK8ParticleNetBB0p35 = false;
	
	
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
	tree->SetBranchAddress("disc_qcd_and_ttbar_Run2_enhanced_v8p2", &disc_v8p2);
	tree->SetBranchAddress("disc_qcd_and_ttbar_Run2_enhanced_v24", &disc_v24);
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
	tree->SetBranchAddress("HLT_AK8DiPFJet250_250_MassSD30", &HLT_AK8DiPFJet250_250_MassSD30); 
	tree->SetBranchAddress("HLT_AK8DiPFJet250_250_MassSD50", &HLT_AK8DiPFJet250_250_MassSD50); 
	tree->SetBranchAddress("HLT_AK8DiPFJet260_260_MassSD30", &HLT_AK8DiPFJet260_260_MassSD30); 
	tree->SetBranchAddress("HLT_AK8DiPFJet270_270_MassSD30", &HLT_AK8DiPFJet270_270_MassSD30); 
	tree->SetBranchAddress("HLT_QuadPFJet70_50_40_30", &HLT_QuadPFJet70_50_40_30);
	tree->SetBranchAddress("HLT_QuadPFJet70_50_40_30_PFBTagParticleNet_2BTagSum0p65", &HLT_QuadPFJet70_50_40_30_PFBTagParticleNet_2BTagSum0p65);
	tree->SetBranchAddress("HLT_QuadPFJet70_50_40_35_PFBTagParticleNet_2BTagSum0p65", &HLT_QuadPFJet70_50_40_35_PFBTagParticleNet_2BTagSum0p65);
	tree->SetBranchAddress("HLT_QuadPFJet70_50_45_35_PFBTagParticleNet_2BTagSum0p65", &HLT_QuadPFJet70_50_45_35_PFBTagParticleNet_2BTagSum0p65);
	tree->SetBranchAddress("HLT_AK8PFJet230_SoftDropMass40", &HLT_AK8PFJet230_SoftDropMass40);
	tree->SetBranchAddress("HLT_AK8PFJet230_SoftDropMass40_PFAK8ParticleNetBB0p35", &HLT_AK8PFJet230_SoftDropMass40_PFAK8ParticleNetBB0p35);
	tree->SetBranchAddress("HLT_AK8PFJet250_SoftDropMass40_PFAK8ParticleNetBB0p35", &HLT_AK8PFJet250_SoftDropMass40_PFAK8ParticleNetBB0p35);
	tree->SetBranchAddress("HLT_AK8PFJet275_SoftDropMass40_PFAK8ParticleNetBB0p35", &HLT_AK8PFJet275_SoftDropMass40_PFAK8ParticleNetBB0p35);
	tree->SetBranchAddress("HLT_AK8PFJet400_SoftDropMass40", &HLT_AK8PFJet400_SoftDropMass40);
	tree->SetBranchAddress("HLT_AK8PFJet425_SoftDropMass40", &HLT_AK8PFJet425_SoftDropMass40);
	tree->SetBranchAddress("HLT_AK8PFJet450_SoftDropMass40", &HLT_AK8PFJet450_SoftDropMass40);
	tree->SetBranchAddress("HLT_AK8PFJet230_SoftDropMass40_PFAK8ParticleNetTauTau0p30", &HLT_AK8PFJet230_SoftDropMass40_PFAK8ParticleNetTauTau0p30);
	tree->SetBranchAddress("HLT_AK8PFJet250_SoftDropMass40_PFAK8ParticleNetTauTau0p30", &HLT_AK8PFJet250_SoftDropMass40_PFAK8ParticleNetTauTau0p30);
	tree->SetBranchAddress("HLT_AK8PFJet275_SoftDropMass40_PFAK8ParticleNetTauTau0p30", &HLT_AK8PFJet275_SoftDropMass40_PFAK8ParticleNetTauTau0p30);
	tree->SetBranchAddress("HLT_IsoMu50_AK8PFJet230_SoftDropMass40", &HLT_IsoMu50_AK8PFJet230_SoftDropMass40);
	tree->SetBranchAddress("HLT_IsoMu50_AK8PFJet230_SoftDropMass40_PFAK8ParticleNetBB0p35", &HLT_IsoMu50_AK8PFJet230_SoftDropMass40_PFAK8ParticleNetBB0p35);
	tree->SetBranchAddress("HLT_Ele50_CaloIdVT_GsfTrkIdT_AK8PFJet230_SoftDropMass40", &HLT_Ele50_CaloIdVT_GsfTrkIdT_AK8PFJet230_SoftDropMass40);
	tree->SetBranchAddress("HLT_Ele50_CaloIdVT_GsfTrkIdT_AK8PFJet230_SoftDropMass40_PFAK8ParticleNetBB0p35", &HLT_Ele50_CaloIdVT_GsfTrkIdT_AK8PFJet230_SoftDropMass40_PFAK8ParticleNetBB0p35);


	bool isData = false;
	if ( processLabels[i] == "Data") isData = true;
    
	cout << "process: " << processLabels[i] << " is Data = " << isData << " | file " << (inputfiles[i][y].first)[j] << " | Total Entries: " << tree->GetEntries() << "\n";

	for(UInt_t ientry=0; ientry < tree->GetEntries(); ientry++) {       	
	  tree->GetEntry(ientry);
      

	  if (ientry % 100000 == 0) cout << "Event " << ientry << endl;      

	  double puWeight = 1;      
	  double myWeight = 1;
	  if (!isData) {	 
	    //myWeight = lumi * weight * triggerEffWeight * pileupWeight * scaleFactors[i];
	    //myWeight = lumi * weight * triggerEffWeight * scaleFactors[i];
	    myWeight = lumi * weight * scaleFactors[i];
	    //cout << " weight: " << lumi << " " << weight << " " << scaleFactors[i] << " " << triggerEffWeight << " " << pileupWeight << "\n";
	    //cout << "scaleFactors: " << scaleFactors[i] << "\n";
	  }

	  //******************************
	  //Trigger Selection
	  //******************************
	  bool passTrigger = false;

	  if (year == "2022") {
	    passTrigger = 
	      (0 == 1)
	      || HLT_AK8PFJet250_SoftDropMass40_PFAK8ParticleNetBB0p35
	      //|| HLT_AK8PFJet425_SoftDropMass40
	      ;       

	    // apply trigger efficiency correction for some triggers that were not enabled for full run
	    if (!isData) {
	    passTrigger = 
	      (0 == 1)
	      || HLT_AK8PFJet250_SoftDropMass40_PFAK8ParticleNetBB0p35
	      //|| HLT_AK8PFJet425_SoftDropMass40
	      ;       

	    myWeight = myWeight;
	    //maybe needs a MC to data correction factor
	    // double triggerEff = 1.0 - 
	    //   (1 - getTriggerEff( triggerEff2016Hist , fatJet1Pt, fatJet1MassSD )) * 
	    //   (1 - getTriggerEff( triggerEff2016Hist , fatJet2Pt, fatJet2MassSD ))
	    //   ;
	    // myWeight = myWeight * triggerEff;
	    }

	  }
	  if (year == "2023") {
	    passTrigger = 
	      (0 == 1)
	      || HLT_AK8PFJet250_SoftDropMass40_PFAK8ParticleNetBB0p35
	      //|| HLT_AK8PFJet425_SoftDropMass40
	      ;       

	    // apply trigger efficiency correction for some triggers that were not enabled for full run
	    if (!isData) {
	    passTrigger = 
	      (0 == 1)
	      || HLT_AK8PFJet250_SoftDropMass40_PFAK8ParticleNetBB0p35
	      //|| HLT_AK8PFJet425_SoftDropMass40
	      ;       

	    myWeight = myWeight;
	    //maybe needs a MC to data correction factor
	    // double triggerEff = 1.0 - 
	    //   (1 - getTriggerEff( triggerEff2016Hist , fatJet1Pt, fatJet1MassSD )) * 
	    //   (1 - getTriggerEff( triggerEff2016Hist , fatJet2Pt, fatJet2MassSD ))
	    //   ;
	    // myWeight = myWeight * triggerEff;
	    }	  

	  }


	  if (year == "2024") {
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

	      passTrigger = true;
	      // double triggerEff = 1.0 - 
	      //   (1 - getTriggerEff( triggerEff2018Hist , fatJet1Pt, fatJet1MassSD )) * 
	      //   (1 - getTriggerEff( triggerEff2018Hist , fatJet2Pt, fatJet2MassSD ))
	      //   ;
	      // myWeight = myWeight * triggerEff;
	    }   
	  }


	  // if (isData) {
	  //   cout << "year = " << year << " : " << passTrigger << "\n";
	  // }

	  if (!passTrigger) continue;


	  //if (isData) continue;

	  //******************************
	  //Selection Cuts 
	  //******************************
	  if ( !(fatJet1Pt > 250 )) continue;
	  if ( !(fatJet2Pt > 250 )) continue;
	  if ( !(fatJet1MassSD > 50)) continue;
	  if ( !(fatJet2MassSD > 50)) continue;
	 
	  //cout << "pass: " << fatJet1Pt << " " << fatJet2Pt << " " << fatJet2MassSD << "\n";

	  //blind the data
	  if (isData) {if ( (fatJet2MassSD > 95 && fatJet2MassSD < 135)) continue;}
	  

	  //******************************
	  //Fill histograms
	  //******************************
	  int NJetsHaveLeptons = 0;
	  if (fatJet1HasMuon || fatJet1HasElectron) NJetsHaveLeptons++;
	  if (fatJet2HasMuon || fatJet2HasElectron) NJetsHaveLeptons++;

	  if (isData) {
	    if ( (fatJet2MassSD > 75 && fatJet2MassSD <= 95) || 
		 (fatJet2MassSD >= 135 && fatJet2MassSD < 155)
		 ) {
	      BkgYield += 1.0;
	    }

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
	    //cout << "fill data\n";

	  } else {
	    
	    if (processLabels[i] == "HH") {
	      if ( (fatJet2MassSD > 95 && fatJet2MassSD < 135)) {
		SignalYield_kl1 += myWeight;
		//cout << "fill signal\n";
	      }
	    } else if(processLabels[i] == "HHkl0"){
	      if ( (fatJet2MassSD > 95 && fatJet2MassSD < 135)) {
		SignalYield_kl0 += myWeight;
	      }
	    } else if(processLabels[i] == "HHkl2p45"){
	      if ( (fatJet2MassSD > 95 && fatJet2MassSD < 135)) {
		SignalYield_kl2p45 += myWeight;
	      }
	    } else if(processLabels[i] == "HHkl5"){
	      if ( (fatJet2MassSD > 95 && fatJet2MassSD < 135)) {
		SignalYield_kl5 += myWeight;
	      }
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
    } //loop over dataset year
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
  //Plots
  //*******************************************************************************************
  //PlotDataAndStackedBkg( histMET, processLabels, color, true, "MET", totalLumi, Label);
  //PlotDataAndStackedBkg( histNLeptons, processLabels, color, true, "NLeptons", totalLumi, Label);
  //PlotDataAndStackedBkg( histNJetsHaveLeptons, processLabels, color, true, "NJetsHaveLeptons", totalLumi, Label);
  cout << "hist 1 " << histJet1Mass.size() << "\n";
  PlotDataAndStackedBkg( histJet1Mass, processLabels, color, true, "Jet1_Mass", totalLumi, Label);
  cout << "hist 2\n";
  PlotDataAndStackedBkg( histJet1Pt, processLabels, color, true, "Jet1_Pt", totalLumi, Label);
  cout << "hist 3\n";
  //PlotDataAndStackedBkg( histJet1DDB, processLabels, color, true, "Jet1_DDB", totalLumi, Label);
  PlotDataAndStackedBkg( histJet1PNetXbb, processLabels, color, true, "Jet1_PNetXbb", totalLumi, Label);
  cout << "hist 4\n";
  PlotDataAndStackedBkg( histJet1Tau3OverTau2, processLabels, color, true, "Jet1_Tau3OverTau2", totalLumi, Label);
  cout << "hist 5\n";  PlotDataAndStackedBkg( histJet2Mass, processLabels, color, true, "Jet2_Mass", totalLumi, Label);
  PlotDataAndStackedBkg( histJet2Pt, processLabels, color, true, "Jet2_Pt", totalLumi, Label);
  cout << "hist 6\n";
  //PlotDataAndStackedBkg( histJet2DDB, processLabels, color, true, "Jet2_DDB", totalLumi, Label);
  PlotDataAndStackedBkg( histJet2PNetXbb, processLabels, color, true, "Jet2_PNetXbb", totalLumi, Label);
  cout << "hist 7\n";
  PlotDataAndStackedBkg( histJet2Tau3OverTau2, processLabels, color, true, "Jet2_Tau3OverTau2", totalLumi, Label);
  cout << "hist 8\n";
  PlotDataAndStackedBkg( histHHPt, processLabels, color, true, "HHPt", totalLumi, Label);
  cout << "hist 9\n";
  PlotDataAndStackedBkg( histHHMass, processLabels, color, true, "HHMass", totalLumi, Label);
  cout << "hist 10\n";

  //--------------------------------------------------------------------------------------------------------------
  // Tables
  //==============================================================================================================
  cout << "For Luminosity = " << totalLumi << " pb^-1\n";
 
  cout << "Selected Event Yield \n";
  cout << "Total Sideband Data: " << dataYield << "\n";
  cout << "Bkg Prediction From Sideband: " << BkgYield << "\n";
  cout << "Signal SM: " << SignalYield_kl1 << "\n";
  cout << "Signal kl0: " << SignalYield_kl0 << "\n";
  cout << "Signal kl2p45: " << SignalYield_kl2p45 << "\n";
  cout << "Signal kl5: " << SignalYield_kl5 << "\n";

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







void SelectHHTo4B_Preselection( int option = -1) {

  std::vector<std::pair<std::vector<std::string>,std::string > > datafiles;
  std::vector<std::vector<std::pair<std::vector<std::string>,std::string > > > bkgfiles;
  std::vector<std::string> processLabels;
  std::vector<int> colors;
  std::vector<float> scaleFactors;

  std::vector<std::string> datafiles_2022;
  std::vector<std::string> datafiles_2023;
  std::vector<std::string> datafiles_2024;

  std::vector<std::string> bkgfiles_ttbar_2022;
  std::vector<std::string> bkgfiles_H_2022;
  std::vector<std::string> bkgfiles_VH_2022;
  std::vector<std::string> bkgfiles_ttH_2022;  
  std::vector<std::string> bkgfiles_qcd_2022; 
  std::vector<std::string> bkgfiles_HH_2022; 
  std::vector<std::string> bkgfiles_HHkl0_2022;
  std::vector<std::string> bkgfiles_HHkl2p45_2022;
  std::vector<std::string> bkgfiles_HHkl5_2022;
  std::vector<std::string> bkgfiles_ttbar_2023;
  std::vector<std::string> bkgfiles_H_2023;
  std::vector<std::string> bkgfiles_VH_2023;
  std::vector<std::string> bkgfiles_ttH_2023;  
  std::vector<std::string> bkgfiles_qcd_2023; 
  std::vector<std::string> bkgfiles_HH_2023; 
  std::vector<std::string> bkgfiles_HHkl0_2023;
  std::vector<std::string> bkgfiles_HHkl2p45_2023;
  std::vector<std::string> bkgfiles_HHkl5_2023;
  std::vector<std::string> bkgfiles_ttbar_2024;
  std::vector<std::string> bkgfiles_H_2024;
  std::vector<std::string> bkgfiles_VH_2024;
  std::vector<std::string> bkgfiles_ttH_2024;  
  std::vector<std::string> bkgfiles_qcd_2024; 
  std::vector<std::string> bkgfiles_HH_2024;
  std::vector<std::string> bkgfiles_HHkl0_2024;
  std::vector<std::string> bkgfiles_HHkl2p45_2024;
  std::vector<std::string> bkgfiles_HHkl5_2024;

  //***********************************
  //2022 Data and MC
  //***********************************

  std::string dir = "/eos/cms/store/group/phys_susy/razor/Run3Analysis/HH/HHTo4BNtupler/option5/nano/run3/combined/";
  datafiles_2022.push_back(dir+"2022/JetHT_2022A_GoodLumi.root");
  datafiles_2022.push_back(dir+"2022/JetHT_2022B_GoodLumi.root");
  datafiles_2022.push_back(dir+"2022/JetHT_2022C_GoodLumi.root");
  datafiles_2022.push_back(dir+"2022/JetMET_2022C_GoodLumi.root");
  datafiles_2022.push_back(dir+"2022/JetMET_2022D_GoodLumi.root");
  datafiles_2022.push_back(dir+"2022/JetMET_2022E_GoodLumi.root");
  datafiles_2022.push_back(dir+"2022/JetMET_2022F_GoodLumi.root");
  datafiles_2022.push_back(dir+"2022/JetMET_2022G_GoodLumi.root");

  bkgfiles_ttbar_2022.push_back(dir+"2022/TTto4Q_postEE_1pb_weighted.root");  
  bkgfiles_ttbar_2022.push_back(dir+"2022/TTtoLNu2Q_PostEE_1pb_weighted.root");   
  bkgfiles_H_2022.push_back(dir+"2022/ggHto2B_Pt200ToInf_PostEE_1pb_weighted.root");
  bkgfiles_H_2022.push_back(dir+"2022/VBFHto2B_PostEE_1pb_weighted.root");
  bkgfiles_VH_2022.push_back(dir+"2022/WminusH_Hto2B_Wto2Q_PostEE_1pb_weighted.root");
  bkgfiles_VH_2022.push_back(dir+"2022/WplusH_Hto2B_Wto2Q_PostEE_1pb_weighted.root");
  bkgfiles_VH_2022.push_back(dir+"2022/ZH_Hto2B_Zto2Q_PostEE_1pb_weighted.root");
  bkgfiles_ttH_2022.push_back(dir+"2022/ttH_Hto2B_PostEE_1pb_weighted.root");

  bkgfiles_qcd_2022.push_back(dir+"2022/QCDPt80to120_postEE_1pb_weighted.root");
  bkgfiles_qcd_2022.push_back(dir+"2022/QCDPt120to170_postEE_1pb_weighted.root");
  bkgfiles_qcd_2022.push_back(dir+"2022/QCDPt170to300_postEE_1pb_weighted.root");
  bkgfiles_qcd_2022.push_back(dir+"2022/QCDPt300to470_postEE_1pb_weighted.root");
  bkgfiles_qcd_2022.push_back(dir+"2022/QCDPt470to600_postEE_1pb_weighted.root");
  bkgfiles_qcd_2022.push_back(dir+"2022/QCDPt600to800_postEE_1pb_weighted.root");
  bkgfiles_qcd_2022.push_back(dir+"2022/QCDPt800to1000_postEE_1pb_weighted.root");
  bkgfiles_qcd_2022.push_back(dir+"2022/QCDPt1000to1400_postEE_1pb_weighted.root");
  bkgfiles_qcd_2022.push_back(dir+"2022/QCDPt1400to1800_postEE_1pb_weighted.root");
  bkgfiles_qcd_2022.push_back(dir+"2022/QCDPt1800to2400_postEE_1pb_weighted.root");
  bkgfiles_qcd_2022.push_back(dir+"2022/QCDPt2400to3200_postEE_1pb_weighted.root");
  bkgfiles_qcd_2022.push_back(dir+"2022/QCDPt3200toInf_postEE_1pb_weighted.root");
  


  bkgfiles_HH_2022.push_back(dir+"2022/ggHH_cHHH_1_TSG_1pb_weighted.root");
  //bkgfiles_HHkl0_2022.push_back(dir+"2022/GluGluToHHTo4B_node_cHHH0_TuneCUETP8M1_PSWeights_13TeV-powheg-pythia8_1pb_weighted.root");
  //bkgfiles_HHkl2p45_2022.push_back(dir+"2022/GluGluToHHTo4B_node_cHHH2p45_TuneCUETP8M1_PSWeights_13TeV-powheg-pythia8_1pb_weighted.root");
  //bkgfiles_HHkl5_2022.push_back(dir+"2022/GluGluToHHTo4B_node_cHHH5_TuneCUETP8M1_PSWeights_13TeV-powheg-pythia8_1pb_weighted.root");



  //***********************************
  //2023 Data and MC
  //***********************************
  datafiles_2023.push_back(dir+"2023/JetHT_2023B_GoodLumi.root");
  datafiles_2023.push_back(dir+"2023/JetHT_2023C_GoodLumi.root");
  datafiles_2023.push_back(dir+"2023/JetHT_2023D_GoodLumi.root");
  datafiles_2023.push_back(dir+"2023/JetHT_2023E_GoodLumi.root");
  datafiles_2023.push_back(dir+"2023/JetHT_2023F_GoodLumi.root");


   bkgfiles_ttbar_2023.push_back(dir+"testing/2023/TTToHadronic_TuneCP5_13TeV-powheg-pythia8_1pb_weighted.root");  
   bkgfiles_ttbar_2023.push_back(dir+"testing/2023/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8_1pb_weighted.root");  
  // bkgfiles_ttbar_2023.push_back(dir+"testing/2023/TT_Mtt-1000toInf_TuneCP5_PSweights_13TeV-powheg-pythia8_1pb_weighted.root");  
  // bkgfiles_ttbar_2023.push_back(dir+"testing/2023/TT_Mtt-700to1000_TuneCP5_PSweights_13TeV-powheg-pythia8_1pb_weighted.root");   
  bkgfiles_H_2023.push_back(dir+"2023/GluGluHToBB_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8_1pb_weighted.root");
  bkgfiles_H_2023.push_back(dir+"2023/VBFHToBB_M-125_13TeV_powheg_pythia8_1pb_weighted.root");
  bkgfiles_VH_2023.push_back(dir+"2023/WminusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8_1pb_weighted.root");
  bkgfiles_VH_2023.push_back(dir+"2023/WplusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8_1pb_weighted.root");
  bkgfiles_VH_2023.push_back(dir+"2023/ZH_HToBB_ZToQQ_M125_13TeV_powheg_pythia8_1pb_weighted.root");
  //  bkgfiles_VH_2023.push_back(dir+"2023/ggZH_HToBB_ZToQQ_M125_13TeV_powheg_pythia8_1pb_weighted.root");
  bkgfiles_ttH_2023.push_back(dir+"2023/ttHTobb_M125_TuneCP5_13TeV-powheg-pythia8_1pb_weighted.root");

  bkgfiles_qcd_2023.push_back(dir+"testing/2023/QCD_HT300to500_TuneCP5_13TeV-madgraph-pythia8_1pb_weighted.root");
  bkgfiles_qcd_2023.push_back(dir+"testing/2023/QCD_HT500to700_TuneCP5_13TeV-madgraph-pythia8_1pb_weighted.root");
  bkgfiles_qcd_2023.push_back(dir+"testing/2023/QCD_HT700to1000_TuneCP5_13TeV-madgraph-pythia8_1pb_weighted.root");
  bkgfiles_qcd_2023.push_back(dir+"testing/2023/QCD_HT1000to1500_TuneCP5_13TeV-madgraph-pythia8_1pb_weighted.root");
  bkgfiles_qcd_2023.push_back(dir+"testing/2023/QCD_HT1500to2000_TuneCP5_13TeV-madgraph-pythia8_1pb_weighted.root");
  bkgfiles_qcd_2023.push_back(dir+"testing/2023/QCD_HT2000toInf_TuneCP5_13TeV-madgraph-pythia8_1pb_weighted.root");

  bkgfiles_HH_2023.push_back(dir+"testing/2023/GluGluToHHTo4B_node_cHHH1_TuneCP5_PSWeights_13TeV-powheg-pythia8_1pb_weighted.root");   
  bkgfiles_HHkl0_2023.push_back(dir+"2023/GluGluToHHTo4B_node_cHHH0_TuneCP5_PSWeights_13TeV-powheg-pythia8_1pb_weighted.root");   
  bkgfiles_HHkl2p45_2023.push_back(dir+"2023/GluGluToHHTo4B_node_cHHH2p45_TuneCP5_PSWeights_13TeV-powheg-pythia8_1pb_weighted.root");   
  bkgfiles_HHkl5_2023.push_back(dir+"2023/GluGluToHHTo4B_node_cHHH5_TuneCP5_PSWeights_13TeV-powheg-pythia8_1pb_weighted.root");   

  //***********************************
  //2024 Data and MC
  //***********************************
  datafiles_2024.push_back(dir+"2024/JetHT_2024A_GoodLumi.root");
  datafiles_2024.push_back(dir+"2024/JetHT_2024B_GoodLumi.root");
  datafiles_2024.push_back(dir+"2024/JetHT_2024C_GoodLumi.root");
  datafiles_2024.push_back(dir+"2024/JetHT_2024D_GoodLumi.root");
   bkgfiles_ttbar_2024.push_back(dir+"testing/2024/TTToHadronic_TuneCP5_13TeV-powheg-pythia8-combined_1pb_weighted.root");  
   bkgfiles_ttbar_2024.push_back(dir+"testing/2024/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8-combined_1pb_weighted.root");  
   //bkgfiles_ttbar_2024.push_back(dir+"testing/2024/TT_Mtt-1000toInf_TuneCP5_13TeV-powheg-pythia8_1pb_weighted.root");
   //bkgfiles_ttbar_2024.push_back(dir+"testing/2024/TT_Mtt-700to1000_TuneCP5_13TeV-powheg-pythia8_1pb_weighted.root");
  bkgfiles_H_2024.push_back(dir+"2024/GluGluHToBB_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8_1pb_weighted.root");
  bkgfiles_H_2024.push_back(dir+"2024/VBFHToBB_M-125_13TeV_powheg_pythia8_weightfix_1pb_weighted.root");
  bkgfiles_VH_2024.push_back(dir+"2024/WminusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8_1pb_weighted.root");
  bkgfiles_VH_2024.push_back(dir+"2024/WplusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8_1pb_weighted.root");
  bkgfiles_VH_2024.push_back(dir+"2024/ZH_HToBB_ZToQQ_M125_13TeV_powheg_pythia8_1pb_weighted.root");
  //  bkgfiles_VH_2024.push_back(dir+"2024/ggZH_HToBB_ZToQQ_M125_13TeV_powheg_pythia8_1pb_weighted.root");
  bkgfiles_ttH_2024.push_back(dir+"2024/ttHTobb_M125_TuneCP5_13TeV-powheg-pythia8_1pb_weighted.root");

  bkgfiles_qcd_2024.push_back(dir+"testing/2024/QCD_HT300to500_TuneCP5_13TeV-madgraphMLM-pythia8_1pb_weighted.root");
  bkgfiles_qcd_2024.push_back(dir+"testing/2024/QCD_HT500to700_TuneCP5_13TeV-madgraphMLM-pythia8_1pb_weighted.root");
  bkgfiles_qcd_2024.push_back(dir+"testing/2024/QCD_HT700to1000_TuneCP5_13TeV-madgraphMLM-pythia8_1pb_weighted.root");
  bkgfiles_qcd_2024.push_back(dir+"testing/2024/QCD_HT1000to1500_TuneCP5_13TeV-madgraphMLM-pythia8_1pb_weighted.root");
  bkgfiles_qcd_2024.push_back(dir+"testing/2024/QCD_HT1500to2000_TuneCP5_13TeV-madgraphMLM-pythia8_1pb_weighted.root");
  bkgfiles_qcd_2024.push_back(dir+"testing/2024/QCD_HT2000toInf_TuneCP5_13TeV-madgraphMLM-pythia8_1pb_weighted.root");

  bkgfiles_HH_2024.push_back(dir+"testing/2024/GluGluToHHTo4B_node_cHHH1_TuneCP5_PSWeights_13TeV-powheg-pythia8_1pb_weighted.root");
  bkgfiles_HHkl0_2024.push_back(dir+"2024/GluGluToHHTo4B_node_cHHH0_TuneCP5_PSWeights_13TeV-powheg-pythia8_1pb_weighted.root");
  bkgfiles_HHkl2p45_2024.push_back(dir+"2024/GluGluToHHTo4B_node_cHHH2p45_TuneCP5_PSWeights_13TeV-powheg-pythia8_1pb_weighted.root");
  bkgfiles_HHkl5_2024.push_back(dir+"2024/GluGluToHHTo4B_node_cHHH5_TuneCP5_PSWeights_13TeV-powheg-pythia8_1pb_weighted.root");


  //another vector to contain the different dataset years
  std::vector<std::pair<std::vector<std::string>,std::string > > bkgfiles_ttbar;
  std::vector<std::pair<std::vector<std::string>,std::string > > bkgfiles_H;
  std::vector<std::pair<std::vector<std::string>,std::string > > bkgfiles_VH;
  std::vector<std::pair<std::vector<std::string>,std::string > > bkgfiles_ttH;  
  std::vector<std::pair<std::vector<std::string>,std::string > > bkgfiles_qcd; 
  std::vector<std::pair<std::vector<std::string>,std::string > > bkgfiles_HH;
  std::vector<std::pair<std::vector<std::string>,std::string > > bkgfiles_HHkl0; 
  std::vector<std::pair<std::vector<std::string>,std::string > > bkgfiles_HHkl2p45; 
  std::vector<std::pair<std::vector<std::string>,std::string > > bkgfiles_HHkl5; 
   
  if (option == -1) {
    datafiles.push_back(std::pair<std::vector<std::string> , std::string> ( datafiles_2022, "2022"));
    datafiles.push_back(std::pair<std::vector<std::string> , std::string> ( datafiles_2023, "2023"));
    datafiles.push_back(std::pair<std::vector<std::string> , std::string> ( datafiles_2024, "2024"));

    bkgfiles_qcd.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_qcd_2022 , "2022"));
    bkgfiles_ttbar.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_ttbar_2022 , "2022"));
    bkgfiles_VH.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_VH_2022 , "2022"));
    bkgfiles_H.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_H_2022 , "2022"));
    bkgfiles_ttH.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_ttH_2022 , "2022"));
    bkgfiles_HH.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_HH_2022 , "2022"));
    bkgfiles_HHkl0.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_HHkl0_2022 , "2022"));
    bkgfiles_HHkl2p45.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_HHkl2p45_2022 , "2022"));
    bkgfiles_HHkl5.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_HHkl5_2022 , "2022"));

    bkgfiles_qcd.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_qcd_2023 , "2023"));
    bkgfiles_ttbar.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_ttbar_2023 , "2023"));
    bkgfiles_VH.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_VH_2023 , "2023"));
    bkgfiles_H.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_H_2023 , "2023"));
    bkgfiles_ttH.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_ttH_2023 , "2023"));
    bkgfiles_HH.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_HH_2023 , "2023"));
    bkgfiles_HHkl0.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_HHkl0_2023 , "2023"));
    bkgfiles_HHkl2p45.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_HHkl2p45_2023 , "2023"));
    bkgfiles_HHkl5.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_HHkl5_2023 , "2023"));

    bkgfiles_qcd.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_qcd_2024 , "2024"));
    bkgfiles_ttbar.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_ttbar_2024 , "2024"));
    bkgfiles_VH.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_VH_2024 , "2024"));
    bkgfiles_H.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_H_2024 , "2024"));
    bkgfiles_ttH.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_ttH_2024 , "2024"));
    bkgfiles_HH.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_HH_2024 , "2024"));
    bkgfiles_HHkl0.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_HHkl0_2024 , "2024"));
    bkgfiles_HHkl2p45.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_HHkl2p45_2024 , "2024"));
    bkgfiles_HHkl5.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_HHkl5_2024 , "2024"));
  }
  if (option == 0) {
    datafiles.push_back(std::pair<std::vector<std::string> , std::string> ( datafiles_2022, "2022"));
    bkgfiles_qcd.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_qcd_2022 , "2022"));
    bkgfiles_ttbar.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_ttbar_2022 , "2022"));
    bkgfiles_VH.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_VH_2022 , "2022"));
    bkgfiles_H.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_H_2022 , "2022"));
    bkgfiles_ttH.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_ttH_2022 , "2022"));
    bkgfiles_HH.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_HH_2022 , "2022"));
    bkgfiles_HHkl0.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_HHkl0_2022 , "2022"));
    bkgfiles_HHkl2p45.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_HHkl2p45_2022 , "2022"));
    bkgfiles_HHkl5.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_HHkl5_2022 , "2022"));
  }
  if (option == 1) {
    datafiles.push_back(std::pair<std::vector<std::string> , std::string> ( datafiles_2023, "2023"));
    bkgfiles_qcd.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_qcd_2023 , "2023"));
    bkgfiles_ttbar.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_ttbar_2023 , "2023"));
    bkgfiles_VH.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_VH_2023 , "2023"));
    bkgfiles_H.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_H_2023 , "2023"));
    bkgfiles_ttH.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_ttH_2023 , "2023"));
    bkgfiles_HH.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_HH_2023 , "2023"));
    bkgfiles_HHkl0.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_HHkl0_2023 , "2023"));
    bkgfiles_HHkl2p45.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_HHkl2p45_2023 , "2023"));
    bkgfiles_HHkl5.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_HHkl5_2023 , "2023"));
  }
  if (option == 2) {
    datafiles.push_back(std::pair<std::vector<std::string> , std::string> ( datafiles_2024, "2024"));
    bkgfiles_qcd.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_qcd_2024 , "2024"));
    bkgfiles_ttbar.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_ttbar_2024 , "2024"));
    bkgfiles_VH.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_VH_2024 , "2024"));
    bkgfiles_H.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_H_2024 , "2024"));
    bkgfiles_ttH.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_ttH_2024 , "2024"));
    bkgfiles_HH.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_HH_2024 , "2024"));
    bkgfiles_HHkl0.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_HHkl0_2024 , "2024"));
    bkgfiles_HHkl2p45.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_HHkl2p45_2024 , "2024"));
    bkgfiles_HHkl5.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_HHkl5_2024 , "2024"));
  }

  bkgfiles.push_back(bkgfiles_qcd);
  bkgfiles.push_back(bkgfiles_ttbar);
  bkgfiles.push_back(bkgfiles_H);
  bkgfiles.push_back(bkgfiles_VH);
  bkgfiles.push_back(bkgfiles_ttH);
  bkgfiles.push_back(bkgfiles_HH);
  // bkgfiles.push_back(bkgfiles_HHkl0);
  // bkgfiles.push_back(bkgfiles_HHkl2p45);
  // bkgfiles.push_back(bkgfiles_HHkl5);

  processLabels.push_back("QCD");
  processLabels.push_back("TTJets");  
  processLabels.push_back("H");
  processLabels.push_back("VH");
  processLabels.push_back("ttH");
  processLabels.push_back("HH");
  // processLabels.push_back("HHkl0");
  // processLabels.push_back("HHkl2p45");
  // processLabels.push_back("HHkl5");
  
  colors.push_back(kAzure+2);
  colors.push_back(kYellow);
  colors.push_back(kOrange-3);
  colors.push_back(kGreen-3);
  colors.push_back(920);
  colors.push_back(617);
  // colors.push_back(kMagenta);
  // colors.push_back(kMagenta-3);
  // colors.push_back(kMagenta+3);
 
  scaleFactors.push_back(1.25);
  scaleFactors.push_back(1.0);
  scaleFactors.push_back(1.0);
  scaleFactors.push_back(1.0);
  scaleFactors.push_back(1.0);
  scaleFactors.push_back(1.0);
  // scaleFactors.push_back(1.0);
  // scaleFactors.push_back(1.0);
  // scaleFactors.push_back(1.0);
  

  string label = "";
  double totalLumi = 0;
  if (option == -1) { label = "Run3"; totalLumi = 62044; }
  if (option == 0)  { label = "2022"; totalLumi = 35182;  }
  if (option == 1)  { label = "2023"; totalLumi = 26862;  }
  if (option == 2)  { label = "2024"; totalLumi = 0;  }

  //*********************************************************************
  //SR Selection
  //********************************************************************* 
  RunSelectHHTo4B(datafiles, bkgfiles,processLabels, colors, scaleFactors, 1, totalLumi, label);

}


//**********************************
//E-Mu Yields :
//**********************************

//MuEG Triggers ( 30 - 20 )
// Data: 148
// MC: 156.16
