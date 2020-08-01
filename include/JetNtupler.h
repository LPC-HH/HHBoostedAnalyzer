#ifndef DEF_JetNtupler
#define DEF_JetNtupler

#include "EventAnalyzer.h"

class JetNtupler: public EventAnalyzer {
    public: 
        JetNtupler(TTree *tree=0): EventAnalyzer(tree) { }
        void Analyze(bool isData, int option, string outputFileName, string label, string pileupWeightName);
};

#endif
