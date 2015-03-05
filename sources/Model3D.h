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
	void calculerBoiteDeCollision(){
		std::vector<float> tmpX;
		std::vector<float> tmpY;
		std::vector<float> tmpZ;
		float xmax, xmin, ymax, ymin, zmax, zmin;
		for (int i = 0; i < nbrFaces; ++i){
			tmpX.push_back(modele->obtVertices()[i * 3]);
			tmpY.push_back(modele->obtVertices()[i * 3 + 1]);
			tmpZ.push_back(modele->obtVertices()[i * 3 + 2]);
		}
		xmax = Maths::obtValeurMax(tmpX);
		xmin = Maths::obtValeurMin(tmpX);
		ymax = Maths::obtValeurMax(tmpY);
		ymin = Maths::obtValeurMin(tmpY);
		zmax = Maths::obtValeurMax(tmpZ);
		zmin = Maths::obtValeurMin(tmpZ);

		for (int i = 0, i < 24, i++){
			switch (i % 3){
			case 0:
				if (i < 12) boiteDeCollision[i] = xmax;
				else boiteDeCollision[i] = xmin;
				break;
			case 1:
				if ((i % 12) < 6) boiteDeCollision[i] = ymax;
				else boitDeCollision[i] = ymin;
				break;
			case 2:
				if ((i % 6) < 3) boiteDeCollision[i] = zmax;
				else boitDeCollision[i] = zmin;
				break;
			}
		}
	}

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