#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TH2D.h>
#include <TH1D.h>
#include <TDirectoryFile.h>
#include <string>
#include <TCanvas.h>
#include <TMath.h>
#include <TApplication.h>
#include <cstdlib>
#include <cmath>
#include <TGraph.h>
using namespace std;

double mydist(double,double);
double fRand(double,double);


int main() {

  
  TFile* myf = new TFile("../build/CloudChamber.root","r");
  TDirectoryFile* dir = (TDirectoryFile*)myf->Get("ntuple");

  TH2D* edep = new TH2D("EvsY","Edep vs Y coord",40,-200.,200.,40,0.,0.02); //E in MeV, Y in mm
 
  int nEvt = 100;
  TTree* tree;
  double x, y, z, E, S;
  
  for(int j=0; j<nEvt; j++) {
  
    string s = "Ntuple"+to_string(j);
    
    tree = (TTree*)dir->Get(s.c_str());
    
    //now reading each leaf
    tree->SetBranchAddress("Xpos",&x);
    tree->SetBranchAddress("Ypos",&y);
    tree->SetBranchAddress("Zpos",&z);
    tree->SetBranchAddress("Estep",&E);
    tree->SetBranchAddress("StepSize",&S);
    
    int nentries = tree->GetEntries();
    double E_new = 0.;
    
    for (int i=0; i<nentries; i++) {
		
      tree->GetEntry(i);
      double y0 = -200.; //mm
      E_new = E*TMath::Exp(-(y-y0)/TMath::Abs(y0));
      
      double r = fRand(exp(-2.),1.);
      double myrandom = mydist(y,y0);
      
      if(r<myrandom) { edep->Fill(y,E_new); }
     
    }

  }
  
  TApplication *myapp=new TApplication("myapp",0,0);
   
  TCanvas *c1 = new TCanvas("c1","edep",700,700);
  edep->Draw("lego");
//  cc->SaveAs("prova.png");
  
//###############################

  double Eprim;
  TTree* pe = (TTree*)dir->Get("PrimaryE");
  pe->SetBranchAddress("PrimE",&Eprim);
  int n1 = pe->GetEntries();
  
  double Egas;
  TTree* egas = (TTree*)dir->Get("NtupleE");
  egas->SetBranchAddress("Egas",&Egas);
  int n2 = egas->GetEntries();
  
  TGraph* gr = new TGraph();
  
  for(int i=0; i<n1; i++) {
    
    pe->GetEntry(i);
    egas->GetEntry(i);
    gr->SetPoint(i, Eprim, Egas/Eprim);
  }
  
  TCanvas* c2 = new TCanvas("c2","eff",700,700);
  gr->SetMarkerStyle(21);
  gr->Draw("ap");

  myapp->Run();
  myf->Close();
  
  
//###############################

  delete myf;
//  delete edep;
  delete myapp;
  delete c1;
  delete c2;

  return 0;
}


//function mydist
double mydist(double x, double x0) {

  double abs_x0 = abs(x0);
  
  return exp(-(x-x0)/abs_x0);

}

//generate random numbers between two doubles
double fRand(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}
