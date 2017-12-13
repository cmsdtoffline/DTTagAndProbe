#ifndef DTTnPSegmentEff_h
#define DTTnPSegmentEff_h

#include "DTTnPBaseAnalysis.h"

#include <string>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
#include <bitset>
#include <regex>
#include <map>

class DTTnPSegmentEff : public DTTnPBaseAnalysis 
{

 public:
  DTTnPSegmentEff(const std::string & configFile);
  ~DTTnPSegmentEff() { };

  void Loop() override;
  
 protected:

  virtual void fill(Int_t iMu) override;
  virtual void book() override;

  Int_t getPassingProbe(const Int_t iMu,
			const Int_t iCh);

};

#endif
