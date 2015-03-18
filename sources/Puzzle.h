
class Puzzle : public Obstacle{
public:
	Puzzle(){}
	Puzzle(Modele3D modele, unsigned int ID, char* materiaux) : Obstacle(modele,ID,materiaux){}
};