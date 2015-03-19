#pragma once
#include "Vecteur3.h"

namespace gfx{

	class Objet3D{
	protected:
		Vecteur3f position;
		Vecteur3f origine;
		Vecteur3f orientation;

	public:

		Objet3D(){
			position = Vecteur3f(0, 0, 0);
			origine = Vecteur3f(0, 0, 0);
			orientation = Vecteur3f(0, 0, 0);
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

		virtual void defPosition(Vecteur3f &pos) = 0;

		virtual void defOrigine(Vecteur3f &org) = 0;

		virtual void defOrientation(Vecteur3f &ort) = 0;

		virtual void rotationner(Vecteur3f &rot) = 0;

		virtual void deplacer(Vecteur3f &dep) = 0;

		virtual void defPosition(float axeX, float axeY, float axeZ) = 0;

		virtual void defOrigine(float axeX, float axeY, float axeZ) = 0;

		virtual void defOrientation(float axeX, float axeY, float axeZ) = 0;

		virtual void rotationner(float axeX, float axeY, float axeZ) = 0;

		virtual void deplacer(float axeX, float axeY, float axeZ) = 0;

		virtual void afficher() = 0;

	};
}



