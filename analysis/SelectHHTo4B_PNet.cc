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

//#include "HHBoostedAnalyzer/macros/tdrstyle.C"
//#include "HHBoostedAnalyzer/macros/CMS_lumi.C"
#include "tdrstyle.C"
#include "CMS_lumi.C"

#endif

float _signalSF = 10.0;

void PlotDataAndStackedBkg( std::vector<TH1D*> hist , std::vector<std::string> processLabels, std::vector<int> color,  bool hasData, std::string varName, std::string label ) {

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
  TH1D *histHH_Signal  = new TH1D();
  std::cout << "deb0" << std::endl;
  std::cout << "deb0: hist.size()-> " << hist.size() << std::endl;
  if (hasData) {
    for (int i = hist.size()-1; i >= 1; --i)
    {
      std::cout << "deb0.0.1; hist[i]->Integral()" << hist[i]->Integral() << std::endl;
      if ( hist[i]->Integral() > 0)
      {
        std::cout << "deb0.1" << std::endl;
        if( processLabels[i] != "HH" )
        {
          hist[i]->SetFillColor(color[i]);
          hist[i]->SetFillStyle(1001);
          stack->Add(hist[i]);
        }
        else histHH_Signal = hist[i];
      }
    }
  } else {
    for (int i = hist.size()-1; i >= 0; --i) {

      std::cout << "deb0.0.2; hist[i]->Integral()" << hist[i]->Integral() << std::endl;
      if ( hist[i]->Integral() > 0)
      {
        std::cout << "deb0.2" << std::endl;
  	     if( processLabels[i] != "HH" )
         {
           hist[i]->SetFillColor(color[i]);
           hist[i]->SetFillStyle(1001);
           stack->Add(hist[i]);
         }
         else histHH_Signal = hist[i];
      }
    }
  }

  std::cout << "deb1" << std::endl;
  for (uint i = 0 ; i < hist.size(); ++i) {
    if (hasData && i==0) {
      legend->AddEntry(hist[i],(processLabels[i]).c_str(), "LP");
    }
    else if(processLabels[i] == "HH")
    {
      legend->AddEntry(hist[i],(processLabels[i]).c_str(), "L");
    }
    else {
      legend->AddEntry(hist[i],(processLabels[i]).c_str(), "F");
    }
  }

  std::cout << "deb2" << std::endl;
  if (stack->GetHists()->GetEntries() > 0) {
    std::cout << "deb2.1" << std::endl;
    stack->Draw("hist");
    histHH_Signal->SetLineColor(kViolet-4);
    histHH_Signal->SetLineWidth(6);
    histHH_Signal->SetLineStyle(9);
    histHH_Signal->Scale(_signalSF);
    histHH_Signal->Draw("hist+same");
    std::cout << "deb2.2" << std::endl;
    stack->GetHistogram()->GetXaxis()->SetTitle(((TH1D*)(stack->GetHists()->At(0)))->GetXaxis()->GetTitle());
    std::cout << "deb2.3" << std::endl;
    stack->GetHistogram()->GetYaxis()->SetTitle(((TH1D*)(stack->GetHists()->At(0)))->GetYaxis()->GetTitle());
    std::cout << "deb2.4" << std::endl;
    stack->GetHistogram()->GetYaxis()->SetTitleOffset(1.0);
    std::cout << "deb2.5" << std::endl;
    stack->GetHistogram()->GetYaxis()->SetTitleSize(0.05);
    std::cout << "deb2.6" << std::endl;
    stack->GetHistogram()->GetXaxis()->SetTitleSize(0.15);
    std::cout << "deb2.7" << std::endl;
    stack->SetMaximum( 1.2* fmax( stack->GetMaximum(), hist[0]->GetMaximum()) );
    std::cout << "deb2.8" << std::endl;
    stack->SetMinimum( 0.1 );
    std::cout << "deb2.9" << std::endl;
    if (hasData) {
     hist[0]->SetMarkerStyle(20);
      hist[0]->SetMarkerSize(1);
      hist[0]->SetLineWidth(1);
      hist[0]->SetLineColor(color[0]);
      hist[0]->Draw("pesame");
    }
    legend->Draw();
    std::cout << "deb2.10" << std::endl;
 }

 std::cout << "deb3" << std::endl;
  //****************************
  //Add CMS and Lumi Labels
  //****************************
  // lumi_13TeV = "42 pb^{-1}";
  lumi_13TeV = "26.2 fb^{-1}";
  writeExtraText = true;
  relPosX = 0.13;
  CMS_lumi(pad1,4,0);

  cv->cd();
  cv->Update();

  std::cout << "deb4" << std::endl;
  TPad *pad2 = new TPad("pad2","pad2", 0,0,1,0.25);
  pad2->SetTopMargin(0.01);
  pad2->SetBottomMargin(0.37);
  pad2->SetRightMargin(0.04);
  pad2->SetGridy();
  pad2->Draw();
  pad2->cd();
  std::cout << "deb5" << std::endl;
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
    //std::cout << "bin " << b << " : " << histDataOverMC->GetBinContent(b) << " " << histDataOverMC->GetBinError(b) << "\n";
  }
  std::cout << "deb6" << std::endl;
  histDataOverMC->GetYaxis()->SetTitle("Data/MC");
  histDataOverMC->GetYaxis()->SetNdivisions(306);
  histDataOverMC->GetYaxis()->SetTitleSize(0.10);
  histDataOverMC->GetYaxis()->SetTitleOffset(0.3);
  histDataOverMC->GetYaxis()->SetRangeUser(0.1,1.9);
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
  cv->SaveAs(Form("HHTo4B_%s%s.png",varName.c_str(), label.c_str()));
  cv->SaveAs(Form("HHTo4B_%s%s.pdf",varName.c_str(), label.c_str()));

  pad1->SetLogy(true);
  cv->SaveAs(Form("HHTo4B_%s%s_Logy.png",varName.c_str(),label.c_str()));
  cv->SaveAs(Form("HHTo4B_%s%s_Logy.pdf",varName.c_str(),label.c_str()));
};



//=== MAIN MACRO =================================================================================================


void RunSelectHHTo4B(  std::vector<std::string> datafiles, std::vector<std::vector<std::string> > bkgfiles, std::vector<std::string> bkgLabels, std::vector<int> bkgColors, std::vector<float> bkgScaleFactors,double lumi, std::string option, int channelOption = -1, std::string label = "") {

  std::string Label = "";
  if (label != "") Label = "_" + label;

  //--------------------------------------------------------------------------------------------------------------
  // Settings
  //==============================================================================================================

  //*****************************************************************************************
  //Make some histograms
  //*****************************************************************************************
  std::vector<std::vector<std::string> > inputfiles;
  std::vector<std::string> processLabels;
  std::vector<int> color;
  std::vector<float> scaleFactors;

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
    std::cout << processLabels[i] << " : " << scaleFactors[i] << "\n";
  }


  std::vector<TH1D*> histMET;
  std::vector<TH1D*> histNLeptons;
  std::vector<TH1D*> histNJetsHaveLeptons;
  std::vector<TH1D*> histJet1Mass;
  std::vector<TH1D*> histJet1Pt;
  std::vector<TH1D*> histJet1Eta;
  std::vector<TH1D*> histJet1Phi;
  std::vector<TH1D*> histJet1DDB;
  std::vector<TH1D*> histJet1PNetXbb;
  std::vector<TH1D*> histJet1Tau3OverTau2;
  std::vector<TH1D*> histJet2Mass;
  std::vector<TH1D*> histJet2Pt;
  std::vector<TH1D*> histJet2Eta;
  std::vector<TH1D*> histJet2Phi;
  std::vector<TH1D*> histJet2DDB;
  std::vector<TH1D*> histJet2PNetXbb;
  std::vector<TH1D*> histJet2Tau3OverTau2;
  //
  std::vector<TH1D*> histHH_Pt;
  std::vector<TH1D*> histHH_Eta;
  std::vector<TH1D*> histHH_Phi;
  std::vector<TH1D*> histHH_Mass;
  std::vector<TH1D*> histJet1PtOverMHH;
  std::vector<TH1D*> histJet2PtOverMHH;
  std::vector<TH1D*> histJet1PtOverMSD;
  std::vector<TH1D*> histJet2PtOverMSD;
  std::vector<TH1D*> histDeltaEta_J1J2;
  std::vector<TH1D*> histDeltaPhi_J1J2;
  std::vector<TH1D*> histDeltaR_J1J2;
  std::vector<TH1D*> histJet2PtOverJet1Pt;
  std::vector<TH1D*> histJet2MSD_Over_Jet1MSD;

  //
  std::vector<TH1D*> hist_disc_qcd_2017_basic0;
  std::vector<TH1D*> hist_disc_qcd_2017_basic1;
  std::vector<TH1D*> hist_disc_qcd_2017_basic2;
  std::vector<TH1D*> hist_disc_qcd_2017_enhanced;
  //
  std::vector<TH1D*> hist_disc_ttbar_2017_basic0;
  std::vector<TH1D*> hist_disc_ttbar_2017_basic1;
  std::vector<TH1D*> hist_disc_ttbar_2017_basic2;
  std::vector<TH1D*> hist_disc_ttbar_2017_enhanced;
  //
  std::vector<TH1D*> hist_disc_qcd_and_ttbar_2017_basic0;
  std::vector<TH1D*> hist_disc_qcd_and_ttbar_2017_basic1;
  std::vector<TH1D*> hist_disc_qcd_and_ttbar_2017_basic2;
  std::vector<TH1D*> hist_disc_qcd_and_ttbar_2017_enhanced;

  assert (inputfiles.size() == processLabels.size());
  for (uint i=0; i < inputfiles.size(); ++i) {
    histMET.push_back(new TH1D(Form("histMET_%s",processLabels[i].c_str()), "; MET [GeV] ; Number of Events", 25, 0, 200));
    histNLeptons.push_back(new TH1D(Form("histNLeptons_%s",processLabels[i].c_str()), "; NLeptons ; Number of Events", 10, -0.5, 9.5));
    histNJetsHaveLeptons.push_back(new TH1D(Form("histNJetsHaveLeptons_%s",processLabels[i].c_str()), "; NJetsHaveLeptons ; Number of Events", 3, -0.5, 2.5));
    histJet1Mass.push_back(new TH1D(Form("histJet1Mass_%s",processLabels[i].c_str()), "; Jet1 Mass [GeV] ; Number of Events", 25, 0, 500));
    histJet1Pt.push_back(new TH1D(Form("histJet1Pt_%s",processLabels[i].c_str()), "; Jet1 p_{T} [GeV] ; Number of Events", 25, 0, 2000));
    histJet1Eta.push_back(new TH1D(Form("histJet1Eta_%s",processLabels[i].c_str()), "; Jet1 #eta ; Number of Events", 25, -5, 5));
    histJet1Phi.push_back(new TH1D(Form("histJet1Phi_%s",processLabels[i].c_str()), "; Jet1 #phi ; Number of Events", 25, -5, 5));
    histJet1DDB.push_back(new TH1D(Form("histJet1DDB_%s",processLabels[i].c_str()), "; Jet1 DDB ; Number of Events", 100, 0, 1.0));
    histJet1PNetXbb.push_back(new TH1D(Form("histJet1PNetXbb_%s",processLabels[i].c_str()), "; Jet1 PNetXbb ; Number of Events", 100, 0, 1.0));
    histJet1Tau3OverTau2.push_back(new TH1D(Form("histJet1Tau3OverTau2_%s",processLabels[i].c_str()), "; Jet1 Tau3OverTau2 ; Number of Events", 25, 0, 1.0));
    histJet2Mass.push_back(new TH1D(Form("histJet2Mass_%s",processLabels[i].c_str()), "; Jet2 Mass [GeV] ; Number of Events", 25, 0, 500));
    histJet2Pt.push_back(new TH1D(Form("histJet2Pt_%s",processLabels[i].c_str()), "; Jet2 p_{T} [GeV] ; Number of Events", 25, 0, 1000));
    histJet2Eta.push_back(new TH1D(Form("histJet2Eta_%s",processLabels[i].c_str()), "; Jet2 #eta ; Number of Events", 25, -5, 5));
    histJet2Phi.push_back(new TH1D(Form("histJet2Phi_%s",processLabels[i].c_str()), "; Jet2 #phi ; Number of Events", 25, -5, 5));
    histJet2DDB.push_back(new TH1D(Form("histJet1DDB_%s",processLabels[i].c_str()), "; Jet2 DDB ; Number of Events", 25, 0, 1.0));
    histJet2PNetXbb.push_back(new TH1D(Form("histJet2PNetXbb_%s",processLabels[i].c_str()), "; Jet2 PNetXbb ; Number of Events", 25, 0, 1.0));
    histJet2Tau3OverTau2.push_back(new TH1D(Form("histJet1Tau3OverTau2_%s",processLabels[i].c_str()), "; Jet2 Tau3OverTau2 ; Number of Events", 25, 0, 1.0));


    //
    histHH_Pt.push_back(new TH1D(Form("histHH_Pt_%s",processLabels[i].c_str()), "; HH p_{T} [GeV] ; Number of Events", 50, 0, 2000));
    histHH_Eta.push_back(new TH1D(Form("histHH_Eta_%s",processLabels[i].c_str()), "; HH #eta ; Number of Events", 50, -10, 10));
    histHH_Phi.push_back(new TH1D(Form("histHH_Phi_%s",processLabels[i].c_str()), "; HH #phi ; Number of Events", 25, -5, 5));
    histHH_Mass.push_back(new TH1D(Form("histHH_Mass_%s",processLabels[i].c_str()), "; HH Mass [GeV] ; Number of Events", 100, 10, 5000));
    histJet1PtOverMHH.push_back(new TH1D(Form("histJet1PtOverMHH_%s",processLabels[i].c_str()), "; Jet1-p_{T}/M_{HH} ; Number of Events", 35, 0, 3.0));
    histJet2PtOverMHH.push_back(new TH1D(Form("histJet2PtOverMHH_%s",processLabels[i].c_str()), "; Jet2-p_{T}/M_{HH} ; Number of Events", 35, 0, 3.0));
    histJet1PtOverMSD.push_back(new TH1D(Form("histJet1PtOverMSD_%s",processLabels[i].c_str()), "; Jet1-p_{T}/M_{Jet1} ; Number of Events", 35, 1, 15.0));
    histJet2PtOverMSD.push_back(new TH1D(Form("histJet2PtOverMSD_%s",processLabels[i].c_str()), "; Jet2-p_{T}/M_{Jet2} ; Number of Events", 35, 1, 15.0));
    histDeltaEta_J1J2.push_back(new TH1D(Form("histDeltaEta_J1J2_%s",processLabels[i].c_str()), "; #Delta#eta(j_{1}-j_{2}) ; Number of Events", 25, -1, 5));
    histDeltaPhi_J1J2.push_back(new TH1D(Form("histDeltaPhi_J1J2_%s",processLabels[i].c_str()), "; #Delta#phi(j_{1}-j_{2}) ; Number of Events", 25, -5, 5));
    histDeltaR_J1J2.push_back(new TH1D(Form("histDeltaR_J1J2_%s",processLabels[i].c_str()), "; #Delta R(j_{1}-j_{2}) ; Number of Events", 25, 0, 7));
    histJet2PtOverJet1Pt.push_back(new TH1D(Form("histJet2PtOverJet1Pt_%s",processLabels[i].c_str()), "; Jet1-p_{T}/Jet1-p_{T} ; Number of Events", 50, 0, 2.0));
    histJet2MSD_Over_Jet1MSD.push_back(new TH1D(Form("histJet2MSD_Over_Jet1MSD_%s",processLabels[i].c_str()), "; M_{Jet2}/M_{Jet1} ; Number of Events", 25, 0, 10.0));
    //
    hist_disc_qcd_2017_basic0.push_back(new TH1D(Form("hist_disc_qcd_2017_basic0_%s",processLabels[i].c_str()), "; disc_qcd_2017_basic0 ; Number of Events", 25, 0, 1.0));
    hist_disc_qcd_2017_basic1.push_back(new TH1D(Form("hist_disc_qcd_2017_basic1_%s",processLabels[i].c_str()), "; disc_qcd_2017_basic1 ; Number of Events", 25, 0, 1.0));
    hist_disc_qcd_2017_basic2.push_back(new TH1D(Form("hist_disc_qcd_2017_basic2_%s",processLabels[i].c_str()), "; disc_qcd_2017_basic2 ; Number of Events", 25, 0, 1.0));
    hist_disc_qcd_2017_enhanced.push_back(new TH1D(Form("hist_disc_qcd_2017_enhanced_%s",processLabels[i].c_str()), "; disc_qcd_2017_enhanced ; Number of Events", 25, 0, 1.0));
    //
    hist_disc_ttbar_2017_basic0.push_back(new TH1D(Form("hist_disc_ttbar_2017_basic0_%s",processLabels[i].c_str()), "; disc_ttbar_2017_basic0 ; Number of Events", 25, 0, 1.0));
    hist_disc_ttbar_2017_basic1.push_back(new TH1D(Form("hist_disc_ttbar_2017_basic1_%s",processLabels[i].c_str()), "; disc_ttbar_2017_basic1 ; Number of Events", 25, 0, 1.0));
    hist_disc_ttbar_2017_basic2.push_back(new TH1D(Form("hist_disc_ttbar_2017_basic2_%s",processLabels[i].c_str()), "; disc_ttbar_2017_basic2 ; Number of Events", 25, 0, 1.0));
    hist_disc_ttbar_2017_enhanced.push_back(new TH1D(Form("hist_disc_ttbar_2017_enhanced_%s",processLabels[i].c_str()), "; disc_ttbar_2017_enhanced ; Number of Events", 25, 0, 1.0));
    //
    hist_disc_qcd_and_ttbar_2017_basic0.push_back(new TH1D(Form("hist_disc_qcd_and_ttbar_2017_basic0_%s",processLabels[i].c_str()), "; disc_qcd_2017_and_ttbar_basic0 ; Number of Events", 25, 0, 1.0));
    hist_disc_qcd_and_ttbar_2017_basic1.push_back(new TH1D(Form("hist_disc_qcd_and_ttbar_2017_basic1_%s",processLabels[i].c_str()), "; disc_qcd_2017_and_ttbar_basic1 ; Number of Events", 25, 0, 1.0));
    hist_disc_qcd_and_ttbar_2017_basic2.push_back(new TH1D(Form("hist_disc_qcd_and_ttbar_2017_basic2_%s",processLabels[i].c_str()), "; disc_qcd_2017_and_ttbar_basic2 ; Number of Events", 25, 0, 1.0));
    hist_disc_qcd_and_ttbar_2017_enhanced.push_back(new TH1D(Form("hist_disc_qcd_and_ttbar_2017_enhanced_%s",processLabels[i].c_str()), "; disc_qcd_and_ttbar_2017_enhanced ; Number of Events", 25, 0, 1.0));



    histMET[i]->Sumw2();
    histNLeptons[i]->Sumw2();
    histNJetsHaveLeptons[i]->Sumw2();
    histJet1Mass[i]->Sumw2();
    histJet1Pt[i]->Sumw2();
    histJet1Eta[i]->Sumw2();
    histJet1Phi[i]->Sumw2();
    histJet1DDB[i]->Sumw2();
    histJet1PNetXbb[i]->Sumw2();
    histJet1Tau3OverTau2[i]->Sumw2();
    histJet2Mass[i]->Sumw2();
    histJet2Pt[i]->Sumw2();
    histJet2Eta[i]->Sumw2();
    histJet2Phi[i]->Sumw2();
    histJet2DDB[i]->Sumw2();
    histJet2PNetXbb[i]->Sumw2();
    histJet2Tau3OverTau2[i]->Sumw2();
    //
    histHH_Pt[i]->Sumw2();
    histHH_Eta[i]->Sumw2();
    histHH_Phi[i]->Sumw2();
    histHH_Mass[i]->Sumw2();
    histJet1PtOverMHH[i]->Sumw2();
    histJet2PtOverMHH[i]->Sumw2();
    histJet1PtOverMSD[i]->Sumw2();
    histJet2PtOverMSD[i]->Sumw2();
    histDeltaEta_J1J2[i]->Sumw2();
    histDeltaPhi_J1J2[i]->Sumw2();
    histDeltaR_J1J2[i]->Sumw2();
    histJet2PtOverJet1Pt[i]->Sumw2();
    histJet2MSD_Over_Jet1MSD[i]->Sumw2();
    //
    hist_disc_qcd_2017_basic0[i]->Sumw2();
    hist_disc_qcd_2017_basic1[i]->Sumw2();
    hist_disc_qcd_2017_basic2[i]->Sumw2();
    hist_disc_qcd_2017_enhanced[i]->Sumw2();
    //
    hist_disc_ttbar_2017_basic0[i]->Sumw2();
    hist_disc_ttbar_2017_basic1[i]->Sumw2();
    hist_disc_ttbar_2017_basic2[i]->Sumw2();
    hist_disc_ttbar_2017_enhanced[i]->Sumw2();
    //
    hist_disc_qcd_and_ttbar_2017_basic0[i]->Sumw2();
    hist_disc_qcd_and_ttbar_2017_basic1[i]->Sumw2();
    hist_disc_qcd_and_ttbar_2017_basic2[i]->Sumw2();
    hist_disc_qcd_and_ttbar_2017_enhanced[i]->Sumw2();
  }

  double dataYield = 0;
  double MCYield = 0;
  double SignalYield = 0;


  //*******************************************************************************************
  //Read file
  //*******************************************************************************************
  for (uint i=0; i < inputfiles.size(); ++i) {

    //for duplicate event checking
    std::map<std::pair<uint,uint>, bool > processedRunEvents;

    for (uint j=0; j < inputfiles[i].size(); ++j) {

      TFile *file = new TFile(inputfiles[i][j].c_str(),"READ");
      TTree *tree = 0;
      if (!file) {
	std::cout << "Input file " << inputfiles[i][j] << " could not be opened\n";
	continue;
      } else {
	tree = (TTree*)file->Get("tree");
      }
      if (!tree) {
	std::cout << "Tree could not be found in input file " << inputfiles[i][j] << "\n";
	continue;
      }

      float weight = 0;
      float triggerEffWeight = 0;
      float pileupWeight = 0;
      float totalWeight = 0;
      float MET = 0;
      float fatJet1Pt = 0;
      float fatJet1Eta = -99.;
      float fatJet1Phi = -99.;
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
      float fatJet2Eta = -99.;
      float fatJet2Phi = -99.;
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

      //
      float hh_pt = 0;
      float hh_eta = 0;
      float hh_phi = 0;
      float hh_mass = 0;
      float fatJet1PtOverMHH = 0;
      float fatJet1PtOverMSD = 0;
      float fatJet2PtOverMHH = 0;
      float fatJet2PtOverMSD = 0;
      float deltaEta_j1j2 = 0;
      float deltaPhi_j1j2 = 0;
      float deltaR_j1j2 = 0;
      float ptj2_over_ptj1 = 0;
      float mj2_over_mj1 = 0;

      //
      bool HLT_PFHT1050;
      bool HLT_AK8PFJet360_TrimMass30;
      bool HLT_AK8PFJet380_TrimMass30;
      bool HLT_AK8PFJet400_TrimMass30;
      bool HLT_AK8PFJet420_TrimMass30;
      bool HLT_AK8PFHT800_TrimMass50;
      bool HLT_PFJet450;
      bool HLT_PFJet500;
      bool HLT_AK8PFJet500;
      bool HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17;
      bool HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1;
      bool HLT_AK8PFJet330_PFAK8BTagCSV_p17;
      bool HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02;
      bool HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2;
      bool HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4;

      //BDTs
      float disc_qcd_2017_basic0 = -1.0;
      float disc_qcd_2017_basic1 = -1.0;
      float disc_qcd_2017_basic2 = -1.0;
      float disc_qcd_2017_enhanced = -1.0;
      //
      float disc_ttbar_2017_basic0 = -1.0;
      float disc_ttbar_2017_basic1 = -1.0;
      float disc_ttbar_2017_basic2 = -1.0;
      float disc_ttbar_2017_enhanced = -1.0;
      //
      float disc_qcd_and_ttbar_2017_basic0 = -1.0;
      float disc_qcd_and_ttbar_2017_basic1 = -1.0;
      float disc_qcd_and_ttbar_2017_basic2 = -1.0;
      float disc_qcd_and_ttbar_2017_enhanced = -1.0;

      tree->SetBranchAddress("weight",&weight);
      tree->SetBranchAddress("triggerEffWeight",&triggerEffWeight);
      tree->SetBranchAddress("pileupWeight",&pileupWeight);
      tree->SetBranchAddress("totalWeight",&totalWeight);
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
      tree->SetBranchAddress("fatJet2Eta",&fatJet2Eta);
      tree->SetBranchAddress("fatJet2Phi",&fatJet2Phi);
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
      //
      tree->SetBranchAddress("hh_pt",&hh_pt);
      tree->SetBranchAddress("hh_eta",&hh_eta);
      tree->SetBranchAddress("hh_phi",&hh_phi);
      tree->SetBranchAddress("hh_mass",&hh_mass);
      tree->SetBranchAddress("fatJet1PtOverMHH",&fatJet1PtOverMHH);
      tree->SetBranchAddress("fatJet1PtOverMSD",&fatJet1PtOverMSD);
      tree->SetBranchAddress("fatJet2PtOverMHH",&fatJet2PtOverMHH);
      tree->SetBranchAddress("fatJet2PtOverMSD",&fatJet2PtOverMSD);
      tree->SetBranchAddress("deltaEta_j1j2",&deltaEta_j1j2);
      tree->SetBranchAddress("deltaPhi_j1j2",&deltaPhi_j1j2);
      tree->SetBranchAddress("deltaR_j1j2",&deltaR_j1j2);
      tree->SetBranchAddress("ptj2_over_ptj1",&ptj2_over_ptj1);
      tree->SetBranchAddress("mj2_over_mj1",&mj2_over_mj1);
      //
      tree->SetBranchAddress("HLT_AK8PFJet360_TrimMass30",                          &HLT_AK8PFJet360_TrimMass30);
      tree->SetBranchAddress("HLT_AK8PFJet380_TrimMass30",                          &HLT_AK8PFJet380_TrimMass30);
      tree->SetBranchAddress("HLT_AK8PFJet400_TrimMass30",                          &HLT_AK8PFJet400_TrimMass30);
      tree->SetBranchAddress("HLT_AK8PFJet420_TrimMass30",                          &HLT_AK8PFJet420_TrimMass30);
      tree->SetBranchAddress("HLT_AK8PFHT800_TrimMass50",                           &HLT_AK8PFHT800_TrimMass50);
      tree->SetBranchAddress("HLT_PFJet450",                                        &HLT_PFJet450);
      tree->SetBranchAddress("HLT_PFJet500",                                        &HLT_PFJet500);
      tree->SetBranchAddress("HLT_AK8PFJet500",                                     &HLT_AK8PFJet500);
      tree->SetBranchAddress("HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17",     &HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17);
      tree->SetBranchAddress("HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1",      &HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1);
      tree->SetBranchAddress("HLT_AK8PFJet330_PFAK8BTagCSV_p17",                    &HLT_AK8PFJet330_PFAK8BTagCSV_p17);
      tree->SetBranchAddress("HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02",  &HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02);
      tree->SetBranchAddress("HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2",  &HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2);
      tree->SetBranchAddress("HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4",  &HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4);

      tree->SetBranchAddress("disc_qcd_2017_basic0",             &disc_qcd_2017_basic0);
      tree->SetBranchAddress("disc_qcd_2017_basic1",             &disc_qcd_2017_basic1);
      tree->SetBranchAddress("disc_qcd_2017_basic2",             &disc_qcd_2017_basic2);
      tree->SetBranchAddress("disc_qcd_2017_enhanced",           &disc_qcd_2017_enhanced);
      //
      tree->SetBranchAddress("disc_ttbar_2017_basic0",            &disc_ttbar_2017_basic0);
      tree->SetBranchAddress("disc_ttbar_2017_basic1",            &disc_ttbar_2017_basic1);
      tree->SetBranchAddress("disc_ttbar_2017_basic2",           &disc_ttbar_2017_basic2);
      tree->SetBranchAddress("disc_ttbar_2017_enhanced",         &disc_ttbar_2017_enhanced);
      //
      tree->SetBranchAddress("disc_qcd_and_ttbar_2017_basic0",   &disc_qcd_and_ttbar_2017_basic0);
      tree->SetBranchAddress("disc_qcd_and_ttbar_2017_basic1",   &disc_qcd_and_ttbar_2017_basic1);
      tree->SetBranchAddress("disc_qcd_and_ttbar_2017_basic2",   &disc_qcd_and_ttbar_2017_basic2);
      tree->SetBranchAddress("disc_qcd_and_ttbar_2017_enhanced", &disc_qcd_and_ttbar_2017_enhanced);

      bool isData = false;
      if ( processLabels[i] == "Data") isData = true;

      std::cout << "process: " << processLabels[i] << " | file " << inputfiles[i][j] << " | Total Entries: " << tree->GetEntries() << "\n";

      for(UInt_t ientry=0; ientry < tree->GetEntries(); ientry++) {
	tree->GetEntry(ientry);


	if (ientry % 100000 == 0) std::cout << "Event " << ientry << std::endl;

	double puWeight = 1;
	double myWeight = 1;
	if (!isData) {
	  //myWeight = lumi * weight * pileupWeight * triggerEffWeight * scaleFactors[i];
    myWeight = lumi * weight * pileupWeight * scaleFactors[i];
    //std::cout << "myWeight: " << myWeight << std::endl;
    //std::cout << lumi << " " << weight << " "  << pileupWeight << " "  << triggerEffWeight << std::endl;
	  //std::cout << "scaleFactors: " << scaleFactors[i] << "\n";
	}

	//******************************
	//Trigger Selection
	//******************************
	bool passTrigger = false;
	passTrigger =
	  // HLT_PFJet450
	  // || HLT_PFJet500

	  HLT_AK8PFJet360_TrimMass30
	  || HLT_AK8PFJet380_TrimMass30
	  || HLT_AK8PFJet400_TrimMass30
	  || HLT_AK8PFJet420_TrimMass30
	  || HLT_AK8PFHT800_TrimMass50
	  || HLT_PFJet450
	  || HLT_PFJet500
	  || HLT_AK8PFJet500
	  //|| HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17
	  //|| HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1
	  || HLT_AK8PFJet330_PFAK8BTagCSV_p17
	  //|| HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02
	  //|| HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2
	  //|| HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4
	  ;
	if (!passTrigger) continue;

	//******************************
	//Selection Cuts
	//******************************
	if ( !(fatJet1Pt > 250 )) continue;
	if ( !(fatJet2Pt > 250 )) continue;
	if ( !(fatJet1MassSD > 30)) continue;
	if ( !(fatJet2MassSD > 30)) continue;


	//SR selection
	if (channelOption == 0) {
	  // if ( !(fatJet1Pt > 350 || fatJet2Pt > 350)) continue;
	  // if ( !(fatJet1Pt > 300 && fatJet2Pt > 300 )) continue;
	  // if ( !(fatJet1PNetXbb > 0.975)) continue;
	  // if ( !(fatJet2PNetXbb > 0.975)) continue;
	  // if ( !(fatJet1MassSD > 100 && fatJet1MassSD < 140)) continue;
	  // //if ( !(fatJet2MassSD > 95 && fatJet2MassSD < 135)) continue;
    //if ( (fatJet1MassSD > 100 && fatJet1MassSD < 140)) continue;
    if ( (fatJet2MassSD > 95 && fatJet2MassSD < 135)) continue;

    //if( disc_qcd_2017_enhanced <= 0.9 ) continue;
	}

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
	  if (!fatJet1HasBJetCSVLoose) continue;
	  if (!fatJet2HasBJetCSVLoose) continue;
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
    histJet1Eta[i]->Fill(fatJet1Eta);
    histJet1Phi[i]->Fill(fatJet1Phi);
	  histJet1DDB[i]->Fill(fatJet1DDBTagger);
	  histJet1PNetXbb[i]->Fill(fatJet1PNetXbb);
	  histJet1Tau3OverTau2[i]->Fill(fatJet1Tau3OverTau2);
	  histJet2Mass[i]->Fill(fatJet2MassSD);
	  histJet2Pt[i]->Fill(fatJet2Pt);
    histJet2Eta[i]->Fill(fatJet2Eta);
    histJet2Phi[i]->Fill(fatJet2Phi);
	  histJet2DDB[i]->Fill(fatJet2DDBTagger);
	  histJet2PNetXbb[i]->Fill(fatJet2PNetXbb);
	  histJet2Tau3OverTau2[i]->Fill(fatJet2Tau3OverTau2);
    //
    histHH_Pt[i]->Fill(hh_pt);
    histHH_Eta[i]->Fill(hh_eta);
    histHH_Phi[i]->Fill(hh_phi);
    histHH_Mass[i]->Fill(hh_mass);
    histJet1PtOverMHH[i]->Fill(fatJet1PtOverMHH);
    histJet2PtOverMHH[i]->Fill(fatJet2PtOverMHH);
    histJet1PtOverMSD[i]->Fill(fatJet1PtOverMSD);
    histJet2PtOverMSD[i]->Fill(fatJet2PtOverMSD);
    histDeltaEta_J1J2[i]->Fill(deltaEta_j1j2);
    histDeltaPhi_J1J2[i]->Fill(deltaPhi_j1j2);
    histDeltaR_J1J2[i]->Fill(deltaR_j1j2);
    histJet2PtOverJet1Pt[i]->Fill(ptj2_over_ptj1);
    histJet2MSD_Over_Jet1MSD[i]->Fill(mj2_over_mj1);
    //
    hist_disc_qcd_2017_basic0[i]->Fill(disc_qcd_2017_basic0);
    hist_disc_qcd_2017_basic1[i]->Fill(disc_qcd_2017_basic1);
    hist_disc_qcd_2017_basic2[i]->Fill(disc_qcd_2017_basic2);
    hist_disc_qcd_2017_enhanced[i]->Fill(disc_qcd_2017_enhanced);
    //
    hist_disc_ttbar_2017_basic0[i]->Fill(disc_ttbar_2017_basic0);
    hist_disc_ttbar_2017_basic1[i]->Fill(disc_ttbar_2017_basic1);
    hist_disc_ttbar_2017_basic2[i]->Fill(disc_ttbar_2017_basic2);
    hist_disc_ttbar_2017_enhanced[i]->Fill(disc_ttbar_2017_enhanced);
    //
    hist_disc_qcd_and_ttbar_2017_basic0[i]->Fill(disc_qcd_and_ttbar_2017_basic0);
    hist_disc_qcd_and_ttbar_2017_basic1[i]->Fill(disc_qcd_and_ttbar_2017_basic1);
    hist_disc_qcd_and_ttbar_2017_basic2[i]->Fill(disc_qcd_and_ttbar_2017_basic2);
    hist_disc_qcd_and_ttbar_2017_enhanced[i]->Fill(disc_qcd_and_ttbar_2017_enhanced);

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
    histJet1Eta[i]->Fill(fatJet1Eta, myWeight);
    histJet1Phi[i]->Fill(fatJet1Phi, myWeight);
	  histJet1DDB[i]->Fill(fatJet1DDBTagger, myWeight);
	  histJet1PNetXbb[i]->Fill(fatJet1PNetXbb, myWeight);
	  histJet1Tau3OverTau2[i]->Fill(fatJet1Tau3OverTau2, myWeight);
	  histJet2Mass[i]->Fill(fatJet2MassSD, myWeight);
	  histJet2Pt[i]->Fill(fatJet2Pt, myWeight);
    histJet2Eta[i]->Fill(fatJet2Eta, myWeight);
    histJet2Phi[i]->Fill(fatJet2Phi, myWeight);
	  histJet2DDB[i]->Fill(fatJet2DDBTagger, myWeight);
	  histJet2PNetXbb[i]->Fill(fatJet2PNetXbb, myWeight);
	  histJet2Tau3OverTau2[i]->Fill(fatJet2Tau3OverTau2, myWeight);
    //
    histHH_Pt[i]->Fill(hh_pt, myWeight);
    histHH_Eta[i]->Fill(hh_eta, myWeight);
    histHH_Phi[i]->Fill(hh_phi, myWeight);
    histHH_Mass[i]->Fill(hh_mass, myWeight);
    histJet1PtOverMHH[i]->Fill(fatJet1PtOverMHH, myWeight);
    histJet2PtOverMHH[i]->Fill(fatJet2PtOverMHH, myWeight);
    histJet1PtOverMSD[i]->Fill(fatJet1PtOverMSD, myWeight);
    histJet2PtOverMSD[i]->Fill(fatJet2PtOverMSD, myWeight);
    histDeltaEta_J1J2[i]->Fill(deltaEta_j1j2, myWeight);
    histDeltaPhi_J1J2[i]->Fill(deltaPhi_j1j2, myWeight);
    histDeltaR_J1J2[i]->Fill(deltaR_j1j2, myWeight);
    histJet2PtOverJet1Pt[i]->Fill(ptj2_over_ptj1, myWeight);
    histJet2MSD_Over_Jet1MSD[i]->Fill(mj2_over_mj1, myWeight);
    //
    hist_disc_qcd_2017_basic0[i]->Fill(disc_qcd_2017_basic0, myWeight);
    hist_disc_qcd_2017_basic1[i]->Fill(disc_qcd_2017_basic1, myWeight);
    hist_disc_qcd_2017_basic2[i]->Fill(disc_qcd_2017_basic2, myWeight);
    hist_disc_qcd_2017_enhanced[i]->Fill(disc_qcd_2017_enhanced, myWeight);
    //
    hist_disc_ttbar_2017_basic0[i]->Fill(disc_ttbar_2017_basic0, myWeight);
    hist_disc_ttbar_2017_basic1[i]->Fill(disc_ttbar_2017_basic1, myWeight);
    hist_disc_ttbar_2017_basic2[i]->Fill(disc_ttbar_2017_basic2, myWeight);
    hist_disc_ttbar_2017_enhanced[i]->Fill(disc_ttbar_2017_enhanced, myWeight);
    //
    hist_disc_qcd_and_ttbar_2017_basic0[i]->Fill(disc_qcd_and_ttbar_2017_basic0, myWeight);
    hist_disc_qcd_and_ttbar_2017_basic1[i]->Fill(disc_qcd_and_ttbar_2017_basic1, myWeight);
    hist_disc_qcd_and_ttbar_2017_basic2[i]->Fill(disc_qcd_and_ttbar_2017_basic2, myWeight);
    hist_disc_qcd_and_ttbar_2017_enhanced[i]->Fill(disc_qcd_and_ttbar_2017_enhanced, myWeight);
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

  std::cout << "[INFO] Making stacked plots" << std::endl;
  //*******************************************************************************************
  //MR
  //*******************************************************************************************
  PlotDataAndStackedBkg( histMET, processLabels, color, true, "MET", Label);
  PlotDataAndStackedBkg( histNLeptons, processLabels, color, true, "NLeptons", Label);
  PlotDataAndStackedBkg( histNJetsHaveLeptons, processLabels, color, true, "NJetsHaveLeptons", Label);
  PlotDataAndStackedBkg( histJet1Mass, processLabels, color, true, "Jet1_Mass", Label);
  PlotDataAndStackedBkg( histJet1Pt, processLabels, color, true, "Jet1_Pt", Label);
  PlotDataAndStackedBkg( histJet1Eta, processLabels, color, true, "Jet1_Eta", Label);
  PlotDataAndStackedBkg( histJet1Phi, processLabels, color, true, "Jet1_Phi", Label);
  PlotDataAndStackedBkg( histJet1DDB, processLabels, color, true, "Jet1_DDB", Label);
  PlotDataAndStackedBkg( histJet1PNetXbb, processLabels, color, true, "Jet1_PNetXbb", Label);
  PlotDataAndStackedBkg( histJet1Tau3OverTau2, processLabels, color, true, "Jet1_Tau3OverTau2", Label);
  PlotDataAndStackedBkg( histJet2Mass, processLabels, color, true, "Jet2_Mass", Label);
  PlotDataAndStackedBkg( histJet2Pt, processLabels, color, true, "Jet2_Pt", Label);
  PlotDataAndStackedBkg( histJet2Eta, processLabels, color, true, "Jet2_Eta", Label);
  PlotDataAndStackedBkg( histJet2Phi, processLabels, color, true, "Jet2_Phi", Label);
  PlotDataAndStackedBkg( histJet2DDB, processLabels, color, true, "Jet2_DDB", Label);
  PlotDataAndStackedBkg( histJet2PNetXbb, processLabels, color, true, "Jet2_PNetXbb", Label);
  PlotDataAndStackedBkg( histJet2Tau3OverTau2, processLabels, color, true, "Jet2_Tau3OverTau2", Label);
  //
  PlotDataAndStackedBkg( histHH_Pt, processLabels, color, true, "HH_Pt", Label);
  PlotDataAndStackedBkg( histHH_Eta, processLabels, color, true, "HH_Eta", Label);
  PlotDataAndStackedBkg( histHH_Phi, processLabels, color, true, "HH_Phi", Label);
  PlotDataAndStackedBkg( histHH_Mass, processLabels, color, true, "HH_Mass", Label);
  PlotDataAndStackedBkg( histJet1PtOverMHH, processLabels, color, true, "Jet1PtOverMHH", Label);
  PlotDataAndStackedBkg( histJet2PtOverMHH, processLabels, color, true, "Jet2PtOverMHH", Label);
  PlotDataAndStackedBkg( histJet1PtOverMSD, processLabels, color, true, "Jet1PtOverMSD", Label);
  PlotDataAndStackedBkg( histJet2PtOverMSD, processLabels, color, true, "Jet2PtOverMSD", Label);
  PlotDataAndStackedBkg( histDeltaEta_J1J2, processLabels, color, true, "DeltaEta_J1J2", Label);
  PlotDataAndStackedBkg( histDeltaPhi_J1J2, processLabels, color, true, "DeltaPhi_J1J2", Label);
  PlotDataAndStackedBkg( histDeltaR_J1J2, processLabels, color, true, "DeltaR_J1J2", Label);
  PlotDataAndStackedBkg( histJet2PtOverJet1Pt, processLabels, color, true, "Jet2PtOverJet1Pt", Label);
  PlotDataAndStackedBkg( histJet2MSD_Over_Jet1MSD, processLabels, color, true, "Jet2MSD_Over_Jet1MSD", Label);
  //
  PlotDataAndStackedBkg( hist_disc_qcd_2017_basic0, processLabels, color, true, "disc_qcd_2017_basic0", Label);
  PlotDataAndStackedBkg( hist_disc_qcd_2017_basic1, processLabels, color, true, "disc_qcd_2017_basic1", Label);
  PlotDataAndStackedBkg( hist_disc_qcd_2017_basic2, processLabels, color, true, "disc_qcd_2017_basic2", Label);
  PlotDataAndStackedBkg( hist_disc_qcd_2017_enhanced, processLabels, color, true, "disc_qcd_2017_enhanced", Label);
  //
  PlotDataAndStackedBkg( hist_disc_ttbar_2017_basic0, processLabels, color, true, "disc_ttbar_2017_basic0", Label);
  PlotDataAndStackedBkg( hist_disc_ttbar_2017_basic1, processLabels, color, true, "disc_ttbar_2017_basic1", Label);
  PlotDataAndStackedBkg( hist_disc_ttbar_2017_basic2, processLabels, color, true, "disc_ttbar_2017_basic2", Label);
  PlotDataAndStackedBkg( hist_disc_ttbar_2017_enhanced, processLabels, color, true, "disc_ttbar_2017_enhanced", Label);
  //
  PlotDataAndStackedBkg( hist_disc_qcd_and_ttbar_2017_basic0, processLabels, color, true, "disc_qcd_and_ttbar_2017_basic0", Label);
  PlotDataAndStackedBkg( hist_disc_qcd_and_ttbar_2017_basic1, processLabels, color, true, "disc_qcd_and_ttbar_2017_basic1", Label);
  PlotDataAndStackedBkg( hist_disc_qcd_and_ttbar_2017_basic2, processLabels, color, true, "disc_qcd_and_ttbar_2017_basic2", Label);
  PlotDataAndStackedBkg( hist_disc_qcd_and_ttbar_2017_enhanced, processLabels, color, true, "disc_qcd_and_ttbar_2017_enhanced", Label);
  //--------------------------------------------------------------------------------------------------------------
  // Tables
  //==============================================================================================================
  std::cout << "For Luminosity = " << lumi << " pb^-1\n";

  std::cout << "Selected Event Yield \n";
  std::cout << "Data: " << dataYield << "\n";
  std::cout << "MC: " << MCYield << "\n";
  std::cout << "Signal: " << SignalYield << "\n";
  std::cout << "S over sqrt(B): " << SignalYield/sqrt(dataYield) << "\n";

  // //--------------------------------------------------------------------------------------------------------------
  // // Output
  // //==============================================================================================================
  TFile *file = TFile::Open(("HHTo4BPlots"+Label+".root").c_str(), "UPDATE");
  file->cd();

  for(int i=0; i<int(inputfiles.size()); i++) {
    file->WriteTObject(histJet1Mass[i], Form("histJet1Mass_%s",processLabels[i].c_str()), "WriteDelete");
    file->WriteTObject(histJet1Pt[i], Form("histJet1Pt_%s",processLabels[i].c_str()), "WriteDelete");
    file->WriteTObject(histJet1Eta[i], Form("histJet1Eta_%s",processLabels[i].c_str()), "WriteDelete");
    file->WriteTObject(histJet1Phi[i], Form("histJet1Phi_%s",processLabels[i].c_str()), "WriteDelete");
    file->WriteTObject(histJet2Mass[i], Form("histJet2Mass_%s",processLabels[i].c_str()), "WriteDelete");
    file->WriteTObject(histJet2Pt[i], Form("histJet2Pt_%s",processLabels[i].c_str()), "WriteDelete");
    file->WriteTObject(histJet2Eta[i], Form("histJet2Eta_%s",processLabels[i].c_str()), "WriteDelete");
    file->WriteTObject(histJet2Phi[i], Form("histJet2Phi_%s",processLabels[i].c_str()), "WriteDelete");
    file->WriteTObject(histNJetsHaveLeptons[i], Form("histNJetsHaveLeptons_%s",processLabels[i].c_str()), "WriteDelete");
    file->WriteTObject(histMET[i], Form("histMET_%s",processLabels[i].c_str()), "WriteDelete");
    //
    file->WriteTObject(histHH_Pt[i],   Form("histHH_Pt_%s",processLabels[i].c_str()), "WriteDelete");
    file->WriteTObject(histHH_Eta[i],  Form("histHH_Eta_%s",processLabels[i].c_str()), "WriteDelete");
    file->WriteTObject(histHH_Phi[i],  Form("histHH_Phi_%s",processLabels[i].c_str()), "WriteDelete");
    file->WriteTObject(histHH_Mass[i], Form("histHH_Mass_%s",processLabels[i].c_str()), "WriteDelete");
    file->WriteTObject(histJet1PtOverMHH[i], Form("histJet1PtOverMHH_%s",processLabels[i].c_str()), "WriteDelete");
    file->WriteTObject(histJet2PtOverMHH[i], Form("histJet2PtOverMHH_%s",processLabels[i].c_str()), "WriteDelete");
    file->WriteTObject(histJet1PtOverMSD[i], Form("histJet1PtOverMSD_%s",processLabels[i].c_str()), "WriteDelete");
    file->WriteTObject(histJet2PtOverMSD[i], Form("histJet2PtOverMSD_%s",processLabels[i].c_str()), "WriteDelete");
    file->WriteTObject(histDeltaEta_J1J2[i], Form("histDeltaEta_J1J2_%s",processLabels[i].c_str()), "WriteDelete");
    file->WriteTObject(histDeltaPhi_J1J2[i], Form("histDeltaPhi_J1J2_%s",processLabels[i].c_str()), "WriteDelete");
    file->WriteTObject(histDeltaR_J1J2[i], Form("histDeltaR_J1J2_%s",processLabels[i].c_str()), "WriteDelete");
    file->WriteTObject(histJet2PtOverJet1Pt[i], Form("histJet2PtOverJet1Pt_%s",processLabels[i].c_str()), "WriteDelete");
    file->WriteTObject(histJet2MSD_Over_Jet1MSD[i], Form("histJet2MSD_Over_Jet1MSD_%s",processLabels[i].c_str()), "WriteDelete");

  }

  file->Close();
  delete file;

}







void SelectHHTo4B_PNet( int option = 0) {


  std::vector<std::string> datafiles;
  std::vector<std::vector<std::string> > bkgfiles;
  std::vector<std::string> processLabels;
  std::vector<int> colors;
  std::vector<float> scaleFactors;

  std::vector<std::string> bkgfiles_ttbar;
  std::vector<std::string> bkgfiles_H;
  std::vector<std::string> bkgfiles_VH;
  std::vector<std::string> bkgfiles_ttH;
  std::vector<std::string> bkgfiles_qcd;
  std::vector<std::string> bkgfiles_HH;

  std::string datafile = "";
  std::string _year = "2017";
  //v2 : DDB selected SR
  //v3_TopTaggedJets : Top CR
  //v4 : PNetXbb selected SR
  //v5 : Top CR with qhu ntuples
  if( _year == "2016")
  {
    //datafiles.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2016/JetHT_2016_Mass30Skim_GoodLumi_BDTs.root");

    bkgfiles_ttbar.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2016/TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8_1pb_weighted_Mass30Skim_BDTs.root");
    bkgfiles_ttbar.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2016/TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8_1pb_weighted_Mass30Skim_BDTs.root");
    bkgfiles_H.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2016/GluGluHToBB_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8_1pb_weighted_Mass30Skim_BDTs.root");
    bkgfiles_H.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2016/VBFHToBB_M-125_13TeV_powheg_pythia8_weightfix-combined_1pb_weighted_Mass30Skim_BDTs.root");
    //bkgfiles_VH.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2016/WminusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8_1pb_weighted_Mass30Skim_BDTs.root");
    //bkgfiles_VH.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2016/WplusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8_1pb_weighted_Mass30Skim_BDTs.root");
    bkgfiles_VH.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2016/ZH_HToBB_ZToQQ_M125_13TeV_powheg_pythia8_1pb_weighted_Mass30Skim_BDTs.root");
    //  bkgfiles_VH.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2017/ggZH_HToBB_ZToQQ_M125_13TeV_powheg_pythia8_1pb_weighted_Mass30Skim_BDTs.root");
    bkgfiles_ttH.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2016/ttHTobb_M125_13TeV_powheg_pythia8_1pb_weighted_Mass30Skim_BDTs.root");

    bkgfiles_qcd.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2016/QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-combined_1pb_weighted_Mass30Skim_BDTs.root");
    bkgfiles_qcd.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2016/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-combined_1pb_weighted_Mass30Skim_BDTs.root");
    bkgfiles_qcd.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2016/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-combined_1pb_weighted_Mass30Skim_BDTs.root");
    bkgfiles_qcd.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2016/QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-combined_1pb_weighted_Mass30Skim_BDTs.root");
    bkgfiles_qcd.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2016/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-combined_1pb_weighted_Mass30Skim_BDTs.root");
    bkgfiles_qcd.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2016/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-combined_1pb_weighted_Mass30Skim_BDTs.root");
    bkgfiles_qcd.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2016/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-combined_1pb_weighted_Mass30Skim_BDTs.root");

    bkgfiles_HH.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2016/GluGluToHHTo4B_node_cHHH1_TuneCUETP8M1_PSWeights_13TeV-powheg-pythia8_1pb_weighted_Mass30Skim_BDTs.root");

  }
  else if( _year == "2017")
  {
    datafiles.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2017/JetHT_2017_Mass30Skim_GoodLumi_BDTs.root");

    bkgfiles_ttbar.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2017/TTToHadronic_TuneCP5_13TeV-powheg-pythia8_1pb_weighted_Mass30Skim_BDTs.root");
    bkgfiles_ttbar.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2017/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8_1pb_weighted_Mass30Skim_BDTs.root");
    bkgfiles_H.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2017/GluGluHToBB_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8_1pb_weighted_Mass30Skim_BDTs.root");
    bkgfiles_H.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2017/VBFHToBB_M-125_13TeV_powheg_pythia8_1pb_weighted_Mass30Skim_BDTs.root");
    bkgfiles_VH.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2017/WminusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8_1pb_weighted_Mass30Skim_BDTs.root");
    bkgfiles_VH.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2017/WplusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8_1pb_weighted_Mass30Skim_BDTs.root");
    bkgfiles_VH.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2017/ZH_HToBB_ZToQQ_M125_13TeV_powheg_pythia8_1pb_weighted_Mass30Skim_BDTs.root");
    //  bkgfiles_VH.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2017/ggZH_HToBB_ZToQQ_M125_13TeV_powheg_pythia8_1pb_weighted_Mass30Skim_BDTs.root");
    bkgfiles_ttH.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2017/ttHTobb_M125_TuneCP5_13TeV-powheg-pythia8_1pb_weighted_Mass30Skim_BDTs.root");

    bkgfiles_qcd.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2017/QCD_HT300to500_TuneCP5_13TeV-madgraph-pythia8_1pb_weighted_Mass30Skim_BDTs.root");
    bkgfiles_qcd.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2017/QCD_HT500to700_TuneCP5_13TeV-madgraph-pythia8_1pb_weighted_Mass30Skim_BDTs.root");
    bkgfiles_qcd.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2017/QCD_HT700to1000_TuneCP5_13TeV-madgraph-pythia8_1pb_weighted_Mass30Skim_BDTs.root");
    bkgfiles_qcd.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2017/QCD_HT1000to1500_TuneCP5_13TeV-madgraph-pythia8_1pb_weighted_Mass30Skim_BDTs.root");
    bkgfiles_qcd.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2017/QCD_HT1500to2000_TuneCP5_13TeV-madgraph-pythia8_1pb_weighted_Mass30Skim_BDTs.root");
    bkgfiles_qcd.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2017/QCD_HT2000toInf_TuneCP5_13TeV-madgraph-pythia8_1pb_weighted_Mass30Skim_BDTs.root");

    bkgfiles_HH.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2017/GluGluToHHTo4B_node_SM_1pb_weighted_Mass30Skim_BDTs.root");
  }
  else if( _year == "2018")
  {
    //datafiles.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2018/JetHT_2018_Mass30Skim_GoodLumi_BDTs.root");

    bkgfiles_ttbar.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2018/TTToHadronic_TuneCP5_13TeV-powheg-pythia8-combined_1pb_weighted_Mass30Skim_BDTs.root");
    bkgfiles_ttbar.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2018/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8-combined_1pb_weighted_Mass30Skim_BDTs.root");
    bkgfiles_H.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2018/GluGluHToBB_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8_1pb_weighted_Mass30Skim_BDTs.root");
    bkgfiles_H.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2018/VBFHToBB_M-125_13TeV_powheg_pythia8_weightfix_1pb_weighted_Mass30Skim_BDTs.root");
    bkgfiles_VH.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2018/WminusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8_1pb_weighted_Mass30Skim_BDTs.root");
    bkgfiles_VH.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2018/WplusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8_1pb_weighted_Mass30Skim_BDTs.root");
    bkgfiles_VH.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2018/ZH_HToBB_ZToQQ_M125_13TeV_powheg_pythia8_1pb_weighted_Mass30Skim_BDTs.root");
    //  bkgfiles_VH.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2017/ggZH_HToBB_ZToQQ_M125_13TeV_powheg_pythia8_1pb_weighted_Mass30Skim_BDTs.root");
    bkgfiles_ttH.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2018/ttHTobb_M125_TuneCP5_13TeV-powheg-pythia8_1pb_weighted_Mass30Skim_BDTs.root");

    bkgfiles_qcd.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2018/QCD_HT300to500_TuneCP5_13TeV-madgraphMLM-pythia8_1pb_weighted_Mass30Skim_BDTs.root");
    bkgfiles_qcd.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2018/QCD_HT500to700_TuneCP5_13TeV-madgraphMLM-pythia8_1pb_weighted_Mass30Skim_BDTs.root");
    bkgfiles_qcd.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2018/QCD_HT700to1000_TuneCP5_13TeV-madgraphMLM-pythia8_1pb_weighted_Mass30Skim_BDTs.root");
    bkgfiles_qcd.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2018/QCD_HT1000to1500_TuneCP5_13TeV-madgraphMLM-pythia8_1pb_weighted_Mass30Skim_BDTs.root");
    bkgfiles_qcd.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2018/QCD_HT1500to2000_TuneCP5_13TeV-madgraphMLM-pythia8_1pb_weighted_Mass30Skim_BDTs.root");
    bkgfiles_qcd.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2018/QCD_HT2000toInf_TuneCP5_13TeV-madgraphMLM-pythia8_1pb_weighted_Mass30Skim_BDTs.root");

    bkgfiles_HH.push_back("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2018/GluGluToHHTo4B_node_SM_1pb_weighted_Mass30Skim_BDTs.root");
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

  //double lumi = 40864 * 0.717;
  //double lumi = 40864 *0.64;
  double lumi = 0.0;
  if( _year == "2016") lumi = 35.922*1000.;
  else if( _year == "2017") lumi = 41.480*1000.;
  else if( _year == "2018") lumi = 59.741*1000.;


  //*********************************************************************
  //SR Selection
  //*********************************************************************
  std::cout << "[INFO] Into RunSelectHHTo4B" << std::endl;
  RunSelectHHTo4B(datafiles, bkgfiles,processLabels, colors, scaleFactors,lumi,"",0, _year);
  std::cout << "[INFO] Out of RunSelectHHTo4B" << std::endl;
  //*********************************************************************
  //TTBAR CR Selection
  //*********************************************************************
  //RunSelectHHTo4B(datafiles, bkgfiles,processLabels, colors, scaleFactors,lumi,"",20,"");

  //*********************************************************************
  //QCD CR Selection
  //*********************************************************************
  //RunSelectHHTo4B(datafiles, bkgfiles,processLabels, colors, scaleFactors,lumi,"",10,"");

}

int main(int argc, char** argv)
{
  SelectHHTo4B_PNet( 0 );
  return 0;
};


//**********************************
//E-Mu Yields :
//**********************************

//MuEG Triggers ( 30 - 20 )
// Data: 148
// MC: 156.16
