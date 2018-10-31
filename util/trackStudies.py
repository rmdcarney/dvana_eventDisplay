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
	if "unmatched_recodv"     in dist: label += "Unmatched Reco DV"
	if "truthmatched_recodv"  in dist: label += "Truth matched Reco DV"

	if "attachedTracks"    in dist: label += ", Attached Tracks"
	if "originalTracks"    in dist: label += ", Associated Tracks"

	return label 

def get_logy(hist):

	dist = hist.GetName()

	if "Trt" in dist: return 1
	if "Sct" in dist: return 1
	if "Pix" in dist: return 1
	if "pt" in dist: return 1
	if "truthMatchProb" in dist: return 1
	if "d0"  in dist: return 1


	return False

def clean1D(hist,color):
	
	hist.SetLineWidth(3)
	hist.SetLineColor(color)
	hist.SetMarkerColor(color)

	return

def rebin(hist):
	dist = hist.GetName()

	if "dvTracks_d0"  in dist: return 2
	if "eta" in dist: return 2
	if "phi" in dist: return 2
	if "pt" in dist: return 2

	return False

def compare1D(dist1, dist2, dist3, dist4):

	#print("")
	#print(dist1)
	#print(dist2)
	#print(dist3)
	#print(dist4)

	hist1 = get1DHisto(f,dist1)
	hist2 = get1DHisto(f,dist2)
	hist3 = get1DHisto(f,dist3)
	hist4 = get1DHisto(f,dist4)

	# setup canvas	
	canvas = ROOT.TCanvas("", "", 800, 900)
	canvas.Draw()
	canvas.cd()

	if rebin(hist1): 
		hist1.Rebin(2)
		hist2.Rebin(2)
		hist3.Rebin(2)
		hist4.Rebin(2)

	#scaling for now
	hist1.Scale(1.0/hist1.Integral(0,-1))
	hist2.Scale(1.0/hist2.Integral(0,-1))
	hist3.Scale(1.0/hist3.Integral(0,-1))
	hist4.Scale(1.0/hist4.Integral(0,-1))

	# draw histos 
	logy = get_logy(hist1)
	
	maximum = max(hist1.GetMaximum(),hist2.GetMaximum(),hist3.GetMaximum(),hist4.GetMaximum())
	hist1.SetMaximum(1.5*maximum)
	hist1.SetMinimum(0.)
	if logy : # since scaling
		hist1.SetMaximum(100)
		hist1.SetMinimum(0.001)
	
	clean1D(hist1, ROOT.kBlue+1)
	clean1D(hist2, ROOT.kViolet+1) 
	clean1D(hist3, ROOT.kRed+1) 
	clean1D(hist4, ROOT.kOrange+1) 

	hist1.Draw("hist")
	hist2.Draw("hist same")
	hist3.Draw("hist same")
	hist4.Draw("hist same")

	legend = ROOT.TLegend(0.17, 0.72, 0.84, 0.90)
	legend.SetBorderSize(0)
	legend.SetFillColor(0)
	legend.SetTextSize(0.035)
	legend.AddEntry(hist1  ,getlabel(hist1),"l") 
	legend.AddEntry(hist2  ,getlabel(hist2),"l")   
	legend.AddEntry(hist3  ,getlabel(hist3),"l")   
	legend.AddEntry(hist4  ,getlabel(hist4),"l")   
	legend.Draw()

	canvas.SetLogy(logy)
	canvas.Print("Plots/Tracks/"+dist1+".png")
	canvas.Close()
	canvas.SetLogy(0)
	return


# main

setStyle()

dists = []
dists.append("dvTracks_NPixDeadSens")	
dists.append("dvTracks_NPixHits")	
dists.append("dvTracks_NPixHoles")	
dists.append("dvTracks_NPixSharedHits")	
dists.append("dvTracks_NSctDeadSens")	
dists.append("dvTracks_NSctHits")	
dists.append("dvTracks_NSctHoles")	
dists.append("dvTracks_NSctSharedHits")	
dists.append("dvTracks_NTrtHits")	
dists.append("dvTracks_NTrtOutliers")	
dists.append("dvTracks_d0")	
dists.append("dvTracks_eta")	
dists.append("dvTracks_phi")	
dists.append("dvTracks_pt")	
dists.append("dvTracks_truthMatchProb")	
dists.append("dvTracks_truthOrigin")	
dists.append("dvTracks_truthType")	
dists.append("dvTracks_z0")
dists.append("dvTracks_absd0")
dists.append("dvTracks_absd0zoom")

sample = "RHad_all"

for dist in dists:
	sel1 = sample+"_truthmatched_recodv_originalTracks_"+dist
	sel2 = sample+"_truthmatched_recodv_attachedTracks_"+dist
	sel3 = sample+"_unmatched_recodv_originalTracks_"+dist
	sel4 = sample+"_unmatched_recodv_attachedTracks_"+dist

	compare1D(sel1, sel2, sel3, sel4)

# done
