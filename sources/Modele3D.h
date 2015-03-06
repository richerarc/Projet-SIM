#pragma once
#include "Modele.h"
#include "Texture.h"
#include <vector>

class Modele3D{
private:
	Modele modele;
	Texture texture;
	float boiteDeCollision[24];
	void calculerBoiteDeCollision(){
		std::vector<float> tmpX;
		std::vector<float> tmpY;
		std::vector<float> tmpZ;
		float xmax, xmin, ymax, ymin, zmax, zmin;
		for (int i = 0; i < modele.obtNbrFaces(); ++i){
			tmpX.push_back(modele.obtVertices()[i * 3]);
			tmpY.push_back(modele.obtVertices()[i * 3 + 1]);
			tmpZ.push_back(modele.obtVertices()[i * 3 + 2]);
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
				else boiteDeCollision[i] = ymin;
				break;
			case 2:
				if ((i % 6) < 3) boiteDeCollision[i] = zmax;
				else boiteDeCollision[i] = zmin;
				break;
			}
		}
	}

public:

	Modele3D(){}

	Modele3D(Modele &modele, Texture &texture){
		this->modele = modele;
		this->texture = texture;
	}

	~Modele3D(){}

	void defModele(Modele &modele){
		this->modele = modele;
	}

	void defTexture(Texture &texture){
		this->texture = texture;
	}

		void defEchelle(float echX,float echY,float echZ){
		for (int i = 0; i < modele.obtNbrFaces(); i++)
		{
			modele.obtVertices()[i * 3] *= echX;
			modele.obtVertices()[i * 3 + 1] *= echY;
			modele.obtVertices()[i * 3 + 2] *= echZ;
		}
		calculerBoiteDeCollision();
		modele.calculerTaille();
	}

	Modele obtModele(){
		return modele;
	}

	float* obtBoiteDeCollision(){
		return boiteDeCollision;
	}

	Texture obtTexture(){
		return texture;
	}
};