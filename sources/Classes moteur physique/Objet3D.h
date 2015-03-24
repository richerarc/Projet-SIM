#pragma once
#include "Vecteur3.h"

namespace gfx{

	class Objet3D{
	protected:
		Vecteur3d position;
		Vecteur3f origine;
		Vecteur3f orientation;
		Vecteur3d vitesse;
		double masse;
		char* materiel;
	public:

		Objet3D(){
		}

		~Objet3D(){
		}

		Vecteur3d obtPosition(){
			return position;
		}

		Vecteur3f obtOrigine(){
			return origine;
		}

		Vecteur3f obtOrientation(){
			return orientation;
		}

		Vecteur3d& obtVitesse() {
			return vitesse;
		}

		double obtMasse() {
			return masse;
		}

		char* obtMateriel() {
			return materiel;
		}

		void defPosition(Vecteur3d &pos){
			position = pos;
		}

		void defOrigine(Vecteur3f &org){
			origine = org;
		}

		void defOrientation(Vecteur3f &ort){
			orientation = ort;
		}

		void defVitesse(Vecteur3d &vit) {
			vitesse = vit;
		}

		void defMasse(double masse) {
			this->masse = masse;
		}

		void defMateriel(char* materiel) {
			this->materiel = materiel;
		}

		void rotationner(Vecteur3f &rot){
			orientation += rot;
		}

		void deplacer(Vecteur3d &dep){
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

		void defVitesse(float axeX, float axeY, float axeZ){
			vitesse.x = axeX;
			vitesse.y = axeY;
			vitesse.z = axeZ;

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

		virtual void rafraichir() = 0;

		virtual void afficher() = 0;

	};
}