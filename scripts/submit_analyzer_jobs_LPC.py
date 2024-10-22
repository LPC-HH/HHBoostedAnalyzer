#!/usr/bin/python

import os
import datetime
import time
import subprocess
import glob
import sys
from collections import OrderedDict

option = 1
label = "option"+str(option)

analysis = "HHTo4BNtupler"
outputfile = "HHTo4BNtuple" + "_" + label

#analysis = "JetHTTriggerNtupler"
#outputfile = "JetHTTriggerNtuple" + "_" + label

#analysis = "MakeMCPileupDistribution"
#outputfile = "MCPileupDistribution" + "_" + label

cmsswReleaseVersion = "CMSSW_14_0_7"



outputDirectoryBase = "/store/user/lpcdihiggsboost/sixie/analyzer/"+analysis+"/ArmenVersion/"
filesPerJob = 1

datasetList = OrderedDict()

#2022 ntuples
datasetList["nano/run3/2022/EGamma_2022C.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/EGamma_2022D.list"] = [1, 1, "2022", "", 1]
datasetList['nano/run3/2022/JetHT_2022C.list'] = [1, 1, "2022", "", 1]
datasetList['nano/run3/2022/JetMET_2022C.list'] = [1, 1, "2022", "", 1]
datasetList['nano/run3/2022/JetMET_2022D.list'] = [1, 1, "2022", "", 1]
datasetList['nano/run3/2022/SingleMuon_2022C.list'] = [1, 1, "2022", "", 1]
datasetList['nano/run3/2022/Muon_2022C.list'] = [1, 1, "2022", "", 1]
datasetList['nano/run3/2022/Muon_2022D.list'] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/QCD-4Jets_HT-1000to1200_TuneCP5_13p6TeV_madgraphMLM-pythia8.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/QCD-4Jets_HT-100to200_TuneCP5_13p6TeV_madgraphMLM-pythia8.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/QCD-4Jets_HT-1200to1500_TuneCP5_13p6TeV_madgraphMLM-pythia8.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/QCD-4Jets_HT-1500to2000_TuneCP5_13p6TeV_madgraphMLM-pythia8.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/QCD-4Jets_HT-2000_TuneCP5_13p6TeV_madgraphMLM-pythia8.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/QCD-4Jets_HT-200to400_TuneCP5_13p6TeV_madgraphMLM-pythia8.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/QCD-4Jets_HT-400to600_TuneCP5_13p6TeV_madgraphMLM-pythia8.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/QCD-4Jets_HT-600to800_TuneCP5_13p6TeV_madgraphMLM-pythia8.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/QCD-4Jets_HT-800to1000_TuneCP5_13p6TeV_madgraphMLM-pythia8.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/TBbarQ_t-channel_4FS.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/TWminusto4Q.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/TWminustoLNu2Q.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/TWminustoLNu2Q_ext1.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/TbarBQ_t-channel_4FS.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/TbarWplusto4Q.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/TbarWplustoLNu2Q.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/TbarWplustoLNu2Q_ext1.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/TTto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/TTto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8_ext.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/TTto4Q_TuneCP5_13p6TeV_powheg-pythia8.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/TTto4Q_TuneCP5_13p6TeV_powheg-pythia8_ext.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/TTtoLNu2Q_TuneCP5_13p6TeV_powheg-pythia8.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/TTtoLNu2Q_TuneCP5_13p6TeV_powheg-pythia8_ext.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/DYto2L-2Jets_MLL-50_0J.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/DYto2L-2Jets_MLL-50_1J.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/DYto2L-2Jets_MLL-50_2J.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/Wto2Q-2Jets_PTQQ-100to200_1J.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/Wto2Q-2Jets_PTQQ-100to200_2J.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/Wto2Q-2Jets_PTQQ-200to400_1J.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/Wto2Q-2Jets_PTQQ-200to400_2J.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/Wto2Q-2Jets_PTQQ-400to600_1J.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/Wto2Q-2Jets_PTQQ-400to600_2J.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/Wto2Q-2Jets_PTQQ-600_1J.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/Wto2Q-2Jets_PTQQ-600_2J.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/WtoLNu-2Jets_0J.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/WtoLNu-2Jets_1J.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/WtoLNu-2Jets_2J.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/Zto2Q-2Jets_PTQQ-100to200_1J.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/Zto2Q-2Jets_PTQQ-100to200_2J.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/Zto2Q-2Jets_PTQQ-200to400_1J.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/Zto2Q-2Jets_PTQQ-200to400_2J.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/Zto2Q-2Jets_PTQQ-400to600_1J.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/Zto2Q-2Jets_PTQQ-400to600_2J.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/Zto2Q-2Jets_PTQQ-600_1J.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/Zto2Q-2Jets_PTQQ-600_2J.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/WW.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/WWto4Q-1Jets-4FS.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/WWtoLNu2Q-1Jets-4FS.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/WZ.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/WZto3LNu-1Jets-4FS.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/WZto4Q-1Jets-4FS.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/ZZ.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/ZZto2L2Q-1Jets.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/ZZto4L-1Jets.list"] = [1, 1, "2022", "", 1]




#2022EE ntuples
datasetList["nano/run3/2022/EGamma_2022E.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022/EGamma_2022F.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022/EGamma_2022G.list"] = [1, 1, "2022EE", "", 1]
datasetList['nano/run3/2022/JetMET_2022E.list'] = [1, 1, "2022EE", "", 1]
datasetList['nano/run3/2022/JetMET_2022F.list'] = [1, 1, "2022EE", "", 1]
datasetList['nano/run3/2022/JetMET_2022G.list'] = [1, 1, "2022EE", "", 1]
datasetList['nano/run3/2022/Muon_2022E.list'] = [1, 1, "2022EE", "", 1]
datasetList['nano/run3/2022/Muon_2022F.list'] = [1, 1, "2022EE", "", 1]
datasetList['nano/run3/2022/Muon_2022G.list'] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/QCD-4Jets_HT-1000to1200_TuneCP5_13p6TeV_madgraphMLM-pythia8.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/QCD-4Jets_HT-1200to1500_TuneCP5_13p6TeV_madgraphMLM-pythia8.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/QCD-4Jets_HT-1500to2000_TuneCP5_13p6TeV_madgraphMLM-pythia8.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/QCD-4Jets_HT-2000_TuneCP5_13p6TeV_madgraphMLM-pythia8.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/QCD-4Jets_HT-200to400_TuneCP5_13p6TeV_madgraphMLM-pythia8.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/QCD-4Jets_HT-400to600_TuneCP5_13p6TeV_madgraphMLM-pythia8.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/QCD-4Jets_HT-600to800_TuneCP5_13p6TeV_madgraphMLM-pythia8.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/QCD-4Jets_HT-800to1000_TuneCP5_13p6TeV_madgraphMLM-pythia8.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/TBbarQ_t-channel_4FS.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/TWminusto4Q.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/TWminustoLNu2Q.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/TWminustoLNu2Q_ext1.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/TbarBQ_t-channel_4FS.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/TbarWplusto4Q.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/TbarWplustoLNu2Q.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/TbarWplustoLNu2Q_ext1.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/TTto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/TTto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8_ext.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/TTto4Q_TuneCP5_13p6TeV_powheg-pythia8.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/TTto4Q_TuneCP5_13p6TeV_powheg-pythia8_ext.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/TTtoLNu2Q_TuneCP5_13p6TeV_powheg-pythia8.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/TTtoLNu2Q_TuneCP5_13p6TeV_powheg-pythia8_ext.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/DYto2L-2Jets_MLL-50_0J.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/DYto2L-2Jets_MLL-50_1J.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/DYto2L-2Jets_MLL-50_2J.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/Wto2Q-2Jets_PTQQ-100to200_1J.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/Wto2Q-2Jets_PTQQ-100to200_2J.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/Wto2Q-2Jets_PTQQ-200to400_1J.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/Wto2Q-2Jets_PTQQ-200to400_2J.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/Wto2Q-2Jets_PTQQ-400to600_1J.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/Wto2Q-2Jets_PTQQ-400to600_2J.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/Wto2Q-2Jets_PTQQ-600_1J.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/Wto2Q-2Jets_PTQQ-600_2J.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/WtoLNu-2Jets_0J.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/WtoLNu-2Jets_1J.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/WtoLNu-2Jets_2J.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/Zto2Q-2Jets_PTQQ-100to200_1J.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/Zto2Q-2Jets_PTQQ-100to200_2J.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/Zto2Q-2Jets_PTQQ-200to400_1J.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/Zto2Q-2Jets_PTQQ-200to400_2J.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/Zto2Q-2Jets_PTQQ-400to600_1J.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/Zto2Q-2Jets_PTQQ-400to600_2J.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/Zto2Q-2Jets_PTQQ-600_1J.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/Zto2Q-2Jets_PTQQ-600_2J.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/WW.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/WWto4Q-1Jets-4FS.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/WWtoLNu2Q-1Jets-4FS.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/WZ.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/WZto3LNu-1Jets-4FS.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/WZto4Q-1Jets-4FS.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/ZZ.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/ZZto2L2Q-1Jets.list"] = [1, 1, "2022EE", "", 1]
datasetList["nano/run3/2022EE/ZZto4L-1Jets.list"] = [1, 1, "2022EE", "", 1]


#2023 ntuples
datasetList['nano/run3/2023/JetMET_2023C_v1.list'] = [1, 1, "2023", "", 1]
datasetList['nano/run3/2023/JetMET_2023C_v2.list'] = [1, 1, "2023", "", 1]
datasetList['nano/run3/2023/JetMET_2023C_v3.list'] = [1, 1, "2023", "", 1]
datasetList['nano/run3/2023/JetMET_2023C_v4.list'] = [1, 1, "2023", "", 1]
datasetList['nano/run3/2023/EGamma_2023C_v1.list'] = [1, 1, "2023", "", 1]
datasetList['nano/run3/2023/EGamma_2023C_v2.list'] = [1, 1, "2023", "", 1]
datasetList['nano/run3/2023/EGamma_2023C_v3.list'] = [1, 1, "2023", "", 1]
datasetList['nano/run3/2023/EGamma_2023C_v4.list'] = [1, 1, "2023", "", 1]
datasetList['nano/run3/2023/Muon_2023C_v1.list'] = [1, 1, "2023", "", 1]
datasetList['nano/run3/2023/Muon_2023C_v2.list'] = [1, 1, "2023", "", 1]
datasetList['nano/run3/2023/Muon_2023C_v3.list'] = [1, 1, "2023", "", 1]
datasetList['nano/run3/2023/Muon_2023C_v4.list'] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/QCD-4Jets_HT-1000to1200.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/QCD-4Jets_HT-100to200.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/QCD-4Jets_HT-1200to1500.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/QCD-4Jets_HT-1500to2000.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/QCD-4Jets_HT-2000.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/QCD-4Jets_HT-200to400.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/QCD-4Jets_HT-400to600.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/QCD-4Jets_HT-40to70.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/QCD-4Jets_HT-600to800.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/QCD-4Jets_HT-70to100.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/QCD-4Jets_HT-800to1000.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/TBbarQ_t-channel_4FS.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/TWminusto4Q.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/TWminustoLNu2Q.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/TbarBQ_t-channel_4FS.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/TbarWplusto4Q.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/TTto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/TTto4Q_TuneCP5_13p6TeV_powheg-pythia8.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/TTtoLNu2Q_TuneCP5_13p6TeV_powheg-pythia8.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/DYto2L-2Jets_MLL-50_0J.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/DYto2L-2Jets_MLL-50_1J.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/DYto2L-2Jets_MLL-50_2J.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/Wto2Q-2Jets_PTQQ-100to200_1J.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/Wto2Q-2Jets_PTQQ-100to200_2J.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/Wto2Q-2Jets_PTQQ-200to400_1J.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/Wto2Q-2Jets_PTQQ-200to400_2J.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/Wto2Q-2Jets_PTQQ-400to600_1J.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/Wto2Q-2Jets_PTQQ-400to600_2J.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/Wto2Q-2Jets_PTQQ-600_1J.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/Wto2Q-2Jets_PTQQ-600_2J.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/WtoLNu-2Jets_0J.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/WtoLNu-2Jets_1J.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/WtoLNu-2Jets_2J.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/Zto2Q-2Jets_PTQQ-100to200_1J.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/Zto2Q-2Jets_PTQQ-100to200_2J.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/Zto2Q-2Jets_PTQQ-200to400_1J.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/Zto2Q-2Jets_PTQQ-200to400_2J.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/Zto2Q-2Jets_PTQQ-400to600_1J.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/Zto2Q-2Jets_PTQQ-400to600_2J.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/Zto2Q-2Jets_PTQQ-600_1J.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/Zto2Q-2Jets_PTQQ-600_2J.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/WW.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/WZ.list"] = [1, 1, "2023", "", 1]
datasetList["nano/run3/2023/ZZ.list"] = [1, 1, "2023", "", 1]



#2023BPix ntuples
datasetList['nano/run3/2023/JetMET_2023D_v1.list'] = [1, 1, "2023BPix", "", 1]
datasetList['nano/run3/2023/JetMET_2023D_v2.list'] = [1, 1, "2023BPix", "", 1]
datasetList['nano/run3/2023/EGamma_2023D_v1.list'] = [1, 1, "2023BPix", "", 1]
datasetList['nano/run3/2023/EGamma_2023D_v2.list'] = [1, 1, "2023BPix", "", 1]
datasetList['nano/run3/2023/Muon_2023D_v1.list'] = [1, 1, "2023BPix", "", 1]
datasetList['nano/run3/2023/Muon_2023D_v2.list'] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/QCD-4Jets_HT-1000to1200.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/QCD-4Jets_HT-100to200.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/QCD-4Jets_HT-1200to1500.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/QCD-4Jets_HT-1500to2000.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/QCD-4Jets_HT-2000.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/QCD-4Jets_HT-200to400.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/QCD-4Jets_HT-400to600.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/QCD-4Jets_HT-40to70.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/QCD-4Jets_HT-600to800.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/QCD-4Jets_HT-70to100.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/QCD-4Jets_HT-800to1000.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/TBbarQ_t-channel_4FS.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/TWminusto4Q.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/TWminustoLNu2Q.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/TbarBQ_t-channel_4FS.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/TbarWplusto4Q.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/TbarWplustoLNu2Q.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/TTto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/TTto4Q_TuneCP5_13p6TeV_powheg-pythia8.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/TTtoLNu2Q_TuneCP5_13p6TeV_powheg-pythia8.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/DYto2L-2Jets_MLL-50_0J.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/DYto2L-2Jets_MLL-50_1J.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/DYto2L-2Jets_MLL-50_2J.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/Wto2Q-2Jets_PTQQ-100to200_1J.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/Wto2Q-2Jets_PTQQ-100to200_2J.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/Wto2Q-2Jets_PTQQ-200to400_1J.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/Wto2Q-2Jets_PTQQ-200to400_2J.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/Wto2Q-2Jets_PTQQ-400to600_1J.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/Wto2Q-2Jets_PTQQ-400to600_2J.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/Wto2Q-2Jets_PTQQ-600_1J.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/Wto2Q-2Jets_PTQQ-600_2J.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/WtoLNu-2Jets_0J.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/WtoLNu-2Jets_1J.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/WtoLNu-2Jets_2J.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/Zto2Q-2Jets_PTQQ-100to200_1J.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/Zto2Q-2Jets_PTQQ-100to200_2J.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/Zto2Q-2Jets_PTQQ-200to400_1J.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/Zto2Q-2Jets_PTQQ-200to400_2J.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/Zto2Q-2Jets_PTQQ-400to600_1J.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/Zto2Q-2Jets_PTQQ-400to600_2J.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/Zto2Q-2Jets_PTQQ-600_1J.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/Zto2Q-2Jets_PTQQ-600_2J.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/WW.list"] = [1, 1, "2023BPix", "", 1]
datasetList["nano/run3/2023BPix/WZ.list"] = [1, 1, "2023BPix", "", 1]


#2024 ntuples
datasetList['nano/run3/2024/JetMET_2024B.list'] = [1, 1, "2024", "", 1]
datasetList['nano/run3/2024/JetMET_2024C.list'] = [1, 1, "2024", "", 1]
datasetList['nano/run3/2024/JetMET_2024D.list'] = [1, 1, "2024", "", 1]
datasetList['nano/run3/2024/JetMET_2024E-v1.list'] = [1, 1, "2024", "", 1]
datasetList['nano/run3/2024/JetMET_2024E-v2.list'] = [1, 1, "2024", "", 1]
datasetList['nano/run3/2024/JetMET_2024F.list'] = [1, 1, "2024", "", 1]
datasetList['nano/run3/2024/JetMET_2024G.list'] = [1, 1, "2024", "", 1]
datasetList['nano/run3/2024/JetMET_2024H.list'] = [1, 1, "2024", "", 1]
datasetList['nano/run3/2024/EGamma_2024B.list'] = [1, 1, "2024", "", 1]
datasetList['nano/run3/2024/EGamma_2024C.list'] = [1, 1, "2024", "", 1]
datasetList['nano/run3/2024/EGamma_2024D.list'] = [1, 1, "2024", "", 1]
datasetList['nano/run3/2024/EGamma_2024E-v1.list'] = [1, 1, "2024", "", 1]
datasetList['nano/run3/2024/EGamma_2024E-v2.list'] = [1, 1, "2024", "", 1]
datasetList['nano/run3/2024/EGamma_2024F.list'] = [1, 1, "2024", "", 1]
datasetList['nano/run3/2024/EGamma_2024G.list'] = [1, 1, "2024", "", 1]
datasetList['nano/run3/2024/EGamma_2024H.list'] = [1, 1, "2024", "", 1]
datasetList['nano/run3/2024/Muon_2024B.list'] = [1, 1, "2024", "", 1]
datasetList['nano/run3/2024/Muon_2024C.list'] = [1, 1, "2024", "", 1]
datasetList['nano/run3/2024/Muon_2024D.list'] = [1, 1, "2024", "", 1]
datasetList['nano/run3/2024/Muon_2024E-v1.list'] = [1, 1, "2024", "", 1]
datasetList['nano/run3/2024/Muon_2024E-v2.list'] = [1, 1, "2024", "", 1]
datasetList['nano/run3/2024/Muon_2024F.list'] = [1, 1, "2024", "", 1]
datasetList['nano/run3/2024/Muon_2024G.list'] = [1, 1, "2024", "", 1]
datasetList['nano/run3/2024/Muon_2024H.list'] = [1, 1, "2024", "", 1]




CMSSW_BASE_DIR = os.getenv('CMSSW_BASE')
Analyzer_DIR = str(CMSSW_BASE_DIR) +'/src/HHBoostedAnalyzer/'


#create directory for condor jobs

for listfile in datasetList.keys():

    datasetName = listfile.replace(".list","")
    print("Preparing analyzer workflow for dataset :" + datasetName + "\n")
    if not os.path.exists(Analyzer_DIR+"/list/" + listfile):
        print ("listfile: " + listfile + " does not exist. skipping.")
        continue

    outputDirectory = outputDirectoryBase + datasetName + "/"
    tmpListFile = open(Analyzer_DIR + "/list/" + listfile,"r")

    year = datasetList[listfile][2]
    sampleName = datasetList[listfile][3]
    numberOfJobsPerFile = datasetList[listfile][4]

    #####################################
    #Job Splitting
    #####################################
    isData = "no"
    if (datasetList[listfile][0] == 1): 
        isData = "yes"
    filesPerJob = datasetList[listfile][1]
    tmpJobFileCount = 0
    nJobs = numberOfJobsPerFile

    if os.path.exists(Analyzer_DIR+"/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/" + "input_list_" + str(nJobs) + ".txt"):
        print ("Warning: condor directory " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + " is not empty. Skipping.")
        continue
        
    #create condor directories
    os.system("mkdir -p " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName )
    os.system("mkdir -p " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/log/")
    os.system("mkdir -p " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/out/")
    os.system("mkdir -p " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/err/")

    tmpOutputListFile = open( Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/" + "input_list_" + str(nJobs/numberOfJobsPerFile) + ".txt","w")
    for line in tmpListFile:
                
        #open list file for new job
        if tmpJobFileCount >= filesPerJob:
            tmpOutputListFile.close()
            tmpJobFileCount = 0
            nJobs = nJobs + numberOfJobsPerFile
            tmpOutputListFile = open( Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/" + "input_list_" + str(nJobs/numberOfJobsPerFile) + ".txt","w")
          
        #write input file into job list file
        tmpOutputListFile.write(line)
        tmpJobFileCount += 1

    tmpOutputListFile.close()    
    os.system("cd " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/; tar czf input_list.tgz input_list_*.txt")

    ###################################################
    #Copy code tarball, run script, and executable
    ###################################################
    #os.system("cd " + Analyzer_DIR + "; tar vczf " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/code.tgz " + " include/ src/ app/ Makefile" )
    os.system("cp " + Analyzer_DIR + "/scripts/run_job_LPC.sh " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/")
    os.system("cp " + Analyzer_DIR + "Run" + analysis + " " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/")
    os.system("mkdir -p " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/HHBoostedAnalyzer/data/")    
    os.system("mkdir -p " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/HHBoostedAnalyzer/data/PileupWeights/")
    os.system("cp " + Analyzer_DIR + "/data/PileupWeights/PileupWeights.root " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/HHBoostedAnalyzer/data/PileupWeights/")
    #os.system("mkdir -p " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/HHBoostedAnalyzer/data/JEC/Summer16_07Aug2017_V11_MC/")
    #os.system("cp " + Analyzer_DIR + "/data/JEC/Summer16_07Aug2017_V11_MC/Summer16_07Aug2017_V11_MC_Uncertainty_AK8PFPuppi.txt " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/HHBoostedAnalyzer/data/JEC/Summer16_07Aug2017_V11_MC/")
    #os.system("mkdir -p " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/HHBoostedAnalyzer/data/JEC/Fall17_17Nov2017_V32_MC/")
    #os.system("cp " + Analyzer_DIR + "/data/JEC/Fall17_17Nov2017_V32_MC/Fall17_17Nov2017_V32_MC_Uncertainty_AK8PFPuppi.txt " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/HHBoostedAnalyzer/data/JEC/Fall17_17Nov2017_V32_MC/")
    #os.system("mkdir -p " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/HHBoostedAnalyzer/data/JEC/Autumn18_V19_MC/")
    #os.system("cp " + Analyzer_DIR + "/data/JEC/Autumn18_V19_MC/Autumn18_V19_MC_Uncertainty_AK8PFPuppi.txt " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/HHBoostedAnalyzer/data/JEC/Autumn18_V19_MC/")


    #####################################
    #Create Condor JDL file
    #####################################
    tmpCondorJDLFile = open(Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/task.jdl","w+")
    tmpCondorJDLFileTemplate = """
Universe  = vanilla
Executable = ./run_job_LPC.sh
"""
    tmpCondorJDLFile.write(tmpCondorJDLFileTemplate)
    tmpCondorJDLFile.write("Arguments = " + analysis + " " + str(isData) + " " + str(option) + " " + "$(I) " + str(numberOfJobsPerFile) + " " + outputfile + " " + outputDirectory + " " + cmsswReleaseVersion + " " + year + " " + sampleName + "\n")

    tmpCondorJDLFileTemplate = """
Log = log/job.$(Cluster).$(Process).log
Output = out/job.$(Cluster).$(Process).out
Error = err/job.$(Cluster).$(Process).err
x509userproxy = $ENV(X509_USER_PROXY)
"""
    tmpCondorJDLFile.write(tmpCondorJDLFileTemplate)
    tmpCondorJDLFile.write(
        "transfer_input_files = " 
        + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/run_job_LPC.sh, " 
        + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/input_list.tgz, " 
        + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/Run" + analysis + ", "        
        #+ Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/HHBoostedAnalyzer/data/PileupWeights/PileupWeights.root, " 
        #+ Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/HHBoostedAnalyzer/data/JEC/Summer16_07Aug2017_V11_MC/Summer16_07Aug2017_V11_MC_Uncertainty_AK8PFPuppi.txt, " 
        #+ Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/HHBoostedAnalyzer/data/JEC/Fall17_17Nov2017_V32_MC/Fall17_17Nov2017_V32_MC_Uncertainty_AK8PFPuppi.txt, " 
        #+ Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/HHBoostedAnalyzer/data/JEC/Autumn18_V19_MC/Autumn18_V19_MC_Uncertainty_AK8PFPuppi.txt " + "\n"
    )

    tmpCondorJDLFileTemplate = """
should_transfer_files = YES
when_to_transfer_output = ON_EXIT

# Resources request
"""
    tmpCondorJDLFile.write(tmpCondorJDLFileTemplate)
    tmpCondorJDLFile.write("RequestMemory = 2000 \n")

    tmpCondorJDLFileTemplate = """

# Jobs selection
Queue I from (
"""

    tmpCondorJDLFile.write(tmpCondorJDLFileTemplate)
    for i in range(1,nJobs+1):
        tmpCondorJDLFile.write(str(i)+"\n")
    tmpCondorJDLFile.write(")\n")
    tmpCondorJDLFile.close()





