{
  TGraphErrors* gsigmaMCP = new TGraphErrors();
  TGraphErrors* gsigmaPlana = new TGraphErrors();
  TGraphErrors* gefficiency = new TGraphErrors();

  float sigmaMCP, sigmaMCPE, sigmaMean, sigmaMeanE, sigmaPlana, sigmaPlanaE, efficiency, efficiencyE;
  float HV_value[7] = {2150, 2250, 2050, 1950, 2350, 2250, 2250};
  float HV_RUN[7] = {5, 6, 7, 8, 9, 10, 12};

  for(int i=0; i<7; ++i){
    std::ifstream inFile(Form("analyzed_data/WFRun%03d.txt",int(HV_RUN[i])), std::ios::in);
      inFile >> sigmaMCP >> sigmaMCPE >> sigmaMean >> sigmaMeanE >> sigmaPlana >> sigmaPlanaE >> efficiency >> efficiencyE;

      //      gsigmaMCP->SetPoint(i, HV_RUN[i], sigmaMCP);
      gsigmaMCP->SetPoint(i, HV_value[i], sigmaMCP);
      gsigmaMCP->SetPointError(i, 0, sigmaMCPE);

      //gsigmaPlana->SetPoint(i, HV_RUN[i], sigmaPlana);
      gsigmaPlana->SetPoint(i, HV_value[i], sigmaPlana);
      gsigmaPlana->SetPointError(i, 0, sigmaPlanaE);

      //gefficiency->SetPoint(i, HV_RUN[i], efficiency);
      gefficiency->SetPoint(i, HV_value[i], efficiency);
      gefficiency->SetPointError(i, 0, efficiencyE);

      inFile.close ();
      std::cout << " run " << Form("WFRun%03d/dat",i+5) << " eff = " << efficiency << " +/- " << efficiencyE << std::endl; 
  }

  TCanvas* cSMCP = new TCanvas();
  gPad->SetGrid();
  gsigmaMCP->GetXaxis()->SetTitle("RUN");
  gsigmaMCP->GetYaxis()->SetRangeUser(0, 0.1);
  gsigmaMCP->GetYaxis()->SetTitle("#sigma MCP (ns)");
  gsigmaMCP->Draw("ap");
  cSMCP->Print("gsigmaMCP.png", "png");
  
  TCanvas* cSPlana = new TCanvas();
  gPad->SetGrid();
  gsigmaPlana->GetXaxis()->SetTitle("RUN");
  gsigmaPlana->GetYaxis()->SetRangeUser(0, 0.2);
  gsigmaPlana->GetYaxis()->SetTitle("#sigma Planacon (ns)");
  gsigmaPlana->Draw("ap");
  cSPlana->Print("gsigmaPlana.png", "png");
  
  TCanvas* cSEfficiency = new TCanvas();
  gPad->SetGrid();
  gefficiency->GetXaxis()->SetTitle("RUN");
  gefficiency->GetYaxis()->SetRangeUser(0, 100);
  gefficiency->GetYaxis()->SetTitle("eff. (%)");
  gefficiency->Draw("ap");
  cSEfficiency->Print("gefficiency.png", "png");
}
