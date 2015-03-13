
class Gestionnaire2D
{
private:
	std::list<Objet2D*> objets;

public:
	Gestionnaire2D(){		
	}

	void afficherTout(){	
		for (auto &i : objets){
			i->afficher();
		}		
	}
	
	void retObjet(Objet2D* objet){
		objets.remove(objet);
	}

	void ajouterObjet(Objet2D* Objet){
		objets.push_back(Objet);
	}

	void vider(){
		if (objets.empty == false){
			objets.clear();
		}
	}

	~Gestionnaire2D(){
		vider();
	}

};

