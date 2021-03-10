
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <THStack.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TLatex.h>
#include <vector>
#include <map>
#include <iostream>

const Int_t NComponents = 10;
int color[NComponents] = {kRed, kGreen+2, kBlue, kViolet, kAzure+10, kBlack, kOrange+1, kGray, kBlack, kBlack};


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


//*************************************************************************************************
//Divide Hist
//*************************************************************************************************
void DivideHist(TH1 *ratio, TH1 *num, TH1 *den) {  
  for (UInt_t b=0; int(b)<num->GetXaxis()->GetNbins()+2; ++b) {
    if ( den->GetBinContent(b) > 1.0e-4 ) {
      cout << "Bin: " << b << " " << ratio->GetXaxis()->GetBinCenter(b) << " : " << num->GetBinContent(b) << " / " << den->GetBinContent(b) << " = " << num->GetBinContent(b) / den->GetBinContent(b) << "\n";
      ratio->SetBinContent(b,num->GetBinContent(b) / den->GetBinContent(b));    
      ratio->SetBinError(b, (num->GetBinContent(b) / den->GetBinContent(b))*sqrt( pow(num->GetBinError(b)/num->GetBinContent(b),2) + pow(den->GetBinError(b)/den->GetBinContent(b),2)));
    } else {
      ratio->SetBinContent(b,0);
      ratio->SetBinError(b,0);
    }
  }
}




void DoComputePileupWeights( string targetPileupFilename, string MCPileupFilename, string MCLabel, string year, string outputfile) {

  
  TFile *TargetPileupFile = new TFile( targetPileupFilename.c_str() , "READ");
  TH1D *TargetPileupDistribution = (TH1D*)TargetPileupFile->Get("pileup");
  NormalizeHist(TargetPileupDistribution);
  
  TFile *MCPileupFile = new TFile( MCPileupFilename.c_str() , "READ");
  TH1F *MCPileupDistribution = (TH1F*)MCPileupFile->Get("PUMean");
  NormalizeHist(MCPileupDistribution);

  TH1F *PileupWeightHist = (TH1F*)MCPileupDistribution->Clone(Form("PUWeight_%s_%s",MCLabel.c_str(), year.c_str()));
  DivideHist( PileupWeightHist , TargetPileupDistribution, MCPileupDistribution);

  TFile *outputFile = new TFile( outputfile.c_str(), "UPDATE");
  outputFile->WriteTObject(PileupWeightHist, Form("PUWeight_%s_%s",MCLabel.c_str(),year.c_str()), "WriteDelete");

  outputFile->Close();
  MCPileupFile->Close();
  TargetPileupFile->Close();


 }
 
void ComputePileupWeights() {

  
  //2016 sample
  vector<string> MCSamples_2016;
  vector<string> MCPileupFiles_2016;

  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/GluGluHToBB_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/GluGluToHHTo4B_node_SM_13TeV-madgraph.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/GluGluToHHTo4B_node_cHHH0_TuneCUETP8M1_PSWeights_13TeV-powheg-pythia8.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/GluGluToHHTo4B_node_cHHH1_TuneCUETP8M1_PSWeights_13TeV-powheg-pythia8.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/GluGluToHHTo4B_node_cHHH2p45_TuneCUETP8M1_PSWeights_13TeV-powheg-pythia8.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/GluGluToHHTo4B_node_cHHH5_TuneCUETP8M1_PSWeights_13TeV-powheg-pythia8.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-combined.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-combined.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-combined.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-combined.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-combined.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-combined.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-combined.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/VBFHHTo4B_CV_1_C2V_1_C3_1_13TeV-madgraph.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/VBFHHTo4B_CV_0_5_C2V_1_C3_1_13TeV-madgraph.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/VBFHHTo4B_CV_1_5_C2V_1_C3_1_13TeV-madgraph.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/VBFHHTo4B_CV_1_C2V_1_C3_0_13TeV-madgraph.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/VBFHHTo4B_CV_1_C2V_1_C3_2_13TeV-madgraph.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/VBFHHTo4B_CV_1_C2V_2_C3_1_13TeV-madgraph.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/VBFHToBB_M-125_13TeV_powheg_pythia8_weightfix-combined.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/ZH_HToBB_ZToQQ_M125_13TeV_powheg_pythia8.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/ttHTobb_M125_13TeV_powheg_pythia8.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/ggZH_HToBB_ZToQQ_M125_13TeV_powheg_pythia8.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/WminusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/WplusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/WW_TuneCUETP8M1_13TeV-pythia8-combined.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/WZ_TuneCUETP8M1_13TeV-pythia8-combined.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/ZZ_TuneCUETP8M1_13TeV-pythia8-combined.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/WJetsToQQ_HT400to600_qc19_3j_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/WJetsToQQ_HT600to800_qc19_3j_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/WJetsToQQ_HT-800toInf_qc19_3j_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/ZJetsToQQ_HT400to600_qc19_4j_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/ZJetsToQQ_HT600to800_qc19_4j_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/ZJetsToQQ_HT-800toInf_qc19_4j_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/ST_tW_top_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/WJetsToLNu_Pt-100To250_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8-combined.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/WJetsToLNu_Pt-250To400_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8-combined.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/WJetsToLNu_Pt-400To600_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8-combined.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/WJetsToLNu_Pt-600ToInf_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8-combined.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/GJets_DR-0p4_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/GJets_DR-0p4_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/GJets_DR-0p4_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/GJets_DR-0p4_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/GJets_DR-0p4_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/TT_Mtt-1000toInf_TuneCUETP8M2T4_13TeV-powheg-pythia8.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/TT_Mtt-700to1000_TuneCUETP8M2T4_13TeV-powheg-pythia8.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/VBF_HH_CV_0_5_C2V_1_C3_1_dipoleRecoilOff-TuneCUETP8M1_PSweights_13TeV-madgraph-pythia8.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/VBF_HH_CV_1_5_C2V_1_C3_1_dipoleRecoilOff-TuneCUETP8M1_PSweights_13TeV-madgraph-pythia8.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/VBF_HH_CV_1_C2V_0_C3_1_dipoleRecoilOff-TuneCUETP8M1_PSweights_13TeV-madgraph-pythia8.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/VBF_HH_CV_1_C2V_1_C3_0_dipoleRecoilOff-TuneCUETP8M1_PSweights_13TeV-madgraph-pythia8.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/VBF_HH_CV_1_C2V_1_C3_1_dipoleRecoilOff-TuneCUETP8M1_PSweights_13TeV-madgraph-pythia8.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/VBF_HH_CV_1_C2V_1_C3_2_dipoleRecoilOff-TuneCUETP8M1_PSweights_13TeV-madgraph-pythia8.root");
  MCPileupFiles_2016.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2016/VBF_HH_CV_1_C2V_2_C3_1_dipoleRecoilOff-TuneCUETP8M1_PSweights_13TeV-madgraph-pythia8.root");



  MCSamples_2016.push_back("GluGluHToBB_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8");
  MCSamples_2016.push_back("GluGluToHHTo4B_node_SM_13TeV-madgraph");
  MCSamples_2016.push_back("GluGluToHHTo4B_node_cHHH0_TuneCUETP8M1_PSWeights_13TeV-powheg-pythia8");
  MCSamples_2016.push_back("GluGluToHHTo4B_node_cHHH1_TuneCUETP8M1_PSWeights_13TeV-powheg-pythia8");
  MCSamples_2016.push_back("GluGluToHHTo4B_node_cHHH2p45_TuneCUETP8M1_PSWeights_13TeV-powheg-pythia8");
  MCSamples_2016.push_back("GluGluToHHTo4B_node_cHHH5_TuneCUETP8M1_PSWeights_13TeV-powheg-pythia8");
  MCSamples_2016.push_back("QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-combined");
  MCSamples_2016.push_back("QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-combined");
  MCSamples_2016.push_back("QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-combined");
  MCSamples_2016.push_back("QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-combined");
  MCSamples_2016.push_back("QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-combined");
  MCSamples_2016.push_back("QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-combined");
  MCSamples_2016.push_back("QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-combined");
  MCSamples_2016.push_back("TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8");
  MCSamples_2016.push_back("TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8");
  MCSamples_2016.push_back("TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8");
  MCSamples_2016.push_back("VBFHHTo4B_CV_1_C2V_1_C3_1_13TeV-madgraph");
  MCSamples_2016.push_back("VBFHHTo4B_CV_0_5_C2V_1_C3_1_13TeV-madgraph");
  MCSamples_2016.push_back("VBFHHTo4B_CV_1_5_C2V_1_C3_1_13TeV-madgraph");
  MCSamples_2016.push_back("VBFHHTo4B_CV_1_C2V_1_C3_0_13TeV-madgraph");
  MCSamples_2016.push_back("VBFHHTo4B_CV_1_C2V_1_C3_2_13TeV-madgraph");
  MCSamples_2016.push_back("VBFHHTo4B_CV_1_C2V_2_C3_1_13TeV-madgraph");
  MCSamples_2016.push_back("VBFHToBB_M-125_13TeV_powheg_pythia8_weightfix-combined");
  MCSamples_2016.push_back("ZH_HToBB_ZToQQ_M125_13TeV_powheg_pythia8");
  MCSamples_2016.push_back("ttHTobb_M125_13TeV_powheg_pythia8");
  MCSamples_2016.push_back("ggZH_HToBB_ZToQQ_M125_13TeV_powheg_pythia8");
  MCSamples_2016.push_back("WminusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8");
  MCSamples_2016.push_back("WplusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8");
  MCSamples_2016.push_back("WW_TuneCUETP8M1_13TeV-pythia8-combined");
  MCSamples_2016.push_back("WZ_TuneCUETP8M1_13TeV-pythia8-combined");
  MCSamples_2016.push_back("ZZ_TuneCUETP8M1_13TeV-pythia8-combined");
  MCSamples_2016.push_back("WJetsToQQ_HT400to600_qc19_3j_TuneCUETP8M1_13TeV-madgraphMLM-pythia8");
  MCSamples_2016.push_back("WJetsToQQ_HT600to800_qc19_3j_TuneCUETP8M1_13TeV-madgraphMLM-pythia8");
  MCSamples_2016.push_back("WJetsToQQ_HT-800toInf_qc19_3j_TuneCUETP8M1_13TeV-madgraphMLM-pythia8");
  MCSamples_2016.push_back("ZJetsToQQ_HT400to600_qc19_4j_TuneCUETP8M1_13TeV-madgraphMLM-pythia8");
  MCSamples_2016.push_back("ZJetsToQQ_HT600to800_qc19_4j_TuneCUETP8M1_13TeV-madgraphMLM-pythia8");
  MCSamples_2016.push_back("ZJetsToQQ_HT-800toInf_qc19_4j_TuneCUETP8M1_13TeV-madgraphMLM-pythia8");
  MCSamples_2016.push_back("ST_tW_top_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8");
  MCSamples_2016.push_back("ST_tW_antitop_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8");
  MCSamples_2016.push_back("WJetsToLNu_Pt-100To250_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8-combined");
  MCSamples_2016.push_back("WJetsToLNu_Pt-250To400_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8-combined");
  MCSamples_2016.push_back("WJetsToLNu_Pt-400To600_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8-combined");
  MCSamples_2016.push_back("WJetsToLNu_Pt-600ToInf_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8-combined");
  MCSamples_2016.push_back("GJets_DR-0p4_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8");
  MCSamples_2016.push_back("GJets_DR-0p4_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8");
  MCSamples_2016.push_back("GJets_DR-0p4_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8");
  MCSamples_2016.push_back("GJets_DR-0p4_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8");
  MCSamples_2016.push_back("GJets_DR-0p4_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8");
  MCSamples_2016.push_back("TT_Mtt-1000toInf_TuneCUETP8M2T4_13TeV-powheg-pythia8");
  MCSamples_2016.push_back("TT_Mtt-700to1000_TuneCUETP8M2T4_13TeV-powheg-pythia8");
  MCSamples_2016.push_back("VBF_HH_CV_0_5_C2V_1_C3_1_dipoleRecoilOff-TuneCUETP8M1_PSweights_13TeV-madgraph-pythia8");
  MCSamples_2016.push_back("VBF_HH_CV_1_5_C2V_1_C3_1_dipoleRecoilOff-TuneCUETP8M1_PSweights_13TeV-madgraph-pythia8");
  MCSamples_2016.push_back("VBF_HH_CV_1_C2V_0_C3_1_dipoleRecoilOff-TuneCUETP8M1_PSweights_13TeV-madgraph-pythia8");
  MCSamples_2016.push_back("VBF_HH_CV_1_C2V_1_C3_0_dipoleRecoilOff-TuneCUETP8M1_PSweights_13TeV-madgraph-pythia8");
  MCSamples_2016.push_back("VBF_HH_CV_1_C2V_1_C3_1_dipoleRecoilOff-TuneCUETP8M1_PSweights_13TeV-madgraph-pythia8");
  MCSamples_2016.push_back("VBF_HH_CV_1_C2V_1_C3_2_dipoleRecoilOff-TuneCUETP8M1_PSweights_13TeV-madgraph-pythia8");
  MCSamples_2016.push_back("VBF_HH_CV_1_C2V_2_C3_1_dipoleRecoilOff-TuneCUETP8M1_PSweights_13TeV-madgraph-pythia8");

 
  //2017 sample
  vector<string> MCSamples_2017;
  vector<string> MCPileupFiles_2017;
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/GluGluHToBB_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/GluGluToHHTo4B_node_SM.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/QCD_HT1000to1500_TuneCP5_13TeV-madgraph-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/QCD_HT1500to2000_TuneCP5_13TeV-madgraph-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/QCD_HT2000toInf_TuneCP5_13TeV-madgraph-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/QCD_HT200to300_TuneCP5_13TeV-madgraph-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/QCD_HT300to500_TuneCP5_13TeV-madgraph-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/QCD_HT500to700_TuneCP5_13TeV-madgraph-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/QCD_HT700to1000_TuneCP5_13TeV-madgraph-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/TTToHadronic_TuneCP5_13TeV-powheg-pythia8-combined.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8-combined.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/VBFHHTo4B_CV_1_C2V_1_C3_1.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/VBFHHTo4B_CV_1_5_C2V_1_C3_1_13TeV-madgraph.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/VBFHHTo4B_CV_1_C2V_1_C3_0_13TeV-madgraph.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/VBFHHTo4B_CV_1_C2V_1_C3_2_13TeV-madgraph.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/VBFHHTo4B_CV_1_C2V_2_C3_1_13TeV-madgraph.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/VBFHToBB_M-125_13TeV_powheg_pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/WminusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/WplusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/ZH_HToBB_ZToQQ_M125_13TeV_powheg_pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/ttHTobb_M125_TuneCP5_13TeV-powheg-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/GluGluToHHTo4B_node_cHHH0_TuneCP5_PSWeights_13TeV-powheg-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/GluGluToHHTo4B_node_cHHH1_TuneCP5_PSWeights_13TeV-powheg-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/GluGluToHHTo4B_node_cHHH2p45_TuneCP5_PSWeights_13TeV-powheg-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/GluGluToHHTo4B_node_cHHH5_TuneCP5_PSWeights_13TeV-powheg-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/WW_TuneCP5_13TeV-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/WZ_TuneCP5_13TeV-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/ZZ_TuneCP5_13TeV-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/WJetsToQQ_HT400to600_qc19_3j_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/WJetsToQQ_HT600to800_qc19_3j_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/WJetsToQQ_HT-800toInf_qc19_3j_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/ZJetsToQQ_HT400to600_qc19_4j_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/ZJetsToQQ_HT600to800_qc19_4j_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/ZJetsToQQ_HT-800toInf_qc19_4j_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/ST_tW_top_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/WJetsToLNu_Pt-100To250_TuneCP5_13TeV-amcatnloFXFX-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/WJetsToLNu_Pt-250To400_TuneCP5_13TeV-amcatnloFXFX-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/WJetsToLNu_Pt-400To600_TuneCP5_13TeV-amcatnloFXFX-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/WJetsToLNu_Pt-50To100_TuneCP5_13TeV-amcatnloFXFX-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/WJetsToLNu_Pt-600ToInf_TuneCP5_13TeV-amcatnloFXFX-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/GJets_DR-0p4_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/GJets_DR-0p4_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/GJets_DR-0p4_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/GJets_DR-0p4_HT-600ToInf_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/TT_Mtt-1000toInf_TuneCP5_PSweights_13TeV-powheg-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/TT_Mtt-700to1000_TuneCP5_PSweights_13TeV-powheg-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/VBF_HH_CV_0_5_C2V_1_C3_1_dipoleRecoilOff-TuneCP5_PSweights_13TeV-madgraph-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/VBF_HH_CV_1_5_C2V_1_C3_1_dipoleRecoilOff-TuneCP5_PSweights_13TeV-madgraph-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/VBF_HH_CV_1_C2V_0_C3_1_dipoleRecoilOff-TuneCP5_PSweights_13TeV-madgraph-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/VBF_HH_CV_1_C2V_1_C3_0_dipoleRecoilOff-TuneCP5_PSweights_13TeV-madgraph-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/VBF_HH_CV_1_C2V_1_C3_1_dipoleRecoilOff-TuneCP5_PSweights_13TeV-madgraph-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/VBF_HH_CV_1_C2V_1_C3_2_dipoleRecoilOff-TuneCP5_PSweights_13TeV-madgraph-pythia8.root");
  MCPileupFiles_2017.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2017/VBF_HH_CV_1_C2V_2_C3_1_dipoleRecoilOff-TuneCP5_PSweights_13TeV-madgraph-pythia8.root");

  MCSamples_2017.push_back("GluGluHToBB_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8");
  MCSamples_2017.push_back("GluGluToHHTo4B_node_SM");
  MCSamples_2017.push_back("QCD_HT1000to1500_TuneCP5_13TeV-madgraph-pythia8");
  MCSamples_2017.push_back("QCD_HT1500to2000_TuneCP5_13TeV-madgraph-pythia8");
  MCSamples_2017.push_back("QCD_HT2000toInf_TuneCP5_13TeV-madgraph-pythia8");
  MCSamples_2017.push_back("QCD_HT200to300_TuneCP5_13TeV-madgraph-pythia8");
  MCSamples_2017.push_back("QCD_HT300to500_TuneCP5_13TeV-madgraph-pythia8");
  MCSamples_2017.push_back("QCD_HT500to700_TuneCP5_13TeV-madgraph-pythia8");
  MCSamples_2017.push_back("QCD_HT700to1000_TuneCP5_13TeV-madgraph-pythia8");
  MCSamples_2017.push_back("TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8");
  MCSamples_2017.push_back("TTToHadronic_TuneCP5_13TeV-powheg-pythia8-combined");
  MCSamples_2017.push_back("TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8-combined");
  MCSamples_2017.push_back("VBFHHTo4B_CV_1_C2V_1_C3_1");
  MCSamples_2017.push_back("VBFHHTo4B_CV_1_5_C2V_1_C3_1_13TeV-madgraph");
  MCSamples_2017.push_back("VBFHHTo4B_CV_1_C2V_1_C3_0_13TeV-madgraph");
  MCSamples_2017.push_back("VBFHHTo4B_CV_1_C2V_1_C3_2_13TeV-madgraph");
  MCSamples_2017.push_back("VBFHHTo4B_CV_1_C2V_2_C3_1_13TeV-madgraph");
  MCSamples_2017.push_back("VBFHToBB_M-125_13TeV_powheg_pythia8");
  MCSamples_2017.push_back("WminusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8");
  MCSamples_2017.push_back("WplusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8");
  MCSamples_2017.push_back("ZH_HToBB_ZToQQ_M125_13TeV_powheg_pythia8");
  MCSamples_2017.push_back("ttHTobb_M125_TuneCP5_13TeV-powheg-pythia8");
  MCSamples_2017.push_back("GluGluToHHTo4B_node_cHHH0_TuneCP5_PSWeights_13TeV-powheg-pythia8");
  MCSamples_2017.push_back("GluGluToHHTo4B_node_cHHH1_TuneCP5_PSWeights_13TeV-powheg-pythia8");
  MCSamples_2017.push_back("GluGluToHHTo4B_node_cHHH2p45_TuneCP5_PSWeights_13TeV-powheg-pythia8");
  MCSamples_2017.push_back("GluGluToHHTo4B_node_cHHH5_TuneCP5_PSWeights_13TeV-powheg-pythia8");
  MCSamples_2017.push_back("WW_TuneCP5_13TeV-pythia8");
  MCSamples_2017.push_back("WZ_TuneCP5_13TeV-pythia8");
  MCSamples_2017.push_back("ZZ_TuneCP5_13TeV-pythia8");
  MCSamples_2017.push_back("WJetsToQQ_HT400to600_qc19_3j_TuneCP5_13TeV-madgraphMLM-pythia8");
  MCSamples_2017.push_back("WJetsToQQ_HT600to800_qc19_3j_TuneCP5_13TeV-madgraphMLM-pythia8");
  MCSamples_2017.push_back("WJetsToQQ_HT-800toInf_qc19_3j_TuneCP5_13TeV-madgraphMLM-pythia8");
  MCSamples_2017.push_back("ZJetsToQQ_HT400to600_qc19_4j_TuneCP5_13TeV-madgraphMLM-pythia8");
  MCSamples_2017.push_back("ZJetsToQQ_HT600to800_qc19_4j_TuneCP5_13TeV-madgraphMLM-pythia8");
  MCSamples_2017.push_back("ZJetsToQQ_HT-800toInf_qc19_4j_TuneCP5_13TeV-madgraphMLM-pythia8");
  MCSamples_2017.push_back("ST_tW_top_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8");
  MCSamples_2017.push_back("ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8");
  MCSamples_2017.push_back("ST_tW_antitop_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8");
  MCSamples_2017.push_back("ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8");
  MCSamples_2017.push_back("WJetsToLNu_Pt-100To250_TuneCP5_13TeV-amcatnloFXFX-pythia8");
  MCSamples_2017.push_back("WJetsToLNu_Pt-250To400_TuneCP5_13TeV-amcatnloFXFX-pythia8");
  MCSamples_2017.push_back("WJetsToLNu_Pt-400To600_TuneCP5_13TeV-amcatnloFXFX-pythia8");
  MCSamples_2017.push_back("WJetsToLNu_Pt-50To100_TuneCP5_13TeV-amcatnloFXFX-pythia8");
  MCSamples_2017.push_back("WJetsToLNu_Pt-600ToInf_TuneCP5_13TeV-amcatnloFXFX-pythia8");
  MCSamples_2017.push_back("GJets_DR-0p4_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8");
  MCSamples_2017.push_back("GJets_DR-0p4_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8");
  MCSamples_2017.push_back("GJets_DR-0p4_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8");
  MCSamples_2017.push_back("GJets_DR-0p4_HT-600ToInf_TuneCP5_13TeV-madgraphMLM-pythia8");
  MCSamples_2017.push_back("TT_Mtt-1000toInf_TuneCP5_PSweights_13TeV-powheg-pythia8");
  MCSamples_2017.push_back("TT_Mtt-700to1000_TuneCP5_PSweights_13TeV-powheg-pythia8");
  MCSamples_2017.push_back("VBF_HH_CV_0_5_C2V_1_C3_1_dipoleRecoilOff-TuneCP5_PSweights_13TeV-madgraph-pythia8");
  MCSamples_2017.push_back("VBF_HH_CV_1_5_C2V_1_C3_1_dipoleRecoilOff-TuneCP5_PSweights_13TeV-madgraph-pythia8");
  MCSamples_2017.push_back("VBF_HH_CV_1_C2V_0_C3_1_dipoleRecoilOff-TuneCP5_PSweights_13TeV-madgraph-pythia8");
  MCSamples_2017.push_back("VBF_HH_CV_1_C2V_1_C3_0_dipoleRecoilOff-TuneCP5_PSweights_13TeV-madgraph-pythia8");
  MCSamples_2017.push_back("VBF_HH_CV_1_C2V_1_C3_1_dipoleRecoilOff-TuneCP5_PSweights_13TeV-madgraph-pythia8");
  MCSamples_2017.push_back("VBF_HH_CV_1_C2V_1_C3_2_dipoleRecoilOff-TuneCP5_PSweights_13TeV-madgraph-pythia8");
  MCSamples_2017.push_back("VBF_HH_CV_1_C2V_2_C3_1_dipoleRecoilOff-TuneCP5_PSweights_13TeV-madgraph-pythia8");



  //2018 sample
  vector<string> MCSamples_2018;
  vector<string> MCPileupFiles_2018;


  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/GluGluHToBB_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/GluGluToHHTo4B_node_SM_TuneCP5_PSWeights_13TeV-madgraph-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/QCD_HT1000to1500_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/QCD_HT1500to2000_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/QCD_HT2000toInf_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/QCD_HT200to300_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/QCD_HT300to500_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/QCD_HT500to700_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/QCD_HT700to1000_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/TTToHadronic_TuneCP5_13TeV-powheg-pythia8-combined.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8-combined.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/VBFHHTo4B_CV_1_C2V_1_C3_1_TuneCP5_PSWeights_13TeV-madgraph-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/VBFHHTo4B_CV_0_5_C2V_1_C3_1_TuneCP5_PSWeights_13TeV-madgraph-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/VBFHHTo4B_CV_1_5_C2V_1_C3_1_TuneCP5_PSWeights_13TeV-madgraph-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/VBFHHTo4B_CV_1_C2V_1_C3_0_TuneCP5_PSWeights_13TeV-madgraph-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/VBFHHTo4B_CV_1_C2V_1_C3_2_TuneCP5_PSWeights_13TeV-madgraph-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/VBFHHTo4B_CV_1_C2V_2_C3_1_TuneCP5_PSWeights_13TeV-madgraph-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/VBFHToBB_M-125_13TeV_powheg_pythia8_weightfix.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/WminusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/WplusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/ZH_HToBB_ZToQQ_M125_13TeV_powheg_pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/ttHTobb_M125_TuneCP5_13TeV-powheg-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/GluGluToHHTo4B_node_cHHH0_TuneCP5_PSWeights_13TeV-powheg-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/GluGluToHHTo4B_node_cHHH1_TuneCP5_PSWeights_13TeV-powheg-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/GluGluToHHTo4B_node_cHHH2p45_TuneCP5_PSWeights_13TeV-powheg-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/GluGluToHHTo4B_node_cHHH5_TuneCP5_PSWeights_13TeV-powheg-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/WW_TuneCP5_13TeV-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/WZ_TuneCP5_13TeV-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/ZZ_TuneCP5_13TeV-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/WJetsToQQ_HT400to600_qc19_3j_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/WJetsToQQ_HT600to800_qc19_3j_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/WJetsToQQ_HT-800toInf_qc19_3j_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/ZJetsToQQ_HT400to600_qc19_4j_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/ZJetsToQQ_HT600to800_qc19_4j_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/ZJetsToQQ_HT-800toInf_qc19_4j_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/WJetsToLNu_Pt-100To250_TuneCP5_13TeV-amcatnloFXFX-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/WJetsToLNu_Pt-250To400_TuneCP5_13TeV-amcatnloFXFX-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/WJetsToLNu_Pt-400To600_TuneCP5_13TeV-amcatnloFXFX-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/WJetsToLNu_Pt-50To100_TuneCP5_13TeV-amcatnloFXFX-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/WJetsToLNu_Pt-600ToInf_TuneCP5_13TeV-amcatnloFXFX-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/GJets_DR-0p4_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/GJets_DR-0p4_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/GJets_DR-0p4_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/GJets_DR-0p4_HT-600ToInf_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/TT_Mtt-1000toInf_TuneCP5_13TeV-powheg-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/TT_Mtt-700to1000_TuneCP5_13TeV-powheg-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/VBF_HH_CV_0_5_C2V_1_C3_1_dipoleRecoilOff-TuneCP5_PSweights_13TeV-madgraph-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/VBF_HH_CV_1_5_C2V_1_C3_1_dipoleRecoilOff-TuneCP5_PSweights_13TeV-madgraph-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/VBF_HH_CV_1_C2V_0_C3_1_dipoleRecoilOff-TuneCP5_PSweights_13TeV-madgraph-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/VBF_HH_CV_1_C2V_1_C3_0_dipoleRecoilOff-TuneCP5_PSweights_13TeV-madgraph-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/VBF_HH_CV_1_C2V_1_C3_1_dipoleRecoilOff-TuneCP5_PSweights_13TeV-madgraph-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/VBF_HH_CV_1_C2V_1_C3_2_dipoleRecoilOff-TuneCP5_PSweights_13TeV-madgraph-pythia8.root");
  MCPileupFiles_2018.push_back("/eos/cms/store/group/phys_susy/razor/Run2Analysis/HH/MakeMCPileupDistribution/v1/nano/v1/combined/2018/VBF_HH_CV_1_C2V_2_C3_1_dipoleRecoilOff-TuneCP5_PSweights_13TeV-madgraph-pythia8.root");



  MCSamples_2018.push_back("GluGluHToBB_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8");
  MCSamples_2018.push_back("GluGluToHHTo4B_node_SM_TuneCP5_PSWeights_13TeV-madgraph-pythia8");
  MCSamples_2018.push_back("QCD_HT1000to1500_TuneCP5_13TeV-madgraphMLM-pythia8");
  MCSamples_2018.push_back("QCD_HT1500to2000_TuneCP5_13TeV-madgraphMLM-pythia8");
  MCSamples_2018.push_back("QCD_HT2000toInf_TuneCP5_13TeV-madgraphMLM-pythia8");
  MCSamples_2018.push_back("QCD_HT200to300_TuneCP5_13TeV-madgraphMLM-pythia8");
  MCSamples_2018.push_back("QCD_HT300to500_TuneCP5_13TeV-madgraphMLM-pythia8");
  MCSamples_2018.push_back("QCD_HT500to700_TuneCP5_13TeV-madgraphMLM-pythia8");
  MCSamples_2018.push_back("QCD_HT700to1000_TuneCP5_13TeV-madgraphMLM-pythia8");
  MCSamples_2018.push_back("TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8");
  MCSamples_2018.push_back("TTToHadronic_TuneCP5_13TeV-powheg-pythia8-combined");
  MCSamples_2018.push_back("TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8-combined");
  MCSamples_2018.push_back("VBFHHTo4B_CV_1_C2V_1_C3_1_TuneCP5_PSWeights_13TeV-madgraph-pythia8");
  MCSamples_2018.push_back("VBFHHTo4B_CV_0_5_C2V_1_C3_1_TuneCP5_PSWeights_13TeV-madgraph-pythia8");
  MCSamples_2018.push_back("VBFHHTo4B_CV_1_5_C2V_1_C3_1_TuneCP5_PSWeights_13TeV-madgraph-pythia8");
  MCSamples_2018.push_back("VBFHHTo4B_CV_1_C2V_1_C3_0_TuneCP5_PSWeights_13TeV-madgraph-pythia8");
  MCSamples_2018.push_back("VBFHHTo4B_CV_1_C2V_1_C3_2_TuneCP5_PSWeights_13TeV-madgraph-pythia8");
  MCSamples_2018.push_back("VBFHHTo4B_CV_1_C2V_2_C3_1_TuneCP5_PSWeights_13TeV-madgraph-pythia8");
  MCSamples_2018.push_back("VBFHToBB_M-125_13TeV_powheg_pythia8_weightfix");
  MCSamples_2018.push_back("WminusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8");
  MCSamples_2018.push_back("WplusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8");
  MCSamples_2018.push_back("ZH_HToBB_ZToQQ_M125_13TeV_powheg_pythia8");
  MCSamples_2018.push_back("ttHTobb_M125_TuneCP5_13TeV-powheg-pythia8");
  MCSamples_2018.push_back("GluGluToHHTo4B_node_cHHH0_TuneCP5_PSWeights_13TeV-powheg-pythia8");
  MCSamples_2018.push_back("GluGluToHHTo4B_node_cHHH1_TuneCP5_PSWeights_13TeV-powheg-pythia8");
  MCSamples_2018.push_back("GluGluToHHTo4B_node_cHHH2p45_TuneCP5_PSWeights_13TeV-powheg-pythia8");
  MCSamples_2018.push_back("GluGluToHHTo4B_node_cHHH5_TuneCP5_PSWeights_13TeV-powheg-pythia8");
  MCSamples_2018.push_back("WW_TuneCP5_13TeV-pythia8");
  MCSamples_2018.push_back("WZ_TuneCP5_13TeV-pythia8");
  MCSamples_2018.push_back("ZZ_TuneCP5_13TeV-pythia8");
  MCSamples_2018.push_back("WJetsToQQ_HT400to600_qc19_3j_TuneCP5_13TeV-madgraphMLM-pythia8");
  MCSamples_2018.push_back("WJetsToQQ_HT600to800_qc19_3j_TuneCP5_13TeV-madgraphMLM-pythia8");
  MCSamples_2018.push_back("WJetsToQQ_HT-800toInf_qc19_3j_TuneCP5_13TeV-madgraphMLM-pythia8");
  MCSamples_2018.push_back("ZJetsToQQ_HT400to600_qc19_4j_TuneCP5_13TeV-madgraphMLM-pythia8");
  MCSamples_2018.push_back("ZJetsToQQ_HT600to800_qc19_4j_TuneCP5_13TeV-madgraphMLM-pythia8");
  MCSamples_2018.push_back("ZJetsToQQ_HT-800toInf_qc19_4j_TuneCP5_13TeV-madgraphMLM-pythia8");
  MCSamples_2018.push_back("ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8");
  MCSamples_2018.push_back("ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8");
  MCSamples_2018.push_back("WJetsToLNu_Pt-100To250_TuneCP5_13TeV-amcatnloFXFX-pythia8");
  MCSamples_2018.push_back("WJetsToLNu_Pt-250To400_TuneCP5_13TeV-amcatnloFXFX-pythia8");
  MCSamples_2018.push_back("WJetsToLNu_Pt-400To600_TuneCP5_13TeV-amcatnloFXFX-pythia8");
  MCSamples_2018.push_back("WJetsToLNu_Pt-50To100_TuneCP5_13TeV-amcatnloFXFX-pythia8");
  MCSamples_2018.push_back("WJetsToLNu_Pt-600ToInf_TuneCP5_13TeV-amcatnloFXFX-pythia8");
  MCSamples_2018.push_back("GJets_DR-0p4_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8");
  MCSamples_2018.push_back("GJets_DR-0p4_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8");
  MCSamples_2018.push_back("GJets_DR-0p4_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8");
  MCSamples_2018.push_back("GJets_DR-0p4_HT-600ToInf_TuneCP5_13TeV-madgraphMLM-pythia8");
  MCSamples_2018.push_back("TT_Mtt-1000toInf_TuneCP5_13TeV-powheg-pythia8");
  MCSamples_2018.push_back("TT_Mtt-700to1000_TuneCP5_13TeV-powheg-pythia8");
  MCSamples_2018.push_back("VBF_HH_CV_0_5_C2V_1_C3_1_dipoleRecoilOff-TuneCP5_PSweights_13TeV-madgraph-pythia8");
  MCSamples_2018.push_back("VBF_HH_CV_1_5_C2V_1_C3_1_dipoleRecoilOff-TuneCP5_PSweights_13TeV-madgraph-pythia8");
  MCSamples_2018.push_back("VBF_HH_CV_1_C2V_0_C3_1_dipoleRecoilOff-TuneCP5_PSweights_13TeV-madgraph-pythia8");
  MCSamples_2018.push_back("VBF_HH_CV_1_C2V_1_C3_0_dipoleRecoilOff-TuneCP5_PSweights_13TeV-madgraph-pythia8");
  MCSamples_2018.push_back("VBF_HH_CV_1_C2V_1_C3_1_dipoleRecoilOff-TuneCP5_PSweights_13TeV-madgraph-pythia8");
  MCSamples_2018.push_back("VBF_HH_CV_1_C2V_1_C3_2_dipoleRecoilOff-TuneCP5_PSweights_13TeV-madgraph-pythia8");
  MCSamples_2018.push_back("VBF_HH_CV_1_C2V_2_C3_1_dipoleRecoilOff-TuneCP5_PSweights_13TeV-madgraph-pythia8");


  assert(MCSamples_2016.size() == MCPileupFiles_2016.size());
  assert(MCSamples_2017.size() == MCPileupFiles_2017.size());
  assert(MCSamples_2018.size() == MCPileupFiles_2018.size());

  for (int i=0; i<MCSamples_2016.size() ; i++) {
    cout << "Computing Pileup Weights for sample: " << MCSamples_2016[i] << "\n";
    DoComputePileupWeights( "/afs/cern.ch/work/s/sixie/public/releases/run2/analysis/HH/CMSSW_10_6_8/src/HHBoostedAnalyzer/data/PileupWeights/PileupTarget_2016_36p2ifb.root",
  			    MCPileupFiles_2016[i],
  			    MCSamples_2016[i],
  			    "2016",
  			    "PileupWeights.root");
    DoComputePileupWeights( "/afs/cern.ch/work/s/sixie/public/releases/run2/analysis/HH/CMSSW_10_6_8/src/HHBoostedAnalyzer/data/PileupWeights/PileupTarget_2016_36p2ifb_SysUp.root",
  			    MCPileupFiles_2016[i],
  			    MCSamples_2016[i],
  			    "2016_SysUp",
  			    "PileupWeights.root");
    DoComputePileupWeights( "/afs/cern.ch/work/s/sixie/public/releases/run2/analysis/HH/CMSSW_10_6_8/src/HHBoostedAnalyzer/data/PileupWeights/PileupTarget_2016_36p2ifb_SysDown.root",
  			    MCPileupFiles_2016[i],
  			    MCSamples_2016[i],
  			    "2016_SysDown",
  			    "PileupWeights.root");

  }


   for (int i=0; i<MCSamples_2017.size() ; i++) {
    cout << "Computing Pileup Weights for sample: " << MCSamples_2017[i] << "\n";
    DoComputePileupWeights( "/afs/cern.ch/work/s/sixie/public/releases/run2/analysis/HH/CMSSW_10_6_8/src/HHBoostedAnalyzer/data/PileupWeights/PileupTarget_2017_41p53ifb.root",
			    MCPileupFiles_2017[i],
			    MCSamples_2017[i],
			    "2017",
			    "PileupWeights.root");
    DoComputePileupWeights( "/afs/cern.ch/work/s/sixie/public/releases/run2/analysis/HH/CMSSW_10_6_8/src/HHBoostedAnalyzer/data/PileupWeights/PileupTarget_2017_41p53ifb_SysUp.root",
			    MCPileupFiles_2017[i],
			    MCSamples_2017[i],
			    "2017_SysUp",
			    "PileupWeights.root");
     DoComputePileupWeights( "/afs/cern.ch/work/s/sixie/public/releases/run2/analysis/HH/CMSSW_10_6_8/src/HHBoostedAnalyzer/data/PileupWeights/PileupTarget_2017_41p53ifb_SysDown.root",
			    MCPileupFiles_2017[i],
			    MCSamples_2017[i],
			    "2017_SysDown",
			    "PileupWeights.root");
 }


   for (int i=0; i<MCSamples_2018.size() ; i++) {
    cout << "Computing Pileup Weights for sample: " << MCSamples_2018[i] << "\n";
    DoComputePileupWeights( "/afs/cern.ch/work/s/sixie/public/releases/run2/analysis/HH/CMSSW_10_6_8/src/HHBoostedAnalyzer/data/PileupWeights/PileupTarget_2018.root",
			    MCPileupFiles_2018[i],
			    MCSamples_2018[i],
			    "2018",
			    "PileupWeights.root");
    DoComputePileupWeights( "/afs/cern.ch/work/s/sixie/public/releases/run2/analysis/HH/CMSSW_10_6_8/src/HHBoostedAnalyzer/data/PileupWeights/PileupTarget_2018_SysUp.root",
			    MCPileupFiles_2018[i],
			    MCSamples_2018[i],
			    "2018_SysUp",
			    "PileupWeights.root");
    DoComputePileupWeights( "/afs/cern.ch/work/s/sixie/public/releases/run2/analysis/HH/CMSSW_10_6_8/src/HHBoostedAnalyzer/data/PileupWeights/PileupTarget_2018_SysDown.root",
			    MCPileupFiles_2018[i],
			    MCSamples_2018[i],
			    "2018_SysDown",
			    "PileupWeights.root");
  }





}
