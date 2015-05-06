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
			if (texture != nullptr)
				this->surface = texture->obtSurface();
			this->position.x = this->position.x/* + (surface->w / 2)*/;
			this->position.y = this->position.y /*+ (surface->h / 2)*/;
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
			if (texture != nullptr){
				glDisable(GL_DEPTH_TEST);
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				glOrtho(0, fenetre.obtTaille().x, 0, fenetre.obtTaille().y, -1, 1);
				glMatrixMode(GL_MODELVIEW);

				glPushMatrix();
				glLoadIdentity();
				glScaled(this->echelle.x, this->echelle.y, 1);
				glEnable(GL_TEXTURE_2D);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glEnable(GL_BLEND);
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

				

				glTranslatef(position.x - origine.x, position.y - origine.y, 0.0f);
				glRotatef(orientation, 0.0f, 0.0f, 1.0f);
				glTranslatef(origine.x, origine.y, 0.0f);

				glDisable(GL_BLEND);
				glDisable(GL_TEXTURE_2D);
				glMatrixMode(GL_PROJECTION);
				glPopMatrix();
				glMatrixMode(GL_MODELVIEW);
				glPopMatrix();
			}

		}
		void defTexture(Texture* texture){
			this->texture = texture;
			if (texture != nullptr)
				this->surface = texture->obtSurface();
		}

		Rectf obtRectangle(){
			return Rectf(position.x, position.y, surface->w, surface->h);
		}

		void defPosModifier(void) {
			double mat[16];
			glPushMatrix();
			glLoadIdentity();
			glScaled(this->echelle.x, this->echelle.y, 1);
			glGetDoublev(GL_MODELVIEW_MATRIX, mat);
			glPopMatrix();

			Vecteur2f posOrigine = { this->position.x + 0.1f, this->position.y + 0.1f };
			Vecteur2f posOrigineModifier;

			double vecteurNormal[4];
			double normalTemp[4];
			normalTemp[3] = 1;
			normalTemp[2] = 0;
			normalTemp[0] = posOrigine.x;
			normalTemp[1] = posOrigine.y;

			vecteurNormal[0] = (mat[0] * normalTemp[0]) + (mat[4] * normalTemp[1]) + (mat[8] * normalTemp[2]) + (mat[12] * normalTemp[3]);
			vecteurNormal[1] = (mat[1] * normalTemp[0]) + (mat[5] * normalTemp[1]) + (mat[9] * normalTemp[2]) + (mat[13] * normalTemp[3]);
			vecteurNormal[2] = (mat[2] * normalTemp[0]) + (mat[6] * normalTemp[1]) + (mat[10] * normalTemp[2]) + (mat[14] * normalTemp[3]);
			vecteurNormal[3] = (mat[3] * normalTemp[0]) + (mat[7] * normalTemp[1]) + (mat[11] * normalTemp[2]) + (mat[15] * normalTemp[3]);

			this->position.x = this->position.x + (this->position.x + (vecteurNormal[0] / vecteurNormal[3]));
			this->position.y = this->position.y + (this->position.y + (vecteurNormal[1] / vecteurNormal[3]));


		}
	};
}