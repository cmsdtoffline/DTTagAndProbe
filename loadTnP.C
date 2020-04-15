#include <string>
#include "TROOT.h"

void loadSegmentTnP()
{

  //gSystem->Load("/opt/local/lib/libboost_filesystem-mt.dylib");
  
  gROOT->ProcessLine(".L DTNtupleBaseAnalyzer.C++");
  gROOT->ProcessLine(".L DTTnPConfig.C++");
  gROOT->ProcessLine(".L DTTnPBaseAnalysis.C++");
  gROOT->ProcessLine(".L DTTnPSegmentEff.C++");

}
