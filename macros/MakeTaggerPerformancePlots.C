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
#include "TEfficiency.h"
#include <TGraphAsymmErrors.h>     
#include <TMath.h>     

#include "HHBoostedAnalyzer/macros/tdrstyle.C"
#include "HHBoostedAnalyzer/macros/CMS_lumi.C"

#endif

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

//*************************************************************************************************
//
//*************************************************************************************************
TGraphAsymmErrors* MakeSigEffVsBkgEffGraph(TH1F* signalHist, TH1F* bkgHist, string name ) {
  //Make Met Plots
  const UInt_t nPoints = signalHist->GetXaxis()->GetNbins();
  double SigEff[nPoints];
  double BkgEff[nPoints];
  double SigEffErrLow[nPoints];
  double SigEffErrHigh[nPoints];
  double BkgEffErrLow[nPoints];
  double BkgEffErrHigh[nPoints];
  double NSigTotal = 0;
  double NBkgTotal = 0;
  
  for (UInt_t q=0; q < nPoints+2; ++q) {
    NSigTotal += signalHist->GetBinContent(q);
    NBkgTotal += bkgHist->GetBinContent(q);
  }

  for(UInt_t b=0; b < nPoints; ++b) {
    Double_t nsig = 0;
    Double_t nbkg = 0;
    for (UInt_t q=b; q < nPoints+2; ++q) {
      nsig += signalHist->GetBinContent(q);
      nbkg += bkgHist->GetBinContent(q);
    }

    Double_t ratio;
    Double_t n1 = 0;
    Double_t n2 = 0;

    // n1 = TMath::Nint(nsig);
    // n2 = TMath::Nint(NSigTotal);
    n1 = nsig;
    n2 = NSigTotal;   
    ratio = n1/n2;

    SigEff[b] = ratio;
    SigEffErrLow[b] = 0;
    SigEffErrHigh[b] = 0;

    // n1 = TMath::Nint(nbkg);
    // n2 = TMath::Nint(NBkgTotal);
    n1 = nbkg;
    n2 = NBkgTotal;
    ratio = n1/n2;
    BkgEff[b] = ratio;
    BkgEffErrLow[b] = 0;
    BkgEffErrHigh[b] = 0;
  }

  TGraphAsymmErrors *tmpSigEffVsBkgEff = new TGraphAsymmErrors (nPoints, SigEff, BkgEff, SigEffErrLow, SigEffErrHigh, BkgEffErrLow, BkgEffErrHigh );
  tmpSigEffVsBkgEff->SetName(name.c_str());
  tmpSigEffVsBkgEff->SetTitle("");
  tmpSigEffVsBkgEff->GetYaxis()->SetTitle("Bkg Eff");
  tmpSigEffVsBkgEff->GetXaxis()->SetTitle("Signal Eff");
  tmpSigEffVsBkgEff->GetYaxis()->SetTitleOffset(1.1);
  tmpSigEffVsBkgEff->GetXaxis()->SetTitleOffset(1.05);
  tmpSigEffVsBkgEff->SetMarkerSize(0.5);
  tmpSigEffVsBkgEff->SetMarkerStyle(20);

  return tmpSigEffVsBkgEff;
}


//*************************************************************************************************
//
//*************************************************************************************************
TGraphAsymmErrors* MakeCurrentWPSigEffVsBkgEffGraph(Double_t signalEff, Double_t bkgEff, string name ) {
  //Make Met Plots
  double SigEff[1];
  double BkgEff[1];
  double SigEffErrLow[1];
  double SigEffErrHigh[1];
  double BkgEffErrLow[1];
  double BkgEffErrHigh[1];
  double NSigTotal = 0;
  double NBkgTotal = 0;
  double cutValue;

  SigEff[0] = signalEff;
  SigEffErrLow[0] = 0;
  SigEffErrHigh[0] = 0;
  BkgEff[0] = bkgEff;
  BkgEffErrLow[0] = 0;
  BkgEffErrHigh[0] = 0;

  TGraphAsymmErrors *tmpSigEffVsBkgEff = new TGraphAsymmErrors (1, SigEff, BkgEff, SigEffErrLow, SigEffErrHigh, BkgEffErrLow, BkgEffErrHigh  );
  tmpSigEffVsBkgEff->SetName(name.c_str());
  tmpSigEffVsBkgEff->SetTitle("");
  tmpSigEffVsBkgEff->GetYaxis()->SetTitle("Bkg Eff");
  tmpSigEffVsBkgEff->GetXaxis()->SetTitle("Signal Eff");
  tmpSigEffVsBkgEff->GetYaxis()->SetTitleOffset(1.1);
  tmpSigEffVsBkgEff->GetXaxis()->SetTitleOffset(1.05);
  tmpSigEffVsBkgEff->SetMarkerColor(kBlack);
  tmpSigEffVsBkgEff->SetLineColor(kBlack);
  tmpSigEffVsBkgEff->SetMarkerSize(1.5);

  return tmpSigEffVsBkgEff;
}



//*************************************************************************************************
//
//*************************************************************************************************
Double_t FindCutValueAtFixedEfficiency(TH1F* signalHist, Double_t targetSignalEff ) {
  //Make Met Plots


  Double_t targetCutValue = -9999;
  Double_t bestCurrentSignalEff = 0;
  const UInt_t nPoints = signalHist->GetXaxis()->GetNbins();
  double NSigTotal = 0;

  for (UInt_t q=0; q < nPoints+2; ++q) {
    NSigTotal += signalHist->GetBinContent(q);
  }


  for(UInt_t b=0; b < nPoints; ++b) {
    Double_t nsig = 0;
    for (UInt_t q=b; q < nPoints+2; ++q) {
      nsig += signalHist->GetBinContent(q);
    }

    Double_t ratio = nsig / NSigTotal;
//     cout << targetSignalEff << " : " << ratio << " , " << signalHist->GetXaxis()->GetBinCenter(b) << endl;

    if (fabs(targetSignalEff - ratio) < fabs(targetSignalEff - bestCurrentSignalEff)) {
      targetCutValue = signalHist->GetXaxis()->GetBinCenter(b);
      bestCurrentSignalEff = ratio;
    }
  }

  return targetCutValue;
}


//*************************************************************************************************
//
//*************************************************************************************************
Double_t FindBkgEffAtFixedSignalEfficiency(TH1F* signalHist, TH1F* bkgHist, Double_t targetSignalEff ) {
  //Make Met Plots


  Double_t targetBkgEff = 0;
  Double_t bestCurrentSignalEff = 0;
  const UInt_t nPoints = signalHist->GetXaxis()->GetNbins();
  double NSigTotal = 0;
  double NBkgTotal = 0;

  for (UInt_t q=0; q < nPoints+2; ++q) {
    NSigTotal += signalHist->GetBinContent(q);
    NBkgTotal += bkgHist->GetBinContent(q);
  }


  for(UInt_t b=0; b < nPoints; ++b) {
    Double_t nsig = 0;
    for (UInt_t q=b; q < nPoints+2; ++q) {
      nsig += signalHist->GetBinContent(q);
    }

    Double_t nbkg = 0;
    for (UInt_t q=b; q < nPoints+2; ++q) {
      nbkg += bkgHist->GetBinContent(q);
    }

    Double_t ratio = nsig / NSigTotal;
    Double_t bkgEff = nbkg / NBkgTotal;
//     cout << targetSignalEff << " : " << ratio << " , " << bkgEff << " : " << signalHist->GetXaxis()->GetBinCenter(b) << endl;

    if (fabs(targetSignalEff - ratio) < fabs(targetSignalEff - bestCurrentSignalEff)) {
      bestCurrentSignalEff = ratio;
      targetBkgEff = bkgEff;
    }
  }

  return targetBkgEff;
}


//*************************************************************************************************
//
//*************************************************************************************************
Double_t FindSigEffAtFixedBkgEfficiency(TH1F* signalHist, TH1F* bkgHist, Double_t targetBkgEff ) {
  //Make Met Plots

  Double_t targetSignalEff = 0;
  Double_t bestCurrentBkgEff = 0;
  const UInt_t nPoints = signalHist->GetXaxis()->GetNbins();
  double NSigTotal = 0;
  double NBkgTotal = 0;

  for (UInt_t q=0; q < nPoints+2; ++q) {
    NSigTotal += signalHist->GetBinContent(q);
    NBkgTotal += bkgHist->GetBinContent(q);
  }


  for(UInt_t b=0; b < nPoints; ++b) {
    Double_t nsig = 0;
    for (UInt_t q=b; q < nPoints+2; ++q) {
      nsig += signalHist->GetBinContent(q);
    }

    Double_t nbkg = 0;
    for (UInt_t q=b; q < nPoints+2; ++q) {
      nbkg += bkgHist->GetBinContent(q);
    }

    Double_t sigEff = nsig / NSigTotal;
    Double_t bkgEff = nbkg / NBkgTotal;
//     cout << targetSignalEff << " : " << ratio << " , " << bkgEff << " : " << signalHist->GetXaxis()->GetBinCenter(b) << endl;

    if (fabs(targetBkgEff - bkgEff) < fabs(targetBkgEff - bestCurrentBkgEff)) {
      bestCurrentBkgEff = bkgEff;
      targetSignalEff = sigEff;
    }
  }

  return targetSignalEff;
}


//=== MAIN MACRO ================================================================================================= 


void RunMakeTaggerPerformancePlots(  std::vector<std::pair<std::vector<std::string>,std::string > > datafiles, std::vector<std::vector<std::pair<std::vector<std::string>,std::string > > > bkgfiles, std::vector<std::string> bkgLabels, std::vector<int> bkgColors, std::vector<float> bkgScaleFactors, int channelOption = 1, double totalLumi = 0, std::string label = "") {
  
  std::string Label = "";
  if (label != "") Label = "_" + label;

 
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
  TH1F *PNetXbbTagger_Signal = new TH1F("PNetXbbTagger_Signal", "; PNetXbbTagger ; Number of Events ",  10000, -2 , 2);
  TH1F *PNetXbbTagger_Bkg = new TH1F("PNetXbbTagger_Bkg", "; PNetXbbTagger ; Number of Events ",  10000, -2 , 2);
 
  Double_t NJets_Signal = 0;
  Double_t NJets_Bkg = 0;
  Double_t NJets_PassXbb0p95_Signal = 0;
  Double_t NJets_PassXbb0p95_Bkg = 0;
  Double_t NJets_PassXbb0p975_Signal = 0;
  Double_t NJets_PassXbb0p975_Bkg = 0;
  Double_t NJets_PassXbb0p985_Signal = 0;
  Double_t NJets_PassXbb0p985_Bkg = 0;


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
      if (year == "2016") {
	lumi = 35922;
      } 
      if (year == "2017") {
	lumi = 41480;
      } 
      if (year == "2018") {
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
	int fatJet1GenMatchIndex = -99;
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
	int fatJet2GenMatchIndex = -99;
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
	tree->SetBranchAddress("fatJet1GenMatchIndex",&fatJet1GenMatchIndex);
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
	tree->SetBranchAddress("fatJet2GenMatchIndex",&fatJet2GenMatchIndex);
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
	tree->SetBranchAddress("disc_qcd_and_ttbar_Run2_enhanced_v5p2", &disc_qcd_and_ttbar_2017_enhanced_v5);
	tree->SetBranchAddress("disc_qcd_and_ttbar_2017_enhanced_v6", &disc_qcd_and_ttbar_2017_enhanced_v6);
	tree->SetBranchAddress("disc_qcd_and_ttbar_2017_enhanced_v7", &disc_qcd_and_ttbar_2017_enhanced_v7);
	tree->SetBranchAddress("disc_qcd_and_ttbar_Run2_enhanced_v8p2", &disc_qcd_and_ttbar_2017_enhanced_v8);
	tree->SetBranchAddress("disc_qcd_and_ttbar_Run2_enhanced_v10p2", &disc_qcd_and_ttbar_2017_enhanced_v10);
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
    
	cout << "process: " << processLabels[i] << " is Data = " << isData << " | file " << (inputfiles[i][y].first)[j] << " | Total Entries: " << tree->GetEntries() << "\n";

	for(UInt_t ientry=0; ientry < tree->GetEntries(); ientry++) {       	
	  tree->GetEntry(ientry);
      

	  if (ientry % 100000 == 0) cout << "Event " << ientry << endl;      

	  double puWeight = 1;      
	  double myWeight = 1;
	  if (!isData) {	 
	    //myWeight = lumi * weight * triggerEffWeight * pileupWeight * scaleFactors[i];
	    //myWeight = lumi * weight * triggerEffWeight * scaleFactors[i];
	    myWeight = fabs(lumi * weight * scaleFactors[i]);
	    //cout << "scaleFactors: " << scaleFactors[i] << "\n";
	  }



	  bool jet1IsSignalJet = bool(fatJet1GenMatchIndex >= 0);
	  bool jet2IsSignalJet = bool(fatJet2GenMatchIndex >= 0);

	  // cout << "jet1: " << fatJet1GenMatchIndex << "\n";
	  // cout << processLabels[i] << "\n";

	  //jet1
	  if (fatJet1Pt > 300  && fatJet1MassSD > 40)  {
	    if (processLabels[i] == "HH" && jet1IsSignalJet) {
	      PNetXbbTagger_Signal->Fill(fatJet1PNetXbb , myWeight);
	      NJets_Signal += myWeight;
	      if (fatJet1PNetXbb > 0.95) NJets_PassXbb0p95_Signal += myWeight;
	      if (fatJet1PNetXbb > 0.975) NJets_PassXbb0p975_Signal += myWeight;
	      if (fatJet1PNetXbb > 0.985) NJets_PassXbb0p985_Signal += myWeight;
	    }
	    if (processLabels[i] == "QCD" && !jet1IsSignalJet) {
	      //cout << "bkg: " << fatJet1PNetXbb << " : " << myWeight << "\n";
	      PNetXbbTagger_Bkg->Fill(fatJet1PNetXbb , myWeight);
	      NJets_Bkg += myWeight;
	      if (fatJet1PNetXbb > 0.95) NJets_PassXbb0p95_Bkg += myWeight;
	      if (fatJet1PNetXbb > 0.975) NJets_PassXbb0p975_Bkg += myWeight;
	      if (fatJet1PNetXbb > 0.985) NJets_PassXbb0p985_Bkg += myWeight;
	    }
	  }

	  //jet2
	  if (fatJet2Pt > 300  && fatJet2MassSD > 40)  {
	    if (processLabels[i] == "HH" && jet2IsSignalJet) {
	      PNetXbbTagger_Signal->Fill(fatJet2PNetXbb , myWeight);
	      NJets_Signal += myWeight;
	      if (fatJet2PNetXbb > 0.95) NJets_PassXbb0p95_Signal += myWeight;
	      if (fatJet2PNetXbb > 0.975) NJets_PassXbb0p975_Signal += myWeight;
	      if (fatJet2PNetXbb > 0.985) NJets_PassXbb0p985_Signal += myWeight;
	    }
	    if (processLabels[i] == "QCD" && !jet2IsSignalJet) {
	      PNetXbbTagger_Bkg->Fill(fatJet2PNetXbb , myWeight);
	      NJets_Bkg += myWeight;
	      if (fatJet2PNetXbb > 0.95) NJets_PassXbb0p95_Bkg += myWeight;
	      if (fatJet2PNetXbb > 0.975) NJets_PassXbb0p975_Bkg += myWeight;
	      if (fatJet2PNetXbb > 0.985) NJets_PassXbb0p985_Bkg += myWeight;
	    }
	  }


	} //loop over events
      } //loop over input files
    } //loop over dataset year
  } //loop over input process type

  //--------------------------------------------------------------------------------------------------------------
  // Make ROC Curves
  //==============================================================================================================
  TGraphAsymmErrors* ROC_PNetXbb = MakeSigEffVsBkgEffGraph(PNetXbbTagger_Signal, PNetXbbTagger_Bkg, "ROC_PNetXbbTagger" );

  vector<TGraphAsymmErrors*> ROCGraphs;
  vector<string> GraphLabels;
  vector<Int_t> colors;
  ROCGraphs.push_back(ROC_PNetXbb);
  GraphLabels.push_back("PNetXbbTagger");
  colors.push_back(kBlue);
  


  //--------------------------------------------------------------------------------------------------------------
  // Working Points
  //==============================================================================================================
  cout << "PNetXbb > 0.95 Signal Efficiency : " << NJets_PassXbb0p95_Signal << " / " << NJets_Signal << " = " << NJets_PassXbb0p95_Signal/NJets_Signal << endl;
  cout << "PNetXbb > 0.95 Bkg Efficiency : " << NJets_PassXbb0p95_Bkg << " / " << NJets_Bkg << " = " << NJets_PassXbb0p95_Bkg/NJets_Bkg << endl;
  TGraphAsymmErrors* ROC_PNetXbb_Pass0p95 = MakeCurrentWPSigEffVsBkgEffGraph(NJets_PassXbb0p95_Signal/NJets_Signal , NJets_PassXbb0p95_Bkg/NJets_Bkg, "ROC_PNetXbb_Pass0p95");

  cout << "PNetXbb > 0.975 Signal Efficiency : " << NJets_PassXbb0p975_Signal << " / " << NJets_Signal << " = " << NJets_PassXbb0p975_Signal/NJets_Signal << endl;
  cout << "PNetXbb > 0.975 Bkg Efficiency : " << NJets_PassXbb0p975_Bkg << " / " << NJets_Bkg << " = " << NJets_PassXbb0p975_Bkg/NJets_Bkg << endl;
  TGraphAsymmErrors* ROC_PNetXbb_Pass0p975 = MakeCurrentWPSigEffVsBkgEffGraph(NJets_PassXbb0p975_Signal/NJets_Signal , NJets_PassXbb0p975_Bkg/NJets_Bkg, "ROC_PNetXbb_Pass0p975");

  cout << "PNetXbb > 0.985 Signal Efficiency : " << NJets_PassXbb0p985_Signal << " / " << NJets_Signal << " = " << NJets_PassXbb0p985_Signal/NJets_Signal << endl;
  cout << "PNetXbb > 0.985 Bkg Efficiency : " << NJets_PassXbb0p985_Bkg << " / " << NJets_Bkg << " = " << NJets_PassXbb0p985_Bkg/NJets_Bkg << endl;
  TGraphAsymmErrors* ROC_PNetXbb_Pass0p985 = MakeCurrentWPSigEffVsBkgEffGraph(NJets_PassXbb0p985_Signal/NJets_Signal , NJets_PassXbb0p985_Bkg/NJets_Bkg, "ROC_PNetXbb_Pass0p985");

  //--------------------------------------------------------------------------------------------------------------
  // Draw
  //==============================================================================================================
  TCanvas *cv =0;
  TLegend *legend = 0;

   Double_t xmin = 0.0;
  Double_t xmax = 1.0;
  Double_t ymin = 0.0;
  Double_t ymax = 1.0;

  cv = new TCanvas("cv", "cv", 800, 600);

  legend = new TLegend(0.15,0.50,0.55,0.85);
  legend->SetTextSize(0.03);
  legend->SetBorderSize(0);
  legend->SetFillStyle(0);
  for (UInt_t i=0; i<GraphLabels.size(); ++i) {
    legend->AddEntry(ROCGraphs[i],GraphLabels[i].c_str(), "LP");

    ROCGraphs[i]->SetMarkerColor(colors[i]);
    ROCGraphs[i]->SetLineColor(colors[i]);
    ROCGraphs[i]->SetMarkerSize(0.5);
   
    ROCGraphs[i]->GetXaxis()->SetRangeUser(xmin,xmax);    
    ROCGraphs[i]->GetYaxis()->SetRangeUser(ymin,ymax);    
    if (i==0) {
      ROCGraphs[i]->Draw("AP");
      ROCGraphs[i]->GetYaxis()->SetTitleSize(0.05);
      ROCGraphs[i]->GetYaxis()->SetTitleOffset(0.9);
      ROCGraphs[i]->GetXaxis()->SetTitleSize(0.05);
      ROCGraphs[i]->GetXaxis()->SetTitleOffset(0.9);

    } else {
      ROCGraphs[i]->Draw("Psame");
    }
  }

  legend->AddEntry(ROC_PNetXbb_Pass0p95, "PNetXbb > 0.95", "P");
  ROC_PNetXbb_Pass0p95->SetFillColor(kRed);
  ROC_PNetXbb_Pass0p95->SetMarkerColor(kRed);
  ROC_PNetXbb_Pass0p95->SetMarkerStyle(34);
  ROC_PNetXbb_Pass0p95->SetMarkerSize(2.5);
  ROC_PNetXbb_Pass0p95->Draw("Psame");

  legend->AddEntry(ROC_PNetXbb_Pass0p975, "PNetXbb > 0.975", "P");
  ROC_PNetXbb_Pass0p975->SetFillColor(kBlack);
  ROC_PNetXbb_Pass0p975->SetMarkerColor(kBlack);
  ROC_PNetXbb_Pass0p975->SetMarkerStyle(34);
  ROC_PNetXbb_Pass0p975->SetMarkerSize(2.5);
  ROC_PNetXbb_Pass0p975->Draw("Psame");

  legend->AddEntry(ROC_PNetXbb_Pass0p985, "PNetXbb > 0.985", "P");
  ROC_PNetXbb_Pass0p985->SetFillColor(kGreen+2);
  ROC_PNetXbb_Pass0p985->SetMarkerColor(kGreen+2);
  ROC_PNetXbb_Pass0p985->SetMarkerStyle(34);
  ROC_PNetXbb_Pass0p985->SetMarkerSize(2.5);
  ROC_PNetXbb_Pass0p985->Draw("Psame");

  legend->Draw();
  cv->SetLogy();
  cv->SaveAs("ROCGraphs_PNetXbb.gif");
  cv->SaveAs("ROCGraphs_PNetXbb.pdf");


  //Plot the Tagger Shape
  PNetXbbTagger_Signal->Rebin(100);
  PNetXbbTagger_Bkg->Rebin(100);
  NormalizeHist(PNetXbbTagger_Signal);
  NormalizeHist(PNetXbbTagger_Bkg);
  legend = new TLegend(0.15,0.50,0.70,0.85);
  legend->SetTextSize(0.03);
  legend->SetBorderSize(0);
  legend->SetFillStyle(0);
  legend->AddEntry(PNetXbbTagger_Signal,"Signal", "LP");
  legend->AddEntry(PNetXbbTagger_Bkg,"QCD Bkg", "LP");
  PNetXbbTagger_Signal->SetLineColor(kBlue);
  PNetXbbTagger_Bkg->SetLineColor(kRed);
  PNetXbbTagger_Signal->SetLineWidth(2);
  PNetXbbTagger_Bkg->SetLineWidth(2);
  PNetXbbTagger_Signal->Draw("hist");
  PNetXbbTagger_Signal->SetStats(0);
  PNetXbbTagger_Signal->GetYaxis()->SetTitleSize(0.05);
  PNetXbbTagger_Signal->GetYaxis()->SetTitleOffset(0.9);
  PNetXbbTagger_Signal->GetYaxis()->SetTitle("Fraction of Events");
  PNetXbbTagger_Signal->GetXaxis()->SetTitleSize(0.05);
  PNetXbbTagger_Signal->GetXaxis()->SetTitleOffset(0.9);
  PNetXbbTagger_Signal->GetXaxis()->SetTitle("Particle-Net Xbb Tagger");
  PNetXbbTagger_Signal->GetXaxis()->SetRangeUser(0.0,1.0);
  PNetXbbTagger_Signal->GetYaxis()->SetRangeUser(0.002,2.0);
  PNetXbbTagger_Bkg->Draw("histsame");
  legend->Draw();
  cv->SaveAs("PNetXbbShape.gif");
  cv->SaveAs("PNetXbbShape.pdf");




  // //--------------------------------------------------------------------------------------------------------------
  // // Output
  // //==============================================================================================================
  TFile *file = TFile::Open("TaggerPerformancePlots.root", "UPDATE");
  file->cd();

  for(int i=0; i<int(inputfiles.size()); i++) {
    file->WriteTObject(PNetXbbTagger_Signal, "PNetXbbTagger_Signal", "WriteDelete");
    file->WriteTObject(PNetXbbTagger_Bkg, "PNetXbbTagger_Bkg", "WriteDelete");
  } 
  
  file->Close();
  delete file;    
  

}







void MakeTaggerPerformancePlots( int option = -1) {

  std::vector<std::pair<std::vector<std::string>,std::string > > datafiles;
  std::vector<std::vector<std::pair<std::vector<std::string>,std::string > > > bkgfiles;
  std::vector<std::string> processLabels;
  std::vector<int> colors;
  std::vector<float> scaleFactors;

  std::vector<std::string> datafiles_2016;
  std::vector<std::string> datafiles_2017;
  std::vector<std::string> datafiles_2018;

  std::vector<std::string> bkgfiles_ttbar_2016;
  std::vector<std::string> bkgfiles_H_2016;
  std::vector<std::string> bkgfiles_VH_2016;
  std::vector<std::string> bkgfiles_ttH_2016;  
  std::vector<std::string> bkgfiles_qcd_2016; 
  std::vector<std::string> bkgfiles_HH_2016; 
  std::vector<std::string> bkgfiles_ttbar_2017;
  std::vector<std::string> bkgfiles_H_2017;
  std::vector<std::string> bkgfiles_VH_2017;
  std::vector<std::string> bkgfiles_ttH_2017;  
  std::vector<std::string> bkgfiles_qcd_2017; 
  std::vector<std::string> bkgfiles_HH_2017; 
  std::vector<std::string> bkgfiles_ttbar_2018;
  std::vector<std::string> bkgfiles_H_2018;
  std::vector<std::string> bkgfiles_VH_2018;
  std::vector<std::string> bkgfiles_ttH_2018;  
  std::vector<std::string> bkgfiles_qcd_2018; 
  std::vector<std::string> bkgfiles_HH_2018; 

  //***********************************
  //2016 Data and MC
  //***********************************


  //***********************************
  //2017 Data and MC
  //***********************************
  bkgfiles_ttbar_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/HHTo4BNtupler/20200801/v10/combined/TTToHadronic_TuneCP5_13TeV-powheg-pythia8_skim_1pb_weighted.root");  

  bkgfiles_qcd_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/HHTo4BNtupler/20200801/v10/combined/QCD_HT300to500_TuneCP5_13TeV-madgraph-pythia8_skim_1pb_weighted.root");
  bkgfiles_qcd_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/HHTo4BNtupler/20200801/v10/combined/QCD_HT500to700_TuneCP5_13TeV-madgraph-pythia8_skim_1pb_weighted.root");
  bkgfiles_qcd_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/HHTo4BNtupler/20200801/v10/combined/QCD_HT700to1000_TuneCP5_13TeV-madgraph-pythia8_skim_1pb_weighted.root");
  bkgfiles_qcd_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/HHTo4BNtupler/20200801/v10/combined/QCD_HT1000to1500_TuneCP5_13TeV-madgraph-pythia8_skim_1pb_weighted.root");
  bkgfiles_qcd_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/HHTo4BNtupler/20200801/v10/combined/QCD_HT1500to2000_TuneCP5_13TeV-madgraph-pythia8_skim_1pb_weighted.root");
  bkgfiles_qcd_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/HHTo4BNtupler/20200801/v10/combined/QCD_HT2000toInf_TuneCP5_13TeV-madgraph-pythia8_skim_1pb_weighted.root");

  bkgfiles_HH_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/HHTo4BNtupler/20200801/v10/combined/GluGluToHHTo4B_node_cHHH1_TuneCUETP8M1_PSWeights_13TeV-powheg-pythia8.root");   
 
  //***********************************
  //2018 Data and MC
  //***********************************
 

  //another vector to contain the different dataset years
  std::vector<std::pair<std::vector<std::string>,std::string > > bkgfiles_ttbar;
  std::vector<std::pair<std::vector<std::string>,std::string > > bkgfiles_H;
  std::vector<std::pair<std::vector<std::string>,std::string > > bkgfiles_VH;
  std::vector<std::pair<std::vector<std::string>,std::string > > bkgfiles_ttH;  
  std::vector<std::pair<std::vector<std::string>,std::string > > bkgfiles_qcd; 
  std::vector<std::pair<std::vector<std::string>,std::string > > bkgfiles_HH; 

  if (option == -1) {
    datafiles.push_back(std::pair<std::vector<std::string> , std::string> ( datafiles_2016, "2016"));
    datafiles.push_back(std::pair<std::vector<std::string> , std::string> ( datafiles_2017, "2017"));
    datafiles.push_back(std::pair<std::vector<std::string> , std::string> ( datafiles_2018, "2018"));

    bkgfiles_qcd.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_qcd_2016 , "2016"));
    bkgfiles_ttbar.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_ttbar_2016 , "2016"));
    bkgfiles_VH.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_VH_2016 , "2016"));
    bkgfiles_H.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_H_2016 , "2016"));
    bkgfiles_ttH.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_ttH_2016 , "2016"));
    bkgfiles_HH.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_HH_2016 , "2016"));

    bkgfiles_qcd.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_qcd_2017 , "2017"));
    bkgfiles_ttbar.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_ttbar_2017 , "2017"));
    bkgfiles_VH.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_VH_2017 , "2017"));
    bkgfiles_H.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_H_2017 , "2017"));
    bkgfiles_ttH.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_ttH_2017 , "2017"));
    bkgfiles_HH.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_HH_2017 , "2017"));

    bkgfiles_qcd.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_qcd_2018 , "2018"));
    bkgfiles_ttbar.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_ttbar_2018 , "2018"));
    bkgfiles_VH.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_VH_2018 , "2018"));
    bkgfiles_H.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_H_2018 , "2018"));
    bkgfiles_ttH.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_ttH_2018 , "2018"));
    bkgfiles_HH.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_HH_2018 , "2018"));
  }
  if (option == 0) {
    datafiles.push_back(std::pair<std::vector<std::string> , std::string> ( datafiles_2016, "2016"));
    bkgfiles_qcd.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_qcd_2016 , "2016"));
    bkgfiles_ttbar.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_ttbar_2016 , "2016"));
    bkgfiles_VH.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_VH_2016 , "2016"));
    bkgfiles_H.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_H_2016 , "2016"));
    bkgfiles_ttH.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_ttH_2016 , "2016"));
    bkgfiles_HH.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_HH_2016 , "2016"));
  }
  if (option == 1) {
    datafiles.push_back(std::pair<std::vector<std::string> , std::string> ( datafiles_2017, "2017"));
    bkgfiles_qcd.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_qcd_2017 , "2017"));
    bkgfiles_ttbar.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_ttbar_2017 , "2017"));
    bkgfiles_VH.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_VH_2017 , "2017"));
    bkgfiles_H.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_H_2017 , "2017"));
    bkgfiles_ttH.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_ttH_2017 , "2017"));
    bkgfiles_HH.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_HH_2017 , "2017"));
  }
  if (option == 2) {
    datafiles.push_back(std::pair<std::vector<std::string> , std::string> ( datafiles_2018, "2018"));
    bkgfiles_qcd.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_qcd_2018 , "2018"));
    bkgfiles_ttbar.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_ttbar_2018 , "2018"));
    bkgfiles_VH.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_VH_2018 , "2018"));
    bkgfiles_H.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_H_2018 , "2018"));
    bkgfiles_ttH.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_ttH_2018 , "2018"));
    bkgfiles_HH.push_back(std::pair<std::vector<std::string> , std::string>( bkgfiles_HH_2018 , "2018"));
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
 
  scaleFactors.push_back(1.0);
  scaleFactors.push_back(1.0);
  scaleFactors.push_back(1.0);
  scaleFactors.push_back(1.0);
  scaleFactors.push_back(1.0);
  scaleFactors.push_back(1.0);

  string label = "";
  double totalLumi = 0;
  if (option == -1) { label = "Run2"; totalLumi = 136143; }
  if (option == 0)  { label = "2016"; totalLumi = 35922;  }
  if (option == 1)  { label = "2017"; totalLumi = 41480;  }
  if (option == 2)  { label = "2018"; totalLumi = 59741;  }

  //*********************************************************************
  //SR Selection
  //********************************************************************* 
  RunMakeTaggerPerformancePlots(datafiles, bkgfiles,processLabels, colors, scaleFactors, 1, totalLumi, label);

}

