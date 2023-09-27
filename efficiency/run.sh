#!/bin/sh 


root -b -q tpc_map_param.C\(\"Ru\",1.0,20,2.0\)
root -b -q tpc_map_param.C\(\"Zr\",1.0,20,2.0\)

for i_dca in {0.8,0.9,1.1,1.2}
do
root -b -q tpc_map_param.C\(\"Ru\",$i_dca,20,2.0\)
root -b -q tpc_map_param.C\(\"Zr\",$i_dca,20,2.0\)
done

for i_nhf in {15,18,22,25}
do
root -b -q tpc_map_param.C\(\"Ru\",1.0,$i_nhf,2.0\)
root -b -q tpc_map_param.C\(\"Zr\",1.0,$i_nhf,2.0\)
done

for i_nsp in {1.6,1.8,2.2,2.5}
do
root -b -q tpc_map_param.C\(\"Ru\",1.0,20,$i_nsp\)
root -b -q tpc_map_param.C\(\"Zr\",1.0,20,$i_nsp\)
done
