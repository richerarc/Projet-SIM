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

	Phase* obtPhase(int index){
		int ind = 0;
		for (auto i : phases){
			if (ind == index)
				return i;
			ind++;
		}
		return nullptr;
	}

	void rafraichir(float frameTime){
			phases.back()->rafraichir(frameTime);
	}
private:
	std::list<Phase*> phases;
};