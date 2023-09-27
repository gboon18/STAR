#!/bin/sh

    root -b -q eff_tpc.C\(\"Proton\",\"Ru\",10,20\)
    root -b -q eff_tpc.C\(\"Proton\",\"Zr\",10,20\)
    root -b -q eff_tpc.C\(\"AntiProton\",\"Ru\",10,20\)
    root -b -q eff_tpc.C\(\"AntiProton\",\"Zr\",10,20\)

for i_dca in {8,9,11,12}
do
    root -b -q eff_tpc.C\(\"Proton\",\"Ru\",$i_dca,20\)
    root -b -q eff_tpc.C\(\"Proton\",\"Zr\",$i_dca,20\)
    root -b -q eff_tpc.C\(\"AntiProton\",\"Ru\",$i_dca,20\)
    root -b -q eff_tpc.C\(\"AntiProton\",\"Zr\",$i_dca,20\)
done

for i_nhf in {15,18,22,25}
do
    root -b -q eff_tpc.C\(\"Proton\",\"Ru\",10,$i_nhf\)
    root -b -q eff_tpc.C\(\"Proton\",\"Zr\",10,$i_nhf\)
    root -b -q eff_tpc.C\(\"AntiProton\",\"Ru\",10,$i_nhf\)
    root -b -q eff_tpc.C\(\"AntiProton\",\"Zr\",10,$i_nhf\)
done
