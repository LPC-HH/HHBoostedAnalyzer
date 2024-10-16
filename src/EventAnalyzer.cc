#include "EventAnalyzer.h"

using namespace std;

EventAnalyzer::EventAnalyzer(TTree *tree) : Events(tree)
{
}

EventAnalyzer::~EventAnalyzer()
{

}

void EventAnalyzer::Analyze(bool isData, string label) {
  cout << "Analyze method called on base EventAnalyzer instance.  Parameters were: " << isData << " " << label  << endl;
}

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
