#pragma once
#include "Objet2D.h"
#include "Texture.h"
#include "Fenetre.h"
#include "Rect.h"
namespace gfx{
	class Sprite2D : public Objet2D{
	public:
		Texture* texture;

		Sprite2D(Vecteur2f position, Texture* texture) : Objet2D(position){
			this->texture = texture;
			this->surface = texture->obtSurface();
			this->position.x = this->position.x + (surface->w / 2);
			this->position.y = this->position.y + (surface->h / 2);
		}
		Sprite2D(){
			texture = nullptr;
		}
		~Sprite2D(){
		}

		Texture* obtTexture(){
			return texture;
		}
		void afficher(gfx::Fenetre& fenetre){
	
			glDisable(GL_DEPTH_TEST);
			glMatrixMode(GL_MODELVIEW);

			glPushMatrix();
			glLoadIdentity();

			glTranslatef(position.x - origine.x, position.y - origine.y, 0.0f);
			glRotatef(orientation, 0.0f, 0.0f, 1.0f);
			glTranslatef(origine.x, origine.y, 0.0f);

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture->obtID());

			glBegin(GL_QUADS);

			glTexCoord2i(0, 1);
			glVertex2f(position.x, position.y);  //1

			glTexCoord2i(1, 1);
			glVertex2f(surface->w + position.x, position.y); //2

			glTexCoord2i(1, 0);
			glVertex2f(surface->w + position.x, surface->h + position.y); //3

			glTexCoord2i(0, 0);
			glVertex2f(position.x, surface->h + position.y); //4
			glEnd();
			glPopMatrix();
			glDisable(GL_TEXTURE_2D);

		}
		void defTexture(Texture* texture){
			this->texture = texture;
			this->surface = texture->obtSurface();
		}

		Rectf obtRectangle(){
			return Rectf(position.x, position.y, surface->w, surface->h);
		}
	};
}