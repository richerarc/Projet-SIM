#pragma once

#include "Vecteur3.h"
#include "Chrono.h"
#include "Joueur.h"

class Sons {
protected:
	Mix_Chunk* audio;
	int idChaine;
	Vecteur3d position;
	int volume;
	
	void defVolume(Vecteur3d positionJoueur, Vecteur3d cameraDevant){
			//TODO : aller voir Olivier Séguin
	}
	
public:
	
	bool actif;
	
	Sons(const char* chemin, int ID){
		audio = Mix_LoadWAV(chemin);
		idChaine = ID;
		actif = false;
	}
	
	~Sons(){Mix_FreeChunk(audio);}
	
	void defPosition(Vecteur3d& pos){position = pos;}
	
	Vecteur3d& obtPosition(){return position;}
	
	int obtVolume(){return volume;}
	
	virtual void defVolume(int nouveauVol){
		Mix_VolumeChunk(audio, nouveauVol);
		volume = nouveauVol;
	}
	
	int obtChaine(){
		return idChaine;
	}
	
	virtual void jouer(Joueur* joueur){
		if (!Mix_Playing(idChaine)){
			Mix_FadeInChannelTimed(idChaine, audio, 0, 1, -1);
		}
	}
};

class Coeur : public Sons {
private:
	Mix_Chunk* audio2;
	Chrono delais;
	double BPM;
public:
	Coeur(const char* chemin1, const char* chemin2, int ID) : Sons(chemin1, ID){
		BPM = 55;
		delais = Chrono();
		actif = true;
		audio2 = Mix_LoadWAV(chemin2);
	}
	
	void defVitesseBattement(int nouveauBPM){
		this->BPM = nouveauBPM;
	}
	
	double obtBattement(){
		return BPM;
	}
	
	void defVolume(int nouveauVol){
		Mix_VolumeChunk(audio, nouveauVol);
		Mix_VolumeChunk(audio2, nouveauVol);
		volume = nouveauVol;
	}
	
	void jouer(Joueur* joueur){
		if (BPM <= 1.0)
			BPM = 1.0;
		if ((delais.obtTempsEcoule().enSecondes() >= 60.0f / BPM) && (!Mix_Playing(idChaine)) && (BPM <= 100)){
			Mix_FadeInChannelTimed(idChaine, audio, 0, 1, -1);
			delais.repartir();
		}
		else if ((delais.obtTempsEcoule().enSecondes() >= 60.0f / BPM) && (!Mix_Playing(idChaine))){
			Mix_FadeInChannelTimed(idChaine, audio2, 0, 1, -1);
			delais.repartir();
		}
	}
};

class Fond : public Sons {
public:
	Fond(const char* chemin, int ID) : Sons(chemin, ID){
		actif = true;
	}
	
	void jouer(Joueur* joueur){
		if (!Mix_Playing(idChaine)){
			Mix_FadeInChannelTimed(idChaine, audio, -1, 200, -1);
		}
	}
};

class Pas : public Sons {
private:
	Mix_Chunk* audio2;
	Chrono delais;
	double vitesse;
	bool premier;
public:
	Pas(const char* chemin1, const char* chemin2, int ID) : Sons(chemin1, ID){
		vitesse = 750;
		delais = Chrono();
		audio2 = Mix_LoadWAV(chemin2);
		premier = true;
	}
	
	void defVolume(int nouveauVol){
		Mix_VolumeChunk(audio, nouveauVol);
		Mix_VolumeChunk(audio2, nouveauVol);
		volume = nouveauVol;
	}
	
	void jouer(Joueur* joueur){
		if ((Clavier::toucheAppuyee(SDLK_w) || Clavier::toucheAppuyee(SDLK_a) || Clavier::toucheAppuyee(SDLK_s) || Clavier::toucheAppuyee(SDLK_d)) && !joueur->enSaut()){
			if (!((delais.obtTempsEcoule().enMillisecondes() <= vitesse) || (Mix_Playing(idChaine)))){
				if (premier)
					Mix_FadeInChannelTimed(idChaine, audio, 0, 1, -1);
				else
					Mix_FadeInChannelTimed(idChaine, audio2, 0, 1, -1);
				premier = !premier;
				delais.repartir();
			}
		}
	}
};