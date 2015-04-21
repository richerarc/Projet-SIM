#pragma once
#include "Menu.h"
#include "GestionnaireControle.h"
#include "GestionnairePhases.h"
#include "Phase.h"
#include "GestionnaireEvenements.h"


class MenuControle : public Menu {

private:
	gfx::Texte2D* Enregistrer;


	gfx::Texte2D* Avancer;
	gfx::Texte2D* Reculer;
	gfx::Texte2D* Droite;
	gfx::Texte2D* Gauche;
	gfx::Texte2D* Sauter;
	gfx::Texte2D* Accroupir;
	gfx::Texte2D* Courir;
	gfx::Texte2D* Tirer;
	gfx::Texte2D* Utiliser;
	gfx::Texte2D* Inventaire;

	gfx::Texte2D* CtrlAvancer;
	gfx::Texte2D* CtrlReculer;
	gfx::Texte2D* CtrlDroite;
	gfx::Texte2D* CtrlGauche;
	gfx::Texte2D* CtrlSauter;
	gfx::Texte2D* CtrlAccroupir;
	gfx::Texte2D* CtrlCourir;
	gfx::Texte2D* CtrlTirer;
	gfx::Texte2D* CtrlUtiliser;
	gfx::Texte2D* CtrlInventaire;

	Action action;
	gfx::Texte2D* toucheEnChoix;
	bool enChoixDeTouche;

public:

	MenuControle(void) : Menu() {

		this->SpriteFond = new gfx::Sprite2D(Vecteur2f(0, 0), &gfx::GestionnaireRessources::obtInstance().obtTexture("Joueur.png"));

		this->Retour = new gfx::Texte2D("Back", "arial.ttf", 55, Vecteur2f(100, 75));

		this->Enregistrer = new gfx::Texte2D("Save", "arial.ttf", 55, Vecteur2f(200, 75));

		Avancer = new gfx::Texte2D("Foward", "arial.ttf", 55, Vecteur2f(100, 755));
		CtrlAvancer = new gfx::Texte2D((char*)GestionnaireControle::obtInstance().obtenirControles()[AVANCER], "arial.ttf", 55, Vecteur2f(400, 755));

		Reculer = new gfx::Texte2D("Backward", "arial.ttf", 55, Vecteur2f(100, 687));
		CtrlReculer = new gfx::Texte2D((char*)GestionnaireControle::obtInstance().obtenirControles()[RECULER], "arial.ttf", 55, Vecteur2f(400, 687));

		Gauche = new gfx::Texte2D("Left", "arial.ttf", 55, Vecteur2f(100, 619));
		CtrlGauche = new gfx::Texte2D((char*)GestionnaireControle::obtInstance().obtenirControles()[GAUCHE], "arial.ttf", 55, Vecteur2f(400, 619));

		Droite = new gfx::Texte2D("Right", "arial.ttf", 55, Vecteur2f(100, 551));
		CtrlGauche = new gfx::Texte2D((char*)GestionnaireControle::obtInstance().obtenirControles()[DROITE], "arial.ttf", 55, Vecteur2f(400, 551));

		Sauter = new gfx::Texte2D("Jump", "arial.ttf", 55, Vecteur2f(100, 483));
		CtrlGauche = new gfx::Texte2D((char*)GestionnaireControle::obtInstance().obtenirControles()[SAUTER], "arial.ttf", 55, Vecteur2f(400, 483));

		Accroupir = new gfx::Texte2D("Crouch", "arial.ttf", 55, Vecteur2f(100, 415));
		CtrlGauche = new gfx::Texte2D((char*)GestionnaireControle::obtInstance().obtenirControles()[ACCROUPIR], "arial.ttf", 55, Vecteur2f(400, 415));

		Courir = new gfx::Texte2D("Run", "arial.ttf", 55, Vecteur2f(100, 347));
		CtrlGauche = new gfx::Texte2D((char*)GestionnaireControle::obtInstance().obtenirControles()[COURIR], "arial.ttf", 55, Vecteur2f(400, 347));

		Tirer = new gfx::Texte2D("Shoot", "arial.ttf", 55, Vecteur2f(100, 279));
		CtrlTirer = new gfx::Texte2D((char*)GestionnaireControle::obtInstance().obtenirControles()[TIRER], "arial.ttf", 55, Vecteur2f(400, 279));

		Utiliser = new gfx::Texte2D("Use/Equip", "arial.ttf", 55, Vecteur2f(100, 211));
		CtrlUtiliser = new gfx::Texte2D((char*)GestionnaireControle::obtInstance().obtenirControles()[UTILISER], "arial.ttf", 55, Vecteur2f(400, 211));

		Inventaire = new gfx::Texte2D("Inventory", "arial.ttf", 55, Vecteur2f(100, 143));
		CtrlInventaire = new gfx::Texte2D((char*)GestionnaireControle::obtInstance().obtenirControles()[INVENTAIRE], "arial.ttf", 55, Vecteur2f(400, 143));

		gfx::Gestionnaire2D::obtInstance().ajouterObjets({ this->SpriteFond, this->Retour, this->Enregistrer, Avancer, CtrlAvancer, Reculer, CtrlReculer,
			Gauche, CtrlGauche, Droite, CtrlDroite, Sauter, CtrlSauter, Accroupir, CtrlAccroupir, Courir, CtrlCourir, Tirer, CtrlTirer, Utiliser, CtrlUtiliser,
			Inventaire, CtrlInventaire });

		GestionnaireEvenements::obtInstance().ajouterUnRappel(SDL_KEYDOWN, std::bind(&MenuControle::gererEvenement, this, std::placeholders::_1));

	}
	~MenuControle(void) {
		gfx::Gestionnaire2D::obtInstance().vider();
	}

	void actualiser(void) {
		
		if (this->Retour->obtRectangle().contient(Souris::obtPosition().x, Souris::obtPosition().y)) {
			this->Retour->defCouleur({ 255, 0, 0, 255 });
			if (Souris::boutonAppuye(SDL_BUTTON_LEFT)) {
				GestionnairePhases::obtInstance().retirerPhase();
				gfx::Gestionnaire2D::obtInstance().vider();
				GestionnairePhases::obtInstance().ajouterPhase(new PhaseMenuOptions);
			}
		}
		else {
			this->Retour->defCouleur({ 255, 255, 255, 255 });
		}

												//ENREGISTRER ...
		if (Enregistrer->obtRectangle().contient(Souris::obtPosition().x, Souris::obtPosition().y)) {
			this->Retour->defCouleur({ 255, 0, 0, 255 });
			if (Souris::boutonAppuye(SDL_BUTTON_LEFT)) {
				GestionnaireControle::obtInstance().sauvegarderControle("Controles.txt");
			}
		}
		else {
			Enregistrer->defCouleur({ 255, 255, 255, 255 });
		}

												//AVANCER ...
		if (CtrlAvancer->obtRectangle().contient(Souris::obtPosition().x, Souris::obtPosition().y)) {
			CtrlAvancer->defCouleur({ 255, 0, 0, 255 });
			if (Souris::boutonAppuye(SDL_BUTTON_LEFT)) {
				action = AVANCER;
				CtrlAvancer->defTexte("Press any key ...");
				toucheEnChoix = CtrlAvancer;
			}
		}
		else{
			CtrlAvancer->defCouleur({ 255, 255, 255, 255 });
		}
												//RECULER ....
		if (CtrlReculer->obtRectangle().contient(Souris::obtPosition().x, Souris::obtPosition().y)) {
			CtrlReculer->defCouleur({ 255, 0, 0, 255 });
			if (Souris::boutonAppuye(SDL_BUTTON_LEFT)) {
				action = RECULER;
				CtrlReculer->defTexte("Press any key ...");
				toucheEnChoix = CtrlReculer;
			}
		}
		else {
			CtrlReculer->defCouleur({ 255, 255, 255, 255 });
		}
											//GAUCHE ....
		if (CtrlGauche->obtRectangle().contient(Souris::obtPosition().x, Souris::obtPosition().y)) {
			CtrlGauche->defCouleur({ 255, 0, 0, 255 });
			if (Souris::boutonAppuye(SDL_BUTTON_LEFT)) {
				action = GAUCHE;
				CtrlGauche->defTexte("Press any key ...");
				toucheEnChoix = CtrlGauche;
			}
		}
		else {
			CtrlGauche->defCouleur({ 255, 255, 255, 255 });
		}

											//DROITE ....
		if (CtrlDroite->obtRectangle().contient(Souris::obtPosition().x, Souris::obtPosition().y)) {
			CtrlDroite->defCouleur({ 255, 0, 0, 255 });
			if (Souris::boutonAppuye(SDL_BUTTON_LEFT)) {
				action = DROITE;
				CtrlDroite->defTexte("Press any key ...");
				toucheEnChoix = CtrlDroite;
			}
		}
		else {
			CtrlDroite->defCouleur({ 255, 255, 255, 255 });
		}

											//SAUTER ....
		if (CtrlSauter->obtRectangle().contient(Souris::obtPosition().x, Souris::obtPosition().y)) {
			CtrlSauter->defCouleur({ 255, 0, 0, 255 });
			if (Souris::boutonAppuye(SDL_BUTTON_LEFT)) {
				action = SAUTER;
				CtrlSauter->defTexte("Press any key ...");
				toucheEnChoix = CtrlSauter;
			}
		}
		else {
			CtrlSauter->defCouleur({ 255, 255, 255, 255 });
		}

											//ACCROUPIR ....
		if (CtrlAccroupir->obtRectangle().contient(Souris::obtPosition().x, Souris::obtPosition().y)) {
			CtrlAccroupir->defCouleur({ 255, 0, 0, 255 });
			if (Souris::boutonAppuye(SDL_BUTTON_LEFT)) {
				action = ACCROUPIR;
				CtrlAccroupir->defTexte("Press any key ...");
				toucheEnChoix = CtrlAccroupir;
			}
		}
		else {
			CtrlAccroupir->defCouleur({ 255, 255, 255, 255 });
		}

											//COURIR ....
		if (CtrlCourir->obtRectangle().contient(Souris::obtPosition().x, Souris::obtPosition().y)) {
			CtrlCourir->defCouleur({ 255, 0, 0, 255 });
			if (Souris::boutonAppuye(SDL_BUTTON_LEFT)) {
				action = COURIR;
				CtrlCourir->defTexte("Press any key ...");
				toucheEnChoix = CtrlCourir;
			}
		}
		else {
			CtrlCourir->defCouleur({ 255, 255, 255, 255 });
		}

										   //TIRER ...
		if (CtrlTirer->obtRectangle().contient(Souris::obtPosition().x, Souris::obtPosition().y)) {
			CtrlTirer->defCouleur({ 255, 0, 0, 255 });
			if (Souris::boutonAppuye(SDL_BUTTON_LEFT)) {
				action = TIRER;
				CtrlTirer->defTexte("Press any key ...");
				toucheEnChoix = CtrlTirer;
			}
		}
		else {
			CtrlTirer->defCouleur({ 255, 255, 255, 255 });
		}


											//UTILISER ....
		if (CtrlUtiliser->obtRectangle().contient(Souris::obtPosition().x, Souris::obtPosition().y)) {
			CtrlUtiliser->defCouleur({ 255, 0, 0, 255 });
			if (Souris::boutonAppuye(SDL_BUTTON_LEFT)) {
				action = UTILISER;
				CtrlUtiliser->defTexte("Press any key ...");
				toucheEnChoix = CtrlUtiliser;
			}
		}
		else {
			CtrlUtiliser->defCouleur({ 255, 255, 255, 255 });
		}


											//INVENTAIRE ....
		if (CtrlInventaire->obtRectangle().contient(Souris::obtPosition().x, Souris::obtPosition().y)) {
			CtrlInventaire->defCouleur({ 255, 0, 0, 255 });
			if (Souris::boutonAppuye(SDL_BUTTON_LEFT)) {
				action = INVENTAIRE;
				CtrlInventaire->defTexte("Press any key ...");
				toucheEnChoix = CtrlInventaire;
			}
		}
		else {
			CtrlInventaire->defCouleur({ 255, 255, 255, 255 });
		}



	}

	void gererEvenement(SDL_Event Event){
		if (enChoixDeTouche) {
			toucheEnChoix->defTexte = (char*)Event.key.keysym.sym;
			GestionnaireControle::obtInstance().definirControle(action, Event.key.keysym.sym);
			enChoixDeTouche = false;
			toucheEnChoix = nullptr;
		}
	}
	


};