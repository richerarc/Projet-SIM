#pragma once
#include "Texture.h"
#include "Vecteur3.h"
class Sprite2D : public Objet2D{
public:
	Texture* texture;

	Sprite2D(Vecteurf position , Texture* texture) : Objet2D(position){
		this->texture = texture;
	}
	Sprite2D(){}

	~Sprite2D(){
	}

	Texture* obtTexture(){
		return texture;
	}

	void defTexture(Texture* texture){
		this->texture = texture;
	}
	//Ceci sera utile pour plutard, ne pas supprimer.
	/*glBegin(GL_QUADS);
	glTexCoord2i(0, texture->obtSurface.h);
	glVertex2i(0, 0);
	glTexCoord2i(texture->obtSurface.w, texture->obtSurface.h);
	glVertex2i(texture->obtSurface.w, 0);
	glTexCoord2i(texture->obtSurface.w, 0);
	glVertex2i(texture->obtSurface.w, texture->obtSurface.h);
	glTexCoord2i(0, 0);
	glVertex2i(0, texture->obtSurface.h);
	glEnd();*/
};