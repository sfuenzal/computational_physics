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

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

using namespace std;

void problem_5_plots()
{   
    // DM off
    double temperature_data_2 [] = {1.2, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3.0, 3.5, 4.0, 4.5, 5.0};
    double magnetization_data_2 [] = {0.997, 0.986, 0.979, 0.970, 0.956, 0.938, 0.911, 0.869, 0.794, 0.670, 0.516, 0.388, 0.304, 0.250, 0.214, 0.189, 0.171, 0.124, 0.103, 0.092, 0.084};
    double specific_heat_data_2 [] = {0.067, 0.196, 0.262, 0.341, 0.439, 0.561, 0.727, 0.955, 1.290, 1.534, 1.409, 1.063, 0.803, 0.641, 0.526, 0.460, 0.400, 0.247, 0.169, 0.126, 0.097};

    auto *c3 = new TCanvas();
    c3 -> SetGrid();
    
    TGraph *gr3 = new TGraph (sizeof(temperature_data_2)/sizeof(temperature_data_2[0]), temperature_data_2, magnetization_data_2);
    gr3 -> SetTitle("magnetization curve DM off (ALPS)");
    gr3 -> GetXaxis() -> SetTitle("T");
    gr3 -> GetXaxis() -> CenterTitle();
    gr3 -> GetXaxis() -> SetLimits(1, 3);
    gr3 -> GetYaxis() -> SetTitle("C");
    gr3 -> GetYaxis() -> CenterTitle();
    gr3 -> Draw("AC*");

    c3 -> Print("magnetization_curve_problem_5_DM_off_ALPS.pdf");

    auto *c4 = new TCanvas();
    c4 -> SetGrid();
    
    TGraph *gr4 = new TGraph (sizeof(temperature_data_2)/sizeof(temperature_data_2[0]), temperature_data_2, specific_heat_data_2);
    gr4 -> SetTitle("Specific heat curve DM off (ALPS)");
    gr4 -> GetXaxis() -> SetTitle("T");
    gr4 -> GetXaxis() -> CenterTitle();
    gr4 -> GetXaxis() -> SetLimits(1, 3);
    gr4 -> GetYaxis() -> SetTitle("C");
    gr4 -> GetYaxis() -> CenterTitle();
    gr4 -> Draw("AC*");

    c4 -> Print("specific_heat_curve_problem_5_DM_off_ALPS.pdf");
}