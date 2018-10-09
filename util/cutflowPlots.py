#!usr/bin/env python
import ROOT
import sys
import math
from array import array
from plots import setStyle
from plots import get1DHisto
from plots import get2DHisto


f = ROOT.TFile.Open("histograms.root") # tmp
#f = ROOT.TFile.Open("histograms.root")


def lifetime(tau_string):
	if   tau_string=="0p01" : return 0.01
	elif tau_string=="0p1"  : return 0.1
	elif tau_string=="1"    : return 1
	elif tau_string=="10"   : return 10
	else 					: return int(tau_string)

def mass(mass_string):
	return int(mass_string)


def MUcutString(cut_int):
	if   cut_int == 1 : return "All"
	elif cut_int == 2 : return "hasPV"
	elif cut_int == 3 : return "PVz"
	elif cut_int == 4 : return "PVntrk"
	elif cut_int == 5 : return "MSonlyTrigger"
	elif cut_int == 6 : return "LHTlt180"
	elif cut_int == 7 : return "hasMuon"
	elif cut_int == 8 : return "passMuonTM"
	elif cut_int == 9 : return "MuonPt25"
	elif cut_int == 10: return "MuonEta2p5"
	elif cut_int == 11: return "MuonID"
	elif cut_int == 12: return "Muond0"
	elif cut_int == 13: return "Muonz0"
	elif cut_int == 14: return "MuonFakeVeto"
	elif cut_int == 15: return "MuonIsolation"
	elif cut_int == 16: return "MuonCosVeto"
	elif cut_int == 17: return "hasDV"
	elif cut_int == 18: return "DVfid"
	elif cut_int == 19: return "DVchi2"
	elif cut_int == 20: return "DVdist"
	elif cut_int == 21: return "DVmat"
	elif cut_int == 22: return "DVntrk3"
	elif cut_int == 23: return "DVmass10"
	elif cut_int == 24: return "DVmuon"
	else : return ""

def METcutString(cut_int):
	if   cut_int == 1 : return "All"
	elif cut_int == 2 : return "hasPV"
	elif cut_int == 3 : return "PVz"
	elif cut_int == 4 : return "PVntrk"
	elif cut_int == 5 : return "METtrigger"
	elif cut_int == 6 : return "LHTgt180"
	#elif cut_int == 7 : return "OfflineMET"
	elif cut_int == 7 : return "hasMuon"
	elif cut_int == 8 : return "MuonPt25"
	elif cut_int == 9 : return "MuonEta2p5"
	elif cut_int == 10: return "MuonID"
	elif cut_int == 11: return "Muond0"
	elif cut_int == 12: return "Muonz0"
	elif cut_int == 13: return "MuonFakeVeto"
	elif cut_int == 14: return "MuonIsolation"
	elif cut_int == 15: return "MuonCosVeto"
	elif cut_int == 16: return "hasDV"
	elif cut_int == 17: return "DVfid"
	elif cut_int == 18: return "DVchi2"
	elif cut_int == 19: return "DVdist"
	elif cut_int == 20: return "DVmat"
	elif cut_int == 21: return "DVntrk3"
	elif cut_int == 22: return "DVmass10"
	elif cut_int == 23: return "DVmuon"
	else : return ""

def plot_SR_efficiency():
	'''
	makes a 2D plot of MET efficiency as a function of mass and lifetime
	'''

	canvas = ROOT.TCanvas("c1", "c1", 800, 800)
	canvas.SetTopMargin(0.05)
	canvas.SetBottomMargin(0.13)
	canvas.SetLeftMargin(0.17)
	canvas.SetRightMargin(0.2)

	# old
	#mstops = ["1600", "1400", "1200", "1000", "800"]
	#taus   = ["0p01", "0p1", "1", "10"]
	# june 2018 samples
	mstops = ["1100", "1400", "1700"]
	taus = ["0p1", "1"]

	xbins = [0.05, 0.5, 5]
	nxbins = len(xbins)-1
	ybins = [950,1250,1550,1850]
	nybins = len(ybins)-1

	h_SRMET_eff = ROOT.TH2F("h_SRMET_eff",";#tau [ns];m_{#tilde{t}} [GeV];Signal Effiency",nxbins,array('d',xbins),nybins,array('d',ybins))
	h_SRMET_evt = ROOT.TH2F("h_SRMET_evt",";#tau [ns];m_{#tilde{t}} [GeV];Signal Events"  ,nxbins,array('d',xbins),nybins,array('d',ybins))

	h_SRMU_eff = ROOT.TH2F("h_SRMU_eff",";#tau [ns];m_{#tilde{t}} [GeV];Signal Effiency",nxbins,array('d',xbins),nybins,array('d',ybins))
	h_SRMU_evt = ROOT.TH2F("h_SRMU_evt",";#tau [ns];m_{#tilde{t}} [GeV];Signal Events"  ,nxbins,array('d',xbins),nybins,array('d',ybins))


	for mstop in mstops:
		for tau in taus:

			sample = "Stop_"+mstop+"_"+tau+"ns"
			h_met_sample = get1DHisto(f,sample+"_METSR_cutflow_wght")

			# last bin requires muon - link 
			# 2nd to last bin doesn't require link
			met_num = 0
			met_den = 1
			if (h_met_sample!=-1):
				met_num = h_met_sample.GetBinContent(h_met_sample.GetXaxis().GetNbins()-1)
				met_den = h_met_sample.GetBinContent(1)

			h_SRMET_evt.Fill(lifetime(tau),mass(mstop),met_num)
			h_SRMET_eff.Fill(lifetime(tau),mass(mstop),met_num/met_den)

			#print num,den,eff

			h_mu_sample = get1DHisto(f,sample+"_MuonSR_cutflow_wght")

			mu_num = 0
			mu_den = 1
			if (h_mu_sample!=-1):
				mu_num = h_mu_sample.GetBinContent(h_mu_sample.GetXaxis().GetNbins()-1)
				mu_den = h_mu_sample.GetBinContent(1)
	 
			h_SRMU_evt.Fill(lifetime(tau),mass(mstop),mu_num)
			h_SRMU_eff.Fill(lifetime(tau),mass(mstop),mu_num/mu_den)




	# Now print histos
	canvas.SetLogx(1)
	canvas.SetLogz(1)
	h_SRMET_evt.GetXaxis().SetTitleOffset(1.3)
	h_SRMET_evt.GetYaxis().SetTitleOffset(1.6)
	h_SRMET_evt.GetZaxis().SetTitleOffset(1.4)
	h_SRMET_evt.Draw("COLZ")
	h_SRMET_evt.Draw("TEXT same")
	canvas.Print("Plots/Cutflows/2D_SRMET_Events.png")

	canvas.SetLogz(0)
	h_SRMET_eff.GetXaxis().SetTitleOffset(1.3)
	h_SRMET_eff.GetYaxis().SetTitleOffset(1.6)
	h_SRMET_eff.GetZaxis().SetTitleOffset(1.5)
	h_SRMET_eff.Draw("COLZ")
	h_SRMET_eff.Draw("TEXT same")
	canvas.Print("Plots/Cutflows/2D_SRMET_Efficiency.png")
	canvas.SetLogx(0)


	canvas.SetLogx(1)
	canvas.SetLogz(1)
	h_SRMU_evt.GetXaxis().SetTitleOffset(1.3)
	h_SRMU_evt.GetYaxis().SetTitleOffset(1.6)
	h_SRMU_evt.GetZaxis().SetTitleOffset(1.4)
	h_SRMU_evt.Draw("COLZ")
	h_SRMU_evt.Draw("TEXT same")
	canvas.Print("Plots/Cutflows/2D_SRMU_Events.png")

	canvas.SetLogz(0)
	h_SRMU_eff.GetXaxis().SetTitleOffset(1.3)
	h_SRMU_eff.GetYaxis().SetTitleOffset(1.6)
	h_SRMU_eff.GetZaxis().SetTitleOffset(1.5)
	h_SRMU_eff.Draw("COLZ")
	h_SRMU_eff.Draw("TEXT same")
	canvas.Print("Plots/Cutflows/2D_SRMU_Efficiency.png")
	canvas.SetLogx(0)


	return 

def print_SRMET_efficiency(sample):

	'''
	Takes a sample and prints a table w/ the # of events passing each cut
	As well as the overall efficiency & relative efficiency of each cut
	'''

	h_sample = get1DHisto(f,sample+"_METSR_cutflow_wght")
	text_file = open("Plots/Cutflows/SR_MET_"+sample+".txt", "w")


	for bin in range(1,h_sample.GetXaxis().GetNbins()+1):

		nevts = h_sample.GetBinContent(bin)

		if nevts == 0: rel_eff = 0
		elif bin == 1: rel_eff = nevts/nevts
		else         : rel_eff = nevts/h_sample.GetBinContent(bin-1)

		tot_eff = nevts/h_sample.GetBinContent(1)

		if ("data" in sample) : text_file.write( "%s: 	%0.1f 	%0.2f 	%0.4f \n"%(METcutString(bin), nevts, rel_eff, tot_eff) )
		else: 					text_file.write( "%s: 	%0.1f 	%0.2f 	%0.2f \n"%(METcutString(bin), nevts, rel_eff, tot_eff) )

	text_file.close()

	return 

def print_SRMU_efficiency(sample):
	'''
	Takes a sample, and prints a table w/ the # of events passing each cut
	As well as the overall efficiency & relative efficiency of each cut
	'''

	h_sample = get1DHisto(f,sample+"_MuonSR_cutflow_wght")
	text_file = open("Plots/Cutflows/SRMU_"+sample+".txt", "w")


	for bin in range(1,h_sample.GetXaxis().GetNbins()+1):

		nevts = h_sample.GetBinContent(bin)

		if nevts == 0: rel_eff = 0
		elif bin == 1: rel_eff = nevts/nevts
		else         : rel_eff = nevts/h_sample.GetBinContent(bin-1)

		tot_eff = nevts/h_sample.GetBinContent(1)

		text_file.write( "%s: 	%0.1f 	%0.2f 	%0.2f \n"%(MUcutString(bin), nevts, rel_eff, tot_eff) )

	text_file.close()

	return 

def print_MuonCR_info(sample):
	'''
	Takes a sample, and prints a table w/ the # of events passing each cut
	'''

	h_cosmic_CR = get1DHisto(f,sample+"_MuonCosmicCR_cutflow_wght")
	h_fake_CR   = get1DHisto(f,sample+"_MuonFakeCR_cutflow_wght")
	h_heavy_CR  = get1DHisto(f,sample+"_MuonHeavyCR_cutflow_wght")
	h_muon_VR   = get1DHisto(f,sample+"_MuonVR_cutflow_wght")

	
	text_file = open("Plots/Cutflows/CRMU_"+sample+".txt", "w")

	# cut strings
	cut_strings = ["No DVs", "Mat 3 Track", "2 Track DVs", "3 Track LM", "3 Track HM"]

	# want the last five bins???
	text_file.write( "Selection: Cosmic  Fake  HeavyFlavor  Nominal \n" )
	for i, cut_string in enumerate(cut_strings):

		nbins = h_cosmic_CR.GetNbinsX()
		bin = nbins-4+i
		#print (bin, cut_string)
		n_cosmic  = h_cosmic_CR.GetBinContent(bin)
		n_fake    = h_fake_CR  .GetBinContent(bin)
		n_heavy   = h_heavy_CR .GetBinContent(bin)
		n_nominal = h_muon_VR  .GetBinContent(bin)


		text_file.write( "%s: 	%0.1f 	%0.1f 	%0.1f 	%0.1f \n"%(cut_string, n_cosmic, n_fake, n_heavy, n_nominal) )

	text_file.close()

	return 

def print_METCR_info(sample):
	'''
	Takes a sample, and prints a table w/ the # of events passing each cut
	'''

	h_cosmic_CR = get1DHisto(f,sample+"_METCosmicCR_cutflow_wght")
	h_fake_CR   = get1DHisto(f,sample+"_METFakeCR_cutflow_wght")
	h_heavy_CR  = get1DHisto(f,sample+"_METHeavyCR_cutflow_wght")
	h_muon_VR   = get1DHisto(f,sample+"_METVR_cutflow_wght")

	
	text_file = open("Plots/Cutflows/CRMET_"+sample+".txt", "w")

	# cut strings
	cut_strings = ["No DVs", "Mat 3 Track", "2 Track DVs", "3 Track LM", "3 Track HV"]

	# want the last five bins???
	text_file.write( "Selection: Cosmic  Fake  HeavyFlavor  Nominal \n" )
	for i, cut_string in enumerate(cut_strings):

		nbins = h_cosmic_CR.GetNbinsX()
		bin = nbins-4+i
		#print (bin, cut_string)
		n_cosmic  = h_cosmic_CR.GetBinContent(bin)
		n_fake    = h_fake_CR  .GetBinContent(bin)
		n_heavy   = h_heavy_CR .GetBinContent(bin)
		n_nominal = h_muon_VR  .GetBinContent(bin)


		text_file.write( "%s: 	%0.1f 	%0.1f 	%0.1f 	%0.1f \n"%(cut_string, n_cosmic, n_fake, n_heavy, n_nominal) )

	text_file.close()

	return 


def makeCutflows():
	'''
	Tries to make some cutflow stuffs

	'''


	plot_SR_efficiency()
	
	#print_SRMET_efficiency("data")
	#print_SRMU_efficiency("data")

	print_SRMET_efficiency("RHad_1000_0p01ns")
	print_SRMET_efficiency("RHad_1100_0p1ns")
	print_SRMET_efficiency("RHad_1100_1ns")
	#print_SRMET_efficiency("Stop_1700_1ns")
	#print_SRMET_efficiency("Stop_1400_0p1ns")
	#print_SRMET_efficiency("Stop_1400_1ns")
	#print_SRMET_efficiency("Stop_1100_0p1ns")
	#print_SRMET_efficiency("Stop_1100_1ns")
	#print_SRMET_efficiency("ttbar")
	#print_SRMET_efficiency("llvv")
	#print_SRMET_efficiency("JZ3W")

	print_SRMU_efficiency("RHad_1000_0p01ns")
	print_SRMU_efficiency("RHad_1100_0p1ns")
	print_SRMU_efficiency("RHad_1100_1ns")
	#print_SRMU_efficiency("Stop_1700_1ns")
	#print_SRMU_efficiency("Stop_1400_0p1ns")
	#print_SRMU_efficiency("Stop_1400_1ns")
	#print_SRMU_efficiency("Stop_1100_0p1ns")
	#print_SRMU_efficiency("Stop_1100_1ns")
	#print_SRMU_efficiency("ttbar")
	#print_SRMU_efficiency("llvv")
	#print_SRMU_efficiency("JZ3W")


	#print_MuonCR_info("data")
	#print_MuonCR_info("Stop_1100_1ns")
	#print_MuonCR_info("Stop_1400_1ns")
	#print_MuonCR_info("Stop_1400_0p1ns")
	#print_METCR_info("data")
	#print_METCR_info("Stop_1100_1ns")
	#print_METCR_info("Stop_1400_1ns")
	#print_METCR_info("Stop_1400_0p1ns")
	return

if __name__ == '__main__':

	setStyle()

	makeCutflows()
