#!/bin/bash

#Runs  Analysis.xml and converts picoDsts from catalog query to femtoDsts

outDir=$1
logDir=$2
schedDir=$3

#Check to make sure there are the right number of arguments
if [ "$#" -ne 3 ]; then
    echo "ERROR: Incorrect number of arguments! This script needs four: outputDir logDir schedDir goodRunsList"
    exit 1
fi

#Check to Make sure the output Directory exists
if [ ! -d $outDir ]; then
    echo "ERROR: Output Directory $outDir does not exist!"
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

star-submit-template -template  Analysis.xml -entities logDir=$logDir,outDir=$outDir,schedDir=$schedDir
