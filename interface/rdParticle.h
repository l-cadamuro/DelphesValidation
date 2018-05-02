#ifndef RDPARTICLE_H
#define RDPARTICLE_H

#include "BaseTree.h"
#include "TChain.h"

class rdParticle : public BaseTree {
    public:
        rdParticle(TChain* ch);
        ~rdParticle(){};

        TTreeReaderValue<Int_t> Particle_size  = {fReader, "Particle_size"};
        TTreeReaderArray<Int_t> PID            = {fReader, "PID"};
        TTreeReaderArray<Int_t> Charge         = {fReader, "Charge"};
        TTreeReaderArray<Int_t> Status         = {fReader, "Status"};
        TTreeReaderArray<Float_t> P            = {fReader, "P"};
        TTreeReaderArray<Float_t> Px           = {fReader, "Px"};
        TTreeReaderArray<Float_t> Py           = {fReader, "Py"};
        TTreeReaderArray<Float_t> Pz           = {fReader, "Pz"};
        TTreeReaderArray<Float_t> E            = {fReader, "E"};
        TTreeReaderArray<Float_t> PT           = {fReader, "PT"};
        TTreeReaderArray<Float_t> Eta          = {fReader, "Eta"};
        TTreeReaderArray<Float_t> Phi          = {fReader, "Phi"};
        TTreeReaderArray<Float_t> Mass         = {fReader, "Mass"};
        TTreeReaderValue<Float_t> IsolationVar = {fReader, "IsolationVar"};
};

rdParticle::rdParticle(TChain* ch) :
    BaseTree(ch)
{}

#endif
