#pragma once
#include "Vecteur3.h"
namespace gfx{
class Objet3D{
private:
	Vecteur3f position;
	Vecteur3f origine;
	Vecteur3f orientation;

public:

	Objet3D(){
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

	void defPosition(Vecteur3f &pos){
		position = pos;
	}

	void defOrigine(Vecteur3f &org){
		origine = org;
	}

	void defOrientation(Vecteur3f &ort){
		orientation = ort;
	}
	void rotationner(Vecteur3f &rot){
		orientation += rot;
	}

	void deplacer(Vecteur3f &dep){
		position += dep;
	}

	void defPosition(int axeX, int axeY, int axeZ){
		position.x = axeX;
		position.y = axeY;
		position.z = axeZ;
	}

	void defOrigine(int axeX, int axeY, int axeZ){
		origine.x = axeX;
		origine.y = axeY;
		origine.z = axeZ;
	}

	void defOrientation(int axeX, int axeY, int axeZ){
		orientation.x = axeX;
		orientation.y = axeY;
		orientation.z = axeZ;

	}

	void rotationner(float axeX, float axeY, float axeZ){
		orientation.x += axeX;
		orientation.y += axeY;
		orientation.z += axeZ;
	}

	void deplacer(int axeX, int axeY, int axeZ){
		position.x += axeX;
		position.y += axeY;
		position.z += axeZ;
	}

	virtual void rafraichir() = 0;

	virtual void afficher() = 0;

};
}