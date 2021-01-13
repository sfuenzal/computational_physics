#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <iomanip>

// PYTHIA
#include "Pythia8/Pythia.h"

// ROOT, for histogramming.
#include "TH1.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TLegend.h"

// ROOT, for interactive graphics.
#include "TVirtualPad.h"
#include "TApplication.h"

// ROOT, for saving file.
#include "TFile.h"

// More ROOT packages.
#include <TChain.h>
#include "TLatex.h"
#include <TMath.h>
#include <TGraph.h>
#include <TLorentzVector.h>

using namespace Pythia8;
using namespace std;

void pythia_higgs_events_generator(Int_t number_of_events)
{
    Double_t a = 124.95;
    Double_t b = 125.05;
    Int_t bins = 10;
    
    TCanvas *canvas_1 = new TCanvas("canvas_1", "canvas_1", 10, 10, 900, 600);
    THStack *hs = new THStack("Information", "Higgs mass stacked histogram");
    
    TH1F *histogram_1_mass_higgs = new TH1F("histogram_1_mass_higgs", "ffbar2H", bins, a, b);
    histogram_1_mass_higgs -> SetMarkerSize(2.0);
    histogram_1_mass_higgs -> SetLineColor(kAzure);
    histogram_1_mass_higgs -> SetFillColor(kAzure);
    
    TH1F *histogram_2_mass_higgs = new TH1F("histogram_2_mass_higgs", "gg2H", bins, a, b);
    histogram_2_mass_higgs -> SetMarkerSize(2.0);
    histogram_2_mass_higgs -> SetLineColor(kBlue);
    histogram_2_mass_higgs -> SetFillColor(kBlue);

    TH1F *histogram_3_mass_higgs = new TH1F("histogram_3_mass_higgs", "gmgm2H", bins, a, b);
    histogram_3_mass_higgs -> SetMarkerSize(2.0);
    histogram_3_mass_higgs -> SetLineColor(kViolet);
    histogram_3_mass_higgs -> SetFillColor(kViolet);

    TH1F *histogram_4_mass_higgs = new TH1F("histogram_4_mass_higgs", "ffbar2HZ", bins, a, b);
    histogram_4_mass_higgs -> SetMarkerSize(2.0);
    histogram_4_mass_higgs -> SetLineColor(kMagenta);
    histogram_4_mass_higgs -> SetFillColor(kMagenta);

    TH1F *histogram_5_mass_higgs = new TH1F("histogram_5_mass_higgs", "ffbar2HW", bins, a, b);
    histogram_5_mass_higgs -> SetMarkerSize(2.0);
    histogram_5_mass_higgs -> SetLineColor(kPink);
    histogram_5_mass_higgs -> SetFillColor(kPink);
    
    TH1F *histogram_6_mass_higgs = new TH1F("histogram_6_mass_higgs", "ff2Hff(t:ZZ)", bins, a, b);
    histogram_6_mass_higgs -> SetMarkerSize(2.0);
    histogram_6_mass_higgs -> SetLineColor(kRed);
    histogram_6_mass_higgs -> SetFillColor(kRed);

    TH1F *histogram_7_mass_higgs = new TH1F("histogram_7_mass_higgs", "ff2Hff(t:WW)", bins, a, b);
    histogram_7_mass_higgs -> SetMarkerSize(2.0);
    histogram_7_mass_higgs -> SetLineColor(kOrange);
    histogram_7_mass_higgs -> SetFillColor(kOrange);

    TH1F *histogram_8_mass_higgs = new TH1F("histogram_8_mass_higgs", "gg2Httbar", bins, a, b);
    histogram_8_mass_higgs -> SetMarkerSize(2.0);
    histogram_8_mass_higgs -> SetLineColor(kYellow);
    histogram_8_mass_higgs -> SetFillColor(kYellow);

    TH1F *histogram_9_mass_higgs = new TH1F("histogram_9_mass_higgs", "qqbar2Httbar", bins, a, b);
    histogram_9_mass_higgs -> SetMarkerSize(2.0);
    histogram_9_mass_higgs -> SetLineColor(kSpring);
    histogram_9_mass_higgs -> SetFillColor(kSpring);

    vector<string> subprocess = {"HiggsSM:ffbar2H = on", "HiggsSM:gg2H = on", "HiggsSM:gmgm2H = on", "HiggsSM:ffbar2HZ = on", "HiggsSM:ffbar2HW = on", "HiggsSM:ff2Hff(t:ZZ) = on", "HiggsSM:ff2Hff(t:WW) = on", "HiggsSM:gg2Httbar = on", "HiggsSM:qqbar2Httbar = on"};
    Double_t matrix_with_higgs_masses[subprocess.size()][10000];

    vector<double> higgs_mass_ffbar2H;
    vector<double> higgs_mass_gg2H;
    vector<double> higgs_mass_gmgm2H;
    vector<double> higgs_mass_ffbar2HZ;
    vector<double> higgs_mass_ffbar2HW;
    vector<double> higgs_mass_ff2Hff_t_ZZ;
    vector<double> higgs_mass_ff2Hff_t_WW;
    vector<double> higgs_mass_gg2Httbar;
    vector<double> higgs_mass_qqbar2Httbar;

    vector<double> higgs_mass_ffbar2H_filter;
    vector<double> higgs_mass_gg2H_filter;
    vector<double> higgs_mass_gmgm2H_filter;
    vector<double> higgs_mass_ffbar2HZ_filter;
    vector<double> higgs_mass_ffbar2HW_filter;
    vector<double> higgs_mass_ff2Hff_t_ZZ_filter;
    vector<double> higgs_mass_ff2Hff_t_WW_filter;
    vector<double> higgs_mass_gg2Httbar_filter;
    vector<double> higgs_mass_qqbar2Httbar_filter;

    for(Int_t ii = 0; ii < subprocess.size(); ++ii)
    {
        Pythia pythia;
        
        pythia.readString(subprocess[ii]);
        pythia.readString("Beams:eCM = 13000.");
        pythia.readString("Next:numberShowEvent = 0");
        pythia.init();
      
        vector<double> temporal_vector_for_counters_mass_higgs;
     
        for (Int_t iEvent = 0; iEvent < number_of_events; ++iEvent) 
        {
            pythia.next(); 
    
            Int_t iH = 0;
            Int_t iH2 = 0;
            for (Int_t i = 0; i < pythia.event.size(); ++i) 
            {
                if (pythia.event[i].id() == 25)
                {
                    iH = i;
                    temporal_vector_for_counters_mass_higgs.push_back(pythia.event[iH].m());
                    matrix_with_higgs_masses[ii][iH] = pythia.event[iH].m();
                }

                if (pythia.event[i].id() == 25)
                {
                    iH2 = i;  
                    matrix_with_higgs_masses[ii][i] = pythia.event[iH2].m();
                }
            }
        }   

        cout << "Number of Higgs boson produced = " << temporal_vector_for_counters_mass_higgs.size() << endl; 
        
        temporal_vector_for_counters_mass_higgs.clear();  
    }

    for (Int_t i = 0; i < 10000; ++i)
    {
        higgs_mass_ffbar2H.push_back(matrix_with_higgs_masses[0][i]);
        higgs_mass_gg2H.push_back(matrix_with_higgs_masses[1][i]);
        higgs_mass_gmgm2H.push_back(matrix_with_higgs_masses[2][i]);
        higgs_mass_ffbar2HZ.push_back(matrix_with_higgs_masses[3][i]);
        higgs_mass_ffbar2HW.push_back(matrix_with_higgs_masses[4][i]);
        higgs_mass_ff2Hff_t_ZZ.push_back(matrix_with_higgs_masses[5][i]);
        higgs_mass_ff2Hff_t_WW.push_back(matrix_with_higgs_masses[6][i]);
        higgs_mass_gg2Httbar.push_back(matrix_with_higgs_masses[7][i]);
        higgs_mass_qqbar2Httbar.push_back(matrix_with_higgs_masses[8][i]);
    }

    //copy_if (higgs_mass_ffbar2H.begin(), higgs_mass_ffbar2H.end(), back_inserter(higgs_mass_ffbar2H_filter), [](int i){return i != 0;} );
    //copy_if (higgs_mass_gg2H.begin(), higgs_mass_gg2H.end(), back_inserter(higgs_mass_gg2H_filter), [](int i){return i != 0;} );
    //copy_if (higgs_mass_gmgm2H.begin(), higgs_mass_gmgm2H.end(), back_inserter(higgs_mass_gmgm2H_filter), [](int i){return i != 0;} );
    //copy_if (higgs_mass_ffbar2HZ.begin(), higgs_mass_ffbar2HZ.end(), back_inserter(higgs_mass_ffbar2HZ_filter), [](int i){return i != 0;} );
    //copy_if (higgs_mass_ffbar2HW.begin(), higgs_mass_ffbar2HW.end(), back_inserter(higgs_mass_ffbar2HW_filter), [](int i){return i != 0;} );
    //copy_if (higgs_mass_ff2Hff_t_ZZ.begin(), higgs_mass_ff2Hff_t_ZZ.end(), back_inserter(higgs_mass_ff2Hff_t_ZZ_filter), [](int i){return i != 0;} );
    //copy_if (higgs_mass_ff2Hff_t_WW.begin(), higgs_mass_ff2Hff_t_WW.end(), back_inserter(higgs_mass_ff2Hff_t_WW_filter), [](int i){return i != 0;} );
    //copy_if (higgs_mass_gg2Httbar.begin(), higgs_mass_gg2Httbar.end(), back_inserter(higgs_mass_gg2Httbar_filter), [](int i){return i != 0;} );
    //copy_if (higgs_mass_qqbar2Httbar.begin(), higgs_mass_qqbar2Httbar.end(), back_inserter(higgs_mass_qqbar2Httbar_filter), [](int i){return i != 0;} );
    
    for (Int_t i = 0; i < higgs_mass_ffbar2H.size(); ++i)
    {
        histogram_1_mass_higgs -> Fill(higgs_mass_ffbar2H[i]);
        hs -> Add(histogram_1_mass_higgs);
    }
    
    for (Int_t i = 0; i < higgs_mass_gg2H.size(); ++i)
    {
        histogram_2_mass_higgs -> Fill(higgs_mass_gg2H[i]);
        hs -> Add(histogram_2_mass_higgs);
    }

    for (Int_t i = 0; i < higgs_mass_gmgm2H.size(); ++i)
    {
        histogram_3_mass_higgs -> Fill(higgs_mass_gmgm2H[i]);
        hs -> Add(histogram_3_mass_higgs);
    }

    for (Int_t i = 0; i < higgs_mass_ffbar2HZ.size(); ++i)
    {
        histogram_4_mass_higgs -> Fill(higgs_mass_ffbar2HZ[i]);
        hs -> Add(histogram_4_mass_higgs);
    }
    
    for (Int_t i = 0; i < higgs_mass_ffbar2HW.size(); ++i)
    {
        histogram_5_mass_higgs -> Fill(higgs_mass_ffbar2HW[i]);
        hs -> Add(histogram_5_mass_higgs);
    }

    for (Int_t i = 0; i < higgs_mass_ff2Hff_t_ZZ.size(); ++i)
    {
        histogram_6_mass_higgs -> Fill(higgs_mass_ff2Hff_t_ZZ[i]);
        hs -> Add(histogram_6_mass_higgs);
    }

    for (Int_t i = 0; i < higgs_mass_ff2Hff_t_WW.size(); ++i)
    {
        histogram_7_mass_higgs -> Fill(higgs_mass_ff2Hff_t_WW[i]);
        hs -> Add(histogram_7_mass_higgs);
    }

    for (Int_t i = 0; i < higgs_mass_gg2Httbar.size(); ++i)
    {
        histogram_8_mass_higgs -> Fill(higgs_mass_gg2Httbar[i]);
        hs -> Add(histogram_8_mass_higgs);
    }

    for (Int_t i = 0; i < higgs_mass_qqbar2Httbar.size(); ++i)
    {
        histogram_9_mass_higgs -> Fill(higgs_mass_qqbar2Httbar[i]);
        hs -> Add(histogram_9_mass_higgs);
    }

    canvas_1 -> SetGrid();
    canvas_1 -> Draw("nostackb");
    hs -> Draw();
    hs -> GetXaxis() -> SetTitle("m");
    hs -> GetXaxis() -> CenterTitle();
    hs -> GetYaxis() -> SetTitle("Events");
    hs -> GetYaxis() -> CenterTitle();
    
    auto legend = new TLegend(0.9, 0.7, 0.48, 0.9);
    legend -> SetHeader("Subprocess", "C"); 
    legend -> AddEntry(histogram_1_mass_higgs, "ffbar2H", "f");
    legend -> AddEntry(histogram_2_mass_higgs, "gg2H", "f");
    legend -> AddEntry(histogram_3_mass_higgs, "gmgm2H", "f");
    legend -> AddEntry(histogram_4_mass_higgs, "ffbar2HZ", "f");
    legend -> AddEntry(histogram_5_mass_higgs, "ffbar2HW", "f");
    legend -> AddEntry(histogram_6_mass_higgs, "ff2Hff_t_ZZ", "f");
    legend -> AddEntry(histogram_7_mass_higgs, "ff2Hff_t_WW", "f");
    legend -> AddEntry(histogram_8_mass_higgs, "gg2Httbar", "f");
    legend -> AddEntry(histogram_9_mass_higgs, "qqbar2Httbar", "f");
    legend -> Draw();

    canvas_1 -> Print("higgs_mass_stacked_histogram.png");
}

int main() 
{
    Int_t simulated_events = 10000;

    pythia_higgs_events_generator(simulated_events);

    return 0;
}