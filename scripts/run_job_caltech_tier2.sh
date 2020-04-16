#!/bin/bash

#######################
#debugging purposes
#######################
voms-proxy-info --all
ls -l

############################
#define exec and setup cmssw
############################
executable=diHiggs
source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc7_amd64_gcc700

###########################
#get cmssw environment
###########################
#cd CMSSW_9_4_2/src/
#eval `scram runtime -sh`
#echo $1

###########################
#run executable
###########################
#./diHiggs --input_list=$1 --output_file=$2

##########################################################
#copy outputfile to /eos space -- define in submitter code
##########################################################
