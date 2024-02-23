#!/usr/bin/python

import os
import datetime
import time
import subprocess
import glob
import sys
from collections import OrderedDict

queueType = "longlunch"
#"longlunch" - 8nh
#"workday" - 1nd
#"microcentury" - 1nh
#"espresso" - 8nm



#analysis = "HHTo4BNtupler"
#option = 5

analysis = "MakeMCPileupDistribution"
option = 1

cmsswReleaseVersion = "CMSSW_12_6_3"
label = "option"+str(option)
filesPerJob = 1
outputfile = "HHTo4BNtuple" + "_" + label
outputDirectoryBase = "/store/group/phys_susy/razor/Run3Analysis/HH/"+analysis+"/"+label+"/"

datasetList = OrderedDict()
#2022 ntuples
# datasetList["nano/run3/2022/EGamma_2022A.list"] = [1, 1, "2022", "", 10]
# datasetList["nano/run3/2022/EGamma_2022B.list"] = [1, 1, "2022", "", 10]
# datasetList["nano/run3/2022/EGamma_2022C.list"] = [1, 1, "2022", "", 10]
# datasetList["nano/run3/2022/EGamma_2022D.list"] = [1, 1, "2022", "", 10]
# datasetList["nano/run3/2022/EGamma_2022E.list"] = [1, 1, "2022", "", 10]
# datasetList["nano/run3/2022/EGamma_2022F.list"] = [1, 1, "2022", "", 10]
# datasetList["nano/run3/2022/EGamma_2022G.list"] = [1, 1, "2022", "", 10]
# datasetList["nano/run3/2022/JetHT_2022A.list"] = [1, 1, "2022", "", 10]
# datasetList["nano/run3/2022/JetHT_2022B.list"] = [1, 1, "2022", "", 10]
# datasetList["nano/run3/2022/JetHT_2022C.list"] = [1, 1, "2022", "", 10]
# datasetList["nano/run3/2022/JetMET_2022C.list"] = [1, 1, "2022", "", 10]
# datasetList["nano/run3/2022/JetMET_2022D.list"] = [1, 1, "2022", "", 10]
# datasetList["nano/run3/2022/JetMET_2022E.list"] = [1, 1, "2022", "", 10]
# datasetList["nano/run3/2022/JetMET_2022F.list"] = [1, 1, "2022", "", 10]
# datasetList["nano/run3/2022/JetMET_2022G.list"] = [1, 1, "2022", "", 10]
# datasetList["nano/run3/2022/SingleMuon_2022A.list"] = [1, 1, "2022", "", 10] 
# datasetList["nano/run3/2022/SingleMuon_2022B.list"] = [1, 1, "2022", "", 10] 
# datasetList["nano/run3/2022/SingleMuon_2022C.list"] = [1, 1, "2022", "", 10]
# datasetList["nano/run3/2022/Muon_2022C.list"] = [1, 1, "2022", "", 10]
# datasetList["nano/run3/2022/Muon_2022D.list"] = [1, 1, "2022", "", 10]
# datasetList["nano/run3/2022/Muon_2022E.list"] = [1, 1, "2022", "", 10]
# datasetList["nano/run3/2022/Muon_2022F.list"] = [1, 1, "2022", "", 10]
# datasetList["nano/run3/2022/Muon_2022G.list"] = [1, 1, "2022", "", 10]

datasetList["nano/run3/2022/GluGlutoHHto4B_kl-0p00_kt-1p00_c2-0p00.list"] = [0, 1, "2022", "", 10]
datasetList["nano/run3/2022/GluGlutoHHto4B_kl-0p00_kt-1p00_c2-1p00.list"] = [0, 1, "2022", "", 10]
datasetList["nano/run3/2022/GluGlutoHHto4B_kl-1p00_kt-1p00_c2-0p00.list"] = [0, 1, "2022", "", 10]
datasetList["nano/run3/2022/GluGlutoHHto4B_kl-1p00_kt-1p00_c2-0p10.list"] = [0, 1, "2022", "", 10]
datasetList["nano/run3/2022/GluGlutoHHto4B_kl-1p00_kt-1p00_c2-0p35.list"] = [0, 1, "2022", "", 10]
datasetList["nano/run3/2022/GluGlutoHHto4B_kl-1p00_kt-1p00_c2-3p00.list"] = [0, 1, "2022", "", 10]
datasetList["nano/run3/2022/GluGlutoHHto4B_kl-1p00_kt-1p00_c2-m2p00.list"] = [0, 1, "2022", "", 10]
datasetList["nano/run3/2022/GluGlutoHHto4B_kl-2p45_kt-1p00_c2-0p00.list"] = [0, 1, "2022", "", 10]
datasetList["nano/run3/2022/GluGlutoHHto4B_kl-5p00_kt-1p00_c2-0p00.list"] = [0, 1, "2022", "", 10]
datasetList['nano/run3/2022/ggHH_cHHH_1_TSG.list'] = [0, 1, "2022", "", 1]
datasetList["nano/run3/2022/TTtoLNu2Q_PostEE.list"] = [0, 1, "2022", "", 10]
datasetList["nano/run3/2022/VBFHto2B_PostEE.list"] = [0, 1, "2022", "", 10]
datasetList["nano/run3/2022/WW_PostEE.list"] = [0, 1, "2022", "", 10]
datasetList["nano/run3/2022/WZ_PostEE.list"] = [0, 1, "2022", "", 10]
datasetList["nano/run3/2022/WminusH_Hto2B_Wto2Q_PostEE.list"] = [0, 1, "2022", "", 10]
datasetList["nano/run3/2022/WplusH_Hto2B_Wto2Q_PostEE.list"] = [0, 1, "2022", "", 10]
datasetList["nano/run3/2022/ZH_Hto2B_Zto2Q_PostEE.list"] = [0, 1, "2022", "", 10]
datasetList["nano/run3/2022/ZZ_PostEE.list"] = [0, 1, "2022", "", 10]
datasetList["nano/run3/2022/ggHto2B_Pt200ToInf_PostEE.list"] = [0, 1, "2022", "", 10]
datasetList["nano/run3/2022/ggZH_Hto2B_Zto2Q_PostEE.list"] = [0, 1, "2022", "", 10]
datasetList["nano/run3/2022/ttH_Hto2B_PostEE.list"] = [0, 1, "2022", "", 10]
datasetList["nano/run3/2022/TTto4Q_postEE.list"] = [0, 1, "2022", "", 10]
datasetList["nano/run3/2022/QCDPt50to80_postEE.list"] = [0, 1, "2022", "", 10]
datasetList["nano/run3/2022/QCDPt80to120_postEE.list"] = [0, 1, "2022", "", 10]
datasetList["nano/run3/2022/QCDPt120to170_postEE.list"] = [0, 1, "2022", "", 10]
datasetList["nano/run3/2022/QCDPt170to300_postEE.list"] = [0, 1, "2022", "", 10]
datasetList["nano/run3/2022/QCDPt300to470_postEE.list"] = [0, 1, "2022", "", 10]
datasetList["nano/run3/2022/QCDPt470to600_postEE.list"] = [0, 1, "2022", "", 10]
datasetList["nano/run3/2022/QCDPt600to800_postEE.list"] = [0, 1, "2022", "", 10]
datasetList["nano/run3/2022/QCDPt800to1000_postEE.list"] = [0, 1, "2022", "", 10]
datasetList["nano/run3/2022/QCDPt1000to1400_postEE.list"] = [0, 1, "2022", "", 10]
datasetList["nano/run3/2022/QCDPt1400to1800_postEE.list"] = [0, 1, "2022", "", 10]
datasetList["nano/run3/2022/QCDPt1800to2400_postEE.list"] = [0, 1, "2022", "", 10]
datasetList["nano/run3/2022/QCDPt2400to3200_postEE.list"] = [0, 1, "2022", "", 10]
datasetList["nano/run3/2022/QCDPt3200toInf_postEE.list"] = [0, 1, "2022", "", 10]
#datasetList["nano/run3/2022/Wto2Q-3Jets_HT-400to600_PostEE.list"] = [0, 1, "2022", "", 10]
#datasetList["nano/run3/2022/Wto2Q-3Jets_HT-800_PostEE.list"] = [0, 1, "2022", "", 10]
datasetList["nano/run3/2022/DYJetsToLL_M50ToInf_PostEE.list"] = [0, 1, "2022", "", 10]
datasetList["nano/run3/2022/Wto2Q-3Jets_HT-200to400.list"] = [0, 1, "2022", "", 10]
datasetList["nano/run3/2022/Wto2Q-3Jets_HT-400to600.list"] = [0, 1, "2022", "", 10]
datasetList["nano/run3/2022/Wto2Q-3Jets_HT-600to800.list"] = [0, 1, "2022", "", 10]
datasetList["nano/run3/2022/Wto2Q-3Jets_HT-800.list"] = [0, 1, "2022", "", 10]
datasetList["nano/run3/2022/WtoLNu-2Jets.list"] = [0, 1, "2022", "", 10]


#2023 ntuples
# datasetList["nano/run3/2023/EGamma0_Run2023A.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/EGamma0_Run2023B.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/EGamma0_Run2023C-v1.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/EGamma0_Run2023C-v2.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/EGamma0_Run2023C-v3.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/EGamma0_Run2023C-v4.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/EGamma0_Run2023D-v1.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/EGamma0_Run2023D-v2.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/EGamma1_Run2023A.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/EGamma1_Run2023B.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/EGamma1_Run2023C-v1.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/EGamma1_Run2023C-v2.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/EGamma1_Run2023C-v3.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/EGamma1_Run2023C-v4.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/EGamma1_Run2023D-v1.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/EGamma1_Run2023D-v2.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/JetMET0_2023A.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/JetMET0_2023B.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/JetMET0_2023C-v1.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/JetMET0_2023C-v2.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/JetMET0_2023C-v3.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/JetMET0_2023C-v4.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/JetMET0_2023D-v1.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/JetMET0_2023D-v2.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/JetMET1_2023A.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/JetMET1_2023B.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/JetMET1_2023C-v1.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/JetMET1_2023C-v2.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/JetMET1_2023C-v3.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/JetMET1_2023C-v4.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/JetMET1_2023D-v1.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/JetMET1_2023D-v2.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/Muon0_2023A.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/Muon0_2023B.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/Muon0_2023C-v1.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/Muon0_2023C-v2.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/Muon0_2023C-v3.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/Muon0_2023C-v4.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/Muon0_2023D-v1.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/Muon0_2023D-v2.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/Muon1_2023A.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/Muon1_2023B.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/Muon1_2023C-v1.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/Muon1_2023C-v2.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/Muon1_2023C-v3.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/Muon1_2023C-v4.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/Muon1_2023D-v1.list"] = [1, 1, "2023", "", 10]
# datasetList["nano/run3/2023/Muon1_2023D-v2.list"] = [1, 1, "2023", "", 10]



#create directory for condor jobs

CMSSW_BASE_DIR = os.getenv('CMSSW_BASE')
Analyzer_DIR = CMSSW_BASE_DIR+"/src/HHBoostedAnalyzer/"

for listfile in datasetList.keys():

    datasetName = listfile.replace(".list","")
    print "Preparing analyzer workflow for dataset :" + datasetName + "\n"
    if not os.path.exists("list/" + listfile):
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

    #####################################
    #Copy run script and executable
    #####################################
    os.system("cp " + Analyzer_DIR + "/scripts/run_job_CERN.sh " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/")
    os.system("cp " + Analyzer_DIR + "Run" + analysis + " " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/")
    os.system("mkdir -p " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/HHBoostedAnalyzer/data/")
    os.system("cp " + Analyzer_DIR + "/data/JetHTTriggerEfficiency_" + year + ".root " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/HHBoostedAnalyzer/data/")
    os.system("cp " + Analyzer_DIR + "/data/JetHTTriggerEfficiency_Summer16.root " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/HHBoostedAnalyzer/data/")
    os.system("cp " + Analyzer_DIR + "/data/JetHTTriggerEfficiency_Fall17.root " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/HHBoostedAnalyzer/data/")
    os.system("cp " + Analyzer_DIR + "/data/JetHTTriggerEfficiency_Fall18.root " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/HHBoostedAnalyzer/data/")
    os.system("mkdir -p " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/HHBoostedAnalyzer/data/PileupWeights/")
    os.system("cp " + Analyzer_DIR + "/data/PileupWeights/PileupWeights.root " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/HHBoostedAnalyzer/data/PileupWeights/")
    os.system("mkdir -p " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/HHBoostedAnalyzer/data/JEC/Summer16_07Aug2017_V11_MC/")
    os.system("cp " + Analyzer_DIR + "/data/JEC/Summer16_07Aug2017_V11_MC/Summer16_07Aug2017_V11_MC_Uncertainty_AK8PFPuppi.txt " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/HHBoostedAnalyzer/data/JEC/Summer16_07Aug2017_V11_MC/")
    os.system("mkdir -p " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/HHBoostedAnalyzer/data/JEC/Fall17_17Nov2017_V32_MC/")
    os.system("cp " + Analyzer_DIR + "/data/JEC/Fall17_17Nov2017_V32_MC/Fall17_17Nov2017_V32_MC_Uncertainty_AK8PFPuppi.txt " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/HHBoostedAnalyzer/data/JEC/Fall17_17Nov2017_V32_MC/")
    os.system("mkdir -p " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/HHBoostedAnalyzer/data/JEC/Autumn18_V19_MC/")
    os.system("cp " + Analyzer_DIR + "/data/JEC/Autumn18_V19_MC/Autumn18_V19_MC_Uncertainty_AK8PFPuppi.txt " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/HHBoostedAnalyzer/data/JEC/Autumn18_V19_MC/")

    #####################################
    #Create Condor JDL file
    #####################################
    tmpCondorJDLFile = open(Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/task.jdl","w+")
    tmpCondorJDLFileTemplate = """
Universe  = vanilla
Executable = ./run_job_CERN.sh
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
    #tmpCondorJDLFile.write("transfer_input_files = " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/run_job_CERN.sh, " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/input_list.tgz, " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/Run" + analysis + "\n")

    #tmpCondorJDLFile.write("transfer_input_files = " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/run_job_CERN.sh, " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/input_list.tgz, " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/Run" + analysis + ", " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/HHBoostedAnalyzer/data/JetHTTriggerEfficiency_" + year + ".root, " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/HHBoostedAnalyzer/data/JetHTTriggerEfficiency_Summer16.root, " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/HHBoostedAnalyzer/data/JetHTTriggerEfficiency_Fall17.root, " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/HHBoostedAnalyzer/data/JetHTTriggerEfficiency_Fall18.root, " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/HHBoostedAnalyzer/data/PileupWeights/PileupWeights.root, " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/HHBoostedAnalyzer/data/JEC/Summer16_07Aug2017_V11_MC/Summer16_07Aug2017_V11_MC_Uncertainty_AK8PFPuppi.txt, " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/HHBoostedAnalyzer/data/JEC/Fall17_17Nov2017_V32_MC/Fall17_17Nov2017_V32_MC_Uncertainty_AK8PFPuppi.txt, " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/HHBoostedAnalyzer/data/JEC/Autumn18_V19_MC/Autumn18_V19_MC_Uncertainty_AK8PFPuppi.txt " + "\n")

    tmpCondorJDLFile.write("transfer_input_files = " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/run_job_CERN.sh, " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/input_list.tgz, " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/Run" + analysis + ", " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/HHBoostedAnalyzer/data/JetHTTriggerEfficiency_" + year + ".root, " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/HHBoostedAnalyzer/data/JetHTTriggerEfficiency_Summer16.root, " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/HHBoostedAnalyzer/data/JetHTTriggerEfficiency_Fall17.root, " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/HHBoostedAnalyzer/data/JetHTTriggerEfficiency_Fall18.root, " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/HHBoostedAnalyzer/data/PileupWeights/PileupWeights.root, " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/HHBoostedAnalyzer/data/JEC/Summer16_07Aug2017_V11_MC/Summer16_07Aug2017_V11_MC_Uncertainty_AK8PFPuppi.txt, " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/HHBoostedAnalyzer/data/JEC/Fall17_17Nov2017_V32_MC/Fall17_17Nov2017_V32_MC_Uncertainty_AK8PFPuppi.txt, " + Analyzer_DIR + "/condor/analyzer_" + analysis + "_" + label + "/" + datasetName + "/HHBoostedAnalyzer/data/JEC/Autumn18_V19_MC/Autumn18_V19_MC_Uncertainty_AK8PFPuppi.txt " + "\n")

    tmpCondorJDLFileTemplate = """
should_transfer_files = YES
when_to_transfer_output = ON_EXIT

# Resources request
"""
    tmpCondorJDLFile.write(tmpCondorJDLFileTemplate)
 
    tmpCondorJDLFileTemplate = """
requirements = (OpSysAndVer =?= \"CentOS7\")
RequestCpus = 1 
RequestMemory = 2000
+JobFlavour = "espresso"
    
# Jobs selection
Queue I from (
"""

    tmpCondorJDLFile.write(tmpCondorJDLFileTemplate)
    for i in range(1,nJobs+1):
        tmpCondorJDLFile.write(str(i)+"\n")
    tmpCondorJDLFile.write(")\n")
    tmpCondorJDLFile.close()









