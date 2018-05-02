#ifndef NTUPLETREES_H
#define NTUPLETREES_H

#include "rdJetPUPPI.h"
#include "rdGenJet.h"
#include "rdParticle.h"
#include "rdEvent.h"
#include <string>
#include <memory>
#include <iostream>

class NtupleTrees {
    public:
        NtupleTrees(std::string filelistname, std::string treename);
        ~NtupleTrees(){}

        rdJetPUPPI* get_JetPUPPI() {return JetPUPPI_.get();}
        rdGenJet*   get_GenJet()   {return GenJet_.get();}
        rdParticle* get_Particle() {return Particle_.get();}
        rdEvent*    get_Event()    {return Event_.get();}

        bool Next();

    private:

        // const static int debug = true;

        TChain JetPUPPI_chain_;
        TChain GenJet_chain_;
        TChain Particle_chain_;
        TChain Event_chain_;

        std::unique_ptr<rdJetPUPPI> JetPUPPI_;
        std::unique_ptr<rdGenJet>   GenJet_;
        std::unique_ptr<rdParticle> Particle_;
        std::unique_ptr<rdEvent>    Event_;

        std::string treename_;

};

bool NtupleTrees::Next()
{
    // FIXME: need a check of the coherence of the trees ?
    bool next = (
        JetPUPPI_ ->Next() &&
        GenJet_   ->Next() &&
        Particle_ ->Next() &&
        Event_    ->Next()
    );
    return next;
}

NtupleTrees::NtupleTrees(std::string filelistname, std::string treename):
    JetPUPPI_chain_ ("ntuple/JetPUPPI"),
    GenJet_chain_   ("ntuple/GenJet"),
    Particle_chain_ ("ntuple/Particle"),
    Event_chain_    ("ntuple/Event"),
    treename_ (treename)
{

    std::cout << "[INFO] NtupleTrees : " << treename_ << " : going to read list " << filelistname << std::endl;
    //cout << "=== inizio parser ===" << endl;
    std::ifstream infile(filelistname.c_str());
    std::string line;
    int nfiles = 0;
    while (std::getline(infile, line))
    {
        line = line.substr(0, line.find("#", 0)); // remove comments introduced by #
        while (line.find(" ") != std::string::npos) line = line.erase(line.find(" "), 1); // remove white spaces
        while (line.find("\n") != std::string::npos) line = line.erase(line.find("\n"), 1); // remove new line characters
        while (line.find("\r") != std::string::npos) line = line.erase(line.find("\r"), 1); // remove carriage return characters
        if (!line.empty()) // skip empty lines
        {
            JetPUPPI_chain_.Add(line.c_str());
            GenJet_chain_.Add(line.c_str());
            Particle_chain_.Add(line.c_str());
            Event_chain_.Add(line.c_str());
            ++nfiles;
        }
    }

    std::cout << "[INFO] NtupleTrees : " << treename_ << " : read " << nfiles << " files" << std::endl;

    /*
    // calling this code will interfere with the readers
    if (debug)
    {
        std::cout << "JetPUPPI_chain_ size : " << JetPUPPI_chain_.GetEntries() << std::endl;
        std::cout << "GenJet_chain_ size : "   << GenJet_chain_.GetEntries()   << std::endl;
        std::cout << "Particle_chain_ size : " << Particle_chain_.GetEntries() << std::endl;
        std::cout << "Event_chain_ size : "    << Event_chain_.GetEntries()    << std::endl;
    }
    */


    /////////// --- create the trees
    JetPUPPI_ = std::unique_ptr<rdJetPUPPI> (new rdJetPUPPI(&JetPUPPI_chain_));
    GenJet_   = std::unique_ptr<rdGenJet>   (new rdGenJet(&GenJet_chain_));
    Particle_ = std::unique_ptr<rdParticle> (new rdParticle(&Particle_chain_));
    Event_    = std::unique_ptr<rdEvent>    (new rdEvent(&Event_chain_));
}

#endif