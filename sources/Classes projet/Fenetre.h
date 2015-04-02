#pragma once
#include <string>
#include <list>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "Vecteur2.h"
#include "ModeVideo.h"

#include "Clavier.h"
#include "Souris.h"

namespace gfx{
	class Fenetre{
	public:

		Fenetre(ModeVideo mv, const std::string& titre, bool pe) : Fenetre(){
			this->taille.x = mv.l;
			this->taille.y = mv.h;

			sdlWindow = SDL_CreateWindow(titre.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, taille.x, taille.y, SDL_WINDOW_OPENGL);

			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
			SDLGLContext = SDL_GL_CreateContext(sdlWindow);

			this->defTitre(titre);
			defPleinEcran(pe);
			fenetrePleinEcran = pe;
		}

		~Fenetre(){
			SDL_GL_DeleteContext(SDLGLContext);
			SDL_DestroyWindow(sdlWindow);
			SDL_Quit();
		}

		Vecteur2ui obtTaille(){ return taille; }

		void defModeVideo(ModeVideo mv){
			this->taille = Vecteur2ui(mv.l, mv.h);
			bool tmpFs = fenetrePleinEcran;
			defPleinEcran(false);
			SDL_SetWindowSize(sdlWindow, taille.x, taille.y);
			SDL_SetWindowPosition(sdlWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
			if (tmpFs)
				defPleinEcran(true);
		}

		void defPleinEcran(bool pe){
			if (pe)
				SDL_SetWindowFullscreen(sdlWindow, SDL_WINDOW_FULLSCREEN);
			else
				SDL_SetWindowFullscreen(sdlWindow, 0);
			fenetrePleinEcran = pe;
		}

		virtual void vider(){
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		virtual void vider(SDL_Color& couleur){
			glClearColor(couleur.r, couleur.g, couleur.b, couleur.a);
			vider();
		}

		virtual void rafraichir(){
			SDL_GL_SwapWindow(sdlWindow);
		}

		void defTitre(const std::string& titre){
			this->titre = titre;
			SDL_SetWindowTitle(sdlWindow, titre.c_str());
		}

		bool sonderEvenements(SDL_Event &event){
			while (SDL_PollEvent(&event)){
				if (event.type == SDL_KEYDOWN){
					Clavier::mettreAJourEtat(event.key.keysym.sym, true);
				}
				if (event.type == SDL_KEYUP){
					Clavier::mettreAJourEtat(event.key.keysym.sym, false);
				}
				if (event.type == SDL_MOUSEBUTTONDOWN){
					Souris::mettreAJourEtatBoutons(event.button.button, true);
				}
				if (event.type == SDL_MOUSEBUTTONUP){
					Souris::mettreAJourEtatBoutons(event.button.button, false);
				}
				if (event.type == SDL_MOUSEMOTION)
					Souris::mettreAJourPosition(event.motion.x, event.motion.y);
				if (event.type == SDL_MOUSEWHEEL)
					Souris::mettreAJourEtatMolette(event.wheel.x, event.wheel.y);
				if (event.type != SDL_MOUSEWHEEL)
					Souris::mettreAJourEtatMolette(0, 0);
				return true;
			}
			return false;
		}

		bool estOuverte(){
			if (fenetreOuverte)
				return true;
			return false;
		}

		void fermer(){
			fenetreOuverte = false;
		}

	protected:
		Fenetre(){
			SDL_Init(SDL_INIT_VIDEO);
			fenetreOuverte = true;
		}

		Vecteur2ui taille;


		std::string titre;
		SDL_Window* sdlWindow;
		SDL_GLContext SDLGLContext;

		bool fenetreOuverte;
		bool fenetrePleinEcran;

	};
}