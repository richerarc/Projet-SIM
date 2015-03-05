#pragma once
#include "Model.h"
#include "Texture.h"

class Model3D{
private:
	Model model;
	Texture texture;
	Vecteur3f echelle;
	float* boiteDeCollision;
	void calculerBoiteDeCollision(){};

public:

	Model3D(){}

	~Model3D(){}

	void defModel(Model &modeltmp){
		model = modeltmp;
	}

	void defTexture(Texture &Texturetmp){
		texture = Texturetmp;
	}

	void defEchelle(Vecteur3f &Echelletmp){
		echelle = Echelletmp;
	}

	Model obtModel(){
		return model;
	}

	Vecteur3f obtEchelle(){
		return echelle;
	}

	float* obtBoiteDeCollision(){
		return boiteDeCollision;
	}

	Texture obtTexture(){
		return texture;
	}
};