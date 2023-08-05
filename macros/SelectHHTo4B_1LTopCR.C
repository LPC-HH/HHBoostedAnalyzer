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
#include <TMath.h>

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

// Taken from here: https://github.com/cms-jet/TopTaggingScaleFactors/tree/master/scaleFactors

double TopTagSF( string workingPoint, string year, double pt ) {
  double result = 1.0;
  if (workingPoint == "0.40") {
    if (year == "2016") {
      if (pt > 600) {
	result = 0.930;
      } else if (pt > 480) { 
	result = 1.013;
      } else if (pt > 400) { 
	result = 1.041;
      } else if (pt > 300) { 
	result = 0.926;
      } else {
	result = 0.926; //this isn't measured, so we take the value of the last bin measured. 
      }      
    } 
    else if (year == "2017") {
      if (pt > 600) {
	result = 0.760;
      } else if (pt > 480) { 
	result = 0.851;
      } else if (pt > 400) { 
	result = 0.856;
      } else if (pt > 300) { 
	result = 0.879;
      } else {
	result = 0.879; //this isn't measured, so we take the value of the last bin measured. 
      }      
    } 
    else if (year == "2018") {
      if (pt > 600) {
	result = 0.787;
      } else if (pt > 480) { 
	result = 0.911;
      } else if (pt > 400) { 
	result = 0.923;
      } else if (pt > 300) { 
	result = 0.888;
      } else {
	result = 0.888; //this isn't measured, so we take the value of the last bin measured. 
      }      
    } 
    else {
      cout << "[TopTagSF] Warning: year=" << year << " is not supported\n";
    }
  } 
  else if (workingPoint == "0.46") {
    if (year == "2016") {
      if (pt > 600) {
	result = 0.993;
      } else if (pt > 480) { 
	result = 0.980;
      } else if (pt > 400) { 
	result = 1.012;
      } else if (pt > 300) { 
	result = 0.922;
      } else {
	result = 0.922; //this isn't measured, so we take the value of the last bin measured. 
      }      
    } 
    else if (year == "2017") {
      if (pt > 600) {
	result = 0.873;
      } else if (pt > 480) { 
	result = 0.887;
      } else if (pt > 400) { 
	result = 0.946;
      } else if (pt > 300) { 
	result = 0.932;
      } else {
	result = 0.932; //this isn't measured, so we take the value of the last bin measured. 
      }      
    } 
    else if (year == "2018") {
      if (pt > 600) {
	result = 0.848;
      } else if (pt > 480) { 
	result = 0.916;
      } else if (pt > 400) { 
	result = 0.967;
      } else if (pt > 300) { 
	result = 0.917;
      } else {
	result = 0.917; //this isn't measured, so we take the value of the last bin measured. 
      }      
    } 
    else {
      cout << "[TopTagSF] Warning: year=" << year << " is not supported\n";
    }
  }
  else {
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
      
      cout << processLabels[i] << " : " << hist[i]->Integral() << "\n";

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
  cv->SaveAs(Form("1LTopCR_%s%s.png",varName.c_str(), label.c_str()));
  cv->SaveAs(Form("1LTopCR_%s%s.pdf",varName.c_str(), label.c_str()));
  
  pad1->SetLogy(true);
  cv->SaveAs(Form("1LTopCR_%s%s_Logy.png",varName.c_str(),label.c_str()));
  cv->SaveAs(Form("1LTopCR_%s%s_Logy.pdf",varName.c_str(),label.c_str()));


 

}



//=== MAIN MACRO ================================================================================================= 


void RunSelect1LTop(  std::vector<std::pair<std::vector<std::string>,std::string > > datafiles, std::vector<std::vector<std::pair<std::vector<std::string>,std::string > > > bkgfiles, std::vector<std::string> bkgLabels, std::vector<int> bkgColors, std::vector<float> bkgScaleFactors, int channelOption = 1, double totalLumi = 0, std::string label = "") {
  
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
  vector<TH1D*> histMET;
  vector<TH1D*> histNLeptons;
  vector<TH1D*> histNJetsHaveLeptons;
  vector<TH1D*> histLep1Pt;
  vector<TH1D*> histLep1Eta;
  vector<TH1D*> histLep1Phi;
  vector<TH1D*> histJet1Mass;
  vector<TH1D*> histJet1Pt;
  vector<TH1D*> histJet1DDB;
  vector<TH1D*> histJet1PNetXbb;
  vector<TH1D*> histJet1PNetXbbSR;
  vector<TH1D*> histJet1PNetXbbSRZoom;
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
    histMET.push_back(new TH1D(Form("histMET_%s",processLabels[i].c_str()), "; MET [GeV] ; Number of Events", 50, 0, 500));
    histNLeptons.push_back(new TH1D(Form("histNLeptons_%s",processLabels[i].c_str()), "; NLeptons ; Number of Events", 10, -0.5, 9.5));
    histNJetsHaveLeptons.push_back(new TH1D(Form("histNJetsHaveLeptons_%s",processLabels[i].c_str()), "; NJetsHaveLeptons ; Number of Events", 3, -0.5, 2.5));
    histLep1Pt.push_back(new TH1D(Form("histLep1Pt_%s",processLabels[i].c_str()), "; Lep1 p_{T} [GeV] ; Number of Events", 50, 0, 500));
    histLep1Eta.push_back(new TH1D(Form("histLep1Eta_%s",processLabels[i].c_str()), "; Lep1 #eta ; Number of Events", 50, -3.0, 3.0));
    histLep1Phi.push_back(new TH1D(Form("histLep1Phi_%s",processLabels[i].c_str()), "; Lep1 #phi ; Number of Events", 50, -3.2, 3.2));
    histJet1Mass.push_back(new TH1D(Form("histJet1Mass_%s",processLabels[i].c_str()), "; Jet1 Mass [GeV] ; Number of Events", 25, 0, 500));
    histJet1Pt.push_back(new TH1D(Form("histJet1Pt_%s",processLabels[i].c_str()), "; Jet1 p_{T} [GeV] ; Number of Events", 50, 0, 2000));
    histJet1DDB.push_back(new TH1D(Form("histJet1DDB_%s",processLabels[i].c_str()), "; Jet1 DDB ; Number of Events", 25, 0, 1.0));
    histJet1PNetXbb.push_back(new TH1D(Form("histJet1PNetXbb_%s",processLabels[i].c_str()), "; Jet1 PNetXbb ; Number of Events", 25, 0, 1.0));

    double histJet1PNetXbbSRBins[8] = {0.05, 0.8, 0.9, 0.945, 0.955, 0.975, 0.985, 1.0};
    histJet1PNetXbbSR.push_back(new TH1D(Form("histJet1PNetXbbSR_%s",processLabels[i].c_str()), "; Jet1 PNetXbb ; Number of Events", 7, histJet1PNetXbbSRBins));

    double histJet1PNetXbbSRZoomBins[6] = {0.9, 0.945, 0.955, 0.975, 0.985, 1.0};
    histJet1PNetXbbSRZoom.push_back(new TH1D(Form("histJet1PNetXbbSRZoom_%s",processLabels[i].c_str()), "; Jet1 PNetXbb ; Number of Events", 5, histJet1PNetXbbSRZoomBins));
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
    histLep1Pt[i]->Sumw2();
    histLep1Eta[i]->Sumw2();
    histLep1Phi[i]->Sumw2();
    histJet1Mass[i]->Sumw2();
    histJet1Pt[i]->Sumw2();
    histJet1DDB[i]->Sumw2();
    histJet1PNetXbb[i]->Sumw2();
    histJet1PNetXbbSR[i]->Sumw2();
    histJet1PNetXbbSRZoom[i]->Sumw2();
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

     //loop over dataset years
    for (uint y=0; y < inputfiles[i].size(); ++y) {

      //inputfiles[i][y] is a pair < vector<string> , string >
      string year = inputfiles[i][y].second;
      double lumi = 0;
      if (year == "2022") {
	lumi = 35182;
      } 
      if (year == "2023") {
	lumi = 26862;
      } 
      if (year == "2024") {
	lumi = 0;
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
	float pileupWeight = 0;
	float MET = 0;
	float fatJet1Pt = 0;
	float fatJet1Eta = 0;
	float fatJet1Phi = 0;
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
	float lep1Pt = -99;
	float lep1Eta = -99;
	float lep1Phi = -99;
	int lep1Id = 0;
	float lep2Pt = -99;
	float lep2Eta = -99;
	float lep2Phi = -99;
	int lep2Id = 0;      
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
	bool HLT_Ele27_WPTight_Gsf = false; 
	bool HLT_Ele28_WPTight_Gsf = false; 
	bool HLT_Ele30_WPTight_Gsf = false; 
	bool HLT_Ele32_WPTight_Gsf = false; 
	bool HLT_Ele35_WPTight_Gsf = false; 
	bool HLT_Ele38_WPTight_Gsf = false; 
	bool HLT_Ele40_WPTight_Gsf = false; 
	bool HLT_IsoMu20 = false; 
	bool HLT_IsoMu24 = false; 
	bool HLT_IsoMu24_eta2p1 = false; 
	bool HLT_IsoMu27 = false; 
	bool HLT_IsoMu30 = false; 
	bool HLT_Mu50 = false; 
	bool HLT_Mu55 = false; 
    

	tree->SetBranchAddress("weight",&weight);                                       
	tree->SetBranchAddress("pileupWeight",&pileupWeight);                                       
	tree->SetBranchAddress("MET",&MET);                                       
	tree->SetBranchAddress("fatJet1Pt",&fatJet1Pt);                                       
	tree->SetBranchAddress("fatJet1Eta",&fatJet1Eta);                                       
	tree->SetBranchAddress("fatJet1Phi",&fatJet1Phi);                                       
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
	tree->SetBranchAddress("lep1Pt", &lep1Pt);
	tree->SetBranchAddress("lep1Eta", &lep1Eta);
	tree->SetBranchAddress("lep1Phi", &lep1Phi);
	tree->SetBranchAddress("lep1Id", &lep1Id);
	tree->SetBranchAddress("lep2Pt", &lep2Pt);
	tree->SetBranchAddress("lep2Eta", &lep2Eta);
	tree->SetBranchAddress("lep2Phi", &lep2Phi);
	tree->SetBranchAddress("lep2Id", &lep2Id);
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
	tree->SetBranchAddress("HLT_Ele27_WPTight_Gsf", &HLT_Ele27_WPTight_Gsf);
	tree->SetBranchAddress("HLT_Ele28_WPTight_Gsf", &HLT_Ele28_WPTight_Gsf);
	tree->SetBranchAddress("HLT_Ele30_WPTight_Gsf", &HLT_Ele30_WPTight_Gsf);
	tree->SetBranchAddress("HLT_Ele32_WPTight_Gsf", &HLT_Ele32_WPTight_Gsf);
	tree->SetBranchAddress("HLT_Ele35_WPTight_Gsf", &HLT_Ele35_WPTight_Gsf);
	tree->SetBranchAddress("HLT_Ele38_WPTight_Gsf", &HLT_Ele38_WPTight_Gsf);
	tree->SetBranchAddress("HLT_Ele40_WPTight_Gsf", &HLT_Ele40_WPTight_Gsf);
	tree->SetBranchAddress("HLT_IsoMu20", &HLT_IsoMu20);
	tree->SetBranchAddress("HLT_IsoMu24", &HLT_IsoMu24);
	tree->SetBranchAddress("HLT_IsoMu24_eta2p1", &HLT_IsoMu24_eta2p1);
	tree->SetBranchAddress("HLT_IsoMu27", &HLT_IsoMu27);
	tree->SetBranchAddress("HLT_IsoMu30", &HLT_IsoMu30);
	tree->SetBranchAddress("HLT_Mu50", &HLT_Mu50);
	tree->SetBranchAddress("HLT_Mu55", &HLT_Mu55);
    

	bool isData = false;
	if ( processLabels[i] == "Data") isData = true;
    
		cout << "process: " << processLabels[i] << " is Data = " << isData << " | file " << (inputfiles[i][y].first)[j] << " | Total Entries: " << tree->GetEntries() << "\n";
		

	for(UInt_t ientry=0; ientry < tree->GetEntries(); ientry++) {       	
	  tree->GetEntry(ientry);
      

	  if (ientry % 100000 == 0) cout << "Event " << ientry << endl;      

	  double puWeight = 1;      
	  double myWeight = 1;
	  if (!isData) {	 
	    //myWeight = lumi * weight * pileupWeight * scaleFactors[i];
	    myWeight = lumi * weight * scaleFactors[i];
	    //cout << "scaleFactors: " << scaleFactors[i] << "\n";
	    //cout << "myWeight: " << myWeight << " " << lumi << " " << weight << " " << scaleFactors[i] << "\n";
	  }

	  //******************************
	  //Trigger Selection
	  //******************************
	  bool passTrigger = false;	  
	  if ( abs(lep1Id) == 11 ) {
	    passTrigger = 
	      //HLT_Ele27_WPTight_Gsf ||
	      //HLT_Ele28_WPTight_Gsf  || 
	      HLT_Ele30_WPTight_Gsf  || 
	      HLT_Ele32_WPTight_Gsf  || 
	      HLT_Ele35_WPTight_Gsf  || 
	      HLT_Ele38_WPTight_Gsf  || 
	      HLT_Ele40_WPTight_Gsf;	    
	  } else {
	    passTrigger = 
	      //HLT_IsoMu20  || 
	      HLT_IsoMu24  || 
	      HLT_IsoMu24_eta2p1  || 
	      HLT_IsoMu27   
	      //HLT_IsoMu30  || 
	      //HLT_Mu50  || 
	      //HLT_Mu55
	      ;
	  }
	  if (!passTrigger) continue;
	
	  //******************************
	  //Selection Cuts 
	  //******************************
	  if ( !(
		  (abs(lep1Id) == 11 && fabs(lep1Eta) < 2.5 )
		  || 
		 (abs(lep1Id) == 13 && fabs(lep1Eta) < 2.4 )
		 )
	       ) continue;
	  if ( !(lep1Pt > 50 )) continue;
	  if ( lep2Pt > 0 ) continue; 
	  if ( !(fatJet1Pt > 250 )) continue;
	  if ( !(fatJet1MassSD > 50)) continue;
	  if ( !(MET > 100 )) continue;

	  double dphi = (fabs(lep1Phi-lep2Phi) > TMath::Pi()) ? fabs(fabs(lep1Phi-lep2Phi) - 2*TMath::Pi()) : fabs(lep1Phi-lep2Phi);
	  if( !(sqrt(pow(lep1Eta-fatJet1Eta,2)+pow(dphi,2)) > 1.0 )) continue;
		 

	  //Top mass window requirement
	  if ( !(fatJet1MassSD > 140)) continue;


	

	  //TTbar Hadronic CR
	  if (!(fatJet1Tau3OverTau2 < 0.46)) continue;	
	  // if (processLabels[i] == "TTJets") {
	  //   double fatJet1TopTagSF = TopTagSF("0.46", year, fatJet1Pt);
	  //   myWeight = myWeight * fatJet1TopTagSF ;
	  // }
 
	  //******************************
	  //Fill histograms
	  //******************************

	  if (isData) {
	    dataYield += 1.0;
	    histMET[i]->Fill(MET);
	    histLep1Pt[i]->Fill(lep1Pt);
	    histLep1Eta[i]->Fill(lep1Eta);
	    histLep1Phi[i]->Fill(lep1Phi);
	    histJet1Mass[i]->Fill(fatJet1MassSD);      
	    histJet1Pt[i]->Fill(fatJet1Pt);
	    histJet1DDB[i]->Fill(fatJet1DDBTagger);
	    histJet1PNetXbb[i]->Fill(fatJet1PNetXbb);
	    histJet1PNetXbbSR[i]->Fill(fatJet1PNetXbb);
	    histJet1PNetXbbSRZoom[i]->Fill(fatJet1PNetXbb);
	    histJet1Tau3OverTau2[i]->Fill(fatJet1Tau3OverTau2);
	  } else {	 
	    MCYield += myWeight;
	    histMET[i]->Fill(MET, myWeight);    
	    histLep1Pt[i]->Fill(lep1Pt, myWeight);
	    histLep1Eta[i]->Fill(lep1Eta, myWeight);
	    histLep1Phi[i]->Fill(lep1Phi, myWeight);
	    histJet1Mass[i]->Fill(fatJet1MassSD, myWeight);      
	    histJet1Pt[i]->Fill(fatJet1Pt, myWeight);
	    histJet1DDB[i]->Fill(fatJet1DDBTagger, myWeight);
	    histJet1PNetXbb[i]->Fill(fatJet1PNetXbb, myWeight);
	    histJet1PNetXbbSR[i]->Fill(fatJet1PNetXbb, myWeight);
	    histJet1PNetXbbSRZoom[i]->Fill(fatJet1PNetXbb, myWeight);
	    histJet1Tau3OverTau2[i]->Fill(fatJet1Tau3OverTau2, myWeight);	
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
  //MR
  //*******************************************************************************************
  PlotDataAndStackedBkg( histMET, processLabels, color, true, "MET", totalLumi, Label);
  PlotDataAndStackedBkg( histLep1Pt, processLabels, color, true, "Lep1Pt", totalLumi, Label);
  PlotDataAndStackedBkg( histLep1Eta, processLabels, color, true, "Lep1Eta", totalLumi, Label);
  PlotDataAndStackedBkg( histLep1Phi, processLabels, color, true, "Lep1Phi", totalLumi, Label);
  PlotDataAndStackedBkg( histJet1Mass, processLabels, color, true, "Jet1_Mass", totalLumi, Label);
  PlotDataAndStackedBkg( histJet1Pt, processLabels, color, true, "Jet1_Pt", totalLumi, Label);
  PlotDataAndStackedBkg( histJet1DDB, processLabels, color, true, "Jet1_DDB", totalLumi, Label);
  PlotDataAndStackedBkg( histJet1PNetXbb, processLabels, color, true, "Jet1_PNetXbb", totalLumi, Label);
  PlotDataAndStackedBkg( histJet1PNetXbbSR, processLabels, color, true, "Jet1_PNetXbbSR", totalLumi, Label);
  PlotDataAndStackedBkg( histJet1PNetXbbSRZoom, processLabels, color, true, "Jet1_PNetXbbSRZoom", totalLumi, Label);
  PlotDataAndStackedBkg( histJet1Tau3OverTau2, processLabels, color, true, "Jet1_Tau3OverTau2", totalLumi, Label);


  //--------------------------------------------------------------------------------------------------------------
  // Tables
  //==============================================================================================================
  cout << "For Luminosity = " << totalLumi << " pb^-1\n";
 
  cout << "Selected Event Yield \n";
  cout << "Data: " << dataYield << "\n";
  cout << "MC: " << MCYield << "\n";


  // //--------------------------------------------------------------------------------------------------------------
  // // Output
  // //==============================================================================================================
  TFile *file = TFile::Open(("1LTopCRPlots"+Label+".root").c_str(), "UPDATE");
  file->cd();

  for(int i=0; i<int(inputfiles.size()); i++) {
    file->WriteTObject(histJet1Mass[i], Form("histJet1Mass_%s",processLabels[i].c_str()), "WriteDelete");
    file->WriteTObject(histJet1Pt[i], Form("histJet1Pt_%s",processLabels[i].c_str()), "WriteDelete");
    file->WriteTObject(histMET[i], Form("histMET_%s",processLabels[i].c_str()), "WriteDelete");
    file->WriteTObject(histJet1PNetXbb[i], Form("histJet1PNetXbb_%s",processLabels[i].c_str()), "WriteDelete");
    file->WriteTObject(histJet1PNetXbbSR[i], Form("histJet1PNetXbbSR_%s",processLabels[i].c_str()), "WriteDelete");
    file->WriteTObject(histJet1PNetXbbSRZoom[i], Form("histJet1PNetXbbSRZoom_%s",processLabels[i].c_str()), "WriteDelete");
  } 
  
  file->Close();
  delete file;       

}







void SelectHHTo4B_1LTopCR( int option = -1) {

  std::vector<std::pair<std::vector<std::string>,std::string > > datafiles;
  std::vector<std::vector<std::pair<std::vector<std::string>,std::string > > > bkgfiles;
  std::vector<std::string> processLabels;
  std::vector<int> colors;
  std::vector<float> scaleFactors;

  std::vector<std::string> datafiles_2022;
  std::vector<std::string> datafiles_2023;
  std::vector<std::string> datafiles_2024;

  std::vector<std::string> bkgfiles_ttbar1L_2022;
  std::vector<std::string> bkgfiles_ttbar2L_2022;
  std::vector<std::string> bkgfiles_WJets_2022;
  std::vector<std::string> bkgfiles_QCD_2022;

  std::vector<std::string> bkgfiles_ttbar1L_2023;
  std::vector<std::string> bkgfiles_ttbar2L_2023;
  std::vector<std::string> bkgfiles_WJets_2023;
  std::vector<std::string> bkgfiles_QCD_2023;

  std::vector<std::string> bkgfiles_ttbar1L_2024;
  std::vector<std::string> bkgfiles_ttbar2L_2024;
  std::vector<std::string> bkgfiles_WJets_2024;
  std::vector<std::string> bkgfiles_QCD_2024;

  //***********************************
  //2016 Data and MC
  //***********************************

  std::string dir = "/eos/cms/store/group/phys_susy/razor/Run3Analysis/HH/HHTo4BNtupler/option21/nano/run3/combined/1LSkim/";
  datafiles_2022.push_back(dir+"2022/SingleMuon_2022A_1LSkim.root");
  datafiles_2022.push_back(dir+"2022/SingleMuon_2022B_1LSkim.root");
  datafiles_2022.push_back(dir+"2022/SingleMuon_2022C_1LSkim.root");
  datafiles_2022.push_back(dir+"2022/Muon_2022C_1LSkim.root");
  datafiles_2022.push_back(dir+"2022/Muon_2022D_1LSkim.root");
  datafiles_2022.push_back(dir+"2022/Muon_2022E_1LSkim.root");
  datafiles_2022.push_back(dir+"2022/Muon_2022F_1LSkim.root");
  datafiles_2022.push_back(dir+"2022/Muon_2022G_1LSkim.root");
  datafiles_2022.push_back(dir+"2022/EGamma_2022A_1LSkim.root");
  datafiles_2022.push_back(dir+"2022/EGamma_2022B_1LSkim.root");
  datafiles_2022.push_back(dir+"2022/EGamma_2022C_1LSkim.root");
  datafiles_2022.push_back(dir+"2022/EGamma_2022D_1LSkim.root");
  datafiles_2022.push_back(dir+"2022/EGamma_2022E_1LSkim.root");
  datafiles_2022.push_back(dir+"2022/EGamma_2022F_1LSkim.root");
  datafiles_2022.push_back(dir+"2022/EGamma_2022G_1LSkim.root");
  bkgfiles_ttbar1L_2022.push_back(dir+"2022/TTtoLNu2Q_PostEE_1pb_weighted_1LSkim.root");  
  bkgfiles_ttbar2L_2022.push_back(dir+"2022/");
  bkgfiles_WJets_2022.push_back(dir+"2022/WtoLNu-2Jets_1pb_weighted_1LSkim.root");
  bkgfiles_QCD_2022.push_back(dir+"2022/QCDPt170to300_postEE_1pb_weighted_1LSkim.root");
  bkgfiles_QCD_2022.push_back(dir+"2022/QCDPt300to470_postEE_1pb_weighted_1LSkim.root");
  bkgfiles_QCD_2022.push_back(dir+"2022/QCDPt470to600_postEE_1pb_weighted_1LSkim.root");
  bkgfiles_QCD_2022.push_back(dir+"2022/QCDPt600to800_postEE_1pb_weighted_1LSkim.root");
  bkgfiles_QCD_2022.push_back(dir+"2022/QCDPt800to1000_postEE_1pb_weighted_1LSkim.root");
  bkgfiles_QCD_2022.push_back(dir+"2022/QCDPt1000to1400_postEE_1pb_weighted_1LSkim.root");
  bkgfiles_QCD_2022.push_back(dir+"2022/QCDPt1400to1800_postEE_1pb_weighted_1LSkim.root");
  bkgfiles_QCD_2022.push_back(dir+"2022/QCDPt1800to2400_postEE_1pb_weighted_1LSkim.root");
  bkgfiles_QCD_2022.push_back(dir+"2022/QCDPt2400to3200_postEE_1pb_weighted_1LSkim.root");
  bkgfiles_QCD_2022.push_back(dir+"2022/QCDPt3200toInf_postEE_1pb_weighted_1LSkim.root");

 


  //another vector to contain the different dataset years
  std::vector<std::pair<std::vector<std::string>,std::string > > bkgfiles_ttbar1L;
  std::vector<std::pair<std::vector<std::string>,std::string > > bkgfiles_ttbar2L;
  std::vector<std::pair<std::vector<std::string>,std::string > > bkgfiles_WJets;
  std::vector<std::pair<std::vector<std::string>,std::string > > bkgfiles_QCD;
  
  if (option == -1) {
    datafiles.push_back(std::pair<std::vector<std::string> , std::string> ( datafiles_2022, "2022"));
    datafiles.push_back(std::pair<std::vector<std::string> , std::string> ( datafiles_2023, "2023"));
    datafiles.push_back(std::pair<std::vector<std::string> , std::string> ( datafiles_2024, "2024"));

    bkgfiles_ttbar1L.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_ttbar1L_2022 , "2022"));
    bkgfiles_ttbar2L.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_ttbar2L_2022 , "2022"));
    bkgfiles_WJets.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_WJets_2022 , "2022"));
    bkgfiles_QCD.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_QCD_2022 , "2022"));

    bkgfiles_ttbar1L.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_ttbar1L_2023 , "2023"));
    bkgfiles_ttbar2L.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_ttbar2L_2023 , "2023"));
    bkgfiles_WJets.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_WJets_2023 , "2023"));
    bkgfiles_QCD.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_QCD_2023 , "2023"));

    bkgfiles_ttbar1L.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_ttbar1L_2024 , "2024"));
    bkgfiles_ttbar2L.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_ttbar2L_2024 , "2024"));
    bkgfiles_WJets.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_WJets_2024 , "2024"));
    bkgfiles_QCD.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_QCD_2024 , "2024"));
  }
  if (option == 0) {
    datafiles.push_back(std::pair<std::vector<std::string> , std::string> ( datafiles_2022, "2022"));
    bkgfiles_ttbar1L.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_ttbar1L_2022 , "2022"));
    bkgfiles_ttbar2L.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_ttbar2L_2022 , "2022"));
    bkgfiles_WJets.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_WJets_2022 , "2022"));
    bkgfiles_QCD.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_QCD_2022 , "2022"));

  }
  if (option == 1) {
    datafiles.push_back(std::pair<std::vector<std::string> , std::string> ( datafiles_2023, "2023"));
    bkgfiles_ttbar1L.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_ttbar1L_2023 , "2023"));
    bkgfiles_ttbar2L.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_ttbar2L_2023 , "2023"));
    bkgfiles_WJets.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_WJets_2023 , "2023"));
    bkgfiles_QCD.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_QCD_2023 , "2023"));

  }
  if (option == 2) {
    datafiles.push_back(std::pair<std::vector<std::string> , std::string> ( datafiles_2024, "2024"));
    bkgfiles_ttbar1L.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_ttbar1L_2024 , "2024"));
    bkgfiles_ttbar2L.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_ttbar2L_2024 , "2024"));
    bkgfiles_WJets.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_WJets_2024 , "2024"));
    bkgfiles_QCD.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_QCD_2024 , "2024"));

  }

  bkgfiles.push_back(bkgfiles_ttbar1L);
  // bkgfiles.push_back(bkgfiles_ttbar2L);
  bkgfiles.push_back(bkgfiles_WJets);
  bkgfiles.push_back(bkgfiles_QCD);

  processLabels.push_back("TTJets 1L");  
  // processLabels.push_back("TTJets 2L");  
  processLabels.push_back("WJets");
  processLabels.push_back("QCD");
  
  colors.push_back(kAzure+10);
  // colors.push_back(kBlue-2);
  colors.push_back(kGreen+2);
  colors.push_back(kRed);
 
  scaleFactors.push_back(0.96);
  // scaleFactors.push_back(1.0);
  scaleFactors.push_back(1.0);
  scaleFactors.push_back(2.3); //QCD for 2017/2018
  //scaleFactors.push_back(0.9); //QCD for 2016
 
  

  string label = "";
  double totalLumi = 0;
  if (option == -1) { label = "Run3"; totalLumi = 62044; }
  if (option == 0)  { label = "2022"; totalLumi = 35182; }
  if (option == 1)  { label = "2023"; totalLumi = 26862; }
  if (option == 2)  { label = "2024"; totalLumi = 0;  }

 
  //*********************************************************************
  //TTBAR 1L CR Selection
  //********************************************************************* 
  RunSelect1LTop(datafiles, bkgfiles,processLabels, colors, scaleFactors,1, totalLumi,label);

}


//**********************************
//E-Mu Yields :
//**********************************

//MuEG Triggers ( 30 - 20 )
// Data: 148
// MC: 156.16
 
