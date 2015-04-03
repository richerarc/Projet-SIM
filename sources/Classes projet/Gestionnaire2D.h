#pragma once
#include <list>
#include "Fenetre.h"
#include "Sprite2D.h"
#include "Texte2D.h"
#include "Singleton.h"
namespace gfx{
	class Gestionnaire2D : public Singleton<Gestionnaire2D>
	{
	private:
		std::list<gfx::Objet2D*> objets;

	public:

		void afficherTout(gfx::Fenetre& fenetre){
			for (auto &i : objets){
				i->afficher(fenetre);
			}
		}

		void retObjet(gfx::Objet2D* objet){
			objets.remove(objet);
		}

		void ajouterObjet(gfx::Objet2D* Objet){
			objets.push_back(Objet);
		}

		void vider(){
			if ((!objets.empty()))
				objets.clear();
		}

		~Gestionnaire2D(){
			vider();
		}

	};
}
