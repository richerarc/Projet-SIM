#pragma once 
#include "Phase.h"

class GestionnairePhases : public Singleton<GestionnairePhases>{
public:
	GestionnairePhases(){

	}

	~GestionnairePhases(){
		while (phases.size() != 0){
			delete phases.back();
			phases.pop_back();
		}
	}

	void ajouterPhase(Phase* phase){
		phases.push_back(phase);
	}

	void retirerPhase(){
		delete phases.back();
		phases.pop_back();
	}

	Phase* obtPhase(int index){
		int ind = 0;
		for (auto i : phases){
			if (ind == index)
				return i;
			ind++;
		}
		return nullptr;
	}
	Phase* obtDerniere(){
		return phases.back();
	}

	void afficher(gfx::Fenetre &fenetre){
		for (auto it : phases)
			it->afficher(fenetre);
	}

	void rafraichir(){
		for (auto it : phases)
			it->rafraichir();
	}
private:
	std::list<Phase*> phases;
};