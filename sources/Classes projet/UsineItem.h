#pragma once
#include "Item.h"
#include "Melee.h"
#include "GestionnaireRessources.h"
#include "Fusil.h"
#include "Consommable.h"
#include "Equipable.h"
#include "Note.h"
#include "Journal.h"

class UsineItem : public Singleton<UsineItem>{
public:
	Item* obtItemParType(int type, unsigned int ID){
		switch (type / 10){
			case (0) :
				switch (type % 10){
					case(0) ://couteau
						return new Melee(0.3, 20.0, type, "Knife", "Don't cut yourself, bro.", "Ressources/Texture/couteauIcone.png", 1, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/couteau.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/couteau.png")), ID, "metal", 0.545);
					case(1) ://chandelier
						return new Melee(0.7, 10.0, type, "Candlestick", "Use it to guide your path, or simply smash things...", "Ressources/Texture/chandelierIcone.png", 1, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/chandelier.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/chandelier.png")), ID, "metal", 3.0);
					case(2) ://HolyRod
						return new Melee(1.5, 236.0, type, "HolyRod", "The divine window opener!", "Ressources/Texture/HolyRod236Icone.png", 1, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/HolyRod236.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/HolyRod236.png")), ID, "metal", 1.4);
					case(3) ://Mac a Patrick
						return new Melee(0.5, 5.0, type, "Your Mac", "The battery is dead", "Ressources/Texture/macIcone.png", 1, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/mac.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/mac.png")), ID, "metal", 2.06);
				}
			case (1) :
				switch (type % 10){
					case(0) ://luger
						return new Fusil(type, "Luger P08", "Pow, Pow", "Ressources/Texture/lugerIcone.png", new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/luger.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/luger.png")), ID, "metal", 0.871, 2.5, 10.0, 0.1, 1, 8, false);;
					case(1) ://thompson
						return new Fusil(type, "Thompson M1", "PPPPPow", "Ressources/Texture/thompsonIcone.png", new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/thompson.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/thompson.png")), ID, "metal", 4.47, 12, 20, 2.0, 1, 30, true);
				}
			case (2) :
				switch (type % 10){
					case(0) ://note
						return new Note(ID, gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/Whyv2_000000.png"));
					case(1) ://journal
						return nullptr /*new Journal()*/;
				}
			case (3) :
				switch (type % 10){
					case(0) ://thai
						return new Thai(ID);
					case(1) ://eau
						return new Eau(ID);
					case(2) ://poulet
						return new Poulet(ID);
					case(3) ://pilule
						return new Pilule(ID);
					case(4) ://lait
						return new Lait(ID);
					case(5) ://chocolat
						return new Chocolat(ID);
					case(6) ://lait
						return new Vin(ID);
					case(7) ://chocolat
						return new Seringue(ID);
				}
			case (4) :
				switch (type % 10){
					case(0) ://balle
						return new Jetable(type, "Tennis ball", "Who knew that the Führer had a tennis court", "Ressources/Texture/TennisIcone.png",16, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/BalleDeTennis.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/Tennis.png")), ID, "ballerebondissante", 0.0585);
					case(1) ://roche
						return new Jetable(type, "Rock", "Paper Scissors", "Ressources/Texture/RocheIcone.png", 16, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/Roche.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/Roche.png")), ID, "metal", 0.5);
					case(2) ://companion
						return new Companion(ID);
				}
			case (5) :
				switch (type % 10){
					case(0) ://masque a gaz
						return new MasqueGaz(ID);
			}
		}
		return nullptr;
	}
};
