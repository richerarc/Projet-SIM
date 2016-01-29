#pragma once
#include <functional>
#include <map>
#include <vector>
#include "Singleton.h"
class GestionnaireEvenements : public Singleton<GestionnaireEvenements>
{
public:
	int ajouterUnRappel(Uint32 type, std::function<void(SDL_Event&)> fonction){
		fonctions[type].push_back(fonction);
		changement = true;
		return fonctions[type].size() - 1;
	}
	void lancerEvenement(SDL_Event event){
		if (fonctions.find(event.type) == fonctions.end())
			return;
		for (auto& it : fonctions[event.type]) {
			it(event);
			if (changement) {
				changement = false;
				return;
			}
		}

	}
private:
	std::map<Uint32, std::vector<std::function<void(SDL_Event&)>>> fonctions;
	static bool changement;
};

bool GestionnaireEvenements::changement = false;

