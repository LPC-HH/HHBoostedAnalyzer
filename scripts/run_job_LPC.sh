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
mkdir -p $cmsswReleaseVersion/src/HHBoostedAnalyzer/data/
xrdcp root://cmsxrootd.fnal.gov//store/user/lpcdihiggsboost/sixie/analyzer/HHTo4BNtupler/ArmenVersion/inputs/data/JetVetoMap_Summer22_23Sep2023_RunCD_v1.root $cmsswReleaseVersion/src/HHBoostedAnalyzer/data/
xrdcp root://cmsxrootd.fnal.gov//store/user/lpcdihiggsboost/sixie/analyzer/HHTo4BNtupler/ArmenVersion/inputs/data/JetVetoMap_Summer22EE_23Sep2023_RunEFG_v1.root $cmsswReleaseVersion/src/HHBoostedAnalyzer/data/
xrdcp root://cmsxrootd.fnal.gov//store/user/lpcdihiggsboost/sixie/analyzer/HHTo4BNtupler/ArmenVersion/inputs/data/JetVetoMap_Summer23Prompt23_RunC_v1.root $cmsswReleaseVersion/src/HHBoostedAnalyzer/data/
xrdcp root://cmsxrootd.fnal.gov//store/user/lpcdihiggsboost/sixie/analyzer/HHTo4BNtupler/ArmenVersion/inputs/data/JetVetoMap_Summer23BPixPrompt23_RunD_v1.root $cmsswReleaseVersion/src/HHBoostedAnalyzer/data/

mkdir -p $cmsswReleaseVersion/src/HHBoostedAnalyzer/data/PileupWeights/
xrdcp root://cmsxrootd.fnal.gov//store/user/lpcdihiggsboost/sixie/analyzer/HHTo4BNtupler/ArmenVersion/inputs/data/PileupReweight_Summer22.root $cmsswReleaseVersion/src/HHBoostedAnalyzer/data/PileupWeights/
xrdcp root://cmsxrootd.fnal.gov//store/user/lpcdihiggsboost/sixie/analyzer/HHTo4BNtupler/ArmenVersion/inputs/data/PileupReweight_Summer22EE.root $cmsswReleaseVersion/src/HHBoostedAnalyzer/data/PileupWeights/
xrdcp root://cmsxrootd.fnal.gov//store/user/lpcdihiggsboost/sixie/analyzer/HHTo4BNtupler/ArmenVersion/inputs/data/PileupReweight_Summer23.root $cmsswReleaseVersion/src/HHBoostedAnalyzer/data/PileupWeights/
xrdcp root://cmsxrootd.fnal.gov//store/user/lpcdihiggsboost/sixie/analyzer/HHTo4BNtupler/ArmenVersion/inputs/data/PileupReweight_Summer23BPix.root $cmsswReleaseVersion/src/HHBoostedAnalyzer/data/PileupWeights/

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
inputfilelist=input_list_${filenumber}.0.txt
mkdir inputs/
for i in `cat $inputfilelist`
do
echo "Copying Input File: " $i
xrdcp $i ./inputs/
done
ls inputs/* > tmp_input_list.txt 
cat tmp_input_list.txt 
pwd


###########################
#run executable
###########################
echo "Executing Analysis executable:"
echo "./${executable} tmp_input_list.txt --outputFile=${outputfile}_${filenumber}.root  --isData=${isData} --year=${year} "
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
