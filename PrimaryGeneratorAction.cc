//      PRIMARY GENERATOR ACTION SOURCE FILE

#include "PrimaryGeneratorAction.hh"
using namespace std;

PrimaryGeneratorAction::PrimaryGeneratorAction()  
{

 fParticleGun = new G4ParticleGun(1); //argument is particle per event

 G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
 G4ParticleDefinition *particle = particleTable->FindParticle("mu+"); 
 fParticleGun->SetParticleDefinition(particle);

}


PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
 delete fParticleGun;
}


void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
 G4double minMomentum = 6;                                                  
 G4double maxMomentum = 6; 
 G4double randomNumber = G4UniformRand(); //random number between 0 and 1
 G4double momentumParticle = minMomentum + ( maxMomentum - minMomentum )*randomNumber;
 G4double momentum_onMeV = momentumParticle*1000;



//columna 12 (8)
G4double Xpos = 18.957*cm;
G4double Zpos = -18.857*cm;
//G4double Zpos = -2.651*cm;
//G4double Zpos = 8.153*cm;
//G4double Zpos = 18.957*cm;


//columna 14 (6)
//G4double Xpos = 8.153*cm;
//G4double Zpos = -18.857*cm;
//G4double Zpos = -2.651*cm;
//G4double Zpos = 8.153*cm;
//G4double Zpos = 18.957*cm;


//columna  15(5)
//G4double Xpos = 2.751*cm;
//G4double Zpos = -18.857*cm;
//G4double Zpos = -2.651*cm;
//G4double Zpos = 8.153*cm;
//G4double Zpos = 18.957*cm;


//columna  18(2)
//G4double Xpos = -13.455*cm;
//G4double Zpos = -18.857*cm;
//G4double Zpos = -2.651*cm;
//G4double Zpos = 8.153*cm;
//G4double Zpos = 18.957*cm; 


//columna  20(0)
//G4double Xpos = -24.259*cm;
//G4double Zpos = -2.651*cm;
//G4double Zpos = -18.857*cm;
//G4double Zpos = 8.153*cm;
//G4double Zpos = 18.957*cm;
   

    G4ThreeVector position(Xpos, 3.7156*m, Zpos); 
   

    G4double thetaMin = 0. * deg;
    G4double thetaMax = 0 * deg; //10.125 * deg; to cover a circle inside the area
    G4double phiMin = 0. * deg;
    G4double phiMax = 360. * deg;
    G4double theta = thetaMin + (thetaMax - thetaMin) * G4UniformRand();
    G4double phi = phiMin + (phiMax - phiMin) * G4UniformRand();
    G4double xDir = std::sin(theta) * std::cos(phi);
    G4double yDir = -1* std::cos(theta);
    G4double zDir = std::sin(theta) * std::sin(phi);

    G4double angle = theta*(180.0/(CLHEP::pi));

    G4double angle_phi = phi*(180.0/(CLHEP::pi));
    //G4double angle = (std::acos(-1.0*yDir))*(180.0/2.0*CLHEP::pi);
   G4double px = momentumParticle*xDir;
   G4double py = momentumParticle*yDir;
   G4double pz = momentumParticle*zDir;

   G4double p_t = sqrt((px*px) + (py*py));
   G4double p_t_b = sqrt((px*px) + (pz*pz));

    G4ThreeVector momentumDirection(xDir,yDir,zDir);  
    fParticleGun->SetParticleMomentumDirection(momentumDirection);
     fParticleGun->SetParticleMomentum(momentumParticle*GeV);
     fParticleGun->SetParticlePosition(position);
     fParticleGun->GeneratePrimaryVertex(anEvent);
    

G4cout << "" << G4endl;                                                            
G4cout << "===============================================================" << G4endl;
G4cout << "MOMENTUM FOR THIS EVENT: " << momentumParticle << " GeV/c \n" << G4endl;  
G4cout << "TRANSVERSE MOMENTUM   sqrt(px^2 + py^2) : " << p_t << " GeV/c \n"<<  G4endl;  
//G4cout << "TRANSVERSE MOMENTUM  [2] sqrt(px^2 + pZ^2) : " << p_t_b << " GeV/c \n"<<  G4endl;                                                         
G4cout << "PARTICLE ANGLE : " <<angle << "° \n"<<  G4endl;  // eta ?  
G4cout << "PARTICLE ANGLE phi: " <<angle_phi << "° \n"<<  G4endl;

G4AnalysisManager *man = G4AnalysisManager::Instance(); 
 man->FillNtupleDColumn(1, 160, momentum_onMeV); 
 man->FillNtupleDColumn(1, 161, momentumParticle);
 man->FillNtupleDColumn(1, 162, angle);
 man->FillNtupleDColumn(1, 180, p_t);
 man->FillNtupleDColumn(1, 201, angle_phi);
 

}

