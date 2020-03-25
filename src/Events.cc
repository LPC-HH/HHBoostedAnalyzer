#define Events_cxx
#include <iostream>
#include <vector>
//LOCAL
#include "Events.hh"
//ROOT
#include <TFile.h>
#include <TH1F.h>
#include <TLorentzVector.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>


void Events::CreateOutputTree()
{
  tree_out = new TTree("hh", "hh");

  //define event output branches;
  tree_out->Branch("run",               &run,     "run/i");      //run number
  tree_out->Branch("luminosityBlock",   &luminosityBlock,     "luminosityBlock/i");      //lumi
  tree_out->Branch("event",             &event,     "event/l");      //event number
  tree_out->Branch("ChsMET_phi",        &ChsMET_phi,     "ChsMET_phi/F");      //
  tree_out->Branch("ChsMET_pt",         &ChsMET_pt,     "ChsMET_pt/F");      //
  tree_out->Branch("ChsMET_sumEt",      &ChsMET_sumEt,     "ChsMET_sumEt/F");      //
  //tree_out->Branch("",      &,     "[nFatJet]/I");      //
  //tree_out->Branch("",      &,     "/");      //

  //define hh-gen-level
  tree_out->Branch("h_gen_pt",       h_gen_pt,      "h_gen_pt[2]/F");      //
  tree_out->Branch("h_gen_eta",      h_gen_eta,     "h_gen_eta[2]/F");      //
  tree_out->Branch("h_gen_phi",      h_gen_phi,     "h_gen_phi[2]/F");      //
  
  //index to fatjet in hh candidate
  tree_out->Branch("hh_fatjet_idx",   hh_fatjet_idx, "hh_fatjet_idx[2]/i");
  
  //define fat-jet variables
  tree_out->Branch("nFatJet",      &nFatJet,     "nFatJet/i");      //
  tree_out->Branch("FatJet_LSmsoftdrop",      FatJet_LSmsoftdrop,     "FatJet_LSmsoftdrop[nFatJet]/F");      //
  tree_out->Branch("FatJet_LSn2b1",      FatJet_LSn2b1,     "FatJet_LSn2b1[nFatJet]/F");      //
  tree_out->Branch("FatJet_LSn3b1",      FatJet_LSn3b1,     "FatJet_LSn3b1[nFatJet]/F");      //
  tree_out->Branch("FatJet_LSpt",      FatJet_LSpt,     "FatJet_LSpt[nFatJet]/F");      //
  tree_out->Branch("FatJet_LSrawmsoftdrop",      FatJet_LSrawmsoftdrop,     "FatJet_LSrawmsoftdrop[nFatJet]/F");      //
  tree_out->Branch("FatJet_LSsubJet1btagDeepB",      FatJet_LSsubJet1btagDeepB,     "FatJet_LSsubJet1btagDeepB[nFatJet]/F");      //
  tree_out->Branch("FatJet_LSsubJet2btagDeepB",      FatJet_LSsubJet2btagDeepB,     "FatJet_LSsubJet2btagDeepB[nFatJet]/F");      //
  tree_out->Branch("FatJet_LStau1",      FatJet_LStau1,     "FatJet_LStau1[nFatJet]/F");      //
  tree_out->Branch("FatJet_LStau2",      FatJet_LStau2,     "FatJet_LStau2[nFatJet]/F");      //
  tree_out->Branch("FatJet_LStau3",      FatJet_LStau3,     "FatJet_LStau3[nFatJet]/F");      //
  tree_out->Branch("FatJet_LStau4",      FatJet_LStau4,     "FatJet_LStau4[nFatJet]/F");      //
  tree_out->Branch("FatJet_area",      FatJet_area,     "FatJet_area[nFatJet]/F");      //
  tree_out->Branch("FatJet_btagDDBvL",      FatJet_btagDDBvL,     "FatJet_btagDDBvL[nFatJet]/F");      //
  tree_out->Branch("FatJet_btagDDCvB",      FatJet_btagDDCvB,     "FatJet_btagDDCvB[nFatJet]/F");      //
  tree_out->Branch("FatJet_btagDDCvL",      FatJet_btagDDCvL,     "FatJet_btagDDCvL[nFatJet]/F");      //
  tree_out->Branch("FatJet_btagHbb",      FatJet_btagHbb,     "FatJet_btagHbb[nFatJet]/F");      //
  tree_out->Branch("FatJet_dRLep",      FatJet_btagHbb,     "FatJet_btagHbb[nFatJet]/F");      //
  tree_out->Branch("FatJet_deepTagHbb",      FatJet_deepTagHbb,     "FatJet_deepTagHbb[nFatJet]/F");      //
  tree_out->Branch("FatJet_deepTagHcc",      FatJet_deepTagHcc,     "FatJet_deepTagHcc[nFatJet]/F");      //
  tree_out->Branch("FatJet_deepTagHqqqq",      FatJet_deepTagHqqqq,     "FatJet_deepTagHqqqq[nFatJet]/F");      //
  tree_out->Branch("FatJet_deepTagMDHbb",      FatJet_deepTagMDHbb,     "FatJet_deepTagMDHbb[nFatJet]/F");      //
  tree_out->Branch("FatJet_deepTagMDHcc",      FatJet_deepTagMDHcc,     "FatJet_deepTagMDHcc[nFatJet]/F");      //
  tree_out->Branch("FatJet_deepTagMDHqqqq",      FatJet_deepTagMDHqqqq,     "FatJet_deepTagMDHqqqq[nFatJet]/F");      //
  tree_out->Branch("FatJet_deepTagMDQCDbb",      FatJet_deepTagMDQCDbb,     "FatJet_deepTagMDQCDbb[nFatJet]/F");      //
  tree_out->Branch("FatJet_deepTagMDQCDcc",      FatJet_deepTagMDQCDcc,     "FatJet_deepTagMDQCDcc[nFatJet]/F");      //
  tree_out->Branch("FatJet_deepTagMDWcq",      FatJet_deepTagMDWcq,     "FatJet_deepTagMDWcq[nFatJet]/F");      //
  tree_out->Branch("FatJet_deepTagMDWqq",      FatJet_deepTagMDWqq,     "FatJet_deepTagMDWqq[nFatJet]/F");      //
  tree_out->Branch("FatJet_deepTagMDZbb",      FatJet_deepTagMDZbb,     "FatJet_deepTagMDZbb[nFatJet]/F");      //
  tree_out->Branch("FatJet_deepTagMDZcc",      FatJet_deepTagMDZcc,     "FatJet_deepTagMDZcc[nFatJet]/F");      //
  tree_out->Branch("FatJet_deepTagMDZqq",      FatJet_deepTagMDZqq,     "FatJet_deepTagMDZqq[nFatJet]/F");      //
  tree_out->Branch("FatJet_deepTagQCDbb",      FatJet_deepTagQCDbb,     "FatJet_deepTagQCDbb[nFatJet]/F");      //
  tree_out->Branch("FatJet_deepTagQCDcc",      FatJet_deepTagQCDcc,     "FatJet_deepTagQCDcc[nFatJet]/F");      //
  tree_out->Branch("FatJet_deepTagWcq",      FatJet_deepTagWcq,     "FatJet_deepTagWcq[nFatJet]/F");      //
  tree_out->Branch("FatJet_deepTagWqq",      FatJet_deepTagWqq,     "FatJet_deepTagWqq[nFatJet]/F");      //
  tree_out->Branch("FatJet_deepTagZbb",      FatJet_deepTagZbb,     "FatJet_deepTagZbb[nFatJet]/F");      //
  tree_out->Branch("FatJet_deepTagZcc",      FatJet_deepTagZcc,     "FatJet_deepTagZcc[nFatJet]/F");      //
  tree_out->Branch("FatJet_deepTagZqq",      FatJet_deepTagZqq,     "FatJet_deepTagZqq[nFatJet]/F");      //
  tree_out->Branch("FatJet_eta",      FatJet_eta,     "FatJet_eta[nFatJet]/F");      //
  tree_out->Branch("FatJet_lsf3",      FatJet_lsf3,     "FatJet_lsf3[nFatJet]/F");      //
  tree_out->Branch("FatJet_mass",      FatJet_mass,     "FatJet_mass[nFatJet]/F");      //
  tree_out->Branch("FatJet_msoftdrop",      FatJet_msoftdrop,     "FatJet_msoftdrop[nFatJet]/F");      //
  tree_out->Branch("FatJet_n2b1",      FatJet_n2b1,     "FatJet_n2b1[nFatJet]/F");      //
  tree_out->Branch("FatJet_n3b1",      FatJet_n3b1,     "FatJet_n3b1[nFatJet]/F");      //
  tree_out->Branch("FatJet_phi",      FatJet_phi,     "FatJet_phi[nFatJet]/F");      //
  tree_out->Branch("FatJet_pt",      FatJet_pt,     "FatJet_pt[nFatJet]/F");      //
  tree_out->Branch("FatJet_rawFactor",      FatJet_rawFactor,     "FatJet_rawFactor[nFatJet]/F");      //
  tree_out->Branch("FatJet_rawmsoftdrop",      FatJet_rawmsoftdrop,     "FatJet_rawmsoftdrop[nFatJet]/F");      //
  tree_out->Branch("FatJet_tau1",      FatJet_tau1,     "FatJet_tau1[nFatJet]/F");      //
  tree_out->Branch("FatJet_tau2",      FatJet_tau2,     "FatJet_tau2[nFatJet]/F");      //
  tree_out->Branch("FatJet_tau3",      FatJet_tau3,     "FatJet_tau3[nFatJet]/F");      //
  tree_out->Branch("FatJet_tau4",      FatJet_tau4,     "FatJet_tau4[nFatJet]/F");      //
  tree_out->Branch("FatJet_electronIdx3SJ",      FatJet_electronIdx3SJ,     "FatJet_electronIdx3SJ[nFatJet]/I");      //
  tree_out->Branch("FatJet_idLep",      FatJet_idLep,     "FatJet_idLep[nFatJet]/I");      //
  tree_out->Branch("FatJet_jetId",      FatJet_jetId,     "FatJet_jetId[nFatJet]/I");      //
  tree_out->Branch("FatJet_muonIdx3SJ",      FatJet_muonIdx3SJ,     "FatJet_muonIdx3SJ[nFatJet]/I");      //
  tree_out->Branch("FatJet_nBHadrons",      FatJet_nBHadrons,     "FatJet_nBHadrons[nFatJet]/I");      //
  tree_out->Branch("FatJet_nCHadrons",      FatJet_nCHadrons,     "FatJet_nCHadrons[nFatJet]/I");      //
  tree_out->Branch("FatJet_nPFConstituents",      FatJet_nPFConstituents,     "FatJet_nPFConstituents[nFatJet]/I");      //
  tree_out->Branch("FatJet_subJetIdx1",      FatJet_subJetIdx1,     "FatJet_subJetIdx1[nFatJet]/I");      //
  tree_out->Branch("FatJet_subJetIdx2",      FatJet_subJetIdx2,     "FatJet_subJetIdx2[nFatJet]/I");      //
  tree_out->Branch("FatJet_Hmatch",      FatJet_Hmatch,     "FatJet_Hmatch[nFatJet]/O");
  tree_out->Branch("FatJet_HgenIdx",      FatJet_HgenIdx,     "FatJet_HgenIdx[nFatJet]/I");
  tree_out->Branch("FatJet_HminDR",      FatJet_HminDR,     "FatJet_HminDR[nFatJet]/F");

  //triggers -- directly from Events TTree
  tree_out->Branch("HLT_PFHT1050",                                        &HLT_PFHT1050,                                       "HLT_PFHT1050/O");
  tree_out->Branch("HLT_AK8PFJet360_TrimMass30",                          &HLT_AK8PFJet360_TrimMass30,                         "HLT_AK8PFJet360_TrimMass30/O");
  tree_out->Branch("HLT_AK8PFJet380_TrimMass30",                          &HLT_AK8PFJet380_TrimMass30,                         "HLT_AK8PFJet380_TrimMass30/O");
  tree_out->Branch("HLT_AK8PFJet400_TrimMass30",                          &HLT_AK8PFJet400_TrimMass30,                         "HLT_AK8PFJet400_TrimMass30/O");
  tree_out->Branch("HLT_AK8PFJet420_TrimMass30",                          &HLT_AK8PFJet420_TrimMass30,                         "HLT_AK8PFJet420_TrimMass30/O");
  tree_out->Branch("HLT_AK8PFHT800_TrimMass50",                           &HLT_AK8PFHT800_TrimMass50,                          "HLT_AK8PFHT800_TrimMass50/O");
  tree_out->Branch("HLT_PFJet500",                                        &HLT_PFJet500,                                       "HLT_PFJet500/O");
  tree_out->Branch("HLT_AK8PFJet500",                                     &HLT_AK8PFJet500,                                    "HLT_AK8PFJet500/O");
  tree_out->Branch("HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17",     &HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17,    "HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17/O");
  tree_out->Branch("HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1",      &HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1,     "HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1/O");
  tree_out->Branch("HLT_AK8PFJet330_PFAK8BTagCSV_p17",                    &HLT_AK8PFJet330_PFAK8BTagCSV_p17,                   "HLT_AK8PFJet330_PFAK8BTagCSV_p17/O");
  //tree_out->Branch("",      &,     "/O");
  //tree_out->Branch("",      &,     "/O");
  //tree_out->Branch("",      &,     "/O");

  //hh candidate info
  tree_out->Branch("hh_pt",      &hh_pt,     "hh_pt/F");
  tree_out->Branch("hh_eta",     &hh_eta,    "hh_eta/F");
  tree_out->Branch("hh_phi",     &hh_phi,    "hh_phi/F");
  tree_out->Branch("hh_mass",    &hh_mass,   "hh_mass/F");
  //
  tree_out->Branch("hh_gen_pt",      &hh_gen_pt,     "hh_gen_pt/F");
  tree_out->Branch("hh_gen_eta",     &hh_gen_eta,    "hh_gen_eta/F");
  tree_out->Branch("hh_gen_phi",     &hh_gen_phi,    "hh_gen_phi/F");
  tree_out->Branch("hh_gen_mass",    &hh_gen_mass,   "hh_gen_mass/F");

};

void Events::ResetOutputTreeVariables()
{
  hh_pt   = -999.;
  hh_eta  = -999.;
  hh_phi  = -999.;
  hh_mass = -999.;
  //
  hh_gen_pt   = -999.;
  hh_gen_eta  = -999.;
  hh_gen_phi  = -999.;
  hh_gen_mass = -999.;
  //
  for(int i = 0; i < 2; i++)
  {
    h_gen_pt[i]  = -999.;
    h_gen_eta[i] = -999.;
    h_gen_phi[i] = -999.;
    hh_fatjet_idx[i] = 999;
  }

  for(int i = 0; i < 100; i++)
  {
    FatJet_HminDR[i] = -999.;
    FatJet_Hmatch[i] = false;
    FatJet_HgenIdx[i] = -1;
  }

}
void Events::Loop()
{
  //   In a ROOT session, you can do:
  //      root> .L Events.C
  //      root> Events t
  //      root> t.GetEntry(12); // Fill t data members with entry number 12
  //      root> t.Show();       // Show values of entry 12
  //      root> t.Show(16);     // Read and show values of entry 16
  //      root> t.Loop();       // Loop on all entries
  //

  //     This is the loop skeleton where:
  //    jentry is the global entry number in the chain
  //    ientry is the entry number in the current Tree
  //  Note that the argument to GetEntry must be:
  //    jentry for TChain::GetEntry
  //    ientry for TTree::GetEntry and TBranch::GetEntry
  //
  //       To read only selected branches, Insert statements like:
  // METHOD1:
  //    fChain->SetBranchStatus("*",0);  // disable all branches
  //    fChain->SetBranchStatus("branchname",1);  // activate branchname
  // METHOD2: replace line
  //    fChain->GetEntry(jentry);       //read all branches
  //by  b_branchname->GetEntry(ientry); //read only this branch
  this->CreateOutputTree();
  TH1F* h_h1_pt = new TH1F("h1_pt", "h1_pt", 100, 0, 1000 );
  TH1F* h_h2_pt = new TH1F("h2_pt", "h2_pt", 100, 0, 1000 );
  TH2F* h_h1_h2_pt = new TH2F("h1_h2_pt","h1_h2_pt", 100, 0, 1000, 100, 0, 1000);

  //-------------------------------------
  //Normalization histograms
  //------------------------------------
  TH1F* NEvents = new TH1F("NEvents", "NEvents", 1, 0, 1);
  TH1F* NEvents_genweight = new TH1F("NEvents_genweight", "NEvents_genweight", 1, 0, 1);

  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++)
  {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    NEvents->Fill( 0.5, 1.0 );
    NEvents_genweight->Fill(0.5, genWeight);


    // if (Cut(ientry) < 0) continue;
    //std::cout << ientry << std::endl;
    this->ResetOutputTreeVariables();
    //std::cout << "============H_GEN===============" << std::endl;
    //------------------------------
    //----find gen-higgs------------
    //------------------------------
    int current_mIndex = -1;
    std::vector< TLorentzVector > h_vector;
    for(int i = 0; i < nGenPart; i++)
    {
      if( abs(GenPart_pdgId[i]) == 5  && GenPart_pdgId[GenPart_genPartIdxMother[i]] == 25 && current_mIndex != GenPart_genPartIdxMother[i] )
      {
        //std::cout << GenPart_genPartIdxMother[i] << std::endl;
        // std::cout << "mother: " << GenPart_pdgId[GenPart_genPartIdxMother[i]]
        // << " PT: " << GenPart_pt[GenPart_genPartIdxMother[i]]
        // << " eta: " << GenPart_eta[GenPart_genPartIdxMother[i]]
        // << " phi: " << GenPart_phi[GenPart_genPartIdxMother[i]] << std::endl;
        TLorentzVector h;
        h.SetPtEtaPhiM( GenPart_pt[GenPart_genPartIdxMother[i]], GenPart_eta[GenPart_genPartIdxMother[i]], GenPart_phi[GenPart_genPartIdxMother[i]], GenPart_mass[GenPart_genPartIdxMother[i]] );
        h_vector.push_back(h);
        current_mIndex = GenPart_genPartIdxMother[i];
      }
    }

    if(h_vector.size() > 1)
    {
      h_h1_pt->Fill(h_vector.at(0).Pt());
      h_h2_pt->Fill(h_vector.at(1).Pt());
      h_h1_h2_pt->Fill(h_vector.at(0).Pt(), h_vector.at(1).Pt());
    }
    //------------------------------
    //-------find fatJet------------
    //------------------------------
    //std::cout << "======================" << std::endl;
    for(unsigned int i = 0; i < nFatJet; i++ )
    {
      TLorentzVector tmp_fatJet;
      tmp_fatJet.SetPtEtaPhiM(FatJet_pt[i],FatJet_eta[i],FatJet_phi[i],FatJet_msoftdrop[i]);
      float minDR = 999.;
      int match_idx = -1;
      for( int j = 0; j < h_vector.size(); j++)
      {
        if(tmp_fatJet.DeltaR(h_vector.at(j)) < minDR)
        {
          minDR = tmp_fatJet.DeltaR(h_vector.at(j));
          match_idx = j;
        }
      }

      FatJet_HminDR[i] = minDR;
      if(FatJet_HminDR[i] < 0.4)
      {
        FatJet_Hmatch[i] = true;
        FatJet_HgenIdx[i] = match_idx;
      }
      //FatJet_Hmatch[i] = true;
      // std::cout << "FatJet_deepTagHbb: " << FatJet_deepTagHbb[i] <<
      // "; pT: " << FatJet_pt[i] << " eta: " <<  FatJet_eta[i]
      // << " phi: " << FatJet_phi[i]
      // << "; FatJet_nBHadrons: " << FatJet_nBHadrons[i] <<
      // "; mass: " << FatJet_mass[i] << "; minDR:" << minDR << std::endl;
    }

    //-----------------------------
    //----------get hh cand -------
    //-----------------------------
    double sum_hh_pt = 0;
    TLorentzVector hh_candidate(0,0,0,0);
    unsigned int hh_candidate_idx1 = -1;
    unsigned int hh_candidate_idx2 = -1;
    for( int i  = 0; i < nFatJet; i++ )
    {
      for(int j = i+1; j < nFatJet; j++)
      {
        if ( FatJet_pt[i] + FatJet_pt[j] > sum_hh_pt)//pick hh candite with largest scalar PT sum
        {
          sum_hh_pt = FatJet_pt[i] + FatJet_pt[j];
          //h1
          TLorentzVector h1;
          h1.SetPtEtaPhiM(FatJet_pt[i],FatJet_eta[i],FatJet_phi[i],FatJet_msoftdrop[i]);
          //h2
          TLorentzVector h2;
          h2.SetPtEtaPhiM(FatJet_pt[j],FatJet_eta[j],FatJet_phi[j],FatJet_msoftdrop[j]);
          hh_candidate = h1+h2;
	  hh_candidate_idx1 = i;
	  hh_candidate_idx2 = j;
        }

      }
    }

    if(h_vector.size() > 1)
    {
      //filling tree_out variables
      this->h_gen_pt[0] = h_vector.at(0).Pt();
      this->h_gen_eta[0] = h_vector.at(0).Eta();
      this->h_gen_phi[0] = h_vector.at(0).Phi();
      //
      this->h_gen_pt[1] = h_vector.at(1).Pt();
      this->h_gen_eta[1] = h_vector.at(1).Eta();
      this->h_gen_phi[1] = h_vector.at(1).Phi();
    }
    //filling hh candidate variable
    this->hh_pt   = hh_candidate.Pt();
    this->hh_eta  = hh_candidate.Eta();
    this->hh_phi  = hh_candidate.Phi();
    this->hh_mass = hh_candidate.M();
    this->hh_fatjet_idx[0] = hh_candidate_idx1;
    this->hh_fatjet_idx[1] = hh_candidate_idx2;
    //gen level
    if(h_vector.size() > 1)
    {
      this->hh_gen_pt   = (h_vector.at(0)+h_vector.at(1)).Pt();
      this->hh_gen_eta  = (h_vector.at(0)+h_vector.at(1)).Eta();
      this->hh_gen_phi  = (h_vector.at(0)+h_vector.at(1)).Phi();
      this->hh_gen_mass = (h_vector.at(0)+h_vector.at(1)).M();
    }
    

    //------------------------------
    //apply skimming
    //-----------------------------
    if( !(HLT_AK8PFJet360_TrimMass30 || HLT_AK8PFJet400_TrimMass30 || HLT_AK8PFJet420_TrimMass30) ) continue;
    
    if ( !(this->hh_pt > 0.0 && FatJet_pt[this->hh_fatjet_idx[0]] > this->fatjet_pt_trh && FatJet_pt[this->hh_fatjet_idx[1]] > this->fatjet_pt_trh) ) continue;

    this->tree_out->Fill();
  }

  TFile* fout = new TFile( fout_name.c_str(), "recreate");
  //h_h1_pt->Write();
  //h_h2_pt->Write();
  //h_h1_h2_pt->Write();
  NEvents->Write();
  NEvents_genweight->Write();
  tree_out->Write();
}
