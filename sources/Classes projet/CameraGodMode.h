#pragma once
#include "Camera.h"
#include "Clavier.h"
namespace gfx{
	class CameraGodMode : public Camera{
	private:
		double vitesse;
	public:
		CameraGodMode(Vecteur3d& position) : Camera(position, Vecteur3d(), Vecteur3d(0, 0, 1)){
			this->vitesse = 0.09;
		}

		void deplacement(float frametime){
			if (Clavier::toucheAppuyee(SDLK_w))
				position += devant * vitesse * frametime;
			if (Clavier::toucheAppuyee(SDLK_s))
				position -= devant * vitesse * frametime;
			if (Clavier::toucheAppuyee(SDLK_a))
				position -= cote * vitesse * frametime;
			if (Clavier::toucheAppuyee(SDLK_d))
				position += cote * vitesse * frametime;
			if (Clavier::toucheAppuyee(SDLK_SPACE))
				position.y += vitesse * frametime;
			if (Clavier::toucheAppuyee(SDLK_LSHIFT))
				position.y -= vitesse * frametime;
		}

		
		
	};
}