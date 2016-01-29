#pragma once 
#include "Item.h"

class Case{
private:
	Item* item;
public:
	Case(){
		item = nullptr;
	}
	void defObjet(Item* objet){
		this->item = objet;
	}

	Item* retirerObjet(){
		Item *tmp = item;
		item = nullptr;
		return tmp;
	}

	Item* obtObjet(){
		return this->item;
	}


};