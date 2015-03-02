#pragma once
#include "Singleton.h"
#include "Salle.h"
#include "Porte.h"
#include <map>
#include <tuple>
#include <list>
class GestionnaireLens : public Singleton<GestionnaireLens>{
private:
	std::map<std::tuple<unsigned int, unsigned int, bool>, std::tuple<unsigned int, unsigned int>> connections;
	std::list<Salle> salles;
	std::list<Porte> portes;
public:
	GestionnaireLens(){}
	~GestionnaireLens(){}

	void ajouter(std::tuple<unsigned int, unsigned int, bool> entree, std::tuple<unsigned int, unsigned int> sortie){
		connections[entree] = sortie;
	}
	std::tuple<unsigned int, unsigned int> destination(std::tuple<unsigned int, unsigned int, bool> sortie){
		return connections.find(sortie)->second;
	}
};