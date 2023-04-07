#!/bin/bash

source $(root-config --bindir)/thisroot.sh

cwd=$(pwd)

for mergedN in 0 1 2 3 4
do

./eff_cbwc_main Ru 10 20 20 60 120 20 5 100 100 ${mergedN} ${cwd}/input/Ru_default.root ref3StPicoEvt ${cwd}/output/Ru_default_${mergedN}.root ${cwd}/output/Ru_cbwc_default_${mergedN}.root 

done
