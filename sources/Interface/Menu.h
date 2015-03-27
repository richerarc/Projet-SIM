class Menu{
private:

	std::list<ControleVisuel*> ListeControles;
	bool Actif;
	Sprite2D SpriteFond;

public:
	Menu(bool Actif, Sprite2D SpriteFond){
		this->Actif = Actif;
		this->SpriteFond = SpriteFond;
	}
	std::list ObtenirListeControle(){
		return ListeControles;
	}

};