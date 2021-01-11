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

# define L 100

void problem_4_DM()
{
    int spin[L][L];
    int i, j, k;
    int ip1, im1, jp1, jm1;
    int mcs;
    int spinValue1, spinValue2, spinNeighbourSum;
    int mag, E;
    int mcsmax;
    int seed;

    double r;
    double K, D;
    double energyChange;
    double rm, rm_E;
    double averageMag, specific_heat;
    double TTC;

    // Set parameters
    mcsmax = 1000;
    TTC = 1.2;
    K = 0.2216544 / TTC;
    D = 1;
    seed = 4711;

    srand(seed);

    // Initialize the Lattice
    for (i = 0; i < L ; ++i)
    {
        for (j = 0; j < L; ++j)
        {
            spin[i][j] = -1;
        }
    }

    mag = -L*L;
    E = 0;
    averageMag = 0.0;
    specific_heat = 0.0;

    int number_of_simulations = 8;
    float averageMag_vector[number_of_simulations];
    float specific_heat_vector[number_of_simulations];
    
    for (k = 0; k < number_of_simulations; ++k)
    {
        // Monte Carlo Loop
        for (mcs = 0; mcs < mcsmax; ++mcs)
        {
            // Loop over all lattice sites
            for (i = 0; i < L; ++i)
            {   
                for (j = 0; j < L; ++j)
                {
                    // Periodic boundary conditions
                    ip1 = i + 1 >= L ? i + 1 - L : i + 1;
                    im1 = i - 1 < 0 ? i - 1 + L : i - 1;
                    jp1 = j + 1 >= L ? j + 1 - L : j + 1;
                    jm1 = j - 1 < 0 ? j - 1 + L : j - 1;

                    // Change in energy
                    spinValue1 = spin[i][j];
                    spinValue2 = spin[i][j] - spin[j][i];
                    spinNeighbourSum = spin[im1][j] + spin[ip1][j] + spin[i][jm1] + spin[i][jp1];
                    energyChange = 2.0 * K * spinValue1 * spinNeighbourSum + 2.0 * D * spinValue2 * spinNeighbourSum;

                    // Generate random numbers                
                    srand((int) time(0));
                    r = (float) rand() / (float) RAND_MAX;

                    // Accept/reject the change
                    if (energyChange == 0.0 || r < exp(-(double) energyChange))
                    {
                        spin[i][j] = -spinValue1;
                        mag -= 2 * spinValue1;
                        E -= 2 * energyChange;
                    }
                }
            }
            rm = (double) mag / (float) (L*L);
            rm_E = (double) E/ (float) (L*L);
            averageMag += fabs(rm);
            specific_heat += fabs(rm_E);
        }
    
        averageMag /= (float) mcsmax;
        specific_heat /= (float) mcsmax;
        averageMag_vector[k] = averageMag;
        specific_heat_vector[k] = specific_heat;
    }
    
    auto *c1 = new TCanvas();
    c1 -> SetGrid();

    float temperature1[number_of_simulations];

    for (i = 0; i < number_of_simulations; ++i)
    {
        temperature1[i] = (float) (i)/(float) (2.26);
    }

    TGraph *gr1 = new TGraph (number_of_simulations, temperature1, averageMag_vector);
    gr1 -> SetTitle("Magnetization curve DM");
    gr1 -> GetXaxis() -> SetTitle("T/Tc");
    gr1 -> GetXaxis() -> CenterTitle();
    gr1 -> GetXaxis() -> SetLimits(0, 3);
    gr1 -> GetYaxis() -> SetTitle("M");
    gr1 -> GetYaxis() -> CenterTitle();
    gr1 -> Draw("AC*");

    c1 -> Print("magnetization_curve_problem_4_DM.pdf");
    
    auto *c2 = new TCanvas();
    c2 -> SetGrid();

    float temperature2[number_of_simulations];

    for (i = 0; i < number_of_simulations; ++i)
    {
        temperature2[i] = (float) (i)/(float) (2.26);
    }

    TGraph *gr2 = new TGraph (number_of_simulations, temperature2, specific_heat_vector);
    gr2 -> SetTitle("Specific heat curve DM");
    gr2 -> GetXaxis() -> SetTitle("T/Tc");
    gr2 -> GetXaxis() -> CenterTitle();
    gr2 -> GetXaxis() -> SetLimits(0, 3);
    gr2 -> GetYaxis() -> SetTitle("C");
    gr2 -> GetYaxis() -> CenterTitle();
    gr2 -> GetYaxis() -> SetLimits(0, 0.22);
    gr2 -> Draw("AC*");

    c2 -> Print("specific_heat_curve_problem_4_DM.pdf");
}