#pragma once
#include "Info.h"
#include "Objet.h"

enum EtatItem { EQUIPE, RANGE, DEPOSE };

class Item{
private:
	InfoObjet* infoObjet;
	int ID;
	char* nom;
	char* description;
	char* cheminIcone;
	int maxPile;
	Objet* objetActuel;
	EtatItem etat;
public:
	Item(int ID, char* nom, char* description, char* cheminIcone, int maxPile, InfoObjet* info){
		this->ID = ID;
		this->nom = nom;
		this->description = description;
		this->cheminIcone = cheminIcone;
		this->maxPile = maxPile;
		this->infoObjet = info;

		objetActuel = nullptr;
		etat = RANGE;
	}

	void defEtat(EtatItem etat){
		this->etat = etat;
		// TODO Ajouter la création d'objets lors du changement d'état.
	}

	EtatItem obtEtat(){
		return etat;
	}

	int obtID(){
		return this->ID;
	}

	InfoObjet* obtInfoObjet(){
		return this->infoObjet;
	}

	char* obtNom(){
		return this->nom;
	}

	char* obtDescription(){
		return this->description;
	}

	char* obtCheminIcone(){
		return this->cheminIcone;
	}

	int obtMaxPile(){
		return this->maxPile;
	}

	Objet* obtObjetActuel(){
		return this->objetActuel;
	}

	virtual void utiliser(){

	}
};