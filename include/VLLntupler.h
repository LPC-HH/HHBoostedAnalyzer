#ifndef DEF_VLLntupler
#define DEF_VLLntupler

#include "EventAnalyzer.h"

class VLLntupler: public EventAnalyzer {
    public: 
        VLLntupler(TTree *tree=0): EventAnalyzer(tree) { }
        void Analyze(bool isData, int option, string outputFileName, string label, string pileupWeightName);
};

#endif
