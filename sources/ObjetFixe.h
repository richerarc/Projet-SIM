class ObjetFixe : public Objet{
public:
	ObjetFixe(gfx::3D modele, unsigned int ID, char* materiaux, Vecteur3f position) : Objet(modele, ID, materiaux, 0, Vecteur3f(0., 0., 0.), position){}
};