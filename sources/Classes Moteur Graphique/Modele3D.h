#pragma once

#include <vector>
#include <queue>
#include <fstream>
#include <iostream>
#include <SDL2/SDL_opengl.h>
#include "Vecteur3.h"
#include "Maths.h"
#include "Modele.h"
#include "Texture.h"
#include "Objet3D.h"


/*
A tester pour les tableaux transformés
*/
namespace gfx{
	class Modele3D : public Objet3D {
	private:
		Modele modele;
		Texture texture;
		double matTrans[16];
		Vecteur3d echelle;

		double* sommetsModif;
		double* normalesModif;
		Vecteur3d boiteDeCollisionModifiee[8];

		bool sommet_Est_Transforme;
		bool normale_Est_Transformee;
		bool bDC_Est_Transformee;

		void calculerMatriceTransformation(){
			glPushMatrix();
			glLoadIdentity();
			glTranslated(position.x - origine.x, position.y - origine.y, position.z - origine.z);
			glRotated(orientation.x, 1, 0, 0);
			glRotated(orientation.y, 0, 1, 0);
			glRotated(orientation.z, 0, 0, 1);
			glTranslated(origine.x, origine.y, origine.z);
			glScaled(echelle.x, echelle.y, echelle.z);
			glGetDoublev(GL_MODELVIEW_MATRIX, matTrans);
			glPopMatrix();
		}

	public:

		Modele3D(){
			echelle = Vecteur3d(1, 1, 1);
			sommet_Est_Transforme = false;
			normale_Est_Transformee = false;
			bDC_Est_Transformee = false;
		}

		Modele3D(Modele &modele, Texture &texture) : Objet3D(){
			this->modele = modele;
			this->texture = texture;
			echelle = Vecteur3d(1, 1, 1);
			sommetsModif = new double[modele.obtNbrVertices()];
			normalesModif = new double[modele.obtNbrVertices()];
			sommet_Est_Transforme = false;
			normale_Est_Transformee = false;
			bDC_Est_Transformee = false;
		}

		double* obtSommetsModifies(){
			if (sommet_Est_Transforme)
			{
				calculerMatriceTransformation();
				double vecteurSommet[4];
				double somTemp[4];
				somTemp[3] = 1;
				for (unsigned int i = 0; i < modele.obtNbrVertices() / 3; i++)
				{
					vecteurSommet[3] = 1;
					for (unsigned int j = 0; j < 3; j++)
						somTemp[j] = modele.obtVertices()[i * 3 + j];

					vecteurSommet[0] =(matTrans[0] * somTemp[0]) + (matTrans[4] * somTemp[1]) + (matTrans[8] * somTemp[2]) + (matTrans[12] * somTemp[3]);
					vecteurSommet[1] =(matTrans[1] * somTemp[0]) + (matTrans[5] * somTemp[1]) + (matTrans[9] * somTemp[2]) + (matTrans[13] * somTemp[3]);
					vecteurSommet[2] =(matTrans[2] * somTemp[0]) + (matTrans[6] * somTemp[1]) + (matTrans[10] * somTemp[2]) + (matTrans[14] * somTemp[3]);
					vecteurSommet[3] =(matTrans[3] * somTemp[0]) + (matTrans[7] * somTemp[1]) + (matTrans[11] * somTemp[2]) + (matTrans[15] * somTemp[3]);

					for (unsigned int j = 0; j < 3; j++)
						sommetsModif[i * 3 + j] = vecteurSommet[j] / vecteurSommet[3];
				}
				sommet_Est_Transforme = false;
			}
			return sommetsModif;
		}

		Vecteur3d* obtBoiteDeCollisionModifiee(){
			if (bDC_Est_Transformee)
			{
				calculerMatriceTransformation();
				double bteCol[4];
				double bteColTemp[4];
				for (int i = 0; i < 8; i++)
				{
					bteColTemp[0] = modele.obtBoiteDeCollision()[i].x;
					bteColTemp[1] = modele.obtBoiteDeCollision()[i].y;
					bteColTemp[2] = modele.obtBoiteDeCollision()[i].z;
					bteColTemp[3] = 1;
					bteCol[0] = (matTrans[0] * bteColTemp[0]) + (matTrans[4] * bteColTemp[1]) + (matTrans[8] * bteColTemp[2]) + (matTrans[12] * bteColTemp[3]);
					bteCol[1] = (matTrans[1] * bteColTemp[0]) + (matTrans[5] * bteColTemp[1]) + (matTrans[9] * bteColTemp[2]) + (matTrans[13] * bteColTemp[3]);
					bteCol[2] = (matTrans[2] * bteColTemp[0]) + (matTrans[6] * bteColTemp[1]) + (matTrans[10] * bteColTemp[2]) + (matTrans[14] * bteColTemp[3]);
					bteCol[3] = (matTrans[3] * bteColTemp[0]) + (matTrans[7] * bteColTemp[1]) + (matTrans[11] * bteColTemp[2]) + (matTrans[15] * bteColTemp[3]);

					boiteDeCollisionModifiee[i].x = bteCol[0] / bteCol[3];
					boiteDeCollisionModifiee[i].y = bteCol[1] / bteCol[3];
					boiteDeCollisionModifiee[i].z = bteCol[2] / bteCol[3];
				}
				bDC_Est_Transformee = false;
			}
			return boiteDeCollisionModifiee;
		}

		~Modele3D(){}

		void defModele(Modele &modele){
			this->modele = modele;
			sommetsModif = new double[modele.obtNbrVertices()];
			normalesModif = new double[modele.obtNbrVertices()];
		}

		void defTexture(Texture &texture){
			this->texture = texture;
		}

		void defEchelle(double echX, double echY, double echZ){
			echelle = Vecteur3d(echX, echY, echZ);
			sommet_Est_Transforme = true;
			bDC_Est_Transformee = true;
		}

		Modele& obtModele(){
			return modele;
		}

		Texture obtTexture(){
			return texture;
		}

		void defPosition(Vecteur3d &pos){
			position = pos;
			sommet_Est_Transforme = true;
			bDC_Est_Transformee = true;
		}

		void defOrigine(Vecteur3d &org){
			origine = org;
		}

		void defOrientation(Vecteur3d &ort){
			orientation = ort;
			sommet_Est_Transforme = true;
			normale_Est_Transformee = true;
			bDC_Est_Transformee = true;
		}

		void rotationner(Vecteur3d &rot){
			orientation += rot;
			sommet_Est_Transforme = true;
			normale_Est_Transformee = true;
			bDC_Est_Transformee = true;
		}

		void deplacer(Vecteur3d &dep){
			position += dep;
			sommet_Est_Transforme = true;
			bDC_Est_Transformee = true;
		}

		void defPosition(double axeX, double axeY, double axeZ){
			position.x = axeX;
			position.y = axeY;
			position.z = axeZ;
			sommet_Est_Transforme = true;
			bDC_Est_Transformee = true;
		}

		void defOrigine(double axeX, double axeY, double axeZ){
			origine.x = axeX;
			origine.y = axeY;
			origine.z = axeZ;
		}

		void defOrientation(double axeX, double axeY, double axeZ){
			orientation.x = axeX;
			orientation.y = axeY;
			orientation.z = axeZ;
			sommet_Est_Transforme = true;
			normale_Est_Transformee = true;
			bDC_Est_Transformee = true;
		}

		void rotationner(double axeX, double axeY, double axeZ){
			orientation.x += axeX;
			orientation.y += axeY;
			orientation.z += axeZ;
			sommet_Est_Transforme = true;
			normale_Est_Transformee = true;
			bDC_Est_Transformee = true;
		}

		void deplacer(double axeX, double axeY, double axeZ){
			position.x += axeX;
			position.y += axeY;
			position.z += axeZ;
			sommet_Est_Transforme = true;
			bDC_Est_Transformee = true;
		}

		void afficher(){
			glBindTexture(GL_TEXTURE_2D, texture.obtID());
			glPushMatrix();
			glLoadIdentity();
			glTranslated(position.x - origine.x, position.y - origine.y, position.z - origine.z);
			glRotated(orientation.x, 1, 0, 0);
			glRotated(orientation.y, 0, 1, 0);
			glRotated(orientation.z, 0, 0, 1);
			glTranslated(origine.x, origine.y, origine.z);
			glScaled(echelle.x, echelle.y, echelle.z);
			glVertexPointer(3, GL_DOUBLE, 0, modele.obtVertices());
			glTexCoordPointer(2, GL_DOUBLE, 0, modele.obtTextures());
			glNormalPointer(GL_DOUBLE, 0, modele.obtNormales());
			glDrawArrays(GL_TRIANGLES, 0, modele.obtNbrSommets());
			glPopMatrix();
		}

		void rafraichir() {}
	};
}
