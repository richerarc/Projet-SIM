#pragma once
#include "Info.h"
#include "ObjetPhysique.h"
#include "Salle.h"
#include <math.h>
enum EtatItem { EQUIPE, RANGE, DEPOSE };
class Joueur;

class Item : public ObjetPhysique{
protected:
	int type;
	char* nom;
	char* description;
	char* cheminIcone;
	int maxPile;
	EtatItem etat;
	Salle* salleActive;

	Chrono animation;
	double angleAnimation;
public:
	Item(int type, char* nom, char* description, char* cheminIcone, int maxPile, gfx::Modele3D* modele, unsigned int ID, char* materiaux, double masse) : ObjetPhysique(modele, ID, materiaux, masse, Vecteur3d(), Vecteur3d(), Vecteur3d(), false){
		this->type = type;
		this->nom = nom;
		this->description = description;
		this->cheminIcone = cheminIcone;
		this->maxPile = maxPile;
		etat = EQUIPE;
		salleActive = nullptr;
	}

	virtual void utiliser(Joueur* joueur) = 0;
	virtual void utiliser2(Joueur* joueur) = 0;
	virtual void equiper(Joueur* joueur) = 0;

	virtual void animer() = 0;

	void defEtat(EtatItem etat){
		if (etat == this->etat)
			return;
		gfx::Gestionnaire3D::obtInstance().retObjet(modele);

		if (etat == EtatItem::EQUIPE){
			vitesse = Vecteur3d(0, 0, 0);
			Vecteur3d position = gfx::Gestionnaire3D::obtInstance().obtCamera()->obtPosition() + gfx::Gestionnaire3D::obtInstance().obtCamera()->obtDevant()*0.8 - gfx::Gestionnaire3D::obtInstance().obtCamera()->obtHaut()*0.13 + gfx::Gestionnaire3D::obtInstance().obtCamera()->obtCote()*0.5;
			modele->defPosition(position);
			gfx::Gestionnaire3D::obtInstance().ajouterObjet(modele);
		}

		else if (etat == EtatItem::DEPOSE){
			if (!salleActive)
				return;
			vitesse = Vecteur3d(0.1, 0, 0);
			salleActive->ajoutObjet(this);
			gfx::Gestionnaire3D::obtInstance().ajouterObjet(modele);
		}
		else if (etat == EtatItem::RANGE){
			vitesse = Vecteur3d(0, 0, 0);
			if (this->etat == EtatItem::DEPOSE)
				salleActive->retirerObjet(this);
			gfx::Gestionnaire3D::obtInstance().retObjet(modele);
		}
		this->etat = etat;
	}

	void actualiser(Salle* salleActuelle, Joueur* joueur){
		this->salleActive = salleActuelle;
		if (etat == EtatItem::EQUIPE){
			if (Souris::boutonAppuye(SDL_BUTTON_LEFT)){
				utiliser(joueur);
			}
			if (Souris::boutonAppuye(SDL_BUTTON_RIGHT)){
				utiliser2(joueur);
			}
			Vecteur3d newPosition = gfx::Gestionnaire3D::obtInstance().obtCamera()->obtPosition() + gfx::Gestionnaire3D::obtInstance().obtCamera()->obtDevant() * 0.8 - gfx::Gestionnaire3D::obtInstance().obtCamera()->obtHaut() * 0.33 + gfx::Gestionnaire3D::obtInstance().obtCamera()->obtCote() * 0.4;
			this->position = newPosition;
			modele->defPosition(position);
			modele->defOrientation(0, 0, 0);
			modele->rotationner(gfx::Gestionnaire3D::obtInstance().obtCamera()->obtHaut(), 80 + gfx::Gestionnaire3D::obtInstance().obtCamera()->obtHAngle());
			animer();
			modele->rotationner(gfx::Gestionnaire3D::obtInstance().obtCamera()->obtCote(), gfx::Gestionnaire3D::obtInstance().obtCamera()->obtVAngle() + angleAnimation);
			
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

	bool obtSiPorte(){
		return false;
	}

};