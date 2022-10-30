#!/usr/bin/python

import os
import datetime
import time
import subprocess
import glob
import sys
import json


datasets = {

# ####################################################################################################
# #2016 Datasets
# ####################################################################################################   
# "JetHT_2016B-ver2_HIPM":"/JetHT/Run2016B-ver2_HIPM_UL2016_MiniAODv2_NanoAODv9-v2/NANOAOD",
# "JetHT_2016C_HIPM":"/JetHT/Run2016C-HIPM_UL2016_MiniAODv2_NanoAODv9-v2/NANOAOD",
# "JetHT_2016D_HIPM":"/JetHT/Run2016D-HIPM_UL2016_MiniAODv2_NanoAODv9-v2/NANOAOD",
# "JetHT_2016E_HIPM":"/JetHT/Run2016E-HIPM_UL2016_MiniAODv2_NanoAODv9-v2/NANOAOD",
# "JetHT_2016F_HIPM":"/JetHT/Run2016F-HIPM_UL2016_MiniAODv2_NanoAODv9-v2/NANOAOD",
# "JetHT_2016F":"/JetHT/Run2016F-UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
# "JetHT_2016G":"/JetHT/Run2016G-UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
# "JetHT_2016H":"/JetHT/Run2016H-UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
# "MET_2016B-v1_HIPM":"/MET/Run2016B-ver1_HIPM_UL2016_MiniAODv2_NanoAODv9-v2/NANOAOD",
# "MET_2016B-v2_HIPM":"/MET/Run2016B-ver2_HIPM_UL2016_MiniAODv2_NanoAODv9-v2/NANOAOD",
# "MET_2016C_HIPM":"/MET/Run2016C-HIPM_UL2016_MiniAODv2_NanoAODv9-v2/NANOAOD",
# "MET_2016D_HIPM":"/MET/Run2016D-HIPM_UL2016_MiniAODv2_NanoAODv9-v2/NANOAOD",
# "MET_2016E_HIPM":"/MET/Run2016E-HIPM_UL2016_MiniAODv2_NanoAODv9-v2/NANOAOD",
# "MET_2016F_HIPM":"/MET/Run2016F-HIPM_UL2016_MiniAODv2_NanoAODv9-v2/NANOAOD",
# "MET_2016F":"/MET/Run2016F-UL2016_MiniAODv2_NanoAODv9-v2/NANOAOD",
# "MET_2016G":"/MET/Run2016G-UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
# "MET_2016H":"/MET/Run2016H-UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
# "SingleMuon_2016B-v1_HIPM":"/SingleMuon/Run2016B-ver1_HIPM_UL2016_MiniAODv2_NanoAODv9-v2/NANOAOD",
# "SingleMuon_2016B-v2_HIPM":"/SingleMuon/Run2016B-ver2_HIPM_UL2016_MiniAODv2_NanoAODv9-v2/NANOAOD",
# "SingleMuon_2016C_HIPM":"/SingleMuon/Run2016C-HIPM_UL2016_MiniAODv2_NanoAODv9-v2/NANOAOD",
# "SingleMuon_2016D_HIPM":"/SingleMuon/Run2016D-HIPM_UL2016_MiniAODv2_NanoAODv9-v2/NANOAOD",
# "SingleMuon_2016E_HIPM":"/SingleMuon/Run2016E-HIPM_UL2016_MiniAODv2_NanoAODv9-v2/NANOAOD",
# "SingleMuon_2016F_HIPM":"/SingleMuon/Run2016F-HIPM_UL2016_MiniAODv2_NanoAODv9-v2/NANOAOD",
# "SingleMuon_2016F":"/SingleMuon/Run2016F-UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
# "SingleMuon_2016G":"/SingleMuon/Run2016G-UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
# "SingleMuon_2016H":"/SingleMuon/Run2016H-UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
# "SingleElectron_2016B-v1_HIPM":"/SingleElectron/Run2016B-ver1_HIPM_UL2016_MiniAODv2_NanoAODv9-v2/NANOAOD",
# "SingleElectron_2016B-v2_HIPM":"/SingleElectron/Run2016B-ver2_HIPM_UL2016_MiniAODv2_NanoAODv9-v2/NANOAOD",
# "SingleElectron_2016C_HIPM":"/SingleElectron/Run2016C-HIPM_UL2016_MiniAODv2_NanoAODv9-v2/NANOAOD",
# "SingleElectron_2016D_HIPM":"/SingleElectron/Run2016D-HIPM_UL2016_MiniAODv2_NanoAODv9-v2/NANOAOD",
# "SingleElectron_2016E_HIPM":"/SingleElectron/Run2016E-HIPM_UL2016_MiniAODv2_NanoAODv9-v2/NANOAOD",
# "SingleElectron_2016F_HIPM":"/SingleElectron/Run2016F-HIPM_UL2016_MiniAODv2_NanoAODv9-v2/NANOAOD",
# "SingleElectron_2016F":"/SingleElectron/Run2016F-UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
# "SingleElectron_2016G":"/SingleElectron/Run2016G-UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
# "SingleElectron_2016H":"/SingleElectron/Run2016H-UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
# "Tau_2016B-v1_HIPM":"/Tau/Run2016B-ver1_HIPM_UL2016_MiniAODv2_NanoAODv9-v2/NANOAOD",
# "Tau_2016B-v2_HIPM":"/Tau/Run2016B-ver2_HIPM_UL2016_MiniAODv2_NanoAODv9-v2/NANOAOD",
# "Tau_2016C_HIPM":"/Tau/Run2016C-HIPM_UL2016_MiniAODv2_NanoAODv9-v2/NANOAOD",
# "Tau_2016D_HIPM":"/Tau/Run2016D-HIPM_UL2016_MiniAODv2_NanoAODv9-v2/NANOAOD",
# "Tau_2016E_HIPM":"/Tau/Run2016E-HIPM_UL2016_MiniAODv2_NanoAODv9-v2/NANOAOD",
# "Tau_2016F_HIPM":"/Tau/Run2016F-HIPM_UL2016_MiniAODv2_NanoAODv9-v2/NANOAOD",
# "Tau_2016F":"/Tau/Run2016F-UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
# "Tau_2016G":"/Tau/Run2016G-UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",
# "Tau_2016H":"/Tau/Run2016H-UL2016_MiniAODv2_NanoAODv9-v1/NANOAOD",


# ####################################################################################################
# #2017 Datasets
# ####################################################################################################   
#"JetHT_2017B":"/JetHT/Run2017B-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"JetHT_2017C":"/JetHT/Run2017C-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"JetHT_2017D":"/JetHT/Run2017D-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"JetHT_2017E":"/JetHT/Run2017E-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"JetHT_2017F":"/JetHT/Run2017F-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD",
# "MET_2017B":"/MET/Run2017B-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD",
# "MET_2017C":"/MET/Run2017C-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD",
# "MET_2017D":"/MET/Run2017D-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD",
# "MET_2017E":"/MET/Run2017E-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD",
# "MET_2017F":"/MET/Run2017F-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD",
# "SingleMuon_2017B":"/SingleMuon/Run2017B-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD",
# "SingleMuon_2017C":"/SingleMuon/Run2017C-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD",
# "SingleMuon_2017D":"/SingleMuon/Run2017D-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD",
# "SingleMuon_2017E":"/SingleMuon/Run2017E-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD",
# "SingleMuon_2017F":"/SingleMuon/Run2017F-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD",
# "SingleMuon_2017G":"/SingleMuon/Run2017G-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD",
# "SingleMuon_2017H":"/SingleMuon/Run2017H-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD",
# "SingleElectron_2017B":"/SingleElectron/Run2017B-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD",
# "SingleElectron_2017C":"/SingleElectron/Run2017C-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD",
# "SingleElectron_2017D":"/SingleElectron/Run2017D-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD",
# "SingleElectron_2017E":"/SingleElectron/Run2017E-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD",
# "SingleElectron_2017F":"/SingleElectron/Run2017F-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD",
# "Tau_2017B":"/Tau/Run2017B-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD",
# "Tau_2017C":"/Tau/Run2017C-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD",
# "Tau_2017D":"/Tau/Run2017D-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD",
# "Tau_2017E":"/Tau/Run2017E-UL2017_MiniAODv2_NanoAODv9-v2/NANOAOD",
# "Tau_2017F":"/Tau/Run2017F-UL2017_MiniAODv2_NanoAODv9-v1/NANOAOD",

####################################################################################################
#2018 Datasets
####################################################################################################   
#"JetHT_2018A":"/JetHT/Run2018A-UL2018_MiniAODv2_NanoAODv9-v2/NANOAOD",
#"JetHT_2018B":"/JetHT/Run2018B-UL2018_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"JetHT_2018C":"/JetHT/Run2018C-UL2018_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"JetHT_2018D":"/JetHT/Run2018D-UL2018_MiniAODv2_NanoAODv9-v2/NANOAOD",
#"MET_2018A":"/MET/Run2018A-UL2018_MiniAODv2_NanoAODv9-v2/NANOAOD",
#"MET_2018B":"/MET/Run2018B-UL2018_MiniAODv2_NanoAODv9-v2/NANOAOD",
#"MET_2018C":"/MET/Run2018C-UL2018_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"MET_2018D":"/MET/Run2018D-UL2018_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"SingleMuon_2018A":"/SingleMuon/Run2018A-UL2018_MiniAODv2_NanoAODv9-v2/NANOAOD",
#"SingleMuon_2018B":"/SingleMuon/Run2018B-UL2018_MiniAODv2_NanoAODv9-v2/NANOAOD",
#"SingleMuon_2018C":"/SingleMuon/Run2018C-UL2018_MiniAODv2_NanoAODv9-v2/NANOAOD",
#"SingleMuon_2018D":"/SingleMuon/Run2018D-UL2018_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"EGamma_2018A":"/EGamma/Run2018A-UL2018_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"EGamma_2018B":"/EGamma/Run2018B-UL2018_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"EGamma_2018C":"/EGamma/Run2018C-UL2018_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"EGamma_2018D":"/EGamma/Run2018D-UL2018_MiniAODv2_NanoAODv9-v3/NANOAOD",
#"Tau_2018A":"/Tau/Run2018A-UL2018_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"Tau_2018B":"/Tau/Run2018B-UL2018_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"Tau_2018C":"/Tau/Run2018C-UL2018_MiniAODv2_NanoAODv9-v1/NANOAOD",
#"Tau_2018D":"/Tau/Run2018D-UL2018_MiniAODv2_NanoAODv9-v2/NANOAOD",



# "DiPhotonJetsBox1BJet_MGG-80toInf_13TeV-sherpa":"/DiPhotonJetsBox1BJet_MGG-80toInf_13TeV-sherpa/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
# "DiPhotonJetsBox2BJets_MGG-80toInf_13TeV-sherpa":"/DiPhotonJetsBox2BJets_MGG-80toInf_13TeV-sherpa/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
# "DiPhotonJetsBox_M40_80-sherpa":"/DiPhotonJetsBox_M40_80-sherpa/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
# "DiPhotonJetsBox_MGG-80toInf_13TeV-sherpa":"/DiPhotonJetsBox_MGG-80toInf_13TeV-sherpa/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
# "QCD_HT200to300_TuneCP5_13TeV-madgraphMLM-pythia8":"/QCD_HT200to300_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
# "QCD_HT300to500_TuneCP5_13TeV-madgraphMLM-pythia8":"/QCD_HT300to500_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
# "QCD_HT500to700_TuneCP5_13TeV-madgraphMLM-pythia8":"/QCD_HT500to700_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
# "QCD_HT700to1000_TuneCP5_13TeV-madgraphMLM-pythia8":"/QCD_HT700to1000_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
# "QCD_HT1000to1500_TuneCP5_13TeV-madgraphMLM-pythia8":"/QCD_HT1000to1500_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
# "QCD_HT1500to2000_TuneCP5_13TeV-madgraphMLM-pythia8":"/QCD_HT1500to2000_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
# "QCD_HT2000toInf_TuneCP5_13TeV-madgraphMLM-pythia8":"/QCD_HT2000toInf_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
# "QCD_Pt-30toInf_DoubleEMEnriched_MGG-40to80_TuneCP5_13TeV-pythia8":"/QCD_Pt-30toInf_DoubleEMEnriched_MGG-40to80_TuneCP5_13TeV-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
# "QCD_Pt-40ToInf_DoubleEMEnriched_MGG-80ToInf_TuneCP5_13TeV-pythia8":"/QCD_Pt-40ToInf_DoubleEMEnriched_MGG-80ToInf_TuneCP5_13TeV-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
# "GJets_DR-0p4_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8":"/GJets_DR-0p4_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
# "GJets_DR-0p4_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8":"/GJets_DR-0p4_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
# "GJets_DR-0p4_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8":"/GJets_DR-0p4_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
# "GJets_DR-0p4_HT-600ToInf_TuneCP5_13TeV-madgraphMLM-pythia8":"/GJets_DR-0p4_HT-600ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
# "TTJets_TuneCP5_13TeV-madgraphMLM-pythia8":"/TTJets_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM",
# /TTGG_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM
# /TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM
# /TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1_ext1-v1/NANOAODSIM
# /TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM
# /TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL18NanoAODv9-20UL18JMENano_106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM
# /TTJets_DiLept_genMET-150_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM
# /TTJets_HT-1200to2500_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM
# /TTJets_HT-2500toInf_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM
# /TTJets_HT-600to800_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM
# /TTJets_HT-800to1200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM
# /TTJets_SingleLeptFromT_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM
# /TTJets_SingleLeptFromTbar_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1/NANOAODSIM





    #"VLLPair_VLLToTauS_MVLL1000_MS10_ctau100":"/VLLPair_VLLToTauS_MVLL1000_MS10_ctau100/lpclonglived-crab_PrivateProduction_UL18_DR_step5_VLLPair_VLLToTauS_MVLL1000_MS10_ctau100_batch1_v1-00000000000000000000000000000000/USER",
    #"VLLPair_VLLToTauS_MVLL200_MS10_ctau300":"/VLLPair_VLLToTauS_MVLL200_MS10_ctau300/lpclonglived-crab_PrivateProduction_UL18_DR_step5_VLLPair_VLLToTauS_MVLL200_MS10_ctau300_batch2_v1-00000000000000000000000000000000/USER",
    #"VLLPair_VLLToTauS_MVLL300_MS10_ctau300":"/VLLPair_VLLToTauS_MVLL300_MS10_ctau300/lpclonglived-crab_PrivateProduction_UL18_DR_step5_VLLPair_VLLToTauS_MVLL300_MS10_ctau300_batch2_v1-00000000000000000000000000000000/USER",
    #"VLLPair_VLLToTauS_MVLL700_MS10_ctau100":"/VLLPair_VLLToTauS_MVLL700_MS10_ctau100/lpclonglived-crab_PrivateProduction_UL18_DR_step5_VLLPair_VLLToTauS_MVLL700_MS10_ctau100_batch2_v1-00000000000000000000000000000000/USER",
}

# if (len(sys.argv) -1 < 1):
#     print "Error. Not enough arguments provided.\n"
#     print "Usage: python printFilesInGivenBlocks.py\n"
#     exit()

#datasetName = sys.argv[1]


for processName in datasets.keys():

    outputFile = open(processName+".list","w")
    print processName
    #command = "dasgoclient -query=\"file dataset=" + datasets[processName] + " instance=prod/phys03 \" -json > tmpOutput.json"
    command = "dasgoclient -query=\"file dataset=" + datasets[processName] + " \" -json > tmpOutput.json"
    print (command)
    os.system(command)

    jsonFile = open("tmpOutput.json","r")
    data = json.load(jsonFile)

    for p in data:
        blockName = p['file'][0]['block.name']
        fileName = p['file'][0]['name']
        outputFile.write("root://cmsxrootd.fnal.gov/"+fileName+"\n")
    

    

