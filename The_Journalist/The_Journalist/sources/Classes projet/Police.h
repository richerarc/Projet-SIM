#pragma once

namespace gfx {
	class Police{

	private:

		TTF_Font* police;
		int taille;

	public:

		Police() {
			police = nullptr;
		}

		Police(const char* emplacement, int taille) {

			police = TTF_OpenFont(emplacement, taille);
			this->taille = taille;
		}

		~Police() {
			TTF_CloseFont(police);
		}

		TTF_Font* obtPolice() {
			return police;
		}

		int obtTaille(){
			return this->taille;
		}

		static std::string creerNom(const char* emplacement, int taille) {

			char chr[6];

			std::string nomTmp("Police");
			nomTmp.append(emplacement);
			int i = nomTmp.length();
			while (nomTmp[--i] != '.')
				nomTmp.pop_back();
			nomTmp.pop_back();
			nomTmp.append(SDL_itoa(taille, chr, 10));

			return nomTmp;
		}
	};
}