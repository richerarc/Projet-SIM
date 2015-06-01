#pragma once
#include "Gestionnaire3D.h"
#include "Vecteur3.h"
#include "Plan.h"
#include "GestionnaireControle.h"
#include "Inventaire.h"

enum etatDynamique { STABLE, CHUTE };
enum etatStatique { DEBOUT, ACCROUPI };
class Joueur {
private:
	gfx::Modele3D* modele3D;
	gfx::Camera* camera;
	gfx::Modele3D* listeModele3D[2];
	Vecteur3d position;
	Vecteur3d vitesse;
	double masse;
	float vitesseDeplacement;
	short etatDynamique, etatStatique;
	short santePhysique, santeMentale;
	Vecteur3d normale;
	Vecteur3d pointCollision;
	bool bloque, saoul;
	Chrono chronoSaut, chronoAlcoolemie;
	Inventaire* inventaire;
	Vecteur3d normaleMur;

	Chrono antiIdle;
	double dernierVAngle;

	/*y=-(Ax+Cz+d)/B */
	void ajusterVitesse(){
		Plan plan(pointCollision, normale);
		double B = plan.obtenirNormale().y;
		if (B){
			double A = plan.obtenirNormale().x;
			double x = vitesse.x;
			double C = plan.obtenirNormale().z;
			double z = vitesse.z;
			double d = plan.obtenirD();
			double y = -(((A * x) + (C * z) + d) / B);
			vitesse.y = y;
			Vecteur3d vitesseTemp = vitesse;
			vitesseTemp.normaliser();
			vitesseTemp *= vitesseDeplacement;
			vitesse.y = vitesseTemp.y;
		}
	}

public:

	Joueur() {}

	Joueur(Vecteur3d position, double hAngle, double vAngle) {
		this->vitesseDeplacement = 4.f;
		this->position = position;
		etatDynamique = CHUTE;
		etatStatique = DEBOUT;
		masse = 87.f;
		santePhysique = 100;
		santeMentale = 100;
		vitesse = { 0, 0, 0 };
		camera = new gfx::Camera;
		listeModele3D[DEBOUT] = new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/Joueur.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/Joueur.png"));
		listeModele3D[ACCROUPI] = new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/JoueurAccroupi.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/Joueur.png"));
		ajouterScene();
		modele3D = listeModele3D[DEBOUT];
		listeModele3D[DEBOUT]->defPosition(position);
		listeModele3D[ACCROUPI]->defPosition(position);
		chronoSaut = Chrono();
		position.y += 1.74;
		camera->defPosition(position);
		modele3D = listeModele3D[DEBOUT];
		camera->defHAngle(hAngle);
		camera->defVAngle(vAngle);
		chronoSaut = Chrono();
		inventaire = new Inventaire(Vecteur2f(9, 3));
		bloquer();
		saoul = false;
	}

	~Joueur() {
		delete camera;
		delete listeModele3D[0];
		delete listeModele3D[1];
		delete inventaire;
	}

	void deplacement(){
		camera->rafraichir();
		if (!bloque){
			if ((Clavier::toucheRelachee(GestionnaireControle::obtInstance().touche(AVANCER)) || Clavier::toucheRelachee(GestionnaireControle::obtInstance().touche(RECULER)) || Clavier::toucheRelachee(GestionnaireControle::obtInstance().touche(GAUCHE)) || Clavier::toucheRelachee(GestionnaireControle::obtInstance().touche(DROITE)) || Manette::orientationRelacher(SDL_CONTROLLER_BUTTON_DPAD_UP) || Manette::orientationRelacher(SDL_CONTROLLER_BUTTON_DPAD_DOWN) || Manette::orientationRelacher(SDL_CONTROLLER_BUTTON_DPAD_LEFT) || Manette::orientationRelacher(SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) && (etatDynamique == STABLE)){
				vitesse.x = 0.f;
				vitesse.z = 0.f;
				if (vitesse.y == 0)
					vitesse.y = 0.f;
			}

			if (etatDynamique == CHUTE && vitesse.x == 0 && vitesse.y == 0 && vitesse.z == 0){
				etatDynamique = STABLE;
			}

			Vecteur3d devant = camera->obtDevant();
			devant.y = 0;
			Vecteur3d cote = camera->obtCote();
			devant.normaliser();
			cote.y = 0;
			if (saoul){
				double temps = chronoAlcoolemie.obtTempsEcoule().enSecondes();
				if (temps < 120){
					double sinT4 = sin(temps) / 4;
					camera->defHAngle(camera->obtHAngle() + sinT4);
					camera->defVAngle(camera->obtVAngle() - sin(temps / 2) / 8 - sinT4);
				}
				else
					saoul = false;
			}
			Vecteur3d vitesseTemp;
			if ((Clavier::toucheRelachee(GestionnaireControle::obtInstance().touche(COURIR)) && Manette::boutonRelacher(SDL_CONTROLLER_BUTTON_LEFTSHOULDER)) && (vitesseDeplacement != 4.f) && (etatStatique == DEBOUT || etatStatique == ACCROUPI)) {
				if (etatStatique == DEBOUT)
					vitesseDeplacement = 4.f;
				else
					vitesseDeplacement = 2.f;
			}

			if (etatDynamique != CHUTE) {

				if ((Clavier::toucheAppuyee(GestionnaireControle::obtInstance().touche(COURIR)) || Manette::boutonAppuyer(SDL_CONTROLLER_BUTTON_LEFTSHOULDER)) && (etatStatique == DEBOUT) && vitesseDeplacement != 8.f)
					vitesseDeplacement = 10.f;

				else if ((Clavier::toucheAppuyee(GestionnaireControle::obtInstance().touche(ACCROUPIR)) || Manette::boutonAppuyer(SDL_CONTROLLER_BUTTON_B)) && (etatStatique == DEBOUT)) {
					modele3D = listeModele3D[ACCROUPI];
					etatStatique = ACCROUPI;
					camera->defPosition(Vecteur3d(position.x, position.y + 1.00f, position.z));
					vitesseDeplacement = 2.f;
				}

				else if (Clavier::toucheRelachee(GestionnaireControle::obtInstance().touche(ACCROUPIR)) && Manette::boutonRelacher(SDL_CONTROLLER_BUTTON_B) && etatStatique == ACCROUPI) {
					modele3D = listeModele3D[DEBOUT];
					ajouterScene();
					etatStatique = DEBOUT;
					camera->defPosition(Vecteur3d(position.x, position.y + 1.74f, position.z));
					vitesseDeplacement = 4.f;
				}

				if (Clavier::toucheAppuyee(GestionnaireControle::obtInstance().touche(AVANCER)) || Manette::orientationAppuyer(SDL_CONTROLLER_BUTTON_DPAD_UP)) {
					vitesse = devant * vitesseDeplacement;
					if (Clavier::toucheAppuyee(GestionnaireControle::obtInstance().touche(DROITE)) || Manette::orientationAppuyer(SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) {
						vitesse = vitesse + (cote * vitesseDeplacement);
						vitesse.normaliser();
						vitesse *= vitesseDeplacement;
					}

					else if (Clavier::toucheAppuyee(GestionnaireControle::obtInstance().touche(GAUCHE)) || Manette::orientationAppuyer(SDL_CONTROLLER_BUTTON_DPAD_LEFT)) {
						vitesseTemp = cote * vitesseDeplacement;
						vitesseTemp.inverser();
						vitesse = vitesse + vitesseTemp;
						vitesse.normaliser();
						vitesse *= vitesseDeplacement;
					}
				}

				else if (Clavier::toucheAppuyee(GestionnaireControle::obtInstance().touche(RECULER)) || Manette::orientationAppuyer(SDL_CONTROLLER_BUTTON_DPAD_DOWN)) {
					if (vitesseDeplacement == 10.f)
						vitesseDeplacement = 5.f;
					vitesse = devant * vitesseDeplacement;
					vitesse.inverser();
					if (Clavier::toucheAppuyee(GestionnaireControle::obtInstance().touche(DROITE)) || Manette::orientationAppuyer(SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) {
						if (vitesseDeplacement == 5.f)
							vitesseDeplacement = 4.f;
						vitesse = vitesse + (cote * vitesseDeplacement);
						vitesse.normaliser();
						vitesse *= vitesseDeplacement;
					}

					else if (Clavier::toucheAppuyee(GestionnaireControle::obtInstance().touche(GAUCHE)) || Manette::orientationAppuyer(SDL_CONTROLLER_BUTTON_DPAD_LEFT)) {
						if (vitesseDeplacement == 5.f)
							vitesseDeplacement = 4.f;
						vitesseTemp = cote * vitesseDeplacement;
						vitesseTemp.inverser();
						vitesse = vitesse + vitesseTemp;
						vitesse.normaliser();
						vitesse *= vitesseDeplacement;
					}
				}

				else if (Clavier::toucheAppuyee(GestionnaireControle::obtInstance().touche(GAUCHE)) || Manette::orientationAppuyer(SDL_CONTROLLER_BUTTON_DPAD_LEFT)) {
					if (vitesseDeplacement >= 8.f)
						vitesseDeplacement = 5.f;
					vitesseTemp = cote * vitesseDeplacement;
					vitesseTemp.inverser();
					vitesse = vitesse + vitesseTemp;
				}

				else if (Clavier::toucheAppuyee(GestionnaireControle::obtInstance().touche(DROITE)) || Manette::orientationAppuyer(SDL_CONTROLLER_BUTTON_DPAD_RIGHT)){
					if (vitesseDeplacement >= 8.f)
						vitesseDeplacement = 5.f;
					vitesse = vitesse + (cote * vitesseDeplacement);
				}

				if (((normale.x != 0.f || normale.z != 0.f) && (normale.y != 0.f))) {
					if (vitesse.produitScalaire(normale) > 0.f) {
						ajusterVitesse();
						if (vitesse.y > 0.f) {
							vitesse.y *= -1;
						}
					}
				}

				if ((Clavier::toucheAppuyee(GestionnaireControle::obtInstance().touche(SAUTER)) || Manette::boutonAppuyer(SDL_CONTROLLER_BUTTON_A)) && (etatStatique == DEBOUT)) {
					if ((chronoSaut.obtTempsEcoule().enSecondes() > 1)){
						chronoSaut.repartir();
						vitesse.y = 5;
						etatDynamique = CHUTE;
					}
				}
			}
			listeModele3D[DEBOUT]->defOrientation(0, (camera->obtHAngle()), 0);
			listeModele3D[ACCROUPI]->defOrientation(0, (camera->obtHAngle()), 0);
			if ((Clavier::toucheRelachee(GestionnaireControle::obtInstance().touche(AVANCER)) &&
				Clavier::toucheRelachee(GestionnaireControle::obtInstance().touche(RECULER)) &&
				Clavier::toucheRelachee(GestionnaireControle::obtInstance().touche(GAUCHE)) &&
				Clavier::toucheRelachee(GestionnaireControle::obtInstance().touche(DROITE)) &&
				Manette::orientationRelacher(SDL_CONTROLLER_BUTTON_DPAD_UP) &&
				Manette::orientationRelacher(SDL_CONTROLLER_BUTTON_DPAD_DOWN) &&
				Manette::orientationRelacher(SDL_CONTROLLER_BUTTON_DPAD_LEFT) &&
				Manette::orientationRelacher(SDL_CONTROLLER_BUTTON_DPAD_RIGHT)))
				vitesseDeplacement = 0;
		}
		
		if (vitesseDeplacement == 0 && !camera->obtChangement()){
			defVAngle(dernierVAngle + 0.02 * sin(antiIdle.obtTempsEcoule().enSecondes()));
		}
		else{
			dernierVAngle = camera->obtVAngle();
		}
	}

	void longer(){
		Vecteur3d direction1;
		Vecteur3d direction2;
		Vecteur3d vitesseNormalisee;
		direction1.x = -normaleMur.z;
		direction1.y = 0.f;
		direction1.z = normaleMur.x;
		direction2.x = normaleMur.z;
		direction2.y = 0.f;
		direction2.z = -normaleMur.x;
		vitesseNormalisee = vitesse;
		vitesseNormalisee.y = 0;
		vitesseNormalisee.normaliser();
		bool droit = false;
		if (normaleMur.x == 0. || normaleMur.z == 0.){
			droit = true;
			if (normaleMur.x == 0.){
				if (normaleMur.z == 1.){
					if (vitesse.x > 0.){
						vitesse.x = direction2.x * vitesseDeplacement;
						vitesse.z = direction2.z * vitesseDeplacement;
					}
					else{
						vitesse.x = direction1.x * vitesseDeplacement;
						vitesse.z = direction1.z * vitesseDeplacement;
					}
				}
				else{
					if (vitesse.x > 0.){
						vitesse.x = direction1.x * vitesseDeplacement;
						vitesse.z = direction1.z * vitesseDeplacement;
					}
					else{
						vitesse.x = direction2.x * vitesseDeplacement;
						vitesse.z = direction2.z * vitesseDeplacement;
					}
				}
			}
			if (normaleMur.z == 0.){
				if (normaleMur.x == 1.){
					if (vitesse.z > 0.){
						vitesse.x = direction1.x * vitesseDeplacement;
						vitesse.z = direction1.z * vitesseDeplacement;
					}
					else{
						vitesse.x = direction2.x * vitesseDeplacement;
						vitesse.z = direction2.z * vitesseDeplacement;
					}
				}
				else{
					if (vitesse.z > 0.){
						vitesse.x = direction2.x * vitesseDeplacement;
						vitesse.z = direction2.z * vitesseDeplacement;
					}
					else{
						vitesse.x = direction1.x * vitesseDeplacement;
						vitesse.z = direction1.z * vitesseDeplacement;
					}
				}
			}
		}
		if (!((vitesseNormalisee.x == direction1.x && vitesseNormalisee.z == direction1.z) || (vitesseNormalisee.x == direction2.x && vitesseNormalisee.z == direction2.z)) && !droit){

			if ((normaleMur.x <= 0. && normaleMur.z >= 0. && vitesseNormalisee.x > direction2.x && vitesseNormalisee.z < direction2.z) ||
				(normaleMur.x >= 0. && normaleMur.z >= 0. && vitesseNormalisee.x < direction2.x && vitesseNormalisee.z < direction2.z) ||
				(normaleMur.x <= 0. && normaleMur.z <= 0. && vitesseNormalisee.x > direction2.x && vitesseNormalisee.z > direction2.z) ||
				(normaleMur.x >= 0. && normaleMur.z <= 0. && vitesseNormalisee.x < direction2.x && vitesseNormalisee.z > direction2.z)
				){
				vitesse.x = direction2.x * vitesseDeplacement;
				vitesse.z = direction2.z * vitesseDeplacement;
			}
			else {
				if ((normaleMur.x <= 0. && normaleMur.z >= 0. && vitesseNormalisee.x >= direction1.x && vitesseNormalisee.z <= direction1.z) ||
					(normaleMur.x >= 0. && normaleMur.z >= 0. && vitesseNormalisee.x <= direction1.x && vitesseNormalisee.z <= direction1.z) ||
					(normaleMur.x <= 0. && normaleMur.z <= 0. && vitesseNormalisee.x >= direction1.x && vitesseNormalisee.z >= direction1.z) ||
					(normaleMur.x >= 0. && normaleMur.z <= 0. && vitesseNormalisee.x <= direction1.x && vitesseNormalisee.z >= direction1.z)
					){
					vitesse.x = direction1.x * vitesseDeplacement;
					vitesse.z = direction1.z * vitesseDeplacement;
				}
				else{
					vitesse.x = direction2.x * vitesseDeplacement;
					vitesse.z = direction2.z * vitesseDeplacement;
				}
			}
		}
	}

	void ajouterScene(){ gfx::Gestionnaire3D::obtInstance().defCamera(camera); }

	void defVitesseY(double y){ this->vitesse.y = y; }

	void defVitesse(Vecteur3d vitesse) { this->vitesse = vitesse; }

	void defPosition(Vecteur3d pos){
		this->position = pos;
		this->listeModele3D[ACCROUPI]->defPosition(position);
		this->listeModele3D[DEBOUT]->defPosition(position);
		if (etatStatique == DEBOUT)
			camera->defPosition(Vecteur3d(position.x, position.y + 1.74f, position.z));
		else
			camera->defPosition(Vecteur3d(position.x, position.y + 1.00f, position.z));
	}

	void defPositionY(double y) {
		this->position.y = y;
		this->modele3D->defPosition(position);
		if (etatStatique == DEBOUT)
			camera->defPosition(Vecteur3d(position.x, position.y + 1.74f, position.z));
		else
			camera->defPosition(Vecteur3d(position.x, position.y + 1.00f, position.z));
	}

	void defPointCollision(Vecteur3d pointCollision){ this->pointCollision = pointCollision; }

	void defNormale(Vecteur3d normale){ this->normale = normale; }

	void defNormaleMur(Vecteur3d normaleMur){ this->normaleMur = normaleMur; }

	void defHAngle(double hAngle){ camera->defHAngle(hAngle); }

	void defVAngle(double vAngle) { camera->defVAngle(vAngle); }

	void defEtat(unsigned int etatDynamique){ if (etatDynamique <= 5) this->etatDynamique = etatDynamique; }

	void defDevant(Vecteur3d devant) { camera->defDevant(devant); }

	void bloquer(){
		this->bloque = true;
		camera->bloquer();
	}

	void deBloquer(){
		this->bloque = false;
		camera->deBloquer();
	}

	void saouler(){
		saoul = true;
		santeMentale += 10;
		chronoAlcoolemie.repartir();
	}

	gfx::Modele3D* obtModele3D() { return modele3D; }

	bool obtBloque(){ return bloque; }

	double obtHAngle(){ return camera->obtHAngle(); }

	double obtVAngle(){ return camera->obtVAngle(); }

	Vecteur3d& obtNormale(){ return this->normale; }

	Vecteur3d& obtNormaleMur(){ return this->normaleMur; }

	Vecteur3d obtPositionCamera(){ return camera->obtPosition(); }

	void defSantePhysique(short santePhysique) { this->santePhysique = santePhysique; if (this->santePhysique > 100) this->santePhysique = 100; }

	void defSanteMentale(short santeMentale) { this->santeMentale = santeMentale; if (this->santeMentale > 100)this->santeMentale = 100; }

	short obtSantePhysique(){ return santePhysique; }

	short obtSanteMentale(){ return santeMentale; }

	Vecteur3d& obtPointCollision(){ return this->pointCollision; }

	Vecteur3d& obtPosition(){ return this->position; }

	Vecteur3d& obtVitesse(){ return this->vitesse; }

	double obtMasse(){ return masse; }

	float obtVitesseDeplacement(){ return vitesseDeplacement; }

	short obtEtat(){ return etatDynamique; }

	Vecteur3d obtDevant() { return camera->obtDevant(); }
	Vecteur3d obtHaut() { return camera->obtHaut(); }
	Vecteur3d obtCote() { return camera->obtCote(); }
	Inventaire* obtInventaire(){ return this->inventaire; }
};
