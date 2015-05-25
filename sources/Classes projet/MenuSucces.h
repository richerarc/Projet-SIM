#pragma once
#include "Menu.h"
#include "Texte2D.h"
#include "MenuSon.h"
#include "PhaseMenuSon.h"
#include "PhaseMenuGraphique.h"
#include "PhaseMenuControle.h"
#include "Bouton.h"

class MenuSucces : public Menu{
private:
	Bouton* reinitialiser;
	std::list<gfx::Texte2D*> listeTitres;
	gfx::Sprite2D* quadrillage;
public:

	MenuSucces(void){
		spriteFond = new gfx::Sprite2D(Vecteur2f(0, 0), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/fondMenu.png"));
		quadrillage = new gfx::Sprite2D(Vecteur2f(20, 90), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/achievementsMenu.png"));
		reinitialiser = new Bouton(std::bind(&MenuSucces::enClicReinit, this, std::placeholders::_1),
			std::bind(&MenuSucces::survol, this, std::placeholders::_1),
			std::bind(&MenuSucces::defaut, this, std::placeholders::_1),
			Vecteur2f(300, 25),
			new std::string("Reset Achievements"),
			50);

		this->retour = new Bouton(std::bind(&MenuSucces::enClicRetour, this, std::placeholders::_1),
			std::bind(&MenuSucces::survol, this, std::placeholders::_1),
			std::bind(&MenuSucces::defaut, this, std::placeholders::_1),
			Vecteur2f(50, 25),
			new std::string("Back"),
			50);

		listeTitres.push_back(new gfx::Texte2D(new std::string ("Wait, what?"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("Ressources/Font/arial.ttf", 25), Vecteur2f(400, 400)));

		std::list <Succes*> liste = GestionnaireSucces::obtInstance().obtListeSucces();
		GestionnaireSucces::obtInstance().chargerFichier("Ressources/Info/sauvegarde_succes.txt");


		for (auto it : liste){
			if (it->obtAccompli()){
				it->obtTitre()->defCouleur({ 255, 255, 255, 255 });
			}
			else{
				it->obtTitre()->defCouleur({ 150, 150, 150, 255 });
			}
			//it->obtTitre()->defPosition();
		}
		defPause(true);
	}

	void enClicReinit(Bouton* envoi){
		if (pause)
			return;
		for (auto it : GestionnaireSucces::obtInstance().obtListeSucces()){
			it->obtTitre()->defCouleur({ 200, 200, 200, 255 });
			it->defAccompli(false);
		}
		GestionnaireSucces::obtInstance().reinitialiserSauvegarde();
	}

	void enClicRetour(Bouton* envoi){
		if (pause)
			return;
		for (auto it : GestionnaireSucces::obtInstance().obtListeSucces()){
			it->obtTitre()->defCouleur({0,0,0,255});
			it->obtTitre()->defPosition(Vecteur2f(905, 640));
		}
		clicRetour();
	}

	void survol(Bouton* envoi){
		if (pause)
			return;
		envoi->defCouleur({ 255, 0, 0, 255 });
	}

	void defaut(Bouton* envoi){
		if (pause)
			return;
		envoi->defCouleur({ 0, 0, 0, 255 });
	}

	void remplir(){
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(spriteFond);
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(quadrillage);
		for (auto it : GestionnaireSucces::obtInstance().obtListeSucces()){
			gfx::Gestionnaire2D::obtInstance().ajouterObjet(it->obtTitre());
		}
		retour->remplir();
		reinitialiser->remplir();
	}
	void defPause(bool pause){
		if (pause) {
			this->pause = pause;
			reinitialiser->defEtat(PAUSE);
			retour->defEtat(PAUSE);
		}

		else {
			this->pause = pause;
			reinitialiser->defEtat(DEFAUT);
			retour->defEtat(DEFAUT);
		}
	}
	void actualiserEchelle(Vecteur2f vecteurEchelle){
		this->retour->defEchelle(vecteurEchelle);
		this->spriteFond->defEchelle(vecteurEchelle);
		reinitialiser->defEchelle(vecteurEchelle);
	}

};