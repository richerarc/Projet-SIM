#pragma once
#include "Info.h"
#include "ObjetPhysique.h"
#include "Salle.h"
#include <math.h>
enum class EtatItem { EQUIPE, RANGE, DEPOSE };

class Item : public ObjetPhysique{
private:
	Chrono animation;
	int type;
	char* nom;
	char* description;
	char* cheminIcone;
	int maxPile;
	EtatItem etat;
	Salle* salleActive;
public:
	Item(int type, char* nom, char* description, char* cheminIcone, int maxPile, gfx::Modele3D* modele, unsigned int ID, char* materiaux, double masse, Vecteur3d vitesse, Vecteur3d position, Vecteur3d vitesseAngulaire, bool collisionInterne) : ObjetPhysique(modele, ID, materiaux, masse, vitesse, position, vitesseAngulaire, collisionInterne){
		this->type = type;
		this->nom = nom;
		this->description = description;
		this->cheminIcone = cheminIcone;
		this->maxPile = maxPile;
		etat = EtatItem::EQUIPE;
		salleActive = nullptr;
	}

	void defEtat(EtatItem etat){
		if (etat == this->etat)
			return;

		if (etat == EtatItem::EQUIPE){
			Vecteur3d position = gfx::Gestionnaire3D::obtInstance().obtCamera()->obtPosition() + gfx::Gestionnaire3D::obtInstance().obtCamera()->obtDevant()*0.8 - gfx::Gestionnaire3D::obtInstance().obtCamera()->obtHaut()*0.13 + gfx::Gestionnaire3D::obtInstance().obtCamera()->obtCote()*0.5;
			modele->defPosition(position);
			gfx::Gestionnaire3D::obtInstance().ajouterObjet(modele);
		}

		else if (etat == EtatItem::DEPOSE)
		{
			if (!salleActive)
				return;
			salleActive->ajoutObjet(this);
		}
		else if (etat == EtatItem::RANGE){
			gfx::Gestionnaire3D::obtInstance().retObjet(modele);
		}
		this->etat = etat;
	}

	void actualiser(Salle* salleActuelle, int etatJoueur){
		this->salleActive = salleActuelle;
		if (etat == EtatItem::EQUIPE){
			Vecteur3d position = gfx::Gestionnaire3D::obtInstance().obtCamera()->obtPosition() + gfx::Gestionnaire3D::obtInstance().obtCamera()->obtDevant()*0.8 - gfx::Gestionnaire3D::obtInstance().obtCamera()->obtHaut()*0.43 + gfx::Gestionnaire3D::obtInstance().obtCamera()->obtCote()*0.5;
			modele->defPosition(position);
			modele->defOrientation(0, 0, 0);
			//if (etatJoueur == 2){
			//	double tempsAnimation = animation.obtTempsEcoule().enSecondes();
			//	modele->rotationner(10 * sin(10 * tempsAnimation), 0, 0);
			//	modele->rotationner(0, 0, 10 * sin(10 * tempsAnimation) - gfx::Gestionnaire3D::obtInstance().obtCamera()->obtVAngle());
			//}
			//else
				modele->rotationner(0, 0, -gfx::Gestionnaire3D::obtInstance().obtCamera()->obtVAngle());
			modele->rotationner(0, 80 + gfx::Gestionnaire3D::obtInstance().obtCamera()->obtHAngle(), 0);
		}
	}

	EtatItem obtEtat(){
		return etat;
	}

	int obtType(){
		return this->type;
	}

	char* obtNom(){
		return this->nom;
	}

	char* obtDescription(){
		return this->description;
	}

	char* obtCheminIcone(){
		return this->cheminIcone;
	}

	int obtMaxPile(){
		return this->maxPile;
	}

	virtual void utiliser(){

	}

	bool obtSiPorte(){
		return false;
	}

};