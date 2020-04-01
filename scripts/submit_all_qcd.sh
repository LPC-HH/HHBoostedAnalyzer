#!/bin/bash

./submit_condor.sh qcd_ht50to100_skim ../list/qcd_ht_50to100.list
./submit_condor.sh qcd_ht300to500_skim ../list/qcd_ht_300to500.list
./submit_condor.sh qcd_ht500to700_skim ../list/qcd_ht_500to700.list
./submit_condor.sh qcd_ht700to1000_skim ../list/qcd_ht_700to1000.list
./submit_condor.sh qcd_ht1000to1500_skim ../list/qcd_ht_1000to1500.list
./submit_condor.sh qcd_ht1500to2000_skim ../list/qcd_ht_1500to2000.list
./submit_condor.sh qcd_ht2000toInf_skim ../list/qcd_ht_2000toInf.list
