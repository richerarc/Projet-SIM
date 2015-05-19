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
				camera->rafraichir();
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

		void ajouterTexture(gfx::Texture* texture, Vecteur3d position, Vecteur3d normale){
			//Vecteur3d tx = normale.produitVectoriel(normale + Vecteur3d(1, 2, 3));
			//Vecteur3d ty = normale.produitVectoriel(tx);
			//double d = position.norme();
			//double n = normale.norme();
			//double vertices[] = { (tx.x + ty.x) + n * d, (tx.y + ty.y) + n * d, (tx.z + ty.z) + n * d,
			//					  (tx.x - ty.x) + n * d, (tx.y - ty.y) + n * d, (tx.z - ty.z) + n * d,
			//					  (-tx.x - ty.x) + n * d, (-tx.y - ty.y) + n * d, (-tx.z - ty.z) + n * d,
			//					  (tx.x - ty.x) + n * d, (tx.y - ty.y) + n * d, (tx.z - ty.z) + n * d,
			//					  (-tx.x - ty.x) + n * d, (-tx.y - ty.y) + n * d, (-tx.z - ty.z) + n * d,
			//					  (-tx.x + ty.x) + n * d, (-tx.y + ty.y) + n * d, (-tx.z + ty.z) + n * d };
			//double textures[] = { 0, 1,
			//					  1, 1,
			//					  1, 0,
			//				      1, 1,
			//					  1, 0,
			//					  0, 0 };
			//double normales[] = { normale.x, normale.y, normale.z,
			//					  normale.x, normale.y, normale.z,
			//				   	  normale.x, normale.y, normale.z,
			//					  normale.x, normale.y, normale.z,
			//					  normale.x, normale.y, normale.z,
			//					  normale.x, normale.y, normale.z };
			//gfx::Modele modele(vertices, textures, normales);
			//gfx::Modele3D plan(&modele, texture);
			//objets.push_back(&plan);
			gfx::Modele3D* plan = new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/trouDeBalle.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/trouDeBalle.png"));
			plan->defPosition(position + normale * 0.01);
			Vecteur3d vRot = normale.angleEntreVecteurs(Vecteur3d(plan->obtModele()->obtNormales()[0], plan->obtModele()->obtNormales()[1], plan->obtModele()->obtNormales()[2]));
			plan->rotationner(0, vRot.x, 0);
			objets.push_back(plan);
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