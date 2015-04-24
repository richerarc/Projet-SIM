#pragma once
#include <map>
#include "Sons.h"
#include "Joueur.h"

enum Sons_t {AH = 1, AVION = 2, BOIRE = 3, BOIS_1 = 4, BOIS_2 = 5, BRUIT = 6, VENT = 6, ELEC_FAIBLE = 7, ELEC_FORT = 8, CRACK_1 = 9, CRACK_2 = 10, DEBARRER = 11, DOUCHE = 12, FERMETURE_PORTE = 13, FOND = 14, GRILLE = 15, HORLOGE = 16, INVENTAIRE = 17, MUNCH_1 = 18, MUNCH_2 = 19, MUNCH_3 = 20, OUVERTURE_PORTE_1 =21, OUVERTURE_PORTE_2 =22, PAPIER_1 =23, PAPIER_2 =24, PAPIER_3 =25, PORTE_BARRE = 26, RECHARGE = 27, RESPIRATION = 28, RONFLEMENT_1 = 29, RONFLEMENT_2 = 30, RONFLEMENT_3 = 31, RONFLEMENT_4 = 32, RONFLEMENT_5 = 33, SNIF = 34, TIR = 35, TIRROIR_1 = 36, TIRROIR_2 = 37, TONNERE = 38, TOUX_1 = 39, TOUX_2 = 40};

class ControlleurAudio : public Singleton<ControlleurAudio>{
private:
	std::map<int, Sons*> sons;
	Coeur *coeur;
	Pas *pas;
	int ittChaine;
	bool initial;
public:
	
	ControlleurAudio(){}
	
	~ControlleurAudio(){}
	
	void initialiser(int chaines){
		Mix_AllocateChannels(chaines);
		ittChaine = 0;
		std::ifstream fichierNom("sons.txt");
		std::string chemin;
		if (fichierNom.is_open()) {
			while (!fichierNom.eof()) {
				fichierNom >> chemin;
				if (chemin == "fond.ogg"){
					Sons* temp = new Fond(chemin.c_str(), ++ittChaine, 20);
					temp->defVolume(20);
					sons[ittChaine] = temp;
				}
				sons[ittChaine] = new Sons(chemin.c_str(), ++ittChaine, 80);
			}
			fichierNom.close();
		}
		coeur = new Coeur("battementLent.ogg", "battementMoyen.ogg", "battementRapide.ogg", "battementAccel.ogg", ++ittChaine, 10);
		pas = new Pas("pas1.ogg", "pas2.ogg", ++ittChaine, 12);
		initial = false;
	}
	
	void fermer(){
		for (int i = 0; i < ittChaine; i++) delete sons[i];
		delete coeur;
		delete pas;
	}
	
	void jouerTout(Joueur* joueur){
		actualiser(joueur);
		for (auto it : sons){
			if (it.second->actif)
				it.second->jouer(joueur);
		}
		coeur->jouer(joueur);
		pas->jouer(joueur);
		if (!initial){
			defVolumeFond(20);
			defVolumeEffet(60);
			coeur->defVolume(25);
			pas->defVolume(10);
			initial = true;
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
	
	void actualiser(Joueur* joueur){
		for (auto it : sons){
			if ((it.second->actif) && (it.second->obtChaine() != 17)){
				it.second->defIntensite(joueur->obtPosition());
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
	
	Coeur* obtCoeur(){
		return coeur;
	}
};