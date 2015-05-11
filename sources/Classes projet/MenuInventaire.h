#pragma once 
#include "Menu.h"
#include "Inventaire.h"
#include "Chrono.h"

class MenuInventaire : public Menu {
private:
	std::list<gfx::Sprite2D*> casesSacADos;
	std::list<gfx::Sprite2D*> casesAccesRapide;

	std::vector<gfx::Sprite2D*> objetsSacADos;
	std::vector<gfx::Sprite2D*> objetsAccesRapide;

	Inventaire* inventaire;
	Item* objetCurseur;
	gfx::Sprite2D* spriteObjetCurseur;

	gfx::Texte2D* texteNom;
	gfx::Texte2D* texteDescription;

public:
	MenuInventaire(Inventaire *inventaire){
		Vecteur2f position;
		this->inventaire = inventaire;
		for (int i = 0; i < inventaire->obtTailleSacADos(); ++i){
			position.x = 300 + (i % inventaire->obtTailleAccesRapide()) * 70;
			position.y = 200 + int(i / inventaire->obtTailleAccesRapide()) * 70;
			casesSacADos.push_back(new gfx::Sprite2D(position, gfx::GestionnaireRessources::obtInstance().obtTexture("caseInventaire.png")));
			Item* objet = inventaire->obtObjetSacADos(i);
			if (objet != nullptr)
				objetsSacADos.push_back(new gfx::Sprite2D(position, gfx::GestionnaireRessources::obtInstance().obtTexture(inventaire->obtObjetSacADos(i)->obtCheminIcone())));
			else
				objetsSacADos.push_back(new gfx::Sprite2D(position, nullptr));
		}

		for (int i = 0; i < inventaire->obtTailleAccesRapide(); ++i){

			position.x = 1190;
			position.y = 10 + i * 70;
			casesAccesRapide.push_back(new gfx::Sprite2D(position, gfx::GestionnaireRessources::obtInstance().obtTexture("caseInventaire.png")));
			Item* objet = inventaire->obtObjetAccesRapide(i);
			if (objet != nullptr)
				objetsAccesRapide.push_back(new gfx::Sprite2D(position, gfx::GestionnaireRessources::obtInstance().obtTexture(objet->obtCheminIcone())));
			else
				objetsAccesRapide.push_back(new gfx::Sprite2D(position, nullptr));
		}
		texteNom = new gfx::Texte2D(new std::string(""), { 62, 62, 62, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("arial.ttf", 40), Vecteur2f(300, 425));
		texteDescription = new gfx::Texte2D(new std::string(""), { 62, 62, 62, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("arial.ttf", 15), Vecteur2f(300, 405));

		pause = false;
		objetCurseur = nullptr;
		spriteObjetCurseur = new gfx::Sprite2D();
		actualiserAffichage();

		GestionnaireEvenements::obtInstance().ajouterUnRappel(SDL_MOUSEBUTTONDOWN, std::bind(&MenuInventaire::surClic, this, std::placeholders::_1));
		GestionnaireEvenements::obtInstance().ajouterUnRappel(SDL_MOUSEMOTION, std::bind(&MenuInventaire::survol, this, std::placeholders::_1));
		GestionnaireEvenements::obtInstance().ajouterUnRappel(SDL_KEYDOWN, std::bind(&MenuInventaire::toucheAppuyee, this, std::placeholders::_1));

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
		delete texteDescription;
		delete texteNom;
	}

	void actualiserAffichage(){
		for (int i = 0; i < inventaire->obtTailleSacADos(); ++i){
			Item* objet = inventaire->obtObjetSacADos(i);
			if (objet != nullptr)
				objetsSacADos[i]->defTexture(gfx::GestionnaireRessources::obtInstance().obtTexture(objet->obtCheminIcone()));
			else
				objetsSacADos[i]->defTexture(nullptr);
		}

		for (int i = 0; i < inventaire->obtTailleAccesRapide(); ++i){
			Item* objet = inventaire->obtObjetAccesRapide(i);
			if (objet != nullptr)
				objetsAccesRapide[i]->defTexture(gfx::GestionnaireRessources::obtInstance().obtTexture(objet->obtCheminIcone()));
			else
				objetsAccesRapide[i]->defTexture(nullptr);
		}
		if (objetCurseur != nullptr)
			spriteObjetCurseur->defTexture(gfx::GestionnaireRessources::obtInstance().obtTexture(objetCurseur->obtCheminIcone()));
		else
			spriteObjetCurseur->defTexture(nullptr);
	}

	void toucheAppuyee(SDL_Event &event){
		if (pause)
			return;
		if (event.key.keysym.sym == SDLK_ESCAPE){
			if (objetCurseur != nullptr){
				inventaire->ajouterObjet(objetCurseur);
				objetCurseur = nullptr;
			}
			gfx::Gestionnaire2D::obtInstance().vider();
			GestionnairePhases::obtInstance().obtPhaseActive()->defPause(true);
			GestionnairePhases::obtInstance().enleverPhaseActive();
			GestionnairePhases::obtInstance().obtPhaseActive()->defPause(false);
			gfx::Gestionnaire3D::obtInstance().obtCamera()->deBloquer();
			GestionnairePhases::obtInstance().obtPhaseActive()->remplir();
		}
	}

	void surClic(SDL_Event &event){
		if (pause)
			return;

		bool dedans = false;
		int ID = 0;
		for (gfx::Sprite2D* sprite : casesSacADos){
			if (sprite->obtRectangle().contient(Vecteur2f(Curseur::obtPosition().x, Curseur::obtPosition().y))){
				dedans = true;
				//Si un objet se trouve déjà où on clique.
				if (inventaire->obtObjetSacADos(ID) != nullptr){
					//Si j'ai déjà un objet sur mon curseur.
					if (objetCurseur != nullptr){
						Item* tmp = objetCurseur;

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
			if (sprite->obtRectangle().contient(Vecteur2f(Curseur::obtPosition().x, Curseur::obtPosition().y))){
				dedans = true;
				//Si un objet se trouve déjà où on clique.
				if (inventaire->obtObjetAccesRapide(ID) != nullptr){
					//Si j'ai déjà un objet sur mon curseur.
					if (objetCurseur != nullptr){
						Item* tmp = objetCurseur;

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
		actualiserAffichage();
		spriteObjetCurseur->defPosition(Vecteur2f(Curseur::obtPosition().x - 32, Curseur::obtPosition().y - 32));
		if (objetCurseur != nullptr){
			texteNom->defTexte(new std::string(objetCurseur->obtNom()));
			texteDescription->defTexte(new std::string(objetCurseur->obtDescription()));
		}

		int ID = 0;
		bool dedans = false;
		for (gfx::Sprite2D* sprite : casesAccesRapide){
			if (sprite->obtRectangle().contient(Vecteur2f(Curseur::obtPosition().x, Curseur::obtPosition().y))){
				dedans = true;
				if (inventaire->obtObjetAccesRapide(ID) != nullptr){
					texteNom->defTexte(new std::string(inventaire->obtObjetAccesRapide(ID)->obtNom()));
					texteDescription->defTexte(new std::string(inventaire->obtObjetAccesRapide(ID)->obtDescription()));
				}
				sprite->defTexture(gfx::GestionnaireRessources::obtInstance().obtTexture("caseInventaireSurvol.png"));
			}
			else{
				sprite->defTexture(gfx::GestionnaireRessources::obtInstance().obtTexture("caseInventaire.png"));
			}
			ID++;
		}
		ID = 0;
		for (gfx::Sprite2D* sprite : casesSacADos){
			if (sprite->obtRectangle().contient(Vecteur2f(Curseur::obtPosition().x, Curseur::obtPosition().y))){
				dedans = true;
				if (inventaire->obtObjetSacADos(ID) != nullptr){
					texteNom->defTexte(new std::string(inventaire->obtObjetSacADos(ID)->obtNom()));
					texteDescription->defTexte(new std::string(inventaire->obtObjetSacADos(ID)->obtDescription()));
				}
				sprite->defTexture(gfx::GestionnaireRessources::obtInstance().obtTexture("caseInventaireSurvol.png"));
			}
			else{
				sprite->defTexture(gfx::GestionnaireRessources::obtInstance().obtTexture("caseInventaire.png"));
			}
			ID++;
		}
		if (!dedans && objetCurseur == nullptr){
			texteDescription->defTexte(new std::string(""));
			texteNom->defTexte(new std::string(""));
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
		gfx::Gestionnaire2D::obtInstance().ajouterObjets({ texteNom, texteDescription, spriteObjetCurseur });
	}

	void vider(){
		for (gfx::Sprite2D* sprite : casesSacADos)
			gfx::Gestionnaire2D::obtInstance().retObjet(sprite);
		for (gfx::Sprite2D* sprite : casesAccesRapide)
			gfx::Gestionnaire2D::obtInstance().retObjet(sprite);

		for (gfx::Sprite2D* sprite : objetsSacADos)
			gfx::Gestionnaire2D::obtInstance().retObjet(sprite);
		for (gfx::Sprite2D* sprite : objetsAccesRapide)
			gfx::Gestionnaire2D::obtInstance().retObjet(sprite);
		gfx::Gestionnaire2D::obtInstance().retObjets({ texteNom, texteDescription, spriteObjetCurseur });
	}

	void defPause(bool pause){
		this->pause = pause;
	}

	void actualiserEchelle(Vecteur2f echelle){

	}
};