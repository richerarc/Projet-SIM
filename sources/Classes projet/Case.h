#pragma once 
#include "Info.h"

class Case{
private:
	InfoObjet* item;
public:
	Case(){
		item = nullptr;
	}
	void defObjet(InfoObjet* objet){
		this->item = objet;
	}

	InfoObjet* retirerObjet(){
		InfoObjet *tmp = item;
		item = nullptr;
		return tmp;
	}

	InfoObjet* obtObjet(){
		return this->item;
	}


};