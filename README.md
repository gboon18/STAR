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
To study the thermodynamic properties of the matter, hadronic matter and Quark Gluon Plasma (QGP), formed in the heavy-ion collisions, we do fluctuation analysis. In this particular case, net-proton number analysis.
It is a proxy to the net-baryon number which is an collision event-by-event conserved quantity.
The fluctuation of this conserved quantity arises due to the underlying interaction and statistical nature of the interaction (partonic and/or hadronic) of the particles.
Depending on the nature of transition from the QGP to hadronic matter, i.e. is it a smooth crossover or the first-order?, the aspect of the fluctuation will be different.

- Correlation length
Correlation length si a measure of distance which physical quantities are correlated. 
QGP has longer correlation length than the hadronic matter: imagine QGP being a more homogeneous soup of partons and gluons where hadronic matter.
If the transition from the QGP to hadronic matter is smooth, the change of correlation length will also be smooth.
Near the critical point, if it exists, the correlation length is expected to diverge: checkout [critical opalescence](https://www.youtube.com/watch?v=DIGdbmJvFUw) due to increased correlation length near the critical point.

The fluctuation of the conserved quantities like net-baryon number will be present in its distribution.
![Net-proton distribution](https://github.com/gboon18/STAR/blob/main/images/net-proton_dist.png)


## Detector efficiency correction

## Centrality bin width correction (CBWC)
