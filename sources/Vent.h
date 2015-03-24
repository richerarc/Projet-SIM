

class Vent : public Objet{
private:
	Vecteur3f position;
	Vecteur3f dimensions;
public:
	Vent(Vecteur3f vitesse, unsigned int ID, Vecteur3f position, Vecteur3f dimensions) : Objet(gfx::Modele3D(), ID, NULL, NULL, vitesse, position){
		this->position.x = position.x;
		this->position.y = position.y;
		this->position.z = position.z;
		this->dimensions.x = dimensions.x;
		this->dimensions.y = dimensions.y;
		this->dimensions.z = dimensions.z;
	}

	void defPosition(Vecteur3f position){
		this->position.x = position.x;
		this->position.y = position.y;
		this->position.z = position.z;
	}
	Vecteur3f obtPosition(){
		return position;
	}

	void defDimensions(Vecteur3f dimensions) {
		this->dimensions.x = dimensions.x;
		this->dimensions.y = dimensions.y;
		this->dimensions.z = dimensions.z;
	}

	Vecteur3f obtDimensions() {
		return dimensions;
	}
};