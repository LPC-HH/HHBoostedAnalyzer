#ifndef JetTree_H
#define JetTree_H

#include "TFile.h"
#include "TTree.h"
#include "TError.h"
#include <cmath>
#include "assert.h"

  class JetTree {

    public:      

      /// variables
      Float_t         weight;
      UInt_t          run;
      UInt_t          lumi;
      UInt_t          event;
      Float_t         Rho; 
      Float_t         NVertices; 
      Float_t         LSmsoftdrop;
      Float_t         LSn2b1;
      Float_t         LSn3b1;
      Float_t         LSpt;
      Float_t         LSrawmsoftdrop;
      Float_t         LSsubJet1btagDeepB;
      Float_t         LSsubJet2btagDeepB;
      Float_t         LStau1;
      Float_t         LStau2;
      Float_t         LStau3;
      Float_t         LStau4;
      Float_t         area;
      Float_t         btagDDBvL;
      Float_t         btagDDCvB;
      Float_t         btagDDCvL;
      Float_t         btagHbb;
      Float_t         dRLep;
      Float_t         deepTagHbb;
      Float_t         deepTagHcc;
      Float_t         deepTagHqqqq;
      Float_t         deepTagMDHbb;
      Float_t         deepTagMDHcc;
      Float_t         deepTagMDHqqqq;
      Float_t         deepTagMDQCDbb;
      Float_t         deepTagMDQCDcc;
      Float_t         deepTagMDWcq;
      Float_t         deepTagMDWqq;
      Float_t         deepTagMDZbb;
      Float_t         deepTagMDZcc;
      Float_t         deepTagMDZqq;
      Float_t         deepTagQCDbb;
      Float_t         deepTagQCDcc;
      Float_t         deepTagWcq;
      Float_t         deepTagWqq;
      Float_t         deepTagZbb;
      Float_t         deepTagZcc;
      Float_t         deepTagZqq;
      Float_t         eta;
      Float_t         lsf3;
      Float_t         mass;
      Float_t         msoftdrop;
      Float_t         n2b1;
      Float_t         n3b1;
      Float_t         phi;
      Float_t         pt;
      Float_t         rawFactor;
      Float_t         rawmsoftdrop;
      Float_t         tau1;
      Float_t         tau2;
      Float_t         tau3;
      Float_t         tau4;
      Int_t           electronIdx3SJ;
      Int_t           idLep;
      Int_t           jetId;
      Int_t           muonIdx3SJ;
      Int_t           nBHadrons;
      Int_t           nCHadrons;
      Int_t           nPFConstituents;
      Int_t           subJetIdx1;
      Int_t           subJetIdx2;
      Bool_t          Hmatch;
      Int_t           HgenIdx;
      Float_t         HminDR;
      Bool_t          matchedToHbb;
      Bool_t          matchedToHWWqqqq;
      Bool_t          matchedToHWWlnuqq;
      Bool_t          matchedToHZZqqqq;
      Float_t         matchedGenMass;
      Float_t         matchedGenPt;
      Float_t         matchedGenEta;
      Float_t         matchedGenPhi;

    public:
      /// this is the main element
      TTree *tree_;
      TFile *f_;
  
      /// hold the names of variables to facilitate things (filled during Init)
      std::vector<std::string> variables_;

      /// default constructor  
      JetTree()  {};
      /// default destructor
      ~JetTree(){ 
        if (f_) f_->Close();  
      };
    
      /// initialize varibles and fill list of available variables
      void InitVariables() {
        weight			           = 0.0;
        run    		                   = 0.0;
        lumi	                           = 0.0;
        event		                   = 0.0;
        Rho  			           = 0.0;
        NVertices 		           = 0.0;
	LSmsoftdrop 		           = -999;
	LSn2b1 		                   = -999;
	LSn3b1 		                   = -999;
	LSpt 		                   = -999;
	LSrawmsoftdrop 		           = -999;
	LSsubJet1btagDeepB 		   = -999;
	LSsubJet2btagDeepB 		   = -999;
	LStau1 		                   = -999;
	LStau2 		                   = -999;
	LStau3 		                   = -999;
	LStau4 		                   = -999;
	area 		                   = -999;
	btagDDBvL 		           = -999;
	btagDDCvB 		           = -999;
	btagDDCvL 		           = -999;
	btagHbb 		           = -999;
	dRLep 		                   = -999;
	deepTagHbb 		           = -999;
	deepTagHcc 		           = -999;
	deepTagHqqqq 		           = -999;
	deepTagMDHbb 		           = -999;
	deepTagMDHcc 		           = -999;
	deepTagMDHqqqq 		           = -999;
	deepTagMDQCDbb 		           = -999;
	deepTagMDQCDcc 		           = -999;
	deepTagMDWcq 		           = -999;
	deepTagMDWqq 		           = -999;
	deepTagMDZbb 		           = -999;
	deepTagMDZcc 		           = -999;
	deepTagMDZqq 		           = -999;
	deepTagQCDbb 		           = -999;
	deepTagQCDcc 		           = -999;
	deepTagWcq 		           = -999;
	deepTagWqq 		           = -999;
	deepTagZbb 		           = -999;
	deepTagZcc 		           = -999;
	deepTagZqq 		           = -999;
	eta 		                   = -999;
	lsf3 		                   = -999;
	mass 		                   = -999;
	msoftdrop 		           = -999;
	n2b1 		                   = -999;
	n3b1 		                   = -999;
	phi 		                   = -999;
	pt 		                   = -999;
	rawFactor 		           = -999;
	rawmsoftdrop 		           = -999;
	tau1 		                   = -999;
	tau2 		                   = -999;
	tau3 		                   = -999;
	tau4 		                   = -999;
	electronIdx3SJ 		           = -999;
	idLep 		                   = -999;
	jetId 		                   = -999;
	muonIdx3SJ 		           = -999;
	nBHadrons 		           = -999;
	nCHadrons 		           = -999;
	nPFConstituents 		   = -999;
	subJetIdx1 		           = -999;
	subJetIdx2 		           = -999;
	Hmatch 		                   = -999;
	HgenIdx 		           = -999;
	HminDR 		                   = -999;
	matchedToHbb                       = 0;
	matchedToHWWqqqq                   = 0;
	matchedToHWWlnuqq                  = 0;
	matchedToHZZqqqq                   = 0;
	matchedGenMass                     = -999;
	matchedGenPt                       = -999;
	matchedGenEta                      = -999;
	matchedGenPhi                      = -999;
      }
    
      /// load a JetTree
      void LoadTree(const char* file){
        f_ = TFile::Open(file);
        assert(f_);
        tree_ = dynamic_cast<TTree*>(f_->Get("Jets"));
        assert(tree_);
      }
    
      /// create a JetTree
      void CreateTree(){
        tree_ = new TTree("Jets","Jets");
        f_ = 0;

        //book the branches
        tree_->Branch("weight",&weight,"weight/F");
        tree_->Branch("run",&run,"run/i");
        tree_->Branch("lumi",&lumi,"lumi/i");
        tree_->Branch("event",&event,"event/i"); 
        tree_->Branch("rho",&Rho,"rho/F"); 
        tree_->Branch("vertices",&NVertices,"vertices/F"); 
	tree_->Branch("LSmsoftdrop",&LSmsoftdrop,"LSmsoftdrop/F");
	tree_->Branch("LSn2b1",&LSn2b1,"LSn2b1/F");
	tree_->Branch("LSn3b1",&LSn3b1,"LSn3b1/F");
	tree_->Branch("LSpt",&LSpt,"LSpt/F");
	tree_->Branch("LSrawmsoftdrop",&LSrawmsoftdrop,"LSrawmsoftdrop/F");
	tree_->Branch("LSsubJet1btagDeepB",&LSsubJet1btagDeepB,"LSsubJet1btagDeepB/F");
	tree_->Branch("LSsubJet2btagDeepB",&LSsubJet2btagDeepB,"LSsubJet2btagDeepB/F");
	tree_->Branch("LStau1",&LStau1,"LStau1/F");
	tree_->Branch("LStau2",&LStau2,"LStau2/F");
	tree_->Branch("LStau3",&LStau3,"LStau3/F");
	tree_->Branch("LStau4",&LStau4,"LStau4/F");
	tree_->Branch("area",&area,"area/F");
	tree_->Branch("btagDDBvL",&btagDDBvL,"btagDDBvL/F");
	tree_->Branch("btagDDCvB",&btagDDCvB,"btagDDCvB/F");
	tree_->Branch("btagDDCvL",&btagDDCvL,"btagDDCvL/F");
	tree_->Branch("btagHbb",&btagHbb,"btagHbb/F");
	tree_->Branch("dRLep",&dRLep,"dRLep/F");
	tree_->Branch("deepTagHbb",&deepTagHbb,"deepTagHbb/F");
	tree_->Branch("deepTagHcc",&deepTagHcc,"deepTagHcc/F");
	tree_->Branch("deepTagHqqqq",&deepTagHqqqq,"deepTagHqqqq/F");
	tree_->Branch("deepTagMDHbb",&deepTagMDHbb,"deepTagMDHbb/F");
	tree_->Branch("deepTagMDHcc",&deepTagMDHcc,"deepTagMDHcc/F");
	tree_->Branch("deepTagMDHqqqq",&deepTagMDHqqqq,"deepTagMDHqqqq/F");
	tree_->Branch("deepTagMDQCDbb",&deepTagMDQCDbb,"deepTagMDQCDbb/F");
	tree_->Branch("deepTagMDQCDcc",&deepTagMDQCDcc,"deepTagMDQCDcc/F");
	tree_->Branch("deepTagMDWcq",&deepTagMDWcq,"deepTagMDWcq/F");
	tree_->Branch("deepTagMDWqq",&deepTagMDWqq,"deepTagMDWqq/F");
	tree_->Branch("deepTagMDZbb",&deepTagMDZbb,"deepTagMDZbb/F");
	tree_->Branch("deepTagMDZcc",&deepTagMDZcc,"deepTagMDZcc/F");
	tree_->Branch("deepTagMDZqq",&deepTagMDZqq,"deepTagMDZqq/F");
	tree_->Branch("deepTagQCDbb",&deepTagQCDbb,"deepTagQCDbb/F");
	tree_->Branch("deepTagQCDcc",&deepTagQCDcc,"deepTagQCDcc/F");
	tree_->Branch("deepTagWcq",&deepTagWcq,"deepTagWcq/F");
	tree_->Branch("deepTagWqq",&deepTagWqq,"deepTagWqq/F");
	tree_->Branch("deepTagZbb",&deepTagZbb,"deepTagZbb/F");
	tree_->Branch("deepTagZcc",&deepTagZcc,"deepTagZcc/F");
	tree_->Branch("deepTagZqq",&deepTagZqq,"deepTagZqq/F");
	tree_->Branch("eta",&eta,"eta/F");
	tree_->Branch("lsf3",&lsf3,"lsf3/F");
	tree_->Branch("mass",&mass,"mass/F");
	tree_->Branch("msoftdrop",&msoftdrop,"msoftdrop/F");
	tree_->Branch("n2b1",&n2b1,"n2b1/F");
	tree_->Branch("n3b1",&n3b1,"n3b1/F");
	tree_->Branch("phi",&phi,"phi/F");
	tree_->Branch("pt",&pt,"pt/F");
	tree_->Branch("rawFactor",&rawFactor,"rawFactor/F");
	tree_->Branch("rawmsoftdrop",&rawmsoftdrop,"rawmsoftdrop/F");
	tree_->Branch("tau1",&tau1,"tau1/F");
	tree_->Branch("tau2",&tau2,"tau2/F");
	tree_->Branch("tau3",&tau3,"tau3/F");
	tree_->Branch("tau4",&tau4,"tau4/F");
	tree_->Branch("electronIdx3SJ",&electronIdx3SJ,"electronIdx3SJ/F");
	tree_->Branch("idLep",&idLep,"idLep/F");
	tree_->Branch("jetId",&jetId,"jetId/F");
	tree_->Branch("muonIdx3SJ",&muonIdx3SJ,"muonIdx3SJ/F");
	tree_->Branch("nBHadrons",&nBHadrons,"nBHadrons/F");
	tree_->Branch("nCHadrons",&nCHadrons,"nCHadrons/F");
	tree_->Branch("nPFConstituents",&nPFConstituents,"nPFConstituents/F");
	tree_->Branch("subJetIdx1",&subJetIdx1,"subJetIdx1/F");
	tree_->Branch("subJetIdx2",&subJetIdx2,"subJetIdx2/F");
	tree_->Branch("Hmatch",&Hmatch,"Hmatch/F");
	tree_->Branch("HgenIdx",&HgenIdx,"HgenIdx/F");
	tree_->Branch("HminDR",&HminDR,"HminDR/F");
	tree_->Branch("matchedToHbb",&matchedToHbb,"matchedToHbb/O");
	tree_->Branch("matchedToHWWqqqq",&matchedToHWWqqqq,"matchedToHWWqqqq/O");
	tree_->Branch("matchedToHWWlnuqq",&matchedToHWWlnuqq,"matchedToHWWlnuqq/O");
	tree_->Branch("matchedToHZZqqqq",&matchedToHZZqqqq,"matchedToHZZqqqq/O");
 	tree_->Branch("matchedGenMass",&matchedGenMass,"matchedGenMass/F");
 	tree_->Branch("matchedGenPt",&matchedGenPt,"matchedGenPt/F");
 	tree_->Branch("matchedGenEta",&matchedGenEta,"matchedGenEta/F");
 	tree_->Branch("matchedGenPhi",&matchedGenPhi,"matchedGenPhi/F");
     } 

      // initialze a JetTree
      void InitTree(){
        assert(tree_);
        // don't forget to set pointers to zero before you set address
        // or you will fully appreciate that "ROOT sucks" :)
        InitVariables();
        //Set branch address
        Int_t currentState = gErrorIgnoreLevel;

        tree_->SetBranchAddress("weight",&weight);
        tree_->SetBranchAddress("run",&run);
        tree_->SetBranchAddress("lumi",&lumi);
        tree_->SetBranchAddress("event",&event); 
        tree_->SetBranchAddress("rho",&Rho);
        tree_->SetBranchAddress("vertices",&NVertices);
	tree_->SetBranchAddress("LSmsoftdrop",&LSmsoftdrop);
	tree_->SetBranchAddress("LSn2b1",&LSn2b1);
	tree_->SetBranchAddress("LSn3b1",&LSn3b1);
	tree_->SetBranchAddress("LSpt",&LSpt);
	tree_->SetBranchAddress("LSrawmsoftdrop",&LSrawmsoftdrop);
	tree_->SetBranchAddress("LSsubJet1btagDeepB",&LSsubJet1btagDeepB);
	tree_->SetBranchAddress("LSsubJet2btagDeepB",&LSsubJet2btagDeepB);
	tree_->SetBranchAddress("LStau1",&LStau1);
	tree_->SetBranchAddress("LStau2",&LStau2);
	tree_->SetBranchAddress("LStau3",&LStau3);
	tree_->SetBranchAddress("LStau4",&LStau4);
	tree_->SetBranchAddress("area",&area);
	tree_->SetBranchAddress("btagDDBvL",&btagDDBvL);
	tree_->SetBranchAddress("btagDDCvB",&btagDDCvB);
	tree_->SetBranchAddress("btagDDCvL",&btagDDCvL);
	tree_->SetBranchAddress("btagHbb",&btagHbb);
	tree_->SetBranchAddress("dRLep",&dRLep);
	tree_->SetBranchAddress("deepTagHbb",&deepTagHbb);
	tree_->SetBranchAddress("deepTagHcc",&deepTagHcc);
	tree_->SetBranchAddress("deepTagHqqqq",&deepTagHqqqq);
	tree_->SetBranchAddress("deepTagMDHbb",&deepTagMDHbb);
	tree_->SetBranchAddress("deepTagMDHcc",&deepTagMDHcc);
	tree_->SetBranchAddress("deepTagMDHqqqq",&deepTagMDHqqqq);
	tree_->SetBranchAddress("deepTagMDQCDbb",&deepTagMDQCDbb);
	tree_->SetBranchAddress("deepTagMDQCDcc",&deepTagMDQCDcc);
	tree_->SetBranchAddress("deepTagMDWcq",&deepTagMDWcq);
	tree_->SetBranchAddress("deepTagMDWqq",&deepTagMDWqq);
	tree_->SetBranchAddress("deepTagMDZbb",&deepTagMDZbb);
	tree_->SetBranchAddress("deepTagMDZcc",&deepTagMDZcc);
	tree_->SetBranchAddress("deepTagMDZqq",&deepTagMDZqq);
	tree_->SetBranchAddress("deepTagQCDbb",&deepTagQCDbb);
	tree_->SetBranchAddress("deepTagQCDcc",&deepTagQCDcc);
	tree_->SetBranchAddress("deepTagWcq",&deepTagWcq);
	tree_->SetBranchAddress("deepTagWqq",&deepTagWqq);
	tree_->SetBranchAddress("deepTagZbb",&deepTagZbb);
	tree_->SetBranchAddress("deepTagZcc",&deepTagZcc);
	tree_->SetBranchAddress("deepTagZqq",&deepTagZqq);
	tree_->SetBranchAddress("eta",&eta);
	tree_->SetBranchAddress("lsf3",&lsf3);
	tree_->SetBranchAddress("mass",&mass);
	tree_->SetBranchAddress("msoftdrop",&msoftdrop);
	tree_->SetBranchAddress("n2b1",&n2b1);
	tree_->SetBranchAddress("n3b1",&n3b1);
	tree_->SetBranchAddress("phi",&phi);
	tree_->SetBranchAddress("pt",&pt);
	tree_->SetBranchAddress("rawFactor",&rawFactor);
	tree_->SetBranchAddress("rawmsoftdrop",&rawmsoftdrop);
	tree_->SetBranchAddress("tau1",&tau1);
	tree_->SetBranchAddress("tau2",&tau2);
	tree_->SetBranchAddress("tau3",&tau3);
	tree_->SetBranchAddress("tau4",&tau4);
	tree_->SetBranchAddress("electronIdx3SJ",&electronIdx3SJ);
	tree_->SetBranchAddress("idLep",&idLep);
	tree_->SetBranchAddress("jetId",&jetId);
	tree_->SetBranchAddress("muonIdx3SJ",&muonIdx3SJ);
	tree_->SetBranchAddress("nBHadrons",&nBHadrons);
	tree_->SetBranchAddress("nCHadrons",&nCHadrons);
	tree_->SetBranchAddress("nPFConstituents",&nPFConstituents);
	tree_->SetBranchAddress("subJetIdx1",&subJetIdx1);
	tree_->SetBranchAddress("subJetIdx2",&subJetIdx2);
	tree_->SetBranchAddress("Hmatch",&Hmatch);
	tree_->SetBranchAddress("HgenIdx",&HgenIdx);
	tree_->SetBranchAddress("HminDR",&HminDR);
	tree_->SetBranchAddress("matchedToHbb",&matchedToHbb);
	tree_->SetBranchAddress("matchedToHWWqqqq",&matchedToHWWqqqq);
	tree_->SetBranchAddress("matchedToHWWlnuqq",&matchedToHWWlnuqq);
	tree_->SetBranchAddress("matchedToHZZqqqq",&matchedToHZZqqqq);
	tree_->SetBranchAddress("matchedGenMass",&matchedGenMass);
	tree_->SetBranchAddress("matchedGenPt",&matchedGenPt);
	tree_->SetBranchAddress("matchedGenEta",&matchedGenEta);
	tree_->SetBranchAddress("matchedGenPhi",&matchedGenPhi);

        gErrorIgnoreLevel = currentState;
      }

  }; 


#endif
