PU=200
# SAMPLE=GG_HH_4B
# SAMPLE=VBF_HH_4B
SAMPLE=TTbar

# python makeComparison.py --sample $SAMPLE --var eta    --PU $PU --ratio --quit --rymax 5        --rebin 10
# python makeComparison.py --sample $SAMPLE --var eta    --PU $PU --ratio --quit --rymax 5 --log  --rebin 10
####
# python makeComparison.py --sample $SAMPLE --var lead_pt    --PU $PU --ratio --quit --rymax 5
# python makeComparison.py --sample $SAMPLE --var sublead_pt --PU $PU --ratio --quit --rymax 5
# python makeComparison.py --sample $SAMPLE --var lead_eta    --PU $PU --ratio --quit
# python makeComparison.py --sample $SAMPLE --var sublead_eta --PU $PU --ratio --quit
# python makeComparison.py --sample $SAMPLE --var lead_eta    --PU $PU --ratio --quit --log
# python makeComparison.py --sample $SAMPLE --var sublead_eta --PU $PU --ratio --quit --log
# python makeComparison.py --sample $SAMPLE --var lead_hadflavour    --PU $PU --ratio --quit
# python makeComparison.py --sample $SAMPLE --var sublead_hadflavour --PU $PU --ratio --quit
# python makeComparison.py --sample $SAMPLE --var lead_DeepCSV    --PU $PU --ratio --quit
# python makeComparison.py --sample $SAMPLE --var sublead_DeepCSV --PU $PU --ratio --quit
# ####
# python makeComparison.py --sample $SAMPLE --var pt_bjets_effDeepCSV_loose    --PU $PU --ratio --rymax 4 --quit
# python makeComparison.py --sample $SAMPLE --var eta_bjets_effDeepCSV_loose    --PU $PU --ratio --rymax 4 --quit
# python makeComparison.py --sample $SAMPLE --var pt_cjets_effDeepCSV_loose    --PU $PU --ratio --rymax 4 --ymax 0.3 --quit
# python makeComparison.py --sample $SAMPLE --var eta_cjets_effDeepCSV_loose    --PU $PU --ratio --rymax 4 --ymax 0.3 --quit
# python makeComparison.py --sample $SAMPLE --var pt_udsgjets_effDeepCSV_loose    --PU $PU --ratio --rymax 4 --ymax 0.1 --log --quit
# python makeComparison.py --sample $SAMPLE --var eta_udsgjets_effDeepCSV_loose    --PU $PU --ratio --rymax 4 --ymax 0.1 --log --quit
# ####
python makeComparison.py --sample $SAMPLE --var pt_bjets_effDeepCSV_medium    --PU $PU --ratio --rymax 4 --quit
# python makeComparison.py --sample $SAMPLE --var eta_bjets_effDeepCSV_medium    --PU $PU --ratio --rymax 4 --quit
# python makeComparison.py --sample $SAMPLE --var pt_cjets_effDeepCSV_medium    --PU $PU --ratio --rymax 4 --ymax 0.3 --quit
# python makeComparison.py --sample $SAMPLE --var eta_cjets_effDeepCSV_medium    --PU $PU --ratio --rymax 4 --ymax 0.3 --quit
# python makeComparison.py --sample $SAMPLE --var pt_udsgjets_effDeepCSV_medium    --PU $PU --ratio --rymax 4 --ymax 0.1 --ymin 1.e-5 --log --quit
# python makeComparison.py --sample $SAMPLE --var eta_udsgjets_effDeepCSV_medium    --PU $PU --ratio --rymax 4 --ymax 0.1 --ymin 1.e-5 --log --quit
# ####
python makeComparison.py --sample $SAMPLE --var pt_bjets_effDeepCSV_medium_eta_lt1p5      --PU $PU --ratio --rymax 4 --quit
python makeComparison.py --sample $SAMPLE --var pt_bjets_effDeepCSV_medium_eta_1p5_2p5    --PU $PU --ratio --rymax 4 --quit
python makeComparison.py --sample $SAMPLE --var pt_bjets_effDeepCSV_medium_eta_2p5_3p5    --PU $PU --ratio --rymax 4 --quit
# ####
# python makeComparison.py --sample $SAMPLE --var pt_bjets_effDeepCSV_tight    --PU $PU --ratio --rymax 4 --quit
# python makeComparison.py --sample $SAMPLE --var eta_bjets_effDeepCSV_tight    --PU $PU --ratio --rymax 4 --quit
# python makeComparison.py --sample $SAMPLE --var pt_cjets_effDeepCSV_tight    --PU $PU --ratio --rymax 4 --ymax 0.3 --quit
# python makeComparison.py --sample $SAMPLE --var eta_cjets_effDeepCSV_tight    --PU $PU --ratio --rymax 4 --ymax 0.3 --quit
# python makeComparison.py --sample $SAMPLE --var pt_udsgjets_effDeepCSV_tight    --PU $PU --ratio --rymax 4 --ymax 0.1 --log --quit
# python makeComparison.py --sample $SAMPLE --var eta_udsgjets_effDeepCSV_tight    --PU $PU --ratio --rymax 4 --ymax 0.1 --log --quit
####
# python makeComparison.py --sample $SAMPLE --var njets           --PU $PU --ratio --rymax 4 --log --quit
# python makeComparison.py --sample $SAMPLE --var njets_etalt3    --PU $PU --ratio --rymax 4 --log --quit
# python makeComparison.py --sample $SAMPLE --var njets_etagt3    --PU $PU --ratio --rymax 4 --log --quit
# python makeComparison.py --sample $SAMPLE --var njets           --PU $PU --ratio --rymax 4  --quit
# python makeComparison.py --sample $SAMPLE --var njets_etalt3    --PU $PU --ratio --rymax 4  --quit
# python makeComparison.py --sample $SAMPLE --var njets_etagt3    --PU $PU --ratio --rymax 4  --quit