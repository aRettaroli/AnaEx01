#ifndef StepMax_h
#define StepMax_h 1

#include "globals.hh"
#include "G4VEmProcess.hh"
#include "G4ParticleDefinition.hh"
#include "G4Step.hh"

class PhysicsListMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class StepMax : public G4VEmProcess
{
public:

  StepMax(PhysicsListMessenger* mess);
  virtual ~StepMax();

  virtual G4bool IsApplicable(const G4ParticleDefinition&);

  virtual void PreparePhysicsTable(const G4ParticleDefinition&);

  virtual void BuildPhysicsTable(const G4ParticleDefinition&);

  virtual void InitialiseProcess(const G4ParticleDefinition*);

  virtual G4double PostStepGetPhysicalInteractionLength(const G4Track& track,
                                                        G4double previousStep,
                                                        G4ForceCondition* cond);

  virtual G4VParticleChange* PostStepDoIt(const G4Track&, const G4Step&);

private:

  PhysicsListMessenger* fMessenger;

  G4double fMaxChargedStep;
  G4bool isInitialised;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

