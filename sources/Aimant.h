class Aimant : public Objet{
private:
	double force;
public:
	Aimant(unsigned int ID, Vecteur3d position, double force) : Objet(gfx::Modele3D(), ID, "", 0., vitesse, position){
		this->position.x = position.x;
		this->position.y = position.y;
		this->position.z = position.z;
		this->force = force;
	}
	
	void defForce(double force){
		this->force = force;
	}
	double obtForce(){
		return force;
	}

	void defPosition(Vecteur3d position){
		this->position.x = position.x;
		this->position.y = position.y;
		this->position.z = position.z;
	}
	Vecteur3d obtPosition(){
		return position;
	}
};