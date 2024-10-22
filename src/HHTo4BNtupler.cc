#include "HHTo4BNtupler.h"
#include <stdlib.h> 
#include "TH1F.h"

using namespace std;

void HHTo4BNtupler::Analyze(bool isData, string outputfilename, string year)
{
    cout << "Start..." << endl;
    string CMSSWDir = std::getenv("CMSSW_BASE");    

    //----------------------------------------
    //Jet Veto Map
    //----------------------------------------
    TFile* JetVetoInputRoot = 0;

    if (year == "2022") {
      JetVetoInputRoot = new TFile((CMSSWDir + "/src/HHBoostedAnalyzer/data/JetVetoMap_Summer22_23Sep2023_RunCD_v1.root").c_str());
    } else if (year == "2022EE") {
      JetVetoInputRoot = new TFile((CMSSWDir + "/src/HHBoostedAnalyzer/data/JetVetoMap_Summer22EE_23Sep2023_RunEFG_v1.root").c_str());
    } else if (year == "2023") {
      JetVetoInputRoot = new TFile((CMSSWDir + "/src/HHBoostedAnalyzer/data/Summer23Prompt23_RunC_v1.root").c_str()); 
    } else if (year == "2023BPix") {
      JetVetoInputRoot = new TFile((CMSSWDir + "/src/HHBoostedAnalyzer/data/JetVetoMap_Summer23BPixPrompt23_RunD_v1.root").c_str()); 
    } else if (year == "2024") {
      JetVetoInputRoot = new TFile((CMSSWDir + "/src/HHBoostedAnalyzer/data/").c_str());  
    }
    
    TH2D * JetVetoMap = 0;
    if (JetVetoInputRoot) {
      JetVetoMap = (TH2D*)JetVetoInputRoot->Get("jetvetomap");
      JetVetoMap->SetDirectory(0);          
      JetVetoInputRoot->Close();
      JetVetoMap->Print();
    }
    else {
      cout << "Could not load JetVetoMap for year " + year + ". " << "\n";
    }       

    //----------------------------------------
    //Load Auxiliary Information
    //---------------------------------------- 
    TH1F *pileupWeightHist = 0;
    TH1F *pileupWeightUpHist = 0;
    TH1F *pileupWeightDownHist = 0;
    
    string pileupWeightFilename = "";
    if (year == "2022") {
      pileupWeightFilename = CMSSWDir + "/src/HHBoostedAnalyzer/data/PileupWeights/PileupReweight_Summer22.root";
    } else if (year == "2022EE") {
      pileupWeightFilename = CMSSWDir + "/src/HHBoostedAnalyzer/data/PileupWeights/PileupReweight_Summer22EE.root";
    } else if (year == "2023") {
      pileupWeightFilename = CMSSWDir + "/src/HHBoostedAnalyzer/data/PileupWeights/PileupReweight_Summer23.root";
    } else if (year == "2023BPix") {
      pileupWeightFilename = CMSSWDir + "/src/HHBoostedAnalyzer/data/PileupWeights/PileupReweight_Summer23BPix.root";
    } else if (year == "2024") {
      pileupWeightFilename = CMSSWDir + "/src/HHBoostedAnalyzer/data/PileupWeights/PileupReweight_Summer23.root";
    }
       
    TFile *pileupWeightFile = TFile::Open(pileupWeightFilename.c_str());
    if (!pileupWeightFile) {
      cout << "Warning : pileupWeightFile " << pileupWeightFile << " could not be opened.\n";  
    } else {
      cout << "Opened pileupWeightFile " << pileupWeightFilename << "\n"; 
    }

    if (pileupWeightFile) {
      pileupWeightHist = (TH1F*)(pileupWeightFile->Get("npu_nominal"));
      pileupWeightHist->SetDirectory(0);
      pileupWeightUpHist = (TH1F*)(pileupWeightFile->Get("npu_up"));
      pileupWeightUpHist->SetDirectory(0);
      pileupWeightDownHist = (TH1F*)(pileupWeightFile->Get("npu_down"));
      pileupWeightDownHist->SetDirectory(0);
    } 
    if (pileupWeightHist) {
      cout << "Found pileupWeightHist " << "npu_nominal" << "in file " << pileupWeightFilename << "\n";
    } else {
      cout << "Warning :  could not find pileupWeightHist named " 
	   << "npu_nominal" 
	   << " in file " << pileupWeightFilename << "\n";
    }
    if (pileupWeightUpHist) {
      cout << "Found pileupWeightUpHist " << "npu_up" << "in file " << pileupWeightFilename << "\n";
    } else {
      cout << "Warning :  could not find pileupWeightUpHist named " 
	   << "npu_up"
	   << " in file " << pileupWeightFilename << "\n";
    }
    if (pileupWeightDownHist) {
      cout << "Found pileupWeightDownHist " << "npu_up" << "in file " << pileupWeightFilename << "\n";
    } else {
      cout << "Warning :  could not find pileupWeightDownHist named " 
	   << "npu_up"
	   << " in file " << pileupWeightFilename << "\n";
    }
    pileupWeightFile->Close();
    pileupWeightHist->Print();

    
    //------------------------------------------------------------------------------------------------------------
    //Output file : It's important to open the output file before opening any of the auxiliary files
    //------------------------------------------------------------------------------------------------------------  
    string outfilename = outputfilename;
    if (outfilename == "") outfilename = "HHTo4BNtuple.root";
    TFile *outFile = new TFile(outfilename.c_str(), "RECREATE");    

    //----------------------------------------
    // histogram containing total number of processed events (for normalization)
    //----------------------------------------  
    TH1F *NEvents = new TH1F("NEvents", "NEvents", 1, 1, 2);
    TH1F *nPU_True = new TH1F("nPU_True", "nPU_True", 100, 0, 100);
    //----------------------------------------
    //output TTree
    //----------------------------------------
    TTree *outputTree = new TTree("tree", "");
    TTree *outputTree_TrgObj = new TTree("tree_TrgObj", "");
    //------------------------
    //declare branch variables
    //------------------------
    // Gen info
    float weight = 0;
    float pileupWeight = 0;
    float pileupWeightUp = 0;
    float pileupWeightDown = 0;
    float totalWeight = 0;
    float genHiggs1Pt = -1;
    float genHiggs1Eta = -1;
    float genHiggs1Phi = -1;
    float genHiggs2Pt = -1;
    float genHiggs2Eta = -1;
    float genHiggs2Phi = -1;
    float genHH_pt = -99;
    float genHH_eta = -99;
    float genHH_phi = -99;
    float genHH_mass = -99;
    float genWPt = -1;
    float genWEta = -1;
    float genWPhi = -1;
    float genZPt = -1;
    float genZEta = -1;
    float genZPhi = -1;
    float genTop1Mass = -1;
    float genTop1Pt = -1;
    float genTop1Eta = -1;
    float genTop1Phi = -1;   
    float genTop2Mass = -1;
    float genTop2Pt = -1;
    float genTop2Eta = -1;
    float genTop2Phi = -1;   
    float genMTT = -1;
    float genLeptonPt = -1;
    float genLeptonEta = -1;
    float genLeptonPhi = -1;
    int   genLeptonId = 0;
    int   genLeptonMotherId = 0;
    float genPhotonPt = -1;
    float genPhotonEta = -1;
    float genPhotonPhi = -1;    

    // Common Variables
    int NJets = 0;
    float MET = -1;

    // FatJets
    float fatJet1_area = -99;
    float fatJet1_btagDDBvLV2 = -99;
    float fatJet1_btagDDCvBV2 = -99;
    float fatJet1_btagDDCvLV2 = -99;
    float fatJet1_btagDeepB = -99;
    float fatJet1_btagHbb = -99;
    int   fatJet1_electronIdx3SJ = -99;
    float fatJet1_eta = -99;
    int   fatJet1_genJetAK8Idx = -99;
    int   fatJet1_hadronFlavour = -99;
    int   fatJet1_jetId = -99;
    float fatJet1_lsf3 = -99;
    float fatJet1_mass = -99;
    float fatJet1_msoftdrop = -99;
    int   fatJet1_muonIdx3SJ = -99;
    float fatJet1_n2b1 = -99;
    float fatJet1_n3b1 = -99;
    int   fatJet1_nBHadrons = -99;
    int   fatJet1_nCHadrons = -99;
    int   fatJet1_nConstituents = -99;
    float fatJet1_particleNetWithMass_H4qvsQCD = -99;
    float fatJet1_particleNetWithMass_HbbvsQCD = -99;
    float fatJet1_particleNetWithMass_HccvsQCD = -99;
    float fatJet1_particleNetWithMass_QCD = -99;
    float fatJet1_particleNetWithMass_TvsQCD = -99;
    float fatJet1_particleNetWithMass_WvsQCD = -99;
    float fatJet1_particleNetWithMass_ZvsQCD = -99;
    float fatJet1_particleNet_QCD = -99;
    float fatJet1_particleNet_QCD0HF = -99;
    float fatJet1_particleNet_QCD1HF = -99;
    float fatJet1_particleNet_QCD2HF = -99;
    float fatJet1_particleNet_XbbVsQCD = -99;
    float fatJet1_particleNet_XccVsQCD = -99;
    float fatJet1_particleNet_XggVsQCD = -99;
    float fatJet1_particleNet_XqqVsQCD = -99;
    float fatJet1_particleNet_XteVsQCD = -99;
    float fatJet1_particleNet_XtmVsQCD = -99;
    float fatJet1_particleNet_XttVsQCD = -99;
    float fatJet1_particleNet_massCorr = -99;
    float fatJet1_globalParT_QCD0HF = -99;
    float fatJet1_globalParT_QCD1HF = -99;
    float fatJet1_globalParT_QCD2HF = -99;
    float fatJet1_globalParT_TopW = -99;
    float fatJet1_globalParT_TopbW = -99;
    float fatJet1_globalParT_TopbWev = -99;
    float fatJet1_globalParT_TopbWmv = -99;
    float fatJet1_globalParT_TopbWq = -99;
    float fatJet1_globalParT_TopbWqq = -99;
    float fatJet1_globalParT_TopbWtauhv = -99;
    float fatJet1_globalParT_Xbb = -99;
    float fatJet1_globalParT_XbbVsQCD = -99;
    float fatJet1_globalParT_Xcc = -99;
    float fatJet1_globalParT_Xcs = -99;
    float fatJet1_globalParT_Xgg = -99;
    float fatJet1_globalParT_Xqq = -99;
    float fatJet1_globalParT_Xtauhtaue = -99;
    float fatJet1_globalParT_Xtauhtauh = -99;
    float fatJet1_globalParT_Xtauhtaum = -99;
    float fatJet1_globalParT_massRes = -99;
    float fatJet1_globalParT_massVis = -99;
    float fatJet1_phi = -99;
    float fatJet1_pt = -99;
    float fatJet1_rawFactor = -99;
    short fatJet1_subJetIdx1 = -1;
    float fatJet1_subJetIdx1_pt = -99;
    float fatJet1_subJetIdx1_eta = -99;
    float fatJet1_subJetIdx1_phi = -99;
    float fatJet1_subJetIdx1_mass = -99;
    short fatJet1_subJetIdx2 = -1;
    float fatJet1_subJetIdx2_pt = -99;
    float fatJet1_subJetIdx2_eta = -99;
    float fatJet1_subJetIdx2_phi = -99;
    float fatJet1_subJetIdx2_mass = -99;
    float fatJet1_tau1 = -99;
    float fatJet1_tau2 = -99;
    float fatJet1_tau3 = -99;
    float fatJet1_tau4 = -99;
    int   fatJet1_GenMatchIndex = -99;
    float fatJet1_Tau3OverTau2 = -99;
    float fatJet1__n2b1 = -99; 
    bool  fatJet1_HasMuon = 0;
    bool  fatJet1_HasElectron = 0;
    bool  fatJet1_HasBJetMedium = 0;
    bool  fatJet1_OppositeHemisphereHasBJet = 0;
    // legacy test
    float fatJet1_particleNetLegacy_Xbb = -99;
    float fatJet1_particleNetLegacy_Xcc = -99;
    float fatJet1_particleNetLegacy_Xqq = -99;
    float fatJet1_particleNetLegacy_QCD = -99;
    float fatJet1_particleNetLegacy_QCDb = -99;
    float fatJet1_particleNetLegacy_QCDbb = -99;
    float fatJet1_particleNetLegacy_QCDothers = -99;
    float fatJet1_particleNetLegacy_mass = -99;

    float fatJet2_area = -99;
    float fatJet2_btagDDBvLV2 = -99;
    float fatJet2_btagDDCvBV2 = -99;
    float fatJet2_btagDDCvLV2 = -99;
    float fatJet2_btagDeepB = -99;
    float fatJet2_btagHbb = -99;
    int   fatJet2_electronIdx3SJ = -99;
    float fatJet2_eta = -99;
    int   fatJet2_genJetAK8Idx = -99;
    int   fatJet2_hadronFlavour = -99;
    int   fatJet2_jetId = -99;
    float fatJet2_lsf3 = -99;
    float fatJet2_mass = -99;
    float fatJet2_msoftdrop = -99;
    int   fatJet2_muonIdx3SJ = -99;
    float fatJet2_n2b1 = -99;
    float fatJet2_n3b1 = -99;
    int   fatJet2_nBHadrons = -99;
    int   fatJet2_nCHadrons = -99;
    int   fatJet2_nConstituents = -99;
    float fatJet2_particleNetWithMass_H4qvsQCD = -99;
    float fatJet2_particleNetWithMass_HbbvsQCD = -99;
    float fatJet2_particleNetWithMass_HccvsQCD = -99;
    float fatJet2_particleNetWithMass_QCD = -99;
    float fatJet2_particleNetWithMass_TvsQCD = -99;
    float fatJet2_particleNetWithMass_WvsQCD = -99;
    float fatJet2_particleNetWithMass_ZvsQCD = -99;
    float fatJet2_particleNet_QCD = -99;
    float fatJet2_particleNet_QCD0HF = -99;
    float fatJet2_particleNet_QCD1HF = -99;
    float fatJet2_particleNet_QCD2HF = -99;
    float fatJet2_particleNet_XbbVsQCD = -99;
    float fatJet2_particleNet_XccVsQCD = -99;
    float fatJet2_particleNet_XggVsQCD = -99;
    float fatJet2_particleNet_XqqVsQCD = -99;
    float fatJet2_particleNet_XteVsQCD = -99;
    float fatJet2_particleNet_XtmVsQCD = -99;
    float fatJet2_particleNet_XttVsQCD = -99;
    float fatJet2_particleNet_massCorr = -99;
    float fatJet2_globalParT_QCD0HF = -99;
    float fatJet2_globalParT_QCD1HF = -99;
    float fatJet2_globalParT_QCD2HF = -99;
    float fatJet2_globalParT_TopW = -99;
    float fatJet2_globalParT_TopbW = -99;
    float fatJet2_globalParT_TopbWev = -99;
    float fatJet2_globalParT_TopbWmv = -99;
    float fatJet2_globalParT_TopbWq = -99;
    float fatJet2_globalParT_TopbWqq = -99;
    float fatJet2_globalParT_TopbWtauhv = -99;
    float fatJet2_globalParT_Xbb = -99;
    float fatJet2_globalParT_XbbVsQCD = -99;
    float fatJet2_globalParT_Xcc = -99;
    float fatJet2_globalParT_Xcs = -99;
    float fatJet2_globalParT_Xgg = -99;
    float fatJet2_globalParT_Xqq = -99;
    float fatJet2_globalParT_Xtauhtaue = -99;
    float fatJet2_globalParT_Xtauhtauh = -99;
    float fatJet2_globalParT_Xtauhtaum = -99;
    float fatJet2_globalParT_massRes = -99;
    float fatJet2_globalParT_massVis = -99;
    float fatJet2_phi = -99;
    float fatJet2_pt = -99;
    float fatJet2_rawFactor = -99;
    short fatJet2_subJetIdx1 = -1;
    float fatJet2_subJetIdx1_pt = -99;
    float fatJet2_subJetIdx1_eta = -99;
    float fatJet2_subJetIdx1_phi = -99;
    float fatJet2_subJetIdx1_mass = -99;
    short fatJet2_subJetIdx2 = -1;
    float fatJet2_subJetIdx2_pt = -99;
    float fatJet2_subJetIdx2_eta = -99;
    float fatJet2_subJetIdx2_phi = -99;
    float fatJet2_subJetIdx2_mass = -99;
    float fatJet2_tau1 = -99;
    float fatJet2_tau2 = -99;
    float fatJet2_tau3 = -99;
    float fatJet2_tau4 = -99;
    int   fatJet2_GenMatchIndex = -99;
    float fatJet2_Tau3OverTau2 = -99;
    float fatJet2__n2b1 = -99; 
    bool  fatJet2_HasMuon = 0;
    bool  fatJet2_HasElectron = 0;
    bool  fatJet2_HasBJetMedium = 0;
    bool  fatJet2_OppositeHemisphereHasBJet = 0;
    // legacy test
    float fatJet2_particleNetLegacy_Xbb = -99;
    float fatJet2_particleNetLegacy_Xcc = -99;
    float fatJet2_particleNetLegacy_Xqq = -99;
    float fatJet2_particleNetLegacy_QCD = -99;
    float fatJet2_particleNetLegacy_QCDb = -99;
    float fatJet2_particleNetLegacy_QCDbb = -99;
    float fatJet2_particleNetLegacy_QCDothers = -99;
    float fatJet2_particleNetLegacy_mass = -99;

    float fatJet3_area = -99;
    float fatJet3_btagDDBvLV2 = -99;
    float fatJet3_btagDDCvBV2 = -99;
    float fatJet3_btagDDCvLV2 = -99;
    float fatJet3_btagDeepB = -99;
    float fatJet3_btagHbb = -99;
    int   fatJet3_electronIdx3SJ = -99;
    float fatJet3_eta = -99;
    int   fatJet3_genJetAK8Idx = -99;
    int   fatJet3_hadronFlavour = -99;
    int   fatJet3_jetId = -99;
    float fatJet3_lsf3 = -99;
    float fatJet3_mass = -99;
    float fatJet3_msoftdrop = -99;
    int   fatJet3_muonIdx3SJ = -99;
    float fatJet3_n2b1 = -99;
    float fatJet3_n3b1 = -99;
    int   fatJet3_nBHadrons = -99;
    int   fatJet3_nCHadrons = -99;
    int   fatJet3_nConstituents = -99;
    float fatJet3_particleNetWithMass_H4qvsQCD = -99;
    float fatJet3_particleNetWithMass_HbbvsQCD = -99;
    float fatJet3_particleNetWithMass_HccvsQCD = -99;
    float fatJet3_particleNetWithMass_QCD = -99;
    float fatJet3_particleNetWithMass_TvsQCD = -99;
    float fatJet3_particleNetWithMass_WvsQCD = -99;
    float fatJet3_particleNetWithMass_ZvsQCD = -99;
    float fatJet3_particleNet_QCD = -99;
    float fatJet3_particleNet_QCD0HF = -99;
    float fatJet3_particleNet_QCD1HF = -99;
    float fatJet3_particleNet_QCD2HF = -99;
    float fatJet3_particleNet_XbbVsQCD = -99;
    float fatJet3_particleNet_XccVsQCD = -99;
    float fatJet3_particleNet_XggVsQCD = -99;
    float fatJet3_particleNet_XqqVsQCD = -99;
    float fatJet3_particleNet_XteVsQCD = -99;
    float fatJet3_particleNet_XtmVsQCD = -99;
    float fatJet3_particleNet_XttVsQCD = -99;
    float fatJet3_particleNet_massCorr = -99;
    float fatJet3_globalParT_QCD0HF = -99;
    float fatJet3_globalParT_QCD1HF = -99;
    float fatJet3_globalParT_QCD2HF = -99;
    float fatJet3_globalParT_TopW = -99;
    float fatJet3_globalParT_TopbW = -99;
    float fatJet3_globalParT_TopbWev = -99;
    float fatJet3_globalParT_TopbWmv = -99;
    float fatJet3_globalParT_TopbWq = -99;
    float fatJet3_globalParT_TopbWqq = -99;
    float fatJet3_globalParT_TopbWtauhv = -99;
    float fatJet3_globalParT_Xbb = -99;
    float fatJet3_globalParT_XbbVsQCD = -99;
    float fatJet3_globalParT_Xcc = -99;
    float fatJet3_globalParT_Xcs = -99;
    float fatJet3_globalParT_Xgg = -99;
    float fatJet3_globalParT_Xqq = -99;
    float fatJet3_globalParT_Xtauhtaue = -99;
    float fatJet3_globalParT_Xtauhtauh = -99;
    float fatJet3_globalParT_Xtauhtaum = -99;
    float fatJet3_globalParT_massRes = -99;
    float fatJet3_globalParT_massVis = -99;
    float fatJet3_phi = -99;
    float fatJet3_pt = -99;
    float fatJet3_rawFactor = -99;
    short fatJet3_subJetIdx1 = -1;
    float fatJet3_subJetIdx1_pt = -99;
    float fatJet3_subJetIdx1_eta = -99;
    float fatJet3_subJetIdx1_phi = -99;
    float fatJet3_subJetIdx1_mass = -99;
    short fatJet3_subJetIdx2 = -1;
    float fatJet3_subJetIdx2_pt = -99;
    float fatJet3_subJetIdx2_eta = -99;
    float fatJet3_subJetIdx2_phi = -99;
    float fatJet3_subJetIdx2_mass = -99;
    float fatJet3_tau1 = -99;
    float fatJet3_tau2 = -99;
    float fatJet3_tau3 = -99;
    float fatJet3_tau4 = -99;
    int   fatJet3_GenMatchIndex = -99;
    float fatJet3_Tau3OverTau2 = -99;
    float fatJet3__n2b1 = -99; 
    bool  fatJet3_HasMuon = 0;
    bool  fatJet3_HasElectron = 0;
    bool  fatJet3_HasBJetMedium = 0;
    bool  fatJet3_OppositeHemisphereHasBJet = 0;
    // legacy test
    float fatJet3_particleNetLegacy_Xbb = -99;
    float fatJet3_particleNetLegacy_Xcc = -99;
    float fatJet3_particleNetLegacy_Xqq = -99;
    float fatJet3_particleNetLegacy_QCD = -99;
    float fatJet3_particleNetLegacy_QCDb = -99;
    float fatJet3_particleNetLegacy_QCDbb = -99;
    float fatJet3_particleNetLegacy_QCDothers = -99;
    float fatJet3_particleNetLegacy_mass = -99;

    //variables for overlap removal with VBF HH->4b boosted analysis
    int isVBFtag = 0;
    float dijetmass = -99;
    float vbfjet1_Pt = -99;
    float vbfjet1_Eta = -99;
    float vbfjet1_Phi = -99;
    float vbfjet1_Mass = -99;
    float vbfjet2_Pt = -99;
    float vbfjet2_Eta = -99;
    float vbfjet2_Phi = -99;
    float vbfjet2_Mass = -99;

///////////////////////////////////////////////////////////////////////////

    float lep1Pt = -99;
    float lep1Eta = -99;
    float lep1Phi = -99;
    int   lep1Id = 0;
    float lep2Pt = -99;
    float lep2Eta = -99;
    float lep2Phi = -99;
    int   lep2Id = 0;
    float pho1Pt = -99;
    float pho1Eta = -99;
    float pho1Phi = -99;

    float jet1Pt = -99;
    float jet1Eta = -99;
    float jet1Phi = -99;
    float jet1_rawFactor = -99;
    float jet2Pt = -99;
    float jet2Eta = -99;
    float jet2Phi = -99;
    float jet2_rawFactor = -99;
    float jet3Pt = -99;
    float jet3Eta = -99;
    float jet3Phi = -99;
    float jet3_rawFactor = -99;
    float jet4Pt = -99;
    float jet4Eta = -99;
    float jet4Phi = -99;
    float jet4_rawFactor = -99;
    int   nBTaggedJets = 0;

    float genJetEta[1000];
    float genJetPhi[1000];
    float genJetMass[1000];
    float genJetPt[1000];
    int   genJetPartonFlavor[1000];
    float genJetAK8Eta[1000];
    float genJetAK8Phi[1000];
    float genJetAK8Mass[1000];
    float genJetAK8Pt[1000];

    // Modification begin: Trigger objects
    Int_t   NTrigger_Objects=0;
    Float_t Trigger_Object_pt[20];
    Float_t Trigger_Object_eta[20];
    Float_t Trigger_Object_phi[20];
    Int_t   Trigger_Object_bit[20];
    outputTree_TrgObj->Branch("NTrigger_Objects",   &NTrigger_Objects,  "NTrigger_Objects/I");
    outputTree_TrgObj->Branch("Trigger_Object_pt",  Trigger_Object_pt,  "Trigger_Object_pt[NTrigger_Objects]/F");
    outputTree_TrgObj->Branch("Trigger_Object_eta", Trigger_Object_eta, "Trigger_Object_eta[NTrigger_Objects]/F");
    outputTree_TrgObj->Branch("Trigger_Object_phi", Trigger_Object_phi, "Trigger_Object_phi[NTrigger_Objects]/F");
    outputTree_TrgObj->Branch("Trigger_Object_bit", Trigger_Object_bit, "Trigger_Object_bit[NTrigger_Objects]/I");
    //------------------------
    //set branches on big tree
    //------------------------    
    outputTree->Branch("weight", &weight, "weight/F");
    outputTree->Branch("pileupWeight", &pileupWeight, "pileupWeight/F");
    outputTree->Branch("pileupWeightUp", &pileupWeightUp, "pileupWeightUp/F");
    outputTree->Branch("pileupWeightDown", &pileupWeightDown, "pileupWeightDown/F");
    outputTree->Branch("run", &run, "run/i");
    outputTree->Branch("lumi", &luminosityBlock, "lumi/i");
    outputTree->Branch("event", &event, "event/l");
    outputTree->Branch("npu", &Pileup_nTrueInt, "npu/F");
    outputTree->Branch("rho", &fixedGridRhoFastjetAll, "rho/F");

    outputTree->Branch("NJets", &NJets, "NJets/I");
    outputTree->Branch("MET", &MET, "MET/F");

    outputTree->Branch("fatJet1_pt", &fatJet1_pt, "fatJet1_pt/F");
    outputTree->Branch("fatJet1_eta", &fatJet1_eta, "fatJet1_eta/F");
    outputTree->Branch("fatJet1_phi", &fatJet1_phi, "fatJet1_phi/F");
    outputTree->Branch("fatJet1_mass", &fatJet1_mass, "fatJet1_mass/F");
    outputTree->Branch("fatJet1_msoftdrop", &fatJet1_msoftdrop, "fatJet1_msoftdrop/F");
    outputTree->Branch("fatJet1_btagDDBvLV2", &fatJet1_btagDDBvLV2, "fatJet1_btagDDBvLV2/F");
    outputTree->Branch("fatJet1_btagDDCvBV2", &fatJet1_btagDDCvBV2, "fatJet1_btagDDCvBV2/F");
    outputTree->Branch("fatJet1_btagDDCvLV2", &fatJet1_btagDDCvLV2, "fatJet1_btagDDCvLV2/F");
    outputTree->Branch("fatJet1_btagDeepB", &fatJet1_btagDeepB, "fatJet1_btagDeepB/F");
    outputTree->Branch("fatJet1_particleNetWithMass_H4qvsQCD", &fatJet1_particleNetWithMass_H4qvsQCD, "fatJet1_particleNetWithMass_H4qvsQCD/F");
    outputTree->Branch("fatJet1_particleNetWithMass_HbbvsQCD", &fatJet1_particleNetWithMass_HbbvsQCD, "fatJet1_particleNetWithMass_HbbvsQCD/F");
    outputTree->Branch("fatJet1_particleNetWithMass_HccvsQCD", &fatJet1_particleNetWithMass_HccvsQCD, "fatJet1_particleNetWithMass_HccvsQCD/F");
    outputTree->Branch("fatJet1_particleNetWithMass_QCD", &fatJet1_particleNetWithMass_QCD, "fatJet1_particleNetWithMass_QCD/F");
    outputTree->Branch("fatJet1_particleNetWithMass_TvsQCD", &fatJet1_particleNetWithMass_TvsQCD, "fatJet1_particleNetWithMass_TvsQCD/F");
    outputTree->Branch("fatJet1_particleNetWithMass_WvsQCD", &fatJet1_particleNetWithMass_WvsQCD, "fatJet1_particleNetWithMass_WvsQCD/F");
    outputTree->Branch("fatJet1_particleNetWithMass_ZvsQCD", &fatJet1_particleNetWithMass_ZvsQCD, "fatJet1_particleNetWithMass_ZvsQCD/F");
    outputTree->Branch("fatJet1_particleNet_QCD", &fatJet1_particleNet_QCD, "fatJet1_particleNet_QCD/F");
    outputTree->Branch("fatJet1_particleNet_QCD0HF", &fatJet1_particleNet_QCD0HF, "fatJet1_particleNet_QCD0HF/F");
    outputTree->Branch("fatJet1_particleNet_QCD1HF", &fatJet1_particleNet_QCD1HF, "fatJet1_particleNet_QCD1HF/F");
    outputTree->Branch("fatJet1_particleNet_QCD2HF", &fatJet1_particleNet_QCD2HF, "fatJet1_particleNet_QCD2HF/F");
    outputTree->Branch("fatJet1_particleNet_XbbVsQCD", &fatJet1_particleNet_XbbVsQCD, "fatJet1_particleNet_XbbVsQCD/F");
    outputTree->Branch("fatJet1_particleNet_XccVsQCD", &fatJet1_particleNet_XccVsQCD, "fatJet1_particleNet_XccVsQCD/F");
    outputTree->Branch("fatJet1_particleNet_XggVsQCD", &fatJet1_particleNet_XggVsQCD, "fatJet1_particleNet_XggVsQCD/F");
    outputTree->Branch("fatJet1_particleNet_XqqVsQCD", &fatJet1_particleNet_XqqVsQCD, "fatJet1_particleNet_XqqVsQCD/F");
    outputTree->Branch("fatJet1_particleNet_massCorr", &fatJet1_particleNet_massCorr, "fatJet1_particleNet_massCorr/F");
    outputTree->Branch("fatJet1_globalParT_QCD0HF", &fatJet1_globalParT_QCD0HF, "fatJet1_globalParT_QCD0HF/F");
    outputTree->Branch("fatJet1_globalParT_QCD1HF", &fatJet1_globalParT_QCD1HF, "fatJet1_globalParT_QCD1HF/F");
    outputTree->Branch("fatJet1_globalParT_QCD2HF", &fatJet1_globalParT_QCD2HF, "fatJet1_globalParT_QCD2HF/F");
    outputTree->Branch("fatJet1_globalParT_TopW", &fatJet1_globalParT_TopW, "fatJet1_globalParT_TopW/F");
    outputTree->Branch("fatJet1_globalParT_TopbW", &fatJet1_globalParT_TopbW, "fatJet1_globalParT_TopbW/F");
    outputTree->Branch("fatJet1_globalParT_TopbWev", &fatJet1_globalParT_TopbWev, "fatJet1_globalParT_TopbWev/F");
    outputTree->Branch("fatJet1_globalParT_TopbWmv", &fatJet1_globalParT_TopbWmv, "fatJet1_globalParT_TopbWmv/F");
    outputTree->Branch("fatJet1_globalParT_TopbWq", &fatJet1_globalParT_TopbWq, "fatJet1_globalParT_TopbWq/F");
    outputTree->Branch("fatJet1_globalParT_TopbWqq", &fatJet1_globalParT_TopbWqq, "fatJet1_globalParT_TopbWqq/F");
    outputTree->Branch("fatJet1_globalParT_TopbWtauhv", &fatJet1_globalParT_TopbWtauhv, "fatJet1_globalParT_TopbWtauhv/F");
    outputTree->Branch("fatJet1_globalParT_Xbb", &fatJet1_globalParT_Xbb, "fatJet1_globalParT_Xbb/F");
    outputTree->Branch("fatJet1_globalParT_XbbVsQCD", &fatJet1_globalParT_XbbVsQCD, "fatJet1_globalParT_XbbVsQCD/F");
    outputTree->Branch("fatJet1_globalParT_Xcc", &fatJet1_globalParT_Xcc, "fatJet1_globalParT_Xcc/F");
    outputTree->Branch("fatJet1_globalParT_Xcs", &fatJet1_globalParT_Xcs, "fatJet1_globalParT_Xcs/F");
    outputTree->Branch("fatJet1_globalParT_Xgg", &fatJet1_globalParT_Xgg, "fatJet1_globalParT_Xgg/F");
    outputTree->Branch("fatJet1_globalParT_Xqq", &fatJet1_globalParT_Xqq, "fatJet1_globalParT_Xqq/F");
    outputTree->Branch("fatJet1_globalParT_Xtauhtaue", &fatJet1_globalParT_Xtauhtaue, "fatJet1_globalParT_Xtauhtaue/F");
    outputTree->Branch("fatJet1_globalParT_Xtauhtauh", &fatJet1_globalParT_Xtauhtauh, "fatJet1_globalParT_Xtauhtauh/F");
    outputTree->Branch("fatJet1_globalParT_Xtauhtaum", &fatJet1_globalParT_Xtauhtaum, "fatJet1_globalParT_Xtauhtaum/F");
    outputTree->Branch("fatJet1_globalParT_massRes", &fatJet1_globalParT_massRes, "fatJet1_globalParT_massRes/F");
    outputTree->Branch("fatJet1_globalParT_massVis", &fatJet1_globalParT_massVis, "fatJet1_globalParT_massVis/F");
    outputTree->Branch("fatJet1_n2b1", &fatJet1_n2b1, "fatJet1_n2b1/F");
    outputTree->Branch("fatJet1_n3b1", &fatJet1_n3b1, "fatJet1_n3b1/F");
    outputTree->Branch("fatJet1_Tau3OverTau2", &fatJet1_Tau3OverTau2, "fatJet1_Tau3OverTau2/F");
    outputTree->Branch("fatJet1_rawFactor", &fatJet1_rawFactor, "fatJet1_rawFactor/F");
    outputTree->Branch("fatJet1_HasMuon", &fatJet1_HasMuon, "fatJet1_HasMuon/O");
    outputTree->Branch("fatJet1_HasElectron", &fatJet1_HasElectron, "fatJet1_HasElectron/O");
    outputTree->Branch("fatJet1_HasBJetMedium", &fatJet1_HasBJetMedium, "fatJet1_HasBJetMedium/O");
    outputTree->Branch("fatJet1_OppositeHemisphereHasBJet", &fatJet1_OppositeHemisphereHasBJet, "fatJet1_OppositeHemisphereHasBJet/O");
    outputTree->Branch("fatJet1_subJetIdx1_pt",   &fatJet1_subJetIdx1_pt,   "fatJet1_subJetIdx1_pt/F");
    outputTree->Branch("fatJet1_subJetIdx1_eta",  &fatJet1_subJetIdx1_eta,  "fatJet1_subJetIdx1_eta/F");
    outputTree->Branch("fatJet1_subJetIdx1_phi",  &fatJet1_subJetIdx1_phi,  "fatJet1_subJetIdx1_phi/F");
    outputTree->Branch("fatJet1_subJetIdx1_mass", &fatJet1_subJetIdx1_mass, "fatJet1_subJetIdx1_mass/F");
    outputTree->Branch("fatJet1_subJetIdx2_pt",   &fatJet1_subJetIdx2_pt,   "fatJet1_subJetIdx2_pt/F");
    outputTree->Branch("fatJet1_subJetIdx2_eta",  &fatJet1_subJetIdx2_eta,  "fatJet1_subJetIdx2_eta/F");
    outputTree->Branch("fatJet1_subJetIdx2_phi",  &fatJet1_subJetIdx2_phi,  "fatJet1_subJetIdx2_phi/F");
    outputTree->Branch("fatJet1_subJetIdx2_mass", &fatJet1_subJetIdx2_mass, "fatJet1_subJetIdx2_mass/F");
    outputTree->Branch("fatJet1_subJetIdx2", &fatJet1_subJetIdx2, "fatJet1_subJetIdx2/I");
    outputTree->Branch("fatJet1_subJetIdx1", &fatJet1_subJetIdx1, "fatJet1_subJetIdx1/I");
    outputTree->Branch("fatJet1_subJetIdx2", &fatJet1_subJetIdx2, "fatJet1_subJetIdx2/I");
    outputTree->Branch("fatJet1_jetId", &fatJet1_jetId, "fatJet1_jetId/I");
    outputTree->Branch("fatJet1_electronIdx3SJ", &fatJet1_electronIdx3SJ, "fatJet1_electronIdx3SJ/I");
    outputTree->Branch("fatJet1_muonIdx3SJ", &fatJet1_muonIdx3SJ, "fatJet1_muonIdx3SJ/I");
    outputTree->Branch("fatJet1_nConstituents", &fatJet1_nConstituents, "fatJet1_nConstituents/I");
    outputTree->Branch("fatJet1_hadronFlavour", &fatJet1_hadronFlavour, "fatJet1_hadronFlavour/I");
    outputTree->Branch("fatJet1_GenMatchIndex", &fatJet1_GenMatchIndex, "fatJet1_GenMatchIndex/I");
    outputTree->Branch("fatJet1_nBHadrons", &fatJet1_nBHadrons, "fatJet1_nBHadrons/I");
    outputTree->Branch("fatJet1_nCHadrons", &fatJet1_nCHadrons, "fatJet1_nCHadrons/I");
    // legacy test
    outputTree->Branch("fatJet1_particleNetLegacy_Xbb", &fatJet1_particleNetLegacy_Xbb, "fatJet1_particleNetLegacy_Xbb/F");
    outputTree->Branch("fatJet1_particleNetLegacy_Xcc", &fatJet1_particleNetLegacy_Xcc, "fatJet1_particleNetLegacy_Xcc/F");
    outputTree->Branch("fatJet1_particleNetLegacy_Xqq", &fatJet1_particleNetLegacy_Xqq, "fatJet1_particleNetLegacy_Xqq/F");
    outputTree->Branch("fatJet1_particleNetLegacy_QCD", &fatJet1_particleNetLegacy_QCD, "fatJet1_particleNetLegacy_QCD/F");
    outputTree->Branch("fatJet1_particleNetLegacy_QCDb", &fatJet1_particleNetLegacy_QCDb, "fatJet1_particleNetLegacy_QCDb/F");
    outputTree->Branch("fatJet1_particleNetLegacy_QCDbb", &fatJet1_particleNetLegacy_QCDbb, "fatJet1_particleNetLegacy_QCDbb/F");
    outputTree->Branch("fatJet1_particleNetLegacy_QCDothers", &fatJet1_particleNetLegacy_QCDothers, "fatJet1_particleNetLegacy_QCDothers/F");
    outputTree->Branch("fatJet1_particleNetLegacy_mass", &fatJet1_particleNetLegacy_mass, "fatJet1_particleNetLegacy_mass/F");

    outputTree->Branch("fatJet2_pt", &fatJet2_pt, "fatJet2_pt/F");
    outputTree->Branch("fatJet2_eta", &fatJet2_eta, "fatJet2_eta/F");
    outputTree->Branch("fatJet2_phi", &fatJet2_phi, "fatJet2_phi/F");
    outputTree->Branch("fatJet2_mass", &fatJet2_mass, "fatJet2_mass/F");
    outputTree->Branch("fatJet2_msoftdrop", &fatJet2_msoftdrop, "fatJet2_msoftdrop/F");
    outputTree->Branch("fatJet2_btagDDBvLV2", &fatJet2_btagDDBvLV2, "fatJet2_btagDDBvLV2/F");
    outputTree->Branch("fatJet2_btagDDCvBV2", &fatJet2_btagDDCvBV2, "fatJet2_btagDDCvBV2/F");
    outputTree->Branch("fatJet2_btagDDCvLV2", &fatJet2_btagDDCvLV2, "fatJet2_btagDDCvLV2/F");
    outputTree->Branch("fatJet2_btagDeepB", &fatJet2_btagDeepB, "fatJet2_btagDeepB/F");
    outputTree->Branch("fatJet2_particleNetWithMass_H4qvsQCD", &fatJet2_particleNetWithMass_H4qvsQCD, "fatJet2_particleNetWithMass_H4qvsQCD/F");
    outputTree->Branch("fatJet2_particleNetWithMass_HbbvsQCD", &fatJet2_particleNetWithMass_HbbvsQCD, "fatJet2_particleNetWithMass_HbbvsQCD/F");
    outputTree->Branch("fatJet2_particleNetWithMass_HccvsQCD", &fatJet2_particleNetWithMass_HccvsQCD, "fatJet2_particleNetWithMass_HccvsQCD/F");
    outputTree->Branch("fatJet2_particleNetWithMass_QCD", &fatJet2_particleNetWithMass_QCD, "fatJet2_particleNetWithMass_QCD/F");
    outputTree->Branch("fatJet2_particleNetWithMass_TvsQCD", &fatJet2_particleNetWithMass_TvsQCD, "fatJet2_particleNetWithMass_TvsQCD/F");
    outputTree->Branch("fatJet2_particleNetWithMass_WvsQCD", &fatJet2_particleNetWithMass_WvsQCD, "fatJet2_particleNetWithMass_WvsQCD/F");
    outputTree->Branch("fatJet2_particleNetWithMass_ZvsQCD", &fatJet2_particleNetWithMass_ZvsQCD, "fatJet2_particleNetWithMass_ZvsQCD/F");
    outputTree->Branch("fatJet2_particleNet_QCD", &fatJet2_particleNet_QCD, "fatJet2_particleNet_QCD/F");
    outputTree->Branch("fatJet2_particleNet_QCD0HF", &fatJet2_particleNet_QCD0HF, "fatJet2_particleNet_QCD0HF/F");
    outputTree->Branch("fatJet2_particleNet_QCD1HF", &fatJet2_particleNet_QCD1HF, "fatJet2_particleNet_QCD1HF/F");
    outputTree->Branch("fatJet2_particleNet_QCD2HF", &fatJet2_particleNet_QCD2HF, "fatJet2_particleNet_QCD2HF/F");
    outputTree->Branch("fatJet2_particleNet_XbbVsQCD", &fatJet2_particleNet_XbbVsQCD, "fatJet2_particleNet_XbbVsQCD/F");
    outputTree->Branch("fatJet2_particleNet_XccVsQCD", &fatJet2_particleNet_XccVsQCD, "fatJet2_particleNet_XccVsQCD/F");
    outputTree->Branch("fatJet2_particleNet_XggVsQCD", &fatJet2_particleNet_XggVsQCD, "fatJet2_particleNet_XggVsQCD/F");
    outputTree->Branch("fatJet2_particleNet_XqqVsQCD", &fatJet2_particleNet_XqqVsQCD, "fatJet2_particleNet_XqqVsQCD/F");
    outputTree->Branch("fatJet2_particleNet_massCorr", &fatJet2_particleNet_massCorr, "fatJet2_particleNet_massCorr/F");
    outputTree->Branch("fatJet2_globalParT_QCD0HF", &fatJet2_globalParT_QCD0HF, "fatJet2_globalParT_QCD0HF/F");
    outputTree->Branch("fatJet2_globalParT_QCD1HF", &fatJet2_globalParT_QCD1HF, "fatJet2_globalParT_QCD1HF/F");
    outputTree->Branch("fatJet2_globalParT_QCD2HF", &fatJet2_globalParT_QCD2HF, "fatJet2_globalParT_QCD2HF/F");
    outputTree->Branch("fatJet2_globalParT_TopW", &fatJet2_globalParT_TopW, "fatJet2_globalParT_TopW/F");
    outputTree->Branch("fatJet2_globalParT_TopbW", &fatJet2_globalParT_TopbW, "fatJet2_globalParT_TopbW/F");
    outputTree->Branch("fatJet2_globalParT_TopbWev", &fatJet2_globalParT_TopbWev, "fatJet2_globalParT_TopbWev/F");
    outputTree->Branch("fatJet2_globalParT_TopbWmv", &fatJet2_globalParT_TopbWmv, "fatJet2_globalParT_TopbWmv/F");
    outputTree->Branch("fatJet2_globalParT_TopbWq", &fatJet2_globalParT_TopbWq, "fatJet2_globalParT_TopbWq/F");
    outputTree->Branch("fatJet2_globalParT_TopbWqq", &fatJet2_globalParT_TopbWqq, "fatJet2_globalParT_TopbWqq/F");
    outputTree->Branch("fatJet2_globalParT_TopbWtauhv", &fatJet2_globalParT_TopbWtauhv, "fatJet2_globalParT_TopbWtauhv/F");
    outputTree->Branch("fatJet2_globalParT_Xbb", &fatJet2_globalParT_Xbb, "fatJet2_globalParT_Xbb/F");
    outputTree->Branch("fatJet2_globalParT_XbbVsQCD", &fatJet2_globalParT_XbbVsQCD, "fatJet2_globalParT_XbbVsQCD/F");
    outputTree->Branch("fatJet2_globalParT_Xcc", &fatJet2_globalParT_Xcc, "fatJet2_globalParT_Xcc/F");
    outputTree->Branch("fatJet2_globalParT_Xcs", &fatJet2_globalParT_Xcs, "fatJet2_globalParT_Xcs/F");
    outputTree->Branch("fatJet2_globalParT_Xgg", &fatJet2_globalParT_Xgg, "fatJet2_globalParT_Xgg/F");
    outputTree->Branch("fatJet2_globalParT_Xqq", &fatJet2_globalParT_Xqq, "fatJet2_globalParT_Xqq/F");
    outputTree->Branch("fatJet2_globalParT_Xtauhtaue", &fatJet2_globalParT_Xtauhtaue, "fatJet2_globalParT_Xtauhtaue/F");
    outputTree->Branch("fatJet2_globalParT_Xtauhtauh", &fatJet2_globalParT_Xtauhtauh, "fatJet2_globalParT_Xtauhtauh/F");
    outputTree->Branch("fatJet2_globalParT_Xtauhtaum", &fatJet2_globalParT_Xtauhtaum, "fatJet2_globalParT_Xtauhtaum/F");
    outputTree->Branch("fatJet2_globalParT_massRes", &fatJet2_globalParT_massRes, "fatJet2_globalParT_massRes/F");
    outputTree->Branch("fatJet2_globalParT_massVis", &fatJet2_globalParT_massVis, "fatJet2_globalParT_massVis/F");
    outputTree->Branch("fatJet2_n2b1", &fatJet2_n2b1, "fatJet2_n2b1/F");
    outputTree->Branch("fatJet2_n3b1", &fatJet2_n3b1, "fatJet2_n3b1/F");
    outputTree->Branch("fatJet2_Tau3OverTau2", &fatJet2_Tau3OverTau2, "fatJet2_Tau3OverTau2/F");
    outputTree->Branch("fatJet2_rawFactor", &fatJet2_rawFactor, "fatJet2_rawFactor/F");
    outputTree->Branch("fatJet2_HasMuon", &fatJet2_HasMuon, "fatJet2_HasMuon/O");
    outputTree->Branch("fatJet2_HasElectron", &fatJet2_HasElectron, "fatJet2_HasElectron/O");
    outputTree->Branch("fatJet2_HasBJetMedium", &fatJet2_HasBJetMedium, "fatJet2_HasBJetMedium/O");
    outputTree->Branch("fatJet2_OppositeHemisphereHasBJet", &fatJet2_OppositeHemisphereHasBJet, "fatJet2_OppositeHemisphereHasBJet/O");
    outputTree->Branch("fatJet2_subJetIdx1_pt",   &fatJet2_subJetIdx1_pt,   "fatJet2_subJetIdx1_pt/F");
    outputTree->Branch("fatJet2_subJetIdx1_eta",  &fatJet2_subJetIdx1_eta,  "fatJet2_subJetIdx1_eta/F");
    outputTree->Branch("fatJet2_subJetIdx1_phi",  &fatJet2_subJetIdx1_phi,  "fatJet2_subJetIdx1_phi/F");
    outputTree->Branch("fatJet2_subJetIdx1_mass", &fatJet2_subJetIdx1_mass, "fatJet2_subJetIdx1_mass/F");
    outputTree->Branch("fatJet2_subJetIdx2_pt",   &fatJet2_subJetIdx2_pt,   "fatJet2_subJetIdx2_pt/F");
    outputTree->Branch("fatJet2_subJetIdx2_eta",  &fatJet2_subJetIdx2_eta,  "fatJet2_subJetIdx2_eta/F");
    outputTree->Branch("fatJet2_subJetIdx2_phi",  &fatJet2_subJetIdx2_phi,  "fatJet2_subJetIdx2_phi/F");
    outputTree->Branch("fatJet2_subJetIdx2_mass", &fatJet2_subJetIdx2_mass, "fatJet2_subJetIdx2_mass/F");
    outputTree->Branch("fatJet2_hadronFlavour", &fatJet2_hadronFlavour, "fatJet2_hadronFlavour/I");
    outputTree->Branch("fatJet2_jetId", &fatJet2_jetId, "fatJet2_jetId/I");
    outputTree->Branch("fatJet2_electronIdx3SJ", &fatJet2_electronIdx3SJ, "fatJet2_electronIdx3SJ/I");
    outputTree->Branch("fatJet2_muonIdx3SJ", &fatJet2_muonIdx3SJ, "fatJet2_muonIdx3SJ/I");
    outputTree->Branch("fatJet2_nConstituents", &fatJet2_nConstituents, "fatJet2_nConstituents/I");
    outputTree->Branch("fatJet2_hadronFlavour", &fatJet2_hadronFlavour, "fatJet2_hadronFlavour/I");
    outputTree->Branch("fatJet2_GenMatchIndex", &fatJet2_GenMatchIndex, "fatJet2_GenMatchIndex/I");
    outputTree->Branch("fatJet2_nBHadrons", &fatJet2_nBHadrons, "fatJet2_nBHadrons/I");
    outputTree->Branch("fatJet2_nCHadrons", &fatJet2_nCHadrons, "fatJet2_nCHadrons/I");
    // legacy test
    outputTree->Branch("fatJet2_particleNetLegacy_Xbb", &fatJet2_particleNetLegacy_Xbb, "fatJet2_particleNetLegacy_Xbb/F");
    outputTree->Branch("fatJet2_particleNetLegacy_Xcc", &fatJet2_particleNetLegacy_Xcc, "fatJet2_particleNetLegacy_Xcc/F");
    outputTree->Branch("fatJet2_particleNetLegacy_Xqq", &fatJet2_particleNetLegacy_Xqq, "fatJet2_particleNetLegacy_Xqq/F");
    outputTree->Branch("fatJet2_particleNetLegacy_QCD", &fatJet2_particleNetLegacy_QCD, "fatJet2_particleNetLegacy_QCD/F");
    outputTree->Branch("fatJet2_particleNetLegacy_QCDb", &fatJet2_particleNetLegacy_QCDb, "fatJet2_particleNetLegacy_QCDb/F");
    outputTree->Branch("fatJet2_particleNetLegacy_QCDbb", &fatJet2_particleNetLegacy_QCDbb, "fatJet2_particleNetLegacy_QCDbb/F");
    outputTree->Branch("fatJet2_particleNetLegacy_QCDothers", &fatJet2_particleNetLegacy_QCDothers, "fatJet2_particleNetLegacy_QCDothers/F");
    outputTree->Branch("fatJet2_particleNetLegacy_mass", &fatJet2_particleNetLegacy_mass, "fatJet2_particleNetLegacy_mass/F");

    outputTree->Branch("fatJet3_pt", &fatJet3_pt, "fatJet3_pt/F");
    outputTree->Branch("fatJet3_eta", &fatJet3_eta, "fatJet3_eta/F");
    outputTree->Branch("fatJet3_phi", &fatJet3_phi, "fatJet3_phi/F");
    outputTree->Branch("fatJet3_mass", &fatJet3_mass, "fatJet3_mass/F");
    outputTree->Branch("fatJet3_msoftdrop", &fatJet3_msoftdrop, "fatJet3_msoftdrop/F");
    outputTree->Branch("fatJet3_btagDDBvLV2", &fatJet3_btagDDBvLV2, "fatJet3_btagDDBvLV2/F");
    outputTree->Branch("fatJet3_btagDDCvBV2", &fatJet3_btagDDCvBV2, "fatJet3_btagDDCvBV2/F");
    outputTree->Branch("fatJet3_btagDDCvLV2", &fatJet3_btagDDCvLV2, "fatJet3_btagDDCvLV2/F");
    outputTree->Branch("fatJet3_btagDeepB", &fatJet3_btagDeepB, "fatJet3_btagDeepB/F");
    outputTree->Branch("fatJet3_particleNetWithMass_H4qvsQCD", &fatJet3_particleNetWithMass_H4qvsQCD, "fatJet3_particleNetWithMass_H4qvsQCD/F");
    outputTree->Branch("fatJet3_particleNetWithMass_HbbvsQCD", &fatJet3_particleNetWithMass_HbbvsQCD, "fatJet3_particleNetWithMass_HbbvsQCD/F");
    outputTree->Branch("fatJet3_particleNetWithMass_HccvsQCD", &fatJet3_particleNetWithMass_HccvsQCD, "fatJet3_particleNetWithMass_HccvsQCD/F");
    outputTree->Branch("fatJet3_particleNetWithMass_QCD", &fatJet3_particleNetWithMass_QCD, "fatJet3_particleNetWithMass_QCD/F");
    outputTree->Branch("fatJet3_particleNetWithMass_TvsQCD", &fatJet3_particleNetWithMass_TvsQCD, "fatJet3_particleNetWithMass_TvsQCD/F");
    outputTree->Branch("fatJet3_particleNetWithMass_WvsQCD", &fatJet3_particleNetWithMass_WvsQCD, "fatJet3_particleNetWithMass_WvsQCD/F");
    outputTree->Branch("fatJet3_particleNetWithMass_ZvsQCD", &fatJet3_particleNetWithMass_ZvsQCD, "fatJet3_particleNetWithMass_ZvsQCD/F");
    outputTree->Branch("fatJet3_particleNet_QCD", &fatJet3_particleNet_QCD, "fatJet3_particleNet_QCD/F");
    outputTree->Branch("fatJet3_particleNet_QCD0HF", &fatJet3_particleNet_QCD0HF, "fatJet3_particleNet_QCD0HF/F");
    outputTree->Branch("fatJet3_particleNet_QCD1HF", &fatJet3_particleNet_QCD1HF, "fatJet3_particleNet_QCD1HF/F");
    outputTree->Branch("fatJet3_particleNet_QCD2HF", &fatJet3_particleNet_QCD2HF, "fatJet3_particleNet_QCD2HF/F");
    outputTree->Branch("fatJet3_particleNet_XbbVsQCD", &fatJet3_particleNet_XbbVsQCD, "fatJet3_particleNet_XbbVsQCD/F");
    outputTree->Branch("fatJet3_particleNet_XccVsQCD", &fatJet3_particleNet_XccVsQCD, "fatJet3_particleNet_XccVsQCD/F");
    outputTree->Branch("fatJet3_particleNet_XggVsQCD", &fatJet3_particleNet_XggVsQCD, "fatJet3_particleNet_XggVsQCD/F");
    outputTree->Branch("fatJet3_particleNet_XqqVsQCD", &fatJet3_particleNet_XqqVsQCD, "fatJet3_particleNet_XqqVsQCD/F");
    outputTree->Branch("fatJet3_particleNet_massCorr", &fatJet3_particleNet_massCorr, "fatJet3_particleNet_massCorr/F");
    outputTree->Branch("fatJet3_globalParT_QCD0HF", &fatJet3_globalParT_QCD0HF, "fatJet3_globalParT_QCD0HF/F");
    outputTree->Branch("fatJet3_globalParT_QCD1HF", &fatJet3_globalParT_QCD1HF, "fatJet3_globalParT_QCD1HF/F");
    outputTree->Branch("fatJet3_globalParT_QCD2HF", &fatJet3_globalParT_QCD2HF, "fatJet3_globalParT_QCD2HF/F");
    outputTree->Branch("fatJet3_globalParT_TopW", &fatJet3_globalParT_TopW, "fatJet3_globalParT_TopW/F");
    outputTree->Branch("fatJet3_globalParT_TopbW", &fatJet3_globalParT_TopbW, "fatJet3_globalParT_TopbW/F");
    outputTree->Branch("fatJet3_globalParT_TopbWev", &fatJet3_globalParT_TopbWev, "fatJet3_globalParT_TopbWev/F");
    outputTree->Branch("fatJet3_globalParT_TopbWmv", &fatJet3_globalParT_TopbWmv, "fatJet3_globalParT_TopbWmv/F");
    outputTree->Branch("fatJet3_globalParT_TopbWq", &fatJet3_globalParT_TopbWq, "fatJet3_globalParT_TopbWq/F");
    outputTree->Branch("fatJet3_globalParT_TopbWqq", &fatJet3_globalParT_TopbWqq, "fatJet3_globalParT_TopbWqq/F");
    outputTree->Branch("fatJet3_globalParT_TopbWtauhv", &fatJet3_globalParT_TopbWtauhv, "fatJet3_globalParT_TopbWtauhv/F");
    outputTree->Branch("fatJet3_globalParT_Xbb", &fatJet3_globalParT_Xbb, "fatJet3_globalParT_Xbb/F");
    outputTree->Branch("fatJet3_globalParT_XbbVsQCD", &fatJet3_globalParT_XbbVsQCD, "fatJet3_globalParT_XbbVsQCD/F");
    outputTree->Branch("fatJet3_globalParT_Xcc", &fatJet3_globalParT_Xcc, "fatJet3_globalParT_Xcc/F");
    outputTree->Branch("fatJet3_globalParT_Xcs", &fatJet3_globalParT_Xcs, "fatJet3_globalParT_Xcs/F");
    outputTree->Branch("fatJet3_globalParT_Xgg", &fatJet3_globalParT_Xgg, "fatJet3_globalParT_Xgg/F");
    outputTree->Branch("fatJet3_globalParT_Xqq", &fatJet3_globalParT_Xqq, "fatJet3_globalParT_Xqq/F");
    outputTree->Branch("fatJet3_globalParT_Xtauhtaue", &fatJet3_globalParT_Xtauhtaue, "fatJet3_globalParT_Xtauhtaue/F");
    outputTree->Branch("fatJet3_globalParT_Xtauhtauh", &fatJet3_globalParT_Xtauhtauh, "fatJet3_globalParT_Xtauhtauh/F");
    outputTree->Branch("fatJet3_globalParT_Xtauhtaum", &fatJet3_globalParT_Xtauhtaum, "fatJet3_globalParT_Xtauhtaum/F");
    outputTree->Branch("fatJet3_globalParT_massRes", &fatJet3_globalParT_massRes, "fatJet3_globalParT_massRes/F");
    outputTree->Branch("fatJet3_globalParT_massVis", &fatJet3_globalParT_massVis, "fatJet3_globalParT_massVis/F");
    outputTree->Branch("fatJet3_n2b1", &fatJet3_n2b1, "fatJet3_n2b1/F");
    outputTree->Branch("fatJet3_n3b1", &fatJet3_n3b1, "fatJet3_n3b1/F");
    outputTree->Branch("fatJet3_Tau3OverTau2", &fatJet3_Tau3OverTau2, "fatJet3_Tau3OverTau2/F");
    outputTree->Branch("fatJet3_rawFactor", &fatJet3_rawFactor, "fatJet3_rawFactor/F");
    outputTree->Branch("fatJet3_HasMuon", &fatJet3_HasMuon, "fatJet3_HasMuon/O");
    outputTree->Branch("fatJet3_HasElectron", &fatJet3_HasElectron, "fatJet3_HasElectron/O");
    outputTree->Branch("fatJet3_HasBJetMedium", &fatJet3_HasBJetMedium, "fatJet3_HasBJetMedium/O");
    outputTree->Branch("fatJet3_OppositeHemisphereHasBJet", &fatJet3_OppositeHemisphereHasBJet, "fatJet3_OppositeHemisphereHasBJet/O");
    outputTree->Branch("fatJet3_subJetIdx1_pt",   &fatJet3_subJetIdx1_pt,   "fatJet3_subJetIdx1_pt/F");
    outputTree->Branch("fatJet3_subJetIdx1_eta",  &fatJet3_subJetIdx1_eta,  "fatJet3_subJetIdx1_eta/F");
    outputTree->Branch("fatJet3_subJetIdx1_phi",  &fatJet3_subJetIdx1_phi,  "fatJet3_subJetIdx1_phi/F");
    outputTree->Branch("fatJet3_subJetIdx1_mass", &fatJet3_subJetIdx1_mass, "fatJet3_subJetIdx1_mass/F");
    outputTree->Branch("fatJet3_subJetIdx2_pt",   &fatJet3_subJetIdx2_pt,   "fatJet3_subJetIdx2_pt/F");
    outputTree->Branch("fatJet3_subJetIdx2_eta",  &fatJet3_subJetIdx2_eta,  "fatJet3_subJetIdx2_eta/F");
    outputTree->Branch("fatJet3_subJetIdx2_phi",  &fatJet3_subJetIdx2_phi,  "fatJet3_subJetIdx2_phi/F");
    outputTree->Branch("fatJet3_subJetIdx2_mass", &fatJet3_subJetIdx2_mass, "fatJet3_subJetIdx2_mass/F");
    outputTree->Branch("fatJet3_hadronFlavour", &fatJet3_hadronFlavour, "fatJet3_hadronFlavour/I");
    outputTree->Branch("fatJet3_jetId", &fatJet3_jetId, "fatJet3_jetId/I");
    outputTree->Branch("fatJet3_electronIdx3SJ", &fatJet3_electronIdx3SJ, "fatJet3_electronIdx3SJ/I");
    outputTree->Branch("fatJet3_muonIdx3SJ", &fatJet3_muonIdx3SJ, "fatJet3_muonIdx3SJ/I");
    outputTree->Branch("fatJet3_nConstituents", &fatJet3_nConstituents, "fatJet3_nConstituents/I");
    outputTree->Branch("fatJet3_hadronFlavour", &fatJet3_hadronFlavour, "fatJet3_hadronFlavour/I");
    outputTree->Branch("fatJet3_GenMatchIndex", &fatJet3_GenMatchIndex, "fatJet3_GenMatchIndex/I");
    outputTree->Branch("fatJet3_nBHadrons", &fatJet3_nBHadrons, "fatJet3_nBHadrons/I");
    outputTree->Branch("fatJet3_nCHadrons", &fatJet3_nCHadrons, "fatJet3_nCHadrons/I");
    // legacy test
    outputTree->Branch("fatJet3_particleNetLegacy_Xbb", &fatJet3_particleNetLegacy_Xbb, "fatJet3_particleNetLegacy_Xbb/F");
    outputTree->Branch("fatJet3_particleNetLegacy_Xcc", &fatJet3_particleNetLegacy_Xcc, "fatJet3_particleNetLegacy_Xcc/F");
    outputTree->Branch("fatJet3_particleNetLegacy_Xqq", &fatJet3_particleNetLegacy_Xqq, "fatJet3_particleNetLegacy_Xqq/F");
    outputTree->Branch("fatJet3_particleNetLegacy_QCD", &fatJet3_particleNetLegacy_QCD, "fatJet3_particleNetLegacy_QCD/F");
    outputTree->Branch("fatJet3_particleNetLegacy_QCDb", &fatJet3_particleNetLegacy_QCDb, "fatJet3_particleNetLegacy_QCDb/F");
    outputTree->Branch("fatJet3_particleNetLegacy_QCDbb", &fatJet3_particleNetLegacy_QCDbb, "fatJet3_particleNetLegacy_QCDbb/F");
    outputTree->Branch("fatJet3_particleNetLegacy_QCDothers", &fatJet3_particleNetLegacy_QCDothers, "fatJet3_particleNetLegacy_QCDothers/F");
    outputTree->Branch("fatJet3_particleNetLegacy_mass", &fatJet3_particleNetLegacy_mass, "fatJet3_particleNetLegacy_mass/F");

    //for phase-space overlap removal with VBFHH->4b boosted analysis
    //small R VBF jets
    outputTree->Branch("isVBFtag", &isVBFtag, "isVBFtag/I");
    outputTree->Branch("dijetmass", &dijetmass, "dijetmass/F");
    outputTree->Branch("vbfjet1_Pt", &vbfjet1_Pt, "vbfjet1_Pt/F");
    outputTree->Branch("vbfjet1_Eta", &vbfjet1_Eta, "vbfjet1_Eta/F");
    outputTree->Branch("vbfjet1_Phi", &vbfjet1_Phi, "vbfjet1_Phi/F");
    outputTree->Branch("vbfjet1_Mass", &vbfjet1_Mass, "vbfjet1_Mass/F");
    outputTree->Branch("vbfjet2_Pt", &vbfjet2_Pt, "vbfjet2_Pt/F");
    outputTree->Branch("vbfjet2_Eta", &vbfjet2_Eta, "vbfjet2_Eta/F");
    outputTree->Branch("vbfjet2_Phi", &vbfjet2_Phi, "vbfjet2_Phi/F");
    outputTree->Branch("vbfjet2_Mass", &vbfjet2_Mass, "vbfjet2_Mass/F");

    outputTree->Branch("jet1Pt", &jet1Pt, "jet1Pt/F");
    outputTree->Branch("jet1Eta", &jet1Eta, "jet1Eta/F");
    outputTree->Branch("jet1Phi", &jet1Phi, "jet1Phi/F");
    outputTree->Branch("jet1_rawFactor", &jet1_rawFactor, "jet1_rawFactor/F");
    outputTree->Branch("jet2Pt", &jet2Pt, "jet2Pt/F");
    outputTree->Branch("jet2Eta", &jet2Eta, "jet2Eta/F");
    outputTree->Branch("jet2Phi", &jet2Phi, "jet2Phi/F");
    outputTree->Branch("jet2_rawFactor", &jet2_rawFactor, "jet2_rawFactor/F");
    outputTree->Branch("jet3Pt", &jet3Pt, "jet3Pt/F");
    outputTree->Branch("jet3Eta", &jet3Eta, "jet3Eta/F");
    outputTree->Branch("jet3Phi", &jet3Phi, "jet3Phi/F");
    outputTree->Branch("jet3_rawFactor", &jet3_rawFactor, "jet3_rawFactor/F");
    outputTree->Branch("jet4Pt", &jet4Pt, "jet4Pt/F");
    outputTree->Branch("jet4Eta", &jet4Eta, "jet4Eta/F");
    outputTree->Branch("jet4Phi", &jet4Phi, "jet4Phi/F");
    outputTree->Branch("jet4_rawFactor", &jet4_rawFactor, "jet4_rawFactor/F");

/*
    outputTree->Branch("genPhotonPt", &genPhotonPt, "genPhotonPt/F");
    outputTree->Branch("genPhotonEta", &genPhotonEta, "genPhotonEta/F");
    outputTree->Branch("genPhotonPhi", &genPhotonPhi, "genPhotonPhi/F");
    outputTree->Branch("genHiggs1Pt", &genHiggs1Pt, "genHiggs1Pt/F");
    outputTree->Branch("genHiggs1Eta", &genHiggs1Eta, "genHiggs1Eta/F");
    outputTree->Branch("genHiggs1Phi", &genHiggs1Phi, "genHiggs1Phi/F");
    outputTree->Branch("genHiggs2Pt", &genHiggs2Pt, "genHiggs2Pt/F");
    outputTree->Branch("genHiggs2Eta", &genHiggs2Eta, "genHiggs2Eta/F");
    outputTree->Branch("genHiggs2Phi", &genHiggs2Phi, "genHiggs2Phi/F");
    outputTree->Branch("genLeptonId", &genLeptonId, "genLeptonId/I");
    outputTree->Branch("genLeptonMotherId", &genLeptonMotherId, "genLeptonMotherId/I");
    outputTree->Branch("genLeptonPt", &genLeptonPt, "genLeptonPt/F");
    outputTree->Branch("genLeptonEta", &genLeptonEta, "genLeptonEta/F");
    outputTree->Branch("genLeptonPhi", &genLeptonPhi, "genLeptonPhi/F");
    outputTree->Branch("genWPt", &genWPt, "genWPt/F");
    outputTree->Branch("genWEta", &genWEta, "genWEta/F");
    outputTree->Branch("genWPhi", &genWPhi, "genWPhi/F");
    outputTree->Branch("genZPt", &genZPt, "genZPt/F");
    outputTree->Branch("genZEta", &genZEta, "genZEta/F");
    outputTree->Branch("genZPhi", &genZPhi, "genZPhi/F");
    outputTree->Branch("genMTT", &genMTT, "genMTT/F");
*/

    outputTree->Branch("lep1Pt", &lep1Pt, "lep1Pt/F");
    outputTree->Branch("lep1Eta", &lep1Eta, "lep1Eta/F");
    outputTree->Branch("lep1Phi", &lep1Phi, "lep1Phi/F");
    outputTree->Branch("lep1Id", &lep1Id, "lep1Id/I");
    outputTree->Branch("lep2Pt", &lep2Pt, "lep2Pt/F");
    outputTree->Branch("lep2Eta", &lep2Eta, "lep2Eta/F");
    outputTree->Branch("lep2Phi", &lep2Phi, "lep2Phi/F");
    outputTree->Branch("lep2Id", &lep2Id, "lep2Id/I");
    outputTree->Branch("nBTaggedJets", &nBTaggedJets, "nBTaggedJets/I");
    outputTree->Branch("pho1Pt", &pho1Pt, "pho1Pt/F");
    outputTree->Branch("pho1Eta", &pho1Eta, "pho1Eta/F");
    outputTree->Branch("pho1Phi", &pho1Phi, "pho1Phi/F");  

    outputTree->Branch("HLT_Ele32_WPTight_Gsf",                                               &HLT_Ele32_WPTight_Gsf,                                         "HLT_Ele32_WPTight_Gsf/O");
    outputTree->Branch("HLT_IsoMu27",                                                         &HLT_IsoMu27,                                                   "HLT_IsoMu27/O");
    outputTree->Branch("HLT_Mu50",                                                            &HLT_Mu50,                                                      "HLT_Mu50/O");
    outputTree->Branch("HLT_AK8PFJet425_SoftDropMass40",                                      &HLT_AK8PFJet425_SoftDropMass40,                                "HLT_AK8PFJet425_SoftDropMass40/O");
    outputTree->Branch("HLT_AK8PFJet230_SoftDropMass40",                                      &HLT_AK8PFJet230_SoftDropMass40,                                "HLT_AK8PFJet230_SoftDropMass40/O");
    outputTree->Branch("HLT_AK8PFJet230_SoftDropMass40_PNetBB0p06",                           &HLT_AK8PFJet230_SoftDropMass40_PNetBB0p06,                     "HLT_AK8PFJet230_SoftDropMass40_PNetBB0p06/O");
    outputTree->Branch("HLT_IsoMu50_AK8PFJet230_SoftDropMass40",                              &HLT_IsoMu50_AK8PFJet230_SoftDropMass40,                        "HLT_IsoMu50_AK8PFJet230_SoftDropMass40/O");
    outputTree->Branch("HLT_IsoMu50_AK8PFJet230_SoftDropMass40_PNetBB0p06",                   &HLT_IsoMu50_AK8PFJet230_SoftDropMass40_PNetBB0p06,             "HLT_IsoMu50_AK8PFJet230_SoftDropMass40_PNetBB0p06/O");
    outputTree->Branch("HLT_Ele50_CaloIdVT_GsfTrkIdT_AK8PFJet230_SoftDropMass40",             &HLT_Ele50_CaloIdVT_GsfTrkIdT_AK8PFJet230_SoftDropMass40,       "HLT_Ele50_CaloIdVT_GsfTrkIdT_AK8PFJet230_SoftDropMass40/O");
    outputTree->Branch("HLT_Ele50_CaloIdVT_GsfTrkIdT_AK8PFJet230_SoftDropMass40_PNetBB0p06",  &HLT_Ele50_CaloIdVT_GsfTrkIdT_AK8PFJet230_SoftDropMass40_PNetBB0p06,       "HLT_Ele50_CaloIdVT_GsfTrkIdT_AK8PFJet230_SoftDropMass40_PNetBB0p06/O");

    outputTree->Branch("nGenJetAK8", &nGenJetAK8, "nGenJetAK8/I");
    outputTree->Branch("GenJetAK8_eta", &genJetAK8Eta, "GenJetAK8_eta[nGenJetAK8]/F");
    outputTree->Branch("GenJetAK8_phi", &genJetAK8Phi, "GenJetAK8_phi[nGenJetAK8]/F");
    outputTree->Branch("GenJetAK8_pt", &genJetAK8Pt, "GenJetAK8_pt[nGenJetAK8]/F");
    outputTree->Branch("GenJetAK8_mass", &genJetAK8Mass, "GenJetAK8_mass[nGenJetAK8]/F");

    outputTree->Branch("nGenJet", &nGenJet, "nGenJet/I");
    outputTree->Branch("GenJet_eta", &genJetEta, "GenJet_eta[nGenJet]/F");
    outputTree->Branch("GenJet_phi", &genJetPhi, "GenJet_phi[nGenJet]/F");
    outputTree->Branch("GenJet_pt", &genJetPt, "GenJet_pt[nGenJet]/F");
    outputTree->Branch("GenJet_mass", &genJetMass, "GenJet_mass[nGenJet]/F");
    outputTree->Branch("GenJet_partonFlavour", &genJetPartonFlavor, "GenJet_partonFlavour[nGenJet]/I");


    //-------------------------------
    //random number generator for JMR
    //-------------------------------
    TRandom3* rnd = new TRandom3(1);


    UInt_t NEventsFilled = 0;
 
    //begin loop
    if (fChain == 0) return;
    UInt_t nentries = fChain->GetEntries();
    Long64_t nbytes = 0, nb = 0;

    cout << "nentries = " << nentries << "\n";
    for (UInt_t jentry=0; jentry<nentries;jentry++) {
      //begin event
      if(jentry % 10000 == 0) cout << "Processing entry " << jentry << endl;
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      //Use the non-normalized version because some samples have non-equal genWeights
      weight = genWeight;
      NEvents->SetBinContent( 1, NEvents->GetBinContent(1) + weight);
      nPU_True->Fill(Pileup_nTrueInt);

      //*************************************************************
      // Jet veto Map
      //*************************************************************
      if (JetVetoMap) {
	bool Jet_In_VetoArea=false;
	for(unsigned int i = 0; i < nJet; i++ )
	  {
	    if(Jet_pt[i]<15) continue;
	    if(Jet_jetId[i] < 2) continue;
	    if((Jet_chEmEF[i] + Jet_neEmEF[i]) >=0.9 ) continue;
	    if(Jet_nMuons[i] >= 1 ) continue;
	    Int_t bin_eta = JetVetoMap->GetXaxis()->FindBin(Jet_eta[i]);
	    Int_t bin_phi = JetVetoMap->GetYaxis()->FindBin(Jet_phi[i]);
	    if(JetVetoMap->GetBinContent(bin_eta,bin_phi) > 0)
	      Jet_In_VetoArea = true;
	  }
	if(Jet_In_VetoArea) continue;
      }

// Minimal Selection
        if(!HLT_AK8PFJet425_SoftDropMass40 && !HLT_AK8PFJet230_SoftDropMass40 && !HLT_AK8PFJet230_SoftDropMass40_PNetBB0p06 &&
           !HLT_Mu50 && !HLT_IsoMu50_AK8PFJet230_SoftDropMass40 && !HLT_IsoMu50_AK8PFJet230_SoftDropMass40_PNetBB0p06 &&
           !HLT_Ele32_WPTight_Gsf && !HLT_Ele50_CaloIdVT_GsfTrkIdT_AK8PFJet230_SoftDropMass40 && !HLT_Ele50_CaloIdVT_GsfTrkIdT_AK8PFJet230_SoftDropMass40_PNetBB0p06
          ) continue;

/*
genHiggs1Pt = -1;
genHiggs1Eta = -1;
genHiggs1Phi = -1;
genHiggs2Pt = -1;
genHiggs2Eta = -1;
genHiggs2Phi = -1;
genHH_pt = -99;
genHH_eta = -99;
genHH_phi = -99;
genHH_mass = -99;
genWPt = -1;
genWEta = -1;
genWPhi = -1;
genZPt = -1;
genZEta = -1;
genZPhi = -1;
genTop1Mass = -1;
genTop1Pt = -1;
genTop1Eta = -1;
genTop1Phi = -1;   
genTop2Mass = -1;
genTop2Pt = -1;
genTop2Eta = -1;
genTop2Phi = -1;   
genMTT = -1;
genLeptonPt = -1;
genLeptonEta = -1;
genLeptonPhi = -1;
genLeptonId = 0;
genLeptonMotherId = 0;
genPhotonPt = -1;
genPhotonEta = -1;
genPhotonPhi = -1;
*/

NJets = 0;
MET = -1;
fatJet1_btagDDBvLV2 = -99;
fatJet1_btagDDCvBV2 = -99;
fatJet1_btagDDCvLV2 = -99;
fatJet1_btagDeepB = -99;
fatJet1_btagHbb = -99;
fatJet1_electronIdx3SJ = -99;
fatJet1_eta = -99;
fatJet1_genJetAK8Idx = -99;
fatJet1_hadronFlavour = -99;
fatJet1_jetId = -99;
fatJet1_lsf3 = -99;
fatJet1_mass = -99;
fatJet1_msoftdrop = -99;
fatJet1_muonIdx3SJ = -99;
fatJet1_n2b1 = -99;
fatJet1_n3b1 = -99;
fatJet1_nBHadrons = -99;
fatJet1_nCHadrons = -99;
fatJet1_nConstituents = -99;
fatJet1_particleNetWithMass_H4qvsQCD = -99;
fatJet1_particleNetWithMass_HbbvsQCD = -99;
fatJet1_particleNetWithMass_HccvsQCD = -99;
fatJet1_particleNetWithMass_QCD = -99;
fatJet1_particleNetWithMass_TvsQCD = -99;
fatJet1_particleNetWithMass_WvsQCD = -99;
fatJet1_particleNetWithMass_ZvsQCD = -99;
fatJet1_particleNet_QCD = -99;
fatJet1_particleNet_QCD0HF = -99;
fatJet1_particleNet_QCD1HF = -99;
fatJet1_particleNet_QCD2HF = -99;
fatJet1_particleNet_XbbVsQCD = -99;
fatJet1_particleNet_XccVsQCD = -99;
fatJet1_particleNet_XggVsQCD = -99;
fatJet1_particleNet_XqqVsQCD = -99;
fatJet1_particleNet_XteVsQCD = -99;
fatJet1_particleNet_XtmVsQCD = -99;
fatJet1_particleNet_XttVsQCD = -99;
fatJet1_particleNet_massCorr = -99;
fatJet1_globalParT_QCD0HF = -99;
fatJet1_globalParT_QCD1HF = -99;
fatJet1_globalParT_QCD2HF = -99;
fatJet1_globalParT_TopW = -99;
fatJet1_globalParT_TopbW = -99;
fatJet1_globalParT_TopbWev = -99;
fatJet1_globalParT_TopbWmv = -99;
fatJet1_globalParT_TopbWq = -99;
fatJet1_globalParT_TopbWqq = -99;
fatJet1_globalParT_TopbWtauhv = -99;
fatJet1_globalParT_Xbb = -99;
fatJet1_globalParT_XbbVsQCD = -99;
fatJet1_globalParT_Xcc = -99;
fatJet1_globalParT_Xcs = -99;
fatJet1_globalParT_Xgg = -99;
fatJet1_globalParT_Xqq = -99;
fatJet1_globalParT_Xtauhtaue = -99;
fatJet1_globalParT_Xtauhtauh = -99;
fatJet1_globalParT_Xtauhtaum = -99;
fatJet1_globalParT_massRes = -99;
fatJet1_globalParT_massVis = -99;
fatJet1_phi = -99;
fatJet1_pt = -99;
fatJet1_rawFactor = -99;
fatJet1_subJetIdx1 = -1;
fatJet1_subJetIdx1_pt = -99;
fatJet1_subJetIdx1_eta = -99;
fatJet1_subJetIdx1_phi = -99;
fatJet1_subJetIdx1_mass = -99;
fatJet1_subJetIdx2 = -1;
fatJet1_subJetIdx2_pt = -99;
fatJet1_subJetIdx2_eta = -99;
fatJet1_subJetIdx2_phi = -99;
fatJet1_subJetIdx2_mass = -99;
fatJet1_tau1 = -99;
fatJet1_tau2 = -99;
fatJet1_tau3 = -99;
fatJet1_tau4 = -99;
fatJet1_GenMatchIndex = -99;
fatJet1_Tau3OverTau2 = -99;
fatJet1__n2b1 = -99; 
fatJet1_HasMuon = 0;
fatJet1_HasElectron = 0;
fatJet1_HasBJetMedium = 0;
fatJet1_OppositeHemisphereHasBJet = 0;
// legacy test
fatJet1_particleNetLegacy_Xbb = -99;
fatJet1_particleNetLegacy_Xcc = -99;
fatJet1_particleNetLegacy_Xqq = -99;
fatJet1_particleNetLegacy_QCD = -99;
fatJet1_particleNetLegacy_QCDb = -99;
fatJet1_particleNetLegacy_QCDbb = -99;
fatJet1_particleNetLegacy_QCDothers = -99;
fatJet1_particleNetLegacy_mass = -99;

fatJet2_area = -99;
fatJet2_btagDDBvLV2 = -99;
fatJet2_btagDDCvBV2 = -99;
fatJet2_btagDDCvLV2 = -99;
fatJet2_btagDeepB = -99;
fatJet2_btagHbb = -99;
fatJet2_electronIdx3SJ = -99;
fatJet2_eta = -99;
fatJet2_genJetAK8Idx = -99;
fatJet2_hadronFlavour = -99;
fatJet2_jetId = -99;
fatJet2_lsf3 = -99;
fatJet2_mass = -99;
fatJet2_msoftdrop = -99;
fatJet2_muonIdx3SJ = -99;
fatJet2_n2b1 = -99;
fatJet2_n3b1 = -99;
fatJet2_nBHadrons = -99;
fatJet2_nCHadrons = -99;
fatJet2_nConstituents = -99;
fatJet2_particleNetWithMass_H4qvsQCD = -99;
fatJet2_particleNetWithMass_HbbvsQCD = -99;
fatJet2_particleNetWithMass_HccvsQCD = -99;
fatJet2_particleNetWithMass_QCD = -99;
fatJet2_particleNetWithMass_TvsQCD = -99;
fatJet2_particleNetWithMass_WvsQCD = -99;
fatJet2_particleNetWithMass_ZvsQCD = -99;
fatJet2_particleNet_QCD = -99;
fatJet2_particleNet_QCD0HF = -99;
fatJet2_particleNet_QCD1HF = -99;
fatJet2_particleNet_QCD2HF = -99;
fatJet2_particleNet_XbbVsQCD = -99;
fatJet2_particleNet_XccVsQCD = -99;
fatJet2_particleNet_XggVsQCD = -99;
fatJet2_particleNet_XqqVsQCD = -99;
fatJet2_particleNet_XteVsQCD = -99;
fatJet2_particleNet_XtmVsQCD = -99;
fatJet2_particleNet_XttVsQCD = -99;
fatJet2_particleNet_massCorr = -99;
fatJet2_globalParT_QCD0HF = -99;
fatJet2_globalParT_QCD1HF = -99;
fatJet2_globalParT_QCD2HF = -99;
fatJet2_globalParT_TopW = -99;
fatJet2_globalParT_TopbW = -99;
fatJet2_globalParT_TopbWev = -99;
fatJet2_globalParT_TopbWmv = -99;
fatJet2_globalParT_TopbWq = -99;
fatJet2_globalParT_TopbWqq = -99;
fatJet2_globalParT_TopbWtauhv = -99;
fatJet2_globalParT_Xbb = -99;
fatJet2_globalParT_XbbVsQCD = -99;
fatJet2_globalParT_Xcc = -99;
fatJet2_globalParT_Xcs = -99;
fatJet2_globalParT_Xgg = -99;
fatJet2_globalParT_Xqq = -99;
fatJet2_globalParT_Xtauhtaue = -99;
fatJet2_globalParT_Xtauhtauh = -99;
fatJet2_globalParT_Xtauhtaum = -99;
fatJet2_globalParT_massRes = -99;
fatJet2_globalParT_massVis = -99;
fatJet2_phi = -99;
fatJet2_pt = -99;
fatJet2_rawFactor = -99;
fatJet2_subJetIdx1 = -1;
fatJet2_subJetIdx1_pt = -99;
fatJet2_subJetIdx1_eta = -99;
fatJet2_subJetIdx1_phi = -99;
fatJet2_subJetIdx1_mass = -99;
fatJet2_subJetIdx2 = -1;
fatJet2_subJetIdx2_pt = -99;
fatJet2_subJetIdx2_eta = -99;
fatJet2_subJetIdx2_phi = -99;
fatJet2_subJetIdx2_mass = -99;
fatJet2_tau1 = -99;
fatJet2_tau2 = -99;
fatJet2_tau3 = -99;
fatJet2_tau4 = -99;
fatJet2_GenMatchIndex = -99;
fatJet2_Tau3OverTau2 = -99;
fatJet2__n2b1 = -99; 
fatJet2_HasMuon = 0;
fatJet2_HasElectron = 0;
fatJet2_HasBJetMedium = 0;
fatJet2_OppositeHemisphereHasBJet = 0;
// legacy test
fatJet2_particleNetLegacy_Xbb = -99;
fatJet2_particleNetLegacy_Xcc = -99;
fatJet2_particleNetLegacy_Xqq = -99;
fatJet2_particleNetLegacy_QCD = -99;
fatJet2_particleNetLegacy_QCDb = -99;
fatJet2_particleNetLegacy_QCDbb = -99;
fatJet2_particleNetLegacy_QCDothers = -99;
fatJet2_particleNetLegacy_mass = -99;

fatJet3_area = -99;
fatJet3_btagDDBvLV2 = -99;
fatJet3_btagDDCvBV2 = -99;
fatJet3_btagDDCvLV2 = -99;
fatJet3_btagDeepB = -99;
fatJet3_btagHbb = -99;
fatJet3_electronIdx3SJ = -99;
fatJet3_eta = -99;
fatJet3_genJetAK8Idx = -99;
fatJet3_hadronFlavour = -99;
fatJet3_jetId = -99;
fatJet3_lsf3 = -99;
fatJet3_mass = -99;
fatJet3_msoftdrop = -99;
fatJet3_muonIdx3SJ = -99;
fatJet3_n2b1 = -99;
fatJet3_n3b1 = -99;
fatJet3_nBHadrons = -99;
fatJet3_nCHadrons = -99;
fatJet3_nConstituents = -99;
fatJet3_particleNetWithMass_H4qvsQCD = -99;
fatJet3_particleNetWithMass_HbbvsQCD = -99;
fatJet3_particleNetWithMass_HccvsQCD = -99;
fatJet3_particleNetWithMass_QCD = -99;
fatJet3_particleNetWithMass_TvsQCD = -99;
fatJet3_particleNetWithMass_WvsQCD = -99;
fatJet3_particleNetWithMass_ZvsQCD = -99;
fatJet3_particleNet_QCD = -99;
fatJet3_particleNet_QCD0HF = -99;
fatJet3_particleNet_QCD1HF = -99;
fatJet3_particleNet_QCD2HF = -99;
fatJet3_particleNet_XbbVsQCD = -99;
fatJet3_particleNet_XccVsQCD = -99;
fatJet3_particleNet_XggVsQCD = -99;
fatJet3_particleNet_XqqVsQCD = -99;
fatJet3_particleNet_XteVsQCD = -99;
fatJet3_particleNet_XtmVsQCD = -99;
fatJet3_particleNet_XttVsQCD = -99;
fatJet3_particleNet_massCorr = -99;
fatJet3_globalParT_QCD0HF = -99;
fatJet3_globalParT_QCD1HF = -99;
fatJet3_globalParT_QCD2HF = -99;
fatJet3_globalParT_TopW = -99;
fatJet3_globalParT_TopbW = -99;
fatJet3_globalParT_TopbWev = -99;
fatJet3_globalParT_TopbWmv = -99;
fatJet3_globalParT_TopbWq = -99;
fatJet3_globalParT_TopbWqq = -99;
fatJet3_globalParT_TopbWtauhv = -99;
fatJet3_globalParT_Xbb = -99;
fatJet3_globalParT_XbbVsQCD = -99;
fatJet3_globalParT_Xcc = -99;
fatJet3_globalParT_Xcs = -99;
fatJet3_globalParT_Xgg = -99;
fatJet3_globalParT_Xqq = -99;
fatJet3_globalParT_Xtauhtaue = -99;
fatJet3_globalParT_Xtauhtauh = -99;
fatJet3_globalParT_Xtauhtaum = -99;
fatJet3_globalParT_massRes = -99;
fatJet3_globalParT_massVis = -99;
fatJet3_phi = -99;
fatJet3_pt = -99;
fatJet3_rawFactor = -99;
fatJet3_subJetIdx1 = -1;
fatJet3_subJetIdx1_pt = -99;
fatJet3_subJetIdx1_eta = -99;
fatJet3_subJetIdx1_phi = -99;
fatJet3_subJetIdx1_mass = -99;
fatJet3_subJetIdx2 = -1;
fatJet3_subJetIdx2_pt = -99;
fatJet3_subJetIdx2_eta = -99;
fatJet3_subJetIdx2_phi = -99;
fatJet3_subJetIdx2_mass = -99;
fatJet3_tau1 = -99;
fatJet3_tau2 = -99;
fatJet3_tau3 = -99;
fatJet3_tau4 = -99;
fatJet3_GenMatchIndex = -99;
fatJet3_Tau3OverTau2 = -99;
fatJet3__n2b1 = -99; 
fatJet3_HasMuon = 0;
fatJet3_HasElectron = 0;
fatJet3_HasBJetMedium = 0;
fatJet3_OppositeHemisphereHasBJet = 0;
// legacy test
fatJet3_particleNetLegacy_Xbb = -99;
fatJet3_particleNetLegacy_Xcc = -99;
fatJet3_particleNetLegacy_Xqq = -99;
fatJet3_particleNetLegacy_QCD = -99;
fatJet3_particleNetLegacy_QCDb = -99;
fatJet3_particleNetLegacy_QCDbb = -99;
fatJet3_particleNetLegacy_QCDothers = -99;
fatJet3_particleNetLegacy_mass = -99;

isVBFtag = 0;
dijetmass = -99;
vbfjet1_Pt = -99;
vbfjet1_Eta = -99;
vbfjet1_Phi = -99;
vbfjet1_Mass = -99;
vbfjet2_Pt = -99;
vbfjet2_Eta = -99;
vbfjet2_Phi = -99;
vbfjet2_Mass = -99;

lep1Pt = -99;
lep1Eta = -99;
lep1Phi = -99;
lep1Id = 0;
lep2Pt = -99;
lep2Eta = -99;
lep2Phi = -99;
lep2Id = 0;
pho1Pt = -99;
pho1Eta = -99;
pho1Phi = -99;
jet1Pt = -99;
jet1Eta = -99;
jet1Phi = -99;
jet1_rawFactor = -99;
jet2Pt = -99;
jet2Eta = -99;
jet2Phi = -99;
jet2_rawFactor = -99;
jet3Pt = -99;
jet3Eta = -99;
jet3Phi = -99;
jet3_rawFactor = -99;
jet4Pt = -99;
jet4Eta = -99;
jet4Phi = -99;
jet4_rawFactor = -99;
nBTaggedJets = 0;


//        if(nFatJet<2) continue;
        if(nFatJet<1) continue;
        if(FatJet_pt[0] < 200 ||  FatJet_msoftdrop[0] < 30 ) continue;
//        if(FatJet_pt[1] < 200 ||  FatJet_msoftdrop[1] < 40 ) continue;

      //------------------------------
      //----Event variables------------
      //------------------------------
      MET = MET_pt;

     if (isData) {nGenJet =0; nGenJetAK8=0;}
      for(int i = 0; i < nGenJet; i++) {
        genJetEta[i] = -999;
        genJetPhi[i] = -999;
        genJetPt[i] = -999;
        genJetMass[i] = -999;
        genJetPartonFlavor[i] = -999;
      }
      for(int i = 0; i < nGenJetAK8; i++) {
        genJetAK8Eta[i] = -999;
        genJetAK8Phi[i] = -999;
        genJetAK8Pt[i] = -999;
        genJetAK8Mass[i] = -999;
      }

      //------------------------------
      //----gen-jets------------
      //------------------------------
     if (!isData){
      for(int i = 0; i < nGenJet; i++) {
       genJetEta[i] = GenJet_eta[i];
       genJetPhi[i] = GenJet_phi[i];
       genJetPt[i] = GenJet_pt[i];
       genJetMass[i] = GenJet_mass[i];
       genJetPartonFlavor[i] = GenJet_partonFlavour[i];
      }

      for(int i = 0; i < nGenJetAK8; i++) {
       genJetAK8Eta[i] = GenJetAK8_eta[i];
       genJetAK8Phi[i] = GenJetAK8_phi[i];
       genJetAK8Pt[i] = GenJetAK8_pt[i];
       genJetAK8Mass[i] = GenJetAK8_mass[i];
      }
     }

/*
      //------------------------------
      //----Gen particles------------
      //------------------------------
      int current_mIndex = -1;
      std::vector< TLorentzVector > genHiggsVector;
      if (!isData) {

	for(int i = 0; i < nGenPart; i++) {
	  if( abs(GenPart_pdgId[i]) == 5  && GenPart_pdgId[GenPart_genPartIdxMother[i]] == 25 && current_mIndex != GenPart_genPartIdxMother[i] ) {
	    TLorentzVector h;
	    h.SetPtEtaPhiM( GenPart_pt[GenPart_genPartIdxMother[i]], GenPart_eta[GenPart_genPartIdxMother[i]], GenPart_phi[GenPart_genPartIdxMother[i]], GenPart_mass[GenPart_genPartIdxMother[i]] );
	    genHiggsVector.push_back(h);
	    current_mIndex = GenPart_genPartIdxMother[i];
	  }

	  if ( (abs(GenPart_pdgId[i]) == 11 || abs(GenPart_pdgId[i]) == 13)
	       && GenPart_pt[i] > 10
	       && (abs(GenPart_pdgId[GenPart_genPartIdxMother[i]]) == 23 || abs(GenPart_pdgId[GenPart_genPartIdxMother[i]]) == 24 || abs(GenPart_pdgId[GenPart_genPartIdxMother[i]]) == 15)
	       && GenPart_pt[i] > genLeptonPt 
	       ) {
	    genLeptonId = GenPart_pdgId[i];
	    genLeptonMotherId = GenPart_pdgId[GenPart_genPartIdxMother[i]];
	    genLeptonPt = GenPart_pt[i];
	    genLeptonEta = GenPart_eta[i];
	    genLeptonPhi = GenPart_phi[i];	    
	  }	       
	  
	  if ( GenPart_pdgId[i] == 22 && GenPart_pdgId[GenPart_genPartIdxMother[i]] == 25 ) {
	    genPhotonPt = GenPart_pt[i];
	    genPhotonEta = GenPart_eta[i];
	    genPhotonPhi = GenPart_phi[i];
	  }

	  if ( abs(GenPart_pdgId[i]) == 23 
	       && GenPart_status[i] == 62 
	       ) {
	    genZPt = GenPart_pt[i];
	    genZEta = GenPart_eta[i];
	    genZPhi = GenPart_phi[i];
	  }

	  if ( abs(GenPart_pdgId[i]) == 24
	       && GenPart_status[i] == 62
	       ) {
	    genWPt = GenPart_pt[i];
	    genWEta = GenPart_eta[i];
	    genWPhi = GenPart_phi[i];
	  }

	  if ( GenPart_pdgId[i] == 6 
	       && GenPart_status[i] == 22 
	       ) {
	    genTop1Mass = GenPart_mass[i];
	    genTop1Pt = GenPart_pt[i];
	    genTop1Eta = GenPart_eta[i];
	    genTop1Phi = GenPart_phi[i];	   
	  }
	  if ( GenPart_pdgId[i] == -6 
	       && GenPart_status[i] == 22 
	       ) {
	    genTop2Mass = GenPart_mass[i];
	    genTop2Pt = GenPart_pt[i];
	    genTop2Eta = GenPart_eta[i];
	    genTop2Phi = GenPart_phi[i];	   
	  }
	  TLorentzVector Top1Vector;
	  Top1Vector.SetPtEtaPhiM( genTop1Pt, genTop1Eta, genTop1Phi, genTop1Mass );
	  TLorentzVector Top2Vector;
	  Top2Vector.SetPtEtaPhiM( genTop2Pt, genTop2Eta, genTop2Phi, genTop2Mass );
	  genMTT = (Top1Vector+Top2Vector).M();

	}

	if(genHiggsVector.size() >= 1) {
	  //filling tree_out variables
	  genHiggs1Pt = genHiggsVector[0].Pt();
	  genHiggs1Eta = genHiggsVector[0].Eta();
	  genHiggs1Phi = genHiggsVector[0].Phi();
	  //
	  if(genHiggsVector.size() >= 2) {
	    genHiggs2Pt = genHiggsVector[1].Pt();
	    genHiggs2Eta = genHiggsVector[1].Eta();
	    genHiggs2Phi = genHiggsVector[1].Phi();	
	  }
	}

	//gen level
	if(genHiggsVector.size() > 1) { 
	  genHH_pt = (genHiggsVector[0]+genHiggsVector[1]).Pt();
	  genHH_eta = (genHiggsVector[0]+genHiggsVector[1]).Eta();
	  genHH_phi = (genHiggsVector[0]+genHiggsVector[1]).Phi();
	  genHH_mass= (genHiggsVector[0]+genHiggsVector[1]).M();
	}
      
      } //end if !data
*/

      //------------------------------------------------------
      //----------Fill PT-ordered FatJet (1,2,3)
      //------------------------------------------------------
      fatJet1_pt        = FatJet_pt[0];
      fatJet1_eta       = FatJet_eta[0];
      fatJet1_phi       = FatJet_phi[0];
      fatJet1_mass      = FatJet_mass[0];
      fatJet1_msoftdrop = FatJet_msoftdrop[0];
      fatJet1_btagDDBvLV2 = FatJet_btagDDBvLV2[0];
      fatJet1_btagDDCvBV2 = FatJet_btagDDCvBV2[0];
      fatJet1_btagDDCvLV2 = FatJet_btagDDCvLV2[0];
      fatJet1_btagDeepB = FatJet_btagDeepB[0];
      fatJet1_btagHbb   = FatJet_btagHbb[0];
      fatJet1_particleNetWithMass_H4qvsQCD = FatJet_particleNetWithMass_H4qvsQCD[0];
      fatJet1_particleNetWithMass_HbbvsQCD = FatJet_particleNetWithMass_HbbvsQCD[0];
      fatJet1_particleNetWithMass_HccvsQCD = FatJet_particleNetWithMass_HccvsQCD[0];
      fatJet1_particleNetWithMass_QCD = FatJet_particleNetWithMass_QCD[0];
      fatJet1_particleNetWithMass_TvsQCD = FatJet_particleNetWithMass_TvsQCD[0];
      fatJet1_particleNetWithMass_WvsQCD = FatJet_particleNetWithMass_WvsQCD[0];
      fatJet1_particleNetWithMass_ZvsQCD = FatJet_particleNetWithMass_ZvsQCD[0];
      fatJet1_particleNet_QCD = FatJet_particleNet_QCD[0];
      fatJet1_particleNet_QCD0HF = FatJet_particleNet_QCD0HF[0];
      fatJet1_particleNet_QCD1HF = FatJet_particleNet_QCD1HF[0];
      fatJet1_particleNet_QCD2HF = FatJet_particleNet_QCD2HF[0];
      fatJet1_particleNet_XbbVsQCD = FatJet_particleNet_XbbVsQCD[0];
      fatJet1_particleNet_XccVsQCD = FatJet_particleNet_XccVsQCD[0];
      fatJet1_particleNet_XggVsQCD = FatJet_particleNet_XggVsQCD[0];
      fatJet1_particleNet_XqqVsQCD = FatJet_particleNet_XqqVsQCD[0];
      fatJet1_particleNet_massCorr = FatJet_particleNet_massCorr[0];
      fatJet1_globalParT_QCD0HF     = FatJet_globalParT_QCD0HF[0]    ;
      fatJet1_globalParT_QCD1HF     = FatJet_globalParT_QCD1HF[0]    ;
      fatJet1_globalParT_QCD2HF     = FatJet_globalParT_QCD2HF[0]    ;
      fatJet1_globalParT_TopW       = FatJet_globalParT_TopW[0]     ;
      fatJet1_globalParT_TopbW      = FatJet_globalParT_TopbW[0]     ;
      fatJet1_globalParT_TopbWev    = FatJet_globalParT_TopbWev[0]   ;
      fatJet1_globalParT_TopbWmv    = FatJet_globalParT_TopbWmv[0]   ;
      fatJet1_globalParT_TopbWq     = FatJet_globalParT_TopbWq[0]    ;
      fatJet1_globalParT_TopbWqq    = FatJet_globalParT_TopbWqq[0]   ;
      fatJet1_globalParT_TopbWtauhv = FatJet_globalParT_TopbWtauhv[0];
      fatJet1_globalParT_Xbb        = FatJet_globalParT_Xbb[0]       ;
      fatJet1_globalParT_XbbVsQCD   = FatJet_globalParT_XbbVsQCD[0]  ;
      fatJet1_globalParT_Xcc        = FatJet_globalParT_Xcc[0]       ;
      fatJet1_globalParT_Xcs        = FatJet_globalParT_Xcs[0]       ;
      fatJet1_globalParT_Xgg        = FatJet_globalParT_Xgg[0]       ;
      fatJet1_globalParT_Xqq        = FatJet_globalParT_Xqq[0]       ;
      fatJet1_globalParT_Xtauhtaue  = FatJet_globalParT_Xtauhtaue[0] ;
      fatJet1_globalParT_Xtauhtauh  = FatJet_globalParT_Xtauhtauh[0] ;
      fatJet1_globalParT_Xtauhtaum  = FatJet_globalParT_Xtauhtaum[0] ;
      fatJet1_globalParT_massRes    = FatJet_globalParT_massRes[0]   ;
      fatJet1_globalParT_massVis    = FatJet_globalParT_massVis[0]   ;      
      fatJet1_n2b1 = FatJet_n2b1[0];
      fatJet1_n3b1 = FatJet_n3b1[0];
      fatJet1_rawFactor = FatJet_rawFactor[0];
      fatJet1_Tau3OverTau2 = FatJet_tau3[0] /  FatJet_tau2[0];
      fatJet1_subJetIdx1      = FatJet_subJetIdx1[0];
      fatJet1_subJetIdx1_pt   = SubJet_pt[fatJet1_subJetIdx1];
      fatJet1_subJetIdx1_eta  = SubJet_eta[fatJet1_subJetIdx1];
      fatJet1_subJetIdx1_phi  = SubJet_phi[fatJet1_subJetIdx1];
      fatJet1_subJetIdx1_mass = SubJet_mass[fatJet1_subJetIdx1];
      fatJet1_subJetIdx2      = FatJet_subJetIdx2[0];
      fatJet1_subJetIdx2_pt   = SubJet_pt[fatJet1_subJetIdx2];
      fatJet1_subJetIdx2_eta  = SubJet_eta[fatJet1_subJetIdx2];
      fatJet1_subJetIdx2_phi  = SubJet_phi[fatJet1_subJetIdx2];
      fatJet1_subJetIdx2_mass = SubJet_mass[fatJet1_subJetIdx2];
      fatJet1_jetId           = FatJet_jetId[0];
      fatJet1_electronIdx3SJ  = FatJet_electronIdx3SJ[0];
      fatJet1_muonIdx3SJ      = FatJet_muonIdx3SJ[0];
      fatJet1_nConstituents   = FatJet_nConstituents[0];
      fatJet1_hadronFlavour   = FatJet_hadronFlavour[0];
      fatJet1_GenMatchIndex   = FatJet_genJetAK8Idx[0];
      fatJet1_nBHadrons       = FatJet_nBHadrons[0];
      fatJet1_nCHadrons       = FatJet_nCHadrons[0];
      // legacy test
      fatJet1_particleNetLegacy_Xbb = FatJet_particleNetLegacy_Xbb[0];
      fatJet1_particleNetLegacy_Xcc = FatJet_particleNetLegacy_Xcc[0];
      fatJet1_particleNetLegacy_Xqq = FatJet_particleNetLegacy_Xqq[0];
      fatJet1_particleNetLegacy_QCD = FatJet_particleNetLegacy_QCD[0];
      fatJet1_particleNetLegacy_QCDb = FatJet_particleNetLegacy_QCDb[0];
      fatJet1_particleNetLegacy_QCDbb = FatJet_particleNetLegacy_QCDbb[0];
      fatJet1_particleNetLegacy_QCDothers = FatJet_particleNetLegacy_QCDothers[0];
      fatJet1_particleNetLegacy_mass = FatJet_particleNetLegacy_mass[0];

       double btagMediumCut = 0.3064 ;   // PreEE
//      double btagMediumCut = 0.3033;     // PostEE

      for(unsigned int q = 0; q < nJet; q++ )
        if (Jet_pt[q] > 25 && Jet_btagDeepFlavB[q] > btagMediumCut && deltaPhi(fatJet1_phi, Jet_phi[q]) > 2.5)
           {fatJet1_OppositeHemisphereHasBJet = true;  break;}

      for(unsigned int q = 0; q < nMuon; q++ )
        if (Muon_pt[q] > 30 && Muon_looseId[q] && deltaR(fatJet1_eta , fatJet1_phi, Muon_eta[q], Muon_phi[q]) < 1.0) 
        {fatJet1_HasMuon = true; break;}

      for(unsigned int q = 0; q < nElectron; q++ )
        if (Electron_pt[q] > 30 && deltaR(fatJet1_eta , fatJet1_phi, Electron_eta[q], Electron_phi[q]) < 1.0)
        {fatJet1_HasElectron = true; break;}

      for(unsigned int q = 0; q < nJet; q++ )
        if (Jet_btagDeepFlavB[q] > btagMediumCut && deltaR(fatJet1_eta , fatJet1_phi, Jet_eta[q], Jet_phi[q]) < 1.0)
        {fatJet1_HasBJetMedium = true; break;}



    if (nFatJet>1 && FatJet_pt[1] > 200 && FatJet_msoftdrop[1] >40){
      fatJet2_pt        = FatJet_pt[1];
      fatJet2_eta       = FatJet_eta[1];
      fatJet2_phi       = FatJet_phi[1];
      fatJet2_mass      = FatJet_mass[1];
      fatJet2_msoftdrop = FatJet_msoftdrop[1];
      fatJet2_btagDDBvLV2 = FatJet_btagDDBvLV2[1];
      fatJet2_btagDDCvBV2 = FatJet_btagDDCvBV2[1];
      fatJet2_btagDDCvLV2 = FatJet_btagDDCvLV2[1];
      fatJet2_btagDeepB = FatJet_btagDeepB[1];
      fatJet2_btagHbb   = FatJet_btagHbb[1];
      fatJet2_particleNetWithMass_H4qvsQCD = FatJet_particleNetWithMass_H4qvsQCD[1];
      fatJet2_particleNetWithMass_HbbvsQCD = FatJet_particleNetWithMass_HbbvsQCD[1];
      fatJet2_particleNetWithMass_HccvsQCD = FatJet_particleNetWithMass_HccvsQCD[1];
      fatJet2_particleNetWithMass_QCD = FatJet_particleNetWithMass_QCD[1];
      fatJet2_particleNetWithMass_TvsQCD = FatJet_particleNetWithMass_TvsQCD[1];
      fatJet2_particleNetWithMass_WvsQCD = FatJet_particleNetWithMass_WvsQCD[1];
      fatJet2_particleNetWithMass_ZvsQCD = FatJet_particleNetWithMass_ZvsQCD[1];
      fatJet2_particleNet_QCD = FatJet_particleNet_QCD[1];
      fatJet2_particleNet_QCD0HF = FatJet_particleNet_QCD0HF[1];
      fatJet2_particleNet_QCD1HF = FatJet_particleNet_QCD1HF[1];
      fatJet2_particleNet_QCD2HF = FatJet_particleNet_QCD2HF[1];
      fatJet2_particleNet_XbbVsQCD = FatJet_particleNet_XbbVsQCD[1];
      fatJet2_particleNet_XccVsQCD = FatJet_particleNet_XccVsQCD[1];
      fatJet2_particleNet_XggVsQCD = FatJet_particleNet_XggVsQCD[1];
      fatJet2_particleNet_XqqVsQCD = FatJet_particleNet_XqqVsQCD[1];
      fatJet2_particleNet_massCorr = FatJet_particleNet_massCorr[1];
      fatJet2_globalParT_QCD0HF     = FatJet_globalParT_QCD0HF[1]    ;
      fatJet2_globalParT_QCD1HF     = FatJet_globalParT_QCD1HF[1]    ;
      fatJet2_globalParT_QCD2HF     = FatJet_globalParT_QCD2HF[1]    ;
      fatJet2_globalParT_TopW       = FatJet_globalParT_TopW[1]     ;
      fatJet2_globalParT_TopbW      = FatJet_globalParT_TopbW[1]     ;
      fatJet2_globalParT_TopbWev    = FatJet_globalParT_TopbWev[1]   ;
      fatJet2_globalParT_TopbWmv    = FatJet_globalParT_TopbWmv[1]   ;
      fatJet2_globalParT_TopbWq     = FatJet_globalParT_TopbWq[1]    ;
      fatJet2_globalParT_TopbWqq    = FatJet_globalParT_TopbWqq[1]   ;
      fatJet2_globalParT_TopbWtauhv = FatJet_globalParT_TopbWtauhv[1];
      fatJet2_globalParT_Xbb        = FatJet_globalParT_Xbb[1]       ;
      fatJet2_globalParT_XbbVsQCD   = FatJet_globalParT_XbbVsQCD[1]  ;
      fatJet2_globalParT_Xcc        = FatJet_globalParT_Xcc[1]       ;
      fatJet2_globalParT_Xcs        = FatJet_globalParT_Xcs[1]       ;
      fatJet2_globalParT_Xgg        = FatJet_globalParT_Xgg[1]       ;
      fatJet2_globalParT_Xqq        = FatJet_globalParT_Xqq[1]       ;
      fatJet2_globalParT_Xtauhtaue  = FatJet_globalParT_Xtauhtaue[1] ;
      fatJet2_globalParT_Xtauhtauh  = FatJet_globalParT_Xtauhtauh[1] ;
      fatJet2_globalParT_Xtauhtaum  = FatJet_globalParT_Xtauhtaum[1] ;
      fatJet2_globalParT_massRes    = FatJet_globalParT_massRes[1]   ;
      fatJet2_globalParT_massVis    = FatJet_globalParT_massVis[1]   ;      
      fatJet2_n2b1 = FatJet_n2b1[1];
      fatJet2_n3b1 = FatJet_n3b1[1];
      fatJet2_rawFactor = FatJet_rawFactor[1];
      fatJet2_Tau3OverTau2 = FatJet_tau3[1] /  FatJet_tau2[1];
      fatJet2_subJetIdx1      = FatJet_subJetIdx1[1];
      fatJet2_subJetIdx1_pt   = SubJet_pt[fatJet2_subJetIdx1];
      fatJet2_subJetIdx1_eta  = SubJet_eta[fatJet2_subJetIdx1];
      fatJet2_subJetIdx1_phi  = SubJet_phi[fatJet2_subJetIdx1];
      fatJet2_subJetIdx1_mass = SubJet_mass[fatJet2_subJetIdx1];
      fatJet2_subJetIdx2      = FatJet_subJetIdx2[1];
      fatJet2_subJetIdx2_pt   = SubJet_pt[fatJet2_subJetIdx2];
      fatJet2_subJetIdx2_eta  = SubJet_eta[fatJet2_subJetIdx2];
      fatJet2_subJetIdx2_phi  = SubJet_phi[fatJet2_subJetIdx2];
      fatJet2_subJetIdx2_mass = SubJet_mass[fatJet2_subJetIdx2];
      fatJet2_jetId           = FatJet_jetId[1];
      fatJet2_electronIdx3SJ  = FatJet_electronIdx3SJ[1];
      fatJet2_muonIdx3SJ      = FatJet_muonIdx3SJ[1];
      fatJet2_nConstituents   = FatJet_nConstituents[1];
      fatJet2_hadronFlavour   = FatJet_hadronFlavour[1];
      fatJet2_GenMatchIndex   = FatJet_genJetAK8Idx[1];
      fatJet2_nBHadrons       = FatJet_nBHadrons[1];
      fatJet2_nCHadrons       = FatJet_nCHadrons[1];
      // legacy test
      fatJet2_particleNetLegacy_Xbb = FatJet_particleNetLegacy_Xbb[1];
      fatJet2_particleNetLegacy_Xcc = FatJet_particleNetLegacy_Xcc[1];
      fatJet2_particleNetLegacy_Xqq = FatJet_particleNetLegacy_Xqq[1];
      fatJet2_particleNetLegacy_QCD = FatJet_particleNetLegacy_QCD[1];
      fatJet2_particleNetLegacy_QCDb = FatJet_particleNetLegacy_QCDb[1];
      fatJet2_particleNetLegacy_QCDbb = FatJet_particleNetLegacy_QCDbb[1];
      fatJet2_particleNetLegacy_QCDothers = FatJet_particleNetLegacy_QCDothers[1];
      fatJet2_particleNetLegacy_mass = FatJet_particleNetLegacy_mass[1];
     }


      for(unsigned int q = 0; q < nJet; q++ )
        if (Jet_pt[q] > 25 && Jet_btagDeepFlavB[q] > btagMediumCut && deltaPhi(fatJet2_phi, Jet_phi[q]) > 2.5)
           {fatJet2_OppositeHemisphereHasBJet = true;  break;}

      for(unsigned int q = 0; q < nMuon; q++ )
        if (Muon_pt[q] > 30 && Muon_looseId[q] && deltaR(fatJet2_eta , fatJet2_phi, Muon_eta[q], Muon_phi[q]) < 1.0) 
        {fatJet2_HasMuon = true; break;}

      for(unsigned int q = 0; q < nElectron; q++ )
        if (Electron_pt[q] > 30 && deltaR(fatJet2_eta , fatJet2_phi, Electron_eta[q], Electron_phi[q]) < 1.0)
        {fatJet2_HasElectron = true; break;}

      //find loose b-tagged jet inside jet
      for(unsigned int q = 0; q < nJet; q++ )
        if (Jet_btagDeepFlavB[q] > btagMediumCut && deltaR(fatJet2_eta , fatJet2_phi, Jet_eta[q], Jet_phi[q]) < 1.0)
        {fatJet2_HasBJetMedium = true; break;}


    if (nFatJet>2 && FatJet_pt[2] > 200 && FatJet_msoftdrop[2] >40){
      fatJet3_pt        = FatJet_pt[2];
      fatJet3_eta       = FatJet_eta[2];
      fatJet3_phi       = FatJet_phi[2];
      fatJet3_mass      = FatJet_mass[2];
      fatJet3_msoftdrop = FatJet_msoftdrop[2];
      fatJet3_btagDDBvLV2 = FatJet_btagDDBvLV2[2];
      fatJet3_btagDDCvBV2 = FatJet_btagDDCvBV2[2];
      fatJet3_btagDDCvLV2 = FatJet_btagDDCvLV2[2];
      fatJet3_btagDeepB = FatJet_btagDeepB[2];
      fatJet3_btagHbb   = FatJet_btagHbb[2];
      fatJet3_particleNetWithMass_H4qvsQCD = FatJet_particleNetWithMass_H4qvsQCD[2];
      fatJet3_particleNetWithMass_HbbvsQCD = FatJet_particleNetWithMass_HbbvsQCD[2];
      fatJet3_particleNetWithMass_HccvsQCD = FatJet_particleNetWithMass_HccvsQCD[2];
      fatJet3_particleNetWithMass_QCD = FatJet_particleNetWithMass_QCD[2];
      fatJet3_particleNetWithMass_TvsQCD = FatJet_particleNetWithMass_TvsQCD[2];
      fatJet3_particleNetWithMass_WvsQCD = FatJet_particleNetWithMass_WvsQCD[2];
      fatJet3_particleNetWithMass_ZvsQCD = FatJet_particleNetWithMass_ZvsQCD[2];
      fatJet3_particleNet_QCD = FatJet_particleNet_QCD[2];
      fatJet3_particleNet_QCD0HF = FatJet_particleNet_QCD0HF[2];
      fatJet3_particleNet_QCD1HF = FatJet_particleNet_QCD1HF[2];
      fatJet3_particleNet_QCD2HF = FatJet_particleNet_QCD2HF[2];
      fatJet3_particleNet_XbbVsQCD = FatJet_particleNet_XbbVsQCD[2];
      fatJet3_particleNet_XccVsQCD = FatJet_particleNet_XccVsQCD[2];
      fatJet3_particleNet_XggVsQCD = FatJet_particleNet_XggVsQCD[2];
      fatJet3_particleNet_XqqVsQCD = FatJet_particleNet_XqqVsQCD[2];
      fatJet3_particleNet_massCorr = FatJet_particleNet_massCorr[2];
      fatJet3_globalParT_QCD0HF     = FatJet_globalParT_QCD0HF[2]    ;
      fatJet3_globalParT_QCD1HF     = FatJet_globalParT_QCD1HF[2]    ;
      fatJet3_globalParT_QCD2HF     = FatJet_globalParT_QCD2HF[2]    ;
      fatJet3_globalParT_TopW       = FatJet_globalParT_TopW[2]     ;
      fatJet3_globalParT_TopbW      = FatJet_globalParT_TopbW[2]     ;
      fatJet3_globalParT_TopbWev    = FatJet_globalParT_TopbWev[2]   ;
      fatJet3_globalParT_TopbWmv    = FatJet_globalParT_TopbWmv[2]   ;
      fatJet3_globalParT_TopbWq     = FatJet_globalParT_TopbWq[2]    ;
      fatJet3_globalParT_TopbWqq    = FatJet_globalParT_TopbWqq[2]   ;
      fatJet3_globalParT_TopbWtauhv = FatJet_globalParT_TopbWtauhv[2];
      fatJet3_globalParT_Xbb        = FatJet_globalParT_Xbb[2]       ;
      fatJet3_globalParT_XbbVsQCD   = FatJet_globalParT_XbbVsQCD[2]  ;
      fatJet3_globalParT_Xcc        = FatJet_globalParT_Xcc[2]       ;
      fatJet3_globalParT_Xcs        = FatJet_globalParT_Xcs[2]       ;
      fatJet3_globalParT_Xgg        = FatJet_globalParT_Xgg[2]       ;
      fatJet3_globalParT_Xqq        = FatJet_globalParT_Xqq[2]       ;
      fatJet3_globalParT_Xtauhtaue  = FatJet_globalParT_Xtauhtaue[2] ;
      fatJet3_globalParT_Xtauhtauh  = FatJet_globalParT_Xtauhtauh[2] ;
      fatJet3_globalParT_Xtauhtaum  = FatJet_globalParT_Xtauhtaum[2] ;
      fatJet3_globalParT_massRes    = FatJet_globalParT_massRes[2]   ;
      fatJet3_globalParT_massVis    = FatJet_globalParT_massVis[2]   ;      
      fatJet3_n2b1 = FatJet_n2b1[2];
      fatJet3_n3b1 = FatJet_n3b1[2];
      fatJet3_rawFactor = FatJet_rawFactor[2];
      fatJet3_Tau3OverTau2 = FatJet_tau3[2] /  FatJet_tau2[2];
      fatJet3_subJetIdx1      = FatJet_subJetIdx1[2];
      fatJet3_subJetIdx1_pt   = SubJet_pt[fatJet3_subJetIdx1];
      fatJet3_subJetIdx1_eta  = SubJet_eta[fatJet3_subJetIdx1];
      fatJet3_subJetIdx1_phi  = SubJet_phi[fatJet3_subJetIdx1];
      fatJet3_subJetIdx1_mass = SubJet_mass[fatJet3_subJetIdx1];
      fatJet3_subJetIdx2      = FatJet_subJetIdx2[2];
      fatJet3_subJetIdx2_pt   = SubJet_pt[fatJet3_subJetIdx2];
      fatJet3_subJetIdx2_eta  = SubJet_eta[fatJet3_subJetIdx2];
      fatJet3_subJetIdx2_phi  = SubJet_phi[fatJet3_subJetIdx2];
      fatJet3_subJetIdx2_mass = SubJet_mass[fatJet3_subJetIdx2];
      fatJet3_jetId           = FatJet_jetId[2];
      fatJet3_electronIdx3SJ  = FatJet_electronIdx3SJ[2];
      fatJet3_muonIdx3SJ      = FatJet_muonIdx3SJ[2];
      fatJet3_nConstituents   = FatJet_nConstituents[2];
      fatJet3_hadronFlavour   = FatJet_hadronFlavour[2];
      fatJet3_GenMatchIndex   = FatJet_genJetAK8Idx[2];
      fatJet3_nBHadrons       = FatJet_nBHadrons[2];
      fatJet3_nCHadrons       = FatJet_nCHadrons[2];
      // legacy test
      fatJet3_particleNetLegacy_Xbb = FatJet_particleNetLegacy_Xbb[2];
      fatJet3_particleNetLegacy_Xcc = FatJet_particleNetLegacy_Xcc[2];
      fatJet3_particleNetLegacy_Xqq = FatJet_particleNetLegacy_Xqq[2];
      fatJet3_particleNetLegacy_QCD = FatJet_particleNetLegacy_QCD[2];
      fatJet3_particleNetLegacy_QCDb = FatJet_particleNetLegacy_QCDb[2];
      fatJet3_particleNetLegacy_QCDbb = FatJet_particleNetLegacy_QCDbb[2];
      fatJet3_particleNetLegacy_QCDothers = FatJet_particleNetLegacy_QCDothers[2];
      fatJet3_particleNetLegacy_mass = FatJet_particleNetLegacy_mass[2];
     }


      for(unsigned int q = 0; q < nJet; q++ )
        if (Jet_pt[q] > 25 && Jet_btagDeepFlavB[q] > btagMediumCut && deltaPhi(fatJet3_phi, Jet_phi[q]) > 2.5)
           {fatJet3_OppositeHemisphereHasBJet = true;  break;}

      for(unsigned int q = 0; q < nMuon; q++ )
        if (Muon_pt[q] > 30 && Muon_looseId[q] && deltaR(fatJet3_eta , fatJet3_phi, Muon_eta[q], Muon_phi[q]) < 1.0) 
        {fatJet3_HasMuon = true; break;}

      for(unsigned int q = 0; q < nElectron; q++ )
        if (Electron_pt[q] > 30 && deltaR(fatJet3_eta , fatJet3_phi, Electron_eta[q], Electron_phi[q]) < 1.0)
        {fatJet3_HasElectron = true; break;}

      //find loose b-tagged jet inside jet
      for(unsigned int q = 0; q < nJet; q++ )
        if (Jet_btagDeepFlavB[q] > btagMediumCut && deltaR(fatJet3_eta , fatJet3_phi, Jet_eta[q], Jet_phi[q]) < 1.0)
        {fatJet3_HasBJetMedium = true; break;}

      //------------------------------------------------------
      //----------Find Leptons
      //------------------------------------------------------
      for(unsigned int i = 0; i < nMuon; i++ ) {
        if (Muon_pt[i] < 30) continue;
        if (fabs(Muon_eta[i]) > 2.4) continue;
        if (Muon_miniPFRelIso_all[i] > 0.2) continue;
        if (!Muon_tightId) continue;

        if (lep1Id == 0) {
          lep1Pt = Muon_pt[i];
          lep1Eta = Muon_eta[i];
          lep1Phi = Muon_phi[i];
          lep1Id = Muon_charge[i] * (13);
        } else if (Muon_pt[i] > lep1Pt) {
          lep2Pt = lep1Pt;
          lep2Eta = lep1Eta;
          lep2Phi = lep1Phi;
          lep2Id = lep1Id;
          lep1Pt = Muon_pt[i];
          lep1Eta = Muon_eta[i];
          lep1Phi = Muon_phi[i];
          lep1Id = Muon_charge[i] * (13);
        } else if (lep2Id == 0 || Muon_pt[i] > lep2Pt) {
          lep2Pt = Muon_pt[i];
          lep2Eta = Muon_eta[i];
          lep2Phi = Muon_phi[i];
          lep2Id = Muon_charge[i] * (13);
        }
      } //loop over muons

      for(unsigned int i = 0; i < nElectron; i++ ) {
        if (Electron_pt[i] < 35) continue;
        if (fabs(Electron_eta[i]) > 2.5) continue;
        if (Electron_miniPFRelIso_all[i] > 0.2) continue;
        if (!Electron_cutBased[i]) continue;
        if (lep1Id == 0) {
          lep1Pt = Electron_pt[i];
          lep1Eta = Electron_eta[i];
          lep1Phi = Electron_phi[i];
          lep1Id = Electron_charge[i] * (11);
        } else if (Electron_pt[i] > lep1Pt) {
          lep2Pt = lep1Pt;
          lep2Eta = lep1Eta;
          lep2Phi = lep1Phi;
          lep2Id = lep1Id;
          lep1Pt = Electron_pt[i];
          lep1Eta = Electron_eta[i];
          lep1Phi = Electron_phi[i];
          lep1Id = Electron_charge[i] * (11);
        } else if (lep2Id == 0 || Electron_pt[i] > lep2Pt) {
          lep2Pt = Electron_pt[i];
          lep2Eta = Electron_eta[i];
          lep2Phi = Electron_phi[i];
          lep2Id = Electron_charge[i] * (11);
        }
      } //loop over electrons

      //------------------------------------------------------
      //----------Find Photons
      //------------------------------------------------------
      for(unsigned int i = 0; i < nPhoton; i++ ) {
        if (Photon_pt[i] < 30) continue;
        if (fabs(Photon_eta[i]) > 2.5) continue;
        if (fabs(Photon_eta[i]) < 1.5) {
          if (Photon_mvaID[i] > 0.42) continue;           // ?? WP to be checked
        } else {
          if (Photon_mvaID[i] > 0.14) continue;           // ?? WP to be checked
        }
        if (!Photon_electronVeto[i]) continue;
        pho1Pt = Photon_pt[i];
        pho1Eta = Photon_eta[i];
        pho1Phi = Photon_phi[i];
      }

      //*******************************
      //Count additional AK4 jets 
      //*******************************
      vector<int> vbfjets_index;
      vbfjets_index.clear();
      for(int i = 0; i < nJet; i++)
       {
        if (Jet_pt[i] > 30 && fabs(Jet_eta[i]) < 2.5 && deltaR(Jet_eta[i] , Jet_phi[i], fatJet1_eta, fatJet1_phi) > 0.8 && deltaR(Jet_eta[i] , Jet_phi[i], fatJet2_eta, fatJet2_phi) > 0.8 )
            NJets++;

        bool passBTag = false;
        if(Jet_pt[i] > 40 && fabs(Jet_eta[i]) < 2.5 && Jet_btagDeepFlavB[i] > btagMediumCut && Jet_jetId[i] >= 4) passBTag = true;

        if(passBTag) 
         {
          nBTaggedJets++;
          if (nBTaggedJets==1) {jet1Pt = Jet_pt[i]; jet1Eta = Jet_eta[i]; jet1Phi = Jet_phi[i]; jet1_rawFactor = Jet_rawFactor[i];}
          if (nBTaggedJets==2) {jet2Pt = Jet_pt[i]; jet2Eta = Jet_eta[i]; jet2Phi = Jet_phi[i]; jet2_rawFactor = Jet_rawFactor[i];}
          if (nBTaggedJets==3) {jet3Pt = Jet_pt[i]; jet3Eta = Jet_eta[i]; jet3Phi = Jet_phi[i]; jet3_rawFactor = Jet_rawFactor[i];}
          if (nBTaggedJets==4) {jet4Pt = Jet_pt[i]; jet4Eta = Jet_eta[i]; jet4Phi = Jet_phi[i]; jet4_rawFactor = Jet_rawFactor[i];}
         }

        if(Jet_pt[i] > 25 && fabs(Jet_eta[i]) < 4.7 && deltaR(Jet_eta[i],Jet_phi[i],fatJet1_eta,fatJet1_phi) > 1.2 && deltaR(Jet_eta[i],Jet_phi[i],fatJet2_eta,fatJet2_phi) > 1.2 && Jet_jetId[i] >= 2)
          {
           bool islepoverlap = false;
           for(unsigned int j = 0; j < nMuon; j++ )
              if(Muon_pt[j]>5 && fabs(Muon_eta[j])<2.4 && abs(Muon_dxy[j]) < 0.05 and abs(Muon_dz[j]) < 0.2 && deltaR(Jet_eta[i] , Jet_phi[i], Muon_eta[j], Muon_phi[j]) < 0.4)
                 {islepoverlap = true; break; }

           for(unsigned int j = 0; j < nElectron; j++ )
              if(Electron_pt[j]>7 && fabs(Electron_eta[j])<2.5 && abs(Electron_dxy[j]) < 0.05 and abs(Electron_dz[j]) < 0.2 && deltaR(Jet_eta[i] , Jet_phi[i], Electron_eta[j], Electron_phi[j]) < 0.4)
                 {islepoverlap = true; break; }

           if(!islepoverlap) vbfjets_index.push_back(i);
          }

         } //loop over AK4 jets

      //get the AK4 jets with the largest pt
      if(vbfjets_index.size()>1){
         vbfjet1_Pt = Jet_pt[vbfjets_index[0]];
         vbfjet1_Eta = Jet_eta[vbfjets_index[0]];
         vbfjet1_Phi = Jet_phi[vbfjets_index[0]];
         vbfjet1_Mass = Jet_mass[vbfjets_index[0]];
         vbfjet2_Pt = Jet_pt[vbfjets_index[1]];
         vbfjet2_Eta = Jet_eta[vbfjets_index[1]];
         vbfjet2_Phi = Jet_phi[vbfjets_index[1]];
         vbfjet2_Mass = Jet_mass[vbfjets_index[1]];
         isVBFtag = 0;
         TLorentzVector jet1,jet2;
         jet1.SetPtEtaPhiM(vbfjet1_Pt,vbfjet1_Eta,vbfjet1_Phi,vbfjet1_Mass);
         jet2.SetPtEtaPhiM(vbfjet2_Pt,vbfjet2_Eta,vbfjet2_Phi,vbfjet2_Mass);
         dijetmass = (jet1 + jet2).M();
         if(dijetmass > 500. && fabs(vbfjet1_Eta-vbfjet2_Eta) > 4.) isVBFtag = 1;
      }

      //****************************************************
      //Compute pileupWeight
      //****************************************************      
      if (pileupWeightHist) {
	pileupWeight = pileupWeightHist->GetBinContent( pileupWeightHist->GetXaxis()->FindFixBin(Pileup_nTrueInt));
	pileupWeightUp = pileupWeightUpHist->GetBinContent( pileupWeightUpHist->GetXaxis()->FindFixBin(Pileup_nTrueInt));
	pileupWeightDown = pileupWeightDownHist->GetBinContent( pileupWeightDownHist->GetXaxis()->FindFixBin(Pileup_nTrueInt));
      }
      
      //****************************************************
      //Fill Event - skim for events with two jets found
      //****************************************************

       totalWeight = weight;

      //****************************************************
      //Fill trigger objects
      //****************************************************
      for(int itg=0;itg<20;itg++) {Trigger_Object_pt[itg]=Trigger_Object_eta[itg]=Trigger_Object_phi[itg]=-99.0; Trigger_Object_bit[itg]=-99;}
      int N_FatJet_TrgObjs = 0;
      for(int iTrg=0; iTrg<nTrigObj;iTrg++)
         if(TrigObj_id[iTrg]==6 && TrigObj_pt[iTrg] >100)
           {
            Trigger_Object_pt[N_FatJet_TrgObjs]  = TrigObj_pt[iTrg];
            Trigger_Object_eta[N_FatJet_TrgObjs] = TrigObj_eta[iTrg];
            Trigger_Object_phi[N_FatJet_TrgObjs] = TrigObj_phi[iTrg];
            Trigger_Object_bit[N_FatJet_TrgObjs] = TrigObj_filterBits[iTrg];
            N_FatJet_TrgObjs++;
           }

        NTrigger_Objects=N_FatJet_TrgObjs;

	NEventsFilled++;
	outputTree->Fill();
	outputTree_TrgObj->Fill();

    }//end of event loop
 
    cout << "Filled Total of " << NEventsFilled << " Events\n";
    cout << "Writing output trees..." << endl;

    //outFile->Write();
    outputTree->Write();
    outputTree_TrgObj->Write();
    NEvents->Write();
    nPU_True->Write();    
    outFile->Close();

}



