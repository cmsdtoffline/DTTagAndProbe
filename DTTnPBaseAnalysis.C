#include "DTTnPBaseAnalysis.h"

DTTnPBaseAnalysis::DTTnPBaseAnalysis(const std::string &configFile)
{
	parseConfig(configFile);

	TChain *chain = new TChain("dtNtupleProducer/DTTREE");

	for (const auto &fileName : m_sampleConfig.fileNames)
	{
		chain->Add(fileName);
	}

	Init(chain);
}

void DTTnPBaseAnalysis::parseConfig(const std::string &configFile)
{
	boost::property_tree::ptree pt;

	try
	{
		boost::property_tree::ini_parser::read_ini(configFile, pt);
	}
	catch (boost::property_tree::ini_parser::ini_parser_error iniParseErr)
	{
		std::cout << "[DTTnPBaseAnalysis::parseConfig] Can't open : "
							<< iniParseErr.filename()
							<< "\n\tin line : " << iniParseErr.line()
							<< "\n\thas error :" << iniParseErr.message()
							<< std::endl;
		throw std::runtime_error("Bad INI parsing");
	}

	for (auto vt : pt)
	{
		if (vt.first.find("TagAndProbe") != std::string::npos)
			m_tnpConfig = TagAndProbeConfig(vt);
		else
			m_sampleConfig = SampleConfig(vt);
	}
}

void DTTnPBaseAnalysis::book()
{
	m_plots["pairMass"] = new TH1F("pairMass",
																 "tag and probe pair mass;mass [GeV];#entries/GeV",
																 100, 50., 150.);
	m_plots["pairDz"] = new TH1F("pairDz",
															 "tag and probe pair dZ;dZ(tag,probe);#entries/0.2",
															 100, -5., 5.);
	m_plots["probePtVsPairDr"] = new TH2F("probePtVsPairDr",
																				"probe p_{T} vs tag and probe dR;probe p_{T} [GeV];tag and probe dR",
																				100, 0., 1000., 100, 0., 2 * TMath::Pi());
	m_plots["probeNPixelHits"] = new TH1F("probeNPixelHits",
																				"probe # pixel hits;# pixel hits;#entries",
																				10, -0.5, 9.5);
	m_plots["probeNTrkLayers"] = new TH1F("probeNTrkLayers",
																				"probe # tracker layers;# tracker layers;#entries",
																				30, -0.5, 29.5);
	m_plots["probeNRPCLayers"] = new TH1F("probeNRPCLayers",
																				"probe # RPC layers;# tracker layers;#entries",
																				30, -0.5, 29.5);
	m_plots["probeReliso"] = new TH1F("probeReliso",
																		"probe relative PF iso (#Delta#beta corrected);isolation;#entries",
																		100, 0., 5.);
	m_plots["probeOrigAlgo"] = new TH1F("probeOrigAlgo",
																			"probe original algo;original algo;#entries",
																			20, -0.5, 19.5);
}

vector<std::pair<Int_t, Int_t>> DTTnPBaseAnalysis::tnpSelection()
{

	vector<std::pair<Int_t, Int_t>> pairs;

	for (std::size_t iTag = 0; iTag < mu_nMuons; ++iTag) // CB int?
	{

		TLorentzVector tagVec;
		tagVec.SetPtEtaPhiM(mu_pt->at(iTag),
												mu_eta->at(iTag),
												mu_phi->at(iTag),
												0.106);

		bool tagQuality =
				mu_isTight->at(iTag) == true &&
				mu_pfIso04->at(iTag) < m_tnpConfig.tag_isoCut &&
				tagVec.Pt() > m_tnpConfig.tag_minPt;

		if (tagQuality && hasTrigger(iTag))
		{

			for (std::size_t iProbe = 0; iProbe < mu_nMuons; ++iProbe)
			{

				if (iTag == iProbe)
					continue;

				TLorentzVector probeVec;
				probeVec.SetPtEtaPhiM(mu_pt->at(iProbe),
															mu_eta->at(iProbe),
															mu_phi->at(iProbe),
															0.106);

				bool probeQuality =
						(mu_isTrackerArb->at(iProbe) == true ||
						 mu_isRPC->at(iProbe) == 1) &&
						mu_trk_origAlgo->at(iProbe) != 14 && // the track is not created out of a STA mu based seeding
						mu_trk_numberOfValidPixelHits->at(iProbe) >= m_tnpConfig.probe_minPixelHits &&
						mu_trk_numberOfValidTrackerLayers->at(iProbe) >= m_tnpConfig.probe_minTrkLayers &&
						mu_pfIso04->at(iProbe) < m_tnpConfig.probe_isoCut &&
						probeVec.Pt() > m_tnpConfig.probe_minPt;

				m_plots["probeNPixelHits"]->Fill(mu_trk_numberOfValidPixelHits->at(iProbe));
				m_plots["probeNTrkLayers"]->Fill(mu_trk_numberOfValidTrackerLayers->at(iProbe));
				m_plots["probeNRPCLayers"]->Fill(mu_isRPC->at(iProbe) ? mu_trkMu_numberOfMatchedRPCLayers->at(iProbe) : 0);
				m_plots["probeReliso"]->Fill(mu_pfIso04->at(iProbe));
				m_plots["probeOrigAlgo"]->Fill(mu_trk_origAlgo->at(iProbe));

				if (probeQuality)
				{
					Float_t mass = (tagVec + probeVec).M();
					Float_t tnpDr = tagVec.DeltaR(probeVec);
					Float_t tnpDz = mu_trk_dz->at(iTag) - mu_trk_dz->at(iProbe);

					m_plots["pairMass"]->Fill(mass);
					m_plots["probePtVsPairDr"]->Fill(probeVec.Pt(), tnpDr);
					m_plots["pairDz"]->Fill(tnpDz);

					if (std::abs(tnpDz) < m_tnpConfig.pair_maxAbsDz &&
							mu_charge->at(iTag) * mu_charge->at(iProbe) == -1 &&
							mass > m_tnpConfig.pair_minInvMass &&
							mass < m_tnpConfig.pair_maxInvMass &&
							tnpDr > m_tnpConfig.pair_minDr)
					{
						pairs.push_back(std::make_pair(iTag, iProbe));

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
	return m_tnpConfig.tag_useIsoHltPath ? mu_firesIsoTrig->at(iTag) : mu_firesTrig->at(iTag);
}

Int_t DTTnPBaseAnalysis::nMatchedCh(const Int_t iMu,
																		const Int_t iCh)
{
	Int_t nMatchedCh = 0;
	UInt_t chMask = mu_trkMu_stationMask->at(iMu);

	for (int index = 0; index < 8; ++index)
		if ((chMask & 1 << index) && index != iCh - 1)
			++nMatchedCh;

	return nMatchedCh;
}
