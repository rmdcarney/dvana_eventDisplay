#!usr/bin/env python
import ROOT
import sys
import math
from array import array
from plots import setStyle
from plots import get1DHisto
from plots import get2DHisto

f = ROOT.TFile.Open("histograms.root")

def rebin(name):
	if "LHTMET" in name : return 5
	if "ptvarcone" in name : return 2
	if "topoetcone" in name : return 2
	if "dv_chi2" in name: return 5
	if "dv_3trk_m" in name: return 5
	if "dv_3trk_r" in name: return 5
	if "dv_m" in name: return 5
	if "dv_r" in name: return 5
	if "dv_z" in name: return 5
	if "recodv_R" in name: return 2
	else : return False

def get_logy(name):
	if "dv_chi2"in name : return True
	if "dv_m"   in name : return True
	if "dv_3trk_m"  in name : return True
	if "dv_r"   in name : return True
	if "dv_nTracks" in name : return True
	if "dv_nLRT"   	in name : return True
	if "mu_d0"  	in name : return True
	if "mu_CBchi2"  in name : return True
	if "topoetcone" in name : return True
	if "ptvarcone"  in name : return True
	if "recodv_Rxy"  in name : return True
	return False

def drawATLASLogo(isSim=0):

	startx = 0.15
	starty = 0.87
	tex =  ROOT.TLatex(startx+0.05,starty,"ATLAS");
	tex.SetNDC();
	tex.SetTextFont(73);
	tex.SetTextSize(40);
	tex.Draw();

	if isSim:
		tex1 =  ROOT.TLatex(startx+0.22,starty,"Simulation Internal");
		tex1.SetNDC();
		tex1.SetTextFont(43);
		tex1.SetTextSize(40);
		tex1.Draw();
		tex2 =  ROOT.TLatex(0.77,0.95,"#tilde{t} #rightarrow b + #mu");
		tex2.SetNDC();
		tex2.SetTextFont(43);
		tex2.SetTextSize(35);
		tex2.Draw();
	else : 
		tex1 =  ROOT.TLatex(startx+0.22,starty,"Internal");
		tex1.SetNDC();
		tex1.SetTextFont(43);
		tex1.SetTextSize(40);
		tex1.Draw();

	return

def signal(hist):

	col = ROOT.kBlack
	#if  "1100_0p1ns" in hist.GetName() : col = ROOT.kAzure+1 
	if  "1100_1ns" 		in hist.GetName() : col = ROOT.kViolet+1 
	if  "1100_0p1ns"   	in hist.GetName() : col = ROOT.kRed+1 
	if  "1300_0p01ns"   in hist.GetName() : col = ROOT.kOrange+1 
	
	hist.SetLineColor(col)
	hist.SetMarkerColor(col)
	hist.SetLineWidth(3)	


	return hist


def signalLabel(hist):

	label = ""
	if  "1300_0p01ns" in hist.GetName() : label = "(m_{#tilde{t}}, #tau_{#tilde{t}}) = (1300 GeV, 0.01 ns)"
	if  "1000_0p01ns" in hist.GetName() : label = "(m_{#tilde{t}}, #tau_{#tilde{t}}) = (1000 GeV, 0.01 ns)"
	if  "1100_0p1ns"  in hist.GetName() : label = "(m_{#tilde{t}}, #tau_{#tilde{t}}) = (1100 GeV, 0.1 ns)"
	if  "1100_1ns"    in hist.GetName() : label = "(m_{#tilde{t}}, #tau_{#tilde{t}}) = (1100 GeV, 1 ns)"

	return label

def comparison(dist,scale=1):

	
	# 1 - 1100 0.1 ns
	# 2 - 1400 0.1 ns
	# 3 - 1400 1 ns
	hist1 = get1DHisto(f,"RHad_1300_0p01ns_"+dist)
	hist2 = get1DHisto(f,"RHad_1100_0p1ns_"+dist)
	hist3 = get1DHisto(f,"RHad_1100_1ns_"+dist)
	#hist4 = get1DHisto(f,"Stop_1400_1ns_"+dist)

	# setup canvas	
	canvas = ROOT.TCanvas("", "", 800, 900)
	canvas.Draw()
	canvas.cd()

	if (rebin(dist)):
		hist1.Rebin(rebin(dist))
		hist2.Rebin(rebin(dist))
		hist3.Rebin(rebin(dist))
		#hist4.Rebin(rebin(dist))

	if scale :
		hist1.Scale(1.0/hist1.Integral(0,-1))
		hist2.Scale(1.0/hist2.Integral(0,-1))
		hist3.Scale(1.0/hist3.Integral(0,-1))
		#hist4.Scale(1.0/hist4.Integral(0,-1))


	# draw histos 
	maximum = max(hist1.GetMaximum(),hist2.GetMaximum(),hist3.GetMaximum())
	#maximum = max(hist1.GetMaximum(),hist2.GetMaximum(),hist3.GetMaximum(),hist4.GetMaximum())
	if get_logy(dist):
		hist1.SetMaximum(100*maximum)
		#if "Muon" in file_name: hist1.SetMinimum(0.01)
		#if "MET"  in file_name: hist2.SetMinimum(0.1)
	else :
		hist1.SetMaximum(1.45*maximum)
		hist1.SetMinimum(0.)
	
	hist1 = signal(hist1)
	hist2 = signal(hist2) 
	hist3 = signal(hist3)  
	#hist4 = signal(hist4)  

	if "all_mu" in dist: hist1.GetYaxis().SetTitle("Muons [au]")
	if "DVs_dv" in dist: hist1.GetYaxis().SetTitle("DVs")
	if "PassPre_dv" in dist: hist1.GetYaxis().SetTitle("Preselected DVs [au]")
	if "PassPreNtrkMass_dv" in dist: hist1.GetYaxis().SetTitle("Fully selected DVs [au]")
	if "LHTMET" in dist: hist1.GetYaxis().SetTitle("events [au]")

	hist1.Draw("hist")
	hist2.Draw("hist same")
	hist3.Draw("hist same") 
	#hist4.Draw("hist same") 


	y = 0.71
	legend = ROOT.TLegend(0.20, y, 0.93, 0.91)
	legend.SetBorderSize(0)
	legend.SetFillColor(0)
	legend.SetTextSize(0.045)
	legend.AddEntry(hist1  ,signalLabel(hist1),"l") 
	legend.AddEntry(hist2  ,signalLabel(hist2),"l")  
	legend.AddEntry(hist3  ,signalLabel(hist3),"l")  
	#legend.AddEntry(hist4  ,signalLabel(hist4),"l")  
	legend.Draw()

	canvas.SetLogy(get_logy(dist))
	canvas.Print("Plots/SignalDists/Compare_"+dist+".png")
	canvas.SetLogy(0)
	canvas.Close()

	return 


def makePlots():

	dists = []
	dists.append("LHTMET")	
	dists.append("muons_all_mu_d0")	
	dists.append("muons_all_mu_z0")	
	dists.append("muons_all_mu_pt")	
	dists.append("muons_all_mu_ptzoom")	
	dists.append("muons_all_mu_ptunzoom")	
	dists.append("muons_all_mu_eta")	
	dists.append("muons_all_mu_QoverP")	
	dists.append("muons_all_mu_CBchi2")	
	dists.append("muons_all_mu_nPres")	
	dists.append("muons_all_mu_nPIX")	
	dists.append("muons_all_mu_nSCT")	
	dists.append("muons_all_mu_nTRT")	
	dists.append("muons_all_mu_ptvarcone30")	
	dists.append("muons_all_mu_topoetcone20")	
	dists.append("DVs_dv_m")	
	dists.append("DVs_dv_nTracks")	
	dists.append("DVs_dv_r")	
	dists.append("DVs_dv_rxy")
	dists.append("DVs_dv_z")	
	dists.append("DVs_dv_nDV")	
	dists.append("DVs_dv_chi2")	
	dists.append("PassPre_dv_nTracks")
	dists.append("PassPre_dv_nLRT")
	dists.append("PassPre_dv_m")
	dists.append("PassPre_dv_mzoom")
	dists.append("PassPreNtrkMass_dv_r")
	dists.append("PassPreNtrkMass_dv_rxy")
	dists.append("PassPreNtrkMass_dv_z")
	dists.append("DVs_dv_3trk_m")
	dists.append("DVs_dv_3trk_rxy")	
	#dists.append("truthmatched_recodv_m")
	#dists.append("truthmatched_recodv_ntrks")
	#dists.append("truthmatched_recodv_Rxy")
	#dists.append("truthmatched_recodv_R")

	for dist in dists:
		if "dv" in dist: comparison(dist,0)
		else : comparison(dist)


#main 
setStyle()
makePlots()