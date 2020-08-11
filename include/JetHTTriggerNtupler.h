#ifndef DEF_JetHTTriggerNtupler
#define DEF_JetHTTriggerNtupler

#include "EventAnalyzer.h"

class JetHTTriggerNtupler: public EventAnalyzer {
    public: 
        JetHTTriggerNtupler(TTree *tree=0): EventAnalyzer(tree) { }
        void Analyze(bool isData, int option, string outputFileName, string label, string pileupWeightName);
};

#endif
