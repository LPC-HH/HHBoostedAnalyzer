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

'ggHH_cHHH_1_TSG':'/ggHH_cHHH_1/lpcdihiggsboost-crab_PrivateProduction_Summer22_DR_step4_MINIAODSIM_ggHH_cHHH_1_batch1_v2-00000000000000000000000000000000/USER',


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
    #command = "dasgoclient -query=\"file dataset=" + datasets[processName] + " \" -json > tmpOutput.json"
    print (command)
    os.system(command)

    jsonFile = open("tmpOutput.json","r")
    data = json.load(jsonFile)

    for p in data:
        blockName = p['file'][0]['block.name']
        fileName = p['file'][0]['name']
        outputFile.write("root://cmsxrootd.fnal.gov/"+fileName+"\n")
