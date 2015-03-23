#pragma once

class Objet {
protected:
	unsigned int ID;
	gfx::Modele3D modele;
	char* materiaux;
	double masse;
	Vecteur3d vitesse;
public:
	Objet(){}
	Objet(gfx::Modele3D modele, unsigned int ID, char* materiaux,double masse,Vecteur3d vitesse){
		this->modele = modele;
		this->ID = ID;
		this->materiaux = materiaux;
		this->masse = masse;;
		this->vitesse.x = vitesse.x;
		this->vitesse.y = vitesse.y;
		this->vitesse.z = vitesse.z;
	}

	virtual Vecteur3d obtPosition(){} = 0;
	void defPosition(double axeX, double axeY, double axeZ){
		modele->defPosition(axeX, axeY, axeZ);
	}
	
	void defID(unsigned int ID){
		this->ID = ID;
	}

	void defMateriaux(char* materiaux){
		this->materiaux = materiaux;
	}

	void defMasse(double masse){
		this->masse = masse;
	}

	void defVitesse(Vecteur3d vitesse){
		this->vitesse.x = vitesse.x;
		this->vitesse.y = vitesse.y;
		this->vitesse.z = vitesse.z;
	}
	
	unsigned int obtID(){
		return this->ID;
	}
	
	gfx::Modele3D& obtModele(){
		return modele;
	}

	char* obtMateriaux(){
		return materiaux;
	}

	double obtMasse(){
		return masse;
	}

	Vecteur3d obtVitesse(){
		return vitesse;
	}
};
