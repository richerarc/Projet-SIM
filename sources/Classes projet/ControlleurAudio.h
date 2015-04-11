#pragma once
#include "Lecteur.h"


class ControlleurAudio : public Singleton<ControlleurAudio>{
private:
	
	int ittChaine;
public:
	
	ControlleurAudio(){}
	
	~ControlleurAudio(){}
	
	void allouerChaines(int chaines){
		lecteur.allouerChaines(chaines);
	}
	
	void initialiser(){
		ittChaine = 0;
		std::ifstream fichierNom("sons.txt");
		std::string chemin;
		if (fichierNom.is_open()) {
			while (!fichierNom.eof()) {
				fichierNom >> chemin;
				lecteur.creerChaine(++ittChaine, chemin.substr(0, chemin.find(".")));
				lecteur.ajouterSon(chemin, chemin.substr(0, chemin.find(".")));
			}
			fichierNom.close();
		}
	}
	
};