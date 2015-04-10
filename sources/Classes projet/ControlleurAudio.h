#pragma once
#include "Lecteur.h"

class ControlleurAudio : public Singleton<ControlleurAudio>{
private:
	Lecteur lecteur;
public:
	
	ControlleurAudio(){}
	
	~ControlleurAudio(){}
	
	void allouerChaines(int chaines){
		lecteur.allouerChaines(chaines);
	}
	
	void initialiser(){
		
	}
	
};