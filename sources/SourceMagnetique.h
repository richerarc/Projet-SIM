class SourceMagnetique : public Objet{
private:
	Vecteur3d position;
	double force;
public:	
	SourceMagnetique(gfx::Modele3D modele, Vecteur3d position, double force) : Objet(modele, ID, NULL, NULL, NULL){
		this->position.x = position.x;
		this->position.y = position.y;
		this->position.z = position.z;
		this->force = force;
	}

	double obtForce(){
		return force;
	}

	void defForce(double force){
		this->force = force;
	}

	Vecteur3d obtPosition(){
		return modele->obtPosition();
	}

	void defPosition(Vecteur3D position){
		modele->defPosition(position.x, position.y, position.z);
		this->position.x = position.x;
		this->position.y = position.y;
		this->position.z = position.z;
	}
};