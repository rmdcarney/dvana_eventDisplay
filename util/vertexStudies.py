#!usr/bin/env python
import ROOT
import sys
import math
from array import array
from plots import setStyle
from plots import get1DHisto
from plots import get2DHisto

f = ROOT.TFile.Open("histograms.root")

def getlabel(hist):
	dist = hist.GetName()
	label = ""

	# sample
	if "Stop_1000_0p1ns" in dist: label += "1000 GeV, 0.1ns: "
	if "Stop_1100_1ns"   in dist: label += "1100 GeV, 1ns: "
	if "RHad_1000_0p01ns" in dist: label += "m(#tilde{t}) = 1000 GeV, #tau(#tilde{t}) = 0.01 ns "
	if "RHad_1100_0p1ns"  in dist: label += "m(#tilde{t}) = 1100 GeV, #tau(#tilde{t}) = 0.1 ns "
	if "RHad_1100_1ns"    in dist: label += "m(#tilde{t}) = 1100 GeV, #tau(#tilde{t}) = 1 ns "
	if "RHad_1300_0p01ns" in dist: label += "m(#tilde{t}) = 1300 GeV, #tau(#tilde{t}) = 0.01 ns "
	if "RHad_all"         in dist: label += "R Hadron Samples"

	# matching selection
	#if   "all" 			 in dist: label += " All"
	#if   "truthmatched"  in dist: label += " Truth Matched"
	#if   "recomatched"   in dist: label += " Reco Matched"
	#if   "unmatched" 	 in dist: label += " Unmatched"

	# object 
	#if "muon" in dist: label += " Muons"
	#if "DV"   in dist: label += " DVs"
	#if "dv"   in dist: label += " DVs"
	
	return label 

def get_logy(hist):
	dist = hist.GetName()

	if "d0" in dist : return True

	return False

def rebin(hist):
	dist = hist.GetName()

	if "d0" in dist: return 2

	return False

def rebin_eff(hist):
	dist = hist.GetName()

	if "d0"  in dist: return 5
	if "eta" in dist: return 2
	if "phi" in dist: return 5
	if "pt"  in dist: return 5

	if "dv_R"  in dist: return 5
	if "dv_m"  in dist: return 5
	#if "dv_ntrks"  in dist: return 2


	return False

def clean1D(hist,scale=False):
	
	if scale:
		hist.Scale(1.0/hist.Integral(0,-1,0,-1))
		hist.SetMaximum(0.1)
		hist.SetMinimum(0.000001)

	hist.GetXaxis().SetNdivisions(505)
	hist.GetYaxis().SetNdivisions(505)
	hist.GetZaxis().SetNdivisions(505)

	hist.GetXaxis().SetTitleSize(0.05)
	hist.GetXaxis().SetLabelSize(0.05)
	hist.GetYaxis().SetTitleSize(0.05)
	hist.GetYaxis().SetLabelSize(0.05)
	hist.GetZaxis().SetTitleSize(0.05)
	hist.GetZaxis().SetLabelSize(0.05)

	hist.GetXaxis().SetTitleOffset(1.2)
	hist.GetYaxis().SetTitleOffset(1.2)
	hist.GetZaxis().SetTitleOffset(2.0)
	
	return 

def ratio(hist):
	# Formats Ratio Histogram

	hist.SetLineWidth(3)
	hist.SetMarkerSize(2)
	hist.SetMarkerStyle(20)
	hist.SetLineColor(ROOT.kBlack)
	hist.SetMarkerColor(ROOT.kBlack)

	hist.GetYaxis().SetTitleSize(20);
	hist.GetYaxis().SetTitleFont(43);
	hist.GetYaxis().SetTitleOffset(1.55);

	# Y axis ratio plot settings
	hist.GetYaxis().SetTitle("Efficiency");

	hist.GetYaxis().SetNdivisions(505);
	hist.GetYaxis().SetTitleSize(28);
	hist.GetYaxis().SetTitleFont(43);
	hist.GetYaxis().SetTitleOffset(1.7);
	hist.GetYaxis().SetLabelFont(43);# Absolute font size in pixel (precision 3)
	hist.GetYaxis().SetLabelSize(25);
	
	# X axis ratio plot settings
	hist.GetXaxis().SetTitleSize(28);
	hist.GetXaxis().SetTitleFont(43);
	hist.GetXaxis().SetTitleOffset(3.0);
	hist.GetXaxis().SetLabelFont(43); # Absolute font size in pixel (precision 3)
	hist.GetXaxis().SetLabelSize(25);

	return hist

def compare1D(dist1, dist2):

	hist1 = get1DHisto(f,dist1)
	hist2 = get1DHisto(f,dist2)

	# setup canvas	
	canvas = ROOT.TCanvas("", "", 800, 900)
	canvas.Draw()
	canvas.cd()

	if "ntrks" not in dist1 or "Stop" not in dist1: 
		hist1.Rebin(2)
		hist2.Rebin(2)

	# draw histos 
	logy = 0
	if "d0" in dist1:
		logy=1
	
	maximum = max(hist1.GetMaximum(),hist2.GetMaximum())
	hist1.SetMaximum(1.45*maximum)
	hist1.SetMinimum(0.)
	if logy :
		hist1.SetMaximum(15*maximum)
		hist1.SetMinimum(0.1)
	
	clean1D(hist1)
	clean1D(hist2) 

	hist1.SetLineWidth(3)
	hist2.SetLineWidth(3)
	hist1.SetLineColor(ROOT.kRed+1)
	hist2.SetLineColor(ROOT.kAzure+1)
	hist1.SetMarkerColor(ROOT.kRed+1)
	hist2.SetMarkerColor(ROOT.kAzure+1)

	hist1.Draw("hist")
	hist2.Draw("hist same")

	legend = ROOT.TLegend(0.17, 0.82, 0.84, 0.90)
	legend.SetBorderSize(0)
	legend.SetFillColor(0)
	legend.SetTextSize(0.035)
	legend.AddEntry(hist1  ,getlabel(hist1),"l") 
	legend.AddEntry(hist2  ,getlabel(hist2),"l")   
	legend.Draw()

	canvas.SetLogy(logy)
	canvas.Print("Plots/Compare/"+dist1+".png")
	canvas.Close()
	canvas.SetLogy(0)
	return

def clean2D(hist,scale=False):
	
	if scale:
		hist.Scale(1.0/hist.Integral(0,-1,0,-1))
		hist.SetMaximum(0.1)
		hist.SetMinimum(0.000001)

	hist.GetXaxis().SetNdivisions(505)
	hist.GetYaxis().SetNdivisions(505)
	hist.GetZaxis().SetNdivisions(505)

	hist.GetXaxis().SetTitleSize(0.05)
	hist.GetXaxis().SetLabelSize(0.05)
	hist.GetYaxis().SetTitleSize(0.05)
	hist.GetYaxis().SetLabelSize(0.05)
	hist.GetZaxis().SetTitleSize(0.05)
	hist.GetZaxis().SetLabelSize(0.05)

	hist.GetXaxis().SetTitleOffset(1.2)
	hist.GetYaxis().SetTitleOffset(1.0)
	hist.GetZaxis().SetTitleOffset(2.0)
	
	return  

def print2D(dist):

	# setup canvas	
	canvas = ROOT.TCanvas("", "", 900, 800)
	canvas.SetTopMargin(0.09)
	canvas.SetBottomMargin(0.13)
	canvas.SetLeftMargin(0.14)
	canvas.SetRightMargin(0.18)
	canvas.Draw()
	canvas.cd()
	#canvas.SetLogz(1)

	hist = get2DHisto(f,dist)
	clean2D(hist)
	if "dPhi" 		in dist: hist.GetYaxis().SetTitle("#Delta#phi_{mu,seg} - #pi")
	if "sumEta" 	in dist: hist.GetXaxis().SetTitle("#eta_{mu} + #eta_{seg}")
	if "sumEtaCorr" in dist: hist.GetXaxis().SetTitle("#eta_{mu} corr. + #eta_{seg}")
	if "Loose"	    in dist: hist.GetZaxis().SetRangeUser(0,15)
	hist.GetYaxis().SetTitleOffset(1.2)
	hist.GetZaxis().SetTitleOffset(1.3)
	hist.Draw("COLZ")

	text =  ROOT.TLatex(0.16,0.92,getlabel(hist));
	text.SetNDC();
	text.SetTextFont(43);
	text.SetTextSize(35);
	text.Draw();

	canvas.Print("Plots/2D/"+dist+".png")
	canvas.Close()

	return 

def efficiency(numerator_name,denominator_name,label1="",label2=""):

	numerator   = get1DHisto(f,numerator_name)
	denominator = get1DHisto(f,denominator_name)

	# setup canvas	
	canvas = ROOT.TCanvas("", "", 800, 900)
	canvas.Draw()

	# Upper plot will be in pad1
	pad1 = ROOT.TPad("pad1", "pad1", 0, 0.35, 1, 1.0);
	pad1.SetBottomMargin(0.02);  # Upper and lower plot are joined
	pad1.SetTicks();          # Ticks
	pad1.Draw();              # Draw the upper pad: pad1
	pad1.cd();                # pad1 becomes the current pad
	pad1.SetLogy(get_logy(numerator))

	# lower plot will be in pad
	canvas.cd();          # Go back to the main canvas before defining pad2
	pad2 = ROOT.TPad("pad2", "pad2", 0, 0.05, 1, 0.35)
	pad2.SetTopMargin(0.02)
	pad2.SetBottomMargin(0.2)
	pad2.SetTicks() # Ticks
	pad2.Draw()
	pad2.cd()
	#pad2.SetLogy(logy)

	# Draw top half
	pad1.cd()
	clean1D(numerator)
	clean1D(denominator)
	if "eta" in numerator_name:
		numerator  .GetXaxis().SetRangeUser(-2.5,2.5) 
		denominator.GetXaxis().SetRangeUser(-2.5,2.5) 
	if rebin_eff(numerator):
		numerator  .Rebin(rebin_eff(numerator))
		denominator.Rebin(rebin_eff(denominator))


	numerator  .SetLineWidth(3)
	denominator.SetLineWidth(3)
	#numerator  .SetFillStyle(1)
	#denominator.SetFillStyle(1)
	#numerator  .SetFillColor(ROOT.kBlack)
	#denominator.SetFillColor(ROOT.kAzure+1)
	numerator  .SetLineColor(ROOT.kAzure+1)
	denominator.SetLineColor(ROOT.kRed+1)

	maxim = max(denominator.GetMaximum(), numerator.GetMaximum())
	denominator.SetMaximum(1.4*maxim)
	if get_logy(denominator):
		denominator.SetMaximum(50*maxim)

	denominator.GetXaxis().SetLabelSize(0)
	denominator.Draw("hist")
	numerator.Draw("hist same")

	y = 0.75
	legend = ROOT.TLegend(0.2, y, 0.93, 0.91)
	legend.SetBorderSize(0)
	legend.SetFillColor(0)
	legend.SetTextSize(0.05)
	legend.AddEntry(numerator    ,label1,"l") 
	legend.AddEntry(denominator  ,label2,"l")   
	legend.Draw()


	# Draw bottom half 
	pad2.cd()       #pad2 becomes the current pad

	# scale and draw
	signal_eff = numerator.Clone()
	signal_eff.Divide(numerator, denominator,1,1,"B");
	signal_eff.GetYaxis().SetRangeUser(0,1.1)
	ratio(signal_eff)

	signal_eff.Draw()

	
	#text =  ROOT.TLatex(0.11,0.92,getlabel(hist));
	#text.SetNDC();
	#text.SetTextFont(43);
	#text.SetTextSize(35);
	#text.Draw();


	canvas.Print("Plots/SigEff/"+numerator_name+".png")

	canvas.SetLogz(0)
	canvas.Close()

	return	


def do1Dcomparisons():
	
	# DV truth DVs v. fake DVs Plots 
	#compare1D("RHad_1100_1ns_truthmatched_recodv_Rxy" 		, "RHad_1100_1ns_unmatched_recodv_Rxy"		)
	#compare1D("RHad_1100_1ns_truthmatched_recodv_R" 		, "RHad_1100_1ns_unmatched_recodv_R"		)
	#compare1D("RHad_1100_1ns_truthmatched_recodv_m" 		, "RHad_1100_1ns_unmatched_recodv_m"		)
	#compare1D("RHad_1100_1ns_truthmatched_recodv_mbig" 		, "RHad_1100_1ns_unmatched_recodv_mbig"		)
	#compare1D("RHad_1100_1ns_truthmatched_recodv_ntrks" 	, "RHad_1100_1ns_unmatched_recodv_ntrks"	)
	#
	#compare1D("RHad_1100_0p1ns_truthmatched_recodv_Rxy" 		, "RHad_1100_0p1ns_unmatched_recodv_Rxy"		)
	#compare1D("RHad_1100_0p1ns_truthmatched_recodv_R" 			, "RHad_1100_0p1ns_unmatched_recodv_R"			)
	#compare1D("RHad_1100_0p1ns_truthmatched_recodv_m" 			, "RHad_1100_0p1ns_unmatched_recodv_m"			)
	#compare1D("RHad_1100_0p1ns_truthmatched_recodv_mbig" 		, "RHad_1100_0p1ns_unmatched_recodv_mbig"		)
	#compare1D("RHad_1100_0p1ns_truthmatched_recodv_ntrks" 		, "RHad_1100_0p1ns_unmatched_recodv_ntrks"		)
	# DV truth DVs v. fake DVs Plots 
	#compare1D("RHad_1000_0p01ns_truthmatched_recodv_Rxy" 		, "RHad_1000_0p01ns_unmatched_recodv_Rxy"		)
	#compare1D("RHad_1000_0p01ns_truthmatched_recodv_R" 			, "RHad_1000_0p01ns_unmatched_recodv_R"			)
	#compare1D("RHad_1000_0p01ns_truthmatched_recodv_m" 			, "RHad_1000_0p01ns_unmatched_recodv_m"			)
	#compare1D("RHad_1000_0p01ns_truthmatched_recodv_mbig" 		, "RHad_1000_0p01ns_unmatched_recodv_mbig"		)
	#compare1D("RHad_1000_0p01ns_truthmatched_recodv_ntrks" 		, "RHad_1000_0p01ns_unmatched_recodv_ntrks"		)
	
	# Muon plots 
	compare1D("RHad_1000_0p01ns_all_truthmuon_d0"  , "RHad_1000_0p01ns_recomatched_truthmuon_d0"  )
	compare1D("RHad_1000_0p01ns_all_truthmuon_pt"  , "RHad_1000_0p01ns_recomatched_truthmuon_pt"  )
	compare1D("RHad_1000_0p01ns_all_truthmuon_eta" , "RHad_1000_0p01ns_recomatched_truthmuon_eta" )
	compare1D("RHad_1000_0p01ns_all_truthmuon_phi" , "RHad_1000_0p01ns_recomatched_truthmuon_phi" )
	
	compare1D("RHad_1100_0p1ns_all_truthmuon_d0"  , "RHad_1100_0p1ns_recomatched_truthmuon_d0"  )
	compare1D("RHad_1100_0p1ns_all_truthmuon_pt"  , "RHad_1100_0p1ns_recomatched_truthmuon_pt"  )
	compare1D("RHad_1100_0p1ns_all_truthmuon_eta" , "RHad_1100_0p1ns_recomatched_truthmuon_eta" )
	compare1D("RHad_1100_0p1ns_all_truthmuon_phi" , "RHad_1100_0p1ns_recomatched_truthmuon_phi" )
	
	compare1D("RHad_1100_1ns_all_truthmuon_d0"  , "RHad_1100_1ns_recomatched_truthmuon_d0"  )
	compare1D("RHad_1100_1ns_all_truthmuon_pt"  , "RHad_1100_1ns_recomatched_truthmuon_pt"  )
	compare1D("RHad_1100_1ns_all_truthmuon_eta" , "RHad_1100_1ns_recomatched_truthmuon_eta" )
	compare1D("RHad_1100_1ns_all_truthmuon_phi" , "RHad_1100_1ns_recomatched_truthmuon_phi" )

	return 

def doMuonEfficiency():
	label_den = "Truth Muons"
	label_num = "Reco Matched Muons"
	efficiency("RHad_1100_1ns_recomatched_truthmuon_d0"  , "RHad_1100_1ns_acceptance_truthmuon_d0" , label_num, label_den )
	efficiency("RHad_1100_1ns_recomatched_truthmuon_pt"  , "RHad_1100_1ns_acceptance_truthmuon_pt" , label_num, label_den )
	efficiency("RHad_1100_1ns_recomatched_truthmuon_eta" , "RHad_1100_1ns_acceptance_truthmuon_eta", label_num, label_den )
	efficiency("RHad_1100_1ns_recomatched_truthmuon_phi" , "RHad_1100_1ns_acceptance_truthmuon_phi", label_num, label_den )

	efficiency("RHad_1100_0p1ns_recomatched_truthmuon_d0"  , "RHad_1100_0p1ns_acceptance_truthmuon_d0" , label_num, label_den )
	efficiency("RHad_1100_0p1ns_recomatched_truthmuon_pt"  , "RHad_1100_0p1ns_acceptance_truthmuon_pt" , label_num, label_den )
	efficiency("RHad_1100_0p1ns_recomatched_truthmuon_eta" , "RHad_1100_0p1ns_acceptance_truthmuon_eta", label_num, label_den )
	efficiency("RHad_1100_0p1ns_recomatched_truthmuon_phi" , "RHad_1100_0p1ns_acceptance_truthmuon_phi", label_num, label_den )
	return 

def doDVEfficiency():
	label_den = "Truth DVs"
	label_num = "Reco Matched DVs"

	efficiency("RHad_all_recomatched_truthdv_Rxy" 		, "RHad_all_all_truthdv_Rxy"		, label_num, label_den )
	efficiency("RHad_all_recomatched_truthdv_R" 		, "RHad_all_all_truthdv_R"			, label_num, label_den )
	efficiency("RHad_all_recomatched_truthdv_m" 		, "RHad_all_all_truthdv_m"			, label_num, label_den )
	efficiency("RHad_all_recomatched_truthdv_ntrks" 	, "RHad_all_all_truthdv_ntrks"		, label_num, label_den )

	efficiency("RHad_1100_1ns_recomatched_truthdv_Rxy" 		, "RHad_1100_1ns_all_truthdv_Rxy"		, label_num, label_den )
	efficiency("RHad_1100_1ns_recomatched_truthdv_R" 		, "RHad_1100_1ns_all_truthdv_R"			, label_num, label_den )
	efficiency("RHad_1100_1ns_recomatched_truthdv_m" 		, "RHad_1100_1ns_all_truthdv_m"			, label_num, label_den )
	efficiency("RHad_1100_1ns_recomatched_truthdv_ntrks" 	, "RHad_1100_1ns_all_truthdv_ntrks"		, label_num, label_den )
	
	efficiency("RHad_1100_0p1ns_recomatched_truthdv_Rxy" 	, "RHad_1100_0p1ns_all_truthdv_Rxy"		, label_num, label_den )
	efficiency("RHad_1100_0p1ns_recomatched_truthdv_R" 		, "RHad_1100_0p1ns_all_truthdv_R"		, label_num, label_den )
	efficiency("RHad_1100_0p1ns_recomatched_truthdv_m" 		, "RHad_1100_0p1ns_all_truthdv_m"		, label_num, label_den )
	efficiency("RHad_1100_0p1ns_recomatched_truthdv_ntrks" 	, "RHad_1100_0p1ns_all_truthdv_ntrks"	, label_num, label_den )	

	#label_den = "Alls DVs"
	#label_num = "Truth Matched DVs"
	#
	#efficiency("RHad_1100_1ns_truthmatched_recodv_Rxy" 		, "RHad_1100_1ns_all_recodv_Rxy"		, label_num, label_den )
	#efficiency("RHad_1100_1ns_truthmatched_recodv_R" 		, "RHad_1100_1ns_all_recodv_R"			, label_num, label_den )
	#efficiency("RHad_1100_1ns_truthmatched_recodv_m" 		, "RHad_1100_1ns_all_recodv_m"			, label_num, label_den )
	#efficiency("RHad_1100_1ns_truthmatched_recodv_mbig" 	, "RHad_1100_1ns_all_recodv_mbig"		, label_num, label_den )
	#efficiency("RHad_1100_1ns_truthmatched_recodv_ntrks" 	, "RHad_1100_1ns_all_recodv_ntrks"		, label_num, label_den )
	#
	#efficiency("RHad_1100_0p1ns_truthmatched_recodv_Rxy" 	, "RHad_1100_0p1ns_all_recodv_Rxy"		, label_num, label_den )
	#efficiency("RHad_1100_0p1ns_truthmatched_recodv_R" 		, "RHad_1100_0p1ns_all_recodv_R"		, label_num, label_den )
	#efficiency("RHad_1100_0p1ns_truthmatched_recodv_m" 		, "RHad_1100_0p1ns_all_recodv_m"		, label_num, label_den )
	#efficiency("RHad_1100_0p1ns_truthmatched_recodv_mbig" 	, "RHad_1100_0p1ns_all_recodv_mbig"		, label_num, label_den )
	#efficiency("RHad_1100_0p1ns_truthmatched_recodv_ntrks" 	, "RHad_1100_0p1ns_all_recodv_ntrks"	, label_num, label_den )

	return 

def do2D():

	print2D( "RHad_all_recomatched_tracking_mdiff_truthdv_rxy") 	
	print2D( "RHad_all_recomatched_tracking_ntrkdiff_truthdv_rxy") 
	print2D( "RHad_all_recomatched_tracking_truthdv_m_recodv_m") 
	print2D( "RHad_all_recomatched_tracking_truthdv_ntrks_recodv_ntrks")
	print2D( "RHad_all_recomatched_tracking_ntrkdiff_mdiff")

	print2D( "RHad_all_recomatched_vertexing_mdiff_truthdv_rxy") 	
	print2D( "RHad_all_recomatched_vertexing_ntrkdiff_truthdv_rxy") 
	print2D( "RHad_all_recomatched_vertexing_truthdv_m_recodv_m") 
	print2D( "RHad_all_recomatched_vertexing_truthdv_ntrks_recodv_ntrks")
	print2D( "RHad_all_recomatched_vertexing_ntrkdiff_mdiff")

	print2D( "RHad_all_recomatched_both_mdiff_truthdv_rxy") 	
	print2D( "RHad_all_recomatched_both_ntrkdiff_truthdv_rxy") 
	print2D( "RHad_all_recomatched_both_truthdv_m_recodv_m") 
	print2D( "RHad_all_recomatched_both_truthdv_ntrks_recodv_ntrks")
	print2D( "RHad_all_recomatched_both_ntrkdiff_mdiff")

	return 

# setup
setStyle()


doDVEfficiency()
doMuonEfficiency()
do1Dcomparisons()
do2D()

#printHowWeDid()




