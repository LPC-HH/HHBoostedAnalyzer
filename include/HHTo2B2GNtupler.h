#ifndef DEF_HHTo2B2GNtupler
#define DEF_HHTo2B2GNtupler

#include "EventAnalyzer.h"
#include "TH2F.h"

class HHTo2B2GNtupler: public EventAnalyzer {
    public: 
        HHTo2B2GNtupler(TTree *tree=0): EventAnalyzer(tree) { }
        void Analyze(bool isData, int option, string outputFileName, string label, string pileupWeightName);
	double getTriggerEff( TH2F *trigEffHist , double pt, double mass );
	double getTriggerEff3D( TH2F *triggerEffHist_Xbb0p0To0p9, 
				TH2F *triggerEffHist_Xbb0p9To0p95, 
				TH2F *triggerEffHist_Xbb0p95To0p98, 
				TH2F *triggerEffHist_Xbb0p98To1p0, 
				double pt, double mass, double PNetXbb );
};

#endif
