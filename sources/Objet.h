#pragma once

class Objet {
protected:
	unsigned int ID;
	gfx::Modele3D modele;
	char* materiaux;
	double masse;
	Vecteur3f vitesse;
	Vecteur3f position;
public:
	Objet(){}
	Objet(gfx::Modele3D modele, unsigned int ID, char* materiaux,double masse,Vecteur3f vitesse, Vecteur3f position){
		this->modele = modele;
		this->ID = ID;
		this->materiaux = materiaux;
		this->masse = masse;;
		this->vitesse.x = vitesse.x;
		this->vitesse.y = vitesse.y;
		this->vitesse.z = vitesse.z;
		this->position = position;
	}
	virtual Vecteur3f obtPosition(){ return position; };
	virtual void defPosition(double axeX, double axeY, double axeZ){
		position.x = axeX;
		position.y = axeY;
		position.z = axeZ;
	}
	virtual Vecteur3f obtDimensions(){ return 0; };
	virtual void defDimensions(Vecteur3f dimensions){};
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
	
	gfx::Modele3D obtModele(){
		return modele;
	}

	char* obtMateriaux(){
		return materiaux;
	}

	double obtMasse(){
		return masse;
	}

	Vecteur3f obtVitesse(){
		return vitesse;
	}
	
};
