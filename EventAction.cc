//   EVENT ACTION SOURCE

#include "EventAction.hh" 
#include "G4Threading.hh"
#include <sstream>
#include <iostream>
using namespace std;


EventAction::EventAction(RunAction*) : photonHits_event_A(10, 0), photonHits_event_B(10, 0) // photonHits_event_A_s(20, 0), photonHits_event_B_s(20, 0) 
{
fEdepA.resize(10, 0.0); 
fEdepB.resize(10, 0.0); 



fGenerated_photons_A.resize(10, 0.0);
fGenerated_photons_B.resize(10, 0.0);



 muonCount = 0;


    traversed_Bars_A.clear();
    traversed_Bars_B.clear();


    Hit_particle_passed_two_layers = false;
    Sumcopies = 0;

    TOTAL_Edep = 0.0;

    TOTAL_Generated_photons = 0.0;
    total_edep_A = 0.0;
    total_edep_B = 0.0;




    particles_names_A.clear();
    particles_names_B.clear();


    pos_layer_A_x.clear();
    pos_layer_A_y.clear();
    pos_layer_A_z.clear();

    pos_layer_B_x.clear();
    pos_layer_B_y.clear();
    pos_layer_B_z.clear();


    particle_tracks_A.clear();  
    particle_tracks_B.clear();
     pos_trackID_A.clear();
     pos_trackID_B.clear();  

    particle_name_tracks_A.clear();  
    particle_name_tracks_B.clear();  
  
    G4int threadID = G4Threading::G4GetThreadId();

    std::stringstream filename;
    filename << "Test_thread_" << threadID << ".dat";

    outFile.open(filename.str());
    
    //outFile.open("Test.dat");  

    /*outFile << "Positions_A(x,y,z,trackID)\tPositions_B(x,y,z,trackID)\t";
    outFile << "Particles_A\tParticles_B\n";*/

    outFile << "EventID\tID_A\tID_B\tHIT\tPart_A\tPart_B\tE_A_MeV\tE_B_MeV\t";
    outFile << "Pos_A(x,y,z)_cm\tPos_B(x,y,z)_cm\n";



}


EventAction::~EventAction()
{ outFile.close();}



void EventAction::BeginOfEventAction(const G4Event*) 
{
    photonHits_event_A.assign(10, 0);
    photonHits_event_B.assign(10, 0);


    
    fEdepA.assign(10, 0.0); 
    fEdepB.assign(10, 0.0);




    fGenerated_photons_A.assign(10, 0.0);
    fGenerated_photons_B.assign(10, 0.0);





 muonCount++;
 G4cout << "ID EVENT: "  << muonCount <<  G4endl;
 G4cout << "" << G4endl;

    
    traversed_Bars_A.clear();
    traversed_Bars_B.clear();

    



    Sumcopies = 0;  
    Hit_particle_passed_two_layers = false;
    

    TOTAL_Edep = 0.0;
   
    TOTAL_Detected_photons = 0.0;
    TOTAL_Generated_photons = 0.0;
    total_edep_A = 0.0;
    total_edep_B = 0.0;






    particles_names_A.clear();
    particles_names_B.clear();


       

    particle_name_tracks_A.clear(); 
    particle_name_tracks_B.clear();   



    particle_tracks_A.clear();  
    particle_tracks_B.clear();
    pos_trackID_A.clear();
    pos_trackID_B.clear(); 
     
    pos_layer_A_x.clear();
    pos_layer_A_y.clear();
    pos_layer_A_z.clear();


    pos_layer_B_x.clear();
    pos_layer_B_y.clear();
    pos_layer_B_z.clear();
 




    //fEdep_abs = 0;


}



void EventAction::EndOfEventAction(const G4Event*event)
{

G4AnalysisManager *man = G4AnalysisManager::Instance();  


//------------------------------- EDEP -----------------------------------------------------------
G4cout << "===============================================================\n" << G4endl;

G4cout << "ENERGY DEPOSITION ON BARS (MeV):   \n" << G4endl;
for (size_t i = 0; i < fEdepA.size(); i++){
    if(fEdepA[i]>0){
    G4cout << "BAR A | " << "ID: "<< i << " |  Edep:  " << fEdepA[i] << "  MeV" << G4endl;
      } 
     man->FillNtupleDColumn(0, i, fEdepA[i]);  
}

for (size_t j = 0; j < fEdepB.size(); j++){
    if(fEdepB[j]>0){
       G4cout << "BAR B | "<<"ID: "<< j + 10  << " |  Edep:  " << fEdepB[j] << "  MeV" << G4endl; 
    }
    man->FillNtupleDColumn(0, j + fEdepA.size(), fEdepB[j] );
    
}


G4cout << "" << G4endl;
if (fEdepA.size() != fEdepB.size() ) {
    G4cerr << "Error: los tamaños de las listas no coinciden (EDEP)." << G4endl;
    return;
}

for (size_t i = 0; i < fEdepA.size(); ++i) {
       TOTAL_Edep += fEdepA[i] + fEdepB[i];

    }

    G4cout << "TOTAL EDEP:  " << TOTAL_Edep << "MeV"<<G4endl;

    man->FillNtupleDColumn(0, 44, TOTAL_Edep);



//------------------ PER LAYER ------------------
for(size_t i = 0; i < fEdepA.size(); ++i){
    if(fEdepA[i] > 0){
        man->FillNtupleDColumn(0, 47,fEdepA[i]);
    }
}

for(size_t i = 0; i < fEdepB.size(); ++i){
    if(fEdepB[i] > 0){
        man->FillNtupleDColumn(0, 48,fEdepB[i]);
    }
}




//----------------------------------------------------------




G4cout << "\n------------------------------------------------------------" << G4endl;
//----------------------------------------GENERATED PHOTONS-------------------------------------------------
G4cout << "" << G4endl;


G4cout << "GENERATED PHOTONS:   " << G4endl;
for (size_t u = 0; u < fGenerated_photons_A.size(); ++u){
    if(fGenerated_photons_A[u]>0.0000001){
         G4cout << "BAR A | " <<"ID: "<<  u  << " |  Generated photons:  " << fGenerated_photons_A[u] << "  photons" << G4endl;   
       }
    man->FillNtupleDColumn(0, u  + fEdepB.size() + fEdepA.size() ,   fGenerated_photons_A[u] );   
}

for (size_t v = 0; v < fGenerated_photons_B.size(); v++){
    if(fGenerated_photons_B[v]>0.0000001){
         G4cout << "BAR B | " <<"ID: "<<  v + 10  << " |  Generated photons:  " << fGenerated_photons_B[v] << "  photons" << G4endl; 
        }
    man->FillNtupleDColumn(0, v + fGenerated_photons_A.size() + fEdepB.size() + fEdepA.size() ,   fGenerated_photons_B[v] ); 
}


G4cout << "\n" << G4endl;

if (fGenerated_photons_A.size() != fGenerated_photons_B.size() ) {
    G4cerr << "Error: los tamaños de las listas no coinciden (Generated Photons)." << G4endl;
    return;
}


G4int photons_gen_A = 0.0;
G4int photons_gen_B = 0.0;



for (size_t i = 0; i < fGenerated_photons_A.size(); ++i) {
    photons_gen_A += fGenerated_photons_A[i];
}
for (size_t i = 0; i < fGenerated_photons_B.size(); ++i) {
    photons_gen_B += fGenerated_photons_B[i];
}
        TOTAL_Generated_photons += photons_gen_A + photons_gen_B;
    
    

    G4cout << "TOTAL GENERATED PHOTONS:  " << TOTAL_Generated_photons <<" photons "<< G4endl;

      man->FillNtupleDColumn(0, 56, TOTAL_Generated_photons);




//------------------ PER LAYER ----------------------
for(size_t i = 0; i < fGenerated_photons_A.size(); ++i){
    if(fGenerated_photons_A[i] > 0.0000001){
        man->FillNtupleDColumn(0,57,fGenerated_photons_A[i]);
    }
}

for(size_t i = 0; i < fGenerated_photons_B.size(); ++i){
    if(fGenerated_photons_B[i] > 0.0000001){
        man->FillNtupleDColumn(0,58,fGenerated_photons_B[i]);
    }
}
G4cout << "\n------------------------------------------------------------" << G4endl;



//G4cout << "\n===============================================================" << G4endl;




//------------------------------------------------------------------------------------------
//              GET THE COPY NUMBER OF THE BARS AND DEFINE THE HIT

G4cout << "" << G4endl;
G4cout << "HIT STATUS: " << G4endl;
G4cout << "" << G4endl;

G4cout << "BAR A | ID: ";
if (traversed_Bars_A.empty()) {
    G4cout << "-1 | NO HIT ";
    man->FillNtupleDColumn(0, 41, -1);
} else {
    for (auto bar : traversed_Bars_A) {
        G4cout << bar << " ";
        man->FillNtupleDColumn(0, 41,bar);
    }
}
 G4cout << G4endl;


    G4cout << "BAR B | ID: ";
    if(traversed_Bars_B.empty()){
        G4cout<< "0 | NO HIT ";
        man->FillNtupleDColumn(0,42,0);
    }else{
    for (auto bar : traversed_Bars_B) {
        G4cout << bar << " ";
        
        man->FillNtupleDColumn(0, 42,bar);
    }
    }
    G4cout << G4endl;


    for(size_t i = 0; i < traversed_Bars_A.size(); ++i){
        if(i < traversed_Bars_B.size()) { 
        if(traversed_Bars_A[i]>=0 && traversed_Bars_A[i]<10 &&
            traversed_Bars_B[i]>=10 && traversed_Bars_B[i]<20){
                Hit_particle_passed_two_layers = true;
             
            }else {
                Hit_particle_passed_two_layers = false;
            }  }
        } 
    


    G4int hit_just_two_layers_crossed = static_cast<G4int>(Hit_particle_passed_two_layers);

    man->FillNtupleIColumn(0, 43, hit_just_two_layers_crossed);

    G4cout << "" << G4endl;
    G4cout << "HIT:  " << Hit_particle_passed_two_layers << "  (1 | yes)  (0 | no)" << G4endl;
    G4cout << "\n" << G4endl;

 


G4cout << "--------------------------------------------------------------------------------" << G4endl;



 //------------------------------------ PARTICLE NAMES-------------------------------------------------------

G4cout <<"==============================================================="<< G4endl;
G4cout <<"PARTICLES NAMES \n" <<G4endl;

G4cout << "Prymary \n"<<G4endl;

G4cout << "PARTICLES ON LAYER A: " <<  G4endl;

if (particles_names_A.empty()) {
    G4cout << "**No particles pierced Layer A in this event. \n" << G4endl;
} else {
    for (auto p_name : particles_names_A) {
        G4cout << p_name << ", \n";
        man->FillNtupleSColumn(0, 45, p_name);
    }}


G4cout << "PARTICLES ON LAYER B: " <<  G4endl;

if (particles_names_B.empty()) {
   G4cout << "**No particles pierced Layer B in this event. \n" << G4endl;
} else {
    for (auto p_name : particles_names_B) {
        G4cout << p_name << ", \n";
        man->FillNtupleSColumn(0, 46, p_name);
    }}



//========================= POSITIONS ============================
G4cout << "------------------------ POSITIONS ------------------------------------" << G4endl;

G4cout << "------------------------ MUONS/PIONS ------------------------------------" << G4endl;
G4cout << G4endl;

G4cout <<"LAYER A | POSITION X : " << G4endl;
for(const auto& pos_x_A :pos_layer_A_x){
        G4cout << pos_x_A << " cm, ";
        man->FillNtupleDColumn(0, 50, pos_x_A);

}
G4cout << "" << G4endl;
G4cout <<"LAYER A | POSITION Y: " << G4endl;
for(const auto& pos_y_A :pos_layer_A_y){
        G4cout << pos_y_A << " cm, ";
        man->FillNtupleDColumn(0, 51, pos_y_A);
}
G4cout << "" << G4endl;
G4cout <<"LAYER A | POSITION Z: " << G4endl;
for(const auto& pos_z_A :pos_layer_A_z){
        G4cout << pos_z_A << " cm, ";
        man->FillNtupleDColumn(0, 52, pos_z_A);
}
G4cout << "" << G4endl;
G4cout << "" << G4endl;

G4cout <<"LAYER B | POSITION X: "<< G4endl;
for(const auto& pos_x_B :pos_layer_B_x){
        G4cout << pos_x_B << " cm, ";
        man->FillNtupleDColumn(0, 53, pos_x_B);
}
G4cout << "" << G4endl;
G4cout <<"LAYER B | POSITION Y: " << G4endl;
for(const auto& pos_y_B :pos_layer_B_y){
        G4cout << pos_y_B << " cm, ";
        man->FillNtupleDColumn(0, 54, pos_y_B);
}
G4cout << "" << G4endl;
G4cout <<"LAYER B | POSITION Z: " << G4endl;
for(const auto& pos_z_B :pos_layer_B_z){
        G4cout << pos_z_B << " cm, ";
        man->FillNtupleDColumn(0, 55, pos_z_B);
}

G4cout <<"==============================================================="<< G4endl;
G4cout << "\n" << G4endl;

G4cout << "Thread: " << G4Threading::G4GetThreadId()
       << " | Event: " << event->GetEventID() << G4endl;
G4cout <<"==============================================================="<< G4endl;
G4cout << "\n" << G4endl;




// ========== ESCRIBIR EN ARCHIVO .dat ==========

    G4int eventID = event->GetEventID();

    outFile << eventID << "\t";

    //outFile << traversed_Bars_A.size() << "\t";
    

    // IDcapa A

    if(traversed_Bars_A.empty()){   
            outFile << "-1.0";
        }else{
        for(size_t i = 0; i < traversed_Bars_A.size(); i++){
        outFile << traversed_Bars_A[i];
       // if(i < traversed_Bars_A.size() - 1) outFile << ",";
        }
    }
    outFile << "\t";
    

    // ID capa B
    if(traversed_Bars_B.empty()){
            outFile << "0";
        }else{
        for(size_t i = 0; i < traversed_Bars_B.size(); i++){
        outFile << traversed_Bars_B[i];
        }
    }
    outFile << "\t";


    //Hit
    if(Hit_particle_passed_two_layers == 1.0){
        outFile << Hit_particle_passed_two_layers;
    }
    outFile << "\t";



    // Nombre capa A 
    for(size_t i = 0; i < particles_names_A.size(); i++){
        outFile << particles_names_A[i];
        //if(i < particle_name_tracks_A.size() - 1) outFile << ",";
    }
    outFile << "\t";
    
    // Nombre capa B
    for(size_t i = 0; i < particles_names_B.size(); i++){
        outFile << particles_names_B[i];
    }
    outFile << "\t";
    

    //Energias
    for(size_t i = 0; i < fEdepA.size(); i++){
        if(fEdepA[i]>0){
            outFile << fEdepA[i] ;    
    }}
    outFile << "\t";


    for(size_t i = 0; i < fEdepB.size(); i++){
        if(fEdepB[i]>0){
            outFile << fEdepB[i];    
    }}
    outFile << "\t";


    
    //Posiciones en capa A: (x,y,z) 
    for(size_t i = 0; i < pos_layer_A_x.size(); i++){
        outFile << "(" << pos_layer_A_x[i] << "," << pos_layer_A_y[i] << "," 
                   << pos_layer_A_z[i] << ")";
       // if(i < pos_layer_A_x.size() - 1) outFile << ";";  
    }
    outFile << "\t";
    
    // Posiciones en capa B
    for(size_t i = 0; i < pos_layer_B_x.size(); i++){
        outFile << "(" << pos_layer_B_x[i] << "," << pos_layer_B_y[i] << "," 
                   << pos_layer_B_z[i] <<  ")";
    }
    outFile << "\n";


man->AddNtupleRow(0);

}



 

