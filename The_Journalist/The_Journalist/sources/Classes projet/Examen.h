#pragma once
#include "Item.h"
#include "Texte2D.h"

class Examen : public Item{
private:
	int allo;
public:
	Examen(unsigned int ID, int aleatoire) : Item(22, "Exam", "This apparently needs correction.", "Ressources/Texture/examenIcone.png", 16, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/examen.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/examenIcone.png")), ID, "metal", 2.0){
		//delete this->obtModele3D()->obtTexture()->;
		allo = aleatoire;
		switch (aleatoire){
		case (0) :
			this->obtModele3D()->defTexture(gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/examBrandon.png"));
			break;
		case (1) :
			this->obtModele3D()->defTexture(gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/examDamien.png"));
			break;
		case (2) :
			this->obtModele3D()->defTexture(gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/examDiego.png"));
			break;
		case (3) :
				 this->obtModele3D()->defTexture(gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/examDom.png"));
			break;
		case (4) :
				 this->obtModele3D()->defTexture(gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/examGab.png"));
			break;
		case (5) :
				 this->obtModele3D()->defTexture(gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/examJessy.png"));
			break;
		case (6) :
				 this->obtModele3D()->defTexture(gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/examJulien.png"));
			break;
		case (7) :
				 this->obtModele3D()->defTexture(gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/examKevin.png"));
			break;
		case (8) :
				 this->obtModele3D()->defTexture(gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/examNathan.png"));
			break;
		case (9) :
				 this->obtModele3D()->defTexture(gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/examNicoC.png"));
			break;
		case (10) :
				  this->obtModele3D()->defTexture(gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/examNicoD.png"));
			break;
		case (11) :
				  this->obtModele3D()->defTexture(gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/examRicher.png"));
			break;
		case (12) :
				  this->obtModele3D()->defTexture(gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/examSam.png"));
			break;
		case (13) :
				  this->obtModele3D()->defTexture(gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/examXavier.png"));
			break;
		}
	}

	void utiliser(Joueur* joueur){

	}

	void utiliser2(Joueur* joueur){

	}

	void equiper(Joueur* joueur){
		switch (rand() % 3){
		case (0):
			return ControlleurAudio::obtInstance().jouer(PAPIER_1, joueur);
		case (1) :
			return ControlleurAudio::obtInstance().jouer(PAPIER_2, joueur);
		case (2) :
			return ControlleurAudio::obtInstance().jouer(PAPIER_3, joueur);
		}
	}

	void animer(Joueur* joueur){
		float vitesseJoueur = joueur->obtVitesseDeplacement();
		if (vitesseJoueur == 4.0f)
			modele->rotationner(Vecteur3d(0, 0, 1), 3 * sin(10 * animation.obtTempsEcoule().enSecondes()));
		if (vitesseJoueur == 10.0f)
			modele->rotationner(Vecteur3d(0, 0, 1), 20 * sin(10 * animation.obtTempsEcoule().enSecondes()));
	}
};