// PYTHIA
#include "Pythia8/Pythia.h"

// ROOT, for histogramming.
#include "TH1.h"
#include "TCanvas.h"

// ROOT, for interactive graphics.
#include "TVirtualPad.h"
#include "TApplication.h"

// More ROOT packages.
#include "TLatex.h"

using namespace Pythia8;

void pythia_higgs_events_generator(Int_t number_of_events)
{
    TCanvas *canvas_1 = new TCanvas("canvas_1", "canvas_1", 10, 10, 900, 600);
    canvas_1 -> Divide(2, 2);

    TH1F *m_e_histogram = new TH1F("Information", "e mass histogram", 10, 0, 0.0009);
    m_e_histogram -> SetMarkerSize(2.0);
    m_e_histogram -> SetLineColor(kBlue);
    m_e_histogram -> SetFillColor(kBlue - 10);

    TH1F *m_mu_histogram = new TH1F("Information", "#mu mass histogram", 100, 0, 0.2);
    m_mu_histogram -> SetMarkerSize(2.0);
    m_mu_histogram -> SetLineColor(kRed);
    m_mu_histogram -> SetFillColor(kRed - 10);

    TH1F *m_Z_histogram = new TH1F("Information", "Z mass histogram", 100, 70, 110);
    m_Z_histogram -> SetMarkerSize(2.0);
    m_Z_histogram -> SetLineColor(kOrange);
    m_Z_histogram -> SetFillColor(kOrange - 10);

    TH1F *m_W_histogram = new TH1F("Information", "W mass histogram", 100, 60, 100);
    m_W_histogram -> SetMarkerSize(2.0);
    m_W_histogram -> SetLineColor(kGreen);
    m_W_histogram -> SetFillColor(kGreen - 10);

    Pythia pythia;
    
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

        Int_t ie = 0;
        Int_t imu = 0;
        Int_t iZ = 0;
        Int_t iW = 0;
        for (Int_t i = 0; i < pythia.event.size(); ++i) // Particle loop.
        {
            
            if (pythia.event[i].id() == 11) // Fill electron mass histogram
            { 
                ie = i;
                m_e_histogram -> Fill(pythia.event[ie].m());
            }

            else if (pythia.event[i].id() == 13) // Fill muon mass histogram
            { 
                imu = i;
                m_mu_histogram -> Fill(pythia.event[imu].m());
            }

            else if (pythia.event[i].id() == 23) // Fill Z mass histogram
            { 
                iZ = i;
                m_Z_histogram -> Fill(pythia.event[iZ].m());
            }

            else if (pythia.event[i].id() == 24) // Fill W mass histogram
            { 
                iW = i;
                m_W_histogram -> Fill(pythia.event[iW].m());
            }
        }
    }

    canvas_1 -> cd(1);
    canvas_1 -> Draw();
    canvas_1 -> SetGrid();
    m_e_histogram -> Draw();
    m_e_histogram -> GetXaxis() -> SetTitle("e mass");
    m_e_histogram -> GetXaxis() -> CenterTitle();
    m_e_histogram -> GetYaxis() -> SetTitle("Events");
    m_e_histogram -> GetYaxis() -> CenterTitle();
    
    canvas_1 -> cd(2);
    canvas_1 -> Draw();
    canvas_1 -> SetGrid();
    m_mu_histogram -> Draw();
    m_mu_histogram -> GetXaxis() -> SetTitle("#mu mass");
    m_mu_histogram -> GetXaxis() -> CenterTitle();
    m_mu_histogram -> GetYaxis() -> SetTitle("Events");
    m_mu_histogram -> GetYaxis() -> CenterTitle();

    canvas_1 -> cd(3);
    canvas_1 -> Draw();
    canvas_1 -> SetGrid();
    m_Z_histogram -> Draw();
    m_Z_histogram -> GetXaxis() -> SetTitle("Z mass");
    m_Z_histogram -> GetXaxis() -> CenterTitle();
    m_Z_histogram -> GetYaxis() -> SetTitle("Events");
    m_Z_histogram -> GetYaxis() -> CenterTitle();

    canvas_1 -> cd(4);
    canvas_1 -> Draw();
    canvas_1 -> SetGrid();
    m_W_histogram -> Draw();
    m_W_histogram -> GetXaxis() -> SetTitle("W mass");
    m_W_histogram -> GetXaxis() -> CenterTitle();
    m_W_histogram -> GetYaxis() -> SetTitle("Events");
    m_W_histogram -> GetYaxis() -> CenterTitle();

    canvas_1 -> Print("mass_e_mu_Z_W_histogram.png");

    pythia.stat();

}

int main() 
{
    Int_t simulated_events = 15000;

    pythia_higgs_events_generator(simulated_events);

    return 0;
}