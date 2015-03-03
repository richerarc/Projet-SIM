

class Porte : public Contenu{
private:
	unsigned int ID;
	bool sortable;
	bool verrouillee;
public:
	Porte(Vecteur3<double> positionDepart, unsigned int identifiant, bool sortie, bool verrou){
		//Le modele de la porte est assignée ici, à faire quand tous les trucs de graphiques requis seront faits
		position = Vecteur<double>(positionDepart.x, positionDepart.y, positionDepart.z);
		ID = Identifiant;
		sortable = sortie;
		verrouillee = verrou;
	}

	unsigned int obtenirID(){
		return ID;
	}
	bool obtenirSortable(){
		return sortable;
	}
	void definirSortable(bool sortie){
		sortable = sortie;
	}
	bool obtenirVerrou(){
		return verrouillee;
	}
	void definirVerrou(bool verrou){
		verrouillee = verrou;
	}
};