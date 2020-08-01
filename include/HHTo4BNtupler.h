#ifndef DEF_HHTo4BNtupler
#define DEF_HHTo4BNtupler

#include "EventAnalyzer.h"
#include "TH2F.h"

class HHTo4BNtupler: public EventAnalyzer {
    public: 
        HHTo4BNtupler(TTree *tree=0): EventAnalyzer(tree) { }
        void Analyze(bool isData, int option, string outputFileName, string label, string pileupWeightName);
	double getTriggerEff( TH2F *trigEffHist , double pt, double mass );

};

#endif
