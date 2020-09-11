//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Aug 20 11:53:21 2020 by ROOT version 6.20/04
// from TTree tree/
// found on file: 2017/TTToHadronic_TuneCP5_13TeV-powheg-pythia8_1pb_weighted_BDTs.root
//////////////////////////////////////////////////////////

#ifndef tree_h
#define tree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class tree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         weight;
   Float_t         triggerEffWeight;
   Float_t         pileupWeight;
   Float_t         totalWeight;
   UInt_t          run;
   UInt_t          lumi;
   ULong64_t       event;
   Float_t         npu;
   Float_t         rho;
   Float_t         genHiggs1Pt;
   Float_t         genHiggs1Eta;
   Float_t         genHiggs1Phi;
   Float_t         genHiggs2Pt;
   Float_t         genHiggs2Eta;
   Float_t         genHiggs2Phi;
   Float_t         genHH_pt;
   Float_t         genHH_eta;
   Float_t         genHH_phi;
   Float_t         genHH_mass;
   Int_t           NJets;
   Float_t         MET;
   Float_t         fatJet1Pt;
   Float_t         fatJet1Eta;
   Float_t         fatJet1Phi;
   Float_t         fatJet1Mass;
   Float_t         fatJet1MassSD;
   Float_t         fatJet1DDBTagger;
   Float_t         fatJet1PNetXbb;
   Float_t         fatJet1PNetQCDb;
   Float_t         fatJet1PNetQCDbb;
   Float_t         fatJet1PNetQCDothers;
   Int_t           fatJet1GenMatchIndex;
   Float_t         fatJet1Tau3OverTau2;
   Bool_t          fatJet1HasMuon;
   Bool_t          fatJet1HasElectron;
   Bool_t          fatJet1HasBJetCSVLoose;
   Bool_t          fatJet1HasBJetCSVMedium;
   Bool_t          fatJet1HasBJetCSVTight;
   Float_t         fatJet2Pt;
   Float_t         fatJet2Eta;
   Float_t         fatJet2Phi;
   Float_t         fatJet2Mass;
   Float_t         fatJet2MassSD;
   Float_t         fatJet2DDBTagger;
   Float_t         fatJet2PNetXbb;
   Float_t         fatJet2PNetQCDb;
   Float_t         fatJet2PNetQCDbb;
   Float_t         fatJet2PNetQCDothers;
   Int_t           fatJet2GenMatchIndex;
   Float_t         fatJet2Tau3OverTau2;
   Bool_t          fatJet2HasMuon;
   Bool_t          fatJet2HasElectron;
   Bool_t          fatJet2HasBJetCSVLoose;
   Bool_t          fatJet2HasBJetCSVMedium;
   Bool_t          fatJet2HasBJetCSVTight;
   Float_t         hh_pt;
   Float_t         hh_eta;
   Float_t         hh_phi;
   Float_t         hh_mass;
   Float_t         fatJet1PtOverMHH;
   Float_t         fatJet1PtOverMSD;
   Float_t         fatJet2PtOverMHH;
   Float_t         fatJet2PtOverMSD;
   Float_t         deltaEta_j1j2;
   Float_t         deltaPhi_j1j2;
   Float_t         deltaR_j1j2;
   Float_t         ptj2_over_ptj1;
   Float_t         mj2_over_mj1;
   Bool_t          HLT_PFHT1050;
   Bool_t          HLT_AK8PFJet360_TrimMass30;
   Bool_t          HLT_AK8PFJet380_TrimMass30;
   Bool_t          HLT_AK8PFJet400_TrimMass30;
   Bool_t          HLT_AK8PFJet420_TrimMass30;
   Bool_t          HLT_AK8PFHT750_TrimMass50;
   Bool_t          HLT_AK8PFHT800_TrimMass50;
   Bool_t          HLT_AK8PFHT850_TrimMass50;
   Bool_t          HLT_AK8PFHT900_TrimMass50;
   Bool_t          HLT_PFJet450;
   Bool_t          HLT_PFJet500;
   Bool_t          HLT_PFJet550;
   Bool_t          HLT_AK8PFJet450;
   Bool_t          HLT_AK8PFJet500;
   Bool_t          HLT_AK8PFJet550;
   Bool_t          HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17;
   Bool_t          HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1;
   Bool_t          HLT_AK8PFJet330_PFAK8BTagCSV_p17;
   Bool_t          HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02;
   Bool_t          HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2;
   Bool_t          HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4;
   Bool_t          HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p20;
   Bool_t          HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p087;
   Bool_t          HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p087;
   Bool_t          HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20;
   Bool_t          HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20;
   Bool_t          HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20;
   Float_t         disc_qcd_2017_basic0;
   Float_t         disc_qcd_2017_basic1;
   Float_t         disc_qcd_2017_basic2;
   Float_t         disc_qcd_2017_enhanced;
   Float_t         disc_qcd_2017_enhanced_v2;
   Float_t         disc_ttbar_2017_basic0;
   Float_t         disc_ttbar_2017_basic1;
   Float_t         disc_ttbar_2017_basic2;
   Float_t         disc_ttbar_2017_enhanced;
   Float_t         disc_ttbar_2017_enhanced_v2;
   Float_t         disc_qcd_and_ttbar_2017_basic0;
   Float_t         disc_qcd_and_ttbar_2017_basic1;
   Float_t         disc_qcd_and_ttbar_2017_basic2;
   Float_t         disc_qcd_and_ttbar_2017_enhanced;
   Float_t         disc_qcd_and_ttbar_2017_enhanced_v2;

   // List of branches
   TBranch        *b_weight;   //!
   TBranch        *b_triggerEffWeight;   //!
   TBranch        *b_pileupWeight;   //!
   TBranch        *b_totalWeight;   //!
   TBranch        *b_run;   //!
   TBranch        *b_lumi;   //!
   TBranch        *b_event;   //!
   TBranch        *b_npu;   //!
   TBranch        *b_rho;   //!
   TBranch        *b_genHiggs1Pt;   //!
   TBranch        *b_genHiggs1Eta;   //!
   TBranch        *b_genHiggs1Phi;   //!
   TBranch        *b_genHiggs2Pt;   //!
   TBranch        *b_genHiggs2Eta;   //!
   TBranch        *b_genHiggs2Phi;   //!
   TBranch        *b_genHH_pt;   //!
   TBranch        *b_genHH_eta;   //!
   TBranch        *b_genHH_phi;   //!
   TBranch        *b_genHH_mass;   //!
   TBranch        *b_NJets;   //!
   TBranch        *b_MET;   //!
   TBranch        *b_fatJet1Pt;   //!
   TBranch        *b_fatJet1Eta;   //!
   TBranch        *b_fatJet1Phi;   //!
   TBranch        *b_fatJet1Mass;   //!
   TBranch        *b_fatJet1MassSD;   //!
   TBranch        *b_fatJet1DDBTagger;   //!
   TBranch        *b_fatJet1PNetXbb;   //!
   TBranch        *b_fatJet1PNetQCDb;   //!
   TBranch        *b_fatJet1PNetQCDbb;   //!
   TBranch        *b_fatJet1PNetQCDothers;   //!
   TBranch        *b_fatJet1GenMatchIndex;   //!
   TBranch        *b_fatJet1Tau3OverTau2;   //!
   TBranch        *b_fatJet1HasMuon;   //!
   TBranch        *b_fatJet1HasElectron;   //!
   TBranch        *b_fatJet1HasBJetCSVLoose;   //!
   TBranch        *b_fatJet1HasBJetCSVMedium;   //!
   TBranch        *b_fatJet1HasBJetCSVTight;   //!
   TBranch        *b_fatJet2Pt;   //!
   TBranch        *b_fatJet2Eta;   //!
   TBranch        *b_fatJet2Phi;   //!
   TBranch        *b_fatJet2Mass;   //!
   TBranch        *b_fatJet2MassSD;   //!
   TBranch        *b_fatJet2DDBTagger;   //!
   TBranch        *b_fatJet2PNetXbb;   //!
   TBranch        *b_fatJet2PNetQCDb;   //!
   TBranch        *b_fatJet2PNetQCDbb;   //!
   TBranch        *b_fatJet2PNetQCDothers;   //!
   TBranch        *b_fatJet2GenMatchIndex;   //!
   TBranch        *b_fatJet2Tau3OverTau2;   //!
   TBranch        *b_fatJet2HasMuon;   //!
   TBranch        *b_fatJet2HasElectron;   //!
   TBranch        *b_fatJet2HasBJetCSVLoose;   //!
   TBranch        *b_fatJet2HasBJetCSVMedium;   //!
   TBranch        *b_fatJet2HasBJetCSVTight;   //!
   TBranch        *b_hh_pt;   //!
   TBranch        *b_hh_eta;   //!
   TBranch        *b_hh_phi;   //!
   TBranch        *b_hh_mass;   //!
   TBranch        *b_fatJet1PtOverMHH;   //!
   TBranch        *b_fatJet1PtOverMSD;   //!
   TBranch        *b_fatJet2PtOverMHH;   //!
   TBranch        *b_fatJet2PtOverMSD;   //!
   TBranch        *b_deltaEta_j1j2;   //!
   TBranch        *b_deltaPhi_j1j2;   //!
   TBranch        *b_deltaR_j1j2;   //!
   TBranch        *b_ptj2_over_ptj1;   //!
   TBranch        *b_mj2_over_mj1;   //!
   TBranch        *b_HLT_PFHT1050;   //!
   TBranch        *b_HLT_AK8PFJet360_TrimMass30;   //!
   TBranch        *b_HLT_AK8PFJet380_TrimMass30;   //!
   TBranch        *b_HLT_AK8PFJet400_TrimMass30;   //!
   TBranch        *b_HLT_AK8PFJet420_TrimMass30;   //!
   TBranch        *b_HLT_AK8PFHT750_TrimMass50;   //!
   TBranch        *b_HLT_AK8PFHT800_TrimMass50;   //!
   TBranch        *b_HLT_AK8PFHT850_TrimMass50;   //!
   TBranch        *b_HLT_AK8PFHT900_TrimMass50;   //!
   TBranch        *b_HLT_PFJet450;   //!
   TBranch        *b_HLT_PFJet500;   //!
   TBranch        *b_HLT_PFJet550;   //!
   TBranch        *b_HLT_AK8PFJet450;   //!
   TBranch        *b_HLT_AK8PFJet500;   //!
   TBranch        *b_HLT_AK8PFJet550;   //!
   TBranch        *b_HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17;   //!
   TBranch        *b_HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1;   //!
   TBranch        *b_HLT_AK8PFJet330_PFAK8BTagCSV_p17;   //!
   TBranch        *b_HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02;   //!
   TBranch        *b_HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2;   //!
   TBranch        *b_HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4;   //!
   TBranch        *b_HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p20;   //!
   TBranch        *b_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p087;   //!
   TBranch        *b_HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p087;   //!
   TBranch        *b_HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20;   //!
   TBranch        *b_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20;   //!
   TBranch        *b_HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20;   //!
   TBranch        *b_disc_qcd_2017_basic0;   //!
   TBranch        *b_disc_qcd_2017_basic1;   //!
   TBranch        *b_disc_qcd_2017_basic2;   //!
   TBranch        *b_disc_qcd_2017_enhanced;   //!
   TBranch        *b_disc_qcd_2017_enhanced_v2;   //!
   TBranch        *b_disc_ttbar_2017_basic0;   //!
   TBranch        *b_disc_ttbar_2017_basic1;   //!
   TBranch        *b_disc_ttbar_2017_basic2;   //!
   TBranch        *b_disc_ttbar_2017_enhanced;   //!
   TBranch        *b_disc_ttbar_2017_enhanced_v2;   //!
   TBranch        *b_disc_qcd_and_ttbar_2017_basic0;   //!
   TBranch        *b_disc_qcd_and_ttbar_2017_basic1;   //!
   TBranch        *b_disc_qcd_and_ttbar_2017_basic2;   //!
   TBranch        *b_disc_qcd_and_ttbar_2017_enhanced;   //!
   TBranch        *b_disc_qcd_and_ttbar_2017_enhanced_v2;   //!

   tree(TTree *tree=0);
   virtual ~tree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef tree_cxx
tree::tree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("2017/TTToHadronic_TuneCP5_13TeV-powheg-pythia8_1pb_weighted_BDTs.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("2017/TTToHadronic_TuneCP5_13TeV-powheg-pythia8_1pb_weighted_BDTs.root");
      }
      f->GetObject("tree",tree);

   }
   Init(tree);
}

tree::~tree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t tree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t tree::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void tree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("weight", &weight, &b_weight);
   fChain->SetBranchAddress("triggerEffWeight", &triggerEffWeight, &b_triggerEffWeight);
   fChain->SetBranchAddress("pileupWeight", &pileupWeight, &b_pileupWeight);
   fChain->SetBranchAddress("totalWeight", &totalWeight, &b_totalWeight);
   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("npu", &npu, &b_npu);
   fChain->SetBranchAddress("rho", &rho, &b_rho);
   fChain->SetBranchAddress("genHiggs1Pt", &genHiggs1Pt, &b_genHiggs1Pt);
   fChain->SetBranchAddress("genHiggs1Eta", &genHiggs1Eta, &b_genHiggs1Eta);
   fChain->SetBranchAddress("genHiggs1Phi", &genHiggs1Phi, &b_genHiggs1Phi);
   fChain->SetBranchAddress("genHiggs2Pt", &genHiggs2Pt, &b_genHiggs2Pt);
   fChain->SetBranchAddress("genHiggs2Eta", &genHiggs2Eta, &b_genHiggs2Eta);
   fChain->SetBranchAddress("genHiggs2Phi", &genHiggs2Phi, &b_genHiggs2Phi);
   fChain->SetBranchAddress("genHH_pt", &genHH_pt, &b_genHH_pt);
   fChain->SetBranchAddress("genHH_eta", &genHH_eta, &b_genHH_eta);
   fChain->SetBranchAddress("genHH_phi", &genHH_phi, &b_genHH_phi);
   fChain->SetBranchAddress("genHH_mass", &genHH_mass, &b_genHH_mass);
   fChain->SetBranchAddress("NJets", &NJets, &b_NJets);
   fChain->SetBranchAddress("MET", &MET, &b_MET);
   fChain->SetBranchAddress("fatJet1Pt", &fatJet1Pt, &b_fatJet1Pt);
   fChain->SetBranchAddress("fatJet1Eta", &fatJet1Eta, &b_fatJet1Eta);
   fChain->SetBranchAddress("fatJet1Phi", &fatJet1Phi, &b_fatJet1Phi);
   fChain->SetBranchAddress("fatJet1Mass", &fatJet1Mass, &b_fatJet1Mass);
   fChain->SetBranchAddress("fatJet1MassSD", &fatJet1MassSD, &b_fatJet1MassSD);
   fChain->SetBranchAddress("fatJet1DDBTagger", &fatJet1DDBTagger, &b_fatJet1DDBTagger);
   fChain->SetBranchAddress("fatJet1PNetXbb", &fatJet1PNetXbb, &b_fatJet1PNetXbb);
   fChain->SetBranchAddress("fatJet1PNetQCDb", &fatJet1PNetQCDb, &b_fatJet1PNetQCDb);
   fChain->SetBranchAddress("fatJet1PNetQCDbb", &fatJet1PNetQCDbb, &b_fatJet1PNetQCDbb);
   fChain->SetBranchAddress("fatJet1PNetQCDothers", &fatJet1PNetQCDothers, &b_fatJet1PNetQCDothers);
   fChain->SetBranchAddress("fatJet1GenMatchIndex", &fatJet1GenMatchIndex, &b_fatJet1GenMatchIndex);
   fChain->SetBranchAddress("fatJet1Tau3OverTau2", &fatJet1Tau3OverTau2, &b_fatJet1Tau3OverTau2);
   fChain->SetBranchAddress("fatJet1HasMuon", &fatJet1HasMuon, &b_fatJet1HasMuon);
   fChain->SetBranchAddress("fatJet1HasElectron", &fatJet1HasElectron, &b_fatJet1HasElectron);
   fChain->SetBranchAddress("fatJet1HasBJetCSVLoose", &fatJet1HasBJetCSVLoose, &b_fatJet1HasBJetCSVLoose);
   fChain->SetBranchAddress("fatJet1HasBJetCSVMedium", &fatJet1HasBJetCSVMedium, &b_fatJet1HasBJetCSVMedium);
   fChain->SetBranchAddress("fatJet1HasBJetCSVTight", &fatJet1HasBJetCSVTight, &b_fatJet1HasBJetCSVTight);
   fChain->SetBranchAddress("fatJet2Pt", &fatJet2Pt, &b_fatJet2Pt);
   fChain->SetBranchAddress("fatJet2Eta", &fatJet2Eta, &b_fatJet2Eta);
   fChain->SetBranchAddress("fatJet2Phi", &fatJet2Phi, &b_fatJet2Phi);
   fChain->SetBranchAddress("fatJet2Mass", &fatJet2Mass, &b_fatJet2Mass);
   fChain->SetBranchAddress("fatJet2MassSD", &fatJet2MassSD, &b_fatJet2MassSD);
   fChain->SetBranchAddress("fatJet2DDBTagger", &fatJet2DDBTagger, &b_fatJet2DDBTagger);
   fChain->SetBranchAddress("fatJet2PNetXbb", &fatJet2PNetXbb, &b_fatJet2PNetXbb);
   fChain->SetBranchAddress("fatJet2PNetQCDb", &fatJet2PNetQCDb, &b_fatJet2PNetQCDb);
   fChain->SetBranchAddress("fatJet2PNetQCDbb", &fatJet2PNetQCDbb, &b_fatJet2PNetQCDbb);
   fChain->SetBranchAddress("fatJet2PNetQCDothers", &fatJet2PNetQCDothers, &b_fatJet2PNetQCDothers);
   fChain->SetBranchAddress("fatJet2GenMatchIndex", &fatJet2GenMatchIndex, &b_fatJet2GenMatchIndex);
   fChain->SetBranchAddress("fatJet2Tau3OverTau2", &fatJet2Tau3OverTau2, &b_fatJet2Tau3OverTau2);
   fChain->SetBranchAddress("fatJet2HasMuon", &fatJet2HasMuon, &b_fatJet2HasMuon);
   fChain->SetBranchAddress("fatJet2HasElectron", &fatJet2HasElectron, &b_fatJet2HasElectron);
   fChain->SetBranchAddress("fatJet2HasBJetCSVLoose", &fatJet2HasBJetCSVLoose, &b_fatJet2HasBJetCSVLoose);
   fChain->SetBranchAddress("fatJet2HasBJetCSVMedium", &fatJet2HasBJetCSVMedium, &b_fatJet2HasBJetCSVMedium);
   fChain->SetBranchAddress("fatJet2HasBJetCSVTight", &fatJet2HasBJetCSVTight, &b_fatJet2HasBJetCSVTight);
   fChain->SetBranchAddress("hh_pt", &hh_pt, &b_hh_pt);
   fChain->SetBranchAddress("hh_eta", &hh_eta, &b_hh_eta);
   fChain->SetBranchAddress("hh_phi", &hh_phi, &b_hh_phi);
   fChain->SetBranchAddress("hh_mass", &hh_mass, &b_hh_mass);
   fChain->SetBranchAddress("fatJet1PtOverMHH", &fatJet1PtOverMHH, &b_fatJet1PtOverMHH);
   fChain->SetBranchAddress("fatJet1PtOverMSD", &fatJet1PtOverMSD, &b_fatJet1PtOverMSD);
   fChain->SetBranchAddress("fatJet2PtOverMHH", &fatJet2PtOverMHH, &b_fatJet2PtOverMHH);
   fChain->SetBranchAddress("fatJet2PtOverMSD", &fatJet2PtOverMSD, &b_fatJet2PtOverMSD);
   fChain->SetBranchAddress("deltaEta_j1j2", &deltaEta_j1j2, &b_deltaEta_j1j2);
   fChain->SetBranchAddress("deltaPhi_j1j2", &deltaPhi_j1j2, &b_deltaPhi_j1j2);
   fChain->SetBranchAddress("deltaR_j1j2", &deltaR_j1j2, &b_deltaR_j1j2);
   fChain->SetBranchAddress("ptj2_over_ptj1", &ptj2_over_ptj1, &b_ptj2_over_ptj1);
   fChain->SetBranchAddress("mj2_over_mj1", &mj2_over_mj1, &b_mj2_over_mj1);
   fChain->SetBranchAddress("HLT_PFHT1050", &HLT_PFHT1050, &b_HLT_PFHT1050);
   fChain->SetBranchAddress("HLT_AK8PFJet360_TrimMass30", &HLT_AK8PFJet360_TrimMass30, &b_HLT_AK8PFJet360_TrimMass30);
   fChain->SetBranchAddress("HLT_AK8PFJet380_TrimMass30", &HLT_AK8PFJet380_TrimMass30, &b_HLT_AK8PFJet380_TrimMass30);
   fChain->SetBranchAddress("HLT_AK8PFJet400_TrimMass30", &HLT_AK8PFJet400_TrimMass30, &b_HLT_AK8PFJet400_TrimMass30);
   fChain->SetBranchAddress("HLT_AK8PFJet420_TrimMass30", &HLT_AK8PFJet420_TrimMass30, &b_HLT_AK8PFJet420_TrimMass30);
   fChain->SetBranchAddress("HLT_AK8PFHT750_TrimMass50", &HLT_AK8PFHT750_TrimMass50, &b_HLT_AK8PFHT750_TrimMass50);
   fChain->SetBranchAddress("HLT_AK8PFHT800_TrimMass50", &HLT_AK8PFHT800_TrimMass50, &b_HLT_AK8PFHT800_TrimMass50);
   fChain->SetBranchAddress("HLT_AK8PFHT850_TrimMass50", &HLT_AK8PFHT850_TrimMass50, &b_HLT_AK8PFHT850_TrimMass50);
   fChain->SetBranchAddress("HLT_AK8PFHT900_TrimMass50", &HLT_AK8PFHT900_TrimMass50, &b_HLT_AK8PFHT900_TrimMass50);
   fChain->SetBranchAddress("HLT_PFJet450", &HLT_PFJet450, &b_HLT_PFJet450);
   fChain->SetBranchAddress("HLT_PFJet500", &HLT_PFJet500, &b_HLT_PFJet500);
   fChain->SetBranchAddress("HLT_PFJet550", &HLT_PFJet550, &b_HLT_PFJet550);
   fChain->SetBranchAddress("HLT_AK8PFJet450", &HLT_AK8PFJet450, &b_HLT_AK8PFJet450);
   fChain->SetBranchAddress("HLT_AK8PFJet500", &HLT_AK8PFJet500, &b_HLT_AK8PFJet500);
   fChain->SetBranchAddress("HLT_AK8PFJet550", &HLT_AK8PFJet550, &b_HLT_AK8PFJet550);
   fChain->SetBranchAddress("HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17", &HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17, &b_HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17);
   fChain->SetBranchAddress("HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1", &HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1, &b_HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1);
   fChain->SetBranchAddress("HLT_AK8PFJet330_PFAK8BTagCSV_p17", &HLT_AK8PFJet330_PFAK8BTagCSV_p17, &b_HLT_AK8PFJet330_PFAK8BTagCSV_p17);
   fChain->SetBranchAddress("HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02", &HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02, &b_HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02);
   fChain->SetBranchAddress("HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2", &HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2, &b_HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2);
   fChain->SetBranchAddress("HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4", &HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4, &b_HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4);
   fChain->SetBranchAddress("HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p20", &HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p20, &b_HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p20);
   fChain->SetBranchAddress("HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p087", &HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p087, &b_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p087);
   fChain->SetBranchAddress("HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p087", &HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p087, &b_HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p087);
   fChain->SetBranchAddress("HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20", &HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20, &b_HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20);
   fChain->SetBranchAddress("HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20", &HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20, &b_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20);
   fChain->SetBranchAddress("HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20", &HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20, &b_HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20);
   fChain->SetBranchAddress("disc_qcd_2017_basic0", &disc_qcd_2017_basic0, &b_disc_qcd_2017_basic0);
   fChain->SetBranchAddress("disc_qcd_2017_basic1", &disc_qcd_2017_basic1, &b_disc_qcd_2017_basic1);
   fChain->SetBranchAddress("disc_qcd_2017_basic2", &disc_qcd_2017_basic2, &b_disc_qcd_2017_basic2);
   fChain->SetBranchAddress("disc_qcd_2017_enhanced", &disc_qcd_2017_enhanced, &b_disc_qcd_2017_enhanced);
   fChain->SetBranchAddress("disc_qcd_2017_enhanced_v2", &disc_qcd_2017_enhanced_v2, &b_disc_qcd_2017_enhanced_v2);
   fChain->SetBranchAddress("disc_ttbar_2017_basic0", &disc_ttbar_2017_basic0, &b_disc_ttbar_2017_basic0);
   fChain->SetBranchAddress("disc_ttbar_2017_basic1", &disc_ttbar_2017_basic1, &b_disc_ttbar_2017_basic1);
   fChain->SetBranchAddress("disc_ttbar_2017_basic2", &disc_ttbar_2017_basic2, &b_disc_ttbar_2017_basic2);
   fChain->SetBranchAddress("disc_ttbar_2017_enhanced", &disc_ttbar_2017_enhanced, &b_disc_ttbar_2017_enhanced);
   fChain->SetBranchAddress("disc_ttbar_2017_enhanced_v2", &disc_ttbar_2017_enhanced_v2, &b_disc_ttbar_2017_enhanced_v2);
   fChain->SetBranchAddress("disc_qcd_and_ttbar_2017_basic0", &disc_qcd_and_ttbar_2017_basic0, &b_disc_qcd_and_ttbar_2017_basic0);
   fChain->SetBranchAddress("disc_qcd_and_ttbar_2017_basic1", &disc_qcd_and_ttbar_2017_basic1, &b_disc_qcd_and_ttbar_2017_basic1);
   fChain->SetBranchAddress("disc_qcd_and_ttbar_2017_basic2", &disc_qcd_and_ttbar_2017_basic2, &b_disc_qcd_and_ttbar_2017_basic2);
   fChain->SetBranchAddress("disc_qcd_and_ttbar_2017_enhanced", &disc_qcd_and_ttbar_2017_enhanced, &b_disc_qcd_and_ttbar_2017_enhanced);
   fChain->SetBranchAddress("disc_qcd_and_ttbar_2017_enhanced_v2", &disc_qcd_and_ttbar_2017_enhanced_v2, &b_disc_qcd_and_ttbar_2017_enhanced_v2);
   Notify();
}

Bool_t tree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void tree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t tree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef tree_cxx
