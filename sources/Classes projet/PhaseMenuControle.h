#pragma once
#include "MenuControle.h"
#include "Phase.h"

class PhaseMenuControle : public Phase{

private:

	MenuControle* menuControle;


public:

	PhaseMenuControle() : Phase(){

		menuControle = new MenuControle();

	}

	~PhaseMenuControle() {

		delete menuControle;

	}

	void rafraichir(){

		menuControle->actualiser();

	}


};