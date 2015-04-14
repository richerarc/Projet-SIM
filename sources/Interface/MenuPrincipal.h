#pragma once
#include "Menu.h"
#include "Sprite2D.h"


class MenuPrincipal : public Menu {

private:
	Bouton* NouvellePartie;
	Bouton* Options;

public:
	MenuPrincipal(void) : Menu() {
		this->Actif = true;
		
		gfx::Texture* TextureSprite = new gfx::Texture();
		gfx::GestionnaireRessources::obtInstance().chargerTexture("C:\\Users\\Xavier\\Desktop\\cube.png");
		this->SpriteFond = new gfx::Sprite2D(Vecteur2f(0, 0), TextureSprite);

		gfx::Texture* TextureSpriteBNPFond = new gfx::Texture();
		gfx::GestionnaireRessources::obtInstance().chargerTexture("C:\\Users\\Xavier\\Desktop\\blanc.png");

		gfx::Texture* TextureSpriteBNPClique = new gfx::Texture();
		gfx::GestionnaireRessources::obtInstance().chargerTexture("C:\\Users\\Xavier\\Desktop\\rose.png");

		gfx::Texture* TextureSpriteBNPSurvol = new gfx::Texture();
		gfx::GestionnaireRessources::obtInstance().chargerTexture("C:\\Users\\Xavier\\Desktop\\turquoise.png");
		NouvellePartie = new Bouton(Vecteur2f(150, 400),Vecteur2f(300, 150),
			new gfx::Texte2D("Nouvelle Partie", "arial.ttf", 9, Vecteur2f(150, 400)),
			new gfx::Sprite2D(Vecteur2f(150, 400), TextureSpriteBNPFond),
			new gfx::Sprite2D(Vecteur2f(150, 400), TextureSpriteBNPClique),
			new gfx::Sprite2D(Vecteur2f(150, 400), TextureSpriteBNPSurvol));



		Options = new Bouton(Vecteur2f(150, 200), Vecteur2f(300, 150),
			new gfx::Texte2D("Options", "arial.ttf", 9, Vecteur2f(150, 200)),
			new gfx::Sprite2D(Vecteur2f(150, 200), TextureSpriteBNPFond),
			new gfx::Sprite2D(Vecteur2f(150, 200), TextureSpriteBNPClique),
			new gfx::Sprite2D(Vecteur2f(150, 200), TextureSpriteBNPSurvol));

		this->Titre = new Etiquette( new gfx::Texte2D("The Journalist", "arial.ttf", 20, Vecteur2f(150, 300)), new gfx::Sprite2D(Vecteur2f(150,300),TextureSpriteBNPFond),Vecteur2f(150,300),Vecteur2f(300, 300));

		this->Retour = new Bouton(Vecteur2f(150, 0), Vecteur2f(300, 150), new gfx::Texte2D("Retour", "arial.ttf", 15, Vecteur2f(150, 0)), new gfx::Sprite2D(Vecteur2f(150, 0), TextureSpriteBNPFond),  new gfx::Sprite2D(Vecteur2f(150, 0), TextureSpriteBNPClique), new gfx::Sprite2D(Vecteur2f(150, 0), TextureSpriteBNPSurvol));

	}
	bool obtActif(void) {
		return this->Actif;
	}
	
	void defActif(bool Actif) {
		this->Actif = Actif;
	}

	void afficher(void) {
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(this->SpriteFond);
		NouvellePartie->afficher();
		Options->afficher();
		this->Titre->afficher();
		this->Retour->afficher();
	}


};