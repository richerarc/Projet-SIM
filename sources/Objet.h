#pragma once

class Objet {
protected:
	unsigned int ID;
	gfx::Modele3D modele;
	char* materiaux;
	double masse;
	Vecteur3d vitesse;
	Vecteur3d position;
public:
	Objet(){}
	Objet(gfx::Modele3D modele, unsigned int ID, char* materiaux,double masse,Vecteur3d vitesse, Vecteur3d position){
		this->modele = modele;
		this->ID = ID;
		this->materiaux = materiaux;
		this->masse = masse;;
		this->vitesse.x = vitesse.x;
		this->vitesse.y = vitesse.y;
		this->vitesse.z = vitesse.z;
		this->position = position;
	}
	virtual Vecteur3d obtPosition(){ return position; };
	virtual void defPosition(Vecteur3d position){
		this->position.x = position.x;
		this->position.y = position.y;
		this->position.z = position.z;
	}
	virtual Vecteur3d obtDimensions(){};
	virtual void defDimensions(Vecteur3d dimensions){};
	virtual void defForce(double force){};
	virtual double obtForce(){ return 0; };
	virtual bool obtSortable(){return false;}
	virtual void defSortable(bool sortie){}
	virtual bool obtVerrou(){return false;}
	virtual void defVerrou(bool verrou){}

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
	
	gfx::Modele3D& obtModele3D(){
		return modele;
	}

	char* obtMateriaux(){
		return materiaux;
	}

	double obtMasse(){
		return masse;
	}

	Vecteur3d& obtVitesse(){
		return vitesse;
	}
	
};
