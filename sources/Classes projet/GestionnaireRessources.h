#pragma once
#include "Singleton.h"
#include "Modele.h"
#include "Texture.h"

#include <map>
#include <vector>

namespace gfx{
	class GestionnaireRessources : public Singleton<GestionnaireRessources>{
	private:
		std::map<const char*, gfx::Modele*>  modeles;
		std::map<const char*, gfx::Texture> textures;
		std::map<const char*, TTF_Font*> fonts;


	public:
		~GestionnaireRessources(){
			for (auto it : modeles)
				delete it.second;
		}

		bool chargerTexture(const char* chemin){
			return textures[chemin].charger(chemin);
		}

		bool chargerModele(const char* chemin){
			return modeles[chemin] = new Modele(chemin);
		}

		bool chargerFont(const char* chemin, const char* nom, int taille) {
			return fonts[nom] = TTF_OpenFont(chemin, taille);
		}

		gfx::Texture& obtTexture(const char* chemin){
			if (textures.find(chemin) == textures.end())
				chargerTexture(chemin);
			return textures[chemin];
		}

		gfx::Modele* obtModele(const char* chemin){
			if (modeles.find(chemin) == modeles.end())
				chargerModele(chemin);
			return modeles[chemin];
		}

		TTF_Font* obtPolice(const char* chemin, const char* nom, int taille) {
			if (fonts.find(nom) == fonts.end())
				chargerFont(chemin, nom, taille);
			return fonts[nom];
		}
	};
}