#ifndef RDEVENT_H
#define RDEVENT_H

#include "BaseTree.h"
#include "TChain.h"

class rdEvent : public BaseTree {
    public:
        rdEvent(TChain* ch);
        ~rdEvent(){};

        TTreeReaderValue<Int_t> Run         = {fReader, "Run"};
        TTreeReaderValue<Int_t> Event       = {fReader, "Event"};
        TTreeReaderValue<Int_t> Lumi        = {fReader, "Lumi"};
        TTreeReaderValue<Int_t> Weight_size = {fReader, "Weight_size"};
        TTreeReaderArray<Float_t> Weight    = {fReader, "Weight"};

};

rdEvent::rdEvent(TChain* ch) :
    BaseTree(ch)
{}

#endif
