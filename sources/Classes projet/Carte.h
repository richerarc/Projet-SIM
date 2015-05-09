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

			Vecteur3d vecteurRatio = Maths::vecteurEntreDeuxPoints(point[i], point[j]);
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

		salleActive->remplir();
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

	int destination(Entree entree, Joueur *joueur) {

		joueur->bloquer();
		joueur->defVitesse(Vecteur3d(0, 0, 0));

		salleSuivante = liens[entree];

		auto sallePrecedente = infosSalles.begin();
		std::advance(sallePrecedente, std::get<0>(entree));
		auto portePrecedente = (*sallePrecedente).Objet.begin();
		std::advance(portePrecedente, std::get<1>(entree));

		// Calcul de la rotation de caméra à appliquer:
		// {

		orientationInitialeCamera = vitesseHRotation = portePrecedente->rotation + 270;

		if (vitesseHRotation > 360)
			vitesseHRotation -= 360;

		if (orientationInitialeCamera > 360)
			orientationInitialeCamera -= 360;

		vitesseHRotation -= joueur->obtCamera()->obtHAngle();

		vitesseVRotation = joueur->obtCamera()->obtVAngle() * -1;

		// }

		// Calcul de la translation à appliquer sur le joueur...
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

		// Définition de la position du faux mur, de la fausse porte et du joueur...
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
				// Ajustement de la caméra horizontale...
				if (joueur->obtCamera()->obtHAngle() != orientationInitialeCamera) {
					if (vitesseHRotation < 0) {
						if ((joueur->obtCamera()->obtHAngle() + (vitesseHRotation * frametime)) <= orientationInitialeCamera)
							joueur->obtCamera()->defHAngle(orientationInitialeCamera);
						else
						{
							joueur->obtCamera()->defHAngle(joueur->obtCamera()->obtHAngle() + (vitesseHRotation * frametime));
						}
					}
					else
					{
						if (joueur->obtCamera()->obtHAngle() + (vitesseHRotation * frametime) >= orientationInitialeCamera)
							joueur->obtCamera()->defHAngle(orientationInitialeCamera);
						else
						{
							joueur->obtCamera()->defHAngle(joueur->obtCamera()->obtHAngle() + (vitesseHRotation * frametime));
						}
					}
				}

				// Ajustement de la caméra verticale...
				if (joueur->obtCamera()->obtVAngle() != 0) {
					joueur->obtCamera()->defVAngle(joueur->obtCamera()->obtVAngle() + (vitesseVRotation * frametime));
					if (vitesseVRotation < 0) {
						if (joueur->obtCamera()->obtVAngle() < 0)
							joueur->obtCamera()->defVAngle(0);
					}
					else
					{
						if (joueur->obtCamera()->obtVAngle() > 0)
							joueur->obtCamera()->defVAngle(0);
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
					joueur->obtCamera()->defHAngle(orientationFinaleCamera);
				}
			}
			else
			{
				if (translationVersPositionNSFinaleJoueur.produitScalaire(Maths::vecteurEntreDeuxPoints(joueur->obtPosition(), positionNSFinaleJoueur)) > 0) {
					joueur->defPosition(joueur->obtPosition() + (translationVersPositionNSFinaleJoueur * frametime));
					modelePorte->rotationner(0, 0.4, 0);
				}
				else
				{
					joueur->defPosition(positionNSFinaleJoueur);
					retirerMur();
					joueur->deBloquer();
					enChangementDeSalle = false;
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
			char* curseur1 = new char[255];
			char* curseur2 = new char[255];
			char* curseur3 = new char[255];
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

	Vecteur3d debut(double& hAngle) {
		auto debut = infosSalles.begin();
		std::advance(debut, /*rand() % infosSalles.size()*/1);
		creerSalle(*debut);
		modeleMur = new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("murSalle.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("murSalle.png"));
		modelePorte = new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("portePlate.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("portePlate.png"));
		modeleMur->defOrientation(0, 0, 0);
		modelePorte->defOrientation(0, 0, 0);

		auto porte = debut->Objet.begin();
		hAngle = porte->rotation + 90;
		return porte->position + (porte->direction.produitVectoriel(Vecteur3d(0, 1, 0)) * 0.7352941176) - (porte->direction * 0.18);
	}
};
