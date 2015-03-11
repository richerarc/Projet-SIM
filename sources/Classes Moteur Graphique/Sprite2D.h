#pragma once
#include "Texture.h"
#include "Vecteur3.h"
#include "Objet2D.h"
class Sprite2D : public Objet2D{
public:
	Texture* texture;

	Sprite2D(Vecteur3f position , Texture* texture) : Objet2D(position){
		this->texture = texture;
		this->surface = texture->obtSurface();
	}
	~Sprite2D(){
	}

	Texture* obtTexture(){
		return texture;
	}

	void defTexture(Texture* texture){
		this->texture = texture;
		this->surface = texture->obtSurface();
	}
};