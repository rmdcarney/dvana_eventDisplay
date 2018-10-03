
//
// Functions necessary to do vertex and reco matching 
//
float sphereCut(float DVR){
	return 0.0133333333*DVR + 1;
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
		if ( truth_vtx.index == index ) dv = truth_vtx;
	}
	return dv;
}
DV return_reco_vertex(int index, std::vector<DV> reco_dvs)
{
	// returns a matching reco muon
	DV dv;
	for (auto reco_dv : reco_dvs )
	{
		if ( reco_dv.index == index ) dv = reco_dv;
	}
	return dv;
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

	// if reco matched
	if (reco_dv.truth_match > -1 )
	{
		plotter.Plot1D(Form("%s_truthmatched_recodv_m" 			, sample.c_str() ),";m [GeV];reco dvs" 		, reco_dv.m 		, 100, 0, 100 		, reco_dv.weight );
		plotter.Plot1D(Form("%s_truthmatched_recodv_mbig" 		, sample.c_str() ),";m [GeV];reco dvs" 		, reco_dv.m 		, 100, 0, 1500 		, reco_dv.weight );
		plotter.Plot1D(Form("%s_truthmatched_recodv_ntrks"  	, sample.c_str() ),";nTracks;reco dvs" 		, reco_dv.nTracks 	, 51, -0.5, 50.5 	, reco_dv.weight );
		plotter.Plot1D(Form("%s_truthmatched_recodv_ntrksbig" 	, sample.c_str() ),";nTracks;reco dvs" 		, reco_dv.nTracks 	, 100, 0, 1000 		, reco_dv.weight );
		plotter.Plot1D(Form("%s_truthmatched_recodv_R"  		, sample.c_str() ),";R [mm];reco dvs" 		, reco_dv.r 		, 100, 0, 500 		, reco_dv.weight );
		plotter.Plot1D(Form("%s_truthmatched_recodv_Rxy" 		, sample.c_str() ),";Rxy [mm];reco dvs" 	, reco_dv.rxy 		, 100, 0, 300	 	, reco_dv.weight );
		plotter.Plot1D(Form("%s_truthmatched_recodv_z"  		, sample.c_str() ),";z [mm];reco dvs" 		, reco_dv.z 		, 100, -300, 300 	, reco_dv.weight );
		plotter.Plot1D(Form("%s_truthmatched_recodv_phi"  		, sample.c_str() ),";phi;reco dvs" 			, reco_dv.phi 		, 100, -3.5, 3.5 	, reco_dv.weight );	
	
		//Muon reco_mu = return_reco_muon(truth_mu.reco_match, reco_mus);
		//plotter.Plot1D(Form("%s_recoMatched_muon_dR"  , sample.c_str() ),";#DeltaR(reco,truth);matched muons" 	, truth_mu.p4.DeltaR(reco_mu.p4) , 100, 0, 0.1, truth_mu.weight );
	} 
	else
	{
		plotter.Plot1D(Form("%s_unmatched_recodv_m" 		, sample.c_str() ),";m [GeV];reco dvs" 		, reco_dv.m 		, 100, 0, 100 		, reco_dv.weight );
		plotter.Plot1D(Form("%s_unmatched_recodv_mbig" 		, sample.c_str() ),";m [GeV];reco dvs" 		, reco_dv.m 		, 100, 0, 1500 		, reco_dv.weight );
		plotter.Plot1D(Form("%s_unmatched_recodv_ntrks"  	, sample.c_str() ),";nTracks;reco dvs" 		, reco_dv.nTracks 	, 51, -0.5, 50.5 	, reco_dv.weight );
		plotter.Plot1D(Form("%s_unmatched_recodv_ntrksbig" 	, sample.c_str() ),";nTracks;reco dvs" 		, reco_dv.nTracks 	, 100, 0, 1000 		, reco_dv.weight );
		plotter.Plot1D(Form("%s_unmatched_recodv_R"  		, sample.c_str() ),";R [mm];reco dvs" 		, reco_dv.r 		, 100, 0, 500 		, reco_dv.weight );
		plotter.Plot1D(Form("%s_unmatched_recodv_Rxy" 		, sample.c_str() ),";Rxy [mm];reco dvs" 	, reco_dv.rxy 		, 100, 0, 300	 	, reco_dv.weight );
		plotter.Plot1D(Form("%s_unmatched_recodv_z"  		, sample.c_str() ),";z [mm];reco dvs" 		, reco_dv.z 		, 100, -300, 300 	, reco_dv.weight );
		plotter.Plot1D(Form("%s_unmatched_recodv_phi"  		, sample.c_str() ),";phi;reco dvs" 			, reco_dv.phi 		, 100, -3.5, 3.5 	, reco_dv.weight );	
	
		//Muon reco_mu = return_reco_muon(truth_mu.reco_match, reco_mus);
		//plotter.Plot1D(Form("%s_recoMatched_muon_dR"  , sample.c_str() ),";#DeltaR(reco,truth);matched muons" 	, truth_mu.p4.DeltaR(reco_mu.p4) , 100, 0, 0.1, truth_mu.weight );
	} 

	// Compared to reco muon

	return;
}


//
// Functions to do muon matching 
//
int find_matching_reco_muon(std::vector<Muon> reco_mus, TruthMuon truth_mu)
{

	float dR=0.4;
	int match = -1;
	float dist = 999999;
	for (auto reco_mu : reco_mus)
	{
		// compute R cutoff for DV
		
		float dist_tmp = reco_mu.p4.DeltaR(truth_mu.p4);
		if (dist_tmp < dR && dist_tmp < dist){
			dist = dist_tmp;
			match = reco_mu.index;
		}
	}
	return match;
}
int find_matching_truth_muon(Muon reco_mu, std::vector<TruthMuon> truth_mus)
{

	float dR=0.4;
	int match = -1;
	float dist = 999999;
	for (auto truth_mu : truth_mus)
	{
		// compute R cutoff for DV
		
		float dist_tmp = reco_mu.p4.DeltaR(truth_mu.p4);
		if (dist_tmp < dR && dist_tmp < dist){
			dist = dist_tmp;
			match = reco_mu.index;
		}
	}
	return match;
}
Muon return_reco_muon(int index, std::vector<Muon> reco_mus)
{
	// returns a matching reco muon
	Muon mu;
	for (auto reco_mu : reco_mus )
	{
		if ( reco_mu.index == index ) mu = reco_mu;
	}
	return mu;
}
TruthMuon return_truth_muon(int index, std::vector<TruthMuon> truth_mus)
{
	// returns a matching truth muon
	TruthMuon mu;
	for (auto truth_mu : truth_mus )
	{
		if ( truth_mu.index == index ) mu = truth_mu;
	}
	return mu;
}

//
// Functions necessary to plot muon matching 
//

void matched_muon_plots(TruthMuon truth_mu, std::vector<Muon> reco_mus, std::string sample="MC")
{
	// Individual properties 
	plotter.Plot1D(Form("%s_all_truthmuon_eta" , sample.c_str() ),";truth eta;truth muons" 		, truth_mu.eta, 100, -5, 5 		, truth_mu.weight );
	plotter.Plot1D(Form("%s_all_truthmuon_pt"  , sample.c_str() ),";truth pT [GeV];truth muons" , truth_mu.pt , 100, 0, 2000 	, truth_mu.weight );
	plotter.Plot1D(Form("%s_all_truthmuon_phi" , sample.c_str() ),";truth phi;truth muons" 		, truth_mu.phi, 100, -3.5, 3.5 	, truth_mu.weight );
	plotter.Plot1D(Form("%s_all_truthmuon_d0"  , sample.c_str() ),";truth d0 [mm];truth muons" 	, truth_mu.d0 , 100, 0, 300 	, truth_mu.weight );

	// if reco matched
	if (truth_mu.reco_match > -1 )
	{
		plotter.Plot1D(Form("%s_recoMatched_truthmuon_eta" , sample.c_str() ),";truth eta;truth muons" 		, truth_mu.eta, 100, -5, 5 		, truth_mu.weight );
		plotter.Plot1D(Form("%s_recoMatched_truthmuon_pt"  , sample.c_str() ),";truth pT [GeV];truth muons" , truth_mu.pt , 100, 0, 2000 	, truth_mu.weight );
		plotter.Plot1D(Form("%s_recoMatched_truthmuon_phi" , sample.c_str() ),";truth phi;truth muons" 		, truth_mu.phi, 100, -3.5, 3.5 	, truth_mu.weight );
		plotter.Plot1D(Form("%s_recoMatched_truthmuon_d0"  , sample.c_str() ),";truth d0 [mm];truth muons" 	, truth_mu.d0 , 100, 0, 300 	, truth_mu.weight );		
	
		Muon reco_mu = return_reco_muon(truth_mu.reco_match, reco_mus);
		plotter.Plot1D(Form("%s_recoMatched_muon_dR"  , sample.c_str() ),";#DeltaR(reco,truth);matched muons" 	, truth_mu.p4.DeltaR(reco_mu.p4) , 100, 0, 0.1, truth_mu.weight );

	} 

	// Compared to reco muon

	return;
}
void unmatched_muon_plots(){
	return;
}