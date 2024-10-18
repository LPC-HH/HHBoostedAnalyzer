#!/bin/bash

#######################
#debugging purposes
#######################
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
export SCRAM_ARCH=el9_amd64_gcc12
#tar -zxvf cms_setup.tar.gz
scramv1 project CMSSW $cmsswReleaseVersion

#########################################
#copy input list and exec to cmssw folder
########################################
#cp code.tgz $cmsswReleaseVersion/src/
cp $executable $cmsswReleaseVersion/src/
cp input_list.tgz $cmsswReleaseVersion/src/
mkdir -p $cmsswReleaseVersion/src/HHBoostedAnalyzer/data/PileupWeights/
#cp HHBoostedAnalyzer/data/PileupWeights/PileupWeights.root $cmsswReleaseVersion/src/HHBoostedAnalyzer/data/PileupWeights/
#cp PileupWeights.root $cmsswReleaseVersion/src/HHBoostedAnalyzer/data/PileupWeights/
#mkdir -p $cmsswReleaseVersion/src/HHBoostedAnalyzer/data/JEC/Summer16_07Aug2017_V11_MC/
#cp Summer16_07Aug2017_V11_MC_Uncertainty_AK8PFPuppi.txt $cmsswReleaseVersion/src/HHBoostedAnalyzer/data/JEC/Summer16_07Aug2017_V11_MC/
#mkdir -p $cmsswReleaseVersion/src/HHBoostedAnalyzer/data/JEC/Fall17_17Nov2017_V32_MC/
#cp Fall17_17Nov2017_V32_MC_Uncertainty_AK8PFPuppi.txt $cmsswReleaseVersion/src/HHBoostedAnalyzer/data/JEC/Fall17_17Nov2017_V32_MC/
#mkdir -p $cmsswReleaseVersion/src/HHBoostedAnalyzer/data/JEC/Autumn18_V19_MC/
#cp Autumn18_V19_MC_Uncertainty_AK8PFPuppi.txt $cmsswReleaseVersion/src/HHBoostedAnalyzer/data/JEC/Autumn18_V19_MC/

###########################
#get cmssw environment
###########################
cd $cmsswReleaseVersion/src/
eval `scram runtime -sh`
tar vxzf input_list.tgz
#tar vxzf code.tgz
#make clean
#make
ls -l

###################################
#copy input files ahead of time
###################################
inputfilelist=input_list_${filenumber}.txt
mkdir inputs/
for i in `cat $inputfilelist`
do
echo "Copying Input File: " $i
xrdcp $i ./inputs/
done
ls inputs/* > tmp_input_list.txt 

pwd
################################################################################################
#get cmssw environment - for some reason this is needed for exectuable to not crash
################################################################################################
cd /uscms_data/d2/sxie/releases/run3/HH/CMSSW_14_0_7/
eval `scram runtime -sh`
cd -


###########################
#run executable
###########################
echo "Executing Analysis executable:"
echo "./${executable} tmp_input_list.txt --outputFile=${outputfile}_${filenumber}_Part${jobIndex}Of${nJobsPerFile}.root  --isData=${isData} --year=${year} "
./${executable} tmp_input_list.txt --outputFile=${outputfile}_${filenumber}.root --isData=${isData} --year=${year}

ls -l
##########################################################
#copy outputfile to /eos space -- define in submitter code
##########################################################
eosmkdir -p ${outputDirectory}
xrdcp -f ${outputfile}_${filenumber}.root root://cmseos.fnal.gov/${outputDirectory}/${outputfile}_${filenumber}.root  
rm ${outputfile}_${filenumber}.root
rm inputs -rv 

cd -
