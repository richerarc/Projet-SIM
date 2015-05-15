#pragma once
#include "Item.h"
#include "Melee.h"
#include "Fusil.h"
#include "GestionnaireRessources.h"

class UsineItem : public Singleton<UsineItem>{
public:
	Item* obtItemParType(int type, unsigned int ID){
		switch (type / 10){
		case (0) :
			switch (type % 10){
			case(0) ://couteau
				return new Melee(0.3, 20.0, type, "Knife", "Don't cut yourself, bro.", "couteauIcone.png", 1, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("couteau.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("couteau.png")), ID, "metal", 0.545);
			case(1) ://chandelier
				return new Melee(0.5, 10.0, type, "Candlestick", "Use it to guide your path, or simply smash things...", "chandelierIcone.png", 1, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("chandelier.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("chandelier.png")), ID, "metal", 3.0);
			case(2) ://HolyRod
				return new Melee(1.5, 236.0, type, "HolyRod", "The divine window opener!", "HolyRod236Icone.png", 1, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("HolyRod236.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("HolyRod236.png")), ID, "metal", 1.0);
		}
		case (1) :
			switch (type % 10){
			case(0) ://luger
				return new Fusil(type, "Luger P08", "Pow, Pow", "fusilIcone.png", new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Luger.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Luger.png")), ID, "metal", 0.871, 1.5, 10.0, 5.0, true, 8);
			case(1) ://thompson
				return new Fusil(type, "Thompson M1", "PPPPPow", "ThompsonIcone.png", new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Thompson.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Thompson.png")), ID, "metal", 4.47, 12, 5.0, 20.0, false, 30);
		}
		case (2) :
			switch (type % 10){
			case(0) ://note
				return nullptr;
			case(1) ://article
				return nullptr;
		}
		case (3) :
			switch (type % 10){
			case(0) ://thai
				return nullptr;
		}
		case (4) :
			switch (type % 10){
			case(0) ://balle
				return nullptr;
			case(1) ://roche
				return nullptr;
		}
		}
	}
};