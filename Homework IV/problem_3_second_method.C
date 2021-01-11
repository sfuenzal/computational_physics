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

void problem_3_second_method()
{
    cout << "item a) and b)" << endl;
    
    Double_t data1[] = {-0.5, -0.25, -0.1, -0.05, 0.0, 0.04, 0.11, 0.14, 0.24, 0.6};

    auto *canvas_1 = new TCanvas();
    canvas_1 -> SetGrid();

    TH1F *gr1 = new TH1F("Data item a) histogram", "Data item a) histogram", 10, -2, 2);
    TF1 *f1 = new TF1("f1", "[0] + [1]*TMath::Cos(x)", -2, 2);
    
    for (Int_t i = 0; i < sizeof(data1)/sizeof(data1[0]); ++i)
    {
        gr1 -> Fill(data1[i]);
    }
    
    gr1 -> GetXaxis() -> SetTitle("Data");
    gr1 -> GetXaxis() -> CenterTitle();
    gr1 -> GetYaxis() -> SetTitle("Events");
    gr1 -> GetYaxis() -> CenterTitle();
    gr1 -> SetMarkerSize(2.0);
    gr1 -> SetLineColor(kBlue);
    gr1 -> SetFillColor(kBlue - 10);
    gr1 -> Draw();
    TFitResultPtr r1 = gr1 -> Fit(f1, "S L");
    TMatrixD cov1 = r1 -> GetCovarianceMatrix();
    TMatrixD cor1 = r1 -> GetCorrelationMatrix();
    cov1.Print(); 
    cor1.Print();

    canvas_1 -> Print("histogram_data_problem_2_item_a_and_b.pdf");

    cout << "" << endl;
    cout << "item c)" << endl;

    Double_t data2[] = {0.05, 0.15, 0.25, 0.35, 0.45, 0.55, 0.65, 0.75, 0.85, 0.95};

    auto *canvas_2 = new TCanvas();
    canvas_2 -> SetGrid();

    TH1F *gr2 = new TH1F("Data item c) histogram", "Data item c) histogram", 15, -1, 3);
    TF1 *f2 = new TF1("f1", "[0] + [1]*TMath::Cos(x)", -1, 3);
    
    for (Int_t i = 0; i < sizeof(data2)/sizeof(data2[0]); ++i)
    {
        gr2 -> Fill(data2[i]);
    }
    
    gr2 -> GetXaxis() -> SetTitle("Data");
    gr2 -> GetXaxis() -> CenterTitle();
    gr2 -> GetYaxis() -> SetTitle("Events");
    gr2 -> GetYaxis() -> CenterTitle();
    gr2 -> SetMarkerSize(2.0);
    gr2 -> SetLineColor(kBlue);
    gr2 -> SetFillColor(kBlue - 10);
    gr2 -> Draw();
    TFitResultPtr r2 = gr2 -> Fit(f2, "S L");
    TMatrixD cov2 = r2 -> GetCovarianceMatrix();
    TMatrixD cor2 = r2 -> GetCorrelationMatrix();
    cov2.Print();
    cor2.Print();
    
    canvas_2 -> Print("histogram_data_problem_2_item_c.pdf");
}