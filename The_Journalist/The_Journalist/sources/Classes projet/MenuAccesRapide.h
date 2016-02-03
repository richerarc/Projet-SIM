#pragma once
#include "Menu.h"
#include "Inventaire.h"
#include "Gestionnaire3D.h"

class MenuAccesRapide : public Menu{
private:
	std::vector<gfx::Sprite2D*> cases;
	std::vector<gfx::Sprite2D*> objets;
	
	gfx::Sprite2D* spriteSurvol;

	Inventaire *inventaire;
	int itemSelectionne;
	//int dernierItemSelectionne;
public:
	MenuAccesRapide(Inventaire *inventaire){
		Vecteur2f position;
		this->inventaire = inventaire;
		for (int i = 0; i < inventaire->obtTailleAccesRapide(); ++i){
			position.x = 1120;
			position.y = 10 + i * 70;
			cases.push_back(new gfx::Sprite2D(position, gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/caseAccesRapide.png")));
			Item* objet = inventaire->obtObjetAccesRapide(i);
			if (objet != nullptr)
				objets.push_back(new gfx::Sprite2D(position + Vecteur2f(70, 0), gfx::GestionnaireRessources::obtInstance().obtTexture(objet->obtCheminIcone())));
			else
				objets.push_back(new gfx::Sprite2D(position + Vecteur2f(70, 0), nullptr));
		}
		spriteSurvol = new gfx::Sprite2D(cases[0]->obtPosition() + Vecteur2f(-51, 0), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/caseAccesRapideSurvol.png"));
		
		pause = false;
		itemSelectionne = 0;
		//dernierItemSelectionne = itemSelectionne + 1;
		GestionnaireEvenements::obtInstance().ajouterUnRappel(SDL_MOUSEWHEEL, std::bind(&MenuAccesRapide::molette, this, std::placeholders::_1));
		//GestionnaireEvenements::obtInstance().ajouterUnRappel(SDL_KEYDOWN, std::bind(&MenuAccesRapide::toucheAppuyee, this, std::placeholders::_1));
	}

	~MenuAccesRapide(){
		while (cases.size() != 0){
			gfx::Gestionnaire2D().retObjet(cases.back());
			delete cases.back();
			cases.pop_back();
		}

		while (objets.size() != 0){
			gfx::Gestionnaire2D().retObjet(objets.back());
			delete objets.back();
			objets.pop_back();
		}
	}

	void actualiserAffichage(){
		for (int i = 0; i < inventaire->obtTailleAccesRapide(); ++i){
			Item* objet = inventaire->obtObjetAccesRapide(i);
			if (objet != nullptr)
				objets[i]->defTexture(gfx::GestionnaireRessources::obtInstance().obtTexture(objet->obtCheminIcone()));
			else
				objets[i]->defTexture(nullptr);
		}
	}

	void molette(SDL_Event &event){
		if (gfx::Gestionnaire3D::obtInstance().obtCamera()->obtBloquer())
			return;
		//dernierItemSelectionne = itemSelectionne;
		itemSelectionne = inventaire->obtItemSelectionne() + event.wheel.y;
		itemSelectionne %= inventaire->obtTailleAccesRapide();
		if (itemSelectionne < 0)
			itemSelectionne = inventaire->obtTailleAccesRapide() - 1;

		spriteSurvol->defPosition(cases[itemSelectionne]->obtPosition() + Vecteur2f(-51, 0));
		inventaire->defItemSelectionne(itemSelectionne);
	}

	//void toucheAppuyee(SDL_Event& event){
	//	/*if (event.key.keysym.sym >= 49 && event.key.keysym.sym <= 58){
	//		dernierItemSelectionne = itemSelectionne;
	//		itemSelectionne = event.key.keysym.sym - 49;
	//		spriteSurvol->defPosition(cases[itemSelectionne]->obtPosition() + Vecteur2f(-51, 0));
	//		inventaire->defItemSelectionne(itemSelectionne);
	//	}*/
	//	/*if (event.key.keysym.sym == SDLK_q){
	//		int swap = itemSelectionne;
	//		itemSelectionne = dernierItemSelectionne;
	//		dernierItemSelectionne = swap;
	//		spriteSurvol->defPosition(cases[itemSelectionne]->obtPosition() + Vecteur2f(-51, 0));
	//		inventaire->defItemSelectionne(itemSelectionne);
	//	}*/
	//}

	void remplir(){
		for (gfx::Sprite2D* sprite : cases)
			gfx::Gestionnaire2D::obtInstance().ajouterObjet(sprite);
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(spriteSurvol);
		for (gfx::Sprite2D* sprite : objets)
			gfx::Gestionnaire2D::obtInstance().ajouterObjet(sprite);
	}

	void vider(){
		for (gfx::Sprite2D* sprite : cases)
			gfx::Gestionnaire2D::obtInstance().retObjet(sprite);
		gfx::Gestionnaire2D::obtInstance().retObjet(spriteSurvol);
		for (gfx::Sprite2D* sprite : objets)
			gfx::Gestionnaire2D::obtInstance().retObjet(sprite);
	}

	void defPause(bool pause){
		this->pause = pause;
	}

	void actualiserEchelle(Vecteur2f vecteurEchelle){

	}
};