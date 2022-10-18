# DumpAna

A program to analize the final step of the dump Data analysis at SeaQuest. 

## Analysis Flow

1. CopyTree.C -> This macro uses the track, and dimuon label event selections, and maake the data-file smaller. The cuts are used from `cutDUMPDY.h`. 

2. getAccFactor.C-> Uses the all event seelections that are considered for the reconstructions and optimization cut. Using these all event selections, it generates a root file which has 2D accpetance factor histograms. 

3. mainDumpAna.C -> is used to consider the same event selections that are used to generate the acceptance factor histogram. After the event selections, we  subtract the combinatorial background (unmix events) here, and then create phi_{CS}-cos\theta_{CS} 2D histograms. And, finally, we apply a 2D fit to extract the angular distribtuions paramters. 
