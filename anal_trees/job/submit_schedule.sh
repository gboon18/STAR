#!/bin/bash

#Runs  Analysis.xml and converts picoDsts from catalog query to femtoDsts

logDir=$1
schedDir=$2
dca_cut=$3
nhitsfit_cut=$4
nsp_cut=$5
m2low_cut=$6
m2up_cut=$7
ptmax_cut=$8
ymax_cut=$9
detefflow_err=${10}
deteffhigh_err=${11}

#Check to make sure there are the right number of arguments
if [ "$#" -ne 11 ]; then
    echo "ERROR: Incorrect number of arguments! This script needs four: logDir schedDir dca_cut nhitsfit_cut nsp_cut m2low_cut m2up_cut"
    echo $logDir $schedDir $dca_cut $nhitsfit_cut $nsp_cut $m2low_cut $m2up_cut $ptmax_cut $ymax_cut $detefflow_err $deteffhigh_err
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

# echo $logDir $goodRunList $outDir $schedDir $runNo $dca_cut $nhitsfit_cut $nsp_cut $m2low_cut $m2up_cut
star-submit-template -template  Analysis_ref3StPicoEvt_corr_Ru.xml -entities logDir=$logDir,schedDir=$schedDir,dca_cut=$dca_cut,nhitsfit_cut=$nhitsfit_cut,nsp_cut=$nsp_cut,m2low_cut=$m2low_cut,m2up_cut=$m2up_cut,ptmax_cut=$ptmax_cut,ymax_cut=$ymax_cut,detefflow_err=$detefflow_err,deteffhigh_err=$deteffhigh_err
star-submit-template -template  Analysis_ref3StPicoEvt_corr_Zr.xml -entities logDir=$logDir,schedDir=$schedDir,dca_cut=$dca_cut,nhitsfit_cut=$nhitsfit_cut,nsp_cut=$nsp_cut,m2low_cut=$m2low_cut,m2up_cut=$m2up_cut,ptmax_cut=$ptmax_cut,ymax_cut=$ymax_cut,detefflow_err=$detefflow_err,deteffhigh_err=$deteffhigh_err
