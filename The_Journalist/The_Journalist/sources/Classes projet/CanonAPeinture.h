#pragma once
#include "Item.h"
#include "Peinture.h"
#include "Maths.h"

class CanonAPeinture : public Item {
private:

	std::list<Peinture*>* peintures;
	Chrono intervalPeinture;
	unsigned int nbrPeinture;

public:

	CanonAPeinture(int type, char* nom, char* description, char* cheminIcone, gfx::Modele3D* modele, unsigned int ID, char* materiaux, double masse) : Item(type, nom, description, cheminIcone, 1, modele, ID, materiaux, masse) {
		peintures = new std::list<Peinture*>();
		intervalPeinture.repartir();
	}

	void reinitialiserListePeinture() {
		peintures->resize(0);
		delete peintures;
		peintures = new std::list<Peinture*>();
		Peinture* peinture;
		if (salleActive) {
			for (auto it : salleActive->obtListeObjet()) {
				peinture = dynamic_cast<Peinture*>(it);
				if (peinture) {
					peintures->push_back(peinture);
				}
			}
		}
	}

	void animer(Joueur* joueur) {
		float vitesseJoueur = joueur->obtVitesseDeplacement();
		if (vitesseJoueur == 4.0f)
			modele->rotationner(Vecteur3d(0, 0, 1), 3 * sin(10 * animation.obtTempsEcoule().enSecondes()));
		if (vitesseJoueur == 10.0f)
			modele->rotationner(Vecteur3d(0, 0, 1), 20 * sin(10 * animation.obtTempsEcoule().enSecondes()));
	}

	void utiliser(Joueur* joueur) {
		if (intervalPeinture.obtTempsEcoule().enSecondes() > 2.40) {
			Droite rayon(gfx::Gestionnaire3D::obtInstance().obtCamera()->obtPosition(), gfx::Gestionnaire3D::obtInstance().obtCamera()->obtDevant());
			Vecteur3d pointCollision;
			Vecteur3d normale;
			if (Physique::obtInstance().collisionDroiteModele(salleActive->obtModele(), rayon, pointCollision, normale, false)) {
				if (Maths::vecteurEntreDeuxPoints(joueur->obtPositionCamera(), pointCollision).norme() < 3) {
					intervalPeinture.repartir();
					ControlleurAudio::obtInstance().jouer(CANONAPEINTURE, joueur);
					Peinture* peinture = new Peinture(124, new gfx::Modele3D(new gfx::Modele("Ressources/Modele/Peinture.obj"), new gfx::Texture("Ressources/Texture/Peinture.png")), pointCollision, normale, true);
					if (peintures->size() == 4) {
						gfx::Gestionnaire3D::obtInstance().retObjet((*peintures->begin())->obtModele3D());
						salleActive->retirerObjet((*peintures->begin()));
						peintures->pop_front();
					}
					gfx::Gestionnaire3D::obtInstance().ajouterObjet(peinture->obtModele3D());
					salleActive->ajoutObjet(peinture);
					peintures->push_back(peinture);
				}
			}
		}
	}

	void utiliser2(Joueur* joueur) {

	}

	void equiper(Joueur* joueur) {
		ControlleurAudio::obtInstance().jouer(EQUIPERCANONAPEINTURE, joueur);
	}
};