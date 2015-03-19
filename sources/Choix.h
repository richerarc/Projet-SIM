
class Choix : public Obstacle{
public:
	Choix(){}
	Choix(Modele3D modele, unsigned int ID, char* materiaux) : Obstacle(modele, ID, materiaux){}
};
