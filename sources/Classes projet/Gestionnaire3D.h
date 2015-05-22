#pragma once
#include <list>
#include "Camera.h"
#include "Modele3D.h"
#include "Singleton.h"
#include "Fenetre.h"
namespace gfx{
	class Gestionnaire3D : public Singleton<Gestionnaire3D>
	{
	private:
		std::list<Objet3D*> objets;
		gfx::Camera* camera;
		double hautY, droitX, ratio, angle, planProche, planLoin;

		void defFrustum(){
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glFrustum(-droitX, droitX, -hautY, hautY, planProche, planLoin);
			glMatrixMode(GL_MODELVIEW);
		}

	public:

		Gestionnaire3D(gfx::Fenetre fenetre ){
			hautY = Maths::degreARadian(70);
			ratio = ((double)fenetre.obtTaille().x / (double)fenetre.obtTaille().y);
			droitX = hautY * (ratio);
			planProche = 1;
			planLoin = 1000;
			defFrustum();
		}

		Gestionnaire3D(){
			hautY = Maths::degreARadian(45);
			ratio = (800.0f / 600.0f);
			droitX = hautY * (ratio);
			planProche = 1;
			planLoin = 1000;
		}

		void defHaut(double haut){
			hautY = haut;
			droitX = hautY * (ratio);
			defFrustum();
		}

		void defAngleDeVue(double fov){
			angle = fov;
			hautY = Maths::degreARadian(fov);
			droitX = hautY * (ratio);
			defFrustum();
		}

		void defPlanProche(double planProche){
			this->planProche = planProche;
		}

		void defPlanLoin(double planLoin){
			this->planLoin = planLoin;
		}

		void afficherTout(){

			if (camera != nullptr){
				camera->appliquer();
				//camera->rafraichir();
			}
			for (auto &i : objets){
				//glEnable(GL_LIGHTING);
				//glEnable(GL_LIGHT0);
				glEnableClientState(GL_VERTEX_ARRAY);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glEnableClientState(GL_NORMAL_ARRAY);
				glEnable(GL_TEXTURE_2D);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glEnable(GL_BLEND); 
				i->afficher();
				glDisable(GL_TEXTURE_2D);
				glDisableClientState(GL_VERTEX_ARRAY);
				glDisableClientState(GL_TEXTURE_COORD_ARRAY);
				glDisableClientState(GL_NORMAL_ARRAY);
				//glDisable(GL_LIGHTING);
				//glDisable(GL_LIGHT0);
			}
		}

		void defFrustum(double fov, double ratio, double min, double max){
			hautY = Maths::degreARadian(fov);
			droitX = hautY * ratio;
			planProche = min;
			planLoin = max;
			defFrustum();
		}

		void retObjet(Objet3D* objet){
			objets.remove(objet);
		}

		void ajouterObjet(Objet3D* Objet){
			objets.push_back(Objet);
		}

		void ajouterObjet(std::initializer_list<gfx::Objet3D*> list){
			objets.insert(objets.end(), list.begin(), list.end());
		}

		void vider(){
			if (!objets.empty()){
				objets.clear();
			}
		}

		void defCamera(gfx::Camera* camera){
			this->camera = camera;
		}

		Camera* obtCamera() {
			return camera;
		}

		~Gestionnaire3D(){
			vider();
			delete camera;
			camera = nullptr;
		}

	};
}