#define DVPlots_cxx

void DVPlots(std::string sample_name, std::vector<DV> dvs, std::string selection, float weight=1.)
{
	plotter.Plot1D(Form("%s_%s_dv_nDV" ,    sample_name.c_str(),selection.c_str()),";N_{DV};Events"  , dvs.size() ,  7, -0.5, 6.5  , weight);

	for (auto dv: dvs){    


  		if (dv.passFiducialCuts && dv.passChisqCut && dv.passDistCut && dv.passMaterialVeto ) {

  			// N - Ntrack plots
  													     plotter.Plot1D(Form("%s_PassPre_dv_nTracks" 	      ,  sample_name.c_str()),";DV nTracks;DVs"  		, dv.nTracks,   25.,  -0.5, 24.5  , dv.weight);
  													     plotter.Plot1D(Form("%s_PassPre_dv_nLRT" 	      	  ,  sample_name.c_str()),";DV nLRT;DVs"  			, dv.nLRT   ,   25.,  -0.5, 24.5 , dv.weight);
  			if ( dv.passMassCut10   )					 plotter.Plot1D(Form("%s_PassPreMass_dv_nTracks" 	  ,  sample_name.c_str()),";DV nTracks;DVs"  		, dv.nTracks,   25.,  -0.5, 24.5 , dv.weight);
  			if ( dv.passMassCut10 && dv. passNtrackCut3 ) plotter.Plot1D(Form("%s_PassPreMassNtrk_dv_nTracks" ,  sample_name.c_str()),";DV nTracks;DVs"  		, dv.nTracks,   25.,  -0.5, 24.5 , dv.weight);

  			// N - Mass plots
  													  plotter.Plot1D(Form("%s_PassPre_dv_m" 	    ,  sample_name.c_str()),";DV m [GeV];DVs"  		, dv.m,   150.,  0, 1500  , dv.weight);
  													  plotter.Plot1D(Form("%s_PassPre_dv_mzoom" 	,  sample_name.c_str()),";DV m [GeV];DVs"  		, dv.m,   100.,  0, 100  , dv.weight);
  			if ( dv.passNtrackCut3 )				  plotter.Plot1D(Form("%s_PassPreNtrk_dv_m" 	,  sample_name.c_str()),";DV m [GeV];DVs"  		, dv.m,   100.,  0, 100  , dv.weight);
  			if (dv.passNtrackCut3 && dv.passMassCut10 ){ plotter.Plot1D(Form("%s_PassPreNtrkMass_dv_m" ,  sample_name.c_str()),";DV m [GeV];DVs"  		, dv.m,   100.,  0, 100  , dv.weight);
  			  										  plotter.Plot1D(Form("%s_PassPreNtrkMass_dv_rxy"  	,  sample_name.c_str()),";DV r_{xy}[mm];DVs"  	, dv.rxy,   100.,   0, 300  , dv.weight);
  			  										  plotter.Plot1D(Form("%s_PassPreNtrkMass_dv_z"  	,  sample_name.c_str()),";DV z [mm];DVs"  		, dv.z  ,   100.,-300, 300  , dv.weight);
  			  										  plotter.Plot1D(Form("%s_PassPreNtrkMass_dv_r"  	,  sample_name.c_str()),";DV r [mm];DVs"  		, dv.r  ,   100.,   0, 500  , dv.weight);
  			  										}
  		}	
		


		//if (selection == "DVall"              ) plotter.Plot1D(Form("%s_dv_cutflow" ,  sample_name.c_str()),";Cut" , 0 ,  10., -0.5, 9.5  , dv.weight);
		//if (selection == "DVpassFiducialCuts" ) plotter.Plot1D(Form("%s_dv_cutflow" ,  sample_name.c_str()),";Cut" , 1 ,  10., -0.5, 9.5  , dv.weight);
		//if (selection == "DVpassChisqCut"     ) plotter.Plot1D(Form("%s_dv_cutflow" ,  sample_name.c_str()),";Cut" , 2 ,  10., -0.5, 9.5  , dv.weight);
		//if (selection == "DVpassDistCut"      ) plotter.Plot1D(Form("%s_dv_cutflow" ,  sample_name.c_str()),";Cut" , 3 ,  10., -0.5, 9.5  , dv.weight);
		//if (selection == "DVpassMaterialVeto" ) plotter.Plot1D(Form("%s_dv_cutflow" ,  sample_name.c_str()),";Cut" , 4 ,  10., -0.5, 9.5  , dv.weight);
		//if (selection == "DVpassMassCut"      ) plotter.Plot1D(Form("%s_dv_cutflow" ,  sample_name.c_str()),";Cut" , 5 ,  10., -0.5, 9.5  , dv.weight);
		//if (selection == "DVpassNtrkCut"      ) plotter.Plot1D(Form("%s_dv_cutflow" ,  sample_name.c_str()),";Cut" , 6 ,  10., -0.5, 9.5  , dv.weight);
		//if (selection == "DVpassMuonLink"     ) plotter.Plot1D(Form("%s_dv_cutflow" ,  sample_name.c_str()),";Cut" , 7 ,  10., -0.5, 9.5  , dv.weight);
		//
		//if (selection == "DVall"              ) plotter.Plot1D(Form("%s_dv_cutflow_raw" ,  sample_name.c_str()),";Cut" , 0 ,  10., -0.5, 9.5 );
		//if (selection == "DVpassFiducialCuts" ) plotter.Plot1D(Form("%s_dv_cutflow_raw" ,  sample_name.c_str()),";Cut" , 1 ,  10., -0.5, 9.5 );
		//if (selection == "DVpassChisqCut"     ) plotter.Plot1D(Form("%s_dv_cutflow_raw" ,  sample_name.c_str()),";Cut" , 2 ,  10., -0.5, 9.5 );
		//if (selection == "DVpassDistCut"      ) plotter.Plot1D(Form("%s_dv_cutflow_raw" ,  sample_name.c_str()),";Cut" , 3 ,  10., -0.5, 9.5 );
		//if (selection == "DVpassMaterialVeto" ) plotter.Plot1D(Form("%s_dv_cutflow_raw" ,  sample_name.c_str()),";Cut" , 4 ,  10., -0.5, 9.5 );
		//if (selection == "DVpassMassCut"      ) plotter.Plot1D(Form("%s_dv_cutflow_raw" ,  sample_name.c_str()),";Cut" , 5 ,  10., -0.5, 9.5 );
		//if (selection == "DVpassNtrkCut"      ) plotter.Plot1D(Form("%s_dv_cutflow_raw" ,  sample_name.c_str()),";Cut" , 6 ,  10., -0.5, 9.5 );
		//if (selection == "DVpassMuonLink"     ) plotter.Plot1D(Form("%s_dv_cutflow_raw" ,  sample_name.c_str()),";Cut" , 7 ,  10., -0.5, 9.5 );
		
		if (dv.passFiducialCuts){
			plotter.Plot1D(Form("%s_%s_dv_m"  		,  sample_name.c_str(),selection.c_str()),";DV m [GeV];DVs"  		, dv.m ,  		200.,  0, 1500, dv.weight);
			plotter.Plot1D(Form("%s_%s_dv_r"      	,  sample_name.c_str(),selection.c_str()),";DV r [mm];DVs"          , dv.r ,        200.,  0, 500, dv.weight);
			plotter.Plot1D(Form("%s_%s_dv_rxy"		,  sample_name.c_str(),selection.c_str()),";DV r_{xy} [mm];DVs"  	, dv.rxy , 		200.,  0, 300 , dv.weight);
			plotter.Plot1D(Form("%s_%s_dv_z"  		,  sample_name.c_str(),selection.c_str()),";DV z [mm];DVs"  		, dv.z ,   		200.,-300,300 , dv.weight);
			plotter.Plot1D(Form("%s_%s_dv_chi2"	   	,  sample_name.c_str(),selection.c_str()),";DV #chi^{2}/N_{DoF};DVs", dv.chi2,  	200.,  0, 10.0, dv.weight);
			plotter.Plot1D(Form("%s_%s_dv_mzoom"   	,  sample_name.c_str(),selection.c_str()),";DV m [GeV];DVs"         , dv.m ,        200.,  0,  50 , dv.weight);
			plotter.Plot1D(Form("%s_%s_dv_lastCut" 	,  sample_name.c_str(),selection.c_str()),";DV Last CUt;DVs"        , dv.lastCut,   10.,-1.5, 8.5, dv.weight);
			plotter.Plot1D(Form("%s_%s_dv_nLRT" 	,  sample_name.c_str(),selection.c_str()),";DV nLRT;DVs"  			, dv.nLRT ,  	25.,  0.5, 25.5  , dv.weight);
			plotter.Plot1D(Form("%s_%s_dv_nTracks" 	,  sample_name.c_str(),selection.c_str()),";DV nTracks;DVs"  		, dv.nTracks,   25.,  0.5, 25.5  , dv.weight);
			plotter.Plot1D(Form("%s_%s_dv_phi" 		,  sample_name.c_str(),selection.c_str()),";DV phi;DVs"  			, dv.phi,   	200.,-3.5, 3.5 , dv.weight);

			if (dv.passNtrackCut3){
				plotter.Plot1D(Form("%s_%s_dv_3trk_m"      ,  sample_name.c_str(),selection.c_str()),";DV m [GeV];DVs"          , dv.m ,        200.,  0, 1500 , dv.weight);
				plotter.Plot1D(Form("%s_%s_dv_3trk_mzoom"  ,  sample_name.c_str(),selection.c_str()),";DV m [GeV];DVs"          , dv.m ,        200.,  0,  50 , dv.weight);
				plotter.Plot1D(Form("%s_%s_dv_3trk_chi2"   ,  sample_name.c_str(),selection.c_str()),";DV #chi^{2}/N_{DoF};DVs" , dv.chi2,  	200.,  0, 10.0, dv.weight);
				plotter.Plot1D(Form("%s_%s_dv_3trk_rxy"	   ,  sample_name.c_str(),selection.c_str()),";DV r_{xy} [mm];DVs"  	, dv.rxy , 		200.,  0, 300 , dv.weight);
				plotter.Plot1D(Form("%s_%s_dv_3trk_z"  	   ,  sample_name.c_str(),selection.c_str()),";DV z [mm];DVs"  			, dv.z ,   		200.,-300,300 , dv.weight);
				plotter.Plot1D(Form("%s_%s_dv_3trk_phi"    ,  sample_name.c_str(),selection.c_str()),";DV phi;DVs"  			, dv.phi ,   	200.,-3.5, 3.5 , dv.weight);
				plotter.Plot1D(Form("%s_%s_dv_3trk_nLRT"   ,  sample_name.c_str(),selection.c_str()),";DV nLRT;DVs"  			, dv.nLRT ,  	30.,  0.5, 30.5  , dv.weight);

			}

		}
		if (dv.passFiducialCuts && 
			dv.passChisqCut && 
			dv.passDistCut && 
			dv.passMaterialVeto ){
			plotter.Plot1D(Form("%s_%s_Pre_dv_m"  		,  sample_name.c_str(),selection.c_str()),";DV m [GeV];DVs"  		, dv.m ,  		200.,  0, 1000, dv.weight);
			plotter.Plot1D(Form("%s_%s_Pre_dv_r"      	,  sample_name.c_str(),selection.c_str()),";DV r [mm];DVs"          , dv.r ,        200.,  0, 500, dv.weight);
			plotter.Plot1D(Form("%s_%s_Pre_dv_rxy"		,  sample_name.c_str(),selection.c_str()),";DV r_{xy} [mm];DVs"  	, dv.rxy , 		200.,  0, 300 , dv.weight);
			plotter.Plot1D(Form("%s_%s_Pre_dv_z"  		,  sample_name.c_str(),selection.c_str()),";DV z [mm];DVs"  		, dv.z ,   		200.,-300,300 , dv.weight);
			plotter.Plot1D(Form("%s_%s_Pre_dv_chi2"	   	,  sample_name.c_str(),selection.c_str()),";DV #chi^{2}/N_{DoF};DVs", dv.chi2,  	200.,  0, 10.0, dv.weight);
			plotter.Plot1D(Form("%s_%s_Pre_dv_mzoom"   	,  sample_name.c_str(),selection.c_str()),";DV m [GeV];DVs"         , dv.m ,        200.,  0,  50 , dv.weight);
			plotter.Plot1D(Form("%s_%s_Pre_dv_lastCut" 	,  sample_name.c_str(),selection.c_str()),";DV Last CUt;DVs"        , dv.lastCut,   10.,-1.5, 8.5, dv.weight);
			plotter.Plot1D(Form("%s_%s_Pre_dv_nLRT" 	,  sample_name.c_str(),selection.c_str()),";DV nLRT;DVs"  			, dv.nLRT ,  	50.,  0.5, 50.5  , dv.weight);
			plotter.Plot1D(Form("%s_%s_Pre_dv_nTracks" 	,  sample_name.c_str(),selection.c_str()),";DV nTracks;DVs"  		, dv.nTracks,   50.,  0.5, 50.5  , dv.weight);
			plotter.Plot1D(Form("%s_%s_Pre_dv_phi" 		,  sample_name.c_str(),selection.c_str()),";DV phi;DVs"  			, dv.phi,   	200.,-3.5, 3.5 , dv.weight);

			if (dv.passNtrackCut3){
				plotter.Plot1D(Form("%s_%s_Pre_dv_3trk_mzoom"  ,  sample_name.c_str(),selection.c_str()),";DV m [GeV];DVs"          , dv.m ,        200.,  0,  50 , dv.weight);
				plotter.Plot1D(Form("%s_%s_Pre_dv_3trk_chi2"   ,  sample_name.c_str(),selection.c_str()),";DV #chi^{2}/N_{DoF};DVs" , dv.chi2,  	200.,  0, 10.0, dv.weight);
				plotter.Plot1D(Form("%s_%s_Pre_dv_3trk_rxy"	   ,  sample_name.c_str(),selection.c_str()),";DV r_{xy} [mm];DVs"  	, dv.rxy , 		200.,  0, 300 , dv.weight);
				plotter.Plot1D(Form("%s_%s_Pre_dv_3trk_z"  	   ,  sample_name.c_str(),selection.c_str()),";DV z [mm];DVs"  			, dv.z ,   		200.,-300,300 , dv.weight);
				plotter.Plot1D(Form("%s_%s_Pre_dv_3trk_phi"    ,  sample_name.c_str(),selection.c_str()),";DV phi;DVs"  			, dv.phi ,   	200.,-3.5, 3.5 , dv.weight);
				plotter.Plot1D(Form("%s_%s_Pre_dv_3trk_nLRT"   ,  sample_name.c_str(),selection.c_str()),";DV nLRT;DVs"  			, dv.nLRT ,  	50.,  0.5, 50.5  , dv.weight);
			}
		}


	}


}
void DVPlots2D(std::string sample_name, std::vector<DV> dvs, std::string selection, float weight=1.)
{

	for (auto dv : dvs ){

		if (dv.passFiducialCuts && 
			dv.passChisqCut && 
			dv.passDistCut && 
			dv.passMaterialVeto ){ plotter.Plot2D(Form("%s_Pre_dv_nTracks_m"	  , sample_name.c_str() 				 ), ";DV nTracks; DV m [GeV]"             , dv.nTracks, dv.m    , 30,    0, 30., 100,    0, 500, dv.weight);
								   plotter.Plot2D(Form("%s_Pre_dv_nTracks_mzoom"  , sample_name.c_str() 				 ), ";DV nTracks; DV m [GeV]"             , dv.nTracks, dv.m    , 4,  1.5,  5.5, 10,     0, 10 , dv.weight);
								   plotter.Plot2D(Form("%s_Pre_dv_nTracks_mextrp" , sample_name.c_str() 				 ), ";DV nTracks; DV m [GeV]"             , dv.nTracks, dv.m    , 30, 1.5, 31.5,200,     0, 200 , dv.weight);
								  }
								  plotter.Plot2D(Form("%s_%s_dv_nTracks_m"  	  , sample_name.c_str(),selection.c_str()), ";DV nTracks; DV m [GeV]"             , dv.nTracks, dv.m    , 30,    0, 30., 100,    0, 500, dv.weight);
								  plotter.Plot2D(Form("%s_%s_dv_nTracks_mzoom"    , sample_name.c_str(),selection.c_str()), ";DV nTracks; DV m [GeV]"             , dv.nTracks, dv.m    , 4,  1.5,  5.5, 10,     0, 10 , dv.weight);
								  plotter.Plot2D(Form("%s_%s_dv_nTracks_mextrp"   , sample_name.c_str(),selection.c_str()), ";DV nTracks; DV m [GeV]"             , dv.nTracks, dv.m    ,30, 1.5, 31.5,200,     0, 200 , dv.weight);


		plotter.Plot2D(Form("%s_%s_dv_z_rxy"        , sample_name.c_str(),selection.c_str()), ";DV z [mm]; DV r_{xy} [mm]"          , dv.z  , dv.rxy      , 100., -300, 300, 100.,    0, 300 , dv.weight);
		plotter.Plot2D(Form("%s_%s_dv_x_y"          , sample_name.c_str(),selection.c_str()), ";DV x [mm]; DV y [mm]"               , dv.x  , dv.y        , 100., -300, 300, 100., -300, 300 , dv.weight);
		plotter.Plot2D(Form("%s_%s_dv_r_m"          , sample_name.c_str(),selection.c_str()), ";DV r [mm]; DV m [GeV]"              , dv.r  , dv.m        , 100.,    0, 300, 100.,    0, 100 , dv.weight);
		plotter.Plot2D(Form("%s_%s_dv_r_nTracks"    , sample_name.c_str(),selection.c_str()), ";DV r [mm]; DV nTracks"              , dv.r  , dv.nTracks  , 100.,    0, 300,  50.,    0, 50  , dv.weight);
		plotter.Plot2D(Form("%s_%s_dv_rxy_m"        , sample_name.c_str(),selection.c_str()), ";DV r_{xy} [mm]; DV m [GeV]"         , dv.rxy, dv.m        , 100.,    0, 300, 100.,    0, 100 , dv.weight);
		plotter.Plot2D(Form("%s_%s_dv_rxy_chi2"     , sample_name.c_str(),selection.c_str()), ";DV r_{xy} [mm];DV #chi^{2}/N_{DoF}" , dv.rxy, dv.chi2     , 100.,    0, 300, 100.,    0, 5.0 , dv.weight);
		plotter.Plot2D(Form("%s_%s_dv_rxy_nLRT"     , sample_name.c_str(),selection.c_str()), ";DV r_{xy} [mm]; DV nLRT"            , dv.rxy  , dv.nLRT   , 100.,    0, 300, 50.,     0, 50  , dv.weight);
		plotter.Plot2D(Form("%s_%s_dv_rxy_nTracks"  , sample_name.c_str(),selection.c_str()), ";DV r_{xy} [mm]; DV nTracks"         , dv.rxy, dv.nTracks  , 100.,    0, 300, 50.,     0, 50  , dv.weight);
		plotter.Plot2D(Form("%s_%s_dv_nTracks_nLRT" , sample_name.c_str(),selection.c_str()), ";DV nTracks; DV nLRT"                , dv.nTracks, dv.nLRT , 50.,     0, 50., 50.,     0, 50. , dv.weight);
		plotter.Plot2D(Form("%s_%s_dv_nTracks_chi2" , sample_name.c_str(),selection.c_str()), ";DV nTracks;DV #chi^{2}/N_{DoF}"     , dv.nTracks, dv.chi2 , 50.,     0, 50., 100.,    0, 5.0 , dv.weight);
		
	}
	

}
