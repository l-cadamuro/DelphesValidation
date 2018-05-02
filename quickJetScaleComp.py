import ROOT

ROOT.gStyle.SetOptStat(0)
ROOT.gROOT.SetBatch(True)

# fRed  = ROOT.TFile.Open('matchedJets_fullsim_TTbar_PU200.root')
# fBlue = ROOT.TFile.Open('matchedJets_fullsim_GG_HH_4B_PU200.root')

fRed  = ROOT.TFile.Open('matchedJets_fullsim_VBF_HH_4B_PU200.root')
fBlue = ROOT.TFile.Open('matchedJets_delphes_VBF_HH_4B_PU200.root')

# title = ';(p_{T}^{reco} - p_{T}^{gen}) / p_{T}^{gen}'
# title = ';reco jet #eta'
title = 'jet |#eta| > 3;reco jet #phi'
# maxEv = ROOT.TTree.kMaxEntries
maxEv = 1000000

legRed = 'FullSim'
legBlue = 'Delphes'

tRed  = fRed.Get('matchedJets')
tBlue = fBlue.Get('matchedJets')

tRed.SetLineColor(ROOT.kRed)
tBlue.SetLineColor(ROOT.kBlue)

# expr = '(jet_pt - genjet_pt) / genjet_pt'
# expr = 'jet_eta'
expr = 'jet_phi'
# cut  = 'jet_pt > 50 && jet_pt < 70 && abs(jet_eta) > 0.0 && abs(jet_eta) < 1.0 && jet_flav == 0'
# cut = 'jet_flav == 0'
# hbounds = '500, 0, 5'
# cut = 'abs(jet_eta) > 3.0'
cut = 'abs(jet_eta) > 3.0'
# cut = ''
# hbounds = '500, -2, 2'
# hbounds = '500, -5, 5'
hbounds = '500, -4, 4'

c1 = ROOT.TCanvas('c1', 'c1', 600, 600)
# c1.SetLogy()

tRed.Draw(expr + ' >> h(' + hbounds + ')', cut, '', maxEv)
hRed = ROOT.gDirectory.Get('h').Clone('hRed')

tBlue.Draw(expr + ' >> h(' + hbounds + ')', cut, '', maxEv)
hBlue = ROOT.gDirectory.Get('h').Clone('hBlue')

# hRed.DrawNormalized()
# hBlue.DrawNormalized('same')
hRed.Scale(1./hRed.Integral())
hBlue.Scale(1./hBlue.Integral())

##########

# ibRed = hRed.FindBin(3.0)
# ibBlue = hBlue.FindBin(3.0)

# print ibRed, ibBlue
# print "Red: ", hRed.Integral(ibRed, -1) / hRed.Integral(-1, -1)
# print "Blue: ", hBlue.Integral(ibBlue, -1) / hBlue.Integral(-1, -1)

# hRed.Rebin(10)
# hBlue.Rebin(10)

#############

mmax = max(hRed.GetMaximum(), hBlue.GetMaximum())
hRed.SetMaximum(1.15*mmax)

hRed.SetTitle(title)
hRed.SetLineWidth(2)
hBlue.SetLineWidth(2)

hRed.Draw('hist')
hBlue.Draw('hist same')

leg = ROOT.TLegend(0.6, 0.6, 0.88, 0.88)
leg.SetFillStyle(0)
leg.SetBorderSize(0)
leg.AddEntry(hRed, legRed)
leg.AddEntry(hBlue, legBlue)
leg.Draw()

c1.Update()
# raw_input()

c1.Print('comp.pdf', 'pdf')