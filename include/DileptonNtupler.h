#ifndef DEF_DileptonNtupler
#define DEF_DileptonNtupler

#include "EventAnalyzer.h"

class DileptonNtupler: public EventAnalyzer {
    public: 
        DileptonNtupler(TTree *tree=0): EventAnalyzer(tree) { }
        void Analyze(bool isData, int option, string outputFileName, string label, string pileupWeightName);
};

#endif
