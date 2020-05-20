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

void PlotDataAndStackedBkg( vector<TH1D*> hist , vector<string> processLabels, vector<int> color,  bool hasData, string varName, string label ) {

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
  lumi_13TeV = "2.1 fb^{-1}";
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
  cv->SaveAs(Form("TTBarDileptonCR_%s%s.png",varName.c_str(), label.c_str()));
  cv->SaveAs(Form("TTBarDileptonCR_%s%s.pdf",varName.c_str(), label.c_str()));
  
  pad1->SetLogy(true);
  cv->SaveAs(Form("TTBarDileptonCR_%s%s_Logy.png",varName.c_str(),label.c_str()));
  cv->SaveAs(Form("TTBarDileptonCR_%s%s_Logy.pdf",varName.c_str(),label.c_str()));


 

}



//=== MAIN MACRO ================================================================================================= 


void RunSelectTTBarDileptonControlSample(  vector<string> datafiles, vector<vector<string> > bkgfiles, vector<string> bkgLabels, vector<int> bkgColors, double lumi, string option, int channelOption = -1, string label = "") {
  
  string Label = "";
  if (label != "") Label = "_" + label;

  //--------------------------------------------------------------------------------------------------------------
  // Settings 
  //============================================================================================================== 
  float MR = 0;
  float Rsq = 0;
  float mll = 0;


  //*****************************************************************************************
  //Make some histograms
  //*****************************************************************************************
  vector<vector<string> > inputfiles;
  vector<string> processLabels;
  vector<int> color;

  inputfiles.push_back(datafiles);
  processLabels.push_back("Data");
  color.push_back(kBlack);
  
  assert(bkgfiles.size() == bkgLabels.size());
  assert(bkgfiles.size() == bkgColors.size());
  for (int i=0; i < int(bkgfiles.size()); ++i) {
    inputfiles.push_back(bkgfiles[i]);
    processLabels.push_back(bkgLabels[i]);
    color.push_back(bkgColors[i]);
  }

  vector<TH1D*> histMET;
  vector<TH1D*> histDileptonMass;
 
  assert (inputfiles.size() == processLabels.size());
  for (uint i=0; i < inputfiles.size(); ++i) {
    histMET.push_back(new TH1D(Form("histMET_%s",processLabels[i].c_str()), "; MET [GeV] ; Number of Events", 25, 0, 500));
    histDileptonMass.push_back(new TH1D(Form("histDileptonMass_%s",processLabels[i].c_str()), "; M_{ll} [GeV/c^{2}]; Number of Events", 40, 0, 500));
    histMET[i]->Sumw2();
    histDileptonMass[i]->Sumw2();  
  }
 
  double dataYield = 0;
  double MCYield = 0;


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
      bool HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ = false;
      bool HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = false;

      tree->SetBranchAddress("weight", &weight);
      tree->SetBranchAddress("lep1Id", &lep1Id);
      tree->SetBranchAddress("lep1Pt", &lep1Pt);
      tree->SetBranchAddress("lep1Eta", &lep1Eta);
      tree->SetBranchAddress("lep1Phi", &lep1Phi);
      tree->SetBranchAddress("lep2Id", &lep2Id);
      tree->SetBranchAddress("lep2Pt", &lep2Pt);
      tree->SetBranchAddress("lep2Eta", &lep2Eta);
      tree->SetBranchAddress("lep2Phi", &lep2Phi);
      tree->SetBranchAddress("dileptonMass", &dileptonMass);
      tree->SetBranchAddress("MET", &MET);
      tree->SetBranchAddress("NJets", &NJets);
      tree->SetBranchAddress("NBTags", &NBTags);     
      tree->SetBranchAddress("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ",
				   &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ);
      tree->SetBranchAddress("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ",
				   &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ);
      
     
      bool isData = false;
      if ( processLabels[i] == "Data") isData = true;
    
      cout << "process: " << processLabels[i] << " | file " << inputfiles[i][j] << " | Total Entries: " << tree->GetEntries() << "\n";

      for(UInt_t ientry=0; ientry < tree->GetEntries(); ientry++) {       	
	tree->GetEntry(ientry);
      

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
	passTrigger = HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ || HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ;
	if (!passTrigger) continue;

	//******************************
	//Selection Cuts 
	//******************************
	if (!( (abs(lep1Id) == 11 || abs(lep1Id) == 13)
	       &&
	       (abs(lep2Id) == 11 || abs(lep2Id) == 13)
	       )
	    ) continue;

	if (!(abs(lep1Id) != abs(lep2Id))) continue;

	//lepton selection
	if (! (lep1Pt > 30 && lep2Pt > 30)) continue;	
	
	//dilepton mass cut
	if ( dileptonMass < 20) continue;
	if ( MET < 40) continue;


	//if (!(NBTags >= 1 )) continue;
	     
	//******************************
	//Fill histograms
	//******************************
	if (isData) {
	  dataYield += 1.0;
	  histDileptonMass[i]->Fill(dileptonMass);      
	  histMET[i]->Fill(MET);

	} else {
	  MCYield += myWeight;
	  histDileptonMass[i]->Fill(dileptonMass, myWeight );      
	  histMET[i]->Fill(MET, myWeight );
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
  PlotDataAndStackedBkg( histDileptonMass, processLabels, color, true, "DileptonMass", Label);
  PlotDataAndStackedBkg( histMET, processLabels, color, true, "MET", Label);

  //--------------------------------------------------------------------------------------------------------------
  // Tables
  //==============================================================================================================
  cout << "For Luminosity = " << lumi << " pb^-1\n";
  // cout << "Yields : MR > 300 && Rsq > 0.1\n";
  //cout << "TTJets: " << 

  cout << "Selected Event Yield \n";
  cout << "Data: " << dataYield << "\n";
  cout << "MC: " << MCYield << "\n";

  // //--------------------------------------------------------------------------------------------------------------
  // // Output
  // //==============================================================================================================
  TFile *file = TFile::Open(("TTBarDileptonControlRegionPlots"+Label+".root").c_str(), "UPDATE");
  file->cd();

  for(int i=0; i<int(inputfiles.size()); i++) {
    file->WriteTObject(histDileptonMass[i], Form("histDileptonMass_%s",processLabels[i].c_str()), "WriteDelete");
    file->WriteTObject(histMET[i], Form("histMET_%s",processLabels[i].c_str()), "WriteDelete");
  } 
  
  file->Close();
  delete file;       

}







void SelectTTBarDileptonControlSample( int option = 0) {

  vector<string> datafiles;
  vector<vector<string> > bkgfiles;
  vector<string> processLabels;
  vector<int> colors;

  string datafile = "";


  //No Skims  
  if (option == 0 ) {
    datafiles.push_back("/afs/cern.ch/work/s/sixie/public/Production/pancake/V1p0/2017/MC/CMSSW_10_6_5/src/HHBoostedAnalyzer/DileptonNtuple.data_2017B.root");
  }

  vector<string> bkgfiles_ttbar;
  vector<string> bkgfiles_wjets;
  vector<string> bkgfiles_singletop;
  vector<string> bkgfiles_dy;  
  vector<string> bkgfiles_vv; 
  vector<string> bkgfiles_ttv;

  bkgfiles_ttbar.push_back("/afs/cern.ch/work/s/sixie/public/Production/pancake/V1p0/2017/MC/CMSSW_10_6_5/src/HHBoostedAnalyzer/DileptonNtuple.ttbar_1pb_weighted.root");

  // bkgfiles_wjets.push_back("/afs/cern.ch/user/s/sixie/eos2/cms/store/group/phys_susy/razor/Run2Analysis/RunTwoRazorControlRegions/2015/DileptonFull_1p23_2015Final/RunTwoRazorControlRegions_DileptonFull_DileptonSkim_WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_1pb_weighted.root"); 
  // bkgfiles_singletop.push_back("/afs/cern.ch/user/s/sixie/eos2/cms/store/group/phys_susy/razor/Run2Analysis/RunTwoRazorControlRegions/2015/DileptonFull_1p23_2015Final/RunTwoRazorControlRegions_DileptonFull_DileptonSkim_SingleTop_1pb_weighted.root");  
  // bkgfiles_dy.push_back("/afs/cern.ch/user/s/sixie/eos2/cms/store/group/phys_susy/razor/Run2Analysis/RunTwoRazorControlRegions/2015/DileptonFull_1p23_2015Final/RunTwoRazorControlRegions_DileptonFull_DileptonSkim_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_1pb_weighted.root");
  // //bkgfiles_dy.push_back("/afs/cern.ch/user/s/sixie/eos2/cms/store/group/phys_susy/razor/Run2Analysis/RunTwoRazorControlRegions/2015/DileptonFull_1p23_2015Final/RunTwoRazorControlRegions_DileptonFull_DileptonSkim_DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_1pb_weighted.root");
  // bkgfiles_vv.push_back("/afs/cern.ch/user/s/sixie/eos2/cms/store/group/phys_susy/razor/Run2Analysis/RunTwoRazorControlRegions/2015/DileptonFull_1p23_2015Final/RunTwoRazorControlRegions_DileptonFull_DileptonSkim_VV_1pb_weighted.root");
  // bkgfiles_ttv.push_back("/afs/cern.ch/user/s/sixie/eos2/cms/store/group/phys_susy/razor/Run2Analysis/RunTwoRazorControlRegions/2015/DileptonFull_1p23_2015Final/RunTwoRazorControlRegions_DileptonFull_DileptonSkim_TTV_1pb_weighted.root");    



  bkgfiles.push_back(bkgfiles_ttbar);
  // bkgfiles.push_back(bkgfiles_dy);
  // bkgfiles.push_back(bkgfiles_vv);
  // bkgfiles.push_back(bkgfiles_singletop);
  // bkgfiles.push_back(bkgfiles_wjets);
  // bkgfiles.push_back(bkgfiles_ttv);

  processLabels.push_back("TTJets");  
  // processLabels.push_back("DY");
  // processLabels.push_back("WW");
  // processLabels.push_back("SingleTop");
  // processLabels.push_back("WJets");
  // processLabels.push_back("TT+V");

  colors.push_back(kAzure+10);
  // colors.push_back(kGreen+2);
  // colors.push_back(kGray);
  // colors.push_back(kBlue);
  // colors.push_back(kRed);
  // colors.push_back(kRed);
 
  double lumi = 4793;

  //*********************************************************************
  //E-Mu Control Region
  //********************************************************************* 
  RunSelectTTBarDileptonControlSample(datafiles, bkgfiles,processLabels, colors, lumi,"",0,"");


}


//**********************************
//E-Mu Yields :
//**********************************

//MuEG Triggers ( 30 - 20 )
// Data: 148
// MC: 156.16
