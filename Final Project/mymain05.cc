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
#include "TLegend.h"
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
#include <TGraph.h>
#include <TLorentzVector.h>

using namespace Pythia8;

void pythia_higgs_events_generator(Int_t number_of_events)
{
    vector<int> loc_vector;
    vector<int> id_vector;
    vector<int> loc_id_daughter_1_vector;
    vector<int> loc_id_daughter_2_vector;
    vector<double> mass_vector;
    vector<double> pt_vector;
    vector<double> eta_vector;
    vector<double> phi_vector;
    vector<double> E_vector;
    vector<string> names_vector;

    int id_daughter_1_vector_filter[number_of_events];
    int id_daughter_2_vector_filter[number_of_events];
    double mass_vector_daughter_1_filter[number_of_events];
    double mass_vector_daughter_2_filter[number_of_events];
    double pt_vector_daughter_1_filter[number_of_events];
    double pt_vector_daughter_2_filter[number_of_events];
    double eta_vector_daughter_1_filter[number_of_events];
    double eta_vector_daughter_2_filter[number_of_events];
    double phi_vector_daughter_1_filter[number_of_events];
    double phi_vector_daughter_2_filter[number_of_events];
    double E_vector_daughter_1_filter[number_of_events];
    double E_vector_daughter_2_filter[number_of_events];
    
    vector<int> id_c_cbar_vector_daughter_1;
    vector<int> id_c_cbar_vector_daughter_2;
    vector<int> id_c_cbar_vector_daughter_1_filter;
    vector<int> id_c_cbar_vector_daughter_2_filter;

    vector<int> id_c_vector_daughter_1_filter;
    vector<int> id_c_vector_daughter_2_filter;
    vector<int> id_cbar_vector_daughter_1_filter;
    vector<int> id_cbar_vector_daughter_2_filter;
    
    vector<int> id_photon_vector_daughter_1;
    vector<int> id_photon_vector_daughter_2;
    vector<int> id_photon_vector_daughter_1_filter;
    vector<int> id_photon_vector_daughter_2_filter;

    vector<double> pt_c;
    vector<double> pt_cbar;
    vector<double> eta_c;
    vector<double> eta_cbar;
    vector<double> phi_c;
    vector<double> phi_cbar;
    vector<double> E_c;
    vector<double> E_cbar;

    vector<double> m_qq;
    vector<double> m_H;

    TCanvas *canvas_1 = new TCanvas("canvas_1", "canvas_1", 10, 10, 900, 600);
    canvas_1 -> Divide(2, 1);
    TH1F *invariant_mass_daughter_1_histogram = new TH1F("Information D1", "Daughter 1 masses [GeV]", 20, 0, 3);
    invariant_mass_daughter_1_histogram -> SetMarkerSize(2.0);
    invariant_mass_daughter_1_histogram -> SetLineColor(kBlue);
    invariant_mass_daughter_1_histogram -> SetFillColor(kBlue - 10);

    TH1F *invariant_mass_daughter_2_histogram = new TH1F("Information D2", "Daughter 2 masses [GeV]", 20, 0, 3);
    invariant_mass_daughter_2_histogram -> SetMarkerSize(2.0);
    invariant_mass_daughter_2_histogram -> SetLineColor(kRed);
    invariant_mass_daughter_2_histogram -> SetFillColor(kRed - 10);

    TCanvas *canvas_2_1 = new TCanvas("canvas_2_1", "canvas_2_1", 10, 10, 900, 600);
    canvas_2_1 -> Divide(1, 1);
    THStack *hs_1 = new THStack("hs_1", "id daughters one");
    TH1F *id_daughter_1_histogram_c_cbar = new TH1F("Information D1 c#bar{c}", "id daughter 1 c#bar{c}", 10, -10, 30);
    id_daughter_1_histogram_c_cbar -> SetMarkerSize(2.0);
    id_daughter_1_histogram_c_cbar -> SetLineColor(kBlue);
    id_daughter_1_histogram_c_cbar -> SetFillColor(kBlue - 10);
    TH1F *id_daughter_1_histogram_photon = new TH1F("Information D1 #gammas", "id daughter 1 photon", 10, -10, 30);
    id_daughter_1_histogram_photon -> SetMarkerSize(2.0);
    id_daughter_1_histogram_photon -> SetLineColor(kRed);
    id_daughter_1_histogram_photon -> SetFillColor(kRed - 10);
    
    TCanvas *canvas_2_2 = new TCanvas("canvas_2_2", "canvas_2_2", 10, 10, 900, 600);
    canvas_2_2 -> Divide(1, 1);
    THStack *hs_2 = new THStack("hs_1", "id daughters two");
    TH1F *id_daughter_2_histogram_c_cbar = new TH1F("Information D2 c#bar{c}", "id daughter 2 c#bar{c}", 10, -10, 30);
    id_daughter_2_histogram_c_cbar -> SetMarkerSize(2.0);
    id_daughter_2_histogram_c_cbar -> SetLineColor(kBlue);
    id_daughter_2_histogram_c_cbar -> SetFillColor(kBlue - 10);
    TH1F *id_daughter_2_histogram_photon = new TH1F("Information D2 #gamma", "id daughter 2 photon", 10, -10, 30);
    id_daughter_2_histogram_photon -> SetMarkerSize(2.0);
    id_daughter_2_histogram_photon -> SetLineColor(kRed);
    id_daughter_2_histogram_photon -> SetFillColor(kRed - 10);

    TCanvas *canvas_3 = new TCanvas("canvas_3", "canvas_3", 10, 10, 900, 600);
    canvas_3 -> Divide(1, 1);
    TH1F *invariant_mass_higgs = new TH1F("Information", "Invariant mass Higgs boson [GeV]", 20, 120, 130);
    invariant_mass_higgs -> SetMarkerSize(2.0);
    invariant_mass_higgs -> SetLineColor(kBlue);
    invariant_mass_higgs -> SetFillColor(kBlue - 10);
    
    Pythia pythia;
    
    ////pythia.readString("Higgs:cubicWidth = on");

    // Switch on processes:
    pythia.readString("HiggsSM:all = on");

    // Energy of the collitions: 13 [TeV] CM energy
    pythia.readString("Beams:eCM = 13000.");

    // How many events you want to see 
   
    pythia.readString("Next:numberShowEvent = 0");
    pythia.init();

    for (Int_t iEvent = 0; iEvent < number_of_events; ++iEvent) // Event loop.
    {
        pythia.next(); 
    
        for (Int_t i = 0; i < pythia.event.size(); ++i) // Particle loop.
        {
            loc_vector.push_back(i);
            id_vector.push_back(pythia.event[i].id());
            loc_id_daughter_1_vector.push_back(pythia.event[i].daughter1());
            loc_id_daughter_2_vector.push_back(pythia.event[i].daughter2());
            mass_vector.push_back(pythia.event[i].m());
            pt_vector.push_back(pythia.event[i].pT());
            eta_vector.push_back(pythia.event[i].eta());
            phi_vector.push_back(pythia.event[i].phi());
            E_vector.push_back(pythia.event[i].e());
            names_vector.push_back(pythia.event[i].name());
        }

        Int_t iH = 0;
        for (Int_t i = 0; i < pythia.event.size(); ++i) // Particle loop.
        {
            if (pythia.event[i].id() == 25)
            {
                if (pythia.event[i].daughter1() != pythia.event[i].daughter2())
                {
                    iH = i;
                    id_daughter_1_vector_filter[iEvent] = id_vector[loc_id_daughter_1_vector[iH]];
                    id_daughter_2_vector_filter[iEvent] = id_vector[loc_id_daughter_2_vector[iH]];
                    mass_vector_daughter_1_filter[iEvent] = mass_vector[loc_id_daughter_1_vector[iH]];
                    mass_vector_daughter_2_filter[iEvent] = mass_vector[loc_id_daughter_2_vector[iH]];
                    pt_vector_daughter_1_filter[iEvent] = pt_vector[loc_id_daughter_1_vector[iH]];
                    pt_vector_daughter_2_filter[iEvent] = pt_vector[loc_id_daughter_2_vector[iH]];
                    eta_vector_daughter_1_filter[iEvent] = eta_vector[loc_id_daughter_1_vector[iH]];
                    eta_vector_daughter_2_filter[iEvent] = eta_vector[loc_id_daughter_2_vector[iH]];
                    phi_vector_daughter_1_filter[iEvent] = phi_vector[loc_id_daughter_1_vector[iH]];
                    phi_vector_daughter_2_filter[iEvent] = phi_vector[loc_id_daughter_2_vector[iH]];
                    E_vector_daughter_1_filter[iEvent] = E_vector[loc_id_daughter_1_vector[iH]];
                    E_vector_daughter_2_filter[iEvent] = E_vector[loc_id_daughter_2_vector[iH]];
                    invariant_mass_daughter_1_histogram  -> Fill(mass_vector_daughter_1_filter[iEvent]);
                    invariant_mass_daughter_2_histogram  -> Fill(mass_vector_daughter_2_filter[iEvent]);
                }    
            }
        }
    }

    for (Int_t i = 0; i < number_of_events; ++i)
    {
        if (id_daughter_1_vector_filter[i] == 4 && id_daughter_2_vector_filter[i] == -4) 
        {
            id_c_cbar_vector_daughter_1.push_back(id_daughter_1_vector_filter[i]);
            id_c_cbar_vector_daughter_2.push_back(id_daughter_2_vector_filter[i]); 
        }

        else if (id_daughter_1_vector_filter[i] == -4 && id_daughter_2_vector_filter[i] == 4) 
        {
            id_c_cbar_vector_daughter_1.push_back(id_daughter_1_vector_filter[i]);
            id_c_cbar_vector_daughter_2.push_back(id_daughter_2_vector_filter[i]); 
        } 
    }

    for (Int_t i = 0; i < number_of_events; ++i)
    {
        if (id_daughter_1_vector_filter[i] == 22 && id_daughter_2_vector_filter[i] == 22) 
        {
            id_photon_vector_daughter_1.push_back(id_daughter_1_vector_filter[i]);
            id_photon_vector_daughter_2.push_back(id_daughter_2_vector_filter[i]); 
        }
    }

    copy_if (id_c_cbar_vector_daughter_1.begin(), id_c_cbar_vector_daughter_1.end(), back_inserter(id_c_cbar_vector_daughter_1_filter), [](int i){return i != 0;} );
    copy_if (id_c_cbar_vector_daughter_2.begin(), id_c_cbar_vector_daughter_2.end(), back_inserter(id_c_cbar_vector_daughter_2_filter), [](int i){return i != 0;} );
    
    copy_if (id_photon_vector_daughter_1.begin(), id_photon_vector_daughter_1.end(), back_inserter(id_photon_vector_daughter_1_filter), [](int i){return i != 0;} );
    copy_if (id_photon_vector_daughter_2.begin(), id_photon_vector_daughter_2.end(), back_inserter(id_photon_vector_daughter_2_filter), [](int i){return i != 0;} );
     
    for (Int_t i = 0; i < id_c_cbar_vector_daughter_1_filter.size(); ++i)
    {
        id_daughter_1_histogram_c_cbar -> Fill(id_c_cbar_vector_daughter_1_filter[i]);
        hs_1 -> Add(id_daughter_1_histogram_c_cbar);
    }
    
    for (Int_t i = 0; i < id_photon_vector_daughter_1_filter.size(); ++i)
    {
        id_daughter_1_histogram_photon -> Fill(id_photon_vector_daughter_1_filter[i]);
        hs_1 -> Add(id_daughter_1_histogram_photon);
    }

    for (Int_t i = 0; i < id_c_cbar_vector_daughter_2_filter.size(); ++i)
    {
        id_daughter_2_histogram_c_cbar -> Fill(id_c_cbar_vector_daughter_2_filter[i]);
        hs_2 -> Add(id_daughter_2_histogram_c_cbar);
    }

    for (Int_t i = 0; i < id_photon_vector_daughter_2_filter.size(); ++i)
    {
        id_daughter_2_histogram_photon -> Fill(id_photon_vector_daughter_2_filter[i]);
        hs_2 -> Add(id_daughter_2_histogram_photon);
    }

    Int_t counter_1_1 = 0;
    for (Int_t i = 0; i < number_of_events; ++i)
    {
        if (id_c_cbar_vector_daughter_1_filter[i] == 4)
        {
            counter_1_1 = i;
            pt_c.push_back(pt_vector_daughter_1_filter[counter_1_1]);
        }
    }

    Int_t counter_1_2 = 0;
    for (Int_t i = 0; i < number_of_events; ++i)
    {
        if (id_c_cbar_vector_daughter_2_filter[i] == -4)
        {
            counter_1_2 = i;
            pt_cbar.push_back(pt_vector_daughter_2_filter[counter_1_2]);
        }
    }

    Int_t counter_2_1 = 0;
    for (Int_t i = 0; i < number_of_events; ++i)
    {
        if (id_c_cbar_vector_daughter_1_filter[i] == 4)
        {
            counter_2_1 = i;
            eta_c.push_back(eta_vector_daughter_1_filter[counter_2_1]);
        }
    }

    Int_t counter_2_2 = 0;
    for (Int_t i = 0; i < number_of_events; ++i)
    {
        if (id_c_cbar_vector_daughter_2_filter[i] == -4)
        {
            counter_2_2 = i;
            eta_cbar.push_back(eta_vector_daughter_2_filter[counter_2_2]);
        }
    }

    Int_t counter_3_1 = 0;
    for (Int_t i = 0; i < number_of_events; ++i)
    {
        if (id_c_cbar_vector_daughter_1_filter[i] == 4)
        {
            counter_3_1 = i;
            phi_c.push_back(phi_vector_daughter_1_filter[counter_3_1]);
        }
    }

    Int_t counter_3_2 = 0;
    for (Int_t i = 0; i < number_of_events; ++i)
    {
        if (id_c_cbar_vector_daughter_2_filter[i] == -4)
        {
            counter_3_2 = i;
            phi_cbar.push_back(phi_vector_daughter_2_filter[counter_3_2]);
        }
    }

    Int_t counter_4_1 = 0;
    for (Int_t i = 0; i < number_of_events; ++i)
    {
        if (id_c_cbar_vector_daughter_1_filter[i] == 4)
        {
            counter_4_1 = i;
            E_c.push_back(E_vector_daughter_1_filter[counter_4_1]);
        }
    }

    Int_t counter_4_2 = 0;
    for (Int_t i = 0; i < number_of_events; ++i)
    {
        if (id_c_cbar_vector_daughter_2_filter[i] == -4)
        {
            counter_4_2 = i;
            E_cbar.push_back(E_vector_daughter_2_filter[counter_4_2]);
        }
    }

    TLorentzVector quark_1  = TLorentzVector();
	TLorentzVector quark_2  = TLorentzVector();
    TLorentzVector quark_12 = TLorentzVector();

    for (Int_t i = 0; i < pt_c.size(); ++i)
    {
        quark_1.SetPtEtaPhiE(pt_c.at(i), eta_c.at(i), phi_c.at(i), E_c.at(i));
        quark_2.SetPtEtaPhiE(pt_cbar.at(i), eta_cbar.at(i), phi_cbar.at(i), E_cbar.at(i));
        quark_12 = quark_1 + quark_2;
        m_qq.push_back(quark_12.Mag());
    }

    Int_t counter_5 = 0;
    for (Int_t i = 0; i < pt_c.size(); ++i)
    {
        if (m_qq[i] > 120 && m_qq[i] < 130)
        {
            counter_5 = i;
            m_H.push_back(m_qq[counter_5]);
        }
    }
    
    for (Int_t i = 0; i < m_H.size(); ++i)
    {
        invariant_mass_higgs -> Fill(m_H[i]);
    }

    canvas_1 -> cd(1);
    canvas_1 -> Draw();
    canvas_1 -> SetGrid();
    invariant_mass_daughter_1_histogram -> Draw();
    invariant_mass_daughter_1_histogram -> GetXaxis() -> SetTitle("m daughter 1");
    invariant_mass_daughter_1_histogram -> GetXaxis() -> CenterTitle();
    invariant_mass_daughter_1_histogram -> GetYaxis() -> SetTitle("Events");
    invariant_mass_daughter_1_histogram -> GetYaxis() -> CenterTitle();
    
    canvas_1 -> cd(2);
    canvas_1 -> Draw();
    canvas_1 -> SetGrid();
    invariant_mass_daughter_2_histogram -> Draw();
    invariant_mass_daughter_2_histogram -> GetXaxis() -> SetTitle("m daughter 2");
    invariant_mass_daughter_2_histogram -> GetXaxis() -> CenterTitle();
    invariant_mass_daughter_2_histogram -> GetYaxis() -> SetTitle("Events");
    invariant_mass_daughter_2_histogram -> GetYaxis() -> CenterTitle();

    canvas_1 -> Print("histogram_mass_daughters_one_and_two_second_analysis.png");

    canvas_2_1 -> cd(1);
    canvas_2_1 -> Draw();
    hs_1 -> Draw("nostack");
    hs_1 -> GetXaxis() -> SetTitle("id daughter 1");
    hs_1 -> GetXaxis() -> CenterTitle();
    hs_1 -> GetYaxis() -> SetTitle("Events");
    hs_1-> GetYaxis() -> CenterTitle();
    
    auto legend_2_1 = new TLegend(0.1, 0.7, 0.48, 0.9);
    legend_2_1 -> SetHeader("Legend", "C"); 
    legend_2_1 -> AddEntry(id_daughter_1_histogram_c_cbar, "c#bar{c}", "f");
    legend_2_1 -> AddEntry(id_daughter_1_histogram_photon, "photons", "f");
    legend_2_1 -> Draw();

    canvas_2_1 -> Print("id_histogram_daughters_1_c_cbar_and_photon.png");
    
    canvas_2_2 -> cd(1);
    canvas_2_2 -> Draw();
    hs_2 -> Draw("nostack");
    hs_2 -> GetXaxis() -> SetTitle("id daughter 2");
    hs_2 -> GetXaxis() -> CenterTitle();
    hs_2 -> GetYaxis() -> SetTitle("Events");
    hs_2 -> GetYaxis() -> CenterTitle();

    auto legend_2_2 = new TLegend(0.1, 0.7, 0.48, 0.9);
    legend_2_2 -> SetHeader("Legend", "C"); 
    legend_2_2 -> AddEntry(id_daughter_2_histogram_c_cbar, "c#bar{c}", "f");
    legend_2_2 -> AddEntry(id_daughter_2_histogram_photon, "photon", "f");
    legend_2_2 -> Draw();

    canvas_2_2 -> Print("id_histogram_daughters_2_c_cbar_and_photon.png");

    canvas_3 -> cd(1);
    canvas_3 -> Draw();
    invariant_mass_higgs -> Draw();
    invariant_mass_higgs -> GetXaxis() -> SetTitle("mH");
    invariant_mass_higgs -> GetYaxis() -> SetTitle("Events");
    invariant_mass_higgs -> GetXaxis() -> CenterTitle();
    invariant_mass_higgs -> GetYaxis() -> CenterTitle();
    
    canvas_3 -> Print("higgs_mass_histogram_second_analysis.png");

    pythia.stat();

    vector<int>().swap(loc_vector);
    vector<int>().swap(id_vector);
    vector<int>().swap(loc_id_daughter_1_vector);
    vector<int>().swap(loc_id_daughter_2_vector);
    vector<double>().swap(mass_vector);
    vector<double>().swap(pt_vector);
    vector<double>().swap(eta_vector);
    vector<double>().swap(phi_vector);
    vector<double>().swap(E_vector);
    vector<string>().swap(names_vector);

    loc_vector.clear();
    id_vector.clear();
    loc_id_daughter_1_vector.clear();
    loc_id_daughter_2_vector.clear();
    mass_vector.clear();
    pt_vector.clear();
    eta_vector.clear();
    phi_vector.clear();
    E_vector.clear();
    names_vector.clear();

    vector<int>().swap(id_c_cbar_vector_daughter_1);
    vector<int>().swap(id_c_cbar_vector_daughter_2);
    vector<int>().swap(id_c_cbar_vector_daughter_1_filter);
    vector<int>().swap(id_c_cbar_vector_daughter_2_filter);

    id_c_cbar_vector_daughter_1.clear();
    id_c_cbar_vector_daughter_2.clear();
    id_c_cbar_vector_daughter_1_filter.clear();
    id_c_cbar_vector_daughter_2_filter.clear();
    
    vector<int>().swap(id_photon_vector_daughter_1);
    vector<int>().swap(id_photon_vector_daughter_2);
    vector<int>().swap(id_photon_vector_daughter_1_filter);
    vector<int>().swap(id_photon_vector_daughter_2_filter);

    id_photon_vector_daughter_1.clear();
    id_photon_vector_daughter_2.clear();
    id_photon_vector_daughter_1_filter.clear();
    id_photon_vector_daughter_2_filter.clear();

    vector<double>().swap(pt_c);
    vector<double>().swap(pt_cbar);
    vector<double>().swap(eta_c);
    vector<double>().swap(eta_cbar);
    vector<double>().swap(phi_c);
    vector<double>().swap(phi_cbar);
    vector<double>().swap(E_c);
    vector<double>().swap(E_cbar); 

    pt_c.clear();
    pt_cbar.clear();
    eta_c.clear();
    eta_cbar.clear();
    phi_c.clear();
    phi_cbar.clear();
    E_c.clear();
    E_cbar.clear();
    
    vector<double>().swap(m_qq);
    vector<double>().swap(m_H);

    m_qq.clear();
    m_H.clear();
}

int main() 
{
    Int_t simulated_events = 10000; // each event is understood as a pp colition

    pythia_higgs_events_generator(simulated_events);

    return 0;
}
