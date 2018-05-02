#ifndef RDGENJET_H
#define RDGENJET_H

#include "BaseTree.h"
#include "TChain.h"

class rdGenJet : public BaseTree {
    public:
        rdGenJet(TChain* ch);
        ~rdGenJet(){};

        TTreeReaderValue<Int_t>   GenJet_size = {fReader, "GenJet_size"};
        TTreeReaderArray<Float_t> PT          = {fReader, "PT"};
        TTreeReaderArray<Float_t> Eta         = {fReader, "Eta"};
        TTreeReaderArray<Float_t> Phi         = {fReader, "Phi"};
        TTreeReaderArray<Float_t> Mass        = {fReader, "Mass"};
};

rdGenJet::rdGenJet(TChain* ch) :
    BaseTree(ch)
{}

#endif