#pragma once
#include <stack>
#include <list>
#include <math.h>
#include "PhaseMenuPause.h"
#include "Maths.h"
#include "Item.h"
#include "MenuAccesRapide.h"
#include "PhaseMenuInventaire.h"

class PhaseJeu : public Phase{

private:

	Joueur* joueur;
	gfx::Texte2D* texte;
	Objet* objetVise;
	bool toucheRelachee;
	std::stack<unsigned int> cheminRecursif;
	std::list<unsigned int> cheminLogique;
	double iterateur_x, iterateur_z;
	int sensPrecedent, sensActuel;
	Chrono tempsJeu;
	Item *itemEquipe;
	Item *test;

	bool retour;

	MenuAccesRapide* accesRapide;

	double exponentielle(double a, double b, double h, double k, double x, int limite){
		double temp = a * pow(M_E, b * (x - h)) + k;
		if (temp < limite){
			return temp;
		}
		return limite;
	}

	void santeMentale(){
		double pourcentagePerdu(0);
		if (cheminRecursif.size() > 1){
			pourcentagePerdu += exponentielle(1, 0.2f, 0, -1, cheminRecursif.size(), 5);
		}
		int idActif = cheminLogique.front();
		std::list<unsigned int>::iterator it = cheminLogique.begin();
		for (++it; it != cheminLogique.end(); ++it){
			if (((*it) == idActif) && ((iterateur_x > 2.5f) || (iterateur_z > 2.5))){
				pourcentagePerdu += exponentielle(1, -0.5f, -3.8f, -1, cheminLogique.size(), 5);
				cheminLogique.erase(cheminLogique.begin(), --it);
				iterateur_x = 0;
				iterateur_z = 0;
				break;
			}
		}
		joueur->defSanteMentale((double)joueur->obtSanteMentale() - ((double)joueur->obtSanteMentale() * (pourcentagePerdu / 100.f)));
	}


	void appliquerPhysique(float frameTime) {
		/*if (joueur->obtVitesse().norme() != 0) {
			Physique::obtInstance().appliquerGravite(joueur->obtVitesse(), frameTime);
			if (joueur->obtNormaleMur().y == 0. && (joueur->obtNormaleMur().x != 0. || joueur->obtNormaleMur().z != 0.)){
				joueur->longer();
			}*/
			joueur->defPosition(joueur->obtPosition() + joueur->obtVitesse() * frameTime);
		//	iterateur_x += joueur->obtVitesse().x * frameTime;
		//	iterateur_z += joueur->obtVitesse().z * frameTime;
		//	short typeCollision = Physique::obtInstance().collisionJoueurSalle(Carte::obtInstance().salleActive->obtModele(), joueur);
		//	//if (typeCollision == MUR) {
		//	//	joueur->obtVitesse().x = 0.;
		//	//	joueur->obtVitesse().z = 0.;
		//	//}
		//	if ((typeCollision == SOLDROIT || typeCollision == SOLCROCHE)){
		//		joueur->defEtat(STABLE);
		//		joueur->obtVitesse().y = 0.f;
		//		joueur->obtVitesse().x = 0.f;
		//		joueur->obtVitesse().z = 0.f;
		//	}
		//}
		Physique::obtInstance().appliquerPhysiqueSurListeObjet(Carte::obtInstance().salleActive->obtModele(), Carte::obtInstance().salleActive->obtListeObjet(), frameTime, tempsJeu.obtTempsEcoule().enSecondes());
	}

	bool detectionObjet() {

		std::list<Objet*> liste = Carte::obtInstance().salleActive->obtListeObjet();
		bool objetDetecte = false;

		for (auto it : liste) {
			Porte* it_Porte = dynamic_cast<Porte*>(it);
			Item* it_Item = dynamic_cast<Item*>(it);
			Droite VueJoueur = Droite(joueur->obtPosition() + (Vecteur3d(0.0, joueur->obtModele3D()->obtModele()->obtTaille().y, 0.0)), joueur->obtVectOrientationVue());
			if ((Maths::distanceEntreDeuxPoints(joueur->obtPosition(), it->obtPosition()) < 2) && (joueur->obtVectOrientationVue().angleEntreVecteurs(Maths::vecteurEntreDeuxPoints(joueur->obtPosition(), it->obtPosition())) <= M_PI / 2)) {
				//if (Physique::obtInstance().collisionDroiteObjet(*it, VueJoueur, Vecteur3d(0, 0, 0), Vecteur3d(0, 0, 0))) {
				//if (Physique::obtInstance().collisionDroiteModele(it->obtModele3D(), VueJoueur, Vecteur3d(0, 0, 0), Vecteur3d(0, 0, 0), true)){
				std::string str1 = "Press ";
				str1.append(*GestionnaireControle::obtInstance().obtTouche((UTILISER)));

				if (it_Porte != nullptr){
					str1.append(" to open door.");
				}
				else if (it_Item != nullptr){
					str1.append(" to pick up ");
					str1.append(it_Item->obtNom());
				}
				//	const char* chr1 = str1.c_str();
				texte->defTexte(&str1);
				gfx::Gestionnaire2D::obtInstance().ajouterObjet(texte);
				objetDetecte = true;
				objetVise = it;
				//}
			}
		}

		if (!objetDetecte)
			gfx::Gestionnaire2D::obtInstance().retObjet(texte);
		return objetDetecte;
	}

public:

	PhaseJeu(Vecteur3d positionJoueur, double hAngle) : Phase(){
		joueur = new Joueur(positionJoueur, hAngle);
		joueur->defEtat(CHUTE);
		joueur->ajouterScene();

		GestionnairePhases::obtInstance().ajouterPhase(new PhaseMenuInventaire(joueur->obtInventaire()));

		texte = new gfx::Texte2D(new std::string("123"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("arial.ttf", 20), Vecteur2f(300, 200));
		toucheRelachee = false;

		cheminRecursif.push(Carte::obtInstance().salleActive->obtID());
		cheminLogique.push_back(Carte::obtInstance().salleActive->obtID());
		iterateur_x = 0;
		iterateur_z = 0;
		tempsJeu = Chrono();

		itemEquipe = nullptr;

		test = new Item(1, "Gun", "Allows you to shoot long range targets.", "fusilIcone.png", 1, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("luger.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("luger.png")), 0, "metal", 20);

		joueur->obtInventaire()->ajouterObjet(test);
		accesRapide = new MenuAccesRapide(joueur->obtInventaire());
		accesRapide->remplir();
		GestionnaireEvenements::obtInstance().ajouterUnRappel(SDL_KEYDOWN, std::bind(&PhaseJeu::toucheAppuyee, this, std::placeholders::_1));
		retour = false;
		pause = false;
	}

	void rafraichir(float frameTime) {
		if (pause)
			return;
		joueur->obtInventaire()->actualiser();
		itemEquipe = joueur->obtInventaire()->obtObjetAccesRapide(joueur->obtInventaire()->obtItemSelectionne());
		if (itemEquipe != nullptr){
			itemEquipe->actualiser(Carte::obtInstance().salleActive, joueur->obtVitesse().norme());
		}
		accesRapide->actualiserAffichage();

		if (Clavier::toucheAppuyee(SDLK_q)){
			if (itemEquipe != nullptr){
				itemEquipe->defEtat(EtatItem::DEPOSE);
				joueur->obtInventaire()->retirerObjetAccesRapide(joueur->obtInventaire()->obtItemSelectionne());
				itemEquipe = nullptr;
			}
		}
		if (!this->pause) {
			joueur->deplacement();
			appliquerPhysique(frameTime);
			ControlleurAudio::obtInstance().jouer(COEUR, joueur);
			ControlleurAudio::obtInstance().jouer(PAS, joueur);
			detectionObjet();
			ControlleurAudio::obtInstance().jouerTout(joueur);
			Carte::obtInstance().transitionSalle(joueur, frameTime);
		}

		if (detectionObjet()){
			if (Clavier::toucheRelachee(SDLK_e) && toucheRelachee){// Touche relach�e bient�t...
				if (objetVise->obtSiPorte()){
					Carte::obtInstance().destination(std::make_tuple(Carte::obtInstance().salleActive->obtID(), objetVise->obtID(), false), joueur);
					if (Carte::obtInstance().salleActive->obtID() != cheminRecursif.top()){
						for (int i = 0; i < cheminRecursif.size(); ++i)
							cheminRecursif.pop();
					}
					cheminRecursif.push(Carte::obtInstance().salleActive->obtID());
					cheminLogique.push_front(Carte::obtInstance().salleActive->obtID());
					santeMentale();
				}
				else if (dynamic_cast<Item*>(objetVise)){
					joueur->obtInventaire()->ajouterObjet((Item*)objetVise);
					objetVise = nullptr;
				}
				toucheRelachee = false;
			}
			if (Clavier::toucheAppuyee(SDLK_e))
				toucheRelachee = true;
		}

	}

	void toucheAppuyee(SDL_Event &event){
		if (pause)
			return;
		if (retour){
			retour = false;
			return;
		}
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			defPause(true);
			gfx::Gestionnaire3D::obtInstance().obtCamera()->bloquer();
			GestionnairePhases::obtInstance().defPhaseActive(MENUPAUSE);
			GestionnairePhases::obtInstance().obtPhaseActive()->defPause(false);
			GestionnairePhases::obtInstance().obtPhaseActive()->remplir();
			Curseur::defPosition(Vecteur2f(fenetre->obtTaille().x / 2, fenetre->obtTaille().y / 2));
			curseur->remplir();
		}
		if (event.key.keysym.sym == SDLK_TAB) {
			defPause(true);
			gfx::Gestionnaire3D::obtInstance().obtCamera()->bloquer();
			GestionnairePhases::obtInstance().defPhaseActive(MENUINVENTAIRE);
			GestionnairePhases::obtInstance().obtPhaseActive()->defPause(false);
			GestionnairePhases::obtInstance().obtPhaseActive()->remplir();
			Curseur::defPosition(Vecteur2f(fenetre->obtTaille().x / 2, fenetre->obtTaille().y / 2));
			curseur->remplir();
			accesRapide->vider();
		}
	}

	void remplir() {
		accesRapide->remplir();
	}

	void defPause(bool pause) {
		if (!pause)
			retour = true;
		this->pause = pause;
	}

	void actualiserEchelle(Vecteur2f vecteurEchelle) {
	}

	float obtTemps() {
		return tempsJeu.obtTempsEcoule().enSecondes();
	}
};

