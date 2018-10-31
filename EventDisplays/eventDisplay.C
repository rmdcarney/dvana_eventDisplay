#include "DataObj.h"

#include <TFile.h>
#include <TTree.h>
#include <TLeaf.h>
#include <TH1F.h>
#include <TVector3.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TSystem.h>
#include <TStyle.h>
#include <TInterpreter.h>
#include <TEllipse.h>
#include <TLine.h>
#include <TLatex.h>
#include <TMath.h>

#include <numeric>
#include <algorithm>
#include <iostream>
#include <map>

#pragma link C++ class std::vector<std::vector<int> >+;
#pragma link C++ class std::vector<std::vector<float> >+;
#pragma link C++ class std::vector<std::vector<unsigned char> >+;
#pragma link C++ class std::vector<std::vector<unsigned int> >+;

bool doPrint=true;
bool doBatch=true;
int maxEvents=500;

//===============================
// W I T H I N 
//===============================
bool within( double r, double rmin, double rmax ) 
{
    return (r > rmin && r < rmax);
}

//===============================
// I S   M U O N 
//===============================
bool isMuon( double trk_d0, double trk_z0, double mu_d0, double mu_z0 )
{  // IS THIS TRACK A MUON

    float eps = 0.0005;
    if ( fabs(mu_d0 - trk_d0) < eps && fabs(mu_z0 - trk_z0) < eps ) return true;
    else return false;

}
//===============================
// E V E N T   D I S P L A Y
//===============================
void eventDisplay() {


    std::cout << "Starting" << std::endl;

    //&&&&&&&&&&&&&&&&&&&&&&
    // display
    //&&&&&&&&&&&&&&&&&&&&&
    gROOT->SetBatch(1);
    gStyle->SetPadLeftMargin(0.15);
    gStyle->SetPadBottomMargin(0.15);
    gStyle->SetPadRightMargin(0.05);
    gStyle->SetPadTopMargin(0.05);
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    gStyle->SetTitleOffset(1.2, "xy");

    std::vector< std::unique_ptr<DataObj> > dobjs;
    // DataObj( filename, treename, title )
    dobjs.emplace_back( new DataObj( "../in/rhad_1700_tau_0p1ns.root", "trees_SRDV_" , "#tilde{t}#rightarrow #mu + q, m(#tilde{t}) = 1700 GeV, #tau(#tilde{t}) = 0.1 ns" ) );

    std::vector<TObject*> objs;
    std::unique_ptr<TCanvas> c( new TCanvas("c", "", 0, 0, 800, 800) );

    //&&&&&&&&&&&&&&&&&&&&&
    // Pixel layer guides
    //&&&&&&&&&&&&&&&&&&&&&
    std::vector< std::unique_ptr<TEllipse> > guides;
    guides.emplace_back( new TEllipse( 0.0, 0.0, 33.0, 33.0 ) );
    guides.emplace_back( new TEllipse( 0.0, 0.0, 50.5, 50.5 ) );
    guides.emplace_back( new TEllipse( 0.0, 0.0, 85.0, 85.0 ) );
    guides.emplace_back( new TEllipse( 0.0, 0.0, 125.0, 125.0 ) );
    guides.emplace_back( new TEllipse( 0.0, 0.0, 299.0, 299.0 ) );
    //guides.emplace_back( new TEllipse( 0.0, 0.0, 371.0, 371.0 ) );
    //guides.emplace_back( new TEllipse( 0.0, 0.0, 443.0, 443.0 ) );

    for( auto& guide : guides ) {
        guide->SetFillStyle(0);
        guide->SetLineColor(kGray);
        guide->SetLineStyle(1);
        guide->SetLineWidth(2);
    }

    //&&&&&&&&&&&&&&&&&&&&&
    // Loop trees
    //&&&&&&&&&&&&&&&&&&&&&
    double scope { 310 };
    std::cout << " size dobjs " << dobjs.size() << std::endl;
    for( auto& dobj : dobjs ) { //loop over trees

        //&&&&&&&&&&&&&
        // Event loop
        //&&&&&&&&&&&&&
        std::cout << "reading tree " << dobj->tree->GetName() << std::endl;
        auto entry = 0LL;
        int printed=0;
        while( entry < dobj->tree->GetEntriesFast() ) {

            std::cout << "reading entry " <<  entry << std::endl;
            dobj->tree->GetEntry( entry );

            // If there are no displaced vertices 
            if( dobj->vtx_r->size() == 0 ) {
                entry++;
                continue;
            }
            c->Clear();

            //&&&&&&&&&&&&&&
            // Draw frames 
            //&&&&&&&&&&&&&&
            std::unique_ptr<TH1> frame1( c->DrawFrame( -scope, -scope, scope, scope ) );
            frame1->SetLineStyle(0);
            frame1->SetLineWidth(0);
            frame1->SetMarkerStyle(0);
            frame1->GetXaxis()->SetTitleOffset(1.5);
            frame1->GetYaxis()->SetTitleOffset(1.8);
            frame1->SetTitle(";x [mm];y [mm]");
            for( auto& guide : guides ) { guide->Draw("l+"); }

            //Latex for labels
            TLatex latex;
            latex.SetTextAlign(12);
            latex.SetTextFont(42);

            //std::cout << "plotting..." << std::endl;
            //&&&&&&&&&&&&&&&&&&&&&&&&
            // plot displace vertices
            //&&&&&&&&&&&&&&&&&&&&&&&
            std::vector< std::unique_ptr<TGraph> > grs_vtx;
            std::vector< std::unique_ptr<TGraph> > grs_hits;
            grs_vtx.emplace_back( new TGraph );
            grs_hits.emplace_back( new TGraph );

            for( auto& gr : grs_vtx ) {
                gr->SetMarkerStyle(20);
                gr->SetMarkerSize(0.7);
            }
            
            // size_t panel { 0 };
            unsigned panel = 0;
            std::vector<std::vector<std::unique_ptr<TGraph> > > gr_trks(2);
            std::vector<std::vector<std::unique_ptr<TGraph> > > bad_trks(2);
            std::vector<std::vector<std::unique_ptr<TGraph> > > muon_trks(2);

            latex.SetTextSize(0.03);
            latex.DrawLatexNDC(0.18, 0.93, dobj->name.c_str() );
            latex.DrawLatexNDC(0.18, 0.88, Form("Run number %i", dobj->runNumber ) );
            latex.DrawLatexNDC(0.18, 0.83, Form("Event number %li", dobj->eventNumber ) );
            latex.SetTextSize(0.023);

            std::cout << " size dvs " << dobj->vtx_ntrk->size() << std::endl;

            // to save times
            auto& trk_pt_wrtSV      = dobj->vtx_trk_pt_wrtSV ;
            auto& trk_eta_wrtSV     = dobj->vtx_trk_eta_wrtSV;
            auto& trk_phi_wrtSV     = dobj->vtx_trk_phi_wrtSV;
            auto& trk_eta           = dobj->vtx_trk_eta;
            auto& trk_phi           = dobj->vtx_trk_phi;
            auto& trk_d0            = dobj->vtx_trk_d0;
            auto& trk_z0            = dobj->vtx_trk_z0;
            auto& trk_pt            = dobj->vtx_trk_pt;
            auto& trk_isAssociated  = dobj->vtx_trk_isAssociated;
            auto& trk_vtx_index     = dobj->vtx_trk_vtx_index;

            auto& muon_d0           = dobj->muon_d0 ;
            auto& muon_z0           = dobj->muon_z0 ;

            //&&&&&&&&&&&&&&&&&&&&&&&
            // Loop vertices
            //&&&&&&&&&&&&&&&&&&&&&&&
            for( size_t iv = 0; iv < dobj->vtx_ntrk->size(); iv++ ) {  

                std::cout << __FUNCTION__ << " vtx index " << iv << std::endl;

                // Apply some fiducial requirements to DVs
                if ( dobj->vtx_rxy->at(iv) < 4 || dobj->vtx_rxy->at(iv) > 300 || dobj->vtx_z->at(iv) > 300 ) continue;

                const auto& r   = dobj->vtx_r  ->at(iv);
                const auto& phi = atan(dobj->vtx_y->at(iv)/dobj->vtx_x->at(iv) );
                const auto& x   = dobj->vtx_x->at(iv) ;
                const auto& y   = dobj->vtx_y->at(iv);
                const auto& index = dobj->vtx_index->at(iv);


                int matched_ntrks = 0;
                //&&&&&&&&&&&&&&&&&&&&&&&
                // Loop DV tracks
                //&&&&&&&&&&&&&&&&&&&&&&&
                for( size_t itrk=0; itrk < trk_pt_wrtSV->size(); itrk++) {

                    if ( trk_vtx_index->at(itrk) != index) continue;// making sure we're only showing relevent tracks
                    matched_ntrks++;

                    // Check if track is in material 
                    bool inMat = 0;
                    if ( trk_isAssociated->at(itrk)==1 && fabs(trk_d0->at(itrk)) > 117 && fabs(trk_d0->at(itrk)) < 125) inMat=1; 
                    if ( trk_isAssociated->at(itrk)==1 && fabs(trk_d0->at(itrk)) > 84  && fabs(trk_d0->at(itrk)) < 94 ) inMat=1; 
                    if ( trk_isAssociated->at(itrk)==1 && fabs(trk_d0->at(itrk)) > 45  && fabs(trk_d0->at(itrk)) < 55 ) inMat=1; 
                    if ( trk_isAssociated->at(itrk)==1 && fabs(trk_d0->at(itrk)) > 30  && fabs(trk_d0->at(itrk)) < 39 ) inMat=1;

                    // If so save to different collection for color coding
                    TVector3 p; p.SetPtEtaPhi( trk_pt_wrtSV->at(itrk), trk_eta_wrtSV->at(itrk), trk_phi_wrtSV->at(itrk) );

                    auto* line = new TGraph;
                    line->SetPoint(0, x, y );
                    //line->SetPoint(0, r*cos(phi), r*sin(phi) );
                    line->SetPoint(1, x + p.Perp()*cos(p.Phi())*20, y + p.Perp()*sin(p.Phi())*20 );
                    //line->SetPoint(1, r*cos(phi) + p.Perp()*cos(p.Phi())*20, r*sin(phi) + p.Perp()*sin(p.Phi())*20 );

                    //if (inMat) {
                    //  bad_trks.at(panel).emplace_back( line );
                    //  latex.DrawLatex( r*cos(phi)-20*scope/400, r*sin(phi)+(matched_ntrks*20+40)*scope/400., Form("eta: %.1f, phi %.1f, d0 : %.1f mm", trk_eta->at(itrk), trk_phi->at(itrk), trk_d0->at(itrk)  )  );
                    //}

                    if (isTrackAMuon){
                        muon_trks.at(panel).emplace_back( line );  
                        latex.DrawLatex( r*cos(phi)-20*scope/400, r*sin(phi)+(matched_ntrks*20+40)*scope/400., Form("muon : pt %.1f, eta %.1f, phi %.1f, d0 %.1f mm", trk_pt->at(itrk), trk_eta->at(itrk), trk_phi->at(itrk), trk_d0->at(itrk)  )  );

                    }  
                    else       {
                        gr_trks.at(panel).emplace_back( line );      
                        latex.DrawLatex( r*cos(phi)-20*scope/400, r*sin(phi)+(matched_ntrks*20+40)*scope/400., Form("track : pt %.1f, eta %.1f, phi %.1f, d0 %.1f mm", trk_pt->at(itrk), trk_eta->at(itrk), trk_phi->at(itrk), trk_d0->at(itrk)  )  );

                    }


                }// end loop on tracks 

                if( matched_ntrks==0 ) {
                    std::cout << "WARNING:: associated track is not found" << std::endl;
                }

                grs_vtx.at(panel)->SetPoint( grs_vtx.at(panel)->GetN(), x, y );
                //grs_vtx.at(panel)->SetPoint( grs_vtx.at(panel)->GetN(), r*cos(phi), r*sin(phi) );

            }// end loop on DVs 

            std::cout << "start plotting" << std::endl;
            std::cout << "Draw DVs" << std::endl;

            if( grs_vtx.at(panel)->GetN() > 0 ) grs_vtx.at(panel)->Draw("p+");

            //std::cout << "Draw Muons" << std::endl;

            //TODO change this for the track collections we care about
            for( auto& gr_trk : muon_trks.at(panel) ) {
                gr_trk->SetLineColor(kRed);
                //gr_trk->SetLineStyle(3);
                gr_trk->Draw("l+");
            }

            //std::cout << "Draw Tracks" << std::endl;
            for( auto& gr_trk : gr_trks.at(panel) ) {
                gr_trk->SetLineColor(kBlue);
                gr_trk->Draw("l+");
            }

            for( auto& bad_trk : bad_trks.at(panel) ) {
                bad_trk->SetLineColor(kBlue); // for now
                bad_trk->Draw("l+");
            }


            std::cout << "Draw Labels" << std::endl;
            //TODO I would save this for debugging only
            for( size_t iv = 0; iv < dobj->vtx_r->size(); iv++ ) {

                // Apply some fiducial requirements to DVs
                if ( dobj->vtx_rxy->at(iv) < 4 || dobj->vtx_rxy->at(iv) > 300 || dobj->vtx_z->at(iv) > 300 ) continue;

                const auto& r   = dobj->vtx_r  ->at(iv);
                const auto& phi = atan(dobj->vtx_y->at(iv)/dobj->vtx_x->at(iv) );
                const auto& x   = dobj->vtx_x->at(iv) ;
                const auto& y   = dobj->vtx_y->at(iv);
                //const auto& phi = dobj->vtx_phi->at(iv);

                //latex.DrawLatex( r*cos(phi)+10*scope/400, r*sin(phi), Form("[%lu]", iv) );

                double xtarget = x+10*scope/400;
                double ytarget = y;

                //latex.DrawLatex( xtarget, ytarget,    Form("[%lu]: " , iv ) ); // draw AT Vertex
                latex.DrawLatex( xtarget, ytarget,      Form("[%lu]: (rxy,z): (%.1f, %.1f), N_{trk}: %u" , iv, dobj->vtx_rxy->at(iv), dobj->vtx_z->at(iv), dobj->vtx_ntrk->at(iv) ) );
                latex.DrawLatex( xtarget, ytarget-20,   Form("  m: %.2f GeV, #chi^{2}: %.2e"         , dobj->vtx_mass->at(iv), dobj->vtx_chi2->at(iv)) );
                latex.DrawLatex( xtarget, ytarget-40,   Form("  x: %.1f, y: %0.1f"                    , dobj->vtx_x->at(iv), dobj->vtx_y->at(iv) ) );
            }// end loop on labeling dvs 


            //std::cout << "modify pad" << std::endl;

            gPad->Modified();
            gPad->Update();


            if( doBatch || doPrint ) {

                gSystem->mkdir( "displays", true );
                gPad->SaveAs(Form("displays/%s_event%li.pdf", dobj->tree_name.c_str(), dobj->eventNumber));
                printed++;
            }

            //std::cout << "process events" << std::endl;
            gSystem->ProcessEvents();

            //std::cout << "blah" << std::endl;

            if( printed >= maxEvents ) break;
            entry++;
            //std::cout << "yikes" << std::endl;

        }// while loop over entries 

        std::cout << "end dobj" << std::endl;

    }//dobjs

}
