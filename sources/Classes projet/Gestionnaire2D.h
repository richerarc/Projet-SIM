#pragma once
#include <list>
#include <initializer_list>
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

		void retObjets(std::initializer_list<gfx::Objet2D*> list){
			for (auto i : list){
				objets.remove(i);
			}
		}

		void ajouterObjet(gfx::Objet2D* obj){
			objets.push_back(obj);
		}

		void ajouterObjets(std::initializer_list<gfx::Objet2D*> list){
			objets.insert(objets.end(), list.begin(), list.end());
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
