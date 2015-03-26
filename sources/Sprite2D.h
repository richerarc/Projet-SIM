#pragma once
#include "Texture.h"
#include "Objet2D.h"
#include "Fenetre.h"
namespace gfx{
	class Sprite2D : public Objet2D{
	public:
		Texture* texture;

		Sprite2D(Vecteur2d  position, Texture* texture) : Objet2D(position){
			this->texture = texture;
			this->surface = texture->obtSurface();
			this->position.x = this->position.x + (surface->w / 2);
			this->position.y = this->position.y + (surface->h / 2);
		}
		~Sprite2D(){
		}

		Texture* obtTexture(){
			return texture;
		}
		void afficher(gfx::Fenetre& fenetre){
	
			glDisable(GL_DEPTH_TEST);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(0, fenetre.obtTaille().x, 0, fenetre.obtTaille().y, -1, 1); 
			glMatrixMode(GL_MODELVIEW);

			glLoadIdentity();

		
			glTranslated(position.x - origine.x, position.y - origine.y, 0.0f);
			glRotated(orientation, 0.0f, 0.0f, 1.0f);
			glTranslated(origine.x, origine.y, 0.0f);
			glPushMatrix();

			glBindTexture(GL_TEXTURE_2D, texture->obtID());
			glEnable(GL_TEXTURE_2D);
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

			glPopMatrix();

		}
		void defTexture(Texture* texture){
			this->texture = texture;
			this->surface = texture->obtSurface();
		}
	};
}