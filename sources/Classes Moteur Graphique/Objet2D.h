#pragma once
#include "Vecteur3.h"
//Note à moi-même: AfficherTexture vs AfficherTexte
class Objet2D{
private:
	Vecteur3f position; 
	Vecteur3f orientation;
	Vecteur3f origine;
	Vecteur3i echelle;
public:
	Objet2D(Vecteur3f position, Vecteur3f orientation, Vecteur3f origine, Vecteur3i echelle){
		this->position = position;
		this->orientation = orientation;
		this->origine = origine;
		this->echelle = echelle;
	}
	void afficherTexte(Texte2D* texte){
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glColor3f(texte->obtCouleur().r, texte->obtCouleur().g, texte->obtCouleur().b);
		glRasterPos2i(position.x,position.y);
		for (std::string::iterator i = texte->obtTexte().begin(); i != texte->obtTexte().end(); ++i){
		}
	}

};