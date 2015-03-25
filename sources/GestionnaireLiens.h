#pragma once
#include <map>
#include <tuple>
#include <list>
#include "Modele3D.h"
#include "Contenu.h"
#include "Porte.h"
#include "Salle.h"
#include "Fabrique.h"

struct InfoObjet {
	const unsigned int ID;
	const char* cheminFicher;
};

struct InfoSalle {
	const unsigned int ID;
	const unsigned int nbrPorte;
	const char* cheminFicher;
	std::list<InfoObjet>
};

class GestionnaireLiens : public Singleton<GestionnaireLiens>{
private:
	std::map<std::tuple<unsigned int, unsigned int, bool>, std::tuple<unsigned int, unsigned int>> connections;
	std::list<InfoSalle> InfosSalles;
	Salle *salleActive
public:
	GestionnaireLiens(){}
	~GestionnaireLiens(){}

	void ajouter(std::tuple<unsigned int, unsigned int, bool> entree, std::tuple<unsigned int, unsigned int> sortie){
		connections[entree] = sortie;
	}
	std::tuple<unsigned int, unsigned int> destination(std::tuple<unsigned int, unsigned int, bool> sortie){
			//return connections.find(sortie)->second;
		return connections[sortie];
	}
	Porte obtPorte(unsigned int _ID){
		for (auto it : portes){
			if (it.obtID() == _ID)
				return it;
		}
		return portes.front();
	}
	Salle obtSalle(unsigned int _ID){
		for (auto it : salles){
			if (it.obtID() == _ID)
				return it;
		}
		return salles.front();
	}
};
