#ifndef physicsObjects_h
#define physicsObjects_h

// Structures for physics objects that don't require doHistos class 
// Useful for packing up n-tuple variables for a single muon
// Can loop through muons more easily to figure 
       
struct Segment {
  unsigned int index;
  TLorentzVector p4;  
  float t0; 
  float clusTime; 

  float x; 
  float y; 
  float z; 

  float muIndex; 
  float nPhiLays; 
  float nPresHits; 
  float nTrigEtaLays; 

  float chmbIndex;
  float etaIndex; 
  float sector;  
  float tech;  
};      
struct Muon {   
   unsigned int index;
   TLorentzVector p4;    
    
   float d0;      
   float z0;      
   float z0corr;      
   float eta;     
   float phi;     
   float pt;  
       
   float nPIX;    
   float nSCT;    
   float nTRT;    
   float DVindex; 
   float author;  
   float TM;      
   float TMmsonly;
   float weight;

   float ptvarcone20;
   float ptvarcone30;
   float ptvarcone40;
   float ptcone20; 
   float ptcone30; 
   float ptcone40; 
   float topoetcone20;
   float topoetcone30;
   float topoetcone40;

   float nPres;
   float nPresGood;
   float nPresHole;

   float dRjet;
   float dRcos;

   float CBchi2; 
   float rho;
   float qOverP; 

   //FOR TESTING
   bool testpassCosmicAcceptance; 
   bool testpassCosmicVeto; 
   bool testpassFakeVeto; 
   bool testpassFullSelection; 
   bool testpassIsolation; 
   bool testpassPreselection; 
   bool testpassSegmentMatch; 

   //CAREFUL NOT CONSECUTIVE
   bool isLeading;
   bool passPreSel;
   bool passFullSel;
   bool passCosVetoTight;
   bool passCosVetoLoose;
   bool passFakeVetoTight;
   bool passFakeVetoLoose;
   bool passFixedCutLoose;
   bool passPt62;   
   bool passPt25;   
   bool passEta2p5;  
   bool passEta1p7;  
   bool passD0;   
   bool passZ0;   
   bool passTM;   
   bool passID; 

   int truth_match;  
};
struct MSTrack {
  unsigned int index;
  TLorentzVector p4; 
  float d0 ;      
  float z0 ;      
  float eta;      
  float phi;      
  float pt ;      
  float MuonIndex;
  float nPres;
  float nPresHole;
  float nPresGood;
  float weight;
};
struct Jet {
   float m;
   float eta;
   float phi;
   float pt;
   float nch_02;
   float nch_04;
};
struct Track {
   unsigned int index;
   TLorentzVector p4; 
   TLorentzVector p4_wrtDV; 
   float DVIndex;
   float charge;
   float RadFirstHit;
   float d0;
   float d0WrtDV;
   float errPt;
   float errd0;
   float errd0WrtDV;
   float errz0;
   float errz0WrtDV;
   float eta;
   float etaWrtDV;
   float phi;
   float phiWrtDV;
   float pt;
   float ptWrtDV;
   float z0;
   float z0WrtDV;
   int isAssociated;

   int NPixDeadSens;  
   int NPixHits;  
   int NPixHoles;  
   int NPixSharedHits;  
   int NSctDeadSens;  
   int NSctHits;  
   int NSctHoles;  
   int NSctSharedHits;  
   int NTrtHits;  
   int NTrtOutliers;  

   float truthMatchProb; 
   float truthOrigin; 
   float truthType; 

   float weight;
};
struct DV {
  unsigned int index;
  TLorentzVector p4; 
  float lastCut;
  float chi2   ;
  float m      ;
  float nLRT   ;
  float nTracks;
  float r      ;
  float rxy    ;
  float x      ;
  float y      ;
  float z      ;
  float phi    ;
  std::vector<Track> tracks;
  float weight ;

  // CAREFUL NOT CONSECUTIVE
  bool passFiducialCuts;
  bool passChisqCut;   
  bool passDistCut;    
  bool passMaterialVeto;
  bool passMassCut;       
  bool passMassCut5;       
  bool passMassCut10;       
  bool passNtrackCut; 
  bool passNtrackCut3; 
  bool passNtrackCut4; 
  bool passNtrackCut5; 
  bool passMuonLink;  

  int truth_match;
  ;    
};


struct IDTrack{
   unsigned int index;
   TLorentzVector p4; 
   float nPix;         
   float nSct;         
   float nTrt;         
   float charge;         
   float chi2;         
   float d0;         
   float eta;         
   float phi;         
   float pt;         
   float theta;         
   float z0;         
   float z0WrtPV;  
};   

struct TruthVertex {
  unsigned int index;

  float pdgId  ;
  float status  ;

  float m      ;
  float mCh    ;
  float mCh1GeV;
  float mCh1GeVd0;
  float mCh1GeVd0dist;
  float mCh1GeVd0distReco;
  
  float n      ;
  float nCh    ;
  float nCh1GeV;
  float nCh1GeVd0;
  float nCh1GeVd0dist;
  float nCh1GeVd0distReco;

  float r      ;
  float rxy    ;
  float x      ;
  float y      ;
  float z      ;
  float phi    ;
  float weight ;

  int reco_match;
};

struct TruthMuon {
  unsigned int index;
  float pdgId  ;
  float status  ;
  float pt; 
  float eta;
  float phi;
  float d0;
  float prod_X;
  float prod_Y;
  float prod_Z;
  float pstatus;
  float parent;
  float charge;
  float weight;

  bool isLeading;   // is leading truth muon in event w/in acceptance (pt > 25, eta, d0)
  //bool isLeadingRH; // is leading muon from single RH 
  TLorentzVector p4; 

  int reco_match;
};

// Define New MET for trigger efficiency
float get_MET_with_Muons( std::vector<Muon> mus, float met, float met_phi){

	TLorentzVector mu_met_4vec; // 4 vector of muons w/ pT >25 GeV & |eta|<2.5, and isolated
	
	for (auto mu : mus){
		if (mu.pt > 25 && fabs(mu.eta) < 2.5 && mu.ptvarcone30/mu.pt < 0.15 && mu.topoetcone20/mu.pt < 0.3){
			mu_met_4vec += mu.p4;
      //std::cout << "muon: pt " << mu.pt << " : phi " << mu.phi << std::endl;
		}
	}
	
	TVector2 mu_2;
	mu_2.Set(mu_met_4vec.Px(),mu_met_4vec.Py());
	TVector2 met_2;
	met_2.SetMagPhi(met,met_phi);

	float new_met  = (met_2+mu_2).Mod();

  //std::cout << " old met: pt " << met << " : phi " << met_phi << std::endl; 
  //std::cout << " new met: pt " << (met_2+mu_2).Mod() << " : phi " << (met_2+mu_2).Phi() << std::endl; 

	return new_met;
}



#endif