 #pragma once
#include <map>
#include <tuple>
#include <list>
#include <vector>
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

typedef std::tuple<unsigned int, unsigned int, bool> Entree;
typedef std::tuple<unsigned int, unsigned int> Sortie;
typedef std::tuple<char*, char*/*, char**/> Modele_Text;

class Carte : public Singleton < Carte > {
private:
	graphe::Graphe carte;
	std::map<Entree, Sortie> liens;
	std::list<InfoSalle> infosSalles;
	gfx::Modele3D *modeleMur;
	gfx::Modele3D *modelePorte;
	Vecteur3d vecteur;
	Vecteur3d vecteurMur;
	Vecteur3d vecteurAide;
	Vecteur3d vecteurDirection;
	Vecteur3d distanceParcourue;
	Vecteur3d distanceAParcourir;
	bool teleporte;

	std::vector<Modele_Text> cheminsModeleText;
	std::vector<char*> cheminsPuzzle;

	void ajouterLien(Entree entree, Sortie sortie){
		liens[entree] = sortie;
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

			Vecteur3d vecteurRatio = Physique::obtInstance().vecteurEntreDeuxPoints(point[i], point[j]);
			vecteurRatio *= ((vecteurRatio.norme() - 1.471) / vecteurRatio.norme());
			vecteurRatio *= ((double)rand() / RAND_MAX);
			vecteurRatio = point[i] + vecteurRatio;
			objet.position.x = vecteurRatio.x;
			objet.position.z = vecteurRatio.z;

			// Boucle qui vérifie si une porte sera en collision avec une autre...
			Vecteur3d pivot = { 0, 1, 0 };
			for (auto it_Porte : salle.Objet) {

				// Si les portes ont la même direction...
				if ((objet.direction == it_Porte.direction) && !(objet.position == it_Porte.position)) {

					if (Physique::obtInstance().distanceEntreDeuxPoints(objet.position, it_Porte.position) <= 1.471) {
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

		Vecteur3d hypothenuse = Physique::obtInstance().vecteurEntreDeuxPoints(pointDeCalcul1, pointDeCalcul2);

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

		for (auto& it : infoSalleActive.Objet) {
			gfx::Modele3D* modeleporte = new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele(it.cheminModele), gfx::GestionnaireRessources::obtInstance().obtTexture(it.cheminTexture));
			modeleporte->defPosition(it.position);
			modeleporte->defOrientation(0, it.rotation, 0);
			switch (it.type) {
				case PORTE:
					salleActive->ajoutObjet(new Porte(modeleporte, it.ID, "metal", it.position, { 0, 0, 0 }, false, true, false, false));
					break;
				case PENDULE:
					salleActive->ajoutObjet(new Pendule(modeleporte, it.ID, "metal", it.position, { 0, 0, 1 }, false, false, false, false));
					break;
				case FIXE:
					salleActive->ajoutObjet(new ObjetFixe(modeleporte, it.ID, "metal", it.position, { 0, 0, 0 }, false, false));
					break;
			}
		}
	}

public:

	Salle *salleActive;
	unsigned int nombreDeSalle;
	double chargement;
	bool finChargement;
	int salle;

	void initialiser() {
		thread_Creation = std::thread(&Carte::creer, this);
	}

	int destination(std::tuple<unsigned int, unsigned int, bool> sortie, Joueur *joueur) {

		delete salleActive;

		Sortie pieceSuivante = liens[sortie];

		auto debut = infosSalles.begin();
		std::advance(debut, std::get<0>(pieceSuivante));

		creerSalle(*debut);

		gfx::Gestionnaire3D::obtInstance().ajouterObjet(modeleMur);
		gfx::Gestionnaire3D::obtInstance().ajouterObjet(modelePorte);

		// Positionnement du joueur...
		auto it = (*debut).Objet.begin();
		std::advance(it, std::get<1>(pieceSuivante));
		vecteurAide = { (*it).direction.x, (*it).direction.y, (*it).direction.z };
		if (vecteurAide.x > 0){
			vecteurDirection.x = 1;
		}
		if (vecteurAide.x < 0){
			vecteurDirection.x = -1;
		}

		if (vecteurAide.z > 0){
			vecteurDirection.z = 1;
		}
		if (vecteurAide.z < 0){
			vecteurDirection.z = -1;
		}
		vecteur = { (*it).position.x + (-1.2 * vecteurDirection.x) + (-0.5 * (*it).direction.z), (*it).position.y, (*it).position.z + (-1.2 * vecteurDirection.z) + (-0.5 * (*it).direction.x) };
		distanceAParcourir = { (-2.5 * vecteurDirection.x) + (-0.5 * (*it).direction.z), 0, (-2.5 * vecteurDirection.z) + (-0.5 * (*it).direction.x) };
		vecteurMur = { (*it).position.x + (-2.5 * vecteurDirection.x), (*it).position.y, (*it).position.z + (-2.5 * vecteurDirection.z) };
		modeleMur->defPosition(vecteurMur);
		modelePorte->defPosition(vecteurMur.x + (-1 * (*it).direction.z), vecteurMur.y, vecteurMur.z + (1 * (*it).direction.x));
		modeleMur->defOrientation(0, (*it).rotation, 0);
		modelePorte->defOrientation(0, (*it).rotation + 180, 0);
		joueur->defPosition(vecteur);
		teleporte = true;

		double anglePorte = Maths::radianADegre((*it).direction.angleEntreVecteurs({ 1, 0, 0 }));

		double angleJoueur = Maths::radianADegre(joueur->obtCamera()->obtDevant().angleEntreVecteurs({ 1, 0, 0 }));

		double angleFinal = angleJoueur + (anglePorte - angleJoueur);

		joueur->obtCamera()->defDevant({ 1, 0, 0 });

		joueur->obtCamera()->defHAngle(angleFinal);

		double angleModif = Maths::radianADegre((*it).direction.angleEntreVecteurs(joueur->obtCamera()->obtDevant()));

		joueur->obtCamera()->defHAngle(joueur->obtCamera()->obtHAngle() - angleModif);

		if ((unsigned)joueur->obtCamera()->obtHAngle() == 89){
			joueur->obtCamera()->defHAngle(joueur->obtCamera()->obtHAngle() + 90);
		}

		return std::get<1>(pieceSuivante);
	}

	void bougerMur(Joueur *joueur, float frameTime){
		if (vecteurAide.x > 0){
			vecteurDirection.x = vecteurAide.x;
		}
		if (vecteurAide.x < 0){
			vecteurDirection.x = -vecteurAide.x;
		}
		if (vecteurAide.z > 0){
			vecteurDirection.z = vecteurAide.z;
		}
		if (vecteurAide.z < 0){
			vecteurDirection.z = -vecteurAide.z;
		}

		if (teleporte){
			ajouterMur();
			joueur->bloquer();
		}
		else if ((distanceParcourue.x >= distanceAParcourir.x) && ((unsigned)distanceParcourue.x != 0)){
			retirerMur();
			joueur->deBloquer();
		}
		else if ((distanceParcourue.z >= distanceAParcourir.z) && ((unsigned)distanceParcourue.z != 0)){
			retirerMur();
			joueur->deBloquer();
		}
		else if ((distanceParcourue.x >= distanceAParcourir.x) && (distanceParcourue.z >= distanceAParcourir.z) && ((unsigned)distanceParcourue.x != 0) && ((unsigned)distanceParcourue.z != 0)){
			retirerMur();
			joueur->deBloquer();
		}
		modeleMur->defPosition(modeleMur->obtPosition() + (vecteurAide)* frameTime);
		modelePorte->defPosition(modelePorte->obtPosition() + (vecteurAide)* frameTime);
		modelePorte->rotationner(0, 0.5, 0);
		distanceParcourue = distanceParcourue + ((vecteurDirection)* frameTime);
	}

	void ajouterMur(){
		gfx::Gestionnaire3D::obtInstance().ajouterObjet(modeleMur);
		gfx::Gestionnaire3D::obtInstance().ajouterObjet(modelePorte);
		teleporte = false;
		distanceParcourue = 0;
	}

	void retirerMur(){
		gfx::Gestionnaire3D::obtInstance().retObjet(modeleMur);
		gfx::Gestionnaire3D::obtInstance().retObjet(modelePorte);
		teleporte = false;
	}

	// Procédure qui permet de créer le graphe et la première salle dans laquelle le joueur commence...
	void creer() {
		srand(time(NULL));
		SDL_GLContext c = fenetre->obtNouveauContext();

		// Création du graphe
		carte.creer(nombreDeSalle);
		int itterateurPorte(0);

		chargement = 0;
		finChargement = false;

		int* porte = new int[nombreDeSalle];
		Entree entree;
		Sortie sortie;
		for (unsigned int i = 0; i < nombreDeSalle; ++i)
			porte[i] = 0;

		for (unsigned int i = 0; i < nombreDeSalle; ++i){
			if (i == 10)
				int hue = 0;
			itterateurPorte = 0;
			for (unsigned int j = 0; j < nombreDeSalle; ++j){
				if (carte.matrice[i * nombreDeSalle + j]){
					entree = std::make_tuple(i, itterateurPorte++, false);
					sortie = std::make_tuple(j, porte[j]);
					++porte[j];
					ajouterLien(entree, sortie);
					Sortie pieceSuivante = liens[entree];
				}
			}
		}

		// Load des salles possibles
		std::ifstream fichierSalle("salle_text.txt");
		std::ifstream fichierObjet("objet_text.txt");
		std::ifstream fichierPuzzle("puzzle_text.txt");

		int itterateur(0);
		while (!fichierSalle.eof()) {
			char* curseur1 = new char[20];
			char* curseur2 = new char[20];
			char* curseur3 = new char[20];
			fichierSalle >> curseur1; fichierSalle >> curseur2; /*fichierSalle >> curseur3;*/
			cheminsModeleText.push_back(Modele_Text(curseur1, curseur2/*, curseur3*/));
			++itterateur;
		}
		fichierSalle.close();
		int nbrPuzzle(0);
		while (!fichierPuzzle.eof()) {
			char* curseur1 = new char[20];
			fichierPuzzle >> curseur1;
			cheminsPuzzle.push_back(curseur1);
			++nbrPuzzle;
		}
		fichierPuzzle.close();
		unsigned int aleatoire;
		InfoObjet objet;
		InfoSalle salle;
		InfoPuzzle puzzle;
		gfx::Modele3D* modeleSalle;

		// Boucle sur toutes les salles...
		for (unsigned int i = 0; i < nombreDeSalle; ++i) {

			salle.ID = i;
			salle.nbrPorte = carte.degreSortant(i);
			salle.echelle = { rand() % 3 + 2.0, 2.0, rand() % 3 + 2.0 };
			aleatoire =  rand() % itterateur;
			salle.cheminModele = (char*)(std::get<0>(cheminsModeleText[aleatoire]));
			salle.cheminTexture = (char*)(std::get<1>(cheminsModeleText[aleatoire]));
			//LecteurFichier::lireBoite(std::get<2>(cheminsModeleText[aleatoire]), salle);
			infosSalles.push_back(salle);
			salle.boitesCollision.clear();
			salle.Objet.clear();
		}

		/*int premiereSalle = 1;//rand() % nombreDeSalle;
		InfoSalle &salle2 = *std::find_if(std::begin(infosSalles), std::end(infosSalles), [&](InfoSalle info){ return info.ID == premiereSalle; });
		
		for (int i = 0; i < nombreDeSalle / 3 && nbrPuzzle > 0; ++i) {
			int aleatoire = rand() % nbrPuzzle;
			--nbrPuzzle;
			LecteurFichier::lirePuzzle(cheminsPuzzle[aleatoire], puzzle);
			cheminsPuzzle.erase(std::find_if(cheminsPuzzle.begin(), cheminsPuzzle.end(), [&](char* chemin){return chemin == cheminsPuzzle[aleatoire];}));
			int lol = salle2.boitesCollision.size();
			BoiteCollision<double> boiteTemp = salle2.obtBoiteCollisionModifie((1/*rand() % salle.boitesCollision.size()));
			if (boiteTemp.obtGrandeurZ() - boiteTemp.obtGrandeurX() < 0){
				//
			}
			puzzle.position = boiteTemp.distanceEntreDeuxCentre(puzzle.boiteCollision);
			/*for (auto &it : puzzle.objet)
				it.position += puzzle.position;

			if (boiteTemp.boiteDansBoite(puzzle.obtBoiteCollisionModifie())){
				for (auto &it : puzzle.objet){
					salle2.Objet.push_back(it);
				}
				
			}
		}*/

		for (auto &it : infosSalles) {

			modeleSalle = new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele(it.cheminModele), new gfx::Texture());
			modeleSalle->defEchelle(it.echelle.x, it.echelle.y, it.echelle.z);

			// Boucle sur toutes les portes d'un salle pour les positionner...
			for (unsigned short IDPorte = 0; IDPorte < it.nbrPorte; ++IDPorte) {
				objet.ID = IDPorte;
				LecteurFichier::lireObjet("portePlate.txt", objet);
				positionnerPorte(*modeleSalle, it, objet);
				it.Objet.push_back(objet);
			}

			// Ajout et réinitialisation de la salle.
			delete modeleSalle;
			chargement += (100.0f / nombreDeSalle);
		}

		finChargement = true;
		//SDL_GL_DeleteContext(c);
	}

	void debut() {
		auto debut = infosSalles.begin();
		std::advance(debut, /*rand() % infosSalles.size()*/1);
		creerSalle(*debut);
		modeleMur = new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("murSalle.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("murSalle.png"));
		modelePorte = new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("portePlate.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("portePlate.png"));
		modeleMur->defOrientation(0, 0, 0);
		modelePorte->defOrientation(0, 0, 0);
	}
};
