#ifndef DTTnPBaseAnalysis_h
#define DTTnPBaseAnalysis_h

#include "DTNtupleBaseAnalyzer.h"
#include "DTTnPConfig.h"

#include "TLorentzVector.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TEfficiency.h"

#include <string>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
#include <bitset>
#include <regex>
#include <map>

class DTTnPBaseAnalysis : public DTNtupleBaseAnalyzer 
{

 public:
  DTTnPBaseAnalysis(const std::string & configFile);
  ~DTTnPBaseAnalysis() { };
  
  virtual void Loop() override;

 protected:
  virtual void Init(TChain* chain) override { DTNtupleBaseAnalyzer::Init(chain); };

  void pharseConfig(const std::string & configFile);

  std::vector<std::pair<Int_t,Int_t>> tnpSelection();
  
  bool hasTrigger(const Int_t iTag);

  Int_t nMatchedCh(const Int_t iMu, const Int_t iCh);  

  virtual void book() override;
  virtual void fill(Int_t iMu) { };
  virtual void endJob() override { };
  
  TagAndProbeConfig m_tnpConfig;
  SampleConfig      m_sampleConfig;

  std::map<std::string, TH1*> m_plots;
  std::map<std::string, TEfficiency*> m_effs;
  
};

#endif
