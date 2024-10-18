#!/usr/bin/python

import os
import datetime
import time
import subprocess
import glob
import sys
from collections import OrderedDict

option = 10
label = "option"+str(option)

analysis = "HHTo4BNtupler"
outputfile = "HHTo4BNtuple" + "_" + label

#analysis = "JetHTTriggerNtupler"
#outputfile = "JetHTTriggerNtuple" + "_" + label

#analysis = "MakeMCPileupDistribution"
#outputfile = "MCPileupDistribution" + "_" + label

cmsswReleaseVersion = "CMSSW_14_0_7"



outputDirectoryBase = "/store/user/lpcdihiggsboost/sixie/analyzer/"+analysis+"/"ArmenVersion/""
filesPerJob = 1

datasetList = OrderedDict()

#2022 ntuples
datasetList["nano/run3/2022/EGamma_2022C.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/EGamma_2022D.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/EGamma_2022E.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/EGamma_2022F.list"] = [1, 1, "2022", "", 1]
datasetList["nano/run3/2022/EGamma_2022G.list"] = [1, 1, "2022", "", 1]
datasetList['nano/run3/2022/JetHT_2022C.list'] = [1, 1, "2022", "", 1]
datasetList['nano/run3/2022/JetMET_2022C.list'] = [1, 1, "2022", "", 1]
datasetList['nano/run3/2022/JetMET_2022D.list'] = [1, 1, "2022", "", 1]
datasetList['nano/run3/2022/JetMET_2022E.list'] = [1, 1, "2022", "", 1]
datasetList['nano/run3/2022/JetMET_2022F.list'] = [1, 1, "2022", "", 1]
datasetList['nano/run3/2022/JetMET_2022G.list'] = [1, 1, "2022", "", 1]
datasetList['nano/run3/2022/SingleMuon_2022C.list'] = [1, 1, "2022", "", 1]
datasetList['nano/run3/2022/Muon_2022C.list'] = [1, 1, "2022", "", 1]
datasetList['nano/run3/2022/Muon_2022D.list'] = [1, 1, "2022", "", 1]
datasetList['nano/run3/2022/Muon_2022E.list'] = [1, 1, "2022", "", 1]
datasetList['nano/run3/2022/Muon_2022F.list'] = [1, 1, "2022", "", 1]
datasetList['nano/run3/2022/Muon_2022G.list'] = [1, 1, "2022", "", 1]


#2023 ntuples
datasetList['nano/run3/2023/JetMET_2023C_v1.list'] = [1, 1, "2023", "", 1]
datasetList['nano/run3/2023/JetMET_2023C_v2.list'] = [1, 1, "2023", "", 1]
datasetList['nano/run3/2023/JetMET_2023C_v3.list'] = [1, 1, "2023", "", 1]
datasetList['nano/run3/2023/JetMET_2023C_v4.list'] = [1, 1, "2023", "", 1]
datasetList['nano/run3/2023/JetMET_2023D_v1.list'] = [1, 1, "2023", "", 1]
datasetList['nano/run3/2023/JetMET_2023D_v2.list'] = [1, 1, "2023", "", 1]
datasetList['nano/run3/2023/EGamma_2023C_v1.list'] = [1, 1, "2023", "", 1]
datasetList['nano/run3/2023/EGamma_2023C_v2.list'] = [1, 1, "2023", "", 1]
datasetList['nano/run3/2023/EGamma_2023C_v3.list'] = [1, 1, "2023", "", 1]
datasetList['nano/run3/2023/EGamma_2023C_v4.list'] = [1, 1, "2023", "", 1]
datasetList['nano/run3/2023/EGamma_2023D_v1.list'] = [1, 1, "2023", "", 1]
datasetList['nano/run3/2023/EGamma_2023D_v2.list'] = [1, 1, "2023", "", 1]
datasetList['nano/run3/2023/Muon_2023C_v1.list'] = [1, 1, "2023", "", 1]
datasetList['nano/run3/2023/Muon_2023C_v2.list'] = [1, 1, "2023", "", 1]
datasetList['nano/run3/2023/Muon_2023C_v3.list'] = [1, 1, "2023", "", 1]
datasetList['nano/run3/2023/Muon_2023C_v4.list'] = [1, 1, "2023", "", 1]
datasetList['nano/run3/2023/Muon_2023D_v1.list'] = [1, 1, "2023", "", 1]
datasetList['nano/run3/2023/Muon_2023D_v2.list'] = [1, 1, "2023", "", 1]

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
        print "Warning: condor directory " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + " is not empty. Skipping."
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





