#include "EventAnalyzer.h"

using namespace std;

EventAnalyzer::EventAnalyzer(TTree *tree) : Events(tree)
{
    //turn off all branches
    //fChain->SetBranchStatus("*", 0);
}

EventAnalyzer::~EventAnalyzer()
{

}

void EventAnalyzer::Analyze(bool isData, int option, string outputFileName, string label) {
    cout << "Analyze method called on base EventAnalyzer instance.  Parameters were: " << isData << " " << option << " " << outputFileName << " " << label << endl;
}

//NOTE: the functions below need to be maintained by hand.  If variables are added or removed from the ntuple, these functions need to be updated to reflect the changes.

// void EventAnalyzer::EnableAll(){
    
// }
