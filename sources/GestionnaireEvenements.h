#pragma once
#include "Singleton.h"
#include <functional>
#include <map>
#include <vector>

class GestionnaireEvenements : public Singleton<GestionnaireEvenements>
{
public:
	int ajouterUnRappel(Uint32 type, std::function<void(SDL_Event)> fonction){
		fonctions[type].push_back(fonction);
		return fonctions[type].size() - 1;
	}
	void lancerEvenement(SDL_Event event){
		if (fonctions.find(event.type) == fonctions.end())
			return;
		for (auto& it : fonctions[event.type])
			it(event);
	}
private:
	std::map<Uint32, std::vector<std::function<void(SDL_Event)>>> fonctions;
};

