//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file EventAction.cc
/// \brief Implementation of the EventAction class
//
//
// $Id: EventAction.cc 98241 2016-07-04 16:56:59Z gcosmo $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "EventAction.hh"

#include "RunAction.hh"
#include "HistoManager.hh"

#include "G4Event.hh"

#include <string>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction(RunAction* run, HistoManager* histo)
:G4UserEventAction(),
 fRunAct(run),fHistoManager(histo),
// fEnergyAbs(0.), fEnergyGap(0.),
// fTrackLAbs(0.), fTrackLGap(0.),
 fEnergyGas(0.),
 fTrackLGas(0.),
 fPrimaryEnergy(0.),
 fPrintModulo(0),
 fEvtID(0)                  
{
 fPrintModulo = 100; }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event* evt)
{  
   fEvtID = evt->GetEventID();
 
 // initialisation per event
// fEnergyAbs = fEnergyGap = 0.;
 fEnergyGas = 0.;
// fTrackLAbs = fTrackLGap = 0.;
 fTrackLGas = 0.;

  //record primary energy of the event
  G4PrimaryVertex* primaryVertex = evt->GetPrimaryVertex();
  G4PrimaryParticle* primaryParticle = primaryVertex->GetPrimary();
  fPrimaryEnergy = primaryParticle->GetKineticEnergy();

//create Ntuple for each event (id = evtID + 2 )
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  std::string evtIDstring = std::to_string(fEvtID);
  analysisManager->CreateNtuple("Ntuple"+evtIDstring, "Evt"+evtIDstring);
  analysisManager->CreateNtupleDColumn("Xpos"); // column Id = 0
  analysisManager->CreateNtupleDColumn("Ypos"); // column Id = 1
  analysisManager->CreateNtupleDColumn("Zpos"); // column Id = 2
  analysisManager->CreateNtupleDColumn("Estep"); // column Id = 3
  analysisManager->CreateNtupleDColumn("StepSize"); // column Id = 4
  analysisManager->FinishNtuple();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event*)
{
  //accumulates statistic
  //
//  fRunAct->FillPerEvent(fEnergyAbs, fEnergyGap, fTrackLAbs, fTrackLGap);
  fRunAct->FillPerEvent(fEnergyGas, fTrackLGas);

  
  //fill histograms
  //
//  fHistoManager->FillHisto(0, fEnergyAbs);
//  fHistoManager->FillHisto(1, fEnergyGap);
//  fHistoManager->FillHisto(2, fTrackLAbs);
//  fHistoManager->FillHisto(3, fTrackLGap);
  fHistoManager->FillHisto(0, fEnergyGas);
  fHistoManager->FillHisto(1, fTrackLGas);
  fHistoManager->FillHisto(2, fPrimaryEnergy);
  
  //fill ntuple
  //
//  fHistoManager->FillNtuple(fEnergyAbs, fEnergyGap, fTrackLAbs, fTrackLGap);
  fHistoManager->FillNtuple(fEnergyGas, fTrackLGas, fPrimaryEnergy);


}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
