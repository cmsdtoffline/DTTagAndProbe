#include "DTTnPBaseAnalysis.h"

DTTnPBaseAnalysis::DTTnPBaseAnalysis(const std::string & configFile) 
{

  pharseConfig(configFile);
  TFile *fileIn = new TFile(m_sampleConfig.fileName,"read");

  TTree * tree = 0;
  fileIn->GetObject("DTTree",tree);

  fileIn->GetObject("triggerFilterNames",m_triggerFilterNames);

  m_hltFilterId = -1;
  Int_t hltFilterNameId = 0;
  
  for (const auto & filterName : (*m_triggerFilterNames))
    {
      if (filterName.find(m_tnpConfig.tag_hltFilter) != std::string::npos)
	{
	  m_hltFilterId = hltFilterNameId;
	  break;
	}
      hltFilterNameId++;
    }

  if (m_hltFilterId>=0)
    std::cout << "[DTTnPBaseAnalysis::DTTnPBaseAnalysis] Found match for HLT filter : " 
	      << m_triggerFilterNames->at(m_hltFilterId) << std::endl;
  else
    std::cout << "[DTTnPBaseAnalysis::DTTnPBaseAnalysis] Not found match for any HLT filter in ntuples, TnP will fail!"  << std::endl;

  Init(tree);

}

void DTTnPBaseAnalysis::pharseConfig(const std::string & configFile)
{

  boost::property_tree::ptree pt;
  
  try
    {
      boost::property_tree::ini_parser::read_ini(configFile, pt);
    }
  catch (boost::property_tree::ini_parser::ini_parser_error iniParseErr)
    {
      std::cout << "[DTTnPBaseAnalysis::pharseConfig] Can't open : " 
		<< iniParseErr.filename()
		<< "\n\tin line : " << iniParseErr.line()
		<< "\n\thas error :" << iniParseErr.message()
		<< std::endl;
      throw std::runtime_error("Bad INI parsing");
    }

  for( auto vt : pt )
    {
      if (vt.first.find("TagAndProbe") != std::string::npos)
	m_tnpConfig = TagAndProbeConfig(vt);
      else
	m_sampleConfig = SampleConfig(vt);
    }

}


void DTTnPBaseAnalysis::Loop()
{

  TFile outputFile(m_sampleConfig.outputFileName,"recreate");
  outputFile.cd();

  book();

  if (fChain == 0) return;

  Long64_t nentries = (m_sampleConfig.nEvents > 0 && 
		       fChain->GetEntriesFast() > m_sampleConfig.nEvents) ? 
                       m_sampleConfig.nEvents : fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) 
    {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if(jentry % 10000 == 0) 
	std::cout << "[DTTnPBaseAnalysis::Loop] processed : " 
		  << jentry << " entries\r" << std::flush;

      bool hasGoodRun = false;

      for (const auto & run : m_sampleConfig.runs)
	{	  
	  if (run == 0 ||
	      run == runnumber)
	    {
	      hasGoodRun = true;
	      break;
	    }
	    
	}

      if(!hasGoodRun)
	continue;

      auto tnpPairs = tnpSelection();

      for(const auto & pair : tnpPairs) 
	{ 

	  hasMatchedCh(pair.second);
	  fill(pair.second);

	}

    }

  std::cout << std::endl; 
  outputFile.Write();
  outputFile.Close();

}

void DTTnPBaseAnalysis::book()
{

  m_plots["pairMass"] = new TH1F("pairMass",
				 "tag and probe pair mass;#entries/GeV;mass [GeV]",
				 100,50.,150.); 
  m_plots["pairDz"] = new TH1F("pairDz",
			       "tag and probe pair dZ;#entries/0.2;dZ(tag,probe)",
			       100,-10.,10.); 
  m_plots["probePtVsPairDr"] = new TH2F("probePtVsPairDr",
					"probe p_{T} vs tag and probe dR;probe p_{T} [GeV];tag and probe dR",
					100,0.,1000., 100,0.,2*TMath::Pi());
  m_plots["probePt"]  = new TH1F("probePt",
				 "probe p_{T};#entries/GeV;p_{T} [GeV]",
				 200,0.,200.); 
  m_plots["probeEta"] = new TH1F("probeEta",
				"probe #eta;#entries/0.05;#eta",
				48,1.2,1.2); 
  m_plots["probeNPixelHits"]  = new TH1F("probeNPixelHits",
				 "probe # pixel hits;#entries;# pixel hits",
				 10,-0.5,9.5); 
  m_plots["probeNTrkLayers"]  = new TH1F("probeNTrkLayers",
				 "probe # tracker layers;#entries;# tracker layers",
				 30,-0.5,29.5); 
  m_plots["probeReliso"]  = new TH1F("probeReliso",
				 "probe relative trk iso;#entries;isolation",
				 100,0.,5.); 
  m_plots["probeOrigAlgo"]  = new TH1F("probeOrigAlgo",
				 "probe original algo;#entries;original algo",
				 20,-0.5,19.5); 
}

vector<std::pair<Int_t,Int_t>> DTTnPBaseAnalysis::tnpSelection()
{
  
  vector<std::pair<Int_t,Int_t>> pairs;
  
  for(Int_t iTag = 0; iTag < Nmuons; ++iTag) 
    {
      
      TLorentzVector tagVec;
      tagVec.SetXYZM(Mu_px->at(iTag),
		     Mu_py->at(iTag),
		     Mu_pz->at(iTag),
		     0.106);
      
      bool tagQuality = 
	Mu_isMuGlobal->at(iTag)     == 1 &&
	Mu_isMuTrackerArb->at(iTag) == 1 &&
	Mu_normchi2_glb->at(iTag)      < 10 &&
	Mu_numberOfHits_sta->at(iTag)        > 0  && 
	Mu_numberOfPixelHits_glb->at(iTag)   >= 1 &&
	Mu_numberOfTrackerHits_glb->at(iTag) >= 6 &&
	Mu_tkIsoR03_glb->at(iTag) / tagVec.Pt() < m_tnpConfig.tag_isoCut &&
	tagVec.Pt() > m_tnpConfig.tag_minPt ;
      
      if(tagQuality && hasTrigger(iTag)) 
	{
	  
	  for(Int_t iProbe = 0; iProbe < Nmuons; ++iProbe) 
	    {
	      
	      if (iTag == iProbe) 
		continue;
	      
	      TLorentzVector probeVec;
	      probeVec.SetXYZM(Mu_px->at(iProbe),
			       Mu_py->at(iProbe),
			       Mu_pz->at(iProbe),
			       0.106);
	      
	      bool probeQuality =
		Mu_isMuTracker->at(iProbe) == 1   && 
		Mu_origAlgo_trk->at(iProbe) != 14 && // the track is not created out of a STA mu based seeding
		Mu_numberOfPixelHits_glb->at(iProbe)   >= m_tnpConfig.probe_minPixelHits &&
		Mu_numberOfTrackerHits_glb->at(iProbe) >= m_tnpConfig.probe_minTrkLayers &&
		Mu_tkIsoR03_glb->at(iProbe) / probeVec.Pt() < m_tnpConfig.probe_isoCut &&
		std::abs(probeVec.Eta()) < m_tnpConfig.probe_maxAbsEta &&
		probeVec.Pt() > m_tnpConfig.probe_minPt;

	      m_plots["probeNPixelHits"]->Fill(Mu_numberOfPixelHits_glb->at(iProbe));
 	      m_plots["probeNTrkLayers"]->Fill(Mu_numberOfTrackerHits_glb->at(iProbe));
	      m_plots["probeReliso"]->Fill(Mu_tkIsoR03_glb->at(iProbe) / probeVec.Pt());
	      m_plots["probeOrigAlgo"]->Fill(Mu_origAlgo_trk->at(iProbe));

	      if (probeQuality)
		{
		  Float_t mass  = (tagVec + probeVec).M();
		  Float_t tnpDr = tagVec.DeltaR(probeVec);
		  Float_t tnpDz = Mu_dz_trk->at(iTag) - Mu_dz_trk->at(iProbe);

		  m_plots["pairMass"]->Fill(mass);
		  m_plots["probePtVsPairDr"]->Fill(probeVec.Pt(),tnpDr);
		  m_plots["pairDz"]->Fill(tnpDz);
		  
		  if (std::abs(tnpDz) < m_tnpConfig.pair_maxAbsDz && 
		      mass  > m_tnpConfig.pair_minInvMass && 
		      mass  < m_tnpConfig.pair_maxInvMass &&
		      tnpDr > m_tnpConfig.pair_minDr)
		    {
		      pairs.push_back(std::make_pair(iTag,iProbe));
		      
		      m_plots["probePt"]->Fill(probeVec.Pt());
		      m_plots["probeEta"]->Fill(probeVec.Eta());

		      break; // just one probe per tag
		    }
		} 
	    }
	}
    }
  
  return pairs;
  
}

bool DTTnPBaseAnalysis::hasTrigger(const Int_t iTag) 
{

  if(m_hltFilterId < 0)
    return false;
  
  return getXY<Float_t>(Mu_hlt_Dr,iTag,m_hltFilterId) < m_tnpConfig.tag_hltDrCut;
  
}

std::bitset<4> DTTnPBaseAnalysis::hasMatchedCh(const Int_t iMu) 
{

  std::bitset<4> matchedCh(std::string("0000"));

  for (Int_t iMatch = 0; iMatch < Mu_nMatches->at(iMu); ++ iMatch)
    {
      Int_t whMu  = getXY<Int_t>(Mu_matches_Wh,iMu,iMatch);
      Int_t secMu = getXY<Int_t>(Mu_matches_Sec,iMu,iMatch);
      Int_t stMu  = getXY<Int_t>(Mu_matches_St,iMu,iMatch);
      Float_t xMu = getXY<Float_t>(Mu_matches_x,iMu,iMatch); 
      Float_t yMu = getXY<Float_t>(Mu_matches_x,iMu,iMatch); 

      for (Int_t iSeg = 0; iSeg < Ndtsegments; ++ iSeg)
	{
	  
	  Int_t whSeg  = dtsegm4D_wheel->at(iSeg);
	  Int_t secSeg = dtsegm4D_sector->at(iSeg);
	  Int_t stSeg  = dtsegm4D_station->at(iSeg);
	  Float_t xSeg = dtsegm4D_x_pos_loc->at(iSeg); 
	  Float_t ySeg = dtsegm4D_x_pos_loc->at(iSeg);

	  if(whMu  == whSeg  && 
	     secMu == secSeg && 
	     stMu  == stSeg  &&
	     std::abs(xMu-xSeg) < 3.)
	    {
	      matchedCh.set(stMu-1,1);
	    }
	  
	}
      
    }

  return matchedCh;
  
}
