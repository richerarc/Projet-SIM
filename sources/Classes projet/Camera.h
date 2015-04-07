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
		double sensibilite;

		double hAngle;
		double vAngle;
		double matriceVue[4][4];

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


		void calculerVecteurs(){
			if (vAngle > 89)
				vAngle = 89;
			if (vAngle < -89)
				vAngle = -89;

			double vAngleRadian = vAngle * MATHS_PI / 180;
			double hAngleRadian = hAngle * MATHS_PI / 180;
			double cos_vAngle = cos(vAngleRadian);

			devant.x = cos_vAngle * sin(hAngleRadian);
			devant.y = sin(vAngleRadian);
			devant.z = cos_vAngle * cos(hAngleRadian);

			devant.normaliser();

			haut = Vecteur3d(0, 1, 0);

			cote = devant.produitVectoriel(haut);
			cote.normaliser();

			haut = cote.produitVectoriel(devant);
			haut.normaliser();

			construireMatrice();
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

	public:

		Camera(Vecteur3d& position, Vecteur3d& cible, Vecteur3d& haut){
			this->position = position;
			this->cible = cible;
			this->haut = haut;
			matriceVue[3][0] = matriceVue[3][1] = matriceVue[3][2] = matriceVue[0][3] = matriceVue[1][3] = matriceVue[2][3] = 0;
			matriceVue[3][3] = 1;
			construireMatrice();

			this->sensibilite = 0.15;

			this->hAngle = 0;
			this->vAngle = 0;

			calculerVecteurs();

			GestionnaireEvenements::obtInstance().ajouterUnRappel(SDL_MOUSEMOTION, std::bind(&Camera::surMouvementSouris, this, std::placeholders::_1));

			SDL_SetRelativeMouseMode(SDL_TRUE);
			SDL_ShowCursor(SDL_DISABLE);
		}

		Camera() : Camera(Vecteur3d(), Vecteur3d(), Vecteur3d()){}

		~Camera(){
			SDL_SetRelativeMouseMode(SDL_FALSE);
			SDL_ShowCursor(SDL_ENABLE);
		}

		void surMouvementSouris(SDL_Event &event){
			hAngle -= event.motion.xrel * sensibilite;
			vAngle -= event.motion.yrel * sensibilite;
			calculerVecteurs();
		}

		void appliquer(){
			glMultMatrixd(&matriceVue[0][0]);
			glTranslated(-position.x, -position.y, -position.z);
		}

		Vecteur3d obtHaut(){ return this->haut; }

		Vecteur3d obtDevant(){ return this->devant; }

		Vecteur3d obtCote(){ return this->cote; }

		Vecteur3d obtPosition(){ return position; }

		void defPosition(Vecteur3d& position){
			this->position = position;
			construireMatrice();
		}

	};
}