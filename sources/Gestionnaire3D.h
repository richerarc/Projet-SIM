#pragma once

namespace gfx{
	class Gestionnaire3D
	{
	private:
		std::list<Objet3D*> objets;
		//Camera3D Cam;
	public:
		Gestionnaire3D(){
		}

		void afficherTout(){
			for (auto &i : objets){
				i->afficher();
			}
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

	void defFrustrum(double angle,double ratio, double min, double max){
		double HautY = Maths::degreARadian(angle);
		double DroitX = HautY * ratio;
		glMatrixMode(GL_PROJECTION); // Matrice de projection.
		glLoadIdentity();
		glFrustum(-DroitX, DroitX, -HautY, HautY, 1, 1000);
		glMatrixMode(GL_MODELVIEW);
	}
}