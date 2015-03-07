#pragma once

class Contenu {
protected:
	unsigned int ID;
	Modele3D modele;
	Vecteur3d position;
public:
	Contenu(){}
	Contenu(Vecteur3d nouvPosition, Modele3D modele, unsigned int ID){
		position.x = nouvPosition.x;
		position.y = nouvPosition.y;
		position.z = nouvPosition.z;
		this->modele = modele;
		this->ID = ID;
	}
	Vecteur3d obtPosition(){
		return position;
	}
	void defPosition(Vecteur3d nouvPosition){
		position.x = nouvPosition.x;
		position.y = nouvPosition.y;
		position.z = nouvPosition.z;
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
	Objet(Vecteur3d nouvPosition, Modele3D modele, unsigned int ID) : Contenu(nouvPosition, modele, ID){}
};
class Obstacle : public Contenu{
public:
	Obstacle(){}
	Obstacle(Vecteur3d nouvPosition, Modele3D modele, unsigned int ID) : Contenu(nouvPosition, modele, ID){}
};
class Piege : public Contenu{
public:
	Piege(){}
	Piege(Vecteur3d nouvPosition, Modele3D modele, unsigned int ID) : Contenu(nouvPosition, modele, ID){}
};
class Choix : public Contenu{
public:
	Choix(){}
	Choix(Vecteur3d nouvPosition, Modele3D modele, unsigned int ID) : Contenu(nouvPosition, modele, ID){}
};
class Puzzle : public Contenu{
public:
	Puzzle(){}
	Puzzle(Vecteur3d nouvPosition, Modele3D modele, unsigned int ID) : Contenu(nouvPosition, modele, ID){}
};