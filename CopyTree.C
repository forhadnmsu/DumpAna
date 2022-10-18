#include "cutDUMPDY.h"
void CopyTree(){
        TFile *f = TFile::Open("merged_RS67_3087all_target.root","read");
        //TFile *f = TFile::Open("data/merged_67_LD2_reWeightV4_Oct17_2022.root","read");
        //TFile *f = TFile::Open("data/combined_reweight_gmc_LD2_DY_4pi3_4_5_6_7.root","read");
        //TFile *f = TFile::Open("data/combinedall_GMC_LD2_unopt.root","read");
        //TTree *T = (TTree*)gROOT->FindObject("result_mc");
        //TTree *T = (TTree*)gROOT->FindObject("result");
        TTree *T = (TTree*)gROOT->FindObject("result_mix");
        Int_t nentries = (Int_t)T->GetEntries();
        //TFile *newfile = new TFile("data/combined_reweightGMC_LD2_DY_V4_Oct17_2022.root","recreate");
        //TFile *newfile = new TFile("data/combinedall_GMC_LD2_opt.root","recreate");
        //TFile *newfile = new TFile("merged_RS67_3087Unmixall_target.root","recreate");
        TFile *newfile = new TFile("merged_RS67_3087Mixall_target.root","recreate");
        //TTree *newtree = T->CopyTree("mass>2.8 && mass<3.20");
        TTree *newtree = T->CopyTree(basicCut);
        newtree->Print();
        newfile->Write();
        delete f;  
        delete newfile; 
}
