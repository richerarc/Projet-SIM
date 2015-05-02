#pragma once 
#include "Phase.h"
#include  <stack>

class GestionnairePhases : public Singleton<GestionnairePhases>{
public:
	GestionnairePhases(){

	}

	~GestionnairePhases(){
		while (phases.size() != 0) {
			delete phases.back();
			phases.pop_back();
		}
	}

	void ajouterPhase(Phase* phase) {
		phases.push_back(phase);
	}

	void enleverPhaseActive() {
		phaseActive.pop();
	}

	void retirerPhase(){
		delete phases.back();
		phases.pop_back();
	}

	void viderPhaseActive() {
		
		for (int i = phaseActive.size(); i > 0; --i)
			phaseActive.pop();

	}

	void defPhaseActive(int index) {
		phaseActive.push(obtPhase(index));
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
			phaseActive.top()->rafraichir(frameTime);
	}
	Phase* obtPhaseActive(){
		if (phaseActive.size() > 0)
			return phaseActive.top();
		return nullptr;
	}

	std::list<Phase*> obtListePhases(void) {
		return phases;
	}
private:
	std::list<Phase*> phases;
	std::stack<Phase*> phaseActive;
};