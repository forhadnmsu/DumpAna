#include <iostream>
#include <sstream>
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"
#include <TStyle.h>
#include"TCanvas.h"
#include "TCut.h"
#include "TLegend.h"
#include "TLine.h"
#include "TLatex.h"
#include "TMarker.h"
#include "ana_const.h"
#include "cutDUMPDY.h"
using namespace std;
void getAccFactor() {
	TH1::SetDefaultSumw2();
	TH2::SetDefaultSumw2();
	gStyle->SetPalette(1);
	ROOT::EnableImplicitMT();
	///////////////////////////////
	//ROOT::RDataFrame dmyDf_mc("result_mc", "data/combined.root"); 
	ROOT::RDataFrame dmyDf_mc("result_mc", "data/combinedall_GMC_LD2_opt.root"); 
	//ROOT::RDataFrame dmyDf_mc("result_mc", "data/combined_reweightGMC_LD2_DY_4pi3_4_5_6_7.root"); 
	//ROOT::RDataFrame dmyDf_mc("result_mc", "data/combined_reweightGMC_LD2_DY_V4_Oct17_2022.root"); 
	ROOT::RDataFrame dmyDf_mc2("result_mc", "data/combined_reweight_gmc_LD2_DY_4pi.root"); 
	TH1D* h_pt = new TH1D("h_pt","h_pt", nBinpt, ptMin, ptMax);
	TH1D* h_x2 = new TH1D("h_x2","h_x2", nBinx2, x2Min, x2Max);
	gStyle->SetOptStat("0");
	TCanvas* c1 = new TCanvas("c1","c1",600,1200);
	c1->Divide(1,2);
	TFile *myfile = new TFile("acc_factor.root","recreate");
	TF2* fit2D = new TF2("fit2D", "[0] * ( 1 + [1]*y*y + 2*[2]*sqrt(1-y*y)*y*cos(x) + [3]*(1-y*y)*cos(2*x)/2.) ", -M_PI, M_PI, costhMin, costhMax);
	for (int i_xT = 1; i_xT <=nBinx2 ; i_xT++) {
		for (int i_pt = 1; i_pt <=nBinpt ; i_pt++) {
			for (int i_D1 = 1; i_D1 <=nBinD1 ; i_D1++) {
				Double_t xBinMinPt = h_pt->GetXaxis()->GetBinLowEdge(i_pt);
				Double_t xBinMaxPt = h_pt->GetXaxis()->GetBinUpEdge(i_pt);
				Double_t xBinMinx2 = h_x2->GetXaxis()->GetBinLowEdge(i_xT);
				Double_t xBinMax2 = h_x2->GetXaxis()->GetBinUpEdge(i_xT);
				//RDATAFRAME
				int D1_low = range_D1*(i_D1-1);
				int D1_high = range_D1*i_D1;
				string  occu =Form ("D1>%i&&D1<%i&&",D1_low,D1_high);
				string  ptCutTrue = Form("true_pT>%4.10f&&true_pT<%4.10f&&",xBinMinPt,xBinMaxPt);
				string trigCut ="fpga1==1&&";
				string massCut = Form("true_mass>%f && true_mass<%f",MassMin, MassMax);
				string massRange = Form("mass>%f && mass<%f&&",MassMin, MassMax);
				string filter_mc_4pi=ptCutTrue+massCut; // 4 pi mc filter 
				string pTBins= Form("pT>%4.10f&&pT<%4.10f&&",xBinMinPt,xBinMaxPt);
				string xTBins=  Form("xT>%4.10f&&xT<%4.10f&&",xBinMinx2,xBinMax2);
				string filter_mc_reco=occu +massCut+"&&"+pTBins+xTBins+massRange+trigCut+dumpCutRD; // reco mc filter
				cout << "true cut "<< filter_mc_4pi << endl;
				cout << "reco cut "<< filter_mc_reco << endl;
				//auto hist2d_mc_4pi = dmyDf_mc2.Filter(filter_mc_4pi).Define("phi_mc_4pi","true_phi").Define("costh_mc_4pi","true_costh").Histo2D({"phi_theta_mc_4pi", "phi_theta_mc_4pi", nBinPhi,phiMin, phiMax, nBinCosth, costhMin, costhMax},"phi_mc_4pi", "costh_mc_4pi","reweight_pt");
				//auto hist2d_mc_reco = dmyDf_mc.Filter(filter_mc_reco).Define("phi_mc_reco","phi").Define("costh_mc_reco","costh").Histo2D({"phi_theta_mc_reco", "phi_theta_mc_reco", nBinPhi,phiMin, phiMax, nBinCosth, costhMin, costhMax},"phi_mc_reco", "costh_mc_reco","reweight_pt");

				auto hist2d_mc_4pi = dmyDf_mc2.Filter(filter_mc_4pi).Define("phi_mc_4pi","true_phi").Define("costh_mc_4pi","true_costh").Histo2D({"phi_theta_mc_4pi", "phi_theta_mc_4pi", nBinPhi,phiMin, phiMax, nBinCosth, costhMin, costhMax},"phi_mc_4pi", "costh_mc_4pi","weight");
				auto hist2d_mc_reco = dmyDf_mc.Filter(filter_mc_reco).Define("phi_mc_reco","phi").Define("costh_mc_reco","costh").Histo2D({"phi_theta_mc_reco", "phi_theta_mc_reco", nBinPhi,phiMin, phiMax, nBinCosth, costhMin, costhMax},"phi_mc_reco", "costh_mc_reco","weight");

				cout <<" entries 4pi:  " <<hist2d_mc_4pi->GetEntries(); 
				cout <<" entries reco: " <<hist2d_mc_reco->GetEntries(); 
				hist2d_mc_4pi->Scale(1./hist2d_mc_4pi->Integral()); 
				TH2*acc_factor = (TH2D*)hist2d_mc_reco->Clone();
				acc_factor->Divide(hist2d_mc_4pi.GetPtr());
				acc_factor->Scale(1./acc_factor->Integral()); 
				c1->cd();
				acc_factor->Draw("colz E text");
				char name[20];
				sprintf(name, "%s%d%s%d%s%i","h2_phi_costh_ixT_",i_xT,"_ipt_",i_pt,"_iD1_",i_D1);

				cout << "name: "<< name << endl;
				TH2D* h = (TH2D*)acc_factor->Clone();    
				h->SetName(name); h->Write(name,TObject::kWriteDelete);
			}
		}
	}
	myfile->Close();
	myfile->ls();
}
