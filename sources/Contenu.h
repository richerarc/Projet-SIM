#pragma once

class Contenu {
protected:
	unsigned int ID;
	Modele3D modele;
public:
	Contenu(){}
	Contenu(Modele3D modele, unsigned int ID){
		this->modele = modele;
		this->ID = ID;
	}
	Vecteur3d obtPos(){
		return modele->obtPosition();
	}
	void defPosition(int axeX, int axeY, int axeZ){
		modele->defPosition(axeX, axeY, axeZ);
	}
	
	void defID(unsigned int ID){
		this->ID = ID;
	}
	
	unsigned int obtID(){
		return this->ID;
	}
	
	Modele3D obtModele(){
		return modele;
	}
};

class Objet : public Contenu{
public:
	Objet(){}
	Objet(Modele3D modele, unsigned int ID) : Contenu(modele, ID){}
};
class Obstacle : public Contenu{
public:
	Obstacle(){}
	Obstacle(Modele3D modele, unsigned int ID) : Contenu(modele, ID){}
};
class Piege : public Obstacle{
public:
	Piege(){}
	Piege(Modele3D modele, unsigned int ID) : Obstacle(modele, ID){}
};
class Choix : public Obstacle{
public:
	Choix(){}
	Choix(Modele3D modele, unsigned int ID) : Obstacle(modele, ID){}
};
class Puzzle : public Obstacle{
public:
	Puzzle(){}
	Puzzle(Modele3D modele, unsigned int ID) : Obstacle(modele, ID){}
};