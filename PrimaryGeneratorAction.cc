//      PRIMARY GENERATOR ACTION SOURCE FILE

#include "PrimaryGeneratorAction.hh"
using namespace std;

PrimaryGeneratorAction::PrimaryGeneratorAction()  
{

 fParticleGun = new G4ParticleGun(1); //argument is particle per event

 G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
 G4ParticleDefinition *particle = particleTable->FindParticle("mu+"); 
 fParticleGun->SetParticleDefinition(particle);


//columna 12 (8)
posX = 0*cm;
posZ = 0*cm;

sigma_x = 0.00701693;
sigma_z = 0.0071868;

posY = 3.7156*m;

}


PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
 delete fParticleGun;
}


void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{

G4double momentumParticle = 2.0;


G4double theta_x = G4RandGauss::shoot(0., sigma_x);
G4double theta_z = G4RandGauss::shoot(0., sigma_z);


G4ThreeVector position(posX, posY,posZ); 
   

/*G4double xDir = std::sin(theta) * std::cos(phi);
 G4double yDir = -1.0* std::cos(theta);
G4double zDir = std::sin(theta) * std::sin(phi);*/


    G4double xDir = theta_x;
    G4double zDir = theta_z;
    G4double yDir = -1.0;
    //G4double yDir = std::sqrt(1.0 - xDir*xDir - zDir*zDir);
    

   G4double px = momentumParticle*xDir;
   G4double py = momentumParticle*yDir;
   G4double pz = momentumParticle*zDir;

   G4double p_t = sqrt((px*px) + (py*py));
   G4double p_t_b = sqrt((px*px) + (pz*pz));

    G4ThreeVector momentumDirection(xDir, yDir,zDir);  
    momentumDirection = momentumDirection.unit();


    fParticleGun->SetParticleMomentumDirection(momentumDirection);
     fParticleGun->SetParticleMomentum(momentumParticle*GeV);
     fParticleGun->SetParticlePosition(position);
     fParticleGun->GeneratePrimaryVertex(anEvent);
    

G4cout << "" << G4endl;                                                            
G4cout << "===============================================================" << G4endl;
G4cout << "MOMENTUM FOR THIS EVENT: " << momentumParticle << " GeV/c \n" << G4endl;  
G4cout << "TRANSVERSE MOMENTUM   sqrt(px^2 + py^2) : " << p_t << " GeV/c \n"<<  G4endl;  


G4AnalysisManager *man = G4AnalysisManager::Instance(); 
 
 man->FillNtupleDColumn(0, 40, momentumParticle);
 man->FillNtupleDColumn(0, 49, p_t);

}



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


//G4double angle = theta*(180.0/(CLHEP::pi));

//G4double angle_phi = phi*(180.0/(CLHEP::pi));