import ROOT
import argparse
import sys
import array

# def graphToHisto(gr, hname, htitle, useMaxErr = True):
    
#     x_points = []
#     y_points = []
#     ex_l_points = []
#     ey_l_points = []
#     ex_h_points = []
#     ey_h_points = []
#     for ipt in range (0, gr.GetN()):
#         x = ROOT.Double(0.0)
#         y = ROOT.Double(0.0)
#         gr.GetPoint(ipt, x, y)
#         x_points.append(float(x))
#         y_points.append(float(y))
#         ex_l = gr.GetErrorXlow(ipt)
#         ey_l = gr.GetErrorYlow(ipt)
#         ex_h = gr.GetErrorXhigh(ipt)
#         ey_h = gr.GetErrorYhigh(ipt)
#         ex_l_points.append(ex_l)
#         ey_l_points.append(ey_l)
#         ex_h_points.append(ex_h)
#         ey_h_points.append(ey_h)
    
#     ## create the binning
#     binning = []
#     for ipt in range(0, len(x_points)):
#         binning.append(x_points[ipt] - ex_l_points[ipt])
#     binning.append(x_points[ipt] + ex_h_points[ipt])
#     bins = array.array('d', binning)
#     h = ROOT.TH1D(hname, htitle, len(binning)-1, bins)

#     for ipt in range(0, len(x_points)):
#         h.SetBinContent(ipt+1, y_points[ipt])
#         err = max (ey_l_points[ipt], ey_h_points[ipt]) if useMaxErr else min (ey_l_points[ipt], ey_h_points[ipt])
#         h.SetBinError(ipt+1, err)

#     return h

def toHistoForRatio (teff):
    hpass = teff.GetCopyPassedHisto()
    htot  = teff.GetCopyTotalHisto()
    hpass.Sumw2()
    htot.Sumw2()
    hratio = hpass.Clone(hpass.GetName() + '_eff')
    hratio.Divide(htot)
    hratio.SetLineColor(teff.GetLineColor())
    hratio.SetMarkerColor(teff.GetMarkerColor())
    hratio.SetMarkerStyle(teff.GetMarkerStyle())
    hratio.SetMarkerSize(teff.GetMarkerSize())
    return hratio

parser = argparse.ArgumentParser(description='Command line parser of plotting options')

parser.add_argument('--var',  dest='var', help='variable name', required=True)
parser.add_argument('--PU',   dest='PU', help='pileup scenario (0 or 200)', required=True)
parser.add_argument('--norm', dest='norm', help='normalization mode (none, max, int)', default='int')
parser.add_argument('--log',  dest='log', help='y log scale', action='store_true', default=False)
parser.add_argument('--ratio', dest='ratio', help='make ratio plot', default=False, action='store_true')
parser.add_argument('--rymin', dest='rymin', help='min y in ratio plot', default=None, type=float)
parser.add_argument('--rymax', dest='rymax', help='max y in ratio plot', default=None, type=float)
parser.add_argument('--ymin', dest='ymin', help='min y in main plot', default=None, type=float)
parser.add_argument('--ymax', dest='ymax', help='max y in main plot', default=None, type=float)
parser.add_argument('--sample', dest='sample', help='sample name', default="TTbar")
parser.add_argument('--rebin', dest='rebin', help='rebin factor', default=None)
parser.add_argument('--quit', dest='quit', help = 'quit at the end of the script, no interactive window', action='store_true', default=False)

args = parser.parse_args()

if args.quit : ROOT.gROOT.SetBatch(True)
ROOT.gStyle.SetOptStat(0)

fIn_fullsim = ROOT.TFile.Open('jethistos_fullsim_%s_PU%s.root' % (args.sample, args.PU))
fIn_delphes = ROOT.TFile.Open('jethistos_delphes_%s_PU%s.root' % (args.sample, args.PU))

vname = args.var
if not vname.startswith('h_'):
    vname = 'h_' + vname

print "... opening ", fIn_fullsim.GetName()
print "... opening ", fIn_delphes.GetName()
print '... getting histos', vname

if not fIn_fullsim.GetListOfKeys().Contains(vname) or not fIn_delphes.GetListOfKeys().Contains(vname):
    print '... file(s) do not contain this histo'
    sys.exit()

hIn_fullsim = fIn_fullsim.Get(vname)
hIn_delphes = fIn_delphes.Get(vname)

is_efficiency = True if isinstance(hIn_fullsim, ROOT.TEfficiency) else False

c1 = ROOT.TCanvas('c1', 'c1', 600, 600)
c1.SetFrameLineWidth(3)
if args.log:
    c1.SetLogy(True)

if not is_efficiency:
    hIn_fullsim.Sumw2()
    hIn_delphes.Sumw2()

if not is_efficiency and args.rebin:
    hIn_fullsim.Rebin(int(args.rebin))
    hIn_delphes.Rebin(int(args.rebin))

## scale, depending on the normalization mode
if not is_efficiency:
    if args.norm == 'none':
        pass
    elif args.norm == 'int':
        hIn_fullsim.Scale(1./hIn_fullsim.Integral())
        hIn_delphes.Scale(1./hIn_delphes.Integral())
    elif args.norm == 'max':
        hIn_fullsim.Scale(1./hIn_fullsim.GetMaximum())
        hIn_delphes.Scale(1./hIn_delphes.GetMaximum())

hIn_fullsim.SetLineColor(ROOT.kRed)
hIn_fullsim.SetMarkerStyle(8)
hIn_fullsim.SetMarkerSize(0.4)
hIn_fullsim.SetMarkerColor(hIn_fullsim.GetLineColor())
hIn_delphes.SetLineColor(ROOT.kBlue)
hIn_delphes.SetMarkerStyle(8)
hIn_delphes.SetMarkerSize(0.4)
hIn_delphes.SetMarkerColor(hIn_delphes.GetLineColor())

ymin, ymax = None, None

if not is_efficiency:
    themax = max(hIn_fullsim.GetMaximum(), hIn_delphes.GetMaximum())
    hIn_fullsim.SetMaximum(1.15*themax)
    ymin, ymax = hIn_fullsim.GetMinimum(), hIn_fullsim.GetMaximum()
    if args.log:
        ymin = 1.e-5

if args.ymin:
    ymin = args.ymin
if args.ymax:
    ymax = args.ymax

if not args.ratio:
    if is_efficiency:
        hIn_fullsim.Draw('ap')
        hIn_delphes.Draw('psame')
    else:
        hIn_fullsim.Draw('pl')
        hIn_delphes.Draw('plsame')
    leg = ROOT.TLegend(0.11, 0.9, 0.88, 0.95)
    text = ROOT.TLatex(0.77, 0.85, "PU " + args.PU)
else:
    
    if not is_efficiency:
        trplot = ROOT.TRatioPlot(hIn_delphes, hIn_fullsim)
    else:
        # hIn_delphes_cp = graphToHisto(hIn_delphes.CreateGraph(), 'hIn_delphes_cp', hIn_delphes.GetTitle())
        # hIn_fullsim_cp = graphToHisto(hIn_fullsim.CreateGraph(), 'hIn_fullsim_cp', hIn_fullsim.GetTitle())
        hIn_delphes_cp = toHistoForRatio(hIn_delphes)
        hIn_fullsim_cp = toHistoForRatio(hIn_fullsim)
        trplot = ROOT.TRatioPlot(hIn_delphes_cp, hIn_fullsim_cp)

    c1.SetLogy(False)
    trplot.Draw()
    trplot.GetLowerRefYaxis().SetTitle("Delphes/FullSim")
    if is_efficiency: 
        if not ymin:
            ymin = 0. if not args.log else 1.e-5
        if not ymax:
            ymax = 1.
    trplot.GetUpperRefYaxis().SetRangeUser(ymin, ymax)
    if args.log:
        trplot.GetUpperPad().SetLogy(True)
    if args.rymin: trplot.GetLowerRefGraph().SetMinimum(args.rymin);
    if args.rymax: trplot.GetLowerRefGraph().SetMaximum(args.rymax);
    leg = ROOT.TLegend(0.11, 0.95, 0.88, 0.98)
    text = ROOT.TLatex(0.77, 0.88, "PU " + args.PU)

c1.cd()

leg.SetNColumns(2)
leg.AddEntry(hIn_fullsim, "Full simulation", "lp")
leg.AddEntry(hIn_delphes, "Delphes", "lp")
leg.SetFillStyle(0)
leg.SetBorderSize(0)
leg.Draw()

text.SetTextFont(42)
text.SetTextSize(0.04)
text.SetNDC(True)
text.Draw()

c1.Update()
if not args.quit:
    raw_input()

oname = 'plots/plot_' + vname.strip('h_') + '_PU' + args.PU + '_' + args.sample
if args.log:
    oname += '_log'
oname += '.pdf'
c1.Print(oname, 'pdf')