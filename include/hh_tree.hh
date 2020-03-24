//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Mar 21 17:02:11 2020 by ROOT version 6.10/09
// from TTree hh/hh
// found on file: /eos/uscms/store/group/lpchbb/LLDJntuples/cmorgoth/qcd_ht_2000toInf_v3/diHiggs_output_qcd_ht_2000toInf_v3_all_1pb_weighted.root
//////////////////////////////////////////////////////////

#ifndef hh_h
#define hh_h

#include <string>

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class hh {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain
   std::string     fout_name;
// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   UInt_t          run;
   UInt_t          luminosityBlock;
   ULong64_t       event;
   Float_t         ChsMET_phi;
   Float_t         ChsMET_pt;
   Float_t         ChsMET_sumEt;
   Float_t         h_pt[2];
   Float_t         h_eta[2];
   Float_t         h_phi[2];
   UInt_t          nFatJet;
   Float_t         FatJet_LSmsoftdrop[8];   //[nFatJet]
   Float_t         FatJet_LSn2b1[8];   //[nFatJet]
   Float_t         FatJet_LSn3b1[8];   //[nFatJet]
   Float_t         FatJet_LSpt[8];   //[nFatJet]
   Float_t         FatJet_LSrawmsoftdrop[8];   //[nFatJet]
   Float_t         FatJet_LSsubJet1btagDeepB[8];   //[nFatJet]
   Float_t         FatJet_LSsubJet2btagDeepB[8];   //[nFatJet]
   Float_t         FatJet_LStau1[8];   //[nFatJet]
   Float_t         FatJet_LStau2[8];   //[nFatJet]
   Float_t         FatJet_LStau3[8];   //[nFatJet]
   Float_t         FatJet_LStau4[8];   //[nFatJet]
   Float_t         FatJet_area[8];   //[nFatJet]
   Float_t         FatJet_btagDDBvL[8];   //[nFatJet]
   Float_t         FatJet_btagDDCvB[8];   //[nFatJet]
   Float_t         FatJet_btagDDCvL[8];   //[nFatJet]
   Float_t         FatJet_btagHbb[8];   //[nFatJet]
   Float_t         FatJet_dRLep[8];   //[nFatJet]
   Float_t         FatJet_deepTagHbb[8];   //[nFatJet]
   Float_t         FatJet_deepTagHcc[8];   //[nFatJet]
   Float_t         FatJet_deepTagHqqqq[8];   //[nFatJet]
   Float_t         FatJet_deepTagMDHbb[8];   //[nFatJet]
   Float_t         FatJet_deepTagMDHcc[8];   //[nFatJet]
   Float_t         FatJet_deepTagMDHqqqq[8];   //[nFatJet]
   Float_t         FatJet_deepTagMDQCDbb[8];   //[nFatJet]
   Float_t         FatJet_deepTagMDQCDcc[8];   //[nFatJet]
   Float_t         FatJet_deepTagMDWcq[8];   //[nFatJet]
   Float_t         FatJet_deepTagMDWqq[8];   //[nFatJet]
   Float_t         FatJet_deepTagMDZbb[8];   //[nFatJet]
   Float_t         FatJet_deepTagMDZcc[8];   //[nFatJet]
   Float_t         FatJet_deepTagMDZqq[8];   //[nFatJet]
   Float_t         FatJet_deepTagQCDbb[8];   //[nFatJet]
   Float_t         FatJet_deepTagQCDcc[8];   //[nFatJet]
   Float_t         FatJet_deepTagWcq[8];   //[nFatJet]
   Float_t         FatJet_deepTagWqq[8];   //[nFatJet]
   Float_t         FatJet_deepTagZbb[8];   //[nFatJet]
   Float_t         FatJet_deepTagZcc[8];   //[nFatJet]
   Float_t         FatJet_deepTagZqq[8];   //[nFatJet]
   Float_t         FatJet_eta[8];   //[nFatJet]
   Float_t         FatJet_lsf3[8];   //[nFatJet]
   Float_t         FatJet_mass[8];   //[nFatJet]
   Float_t         FatJet_msoftdrop[8];   //[nFatJet]
   Float_t         FatJet_n2b1[8];   //[nFatJet]
   Float_t         FatJet_n3b1[8];   //[nFatJet]
   Float_t         FatJet_phi[8];   //[nFatJet]
   Float_t         FatJet_pt[8];   //[nFatJet]
   Float_t         FatJet_rawFactor[8];   //[nFatJet]
   Float_t         FatJet_rawmsoftdrop[8];   //[nFatJet]
   Float_t         FatJet_tau1[8];   //[nFatJet]
   Float_t         FatJet_tau2[8];   //[nFatJet]
   Float_t         FatJet_tau3[8];   //[nFatJet]
   Float_t         FatJet_tau4[8];   //[nFatJet]
   Int_t           FatJet_electronIdx3SJ[8];   //[nFatJet]
   Int_t           FatJet_idLep[8];   //[nFatJet]
   Int_t           FatJet_jetId[8];   //[nFatJet]
   Int_t           FatJet_muonIdx3SJ[8];   //[nFatJet]
   Int_t           FatJet_nBHadrons[8];   //[nFatJet]
   Int_t           FatJet_nCHadrons[8];   //[nFatJet]
   Int_t           FatJet_nPFConstituents[8];   //[nFatJet]
   Int_t           FatJet_subJetIdx1[8];   //[nFatJet]
   Int_t           FatJet_subJetIdx2[8];   //[nFatJet]
   Bool_t          FatJet_Hmatch[8];   //[nFatJet]
   Int_t           FatJet_HgenIdx[8];   //[nFatJet]
   Float_t         FatJet_HminDR[8];   //[nFatJet]
   Float_t         hh_pt;
   Float_t         hh_eta;
   Float_t         hh_phi;
   Float_t         hh_mass;
   Float_t         hh_gen_pt;
   Float_t         hh_gen_eta;
   Float_t         hh_gen_phi;
   Float_t         hh_gen_mass;
   Float_t         weight;

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_luminosityBlock;   //!
   TBranch        *b_event;   //!
   TBranch        *b_ChsMET_phi;   //!
   TBranch        *b_ChsMET_pt;   //!
   TBranch        *b_ChsMET_sumEt;   //!
   TBranch        *b_h_pt;   //!
   TBranch        *b_h_eta;   //!
   TBranch        *b_h_phi;   //!
   TBranch        *b_nFatJet;   //!
   TBranch        *b_FatJet_LSmsoftdrop;   //!
   TBranch        *b_FatJet_LSn2b1;   //!
   TBranch        *b_FatJet_LSn3b1;   //!
   TBranch        *b_FatJet_LSpt;   //!
   TBranch        *b_FatJet_LSrawmsoftdrop;   //!
   TBranch        *b_FatJet_LSsubJet1btagDeepB;   //!
   TBranch        *b_FatJet_LSsubJet2btagDeepB;   //!
   TBranch        *b_FatJet_LStau1;   //!
   TBranch        *b_FatJet_LStau2;   //!
   TBranch        *b_FatJet_LStau3;   //!
   TBranch        *b_FatJet_LStau4;   //!
   TBranch        *b_FatJet_area;   //!
   TBranch        *b_FatJet_btagDDBvL;   //!
   TBranch        *b_FatJet_btagDDCvB;   //!
   TBranch        *b_FatJet_btagDDCvL;   //!
   TBranch        *b_FatJet_btagHbb;   //!
   TBranch        *b_FatJet_dRLep;   //!
   TBranch        *b_FatJet_deepTagHbb;   //!
   TBranch        *b_FatJet_deepTagHcc;   //!
   TBranch        *b_FatJet_deepTagHqqqq;   //!
   TBranch        *b_FatJet_deepTagMDHbb;   //!
   TBranch        *b_FatJet_deepTagMDHcc;   //!
   TBranch        *b_FatJet_deepTagMDHqqqq;   //!
   TBranch        *b_FatJet_deepTagMDQCDbb;   //!
   TBranch        *b_FatJet_deepTagMDQCDcc;   //!
   TBranch        *b_FatJet_deepTagMDWcq;   //!
   TBranch        *b_FatJet_deepTagMDWqq;   //!
   TBranch        *b_FatJet_deepTagMDZbb;   //!
   TBranch        *b_FatJet_deepTagMDZcc;   //!
   TBranch        *b_FatJet_deepTagMDZqq;   //!
   TBranch        *b_FatJet_deepTagQCDbb;   //!
   TBranch        *b_FatJet_deepTagQCDcc;   //!
   TBranch        *b_FatJet_deepTagWcq;   //!
   TBranch        *b_FatJet_deepTagWqq;   //!
   TBranch        *b_FatJet_deepTagZbb;   //!
   TBranch        *b_FatJet_deepTagZcc;   //!
   TBranch        *b_FatJet_deepTagZqq;   //!
   TBranch        *b_FatJet_eta;   //!
   TBranch        *b_FatJet_lsf3;   //!
   TBranch        *b_FatJet_mass;   //!
   TBranch        *b_FatJet_msoftdrop;   //!
   TBranch        *b_FatJet_n2b1;   //!
   TBranch        *b_FatJet_n3b1;   //!
   TBranch        *b_FatJet_phi;   //!
   TBranch        *b_FatJet_pt;   //!
   TBranch        *b_FatJet_rawFactor;   //!
   TBranch        *b_FatJet_rawmsoftdrop;   //!
   TBranch        *b_FatJet_tau1;   //!
   TBranch        *b_FatJet_tau2;   //!
   TBranch        *b_FatJet_tau3;   //!
   TBranch        *b_FatJet_tau4;   //!
   TBranch        *b_FatJet_electronIdx3SJ;   //!
   TBranch        *b_FatJet_idLep;   //!
   TBranch        *b_FatJet_jetId;   //!
   TBranch        *b_FatJet_muonIdx3SJ;   //!
   TBranch        *b_FatJet_nBHadrons;   //!
   TBranch        *b_FatJet_nCHadrons;   //!
   TBranch        *b_FatJet_nPFConstituents;   //!
   TBranch        *b_FatJet_subJetIdx1;   //!
   TBranch        *b_FatJet_subJetIdx2;   //!
   TBranch        *b_FatJet_Hmatch;   //!
   TBranch        *b_FatJet_HgenIdx;   //!
   TBranch        *b_FatJet_HminDR;   //!
   TBranch        *b_hh_pt;   //!
   TBranch        *b_hh_eta;   //!
   TBranch        *b_hh_phi;   //!
   TBranch        *b_hh_mass;   //!
   TBranch        *b_hh_gen_pt;   //!
   TBranch        *b_hh_gen_eta;   //!
   TBranch        *b_hh_gen_phi;   //!
   TBranch        *b_hh_gen_mass;   //!
   TBranch        *b_weight;   //!
  
  //added variables
  double global_weight = 1.0;
  double lumi = 42.0;
  std::string process = "data";
  
   hh(TTree *tree=0);
   virtual ~hh();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef hh_cxx
hh::hh(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/eos/uscms/store/group/lpchbb/LLDJntuples/cmorgoth/qcd_ht_2000toInf_v3/diHiggs_output_qcd_ht_2000toInf_v3_all_1pb_weighted.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/eos/uscms/store/group/lpchbb/LLDJntuples/cmorgoth/qcd_ht_2000toInf_v3/diHiggs_output_qcd_ht_2000toInf_v3_all_1pb_weighted.root");
      }
      f->GetObject("hh",tree);

   }
   Init(tree);
}

hh::~hh()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t hh::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t hh::LoadTree(Long64_t entry)
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

void hh::Init(TTree *tree)
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

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("luminosityBlock", &luminosityBlock, &b_luminosityBlock);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("ChsMET_phi", &ChsMET_phi, &b_ChsMET_phi);
   fChain->SetBranchAddress("ChsMET_pt", &ChsMET_pt, &b_ChsMET_pt);
   fChain->SetBranchAddress("ChsMET_sumEt", &ChsMET_sumEt, &b_ChsMET_sumEt);
   fChain->SetBranchAddress("h_pt", h_pt, &b_h_pt);
   fChain->SetBranchAddress("h_eta", h_eta, &b_h_eta);
   fChain->SetBranchAddress("h_phi", h_phi, &b_h_phi);
   fChain->SetBranchAddress("nFatJet", &nFatJet, &b_nFatJet);
   fChain->SetBranchAddress("FatJet_LSmsoftdrop", FatJet_LSmsoftdrop, &b_FatJet_LSmsoftdrop);
   fChain->SetBranchAddress("FatJet_LSn2b1", FatJet_LSn2b1, &b_FatJet_LSn2b1);
   fChain->SetBranchAddress("FatJet_LSn3b1", FatJet_LSn3b1, &b_FatJet_LSn3b1);
   fChain->SetBranchAddress("FatJet_LSpt", FatJet_LSpt, &b_FatJet_LSpt);
   fChain->SetBranchAddress("FatJet_LSrawmsoftdrop", FatJet_LSrawmsoftdrop, &b_FatJet_LSrawmsoftdrop);
   fChain->SetBranchAddress("FatJet_LSsubJet1btagDeepB", FatJet_LSsubJet1btagDeepB, &b_FatJet_LSsubJet1btagDeepB);
   fChain->SetBranchAddress("FatJet_LSsubJet2btagDeepB", FatJet_LSsubJet2btagDeepB, &b_FatJet_LSsubJet2btagDeepB);
   fChain->SetBranchAddress("FatJet_LStau1", FatJet_LStau1, &b_FatJet_LStau1);
   fChain->SetBranchAddress("FatJet_LStau2", FatJet_LStau2, &b_FatJet_LStau2);
   fChain->SetBranchAddress("FatJet_LStau3", FatJet_LStau3, &b_FatJet_LStau3);
   fChain->SetBranchAddress("FatJet_LStau4", FatJet_LStau4, &b_FatJet_LStau4);
   fChain->SetBranchAddress("FatJet_area", FatJet_area, &b_FatJet_area);
   fChain->SetBranchAddress("FatJet_btagDDBvL", FatJet_btagDDBvL, &b_FatJet_btagDDBvL);
   fChain->SetBranchAddress("FatJet_btagDDCvB", FatJet_btagDDCvB, &b_FatJet_btagDDCvB);
   fChain->SetBranchAddress("FatJet_btagDDCvL", FatJet_btagDDCvL, &b_FatJet_btagDDCvL);
   fChain->SetBranchAddress("FatJet_btagHbb", FatJet_btagHbb, &b_FatJet_btagHbb);
   fChain->SetBranchAddress("FatJet_dRLep", FatJet_dRLep, &b_FatJet_dRLep);
   fChain->SetBranchAddress("FatJet_deepTagHbb", FatJet_deepTagHbb, &b_FatJet_deepTagHbb);
   fChain->SetBranchAddress("FatJet_deepTagHcc", FatJet_deepTagHcc, &b_FatJet_deepTagHcc);
   fChain->SetBranchAddress("FatJet_deepTagHqqqq", FatJet_deepTagHqqqq, &b_FatJet_deepTagHqqqq);
   fChain->SetBranchAddress("FatJet_deepTagMDHbb", FatJet_deepTagMDHbb, &b_FatJet_deepTagMDHbb);
   fChain->SetBranchAddress("FatJet_deepTagMDHcc", FatJet_deepTagMDHcc, &b_FatJet_deepTagMDHcc);
   fChain->SetBranchAddress("FatJet_deepTagMDHqqqq", FatJet_deepTagMDHqqqq, &b_FatJet_deepTagMDHqqqq);
   fChain->SetBranchAddress("FatJet_deepTagMDQCDbb", FatJet_deepTagMDQCDbb, &b_FatJet_deepTagMDQCDbb);
   fChain->SetBranchAddress("FatJet_deepTagMDQCDcc", FatJet_deepTagMDQCDcc, &b_FatJet_deepTagMDQCDcc);
   fChain->SetBranchAddress("FatJet_deepTagMDWcq", FatJet_deepTagMDWcq, &b_FatJet_deepTagMDWcq);
   fChain->SetBranchAddress("FatJet_deepTagMDWqq", FatJet_deepTagMDWqq, &b_FatJet_deepTagMDWqq);
   fChain->SetBranchAddress("FatJet_deepTagMDZbb", FatJet_deepTagMDZbb, &b_FatJet_deepTagMDZbb);
   fChain->SetBranchAddress("FatJet_deepTagMDZcc", FatJet_deepTagMDZcc, &b_FatJet_deepTagMDZcc);
   fChain->SetBranchAddress("FatJet_deepTagMDZqq", FatJet_deepTagMDZqq, &b_FatJet_deepTagMDZqq);
   fChain->SetBranchAddress("FatJet_deepTagQCDbb", FatJet_deepTagQCDbb, &b_FatJet_deepTagQCDbb);
   fChain->SetBranchAddress("FatJet_deepTagQCDcc", FatJet_deepTagQCDcc, &b_FatJet_deepTagQCDcc);
   fChain->SetBranchAddress("FatJet_deepTagWcq", FatJet_deepTagWcq, &b_FatJet_deepTagWcq);
   fChain->SetBranchAddress("FatJet_deepTagWqq", FatJet_deepTagWqq, &b_FatJet_deepTagWqq);
   fChain->SetBranchAddress("FatJet_deepTagZbb", FatJet_deepTagZbb, &b_FatJet_deepTagZbb);
   fChain->SetBranchAddress("FatJet_deepTagZcc", FatJet_deepTagZcc, &b_FatJet_deepTagZcc);
   fChain->SetBranchAddress("FatJet_deepTagZqq", FatJet_deepTagZqq, &b_FatJet_deepTagZqq);
   fChain->SetBranchAddress("FatJet_eta", FatJet_eta, &b_FatJet_eta);
   fChain->SetBranchAddress("FatJet_lsf3", FatJet_lsf3, &b_FatJet_lsf3);
   fChain->SetBranchAddress("FatJet_mass", FatJet_mass, &b_FatJet_mass);
   fChain->SetBranchAddress("FatJet_msoftdrop", FatJet_msoftdrop, &b_FatJet_msoftdrop);
   fChain->SetBranchAddress("FatJet_n2b1", FatJet_n2b1, &b_FatJet_n2b1);
   fChain->SetBranchAddress("FatJet_n3b1", FatJet_n3b1, &b_FatJet_n3b1);
   fChain->SetBranchAddress("FatJet_phi", FatJet_phi, &b_FatJet_phi);
   fChain->SetBranchAddress("FatJet_pt", FatJet_pt, &b_FatJet_pt);
   fChain->SetBranchAddress("FatJet_rawFactor", FatJet_rawFactor, &b_FatJet_rawFactor);
   fChain->SetBranchAddress("FatJet_rawmsoftdrop", FatJet_rawmsoftdrop, &b_FatJet_rawmsoftdrop);
   fChain->SetBranchAddress("FatJet_tau1", FatJet_tau1, &b_FatJet_tau1);
   fChain->SetBranchAddress("FatJet_tau2", FatJet_tau2, &b_FatJet_tau2);
   fChain->SetBranchAddress("FatJet_tau3", FatJet_tau3, &b_FatJet_tau3);
   fChain->SetBranchAddress("FatJet_tau4", FatJet_tau4, &b_FatJet_tau4);
   fChain->SetBranchAddress("FatJet_electronIdx3SJ", FatJet_electronIdx3SJ, &b_FatJet_electronIdx3SJ);
   fChain->SetBranchAddress("FatJet_idLep", FatJet_idLep, &b_FatJet_idLep);
   fChain->SetBranchAddress("FatJet_jetId", FatJet_jetId, &b_FatJet_jetId);
   fChain->SetBranchAddress("FatJet_muonIdx3SJ", FatJet_muonIdx3SJ, &b_FatJet_muonIdx3SJ);
   fChain->SetBranchAddress("FatJet_nBHadrons", FatJet_nBHadrons, &b_FatJet_nBHadrons);
   fChain->SetBranchAddress("FatJet_nCHadrons", FatJet_nCHadrons, &b_FatJet_nCHadrons);
   fChain->SetBranchAddress("FatJet_nPFConstituents", FatJet_nPFConstituents, &b_FatJet_nPFConstituents);
   fChain->SetBranchAddress("FatJet_subJetIdx1", FatJet_subJetIdx1, &b_FatJet_subJetIdx1);
   fChain->SetBranchAddress("FatJet_subJetIdx2", FatJet_subJetIdx2, &b_FatJet_subJetIdx2);
   fChain->SetBranchAddress("FatJet_Hmatch", FatJet_Hmatch, &b_FatJet_Hmatch);
   fChain->SetBranchAddress("FatJet_HgenIdx", FatJet_HgenIdx, &b_FatJet_HgenIdx);
   fChain->SetBranchAddress("FatJet_HminDR", FatJet_HminDR, &b_FatJet_HminDR);
   fChain->SetBranchAddress("hh_pt", &hh_pt, &b_hh_pt);
   fChain->SetBranchAddress("hh_eta", &hh_eta, &b_hh_eta);
   fChain->SetBranchAddress("hh_phi", &hh_phi, &b_hh_phi);
   fChain->SetBranchAddress("hh_mass", &hh_mass, &b_hh_mass);
   fChain->SetBranchAddress("hh_gen_pt", &hh_gen_pt, &b_hh_gen_pt);
   fChain->SetBranchAddress("hh_gen_eta", &hh_gen_eta, &b_hh_gen_eta);
   fChain->SetBranchAddress("hh_gen_phi", &hh_gen_phi, &b_hh_gen_phi);
   fChain->SetBranchAddress("hh_gen_mass", &hh_gen_mass, &b_hh_gen_mass);
   fChain->SetBranchAddress("weight", &weight, &b_weight);
   Notify();
}

Bool_t hh::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void hh::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t hh::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef hh_cxx
