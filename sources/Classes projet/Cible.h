#pragma once
#include "Vecteur3.h"
#include <math.h>
#include "Info.h"
#include "Maths.h"
#include "Porte.h"

class Cible {

private:
	unsigned int force;
	BoiteCollision<double> boitePoignee;
public:
	Cible(unsigned int force, InfoObjet& porte){
		/* ***VERSION 1***
		this->force = force;
		double mat[4];
		mat[0] = cos(Maths::degreARadian(porte.rotation));
		mat[1] = -sin(Maths::degreARadian(porte.rotation));
		mat[2] = sin(Maths::degreARadian(porte.rotation));
		mat[3] = cos(Maths::degreARadian(porte.rotation));

		Vecteur3d tabVecteur[8];
		tabVecteur[0] = Vecteur3d(0.15 + porte.position.x, 1.52201 + porte.position.y, -1.04883 + porte.position.z);
		tabVecteur[1] = Vecteur3d(0.15 + porte.position.x, 1.44648 + porte.position.y, -1.04883 + porte.position.z);
		tabVecteur[2] = Vecteur3d(0.15 + porte.position.x, 1.52201 + porte.position.y, -1.28284 + porte.position.z);
		tabVecteur[3] = Vecteur3d(0.15 + porte.position.x, 1.44648 + porte.position.y, -1.28284 + porte.position.z);
		tabVecteur[4] = Vecteur3d(0.05941 + porte.position.x, 1.52201 + porte.position.y, -1.04883 + porte.position.z);
		tabVecteur[5] = Vecteur3d(0.05941 + porte.position.x, 1.44648 + porte.position.y, -1.04883 + porte.position.z);
		tabVecteur[6] = Vecteur3d(0.05941 + porte.position.x, 1.52201 + porte.position.y, -1.28284 + porte.position.z);
		tabVecteur[7] = Vecteur3d(0.05941 + porte.position.x, 1.44648 + porte.position.y, -1.28284 + porte.position.z);
		for (int i = 0; i < 8; ++i) {
			tabVecteur[i].x = tabVecteur[i].x * mat[0] + tabVecteur[i].z * mat[1];
			tabVecteur[i].z = tabVecteur[i].x * mat[2] + tabVecteur[i].z * mat[3];
		}

		boitePoignee = (BoiteCollision<double>(tabVecteur));*/


		double mat[16];
		glPushMatrix();
		glLoadIdentity();
		glRotated(Maths::degreARadian(porte.rotation), 0, 1, 0);
		glGetDoublev(GL_MODELVIEW_MATRIX, mat);
		glPopMatrix();

		Vecteur3d tabVecteur[8];
		tabVecteur[0] = Vecteur3d(0.15 + porte.position.x, 1.52201 + porte.position.y, -1.04883 + porte.position.z);
		tabVecteur[1] = Vecteur3d(0.15 + porte.position.x, 1.44648 + porte.position.y, -1.04883 + porte.position.z);
		tabVecteur[2] = Vecteur3d(0.15 + porte.position.x, 1.52201 + porte.position.y, -1.28284 + porte.position.z);
		tabVecteur[3] = Vecteur3d(0.15 + porte.position.x, 1.44648 + porte.position.y, -1.28284 + porte.position.z);
		tabVecteur[4] = Vecteur3d(0.05941 + porte.position.x, 1.52201 + porte.position.y, -1.04883 + porte.position.z);
		tabVecteur[5] = Vecteur3d(0.05941 + porte.position.x, 1.44648 + porte.position.y, -1.04883 + porte.position.z);
		tabVecteur[6] = Vecteur3d(0.05941 + porte.position.x, 1.52201 + porte.position.y, -1.28284 + porte.position.z);
		tabVecteur[7] = Vecteur3d(0.05941 + porte.position.x, 1.44648 + porte.position.y, -1.28284 + porte.position.z);

		for (int i = 0; i < 8; ++i) {

			double vecteurNormal[4];
			double normalTemp[4];
			normalTemp[3] = 1;
			normalTemp[0] = tabVecteur[i].x;
			normalTemp[1] = tabVecteur[i].y;
			normalTemp[2] = tabVecteur[i].z;

			vecteurNormal[0] = (mat[0] * normalTemp[0]) + (mat[4] * normalTemp[1]) + (mat[8] * normalTemp[2]) + (mat[12] * normalTemp[3]);
			vecteurNormal[1] = (mat[1] * normalTemp[0]) + (mat[5] * normalTemp[1]) + (mat[9] * normalTemp[2]) + (mat[13] * normalTemp[3]);
			vecteurNormal[2] = (mat[2] * normalTemp[0]) + (mat[6] * normalTemp[1]) + (mat[10] * normalTemp[2]) + (mat[14] * normalTemp[3]);
			vecteurNormal[3] = (mat[3] * normalTemp[0]) + (mat[7] * normalTemp[1]) + (mat[11] * normalTemp[2]) + (mat[15] * normalTemp[3]);

			tabVecteur[i].x = tabVecteur[i].x + (tabVecteur[i].x + (vecteurNormal[0] / vecteurNormal[3]));
			tabVecteur[i].y = tabVecteur[i].y + (tabVecteur[i].y + (vecteurNormal[1] / vecteurNormal[3]));
			tabVecteur[i].z = tabVecteur[i].z + (tabVecteur[i].z + (vecteurNormal[2] / vecteurNormal[3]));



		}
		boitePoignee = (BoiteCollision<double>(tabVecteur));
	}
	void defForce(unsigned int force) {
		this->force = force;
	}

	unsigned int obtForce(void) {
		return force;
	}

	BoiteCollision<double> obtBoiteCollision(void) {
		return boitePoignee;
	}

};