//   EVENT ACTION HEADER

#ifndef EVENT_HH
#define EVENT_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "G4AnalysisManager.hh"
#include "RunAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;

class EventAction : public G4UserEventAction
{
public:

 EventAction(RunAction*);
 ~EventAction();

 
 virtual void BeginOfEventAction(const G4Event*);
 virtual void EndOfEventAction(const G4Event*);


//-------------------- DETECTED PHOTONS --------------------

//--------------------- JUST MUONS/PIONS --------------------------------

/*void Add_DetectedPhotons_event_A_SiPMs (G4int sipmID_a)
{
    if (sipmID_a >= 0 && sipmID_a < 10 )
    {
        photonHits_event_A[sipmID_a]++;
    }
}
std::vector<G4int> GetPhotonHits_A() const{return photonHits_event_A;}


void Add_DetectedPhotons_event_B_SiPMs (G4int sipmID_b)
{
    if (sipmID_b >= 0 && sipmID_b < 10 )
    {
        photonHits_event_B[sipmID_b]++;
    }
}
std::vector<G4int> GetPhotonHits_B() const{return photonHits_event_B;}*/





//-------------------- TOTAL EDEP  --------------------

//---------- JUST MUONS/PIONS ---------------

void AddEdepA(G4int E_A, G4double edep_A)
{ 
    if (E_A >= 0 && E_A < fEdepA.size()) 
    {
        fEdepA[E_A] += edep_A;
    }
}
std::vector<G4double> GetEdepA() const { return fEdepA; }


void AddEdepB(G4int E_B, G4double edep_B)
{ 
    if (E_B >= 0 && E_B < fEdepB.size()) 
    {
        fEdepB[E_B] += edep_B;
    }
}
std::vector<G4double> GetEdepB() const { return fEdepB; }


//-----------------------------------------------------------
//void AddEdepAbs(G4double edep_abs){fEdep_abs += edep_abs;}
//-----------------------------------------------------------




//------------------------- GENERATED PHOTONS --------------------------------

//------------------- JUST MUONS/PIONS -----------------------------------------------------
void AddPhotonG_UsingEdep_A(G4int PhotonGen_a, G4double generated_photons_A) 
 {
    if (PhotonGen_a >= 0 && PhotonGen_a < fGenerated_photons_A.size())
    {
        fGenerated_photons_A[PhotonGen_a] += generated_photons_A;
    }
 }
 std::vector<G4int> GetPhotonCount_Edep_A() const { return fGenerated_photons_A; }


void AddPhotonG_UsingEdep_B(G4int PhotonGen_b, G4double generated_photons_B)
 {
    if (PhotonGen_b >= 0 && PhotonGen_b <fGenerated_photons_B.size())
    {
        fGenerated_photons_B[PhotonGen_b] += generated_photons_B;
    }
 }
 std::vector<G4int> GetPhotonCount_Edep_B() const { return fGenerated_photons_B; }



//-------------------------- BAR ID -----------------------------
//-------------- JUST MUONS/PION --------------------------------------------------------------------------------------------- 
void AddTraversedBar_A (G4int barA){

        if (std::find(traversed_Bars_A.begin(), traversed_Bars_A.end(), barA) == traversed_Bars_A.end()) {  
          traversed_Bars_A.push_back(barA);
        }
}
std::vector<G4int> GetTraversedBars_A() const {return traversed_Bars_A;}


void AddTraversedBar_B (G4int barB){
    
        if (std::find(traversed_Bars_B.begin(), traversed_Bars_B.end(), barB) == traversed_Bars_B.end()) {
           traversed_Bars_B.push_back(barB);
        }
}
std::vector<G4int> GetTraversedBars_B() const {return traversed_Bars_B;}




//---------------------------PARTICLE NAME ----------------------------


void Particle_Name_Pierced_Layer_A(G4String name_a, G4int trackID){
    
if (particle_name_tracks_A.find(trackID) == particle_name_tracks_A.end()) {
    particles_names_A.push_back(name_a);
   particle_name_tracks_A.insert(trackID); 
}
}

vector<G4String> Get_particle_names_A() const {return particles_names_A;}



void Particle_Name_Pierced_Layer_B(G4String name_b, G4int trackID){
   
   if (particle_name_tracks_B.find(trackID) == particle_name_tracks_B.end()) {
    particles_names_B.push_back(name_b);
     particle_name_tracks_B.insert(trackID);
    }
}

vector<G4String> Get_particle_names_B() const {return particles_names_B;}




//---------------------------------PARTICLE POSITION --------------------------------------------------

//-------------------- JUST MUONS/PIONS ---------------------------

//-------------------- LAYER A --------------------------
void Add_Positions_Layer_A(G4double pos_xa, G4double pos_ya, G4double pos_za, G4int trackID_pos){
    if (particle_tracks_A.find(trackID_pos) == particle_tracks_A.end()) {
    pos_layer_A_x.push_back(pos_xa);
    pos_layer_A_y.push_back(pos_ya);
    pos_layer_A_z.push_back(pos_za);
    pos_trackID_A.push_back(trackID_pos);
    particle_tracks_A.insert(trackID_pos);
    }
}
vector<G4double> Get_pos_x_a() const {return pos_layer_A_x;}
vector<G4double> Get_pos_y_a() const {return pos_layer_A_y;}
vector<G4double> Get_pos_z_a() const {return pos_layer_A_z;}
 vector<G4int> Get_trackID_a() const {return pos_trackID_A;} 





//-------------------- LAYER B --------------------------
void Add_Positions_Layer_B(G4double pos_xb, G4double pos_yb, G4double pos_zb, G4int trackID_pos){
    if (particle_tracks_B.find(trackID_pos) == particle_tracks_B.end()){ 
    pos_layer_B_x.push_back(pos_xb);
    pos_layer_B_y.push_back(pos_yb);
    pos_layer_B_z.push_back(pos_zb);
    pos_trackID_B.push_back(trackID_pos);
    particle_tracks_B.insert(trackID_pos);
    }
}
vector<G4double> Get_pos_x_b() const {return pos_layer_B_x;}
vector<G4double> Get_pos_y_b() const {return pos_layer_B_y;}
vector<G4double> Get_pos_z_b() const {return pos_layer_B_z;}
 vector<G4int> Get_trackID_b() const {return pos_trackID_B;} 



//---------------------------------------------------------


private:


std::vector<G4int> photonHits_event_A;
std::vector<G4int> photonHits_event_B;




std::vector<G4double> localTimes;
 

std::vector<G4double> fEdepA;
std::vector<G4double> fEdepB;




std::vector<G4int> fGenerated_photons_A;
std::vector<G4int> fGenerated_photons_B;




std::vector<G4int> traversed_Bars_A; 
std::vector<G4int> traversed_Bars_B; 





vector<G4String> particles_names_A; 
vector<G4String> particles_names_B;
std::set<G4int> particle_tracks_A;  // Para trackear partículas únicas en capa A //<---- NEW
std::set<G4int> particle_tracks_B;  // Para trackear partículas únicas en capa B //<---- NEW
std::set<G4int> particle_name_tracks_A;  //<---- NEW
std::set<G4int> particle_name_tracks_B;  //<---- NEW



G4double TOTAL_Edep;


G4double fEdep_abs;


G4int TOTAL_Detected_photons;
G4double TOTAL_Generated_photons;

G4double total_edep_A;
G4double total_edep_B;



vector<G4int> pos_trackID_A;
vector<G4int> pos_trackID_B;

vector<G4double> pos_layer_A_x;
vector<G4double> pos_layer_A_y;
vector<G4double> pos_layer_A_z;

vector<G4double> pos_layer_B_x;
vector<G4double> pos_layer_B_y;
vector<G4double> pos_layer_B_z;




 G4int muonCount;

 G4bool Hit_particle_passed_two_layers = false;
 

 G4int Sumcopies;


std::ofstream outFile;

};

#endif



