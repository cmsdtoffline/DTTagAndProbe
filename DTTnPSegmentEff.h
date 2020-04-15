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

  void book() final;   
  void fill() final { };
  void endJob() final;

  void fill(const std::size_t iMu);
  void harvesting();

  std::pair<std::size_t,
	    std::size_t>  getPassingProbe(const std::size_t iMu,
					  const Int_t iCh);
  
  std::size_t getPassingProbeInCh(const Int_t muSt,
				  const Int_t muSec,
				  const Int_t muWh,
				  const Int_t xMu,
				  const Int_t yMu);

  static constexpr Int_t N_WHEELS   = 5;
  static constexpr Int_t N_SECTORS  = 14;
  static constexpr Int_t N_STATIONS = 4;
  static constexpr std::size_t NULL_IDX = 999;

};

#endif
