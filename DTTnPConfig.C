#include "DTTnPConfig.h"

SampleConfig::SampleConfig(boost::property_tree::ptree::value_type & vt)
{
 
  try
    {
      nEvents  = vt.second.get<Float_t>("nEvents");
      fileName = TString(vt.second.get<std::string>("fileName").c_str());
      outputFileName = TString(vt.second.get<std::string>("outputFileName").c_str());
      runs       = toArray(vt.second.get<std::string>("runs"));
      sampleName = TString(vt.first.c_str());
    }
  
  catch (boost::property_tree::ptree_bad_data bd)
    {
      std::cout << "[SampleConfig::SampleConfig] Can't get data : has error : "
		<< bd.what() << std::endl;
      throw std::runtime_error("Bad INI variables");
    }
  
}

std::vector<int> SampleConfig::toArray(const std::string& entries)
{
  
  std::vector<int> result;
  std::stringstream sentries(entries);
  std::string item;
  while(std::getline(sentries, item, ','))
    result.push_back(atoi(item.c_str()));
  return result;
  
}

TagAndProbeConfig::TagAndProbeConfig(boost::property_tree::ptree::value_type & vt)
{

  try
    {      
      hlt_path = vt.second.get<std::string>("hlt_path");

      pair_minInvMass = vt.second.get<Float_t>("pair_minInvMass");
      pair_maxInvMass = vt.second.get<Float_t>("pair_maxInvMass");
      pair_maxAbsDz   = vt.second.get<Float_t>("pair_maxAbsDz");
      pair_minDr      = vt.second.get<Float_t>("pair_minDr");

      tag_minPt  = vt.second.get<Float_t>("tag_minPt");
      tag_isoCut = vt.second.get<Float_t>("tag_isoCut");

      tag_hltFilter = vt.second.get<std::string>("tag_hltFilter");
      tag_hltDrCut  = vt.second.get<Float_t>("tag_hltDrCut");
      
      probe_minPt     = vt.second.get<Float_t>("probe_minPt");
      probe_maxAbsEta = vt.second.get<Float_t>("probe_maxAbsEta");
      probe_isoCut    = vt.second.get<Float_t>("probe_isoCut");

      probe_minTrkLayers  = vt.second.get<Int_t>("probe_minTrkLayers");
      probe_minPixelHits  = vt.second.get<Int_t>("probe_minPixelHits");

      probe_minNMatchedSeg = vt.second.get<Int_t>("probe_minNMatchedSeg");

      passing_probe_maxTkSegDx = vt.second.get<Float_t>("passing_probe_maxTkSegDx");
      passing_probe_maxTkSegDy = vt.second.get<Float_t>("passing_probe_maxTkSegDy");
      passing_probe_maxTkSegDr = vt.second.get<Float_t>("passing_probe_maxTkSegDr");
      
    }

  catch (boost::property_tree::ptree_bad_data bd)
    {
      std::cout << "[TagAndProbeConfig::TagAndProbeConfig] Can't get data : has error : "
		<< bd.what() << std::endl;
      throw std::runtime_error("Bad INI variables");
    }

}
