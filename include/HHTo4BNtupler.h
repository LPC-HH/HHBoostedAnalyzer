#ifndef DEF_HHTo4BNtupler
#define DEF_HHTo4BNtupler

#include "EventAnalyzer.h"

class HHTo4BNtupler: public EventAnalyzer {
    public: 
        HHTo4BNtupler(TTree *tree=0): EventAnalyzer(tree) { }
        void Analyze(bool isData, int option, string outputFileName, string label);
};

#endif
