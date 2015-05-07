#pragma once
#include <set>
#include <stdlib.h>
class Manette{
private:
	static SDL_GameController *manette;
	static SDL_Joystick* patron;
	static std::set<short> boutons;
	static std::set<int> orientation;
	static float positionGauchex;
	static float positionGauchey;
	static float positionDroitex;
	static float positionDroitey;
public:

	~Manette(){
		SDL_GameControllerClose(manette);
	}
	static bool ouvrirManette(){
		for (int i = 0; i < SDL_NumJoysticks(); ++i) {
			if (SDL_IsGameController(i)) {
				manette = SDL_GameControllerOpen(i);

				patron = SDL_GameControllerGetJoystick(manette);
			}
		}
		return manette == nullptr;

	}

	static void mettreAJourBoutons(){
		bool AButton = SDL_GameControllerGetButton(manette, SDL_CONTROLLER_BUTTON_A);
		bool BButton = SDL_GameControllerGetButton(manette, SDL_CONTROLLER_BUTTON_B);
		bool XButton = SDL_GameControllerGetButton(manette, SDL_CONTROLLER_BUTTON_X);
		bool YButton = SDL_GameControllerGetButton(manette, SDL_CONTROLLER_BUTTON_Y);
		bool ESCButton = SDL_GameControllerGetButton(manette, SDL_CONTROLLER_BUTTON_START);

		if (AButton)
			boutons.insert(SDL_CONTROLLER_BUTTON_A);
		else
			boutons.erase(SDL_CONTROLLER_BUTTON_A);
		if (BButton)
			boutons.insert(SDL_CONTROLLER_BUTTON_B);
		else
			boutons.erase(SDL_CONTROLLER_BUTTON_B);
		if (XButton)
			boutons.insert(SDL_CONTROLLER_BUTTON_X);
		else
			boutons.erase(SDL_CONTROLLER_BUTTON_X);
		if (YButton)
			boutons.insert(SDL_CONTROLLER_BUTTON_Y);
		else
			boutons.erase(SDL_CONTROLLER_BUTTON_Y);
		if (ESCButton)
			boutons.insert(SDL_CONTROLLER_BUTTON_START);
		else
			boutons.erase(SDL_CONTROLLER_BUTTON_START);

	}
	static void mettreAJourControleGauche(SDL_Event &event){

		if (event.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX)
			positionGauchex = (event.caxis.value) / 22000.0f;

		if (event.caxis.axis == SDL_CONTROLLER_AXIS_LEFTY)
			positionGauchey = (event.caxis.value) / 22000.0f;

	}
	static void mettreAJourControleDroite(SDL_Event &event){

		if (event.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTX)
			positionDroitex = (event.caxis.value) / 22000.0f;

		if (event.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTY)
			positionDroitey = (event.caxis.value) / 22000.0f;
	}
	static void verifierOrientationChapeau(SDL_Event &event){
		bool chapeauGauche;
		bool chapeauDroite;
		bool chapeauHaut;
		bool chapeauBas;

		switch (event.type)
		{
		case 1618:

			if (event.jhat.hat == 13)
				chapeauGauche = true;
			else
				chapeauGauche = false;

			if (event.jhat.hat == 11)
				chapeauHaut = true;
			else
				chapeauHaut = false;

			if (event.jhat.hat == 14)
				chapeauDroite = true;
			else
				chapeauDroite = false;

			if (event.jhat.hat == 12)
				chapeauBas = true;
			else
				chapeauBas = false;

			if (chapeauGauche)
				orientation.insert(0);
			else
				orientation.erase(0);
			if (chapeauHaut)
				orientation.insert(1);
			else
				orientation.erase(1);
			if (chapeauDroite)
				orientation.insert(2);
			else
				orientation.erase(2);
			if (chapeauBas)
				orientation.insert(3);
			else
				orientation.erase(3);

			break;
		}

	}

	static bool boutonAppuyer(short bouton){
		return boutons.find(bouton) != boutons.end();
	}
	static bool boutonRelacher(short bouton){
		return boutons.find(bouton) == boutons.end();
	}
	static bool orientationAppuyer(int i){
		return orientation.find(i) != orientation.end();
	}
	static bool orientationRelacher(int i){
		return orientation.find(i) == orientation.end();
	}
	static float obtenirPositionGaucheX(){
		return positionGauchex;
	}
	static float obtenirPositionGaucheY(){
		return positionGauchey;
	}
	static float obtenirPositionDroiteX(){
		return positionDroitex;
	}
	static float obtenirPositionDroiteY(){
		return positionDroitey;
	}
};
std::set<short> Manette::boutons;
std::set<int> Manette::orientation;
SDL_GameController* Manette::manette = NULL;
SDL_Joystick* Manette::patron = NULL;
float Manette::positionGauchex(0);
float Manette::positionGauchey(0);
float Manette::positionDroitex(0);
float Manette::positionDroitey(0);

