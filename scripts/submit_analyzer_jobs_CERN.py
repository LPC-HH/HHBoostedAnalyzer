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
filesPerJob = 2

datasetList = OrderedDict()
datasetList['LPC/GluGluToHHTo4B_node_SM_13TeV-madgraph_correctedcfg.list'] = [0]
#datasetList['LPC/data.list'] = [1]

#create directory for condor jobs

for listfile in datasetList.keys():

    datasetName = listfile.replace(".list","")
    print "Preparing analyzer workflow for dataset :" + datasetName + "\n"
    if not os.path.exists("list/" + listfile):
        print "listfile: " + listfile + " does not exist. skipping."
        continue

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
    tmpOutputListFile = open( "condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/" + "input_file_list_" + str(nJobs) + ".txt","w")
    for line in tmpListFile:
                
        #open list file for new job
        if tmpJobFileCount >= filesPerJob:
            tmpOutputListFile.close()
            tmpJobFileCount = 0
            nJobs = nJobs + 1           
            tmpOutputListFile = open( "condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/" + "input_file_list_" + str(nJobs) + ".txt","w")
          
        #write input file into job list file
        tmpOutputListFile.write(line)
        tmpJobFileCount += 1

    #####################################
    #Create Condor JDL file
    #####################################
    tmpCondorJDLFile = open("condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/task.jdl","w+")
    tmpCondorJDLFileTemplate = """
Universe  = vanilla
Executable = ../run_job.sh
Arguments = $(I)
Log = log/job.$(Cluster).$(Process).log
Output = out/job.$(Cluster).$(Process).out
Error = err/job.$(Cluster).$(Process).err
x509userproxy = $ENV(X509_USER_PROXY)
transfer_input_files = ../run_reco_ntupler.sh
should_transfer_files = YES
when_to_transfer_output = ON_EXIT

# Resources request
"""
    tmpCondorJDLFile.write(tmpCondorJDLFileTemplate)
    tmpCondorJDLFile.write("requirements = (OpSysAndVer =?= \"SLCern6\")\n")
    tmpCondorJDLFile.write("RequestCpus = 1 \n")
    tmpCondorJDLFile.write("RequestMemory = 2000 \n")
    tmpCondorJDLFile.write("+JobFlavour = \"" + queueType + "\"")
    
    tmpCondorJDLFileTemplate = """

# Jobs selection
Queue I from (
"""

    tmpCondorJDLFile.write(tmpCondorJDLFileTemplate)
    for i in range(1,nJobs+1):
        tmpCondorJDLFile.write(str(i)+"\n")
    tmpCondorJDLFile.write(")\n")
    tmpCondorJDLFile.close()





