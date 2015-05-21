#include "ObjetFixe.h"

class Commutateur : public Objet{
private:
	bool O_F;
public:
	
	Commutateur(gfx::Modele3D* modele, unsigned int ID, char* materiaux, Vecteur3d position, Vecteur3d vitesseAngulaire, bool collisionInterne) : Objet(modele, ID, materiaux, 0, Vecteur3d(0., 0., 0.), position, vitesseAngulaire, collisionInterne){O_F = 0;}
	
	bool actioner(){
		O_F = !O_F;
		if (O_F){
			modele->rotationner(-90, 0, 0);
		}
		else if (!O_F){
			modele->rotationner(90, 0, 0);
		}
		return O_F;
	}
	bool obtEtat(){return O_F;}
	bool obtSiPorte(){return false;}
};