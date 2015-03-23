#pragma once

class Porte : public Objet{
private:
	bool sortable;
	bool verrouillee;
public:
	Porte(){}
	
	Porte(Modele3D modele, unsigned int ID, char* materiaux, double masse, bool sortie, bool verrou) : Objet(modele, ID, materiaux, masse){
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