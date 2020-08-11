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

void EventAnalyzer::Analyze(bool isData, int option, string outputFileName, string label, string pileupWeightName) {
  cout << "Analyze method called on base EventAnalyzer instance.  Parameters were: " << isData << " " << option << " " << outputFileName << " " << label << " " << pileupWeightName << endl;
}

//NOTE: the functions below need to be maintained by hand.  If variables are added or removed from the ntuple, these functions need to be updated to reflect the changes.

// void EventAnalyzer::EnableAll(){
    
// }

double EventAnalyzer::deltaPhi(double phi1, double phi2) {
  double dphi = phi1-phi2;
  while (dphi > TMath::Pi())
    dphi -= TMath::TwoPi();
  while (dphi <= -TMath::Pi())
    dphi += TMath::TwoPi();
  return dphi;
}

double EventAnalyzer::deltaR(double eta1, double phi1, double eta2, double phi2) {
  double dphi = deltaPhi(phi1,phi2);
  double deta = eta1 - eta2;
  return sqrt( dphi*dphi + deta*deta);
}
