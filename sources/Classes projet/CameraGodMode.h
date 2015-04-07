#pragma once
#include "Camera.h"

namespace gfx{
	class CameraGodMode : public Camera{
	private:
		float vitesse;
		float sensibilite;

		float hAngle;
		float vAngle;

		void calculerVecteurs(){
			if (vAngle > 89)
				vAngle = 89;
			if (vAngle < -89)
				vAngle = -89;

			double vAngleRadian = vAngle * MATHS_PI / 180;
			double hAngleRadian = hAngle * MATHS_PI / 180;
			double cos_vAngle = cos(vAngleRadian);

			devant.x = cos_vAngle * sin(hAngleRadian);
			devant.y = sin(vAngleRadian);
			devant.z = cos_vAngle * cos(hAngleRadian);

			devant.normaliser();

			haut = Vecteur3d(0, 1, 0);

			cote = devant.produitVectoriel(haut);
			cote.normaliser();

			haut = cote.produitVectoriel(devant);
			haut.normaliser();

			construireMatrice();
		}
	public:

		CameraGodMode(Vecteur3d& position) : Camera(position, Vecteur3d(), Vecteur3d(0, 0, 1)){
			this->vitesse = 0.09;
			this->sensibilite = 0.15;
			
			this->hAngle = 0;
			this->vAngle = 0;

			calculerVecteurs();

			GestionnaireEvenements::obtInstance().ajouterUnRappel(SDL_MOUSEMOTION, std::bind(&CameraGodMode::surMouvementSouris, this, std::placeholders::_1));

			SDL_SetRelativeMouseMode(SDL_TRUE);
			SDL_ShowCursor(SDL_DISABLE);
		}

		~CameraGodMode(){
			SDL_SetRelativeMouseMode(SDL_FALSE);
			SDL_ShowCursor(SDL_ENABLE);
		}

		void surMouvementSouris(SDL_Event &event){
			hAngle -= event.motion.xrel * sensibilite;
			vAngle -= event.motion.yrel * sensibilite;
			calculerVecteurs();
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
				position.y += vitesse;
			if (Clavier::toucheAppuyee(SDLK_LSHIFT))
				position.y -= vitesse;
		}

		
		
	};
}