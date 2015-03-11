#pragma once

#ifndef Fabrique_Fabrique_h
#define Fabrique_Fabrique_h

Manque la classe model avant de la tester
class Fabrique : public Singleton<Fabrique> {
private:
	static int pos,
	itterateurID,
	nbrModelPiece,
	nbrModelConnecteur,
	nbrTexturePiece;
public:
	Salle obtSalle(bool typeSalle){ // true pour une pièce et false pour un connecteur
		switch (type) {
			case false:
				return Connecteur(Modele3D(GestionnaireRessources::obtInstance().obtModel(rand() % nbrModelConnecteur + 15), GestionnaireRessources::obtInstance().obtTexture(rand() % nbrTexturePiece)), ++this->itterateurID);
				break;
			default:
				return Piece(Modele3D(GestionnaireRessources::obtInstance().obtModel(rand() % nbrModelPiece), GestionnaireRessources::obtInstance().obtTexture(rand() % nbrTexturePiece)), ++this->itterateurID);
				break;
		}
	}
};

int Fabrique::pos = -100;
int Fabrique::itterateurID = 0;
int Fabrique::nbrModelPiece = 15;
int Fabrique::nbrModelConnecteur = 8;
int Fabrique::nbrTexturePiece = 6;
#endif
