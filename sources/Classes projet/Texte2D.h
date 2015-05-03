#pragma once
#include "Objet2D.h"
#include "Texture.h"
#include "Fenetre.h"
#include "Rect.h"
namespace gfx{
	class Texte2D : public Objet2D{
	public:
		gfx::Texte* texte;

		Texte2D(std::string* texte, SDL_Color couleur, gfx::Police* police, Vecteur2f position) : Objet2D(position){
			this->texte = gfx::GestionnaireRessources::obtInstance().obtTexte(texte->c_str(), couleur, police);
			surface = nullptr;
		}
		Texte2D(){
			this->texte = nullptr;

		}

		void defTexte(std::string* texte){
			this->texte = gfx::GestionnaireRessources::obtInstance().obtTexte(texte->c_str(), this->texte->obtCouleur(), this->texte->obtPolice());
		}
		void afficher(gfx::Fenetre& fenetre){
			if (texte->obtSurface() != nullptr){
				glDisable(GL_DEPTH_TEST);
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				glOrtho(0, fenetre.obtTaille().x, 0, fenetre.obtTaille().y, -1, 1);
				glMatrixMode(GL_MODELVIEW);
				glPushMatrix();
				glBindTexture(GL_TEXTURE_2D, texte->obtID());
				glLoadIdentity();
				glScaled(this->echelle.x, this->echelle.y, 1);
				glEnable(GL_TEXTURE_2D);
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glMatrixMode(GL_MODELVIEW);

				glBegin(GL_QUADS);

				glTexCoord2i(0, 1);
				glVertex2d(position.x, position.y);  //1

				glTexCoord2i(1, 1);
				glVertex2d(texte->obtSurface()->w + position.x, position.y); //2

				glTexCoord2i(1, 0);
				glVertex2d(texte->obtSurface()->w + position.x, texte->obtSurface()->h + position.y); //3

				glTexCoord2i(0, 0);
				glVertex2d(position.x, texte->obtSurface()->h + position.y); //4


				glEnd();



				glDisable(GL_TEXTURE_2D);
				glDisable(GL_BLEND);
				glMatrixMode(GL_PROJECTION);
				glPopMatrix();
				glMatrixMode(GL_MODELVIEW);
				glPopMatrix();
			}
		}
		void defPolice(Police* police){
			this->texte = gfx::GestionnaireRessources::obtInstance().obtTexte(texte->obtTexte(), texte->obtCouleur(), police);
		}

		void defCouleur(SDL_Color couleur){
			this->texte = gfx::GestionnaireRessources::obtInstance().obtTexte(texte->obtTexte(), couleur, texte->obtPolice());
		}

		Rectf obtRectangle(){
			return Rectf(position.x, position.y, texte->obtSurface()->w, texte->obtSurface()->h);
		}


	};
}