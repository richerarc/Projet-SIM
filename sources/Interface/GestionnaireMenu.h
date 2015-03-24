class GestionnaireMenu{
private:
	std::list<Menu*> Menus;

public:
	GestionnaireMenu(){

	}


	void retirerMenu(Menu* Menu){
		Menus.remove(Menu);
	}

	void ajouterMenu(Menu* Menu){
		Menus.push_back(Menu);
	}

	void vider(){
		if (Menus.empty == false){
			Menus.clear();
		}
	}

	std::list ObtenirListeMenu(){
		return Menus;
	}

	~GestionnaireMenu(){
		vider();
	}


};