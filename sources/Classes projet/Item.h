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

	Chrono animation;
	double angleHorizontal;

	bool equipe;

public:
	static Salle* salleActive;
	Item(int type, char* nom, char* description, char* cheminIcone, int maxPile, gfx::Modele3D* modele, unsigned int ID, char* materiaux, double masse) : ObjetPhysique(modele, ID, materiaux, masse, Vecteur3d(), Vecteur3d(), Vecteur3d(), false){
		this->type = type;
		this->nom = nom;
		this->description = description;
		this->cheminIcone = cheminIcone;
		this->maxPile = maxPile;
		etat = DEPOSE;
		salleActive = nullptr;
	}

	virtual void utiliser(Joueur* joueur) = 0;
	virtual void utiliser2(Joueur* joueur) = 0;
	virtual void equiper(Joueur* joueur) = 0;

	virtual void animer(Joueur* joueur) = 0;

	 virtual void defEtat(EtatItem etat){
		if (etat == this->etat)
			return;
		gfx::Gestionnaire3D::obtInstance().retObjet(modele);

		if (etat == EtatItem::EQUIPE){
			vitesse = Vecteur3d(0, 0, 0);
			Vecteur3d position = gfx::Gestionnaire3D::obtInstance().obtCamera()->obtPosition() + gfx::Gestionnaire3D::obtInstance().obtCamera()->obtDevant()*0.8 - gfx::Gestionnaire3D::obtInstance().obtCamera()->obtHaut()*0.13 + gfx::Gestionnaire3D::obtInstance().obtCamera()->obtCote()*0.5;
			modele->defPosition(position);
			gfx::Gestionnaire3D::obtInstance().ajouterObjet(modele);
			angleHorizontal = 80;
			equipe = true;
		}

		else if (etat == EtatItem::DEPOSE){
			if (!salleActive)
				return;
			vitesse = Vecteur3d(0.1, 0, 0);
			salleActive->ajoutObjet(this);
			gfx::Gestionnaire3D::obtInstance().ajouterObjet(modele);
			equipe = false;
		}
		else if (etat == EtatItem::RANGE){
			vitesse = Vecteur3d(0, 0, 0);
			if (this->etat == EtatItem::DEPOSE)
				salleActive->retirerObjet(this);
			gfx::Gestionnaire3D::obtInstance().retObjet(modele);
			equipe = false;
		}
		this->etat = etat;
	}

	void actualiser(Salle* salleActuelle, Joueur* joueur, float frametime){
		this->salleActive = salleActuelle;
		if (etat == EtatItem::EQUIPE){
			Vecteur3d newPosition = gfx::Gestionnaire3D::obtInstance().obtCamera()->obtPosition() + gfx::Gestionnaire3D::obtInstance().obtCamera()->obtDevant() * 0.8 - gfx::Gestionnaire3D::obtInstance().obtCamera()->obtHaut() * 0.33 + gfx::Gestionnaire3D::obtInstance().obtCamera()->obtCote() * 0.4;
			this->position = newPosition;
			modele->defPosition(position);
			if (equipe){
				equiper(joueur);
				equipe = false;
			}
			if (Souris::boutonAppuye(SDL_BUTTON_LEFT)){
				utiliser(joueur);
			}
			if (Souris::boutonAppuye(SDL_BUTTON_RIGHT)){
				utiliser2(joueur);
			}
			if (etat == EtatItem::EQUIPE){
				modele->defOrientation(0, 0, 0);
				modele->rotationner(gfx::Gestionnaire3D::obtInstance().obtCamera()->obtHaut(), angleHorizontal + gfx::Gestionnaire3D::obtInstance().obtCamera()->obtHAngle());
				animer(joueur);
				if (etat == EtatItem::EQUIPE)
					modele->rotationner(gfx::Gestionnaire3D::obtInstance().obtCamera()->obtCote(), gfx::Gestionnaire3D::obtInstance().obtCamera()->obtVAngle());
			}
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
Salle* Item::salleActive = nullptr;

