

class Vent : public Objet{
private:
	Vecteur3d dimensions;
public:
	Vent(Vecteur3d vitesse, unsigned int ID, Vecteur3d position, Vecteur3d dimensions) : Objet(gfx::Modele3D(), ID, "air", 0., vitesse, position){
		this->dimensions.x = dimensions.x;
		this->dimensions.y = dimensions.y;
		this->dimensions.z = dimensions.z;
	}
};