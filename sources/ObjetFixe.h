class ObjetFixe : public Objet{
public:
	ObjetFixe(unsigned int ID, char* materiaux, Modele3D modele) : Objet(modele, ID, materiaux){}
};