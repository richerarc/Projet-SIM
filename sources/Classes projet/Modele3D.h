#pragma once
#include <vector>
#include <queue>
#include <fstream>
#include <iostream> 
#include "Matrices.h"
#include "Maths.h"
#include "Modele.h"
#include "Texture.h"
#include "Objet3D.h"

namespace gfx{
	class Modele3D : public Objet3D {
	private:
		Modele* modele;
		Texture* texture;
		Matrice4X4d matriceTransformation;
		Vecteur3d echelle;
		double* sommetsModif;
		double* normalesModif;
		Vecteur3d boiteDeCollisionModifiee[8];
		bool sommet_Est_Transforme;
		bool normale_Est_Transforme;
		bool bDC_Est_Transformee;

		std::vector<std::tuple<double, Vecteur3d>> rotations;

		void calculerMatriceTransformation(bool sommet){
			double mat[16];
			glPushMatrix();
			glLoadIdentity();
			glTranslated(position.x - origine.x, position.y - origine.y, position.z - origine.z);
			glRotated(orientation.x, 1, 0, 0);
			glRotated(orientation.y, 0, 1, 0);
			glRotated(orientation.z, 0, 0, 1);
			glTranslated(origine.x, origine.y, origine.z);
			if (sommet)
				glScaled(echelle.x, echelle.y, echelle.z);
			else
				glScaled(echelle.z, echelle.y, echelle.x);
			glGetDoublev(GL_MODELVIEW_MATRIX, mat);
			glPopMatrix();
			matriceTransformation.defMatrice(mat);
		}

	public:

		Modele3D() : Objet3D(){
			echelle = Vecteur3d(1, 1, 1);
			sommet_Est_Transforme = false;
			normale_Est_Transforme = false;
			bDC_Est_Transformee = false;
			sommetsModif = nullptr;
			normalesModif = nullptr;
			matriceTransformation = Matrice4X4d();
			echelle = Vecteur3d(1.3529411765, 1.3529411765, 1.3529411765);
		}

		Modele3D(Modele *modele, Texture *texture) : Objet3D(){
			this->modele = modele;
			this->texture = texture;
			echelle = Vecteur3d(1, 1, 1);
			sommetsModif = new double[modele->obtNbrVertices()];
			normalesModif = new double[modele->obtNbrVertices()];
			for (unsigned int i = 0; i < modele->obtNbrVertices(); i++){
				sommetsModif[i] = modele->obtVertices()[i];
				normalesModif[i] = modele->obtNormales()[i];
			}
			for (unsigned int i = 0; i < 8; i++)
				boiteDeCollisionModifiee[i] = modele->obtBoiteDeCollision()[i];
			sommet_Est_Transforme = false;
			normale_Est_Transforme = false;
			bDC_Est_Transformee = false;
			matriceTransformation = Matrice4X4d();
		}

		double* obtNormalesModifies(){
			if (normale_Est_Transforme)
			{
				calculerMatriceTransformation(false);
				matriceTransformation.inverser();
				matriceTransformation.transposer();
				double vecteurNormal[4];
				double normalTemp[4];
				normalTemp[3] = 1;
				for (unsigned int i = 0; i < modele->obtNbrVertices() / 3; i++)
				{
					for (unsigned int j = 0; j < 3; j++)
						normalTemp[j] = modele->obtNormales()[i * 3 + j];

					vecteurNormal[0] = (matriceTransformation[0] * normalTemp[0]) + (matriceTransformation[4] * normalTemp[1]) + (matriceTransformation[8] * normalTemp[2]) + (matriceTransformation[12] * normalTemp[3]);
					vecteurNormal[1] = (matriceTransformation[1] * normalTemp[0]) + (matriceTransformation[5] * normalTemp[1]) + (matriceTransformation[9] * normalTemp[2]) + (matriceTransformation[13] * normalTemp[3]);
					vecteurNormal[2] = (matriceTransformation[2] * normalTemp[0]) + (matriceTransformation[6] * normalTemp[1]) + (matriceTransformation[10] * normalTemp[2]) + (matriceTransformation[14] * normalTemp[3]);
					vecteurNormal[3] = (matriceTransformation[3] * normalTemp[0]) + (matriceTransformation[7] * normalTemp[1]) + (matriceTransformation[11] * normalTemp[2]) + (matriceTransformation[15] * normalTemp[3]);

					for (unsigned int j = 0; j < 3; j++){
						if (vecteurNormal[3] != 1)
							normalesModif[i * 3 + j] = vecteurNormal[j] / vecteurNormal[3];
						else
							normalesModif[i * 3 + j] = vecteurNormal[j];
					}
				}
				normale_Est_Transforme = false;
			}
			return normalesModif;
		}

		double* obtSommetsModifies(){
			if (sommet_Est_Transforme)
			{
				calculerMatriceTransformation(true);
				double vecteurNormal[4];
				double normalTemp[4];
				normalTemp[3] = 1;
				for (unsigned int i = 0; i < modele->obtNbrVertices() / 3; i++)
				{
					for (unsigned int j = 0; j < 3; j++)
						normalTemp[j] = modele->obtVertices()[i * 3 + j];

					vecteurNormal[0] = (matriceTransformation[0] * normalTemp[0]) + (matriceTransformation[4] * normalTemp[1]) + (matriceTransformation[8] * normalTemp[2]) + (matriceTransformation[12] * normalTemp[3]);
					vecteurNormal[1] = (matriceTransformation[1] * normalTemp[0]) + (matriceTransformation[5] * normalTemp[1]) + (matriceTransformation[9] * normalTemp[2]) + (matriceTransformation[13] * normalTemp[3]);
					vecteurNormal[2] = (matriceTransformation[2] * normalTemp[0]) + (matriceTransformation[6] * normalTemp[1]) + (matriceTransformation[10] * normalTemp[2]) + (matriceTransformation[14] * normalTemp[3]);
					vecteurNormal[3] = (matriceTransformation[3] * normalTemp[0]) + (matriceTransformation[7] * normalTemp[1]) + (matriceTransformation[11] * normalTemp[2]) + (matriceTransformation[15] * normalTemp[3]);

					for (unsigned int j = 0; j < 3; j++){
						if (vecteurNormal[3] != 1)
							sommetsModif[i * 3 + j] = vecteurNormal[j] / vecteurNormal[3];
						else
							sommetsModif[i * 3 + j] = vecteurNormal[j];
					}

				}
				sommet_Est_Transforme = false;
			}
			return sommetsModif;
		}

		Vecteur3d* obtBoiteDeCollisionModifiee(){
			if (bDC_Est_Transformee)
			{
				calculerMatriceTransformation(true);
				double bteCol[4];
				double bteColTemp[4];
				bteColTemp[3] = 1;
				for (int i = 0; i < 8; i++)
				{
					bteColTemp[0] = modele->obtBoiteDeCollision()[i].x;
					bteColTemp[1] = modele->obtBoiteDeCollision()[i].y;
					bteColTemp[2] = modele->obtBoiteDeCollision()[i].z;
					bteCol[0] = (matriceTransformation[0] * bteColTemp[0]) + (matriceTransformation[4] * bteColTemp[1]) + (matriceTransformation[8] * bteColTemp[2]) + (matriceTransformation[12] * bteColTemp[3]);
					bteCol[1] = (matriceTransformation[1] * bteColTemp[0]) + (matriceTransformation[5] * bteColTemp[1]) + (matriceTransformation[9] * bteColTemp[2]) + (matriceTransformation[13] * bteColTemp[3]);
					bteCol[2] = (matriceTransformation[2] * bteColTemp[0]) + (matriceTransformation[6] * bteColTemp[1]) + (matriceTransformation[10] * bteColTemp[2]) + (matriceTransformation[14] * bteColTemp[3]);
					bteCol[3] = (matriceTransformation[3] * bteColTemp[0]) + (matriceTransformation[7] * bteColTemp[1]) + (matriceTransformation[11] * bteColTemp[2]) + (matriceTransformation[15] * bteColTemp[3]);
					if (bteCol[3] != 1)
					{
						boiteDeCollisionModifiee[i].x = bteCol[0] / bteCol[3];
						boiteDeCollisionModifiee[i].y = bteCol[1] / bteCol[3];
						boiteDeCollisionModifiee[i].z = bteCol[2] / bteCol[3];
					}
					else
					{
						boiteDeCollisionModifiee[i].x = bteCol[0];
						boiteDeCollisionModifiee[i].y = bteCol[1];
						boiteDeCollisionModifiee[i].z = bteCol[2];
					}

				}
				bDC_Est_Transformee = false;
			}
			return boiteDeCollisionModifiee;
		}


		~Modele3D(){
			if (sommetsModif){
				delete[] sommetsModif;
				sommetsModif = nullptr;
			}
			if (normalesModif){
				delete[] normalesModif;
				normalesModif = nullptr;
			}
		}

		void defModele(Modele *modele){
			this->modele = modele;
			delete[] sommetsModif;
			sommetsModif = new double[modele->obtNbrVertices()];
			delete[] normalesModif;
			normalesModif = new double[modele->obtNbrVertices()];
			for (unsigned int i = 0; i < modele->obtNbrVertices(); i++){
				sommetsModif[i] = modele->obtVertices()[i];
				normalesModif[i] = modele->obtNormales()[i];
			}
			for (unsigned int i = 0; i < 8; i++)
				boiteDeCollisionModifiee[i] = modele->obtBoiteDeCollision()[i];
			sommet_Est_Transforme = false;
			normale_Est_Transforme = false;
			bDC_Est_Transformee = false;
		}

		void defTexture(Texture *texture){
			this->texture = texture;
		}

		void defEchelle(double echX, double echY, double echZ){
			echelle = Vecteur3d(echX, echY, echZ);
			sommet_Est_Transforme = true;
			normale_Est_Transforme = true;
			bDC_Est_Transformee = true;
		}

		Modele* obtModele(){
			return modele;
		}

		Texture* obtTexture(){
			return texture;
		}

		void defPosition(Vecteur3d pos){
			position = pos;
			sommet_Est_Transforme = true;
			bDC_Est_Transformee = true;
		}

		void defOrigine(Vecteur3d org){
			origine.x = -org.x;
			origine.y = -org.y;
			origine.z = -org.z;
		}

		void defOrientation(Vecteur3d ort){
			orientation = ort;
			sommet_Est_Transforme = true;
			normale_Est_Transforme = true;
			bDC_Est_Transformee = true;
			rotations.clear();
		}

		void rotationner(Vecteur3d rot){
			orientation += rot;
			sommet_Est_Transforme = true;
			normale_Est_Transforme = true;
			bDC_Est_Transformee = true;
		}

		void deplacer(Vecteur3d dep){
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
			origine.x = -axeX;
			origine.y = -axeY;
			origine.z = -axeZ;
		}

		void defOrientation(double axeX, double axeY, double axeZ){
			orientation.x = axeX;
			orientation.y = axeY;
			orientation.z = axeZ;
			sommet_Est_Transforme = true;
			normale_Est_Transforme = true;
			bDC_Est_Transformee = true;
			rotations.clear();
		}

		void rotationner(double axeX, double axeY, double axeZ){
			orientation.x += axeX;
			orientation.y += axeY;
			orientation.z += axeZ;
			sommet_Est_Transforme = true;
			normale_Est_Transforme = true;
			bDC_Est_Transformee = true;
		}

		void rotationner(Vecteur3d axe, double angle){
			sommet_Est_Transforme = true;
			normale_Est_Transforme = true;
			bDC_Est_Transformee = true;

			rotations.push_back(std::make_tuple(angle, axe));

		}

		void deplacer(double axeX, double axeY, double axeZ){
			position.x += axeX;
			position.y += axeY;
			position.z += axeZ;
			sommet_Est_Transforme = true;
			bDC_Est_Transformee = true;
		}

		void afficher(){
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glEnable(GL_DEPTH_TEST);
			glBindTexture(GL_TEXTURE_2D, texture->obtID());
			glPushMatrix();
			//glLoadIdentity();
			glTranslated(position.x - origine.x, position.y - origine.y, position.z - origine.z);
			for (auto &it : rotations){
				Vecteur3d axe = std::get<1>(it);
				glRotated(std::get<0>(it), axe.x, axe.y, axe.z);
			}
			glRotated(orientation.x, 1, 0, 0);
			glRotated(orientation.z, 0, 0, 1);
			glRotated(orientation.y, 0, 1, 0);
			glTranslated(origine.x, origine.y, origine.z);
			glScaled(echelle.x, echelle.y, echelle.z);
			glVertexPointer(3, GL_DOUBLE, 0, modele->obtVertices());
			glTexCoordPointer(2, GL_DOUBLE, 0, modele->obtTextures());
			glNormalPointer(GL_DOUBLE, 0, modele->obtNormales());
			glDrawArrays(GL_TRIANGLES, 0, modele->obtNbrSommets());
			glPopMatrix();
			glDisable(GL_DEPTH_TEST);
			//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

	};
}
