//    PRYMARY GENERATOR ACTION HEADER


#ifndef PRIMARYGENERATORACTION_HH
#define PRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4AnalysisManager.hh" 
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "Randomize.hh"
#include "G4GenericMessenger.hh"
#include "globals.hh"




class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
 public:
  PrimaryGeneratorAction();
  ~PrimaryGeneratorAction();

  virtual void GeneratePrimaries(G4Event*);

  void SetCenterPosition(G4double x, G4double z) {
        posX = x;
        posZ = z;
    }

  void SetSigmas(G4double sigmax, G4double sigmaz) {
        sigma_x = sigmax;
        sigma_z = sigmaz;
    }


 private:
  G4ParticleGun *fParticleGun;
  G4double posX;
  G4double posZ;
  G4double sigma_x;
  G4double sigma_z;
  G4double posY;
};

#endif

