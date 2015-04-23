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

	void ajouterPhase(Phase* phase) {
		phases.push_back(phase);
	}

	void retirerPhase(){
		delete phases.back();
		phases.pop_back();
	}

	void defPhaseActive(int index) {
		phaseActive = obtPhase(index);
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

	Phase* obtDerniere() {
		return phases.back();
	}

	void rafraichir(float frameTime){
			phaseActive->rafraichir(frameTime);
	}
private:
	std::list<Phase*> phases;
	Phase* phaseActive;
};