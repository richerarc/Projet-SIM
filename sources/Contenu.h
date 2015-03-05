#pragma once

class Contenu {
protected:
	Model3D modele;
	Vecteur3d position;
public:
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
};
class Obstacle : public Contenu{
};
class Piege : public Contenu{
};
class Choix : public Contenu{
};
class Puzzle : public Contenu{
};
