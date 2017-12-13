#ifndef DTTnPConfig_h
#define DTTnPConfig_h

#include "TString.h"
#include <string>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
#include <regex>
#include <map>

#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/exceptions.hpp>
#include <boost/lexical_cast.hpp>

class SampleConfig 
{

 public :
  
  // config parameters (public for direct access)

  TString fileName;  
  TString outputFileName;  
  TString sampleName;  
  Float_t nEvents;

  std::vector<int> runs;
        
  SampleConfig() {};
    
#ifndef __MAKECINT__ // CB CINT doesn't like boost :'-(    
  SampleConfig(boost::property_tree::ptree::value_type & vt); 
#endif

  ~SampleConfig() {};

 private:
  std::vector<int> toArray(const std::string & entries); 
    
};


class TagAndProbeConfig 
{
  
 public :
  
  // config parameters (public for direct access)
    
  Float_t pair_minInvMass;
  Float_t pair_maxInvMass;    
  Float_t pair_maxAbsDz;
  Float_t pair_minDr;      
 
  Float_t tag_minPt;      
  
  Float_t tag_isoCut;
  Float_t tag_hltDrCut;
  std::string tag_hltFilter;
  
  Float_t probe_minPt;      
  Float_t probe_maxAbsEta;
  
  Float_t probe_isoCut;
  Int_t   probe_minTrkLayers;      
  Int_t   probe_minPixelHits;

  Float_t probe_maxTkSegDx;
  Float_t probe_maxTkSegDy;
  Float_t probe_minNMatchedSeg;
  Int_t   probe_minRPCLayers;      

  Float_t passing_probe_maxTkSegDx;
  Float_t passing_probe_maxTkSegDy;
  Float_t passing_probe_maxTkSegDr;
  
  std::string hlt_path; 
  
  TagAndProbeConfig() {};
  
#ifndef __MAKECINT__ // CB CINT doesn't like boost :'-(    
  TagAndProbeConfig(boost::property_tree::ptree::value_type & vt); 
#endif
  
  ~TagAndProbeConfig() {};
  
};

#endif

