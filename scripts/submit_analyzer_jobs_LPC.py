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
option = 2
cmsswReleaseVersion = "CMSSW_10_6_5"
label = "v4"
outputfile = "HHTo4BNtuple" + "_" + label
outputDirectoryBase = "/store/user/lpcbacon/sixie/analyzer/"+analysis+"/"+label+"/"
#filesPerJob = 2

datasetList = OrderedDict()
# datasetList['LPC/GluGluToHHTo4B_node_SM_13TeV-madgraph_correctedcfg.list'] = [0, 2]
# datasetList['LPC/ttHTobb_M125_TuneCP5_13TeV-powheg-pythia8.list'] = [0, 2]
# datasetList['LPC/ttHJetTobb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8.list'] = [0, 2]
# datasetList['LPC/ggZH_HToBB_ZToQQ_M125_13TeV_powheg_pythia8.list'] = [0, 2]
# datasetList['LPC/ZH_HToBB_ZToQQ_M125_13TeV_powheg_pythia8.list'] = [0, 2]
# datasetList['LPC/WplusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8.list'] = [0, 2]
# datasetList['LPC/WminusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8.list'] = [0, 2]
# datasetList['LPC/VBFHiggs0PHToBB_M125_13TeV_JHUGenV7011_pythia8.list'] = [0, 2]
# datasetList['LPC/TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8.list'] = [0, 2]
# datasetList['LPC/GluGluHToBB_M125_TuneCP5_13TeV-powheg-pythia8.list'] = [0, 2]
# datasetList['LPC/GluGluHToBB_M125_13TeV_amcatnloFXFX_pythia8.list'] = [0, 2]
# datasetList['LPC/qcd_ht_1000to1500.list'] = [0, 2]
# datasetList['LPC/qcd_ht_2000toInf.list'] = [0, 2]
# datasetList['LPC/qcd_ht_50to100.list'] = [0, 2]
# datasetList['LPC/qcd_ht_100to200.list'] = [0, 2]
# datasetList['LPC/qcd_ht_300to500.list'] = [0, 2]
# datasetList['LPC/qcd_ht_700to1000.list'] = [0, 2]
# datasetList['LPC/qcd_ht_1500to2000.list'] = [0, 2]
# datasetList['LPC/qcd_ht_500to700.list'] = [0, 2]
# datasetList['LPC/data_Run2017B-09Aug2019_UL2017_v1.list'] = [1, 1]
# datasetList['LPC/data_Run2017C-09Aug2019_UL2017_v1.list'] = [1, 1]
# datasetList['LPC/data_Run2017D-09Aug2019_UL2017_v1.list'] = [1, 1]
# datasetList['LPC/data_Run2017E-09Aug2019_UL2017_v1.list'] = [1, 1]
# datasetList['LPC/data_Run2017F-09Aug2019_UL2017_v1.list'] = [1, 1]


# #2016 hqu ntuples
# datasetList['nano/v1/2016/JetHT_2016B-ver2.list'] = [1, 1]
# datasetList['nano/v1/2016/JetHT_2016C.list'] = [1, 1]
# datasetList['nano/v1/2016/JetHT_2016D.list'] = [1, 1]
# datasetList['nano/v1/2016/JetHT_2016E.list'] = [1, 1]
# datasetList['nano/v1/2016/JetHT_2016F.list'] = [1, 1]
# datasetList['nano/v1/2016/JetHT_2016G.list'] = [1, 1]
# datasetList['nano/v1/2016/JetHT_2016H.list'] = [1, 1]
# datasetList['nano/v1/2016/GluGluHToBB_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8.list'] = [0, 2]
# datasetList['nano/v1/2016/GluGluToHHTo4B_node_SM_13TeV-madgraph.list'] = [0, 2]
# datasetList['nano/v1/2016/GluGluToHHTo4B_node_cHHH0_TuneCUETP8M1_PSWeights_13TeV-powheg-pythia8.list'] = [0, 2]
# datasetList['nano/v1/2016/GluGluToHHTo4B_node_cHHH1_TuneCUETP8M1_PSWeights_13TeV-powheg-pythia8.list'] = [0, 2]
# datasetList['nano/v1/2016/GluGluToHHTo4B_node_cHHH2p45_TuneCUETP8M1_PSWeights_13TeV-powheg-pythia8.list'] = [0, 2]
# datasetList['nano/v1/2016/GluGluToHHTo4B_node_cHHH5_TuneCUETP8M1_PSWeights_13TeV-powheg-pythia8.list'] = [0, 2]
# datasetList['nano/v1/2016/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-ext1.list'] = [0, 2]
# datasetList['nano/v1/2016/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.list'] = [0, 2]
# datasetList['nano/v1/2016/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-ext1.list'] = [0, 2]
# datasetList['nano/v1/2016/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.list'] = [0, 2]
# datasetList['nano/v1/2016/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-ext1.list'] = [0, 2]
# datasetList['nano/v1/2016/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.list'] = [0, 2]
# datasetList['nano/v1/2016/QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-ext1.list'] = [0, 2]
# datasetList['nano/v1/2016/QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.list'] = [0, 2]
# datasetList['nano/v1/2016/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-ext1.list'] = [0, 2]
# datasetList['nano/v1/2016/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.list'] = [0, 2]
# datasetList['nano/v1/2016/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-ext1.list'] = [0, 2]
# datasetList['nano/v1/2016/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.list'] = [0, 2]
# datasetList['nano/v1/2016/QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8-ext1.list'] = [0, 2]
# datasetList['nano/v1/2016/QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.list'] = [0, 2]
# datasetList['nano/v1/2016/TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8.list'] = [0, 2]
# datasetList['nano/v1/2016/TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8.list'] = [0, 2]
# datasetList['nano/v1/2016/TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8.list'] = [0, 2]
# datasetList['nano/v1/2016/VBFHHTo4B_CV_1_C2V_1_C3_1_13TeV-madgraph.list'] = [0, 2]
# datasetList['nano/v1/2016/VBFHToBB_M-125_13TeV_powheg_pythia8_weightfix-ext1.list'] = [0, 2]
# datasetList['nano/v1/2016/VBFHToBB_M-125_13TeV_powheg_pythia8_weightfix.list'] = [0, 2]
# datasetList['nano/v1/2016/ZH_HToBB_ZToQQ_M125_13TeV_powheg_pythia8.list'] = [0, 2]
# datasetList['nano/v1/2016/ttHTobb_M125_13TeV_powheg_pythia8.list'] = [0, 2]



#2017 hqu ntuples
datasetList['nano/v1/2017/GluGluHToBB_M-125_13TeV_powheg_MINLO_NNLOPS_pythia8.list'] = [0, 2]
datasetList['nano/v1/2017/GluGluToHHTo4B_node_SM.list'] = [0, 2]
datasetList['nano/v1/2017/QCD_HT1000to1500_TuneCP5_13TeV-madgraph-pythia8.list'] = [0, 2]
datasetList['nano/v1/2017/QCD_HT1500to2000_TuneCP5_13TeV-madgraph-pythia8.list'] = [0, 2]
datasetList['nano/v1/2017/QCD_HT2000toInf_TuneCP5_13TeV-madgraph-pythia8.list'] = [0, 2]
datasetList['nano/v1/2017/QCD_HT200to300_TuneCP5_13TeV-madgraph-pythia8.list'] = [0, 2]
datasetList['nano/v1/2017/QCD_HT300to500_TuneCP5_13TeV-madgraph-pythia8.list'] = [0, 2]
datasetList['nano/v1/2017/QCD_HT500to700_TuneCP5_13TeV-madgraph-pythia8.list'] = [0, 2]
datasetList['nano/v1/2017/QCD_HT700to1000_TuneCP5_13TeV-madgraph-pythia8.list'] = [0, 2]
datasetList['nano/v1/2017/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8.list'] = [0, 2]
datasetList['nano/v1/2017/TTToHadronic_TuneCP5_13TeV-powheg-pythia8.list'] = [0, 2]
datasetList['nano/v1/2017/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8.list'] = [0, 2]
datasetList['nano/v1/2017/VBFHHTo4B_CV_1_C2V_1_C3_1.list'] = [0, 2]
datasetList['nano/v1/2017/VBFHToBB_M-125_13TeV_powheg_pythia8.list'] = [0, 2]
datasetList['nano/v1/2017/WminusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8.list'] = [0, 2]
datasetList['nano/v1/2017/WplusH_HToBB_WToQQ_M125_13TeV_powheg_pythia8.list'] = [0, 2]
datasetList['nano/v1/2017/ZH_HToBB_ZToQQ_M125_13TeV_powheg_pythia8.list'] = [0, 2]
datasetList['nano/v1/2017/ttHTobb_M125_TuneCP5_13TeV-powheg-pythia8.list'] = [0, 2]
datasetList['nano/v1/2017/JetHT_2017B.list'] = [1, 1]
datasetList['nano/v1/2017/JetHT_2017C.list'] = [1, 1]
datasetList['nano/v1/2017/JetHT_2017D.list'] = [1, 1]
datasetList['nano/v1/2017/JetHT_2017E.list'] = [1, 1]
datasetList['nano/v1/2017/JetHT_2017F.list'] = [1, 1]



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
    isData = "no"
    if (datasetList[listfile][0] == 1): 
        isData = "yes"
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

    tmpOutputListFile.close()    
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





