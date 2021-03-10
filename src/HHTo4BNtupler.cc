#include "HHTo4BNtupler.h"
#include <stdlib.h> 
#include "JetTree.h"
#include "JetCorrectorParameters.h"
#include "JetCorrectionUncertainty.h"

//C++ includes

//ROOT includes
#include "TH1F.h"

using namespace std;

double HHTo4BNtupler::getTriggerEff3D( TH2F *triggerEffHist_Xbb0p0To0p9, 
				     TH2F *triggerEffHist_Xbb0p9To0p95, 
				     TH2F *triggerEffHist_Xbb0p95To0p98, 
				     TH2F *triggerEffHist_Xbb0p98To1p0, 
				     double pt, double mass, double PNetXbb ) {
  double result = 0.0;
  double tmpMass = 0;
  double tmpPt = 0;
  double tmpPNetXbb = 0;
  TH2F* trigEffHist = 0;
  if (PNetXbb < 0.9) {
    trigEffHist = triggerEffHist_Xbb0p0To0p9;
  } else if (PNetXbb < 0.95) {
    trigEffHist = triggerEffHist_Xbb0p9To0p95;    
  } else if (PNetXbb < 0.98) {
    trigEffHist = triggerEffHist_Xbb0p95To0p98;    
  } else {
    trigEffHist = triggerEffHist_Xbb0p98To1p0;    
  }
  
  if (trigEffHist) {
    // constrain to histogram bounds
    if( mass > trigEffHist->GetXaxis()->GetXmax() * 0.999 ) {
      tmpMass = trigEffHist->GetXaxis()->GetXmax() * 0.999;
    } else if ( mass < 0 ) {
      tmpMass = 0.001;
      //cout << "Warning: mass=" << mass << " is negative and unphysical\n";
    } else {
      tmpMass = mass;
    }
    
    if( pt > trigEffHist->GetYaxis()->GetXmax() * 0.999 ) {
      tmpPt = trigEffHist->GetYaxis()->GetXmax() * 0.999;
    } else if (pt < 0) {
      tmpPt = 0.001;
      cout << "Warning: pt=" << pt << " is negative and unphysical\n";
    } else {
      tmpPt = pt;
    }
    
    result = trigEffHist->GetBinContent(
					trigEffHist->GetXaxis()->FindFixBin( tmpMass ),
					trigEffHist->GetYaxis()->FindFixBin( tmpPt )
					);  
  } else {
    std::cout << "Error: expected a histogram, got a null pointer" << std::endl;
    return 0;
  }
}




double HHTo4BNtupler::getTriggerEff( TH2F *trigEffHist , double pt, double mass ) {
  double result = 0.0;
  double tmpMass = 0;
  double tmpPt = 0;

  if (trigEffHist) {
      // constrain to histogram bounds
      if( mass > trigEffHist->GetXaxis()->GetXmax() * 0.999 ) {
	tmpMass = trigEffHist->GetXaxis()->GetXmax() * 0.999;
      } else if ( mass < 0 ) {
	tmpMass = 0.001;
	//cout << "Warning: mass=" << mass << " is negative and unphysical\n";
      } else {
	tmpMass = mass;
      }

      if( pt > trigEffHist->GetYaxis()->GetXmax() * 0.999 ) {
	tmpPt = trigEffHist->GetYaxis()->GetXmax() * 0.999;
      } else if (pt < 0) {
	tmpPt = 0.001;
	cout << "Warning: pt=" << pt << " is negative and unphysical\n";
      } else {
	tmpPt = pt;
      }

      result = trigEffHist->GetBinContent(
				 trigEffHist->GetXaxis()->FindFixBin( tmpMass ),
				 trigEffHist->GetYaxis()->FindFixBin( tmpPt )
				 );  
         
  } else {
    std::cout << "Error: expected a histogram, got a null pointer" << std::endl;
    return 0;
  }
  
  //cout << "mass = " << mass << " , pt = " << pt << " : trigEff = " << result << "\n";

  return result; 
}


void HHTo4BNtupler::Analyze(bool isData, int Option, string outputfilename, string year, string pileupWeightName)
{
 
    cout << "Initializing..." << endl;

    //----------------------------------------
    //Load auxiliary information
    //----------------------------------------  
    TH2F *triggerEffHist = 0;    
    TH2F *triggerEffHist_Xbb0p0To0p9 = 0;    
    TH2F *triggerEffHist_Xbb0p9To0p95 = 0;    
    TH2F *triggerEffHist_Xbb0p95To0p98 = 0;    
    TH2F *triggerEffHist_Xbb0p98To1p0 = 0;    
    TH2F *triggerEffMCHist = 0;    
    TH2F *triggerEffMCHist_Xbb0p0To0p9 = 0;    
    TH2F *triggerEffMCHist_Xbb0p9To0p95 = 0;    
    TH2F *triggerEffMCHist_Xbb0p95To0p98 = 0;    
    TH2F *triggerEffMCHist_Xbb0p98To1p0 = 0;    

    TH1F *pileupWeightHist = 0;
    TH1F *pileupWeightUpHist = 0;
    TH1F *pileupWeightDownHist = 0;
    
    string CMSSWDir = std::getenv("CMSSW_BASE");
    if (!isData) {
      string triggerEffFilename = "";
      string triggerEffMCFilename = "";
      if (year == "2016") {
	triggerEffFilename = CMSSWDir + "/src/HHBoostedAnalyzer/data/JetHTTriggerEfficiency_2016.root";
	triggerEffMCFilename = CMSSWDir + "/src/HHBoostedAnalyzer/data/JetHTTriggerEfficiency_Summer16.root";
      } else if (year == "2017") {
	triggerEffFilename = CMSSWDir + "/src/HHBoostedAnalyzer/data/JetHTTriggerEfficiency_2017.root";
	triggerEffMCFilename = CMSSWDir + "/src/HHBoostedAnalyzer/data/JetHTTriggerEfficiency_Fall17.root";
      } else if (year == "2018") {
	triggerEffFilename = CMSSWDir + "/src/HHBoostedAnalyzer/data/JetHTTriggerEfficiency_2018.root";
	triggerEffMCFilename = CMSSWDir + "/src/HHBoostedAnalyzer/data/JetHTTriggerEfficiency_Fall18.root";
      } else {
	cout << "[HHTo4BNtupler] Warning: year " << year << " is not supported. \n";
      }
      TFile *triggerEffFile = new TFile(triggerEffFilename.c_str(),"READ");
      TFile *triggerEffMCFile = new TFile(triggerEffMCFilename.c_str(),"READ");

      if (!triggerEffFile) {
	cout << "Warning : triggerEffFile " << triggerEffFilename << " could not be opened.\n";
      } else {
	cout << "Opened triggerEffFile " << triggerEffFilename << "\n";
      }
      if (triggerEffFile) {
	triggerEffHist = (TH2F*)triggerEffFile->Get("efficiency_ptmass");  
	triggerEffHist_Xbb0p0To0p9 = (TH2F*)triggerEffFile->Get("efficiency_ptmass_Xbb0p0To0p9");  
	triggerEffHist_Xbb0p9To0p95 = (TH2F*)triggerEffFile->Get("efficiency_ptmass_Xbb0p9To0p95");  
	triggerEffHist_Xbb0p95To0p98 = (TH2F*)triggerEffFile->Get("efficiency_ptmass_Xbb0p95To0p98");  
	triggerEffHist_Xbb0p98To1p0 = (TH2F*)triggerEffFile->Get("efficiency_ptmass_Xbb0p98To1p0");    
      } else {
	cout << "Warning : could not open file " << triggerEffFilename << "\n";
      }
      if (triggerEffHist) cout << "Found triggerEffHist in file " << triggerEffFilename << "\n";
      if (triggerEffHist_Xbb0p0To0p9) cout << "Found triggerEffHist_Xbb0p0To0p9 in file " << triggerEffFilename << "\n";
      if (triggerEffHist_Xbb0p9To0p95) cout << "Found triggerEffHist_Xbb0p9To0p95 in file " << triggerEffFilename << "\n";
      if (triggerEffHist_Xbb0p95To0p98) cout << "Found triggerEffHist_Xbb0p95To0p98 in file " << triggerEffFilename << "\n";
      if (triggerEffHist_Xbb0p98To1p0) cout << "Found triggerEffHist_Xbb0p98To1p0 in file " << triggerEffFilename << "\n";

      if (!triggerEffMCFile) {
	cout << "Warning : triggerEffMCFile " << triggerEffMCFilename << " could not be opened.\n";
      } else {
	cout << "Opened triggerEffMCFile " << triggerEffMCFilename << "\n";
      }
      if (triggerEffMCFile) {
	triggerEffMCHist = (TH2F*)triggerEffMCFile->Get("efficiency_ptmass");    
	triggerEffMCHist_Xbb0p0To0p9 = (TH2F*)triggerEffMCFile->Get("efficiency_ptmass_Xbb0p0To0p9");  
	triggerEffMCHist_Xbb0p9To0p95 = (TH2F*)triggerEffMCFile->Get("efficiency_ptmass_Xbb0p9To0p95");  
	triggerEffMCHist_Xbb0p95To0p98 = (TH2F*)triggerEffMCFile->Get("efficiency_ptmass_Xbb0p95To0p98");  
	triggerEffMCHist_Xbb0p98To1p0 = (TH2F*)triggerEffMCFile->Get("efficiency_ptmass_Xbb0p98To1p0");    
      } else {
	cout << "Warning : could not open file " << triggerEffMCFilename << "\n";
      }
      if (triggerEffMCHist) cout << "Found triggerEffMCHist in file " << triggerEffMCFilename << "\n";
      if (triggerEffMCHist_Xbb0p0To0p9) cout << "Found triggerEffMCHist_Xbb0p0To0p9 in file " << triggerEffMCFilename << "\n";
      if (triggerEffMCHist_Xbb0p9To0p95) cout << "Found triggerEffMCHist_Xbb0p9To0p95 in file " << triggerEffMCFilename << "\n";
      if (triggerEffMCHist_Xbb0p95To0p98) cout << "Found triggerEffMCHist_Xbb0p95To0p98 in file " << triggerEffMCFilename << "\n";
      if (triggerEffMCHist_Xbb0p98To1p0) cout << "Found triggerEffMCHist_Xbb0p98To1p0 in file " << triggerEffMCFilename << "\n";
 
      string pileupWeightFilename = CMSSWDir + "/src/HHBoostedAnalyzer/data/PileupWeights/PileupWeights.root";
      TFile *pileupWeightFile = new TFile(pileupWeightFilename.c_str(),"READ");
      if (!pileupWeightFile) {
	cout << "Warning : pileupWeightFile " << pileupWeightFile << " could not be opened.\n";  
      } else {
	cout << "Opened pileupWeightFile " << pileupWeightFilename << "\n"; 
      }
      string pileupWeightHistname = "PUWeight_" + pileupWeightName + "_" + year;
      if (pileupWeightFile) {
	pileupWeightHist = (TH1F*)pileupWeightFile->Get(pileupWeightHistname.c_str());
	pileupWeightUpHist = (TH1F*)pileupWeightFile->Get((pileupWeightHistname+"_SysUp").c_str());
	pileupWeightDownHist = (TH1F*)pileupWeightFile->Get((pileupWeightHistname+"_SysDown").c_str());
      } 
      if (pileupWeightHist) {
	cout << "Found pileupWeightHist " << pileupWeightHistname << "in file " << pileupWeightFilename << "\n";
      } else {
	cout << "Warning :  could not find pileupWeightHist named " 
	     << pileupWeightHistname 
	     << " in file " << pileupWeightFilename << "\n";
      }
      if (pileupWeightUpHist) {
	cout << "Found pileupWeightUpHist " << pileupWeightHistname+"_SysUp" << "in file " << pileupWeightFilename << "\n";
      } else {
	cout << "Warning :  could not find pileupWeightUpHist named " 
	     << pileupWeightHistname +"_SysUp"
	     << " in file " << pileupWeightFilename << "\n";
      }
      if (pileupWeightDownHist) {
	cout << "Found pileupWeightDownHist " << pileupWeightHistname+"_SysDown" << "in file " << pileupWeightFilename << "\n";
      } else {
	cout << "Warning :  could not find pileupWeightDownHist named " 
	     << pileupWeightHistname +"_SysDown"
	     << " in file " << pileupWeightFilename << "\n";
      }
    
    }

    //----------------------------------------
    //Jet Mass Scale: https://github.com/cms-nanoAOD/nanoAOD-tools/blob/a4b3c03ca5d8f4b8fbebc145ddcd605c7553d767/python/postprocessing/modules/jme/jetmetHelperRun2.py#L45-L58
    //----------------------------------------
    float* jmsValues;//{nominal, down, up}
    if(year == "2016")
      {
	float tmp_jms[] = {1.00, 0.9906, 1.0094};
	jmsValues = tmp_jms;
      }
    else if(year == "2017")
      {
	//float tmp_jms[] = {0.982, 0.978, 0.986};
	float tmp_jms[] = {1.0016, 0.978, 0.986}; //Tuned to our Top control region
	jmsValues = tmp_jms;
      }
    else if(year == "2018")
      {
	float tmp_jms[] = {0.997, 0.993, 1.001};
	jmsValues = tmp_jms;
      }
    else
      {
	std::cout << "year is not acceptable! Use: 2016, 2017, 2018" << std::endl;
	exit(EXIT_FAILURE);
      }

    //----------------------------------------
    //Jet Mass Resolution: https://github.com/cms-nanoAOD/nanoAOD-tools/blob/a4b3c03ca5d8f4b8fbebc145ddcd605c7553d767/python/postprocessing/modules/jme/jetmetHelperRun2.py#L45-L58
    //----------------------------------------
    float* jmrValues;//{nominal, down, up}
    if(year == "2016")
      {
	//float tmp_jmr[] = {1.00, 1.0, 1.2};
	float tmp_jmr[] = {1.00, 1.0, 1.09}; //Tuned to our Top control region
	jmrValues = tmp_jmr;
      }
    else if(year == "2017")
      {
	//float tmp_jmr[] = {1.09, 1.04, 1.14};
	float tmp_jmr[] = {1.03, 1.00, 1.07};  //Tuned to our Top control region
        jmrValues = tmp_jmr;
      }
    else if(year == "2018")
      {
	//float tmp_jmr[] = {1.24, 1.20, 1.28};
	float tmp_jmr[] = {1.065, 1.031, 1.099}; //Tuned to our Top control region
        jmrValues = tmp_jmr;
      }
    else
      {
	std::cout << "year is not acceptable! Use: 2016, 2017, 2018" << std::endl;
	exit(EXIT_FAILURE);
      }


    //----------------------------------------
    //---jet energy scale uncertainty
    //----------------------------------------
    string JECUncertaintyFile = "";
    if (year == "2016") {
      JECUncertaintyFile = CMSSWDir + "/src/HHBoostedAnalyzer/data/JEC/Summer16_07Aug2017_V11_MC/Summer16_07Aug2017_V11_MC_Uncertainty_AK8PFPuppi.txt";
    } else if (year == "2017") {
      JECUncertaintyFile = CMSSWDir + "/src/HHBoostedAnalyzer/data/JEC/Fall17_17Nov2017_V32_MC/Fall17_17Nov2017_V32_MC_Uncertainty_AK8PFPuppi.txt";
    } else if (year == "2018") {
     JECUncertaintyFile = CMSSWDir + "/src/HHBoostedAnalyzer/data/JEC/Autumn18_V19_MC/Autumn18_V19_MC_Uncertainty_AK8PFPuppi.txt";
    }
    JetCorrectionUncertainty *jecUnc = new JetCorrectionUncertainty(JECUncertaintyFile.c_str());
    
    //----------------------------------------
    //Output file
    //----------------------------------------  
    string outfilename = outputfilename;
    if (outfilename == "") outfilename = "HHTo4BNtuple.root";
    TFile *outFile = new TFile(outfilename.c_str(), "RECREATE");    
 
    //histogram containing total number of processed events (for normalization)
    TH1F *NEvents = new TH1F("NEvents", "NEvents", 1, 1, 2);

    //output TTree
    TTree *outputTree = new TTree("tree", "");
 
    //------------------------
    //declare branch variables
    //------------------------  
    float weight = 0;
    float triggerEffWeight = 0;
    float triggerEff3DWeight = 0;
    float triggerEffMCWeight = 0;
    float triggerEffMC3DWeight = 0;
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

    int NJets = 0;
    float MET = -1;
    float fatJet1Pt = -99;
    float fatJet1Pt_JES_Up   = -99;
    float fatJet1Pt_JES_Down = -99;
    float fatJet1Eta = -99;
    float fatJet1Phi = -99;
    float fatJet1Mass = -99;
    float fatJet1MassSD      = -99;
    float fatJet1MassSD_UnCorrected  = -99;
    float fatJet1MassSD_JMS_Up       = -99;//jet mass scale up
    float fatJet1MassSD_JMS_Down     = -99;//jet mass scale down
    float fatJet1MassSD_JMR_Up       = -99;//jet mass resolution up
    float fatJet1MassSD_JMR_Down     = -99;//jet mass resolution down
    float fatJet1DDBTagger = -99;
    float fatJet1PNetXbb = -99;
    float fatJet1PNetQCDb = -99;
    float fatJet1PNetQCDbb = -99;
    float fatJet1PNetQCDc = -99;
    float fatJet1PNetQCDcc = -99;
    float fatJet1PNetQCDothers = -99;
    float fatJet1_deepTagMD_W =  -99;
    float fatJet1_deepTagMD_Z =  -99;
    float fatJet1_deepTag_W =  -99;
    float fatJet1_deepTag_Z =  -99;
    int   fatJet1GenMatchIndex = -99;
    float fatJet1Tau3OverTau2 = -99;
    float fatJet1_n2b1 = -99; 
    bool fatJet1HasMuon = 0;
    bool fatJet1HasElectron = 0;
    bool fatJet1HasBJetCSVLoose = 0;
    bool fatJet1HasBJetCSVMedium = 0;
    bool fatJet1HasBJetCSVTight = 0;
    bool fatJet1OppositeHemisphereHasBJet = 0;
    float fatJet2Pt = -99;
    float fatJet2Pt_JES_Up   = -99;
    float fatJet2Pt_JES_Down = -99;
    float fatJet2Eta = -99;
    float fatJet2Phi = -99;
    float fatJet2Mass = -99;
    float fatJet2MassSD = -99;
    float fatJet2MassSD_UnCorrected  = -99;
    float fatJet2MassSD_JMS_Up       = -99;//jet mass scale up
    float fatJet2MassSD_JMS_Down     = -99;//jet mass scale down
    float fatJet2MassSD_JMR_Up       = -99;//jet mass resolution up
    float fatJet2MassSD_JMR_Down     = -99;//jet mass resolution down
    float fatJet2DDBTagger = -99;
    float fatJet2PNetXbb = -99;
    float fatJet2PNetQCDb = -99;
    float fatJet2PNetQCDbb = -99;
    float fatJet2PNetQCDc = -99;
    float fatJet2PNetQCDcc = -99;
    float fatJet2PNetQCDothers = -99;
    float fatJet2_deepTagMD_W =  -99;
    float fatJet2_deepTagMD_Z =  -99;
    float fatJet2_deepTag_W =  -99;
    float fatJet2_deepTag_Z =  -99;
    int   fatJet2GenMatchIndex = -99;
    float fatJet2Tau3OverTau2 = -99;
    bool fatJet2HasMuon = 0;
    bool fatJet2HasElectron = 0;
    bool fatJet2HasBJetCSVLoose = 0;
    bool fatJet2HasBJetCSVMedium = 0;
    bool fatJet2HasBJetCSVTight = 0;
    float fatJet3Pt = -99;
    float fatJet3Pt_JES_Up   = -99;
    float fatJet3Pt_JES_Down = -99;
    float fatJet3Eta = -99;
    float fatJet3Phi = -99;
    float fatJet3Mass = -99;
    float fatJet3MassSD = -99;
    float fatJet3MassSD_UnCorrected  = -99;
    float fatJet3MassSD_JMS_Up       = -99;//jet mass scale up
    float fatJet3MassSD_JMS_Down     = -99;//jet mass scale down
    float fatJet3MassSD_JMR_Up       = -99;//jet mass resolution up
    float fatJet3MassSD_JMR_Down     = -99;//jet mass resolution down
    float fatJet3DDBTagger = -99;
    float fatJet3PNetXbb = -99;
    float fatJet3PNetQCDb = -99;
    float fatJet3PNetQCDbb = -99;
    float fatJet3PNetQCDc = -99;
    float fatJet3PNetQCDcc = -99;
    float fatJet3PNetQCDothers = -99;
    float fatJet3Tau3OverTau2 = -99;
    bool fatJet3HasMuon = 0;
    bool fatJet3HasElectron = 0;
    bool fatJet3HasBJetCSVLoose = 0;
    bool fatJet3HasBJetCSVMedium = 0;
    bool fatJet3HasBJetCSVTight = 0;
    float hh_pt = -99;
    float hh_eta = -99;
    float hh_phi = -99;
    float hh_mass = -99;        
    float hh_pt_JESUp = -99;
    float hh_pt_JESDown = -99;
    float hh_pt_JMSUp = -99;
    float hh_pt_JMSDown = -99;
    float hh_pt_JMRUp = -99;
    float hh_pt_JMRDown = -99;
    float hh_eta_JESUp = -99;
    float hh_eta_JESDown = -99;
    float hh_eta_JMSUp = -99;
    float hh_eta_JMSDown = -99;
    float hh_eta_JMRUp = -99;
    float hh_eta_JMRDown = -99;
    float hh_mass_JESUp = -99;
    float hh_mass_JESDown = -99;
    float hh_mass_JMSUp = -99;
    float hh_mass_JMSDown = -99;
    float hh_mass_JMRUp = -99;
    float hh_mass_JMRDown = -99;    
    float fatJet1PtOverMHH = -99;
    float fatJet1PtOverMHH_JESUp = -99;
    float fatJet1PtOverMHH_JESDown = -99;
    float fatJet1PtOverMHH_JMSUp = -99;
    float fatJet1PtOverMHH_JMSDown = -99;
    float fatJet1PtOverMHH_JMRUp = -99;
    float fatJet1PtOverMHH_JMRDown = -99;
    float fatJet1PtOverMSD = -99;
    float fatJet2PtOverMHH = -99;
    float fatJet2PtOverMHH_JESUp = -99;
    float fatJet2PtOverMHH_JESDown = -99;
    float fatJet2PtOverMHH_JMSUp = -99;
    float fatJet2PtOverMHH_JMSDown = -99;
    float fatJet2PtOverMHH_JMRUp = -99;
    float fatJet2PtOverMHH_JMRDown = -99;
    float fatJet2PtOverMSD = -99;
    float deltaEta_j1j2 = -99;
    float deltaPhi_j1j2 = -99;
    float deltaR_j1j2 = -99;    
    float ptj2_over_ptj1 = -99;
    float mj2_over_mj1 = -99;
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
    float jet1DeepJetBTag = -99;
    float jet2Pt = -99;
    float jet2Eta = -99;
    float jet2Phi = -99;
    float jet2DeepJetBTag = -99;
    float jet3Pt = -99;
    float jet3Eta = -99;
    float jet3Phi = -99;
    float jet3DeepJetBTag = -99;
    float jet4Pt = -99;
    float jet4Eta = -99;
    float jet4Phi = -99;
    float jet4DeepJetBTag = -99;
    int   nBTaggedJets = 0;
    //variables for overlap removal with VBF HH->4b boosted analysis
    int isVBFtag = 0;
    float dijetmass = -99;
    float vbfjet1Pt = -99;
    float vbfjet1Eta = -99;
    float vbfjet1Phi = -99;
    float vbfjet1Mass = -99;
    float vbfjet2Pt = -99;
    float vbfjet2Eta = -99;
    float vbfjet2Phi = -99;
    float vbfjet2Mass = -99;
    float vbffatJet1Pt = -99;
    float vbffatJet1Eta = -99;
    float vbffatJet1Phi = -99;
    float vbffatJet1PNetXbb = -99;
    float vbffatJet2Pt = -99;
    float vbffatJet2Eta = -99;
    float vbffatJet2Phi = -99;
    float vbffatJet2PNetXbb = -99;

    //------------------------
    //set branches on big tree
    //------------------------    
    outputTree->Branch("weight", &weight, "weight/F");
    outputTree->Branch("genMTT", &genMTT, "genMTT/F");

    if (Option != 100) {

      outputTree->Branch("triggerEffWeight", &triggerEffWeight, "triggerEffWeight/F");
      outputTree->Branch("triggerEff3DWeight", &triggerEff3DWeight, "triggerEff3DWeight/F");
      outputTree->Branch("triggerEffMCWeight", &triggerEffMCWeight, "triggerEffMCWeight/F");
      outputTree->Branch("triggerEffMC3DWeight", &triggerEffMC3DWeight, "triggerEffMC3DWeight/F");

      float triggerEff3DWeight = 0;
      float triggerEffMCWeight = 0;
      float triggerEffMC3DWeight = 0;
      
      outputTree->Branch("pileupWeight", &pileupWeight, "pileupWeight/F");
      outputTree->Branch("pileupWeightUp", &pileupWeightUp, "pileupWeightUp/F");
      outputTree->Branch("pileupWeightDown", &pileupWeightDown, "pileupWeightDown/F");
      outputTree->Branch("totalWeight", &totalWeight, "totalWeight/F");
      outputTree->Branch("run", &run, "run/i");
      outputTree->Branch("lumi", &luminosityBlock, "lumi/i");
      outputTree->Branch("event", &event, "event/l");
      outputTree->Branch("npu", &Pileup_nTrueInt, "npu/F");
      outputTree->Branch("rho", &fixedGridRhoFastjetAll, "rho/F");

      outputTree->Branch("NJets", &NJets, "NJets/I");
      outputTree->Branch("MET", &MET, "MET/F");
      outputTree->Branch("fatJet1Pt", &fatJet1Pt, "fatJet1Pt/F");
      outputTree->Branch("fatJet1Pt_JES_Up", &fatJet1Pt_JES_Up, "fatJet1Pt_JES_Up/F");
      outputTree->Branch("fatJet1Pt_JES_Down", &fatJet1Pt_JES_Down, "fatJet1Pt_JES_Down/F");
      outputTree->Branch("fatJet1Eta", &fatJet1Eta, "fatJet1Eta/F");
      outputTree->Branch("fatJet1Phi", &fatJet1Phi, "fatJet1Phi/F");
      outputTree->Branch("fatJet1Mass", &fatJet1Mass, "fatJet1Mass/F");
      outputTree->Branch("fatJet1MassSD", &fatJet1MassSD, "fatJet1MassSD/F");
      outputTree->Branch("fatJet1MassSD_UnCorrected", &fatJet1MassSD_UnCorrected, "fatJet1MassSD_UnCorrected/F");
      outputTree->Branch("fatJet1MassSD_JMS_Up", &fatJet1MassSD_JMS_Up, "fatJet1MassSD_JMS_Up/F");
      outputTree->Branch("fatJet1MassSD_JMS_Down", &fatJet1MassSD_JMS_Down, "fatJet1MassSD_JMS_Down/F");
      outputTree->Branch("fatJet1MassSD_JMR_Up", &fatJet1MassSD_JMR_Up, "fatJet1MassSD_JMR_Up/F");
      outputTree->Branch("fatJet1MassSD_JMR_Down", &fatJet1MassSD_JMR_Down, "fatJet1MassSD_JMR_Down/F");
      outputTree->Branch("fatJet1DDBTagger", &fatJet1DDBTagger, "fatJet1DDBTagger/F");
      outputTree->Branch("fatJet1PNetXbb", &fatJet1PNetXbb, "fatJet1PNetXbb/F");
      outputTree->Branch("fatJet1PNetQCDb", &fatJet1PNetQCDb, "fatJet1PNetQCDb/F");
      outputTree->Branch("fatJet1PNetQCDbb", &fatJet1PNetQCDbb, "fatJet1PNetQCDbb/F");
      outputTree->Branch("fatJet1PNetQCDc", &fatJet1PNetQCDc, "fatJet1PNetQCDc/F");
      outputTree->Branch("fatJet1PNetQCDcc", &fatJet1PNetQCDcc, "fatJet1PNetQCDcc/F");
      outputTree->Branch("fatJet1PNetQCDothers", &fatJet1PNetQCDothers, "fatJet1PNetQCDothers/F");
      outputTree->Branch("fatJet1_deepTagMD_W", &fatJet1_deepTagMD_W, "fatJet1_deepTagMD_W/F");
      outputTree->Branch("fatJet1_deepTagMD_Z", &fatJet1_deepTagMD_Z, "fatJet1_deepTagMD_Z/F");
      outputTree->Branch("fatJet1_deepTag_W", &fatJet1_deepTag_W, "fatJet1_deepTag_W/F");
      outputTree->Branch("fatJet1_deepTag_Z", &fatJet1_deepTag_Z, "fatJet1_deepTag_Z/F"); 
      outputTree->Branch("fatJet1GenMatchIndex", &fatJet1GenMatchIndex, "fatJet1GenMatchIndex/I");
      outputTree->Branch("fatJet1Tau3OverTau2", &fatJet1Tau3OverTau2, "fatJet1Tau3OverTau2/F");
      outputTree->Branch("fatJet1_n2b1", &fatJet1_n2b1, "fatJet1_n2b1/F");
      outputTree->Branch("fatJet1HasMuon", &fatJet1HasMuon, "fatJet1HasMuon/O");
      outputTree->Branch("fatJet1HasElectron", &fatJet1HasElectron, "fatJet1HasElectron/O");
      outputTree->Branch("fatJet1HasBJetCSVLoose", &fatJet1HasBJetCSVLoose, "fatJet1HasBJetCSVLoose/O");
      outputTree->Branch("fatJet1HasBJetCSVMedium", &fatJet1HasBJetCSVMedium, "fatJet1HasBJetCSVMedium/O");
      outputTree->Branch("fatJet1HasBJetCSVTight", &fatJet1HasBJetCSVTight, "fatJet1HasBJetCSVTight/O");
      outputTree->Branch("fatJet1OppositeHemisphereHasBJet", &fatJet1OppositeHemisphereHasBJet, "fatJet1OppositeHemisphereHasBJet/O");
        
      //for phase-space overlap removal with VBFHH->4b boosted analysis
      //small R VBF jets
      outputTree->Branch("isVBFtag", &isVBFtag, "isVBFtag/I");
      outputTree->Branch("dijetmass", &dijetmass, "dijetmass/F");
      outputTree->Branch("vbfjet1Pt", &vbfjet1Pt, "vbfjet1Pt/F");
      outputTree->Branch("vbfjet1Eta", &vbfjet1Eta, "vbfjet1Eta/F");
      outputTree->Branch("vbfjet1Phi", &vbfjet1Phi, "vbfjet1Phi/F");
      outputTree->Branch("vbfjet1Mass", &vbfjet1Mass, "vbfjet1Mass/F");
      outputTree->Branch("vbfjet2Pt", &vbfjet2Pt, "vbfjet2Pt/F");
      outputTree->Branch("vbfjet2Eta", &vbfjet2Eta, "vbfjet2Eta/F");
      outputTree->Branch("vbfjet2Phi", &vbfjet2Phi, "vbfjet2Phi/F");
      outputTree->Branch("vbfjet2Mass", &vbfjet2Mass, "vbfjet2Mass/F");
      //leading and subleading AK8jets
      outputTree->Branch("vbffatJet1PNetXbb", &vbffatJet1PNetXbb, "vbffatJet1PNetXbb/F");
      outputTree->Branch("vbffatJet1Pt", &vbffatJet1Pt, "vbffatJet1Pt/F");
      outputTree->Branch("vbffatJet1Eta", &vbffatJet1Eta, "vbffatJet1Eta/F");
      outputTree->Branch("vbffatJet1Phi", &vbffatJet1Phi, "vbffatJet1Phi/F");
      outputTree->Branch("vbffatJet2PNetXbb", &vbffatJet2PNetXbb, "vbffatJet2PNetXbb/F");
      outputTree->Branch("vbffatJet2Pt", &vbffatJet2Pt, "vbffatJet2Pt/F");
      outputTree->Branch("vbffatJet2Eta", &vbffatJet2Eta, "vbffatJet2Eta/F");
      outputTree->Branch("vbffatJet2Phi", &vbffatJet2Phi, "vbffatJet2Phi/F");
    }

    if (Option == 0) {
      outputTree->Branch("genPhotonPt", &genPhotonPt, "genPhotonPt/F");
      outputTree->Branch("genPhotonEta", &genPhotonEta, "genPhotonEta/F");
      outputTree->Branch("genPhotonPhi", &genPhotonPhi, "genPhotonPhi/F");

      outputTree->Branch("jet1Pt", &jet1Pt, "jet1Pt/F");
      outputTree->Branch("jet1Eta", &jet1Eta, "jet1Eta/F");
      outputTree->Branch("jet1Phi", &jet1Phi, "jet1Phi/F");
      outputTree->Branch("jet1DeepJetBTag", &jet1DeepJetBTag, "jet1DeepJetBTag/F");      
      outputTree->Branch("jet2Pt", &jet2Pt, "jet2Pt/F");
      outputTree->Branch("jet2Eta", &jet2Eta, "jet2Eta/F");
      outputTree->Branch("jet2Phi", &jet2Phi, "jet2Phi/F");
      outputTree->Branch("jet2DeepJetBTag", &jet2DeepJetBTag, "jet2DeepJetBTag/F");      
      outputTree->Branch("jet3Pt", &jet3Pt, "jet3Pt/F");
      outputTree->Branch("jet3Eta", &jet3Eta, "jet3Eta/F");
      outputTree->Branch("jet3Phi", &jet3Phi, "jet3Phi/F");
      outputTree->Branch("jet3DeepJetBTag", &jet3DeepJetBTag, "jet3DeepJetBTag/F");      
      outputTree->Branch("jet4Pt", &jet4Pt, "jet4Pt/F");
      outputTree->Branch("jet4Eta", &jet4Eta, "jet4Eta/F");
      outputTree->Branch("jet4Phi", &jet4Phi, "jet4Phi/F");
      outputTree->Branch("jet4DeepJetBTag", &jet4DeepJetBTag, "jet4DeepJetBTag/F");      
   }


    if (Option != 20 && Option != 100) {
      outputTree->Branch("genHiggs1Pt", &genHiggs1Pt, "genHiggs1Pt/F");
      outputTree->Branch("genHiggs1Eta", &genHiggs1Eta, "genHiggs1Eta/F");
      outputTree->Branch("genHiggs1Phi", &genHiggs1Phi, "genHiggs1Phi/F");
      outputTree->Branch("genHiggs2Pt", &genHiggs2Pt, "genHiggs2Pt/F");
      outputTree->Branch("genHiggs2Eta", &genHiggs2Eta, "genHiggs2Eta/F");
      outputTree->Branch("genHiggs2Phi", &genHiggs2Phi, "genHiggs2Phi/F");
      outputTree->Branch("genHH_pt",      &genHH_pt,     "genHH_pt/F");
      outputTree->Branch("genHH_eta",     &genHH_eta,    "genHH_eta/F");
      outputTree->Branch("genHH_phi",     &genHH_phi,    "genHH_phi/F");
      outputTree->Branch("genHH_mass",    &genHH_mass,   "genHH_mass/F");
      outputTree->Branch("genLeptonId", &genLeptonId, "genLeptonId/I");
      outputTree->Branch("genLeptonMotherId", &genLeptonMotherId, "genLeptonMotherId/I");
      outputTree->Branch("genLeptonPt", &genLeptonPt, "genLeptonPt/F");
      outputTree->Branch("genLeptonEta", &genLeptonEta, "genLeptonEta/F");
      outputTree->Branch("genLeptonPhi", &genLeptonPhi, "genLeptonPhi/F");

      outputTree->Branch("fatJet2Pt", &fatJet2Pt, "fatJet2Pt/F");
      outputTree->Branch("fatJet2Pt_JES_Up", &fatJet2Pt_JES_Up, "fatJet2Pt_JES_Up/F");
      outputTree->Branch("fatJet2Pt_JES_Down", &fatJet2Pt_JES_Down, "fatJet2Pt_JES_Down/F");
      outputTree->Branch("fatJet2Eta", &fatJet2Eta, "fatJet2Eta/F");
      outputTree->Branch("fatJet2Phi", &fatJet2Phi, "fatJet2Phi/F");
      outputTree->Branch("fatJet2Mass", &fatJet2Mass, "fatJet2Mass/F");
      outputTree->Branch("fatJet2MassSD", &fatJet2MassSD, "fatJet2MassSD/F");
      outputTree->Branch("fatJet2MassSD_UnCorrected", &fatJet2MassSD_UnCorrected, "fatJet2MassSD_UnCorrected/F");
      outputTree->Branch("fatJet2MassSD_JMS_Up", &fatJet2MassSD_JMS_Up, "fatJet2MassSD_JMS_Up/F");
      outputTree->Branch("fatJet2MassSD_JMS_Down", &fatJet2MassSD_JMS_Down, "fatJet2MassSD_JMS_Down/F");
      outputTree->Branch("fatJet2MassSD_JMR_Up", &fatJet2MassSD_JMR_Up, "fatJet2MassSD_JMR_Up/F");
      outputTree->Branch("fatJet2MassSD_JMR_Down", &fatJet2MassSD_JMR_Down, "fatJet2MassSD_JMR_Down/F");
      outputTree->Branch("fatJet2DDBTagger", &fatJet2DDBTagger, "fatJet2DDBTagger/F");
      outputTree->Branch("fatJet2PNetXbb", &fatJet2PNetXbb, "fatJet2PNetXbb/F");
      outputTree->Branch("fatJet2PNetQCDb", &fatJet2PNetQCDb, "fatJet2PNetQCDb/F");
      outputTree->Branch("fatJet2PNetQCDbb", &fatJet2PNetQCDbb, "fatJet2PNetQCDbb/F");
      outputTree->Branch("fatJet2PNetQCDc", &fatJet2PNetQCDc, "fatJet2PNetQCDc/F");
      outputTree->Branch("fatJet2PNetQCDcc", &fatJet2PNetQCDcc, "fatJet2PNetQCDcc/F");
      outputTree->Branch("fatJet2PNetQCDothers", &fatJet2PNetQCDothers, "fatJet2PNetQCDothers/F");
      outputTree->Branch("fatJet2_deepTagMD_W", &fatJet2_deepTagMD_W, "fatJet2_deepTagMD_W/F");
      outputTree->Branch("fatJet2_deepTagMD_Z", &fatJet2_deepTagMD_Z, "fatJet2_deepTagMD_Z/F");
      outputTree->Branch("fatJet2_deepTag_W", &fatJet2_deepTag_W, "fatJet2_deepTag_W/F");
      outputTree->Branch("fatJet2_deepTag_Z", &fatJet2_deepTag_Z, "fatJet2_deepTag_Z/F"); 
      outputTree->Branch("fatJet2GenMatchIndex", &fatJet2GenMatchIndex, "fatJet2GenMatchIndex/I");
      outputTree->Branch("fatJet2Tau3OverTau2", &fatJet2Tau3OverTau2, "fatJet2Tau3OverTau2/F");
      outputTree->Branch("fatJet2HasMuon", &fatJet2HasMuon, "fatJet2HasMuon/O");
      outputTree->Branch("fatJet2HasElectron", &fatJet2HasElectron, "fatJet2HasElectron/O");
      outputTree->Branch("fatJet2HasBJetCSVLoose", &fatJet2HasBJetCSVLoose, "fatJet2HasBJetCSVLoose/O");
      outputTree->Branch("fatJet2HasBJetCSVMedium", &fatJet2HasBJetCSVMedium, "fatJet2HasBJetCSVMedium/O");
      outputTree->Branch("fatJet2HasBJetCSVTight", &fatJet2HasBJetCSVTight, "fatJet2HasBJetCSVTight/O");
      outputTree->Branch("fatJet3Pt", &fatJet3Pt, "fatJet3Pt/F");
      // outputTree->Branch("fatJet3Pt_JES_Up", &fatJet3Pt_JES_Up, "fatJet3Pt_JES_Up/F");
      // outputTree->Branch("fatJet3Pt_JES_Down", &fatJet3Pt_JES_Down, "fatJet3Pt_JES_Down/F");
      outputTree->Branch("fatJet3Eta", &fatJet3Eta, "fatJet3Eta/F");
      outputTree->Branch("fatJet3Phi", &fatJet3Phi, "fatJet3Phi/F");
      outputTree->Branch("fatJet3Mass", &fatJet3Mass, "fatJet3Mass/F");
      outputTree->Branch("fatJet3MassSD", &fatJet3MassSD, "fatJet3MassSD/F");
      // outputTree->Branch("fatJet3MassSD_UnCorrected", &fatJet3MassSD_UnCorrected, "fatJet3MassSD_UnCorrected/F");
      // outputTree->Branch("fatJet3MassSD_JMS_Up", &fatJet3MassSD_JMS_Up, "fatJet3MassSD_JMS_Up/F");
      // outputTree->Branch("fatJet3MassSD_JMS_Down", &fatJet3MassSD_JMS_Down, "fatJet3MassSD_JMS_Down/F");
      // outputTree->Branch("fatJet3MassSD_JMR_Up", &fatJet3MassSD_JMR_Up, "fatJet3MassSD_JMR_Up/F");
      // outputTree->Branch("fatJet3MassSD_JMR_Down", &fatJet3MassSD_JMR_Down, "fatJet3MassSD_JMR_Down/F");
      outputTree->Branch("fatJet3DDBTagger", &fatJet3DDBTagger, "fatJet3DDBTagger/F");
      outputTree->Branch("fatJet3PNetXbb", &fatJet3PNetXbb, "fatJet3PNetXbb/F");
      outputTree->Branch("fatJet3PNetQCDb", &fatJet3PNetQCDb, "fatJet3PNetQCDb/F");
      outputTree->Branch("fatJet3PNetQCDbb", &fatJet3PNetQCDbb, "fatJet3PNetQCDbb/F");
      outputTree->Branch("fatJet3PNetQCDc", &fatJet3PNetQCDc, "fatJet3PNetQCDc/F");
      outputTree->Branch("fatJet3PNetQCDcc", &fatJet3PNetQCDcc, "fatJet3PNetQCDcc/F");
      outputTree->Branch("fatJet3PNetQCDothers", &fatJet3PNetQCDothers, "fatJet3PNetQCDothers/F");
      outputTree->Branch("fatJet3Tau3OverTau2", &fatJet3Tau3OverTau2, "fatJet3Tau3OverTau2/F");
      outputTree->Branch("fatJet3HasMuon", &fatJet3HasMuon, "fatJet3HasMuon/O");
      outputTree->Branch("fatJet3HasElectron", &fatJet3HasElectron, "fatJet3HasElectron/O");
      outputTree->Branch("fatJet3HasBJetCSVLoose", &fatJet3HasBJetCSVLoose, "fatJet3HasBJetCSVLoose/O");
      outputTree->Branch("fatJet3HasBJetCSVMedium", &fatJet3HasBJetCSVMedium, "fatJet3HasBJetCSVMedium/O");
      outputTree->Branch("fatJet3HasBJetCSVTight", &fatJet3HasBJetCSVTight, "fatJet3HasBJetCSVTight/O");
      outputTree->Branch("hh_pt",      &hh_pt,     "hh_pt/F");
      outputTree->Branch("hh_eta",     &hh_eta,    "hh_eta/F");
      outputTree->Branch("hh_phi",     &hh_phi,    "hh_phi/F");
      outputTree->Branch("hh_mass",    &hh_mass,   "hh_mass/F");
      outputTree->Branch("hh_pt_JESUp",      &hh_pt_JESUp,     "hh_pt_JESUp/F");
      outputTree->Branch("hh_pt_JESDown",    &hh_pt_JESDown,   "hh_pt_JESDown/F");
      outputTree->Branch("hh_pt_JMSUp",      &hh_pt_JMSUp,     "hh_pt_JMSUp/F");
      outputTree->Branch("hh_pt_JMSDown",    &hh_pt_JMSDown,   "hh_pt_JMSDown/F");
      outputTree->Branch("hh_pt_JMRUp",      &hh_pt_JMRUp,     "hh_pt_JMRUp/F");
      outputTree->Branch("hh_pt_JMRDown",    &hh_pt_JMRDown,   "hh_pt_JMRDown/F");
      outputTree->Branch("hh_eta_JESUp",      &hh_eta_JESUp,     "hh_eta_JESUp/F");
      outputTree->Branch("hh_eta_JESDown",    &hh_eta_JESDown,   "hh_eta_JESDown/F");
      outputTree->Branch("hh_eta_JMSUp",      &hh_eta_JMSUp,     "hh_eta_JMSUp/F");
      outputTree->Branch("hh_eta_JMSDown",    &hh_eta_JMSDown,   "hh_eta_JMSDown/F");
      outputTree->Branch("hh_eta_JMRUp",      &hh_eta_JMRUp,     "hh_eta_JMRUp/F");
      outputTree->Branch("hh_eta_JMRDown",    &hh_eta_JMRDown,   "hh_eta_JMRDown/F");
      outputTree->Branch("hh_mass_JESUp",      &hh_mass_JESUp,     "hh_mass_JESUp/F");
      outputTree->Branch("hh_mass_JESDown",    &hh_mass_JESDown,   "hh_mass_JESDown/F");
      outputTree->Branch("hh_mass_JMSUp",      &hh_mass_JMSUp,     "hh_mass_JMSUp/F");
      outputTree->Branch("hh_mass_JMSDown",    &hh_mass_JMSDown,   "hh_mass_JMSDown/F");
      outputTree->Branch("hh_mass_JMRUp",      &hh_mass_JMRUp,     "hh_mass_JMRUp/F");
      outputTree->Branch("hh_mass_JMRDown",    &hh_mass_JMRDown,   "hh_mass_JMRDown/F");
      outputTree->Branch("fatJet1PtOverMHH",    &fatJet1PtOverMHH,   "fatJet1PtOverMHH/F");
      outputTree->Branch("fatJet1PtOverMHH_JESUp",    &fatJet1PtOverMHH_JESUp,   "fatJet1PtOverMHH_JESUp/F");
      outputTree->Branch("fatJet1PtOverMHH_JESDown",  &fatJet1PtOverMHH_JESDown, "fatJet1PtOverMHH_JESDown/F");
      outputTree->Branch("fatJet1PtOverMHH_JMSUp",    &fatJet1PtOverMHH_JMSUp,   "fatJet1PtOverMHH_JMSUp/F");
      outputTree->Branch("fatJet1PtOverMHH_JMSDown",  &fatJet1PtOverMHH_JMSDown, "fatJet1PtOverMHH_JMSDown/F");
      outputTree->Branch("fatJet1PtOverMHH_JMRUp",    &fatJet1PtOverMHH_JMRUp,   "fatJet1PtOverMHH_JMRUp/F");
      outputTree->Branch("fatJet1PtOverMHH_JMRDown",  &fatJet1PtOverMHH_JMRDown, "fatJet1PtOverMHH_JMRDown/F");
      outputTree->Branch("fatJet1PtOverMSD",    &fatJet1PtOverMSD,   "fatJet1PtOverMSD/F");
      outputTree->Branch("fatJet2PtOverMHH",    &fatJet2PtOverMHH,   "fatJet2PtOverMHH/F");
      outputTree->Branch("fatJet2PtOverMHH_JESUp",    &fatJet2PtOverMHH_JESUp,   "fatJet2PtOverMHH_JESUp/F");
      outputTree->Branch("fatJet2PtOverMHH_JESDown",  &fatJet2PtOverMHH_JESDown, "fatJet2PtOverMHH_JESDown/F");
      outputTree->Branch("fatJet2PtOverMHH_JMSUp",    &fatJet2PtOverMHH_JMSUp,   "fatJet2PtOverMHH_JMSUp/F");
      outputTree->Branch("fatJet2PtOverMHH_JMSDown",  &fatJet2PtOverMHH_JMSDown, "fatJet2PtOverMHH_JMSDown/F");
      outputTree->Branch("fatJet2PtOverMHH_JMRUp",    &fatJet2PtOverMHH_JMRUp,   "fatJet2PtOverMHH_JMRUp/F");
      outputTree->Branch("fatJet2PtOverMHH_JMRDown",  &fatJet2PtOverMHH_JMRDown, "fatJet2PtOverMHH_JMRDown/F");
      outputTree->Branch("fatJet2PtOverMSD",    &fatJet2PtOverMSD,   "fatJet2PtOverMSD/F");
      outputTree->Branch("deltaEta_j1j2",    &deltaEta_j1j2,   "deltaEta_j1j2/F");
      outputTree->Branch("deltaPhi_j1j2",    &deltaPhi_j1j2,   "deltaPhi_j1j2/F");
      outputTree->Branch("deltaR_j1j2",    &deltaR_j1j2,   "deltaR_j1j2/F");
      outputTree->Branch("ptj2_over_ptj1",    &ptj2_over_ptj1,   "ptj2_over_ptj1/F");
      outputTree->Branch("mj2_over_mj1",    &mj2_over_mj1,   "mj2_over_mj1/F");
      outputTree->Branch("lep1Pt", &lep1Pt, "lep1Pt/F");
      outputTree->Branch("lep1Eta", &lep1Eta, "lep1Eta/F");
      outputTree->Branch("lep1Phi", &lep1Phi, "lep1Phi/F");
      outputTree->Branch("lep1Id", &lep1Id, "lep1Id/I");
      outputTree->Branch("lep2Pt", &lep2Pt, "lep2Pt/F");
      outputTree->Branch("lep2Eta", &lep2Eta, "lep2Eta/F");
      outputTree->Branch("lep2Phi", &lep2Phi, "lep2Phi/F");
      outputTree->Branch("lep2Id", &lep2Id, "lep2Id/I");
      outputTree->Branch("nBTaggedJets", &nBTaggedJets, "nBTaggedJets/I");      
    } 

    if (Option == 0 || Option == 20 || Option == 21) {
      outputTree->Branch("genWPt", &genWPt, "genWPt/F");
      outputTree->Branch("genWEta", &genWEta, "genWEta/F");
      outputTree->Branch("genWPhi", &genWPhi, "genWPhi/F");
      outputTree->Branch("genZPt", &genZPt, "genZPt/F");
      outputTree->Branch("genZEta", &genZEta, "genZEta/F");
      outputTree->Branch("genZPhi", &genZPhi, "genZPhi/F");
   }

    if (Option == 0 || Option == 20 || Option == 21) {            
      outputTree->Branch("pho1Pt", &pho1Pt, "pho1Pt/F");
      outputTree->Branch("pho1Eta", &pho1Eta, "pho1Eta/F");
      outputTree->Branch("pho1Phi", &pho1Phi, "pho1Phi/F");  
    }

    if (Option != 100) {

      outputTree->Branch("HLT_Ele27_WPTight_Gsf", &HLT_Ele27_WPTight_Gsf, "HLT_Ele27_WPTight_Gsf/O");
      outputTree->Branch("HLT_Ele28_WPTight_Gsf", &HLT_Ele28_WPTight_Gsf, "HLT_Ele28_WPTight_Gsf/O");
      outputTree->Branch("HLT_Ele30_WPTight_Gsf", &HLT_Ele30_WPTight_Gsf, "HLT_Ele30_WPTight_Gsf/O");
      outputTree->Branch("HLT_Ele32_WPTight_Gsf", &HLT_Ele32_WPTight_Gsf, "HLT_Ele32_WPTight_Gsf/O");
      outputTree->Branch("HLT_Ele35_WPTight_Gsf", &HLT_Ele35_WPTight_Gsf, "HLT_Ele35_WPTight_Gsf/O");
      outputTree->Branch("HLT_Ele38_WPTight_Gsf", &HLT_Ele38_WPTight_Gsf, "HLT_Ele38_WPTight_Gsf/O");
      outputTree->Branch("HLT_Ele40_WPTight_Gsf", &HLT_Ele40_WPTight_Gsf, "HLT_Ele40_WPTight_Gsf/O");
      outputTree->Branch("HLT_IsoMu20", &HLT_IsoMu20, "HLT_IsoMu20/O");
      outputTree->Branch("HLT_IsoMu24", &HLT_IsoMu24, "HLT_IsoMu24/O");
      outputTree->Branch("HLT_IsoMu24_eta2p1", &HLT_IsoMu24_eta2p1, "HLT_IsoMu24_eta2p1/O");
      outputTree->Branch("HLT_IsoMu27", &HLT_IsoMu27, "HLT_IsoMu27/O");
      outputTree->Branch("HLT_IsoMu30", &HLT_IsoMu30, "HLT_IsoMu30/O");
      outputTree->Branch("HLT_Mu50", &HLT_Mu50, "HLT_Mu50/O");
      outputTree->Branch("HLT_Mu55", &HLT_Mu55, "HLT_Mu55/O");
      outputTree->Branch("HLT_Photon175",                                      &HLT_Photon175,                         "HLT_Photon175/O");
      outputTree->Branch("HLT_PFHT780",                                        &HLT_PFHT780,                                       "HLT_PFHT780/O");
      outputTree->Branch("HLT_PFHT890",                                        &HLT_PFHT890,                                       "HLT_PFHT890/O");
      outputTree->Branch("HLT_PFHT1050",                                        &HLT_PFHT1050,                                       "HLT_PFHT1050/O");
      outputTree->Branch("HLT_AK8PFJet360_TrimMass30",                          &HLT_AK8PFJet360_TrimMass30,                         "HLT_AK8PFJet360_TrimMass30/O");
      outputTree->Branch("HLT_AK8PFJet380_TrimMass30",                          &HLT_AK8PFJet380_TrimMass30,                         "HLT_AK8PFJet380_TrimMass30/O");
      outputTree->Branch("HLT_AK8PFJet400_TrimMass30",                          &HLT_AK8PFJet400_TrimMass30,                         "HLT_AK8PFJet400_TrimMass30/O");
      outputTree->Branch("HLT_AK8PFJet420_TrimMass30",                          &HLT_AK8PFJet420_TrimMass30,                         "HLT_AK8PFJet420_TrimMass30/O");
      outputTree->Branch("HLT_AK8PFHT750_TrimMass50",                           &HLT_AK8PFHT750_TrimMass50,                          "HLT_AK8PFHT750_TrimMass50/O");
      outputTree->Branch("HLT_AK8PFHT800_TrimMass50",                           &HLT_AK8PFHT800_TrimMass50,                          "HLT_AK8PFHT800_TrimMass50/O");
      outputTree->Branch("HLT_AK8PFHT850_TrimMass50",                           &HLT_AK8PFHT850_TrimMass50,                          "HLT_AK8PFHT850_TrimMass50/O");
      outputTree->Branch("HLT_AK8PFHT900_TrimMass50",                           &HLT_AK8PFHT900_TrimMass50,                          "HLT_AK8PFHT900_TrimMass50/O");
      //outputTree->Branch("HLT_AK8PFHT700_TrimR0p1PT0p03Mass50",                 &HLT_AK8PFHT700_TrimR0p1PT0p03Mass50,                "HLT_AK8PFHT700_TrimR0p1PT0p03Mass50/O");
      // outputTree->Branch("HLT_PFHT650_WideJetMJJ950DEtaJJ1p5",                  &HLT_PFHT650_WideJetMJJ950DEtaJJ1p5,                 "HLT_PFHT650_WideJetMJJ950DEtaJJ1p5/O");
      // outputTree->Branch("HLT_PFHT650_WideJetMJJ900DEtaJJ1p5",                  &HLT_PFHT650_WideJetMJJ900DEtaJJ1p5,                  "HLT_PFHT650_WideJetMJJ900DEtaJJ1p5/O");
      outputTree->Branch("HLT_PFJet450",                                        &HLT_PFJet450,                                       "HLT_PFJet450/O");
      outputTree->Branch("HLT_PFJet500",                                        &HLT_PFJet500,                                       "HLT_PFJet500/O");
      outputTree->Branch("HLT_PFJet550",                                        &HLT_PFJet550,                                       "HLT_PFJet550/O");
      outputTree->Branch("HLT_AK8PFJet400",                                     &HLT_AK8PFJet400,                                    "HLT_AK8PFJet400/O");
      outputTree->Branch("HLT_AK8PFJet450",                                     &HLT_AK8PFJet450,                                    "HLT_AK8PFJet450/O");
      outputTree->Branch("HLT_AK8PFJet500",                                     &HLT_AK8PFJet500,                                    "HLT_AK8PFJet500/O");
      outputTree->Branch("HLT_AK8PFJet550",                                     &HLT_AK8PFJet550,                                    "HLT_AK8PFJet550/O");
      outputTree->Branch("HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17",     &HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17,    "HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17/O");
      outputTree->Branch("HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1",      &HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1,     "HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1/O");
      outputTree->Branch("HLT_AK8PFJet330_PFAK8BTagCSV_p17",                    &HLT_AK8PFJet330_PFAK8BTagCSV_p17,                   "HLT_AK8PFJet330_PFAK8BTagCSV_p17/O");
      outputTree->Branch("HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02",  &HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02, "HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02/O");
      outputTree->Branch("HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2",  &HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2, "HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2/O");
      outputTree->Branch("HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4",  &HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4, "HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4/O"); 
      outputTree->Branch("HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p20",        &HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p20,       "HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p20/O");
      outputTree->Branch("HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p087",       &HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p087,      "HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p087/O");
      outputTree->Branch("HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p087",       &HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p087,      "HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p087/O");
      outputTree->Branch("HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20",     &HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20,    "HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20/O");
      outputTree->Branch("HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20",        &HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20,       "HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20/O");
      outputTree->Branch("HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20",        &HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20,       "HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20/O");	
    }


    cout << "Run With Option = " << Option << "\n";
    
    if (Option == 0) cout << "Option = 100 : No Cuts \n";
    if (Option == 2) cout << "Option = 2 : Select FatJets with pT > 200 GeV and PNetXbb > 0.8 only\n";
    if (Option == 5) cout << "Option = 5 : Select Events with FatJet1 pT > 200 GeV and PNetXbb > 0.8 only\n";
    if (Option == 10) cout << "Option = 10 : Select FatJets with pT > 200 GeV and tau3/tau2 < 0.54 only\n";
    if (Option == 20) cout << "Option = 20 : Select FatJets with pT > 200 GeV and MassSD>50, but only save Jet1 info\n";
    if (Option == 21) cout << "Option = 21 : Select FatJets with pT > 200 GeV and MassSD>50, but save all info\n";
    if (Option == 100) cout << "Option = 100 : No Cuts, save only genMTT \n";

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
      if(jentry % 1000 == 0) cout << "Processing entry " << jentry << endl;
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;


      //fill normalization histogram
      weight = genWeight / fabs(genWeight);
      NEvents->SetBinContent( 1, NEvents->GetBinContent(1) + weight);


      //reset tree variables
      genHiggs1Pt = -99.0;
      genHiggs1Eta = -99.0;
      genHiggs1Phi = -99.0;
      genHiggs2Pt = -99.0;
      genHiggs2Eta = -99.0;
      genHiggs2Phi = -99.0;
      genHH_pt = -99;
      genHH_eta = -99;
      genHH_phi = -99;
      genHH_mass = -99;   
      genWPt = -99.0;
      genWEta = -99.0;
      genWPhi = -99.0;
      genZPt = -99.0;
      genZEta = -99.0;
      genZPhi = -99.0;
      genTop1Pt = -99.0;
      genTop1Mass = -99.0;
      genTop1Eta = -99.0;
      genTop1Phi = -99.0;
      genTop2Pt = -99.0;
      genTop2Mass = -99.0;
      genTop2Eta = -99.0;
      genTop2Phi = -99.0;
      genMTT = -99;
      genLeptonId = 0;
      genLeptonMotherId = 0;
      genLeptonPt = -99.0;
      genLeptonEta = -99.0;
      genLeptonPhi = -99.0;
      genPhotonPt = -99.0;
      genPhotonEta = -99.0;
      genPhotonPhi = -99.0;
      NJets = -1;
      MET = -99.0;

      fatJet1Pt          = -99.0;
      fatJet1Pt_JES_Up   = -99.0;
      fatJet1Pt_JES_Down = -99.0;
      fatJet1Eta = -99.0;
      fatJet1Phi = -99.0;
      fatJet1Mass = -99.0;
      fatJet1MassSD      = -99.0;
      fatJet1MassSD_UnCorrected = -99.0;
      fatJet1MassSD_JMS_Up      = -99.0;
      fatJet1MassSD_JMS_Down    = -99.0;
      fatJet1MassSD_JMR_Up      = -99.0;
      fatJet1MassSD_JMR_Down    = -99.0;
      fatJet1DDBTagger = -99.0;
      fatJet1PNetXbb = -99;
      fatJet1PNetQCDb = -99;
      fatJet1PNetQCDbb = -99;
      fatJet1PNetQCDc = -99;
      fatJet1PNetQCDcc = -99;
      fatJet1PNetQCDothers = -99;
      fatJet1_deepTagMD_W =  -99;
      fatJet1_deepTagMD_Z =  -99;
      fatJet1_deepTag_W =  -99;
      fatJet1_deepTag_Z =  -99;   
      fatJet1GenMatchIndex = -99.0;
      fatJet1Tau3OverTau2 = -99;
      fatJet1_n2b1 = -99; 
      fatJet1HasMuon = 0;
      fatJet1HasElectron = 0;
      fatJet1HasBJetCSVLoose = 0;
      fatJet1HasBJetCSVMedium = 0;
      fatJet1HasBJetCSVTight = 0;      
      fatJet1OppositeHemisphereHasBJet = 0;
      fatJet2Pt = -99.0;
      fatJet2Pt_JES_Up   = -99.0;
      fatJet2Pt_JES_Down = -99.0;
      fatJet2Eta = -99.0;
      fatJet2Phi = -99.0;
      fatJet2Mass = -99.0;
      fatJet2MassSD = -99.0;
      fatJet2MassSD_UnCorrected = -99.0;
      fatJet2MassSD_JMS_Up      = -99.0;
      fatJet2MassSD_JMS_Down    = -99.0;
      fatJet2MassSD_JMR_Up      = -99.0;
      fatJet2MassSD_JMR_Down    = -99.0;
      fatJet2DDBTagger = -99.0;
      fatJet2PNetXbb = -99;
      fatJet2PNetQCDb = -99;
      fatJet2PNetQCDbb = -99;
      fatJet2PNetQCDc = -99;
      fatJet2PNetQCDcc = -99;
      fatJet2PNetQCDothers = -99;
      fatJet2_deepTagMD_W =  -99;
      fatJet2_deepTagMD_Z =  -99;
      fatJet2_deepTag_W =  -99;
      fatJet2_deepTag_Z =  -99;   
      fatJet2GenMatchIndex = -99.0;
      fatJet2Tau3OverTau2 = -99;
      fatJet2HasMuon = 0;
      fatJet2HasElectron = 0;
      fatJet2HasBJetCSVLoose = 0;
      fatJet2HasBJetCSVMedium = 0;
      fatJet2HasBJetCSVTight = 0;
      fatJet3Pt = -99.0;
      fatJet2Pt_JES_Up   = -99.0;
      fatJet2Pt_JES_Down = -99.0;
      fatJet3Eta = -99.0;
      fatJet3Phi = -99.0;
      fatJet3Mass = -99.0;
      fatJet3MassSD = -99.0;
      fatJet3MassSD_UnCorrected = -99.0;
      fatJet3MassSD_JMS_Up      = -99.0;
      fatJet3MassSD_JMS_Down    = -99.0;
      fatJet3MassSD_JMR_Up      = -99.0;
      fatJet3MassSD_JMR_Down    = -99.0;
      fatJet3DDBTagger = -99.0;
      fatJet3PNetXbb = -99;
      fatJet3PNetQCDb = -99;
      fatJet3PNetQCDbb = -99;
      fatJet3PNetQCDc = -99;
      fatJet3PNetQCDcc = -99;
      fatJet3PNetQCDothers = -99;
      fatJet3Tau3OverTau2 = -99;
      fatJet3HasMuon = 0;
      fatJet3HasElectron = 0;
      fatJet3HasBJetCSVLoose = 0;
      fatJet3HasBJetCSVMedium = 0;
      fatJet3HasBJetCSVTight = 0;
      hh_pt = -99;
      hh_eta = -99;
      hh_phi = -99;
      hh_mass = -99;
      hh_pt_JESUp = -99;
      hh_pt_JESDown = -99;
      hh_pt_JMSUp = -99;
      hh_pt_JMSDown = -99;
      hh_pt_JMRUp = -99;
      hh_pt_JMRDown = -99;
      hh_eta_JESUp = -99;
      hh_eta_JESDown = -99;
      hh_eta_JMSUp = -99;
      hh_eta_JMSDown = -99;
      hh_eta_JMRUp = -99;
      hh_eta_JMRDown = -99;
      hh_mass_JESUp = -99;
      hh_mass_JESDown = -99;
      hh_mass_JMSUp = -99;
      hh_mass_JMSDown = -99;
      hh_mass_JMRUp = -99;
      hh_mass_JMRDown = -99;  
      fatJet1PtOverMHH = -99;
      fatJet1PtOverMHH_JESUp = -99;
      fatJet1PtOverMHH_JESDown = -99;
      fatJet1PtOverMHH_JMSUp = -99;
      fatJet1PtOverMHH_JMSDown = -99;
      fatJet1PtOverMHH_JMRUp = -99;
      fatJet1PtOverMHH_JMRDown = -99;
      fatJet1PtOverMSD = -99;
      fatJet2PtOverMHH = -99;
      fatJet2PtOverMHH_JESUp = -99;
      fatJet2PtOverMHH_JESDown = -99;
      fatJet2PtOverMHH_JMSUp = -99;
      fatJet2PtOverMHH_JMSDown = -99;
      fatJet2PtOverMHH_JMRUp = -99;
      fatJet2PtOverMHH_JMRDown = -99;
      fatJet2PtOverMSD = -99;
      deltaEta_j1j2 = -99;
      deltaPhi_j1j2 = -99;
      deltaR_j1j2 = -99;    
      ptj2_over_ptj1 = -99;
      mj2_over_mj1 = -99;
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
      jet1DeepJetBTag = -99;
      jet2Pt = -99;
      jet2Eta = -99;
      jet2Phi = -99;
      jet2DeepJetBTag = -99;
      jet3Pt = -99;
      jet3Eta = -99;
      jet3Phi = -99;
      jet3DeepJetBTag = -99;
      jet4Pt = -99;
      jet4Eta = -99;
      jet4Phi = -99;
      jet4DeepJetBTag = -99;
      nBTaggedJets = 0;
      //variables for overlap removal with VBF HH->4b boosted analysis
      isVBFtag = 0;
      dijetmass = -99;
      vbfjet1Pt = -99;
      vbfjet1Eta = -99;
      vbfjet1Phi = -99;
      vbfjet1Mass = -99;
      vbfjet2Pt = -99;
      vbfjet2Eta = -99;
      vbfjet2Phi = -99;
      vbfjet2Mass = -99;
      vbffatJet1Pt = -99;
      vbffatJet1Eta = -99;
      vbffatJet1Phi = -99;
      vbffatJet1PNetXbb = -99;
      vbffatJet2Pt = -99;
      vbffatJet2Eta = -99;
      vbffatJet2Phi = -99;
      vbffatJet2PNetXbb = -99;

      //------------------------------
      //----Event variables------------
      //------------------------------
      MET = MET_pt;

      //------------------------------
      //----find gen-higgs------------
      //------------------------------
      int current_mIndex = -1;
      std::vector< TLorentzVector > genHiggsVector;
      if (!isData) {

	for(int i = 0; i < nGenPart; i++) {
	  if( abs(GenPart_pdgId[i]) == 5  && GenPart_pdgId[GenPart_genPartIdxMother[i]] == 25 && current_mIndex != GenPart_genPartIdxMother[i] ) {
	    //std::cout << GenPart_genPartIdxMother[i] << std::endl;
	    // std::cout << "mother: " << GenPart_pdgId[GenPart_genPartIdxMother[i]]
	    // << " PT: " << GenPart_pt[GenPart_genPartIdxMother[i]]
	    // << " eta: " << GenPart_eta[GenPart_genPartIdxMother[i]]
	    // << " phi: " << GenPart_phi[GenPart_genPartIdxMother[i]] << std::endl;
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


      //-------------------------------------------------------------
      //--- define random numbers for jet mass smearing correction
      //-------------------------------------------------------------
      double corr_fatJet1_mass_JMRUp = rnd->Gaus( 0.0, jmrValues[2] - 1.0 );
      double corr_fatJet1_mass = (fmax(jmrValues[0] - 1.0,0.0))/(jmrValues[2] - 1.0) * corr_fatJet1_mass_JMRUp;
      double corr_fatJet1_mass_JMRDown = (fmax(jmrValues[1] - 1.0,0.0))/(jmrValues[2] - 1.0) * corr_fatJet1_mass_JMRUp;
      double corr_fatJet2_mass_JMRUp = rnd->Gaus( 0.0, jmrValues[2] - 1.0 );
      double corr_fatJet2_mass = (fmax(jmrValues[0] - 1.0,0.0))/(jmrValues[2] - 1.0) * corr_fatJet2_mass_JMRUp;
      double corr_fatJet2_mass_JMRDown = (fmax(jmrValues[1] - 1.0,0.0))/(jmrValues[2] - 1.0) * corr_fatJet2_mass_JMRUp;
      double corr_fatJet3_mass_JMRUp = rnd->Gaus( 0.0, jmrValues[2] - 1.0 );
      double corr_fatJet3_mass = (fmax(jmrValues[0] - 1.0,0.0))/(jmrValues[2] - 1.0) * corr_fatJet3_mass_JMRUp;
      double corr_fatJet3_mass_JMRDown = (fmax(jmrValues[1] - 1.0,0.0))/(jmrValues[2] - 1.0) * corr_fatJet3_mass_JMRUp;
           
      //------------------------------
      //-------find fatJet------------
      //------------------------------
      vector<int> selectedFatJetIndices;

      for(unsigned int i = 0; i < nFatJet; i++ ) {       
	//Hbb fat jet pre-selection
	if (FatJet_pt[i] < 200) continue;
	
	//Select signal region with jets having DDB > 0.8
	if (Option == 1) {
	  if (!(FatJet_btagDDBvL[i] > 0.80)) continue;
	} 
	if (Option == 2) {
	  if (!(FatJet_ParticleNetMD_probXbb[i]/(1.0 - FatJet_ParticleNetMD_probXcc[i] - FatJet_ParticleNetMD_probXqq[i]) > 0.80)) continue;
	} 
	
	//Select ttbar control region with jets 
	if (Option == 10) {
	  if (!(FatJet_tau3[i] / FatJet_tau2[i] < 0.54 )) continue;
	} 
	selectedFatJetIndices.push_back(i);
      }

      //------------------------------------------------------
      //----------select the two H candidates with largest Xbb
      //------------------------------------------------------
      int fatJet1Index = -1;
      int fatJet2Index = -1;
      double tmpfatJet1Pt = -999;
      double tmpfatJet2Pt = -999;
      double tmpfatJet1Tagger = -999;
      double tmpfatJet2Tagger = -999;
        
      int vbffatJet1Index = -1;
      int vbffatJet2Index = -1;
      double tmpvbffatJet1Pt = -999;
      double tmpvbffatJet2Pt = -999;
        
      if (Option <= 10) {
	for(unsigned int i = 0; i < selectedFatJetIndices.size(); i++ ) {
	  double fatJetTagger = FatJet_ParticleNetMD_probXbb[selectedFatJetIndices[i]]/(1.0 - FatJet_ParticleNetMD_probXcc[selectedFatJetIndices[i]] - FatJet_ParticleNetMD_probXqq[selectedFatJetIndices[i]]);
	  if (fatJetTagger > tmpfatJet1Tagger) {
	    tmpfatJet2Tagger = tmpfatJet1Tagger;
	    fatJet2Index = fatJet1Index;	  
	    tmpfatJet1Tagger = fatJetTagger;
	    fatJet1Index = selectedFatJetIndices[i];
	  } else if (fatJetTagger > tmpfatJet2Tagger) {
	    tmpfatJet2Tagger = fatJetTagger;
	    fatJet2Index = selectedFatJetIndices[i];
	  }
        
      //fat jet used in the VBF HH->4b analysis
	  if (FatJet_pt[selectedFatJetIndices[i]] > tmpvbffatJet1Pt) {
	    tmpvbffatJet2Pt = vbffatJet1Pt;
	    vbffatJet2Index = vbffatJet1Index;	  
	    tmpvbffatJet1Pt = FatJet_pt[selectedFatJetIndices[i]];
	    vbffatJet1Index = selectedFatJetIndices[i];
	  } else if ( FatJet_pt[selectedFatJetIndices[i]] > tmpvbffatJet2Pt ) {
	    tmpvbffatJet2Pt = FatJet_pt[selectedFatJetIndices[i]];
	    vbffatJet2Index = selectedFatJetIndices[i];
	  } 
	}
        vbffatJet1Pt = FatJet_pt[vbffatJet1Index];
        vbffatJet1Eta = FatJet_eta[vbffatJet1Index];
        vbffatJet1Phi = FatJet_phi[vbffatJet1Index];
        vbffatJet1PNetXbb = FatJet_ParticleNetMD_probXbb[vbffatJet1Index]/(1.0 - FatJet_ParticleNetMD_probXcc[vbffatJet1Index] - FatJet_ParticleNetMD_probXqq[vbffatJet1Index]);
        vbffatJet2Pt = FatJet_pt[vbffatJet2Index];
        vbffatJet2Eta = FatJet_eta[vbffatJet2Index];
        vbffatJet2Phi = FatJet_phi[vbffatJet2Index];
        vbffatJet2PNetXbb = FatJet_ParticleNetMD_probXbb[vbffatJet2Index]/(1.0 - FatJet_ParticleNetMD_probXcc[vbffatJet2Index] - FatJet_ParticleNetMD_probXqq[vbffatJet2Index]);

      } else if (Option == 20 || Option == 21) {
	for(unsigned int i = 0; i < selectedFatJetIndices.size(); i++ ) {
	  if (FatJet_pt[selectedFatJetIndices[i]] > tmpfatJet1Pt) {
	    tmpfatJet2Pt = fatJet1Pt;
	    fatJet2Index = fatJet1Index;	  
	    tmpfatJet1Pt = FatJet_pt[selectedFatJetIndices[i]];
	    fatJet1Index = selectedFatJetIndices[i];
	  } else if ( FatJet_pt[selectedFatJetIndices[i]] > tmpfatJet2Pt ) {
	    tmpfatJet2Pt = FatJet_pt[selectedFatJetIndices[i]];
	    fatJet2Index = selectedFatJetIndices[i];
	  }
	}
      }

      


      //------------------------------------------------------
      //----------look for presence of a third AK8 jet
      //------------------------------------------------------
      int fatJet3Index = -1;
      //double tmpfatJet3Pt = -999;
      double tmpfatJet3Tagger = -999;
      for(unsigned int i = 0; i < nFatJet; i++ ) {  
	double fatJetTagger = FatJet_ParticleNetMD_probXbb[i]/(1.0 - FatJet_ParticleNetMD_probXcc[i] - FatJet_ParticleNetMD_probXqq[i]);
	//Hbb fat jet pre-selection
	if (FatJet_pt[i] < 100) continue;
	if (i == fatJet1Index || i == fatJet2Index) continue;
	if (fatJetTagger > tmpfatJet3Tagger) {
	  fatJet3Index = i;
	  //tmpfatJet3Pt = FatJet_pt[i];
	  tmpfatJet3Tagger = fatJetTagger;
	}
      }

      //------------------------------------------------------
      //----------Fill higgs candidate information
      //------------------------------------------------------
   
      fatJet1Pt = FatJet_pt[fatJet1Index];
      fatJet1Eta = FatJet_eta[fatJet1Index];
      fatJet1Phi                = FatJet_phi[fatJet1Index];
      fatJet1Mass               = FatJet_mass[fatJet1Index];
      fatJet1MassSD_UnCorrected = FatJet_msoftdrop[fatJet1Index];
      fatJet1MassSD = jmsValues[0]*fatJet1MassSD_UnCorrected;//correct, mass scale and resolution, for resolution subtract 1.0 from width

      //For MC apply jet energy and mass corrections
      if ( !isData ) {
	jecUnc->setJetEta(fatJet1Eta);
	jecUnc->setJetPt(fatJet1Pt);
	double unc = jecUnc->getUncertainty(true);
	fatJet1Pt_JES_Up   = fatJet1Pt*(1+unc);
	fatJet1Pt_JES_Down = fatJet1Pt/(1+unc);
	fatJet1MassSD             = ( 1.0 + corr_fatJet1_mass )*jmsValues[0]*fatJet1MassSD_UnCorrected;//correct, mass scale and resolution, for resolution subtract 1.0 from width
	fatJet1MassSD_JMS_Down    = (jmsValues[1]/jmsValues[0])*fatJet1MassSD;//jet mass scale down
	fatJet1MassSD_JMS_Up      = (jmsValues[2]/jmsValues[0])*fatJet1MassSD;//jrt mass scale up
	fatJet1MassSD_JMR_Down    = ( 1.0 + corr_fatJet1_mass_JMRDown )*jmsValues[0]*fatJet1MassSD_UnCorrected;//jet mass resolution down -- wrt scale corrected value -- for resolution subtract 1.0 from width
	fatJet1MassSD_JMR_Up      = ( 1.0 + corr_fatJet1_mass_JMRUp )*jmsValues[0]*fatJet1MassSD_UnCorrected;//jrt mass resolution up -- wrt to scale corrected value -- for resolution subtract 1.0 from width
      } 
      
      fatJet1DDBTagger = FatJet_btagDDBvL[fatJet1Index];
      fatJet1PNetXbb = FatJet_ParticleNetMD_probXbb[fatJet1Index]/(1.0 - FatJet_ParticleNetMD_probXcc[fatJet1Index] - FatJet_ParticleNetMD_probXqq[fatJet1Index]);
      fatJet1PNetQCDb = FatJet_ParticleNetMD_probQCDb[fatJet1Index];
      fatJet1PNetQCDbb = FatJet_ParticleNetMD_probQCDbb[fatJet1Index];
      fatJet1PNetQCDc = FatJet_ParticleNetMD_probQCDc[fatJet1Index];
      fatJet1PNetQCDcc = FatJet_ParticleNetMD_probQCDcc[fatJet1Index];
      fatJet1PNetQCDothers = FatJet_ParticleNetMD_probQCDothers[fatJet1Index];
      fatJet1_deepTagMD_W  =  FatJet_deepTagMD_WvsQCD[fatJet1Index];
      fatJet1_deepTagMD_Z  =  FatJet_deepTagMD_ZvsQCD[fatJet1Index];
      fatJet1_deepTag_W    =  FatJet_deepTag_WvsQCD[fatJet1Index]; 
      fatJet1_deepTag_Z    =  FatJet_deepTag_ZvsQCD[fatJet1Index]; 
      fatJet1Tau3OverTau2 = FatJet_tau3[fatJet1Index] /  FatJet_tau2[fatJet1Index];
      fatJet1_n2b1 = FatJet_n2b1[fatJet1Index];

      //****************************************
      //Define Higgs Jet TLorentzVectors
      //****************************************
      TLorentzVector Higgs1Jet;
      Higgs1Jet.SetPtEtaPhiM(fatJet1Pt,fatJet1Eta,fatJet1Phi,fatJet1MassSD);
      float Higgs1MinDR = 999.;
      int Higgs1_match_idx = -1;
      for( int j = 0; j < genHiggsVector.size(); j++) {
	if(Higgs1Jet.DeltaR(genHiggsVector[j]) < Higgs1MinDR) {
	  Higgs1MinDR = Higgs1Jet.DeltaR(genHiggsVector[j]);
	  Higgs1_match_idx = j;
	}
      }
      if(Higgs1MinDR < 0.4) {
	fatJet1GenMatchIndex = Higgs1_match_idx;
      }
      TLorentzVector Higgs1Jet_JESUp;
      Higgs1Jet_JESUp.SetPtEtaPhiM(fatJet1Pt_JES_Up,fatJet1Eta,fatJet1Phi,fatJet1MassSD);
      TLorentzVector Higgs1Jet_JESDown;
      Higgs1Jet_JESDown.SetPtEtaPhiM(fatJet1Pt_JES_Down,fatJet1Eta,fatJet1Phi,fatJet1MassSD);
      TLorentzVector Higgs1Jet_JMSUp;
      Higgs1Jet_JMSUp.SetPtEtaPhiM(fatJet1Pt,fatJet1Eta,fatJet1Phi,fatJet1MassSD_JMS_Up);
      TLorentzVector Higgs1Jet_JMSDown;
      Higgs1Jet_JMSDown.SetPtEtaPhiM(fatJet1Pt,fatJet1Eta,fatJet1Phi,fatJet1MassSD_JMS_Down);
      TLorentzVector Higgs1Jet_JMRUp;
      Higgs1Jet_JMRUp.SetPtEtaPhiM(fatJet1Pt,fatJet1Eta,fatJet1Phi,fatJet1MassSD_JMR_Up);
      TLorentzVector Higgs1Jet_JMRDown;
      Higgs1Jet_JMRDown.SetPtEtaPhiM(fatJet1Pt,fatJet1Eta,fatJet1Phi,fatJet1MassSD_JMR_Down);


      //find any bjets in opposite hemisphere as fatJet1
      double btagMediumCut = -1;
      if (year == "2016") btagMediumCut = 0.3033;
      else if (year == "2017") btagMediumCut = 0.3033 ;
      else if (year == "2018") btagMediumCut = 0.2770;
      for(unsigned int q = 0; q < nJet; q++ ) {       
	if (Jet_pt[q] > 25 && Jet_btagDeepB[q] > btagMediumCut && 
	    deltaPhi(fatJet1Phi, Jet_phi[q]) > 2.5
	    ) {
	  fatJet1OppositeHemisphereHasBJet = true;
	  break;
	}
      }
	

      //find muon inside jet
      for(unsigned int q = 0; q < nMuon; q++ ) {       
	if (Muon_pt[q] > 30 && Muon_looseId[q] && 
	    deltaR(fatJet1Eta , fatJet1Phi, Muon_eta[q], Muon_phi[q]) < 1.0
	    ) {
	  fatJet1HasMuon = true;
	  break;
	}
      }
      //find electron inside jet
      for(unsigned int q = 0; q < nElectron; q++ ) {       
	if (Electron_pt[q] > 30 && Electron_mvaFall17V2noIso_WP90[q] && 
	    deltaR(fatJet1Eta , fatJet1Phi, Electron_eta[q], Electron_phi[q]) < 1.0
	    ) {
	  fatJet1HasElectron = true;
	  break;
	}
      }
      //find loose b-tagged jet inside jet
      for(unsigned int q = 0; q < nJet; q++ ) {       
	if (Jet_btagDeepB[q] > 0.0521 && 
	    deltaR(fatJet1Eta , fatJet1Phi, Jet_eta[q], Jet_phi[q]) < 1.0
	    ) {
	  fatJet1HasBJetCSVLoose = true;
	  break;
	}
      }
     //find medium b-tagged jet inside jet
      for(unsigned int q = 0; q < nJet; q++ ) {       
	if (Jet_btagDeepB[q] > 0.3033 && 
	    deltaR(fatJet1Eta , fatJet1Phi, Jet_eta[q], Jet_phi[q]) < 1.0
	    ) {
	  fatJet1HasBJetCSVMedium = true;
	  break;
	}
      }
      //find tight b-tagged jet inside jet
      for(unsigned int q = 0; q < nJet; q++ ) {       
	if (Jet_btagDeepB[q] > 0.7489 && 
	    deltaR(fatJet1Eta , fatJet1Phi, Jet_eta[q], Jet_phi[q]) < 1.0
	    ) {
	  fatJet1HasBJetCSVTight = true;
	  break;
	}
      }



      fatJet2Pt = FatJet_pt[fatJet2Index];
      fatJet2Eta = FatJet_eta[fatJet2Index];
      fatJet2Phi                = FatJet_phi[fatJet2Index];
      fatJet2Mass               = FatJet_mass[fatJet2Index];
      fatJet2MassSD_UnCorrected = FatJet_msoftdrop[fatJet2Index];
      fatJet2MassSD             = jmsValues[0]*fatJet2MassSD_UnCorrected;//correct, mass scale and resolution, for resolution subtract 1.0 from width

     //For MC apply jet energy and mass corrections
      if ( !isData ) {
	jecUnc->setJetEta(fatJet2Eta);
	jecUnc->setJetPt(fatJet2Pt);
	double unc                = jecUnc->getUncertainty(true);
	fatJet2Pt_JES_Up   = fatJet2Pt*(1+unc);
	fatJet2Pt_JES_Down = fatJet2Pt/(1+unc);
        fatJet2MassSD             = ( 1.0 + corr_fatJet2_mass )*jmsValues[0]*fatJet2MassSD_UnCorrected;//correct, mass scale and resolution, for resolution subtract 1.0 from width
	fatJet2MassSD_JMS_Down    = (jmsValues[1]/jmsValues[0])*fatJet2MassSD;//jet mass scale down
	fatJet2MassSD_JMS_Up      = (jmsValues[2]/jmsValues[0])*fatJet2MassSD;//jrt mass scale up
	fatJet2MassSD_JMR_Down    = ( 1.0 + corr_fatJet2_mass_JMRDown )*jmsValues[0]*fatJet2MassSD_UnCorrected;//jet mass resolution down -- wrt scale corrected value -- for resolution subtract 1.0 from width
	fatJet2MassSD_JMR_Up      = ( 1.0 + corr_fatJet2_mass_JMRUp )*jmsValues[0]*fatJet2MassSD_UnCorrected;//jrt mass resolution up -- wrt to scale corrected value -- for resolution subtract 1.0 from width
       }
     
      fatJet2DDBTagger = FatJet_btagDDBvL[fatJet2Index];
      fatJet2PNetXbb = FatJet_ParticleNetMD_probXbb[fatJet2Index]/(1.0 - FatJet_ParticleNetMD_probXcc[fatJet2Index] - FatJet_ParticleNetMD_probXqq[fatJet2Index]);
      fatJet2PNetQCDb = FatJet_ParticleNetMD_probQCDb[fatJet2Index];
      fatJet2PNetQCDbb = FatJet_ParticleNetMD_probQCDbb[fatJet2Index];
      fatJet2PNetQCDc = FatJet_ParticleNetMD_probQCDc[fatJet2Index];
      fatJet2PNetQCDcc = FatJet_ParticleNetMD_probQCDcc[fatJet2Index];
      fatJet2PNetQCDothers = FatJet_ParticleNetMD_probQCDothers[fatJet2Index];
      fatJet2_deepTagMD_W  =  FatJet_deepTagMD_WvsQCD[fatJet2Index];
      fatJet2_deepTagMD_Z  =  FatJet_deepTagMD_ZvsQCD[fatJet2Index];
      fatJet2_deepTag_W    =  FatJet_deepTag_WvsQCD[fatJet2Index]; 
      fatJet2_deepTag_Z    =  FatJet_deepTag_ZvsQCD[fatJet2Index]; 
      fatJet2Tau3OverTau2 = FatJet_tau3[fatJet2Index] /  FatJet_tau2[fatJet2Index];


      TLorentzVector Higgs2Jet;
      Higgs2Jet.SetPtEtaPhiM(FatJet_pt[fatJet2Index],FatJet_eta[fatJet2Index],FatJet_phi[fatJet2Index],FatJet_msoftdrop[fatJet2Index]);
      float Higgs2MinDR = 999.;
      int Higgs2_match_idx = -1;
      for( int j = 0; j < genHiggsVector.size(); j++) {
	if(Higgs2Jet.DeltaR(genHiggsVector[j]) < Higgs2MinDR) {
	  Higgs2MinDR = Higgs2Jet.DeltaR(genHiggsVector[j]);
	  Higgs2_match_idx = j;
	}
      }
      if(Higgs2MinDR < 0.4) {
	fatJet2GenMatchIndex = Higgs2_match_idx;
      }
      TLorentzVector Higgs2Jet_JESUp;
      Higgs2Jet_JESUp.SetPtEtaPhiM(fatJet2Pt_JES_Up,fatJet2Eta,fatJet2Phi,fatJet2MassSD);
      TLorentzVector Higgs2Jet_JESDown;
      Higgs2Jet_JESDown.SetPtEtaPhiM(fatJet2Pt_JES_Down,fatJet2Eta,fatJet2Phi,fatJet2MassSD);
      TLorentzVector Higgs2Jet_JMSUp;
      Higgs2Jet_JMSUp.SetPtEtaPhiM(fatJet2Pt,fatJet2Eta,fatJet2Phi,fatJet2MassSD_JMS_Up);
      TLorentzVector Higgs2Jet_JMSDown;
      Higgs2Jet_JMSDown.SetPtEtaPhiM(fatJet2Pt,fatJet2Eta,fatJet2Phi,fatJet2MassSD_JMS_Down);
      TLorentzVector Higgs2Jet_JMRUp;
      Higgs2Jet_JMRUp.SetPtEtaPhiM(fatJet2Pt,fatJet2Eta,fatJet2Phi,fatJet2MassSD_JMR_Up);
      TLorentzVector Higgs2Jet_JMRDown;
      Higgs2Jet_JMRDown.SetPtEtaPhiM(fatJet2Pt,fatJet2Eta,fatJet2Phi,fatJet2MassSD_JMR_Down);

       
      //find muon inside jet
      for(unsigned int q = 0; q < nMuon; q++ ) {       
	if (Muon_pt[q] > 30 && Muon_looseId[q] && 
	    deltaR(fatJet2Eta , fatJet2Phi, Muon_eta[q], Muon_phi[q]) < 1.0
	    ) {
	  fatJet2HasMuon = true;
	  break;
	}
      }
      //find electron inside jet
      for(unsigned int q = 0; q < nElectron; q++ ) {       
	if (Electron_pt[q] > 30 && Electron_mvaFall17V2noIso_WP90[q] && 
	    deltaR(fatJet2Eta , fatJet2Phi, Electron_eta[q], Electron_phi[q]) < 1.0
	    ) {
	  fatJet2HasElectron = true;
	  break;
	}
      }
      //find loose b-tagged jet inside jet
      for(unsigned int q = 0; q < nJet; q++ ) {       
	if (Jet_btagDeepB[q] > 0.0521 && 
	    deltaR(fatJet2Eta , fatJet2Phi, Jet_eta[q], Jet_phi[q]) < 1.0
	    ) {
	  fatJet2HasBJetCSVLoose = true;
	  break;
	}
      }
      //find medium b-tagged jet inside jet
      for(unsigned int q = 0; q < nJet; q++ ) {       
	if (Jet_btagDeepB[q] > 0.3033 && 
	    deltaR(fatJet2Eta , fatJet2Phi, Jet_eta[q], Jet_phi[q]) < 1.0
	    ) {
	  fatJet2HasBJetCSVMedium = true;
	  break;
	}
      }
      //find tight b-tagged jet inside jet
      for(unsigned int q = 0; q < nJet; q++ ) {       
	if (Jet_btagDeepB[q] > 0.7489 && 
	    deltaR(fatJet2Eta , fatJet2Phi, Jet_eta[q], Jet_phi[q]) < 1.0
	    ) {
	  fatJet2HasBJetCSVTight = true;
	  break;
	}
      }


      //------------------------------------------------------
      //----------Fill Jet 3 information
      //------------------------------------------------------
      fatJet3Pt = FatJet_pt[fatJet3Index];
      fatJet3Eta = FatJet_eta[fatJet3Index];
      fatJet3Phi                = FatJet_phi[fatJet3Index];
      fatJet3Mass               = FatJet_mass[fatJet3Index];
      fatJet3MassSD_UnCorrected = FatJet_msoftdrop[fatJet3Index];
      fatJet3MassSD             = jmsValues[0]*fatJet3MassSD_UnCorrected;//correct, mass scale and resolution, for resolution subtract 1.0 from width
      if ( !isData ) {
          jecUnc->setJetEta(fatJet3Eta);
          jecUnc->setJetPt(fatJet3Pt);
          double unc                = jecUnc->getUncertainty(true);
          fatJet3Pt_JES_Up   = fatJet3Pt*(1+unc);
          fatJet3Pt_JES_Down = fatJet3Pt/(1+unc);
	  fatJet3MassSD             = ( 1.0 + corr_fatJet3_mass )*jmsValues[0]*fatJet3MassSD_UnCorrected;//correct, mass scale and resolution, for resolution subtract 1.0 from width
	  fatJet3MassSD_JMS_Down    = (jmsValues[1]/jmsValues[0])*fatJet3MassSD;//jet mass scale down
	  fatJet3MassSD_JMS_Up      = (jmsValues[2]/jmsValues[0])*fatJet3MassSD;//jrt mass scale up
	  fatJet3MassSD_JMR_Down    = ( 1.0 + corr_fatJet3_mass_JMRDown )*jmsValues[0]*fatJet3MassSD_UnCorrected;//jet mass resolution down -- wrt scale corrected value -- for resolution subtract 1.0 from width
	  fatJet3MassSD_JMR_Up      = ( 1.0 + corr_fatJet3_mass_JMRUp )*jmsValues[0]*fatJet3MassSD_UnCorrected;//jrt mass resolution up -- wrt to scale corrected value -- for resolution subtract 1.0 from width
      }
      


      fatJet3DDBTagger = FatJet_btagDDBvL[fatJet3Index];
      fatJet3PNetXbb = FatJet_ParticleNetMD_probXbb[fatJet3Index]/(1.0 - FatJet_ParticleNetMD_probXcc[fatJet3Index] - FatJet_ParticleNetMD_probXqq[fatJet3Index]);
      fatJet3PNetQCDb = FatJet_ParticleNetMD_probQCDb[fatJet3Index];
      fatJet3PNetQCDbb = FatJet_ParticleNetMD_probQCDbb[fatJet3Index];
      fatJet3PNetQCDc = FatJet_ParticleNetMD_probQCDc[fatJet3Index];
      fatJet3PNetQCDcc = FatJet_ParticleNetMD_probQCDcc[fatJet3Index];
      fatJet3PNetQCDothers = FatJet_ParticleNetMD_probQCDothers[fatJet3Index];

      fatJet3Tau3OverTau2 = FatJet_tau3[fatJet3Index] /  FatJet_tau2[fatJet3Index];
      //find muon inside jet
      for(unsigned int q = 0; q < nMuon; q++ ) {       
	if (Muon_pt[q] > 30 && Muon_looseId[q] && 
	    deltaR(fatJet3Eta , fatJet3Phi, Muon_eta[q], Muon_phi[q]) < 1.0
	    ) {
	  fatJet3HasMuon = true;
	  break;
	}
      }
      //find electron inside jet
      for(unsigned int q = 0; q < nElectron; q++ ) {       
	if (Electron_pt[q] > 30 && Electron_mvaFall17V2noIso_WP90[q] && 
	    deltaR(fatJet3Eta , fatJet3Phi, Electron_eta[q], Electron_phi[q]) < 1.0
	    ) {
	  fatJet3HasElectron = true;
	  break;
	}
      }
      //find loose b-tagged jet inside jet
      for(unsigned int q = 0; q < nJet; q++ ) {       
	if (Jet_btagDeepB[q] > 0.0521 && 
	    deltaR(fatJet3Eta , fatJet3Phi, Jet_eta[q], Jet_phi[q]) < 1.0
	    ) {
	  fatJet3HasBJetCSVLoose = true;
	  break;
	}
      }
     //find medium b-tagged jet inside jet
      for(unsigned int q = 0; q < nJet; q++ ) {       
	if (Jet_btagDeepB[q] > 0.3033 && 
	    deltaR(fatJet3Eta , fatJet3Phi, Jet_eta[q], Jet_phi[q]) < 1.0
	    ) {
	  fatJet3HasBJetCSVMedium = true;
	  break;
	}
      }
      //find tight b-tagged jet inside jet
      for(unsigned int q = 0; q < nJet; q++ ) {       
	if (Jet_btagDeepB[q] > 0.7489 && 
	    deltaR(fatJet3Eta , fatJet3Phi, Jet_eta[q], Jet_phi[q]) < 1.0
	    ) {
	  fatJet3HasBJetCSVTight = true;
	  break;
	}
      }


      //------------------------------------------------------
      //----------Fill hh candidate information
      //------------------------------------------------------
      hh_pt = (Higgs1Jet+Higgs2Jet).Pt();
      hh_eta = (Higgs1Jet+Higgs2Jet).Eta();
      hh_phi = (Higgs1Jet+Higgs2Jet).Phi();
      hh_mass = (Higgs1Jet+Higgs2Jet).M();     
      fatJet1PtOverMHH = fatJet1Pt / hh_mass;
      fatJet1PtOverMSD = fatJet1Pt / fatJet1MassSD;
      fatJet2PtOverMHH = fatJet2Pt / hh_mass;
      fatJet2PtOverMSD = fatJet2Pt / fatJet1MassSD;

      if ( !isData ) {
	hh_pt_JESUp = (Higgs1Jet_JESUp+Higgs2Jet_JESUp).Pt();
	hh_pt_JESDown = (Higgs1Jet_JESDown+Higgs2Jet_JESDown).Pt();
	hh_pt_JMSUp = (Higgs1Jet_JMSUp+Higgs2Jet_JMSUp).Pt();
	hh_pt_JMSDown = (Higgs1Jet_JMSDown+Higgs2Jet_JMSDown).Pt();
	hh_pt_JMRUp = (Higgs1Jet_JMRUp+Higgs2Jet_JMRUp).Pt();
	hh_pt_JMRDown = (Higgs1Jet_JMRDown+Higgs2Jet_JMRDown).Pt();
	hh_eta_JESUp = (Higgs1Jet_JESUp+Higgs2Jet_JESUp).Eta();
	hh_eta_JESDown = (Higgs1Jet_JESDown+Higgs2Jet_JESDown).Eta();
	hh_eta_JMSUp = (Higgs1Jet_JMSUp+Higgs2Jet_JMSUp).Eta();
	hh_eta_JMSDown = (Higgs1Jet_JMSDown+Higgs2Jet_JMSDown).Eta();
	hh_eta_JMRUp = (Higgs1Jet_JMRUp+Higgs2Jet_JMRUp).Eta();
	hh_eta_JMRDown = (Higgs1Jet_JMRDown+Higgs2Jet_JMRDown).Eta();
	hh_mass_JESUp = (Higgs1Jet_JESUp+Higgs2Jet_JESUp).M();
	hh_mass_JESDown = (Higgs1Jet_JESDown+Higgs2Jet_JESDown).M();
	hh_mass_JMSUp = (Higgs1Jet_JMSUp+Higgs2Jet_JMSUp).M();
	hh_mass_JMSDown = (Higgs1Jet_JMSDown+Higgs2Jet_JMSDown).M();
	hh_mass_JMRUp = (Higgs1Jet_JMRUp+Higgs2Jet_JMRUp).M();
	hh_mass_JMRDown = (Higgs1Jet_JMRDown+Higgs2Jet_JMRDown).M();  
	fatJet1PtOverMHH_JESUp = fatJet1Pt_JES_Up / hh_mass_JESUp;
	fatJet1PtOverMHH_JESDown = fatJet1Pt_JES_Down / hh_mass_JESDown;
	fatJet1PtOverMHH_JMSUp = fatJet1Pt / hh_mass_JMSUp;
	fatJet1PtOverMHH_JMSDown = fatJet1Pt / hh_mass_JMSDown;
	fatJet1PtOverMHH_JMRUp = fatJet1Pt / hh_mass_JMRUp;
	fatJet1PtOverMHH_JMRDown = fatJet1Pt / hh_mass_JMRDown;
	fatJet2PtOverMHH_JESUp = fatJet2Pt_JES_Up / hh_mass_JESUp;
	fatJet2PtOverMHH_JESDown = fatJet2Pt_JES_Down / hh_mass_JESDown;
	fatJet2PtOverMHH_JMSUp = fatJet2Pt / hh_mass_JMSUp;
	fatJet2PtOverMHH_JMSDown = fatJet2Pt / hh_mass_JMSDown;
	fatJet2PtOverMHH_JMRUp = fatJet2Pt / hh_mass_JMRUp;
	fatJet2PtOverMHH_JMRDown = fatJet2Pt / hh_mass_JMRDown;	
      }

      deltaEta_j1j2 = fabs(fatJet1Eta - fatJet2Eta);
      deltaPhi_j1j2 = deltaPhi(fatJet1Phi, fatJet2Phi);
      deltaR_j1j2 = deltaR(fatJet1Eta, fatJet1Phi, fatJet2Eta, fatJet2Phi);
      ptj2_over_ptj1 = fatJet2Pt / fatJet1Pt;
      mj2_over_mj1 = fatJet2MassSD / fatJet1MassSD;             

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
	  if (Photon_mvaID[i] > 0.42) continue;
	} else {
	  if (Photon_mvaID[i] > 0.14) continue;
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
      for(int i = 0; i < nJet; i++) {
	if (Jet_pt[i] > 30 && fabs(Jet_eta[i]) < 2.5
	    && deltaR(Jet_eta[i] , Jet_phi[i], fatJet1Eta, fatJet1Phi) > 0.8
	    && deltaR(Jet_eta[i] , Jet_phi[i], fatJet2Eta, fatJet2Phi) > 0.8
	    ) {
	  NJets++;
	}

	bool passBTag = false;
	if (year == "2018") {
	  if (Jet_pt[i] > 40 && fabs(Jet_eta[i]) < 2.5
	      && Jet_btagDeepFlavB[i] > 0.2770
	      && Jet_puId[i] >= 2	
	      && Jet_jetId[i] >= 4
	      ) {
	    passBTag = true;
	  }
	} else if (year == "2017" ) {
	  if (Jet_pt[i] > 40 && fabs(Jet_eta[i]) < 2.5
	      && Jet_btagDeepFlavB[i] > 0.3033
	      && Jet_puId[i] >= 2
	      && Jet_jetId[i] >= 4
	      ) {
	    passBTag = true;
	  }
	} else if (year == "2016") {
	  if (Jet_pt[i] > 30 && fabs(Jet_eta[i]) < 2.4
	      && Jet_btagDeepFlavB[i] > 0.3033
	      && Jet_puId[i] >= 2
	      && Jet_jetId[i] >= 4
	      ) {
	    passBTag = true;
	  }
	}
	
	if (passBTag) {
	  nBTaggedJets++;

	  if (nBTaggedJets==1) {
	    jet1Pt = Jet_pt[i];
	    jet1Eta = Jet_eta[i];
	    jet1Phi = Jet_phi[i];
	  }
	  if (nBTaggedJets==2) {
	    jet2Pt = Jet_pt[i];
	    jet2Eta = Jet_eta[i];
	    jet2Phi = Jet_phi[i];
	  }
	  if (nBTaggedJets==3) {
	    jet3Pt = Jet_pt[i];
	    jet3Eta = Jet_eta[i];
	    jet3Phi = Jet_phi[i];
	  }
	  if (nBTaggedJets==4) {
	    jet4Pt = Jet_pt[i];
	    jet4Eta = Jet_eta[i];
	    jet4Phi = Jet_phi[i];
	  }


	}

      //find AK4 jets for VBF HH->4b analysis
      //Pick a pair of opposite-η jets that maximizes mjj
      //pT>25 GeV, |η|<4.7, lepton cleaning (ΔR(j,e/μ)>0.4), AK8 jet cleaning (ΔR(j,AK8)>0.4),pass tight jet ID and medium pileup jet ID
      //Δη(jj) > 4.0 and mjjmax > 600 GeV, |ηtag jet|>1.5 for both jets
      if (Jet_pt[i] > 25 && fabs(Jet_eta[i]) < 4.7
	    && deltaR(Jet_eta[i] , Jet_phi[i], vbffatJet1Eta, vbffatJet1Phi) > 0.4
	    && deltaR(Jet_eta[i] , Jet_phi[i], vbffatJet2Eta, vbffatJet2Phi) > 0.4
        && Jet_puId[i] >= 2 && ((Jet_pt[i] <50 && Jet_jetId[i] >= 6 )||Jet_pt[i] >50)){
          if (year == "2016"){
            if (Jet_puId[i] < 3) continue;
          }
        
          bool islepoverlap = false;
          for(unsigned int j = 0; j < nMuon; j++ ) { 
              if(Muon_pt[j]>5 && deltaR(Jet_eta[i] , Jet_phi[i], Muon_eta[j], Muon_phi[j]) < 0.4){
                  islepoverlap = true;
                  break;
              }
          }
          for(unsigned int j = 0; j < nElectron; j++ ) { 
              if(Electron_pt[j]>7 && deltaR(Jet_eta[i] , Jet_phi[i], Electron_eta[j], Electron_phi[j]) < 0.4){
                  islepoverlap = true;
                  break;
              }
          }
          if(!islepoverlap) vbfjets_index.push_back(i);  
	}   
      
      } //loop over AK4 jets
      
      //get the AK4 jets with the largest mjj
      if(vbfjets_index.size()>1){
          int jet1_index = -99;
          int jet2_index = -99;
          for(int k=0; k<vbfjets_index.size();k++){
              for(int j=k+1; j<vbfjets_index.size();j++){
                  if(Jet_eta[vbfjets_index[k]]*Jet_eta[vbfjets_index[j]]<0){
                      TLorentzVector jet1,jet2;
                      jet1.SetPtEtaPhiM(Jet_pt[vbfjets_index[k]], Jet_eta[vbfjets_index[k]], Jet_phi[vbfjets_index[k]], Jet_mass[vbfjets_index[k]]);
                      jet2.SetPtEtaPhiM(Jet_pt[vbfjets_index[j]], Jet_eta[vbfjets_index[j]], Jet_phi[vbfjets_index[j]], Jet_mass[vbfjets_index[j]]);   
                      float tmp_dijetmass = (jet1 + jet2).M(); 
                      if(dijetmass < tmp_dijetmass){
                         dijetmass = tmp_dijetmass;
                         jet1_index = k;
                         jet2_index = j;
                      }              
                  }
              }
          }
          if((jet1_index > -99) && (jet2_index > -99)){
              vbfjet1Pt = Jet_pt[vbfjets_index[jet1_index]];
              vbfjet1Eta = Jet_eta[vbfjets_index[jet1_index]];
              vbfjet1Phi = Jet_phi[vbfjets_index[jet1_index]];
              vbfjet1Mass = Jet_mass[vbfjets_index[jet1_index]];
              vbfjet2Pt = Jet_pt[vbfjets_index[jet2_index]];
              vbfjet2Eta = Jet_eta[vbfjets_index[jet2_index]];
              vbfjet2Phi = Jet_phi[vbfjets_index[jet2_index]];
              vbfjet2Mass = Jet_mass[vbfjets_index[jet2_index]];
              isVBFtag = 0;
              if(fabs(vbfjet1Eta) > 1.5 && fabs(vbfjet2Eta) > 1.5 && dijetmass > 600 && fabs(vbfjet1Eta-vbfjet2Eta) > 4 && vbffatJet1Pt > 500 && vbffatJet2Pt > 400 && vbffatJet1PNetXbb > 0.9 && vbffatJet2PNetXbb > 0.9 && fabs(vbffatJet1Eta-vbffatJet2Eta) < 2.6 && fabs(vbffatJet1Phi-vbffatJet2Phi) > 2.6) isVBFtag = 1;
          }
      }
        
      //****************************************************
      //Fill Event - skim for events with two jets found
      //****************************************************
      if (
	  Option == 100 || 
	  Option == 0 || 
	  (Option == 5 && fatJet1Pt > 250 && fatJet2Pt > 250 && fatJet1MassSD > 50 
	   && fatJet2MassSD > 50 && fatJet1PNetXbb > 0.8) || 
	  (Option == 10 && ( (fatJet1Pt > 250 && fatJet2Pt > 250) || (fatJet1Pt > 250 && lep1Id != 0)) ) || 
	  (Option == 20 && fatJet1Pt > 250 && fatJet1MassSD > 30 && lep1Id == 0) ||
	  (Option == 21 && fatJet1Pt > 250 && fatJet1MassSD > 30 )
	  ) {
	 

	//****************************************************
	//Compute trigger efficiency weight
	//****************************************************      
	if (triggerEffHist) {
	  triggerEffWeight = 1.0 - 
	    (1 - getTriggerEff( triggerEffHist , fatJet1Pt, fatJet1MassSD )) * 
	    (1 - getTriggerEff( triggerEffHist , fatJet2Pt, fatJet2MassSD ))
	    ;
	  triggerEff3DWeight = 1.0 - 
	    (1 - getTriggerEff3D( triggerEffHist_Xbb0p0To0p9, 
				  triggerEffHist_Xbb0p9To0p95, 
				  triggerEffHist_Xbb0p95To0p98, 
				  triggerEffHist_Xbb0p98To1p0, 
				  fatJet1Pt, fatJet1MassSD, fatJet1PNetXbb )) * 
	    (1 - getTriggerEff3D( triggerEffHist_Xbb0p0To0p9, 
				  triggerEffHist_Xbb0p9To0p95, 
				  triggerEffHist_Xbb0p95To0p98, 
				  triggerEffHist_Xbb0p98To1p0, 
				  fatJet2Pt, fatJet2MassSD, fatJet2PNetXbb ))
	    ;	

	  triggerEffMCWeight = 1.0 - 
	    (1 - getTriggerEff( triggerEffMCHist , fatJet1Pt, fatJet1MassSD )) * 
	    (1 - getTriggerEff( triggerEffMCHist , fatJet2Pt, fatJet2MassSD ))
	    ;
	  triggerEffMC3DWeight = 1.0 - 
	    (1 - getTriggerEff3D( triggerEffMCHist_Xbb0p0To0p9, 
				  triggerEffMCHist_Xbb0p9To0p95, 
				  triggerEffMCHist_Xbb0p95To0p98, 
				  triggerEffMCHist_Xbb0p98To1p0, 
				  fatJet1Pt, fatJet1MassSD, fatJet1PNetXbb )) * 
	    (1 - getTriggerEff3D( triggerEffMCHist_Xbb0p0To0p9, 
				  triggerEffMCHist_Xbb0p9To0p95, 
				  triggerEffMCHist_Xbb0p95To0p98, 
				  triggerEffMCHist_Xbb0p98To1p0, 
				  fatJet2Pt, fatJet2MassSD, fatJet2PNetXbb ))
	    ;	

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
	//Compute totalWeight
	//****************************************************      
	totalWeight = weight * triggerEffWeight * pileupWeight;
 

	NEventsFilled++;            
	outputTree->Fill();      
      }
    }//end of event loop

    cout << "Filled Total of " << NEventsFilled << " Events\n";
    cout << "Writing output trees..." << endl;
    outFile->Write();
    outFile->Close();

}



