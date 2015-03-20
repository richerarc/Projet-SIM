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

namespace gfx{
	class Modele3D : public Objet3D {
	private:
		Modele modele;
		Texture texture;
		float matTrans[16];
		Vecteur3f echelle;
		Vecteur3f boiteDeCollision[8];//ToDo
		bool Transformee; //Todo
		
		void calculerMatriceTransformation(){
			glPushMatrix();
				glLoadIdentity();
				glTranslatef(position.x - origine.x, position.y - origine.y, position.z - origine.z);
				glRotatef(orientation.x, 1, 0, 0);
				glRotatef(orientation.y, 0, 1, 0);
				glRotatef(orientation.z, 0, 0, 1);
				glTranslatef(origine.x, origine.y, origine.z);
				glScalef(echelle.x, echelle.y, echelle.z);
				glGetFloatv(GL_MODELVIEW_MATRIX, matTrans);
			glPopMatrix();
		}

		//ToDo
		void calculerBoiteDeCollision(){
			std::vector<float> tmpX;
			std::vector<float> tmpY;
			std::vector<float> tmpZ;
			float xmax, xmin, ymax, ymin, zmax, zmin;
			for (int i = 0; i < modele.obtNbrFaces(); ++i){
				tmpX.push_back(modele.obtVertices()[i * 3]);
				tmpY.push_back(modele.obtVertices()[i * 3 + 1]);
				tmpZ.push_back(modele.obtVertices()[i * 3 + 2]);
			}
			xmax = Maths::obtValeurMax(tmpX);
			xmin = Maths::obtValeurMin(tmpX);
			ymax = Maths::obtValeurMax(tmpY);
			ymin = Maths::obtValeurMin(tmpY);
			zmax = Maths::obtValeurMax(tmpZ);
			zmin = Maths::obtValeurMin(tmpZ);
			boiteDeCollision[0] = Vecteur3f(xmin, ymin, zmax);
			boiteDeCollision[1] = Vecteur3f(xmin, ymax, zmax);
			boiteDeCollision[2] = Vecteur3f(xmax, ymax, zmax);
			boiteDeCollision[3] = Vecteur3f(xmax, ymin, zmax);
			boiteDeCollision[4] = Vecteur3f(xmin, ymin, zmin);
			boiteDeCollision[5] = Vecteur3f(xmin, ymax, zmin);
			boiteDeCollision[6] = Vecteur3f(xmax, ymax, zmin);
			boiteDeCollision[7] = Vecteur3f(xmax, ymin, zmin);
		}

	public:

		Modele3D(){
			echelle = Vecteur3f(1, 1, 1);
		}

		Modele3D(Modele &modele, Texture &texture) : Objet3D(){
			this->modele = modele;
			this->texture = texture;
			echelle = Vecteur3f(1, 1, 1);
			calculerBoiteDeCollision();
		}

		//ToDo
		Vecteur3f* obtBoiteDeCollision(){
			calculerMatriceTransformation();
			float col[4];
			float colTemp[4];

			for (unsigned int i = 0; i < 8; i++)
			{
				colTemp[0] = boiteDeCollision[i].x;
				colTemp[1] = boiteDeCollision[i].y;
				colTemp[2] = boiteDeCollision[i].z;
				colTemp[3] = 1;

				col[0] = (double)(matTrans[0] * colTemp[0]) + (double)(matTrans[4] * colTemp[1]) + (double)(matTrans[8] * colTemp[2]) + (double)(matTrans[12] * colTemp[3]);
				col[1] = (double)(matTrans[1] * colTemp[0]) + (double)(matTrans[5] * colTemp[1]) + (double)(matTrans[9] * colTemp[2]) + (double)(matTrans[13] * colTemp[3]);
				col[2] = (double)(matTrans[2] * colTemp[0]) + (double)(matTrans[6] * colTemp[1]) + (double)(matTrans[10] * colTemp[2]) + (double)(matTrans[14] * colTemp[3]);
				col[3] = (double)(matTrans[3] * colTemp[0]) + (double)(matTrans[7] * colTemp[1]) + (double)(matTrans[11] * colTemp[2]) + (double)(matTrans[15] * colTemp[3]);

				boiteDeCollision[i].x = col[0] / col[3];
				boiteDeCollision[i].y = col[1] / col[3];
				boiteDeCollision[i].z = col[2] / col[3];
			}
			return nullptr;
		}

		float* obtommetsModifies(){
			calculerMatriceTransformation();
			float* sommets = new float[modele.obtNbrVertices()];
			float som[4];
			float somTemp[4];
			for (unsigned int i = 0; i < modele.obtNbrVertices() / 3; i++)
			{
				som[3] = 1;
				for (unsigned int j = 0; j < 3; j++)
					somTemp[j] = modele.obtVertices()[i * 3 + j];

				som[0] = (double)(matTrans[0] * somTemp[0]) + (double)(matTrans[4] * somTemp[1]) + (double)(matTrans[8] * somTemp[2]) + (double)(matTrans[12] * somTemp[3]);
				som[1] = (double)(matTrans[1] * somTemp[0]) + (double)(matTrans[5] * somTemp[1]) + (double)(matTrans[9] * somTemp[2]) + (double)(matTrans[13] * somTemp[3]);
				som[2] = (double)(matTrans[2] * somTemp[0]) + (double)(matTrans[6] * somTemp[1]) + (double)(matTrans[10] * somTemp[2]) + (double)(matTrans[14] * somTemp[3]);
				som[3] = (double)(matTrans[3] * somTemp[0]) + (double)(matTrans[7] * somTemp[1]) + (double)(matTrans[11] * somTemp[2]) + (double)(matTrans[15] * somTemp[3]);
				
				for (unsigned int j = 0; j < 3; j++)
					sommets[i * 3 + j] = som[j] / som[3];
				//sommets[i * 3 + 0] = som[0] / som[3];
				//sommets[i * 3 + 1] = som[1] / som[3];
				//sommets[i * 3 + 2] = som[2] / som[3];
			}
			return sommets;
		}


		~Modele3D(){}

		void defModele(Modele &modele){
			this->modele = modele;
			calculerBoiteDeCollision()
		}

		void defTexture(Texture &texture){
			this->texture = texture;
		}

		void defEchelle(float echX, float echY, float echZ){
			echelle = Vecteur3f(echX, echY, echZ);
		}

		Modele obtModele(){
			return modele;
		}

		Texture obtTexture(){
			return texture;
		}

		void defPosition(Vecteur3f &pos){
			position = pos;
		}

		void defOrigine(Vecteur3f &org){
			origine = org;
		}

		void defOrientation(Vecteur3f &ort){
			orientation = ort;
		}

		void rotationner(Vecteur3f &rot){
			orientation += rot;
		}

		void deplacer(Vecteur3f &dep){
			position += dep;
		}

		void defPosition(float axeX, float axeY, float axeZ){
			position.x = axeX;
			position.y = axeY;
			position.z = axeZ;
		}

		void defOrigine(float axeX, float axeY, float axeZ){
			origine.x = axeX;
			origine.y = axeY;
			origine.z = axeZ;
		}

		void defOrientation(float axeX, float axeY, float axeZ){
			orientation.x = axeX;
			orientation.y = axeY;
			orientation.z = axeZ;
		}

		void rotationner(float axeX, float axeY, float axeZ){
			orientation.x += axeX;
			orientation.y += axeY;
			orientation.z += axeZ;
		}

		void deplacer(float axeX, float axeY, float axeZ){
			position.x += axeX;
			position.y += axeY;
			position.z += axeZ;
		}

		void afficher(){
			glBindTexture(GL_TEXTURE_2D, texture.obtID());
			glPushMatrix();
				glLoadIdentity();
				glTranslatef(position.x - origine.x, position.y - origine.y, position.z - origine.z);
				glRotatef(orientation.x, 1, 0, 0);
				glRotatef(orientation.y, 0, 1, 0);
				glRotatef(orientation.z, 0, 0, 1);
				glTranslatef(origine.x, origine.y, origine.z);
				glScalef(echelle.x, echelle.y, echelle.z);
				glVertexPointer(3, GL_FLOAT, 0, modele.obtVertices());
				glTexCoordPointer(2, GL_FLOAT, 0, modele.obtTextures());
				glNormalPointer(GL_FLOAT, 0, modele.obtNormales());
				glDrawArrays(GL_TRIANGLES, 0, modele.obtNbrFaces());
			glPopMatrix();
		}

	};
}