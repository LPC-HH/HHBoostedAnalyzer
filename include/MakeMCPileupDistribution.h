#ifndef DEF_MakeMCPileupDistribution
#define DEF_MakeMCPileupDistribution

#include "EventAnalyzer.h"

class MakeMCPileupDistribution: public EventAnalyzer {
    public: 
        MakeMCPileupDistribution(TTree *tree=0): EventAnalyzer(tree) { }
        void Analyze(bool isData, int option, string outputFileName, string label, string pileupWeightName);
};

#endif
