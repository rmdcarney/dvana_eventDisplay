#ifndef cutflowHelper_h
#define cutflowHelper_h

  // a function to check whether an event passes
  // all the cuts up to "cut" - possibility to exclude some cuts
  // Usage: given a flag, check if it passes all cuts up to and including "cut"
  // excluding the cuts in "excludedCuts"
 // a function to create the bit mask
unsigned int bitmask(const unsigned int cut, const std::vector<unsigned int> excludeCuts={}) {
  
  unsigned int mask = 0;
  unsigned int bit  = 0;
  
  for (unsigned int i=0; i < cut+1; ++i) {
    if   ( std::find(excludeCuts.begin(), excludeCuts.end(), i) != excludeCuts.end() ) {
      // if a cut should be excluded set the corresponding bit to 0
      mask = mask | 0 << bit++;
    } else  { 
      // otherwise set the bit to 1
      mask = mask | 1 << bit++;
    }  
  }
  
  return mask;
}

bool passAllCutsUpTo(const unsigned long int flag, const unsigned int cut, const std::vector<unsigned int> excludeCuts={}) {
  
  // Get the bitmask: we want to check all cuts up to "cut" excluding the cuts listed in excludeCuts
  unsigned int mask = bitmask(cut, excludeCuts);
  // Check if the flag matches the bit mask
  return (flag & mask) == mask;
  
}

 // a function to check whether an event passes a specific set of cuts
bool passSpecificCuts(const unsigned long int flag, const std::vector<unsigned int> cuts) { 
  unsigned int mask = 0;
  // Make the bit mask
  for (auto cut : cuts) mask = mask | 1 << cut;
  // Check if the flag matches the bit mask
  return (flag & mask) == mask;
}


// a function to update the bit flag
void updateFlag(unsigned long int &flag, const unsigned int cutPosition, const bool passCut=1) { 
  // Put bit passCut (true or false) at position cutPosition
  flag = flag | passCut << cutPosition;
}


 // for DV Muon METSRs
namespace DVMu_METCuts {
	enum {
		AllNtup = 0,
		hasPV, // 1
		passPVz, //2 
		passPVntrk,
		passMETtrigger,
		passLHT, //5
		hasMuon,
		passMuonPt, 
		passMuonEta, //8
		passMuonID,
		passMuond0,  
		passMuonz0,  // 11
		passMuonFakeVeto, //12
		passFixedCutLoose,
		passMuonCosVeto,
		hasDV, //15
		passDVfid,
		passDVchi2,
		passDVdist,
		passDVmat,
		passDVntrk, //20
		passDVmass,
		passDVmuon, //22

		// For Control Regions
		failMuonFakeVeto, // 23
		failMuonHVVeto,   // 24
		failMuonCosVeto,  // 25
		noDV, 			  // 26 CR for measuring templates
		failDVmat3track,  // 27 VRMAT - if you fail
		passDV2track,     // 28 VR2LM
		passDV3trackLM,   // 29 VR3LM
		passDV3trackHM,   // 30 SR prediction!
   };
}
 // for DV Muon MuonSRs
namespace DVMu_MuonCuts {
	enum {
		AllNtup = 0,
		hasPV,
		passPVz,
		passPVntrk,
		passMSonlyTrigger, // 4
		passLHT,
		hasMuon,
		passMuonTM,
		passMuonPt,
		passMuonEta,
		passMuonID, // 10
		passMuond0, // 11
		passMuonz0, // 12
		passMuonFakeVeto,
		passFixedCutLoose,
		passMuonCosVeto, // 15
		hasDV, 			 // 16
		passDVfid,
		passDVchi2,
		passDVdist,
		passDVmat,
		passDVntrk, //21
		passDVmass,
		passDVmuon,

		// For Control Regions
		failMuonFakeVeto, 	// 24
		failMuonHVVeto,  	// 25 
		failMuonCosVeto, 	// 26 
		noDV, 			 	// 27 CR for measuring templates
		failDVmat3track, 	// 28 VRMAT - if you fail
		passDV2track,    	// 29 VR2LM
		passDV3trackLM,  	// 30 VR3LM
		passDV3trackHM,  	// 31 SR prediction! (
			// CANNOT ADD ANYMORE CUTS!
   };
}



namespace AnalysisRegions {
   enum {
      met_matched = 0,
      met_unmatched,
      muon_matched,
      muon_unmatched
   };
}

#endif