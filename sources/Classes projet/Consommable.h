#pragma once 
#include "Melee.h"

struct Thai : public Melee{
	Thai(unsigned int ID) : Melee(0.3, 2.0, 30, "Felix's thai box", "Extremely hot General Tso's chicken", "Ressources/Texture/thaiIcone.png", 16, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/thai.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/thai.png")), ID, "carton", 0.76){

	}
	void utiliser2(Joueur* joueur){}
	void equiper(Joueur* joueur){}
};
struct Eau : public Melee{
	Eau(unsigned int ID) : Melee(0.3, 2.0, 30, "Water bottle", "Fresh old water", "Ressources/Texture/eauIcone.png", 16, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/eau.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/eau.png")), ID, "plastique", 0.4){

	}
	void utiliser2(Joueur* joueur){}
	void equiper(Joueur* joueur){}
};
struct Poulet : public Melee{
	Poulet(unsigned int ID) : Melee(0.3, 2.0, 30, "Chicken drumstick", "Colonel Sander would be proud of it", "Ressources/Texture/pouletIcone.png", 16, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/poulet.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/poulet.png")), ID, "plastique", 0.12){

	}
	void utiliser2(Joueur* joueur){}
	void equiper(Joueur* joueur){}
};
struct Pilule : public Melee{
	Pilule(unsigned int ID) : Melee(0.1, 2.0, 30, "Some pills", "This is your last chance. After this, there is no turning back.", "Ressources/Texture/piluleIcone.png", 16, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/pilule.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/pilule.png")), ID, "plastique", 0.05){

	}
	void utiliser2(Joueur* joueur){}
	void equiper(Joueur* joueur){}
};
struct Lait : public Melee{
	Lait(unsigned int ID) : Melee(0.3, 2.0, 30, "Milk carton", "You deserve Natrel", "Ressources/Texture/PinteDeLaitIcone.png", 16, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/PinteDeLait.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/PinteDeLait.png")), ID, "carton", 2.1){

	}
	void utiliser2(Joueur* joueur){}
	void equiper(Joueur* joueur){}
};
struct Chocolat : public Melee{
	Chocolate(unsigned int ID) : Melee(0.3, 2.0, 30, "Big Black Chocolate", "JEW won't belive it how good it tastes", "Ressources/Texture/chocolatIcone.png", 16, new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/chocolat.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/chocolat.png")), ID, "carton", 2.1){

	}
	void utiliser2(Joueur* joueur){}
	void equiper(Joueur* joueur){}
};