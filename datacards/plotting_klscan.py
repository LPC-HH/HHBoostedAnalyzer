#this plotting script is from https://gitlab.cern.ch/ccaputo/hhbb4l-klambda-scan-run2 

import matplotlib
matplotlib.use('Agg')

import numpy as np
import json
import numpy as np

from matplotlib import pyplot as plt
from matplotlib import rcParams
rcParams['font.family'] = 'sans-serif'
rcParams['font.sans-serif'] = ['Tahoma']
from matplotlib import pyplot as plt

def getArrays(json_dict):
    exp_0  = []
    exp_p1 = []
    exp_m1 = []
    exp_p2 = []
    exp_m2 = []
    obs    = []

    keys = np.array([float(key) for key in json_dict.keys()])
    keys.sort()
    #keys = keys[:-1]
    for kl in keys:
        limit = json_dict[str(kl)]
        exp_0.append(limit['exp0'])
        exp_p1.append(limit['exp+1'])
        exp_m1.append(limit['exp-1'])
        exp_p2.append(limit['exp+2'])
        exp_m2.append(limit['exp-2'])
        #obs.append(limit['obs'])
        obs.append(limit['exp0'])

    return obs, exp_0, exp_p1, exp_m1, exp_p2, exp_m2, keys


def klscan_plotting(year, filename):

    lumi = {'2016': '35.8', '2017': '41.5', '2018': '59.7', 'Run2':'136.1'}

    with open(filename) as json_file:
        json_dict = json.load(json_file)
        obs, exp_0, exp_p1, exp_m1, exp_p2, exp_m2, kl = getArrays(json_dict)

        # Parameters for the theoretical HH xsection []
        A = 62.5359
        B = -44.3231
        C = 9.6340

        kl_fine = np.arange(kl[0],kl[-1],0.1)
        print(kl[-1],kl[0])

        NNLO_correction = 1.115
        # XSec array used for scaling the Combine result
        xsec = NNLO_correction*(A + B*kl + C*kl**2)
        # XSec array used for plotting theoretical curve
        xsec_fine =  NNLO_correction*(A + B*kl_fine + C*kl_fine**2)

        xsec_obs      = obs*xsec
        xsec_limit    = exp_0*xsec
        xsec_limit_p2 = exp_p2*xsec
        xsec_limit_p1 = exp_p1*xsec
        xsec_limit_m1 = exp_m1*xsec
        xsec_limit_m2 = exp_m2*xsec

        fig = plt.figure(figsize=(10,10))
        ax  = fig.add_subplot(1,1,1)

        #Theory curve
        ax.plot(kl_fine, xsec_fine, color='red', lw='2', label='theory')
        # Uncertanties bands
        ax.fill_between(kl,xsec_limit_p2, color="gold", label=r"2 sigma")
        ax.fill_between(kl,xsec_limit_p1, color="forestgreen", label=r"1 sigma")
        ax.fill_between(kl,xsec_limit_m1, color="gold")
        ax.fill_between(kl,xsec_limit_m2, color="white")
        # Expected and observed limits
        ax.plot(kl, xsec_limit, color='k', ls='--', label="Expected")
        #ax.plot(kl, xsec_obs, '.', color='k', label="Observed", ls='-')


        ax.set_ylim(10,10e5)
        ax.set_xlim(-25,45)
        ax.set_ylabel(r"95% CL on $\sigma_{ggF}(pp \to HH)$ [fb]", fontsize="23",fontweight='normal')
        ax.set_xlabel(r"$\kappa_{\lambda}$", fontsize="23", fontweight='normal')

        #ax.set_xticks(ticks=keys)
        #ax.set_title("CMS Preliminary", loc="left", fontdict={'fontsize': "14", 'fontweight':'bold'})
        fig.text(.22, 0.85, "CMS", fontweight='bold',
                fontsize=24, color='k', rotation=0,
                ha='right', va='top', alpha=1)
        fig.text(.285, 0.81, "Preliminary", fontstyle='italic',
                fontsize=20, color='k', rotation=0,
                ha='right', va='top', alpha=1)
        ax.set_title("%s $fb^{-1}$ (13 TeV)"%(lumi[year]), loc="right", fontdict={'fontsize': "18", 'fontweight':'normal'})


        #ax.tick_params(direction='out', length=6, width=1, colors='k',
        #              grid_color='k', which='major')
        #ax.tick_params(direction='out', length=3, width=1, colors='k',
        #              grid_color='k', which='minor')

        from matplotlib.lines import Line2D
        from matplotlib.patches import Patch

        custom_lines = [Line2D([0], [0], color="red", lw=1, ls="-", label='Theory Prediction'),
                        Line2D([0], [0], color="black", lw=1, ls="-", label='Observed 95% CL Limit'),
                        Line2D([0], [0], color="black", lw=1, ls="--", label='Expected 95% CL Limit'),
                        Patch(facecolor="forestgreen", edgecolor='k',label=r'Expected $\pm$1 s.d.'),
                        Patch(facecolor="gold", edgecolor='k', label=r'Expected $\pm$2 s.d.')]

        ax.legend(handles=custom_lines,fontsize=16)

        #plt.title(r"$HH \to bbZZ \to bbZZ(4l)$", fontdict={'fontsize': "18",'fontweight':'normal'})
        plt.yscale("log")
        plt.grid(ls='--',color='grey')

        # position bottom right
        #fig.text(.86, 0.15, 'VERY PRELIMINARY',
        #         fontsize=70, color='k', rotation=45,
        #         ha='right', va='bottom', alpha=0.6)

        print("OBSERVED")
        print(kl[ xsec_obs < xsec ])
        print("EXP")
        print(kl[xsec_limit < xsec])

        plt.savefig("klambda_scan_JESsplitting_{}_UNBLIND.pdf".format(year))


limits_files = {#'2016': 'kl_scan_2016_JesSplitting.json',
                #'2017': 'kl_scan_2017_JesSplitting.json',
                #'2018': 'kl_scan_2018_JesSplitting.json',
                'Run2': 'kl_limits_default.json'}

for year, filename in limits_files.items():
    print(year,filename)
    klscan_plotting(year, filename)

