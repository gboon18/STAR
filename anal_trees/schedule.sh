#!/bin/bash

# logDir=/star/u/hsko/pwg/anal/Coll/isobar/ZrZrRuRu200_2018/charge/cum/effcorr/1_DetEff_light2/output/10102022/23122022_1/job
# schedDir=/star/u/hsko/pwg/anal/Coll/isobar/ZrZrRuRu200_2018/charge/cum/effcorr/1_DetEff_light2/output/10102022/23122022_1/submit

logDir= # assign your log directory
schedDir= # assign your scheduler directory

while read runNo; do
dca, nhitsfit nsp, m2low, m2high, ptmax, ymax, detefflow_err, deteffhigh_err
    ./submit_schedule.sh $logDir $schedDir $runNo 1.0 20 2.0 0.60 1.20 2.0 0.5 1.0 1.0 # original

for dca_cut in 0.8 0.9 1.1 1.2
do
    ./submit_schedule.sh $logDir $schedDir $runNo $dca_cut 20 2.0 0.60 1.20 2.0 0.5 1.0 1.0
done
for nhitsfit_cut in 15 18 22 25
do
    ./submit_schedule.sh $logDir $schedDir $runNo 1.0 $nhitsfit_cut 2.0 0.60 1.20 2.0 0.5 1.0 1.0
done
for nsp_cut in 1.6 1.8 2.2 2.5
do
    ./submit_schedule.sh $logDir $schedDir $runNo 1.0 20 $nsp_cut 0.60 1.20 2.0 0.5 1.0 1.0
done
#mass cut
    ./submit_schedule.sh $logDir $schedDir $runNo 1.0 20 2.0 0.50 1.10 2.0 0.5 1.0 1.0
    ./submit_schedule.sh $logDir $schedDir $runNo 1.0 20 2.0 0.50 1.15 2.0 0.5 1.0 1.0
    ./submit_schedule.sh $logDir $schedDir $runNo 1.0 20 2.0 0.65 1.25 2.0 0.5 1.0 1.0
    ./submit_schedule.sh $logDir $schedDir $runNo 1.0 20 2.0 0.70 1.30 2.0 0.5 1.0 1.0
#det eff err: low_pt high_pt
    ./submit_schedule.sh $logDir $schedDir $runNo 1.0 20 2.0 0.60 1.20 2.0 0.5 1.05 1.05
    ./submit_schedule.sh $logDir $schedDir $runNo 1.0 20 2.0 0.60 1.20 2.0 0.5 0.95 0.95
    ./submit_schedule.sh $logDir $schedDir $runNo 1.0 20 2.0 0.60 1.20 2.0 0.5 1.05 0.95
    ./submit_schedule.sh $logDir $schedDir $runNo 1.0 20 2.0 0.60 1.20 2.0 0.5 0.95 1.05

done <job/CME_HoSan_GoodRunNumbers_new_count.list
