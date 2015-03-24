
class Obstacle : public Objet{
public:
	Obstacle(){}
	Obstacle(gfx::Modele3D& modele, unsigned int ID,char* materiaux,Vecteur3d position) : Objet(modele, ID, materiaux, 0, Vecteur3d(0.,0.,0.),position){}
};