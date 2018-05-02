// c++ -lm -o compare compare.cpp `root-config --glibs --cflags` -I interface/ -lTreePlayer

// #include "JetPUPPI.h"
#include "NtupleTrees.h"
#include "validation/jetPlots.h"
#include "TH1D.h"
#include "TFile.h"
#include <iostream>
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

int main()
{


    NtupleTrees delphes ("filelists/TTbar_PU0_Delphes.txt", "delphes");
    NtupleTrees fullsim ("filelists/TTbar_PU0_FullSim.txt", "fullsim");
    // NtupleTrees delphes ("filelists/TTbar_PU0_Delphes_debug.txt", "delphes");
    // NtupleTrees fullsim ("filelists/TTbar_PU0_FullSim_debug.txt", "fullsim");

    TFile* fOut = new TFile ("histos.root", "recreate");
    TH1D* h_delphes = new TH1D("h_delphes", "h_delphes", 500, 0, 500);
    TH1D* h_fullsim = new TH1D("h_fullsim", "h_fullsim", 500, 0, 500);

    cout << "... loop on DELPHES" << endl;

    int maxEvts = 10000000;

    // loop on delphes
    for (uint iEv = 0; true; ++iEv)
    {
        if (maxEvts > -1 && iEv > maxEvts)
            break;

        if (iEv % 100000 == 0)
            cout << "... processing " << iEv << endl;

        if (!delphes.Next())
            break;

        // skip (semi)leptonic events
        if (hasEleOrMu(&delphes))
            continue;

        // h_delphes->Fill(*(delphes.get_JetPUPPI()->JetPUPPI_size));
        for (uint ijet = 0; ijet < *(delphes.get_JetPUPPI()->JetPUPPI_size); ++ijet){
            float pt = delphes.get_JetPUPPI()->PT.At(ijet);
            if (pt < 20) continue;
            h_delphes->Fill(pt);
        }
    }

    cout << "... loop on FULLSIM" << endl;
    for (uint iEv = 0; true; ++iEv)
    {
        if (maxEvts > -1 && iEv > maxEvts)
            break;

        if (iEv % 100000 == 0)
            cout << "... processing " << iEv << endl;

        if (!fullsim.Next())
            break;

        // skip (semi)leptonic events
        if (hasEleOrMu(&fullsim))
            continue;

        // h_fullsim->Fill(*(fullsim.get_JetPUPPI()->JetPUPPI_size));
        for (uint ijet = 0; ijet < *(fullsim.get_JetPUPPI()->JetPUPPI_size); ++ijet){
            float pt = fullsim.get_JetPUPPI()->PT.At(ijet);
            if (pt < 20) continue;
            h_fullsim->Fill(pt);
        }
    }

    fOut->cd();
    h_delphes->Write();
    h_fullsim->Write();
    fOut->Close();
}