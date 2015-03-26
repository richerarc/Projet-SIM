#pragma once
#include <map>
#include <tuple>
#include <list>
#include "Modele3D.h"
#include "Contenu.h"
#include "Porte.h"
#include "Salle.h"
#include "Info.h"
#include "Fabrique.h"
#include "graphe.h"

struct InfoObjet {
	const unsigned int ID;
	const char* cheminFicher;
};

struct InfoSalle {
	const unsigned int ID;
	const unsigned int nbrPorte;
	const char* cheminFicher;
	std::list<InfoObjet> Objet;
};

class Carte : public Singleton<GestionnaireLiens>{
private:
	graphe::Graphe carte;
	std::map<std::tuple<unsigned int, unsigned int, bool>, std::tuple<unsigned int, unsigned int>> Liens;
	std::list<InfoSalle> InfosSalles;
	Salle *salleActive;
	
	void ajouterLien(std::tuple<unsigned int, unsigned int, bool> entree, std::tuple<unsigned int, unsigned int> sortie){
		connections[entree] = sortie;
	}
public:
	GestionnaireLiens(){}
	~GestionnaireLiens(){}
	
	std::tuple<unsigned int, unsigned int> destination(std::tuple<unsigned int, unsigned int, bool> sortie){
		return connections[sortie];
	}
	
	void creer(const unsigned int limite){
		carte.creer(limite);
		int itterateurPorte(0);
		
		int porte[limite];
		for (int i = 0; i < limite; i++)
			porte[i] = 0;
		
		for (int i = 0; i < limite; i++){
			for (int j = 0; j < limite; j++){
				if (carte.matrice[i * limite + j]){
					ajouterLien(std::tuple<i, ++itterateurPorte, false>, std::tuple<j, ++porte[j]>)
				}
			}
		}
	}
};
