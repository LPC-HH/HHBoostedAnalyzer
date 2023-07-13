#!/bin/bash

#######################
#debugging purposes
#######################
export X509_USER_PROXY=~/sixieProxy
voms-proxy-info --all
ls -l

############################
#define input parameters
############################
analysisType=$1
isData=$2
option=$3
jobnumber=$4
nJobsPerFile=$5
outputfile=$6
outputDirectory=$7
cmsswReleaseVersion=$8
year=$9
sampleName=$10

###############################################
#calculate filenumber and jobIndex
###############################################
filenumber=$(((($jobnumber-1)/$nJobsPerFile)+1))
jobIndex=$((($jobnumber-1)%$nJobsPerFile))


############################
#define exec and setup cmssw
############################
workDir=`pwd`
executable=Run${analysisType}
source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc7_amd64_gcc10
#tar -zxvf cms_setup.tar.gz
scramv1 project CMSSW $cmsswReleaseVersion

#########################################
#copy input list and exec to cmssw folder
########################################
cp input_list.tgz $cmsswReleaseVersion/src/
cp ${executable} $cmsswReleaseVersion/src/.
mkdir -p $cmsswReleaseVersion/src/HHBoostedAnalyzer/data/PileupWeights/
cp HHBoostedAnalyzer/data/JetHTTriggerEfficiency_2016.root $cmsswReleaseVersion/src/HHBoostedAnalyzer/data/
cp JetHTTriggerEfficiency_2016.root $cmsswReleaseVersion/src/HHBoostedAnalyzer/data/
cp HHBoostedAnalyzer/data/JetHTTriggerEfficiency_2017.root $cmsswReleaseVersion/src/HHBoostedAnalyzer/data/
cp JetHTTriggerEfficiency_2017.root $cmsswReleaseVersion/src/HHBoostedAnalyzer/data/
cp HHBoostedAnalyzer/data/JetHTTriggerEfficiency_2018.root $cmsswReleaseVersion/src/HHBoostedAnalyzer/data/
cp JetHTTriggerEfficiency_2018.root $cmsswReleaseVersion/src/HHBoostedAnalyzer/data/
cp HHBoostedAnalyzer/data/JetHTTriggerEfficiency_2022.root $cmsswReleaseVersion/src/HHBoostedAnalyzer/data/
cp JetHTTriggerEfficiency_2018.root $cmsswReleaseVersion/src/HHBoostedAnalyzer/data/
cp HHBoostedAnalyzer/data/JetHTTriggerEfficiency_Summer16.root $cmsswReleaseVersion/src/HHBoostedAnalyzer/data/
cp JetHTTriggerEfficiency_Summer16.root $cmsswReleaseVersion/src/HHBoostedAnalyzer/data/
cp HHBoostedAnalyzer/data/JetHTTriggerEfficiency_Fall17.root $cmsswReleaseVersion/src/HHBoostedAnalyzer/data/
cp JetHTTriggerEfficiency_Fall17.root $cmsswReleaseVersion/src/HHBoostedAnalyzer/data/
cp HHBoostedAnalyzer/data/JetHTTriggerEfficiency_Fall18.root $cmsswReleaseVersion/src/HHBoostedAnalyzer/data/
cp JetHTTriggerEfficiency_Fall18.root $cmsswReleaseVersion/src/HHBoostedAnalyzer/data/
cp HHBoostedAnalyzer/data/PileupWeights/PileupWeights.root $cmsswReleaseVersion/src/HHBoostedAnalyzer/data/PileupWeights/
cp PileupWeights.root $cmsswReleaseVersion/src/HHBoostedAnalyzer/data/PileupWeights/
mkdir -p $cmsswReleaseVersion/src/HHBoostedAnalyzer/data/JEC/Summer16_07Aug2017_V11_MC/
cp Summer16_07Aug2017_V11_MC_Uncertainty_AK8PFPuppi.txt $cmsswReleaseVersion/src/HHBoostedAnalyzer/data/JEC/Summer16_07Aug2017_V11_MC/
mkdir -p $cmsswReleaseVersion/src/HHBoostedAnalyzer/data/JEC/Fall17_17Nov2017_V32_MC/
cp Fall17_17Nov2017_V32_MC_Uncertainty_AK8PFPuppi.txt $cmsswReleaseVersion/src/HHBoostedAnalyzer/data/JEC/Fall17_17Nov2017_V32_MC/
mkdir -p $cmsswReleaseVersion/src/HHBoostedAnalyzer/data/JEC/Autumn18_V19_MC/
cp Autumn18_V19_MC_Uncertainty_AK8PFPuppi.txt $cmsswReleaseVersion/src/HHBoostedAnalyzer/data/JEC/Autumn18_V19_MC/

###########################
#get cmssw environment
###########################
cd $cmsswReleaseVersion/src/
eval `scram runtime -sh`
tar vxzf input_list.tgz
inputfilelist=input_list_${filenumber}.txt
echo "input filelist : ${inputfilelist}"

###################################
#copy input files ahead of time
###################################
rm -rf inputs/
mkdir -p inputs/
for i in `cat $inputfilelist`
do
echo "Copying Input File: " $i
xrdcp $i ./inputs/
done
ls inputs/* > tmp_input_list.txt 
echo "Input files"
ls -l inputs/*

############################################
#use this if the files are local on lxplus
############################################
#for i in `cat $inputfilelist`
#do
#echo "Copying Input File: " $i
#ls -l $i
#done
#cp $inputfilelist tmp_input_list.txt #Use this if files are all at CERN


###########################
#run executable
###########################
echo "Executing Analysis executable:"
echo "./${executable} tmp_input_list.txt --outputFile=${outputfile}_${filenumber}_Part${jobIndex}Of${nJobsPerFile}.root --optionNumber=${option} --isData=${isData} --year=${year} --pileupWeightName=${sampleName} --numberOfJobs=${nJobsPerFile} --jobIndex=${jobIndex}"
./${executable} tmp_input_list.txt --outputFile=${outputfile}_${filenumber}_Part${jobIndex}Of${nJobsPerFile}.root --optionNumber=${option} --isData=${isData} --year=${year} --pileupWeightName=${sampleName} --numberOfJobs=${nJobsPerFile} --jobIndex=${jobIndex}

ls -l
##########################################################
#copy outputfile to /eos space -- define in submitter code
##########################################################
mkdir -p /eos/cms/${outputDirectory}
cp ${outputfile}_${filenumber}_Part${jobIndex}Of${nJobsPerFile}.root /eos/cms/${outputDirectory}/${outputfile}_${filenumber}_Part${jobIndex}Of${nJobsPerFile}.root  -v 
rm ${outputfile}_${filenumber}_Part${jobIndex}Of${nJobsPerFile}.root
rm inputs -rv 

cd -
