#pragma once
#include "Singleton.h"
#include "Modele.h"
#include "Texture.h"
#include "Police.h"
#include "Texte.h"

#include <map>
#include <vector>

namespace gfx{
	class GestionnaireRessources : public Singleton<GestionnaireRessources>{
	private:
		std::map<const char*, gfx::Modele*>  modeles;
		std::map<const char*, gfx::Texture> textures;
		std::map<std::string, gfx::Police*> polices;
		std::map<std::string, gfx::Texte*> textes;

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

		bool chargerPolice(const char* chemin, std::string nom, int taille) {
			return polices[nom] = new gfx::Police(chemin, taille);
		}

		bool chargerTexte(const char* texte, std::string nom, SDL_Color couleur, gfx::Police* police) {
			return textes[nom] = new gfx::Texte(texte, couleur, police);
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

		gfx::Police* obtPolice(const char* chemin, int taille) {
			std::string nom = gfx::Police::creerNom(chemin, taille);
			if (polices.find(nom.c_str()) == polices.end())
				chargerPolice(chemin, nom.c_str(), taille);
			return polices[nom];
		}

		gfx::Texte* obtTexte(const char* texte, SDL_Color couleur, gfx::Police* police) {
			std::string nom = gfx::Texte::creerNom(texte, couleur);
			if (textes.find(nom.c_str()) == textes.end())
				chargerTexte(texte, nom, couleur, police);
			return textes[nom];
		}
	};
}