#pragma once
#include "Item.h"

class MasqueGaz : public Item{
	bool etatEquipe;
	gfx::Objet2D* filtre;
	short durabilite;
public:
	MasqueGaz(unsigned int ID) : Item(50, "Gas Mask", "Your key to get away alive", "Ressources/Texture/masqueAGazIcone.png", 16, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/masqueAGaz.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/masqueAGaz.png")), ID, "metal", 2.0){
		etatEquipe = false;
		filtre = new gfx::Sprite2D(Vecteur2f(), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/filtreMasqueAGaz.png"));
		filtre->defEchelle(Vecteur2f(fenetre->obtTaille().x / 1024.0, fenetre->obtTaille().y / 1024.0));
		durabilite = 100;
	}
	void defEtat(EtatItem etat){
		if (etat == this->etat)
			return;
		gfx::Gestionnaire3D::obtInstance().retObjet(modele);

		if (etat == EtatItem::EQUIPE){
			vitesse = Vecteur3d(0, 0, 0);
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
			vitesse = Vecteur3d(0.1, 0, 0);
			salleActive->ajoutObjet(this);
			gfx::Gestionnaire2D::obtInstance().retObjet(filtre);
			gfx::Gestionnaire3D::obtInstance().ajouterObjet(modele);
			etatEquipe = false;
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
	void utiliser(Joueur* joueur){
		if (!etatEquipe && durabilite > 0){
			gfx::Gestionnaire2D::obtInstance().ajouterObjet(filtre);
			gfx::Gestionnaire3D::obtInstance().retObjet(modele);
			etatEquipe = true;
		}
	}
	void utiliser2(Joueur* joueur){
		if (etatEquipe){
			gfx::Gestionnaire2D::obtInstance().retObjet(filtre);
			gfx::Gestionnaire3D::obtInstance().ajouterObjet(modele);
			etatEquipe = false;
		}
	}
	void equiper(Joueur* joueur){}
	void animer(Joueur* joueur) {}

	bool estEquipe(){ return etatEquipe; }
	void user(){
		--durabilite;
		if (durabilite == 0){
			etatEquipe = false;
			gfx::Gestionnaire2D::obtInstance().retObjet(filtre);
			gfx::Gestionnaire3D::obtInstance().ajouterObjet(modele);
		}
	}
	short obtDurabilite() { return durabilite; }
	void recharger() { durabilite = 100; }
};