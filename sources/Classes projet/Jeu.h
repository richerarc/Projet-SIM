#pragma once
//#include <math.h>
//#include <list>
//#include <vector>
//#include <queue>
//#include <string>
//#include <map>
//#include <iostream>
//#include <algorithm>
//#include <chrono>
//#include <tuple>
//#include <set>
//#include <functional>
//#include <fstream>
//
//
//#include "Vecteur2.h"
//#include "Vecteur3.h"
//#include "Maths.h"
//#include "Graphe.h"
//
//#include "Souris.h"
//#include "Clavier.h"
//#include "Fenetre.h"
//#include "Singleton.h"
//#include "Texture.h"
//#include "Modele.h"
//
//#include "Temps.h"
//#include "Chrono.h"
//
//
//#include "Objet.h"
//
//#include "Camera.h"
//#include "CameraGodMode.h"
//
//
//#include "Fenetre.h"
#include "Gestionnaire2D.h"
#include "Gestionnaire3D.h"
//#include "GestionnaireRessources.h"
//#include "GestionnaireLiens.h"
#include "GestionnaireEvenements.h"


class Jeu{

public:

private:
	static gfx::Fenetre fenetre;
	static SDL_Event evenement;

	

public:


	static void demarrer(){
		fenetre = gfx::Fenetre(gfx::ModeVideo(500, 500), "CoffeeTrip", false);
		while (fenetre.estOuverte()){

			while (fenetre.sonderEvenements(evenement)){
				if (evenement.type == SDL_QUIT)
					fenetre.fermer();
			}

			fenetre.vider();

			//Affichages

			fenetre.rafraichir();

		}
	}
};
