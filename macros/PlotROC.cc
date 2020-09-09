#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <TLatex.h>

const float lumi = 5;
//Axis
const float axisTitleSize = 0.06;
const float axisTitleOffset = .8;

const float axisTitleSizeRatioX   = 0.18;
const float axisLabelSizeRatioX   = 0.12;
const float axisTitleOffsetRatioX = 0.94;

const float axisTitleSizeRatioY   = 0.15;
const float axisLabelSizeRatioY   = 0.108;
const float axisTitleOffsetRatioY = 0.32;

//Margins
const float leftMargin   = 0.12;
const float rightMargin  = 0.05;
const float topMargin    = 0.07;
const float bottomMargin = 0.12;

//CMS STANDARD
TString CMSText = "CMS";
TString extraText   = "Preliminary";
//TString lumiText = "2.32 fb^{-1} (13 TeV)";
TString lumiText = "12.92 fb^{-1} (13 TeV)";

bool AddCMS( TCanvas* C );

int main(int argc, char** argv )
{
  //TFile* f_bkg    = new TFile("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2017/GluGluToHHTo4B_node_cHHH1_TuneCP5_PSWeights_13TeV-powheg-pythia8_1pb_weighted_Mass30Skim_BDTs.root", "READ");
  TFile* f_bkg    = new TFile("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2017/QCD_HT_ALL_TuneCP5_13TeV-madgraph-pythia8_1pb_weighted_Mass30Skim_BDTs.root", "READ");
  TTree* tree_bkg = (TTree*)f_bkg->Get("tree");

  float weight;
  float triggerEffWeight;
  float pileupWeight;

  float fatJet1Pt;
  float fatJet1MassSD;
  float fatJet1PNetXbb;
  float fatJet2Pt;
  float fatJet2MassSD;
  float fatJet2PNetXbb;

  float disc_qcd_2017_basic0;
  float disc_qcd_2017_basic1;
  float disc_qcd_2017_basic2;
  float disc_qcd_2017_enhanced;
  //
  float disc_ttbar_2017_basic0;
  float disc_ttbar_2017_basic1;
  float disc_ttbar_2017_basic2;
  float disc_ttbar_2017_enhanced;

  tree_bkg->SetBranchAddress("weight",&weight);

  tree_bkg->SetBranchAddress("triggerEffWeight",&triggerEffWeight);
  tree_bkg->SetBranchAddress("pileupWeight",&pileupWeight);
  tree_bkg->SetBranchAddress("fatJet1Pt",&fatJet1Pt);
  tree_bkg->SetBranchAddress("fatJet1MassSD",&fatJet1MassSD);
  tree_bkg->SetBranchAddress("fatJet1PNetXbb",&fatJet1PNetXbb);
  tree_bkg->SetBranchAddress("fatJet2Pt",&fatJet2Pt);
  tree_bkg->SetBranchAddress("fatJet2MassSD",&fatJet2MassSD);
  tree_bkg->SetBranchAddress("fatJet2PNetXbb",&fatJet2PNetXbb);
  tree_bkg->SetBranchAddress("disc_qcd_2017_basic0",&disc_qcd_2017_basic0);
  tree_bkg->SetBranchAddress("disc_qcd_2017_basic1",&disc_qcd_2017_basic1);
  tree_bkg->SetBranchAddress("disc_qcd_2017_basic2",&disc_qcd_2017_basic2);
  tree_bkg->SetBranchAddress("disc_qcd_2017_enhanced",&disc_qcd_2017_enhanced);
  tree_bkg->SetBranchAddress("disc_ttbar_2017_basic0",&disc_ttbar_2017_basic0);
  tree_bkg->SetBranchAddress("disc_ttbar_2017_basic1",&disc_ttbar_2017_basic1);
  tree_bkg->SetBranchAddress("disc_ttbar_2017_basic2",&disc_ttbar_2017_basic2);
  tree_bkg->SetBranchAddress("disc_ttbar_2017_enhanced",&disc_ttbar_2017_enhanced);


  const int n_bins = 1000;
  TH1F* h_disc_qcd_2017_basic0_bkg        = new TH1F("disc_qcd_2017_basic0_bkg", "disc_qcd_2017_basic0_bkg", n_bins, 0, 1);
  TH1F* h_disc_qcd_2017_basic0_bkg_pnet   = new TH1F("disc_qcd_2017_basic0_bkg_pnet", "disc_qcd_2017_basic0_bkg_pnet", n_bins, 0, 1);
  TH1F* h_disc_qcd_2017_basic1_bkg        = new TH1F("disc_qcd_2017_basic1_bkg", "disc_qcd_2017_basic1_bkg", n_bins, 0, 1);
  TH1F* h_disc_qcd_2017_basic1_bkg_pnet   = new TH1F("disc_qcd_2017_basic1_bkg_pnet", "disc_qcd_2017_basic1_bkg_pnet", n_bins, 0, 1);
  TH1F* h_disc_qcd_2017_basic2_bkg        = new TH1F("disc_qcd_2017_basic2_bkg", "disc_qcd_2017_basic2_bkg", n_bins, 0, 1);
  TH1F* h_disc_qcd_2017_enhanced_bkg      = new TH1F("disc_qcd_2017_enhanced_bkg", "disc_qcd_2017_enhanced_bkg", n_bins, 0, 1);

  double sum_weights                = 0.0;
  double sum_weights_pass_cut_based = 0.0;
  int nentries = tree_bkg->GetEntries();
  for(int i = 0; i < nentries; i++ )
  {
    tree_bkg->GetEntry(i);
    //double my_weight = weight * pileupWeight * triggerEffWeight;
    double my_weight = weight * triggerEffWeight;
    //std::cout << weight << " " << pileupWeight << " " << triggerEffWeight << std::endl;
    sum_weights += my_weight;
    if(  (fatJet1Pt > 250 && fatJet2Pt > 250)
      && (fatJet1Pt > 300 || fatJet2Pt > 300)
      && (fatJet1MassSD > 100 && fatJet1MassSD < 140)
      && (fatJet1PNetXbb > 0.975 && fatJet2PNetXbb > 0.975)
    ) sum_weights_pass_cut_based += my_weight;
    if(i%1000 == 0) std::cout << "entry # " << i << std::endl;
    //std::cout << "disc_qcd_2017_enhanced: " << disc_qcd_2017_enhanced << std::endl;
    h_disc_qcd_2017_basic0_bkg->Fill(disc_qcd_2017_basic0,my_weight);
    if( fatJet1PNetXbb > 0.975 && fatJet2PNetXbb > 0.975 ) h_disc_qcd_2017_basic0_bkg_pnet->Fill(disc_qcd_2017_basic0,my_weight);
    h_disc_qcd_2017_basic1_bkg->Fill(disc_qcd_2017_basic1,my_weight);
    if( fatJet2PNetXbb > 0.975 ) h_disc_qcd_2017_basic1_bkg_pnet->Fill(disc_qcd_2017_basic1,my_weight);
    h_disc_qcd_2017_basic2_bkg->Fill(disc_qcd_2017_basic2,my_weight);
    h_disc_qcd_2017_enhanced_bkg->Fill(disc_qcd_2017_enhanced,my_weight);
  }

  std::cout << "--> " << sum_weights << " " << sum_weights_pass_cut_based << std::endl;
  std::cout << "BKG eff cut-based: " << 100.*(sum_weights_pass_cut_based/sum_weights) << " %" << std::endl;




  //---------------------------
  //signal
  //---------------------------
  TFile* f_signal    = new TFile("/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2017/GluGluToHHTo4B_node_cHHH1_TuneCP5_PSWeights_13TeV-powheg-pythia8_1pb_weighted_Mass30Skim_BDTs.root", "READ");
  TTree* tree_signal = (TTree*)f_signal->Get("tree");

  tree_signal->SetBranchAddress("weight",&weight);

  tree_signal->SetBranchAddress("triggerEffWeight",&triggerEffWeight);
  tree_signal->SetBranchAddress("pileupWeight",&pileupWeight);
  tree_signal->SetBranchAddress("fatJet1Pt",&fatJet1Pt);
  tree_signal->SetBranchAddress("fatJet1MassSD",&fatJet1MassSD);
  tree_signal->SetBranchAddress("fatJet1PNetXbb",&fatJet1PNetXbb);
  tree_signal->SetBranchAddress("fatJet2Pt",&fatJet2Pt);
  tree_signal->SetBranchAddress("fatJet2MassSD",&fatJet2MassSD);
  tree_signal->SetBranchAddress("fatJet2PNetXbb",&fatJet2PNetXbb);
  tree_signal->SetBranchAddress("disc_qcd_2017_basic0",&disc_qcd_2017_basic0);
  tree_signal->SetBranchAddress("disc_qcd_2017_basic1",&disc_qcd_2017_basic1);
  tree_signal->SetBranchAddress("disc_qcd_2017_basic2",&disc_qcd_2017_basic2);
  tree_signal->SetBranchAddress("disc_qcd_2017_enhanced",&disc_qcd_2017_enhanced);
  tree_signal->SetBranchAddress("disc_ttbar_2017_basic0",&disc_ttbar_2017_basic0);
  tree_signal->SetBranchAddress("disc_ttbar_2017_basic1",&disc_ttbar_2017_basic1);
  tree_signal->SetBranchAddress("disc_ttbar_2017_basic2",&disc_ttbar_2017_basic2);
  tree_signal->SetBranchAddress("disc_ttbar_2017_enhanced",&disc_ttbar_2017_enhanced);

  TH1F* h_disc_qcd_2017_basic0_signal        = new TH1F("disc_qcd_2017_basic0_signal", "disc_qcd_2017_basic0_signal", n_bins, 0, 1);
  TH1F* h_disc_qcd_2017_basic0_signal_pnet   = new TH1F("disc_qcd_2017_basic0_signal_pnet", "disc_qcd_2017_basic0_signal_pnet", n_bins, 0, 1);
  TH1F* h_disc_qcd_2017_basic1_signal        = new TH1F("disc_qcd_2017_basic1_signal", "disc_qcd_2017_basic1_signal", n_bins, 0, 1);
  TH1F* h_disc_qcd_2017_basic1_signal_pnet   = new TH1F("disc_qcd_2017_basic1_signal_pnet", "disc_qcd_2017_basic1_signal_pnet", n_bins, 0, 1);
  TH1F* h_disc_qcd_2017_basic2_signal        = new TH1F("disc_qcd_2017_basic2_signal", "disc_qcd_2017_basic2_signal", n_bins, 0, 1);
  TH1F* h_disc_qcd_2017_enhanced_signal      = new TH1F("disc_qcd_2017_enhanced_signal", "disc_qcd_2017_enhanced_signal", n_bins, 0, 1);


  double sum_weights_signal                = 0.0;
  double sum_weights_pass_cut_based_signal = 0.0;
  nentries = tree_signal->GetEntries();
  for(int i = 0; i < nentries; i++ )
  {
    tree_signal->GetEntry(i);
    //double my_weight = weight * pileupWeight * triggerEffWeight;
    double my_weight = weight * triggerEffWeight;
    //std::cout << weight << " " << pileupWeight << " " << triggerEffWeight << std::endl;
    sum_weights_signal += my_weight;
    if(  (fatJet1Pt > 250 && fatJet2Pt > 250)
      && (fatJet1Pt > 300 || fatJet2Pt > 300)
      && (fatJet1MassSD > 100 && fatJet1MassSD < 140)
      && (fatJet1PNetXbb > 0.975 && fatJet2PNetXbb > 0.975)
    ) sum_weights_pass_cut_based_signal += my_weight;
    if(i%1000 == 0) std::cout << "entry # " << i << std::endl;
    //std::cout << "disc_qcd_2017_enhanced: " << disc_qcd_2017_enhanced << std::endl;
    h_disc_qcd_2017_basic0_signal->Fill(disc_qcd_2017_basic0,my_weight);
    if( fatJet1PNetXbb > 0.975 && fatJet2PNetXbb > 0.975 ) h_disc_qcd_2017_basic0_signal_pnet->Fill(disc_qcd_2017_basic0,my_weight);
    h_disc_qcd_2017_basic1_signal->Fill(disc_qcd_2017_basic1,my_weight);
    if( fatJet2PNetXbb > 0.975 ) h_disc_qcd_2017_basic1_signal_pnet->Fill(disc_qcd_2017_basic1,my_weight);
    h_disc_qcd_2017_basic2_signal->Fill(disc_qcd_2017_basic2,my_weight);
    h_disc_qcd_2017_enhanced_signal->Fill(disc_qcd_2017_enhanced,my_weight);
  }

  //std::cout << "--> " << sum_weights << " " << sum_weights_pass_cut_based << std::endl;
  double signal_eff = sum_weights_pass_cut_based_signal/sum_weights_signal;
  double bkg_eff    = sum_weights_pass_cut_based/sum_weights;
  std::cout << "BKG eff cut-based: "    << 100.*(sum_weights_pass_cut_based/sum_weights) << " %" << std::endl;
  std::cout << "signal eff cut-based: " << 100.*(sum_weights_pass_cut_based_signal/sum_weights_signal) << " %" << std::endl;

  //loop over discriminator histograms
  float eff_disc_qcd_2017_basic0_signal[n_bins];
  float eff_disc_qcd_2017_basic0_signal_pnet[n_bins];
  float eff_disc_qcd_2017_basic1_signal[n_bins];
  float eff_disc_qcd_2017_basic1_signal_pnet[n_bins];
  float eff_disc_qcd_2017_basic2_signal[n_bins];
  float eff_disc_qcd_2017_enhanced_signal[n_bins];

  float eff_disc_qcd_2017_basic0_bkg[n_bins];
  float eff_disc_qcd_2017_basic0_bkg_pnet[n_bins];
  float eff_disc_qcd_2017_basic1_bkg[n_bins];
  float eff_disc_qcd_2017_basic1_bkg_pnet[n_bins];
  float eff_disc_qcd_2017_basic2_bkg[n_bins];
  float eff_disc_qcd_2017_enhanced_bkg[n_bins];
  for ( unsigned int i = 1; i <= n_bins; i++ )
  {
    eff_disc_qcd_2017_basic0_signal[i-1]      = h_disc_qcd_2017_basic0_signal->Integral(i,n_bins)/h_disc_qcd_2017_basic0_signal->Integral();
    eff_disc_qcd_2017_basic0_signal_pnet[i-1] = h_disc_qcd_2017_basic0_signal_pnet->Integral(i,n_bins)/h_disc_qcd_2017_basic0_signal->Integral();
    eff_disc_qcd_2017_basic1_signal[i-1]      = h_disc_qcd_2017_basic1_signal->Integral(i,n_bins)/h_disc_qcd_2017_basic1_signal->Integral();
    eff_disc_qcd_2017_basic1_signal_pnet[i-1] = h_disc_qcd_2017_basic1_signal_pnet->Integral(i,n_bins)/h_disc_qcd_2017_basic1_signal->Integral();
    eff_disc_qcd_2017_basic2_signal[i-1]      = h_disc_qcd_2017_basic1_signal->Integral(i,n_bins)/h_disc_qcd_2017_basic2_signal->Integral();
    eff_disc_qcd_2017_enhanced_signal[i-1]    = h_disc_qcd_2017_enhanced_signal->Integral(i,n_bins)/h_disc_qcd_2017_enhanced_signal->Integral();


    eff_disc_qcd_2017_basic0_bkg[i-1]         = h_disc_qcd_2017_basic0_bkg->Integral(i,n_bins)/h_disc_qcd_2017_basic0_bkg->Integral();
    eff_disc_qcd_2017_basic0_bkg_pnet[i-1]    = h_disc_qcd_2017_basic0_bkg_pnet->Integral(i,n_bins)/h_disc_qcd_2017_basic0_bkg->Integral();
    eff_disc_qcd_2017_basic1_bkg[i-1]         = h_disc_qcd_2017_basic1_bkg->Integral(i,n_bins)/h_disc_qcd_2017_basic1_bkg->Integral();
    eff_disc_qcd_2017_basic1_bkg_pnet[i-1]    = h_disc_qcd_2017_basic1_bkg_pnet->Integral(i,n_bins)/h_disc_qcd_2017_basic1_bkg->Integral();
    eff_disc_qcd_2017_basic2_bkg[i-1]         = h_disc_qcd_2017_basic2_bkg->Integral(i,n_bins)/h_disc_qcd_2017_basic2_bkg->Integral();
    eff_disc_qcd_2017_enhanced_bkg[i-1]       = h_disc_qcd_2017_enhanced_bkg->Integral(i,n_bins)/h_disc_qcd_2017_enhanced_bkg->Integral();
    //std::cout << "signalEFF: " << eff_disc_qcd_2017_basic0_signal[i-1] << " bkgEFF: " << eff_disc_qcd_2017_basic0_bkg[i-1] << std::endl;
  }

  TGraph* roc_disc_qcd_2017_basic0   = new TGraph(n_bins,eff_disc_qcd_2017_basic0_bkg_pnet,eff_disc_qcd_2017_basic0_signal_pnet);
  TGraph* roc_disc_qcd_2017_basic1   = new TGraph(n_bins,eff_disc_qcd_2017_basic1_bkg_pnet,eff_disc_qcd_2017_basic1_signal_pnet);
  TGraph* roc_disc_qcd_2017_basic2   = new TGraph(n_bins,eff_disc_qcd_2017_basic2_bkg,eff_disc_qcd_2017_basic2_signal);
  TGraph* roc_disc_qcd_2017_enhanced = new TGraph(n_bins,eff_disc_qcd_2017_enhanced_bkg,eff_disc_qcd_2017_enhanced_signal);

  TGraph* cut_based = new TGraph(1);
  cut_based->SetPoint(1, bkg_eff, signal_eff);
  //TCanvas
  TCanvas* c = new TCanvas( "c", "c", 2119, 33, 800, 700 );
  c->SetHighLightColor(2);
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetBorderSize(2);
  c->SetLeftMargin( leftMargin );
  c->SetRightMargin( rightMargin );
  c->SetTopMargin( topMargin );
  c->SetBottomMargin( bottomMargin );
  c->SetFrameBorderMode(0);
  c->SetFrameBorderMode(0);

  roc_disc_qcd_2017_basic0->SetLineWidth(3);
  roc_disc_qcd_2017_basic0->SetLineStyle(2);

  roc_disc_qcd_2017_basic0->SetTitle("");
  roc_disc_qcd_2017_basic0->GetXaxis()->SetTitleSize(0.05);
  roc_disc_qcd_2017_basic0->GetXaxis()->SetTitle("Background efficiency");
  roc_disc_qcd_2017_basic0->GetYaxis()->SetTitleSize(0.05);

  roc_disc_qcd_2017_basic0->SetMaximum(1.1);
  roc_disc_qcd_2017_basic0->GetYaxis()->CenterTitle(kTRUE);
  roc_disc_qcd_2017_basic0->GetYaxis()->SetTitle("Signal efficiency");

  roc_disc_qcd_2017_basic1->SetLineWidth(3);
  roc_disc_qcd_2017_basic1->SetLineStyle(2);
  roc_disc_qcd_2017_basic1->SetLineColor(kViolet-2);

  roc_disc_qcd_2017_basic2->SetLineWidth(3);
  roc_disc_qcd_2017_basic2->SetLineStyle(2);
  roc_disc_qcd_2017_basic2->SetLineColor(kAzure+2);

  roc_disc_qcd_2017_enhanced->SetLineWidth(3);
  roc_disc_qcd_2017_enhanced->SetLineStyle(2);
  roc_disc_qcd_2017_enhanced->SetLineColor(kRed);

  cut_based->SetMarkerStyle(20);
  cut_based->SetMarkerColor(kPink-3);
  cut_based->SetMarkerSize(2);

  roc_disc_qcd_2017_basic0->Draw("AL");
  roc_disc_qcd_2017_basic0->GetYaxis()->SetLimits(0,1.1);
  roc_disc_qcd_2017_basic0->GetXaxis()->SetLimits(1e-5,1.0);
  roc_disc_qcd_2017_basic0->Draw("AL");
  roc_disc_qcd_2017_basic1->Draw("L");
  roc_disc_qcd_2017_basic2->Draw("L");
  roc_disc_qcd_2017_enhanced->Draw("L");
  cut_based->Draw("P");

  AddCMS(c);
  c->Update();
  c->SetLogx();
  c->SetGrid();
  c->SaveAs("roc_disc_qcd_2017_basic0.pdf");


  f_bkg->Close();
  f_signal->Close();
  return 0;
};

bool AddCMS( TCanvas* C )
{
  C->cd();
  float lumix = 0.955;
  float lumiy = 0.945;
  float lumifont = 42;

  float cmsx = 0.28;
  float cmsy = 0.875;
  float cmsTextFont   = 61;  // default is helvetic-bold
  float extrax = cmsx + 0.078;
  float extray = cmsy - 0.04;
  float extraTextFont = 52;  // default is helvetica-italics
  // ratio of "CMS" and extra text size
  float extraOverCmsTextSize  = 0.76;
  float cmsSize = 0.06;
  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);
  float extraTextSize = extraOverCmsTextSize*cmsSize;
  latex.SetTextFont(lumifont);
  latex.SetTextAlign(31);
  latex.SetTextSize(cmsSize);
  latex.DrawLatex(lumix, lumiy,lumiText);

  latex.SetTextFont(cmsTextFont);
  latex.SetTextAlign(31);
  latex.SetTextSize(cmsSize);
  latex.DrawLatex(cmsx, cmsy, CMSText);

  latex.SetTextFont(extraTextFont);
  latex.SetTextAlign(31);
  latex.SetTextSize(extraTextSize);
  latex.DrawLatex(extrax, extray, extraText);
  return true;
};
