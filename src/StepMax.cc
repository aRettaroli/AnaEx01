#include "StepMax.hh"
#include "PhysicsListMessenger.hh"
#include "G4VPhysicalVolume.hh"
#include "G4TransportationProcessType.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

StepMax::StepMax(PhysicsListMessenger* mess)
  : G4VEmProcess("UserMaxStep", fGeneral),fMessenger(mess),
    fMaxChargedStep(DBL_MAX),isInitialised(false)
{
  SetProcessSubType(static_cast<G4int>(STEP_LIMITER));  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

StepMax::~StepMax() 
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool StepMax::IsApplicable(const G4ParticleDefinition& part)
{
  return (part.GetPDGCharge() != 0. && !part.IsShortLived());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void StepMax::PreparePhysicsTable(const G4ParticleDefinition&)
{
  if(isInitialised) {
    isInitialised = false;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void StepMax::BuildPhysicsTable(const G4ParticleDefinition&)
{
  if(!isInitialised) {
    fMaxChargedStep = fMessenger->GetMaxChargedStep();
    isInitialised = true;
    if(fMaxChargedStep < DBL_MAX) {
      G4cout << GetProcessName() << ":  SubType= " << GetProcessSubType()
             << "  Step limit(mm)= " << fMaxChargedStep << G4endl;
    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void StepMax::InitialiseProcess(const G4ParticleDefinition*)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double 
StepMax::PostStepGetPhysicalInteractionLength(const G4Track&,
                                              G4double,
                                              G4ForceCondition* condition)
{
  // condition is set to "Not Forced"
  *condition = NotForced;
  return fMaxChargedStep;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VParticleChange* StepMax::PostStepDoIt(const G4Track& aTrack, const G4Step&)
{
  // do nothing
  aParticleChange.Initialize(aTrack);
  return &aParticleChange;
}
