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
# 'JetHT_2016B-ver2':'/JetHT/hqu-NanoTuples-30Apr2020_Run2016B-17Jul2018_ver2-v2-b0abb2002249db2b4f7fad7e7c1c0c68/USER',
# 'JetHT_2016C':'/JetHT/hqu-NanoTuples-30Apr2020_Run2016C-17Jul2018-v1-b0abb2002249db2b4f7fad7e7c1c0c68/USER',
# 'JetHT_2016D':'/JetHT/hqu-NanoTuples-30Apr2020_Run2016D-17Jul2018-v1-b0abb2002249db2b4f7fad7e7c1c0c68/USER',
# 'JetHT_2016E':'/JetHT/hqu-NanoTuples-30Apr2020_Run2016E-17Jul2018-v1-b0abb2002249db2b4f7fad7e7c1c0c68/USER',
# 'JetHT_2016F':'/JetHT/hqu-NanoTuples-30Apr2020_Run2016F-17Jul2018-v1-b0abb2002249db2b4f7fad7e7c1c0c68/USER',
# 'JetHT_2016G':'/JetHT/hqu-NanoTuples-30Apr2020_Run2016G-17Jul2018-v1-b0abb2002249db2b4f7fad7e7c1c0c68/USER',
# 'JetHT_2016H':'/JetHT/hqu-NanoTuples-30Apr2020_Run2016H-17Jul2018-v1-b0abb2002249db2b4f7fad7e7c1c0c68/USER',
# 'GluGluToHHTo4B_node_cHHH5_TuneCUETP8M1_PSWeights_13TeV-powheg-pythia8':'/GluGluToHHTo4B_node_cHHH5_TuneCUETP8M1_PSWeights_13TeV-powheg-pythia8/slaurila-NanoTuples-30Apr2020_RunIISummer16MiniAODv3-PUMoriond17_94X_v3-v1-44377faedc969dcf531f5eb3e501054b/USER',
# 'GluGluToHHTo4B_node_cHHH2p45_TuneCUETP8M1_PSWeights_13TeV-powheg-pythia8':'/GluGluToHHTo4B_node_cHHH2p45_TuneCUETP8M1_PSWeights_13TeV-powheg-pythia8/slaurila-NanoTuples-30Apr2020_RunIISummer16MiniAODv3-PUMoriond17_94X_v3-v1-44377faedc969dcf531f5eb3e501054b/USER',
# 'GluGluToHHTo4B_node_cHHH1_TuneCUETP8M1_PSWeights_13TeV-powheg-pythia8':'/GluGluToHHTo4B_node_cHHH1_TuneCUETP8M1_PSWeights_13TeV-powheg-pythia8/slaurila-NanoTuples-30Apr2020_RunIISummer16MiniAODv3-PUMoriond17_94X_v3-v1-44377faedc969dcf531f5eb3e501054b/USER',
# 'GluGluToHHTo4B_node_cHHH0_TuneCUETP8M1_PSWeights_13TeV-powheg-pythia8':'/GluGluToHHTo4B_node_cHHH0_TuneCUETP8M1_PSWeights_13TeV-powheg-pythia8/slaurila-NanoTuples-30Apr2020_RunIISummer16MiniAODv3-PUMoriond17_94X_v3-v1-44377faedc969dcf531f5eb3e501054b/USER',
# 'GluGluToHHTo4B_node_SM_13TeV-madgraph':'/GluGluToHHTo4B_node_SM_13TeV-madgraph/slaurila-NanoTuples-30Apr2020_RunIISummer16MiniAODv3-PUMoriond17_94X_v3-v2-44377faedc969dcf531f5eb3e501054b/USER',
# 'VBFHHTo4B_CV_1_C2V_1_C3_1_13TeV-madgraph':'/VBFHHTo4B_CV_1_C2V_1_C3_1_13TeV-madgraph/slaurila-NanoTuples-30Apr2020_RunIISummer16MiniAODv3-PUMoriond17_94X_v3-v2-44377faedc969dcf531f5eb3e501054b/USER',
# 'QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8':'/QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/bortigno-NanoTuples-30Apr2020_RunIISummer16MiniAODv3-PUMoriond17_94X_v3-v2-44377faedc969dcf531f5eb3e501054b/USER',
# 'QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-ext1':'/QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/bortigno-NanoTuples-30Apr2020_RunIISummer16MiniAODv3-PUMoriond17_94X_v3-ext1-v2-44377faedc969dcf531f5eb3e501054b/USER',
# 'QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8':'/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/bortigno-NanoTuples-30Apr2020_RunIISummer16MiniAODv3-PUMoriond17_94X_v3-v2-44377faedc969dcf531f5eb3e501054b/USER',
# 'QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-ext1':'/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/bortigno-NanoTuples-30Apr2020_RunIISummer16MiniAODv3-PUMoriond17_94X_v3-ext1-v2-44377faedc969dcf531f5eb3e501054b/USER',
# 'QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8':'/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/bortigno-NanoTuples-30Apr2020_RunIISummer16MiniAODv3-PUMoriond17_94X_v3-v2-44377faedc969dcf531f5eb3e501054b/USER',
# 'QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-ext1':'/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/bortigno-NanoTuples-30Apr2020_RunIISummer16MiniAODv3-PUMoriond17_94X_v3-ext1-v2-44377faedc969dcf531f5eb3e501054b/USER',
# 'QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8':'/QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/bortigno-NanoTuples-30Apr2020_RunIISummer16MiniAODv3-PUMoriond17_94X_v3-v2-44377faedc969dcf531f5eb3e501054b/USER',
# 'QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-ext1':'/QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/bortigno-NanoTuples-30Apr2020_RunIISummer16MiniAODv3-PUMoriond17_94X_v3-ext1-v2-44377faedc969dcf531f5eb3e501054b/USER',
# 'QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8':'/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/bortigno-NanoTuples-30Apr2020_RunIISummer16MiniAODv3-PUMoriond17_94X_v3-v2-44377faedc969dcf531f5eb3e501054b/USER',
# 'QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-ext1':'/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/bortigno-NanoTuples-30Apr2020_RunIISummer16MiniAODv3-PUMoriond17_94X_v3-ext1-v2-44377faedc969dcf531f5eb3e501054b/USER',
# 'QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8':'/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/bortigno-NanoTuples-30Apr2020_RunIISummer16MiniAODv3-PUMoriond17_94X_v3-v2-44377faedc969dcf531f5eb3e501054b/USER',
# 'QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-ext1':'/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/bortigno-NanoTuples-30Apr2020_RunIISummer16MiniAODv3-PUMoriond17_94X_v3-ext1-v2-44377faedc969dcf531f5eb3e501054b/USER',
# 'QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8':'/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/bortigno-NanoTuples-30Apr2020_RunIISummer16MiniAODv3-PUMoriond17_94X_v3-v2-44377faedc969dcf531f5eb3e501054b/USER',
# 'QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-ext1':'/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/bortigno-NanoTuples-30Apr2020_RunIISummer16MiniAODv3-PUMoriond17_94X_v3-ext1-v2-44377faedc969dcf531f5eb3e501054b/USER',
# 'TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8':'/TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8/bortigno-NanoTuples-30Apr2020_RunIISummer16MiniAODv3-PUMoriond17_94X_v3-v1-44377faedc969dcf531f5eb3e501054b/USER',
# 'TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8':'/TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8/bortigno-NanoTuples-30Apr2020_RunIISummer16MiniAODv3-PUMoriond17_94X_v3-v1-44377faedc969dcf531f5eb3e501054b/USER',
# 'TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8':'/TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8/bortigno-NanoTuples-30Apr2020_RunIISummer16MiniAODv3-PUMoriond17_94X_v3-v1-44377faedc969dcf531f5eb3e501054b/USER',
# 'GluGluHToBB_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8':'/GluGluHToBB_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/bortigno-NanoTuples-30Apr2020_RunIISummer16MiniAODv3-PUMoriond17_94X_v3-v2-44377faedc969dcf531f5eb3e501054b/USER',
# 'VBFHToBB_M-125_13TeV_powheg_pythia8_weightfix':'/VBFHToBB_M-125_13TeV_powheg_pythia8_weightfix/bortigno-NanoTuples-30Apr2020_RunIISummer16MiniAODv3-PUMoriond17_94X_v3-v1-44377faedc969dcf531f5eb3e501054b/USER',
# 'VBFHToBB_M-125_13TeV_powheg_pythia8_weightfix-ext1':'/VBFHToBB_M-125_13TeV_powheg_pythia8_weightfix/bortigno-NanoTuples-30Apr2020_RunIISummer16MiniAODv3-PUMoriond17_94X_v3-ext1-v1-44377faedc969dcf531f5eb3e501054b/USER',
# #WH, HToBB WToQQ is missing
# 'ZH_HToBB_ZToQQ_M125_13TeV_powheg_pythia8':'/ZH_HToBB_ZToQQ_M125_13TeV_powheg_pythia8/slaurila-NanoTuples-30Apr2020_RunIISummer16MiniAODv3-PUMoriond17_94X_v3-v1-44377faedc969dcf531f5eb3e501054b/USER',
# 'ttHTobb_M125_13TeV_powheg_pythia8':'/ttHTobb_M125_13TeV_powheg_pythia8/slaurila-NanoTuples-30Apr2020_RunIISummer16MiniAODv3-PUMoriond17_94X_v3-v2-44377faedc969dcf531f5eb3e501054b/USER',


# ####################################################################################################
# #2017 Datasets
# ####################################################################################################   
# 'JetHT_2017B':'/JetHT/hqu-NanoTuples-30Apr2020_Run2017B-31Mar2018-v1-b2e5aecd7d318124ef1b7f48a4318be4/USER',
# 'JetHT_2017C':'/JetHT/hqu-NanoTuples-30Apr2020_Run2017C-31Mar2018-v1-b2e5aecd7d318124ef1b7f48a4318be4/USER',
# 'JetHT_2017D':'/JetHT/hqu-NanoTuples-30Apr2020_Run2017D-31Mar2018-v1-b2e5aecd7d318124ef1b7f48a4318be4/USER',
# 'JetHT_2017E':'/JetHT/hqu-NanoTuples-30Apr2020_Run2017E-31Mar2018-v1-b2e5aecd7d318124ef1b7f48a4318be4/USER',
# 'JetHT_2017F':'/JetHT/hqu-NanoTuples-30Apr2020_Run2017F-31Mar2018-v1-b2e5aecd7d318124ef1b7f48a4318be4/USER',
# 'GluGluToHHTo4B_node_SM':'/GluGluToHHTo4B_node_SM_13TeV-madgraph_correctedcfg/slaurila-NanoTuples-30Apr2020_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_v14-v1-6f7c69ffdbb83072d4913e5f3cf0008f/USER',
# 'VBFHHTo4B_CV_1_C2V_1_C3_1':'/VBFHHTo4B_CV_1_C2V_1_C3_1_13TeV-madgraph/slaurila-NanoTuples-30Apr2020_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_v14-v3-6f7c69ffdbb83072d4913e5f3cf0008f/USER',
# 'TTToHadronic_TuneCP5_13TeV-powheg-pythia8':'/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/coli-NanoTuples-30Apr2020_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_v14-ext1-v1-6f7c69ffdbb83072d4913e5f3cf0008f/USER',
# 'TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8':'/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/coli-NanoTuples-30Apr2020_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_v14-ext1-v1-6f7c69ffdbb83072d4913e5f3cf0008f/USER',
# 'TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8':'/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/coli-NanoTuples-30Apr2020_RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_v14-v1-6f7c69ffdbb83072d4913e5f3cf0008f/USER',
# 'QCD_HT200to300_TuneCP5_13TeV-madgraph-pythia8':'/QCD_HT200to300_TuneCP5_13TeV-madgraph-pythia8/coli-NanoTuples-30Apr2020_RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_v14-v2-6f7c69ffdbb83072d4913e5f3cf0008f/USER',
# 'QCD_HT300to500_TuneCP5_13TeV-madgraph-pythia8':'/QCD_HT300to500_TuneCP5_13TeV-madgraph-pythia8/coli-NanoTuples-30Apr2020_RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_v14-v1-6f7c69ffdbb83072d4913e5f3cf0008f/USER',
# 'QCD_HT500to700_TuneCP5_13TeV-madgraph-pythia8':'/QCD_HT500to700_TuneCP5_13TeV-madgraph-pythia8/coli-NanoTuples-30Apr2020_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_v14-v2-6f7c69ffdbb83072d4913e5f3cf0008f/USER',
# 'QCD_HT700to1000_TuneCP5_13TeV-madgraph-pythia8':'/QCD_HT700to1000_TuneCP5_13TeV-madgraph-pythia8/coli-NanoTuples-30Apr2020_RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_v14-v2-6f7c69ffdbb83072d4913e5f3cf0008f/USER',
# 'QCD_HT1000to1500_TuneCP5_13TeV-madgraph-pythia8':'/QCD_HT1000to1500_TuneCP5_13TeV-madgraph-pythia8/coli-NanoTuples-30Apr2020_RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_v14-v1-6f7c69ffdbb83072d4913e5f3cf0008f/USER',
# 'QCD_HT1500to2000_TuneCP5_13TeV-madgraph-pythia8':'/QCD_HT1500to2000_TuneCP5_13TeV-madgraph-pythia8/coli-NanoTuples-30Apr2020_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_v14-v2-6f7c69ffdbb83072d4913e5f3cf0008f/USER',
# 'QCD_HT2000toInf_TuneCP5_13TeV-madgraph-pythia8':'/QCD_HT2000toInf_TuneCP5_13TeV-madgraph-pythia8/coli-NanoTuples-30Apr2020_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_v14-v2-6f7c69ffdbb83072d4913e5f3cf0008f/USER',
# 'GluGluHToBB_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8':'/GluGluHToBB_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/coli-NanoTuples-30Apr2020_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_v14-v1-6f7c69ffdbb83072d4913e5f3cf0008f/USER',
# 'VBFHToBB_M-125_13TeV_powheg_pythia8':'/VBFHToBB_M-125_13TeV_powheg_pythia8_weightfix/coli-NanoTuples-30Apr2020_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_v14-v1-6f7c69ffdbb83072d4913e5f3cf0008f/USER',
# 'WminusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8':'/WminusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8/slaurila-NanoTuples-30Apr2020_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_v14-v1-6f7c69ffdbb83072d4913e5f3cf0008f/USER',
# 'WplusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8':'/WplusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8/slaurila-NanoTuples-30Apr2020_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_v14-v1-6f7c69ffdbb83072d4913e5f3cf0008f/USER',
# 'ZH_HToBB_ZToQQ_M125_13TeV_powheg_pythia8':'/ZH_HToBB_ZToQQ_M125_13TeV_powheg_pythia8/slaurila-NanoTuples-30Apr2020_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_v14-v1-6f7c69ffdbb83072d4913e5f3cf0008f/USER',
# 'ttHTobb_M125_TuneCP5_13TeV-powheg-pythia8':'/ttHTobb_M125_TuneCP5_13TeV-powheg-pythia8/slaurila-NanoTuples-30Apr2020_RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_v14-v1-6f7c69ffdbb83072d4913e5f3cf0008f/USER',


####################################################################################################
#2018 Datasets
####################################################################################################   
'JetHT_2018A':'/JetHT/hqu-NanoTuples-30Apr2020_Run2018A-17Sep2018-v1-51ac09360ac5a9839ebad8683652478b/USER',
'JetHT_2018B':'/JetHT/hqu-NanoTuples-30Apr2020_Run2018B-17Sep2018-v1-51ac09360ac5a9839ebad8683652478b/USER',
'JetHT_2018C':'/JetHT/hqu-NanoTuples-30Apr2020_Run2018C-17Sep2018-v1-51ac09360ac5a9839ebad8683652478b/USER',
'JetHT_2018D':'/JetHT/hqu-NanoTuples-30Apr2020_Run2018D-PromptReco-v2-99b92eeae6e347dd2619a79a606c4aaa/USER',
'GluGluToHHTo4B_node_SM_TuneCP5_PSWeights_13TeV-madgraph-pythia8':'/GluGluToHHTo4B_node_SM_TuneCP5_PSWeights_13TeV-madgraph-pythia8/slaurila-NanoTuples-30Apr2020_RunIIAutumn18MiniAOD-102X_v15-v1-27c3bb388d728791ecf339ca1f755fce/USER',
'VBFHHTo4B_CV_1_C2V_1_C3_1_TuneCP5_PSWeights_13TeV-madgraph-pythia8':'/VBFHHTo4B_CV_1_C2V_1_C3_1_TuneCP5_PSWeights_13TeV-madgraph-pythia8/slaurila-NanoTuples-30Apr2020_RunIIAutumn18MiniAOD-102X_v15-v1-27c3bb388d728791ecf339ca1f755fce/USER',
'QCD_HT200to300_TuneCP5_13TeV-madgraphMLM-pythia8':'/QCD_HT200to300_TuneCP5_13TeV-madgraphMLM-pythia8/gouskos-NanoTuples-30Apr2020_RunIIAutumn18MiniAOD-102X_v15-v1-27c3bb388d728791ecf339ca1f755fce/USER',
'QCD_HT300to500_TuneCP5_13TeV-madgraphMLM-pythia8':'/QCD_HT300to500_TuneCP5_13TeV-madgraphMLM-pythia8/gouskos-NanoTuples-30Apr2020_RunIIAutumn18MiniAOD-102X_v15-v1-27c3bb388d728791ecf339ca1f755fce/USER',
'QCD_HT500to700_TuneCP5_13TeV-madgraphMLM-pythia8':'/QCD_HT500to700_TuneCP5_13TeV-madgraphMLM-pythia8/gouskos-NanoTuples-30Apr2020_RunIIAutumn18MiniAOD-102X_v15-v1-27c3bb388d728791ecf339ca1f755fce/USER',
'QCD_HT700to1000_TuneCP5_13TeV-madgraphMLM-pythia8':'/QCD_HT700to1000_TuneCP5_13TeV-madgraphMLM-pythia8/gouskos-NanoTuples-30Apr2020_RunIIAutumn18MiniAOD-102X_v15-v1-27c3bb388d728791ecf339ca1f755fce/USER',
'QCD_HT1000to1500_TuneCP5_13TeV-madgraphMLM-pythia8':'/QCD_HT1000to1500_TuneCP5_13TeV-madgraphMLM-pythia8/gouskos-NanoTuples-30Apr2020_RunIIAutumn18MiniAOD-102X_v15-v1-27c3bb388d728791ecf339ca1f755fce/USER',
'QCD_HT1500to2000_TuneCP5_13TeV-madgraphMLM-pythia8':'/QCD_HT1500to2000_TuneCP5_13TeV-madgraphMLM-pythia8/gouskos-NanoTuples-30Apr2020_RunIIAutumn18MiniAOD-102X_v15-v1-27c3bb388d728791ecf339ca1f755fce/USER',
'QCD_HT2000toInf_TuneCP5_13TeV-madgraphMLM-pythia8':'/QCD_HT2000toInf_TuneCP5_13TeV-madgraphMLM-pythia8/gouskos-NanoTuples-30Apr2020_RunIIAutumn18MiniAOD-102X_v15-v1-27c3bb388d728791ecf339ca1f755fce/USER',
'TTToHadronic_TuneCP5_13TeV-powheg-pythia8':'/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/gouskos-NanoTuples-30Apr2020_RunIIAutumn18MiniAOD-102X_v15-v1-27c3bb388d728791ecf339ca1f755fce/USER',
'TTToHadronic_TuneCP5_13TeV-powheg-pythia8-ext2':'/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/gouskos-NanoTuples-30Apr2020_RunIIAutumn18MiniAOD-102X_v15-ext2-v2-27c3bb388d728791ecf339ca1f755fce/USER',
'TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8':'/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/gouskos-NanoTuples-30Apr2020_RunIIAutumn18MiniAOD-102X_v15-v1-27c3bb388d728791ecf339ca1f755fce/USER',
'TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8-ext3':'/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/gouskos-NanoTuples-30Apr2020_RunIIAutumn18MiniAOD-102X_v15-ext3-v2-27c3bb388d728791ecf339ca1f755fce/USER',
'TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8':'/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/gouskos-NanoTuples-30Apr2020_RunIIAutumn18MiniAOD-102X_v15-v1-27c3bb388d728791ecf339ca1f755fce/USER',
'GluGluHToBB_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8':'/GluGluHToBB_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/gouskos-NanoTuples-30Apr2020_RunIIAutumn18MiniAOD-102X_v15-v1-27c3bb388d728791ecf339ca1f755fce/USER',
'VBFHToBB_M-125_13TeV_powheg_pythia8_weightfix':'/VBFHToBB_M-125_13TeV_powheg_pythia8_weightfix/gouskos-NanoTuples-30Apr2020_RunIIAutumn18MiniAOD-102X_v15-v1-27c3bb388d728791ecf339ca1f755fce/USER',
'WminusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8':'/WminusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8/slaurila-NanoTuples-30Apr2020_RunIIAutumn18MiniAOD-102X_v15-v1-27c3bb388d728791ecf339ca1f755fce/USER',
'WplusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8':'/WplusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8/slaurila-NanoTuples-30Apr2020_RunIIAutumn18MiniAOD-102X_v15-v1-27c3bb388d728791ecf339ca1f755fce/USER',
'ZH_HToBB_ZToQQ_M125_13TeV_powheg_pythia8':'/ZH_HToBB_ZToQQ_M125_13TeV_powheg_pythia8/slaurila-NanoTuples-30Apr2020_RunIIAutumn18MiniAOD-102X_v15-v1-27c3bb388d728791ecf339ca1f755fce/USER',
'ttHTobb_M125_TuneCP5_13TeV-powheg-pythia8':'/ttHTobb_M125_TuneCP5_13TeV-powheg-pythia8/slaurila-NanoTuples-30Apr2020_RunIIAutumn18MiniAOD-102X_v15-v2-27c3bb388d728791ecf339ca1f755fce/USER',
}

# if (len(sys.argv) -1 < 1):
#     print "Error. Not enough arguments provided.\n"
#     print "Usage: python printFilesInGivenBlocks.py\n"
#     exit()

#datasetName = sys.argv[1]


for processName in datasets.keys():

    outputFile = open(processName+".list","w")
    print processName
    command = "dasgoclient -query=\"file dataset=" + datasets[processName] + " instance=prod/phys03 \" -json > tmpOutput.json"
    os.system(command)

    jsonFile = open("tmpOutput.json","r")
    data = json.load(jsonFile)

    for p in data:
        blockName = p['file'][0]['block.name']
        fileName = p['file'][0]['name']
        outputFile.write("root://cmsxrootd.fnal.gov/"+fileName+"\n")
    

    
