#pragma once

#include "Vecteur3.h"
#include "Chrono.h"

class Sons {
protected:
	Mix_Chunk* audio;
	int idChaine;
	Vecteur3d position;
	int volume;
public:
	
	Sons(const char* chemin, int ID, Vecteur3d& pos, int volumeDepart){
		audio = Mix_LoadWAV(chemin);
		idChaine = ID;
		position = pos;
		volume = volumeDepart;
	}
	
	~Sons(){Mix_FreeChunk(audio);}
	
	void defPosition(Vecteur3d& pos){position = pos;}
	
	Vecteur3d& obtPosition(){return position;}
	
	int obtVolume(){return volume;}
	
	void defVolume(int nouveauVol){
		Mix_Volume(idChaine, nouveauVol);
		Mix_VolumeChunk(audio, nouveauVol);
		volume = nouveauVol;
	}
	
	void defVolume(Vecteur3d positionJoueur, Vecteur3d cameraDevant){
			//TODO : aller voir Olivier Séguin
	}
	
	virtual void jouer(){
		if (!Mix_Playing(idChaine)){
			Mix_FadeInChannelTimed(idChaine, audio, 0, 0, -1);
		}
	}
};

class Coeur : public Sons {
private:
	Chrono delais;
	int BPM;
public:
	Coeur(const char* chemin, int ID, Vecteur3d& pos, int volumeDepart) : Sons(chemin, ID, pos, volumeDepart){
		BPM = 70;
		delais = Chrono();
	}
	
	void defVitesseBattement(int nouveauBPM){
		this->BPM = nouveauBPM;
	}
	
	void jouer(){
			//TODO
	}
};