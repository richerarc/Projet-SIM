class Piege : public Obstacle{
public:
	Piege(){}
	Piege(gfx::Modele3D modele, unsigned int ID, char* materiaux) : Obstacle(modele, ID, materiaux){}
};
