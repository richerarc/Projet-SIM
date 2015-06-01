#pragma once
#include "Item.h"

class Cle : public Item{
protected:
	double portee;
	int degats;
	Chrono dps;
public:
	Cle(unsigned int ID, int type, char* nom, char* description, char* cheminTexture) : Item(type, nom, description, "Ressources/Texture/cleIcone.png", 1, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/Clef.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture(cheminTexture)), ID, "metal", 0.3){}
	void utiliser(Joueur* joueur){
		if (!joueur->obtBloque()){
			if (dps.obtTempsEcoule().enSecondes() > 0.4){
				dps.repartir();
				Droite rayon(gfx::Gestionnaire3D::obtInstance().obtCamera()->obtPosition(), gfx::Gestionnaire3D::obtInstance().obtCamera()->obtDevant());
				Vecteur3d pointCollision;
				Vecteur3d normale;
				if (Physique::obtInstance().collisionDroiteModele(salleActive->obtModele(), rayon, pointCollision, normale, false)){
					if (Maths::distanceEntreDeuxPoints(pointCollision, gfx::Gestionnaire3D::obtInstance().obtCamera()->obtPosition()) < portee){



						for (auto it : salleActive->obtListeObjet()) {
							if (it->obtSiPorte()) {
								Porte* porte = dynamic_cast<Porte*>(it);
								if (porte->obtCible()->obtBoiteCollision().pointDansBoite2(pointCollision)) {
									if (porte->obtCible()->obtForce() < degats) {
										porte->obtCible()->defForce(0);
										porte->defVerrouillee(false);
									}
								}
							}
						}
					}
					else{
						ControlleurAudio::obtInstance().jouer(COUPCOUTEAUVIDE, joueur);
					}
				}
				for (auto it : salleActive->obtListeObjet()){
					if (it->obtMateriaux() == "personnage" && (Physique::obtInstance().collisionDroiteModele(it->obtModele3D(), rayon, pointCollision, normale, false))){
						salleActive->retirerObjet(it);
						delete it;
						ControlleurAudio::obtInstance().jouer(AH, joueur);
						GestionnaireSucces::obtInstance().obtSucces(27);
						joueur->defSanteMentale(joueur->obtSanteMentale() - 15);
						break;
					}
				}

			}
		}
	}
	void utiliser2(Joueur* joueur){}
	void equiper(Joueur* joueur){}
	void animer(Joueur* joueur){
		float vitesseJoueur = joueur->obtVitesseDeplacement();
		if (vitesseJoueur == 4.0f){
			modele->rotationner(Vecteur3d(0, 0, 1), 3 * sin(10 * animation.obtTempsEcoule().enSecondes()));
			modele->deplacer(0, 0.05 * sin(10 * animation.obtTempsEcoule().enSecondes()), 0);
		}
		if (vitesseJoueur == 10.0f){
			modele->rotationner(Vecteur3d(0, 0, 1), 6 * sin(10 * animation.obtTempsEcoule().enSecondes()));
			modele->deplacer(0, 0.07 * sin(10 * animation.obtTempsEcoule().enSecondes()), 0);
		}
	}
};

class CleRoulliee : public Cle{
public:
	CleRoulliee(unsigned int ID) : Cle(ID, 70, "Rusty Key", "At least it's still usable", "Ressources/Texture/cleRoulliee.png"){
		degats = 20;
		portee = 1.5;
	}
};

class CleFer : public Cle{
public:
	CleFer(unsigned int ID) : Cle(ID, 71, "Iron Key", "A pretty nice key", "Ressources/Texture/cleFer.png"){
		degats = 80;
		portee = 1.5;
	}
};

class CleFinale : public Cle{
public:
	CleFinale(unsigned int ID) : Cle(ID, 72, "Final Key", "The only key that will open your way out", "Ressources/Texture/cleFinale.png"){
		degats = INT_MAX;
		portee = 1.5;
	}
};