#pragma once
#include "Item.h"
#include "Texte2D.h"

class Note : public Item {

private:
	int animationActuelle;
public:

	Note(int ID, gfx::Texture* texture) : Item(20, "Note", "Something is written on this piece of paper.", "Ressources/Texture/noteIcone.png", 1, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/note.obj"), texture), ID, "carton", 1.0){
		
	}

	void utiliser(Joueur* joueur){
		Vecteur3d newPosition = gfx::Gestionnaire3D::obtInstance().obtCamera()->obtPosition() + gfx::Gestionnaire3D::obtInstance().obtCamera()->obtDevant() * 0.8;
		this->position = newPosition;
		modele->defPosition(position);
		angleHorizontal = 120;
	}

	void utiliser2(Joueur* joueur){
	
	}

	void equiper(Joueur* joueur){

	}

	void animer(Joueur* joueur){
		float vitesseJoueur = joueur->obtVitesseDeplacement();
		if (vitesseJoueur == 4.0f)
			modele->rotationner(Vecteur3d(0, 0, 1), 3 * sin(10 * animation.obtTempsEcoule().enSecondes()));
		if (vitesseJoueur == 10.0f)
			modele->rotationner(Vecteur3d(0, 0, 1), 20 * sin(10 * animation.obtTempsEcoule().enSecondes()));
	}
};