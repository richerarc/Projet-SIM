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
	public:
		~GestionnaireRessources(){
			modeles.empty();
		}

		bool chargerTexture(const char* chemin){
			return textures[chemin].charger(chemin);
		}

		bool chargerModele(const char* chemin){
			return modeles[chemin] = new Modele(chemin);
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

	};
}