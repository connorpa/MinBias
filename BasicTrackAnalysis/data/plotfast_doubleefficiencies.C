// IMPORTANT: there must be a directory "plots" in the directory where this macro is executed

void plotfast_doubleefficiencies (TString filename)
{
    TFile * f = new TFile(filename, "READ");

    gStyle->SetOptStat(0);
    gStyle->SetTitleFont(62);
    // tracks
    vector<TString> variables, titles;

    variables.push_back("pt_0");   titles.push_back("0 < |#eta| < 0.6");
    variables.push_back("pt_1");   titles.push_back("0.6 < |#eta| < 1.2");
    variables.push_back("pt_2");   titles.push_back("1.2 < |#eta| < 1.8");
    variables.push_back("pt_3");   titles.push_back("1.8 < |#eta| < 2.4");
    TCanvas * c_pt_eta       = new TCanvas ("c_pt_eta"),
            * c_pt_eta_ratio = new TCanvas ("c_pt_eta_ratio");
    c_pt_eta->Draw();
    c_pt_eta_ratio->Draw();
    TPad * pad[4];
    pad[0] = new TPad("pad1", "", 0.0, 0.55, 0.5, 1.0);
    pad[1] = new TPad("pad2", "", 0.5, 0.55, 1.0, 1.0);
    pad[2] = new TPad("pad3", "", 0.0, 0.1 , 0.5, 0.5);
    pad[3] = new TPad("pad4", "", 0.5, 0.1 , 1.0, 0.5);
    TPad * pad_legend = new TPad("p_leg", "", 0.0, 0.0, 1.0, 0.1);
    TLegend * legend_ratio = new TLegend(0.6, 0.6, 0.9, 0.9);
    for (unsigned int i = 0 ; i < variables.size() ; i++)
    {
        c_pt_eta->cd();  
        pad[i]->Draw();
        pad[i]->cd();
        TH1D * h_gen = (TH1D *) f->Get("GT_" + variables[i])->Clone();
        TH1D * h_rec = (TH1D *) f->Get("RT_" + variables[i])->Clone();
        h_gen->SetTitleFont(62);
        h_rec->SetTitleFont(62);
        h_gen->SetLineWidth(2);
        h_rec->SetLineWidth(2);
        h_gen->Draw();
        h_rec->SetLineColor(kRed);
        h_rec->Draw("SAME");
        pad[i]->SetLogy();
        pad[i]->SetGrid();

        c_pt_eta_ratio->cd();
        TH1D * h_eff = (TH1D *) f->Get("ratio_tracks_" + variables[i])->Clone();
        h_eff->SetTitle("transverse momentum efficiency in pseudorapidity bins");
        h_eff->SetTitleFont(62);
        h_eff->SetLineColor(i+2);
        h_eff->SetLineWidth(2);
        h_eff->SetMinimum(0);
        h_eff->SetMaximum(1);
        h_eff->Draw(i > 0 ? "SAME" : "");
        legend_ratio->AddEntry(h_eff, titles[i]);
    }

    TLegend * legend_pt_eta = new TLegend (0, 0, 1, 1, "", "NBNDC");
    TH1D * h1 = new TH1D ("generated_tracks"    ,"generated tracks"    , 1, 0, 1);
    TH1D * h2 = new TH1D ("reconstructed_tracks","reconstructed tracks", 1, 0, 1);
    h2->SetLineColor(kBlue);
    legend_pt_eta->AddEntry(h1, "gen");
    legend_pt_eta->AddEntry(h2, "rec");
    c_pt_eta->cd();
    pad_legend->Draw();
    legend_pt_eta->Draw();


    c_pt_eta_ratio->cd();
    c_pt_eta_ratio->SetGrid();
    legend_ratio->Draw();
    c_pt_eta_ratio->WaitPrimitive();
    TString name_ratio = "plots/" + filename;
    name_ratio.ReplaceAll(".root", "pt_eta_bin_eff.pdf");
    c_pt_eta_ratio->Print(name_ratio, "pdf");

    //c_pt_eta->WaitPrimitive();
    TString name = "plots/" + filename;
    name.ReplaceAll(".root", "pt_eta_bin.pdf");
    c_pt_eta->Print(name, "pdf");
    delete c_pt_eta;
    delete c_pt_eta_ratio;
}
