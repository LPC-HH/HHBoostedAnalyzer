# diHiggs

cmsrel CMSSW_9_4_2

cd CMSSW_9_4_2/src

cmsenv

git clone git@github.com:LPC-HH/HHBoostedAnalyzer.git

cd HHBoostedAnalyzer

make

#to submit jobs

mkdir -p condor
voms-proxy-init --voms cms

#submission scripts are in HHBoostedAnalyzer/scripts

