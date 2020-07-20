#!/usr/bin/python

import os
import datetime
import time
import subprocess
import glob
import sys
import json


datasets = {
'GluGluToHHTo4B_node_SM':'/GluGluToHHTo4B_node_SM_13TeV-madgraph_correctedcfg/slaurila-NanoTuples-30Apr2020_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_v14-v1-6f7c69ffdbb83072d4913e5f3cf0008f/USER',
'VBFHHTo4B_CV_1_C2V_1_C3_1':'/VBFHHTo4B_CV_1_C2V_1_C3_1_13TeV-madgraph/slaurila-NanoTuples-30Apr2020_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_v14-v3-6f7c69ffdbb83072d4913e5f3cf0008f/USER',
'TTToHadronic_TuneCP5_13TeV-powheg-pythia8':'/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/coli-NanoTuples-30Apr2020_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_v14-ext1-v1-6f7c69ffdbb83072d4913e5f3cf0008f/USER',
'TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8':'/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/coli-NanoTuples-30Apr2020_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_v14-ext1-v1-6f7c69ffdbb83072d4913e5f3cf0008f/USER',
'TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8':'/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/coli-NanoTuples-30Apr2020_RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_v14-v1-6f7c69ffdbb83072d4913e5f3cf0008f/USER',
'QCD_HT200to300_TuneCP5_13TeV-madgraph-pythia8':'/QCD_HT200to300_TuneCP5_13TeV-madgraph-pythia8/coli-NanoTuples-30Apr2020_RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_v14-v2-6f7c69ffdbb83072d4913e5f3cf0008f/USER',
'QCD_HT300to500_TuneCP5_13TeV-madgraph-pythia8':'/QCD_HT300to500_TuneCP5_13TeV-madgraph-pythia8/coli-NanoTuples-30Apr2020_RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_v14-v1-6f7c69ffdbb83072d4913e5f3cf0008f/USER',
'QCD_HT500to700_TuneCP5_13TeV-madgraph-pythia8':'/QCD_HT500to700_TuneCP5_13TeV-madgraph-pythia8/coli-NanoTuples-30Apr2020_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_v14-v2-6f7c69ffdbb83072d4913e5f3cf0008f/USER',
'QCD_HT700to1000_TuneCP5_13TeV-madgraph-pythia8':'/QCD_HT700to1000_TuneCP5_13TeV-madgraph-pythia8/coli-NanoTuples-30Apr2020_RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_v14-v2-6f7c69ffdbb83072d4913e5f3cf0008f/USER',
'QCD_HT1000to1500_TuneCP5_13TeV-madgraph-pythia8':'/QCD_HT1000to1500_TuneCP5_13TeV-madgraph-pythia8/coli-NanoTuples-30Apr2020_RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_v14-v1-6f7c69ffdbb83072d4913e5f3cf0008f/USER',
'QCD_HT1500to2000_TuneCP5_13TeV-madgraph-pythia8':'/QCD_HT1500to2000_TuneCP5_13TeV-madgraph-pythia8/coli-NanoTuples-30Apr2020_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_v14-v2-6f7c69ffdbb83072d4913e5f3cf0008f/USER',
'QCD_HT2000toInf_TuneCP5_13TeV-madgraph-pythia8':'/QCD_HT2000toInf_TuneCP5_13TeV-madgraph-pythia8/coli-NanoTuples-30Apr2020_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_v14-v2-6f7c69ffdbb83072d4913e5f3cf0008f/USER',
'GluGluHToBB_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8':'/GluGluHToBB_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8/coli-NanoTuples-30Apr2020_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_v14-v1-6f7c69ffdbb83072d4913e5f3cf0008f/USER',
'VBFHToBB_M-125_13TeV_powheg_pythia8':'/VBFHToBB_M-125_13TeV_powheg_pythia8_weightfix/coli-NanoTuples-30Apr2020_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_v14-v1-6f7c69ffdbb83072d4913e5f3cf0008f/USER',
'WminusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8':'/WminusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8/slaurila-NanoTuples-30Apr2020_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_v14-v1-6f7c69ffdbb83072d4913e5f3cf0008f/USER',
'WplusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8':'/WplusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8/slaurila-NanoTuples-30Apr2020_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_v14-v1-6f7c69ffdbb83072d4913e5f3cf0008f/USER',
'ZH_HToBB_ZToQQ_M125_13TeV_powheg_pythia8':'/ZH_HToBB_ZToQQ_M125_13TeV_powheg_pythia8/slaurila-NanoTuples-30Apr2020_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_v14-v1-6f7c69ffdbb83072d4913e5f3cf0008f/USER',
'ttHTobb_M125_TuneCP5_13TeV-powheg-pythia8':'/ttHTobb_M125_TuneCP5_13TeV-powheg-pythia8/slaurila-NanoTuples-30Apr2020_RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_v14-v1-6f7c69ffdbb83072d4913e5f3cf0008f/USER',
'JetHT_2017B':'/JetHT/hqu-NanoTuples-30Apr2020_Run2017B-31Mar2018-v1-b2e5aecd7d318124ef1b7f48a4318be4/USER',
'JetHT_2017C':'/JetHT/hqu-NanoTuples-30Apr2020_Run2017C-31Mar2018-v1-b2e5aecd7d318124ef1b7f48a4318be4/USER',
'JetHT_2017D':'/JetHT/hqu-NanoTuples-30Apr2020_Run2017D-31Mar2018-v1-b2e5aecd7d318124ef1b7f48a4318be4/USER',
'JetHT_2017E':'/JetHT/hqu-NanoTuples-30Apr2020_Run2017E-31Mar2018-v1-b2e5aecd7d318124ef1b7f48a4318be4/USER',
'JetHT_2017F':'/JetHT/hqu-NanoTuples-30Apr2020_Run2017F-31Mar2018-v1-b2e5aecd7d318124ef1b7f48a4318be4/USER',
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
    

    

