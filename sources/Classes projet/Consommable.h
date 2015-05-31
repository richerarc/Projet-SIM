#pragma once 
#include "Melee.h"
#include "Jetable.h"
class Consommable{
protected:
	bool etatAnimation, sonAnimation;
	Vecteur3d posAnimation;
	Vecteur3d posDepart;
	Vecteur3d rotAnimation;
	virtual void consommer(double temps, Joueur* joueur){
		rotAnimation = Vecteur3d(0, 0, -50 * temps);
		posAnimation = Vecteur3d(posDepart + (joueur->obtHaut() * 0.30 - joueur->obtDevant() * 0.8 - joueur->obtCote() * 0.5) * (temps / 2));
	}
	void finConsommation(Joueur* joueur){
		joueur->deBloquer();
		Item* item = joueur->obtInventaire()->retirerObjetAccesRapide(joueur->obtInventaire()->obtItemSelectionne());
		item->defEtat(EtatItem::RANGE);
		delete item;
	}
public:
	Consommable(){
		etatAnimation = false;
		sonAnimation = false;
	};
};

struct Thai : public Jetable, public Consommable{
	Thai(unsigned int ID) : Jetable(30, "Felix's thai box", "Extremely hot General Tso's chicken", "Ressources/Texture/thaiIcone.png", 16, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/thai.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/thai.png")), ID, "carton", 0.76){}
	void animer(Joueur* joueur){
		if (etatAnimation){
			if (animation.obtTempsEcoule().enSecondes() < 1.5){
				consommer(animation.obtTempsEcoule().enSecondes(), joueur);
				if (!sonAnimation){
					sonAnimation = true;
					ControlleurAudio::obtInstance().jouer(MUNCH_1, joueur);
				}
				if (etat == EtatItem::EQUIPE){
					this->modele->rotationner(rotAnimation);
					this->defPosition(posAnimation);
				}
			}
			else{
				joueur->defSantePhysique(joueur->obtSantePhysique() + 10);
				finConsommation(joueur);
			}
		}
	}
	void utiliser2(Joueur* joueur){
		if (!joueur->obtBloque()){
			if (!etatAnimation && joueur->obtVitesseDeplacement() == 0 && joueur->obtEtat() == STABLE){
				etatAnimation = true;
				posDepart = position;
				joueur->bloquer();
				animation.repartir();
			}
		}
	}
	void equiper(Joueur* joueur){}
};
struct Eau : public Jetable, public Consommable{
	Eau(unsigned int ID) : Jetable(31, "Water bottle", "Fresh old water", "Ressources/Texture/eauIcone.png", 16, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/eau.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/eau.png")), ID, "plastique", 0.4){}
	void animer(Joueur* joueur){
		if (etatAnimation){
			if (animation.obtTempsEcoule().enSecondes() < 1.5){
				consommer(animation.obtTempsEcoule().enSecondes(), joueur);
				if (!sonAnimation){
					sonAnimation = true;
					ControlleurAudio::obtInstance().jouer(BOIRE, joueur);
				}
				if (etat == EtatItem::EQUIPE){
					this->modele->rotationner(rotAnimation);
					this->defPosition(posAnimation);
				}
			}
			else{
				//réduit la température corporelle, bref fait rien dans le jeu, mais on plogue Éduc1
				finConsommation(joueur);
			}
		}
	}
	void utiliser2(Joueur* joueur){
		if (!joueur->obtBloque()){
			if (!etatAnimation && joueur->obtVitesseDeplacement() == 0 && joueur->obtEtat() == STABLE){
				etatAnimation = true;
				posDepart = position;
				joueur->bloquer();
				animation.repartir();
			}
		}
	}
	void equiper(Joueur* joueur){}
};
struct Poulet : public Melee, public Consommable{
	Poulet(unsigned int ID) : Melee(1.5, 2, 32, "Chicken drumstick", "Colonel Sander would be proud of it", "Ressources/Texture/pouletIcone.png", 16, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/poulet.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/poulet.png")), ID, "plastique", 0.12){}
	void animer(Joueur* joueur){
		if (etatAnimation){
			if (animation.obtTempsEcoule().enSecondes() < 1.5){
				consommer(animation.obtTempsEcoule().enSecondes(), joueur);
				if (!sonAnimation){
					sonAnimation = true;
					ControlleurAudio::obtInstance().jouer(MUNCH_2, joueur);
				}
				if (etat == EtatItem::EQUIPE){
					this->modele->rotationner(rotAnimation);
					this->defPosition(posAnimation);
				}
			}
			else{
				if (rand() % 2)
					joueur->defSantePhysique(joueur->obtSantePhysique() + 5);
				else
					joueur->defSantePhysique(joueur->obtSantePhysique() - 5);
				finConsommation(joueur);
			}
		}
		else if (animationActuelle == 1){
			double tempsMax = 0.4;
			double tempsEcoule = animationMelee.obtTempsEcoule().enSecondes();
			if (tempsEcoule < tempsMax){
				modele->rotationner(Vecteur3d(0, 0, 1), 12500 * tempsEcoule * (tempsEcoule - tempsMax) * (tempsEcoule - 2 * tempsMax / 3));
			}
			else{
				animationMelee.repartir();
				animationActuelle = 0;
			}
		}
	}
	void utiliser2(Joueur* joueur){
		if (!joueur->obtBloque()){
			if (!etatAnimation && joueur->obtVitesseDeplacement() == 0 && joueur->obtEtat() == STABLE){
				etatAnimation = true;
				posDepart = position;
				joueur->bloquer();
				animation.repartir();
			}
		}
	}
	void equiper(Joueur* joueur){}
};
struct Pilule : public Jetable, public Consommable{
	Pilule(unsigned int ID) : Jetable(33, "Some pills", "This is your last chance. After this, there is no turning back.", "Ressources/Texture/pilluleIcone.png", 16, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/potpillule.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/potpilluletexture.png")), ID, "plastique", 0.05){}
	void animer(Joueur* joueur){
		if (etatAnimation){
			if (animation.obtTempsEcoule().enSecondes() < 1.5){
				consommer(animation.obtTempsEcoule().enSecondes(), joueur);
				if (!sonAnimation){
					sonAnimation = true;
					ControlleurAudio::obtInstance().jouer(TOUX_1, joueur);
				}
				if (etat == EtatItem::EQUIPE){
					this->modele->rotationner(rotAnimation);
					this->defPosition(posAnimation);
				}
			}
			else{
				if (rand() % 2)
					joueur->defSanteMentale(joueur->obtSanteMentale() + 5);
				else
					joueur->defSanteMentale(joueur->obtSanteMentale() - 5);
				finConsommation(joueur);
			}
		}
	}
	void utiliser2(Joueur* joueur){
		if (!joueur->obtBloque()){
			if (!etatAnimation && joueur->obtVitesseDeplacement() == 0){
				etatAnimation = true;
				posDepart = position;
				joueur->bloquer();
				animation.repartir();
			}
		}
	}
	void equiper(Joueur* joueur){}
};
struct Lait : public Jetable, public Consommable{
	Lait(unsigned int ID) : Jetable(34, "Milk carton", "You deserve Natrel", "Ressources/Texture/PinteDeLaitIcone.png", 16, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/PinteDeLait.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/PinteDeLait.png")), ID, "carton", 2.1){}
	void animer(Joueur* joueur){
		if (etatAnimation){
			if (animation.obtTempsEcoule().enSecondes() < 1.5){
				consommer(animation.obtTempsEcoule().enSecondes(), joueur);
				if (!sonAnimation){
					sonAnimation = true;
					ControlleurAudio::obtInstance().jouer(BOIRE, joueur);
				}
				if (etat == EtatItem::EQUIPE){
					this->modele->rotationner(rotAnimation);
					this->defPosition(posAnimation);
				}
			}
			else{
				joueur->defSantePhysique(joueur->obtSantePhysique() - 10);
				finConsommation(joueur);
			}
		}
	}
	void utiliser2(Joueur* joueur){
		if (!joueur->obtBloque()){
			if (!etatAnimation && joueur->obtVitesseDeplacement() == 0 && joueur->obtEtat() == STABLE){
				etatAnimation = true;
				posDepart = position;
				joueur->bloquer();
				animation.repartir();
			}
		}
	}
	void equiper(Joueur* joueur){}
};
struct Chocolat : public Jetable, public Consommable{
	Chocolat(unsigned int ID) : Jetable(35, "Big Black Chocolate", "JEW won't belive it how good it tastes", "Ressources/Texture/chocolatIcone.png", 16, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/chocolat.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/chocolat.png")), ID, "carton", 2.1){}
	void animer(Joueur* joueur){
		if (etatAnimation){
			if (animation.obtTempsEcoule().enSecondes() < 1.5){
				consommer(animation.obtTempsEcoule().enSecondes(), joueur);
				if (!sonAnimation){
					sonAnimation = true;
					ControlleurAudio::obtInstance().jouer(MUNCH_3, joueur);
				}
				if (etat == EtatItem::EQUIPE){
					this->modele->rotationner(rotAnimation);
					this->defPosition(posAnimation);
				}
			}
			else{
				joueur->defSanteMentale(joueur->obtSanteMentale() + 5);
				finConsommation(joueur);
			}
		}
	}
	void utiliser2(Joueur* joueur){
		if (!joueur->obtBloque()){
			if (!etatAnimation && joueur->obtVitesseDeplacement() == 0){
				etatAnimation = true;
				posDepart = position;
				joueur->bloquer();
				animation.repartir();
			}
		}
	}
	void equiper(Joueur* joueur){}
};
struct Vin : public Jetable, public Consommable{
	Vin(unsigned int ID) : Jetable(36, "Red winw", "Pray for it to be a good vintage", "Ressources/Texture/bouteillevinIcone.png", 16, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/bouteillevin.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/bouteillevin.png")), ID, "metal", 2.1){}
	void animer(Joueur* joueur){
		if (etatAnimation){
			if (animation.obtTempsEcoule().enSecondes() < 1.5){
				consommer(animation.obtTempsEcoule().enSecondes(), joueur);
				if (!sonAnimation){
					sonAnimation = true;
					ControlleurAudio::obtInstance().jouer(BOIRE, joueur);
				}
				if (etat == EtatItem::EQUIPE){
					this->modele->rotationner(rotAnimation);
					this->defPosition(posAnimation);
				}
			}
			else{
				joueur->saouler();
				finConsommation(joueur);
			}
		}
	}
	void utiliser2(Joueur* joueur){
		if (!joueur->obtBloque()){
			if (!etatAnimation && joueur->obtVitesseDeplacement() == 0 && joueur->obtEtat() == STABLE){
				etatAnimation = true;
				posDepart = position;
				joueur->bloquer();
				animation.repartir();
			}
		}
	}
	void equiper(Joueur* joueur){}
};

struct Biere : public Jetable, public Consommable{
	Biere(unsigned int ID) : Jetable(38, "Ice Cold Beer", "Because it needs to be cold.", "Ressources/Texture/bouteilleBiereIcone.png", 16, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/bouteilleBiere.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/bouteilleBiere.png")), ID, "metal", 2.1){}
	void animer(Joueur* joueur){
		if (etatAnimation){
			if (animation.obtTempsEcoule().enSecondes() < 1.5){
				consommer(animation.obtTempsEcoule().enSecondes(), joueur);
				if (!sonAnimation){
					sonAnimation = true;
					ControlleurAudio::obtInstance().jouer(BOIRE, joueur);
				}
				if (etat == EtatItem::EQUIPE){
					this->modele->rotationner(rotAnimation);
					this->defPosition(posAnimation);
				}
			}
			else{
				joueur->saouler();
				finConsommation(joueur);
			}
		}
	}
	void utiliser2(Joueur* joueur){
		if (!joueur->obtBloque()){
			if (!etatAnimation && joueur->obtVitesseDeplacement() == 0 && joueur->obtEtat() == STABLE){
				etatAnimation = true;
				posDepart = position;
				joueur->bloquer();
				animation.repartir();
			}
		}
	}
	void equiper(Joueur* joueur){}
};

struct Seringue : public Jetable, public Consommable{
	Seringue(unsigned int ID) : Jetable(37, "Syringe", "50cc of pure expirementation", "Ressources/Texture/seringueIcone.png", 16, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/seringue.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/seringue.png")), ID, "metal", 2.1){}
	void consommer(double temps, Joueur* joueur){
		rotAnimation = Vecteur3d(90 * temps, 0, 0);
		posAnimation = Vecteur3d(posDepart + (joueur->obtHaut() * 0.30 - joueur->obtCote() * 0.50) * (temps / 2));
	}
	void animer(Joueur* joueur){
		if (etatAnimation){
			if (animation.obtTempsEcoule().enSecondes() < 1.5){
				consommer(animation.obtTempsEcoule().enSecondes(), joueur);
				if (!sonAnimation){
					sonAnimation = true;
					ControlleurAudio::obtInstance().jouer(Sons_t::RESPIRATION , joueur);
				}
				if (etat == EtatItem::EQUIPE){
					this->modele->rotationner(rotAnimation);
					this->defPosition(posAnimation);
				}
			}
			else{
				joueur->defSantePhysique(joueur->obtSantePhysique() + 20);
				joueur->defSanteMentale(joueur->obtSanteMentale() + 5);
				finConsommation(joueur);
			}
		}
	}
	void utiliser2(Joueur* joueur){
		if (!joueur->obtBloque()){
			if (!etatAnimation && joueur->obtVitesseDeplacement() == 0 && joueur->obtEtat() == STABLE){
				etatAnimation = true;
				posDepart = position;
				joueur->bloquer();
				animation.repartir();
			}
		}
	}
	void equiper(Joueur* joueur){}
};
