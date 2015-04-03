#pragma once
#include <list>
#include "CameraGodMode.h"
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
			/*à changer quand on aura une fps*/
			camera = new gfx::CameraGodMode(Vecteur3d(0, 0, 0));
			hautY = Maths::degreARadian(70);
			ratio = ((double)fenetre.obtTaille().x / (double)fenetre.obtTaille().y);
			droitX = hautY * (ratio);
			planProche = 1;
			planLoin = 1000;
			defFrustum();
		}

		Gestionnaire3D(){
			camera = new gfx::CameraGodMode(Vecteur3d(0, 0, 0));
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
			for (auto &i : objets){
				i->afficher();
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

		void vider(){
			if (!objets.empty()){
				objets.clear();
			}
		}

		void defCamera(gfx::Camera* camera){
			this->camera = camera;
		}

		~Gestionnaire3D(){
			vider();
			delete camera;
			camera = nullptr;
		}

	};
}