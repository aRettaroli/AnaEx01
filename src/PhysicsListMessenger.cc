#include "PhysicsListMessenger.hh"

//#include "PhysicsList.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysicsListMessenger::PhysicsListMessenger()
  :G4UImessenger(),fMaxChargedStep(DBL_MAX)
{
  fPhysDir = new G4UIdirectory("/chamb/phys/");
  fPhysDir->SetGuidance("physics list commands");

//  fListCmd = new G4UIcmdWithAString("/testem/phys/addPhysics",this);  
//  fListCmd->SetGuidance("Add modula physics list.");
//  fListCmd->SetParameterName("PList",false);
//  fListCmd->AvailableForStates(G4State_PreInit);
//  fListCmd->SetToBeBroadcasted(false);      

  fStepMaxCmd = new G4UIcmdWithADoubleAndUnit("/chamb/stepMax",this);
  fStepMaxCmd->SetGuidance("Set max allowed step length");
  fStepMaxCmd->SetParameterName("mxStep",false);
  fStepMaxCmd->SetRange("mxStep>0.");
  fStepMaxCmd->SetUnitCategory("Length");
  fStepMaxCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysicsListMessenger::~PhysicsListMessenger()
{
//  delete fListCmd;
  delete fPhysDir;
  delete fStepMaxCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsListMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{ 
//  if( command == fListCmd )
//    { fPhysicsList->AddPhysicsList(newValue); }
  if (command == fStepMaxCmd)
    { fMaxChargedStep = fStepMaxCmd->GetNewDoubleValue(newValue); }
}

