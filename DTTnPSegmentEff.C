#include "DTTnPSegmentEff.h"

DTTnPSegmentEff::DTTnPSegmentEff(const std::string & configFile) : DTTnPBaseAnalysis(configFile)
{

}

void DTTnPSegmentEff::Loop()
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
	std::cout << "[DTTnPSegmentEff::Loop] processed : " 
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

	  fill(pair.second);

	}

    }

  std::cout << std::endl; 
  outputFile.Write();
  outputFile.Close();

}

void DTTnPSegmentEff::book()
{

  DTTnPBaseAnalysis::book();

  m_plots["nOtherMatchedChVsEta"] = new TH2F("nOtherMatchedChVsEta",
					     "# of matched stations other than the one under investigation",
					     96,-1.2,1.2,5,-0.5,4.5);

  for (Int_t iCh = 1; iCh < 5; ++iCh)
    {
      std::stringstream iChTag;
      iChTag << "MB" << iCh;

      std::string hName = "effVsEta" + iChTag.str();
      m_effs[hName.c_str()] = new TEfficiency(hName.c_str(),
					      "segment efficiency vs #eta;muon #eta;Efficiency",
					      96,-1.2,1.2);
      hName = "effVsPhiPlus" + iChTag.str();
      m_effs[hName.c_str()] = new TEfficiency(hName.c_str(),
					      "segment efficiency vs #phi for mu^{+};muon #phi;Efficiency",
					      96,-TMath::Pi(),TMath::Pi());

      hName = "effVsPhiMinus" + iChTag.str();
      m_effs[hName.c_str()] = new TEfficiency(hName.c_str(),
					      "segment efficiency vs #phi for mu^{-};muon #phi;Efficiency",
					      96,-TMath::Pi(),TMath::Pi());

      hName = "effPhiVsEtaPlus" + iChTag.str();
      m_effs[hName.c_str()] = new TEfficiency(hName.c_str(),
					      "segment efficiency #phi vs #eta for mu^{+};muon #phi;muon #eta",
					      96,-TMath::Pi(),TMath::Pi(),96,-1.2,1.2);

      hName = "effPhiVsEtaMinus" + iChTag.str();
      m_effs[hName.c_str()] = new TEfficiency(hName.c_str(),
					      "segment efficiency #phi vs #eta for mu^{+};muon #phi;muon #eta",
					      96,-TMath::Pi(),TMath::Pi(),96,-1.2,1.2);

      hName = "effVsPt" + iChTag.str();
      m_effs[hName.c_str()] = new TEfficiency(hName.c_str(),
					      "segment efficiency vs p_{T};muon p_{T};Efficiency",
					      100,0.,200.);

      hName = "effSecVsWh" + iChTag.str();
      m_effs[hName.c_str()] = new TEfficiency(hName.c_str(),
					      "segment efficiency sector vs wheel;sector;wheel",
					      14,0.5,14.5,5,-2,2);
      hName = "effChamb" + iChTag.str();
      m_effs[hName.c_str()] = new TEfficiency(hName.c_str(),
					      "segment efficiency chamber summary;efficiency;# chambers",
					      200,0.,1.);
    }
 
}

void DTTnPSegmentEff::fill(const Int_t iMu)
{

  std::bitset<4> matchedCh = DTTnPBaseAnalysis::hasMatchedCh(iMu);

  for (Int_t iCh = 1; iCh < 5; ++iCh)
    {
      std::stringstream iChTag;
      iChTag << "MB" << iCh;

      Int_t nMatchInOtherCh = 0;

      for (Int_t iOtherCh = 1; iOtherCh < 5; ++iOtherCh)
	nMatchInOtherCh +=  iCh != iOtherCh ? matchedCh[iOtherCh-1] : 0;

      m_plots["nOtherMatchedChVsEta"]->Fill(Mu_eta->at(iMu),nMatchInOtherCh);

      if (nMatchInOtherCh >= m_tnpConfig.probe_minNMatchedSeg)
	{
	  Int_t iPassingSeg = getPassingProbe(iMu,iCh);
	  
	  Int_t probeSec = 0;
	  Int_t probeWh = 0;

	  Int_t iPassingSegInCh = getPassingProbe(iMu,iCh,probeSec,probeWh);

	  std::string hName = "effVsEta" + iChTag.str();
	  m_effs[hName]->Fill(iPassingSeg >= 0,Mu_eta->at(iMu));

	      
	  if (Mu_charge->at(iMu) == 1)
	    {
	      hName = "effVsPhiPlus" + iChTag.str();
	      m_effs[hName]->Fill(iPassingSeg >= 0,Mu_phi->at(iMu));
	      hName = "effPhiVsEtaPlus" + iChTag.str();
	      m_effs[hName]->Fill(iPassingSeg >= 0,Mu_phi->at(iMu),Mu_eta->at(iMu));
	    }

	  if (Mu_charge->at(iMu) == -1)
	    {
	      hName = "effVsPhiMinus" + iChTag.str();
              m_effs[hName]->Fill(iPassingSeg >= 0,Mu_phi->at(iMu));
	      hName = "effPhiVsEtaMinus" + iChTag.str();
	      m_effs[hName]->Fill(iPassingSeg >= 0,Mu_phi->at(iMu),Mu_eta->at(iMu));
	    }

	  hName = "effVsPt" + iChTag.str();
	  m_effs[hName]->Fill(iPassingSeg >= 0,
			      sqrt((Mu_px->at(iMu) * Mu_px->at(iMu)) +
				   (Mu_py->at(iMu) * Mu_py->at(iMu))));

	  if (probeSec > 0)
	    {
	      hName = "effPhiVsEtaPlus" + iChTag.str();
              m_effs[hName]->Fill(iPassingSegInCh >= 0,probeSec,probeWh);
	    }
	  
	}
    }

}

Int_t DTTnPSegmentEff::getPassingProbe(const Int_t iMu,
				       const Int_t iCh) 
{

  Int_t iBestSeg   = -1;
  Float_t bestSegDr = 999.;	  
	  
  for (Int_t iMatch = 0; iMatch < Mu_nMatches->at(iMu); ++ iMatch)
    {
      Int_t whMu  = getXY<Int_t>(Mu_matches_Wh,iMu,iMatch);
      Int_t secMu = getXY<Int_t>(Mu_matches_Sec,iMu,iMatch);
      Int_t stMu  = getXY<Int_t>(Mu_matches_St,iMu,iMatch);
      Float_t xMu = getXY<Float_t>(Mu_matches_x,iMu,iMatch); 
      Float_t yMu = getXY<Float_t>(Mu_matches_x,iMu,iMatch); 
      
      if (stMu == iCh)
	{

	  iBestSeg = getPassingProbeInCh(iMu,muSt,muSec,
					 muWh,xMu,yMu);
	  
	  Float_t xSeg = dtsegm4D_x_pos_loc->at(iSeg); 
	  Float_t ySeg = dtsegm4D_x_pos_loc->at(iSeg);

	  Float_t dX = std::abs(xSeg-xMu);
	  Float_t dY = std::abs(ySeg-yMu);
	  Float_t dR = sqrt(dX*dX + dY*dY);
 
	  if(dR < bestSegDr)
	    {
	      iBestSeg = iSeg;
	      bestSegDr = dR;
	    }
	}
      
    }

  return iBestSeg;
  
}

Int_t DTTnPSegmentEff::getPassingProbeInCh(const Int_t iMu,
					   const Int_t iCh,
					   Int_t & probeSec,
					   Int_t & probeWh) 
{

  Int_t iBestSeg   = -1;
  Float_t bestSegDr = 999.;	  
	  
  for (Int_t iMatch = 0; iMatch < Mu_nMatches->at(iMu); ++ iMatch)
    {
      Int_t whMu  = getXY<Int_t>(Mu_matches_Wh,iMu,iMatch);
      Int_t secMu = getXY<Int_t>(Mu_matches_Sec,iMu,iMatch);
      Int_t stMu  = getXY<Int_t>(Mu_matches_St,iMu,iMatch);
      Float_t xMu = getXY<Float_t>(Mu_matches_x,iMu,iMatch); 
      Float_t yMu = getXY<Float_t>(Mu_matches_x,iMu,iMatch); 
      Float_t xBorderMu = getXY<Float_t>(Mu_matches_edgeX,iMu,iMatch); 
      Float_t yBorderMu = getXY<Float_t>(Mu_matches_edgeY,iMu,iMatch); 
      
      if (stMu == iCh &&
	  xBorderMu < m_tnpConfig.probe_maxBorderDx &&
	  yBorderMu < m_tnpConfig.probe_maxBorderDy )
	{

	  probeSec = secMu;
	  probeWh  = whMu;
	  
	  iBestSeg = getPassingProbeInCh(iMu,muSt,muSec,
					 muWh,xMu,yMu);
	  
	  Float_t xSeg = dtsegm4D_x_pos_loc->at(iSeg); 
	  Float_t ySeg = dtsegm4D_x_pos_loc->at(iSeg);

	  Float_t dX = std::abs(xSeg-xMu);
	  Float_t dY = std::abs(ySeg-yMu);
	  Float_t dR = sqrt(dX*dX + dY*dY);
 
	  if(dR < bestSegDr)
	    {
	      iBestSeg = iSeg;
	      bestSegDr = dR;
	    }
	}
      
    }

  return iBestSeg;
  
}

Int_t DTTnPSegmentEff::getPassingProbeInCh(const Int_t iMu,
					   const Int_t muSt,
					   const Int_t muSec,
					   const Int_t muWh,
					   const Int_t xMu,
					   const Int_t yMu) 
{

  Int_t iBestSeg   = -1;
  Float_t bestSegDr = 999.;	  	  

  for (Int_t iSeg = 0; iSeg < Ndtsegments; ++ iSeg)
    {
      
      Int_t whSeg  = dtsegm4D_wheel->at(iSeg);
      Int_t secSeg = dtsegm4D_sector->at(iSeg);
      Int_t stSeg  = dtsegm4D_station->at(iSeg);
      Float_t xSeg = dtsegm4D_x_pos_loc->at(iSeg); 
      Float_t ySeg = dtsegm4D_x_pos_loc->at(iSeg);
      
      Float_t dX = std::abs(xSeg-xMu);
      Float_t dY = std::abs(ySeg-yMu);
      Float_t dR = sqrt(dX*dX + dY*dY);
      
      if(whMu  == whSeg  && 
	 secMu == secSeg && 
	 stMu  == stSeg  &&
	 dR < bestSegDr  &&
	 dR < m_tnpConfig.passing_probe_maxTkSegDr &&
	 dX < m_tnpConfig.passing_probe_maxTkSegDx &&
	 dY < m_tnpConfig.passing_probe_maxTkSegDy )
	{
	  iBestSeg = iSeg;
	  bestSegDr = dR;
	}
    }

  return bestSegDr;
  
}
