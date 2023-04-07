# STAR Zr+Zr and Ru+Ru collisions data analysis
## Collision event-by-event net-proton number fluctuation analysis code.

## Table of contents

- [Quick start](#quick-start)
- [Net-proton number fluctuation] (#net-proton-number-fluctuation)
- [Detector efficiency correction] (#detector-efficiency-correction)
- [Centrality bin width correction] (#centrality-bin-width-correction)

## Quick start
This program requires c++11 and CERN ROOT [v6.22/06](https://root.cern/releases/release-62206/).
At this stage, we have collected proton and anti-proton tracks from the STAR detector at the Relativisitic Heavy-Ion Collider at Brookhaven National Laboratory.
We have taken into account the particle track detection efficiency.
The calculations are done in [calcum](https://github.com/gboon18/STAR/tree/main/calcum) directory.
The CalCum.cpp calculates the cumulants up to the sixth order.
Cum.cpp fills the cumculants to the histogram in the event multiplicity bin and merge the multiplicity bins to several centrality with the centrality bin widht correction (CWBC).
First, let's clone the code 
```sh
git clone https://github.com/gboon18/STAR.git
```
then run
```sh
./Cum.sh
```

After the calculations are don in [calcum](https://github.com/gboon18/STAR/tree/main/calcum) directory, we move to the plot directory to plot the results.


## Net-proton number fluctuation

## Detector efficiency correction

## Centrality bin width correction (CBWC)
