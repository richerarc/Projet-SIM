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
	}

	~Salle() {
		for (auto it : objets) {
			delete it;
		}
		gfx::Gestionnaire3D::obtInstance().retObjet(modele);
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

	void defEchelle(Vecteur3d& echelle){
		this->modele->defEchelle(echelle.x, echelle.y, echelle.z);
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
		for (auto it : objets){
			if (it->obtID() == ID)
				return it;
		}
		return nullptr;
	}

	std::list<Objet*>& obtListeObjet() {

		return objets;
	}
};