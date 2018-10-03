//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri May  5 13:26:51 2017 by ROOT version 6.04/06
// from TTree trees_SRDV_/trees_SRDV_
// found on file: signalSamples/lmdp211_CT100/data-trees/mc15_13TeV.402807.MGPy8EG_A14N23LO_SS_RPVDV_700_500_lamp211_100.recon.DAOD_RPVLL.e4332_s2608_s2183_r8788.root
//////////////////////////////////////////////////////////

#ifndef doHistos_h
#define doHistos_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TLorentzVector.h>
#include "SignalEfficiency/PlotHelper.h"
#include "SignalEfficiency/GeometryHelper.h"
#include "SignalEfficiency/PhysicsObjects.h"
#include "vector"


PlotHelper plotter("");//set up the plotter
TCanvas *c1 = new TCanvas("c1","c1",800,800);


float m_pion = 0.139570; // GeV
float m_muon = 0.1056583745; // GeV


class doHistos {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Bool_t           passHLTmsonly;
   Bool_t           passMETtrigger;
   Int_t           DV_n;
   Float_t         HT;
   Double_t         MET;
   Double_t         MET_phi;
   Double_t         MET_HLT;
   Double_t         MET_HLT_phi;
   Double_t         MET_LHT;
   Double_t         MET_LHT_phi;
   Double_t         MEff;
   Double_t         MHT_HLT;
   Double_t         MHT_HLT_phi;
   Int_t           NPV;
   Int_t           PV_nTracks;
   Float_t         PV_rxy;
   Float_t         PV_sumpT2;
   Float_t         PV_x;
   Float_t         PV_y;
   Float_t         PV_z;
   Float_t         WZweight;
   Float_t         actualInteractionsPerCrossing;
   Float_t         averageInteractionsPerCrossing;
   Int_t           bcid;
   Float_t         elSF;
   Long64_t        eventNumber;
   Int_t           lumiBlock;
   Int_t           mcChannelNumber;
   Float_t         mcEventWeight;
   Float_t         muSF;
   Long64_t        pileupReweightHash;
   Float_t         pileupWeight;
   Int_t           runNumber;

   std::vector<float>         *DV_chisqPerDoF;
   std::vector<unsigned long> *DV_index;
   std::vector<int>           *DV_lastCut;
   std::vector<double>        *DV_m;
   std::vector<double>        *DV_mass;
   std::vector<double>        *DV_mass_selected;
   std::vector<int>           *DV_nLRT;
   std::vector<int>           *DV_nTracks;
   std::vector<double>        *DV_r;
   std::vector<double>        *DV_rxy;
   std::vector<float>         *DV_x;
   std::vector<float>         *DV_y;
   std::vector<float>         *DV_z;

   //std::vector<float>   *Track_charge;
   std::vector<unsigned long>   *track_DVIndex;
   std::vector<unsigned long> *track_index;
   std::vector<unsigned int> *track_hitPattern;
   std::vector<float>   *track_RadFirstHit;
   std::vector<int>   *track_isLRT;
   std::vector<int>   *track_isAssociated;
   std::vector<float>   *track_d0;
   std::vector<float>   *track_d0WrtDV;
   std::vector<double>   *track_errPt;
   std::vector<double>   *track_errd0;
   std::vector<float>   *track_errd0WrtDV;
   std::vector<double>   *track_errz0;
   std::vector<float>   *track_errz0WrtDV;
   std::vector<double>   *track_eta;
   std::vector<float>   *track_etaWrtDV;
   std::vector<double>   *track_phi;
   std::vector<float>   *track_phiWrtDV;
   std::vector<double>   *track_pt;
   std::vector<double>   *track_ptWrtDV;
   std::vector<float>   *track_z0;
   std::vector<float>   *track_z0WrtDV;
   std::vector<unsigned char> *track_NPixDeadSens; 
   std::vector<unsigned char> *track_NPixHits; 
   std::vector<unsigned char> *track_NPixHoles; 
   std::vector<unsigned char> *track_NPixSharedHits; 
   std::vector<unsigned char> *track_NSctDeadSens; 
   std::vector<unsigned char> *track_NSctHits; 
   std::vector<unsigned char> *track_NSctHoles; 
   std::vector<unsigned char> *track_NSctSharedHits; 
   std::vector<unsigned char> *track_NTrtHits; 
   std::vector<unsigned char> *track_NTrtOutliers; 

   std::vector<float> *track_truthMatchProb; 
   std::vector<int> *track_truthOrigin; 
   std::vector<int> *track_truthType; 


   std::vector<char>     *jet_BTag;
   std::vector<double>   *jet_M;
   std::vector<double>   *jet_Eta;
   std::vector<double>   *jet_Phi;
   std::vector<double>   *jet_Pt;

   std::vector<float>   *mstrack_D0;
   std::vector<double>   *mstrack_ELoss;
   std::vector<double>   *mstrack_ELossSigma;
   std::vector<double>   *mstrack_MeasELoss;
   std::vector<double>   *mstrack_MeasELossSigma;
   std::vector<unsigned long>   *mstrack_muIndex;
   std::vector<unsigned long>   *mstrack_index;
   std::vector<float>   *mstrack_ParamELoss;
   std::vector<float>   *mstrack_ParamELossSigmaM;
   std::vector<float>   *mstrack_ParamELossSigmaP;
   std::vector<float>   *mstrack_Z0;
   std::vector<double>   *mstrack_eta;
   std::vector<unsigned char>   *mstrack_nPres;
   std::vector<unsigned char>   *mstrack_nPresGood;
   std::vector<unsigned char>   *mstrack_nPresHole;
   std::vector<double>   *mstrack_phi;
   std::vector<double>   *mstrack_pt;


   std::vector<double>   *muon_CBchi2;
   std::vector<float>   *muon_DVindex;
   std::vector<unsigned long>   *muon_index;
   std::vector<int>   *muon_isLRT;
   //std::vector<float>   *muon_IDchi2;
   //std::vector<float>   *muon_MEchi2;
   std::vector<double>   *muon_RadFirstHit;
   std::vector<float>   *muon_QoverPsignif;
   std::vector<int>   *muon_TrigMatch;
   std::vector<int>   *muon_TrigMatchMSOnly;
   std::vector<unsigned short>   *muon_author;
   std::vector<float>   *muon_charge;
   std::vector<double>   *muon_d0;
   std::vector<double>   *muon_eta;
   std::vector<int>   *muon_hasCBtrack;
   std::vector<int>   *muon_hasIDtrack;
   std::vector<int>   *muon_hasMEtrack;
   std::vector<int>   *muon_hasMStrack;
   std::vector<char>   *muon_isCommonGood;
   std::vector<char>   *muon_isSignal;
   std::vector<int>   *muon_nPIX;
   std::vector<unsigned char>   *muon_nPres;
   std::vector<unsigned char>   *muon_nPresGood;
   std::vector<unsigned char>   *muon_nPresHole;
   std::vector<int>   *muon_nSCT;
   std::vector<int>   *muon_nTRT;
   std::vector<double>   *muon_phi;
   std::vector<double>   *muon_pt;
   std::vector<float>   *muon_rho;
   std::vector<int>   *muon_truthOrigin;
   std::vector<int>   *muon_truthType;
   std::vector<double>   *muon_z0;
   std::vector<double>   *muon_ptvarcone20;  
   std::vector<double>   *muon_ptvarcone30;  
   std::vector<double>   *muon_ptvarcone40;  
   std::vector<double>   *muon_ptcone20; 
   std::vector<double>   *muon_ptcone30; 
   std::vector<double>   *muon_ptcone40; 
   std::vector<double>   *muon_topoetcone20; 
   std::vector<double>   *muon_topoetcone30; 
   std::vector<double>   *muon_topoetcone40; 
   std::vector<int>  *muon_passCosmicAcceptance; 
   std::vector<int>  *muon_passCosmicVeto; 
   std::vector<int>  *muon_passFakeVeto; 
   std::vector<int>  *muon_passFullSelection; 
   std::vector<int>  *muon_passIsolation; 
   std::vector<int>  *muon_passPreselection; 
   std::vector<int>  *muon_passSegmentMatch; 


   std::vector<int>              *msSegment_chmbIndex;        
   std::vector<float>            *msSegment_clusTime;       
   std::vector<float>            *msSegment_clusTimeErr;    
   std::vector<int>              *msSegment_etaIndex;         
   std::vector<unsigned long>    *msSegment_index;  
   std::vector<int>              *msSegment_muIndex;          
   std::vector<int>              *msSegment_nPhiLays;         
   std::vector<int>              *msSegment_nPresHits;        
   std::vector<int>              *msSegment_nTrigEtaLays;     
   std::vector<float>            *msSegment_px;             
   std::vector<float>            *msSegment_py;             
   std::vector<float>            *msSegment_pz;             
   std::vector<int>              *msSegment_sector;           
   std::vector<float>            *msSegment_t0;             
   std::vector<float>            *msSegment_t0Err;          
   std::vector<int>              *msSegment_tech;             
   std::vector<float>            *msSegment_x;              
   std::vector<float>            *msSegment_y;              
   std::vector<float>            *msSegment_z;              

   std::vector<double>   *tracklessJet_Eta;
   std::vector<double>   *tracklessJet_Phi;
   std::vector<double>   *tracklessJet_Pt;
   std::vector<double>   *tracklessJet_SumPtTrkPt500;

   //std::vector<float>   *muDV_d0wrtSV; 
   //std::vector<float>   *muDV_dvIndex; 
   //std::vector<float>   *muDV_muIndex; 
   //std::vector<float>   *muDV_z0wrtSV; 

   std::vector<int>    *idTrack_NPix_DeadSens; 
   std::vector<int>    *idTrack_NPix_Hits; 
   std::vector<int>    *idTrack_NPix_Holes; 
   std::vector<int>    *idTrack_NPix_ShrHits; 
   std::vector<int>    *idTrack_NSct_DeadSens; 
   std::vector<int>    *idTrack_NSct_Hits; 
   std::vector<int>    *idTrack_NSct_Holes; 
   std::vector<int>    *idTrack_NSct_ShrHits; 
   std::vector<int>    *idTrack_NTrt_Hits; 
   std::vector<int>    *idTrack_NTrt_Outliers; 
   std::vector<float>    *idTrack_RadFirstHit; 
   std::vector<float>    *idTrack_charge; 
   std::vector<float>    *idTrack_chi2; 
   std::vector<int>    *idTrack_cosTag; 
   std::vector<float>    *idTrack_d0; 
   std::vector<double>    *idTrack_errPt; 
   std::vector<double>    *idTrack_errd0; 
   std::vector<double>    *idTrack_errz0; 
   std::vector<double>    *idTrack_eta; 
   std::vector<unsigned long>    *idTrack_index; 
   std::vector<int>    *idTrack_isLRT; 
   std::vector<double>    *idTrack_phi; 
   std::vector<double>    *idTrack_pt; 
   std::vector<float>    *idTrack_theta; 
   std::vector<float>    *idTrack_z0; 
   std::vector<float>    *idTrack_z0WrtPV; 

   std::vector<double>       *truthSparticle_BetaGamma ; 
   std::vector<double>       *truthSparticle_Charge ; 
   std::vector<double>       *truthSparticle_Eta ; 
   std::vector<double>       *truthSparticle_M ; 
   std::vector<int>          *truthSparticle_PdgId ; 
   std::vector<double>       *truthSparticle_Phi ; 
   std::vector<double>       *truthSparticle_ProperDecayTime ; 
   std::vector<double>       *truthSparticle_Pt ; 
   std::vector<int>          *truthSparticle_Status ; 
   std::vector<double>       *truthSparticle_VtxMChParticles ; 
   std::vector<double>       *truthSparticle_VtxMChParticles1GeV ; 
   std::vector<double>       *truthSparticle_VtxMChParticles1GeVd0 ; 
   std::vector<int>          *truthSparticle_VtxNChParticles ; 
   std::vector<int>          *truthSparticle_VtxNChParticles1GeV ; 
   std::vector<int>          *truthSparticle_VtxNChParticles1GeVd0 ; 
   std::vector<unsigned long> *truthSparticle_VtxNParticles ;                
   std::vector<float>        *truthSparticle_VtxX ; 
   std::vector<float>        *truthSparticle_VtxY ; 
   std::vector<float>        *truthSparticle_VtxZ ; 
   std::vector<double>       *truthTrack_Charge ; 
   std::vector<double>       *truthTrack_Eta ; 
   std::vector<int>          *truthTrack_Parent ; 
   std::vector<int>          *truthTrack_ParentStatus;
   std::vector<int>          *truthTrack_PdgId ; 
   std::vector<double>       *truthTrack_Phi ; 
   std::vector<double>       *truthTrack_Pt ; 
   std::vector<int>          *truthTrack_Status ; 
   std::vector<double>       *truthTrack_d0 ; 


   std::vector<double> *truthParticle_Charge;
   std::vector<double> *truthParticle_Eta;
   std::vector<double> *truthParticle_PdgId;
   std::vector<double> *truthParticle_Phi;
   std::vector<double> *truthParticle_Pt;

   // List of branches
   TBranch        *b_passMETtrigger; //!
   TBranch        *b_DV_n;   //!
   TBranch        *b_HT;   //!
   TBranch        *b_MET;   //!
   TBranch        *b_MET_phi; //!
   TBranch        *b_MET_HLT;   //!
   TBranch        *b_MET_HLT_phi;   //!
   TBranch        *b_MET_LHT;   //!
   TBranch        *b_MET_LHT_phi;   //!
   TBranch        *b_MEff;   //!
   TBranch        *b_MHT_HLT;   //!
   TBranch        *b_MHT_HLT_phi;   //!
   TBranch        *b_NPV;   //!
   TBranch        *b_PV_nTracks;   //!
   TBranch        *b_PV_rxy;   //!
   TBranch        *b_PV_sumpT2;   //!
   TBranch        *b_PV_x;   //!
   TBranch        *b_PV_y;   //!
   TBranch        *b_PV_z;   //!
   TBranch        *b_WZweight;   //!
   TBranch        *b_actualInteractionsPerCrossing;   //!
   TBranch        *b_averageInteractionsPerCrossing;   //!
   TBranch        *b_bcid;   //!
   TBranch        *b_elSF;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_lumiBlock;   //!
   TBranch        *b_mcChannelNumber;   //!
   TBranch        *b_mcEventWeight;   //!
   TBranch        *b_muSF;   //!
   TBranch        *b_passHLTmsonly;   //!
   TBranch        *b_pileupReweightHash;   //!
   TBranch        *b_pileupWeight;   //!
   TBranch        *b_runNumber;   //!

   TBranch  *b_DV_chisqPerDoF; //!
   TBranch  *b_DV_index; //!
   TBranch  *b_DV_lastCut; //!
   TBranch  *b_DV_m; //!
   TBranch  *b_DV_mass; //!
   TBranch  *b_DV_mass_selected; //!
   TBranch  *b_DV_nLRT; //!
   TBranch  *b_DV_nTracks; //!
   TBranch  *b_DV_r; //!
   TBranch  *b_DV_rxy; //!
   TBranch  *b_DV_x; //!
   TBranch  *b_DV_y; //!
   TBranch  *b_DV_z; //!

   //TBranch        *b_Track_charge; //!
   TBranch *b_track_DVIndex; //!
   TBranch *b_track_index; //!
   TBranch *b_track_hitPattern; //!
   TBranch *b_track_RadFirstHit; //!
   TBranch *b_track_isLRT; //!
   TBranch *b_track_isAssociated; //!
   TBranch *b_track_d0; //!
   TBranch *b_track_d0WrtDV; //!
   TBranch *b_track_errPt; //!
   TBranch *b_track_errd0; //!
   TBranch *b_track_errd0WrtDV; //!
   TBranch *b_track_errz0; //!
   TBranch *b_track_errz0WrtDV; //!
   TBranch *b_track_eta; //!
   TBranch *b_track_etaWrtDV; //!
   TBranch *b_track_phi; //!
   TBranch *b_track_phiWrtDV; //!
   TBranch *b_track_pt; //!
   TBranch *b_track_ptWrtDV; //!
   TBranch *b_track_z0; //!
   TBranch *b_track_z0WrtDV; //!
   TBranch *b_track_NPixDeadSens; //! 
   TBranch *b_track_NPixHits; //! 
   TBranch *b_track_NPixHoles; //! 
   TBranch *b_track_NPixSharedHits; //! 
   TBranch *b_track_NSctDeadSens; //! 
   TBranch *b_track_NSctHits; //! 
   TBranch *b_track_NSctHoles; //! 
   TBranch *b_track_NSctSharedHits; //! 
   TBranch *b_track_NTrtHits; //! 
   TBranch *b_track_NTrtOutliers; //! 

   TBranch *b_track_truthMatchProb; //! 
   TBranch *b_track_truthOrigin; //! 
   TBranch *b_track_truthType; //! 


   TBranch        *b_jet_BTag;   //!
   TBranch        *b_jet_M;   //!
   TBranch        *b_jet_Eta;   //!
   TBranch        *b_jet_Phi;   //!
   TBranch        *b_jet_Pt;   //!
   TBranch        *b_mstrack_D0;   //!
   TBranch        *b_mstrack_ELoss;   //!
   TBranch        *b_mstrack_ELossSigma;   //!
   TBranch        *b_mstrack_MeasELoss;   //!
   TBranch        *b_mstrack_MeasELossSigma;   //!
   TBranch        *b_mstrack_muIndex;   //!
   TBranch        *b_mstrack_index;   //!
   TBranch        *b_mstrack_ParamELoss;   //!
   TBranch        *b_mstrack_ParamELossSigmaM;   //!
   TBranch        *b_mstrack_ParamELossSigmaP;   //!
   TBranch        *b_mstrack_Z0;   //!
   TBranch        *b_mstrack_eta;   //!
   TBranch        *b_mstrack_nPres;   //!
   TBranch        *b_mstrack_nPresGood;   //!
   TBranch        *b_mstrack_nPresHole;   //!
   TBranch        *b_mstrack_phi;   //!
   TBranch        *b_mstrack_pt;   //!



   TBranch     *b_muon_CBchi2; //!
   TBranch     *b_muon_DVindex; //!
   TBranch     *b_muon_index; //!
   TBranch     *b_muon_isLRT; //!
   //TBranch        *b_muon_IDchi2;   //!
   //TBranch        *b_muon_MEchi2;   //!
   TBranch        *b_muon_QoverPsignif;   //!
   TBranch        *b_muon_TrigMatch;   //!
   TBranch        *b_muon_TrigMatchMSOnly;   //!
   TBranch        *b_muon_author;   //!
   TBranch        *b_muon_charge;   //!
   TBranch        *b_muon_d0;   //!
   TBranch        *b_muon_eta;   //!
   TBranch        *b_muon_hasCBtrack;   //!
   TBranch        *b_muon_hasIDtrack;   //!
   TBranch        *b_muon_hasMEtrack;   //!
   TBranch        *b_muon_hasMStrack;   //!
   TBranch        *b_muon_isCommonGood;   //!
   TBranch        *b_muon_isSignal;   //!
   TBranch        *b_muon_nPIX;   //!
   TBranch        *b_muon_nPres;   //!
   TBranch        *b_muon_nPresGood;   //!
   TBranch        *b_muon_nPresHole;   //!
   TBranch        *b_muon_nSCT;   //!
   TBranch        *b_muon_nTRT;   //!
   TBranch        *b_muon_phi;   //!
   TBranch        *b_muon_pt;   //!
   TBranch        *b_muon_rho;   //!
   TBranch        *b_muon_truthOrigin;   //!
   TBranch        *b_muon_truthType;   //!
   TBranch        *b_muon_z0;   //!
   TBranch        *b_muon_ptvarcone20;    //!  
   TBranch        *b_muon_ptvarcone30;    //!  
   TBranch        *b_muon_ptvarcone40;    //!  
   TBranch        *b_muon_ptcone20;    //! 
   TBranch        *b_muon_ptcone30;    //! 
   TBranch        *b_muon_ptcone40;    //! 
   TBranch        *b_muon_topoetcone20;   //! 
   TBranch        *b_muon_topoetcone30;   //! 
   TBranch        *b_muon_topoetcone40;   //!

   TBranch        *b_muon_passCosmicAcceptance; //! 
   TBranch        *b_muon_passCosmicVeto; //! 
   TBranch        *b_muon_passFakeVeto; //! 
   TBranch        *b_muon_passFullSelection; //! 
   TBranch        *b_muon_passIsolation; //! 
   TBranch        *b_muon_passPreselection; //! 
   TBranch        *b_muon_passSegmentMatch; //! 

   TBranch        *b_msSegment_chmbIndex; //!        
   TBranch        *b_msSegment_clusTime; //!       
   TBranch        *b_msSegment_clusTimeErr; //!    
   TBranch        *b_msSegment_etaIndex; //!         
   TBranch        *b_msSegment_index; //!  
   TBranch        *b_msSegment_muIndex; //!          
   TBranch        *b_msSegment_nPhiLays; //!         
   TBranch        *b_msSegment_nPresHits; //!        
   TBranch        *b_msSegment_nTrigEtaLays; //!     
   TBranch        *b_msSegment_px; //!             
   TBranch        *b_msSegment_py; //!             
   TBranch        *b_msSegment_pz; //!             
   TBranch        *b_msSegment_sector; //!           
   TBranch        *b_msSegment_t0; //!             
   TBranch        *b_msSegment_t0Err; //!          
   TBranch        *b_msSegment_tech; //!             
   TBranch        *b_msSegment_x; //!              
   TBranch        *b_msSegment_y; //!              
   TBranch        *b_msSegment_z; //!              


   TBranch        *b_tracklessJet_Eta;   //!
   TBranch        *b_tracklessJet_Phi;   //!
   TBranch        *b_tracklessJet_Pt;   //!
   TBranch        *b_tracklessJet_SumPtTrkPt500;   //!

   //TBranch        *b_muDV_d0wrtSV; //! 
   //TBranch        *b_muDV_dvIndex; //! 
   //TBranch        *b_muDV_muIndex; //! 
   //TBranch        *b_muDV_z0wrtSV; //!

   TBranch    *b_idTrack_NPix_DeadSens; //! 
   TBranch    *b_idTrack_NPix_Hits; //! 
   TBranch    *b_idTrack_NPix_Holes; //! 
   TBranch    *b_idTrack_NPix_ShrHits; //! 
   TBranch    *b_idTrack_NSct_DeadSens; //! 
   TBranch    *b_idTrack_NSct_Hits; //! 
   TBranch    *b_idTrack_NSct_Holes; //! 
   TBranch    *b_idTrack_NSct_ShrHits; //! 
   TBranch    *b_idTrack_NTrt_Hits; //! 
   TBranch    *b_idTrack_NTrt_Outliers; //! 
   TBranch    *b_idTrack_RadFirstHit; //! 
   TBranch    *b_idTrack_charge; //! 
   TBranch    *b_idTrack_chi2; //! 
   TBranch    *b_idTrack_cosTag; //! 
   TBranch    *b_idTrack_d0; //! 
   TBranch    *b_idTrack_errPt; //! 
   TBranch    *b_idTrack_errd0; //! 
   TBranch    *b_idTrack_errz0; //! 
   TBranch    *b_idTrack_eta; //! 
   TBranch    *b_idTrack_index; //! 
   TBranch    *b_idTrack_isLRT; //! 
   TBranch    *b_idTrack_phi; //! 
   TBranch    *b_idTrack_pt; //! 
   TBranch    *b_idTrack_theta; //! 
   TBranch    *b_idTrack_z0; //! 
   TBranch    *b_idTrack_z0WrtPV; //! 

   TBranch *b_truthSparticle_BetaGamma ; //! 
   TBranch *b_truthSparticle_Charge ; //! 
   TBranch *b_truthSparticle_Eta ; //! 
   TBranch *b_truthSparticle_M ; //! 
   TBranch *b_truthSparticle_PdgId ; //! 
   TBranch *b_truthSparticle_Phi ; //! 
   TBranch *b_truthSparticle_ProperDecayTime ; //! 
   TBranch *b_truthSparticle_Pt ; //! 
   TBranch *b_truthSparticle_Status ; //! 
   TBranch *b_truthSparticle_VtxMChParticles ; //! 
   TBranch *b_truthSparticle_VtxMChParticles1GeV ; //! 
   TBranch *b_truthSparticle_VtxMChParticles1GeVd0 ; //! 
   TBranch *b_truthSparticle_VtxNChParticles ; //! 
   TBranch *b_truthSparticle_VtxNChParticles1GeV ; //! 
   TBranch *b_truthSparticle_VtxNChParticles1GeVd0 ; //! 
   TBranch *b_truthSparticle_VtxNParticles ; //!                
   TBranch *b_truthSparticle_VtxX ; //! 
   TBranch *b_truthSparticle_VtxY ; //! 
   TBranch *b_truthSparticle_VtxZ ; //! 
   TBranch *b_truthTrack_Charge ; //! 
   TBranch *b_truthTrack_Eta ; //! 
   TBranch *b_truthTrack_Parent ; //! 
   TBranch *b_truthTrack_ParentStatus ; //!
   TBranch *b_truthTrack_PdgId ; //! 
   TBranch *b_truthTrack_Phi ; //! 
   TBranch *b_truthTrack_Pt ; //! 
   TBranch *b_truthTrack_Status ; //! 
   TBranch *b_truthTrack_d0 ; //! 
        

   TBranch *b_truthParticle_Charge; //
   TBranch *b_truthParticle_Eta; //
   TBranch *b_truthParticle_PdgId; //
   TBranch *b_truthParticle_Phi; //
   TBranch *b_truthParticle_Pt; //     

   doHistos(TTree *tree=0,bool isMC=1);
   virtual ~doHistos();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree,bool isMC);
   virtual void     Loop(std::string s_sample);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   virtual float    getStopMass();
   //virtual float    getStopDisplacement();
   //virtual float    getStopDisplacementRxy();
   virtual float    recomputeDVmass(std::string s_sample, DV dv,  Muon mu);
   virtual int      isMuonDVLink(DV dv,  Muon mu);
   virtual int      getMuonDVLink(std::string s_sample, DV dv, std::vector<Muon> mus, float evt_wght);
   //virtual int      getMuonDVMatch(std::string s_sample, DV dv, std::vector<Muon> mus, float evt_wght);
   //virtual void     metEfficiencyStudy(std::string s_sample, std::vector<Muon> muons, float evt_wght);
   //virtual void     metEfficiencyPlots(std::string s_sample, std::string selection, float mu_pt, float mu_eta, float new_met, float evt_wght);
   //virtual void     makeCutflow(std::string s_sample, std::vector<Muon> mus, std::vector<DV> dvs, float evt_wght);
   virtual float    Z_mass();
   virtual bool     passZmumu();
   virtual int      getNcharge(float pt, float eta, float phi, float m, float dR); 


};

#endif

#ifdef doHistos_cxx
doHistos::doHistos(TTree *tree,bool isMC) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("signalSamples/lmdp211_CT100/data-trees/mc15_13TeV.402807.MGPy8EG_A14N23LO_SS_RPVDV_700_500_lamp211_100.recon.DAOD_RPVLL.e4332_s2608_s2183_r8788.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("signalSamples/lmdp211_CT100/data-trees/mc15_13TeV.402807.MGPy8EG_A14N23LO_SS_RPVDV_700_500_lamp211_100.recon.DAOD_RPVLL.e4332_s2608_s2183_r8788.root");
      }
      f->GetObject("trees_SRDV_",tree);

   }
   Init(tree,isMC);
}

doHistos::~doHistos()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t doHistos::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t doHistos::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void doHistos::Init(TTree *tree,bool isMC)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

  //std::cout << "init" <<std::endl;

   // Set object pointer
   DV_chisqPerDoF = 0;
   DV_index = 0;
   DV_lastCut = 0;
   DV_m = 0;
   DV_mass = 0;
   DV_mass_selected = 0;
   DV_nLRT = 0;
   DV_nTracks = 0;
   DV_r = 0;
   DV_rxy = 0;
   DV_x = 0;
   DV_y = 0;
   DV_z = 0;

   track_DVIndex = 0;
   track_index = 0;
   track_hitPattern = 0;
   track_RadFirstHit = 0;
   track_isLRT = 0;
   track_isAssociated = 0;
   track_d0 = 0;
   track_d0WrtDV = 0;
   track_errPt = 0;
   track_errd0 = 0;
   track_errd0WrtDV = 0;
   track_errz0 = 0;
   track_errz0WrtDV = 0;
   track_eta = 0;
   track_etaWrtDV = 0;
   track_phi = 0;
   track_phiWrtDV = 0;
   track_pt = 0;
   track_ptWrtDV = 0;
   track_z0 = 0;
   track_z0WrtDV = 0;
   track_NPixDeadSens = 0; 
   track_NPixHits = 0; 
   track_NPixHoles = 0; 
   track_NPixSharedHits = 0; 
   track_NSctDeadSens = 0; 
   track_NSctHits = 0; 
   track_NSctHoles = 0; 
   track_NSctSharedHits = 0; 
   track_NTrtHits = 0; 
   track_NTrtOutliers = 0; 

   track_truthMatchProb = 0;  
   track_truthOrigin = 0;  
   track_truthType = 0;  

   jet_BTag = 0;
   jet_M = 0;
   jet_Eta = 0;
   jet_Phi = 0;
   jet_Pt = 0;

   mstrack_D0 = 0;
   mstrack_ELoss = 0;
   mstrack_ELossSigma = 0;
   mstrack_MeasELoss = 0;
   mstrack_MeasELossSigma = 0;
   mstrack_muIndex = 0;
   mstrack_index = 0;
   mstrack_ParamELoss = 0;
   mstrack_ParamELossSigmaM = 0;
   mstrack_ParamELossSigmaP = 0;
   mstrack_Z0 = 0;
   mstrack_eta = 0;
   mstrack_nPres = 0;
   mstrack_nPresGood = 0;
   mstrack_nPresHole = 0;
   mstrack_phi = 0;
   mstrack_pt = 0;

   muon_CBchi2=0; 
   muon_DVindex=0; 
   muon_index=0; 
   muon_isLRT=0; 
   //muon_IDchi2 = 0;
   //muon_MEchi2 = 0;
   muon_QoverPsignif = 0;
   muon_TrigMatch = 0;
   muon_TrigMatchMSOnly = 0;
   muon_author = 0;
   muon_charge = 0;
   muon_d0 = 0;
   muon_eta = 0;
   muon_hasCBtrack = 0;
   muon_hasIDtrack = 0;
   muon_hasMEtrack = 0;
   muon_hasMStrack = 0;
   muon_isCommonGood = 0;
   muon_isSignal = 0;
   muon_nPIX = 0;
   muon_nPres = 0;
   muon_nPresGood = 0;
   muon_nPresHole = 0;
   muon_nSCT = 0;
   muon_nTRT = 0;
   muon_phi = 0;
   muon_pt = 0;
   muon_rho = 0;
   muon_truthOrigin = 0;
   muon_truthType = 0;
   muon_z0 = 0;
   muon_ptvarcone20 = 0;
   muon_ptvarcone30 = 0;
   muon_ptvarcone40 = 0;
   muon_ptcone20 = 0;
   muon_ptcone30 = 0;
   muon_ptcone40 = 0;
   muon_topoetcone20 = 0;
   muon_topoetcone30 = 0;
   muon_topoetcone40 = 0;

   muon_passCosmicAcceptance = 0; 
   muon_passCosmicVeto = 0; 
   muon_passFakeVeto = 0; 
   muon_passFullSelection = 0; 
   muon_passIsolation = 0; 
   muon_passPreselection = 0; 
   muon_passSegmentMatch = 0; 

   msSegment_chmbIndex = 0;        
   msSegment_clusTime = 0;       
   msSegment_clusTimeErr = 0;    
   msSegment_etaIndex = 0;         
   msSegment_index = 0;  
   msSegment_muIndex = 0;          
   msSegment_nPhiLays = 0;         
   msSegment_nPresHits = 0;        
   msSegment_nTrigEtaLays = 0;     
   msSegment_px = 0;             
   msSegment_py = 0;             
   msSegment_pz = 0;             
   msSegment_sector = 0;           
   msSegment_t0 = 0;             
   msSegment_t0Err = 0;          
   msSegment_tech = 0;             
   msSegment_x = 0;              
   msSegment_y = 0;              
   msSegment_z = 0;              


   tracklessJet_Eta = 0;
   tracklessJet_Phi = 0;
   tracklessJet_Pt = 0;
   tracklessJet_SumPtTrkPt500 = 0;

   //muDV_d0wrtSV = 0; 
   //muDV_dvIndex = 0; 
   //muDV_muIndex = 0; 
   //muDV_z0wrtSV = 0;

   idTrack_NPix_DeadSens = 0;  
   idTrack_NPix_Hits = 0;  
   idTrack_NPix_Holes = 0;  
   idTrack_NPix_ShrHits = 0;  
   idTrack_NSct_DeadSens = 0;  
   idTrack_NSct_Hits = 0;  
   idTrack_NSct_Holes = 0;  
   idTrack_NSct_ShrHits = 0;  
   idTrack_NTrt_Hits = 0;  
   idTrack_NTrt_Outliers = 0;  
   idTrack_RadFirstHit = 0;  
   idTrack_charge = 0;  
   idTrack_chi2 = 0;  
   idTrack_cosTag = 0;  
   idTrack_d0 = 0;  
   idTrack_errPt = 0;  
   idTrack_errd0 = 0;  
   idTrack_errz0 = 0;  
   idTrack_eta = 0;  
   idTrack_index = 0;  
   idTrack_isLRT = 0;  
   idTrack_phi = 0;  
   idTrack_pt = 0;  
   idTrack_theta = 0;  
   idTrack_z0 = 0;  
   idTrack_z0WrtPV = 0;   

   if (isMC){
   truthSparticle_BetaGamma = 0 ; 
   truthSparticle_Charge = 0 ; 
   truthSparticle_Eta = 0 ; 
   truthSparticle_M = 0 ; 
   truthSparticle_PdgId = 0 ; 
   truthSparticle_Phi = 0 ; 
   truthSparticle_ProperDecayTime = 0 ; 
   truthSparticle_Pt = 0 ; 
   truthSparticle_Status = 0 ; 
   truthSparticle_VtxMChParticles = 0 ; 
   truthSparticle_VtxMChParticles1GeV = 0 ; 
   truthSparticle_VtxMChParticles1GeVd0 = 0 ; 
   truthSparticle_VtxNChParticles = 0 ; 
   truthSparticle_VtxNChParticles1GeV = 0 ; 
   truthSparticle_VtxNChParticles1GeVd0 = 0 ; 
   truthSparticle_VtxNParticles = 0 ;                
   truthSparticle_VtxX = 0 ; 
   truthSparticle_VtxY = 0 ; 
   truthSparticle_VtxZ = 0 ; 
   truthTrack_Charge = 0 ; 
   truthTrack_Eta = 0 ; 
   truthTrack_Parent = 0 ; 
   truthTrack_ParentStatus = 0 ;
   truthTrack_PdgId = 0 ; 
   truthTrack_Phi = 0 ; 
   truthTrack_Pt = 0 ; 
   truthTrack_Status = 0 ; 
   truthTrack_d0 = 0 ; 

   truthParticle_Charge = 0;
   truthParticle_Eta = 0;
   truthParticle_PdgId = 0;
   truthParticle_Phi = 0;
   truthParticle_Pt = 0;    
 
   }
                



   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   //std::cout << "set branch addresses" <<std::endl;

   fChain->SetBranchAddress("passMETtrigger", &passMETtrigger, &b_passMETtrigger);
   fChain->SetBranchAddress("DV_n", &DV_n, &b_DV_n);
   fChain->SetBranchAddress("HT", &HT, &b_HT);
   fChain->SetBranchAddress("MET", &MET, &b_MET);
   fChain->SetBranchAddress("MET_phi", &MET_phi, &b_MET_phi);
   fChain->SetBranchAddress("MET_HLT", &MET_HLT, &b_MET_HLT);
   fChain->SetBranchAddress("MET_HLT_phi", &MET_HLT_phi, &b_MET_HLT_phi);
   fChain->SetBranchAddress("MET_LHT", &MET_LHT, &b_MET_LHT);
   fChain->SetBranchAddress("MET_LHT_phi", &MET_LHT_phi, &b_MET_LHT_phi);
   fChain->SetBranchAddress("MEff", &MEff, &b_MEff);
   fChain->SetBranchAddress("MHT_HLT", &MHT_HLT, &b_MHT_HLT);
   fChain->SetBranchAddress("MHT_HLT_phi", &MHT_HLT_phi, &b_MHT_HLT_phi);
   fChain->SetBranchAddress("NPV", &NPV, &b_NPV);
   fChain->SetBranchAddress("PV_nTracks", &PV_nTracks, &b_PV_nTracks);
   fChain->SetBranchAddress("PV_rxy", &PV_rxy, &b_PV_rxy);
   fChain->SetBranchAddress("PV_sumpT2", &PV_sumpT2, &b_PV_sumpT2);
   fChain->SetBranchAddress("PV_x", &PV_x, &b_PV_x);
   fChain->SetBranchAddress("PV_y", &PV_y, &b_PV_y);
   fChain->SetBranchAddress("PV_z", &PV_z, &b_PV_z);

   fChain->SetBranchAddress("WZweight", &WZweight, &b_WZweight);
   fChain->SetBranchAddress("actualInteractionsPerCrossing", &actualInteractionsPerCrossing, &b_actualInteractionsPerCrossing);
   fChain->SetBranchAddress("averageInteractionsPerCrossing", &averageInteractionsPerCrossing, &b_averageInteractionsPerCrossing);
   fChain->SetBranchAddress("bcid", &bcid, &b_bcid);
   fChain->SetBranchAddress("elSF", &elSF, &b_elSF);
   fChain->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain->SetBranchAddress("lumiBlock", &lumiBlock, &b_lumiBlock);

   if (isMC){
      fChain->SetBranchAddress("mcChannelNumber", &mcChannelNumber, &b_mcChannelNumber);
      fChain->SetBranchAddress("mcEventWeight", &mcEventWeight, &b_mcEventWeight);      
   }

   fChain->SetBranchAddress("muSF", &muSF, &b_muSF);
   fChain->SetBranchAddress("passHLTmsonly", &passHLTmsonly, &b_passHLTmsonly);
   fChain->SetBranchAddress("pileupReweightHash", &pileupReweightHash, &b_pileupReweightHash);
   fChain->SetBranchAddress("pileupWeight", &pileupWeight, &b_pileupWeight);
   fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);

   fChain->SetBranchAddress("DV_chisqPerDoF", &DV_chisqPerDoF, &b_DV_chisqPerDoF);
   fChain->SetBranchAddress("DV_index", &DV_index, &b_DV_index);
   fChain->SetBranchAddress("DV_lastCut", &DV_lastCut, &b_DV_lastCut);
   fChain->SetBranchAddress("DV_m", &DV_m, &b_DV_m);
   fChain->SetBranchAddress("DV_mass", &DV_mass, &b_DV_mass);
   fChain->SetBranchAddress("DV_mass_selected", &DV_mass_selected, &b_DV_mass_selected);
   fChain->SetBranchAddress("DV_nLRT", &DV_nLRT, &b_DV_nLRT);
   fChain->SetBranchAddress("DV_nTracks", &DV_nTracks, &b_DV_nTracks);
   fChain->SetBranchAddress("DV_r", &DV_r, &b_DV_r);
   fChain->SetBranchAddress("DV_rxy", &DV_rxy, &b_DV_rxy);
   fChain->SetBranchAddress("DV_x", &DV_x, &b_DV_x);
   fChain->SetBranchAddress("DV_y", &DV_y, &b_DV_y);
   fChain->SetBranchAddress("DV_z", &DV_z, &b_DV_z);

   fChain->SetBranchAddress("track_DVIndex", &track_DVIndex, &b_track_DVIndex);
   fChain->SetBranchAddress("track_index", &track_index, &b_track_index);
   fChain->SetBranchAddress("track_hitPattern", &track_hitPattern, &b_track_hitPattern);
   fChain->SetBranchAddress("track_RadFirstHit", &track_RadFirstHit, &b_track_RadFirstHit);
   fChain->SetBranchAddress("track_isLRT", &track_isLRT, &b_track_isLRT);
   fChain->SetBranchAddress("track_isAssociated", &track_isAssociated, &b_track_isAssociated);
   fChain->SetBranchAddress("track_d0", &track_d0, &b_track_d0);
   fChain->SetBranchAddress("track_d0WrtDV", &track_d0WrtDV, &b_track_d0WrtDV);
   fChain->SetBranchAddress("track_errPt", &track_errPt, &b_track_errPt);
   fChain->SetBranchAddress("track_errd0", &track_errd0, &b_track_errd0);
   fChain->SetBranchAddress("track_errd0WrtDV", &track_errd0WrtDV, &b_track_errd0WrtDV);
   fChain->SetBranchAddress("track_errz0", &track_errz0, &b_track_errz0);
   fChain->SetBranchAddress("track_errz0WrtDV", &track_errz0WrtDV, &b_track_errz0WrtDV);
   fChain->SetBranchAddress("track_eta", &track_eta, &b_track_eta);
   fChain->SetBranchAddress("track_etaWrtDV", &track_etaWrtDV, &b_track_etaWrtDV);
   fChain->SetBranchAddress("track_phi", &track_phi, &b_track_phi);
   fChain->SetBranchAddress("track_phiWrtDV", &track_phiWrtDV, &b_track_phiWrtDV);
   fChain->SetBranchAddress("track_pt", &track_pt, &b_track_pt);
   fChain->SetBranchAddress("track_ptWrtDV", &track_ptWrtDV, &b_track_ptWrtDV);
   fChain->SetBranchAddress("track_z0", &track_z0, &b_track_z0);
   fChain->SetBranchAddress("track_z0WrtDV", &track_z0WrtDV, &b_track_z0WrtDV);
   fChain->SetBranchAddress("track_NPixDeadSens", &track_NPixDeadSens, &b_track_NPixDeadSens); 
   fChain->SetBranchAddress("track_NPixHits", &track_NPixHits, &b_track_NPixHits); 
   fChain->SetBranchAddress("track_NPixHoles", &track_NPixHoles, &b_track_NPixHoles); 
   fChain->SetBranchAddress("track_NPixSharedHits", &track_NPixSharedHits, &b_track_NPixSharedHits); 
   fChain->SetBranchAddress("track_NSctDeadSens", &track_NSctDeadSens, &b_track_NSctDeadSens); 
   fChain->SetBranchAddress("track_NSctHits", &track_NSctHits, &b_track_NSctHits); 
   fChain->SetBranchAddress("track_NSctHoles", &track_NSctHoles, &b_track_NSctHoles); 
   fChain->SetBranchAddress("track_NSctSharedHits", &track_NSctSharedHits, &b_track_NSctSharedHits); 
   fChain->SetBranchAddress("track_NTrtHits", &track_NTrtHits, &b_track_NTrtHits); 
   fChain->SetBranchAddress("track_NTrtOutliers", &track_NTrtOutliers, &b_track_NTrtOutliers); 

   fChain->SetBranchAddress("jet_Eta", &jet_Eta, &b_jet_Eta);
   fChain->SetBranchAddress("jet_Phi", &jet_Phi, &b_jet_Phi);
   fChain->SetBranchAddress("jet_BTag", &jet_BTag, &b_jet_BTag);
   fChain->SetBranchAddress("jet_M", &jet_M, &b_jet_M);
   fChain->SetBranchAddress("jet_Pt", &jet_Pt, &b_jet_Pt);

   fChain->SetBranchAddress("mstrack_D0", &mstrack_D0, &b_mstrack_D0);
   fChain->SetBranchAddress("mstrack_ELoss", &mstrack_ELoss, &b_mstrack_ELoss);
   fChain->SetBranchAddress("mstrack_ELossSigma", &mstrack_ELossSigma, &b_mstrack_ELossSigma);
   fChain->SetBranchAddress("mstrack_MeasELoss", &mstrack_MeasELoss, &b_mstrack_MeasELoss);
   fChain->SetBranchAddress("mstrack_MeasELossSigma", &mstrack_MeasELossSigma, &b_mstrack_MeasELossSigma);
   //fChain->SetBranchAddress("mstrack_muIndex", &mstrack_muIndex, &b_mstrack_muIndex);
   //fChain->SetBranchAddress("mstrack_index", &mstrack_index, &b_mstrack_index);
   fChain->SetBranchAddress("mstrack_ParamELoss", &mstrack_ParamELoss, &b_mstrack_ParamELoss);
   fChain->SetBranchAddress("mstrack_ParamELossSigmaM", &mstrack_ParamELossSigmaM, &b_mstrack_ParamELossSigmaM);
   fChain->SetBranchAddress("mstrack_ParamELossSigmaP", &mstrack_ParamELossSigmaP, &b_mstrack_ParamELossSigmaP);
   fChain->SetBranchAddress("mstrack_Z0", &mstrack_Z0, &b_mstrack_Z0);
   fChain->SetBranchAddress("mstrack_eta", &mstrack_eta, &b_mstrack_eta);
   fChain->SetBranchAddress("mstrack_nPres", &mstrack_nPres, &b_mstrack_nPres);
   fChain->SetBranchAddress("mstrack_nPresGood", &mstrack_nPresGood, &b_mstrack_nPresGood);
   fChain->SetBranchAddress("mstrack_nPresHole", &mstrack_nPresHole, &b_mstrack_nPresHole);
   fChain->SetBranchAddress("mstrack_phi", &mstrack_phi, &b_mstrack_phi);
   fChain->SetBranchAddress("mstrack_pt", &mstrack_pt, &b_mstrack_pt);

   fChain->SetBranchAddress("muon_CBchi2", &muon_CBchi2, &b_muon_CBchi2) ;
   fChain->SetBranchAddress("muon_DVindex", &muon_DVindex, &b_muon_DVindex) ;
   fChain->SetBranchAddress("muon_index", &muon_index, &b_muon_index) ;
   fChain->SetBranchAddress("muon_isLRT", &muon_isLRT, &b_muon_isLRT) ;
   //fChain->SetBranchAddress("muon_IDchi2", &muon_IDchi2, &b_muon_IDchi2);
   //fChain->SetBranchAddress("muon_MEchi2", &muon_MEchi2, &b_muon_MEchi2);
   fChain->SetBranchAddress("muon_QoverPsignif", &muon_QoverPsignif, &b_muon_QoverPsignif);
   fChain->SetBranchAddress("muon_TrigMatch", &muon_TrigMatch, &b_muon_TrigMatch);
   fChain->SetBranchAddress("muon_TrigMatchMSOnly", &muon_TrigMatchMSOnly, &b_muon_TrigMatchMSOnly);
   fChain->SetBranchAddress("muon_author", &muon_author, &b_muon_author);
   fChain->SetBranchAddress("muon_charge", &muon_charge, &b_muon_charge);
   fChain->SetBranchAddress("muon_d0", &muon_d0, &b_muon_d0);
   fChain->SetBranchAddress("muon_eta", &muon_eta, &b_muon_eta);
   fChain->SetBranchAddress("muon_hasCBtrack", &muon_hasCBtrack, &b_muon_hasCBtrack);
   fChain->SetBranchAddress("muon_hasIDtrack", &muon_hasIDtrack, &b_muon_hasIDtrack);
   fChain->SetBranchAddress("muon_hasMEtrack", &muon_hasMEtrack, &b_muon_hasMEtrack);
   fChain->SetBranchAddress("muon_hasMStrack", &muon_hasMStrack, &b_muon_hasMStrack);
   fChain->SetBranchAddress("muon_isCommonGood", &muon_isCommonGood, &b_muon_isCommonGood);
   fChain->SetBranchAddress("muon_isSignal", &muon_isSignal, &b_muon_isSignal);
   fChain->SetBranchAddress("muon_nPIX", &muon_nPIX, &b_muon_nPIX);
   fChain->SetBranchAddress("muon_nPres", &muon_nPres, &b_muon_nPres);
   fChain->SetBranchAddress("muon_nPresGood", &muon_nPresGood, &b_muon_nPresGood);
   fChain->SetBranchAddress("muon_nPresHole", &muon_nPresHole, &b_muon_nPresHole);
   fChain->SetBranchAddress("muon_nSCT", &muon_nSCT, &b_muon_nSCT);
   fChain->SetBranchAddress("muon_nTRT", &muon_nTRT, &b_muon_nTRT);
   fChain->SetBranchAddress("muon_phi", &muon_phi, &b_muon_phi);
   fChain->SetBranchAddress("muon_pt", &muon_pt, &b_muon_pt);
   fChain->SetBranchAddress("muon_rho", &muon_rho, &b_muon_rho);
   fChain->SetBranchAddress("muon_truthOrigin", &muon_truthOrigin, &b_muon_truthOrigin);
   fChain->SetBranchAddress("muon_truthType", &muon_truthType, &b_muon_truthType);
   fChain->SetBranchAddress("muon_z0", &muon_z0, &b_muon_z0);
   fChain->SetBranchAddress("muon_ptvarcone20", &muon_ptvarcone20, &b_muon_ptvarcone20); 
   fChain->SetBranchAddress("muon_ptvarcone30", &muon_ptvarcone30, &b_muon_ptvarcone30); 
   fChain->SetBranchAddress("muon_ptvarcone40", &muon_ptvarcone40, &b_muon_ptvarcone40); 
   fChain->SetBranchAddress("muon_ptcone20", &muon_ptcone20, &b_muon_ptcone20); 
   fChain->SetBranchAddress("muon_ptcone30", &muon_ptcone30, &b_muon_ptcone30); 
   fChain->SetBranchAddress("muon_ptcone40", &muon_ptcone40, &b_muon_ptcone40); 
   fChain->SetBranchAddress("muon_topoetcone20", &muon_topoetcone20, &b_muon_topoetcone20); 
   fChain->SetBranchAddress("muon_topoetcone30", &muon_topoetcone30, &b_muon_topoetcone30); 
   fChain->SetBranchAddress("muon_topoetcone40", &muon_topoetcone40, &b_muon_topoetcone40); 

   fChain->SetBranchAddress("muon_passCosmicAcceptance", &muon_passCosmicAcceptance, &b_muon_passCosmicAcceptance); 
   fChain->SetBranchAddress("muon_passCosmicVeto", &muon_passCosmicVeto, &b_muon_passCosmicVeto); 
   fChain->SetBranchAddress("muon_passFakeVeto", &muon_passFakeVeto, &b_muon_passFakeVeto); 
   fChain->SetBranchAddress("muon_passFullSelection", &muon_passFullSelection, &b_muon_passFullSelection); 
   fChain->SetBranchAddress("muon_passIsolation", &muon_passIsolation, &b_muon_passIsolation); 
   fChain->SetBranchAddress("muon_passPreselection", &muon_passPreselection, &b_muon_passPreselection); 
   fChain->SetBranchAddress("muon_passSegmentMatch", &muon_passSegmentMatch, &b_muon_passSegmentMatch); 

   fChain->SetBranchAddress("msSegment_chmbIndex", &msSegment_chmbIndex, &b_msSegment_chmbIndex);        
   fChain->SetBranchAddress("msSegment_clusTime", &msSegment_clusTime, &b_msSegment_clusTime);       
   //fChain->SetBranchAddress("msSegment_clusTimeErr", &msSegment_clusTimeErr, &b_msSegment_clusTimeErr);    
   fChain->SetBranchAddress("msSegment_etaIndex", &msSegment_etaIndex, &b_msSegment_etaIndex);         
   //fChain->SetBranchAddress("msSegment_index", &msSegment_index, &b_msSegment_index);  
   //fChain->SetBranchAddress("msSegment_muIndex", &msSegment_muIndex, &b_msSegment_muIndex);          
   fChain->SetBranchAddress("msSegment_nPhiLays", &msSegment_nPhiLays, &b_msSegment_nPhiLays);         
   fChain->SetBranchAddress("msSegment_nPresHits", &msSegment_nPresHits, &b_msSegment_nPresHits);        
   fChain->SetBranchAddress("msSegment_nTrigEtaLays", &msSegment_nTrigEtaLays, &b_msSegment_nTrigEtaLays);     
   //fChain->SetBranchAddress("msSegment_px", &msSegment_px, &b_msSegment_px);             
   //fChain->SetBranchAddress("msSegment_py", &msSegment_py, &b_msSegment_py);             
   //fChain->SetBranchAddress("msSegment_pz", &msSegment_pz, &b_msSegment_pz);             
   fChain->SetBranchAddress("msSegment_sector", &msSegment_sector, &b_msSegment_sector);           
   fChain->SetBranchAddress("msSegment_t0", &msSegment_t0, &b_msSegment_t0);             
   //fChain->SetBranchAddress("msSegment_t0Err", &msSegment_t0Err, &b_msSegment_t0Err);          
   //fChain->SetBranchAddress("msSegment_tech", &msSegment_tech, &b_msSegment_tech);             
   fChain->SetBranchAddress("msSegment_x", &msSegment_x, &b_msSegment_x);              
   fChain->SetBranchAddress("msSegment_y", &msSegment_y, &b_msSegment_y);              
   fChain->SetBranchAddress("msSegment_z", &msSegment_z, &b_msSegment_z);              

   //fChain->SetBranchAddress("tracklessJet_Eta", &tracklessJet_Eta, &b_tracklessJet_Eta);
   //fChain->SetBranchAddress("tracklessJet_Phi", &tracklessJet_Phi, &b_tracklessJet_Phi);
   //fChain->SetBranchAddress("tracklessJet_Pt", &tracklessJet_Pt, &b_tracklessJet_Pt);
   //fChain->SetBranchAddress("tracklessJet_SumPtTrkPt500", &tracklessJet_SumPtTrkPt500, &b_tracklessJet_SumPtTrkPt500);

   //fChain->SetBranchAddress("muDV_d0wrtSV", &muDV_d0wrtSV, &b_muDV_d0wrtSV); 
   //fChain->SetBranchAddress("muDV_dvIndex", &muDV_dvIndex, &b_muDV_dvIndex); 
   //fChain->SetBranchAddress("muDV_muIndex", &muDV_muIndex, &b_muDV_muIndex); 
   //fChain->SetBranchAddress("muDV_z0wrtSV", &muDV_z0wrtSV, &b_muDV_z0wrtSV);

   fChain->SetBranchAddress("idTrack_NPix_DeadSens", &idTrack_NPix_DeadSens, &b_idTrack_NPix_DeadSens);   
   fChain->SetBranchAddress("idTrack_NPix_Hits", &idTrack_NPix_Hits, &b_idTrack_NPix_Hits);   
   fChain->SetBranchAddress("idTrack_NPix_Holes", &idTrack_NPix_Holes, &b_idTrack_NPix_Holes);   
   fChain->SetBranchAddress("idTrack_NPix_ShrHits", &idTrack_NPix_ShrHits, &b_idTrack_NPix_ShrHits);   
   fChain->SetBranchAddress("idTrack_NSct_DeadSens", &idTrack_NSct_DeadSens, &b_idTrack_NSct_DeadSens);   
   fChain->SetBranchAddress("idTrack_NSct_Hits", &idTrack_NSct_Hits, &b_idTrack_NSct_Hits);   
   fChain->SetBranchAddress("idTrack_NSct_Holes", &idTrack_NSct_Holes, &b_idTrack_NSct_Holes);   
   fChain->SetBranchAddress("idTrack_NSct_ShrHits", &idTrack_NSct_ShrHits, &b_idTrack_NSct_ShrHits);   
   fChain->SetBranchAddress("idTrack_NTrt_Hits", &idTrack_NTrt_Hits, &b_idTrack_NTrt_Hits);   
   fChain->SetBranchAddress("idTrack_NTrt_Outliers", &idTrack_NTrt_Outliers, &b_idTrack_NTrt_Outliers);   
   fChain->SetBranchAddress("idTrack_RadFirstHit", &idTrack_RadFirstHit, &b_idTrack_RadFirstHit);   
   fChain->SetBranchAddress("idTrack_charge", &idTrack_charge, &b_idTrack_charge);   
   fChain->SetBranchAddress("idTrack_chi2", &idTrack_chi2, &b_idTrack_chi2);   
   fChain->SetBranchAddress("idTrack_cosTag", &idTrack_cosTag, &b_idTrack_cosTag);   
   fChain->SetBranchAddress("idTrack_d0", &idTrack_d0, &b_idTrack_d0);   
   fChain->SetBranchAddress("idTrack_errPt", &idTrack_errPt, &b_idTrack_errPt);   
   fChain->SetBranchAddress("idTrack_errd0", &idTrack_errd0, &b_idTrack_errd0);   
   fChain->SetBranchAddress("idTrack_errz0", &idTrack_errz0, &b_idTrack_errz0);   
   fChain->SetBranchAddress("idTrack_eta", &idTrack_eta, &b_idTrack_eta);   
   fChain->SetBranchAddress("idTrack_index", &idTrack_index, &b_idTrack_index);   
   fChain->SetBranchAddress("idTrack_isLRT", &idTrack_isLRT, &b_idTrack_isLRT);   
   fChain->SetBranchAddress("idTrack_phi", &idTrack_phi, &b_idTrack_phi);   
   fChain->SetBranchAddress("idTrack_pt", &idTrack_pt, &b_idTrack_pt);   
   fChain->SetBranchAddress("idTrack_theta", &idTrack_theta, &b_idTrack_theta);   
   fChain->SetBranchAddress("idTrack_z0", &idTrack_z0, &b_idTrack_z0);   
   fChain->SetBranchAddress("idTrack_z0WrtPV", &idTrack_z0WrtPV, &b_idTrack_z0WrtPV);    

   if (isMC){
      fChain->SetBranchAddress("track_truthMatchProb", &track_truthMatchProb, &b_track_truthMatchProb);
      fChain->SetBranchAddress("track_truthOrigin", &track_truthOrigin, &b_track_truthOrigin);
      fChain->SetBranchAddress("track_truthType", &track_truthType, &b_track_truthType);


      fChain->SetBranchAddress("truthSparticle_BetaGamma" ,&truthSparticle_BetaGamma, &b_truthSparticle_BetaGamma) ; 
      fChain->SetBranchAddress("truthSparticle_Charge" ,&truthSparticle_Charge, &b_truthSparticle_Charge) ; 
      fChain->SetBranchAddress("truthSparticle_Eta" ,&truthSparticle_Eta, &b_truthSparticle_Eta) ; 
      fChain->SetBranchAddress("truthSparticle_M" ,&truthSparticle_M, &b_truthSparticle_M) ; 
      fChain->SetBranchAddress("truthSparticle_PdgId" ,&truthSparticle_PdgId, &b_truthSparticle_PdgId) ; 
      fChain->SetBranchAddress("truthSparticle_Phi" ,&truthSparticle_Phi, &b_truthSparticle_Phi) ; 
      fChain->SetBranchAddress("truthSparticle_ProperDecayTime" ,&truthSparticle_ProperDecayTime, &b_truthSparticle_ProperDecayTime) ; 
      fChain->SetBranchAddress("truthSparticle_Pt" ,&truthSparticle_Pt, &b_truthSparticle_Pt) ; 
      fChain->SetBranchAddress("truthSparticle_Status" ,&truthSparticle_Status, &b_truthSparticle_Status) ; 
      fChain->SetBranchAddress("truthSparticle_VtxMChParticles" ,&truthSparticle_VtxMChParticles, &b_truthSparticle_VtxMChParticles) ; 
      fChain->SetBranchAddress("truthSparticle_VtxMChParticles1GeV" ,&truthSparticle_VtxMChParticles1GeV, &b_truthSparticle_VtxMChParticles1GeV) ; 
      fChain->SetBranchAddress("truthSparticle_VtxMChParticles1GeVd0" ,&truthSparticle_VtxMChParticles1GeVd0, &b_truthSparticle_VtxMChParticles1GeVd0) ; 
      fChain->SetBranchAddress("truthSparticle_VtxNChParticles" ,&truthSparticle_VtxNChParticles, &b_truthSparticle_VtxNChParticles) ; 
      fChain->SetBranchAddress("truthSparticle_VtxNChParticles1GeV" ,&truthSparticle_VtxNChParticles1GeV, &b_truthSparticle_VtxNChParticles1GeV) ; 
      fChain->SetBranchAddress("truthSparticle_VtxNChParticles1GeVd0" ,&truthSparticle_VtxNChParticles1GeVd0, &b_truthSparticle_VtxNChParticles1GeVd0) ; 
      fChain->SetBranchAddress("truthSparticle_VtxNParticles" ,&truthSparticle_VtxNParticles, &b_truthSparticle_VtxNParticles) ;                
      fChain->SetBranchAddress("truthSparticle_VtxX" ,&truthSparticle_VtxX, &b_truthSparticle_VtxX) ; 
      fChain->SetBranchAddress("truthSparticle_VtxY" ,&truthSparticle_VtxY, &b_truthSparticle_VtxY) ; 
      fChain->SetBranchAddress("truthSparticle_VtxZ" ,&truthSparticle_VtxZ, &b_truthSparticle_VtxZ) ; 
      fChain->SetBranchAddress("truthTrack_Charge" ,&truthTrack_Charge, &b_truthTrack_Charge) ; 
      fChain->SetBranchAddress("truthTrack_Eta" ,&truthTrack_Eta, &b_truthTrack_Eta) ; 
      fChain->SetBranchAddress("truthTrack_Parent" ,&truthTrack_Parent, &b_truthTrack_Parent) ; 
      fChain->SetBranchAddress("truthTrack_ParentStatus", &truthTrack_ParentStatus, &b_truthTrack_ParentStatus);
      fChain->SetBranchAddress("truthTrack_PdgId" ,&truthTrack_PdgId, &b_truthTrack_PdgId) ; 
      fChain->SetBranchAddress("truthTrack_Phi" ,&truthTrack_Phi, &b_truthTrack_Phi) ; 
      fChain->SetBranchAddress("truthTrack_Pt" ,&truthTrack_Pt, &b_truthTrack_Pt) ; 
      fChain->SetBranchAddress("truthTrack_Status" ,&truthTrack_Status, &b_truthTrack_Status) ; 
      fChain->SetBranchAddress("truthTrack_d0" ,&truthTrack_d0, &b_truthTrack_d0) ; 

      //fChain->SetBranchAddress("truthParticle_Charge", &truthParticle_Charge, &b_truthParticle_Charge );
      //fChain->SetBranchAddress("truthParticle_Eta", &truthParticle_Eta, &b_truthParticle_Eta );
      //fChain->SetBranchAddress("truthParticle_PdgId", &truthParticle_PdgId, &b_truthParticle_PdgId );
      //fChain->SetBranchAddress("truthParticle_Phi", &truthParticle_Phi, &b_truthParticle_Phi );
      //fChain->SetBranchAddress("truthParticle_Pt", &truthParticle_Pt, &b_truthParticle_Pt );
   }

   Notify();

}

Bool_t doHistos::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void doHistos::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t doHistos::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef doHistos_cxx
