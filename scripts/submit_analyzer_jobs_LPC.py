#!/usr/bin/python

import os
import datetime
import time
import subprocess
import glob
import sys
from collections import OrderedDict

queueType = "longlunch"

analysis = "HHTo4BNtupler"
option = 1
cmsswReleaseVersion = "CMSSW_10_6_5"
label = "v1"
outputfile = "HHTo4BNtuple" + "_" + label
outputDirectoryBase = "/store/user/lpcbacon/sixie/analyzer/"+analysis+"/"
#filesPerJob = 2

datasetList = OrderedDict()
datasetList['LPC/GluGluToHHTo4B_node_SM_13TeV-madgraph_correctedcfg.list'] = [0, 2]
datasetList['LPC/ttHTobb_M125_TuneCP5_13TeV-powheg-pythia8.list'] = [0, 2]
datasetList['LPC/ttHJetTobb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8.list'] = [0, 2]
datasetList['LPC/ggZH_HToBB_ZToQQ_M125_13TeV_powheg_pythia8.list'] = [0, 2]
datasetList['LPC/ZH_HToBB_ZToQQ_M125_13TeV_powheg_pythia8.list'] = [0, 2]
datasetList['LPC/WplusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8.list'] = [0, 2]
datasetList['LPC/WminusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8.list'] = [0, 2]
datasetList['LPC/VBFHiggs0PHToBB_M125_13TeV_JHUGenV7011_pythia8.list'] = [0, 2]
datasetList['LPC/TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8.list'] = [0, 2]
datasetList['LPC/GluGluHToBB_M125_TuneCP5_13TeV-powheg-pythia8.list'] = [0, 2]
datasetList['LPC/GluGluHToBB_M125_13TeV_amcatnloFXFX_pythia8.list'] = [0, 2]
datasetList['LPC/data_Run2017B-09Aug2019_UL2017_v1.list.list'] = [0, 1]
datasetList['LPC/data_Run2017C-09Aug2019_UL2017_v1.list.list'] = [0, 1]
datasetList['LPC/data_Run2017D-09Aug2019_UL2017_v1.list.list'] = [0, 1]
datasetList['LPC/data_Run2017E-09Aug2019_UL2017_v1.list.list'] = [0, 1]
datasetList['LPC/data_Run2017F-09Aug2019_UL2017_v1.list.list'] = [0, 1]

CMSSW_BASE_DIR = os.getenv('CMSSW_BASE')
Analyzer_DIR = CMSSW_BASE_DIR+"/src/HHBoostedAnalyzer/"

#create directory for condor jobs

for listfile in datasetList.keys():

    datasetName = listfile.replace(".list","")
    print "Preparing analyzer workflow for dataset :" + datasetName + "\n"
    if not os.path.exists(Analyzer_DIR+"/list/" + listfile):
        print "listfile: " + listfile + " does not exist. skipping."
        continue

    outputDirectory = outputDirectoryBase + datasetName + "/"
    tmpListFile = open(Analyzer_DIR + "/list/" + listfile,"r")



    #####################################
    #Job Splitting
    #####################################
    isData = datasetList[listfile][0]
    filesPerJob = datasetList[listfile][1]
    tmpJobFileCount = 0
    nJobs = 1

    if os.path.exists(Analyzer_DIR+"/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/" + "input_list_" + str(nJobs) + ".txt"):
        print "Warning: condor directory " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + " is not empty. Skipping."
        continue
        
    #create condor directories
    os.system("mkdir -p " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName )
    os.system("mkdir -p " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/log/")
    os.system("mkdir -p " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/out/")
    os.system("mkdir -p " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/err/")

    tmpOutputListFile = open( Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/" + "input_list_" + str(nJobs) + ".txt","w")
    for line in tmpListFile:
                
        #open list file for new job
        if tmpJobFileCount >= filesPerJob:
            tmpOutputListFile.close()
            tmpJobFileCount = 0
            nJobs = nJobs + 1           
            tmpOutputListFile = open( Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/" + "input_list_" + str(nJobs) + ".txt","w")
          
        #write input file into job list file
        tmpOutputListFile.write(line)
        tmpJobFileCount += 1

    os.system("cd " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/; tar czf input_list.tgz input_list_*.txt")

    #####################################
    #Copy run script and executable
    #####################################
    os.system("cp " + Analyzer_DIR + "/scripts/run_job_LPC.sh " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/")
    os.system("cp " + Analyzer_DIR + "Run" + analysis + " " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/")

    #####################################
    #Create Condor JDL file
    #####################################
    tmpCondorJDLFile = open(Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/task.jdl","w+")
    tmpCondorJDLFileTemplate = """
Universe  = vanilla
Executable = ./run_job_LPC.sh
"""
    tmpCondorJDLFile.write(tmpCondorJDLFileTemplate)
    tmpCondorJDLFile.write("Arguments = " + analysis + " " + str(isData) + " " + str(option) + " " + "$(I) " + outputfile + " " + outputDirectory + " " + cmsswReleaseVersion + " " + "\n")

    tmpCondorJDLFileTemplate = """
Log = log/job.$(Cluster).$(Process).log
Output = out/job.$(Cluster).$(Process).out
Error = err/job.$(Cluster).$(Process).err
x509userproxy = $ENV(X509_USER_PROXY)
"""
    tmpCondorJDLFile.write(tmpCondorJDLFileTemplate)
    tmpCondorJDLFile.write("transfer_input_files = " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/run_job_LPC.sh, " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/input_list.tgz, " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/Run" + analysis + " " + "\n")

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





