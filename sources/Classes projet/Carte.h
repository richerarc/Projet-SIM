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
#include "Personnage.h"
#include "ControlleurAudio.h"
#include "Vent.h"
#include "Commutateur.h"
#include "UsineItem.h"
#include "PlafondTueur.h"

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
	Objet* avion;
	std::stack<InfoObjet> ItemsUniques;
	std::vector<InfoObjet> Fixes;
	std::vector<InfoObjet> Items;

	// Variables d'animation...
	Vecteur3d translations[2],
		positions[3];

	double orientationCamera[3],
		vitesseRotationHV[2];

	float temps;

	bool premiereFois,
		enChangementDeSalle,
		enLeverLit,
		ouvrirYeux,
		teleporte,
		enFinPartie,
		dejaCalculee,
		alavion;

	Sortie salleSuivante;

	gfx::Sprite2D* noirHautBas[2];

	std::vector<Modele_Text> cheminsModeleText;
	std::vector<char*> cheminsPuzzle;
	std::vector<char*> cheminsObjet;

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
			objet.rotation.y = (Vecteur3d({ -1, 0, 0 }).produitScalaire(normale) < 0) ? (90 - Maths::radianADegre(Vecteur3d({ -1, 0, 0 }).produitVectoriel(Vecteur3d({ 0, 1, 0 })).angleEntreVecteurs(normale)))
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

				if ((*it_Porte).largeur != 0) {

					if ((*it_Porte).rotation.y == 0) {
						if (objet.position.z >= (*it_Porte).position.z && (objet.position.x <= (*it_Porte).position.x && objet.position.x >= (*it_Porte).position.x + (*it_Porte).largeur))
							PorteAuMur = false;
					}
					else if ((*it_Porte).rotation.y == 180) {
						if (objet.position.z <= (*it_Porte).position.z && (objet.position.x >= (*it_Porte).position.x && objet.position.x <= (*it_Porte).position.x + (*it_Porte).largeur))
							PorteAuMur = false;
					}
					else if ((*it_Porte).rotation.y == 270) {
						if (objet.position.x <= (*it_Porte).position.x && (objet.position.z >= (*it_Porte).position.z + (*it_Porte).largeur && objet.position.z <= (*it_Porte).position.z))
							PorteAuMur = false;
					}
					else if ((*it_Porte).rotation.y == 90) {
						if (objet.position.x >= (*it_Porte).position.x && (objet.position.z <= (*it_Porte).position.z + (*it_Porte).largeur && objet.position.z >= (*it_Porte).position.z))
							PorteAuMur = false;
					}
					Remplisseur* remp;
					for (auto it_boite : salle.Objet){
						if ((*it_boite).type == REMPLISSEUR){
							remp = new Remplisseur(new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele((*it_boite).cheminModele), gfx::GestionnaireRessources::obtInstance().obtTexture((*it_boite).cheminTexture)), (*it_boite).largeur, (*it_boite).position, (*it_boite).ID);
							if (remp->obtModele3D()->obtBoiteCollision().pointDansBoite(objet.position)){
								PorteAuMur = false;
								break;
							}
							delete remp;
						}
					}
				}

				// Si les portes ont la même direction...
				else if ((objet.direction == (*it_Porte).direction) && !(objet.position == (*it_Porte).position)) {

					if (Maths::distanceEntreDeuxPoints(objet.position, (*it_Porte).position) <= 1.471) {
						PorteAuMur = false;
					}
					Remplisseur* remp;
					for (auto it_boite : salle.Objet){
						if ((*it_boite).type == REMPLISSEUR){
							remp = new Remplisseur(new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele((*it_boite).cheminModele), gfx::GestionnaireRessources::obtInstance().obtTexture((*it_boite).cheminTexture)), (*it_boite).largeur, (*it_boite).position, (*it_boite).ID);
							if (remp->obtModele3D()->obtBoiteCollision().pointDansBoite(objet.position)){
								PorteAuMur = false;
								break;
							}
							delete remp;
						}
					}
				}
			}
		}
	}

	bool positionnerObjet(gfx::Modele3D& modeleSalle, InfoSalle& salle, InfoObjet& objet) {
		bool positionne = false;
		int nbrIt(0);
		while (!positionne){
			
			unsigned int depart = 0;
			Vecteur3d normale;
			Vecteur3d point[3];
			Vecteur3d swap;
			
			double* vertices = modeleSalle.obtSommetsModifies();
			double* normales = modeleSalle.obtNormalesModifies();
			
			if (objet.positionement == SOLS){
				do{
					depart = (rand() % modeleSalle.obtModele()->obtNbrFaces()) * 9;
					normale = { normales[depart] + normales[depart + 3] + normales[depart + 6], normales[depart + 1] + normales[depart + 4] + normales[depart + 7], normales[depart + 2] + normales[depart + 5] + normales[depart + 8]};
				}while(normale.y <= 0.5);
				
				for (int i = 0; i < 3; ++i) {
					point[i] = { vertices[depart + i * 3], vertices[depart + i * 3 + 1], vertices[depart + i * 3 + 2] };
				}
				
				double largeurX = 0.0f, largeurZ = 0.0f, temp = 0.0f;
				for (int i = 0; i<3; ++i){
					temp = fabs(fabs(point[i].x) - fabs(point[i+ 1 % 3].x));
					if (temp > largeurX)
						largeurX = temp;
					temp = fabs(fabs(point[i].z) - fabs(point[i+ 1 % 3].z));
					if (temp > largeurZ)
						largeurZ = temp;
				}
				
				gfx::Modele3D modele(gfx::GestionnaireRessources::obtInstance().obtModele(objet.cheminModele), gfx::GestionnaireRessources::obtInstance().obtTexture(objet.cheminTexture));
				modele.defOrientation(0, objet.rotation.y, 0);
				BoiteCollision<double> boite(modele.obtBoiteDeCollisionModifiee());
				double x(0.0f),y(0.0f),z(0.0f);
				
				unsigned int i;
				unsigned int j;
				do {
					do{
						i = rand() % 3;
						j = rand() % 3;
					} while (i == j);
				} while (point[i].z == point[j].z);
				
				unsigned int k;
				unsigned int l;
				do {
					do{
						k = rand() % 3;
						l = rand() % 3;
					} while (k == l);
				} while (point[k].x == point[l].x);
				
				if ((point[l].x == point[i].x) && (point[l].x == point[j].x)){
					x = point[l].x; y = point[l].y; z = point[l].z;
				}
				else{
					x = point[k].x; y = point[k].y; z = point[k].z;
				}
				
				Vecteur3d p,d;
				if (largeurX > 4 && largeurZ > 4){
					p = {((x / 3) + (rand()%2 * -1)*(rand() % (int)largeurX/4)), (y / 3), ((z / 3) + (rand()%2 * -1)*(rand() % (int)largeurZ/4))};
					while([&]() -> bool
						  {
							  Plan plan(point[0],point[1],point[2], normale);
							  Droite dr(p, normale * -1);
							  
							  return !plan.insertionDroitePlan(dr, d);
							  
						  }()){
							  p = {((x / 3) + (rand()%2 * -1)*(rand() % (int)largeurX/4)), (y / 3), ((z / 3) + (rand()%2 * -1)*(rand() % (int)largeurZ/4))};
						  }
					if (objet.type == ITEM){
						if (p.y < 0)
							p.y = 0;
						if (d.y > p.y)
							p.y = d.y;
					}
					else{
						p.y = 0;
					}
				}
				else
					p = {(x / 3), (y / 3), (z / 3)};
				
				if (boite.obtGrandeurX() <= largeurX && boite.obtGrandeurZ() <= largeurZ){
					bool memePosition = false;
					for (auto it : salle.Objet){
						if (it->position.x == p.x && it->position.y == p.y && it->position.z == p.z){
							memePosition = true;
							break;
						}
					}
					Remplisseur* remp;
					for (auto it_boite : salle.Objet){
						if ((*it_boite).type == REMPLISSEUR){
							remp = new Remplisseur(new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele((*it_boite).cheminModele), gfx::GestionnaireRessources::obtInstance().obtTexture((*it_boite).cheminTexture)), (*it_boite).largeur, (*it_boite).position, (*it_boite).ID);
							if (remp->obtModele3D()->obtBoiteCollision().pointDansBoite(objet.position)){
								memePosition = true;
								break;
							}
							delete remp;
						}
					}
					
					if (!memePosition){
						objet.position = p;
						return true;
					}
				}
			}
//			else if(objet.positionement == MURS){
//				unsigned int depart;
//				Vecteur3d normale;
//				Vecteur3d point[3];
//				Vecteur3d swap;
//				
//				bool PorteAuMur = false;
//				double* vertices = modeleSalle.obtSommetsModifies();
//				double* normales = modeleSalle.obtNormalesModifies();
//				while (!PorteAuMur)
//				{
//					PorteAuMur = true;
//					do{
//						double y;
//						do{
//							depart = (rand() % modeleSalle.obtModele()->obtNbrFaces()) * 9;
//							normale = { normales[depart], normales[depart + 1], normales[depart + 2] };
//						} while (normale.y != 0);
//						for (int i = 0; i < 3; ++i) {
//							
//							point[i] = { vertices[depart + i * 3], vertices[depart + i * 3 + 1], vertices[depart + i * 3 + 2] };
//							
//						}
//					} while (!espacePorte(point[0], point[1], point[2]));
//					normale.normaliser();
//						// Angle de la porte...
//					objet.rotation.y = (Vecteur3d({ -1, 0, 0 }).produitScalaire(normale) < 0) ? (90 - Maths::radianADegre(Vecteur3d({ -1, 0, 0 }).produitVectoriel(Vecteur3d({ 0, 1, 0 })).angleEntreVecteurs(normale)))
//					: (270 - Maths::radianADegre(Vecteur3d({ -1, 0, 0 }).produitVectoriel(Vecteur3d({ 0, -1, 0 })).angleEntreVecteurs(normale)));
//					
//					objet.direction = normale * -1;
//					
//					double y1 = point[0].y;
//					double y2;
//					do {
//						y2 = point[rand() % 2 + 1].y;
//					} while (y1 == y2);
//					
//					objet.position.y = (y1 < y2) ? y1 : y2;
//					
//					unsigned int i;
//					unsigned int j;
//					do {
//						do{
//							i = rand() % 3;
//							j = rand() % 3;
//						} while (i == j);
//					} while (point[i].y != point[j].y);
//					
//						// Positionnement des points de blender dans le même sens...
//					if (abs(normale.x) != 1 && abs(normale.z) != 1) {
//						if ((normale.x >= 0 && normale.z >= 0) || (normale.x < 0 && normale.z >= 0)) {
//							if (point[i].x > point[j].x) {
//								swap = point[i];
//								point[i] = point[j];
//								point[j] = swap;
//							}
//						}
//						else if ((normale.x < 0 && normale.z < 0) || (normale.x >= 0 && normale.z < 0)) {
//							if (point[i].x < point[j].x) {
//								swap = point[i];
//								point[i] = point[j];
//								point[j] = swap;
//							}
//						}
//					}
//					else
//					{
//						switch ((int)normale.x) {
//							case 1:
//								if (point[i].z < point[j].z) {
//									swap = point[i];
//									point[i] = point[j];
//									point[j] = swap;
//								}
//								break;
//							case -1:
//								if (point[i].z > point[j].z) {
//									swap = point[i];
//									point[i] = point[j];
//									point[j] = swap;
//								}
//								break;
//						}
//						switch ((int)normale.z) {
//							case 1:
//								if (point[i].x > point[j].x) {
//									swap = point[i];
//									point[i] = point[j];
//									point[j] = swap;
//								}
//								break;
//							case -1:
//								if (point[i].x < point[j].x) {
//									swap = point[i];
//									point[i] = point[j];
//									point[j] = swap;
//								}
//								break;
//						}
//					}
//					
//					gfx::Modele3D modele(gfx::GestionnaireRessources::obtInstance().obtModele(objet.cheminModele), gfx::GestionnaireRessources::obtInstance().obtTexture(objet.cheminTexture));
//					modele.defOrientation(0, objet.rotation.y, 0);
//					BoiteCollision<double> boite(modele.obtBoiteDeCollisionModifiee());
//					
//					Vecteur3d vecteurRatio = Maths::vecteurEntreDeuxPoints(point[i], point[j]);
//					vecteurRatio *= ((vecteurRatio.norme() - boite.obtGrandeurX()) / vecteurRatio.norme());
//					vecteurRatio *= ((double)rand() / RAND_MAX);
//					vecteurRatio = point[i] + vecteurRatio;
//					objet.position.x = vecteurRatio.x;
//					objet.position.z = vecteurRatio.z;
//					
//						// Boucle qui vérifie si une porte sera en collision avec une autre...
//					Vecteur3d pivot = { 0, 1, 0 };
//					for (auto it : salle.Objet) {
//						
//						if ((*it).largeur != 0) {
//							
//							if ((*it).rotation.y == 0) {
//								if (objet.position.z >= (*it).position.z && (objet.position.x <= (*it).position.x && objet.position.x >= (*it).position.x + (*it).largeur))
//									PorteAuMur = false;
//							}
//							else if ((*it).rotation.y == 180) {
//								if (objet.position.z <= (*it).position.z && (objet.position.x >= (*it).position.x && objet.position.x <= (*it).position.x + (*it).largeur))
//									PorteAuMur = false;
//							}
//							else if ((*it).rotation.y == 270) {
//								if (objet.position.x <= (*it).position.x && (objet.position.z >= (*it).position.z + (*it).largeur && objet.position.z <= (*it).position.z))
//									PorteAuMur = false;
//							}
//							else if ((*it).rotation.y == 90) {
//								if (objet.position.x >= (*it).position.x && (objet.position.z <= (*it).position.z + (*it).largeur && objet.position.z >= (*it).position.z))
//									PorteAuMur = false;
//							}
//							Remplisseur* remp;
//							for (auto it_boite : salle.Objet){
//								if ((*it_boite).type == REMPLISSEUR){
//									remp = new Remplisseur(new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele((*it_boite).cheminModele), gfx::GestionnaireRessources::obtInstance().obtTexture((*it_boite).cheminTexture)), (*it_boite).largeur, (*it_boite).position, (*it_boite).ID);
//									if (remp->obtModele3D()->obtBoiteCollision().pointDansBoite(objet.position)){
//										PorteAuMur = false;
//										break;
//									}
//									delete remp;
//								}
//							}
//						}
//						
//							// Si les portes ont la même direction...
//						else if ((objet.direction == (*it).direction) && !(objet.position == (*it).position)) {
//							
//							if (Maths::distanceEntreDeuxPoints(objet.position, (*it).position) <= boite.obtGrandeurX()) {
//								PorteAuMur = false;
//							}
//							Remplisseur* remp;
//							for (auto it_boite : salle.Objet){
//								if ((*it_boite).type == REMPLISSEUR){
//									remp = new Remplisseur(new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele((*it_boite).cheminModele), gfx::GestionnaireRessources::obtInstance().obtTexture((*it_boite).cheminTexture)), (*it_boite).largeur, (*it_boite).position, (*it_boite).ID);
//									if (remp->obtModele3D()->obtBoiteCollision().pointDansBoite(objet.position)){
//										PorteAuMur = false;
//										break;
//									}
//									delete remp;
//								}
//							}
//						}
//					}
//				}
//			}
			
			if (nbrIt > 20)
				return false;
			++nbrIt;
		}
		return false;
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
			gfx::Modele3D* modeleObjet = nullptr;
			if ((*it).type != ITEM){
				modeleObjet = new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele((*it).cheminModele), gfx::GestionnaireRessources::obtInstance().obtTexture((*it).cheminTexture));
				modeleObjet->defPosition((*it).position);
				modeleObjet->defOrientation((*it).rotation);
			}
			switch ((*it).type) {
			case PORTE:
				salleActive->ajoutObjet(new Porte(modeleObjet, (*it).ID, "metal", (*it).position, { 0, 0, 0 }, false, true, (*it).estVerrouille, false, new Cible(10, *it)));
				break;
			case PENDULE:
				if (!(*it).rotation.y)
					salleActive->ajoutObjet(new Pendule(modeleObjet, (*it).ID, "metal", (*it).position, { 2, 0, 0 }, false, false, phasePendule += (rand() % 4 + 1) / MATHS_PI, 30));
				else
					salleActive->ajoutObjet(new Pendule(modeleObjet, (*it).ID, "metal", (*it).position, { 0, 0, 2 }, false, false, phasePendule += (rand() % 4 + 1) / MATHS_PI, 30));
				break;
			case FIXE:
				salleActive->ajoutObjet(new ObjetFixe(modeleObjet, (*it).ID, "metal", (*it).position, { 0, 0, 0 }, false, false));
				break;
			case PEINTURE:
				salleActive->ajoutObjet(new Peinture((*it).ID, modeleObjet, (*it).position, true));
				break;
			case PERSONNAGE:
				salleActive->ajoutObjet(new Personnage((*it).ID, modeleObjet, (*it).position));
				break;
			case REMPLISSEUR:
				salleActive->ajoutObjet(new Remplisseur(modeleObjet, (*it).largeur, (*it).position, (*it).ID));
				break;
			case VENTILATEUR:
				salleActive->ajoutObjet(new Vent(modeleObjet, (*it).ID, Vecteur3d(0, 5, 0), (*it).position, Vecteur3d((*it).largeur, 20, (*it).largeur)));
				break;
			case COMMUTATEUR:
				salleActive->ajoutObjet(new Commutateur(modeleObjet, (*it).ID, "metal", (*it).position, { 0, 0, 0 }, false));
				break;
			case PLAFONDTUEUR:
				salleActive->ajoutObjet(new PlafondTueur(modeleObjet, (*it).ID, "metal", (*it).position, { 0, 0, 0 }, true, false));
				break;
			case ITEM:
				Item *itm = UsineItem::obtInstance().obtItemParType((*it).IDitem, (*it).ID);
				itm->defPosition((*it).position);
				itm->defVitesse({ 0, -0.1, 0 });
				itm->defStable(false);
				salleActive->ajoutObjet(itm);
				break;
			}
		}

		salleActive->remplir();
	}

	bool creerPuzzle(InfoSalle& salle, int &nbrPuzzle) {

		int IDPuzzle = rand() % nbrPuzzle;
		char* nomPuzzle = cheminsPuzzle[IDPuzzle];

		if (!strcmp(nomPuzzle, "Ressources/Info/Pendules.pzl")) {
			if (pendules(salle)) {
				cheminsPuzzle.erase(std::find(cheminsPuzzle.begin(), cheminsPuzzle.end(), nomPuzzle));
				--nbrPuzzle;
				return true;
			}
		}
		if (!strcmp(nomPuzzle, "Ressources/Info/Plafond.pzl")) {
			if (plafond(salle)) {
				cheminsPuzzle.erase(std::find(cheminsPuzzle.begin(), cheminsPuzzle.end(), nomPuzzle));
				--nbrPuzzle;
				return true;
			}
		}
		return false;
	}

	void etablirPorteVerrouille(unsigned int IDPiece, unsigned int IDPiecePrecedente, unsigned int itteration, std::map<unsigned int, unsigned int>& itterateurs) {


		std::vector<Entree> entrees;
		bool porteDejaVerrouille = false;
		unsigned int nbrPorte = 0;
		auto it_Salle = infosSalles.begin();
		std::advance(it_Salle, IDPiece);
		for (auto it_Porte : it_Salle->Objet) {
			if (it_Porte->type == PORTE) {
				Entree entree(IDPiece, it_Porte->ID, false);
				if (std::get<0>(liens[entree]) != IDPiecePrecedente)
					entrees.push_back(entree);
				if (it_Porte->estVerrouille)
					porteDejaVerrouille = true;
				++nbrPorte;
			}
		}

		if (itterateurs[IDPiece] != 1) {
			if (itteration > 2) {
				if (!porteDejaVerrouille) {
					for (auto it_Porte : it_Salle->Objet) {
						if (it_Porte->type == PORTE) {
							unsigned int pos = (rand() % (nbrPorte * itteration)) + 1;
							it_Porte->estVerrouille = (pos >= (/*nbrPorte + */itteration)) ? true : false;
						}
					}
					itterateurs[IDPiece] = itteration;
				}
				else {
					if (itterateurs[IDPiece] > itteration) {
						for (auto it_Porte : it_Salle->Objet) {
							if (it_Porte->type == PORTE) {
								unsigned int pos = (rand() % (nbrPorte * itteration)) + 1;
								it_Porte->estVerrouille = (pos >= (/*nbrPorte + */itteration)) ? true : false;
							}
						}
						itterateurs[IDPiece] = itteration;
					}
				}
			}
			else
			{
				itterateurs[IDPiece] = 1;
			}
		}

		if (!porteDejaVerrouille) {
			for (unsigned int ui = 0; ui < entrees.size(); ++ui) {
				etablirPorteVerrouille(std::get<0>(liens[entrees[ui]]), IDPiece, itteration + 1, itterateurs);
			}
		}
	}

public:

	Salle *salleActive;
	unsigned int nombreDeSalle;
	double chargement;
	bool finChargement;
	int salle;

	void ajouterLien(Entree entree, Sortie sortie){
		liens[entree] = sortie;
	}

	void mettreAJourInfoSalle(InfoSalle& sallePrecedente, Entree entree) {
		bool estDansListe = false;

		std::vector<InfoObjet*> infosObjetARetirer;
		unsigned int nbrinfosObjARet = 0;

		for (auto it : sallePrecedente.Objet) {
			if (it->type == ITEM) {
				for (auto it_SalleActive : salleActive->obtListeObjet()) {
					Item* item = dynamic_cast<Item*>(it_SalleActive);
					if (item) {
						if (it->position == item->obtPosition()) {
							salleActive->retirerObjet(it_SalleActive);
							delete it_SalleActive;
							it_SalleActive = nullptr;
							estDansListe = true;
							break;
						}
					}
				}
				if (!estDansListe) {
					infosObjetARetirer.push_back(it);
					++nbrinfosObjARet;
				}
				else
					estDansListe = false;
			}
		}

		for (; nbrinfosObjARet > 0; --nbrinfosObjARet) {
			sallePrecedente.Objet.remove(infosObjetARetirer[nbrinfosObjARet - 1]);
			delete infosObjetARetirer[nbrinfosObjARet - 1];
		}

		for (auto it : salleActive->obtListeObjet()) {
			Item* item = dynamic_cast<Item*>(it);
			if (item) {

				InfoObjet leitem;
				leitem.ID = sallePrecedente.Objet.size();
				leitem.position = item->obtPosition();
				leitem.rotation = item->obtModele3D()->obtOrientation();
				leitem.type = ITEM;
				leitem.IDitem = item->obtType();
				sallePrecedente.Objet.push_back(new InfoObjet(leitem));
			}
			else
			{
				Porte* porte = dynamic_cast<Porte*>(it);
				if (porte) {
					if (!porte->obtVerrouillee()) {
						for (auto it : sallePrecedente.Objet) {
							if (it->ID == porte->obtID()) {
								it->estVerrouille = false;
							}
						}
					}
				}
				else
				{
					Peinture* peinture = dynamic_cast<Peinture*>(it);
					if (peinture) {

						if (peinture->estPermanente()) {

							InfoObjet lapeinture;
							lapeinture.ID = sallePrecedente.Objet.size();
							lapeinture.cheminModele = "Ressources/Modele/Peinture.obj";
							lapeinture.cheminTexture = "Ressources/Texture/Peinture.png";
							lapeinture.position = peinture->obtPosition();
							lapeinture.rotation = peinture->obtModele3D()->obtOrientation();
							lapeinture.type = PEINTURE;
							sallePrecedente.Objet.push_back(new InfoObjet(lapeinture));
						}
					}
				}
			}
		}

		unsigned int ID = 0;

		for (auto it : sallePrecedente.Objet) {
			if (it->ID != ID) {
				if (it->type == PORTE) {
					Sortie sortie(sallePrecedente.ID, ID);
					Entree entreetmp(sallePrecedente.ID, ID, false);
					Sortie sortietmp = liens[entree];
					liens[Entree(std::get<0>(sortietmp), std::get<1>(sortietmp), false)] = sortie;
					liens.erase(entree);
					ajouterLien(entreetmp, sortietmp);
				}
				it->ID = ID;
			}
			++ID;
		}
	}

	int destination(Entree entree, Joueur *joueur) {

		joueur->bloquer();
		joueur->defVitesse(Vecteur3d(0, 0, 0));

		salleSuivante = liens[entree];

		auto sallePrecedente = infosSalles.begin();
		std::advance(sallePrecedente, std::get<0>(entree));

		auto portePrecedente = (*sallePrecedente).Objet.begin();
		std::advance(portePrecedente, std::get<1>(entree));

		mettreAJourInfoSalle((*sallePrecedente), entree);

		// Calcul de la rotation de camÃ©ra Ã  appliquer:
		// {

		orientationCamera[0] = vitesseRotationHV[0] = (*portePrecedente)->rotation.y + 270;

		if (vitesseRotationHV[0] > 360)
			vitesseRotationHV[0] -= 360;

		if (orientationCamera[0] > 360)
			orientationCamera[0] -= 360;

		vitesseRotationHV[0] -= joueur->obtHAngle();

		if (vitesseRotationHV[0] < -180) {
			vitesseRotationHV[0] += 360;
		}

		vitesseRotationHV[1] = joueur->obtVAngle() * -1;

		// }

		// Calcul de la translation Ã  appliquer sur le joueur...
		// {

		positions[0] = (*portePrecedente)->position + ((*portePrecedente)->direction.produitVectoriel(Vecteur3d(0, 1, 0)) * 0.7352941176) - ((*portePrecedente)->direction * 1.5);

		translations[0] = Maths::vecteurEntreDeuxPoints(joueur->obtPosition(), positions[0]);
		translations[0].normaliser();

		// }

		// Calcul de la nouvelle position du joueur et mur/porte
		// {

		auto debut = infosSalles.begin();
		std::advance(debut, std::get<0>(salleSuivante));

		auto it = (*debut).Objet.begin();
		std::advance(it, std::get<1>(salleSuivante));

		// DÃ©finition de la position du faux mur, de la fausse porte et du joueur...
		Vecteur3d positionMur = (*it)->position - ((*it)->direction * 1.68);

		modeleMur->defPosition(positionMur);
		modelePorte->defPosition(positionMur.x - (1.470588235 * (*it)->direction.z), positionMur.y, positionMur.z + (1.470588235 * (*it)->direction.x));
		modeleMur->defOrientation((*it)->rotation);
		modelePorte->defOrientation((*it)->rotation.x, (*it)->rotation.y + 180, (*it)->rotation.z);

		positions[1] = (*it)->position + ((*it)->direction.produitVectoriel(Vecteur3d(0, 1, 0)) * 0.7352941176) - ((*it)->direction * 0.18);
		positions[2] = positions[1] - ((*it)->direction * 1.5);

		translations[1] = Maths::vecteurEntreDeuxPoints(positions[1], positions[2]);
		translations[1].normaliser();

		orientationCamera[1] = (*it)->rotation.y + 90;

		if (orientationCamera[1] > 360)
			orientationCamera[1] -= 360;

		// }

		teleporte = false;
		enChangementDeSalle = true;
		premiereFois = true;
		return std::get<1>(salleSuivante);
	}

	bool animationTransitionSalle(Joueur* joueur, float frametime) {

		if (enChangementDeSalle) {

			if (!premiereFois) {
				if (!teleporte) {
					// Ajustement de la camera horizontale...
					if (joueur->obtHAngle() != orientationCamera[0]) {
						if (vitesseRotationHV[0] < 0) {
							if ((joueur->obtHAngle() + (vitesseRotationHV[0] * frametime)) <= orientationCamera[0])
								joueur->defHAngle(orientationCamera[0]);
							else
							{
								joueur->defHAngle(joueur->obtHAngle() + (vitesseRotationHV[0] * frametime));
							}
						}
						else
						{
							if (joueur->obtHAngle() + (vitesseRotationHV[0] * frametime) >= orientationCamera[0])
								joueur->defHAngle(orientationCamera[0]);
							else
							{
								joueur->defHAngle(joueur->obtHAngle() + (vitesseRotationHV[0] * frametime));
							}
						}
					}

					// Ajustement de la camera verticale...
					if (joueur->obtVAngle() != 0) {
						joueur->defVAngle(joueur->obtVAngle() + (vitesseRotationHV[1] * frametime));
						if (vitesseRotationHV[1] < 0) {
							if (joueur->obtVAngle() < 0)
								joueur->defVAngle(0);
						}
						else
						{
							if (joueur->obtVAngle() > 0)
								joueur->defVAngle(0);
						}
					}

					if (translations[0].produitScalaire(Maths::vecteurEntreDeuxPoints(joueur->obtPosition(), positions[0])) > 0) {
						joueur->defPosition(joueur->obtPosition() + (translations[0] * frametime * 1.5));
					}
					else
					{
						joueur->defPosition(positions[0]);
					}

					if (joueur->obtHAngle() == orientationCamera[0] && joueur->obtVAngle() == 0 && joueur->obtPosition() == positions[0]) {
						teleporte = true;
						delete salleActive;
						auto debut = infosSalles.begin();
						std::advance(debut, std::get<0>(salleSuivante));

						creerSalle(*debut);

						Item* canon = joueur->obtInventaire()->obtItemParType(12);
						CanonAPeinture* it_Canon = dynamic_cast<CanonAPeinture*>(canon);
						if (it_Canon != nullptr)
							it_Canon->reinitialiserListePeinture();

						ajouterMur();
						joueur->defPosition(positions[1]);
						joueur->defHAngle(orientationCamera[1]);
						ControlleurAudio::obtInstance().jouer(OUVERTURE_PORTE_1, joueur);

					}
				}
				else
				{
					if (translations[1].produitScalaire(Maths::vecteurEntreDeuxPoints(joueur->obtPosition(), positions[2])) > 0) {
						joueur->defPosition(joueur->obtPosition() + (translations[1] * frametime));
						modelePorte->rotationner(0, 1.6, 0);
					}
					else
					{
						joueur->defPosition(positions[2]);
						retirerMur();
						joueur->deBloquer();
						enChangementDeSalle = false;
						ControlleurAudio::obtInstance().jouer(FERMETURE_PORTE, joueur);
					}
				}
			}
			else
				premiereFois = false;
			return true;
		}
		return false;
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

		int nbrObjet(0);
		while (!fichierObjet.eof()) {
			char* curseur1 = new char[20];
			fichierObjet >> curseur1;
			cheminsObjet.push_back(curseur1);
			++nbrObjet;
		}
		
		for (int i = 0; i < cheminsObjet.size(); ++i){
			InfoObjet obj;
			LecteurFichier::lireObjet(cheminsObjet[i], obj);
			if (obj.type == ITEM){
				if (obj.IDitem == 0 || obj.IDitem == 1 || obj.IDitem == 2 || obj.IDitem == 3 || obj.IDitem == 10 || obj.IDitem == 11 || obj.IDitem == 12 || obj.IDitem == 20){
					ItemsUniques.push(obj);
				}
				else
					Items.push_back(obj);
			}
			else
				Fixes.push_back(obj);
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
		std::list<int> sallePrecedente;
		std::vector<int> salleAvecPuzzle;

		do {
			IDSalle = rand() % nombreDeSalle;
		} while (!creerPuzzle(*std::find_if(std::begin(infosSalles), std::end(infosSalles), [&](InfoSalle info){ return info.ID == IDSalle; }), nbrPuzzle));
		salleAvecPuzzle.push_back(IDSalle);

		int essai(0);

		for (int i = 1; i < nombreDeSalle / 3 && nbrPuzzle > 0; ++i) {
			prochaineSalle = rand() % nombreDeSalle;
			while (!creerPuzzle(*std::find_if(std::begin(infosSalles), std::end(infosSalles), [&](InfoSalle info){ return info.ID == prochaineSalle; }), nbrPuzzle)){
				do {
					prochaineSalle = rand() % nombreDeSalle;
					salleCorrecte = true;
					salleSuivante = carte.obtListeAdjacence(prochaineSalle);

					for (int j = 0; j < salleAvecPuzzle.size(); ++j) {
						salleSuivante = carte.obtListeAdjacence(salleAvecPuzzle[j]);
						sallePrecedente = carte.obtListeAdjacenceInverse(salleAvecPuzzle[j]);
						if (essai < 15) {
							for (auto s : salleSuivante) {
								if (s == prochaineSalle)
									salleCorrecte = false;
							}

							for (auto p : sallePrecedente) {
								if (p == prochaineSalle)
									salleCorrecte = false;
							}
						}
						if ((salleAvecPuzzle[j] == prochaineSalle))
							salleCorrecte = !true; // Parce que pourquoi pas...

						++essai;
					}
				} while (!salleCorrecte);
			}
			IDSalle = prochaineSalle;
			salleAvecPuzzle.push_back(IDSalle);
			essai = 0;
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
				objet.estVerrouille = false;
				it.Objet.push_front(new InfoObjet(objet));
			}
			
			objet.ID = it.Objet.size();
			objet.largeur = 0;
			if (ItemsUniques.size()){
				objet = ItemsUniques.top();
				if(positionnerObjet(*modeleSalle, it, objet)){
					it.Objet.push_back(new InfoObjet(objet));
					ItemsUniques.pop();
				}
			}
			objet.ID = it.Objet.size();
			objet.largeur = 0;
			objet = Items[rand() % Items.size()];
			if(positionnerObjet(*modeleSalle, it, objet)){
				it.Objet.push_back(new InfoObjet(objet));
			}
			for (unsigned short i = 0; i < 3; ++i) {
				objet.ID = it.Objet.size();
				objet.largeur = 0;
				objet = Fixes[rand() % Fixes.size()];
				if(positionnerObjet(*modeleSalle, it, objet))
					it.Objet.push_back(new InfoObjet(objet));
			}

			// Ajout et réinitialisation de la salle.
			delete modeleSalle;
			chargement += (100.0f / nombreDeSalle);
		}
		finChargement = true;
	}

	Vecteur3d debut(double& hAngle, double& vAngle) {

		// Salle de début

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
		porte.rotation = { 0, 90, 0 };
		porte.estVerrouille = false;
		salleDebut.Objet.push_back(new InfoObjet(porte));

		// Lit

		InfoObjet lit;
		LecteurFichier::lireObjet("Ressources/Info/lit.txt", lit);
		lit.direction = { 0, 0, 0 };
		lit.ID = 1;
		lit.largeur = 0;
		lit.position = { 2.5, 1.0, -10.9 };
		lit.rotation = { 0, 0, 0 };

		salleDebut.Objet.push_back(new InfoObjet(lit));

		// Lavabo

		InfoObjet lavabo;
		LecteurFichier::lireObjet("Ressources/Info/lavabo.txt", lavabo);
		lavabo.direction = { 0, 0, 0 };
		lavabo.ID = 2;
		lavabo.largeur = 0;
		lavabo.position = { 5.0, 1.3, -1.5 };
		lavabo.rotation = { 0, 0, 0 };

		salleDebut.Objet.push_back(new InfoObjet(lavabo));

		// Bureau

		InfoObjet bureau;
		LecteurFichier::lireObjet("Ressources/Info/bureau.txt", bureau);
		bureau.direction = { 0, 0, 0 };
		bureau.ID = 3;
		bureau.largeur = 0;
		bureau.position = { -4.9, 0.0, -3.0 };
		bureau.rotation = { 0, -90, 0 };

		salleDebut.Objet.push_back(new InfoObjet(bureau));
		
			// Companion
		
		InfoObjet companion;
		LecteurFichier::lireObjet("Ressources/Info/thai.txt", companion);
		companion.direction = { 0, 0, 0 };
		companion.ID = 8;
		companion.largeur = 0;
		companion.position = { -4.9, 2.0, -3.0 };
		companion.IDitem = 42;
		
		salleDebut.Objet.push_back(new InfoObjet(companion));


		// Poubelle

		InfoObjet poubelle;
		LecteurFichier::lireObjet("Ressources/Info/poubelle.txt", poubelle);
		poubelle.direction = { 0, 0, 0 };
		poubelle.ID = 4;
		poubelle.largeur = 0;
		poubelle.position = { -4.3, 0.0, -0.75 };
		poubelle.rotation = { 0, 0, 0 };

		salleDebut.Objet.push_back(new InfoObjet(poubelle));

		// Etagere

		InfoObjet etagere;
		LecteurFichier::lireObjet("Ressources/Info/etagere.txt", etagere);
		etagere.direction = { 0, 0, 0 };
		etagere.ID = 5;
		etagere.largeur = 0;
		etagere.position = { -1.7, 0.0, 1.55 };
		etagere.rotation = { 0, 180, 0 };

		salleDebut.Objet.push_back(new InfoObjet(etagere));

		// Table de chevet

		InfoObjet tabledechevet;
		LecteurFichier::lireObjet("Ressources/Info/tabledechevet.txt", tabledechevet);
		tabledechevet.direction = { 0, 0, 0 };
		tabledechevet.ID = 6;
		tabledechevet.largeur = 0;
		tabledechevet.position = { 1.0, 1.0, -10.5 };
		tabledechevet.rotation = { 0, 0, 0 };

		salleDebut.Objet.push_back(new InfoObjet(tabledechevet));

		// Masque

		InfoObjet masque;
		masque.direction = { 0, 0, 0 };
		masque.ID = 7;
		masque.largeur = 0;
		masque.position = { 1.0, 2.0, -10.5 };
		masque.rotation = { 0, 0, 0 };
		masque.IDitem = 50;
		masque.type = ITEM;

		salleDebut.Objet.push_back(new InfoObjet(masque));

		// Ajout du lien de sortie de la salle de début

		int IDporte;

		auto it = infosSalles.begin();

		std::advance(it, rand() % nombreDeSalle);

		InfoObjet obj;
		obj.largeur = 0;
		LecteurFichier::lireObjet("Ressources/Info/portePlate.txt", obj);
		gfx::Modele3D* mod;
		for (auto &itt : infosSalles){
			if (itt.ID == it->ID){
				IDporte = obj.ID = itt.Objet.size();
				mod = new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele(itt.cheminModele), gfx::GestionnaireRessources::obtInstance().obtTexture(itt.cheminTexture));
				mod->defEchelle(itt.echelle.x, itt.echelle.y, itt.echelle.z);
				itt.nbrPorte++;
				positionnerPorte(*mod, itt, obj);
				obj.estVerrouille = false;
				itt.Objet.push_back(new InfoObjet(obj));
				break;
			}
		}

		//ajouterLien(Entree(salleDebut.ID, 0, false), Sortie(infosSalles.size()+4, 0));
		ajouterLien(Entree(salleDebut.ID, 0, false), Sortie(it->ID, IDporte));
		ajouterLien(Entree(it->ID, IDporte, false), Sortie(salleDebut.ID, 0));

		// Ajout/Création de la salle et autre
		infosSalles.push_back(salleDebut);

		// Verrouillage des portes...
		std::map<unsigned int, unsigned int> itterateurs;
		for (unsigned int i = 0; i < infosSalles.size(); ++i) {
			itterateurs[i] = 0;
		}
		etablirPorteVerrouille(std::get<0>(liens[Entree(salleDebut.ID, 0, false)]), salleDebut.ID, 1, itterateurs);

		creerSalle(salleDebut);

		modeleMur = new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/murSalle.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/murSalle.png"));
		modelePorte = new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele("Ressources/Modele/portePlate.obj"), gfx::GestionnaireRessources::obtInstance().obtTexture("Ressources/Texture/portePlate.png"));
		modeleMur->defOrientation(0, 0, 0);
		modelePorte->defOrientation(0, 0, 0);

		translations[0] = Vecteur3d(6.2604991551431175809545086, 7.80950374479346291875153944, 4.65);
		positions[0] = lit.position + Vecteur3d(-0.32567, 0.98625, 0.43851);
		double ln = log(1.611022959 / 0.08);
		positions[1] = Vecteur3d(positions[0].x - (ln / translations[0].x),
			positions[0].y + (ln / translations[0].y),
			positions[0].z + (ln / translations[0].z));
		positions[2] = Vecteur3d(1.32694, 2.74, -9.81577);
		translations[1] = Maths::vecteurEntreDeuxPoints(positions[1], positions[2]);
		premiereFois = true;
		ouvrirYeux = true;
		enLeverLit = true;
		teleporte = true;
		hAngle = 0;
		vAngle = 50;
		noirHautBas[0] = new gfx::Sprite2D(Vecteur2f(0, (fenetre->obtTaille().y / 2) - (170 * ((float)fenetre->obtTaille().y / (float)RESOLUTION_DEFAUT_Y))), new gfx::Texture("Ressources/Texture/noirHaut.png"));
		noirHautBas[1] = new gfx::Sprite2D(Vecteur2f(0, 0), new gfx::Texture("Ressources/Texture/noirBas.png"));
		noirHautBas[1]->defPosition(Vecteur2f(0, -((noirHautBas[1]->obtTexture()->obtTaille().y * ((float)fenetre->obtTaille().y / (float)RESOLUTION_DEFAUT_Y)) - fenetre->obtTaille().y / 2) + (170 * ((float)fenetre->obtTaille().y / (float)RESOLUTION_DEFAUT_Y))));

		gfx::Gestionnaire2D::obtInstance().ajouterObjets({ noirHautBas[0], noirHautBas[1] });

		teleporteur();
		fin();
		salleBasseGravite();
		sallePhilo();
		salleIllumi();
		return Vecteur3d(positions[0].x, positions[0].y - 1.74, positions[0].z);
	}

	void teleporteur(){

		InfoSalle salleTeleporteur;
		salleTeleporteur.cheminModele = "Ressources/Modele/teleporteur.obj";
		salleTeleporteur.cheminTexture = "Ressources/Texture/teleporteur.png";
		salleTeleporteur.echelle = { 1.0, 1.0, 1.0 };
		salleTeleporteur.ID = infosSalles.size();
		salleTeleporteur.nbrPorte = 1;

		// Création des objets de la salle

		// Porte (EntrŽe)

		InfoObjet porte;
		LecteurFichier::lireObjet("Ressources/Info/portePlate.txt", porte);
		porte.direction = { 1, 0, 0 };
		porte.ID = 0;
		porte.largeur = 0;
		porte.position = { 21.1, 0, -1.470588235 / 2 };
		porte.rotation = { 0, 180, 0 };
		porte.estVerrouille = false;
		salleTeleporteur.Objet.push_back(new InfoObjet(porte));


		// Porte (Sortie)
		InfoObjet porte2;
		LecteurFichier::lireObjet("Ressources/Info/portePlate.txt", porte2);
		porte2.direction = { -1, 0, 0 };
		porte2.ID = 1;
		porte2.largeur = 0;
		porte2.position = { -21.1, 0, 1.470588235 / 2 };
		porte2.rotation = { 0, 0, 0 };
		porte2.estVerrouille = false;
		salleTeleporteur.Objet.push_back(new InfoObjet(porte2));

		// Poste
		InfoObjet poste;
		poste.cheminModele = "Ressources/Modele/poste.obj";
		poste.cheminTexture = "Ressources/Texture/poste.png";
		poste.direction = { 0, 0, 0 };
		poste.ID = 2;
		poste.largeur = 0;
		poste.position = { 0, 0, 5 };
		poste.rotation = { 0, 90, 0 };
		poste.type = FIXE;

		salleTeleporteur.Objet.push_back(new InfoObjet(poste));

		// Plate
		InfoObjet plate;
		plate.cheminModele = "Ressources/Modele/plate.obj";
		plate.cheminTexture = "Ressources/Texture/plate.png";
		plate.direction = { 0, 0, 0 };
		plate.ID = 3;
		plate.largeur = 0;
		plate.position = { 0.93, 0.96, 4.7 };
		plate.rotation = { 0, 90, 0 };
		plate.type = FIXE;

		salleTeleporteur.Objet.push_back(new InfoObjet(plate));

		plate.ID = 4;
		plate.position = { 0.73, 0.96, 4.7 };
		plate.type = FIXE;

		salleTeleporteur.Objet.push_back(new InfoObjet(plate));

		plate.ID = 5;
		plate.position = { 0.53, 0.96, 4.7 };
		plate.type = FIXE;

		salleTeleporteur.Objet.push_back(new InfoObjet(plate));

		plate.ID = 6;
		plate.position = { 0.33, 0.96, 4.7 };
		plate.type = FIXE;

		salleTeleporteur.Objet.push_back(new InfoObjet(plate));



		plate.ID = 7;
		plate.position = { -0.13, 0.96, 4.7 };
		plate.type = FIXE;

		salleTeleporteur.Objet.push_back(new InfoObjet(plate));

		plate.ID = 10;
		plate.position = { -0.73, 0.96, 4.7 };
		plate.type = FIXE;

		salleTeleporteur.Objet.push_back(new InfoObjet(plate));

		plate.ID = 9;
		plate.position = { -0.53, 0.96, 4.7 };
		plate.type = FIXE;

		salleTeleporteur.Objet.push_back(new InfoObjet(plate));

		plate.ID = 8;
		plate.position = { -0.33, 0.96, 4.7 };
		plate.type = FIXE;

		salleTeleporteur.Objet.push_back(new InfoObjet(plate));

		//Switch

		InfoObjet com;
		com.cheminModele = "Ressources/Modele/switch.obj";
		com.cheminTexture = "Ressources/Texture/switch.png";
		com.direction = { 0, 0, 0 };
		com.ID = 11;
		com.largeur = 0;
		com.position = { 0.93, 0.98, 4.72 };
		com.rotation = { 0, 90, 0 };
		com.type = COMMUTATEUR;

		salleTeleporteur.Objet.push_back(new InfoObjet(com));

		com.ID = 12;
		com.position = { 0.73, 0.98, 4.72 };
		com.type = COMMUTATEUR;

		salleTeleporteur.Objet.push_back(new InfoObjet(com));

		com.ID = 13;
		com.position = { 0.53, 0.98, 4.72 };
		com.type = COMMUTATEUR;

		salleTeleporteur.Objet.push_back(new InfoObjet(com));

		com.ID = 14;
		com.position = { 0.33, 0.98, 4.72 };
		com.type = COMMUTATEUR;

		salleTeleporteur.Objet.push_back(new InfoObjet(com));



		com.ID = 15;
		com.position = { -0.13, 0.98, 4.72 };
		com.type = COMMUTATEUR;

		salleTeleporteur.Objet.push_back(new InfoObjet(com));

		com.ID = 18;
		com.position = { -0.73, 0.98, 4.72 };
		com.type = COMMUTATEUR;

		salleTeleporteur.Objet.push_back(new InfoObjet(com));

		com.ID = 17;
		com.position = { -0.53, 0.98, 4.72 };
		com.type = COMMUTATEUR;

		salleTeleporteur.Objet.push_back(new InfoObjet(com));

		com.ID = 16;
		com.position = { -0.33, 0.98, 4.72 };
		com.type = COMMUTATEUR;

		salleTeleporteur.Objet.push_back(new InfoObjet(com));
		int IDporte;
		
		auto it = infosSalles.begin();
		
		std::advance(it, rand() % nombreDeSalle);
		
		InfoObjet obj;
		obj.largeur = 0;
		LecteurFichier::lireObjet("Ressources/Info/portePlate.txt", obj);
		gfx::Modele3D* mod;
		for (auto &itt : infosSalles){
			if (itt.ID == it->ID){
				IDporte = obj.ID = itt.Objet.size();
				mod = new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele(itt.cheminModele), gfx::GestionnaireRessources::obtInstance().obtTexture(itt.cheminTexture));
				mod->defEchelle(itt.echelle.x, itt.echelle.y, itt.echelle.z);
				itt.nbrPorte++;
				positionnerPorte(*mod, itt, obj);
				obj.estVerrouille = false;
				(*it).Objet.push_back(new InfoObjet(obj));
				break;
			}
		}
		
		ajouterLien(Entree(salleTeleporteur.ID, 0, false), Sortie(it->ID, IDporte));
		ajouterLien(Entree(it->ID, IDporte, false), Sortie(salleTeleporteur.ID, 0));
		
		infosSalles.push_back(salleTeleporteur);
	}
	
	void sallePhilo(){
		InfoSalle sallePhilo;
		sallePhilo.cheminModele = "Ressources/Modele/PiecePhilo.obj";
		sallePhilo.cheminTexture = "Ressources/Texture/PiecePhilo.png";
		sallePhilo.echelle = { 1.0, 1.0, 1.0 };
		sallePhilo.ID = infosSalles.size();
		sallePhilo.nbrPorte = 3;

		// Création des objets de la salle

		// Porte (Entree)

		InfoObjet porte;
		LecteurFichier::lireObjet("Ressources/Info/portePlate.txt", porte);
		porte.direction = { 0, 0, 1 };
		porte.ID = 0;
		porte.largeur = 0;
		porte.position = { 0., 0., 4.88968};
		porte.rotation = { 0, 90, 0 };
		porte.estVerrouille = false;
		sallePhilo.Objet.push_back(new InfoObjet(porte));


		// Porte (Sortie1)
		InfoObjet porte2;
		LecteurFichier::lireObjet("Ressources/Info/portePlate.txt", porte2);
		porte2.direction = { 0, 0, -1 };
		porte2.ID = 1;
		porte2.largeur = 0;
		porte2.position = { 1.5, 0., -4.88968 };
		porte2.rotation = { 0, 270, 0 };
		porte2.estVerrouille = false;
		sallePhilo.Objet.push_back(new InfoObjet(porte2));

		// Porte (Sortie2)
		InfoObjet porte3;
		LecteurFichier::lireObjet("Ressources/Info/portePlate.txt", porte3);
		porte3.direction = { 0, 0, -1 };
		porte3.ID = 2;
		porte3.largeur = 0;
		porte3.position = { -3., 0., -4.88968 };
		porte3.rotation = { 0, 270, 0 };
		porte3.estVerrouille = false;
		sallePhilo.Objet.push_back(new InfoObjet(porte3));

		// Personnage à tuer/sauver
		InfoObjet personnage;
		personnage.largeur = 100;
		personnage.cheminModele = "Ressources/Modele/Kevin.obj";
		personnage.cheminTexture = "Ressources/Texture/Kevin.png";
		personnage.direction = { 0, 0, 0 };
		personnage.ID = 3;
		personnage.largeur = 0;
		personnage.position = { 2.25, 0., -4.5 };
		personnage.rotation = { 0, 0, 0 };
		personnage.type = PERSONNAGE;
		sallePhilo.Objet.push_back(new InfoObjet(personnage));

		//Arme
		InfoObjet arme;
		arme.direction = { 0, 0, 0 };
		arme.ID = 4;
		arme.position = { 0., 2., 0. };
		arme.rotation = { 0, 0, 0 };
		arme.type = ITEM;
		arme.IDitem = 32;
		arme.positionement = SOLS;
		sallePhilo.Objet.push_back(new InfoObjet(arme));


		int IDporte;

		auto it = infosSalles.begin();

		std::advance(it, rand() % nombreDeSalle);

		InfoObjet obj;
		obj.largeur = 0;
		LecteurFichier::lireObjet("Ressources/Info/portePlate.txt", obj);
		gfx::Modele3D* mod;
		for (auto &itt : infosSalles){
			if (itt.ID == it->ID){
				IDporte = obj.ID = itt.Objet.size();
				mod = new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele(itt.cheminModele), gfx::GestionnaireRessources::obtInstance().obtTexture(itt.cheminTexture));
				mod->defEchelle(itt.echelle.x, itt.echelle.y, itt.echelle.z);
				itt.nbrPorte++;
				positionnerPorte(*mod, itt, obj);
				obj.estVerrouille = false;
				(*it).Objet.push_back(new InfoObjet(obj));
				break;
			}
		}

		ajouterLien(Entree(sallePhilo.ID, 0, false), Sortie(it->ID, IDporte));
		ajouterLien(Entree(it->ID, IDporte, false), Sortie(sallePhilo.ID, 0));

		infosSalles.push_back(sallePhilo);
	}

	void salleBasseGravite(){
		InfoSalle salleBasseGravite;
		salleBasseGravite.cheminModele = "Ressources/Modele/SalleBasseGravite.obj";
		salleBasseGravite.cheminTexture = "Ressources/Texture/SalleBasseGravite.png";
		salleBasseGravite.echelle = { 1.0, 1.0, 1.0 };
		salleBasseGravite.ID = infosSalles.size();
		salleBasseGravite.nbrPorte = 2;

		// Création des objets de la salle

		// Porte (Entree)

		InfoObjet porte;
		LecteurFichier::lireObjet("Ressources/Info/portePlate.txt", porte);
		porte.direction = { 0, 0, -1 };
		porte.ID = 0;
		porte.largeur = 0;
		porte.position = { -0.76278, 2.18987, -10.92852 };
		porte.rotation = { 0, -90, 0 };
		porte.estVerrouille = false;
		salleBasseGravite.Objet.push_back(new InfoObjet(porte));


		// Porte (Sortie)
		InfoObjet porte2;
		LecteurFichier::lireObjet("Ressources/Info/portePlate.txt", porte2);
		porte2.direction = { 0, 0, 1 };
		porte2.ID = 1;
		porte2.largeur = 0;
		porte2.position = { 0.71043, 3.53152, 22.30799 };
		porte2.rotation = { 0, 90, 0 };
		porte2.estVerrouille = false;
		salleBasseGravite.Objet.push_back(new InfoObjet(porte2));

		// Plate
		InfoObjet plate;
		plate.cheminModele = "Ressources/Modele/plate.obj";
		plate.cheminTexture = "Ressources/Texture/plate.png";
		plate.direction = { 0, 0, 0 };
		plate.ID = 2;
		plate.largeur = 0;
		plate.position = { -2.15766, 3.90031, -7.41128 };
		plate.rotation = { 0, 90, -90 };
		plate.type = FIXE;
		salleBasseGravite.Objet.push_back(new InfoObjet(plate));

		//Commutateur
		InfoObjet com;
		com.cheminModele = "Ressources/Modele/switch.obj";
		com.cheminTexture = "Ressources/Texture/switch.png";
		com.direction = { 0, 0, 0 };
		com.ID = 3;
		com.largeur = 0;
		com.position = { -2.14066, 3.90031, -7.41128 };
		com.rotation = { -90, 0, 0 };
		com.type = COMMUTATEUR;
		salleBasseGravite.Objet.push_back(new InfoObjet(com));

		int IDporte;

		auto it = infosSalles.begin();

		std::advance(it, rand() % nombreDeSalle);

		InfoObjet obj;
		obj.largeur = 0;
		LecteurFichier::lireObjet("Ressources/Info/portePlate.txt", obj);
		gfx::Modele3D* mod;
		for (auto &itt : infosSalles){
			if (itt.ID == it->ID){
				IDporte = obj.ID = itt.Objet.size();
				mod = new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele(itt.cheminModele), gfx::GestionnaireRessources::obtInstance().obtTexture(itt.cheminTexture));
				mod->defEchelle(itt.echelle.x, itt.echelle.y, itt.echelle.z);
				itt.nbrPorte++;
				positionnerPorte(*mod, itt, obj);
				obj.estVerrouille = false;
				(*it).Objet.push_back(new InfoObjet(obj));
				break;
			}
		}

		ajouterLien(Entree(salleBasseGravite.ID, 0, false), Sortie(it->ID, IDporte));
		ajouterLien(Entree(it->ID, IDporte, false), Sortie(salleBasseGravite.ID, 0));

		infosSalles.push_back(salleBasseGravite);
	}

	void fin(){
		// Salle de fin

		InfoSalle salleFin;
		salleFin.cheminModele = "Ressources/Modele/SalleFinStuff.obj";
		salleFin.cheminTexture = "Ressources/Texture/salleFinStuff.png";
		salleFin.echelle = { 1.0, 1.0, 1.0 };
		salleFin.ID = infosSalles.size();
		salleFin.nbrPorte = 1;

		// Création objets salle finale

		InfoObjet demiSphere;
		LecteurFichier::lireObjet("Ressources/Info/demiSphere.txt", demiSphere);
		demiSphere.direction = { 0, 0, 0 };
		demiSphere.ID = 0;
		demiSphere.largeur = 0;
		demiSphere.position = { -32.9405, 0, -74.5517 };
		demiSphere.rotation = { 0, 0, 0 };
		demiSphere.type = FIXE;

		salleFin.Objet.push_back(new InfoObjet(demiSphere));

		// Porte

		InfoObjet porteFin;
		LecteurFichier::lireObjet("Ressources/Info/portePlate.txt", porteFin);
		porteFin.direction = { 0, 0, 0 };
		porteFin.ID = 1;
		porteFin.largeur = 0;
		porteFin.position = { -32.9405, 0, -74.5517 };
		porteFin.rotation = { 0, -38, 0 };
		porteFin.estVerrouille = false;
		salleFin.Objet.push_back(new InfoObjet(porteFin));

		// Création de l'avion

		InfoObjet avion;
		LecteurFichier::lireObjet("Ressources/Info/avion.txt", avion);
		avion.direction = { 0, 0, 0 };
		avion.ID = 2;
		avion.largeur = 0;
		avion.position = { -17, 0, -74.7745 };
		avion.rotation = { 0, 0, 0 };
		avion.type = 2;

		salleFin.Objet.push_back(new InfoObjet(avion));
		
		int IDporte;
		
		auto it = infosSalles.begin();
		
		std::advance(it, rand() % nombreDeSalle);
		
		InfoObjet obj;
		obj.largeur = 0;
		LecteurFichier::lireObjet("Ressources/Info/portePlate.txt", obj);
		gfx::Modele3D* mod;
		for (auto &itt : infosSalles){
			if (itt.ID == it->ID){
				IDporte = obj.ID = itt.Objet.size();
				mod = new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele(itt.cheminModele), gfx::GestionnaireRessources::obtInstance().obtTexture(itt.cheminTexture));
				mod->defEchelle(itt.echelle.x, itt.echelle.y, itt.echelle.z);
				itt.nbrPorte++;
				positionnerPorte(*mod, itt, obj);
				obj.estVerrouille = false;
				itt.Objet.push_back(new InfoObjet(obj));
				break;
			}
		}
		
		ajouterLien(Entree(salleFin.ID, 0, false), Sortie(it->ID, IDporte));
		ajouterLien(Entree(it->ID, IDporte, false), Sortie(salleFin.ID, 0));
		
		infosSalles.push_back(salleFin);
	}

	bool animationLeverLit(Joueur* joueur, float frameTime) {
		if (enLeverLit) {
			if (frameTime < 0.5) { // À cause du frametime accumulé
				temps += frameTime;
				if (ouvrirYeux) {
					if (temps < 4.2) {
						if ((temps < 1) || (temps > 2.5 && temps < 4)) {
							noirHautBas[0]->defPosition(Vecteur2f(noirHautBas[0]->obtPosition().x, noirHautBas[0]->obtPosition().y + (frameTime * (float)(fenetre->obtTaille().y / 2))));
							noirHautBas[1]->defPosition(Vecteur2f(noirHautBas[1]->obtPosition().x, noirHautBas[1]->obtPosition().y - (frameTime * (float)(fenetre->obtTaille().y / 2))));
						}
						else if (temps < 2) {
							noirHautBas[0]->defPosition(Vecteur2f(noirHautBas[0]->obtPosition().x, noirHautBas[0]->obtPosition().y - (frameTime * (float)(fenetre->obtTaille().y / 2))));
							noirHautBas[1]->defPosition(Vecteur2f(noirHautBas[1]->obtPosition().x, noirHautBas[1]->obtPosition().y + (frameTime * (float)(fenetre->obtTaille().y / 2))));
						}
					}
					else
					{
						ouvrirYeux = false;
						gfx::Gestionnaire2D::obtInstance().retObjets({ noirHautBas[0], noirHautBas[1] });
						delete noirHautBas[0];
						delete noirHautBas[1];
						temps = 0;
					}
				}
				else
				{
					if (translations[0].x) {
						if (Maths::vecteurEntreDeuxPoints(positions[0], positions[1]).produitScalaire(Maths::vecteurEntreDeuxPoints(joueur->obtPositionCamera(), positions[1])) > 0) {
							double ln = log(temps / 0.08);
							Vecteur3d tmp = { 2.17433 - (ln / translations[0].x),
								1.98625 + (ln / translations[0].y),
								-10.46149 + (ln / translations[0].z) };
							tmp.y -= 1.74;
							joueur->defPosition(tmp);
							joueur->defHAngle(0 - (temps*55.86512563));
							joueur->defVAngle(50 - (temps*46.55427137));
						}
						else
						{
							translations[0].x = 0;
							temps = 0;
						}
					}
					else
					{
						if (temps > 2) {
							if (translations[1].produitScalaire(Maths::vecteurEntreDeuxPoints(joueur->obtPositionCamera(), positions[2])) > 0) {
								joueur->defPosition(joueur->obtPosition() + (translations[1] * frameTime * 1.5));
								joueur->defVAngle(joueur->obtVAngle() + (frameTime * 40));
							}
							else
							{
								joueur->deBloquer();
								enLeverLit = false;
							}
						}
					}
				}
			}
			return true;
		}
		return false;
	}

	void calculAnimationFinPartie(Joueur* joueur){
		if (!dejaCalculee){
			joueur->defPosition(Vecteur3d(-32.9405, 0, -74.5517));
			joueur->bloquer();
			avion = salleActive->obtListeObjet().back();
			Vecteur3d vec1 = avion->obtPosition();
			vec1.x -= 1.174;
			vec1.y = 0;
			vec1.z += 0.32904;
			translations[0] = Maths::vecteurEntreDeuxPoints(joueur->obtPosition(), vec1);
			orientationCamera[0] = joueur->obtDevant().angleEntreVecteurs(translations[0]) * 180 / M_PI;
			positions[0] = vec1;

			vec1 = (avion)->obtPosition();
			vec1.z += 1.3;
			vec1.y += 0.1;

			positions[1] = vec1;
			translations[1] = Maths::vecteurEntreDeuxPoints(joueur->obtPosition() + translations[0], positions[1]);
			orientationCamera[1] = translations[0].angleEntreVecteurs(Vecteur3d(0, 0, 1)) * 180 / M_PI + 18;
			orientationCamera[2] = 20;
			enFinPartie = true;
			alavion = false;
			dejaCalculee = true;
		}
	}

	unsigned int animationFinPartie(Joueur* joueur, float frameTime){
		if (enFinPartie){
			if (!alavion) {
				if (translations[0].produitScalaire(Maths::vecteurEntreDeuxPoints(joueur->obtPosition(), positions[0])) > 0){
					joueur->defPosition(joueur->obtPosition() + translations[0] * frameTime * 0.10f);

					if (orientationCamera[0] > 0){
						joueur->defHAngle(joueur->obtHAngle() + 1);
						orientationCamera[0] -= 1;
					}
					return 1;
				}
				else {
					if (translations[1].produitScalaire(Maths::vecteurEntreDeuxPoints(joueur->obtPosition(), positions[1])) > 0) {
						joueur->defPosition(joueur->obtPosition() + translations[1] * frameTime * 0.5f);

						if (orientationCamera[1] > 0){
							joueur->defHAngle(joueur->obtHAngle() - 1);
							orientationCamera[1] -= 1;
						}
						if (orientationCamera[2] > 0){
							joueur->defHAngle(joueur->obtHAngle() + 1);
							orientationCamera[2] -= 1;
						}
						return 1;
					}
					else
					{
						translations[0] = Maths::vecteurEntreDeuxPoints(avion->obtPosition(), Vecteur3d(avion->obtPosition().x + 10, 0, avion->obtPosition().z + 600));
						positions[0] = Vecteur3d(avion->obtPosition().x, 15, avion->obtPosition().z + 600);
						ControlleurAudio::obtInstance().jouer(AVION, joueur);
						temps = 0;
						alavion = true;
						return 1;
					}
				}
			}
			else
			{
				temps += frameTime;
				if (translations[0].produitScalaire(Maths::vecteurEntreDeuxPoints(avion->obtPosition(), positions[0])) > 0) {
					avion->defPosition(avion->obtPosition() + translations[0] * temps / 1000);
					joueur->defPosition(joueur->obtPosition() + translations[0] * temps / 1000);
					if (temps >= 1) {
						avion->defPosition(avion->obtPosition() + Vecteur3d(0, (temps - 1) / 25, 0));
						joueur->defPosition(joueur->obtPosition() + Vecteur3d(0, (temps - 1) / 25, 0));
					}
					return 1;
				}
				else
				{
					avion = nullptr;
					enFinPartie = true;
					///Terminée
					return 2;
				}
			}
		}
		return 0;
	}
	
	void salleIllumi(){
		InfoSalle illumi;
		illumi.cheminModele = "Ressources/Modele/SalleIlluminazi.obj";
		illumi.cheminTexture = "Ressources/Texture/SalleIlluminazi.png";
		illumi.echelle = { 3.0, 3.0, 3.0 };
		illumi.ID = infosSalles.size();
		illumi.nbrPorte = 3;
		
			// Création des objets de la salle
		
			// Porte (Entree)
		
		InfoObjet porte;
		LecteurFichier::lireObjet("Ressources/Info/portePlate.txt", porte);
		porte.direction = { 0, 0, 1 };
		porte.ID = 0;
		porte.largeur = 0;
		porte.position = { 9., 0., 0.};
		porte.rotation = { 0, 90, 0 };
		porte.estVerrouille = false;
		illumi.Objet.push_back(new InfoObjet(porte));
		
		int IDporte;
		
		auto it = infosSalles.begin();
		
		std::advance(it, rand() % nombreDeSalle);
		
		InfoObjet obj;
		obj.largeur = 0;
		LecteurFichier::lireObjet("Ressources/Info/portePlate.txt", obj);
		gfx::Modele3D* mod;
		for (auto &itt : infosSalles){
			if (itt.ID == it->ID){
				IDporte = obj.ID = itt.Objet.size();
				mod = new gfx::Modele3D(gfx::GestionnaireRessources::obtInstance().obtModele(itt.cheminModele), gfx::GestionnaireRessources::obtInstance().obtTexture(itt.cheminTexture));
				mod->defEchelle(itt.echelle.x, itt.echelle.y, itt.echelle.z);
				itt.nbrPorte++;
				positionnerPorte(*mod, itt, obj);
				obj.estVerrouille = false;
				(*it).Objet.push_back(new InfoObjet(obj));
				break;
			}
		}
		
		ajouterLien(Entree(illumi.ID, 0, false), Sortie(it->ID, IDporte));
		ajouterLien(Entree(it->ID, IDporte, false), Sortie(illumi.ID, 0));
		
		infosSalles.push_back(illumi);
	}

	void recommencer() {
		delete modeleMur;
		delete modelePorte;
		modeleMur = nullptr;
		modelePorte = nullptr;
		carte = graphe::Graphe();
		delete salleActive;
		salleActive = nullptr;
		infosSalles.clear();
		liens.clear();
		chargement = 0;

	}

	void defNbrSalle(unsigned int nbrSalles) {
		nombreDeSalle = nbrSalles;
	}

	bool obtEnFinPartie() {
		return enFinPartie;
	}

	bool pendules(InfoSalle& salle) {

		if (!strcmp(salle.cheminModele, "Ressources/Modele/SalleL.obj")) {

			InfoObjet pendule;
			pendule.cheminModele = "Ressources/Modele/Pendule.obj";
			pendule.cheminTexture = "Ressources/Texture/Pendule.png";
			pendule.position = Vecteur3d(-0.23306, 4.41787, 8.71071);
			pendule.ID = salle.Objet.size();
			pendule.rotation = Vecteur3d();
			pendule.type = PENDULE;
			salle.Objet.push_back(new InfoObjet(pendule));

			pendule.cheminModele = "Ressources/Modele/Pendule.obj";
			pendule.cheminTexture = "Ressources/Texture/Pendule.png";
			pendule.position = Vecteur3d(-4.79973, 4.41787, 8.71071);
			pendule.ID = salle.Objet.size();
			pendule.rotation = Vecteur3d();
			pendule.type = PENDULE;
			salle.Objet.push_back(new InfoObjet(pendule));

			pendule.cheminModele = "Ressources/Modele/Pendule.obj";
			pendule.cheminTexture = "Ressources/Texture/Pendule.png";
			pendule.position = Vecteur3d(-10.15104, 4.41787, 8.71071);
			pendule.ID = salle.Objet.size();
			pendule.rotation = Vecteur3d();
			pendule.type = PENDULE;
			salle.Objet.push_back(new InfoObjet(pendule));

			pendule.cheminModele = "Ressources/Modele/Pendule.obj";
			pendule.cheminTexture = "Ressources/Texture/Pendule.png";
			pendule.position = Vecteur3d(-15.40232, 4.41787, 8.71071);
			pendule.ID = salle.Objet.size();
			pendule.rotation = Vecteur3d();
			pendule.type = PENDULE;
			salle.Objet.push_back(new InfoObjet(pendule));


			InfoObjet poutre;
			poutre.cheminModele = "Ressources/Modele/PoutreVerticale.obj";
			poutre.cheminTexture = "Ressources/Texture/PoutreVerticale.png";
			poutre.position = Vecteur3d(-0.23306, 4.41787, 8.8136);
			poutre.ID = salle.Objet.size();
			poutre.rotation = Vecteur3d();
			poutre.type = FIXE;
			salle.Objet.push_back(new InfoObjet(poutre));

			poutre.cheminModele = "Ressources/Modele/PoutreVerticale.obj";
			poutre.cheminTexture = "Ressources/Texture/PoutreVerticale.png";
			poutre.position = Vecteur3d(-4.79973, 4.3465, 8.8136);
			poutre.ID = salle.Objet.size();
			poutre.rotation = Vecteur3d();
			poutre.type = FIXE;
			salle.Objet.push_back(new InfoObjet(poutre));

			poutre.cheminModele = "Ressources/Modele/PoutreVerticale.obj";
			poutre.cheminTexture = "Ressources/Texture/PoutreVerticale.png";
			poutre.position = Vecteur3d(-10.15104, 4.3465, 8.8136);
			poutre.ID = salle.Objet.size();
			poutre.rotation = Vecteur3d();
			poutre.type = FIXE;
			salle.Objet.push_back(new InfoObjet(poutre));

			poutre.cheminModele = "Ressources/Modele/PoutreVerticale.obj";
			poutre.cheminTexture = "Ressources/Texture/PoutreVerticale.png";
			poutre.position = Vecteur3d(-15.40232, 4.3465, 8.8136);
			poutre.ID = salle.Objet.size();
			poutre.rotation = Vecteur3d();
			poutre.type = FIXE;
			salle.Objet.push_back(new InfoObjet(poutre));


			InfoObjet remplisseur;
			remplisseur.cheminModele = "Ressources/Modele/Remplisseur.obj";
			remplisseur.cheminTexture = "Ressources/Texture/Remplisseur.png";
			remplisseur.position = Vecteur3d(-17.97485, 0, 5.50875);
			remplisseur.ID = salle.Objet.size();
			remplisseur.rotation = Vecteur3d();
			remplisseur.largeur = 17.981;
			remplisseur.type = REMPLISSEUR;
			salle.Objet.push_back(new InfoObjet(remplisseur));

			remplisseur.cheminModele = "Ressources/Modele/Remplisseur.obj";
			remplisseur.cheminTexture = "Ressources/Texture/Remplisseur.png";
			remplisseur.position = Vecteur3d(-0.12652, 0, 12.19997);
			remplisseur.ID = salle.Objet.size();
			remplisseur.rotation = Vecteur3d(0, 180, 0);
			remplisseur.largeur = 17.981;
			remplisseur.type = REMPLISSEUR;
			salle.Objet.push_back(new InfoObjet(remplisseur));

			return true;
		}
		else if (!strcmp(salle.cheminModele, "Ressources/Modele/SalleU.obj")){

			InfoObjet pendule;
			pendule.cheminModele = "Ressources/Modele/Pendule.obj";
			pendule.cheminTexture = "Ressources/Texture/Pendule.png";
			pendule.position = Vecteur3d(1.29921, 4.41787, -4.32525);
			pendule.ID = salle.Objet.size();
			pendule.rotation = Vecteur3d();
			pendule.type = PENDULE;
			salle.Objet.push_back(new InfoObjet(pendule));

			pendule.cheminModele = "Ressources/Modele/Pendule.obj";
			pendule.cheminTexture = "Ressources/Texture/Pendule.png";
			pendule.position = Vecteur3d(-3.26746, 4.41787, -4.32525);
			pendule.ID = salle.Objet.size();
			pendule.rotation = Vecteur3d();
			pendule.type = PENDULE;
			salle.Objet.push_back(new InfoObjet(pendule));

			pendule.cheminModele = "Ressources/Modele/Pendule.obj";
			pendule.cheminTexture = "Ressources/Texture/Pendule.png";
			pendule.position = Vecteur3d(-8.61877, 4.41787, -4.32525);
			pendule.ID = salle.Objet.size();
			pendule.rotation = Vecteur3d();
			pendule.type = PENDULE;
			salle.Objet.push_back(new InfoObjet(pendule));

			pendule.cheminModele = "Ressources/Modele/Pendule.obj";
			pendule.cheminTexture = "Ressources/Texture/Pendule.png";
			pendule.position = Vecteur3d(-13.87005, 4.41787, -4.32525);
			pendule.ID = salle.Objet.size();
			pendule.rotation = Vecteur3d();
			pendule.type = PENDULE;
			salle.Objet.push_back(new InfoObjet(pendule));


			InfoObjet poutre;
			poutre.cheminModele = "Ressources/Modele/PoutreVerticale.obj";
			poutre.cheminTexture = "Ressources/Texture/PoutreVerticale.png";
			poutre.position = Vecteur3d(1.29922, 4.34650, -4.22235);
			poutre.ID = salle.Objet.size();
			poutre.rotation = Vecteur3d();
			poutre.type = FIXE;
			salle.Objet.push_back(new InfoObjet(poutre));

			poutre.cheminModele = "Ressources/Modele/PoutreVerticale.obj";
			poutre.cheminTexture = "Ressources/Texture/PoutreVerticale.png";
			poutre.position = Vecteur3d(-3.26746, 4.34650, -4.22235);
			poutre.ID = salle.Objet.size();
			poutre.rotation = Vecteur3d();
			poutre.type = FIXE;
			salle.Objet.push_back(new InfoObjet(poutre));

			poutre.cheminModele = "Ressources/Modele/PoutreVerticale.obj";
			poutre.cheminTexture = "Ressources/Texture/PoutreVerticale.png";
			poutre.position = Vecteur3d(-8.61877, 4.34650, -4.22235);
			poutre.ID = salle.Objet.size();
			poutre.rotation = Vecteur3d();
			poutre.type = FIXE;
			salle.Objet.push_back(new InfoObjet(poutre));

			poutre.cheminModele = "Ressources/Modele/PoutreVerticale.obj";
			poutre.cheminTexture = "Ressources/Texture/PoutreVerticale.png";
			poutre.position = Vecteur3d(-13.87005, 4.34650, -4.22235);
			poutre.ID = salle.Objet.size();
			poutre.rotation = Vecteur3d();
			poutre.type = FIXE;
			salle.Objet.push_back(new InfoObjet(poutre));


			InfoObjet remplisseur;
			remplisseur.cheminModele = "Ressources/Modele/Remplisseur.obj";
			remplisseur.cheminTexture = "Ressources/Texture/Remplisseur.png";
			remplisseur.position = Vecteur3d(-16.44258, 0.00000, -7.52721);
			remplisseur.ID = salle.Objet.size();
			remplisseur.rotation = Vecteur3d();
			remplisseur.largeur = 21.111;
			remplisseur.type = REMPLISSEUR;
			salle.Objet.push_back(new InfoObjet(remplisseur));

			remplisseur.cheminModele = "Ressources/Modele/Remplisseur.obj";
			remplisseur.cheminTexture = "Ressources/Texture/Remplisseur.png";
			remplisseur.position = Vecteur3d(1.40575, 0.00000, -0.83598);
			remplisseur.ID = salle.Objet.size();
			remplisseur.rotation = Vecteur3d(0, 180, 0);;
			remplisseur.largeur = 20.970;
			remplisseur.type = REMPLISSEUR;
			salle.Objet.push_back(new InfoObjet(remplisseur));

			return true;

		}

		else if (!strcmp(salle.cheminModele, "Ressources/Modele/SalleConvergente.obj")) {

			InfoObjet pendule;
			pendule.cheminModele = "Ressources/Modele/Pendule.obj";
			pendule.cheminTexture = "Ressources/Texture/Pendule.png";
			pendule.position = Vecteur3d(8.40195, 4.41787, 0);
			pendule.ID = salle.Objet.size();
			pendule.rotation = Vecteur3d();
			pendule.type = PENDULE;
			salle.Objet.push_back(new InfoObjet(pendule));

			pendule.cheminModele = "Ressources/Modele/Pendule.obj";
			pendule.cheminTexture = "Ressources/Texture/Pendule.png";
			pendule.position = Vecteur3d(13.65323, 4.41787, 0);
			pendule.ID = salle.Objet.size();
			pendule.rotation = Vecteur3d();
			pendule.type = PENDULE;
			salle.Objet.push_back(new InfoObjet(pendule));

			pendule.cheminModele = "Ressources/Modele/Pendule.obj";
			pendule.cheminTexture = "Ressources/Texture/Pendule.png";
			pendule.position = Vecteur3d(19.00454, 4.41787, 0);
			pendule.ID = salle.Objet.size();
			pendule.rotation = Vecteur3d();
			pendule.type = PENDULE;
			salle.Objet.push_back(new InfoObjet(pendule));

			pendule.cheminModele = "Ressources/Modele/Pendule.obj";
			pendule.cheminTexture = "Ressources/Texture/Pendule.png";
			pendule.position = Vecteur3d(23.57121, 4.41787, 0);
			pendule.ID = salle.Objet.size();
			pendule.rotation = Vecteur3d();
			pendule.type = PENDULE;
			salle.Objet.push_back(new InfoObjet(pendule));


			InfoObjet poutre;
			poutre.cheminModele = "Ressources/Modele/PoutreVerticale.obj";
			poutre.cheminTexture = "Ressources/Texture/PoutreVerticale.png";
			poutre.position = Vecteur3d(8.40195, 4.41787, 0);
			poutre.ID = salle.Objet.size();
			poutre.rotation = Vecteur3d();
			poutre.type = FIXE;
			salle.Objet.push_back(new InfoObjet(poutre));

			poutre.cheminModele = "Ressources/Modele/PoutreVerticale.obj";
			poutre.cheminTexture = "Ressources/Texture/PoutreVerticale.png";
			poutre.position = Vecteur3d(13.65323, 4.3465, 0);
			poutre.ID = salle.Objet.size();
			poutre.rotation = Vecteur3d();
			poutre.type = FIXE;
			salle.Objet.push_back(new InfoObjet(poutre));

			poutre.cheminModele = "Ressources/Modele/PoutreVerticale.obj";
			poutre.cheminTexture = "Ressources/Texture/PoutreVerticale.png";
			poutre.position = Vecteur3d(19.00454, 4.3465, 0);
			poutre.ID = salle.Objet.size();
			poutre.rotation = Vecteur3d();
			poutre.type = FIXE;
			salle.Objet.push_back(new InfoObjet(poutre));

			poutre.cheminModele = "Ressources/Modele/PoutreVerticale.obj";
			poutre.cheminTexture = "Ressources/Texture/PoutreVerticale.png";
			poutre.position = Vecteur3d(23.57122, 4.3465, 0);
			poutre.ID = salle.Objet.size();
			poutre.rotation = Vecteur3d();
			poutre.type = FIXE;
			salle.Objet.push_back(new InfoObjet(poutre));


			InfoObjet remplisseur;
			remplisseur.cheminModele = "Ressources/Modele/Remplisseur.obj";
			remplisseur.cheminTexture = "Ressources/Texture/Remplisseur.png";
			remplisseur.position = Vecteur3d(5.82942, 0, -3.3139);
			remplisseur.ID = salle.Objet.size();
			remplisseur.rotation = Vecteur3d();
			remplisseur.largeur = 17.981;
			remplisseur.type = REMPLISSEUR;
			salle.Objet.push_back(new InfoObjet(remplisseur));

			remplisseur.cheminModele = "Ressources/Modele/Remplisseur.obj";
			remplisseur.cheminTexture = "Ressources/Texture/Remplisseur.png";
			remplisseur.position = Vecteur3d(23.67775, 0, 3.37732);
			remplisseur.ID = salle.Objet.size();
			remplisseur.rotation = Vecteur3d(0, 180, 0);;
			remplisseur.largeur = 17.981;
			remplisseur.type = REMPLISSEUR;
			salle.Objet.push_back(new InfoObjet(remplisseur));

			return true;

		}

		else if (!strcmp(salle.cheminModele, "Ressources/Modele/SalleHexagonale.obj")) {

			InfoObjet pendule;
			pendule.cheminModele = "Ressources/Modele/Pendule.obj";
			pendule.cheminTexture = "Ressources/Texture/Pendule.png";
			pendule.position = Vecteur3d(-6.56341, 4.41787, -0.38614);
			pendule.ID = salle.Objet.size();
			pendule.rotation = Vecteur3d();
			pendule.type = PENDULE;
			salle.Objet.push_back(new InfoObjet(pendule));

			pendule.cheminModele = "Ressources/Modele/Pendule.obj";
			pendule.cheminTexture = "Ressources/Texture/Pendule.png";
			pendule.position = Vecteur3d(-1.31212, 4.41787, -0.38614);
			pendule.ID = salle.Objet.size();
			pendule.rotation = Vecteur3d();
			pendule.type = PENDULE;
			salle.Objet.push_back(new InfoObjet(pendule));

			pendule.cheminModele = "Ressources/Modele/Pendule.obj";
			pendule.cheminTexture = "Ressources/Texture/Pendule.png";
			pendule.position = Vecteur3d(4.03919, 4.41787, -0.38614);
			pendule.ID = salle.Objet.size();
			pendule.rotation = Vecteur3d();
			pendule.type = PENDULE;
			salle.Objet.push_back(new InfoObjet(pendule));

			pendule.cheminModele = "Ressources/Modele/Pendule.obj";
			pendule.cheminTexture = "Ressources/Texture/Pendule.png";
			pendule.position = Vecteur3d(8.60586, 4.41787, -0.38614);
			pendule.ID = salle.Objet.size();
			pendule.rotation = Vecteur3d();
			pendule.type = PENDULE;
			salle.Objet.push_back(new InfoObjet(pendule));


			InfoObjet poutre;
			poutre.cheminModele = "Ressources/Modele/PoutreVerticale.obj";
			poutre.cheminTexture = "Ressources/Texture/PoutreVerticale.png";
			poutre.position = Vecteur3d(-6.56341, 4.41787, -0.28324);
			poutre.ID = salle.Objet.size();
			poutre.rotation = Vecteur3d();
			poutre.type = FIXE;
			salle.Objet.push_back(new InfoObjet(poutre));

			poutre.cheminModele = "Ressources/Modele/PoutreVerticale.obj";
			poutre.cheminTexture = "Ressources/Texture/PoutreVerticale.png";
			poutre.position = Vecteur3d(-1.31212, 4.3465, -0.28324);
			poutre.ID = salle.Objet.size();
			poutre.rotation = Vecteur3d();
			poutre.type = FIXE;
			salle.Objet.push_back(new InfoObjet(poutre));

			poutre.cheminModele = "Ressources/Modele/PoutreVerticale.obj";
			poutre.cheminTexture = "Ressources/Texture/PoutreVerticale.png";
			poutre.position = Vecteur3d(4.03919, 4.3465, -0.28324);
			poutre.ID = salle.Objet.size();
			poutre.rotation = Vecteur3d();
			poutre.type = FIXE;
			salle.Objet.push_back(new InfoObjet(poutre));

			poutre.cheminModele = "Ressources/Modele/PoutreVerticale.obj";
			poutre.cheminTexture = "Ressources/Texture/PoutreVerticale.png";
			poutre.position = Vecteur3d(8.60586, 4.3465, -0.28324);
			poutre.ID = salle.Objet.size();
			poutre.rotation = Vecteur3d();
			poutre.type = FIXE;
			salle.Objet.push_back(new InfoObjet(poutre));


			InfoObjet remplisseur;
			remplisseur.cheminModele = "Ressources/Modele/Remplisseur.obj";
			remplisseur.cheminTexture = "Ressources/Texture/Remplisseur.png";
			remplisseur.position = Vecteur3d(-8.76929, 0, -3.74245);
			remplisseur.ID = salle.Objet.size();
			remplisseur.rotation = Vecteur3d();
			remplisseur.largeur = 22.917;
			remplisseur.type = REMPLISSEUR;
			salle.Objet.push_back(new InfoObjet(remplisseur));

			remplisseur.cheminModele = "Ressources/Modele/Remplisseur.obj";
			remplisseur.cheminTexture = "Ressources/Texture/Remplisseur.png";
			remplisseur.position = Vecteur3d(8.7124, 0, 3.10313);
			remplisseur.ID = salle.Objet.size();
			remplisseur.rotation = Vecteur3d(0, 180, 0);;
			remplisseur.largeur = 22.917;
			remplisseur.type = REMPLISSEUR;
			salle.Objet.push_back(new InfoObjet(remplisseur));

			return true;

		}

		else if (!strcmp(salle.cheminModele, "Ressources/Modele/SalleCegep.obj")) {

			InfoObjet pendule;
			pendule.cheminModele = "Ressources/Modele/Pendule.obj";
			pendule.cheminTexture = "Ressources/Texture/Pendule.png";
			pendule.position = Vecteur3d(0.40152, 4.41787, 51.65161);
			pendule.ID = salle.Objet.size();
			pendule.rotation = Vecteur3d(0, 0, 90);
			pendule.type = PENDULE;
			salle.Objet.push_back(new InfoObjet(pendule));

			pendule.cheminModele = "Ressources/Modele/Pendule.obj";
			pendule.cheminTexture = "Ressources/Texture/Pendule.png";
			pendule.position = Vecteur3d(0.40152, 4.41787, 46.40033);
			pendule.ID = salle.Objet.size();
			pendule.rotation = Vecteur3d(0, 90, 0);
			pendule.type = PENDULE;
			salle.Objet.push_back(new InfoObjet(pendule));

			pendule.cheminModele = "Ressources/Modele/Pendule.obj";
			pendule.cheminTexture = "Ressources/Texture/Pendule.png";
			pendule.position = Vecteur3d(0.40152, 4.41787, 41.04902);
			pendule.ID = salle.Objet.size();
			pendule.rotation = Vecteur3d(0, 90, 0);
			pendule.type = PENDULE;
			salle.Objet.push_back(new InfoObjet(pendule));

			pendule.cheminModele = "Ressources/Modele/Pendule.obj";
			pendule.cheminTexture = "Ressources/Texture/Pendule.png";
			pendule.position = Vecteur3d(0.40152, 4.41787, 36.48234);
			pendule.ID = salle.Objet.size();
			pendule.rotation = Vecteur3d(0, 90, 0);
			pendule.type = PENDULE;
			salle.Objet.push_back(new InfoObjet(pendule));


			InfoObjet poutre;
			poutre.cheminModele = "Ressources/Modele/PoutreVerticale.obj";
			poutre.cheminTexture = "Ressources/Texture/PoutreVerticale.png";
			poutre.position = Vecteur3d(0.50442, 4.34650, 51.65161);
			poutre.ID = salle.Objet.size();
			poutre.rotation = Vecteur3d(0, 90, 0);
			poutre.type = FIXE;
			salle.Objet.push_back(new InfoObjet(poutre));

			poutre.cheminModele = "Ressources/Modele/PoutreVerticale.obj";
			poutre.cheminTexture = "Ressources/Texture/PoutreVerticale.png";
			poutre.position = Vecteur3d(0.50442, 4.34650, 46.40033);
			poutre.ID = salle.Objet.size();
			poutre.rotation = Vecteur3d(0, 90, 0);
			poutre.type = FIXE;
			salle.Objet.push_back(new InfoObjet(poutre));

			poutre.cheminModele = "Ressources/Modele/PoutreVerticale.obj";
			poutre.cheminTexture = "Ressources/Texture/PoutreVerticale.png";
			poutre.position = Vecteur3d(0.50442, 4.34650, 41.04902);
			poutre.ID = salle.Objet.size();
			poutre.rotation = Vecteur3d(0, 90, 0);
			poutre.type = FIXE;
			salle.Objet.push_back(new InfoObjet(poutre));

			poutre.cheminModele = "Ressources/Modele/PoutreVerticale.obj";
			poutre.cheminTexture = "Ressources/Texture/PoutreVerticale.png";
			poutre.position = Vecteur3d(0.50442, 4.34650, 36.48234);
			poutre.ID = salle.Objet.size();
			poutre.rotation = Vecteur3d(0, 90, 0);
			poutre.type = FIXE;
			salle.Objet.push_back(new InfoObjet(poutre));


			InfoObjet remplisseur;
			remplisseur.cheminModele = "Ressources/Modele/Remplisseur.obj";
			remplisseur.cheminTexture = "Ressources/Texture/Remplisseur.png";
			remplisseur.position = Vecteur3d(-2.80044, 0.00000, 54.22414);
			remplisseur.ID = salle.Objet.size();
			remplisseur.rotation = Vecteur3d(0, 90, 0);
			remplisseur.largeur = 17.981;
			remplisseur.type = REMPLISSEUR;
			salle.Objet.push_back(new InfoObjet(remplisseur));

			remplisseur.cheminModele = "Ressources/Modele/Remplisseur.obj";
			remplisseur.cheminTexture = "Ressources/Texture/Remplisseur.png";
			remplisseur.position = Vecteur3d(3.89079, 0.00000, 36.37581);
			remplisseur.ID = salle.Objet.size();
			remplisseur.rotation = Vecteur3d(0, 270, 0);
			remplisseur.largeur = 17.981;
			remplisseur.type = REMPLISSEUR;
			salle.Objet.push_back(new InfoObjet(remplisseur));

			return true;

		}

		else if (!strcmp(salle.cheminModele, "Ressources/Modele/SalleOctogonale.obj")) {

			InfoObjet pendule;
			pendule.cheminModele = "Ressources/Modele/Pendule.obj";
			pendule.cheminTexture = "Ressources/Texture/Pendule.png";
			pendule.position = Vecteur3d(8.39268, 4.41787, -0.10854);
			pendule.ID = salle.Objet.size();
			pendule.rotation = Vecteur3d();
			pendule.type = PENDULE;
			salle.Objet.push_back(new InfoObjet(pendule));

			pendule.cheminModele = "Ressources/Modele/Pendule.obj";
			pendule.cheminTexture = "Ressources/Texture/Pendule.png";
			pendule.position = Vecteur3d(3.82601, 4.41787, -0.10854);
			pendule.ID = salle.Objet.size();
			pendule.rotation = Vecteur3d();
			pendule.type = PENDULE;
			salle.Objet.push_back(new InfoObjet(pendule));

			pendule.cheminModele = "Ressources/Modele/Pendule.obj";
			pendule.cheminTexture = "Ressources/Texture/Pendule.png";
			pendule.position = Vecteur3d(-1.5253, 4.41787, -0.10854);
			pendule.ID = salle.Objet.size();
			pendule.rotation = Vecteur3d();
			pendule.type = PENDULE;
			salle.Objet.push_back(new InfoObjet(pendule));

			pendule.cheminModele = "Ressources/Modele/Pendule.obj";
			pendule.cheminTexture = "Ressources/Texture/Pendule.png";
			pendule.position = Vecteur3d(-6.77659, 4.41787, -0.10854);
			pendule.ID = salle.Objet.size();
			pendule.rotation = Vecteur3d();
			pendule.type = PENDULE;
			salle.Objet.push_back(new InfoObjet(pendule));


			InfoObjet poutre;
			poutre.cheminModele = "Ressources/Modele/PoutreVerticale.obj";
			poutre.cheminTexture = "Ressources/Texture/PoutreVerticale.png";
			poutre.position = Vecteur3d(8.39268, 4.3465, -0.00565);
			poutre.ID = salle.Objet.size();
			poutre.rotation = Vecteur3d();
			poutre.type = FIXE;
			salle.Objet.push_back(new InfoObjet(poutre));

			poutre.cheminModele = "Ressources/Modele/PoutreVerticale.obj";
			poutre.cheminTexture = "Ressources/Texture/PoutreVerticale.png";
			poutre.position = Vecteur3d(3.82601, 4.3465, -0.00565);
			poutre.ID = salle.Objet.size();
			poutre.rotation = Vecteur3d();
			poutre.type = FIXE;
			salle.Objet.push_back(new InfoObjet(poutre));

			poutre.cheminModele = "Ressources/Modele/PoutreVerticale.obj";
			poutre.cheminTexture = "Ressources/Texture/PoutreVerticale.png";
			poutre.position = Vecteur3d(-1.5253, 4.3465, -0.00565);
			poutre.ID = salle.Objet.size();
			poutre.rotation = Vecteur3d();
			poutre.type = FIXE;
			salle.Objet.push_back(new InfoObjet(poutre));

			poutre.cheminModele = "Ressources/Modele/PoutreVerticale.obj";
			poutre.cheminTexture = "Ressources/Texture/PoutreVerticale.png";
			poutre.position = Vecteur3d(-6.77659, 4.3465, -0.00565);
			poutre.ID = salle.Objet.size();
			poutre.rotation = Vecteur3d();
			poutre.type = FIXE;
			salle.Objet.push_back(new InfoObjet(poutre));


			InfoObjet remplisseur;
			remplisseur.cheminModele = "Ressources/Modele/Remplisseur.obj";
			remplisseur.cheminTexture = "Ressources/Texture/Remplisseur.png";
			remplisseur.position = Vecteur3d(-9.34912, 0.00000, -3.31051);
			remplisseur.ID = salle.Objet.size();
			remplisseur.rotation = Vecteur3d();
			remplisseur.largeur = 20.735;
			remplisseur.type = REMPLISSEUR;
			salle.Objet.push_back(new InfoObjet(remplisseur));

			remplisseur.cheminModele = "Ressources/Modele/Remplisseur.obj";
			remplisseur.cheminTexture = "Ressources/Texture/Remplisseur.png";
			remplisseur.position = Vecteur3d(8.49922, 0.00000, 3.38072);
			remplisseur.ID = salle.Objet.size();
			remplisseur.rotation = Vecteur3d(0, 180, 0);;
			remplisseur.largeur = 21.000;
			remplisseur.type = REMPLISSEUR;
			salle.Objet.push_back(new InfoObjet(remplisseur));

			return true;
		}

		else if (!strcmp(salle.cheminModele, "Ressources/Modele/SalleEscalier.obj")) {

			InfoObjet pendule;
			pendule.cheminModele = "Ressources/Modele/Pendule.obj";
			pendule.cheminTexture = "Ressources/Texture/Pendule.png";
			pendule.position = Vecteur3d(8.06997, 3.41787, 0.32109);
			pendule.ID = salle.Objet.size();
			pendule.rotation = Vecteur3d();
			pendule.type = PENDULE;
			salle.Objet.push_back(new InfoObjet(pendule));

			pendule.cheminModele = "Ressources/Modele/Pendule.obj";
			pendule.cheminTexture = "Ressources/Texture/Pendule.png";
			pendule.position = Vecteur3d(3.50330, 3.41787, 0.32108);
			pendule.ID = salle.Objet.size();
			pendule.rotation = Vecteur3d();
			pendule.type = PENDULE;
			salle.Objet.push_back(new InfoObjet(pendule));

			pendule.cheminModele = "Ressources/Modele/Pendule.obj";
			pendule.cheminTexture = "Ressources/Texture/Pendule.png";
			pendule.position = Vecteur3d(-1.84801, 3.41787, 0.32108);
			pendule.ID = salle.Objet.size();
			pendule.rotation = Vecteur3d();
			pendule.type = PENDULE;
			salle.Objet.push_back(new InfoObjet(pendule));

			pendule.cheminModele = "Ressources/Modele/Pendule.obj";
			pendule.cheminTexture = "Ressources/Texture/Pendule.png";
			pendule.position = Vecteur3d(-7.09929, 3.41787, 0.32109);
			pendule.ID = salle.Objet.size();
			pendule.rotation = Vecteur3d();
			pendule.type = PENDULE;
			salle.Objet.push_back(new InfoObjet(pendule));


			InfoObjet poutre;
			poutre.cheminModele = "Ressources/Modele/PoutreVerticale.obj";
			poutre.cheminTexture = "Ressources/Texture/PoutreVerticale.png";
			poutre.position = Vecteur3d(8.06997, 3.34650, 0.42398);
			poutre.ID = salle.Objet.size();
			poutre.rotation = Vecteur3d();
			poutre.type = FIXE;
			salle.Objet.push_back(new InfoObjet(poutre));

			poutre.cheminModele = "Ressources/Modele/PoutreVerticale.obj";
			poutre.cheminTexture = "Ressources/Texture/PoutreVerticale.png";
			poutre.position = Vecteur3d(3.50330, 3.34650, 0.42398);
			poutre.ID = salle.Objet.size();
			poutre.rotation = Vecteur3d();
			poutre.type = FIXE;
			salle.Objet.push_back(new InfoObjet(poutre));

			poutre.cheminModele = "Ressources/Modele/PoutreVerticale.obj";
			poutre.cheminTexture = "Ressources/Texture/PoutreVerticale.png";
			poutre.position = Vecteur3d(-1.84801, 3.34650, 0.42398);
			poutre.ID = salle.Objet.size();
			poutre.rotation = Vecteur3d();
			poutre.type = FIXE;
			salle.Objet.push_back(new InfoObjet(poutre));

			poutre.cheminModele = "Ressources/Modele/PoutreVerticale.obj";
			poutre.cheminTexture = "Ressources/Texture/PoutreVerticale.png";
			poutre.position = Vecteur3d(-7.09929, 3.34650, 0.42398);
			poutre.ID = salle.Objet.size();
			poutre.rotation = Vecteur3d();
			poutre.type = FIXE;
			salle.Objet.push_back(new InfoObjet(poutre));


			InfoObjet remplisseur;
			remplisseur.cheminModele = "Ressources/Modele/Remplisseur.obj";
			remplisseur.cheminTexture = "Ressources/Texture/Remplisseur.png";
			remplisseur.position = Vecteur3d(-9.67182, -1.00000, -2.88087);
			remplisseur.ID = salle.Objet.size();
			remplisseur.rotation = Vecteur3d();
			remplisseur.largeur = 20.000;
			remplisseur.type = REMPLISSEUR;
			salle.Objet.push_back(new InfoObjet(remplisseur));

			remplisseur.cheminModele = "Ressources/Modele/Remplisseur.obj";
			remplisseur.cheminTexture = "Ressources/Texture/Remplisseur.png";
			remplisseur.position = Vecteur3d(8.17651, -1.00000, 3.81035);
			remplisseur.ID = salle.Objet.size();
			remplisseur.rotation = Vecteur3d(0, 180, 0);;
			remplisseur.largeur = 20.000;
			remplisseur.type = REMPLISSEUR;
			salle.Objet.push_back(new InfoObjet(remplisseur));

			return true;
		}
		return false;
	}

	bool plafond(InfoSalle& salle) {

		if (!strcmp(salle.cheminModele, "Ressources/Modele/SalleU.obj")) {

			InfoObjet plafondTueur;
			plafondTueur.cheminModele = "Ressources/Modele/DeathCeiling.obj";
			plafondTueur.cheminTexture = "Ressources/Texture/DeathCeiling.png";
			plafondTueur.position = Vecteur3d(-4.65045, 0.85373, -4.20551);
			plafondTueur.ID = salle.Objet.size();
			plafondTueur.rotation = Vecteur3d();
			plafondTueur.type = PLAFONDTUEUR;
			salle.Objet.push_back(new InfoObjet(plafondTueur));


			InfoObjet remplisseur;
			remplisseur.cheminModele = "Ressources/Modele/Remplisseur.obj";
			remplisseur.cheminTexture = "Ressources/Texture/Remplisseur.png";
			remplisseur.position = Vecteur3d(-13.48986, 0.85373, -9.49320);
			remplisseur.ID = salle.Objet.size();
			remplisseur.rotation = Vecteur3d();
			remplisseur.largeur = 14.014;
			remplisseur.type = REMPLISSEUR;
			salle.Objet.push_back(new InfoObjet(remplisseur));

			remplisseur.cheminModele = "Ressources/Modele/Remplisseur.obj";
			remplisseur.cheminTexture = "Ressources/Texture/Remplisseur.png";
			remplisseur.position = Vecteur3d(4.49040, 0.85373, 0.91105);
			remplisseur.ID = salle.Objet.size();
			remplisseur.rotation = Vecteur3d(0, 180, 0);
			remplisseur.largeur = 13.973;
			remplisseur.type = REMPLISSEUR;
			salle.Objet.push_back(new InfoObjet(remplisseur));

			return true;
		}

		else if (!strcmp(salle.cheminModele, "Ressources/Modele/SalleCegep.obj")) {

			InfoObjet plafondTueur;
			plafondTueur.cheminModele = "Ressources/Modele/DeathCeiling.obj";
			plafondTueur.cheminTexture = "Ressources/Texture/DeathCeiling.png";
			plafondTueur.position = Vecteur3d(52.73269, 12.37467, 12.45685);
			plafondTueur.ID = salle.Objet.size();
			plafondTueur.rotation = Vecteur3d(0, 90, 0);
			plafondTueur.type = PLAFONDTUEUR;
			salle.Objet.push_back(new InfoObjet(plafondTueur));


			InfoObjet remplisseur;
			remplisseur.cheminModele = "Ressources/Modele/Remplisseur.obj";
			remplisseur.cheminTexture = "Ressources/Texture/Remplisseur.png";
			remplisseur.position = Vecteur3d(47.44500, 12.37467, 21.29626);
			remplisseur.ID = salle.Objet.size();
			remplisseur.rotation = Vecteur3d(0, 90, 0);
			remplisseur.largeur = 17.981;
			remplisseur.type = REMPLISSEUR;
			salle.Objet.push_back(new InfoObjet(remplisseur));

			remplisseur.cheminModele = "Ressources/Modele/Remplisseur.obj";
			remplisseur.cheminTexture = "Ressources/Texture/Remplisseur.png";
			remplisseur.position = Vecteur3d(57.84925, 12.37467, 3.31600);
			remplisseur.ID = salle.Objet.size();
			remplisseur.rotation = Vecteur3d(0, 270, 0);
			remplisseur.largeur = 17.981;
			remplisseur.type = REMPLISSEUR;
			salle.Objet.push_back(new InfoObjet(remplisseur));

			return true;
		}

		else if (!strcmp(salle.cheminModele, "Ressources/Modele/SalleEscalier.obj")) {

			InfoObjet plafondTueur;
			plafondTueur.cheminModele = "Ressources/Modele/DeathCeiling.obj";
			plafondTueur.cheminTexture = "Ressources/Texture/DeathCeiling.png";
			plafondTueur.position = Vecteur3d(0.00000, -1.00000, 0.00000);
			plafondTueur.ID = salle.Objet.size();
			plafondTueur.rotation = Vecteur3d();
			plafondTueur.type = PLAFONDTUEUR;
			salle.Objet.push_back(new InfoObjet(plafondTueur));


			InfoObjet remplisseur;
			remplisseur.cheminModele = "Ressources/Modele/Remplisseur.obj";
			remplisseur.cheminTexture = "Ressources/Texture/Remplisseur.png";
			remplisseur.position = Vecteur3d(-8.83941, -1.00000, -5.28769);
			remplisseur.ID = salle.Objet.size();
			remplisseur.rotation = Vecteur3d();
			remplisseur.largeur = 20.581;
			remplisseur.type = REMPLISSEUR;
			salle.Objet.push_back(new InfoObjet(remplisseur));

			remplisseur.cheminModele = "Ressources/Modele/Remplisseur.obj";
			remplisseur.cheminTexture = "Ressources/Texture/Remplisseur.png";
			remplisseur.position = Vecteur3d(9.14085, -1.00000, 5.11656);
			remplisseur.ID = salle.Objet.size();
			remplisseur.rotation = Vecteur3d(0, 180, 0);
			remplisseur.largeur = 20.481;
			remplisseur.type = REMPLISSEUR;
			salle.Objet.push_back(new InfoObjet(remplisseur));

			return true;
		}

		else if (!strcmp(salle.cheminModele, "Ressources/Modele/SalleHexagonale.obj")) {

			InfoObjet plafondTueur;
			plafondTueur.cheminModele = "Ressources/Modele/DeathCeiling.obj";
			plafondTueur.cheminTexture = "Ressources/Texture/DeathCeiling.png";
			plafondTueur.position = Vecteur3d(0.00000, 0.00000, 0.00000);
			plafondTueur.ID = salle.Objet.size();
			plafondTueur.rotation = Vecteur3d();
			plafondTueur.type = PLAFONDTUEUR;
			salle.Objet.push_back(new InfoObjet(plafondTueur));


			InfoObjet remplisseur;
			remplisseur.cheminModele = "Ressources/Modele/Remplisseur.obj";
			remplisseur.cheminTexture = "Ressources/Texture/Remplisseur.png";
			remplisseur.position = Vecteur3d(-8.83941, 0.00000, -5.28769);
			remplisseur.ID = salle.Objet.size();
			remplisseur.rotation = Vecteur3d();
			remplisseur.largeur = 14.098;
			remplisseur.type = REMPLISSEUR;
			salle.Objet.push_back(new InfoObjet(remplisseur));

			remplisseur.cheminModele = "Ressources/Modele/Remplisseur.obj";
			remplisseur.cheminTexture = "Ressources/Texture/Remplisseur.png";
			remplisseur.position = Vecteur3d(9.14085, 0.00000, 5.11656);
			remplisseur.ID = salle.Objet.size();
			remplisseur.rotation = Vecteur3d(0, 180, 0);
			remplisseur.largeur = 14.128;
			remplisseur.type = REMPLISSEUR;
			salle.Objet.push_back(new InfoObjet(remplisseur));

			return true;
		}
		else if (!strcmp(salle.cheminModele, "Ressources/Modele/SalleL.obj")) {

			InfoObjet plafondTueur;
			plafondTueur.cheminModele = "Ressources/Modele/DeathCeiling.obj";
			plafondTueur.cheminTexture = "Ressources/Texture/DeathCeiling.png";
			plafondTueur.position = Vecteur3d(9.06909, 0.00000, -7.32023);
			plafondTueur.ID = salle.Objet.size();
			plafondTueur.rotation = Vecteur3d(0, 90, 0);
			plafondTueur.type = PLAFONDTUEUR;
			salle.Objet.push_back(new InfoObjet(plafondTueur));


			InfoObjet remplisseur;
			remplisseur.cheminModele = "Ressources/Modele/Remplisseur.obj";
			remplisseur.cheminTexture = "Ressources/Texture/Remplisseur.png";
			remplisseur.position = Vecteur3d(3.7814, 0.00000, -0.02792);
			remplisseur.ID = salle.Objet.size();
			remplisseur.rotation = Vecteur3d(0, 90, 0);
			remplisseur.largeur = 17.981;
			remplisseur.type = REMPLISSEUR;
			salle.Objet.push_back(new InfoObjet(remplisseur));

			remplisseur.cheminModele = "Ressources/Modele/Remplisseur.obj";
			remplisseur.cheminTexture = "Ressources/Texture/Remplisseur.png";
			remplisseur.position = Vecteur3d(14.18565, 0.00000, -18.00817);
			remplisseur.ID = salle.Objet.size();
			remplisseur.rotation = Vecteur3d(0, 270, 0);
			remplisseur.largeur = 17.981;
			remplisseur.type = REMPLISSEUR;
			salle.Objet.push_back(new InfoObjet(remplisseur));

			return true;
		}
		else if (!strcmp(salle.cheminModele, "Ressources/Modele/SalleOctogonale.obj")) {

			InfoObjet plafondTueur;
			plafondTueur.cheminModele = "Ressources/Modele/DeathCeiling.obj";
			plafondTueur.cheminTexture = "Ressources/Texture/DeathCeiling.png";
			plafondTueur.position = Vecteur3d(0.00000, 0.00000, 0.00000);
			plafondTueur.ID = salle.Objet.size();
			plafondTueur.rotation = Vecteur3d();
			plafondTueur.type = PLAFONDTUEUR;
			salle.Objet.push_back(new InfoObjet(plafondTueur));


			InfoObjet remplisseur;
			remplisseur.cheminModele = "Ressources/Modele/Remplisseur.obj";
			remplisseur.cheminTexture = "Ressources/Texture/Remplisseur.png";
			remplisseur.position = Vecteur3d(-8.83941, 0.00000, -5.28769);
			remplisseur.ID = salle.Objet.size();
			remplisseur.rotation = Vecteur3d();
			remplisseur.largeur = 14.071;
			remplisseur.type = REMPLISSEUR;
			salle.Objet.push_back(new InfoObjet(remplisseur));

			remplisseur.cheminModele = "Ressources/Modele/Remplisseur.obj";
			remplisseur.cheminTexture = "Ressources/Texture/Remplisseur.png";
			remplisseur.position = Vecteur3d(9.14085, 0.00000, 5.11656);
			remplisseur.ID = salle.Objet.size();
			remplisseur.rotation = Vecteur3d(0, 180, 0);
			remplisseur.largeur = 14.066;
			remplisseur.type = REMPLISSEUR;
			salle.Objet.push_back(new InfoObjet(remplisseur));

			return true;
		}
		return false;
	}
};
