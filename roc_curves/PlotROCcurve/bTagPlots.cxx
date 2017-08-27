/*
 * bTagPlots.cxx
 * 
 * Copyright 2017 Praveen C Tiwari <ptiwari@Planet-Earth>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include "TInterpreter.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TFile.h"
#include "TH2.h"
#include "TNtuple.h"
#include "TPaveLabel.h"
#include "TPaveText.h"
#include "TFrame.h"
#include "TSystem.h"
#include "TInterpreter.h"
#include "TAttLine.h"
#include "TAttMarker.h"


void jetCSVROC(string filename, string name, string save, string xlabel, string suff = "hltCombinedSecondaryVertexBJetTagsCalo", float xlow = 0., float xhigh = 200., int rebin = 10, float bottom = 0., float top = 5000.) {
  gROOT->ForceStyle();
  gStyle->SetOptTitle(0);
  TFile *file0 = new TFile(Form("DQM_V0001_R000000001__CMSSW_X_Y_Z__RelVal__TrigVal.root"));
  TH1F  *h_bjet_light_mistag_eff = (TH1F*)file0->Get("DQMData/Run 1/HLT/Run summary/BTag/Discriminator/HLT_PFHT380_SixJet32_DoubleBTagCSV_p075_v1/efficiency/hltCombinedSecondaryVertexBJetTagsCalo_b_light_mistagrate");
  TH1F  *h_bjet_c_mistag_eff = (TH1F*)file0->Get("DQMData/Run 1/HLT/Run summary/BTag/Discriminator/HLT_PFHT380_SixJet32_DoubleBTagCSV_p075_v1/efficiency/hltCombinedSecondaryVertexBJetTagsCalo_b_c_mistagrate");


  h_bjet_c_mistag_eff->SetName("hltCombinedSecondaryVertexBJetTagsCalo");
  h_bjet_c_mistag_eff->SetTitle("b vs c efficiency");
  h_bjet_light_mistag_eff->SetTitle("b vs light efficiency");

  //h_bjet_c_mistag_eff->SetLineColor(kRed);
   h_bjet_c_mistag_eff->SetMarkerColor(kRed);
   h_bjet_c_mistag_eff->SetMarkerStyle(20);
  //h_bjet_c_mistag_eff->SetLineWidth(2);
  h_bjet_c_mistag_eff->SetMarkerSize(1);

  h_bjet_light_mistag_eff->SetMarkerColor(kBlue);
  h_bjet_light_mistag_eff->SetMarkerStyle(21);
  //h_bjet_light_mistag_eff->SetLineColor(kBlue);
  //h_bjet_light_mistag_eff->SetLineWidth(2);
  h_bjet_light_mistag_eff->SetMarkerSize(1);

  TCanvas *caloCSVroc = new TCanvas("caloCSVroc","caloCSVroc",10,10,1366,1080);
  caloCSVroc->SetGrid();
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  caloCSVroc->SetLogy();
  h_bjet_c_mistag_eff->GetYaxis()->SetTitle("mistagrate");
  h_bjet_c_mistag_eff->GetXaxis()->SetTitle(xlabel.c_str());
  h_bjet_c_mistag_eff->GetYaxis()->SetRangeUser(0.0001,1);
  h_bjet_c_mistag_eff->GetYaxis()->SetRangeUser(0.0001,1);
  h_bjet_c_mistag_eff->Draw("p hist");
  h_bjet_light_mistag_eff->Draw("p hist same");
  caloCSVroc->BuildLegend(0.11,0.8,0.3,0.9);
  mylatex1 = new TLatex(0.3,1.2,"hltCombinedSecondaryVertexBJetTagsCalo"); // coordinates are absolute here
  mylatex1->SetTextSize(0.02);
  mylatex1->Draw();

  caloCSVroc->SaveAs(Form("CSV_Calo_ROC.pdf"));
}
void jetCSVROC_PF(string filename, string name, string save, string xlabel, string suff = "hltCombinedSecondaryVertexBJetTagsPF", float xlow = 0., float xhigh = 200., int rebin = 10, float bottom = 0., float top = 5000.) {
  gROOT->ForceStyle();
  gStyle->SetOptTitle(0);
  TFile *file = new TFile(Form("DQM_V0001_R000000001__CMSSW_X_Y_Z__RelVal__TrigVal.root"));
  TH1F  *h_bjet_light_mistag_eff = (TH1F*)file->Get("DQMData/Run 1/HLT/Run summary/BTag/Discriminator/HLT_PFHT380_SixJet32_DoubleBTagCSV_p075_v1/efficiency/hltCombinedSecondaryVertexBJetTagsPF_b_light_mistagrate");
  TH1F  *h_bjet_c_mistag_eff = (TH1F*)file->Get("DQMData/Run 1/HLT/Run summary/BTag/Discriminator/HLT_PFHT380_SixJet32_DoubleBTagCSV_p075_v1/efficiency/hltCombinedSecondaryVertexBJetTagsPF_b_c_mistagrate");


  h_bjet_c_mistag_eff->SetName("hltCombinedSecondaryVertexBJetTagsPF");
  h_bjet_c_mistag_eff->SetTitle("b vs c efficiency");
  h_bjet_light_mistag_eff->SetTitle("b vs light efficiency");

  //h_bjet_c_mistag_eff->SetLineColor(kRed);
   h_bjet_c_mistag_eff->SetMarkerColor(kRed);
   h_bjet_c_mistag_eff->SetMarkerStyle(20);
  //h_bjet_c_mistag_eff->SetLineWidth(2);
  h_bjet_c_mistag_eff->SetMarkerSize(1);

  h_bjet_light_mistag_eff->SetMarkerColor(kBlue);
  h_bjet_light_mistag_eff->SetMarkerStyle(21);
  //h_bjet_light_mistag_eff->SetLineColor(kBlue);
  //h_bjet_light_mistag_eff->SetLineWidth(2);
  h_bjet_light_mistag_eff->SetMarkerSize(1);

  TCanvas *pfCSVroc = new TCanvas("pfCSVroc","pfCSVroc",10,10,1366,1080);
  pfCSVroc->SetGrid();
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  pfCSVroc->SetLogy();
  h_bjet_c_mistag_eff->GetYaxis()->SetTitle("mistagrate");
  h_bjet_c_mistag_eff->GetXaxis()->SetTitle(xlabel.c_str());
  h_bjet_c_mistag_eff->GetYaxis()->SetRangeUser(0.0001,1);
  h_bjet_c_mistag_eff->GetYaxis()->SetRangeUser(0.0001,1);
  h_bjet_c_mistag_eff->Draw("p hist");
  h_bjet_light_mistag_eff->Draw("p hist same");
  pfCSVroc->BuildLegend(0.11,0.8,0.3,0.9);
  mylatex1 = new TLatex(0.3,1.2,"hltCombinedSecondaryVertexBJetTagsPF"); // coordinates are absolute here
  mylatex1->SetTextSize(0.02);
  mylatex1->Draw();

  pfCSVroc->SaveAs(Form("CSV_PF_ROC.pdf"));
}

void jetCSVROC_DeepCSV(string filename, string name, string save, string xlabel, string suff = "hltDeepCombinedSecondaryVertexBJetTagsCalo", float xlow = 0., float xhigh = 200., int rebin = 1, float bottom = 0., float top = 5000.) {
  gROOT->ForceStyle();
  gStyle->SetOptTitle(0);
  TFile *file = new TFile(Form("DQM_V0001_R000000001__CMSSW_X_Y_Z__RelVal__TrigVal.root"));
  TH1F  *h_bjet_light_mistag_eff = (TH1F*)file->Get("DQMData/Run 1/HLT/Run summary/BTag/Discriminator/HLT_PFHT380_SixJet32_DoubleBTagDeepCSV_p051_v1/efficiency/hltDeepCombinedSecondaryVertexBJetTagsCalo_b_light_mistagrate");
  TH1F  *h_bjet_c_mistag_eff = (TH1F*)file->Get("DQMData/Run 1/HLT/Run summary/BTag/Discriminator/HLT_PFHT380_SixJet32_DoubleBTagDeepCSV_p051_v1/efficiency/hltDeepCombinedSecondaryVertexBJetTagsCalo_b_c_mistagrate");


  h_bjet_c_mistag_eff->SetName("hltDeepCombinedSecondaryVertexBJetTagsCalo");
  h_bjet_c_mistag_eff->SetTitle("b vs c efficiency");
  h_bjet_light_mistag_eff->SetTitle("b vs light efficiency");

  //h_bjet_c_mistag_eff->SetLineColor(kRed);
   h_bjet_c_mistag_eff->SetMarkerColor(kRed);
   h_bjet_c_mistag_eff->SetMarkerStyle(20);
  //h_bjet_c_mistag_eff->SetLineWidth(2);
  h_bjet_c_mistag_eff->SetMarkerSize(1);

  h_bjet_light_mistag_eff->SetMarkerColor(kBlue);
  h_bjet_light_mistag_eff->SetMarkerStyle(21);
  //h_bjet_light_mistag_eff->SetLineColor(kBlue);
  //h_bjet_light_mistag_eff->SetLineWidth(2);
  h_bjet_light_mistag_eff->SetMarkerSize(1);

  TCanvas *caloDeepCSVroc = new TCanvas("caloDeepCSVroc","caloDeepCSVroc",10,10,1366,1080);
  caloDeepCSVroc->SetGrid();
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  caloDeepCSVroc->SetLogy();
  h_bjet_c_mistag_eff->GetYaxis()->SetTitle("mistagrate");
  h_bjet_c_mistag_eff->GetXaxis()->SetTitle(xlabel.c_str());
  h_bjet_c_mistag_eff->GetYaxis()->SetRangeUser(0.0001,1);
  h_bjet_c_mistag_eff->GetYaxis()->SetRangeUser(0.0001,1);
  h_bjet_c_mistag_eff->Draw("p hist");
  h_bjet_light_mistag_eff->Draw("p hist same");
  caloDeepCSVroc->BuildLegend(0.11,0.8,0.3,0.9);
  mylatex1 = new TLatex(0.3,1.2,"hltDeepCombinedSecondaryVertexBJetTagsCalo"); // coordinates are absolute here
  mylatex1->SetTextSize(0.02);
  mylatex1->Draw();

  caloDeepCSVroc->SaveAs(Form("DeepCSV_Calo_ROC.pdf"));
}
void jetCSVROC_PF_DeepCSV(string filename, string name, string save, string xlabel, string suff = "hltDeepCombinedSecondaryVertexBJetTagsPF", float xlow = 0., float xhigh = 200., int rebin = 1, float bottom = 0., float top = 5000.) {
  gROOT->ForceStyle();
  gStyle->SetOptTitle(0);
  TFile *file = new TFile(Form("DQM_V0001_R000000001__CMSSW_X_Y_Z__RelVal__TrigVal.root"));
  TH1F  *h_bjet_light_mistag_eff = (TH1F*)file->Get("DQMData/Run 1/HLT/Run summary/BTag/Discriminator/HLT_PFHT380_SixJet32_DoubleBTagDeepCSV_p051_v1/efficiency/hltDeepCombinedSecondaryVertexBJetTagsPF_b_light_mistagrate");
  TH1F  *h_bjet_c_mistag_eff = (TH1F*)file->Get("DQMData/Run 1/HLT/Run summary/BTag/Discriminator/HLT_PFHT380_SixJet32_DoubleBTagDeepCSV_p051_v1/efficiency/hltDeepCombinedSecondaryVertexBJetTagsPF_b_c_mistagrate");


  h_bjet_c_mistag_eff->SetName("hltDeepCombinedSecondaryVertexBJetTagsPF");
  h_bjet_c_mistag_eff->SetTitle("b vs c efficiency");
  h_bjet_light_mistag_eff->SetTitle("b vs light efficiency");

  //h_bjet_c_mistag_eff->SetLineColor(kRed);
   h_bjet_c_mistag_eff->SetMarkerColor(kRed);
   h_bjet_c_mistag_eff->SetMarkerStyle(20);
  //h_bjet_c_mistag_eff->SetLineWidth(2);
  h_bjet_c_mistag_eff->SetMarkerSize(1);

  h_bjet_light_mistag_eff->SetMarkerColor(kBlue);
  h_bjet_light_mistag_eff->SetMarkerStyle(21);
  //h_bjet_light_mistag_eff->SetLineColor(kBlue);
  //h_bjet_light_mistag_eff->SetLineWidth(2);
  h_bjet_light_mistag_eff->SetMarkerSize(1);

  TCanvas *pfDeepCSVroc = new TCanvas("pfDeepCSVroc","pfDeepCSVroc",10,10,1366,1080);
  pfDeepCSVroc->SetGrid();
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  pfDeepCSVroc->SetLogy();
  h_bjet_c_mistag_eff->GetYaxis()->SetTitle("mistagrate");
  h_bjet_c_mistag_eff->GetXaxis()->SetTitle(xlabel.c_str());
  h_bjet_c_mistag_eff->GetYaxis()->SetRangeUser(0.0001,1);
  h_bjet_c_mistag_eff->GetYaxis()->SetRangeUser(0.0001,1);
  h_bjet_c_mistag_eff->Draw("p hist");
  h_bjet_light_mistag_eff->Draw("p hist same");
  pfDeepCSVroc->BuildLegend(0.11,0.8,0.3,0.9);
  mylatex1 = new TLatex(0.3,1.2,"hltDeepCombinedSecondaryVertexBJetTagsPF"); // coordinates are absolute here
  mylatex1->SetTextSize(0.02);
  mylatex1->Draw();

  pfDeepCSVroc->SaveAs(Form("DeepCSV_PF_ROC.pdf"));
}
void bTagPlots(){
   jetCSVROC("CSVv2 ROC Curve", "hltCombinedSecondaryVertexBJetTagsCalo", "ttbar", "b-jet efficiency","",0.,100);
   jetCSVROC_PF("CSVv2 ROC Curve", "hltCombinedSecondaryVertexBJetTagsPF", "ttbar", "b-jet efficiency","",0.,100);   
   jetCSVROC_DeepCSV("DeepCSV ROC Curve", "hltDeepCombinedSecondaryVertexBJetTagsCalo", "ttbar", "b-jet efficiency","",0.,100);
   jetCSVROC_PF_DeepCSV("DeepCSV ROC Curve", "hltDeepCombinedSecondaryVertexBJetTagsPF", "ttbar", "b-jet efficiency","",0.,100); 
 }

