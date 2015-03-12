class Salle{
private:
	int X,Y;
	int nbrLiens;
	int entre, sortie, sortix, sortiy, entrex, entrey;
	SDL_Renderer* Renderer;
public:
	Salle(SDL_Renderer* renderer, bool Type, int x, int y){
		X = 19 + 128 * x;
		Y = 7 + 103 * y;
		Renderer = renderer;
		SDL_Rect Rectangle;
		Rectangle.x = X;
		Rectangle.y = Y;
		Rectangle.w = 90;
		Rectangle.h = 90;
		if (Type){
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		}
		else{
			SDL_SetRenderDrawColor(renderer, 107, 142, 35, 255);
		}
		SDL_RenderDrawRect(renderer, &Rectangle);
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
};