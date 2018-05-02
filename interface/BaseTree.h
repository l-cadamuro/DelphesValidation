#ifndef BASETREE_H
#define BASETREE_H

#include "TTree.h"
#include "TChain.h"
#include "TTreeReader.h"
#include "TTreeReaderArray.h"
#include "TTreeReaderValue.h"
#include <memory>

class BaseTree {
    public:
        BaseTree(TChain* ch);
        virtual ~BaseTree() = 0;
        TTreeReader& reader() {return fReader;}
        // TChain*      chain()  {return fChain.get();}

        bool Next() {
            return fReader.Next();
        }
    protected:
        TTreeReader     fReader;          //!the tree reader
        // std::unique_ptr<TChain> fChain;   //!pointer to the analyzed TTree or TChain

};

BaseTree::BaseTree(TChain* ch) :
    fReader(ch)//,
    // fChain(ch)
{}

BaseTree::~BaseTree()
{}


#endif