#pragma once
#include "Item.h"
#include "ControlleurAudio.h"
#include "Texte2D.h"
#include "GestionnaireRessources.h"

class Illuminati : public Item{
private:
	gfx::Texte2D* texteIllumination;
public:

	Illuminati(unsigned int ID) : Item(80, "Triangle of the illumination", "Is this real life?", "Ressources/Texture/illuminatiIcone.png", 1, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/trouDeBalle.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/illuminati.png")), ID, "metal", 10){
		texteIllumination = new gfx::Texte2D(new std::string("Illuminati Confirmed!"), { 255, 255, 255, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("Ressources/Font/arial.ttf", 60), Vecteur2f(100, 300));
	}

	~Illuminati(){
		gfx::Gestionnaire2D::obtInstance().retObjet(texteIllumination);
		delete texteIllumination;
	}

	void utiliser(Joueur* joueur){
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(texteIllumination);
	}

	void utiliser2(Joueur* joueur){
		gfx::Gestionnaire2D::obtInstance().retObjet(texteIllumination);
	}

	void equiper(Joueur* joueur){
		ControlleurAudio::obtInstance().jouer(XFILE, joueur);
	}

	void animer(Joueur* joueur){
		
	}
};