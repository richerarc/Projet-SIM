#pragma once

namespace gfx {

	class Texte{

	private:

		SDL_Surface* surface;
		SDL_Color couleur;
		gfx::Police* police;
		const char* texte;
		GLuint ID;

	public:

		Texte(const char* texte, SDL_Color couleur, Police* police) {

			surface = TTF_RenderText_Blended(police->obtPolice(), texte, couleur);
			this->couleur = couleur;
			this->police = police;
			this->texte = texte;

			if (surface != nullptr) {
				glGenTextures(1, &ID);
				glBindTexture(GL_TEXTURE_2D, ID);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, surface->pixels);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			}
		}

		~Texte() {
			SDL_FreeSurface(surface);
		}

		SDL_Surface* obtSurface(){
			return surface;
		}

		SDL_Color obtCouleur() {
			return couleur;
		}

		gfx::Police* obtPolice() {
			return police;
		}

		const char* obtTexte() {
			return texte;
		}

		GLuint obtID() {
			return ID;
		}

		static std::string creerNom(const char* texte, SDL_Color couleur, int taille) {

			char chr[6];

			std::string nomTmp("Texte");
			nomTmp.append(texte);
			nomTmp.append(SDL_itoa(couleur.r, chr, 10));
			nomTmp.append(SDL_itoa(couleur.g, chr, 10));
			nomTmp.append(SDL_itoa(couleur.b, chr, 10));
			nomTmp.append(SDL_itoa(couleur.a, chr, 10));
			nomTmp.append(SDL_itoa(taille, chr, 10));

			return nomTmp;
		}
	};
}