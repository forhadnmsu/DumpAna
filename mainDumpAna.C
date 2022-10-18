#include <iostream>
#include <sstream>
#include "TH2D.h"
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
TH2D * ResetEmptyBins(
                        const char* hname,
                         TH2D* h_phi_costh )
 {   
	int nbinX = h_phi_costh->GetNbinsX();
	int nbinY = h_phi_costh->GetNbinsY();
	TH2D *h = (TH2D*)h_phi_costh->Clone();
	for (int ii=1; ii<= nbinX; ii++){
		for (int jj=1; jj<= nbinY; jj++){

			if(h_phi_costh->GetBinContent(ii,jj) <=5){
				h->SetBinContent(ii,jj,0);
				h->SetBinError(ii,jj,0);
			};
		}
	}
	return h;
}

void mainDumpAna() {
	gROOT->ForceStyle();
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(1);
	ROOT::EnableImplicitMT();
	TH1::SetDefaultSumw2();
	TH2::SetDefaultSumw2();
	gStyle->SetPalette(1);
	///////////////////////////////
	ROOT::RDataFrame dmyDf_data("result", "merged_RS67_3087Unmixall_target.root"); 
	ROOT::RDataFrame dmyDf_mix("result_mix", "merged_RS67_3087Mixall_target.root"); 
	std::ofstream out_File;
	std::ofstream out_File2;
	out_File.open("err.csv");
	out_File2.open("err2.csv");
	//ROOT::RDataFrame dmyDf_data("result", "merged_RS67_3089LD2.root"); 
	//ROOT::RDataFrame dmyDf_mix("result_mix", "merged_RS67_3089LD2.root"); 
	//out_File<< "pT low "<< " and pT high,"<<"D1 low and " << "D1 high"<<endl;
	TH1D* h_pt = new TH1D("h_pt","h_pt", nBinpt, ptMin, ptMax);
	TH1D* h_x2 = new TH1D("h_x2","h_x2", nBinx2, x2Min, x2Max);
	TH1D* h_D1 = new TH1D("h_D1","h_D1", 4, 0, 280);
	gStyle->SetOptStat("0");
	TCanvas* c1 = new TCanvas("c1","c1",1200,2400);
	//c1->Divide(2,1);
	c1->Divide(2,6);
	TFile *myfile = TFile::Open("acc_factor.root","read");
	TF2* fit2D = new TF2("fit2D", "[0] * ( 1 + [1]*y*y + 2*[2]*sqrt(1-y*y)*y*cos(x) + [3]*(1-y*y)*cos(2*x)/2.) ", -M_PI, M_PI, costhMin, costhMax);
	fit2D->SetParameters(1,1,0,0);
	fit2D->SetParNames("A", "#lambda","#mu","#nu");
	int can =0;

	out_File2<<"lambda,lambdae,mu,mue,nu,nue,chiNDF"<<endl;
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
				string  ptCutTrue = Form("true_pT>%4.10f&&true_pT<%4.10f&&",xBinMinPt,xBinMaxPt);
				string  occu =Form ("D1>%i&&D1<%i&&",D1_low,D1_high);
				//string massCut = "true_mass>5.0 && true_mass<8.0";
				string massCut = Form("true_mass>%f && true_mass<%f",MassMin, MassMax);
				string pTBins= Form("pT>%4.10f&&pT<%4.10f&&",xBinMinPt,xBinMaxPt);
				string xTBins=  Form("xT>%4.10f&&xT<%4.10f&&",xBinMinx2,xBinMax2);
				//string massRange=" mass>5.0 && mass<8.0&&";
				string massRange=Form(" mass>%f && mass<%f&&",MassMin, MassMax);
				string final_cut_filter=occu+pTBins+xTBins+massRange+dumpCutRD; // data filter 
				cout << "cut in data: "<< final_cut_filter << endl;

				auto hist2d_unmix = dmyDf_data.Filter(final_cut_filter).Define("phi_","phi").Define("costh_","costh").Histo2D({"phi_theta_unmix", "phi_theta_unmix", nBinPhi,phiMin, phiMax, nBinCosth, costhMin, costhMax}, "phi_", "costh_");
				auto hist2d_mix = dmyDf_mix.Filter(final_cut_filter).Define("phi_","phi").Define("costh_","costh").Histo2D({"phi_theta_mix", "phi_theta_mix", nBinPhi,phiMin, phiMax, nBinCosth, costhMin, costhMax},"phi_", "costh_");
				TH2D* acc_factor = (TH2D*)myfile->Get(Form("h2_phi_costh_ixT_%i_ipt_%i_iD1_%i",i_xT ,i_pt, i_D1));
				hist2d_unmix->Add(hist2d_mix.GetPtr(),-1);
				cout <<"Integrated signal count: "<< hist2d_unmix->Integral()<<endl;
				hist2d_unmix->SetName(Form("phi_theta_ipT%i_i_D1_%i",i_pt,i_D1));
				TH2D*h2_phi_costh = ResetEmptyBins("h2_phi_costh",hist2d_unmix.GetPtr());
				//TH2D*h2_phi_costh = (TH2D*)hist2d_unmix->Clone();
				int analized_data = h2_phi_costh->Integral();
				out_File <<setprecision(4)<< analized_data<< "&"<< Form("$%i<D1<%i$& $%4.2f<pT<%4.2f$",D1_low,D1_high,xBinMinPt,xBinMaxPt)<<"&";
				//out_File2 << setprecision(4) <<Form("$%i<D1<%i$, $%4.2f<pT<%4.2f$",D1_low,D1_high,xBinMinPt,xBinMaxPt)<<",";
				can++;
				c1->cd(can);	
				h2_phi_costh->Draw("colz E text");
				h2_phi_costh->SetTitle(Form("(Unmix -Mix) Events in  pT_{low}=%4.2f and pT_{high}=%4.2f  and D1_{low}=%i&&D1_{high}=%i ;#phi_{CS};cos#theta_{CS}",xBinMinPt,xBinMaxPt, D1_low,D1_high));
				can++;
				c1->cd(can);
				TH2*acc_corrected_h2d = (TH2D*)h2_phi_costh->Clone();
				//TH2D*acc_corrected_h2d = ResetEmptyBins("acc_corrected_h2d",h2_phi_costh);	
				acc_corrected_h2d->Divide(acc_factor);
				/*
				   bool fitOK = false;
				   while( ! fitOK ){
				   acc_corrected_h2d->Fit("fit2D","M");
				   double tempChisq = fit2D->GetChisquare() / fit2D->GetNDF();
				   fitOK = tempChisq < 16.0 ? true : false;
				   }
				 */
				acc_corrected_h2d->Fit("fit2D");
				std::setprecision(4);
				cout << fit2D->GetChisquare() / fit2D->GetNDF() << endl;
				out_File << fit2D->GetParameter(1) <<"&"<< fit2D->GetParError(1) <<"&"<<fit2D->GetParameter(2) <<"&"<< fit2D->GetParError(2) <<"&"<<fit2D->GetParameter(3) << "&"<< fit2D->GetParError(3) <<"&"<< fit2D->GetChisquare() / fit2D->GetNDF() <<"\\" <<endl;
				out_File2 << fit2D->GetParameter(1) <<","<< fit2D->GetParError(1) <<","<<fit2D->GetParameter(2) <<","<< fit2D->GetParError(2) <<","<<fit2D->GetParameter(3) << ","<< fit2D->GetParError(3) <<","<< fit2D->GetChisquare() / fit2D->GetNDF() <<endl;
				acc_corrected_h2d->SetTitle(Form("Acc. corrected in pT_{low}=%4.2f and pT_{high}=%4.2f  and D1_{low}=%i&&D1_{high}=%i ;#phi_{CS};cos#theta_{CS}",xBinMinPt,xBinMaxPt, D1_low,D1_high));
				acc_corrected_h2d->Draw("colz");
				if(can==12){
					c1->SaveAs(Form("plot/acc_corrected_iPT_%i.pdf",i_pt));
					can=0;
				}
				delete acc_factor;
			}
		}
	}
	out_File.close();
	out_File2.close();
}
