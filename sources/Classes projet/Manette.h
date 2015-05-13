#pragma once
#include <set>
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
				patron = SDL_JoystickOpen(i);
				break;
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

	static void mettreAJourEtat(short orientations, bool etat){
		if (etat)
			orientation.insert(orientations);
		else
			orientation.erase(orientations);
	}

	//static void verifierOrientationControleGauche(SDL_Event &event){
	//	if (event.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX){
	//		if (event.caxis.value > 0)
	//			orientation.insert(0);
	//		else
	//			orientation.erase(0);
	//		if (event.caxis.value < 0)
	//			orientation.insert(1);
	//		else
	//			orientation.erase(1);
	//		
	//	}
	//	if (event.caxis.axis == SDL_CONTROLLER_AXIS_LEFTY){
	//		if (event.caxis.value > 0)
	//			orientation.insert(2);
	//		else
	//			orientation.erase(2);
	//		if (event.caxis.value < 0)
	//			orientation.insert(3);
	//		else
	//			orientation.erase(3);
	//	}
	//}

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
