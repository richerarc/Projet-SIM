#pragma once

namespace gfx{
	class Gestionnaire3D
	{
	private:
		std::list<Objet3D*> objets;
		//Camera3D Cam;
		double hautY, droitX, ratio, angle, planProche, planLoin;

	public:
		Gestionnaire3D(gfx::Fenetre fenetre ){
			hautY = Maths::degreARadian(70);
			droitX = hautY* (fenetre.obtTaille().x / fenetre.obtTaille().y);

		}

		void afficherTout(){
			for (auto &i : objets){
				i->afficher();
			}
		}

		void defFrustrum(double angle, double ratio, double min, double max){
			hautY = Maths::degreARadian(angle);
			droitX = hautY * ratio;
			glMatrixMode(GL_PROJECTION); // Matrice de projection.
			glLoadIdentity();
			glFrustum(-droitX, droitX, -hautY, hautY, 1, 1000);
			glMatrixMode(GL_MODELVIEW);
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

	//	void defCamera(Camera3D Camera){

	//	}

		~Gestionnaire3D(){
			vider();
		}

	};
}