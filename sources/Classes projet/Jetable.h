#pragma once 
#include "Item.h"

struct Jetable : public Item{
	Jetable(int type, char* nom, char* description, char* cheminIcone, int maxPile, gfx::Modele3D* modele, unsigned int ID, char* materiaux, double masse) : Item(type, nom, description, cheminIcone, maxPile, modele, ID, materiaux, masse){

	}
	~Jetable(){

	}
	virtual void animer(Joueur* joueur){
		float vitesseJoueur = joueur->obtVitesseDeplacement();
		if (vitesseJoueur == 4.0f)
			modele->rotationner(Vecteur3d(0, 0, 1), 3 * sin(10 * animation.obtTempsEcoule().enSecondes()));
		if (vitesseJoueur == 10.0f)
			modele->rotationner(Vecteur3d(0, 0, 1), 20 * sin(10 * animation.obtTempsEcoule().enSecondes()));
	}
	void utiliser(Joueur* joueur){
		if (!joueur->obtBloque()){
			this->defEtat(EtatItem::DEPOSE);
			this->defVitesse(joueur->obtDevant() * 10);
			joueur->obtInventaire()->retirerObjetAccesRapide(joueur->obtInventaire()->obtItemSelectionne());
		}
	}
	virtual void utiliser2(Joueur* joueur){
		if (!joueur->obtBloque()){
			this->defEtat(EtatItem::DEPOSE);
			this->defVitesse(joueur->obtDevant() * 25);
			joueur->obtInventaire()->retirerObjetAccesRapide(joueur->obtInventaire()->obtItemSelectionne());
		}
	}
	void equiper(Joueur* joueur){}
};

class Companion : public Jetable{
private:
	gfx::Modele3D* batman;
	gfx::Modele3D* joker;
	gfx::Modele3D* companion;
	gfx::Modele3D* modeleActuel;
public:
	Companion(int ID) : Jetable(42, "Companion", "Your trustworthy companion", "Ressources/Texture/CompanionIcone.png", 1, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/Companion.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/Companion.png")), ID, "roche", 1){
		batman = new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/batman.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/batman.png"));
		joker = new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/Joker.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/Joker.png"));
		companion = this->obtModele3D();
		modeleActuel = companion;
		modeleActuel->defEchelle(0.5, 0.5, 0.5);
	}

	void changerModele(short santeMentale){
		if (santeMentale <= 25 && modeleActuel != joker){
			modeleActuel = joker;
			modeleActuel->defModele(joker->obtModele());
			modeleActuel->defTexture(joker->obtTexture());
				//GestionnaireSucces::obtInstance().obtSucces(26);
		}
		if (santeMentale <= 60 && santeMentale > 25 && modeleActuel != batman){
			modeleActuel = batman;
			modeleActuel->defModele(batman->obtModele());
			modeleActuel->defTexture(batman->obtTexture());
				//GestionnaireSucces::obtInstance().obtSucces(7);
		}
		if (santeMentale > 60 && modeleActuel != companion){
			modeleActuel = companion;
			modeleActuel->defModele(companion->obtModele());
			modeleActuel->defTexture(companion->obtTexture());
		}
		modele->defModele(modeleActuel->obtModele());
		modele->defTexture(modeleActuel->obtTexture());
	}
};