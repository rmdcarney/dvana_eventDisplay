#include <numeric>
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

#include <TFile.h>
#include <TTree.h>
#include <TLeaf.h>
#include <TH1F.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <TROOT.h>

//============================
// E N U M   D E T   T Y P E
//============================
enum DetectorType {
    
    pixelBarrel0 = 0, //!< there are three or four pixel barrel layers (R1/R2)
    pixelBarrel1 = 1,
    pixelBarrel2 = 2,
    pixelBarrel3 = 3,
 
    pixelEndCap0 = 4, //!< three pixel discs (on each side)
    pixelEndCap1 = 5,
    pixelEndCap2 = 6,
 
    sctBarrel0   = 7, //!< four sct barrel layers
    sctBarrel1   = 8,
    sctBarrel2   = 9,
    sctBarrel3   = 10,
 
    sctEndCap0   = 11, //!< and 9 sct discs (on each side)
    sctEndCap1   = 12,
    sctEndCap2   = 13,
    sctEndCap3   = 14,
    sctEndCap4   = 15,
    sctEndCap5   = 16,
    sctEndCap6   = 17,
    sctEndCap7   = 18,
    sctEndCap8   = 19,
 
    trtBarrel    = 20,
    trtEndCap    = 21,
 
    DBM0 = 22,
    DBM1 = 23,
    DBM2 = 24,
 
    numberOfDetectorTypes = 25
 
  };

//============================
// H A S   H I T
//============================
inline bool hasHit( const uint32_t& pattern, enum DetectorType layer ) { return ( pattern & ( 1<<layer ) ); }


//============================
// D A T A  O B J
//============================
class DataObj {
public:
 
  //&&&&&&&&&&&&&&&&&
  // Member vars
  //&&&&&&&&&&&&&&&&&
  std::string name;
  std::string tree_name;
  
  TFile *file;
  TTree *tree;
  
  long long int entry;
  
  //int eventCount;
  long eventNumber;
  int runNumber;
  int nSelectedTracks;
  std::vector<float>* trk_d0;
  std::vector<float>* trk_z0;
  std::vector<float>* trk_pt;
  std::vector<float>* trk_eta;
  std::vector<float>* trk_phi;

  std::vector<float>* muon_d0;
  std::vector<float>* muon_z0;
  std::vector<float>* muon_pt;
  std::vector<float>* muon_eta;
  std::vector<float>* muon_phi;
  std::vector<int>  * muon_charge;

  //std::vector<unsigned int>*   trk_selected;
  std::vector<float>* vtx_r;
  std::vector<float>* vtx_rxy;
  std::vector<float>* vtx_z;
  std::vector<float>* vtx_x;
  std::vector<float>* vtx_y;
  std::vector<unsigned long> * vtx_index;
  std::vector<float>* vtx_phi;
  std::vector<float>* vtx_mass;
  std::vector<float>* vtx_chi2;
  std::vector<float>* vtx_direction;
  std::vector<float>* vtx_pt;
  std::vector<float>* vtx_minOpAng;
  std::vector<unsigned int>* vtx_ntrk;
  std::vector<int> * vtx_trk_charge;
  std::vector<float> * vtx_trk_pt;
  std::vector<float> * vtx_trk_eta;
  std::vector<float> * vtx_trk_phi;
  std::vector<float> * vtx_trk_d0;
  std::vector<float> * vtx_trk_z0;
  std::vector<double> * vtx_trk_pt_wrtSV;
  std::vector<float> * vtx_trk_eta_wrtSV;
  std::vector<float> * vtx_trk_phi_wrtSV;
  std::vector<float> * vtx_trk_d0_wrtSV;
  std::vector<float> * vtx_trk_z0_wrtSV;
  std::vector<unsigned char> * vtx_trk_nSCTHits;
  std::vector<unsigned char> * vtx_trk_nTRTHits;
  std::vector<unsigned int> * vtx_trk_hitPattern;
  std::vector<unsigned char> * vtx_trk_isAssociated;
  std::vector<unsigned long> * vtx_trk_vtx_index;
  
  std::vector<float>* truth_vtx_r;
  std::vector<float>* truth_vtx_z;
  std::vector<float>* truth_vtx_phi;
  
  std::vector<std::vector<float> >* truth_vtx_trk_pt;
  std::vector<std::vector<float> >* truth_vtx_trk_eta;
  std::vector<std::vector<float> >* truth_vtx_trk_phi;
  
  TH1F *hvtx_r;
  TH1F *hvtx_z;
  TH1F *hvtx_mass;
  TH1F *hvtx_pt;
  TH1F *hvtx_HT;
  TH1F *hvtx_beta;
  TH1F *hvtx_HTratio;
  TH1F *hvtx_ntrk;
  TH1F *hvtx_chi2;
  TH1F *hvtx_r_n3;
  TH1F *hvtx_minOpAng;
  TH1F *hdir;
  TH1F *hScore;
  
  TH1F *htrk_d0;
  TH1F *htrk_z0;
  TH1F *htrk_pt;
  TH1F *htrk_eta;
  TH1F *htrk_phi;
  TH1F *htrk_d0_matched;
  TH1F *htrk_z0_matched;
  TH1F *htrk_pt_matched;
  TH1F *htrk_eta_matched;
  TH1F *htrk_phi_matched;
  
  TBranch* b_trk_d0;
  TBranch* b_trk_z0;
  TBranch* b_trk_pt;
  TBranch* b_trk_eta;
  TBranch* b_trk_phi;
  
  TBranch* b_muon_d0;
  TBranch* b_muon_z0;
  TBranch* b_muon_pt;
  TBranch* b_muon_eta;
  TBranch* b_muon_phi;
  TBranch* b_muon_charge;

  //TBranch* b_trk_selected;
  TBranch* b_vtx_r;
  TBranch* b_vtx_rxy;
  TBranch* b_vtx_z;
  TBranch* b_vtx_x;
  TBranch* b_vtx_y;
  TBranch* b_vtx_index;
  TBranch* b_vtx_phi;
  TBranch* b_vtx_mass;
  TBranch* b_vtx_chi2;
  TBranch* b_vtx_direction;
  TBranch* b_vtx_trk_charge;
  TBranch* b_vtx_pt;
  TBranch* b_vtx_minOpAng;
  TBranch* b_vtx_ntrk;
  TBranch* b_vtx_trk_pt;
  TBranch* b_vtx_trk_eta;
  TBranch* b_vtx_trk_phi;
  TBranch* b_vtx_trk_d0;
  TBranch* b_vtx_trk_z0;
  TBranch* b_vtx_trk_d0_wrtSV;
  TBranch* b_vtx_trk_z0_wrtSV;
  TBranch* b_vtx_trk_pt_wrtSV;
  TBranch* b_vtx_trk_eta_wrtSV;
  TBranch* b_vtx_trk_phi_wrtSV;
  TBranch* b_vtx_trk_nSCTHits;
  TBranch* b_vtx_trk_nTRTHits;
  TBranch* b_vtx_trk_hitPattern;
  TBranch* b_vtx_trk_isAssociated;
  TBranch* b_vtx_trk_vtx_index;
  
  TBranch* b_truth_vtx_r;
  TBranch* b_truth_vtx_z;
  TBranch* b_truth_vtx_phi;
  TBranch* b_truth_vtx_trk_pt;
  TBranch* b_truth_vtx_trk_eta;
  TBranch* b_truth_vtx_trk_phi;
 
  //&&&&&&&&&&&&&&&&&&&&&&&&&&
  // E N U M   k - S H O R T
  //&&&&&&&&&&&&&&&&&&&&&&&&&&
  std::map<int, int> eventmap;
  
  enum mode { kInclusive, kKshort, kFakeReject, kFakeRejectKshort, kInnerBeamPipe, kN3, kN3outer };
  unsigned mode;
  
  dataobj( std::string filename, std::string treename, std::string n ) : name( n ),
    file( TFile::Open( filename.c_str() ) ),
    tree_name( treename ),
    entry( 0 ),
    eventNumber(0),
    runNumber(0),
    nSelectedTracks(0),
    trk_d0( nullptr ), trk_z0( nullptr ), trk_pt( nullptr ), trk_eta( nullptr ), trk_phi( nullptr ),

    muon_d0( nullptr ), muon_z0( nullptr ), muon_pt( nullptr ), muon_eta( nullptr ), muon_phi( nullptr ), muon_charge( nullptr ),

    vtx_rxy( nullptr ), vtx_r( nullptr ), vtx_z( nullptr ), vtx_x( nullptr ), vtx_y( nullptr ), vtx_phi( nullptr ),
    vtx_mass( nullptr ), vtx_chi2( nullptr ), vtx_index( nullptr ),
    vtx_direction( nullptr ), vtx_pt( nullptr ), vtx_minOpAng( nullptr ), vtx_ntrk( nullptr ),
    
    vtx_trk_charge( nullptr ),
    vtx_trk_pt( nullptr ), vtx_trk_eta( nullptr ), vtx_trk_phi( nullptr ),
    vtx_trk_d0( nullptr ), vtx_trk_z0( nullptr ),
    vtx_trk_d0_wrtSV( nullptr ), vtx_trk_z0_wrtSV( nullptr ),
    vtx_trk_pt_wrtSV ( nullptr ),
    vtx_trk_eta_wrtSV ( nullptr ),
    vtx_trk_phi_wrtSV ( nullptr ),
    vtx_trk_nSCTHits ( nullptr ),
    vtx_trk_nTRTHits ( nullptr ),
    vtx_trk_hitPattern ( nullptr ),
    vtx_trk_isAssociated( nullptr ),
    vtx_trk_vtx_index( nullptr ),

    truth_vtx_r( nullptr ),
    truth_vtx_z( nullptr ),
    truth_vtx_phi( nullptr ),
    truth_vtx_trk_pt( nullptr ),
    truth_vtx_trk_eta( nullptr ),
    truth_vtx_trk_phi( nullptr ),



    hvtx_r( new TH1F("hvtx_r", ";r [mm];Vertices", 400, 0, 400) ),
    hvtx_z( new TH1F("hvtx_z", ";z [mm];Vertices", 200, -1000, 1000) ),
    hvtx_mass( new TH1F("hvtx_mass", ";mass [GeV];Vertices", 100, 0, 100) ),
    hvtx_pt( new TH1F("hvtx_pt",   ";p_{T} [GeV];Vertices", 200, 0, 100) ),
    hvtx_HT( new TH1F("hvtx_HT",   ";H_{T} [GeV];Vertices", 200, 0, 100) ),
    hvtx_beta( new TH1F("hvtx_beta",   ";#beta;Vertices", 20, 0, 1.0) ),
    hvtx_HTratio( new TH1F("hvtx_HTratio",   ";H_{T}/m;Vertices", 100, 0, 10.0) ),
    hvtx_ntrk( new TH1F("hvtx_ntrk", ";N_{track};Vertices", 10,1.5,11.5) ),
    hvtx_chi2( new TH1F("hvtx_chi2", ";#chi^{2}/N_{dof};Vertices", 400, 0, 10) ),
    hvtx_r_n3( new TH1F("hvtx_r_n3", ";r [mm];Vertices", 400, 0, 400) ),
    hvtx_minOpAng( new TH1F("hvtx_minOpAng", ";cos(#theta_{op});Vertices", 200, -1.1, 1.1) ),
    hdir( new TH1F("hdir", "", 200, -1, 1) ),
    hScore( new TH1F("hScore", "", 100, -100, 100) ),
    htrk_d0( new TH1F("htrk_d0", ";d_{0} [mm];Tracks", 200, -400, 400 ) ),
    htrk_z0( new TH1F("htrk_z0", ";z_{0} [mm];Tracks", 100, -1500, 1500 ) ),
    htrk_pt( new TH1F("htrk_pt", ";p_{T} [GeV];Tracks", 200, 0, 20 ) ),
    htrk_eta( new TH1F("htrk_eta", ";#eta;Tracks", 60, -3, 3 ) ),
    htrk_d0_matched( new TH1F("htrk_d0_matched", ";d_{0} [mm];Tracks", 200, -400, 400 ) ),
    htrk_z0_matched( new TH1F("htrk_z0_matched", ";z_{0} [mm];Tracks", 100, -1500, 1500 ) ),
    htrk_pt_matched( new TH1F("htrk_pt_matched", ";p_{T} [GeV];Tracks", 200, 0, 20 ) ),
    htrk_eta_matched( new TH1F("htrk_eta_matched", ";#eta;Tracks", 60, -3, 3 ) ),
    mode( kInclusive )
  {
    tree = dynamic_cast<TTree*>( file->Get(treename.c_str() ) ); // using cosmic tree for now
    setBranchAddress();
  }
  
  ~dataobj() {}
  void setBranchAddress() {
    
    //tree->FindLeaf( "eventCount" )      ->SetAddress( &eventCount );
    tree->FindLeaf( "eventNumber" ) ->SetAddress( &eventNumber );
    tree->FindLeaf( "runNumber"   ) ->SetAddress( &runNumber);
    //tree->FindLeaf( "nSelectedTracks" ) ->SetAddress( &nSelectedTracks );
    
    tree->SetBranchAddress( "muon_d0",   &muon_d0,  &b_muon_d0 );
    tree->SetBranchAddress( "muon_z0",   &muon_z0,  &b_muon_z0 );
    tree->SetBranchAddress( "muon_pt",   &muon_pt,  &b_muon_pt );
    tree->SetBranchAddress( "muon_eta",  &muon_eta, &b_muon_eta );
    tree->SetBranchAddress( "muon_phi",  &muon_phi, &b_muon_phi );
    tree->SetBranchAddress( "muon_charge",  &muon_charge, &b_muon_charge );
    //tree->SetBranchAddress( "trk_selected", &trk_selected, &b_trk_selected );
    
    tree->SetBranchAddress( "DV_r",            &vtx_r,            &b_vtx_r            );
    tree->SetBranchAddress( "DV_rxy",          &vtx_rxy,          &b_vtx_rxy          );
    tree->SetBranchAddress( "DV_z",            &vtx_z,            &b_vtx_z            );
    tree->SetBranchAddress( "DV_x",            &vtx_x,            &b_vtx_x            );
    tree->SetBranchAddress( "DV_y",            &vtx_y,            &b_vtx_y            );
    tree->SetBranchAddress( "DV_mass",         &vtx_mass,         &b_vtx_mass         );
    tree->SetBranchAddress( "DV_chisqPerDoF",  &vtx_chi2,         &b_vtx_chi2         );
    tree->SetBranchAddress( "DV_nTracks",      &vtx_ntrk,         &b_vtx_ntrk         );
    tree->SetBranchAddress( "DV_index",        &vtx_index,         &b_vtx_index       );

    tree->SetBranchAddress( "track_charge",   &vtx_trk_charge,   &b_vtx_trk_charge   );
    tree->SetBranchAddress( "track_pt",       &vtx_trk_pt,       &b_vtx_trk_pt       );
    tree->SetBranchAddress( "track_eta",      &vtx_trk_eta,      &b_vtx_trk_eta      );
    tree->SetBranchAddress( "track_phi",      &vtx_trk_phi,      &b_vtx_trk_phi      );
    tree->SetBranchAddress( "track_d0",       &vtx_trk_d0,       &b_vtx_trk_d0       );
    tree->SetBranchAddress( "track_z0",       &vtx_trk_z0,       &b_vtx_trk_z0       );
    tree->SetBranchAddress( "track_d0WrtDV", &vtx_trk_d0_wrtSV, &b_vtx_trk_d0_wrtSV );
    tree->SetBranchAddress( "track_z0WrtDV", &vtx_trk_z0_wrtSV, &b_vtx_trk_z0_wrtSV );
    tree->SetBranchAddress( "track_ptWrtDV", &vtx_trk_pt_wrtSV, &b_vtx_trk_pt_wrtSV );
    tree->SetBranchAddress( "track_etaWrtDV", &vtx_trk_eta_wrtSV, &b_vtx_trk_eta_wrtSV );
    tree->SetBranchAddress( "track_phiWrtDV", &vtx_trk_phi_wrtSV, &b_vtx_trk_phi_wrtSV );
    tree->SetBranchAddress( "track_NSctHits", &vtx_trk_nSCTHits, &b_vtx_trk_nSCTHits );
    tree->SetBranchAddress( "track_NTrtHits", &vtx_trk_nTRTHits, &b_vtx_trk_nTRTHits );
    tree->SetBranchAddress( "track_isAssociated", &vtx_trk_isAssociated, &b_vtx_trk_isAssociated );
    tree->SetBranchAddress( "track_DVIndex", &vtx_trk_vtx_index, &b_vtx_trk_vtx_index );
    //tree->SetBranchAddress( "Track_hitPattern", &vtx_trk_hitPattern, &b_vtx_trk_hitPattern );
    //
    //tree->SetBranchAddress( "truth_vtx_r",   &truth_vtx_r,   &b_truth_vtx_r   );
    //tree->SetBranchAddress( "truth_vtx_z",   &truth_vtx_z,   &b_truth_vtx_z   );
    //tree->SetBranchAddress( "truth_vtx_phi", &truth_vtx_phi, &b_truth_vtx_phi );
    //
    //tree->SetBranchAddress( "truth_vtx_trk_pt",  &truth_vtx_trk_pt,  &b_truth_vtx_trk_pt  );
    //tree->SetBranchAddress( "truth_vtx_trk_eta", &truth_vtx_trk_eta, &b_truth_vtx_trk_eta );
    //tree->SetBranchAddress( "truth_vtx_trk_phi", &truth_vtx_trk_phi, &b_truth_vtx_trk_phi );
  }
  
  void print() {
    std::cout << "\nDataset " << name << std::endl;
    //std::cout << Form("Event count = %d, Event number = %d", eventCount, eventNumber) << std::endl;
    std::cout << Form("Reco tracks size = %zu, Selected size = %d", trk_d0->size(), nSelectedTracks ) << std::endl;
    std::cout << Form("Reco vertices size = %zu", vtx_r->size() ) << std::endl;
    
    for( size_t i=0; i < vtx_r->size(); i++) {
      
      //if( vtx_chi2->at(i) > 10. ) continue;
      
      TVector3 sumP;
      auto& trk_pt      = vtx_trk_pt  ;
      auto& trk_eta     = vtx_trk_eta ;
      auto& trk_phi     = vtx_trk_phi ;
      auto& trk_d0      = vtx_trk_d0  ;
      auto& trk_z0      = vtx_trk_z0  ;
      auto& trk_d0wrtSV = vtx_trk_d0_wrtSV   ;
      auto& trk_z0wrtSV = vtx_trk_z0_wrtSV   ;
      auto& trk_vtx_index = vtx_trk_vtx_index;
      
      std::string d0s;
      std::string d0wrtSVs;
      
      for( size_t itrk = 0; itrk < trk_pt->size(); itrk++ ) {

        if ( trk_vtx_index->at(itrk) != vtx_index->at(i)) continue;// making sure we're only showing relevent tracks


        TVector3 trk_p;
        trk_p.SetPtEtaPhi( trk_pt->at(itrk), 0.0, trk_phi->at(itrk) );
        sumP += trk_p;
        d0s += Form("%.3f, ", trk_d0->at(itrk) );
        d0wrtSVs += Form("%.3f, ", trk_d0wrtSV->at(itrk) );
      }
        
      TVector3 pos;
      pos.SetXYZ( vtx_x->at(i), vtx_y->at(i), 0.0 );
      
      if( vtx_direction ) {
        auto direction = vtx_direction->at(i);
        hdir->Fill( direction );
        
        //if( direction < 1.0/sqrt(2.0) ) continue;
        
        std::cout << Form("  Vertex [%3zu]: (r, z, phi) = (%7.2f, %7.1f, %5.2f), mass = %10.3f, chi2 = %.3e, ntrk = %d, dir = %.3f, d0 = { %s }, d0wrtSV { %s }",
                          i, vtx_r->at(i), vtx_z->at(i), vtx_phi->at(i), vtx_mass->at(i), vtx_chi2->at(i), vtx_ntrk->at(i), vtx_direction->at(i), d0s.c_str(), d0wrtSVs.c_str() )
                  << std::endl;
      } else {
        std::cout << Form("  Vertex [%3zu]: (r, z, phi) = (%7.2f, %7.1f, %5.2f), mass = %10.3f, chi2 = %.3e, ntrk = %d, d0 = { %s }, d0wrtSV { %s }",
                          i, vtx_r->at(i), vtx_z->at(i), vtx_phi->at(i), vtx_mass->at(i), vtx_chi2->at(i), vtx_ntrk->at(i), d0s.c_str(), d0wrtSVs.c_str() )
                  << std::endl;
      }

    }
    std::cout << "-----\n" << std::endl;
  }
  
  
  void fillHistos() {
    
    for( long long ientry = 0; ientry < tree->GetEntriesFast(); ientry++ ) {
      tree->GetEntry( ientry );
    
      for( size_t ivtx=0; ivtx< vtx_r->size(); ivtx++ ) {
        
        auto vtx_HT = 0.;
        TLorentzVector vtx_p4;
        for( unsigned itrk =0; itrk < vtx_trk_pt->size(); itrk++) {
          if ( vtx_trk_vtx_index->at(itrk) != vtx_index->at(ivtx)) continue;// making sure we're only showing relevent tracks
          vtx_HT += vtx_trk_pt->at(itrk);
          TLorentzVector p4; p4.SetPtEtaPhiM( vtx_trk_pt->at(itrk), vtx_trk_eta->at(itrk), vtx_trk_phi->at(itrk), 139.57018 );
          vtx_p4 += p4;
        }
          
        if( mode == kKshort ) {
          if( vtx_ntrk->at(ivtx) != 2 ) continue;
          if( !(vtx_mass->at(ivtx) > 450. && vtx_mass->at(ivtx) < 550.) ) continue;
        }
        if( mode == kFakeReject ) {
          unsigned count_good { 0 };
          for( unsigned itrk =0; itrk < vtx_trk_nSCTHits->size(); itrk++) {
            if ( vtx_trk_vtx_index->at(itrk) != vtx_index->at(ivtx)) continue;// making sure we're only showing relevent tracks
            if( vtx_trk_nSCTHits->at(itrk) >= 7 && vtx_trk_nTRTHits->at(itrk) >= 30 ) count_good++;
          }
          if( count_good*1.0/(vtx_trk_nSCTHits->size())*1.0 < 0.7 ) continue;
        }
        if( mode == kFakeRejectKshort ) {
          if( vtx_ntrk->at(ivtx) != 2 ) continue;
          if( !(vtx_mass->at(ivtx) > 450. && vtx_mass->at(ivtx) < 550.) ) continue;
          unsigned count_good { 0 };
          for( unsigned itrk =0; itrk < vtx_trk_nSCTHits->size(); itrk++) {
            if ( vtx_trk_vtx_index->at(itrk) != vtx_index->at(ivtx)) continue;// making sure we're only showing relevent tracks
            if( vtx_trk_nSCTHits->at(itrk) >= 7 && vtx_trk_nTRTHits->at(itrk) >= 30 ) count_good++;
          }
          if( count_good*1.0/(vtx_trk_nSCTHits->size())*1.0 < 0.7 ) continue;
        }
        if( mode == kInnerBeamPipe ) {
          if( vtx_r->at(ivtx) > 20. ) continue;
          if( vtx_ntrk->at(ivtx) < 3 ) continue;
        }
        if( mode == kN3 ) {
          if( vtx_ntrk->at(ivtx) < 3 ) continue;
        }
        if( mode == kN3outer ) {
          if( vtx_ntrk->at(ivtx) < 3 ) continue;
          if( vtx_r->at(ivtx) < 125. ) continue;
        }
        
        hvtx_r->Fill( vtx_r->at(ivtx) );
        hvtx_z->Fill( vtx_z->at(ivtx) );
        hvtx_mass->Fill( vtx_mass->at(ivtx)*1.e-3 );
        hvtx_ntrk->Fill( vtx_ntrk->at(ivtx) );
        hvtx_chi2->Fill( vtx_chi2->at(ivtx) );
        hvtx_minOpAng->Fill( vtx_minOpAng->at(ivtx) );
        hvtx_HT->Fill( vtx_HT*1.e-3 );
        hvtx_pt->Fill( vtx_p4.Pt()*1.e-3 );
        hvtx_beta->Fill( vtx_p4.Beta() );
        hvtx_HTratio->Fill( vtx_HT/vtx_p4.M() );
        if( vtx_ntrk->at(ivtx) > 2 ) hvtx_r_n3->Fill( vtx_r->at(ivtx) );
      }
    }
    
  }
  
  
  int findMatchedVertex( dataobj& d, const int& index ) {
    auto dev = [] ( float& v1, float& v2 ) ->float { return fabs( (v1-v2)/v2 ); };
    
    std::vector<float> scores;
    for( size_t i=0; i < vtx_r->size(); i++) {
      std::vector<float> nll;
      nll.emplace_back( -log( dev( d.vtx_r->at(index), vtx_r->at(i) ) ) );
      nll.emplace_back( -log( dev( d.vtx_z->at(index), vtx_z->at(i) ) ) );
      nll.emplace_back( -log( dev( d.vtx_phi->at(index), vtx_phi->at(i) ) ) );
      //nll.emplace_back( -log( dev( d.vtx_mass->at(index), vtx_mass->at(i) ) ) );
      nll.emplace_back( -log( dev( d.vtx_chi2->at(index), vtx_chi2->at(i) ) ) );
      
      auto likelihood = std::accumulate( nll.begin(), nll.end(), 0.0 );
      scores.emplace_back( likelihood );
    }
    
    if( scores.size() > 0 ) {
      auto maxScore = std::max_element( scores.begin(), scores.end() );
      hScore->Fill( *maxScore );
      
      auto k = maxScore - scores.begin();
      
      if( *maxScore > 20. ) {
        std::cout << Form("--> *matched*: Vertex [%3zu]: (r, z, phi) = (%7.2f, %7.1f, %5.2f), mass = %10.3f, chi2 = %.3e",
                          k, vtx_r->at(k), vtx_z->at(k), vtx_phi->at(k), vtx_mass->at(k), vtx_chi2->at(k) )
                  << std::endl;
      }
      
      return ( maxScore - scores.begin() );
    } else {
      return -1;
    }
  }
  
};


bool operator==(dataobj d1, dataobj d2) {
  return ( d1.eventNumber == d2.eventNumber );
}

int findKshort( dataobj& d ) {
  for( size_t iv = 0; iv < d.vtx_r->size(); iv++ ) {
    if( d.vtx_chi2->at(iv) < 10. && d.vtx_mass->at(iv) > 450. && d.vtx_mass->at(iv) < 550. ) {
      return iv;
    }
  }
  return -1;
}

