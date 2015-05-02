#pragma once

class Curseur {

private:
	static Vecteur2f position;
	static int hauteur;
	gfx::Sprite2D* texture;
	int positionx;
	int positiony;
	

public:

	Curseur(Vecteur2f position) {
		positionx = 0;
		positiony = 0;
		this->position = position;
		texture = new gfx::Sprite2D(position, &gfx::GestionnaireRessources::obtInstance().obtTexture("Curseur.png"));
		hauteur = texture->obtTexture()->obtSurface()->h;
		GestionnaireEvenements::obtInstance().ajouterUnRappel(SDL_MOUSEMOTION, std::bind(&Curseur::gererEvenementSouris, this, std::placeholders::_1));
		GestionnaireEvenements::obtInstance().ajouterUnRappel(SDL_CONTROLLERAXISMOTION, std::bind(&Curseur::obtenirAxis, this, std::placeholders::_1));
	
	}

	void gererEvenementSouris(SDL_Event& event) {

		position.x += event.motion.xrel;
		position.y += -event.motion.yrel;
		
		texture->defPosition(position);

	}
	void obtenirAxis(SDL_Event& event){
		if (event.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX || event.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTX)
			positionx = (event.caxis.value) / 2000.0f;
		if (event.caxis.axis == SDL_CONTROLLER_AXIS_LEFTY || event.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTY)
			positiony = (event.caxis.value) / 2000.0f;
	}
	
	void rafraichir() {
		position.x += positionx;
		position.y -= positiony;
		texture->defPosition(position);
	}

	void remplir() {
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(texture);
	}

	static Vecteur2f obtPosition() {
		return Vecteur2f(position.x, position.y + hauteur);
	}

};

Vecteur2f Curseur::position;
int Curseur::hauteur(0);
