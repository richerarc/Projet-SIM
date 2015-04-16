#pragma once 
#include "Vecteur2.h"

template<typename T>
class Rect{
public:
	Rect(T x = 0, T y = 0, T l = 0, T h = 0){
		this->h = h;
		this->l = l;
		this->y = hauteur - y - h;
		this->x = x;
	}

	bool contient(float x, float y){
		bool estDansX = x >= this->x && x <= (this->x + this->l);
		bool estDansY = y >= this->y && y <= (this->y + this->h);
		return estDansX && estDansY;
	}
	bool contient(Vecteur2<T> &point){
		return contient(point.x, point.y);
	}
	bool intersecte(Rect<T> &rect){
		if (contient(rect.x, rect.y) || contient(rect.x, rect.y + rect.h) || contient(rect.x + rect.l, rect.y) || contient(rect.x + rect.l, rect.y + rect.h))
			return true;
		return false;
	}

	static void defDimention(int h) {

		hauteur = h;
	}

	T x, y, l, h;

	static int hauteur;
};
typedef Rect<int> Recti;
typedef Rect<float> Rectf;
typedef Rect<double> Rectd;

int Rect<float>::hauteur = 0;