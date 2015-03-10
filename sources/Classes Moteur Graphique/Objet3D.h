#pragma once

class Objet3D{
private:
	Vecteur3f position;
	Vecteur3f origine;
	Vecteur3f orientation;

public:

	Objet3D(){
		position = new Vecteur3f();
		origine = new Vecteur3f();
		orientation = new Vecteur3f();
	}
	
	~Objet3D(){
	}

	Vecteur3f obtPosition(){
		return position;
	}

	Vecteur3f obtOrigine(){
		return origine;
	}

	Vecteur3f obtOrientation(){
		return orientation;
	}

	void defPosition(Vecteur3f pos){
		position = pos;
	}

	void defOrigine(Vecteur3f org){
		origine = org;
	}

	void defOrientation(Vecteur3f ort){
		orientation = ort;
	}

	void Afficher(){
		
	}

};