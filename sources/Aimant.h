class Aimant : public Objet{
private:
	double force;
public:
	Aimant(gfx::Modele3D, modlele, unsigned int ID, Vecteur3d position, double force) : Objet(modlele, ID, "metaux", 0., vitesse, position){
		this->force = force;
	}
	
	void defForce(double force){
		this->force = force;
	}
	double obtForce(){
		return force;
	}
};