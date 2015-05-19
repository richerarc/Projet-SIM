#pragma once
#include <SDL2\SDL.h>
#include "Succes.h"
#include <list>
#include "Chrono.h"
#include "Singleton.h"
#include "Vecteur3.h"
#include "Texte.h"
#include "Texte2D.h"
#include "Police.h"
class GestionnaireSucces: public Singleton<GestionnaireSucces>{
private:
	std::list<Succes*> listeSucces;
	Chrono chronoSanteMentale;
	Chrono chronoAffichage;
	gfx::Sprite2D* boite;
	gfx::Texte2D* titre;
	gfx::Texte2D* description;
public:
	void initialiser(){
		titre = nullptr;
		description = nullptr;
		boite = new gfx::Sprite2D(Vecteur2f(900, 550), new gfx::Texture("Ressources/Texture/achievement.png"));
		listeSucces.push_back(new Succes(new gfx::Texte2D(new std::string("Wait, what?"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("Ressources/Font/arial.ttf", 25), Vecteur2f(905, 650)), new gfx::Texte2D(new std::string("Lose sanity for the first time"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("Ressources/Font/arial.ttf", 19), Vecteur2f(905,585)), 0));
		listeSucces.push_back(new Succes(new gfx::Texte2D(new std::string("It's dangerous to go alone! Take this."), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("Ressources/Font/arial.ttf", 20), Vecteur2f(905, 650)), new gfx::Texte2D(new std::string("Pick up an item for the first time"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("Ressources/Font/arial.ttf", 17), Vecteur2f(905, 585)), 1));
		listeSucces.push_back(new Succes(new gfx::Texte2D(new std::string("We've got a long way to go..."), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("Ressources/Font/arial.ttf", 25), Vecteur2f(905, 650)), new gfx::Texte2D(new std::string("Start a new game"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("Ressources/Font/arial.ttf", 20), Vecteur2f(905, 585)), 2));
		chargerFichier("Ressources/Info/sauvegarde_succes.txt");
	}
	void reinitialiserSauvegarde(){
		for (auto it : listeSucces){
			it->defAccompli(false);
		}
		std::ofstream fichier;
		fichier.open("Ressources/Info/sauvegarde_succes.txt",std::ofstream::out | std::ofstream::trunc);
		fichier.close();
	}
	void chargerFichier(const char* nomFichier){
		std::ifstream fichier;
		fichier.open(nomFichier);
		unsigned short ligne;
		while (!fichier.eof()){
			fichier >> ligne;
			for (auto it : listeSucces){
				if (it->obtID() == ligne){
					it->defAccompli(true);
				}
			}
		}
		fichier.close();
	}
	void afficherSucces(Succes* succes){
		if (titre != nullptr){
			gfx::Gestionnaire2D::obtInstance().retObjet(titre);
		}
		titre = succes->obtTitre();
		if (titre != nullptr){
			gfx::Gestionnaire2D::obtInstance().retObjet(description);
		}
		description = succes->obtDescription();
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(boite);
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(succes->obtTitre());
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(succes->obtDescription());
		chronoAffichage.repartir();
	}
	void verifierTempsAffichage(){
		if (chronoAffichage.obtTempsEcoule().enMillisecondes() > 5000.){
			gfx::Gestionnaire2D::obtInstance().retObjet(boite);
			gfx::Gestionnaire2D::obtInstance().retObjet(titre);
			gfx::Gestionnaire2D::obtInstance().retObjet(description);
			titre = nullptr;
			description = nullptr;
		}
	}
	void ajouterAuFichier(unsigned short IDSucces){
		std::ofstream fichier;
		fichier.open("Ressources/Info/sauvegarde_succes.txt");
		fichier << std::to_string(IDSucces) + "\n";
		fichier.close();
	}
	void obtSucces(unsigned short IDSucces){
		for (auto it : listeSucces){
			if (!it->obtAccompli() && it->obtID() == IDSucces){
				it->defAccompli(true);
				ajouterAuFichier(IDSucces);
				afficherSucces(it);
				break;
			}
		}
	}
};