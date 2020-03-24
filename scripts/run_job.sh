#!/bin/bash

echo "TEST"
voms-proxy-info --all
ls -l
echo "DONE"

work_dir=HHBoostedAnalyzer

source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc6_amd64_gcc630
tar -zxvf cms_setup.tar.gz
cp input_list_* CMSSW_9_4_2/src/${work_dir}/.
cd CMSSW_9_4_2/src/${work_dir}
eval `scram runtime -sh`
make clean
make -j 16
echo $1
echo $1
echo $1

./diHiggs --input_list=$1 --output_file=$2

#gfal-copy -f *.root gsiftp://cmseos-gridftp.fnal.gov//store/group/lpchbb/LLDJntuples/cmorgoth/.
