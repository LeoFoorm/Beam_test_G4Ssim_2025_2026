//  STEPPING ACTION SOURCE

#include "SteppingAction.hh"
#include <vector>

using namespace std;

SteppingAction::SteppingAction( EventAction *eventaction)
{
 fEventAction = eventaction;

}


SteppingAction::~SteppingAction()
{}


void SteppingAction::UserSteppingAction(const G4Step *step)
{

const DetectorConstruction *detectorconstruction = static_cast < const DetectorConstruction* > (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
 
const std::vector<G4LogicalVolume*>& scoringVolumesA = detectorconstruction->GetScoringVolumesA();
const std::vector<G4LogicalVolume*>& scoringVolumesB = detectorconstruction->GetScoringVolumesB();
G4LogicalVolume* scoringVolume_Absorber = detectorconstruction->GetScoringVolumeAbsorber();
   

G4TouchableHandle touchedbar = step->GetPreStepPoint()->GetTouchableHandle(); 
 G4LogicalVolume* barvolume = touchedbar->GetVolume()->GetLogicalVolume();


 G4double stepLength = step->GetStepLength();
 G4ParticleDefinition* particle = step->GetTrack()->GetDefinition();
 
 
 G4Track* track = step->GetTrack();


G4StepPoint *PreStep = step->GetPreStepPoint();
  
 
//if(particle->GetParticleName()== "mu+" ||  particle->GetParticleName() == "pi+" )
if(particle->GetParticleName() !="opticalphoton" ){

   G4double generated_photons_A;
   G4double generated_photons_B ;






if (std::find(scoringVolumesA.begin(), scoringVolumesA.end(), barvolume) != scoringVolumesA.end())
        {

        // if(particle->GetParticleName()== "mu+" ||  particle->GetParticleName() == "pi+" ){


         G4int copyNumA = touchedbar->GetCopyNumber(); 
         fEventAction->AddTraversedBar_A(copyNumA);
    

       

      

         G4double edep_A = step->GetTotalEnergyDeposit();

          //G4double stepLength_New = step->GetStepLength(); 
         
         if (edep_A > 0.&& stepLength > 0.)
         {


             G4ThreeVector position_A = step->GetPostStepPoint()->GetPosition();
       
        G4double A_pos_x = position_A.x()/(cm);
        G4double A_pos_y = position_A.y()/(cm);
        G4double A_pos_z = position_A.z()/(cm);
        G4int trackID_pos = step->GetTrack()->GetTrackID();       
         
        fEventAction->Add_Positions_Layer_A(A_pos_x, A_pos_y, A_pos_z, trackID_pos);


            G4String p_name = step->GetTrack()->GetDefinition()->GetParticleName();
            G4int trackID = step->GetTrack()->GetTrackID();     
            fEventAction->Particle_Name_Pierced_Layer_A(p_name, trackID);



            G4Material *plastic_scin = step->GetPreStepPoint()->GetMaterial(); 
            G4MaterialPropertiesTable *Yield = plastic_scin->GetMaterialPropertiesTable(); 
            G4double Scintillation_Yield = Yield->GetConstProperty("SCINTILLATIONYIELD");

            generated_photons_A = edep_A * Scintillation_Yield; 
            generated_photons_A = G4Poisson(generated_photons_A); 

          

            size_t a = std::distance(scoringVolumesA.begin(),
                                              std::find(scoringVolumesA.begin(), scoringVolumesA.end(), barvolume));
            
            fEventAction->AddPhotonG_UsingEdep_A(a, generated_photons_A);
            fEventAction->AddEdepA(a, edep_A);
 
           G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();


         } 
         }
      

         if (std::find(scoringVolumesB.begin(), scoringVolumesB.end(), barvolume) != scoringVolumesB.end())
        {

           
            G4int copyNumB = touchedbar->GetCopyNumber(); 
            fEventAction->AddTraversedBar_B(copyNumB);
            
            G4ThreeVector position_B = step->GetPostStepPoint()->GetPosition();
       
            G4double B_pos_x = position_B.x()/(cm);
            G4double B_pos_y = position_B.y()/(cm);
            G4double B_pos_z = position_B.z()/(cm);
            G4int trackID_pos = step->GetTrack()->GetTrackID(); 
        
            fEventAction->Add_Positions_Layer_B(B_pos_x, B_pos_y, B_pos_z, trackID_pos);


            G4double edep_B = step->GetTotalEnergyDeposit();

         if (edep_B > 0.&& stepLength > 0.)
         {

            G4String p_name = step->GetTrack()->GetDefinition()->GetParticleName();
            G4int trackID = step->GetTrack()->GetTrackID();         //<--- NEW
            fEventAction->Particle_Name_Pierced_Layer_B(p_name, trackID);  


            G4Material *plastic_scin = step->GetPreStepPoint()->GetMaterial(); 
            G4MaterialPropertiesTable *Yield = plastic_scin->GetMaterialPropertiesTable(); 
            G4double Scintillation_Yield = Yield->GetConstProperty("SCINTILLATIONYIELD");

            generated_photons_B = edep_B * Scintillation_Yield; 
            generated_photons_B = G4Poisson(generated_photons_B); 
            
            size_t b = std::distance(scoringVolumesB.begin(),
                                              std::find(scoringVolumesB.begin(), scoringVolumesB.end(), barvolume));
            
            fEventAction->AddPhotonG_UsingEdep_B(b, generated_photons_B); 
            fEventAction->AddEdepB(b, edep_B);



            G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();


         }
         }
} 

// ---------------------------------------------------------------------------------



}


