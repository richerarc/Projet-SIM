#pragma once

class Objet3D{
private:
	Vecteur3f position;
	Vecteur3f origine;
	Vecteur3f orientation;

public:

	Objet3D(){}
	
	~Objet3D(){}

	Vecteur3f obtPosition(){}

	Vecteur3f obtOrigine(){}

	Vecteur3f obtOrientation(){}

	void defPosition(Vecteur3f pos){}

	void defOrigine(Vecteur3f pos){}

	void defOrientation(Vecteur3f pos){}

	void Afficher(){}

};