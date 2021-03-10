#########
#Author: Nan Lu
#October 24 2020
#########
#I usually put HHModel.py in the Higgs Combine Tool directory: src/HiggsAnalysis/CombinedLimit/python/HHModel.py 
version=v2
dc=ws_HH_boosted4b_baseline_${version}
text2workspace.py ${dc}.txt -P HiggsAnalysis.CombinedLimit.HHModel:HHcomb3 --mass=125
dataname=data_obs
MH=125.

#upper limit on ggHH XS:
for KL in `seq -25 0.5 35`;do combine -M AsymptoticLimits ${dc}.root -n ${version} --redefineSignalPOIs r --setParameters r_gghh=1,r_qqhh=1,kt=1,kl=$KL,CV=1,C2V=1 --mass=$KL --cminDefaultMinimizerStrategy 1 --cminFallbackAlgo Minuit2,Migrad,0:0.1 --run blind;done

combineTool.py -M CollectLimits higgsCombine${version}.AsymptoticLimits.*.root --use-dirs -o kl_limits.json

python plotting_klscan.py

############################

#1D scan
combine -D data_obs -M MultiDimFit --algo grid --point 55 ${dc}.root -m 125 -n ${version} --redefineSignalPOIs kl --setParameterRanges kl=-20.5,34.5 --setParameters kl=1,kt=1,C2V=1,CV=1,r=1,r_qqhh=1,r_gghh=1  --freezeParameters r,r_gghh,r_qqhh,kt,CV,C2V --saveNLL --cminDefaultMinimizerStrategy 1 --cminFallbackAlgo Minuit2,Migrad,0:0.1 

#1D scan plot 
#ref: https://github.com/cms-analysis/CombineHarvester/blob/master/CombineTools/scripts/plot1DScan.py
plot1DScan.py higgsCombine${version}.MultiDimFit.mH125.root --POI kl
