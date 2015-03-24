class Menu{
private:

	std::list<ControleVisuel*> Controles;

public:

	std::list ObtenirListeControle(){
		return Controles;
	}

};