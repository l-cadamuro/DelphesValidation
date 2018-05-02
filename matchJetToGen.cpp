// c++ -lm -o matchJetToGen matchJetToGen.cpp `root-config --glibs --cflags` -I interface/ -lTreePlayer
//
// this matches the reco jets to the gen jets to make a flat tree to derive JEC/JES
// ./matchJetToGen [0|1] [0|200 (optional)] ["TTbar"|"GG_HH_4B"|"VBF_HH_4B" (optional)] [maxEvts (optional)]

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
    
    if (isFullSim)
    {
        tname = string("fullsim") + PUstring;
        fname = string("filelists/") + SampleString + string("_PU") + PUstring + string("_FullSim.txt");
        oname = string("matchedJets_fullsim_") + SampleString + string ("_PU") + PUstring + ".root";
    }
    else
    {
        tname = string("delphes") + PUstring;
        fname = string("filelists/") + SampleString + string("_PU") + PUstring + string("_Delphes.txt");
        oname = string("matchedJets_delphes_") + SampleString + string ("_PU") + PUstring + ".root";
    }

    // prepare otuput
    NtupleTrees nt (fname, tname);
    TFile* fOut = new TFile (oname.c_str(), "recreate");
    TTree* tOut = new TTree ("matchedJets", "matchedJets");

    // branches
    float jet_pt;
    float jet_eta;
    float jet_phi;
    float jet_mass;
    int   jet_flav;

    float genjet_pt;
    float genjet_eta;
    float genjet_phi;
    float genjet_mass;

    tOut->Branch("jet_pt", &jet_pt);
    tOut->Branch("jet_eta", &jet_eta);
    tOut->Branch("jet_phi", &jet_phi);
    tOut->Branch("jet_mass", &jet_mass);
    tOut->Branch("jet_flav", &jet_flav);

    tOut->Branch("genjet_pt", &genjet_pt);
    tOut->Branch("genjet_eta", &genjet_eta);
    tOut->Branch("genjet_phi", &genjet_phi);
    tOut->Branch("genjet_mass", &genjet_mass);

    /////////
    bool saveOnlyMatched = true;

    ////////

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
            // jetPlots::jetInfo jinfo;
            // jinfo.pt  = nt.get_JetPUPPI()->PT.At(ijet);
            // jinfo.eta = nt.get_JetPUPPI()->Eta.At(ijet);
            // jinfo.hadron_flavour = nt.get_JetPUPPI()->HadronFlavor.At(ijet);
            // jinfo.DeepCSV = nt.get_JetPUPPI()->DeepCSV.At(ijet);
            // jinfo.MVAv2   = nt.get_JetPUPPI()->MVAv2.At(ijet);

            TLorentzVector jet_tlv;
            jet_tlv.SetPtEtaPhiM(
                nt.get_JetPUPPI()->PT.At(ijet),
                nt.get_JetPUPPI()->Eta.At(ijet),
                nt.get_JetPUPPI()->Phi.At(ijet),
                nt.get_JetPUPPI()->Mass.At(ijet)
            );

            int igj = get_closest_dR (jet_tlv, tlv_gjs, 0.2); // searching for jet makes this 50% slower
            // int igj = -1;
            // jinfo.gjpt    = (igj >= 0 ? nt.get_GenJet()->PT.At(igj) : -999.);

            jet_pt   = nt.get_JetPUPPI()->PT.At(ijet);
            jet_eta  = nt.get_JetPUPPI()->Eta.At(ijet);
            jet_phi  = nt.get_JetPUPPI()->Phi.At(ijet);
            jet_mass = nt.get_JetPUPPI()->Mass.At(ijet);
            jet_flav = nt.get_JetPUPPI()->HadronFlavor.At(ijet);

            // only use 0, 4, 5 for valid flavs
            if (jet_flav != 5 && jet_flav != 4) jet_flav = 0;

            if (igj > 0)
            {
                genjet_pt   = nt.get_GenJet()->PT.At(igj);
                genjet_eta  = nt.get_GenJet()->Eta.At(igj);
                genjet_phi  = nt.get_GenJet()->Phi.At(igj);
                genjet_mass = nt.get_GenJet()->Mass.At(igj);

                tOut->Fill();
            }

            else if (!saveOnlyMatched)
            {
                genjet_pt   = -1.0;
                genjet_eta  = -1.0;
                genjet_phi  = -1.0;
                genjet_mass = -1.0;

                tOut->Fill();
            }
        }
    }

    fOut->cd();
    tOut->Write();
    fOut->Close();

}