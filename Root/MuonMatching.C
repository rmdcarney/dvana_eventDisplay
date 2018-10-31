


// ***************************
// Functions to do muon matching 
// ***************************
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
	plotter.Plot1D(Form("%s_all_truthmuon_eta" , sample.c_str() ),";truth eta;truth muons" 		, truth_mu.eta, 100, -3.5, 3.5 		, truth_mu.weight );
	plotter.Plot1D(Form("%s_all_truthmuon_pt"  , sample.c_str() ),";truth pT [GeV];truth muons" , truth_mu.pt , 100, 0, 2000 	, truth_mu.weight );
	plotter.Plot1D(Form("%s_all_truthmuon_phi" , sample.c_str() ),";truth phi;truth muons" 		, truth_mu.phi, 100, -3.5, 3.5 	, truth_mu.weight );
	plotter.Plot1D(Form("%s_all_truthmuon_d0"  , sample.c_str() ),";truth d0 [mm];truth muons" 	, truth_mu.d0 , 100, 0, 300 	, truth_mu.weight );

	// With Acceptance
	if (truth_mu.d0 < 300 && fabs(truth_mu.eta) < 2.5 && truth_mu.pt > 25){
		plotter.Plot1D(Form("%s_acceptance_truthmuon_eta" , sample.c_str() ),";truth eta;truth muons" 		, truth_mu.eta, 100, -3.5, 3.5 	, truth_mu.weight );
		plotter.Plot1D(Form("%s_acceptance_truthmuon_pt"  , sample.c_str() ),";truth pT [GeV];truth muons"  , truth_mu.pt , 100, 0, 2000 	, truth_mu.weight );
		plotter.Plot1D(Form("%s_acceptance_truthmuon_phi" , sample.c_str() ),";truth phi;truth muons" 		, truth_mu.phi, 100, -3.5, 3.5 	, truth_mu.weight );
		plotter.Plot1D(Form("%s_acceptance_truthmuon_d0"  , sample.c_str() ),";truth d0 [mm];truth muons" 	, truth_mu.d0 , 100, 0, 300 	, truth_mu.weight );		
	} 

	// if reco matched
	if (truth_mu.d0 < 300 && fabs(truth_mu.eta) < 2.5 && truth_mu.pt > 25 && truth_mu.reco_match > -1 )
	{
		plotter.Plot1D(Form("%s_recomatched_truthmuon_eta" , sample.c_str() ),";truth eta;truth muons" 		, truth_mu.eta, 100, -3.5, 3.5 	, truth_mu.weight );
		plotter.Plot1D(Form("%s_recomatched_truthmuon_pt"  , sample.c_str() ),";truth pT [GeV];truth muons" , truth_mu.pt , 100, 0, 2000 	, truth_mu.weight );
		plotter.Plot1D(Form("%s_recomatched_truthmuon_phi" , sample.c_str() ),";truth phi;truth muons" 		, truth_mu.phi, 100, -3.5, 3.5 	, truth_mu.weight );
		plotter.Plot1D(Form("%s_recomatched_truthmuon_d0"  , sample.c_str() ),";truth d0 [mm];truth muons" 	, truth_mu.d0 , 100, 0, 300 	, truth_mu.weight );		
	
		Muon reco_mu = return_reco_muon(truth_mu.reco_match, reco_mus);
		plotter.Plot1D(Form("%s_recomatched_muon_dR"  , sample.c_str() ),";#DeltaR(reco,truth);matched muons" 	, truth_mu.p4.DeltaR(reco_mu.p4) , 100, 0, 0.1, truth_mu.weight );

	} 

	// Compared to reco muon

	return;
}
void unmatched_muon_plots(){
	return;
}