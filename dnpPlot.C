# include "TGraphErrors.h"
# include "TF1.h"
# include "TLegend.h"
#include "../ana_const.h"
void dnpPlot(){
	gROOT->ForceStyle();
	//gStyle->SetTitleFontSize(0.1);
	gStyle->SetTitleSize(0.05);
	gStyle->SetLabelSize(0.07,"Y");
	gStyle->SetLabelSize(0.07,"X");
	gStyle->SetEndErrorSize(3);
	gStyle->SetErrorX(1.);
	gStyle->SetMarkerSize(1.5);
	//gStyle->SetTitleW(0.6);  //per cent of the pad width
	//gStyle->SetTitleH(0.08); //per cent of the pad height
	ostringstream oss;
	TH1D* h_pt_par_lambda = new TH1D("h_pt_par_lambda","h_pt_par_lambda", nBinpt, ptMin, ptMax);
	TH1D* h_pt_par_mu = new TH1D("h_pt_par_mu","h_pt_par_mu", nBinpt, ptMin, ptMax);
	TH1D* h_pt_par_nu = new TH1D("h_pt_par_nu","h_pt_par_nu", nBinpt, ptMin, ptMax);

	float x_lambda[6];
	float x_mu[6];
	float x_nu[6];
	float x_lambdaE[6];
	float x_muE[6];
	float x_nuE[6];

	float y_lambda[6];
	float y_mu[6];
	float y_nu[6];

	float y_lambdaE[6];
	float y_muE[6];
	float y_nuE[6];

	float min =0.;
	float max=2.5;

	TMultiGraph *mg1 = new TMultiGraph();
	mg1->SetTitle(";Dimuon pT;#lambda");
	//mg1->GetYaxis()->SetTitleOffset(0);
	TMultiGraph *mg2 = new TMultiGraph();
	mg2->SetTitle(";Dimuon pT;#mu");
	TMultiGraph *mg3 = new TMultiGraph();
	mg3->SetTitle(";Dimuon pT;#nu");

	//For NA10 experiment
	//https://link.springer.com/article/10.1007/BF01549713
	float ptBin_na10[5];
	float x_lambda_na10[5]={0.32,0.74,1.23,1.72,2.44};
	float x_mu_na10[5]={0.0,0.0,0.0,0.0,0.0};
	float x_nu_na10[5];
	float x_lambdaE_na10[5];
	float x_muE_na10[5]={0.0,0.0,0.0,0.0,0.0};
	float x_nuE_na10[5];
	float y_lambda_na10[5]={0.87,1.20,0.99,0.96,0.65}; // sqrt{s}= 16.2 
	float y_lambdaE_na10[5]={0.18,0.13,0.16,0.22,0.26}; // sqrt{s}= 16.2 
	float y_mu_na10[5]={0.060,0.003,-0.051,0.042,-0.046}; // sqrt{s}= 16.2 
	float y_muE_na10[5]={0.041,0.032,0.037,0.054,0.07}; // sqrt{s}= 16.2 
	float y_nu_na10[5]={0.002,0.079,0.074,0.184,0.150}; // sqrt{s}= 16.2 
	float y_nuE_na10[5]={0.035,0.026,0.032,0.044,0.055};// sqrt{s}= 16.2 


	auto gr_na10_lambda = new TGraphErrors(4,x_lambda_na10,y_lambda_na10,x_muE_na10,y_lambdaE_na10);
	auto gr_na10_mu = new TGraphErrors(4,x_lambda_na10, y_mu_na10,x_muE_na10,y_muE_na10);
	auto gr_na10_nu = new TGraphErrors(4,x_lambda_na10, y_nu_na10,x_muE_na10,y_nuE_na10);
	gr_na10_nu->SetName("gr_na10_nu");



	////e866 p+d
	float X_E866[4] =  { 0.30, 0.75, 1.25, 1.70 };
	float X_ERROR_E866[4] =  { 0.0, 0.0, 0.0, 0.0 };
	float LAMBDA_E866PD [4] = {1.46,0.75,1.25,1.75};
	float LAMBDA_ERR_E866PD [4] = {0.15,0.10,0.10,0.19};
	float MU_E866PD [4] = {0.03,0.003,0.03,-0.04};
	float MU_ERR_E866PD[4] = {0.03,0.03,0.05,0.05};
	float NU_E866PD[4]= { -.02, 0.04, 0.06, 0.04 };
	float NU_ERR_E866PD[4]={ 0.03, 0.02, 0.02, 0.03 };
	//adding graph
	auto gr_e866PD_lambda = new TGraphErrors(4,X_E866, LAMBDA_E866PD,X_ERROR_E866,LAMBDA_ERR_E866PD);
	auto gr_e866PD_mu = new TGraphErrors(4,X_E866, MU_E866PD,X_ERROR_E866,MU_ERR_E866PD);
	auto gr_e866PD_nu = new TGraphErrors(4,X_E866,NU_E866PD,X_ERROR_E866,NU_ERR_E866PD);
	//==================

        //E615: https://journals.aps.org/prd/pdf/10.1103/PhysRevD.39.92
        const int N_E615 = 6;
        float PT_E615 [N_E615] = { 0.25, 0.75, 1.25, 1.75, 2.25, 2.75 };
        float PT_E615E [N_E615] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
        float LAMBDA_E615 [N_E615] = {1.10,1.19,1.32,1.04,0.91,1.29};
        float LAMBDA_ERR_E615 [N_E615] = {0.13,0.12,0.13,0.17,0.33,0.39};
        float MU_E615 [N_E615] = {0.05, 0.09, 0.16, 0.08, 0.29,0.37};
        float MU_ERR_E615[N_E615] = {0.03,0.04,0.04,0.05, 0.15, 0.24};
        float NU_E615 [N_E615] = { 0.030, 0.139, 0.311, 0.230, 0.430, 0.731 };
        float NU_ERR_E615[N_E615] = { 0.041, 0.030, 0.042, 0.061, 0.189, 0.291 };
	//Adding graphs
	auto gr_e615_lambda = new TGraphErrors(6,PT_E615, LAMBDA_E615,PT_E615E,LAMBDA_ERR_E615);
	auto gr_e615_mu = new TGraphErrors(6,PT_E615, MU_E615,PT_E615E,MU_ERR_E615);
	auto gr_e615_nu = new TGraphErrors(6,PT_E615, NU_E615,PT_E615E,NU_ERR_E615);

	//SeaQuest
        const int N_E906 = 4;
        float x_sea=0.0;
        float x_sea_e=0.4;
        float PT_E906 [N_E906] = { 0.25, 0.75, 1.25, 1.75 };
        float PT_E906E[N_E906] = {x_sea,x_sea,x_sea,x_sea};
        float XERROR_E906 [N_E906] = {x_sea_e,x_sea_e,x_sea_e,x_sea_e};
        float LAMBDA_ERR_E906 [N_E906] = {0.17,0.13,0.16,0.24};
        float MU_ERR_E906[N_E906] = {0.03,0.04,0.04,0.05};
        float NU_ERR_E906[N_E906] = { 0.041, 0.030, 0.042, 0.061 };
	//Adding graphs
	auto gr_e906_lambda = new TGraphErrors(4,PT_E906, XERROR_E906,PT_E906E,LAMBDA_ERR_E906);
	auto gr_e906_mu = new TGraphErrors(4,PT_E906,XERROR_E906,PT_E906E,MU_ERR_E906);
	auto gr_e906_nu = new TGraphErrors(4,PT_E906,XERROR_E906,PT_E906E,NU_ERR_E906);	


	//gr_na10_nu->GetXaxis()->SetLimits(0.0,2.0);
	//gr_e866PD_lambda->GetXaxis()->SetLimits(0.0,2.0);
	//gr_na10_mu->GetXaxis()->SetLimits(0.0,2.0);
	gr_na10_lambda->SetName("gr_na10_lambda");
	gr_e615_lambda->SetName("gr_e615_lambda");
	gr_e906_lambda->SetName("gr_e906_lambda");
	gr_e866PD_lambda->SetName("gr_e866PD_lambda");
	gr_e866PD_nu->SetName("gr_e866PD_nu");
	gr_na10_mu->SetName("gr_na10_mu");

	TCanvas * c = new TCanvas("c", "c",800,1000);
	c->Divide(1,3,0,0);
	c->cd(1);
	gr_na10_lambda->SetMarkerStyle(20);
	gr_na10_lambda->SetMarkerColor(kRed);
	gr_e615_lambda->SetMarkerStyle(48);
	gr_e615_lambda->SetMarkerSize(1.3);
	gr_e615_lambda->SetMarkerColor(kBlack);
	gr_e906_lambda->SetMarkerStyle(20);
	gr_e906_lambda->SetMarkerColor(kBlue);
	gr_e866PD_lambda->SetMarkerStyle(20);

	mg1->Add(gr_e866PD_lambda);
	mg1->Add(gr_na10_lambda);
	mg1->Add(gr_e615_lambda);
	mg1->Add(gr_e906_lambda);
	mg1->Draw("AP");
	auto leg = new TLegend(0.1,1.0,0.48,0.85);
	leg->AddEntry("gr_e615_lambda","E615 (#pi^{-} + W) @252GeV","p");
	leg->AddEntry("gr_na10_lambda","NA10 (#pi^{-} + W) @140GeV" ,"p");
	leg->AddEntry("gr_e906_lambda","E906 (p + dump) @120GeV","p");
	leg->AddEntry("gr_e866PD_lambda","E866 (p + d) @800GeV","p");
	leg ->Draw();
	c->cd(2);
	gr_na10_mu->SetMarkerColor(kRed);
	gr_na10_mu->SetMarkerStyle(20);

	gr_e615_mu->SetMarkerStyle(48);
	gr_e615_mu->SetMarkerSize(1.3);
	gr_e615_mu->SetMarkerColor(kBlack);

	gr_e866PD_mu->SetMarkerColor(kBlack);
	gr_e866PD_mu->SetMarkerStyle(20);

	gr_e906_mu->SetMarkerStyle(20);
	gr_e906_mu->SetMarkerColor(kBlue);

	mg2->Add(gr_na10_mu);
	mg2->Add(gr_e866PD_mu);
	mg2->Add(gr_e615_mu);
	mg2->Add(gr_e906_mu);
	mg2->Draw("AP");

	c->cd(3);
	gr_na10_nu->SetMarkerColor(kRed);
	gr_na10_nu->SetMarkerStyle(20);

	gr_e615_nu->SetMarkerStyle(48);
	gr_e615_nu->SetMarkerSize(1.3);
	gr_e615_nu->SetMarkerColor(kBlack);

	gr_e866PD_nu->SetMarkerColor(kBlack);
	gr_e866PD_nu->SetMarkerStyle(20);

	gr_e906_nu->SetMarkerStyle(20);
	gr_e906_nu->SetMarkerColor(kBlue);

	mg3->Add(gr_na10_nu);
	mg3->Add(gr_e866PD_nu);
	mg3->Add(gr_e615_nu);
	mg3->Add(gr_e906_nu);
	mg3->Draw("AP");
	c->SaveAs("plot/lambda.png");
	return c;
}
