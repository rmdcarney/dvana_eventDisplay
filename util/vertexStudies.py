#!usr/bin/env python
import ROOT
import sys
import math
from array import array
from plots import setStyle
from plots import get1DHisto
from plots import get2DHisto

f = ROOT.TFile.Open("histograms.root")
fout = ROOT.TFile.Open("Plots/maps/SegmentMaps.root","RECREATE")

def getlabel(hist):
	dist = hist.GetName()
	
	if   "truthmatched"  in dist: return "Truth Matched DV"
	if   "unmatched" 	 in dist: return "Unmatched DV"
	#elif "BM"  in dist and "2016" in dist : return "MS Middle Barrel 2016"
	#elif "BM"  in dist and "2017" in dist : return "MS Middle Barrel 2017"
	#elif "BO"  in dist: return "MS Outer Barrel"
	#elif "ALL" in dist: return "MS Barrel"
#
	#elif "Loosematched" 			in dist: return "Fail Cosmic Veto"
	#elif "Looseunmatched_passaccep" in dist: return "Pass Cosmic Veto - Pass Acceptance"
	#elif "Looseunmatched_failaccep" in dist: return "Pass Cosmic Veto - Fail Acceptance"
	#elif "Looseunmatched" 			in dist: return "Pass Cosmic Veto"

	return ""
def rebin(dist):
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

def compare1D(dist1, dist2):

	# 1 - 1100 0.1 ns
	# 2 - 1400 0.1 ns
	# 3 - 1400 1 ns
	hist1 = get1DHisto(f,dist1)
	hist2 = get1DHisto(f,dist2)

	# setup canvas	
	canvas = ROOT.TCanvas("", "", 800, 900)
	canvas.Draw()
	canvas.cd()

	hist1.Rebin(5)
	hist2.Rebin(5)

	# draw histos 
	maximum = max(hist1.GetMaximum(),hist2.GetMaximum())
	hist1.SetMaximum(1.45*maximum)
	hist1.SetMinimum(0.)
	
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
	legend.SetTextSize(0.04)
	legend.AddEntry(hist1  ,getlabel(hist1),"l") 
	legend.AddEntry(hist2  ,getlabel(hist2),"l")   
	legend.Draw()

	canvas.SetLogy(0)
	canvas.Print("Plots/Compare_"+dist1+".png")
	canvas.Close()
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

	canvas.Print("Plots/maps/2D_"+dist+".png")
	canvas.Close()

	return 


def drawR():

	# setup canvas	
	canvas = ROOT.TCanvas("", "", 900, 800)
	canvas.SetTopMargin(0.09)
	canvas.SetBottomMargin(0.15)
	canvas.SetLeftMargin(0.2)
	canvas.SetRightMargin(0.09)
	canvas.Draw()
	canvas.cd()
	#canvas.SetLogz(1)

	# get histograms
	hist_BI_2016 = get1DHisto(f,"BI_2016_seg_r")	
	hist_BI_2017 = get1DHisto(f,"BI_2017_seg_r")	
	hist_BM_2016 = get1DHisto(f,"BM_2016_seg_r")	
	hist_BM_2017 = get1DHisto(f,"BM_2017_seg_r")	
	hist_BO_2016 = get1DHisto(f,"BO_2016_seg_r")	
	hist_BO_2017 = get1DHisto(f,"BO_2017_seg_r")

	hist_BI = hist_BI_2016.Clone("BI_seg_r")
	hist_BM = hist_BM_2016.Clone("BM_seg_r")
	hist_BO = hist_BO_2016.Clone("BO_seg_r")
	hist_BI.Add(hist_BI_2017)
	hist_BM.Add(hist_BM_2017)
	hist_BO.Add(hist_BO_2017)

	hist_BI.SetLineWidth(3)
	hist_BM.SetLineWidth(3)
	hist_BO.SetLineWidth(3)
	hist_BI.SetLineColor(ROOT.kAzure+1)
	hist_BM.SetLineColor(ROOT.kViolet+1)
	hist_BO.SetLineColor(ROOT.kOrange+1 )
	hist_BI.SetMarkerColor(ROOT.kAzure+1)
	hist_BM.SetMarkerColor(ROOT.kViolet+1)
	hist_BO.SetMarkerColor(ROOT.kOrange+1)

	hist_BI.GetYaxis().SetRangeUser(0,1200000)
	hist_BI.GetXaxis().SetRangeUser(0,20000)
	hist_BI.GetXaxis().SetTitle("segment R [mm]")
	hist_BI.GetXaxis().SetTitleOffset(1.3)

	hist_BI.Draw("hist")
	hist_BM.Draw("hist same")
	hist_BO.Draw("hist same")

	avg_BI = str(round(hist_BI.GetMean()))
	avg_BM = str(round(hist_BM.GetMean()))
	avg_BO = str(round(hist_BO.GetMean()))

	legend = ROOT.TLegend(0.22, 0.71, 0.90, 0.89)
	legend.SetBorderSize(0)
	legend.SetFillColor(0)
	legend.SetTextSize(0.045)
	legend.AddEntry(hist_BI  ,"Inner Barrel : R = "+avg_BI+" mm" ,"l") 
	legend.AddEntry(hist_BM  ,"Middle Barrel : R = "+avg_BM+" mm" ,"l") 
	legend.AddEntry(hist_BO  ,"Outer Barrel : R = "+avg_BO+" mm" ,"l") 
	legend.Draw()

	canvas.Print("Plots/maps/Average_Segment_R.png")
	canvas.Close()

	return 
def makeMap(station,year=2016):

	# get histogram of interest
	if station == "BI": 
		hist_2016 = get2DHisto(f,"BI_2016_seg_eta_phi")
		hist_2017 = get2DHisto(f,"BI_2017_seg_eta_phi")
		hist = hist_2016.Clone("BI_seg_eta_phi")
		hist.Add(hist_2017)
		dist = "BI"
	elif station == "BM" and year == 2016:
		hist = get1DHisto(f,"BM_2016_seg_eta_phi")
		dist = "BM_2016"
	elif station == "BM" and year == 2017:
		hist = get1DHisto(f,"BM_2017_seg_eta_phi")
		dist = "BM_2017"
	else : # station is "BO" 
		hist_2016 = get2DHisto(f,"BO_2016_seg_eta_phi")
		hist_2017 = get2DHisto(f,"BO_2017_seg_eta_phi")
		hist = hist_2016.Clone("BO_seg_eta_phi")
		hist.Add(hist_2017)
		dist = "BO"

	# clone for map version before rebinning
	hist_map = hist.Clone(dist+"_map")

	# setup canvas	
	canvas = ROOT.TCanvas("", "", 900, 800)
	canvas.SetTopMargin(0.09)
	canvas.SetBottomMargin(0.13)
	canvas.SetLeftMargin(0.1)
	canvas.SetRightMargin(0.25)
	canvas.Draw()
	canvas.cd()
	canvas.SetLogz(1)

	# scale and draw
	clean2D(hist,1)
	hist.GetZaxis().SetTitle("segments [au]")
	hist.Draw("COLZ")

	text =  ROOT.TLatex(0.11,0.92,getlabel(hist));
	text.SetNDC();
	text.SetTextFont(43);
	text.SetTextSize(35);
	text.Draw();

	# save original histogram 
	fout.cd()
	hist.Write()

	canvas.Print("Plots/maps/"+dist+".png")
	canvas.Print("Plots/maps/"+dist+".png")

	# now we finally make our map
	canvas.SetLogz(0)
	if "BM" in dist: hist_map.RebinY(5)
	else 		   : hist_map.RebinY(10)

	# and now convert to 1s and 0s
	for x in range(0,hist_map.GetNbinsX()+1):
		for y in range(0,hist_map.GetNbinsY()+1):
			if hist_map.GetBinContent(x,y)>5 : hist_map.SetBinContent(x,y,1)
			else							 : hist_map.SetBinContent(x,y,0)

	# some cleaning before drawing 
	clean2D(hist_map)
	hist_map.GetZaxis().SetRangeUser(0,2)
	hist_map.GetZaxis().SetTitle("segment map")
	hist_map.GetZaxis().SetTitleOffset(1.6)
	hist_map.Draw("COLZ")
	# and all the saveing
	text.Draw();
	fout.cd()
	hist_map.Write() # save final histogram
	canvas.Print("Plots/maps/"+dist+"_map.png")

	canvas.Close()

	return 

def optimizeSumEtaDeltaPhi():

	signal = get2DHisto(f,"Stop_Signals_ALL_min_sumEtaCorr_dPhi")
	cosmic = get2DHisto(f,"data_ALL_min_sumEtaCorr_dPhi")

	signal_eff = signal.Clone("Signal_sumEtaCorr_dPhi_efficiency")
	cosmic_eff = cosmic.Clone("Cosmic_sumEtaCorr_dPhi_efficiency")
	s_over_b = signal_eff.Clone("2D_sumEtaCorr_dPhi_SoverB")

	# compute denominator
	denom_sig = signal.Integral(0,signal.GetNbinsX()+1,0,signal.GetNbinsY()+1)
	denom_cos = cosmic.Integral(0,signal.GetNbinsX()+1,0,signal.GetNbinsY()+1)
	for binx in range(1,signal.GetNbinsX()+1):
		for biny in range(1,signal.GetNbinsY()+1):

			# Compute 
			num_sig = signal.Integral(0,binx,0,biny)
			num_cos = cosmic.Integral(0,binx,0,biny)
			if num_cos/denom_cos != 1.0:
				s_o_b = (1.0-num_sig/denom_sig)/(1.0-num_cos/denom_cos)
			else : 
				s_o_b = 0

			signal_eff.SetBinContent(binx,biny,num_sig/denom_sig)
			cosmic_eff.SetBinContent(binx,biny,num_cos/denom_cos)
			s_over_b.SetBinContent(binx,biny,s_o_b)

			# print eff if worth knowing

	# setup canvas	
	canvas = ROOT.TCanvas("", "", 900, 800)
	canvas.SetTopMargin(0.09)
	canvas.SetBottomMargin(0.13)
	canvas.SetLeftMargin(0.14)
	canvas.SetRightMargin(0.18)
	canvas.Draw()
	canvas.cd()
	#canvas.SetLogz(1)

	# scale and draw
	clean2D(signal_eff)
	clean2D(cosmic_eff)
	clean2D(s_over_b)
	signal_eff.GetYaxis().SetTitle("#Delta#phi_{mu,seg} - #pi")
	signal_eff.GetXaxis().SetTitle("#eta_{mu} corr. + #eta_{seg}")
	signal_eff.GetZaxis().SetTitle("signal reject.")
	cosmic_eff.GetYaxis().SetTitle("#Delta#phi_{mu,seg} - #pi")
	cosmic_eff.GetXaxis().SetTitle("#eta_{mu} corr. + #eta_{seg}")	
	cosmic_eff.GetZaxis().SetTitle("cosmic reject.")
	s_over_b.GetYaxis().SetTitle("#Delta#phi_{mu,seg} - #pi")
	s_over_b.GetXaxis().SetTitle("#eta_{mu} corr. + #eta_{seg}")	
	s_over_b.GetZaxis().SetTitle("S/B")


	signal_eff.GetYaxis().SetTitleOffset(1.2)
	cosmic_eff.GetYaxis().SetTitleOffset(1.2)
	s_over_b  .GetYaxis().SetTitleOffset(1.2)
	signal_eff.GetZaxis().SetTitleOffset(1.3)
	cosmic_eff.GetZaxis().SetTitleOffset(1.3)
	s_over_b  .GetZaxis().SetTitleOffset(1.3)

	signal_eff.GetXaxis().SetRangeUser(0.0,0.3)
	cosmic_eff.GetXaxis().SetRangeUser(0.0,0.3)
	s_over_b  .GetXaxis().SetRangeUser(0.0,0.3)
	signal_eff.GetYaxis().SetRangeUser(0.0,0.3)
	cosmic_eff.GetYaxis().SetRangeUser(0.0,0.3)
	s_over_b  .GetYaxis().SetRangeUser(0.0,0.3)
	signal_eff.GetZaxis().SetRangeUser(0.0,0.2)
	cosmic_eff.GetZaxis().SetRangeUser(0.8,1.0)
	

	#text =  ROOT.TLatex(0.11,0.92,getlabel(hist));
	#text.SetNDC();
	#text.SetTextFont(43);
	#text.SetTextSize(35);
	#text.Draw();

	#save
	fout.cd()
	signal_eff.Write()
	cosmic_eff.Write()
	s_over_b.Write()

	signal_eff.Draw("COLZ")
	canvas.Print("Plots/maps/2D_sumEtaCorr_dPhi_signal_efficiency.png")

	cosmic_eff.Draw("COLZ")
	canvas.Print("Plots/maps/2D_sumEtaCorr_dPhi_cosmic_efficiency.png")

	s_over_b.Draw("COLZ")
	canvas.Print("Plots/maps/2D_sumEtaCorr_dPhi_soverb.png")

	canvas.SetLogz(0)
	canvas.Close()

	#working points to test
	etas = [0.025,0.05,0.075]
	phis = [0.18,0.2,0.22]

	sig_vals = []
	cos_vals = []
	for eta in etas:

		sig_vals_eta = []
		cos_vals_eta = []
		for phi in phis: 
			
			binx = signal.GetXaxis().FindBin(eta);
			biny = signal.GetYaxis().FindBin(phi);	

			sig_vals_eta.append( signal_eff.GetBinContent(binx,biny ) )
			cos_vals_eta.append( cosmic_eff.GetBinContent(binx,biny ) )
			
			print (binx,signal_eff.GetXaxis().GetBinLowEdge(binx),signal_eff.GetXaxis().GetBinLowEdge(binx)+signal_eff.GetXaxis().GetBinWidth(binx))
			print (biny,signal_eff.GetYaxis().GetBinLowEdge(biny),signal_eff.GetYaxis().GetBinLowEdge(biny)+signal_eff.GetYaxis().GetBinWidth(biny))

		sig_vals.append(sig_vals_eta)
		cos_vals.append(cos_vals_eta)
	
	print ("")		
	print ("%0.3f %0.3f %0.3f"%(sig_vals[0][0],sig_vals[1][0],sig_vals[2][0] ))
	print ("%0.3f %0.3f %0.3f"%(sig_vals[0][1],sig_vals[1][1],sig_vals[2][1] ))	
	print ("%0.3f %0.3f %0.3f"%(sig_vals[0][2],sig_vals[1][2],sig_vals[2][2] ))	
	print ("")
	print ("%0.3f %0.3f %0.3f"%(cos_vals[0][0],cos_vals[1][0],cos_vals[2][0] ))
	print ("%0.3f %0.3f %0.3f"%(cos_vals[0][1],cos_vals[1][1],cos_vals[2][1] ))	
	print ("%0.3f %0.3f %0.3f"%(cos_vals[0][2],cos_vals[1][2],cos_vals[2][2] ))	

	return

def optimizeDeltaR():

	signal = get1DHisto(f,"Stop_Signals_ALL_min_Rcos")
	cosmic = get1DHisto(f,"data_ALL_min_Rcos")

	signal_eff = signal.Clone("Signal_min_Rcos")
	cosmic_eff = cosmic.Clone("data_min_Rcos")

	# compute denominator
	denom_sig = signal.Integral(0,signal.GetNbinsX()+1)
	denom_cos = cosmic.Integral(0,signal.GetNbinsX()+1)
	for binx in range(1,signal.GetNbinsX()+1):

		# Compute numerator
		num_sig = signal.Integral(0,binx)
		num_cos = cosmic.Integral(0,binx)

		# compute efficiency
		signal_eff.SetBinContent(binx,num_sig/denom_sig)
		cosmic_eff.SetBinContent(binx,num_cos/denom_cos)
		signal_eff.SetBinError(binx,0)
		cosmic_eff.SetBinError(binx,0)
		# print eff if worth knowing

	# setup canvas	
	canvas = ROOT.TCanvas("", "", 900, 800)
	canvas.SetTopMargin(0.09)
	canvas.SetBottomMargin(0.13)
	canvas.SetLeftMargin(0.1)
	canvas.SetRightMargin(0.25)
	canvas.Draw()
	canvas.cd()
	#canvas.SetLogz(1)

	# scale and draw
	s_over_b = signal_eff.Clone("1D_min_Rcos_soverb")
	s_over_b.Divide(cosmic_eff)

	clean1D(signal_eff)
	clean1D(cosmic_eff)
	clean1D(s_over_b)

	signal_eff.GetYaxis().SetTitle("signal reject.")
	cosmic_eff.GetYaxis().SetTitle("cosmic reject.")
	signal_eff.GetYaxis().SetRangeUser(0,1.0)
	cosmic_eff.GetYaxis().SetRangeUser(0,1.0)
	s_over_b.GetYaxis().SetTitle("S/B")


	
	#text =  ROOT.TLatex(0.11,0.92,getlabel(hist));
	#text.SetNDC();
	#text.SetTextFont(43);
	#text.SetTextSize(35);
	#text.Draw();

	#save
	fout.cd()
	signal_eff.Write()
	cosmic_eff.Write()
	s_over_b.Write()

	signal_eff.Draw("COLZ")
	canvas.Print("Plots/maps/1D_min_Rcos_signal_efficiency.png")

	cosmic_eff.Draw("COLZ")
	canvas.Print("Plots/maps/1D_min_Rcos_cosmic_efficiency.png")

	s_over_b.Draw("COLZ")
	canvas.Print("Plots/maps/1D_min_Rcos_soverb.png")

	canvas.SetLogz(0)
	canvas.Close()

	#working points to test
	dRs = [0.16,0.18,0.2]

	sig_vals = []
	cos_vals = []

	for dR in dRs: 
		
		binx = signal.GetXaxis().FindBin(dR);

		sig_vals.append( signal_eff.GetBinContent(binx ) )
		cos_vals.append( cosmic_eff.GetBinContent(binx ) )
		
		print (binx, dR)
	
	print ("")		
	print ("%0.3f %0.3f %0.3f"%(sig_vals[0],sig_vals[1],sig_vals[2] ))
	print ("")
	print ("%0.3f %0.3f %0.3f"%(cos_vals[0],cos_vals[1],cos_vals[2] ))

def printHowWeDid():

	# for cosmics
	hist_den_orig  = get2DHisto(f,"data_Tightmatched_eta_phi")
	hist_nom_orig  = get2DHisto(f,"data_Tightunmatched_eta_phi")
	hist_nom_box   = get2DHisto(f,"data_Looseunmatched_eta_phi")
	hist_nom_final = get2DHisto(f,"data_Looseunmatched_passaccep_eta_phi")

	den_orig = hist_den_orig.Integral(0,-1,0,-1) 
	nom_orig = hist_nom_orig.Integral(0,-1,0,-1) 
	nom_box  = hist_nom_box.Integral(0,-1,0,-1)  
	nom_final= hist_nom_final.Integral(0,-1,0,-1)
	den_orig += nom_orig

	# print 
	print("Cosmic Transfer Factors")
	print("%.3f"%(nom_orig/den_orig)) 
	print("%.3f"%(nom_box/den_orig))  
	print("%.3f"%(nom_final/den_orig))

	# for signal
	hist_den_orig  = get2DHisto(f,"Stop_Signals_Tightmatched_eta_phi")
	hist_nom_orig  = get2DHisto(f,"Stop_Signals_Tightunmatched_eta_phi")
	hist_nom_box   = get2DHisto(f,"Stop_Signals_Looseunmatched_eta_phi")
	hist_nom_final = get2DHisto(f,"Stop_Signals_Looseunmatched_passaccep_eta_phi")

	den_orig = hist_den_orig.Integral(0,-1,0,-1) 
	nom_orig = hist_nom_orig.Integral(0,-1,0,-1) 
	nom_box  = hist_nom_box.Integral(0,-1,0,-1)  
	nom_final= hist_nom_final.Integral(0,-1,0,-1)
	den_orig += nom_orig

	# print 
	print("Signal Efficiency")
	print("%.3f"%(nom_orig/den_orig)) 
	print("%.3f"%(nom_box/den_orig))  
	print("%.3f"%(nom_final/den_orig))

	return 

# setup
setStyle()

# show effect of eta correction 
#print2D("data_BI_min_sumEtaCorr_dPhi")
#print2D("data_BI_min_sumEta_dPhi")
#
## and plots for optimizing new cut
#print2D("Stop_Signals_ALL_min_sumEtaCorr_dPhi")
#print2D("Stop_Signals_ALL_min_sumEta_dPhi")
#print2D("data_ALL_min_sumEtaCorr_dPhi")
#print2D("data_ALL_min_sumEta_dPhi")
#
## make maps
#makeMap("BI")
#makeMap("BM",2016)
#makeMap("BM",2017)
#makeMap("BO")
#
## optimize
#optimizeSumEtaDeltaPhi()
#optimizeDeltaR()
#
##get average R values for Inner/Middle/Outer Stations
#drawR()
#
##Test new acceptance cuts
#print2D("data_Loosematched_eta_phi")
#print2D("data_Looseunmatched_eta_phi")
#print2D("data_Looseunmatched_failaccep_eta_phi")
#print2D("data_Looseunmatched_passaccep_eta_phi")

compare1D("MC_unmatched_recodv_Rxy"		,"MC_truthmatched_recodv_Rxy")
compare1D("MC_unmatched_recodv_R"		,"MC_truthmatched_recodv_R")
compare1D("MC_unmatched_recodv_m"		,"MC_truthmatched_recodv_m")
compare1D("MC_unmatched_recodv_mbig"	,"MC_truthmatched_recodv_mbig")
compare1D("MC_unmatched_recodv_ntrks"	,"MC_truthmatched_recodv_ntrks")
compare1D("MC_unmatched_recodv_ntrksbig","MC_truthmatched_recodv_ntrksbig")

#printHowWeDid()