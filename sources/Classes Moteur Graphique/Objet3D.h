#pragma once
#include "Vecteur3.h"

namespace gfx{

	class Objet3D{
	protected:
		Vecteur3d position;
		Vecteur3d origine;
		Vecteur3d orientation;

	public:

		Objet3D(){
			position = Vecteur3d(0, 0, 0);
			origine = Vecteur3d(0, 0, 0);
			orientation = Vecteur3d(0, 0, 0);
		}

		~Objet3D(){
		}

		Vecteur3d obtPosition(){
			return position;
		}

		Vecteur3d obtOrigine(){
			return origine;
		}

		Vecteur3d obtOrientation(){
			return orientation;
		}

		virtual void defPosition(Vecteur3d &pos) = 0;

		virtual void defOrigine(Vecteur3d &org) = 0;

		virtual void defOrientation(Vecteur3d &ort) = 0;

		virtual void rotationner(Vecteur3d &rot) = 0;

		virtual void deplacer(Vecteur3d &dep) = 0;

		virtual void defPosition(double axeX, double axeY, double axeZ) = 0;

		virtual void defOrigine(double axeX, double axeY, double axeZ) = 0;

		virtual void defOrientation(double axeX, double axeY, double axeZ) = 0;

		virtual void rotationner(double axeX, double axeY, double axeZ) = 0;

		virtual void deplacer(double axeX, double axeY, double axeZ) = 0;

		virtual void afficher() = 0;

	};
}



