#ifndef PhysicsListMessenger_h
#define PhysicsListMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class PhysicsList;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class PhysicsListMessenger: public G4UImessenger
{
public:
  
  PhysicsListMessenger(PhysicsList* );
 ~PhysicsListMessenger();
    
  virtual void SetNewValue(G4UIcommand*, G4String);

//  inline G4double GetMaxChargedStep() const { return fMaxChargedStep; }
    
private:
  
  PhysicsList*               fPhysicsList;
    
  G4UIdirectory*             fPhysDir;    
  G4UIcmdWithAString*        fListCmd;
  G4UIcmdWithADoubleAndUnit* fRCmd;    
//  G4UIcmdWithADoubleAndUnit* fStepMaxCmd;
//  G4double                   fMaxChargedStep;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
