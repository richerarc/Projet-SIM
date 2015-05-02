#pragma once 
#include "Menu.h"
#include "Inventaire.h"

class MenuInventaire : public Menu {
private:
	std::list<gfx::Sprite2D*> casesSacADos;
	std::list<gfx::Sprite2D*> casesAccesRapide;

	std::vector<gfx::Sprite2D*> objetsSacADos;
	std::vector<gfx::Sprite2D*> objetsAccesRapide;

	Inventaire* inventaire;
	InfoObjet* objetCurseur;
	gfx::Sprite2D* spriteObjetCurseur;

	Chrono chrono;

public:
	MenuInventaire(Inventaire *inventaire){
		Vecteur2f position;
		this->inventaire = inventaire;
		for (int i = 0; i < inventaire->obtTailleSacADos(); ++i){
			position.x = 300 + (i % inventaire->obtTailleAccesRapide()) * 70;
			position.y = 200 + int(i / inventaire->obtTailleAccesRapide()) * 70;
			casesSacADos.push_back(new gfx::Sprite2D(position, &gfx::GestionnaireRessources::obtInstance().obtTexture("case.png")));
			InfoObjet* objet = inventaire->obtObjetSacADos(i);
			if (objet != nullptr)
				objetsSacADos.push_back(new gfx::Sprite2D(position, &gfx::GestionnaireRessources::obtInstance().obtTexture(inventaire->obtObjetSacADos(i)->cheminIcone)));
			else
				objetsSacADos.push_back(new gfx::Sprite2D(position, nullptr));
		}

		for (int i = 0; i < inventaire->obtTailleAccesRapide(); ++i){

			position.x = 1200;
			position.y = 10 + i * 70;
			casesAccesRapide.push_back(new gfx::Sprite2D(position, &gfx::GestionnaireRessources::obtInstance().obtTexture("case.png")));
			InfoObjet* objet = inventaire->obtObjetAccesRapide(i);
			if (objet != nullptr)
				objetsAccesRapide.push_back(new gfx::Sprite2D(position, &gfx::GestionnaireRessources::obtInstance().obtTexture(objet->cheminIcone)));
			else
				objetsAccesRapide.push_back(new gfx::Sprite2D(position, nullptr));
		}

		pause = false;
		objetCurseur = nullptr;
		spriteObjetCurseur = new gfx::Sprite2D();
		actualiserAffichage();

		GestionnaireEvenements::obtInstance().ajouterUnRappel(SDL_MOUSEBUTTONDOWN, std::bind(&MenuInventaire::surClic, this, std::placeholders::_1));
		GestionnaireEvenements::obtInstance().ajouterUnRappel(SDL_MOUSEMOTION, std::bind(&MenuInventaire::survol, this, std::placeholders::_1));

	}

	~MenuInventaire(){
		while (casesSacADos.size() != 0){
			gfx::Gestionnaire2D().retObjet(casesSacADos.back());
			delete casesSacADos.back();
			casesSacADos.pop_back();
		}

		while (casesAccesRapide.size() != 0){
			gfx::Gestionnaire2D().retObjet(casesAccesRapide.back());
			delete casesAccesRapide.back();
			casesAccesRapide.pop_back();
		}

		while (objetsSacADos.size() != 0){
			gfx::Gestionnaire2D().retObjet(objetsSacADos.back());
			delete objetsSacADos.back();
			objetsSacADos.pop_back();
		}

		while (objetsAccesRapide.size() != 0){
			gfx::Gestionnaire2D().retObjet(objetsAccesRapide.back());
			delete objetsAccesRapide.back();
			objetsAccesRapide.pop_back();
		}
		delete spriteObjetCurseur;
	}

	void actualiserAffichage(){
		for (int i = 0; i < inventaire->obtTailleSacADos(); ++i){
			InfoObjet* objet = inventaire->obtObjetSacADos(i);
			if (objet != nullptr)
				objetsSacADos[i]->defTexture(&gfx::GestionnaireRessources::obtInstance().obtTexture(objet->cheminIcone));
			else
				objetsSacADos[i]->defTexture(nullptr);
		}

		for (int i = 0; i < inventaire->obtTailleAccesRapide(); ++i){
			InfoObjet* objet = inventaire->obtObjetAccesRapide(i);
			if (objet != nullptr)
				objetsAccesRapide[i]->defTexture(&gfx::GestionnaireRessources::obtInstance().obtTexture(objet->cheminIcone));
			else
				objetsAccesRapide[i]->defTexture(nullptr);
		}
		if (objetCurseur != nullptr)
			spriteObjetCurseur->defTexture(&gfx::GestionnaireRessources::obtInstance().obtTexture(objetCurseur->cheminIcone));
		else
			spriteObjetCurseur->defTexture(nullptr);
	}

	void surClic(SDL_Event &event){
		if (pause)
			return;

		bool dedans = false;
		int ID = 0;
		for (gfx::Sprite2D* sprite : casesSacADos){
			if (sprite->obtRectangle().contient(Vecteur2f(Souris::obtPosition().x, Souris::obtPosition().y))){
					dedans = true;
					//Si un objet se trouve déjà où on clique.
					if (inventaire->obtObjetSacADos(ID) != nullptr){
						//Si j'ai déjà un objet sur mon curseur.
						if (objetCurseur != nullptr){
							InfoObjet* tmp = objetCurseur;

							objetCurseur = inventaire->retirerObjetSacADos(ID);

							inventaire->ajouterObjetCaseSacADos(tmp, ID);
							actualiserAffichage();
						}
						else{
							objetCurseur = inventaire->retirerObjetSacADos(ID);
							actualiserAffichage();
						}
					}
					else{
						if (objetCurseur != nullptr){
							inventaire->ajouterObjetCaseSacADos(objetCurseur, ID);
							objetCurseur = nullptr;
							actualiserAffichage();
						}
					}

				}
			ID++;
		}
		ID = 0;
		for (gfx::Sprite2D* sprite : casesAccesRapide){
			if (sprite->obtRectangle().contient(Vecteur2f(Souris::obtPosition().x, Souris::obtPosition().y))){
					dedans = true;
					//Si un objet se trouve déjà où on clique.
					if (inventaire->obtObjetAccesRapide(ID) != nullptr){
						//Si j'ai déjà un objet sur mon curseur.
						if (objetCurseur != nullptr){
							InfoObjet* tmp = objetCurseur;

							objetCurseur = inventaire->retirerObjetAccesRapide(ID);

							inventaire->ajouterObjetCaseAccesRapide(tmp, ID);
							actualiserAffichage();
						}
						else{
							objetCurseur = inventaire->retirerObjetAccesRapide(ID);
							actualiserAffichage();
						}
					}
					else{
						if (objetCurseur != nullptr){
							inventaire->ajouterObjetCaseAccesRapide(objetCurseur, ID);
							objetCurseur = nullptr;
							actualiserAffichage();
						}

					}
				}
			ID++;
		}
		if (!dedans){
			if (Souris::boutonAppuye(SDL_BUTTON_LEFT)){
				if (objetCurseur != nullptr){
					inventaire->ajouterObjet(objetCurseur);
					objetCurseur = nullptr;
					actualiserAffichage();
				}
			}
		}
	}

	void survol(SDL_Event &event){
		if (pause)
			return;

		spriteObjetCurseur->defPosition(Vecteur2f(Souris::obtPosition().x - 32, 720 - Souris::obtPosition().y - 32));

		for (gfx::Sprite2D* sprite : casesAccesRapide){
			if (sprite->obtRectangle().contient(Vecteur2f(Souris::obtPosition().x, Souris::obtPosition().y)))
				sprite->defTexture(&gfx::GestionnaireRessources::obtInstance().obtTexture("caseSurvol.png"));
			else
				sprite->defTexture(&gfx::GestionnaireRessources::obtInstance().obtTexture("case.png"));
		}
		for (gfx::Sprite2D* sprite : casesSacADos){
			if (sprite->obtRectangle().contient(Vecteur2f(Souris::obtPosition().x, Souris::obtPosition().y)))
				sprite->defTexture(&gfx::GestionnaireRessources::obtInstance().obtTexture("caseSurvol.png"));
			else
				sprite->defTexture(&gfx::GestionnaireRessources::obtInstance().obtTexture("case.png"));
		}
	}


	void remplir(){
		for (gfx::Sprite2D* sprite : casesSacADos)
			gfx::Gestionnaire2D::obtInstance().ajouterObjet(sprite);
		for (gfx::Sprite2D* sprite : casesAccesRapide)
			gfx::Gestionnaire2D::obtInstance().ajouterObjet(sprite);

		for (gfx::Sprite2D* sprite : objetsSacADos)
			gfx::Gestionnaire2D::obtInstance().ajouterObjet(sprite);
		for (gfx::Sprite2D* sprite : objetsAccesRapide)
			gfx::Gestionnaire2D::obtInstance().ajouterObjet(sprite);
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(spriteObjetCurseur);
	}

	void defPause(bool pause){
		this->pause = pause;
	}

	void actualiserEchelle(Vecteur2f echelle){

	}
};