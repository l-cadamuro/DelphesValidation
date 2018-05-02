#ifndef RDJETPUPPI_H
#define RDJETPUPPI_H

#include "BaseTree.h"
#include "TChain.h"

class rdJetPUPPI : public BaseTree {
    public:
        rdJetPUPPI(TChain* ch);
        ~rdJetPUPPI(){};

       TTreeReaderValue<Int_t> JetPUPPI_size = {fReader, "JetPUPPI_size"};
       TTreeReaderArray<Int_t> ID            = {fReader, "ID"};
       TTreeReaderArray<Int_t> GenJet        = {fReader, "GenJet"};
       TTreeReaderArray<Float_t> PT          = {fReader, "PT"};
       TTreeReaderArray<Float_t> Eta         = {fReader, "Eta"};
       TTreeReaderArray<Float_t> Phi         = {fReader, "Phi"};
       TTreeReaderArray<Float_t> Mass        = {fReader, "Mass"};
       TTreeReaderArray<Int_t> MVAv2         = {fReader, "MVAv2"};
       TTreeReaderArray<Int_t> DeepCSV       = {fReader, "DeepCSV"};
       TTreeReaderArray<Int_t> PartonFlavor  = {fReader, "PartonFlavor"};
       TTreeReaderArray<Int_t> HadronFlavor  = {fReader, "HadronFlavor"};
       TTreeReaderArray<Int_t> GenPartonPID  = {fReader, "GenPartonPID"};
       TTreeReaderArray<Float_t> SF          = {fReader, "SF"};
       TTreeReaderArray<Float_t> JECSF       = {fReader, "JECSF"};
};

rdJetPUPPI::rdJetPUPPI(TChain* ch) :
    BaseTree(ch)
{}

#endif