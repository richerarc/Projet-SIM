#pragma once
namespace gfx{

	class Objet2D{
	protected:

		Vecteur2f position;
		double orientation;
		Vecteur2f origine;
		Vecteur2f echelle;
		SDL_Surface* surface;

	public:

		Objet2D(Vecteur2f position){
			this->position = position;
			echelle.x = (float)fenetre->obtTaille().x / RESOLUTION_DEFAUT_X;
			echelle.y = (float)fenetre->obtTaille().y / RESOLUTION_DEFAUT_Y;
		}

		Objet2D():Objet2D(Vecteur2f()){
		}

		~Objet2D(){
		}

		virtual void afficher(gfx::Fenetre& fenetre) = 0;

		void defPosition(Vecteur2f position){
			this->position = position;
		}
		void deplacer(Vecteur2f position){
			this->position = this->position + position;
		}
		void defOrigine(Vecteur2f origine){
			this->origine = origine;
		}
		void defEchelle(Vecteur2f echelle){
			this->echelle = echelle;
		}
		void defOrientation(double orientation){
			this->orientation = orientation;
		}
		void rotationner(double orientation){
			this->orientation = this->orientation + orientation;
		}

		Vecteur2f obtPosition(){ return position; }
		Vecteur2f obtOrigine(){ return origine; }
		double obtOrientation(){ return orientation; }
		Vecteur2f obtEchelle(){ return echelle; }
	};
}