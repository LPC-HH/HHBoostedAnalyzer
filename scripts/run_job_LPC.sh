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
outputfile=$5
outputDirectory=$6
cmsswReleaseVersion=$7

############################
#define exec and setup cmssw
############################
workDir=`pwd`
executable=Run${analysisType}
source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc7_amd64_gcc820
#tar -zxvf cms_setup.tar.gz
scramv1 project CMSSW $cmsswReleaseVersion

#########################################
#copy input list and exec to cmssw folder
########################################
cp input_list.tgz $cmsswReleaseVersion/src/
cp ${executable} $cmsswReleaseVersion/src/.

###########################
#get cmssw environment
###########################
cd $cmsswReleaseVersion/src/
eval `scram runtime -sh`
tar vxzf input_list.tgz
inputfilelist=input_list_${jobnumber}.txt

###########################
#run executable
###########################
echo "Executing Analysis executable:"
echo "./${executable} ${inputfilelist} --outputFile=${outputfile} --optionNumber=${option} -d=${isData} "
./${executable} ${inputfilelist} --outputFile=${outputfile}_${jobnumber}.root --optionNumber=${option} -d=${isData} 

ls -l
##########################################################
#copy outputfile to /eos space -- define in submitter code
##########################################################
eosmkdir -p ${outputDirectory}
xrdcp -f ${outputfile}_${jobnumber}.root root://cmseos.fnal.gov/${outputDirectory}/${outputfile}_${jobnumber}.root 
rm ${outputfile}_${jobnumber}.root

cd -
