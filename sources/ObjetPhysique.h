class ObjetPhysique : public Objet{
public:
	ObjetPhysique(unsigned int ID, char* materiaux, Modele3D modele, double masse, Vecteur3d vitesse) : Objet(modele, ID, materiaux, masse, vitesse){}
};