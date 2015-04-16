#pragma once
#include "Objet2D.h"
#include "Texture.h"
#include "Fenetre.h"
#include "Rect.h"
namespace gfx{
	class Texte2D : public Objet2D{
	public:
		const char* texte;
		unsigned int taille;
		SDL_Color couleur;
		TTF_Font* police;
		GLuint ID;


		Texte2D(const char* texte, const char* pathPolice, int taille, Vecteur2f  position) : Objet2D(position){
			this->texte = texte;
			this->taille = taille;
			police = TTF_OpenFont(pathPolice, taille);
			couleur = { 255, 255, 255, 255 };
			chargerSurface();
		}
		Texte2D(){
			this->texte = nullptr;
			this->taille = 0;
			police = nullptr;
		}
		~Texte2D(){
			TTF_CloseFont(police);
		}
		void chargerSurface(){
			surface = TTF_RenderText_Blended(police, texte, couleur);
			glGenTextures(1, &ID);
			glBindTexture(GL_TEXTURE_2D, ID);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, surface->pixels);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		void defTexte(const char* texte){
			this->texte = texte;
			chargerSurface();
		}
		void afficher(gfx::Fenetre& fenetre){
			glDisable(GL_DEPTH_TEST);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(0, fenetre.obtTaille().x, 0, fenetre.obtTaille().y, -1, 1);
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glBindTexture(GL_TEXTURE_2D, ID);
			glLoadIdentity();
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glMatrixMode(GL_MODELVIEW);

			glBegin(GL_QUADS);

			glTexCoord2i(0, 1);
			glVertex2d(position.x, position.y);  //1

			glTexCoord2i(1, 1);
			glVertex2d(surface->w + position.x, position.y); //2

			glTexCoord2i(1, 0);
			glVertex2d(surface->w + position.x, surface->h + position.y); //3

			glTexCoord2i(0, 0);
			glVertex2d(position.x, surface->h + position.y); //4


			glEnd();

			glDisable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);
			glMatrixMode(GL_PROJECTION);
			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
			glPopMatrix();
		}
		void defPolice(const char* pathPolice){
			police = TTF_OpenFont(pathPolice, taille);
			chargerSurface();
		}
		void defTaille(unsigned int taille){
			this->taille = taille;
			chargerSurface();
		}
		void defCouleur(SDL_Color couleur){
			this->couleur = couleur;
			chargerSurface();
		}
		const char* obtTexte(){ return texte; }
		unsigned int obtTaille(){ return taille; }
		SDL_Color obtCouleur(){ return couleur; }

		Rectf obtRectangle(){
			return Rectf(position.x, position.y, surface->w, surface->h);
		}


	};
}