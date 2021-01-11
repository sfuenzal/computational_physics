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

#include <iostream>
#include <math.h>

using namespace std;

Double_t exponentially_modified_gaussian_distribution(Double_t *x, Double_t *param)
{
    Double_t param0 = 3.0; // tau
    Double_t param1 = 2.0; // sigma
    return (1/2.)*param0*TMath::Exp( (1/2.)*param0*( pow(param1, 2)*param0 + 2*param[0] - 2*x[0] ) )*( TMath::Erfc( ( pow(param1, 2)*param0 + param[0] - x[0] )/(TMath::Sqrt(2)*param1) )  ) ;
}

void problem_2()
{    
    // item a
    
    auto *c1 = new TCanvas();
    c1 -> SetGrid();
    
    TF1 *exponentially_modified_gaussian_distribution_graph_1 = new TF1("EMG probability density function", exponentially_modified_gaussian_distribution, -4 , 6, 2);
    exponentially_modified_gaussian_distribution_graph_1 -> SetParameter(0, 0); // mu
    exponentially_modified_gaussian_distribution_graph_1 -> SetLineColor(4);
    exponentially_modified_gaussian_distribution_graph_1 -> SetLineStyle(1);
    exponentially_modified_gaussian_distribution_graph_1 -> GetXaxis() -> SetTitle("x");
    exponentially_modified_gaussian_distribution_graph_1 -> GetXaxis() -> CenterTitle();
    exponentially_modified_gaussian_distribution_graph_1 -> GetYaxis() -> SetTitle("f(x)");
    exponentially_modified_gaussian_distribution_graph_1 -> GetYaxis() -> CenterTitle();
    exponentially_modified_gaussian_distribution_graph_1 -> Draw();

    TF1 *exponentially_modified_gaussian_distribution_graph_2 = new TF1("EMG probability density function", exponentially_modified_gaussian_distribution, -4 , 6, 2);
    exponentially_modified_gaussian_distribution_graph_2 -> SetParameter(0, -2); // mu
    exponentially_modified_gaussian_distribution_graph_2 -> SetLineColor(3);
    exponentially_modified_gaussian_distribution_graph_2 -> SetLineStyle(1);
    exponentially_modified_gaussian_distribution_graph_2 -> GetXaxis() -> SetTitle("x");
    exponentially_modified_gaussian_distribution_graph_2 -> GetXaxis() -> CenterTitle();
    exponentially_modified_gaussian_distribution_graph_2 -> GetYaxis() -> SetTitle("f(x)");
    exponentially_modified_gaussian_distribution_graph_2 -> GetYaxis() -> CenterTitle();
    exponentially_modified_gaussian_distribution_graph_2 -> Draw("same");

    TF1 *exponentially_modified_gaussian_distribution_graph_3 = new TF1("EMG probability density function", exponentially_modified_gaussian_distribution, -4 , 6, 2);
    exponentially_modified_gaussian_distribution_graph_3 -> SetParameter(0, 2); // mu
    exponentially_modified_gaussian_distribution_graph_3 -> SetLineColor(2);
    exponentially_modified_gaussian_distribution_graph_3 -> SetLineStyle(1);
    exponentially_modified_gaussian_distribution_graph_3 -> GetXaxis() -> SetTitle("x");
    exponentially_modified_gaussian_distribution_graph_3 -> GetXaxis() -> CenterTitle();
    exponentially_modified_gaussian_distribution_graph_3 -> GetYaxis() -> SetTitle("f(x)");
    exponentially_modified_gaussian_distribution_graph_3 -> GetYaxis() -> CenterTitle();
    exponentially_modified_gaussian_distribution_graph_3 -> Draw("same");

    auto legend = new TLegend(0.1, 0.7, 0.48, 0.9);
    legend -> SetHeader("EMG with different #mu", "C"); // option "C" allows to center the header
    legend -> AddEntry(exponentially_modified_gaussian_distribution_graph_1, "#mu = 0", "l");
    legend -> AddEntry(exponentially_modified_gaussian_distribution_graph_2, "#mu = -2", "l");
    legend -> AddEntry(exponentially_modified_gaussian_distribution_graph_3, "#mu = 2", "l");
    legend -> Draw();
    
    c1 -> Print("exponentially_modified_gaussian_distribution_graph.pdf");
    
    // item b

    Int_t number_of_simulations = 50000;
    
    // Gaussian distribution parameters
    Double_t mu = 0.0;
    Double_t sigma = 2.0;
    
    // Exponential distribution parameters
    Double_t tau = 3.0;
    
    TRandom3 r1, r2;

    vector<double> x1;

    for (Int_t i = 0; i < number_of_simulations; ++i)
    {
        x1.push_back(r1.Gaus(mu, sigma) + r2.Exp(tau));
    }

    auto *c2 = new TCanvas();
    c2 -> SetGrid();
    
    TF1 *func = new TF1("m1", "gaus", -4, 6);
    TH1F *histogram_convolution = new TH1F("Histogram convolution", "Histogram convolution", 100, -4, 6);
    histogram_convolution -> SetMarkerSize(2.0);
    histogram_convolution -> SetLineColor(kBlue);
    histogram_convolution -> SetFillColor(kBlue - 10);

    for (Int_t i = 0; i < number_of_simulations; ++i)
    {
        histogram_convolution -> Fill(x1[i]);
    }

    histogram_convolution -> GetXaxis() -> SetTitle("f(x)");
    histogram_convolution -> GetYaxis() -> SetTitle("Events");
    histogram_convolution -> GetXaxis() -> CenterTitle();
    histogram_convolution -> GetYaxis() -> CenterTitle();
    histogram_convolution -> Fit(func);
    c2 -> Draw();
    histogram_convolution -> Draw();

    c2 -> Print("histogram_convolution.pdf");

    // item c

    TRandom3 r3, r4;
    
    vector<double> x2, x3, f, f_filter;

    for (Int_t i = 0; i < number_of_simulations; ++i)
    {
       x2.push_back(r3.Uniform(-4, 6));
       x3.push_back(r4.Uniform(0, 0.2));
    }

    for (Int_t i = 0; i < number_of_simulations; ++i)
    {
        f.push_back( (1/2.)*tau*TMath::Exp( (1/2.)*tau*( pow(sigma, 2)*tau + 2*mu - 2*x2[i] ) )*( TMath::Erfc( ( pow(sigma, 2)*tau + mu - x2[i] )/(TMath::Sqrt(2)*sigma) )  )  );
    }

    for(Int_t i = 0; i < number_of_simulations; ++i)
    {
        if (x3[i] < f[i])
        {
            f_filter.push_back(f[i]);
        }
    }

    auto *c3 = new TCanvas();
    c3 -> SetGrid();

    TH1F *histogram_rejection_method = new TH1F("Histogram rejection method", "Histogram rejection method", 100, 0.02, 0.2);
    histogram_rejection_method -> SetMarkerSize(2.0);
    histogram_rejection_method -> SetLineColor(kBlue);
    histogram_rejection_method -> SetFillColor(kBlue - 10);

    for (Int_t i = 0; i < f_filter.size(); ++i)
    {
        histogram_rejection_method -> Fill(f_filter[i]);
    }

    histogram_rejection_method -> GetXaxis() -> SetTitle("f(x)");
    histogram_rejection_method -> GetYaxis() -> SetTitle("Events");
    histogram_rejection_method -> GetXaxis() -> CenterTitle();
    histogram_rejection_method -> GetYaxis() -> CenterTitle();
    c3 -> Draw();
    histogram_rejection_method -> Draw();

    c3 -> Print("histogram_rejection_method.pdf");

    for (Int_t i = 0; i < f_filter.size(); ++i)
    {
        cout << "Data Acceptance/Rejection Method = " << f_filter[i] << endl;
    }

}