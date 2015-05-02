#pragma once
#include <set>
class Manette{
private:
	static SDL_GameController *manette;
	static SDL_Joystick* patron;
	static std::set<short> boutons;
public:

	~Manette(){
		SDL_GameControllerClose(manette);
	}
	static	void ouvrirManette(){
		for (int i = 0; i < SDL_NumJoysticks(); ++i) {
			if (SDL_IsGameController(i)) {
				manette = SDL_GameControllerOpen(i);
				patron = SDL_GameControllerGetJoystick(manette);
				break;
			}
		}
	}

	static void mettreAJourEtat(){

		bool AButton = SDL_GameControllerGetButton(manette, SDL_CONTROLLER_BUTTON_A);
		bool BButton = SDL_GameControllerGetButton(manette, SDL_CONTROLLER_BUTTON_B);
		bool XButton = SDL_GameControllerGetButton(manette, SDL_CONTROLLER_BUTTON_X);
		bool YButton = SDL_GameControllerGetButton(manette, SDL_CONTROLLER_BUTTON_Y);
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
	}

	static bool boutonAppuyer(short bouton){
		return boutons.find(bouton) != boutons.end();
	}

	static bool boutonRelacher(short bouton){
		return boutons.find(bouton) == boutons.end();
	}

};
std::set<short> Manette::boutons;
SDL_GameController* Manette::manette = NULL;
SDL_Joystick* Manette::patron = NULL;