#pragma once
#include "Menu.h"
#include "Sprite2D.h"
#include "GestionnairePhases.h"
#include "Jeu.h"


class MenuPrincipal : public Menu {
private:
	gfx::Texte2D* nouvellePartie;
	gfx::Texte2D* options;
	gfx::Sprite2D* logo;
public:
	MenuPrincipal(void) {
		nouvellePartie = new gfx::Texte2D("Nouvelle Partie", "arial.ttf", 9, Vecteur2f(150, 400));
		options = new gfx::Texte2D("Options", "arial.ttf", 9, Vecteur2f(150, 200));

		logo = new gfx::Sprite2D(Vecteur2f(150, 400), &gfx::GestionnaireRessources::obtInstance().obtTexture(""));
		this->Retour = new gfx::Texte2D("Retour", "arial.ttf", 15, Vecteur2f(150, 0));

		this->SpriteFond = new gfx::Sprite2D(Vecteur2f(150, 400), &gfx::GestionnaireRessources::obtInstance().obtTexture("")),

		gfx::Gestionnaire2D::obtInstance().ajouterObjet(nouvellePartie);
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(options);
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(this->Retour);
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(logo);
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(this->SpriteFond);
	}

	~MenuPrincipal(void) {
		gfx::Gestionnaire2D::obtInstance().vider();
	}

	void actualiser(void) {
		if (nouvellePartie->obtRectangle().contient(Souris::obtPosition().x, Souris::obtPosition().y)) {
			GestionnairePhases::obtInstance().retirerPhase();
			GestionnairePhases::obtInstance().ajouterPhase(new PhaseNouvellePartie());
		}
		else if (options->obtRectangle().contient(Souris::obtPosition().x, Souris::obtPosition().y)) {
			GestionnairePhases::obtInstance().retirerPhase();
			GestionnairePhases::obtInstance().ajouterPhase(new PhaseOptions());
		}
		else if (this->Retour->obtRectangle().contient(Souris::obtPosition().x, Souris::obtPosition().y)) {
			Jeu::fenetre->fermer();
		}
	}

};