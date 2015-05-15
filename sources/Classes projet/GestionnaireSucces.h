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
	std::list<Succes> listeSucces;
	Chrono chronoSanteMentale;
	Chrono chronoAffichage;
	gfx::Sprite2D* boite;
public:
	void initialiser(){
		boite = new gfx::Sprite2D(Vecteur2f(0, 520), new gfx::Texture("Ressources/Texture/achievement.png"));
		listeSucces.push_back(Succes(new gfx::Texte2D(new std::string("Wait, what?"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("Ressources/Font/arial.ttf", 58), Vecteur2f(620, 641)), new gfx::Texte2D(new std::string("Lose sanity for the first time."), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("Ressources/Font/arial.ttf", 58), Vecteur2f(20, 580)), 0));
		listeSucces.push_back(Succes(new gfx::Texte2D(new std::string("It's dangerous to go alone! Take this."), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("Ressources/Font/arial.ttf", 55), Vecteur2f(0, 0)), new gfx::Texte2D(new std::string("Pick up an item for the first time"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("Ressources/Font/arial.ttf", 55), Vecteur2f(0, 0)), 1));
	}
	void reinitialiserSauvegarde(){
		for (auto it : listeSucces){
			it.defAccompli(false);
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
				if (it.obtID() == ligne){
					it.defAccompli(true);
					break;
				}
			}
		}
		fichier.close();
	}
	void afficherSucces(Succes succes){
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(boite);
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(succes.obtTitre());
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(succes.obtDescription());
			//if (it.obtID() == ID){
				//gfx::Gestionnaire2D::obtInstance().ajouterObjet(it.obtTitre());
				//gfx::Gestionnaire2D::obtInstance().ajouterObjet(it.obtDescription());
				//gfx::Gestionnaire2D::obtInstance().
			//}
	}
	void ajouterAuFichier(unsigned short IDSucces){
		std::ofstream fichier;
		fichier.open("Ressources/Info/sauvegarde_succes.txt");
		fichier << std::to_string(IDSucces) + "\n";
		fichier.close();
	}
	void obtSucces(unsigned short IDSucces){
		for (auto it : listeSucces){
			if (!it.obtAccompli() && it.obtID() == IDSucces){
				it.defAccompli(true);
				ajouterAuFichier(IDSucces);
				afficherSucces(it);
				break;
			}
		}
	}
};