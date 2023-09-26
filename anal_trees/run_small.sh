#!/bin/bash
source $(root-config --bindir)/thisroot.sh

./eff_main job/Data/19129008/file.list 1.0 20 2.0 0.60 1.20 2.0 0.5 1.0 1.0 1   # default cuts

for dca_cut in 0.8 0.9 1.1 1.2
do
./eff_main job/Data/19129008/file.list $dca_cut 20 2.0 0.60 1.20 2.0 0.5 1.0 1.0 1 
done

for nhitsfit_cut in 15 18 22 25
do
./eff_main job/Data/19129008/file.list 1.0 $nhitsfit_cut 2.0 0.60 1.20 2.0 0.5 1.0 1.0 1 
done

for nsp_cut in 1.6 1.8 2.2 2.5
do
./eff_main job/Data/19129008/file.list 1.0 20 $nsp_cut 0.60 1.20 2.0 0.5 1.0 1.0 1
done

#mass cut
./eff_main job/Data/19129008/file.list 1.0 20 2.0 0.50 1.10 2.0 0.5 1.0 1.0 1
./eff_main job/Data/19129008/file.list 1.0 20 2.0 0.50 1.15 2.0 0.5 1.0 1.0 1
./eff_main job/Data/19129008/file.list 1.0 20 2.0 0.65 1.25 2.0 0.5 1.0 1.0 1
./eff_main job/Data/19129008/file.list 1.0 20 2.0 0.70 1.30 2.0 0.5 1.0 1.0 1

#det eff err: low_pt high_pt
./eff_main job/Data/19129008/file.list 1.0 20 2.0 0.60 1.20 2.0 0.5 1.05 1.05 1
./eff_main job/Data/19129008/file.list 1.0 20 2.0 0.60 1.20 2.0 0.5 0.95 0.95 1
./eff_main job/Data/19129008/file.list 1.0 20 2.0 0.60 1.20 2.0 0.5 1.05 0.95 1
./eff_main job/Data/19129008/file.list 1.0 20 2.0 0.60 1.20 2.0 0.5 0.95 1.05 1
