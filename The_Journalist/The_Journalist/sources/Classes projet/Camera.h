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
		double valeurx;
		double valeury;
		double hAngle;
		double vAngle;
		double matriceVue[4][4];

		bool pause;

		bool changement;
		double dernierHAngle;
		double dernierVAngle;

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

			if (hAngle < 0)
				hAngle += 360;
			if (hAngle > 360)
				hAngle -= 360;

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

		Camera(Vecteur3d position, Vecteur3d cible, Vecteur3d haut){
			this->valeurx = 0;
			this->valeury = 0;
			this->position = position;
			this->cible = cible;
			this->haut = haut;
			matriceVue[3][0] = matriceVue[3][1] = matriceVue[3][2] = matriceVue[0][3] = matriceVue[1][3] = matriceVue[2][3] = 0;
			matriceVue[3][3] = 1;
			construireMatrice();

			this->sensibilite = 0.15;

			this->hAngle = 0;
			this->vAngle = 0;
			this->dernierHAngle = hAngle;
			this->dernierVAngle = vAngle;

			this->pause = false;

			calculerVecteurs();

			GestionnaireEvenements::obtInstance().ajouterUnRappel(SDL_MOUSEMOTION, std::bind(&Camera::surMouvementSouris, this, std::placeholders::_1));
			GestionnaireEvenements::obtInstance().ajouterUnRappel(SDL_CONTROLLERAXISMOTION, std::bind(&Camera::surMouvementManette, this, std::placeholders::_1));

			SDL_SetRelativeMouseMode(SDL_TRUE);
			SDL_ShowCursor(SDL_DISABLE);
		}

		Camera() : Camera(Vecteur3d(), Vecteur3d(), Vecteur3d()){}

		~Camera(){
			SDL_SetRelativeMouseMode(SDL_FALSE);
			SDL_ShowCursor(SDL_ENABLE);
		}

		void surMouvementSouris(SDL_Event &event){
			if (!pause) {
				hAngle -= event.motion.xrel * sensibilite;
				vAngle -= event.motion.yrel * sensibilite;
				calculerVecteurs();
			}
		}
		void surMouvementManette(SDL_Event& event){
			if (!pause) {
				if ((event.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTX || event.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTY)){
						Manette::mettreAJourControleDroite(event);
						valeurx = (Manette::obtenirPositionDroiteX());
						valeury = (Manette::obtenirPositionDroiteY());
				}
				else{
					valeurx = 0;
					valeury = 0;
				}
			}
		}
		void rafraichir(){
			hAngle -= valeurx;
			vAngle -= valeury;
			
			changement = dernierHAngle != hAngle || dernierVAngle != vAngle;
			dernierHAngle = hAngle;
			dernierVAngle = vAngle;

			calculerVecteurs();
		}
		void appliquer(){
			glMultMatrixd(&matriceVue[0][0]);
			glTranslated(-position.x, -position.y, -position.z);
		}

		bool obtChangement(){ return this->changement; }

		void bloquer() { pause = true; }

		void deBloquer(){ pause = false; }
		
		bool obtBloquer() { return pause; }

		double obtHAngle(){	return hAngle; }

		double obtVAngle() { return vAngle; }

		void defHAngle(double hAngle){ this->hAngle = hAngle; calculerVecteurs(); }

		void defVAngle(double vAngle) { this->vAngle = vAngle; calculerVecteurs(); }

		void defDevant(Vecteur3d devant){ this->devant = devant; }

		Vecteur3d obtHaut(){ return this->haut; }

		Vecteur3d obtDevant(){ return this->devant; }

		Vecteur3d obtCote(){ return this->cote; }

		Vecteur3d obtPosition(){ return position; }

		void defPosition(Vecteur3d position){
			this->position = position;
			construireMatrice();
		}

	};
}