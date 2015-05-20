// IMPORTANT: there must be a directory "plots" in the directory where this macro is executed

void plotfast_vertices (TString filename)
{
    TFile * f = new TFile(filename, "READ");

    gStyle->SetOptStat(0);
    gStyle->SetTitleFont(62);
    // tracks
    vector<TString> variables, titles;
    variables.push_back("x");
    variables.push_back("y");
    variables.push_back("z");
    for (unsigned int ivar = 0 ; ivar < variables.size() ; ivar++)
    {
        TCanvas * c = new TCanvas ("c_" + variables[ivar], variables[ivar], 842, 594);
        c->Draw();
        TH1D * h_gen = (TH1D *) f->Get("GV_" + variables[ivar])->Clone();
        TH1D * h_rec = (TH1D *) f->Get("RV_" + variables[ivar])->Clone();
        h_rec->SetTitle("");
        h_gen->SetTitle("");
        h_gen->SetXTitle(variables[ivar] + "/mm");
        h_gen->SetLineWidth(2);
        h_rec->SetLineWidth(2);
        h_rec->SetLineColor(kRed);
        TLegend * legend = new TLegend (0.75, 0.75, 0.9, 0.9);
        legend->SetLineWidth(0);
        legend->SetFillColor(0);
        h_gen->Draw();
        h_rec->Draw("SAME");
        legend->AddEntry(h_gen, "gen");
        legend->AddEntry(h_rec, "rec");
        legend->Draw();
        c->SetGrid();
        c->WaitPrimitive();
        TString name = "plots/" + filename;
        name.ReplaceAll(".root", variables[ivar] + ".pdf");
        c->Print(name, "pdf");
        delete h_gen;
        delete h_rec;
        delete c;
    }
}
