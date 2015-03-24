

class Vent : public Objet{
private:
	Vecteur3d position;
	Vecteur3d dimensions;
public:
	Vent(Vecteur3d vitesse, unsigned int ID, Vecteur3d position, Vecteur3d dimensions) : Objet(gfx::Modele3D(), ID, "air", 0., vitesse, position){
		this->position.x = position.x;
		this->position.y = position.y;
		this->position.z = position.z;
		this->dimensions.x = dimensions.x;
		this->dimensions.y = dimensions.y;
		this->dimensions.z = dimensions.z;
	}

	void defPosition(Vecteur3d position){
		this->position.x = position.x;
		this->position.y = position.y;
		this->position.z = position.z;
	}
	Vecteur3d obtPosition(){
		return position;
	}

	void defDimensions(Vecteur3d dimensions) {
		this->dimensions.x = dimensions.x;
		this->dimensions.y = dimensions.y;
		this->dimensions.z = dimensions.z;
	}

	Vecteur3d obtDimensions() {
		return dimensions;
	}
};