#pragma once
#include "Vecteur3.h"
#include "Vecteur2.h"
class Objet2D{
protected:
	Vecteur3f position;
	float positionx;
	float positiony;
	Vecteur3f orientation;
	Vecteur3f origine;
	Vecteur2i echelle;
	float echelled;
	SDL_Surface* surface;
public:
	Objet2D(Vecteur3f position){
		//this->position = position;
		//Setter l'origine à la position, et calculer la nouvelle position résultante
	//	origine = this->position;
		//this->position.x = position.x - (surface->w / 2);
	//	this->position.y = position.y - (surface->h / 2);

	}
	~Objet2D(){
		if (surface != nullptr){
			SDL_FreeSurface(surface);
			surface = nullptr;
		}
	}
	void afficher(){
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDisable(GL_DEPTH_TEST);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, 500, 0, 500, -1, 1); //Remplacer les deux 500 par la windows
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glEnable(GL_TEXTURE_2D);
		
		glBegin(GL_QUADS);
		//Mettre la surface à l'echelle
		//surface->h = surface->h*echelled;
		//surface->w = surface->w*echelled;

		glTexCoord2i(0, 0);
		glVertex2i(positionx, positiony);  //1

		glTexCoord2i(1, 0);
		glVertex2i(surface->w, positiony); //2

		glTexCoord2i(1, 1);
		glVertex2i(surface->w, surface->h); //3

		glTexCoord2i(0, 1);
		glVertex2i(positionx, surface->h); //4
	/*	glTexCoord2i(0, 0);
		glVertex2i(position.x, position.y);  //1

		glTexCoord2i(1,0);
		glVertex2i(surface->w, position.y); //2

		glTexCoord2i(1, 1);
		glVertex2i(surface->w, surface->h); //3

		glTexCoord2i(0, 1);
		glVertex2i(position.x, surface->h); //4*/

		glEnd();
		glPopMatrix();
	}

	void defPosition(float positionx, float positiony){
		this->positionx = positionx - (surface->w / 2);
		this->positiony = positiony - (surface->h / 2);
		//this->position = position;
	//	this->position.x = position.x - (surface->w / 2);
		//this->position.y = position.y - (surface->h / 2);
	}
	void defOrigine(Vecteur3f origine){
		this->origine = origine;
	}
	void defEchelle(float echelle){
		echelled = echelle;
		surface->h = surface->h*echelled;
		surface->w = surface->w*echelled;
	}
	Vecteur3f obtPosition(){ return position; }
	Vecteur3f obtOrigine(){ return origine; }
	Vecteur3f obtOrientation(){ return orientation; }
	Vecteur2i obtEchelle(){ return echelle; }
};