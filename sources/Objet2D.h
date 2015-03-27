#include "Texte2D.h"
#include "Sprite2D.h"
namespace gfx{
	class Objet2D{
	protected:
		Vecteur2d position;
		double orientation;
		Vecteur2d origine;
		Vecteur2d echelle;
		SDL_Surface* surface;
	public:
		Objet2D(Vecteur2d position){
			this->position = position;
			echelle.x = 1;
			echelle.y = 1;

		}
		~Objet2D(){
			if (surface != nullptr){
				SDL_FreeSurface(surface);
				surface = nullptr;
			}
		}
		virtual void afficher(gfx::Fenetre& fenetre) = 0;

		void defPosition(Vecteur2d position){
			this->position = position;
		}
		void deplacer(Vecteur2d position){
			this->position = this->position + position;
		}
		void defOrigine(Vecteur2d origine){
			this->origine = origine;
		}
		void defEchelle(Vecteur2d echelle){
			this->echelle = echelle;
			surface->h = surface->h*echelle.y;
			surface->w = surface->w*echelle.x;
		}
		void defOrientation(double orientation){
			this->orientation = orientation;
		}
		void rotationner(double orientation){
			this->orientation = this->orientation + orientation;
		}

		Vecteur2d obtPosition(){ return position; }
		Vecteur2d obtOrigine(){ return origine; }
		double obtOrientation(){ return orientation; }
		Vecteur2d obtEchelle(){ return echelle; }
	};
}