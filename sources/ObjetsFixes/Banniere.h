class Banniere : public ObjetFixe{
public:
	Banniere(gfx::Modele3D modele, unsigned int ID, char* materiaux, Vecteur3d position) : ObjetFixe(modele, ID, materiaux, 0, Vecteur3d(0., 0., 0.), position){
		//Associele bon modèle ici...
	}
};