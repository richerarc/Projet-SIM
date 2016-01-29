#pragma once
#include "GestionnaireEvenements.h"

namespace gfx {

	class BarreProgressive : public Objet2D{

	private:
		gfx::Sprite2D* textureFond;
		SDL_Color couleurBarre;
		Rectf fond;

	public:

		BarreProgressive(gfx::Texture* texture, SDL_Color couleur, Vecteur2f position) : Objet2D(position){

			textureFond = new Sprite2D(position, texture);
			couleurBarre = couleur;
			fond = Rectf(position.x + 2, position.y + 2, 10, texture->obtSurface()->h - 4);
		}

		void rafraichir(float pourcentage) {

			if (fond.l < textureFond->obtTexture()->obtSurface()->w - 4)
				fond.l = (pourcentage / 100) * (textureFond->obtTexture()->obtSurface()->w - 4);

		}

		void afficher(gfx::Fenetre& fenetre) {

			textureFond->afficher(fenetre);

			glDisable(GL_DEPTH_TEST);
			glMatrixMode(GL_MODELVIEW);
			glEnable(GL_COLOR);

			glPushMatrix();
			glLoadIdentity();
			glScaled(this->echelle.x, this->echelle.y, 1);
			
			glBegin(GL_QUADS);

			glVertex2f(fond.x, fond.y);  //1

			glVertex2f(fond.l + fond.x, fond.y); //2

			glVertex2f(fond.l + fond.x, fond.h + fond.y); //3

			glVertex2f(fond.x, fond.h + fond.y); //4
			glEnd();

			glPopMatrix();

		}
	};
}