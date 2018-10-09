
void makeCutflowHist(std::string s_sample, std::string s_region, unsigned long int flag, std::vector<unsigned int> cuts, float evt_wght)
{
	std::vector<unsigned int> incrementCuts;
	unsigned int n_cuts = cuts.size();
	int n_bins = n_cuts;

	bool isCR   = false;
	bool isMET  = false;
	bool isMuon = false;

	if ( s_region.find("CR"  ) != std::string::npos || s_region.find("VR"  ) != std::string::npos ) isCR   = true;
	if ( s_region.find("MET" ) != std::string::npos ) isMET  = true;
	if ( s_region.find("Muon") != std::string::npos ) isMuon = true;
	if ( isCR ) n_bins = n_bins+5;

	for (unsigned int i=0; i < n_cuts; i++)
	{
		incrementCuts.push_back(cuts.at(i));

		//std::cout << s_region << " " << i << " " <<  cuts.at(i) << std::endl;


		if ( passSpecificCuts(flag, incrementCuts) ) 
		{

   			plotter.Plot1D(Form("%s_%s_cutflow_wght" , s_sample.c_str(), s_region.c_str()),";cut;Events"     , i ,  n_bins,  -0.5, n_bins-0.5   , evt_wght);
   			plotter.Plot1D(Form("%s_%s_cutflow_raw"  , s_sample.c_str(), s_region.c_str()),";cut;Events Raw" , i ,  n_bins,  -0.5, n_bins-0.5   , 1.0);

   		}
	}

	// DV regions
	
	if ( isCR )
	{
		// Add up DV regions
		std::vector<unsigned int> CR_Cuts;
		if ( isMuon ) 
		{
			CR_Cuts = {	
			DVMu_MuonCuts::noDV, 
			DVMu_MuonCuts::passDV2track, 
			DVMu_MuonCuts::passDV3trackLM, 
			DVMu_MuonCuts::failDVmat3track,
			DVMu_MuonCuts::passDV3trackHM };
		}
		else if (isMET)
		{ 
			CR_Cuts = {	
			DVMu_METCuts::noDV, 
			DVMu_METCuts::passDV2track, 
			DVMu_METCuts::passDV3trackLM, 
			DVMu_METCuts::failDVmat3track,
			DVMu_METCuts::passDV3trackHM };
		}

		// Append DV region info to muon info
		for (unsigned int i=0; i<CR_Cuts.size(); i++)
		{
			// tmp vector 
			std::vector<unsigned int> tmp_cuts = cuts;
			tmp_cuts.push_back(CR_Cuts.at(i));

			//if (s_region=="MuonVR" ) std::cout << s_region << " " << n_cuts+i << " " << CR_Cuts.at(i) << std::endl;
			
			if ( passSpecificCuts(flag, tmp_cuts) )
			{	
				//if (s_region=="MuonVR" ) std::cout << " pass " << std::bitset<34>(flag) << std::endl;
				//if (s_region=="MuonVR") std::cout << s_region << " : CR cut " << i << " " <<  CR_Cuts.at(i)  << ": pass " << evt_wght << std::endl;
   				plotter.Plot1D(Form("%s_%s_cutflow_wght" , s_sample.c_str(), s_region.c_str()),";cut;Events"     , n_cuts+i ,  n_bins,  -0.5, n_bins-0.5   , evt_wght);
   				plotter.Plot1D(Form("%s_%s_cutflow_raw"  , s_sample.c_str(), s_region.c_str()),";cut;Events Raw" , n_cuts+i ,  n_bins,  -0.5, n_bins-0.5   , 1.0);				
			}

			tmp_cuts.clear();
		}// end loop

	}// end if CR 
	return;

}

void fillMuonCutflowHist(std::string s_sample, unsigned long int flag, float evt_wght){

	// For Cosmic Control Region 
	std::vector<unsigned int> cutsMuonCosmicCR = {DVMu_MuonCuts::AllNtup, DVMu_MuonCuts::hasPV, DVMu_MuonCuts::passPVz, DVMu_MuonCuts::passPVntrk,
					DVMu_MuonCuts::passMSonlyTrigger, DVMu_MuonCuts::passLHT, DVMu_MuonCuts::hasMuon, DVMu_MuonCuts::passMuonTM,
					DVMu_MuonCuts::passMuonPt, DVMu_MuonCuts::passMuonEta, DVMu_MuonCuts::passMuonID, DVMu_MuonCuts::passMuond0, DVMu_MuonCuts::passMuonz0,
					DVMu_MuonCuts::passMuonFakeVeto, DVMu_MuonCuts::passFixedCutLoose, DVMu_MuonCuts::failMuonCosVeto, // fail muon cos veto 
					};

	
   	// For Fake Control Region 
	std::vector<unsigned int> cutsMuonFakeCR = {DVMu_MuonCuts::AllNtup, DVMu_MuonCuts::hasPV, DVMu_MuonCuts::passPVz, DVMu_MuonCuts::passPVntrk,
					DVMu_MuonCuts::passMSonlyTrigger, DVMu_MuonCuts::passLHT, DVMu_MuonCuts::hasMuon, DVMu_MuonCuts::passMuonTM,
					DVMu_MuonCuts::passMuonPt, DVMu_MuonCuts::passMuonEta, DVMu_MuonCuts::passMuonID, DVMu_MuonCuts::passMuond0, DVMu_MuonCuts::passMuonz0,
					DVMu_MuonCuts::failMuonFakeVeto, DVMu_MuonCuts::passFixedCutLoose, DVMu_MuonCuts::passMuonCosVeto, // fail muon cos veto 
					};

   	// For Heavy Flavor Control Region 
	std::vector<unsigned int> cutsMuonHeavyCR = {DVMu_MuonCuts::AllNtup, DVMu_MuonCuts::hasPV, DVMu_MuonCuts::passPVz, DVMu_MuonCuts::passPVntrk,
					DVMu_MuonCuts::passMSonlyTrigger, DVMu_MuonCuts::passLHT, DVMu_MuonCuts::hasMuon, DVMu_MuonCuts::passMuonTM,
					DVMu_MuonCuts::passMuonPt, DVMu_MuonCuts::passMuonEta, DVMu_MuonCuts::passMuonID, DVMu_MuonCuts::passMuond0, DVMu_MuonCuts::passMuonz0,
					DVMu_MuonCuts::passMuonFakeVeto, DVMu_MuonCuts::failMuonHVVeto, DVMu_MuonCuts::passMuonCosVeto, // fail muon cos veto 
					};

	// For VR 
   	std::vector<unsigned int> cutsMuonVR = {DVMu_MuonCuts::AllNtup, DVMu_MuonCuts::hasPV, DVMu_MuonCuts::passPVz, DVMu_MuonCuts::passPVntrk,
					DVMu_MuonCuts::passMSonlyTrigger, DVMu_MuonCuts::passLHT, DVMu_MuonCuts::hasMuon, DVMu_MuonCuts::passMuonTM,
					DVMu_MuonCuts::passMuonPt, DVMu_MuonCuts::passMuonEta, DVMu_MuonCuts::passMuonID, DVMu_MuonCuts::passMuond0, DVMu_MuonCuts::passMuonz0,
					DVMu_MuonCuts::passMuonFakeVeto, DVMu_MuonCuts::passFixedCutLoose, DVMu_MuonCuts::passMuonCosVeto, // fail muon cos veto 
					};

   	// For Signal Region 
   	std::vector<unsigned int> cutsMuonSR = {DVMu_MuonCuts::AllNtup, DVMu_MuonCuts::hasPV, DVMu_MuonCuts::passPVz, DVMu_MuonCuts::passPVntrk,
					DVMu_MuonCuts::passMSonlyTrigger, DVMu_MuonCuts::passLHT, DVMu_MuonCuts::hasMuon, DVMu_MuonCuts::passMuonTM,
					DVMu_MuonCuts::passMuonPt, DVMu_MuonCuts::passMuonEta, DVMu_MuonCuts::passMuonID, DVMu_MuonCuts::passMuond0, DVMu_MuonCuts::passMuonz0,
					DVMu_MuonCuts::passMuonFakeVeto, DVMu_MuonCuts::passFixedCutLoose, DVMu_MuonCuts::passMuonCosVeto, 
					DVMu_MuonCuts::hasDV, DVMu_MuonCuts::passDVfid, DVMu_MuonCuts::passDVchi2, DVMu_MuonCuts::passDVdist, 
					DVMu_MuonCuts::passDVmat, DVMu_MuonCuts::passDVntrk, DVMu_MuonCuts::passDVmass, DVMu_MuonCuts::passDVmuon };

   	makeCutflowHist( s_sample, "MuonCosmicCR", flag, cutsMuonCosmicCR 	, evt_wght);
   	makeCutflowHist( s_sample, "MuonFakeCR"  , flag, cutsMuonFakeCR		, evt_wght);
   	makeCutflowHist( s_sample, "MuonHeavyCR" , flag, cutsMuonHeavyCR	, evt_wght);
   	makeCutflowHist( s_sample, "MuonVR" 	 , flag, cutsMuonVR 		, evt_wght);
   	makeCutflowHist( s_sample, "MuonSR"  	 , flag, cutsMuonSR 		, evt_wght);

	return; 
}
void fillMETCutflowHist(std::string s_sample, unsigned long int flag, float evt_wght){

	std::vector<unsigned int> cutsMETCosmicCR = {DVMu_METCuts::AllNtup, DVMu_METCuts::hasPV, DVMu_METCuts::passPVz, DVMu_METCuts::passPVntrk,
					DVMu_METCuts::passMETtrigger, DVMu_METCuts::passLHT,  
					DVMu_METCuts::hasMuon, DVMu_METCuts::passMuonPt, DVMu_METCuts::passMuonEta, DVMu_METCuts::passMuonID, DVMu_METCuts::passMuond0, DVMu_METCuts::passMuonz0, 
					DVMu_METCuts::passMuonFakeVeto, DVMu_METCuts::passFixedCutLoose, DVMu_METCuts::failMuonCosVeto, 
					// DV regions
					};

	std::vector<unsigned int> cutsMETFakeCR = {DVMu_METCuts::AllNtup, DVMu_METCuts::hasPV, DVMu_METCuts::passPVz, DVMu_METCuts::passPVntrk,
					DVMu_METCuts::passMETtrigger, DVMu_METCuts::passLHT,  
					DVMu_METCuts::hasMuon, DVMu_METCuts::passMuonPt, DVMu_METCuts::passMuonEta, DVMu_METCuts::passMuonID, DVMu_METCuts::passMuond0, DVMu_METCuts::passMuonz0, 
					DVMu_METCuts::failMuonFakeVeto, DVMu_METCuts::passFixedCutLoose, DVMu_METCuts::passMuonCosVeto, 
					// DV regions
					};

	std::vector<unsigned int> cutsMETHeavyCR = {DVMu_METCuts::AllNtup, DVMu_METCuts::hasPV, DVMu_METCuts::passPVz, DVMu_METCuts::passPVntrk,
					DVMu_METCuts::passMETtrigger, DVMu_METCuts::passLHT,  
					DVMu_METCuts::hasMuon, DVMu_METCuts::passMuonPt, DVMu_METCuts::passMuonEta, DVMu_METCuts::passMuonID, DVMu_METCuts::passMuond0, DVMu_METCuts::passMuonz0, 
					DVMu_METCuts::passMuonFakeVeto, DVMu_METCuts::failMuonHVVeto, DVMu_METCuts::passMuonCosVeto, 
					};

	std::vector<unsigned int> cutsMETVR = {DVMu_METCuts::AllNtup, DVMu_METCuts::hasPV, DVMu_METCuts::passPVz, DVMu_METCuts::passPVntrk,
					DVMu_METCuts::passMETtrigger, DVMu_METCuts::passLHT,  
					DVMu_METCuts::hasMuon, DVMu_METCuts::passMuonPt, DVMu_METCuts::passMuonEta, DVMu_METCuts::passMuonID, DVMu_METCuts::passMuond0, DVMu_METCuts::passMuonz0, 
					DVMu_METCuts::passMuonFakeVeto, DVMu_METCuts::passFixedCutLoose, DVMu_METCuts::passMuonCosVeto, 
					};


	std::vector<unsigned int> cutsMETSR = {DVMu_METCuts::AllNtup, DVMu_METCuts::hasPV, DVMu_METCuts::passPVz, DVMu_METCuts::passPVntrk,
					DVMu_METCuts::passMETtrigger, DVMu_METCuts::passLHT,  
					DVMu_METCuts::hasMuon, DVMu_METCuts::passMuonPt, DVMu_METCuts::passMuonEta, DVMu_METCuts::passMuonID, DVMu_METCuts::passMuond0, DVMu_METCuts::passMuonz0, 
					DVMu_METCuts::passMuonFakeVeto, DVMu_METCuts::passFixedCutLoose, DVMu_METCuts::passMuonCosVeto, 
					DVMu_METCuts::hasDV, DVMu_METCuts::passDVfid, DVMu_METCuts::passDVchi2, DVMu_METCuts::passDVdist, 
					DVMu_METCuts::passDVmat, DVMu_METCuts::passDVntrk, DVMu_METCuts::passDVmass, DVMu_METCuts::passDVmuon };

   	makeCutflowHist( s_sample, "METCosmicCR", flag, cutsMETCosmicCR , evt_wght);
   	makeCutflowHist( s_sample, "METFakeCR"  , flag, cutsMETFakeCR	, evt_wght);
   	makeCutflowHist( s_sample, "METHeavyCR" , flag, cutsMETHeavyCR	, evt_wght);
   	makeCutflowHist( s_sample, "METVR"		, flag, cutsMETVR 		, evt_wght);
   	makeCutflowHist( s_sample, "METSR"		, flag, cutsMETSR 		, evt_wght);

	return; 
}

void doHistos::makeCutflow(std::string s_sample, std::vector<Muon> mus, std::vector<DV> dvs, float evt_wght){
	// Makes a cutflow!

	//std::cout << s_sample << " event " << eventNumber << std::endl;


	// Control region cuts to take care of...
	//failMuonFakeVeto, 
	//failMuonHVVeto,
	//failMuonCosVeto, // 
	//noDV, 			 // CR for measuring templates
	//failDVmat, 		 // 
	//failDVmat3track, // VRMAT - if you fail
	//passDV2track,    // VR2LM
	//passDV3trackLM,  // VR3LM
	//passDV3trackHM,  // SR prediction!

	// Initialize the event flags to zero - have one for MET SR and another for MU SR
	unsigned long int eventMETFlag  = 0; 
	unsigned long int eventMuonFlag = 0; 

	//std::cout << evt_wght << std::endl;

	updateFlag(eventMETFlag   , DVMu_METCuts::AllNtup);
	updateFlag(eventMuonFlag  , DVMu_MuonCuts::AllNtup);
	/*
		PRIMARY VERTEX
	*/
	if (  NPV > 0 ) 
	{ 
		updateFlag(eventMETFlag   , DVMu_METCuts::hasPV);
		updateFlag(eventMuonFlag  , DVMu_MuonCuts::hasPV);	
	}
	if (fabs(PV_z) < 200 ) 
	{ 
		updateFlag(eventMETFlag, DVMu_METCuts::passPVz);		
		updateFlag(eventMuonFlag, DVMu_MuonCuts::passPVz); 		
	}
	if (PV_nTracks >= 2  ) 
	{
		updateFlag(eventMETFlag, DVMu_METCuts::passPVntrk);	
		updateFlag(eventMuonFlag, DVMu_MuonCuts::passPVntrk); 	
	}

	/*
		MET SR Trigger stuff first?
	*/
	//float new_met = get_MET_with_Muons( mus, MET, MET_phi);
	
	if ( MHT_HLT>120    ) { updateFlag(eventMETFlag, DVMu_METCuts::passMETtrigger);  }
	if ( MET_LHT>180.   ) { updateFlag(eventMETFlag, DVMu_METCuts::passLHT); 		 }

	/*
		Then Muon SR Trigger stuff
	*/
	if ( passHLTmsonly  ) { updateFlag(eventMuonFlag, DVMu_MuonCuts::passMSonlyTrigger);  }
	if ( MET_LHT<180.   ) { updateFlag(eventMuonFlag, DVMu_MuonCuts::passLHT);			  }

	/*
		Muons
	*/
	// apply cosmic veto at the event level? 
	bool fail_cos = false;
	float dR_min = 5.0;
	for ( auto mu : mus ){
		//if (mu.passPreSel ) std::cout << "pre  dR " << mu.dRcos  << " : pass " << mu.passCosVetoTight << std::endl;
		//if (mu.passFullSel) std::cout << "full dR " << mu.dRcos  << " : pass " << mu.passCosVetoTight << std::endl;
		//if (mu.isLeading  ) std::cout << "lead dR " << mu.dRcos  << " : pass " << mu.passCosVetoTight << std::endl;
		if (mu.passFullSel){
		  if ( mu.dRcos < dR_min ) dR_min = mu.dRcos;
		  if ( mu.dRcos < 0.2 ) fail_cos = true;
		  if (!mu.passCosVetoTight) fail_cos = true;
		}
		// look for any preselected muon, passing fake veto and heavy flavor veto with dR cos < 0.2 - if you have one, you fail the event
	}

	for ( auto mu : mus ){ // require muon cuts to be consecutive 
	

		// FOR Muon SR only 
		//if (mu.passTM && mu.passPt62 && mu.passEta1p7) updateFlag(eventMuonFlag, DVMu_MuonCuts::passMuonTM);

		// FOR MET SRs 
								updateFlag(eventMETFlag, DVMu_METCuts::hasMuon);			
		if (mu.passPt25) { 		updateFlag(eventMETFlag, DVMu_METCuts::passMuonPt);			
		  if (mu.passEta2p5){	updateFlag(eventMETFlag, DVMu_METCuts::passMuonEta);		
		  	if (mu.passID){ 	updateFlag(eventMETFlag, DVMu_METCuts::passMuonID);			
			  if (mu.passD0){ 	updateFlag(eventMETFlag, DVMu_METCuts::passMuond0);			
			    				updateFlag(eventMETFlag, DVMu_METCuts::passMuonz0);		
			    //if (mu.passZ0){ 	updateFlag(eventMETFlag, DVMu_METCuts::passMuonz0);		
		  	      if (mu.isLeading){
		  	      	if (mu.passFakeVetoTight ) 	updateFlag(eventMETFlag, DVMu_METCuts::passMuonFakeVeto);	
		  	      	else 						updateFlag(eventMETFlag, DVMu_METCuts::failMuonFakeVeto);
		  	        if (mu.passFixedCutLoose ) 	updateFlag(eventMETFlag, DVMu_METCuts::passFixedCutLoose);		
		  	        else 						updateFlag(eventMETFlag, DVMu_METCuts::failMuonHVVeto);
		  	        if (mu.passCosVetoTight  )	updateFlag(eventMETFlag, DVMu_METCuts::passMuonCosVeto);
					else 						updateFlag(eventMETFlag, DVMu_METCuts::failMuonCosVeto);
		  	      }// end is leading
		  	    //}
		  	  }
		  	}
		  }
		}
		// FOR MET and MUON SRs 
									updateFlag(eventMuonFlag, DVMu_MuonCuts::hasMuon);
		if (mu.passTM){				updateFlag(eventMuonFlag, DVMu_MuonCuts::passMuonTM);
		  if (mu.passPt62) { 		updateFlag(eventMuonFlag, DVMu_MuonCuts::passMuonPt);
		  	if (mu.passEta1p7){		updateFlag(eventMuonFlag, DVMu_MuonCuts::passMuonEta);
		      if (mu.passID){ 		updateFlag(eventMuonFlag, DVMu_MuonCuts::passMuonID);
		  	    if (mu.passD0){ 	updateFlag(eventMuonFlag, DVMu_MuonCuts::passMuond0);
		  	      				 	updateFlag(eventMuonFlag, DVMu_MuonCuts::passMuonz0); // drop cut for now
		  	      //if (mu.passZ0){ 	updateFlag(eventMuonFlag, DVMu_MuonCuts::passMuonz0);
		    	    if (mu.isLeading){
		  	      		if (mu.passFakeVetoTight ) 	updateFlag(eventMuonFlag, DVMu_MuonCuts::passMuonFakeVeto);	
		  	      		else 						updateFlag(eventMuonFlag, DVMu_MuonCuts::failMuonFakeVeto);
		  	        	if (mu.passFixedCutLoose ) 	updateFlag(eventMuonFlag, DVMu_MuonCuts::passFixedCutLoose);		
		  	        	else 						updateFlag(eventMuonFlag, DVMu_MuonCuts::failMuonHVVeto);
						if (mu.passCosVetoTight  )	updateFlag(eventMuonFlag, DVMu_MuonCuts::passMuonCosVeto);
						else 						updateFlag(eventMuonFlag, DVMu_MuonCuts::failMuonCosVeto);

		  	        	if ( mu.passFakeVetoTight && mu.passFixedCutLoose && passHLTmsonly && MET_LHT < 180 && s_sample=="data"){

		  	        		plotter.Plot1D("data_k_Muons_dRmin"		  ,";dRmin;muons"	, dR_min	, 100, 0, 1.0);

		  	        		if (!fail_cos){
		  	        				plotter.Plot1D("data_k_signalMuons_eta"		  ,";#eta;muons"			, mu.eta			, 100, -2.5, 2.5);
		    	    	  			plotter.Plot1D("data_k_signalMuons_phi"		  ,";#phi;muons"			, mu.phi			, 100, -3.5, 3.5);
		    	    	  			plotter.Plot1D("data_k_signalMuons_pt"		  ,";pt;muons"				, mu.pt 			, 100,    0, 1000);
		    	    	  			plotter.Plot1D("data_k_signalMuons_d0"		  ,";d0;muons"				, mu.d0 			, 100, -300, 300);
		    	    	  			plotter.Plot1D("data_k_signalMuons_z0"		  ,";z0;muons"				, mu.z0 			, 100, -300, 300);
		    	    	  			plotter.Plot1D("data_k_signalMuons_z0corr"	  ,";z0corr;muons"			, mu.z0corr 		, 100, -300, 300);
		    	    	  			plotter.Plot1D("data_k_signalMuons_chi2"	  ,";chi2;muons"			, mu.CBchi2			, 100, 0, 10);
		    	    	  			plotter.Plot1D("data_k_signalMuons_npres"	  ,";npres;muons"			, mu.nPres 			, 6, -0.5, 5.5);
		    	    	  			plotter.Plot1D("data_k_signalMuons_ptvar"	  ,";ptvarcone30;muons"		, mu.ptvarcone30	, 100, 0, 0.3);
		    	    	  			plotter.Plot1D("data_k_signalMuons_topoet"	  ,";topoetcone20;muons"	, mu.topoetcone20	, 100, 0, 0.3);
		    	    	  			plotter.Plot1D("data_k_signalMuons_isTM" 	  ,";isTM;muons"			, mu.passTM    		, 2, -0.5, 1.5);
		    	    	  			plotter.Plot1D("data_k_signalMuons_isLeading" ,";islead;muons"			, mu.isLeading    	, 2, -0.5, 1.5);
		    	    	  			plotter.Plot1D("data_k_signalMuons_dRcos"     ,";dRcos;muons"			, mu.dRcos      	, 100, 0, 5);
		    	    	  			plotter.Plot1D("data_k_signalMuons_dRmin"     ,";dRmin;muons"			, dR_min         	, 100, 0, 5);
  	  	
  	  		    		      		plotter.Plot2D("data_k_signalMuons_eta_phi" ,";#eta;z0;muons", mu.eta  , mu.phi , 100, -1.1, 1.1, 100, -3.5, 3.5);
		  	        		}
		  	        		else {
	
		  	    					plotter.Plot1D("data_k_cosmicMuons_eta"			,";eta;muons"			, mu.eta			, 100, -2.5, 2.5);
		    	    	  			plotter.Plot1D("data_k_cosmicMuons_phi"			,";phi;muons"			, mu.phi			, 100, -3.5, 3.5);
		    	    	  			plotter.Plot1D("data_k_cosmicMuons_pt"			,";pt;muons"			, mu.pt 			, 100,    0, 1000);
		    	    	  			plotter.Plot1D("data_k_cosmicMuons_d0"			,";d0;muons"			, mu.d0 			, 100, -300, 300);
		    	    	  			plotter.Plot1D("data_k_cosmicMuons_z0"			,";z0;muons"			, mu.z0 			, 100, -300, 300);
		    	    	  			plotter.Plot1D("data_k_cosmicMuons_z0corr"		,";z0corr;muons"		, mu.z0corr 		, 100, -300, 300);
		    	    	  			plotter.Plot1D("data_k_cosmicMuons_chi2"		,";chi2;muons"			, mu.CBchi2			, 100, 0, 10);
		    	    	  			plotter.Plot1D("data_k_cosmicMuons_npres"		,";npres;muons"			, mu.nPres 			, 6, -0.5, 5.5);
		    	    	  			plotter.Plot1D("data_k_cosmicMuons_ptvar"		,";ptvarcone30;muons"	, mu.ptvarcone30	, 100, 0, 0.3);
		    	    	  			plotter.Plot1D("data_k_cosmicMuons_topoet"		,";topoetcone20;muons"	, mu.topoetcone20	, 100, 0, 0.3);
		    	    	  			plotter.Plot1D("data_k_cosmicMuons_isTM" 		,";isTM;muons"			, mu.passTM    		, 2, -0.5, 1.5);
		    	    	  			plotter.Plot1D("data_k_cosmicMuons_isLeading" 	,";islead;muons"		, mu.isLeading    	, 2, -0.5, 1.5);
		    	    	  			plotter.Plot1D("data_k_cosmicMuons_dRcos"     	,";dRcos;muons"			, mu.dRcos      	, 100, 0, 5);
		    	    	  			plotter.Plot1D("data_k_cosmicMuons_dRmin"     	,";dRmin;muons"			, dR_min         	, 100, 0, 5);
	
		    	    	  			plotter.Plot2D("data_k_cosmicMuons_eta_phi" ,";#eta;z0;muons", mu.eta  , mu.phi , 100, -1.1, 1.1, 100, -3.5, 3.5);
	
		  	        		}

		  	        	} // cosmic veto studies just to make sure 
		  	        }// end is leading
		  	      }
		    	}
		      }
		    //}
		  }
		}
	}



	//if (!fail_cos){
	//	updateFlag(eventMETFlag , DVMu_METCuts::passMuonCosVeto);
	//	updateFlag(eventMuonFlag, DVMu_MuonCuts::passMuonCosVeto);
	//}
	//else {
	//	updateFlag(eventMETFlag , DVMu_METCuts::failMuonCosVeto);
	//	updateFlag(eventMuonFlag, DVMu_MuonCuts::failMuonCosVeto);
	//}
	/*
		DVs
	*/

	// For control region definitions
	int DV_region = 0;
    // 0 -- if No DVs in the event at all 
    // 1 -- if there is any DV with at least three tracks in material veto 
    // 2 -- if there is any DV at all
    // 3 -- if there is any DV with at least three tracks and mass < 10
    // 4 -- if there is any DV with at least three tracks and mass > 10

	for ( auto dv : dvs ){ 
														updateFlag(eventMETFlag, DVMu_METCuts::hasDV);			updateFlag(eventMuonFlag, DVMu_MuonCuts::hasDV);
		if (dv.passFiducialCuts) { 						updateFlag(eventMETFlag, DVMu_METCuts::passDVfid);		updateFlag(eventMuonFlag, DVMu_MuonCuts::passDVfid);
			if (dv.passChisqCut){						updateFlag(eventMETFlag, DVMu_METCuts::passDVchi2);		updateFlag(eventMuonFlag, DVMu_MuonCuts::passDVchi2);
				if (dv.passDistCut){ 					updateFlag(eventMETFlag, DVMu_METCuts::passDVdist);		updateFlag(eventMuonFlag, DVMu_MuonCuts::passDVdist);
					if (dv.passNtrackCut3 && !dv.passMaterialVeto) {
						if (DV_region < 1) DV_region=1;
					}
					if (dv.passMaterialVeto){			updateFlag(eventMETFlag, DVMu_METCuts::passDVmat);		updateFlag(eventMuonFlag, DVMu_MuonCuts::passDVmat);
						if (DV_region < 2) DV_region=2;
						if (dv.passNtrackCut3){			updateFlag(eventMETFlag, DVMu_METCuts::passDVntrk);		updateFlag(eventMuonFlag, DVMu_MuonCuts::passDVntrk);
							if (DV_region < 3) DV_region=3;
							if (dv.passMassCut10){		updateFlag(eventMETFlag, DVMu_METCuts::passDVmass);		updateFlag(eventMuonFlag, DVMu_MuonCuts::passDVmass);			
								if (DV_region < 4) DV_region=4;
								if (dv.passMuonLink){
									updateFlag(eventMETFlag, DVMu_METCuts::passDVmuon);		updateFlag(eventMuonFlag, DVMu_MuonCuts::passDVmuon);
								}	
							}// mass	  
						}// ntrack 3
					}// mat veto
				}// dist
			}//chi2
		}//fid
	}// dv
	if      (DV_region==0) { updateFlag(eventMETFlag, DVMu_METCuts::noDV);			  updateFlag(eventMuonFlag, DVMu_MuonCuts::noDV); 			}
	else if (DV_region==1) { updateFlag(eventMETFlag, DVMu_METCuts::failDVmat3track); updateFlag(eventMuonFlag, DVMu_MuonCuts::failDVmat3track); }
	else if (DV_region==2) { updateFlag(eventMETFlag, DVMu_METCuts::passDV2track);	  updateFlag(eventMuonFlag, DVMu_MuonCuts::passDV2track); 	}
	else if (DV_region==3) { updateFlag(eventMETFlag, DVMu_METCuts::passDV3trackLM);  updateFlag(eventMuonFlag, DVMu_MuonCuts::passDV3trackLM);	}
	else if (DV_region==4) { updateFlag(eventMETFlag, DVMu_METCuts::passDV3trackHM);  updateFlag(eventMuonFlag, DVMu_MuonCuts::passDV3trackHM); }

	fillMETCutflowHist (s_sample, eventMETFlag , evt_wght);
	fillMuonCutflowHist(s_sample, eventMuonFlag, evt_wght);

	// TO DO 
	//fillMETFake		(s_sample, eventMETFlag, evt_wght);
	//fillMETCosmic	(s_sample, eventMETFlag, evt_wght);	
	//fillMuonFake	(s_sample, eventMuonFlag, evt_wght);	
	//fillMuonCosmic	(s_sample, eventMuonFlag, evt_wght);	
	//std::cout << "eventMETFlag " << std::bitset<20>(eventMETFlag).to_string() << std::endl;




	return; 
}
