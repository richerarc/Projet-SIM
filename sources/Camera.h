#pragma once 
#include "Vecteur3.h"
#include <SDL2/SDL_opengl.h>
#include <GL/GLU.h>
class Camera{
protected:
	Vecteur3f position,
		cible,
		haut,
		cote,
		devant;
	float matriceVue[4][4];

	void coustruireMatrice(){
		matriceVue[0][0] = cote.x;
		matriceVue[1][0] = cote.y;
		matriceVue[2][0] = cote.z;

		matriceVue[0][1] = haut.x;
		matriceVue[1][1] = haut.y;
		matriceVue[2][1] = haut.z;

		matriceVue[0][2] = -devant.x;
		matriceVue[1][2] = -devant.y;
		matriceVue[2][2] = -devant.z;
	}

	void defCible(Vecteur3f& cible){
		this->cible = cible;
		coustruireMatrice();
	}

	void defHaut(Vecteur3f& haut){
		this->haut = haut;
		coustruireMatrice();
	}

	Vecteur3f obtCible(){ return cible; }
	Vecteur3f obtHaut(){ return haut; }

public:

	Camera(Vecteur3f& position, Vecteur3f& cible, Vecteur3f& haut){
		this->position = position;
		this->cible = cible;
		this->haut = haut;
		matriceVue[3][0] = matriceVue[3][1] = matriceVue[3][2] = matriceVue[0][3] = matriceVue[1][3] = matriceVue[2][3] = 0;
		matriceVue[3][3] = 1;
		coustruireMatrice();
	}

	Camera(){
		position = Vecteur3f(0, 0, 0);
		cible = Vecteur3f(0, 0, 0);
		haut = Vecteur3f(0, 0, 0);
		matriceVue[3][0] = matriceVue[3][1] = matriceVue[3][2] = matriceVue[0][3] = matriceVue[1][3] = matriceVue[2][3] = 0;
		matriceVue[3][3] = 1;
		coustruireMatrice();
	}


	void appliquer(){
		gluLookAt(position.x, position.y, position.z, cible.x, cible.y, cible.z, 0, 0, 1);
		/*glMultMatrixf(&matriceVue[0][0]);
		glTranslatef(-position.x, -position.y, -position.z);*/
	}

	Vecteur3f obtPosition(){ return position; }

	void defPosition(Vecteur3f& position){
		this->position = position;
		coustruireMatrice();
	}

};