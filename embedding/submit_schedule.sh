#!/bin/bash

#Runs  Analysis.xml and converts picoDsts from catalog query to femtoDsts

outDir=$1
logDir=$2
schedDir=$3
goodRunList=$4 # probably should be filelist/GoodRuns.txt
dca_cut=$5
nhitsfit_cut=$6

#Check to make sure there are the right number of arguments
if [ "$#" -ne 6 ]; then
    echo "ERROR: Incorrect number of arguments! This script needs six: outputDir logDir schedDir goodRunsList dca_cut nhitsfit_cut"
    exit 1
fi

#Check to Make sure the output Directory exists
if [ ! -d $outDir ]; then
    echo "ERROR: Output Directory $outDir does not exist!"
    exit 1
fi

#Check to make sure that the inputFileList exists 
if [ ! -e $goodRunList ]; then
    echo "ERROR: Input file list $goodRunList does not exist!"
    exit 1
fi

#Check that the log directory exists, if not make it
if [ ! -d $logDir ]; then
    echo "Creating the log directory $logDir"
    mkdir $logDir
fi

#Check that the scheduler directory exists, if not make it
if [ ! -d $schedDir ]; then
    echo "Creating the scheduler directory $schedDir"
    mkdir $schedDir
fi

# echo $logDir $goodRunList $outDir $schedDir $dca_cut $nhitsfit_cut $thisNameRuZr
star-submit-template -template  Analysis_Proton_Ru.xml -entities logDir=$logDir,goodRunList=$goodRunList,outDir=$outDir,schedDir=$schedDir,dca_cut=$dca_cut,nhitsfit_cut=$nhitsfit_cut,thisNameRuZr="Ru"
star-submit-template -template  Analysis_AntiProton_Ru.xml -entities logDir=$logDir,goodRunList=$goodRunList,outDir=$outDir,schedDir=$schedDir,dca_cut=$dca_cut,nhitsfit_cut=$nhitsfit_cut,thisNameRuZr="Ru"
star-submit-template -template  Analysis_Proton_Zr.xml -entities logDir=$logDir,goodRunList=$goodRunList,outDir=$outDir,schedDir=$schedDir,dca_cut=$dca_cut,nhitsfit_cut=$nhitsfit_cut,thisNameRuZr="Zr"
star-submit-template -template  Analysis_AntiProton_Zr.xml -entities logDir=$logDir,goodRunList=$goodRunList,outDir=$outDir,schedDir=$schedDir,dca_cut=$dca_cut,nhitsfit_cut=$nhitsfit_cut,thisNameRuZr="Zr"
# star-submit-template -template  Analysis_Piplus_Ru.xml -entities logDir=$logDir,goodRunList=$goodRunList,outDir=$outDir,schedDir=$schedDir,dca_cut=$dca_cut,nhitsfit_cut=$nhitsfit_cut,thisNameRuZr="Ru"
# star-submit-template -template  Analysis_Piplus_Zr.xml -entities logDir=$logDir,goodRunList=$goodRunList,outDir=$outDir,schedDir=$schedDir,dca_cut=$dca_cut,nhitsfit_cut=$nhitsfit_cut,thisNameRuZr="Zr"
# star-submit-template -template  Analysis_Kplus_Ru.xml -entities logDir=$logDir,goodRunList=$goodRunList,outDir=$outDir,schedDir=$schedDir,dca_cut=$dca_cut,nhitsfit_cut=$nhitsfit_cut,thisNameRuZr="Ru"
# star-submit-template -template  Analysis_Kplus_Zr.xml -entities logDir=$logDir,goodRunList=$goodRunList,outDir=$outDir,schedDir=$schedDir,dca_cut=$dca_cut,nhitsfit_cut=$nhitsfit_cut,thisNameRuZr="Zr"
# star-submit-template -template  Analysis_Piminus_Ru.xml -entities logDir=$logDir,goodRunList=$goodRunList,outDir=$outDir,schedDir=$schedDir,dca_cut=$dca_cut,nhitsfit_cut=$nhitsfit_cut,thisNameRuZr="Ru"
# star-submit-template -template  Analysis_Piminus_Zr.xml -entities logDir=$logDir,goodRunList=$goodRunList,outDir=$outDir,schedDir=$schedDir,dca_cut=$dca_cut,nhitsfit_cut=$nhitsfit_cut,thisNameRuZr="Zr"
# star-submit-template -template  Analysis_Kminus_Ru.xml -entities logDir=$logDir,goodRunList=$goodRunList,outDir=$outDir,schedDir=$schedDir,dca_cut=$dca_cut,nhitsfit_cut=$nhitsfit_cut,thisNameRuZr="Ru"
# star-submit-template -template  Analysis_Kminus_Zr.xml -entities logDir=$logDir,goodRunList=$goodRunList,outDir=$outDir,schedDir=$schedDir,dca_cut=$dca_cut,nhitsfit_cut=$nhitsfit_cut,thisNameRuZr="Zr"
