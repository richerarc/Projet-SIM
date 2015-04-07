#pragma once
#include "Physique.h"
#include "Objet.h"
#include "Vent.h"
#include "Aimant.h"
#include "ObjetFixe.h"
#include "ObjetPhysique.h"

class Salle{
protected:
	unsigned int ID;
	unsigned int nbrPortes;
	gfx::Modele3D modele;
	std::list<Objet*> objets;
public:
	Salle(){}

	Salle(gfx::Modele3D modele, unsigned int nbrPorte, int ID){
		nbrPortes = nbrPorte;
		this->ID = ID;
		this->modele = modele;
	}

	void appliquerPhysiqueSurListeObjet(float frameTime) {
		for (auto it : objets) {
			if (it->obtMasse() != 0) {
				Physique::obtInstance().appliquerGravite(it->obtVitesse(), frameTime);
			}
			Vent* it_Vent = dynamic_cast<Vent*>(it);
			if (it_Vent != nullptr) {
				for (auto it_Objet : objets) {
					if (it_Objet->obtMasse() != 0) {
						/*
						if (it_Objet->obtModele3D().obtPosition().x >= it->obtPosition().x && it_Objet->obtModele3D().obtPosition().x <= it->obtPosition().x + it->obtDimensions().x) {
						if (it_Objet->obtModele3D().obtPosition().y >= it->obtPosition().y && it_Objet->obtModele3D().obtPosition().y <= it->obtPosition().y + it->obtDimensions().y) {
						if (it_Objet->obtModele3D().obtPosition().z >= it->obtPosition().z && it_Objet->obtModele3D().obtPosition().z <= it->obtPosition().z + it->obtDimensions().z) {
						Physique::obtInstance().appliquerVent(it->obtVitesse(), *it_Objet, frameTime);
						}
						}
						}
						*/
					}
				}
			}
			Aimant* it_Aimant = dynamic_cast<Aimant*>(it);
			if (it_Aimant != nullptr) {
				for (auto it_Objet : objets) {
					if (it_Objet->obtMasse() != 0) {
						Physique::obtInstance().appliquerMagnetisme(*it_Objet, it_Aimant->obtPosition(), it_Aimant->obtForce(), frameTime);
					}
				}
			}
			ObjetFixe* it_ObjetFixe = dynamic_cast<ObjetFixe*>(it);
			if (it_ObjetFixe != nullptr) {
				for (auto it_Objet : objets) {
					if (it_Objet->obtMasse() != 0) {
						// collisions

					}
				}
			}
		}
	}

	unsigned int obtNbrPortes(){
		return nbrPortes;
	}

	unsigned int obtID(){
		return ID;
	}

	void setID(unsigned int ID){
		this->ID = ID;
	}

	Vecteur3d obtPos(){
		return modele.obtPosition();
	}

	void defPosition(int axeX, int axeY, int axeZ){
		modele.defPosition(axeX, axeY, axeZ);
	}

	gfx::Modele3D& obtModele(){
		return modele;
	}
	
	void ajoutObjet(Objet *objet){
		objets.push_back(objet);
	}
	
	Objet* obtObjet(unsigned int ID){
		for(auto it: objets){
			if (it->obtID() == ID)
				return it;
		}
	}
	
	std::list<Objet*>& obtListeObjet() {
		
		return objets;
	}
};