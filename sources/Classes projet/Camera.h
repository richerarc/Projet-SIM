#pragma once 
#include <math.h>
#include "Maths.h"
#include "GestionnaireEvenements.h"
#include "Vecteur3.h"

namespace gfx{
	class Camera{
	protected:
		Vecteur3d position,
			cible,
			haut,
			cote,
			devant;
		float matriceVue[4][4];

		void construireMatrice(){
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

		void defCible(Vecteur3d& cible){
			this->cible = cible;
			construireMatrice();
		}

		void defHaut(Vecteur3d& haut){
			this->haut = haut;
			construireMatrice();
		}

		Vecteur3d obtCible(){ return cible; }
		Vecteur3d obtHaut(){ return haut; }

	public:

		Camera(Vecteur3d& position, Vecteur3d& cible, Vecteur3d& haut){
			this->position = position;
			this->cible = cible;
			this->haut = haut;
			matriceVue[3][0] = matriceVue[3][1] = matriceVue[3][2] = matriceVue[0][3] = matriceVue[1][3] = matriceVue[2][3] = 0;
			matriceVue[3][3] = 1;
			construireMatrice();
		}

		Camera(){
			position = Vecteur3d(0, 0, 0);
			cible = Vecteur3d(0, 0, 0);
			haut = Vecteur3d(0, 0, 0);
			matriceVue[3][0] = matriceVue[3][1] = matriceVue[3][2] = matriceVue[0][3] = matriceVue[1][3] = matriceVue[2][3] = 0;
			matriceVue[3][3] = 1;
			construireMatrice();
		}


		void appliquer(){
			glMultMatrixf(&matriceVue[0][0]);
			glTranslatef(-position.x, -position.y, -position.z);
		}

		Vecteur3d obtPosition(){ return position; }

		void defPosition(Vecteur3d& position){
			this->position = position;
			construireMatrice();
		}

	};
}