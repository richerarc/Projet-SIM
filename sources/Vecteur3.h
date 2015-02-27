#pragma once

template<typename T>
class Vecteur3{
public:
	T x, y, z;

	Vecteur3(T x = 0, T y = 0, T z = 0) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	T norme() {
		return sqrt((x * x) + (y * y) + (z * z));
	}
	
	void normalizer() {
		T norme = Norme();
		x /= norme;
		y /= norme;
		z /= norme;
	}

	void inverser() {
		x = -x;
		y = -y;
		z = -z;
	}
	
	void operator+=(Vecteur3<T>& autre) {
		x += autre.x;
		y += autre.y;
		z += autre.z;
	}
	
	void operator-=(Vector3<T>& autre) {
		x -= autre.x;
		y -= autre.y;
		z -= autre.z;
	}
	
	void operator*=(float scalaire) {
		x *= scalaire;
		y *= scalaire;
		z *= scalaire;
	}

	T produitScalaire(Vector3<T>& autre) {
		return ((this->x * autre.x) + (this->y * autre.y) + (this->.z * autre.z));
	}

	Vector3<T> produitVectoriel(Vector3<T>& autre) {
		Vector3<T> vectP;
		vectP.x = (this->y * autre.z) - (autre.z * this->y);
		vectP.y = (this->z * autre.x) - (autre.x * this->z);
		vectP.z = (this->x * autre.y) - (autre.x * this->y);
		return vectP;
	}
};

template<typename T>
Vector3<T> operator*(Vector3<T>& vect, float scalaire) {
	return Vector3<T>(vect.x * scalaire, vect.y * scalaire, vect.z * scalaire);
}

template<typename T>
Vector3<T> operator/(Vector3<T>& vect, float scalaire) {
	return Vector3<T>(vect.x / scalaire, vect.y / scalaire, vect.z / scalaire);
}
	
template<typename T>
Vector3<T> operator+(Vector3<T>& gauche, Vector3<T>& droite) {
	return Vecteur3<T>(gauche.x + droite.x, gauche.y + droite.y, gauche.z + droite.z);
}

template<typename T>
Vector3<T> operator-(Vector3<T>& gauche, Vector3<T>& droite) {
	return Vecteur3<T>(gauche.x - droite.x, gauche.y - droite.y, gauche.z - droite.z);
}

typedef Vector3<int> Vector3i;
typedef Vector3<unsigned int> Vector3ui;
typedef Vector3<float> Vector3f;
typedef Vector3<double> Vector3d;