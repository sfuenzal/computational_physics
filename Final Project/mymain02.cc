#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>

// PYTHIA
#include "Pythia8/Pythia.h"

// ROOT, for histogramming.
#include "TH1.h"
#include "TCanvas.h"
#include "THStack.h"

// ROOT, for interactive graphics.
#include "TVirtualPad.h"
#include "TApplication.h"

// ROOT, for saving file.
#include "TFile.h"

// More ROOT packages.
#include <TChain.h>
#include "TLatex.h"
#include <TMath.h>
#include <TLorentzVector.h>

using namespace Pythia8;

void pythia_higgs_events_generator(Int_t number_of_events)
{
    TCanvas *canvas_1 = new TCanvas("canvas_1", "canvas_1", 10, 10, 900, 600);
    canvas_1 -> Divide(2, 2);

    TH1F *pT_histogram = new TH1F("Information", "Transversal momentum", 100, 0, 400);
    pT_histogram -> SetMarkerSize(2.0);
    pT_histogram -> SetLineColor(kBlue);
    pT_histogram -> SetFillColor(kBlue - 10);

    TH1F *eta_histogram = new TH1F("Information", "Pseudo-rapidity", 100, -10, 10);
    eta_histogram -> SetMarkerSize(2.0);
    eta_histogram -> SetLineColor(kRed);
    eta_histogram -> SetFillColor(kRed - 10);

    TH1F *phi_histogram = new TH1F("Information", "Azimuthal angle", 100, -5, 5);
    phi_histogram -> SetMarkerSize(2.0);
    phi_histogram -> SetLineColor(kOrange);
    phi_histogram -> SetFillColor(kOrange - 10);

    TH1F *E_histogram = new TH1F("Information", "Energy", 100, 100, 1000);
    E_histogram -> SetMarkerSize(2.0);
    E_histogram -> SetLineColor(kGreen);
    E_histogram -> SetFillColor(kGreen - 10);

    TCanvas *canvas_2 = new TCanvas("canvas_2", "canvas_2", 10, 10, 900, 600);
    canvas_2 -> Divide(2, 2);

    TH1F *rapidity_histogram = new TH1F("Information", "Rapidity", 100, -6, 6);
    rapidity_histogram -> SetMarkerSize(2.0);
    rapidity_histogram -> SetLineColor(kBlue);
    rapidity_histogram -> SetFillColor(kBlue - 10);

    TH1F *theta_histogram = new TH1F("Information", "Polar angle", 100, 0, 3.2);
    theta_histogram -> SetMarkerSize(2.0);
    theta_histogram -> SetLineColor(kRed);
    theta_histogram -> SetFillColor(kRed - 10);

    TH1F *eT_histogram = new TH1F("Information", "Transversal energy", 100, 0, 400);
    eT_histogram -> SetMarkerSize(2.0);
    eT_histogram -> SetLineColor(kOrange);
    eT_histogram -> SetFillColor(kOrange - 10);
    
    TH1F *mT_histogram = new TH1F("Information", "Transversal mass", 100, 124.8, 125.2);
    mT_histogram -> SetMarkerSize(2.0);
    mT_histogram -> SetLineColor(kGreen);
    mT_histogram -> SetFillColor(kGreen - 10);

    TCanvas *canvas_3 = new TCanvas("canvas_3", "canvas_3", 10, 10, 900, 600);
    canvas_3 -> Divide(1, 1);

    TH1F *invariant_mass_histogram = new TH1F("Information", "Higgs mass", 100, 124.8, 125.2);
    invariant_mass_histogram -> SetMarkerSize(2.0);
    invariant_mass_histogram -> SetLineColor(kBlue);
    invariant_mass_histogram -> SetFillColor(kBlue - 10);

    Pythia pythia;

    pythia.readString("Higgs:cubicWidth = on");
    pythia.readString("Higgs:runningLoopMass = on");
    pythia.readString("Higgs:clipWings = on");
    pythia.readString("Higgs:wingsFac = 50");
    pythia.readString("HiggsSM:NLOWidths = on");
    
    // Switch on processes:
    pythia.readString("HiggsSM:all = on");
 
    // Energy of the collitions: 13 [TeV] CM energy
    pythia.readString("Beams:eCM = 13000.");

    // How many events you want to see 
   
    pythia.readString("Next:numberShowEvent = 2");
    pythia.init();

    for (int iEvent = 0; iEvent < number_of_events; ++iEvent) // Event loop.
    {
        pythia.next(); 
    
        Int_t iH = 0;
        for (Int_t i = 0; i < pythia.event.size(); ++i) // Particle loop.
        {            
            
            if (pythia.event[i].id() == 25)
            {
                iH = i;
                pT_histogram -> Fill(pythia.event[iH].pT());
                eta_histogram -> Fill(pythia.event[iH].eta());
                phi_histogram -> Fill(pythia.event[iH].phi());
                E_histogram -> Fill(pythia.event[iH].e());
                rapidity_histogram -> Fill(pythia.event[iH].y());
                theta_histogram -> Fill(pythia.event[iH].theta());
                eT_histogram -> Fill(pythia.event[iH].eT());
                mT_histogram -> Fill(pythia.event[iH].mT());
                invariant_mass_histogram -> Fill(pythia.event[iH].m());
            }
        }
    }

    canvas_1 -> cd(1);
    canvas_1 -> Draw();
    canvas_1 -> SetGrid();
    pT_histogram -> Draw();
    pT_histogram -> GetXaxis() -> SetTitle("pT");
    pT_histogram -> GetXaxis() -> CenterTitle();
    pT_histogram -> GetYaxis() -> SetTitle("Events");
    pT_histogram -> GetYaxis() -> CenterTitle();

    canvas_1 -> cd(2);
    canvas_1 -> Draw();
    canvas_1 -> SetGrid();
    eta_histogram -> Draw();
    eta_histogram -> GetXaxis() -> SetTitle("#eta");
    eta_histogram -> GetXaxis() -> CenterTitle();
    eta_histogram -> GetYaxis() -> SetTitle("Events");
    eta_histogram -> GetYaxis() -> CenterTitle();

    canvas_1 -> cd(3);
    canvas_1 -> Draw();
    canvas_1 -> SetGrid();
    phi_histogram -> Draw();
    phi_histogram -> GetXaxis() -> SetTitle("#phi");
    phi_histogram -> GetXaxis() -> CenterTitle();
    phi_histogram -> GetYaxis() -> SetTitle("Events");
    phi_histogram -> GetYaxis() -> CenterTitle();

    canvas_1 -> cd(4);
    canvas_1 -> Draw();
    canvas_1 -> SetGrid();
    E_histogram -> Draw();
    E_histogram -> GetXaxis() -> SetTitle("E");
    E_histogram -> GetXaxis() -> CenterTitle();
    E_histogram -> GetYaxis() -> SetTitle("Events");
    E_histogram -> GetYaxis() -> CenterTitle();

    canvas_1 -> Print("higgs_pt_eta_phi_e.png");

    canvas_2 -> cd(1);
    canvas_2 -> Draw();
    canvas_2 -> SetGrid();
    rapidity_histogram -> Draw();
    rapidity_histogram -> GetXaxis() -> SetTitle("y");
    rapidity_histogram -> GetXaxis() -> CenterTitle();
    rapidity_histogram -> GetYaxis() -> SetTitle("Events");
    rapidity_histogram -> GetYaxis() -> CenterTitle();

    canvas_2 -> cd(2);
    canvas_2 -> Draw();
    canvas_2 -> SetGrid();
    theta_histogram -> Draw();
    theta_histogram -> GetXaxis() -> SetTitle("#theta");
    theta_histogram -> GetXaxis() -> CenterTitle();
    theta_histogram -> GetYaxis() -> SetTitle("Events");
    theta_histogram -> GetYaxis() -> CenterTitle();

    canvas_2 -> cd(3);
    canvas_2 -> Draw();
    canvas_2 -> SetGrid();
    eT_histogram -> Draw();
    eT_histogram -> GetXaxis() -> SetTitle("ET");
    eT_histogram -> GetXaxis() -> CenterTitle();
    eT_histogram -> GetYaxis() -> SetTitle("Events");
    eT_histogram -> GetYaxis() -> CenterTitle();

    canvas_2 -> cd(4);
    canvas_2 -> Draw();
    canvas_2 -> SetGrid();
    mT_histogram -> Draw();
    mT_histogram -> GetXaxis() -> SetTitle("mT");
    mT_histogram -> GetXaxis() -> CenterTitle();
    mT_histogram -> GetYaxis() -> SetTitle("Events");
    mT_histogram -> GetYaxis() -> CenterTitle();

    canvas_2 -> Print("higgs_y_theta_et_mt.png");

    canvas_3 -> cd(1);
    canvas_3 -> Draw();
    canvas_3 -> SetGrid();
    invariant_mass_histogram -> Draw();
    invariant_mass_histogram -> Draw();
    invariant_mass_histogram -> GetXaxis() -> SetTitle("m");
    invariant_mass_histogram -> GetXaxis() -> CenterTitle();
    invariant_mass_histogram -> GetYaxis() -> SetTitle("Events");
    invariant_mass_histogram -> GetYaxis() -> CenterTitle();

    canvas_3 -> Print("higgs_invariant_mass.png");

    pythia.stat();

}

int main() 
{
    Int_t simulated_events = 10000;

    pythia_higgs_events_generator(simulated_events);

    return 0;
}

