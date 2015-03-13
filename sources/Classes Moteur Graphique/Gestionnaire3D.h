class Gestionnaire3D
{
private:
	std::list<Objet3D*> objets;

public:
	Gestionnaire3D(){
	}

	void afficherTout(){
		for (auto &i : objets){
			i->afficher();
		}
	}

	void retObjet(Objet3D* objet){
		objets.remove(objet);
	}

	void ajouterObjet(Objet3D* Objet){
		objets.push_back(Objet);
	}

	void vider(){
		if (objets.empty == false){
			objets.clear();
		}
	}

	void defCamera(Camera3D Camera){

	}

	~Gestionnaire3D(){
		vider();
	}

};