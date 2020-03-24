#define hh_cxx
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

//LOCAL
#include <hh_tree.hh>

void hh::Loop()
{
//   In a ROOT session, you can do:
//      root> .L hh.C
//      root> hh t
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
  
  TH1F* h_j1_mass = new TH1F("h_j1_mass", "h_j1_mass", 100, 0, 1000);
  TH1F* h_j2_mass = new TH1F("h_j2_mass", "h_j2_mass", 100, 0, 1000);

  TH1F* h_j1_pt = new TH1F("h_j1_pt", "h_j1_pt", 100, 0, 1000);
  TH1F* h_j2_pt = new TH1F("h_j2_pt", "h_j2_pt", 100, 0, 1000);
  
  TH1F* h_j1_eta = new TH1F("h_j1_eta", "h_j1_eta", 50, -3.0, 3.0);
  TH1F* h_j2_eta = new TH1F("h_j2_eta", "h_j2_eta", 50, -3.0, 3.0);
  
  TH1F* h_j1_phi = new TH1F("h_j1_phi", "h_j1_phi", 50, -3.1416, 3.1416);
  TH1F* h_j2_phi = new TH1F("h_j2_phi", "h_j2_phi", 50, -3.1416, 3.1416);
  
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      
      //if( !(FatJet_btagDDBvL[0]>0.8 && FatJet_btagDDBvL[1]>0.8 && FatJet_pt[0]>300. && FatJet_pt[1]>300. && FatJet_msoftdrop[1]>100. && FatJet_msoftdrop[1]<160. && FatJet_msoftdrop[0]>100. && FatJet_msoftdrop[0]<160.)) continue;

      
      if( this->process == "data" || this->process == "Data" || this->process == "DATA")
	{
	  this->global_weight = 1.0;
	}
      else
	{
	  this->global_weight = this->weight*this->lumi;
	}
      
      if( !(FatJet_msoftdrop[0]>100. && FatJet_msoftdrop[0]<160.) ) h_j1_mass->Fill(FatJet_msoftdrop[0], this->global_weight);
      if( !(FatJet_msoftdrop[1]>100. && FatJet_msoftdrop[1]<160.) ) h_j2_mass->Fill(FatJet_msoftdrop[1], this->global_weight);
      

      h_j1_pt->Fill(FatJet_pt[0], this->global_weight);
      h_j2_pt->Fill(FatJet_pt[1], this->global_weight);

      h_j1_eta->Fill(FatJet_eta[0], this->global_weight);
      h_j2_eta->Fill(FatJet_eta[1], this->global_weight);

      h_j1_phi->Fill(FatJet_phi[0], this->global_weight);
      h_j2_phi->Fill(FatJet_phi[1], this->global_weight);
   }

   TFile* out = new TFile(fout_name.c_str(), "recreate");
   
   h_j1_mass->Write();
   h_j2_mass->Write();
   
   h_j1_pt->Write();
   h_j2_pt->Write();

   h_j1_eta->Write();
   h_j2_eta->Write();

   h_j1_phi->Write();
   h_j2_phi->Write();
   
   out->Close();
}
