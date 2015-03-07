#pragma once

class Contenu {
protected:
	Model3D modele;
	Vecteur3d position;
public:
	Contenu(){}
	Contenu(Vecteur3d nouvPosition){
		position.x = nouvPosition.x;
		position.y = nouvPosition.y;
		position.z = nouvPosition.z;
	}
	Vecteur3d obtPosition(){
		return position;
	}
	void defPosition(Vecteur3d nouvPosition){
		position.x = nouvPosition.x;
		position.y = nouvPosition.y;
		position.z = nouvPosition.z;
	}
};

class Objet : public Contenu{
public:
	Objet(){}
	Objet(Vecteur3d nouvPosition) : Contenu(nouvPosition){}
};
class Obstacle : public Contenu{
public:
	Obstacle(){}
	Obstacle(Vecteur3d nouvPosition) : Contenu(nouvPosition){}
};
class Piege : public Contenu{
public:
	Piege(){}
	Piege(Vecteur3d nouvPosition) : Contenu(nouvPosition){}
};
class Choix : public Contenu{
public:
	Choix(){}
	Choix(Vecteur3d nouvPosition) : Contenu(nouvPosition){}
};
class Puzzle : public Contenu{
public:
	Puzzle(){}
	Puzzle(Vecteur3d nouvPosition) : Contenu(nouvPosition){}
};