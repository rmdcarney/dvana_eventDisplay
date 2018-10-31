
//
// Functions necessary to do vertex and reco matching 
//
float sphereCut(float DVR){
	//return 0.0133333333*DVR + 1;// from dv+met parameterization
	return 5;
}
float vertex_distance(DV dv, TruthVertex rh)
{

	// make three vectors
	TVector3 truth;
	truth.SetXYZ(rh.x, rh.y, rh.z);

	TVector3 reco;
	reco.SetXYZ(dv.x, dv.y, dv.z);

	float dist = (truth-reco).Mag();
	return dist;
 
}
bool dv_passSelection(DV dv)
{
	// ignore material veto for now
	//if (dv.passFiducialCuts && dv.passChisqCut && dv.passDistCut && dv.passMaterialVeto && dv.passMassCut10 && dv.passNtrackCut3) return true;
	if (dv.passFiducialCuts && dv.passChisqCut && dv.passDistCut && dv.passMassCut10 && dv.passNtrackCut3) return true; 
	else return false;
}
int find_matching_truth_vertex(DV dv, std::vector<TruthVertex> rhadrons)
{

	// compute R cutoff for DV
	float R = sphereCut(dv.rxy);
	int match = -1;
	float dist = 999999;
	for (auto rh : rhadrons)
	{
		float dist_tmp = vertex_distance(dv,rh);
		if (dist_tmp < R && dist_tmp < dist &&  dv_passSelection(dv) ){
			dist = dist_tmp;
			match = rh.index;

			//std::cout << "truth matching dv " << dv.index << " " << rh.index << " " << dist_tmp << std::endl;
		}
	}
	return match;
}
int find_matching_reco_vertex(std::vector<DV> dvs, TruthVertex rh)
{

	float R=1;
	int match = -1;
	float dist = 999999;
	for (auto dv : dvs)
	{
		// compute R cutoff for DV
		R = sphereCut(dv.rxy);
		float dist_tmp = vertex_distance(dv,rh);
		if (dist_tmp < R && dist_tmp < dist &&  dv_passSelection(dv) ){
			dist = dist_tmp;
			match = dv.index;
		}
	}
	return match;
}

//
// Plots to study vertex matching 
//
TruthVertex return_truth_vertex(int index, std::vector<TruthVertex> truth_vtxs)
{
	// returns a matching truth muon
	TruthVertex dv;
	for (auto truth_vtx : truth_vtxs )
	{
		if ( truth_vtx.index == index ) 
		{
			dv = truth_vtx;
			break;
		}
	}
	return dv;
}
DV return_reco_vertex(int index, std::vector<DV> reco_dvs)
{
	// returns a matching reco muon
	DV dv;
	for (auto reco_dv : reco_dvs )
	{
		if ( reco_dv.index == index ) 
		{
			dv = reco_dv;
			break;
		}
	}
	return dv;
}
void track_plots(std::string sample, std::string selection, Track trk)
{
	plotter.Plot1D(Form("%s_%s_dvTracks_eta" 	, sample.c_str(), selection.c_str() ),";trk eta;dv trks" 		, trk.eta	, 50, -3.5, 3.5, 	 trk.weight );
	plotter.Plot1D(Form("%s_%s_dvTracks_phi" 	, sample.c_str(), selection.c_str() ),";trk phi;dv trks" 		, trk.phi	, 50, -3.5, 3.5,	 trk.weight );
	plotter.Plot1D(Form("%s_%s_dvTracks_pt"   	, sample.c_str(), selection.c_str() ),";trk pt;dv trks" 		, trk.pt	, 50,   0 , 100,  	 trk.weight );
	plotter.Plot1D(Form("%s_%s_dvTracks_d0"   	, sample.c_str(), selection.c_str() ),";trk d0;dv trks" 		, trk.d0	, 50, -300, 300, 	 trk.weight );
	plotter.Plot1D(Form("%s_%s_dvTracks_z0"   	, sample.c_str(), selection.c_str() ),";trk z0;dv trks" 		, trk.z0	, 50, -700, 700, 	 trk.weight );
	
	plotter.Plot1D(Form("%s_%s_dvTracks_absd0"   , sample.c_str(), selection.c_str() ),";trk |d0|;dv trks" 	, abs(trk.d0)	, 50, 0, 300, 	 trk.weight );
	plotter.Plot1D(Form("%s_%s_dvTracks_absd0zoom"   , sample.c_str(), selection.c_str() ),";trk |d0|;dv trks" 	, abs(trk.d0)	, 50, 0, 10, 	 trk.weight );


   	plotter.Plot1D(Form("%s_%s_dvTracks_NPixDeadSens" 	, sample.c_str(), selection.c_str() ), ";NPixDeadSens;dv trks" 		, trk.NPixDeadSens		, 10, -0.5, 10.5 	, trk.weight);  
   	plotter.Plot1D(Form("%s_%s_dvTracks_NPixHits" 		, sample.c_str(), selection.c_str() ), ";NPixHits;dv trks" 			, trk.NPixHits			, 10, -0.5, 10.5 	, trk.weight); 
   	plotter.Plot1D(Form("%s_%s_dvTracks_NPixHoles" 		, sample.c_str(), selection.c_str() ), ";NPixHoles;dv trks" 		, trk.NPixHoles			, 10, -0.5, 10.5 	, trk.weight); 
   	plotter.Plot1D(Form("%s_%s_dvTracks_NPixSharedHits" , sample.c_str(), selection.c_str() ), ";NPixSharedHits;dv trks" 	, trk.NPixSharedHits	, 10, -0.5, 10.5 	, trk.weight);   
   	plotter.Plot1D(Form("%s_%s_dvTracks_NSctDeadSens" 	, sample.c_str(), selection.c_str() ), ";NSctDeadSens;dv trks" 		, trk.NSctDeadSens		, 16, -0.5, 15.5 	, trk.weight);  
   	plotter.Plot1D(Form("%s_%s_dvTracks_NSctHits" 		, sample.c_str(), selection.c_str() ), ";NSctHits;dv trks" 			, trk.NSctHits			, 16, -0.5, 15.5 	, trk.weight); 
   	plotter.Plot1D(Form("%s_%s_dvTracks_NSctHoles" 		, sample.c_str(), selection.c_str() ), ";NSctHoles;dv trks" 		, trk.NSctHoles			, 16, -0.5, 15.5 	, trk.weight); 
   	plotter.Plot1D(Form("%s_%s_dvTracks_NSctSharedHits" , sample.c_str(), selection.c_str() ), ";NSctSharedHits;dv trks" 	, trk.NSctSharedHits	, 16, -0.5, 15.5 	, trk.weight);   
   	plotter.Plot1D(Form("%s_%s_dvTracks_NTrtHits" 		, sample.c_str(), selection.c_str() ), ";NTrtHits;dv trks" 			, trk.NTrtHits			, 51, -0.5, 50.5 	, trk.weight); 
   	plotter.Plot1D(Form("%s_%s_dvTracks_NTrtOutliers" 	, sample.c_str(), selection.c_str() ), ";NTrtOutliers;dv trks" 		, trk.NTrtOutliers		, 51, -0.5, 50.5 	, trk.weight);  
   	plotter.Plot1D(Form("%s_%s_dvTracks_truthMatchProb" , sample.c_str(), selection.c_str() ), ";truthMatchProb;dv trks" 	, trk.truthMatchProb	, 20, 0, 1 			, trk.weight); 
   	plotter.Plot1D(Form("%s_%s_dvTracks_truthOrigin" 	, sample.c_str(), selection.c_str() ), ";truthOrigin;dv trks" 		, trk.truthOrigin		, 50, 0, 50 		, trk.weight); 
   	plotter.Plot1D(Form("%s_%s_dvTracks_truthType" 		, sample.c_str(), selection.c_str() ), ";truthType;dv trks" 		, trk.truthType	        , 50, 0, 50 		, trk.weight);

	return;
}
void reco_dv_plots(DV reco_dv, std::vector<TruthVertex> truth_vtxs, std::string sample="MC")
{
	// Individual properties 
	plotter.Plot1D(Form("%s_all_recodv_m" 		, sample.c_str() ),";m [GeV];reco dvs" 		, reco_dv.m 		, 100, 0, 100 		, reco_dv.weight );
	plotter.Plot1D(Form("%s_all_recodv_mbig" 	, sample.c_str() ),";m [GeV];reco dvs" 		, reco_dv.m 		, 100, 0, 1500 		, reco_dv.weight );
	plotter.Plot1D(Form("%s_all_recodv_ntrks"  	, sample.c_str() ),";nTracks;reco dvs" 		, reco_dv.nTracks 	, 51, -0.5, 50.5 	, reco_dv.weight );
	plotter.Plot1D(Form("%s_all_recodv_ntrksbig" , sample.c_str() ),";nTracks;reco dvs" 	, reco_dv.nTracks 	, 100, 0, 1000 		, reco_dv.weight );
	plotter.Plot1D(Form("%s_all_recodv_R"  		, sample.c_str() ),";R [mm];reco dvs" 		, reco_dv.r 		, 100, 0, 500 		, reco_dv.weight );
	plotter.Plot1D(Form("%s_all_recodv_Rxy" 	, sample.c_str() ),";Rxy [mm];reco dvs" 	, reco_dv.rxy 		, 100, 0, 300	 	, reco_dv.weight );
	plotter.Plot1D(Form("%s_all_recodv_z"  		, sample.c_str() ),";z [mm];reco dvs" 		, reco_dv.z 		, 100, -300, 300 	, reco_dv.weight );
	plotter.Plot1D(Form("%s_all_recodv_phi"  	, sample.c_str() ),";phi;reco dvs" 			, reco_dv.phi 		, 100, -3.5, 3.5 	, reco_dv.weight );

	// if dv is truth matched
	if (reco_dv.truth_match > -1 )
	{
		plotter.Plot1D(Form("%s_truthmatched_recodv_m" 			, sample.c_str() ),";m [GeV];reco dvs" 		, reco_dv.m 		, 100, 0, 100 		, reco_dv.weight );
		plotter.Plot1D(Form("%s_truthmatched_recodv_mbig" 		, sample.c_str() ),";m [GeV];reco dvs" 		, reco_dv.m 		, 100, 0, 1500 		, reco_dv.weight );
		plotter.Plot1D(Form("%s_truthmatched_recodv_ntrks"  	, sample.c_str() ),";nTracks;reco dvs" 		, reco_dv.nTracks 	, 25, -0.5, 24.5 	, reco_dv.weight );
		plotter.Plot1D(Form("%s_truthmatched_recodv_ntrksbig" 	, sample.c_str() ),";nTracks;reco dvs" 		, reco_dv.nTracks 	, 100, 0, 1000 		, reco_dv.weight );
		plotter.Plot1D(Form("%s_truthmatched_recodv_R"  		, sample.c_str() ),";R [mm];reco dvs" 		, reco_dv.r 		, 100, 0, 500 		, reco_dv.weight );
		plotter.Plot1D(Form("%s_truthmatched_recodv_Rxy" 		, sample.c_str() ),";Rxy [mm];reco dvs" 	, reco_dv.rxy 		, 100, 0, 300	 	, reco_dv.weight );
		plotter.Plot1D(Form("%s_truthmatched_recodv_z"  		, sample.c_str() ),";z [mm];reco dvs" 		, reco_dv.z 		, 100, -300, 300 	, reco_dv.weight );
		plotter.Plot1D(Form("%s_truthmatched_recodv_phi"  		, sample.c_str() ),";phi;reco dvs" 			, reco_dv.phi 		, 100, -3.5, 3.5 	, reco_dv.weight );	
	
		// get tracks? 
		for (auto trk: reco_dv.tracks)
		{
		 
			if (trk.isAssociated == 1) track_plots(sample, "truthmatched_recodv_attachedTracks", trk);
			else 					   track_plots(sample, "truthmatched_recodv_originalTracks", trk);
		}
	} 
	else // THIS DV is PROBABLY FAKE! 
	{
		plotter.Plot1D(Form("%s_unmatched_recodv_m" 		, sample.c_str() ),";m [GeV];reco dvs" 		, reco_dv.m 		, 100, 0, 100 		, reco_dv.weight );
		plotter.Plot1D(Form("%s_unmatched_recodv_mbig" 		, sample.c_str() ),";m [GeV];reco dvs" 		, reco_dv.m 		, 100, 0, 1500 		, reco_dv.weight );
		plotter.Plot1D(Form("%s_unmatched_recodv_ntrks"  	, sample.c_str() ),";nTracks;reco dvs" 		, reco_dv.nTracks 	, 51, -0.5, 50.5 	, reco_dv.weight );
		plotter.Plot1D(Form("%s_unmatched_recodv_ntrksbig" 	, sample.c_str() ),";nTracks;reco dvs" 		, reco_dv.nTracks 	, 100, 0, 1000 		, reco_dv.weight );
		plotter.Plot1D(Form("%s_unmatched_recodv_R"  		, sample.c_str() ),";R [mm];reco dvs" 		, reco_dv.r 		, 100, 0, 500 		, reco_dv.weight );
		plotter.Plot1D(Form("%s_unmatched_recodv_Rxy" 		, sample.c_str() ),";Rxy [mm];reco dvs" 	, reco_dv.rxy 		, 100, 0, 300	 	, reco_dv.weight );
		plotter.Plot1D(Form("%s_unmatched_recodv_z"  		, sample.c_str() ),";z [mm];reco dvs" 		, reco_dv.z 		, 100, -300, 300 	, reco_dv.weight );
		plotter.Plot1D(Form("%s_unmatched_recodv_phi"  		, sample.c_str() ),";phi;reco dvs" 			, reco_dv.phi 		, 100, -3.5, 3.5 	, reco_dv.weight );	
	
		// get tracks? 
		for (auto trk: reco_dv.tracks)
		{
		 
			if (trk.isAssociated == 1) track_plots(sample, "unmatched_recodv_attachedTracks", trk);
			else 					   track_plots(sample, "unmatched_recodv_originalTracks", trk);
		}

	} 


	return;
}
void truth_dv_plots(TruthVertex truth_dv, std::vector<DV> reco_dvs, std::string sample="MC")
{
	// Individual properties 
	plotter.Plot1D(Form("%s_all_truthdv_m" 			, sample.c_str() ),";m [GeV];truth dvs" 	, truth_dv.mCh1GeVd0 	, 100, 0, 1500 		, truth_dv.weight );
	plotter.Plot1D(Form("%s_all_truthdv_ntrks"  	, sample.c_str() ),";nTracks;truth dvs" 	, truth_dv.nCh1GeVd0 	, 25, -0.5, 24.5 	, truth_dv.weight );
	plotter.Plot1D(Form("%s_all_truthdv_R"  		, sample.c_str() ),";R [mm];truth dvs" 		, truth_dv.r 			, 100, 0, 500 		, truth_dv.weight );
	plotter.Plot1D(Form("%s_all_truthdv_Rxy" 		, sample.c_str() ),";Rxy [mm];truth dvs" 	, truth_dv.rxy 			, 100, 0, 300	 	, truth_dv.weight );
	plotter.Plot1D(Form("%s_all_truthdv_z"  		, sample.c_str() ),";z [mm];truth dvs" 		, truth_dv.z 			, 100, -300, 300 	, truth_dv.weight );

	// if truth vertex is reco matched
	if (truth_dv.reco_match > -1 )
	{
		plotter.Plot1D(Form("%s_recomatched_truthdv_m" 			, sample.c_str() ),";m [GeV];truth dvs" 	, truth_dv.mCh1GeVd0 	, 100, 0, 1500 		, truth_dv.weight );
		plotter.Plot1D(Form("%s_recomatched_truthdv_ntrks"  	, sample.c_str() ),";nTracks;truth dvs" 	, truth_dv.nCh1GeVd0 	, 25, -0.5, 24.5 	, truth_dv.weight );
		plotter.Plot1D(Form("%s_recomatched_truthdv_R"  		, sample.c_str() ),";R [mm];truth dvs" 		, truth_dv.r 			, 100, 0, 500 		, truth_dv.weight );
		plotter.Plot1D(Form("%s_recomatched_truthdv_Rxy" 		, sample.c_str() ),";Rxy [mm];truth dvs" 	, truth_dv.rxy 			, 100, 0, 300	 	, truth_dv.weight );
		plotter.Plot1D(Form("%s_recomatched_truthdv_z"  		, sample.c_str() ),";z [mm];truth dvs" 		, truth_dv.z 			, 100, -300, 300 	, truth_dv.weight );
	
		float bins=20;
		DV reco_dv = return_reco_vertex(truth_dv.reco_match, reco_dvs);
		// truth tracks which are reconstructed
		plotter.Plot2D(Form("%s_recomatched_tracking_truthdv_m_recodv_m"			, sample.c_str() ),";m truth accep tracks [GeV];m truth reco tracks [GeV];reco matched DVs"	 , truth_dv.mCh1GeVd0, truth_dv.mCh1GeVd0distReco      , 100, 0, 1500  , 100, 0, 1500  , truth_dv.weight );
		plotter.Plot2D(Form("%s_recomatched_tracking_truthdv_ntrks_recodv_ntrks" 	, sample.c_str() ),";ntrk truth accep;ntrk truth reco tracks;reco matched DVs"      	 , truth_dv.nCh1GeVd0, truth_dv.nCh1GeVd0distReco, bins, -0.5, bins-0.5, bins, -0.5, bins-0.5, truth_dv.weight );
		plotter.Plot2D(Form("%s_recomatched_tracking_mdiff_truthdv_rxy"				, sample.c_str() ),";Rxy [mm];m truth reco tracks - truth accep tracks[GeV];reco matched DVs", truth_dv.rxy, truth_dv.mCh1GeVd0distReco - truth_dv.mCh1GeVd0        , 100, 0, 300, 100, -1500, 1500, truth_dv.weight );
		plotter.Plot2D(Form("%s_recomatched_tracking_ntrkdiff_truthdv_rxy"			, sample.c_str() ),";Rxy [mm];ntrks truth reco tracks - truth accp tracks;reco matched DVs"  , truth_dv.rxy, truth_dv.nCh1GeVd0distReco - truth_dv.nCh1GeVd0  , 100, 0, 300,  bins+1, -bins/2-0.5, bins/2+0.5, truth_dv.weight );
		plotter.Plot2D(Form("%s_recomatched_tracking_ntrkdiff_mdiff"			 	, sample.c_str() ),";ntrks truth reco tracks - truth accep tracks;m truth reco tracks - truth accp tracks [GeV];reco matched DVs"  , truth_dv.nCh1GeVd0distReco - truth_dv.nCh1GeVd0, truth_dv.mCh1GeVd0distReco - truth_dv.mCh1GeVd0 , bins+1, -bins/2-0.5, bins/2+0.5, 100, -1500, 1500, truth_dv.weight );

		// truth tracks, reconstructed, which are vertexed
		plotter.Plot2D(Form("%s_recomatched_vertexing_truthdv_m_recodv_m"			, sample.c_str() ),";m truth reco tracks[GeV];m reco dv [GeV];reco matched DVs"	 , truth_dv.mCh1GeVd0distReco, reco_dv.m      , 100, 0, 1500  , 100, 0, 1500  , truth_dv.weight );
		plotter.Plot2D(Form("%s_recomatched_vertexing_truthdv_ntrks_recodv_ntrks" 	, sample.c_str() ),";ntrk truth reco tracks;ntrk reco dv;reco matched DVs"      	 , truth_dv.nCh1GeVd0distReco, reco_dv.nTracks, bins, -0.5, bins-0.5, bins, -0.5, bins-0.5, truth_dv.weight );
		plotter.Plot2D(Form("%s_recomatched_vertexing_mdiff_truthdv_rxy"			, sample.c_str() ),";Rxy [mm];m reco dv - truth reco tracks[GeV];reco matched DVs", truth_dv.rxy, reco_dv.m - truth_dv.mCh1GeVd0distReco        , 100, 0, 300, 100, -1500, 1500, truth_dv.weight );
		plotter.Plot2D(Form("%s_recomatched_vertexing_ntrkdiff_truthdv_rxy"			, sample.c_str() ),";Rxy [mm];ntrks reco dv - truth reco tracks;reco matched DVs"  , truth_dv.rxy, reco_dv.nTracks - truth_dv.nCh1GeVd0distReco  , 100, 0, 300,  bins+1, -bins/2-0.5, bins/2+0.5, truth_dv.weight );
		plotter.Plot2D(Form("%s_recomatched_vertexing_ntrkdiff_mdiff"			 	, sample.c_str() ),";ntrks reco dv - truth reco tracks;m reco dv - truth reco tracks[GeV];reco matched DVs"  , reco_dv.nTracks - truth_dv.nCh1GeVd0distReco, reco_dv.m - truth_dv.mCh1GeVd0distReco , bins+1, -bins/2-0.5, bins/2+0.5, 100, -1500, 1500, truth_dv.weight );

		// truth tracks which are vertexed
		plotter.Plot2D(Form("%s_recomatched_both_truthdv_m_recodv_m"			, sample.c_str() ),";m truth accep tracks [GeV];m reco dv [GeV];reco matched DVs"	 , truth_dv.mCh1GeVd0, reco_dv.m      , 100, 0, 1500  , 100, 0, 1500  , truth_dv.weight );
		plotter.Plot2D(Form("%s_recomatched_both_truthdv_ntrks_recodv_ntrks" 	, sample.c_str() ),";ntrk truth accep tracks;ntrk reco dv;reco matched DVs"      	 , truth_dv.nCh1GeVd0, reco_dv.nTracks, bins, -0.5, bins-0.5, bins, -0.5, bins-0.5, truth_dv.weight );
		plotter.Plot2D(Form("%s_recomatched_both_mdiff_truthdv_rxy"				, sample.c_str() ),";Rxy [mm];m reco dv - truth accep tracks[GeV];reco matched DVs", truth_dv.rxy, reco_dv.m - truth_dv.mCh1GeVd0        , 100, 0, 300, 100, -1500, 1500, truth_dv.weight );
		plotter.Plot2D(Form("%s_recomatched_both_ntrkdiff_truthdv_rxy"			, sample.c_str() ),";Rxy [mm];ntrks reco dv- truth accep tracks;reco matched DVs"  , truth_dv.rxy, reco_dv.nTracks - truth_dv.nCh1GeVd0  , 100, 0, 300,  bins+1, -bins/2-0.5, bins/2+0.5, truth_dv.weight );
		plotter.Plot2D(Form("%s_recomatched_both_ntrkdiff_mdiff"			    , sample.c_str() ),";ntrks reco dv - truth accep traacks;m reco dv - truth accep tracks [GeV];reco matched DVs"  , reco_dv.nTracks - truth_dv.nCh1GeVd0, reco_dv.m - truth_dv.mCh1GeVd0 , bins+1, -bins/2-0.5, bins/2+0.5, 100, -1500, 1500, truth_dv.weight );
		//Muon reco_mu = return_reco_muon(truth_mu.reco_match, reco_mus);
		//plotter.Plot1D(Form("%s_recoMatched_muon_dR"  , sample.c_str() ),";#DeltaR(reco,truth);matched muons" 	, truth_mu.p4.DeltaR(reco_mu.p4) , 100, 0, 0.1, truth_mu.weight );
	} 
	else
	{
		plotter.Plot1D(Form("%s_unmatched_truthdv_m" 		, sample.c_str() ),";m [GeV];truth dvs" 	, truth_dv.mCh1GeVd0 	, 100, 0, 1500 		, truth_dv.weight );
		plotter.Plot1D(Form("%s_unmatched_truthdv_ntrks"  	, sample.c_str() ),";nTracks;truth dvs" 	, truth_dv.nCh1GeVd0 	, 25, -0.5, 24.5 	, truth_dv.weight );
		plotter.Plot1D(Form("%s_unmatched_truthdv_R"  		, sample.c_str() ),";R [mm];truth dvs" 		, truth_dv.r 			, 100, 0, 500 		, truth_dv.weight );
		plotter.Plot1D(Form("%s_unmatched_truthdv_Rxy" 		, sample.c_str() ),";Rxy [mm];truth dvs" 	, truth_dv.rxy 			, 100, 0, 300	 	, truth_dv.weight );
		plotter.Plot1D(Form("%s_unmatched_truthdv_z"  		, sample.c_str() ),";z [mm];truth dvs" 		, truth_dv.z 			, 100, -300, 300 	, truth_dv.weight );


	} 


	return;
}

