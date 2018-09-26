#ifndef geometryhelper_h
#define geometryhelper_h

// Geometry functions that don't require doHistos class 
#define PI 3.14159265359


float deltaPhi(float phi1, float phi2){
	float dphi = phi1-phi2; 
	if (dphi >= PI) dphi -= 2* PI;
    if (dphi < -PI) dphi += 2* PI;
	return dphi;
}
float deltaEta(float eta1, float eta2){
	return eta1 - eta2;
}
float dR_cosmic(TLorentzVector p1, TLorentzVector p2){

	float absdphi = fabs(p1.DeltaPhi(p2));  
	float sumeta = p1.Eta()+p2.Eta();
	// for debugging
	//std::cout << " " << std::endl;
	//std::cout << " " << std::endl;
	//std::cout << " " << std::endl;
	//std::cout << "eta " << p1.Phi() << " : phi " << p1.Eta() << std::endl; 
	//std::cout << "eta " << p2.Phi() << " : phi " << p2.Eta() << std::endl; 
	//std::cout << " dphi " << absdphi << std::endl;
	//std::cout << " seta " << sumeta << std::endl;
	//std::cout << " dphi - PI " << absdphi-PI << std::endl;
	//std::cout << " dR " << sqrt( ( absdphi - PI )*( absdphi - PI ) + sumeta*sumeta ) << std::endl;

	//dR_cos = sqrt( ( absdphi - pi )*( absdphi - pi ) + sumeta*sumeta )
	float dR = sqrt( ( absdphi - PI )*( absdphi - PI ) + sumeta*sumeta );
	return dR; 

}


float vertexRxy(float x, float y){

	float r = sqrt(x*x+y*y);
	return r; 
}
float vertexR(float x, float y, float z){

	float r = sqrt(x*x+y*y+z*z);
	return r; 
}



#endif