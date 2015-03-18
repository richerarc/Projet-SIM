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
		Vecteur3f boiteDeCollision[8];
		Vecteur3f echelle;
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
			boiteDeCollision[0] = Vecteur3f(xmax, ymax, zmax);
			boiteDeCollision[1] = Vecteur3f(xmax, ymax, zmin);
			boiteDeCollision[2] = Vecteur3f(xmax, ymin, zmax);
			boiteDeCollision[3] = Vecteur3f(xmax, ymin, zmin);
			boiteDeCollision[4] = Vecteur3f(xmin, ymax, zmax);
			boiteDeCollision[5] = Vecteur3f(xmin, ymax, zmin);
			boiteDeCollision[6] = Vecteur3f(xmin, ymin, zmax);
			boiteDeCollision[7] = Vecteur3f(xmin, ymin, zmin);
		}

		void RotationBoiteCollision(){
			float cosx = cos(Maths::degreARadian(obtOrientation().x));
			float sinx = sin(Maths::degreARadian(obtOrientation().x));
			float cosy = cos(Maths::degreARadian(obtOrientation().y));
			float siny = sin(Maths::degreARadian(obtOrientation().y));
			float cosz = cos(Maths::degreARadian(obtOrientation().z));
			float sinz = sin(Maths::degreARadian(obtOrientation().z));

			for (int i = 0; i < 8; i++){
				boiteDeCollision[i].y = (boiteDeCollision[i].y * cosx - boiteDeCollision[i].z * sinx);
				boiteDeCollision[i].z = (boiteDeCollision[i].z * cosx + boiteDeCollision[i].y * sinx);

				boiteDeCollision[i].x = (cosy * boiteDeCollision[i].x + boiteDeCollision[i].z * siny);
				boiteDeCollision[i].z = (-siny * boiteDeCollision[i].x + boiteDeCollision[i].z * cosy);

				boiteDeCollision[i].x = (cosz * boiteDeCollision[i].x - boiteDeCollision[i].y * sinz);
				boiteDeCollision[i].y = (sinz * boiteDeCollision[i].x + boiteDeCollision[i].y * cosz);
			}

		}

	public:

		Modele3D(){
			echelle = Vecteur3f(1, 1, 1);
		}

		Modele3D(Modele &modele, Texture &texture): Objet3D() {
			this->modele = modele;
			this->texture = texture;
			echelle = Vecteur3f(1, 1, 1);
		}

		~Modele3D(){}

		void defModele(Modele &modele){
			this->modele = modele;
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

		Vecteur3f* obtBoiteDeCollision(){
			return boiteDeCollision;
		}

		Texture obtTexture(){
			return texture;
		}

		virtual void rafraichir(){
			glPushMatrix();
			glLoadIdentity();


			glPopMatrix();
		};

		virtual void afficher(){
			glBindTexture(GL_TEXTURE_2D, texture.obtID());
			glPushMatrix();
				glLoadIdentity();
				glTranslatef(position.x, position.y, position.z);
				glRotatef(orientation.x, 1, 0, 0);
				glRotatef(orientation.y, 0, 1, 0);
				glRotatef(orientation.z, 0, 0, 1);
				glScalef(echelle.x, echelle.y, echelle.z);
				glVertexPointer(3, GL_FLOAT, 0, modele.obtVertices());
				glTexCoordPointer(2, GL_FLOAT, 0, modele.obtTextures());
				glNormalPointer(GL_FLOAT, 0, modele.obtNormales());
				glDrawArrays(GL_TRIANGLES, 0, modele.obtNbrFaces());
			glPopMatrix();
		}
	};
}