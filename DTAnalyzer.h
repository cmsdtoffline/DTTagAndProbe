//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Dec 10 21:15:17 2017 by ROOT version 6.08/07
// from TTree DTTree/CMSSW DT tree
// found on file: DTNtuple.root
//////////////////////////////////////////////////////////

#ifndef DTAnalyzer_h
#define DTAnalyzer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "TVector.h"
#include "TClonesArray.h"

class DTAnalyzer {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           runnumber;
   Int_t           lumiblock;
   Long64_t        eventNumber;
   Float_t         timestamp;
   Int_t           bunchXing;
   Long64_t        orbitNum;
   Float_t         PV_x;
   Float_t         PV_y;
   Float_t         PV_z;
   Float_t         PV_xxE;
   Float_t         PV_yyE;
   Float_t         PV_zzE;
   Float_t         PV_xyE;
   Float_t         PV_xzE;
   Float_t         PV_yzE;
   Float_t         PV_normchi2;
   Float_t         PV_Nvtx;
   Float_t         lumiperblock;
   Float_t         beam1Intensity;
   Float_t         beam2Intensity;
   vector<TString> *hlt_path;
   vector<short>   *digi_wheel;
   vector<short>   *digi_sector;
   vector<short>   *digi_station;
   vector<short>   *digi_sl;
   vector<short>   *digi_layer;
   vector<short>   *digi_wire;
   vector<float>   *digi_time;
   vector<short>   *dtsegm4D_wheel;
   vector<short>   *dtsegm4D_sector;
   vector<short>   *dtsegm4D_station;
   vector<short>   *dtsegm4D_hasPhi;
   vector<short>   *dtsegm4D_hasZed;
   vector<float>   *dtsegm4D_x_pos_loc;
   vector<float>   *dtsegm4D_y_pos_loc;
   vector<float>   *dtsegm4D_z_pos_loc;
   vector<float>   *dtsegm4D_x_dir_loc;
   vector<float>   *dtsegm4D_y_dir_loc;
   vector<float>   *dtsegm4D_z_dir_loc;
   vector<float>   *dtsegm4D_cosx;
   vector<float>   *dtsegm4D_cosy;
   vector<float>   *dtsegm4D_cosz;
   vector<float>   *dtsegm4D_phi;
   vector<float>   *dtsegm4D_theta;
   vector<float>   *dtsegm4D_eta;
   vector<float>   *dtsegm4D_t0;
   vector<float>   *dtsegm4D_vdrift;
   vector<float>   *dtsegm4D_phinormchisq;
   vector<short>   *dtsegm4D_phinhits;
   vector<float>   *dtsegm4D_znormchisq;
   vector<short>   *dtsegm4D_znhits;
   TClonesArray    *dtsegm4D_hitsExpPos;
   TClonesArray    *dtsegm4D_hitsExpWire;
   TClonesArray    *dtsegm4D_phi_hitsPos;
   TClonesArray    *dtsegm4D_phi_hitsPosCh;
   TClonesArray    *dtsegm4D_phi_hitsPosErr;
   TClonesArray    *dtsegm4D_phi_hitsSide;
   TClonesArray    *dtsegm4D_phi_hitsWire;
   TClonesArray    *dtsegm4D_phi_hitsLayer;
   TClonesArray    *dtsegm4D_phi_hitsSuperLayer;
   TClonesArray    *dtsegm4D_phi_hitsTime;
   TClonesArray    *dtsegm4D_phi_hitsTimeCali;
   TClonesArray    *dtsegm4D_z_hitsPos;
   TClonesArray    *dtsegm4D_z_hitsPosCh;
   TClonesArray    *dtsegm4D_z_hitsPosErr;
   TClonesArray    *dtsegm4D_z_hitsSide;
   TClonesArray    *dtsegm4D_z_hitsWire;
   TClonesArray    *dtsegm4D_z_hitsLayer;
   TClonesArray    *dtsegm4D_z_hitsTime;
   TClonesArray    *dtsegm4D_z_hitsTimeCali;
   vector<short>   *cscsegm_ring;
   vector<short>   *cscsegm_chamber;
   vector<short>   *cscsegm_station;
   vector<float>   *cscsegm_cosx;
   vector<float>   *cscsegm_cosy;
   vector<float>   *cscsegm_cosz;
   vector<float>   *cscsegm_phi;
   vector<float>   *cscsegm_eta;
   vector<float>   *cscsegm_normchisq;
   vector<short>   *cscsegm_nRecHits;
   vector<short>   *ltTwinMuxIn_wheel;
   vector<short>   *ltTwinMuxIn_sector;
   vector<short>   *ltTwinMuxIn_station;
   vector<short>   *ltTwinMuxIn_quality;
   vector<short>   *ltTwinMuxIn_bx;
   vector<float>   *ltTwinMuxIn_phi;
   vector<float>   *ltTwinMuxIn_phiB;
   vector<short>   *ltTwinMuxIn_is2nd;
   vector<short>   *ltTwinMuxOut_wheel;
   vector<short>   *ltTwinMuxOut_sector;
   vector<short>   *ltTwinMuxOut_station;
   vector<short>   *ltTwinMuxOut_quality;
   vector<short>   *ltTwinMuxOut_rpcbit;
   vector<short>   *ltTwinMuxOut_bx;
   vector<float>   *ltTwinMuxOut_phi;
   vector<float>   *ltTwinMuxOut_phiB;
   vector<short>   *ltTwinMuxOut_is2nd;
   vector<short>   *ltTwinMux_thWheel;
   vector<short>   *ltTwinMux_thSector;
   vector<short>   *ltTwinMux_thStation;
   vector<short>   *ltTwinMux_thBx;
   vector<short>   *ltTwinMux_thHits;
   vector<short>   *Mu_isMuGlobal;
   vector<short>   *Mu_isMuTracker;
   vector<short>   *Mu_isMuTrackerArb;
   vector<short>   *Mu_isMuStandAlone;
   vector<short>   *Mu_isMuRPC;
   vector<int>     *Mu_nMatches;
   vector<int>     *Mu_numberOfChambers_sta;
   vector<int>     *Mu_numberOfMatches_sta;
   vector<unsigned int> *Mu_stationMask;
   vector<int>     *Mu_numberOfMatchedStations;
   vector<float>   *Mu_px;
   vector<float>   *Mu_py;
   vector<float>   *Mu_pz;
   vector<float>   *Mu_phi;
   vector<float>   *Mu_eta;
   vector<int>     *Mu_numberOfHits_sta;
   vector<int>     *Mu_segmentIndex_sta;
   vector<short>   *Mu_recHitsSize;
   vector<float>   *Mu_normchi2_sta;
   vector<short>   *Mu_charge;
   vector<float>   *Mu_dxy_sta;
   vector<float>   *Mu_dz_sta;
   vector<float>   *Mu_z_mb2_mu;
   vector<float>   *Mu_phi_mb2_mu;
   vector<float>   *Mu_pseta_mb2_mu;
   vector<float>   *Mu_normchi2_glb;
   vector<float>   *Mu_dxy_glb;
   vector<float>   *Mu_dz_glb;
   vector<int>     *Mu_numberOfPixelHits_glb;
   vector<int>     *Mu_numberOfTrackerHits_glb;
   vector<float>   *Mu_tkIsoR03_glb;
   vector<float>   *Mu_ntkIsoR03_glb;
   vector<float>   *Mu_emIsoR03_glb;
   vector<float>   *Mu_hadIsoR03_glb;
   vector<float>   *Mu_normchi2_trk;
   vector<float>   *Mu_dxy_trk;
   vector<float>   *Mu_dz_trk;
   vector<int>     *Mu_numberOfPixelHits_trk;
   vector<int>     *Mu_numberOfTrackerLayers_trk;
   vector<int>     *Mu_algo_trk;
   vector<int>     *Mu_origAlgo_trk;
   vector<int>     *Mu_numberOfRPCLayers_rpc;
   TClonesArray    *Mu_matches_Wh;
   TClonesArray    *Mu_matches_Sec;
   TClonesArray    *Mu_matches_St;
   TClonesArray    *Mu_matches_x;
   TClonesArray    *Mu_matches_y;
   TClonesArray    *Mu_matches_phi;
   TClonesArray    *Mu_matches_eta;
   TClonesArray    *Mu_matches_edgeX;
   TClonesArray    *Mu_matches_edgeY;
   TClonesArray    *Mu_hlt_Dr;
   vector<float>   *STAMu_caloCompatibility;
   vector<float>   *Mu_time_sta;
   vector<float>   *Mu_timeNDof_sta;
   vector<short>   *gmt_bx;
   vector<float>   *gmt_phi;
   vector<float>   *gmt_eta;
   vector<float>   *gmt_pt;
   vector<short>   *gmt_charge;
   vector<short>   *gmt_qual;
   vector<int>     *gmt_tf_idx;
   vector<short>   *gt_algo_bit;
   vector<short>   *gt_algo_bx;
   vector<short>   *gt_tt_bit;
   vector<short>   *gt_tt_bx;
   vector<int>     *rpc_region;
   vector<int>     *rpc_clusterSize;
   vector<int>     *rpc_strip;
   vector<int>     *rpc_bx;
   vector<int>     *rpc_station;
   vector<int>     *rpc_sector;
   vector<int>     *rpc_layer;
   vector<int>     *rpc_subsector;
   vector<int>     *rpc_roll;
   vector<int>     *rpc_ring;
   Short_t         Ndigis;
   Short_t         Ndtsegments;
   Short_t         Ncscsegments;
   Short_t         NdtltTwinMuxOut;
   Short_t         NdtltTwinMux_th;
   Short_t         NdtltTwinMuxIn;
   Short_t         Nmuons;
   Short_t         Ngmt;
   Short_t         Ngtalgo;
   Short_t         Ngttechtrig;
   Short_t         Nhlt;
   Short_t         NrpcRecHits;
   vector<short>   *bmtfPt;
   vector<short>   *bmtfEta;
   vector<short>   *bmtfPhi;
   vector<short>   *bmtfGlobalPhi;
   vector<short>   *bmftFineBit;
   vector<short>   *bmtfqual;
   vector<short>   *bmtfch;
   vector<short>   *bmtfbx;
   vector<short>   *bmtfprocessor;
   vector<short>   *bmtfwh;
   vector<short>   *bmtftrAddress;
   Int_t           bmtfSize;
   Int_t           bmtfPhSize;
   vector<int>     *bmtfPhBx;
   vector<int>     *bmtfPhWh;
   vector<int>     *bmtfPhSe;
   vector<int>     *bmtfPhSt;
   vector<float>   *bmtfPhAng;
   vector<float>   *bmtfPhBandAng;
   vector<int>     *bmtfPhCode;
   vector<int>     *bmtfPhTs2Tag;
   Int_t           bmtfThSize;
   vector<int>     *bmtfThBx;
   vector<int>     *bmtfThWh;
   vector<int>     *bmtfThSe;
   vector<int>     *bmtfThSt;
   vector<int>     *bmtfThTheta;
   vector<int>     *bmtfThCode;
   Short_t         NirpcdigiTwinMux;
   vector<int>     *RpcDigiTwinMuxBx;
   vector<int>     *RpcDigiTwinMuxStrip;
   vector<int>     *RpcDigiTwinMuxRegion;
   vector<int>     *RpcDigiTwinMuxRing;
   vector<int>     *RpcDigiTwinMuxStation;
   vector<int>     *RpcDigiTwinMuxLayer;
   vector<int>     *RpcDigiTwinMuxSector;
   vector<int>     *RpcDigiTwinMuxSubSector;
   vector<int>     *RpcDigiTwinMuxRoll;
   vector<int>     *RpcDigiTwinMuxTrIndex;
   vector<int>     *RpcDigiTwinMuxDet;
   vector<int>     *RpcDigiTwinMuxSubdetId;
   vector<int>     *RpcDigiTwinMuxRawId;
   Short_t         NirpcrechitsTwinMux;
   vector<int>     *RpcRecHitTwinMuxRegion;
   vector<int>     *RpcRecHitTwinMuxClusterSize;
   vector<int>     *RpcRecHitTwinMuxStrip;
   vector<int>     *RpcRecHitTwinMuxBx;
   vector<int>     *RpcRecHitTwinMuxStation;
   vector<int>     *RpcRecHitTwinMuxSector;
   vector<int>     *RpcRecHitTwinMuxLayer;
   vector<int>     *RpcRecHitTwinMuxSubsector;
   vector<int>     *RpcRecHitTwinMuxRoll;
   vector<int>     *RpcRecHitTwinMuxRing;

   // List of branches
   TBranch        *b_runnumber;   //!
   TBranch        *b_lumiblock;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_timestamp;   //!
   TBranch        *b_bunchXing;   //!
   TBranch        *b_orbitNum;   //!
   TBranch        *b_PV_x;   //!
   TBranch        *b_PV_y;   //!
   TBranch        *b_PV_z;   //!
   TBranch        *b_PV_xxE;   //!
   TBranch        *b_PV_yyE;   //!
   TBranch        *b_PV_zzE;   //!
   TBranch        *b_PV_xyE;   //!
   TBranch        *b_PV_xzE;   //!
   TBranch        *b_PV_yzE;   //!
   TBranch        *b_PV_normch2;   //!
   TBranch        *b_PV_Nvtx;   //!
   TBranch        *b_lumiperblock;   //!
   TBranch        *b_beam1Intensity;   //!
   TBranch        *b_beam2Intensity;   //!
   TBranch        *b_hlt_path;   //!
   TBranch        *b_digi_wheel;   //!
   TBranch        *b_digi_sector;   //!
   TBranch        *b_digi_station;   //!
   TBranch        *b_digi_sl;   //!
   TBranch        *b_digi_layer;   //!
   TBranch        *b_digi_wire;   //!
   TBranch        *b_digi_time;   //!
   TBranch        *b_dtsegm4D_wheel;   //!
   TBranch        *b_dtsegm4D_sector;   //!
   TBranch        *b_dtsegm4D_station;   //!
   TBranch        *b_dtsegm4D_hasPhi;   //!
   TBranch        *b_dtsegm4D_hasZed;   //!
   TBranch        *b_dtsegm4D_x_pos_loc;   //!
   TBranch        *b_dtsegm4D_y_pos_loc;   //!
   TBranch        *b_dtsegm4D_z_pos_loc;   //!
   TBranch        *b_dtsegm4D_x_dir_loc;   //!
   TBranch        *b_dtsegm4D_y_dir_loc;   //!
   TBranch        *b_dtsegm4D_z_dir_loc;   //!
   TBranch        *b_dtsegm4D_cosx;   //!
   TBranch        *b_dtsegm4D_cosy;   //!
   TBranch        *b_dtsegm4D_cosz;   //!
   TBranch        *b_dtsegm4D_phi;   //!
   TBranch        *b_dtsegm4D_theta;   //!
   TBranch        *b_dtsegm4D_eta;   //!
   TBranch        *b_dtsegm4D_t0;   //!
   TBranch        *b_dtsegm4D_vdrift;   //!
   TBranch        *b_dtsegm4D_phinormchisq;   //!
   TBranch        *b_dtsegm4D_phinhits;   //!
   TBranch        *b_dtsegm4D_znormchisq;   //!
   TBranch        *b_dtsegm4D_znhits;   //!
   TBranch        *b_dtsegm4D_hitsExpPos;   //!
   TBranch        *b_dtsegm4D_hitsExpWire;   //!
   TBranch        *b_dtsegm4D_phi_hitsPos;   //!
   TBranch        *b_dtsegm4D_phi_hitsPosCh;   //!
   TBranch        *b_dtsegm4D_phi_hitsPosErr;   //!
   TBranch        *b_dtsegm4D_phi_hitsSide;   //!
   TBranch        *b_dtsegm4D_phi_hitsWire;   //!
   TBranch        *b_dtsegm4D_phi_hitsLayer;   //!
   TBranch        *b_dtsegm4D_phi_hitsSuperLayer;   //!
   TBranch        *b_dtsegm4D_phi_hitsTime;   //!
   TBranch        *b_dtsegm4D_phi_hitsTimeCali;   //!
   TBranch        *b_dtsegm4D_z_hitsPos;   //!
   TBranch        *b_dtsegm4D_z_hitsPosCh;   //!
   TBranch        *b_dtsegm4D_z_hitsPosErr;   //!
   TBranch        *b_dtsegm4D_z_hitsSide;   //!
   TBranch        *b_dtsegm4D_z_hitsWire;   //!
   TBranch        *b_dtsegm4D_z_hitsLayer;   //!
   TBranch        *b_dtsegm4D_z_hitsTime;   //!
   TBranch        *b_dtsegm4D_z_hitsTimeCali;   //!
   TBranch        *b_cscsegm_ring;   //!
   TBranch        *b_cscsegm_chamber;   //!
   TBranch        *b_cscsegm_station;   //!
   TBranch        *b_cscsegm_cosx;   //!
   TBranch        *b_cscsegm_cosy;   //!
   TBranch        *b_cscsegm_cosz;   //!
   TBranch        *b_cscsegm_phi;   //!
   TBranch        *b_cscsegm_eta;   //!
   TBranch        *b_cscsegm_normchisq;   //!
   TBranch        *b_cscsegm_nRecHits;   //!
   TBranch        *b_ltTwinMuxIn_wheel;   //!
   TBranch        *b_ltTwinMuxIn_sector;   //!
   TBranch        *b_ltTwinMuxIn_station;   //!
   TBranch        *b_ltTwinMuxIn_quality;   //!
   TBranch        *b_ltTwinMuxIn_bx;   //!
   TBranch        *b_ltTwinMuxIn_phi;   //!
   TBranch        *b_ltTwinMuxIn_phiB;   //!
   TBranch        *b_ltTwinMuxIn_is2nd;   //!
   TBranch        *b_ltTwinMuxOut_wheel;   //!
   TBranch        *b_ltTwinMuxOut_sector;   //!
   TBranch        *b_ltTwinMuxOut_station;   //!
   TBranch        *b_ltTwinMuxOut_quality;   //!
   TBranch        *b_ltTwinMuxOut_rpcbit;   //!
   TBranch        *b_ltTwinMuxOut_bx;   //!
   TBranch        *b_ltTwinMuxOut_phi;   //!
   TBranch        *b_ltTwinMuxOut_phiB;   //!
   TBranch        *b_ltTwinMuxOut_is2nd;   //!
   TBranch        *b_ltTwinMux_thWheel;   //!
   TBranch        *b_ltTwinMux_thSector;   //!
   TBranch        *b_ltTwinMux_thStation;   //!
   TBranch        *b_ltTwinMux_thBx;   //!
   TBranch        *b_ltTwinMux_thHits;   //!
   TBranch        *b_Mu_isMuGlobal;   //!
   TBranch        *b_Mu_isMuTracker;   //!
   TBranch        *b_Mu_isMuTrackerArb;   //!
   TBranch        *b_Mu_isMuStandAlone;   //!
   TBranch        *b_Mu_isMuRPC;   //!
   TBranch        *b_Mu_nMatches;   //!
   TBranch        *b_Mu_numberOfChambers_sta;   //!
   TBranch        *b_Mu_numberOfMatches_sta;   //!
   TBranch        *b_Mu_stationMask;   //!
   TBranch        *b_Mu_numberOfMatchedStations;   //!
   TBranch        *b_Mu_px;   //!
   TBranch        *b_Mu_py;   //!
   TBranch        *b_Mu_pz;   //!
   TBranch        *b_Mu_phi;   //!
   TBranch        *b_Mu_eta;   //!
   TBranch        *b_Mu_numberOfHits_sta;   //!
   TBranch        *b_Mu_segmentIndex_sta;   //!
   TBranch        *b_Mu_recHitsSize;   //!
   TBranch        *b_Mu_normchi2_sta;   //!
   TBranch        *b_Mu_charge;   //!
   TBranch        *b_Mu_dxy_sta;   //!
   TBranch        *b_Mu_dz_sta;   //!
   TBranch        *b_Mu_z_mb2_mu;   //!
   TBranch        *b_Mu_phi_mb2_mu;   //!
   TBranch        *b_Mu_pseta_mb2_mu;   //!
   TBranch        *b_Mu_normchi2_glb;   //!
   TBranch        *b_Mu_dxy_glb;   //!
   TBranch        *b_Mu_dz_glb;   //!
   TBranch        *b_Mu_numberOfPixelHits_glb;   //!
   TBranch        *b_Mu_numberOfTrackerHits_glb;   //!
   TBranch        *b_Mu_tkIsoR03_glb;   //!
   TBranch        *b_Mu_ntkIsoR03_glb;   //!
   TBranch        *b_Mu_emIsoR03_glb;   //!
   TBranch        *b_Mu_hadIsoR03_glb;   //!
   TBranch        *b_Mu_normchi2_trk;   //!
   TBranch        *b_Mu_dxy_trk;   //!
   TBranch        *b_Mu_dz_trk;   //!
   TBranch        *b_Mu_numberOfPixelHits_trk;   //!
   TBranch        *b_Mu_numberOfTrackerLayers_trk;   //!
   TBranch        *b_Mu_algo_trk;   //!
   TBranch        *b_Mu_origAlgo_trk;   //!
   TBranch        *b_Mu_numberOfRPCLayers_rpc;   //!
   TBranch        *b_Mu_matches_Wh;   //!
   TBranch        *b_Mu_matches_Sec;   //!
   TBranch        *b_Mu_matches_St;   //!
   TBranch        *b_Mu_matches_x;   //!
   TBranch        *b_Mu_matches_y;   //!
   TBranch        *b_Mu_matches_phi;   //!
   TBranch        *b_Mu_matches_eta;   //!
   TBranch        *b_Mu_matches_edgeX;   //!
   TBranch        *b_Mu_matches_edgeY;   //!
   TBranch        *b_Mu_hlt_Dr;   //!
   TBranch        *b_STAMu_caloCompatibility;   //!
   TBranch        *b_Mu_time_sta;   //!
   TBranch        *b_Mu_timeNDof_sta;   //!
   TBranch        *b_gmt_bx;   //!
   TBranch        *b_gmt_phi;   //!
   TBranch        *b_gmt_eta;   //!
   TBranch        *b_gmt_pt;   //!
   TBranch        *b_gmt_charge;   //!
   TBranch        *b_gmt_qual;   //!
   TBranch        *b_gmt_tf_idx;   //!
   TBranch        *b_gt_algo_bit;   //!
   TBranch        *b_gt_algo_bx;   //!
   TBranch        *b_gt_tt_bit;   //!
   TBranch        *b_gt_tt_bx;   //!
   TBranch        *b_rpc_region;   //!
   TBranch        *b_rpc_clusterSize;   //!
   TBranch        *b_rpc_strip;   //!
   TBranch        *b_rpc_bx;   //!
   TBranch        *b_rpc_station;   //!
   TBranch        *b_rpc_sector;   //!
   TBranch        *b_rpc_layer;   //!
   TBranch        *b_rpc_subsector;   //!
   TBranch        *b_rpc_roll;   //!
   TBranch        *b_rpc_ring;   //!
   TBranch        *b_Ndigis;   //!
   TBranch        *b_Ndtsegments;   //!
   TBranch        *b_Ncscsegments;   //!
   TBranch        *b_NdtltTwinMuxOut;   //!
   TBranch        *b_NdtltTwinMux_th;   //!
   TBranch        *b_NdtltTwinMuxIn;   //!
   TBranch        *b_Nmuons;   //!
   TBranch        *b_Ngmt;   //!
   TBranch        *b_Ngtalgo;   //!
   TBranch        *b_Ngttt;   //!
   TBranch        *b_Nhlt;   //!
   TBranch        *b_NrpcRecHits;   //!
   TBranch        *b_bmtfPt;   //!
   TBranch        *b_bmtfEta;   //!
   TBranch        *b_bmtfPhi;   //!
   TBranch        *b_bmtfGlobalPhi;   //!
   TBranch        *b_bmftFineBit;   //!
   TBranch        *b_bmtfqual;   //!
   TBranch        *b_bmtfch;   //!
   TBranch        *b_bmtfbx;   //!
   TBranch        *b_bmtfprocessor;   //!
   TBranch        *b_bmtfwh;   //!
   TBranch        *b_bmtftrAddress;   //!
   TBranch        *b_bmtfSize;   //!
   TBranch        *b_bmtfPhSize;   //!
   TBranch        *b_bmtfPhBx;   //!
   TBranch        *b_bmtfPhWh;   //!
   TBranch        *b_bmtfPhSe;   //!
   TBranch        *b_bmtfPhSt;   //!
   TBranch        *b_bmtfPhAng;   //!
   TBranch        *b_bmtfPhBandAng;   //!
   TBranch        *b_bmtfPhCode;   //!
   TBranch        *b_bmtfPhTs2Tag;   //!
   TBranch        *b_bmtfThSize;   //!
   TBranch        *b_bmtfThBx;   //!
   TBranch        *b_bmtfThWh;   //!
   TBranch        *b_bmtfThSe;   //!
   TBranch        *b_bmtfThSt;   //!
   TBranch        *b_bmtfThTheta;   //!
   TBranch        *b_bmtfThCode;   //!
   TBranch        *b_NirpcdigiTwinMux;   //!
   TBranch        *b_RpcDigiTwinMuxBx;   //!
   TBranch        *b_RpcDigiTwinMuxStrip;   //!
   TBranch        *b_RpcDigiTwinMuxRegion;   //!
   TBranch        *b_RpcDigiTwinMuxRing;   //!
   TBranch        *b_RpcDigiTwinMuxStation;   //!
   TBranch        *b_RpcDigiTwinMuxLayer;   //!
   TBranch        *b_RpcDigiTwinMuxSector;   //!
   TBranch        *b_RpcDigiTwinMuxSubSector;   //!
   TBranch        *b_RpcDigiTwinMuxRoll;   //!
   TBranch        *b_RpcDigiTwinMuxTrIndex;   //!
   TBranch        *b_RpcDigiTwinMuxDet;   //!
   TBranch        *b_RpcDigiTwinMuxSubdetId;   //!
   TBranch        *b_RpcDigiTwinMuxRawId;   //!
   TBranch        *b_NirpcrechitsTwinMux;   //!
   TBranch        *b_RpcRecHitTwinMuxRegion;   //!
   TBranch        *b_RpcRecHitTwinMuxClusterSize;   //!
   TBranch        *b_RpcRecHitTwinMuxStrip;   //!
   TBranch        *b_RpcRecHitTwinMuxBx;   //!
   TBranch        *b_RpcRecHitTwinMuxStation;   //!
   TBranch        *b_RpcRecHitTwinMuxSector;   //!
   TBranch        *b_RpcRecHitTwinMuxLayer;   //!
   TBranch        *b_RpcRecHitTwinMuxSubsector;   //!
   TBranch        *b_RpcRecHitTwinMuxRoll;   //!
   TBranch        *b_RpcRecHitTwinMuxRing;   //!

   DTAnalyzer(TTree *tree=0);
   virtual ~DTAnalyzer();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   template<typename T> T getXY(TClonesArray * arr, int x, int y) 
     { return static_cast<T>((*((TVectorT<float> *)(arr->At(x))))[y]); };

};

#endif
