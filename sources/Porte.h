#pragma once

class Porte : public Objet{
private:
	bool sortable;
	bool verrouillee;
public:
	Porte(){}
	
	Porte(gfx::Modele3D modele, unsigned int ID, char* materiaux, double masse, Vecteur3d position, bool sortie, bool verrou) : Objet(modele, ID, materiaux, masse,Vecteur3d(0.,0.,0.),position){
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