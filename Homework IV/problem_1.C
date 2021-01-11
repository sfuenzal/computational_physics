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

#include <iostream>
#include <math.h>

using namespace std;

Int_t factorial_function(Int_t n)
{
    if (n == 0)
    {
        return 1;
    }
    
    else 
    {
        return n*factorial_function(n - 1);
    }
}

Double_t poisson_pdf(Int_t n, Double_t lambda)
{
    return ROOT::Math::poisson_pdf(n, lambda);
}

void problem_1()
{
    Int_t number_of_events = 2;
    Float_t mean_poisson_distribution = 3.7;

    cout << "Mean Poisson distribution = " << mean_poisson_distribution << endl;
    
    cout << " " << endl;

    for (Int_t i = 0; i <= number_of_events; ++i)
    {
        cout << "Probability event (by hand) " << i << " = " << (pow(mean_poisson_distribution, i)/factorial_function(i))*TMath::Exp(-mean_poisson_distribution) << endl;
    }

    cout << " " << endl;

    Double_t sum_1 = 0;
    for (Int_t i = 0; i <= number_of_events; ++i)
    {
        sum_1 += (pow(mean_poisson_distribution, i)/factorial_function(i))*TMath::Exp(-mean_poisson_distribution);
    }

    cout << "Sum probabilities event (by hand) = " << sum_1 << endl;

    cout << " " << endl;

    for (Int_t i = 0; i <= number_of_events; ++i)
    {
        cout << "Probability event (ROOT poisson_pdf) " << i << " = " << poisson_pdf(i, mean_poisson_distribution) << endl;
    }
    
    cout << " " << endl;

    Double_t sum_2 = 0;
    
    for (Int_t i = 0; i <= number_of_events; ++i)
    {
        sum_2 += (double) poisson_pdf(i, mean_poisson_distribution);
    }

    cout << "Sum probabilities event (ROOT poisson_pdf) = " << sum_2 << endl;

    cout << " " << endl;
}