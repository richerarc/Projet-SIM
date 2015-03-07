#pragma once
#include "Texture.h"
class Sprite2D{
public:
	Texture* texture;

	Sprite2D(){
		texture = nullptr;
	}

	~Sprite2D(){
	}

	Texture* obtTexture(){
		return texture;
	}

	void defTexture(Texture* texture){
		this-> texture = texture;
	}
	//Ceci sera utile pour plutard quand je vais avoir a afficher le sprite, ne pas supprimer.
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