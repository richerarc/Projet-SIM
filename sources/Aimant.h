class Aimant : public Objet{
private:
	double force;
public:
	Aimant(gfx::Modele3D modele, unsigned int ID, Vecteur3d position, double force) : Objet(modele, ID, "metal", 0.f, Vecteur3d(0.f, 0.f, 0.f), position){
		this->force = force;
	}

	void defForce(double force){
		this->force = force;
	}
	double obtForce(){
		return force;
	}
};