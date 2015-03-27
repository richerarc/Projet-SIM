
class GestionnaireMenu : Singleton{
private:
	std::list<Menu*> Menus;

public:
	GestionnaireMenu(){

	}


	void retirerMenu(Menu* Menu){
		this->Menus.remove(Menu);
	}

	void ajouterMenu(Menu* Menu){
		this->Menus.push_back(Menu);
	}

	void vider(){
		if (this->Menus.empty == false){
			this->Menus.clear();
		}
	}

	std::list ObtenirListeMenu(){
		return this->Menus;
	}

	~GestionnaireMenu(){
		vider();
	}


};