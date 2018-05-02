# DelphesValidation
Set of tools to perform the validation of the Delphes PhaseII fast simulation against the CMS FullSim

## Install
```
cmsrel CMSSW_9_3_2
cd CMSSW_9_3_2/src/
cmsnev
git clone https://github.com/l-cadamuro/DelphesValidation
```

## List of executables
* `matchJetToGen.cpp` : make a TTree with the reco and gen jets to compute the resolution / response / etc. Set Delphes/FullSim, PU and input from cmd line.
* `makePlots.cpp` : produce an output with all the plots of the validation. Set Delphes/FullSim, PU and input from cmd line.
* `compare.cpp` : just fills a single histogram for Delphes and FullSim (useful for quick comparisons / developments)

## List of macros and scripts
* `makeComparison.py` : make a pdf output of a variable (configure from cmd line)
* `makeAllPlots.sh` : create the pdf output of many variables (calls makeComparison.py)
* `quickJetScaleComp.py` : quick script to compare two variables (configure name, cut and histo inside the script)
* `make_jecs.py` : derive the jet energy scale and resolution in pt/eta/flavour bins using pandas
* `draw_jec_maps.py` : draw the JEC/JER maps produced from the previous code
