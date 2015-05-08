#pragma once
#define MATHS_PI 3.141592654
#define M_E  2.7182818284590452353602874713526624977572470936999595749669676277240766303535475945713821785251664274
#include <algorithm>
#include <vector>
class Maths{
public:
	static double obtValeurMax(std::vector<double> &nombres){
		double maximum = nombres[0];
		for (auto i : nombres)
			maximum = std::max(maximum, i);
		return maximum;
	}

	static double obtValeurMin(std::vector<double> &nombres){
		double minimum = nombres[0];
		for (auto i : nombres)
			minimum = std::min(minimum, i);
		return minimum;
	}
	static double degreARadian(double degre){
		return ((degre * MATHS_PI) / 180);
	}

	static double radianADegre(double radian){
		return ((radian * 180) / MATHS_PI);
	}

	static bool memeCote(Vecteur3d point1, Vecteur3d point2, Vecteur3d droite1, Vecteur3d droite2) {

		Vecteur3d produit1 = (droite2 - droite1).produitVectoriel(point1 - droite1);
		Vecteur3d produit2 = (droite2 - droite1).produitVectoriel(point2 - droite1);
		if (produit1.produitScalaire(produit2) >= 0)
			return true;
		return false;
	}

	static double distanceEntreDeuxPoints(Vecteur3d point1, Vecteur3d point2) {
		return SDL_sqrt(SDL_pow((point2.x - point1.x), 2) + SDL_pow((point2.y - point1.y), 2) + SDL_pow((point2.z - point1.z), 2));
	}

	static Vecteur3d vecteurEntreDeuxPoints(Vecteur3d point1, Vecteur3d point2) {
		return Vecteur3d((point2.x - point1.x), (point2.y - point1.y), (point2.z - point1.z));
	}

	static bool pointDansFace(Vecteur3d p, Vecteur3d a, Vecteur3d b, Vecteur3d c) {
		if (memeCote(p, a, b, c) && memeCote(p, b, a, c) && memeCote(p, c, a, b))
			return true;
		else
			return false;
	}

	static bool pointDansFace1(Vecteur3d& point1, Vecteur3d& point2, Vecteur3d& point3, Vecteur3d& point, Vecteur3d normale) {

		Vecteur3d v0 = point3 - point1;
		Vecteur3d v1 = point2 - point1;
		Vecteur3d v2 = point - point1;

		Vecteur2d vect0;
		Vecteur2d vect1;
		Vecteur2d vect2;

		normale.normaliser();

		double x = fabs(normale.x);
		double y = fabs(normale.y);
		double z = fabs(normale.z);

		if (y >= x && y >= z) {

			vect0 = Vecteur2d(v0.x, v0.z);
			vect1 = Vecteur2d(v1.x, v1.z);
			vect2 = Vecteur2d(v2.x, v2.z);
		}
		if (z >= x && z >= y) {

			vect0 = Vecteur2d(v0.x, v0.y);
			vect1 = Vecteur2d(v1.x, v1.y);
			vect2 = Vecteur2d(v2.x, v2.y);
		}
		if (x >= y && x >= z) {

			vect0 = Vecteur2d(v0.y, v0.z);
			vect1 = Vecteur2d(v1.y, v1.z);
			vect2 = Vecteur2d(v2.y, v2.z);
		}

		double produit00 = vect0.produitScalaire(vect0);
		double produit01 = vect0.produitScalaire(vect1);
		double produit02 = vect0.produitScalaire(vect2);
		double produit11 = vect1.produitScalaire(vect1);
		double produit12 = vect1.produitScalaire(vect2);

		double invDenom = 1 / (produit00 * produit11 - produit01 * produit01);
		double u = (produit11 * produit02 - produit01 * produit12) * invDenom;
		double vv = (produit00 * produit12 - produit01 * produit02) * invDenom;
		double v = (produit00 * produit12 - produit12 * produit02) * invDenom;

		return ((u >= 0) && (vv >= 0) && (u + vv < 1)) || ((u >= 0) && (v >= 0) && (u + v < 1));

	}

};