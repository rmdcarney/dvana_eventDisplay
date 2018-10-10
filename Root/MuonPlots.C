#define muonPlots_cxx


void muonTriggerEfficiency(std::string sample_name, std::vector<Muon> muons, std::string selection, float weight=1.)
{

	for (auto mu : muons)
	{
		
		if (mu.ptvarcone30 < 0.15 && mu.topoetcone30 < 0.3 && mu.CBchi2 < 8 && mu.nPres > 2 && fabs(mu.d0)<300 && fabs(mu.z0)<300){ // fake and heavy flavor cuts

			plotter.Plot1D(Form("%s_mu_msonlytrigdenom_eta" ,  sample_name.c_str()),";|#eta|;muons" 	, mu.eta, 50 , -1.1, 1.1  , mu.weight);
			plotter.Plot1D(Form("%s_mu_msonlytrigdenom_phi" ,  sample_name.c_str()),";#phi;muons" 		, mu.phi, 50 , -3.5,  3.5  , mu.weight);
			plotter.Plot1D(Form("%s_mu_msonlytrigdenom_pt"  ,  sample_name.c_str()),";p_{T} [GeV];muons", mu.pt , 20 ,   50,   70  , mu.weight);
			plotter.Plot1D(Form("%s_mu_msonlytrigdenom_d0"  ,  sample_name.c_str()),";|d0| [mm];muons" 	, fabs(mu.d0) , 30 ,   0, 300  , mu.weight);
			plotter.Plot1D(Form("%s_mu_msonlytrigdenom_z0"  ,  sample_name.c_str()),";|z0| [mm];muons" 	, fabs(mu.z0) , 30 ,   0, 300  , mu.weight);

			if (fabs(mu.eta) < 1.07){
				plotter.Plot1D(Form("%s_mu_msonlytrigdenometa_eta" ,  sample_name.c_str()),";#eta;muons" 		, mu.eta, 50 , -1.1, 1.1  , mu.weight);
				plotter.Plot1D(Form("%s_mu_msonlytrigdenometa_phi" ,  sample_name.c_str()),";#phi;muons" 		, mu.phi, 50 , -3.5,  3.5  , mu.weight);
				plotter.Plot1D(Form("%s_mu_msonlytrigdenometa_pt"  ,  sample_name.c_str()),";p_{T} [GeV];muons" , mu.pt , 20 ,   50,   70  , mu.weight);
				plotter.Plot1D(Form("%s_mu_msonlytrigdenometa_d0"  ,  sample_name.c_str()),";|d0| [mm];muons" 	, fabs(mu.d0) , 30 ,   0, 300  , mu.weight);
				plotter.Plot1D(Form("%s_mu_msonlytrigdenometa_z0"  ,  sample_name.c_str()),";|z0| [mm];muons" 	, fabs(mu.z0) , 30 ,   0, 300  , mu.weight);
			}
			if (mu.pt > 62){
				plotter.Plot1D(Form("%s_mu_msonlytrigdenompt_eta" ,  sample_name.c_str()),";#eta;muons" 		, mu.eta, 50 , -1.1, 1.1  , mu.weight);
				plotter.Plot1D(Form("%s_mu_msonlytrigdenompt_phi" ,  sample_name.c_str()),";#phi;muons" 		, mu.phi, 50 , -3.5,  3.5  , mu.weight);
				plotter.Plot1D(Form("%s_mu_msonlytrigdenompt_pt"  ,  sample_name.c_str()),";p_{T} [GeV];muons" 	, mu.pt , 20 ,   50,   70  , mu.weight);
				plotter.Plot1D(Form("%s_mu_msonlytrigdenompt_d0"  ,  sample_name.c_str()),";|d0| [mm];muons" 	, fabs(mu.d0) , 30 ,   0, 300  , mu.weight);
				plotter.Plot1D(Form("%s_mu_msonlytrigdenompt_z0"  ,  sample_name.c_str()),";|z0| [mm];muons" 	, fabs(mu.z0) , 30 ,   0, 300  , mu.weight);
			}
			if (fabs(mu.eta) < 1.07 && mu.pt > 62){
				plotter.Plot1D(Form("%s_mu_msonlytrigdenompteta_eta" ,  sample_name.c_str()),";#eta;muons" 		, mu.eta, 50 , -1.1, 1.1  , mu.weight);
				plotter.Plot1D(Form("%s_mu_msonlytrigdenompteta_phi" ,  sample_name.c_str()),";#phi;muons" 		, mu.phi, 50 , -3.5,  3.5  , mu.weight);
				plotter.Plot1D(Form("%s_mu_msonlytrigdenompteta_pt"  ,  sample_name.c_str()),";p_{T} [GeV];muons" 	, mu.pt , 20 ,   50,   70  , mu.weight);
				plotter.Plot1D(Form("%s_mu_msonlytrigdenompteta_d0"  ,  sample_name.c_str()),";|d0| [mm];muons" 	, fabs(mu.d0) , 30 ,   0, 300  , mu.weight);
				plotter.Plot1D(Form("%s_mu_msonlytrigdenompteta_z0"  ,  sample_name.c_str()),";|z0| [mm];muons" 	, fabs(mu.z0) , 30 ,   0, 300  , mu.weight);
			}
			if (mu.TMmsonly){
				plotter.Plot1D(Form("%s_mu_msonlytrignum_eta" ,  sample_name.c_str()),";#eta;muons" 		, mu.eta, 50 , -1.1, 1.1  , mu.weight);
				plotter.Plot1D(Form("%s_mu_msonlytrignum_phi" ,  sample_name.c_str()),";#phi;muons" 		, mu.phi, 50 , -3.5,  3.5  , mu.weight);
				plotter.Plot1D(Form("%s_mu_msonlytrignum_pt"  ,  sample_name.c_str()),";p_{T} [GeV];muons" 	, mu.pt , 20 ,   50,   70  , mu.weight);
				plotter.Plot1D(Form("%s_mu_msonlytrignum_d0"  ,  sample_name.c_str()),";|d0| [mm];muons" 	, fabs(mu.d0) , 30 ,   0, 300  , mu.weight);
				plotter.Plot1D(Form("%s_mu_msonlytrignum_z0"  ,  sample_name.c_str()),";|z0| [mm];muons" 	, fabs(mu.z0) , 30 ,   0, 300  , mu.weight);
			}

		}

	}

	return;
}

void muonPlots1D(std::string sample_name, Muon mu, std::string event_selection, std::string muon_selection, float weight=1.)
{
	// kinematics
	plotter.Plot1D(Form("%s_%s_%s_mu_d0" ,    sample_name.c_str(),event_selection.c_str(),muon_selection.c_str()),";d0(#mu) [mm];Muons"       , mu.d0 ,  50., -300, 300  , mu.weight);
	plotter.Plot1D(Form("%s_%s_%s_mu_z0" ,    sample_name.c_str(),event_selection.c_str(),muon_selection.c_str()),";z0(#mu) [mm];Muons"       , mu.z0 ,  50., -300, 300  , mu.weight);
	plotter.Plot1D(Form("%s_%s_%s_mu_eta",    sample_name.c_str(),event_selection.c_str(),muon_selection.c_str()),";#eta(#mu);Muons"          , mu.eta,  50., -3.5, 3.5  , mu.weight);
	plotter.Plot1D(Form("%s_%s_%s_mu_phi",    sample_name.c_str(),event_selection.c_str(),muon_selection.c_str()),";#phi(#mu);Muons"          , mu.phi,  50., -3.5, 3.5  , mu.weight);
	plotter.Plot1D(Form("%s_%s_%s_mu_pt" ,    sample_name.c_str(),event_selection.c_str(),muon_selection.c_str()),";p_{T}(#mu) [GeV];Muons"   , mu.pt ,  50.,    0, 1000 , mu.weight);
	
	// Fakes 
	if (fabs(mu.eta)<1.05)  
	{
		plotter.Plot1D(Form("%s_%s_%s_mu_nPresBA" ,   sample_name.c_str(),event_selection.c_str(),muon_selection.c_str()),";nPrec;Muons"   	, mu.nPres    ,  7., -0.5, 6.5 , mu.weight);
		if (fabs(mu.CBchi2)<8) plotter.Plot1D(Form("%s_%s_%s_mu_nPresBAchi2" ,   sample_name.c_str(),event_selection.c_str(),muon_selection.c_str()),";nPrec;Muons"   	, mu.nPres    ,  7., -0.5, 6.5 , mu.weight);
	}
	else 
	{				
		plotter.Plot1D(Form("%s_%s_%s_mu_nPresEC" ,   sample_name.c_str(),event_selection.c_str(),muon_selection.c_str()),";nPrec;Muons"   	, mu.nPres    ,  7., -0.5, 6.5 , mu.weight);
		if (fabs(mu.CBchi2)<8) plotter.Plot1D(Form("%s_%s_%s_mu_nPresECchi2" ,   sample_name.c_str(),event_selection.c_str(),muon_selection.c_str()),";nPrec;Muons"   	, mu.nPres    ,  7., -0.5, 6.5 , mu.weight);
	}
	plotter.Plot1D(Form("%s_%s_%s_mu_nPres"    ,   sample_name.c_str(),event_selection.c_str(),muon_selection.c_str()),";nPrec;Muons"   	, mu.nPres    ,  7., -0.5, 6.5 , mu.weight);
	plotter.Plot1D(Form("%s_%s_%s_mu_nPresGood",   sample_name.c_str(),event_selection.c_str(),muon_selection.c_str()),";nPrecGood;Muons"   , mu.nPresGood,  7., -0.5, 6.5 , mu.weight);
	plotter.Plot1D(Form("%s_%s_%s_mu_nPresHole",   sample_name.c_str(),event_selection.c_str(),muon_selection.c_str()),";nPrecHole;Muons"   , mu.nPresHole,  7., -0.5, 6.5 , mu.weight);

	plotter.Plot1D(Form("%s_%s_%s_mu_nPIX",   sample_name.c_str(),event_selection.c_str(),muon_selection.c_str()),";nPIX on ID Track;Muons"    	, mu.nPIX  	,  10., -0.5, 9.5 , mu.weight);
	plotter.Plot1D(Form("%s_%s_%s_mu_nSCT",   sample_name.c_str(),event_selection.c_str(),muon_selection.c_str()),";nSCT on ID Track;Muons"    	, mu.nSCT  	,  20., -0.5, 19.5, mu.weight);
	plotter.Plot1D(Form("%s_%s_%s_mu_nTRT",   sample_name.c_str(),event_selection.c_str(),muon_selection.c_str()),";nTRT on ID Track;Muons"    	, mu.nTRT  	,  50., -0.5, 49.5, mu.weight);
	plotter.Plot1D(Form("%s_%s_%s_mu_CBchi2", sample_name.c_str(),event_selection.c_str(),muon_selection.c_str()),";CB#chi^{2}/N_{DoF};Muons"  , mu.CBchi2	, 40, 0.,10.     , mu.weight);
	plotter.Plot1D(Form("%s_%s_%s_mu_QoverP", sample_name.c_str(),event_selection.c_str(),muon_selection.c_str()),";Q/P Signif.;Muons" 		, mu.qOverP	, 40, 0.,8.      , mu.weight);
	
	// Cosmic 
   	plotter.Plot1D(Form("%s_%s_%s_mu_dRcos", sample_name.c_str(),event_selection.c_str(),muon_selection.c_str()), ";min #DeltaR_{cos}(#mu,seg);Muons"	, mu.dRcos  , 40, 0.0, 2., mu.weight);	
   	
   	// Heavy Flavor
   	plotter.Plot1D(Form("%s_%s_%s_mu_ptvarcone30" , sample_name.c_str(),event_selection.c_str(),muon_selection.c_str()), ";ptvarcone30/p_{T};Muons"	, mu.ptvarcone30  , 100,  0.0, 1., mu.weight);	
   	plotter.Plot1D(Form("%s_%s_%s_mu_topoetcone20", sample_name.c_str(),event_selection.c_str(),muon_selection.c_str()), ";topoetcone20/p_{T};Muons"	, mu.topoetcone20 , 100,  0.0, 1., mu.weight);
   	plotter.Plot1D(Form("%s_%s_%s_mu_dRjet"       , sample_name.c_str(),event_selection.c_str(),muon_selection.c_str()), ";#DeltaR(#mu,jet);Muons"	, mu.dRjet         , 100, 0.0, 3., mu.weight);	
		
	// different zoom 
	plotter.Plot1D(Form("%s_%s_%s_mu_abseta" 	 , sample_name.c_str(),event_selection.c_str(),muon_selection.c_str()),";|#eta(#mu)|;Muons"         , fabs(mu.eta),  50.,    0, 1.1  , mu.weight);
	plotter.Plot1D(Form("%s_%s_%s_mu_etazoom" 	 , sample_name.c_str(),event_selection.c_str(),muon_selection.c_str()),";#eta(#mu);Muons"           , mu.eta      ,  25., -1.1, 1.1  , mu.weight);
	plotter.Plot1D(Form("%s_%s_%s_mu_d0zoom"  	 , sample_name.c_str(),event_selection.c_str(),muon_selection.c_str()),";|d0(#mu)|;Muons"           , fabs(mu.d0) ,  75., 0, 15      , mu.weight);
	plotter.Plot1D(Form("%s_%s_%s_mu_ptzoom"  	 , sample_name.c_str(),event_selection.c_str(),muon_selection.c_str()),";p_{T}(#mu) [GeV];Muons"    , mu.pt       ,  75.,  25, 100   , mu.weight);
	plotter.Plot1D(Form("%s_%s_%s_mu_ptunzoom"   , sample_name.c_str(),event_selection.c_str(),muon_selection.c_str()),";p_{T}(#mu) [GeV];Muons"    , mu.pt       ,  100., 0, 2000   , mu.weight);
	plotter.Plot1D(Form("%s_%s_%s_mu_CBchi2zoom" , sample_name.c_str(),event_selection.c_str(),muon_selection.c_str()),";CB#chi^{2}/N_{DoF};Muons"  , mu.CBchi2   ,  100,  0., 50.   , mu.weight);

	return;
}
void muonPlots2D(std::string sample_name,  Muon mu, std::string event_selection, std::string muon_selection, float weight=1.)
{
	
	plotter.Plot2D(Form("%s_%s_%s_mu_z0_d0"    , sample_name.c_str(),event_selection.c_str(),muon_selection.c_str()), ";z0(#mu) ; d0(#mu)"           , mu.z0,  mu.d0 ,  100., -300, 300, 100., -200, 200 , mu.weight);
	plotter.Plot2D(Form("%s_%s_%s_mu_eta_d0"   , sample_name.c_str(),event_selection.c_str(),muon_selection.c_str()), ";#eta(#mu);d0(#mu)"           , mu.eta, mu.d0 ,  50., -3, 3, 50., -200, 200 , mu.weight);
	plotter.Plot2D(Form("%s_%s_%s_mu_eta_z0"   , sample_name.c_str(),event_selection.c_str(),muon_selection.c_str()), ";#eta(#mu);z0(#mu)"           , mu.eta, mu.z0 ,  50., -3, 3, 50., -300, 300 , mu.weight);
	plotter.Plot2D(Form("%s_%s_%s_mu_eta_phi"  , sample_name.c_str(),event_selection.c_str(),muon_selection.c_str()), ";#eta(#mu);phi(#mu)"          , mu.eta, mu.phi,  50., -3, 3, 25., -3.5, 3.5 , mu.weight);
	plotter.Plot2D(Form("%s_%s_%s_mu_eta_pt"   , sample_name.c_str(),event_selection.c_str(),muon_selection.c_str()), ";#eta(#mu) ;p_{T}(#mu) [GeV]" , mu.eta, mu.pt,   50., -3, 3, 50.,  0 ,  500 , mu.weight);
	plotter.Plot2D(Form("%s_%s_%s_mu_eta_nPIX" , sample_name.c_str(),event_selection.c_str(),muon_selection.c_str()), ";#eta(#mu) ;nPIX"             , mu.eta, mu.nPIX, 50., -3, 3, 10., -0.5, 9.5 , mu.weight);
	plotter.Plot2D(Form("%s_%s_%s_mu_eta_nSCT" , sample_name.c_str(),event_selection.c_str(),muon_selection.c_str()), ";#eta(#mu) ;nSCT"             , mu.eta, mu.nSCT, 50., -3, 3, 20., -0.5, 19.5, mu.weight);
	plotter.Plot2D(Form("%s_%s_%s_mu_eta_nTRT" , sample_name.c_str(),event_selection.c_str(),muon_selection.c_str()), ";#eta(#mu) ;nTRT"             , mu.eta, mu.nTRT, 50., -3, 3, 50., -0.5, 49.5, mu.weight);
	plotter.Plot2D(Form("%s_%s_%s_mu_nPIX_nSCT", sample_name.c_str(),event_selection.c_str(),muon_selection.c_str()), ";nPIX ;nSCT"                  , mu.nPIX, mu.nSCT, 10., -0.5, 9.5, 20., -0.5, 19.5, mu.weight);
	plotter.Plot2D(Form("%s_%s_%s_mu_nPIX_nTRT", sample_name.c_str(),event_selection.c_str(),muon_selection.c_str()), ";nPIX ;nTRT"                  , mu.nPIX, mu.nTRT, 10., -0.5, 9.5, 50., -0.5, 49.5, mu.weight);
	plotter.Plot2D(Form("%s_%s_%s_mu_nSCT_nTRT", sample_name.c_str(),event_selection.c_str(),muon_selection.c_str()), ";nSCT ;nTRT"                  , mu.nSCT, mu.nTRT, 20., -0.5, 19.5, 50., -0.5, 49.5, mu.weight);

}
void muonPlots(std::string sample_name, std::vector<Muon> muons, std::string selection, float weight=1.)
{


	//
	// all muons
	//
	for (auto mu: muons)
	{
		if (fabs(mu.d0) < 300)	 muonPlots1D(sample_name, mu, selection, "all"  , weight);
	}
	//
	// Control region muons
	//
	int nMuPresel = 0;
	if (selection=="MuonZsel" || selection=="METZsel"){

		Muon mu; 
		if (muons.at(0).pt > muons.at(1).pt) mu = muons.at(0);
		else mu = muons.at(1);
		

		if (mu.passEta2p5 && mu.passPt25) 
		{
			nMuPresel++;
			
			//std::cout << "leading mu!" << std::endl;
			if (mu.passFullSel 		 && mu.passCosVetoTight)  muonPlots1D(sample_name, mu, selection, "FinalSel"  , weight);
			if (mu.passCosVetoTight  && mu.passFakeVetoTight) muonPlots1D(sample_name, mu, selection, "IsolCuts"  , weight);
			if (mu.passCosVetoTight  && mu.passFixedCutLoose) muonPlots1D(sample_name, mu, selection, "FakeCuts"  , weight);
			if (mu.passFixedCutLoose && mu.passFakeVetoTight) muonPlots1D(sample_name, mu, selection, "CosmicCuts", weight);
			
		}
	}
	else {
		// Muon Level Plots
		for (auto mu : muons){
	
			if (mu.passPreSel) 
			{
				nMuPresel++;
				if (mu.isLeading)
				{
					muonPlots1D(sample_name, mu, selection, "PreSel"  , weight);
					if (mu.passFullSel 		 && mu.passCosVetoTight && mu.TMmsonly && mu.passEta1p7 && mu.passPt62)  muonPlots1D(sample_name, mu, selection, "MSonlyFullSel"  , weight);
					
					if (mu.passFullSel 		 && mu.passCosVetoTight)  muonPlots1D(sample_name, mu, selection, "FinalSel"  , weight);
					if (mu.passCosVetoTight  && mu.passFakeVetoTight) muonPlots1D(sample_name, mu, selection, "IsolCuts"  , weight);
					if (mu.passCosVetoTight  && mu.passFixedCutLoose) muonPlots1D(sample_name, mu, selection, "FakeCuts"  , weight);
					if (mu.passFixedCutLoose && mu.passFakeVetoTight) muonPlots1D(sample_name, mu, selection, "CosmicCuts", weight);
	
				}
			}
			
		}		
	}
	


	plotter.Plot1D(Form("%s_%s_mu_nMuToT" ,    sample_name.c_str(),selection.c_str()),";N#mu;Events"  			  , muons.size() ,  7, -0.5, 6.5  , weight);
	plotter.Plot1D(Form("%s_%s_mu_nMuPre" ,    sample_name.c_str(),selection.c_str()),";N#mu Preselected;Events"  , nMuPresel    ,  7, -0.5, 6.5  , weight);

	return;
}


