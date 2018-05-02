#ifndef JETPLOTS_H
#define JETPLOTS_H

#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TEfficiency.h"
#include <memory>
#include <vector>

// ------- extend the jetInfo structure if more info is needed

class jetPlots {

    public:

        struct jetInfo {
            float pt;
            float eta;
            int hadron_flavour;
            int DeepCSV;
            int MVAv2;
            float gjpt;
        };
        
        jetPlots();
        ~jetPlots(){};

        // void fillPlots(jetInfo ji);
        void feed(jetInfo ji); // adds a jet to the internal collection
        void fillPlots(); // processes the jets saved and cleans the collection
        void saveToFile(TFile* fOut);
        void setColor(int col){color_ = col;}

    private:
        std::shared_ptr<TH1D> h_pt  = std::make_shared<TH1D>("h_pt",  ";jet p_{T} [GeV]; events", 500, 0, 500) ;
        std::shared_ptr<TH1D> h_eta = std::make_shared<TH1D>("h_eta", ";jet #eta; events", 200, -5, 5) ;

        const static int n_pt_binning = 25;
        std::array<float, n_pt_binning> pt_binning = {0, 20, 22, 24, 26, 28, 30, 35, 40, 45, 50, 55, 60, 70, 80, 90, 100, 150, 200, 250, 300, 350, 400, 450, 500};
        
        // // btag
        // std::shared_ptr<TH1D> h_pt_bjets_allDeepCSV   = std::make_shared<TH1D>("h_pt_bjets_allDeepCSV",  ";jet p_{T} [GeV]; events", 100, 0, 500) ;
        // std::shared_ptr<TH1D> h_eta_bjets_allDeepCSV  = std::make_shared<TH1D>("h_eta_bjets_allDeepCSV",  ";jet #eta; events", 200, -5, 5) ;
        // std::shared_ptr<TH1D> h_pt_cjets_allDeepCSV   = std::make_shared<TH1D>("h_pt_cjets_allDeepCSV",  ";jet p_{T} [GeV]; events", 100, 0, 500) ;
        // std::shared_ptr<TH1D> h_eta_cjets_allDeepCSV  = std::make_shared<TH1D>("h_eta_cjets_allDeepCSV",  ";jet #eta; events", 200, -5, 5) ;
        // std::shared_ptr<TH1D> h_pt_udsgjets_allDeepCSV   = std::make_shared<TH1D>("h_pt_udsgjets_allDeepCSV",  ";jet p_{T} [GeV]; events", 100, 0, 500) ;
        // std::shared_ptr<TH1D> h_eta_udsgjets_allDeepCSV  = std::make_shared<TH1D>("h_eta_udsgjets_allDeepCSV",  ";jet #eta; events", 200, -5, 5) ;
        
        // // loose WP
        // std::shared_ptr<TH1D> h_pt_bjets_passDeepCSV_loose  = std::make_shared<TH1D>("h_pt_bjets_passDeepCSV_loose",  ";jet p_{T} [GeV]; events", 100, 0, 500) ;
        // std::shared_ptr<TH1D> h_eta_bjets_passDeepCSV_loose = std::make_shared<TH1D>("h_eta_bjets_passDeepCSV_loose",  ";jet #eta; events", 200, -5, 5) ;        
        // std::shared_ptr<TH1D> h_pt_cjets_passDeepCSV_loose  = std::make_shared<TH1D>("h_pt_cjets_passDeepCSV_loose",  ";jet p_{T} [GeV]; events", 100, 0, 500) ;
        // std::shared_ptr<TH1D> h_eta_cjets_passDeepCSV_loose = std::make_shared<TH1D>("h_eta_cjets_passDeepCSV_loose",  ";jet #eta; events", 200, -5, 5) ;        
        // std::shared_ptr<TH1D> h_pt_udsgjets_passDeepCSV_loose  = std::make_shared<TH1D>("h_pt_udsgjets_passDeepCSV_loose",  ";jet p_{T} [GeV]; events", 100, 0, 500) ;
        // std::shared_ptr<TH1D> h_eta_udsgjets_passDeepCSV_loose = std::make_shared<TH1D>("h_eta_udsgjets_passDeepCSV_loose",  ";jet #eta; events", 200, -5, 5) ;

        // // medium WP
        // std::shared_ptr<TH1D> h_pt_bjets_passDeepCSV_medium  = std::make_shared<TH1D>("h_pt_bjets_passDeepCSV_medium",  ";jet p_{T} [GeV]; events", 100, 0, 500) ;
        // std::shared_ptr<TH1D> h_eta_bjets_passDeepCSV_medium = std::make_shared<TH1D>("h_eta_bjets_passDeepCSV_medium",  ";jet #eta; events", 200, -5, 5) ;
        // std::shared_ptr<TH1D> h_pt_cjets_passDeepCSV_medium  = std::make_shared<TH1D>("h_pt_cjets_passDeepCSV_medium",  ";jet p_{T} [GeV]; events", 100, 0, 500) ;
        // std::shared_ptr<TH1D> h_eta_cjets_passDeepCSV_medium = std::make_shared<TH1D>("h_eta_cjets_passDeepCSV_medium",  ";jet #eta; events", 200, -5, 5) ;
        // std::shared_ptr<TH1D> h_pt_udsgjets_passDeepCSV_medium  = std::make_shared<TH1D>("h_pt_udsgjets_passDeepCSV_medium",  ";jet p_{T} [GeV]; events", 100, 0, 500) ;
        // std::shared_ptr<TH1D> h_eta_udsgjets_passDeepCSV_medium = std::make_shared<TH1D>("h_eta_udsgjets_passDeepCSV_medium",  ";jet #eta; events", 200, -5, 5) ;

        // // tight WP
        // std::shared_ptr<TH1D> h_pt_bjets_passDeepCSV_tight  = std::make_shared<TH1D>("h_pt_bjets_passDeepCSV_tight",  ";jet p_{T} [GeV]; events", 100, 0, 500) ;
        // std::shared_ptr<TH1D> h_eta_bjets_passDeepCSV_tight = std::make_shared<TH1D>("h_eta_bjets_passDeepCSV_tight",  ";jet #eta; events", 200, -5, 5) ;
        // std::shared_ptr<TH1D> h_pt_cjets_passDeepCSV_tight  = std::make_shared<TH1D>("h_pt_cjets_passDeepCSV_tight",  ";jet p_{T} [GeV]; events", 100, 0, 500) ;
        // std::shared_ptr<TH1D> h_eta_cjets_passDeepCSV_tight = std::make_shared<TH1D>("h_eta_cjets_passDeepCSV_tight",  ";jet #eta; events", 200, -5, 5) ;
        // std::shared_ptr<TH1D> h_pt_udsgjets_passDeepCSV_tight  = std::make_shared<TH1D>("h_pt_udsgjets_passDeepCSV_tight",  ";jet p_{T} [GeV]; events", 100, 0, 500) ;
        // std::shared_ptr<TH1D> h_eta_udsgjets_passDeepCSV_tight = std::make_shared<TH1D>("h_eta_udsgjets_passDeepCSV_tight",  ";jet #eta; events", 200, -5, 5) ;

        // btag
        std::shared_ptr<TH1D> h_pt_bjets_allDeepCSV   = std::make_shared<TH1D>("h_pt_bjets_allDeepCSV",  ";jet p_{T} [GeV]; events", n_pt_binning-1, pt_binning.data()) ;
        std::shared_ptr<TH1D> h_eta_bjets_allDeepCSV  = std::make_shared<TH1D>("h_eta_bjets_allDeepCSV",  ";jet #eta; events", 100, -5, 5) ;
        std::shared_ptr<TH1D> h_pt_cjets_allDeepCSV   = std::make_shared<TH1D>("h_pt_cjets_allDeepCSV",  ";jet p_{T} [GeV]; events", n_pt_binning-1, pt_binning.data()) ;
        std::shared_ptr<TH1D> h_eta_cjets_allDeepCSV  = std::make_shared<TH1D>("h_eta_cjets_allDeepCSV",  ";jet #eta; events", 100, -5, 5) ;
        std::shared_ptr<TH1D> h_pt_udsgjets_allDeepCSV   = std::make_shared<TH1D>("h_pt_udsgjets_allDeepCSV",  ";jet p_{T} [GeV]; events", n_pt_binning-1, pt_binning.data()) ;
        std::shared_ptr<TH1D> h_eta_udsgjets_allDeepCSV  = std::make_shared<TH1D>("h_eta_udsgjets_allDeepCSV",  ";jet #eta; events", 100, -5, 5) ;

        // split b tag in 3 eta ranges
        std::shared_ptr<TH1D> h_pt_bjets_allDeepCSV_eta_lt1p5     = std::make_shared<TH1D>("h_pt_bjets_allDeepCSV_eta_lt1p5",  ";jet p_{T} [GeV]; events", n_pt_binning-1, pt_binning.data()) ;
        std::shared_ptr<TH1D> h_pt_bjets_allDeepCSV_eta_1p5_2p5   = std::make_shared<TH1D>("h_pt_bjets_allDeepCSV_eta_1p5_2p5",  ";jet p_{T} [GeV]; events", n_pt_binning-1, pt_binning.data()) ;
        std::shared_ptr<TH1D> h_pt_bjets_allDeepCSV_eta_2p5_3p5   = std::make_shared<TH1D>("h_pt_bjets_allDeepCSV_eta_2p5_3p5",  ";jet p_{T} [GeV]; events", n_pt_binning-1, pt_binning.data()) ;
        
        // loose WP
        std::shared_ptr<TH1D> h_pt_bjets_passDeepCSV_loose  = std::make_shared<TH1D>("h_pt_bjets_passDeepCSV_loose",  ";jet p_{T} [GeV]; events", n_pt_binning-1, pt_binning.data()) ;
        std::shared_ptr<TH1D> h_eta_bjets_passDeepCSV_loose = std::make_shared<TH1D>("h_eta_bjets_passDeepCSV_loose",  ";jet #eta; events", 100, -5, 5) ;        
        std::shared_ptr<TH1D> h_pt_cjets_passDeepCSV_loose  = std::make_shared<TH1D>("h_pt_cjets_passDeepCSV_loose",  ";jet p_{T} [GeV]; events", n_pt_binning-1, pt_binning.data()) ;
        std::shared_ptr<TH1D> h_eta_cjets_passDeepCSV_loose = std::make_shared<TH1D>("h_eta_cjets_passDeepCSV_loose",  ";jet #eta; events", 100, -5, 5) ;        
        std::shared_ptr<TH1D> h_pt_udsgjets_passDeepCSV_loose  = std::make_shared<TH1D>("h_pt_udsgjets_passDeepCSV_loose",  ";jet p_{T} [GeV]; events", n_pt_binning-1, pt_binning.data()) ;
        std::shared_ptr<TH1D> h_eta_udsgjets_passDeepCSV_loose = std::make_shared<TH1D>("h_eta_udsgjets_passDeepCSV_loose",  ";jet #eta; events", 100, -5, 5) ;

        // medium WP
        std::shared_ptr<TH1D> h_pt_bjets_passDeepCSV_medium  = std::make_shared<TH1D>("h_pt_bjets_passDeepCSV_medium",  ";jet p_{T} [GeV]; events", n_pt_binning-1, pt_binning.data()) ;
        std::shared_ptr<TH1D> h_eta_bjets_passDeepCSV_medium = std::make_shared<TH1D>("h_eta_bjets_passDeepCSV_medium",  ";jet #eta; events", 100, -5, 5) ;
        std::shared_ptr<TH1D> h_pt_cjets_passDeepCSV_medium  = std::make_shared<TH1D>("h_pt_cjets_passDeepCSV_medium",  ";jet p_{T} [GeV]; events", n_pt_binning-1, pt_binning.data()) ;
        std::shared_ptr<TH1D> h_eta_cjets_passDeepCSV_medium = std::make_shared<TH1D>("h_eta_cjets_passDeepCSV_medium",  ";jet #eta; events", 100, -5, 5) ;
        std::shared_ptr<TH1D> h_pt_udsgjets_passDeepCSV_medium  = std::make_shared<TH1D>("h_pt_udsgjets_passDeepCSV_medium",  ";jet p_{T} [GeV]; events", n_pt_binning-1, pt_binning.data()) ;
        std::shared_ptr<TH1D> h_eta_udsgjets_passDeepCSV_medium = std::make_shared<TH1D>("h_eta_udsgjets_passDeepCSV_medium",  ";jet #eta; events", 100, -5, 5) ;

        std::shared_ptr<TH1D> h_pt_bjets_passDeepCSV_medium_eta_lt1p5     = std::make_shared<TH1D>("h_pt_bjets_passDeepCSV_medium_eta_lt1p5",  ";jet p_{T} [GeV]; events", n_pt_binning-1, pt_binning.data()) ;
        std::shared_ptr<TH1D> h_pt_bjets_passDeepCSV_medium_eta_1p5_2p5   = std::make_shared<TH1D>("h_pt_bjets_passDeepCSV_medium_eta_1p5_2p5",  ";jet p_{T} [GeV]; events", n_pt_binning-1, pt_binning.data()) ;
        std::shared_ptr<TH1D> h_pt_bjets_passDeepCSV_medium_eta_2p5_3p5   = std::make_shared<TH1D>("h_pt_bjets_passDeepCSV_medium_eta_2p5_3p5",  ";jet p_{T} [GeV]; events", n_pt_binning-1, pt_binning.data()) ;

        // tight WP
        std::shared_ptr<TH1D> h_pt_bjets_passDeepCSV_tight  = std::make_shared<TH1D>("h_pt_bjets_passDeepCSV_tight",  ";jet p_{T} [GeV]; events", n_pt_binning-1, pt_binning.data()) ;
        std::shared_ptr<TH1D> h_eta_bjets_passDeepCSV_tight = std::make_shared<TH1D>("h_eta_bjets_passDeepCSV_tight",  ";jet #eta; events", 100, -5, 5) ;
        std::shared_ptr<TH1D> h_pt_cjets_passDeepCSV_tight  = std::make_shared<TH1D>("h_pt_cjets_passDeepCSV_tight",  ";jet p_{T} [GeV]; events", n_pt_binning-1, pt_binning.data()) ;
        std::shared_ptr<TH1D> h_eta_cjets_passDeepCSV_tight = std::make_shared<TH1D>("h_eta_cjets_passDeepCSV_tight",  ";jet #eta; events", 100, -5, 5) ;
        std::shared_ptr<TH1D> h_pt_udsgjets_passDeepCSV_tight  = std::make_shared<TH1D>("h_pt_udsgjets_passDeepCSV_tight",  ";jet p_{T} [GeV]; events", n_pt_binning-1, pt_binning.data()) ;
        std::shared_ptr<TH1D> h_eta_udsgjets_passDeepCSV_tight = std::make_shared<TH1D>("h_eta_udsgjets_passDeepCSV_tight",  ";jet #eta; events", 100, -5, 5) ;

        // ----------------------------------------------------------

        std::shared_ptr<TH1D> h_lead_pt         = std::make_shared<TH1D>("h_lead_pt",  ";leading jet p_{T} [GeV]; events", 500, 0, 500) ;
        std::shared_ptr<TH1D> h_lead_eta        = std::make_shared<TH1D>("h_lead_eta", ";leading jet #eta; events", 200, -5, 5) ;
        std::shared_ptr<TH1D> h_lead_hadflavour = std::make_shared<TH1D>("h_lead_hadflavour", ";leading jet hadron flavour; events", 50, -25, 25) ;
        std::shared_ptr<TH1D> h_lead_DeepCSV    = std::make_shared<TH1D>("h_lead_DeepCSV", ";leading jet Deep CSV; events", 8, 0, 8) ;
        std::shared_ptr<TH1D> h_lead_MVAv2      = std::make_shared<TH1D>("h_lead_MVAv2", ";leading jet Deep CSV; events", 8, 0, 8) ;

        std::shared_ptr<TH1D> h_sublead_pt         = std::make_shared<TH1D>("h_sublead_pt",  ";subleading jet p_{T} [GeV]; events", 500, 0, 500) ;
        std::shared_ptr<TH1D> h_sublead_eta        = std::make_shared<TH1D>("h_sublead_eta", ";subleading jet #eta; events", 200, -5, 5) ;
        std::shared_ptr<TH1D> h_sublead_hadflavour = std::make_shared<TH1D>("h_sublead_hadflavour", ";subleading jet hadron flavour; events", 50, -25, 25) ;
        std::shared_ptr<TH1D> h_sublead_DeepCSV    = std::make_shared<TH1D>("h_sublead_DeepCSV", ";subleading jet Deep CSV; events", 8, 0, 8) ;
        std::shared_ptr<TH1D> h_sublead_MVAv2      = std::make_shared<TH1D>("h_sublead_MVAv2", ";subleading jet Deep CSV; events", 8, 0, 8) ;

        // ----------------------------------------------------------

        std::shared_ptr<TH1D> h_resol       = std::make_shared<TH1D>("h_resol", ";jet p_{T} / gen jet p_{T}", 500, 0, 5);
        std::shared_ptr<TH1D> h_resol_udsg  = std::make_shared<TH1D>("h_resol_udsg", ";jet p_{T} / gen jet p_{T}", 500, 0, 5);
        std::shared_ptr<TH1D> h_resol_b     = std::make_shared<TH1D>("h_resol_b", ";jet p_{T} / gen jet p_{T}", 500, 0, 5);
        std::shared_ptr<TH1D> h_resol_c     = std::make_shared<TH1D>("h_resol_c", ";jet p_{T} / gen jet p_{T}", 500, 0, 5);

        // ----------------------------------------------------------

        std::shared_ptr<TH1D> h_njets_      = std::make_shared<TH1D>("h_njets", ";N_{jets}", 15, 0, 15);
        std::shared_ptr<TH1D> h_njets_etalt3_ = std::make_shared<TH1D>("h_njets_etalt3", ";N_{jets}, |#eta| < 3", 15, 0, 15);
        std::shared_ptr<TH1D> h_njets_etagt3_ = std::make_shared<TH1D>("h_njets_etagt3", ";N_{jets}, |#eta| > 3", 15, 0, 15);


        std::vector<jetInfo> jets_;

        std::vector<TH1*> all_histos_; // this is just to apply global propertu easily to object, so raw pointer --> do not use for memory management/access/etc

        int color_;
};

// void jetPlots::fillPlots(jetInfo ji)
// {
//     h_pt->Fill(ji.pt);
//     h_eta->Fill(ji.eta);
// }

jetPlots::jetPlots()
{
    color_ = kBlue;

    all_histos_.clear();

    all_histos_.push_back(h_pt.get());
    all_histos_.push_back(h_eta.get());
    
    all_histos_.push_back(h_pt_bjets_allDeepCSV.get());
    all_histos_.push_back(h_eta_bjets_allDeepCSV.get());
    all_histos_.push_back(h_pt_cjets_allDeepCSV.get());
    all_histos_.push_back(h_eta_cjets_allDeepCSV.get());
    all_histos_.push_back(h_pt_udsgjets_allDeepCSV.get());
    all_histos_.push_back(h_eta_udsgjets_allDeepCSV.get());

    all_histos_.push_back(h_pt_bjets_allDeepCSV_eta_lt1p5.get());
    all_histos_.push_back(h_pt_bjets_allDeepCSV_eta_1p5_2p5.get());
    all_histos_.push_back(h_pt_bjets_allDeepCSV_eta_2p5_3p5.get());

    all_histos_.push_back(h_pt_bjets_passDeepCSV_loose.get());
    all_histos_.push_back(h_eta_bjets_passDeepCSV_loose.get());
    all_histos_.push_back(h_pt_cjets_passDeepCSV_loose.get());
    all_histos_.push_back(h_eta_cjets_passDeepCSV_loose.get());
    all_histos_.push_back(h_pt_udsgjets_passDeepCSV_loose.get());
    all_histos_.push_back(h_eta_udsgjets_passDeepCSV_loose.get());

    all_histos_.push_back(h_pt_bjets_passDeepCSV_medium.get());
    all_histos_.push_back(h_eta_bjets_passDeepCSV_medium.get());
    all_histos_.push_back(h_pt_cjets_passDeepCSV_medium.get());
    all_histos_.push_back(h_eta_cjets_passDeepCSV_medium.get());
    all_histos_.push_back(h_pt_udsgjets_passDeepCSV_medium.get());
    all_histos_.push_back(h_eta_udsgjets_passDeepCSV_medium.get());

    all_histos_.push_back(h_pt_bjets_passDeepCSV_medium_eta_lt1p5.get());
    all_histos_.push_back(h_pt_bjets_passDeepCSV_medium_eta_1p5_2p5.get());
    all_histos_.push_back(h_pt_bjets_passDeepCSV_medium_eta_2p5_3p5.get());

    all_histos_.push_back(h_pt_bjets_passDeepCSV_tight.get());
    all_histos_.push_back(h_eta_bjets_passDeepCSV_tight.get());
    all_histos_.push_back(h_pt_cjets_passDeepCSV_tight.get());
    all_histos_.push_back(h_eta_cjets_passDeepCSV_tight.get());
    all_histos_.push_back(h_pt_udsgjets_passDeepCSV_tight.get());
    all_histos_.push_back(h_eta_udsgjets_passDeepCSV_tight.get());

    all_histos_.push_back(h_lead_pt.get());
    all_histos_.push_back(h_lead_eta.get());
    all_histos_.push_back(h_lead_hadflavour.get());
    all_histos_.push_back(h_lead_DeepCSV.get());
    all_histos_.push_back(h_lead_MVAv2.get());
    
    all_histos_.push_back(h_sublead_pt.get());
    all_histos_.push_back(h_sublead_eta.get());
    all_histos_.push_back(h_sublead_hadflavour.get());
    all_histos_.push_back(h_sublead_DeepCSV.get());
    all_histos_.push_back(h_sublead_MVAv2.get());

    all_histos_.push_back(h_resol.get());
    all_histos_.push_back(h_resol_udsg.get());
    all_histos_.push_back(h_resol_b.get());
    all_histos_.push_back(h_resol_c.get());

    all_histos_.push_back(h_njets_.get());
    all_histos_.push_back(h_njets_etalt3_.get());
    all_histos_.push_back(h_njets_etagt3_.get());
}

void jetPlots::fillPlots()
{
    // all jets
    int  njets = 0;
    int  njets_etalt3 = 0;
    int  njets_etagt3 = 0;

    for (uint jidx = 0; jidx < jets_.size(); ++jidx)
    {
        jetInfo& ji = jets_.at(jidx);
        h_pt->Fill(ji.pt);
        h_eta->Fill(ji.eta);

        float pt = ji.pt;
        float eta = ji.eta;
        float aeta = std::abs(eta);
        int  flav = abs(ji.hadron_flavour);
        bool btagged_loose  = (ji.DeepCSV & (1 << 0));
        bool btagged_medium = (ji.DeepCSV & (1 << 1));
        bool btagged_tight  = (ji.DeepCSV & (1 << 2));

        ++njets;
        if (aeta < 3.0) ++njets_etalt3;
        else            ++njets_etagt3;

        if (ji.gjpt > 0) {
            double resol = ji.pt / ji.gjpt;
            h_resol->Fill(resol);
            if      (flav == 5) h_resol_b    -> Fill(resol);
            else if (flav == 4) h_resol_c    -> Fill(resol);
            else                h_resol_udsg -> Fill(resol);
        }

        // jet b-tag - restrict to leading and subleading jet
        if (jidx <= 1)
        {
            if (flav == 5) // bjets
            {
                h_pt_bjets_allDeepCSV->Fill(pt);
                h_eta_bjets_allDeepCSV->Fill(eta);
                if (btagged_loose)  h_pt_bjets_passDeepCSV_loose->Fill(pt);
                if (btagged_loose)  h_eta_bjets_passDeepCSV_loose->Fill(eta);
                if (btagged_medium) h_pt_bjets_passDeepCSV_medium->Fill(pt);
                if (btagged_medium) h_eta_bjets_passDeepCSV_medium->Fill(eta);
                if (btagged_tight)  h_pt_bjets_passDeepCSV_tight->Fill(pt);
                if (btagged_tight)  h_eta_bjets_passDeepCSV_tight->Fill(eta);

                // special - eta ranges for b jets to compare with TDR
                if (aeta < 1.5){                    
                    h_pt_bjets_allDeepCSV_eta_lt1p5->Fill(pt);
                    if (btagged_medium) h_pt_bjets_passDeepCSV_medium_eta_lt1p5->Fill(pt);
                }
                else if (aeta < 2.5){                    
                    h_pt_bjets_allDeepCSV_eta_1p5_2p5->Fill(pt);
                    if (btagged_medium) h_pt_bjets_passDeepCSV_medium_eta_1p5_2p5->Fill(pt);
                }
                else if (aeta < 3.5){                    
                    h_pt_bjets_allDeepCSV_eta_2p5_3p5->Fill(pt);
                    if (btagged_medium) h_pt_bjets_passDeepCSV_medium_eta_2p5_3p5->Fill(pt);
                }
            }
            else if (flav == 4) // cjets
            {
                h_pt_cjets_allDeepCSV->Fill(pt);
                h_eta_cjets_allDeepCSV->Fill(eta);
                if (btagged_loose)  h_pt_cjets_passDeepCSV_loose->Fill(pt);
                if (btagged_loose)  h_eta_cjets_passDeepCSV_loose->Fill(eta);
                if (btagged_medium) h_pt_cjets_passDeepCSV_medium->Fill(pt);
                if (btagged_medium) h_eta_cjets_passDeepCSV_medium->Fill(eta);
                if (btagged_tight)  h_pt_cjets_passDeepCSV_tight->Fill(pt);
                if (btagged_tight)  h_eta_cjets_passDeepCSV_tight->Fill(eta);
            }
            else // light jest
            {
                h_pt_udsgjets_allDeepCSV->Fill(pt);
                h_eta_udsgjets_allDeepCSV->Fill(eta);
                if (btagged_loose)  h_pt_udsgjets_passDeepCSV_loose->Fill(pt);
                if (btagged_loose)  h_eta_udsgjets_passDeepCSV_loose->Fill(eta);
                if (btagged_medium) h_pt_udsgjets_passDeepCSV_medium->Fill(pt);
                if (btagged_medium) h_eta_udsgjets_passDeepCSV_medium->Fill(eta);
                if (btagged_tight)  h_pt_udsgjets_passDeepCSV_tight->Fill(pt);
                if (btagged_tight)  h_eta_udsgjets_passDeepCSV_tight->Fill(eta);
            }
        }
    }

    // leading jet
    if (jets_.size() > 0)
    {
        h_lead_pt->Fill(jets_.at(0).pt);
        h_lead_eta->Fill(jets_.at(0).eta);
        h_lead_hadflavour->Fill(jets_.at(0).hadron_flavour);
        h_lead_DeepCSV->Fill(jets_.at(0).DeepCSV);
        h_lead_MVAv2->Fill(jets_.at(0).MVAv2);
    }

    // subleading jet
    if (jets_.size() > 1)
    {
        h_sublead_pt->Fill(jets_.at(1).pt);
        h_sublead_eta->Fill(jets_.at(1).eta);
        h_sublead_hadflavour->Fill(jets_.at(1).hadron_flavour);
        h_sublead_DeepCSV->Fill(jets_.at(1).DeepCSV);
        h_sublead_MVAv2->Fill(jets_.at(1).MVAv2);
    }

    h_njets_->Fill(njets);
    h_njets_etalt3_->Fill(njets_etalt3);
    h_njets_etagt3_->Fill(njets_etagt3);


    // at the end, clear the jets stored and prepare for a new event
    jets_.clear();
}


void jetPlots::feed(jetInfo ji)
{
    // NOTE: assumes jets are arriving in order of pT. If ordering is needed, insert in order here
    if (ji.pt < 20) // since min pT is differnt in fullsim and delphes
        return;
    
    jets_.push_back(ji);
}

void jetPlots::saveToFile(TFile* fOut)
{

    // postprocessing here
    std::shared_ptr<TEfficiency> h_pt_bjets_effDeepCSV_loose      = std::make_shared<TEfficiency> (*h_pt_bjets_passDeepCSV_loose,      *h_pt_bjets_allDeepCSV);
    std::shared_ptr<TEfficiency> h_eta_bjets_effDeepCSV_loose     = std::make_shared<TEfficiency> (*h_eta_bjets_passDeepCSV_loose,     *h_eta_bjets_allDeepCSV);
    std::shared_ptr<TEfficiency> h_pt_cjets_effDeepCSV_loose      = std::make_shared<TEfficiency> (*h_pt_cjets_passDeepCSV_loose,      *h_pt_cjets_allDeepCSV);
    std::shared_ptr<TEfficiency> h_eta_cjets_effDeepCSV_loose     = std::make_shared<TEfficiency> (*h_eta_cjets_passDeepCSV_loose,     *h_eta_cjets_allDeepCSV);
    std::shared_ptr<TEfficiency> h_pt_udsgjets_effDeepCSV_loose   = std::make_shared<TEfficiency> (*h_pt_udsgjets_passDeepCSV_loose,   *h_pt_udsgjets_allDeepCSV);
    std::shared_ptr<TEfficiency> h_eta_udsgjets_effDeepCSV_loose  = std::make_shared<TEfficiency> (*h_eta_udsgjets_passDeepCSV_loose,  *h_eta_udsgjets_allDeepCSV);
    std::shared_ptr<TEfficiency> h_pt_bjets_effDeepCSV_medium     = std::make_shared<TEfficiency> (*h_pt_bjets_passDeepCSV_medium,     *h_pt_bjets_allDeepCSV);
    std::shared_ptr<TEfficiency> h_eta_bjets_effDeepCSV_medium    = std::make_shared<TEfficiency> (*h_eta_bjets_passDeepCSV_medium,    *h_eta_bjets_allDeepCSV);
    std::shared_ptr<TEfficiency> h_pt_cjets_effDeepCSV_medium     = std::make_shared<TEfficiency> (*h_pt_cjets_passDeepCSV_medium,     *h_pt_cjets_allDeepCSV);
    std::shared_ptr<TEfficiency> h_eta_cjets_effDeepCSV_medium    = std::make_shared<TEfficiency> (*h_eta_cjets_passDeepCSV_medium,    *h_eta_cjets_allDeepCSV);
    std::shared_ptr<TEfficiency> h_pt_udsgjets_effDeepCSV_medium  = std::make_shared<TEfficiency> (*h_pt_udsgjets_passDeepCSV_medium,  *h_pt_udsgjets_allDeepCSV);
    std::shared_ptr<TEfficiency> h_eta_udsgjets_effDeepCSV_medium = std::make_shared<TEfficiency> (*h_eta_udsgjets_passDeepCSV_medium, *h_eta_udsgjets_allDeepCSV);
    std::shared_ptr<TEfficiency> h_pt_bjets_effDeepCSV_tight      = std::make_shared<TEfficiency> (*h_pt_bjets_passDeepCSV_tight,      *h_pt_bjets_allDeepCSV);
    std::shared_ptr<TEfficiency> h_eta_bjets_effDeepCSV_tight     = std::make_shared<TEfficiency> (*h_eta_bjets_passDeepCSV_tight,     *h_eta_bjets_allDeepCSV);
    std::shared_ptr<TEfficiency> h_pt_cjets_effDeepCSV_tight      = std::make_shared<TEfficiency> (*h_pt_cjets_passDeepCSV_tight,      *h_pt_cjets_allDeepCSV);
    std::shared_ptr<TEfficiency> h_eta_cjets_effDeepCSV_tight     = std::make_shared<TEfficiency> (*h_eta_cjets_passDeepCSV_tight,     *h_eta_cjets_allDeepCSV);
    std::shared_ptr<TEfficiency> h_pt_udsgjets_effDeepCSV_tight   = std::make_shared<TEfficiency> (*h_pt_udsgjets_passDeepCSV_tight,   *h_pt_udsgjets_allDeepCSV);
    std::shared_ptr<TEfficiency> h_eta_udsgjets_effDeepCSV_tight  = std::make_shared<TEfficiency> (*h_eta_udsgjets_passDeepCSV_tight,  *h_eta_udsgjets_allDeepCSV);
    // special in eta ranges
    std::shared_ptr<TEfficiency> h_pt_bjets_effDeepCSV_medium_eta_lt1p5   = std::make_shared<TEfficiency> (*h_pt_bjets_passDeepCSV_medium_eta_lt1p5,   *h_pt_bjets_allDeepCSV_eta_lt1p5);
    std::shared_ptr<TEfficiency> h_pt_bjets_effDeepCSV_medium_eta_1p5_2p5 = std::make_shared<TEfficiency> (*h_pt_bjets_passDeepCSV_medium_eta_1p5_2p5, *h_pt_bjets_allDeepCSV_eta_1p5_2p5);
    std::shared_ptr<TEfficiency> h_pt_bjets_effDeepCSV_medium_eta_2p5_3p5 = std::make_shared<TEfficiency> (*h_pt_bjets_passDeepCSV_medium_eta_2p5_3p5, *h_pt_bjets_allDeepCSV_eta_2p5_3p5);

    h_pt_bjets_effDeepCSV_loose->SetName("h_pt_bjets_effDeepCSV_loose");
    h_eta_bjets_effDeepCSV_loose->SetName("h_eta_bjets_effDeepCSV_loose");
    h_pt_cjets_effDeepCSV_loose->SetName("h_pt_cjets_effDeepCSV_loose");
    h_eta_cjets_effDeepCSV_loose->SetName("h_eta_cjets_effDeepCSV_loose");
    h_pt_udsgjets_effDeepCSV_loose->SetName("h_pt_udsgjets_effDeepCSV_loose");
    h_eta_udsgjets_effDeepCSV_loose->SetName("h_eta_udsgjets_effDeepCSV_loose");
    h_pt_bjets_effDeepCSV_medium->SetName("h_pt_bjets_effDeepCSV_medium");
    h_eta_bjets_effDeepCSV_medium->SetName("h_eta_bjets_effDeepCSV_medium");
    h_pt_cjets_effDeepCSV_medium->SetName("h_pt_cjets_effDeepCSV_medium");
    h_eta_cjets_effDeepCSV_medium->SetName("h_eta_cjets_effDeepCSV_medium");
    h_pt_udsgjets_effDeepCSV_medium->SetName("h_pt_udsgjets_effDeepCSV_medium");
    h_eta_udsgjets_effDeepCSV_medium->SetName("h_eta_udsgjets_effDeepCSV_medium");
    h_pt_bjets_effDeepCSV_tight->SetName("h_pt_bjets_effDeepCSV_tight");
    h_eta_bjets_effDeepCSV_tight->SetName("h_eta_bjets_effDeepCSV_tight");
    h_pt_cjets_effDeepCSV_tight->SetName("h_pt_cjets_effDeepCSV_tight");
    h_eta_cjets_effDeepCSV_tight->SetName("h_eta_cjets_effDeepCSV_tight");
    h_pt_udsgjets_effDeepCSV_tight->SetName("h_pt_udsgjets_effDeepCSV_tight");
    h_eta_udsgjets_effDeepCSV_tight->SetName("h_eta_udsgjets_effDeepCSV_tight");
    //
    h_pt_bjets_effDeepCSV_medium_eta_lt1p5->SetName("h_pt_bjets_effDeepCSV_medium_eta_lt1p5");
    h_pt_bjets_effDeepCSV_medium_eta_1p5_2p5->SetName("h_pt_bjets_effDeepCSV_medium_eta_1p5_2p5");
    h_pt_bjets_effDeepCSV_medium_eta_2p5_3p5->SetName("h_pt_bjets_effDeepCSV_medium_eta_2p5_3p5");

    std::vector<TEfficiency*> all_effs_;
    all_effs_.push_back(h_pt_bjets_effDeepCSV_loose.get());
    all_effs_.push_back(h_eta_bjets_effDeepCSV_loose.get());
    all_effs_.push_back(h_pt_cjets_effDeepCSV_loose.get());
    all_effs_.push_back(h_eta_cjets_effDeepCSV_loose.get());
    all_effs_.push_back(h_pt_udsgjets_effDeepCSV_loose.get());
    all_effs_.push_back(h_eta_udsgjets_effDeepCSV_loose.get());
    all_effs_.push_back(h_pt_bjets_effDeepCSV_medium.get());
    all_effs_.push_back(h_eta_bjets_effDeepCSV_medium.get());
    all_effs_.push_back(h_pt_cjets_effDeepCSV_medium.get());
    all_effs_.push_back(h_eta_cjets_effDeepCSV_medium.get());
    all_effs_.push_back(h_pt_udsgjets_effDeepCSV_medium.get());
    all_effs_.push_back(h_eta_udsgjets_effDeepCSV_medium.get());
    all_effs_.push_back(h_pt_bjets_effDeepCSV_tight.get());
    all_effs_.push_back(h_eta_bjets_effDeepCSV_tight.get());
    all_effs_.push_back(h_pt_cjets_effDeepCSV_tight.get());
    all_effs_.push_back(h_eta_cjets_effDeepCSV_tight.get());
    all_effs_.push_back(h_pt_udsgjets_effDeepCSV_tight.get());
    all_effs_.push_back(h_eta_udsgjets_effDeepCSV_tight.get());
    //
    all_effs_.push_back(h_pt_bjets_effDeepCSV_medium_eta_lt1p5.get());
    all_effs_.push_back(h_pt_bjets_effDeepCSV_medium_eta_1p5_2p5.get());
    all_effs_.push_back(h_pt_bjets_effDeepCSV_medium_eta_2p5_3p5.get());


    // make the btag plots

    fOut->cd();
    for (TH1* h : all_histos_){
        h->SetLineColor(color_);
        h->Write();
    }
    for (TEfficiency* e : all_effs_){
        e->SetLineColor(color_);
        e->Write();
    }

}

#endif