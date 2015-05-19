 #pragma once
#include <map>
#include <tuple>
#include <vector>
#include <list>
#include <fstream>
#include <cmath>
#include "Modele3D.h"
#include "Porte.h"
#include "Salle.h"
#include "Info.h"
#include "Graphe.h"
#include "GestionnaireChemin.h"
#include "GestionnaireRessources.h"
#include "Gestionnaire3D.h"
#include "LecteurFichier.h"
#include "Joueur.h"
#include "Physique.h"
#include "Remplisseur.h"
//#include "Balance.h"
#include "ControlleurAudio.h"
#include "Vent.h"

typedef std::tuple<unsigned int, unsigned int, bool> Entree;
typedef std::tuple<unsigned int, unsigned int> Sortie;
typedef std::tuple<char*, char*, char*> Modele_Text;

class Carte : public Singleton < Carte > {
private:
	graphe::Graphe carte;
	std::map<Entree, Sortie> liens;
	std::list<InfoSalle> infosSalles;
	gfx::Modele3D *modeleMur;
	gfx::Modele3D *modelePorte;

	Vecteur3d translationVersPositionASJoueur;
	Vecteur3d translationVersPositionNSFinaleJoueur;
	Vecteur3d positionASJoueur;
	Vecteur3d positionNSInitialeJoueur;
	Vecteur3d positionNSFinaleJoueur;
	double orientationInitialeCamera;
	double orientationFinaleCamera;
	double vitesseHRotation;
	double vitesseVRotation;
	bool enChangementDeSalle;
	bool teleporte;
	Sortie salleSuivante;

	std::vector<Modele_Text> cheminsModeleText;
	std::vector<char*> cheminsPuzzle;

	int obtElementListe(std::list<int> liste, int ID) {
		auto it = liste.begin();

		for (int i = 0; i < ID; ++i)
			++it;

		return *it;
	}

	void ajouterLien(Entree entree, Sortie sortie){
		liens[entree] = sortie;
	}

	bool positionnerPuzzle(InfoSalle& salle, InfoPuzzle& puzzle) {

		bool puzzlePlace = false;
		std::vector<int> nombreBoite;
		std::vector<int>::iterator itBoites;
		BoiteCollision<double> boiteSalle;
		BoiteCollision<double> boitePuzzleTemp;
		InfoObjet remplisseur;

		remplisseur.cheminModele = "Ressources/Modele/Remplisseur.obj";
		remplisseur.cheminTexture = "Ressources/Texture/Remplisseur.png";
		remplisseur.type = REMPLISSEUR;

		for (int i = 0; i < salle.boitesCollision.size(); ++i)
			nombreBoite.push_back(i);

		int aleatoire = rand() % nombreBoite.size();
		boiteSalle = salle.obtBoiteCollisionModifie(nombreBoite[aleatoire]);
		itBoites = nombreBoite.begin();
		for (int i = 0; i < aleatoire; ++i) ++itBoites;

		while (!puzzlePlace && nombreBoite.size()!= 0) {
			
			nombreBoite.erase(itBoites);
			puzzle.position = boiteSalle.distanceEntreDeuxCentre(puzzle.boiteCollision);
			boitePuzzleTemp = puzzle.obtBoiteCollisionModifie();

			if (!boiteSalle.boiteDansBoite(boitePuzzleTemp)){

				if (boiteSalle.obtGrandeurX() - boiteSalle.obtGrandeurZ() < 0){
					double deltaXmen;
					for (auto &it : puzzle.objet){
						deltaXmen = fabs(it.position.x - puzzle.boiteCollision.obtCentreBoite().x);
						it.rotation = 270;
						if (it.position.x < 0){
							it.position.x += deltaXmen;
							it.position.z -= deltaXmen;
						}
						else{
							it.position.x -= deltaXmen;
							it.position.z += deltaXmen;
						}
					}
					puzzle.rotation = 270;
				}
				else{
					puzzle.rotation = 0;
				}
				boitePuzzleTemp = puzzle.obtBoiteCollisionModifie();
			}

			for (auto &it : puzzle.objet)
				it.position += puzzle.position;

			if (boiteSalle.boiteDansBoite(boitePuzzleTemp)){
				if ((puzzle.entrees[0] && puzzle.entrees[2] && !puzzle.entrees[1] && !puzzle.entrees[3] && puzzle.rotation == 0) || (!puzzle.entrees[0] && !puzzle.entrees[2] && puzzle.entrees[1] && puzzle.entrees[3] && puzzle.rotation == 270)) {
					remplisseur.largeur = boiteSalle.obtGrandeurX();
					remplisseur.rotation = 0;
					remplisseur.position = Vecteur3d(boiteSalle.obtXMin(), 1, boitePuzzleTemp.obtZMin());
					puzzle.objet.push_back(remplisseur);
					remplisseur.rotation = 180;
					remplisseur.position = Vecteur3d(boiteSalle.obtXMax(), 1, boitePuzzleTemp.obtZMax());
					puzzle.objet.push_back(remplisseur);
				}

				else if ((!puzzle.entrees[0] && !puzzle.entrees[2] && puzzle.entrees[1] && puzzle.entrees[3] && puzzle.rotation == 0) || (puzzle.entrees[0] && puzzle.entrees[2] && !puzzle.entrees[1] && !puzzle.entrees[3] && puzzle.rotation == 270)) {
					remplisseur.largeur = boiteSalle.obtGrandeurZ();
					remplisseur.rotation = 270;
					remplisseur.position = Vecteur3d(boitePuzzleTemp.obtXMax(), 1, boiteSalle.obtZMin());
					puzzle.objet.push_back(remplisseur);
					remplisseur.rotation = 90;
					remplisseur.position = Vecteur3d(boitePuzzleTemp.obtXMin(), 1, boiteSalle.obtZMax());
					puzzle.objet.push_back(remplisseur);
				}

				for (auto &it : puzzle.objet){
					salle.Objet.push_back(it);
				}
				return true;
			}
			else {
				if (nombreBoite.size() > 0) {
					aleatoire = rand() % nombreBoite.size();
					boiteSalle = salle.obtBoiteCollisionModifie(nombreBoite[aleatoire]);
					itBoites = nombreBoite.begin();
					for (int i = 0; i < aleatoire; ++i) ++itBoites;
				}
			}
		}
		return false;
	}

	void positionnerPorte(gfx::Modele3D& modeleSalle, InfoSalle& salle, InfoObjet& objet) {
		unsigned int depart;
		Vecteur3d normale;
		Vecteur3d point[3];
		Vecteur3d swap;

		bool PorteAuMur = false;
		double* vertices = modeleSalle.obtSommetsModifies();
		double* normales = modeleSalle.obtNormalesModifies();
		while (!PorteAuMur)
		{
			PorteAuMur = true;
			do{
				double y;
				do{
					depart = (rand() % modeleSalle.obtModele()->obtNbrFaces()) * 9;
					normale = { normales[depart], normales[depart + 1], normales[depart + 2] };
				} while (normale.y != 0);
				for (int i = 0; i < 3; ++i) {

					point[i] = { vertices[depart + i * 3], vertices[depart + i * 3 + 1], vertices[depart + i * 3 + 2] };

				}
			} while (!espacePorte(point[0], point[1], point[2]));
			normale.normaliser();
			// Angle de la porte...
			objet.rotation = (Vecteur3d({ -1, 0, 0 }).produitScalaire(normale) < 0) ? (90 - Maths::radianADegre(Vecteur3d({ -1, 0, 0 }).produitVectoriel(Vecteur3d({ 0, 1, 0 })).angleEntreVecteurs(normale)))
				: (270 - Maths::radianADegre(Vecteur3d({ -1, 0, 0 }).produitVectoriel(Vecteur3d({ 0, -1, 0 })).angleEntreVecteurs(normale)));

			objet.direction = normale * -1;

			double y1 = point[0].y;
			double y2;
			do {
				y2 = point[rand() % 2 + 1].y;
			} while (y1 == y2);

			objet.position.y = (y1 < y2) ? y1 : y2;

			unsigned int i;
			unsigned int j;
			do {
				do{
					i = rand() % 3;
					j = rand() % 3;
				} while (i == j);
			} while (point[i].y != point[j].y);

			// Positionnement des points de blender dans le même sens...
			if (abs(normale.x) != 1 && abs(normale.z) != 1) {
				if ((normale.x >= 0 && normale.z >= 0) || (normale.x < 0 && normale.z >= 0)) {
					if (point[i].x > point[j].x) {
						swap = point[i];
						point[i] = point[j];
						point[j] = swap;
					}
				}
				else if ((normale.x < 0 && normale.z < 0) || (normale.x >= 0 && normale.z < 0)) {
					if (point[i].x < point[j].x) {
						swap = point[i];
						point[i] = point[j];
						point[j] = swap;
					}
				}
			}
			else
			{
				switch ((int)normale.x) {
				case 1:
					if (point[i].z < point[j].z) {
						swap = point[i];
						point[i] = point[j];
						point[j] = swap;
					}
					break;
				case -1:
					if (point[i].z > point[j].z) {
						swap = point[i];
						point[i] = point[j];
						point[j] = swap;
					}
					break;
				}
				switch ((int)normale.z) {
				case 1:
					if (point[i].x > point[j].x) {
						swap = point[i];
						point[i] = point[j];
						point[j] = swap;
					}
					break;
				case -1:
					if (point[i].x < point[j].x) {
						swap = point[i];
						point[i] = point[j];
						point[j] = swap;
					}
					break;
				}
			}

			Vecteur3d vecteurRatio = Maths::vecteurEntreDeuxPoints(point[i], point[j]);
			vecteurRatio *= ((vecteurRatio.norme() - 1.471) / vecteurRatio.norme());
			vecteurRatio *= ((double)rand() / RAND_MAX);
			vecteurRatio = point[i] + vecteurRatio;
			objet.position.x = vecteurRatio.x;
			objet.position.z = vecteurRatio.z;

			// Boucle qui vérifie si une porte sera en collision avec une autre...
			Vecteur3d pivot = { 0, 1, 0 };
			for (auto it_Porte : salle.Objet) {

				if (it_Porte.largeur != 0) {

					if (it_Porte.rotation == 0) {
						if (objet.position.z >= it_Porte.position.z && (objet.position.x <= it_Porte.position.x && objet.position.x >= it_Porte.position.x + it_Porte.largeur))
							PorteAuMur = false;
					}
					else if (it_Porte.rotation == 180) {
						if (objet.position.z <= it_Porte.position.z && (objet.position.x >= it_Porte.position.x && objet.position.x <= it_Porte.position.x + it_Porte.largeur))
							PorteAuMur = false;
					}
					else if (it_Porte.rotation == 270) {
						if (objet.position.x <= it_Porte.position.x && (objet.position.z >= it_Porte.position.z + it_Porte.largeur && objet.position.z <= it_Porte.position.z))
							PorteAuMur = false;
					}
					else if (it_Porte.rotation == 90) {
						if (objet.position.x >= it_Porte.position.x && (objet.position.z <= it_Porte.position.z + it_Porte.largeur && objet.position.z >= it_Porte.position.z))
							PorteAuMur = false;
					}
				}

				// Si les portes ont la même direction...
				else if ((objet.direction == it_Porte.direction) && !(objet.position == it_Porte.position)) {

					if (Maths::distanceEntreDeuxPoints(objet.position, it_Porte.position) <= 1.471) {
						PorteAuMur = false;
					}
				}
			}
		}
	}

	bool espacePorte(Vecteur3d point1, Vecteur3d point2, Vecteur3d point3) {

		if (point1.y != point2.y && point1.y != point3.y && point2.y != point3.y) {
			return false;
		}

		Vecteur3d pointDeCalcul1;
		Vecteur3d pointDeCalcul2;

		if (point1.y != point2.y && point1.y != point3.y) {
			pointDeCalcul1 = point1;
			if (point1.x == point2.x && point1.z == point2.z) {
				pointDeCalcul2 = point3;
			}
			else
			{
				pointDeCalcul2 = point2;
			}
		}
		else if (point2.y != point1.y && point2.y != point3.y) {
			pointDeCalcul1 = point2;
			if (point2.x == point3.x && point2.z == point3.z) {
				pointDeCalcul2 = point1;
			}
			else
			{
				pointDeCalcul2 = point3;
			}
		}
		else {
			pointDeCalcul1 = point3;
			if (point3.x == point1.x && point3.z == point1.z) {
				pointDeCalcul2 = point2;
			}
			else
			{
				pointDeCalcul2 = point1;
			}
		}

		Vecteur3d hypothenuse = Maths::vecteurEntreDeuxPoints(pointDeCalcul1, pointDeCalcul2);

		if (abs(hypothenuse.y) <= 2.71) {
			return false;
		}

		if (SDL_sqrt(SDL_pow(hypothenuse.x, 2) + SDL_pow(hypothenuse.z, 2)) <= 1.471) {
			return false;
		}
		return true;
	}

	void creerSalle(InfoSalle& infoSalleActive) {

		salleActive = new Salle(new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele(infoSalleActive.cheminModele), gfx::GestionnaireRessources::obtInstance().obtTexture(infoSalleActive.cheminTexture)), infoSalleActive.nbrPorte, infoSalleActive.ID);
		salleActive->defEchelle(infoSalleActive.echelle);
		double phasePendule = MATHS_PI;

		for (auto& it : infoSalleActive.Objet) {
			gfx::Modele3D* modeleporte = new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele(it.cheminModele), gfx::GestionnaireRessources::obtInstance().obtTexture(it.cheminTexture));
			modeleporte->defPosition(it.position);
			modeleporte->defOrientation(0, it.rotation, 0);
			switch (it.type) {
				case PORTE:
					salleActive->ajoutObjet(new Porte(modeleporte, it.ID, "metal", it.position, { 0, 0, 0 }, false, true, false, false));
					break;
				case PENDULE:
					if (!it.rotation)
						salleActive->ajoutObjet(new Pendule(modeleporte, it.ID, "metal", it.position, { 2, 0, 0 }, false, false, phasePendule += (rand() % 4 + 1) / MATHS_PI, 30));
					else
						salleActive->ajoutObjet(new Pendule(modeleporte, it.ID, "metal", it.position, { 0, 0, 2 }, false, false, phasePendule += (rand() % 4 + 1) / MATHS_PI, 30));
					break;
				case FIXE:
					salleActive->ajoutObjet(new ObjetFixe(modeleporte, it.ID, "metal", it.position, { 0, 0, 0 }, false, false));
					break;
				case REMPLISSEUR:
					salleActive->ajoutObjet(new Remplisseur(modeleporte, it.largeur, it.position, it.ID));
					break;
				case VENT:
					salleActive->ajoutObjet(new Vent(modeleporte, it.ID, Vecteur3d(0,5,0), it.position, Vecteur3d(it.largeur, 20, it.largeur)));
					break;
			}
		}

		salleActive->remplir();
	}

	bool creerPuzzle(int &nbrPuzzle, int IDSalle) {

		InfoSalle& salle = *std::find_if(std::begin(infosSalles), std::end(infosSalles), [&](InfoSalle info){ return info.ID == IDSalle; });
		InfoPuzzle puzzle;
		bool puzzlePlace = false;
		int aleatoire;

		aleatoire = rand() % nbrPuzzle;
		LecteurFichier::lirePuzzle(cheminsPuzzle[aleatoire], puzzle);
		puzzle.rotation = 0;

		if (positionnerPuzzle(salle, puzzle)) {
			--nbrPuzzle;
			cheminsPuzzle.erase(std::find_if(cheminsPuzzle.begin(), cheminsPuzzle.end(), [&](char* chemin){return !strcmp(chemin, cheminsPuzzle[aleatoire]);}));
			return true;
		}
		return false;
	}

public:

	Salle *salleActive;
	unsigned int nombreDeSalle;
	double chargement;
	bool finChargement;
	int salle;

	int destination(Entree entree, Joueur *joueur) {

		joueur->bloquer();
		joueur->defVitesse(Vecteur3d(0, 0, 0));

		salleSuivante = liens[entree];

		auto sallePrecedente = infosSalles.begin();
		std::advance(sallePrecedente, std::get<0>(entree));
		auto portePrecedente = (*sallePrecedente).Objet.begin();
		std::advance(portePrecedente, std::get<1>(entree));

		// Calcul de la rotation de camÃ©ra Ã  appliquer:
		// {

		orientationInitialeCamera = vitesseHRotation = portePrecedente->rotation + 270;

		if (vitesseHRotation > 360)
			vitesseHRotation -= 360;

		if (orientationInitialeCamera > 360)
			orientationInitialeCamera -= 360;

		vitesseHRotation -= joueur->obtCamera()->obtHAngle();

		if (vitesseHRotation < -180) {
			vitesseHRotation += 360;
		}

		vitesseVRotation = joueur->obtCamera()->obtVAngle() * -1;

		// }

		// Calcul de la translation Ã  appliquer sur le joueur...
		// {

		positionASJoueur = portePrecedente->position + (portePrecedente->direction.produitVectoriel(Vecteur3d(0, 1, 0)) * 0.7352941176) - (portePrecedente->direction * 1.5);

		translationVersPositionASJoueur = Maths::vecteurEntreDeuxPoints(joueur->obtPosition(), positionASJoueur);
		translationVersPositionASJoueur.normaliser();

		// }

		// Calcul de la nouvelle position du joueur et mur/porte
		// {

		auto debut = infosSalles.begin();
		std::advance(debut, std::get<0>(salleSuivante));

		auto it = (*debut).Objet.begin();
		std::advance(it, std::get<1>(salleSuivante));

		// DÃ©finition de la position du faux mur, de la fausse porte et du joueur...
		Vecteur3d positionMur = it->position - (it->direction * 1.68);

		modeleMur->defPosition(positionMur);
		modelePorte->defPosition(positionMur.x - (1.470588235 * it->direction.z), positionMur.y, positionMur.z + (1.470588235 * it->direction.x));
		modeleMur->defOrientation(0, it->rotation, 0);
		modelePorte->defOrientation(0, it->rotation + 180, 0);

		positionNSInitialeJoueur = it->position + (it->direction.produitVectoriel(Vecteur3d(0, 1, 0)) * 0.7352941176) - (it->direction * 0.18);
		positionNSFinaleJoueur = positionNSInitialeJoueur - (it->direction * 1.5);

		translationVersPositionNSFinaleJoueur = Maths::vecteurEntreDeuxPoints(positionNSInitialeJoueur, positionNSFinaleJoueur);
		translationVersPositionNSFinaleJoueur.normaliser();

		orientationFinaleCamera = it->rotation + 90;

		if (orientationFinaleCamera > 360)
			orientationFinaleCamera -= 360;

		// }

		teleporte = false;
		enChangementDeSalle = true;
		return std::get<1>(salleSuivante);
	}

	void transitionSalle(Joueur* joueur, float frametime) {
		if (enChangementDeSalle) {
			if (!teleporte) {
				// Ajustement de la camÃ©ra horizontale...
				if (joueur->obtCamera()->obtHAngle() != orientationInitialeCamera) {
					if (vitesseHRotation < 0) {
						if ((joueur->obtCamera()->obtHAngle() + (vitesseHRotation * frametime)) <= orientationInitialeCamera)
							joueur->defHAngle(orientationInitialeCamera);
						else
						{
							joueur->defHAngle(joueur->obtCamera()->obtHAngle() + (vitesseHRotation * frametime));
						}
					}
					else
					{
						if (joueur->obtCamera()->obtHAngle() + (vitesseHRotation * frametime) >= orientationInitialeCamera)
							joueur->defHAngle(orientationInitialeCamera);
						else
						{
							joueur->defHAngle(joueur->obtCamera()->obtHAngle() + (vitesseHRotation * frametime));
						}
					}
				}

				// Ajustement de la camÃ©ra verticale...
				if (joueur->obtCamera()->obtVAngle() != 0) {
					joueur->defVAngle(joueur->obtCamera()->obtVAngle() + (vitesseVRotation * frametime));
					if (vitesseVRotation < 0) {
						if (joueur->obtCamera()->obtVAngle() < 0)
							joueur->defVAngle(0);
					}
					else
					{
						if (joueur->obtCamera()->obtVAngle() > 0)
							joueur->defVAngle(0);
					}
				}

				if (translationVersPositionASJoueur.produitScalaire(Maths::vecteurEntreDeuxPoints(joueur->obtPosition(), positionASJoueur)) > 0) {
					joueur->defPosition(joueur->obtPosition() + (translationVersPositionASJoueur * frametime * 1.5));
				}
				else
				{
					joueur->defPosition(positionASJoueur);
				}

				if (joueur->obtCamera()->obtHAngle() == orientationInitialeCamera && joueur->obtCamera()->obtVAngle() == 0 && joueur->obtPosition() == positionASJoueur) {
					teleporte = true;
					delete salleActive;
					auto debut = infosSalles.begin();
					std::advance(debut, std::get<0>(salleSuivante));

					creerSalle(*debut);

					ajouterMur();
					joueur->defPosition(positionNSInitialeJoueur);
					joueur->defHAngle(orientationFinaleCamera);
					ControlleurAudio::obtInstance().jouer(OUVERTURE_PORTE_1, joueur);
				}
			}
			else
			{
				if (translationVersPositionNSFinaleJoueur.produitScalaire(Maths::vecteurEntreDeuxPoints(joueur->obtPosition(), positionNSFinaleJoueur)) > 0) {
					joueur->defPosition(joueur->obtPosition() + (translationVersPositionNSFinaleJoueur * frametime));
					modelePorte->rotationner(0, 1.6, 0);
				}
				else
				{
					joueur->defPosition(positionNSFinaleJoueur);
					retirerMur();
					joueur->deBloquer();
					enChangementDeSalle = false;
					ControlleurAudio::obtInstance().jouer(FERMETURE_PORTE, joueur);
				}
			}
		}
	}

	void ajouterMur(){
		gfx::Gestionnaire3D::obtInstance().ajouterObjet(modeleMur);
		gfx::Gestionnaire3D::obtInstance().ajouterObjet(modelePorte);
	}

	void retirerMur(){
		gfx::Gestionnaire3D::obtInstance().retObjet(modeleMur);
		gfx::Gestionnaire3D::obtInstance().retObjet(modelePorte);
	}

	// Procédure qui permet de créer le graphe et la première salle dans laquelle le joueur commence...
	void creer() {
		srand(time(NULL));

		// Création du graphe
		carte.creer(nombreDeSalle);
		int itterateurPorte(0);

		chargement = 0;
		finChargement = false;

		int* porte = new int[nombreDeSalle];
		Entree entree;
		Sortie sortie;
		for (unsigned int i = 0; i < nombreDeSalle; ++i)
			porte[i] = carte.degreSortant(i);

		for (unsigned int i = 0; i < nombreDeSalle; ++i){
			itterateurPorte = 0;
			for (unsigned int j = 0; j < nombreDeSalle; ++j){
				if (carte.matrice[i * nombreDeSalle + j]){
					entree = std::make_tuple(i, itterateurPorte++, false);
					sortie = std::make_tuple(j, rand() % porte[j]);
					ajouterLien(entree, sortie);
					Sortie pieceSuivante = liens[entree];
				}
			}
		}

		// Load des salles possibles
		std::ifstream fichierSalle("Ressources/Info/salle_text.txt");
		std::ifstream fichierObjet("Ressources/Info/objet_text.txt");
		std::ifstream fichierPuzzle("Ressources/Info/puzzle_text.txt");

		int itterateur(0);
		while (!fichierSalle.eof()) {
			char* curseur1 = new char[255];
			char* curseur2 = new char[255];
			char* curseur3 = new char[255];
			fichierSalle >> curseur1; fichierSalle >> curseur2; fichierSalle >> curseur3;
			cheminsModeleText.push_back(Modele_Text(curseur1, curseur2, curseur3));
			++itterateur;
		}

		int nbrPuzzle(0);
		while (!fichierPuzzle.eof()) {
			char* curseur1 = new char[20];
			fichierPuzzle >> curseur1;
			cheminsPuzzle.push_back(curseur1);
			++nbrPuzzle;
		}

		unsigned int aleatoire;
		InfoObjet objet;
		InfoSalle salle;
		gfx::Modele3D* modeleSalle;

		// Boucle sur toutes les salles...
		for (unsigned int i = 0; i < nombreDeSalle; ++i) {

			salle.ID = i;
			salle.nbrPorte = carte.degreSortant(i);
			salle.echelle = { 3, 2, 3 };

			aleatoire = rand() % itterateur;

			salle.cheminModele = (char*)(std::get<0>(cheminsModeleText[aleatoire]));
			salle.cheminTexture = (char*)(std::get<1>(cheminsModeleText[aleatoire]));
			LecteurFichier::lireBoite(std::get<2>(cheminsModeleText[aleatoire]), salle);
			infosSalles.push_back(salle);
			salle.boitesCollision.clear();
			salle.Objet.clear();
		}

		int IDSalle(0);
		int prochaineSalle;
		bool salleCorrecte;
		std::list<int> salleSuivante;
		std::vector<int> salleAvecPuzzle;

		do {
			IDSalle = rand() % nombreDeSalle;
		}
		while (!creerPuzzle(nbrPuzzle, IDSalle));
		salleAvecPuzzle.push_back(IDSalle);

		for (int i = 1; i < nombreDeSalle / 3 && nbrPuzzle > 0; ++i) {

			do {
				salleSuivante = carte.obtListeAdjacence(IDSalle);
				prochaineSalle = obtElementListe(salleSuivante, rand() % salleSuivante.size());
				salleSuivante = carte.obtListeAdjacence(prochaineSalle);
				int nbrEssais(0);
				do {
					salleCorrecte = true;
					if (nbrEssais > 10) {
						salleSuivante = carte.obtListeAdjacence(IDSalle);
						prochaineSalle = obtElementListe(salleSuivante, rand() % salleSuivante.size());
						salleSuivante = carte.obtListeAdjacence(prochaineSalle);
						nbrEssais = 0;
					}
					prochaineSalle = obtElementListe(salleSuivante, rand() % salleSuivante.size());
					salleSuivante = carte.obtListeAdjacence(prochaineSalle);

					for (int j = 0; j < salleAvecPuzzle.size() && salleCorrecte; ++j) {
						salleCorrecte = !((salleAvecPuzzle[j] == prochaineSalle));
						++nbrEssais;
					}
				} while (!salleCorrecte);
			} while (!creerPuzzle(nbrPuzzle, prochaineSalle));
			IDSalle = prochaineSalle;
			salleAvecPuzzle.push_back(IDSalle);
		}

		for (auto &it : infosSalles) {

			modeleSalle = new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele(it.cheminModele), new gfx::Texture());
			modeleSalle->defEchelle(it.echelle.x, it.echelle.y, it.echelle.z);

			// Boucle sur toutes les portes d'un salle pour les positionner...
			for (unsigned short IDPorte = it.nbrPorte; IDPorte > 0; --IDPorte) {
				objet.ID = IDPorte - 1;
				objet.largeur = 0;
				LecteurFichier::lireObjet("Ressources/Info/portePlate.txt", objet);
				positionnerPorte(*modeleSalle, it, objet);
				it.Objet.push_front(objet);
			}

			// Ajout et réinitialisation de la salle.
			delete modeleSalle;
			chargement += (100.0f / nombreDeSalle);
		}
		finChargement = true;
	}

	Vecteur3d debut(double& hAngle) {

		InfoSalle salleDebut;
		salleDebut.cheminModele = "Ressources/Modele/SalleDebut.obj";
		salleDebut.cheminTexture = "Ressources/Texture/SalleDebut.png";
		salleDebut.echelle = { 1.0, 1.0, 1.0 };
		salleDebut.ID = infosSalles.size();
		salleDebut.nbrPorte = 1;

		// Création des objets de la salle

		// Porte (En premier)

		InfoObjet porte;
		LecteurFichier::lireObjet("Ressources/Info/portePlate.txt", porte);
		porte.direction = { 0, 0, 1 };
		porte.ID = 0;
		porte.largeur = 0;
		porte.position = { 4.1, 0, 2.57 };
		porte.rotation = 90;

		salleDebut.Objet.push_back(porte);

		// Lit

		InfoObjet lit;
		LecteurFichier::lireObjet("Ressources/Info/lit.txt", lit);
		lit.direction = { 0, 0, 0 };
		lit.ID = 1;
		lit.largeur = 0;
		lit.position = { 2.5, 1.0, -10.9 };
		lit.rotation = 0;

		salleDebut.Objet.push_back(lit);

		// Lavabo

		InfoObjet lavabo;
		LecteurFichier::lireObjet("Ressources/Info/lavabo.txt", lavabo);
		lavabo.direction = { 0, 0, 0 };
		lavabo.ID = 2;
		lavabo.largeur = 0;
		lavabo.position = { 5.0, 1.3, -1.5 };
		lavabo.rotation = 0;

		salleDebut.Objet.push_back(lavabo);

		// Bureau

		InfoObjet bureau;
		LecteurFichier::lireObjet("Ressources/Info/bureau.txt", bureau);
		bureau.direction = { 0, 0, 0 };
		bureau.ID = 3;
		bureau.largeur = 0;
		bureau.position = { -4.9, 0.0, -3.0 };
		bureau.rotation = -90;

		salleDebut.Objet.push_back(bureau);

		// Poubelle

		InfoObjet poubelle;
		LecteurFichier::lireObjet("Ressources/Info/poubelle.txt", poubelle);
		poubelle.direction = { 0, 0, 0 };
		poubelle.ID = 4;
		poubelle.largeur = 0;
		poubelle.position = { -4.3, 0.0, -0.75 };
		poubelle.rotation = 0;

		salleDebut.Objet.push_back(poubelle);

		// Etagere

		InfoObjet etagere;
		LecteurFichier::lireObjet("Ressources/Info/etagere.txt", etagere);
		etagere.direction = { 0, 0, 0 };
		etagere.ID = 4;
		etagere.largeur = 0;
		etagere.position = { -1.7, 0.0, 1.55 };
		etagere.rotation = 180;

		salleDebut.Objet.push_back(etagere);

		// Table de chevet

		// Ajout du lien de sortie de la salle de début

		unsigned int IDSalleConnectee = rand() % (nombreDeSalle - 1);

		/*InfoSalle salleConnectee = (*infosSalles.begin()); // Erreur louche
		std::advance(IDSalleConnectee, salleConnectee);

		unsigned int IDPorteSalleConnectee = rand() % salleConnectee.nbrPorte;*/

		unsigned int IDPorteSalleConnectee = 0;

		ajouterLien(Entree(20, 0, false), Sortie(IDSalleConnectee, IDPorteSalleConnectee));

		// Ajout/Création de la salle et autre
		infosSalles.push_back(salleDebut);

		creerSalle(salleDebut);

		modeleMur = new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/murSalle.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/murSalle.png"));
		modelePorte = new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/portePlate.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/portePlate.png"));
		modeleMur->defOrientation(0, 0, 0);
		modelePorte->defOrientation(0, 0, 0);

		hAngle = 270;
		return lit.position + Vecteur3d(-1.3, 0, 0.9);
	}
};
