#pragma once

class Contenu {
protected:
	Model3d modele;
	Vecteur3<double> position;
public:
	Vecteur3<double> obtPosition(){
		return position;
	}
	void defPosition(Vecteur3<double> nouvPosition){
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