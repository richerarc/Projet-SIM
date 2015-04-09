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
			gfx::Texte2D("Nouvelle Partie", "arial.ttf", 9, Vecteur2f(150, 150)),
			gfx::Sprite2D(Vecteur2f(150, 150), TextureSpriteBNPFond),
			gfx::Sprite2D(Vecteur2f(150, 150), TextureSpriteBNPClique),
			gfx::Sprite2D(Vecteur2f(150, 150), TextureSpriteBNPSurvol));



		Options = new Bouton(Vecteur2f(150, 200), Vecteur2f(300, 150),
			gfx::Texte2D("Options", "arial.ttf", 9, Vecteur2f(150, 180)),
			gfx::Sprite2D(Vecteur2f(150,180),TextureSpriteBNPFond),
			gfx::Sprite2D(Vecteur2f(150, 180), TextureSpriteBNPClique),
			gfx::Sprite2D(Vecteur2f(150, 180), TextureSpriteBNPSurvol));

		this->Titre = new Etiquette(gfx::Texte2D("The Journalist", "arial.ttf", 20, Vecteur2f(150, 300)),gfx::Sprite2D(Vecteur2f(150,300),TextureSpriteBNPFond),Vecteur2f(150,700),Vecteur2f(300, 150));

		this->Retour = new Bouton(Vecteur2f(150, 0), Vecteur2f(300, 150), gfx::Texte2D("Retour", "arial.ttf", 15, Vecteur2f(150, 110)), gfx::Sprite2D(Vecteur2f(150, 110), TextureSpriteBNPFond), gfx::Sprite2D(Vecteur2f(150, 110), TextureSpriteBNPClique), gfx::Sprite2D(Vecteur2f(150, 110), TextureSpriteBNPSurvol));

	}
	bool obtActif(void) {
		return this->Actif;
	}
	
	void defActif(bool Actif) {
		this->Actif = Actif;
	}

	


};