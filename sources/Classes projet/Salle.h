#pragma once


class Salle{
protected:
	unsigned int ID;
	unsigned int nbrPortes;
	gfx::Modele3D* modele;
	std::list<Objet*> objets;
public:
	Salle(){}

	Salle(gfx::Modele3D* modele, unsigned int nbrPorte, int ID){
		nbrPortes = nbrPorte;
		this->ID = ID;
		this->modele = modele;
		gfx::Gestionnaire3D::obtInstance().ajouterObjet(this->modele);
		this->modele->defEchelle(3, 3, 3);
	}

	unsigned int obtNbrPortes(){
		return nbrPortes;
	}

	unsigned int obtID(){
		return ID;
	}

	void setID(unsigned int ID){
		this->ID = ID;
	}

	Vecteur3d obtPos(){
		return modele->obtPosition();
	}

	void defPosition(int axeX, int axeY, int axeZ){
		modele->defPosition(axeX, axeY, axeZ);
	}

	gfx::Modele3D* obtModele(){
		return modele;
	}
	
	void ajoutObjet(Objet *objet){
		objets.push_back(objet);
	}
	
	Objet* obtObjet(unsigned int ID){
		for(auto it: objets){
			if (it->obtID() == ID)
				return it;
		}
		return nullptr;
	}
	
	std::list<Objet*>& obtListeObjet() {
		
		return objets;
	}
};