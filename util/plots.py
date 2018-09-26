#!usr/bin/env python

import ROOT
from ROOT import gROOT, TCanvas, TH1F, THStack, TGraph, TStyle, TColor


def get_logy(filename):

	return False

def get1DHisto(f,histo_name):
	hist_tmp = f.Get(histo_name)
	if (hist_tmp):
		hist = hist_tmp.Clone()
		hist.GetXaxis().SetTitleSize(0.05)
		hist.GetXaxis().SetLabelSize(0.05)
		hist.GetYaxis().SetTitleSize(0.05)
		hist.GetYaxis().SetLabelSize(0.05)

		hist.GetXaxis().SetNdivisions(505)
		hist.GetYaxis().SetNdivisions(505)
		hist.GetZaxis().SetNdivisions(505)

		hist.SetFillColor(0)
		hist.SetLineWidth(2)

		hist_tmp=-1
		return hist

	else: 
		return -1

def get2DHisto(f,histo_name):
	hist_tmp = f.Get(histo_name)
	if (hist_tmp):
		hist = hist_tmp.Clone()
		hist.GetXaxis().SetTitleSize(0.05)
		hist.GetXaxis().SetLabelSize(0.05)
		hist.GetYaxis().SetTitleSize(0.05)
		hist.GetYaxis().SetLabelSize(0.05)
		hist.GetZaxis().SetTitleSize(0.05)
		hist.GetZaxis().SetLabelSize(0.05)
		hist_tmp=-1
		return hist

	else: 
		return -1



def setStyle():

	ROOT.gROOT.SetBatch(True)
	
	icol=0 # WHITE
	ROOT.gStyle.SetFrameBorderMode(icol)
	ROOT.gStyle.SetFrameFillColor(icol)
	ROOT.gStyle.SetCanvasBorderMode(icol)
	ROOT.gStyle.SetCanvasColor(icol)
	ROOT.gStyle.SetPadBorderMode(icol)
	ROOT.gStyle.SetPadColor(icol)
	ROOT.gStyle.SetStatColor(icol)
	
	# set the paper & margin sizes
	ROOT.gStyle.SetPaperSize(20,26)
	
	# set margin sizes
	ROOT.gStyle.SetPadTopMargin(0.07)
	ROOT.gStyle.SetPadRightMargin(0.05)
	ROOT.gStyle.SetPadBottomMargin(0.16)
	ROOT.gStyle.SetPadLeftMargin(0.16)
	
	# set title offsets (for axis label)
	ROOT.gStyle.SetTitleXOffset(1.6)
	ROOT.gStyle.SetTitleYOffset(1.6)

	ROOT.gStyle.SetPadTickX(True)
	ROOT.gStyle.SetPadTickY(True)
	
	# use large fonts
	#Int_t font=72; // Helvetica italics
	font=42 # Helvetica
	tsize=0.05
	ROOT.gStyle.SetTextFont(font)
	
	ROOT.gStyle.SetTextSize(tsize)
	ROOT.gStyle.SetLabelFont(font,"x")
	ROOT.gStyle.SetTitleFont(font,"x")
	ROOT.gStyle.SetLabelFont(font,"y")
	ROOT.gStyle.SetTitleFont(font,"y")
	ROOT.gStyle.SetLabelFont(font,"z")
	ROOT.gStyle.SetTitleFont(font,"z")
	
	ROOT.gStyle.SetLabelSize(tsize,"x")
	ROOT.gStyle.SetTitleSize(tsize,"x")
	ROOT.gStyle.SetLabelSize(tsize,"y")
	ROOT.gStyle.SetTitleSize(tsize,"y")
	ROOT.gStyle.SetLabelSize(tsize,"z")
	ROOT.gStyle.SetTitleSize(tsize,"z")
	
	# use bold lines and markers
	ROOT.gStyle.SetMarkerStyle(20)
	ROOT.gStyle.SetMarkerSize(1.2)

	ROOT.gStyle.SetOptStat(0)

	return