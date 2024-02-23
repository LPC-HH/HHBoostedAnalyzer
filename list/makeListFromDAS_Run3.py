#!/usr/bin/python

import os
import datetime
import time
import subprocess
import glob
import sys
import json


datasets = {

####################################################################################################
#2022 Datasets
####################################################################################################   
#'JetMET_2022C':'/JetMET/Run2022C-PromptNanoAODv10_v1-v1/NANOAOD',
#'JetMET_2022D-v1':'/JetMET/Run2022D-PromptNanoAODv10_v1-v1/NANOAOD',
#'JetMET_2022D-v2':'/JetMET/Run2022D-PromptNanoAODv10_v2-v1/NANOAOD',
#'JetMET_2022E':'/JetMET/Run2022E-PromptNanoAODv10_v1-v3/NANOAOD',
#'JetMET_2022F':'/JetMET/Run2022F-PromptNanoAODv10_v1-v2/NANOAOD',
#'JetMET_2022G':'/JetMET/Run2022G-PromptNanoAODv10_v1-v1/NANOAOD',
# 'EGamma_2022A':'/EGamma/Run2022A-ReRecoNanoAODv11-v1/NANOAOD',
# 'EGamma_2022B':'/EGamma/Run2022B-ReRecoNanoAODv11-v1/NANOAOD',
# 'EGamma_2022C':'/EGamma/Run2022C-ReRecoNanoAODv11-v1/NANOAOD',
# 'EGamma_2022D':'/EGamma/Run2022D-ReRecoNanoAODv11-v1/NANOAOD',
# 'EGamma_2022E':'/EGamma/Run2022E-ReRecoNanoAODv11-v1/NANOAOD',
# 'EGamma_2022F':'/EGamma/Run2022F-PromptNanoAODv11_v1-v2/NANOAOD',
# 'EGamma_2022G':'/EGamma/Run2022G-PromptNanoAODv11_v1-v2/NANOAOD',
# 'SingleMuon_2022A':'/SingleMuon/Run2022A-ReRecoNanoAODv11-v1/NANOAOD',
# 'SingleMuon_2022B':'/SingleMuon/Run2022B-ReRecoNanoAODv11-v1/NANOAOD',
# 'SingleMuon_2022C':'/SingleMuon/Run2022C-ReRecoNanoAODv11-v1/NANOAOD',
# 'Muon_2022C':'/Muon/Run2022C-ReRecoNanoAODv11-v1/NANOAOD',
# 'Muon_2022D':'/Muon/Run2022D-ReRecoNanoAODv11-v1/NANOAOD',
# 'Muon_2022E':'/Muon/Run2022E-ReRecoNanoAODv11-v1/NANOAOD',
# 'Muon_2022F':'/Muon/Run2022F-PromptNanoAODv11_v1-v2/NANOAOD',
# 'Muon_2022G':'/Muon/Run2022G-PromptNanoAODv11_v1-v2/NANOAOD',
# 'JetHT_2022A':'/JetHT/Run2022A-ReRecoNanoAODv11-v1/NANOAOD',
# 'JetHT_2022B':'/JetHT/Run2022B-ReRecoNanoAODv11-v1/NANOAOD',
# 'JetHT_2022C':'/JetHT/Run2022C-ReRecoNanoAODv11-v1/NANOAOD',
# 'JetMET_2022C':'/JetMET/Run2022C-ReRecoNanoAODv11-v1/NANOAOD',
# 'JetMET_2022D':'/JetMET/Run2022D-ReRecoNanoAODv11-v1/NANOAOD',
# 'JetMET_2022E':'/JetMET/Run2022E-ReRecoNanoAODv11-v1/NANOAOD',
# 'JetMET_2022F':'/JetMET/Run2022F-PromptNanoAODv11_v1-v2/NANOAOD',
# 'JetMET_2022G':'/JetMET/Run2022G-PromptNanoAODv11_v1-v2/NANOAOD',

#Private MC
#'ggHH_cHHH_1_TSG':'/ggHH_cHHH_1/lpcdihiggsboost-crab_PrivateProduction_Summer22_DR_step4_MINIAODSIM_ggHH_cHHH_1_batch1_v2-00000000000000000000000000000000/USER',
# "GluGlutoHHto4B_kl-0p00_kt-1p00_c2-0p00":"/GluGlutoHHto4B_kl-0p00_kt-1p00_c2-0p00_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22EENanoAODv10-Poisson60KeepRAW_124X_mcRun3_2022_realistic_postEE_v1-v2/NANOAODSIM",
# "GluGlutoHHto4B_kl-0p00_kt-1p00_c2-1p00":"/GluGlutoHHto4B_kl-0p00_kt-1p00_c2-1p00_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22EENanoAODv10-Poisson60KeepRAW_124X_mcRun3_2022_realistic_postEE_v1-v2/NANOAODSIM",
# "GluGlutoHHto4B_kl-1p00_kt-1p00_c2-0p00":"/GluGlutoHHto4B_kl-1p00_kt-1p00_c2-0p00_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22EENanoAODv10-Poisson60KeepRAW_124X_mcRun3_2022_realistic_postEE_v1-v2/NANOAODSIM",
# "GluGlutoHHto4B_kl-1p00_kt-1p00_c2-0p10":"/GluGlutoHHto4B_kl-1p00_kt-1p00_c2-0p10_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22EENanoAODv10-Poisson60KeepRAW_124X_mcRun3_2022_realistic_postEE_v1-v2/NANOAODSIM",
# "GluGlutoHHto4B_kl-1p00_kt-1p00_c2-0p35":"/GluGlutoHHto4B_kl-1p00_kt-1p00_c2-0p35_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22EENanoAODv10-Poisson60KeepRAW_124X_mcRun3_2022_realistic_postEE_v1-v2/NANOAODSIM",
# "GluGlutoHHto4B_kl-1p00_kt-1p00_c2-3p00":"/GluGlutoHHto4B_kl-1p00_kt-1p00_c2-3p00_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22EENanoAODv10-Poisson60KeepRAW_124X_mcRun3_2022_realistic_postEE_v1-v2/NANOAODSIM",
# "GluGlutoHHto4B_kl-1p00_kt-1p00_c2-m2p00":"/GluGlutoHHto4B_kl-1p00_kt-1p00_c2-m2p00_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22EENanoAODv10-Poisson60KeepRAW_124X_mcRun3_2022_realistic_postEE_v1-v2/NANOAODSIM",
# "GluGlutoHHto4B_kl-2p45_kt-1p00_c2-0p00":"/GluGlutoHHto4B_kl-2p45_kt-1p00_c2-0p00_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22EENanoAODv10-Poisson60KeepRAW_124X_mcRun3_2022_realistic_postEE_v1-v2/NANOAODSIM",
# "GluGlutoHHto4B_kl-5p00_kt-1p00_c2-0p00":"/GluGlutoHHto4B_kl-5p00_kt-1p00_c2-0p00_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22EENanoAODv10-Poisson60KeepRAW_124X_mcRun3_2022_realistic_postEE_v1-v2/NANOAODSIM",

#2022 MC 
# 'QCDPt15to30':'/QCD_PT-15to30_TuneCP5_13p6TeV_pythia8/Run3Summer22NanoAODv11-126X_mcRun3_2022_realistic_v2-v1/NANOAODSIM',
# 'QCDPt30to50':'/QCD_PT-30to50_TuneCP5_13p6TeV_pythia8/Run3Summer22NanoAODv11-126X_mcRun3_2022_realistic_v2-v1/NANOAODSIM',
# 'QCDPt50to80':'/QCD_PT-50to80_TuneCP5_13p6TeV_pythia8/Run3Summer22NanoAODv11-126X_mcRun3_2022_realistic_v2_ext1-v1/NANOAODSIM',
# 'QCDPt80to120':'/QCD_PT-80to120_TuneCP5_13p6TeV_pythia8/Run3Summer22NanoAODv11-126X_mcRun3_2022_realistic_v2_ext1-v1/NANOAODSIM',
# 'QCDPt120to170':'/QCD_PT-120to170_TuneCP5_13p6TeV_pythia8/Run3Summer22NanoAODv11-126X_mcRun3_2022_realistic_v2_ext1-v1/NANOAODSIM',
# 'QCDPt170to300':'/QCD_PT-170to300_TuneCP5_13p6TeV_pythia8/Run3Summer22NanoAODv11-126X_mcRun3_2022_realistic_v2_ext1-v1/NANOAODSIM',
# 'QCDPt470to600':'/QCD_PT-470to600_TuneCP5_13p6TeV_pythia8/Run3Summer22NanoAODv11-126X_mcRun3_2022_realistic_v2_ext1-v1/NANOAODSIM',
# 'QCDPt600to800':'/QCD_PT-600to800_TuneCP5_13p6TeV_pythia8/Run3Summer22NanoAODv11-126X_mcRun3_2022_realistic_v2_ext1-v1/NANOAODSIM',
# 'QCDPt800to1000':'/QCD_PT-800to1000_TuneCP5_13p6TeV_pythia8/Run3Summer22NanoAODv11-126X_mcRun3_2022_realistic_v2_ext1-v1/NANOAODSIM',
# 'QCDPt1000to1400':'/QCD_PT-1000to1400_TuneCP5_13p6TeV_pythia8/Run3Summer22NanoAODv11-126X_mcRun3_2022_realistic_v2_ext1-v1/NANOAODSIM',
# 'QCDPt1400to1800':'/QCD_PT-1400to1800_TuneCP5_13p6TeV_pythia8/Run3Summer22NanoAODv11-126X_mcRun3_2022_realistic_v2_ext1-v1/NANOAODSIM',
# 'QCDPt1800to2400':'/QCD_PT-1800to2400_TuneCP5_13p6TeV_pythia8/Run3Summer22NanoAODv11-126X_mcRun3_2022_realistic_v2_ext1-v1/NANOAODSIM',
# 'QCDPt2400to3200':'/QCD_PT-2400to3200_TuneCP5_13p6TeV_pythia8/Run3Summer22NanoAODv11-126X_mcRun3_2022_realistic_v2_ext1-v1/NANOAODSIM',
# 'QCDPt3200toInf':'/QCD_PT-3200_TuneCP5_13p6TeV_pythia8/Run3Summer22NanoAODv11-126X_mcRun3_2022_realistic_v2_ext1-v1/NANOAODSIM',
# 'ggHto2B_Pt200ToInf':'/GluGluHto2B_PT-200_M-125_TuneCP5_13p6TeV_powheg-minlo-pythia8/Run3Summer22NanoAODv11-126X_mcRun3_2022_realistic_v2-v1/NANOAODSIM',
# 'VBFHto2B':'/VBFHto2B_M-125_dipoleRecoilOn_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22NanoAODv11-126X_mcRun3_2022_realistic_v2-v1/NANOAODSIM',
# 'WminusH_Hto2B_Wto2Q':'/WminusH_Hto2B_Wto2Q_M-125_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22NanoAODv11-126X_mcRun3_2022_realistic_v2-v1/NANOAODSIM',
# 'WplusH_Hto2B_Wto2Q':'/WplusH_Hto2B_Wto2Q_M-125_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22NanoAODv11-126X_mcRun3_2022_realistic_v2-v1/NANOAODSIM',
# 'ZH_Hto2B_Zto2Q':'/ZH_Hto2B_Zto2Q_M-125_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22NanoAODv11-126X_mcRun3_2022_realistic_v2-v1/NANOAODSIM',
# 'ggZH_Hto2B_Zto2Q':'/ggZH_Hto2B_Zto2Q_M-125_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22NanoAODv11-126X_mcRun3_2022_realistic_v2-v1/NANOAODSIM',
# 'ttH_Hto2B':'/ttHto2B_M-125_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22NanoAODv11-126X_mcRun3_2022_realistic_v2-v1/NANOAODSIM',
# 'WW':'/WW_TuneCP5_13p6TeV_pythia8/Run3Summer22NanoAODv11-126X_mcRun3_2022_realistic_v2-v2/NANOAODSIM',
# 'WZ':'/WZ_TuneCP5_13p6TeV_pythia8/Run3Summer22NanoAODv11-126X_mcRun3_2022_realistic_v2-v1/NANOAODSIM',
# 'ZZ':'/ZZ_TuneCP5_13p6TeV_pythia8/Run3Summer22NanoAODv11-126X_mcRun3_2022_realistic_v2-v1/NANOAODSIM',
# 'DYJetsToLL_M50ToInf':'/DYJetsToLL_M-50_TuneCP5_13p6TeV-madgraphMLM-pythia8/Run3Summer22NanoAODv11-forPOG_126X_mcRun3_2022_realistic_v2-v1/NANOAODSIM',
#'Wto2Q-3Jets_HT-200to400':'/Wto2Q-3Jets_HT-200to400_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Summer22NanoAODv11-126X_mcRun3_2022_realistic_v2-v2/NANOAODSIM',
#'Wto2Q-3Jets_HT-400to600':'/Wto2Q-3Jets_HT-400to600_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Summer22NanoAODv11-126X_mcRun3_2022_realistic_v2-v2/NANOAODSIM',
#'Wto2Q-3Jets_HT-600to800':'/Wto2Q-3Jets_HT-600to800_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Summer22NanoAODv11-126X_mcRun3_2022_realistic_v2-v2/NANOAODSIM',
#'Wto2Q-3Jets_HT-800':'/Wto2Q-3Jets_HT-800_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Summer22NanoAODv11-126X_mcRun3_2022_realistic_v2-v2/NANOAODSIM',
#'WtoLNu-2Jets':'/WtoLNu-2Jets_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/Run3Summer22NanoAODv11-126X_mcRun3_2022_realistic_v2-v1/NANOAODSIM',
'VBFHHto2B2G_CV_1_C2V_0_C3_1':'/VBFHHto2B2G_CV_1_C2V_0_C3_1_TuneCP5_13p6TeV_madgraph-pythia8/Run3Summer22NanoAODv11-126X_mcRun3_2022_realistic_v2-v2/NANOAODSIM',
'VBFHHto2B2G_CV_1_C2V_1_C3_1':'/VBFHHto2B2G_CV_1_C2V_1_C3_1_TuneCP5_13p6TeV_madgraph-pythia8/Run3Summer22NanoAODv11-126X_mcRun3_2022_realistic_v2-v2/NANOAODSIM',

#2022 postEE MC
# 'QCDPt50to80_postEE':'/QCD_PT-50to80_TuneCP5_13p6TeV_pythia8/Run3Summer22EENanoAODv11-126X_mcRun3_2022_realistic_postEE_v1-v1/NANOAODSIM',
# 'QCDPt80to120_postEE':'/QCD_PT-80to120_TuneCP5_13p6TeV_pythia8/Run3Summer22EENanoAODv11-126X_mcRun3_2022_realistic_postEE_v1-v1/NANOAODSIM',
# 'QCDPt120to170_postEE':'/QCD_PT-120to170_TuneCP5_13p6TeV_pythia8/Run3Summer22EENanoAODv11-126X_mcRun3_2022_realistic_postEE_v1_ext1-v1/NANOAODSIM',
# 'QCDPt170to300_postEE':'/QCD_PT-170to300_TuneCP5_13p6TeV_pythia8/Run3Summer22EENanoAODv11-126X_mcRun3_2022_realistic_postEE_v1_ext1-v1/NANOAODSIM',
# 'QCDPt300to470_postEE':'/QCD_PT-300to470_TuneCP5_13p6TeV_pythia8/Run3Summer22EENanoAODv11-126X_mcRun3_2022_realistic_postEE_v1_ext1-v1/NANOAODSIM',
# 'QCDPt470to600_postEE':'/QCD_PT-470to600_TuneCP5_13p6TeV_pythia8/Run3Summer22EENanoAODv11-126X_mcRun3_2022_realistic_postEE_v1_ext1-v1/NANOAODSIM',
# 'QCDPt600to800_postEE':'/QCD_PT-600to800_TuneCP5_13p6TeV_pythia8/Run3Summer22EENanoAODv11-126X_mcRun3_2022_realistic_postEE_v1_ext1-v1/NANOAODSIM',
# 'QCDPt800to1000_postEE':'/QCD_PT-800to1000_TuneCP5_13p6TeV_pythia8/Run3Summer22EENanoAODv11-126X_mcRun3_2022_realistic_postEE_v1_ext1-v1/NANOAODSIM',
# 'QCDPt1000to1400_postEE':'/QCD_PT-1000to1400_TuneCP5_13p6TeV_pythia8/Run3Summer22EENanoAODv11-126X_mcRun3_2022_realistic_postEE_v1_ext1-v1/NANOAODSIM',
# 'QCDPt1400to1800_postEE':'/QCD_PT-1400to1800_TuneCP5_13p6TeV_pythia8/Run3Summer22EENanoAODv11-126X_mcRun3_2022_realistic_postEE_v1_ext1-v1/NANOAODSIM',
# 'QCDPt1800to2400_postEE':'/QCD_PT-1800to2400_TuneCP5_13p6TeV_pythia8/Run3Summer22EENanoAODv11-126X_mcRun3_2022_realistic_postEE_v1_ext1-v1/NANOAODSIM',
# 'QCDPt2400to3200_postEE':'/QCD_PT-2400to3200_TuneCP5_13p6TeV_pythia8/Run3Summer22EENanoAODv11-126X_mcRun3_2022_realistic_postEE_v1_ext1-v1/NANOAODSIM',
# 'QCDPt3200toInf_postEE':'/QCD_PT-3200_TuneCP5_13p6TeV_pythia8/Run3Summer22EENanoAODv11-126X_mcRun3_2022_realistic_postEE_v1_ext1-v1/NANOAODSIM',
# 'TTto4Q_postEE':'/TTto4Q_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22EENanoAODv11-126X_mcRun3_2022_realistic_postEE_v1-v1/NANOAODSIM',
# 'TTtoLNu2Q_PostEE':'/TTtoLNu2Q_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22EENanoAODv11-126X_mcRun3_2022_realistic_postEE_v1-v1/NANOAODSIM',
# 'ggHto2B_Pt200ToInf_PostEE':'/GluGluHto2B_PT-200_M-125_TuneCP5_13p6TeV_powheg-minlo-pythia8/Run3Summer22EENanoAODv11-126X_mcRun3_2022_realistic_postEE_v1-v1/NANOAODSIM',
# 'VBFHto2B_PostEE':'/VBFHto2B_M-125_dipoleRecoilOn_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22EENanoAODv11-126X_mcRun3_2022_realistic_postEE_v1-v1/NANOAODSIM',
# 'WminusH_Hto2B_Wto2Q_PostEE':'/WminusH_Hto2B_Wto2Q_M-125_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22EENanoAODv11-126X_mcRun3_2022_realistic_postEE_v1-v1/NANOAODSIM',
# 'WplusH_Hto2B_Wto2Q_PostEE':'/WplusH_Hto2B_Wto2Q_M-125_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22EENanoAODv11-126X_mcRun3_2022_realistic_postEE_v1-v1/NANOAODSIM',
# 'ZH_Hto2B_Zto2Q_PostEE':'/ZH_Hto2B_Zto2Q_M-125_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22EENanoAODv11-126X_mcRun3_2022_realistic_postEE_v1-v1/NANOAODSIM',
# 'ggZH_Hto2B_Zto2Q_PostEE':'/ggZH_Hto2B_Zto2Q_M-125_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22EENanoAODv11-126X_mcRun3_2022_realistic_postEE_v1-v1/NANOAODSIM',
# 'ttH_Hto2B_PostEE':'/ttHto2B_M-125_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22EENanoAODv11-126X_mcRun3_2022_realistic_postEE_v1-v1/NANOAODSIM',
# 'WW_PostEE':'/WW_TuneCP5_13p6TeV_pythia8/Run3Summer22EENanoAODv11-126X_mcRun3_2022_realistic_postEE_v1-v1/NANOAODSIM',
# 'WZ_PostEE':'/WZ_TuneCP5_13p6TeV_pythia8/Run3Summer22EENanoAODv11-126X_mcRun3_2022_realistic_postEE_v1-v1/NANOAODSIM',
# 'ZZ_PostEE':'/ZZ_TuneCP5_13p6TeV_pythia8/Run3Summer22EENanoAODv11-126X_mcRun3_2022_realistic_postEE_v1-v2/NANOAODSIM',
# 'DYJetsToLL_M50ToInf_PostEE':'/DYJetsToLL_M-50_TuneCP5_13p6TeV-madgraphMLM-pythia8/Run3Summer22EENanoAODv11-forPOG_126X_mcRun3_2022_realistic_postEE_v1-v1/NANOAODSIM',
#'Wto2Q-3Jets_HT-400to600_PostEE':'/Wto2Q-3Jets_HT-400to600_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Summer22EENanoAODv11-126X_mcRun3_2022_realistic_postEE_v1-v2/NANOAODSIM',
#'Wto2Q-3Jets_HT-800_PostEE':'/Wto2Q-3Jets_HT-800_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Summer22EENanoAODv11-126X_mcRun3_2022_realistic_postEE_v1-v2/NANOAODSIM',
#"WtoLNu-2Jets_PostEE":"/WtoLNu-2Jets_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/Run3Summer22EENanoAODv11-126X_mcRun3_2022_realistic_postEE_v1-v1/NANOAODSIM",

'VBFHHto2B2G_CV_1_C2V_0_C3_1_postEE':'/VBFHHto2B2G_CV_1_C2V_0_C3_1_TuneCP5_13p6TeV_madgraph-pythia8/Run3Summer22EENanoAODv11-126X_mcRun3_2022_realistic_postEE_v1-v2/NANOAODSIM',
'VBFHHto2B2G_CV_1_C2V_1_C3_1_postEE':'/VBFHHto2B2G_CV_1_C2V_1_C3_1_TuneCP5_13p6TeV_madgraph-pythia8/Run3Summer22EENanoAODv11-126X_mcRun3_2022_realistic_postEE_v1-v2/NANOAODSIM',


####################################################################################################
#2023 Datasets
####################################################################################################   
# "JetMET0_2023A":"/JetMET0/Run2023A-PromptNanoAODv11p9_v2-v1/NANOAOD",
# "JetMET0_2023B":"/JetMET0/Run2023B-PromptNanoAODv11p9_v1-v1/NANOAOD",
# "JetMET0_2023C-v1":"/JetMET0/Run2023C-PromptNanoAODv11p9_v1-v1/NANOAOD",
# "JetMET0_2023C-v2":"/JetMET0/Run2023C-PromptNanoAODv12_v2-v2/NANOAOD",
# "JetMET0_2023C-v3":"/JetMET0/Run2023C-PromptNanoAODv12_v3-v1/NANOAOD",
# "JetMET0_2023C-v4":"/JetMET0/Run2023C-PromptNanoAODv12_v4-v1/NANOAOD",
# "JetMET0_2023D-v1":"/JetMET0/Run2023D-PromptReco-v1/NANOAOD",
# "JetMET0_2023D-v2":"/JetMET0/Run2023D-PromptReco-v2/NANOAOD",
# "JetMET1_2023A":"/JetMET1/Run2023A-PromptNanoAODv11p9_v2-v1/NANOAOD",
# "JetMET1_2023B":"/JetMET1/Run2023B-PromptNanoAODv11p9_v1-v1/NANOAOD",
# "JetMET1_2023C-v1":"/JetMET1/Run2023C-PromptNanoAODv11p9_v1-v1/NANOAOD",
# "JetMET1_2023C-v2":"/JetMET1/Run2023C-PromptNanoAODv12_v2-v4/NANOAOD",
# "JetMET1_2023C-v3":"/JetMET1/Run2023C-PromptNanoAODv12_v3-v1/NANOAOD",
# "JetMET1_2023C-v4":"/JetMET1/Run2023C-PromptNanoAODv12_v4-v1/NANOAOD",
# "JetMET1_2023D-v1":"/JetMET1/Run2023D-PromptReco-v1/NANOAOD",
# "JetMET1_2023D-v2":"/JetMET1/Run2023D-PromptReco-v2/NANOAOD",
# "Muon0_2023A":"/Muon0/Run2023A-PromptNanoAODv11p9_v2-v1/NANOAOD",
# "Muon0_2023B":"/Muon0/Run2023B-PromptNanoAODv11p9_v1-v2/NANOAOD",
# "Muon0_2023C-v1":"/Muon0/Run2023C-PromptNanoAODv11p9_v1-v1/NANOAOD",
# "Muon0_2023C-v2":"/Muon0/Run2023C-PromptNanoAODv12_v2-v2/NANOAOD",
# "Muon0_2023C-v3":"/Muon0/Run2023C-PromptNanoAODv12_v3-v1/NANOAOD",
# "Muon0_2023C-v4":"/Muon0/Run2023C-PromptNanoAODv12_v4-v1/NANOAOD",
# "Muon0_2023D-v1":"/Muon0/Run2023D-PromptReco-v1/NANOAOD",
# "Muon0_2023D-v2":"/Muon0/Run2023D-PromptReco-v2/NANOAOD",
# "Muon1_2023A":"/Muon1/Run2023A-PromptNanoAODv11p9_v2-v1/NANOAOD",
# "Muon1_2023B":"/Muon1/Run2023B-PromptNanoAODv11p9_v1-v2/NANOAOD",
# "Muon1_2023C-v1":"/Muon1/Run2023C-PromptNanoAODv11p9_v1-v1/NANOAOD",
# "Muon1_2023C-v2":"/Muon1/Run2023C-PromptNanoAODv12_v2-v2/NANOAOD",
# "Muon1_2023C-v3":"/Muon1/Run2023C-PromptNanoAODv12_v3-v1/NANOAOD",
# "Muon1_2023C-v4":"/Muon1/Run2023C-PromptNanoAODv12_v4-v1/NANOAOD",
# "Muon1_2023D-v1":"/Muon1/Run2023D-PromptReco-v1/NANOAOD",
# "Muon1_2023D-v2":"/Muon1/Run2023D-PromptReco-v2/NANOAOD",
# "EGamma0_Run2023A":"/EGamma0/Run2023A-PromptNanoAODv11p9_v2-v1/NANOAOD",
# "EGamma0_Run2023B":"/EGamma0/Run2023B-PromptNanoAODv11p9_v1-v1/NANOAOD",
# "EGamma0_Run2023C-v1":"/EGamma0/Run2023C-PromptNanoAODv11p9_v1-v1/NANOAOD",
# "EGamma0_Run2023C-v2":"/EGamma0/Run2023C-PromptNanoAODv12_v2-v2/NANOAOD",
# "EGamma0_Run2023C-v3":"/EGamma0/Run2023C-PromptNanoAODv12_v3-v1/NANOAOD",
# "EGamma0_Run2023C-v4":"/EGamma0/Run2023C-PromptNanoAODv12_v4-v1/NANOAOD",
# "EGamma0_Run2023D-v1":"/EGamma0/Run2023D-PromptReco-v1/NANOAOD",
# "EGamma0_Run2023D-v2":"/EGamma0/Run2023D-PromptReco-v2/NANOAOD",
# "EGamma1_Run2023A":"/EGamma1/Run2023A-PromptNanoAODv11p9_v2-v1/NANOAOD",
# "EGamma1_Run2023B":"/EGamma1/Run2023B-PromptNanoAODv11p9_v1-v1/NANOAOD",
# "EGamma1_Run2023C-v1":"/EGamma1/Run2023C-PromptNanoAODv11p9_v1-v1/NANOAOD",
# "EGamma1_Run2023C-v2":"/EGamma1/Run2023C-PromptNanoAODv12_v2-v2/NANOAOD",
# "EGamma1_Run2023C-v3":"/EGamma1/Run2023C-PromptNanoAODv12_v3-v1/NANOAOD",
# "EGamma1_Run2023C-v4":"/EGamma1/Run2023C-PromptNanoAODv12_v4-v1/NANOAOD",
# "EGamma1_Run2023D-v1":"/EGamma1/Run2023D-PromptReco-v1/NANOAOD",
# "EGamma1_Run2023D-v2":"/EGamma1/Run2023D-PromptReco-v2/NANOAOD",
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
