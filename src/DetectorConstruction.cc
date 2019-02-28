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
/// \file DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class
//
//
// $Id: DetectorConstruction.cc 101905 2016-12-07 11:34:39Z gunter $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
:G4VUserDetectorConstruction(),
 fGasMaterial(0),fDefaultMaterial(0),
 fSolidWorld(0),fLogicWorld(0),fPhysiWorld(0),
 fSolidChamber (0),fLogicChamber (0),fPhysiChamber (0),
 fDetectorMessenger(0)
//previous implementation:
//fAbsorberMaterial(0),fGapMaterial(0),fDefaultMaterial(0),
//fSolidWorld(0),fLogicWorld(0),fPhysiWorld(0),
//fSolidCalor(0),fLogicCalor(0),fPhysiCalor(0),
//fSolidLayer(0),fLogicLayer(0),fPhysiLayer(0),
//fSolidAbsorber(0),fLogicAbsorber(0),fPhysiAbsorber(0),
//fSolidGap (0),fLogicGap (0),fPhysiGap (0),
//fDetectorMessenger(0)
{
  // default parameter values of the chamber
//  fAbsorberThickness = 10.*mm;
//  fGapThickness      =  5.*mm;
//  fNbOfLayers        = 10;
//  fCalorSizeYZ       = 10.*cm;
  fChamberSizeYZ       = 40.*cm;
  fChamberThickness    = 80.*cm;
  ComputeChamberParameters();
  
  // materials
  DefineMaterials();
//  SetAbsorberMaterial("G4_Pb");
//  SetGapMaterial("G4_lAr");
//  SetGasMaterial("G4_WATER_VAPOR");
  SetGasMaterial("WATER_VAPOR_SAT"); //my supersaturated vapor
	
  // create commands for interactive definition of the chamber
  fDetectorMessenger = new DetectorMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{ delete fDetectorMessenger;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  return ConstructChamber();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineMaterials()
{ 
// use G4-NIST materials data base
//
  G4NistManager* man = G4NistManager::Instance();
  fDefaultMaterial = man->FindOrBuildMaterial("G4_Galactic");
//man->FindOrBuildMaterial("G4_Pb");
//man->FindOrBuildMaterial("G4_lAr");
  man->FindOrBuildMaterial("G4_WATER_VAPOR");
  //definition of supersaturated vapot
  man->ConstructNewGasMaterial("WATER_VAPOR_SAT","G4_WATER_VAPOR",195*kelvin,2*bar,1);
  

// print table
//
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::ConstructChamber()
{

  // Clean old geometry, if any
  //
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();

  // complete the chamber parameters definition
  ComputeChamberParameters();
   
  //     
  // World
  //
  fSolidWorld = new G4Box("World",                                //its name
                   fWorldSizeX/2,fWorldSizeYZ/2,fWorldSizeYZ/2);  //its size
                         
  fLogicWorld = new G4LogicalVolume(fSolidWorld,            //its solid
                                   fDefaultMaterial,        //its material
                                   "World");                //its name
                                   
  fPhysiWorld = new G4PVPlacement(0,                        //no rotation
                                 G4ThreeVector(),           //at (0,0,0)
                                 fLogicWorld,             //its logical volume
                                 "World",                   //its name
                                 0,                         //its mother  volume
                                 false,                  //no boolean operation
                                 0);                        //copy number
  
  //                               
  // Chamber
  //  
  fSolidChamber=0; fLogicChamber=0; fPhysiChamber=0;
	
  if (fChamberThickness > 0.)
    { fSolidChamber = new G4Box("Cloud chamber",                //its name
                    fChamberThickness/2,fChamberSizeYZ/2,fChamberSizeYZ/2);//size
                                 
      fLogicChamber = new G4LogicalVolume(fSolidChamber,        //its solid
                                        fGasMaterial,   //its material
                                        "Cloud chamber");     //its name
                                           
      fPhysiChamber = new G4PVPlacement(0,                    //no rotation
                                     G4ThreeVector(),       //at (0,0,0)
                                     fLogicChamber,           //its logical volume
                                     "Cloud chamber",         //its name
                                     fLogicWorld,           //its mother  volume
                                     false,              //no boolean operation
                                     0);                    //copy number
  
	}
	
  PrintChamberParameters();
  
  //                                        
  // Visualization attributes
  //
  fLogicWorld->SetVisAttributes (G4VisAttributes::GetInvisible());

  G4VisAttributes* simpleBoxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  simpleBoxVisAtt->SetVisibility(true);
  fLogicChamber->SetVisAttributes(simpleBoxVisAtt);

  //
  //always return the physical World
  //
  return fPhysiWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//void DetectorConstruction::PrintCalorParameters()
//{
//  G4cout << "\n------------------------------------------------------------"
//         << "\n---> The calorimeter is " << fNbOfLayers << " layers of: [ "
//         << fAbsorberThickness/mm << "mm of " << fAbsorberMaterial->GetName()
//         << " + "
//         << fGapThickness/mm << "mm of " << fGapMaterial->GetName() << " ] "
//         << "\n------------------------------------------------------------\n";
//}

void DetectorConstruction::PrintChamberParameters()
{
	G4cout << "\n------------------------------------------------------------"
	<< "\n---> The chamber is made of: [ "
	<< fChamberThickness/mm << "mm of " << fGasMaterial->GetName()
	<< " ] "
	<< "\n------------------------------------------------------------\n";
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//void DetectorConstruction::SetAbsorberMaterial(G4String materialChoice)
//{
//  // search the material by its name
//  G4Material* pttoMaterial =
//  G4NistManager::Instance()->FindOrBuildMaterial(materialChoice);
//  if (pttoMaterial)
//  {
//      fAbsorberMaterial = pttoMaterial;
//      if ( fLogicAbsorber )
//      {
//          fLogicAbsorber->SetMaterial(fAbsorberMaterial);
//          G4RunManager::GetRunManager()->PhysicsHasBeenModified();
//      }
//  }
//}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//void DetectorConstruction::SetGapMaterial(G4String materialChoice)
//{
//  // search the material by its name
//  G4Material* pttoMaterial =
//  G4NistManager::Instance()->FindOrBuildMaterial(materialChoice);
//  if (pttoMaterial)
//  {
//      fGapMaterial = pttoMaterial;
//      if ( fLogicGap )
//      {
//          fLogicGap->SetMaterial(fGapMaterial);
//          G4RunManager::GetRunManager()->PhysicsHasBeenModified();
//      }
//  }
//}

void DetectorConstruction::SetGasMaterial(G4String materialChoice)
{

//  G4cout << "\n \nSONO DENTRO A SETGASMATERIAL\n \n";
	// search the material by its name
	G4Material* pttoMaterial =
	G4NistManager::Instance()->FindOrBuildMaterial(materialChoice);
	if (pttoMaterial)
	{
//	G4cout << "\n \nSONO DENTRO A IF pttomaterial\n \n";
		fGasMaterial = pttoMaterial;
		if ( fLogicChamber )
		{
//		G4cout << "\n \nSONO DENTRO A IF flogicalchamber\n \n";
			fLogicChamber->SetMaterial(fGasMaterial);
			G4RunManager::GetRunManager()->PhysicsHasBeenModified();
		}
	}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//void DetectorConstruction::SetAbsorberThickness(G4double val)
//{
//  // change Absorber thickness and recompute the calorimeter parameters
//  fAbsorberThickness = val;
//  G4RunManager::GetRunManager()->ReinitializeGeometry();
//}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//void DetectorConstruction::SetGapThickness(G4double val)
//{
//  // change Gap thickness and recompute the calorimeter parameters
//  fGapThickness = val;
//  G4RunManager::GetRunManager()->ReinitializeGeometry();
//}

void DetectorConstruction::SetChamberThickness(G4double val)
{
	// change chamber thickness and recompute the chamber parameters
	fChamberThickness = val;
	G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetChamberSizeYZ(G4double val)
{
  // change the transverse size and recompute the chamber parameters
  fChamberSizeYZ = val;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//void DetectorConstruction::SetNbOfLayers(G4int val)
//{
//  fNbOfLayers = val;
//  G4RunManager::GetRunManager()->ReinitializeGeometry();
//}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
