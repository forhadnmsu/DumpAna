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
void mainDumpAna() {
	gROOT->ForceStyle();
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(1);
	ROOT::EnableImplicitMT();
	TH1::SetDefaultSumw2();
	TH2::SetDefaultSumw2();
	gStyle->SetPalette(1);
	///////////////////////////////
	ROOT::RDataFrame dmyDf_mc("result_mc", "combined_LD2_DUMP_67_GMC.root"); 
	ROOT::RDataFrame dmyDf_data("result", "merged_RS67_3087all_target.root"); 
	ROOT::RDataFrame dmyDf_mix("result_mix", "merged_RS67_3087all_target.root"); 
	TH1D* h_pt = new TH1D("h_pt","h_pt", nBinpt, ptMin, ptMax);
	TH1D* h_x2 = new TH1D("h_x2","h_x2", nBinx2, x2Min, x2Max);
	gStyle->SetOptStat("0");
	TCanvas* c1 = new TCanvas("c1","c1",1200,1600);
	//c1->Divide(2,1);
	c1->Divide(2,4);
	TFile *myfile = TFile::Open("acc_factor.root","read");
	TF2* fit2D = new TF2("fit2D", "[0] * ( 1 + [1]*y*y + 2*[2]*sqrt(1-y*y)*y*cos(x) + [3]*(1-y*y)*cos(2*x)/2.) ", -M_PI, M_PI, -0.5, 0.5);
	fit2D->SetParameters(1,1,0,0);
	fit2D->SetParNames("A", "#lambda","#mu","#nu");
	for (int i_xT = 1; i_xT <=nBinx2 ; i_xT++) {
		for (int i_pt = 1; i_pt <=nBinpt ; i_pt++) {
			Double_t xBinMinPt = h_pt->GetXaxis()->GetBinLowEdge(i_pt);
			Double_t xBinMaxPt = h_pt->GetXaxis()->GetBinUpEdge(i_pt);
			Double_t xBinMinx2 = h_x2->GetXaxis()->GetBinLowEdge(i_xT);
			Double_t xBinMax2 = h_x2->GetXaxis()->GetBinUpEdge(i_xT);
			//RDATAFRAME
			string  ptCutTrue = Form("true_pT>%4.10f&&true_pT<%4.10f&&",xBinMinPt,xBinMaxPt);
			string trigCut ="fpga1==1&&";
			string massCut = "true_mass>5.0 && true_mass<8.0";
			string filter_mc_4pi=ptCutTrue+massCut; // 4 pi mc filter 
			string filter_mc_reco=ptCutTrue+trigCut+massCut+"&&"+dumpCutRD; // reco mc filter
											//Data
			string pTBins= Form("pT>%4.10f&&pT<%4.10f&&",xBinMinPt,xBinMaxPt);
			string xTBins=  Form("xT>%4.10f&&xT<%4.10f&&",xBinMinx2,xBinMax2);
			string massRange=" mass>5.0 && mass<8.0&&";
			string final_cut_filter=pTBins+xTBins+massRange+dumpCutRD; // data filter 

			auto hist2d_unmix = dmyDf_data.Filter(final_cut_filter).Define("phi_","phi").Define("costh_","costh").Histo2D({"phi_theta_unmix", "phi_theta_unmix", nBinPhi,phiMin, phiMax, nBinCosth, costhMin, costhMax}, "phi_", "costh_");
			auto hist2d_mix = dmyDf_mix.Filter(final_cut_filter).Define("phi_","phi").Define("costh_","costh").Histo2D({"phi_theta_mix", "phi_theta_mix", nBinPhi,phiMin, phiMax, nBinCosth, costhMin, costhMax},"phi_", "costh_");
			TH2D* acc_factor = (TH2D*)myfile->Get(Form("h2_phi_costh_ixT_%i_ipt_%i",i_xT ,i_pt));
			hist2d_unmix->Add(hist2d_mix.GetPtr(),-1);
			cout <<"Integrated signal count: "<< hist2d_unmix->Integral()<<endl;
			hist2d_unmix->SetName(Form("phi_theta_ipT%i",i_pt));
			TH2*h2_phi_costh = (TH2D*)hist2d_unmix->Clone();
			int can = (2*i_pt-1); 
			c1->cd(can);	
			h2_phi_costh->Draw("colz E text");
			h2_phi_costh->SetTitle(Form("(Unmix -Mix) Events in pT_{low}=%4.2f and pT_{high}=%4.2f ;#phi_{CS};cos#theta_{CS}",xBinMinPt,xBinMaxPt));
			can++;
			c1->cd(can);
			TH2*acc_corrected_h2d = (TH2D*)h2_phi_costh->Clone();
			acc_corrected_h2d->Divide(acc_factor);
			/*			bool fitOK = false;
						while( ! fitOK ){
						acc_corrected_h2d->Fit("fit2D");
						double tempChisq = fit2D->GetChisquare() / fit2D->GetNDF();
						fitOK = tempChisq < 3.0 ? true : false;
						}

			 */			 
			acc_corrected_h2d->Fit("fit2D");
			cout << fit2D->GetChisquare() / fit2D->GetNDF() << endl;
			acc_corrected_h2d->SetTitle(Form("Acc. corrected in pT_{low}=%4.2f and pT_{high}=%4.2f ;#phi_{CS};cos#theta_{CS}",xBinMinPt,xBinMaxPt));
			acc_corrected_h2d->Draw("colz");
			if(can==8)c1->SaveAs("acc_corrected.pdf");
			delete acc_factor;
		}
	}
}
