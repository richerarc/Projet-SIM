#pragma once
#include "Item.h"

class MasqueGaz : public Item{
	bool etatEquipe;
	short durabilite;
public:
	MasqueGaz(unsigned int ID) : Item(50, "Gas Mask", "Your key to get away alive", "Ressources/Texture/masqueAGazIcone.png", 16, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/masqueAGaz.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/masqueAGaz.png")), ID, "metal", 2.0){
		etatEquipe = false;
		durabilite = 100;
	}
	void defEtat(EtatItem etat){
		if (etat == this->etat)
			return;
		gfx::Gestionnaire3D::obtInstance().retObjet(modele);

		if (etat == EtatItem::EQUIPE){
			Vecteur3d position = gfx::Gestionnaire3D::obtInstance().obtCamera()->obtPosition() + gfx::Gestionnaire3D::obtInstance().obtCamera()->obtDevant()*0.8 - gfx::Gestionnaire3D::obtInstance().obtCamera()->obtHaut()*0.13 + gfx::Gestionnaire3D::obtInstance().obtCamera()->obtCote()*0.5;
			modele->defPosition(position);
			if (!etatEquipe)
				gfx::Gestionnaire3D::obtInstance().ajouterObjet(modele);
			angleHorizontal = 80;
			equipe = true;
		}

		else if (etat == EtatItem::DEPOSE){
			if (!salleActive)
				return;
			this->defVitesse(gfx::Gestionnaire3D::obtInstance().obtCamera()->obtDevant() * 10);
			this->defVitesseAngulaire(Vecteur3d(0, 0, 0));
			this->obtModele3D()->defOrientation(Vecteur3d(0, 0, -45));
			this->defStable(false);
			salleActive->ajoutObjet(this);
			gfx::Gestionnaire3D::obtInstance().ajouterObjet(modele);
			etatEquipe = false;
			equipe = false;
		}
		else if (etat == EtatItem::RANGE){
			if (this->etat == EtatItem::DEPOSE)
				salleActive->retirerObjet(this);
			gfx::Gestionnaire3D::obtInstance().retObjet(modele);
			equipe = false;
		}
		this->etat = etat;
	}
	void utiliser(Joueur* joueur){
		if (!joueur->obtBloque()){
			if (!etatEquipe && durabilite > 0){
				gfx::Gestionnaire3D::obtInstance().retObjet(modele);
				etatEquipe = true;
			}
		}
	}
	void utiliser2(Joueur* joueur){
		if (!joueur->obtBloque()){
			if (etatEquipe){
				gfx::Gestionnaire3D::obtInstance().ajouterObjet(modele);
				etatEquipe = false;
			}
		}
	}
	void equiper(Joueur* joueur){}
	void animer(Joueur* joueur) {}
	void reinitialiserListePeinture() {}

	bool estEquipe(){ return etatEquipe; }
	void user(){
		--durabilite;
		if (durabilite < 0){
			durabilite = 0;
			etatEquipe = false;
		}
	}
	short obtDurabilite() { return durabilite; }
	void recharger() { durabilite = 100; }
};