#pragma once
#include "ObjetFixe.h"
#include "BoiteCollision.h"

class Remplisseur : public ObjetFixe {

public:

	Remplisseur(gfx::Modele3D* modele, double largeur, Vecteur3d position, int ID) : ObjetFixe(modele, ID, "Bois", position, { 0, 0, 0 }, false, false){

		double* vertices = modele->obtModele()->obtVertices();
		BoiteCollision<double> boite = BoiteCollision<double>(modele->obtModele()->obtBoiteDeCollision());

		int xmin = boite.obtXMin() + 0.5;
		int xautre;

		for (int i = 0; i < modele->obtModele()->obtNbrVertices(); ++i) {
			xautre = vertices[i * 3] + 0.5;
			if (xautre != xmin)
				vertices[i * 3] = (fabs(boite.obtXMin()) + largeur);

		}
	}

};