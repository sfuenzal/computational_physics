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
    
    vector<int> id_photon_vector_daughter_1;
    vector<int> id_photon_vector_daughter_2;
    vector<int> id_photon_vector_daughter_1_filter;
    vector<int> id_photon_vector_daughter_2_filter;
    
    vector<int> id_gluon_vector_daughter_1;
    vector<int> id_gluon_vector_daughter_2;
    vector<int> id_gluon_vector_daughter_1_filter;
    vector<int> id_gluon_vector_daughter_2_filter;

    vector<double> pt_photon_1;
    vector<double> pt_photon_2;
    vector<double> eta_photon_1;
    vector<double> eta_photon_2;
    vector<double> phi_photon_1;
    vector<double> phi_photon_2;
    vector<double> E_photon_1;
    vector<double> E_photon_2;

    vector<double> m_yy;
    vector<double> m_yy_filter;

    TCanvas *canvas_1 = new TCanvas("canvas_1", "canvas_1", 10, 10, 900, 600);
    canvas_1 -> Divide(2, 1);
    TH1F *invariant_mass_daughter_1_histogram = new TH1F("Information D1", "Daughter 1 masses [GeV]", 20, 0, 2.2);
    invariant_mass_daughter_1_histogram -> SetMarkerSize(2.0);
    invariant_mass_daughter_1_histogram -> SetLineColor(kBlue);
    invariant_mass_daughter_1_histogram -> SetFillColor(kBlue - 10);

    TH1F *invariant_mass_daughter_2_histogram = new TH1F("Information D2", "Daughter 2 masses [GeV]", 20, 0, 2.2);
    invariant_mass_daughter_2_histogram -> SetMarkerSize(2.0);
    invariant_mass_daughter_2_histogram -> SetLineColor(kRed);
    invariant_mass_daughter_2_histogram -> SetFillColor(kRed - 10);

    TCanvas *canvas_2_1 = new TCanvas("canvas_2_1", "canvas_2_1", 10, 10, 900, 600);
    canvas_2_1 -> Divide(1, 1);
    THStack *hs_1 = new THStack("hs_1", "id daughters one");
    TH1F *id_daughter_1_histogram_photon = new TH1F("Information D1 #gamma", "id daughter 1 photon", 10, 20, 23);
    id_daughter_1_histogram_photon -> SetMarkerSize(2.0);
    id_daughter_1_histogram_photon -> SetLineColor(kBlue);
    id_daughter_1_histogram_photon -> SetFillColor(kBlue - 10);
    TH1F *id_daughter_1_histogram_gluon = new TH1F("Information D1 g", "id daughter 1 gluon", 10, 20, 23);
    id_daughter_1_histogram_gluon -> SetMarkerSize(2.0);
    id_daughter_1_histogram_gluon -> SetLineColor(kRed);
    id_daughter_1_histogram_gluon -> SetFillColor(kRed - 10);
    
    TCanvas *canvas_2_2 = new TCanvas("canvas_2_2", "canvas_2_2", 10, 10, 900, 600);
    canvas_2_2 -> Divide(1, 1);
    THStack *hs_2 = new THStack("hs_1", "id daughters two");
    TH1F *id_daughter_2_histogram_photon = new TH1F("Information D2 #gamma", "id daughter 2 photon", 10, 20, 23);
    id_daughter_2_histogram_photon -> SetMarkerSize(2.0);
    id_daughter_2_histogram_photon -> SetLineColor(kBlue);
    id_daughter_2_histogram_photon -> SetFillColor(kBlue - 10);
    TH1F *id_daughter_2_histogram_gluon = new TH1F("Information D2 g", "id daughter 2 gluon", 10, 20, 23);
    id_daughter_2_histogram_gluon -> SetMarkerSize(2.0);
    id_daughter_2_histogram_gluon -> SetLineColor(kRed);
    id_daughter_2_histogram_gluon -> SetFillColor(kRed - 10);

    TCanvas *canvas_3 = new TCanvas("canvas_3", "canvas_3", 10, 10, 900, 600);
    canvas_3 -> Divide(1, 1);
    TH1F *invariant_mass_higgs = new TH1F("Information", "Invariant mass Higgs boson [GeV]", 8, 120, 130);
    invariant_mass_higgs -> SetMarkerSize(2.0);
    invariant_mass_higgs -> SetLineColor(kBlue);
    invariant_mass_higgs -> SetFillColor(kBlue - 10);
    
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
        if (id_daughter_1_vector_filter[i] == 22 && id_daughter_2_vector_filter[i] == 22) //photon
        {
            id_photon_vector_daughter_1.push_back(id_daughter_1_vector_filter[i]);
            id_photon_vector_daughter_2.push_back(id_daughter_2_vector_filter[i]); 
        }
    }

    for (Int_t i = 0; i < number_of_events; ++i)
    {
        if (id_daughter_1_vector_filter[i] == 21 && id_daughter_2_vector_filter[i] == 21) //gluon
        {
            id_gluon_vector_daughter_1.push_back(id_daughter_1_vector_filter[i]);
            id_gluon_vector_daughter_2.push_back(id_daughter_2_vector_filter[i]); 
        }
    }

    for (Int_t i = 0; i < number_of_events; ++i)
    {
        if (id_daughter_1_vector_filter[i] == 22 && id_daughter_1_vector_filter[i] == 22)
        {
            pt_photon_1.push_back(pt_vector_daughter_1_filter[i]);
            pt_photon_2.push_back(pt_vector_daughter_2_filter[i]);
        }
    }

    for (Int_t i = 0; i < number_of_events; ++i)
    {
        if (id_daughter_1_vector_filter[i] == 22 && id_daughter_1_vector_filter[i] == 22)
        {
            eta_photon_1.push_back(eta_vector_daughter_1_filter[i]);
            eta_photon_2.push_back(eta_vector_daughter_2_filter[i]);
        }
    }

    for (Int_t i = 0; i < number_of_events; ++i)
    {
        if (id_daughter_1_vector_filter[i] == 22 && id_daughter_1_vector_filter[i] == 22)
        {
            phi_photon_1.push_back(phi_vector_daughter_1_filter[i]);
            phi_photon_2.push_back(phi_vector_daughter_2_filter[i]);
        }
    }

    for (Int_t i = 0; i < number_of_events; ++i)
    {
        if (id_daughter_1_vector_filter[i] == 22 && id_daughter_1_vector_filter[i] == 22)
        {
            E_photon_1.push_back(E_vector_daughter_1_filter[i]);
            E_photon_2.push_back(E_vector_daughter_2_filter[i]);
        }
    }

    //filters
    copy_if (id_photon_vector_daughter_1.begin(), id_photon_vector_daughter_1.end(), back_inserter(id_photon_vector_daughter_1_filter), [](int i){return i != 0;} );
    copy_if (id_photon_vector_daughter_2.begin(), id_photon_vector_daughter_2.end(), back_inserter(id_photon_vector_daughter_2_filter), [](int i){return i != 0;} );
    
    copy_if (id_gluon_vector_daughter_1.begin(), id_gluon_vector_daughter_1.end(), back_inserter(id_gluon_vector_daughter_1_filter), [](int i){return i != 0;} );
    copy_if (id_gluon_vector_daughter_2.begin(), id_gluon_vector_daughter_2.end(), back_inserter(id_gluon_vector_daughter_2_filter), [](int i){return i != 0;} );
     
    for (Int_t i = 0; i < id_photon_vector_daughter_1_filter.size(); ++i)
    {
        id_daughter_1_histogram_photon -> Fill(id_photon_vector_daughter_1_filter[i]);
        hs_1 -> Add(id_daughter_1_histogram_photon);
    }
    
    for (Int_t i = 0; i < id_gluon_vector_daughter_1_filter.size(); ++i)
    {
        id_daughter_1_histogram_gluon -> Fill(id_gluon_vector_daughter_1_filter[i]);
        hs_1 -> Add(id_daughter_1_histogram_gluon);
    }

    for (Int_t i = 0; i < id_photon_vector_daughter_2_filter.size(); ++i)
    {
        id_daughter_2_histogram_photon -> Fill(id_photon_vector_daughter_2_filter[i]);
        hs_2 -> Add(id_daughter_2_histogram_photon);
    }

    for (Int_t i = 0; i < id_gluon_vector_daughter_2_filter.size(); ++i)
    {
        id_daughter_2_histogram_gluon -> Fill(id_gluon_vector_daughter_2_filter[i]);
        hs_2 -> Add(id_daughter_2_histogram_gluon);
    }

    // diphoton mass higgs

    TLorentzVector Photon_1  = TLorentzVector();
	TLorentzVector Photon_2  = TLorentzVector();

    for (Int_t i = 0; i < pt_photon_1.size(); ++i)
    {
        Photon_1.SetPtEtaPhiE(pt_photon_1.at(i), eta_photon_1.at(i), phi_photon_1.at(i), E_photon_1.at(i));
        Photon_2.SetPtEtaPhiE(pt_photon_2.at(i), eta_photon_2.at(i), phi_photon_2.at(i), E_photon_2.at(i));
    }

    Double_t dPhi_yy[pt_photon_1.size()];
 
    //for (Int_t i = 0; i < pt_photon_1.size(); ++i)
    //{
        //dPhi_yy[i] = Photon_1.DeltaPhi(Photon_2);
    //}

    for (Int_t i = 0; i < pt_photon_1.size(); ++i)
    {
        dPhi_yy[i] = TMath::Abs( phi_photon_1[i] - phi_photon_2[i] );
        dPhi_yy[i] = dPhi_yy[i] < TMath::Pi() ? dPhi_yy[i] : 2*TMath::Pi() - dPhi_yy[i];
    }

    //TLorentzVector Higgs = Photon_1 + Photon_2;

    for (Int_t i = 0; i < pt_photon_1.size(); ++i)
    {
        m_yy.push_back(TMath::Sqrt( 2 * Photon_1.Pt() * Photon_2.Pt() * ( TMath::CosH( Photon_1.Eta() - Photon_2.Eta() ) - TMath::Cos( dPhi_yy[i] ) ) )*1000 - 10);
        //m_yy.push_back(Higgs.M());
    }

    // Photon1.SetPtEtaPhiM(...);

    copy_if (m_yy.begin(), m_yy.end(), back_inserter(m_yy_filter), [](int i){return (i > 121 && i < 129);} );

    for (Int_t i = 0; i < m_yy_filter.size(); ++i)
    {
       invariant_mass_higgs -> Fill(m_yy_filter[i]);
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

    canvas_1 -> Print("histogram_mass_daughters_one_and_two.png");

    canvas_2_1 -> cd(1);
    canvas_2_1 -> Draw();
    canvas_2_1 -> SetGrid();
    hs_1 -> Draw("nostack");
    hs_1 -> GetXaxis() -> SetTitle("id daughter 1");
    hs_1 -> GetXaxis() -> CenterTitle();
    hs_1 -> GetYaxis() -> SetTitle("Events");
    hs_1-> GetYaxis() -> CenterTitle();
    
    auto legend_2_1 = new TLegend(0.9, 0.7, 0.48, 0.9);
    legend_2_1 -> SetHeader("Legend", "C"); 
    legend_2_1 -> AddEntry(id_daughter_1_histogram_photon, "Photons", "f");
    legend_2_1 -> AddEntry(id_daughter_1_histogram_gluon, "Gluons", "f");
    legend_2_1 -> Draw();

    canvas_2_1 -> Print("id_histogram_daughters_1_photon_and_gluon.png");
    
    canvas_2_2 -> cd(1);
    canvas_2_2 -> Draw();
    canvas_2_2 -> SetGrid();
    hs_2 -> Draw("nostack");
    hs_2 -> GetXaxis() -> SetTitle("id daughter 2");
    hs_2 -> GetXaxis() -> CenterTitle();
    hs_2 -> GetYaxis() -> SetTitle("Events");
    hs_2 -> GetYaxis() -> CenterTitle();

    auto legend_2_2 = new TLegend(0.9, 0.7, 0.48, 0.9);
    legend_2_2 -> SetHeader("Legend", "C"); 
    legend_2_2 -> AddEntry(id_daughter_2_histogram_photon, "Photons", "f");
    legend_2_2 -> AddEntry(id_daughter_2_histogram_gluon, "Gluons", "f");
    legend_2_2 -> Draw();

    canvas_2_2 -> Print("id_histogram_daughters_2_photon_and_gluon.png");

    canvas_3 -> cd(1);
    canvas_3 -> Draw();
    canvas_3 -> SetGrid();
    invariant_mass_higgs -> Draw();
    invariant_mass_higgs -> GetXaxis() -> SetTitle("myy");
    invariant_mass_higgs -> GetXaxis() -> CenterTitle();
    invariant_mass_higgs -> GetYaxis() -> SetTitle("Events");
    invariant_mass_higgs -> GetYaxis() -> CenterTitle();
 
    canvas_3 -> Print("higgs_mass_histogram.png");

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

    vector<int>().swap(id_photon_vector_daughter_1);
    vector<int>().swap(id_photon_vector_daughter_2);
    vector<int>().swap(id_photon_vector_daughter_1_filter);
    vector<int>().swap(id_photon_vector_daughter_2_filter);

    id_photon_vector_daughter_1.clear();
    id_photon_vector_daughter_2.clear();
    id_photon_vector_daughter_1_filter.clear();
    id_photon_vector_daughter_2_filter.clear();
    
    vector<int>().swap(id_gluon_vector_daughter_1);
    vector<int>().swap(id_gluon_vector_daughter_2);
    vector<int>().swap(id_gluon_vector_daughter_1_filter);
    vector<int>().swap(id_gluon_vector_daughter_2_filter);

    id_gluon_vector_daughter_1.clear();
    id_gluon_vector_daughter_2.clear();
    id_gluon_vector_daughter_1_filter.clear();
    id_gluon_vector_daughter_2_filter.clear();

    vector<double>().swap(pt_photon_1);
    vector<double>().swap(pt_photon_2);
    vector<double>().swap(eta_photon_1);
    vector<double>().swap(eta_photon_2);
    vector<double>().swap(phi_photon_1);
    vector<double>().swap(phi_photon_2);
    vector<double>().swap(E_photon_1);
    vector<double>().swap(E_photon_2); 

    pt_photon_1.clear();
    pt_photon_2.clear();
    eta_photon_1.clear();
    eta_photon_2.clear();
    phi_photon_1.clear();
    phi_photon_2.clear();
    E_photon_1.clear();
    E_photon_2.clear();
    
    vector<double>().swap(m_yy);
    vector<double>().swap(m_yy_filter);

    m_yy.clear();
    m_yy_filter.clear();
}

int main() 
{
    Int_t simulated_events = 10000; // each event is understood as a pp colition

    pythia_higgs_events_generator(simulated_events);

    return 0;
}
