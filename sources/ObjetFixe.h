class ObjetFixe : public Objet{
public:
	ObjetFixe(unsigned int ID, char* materiaux, gfx::Modele3D modele) : Objet(modele, ID, materiaux, NULL, NULL){}

	Vecteur3d obtPosition(){
		return modele->obtPosition();
	}
};