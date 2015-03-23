
class Obstacle : public Objet{
public:
	Obstacle(){}
	Obstacle(Modele3D modele, unsigned int ID,char* materiaux) : Objet(modele, ID, materiaux, NULL, NULL){}
	Vecteur3d obtPosition(){
		return modele->obtPosition();
	}
};