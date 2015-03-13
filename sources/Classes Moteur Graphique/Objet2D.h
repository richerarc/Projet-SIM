#pragma once
#include "Vecteur3.h"
class Objet2D{
protected:
	Vecteur3f position;
	Vecteur3f orientation;
	Vecteur3f origine;
	Vecteur3i echelle;
	SDL_Surface* surface;
public:
	Objet2D(Vecteur3f position){
		this->position = position;
	}
	void afficher(){


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDisable(GL_DEPTH_TEST);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, 500, 0, 500, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		glEnable(GL_TEXTURE_2D);
		unsigned int ID;
		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBegin(GL_QUADS);

		glTexCoord2i(0, 0);
		glVertex2i(0, 0);
		glTexCoord2i(1,0);
		glVertex2i(surface->w, 0);
		glTexCoord2i(1, 1);
		glVertex2i(surface->w,surface->h);
		glTexCoord2i(0, 1);
		glVertex2i(0,surface->h);
		glEnd();
		glPopMatrix();




	/*	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, 500, 0, 500, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glEnable(GL_TEXTURE_2D);
		unsigned int ID;
		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//Réduire la texture
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//Agrandire la texture

		

		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBegin(GL_QUADS);

		glTexCoord2i(0,surface->h);
		glVertex2i(0, 0);
		glTexCoord2i(surface->w, surface->h);
		glVertex2i(surface->w, 0);
		glTexCoord2i(surface->w, 0);
		glVertex2i(surface->w, surface->h);
		glTexCoord2i(0, 0);
		glVertex2i(0, surface->h);

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnd();
		glFlush();
		*/
	}

	void defPosition(Vecteur3f position){
		this->position = position;
	}
	void defOrigine(Vecteur3f origine){
		this->origine = origine;
	}
	void defEchelle(Vecteur3i echelle){
		this->echelle = echelle;
	}
	Vecteur3f obtPosition(){ return position; }
	Vecteur3f obtOrigine(){ return origine; }
	Vecteur3f obtOrientation(){ return orientation; }
	Vecteur3i obtEchelle(){ return echelle; }
};