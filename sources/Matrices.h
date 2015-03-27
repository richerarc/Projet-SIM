
#pragma once
double EPSILON = 0.00001;
#include <math.h>
#include "Vecteur3.h"
template<typename T>
class Matrice3X3{
private:
	T matrice[9];
	T matriceTrans[9];
public:

	Matrice3X3(){
		identite();
	}

	Matrice3X3(const T mat[9]){
		defMatrice(mat);
	}

	Matrice3X3(T mat0, T mat1, T mat2, T mat3, T mat4, T mat5, T mat6, T mat7, T mat8){
		defMatrice(mat0, mat1, mat2, mat3, mat4, mat5, mat6, mat7, mat8);
	}

	~Matrice3X3(){}

	void defMatrice(const T mat[9]){
		matrice[0] = mat[0];
		matrice[1] = mat[1];
		matrice[2] = mat[2];
		matrice[3] = mat[3];
		matrice[4] = mat[4];
		matrice[5] = mat[5];
		matrice[6] = mat[6];
		matrice[7] = mat[7];
		matrice[8] = mat[8];
	}

	void defMatrice(T mat0, T mat1, T mat2, T mat3, T mat4, T mat5, T mat6, T mat7, T mat8){
		matrice[0] = mat0;
		matrice[1] = mat1;
		matrice[2] = mat2;
		matrice[3] = mat3;
		matrice[4] = mat4;
		matrice[5] = mat5;
		matrice[6] = mat6;
		matrice[7] = mat7;
		matrice[8] = mat8;
	}

	void defLigne(int noLigne, const T ligne[3]){
		matrice[noLigne] = ligne[0];
		matrice[noLigne + 3] = ligne[1];
		matrice[noLigne + 6] = ligne[2];
	}

	void defLigne(int noLigne, Vecteur3<T> vec){
		matrice[noLigne] = vec.x;
		matrice[noLigne + 3] = vec.y;
		matrice[noLigne + 6] = vec.z;
	}

	void defColone(int noCol, const T col[3]){
		matrice[noCol * 3] = col[0];
		matrice[noCol * 3 + 1] = col[1];
		matrice[noCol * 3 + 2] = col[2];
	}

	void defColone(int noCol, Vecteur3<T> vec){
		matrice[noCol * 3] = vec.x;
		matrice[noCol * 3 + 1] = vec.y;
		matrice[noCol * 3 + 2] = vec.z;
	}

	T* obtMatrice(){return matrice;}

	T* obtTranspose(){

		matriceTrans[0] = matrice[0];
		matriceTrans[1] = matrice[3];
		matriceTrans[2] = matrice[6];
		matriceTrans[3] = matrice[1];
		matriceTrans[4] = matrice[4];
		matriceTrans[5] = matrice[7];
		matriceTrans[6] = matrice[2];
		matriceTrans[7] = matrice[5];
		matriceTrans[8] = matrice[8];
		return matriceTrans;
	}

	bool inverser(){
		double determinant, determinantInv;
		T tmp[9];

		tmp[0] = matrice[4] * matrice[8] - matrice[5] * matrice[7];
		tmp[1] = matrice[2] * matrice[7] - matrice[1] * matrice[8];
		tmp[2] = matrice[1] * matrice[5] - matrice[2] * matrice[4];
		tmp[3] = matrice[5] * matrice[6] - matrice[3] * matrice[8];
		tmp[4] = matrice[0] * matrice[8] - matrice[2] * matrice[6];
		tmp[5] = matrice[2] * matrice[3] - matrice[0] * matrice[5];
		tmp[6] = matrice[3] * matrice[7] - matrice[4] * matrice[6];
		tmp[7] = matrice[1] * matrice[6] - matrice[0] * matrice[7];
		tmp[8] = matrice[0] * matrice[4] - matrice[1] * matrice[3];

		// Regarder si le determinant est 0
		determinant = matrice[0] * tmp[0] + matrice[1] * tmp[3] + matrice[2] * tmp[6];
		if (fabs(determinant) <= EPSILON){
			identite(); // imposible d'inverser on met l'identité
			return false;
		}

		determinantInv = 1.0f / determinant;
		matrice[0] = determinantInv * tmp[0];
		matrice[1] = determinantInv * tmp[1];
		matrice[2] = determinantInv * tmp[2];
		matrice[3] = determinantInv * tmp[3];
		matrice[4] = determinantInv * tmp[4];
		matrice[5] = determinantInv * tmp[5];
		matrice[6] = determinantInv * tmp[6];
		matrice[7] = determinantInv * tmp[7];
		matrice[8] = determinantInv * tmp[8];
		return true;
	}

	T& operator[](int index){
		return matrice[index];
	}

	void identite(){
		matrice[0] = matrice[4] = matrice[8] = 1.0f;
		matrice[1] = matrice[2] = matrice[3] = matrice[5] = matrice[6] = matrice[7] = 0.0f;
	}
};
typedef Matrice3X3<int> Matrice3X3i;
typedef Matrice3X3<unsigned int> Matrice3X3ui;
typedef Matrice3X3<float> Matrice3X3f;
typedef Matrice3X3<double> Matrice3X3d;

template<typename T>
class Matrice4X4
{
private:
	T matrice[16];
	T matriceTrans[16];

	void inversionAffine(){
		Matrice3X3<T> temp(matrice[0], matrice[1], matrice[2], matrice[4], matrice[5], matrice[6], matrice[8], matrice[9], matrice[10]);
		temp.inverser();
		matrice[0] = temp.obtMatrice()[0];
		matrice[1] = temp.obtMatrice()[1];
		matrice[2] = temp.obtMatrice()[2];
		matrice[4] = temp.obtMatrice()[3];
		matrice[5] = temp.obtMatrice()[4];
		matrice[6] = temp.obtMatrice()[5];
		matrice[8] = temp.obtMatrice()[6];
		matrice[9] = temp.obtMatrice()[7];
		matrice[10] = temp.obtMatrice()[8];
		double x = matrice[12];
		double y = matrice[13];
		double z = matrice[14];
		matrice[12] = -(temp.obtMatrice()[0] * x + temp.obtMatrice()[3] * y + temp.obtMatrice()[6] * z);
		matrice[13] = -(temp.obtMatrice()[1] * x + temp.obtMatrice()[4] * y + temp.obtMatrice()[7] * z);
		matrice[14] = -(temp.obtMatrice()[2] * x + temp.obtMatrice()[5] * y + temp.obtMatrice()[8] * z);
	}

	bool inversionGenerale(){

		double cofacteur0 = obtCofacteur(matrice[5], matrice[6], matrice[7], matrice[9], matrice[10], matrice[11], matrice[13], matrice[14], matrice[15]);
		double cofacteur1 = obtCofacteur(matrice[4], matrice[6], matrice[7], matrice[8], matrice[10], matrice[11], matrice[12], matrice[14], matrice[15]);
		double cofacteur2 = obtCofacteur(matrice[4], matrice[5], matrice[7], matrice[8], matrice[9], matrice[11], matrice[12], matrice[13], matrice[15]);
		double cofacteur3 = obtCofacteur(matrice[4], matrice[5], matrice[6], matrice[8], matrice[9], matrice[10], matrice[12], matrice[13], matrice[14]);

		double determinant = matrice[0] * cofacteur0 - matrice[1] * cofacteur1 + matrice[2] * cofacteur2 - matrice[3] * cofacteur3;
		if (fabs(determinant) <= EPSILON){
			identite();
			return false;
		}

		double cofacteur4 = obtCofacteur(matrice[1], matrice[2], matrice[3], matrice[9], matrice[10], matrice[11], matrice[13], matrice[14], matrice[15]);
		double cofacteur5 = obtCofacteur(matrice[0], matrice[2], matrice[3], matrice[8], matrice[10], matrice[11], matrice[12], matrice[14], matrice[15]);
		double cofacteur6 = obtCofacteur(matrice[0], matrice[1], matrice[3], matrice[8], matrice[9], matrice[11], matrice[12], matrice[13], matrice[15]);
		double cofacteur7 = obtCofacteur(matrice[0], matrice[1], matrice[2], matrice[8], matrice[9], matrice[10], matrice[12], matrice[13], matrice[14]);
		double cofacteur8 = obtCofacteur(matrice[1], matrice[2], matrice[3], matrice[5], matrice[6], matrice[7], matrice[13], matrice[14], matrice[15]);
		double cofacteur9 = obtCofacteur(matrice[0], matrice[2], matrice[3], matrice[4], matrice[6], matrice[7], matrice[12], matrice[14], matrice[15]);
		double cofacteur10 = obtCofacteur(matrice[0], matrice[1], matrice[3], matrice[4], matrice[5], matrice[7], matrice[12], matrice[13], matrice[15]);
		double cofacteur11 = obtCofacteur(matrice[0], matrice[1], matrice[2], matrice[4], matrice[5], matrice[6], matrice[12], matrice[13], matrice[14]);
		double cofacteur12 = obtCofacteur(matrice[1], matrice[2], matrice[3], matrice[5], matrice[6], matrice[7], matrice[9], matrice[10], matrice[11]);
		double cofacteur13 = obtCofacteur(matrice[0], matrice[2], matrice[3], matrice[4], matrice[6], matrice[7], matrice[8], matrice[10], matrice[11]);
		double cofacteur14 = obtCofacteur(matrice[0], matrice[1], matrice[3], matrice[4], matrice[5], matrice[7], matrice[8], matrice[9], matrice[11]);
		double cofacteur15 = obtCofacteur(matrice[0], matrice[1], matrice[2], matrice[4], matrice[5], matrice[6], matrice[8], matrice[9], matrice[10]);

		double determinantInv = 1.0f / determinant;
		matrice[0] = determinantInv * cofacteur0;
		matrice[1] = -determinantInv * cofacteur4;
		matrice[2] = determinantInv * cofacteur8;
		matrice[3] = -determinantInv * cofacteur12;

		matrice[4] = -determinantInv * cofacteur1;
		matrice[5] = determinantInv * cofacteur5;
		matrice[6] = -determinantInv * cofacteur9;
		matrice[7] = determinantInv * cofacteur13;

		matrice[8] = determinantInv * cofacteur2;
		matrice[9] = -determinantInv * cofacteur6;
		matrice[10] = determinantInv * cofacteur10;
		matrice[11] = -determinantInv * cofacteur14;

		matrice[12] = -determinantInv * cofacteur3;
		matrice[13] = determinantInv * cofacteur7;
		matrice[14] = -determinantInv * cofacteur11;
		matrice[15] = determinantInv * cofacteur15;
		return true;
	}

	T obtCofacteur(T m0, T m1, T m2, T m3, T m4, T m5, T m6, T m7, T m8){
		return m0 * (m4 * m8 - m5 * m7) - m1 * (m3 * m8 - m5 * m6) + m2 * (m3 * m7 - m4 * m6);
	}

public:

	Matrice4X4(){
		identite();
	}

	Matrice4X4(const T mat[16]){
		defMatrice(mat);
	}

	Matrice4X4(T mat0, T mat1, T mat2, T mat3, T mat4, T mat5, T mat6, T mat7, T mat8, T mat9, T mat10, T mat11, T mat12, T mat13, T mat14, T mat15){
		defMatrice(mat0, mat1, mat2, mat3, mat4, mat5, mat6, mat7, mat8, mat9, mat10, mat11, mat12, mat13, mat14, mat15);
	}

	~Matrice4X4(){}

	void defMatrice(const T mat[16]){
		matrice[0] = mat[0];
		matrice[1] = mat[1];
		matrice[2] = mat[2];
		matrice[3] = mat[3];
		matrice[4] = mat[4];
		matrice[5] = mat[5];
		matrice[6] = mat[6];
		matrice[7] = mat[7];
		matrice[8] = mat[8];
		matrice[9] = mat[9];
		matrice[10] = mat[10];
		matrice[11] = mat[11];
		matrice[12] = mat[12];
		matrice[13] = mat[13];
		matrice[14] = mat[14];
		matrice[15] = mat[15];
	}

	void defMatrice(T mat0, T mat1, T mat2, T mat3, T mat4, T mat5, T mat6, T mat7, T mat8, T mat9, T mat10, T mat11, T mat12, T mat13, T mat14, T mat15){
		matrice[0] = mat0;
		matrice[1] = mat1;
		matrice[2] = mat2;
		matrice[3] = mat3;
		matrice[4] = mat4;
		matrice[5] = mat5;
		matrice[6] = mat6;
		matrice[7] = mat7;
		matrice[8] = mat8;
		matrice[9] = mat9;
		matrice[10] = mat10;
		matrice[11] = mat11;
		matrice[12] = mat12;
		matrice[13] = mat13;
		matrice[14] = mat14;
		matrice[15] = mat15;
	}

	void defLigne(int noLigne, const T ligne[4]){
		matrice[noLigne] = ligne[0];
		matrice[noLigne + 4] = ligne[1];
		matrice[noLigne + 8] = ligne[2];
		matrice[noLigne + 12] = ligne[3];
	}

	void defLigne(int noLigne, Vecteur3<T> vec){
		matrice[noLigne] = vec.x;
		matrice[noLigne + 4] = vec.y;
		matrice[noLigne + 8] = vec.z;
	}

	void defColone(int noCol, const T col[4]){
		matrice[noCol * 4] = col[0];
		matrice[noCol * 4 + 1] = col[1];
		matrice[noCol * 4 + 2] = col[2];
		matrice[noCol * 4 + 3] = col[3];
	}

	void defColone(int noCol, Vecteur3<T> vec){
		matrice[noCol * 4] = vec.x;
		matrice[noCol * 4 + 1] = vec.y;
		matrice[noCol * 4 + 2] = vec.z;
	}

	T* obtTranspose(){
		matriceTrans[0] = matrice[0];
		matriceTrans[1] = matrice[4];
		matriceTrans[2] = matrice[8];
		matriceTrans[3] = matrice[12];
		matriceTrans[4] = matrice[1];
		matriceTrans[5] = matrice[5];
		matriceTrans[6] = matrice[9];
		matriceTrans[7] = matrice[13];
		matriceTrans[8] = matrice[2];
		matriceTrans[9] = matrice[6];
		matriceTrans[10] = matrice[10];
		matriceTrans[11] = matrice[14];
		matriceTrans[12] = matrice[3];
		matriceTrans[13] = matrice[7];
		matriceTrans[14] = matrice[11];
		matriceTrans[15] = matrice[15];
		return matriceTrans;
	}

	void transposer(){
		std::swap(matrice[1], matrice[3]);
		std::swap(matrice[2], matrice[6]);
		std::swap(matrice[5], matrice[7]);
	}

	void inverser(){

		if (matrice[3] == 0 && matrice[7] == 0 && matrice[11] == 0 && matrice[15] == 1)
			inversionAffine();
		else
			inversionGenerale();
	}

	T* obtMatrice(){ return matrice; }

	void identite(){
		matrice[0] = matrice[5] = matrice[10] = matrice[15] = 1.0f;
		matrice[1] = matrice[2] = matrice[3] = matrice[4] = matrice[6] = matrice[7] = matrice[8] = matrice[9] = matrice[11] = matrice[12] = matrice[13] = matrice[14] = 0.0f;
	}

	T operator[](int index){
		return matrice[index];
	}

};
typedef Matrice4X4<int> Matrice4X4i;
typedef Matrice4X4<unsigned int> Matrice4X4ui;
typedef Matrice4X4<float> Matrice4X4f;
typedef Matrice4X4<double> Matrice4X4d;