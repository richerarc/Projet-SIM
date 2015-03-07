#pragma once

class Chrono {
private:

	unsigned int temps;

public:

	Chrono() {
		temps = 0;
	}

	void partir() {
		temps = SDL_GetTicks();
	}

	double obtenirTemps() {
		return SDL_GetTicks() - temps;
	}

};