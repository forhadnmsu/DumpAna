#ifndef _ANA_CONSTANTS_H
#define _ANA_CONSTANTS_H	
//global variables and binning
        Int_t nBinCosth = 14; 
        Double_t costhMin = -0.5;
        Double_t costhMax = 0.5;

        Int_t nBinPhi = 14; 
        //Double_t phiMin = -M_PI;
        Double_t phiMin = -M_PI;
        Double_t phiMax = M_PI;

        int nBinpt = 4;
        Double_t ptMin = 0.00;
        Double_t ptMax = 2.00;

        int nBinxF = 1;
        Double_t xFMin = 0.00;
        Double_t xFMax = 1.00;

        int nBinx2 = 1;
        Double_t x2Min = 0.00;
        Double_t x2Max = 1.0;

        int nBinMass = 20;
        Double_t MassMin = 5.0;
        Double_t MassMax = 8.00;

	int nBinD1 =6;
	int range_D1=50;


//        double mass_low = 4.5;
//        double mass_high = 8.0;
//        int event_thrs_in_each_Mhist =5;
#endif
