#!/bin/bash

#Runs  Analysis.xml and converts picoDsts from catalog query to femtoDsts

logDir=$1
schedDir=$2
runNo=$3
dca_cut=$4
nhitsfit_cut=$5
nsp_cut=$6
m2low_cut=$7
m2up_cut=$8
ptmax_cut=$9
ymax_cut=${10}
detefflow_err=${11}
deteffhigh_err=${12}

#Check to make sure there are the right number of arguments
if [ "$#" -ne 12 ]; then
    echo "$# ERROR: Incorrect number of arguments! This script needs fourteen: logDir schedDir goodRunsList runNo dca_cut nhitsfit_cut nsp_cut m2low_cut m2up_cut detefflow_err deteffhigh_err"
    echo $logDir $schedDir $runNo $dca_cut $nhitsfit_cut $nsp_cut $m2low_cut $m2up_cut $ptmax_cut $ymax_cut $detefflow_err $deteffhigh_err
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

# echo $logDir $schedDir $runNo $dca_cut $nhitsfit_cut $nsp_cut $m2low_cut $m2up_cut $ptmax_cut $ymax_cut $detefflow_err $deteffhigh_err
star-submit-template -template  Analysis.xml -entities logDir=$logDir,schedDir=$schedDir,runNo=$runNo,dca_cut=$dca_cut,nhitsfit_cut=$nhitsfit_cut,nsp_cut=$nsp_cut,m2low_cut=$m2low_cut,m2up_cut=$m2up_cut,ptmax_cut=$ptmax_cut,ymax_cut=$ymax_cut,detefflow_err=$detefflow_err,deteffhigh_err=$deteffhigh_err
