#pragma once
#include "Item.h"

class Munition : public Item{
protected:
	int quantite;
	virtual void recharger(Joueur* joueur) = 0;
public:
	Munition(int type, char* nom, char* description, char* cheminIcone, gfx::Modele3D* modele, unsigned int ID, double masse) : Item(type, nom, description, cheminIcone, INT_MAX, modele, ID, "metal", masse){	}
	void utiliser(Joueur* joueur){
		if (!joueur->obtBloque()){
			if (quantite)
				recharger(joueur);
			if (!quantite){
				Item* item = joueur->obtInventaire()->retirerObjetAccesRapide(joueur->obtInventaire()->obtItemSelectionne());
				item->defEtat(EtatItem::RANGE);
				delete item;
			}
		}
	}
	void utiliser2(Joueur* joueur){}
	void equiper(Joueur* joueur){}
	void animer(Joueur* joueur){}
	int obtQuant(){ return quantite; }
};

class Acp45 : public Munition{
	void recharger(Joueur* joueur){
		Item* itemTmp = joueur->obtInventaire()->obtItemParType(11);
		if (itemTmp != nullptr){
			Fusil* tmp = dynamic_cast<Fusil*>(itemTmp);
			short munition = tmp->obtChargeur() - tmp->obtballesRestantes();
			if (munition > quantite){
				munition = quantite;
			}
			if (munition){
				tmp->charger(munition);
				quantite -= munition;
				ControlleurAudio::obtInstance().jouer(EQUIPERFUSIL, joueur);
			}
		}
	}
public:
	Acp45(unsigned int ID) : Munition(60, ".45 ACP", "A box of 60 thompson ammo", "Ressources/Texture/ACP45Icone.png", new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/Munition.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/ACP45.png")), ID, 0.2){
		quantite = 60;
	}
};

class Parabellum : public Munition{
	void recharger(Joueur* joueur){
		Item* itemTmp = joueur->obtInventaire()->obtItemParType(10);
		if (itemTmp != nullptr){
			Fusil* tmp = dynamic_cast<Fusil*>(itemTmp);
			short munition = tmp->obtChargeur() - tmp->obtballesRestantes();
			if (munition > quantite){
				munition = quantite;
			}
			if (munition){
				tmp->charger(munition);
				quantite -= munition;
				ControlleurAudio::obtInstance().jouer(EQUIPERFUSIL, joueur);
			}
		}
	}
public:
	Parabellum(unsigned int ID) : Munition(61, "PARABELLUM", "A box of 24 luger ammo", "Ressources/Texture/PARABELLUMIcone.png", new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/Munition.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/PARABELLUM.png")), ID, 0.2){
		quantite = 24;
	}
};

class CartoucheGaz : public Munition{
	void recharger(Joueur* joueur){
		Item* itemTmp = joueur->obtInventaire()->obtItemParType(50);
		if (itemTmp != nullptr){
			MasqueGaz* tmp = dynamic_cast<MasqueGaz*>(itemTmp);
			tmp->recharger();
			--quantite;
		}
	}
public:
	CartoucheGaz(unsigned int ID) : Munition(62, "Gas mask's filter", "A brand new filter for your mask!", "Ressources/Texture/filtreGasIcone.png", new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/cartoucheGas.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/cartoucheGas.png")), ID, 0.2){
		quantite = 1;
	}
};
