class Piege : public Obstacle{
public:
	Piege(){}
	Piege(Modele3D modele, unsigned int ID, char* materiaux) : Obstacle(modele, ID, materiaux){}
};
