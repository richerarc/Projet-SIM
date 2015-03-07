#pragma once
#include "Contenu.h"

class Porte : public Contenu{
private:
	bool sortable;
	bool verrouillee;
public:
	Porte(){}
	
	Porte(Vecteur3d positionDepart, Modele3D modele, unsigned int identifiant, bool sortie, bool verrou) : Contenu(positionDepart, modele, ID){
		sortable = sortie;
		verrouillee = verrou;
	}

	bool obtSortable(){
		return sortable;
	}
	void defSortable(bool sortie){
		sortable = sortie;
	}
	bool obtVerrou(){
		return verrouillee;
	}
	void defVerrou(bool verrou){
		verrouillee = verrou;
	}
};