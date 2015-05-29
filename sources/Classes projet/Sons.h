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
	bool eloigne;
	
public:
	
	bool actif;
	
	void defIntensite(Vecteur3d positionJoueur){
		double theta = position.angleEntreVecteurs(positionJoueur);
		theta = Maths::radianADegre(theta);
		int norme = (position - positionJoueur).norme() * 2;
		if (norme > 255){
			Mix_VolumeChunk(audio, 0);
			norme = 255;
			eloigne = true;
		}
		else if (eloigne){
			Mix_VolumeChunk(audio, volume);
			eloigne = false;
		}
		Mix_SetPosition(idChaine, (Uint16)theta, (Uint8)norme);
	}
	
	void defIntensite(Uint16 theta, Uint8 distance){
		Mix_SetPosition(idChaine, theta, distance);
	}
	
	Sons(const char* chemin, int ID, int volume){
		audio = Mix_LoadWAV(chemin);
		idChaine = ID;
		this->volume = volume;
		actif = false;
		eloigne = false;
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
	virtual void jouerRepetitions(Joueur* joueur){
			Mix_FadeInChannelTimed(idChaine, audio, 0, 1, -1);
	}
};

class Coeur : public Sons {
private:
	Mix_Chunk* audio2;
	Mix_Chunk* audio3;
	Mix_Chunk* audio4;
	Chrono delais;
	double BPM;
	short santePhysique, santeMentale, effort;
	
	void defBattement(Joueur* joueur){
		if (joueur->obtSanteMentale() != santeMentale){
			BPM = 210 - ((float)joueur->obtSanteMentale() * 1.55);
			santeMentale = joueur->obtSanteMentale();
		}
		if (joueur->obtVitesse().norme() && joueur->obtVitesseDeplacement() >= 5.f && effort < 100){
			if (effort % 2)
				BPM += 1;
			if (!effort)
				defVolume(volume + 10);
			effort += 1;
		}
		else if (joueur->obtVitesse().norme() && joueur->obtVitesseDeplacement() <= 4.f && effort > 0){
			if (effort % 2)
				BPM -= 1;
			if (effort == 1)
				defVolume(volume - 10);
			effort -= 1;
		}
		if (joueur->obtSantePhysique() != santePhysique){
			defVolume(127-joueur->obtSantePhysique());
			santePhysique = joueur->obtSantePhysique();
		}
	}
	
public:
	Coeur(const char* chemin1, const char* chemin2, const char* chemin3, const char* chemin4, int ID, int volume) : Sons(chemin1, ID, volume){
		BPM = 55;
		delais = Chrono();
		actif = true;
		audio2 = Mix_LoadWAV(chemin2);
		audio3 = Mix_LoadWAV(chemin3);
		audio4 = Mix_LoadWAV(chemin4);
		santeMentale = 100;
		santePhysique = 100;
		defVolume(27);
	}
	
	double obtBattement(){
		return BPM;
	}
	
	void defVolume(int nouveauVol){
		Mix_VolumeChunk(audio, nouveauVol);
		Mix_VolumeChunk(audio2, nouveauVol);
		Mix_VolumeChunk(audio3, nouveauVol);
		Mix_VolumeChunk(audio4, nouveauVol);
		volume = nouveauVol;
	}
	
	void jouer(Joueur* joueur){
		defBattement(joueur);
		if ((delais.obtTempsEcoule().enSecondes() >= 60.0f / BPM) && (!Mix_Playing(idChaine)) && (BPM <= 80)){
			Mix_FadeInChannelTimed(idChaine, audio, 0, 1, -1);
			delais.repartir();
		}
		else if ((delais.obtTempsEcoule().enSecondes() >= 60.0f / BPM) && (!Mix_Playing(idChaine)) && (BPM <= 120)){
			Mix_FadeInChannelTimed(idChaine, audio2, 0, 1, -1);
			delais.repartir();
		}
		else if ((delais.obtTempsEcoule().enSecondes() >= 60.0f / BPM) && (!Mix_Playing(idChaine)) && (BPM <= 160)){
			Mix_FadeInChannelTimed(idChaine, audio3, 0, 1, -1);
			delais.repartir();
		}
		else if ((delais.obtTempsEcoule().enSecondes() >= 60.0f / BPM) && (!Mix_Playing(idChaine)) && (BPM <= 210)){
			Mix_FadeInChannelTimed(idChaine, audio4, 0, 1, -1);
			delais.repartir();
		}
	}
};

class Fond : public Sons {
public:
	Fond(const char* chemin, int ID, int volume) : Sons(chemin, ID, volume){
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
	bool premier;
public:
	Pas(const char* chemin1, const char* chemin2, int ID, int volume) : Sons(chemin1, ID, volume){
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
		if (joueur->obtVitesseDeplacement() > 0 && joueur->obtVitesseDeplacement() <= 4.f && joueur->obtEtat() != CHUTE){
			if (!((delais.obtTempsEcoule().enMillisecondes() <= 650) || (Mix_Playing(idChaine)))){
				if (premier){
					Mix_FadeInChannelTimed(idChaine, audio, 0, 1, -1);
				}
				else{
					Mix_FadeInChannelTimed(idChaine, audio2, 0, 1, -1);
				}
				premier = !premier;
				delais.repartir();
			}
		}
		else if (joueur->obtVitesseDeplacement() >= 5.f && joueur->obtEtat() != CHUTE){
			if (!((delais.obtTempsEcoule().enMillisecondes() <= 325) || (Mix_Playing(idChaine)))){
				if (premier){
					Mix_FadeInChannelTimed(idChaine, audio, 0, 1, -1);
				}
				else{
					Mix_FadeInChannelTimed(idChaine, audio2, 0, 1, -1);
				}
				premier = !premier;
				delais.repartir();
			}
		}
	}
};