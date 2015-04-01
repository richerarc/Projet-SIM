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
#include "Graphe.h"
#include "GestionaireChemins.h"

typedef std::tuple<unsigned int, unsigned int, bool> Entree;
typedef std::tuple<unsigned int, unsigned int> Sortie;

class Carte{
private:
	graphe::Graphe carte;
	std::map<Entree, Sortie> liens;
	std::list<InfoSalle> InfosSalles;
	Salle *salleActive;
	
	void ajouterLien(Entree entree, Sortie sortie){
		liens[entree] = sortie;
	}
public:
	
	std::tuple<unsigned int, unsigned int> destination(std::tuple<unsigned int, unsigned int, bool> sortie){
		return liens[sortie];
	}
	
	void creer(const unsigned int limite){
		carte.creer(limite);
		int itterateurPorte(0);
		
		int porte[limite];
		Entree entree;
		Sortie sortie;
		for (int i = 0; i < limite; i++)
			porte[i] = 0;
		
		for (int i = 0; i < limite; i++){
			for (int j = 0; j < limite; j++){
				if (carte.matrice[i * limite + j]){
					entree = std::make_tuple(i, ++itterateurPorte, false);
					sortie = std::make_tuple(j, porte[j]);
					++porte[j];
					ajouterLien(entree, sortie);
					
				}
			}
		}
	}
};
