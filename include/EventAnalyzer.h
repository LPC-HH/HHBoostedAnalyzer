#ifndef EventAnalyzer_h
#define EventAnalyzer_h

#include "Events.hh" //This is a MakeClass of the RazorEvents tree in the ntuple to be analyzed

//ROOT includes
#include <TROOT.h>
#include <TChain.h>
#include <TTree.h>
#include <TFile.h>
#include "TLorentzVector.h"
#include "TRandom3.h"

//C++ includes
#include <map>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class EventAnalyzer: public Events {
    public :
        EventAnalyzer(TTree *tree=0);
        virtual ~EventAnalyzer();       

        /* void EnableAll(); */
	double deltaPhi(double phi1, double phi2);
	double deltaR(double eta1, double phi1, double eta2, double phi2);

        //------ LIST OF ANALYSES ------//
        virtual void Analyze(bool isData, int option, string outputFileName, string label, string pileupWeightName);
  
};

#endif
