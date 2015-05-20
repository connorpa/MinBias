// IMPORTANT: there must be a directory "plots" in the directory where this macro is executed

void plotfast_singleefficiencies (TString filename)
{
    TFile * f = new TFile(filename, "READ");

    gStyle->SetOptStat(0);
    gStyle->SetTitleFont(62);
    // tracks
    vector<TString> variables, titles;
    variables.push_back("pt");     titles.push_back("transverse momentum");
    variables.push_back("eta");    titles.push_back("pseudorapidity");
    variables.push_back("phi");    titles.push_back("azimuthal angle");
    variables.push_back("M");      titles.push_back("multiplicity");
    for (unsigned int ivar = 0 ; ivar < variables.size() ; ivar++)
    {
        TCanvas * c = new TCanvas ("c_" + variables[ivar], variables[ivar], 594, 842);
        c->Draw();
        TPad * p_main   = new TPad("p_main"  , titles[ivar], 0.0, 0.5, 1.0, 1.0),
             * p_ratio  = new TPad("p_ratio" , "efficiency", 0.0, 0.0, 1.0, 0.5);
             //* p_legend = new TPad("p_legend", "legend"    , 0.0, 0.0, 1.0, 0.1);

        p_main->Draw();
        p_main->cd();
        TH1D * h_gen = (TH1D *) f->Get("GT_" + variables[ivar])->Clone();
        TH1D * h_rec = (TH1D *) f->Get("RT_" + variables[ivar])->Clone();
        h_gen->SetTitle("");
        h_rec->SetTitle("");
        if (variables[ivar] == "pt" || variables[ivar] == "M") p_main->SetLogy();
        h_gen->Draw();
        h_rec->SetLineColor(kRed);
        h_rec->SetLineWidth(2);
        h_gen->SetLineWidth(2);
        h_rec->Draw("SAME");
        p_main->SetGrid();

        c->cd();
        p_ratio->Draw();
        p_ratio->cd();
        TH1D * h_eff = (TH1D *) f->Get("ratio_tracks_" + variables[ivar])->Clone();
        h_eff->SetTitleFont(62);
        h_eff->SetLineColor(kBlack);
        h_eff->SetLineWidth(2);
        h_eff->SetMinimum(0);
        h_eff->SetMaximum(1);
        h_eff->Draw();
        p_ratio->SetGrid();

        c->cd();
        //p_legend->Draw();
        //p_legend->cd();
        p_main->cd();
        TLegend * legend = new TLegend (0.6, 0.6, 0.9, 0.9, "", "NBNDC");
        legend->SetLineWidth(0);
        legend->AddEntry(h_gen, "gen");
        legend->AddEntry(h_rec, "rec");
        legend->AddEntry(h_eff, "gen/rec");
        legend->Draw();

        c->WaitPrimitive();
        TString name = "plots/" + filename;
        name.ReplaceAll(".root", variables[ivar] + ".pdf");
        c->Print(name, "pdf");
        delete h_gen;
        delete h_rec;
        delete h_eff;
        delete p_main  ;
        delete p_ratio ;
        delete c;
    }
}
