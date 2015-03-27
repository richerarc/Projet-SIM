/*
Bienvenu dans l'engine de teste pour la physique les sections importantes pour le main ont été marquées par une suite de point,
Voici une liste des obj présent dans le fichier:
-plan.obj
-plancroche.obj
-sphere.obj
Chaque obj doit être accompsgné d'une texture qui lui est respective sinon ca plante! Have Fun!
*/




#include <iostream>
#include <SDL2\SDL.h>
#include <SDL2\SDL_opengl.h>
#include <map>

#include "Window.h"
#include "Camera.h"
#include "Vecteur3.h"
#include "Modele3D.h"
#include "GestionnaireRessources.h"
#include "Objet.h"
#include "ObjetPhysique.h"
#include "Vent.h"
#include "ObjetFixe.h"
#include "Aimant.h"


int main(int argc, char** argv){
	Window window(sdl::VideoMode(800, 600), "OpenGL Test", false);

	double HautY =  30 * M_PI / 180;
	double DroitX = HautY * (1.3333);
	glMatrixMode(GL_PROJECTION); // Matrice de projection.
	glLoadIdentity();
	glFrustum(-DroitX, DroitX, -HautY, HautY, 0.99, 100);

	glEnable(GL_TEXTURE_2D);

	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDisable(GL_CULL_FACE);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	Camera cam(Vecteur3f(0, 0, 2), Vecteur3f(0, 0, 0), Vecteur3f(0, 1, 0));
	// Mettre les objets ICI:......................................................................................................................................................................
	gfx::Modele3D modele3Dobjet(&gfx::GestionnaireRessources::obtInstance().obtModele("sphere.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("sphere.png"));
	gfx::Modele3D modele3Dplan(&gfx::GestionnaireRessources::obtInstance().obtModele("plan.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("plan.png"));
	gfx::Modele3D modele3Daimant(&gfx::GestionnaireRessources::obtInstance().obtModele("sphere.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("sphere.png"));

	Objet* objet = new ObjetPhysique(modele3Dobjet, 1, "metal", 10, { 0, 0, -2 });
	Objet* vent = new Vent({ 10, 0, 0 }, 3, { -10, -10, -10 }, { 20, 20, 20 });
	Objet* plan = new ObjetFixe(modele3Dplan, 2, "metal", { 0, 0, -6 });
	Objet* aimant = new Aimant(modele3Daimant, 4, { 0, 5, -5 }, 000);
	// Définir les propriétées des objets ici:.....................................................................................................................................................
	objet->defVitesse({ 0, 0, 0 });
	std::list<Objet*> listeObjet;
	listeObjet.push_front(objet);
	listeObjet.push_front(vent);
	listeObjet.push_front(plan);
	listeObjet.push_front(aimant);


	//glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	Chrono bacon;
	Chrono update;
	while (window.isOpen()){
		float frametime = bacon.repartir().enSecondes();
		Physique::obtInstance().repartirTemps();
		if (update.obtTempsEcoule().enSecondes() >= 0.5){
			std::cout << 1 / frametime << std::endl;
			update.repartir();
		}
		SDL_Event event;
		while (window.pollEvent(event)){
			if (event.type == SDL_QUIT)
				window.close();
		}
		window.clear();
		glLoadIdentity();
		//Application de la Physique:.............................................................................................................................................................

		for (auto it : listeObjet) {
			it->appliquerPhysique(listeObjet);
		}

		if (frametime) {
			objet.defPosition(objet.obtPosition() + (objet.obtVitesse() * frametime));
		}
		
		if (Clavier::toucheAppuyee(SDLK_w)){
		}
		if (Clavier::toucheAppuyee(SDLK_s)){
		}
		if (Clavier::toucheAppuyee(SDLK_d)){
		}
		if (Clavier::toucheAppuyee(SDLK_a)){
		}

		if (Clavier::toucheAppuyee(SDLK_UP)){
		}
		if (Clavier::toucheAppuyee(SDLK_DOWN)){
		}

		if (Clavier::toucheAppuyee(SDLK_RIGHT)){
			plan.rotationner(0.009, 0, 0); objet.rotationner(0.009, 0, 0);
		}
		if (Clavier::toucheAppuyee(SDLK_LEFT)){
			plan.rotationner(-0.009, 0, 0); objet.rotationner(-0.009, 0, 0);
		}

		// Affichage:.............................................................................................................................................................................
		plan.afficher();
		objet.afficher();

		cam.apply();

		window.refresh();

	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisable(GL_TEXTURE_2D);

	return 0;
}