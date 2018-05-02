// c++ -lm -o makePlots makePlots.cpp `root-config --glibs --cflags` -I interface/ -lTreePlayer
// usage
// ./makePlots [0|1] [0|200 (optional)] ["TTbar"|"GG_HH_4B"|"VBF_HH_4B" (optional)] [maxEvts (optional)]
#include "NtupleTrees.h"
#include "validation/jetPlots.h"
#include "TH1D.h"
#include "TFile.h"
#include "TEfficiency.h"
#include "TLorentzVector.h"
#include <iostream>
#include <utility>
#include <string>
using namespace std;

bool hasEleOrMu(NtupleTrees* nt)
{
    for (uint ip = 0; ip < *(nt->get_Particle()->Particle_size); ++ip)
    {
        int apid = abs(nt->get_Particle()->PID.At(ip));
        if (apid == 11 || apid == 13)
            return true;
    }
    return false;
}

int get_closest_dR (TLorentzVector this_v, const std::vector<TLorentzVector>& tomatch, float dR_max = 0.5)
{
    std::vector<pair<float, int>> dRs;
    for (uint itm = 0; itm < tomatch.size(); ++itm)
    {
        float dR = tomatch.at(itm).DeltaR(this_v);
        if (dR < dR_max)
            dRs.push_back(make_pair(dR, itm));
    }

    if (dRs.size() == 0)
        return -1;

    sort(dRs.begin(), dRs.end());
    return dRs.at(0).second;
}

int main(int argc, char** argv)
{

    // int maxEvts = 10000000;
    // int maxEvts = 200000;

    //////////////////////////////////////////

    if (argc < 2)
    {
        cout << "Please say if I need to process delphes (0) or fullsim (1)" << endl;
        return 1;
    }

    std::string PUstring = (argc >= 3 ? argv[2] : "200");
    if (PUstring != string("200") and PUstring != string("0"))
    {
        cout << "You specified a pileup, but I am expecting either 0 or 200, exit" << endl;
        return 2;
    }
    cout << "Running on PU " << PUstring << endl;

    std::string SampleString = (argc >= 4 ? argv[3] : "TTbar");
    cout << "Running on sample " << SampleString << endl;
    
    int maxEvts = (argc >= 5 ? std::stoi(argv[4]) : -1);
    cout << "Max events " << maxEvts << endl;

    bool isFullSim = false;
    if (std::stoi(argv[1]) == 0)
        isFullSim = false;
    else if (std::stoi(argv[1]) == 1)
        isFullSim = true;

    cout << "Is this full simulation? " << boolalpha << isFullSim << noboolalpha << endl;

    string tname;
    string fname;
    string oname;
    
    string extra = "";

    if (isFullSim)
    {
        tname = string("fullsim") + PUstring;
        fname = string("filelists/") + SampleString + string("_PU") + PUstring + string("_FullSim.txt");
        oname = string("jethistos_fullsim_") + SampleString + string ("_PU") + PUstring + extra + ".root";
    }
    else
    {
        tname = string("delphes") + PUstring;
        fname = string("filelists/") + SampleString + string("_PU") + PUstring + string("_Delphes.txt");
        oname = string("jethistos_delphes_") + SampleString + string ("_PU") + PUstring + extra + ".root";
    }

    NtupleTrees nt (fname, tname);
    TFile* fOut = new TFile (oname.c_str(), "recreate");
    jetPlots jp;
    jp.setColor(isFullSim ? kRed : kBlue);


    cout << "... start loop" << endl;

    for (uint iEv = 0; true; ++iEv)
    {
        if (maxEvts > -1 && iEv > maxEvts)
            break;

        if (iEv % 100000 == 0)
            cout << "... processing " << iEv << endl;

        if (!nt.Next())
            break;

        // skip (semi)leptonic events
        if (hasEleOrMu(&nt))
            continue;

        std::vector<TLorentzVector> tlv_gjs;
        for (uint igj = 0; igj < *(nt.get_GenJet()->GenJet_size); ++igj){
            TLorentzVector tlv;
            tlv.SetPtEtaPhiM(
                nt.get_GenJet()->PT.At(igj),
                nt.get_GenJet()->Eta.At(igj),
                nt.get_GenJet()->Phi.At(igj),
                nt.get_GenJet()->Mass.At(igj)
            );
            tlv_gjs.push_back(tlv);
        }

        // h_nt->Fill(*(nt.get_JetPUPPI()->JetPUPPI_size));
        for (uint ijet = 0; ijet < *(nt.get_JetPUPPI()->JetPUPPI_size); ++ijet){
            jetPlots::jetInfo jinfo;
            jinfo.pt  = nt.get_JetPUPPI()->PT.At(ijet);
            jinfo.eta = nt.get_JetPUPPI()->Eta.At(ijet);
            jinfo.hadron_flavour = nt.get_JetPUPPI()->HadronFlavor.At(ijet);
            jinfo.DeepCSV = nt.get_JetPUPPI()->DeepCSV.At(ijet);
            jinfo.MVAv2   = nt.get_JetPUPPI()->MVAv2.At(ijet);

            TLorentzVector jet_tlv;
            jet_tlv.SetPtEtaPhiM(
                nt.get_JetPUPPI()->PT.At(ijet),
                nt.get_JetPUPPI()->Eta.At(ijet),
                nt.get_JetPUPPI()->Phi.At(ijet),
                nt.get_JetPUPPI()->Mass.At(ijet)
            );

            int igj = get_closest_dR (jet_tlv, tlv_gjs); // searching for jet makes this 50% slower
            // int igj = -1;
            jinfo.gjpt    = (igj >= 0 ? nt.get_GenJet()->PT.At(igj) : -999.);

            // if (nt.get_JetPUPPI()->GenJet.At(ijet) < 0) cout << nt.get_JetPUPPI()->GenJet.At(ijet) << endl;
            // int igj = nt.get_JetPUPPI()->GenJet.At(ijet);
            // if (igj >= *(nt.get_GenJet()->GenJet_size)) cout << igj << " " << *(nt.get_GenJet()->GenJet_size) << endl;
            // if (igj == -1) cout << igj << endl;
            // jinfo.gjpt    = (igj >= 0 ? nt.get_GenJet()->PT.At(igj) : -999.);
            // if (jinfo.pt < 20) continue; // FIXME: move this to filling plots, not here
            // jp.fillPlots(jinfo);
            
            jp.feed(jinfo);
        }
        jp.fillPlots();
    }

    jp.saveToFile(fOut);
    fOut->Close();


}