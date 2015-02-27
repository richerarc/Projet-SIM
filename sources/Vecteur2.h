#pragma once
#include <vector>
#include <SDL2/SDL.h>

template<typename T>
class Vecteur2{
public:
	T x, y;
	
	Vecteur2(T x = 0, T y = 0) { 
		this->x = x; this->y = y; 
	}
		
	Vecteur2 operator+(Vecteur2& vect) { 
		return Vecteur2(this->x + vect.x, this->y + vect.y); 
	}
		
	void operator+=(Vecteur2& autre) { 
		x += autre.x; y += autre.y; 
	}
		
	Vecteur2 operator-(Vecteur2& vect) { 
		return Vecteur2(this->x - vect.x, this->y - vect.y); 
	}
		
	void operator-=(Vecteur2& autre) { 
		x -= autre.x; y -= autre.y; 
	}
		
	Vecteur2 operator*(float scalaire) { 
		return Vecteur2(this->x * scalaire, this->y * scalaire); 
	}
		
	void operator*=(Vecteur2& autre) { 
		x *= autre.x; y *= autre.y; 
	}
		
	bool operator==(Vecteur2& autre) { 
		return x == autre.x && y == autre.y; 
	}
		
	bool operator!=(Vecteur2 &autre) { 
		return !operator==(autre); 
	}

	float norme() { 
		return sqrt(x * x + y * y); 
	}

	void normalizer() { 
		float module = norme(); 
		this->x /= module; this->y /= module; 
	}
		
		
};
typedef Vector2<int> Vector2i;
typedef Vector2<unsigned int> Vector2ui;
typedef Vector2<float> Vector2f;
typedef Vector2<double> Vector2d;