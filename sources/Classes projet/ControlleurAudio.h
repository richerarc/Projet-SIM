#pragma once
#include <map>
#include "Sons.h"
#include "Joueur.h"

enum Sons_t {AH = 1, AVION = 2, BOIRE = 3, BOIS_1 = 4, BOIS_2 = 5, BRUIT = 6, VENT = 7, ELEC_FAIBLE = 8, ELEC_FORT = 9, CRACK_1 = 10, CRACK_2 = 11, DEBARRER = 12, DOUCHE = 13, FERMETURE_PORTE = 14, FOND = 15, GRILLE = 16, HORLOGE = 17, INVENTAIRE = 18, MUNCH_1 = 19, MUNCH_2 = 20, MUNCH_3 = 21, OUVERTURE_PORTE_1 =22, OUVERTURE_PORTE_2 =23, PAPIER_1 =24, PAPIER_2 =25, PAPIER_3 =26, PORTE_BARRE = 27, RECHARGE = 28, RESPIRATION = 29, RONFLEMENT_1 = 30, RONFLEMENT_2 = 31, RONFLEMENT_3 = 32, RONFLEMENT_4 = 33, RONFLEMENT_5 = 34, SNIF = 35, TIR = 36, TIRROIR_1 = 37, TIRROIR_2 = 38, TONNERE = 39, TOUX_1 = 40, TOUX_2 = 41, COEUR = 42, PAS = 43};

class ControlleurAudio : public Singleton<ControlleurAudio>{
private:
	std::map<int, Sons*> sons;
	Coeur *coeur;
	Pas *pas;
	int ittChaine;
	bool initial;
	
	void actualiser(Joueur* joueur){
		for (auto it : sons){
			if ((it.second->actif) && (it.second->obtChaine() != 17)){
				it.second->defIntensite(joueur->obtPositionCamera());
			}
		}
	}
	
public:
	
	ControlleurAudio(){}
	
	~ControlleurAudio(){}
	
	void initialiser(int chaines){
		Mix_AllocateChannels(chaines);
		ittChaine = 0;
		std::ifstream fichierNom("Ressources/Info/sons.txt");
		std::string chemin;
		if (fichierNom.is_open()) {
			while (!fichierNom.eof()) {
				fichierNom >> chemin;
				if (chemin == "Ressources/Son/fond.ogg"){
					Sons* temp = new Fond(chemin.c_str(), ++ittChaine, 20);
					temp->defVolume(20);
					sons[ittChaine] = temp;
				}
				else{
					sons[ittChaine] = new Sons(chemin.c_str(), ++ittChaine, 80);
				}
			}
			fichierNom.close();
		}
		sons[ittChaine] = new Coeur("Ressources/Son/battementLent.ogg", "Ressources/Son/battementMoyen.ogg", "Ressources/Son/battementRapide.ogg", "Ressources/Son/battementAccel.ogg", ++ittChaine, 10);
		sons[ittChaine] = new Pas("Ressources/Son/pas1.ogg", "Ressources/Son/pas2.ogg", ++ittChaine, 12);
		initial = false;
	}
	
	void fermer(){
		for (int i = -1; i < ittChaine; delete sons[++i]);
	}
	
	void jouerTout(Joueur* joueur){
		actualiser(joueur);
		for (auto it : sons){
			if (it.second->actif)
				it.second->jouer(joueur);
		}
		if (!initial){
			defVolumeFond(20);
			defVolumeEffet(60);
			sons[COEUR]->defVolume(25);
			sons[PAS]->defVolume(10);
			initial = true;
		}
	}
	
	void jouer (Sons_t type, Joueur* joueur){
		if (!(type == COEUR || type == PAS || type == FOND)){
			sons[type]->defIntensite(joueur->obtPositionCamera());
			sons[type]->jouer(joueur);
		}
		else{
			sons[type]->jouer(joueur);
		}
	}
	
	void defVolumeFond(int vol){
		Mix_Volume(FOND, vol);
	}
	
	void defVolumeEffet(int vol){
		for (auto it : sons){
			if (it.second->obtChaine() != FOND){
				Mix_Volume(it.second->obtChaine(), vol);
			}
		}
	}
	
	void defVolumePrinc(int vol){
		Mix_Volume(-1, vol);
	}
	
	void defVolumeSon(int vol, int chaine){ // chaine = -1 pour tout
		for (auto it : sons){
			if ((chaine == -1) || it.second->obtChaine() == chaine){
				it.second->defVolume(vol);
			}
		}
	}
	
	void defPosition (int chaine, Vecteur3d pos){
		for (auto it : sons){
			if ((chaine == -1) || it.second->obtChaine() == chaine){
				it.second->defPosition(pos);
			}
		}
	}
	
	void defActivite(int chaine, bool actif){
		for (auto it : sons){
			if ((chaine == -1) || it.second->obtChaine() == chaine){
				it.second->actif = actif;
			}
		}
	}
};