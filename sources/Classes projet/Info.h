#pragma once
#include "BoiteCollision.h"

enum objet_type{PORTE, PENDULE, FIXE, PHYSIQUE, ITEM, REMPLISSEUR, VENTILATEUR, COMMUTATEUR};
enum position_type{MURS = 101, SOLS=102, PLAFONDS=103, MURS_SOLS=104, MURS_PLAFONDS=105};

struct InfoObjet {
	unsigned int ID;
	Vecteur3d position;
	Vecteur3d direction;
	double rotation;
	char* cheminModele;
	char* cheminTexture;
	int type;
	double largeur;
	int IDitem;
	position_type positionement;
};


struct InfoPuzzle{
	std::list<InfoObjet> objet;
	BoiteCollision<double> boiteCollision;
	Vecteur3d position;
	bool entrees[4];
	double rotation;

	BoiteCollision<double> obtBoiteCollisionModifie(){
		double mat[16];
		BoiteCollision<double> boiteDeCollisionModifiee;
		glPushMatrix();
		glLoadIdentity();
		glTranslated(position.x, position.y, position.z);
		glRotated(rotation, 0, 1, 0);
		glGetDoublev(GL_MODELVIEW_MATRIX, mat);
		glPopMatrix();
		double bteCol[4];
		double bteColTemp[4];
		bteColTemp[3] = 1;
		for (int i = 0; i < 8; i++){
			bteColTemp[0] = boiteCollision.obtBoite()[i].x;
			bteColTemp[1] = boiteCollision.obtBoite()[i].y;
			bteColTemp[2] = boiteCollision.obtBoite()[i].z;
			bteCol[0] = (mat[0] * bteColTemp[0]) + (mat[4] * bteColTemp[1]) + (mat[8] * bteColTemp[2]) + (mat[12] * bteColTemp[3]);
			bteCol[1] = (mat[1] * bteColTemp[0]) + (mat[5] * bteColTemp[1]) + (mat[9] * bteColTemp[2]) + (mat[13] * bteColTemp[3]);
			bteCol[2] = (mat[2] * bteColTemp[0]) + (mat[6] * bteColTemp[1]) + (mat[10] * bteColTemp[2]) + (mat[14] * bteColTemp[3]);
			bteCol[3] = (mat[3] * bteColTemp[0]) + (mat[7] * bteColTemp[1]) + (mat[11] * bteColTemp[2]) + (mat[15] * bteColTemp[3]);
			if (bteCol[3] != 1){
				boiteDeCollisionModifiee.obtBoite()[i].x = bteCol[0] / bteCol[3];
				boiteDeCollisionModifiee.obtBoite()[i].y = bteCol[1] / bteCol[3];
				boiteDeCollisionModifiee.obtBoite()[i].z = bteCol[2] / bteCol[3];
			}
			else{
				boiteDeCollisionModifiee.obtBoite()[i].x = bteCol[0];
				boiteDeCollisionModifiee.obtBoite()[i].y = bteCol[1];
				boiteDeCollisionModifiee.obtBoite()[i].z = bteCol[2];
			}

		}
		return boiteDeCollisionModifiee;
	}
};

struct InfoSalle {
	unsigned int ID;
	unsigned int nbrPorte;
	Vecteur3d echelle;
	char* cheminModele;
	char* cheminTexture;
	InfoPuzzle puzzle;
	std::list<InfoObjet> Objet;
	std::list<BoiteCollision<double>> boitesCollision;
	
	BoiteCollision<double> obtBoiteCollisionModifie(int ID){
		/*double mat[16];
		BoiteCollision<double> boiteDeCollisionModifiee;
		glPushMatrix();
		glLoadIdentity();
		glScaled(echelle.x, echelle.y, echelle.z);
		glGetDoublev(GL_MODELVIEW_MATRIX, mat);
		glPopMatrix();*/
		auto it = boitesCollision.begin();
		for (int i = 0; i < ID; ++i) ++it;
		
		/*double bteCol[4];
		double bteColTemp[4];
		bteColTemp[3] = 1;
		for (int i = 0; i < 8; i++){
			bteColTemp[0] = (*it).obtBoite()[i].x;
			bteColTemp[1] = (*it).obtBoite()[i].y;
			bteColTemp[2] = (*it).obtBoite()[i].z;
			bteCol[0] = (mat[0] * bteColTemp[0]) + (mat[4] * bteColTemp[1]) + (mat[8] * bteColTemp[2]) + (mat[12] * bteColTemp[3]);
			bteCol[1] = (mat[1] * bteColTemp[0]) + (mat[5] * bteColTemp[1]) + (mat[9] * bteColTemp[2]) + (mat[13] * bteColTemp[3]);
			bteCol[2] = (mat[2] * bteColTemp[0]) + (mat[6] * bteColTemp[1]) + (mat[10] * bteColTemp[2]) + (mat[14] * bteColTemp[3]);
			bteCol[3] = (mat[3] * bteColTemp[0]) + (mat[7] * bteColTemp[1]) + (mat[11] * bteColTemp[2]) + (mat[15] * bteColTemp[3]);
			if (bteCol[3] != 1){
				boiteDeCollisionModifiee.obtBoite()[i].x = bteCol[0] / bteCol[3];
				boiteDeCollisionModifiee.obtBoite()[i].y = bteCol[1] / bteCol[3];
				boiteDeCollisionModifiee.obtBoite()[i].z = bteCol[2] / bteCol[3];
			}
			else{
				boiteDeCollisionModifiee.obtBoite()[i].x = bteCol[0];
				boiteDeCollisionModifiee.obtBoite()[i].y = bteCol[1];
				boiteDeCollisionModifiee.obtBoite()[i].z = bteCol[2];
			}
			
		}*/
		return *it;
	}
};