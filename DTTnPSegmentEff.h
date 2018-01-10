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

  virtual void book() override;   
  virtual void fill(Int_t iMu) override;
  virtual void endJob() override;

  Int_t getPassingProbe(const Int_t iMu,
			const Int_t iCh);

  Int_t getPassingProbeInCh(const Int_t iMu,
                            const Int_t muSt,
                            const Int_t muSec,
                            const Int_t muWh,
                            const Int_t xMu,
                            const Int_t yMu);

};

#endif
