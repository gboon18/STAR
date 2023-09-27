#!/bin/bash

outDir=/star/u/hsko/pwg/anal/Coll/isobar/ZrZrRuRu200_2018/charge/embedding/mudst/anamudst/output/27092022/27092022_1/output
logDir=/star/u/hsko/pwg/anal/Coll/isobar/ZrZrRuRu200_2018/charge/embedding/mudst/anamudst/output/27092022/27092022_1/job
schedDir=/star/u/hsko/pwg/anal/Coll/isobar/ZrZrRuRu200_2018/charge/embedding/mudst/anamudst/output/27092022/27092022_1/submit
goodRunList=/star/u/hsko/anal/Coll/isobar/ZrZrRuRu200_2018/charge/QA_tree/common_GoodRunNumbers_catalog.list

# ./submit_schedule.sh $outDir $logDir $schedDir $goodRunList

# while read runNo; do
#   # echo "$runNo"
#     ./submit_schedule.sh $outDir $logDir $schedDir $goodRunList $runNo
# done <job/CME_HoSan_GoodRunNumbers_new_count.list

# ./submit_schedule.sh $outDir $logDir $schedDir $goodRunList 19129008

#dca_cut will be divided by 10 in makeMuDstQA.C dca_cut nhitsfit_cut

# ./submit_schedule.sh $outDir $logDir $schedDir $goodRunList 10 20
# ./submit_schedule.sh $outDir $logDir $schedDir $goodRunList 30 10

./submit_schedule.sh $outDir $logDir $schedDir $goodRunList 8 20
./submit_schedule.sh $outDir $logDir $schedDir $goodRunList 9 20
./submit_schedule.sh $outDir $logDir $schedDir $goodRunList 11 20
./submit_schedule.sh $outDir $logDir $schedDir $goodRunList 12 20

./submit_schedule.sh $outDir $logDir $schedDir $goodRunList 10 15
./submit_schedule.sh $outDir $logDir $schedDir $goodRunList 10 18
./submit_schedule.sh $outDir $logDir $schedDir $goodRunList 10 22
./submit_schedule.sh $outDir $logDir $schedDir $goodRunList 10 25
