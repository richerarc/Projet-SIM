class Salle{
private:
	int X,Y;
	int nbrLiens;
	int entre, sortie, sortix, sortiy, entrex, entrey;
	SDL_Renderer* Renderer;
	bool typeSalle;
public:
	Salle(SDL_Renderer* renderer, bool Type, int x, int y,int nbrLiens){
		X = 19 + 128 * x;
		Y = 7 + 103 * y;
		Renderer = renderer;
		SDL_Rect Rectangle;
		Rectangle.x = X;
		Rectangle.y = Y;
		Rectangle.w = 90;
		Rectangle.h = 90;
		typeSalle = Type;
		this->nbrLiens = nbrLiens;
	}
	int obtEntree(){
		return entre;
	}
	int obtSortie(){
		return sortie;
	}

	int obtNbrLiens(){
		return nbrLiens;
	}

	void defNbrLiens(int nbrLiens){
		this->nbrLiens = nbrLiens;
	}

	int obtX(){
		return X;
	}

	int obtY(){
		return Y;
	}

	int obtSortieX(){
		return sortix;
	}

	int obtSortieY(){
		return sortiy;
	}
	/*
	void lierAvec(Salle* salleSorti, bool TypeLien){
			switch (entre){
			case 0:
				entrex =X;
				entrey =Y + 45;
				entre++;
				break;
			case 1:
				entrex =X + 90;
				entrey =Y + 45;
				entre++;
				break;
			case 2:
				entrex =X + 45;
				entrey =Y;
				entre++;
				break;
			case 3:
				entrex =X + 45;
				entrey =Y + 90;
				entre++;
				break;	
			}
			switch (sortie){
			case 0:
				sortix = salleSorti->obtX();
				sortiy = salleSorti->obtY() + 45;
				sortie++;
				break;
			case 1:
				sortix = salleSorti->obtX() + 90;
				sortiy = salleSorti->obtY() + 45;
				sortie++;
				break;
			case 2:
				sortix = salleSorti->obtX() + 45;
				sortiy = salleSorti->obtY();
				sortie++;
				break;
			case 3:
				sortix = salleSorti->obtX() + 45;
				sortiy = salleSorti->obtY() + 90;
				sortie++;
				break;
			}
		if (TypeLien){ //si Porte
			SDL_SetRenderDrawColor(Renderer, 0, 255, 0, 255);
		}
		else{ // Si portail
			SDL_Rect Rectangle;
			Rectangle.x = sortix;
			Rectangle.y = sortiy;
			Rectangle.w = 10;
			Rectangle.h = 10;
			SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 255);
			SDL_RenderDrawRect(Renderer, &Rectangle);
			SDL_SetRenderDrawColor(Renderer, 0, 0, 255, 255);
		}

		SDL_RenderDrawLine(Renderer, entrex, entrey, sortix, sortiy);//Créer ligne
	}
	*/
	void lierAvec(Salle* salleSorti, bool TypeLien, int IDPorteEntree, int IDPorteSortie){
		switch (IDPorteEntree){
		case 0:
			entrex = X;
			entrey = Y + 45;
			entre++;
			break;
		case 1:
			entrex = X + 90;
			entrey = Y + 45;
			entre++;
			break;
		case 2:
			entrex = X + 45;
			entrey = Y;
			entre++;
			break;
		case 3:
			entrex = X + 45;
			entrey = Y + 90;
			entre++;
			break;
		}
		switch (IDPorteSortie){
		case 0:
			sortix = salleSorti->obtX();
			sortiy = salleSorti->obtY() + 45;
			sortie++;
			break;
		case 1:
			sortix = salleSorti->obtX() + 90;
			sortiy = salleSorti->obtY() + 45;
			sortie++;
			break;
		case 2:
			sortix = salleSorti->obtX() + 45;
			sortiy = salleSorti->obtY();
			sortie++;
			break;
		case 3:
			sortix = salleSorti->obtX() + 45;
			sortiy = salleSorti->obtY() + 90;
			sortie++;
			break;
		}
		if (TypeLien){ //si Porte
			SDL_SetRenderDrawColor(Renderer, 0, 255, 0, 255);
			SDL_Rect Rectangle;
			Rectangle.x = sortix + 1;
			Rectangle.y = sortiy + 1;
			Rectangle.w = 10;
			Rectangle.h = 10;
			SDL_RenderDrawRect(Renderer, &Rectangle);
		}
		else{ // Si portail
			SDL_Rect Rectangle;
			Rectangle.x = sortix;
			Rectangle.y = sortiy;
			Rectangle.w = 10;
			Rectangle.h = 10;
			SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 255);
			SDL_RenderDrawRect(Renderer, &Rectangle);
			SDL_SetRenderDrawColor(Renderer, 0, 0, 255, 255);
		}

		SDL_RenderDrawLine(Renderer, entrex, entrey, sortix, sortiy);//Créer ligne
	}
	void dessinerSalle(){
		SDL_Rect Rectangle;
		Rectangle.x = X;
		Rectangle.y = Y;
		Rectangle.w = 90;
		Rectangle.h = 90;
		if (typeSalle){
			SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
		}
		else{
			SDL_SetRenderDrawColor(Renderer, 107, 142, 35, 255);
		}
		SDL_RenderDrawRect(Renderer, &Rectangle);
		switch (nbrLiens){
		case 1:
			SDL_RenderDrawLine(Renderer, X + 20, Y + 20, X + 20, Y + 50);
			break;
		case 2:
			SDL_RenderDrawLine(Renderer, X + 20, Y + 20, X + 20, Y + 50);
			SDL_RenderDrawLine(Renderer, X + 25, Y + 20, X + 25, Y + 50);
			break;
		case 3:
			SDL_RenderDrawLine(Renderer, X + 20, Y + 20, X + 20, Y + 50);
			SDL_RenderDrawLine(Renderer, X + 25, Y + 20, X + 25, Y + 50);
			SDL_RenderDrawLine(Renderer, X + 30, Y + 20, X + 30, Y + 50);
			break;
		case 4:
			SDL_RenderDrawLine(Renderer, X + 20, Y + 20, X + 20, Y + 50);
			SDL_RenderDrawLine(Renderer, X + 25, Y + 20, X + 25, Y + 50);
			SDL_RenderDrawLine(Renderer, X + 30, Y + 20, X + 30, Y + 50);
			SDL_RenderDrawLine(Renderer, X + 35, Y + 20, X + 35, Y + 50);
			break;
		}
	}
};