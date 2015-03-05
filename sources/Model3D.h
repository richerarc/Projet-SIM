#pragma once
#include "Model.h"
#include "Texture.h"
#include <vector>

class Model3D{
private:
	Model model;
	Texture texture;
	Vecteur3f echelle;
	float boiteDeCollision[8];
	void calculerBoiteDeCollision(){};

public:

	Model3D(){}

	Model3D(Model &model, Texture &texture){
		this->model = model;
		this->texture = texture;
	}

	~Model3D(){}

	void defModel(Model &model){
		this->model = modeltmp;
	}

	void defTexture(Texture &texture){
		this->texture = Texture;
	}

	void defEchelle(Vecteur3f &echelle){
		this->echelle = echelle;
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