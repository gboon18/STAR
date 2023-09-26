#!/bin/bash

# These are examples
# outDir=/star/u/hsko/pwg/anal/Coll/isobar/ZrZrRuRu200_2018/charge/QA_tree_light2/output/net_proton/10032023/10032023_1/output/tree
# logDir=/star/u/hsko/pwg/anal/Coll/isobar/ZrZrRuRu200_2018/charge/QA_tree_light2/output/net_proton/10032023/10032023_1/job
# schedDir=/star/u/hsko/pwg/anal/Coll/isobar/ZrZrRuRu200_2018/charge/QA_tree_light2/output/net_proton/10032023/10032023_1/submitDirectory

outDir= # put your output directory here
logDir= # put your log directory here
schedDir= # put your schedule submission directory here


./submit_schedule.sh $outDir $logDir $schedDir $goodRunList
