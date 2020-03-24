#!/bin/bash

#######################
#debugging purposes
#######################
voms-proxy-info --all
ls -l

############################
#define exec and setup cmssw
############################
executable=diHiggsPlots
source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc6_amd64_gcc630
tar -zxvf cms_setup.tar.gz

#########################################
#copy input list and exec to cmssw folder
########################################
cp input_list_* CMSSW_9_4_2/src/.
cp ${executable} CMSSW_9_4_2/src/.

###########################
#get cmssw environment
###########################
cd CMSSW_9_4_2/src/
eval `scram runtime -sh`
echo $1

###########################
#run executable and delete
###########################
./diHiggsPlots --input_list=$1 --output_file=$2 $3
rm dummy.root


##########################################################
#copy outputfile to /eos space -- define in submitter code
##########################################################
