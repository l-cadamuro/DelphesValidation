import ROOT
import operator
import numpy as np
import scipy, sys
import copy
from array import array
import pandas as pd
import matplotlib.pyplot as plt
import json

# def show(data, data_format, ientry):
#     print '==== EVENT', ientry, '===='
#     for idx in range(0, len(data_format)):
#         print data_format[idx][0], data_format[idx][1], data[idx][ientry]


##### fixme: consider saving df to disc?

fullsim = True

if fullsim:
    fIn = ROOT.TFile.Open('matchedJets_fullsim_TTbar_PU200.root')
else:
    fIn = ROOT.TFile.Open('matchedJets_delphes_TTbar_PU200.root')

tIn = fIn.Get('matchedJets')
nevents = tIn.GetEntries()
# nevents = 1000

print "Tree has", nevents, "events"

data_format = (
    ('jet_pt'       , 'double'),
    ('jet_eta'      , 'double'),
    # ('jet_phi'      , 'double'),
    # ('jet_mass'     , 'double'),
    ('jet_flav'     , 'double'), ## note: GetV1 will convert everything to double :-(
    ('genjet_pt'    , 'double'),
    # ('genjet_eta'   , 'double'),
    # ('genjet_phi'   , 'double'),
    # ('genjet_mass'  , 'double'),
)

print "... going to fetch data from tree"

##### copy the data to memory. This is super fast, excellent!!
data_buf = [None] * len(data_format)
tIn.SetEstimate(nevents + 1);
for idx, df in enumerate(data_format):
    print '... reading data in', df[0]
    tIn.Draw(df[0],"","goff",nevents,0)
    temp=tIn.GetV1()
    data_buf[idx]=copy.deepcopy(scipy.frombuffer(buffer=temp,dtype=df[1],count=nevents))

print "... done"

data = np.asarray(data_buf)
df   = pd.DataFrame(data, index=[x[0] for x in data_format])
df   = df.transpose()

## graphics options for display
pd.set_option('expand_frame_repr', False)
pd.options.display.max_rows = 10

# print df
# convert jet flav column to integer type
df['jet_flav'] = df['jet_flav'].astype(int)
# use abs eta of jet
df['jet_eta'] = df['jet_eta'].abs()

# print df

####################

print '... computing response'
col_response = df.loc[ : , 'jet_pt'].subtract(df.loc[ : , 'genjet_pt']).divide(df.loc[ : , 'genjet_pt']) ## (reco - gen) / gen
print '... appending response values to df'
df.loc[:, 'response']   = col_response

print df

####################

### test : dump tp file -- OK, cross checked with manual Draw()
# fOut = ROOT.TFile("jet_response.root", 'recreate')
# hResp   = ROOT.TH1D('hResp', 'hResp', 1000, -3, 3)
# hResp_b = ROOT.TH1D('hResp_b', 'hResp_b', 1000, -3, 3)

# for index, row in df.iterrows():
#     hResp.Fill(row['response'])
#     if row['jet_flav'] == 5:
#         hResp_b.Fill(row['response'])

# hResp.Write()
# hResp_b.Write()
# fOut.Close()

####################

bins_jet_pt   = np.geomspace(start = 20,  stop = 500,  num = 18)
bins_jet_pt   = np.append(bins_jet_pt, 99999)
# bins_jet_eta  = np.linspace(start = 0,   stop = 5,   num = 5)
bins_jet_eta  = np.linspace(start = 0,   stop = 3,   num = 6)
# bins_jet_flav = [-0.5, 0.5, 4.5, 5.5] ## 0: udsg, 1: c, 2: b
bins_jet_flav = [-0.5, 0.5, 5.5] ## 0: putting b and c together. 0: udsg, 1: b+c

print 'bins_jet_pt = ', bins_jet_pt
print 'bins_jet_eta = ', bins_jet_eta
print 'bins_jet_flav = ', bins_jet_flav

cut_jet_pt   = pd.cut(df.loc[:,'jet_pt'], bins_jet_pt, labels=range(len(bins_jet_pt)-1))
cut_jet_eta  = pd.cut(df.loc[:,'jet_eta'], bins_jet_eta, labels=range(len(bins_jet_eta)-1))
cut_jet_flav = pd.cut(df.loc[:,'jet_flav'], bins_jet_flav, labels=range(len(bins_jet_flav)-1))

gpb = df.groupby([cut_jet_pt, cut_jet_eta, cut_jet_flav])

# print '.. test in the bin 1,1,1'
# print df.iloc[gpb.indices[1,1,1]]
if fullsim:
    fOut = ROOT.TFile.Open("jet_response_maps_fullsim.root", 'recreate')
else:
    fOut = ROOT.TFile.Open("jet_response_maps_delphes.root", 'recreate')

binning_params = [len(bins_jet_pt)-1, array('d', bins_jet_pt), len(bins_jet_eta)-1, array('d', bins_jet_eta)]

h_scale_udsg = ROOT.TH2D('h_scale_udsg', 'Scale, udsg jets;jet p_{T} [GeV], jet #eta', *binning_params)
h_scale_bc   = ROOT.TH2D('h_scale_bc',   'Scale, bc jets;jet p_{T} [GeV], jet #eta',   *binning_params)
h_scale = [h_scale_udsg, h_scale_bc]

h_resol_udsg = ROOT.TH2D('h_resol_udsg', 'Resolution, udsg jets;jet p_{T} [GeV], jet #eta', *binning_params)
h_resol_bc   = ROOT.TH2D('h_resol_bc',   'Resolution, bc jets;jet p_{T} [GeV], jet #eta',   *binning_params)
h_resol = [h_resol_udsg, h_resol_bc]

h_stat_udsg = ROOT.TH2D('h_stat_udsg', 'Number of events, udsg jets;jet p_{T} [GeV], jet #eta', *binning_params)
h_stat_bc   = ROOT.TH2D('h_stat_bc',   'Number of events, bc jets;jet p_{T} [GeV], jet #eta',   *binning_params)
h_stat = [h_stat_udsg, h_stat_bc]


for bpt in range(len(bins_jet_pt)-1):
    for beta in range(len(bins_jet_eta)-1):
        for bfl in range(len(bins_jet_flav)-1):
            try: sl = df.iloc[gpb.indices[bpt, beta, bfl]]
            except KeyError:
                print "bin ", bpt, beta, bfl, "pt = (%.1f, %.1f), eta = (%.1f, %.1f), flav = (%.1f, %.1f)" % (
                    bins_jet_pt[bpt], bins_jet_pt[bpt+1],
                    bins_jet_eta[beta], bins_jet_eta[beta+1],
                    bins_jet_flav[bfl], bins_jet_flav[bfl+1]
                ), "looks empty"
                avg = 1.0
                rms = 1.0
                nev = 0
            else:
                # print '------' , bpt, beta, bfl
                # print sl
                # print sl['response']
                avg = sl['response'].mean()
                rms = sl['response'].std()
                nev = sl['response'].size
                # print avg
                # print '------'
            h_scale[bfl].SetBinContent(bpt+1, beta+1, avg)
            h_resol[bfl].SetBinContent(bpt+1, beta+1, rms)
            h_stat[bfl] .SetBinContent(bpt+1, beta+1, nev)


fOut.cd()
for h in h_scale : h.Write()
for h in h_resol : h.Write()
for h in h_stat  : h.Write()
fOut.Close()