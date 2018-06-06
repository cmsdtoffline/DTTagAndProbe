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

  std::cout << "[DTTnPSegmentEff::Loop] going to process "
	    << nentries << " entries\n" << std::flush;

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

  harvesting();

  std::cout << std::endl;
  
  endJob();

  outputFile.Write();
  outputFile.Close();

}

void DTTnPSegmentEff::book()
{

  DTTnPBaseAnalysis::book();

  Double_t ptBins[22] = {0., 5., 10., 15., 20., 25., 30., 35., 40., 50., 60.,
			 70., 90., 110., 130., 150., 200., 250., 300., 400., 500., 750};
  
  m_plots["nOtherMatchedChVsEta"] = new TH2F("nOtherMatchedChVsEta",
					     "# of matched stations other than the one under investigation",
					     96,-1.2,1.2,5,-0.5,4.5);
  
  m_effs["effSecVsWhAllOne"] = new TEfficiency("effSecVsWhAll",
					    "segment efficiency sector vs wheel;sector;wheel",
					    24,0.5,12.5,10,-2.5,2.5);

  m_effs["effSecVsWhAllTwo"] = new TEfficiency("effSecVsWhAll",
					       "segment efficiency sector vs wheel;wheel/station;sector;",
					       20,1.0,21.0,12,1.0,13.0);
  
  m_plots["effChambAll"] = new TH1F("effChambAll",
				    "segment efficiency chamber summary;efficiency;# chambers",
				    50,0.9,1.);

  for (Int_t iCh = 1; iCh < 5; ++iCh)
    {
      std::stringstream iChTag;
      iChTag << "MB" << iCh;

      std::string hName = "probePt" + iChTag.str();
      m_plots[hName]  = new TH1F(hName.c_str(),
				 "probe p_{T};p_{T} [GeV];#entries/GeV",
				 200,0.,200.); 
      hName = "probeEta" + iChTag.str();
      m_plots[hName] = new TH1F(hName.c_str(),
				"probe #eta;#eta;#entries/0.05",
				56,-1.2,1.2); 
      hName = "probePhi" + iChTag.str();
      m_plots[hName] = new TH1F(hName.c_str(),
				"probe #phi;#phi;#entries/(pi*90)",
				180,-TMath::Pi(),TMath::Pi());

      hName = "probeDrVsPt" + iChTag.str();
      m_plots[hName]  = new TH2F(hName.c_str(),
				 "dR vs p_{T};p_{T} [GeV];dR",
				 200,0.,200.,50,0.,0.5); 

      hName = "probeDxVsPt" + iChTag.str();
      m_plots[hName]  = new TH2F(hName.c_str(),
				 "dX vs p_{T};p_{T} [GeV];dX",
				 200,0.,200.,50,0.,50); 

      hName = "probeDyVsPt" + iChTag.str();
      m_plots[hName]  = new TH2F(hName.c_str(),
				 "dY vs p_{T};p_{T} [GeV];dY",
				 200,0.,200.,50,0.,50); 

      hName = "effAccVsEta" + iChTag.str();
      m_effs[hName] = new TEfficiency(hName.c_str(),
				      "segment efficiency x acceptance vs #eta;muon #eta;Efficiency",
				      96,-1.2,1.2);
      hName = "effAccVsPhiPlus" + iChTag.str();
      m_effs[hName] = new TEfficiency(hName.c_str(),
				      "segment efficiency x acceptance vs #phi for mu^{+};muon #phi;Efficiency",
				      96,-TMath::Pi(),TMath::Pi());

      hName = "effAccVsPhiMinus" + iChTag.str();
      m_effs[hName] = new TEfficiency(hName.c_str(),
				      "segment efficiency x acceptance vs #phi for mu^{-};muon #phi;Efficiency",
				      96,-TMath::Pi(),TMath::Pi());

      hName = "effAccPhiVsEtaPlus" + iChTag.str();
      m_effs[hName] = new TEfficiency(hName.c_str(),
				      "segment efficiency x acceptance #phi vs #eta for mu^{+};muon #phi;muon #eta",
				      96,-TMath::Pi(),TMath::Pi(),96,-1.4,1.4);
      
      hName = "effAccPhiVsEtaMinus" + iChTag.str();
      m_effs[hName] = new TEfficiency(hName.c_str(),
				      "segment efficiency x acceptance #phi vs #eta for mu^{+};muon #phi;muon #eta",
				      96,-TMath::Pi(),TMath::Pi(),96,-1.4,1.4);

      hName = "effAccVsPt" + iChTag.str();
      m_effs[hName] = new TEfficiency(hName.c_str(),
				      "segment efficiency x acceptance vs p_{T};muon p_{T};Efficiency",
				      21, ptBins);

      hName = "effVsPt" + iChTag.str();
      m_effs[hName] = new TEfficiency(hName.c_str(),
				      "segment efficiency vs p_{T};muon p_{T};Efficiency",
				      21, ptBins);

      hName = "effVsLumi" + iChTag.str();
      m_effs[hName] = new TEfficiency(hName.c_str(),
				      "segment efficiency vs inst. lumi.;inst. lumi.;Efficiency",
				      50,0.,20000.);

      hName = "effVsRun" + iChTag.str();
      m_effs[hName] = new TEfficiency(hName.c_str(),
				      "segment efficiency vs run number;run number;Efficiency",
				      240, 294500., 306500.);

      hName = "effVsVtx" + iChTag.str();
      m_effs[hName] = new TEfficiency(hName.c_str(),
				      "segment efficiency vs # of reco. vtx.;# of reco. vtx.;Efficiency",
				      100,0.,100.);
      
      hName = "effVsNHitsPhi" + iChTag.str();
      m_effs[hName] = new TEfficiency(hName.c_str(),
				      "segment efficiency vs # phi hits.; # phi hits;Efficiency",
				      8,0.5,8.5);

      hName = "effSecVsWh" + iChTag.str();
      m_effs[hName] = new TEfficiency(hName.c_str(),
				      "segment efficiency sector vs wheel;sector;wheel",
				      14,1.,15.,5,-2.,3.);

      hName = "effChamb" + iChTag.str();
      m_plots[hName.c_str()] = new TH1F(hName.c_str(),
					"segment efficiency chamber summary;efficiency;# chambers",
					50,0.9,1.);
    }
 
}

void DTTnPSegmentEff::harvesting()
{

  std::vector<std::string> effNames  = { "effSecVsWhMB1", "effSecVsWhMB2", "effSecVsWhMB3", "effSecVsWhMB4" };
  std::vector<std::string> plotNames = { "effChambMB1",   "effChambMB2",   "effChambMB3",   "effChambMB4" };

  std::vector<std::string>::const_iterator effNamesIt  = effNames.begin();
  std::vector<std::string>::const_iterator plotNamesIt = plotNames.begin();

  std::vector<std::string>::const_iterator effNamesEnd  = effNames.end();
  std::vector<std::string>::const_iterator plotNamesEnd = plotNames.end();

  for (; effNamesIt != effNamesEnd && plotNamesIt != plotNamesEnd; ++effNamesIt, ++plotNamesIt)
    {
      Int_t nBinsX = m_effs[(*effNamesIt)]->GetTotalHistogram()->GetNbinsX();
      Int_t nBinsY = m_effs[(*effNamesIt)]->GetTotalHistogram()->GetNbinsY();

      for (Int_t binX = 1; binX <= nBinsX; ++binX)
	{
	  
	  if (binX > 12 && effNamesIt->find("MB4") == std::string::npos)
	    break;
	  
	  for (Int_t binY = 1; binY <= nBinsY; ++binY)
	    {	      
	      Int_t bin = m_effs[(*effNamesIt)]->GetGlobalBin(binX,binY);
	      m_plots[(*plotNamesIt)]->Fill(m_effs[(*effNamesIt)]->GetEfficiency(bin));
	      m_plots["effChambAll"]->Fill(m_effs[(*effNamesIt)]->GetEfficiency(bin));
	    }
	}

    }

}

void DTTnPSegmentEff::fill(const Int_t iMu)
{

  TLorentzVector probeVec;
  probeVec.SetXYZM(Mu_px->at(iMu),
		   Mu_py->at(iMu),
		   Mu_pz->at(iMu),
		   0.106);

   for (Int_t iCh = 1; iCh < 5; ++iCh)
    {
      std::stringstream iChTag;
      iChTag << "MB" << iCh;

      Int_t nMatchInOtherCh = DTTnPBaseAnalysis::nMatchedCh(iMu,iCh);

      m_plots["nOtherMatchedChVsEta"]->Fill(Mu_eta->at(iMu),nMatchInOtherCh);

      if ( nMatchInOtherCh >= m_tnpConfig.probe_minNMatchedSeg ||
	   Mu_numberOfRPCLayers_rpc->at(iMu) >= m_tnpConfig.probe_minNRPCLayers )
	{
	  std::pair<Int_t,Int_t> iPassingProbe = getPassingProbe(iMu,iCh);
	  Int_t iPassingSeg   = iPassingProbe.first;
	  Int_t iPassingMatch = iPassingProbe.second;
	  
	  std::string hName = "effAccVsEta" + iChTag.str();
	  m_effs[hName]->Fill(iPassingSeg >= 0,Mu_eta->at(iMu));

	  if (Mu_charge->at(iMu) == 1)
            {
              hName = "effAccPhiVsEtaPlus" + iChTag.str();
              m_effs[hName]->Fill(iPassingSeg >= 0,Mu_phi->at(iMu),Mu_eta->at(iMu));
            }

          if (Mu_charge->at(iMu) == -1)
            {
              hName = "effAccPhiVsEtaMinus" + iChTag.str();
              m_effs[hName]->Fill(iPassingSeg >= 0,Mu_phi->at(iMu),Mu_eta->at(iMu));
            }

	  if (std::abs(probeVec.Eta()) < m_tnpConfig.probe_maxAbsEta[iCh - 1])
	    {

	      hName = "probePt" + iChTag.str(); 
	      m_plots[hName]->Fill(probeVec.Pt());

	      hName = "probeEta" + iChTag.str(); 
	      m_plots[hName]->Fill(probeVec.Eta());
	      
	      hName = "probePhi" + iChTag.str(); 
	      m_plots[hName]->Fill(probeVec.Phi());

	      if (iPassingSeg > -1)
		{

		  Float_t xMu = getXY<Float_t>(Mu_matches_x,iMu,iPassingMatch); 
		  Float_t yMu = getXY<Float_t>(Mu_matches_y,iMu,iPassingMatch);
		  
		  Float_t xSeg = dtsegm4D_x_pos_loc->at(iPassingSeg);
		  Float_t ySeg = dtsegm4D_y_pos_loc->at(iPassingSeg);
	  
		  Float_t dX = std::abs(xSeg-xMu);
		  Float_t dY = std::abs(ySeg-yMu);
		  Float_t dR = sqrt(dX*dX + dY*dY);
	  		  
		  hName = "probeDrVsPt" + iChTag.str();
		  m_plots[hName.c_str()]->Fill(probeVec.Pt(),dR);
		  
		  hName = "probeDxVsPt" + iChTag.str();
		  m_plots[hName.c_str()]->Fill(probeVec.Pt(),dX);
		  
		  hName = "probeDyVsPt" + iChTag.str();
		  m_plots[hName.c_str()]->Fill(probeVec.Pt(),dY);
		}
	      
	      if (Mu_charge->at(iMu) == 1)
		{
		  hName = "effAccVsPhiPlus" + iChTag.str();
		  m_effs[hName]->Fill(iPassingSeg >= 0,Mu_phi->at(iMu));
		}
	      
	      if (Mu_charge->at(iMu) == -1)
		{
		  hName = "effAccVsPhiMinus" + iChTag.str();
		  m_effs[hName]->Fill(iPassingSeg >= 0,Mu_phi->at(iMu));
		}
	      
	      hName = "effAccVsPt" + iChTag.str();
	      m_effs[hName]->Fill(iPassingSeg >= 0,probeVec.Pt());
	      
	      for (Int_t iMatch = 0; iMatch < Mu_nMatches->at(iMu); ++iMatch)
		{
		  Int_t whMu  = getXY<Int_t>(Mu_matches_Wh,iMu,iMatch);
		  Int_t secMu = getXY<Int_t>(Mu_matches_Sec,iMu,iMatch);
		  Int_t stMu  = getXY<Int_t>(Mu_matches_St,iMu,iMatch);
		  Float_t xMu = getXY<Float_t>(Mu_matches_x,iMu,iMatch);
		  Float_t yMu = getXY<Float_t>(Mu_matches_y,iMu,iMatch);
		  
		  Float_t xBorderMu = getXY<Float_t>(Mu_matches_edgeX,iMu,iMatch);
		  Float_t yBorderMu = getXY<Float_t>(Mu_matches_edgeY,iMu,iMatch);
		  
		  if (stMu == iCh &&
		      xBorderMu < m_tnpConfig.probe_maxBorderDx &&
		      yBorderMu < m_tnpConfig.probe_maxBorderDy )
		    { 
		      
		      iPassingSeg =  getPassingProbeInCh(iMu,stMu,secMu,whMu,xMu,yMu);
		      
		      hName = "effVsPt" + iChTag.str();
		      m_effs[hName]->Fill(iPassingSeg >= 0,probeVec.Pt());
		      
		      hName = "effSecVsWh" + iChTag.str();
		      m_effs[hName]->Fill(iPassingSeg >= 0,secMu + 0.5,whMu + 0.5);

		      Float_t secBinOne = secMu == 13 ? 4 : secMu==14 ? 10 : secMu;
		      secBinOne += (stMu % 2 == 1) ? -0.1 : 0.1;

		      Float_t whBinOne = whMu + ((stMu -1) / 2 == 0 ? -0.1 : 0.1);
		      
		      hName = "effSecVsWhAllOne";
		      m_effs[hName]->Fill(iPassingSeg >= 0,secBinOne,whBinOne);

		      Float_t secBinTwo = secMu == 13 ? 4 : secMu==14 ? 10 : secMu;
		      secBinTwo += 0.1;

		      Float_t whBinTwo = whMu + 3.1 + ((stMu - 1) * 5);
		      
		      hName = "effSecVsWhAllTwo";
		      m_effs[hName]->Fill(iPassingSeg >= 0,whBinTwo,secBinTwo);

		      hName = "effVsLumi" + iChTag.str();
		      m_effs[hName]->Fill(iPassingSeg >= 0,lumiperblock);

		      hName = "effVsVtx" + iChTag.str();
		      m_effs[hName]->Fill(iPassingSeg >= 0,PV_Nvtx);

		      hName = "effVsRun" + iChTag.str();
		      m_effs[hName]->Fill(iPassingSeg >= 0,runnumber);
		      
		      hName = "effVsNHitsPhi" + iChTag.str();
		      Int_t nPhiHits = iPassingSeg >= 0 ? dtsegm4D_phinhits->at(iPassingSeg) : 0;
		      
		      for (Int_t phiHits = 1; phiHits < 9; ++phiHits)
			m_effs[hName]->Fill(nPhiHits >= phiHits, phiHits);
		      
		    }

		}

	    }

	}

    }
   
}

void DTTnPSegmentEff::endJob() 
{

  for (Int_t iCh = 1; iCh < 5; ++iCh)
    {
      std::stringstream iChTag;
      iChTag << "MB" << iCh;

      for (Int_t iWh = 1; iWh < 6; ++iWh)
	{

	  for (Int_t iSec = 1; iSec < 15; ++iSec)
	    {

	      if (iSec > 12 && iCh !=4)
		continue;
	      
	      std::string hName   = "effChamb" + iChTag.str();
	      std::string effName = "effSecVsWh" + iChTag.str();
	      m_plots[hName.c_str()]->Fill(m_effs[effName.c_str()]->GetEfficiency(m_effs[effName.c_str()]->GetGlobalBin(iSec,iWh)));
	      
	    }

	}

    }
  
}

std::pair<Int_t,Int_t> DTTnPSegmentEff::getPassingProbe(const Int_t iMu,
							const Int_t iCh) 
{

  Int_t iBestMatch = -1;
  Int_t iBestSeg   = -1;
  Float_t bestSegDr = 999.;	  
	  
  for (Int_t iMatch = 0; iMatch < Mu_nMatches->at(iMu); ++ iMatch)
    {
      Int_t whMu  = getXY<Int_t>(Mu_matches_Wh,iMu,iMatch);
      Int_t secMu = getXY<Int_t>(Mu_matches_Sec,iMu,iMatch);
      Int_t stMu  = getXY<Int_t>(Mu_matches_St,iMu,iMatch);
      Float_t xMu = getXY<Float_t>(Mu_matches_x,iMu,iMatch); 
      Float_t yMu = getXY<Float_t>(Mu_matches_y,iMu,iMatch); 
      
      if (stMu == iCh)
	{
	  
	  Int_t iSeg = getPassingProbeInCh(iMu,stMu,secMu,
					   whMu,xMu,yMu);

	  if (iSeg < 0)
	    continue;
	  
          Float_t xSeg = dtsegm4D_x_pos_loc->at(iSeg);
          Float_t ySeg = dtsegm4D_y_pos_loc->at(iSeg);
	  
          Float_t dX = std::abs(xSeg-xMu);
          Float_t dY = std::abs(ySeg-yMu);
          Float_t dR = sqrt(dX*dX + dY*dY);
	  
          if(dR < bestSegDr)
            {
              iBestMatch = iMatch;
              iBestSeg   = iSeg;
              bestSegDr  = dR;
            }
	  
	}
      
    }

  return std::pair<Int_t,Int_t>(iBestSeg,iBestMatch);

}


Int_t DTTnPSegmentEff::getPassingProbeInCh(const Int_t iMu,
					   const Int_t stMu,
					   const Int_t secMu,
					   const Int_t whMu,
					   const Int_t xMu,
					   const Int_t yMu)
{
  
  Int_t iBestSeg   = -1;
  Float_t bestSegDr = 999.;
  Float_t bestSegDx = 999.;
  Float_t bestSegDy = 999.;
  
  for (Int_t iSeg = 0; iSeg < Ndtsegments; ++ iSeg)
    {
      
      Int_t whSeg  = dtsegm4D_wheel->at(iSeg);
      Int_t secSeg = dtsegm4D_sector->at(iSeg);
      Int_t stSeg  = dtsegm4D_station->at(iSeg);
      Float_t xSeg = dtsegm4D_x_pos_loc->at(iSeg);
      Float_t ySeg = dtsegm4D_y_pos_loc->at(iSeg);
      
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
	  bestSegDx = dX;
	  bestSegDy = dY;
	}
    }
        
  return iBestSeg;

}
