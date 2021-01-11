#include "TCanvas.h"
#include "TROOT.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TH1F.h"   
#include "TLegend.h"
#include "TFile.h"  
#include "TArrow.h"
#include "TLatex.h"
#include "TMath.h"
#include "TMultiGraph.h"
#include <RooStats/ProfileLikelihoodCalculator.h>

#include <iostream>
#include <math.h>

using namespace std;

void problem_3()
{   
    ROOT::Math::MinimizerOptions::SetDefaultMinimizer("Minuit2");

    // item a and b
    Double_t data1[] = {-0.5, -0.25, -0.1, -0.05, 0.0, 0.04, 0.11, 0.14, 0.24, 0.6};
    
    auto *c1 = new TCanvas();
    c1 -> SetGrid();

    TF1 *f1 = new TF1("f1", "[1] + [0]*TMath::Cos(x)", -2, 2);
    f1 -> SetParameters(0, 2);
    TH1F *h1 = new TH1F("Data item a) histogram", "Data item a) histogram", 10, -2, 2);
    h1 -> SetMarkerSize(2.0);
    h1 -> SetLineColor(kBlue);
    h1 -> SetFillColor(kBlue - 10);
 
    for (Int_t i = 0; i < sizeof(data1)/sizeof(data1[0]); ++i)
    {
        h1 -> Fill(data1[i]);
    }

    h1 -> GetXaxis() -> SetTitle("Data");
    h1 -> GetYaxis() -> SetTitle("Events");
    h1 -> GetXaxis() -> CenterTitle();
    h1 -> GetYaxis() -> CenterTitle();
    h1 -> Fit(f1, "L");
    gStyle -> SetOptFit(1111);
    c1 -> Draw();
    h1 -> Draw();
    TFitResultPtr r1 = h1 -> Fit(f1, "S");
    TMatrixD cov1 = r1 -> GetCorrelationMatrix();
    TMatrixD cor1 = r1 -> GetCovarianceMatrix();
    cov1.Print();
    cor1.Print();

    Double_t *ci1;
    ci1 = new Double_t[10];
    (TVirtualFitter::GetFitter()) -> GetConfidenceIntervals(10, 1, &data1[0], &ci1[0], 0.95);
    printf("\n");
    for(Int_t i = 0; i < sizeof(data1)/sizeof(data1[0]); ++i)
    {
        printf("%2d --> %8.5E\n", i + 1, ci1[i]);
    }
    
    TH1D *hint1 = new TH1D("hint", "Fitted gaussian with .95 conf.band", 5, -2, 2);
    (TVirtualFitter::GetFitter()) -> GetConfidenceIntervals(hint1);
    hint1 -> SetStats(kFALSE);
    hint1 -> SetFillColor(2);
    hint1 -> Draw("same");

    c1 -> Print("histogram_data_problem_2_item_a_and_b.pdf");

    Double_t x1[10];

    for (Int_t i = 0; i < 10; ++i)
    {
        x1[i] = 1 + data1[i];
    }
    
    auto *extra_canvas_1 = new TCanvas();
    extra_canvas_1 -> SetGrid();

    TF1 *f1_extra = new TF1("f1_extra", "1 + [0]*x", -2, 2);
    TGraph *gr1 = new TGraph (10, data1, x1);
    gr1 -> SetTitle("Extra fit item a)");
    gr1 -> GetXaxis() -> SetTitle("cos(x)");
    gr1 -> GetXaxis() -> CenterTitle();
    gr1 -> GetYaxis() -> SetTitle("1 + #lambda cos(x)");
    gr1 -> GetYaxis() -> CenterTitle();
    gr1 -> Fit(f1_extra, "L");
    gr1 -> Draw("A*");

    TH1D *gr1_condfidence = new TH1D("hint", "Fitted gaussian with .95 conf.band", 100, -2, 2);
    (TVirtualFitter::GetFitter()) -> GetConfidenceIntervals(gr1_condfidence);
    gr1_condfidence -> SetStats(kFALSE);
    gr1_condfidence -> SetFillColor(2);
    gr1_condfidence -> Draw("same");

    extra_canvas_1 -> Print("extra_fit_item_a.pdf");

    // item c
    Double_t data2[] = {0.05, 0.15, 0.25, 0.35, 0.45, 0.55, 0.65, 0.75, 0.85, 0.95};

    auto *c2 = new TCanvas();
    c2 -> SetGrid();

    TF1 *f2 = new TF1("f1", "1 + [0]*TMath::Cos(x)", -2, 2);
    f2 -> SetParameters(0, 2);
    TH1F *h2 = new TH1F("Data item c) histogram", "Data item c) histogram", 15, -2, 2);
    h2 -> SetMarkerSize(2.0);
    h2 -> SetLineColor(kBlue);
    h2 -> SetFillColor(kBlue - 10); 

    for (Int_t i = 0; i < sizeof(data2)/sizeof(data2[0]); ++i)
    {
        h2 -> Fill(data2[i]);
    }

    h2 -> GetXaxis() -> SetTitle("Data");
    h2 -> GetYaxis() -> SetTitle("Events");
    h2 -> GetXaxis() -> CenterTitle();
    h2 -> GetYaxis() -> CenterTitle();
    h2 -> Fit(f2, "L");
    gStyle -> SetOptFit(1111);
    c2 -> Draw();
    h2 -> Draw();

    Double_t *ci2;
    ci2 = new Double_t[10];
    (TVirtualFitter::GetFitter()) -> GetConfidenceIntervals(10, 1, &data2[0], &ci2[0], 0.95);
    printf("\n");
    for(Int_t i = 0; i < sizeof(data2)/sizeof(data2[0]); ++i)
    {
        printf("%2d --> %8.5E\n", i + 1, ci2[i]);
    }
    
    TH1D *hint2 = new TH1D("hint", "Fitted gaussian with .95 conf.band", 5, -2, 2);
    (TVirtualFitter::GetFitter()) -> GetConfidenceIntervals(hint2);
    hint2 -> SetStats(kFALSE);
    hint2 -> SetFillColor(2);
    hint2 -> Draw("same");

    c2 -> Print("histogram_data_problem_2_item_c.pdf");

     Double_t x2[10];

    for (Int_t i = 0; i < 10; ++i)
    {
        x2[i] = 1 + data2[i];
    }
    
    auto *extra_canvas_2 = new TCanvas();
    extra_canvas_2 -> SetGrid();

    TF1 *f2_extra = new TF1("f2_extra", "1 + [0]*x", -2, 2);

    TGraph *gr2 = new TGraph (10, data2, x2);
    gr2 -> SetTitle("Extra fit item c)");
    gr2 -> GetXaxis() -> SetTitle("cos(x)");
    gr2 -> GetXaxis() -> CenterTitle();
    gr2 -> GetYaxis() -> SetTitle("1 + #lambda cos(x)");
    gr2 -> GetYaxis() -> CenterTitle();
    gr2 -> Fit(f2_extra, "L");
    gr2 -> Draw("A*");

    TH1D *gr2_condfidence = new TH1D("hint", "Fitted gaussian with .95 conf.band", 100, -2, 2);
    (TVirtualFitter::GetFitter()) -> GetConfidenceIntervals(gr2_condfidence);
    gr2_condfidence -> SetStats(kFALSE);
    gr2_condfidence -> SetFillColor(2);
    gr2_condfidence -> Draw("same");

    extra_canvas_2 -> Print("extra_fit_item_c.pdf");

}
