#!/bin/bash

# logDir=/star/u/hsko/pwg/anal/Coll/isobar/ZrZrRuRu200_2018/charge/cum/effcorr/1_DetEff_light2/output/10102022/23122022_1/merge/job
# schedDir=/star/u/hsko/pwg/anal/Coll/isobar/ZrZrRuRu200_2018/charge/cum/effcorr/1_DetEff_light2/output/10102022/23122022_1/merge/submit

logDir= #asign log directory
schedDir= #assign scheduler directory


#dca, nhitsfit nsp, m2low, m2high, ptmax, ymax, detefflow_err, deteffhigh_err
    ./submit_schedule.sh $logDir $schedDir 10 20 20 60 120 20 5 100 100 # original
for dca_cut in 8 9 11 12
do
    ./submit_schedule.sh $logDir $schedDir $dca_cut 20 20 60 120 20 5 100 100
done
for nhitsfit_cut in 15 18 22 25
do
    ./submit_schedule.sh $logDir $schedDir 10 $nhitsfit_cut 20 60 120 20 5 100 100
done
for nsp_cut in 16 18 22 25
do
    ./submit_schedule.sh $logDir $schedDir 10 20 $nsp_cut 60 120 20 5 100 100
done
#mass cut
    ./submit_schedule.sh $logDir $schedDir 10 20 20 50 110 20 5 100 100
    ./submit_schedule.sh $logDir $schedDir 10 20 20 50 115 20 5 100 100
    ./submit_schedule.sh $logDir $schedDir 10 20 20 65 125 20 5 100 100
    ./submit_schedule.sh $logDir $schedDir 10 20 20 70 130 20 5 100 100
#det eff err: low_pt high_pt
    ./submit_schedule.sh $logDir $schedDir 10 20 20 60 120 20 5 105 105
    ./submit_schedule.sh $logDir $schedDir 10 20 20 60 120 20 5 95 95
    ./submit_schedule.sh $logDir $schedDir 10 20 20 60 120 20 5 105 95
    ./submit_schedule.sh $logDir $schedDir 10 20 20 60 120 20 5 95 105

