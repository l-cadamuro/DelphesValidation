import ROOT

ROOT.gStyle.SetOptStat(0)
fIn = ROOT.TFile.Open('jet_response_maps_fullsim.root')

#hIn = fIn.Get('h_scale_bc')
#title = 'b jet scale; p_{T}^{reco} [GeV]; |#eta|'

hIn = fIn.Get('h_resol_bc')
title = 'b jet resolution; p_{T}^{reco} [GeV]; |#eta|'

hIn.GetXaxis().SetRangeUser(21, 180)

c1 = ROOT.TCanvas('c1', 'c1', 600, 600)
c1.SetLogx(True)
c1.SetRightMargin(0.15)

hIn.SetTitle(title)
hIn.Draw('colz')

c1.Update()
raw_input()
c1.Print(hIn.GetName()+'.pdf', 'pdf')
