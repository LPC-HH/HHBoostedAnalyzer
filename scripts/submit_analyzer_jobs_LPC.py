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
outputDirectoryBase = "/eos/uscms//store/user/lpcbacon/sixie/analyzer/"+analysis+"/"
filesPerJob = 2

datasetList = OrderedDict()
#datasetList['LPC/GluGluToHHTo4B_node_SM_13TeV-madgraph_correctedcfg.list'] = [0]
datasetList['LPC/ttHTobb_M125_TuneCP5_13TeV-powheg-pythia8.list'] = [0]
datasetList['LPC/ttHJetTobb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8.list'] = [0]
datasetList['LPC/ggZH_HToBB_ZToQQ_M125_13TeV_powheg_pythia8.list'] = [0]
datasetList['LPC/ZH_HToBB_ZToQQ_M125_13TeV_powheg_pythia8.list'] = [0]
datasetList['LPC/WplusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8.list'] = [0]
datasetList['LPC/WminusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8.list'] = [0]
datasetList['LPC/VBFHiggs0PHToBB_M125_13TeV_JHUGenV7011_pythia8.list'] = [0]
datasetList['LPC/TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8.list'] = [0]
datasetList['LPC/GluGluHToBB_M125_TuneCP5_13TeV-powheg-pythia8.list'] = [0]
datasetList['LPC/GluGluHToBB_M125_13TeV_amcatnloFXFX_pythia8.list'] = [0]



#create directory for condor jobs

for listfile in datasetList.keys():

    datasetName = listfile.replace(".list","")
    print "Preparing analyzer workflow for dataset :" + datasetName + "\n"
    if not os.path.exists("list/" + listfile):
        print "listfile: " + listfile + " does not exist. skipping."
        continue

    outputDirectory = outputDirectoryBase + datasetName + "/"
    tmpListFile = open("list/" + listfile,"r")



    #####################################
    #Job Splitting
    #####################################
    tmpJobFileCount = 0
    nJobs = 1

    if os.path.exists("condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/" + "input_list_" + str(nJobs) + ".txt"):
        print "Warning: condor directory condor/analyzer_" + analysis + "_" + label + "/" + datasetName + " is not empty. Skipping."
        continue
        
    os.system("mkdir -p condor/analyzer_" + analysis + "_" + label + "/" + datasetName )
    tmpOutputListFile = open( "condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/" + "input_list_" + str(nJobs) + ".txt","w")
    for line in tmpListFile:
                
        #open list file for new job
        if tmpJobFileCount >= filesPerJob:
            tmpOutputListFile.close()
            tmpJobFileCount = 0
            nJobs = nJobs + 1           
            tmpOutputListFile = open( "condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/" + "input_list_" + str(nJobs) + ".txt","w")
          
        #write input file into job list file
        tmpOutputListFile.write(line)
        tmpJobFileCount += 1

    os.system("cd condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/; tar czf input_list.tgz input_list_*.txt")

    #####################################
    #Copy run script and executable
    #####################################
    os.system("cp scripts/run_job_LPC.sh condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/")
    os.system("cp Run" + analysis + " condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/")

    #####################################
    #Create Condor JDL file
    #####################################
    tmpCondorJDLFile = open("condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/task.jdl","w+")
    tmpCondorJDLFileTemplate = """
Universe  = vanilla
Executable = ./run_job_LPC.sh
"""
    tmpCondorJDLFile.write(tmpCondorJDLFileTemplate)
    tmpCondorJDLFile.write("Arguments = " + analysis + " " + str(datasetList[listfile][0]) + " " + str(option) + " " + "$(I) " + outputfile + " " + outputDirectory + " " + cmsswReleaseVersion + " " + "\n")

    tmpCondorJDLFileTemplate = """
Log = log/job.$(Cluster).$(Process).log
Output = out/job.$(Cluster).$(Process).out
Error = err/job.$(Cluster).$(Process).err
x509userproxy = $ENV(X509_USER_PROXY)
"""
    tmpCondorJDLFile.write(tmpCondorJDLFileTemplate)
    tmpCondorJDLFile.write("transfer_input_files = ./run_job_LPC.sh ./input_list.tgz ./Run" + analysis + " " + "\n")

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





