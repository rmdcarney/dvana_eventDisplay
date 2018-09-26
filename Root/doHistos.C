#define doHistos_cxx
#include "SignalEfficiency/doHistos.h"
#include "Root/VertexMatching.C"
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

/*
#include "Root/SegmentMaps.C"
#include "Root/MetEfficiency.C"
#include "Root/MakeCutflow.C"
#include "Root/MuonPlots.C"
#include "Root/DVPlots.C"
#include "Root/TrackPlots.C"
#include "Root/PileupPlots.C"
*/

bool debug = false;
bool test = false;
bool doMatHistos = false;
int maxevents = 100;

float doHistos::Z_mass()
{
  if (muon_d0->size()==2)
  {
    TLorentzVector mu1;
    TLorentzVector mu2;
    mu1.SetPtEtaPhiM(muon_pt->at(0), muon_eta->at(0), muon_phi->at(0), m_muon);
    mu2.SetPtEtaPhiM(muon_pt->at(1), muon_eta->at(1), muon_phi->at(1), m_muon);     

    return (mu1+mu2).M();
  }
  else return -1;
}
bool doHistos::passZmumu()
{
  
  //bool passTrig = passHLTmsonly || passMETtrigger;

  bool two_muons = (muon_d0->size()==2) ;

  bool opposite_sign = false;
  bool passTM = false;
  bool z_mass = false;

  if (two_muons){

    for (int mu=0; mu<muon_charge->size(); mu++){
      if (muon_TrigMatchMSOnly->at(mu) && fabs(muon_eta->at(mu))<1.05 && muon_pt->at(mu)>62. ) passTM=true;
    }

    opposite_sign = ( (muon_charge->at(0)+muon_charge->at(1) ) == 0 );

    if ( Z_mass()>81. && Z_mass()<101.) z_mass = true;
  }


  //bool isZ = (passTrig && two_muons && opposite_sign && passTM && z_mass);
  bool isZ = (two_muons && opposite_sign && z_mass);
  return isZ;
}
float histWeight(TString sample_name, float event_weight){

	float lumi = 77300.; //pb-1 2016+2017
	float hWght = 1; 

			
	float cross_x = -1;
	float total_sum_weights = -1; 

	if (sample_name == "lmdpctau10"  ) {total_sum_weights = 10000; cross_x = 0.677259;  }// pb
	if (sample_name == "lmdpctau100" ) {total_sum_weights = 10000; cross_x = 0.677259;  }// pb
	if (sample_name == "lmdpctau1000") {total_sum_weights = 9000 ; cross_x = 0.677259;  }// pb


	else if (sample_name.Contains("Stop_1700") 		 ) { total_sum_weights = 10000; cross_x = 0.0000807774; } // pb
	else if (sample_name.Contains("Stop_1400_1ns") 	 ) { total_sum_weights = 5000; cross_x = 0.000461944; } // pb
	else if (sample_name.Contains("Stop_1400_0p1ns") ) { total_sum_weights = 7000; cross_x = 0.000461944; } // pb
	else if (sample_name.Contains("Stop_1100_1ns") 	 ) { total_sum_weights = 2000; cross_x = 0.00307413 ; } // pb
	else if (sample_name.Contains("Stop_1100_0p1ns") ) { total_sum_weights = 5000; cross_x = 0.00307413 ; } // pb


	else if (sample_name.Contains("Stop_1600") ) { total_sum_weights = 500; cross_x = 0.000141382; } // pb
	else if (sample_name.Contains("Stop_1400") ) { total_sum_weights = 500; cross_x = 0.000461944; } // pb
	else if (sample_name.Contains("Stop_1200") ) { total_sum_weights = 500; cross_x = 0.00159844 ; } // pb
	else if (sample_name.Contains("Stop_1000") ) { total_sum_weights = 500; cross_x = 0.00615134 ; } // pb
	else if (sample_name.Contains("Stop_800" ) ) { total_sum_weights = 500; cross_x = 0.0283338  ; }
	else if (sample_name.Contains("Stop_600" ) ) { total_sum_weights = 500; cross_x = 0.174599   ; }
	else if (sample_name.Contains("Stop_400" ) ) { total_sum_weights = 500; cross_x = 1.83537    ; }
	else if (sample_name.Contains("Stop_200" ) ) { total_sum_weights = 500; cross_x = 64.5085    ; }

	else if (sample_name.Contains("ttbar"  	   )) { total_sum_weights = 700000; cross_x = 87.596507; } //pb

	else if (sample_name.Contains("llll"	   )) { total_sum_weights = 120000; cross_x = 11.65255; }
	else if (sample_name.Contains("llvv"	   )) { total_sum_weights = 130000; cross_x = 12.73818; }
	else if (sample_name.Contains("lllvSFMinus")) { total_sum_weights = 20000 ; cross_x = 1.678222; }

	else if (sample_name.Contains("JZ3W")) { total_sum_weights = 200000; cross_x = 8452.58208; }
	else if (sample_name.Contains("JZ4W")) { total_sum_weights = 199800; cross_x = 135.035382; }
	else if (sample_name.Contains("JZ5W")) { total_sum_weights = 199800; cross_x = 4.199465; }
	else if (sample_name.Contains("JZ6W")) { total_sum_weights = 200000; cross_x = 0.241942; }
	else if (sample_name.Contains("JZ7W")) { total_sum_weights = 100000; cross_x = 0.006356; }
	else if (sample_name.Contains("JZ8W")) { total_sum_weights = 100000; cross_x = 0.006354; }


	
	if (cross_x>-1 && total_sum_weights>-1) hWght = lumi * cross_x * event_weight / total_sum_weights;
		
	return hWght;
			
}
float doHistos::getStopMass()
{
	float stopMass = -99;

	for (unsigned int p = 0; p< truthSparticle_M->size(); p++){
		if (truthSparticle_M->at(p) == 1000006){
			stopMass = truthSparticle_M->at(p);
		}
	}

	return stopMass;
}


void msTrackPlots(std::string sample_name, std::vector<MSTrack> mstracks,  std::string selection, float weight =1.)
{
	for (auto mst : mstracks){
		if (selection == "msTrack_allMStracks") plotter.Plot1D(Form("%s_msTrack_cutflow" ,  sample_name.c_str()),";Cut" , 0 ,  10., -0.5, 9.5  , mst.weight);
		if (selection == "msTrack_standalone" ) plotter.Plot1D(Form("%s_msTrack_cutflow" ,  sample_name.c_str()),";Cut" , 1 ,  10., -0.5, 9.5  , mst.weight);
		if (selection == "msTrack_nPresLayers") plotter.Plot1D(Form("%s_msTrack_cutflow" ,  sample_name.c_str()),";Cut" , 2 ,  10., -0.5, 9.5  , mst.weight);
		if (selection == "msTrack_passTrigger") plotter.Plot1D(Form("%s_msTrack_cutflow" ,  sample_name.c_str()),";Cut" , 3 ,  10., -0.5, 9.5  , mst.weight);
		if (selection == "msTrack_passPt"     ) plotter.Plot1D(Form("%s_msTrack_cutflow" ,  sample_name.c_str()),";Cut" , 4 ,  10., -0.5, 9.5  , mst.weight);
		if (selection == "msTrack_passEta"    ) plotter.Plot1D(Form("%s_msTrack_cutflow" ,  sample_name.c_str()),";Cut" , 5 ,  10., -0.5, 9.5  , mst.weight);
		if (selection == "msTrack_passd0"     ) plotter.Plot1D(Form("%s_msTrack_cutflow" ,  sample_name.c_str()),";Cut" , 6 ,  10., -0.5, 9.5  , mst.weight);
		
		if (selection == "msTrack_allMStracks") plotter.Plot1D(Form("%s_msTrack_cutflow_raw" ,  sample_name.c_str()),";Cut" , 0 ,  10., -0.5, 9.5 );
		if (selection == "msTrack_standalone" ) plotter.Plot1D(Form("%s_msTrack_cutflow_raw" ,  sample_name.c_str()),";Cut" , 1 ,  10., -0.5, 9.5 );
		if (selection == "msTrack_nPresLayers") plotter.Plot1D(Form("%s_msTrack_cutflow_raw" ,  sample_name.c_str()),";Cut" , 2 ,  10., -0.5, 9.5 );
		if (selection == "msTrack_passTrigger") plotter.Plot1D(Form("%s_msTrack_cutflow_raw" ,  sample_name.c_str()),";Cut" , 3 ,  10., -0.5, 9.5 );
		if (selection == "msTrack_passPt"     ) plotter.Plot1D(Form("%s_msTrack_cutflow_raw" ,  sample_name.c_str()),";Cut" , 4 ,  10., -0.5, 9.5 );
		if (selection == "msTrack_passEta"    ) plotter.Plot1D(Form("%s_msTrack_cutflow_raw" ,  sample_name.c_str()),";Cut" , 5 ,  10., -0.5, 9.5 );
		if (selection == "msTrack_passd0"     ) plotter.Plot1D(Form("%s_msTrack_cutflow_raw" ,  sample_name.c_str()),";Cut" , 6 ,  10., -0.5, 9.5 );
	
		plotter.Plot1D(Form("%s_%s_msTrack_d0"        ,  sample_name.c_str(),selection.c_str()),";d0(#mu);Muons"                 , mst.d0 ,  50., -200, 200 , mst.weight);
		plotter.Plot1D(Form("%s_%s_msTrack_z0"        ,  sample_name.c_str(),selection.c_str()),";z0(#mu);Muons"                 , mst.z0 ,  50., -500, 500 , mst.weight);
		plotter.Plot1D(Form("%s_%s_msTrack_pt"        ,  sample_name.c_str(),selection.c_str()),";p_{T}(#mu) [GeV];Muons"        , mst.pt ,  50.,  0, 1000  , mst.weight);
		plotter.Plot1D(Form("%s_%s_msTrack_eta"       ,  sample_name.c_str(),selection.c_str()),";#eta(#mu);Muons"               , mst.eta,  25., -1.2, 1.2 , mst.weight);
		plotter.Plot1D(Form("%s_%s_msTrack_etazoom"   ,  sample_name.c_str(),selection.c_str()),";#eta(#mu);Muons"               , mst.eta,  25., -3., 3.   , mst.weight);
		plotter.Plot1D(Form("%s_%s_msTrack_phi"       ,  sample_name.c_str(),selection.c_str()),";#phi(#mu);Muons"               , mst.phi,  25., -3.5, 3.5 , mst.weight);
		plotter.Plot1D(Form("%s_%s_msTrack_nPres"     ,  sample_name.c_str(),selection.c_str()),";N Precision Layers;Muons"      , mst.nPres,      6., -0.5, 5.5 , mst.weight);
		plotter.Plot1D(Form("%s_%s_msTrack_nPresGood" ,  sample_name.c_str(),selection.c_str()),";N Good Precision Layers;Muons" , mst.nPresGood,  6., -0.5, 5.5 , mst.weight);
		plotter.Plot1D(Form("%s_%s_msTrack_nPresHole" ,  sample_name.c_str(),selection.c_str()),";N Precision Layer Holes;Muons" , mst.nPresHole,  6., -0.5, 5.5 , mst.weight);
	}


}




int getMuonTrack(Muon muon,std::vector<Track> tracks){

	int matched_track = -99;
	float eps = 0.005;
	
	for (unsigned int trk=0; trk<tracks.size(); trk++ ){
		Track track = tracks.at(trk);
    	if ( fabs( track.d0 - muon.d0) < eps && fabs(track.z0 - muon.z0) < eps ) matched_track = trk;
    }// end loop on tracks

	return matched_track;
}
float DOCA( float d0, float z0){
	// given a d0 and z0 returns the distance of closest approach 

	float doca = sqrt( d0*d0 + z0*z0 );
	return doca;
}

float doHistos::recomputeDVmass(std::string sample_name,DV dv,  Muon mu){
	// if muon is linked to the DV returns the track of interest 

	TLorentzVector dv_4;
	
	// Add up tracks associated to DV 
	for (unsigned int trk=0; trk < track_d0->size(); trk++){

		if (track_DVIndex->at(trk)!=dv.index) continue;

		TLorentzVector trk_4;
		trk_4.SetPtEtaPhiM(track_ptWrtDV->at(trk),track_etaWrtDV->at(trk),track_phiWrtDV->at(trk),m_pion);
		dv_4 += trk_4;


	} // track loop

	// Add up muons
	dv_4+=mu.p4;


	//std::cout << "Matched Not Linked" << std::endl;
	//std::cout << "Old M " << DV_m->at(dvtx) 	  << " New M " << dv.m 	   << std::endl;
	//std::cout << "Old N " << DV_nTracks->at(dvtx) << " New N " << dv.nTracks << std::endl;

	plotter.Plot1D(Form("%s_muDVMatching_oldMass"  , sample_name.c_str()),";DV old mass [GeV];DVs"  , dv.m         , 200 , 0, 1000 );
	plotter.Plot1D(Form("%s_muDVMatching_newMass"  , sample_name.c_str()),";DV new mass [GeV];DVs"  , dv_4.M()     , 200 , 0, 1000 );
	plotter.Plot1D(Form("%s_muDVMatching_oldNtrk"  , sample_name.c_str()),";DV old Ntrk ;Dvs"       , dv.nTracks   , 50 , 1.5, 51.5 );
	plotter.Plot1D(Form("%s_muDVMatching_newNtrk"  , sample_name.c_str()),";DV new Ntrk ;Dvs"       , dv.nTracks+1 , 50 , 1.5, 51.5 );

	return dv_4.M();


}
int doHistos::isMuonDVLink(DV dv,  Muon mu){
	// if muon is linked to the DV returns the track of interest 

	float eps = 0.0005;
	bool linked_mu = false;
	int linked_track = -1;

	for (unsigned int trk=0; trk < track_d0->size(); trk++){

		if (track_DVIndex->at(trk)!=dv.index) continue;

			if (  fabs(mu.d0 - track_d0->at(trk)) < eps && fabs(mu.z0 - track_z0->at(trk)) < eps ) {
				linked_mu = true;
				linked_track = trk;

				//std::cout << "DV Index " << dv.index  << " : Muon Index " << mu.index << std::endl;
				//std::cout << "d_eta " << fabs(mu.eta - Track_eta->at(trk)) << std::endl;
				//std::cout << "d_phi " << fabs(mu.phi - Track_phi->at(trk)) << std::endl;
				//std::cout << "d_pt  " << fabs(mu.pt  - Track_pt ->at(trk)) << std::endl;
				//std::cout << "d_d0  " << fabs(mu.d0  - Track_d0 ->at(trk)) << std::endl;
				//std::cout << "d_z0  " << fabs(mu.z0  - Track_z0 ->at(trk)) << std::endl;
			 	
			 }

	} // track loop

	return linked_track;


}
int doHistos::getMuonDVLink(std::string sample_name, DV dv, std::vector<Muon> mus, float weight=1.){
	// returns linked muon 

	float linked_mu = -1;

	for (auto mu : mus){
		
		if (mu.passPt25 && mu.passEta2p5 && mu.passID) {
			
			if (isMuonDVLink(dv,mu) > -1 ) linked_mu = mu.index; 
		
		}

	}

	return linked_mu;
	
}
//int doHistos::getMuonDVMatch(std::string sample_name, DV dv, std::vector<Muon> mus, float weight=1.){
//	// returns matched muon
//	int matched_mu = -1;
//	int linked_mu = -1;
//	int linked_trk = -1;
//
//	float smallest_d0 = 999;
//	float smallest_z0 = 999; 
//	float smallest_DOCA = 999;
//	
//	for ( unsigned int pair = 0; pair < muDV_d0wrtSV->size(); pair++ ){ // MATCHING TO MUONS PASSING EVENT SELECTION
//		
//		if (muDV_dvIndex->at(pair)!=dv.index) continue;
//
//		for (auto mu : mus ){
//
//			if (muDV_muIndex->at(pair)!=mu.index) continue;
//
//			if (mu.passPt25 && mu.passEta2p5 && mu.passID) {
//				
//				float doca = DOCA( muDV_d0wrtSV->at(pair),muDV_z0wrtSV->at(pair) );
//
//				if ( doca < fabs(smallest_DOCA) ){
//
//					smallest_d0 = muDV_d0wrtSV->at(pair);
//					smallest_z0 = muDV_z0wrtSV->at(pair);
//					smallest_DOCA = doca;
//					
//					if (doca < 0.5) matched_mu = mu.index;
//
//					if ( isMuonDVLink(dv,mu) > -1 ) {
//										
//						linked_mu = mu.index;
//						linked_trk = isMuonDVLink(dv,mu);
//
//						//std::cout << "linked!" << std::endl;
//						//std::cout << "Track_d0 wrt DV " << Track_d0WrtDV->at(linked_trk) << std::endl;
//						//std::cout << "Track_z0 wrt DV " << Track_z0WrtDV->at(linked_trk) << std::endl;
//						//std::cout << "Muon_d0 wrt DV "  <<  muDV_d0wrtSV->at(pair) << std::endl;
//						//std::cout << "Muon_z0 wrt DV "  <<  muDV_z0wrtSV->at(pair) << std::endl;
//						//std::cout << " MU chi2 "   <<  mu.CBchi2 << std::endl;
//						//std::cout << " DV chi2 "  <<  dv.chi2 << std::endl;
//
//						plotter.Plot1D(Form("%s_linkedmu_muDV_diffTrkMuond0"   	,  sample_name.c_str()),";track - #mu (d0 wrt DV) [mm];Linked DV-Muon Pairs"  , Track_d0WrtDV->at(linked_trk) - muDV_d0wrtSV->at(pair) , 200 , -100, 100 );
//						plotter.Plot1D(Form("%s_linkedmu_muDV_diffTrkMuonz0"   	,  sample_name.c_str()),";track - #mu (z0 wrt DV) [mm];Linked DV-Muon Pairs"  , Track_z0WrtDV->at(linked_trk) - muDV_z0wrtSV->at(pair) , 200 , -100, 100 );
//						
//						plotter.Plot2D(Form("%s_linkedmu_muDV_diffTrkMuond0_muDOCA"  ,  sample_name.c_str()),";track - #mu (d0 wrt DV) [mm];Muon DOCA"   		, Track_d0WrtDV->at(linked_trk) - muDV_d0wrtSV->at(pair) , doca , 100 , -100, 100, 50, 0, 100 );
//						plotter.Plot2D(Form("%s_linkedmu_muDV_diffTrkMuonz0_muDOCA"  ,  sample_name.c_str()),";track - #mu (z0 wrt DV) [mm];Muon DOCA"   		, Track_z0WrtDV->at(linked_trk) - muDV_z0wrtSV->at(pair) , doca , 100 , -100, 100, 50, 0, 100 );
//						
//						if (dv.chi2 < 10){
//							plotter.Plot1D(Form("%s_linkedmugooddv_muDV_mud0wrtDV"   ,  sample_name.c_str()),";Muon d0 to DV [mm];Pairs (dv #chi^{2}/N_{DoF} < 10)"   , muDV_d0wrtSV->at(pair)  	  , 200 , -100, 100 );
//							plotter.Plot1D(Form("%s_linkedmugooddv_muDV_muz0wrtDV"   ,  sample_name.c_str()),";Muon z0 to DV [mm];Pairs (dv #chi^{2}/N_{DoF} < 10)"   , muDV_z0wrtSV->at(pair) 		  , 200 , -100, 100 );
//							plotter.Plot1D(Form("%s_linkedmugooddv_muDV_trkd0wrtDV"  ,  sample_name.c_str()),";Track d0 to DV [mm];Pairs (dv #chi^{2}/N_{DoF} < 10)"  , Track_d0WrtDV->at(linked_trk) , 200 , -100, 100 );
//							plotter.Plot1D(Form("%s_linkedmugooddv_muDV_trkz0wrtDV"  ,  sample_name.c_str()),";Track z0 to DV [mm];Pairs (dv #chi^{2}/N_{DoF} < 10)"  , Track_z0WrtDV->at(linked_trk) , 200 , -100, 100 );
//						}
//						else {
//							plotter.Plot1D(Form("%s_linkedmubaddv_muDV_mud0wrtDV"   ,  sample_name.c_str()),";Muon d0 to DV [mm];Pairs (dv #chi^{2}/N_{DoF} > 10)"   , muDV_d0wrtSV->at(pair)  	  	  , 200 , -100, 100 );
//							plotter.Plot1D(Form("%s_linkedmubaddv_muDV_muz0wrtDV"   ,  sample_name.c_str()),";Muon z0 to DV [mm];Pairs (dv #chi^{2}/N_{DoF} > 10)"   , muDV_z0wrtSV->at(pair)  	  	  , 200 , -100, 100 );
//							plotter.Plot1D(Form("%s_linkedmubaddv_muDV_trkd0wrtDV"  ,  sample_name.c_str()),";Track d0 to DV [mm];Pairs (dv #chi^{2}/N_{DoF} > 10)"  , Track_d0WrtDV->at(linked_trk)  , 200 , -100, 100 );
//							plotter.Plot1D(Form("%s_linkedmubaddv_muDV_trkz0wrtDV"  ,  sample_name.c_str()),";Track z0 to DV [mm];Pairs (dv #chi^{2}/N_{DoF} > 10)"  , Track_z0WrtDV->at(linked_trk)  , 200 , -100, 100 );
//						}// DV chi2 study
//
//					}// if you found a link
//				}// if you're muon is a signal muon
//				 
//			}// muon index check
//
//		}// loop over all muons
//
//	}// loop over all dv muon pairs...
//
//	//if (matched_mu) std::cout << "matched" << std::endl;
//
//	if (smallest_z0 < 999 && smallest_d0 < 999){
//		plotter.Plot1Dlog(Form("%s_all_muDV_closestd0"   ,  sample_name.c_str()),";#mu (d0 wrt DV) [mm];DV-Muon Combinations"   , fabs(smallest_d0)  , 0.0001, 1000 );
//		plotter.Plot1Dlog(Form("%s_all_muDV_closestz0"   ,  sample_name.c_str()),";#mu (z0 wrt DV) [mm];DV-Muon Combinations"   , fabs(smallest_z0)  , 0.0001, 1000 );
//		plotter.Plot1Dlog(Form("%s_all_muDV_closestDOCA" ,  sample_name.c_str()),";#mu (DOCA wrt DV) [mm];DV-Muon Combinations" , fabs(smallest_DOCA), 0.0001, 1000 );
//		
//		if (linked_mu>-1){
//			plotter.Plot1Dlog(Form("%s_linkedmu_muDV_closestd0"   ,  sample_name.c_str()),";#mu (d0 wrt DV) [mm];DV-Muon Combinations"   , fabs(smallest_d0)  , 0.0001, 1000 );
//			plotter.Plot1Dlog(Form("%s_linkedmu_muDV_closestz0"   ,  sample_name.c_str()),";#mu (z0 wrt DV) [mm];DV-Muon Combinations"   , fabs(smallest_z0)  , 0.0001, 1000 );
//			plotter.Plot1Dlog(Form("%s_linkedmu_muDV_closestDOCA" ,  sample_name.c_str()),";#mu (DOCA wrt DV) [mm];DV-Muon Combinations" , fabs(smallest_DOCA), 0.0001, 1000 );
//
//			if (dv.passMassCut5 && dv.passNtrackCut3 && dv.passChisqCut){
//				plotter.Plot1Dlog(Form("%s_linkedmuSig_muDV_closestd0"   ,  sample_name.c_str()),";#mu (d0 wrt DV) [mm];DV-Muon Combinations"   , fabs(smallest_d0)  , 0.0001, 1000 );
//				plotter.Plot1Dlog(Form("%s_linkedmuSig_muDV_closestz0"   ,  sample_name.c_str()),";#mu (z0 wrt DV) [mm];DV-Muon Combinations"   , fabs(smallest_z0)  , 0.0001, 1000 );
//				plotter.Plot1Dlog(Form("%s_linkedmuSig_muDV_closestDOCA" ,  sample_name.c_str()),";#mu (DOCA wrt DV) [mm];DV-Muon Combinations" , fabs(smallest_DOCA), 0.0001, 1000 );
//			}
//		}
//
//		if (dv.passMassCut5 && dv.passNtrackCut3 && dv.passChisqCut){
//			plotter.Plot1Dlog(Form("%s_passMass5ntrk3_muDV_closestd0"   ,  sample_name.c_str()),";#mu (d0 wrt DV) [mm];DV-Muon Combinations"   , fabs(smallest_d0)  , 0.0001, 1000 );
//			plotter.Plot1Dlog(Form("%s_passMass5ntrk3_muDV_closestz0"   ,  sample_name.c_str()),";#mu (z0 wrt DV) [mm];DV-Muon Combinations"   , fabs(smallest_z0)  , 0.0001, 1000 );
//			plotter.Plot1Dlog(Form("%s_passMass5ntrk3_muDV_closestDOCA" ,  sample_name.c_str()),";#mu (DOCA wrt DV) [mm];DV-Muon Combinations" , fabs(smallest_DOCA), 0.0001, 1000 );
//		}
//	}
//
//
//	return matched_mu;
//}

void doHistos::Loop(std::string s_sample)
{
	//////////////////////////////////////////////////////
	// Loops over the input ntuple from a given sample  //
	//////////////////////////////////////////////////////
	
	if (fChain == 0) return;
	
	Long64_t nentries = fChain->GetEntriesFast();
	std::cout << " Analyzing Tree : " << s_sample << " with " << nentries << " entries" << std::endl;


	
	if (debug && nentries > maxevents) nentries = 1000;
	if (test && nentries > maxevents) nentries = 500000;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		fChain->GetEntry(jentry);
		if (jentry%100000 == 0){std::cout << "processed " << jentry << std::endl;}

		//////////////////////////////////////////////////////
		// 			Now analyzing a single event 		    //
		//////////////////////////////////////////////////////

		if ( s_sample=="data" && (!passMETtrigger && !passHLTmsonly) ) continue; // in data skip events which don't fire our trigger - for now

		bool isZ = passZmumu();


		/*
		 Get the event weight & sample name
		*/

		if (debug) std::cout << "getting event weight" << std::endl;
		float evt_wght;
		if 	(s_sample=="data")  evt_wght=1.0;    
		else if (s_sample.find("Stop") != std::string::npos) {
				evt_wght = histWeight( s_sample, mcEventWeight ); // Pileup is wrong
		}
		else 	evt_wght = histWeight( s_sample, mcEventWeight*pileupWeight ); // is MC
		

		/*
		 Get some variables of interest
		*/

		if (debug) {
			int nMu  = muon_pt->size();
			int nMst = mstrack_nPres->size();
			int nDV  = DV_m->size();
			std::cout << "Event " << jentry << " : " << nMu << " Muons " << nMst << " MSTracks " << nDV << " DVs " << evt_wght << " evt wgt. " << std::endl;
		}
		bool blind = false;



		/*
		 Packing up Segments 
		*/
		if (debug) std::cout << "getting segments" << std::endl;

		std::vector<Segment> segments; segments.clear();
		for (unsigned int seg=0; seg<msSegment_t0->size(); seg++ ){
			Segment segment;

			segment.t0 		 = msSegment_t0->at(seg);
			segment.clusTime = msSegment_clusTime->at(seg);

			segment.x = msSegment_x->at(seg);
			segment.y = msSegment_y->at(seg);
			segment.z = msSegment_z->at(seg);

  			//segment.muIndex 		= msSegment_muIndex->at(seg);          
  			segment.nPhiLays		= msSegment_nPhiLays->at(seg);         
  			segment.nPresHits		= msSegment_nPresHits->at(seg);        
  			segment.nTrigEtaLays	= msSegment_nTrigEtaLays->at(seg); 


  			segment.chmbIndex 	= msSegment_chmbIndex->at(seg);          
  			segment.etaIndex 	= msSegment_etaIndex->at(seg);                 
  			segment.sector 		= msSegment_sector->at(seg);                  
  			//segment.tech 		= msSegment_tech->at(seg);             
  			
  			TLorentzVector four_vector;
			four_vector.SetXYZM(segment.x,segment.y,segment.z,m_muon);
			segment.p4	= four_vector; 

			segments.push_back(segment);
		}
		/*
		 Packing up Muons 
		*/
		if (debug) std::cout << "getting muons" << std::endl;
		std::vector<Muon> muons; muons.clear();
		float max_pt = 25;
		int lead_mu = -1; 
		for (unsigned int mu=0; mu<muon_pt->size(); mu++ ){

			Muon muon;
			muon.index    = mu;

			muon.d0       = muon_d0             ->at(mu);
			muon.z0       = muon_z0             ->at(mu); // z where d0 is measured with respect to the origin
			muon.z0corr   = muon.z0 - PV_z;				  // z where d0 is measured with respect to the primary vertex? 
			muon.eta      = muon_eta            ->at(mu);
			muon.phi      = muon_phi            ->at(mu);
			muon.pt       = muon_pt             ->at(mu);

			TLorentzVector four_vec;
			four_vec.SetPtEtaPhiM(muon.pt,muon.eta,muon.phi,m_muon);
			muon.p4	= four_vec; 

			muon.nPres    = muon_nPres          ->at(mu);
			muon.nPresGood= muon_nPresGood      ->at(mu);
			muon.nPresHole= muon_nPresHole      ->at(mu);
			muon.nPIX     = muon_nPIX           ->at(mu);
			muon.nSCT     = muon_nSCT           ->at(mu);
			muon.nTRT     = muon_nTRT           ->at(mu);
			muon.DVindex  = muon_DVindex        ->at(mu);
			muon.author   = muon_author         ->at(mu);
			muon.TM       = muon_TrigMatch      ->at(mu);
			muon.TMmsonly = muon_TrigMatchMSOnly->at(mu);

			muon.CBchi2   = muon_CBchi2         ->at(mu);
    		muon.rho	  = muon_CBchi2			->at(mu);
    		muon.qOverP	  = muon_QoverPsignif 	->at(mu); 

			muon.weight   = evt_wght*muSF;

   			muon.ptvarcone20	= muon_ptvarcone20  ->at(mu)/(muon.pt);	
   			muon.ptvarcone30	= muon_ptvarcone30  ->at(mu)/(muon.pt);	
   			muon.ptvarcone40	= muon_ptvarcone40  ->at(mu)/(muon.pt);	
   			muon.ptcone20 		= muon_ptcone20 	->at(mu)/(muon.pt);
   			muon.ptcone30 		= muon_ptcone30 	->at(mu)/(muon.pt);
   			muon.ptcone40 		= muon_ptcone40 	->at(mu)/(muon.pt);
   			muon.topoetcone20	= muon_topoetcone20 ->at(mu)/(muon.pt);
   			muon.topoetcone30	= muon_topoetcone30 ->at(mu)/(muon.pt);
   			muon.topoetcone40	= muon_topoetcone40 ->at(mu)/(muon.pt);

   			// For testing
   			muon.testpassCosmicAcceptance 		= muon_passCosmicAcceptance->at(mu); 
   			muon.testpassCosmicVeto 			= muon_passCosmicVeto->at(mu); 
   			muon.testpassFakeVeto 				= muon_passFakeVeto->at(mu); 
   			muon.testpassFullSelection 			= muon_passFullSelection->at(mu); 
   			muon.testpassIsolation 				= muon_passIsolation->at(mu); 
   			muon.testpassPreselection 			= muon_passPreselection->at(mu); 
   			muon.testpassSegmentMatch 			= muon_passSegmentMatch->at(mu); 


			//CAREFUL NOT CONSECUTIVE
			float dR_cos_min 	 = 5.0; 
			//bool fail_cos = false;											
			for (auto segment : segments){ 
				float dR_cos = dR_cosmic( muon.p4, segment.p4 );
				if (dR_cos < dR_cos_min) {
					dR_cos_min = dR_cos; 
				}
				// to debug
				//std::cout << "mu " << mu << " : seg " << std::endl;
				//std::cout << "MUO : eta " << muon.eta  << " : phi " << muon.phi  << " : pt " << muon.pt << std::endl;
				//std::cout << "SEG : eta " << segment.p4.Eta() << " : phi " << segment.p4.Phi() << std::endl;
				//std::cout << "DR COS  " << dR_cos << std::endl;
			}
			//std::cout << "FINAL " << dR_cos_min << std::endl; 
			muon.dRcos 	= dR_cos_min; 

			// Cut information 


   			muon.passCosVetoTight 	= (dR_cos_min > 0.2  ) 			? true : false; 
   			muon.passCosVetoLoose 	= (dR_cos_min > 0.15 ) 			? true : false; 
   			muon.passFakeVetoTight	= (muon.nPres >2 && muon.CBchi2 < 8) ? true : false;
   			muon.passFakeVetoLoose	= ( ((fabs(muon.eta)<1.05&&muon.nPres>1)||(fabs(muon.eta)>1.05&&muon.nPres>2)) && muon.CBchi2 < 8 ) ? true : false;
   			muon.passFixedCutLoose	= ( muon.ptvarcone30<0.15 && muon.topoetcone20 < 0.3) ? true : false;

   			muon.passPt62 		= (muon.pt > 62)		 	 ? true : false;   
   			muon.passPt25 		= (muon.pt > 25)		 	 ? true : false;    
   			muon.passEta2p5 	= (fabs(muon.eta)<2.5)  	 ? true : false;   
   			muon.passEta1p7 	= (fabs(muon.eta)<1.07)  	 ? true : false;   
   			muon.passD0 		= (fabs(muon.d0)>1.5&&fabs(muon.d0)<300)? true : false; 
   			muon.passZ0 		= (fabs(muon.z0)<300)	 ? true : false; 
   			muon.passTM 		= (muon.TMmsonly)			 ? true : false; 
   			muon.passID 		= (muon.nPIX>1||muon.nTRT>0) ? true : false;    

 			muon.passPreSel     = (muon.passEta2p5&&muon.passPt25&&muon.passD0 )  ? true : false;
 			muon.passFullSel    = (muon.passEta2p5&&muon.passPt25&&muon.passD0&&muon.passCosVetoTight&&muon.passFakeVetoTight&&muon.passFixedCutLoose)  ? true : false;
			// Cosmic, Fake, Heavy Flavor Vetos
			//std::cout << " " << std::endl;
			//std::cout << " " << std::endl;
			//std::cout << " " << std::endl;
			//std::cout << " " << std::endl;
			//std::cout << "trg match " << muon.passTM << std::endl;
 			//std::cout << "dR cos " << muon.dRcos << std::endl;
 			//std::cout << muon.passCosVetoTight << std::endl;

			// commenting out for data temp
			// find the jet nearest the muon
   			//float dRmin = 2*PI;
   			//for (unsigned int jet=0; jet<jetPt->size(); jet++){
   			//	if (jetPt->at(jet) < 30  && fabs(jetEta->at(jet) > 2.5) ) {
   			//		TLorentzVector jet_4vec;
   			//		jet_4vec.SetPtEtaPhiE(jetPt->at(jet),jetEta->at(jet),jetPhi->at(jet),jetE->at(jet));
   			//		float dR = four_vec.DeltaR(jet_4vec);
   			//		if (dR<dRmin) dRmin = dR; 
   			//	}
   			//}
   			//muon.dRjet  = dRmin;
   
			muons.push_back(muon);

			if (debug) std::cout << " muon " << mu << " : pt  " << muon.pt  << " : eta " << muon.eta << " : phi " << muon.phi << " : d0 " << muon.d0 << std::endl;
  			
  			// find leading muons
  			if (muon.passPreSel && muon.pt > max_pt) lead_mu = mu;
		}
		// save leading muon
		for (int i = 0; i<muons.size(); i++ )
		{
			if (i == lead_mu ) (muons.at(i)).isLeading = 1;
			else 			   (muons.at(i)).isLeading = 0;
		}

		/*
		 Packing Muon Spectrometer Tracks 
		*/
		if (debug) std::cout << "getting msTracks" << std::endl;
		std::vector<MSTrack> msTracks; msTracks.clear();
    	for (unsigned int mst = 0; mst<mstrack_nPres->size(); mst++){
			
			MSTrack msTrack; 
			msTrack.index = mst;
			msTrack.d0        = mstrack_D0   	 ->at(mst);
			msTrack.z0        = mstrack_Z0   	 ->at(mst);
			msTrack.eta       = mstrack_eta  	 ->at(mst);
			msTrack.phi       = mstrack_phi  	 ->at(mst);
			msTrack.pt        = mstrack_pt   	 ->at(mst);
			msTrack.nPres     = mstrack_nPres	 ->at(mst);
			msTrack.nPresHole = mstrack_nPresHole->at(mst);
			msTrack.nPresGood = mstrack_nPresGood->at(mst);
			//msTrack.MuonIndex = mstrack_muIndex  ->at(mst);
			msTrack.weight    = evt_wght;
			TLorentzVector four_vec;
			four_vec.SetPtEtaPhiM(msTrack.pt,msTrack.eta,msTrack.phi,m_muon);
			msTrack.p4	= four_vec; 
			msTracks.push_back(msTrack);
			if (debug) std::cout << " mstrack " << mst << " : pt  " << msTrack.pt  << " : eta " << msTrack.eta << " : phi " << msTrack.phi << std::endl;

		}
		/*
		 Packing DV associated tracks 
		*/
		if (debug) std::cout << "getting tracks associated to DVs" << std::endl;
		std::vector<Track> tracks; tracks.clear();
		for (unsigned int trk = 0; trk < track_DVIndex->size(); trk++){
			Track track;
			track.DVIndex		 = 		 track_DVIndex			->at(trk);
   			//track.charge		 = 		 track_charge			->at(trk);
   			track.RadFirstHit	 = 		 track_RadFirstHit		->at(trk);
   			track.d0			 = 		 track_d0				->at(trk);
   			track.d0WrtDV		 = 		 track_d0WrtDV			->at(trk);
   			track.errPt			 = 		 track_errPt			->at(trk);
   			track.errd0			 = 		 track_errd0			->at(trk);
   			track.errd0WrtDV	 = 		 track_errd0WrtDV		->at(trk);
   			track.errz0			 = 		 track_errz0			->at(trk);
   			track.errz0WrtDV	 = 		 track_errz0WrtDV		->at(trk);
   			track.eta			 = 		 track_eta				->at(trk);
   			track.etaWrtDV		 = 		 track_etaWrtDV			->at(trk);
   			track.phi			 = 		 track_phi				->at(trk);
   			track.phiWrtDV		 = 		 track_phiWrtDV			->at(trk);
   			track.pt			 = 		 track_pt				->at(trk);
   			track.ptWrtDV		 = 		 track_ptWrtDV			->at(trk);
   			track.z0			 = 		 track_z0				->at(trk);
   			track.z0WrtDV		 = 		 track_z0WrtDV			->at(trk);

   			TLorentzVector four_vector; 
   			TLorentzVector four_vector_wrtDV; 
   			four_vector.SetPtEtaPhiM(track.pt, track.eta, track.phi, m_pion);
   			four_vector_wrtDV.SetPtEtaPhiM(track.ptWrtDV , track.etaWrtDV, track.phiWrtDV, m_pion);

   			track.p4 	   = four_vector;
   			track.p4_wrtDV = four_vector_wrtDV;

   			tracks.push_back(track);

		}


		/*
		 Packing Inner Detector Tracks 
		*/
		//std::vector<IDTrack> id_tracks; id_tracks.clear();
		//for (unsigned int trk = 0; trk <idTrack_d0->size(); trk++){
		//	if ( fabs(idTrack_d0->at(trk) > 1.0) ){
		//
		//		IDTrack id_track; 
		//		id_track.index = trk;
   		//		id_track.nPix 		= idTrack_NPix_Hits	->at(trk);         
   		//		id_track.nSct 		= idTrack_NSct_Hits	->at(trk);         
   		//		id_track.nTrt 		= idTrack_NTrt_Hits	->at(trk);         
   		//		id_track.charge 	= idTrack_charge	->at(trk);         
   		//		id_track.chi2 		= idTrack_chi2		->at(trk);         
   		//		id_track.d0 		= idTrack_d0		->at(trk);         
   		//		id_track.eta 		= idTrack_eta		->at(trk);         
   		//		id_track.phi 		= idTrack_phi		->at(trk);         
   		//		id_track.pt 		= idTrack_pt		->at(trk);         
   		//		id_track.theta 		= idTrack_theta		->at(trk);         
   		//		id_track.z0 		= idTrack_z0		->at(trk);         
   		//		id_track.z0WrtPV 	= idTrack_z0WrtPV	->at(trk);  
   		//		TLorentzVector four_vec;
		//		four_vec.SetPtEtaPhiM(id_track.pt,id_track.eta,id_track.phi,m_pion);
		//		id_track.p4	= four_vec;  
		//
   		//		id_tracks.push_back(id_track);
		//
		//	}
		//	
		//}

		/*
		 Packing up Displaced Vertices  
		*/
		if (debug) std::cout << "getting DVs" << std::endl;

		std::vector<DV> displacedVertices; displacedVertices.clear();
  		for (unsigned int dvtx = 0; dvtx<DV_m->size(); dvtx++){

			DV dv;
			dv.index = dvtx;
			dv.chi2    = DV_chisqPerDoF->at(dvtx);
			dv.m       = DV_m        ->at(dvtx);
			dv.nLRT    = DV_nLRT   	 ->at(dvtx);
			dv.nTracks = DV_nTracks	 ->at(dvtx);
			dv.r       = DV_r      	 ->at(dvtx);
			dv.rxy     = DV_rxy    	 ->at(dvtx);
			dv.x       = DV_x      	 ->at(dvtx);
			dv.y       = DV_y      	 ->at(dvtx);
			dv.z       = DV_z      	 ->at(dvtx);
			dv.lastCut = DV_lastCut	 ->at(dvtx);
			dv.phi 	   = atan(dv.y/dv.x);

			// commenting out for data
			//int i_matched_mu = getMuonDVMatch(s_sample,dv,muons);	
			//int i_linked_mu  = getMuonDVLink (s_sample,dv,muons);	

			
			//if (i_matched_mu >  -1 && i_linked_mu == -1 ) { 	
			//	// IF DV is matched to a muon but not linked in xAOD
			//	// recompute DV # tracks 
			//	// recompute DV mass 
			//		
			//	dv.nTracks = dv.nTracks+1;	
			//	dv.m = recomputeDVmass(s_sample,dv,muons.at(i_matched_mu));
			//}

			// FOR CUTFLOW 
			dv.passFiducialCuts   = (dv.lastCut >= 1 || dv.lastCut == -1 ) ? true : false; // cumulative
  			dv.passChisqCut       = (dv.chi2 < 5 						 ) ? true : false; 
  			dv.passDistCut        = (dv.lastCut >= 3 || dv.lastCut == -1 ) ? true : false; // cumulative
  			dv.passMaterialVeto   = (dv.lastCut >= 4 || dv.lastCut == -1 ) ? true : false; // cumulative 
  			dv.passMassCut10      = (dv.m > 10 							 ) ? true : false; 
  			dv.passMassCut5       = (dv.m > 5 							 ) ? true : false; 
  			dv.passNtrackCut3     = (dv.nTracks > 2 					 ) ? true : false; 
  			dv.passNtrackCut4     = (dv.nTracks > 3 					 ) ? true : false; 
  			dv.passNtrackCut5     = (dv.nTracks > 4 					 ) ? true : false; 
  			//dv.passMuonLink       = (i_matched_mu > -1 ||i_linked_mu > -1) ? true : false; // take a matched or linked muon


			dv.weight  = evt_wght;
			displacedVertices.push_back(dv);

			////////////////////////////////////////////////////////////////
			// 						 BLINDING! 							  //
			////////////////////////////////////////////////////////////////
			//if ( s_sample=="data" && dv.m > 10 && dv.nTracks > 4 ) blind = true;

			if (debug) std::cout << " dv " << dvtx << " : m  " << dv.m  << " : nTrks " << dv.nTracks << " : rxy " << dv
				.rxy << std::endl;
		}

		if (debug) std::cout << "getting truth vertices" << std::endl;

		std::vector<TruthVertex> truthVertices; truthVertices.clear();
		for (unsigned int vtx = 0; vtx<truthSparticle_Eta->size(); vtx++)
		{
			// only save r-hadrons with status 1
			if (truthSparticle_Status->at(vtx) == 1 && fabs(truthSparticle_PdgId->at(vtx)) < 1000000000)
			{
				TruthVertex truthVertex;
  				truthVertex.index 		= vtx;
  				truthVertex.pdgId  		= truthSparticle_PdgId->at(vtx); 
  				truthVertex.status 		= truthSparticle_Status->at(vtx); 
	
  				truthVertex.m      		= truthSparticle_M->at(vtx);
  				truthVertex.mCh    		= truthSparticle_VtxMChParticles->at(vtx);
  				truthVertex.mCh1GeV		= truthSparticle_VtxMChParticles1GeV->at(vtx);
  				truthVertex.mCh1GeVd0   = truthSparticle_VtxMChParticles1GeVd0->at(vtx);
  				truthVertex.n         	= truthSparticle_VtxNParticles->at(vtx); 
  				truthVertex.nCh    	  	= truthSparticle_VtxNChParticles->at(vtx);
  				truthVertex.nCh1GeV   	= truthSparticle_VtxNChParticles1GeV->at(vtx);
  				truthVertex.nCh1GeVd0 	= truthSparticle_VtxNChParticles1GeVd0->at(vtx);
	
  				truthVertex.r      = vertexR(truthSparticle_VtxX->at(vtx),truthSparticle_VtxY->at(vtx),truthSparticle_VtxZ->at(vtx));
  				truthVertex.rxy    = vertexRxy(truthSparticle_VtxX->at(vtx),truthSparticle_VtxY->at(vtx));
  				truthVertex.x      = truthSparticle_VtxX->at(vtx);
  				truthVertex.y      = truthSparticle_VtxY->at(vtx);
  				truthVertex.z      = truthSparticle_VtxZ->at(vtx);
  				truthVertex.phi    = truthSparticle_Phi->at(vtx);
  				truthVertex.weight = evt_wght;
	
				//std::cout << " truth vtx " << vtx << " : m  " << truthVertex.m  << " : nTrks " << truthVertex.nCh1GeVd0 << " : pdg " << truthVertex.pdgId << std::endl;	

  				truthVertices.push_back(truthVertex);
  				if (debug) std::cout << " truth vtx " << vtx << " : m  " << truthVertex.m  << " : nTrks " << truthVertex.nCh1GeVd0 << " : rxy " << truthVertex.rxy << std::endl;				
				

			}
		}
			


		std::cout << jentry << std::endl;
		std::vector<TruthMuon> truthMuons; truthMuons.clear();
		for (unsigned int trk = 0; trk<truthTrack_Eta->size(); trk++)
		{
			if ( fabs(truthTrack_PdgId->at(trk)) ==  13  ) 
			{
				std::cout << truthTrack_Parent->at(trk) << " : pt " << truthTrack_Pt->at(trk) << std::endl;
				TruthMuon truthMuon;

   				truthMuon.charge  	= truthTrack_Charge->at(trk) ; 
   				truthMuon.eta  		= truthTrack_Eta->at(trk) ; 
   				truthMuon.parent  	= truthTrack_Parent->at(trk) ; 
   				truthMuon.pdgId  	= truthTrack_PdgId->at(trk) ; 
   				truthMuon.phi  		= truthTrack_Phi->at(trk) ; 
   				truthMuon.pt  		= truthTrack_Pt->at(trk) ; 
   				truthMuon.status  	= truthTrack_Status->at(trk) ; 
   				truthMuon.d0  		= truthTrack_d0->at(trk) ; 
   				truthMuon.weight 	= evt_wght;

				TLorentzVector four_vec;
				four_vec.SetPtEtaPhiM(truthMuon.pt,truthMuon.eta,truthMuon.phi,m_muon);
				truthMuon.p4	= four_vec; 

				

   				truthMuons.push_back(truthMuon);		



   				//std::cout << " truth muon " << trk << " : pt  " << truthMuon.pt  << " : eta " << truthMuon.eta << " : phi " << truthMuon.phi << std::endl;							
			}

		}

  		

  		// Do truth to reco matching of DVs
  		for (auto rh : truthVertices)
  		{
  			rh.reco_match = find_matching_reco_vertex(displacedVertices, rh);
  			//std::cout << "Truth Vtx " << rh.index << " : m " << rh.m << " : ntrk " << rh.nCh1GeVd0 << " : match " << rh.reco_match << std::endl;
  		}
  		for (auto dv : displacedVertices)
  		{
  			dv.truth_match = find_matching_truth_vertex(dv, truthVertices);

  			if (dv.nTracks>3 && dv.m > 10 && fabs(dv.z) < 300 && dv.rxy < 300 && dv.passDistCut) reco_dv_plots(dv, truthVertices);
  			//std::cout << "Reco Vtx " << dv.index << " : m " << dv.m << " : ntrk " << dv.nTracks << " : match " << dv.truth_match << std::endl;
  		}


		// Do truth to reco matching of muons
  		for (auto truth_mu : truthMuons)
  		{
  			truth_mu.reco_match = find_matching_reco_muon(muons, truth_mu);
  			//std::cout << "Truth Muon : pt " << truth_mu.pt << " : eta " << truth_mu.eta << " : phi "  << truth_mu.phi << std::endl;
  			
  			matched_muon_plots(truth_mu, muons);

  			//pull out matching reco
  			if (truth_mu.reco_match > -1)
  			{
  				Muon mu = return_reco_muon(truth_mu.reco_match, muons);
  				//std::cout << "Reco Muon : pt " << mu.pt << " : eta " << mu.eta << " : phi "  << mu.phi << " : dR " << mu.p4.DeltaR(truth_mu.p4) << std::endl;
  			}
  			
  		}
  		for (auto reco_mu : muons)
  		{
  			reco_mu.truth_match = find_matching_truth_muon(reco_mu, truthMuons);
  			//std::cout << "Reco Muon : pt " << mu.pt << " : eta " << mu.eta << " : phi "  << mu.phi << std::endl;
  			//pull out matching truth
  			//if (truth_mu.reco_match > -1)
  			//{
  			//	TruthMuon mu = return_truth_muon(reco_mu.truth_match, truthMuons);
  			//	std::cout << "Reco Muon : pt " << mu.pt << " : eta " << mu.eta << " : phi "  << mu.phi << " : dR " << mu.p4.DeltaR(reco_mu.p4) << std::endl;
  			//}
  		}


		/////////////////////////////////////
		// 			APPLY BLINDING		   //
		/////////////////////////////////////
		if (blind) continue;

		//// Make some plotzz
		
		
		


		

		
	}// End loop over events
}
int main(int argc, char* argv[]){

	// defaults 
	std::string sample_name = "lmdpctau10";
	std::string output_name = "lmdpctau10";
	std::string file_name = "signalSamples/lmdp211_CT10/data-trees/mc15_13TeV.402806.MGPy8EG_A14N23LO_SS_RPVDV_700_500_lamp211_10.merge.DAOD_SUSY15.e4332_s2608_s2183_r8788_p2877.root";

	if (argc > 2){
		sample_name = argv[1];
		output_name = argv[2];
		file_name   = argv[3];

	}

	std::cout << "Starting DV + MUON Studies!" << std::endl;

	gROOT->SetBatch();
	gStyle->SetOptStat(0);
	PlotHelper::setPlotStyle(0);

	TFile *file = TFile::Open(file_name.c_str());
	TString tree_name = "trees_SRDV_";
	TTree *tree = (TTree*)file->Get(tree_name);
	bool isMC = 1;
	if (sample_name=="data") isMC = 0;
	if (sample_name=="testing") isMC = 0;
	doHistos analysis(tree,isMC);
	analysis.Loop(sample_name);

	// Save histogrmas here
	TFile *output_file = TFile::Open(Form("output/%s.root",output_name.c_str()),"RECREATE");
	output_file->cd();

	c1->SetTickx(true);
	c1->SetTicky(true);
	plotter.DrawAll1D(c1);
	plotter.DrawAll1Dlog(c1);
	plotter.DrawAll2D(c1, "colz");
	plotter.DrawAll3D(c1, "box");

}
