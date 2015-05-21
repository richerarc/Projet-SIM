#pragma once
#include "Item.h"
#include "Melee.h"
#include "GestionnaireRessources.h"
#include "Fusil.h"

class UsineItem : public Singleton<UsineItem>{
public:
	Item* obtItemParType(int type, unsigned int ID){
		switch (type / 10){
			case (0) :
				switch (type % 10){
					case(0) ://couteau
						return new Melee(0.3, 20.0, type, "Knife", "Don't cut yourself, bro.", "Ressources/Texture/couteauIcone.png", 1, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/couteau.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/couteau.png")), ID, "metal", 0.545);
					case(1) ://chandelier
						return new Melee(0.5, 10.0, type, "Candlestick", "Use it to guide your path, or simply smash things...", "Ressources/Texture/chandelierIcone.png", 1, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/chandelier.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/chandelier.png")), ID, "metal", 3.0);
					case(2) ://HolyRod
						return new Melee(1.5, 236.0, type, "HolyRod", "The divine window opener!", "Ressources/Texture/HolyRod236Icone.png", 1, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/HolyRod236.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/HolyRod236.png")), ID, "metal", 1.0);
				}
			case (1) :
				switch (type % 10){
					case(0) ://luger
						return new Fusil(type, "Luger P08", "Pow, Pow", "Ressources/Texture/fusilIcone.png", new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/luger.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/luger.png")), ID, "metal", 0.871, 1.5, 10.0, 5.0, true, 8);;
					case(1) ://thompson
						return new Fusil(type, "Thompson M1", "PPPPPow", "Ressources/Texture/fusilIcone.png", new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/thai.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/thai.png")), ID, "metal", 4.47, 12, 5.0, 20.0, false, 30);;
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
		return nullptr;
	}
};