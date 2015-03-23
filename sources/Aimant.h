class Aimant : public Objet{
private:
	double force;
public:
	Aimant(unsigned int ID, Vecteur3f position, double force) : Objet(gfx::Modele3D(), ID, NULL, NULL, vitesse, position){
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

	void defPosition(Vecteur3f position){
		this->position.x = position.x;
		this->position.y = position.y;
		this->position.z = position.z;
	}
	Vecteur3f obtPosition(){
		return position;
	}
};