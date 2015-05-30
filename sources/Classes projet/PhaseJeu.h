#pragma once
#include <stack>
#include <list>
#include <math.h>
#include "PhaseMenuPause.h"
#include "Maths.h"
#include "Item.h"
#include "MenuAccesRapide.h"
#include "PhaseMenuInventaire.h"
#include "GestionnaireSucces.h"
#include "UsineItem.h"
#include "PhaseMenuFin.h"
enum niveauDifficulte{ FACILE = 15, NORMAL = 20, HARDCORE = 32 };
class PhaseJeu : public Phase{

private:

	Joueur* joueur;
	gfx::Texte2D* texteUtiliser;
	Objet* objetVise;
	bool toucheRelachee;
	bool retour;
	bool finAnimationDebut, finTransitionSalle, santeEstAffichee;
	unsigned int difficulte;
	std::stack<unsigned int> cheminRecursif;
	std::list<unsigned int> cheminLogique;
	double iterateur_x, iterateur_z;
	Chrono tempsJeu, tempsAffichageID, tempsPhysique;
	gfx::Texte2D* texteChrono;
	gfx::Texte2D* texte_ID_Salle;
	gfx::Texte2D* vie;
	gfx::Texte2D* vieMentale;
	gfx::Texte2D* munitionLugerRestantes;
	gfx::Texte2D* munitionThompsonRestantes;
	gfx::Texte2D* gazRestant;
	double tempsRestant;
	double compteurViePhysique;
	Item *itemEquipe;
	Item *test;
	char dizaine[5];
	char unite[5];
	char chritoa[255];
	MenuAccesRapide* accesRapide;
	gfx::Sprite2D* point;
	gfx::Sprite2D* compteurMunitionLuger;
	gfx::Sprite2D* compteurMunitionThompson;
	gfx::Sprite2D* compteurGaz;

	double exponentielle(double a, double b, double h, double k, double x, int limite){
		double temp = a * pow(M_E, b * (x - h)) + k;
		if (temp < limite){
			return temp;
		}
		return limite;
	}

	void santeMentale(){
		double pourcentagePerdu(0);
		if (cheminRecursif.size() > 1){
			pourcentagePerdu += exponentielle(1, 0.2f, 0, -1, cheminRecursif.size(), 5);
		}
		int idActif = cheminLogique.front();
		std::list<unsigned int>::iterator it = cheminLogique.begin();
		for (++it; it != cheminLogique.end(); ++it){
			if (((*it) == idActif) && ((iterateur_x > 2.5f) || (iterateur_z > 2.5))){
				pourcentagePerdu += exponentielle(1, -0.5f, -3.8f, -1, cheminLogique.size(), 5);
				cheminLogique.erase(cheminLogique.begin(), --it);
				iterateur_x = 0;
				iterateur_z = 0;
				break;
			}
		}
		short santeMentalePrecedente = joueur->obtSanteMentale();
		joueur->defSanteMentale((double)joueur->obtSanteMentale() - ((double)joueur->obtSanteMentale() * (pourcentagePerdu / 100.f)));
		if (((santeMentalePrecedente - joueur->obtSanteMentale()) / santeMentalePrecedente) > 0.02)
			GestionnaireSucces::obtInstance().obtSucces(0);
		if (joueur->obtSanteMentale() <= 60 && santeMentalePrecedente > 60){
			GestionnaireSucces::obtInstance().obtSucces(7);
		}
		if (joueur->obtSanteMentale() <= 25 && santeMentalePrecedente > 25){
			GestionnaireSucces::obtInstance().obtSucces(26);
		}
		if ((joueur->obtSanteMentale() < 25) && !(GestionnaireSucces::obtInstance().obtChronoDeclenche())){
			GestionnaireSucces::obtInstance().obtChronoSanteMentale()->repartir();
			GestionnaireSucces::obtInstance().defChronoDeclenche();
		}
		for (int i = 0; i < joueur->obtInventaire()->obtTailleSacADos(); i++){
			if (joueur->obtInventaire()->obtObjetSacADos(i) != nullptr){
				if (joueur->obtInventaire()->obtObjetSacADos(i)->obtNom() == "Companion"){
					Companion* companion = dynamic_cast<Companion*>(joueur->obtInventaire()->obtObjetSacADos(i));
					companion->changerModele(joueur->obtSanteMentale());
				}
			}
		}
		for (int i = 0; i < joueur->obtInventaire()->obtTailleAccesRapide(); i++){
			if (joueur->obtInventaire()->obtObjetAccesRapide(i) != nullptr){
				if (joueur->obtInventaire()->obtObjetAccesRapide(i)->obtNom() == "Companion"){
					Companion* companion = dynamic_cast<Companion*>(joueur->obtInventaire()->obtObjetAccesRapide(i));
					companion->changerModele(joueur->obtSanteMentale());
				}
			}
		}
	}

	void mettreAJourtexteChrono(){
		std::string stringTexteChrono;
		stringTexteChrono = "";
		int heures, minutes, secondes;
		heures = (int)(tempsRestant / 3600);
		minutes = (int)(tempsRestant / 60) % 60;
		secondes = (int)tempsRestant % 60;

		if (secondes < 0)
			secondes = 0;

		if (heures >= 10){
			stringTexteChrono.append(SDL_itoa(heures, chritoa, 10));
		}
		else{
			stringTexteChrono.append("0");
			stringTexteChrono.append(SDL_itoa(heures, chritoa, 10));
		}
		stringTexteChrono.append(":");
		if (minutes >= 10){
			stringTexteChrono.append(SDL_itoa(minutes, chritoa, 10));
		}
		else{
			stringTexteChrono.append("0");
			stringTexteChrono.append(SDL_itoa(minutes, chritoa, 10));
		}
		stringTexteChrono.append(":");
		if (secondes >= 10){
			stringTexteChrono.append(SDL_itoa(secondes, chritoa, 10));
		}
		else{
			stringTexteChrono.append("0");
			stringTexteChrono.append(SDL_itoa(secondes, chritoa, 10));
		}
		texteChrono->defTexte(&stringTexteChrono);
	}

	void mettreAJourTextesSante(){
		std::string nouvVie = "Health: ";
		std::string nouvVieMentale = "Sanity: ";
		nouvVie.append(SDL_itoa(joueur->obtSantePhysique(), chritoa, 10));
		nouvVieMentale.append(SDL_itoa(joueur->obtSanteMentale(), chritoa, 10));
		vie->defTexte(&nouvVie);
		vieMentale->defTexte(&nouvVieMentale);
	}

	void mettreAJourGazRestant(short gaz){
		std::string str;
		str = SDL_itoa(gaz, chritoa, 10);
		str.append(" %");
		gazRestant->defTexte(&str);
	}
	void mettreAJourMunitionRestant(short munition, short chargeur){
		std::string str;
		str = SDL_itoa(munition, chritoa, 10);
		str.append("/");
		str.append(SDL_itoa(chargeur, chritoa, 10));
		chargeur == 8 ? munitionLugerRestantes->defTexte(&str) : munitionThompsonRestantes->defTexte(&str);
	}

	void appliquerPhysique(float frameTime) {
		if (joueur->obtVitesse().norme() != 0) {
			if (joueur->obtNormale().y != 1) {
				Physique::obtInstance().appliquerGravite(joueur->obtVitesse(), frameTime);
			}
			//if (joueur->obtNormaleMur().y == 0. && (joueur->obtNormaleMur().x != 0. || joueur->obtNormaleMur().z != 0.)){
			//	joueur->longer();
			//}
			joueur->defPosition(joueur->obtPosition() + joueur->obtVitesse() * frameTime);
			iterateur_x += joueur->obtVitesse().x * frameTime;
			iterateur_z += joueur->obtVitesse().z * frameTime;
			Physique::obtInstance().collisionJoueurSalle(Carte::obtInstance().salleActive->obtModele(), joueur);
			Physique::obtInstance().collisionJoueurObjet(joueur, Carte::obtInstance().salleActive->obtListeObjet());
		}
		Physique::obtInstance().appliquerPhysiqueSurListeObjet(Carte::obtInstance().salleActive->obtModele(), Carte::obtInstance().salleActive->obtListeObjet(), frameTime, tempsPhysique.obtTempsEcoule().enSecondes());
	}

	bool detectionObjet() {

		std::list<Objet*> liste = Carte::obtInstance().salleActive->obtListeObjet();
		bool objetDetecte = false;

		for (auto it : liste) {
			Porte* it_Porte = dynamic_cast<Porte*>(it);
			Item* it_Item = dynamic_cast<Item*>(it);
			Commutateur* it_com = dynamic_cast<Commutateur*>(it);
			ObjetFixe* it_fixe = dynamic_cast<ObjetFixe*>(it);
			if(it_Porte || !it_fixe){
				Vecteur3d pointCollision, normale;
				Droite VueJoueur = Droite(joueur->obtPosition() + (Vecteur3d(0.0, joueur->obtModele3D()->obtModele()->obtTaille().y, 0.0)), joueur->obtDevant());
				if ((Maths::distanceEntreDeuxPoints(joueur->obtPosition(), it->obtPosition()) < 2) && Physique::obtInstance().collisionDroiteModele(it->obtModele3D(), VueJoueur, pointCollision, normale, nullptr, false)) {

					std::string str1 = "Press ";
					str1.append(*GestionnaireControle::obtInstance().obtTouche((UTILISER)));
					
					if (it_Porte != nullptr){
						if (it_Porte->obtVerrouillee())
							str1.append(" to unlock door.");
						else
							str1.append(" to open door.");
					}

					else if (it_Item != nullptr){
						str1.append(" to pick up ");
						str1.append(it_Item->obtNom());
					}
					else if (it_com != nullptr){
						if (it_com->obtEtat())
							str1.append(" to turn off");
						else
							str1.append(" to turn on");
					}
					texteUtiliser->defTexte(&str1);
					gfx::Gestionnaire2D::obtInstance().ajouterObjet(texteUtiliser);
					objetDetecte = true;
					objetVise = it;
				}
			}
		}
		if (!objetDetecte)
			gfx::Gestionnaire2D::obtInstance().retObjet(texteUtiliser);
		return objetDetecte;
	}

public:

	PhaseJeu(Vecteur3d positionJoueur, double hAngle, double vAngle) : Phase(){

		difficulte = Carte::obtInstance().nombreDeSalle;

		joueur = new Joueur(positionJoueur, hAngle, vAngle);
		joueur->defEtat(CHUTE);
		joueur->ajouterScene();

		test = UsineItem::obtInstance().obtItemParType(40, 0);
		joueur->obtInventaire()->ajouterObjet(test);
		joueur->obtInventaire()->ajouterObjet(UsineItem::obtInstance().obtItemParType(50, 0));
		joueur->obtInventaire()->ajouterObjet(UsineItem::obtInstance().obtItemParType(10, 0));
		joueur->obtInventaire()->ajouterObjet(UsineItem::obtInstance().obtItemParType(61, 0));
		accesRapide = new MenuAccesRapide(joueur->obtInventaire());
		accesRapide->remplir();

		GestionnairePhases::obtInstance().ajouterPhase(new PhaseMenuInventaire(joueur->obtInventaire()));
		GestionnaireEvenements::obtInstance().ajouterUnRappel(SDL_KEYDOWN, std::bind(&PhaseJeu::toucheAppuyee, this, std::placeholders::_1));
		GestionnaireEvenements::obtInstance().ajouterUnRappel(SDL_CONTROLLERBUTTONDOWN, std::bind(&PhaseJeu::toucheAppuyee, this, std::placeholders::_1));

		texteUtiliser = new gfx::Texte2D(new std::string(""), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("Ressources/Font/arial.ttf", 20), Vecteur2f(300, 200));
		texte_ID_Salle = new gfx::Texte2D(new std::string(""), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("Ressources/Font/arial.ttf", 60), Vecteur2f(70, 50));
		texteChrono = new gfx::Texte2D(new std::string(""), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("Ressources/Font/arial.ttf", 40), Vecteur2f(RESOLUTION_DEFAUT_X / 2 - 40, 670));
		vie = new gfx::Texte2D(new std::string(""), { 255, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("Ressources/Font/arial.ttf", 23), Vecteur2f(200, 10));
		vieMentale = new gfx::Texte2D(new std::string(""), { 0, 0, 255, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("Ressources/Font/arial.ttf", 23), Vecteur2f(350, 10));
		gazRestant = new gfx::Texte2D(new std::string("0%"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("Ressources/Font/arial.ttf", 25), Vecteur2f(45, 10));
		point = new gfx::Sprite2D(Vecteur2f(638, 358), gfx::GestionnaireRessources().obtTexture("Ressources/Texture/point.png"));
		compteurGaz = new gfx::Sprite2D(Vecteur2f(15, 10), gfx::GestionnaireRessources().obtTexture("Ressources/Texture/cartoucheGazIcone.png"));
		munitionLugerRestantes = new gfx::Texte2D(new std::string("0/8"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("Ressources/Font/arial.ttf", 25), Vecteur2f(45, 42));
		munitionThompsonRestantes = new gfx::Texte2D(new std::string("0/20"), { 0, 0, 0, 255 }, gfx::GestionnaireRessources::obtInstance().obtPolice("Ressources/Font/arial.ttf", 25), Vecteur2f(45, 74));
		compteurMunitionLuger = new gfx::Sprite2D(Vecteur2f(15, 42), gfx::GestionnaireRessources().obtTexture("Ressources/Texture/PARABELLUMIcone32.png"));
		compteurMunitionThompson = new gfx::Sprite2D(Vecteur2f(15, 74), gfx::GestionnaireRessources().obtTexture("Ressources/Texture/ACP45Icone32.png"));
		mettreAJourTextesSante();
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(vie);
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(vieMentale);
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(gazRestant);
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(munitionLugerRestantes);
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(munitionThompsonRestantes);
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(point);
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(compteurGaz);
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(compteurMunitionLuger);
		gfx::Gestionnaire2D::obtInstance().ajouterObjet(compteurMunitionThompson);

		std::string str = SDL_uitoa(Carte::obtInstance().salleActive->obtID(), chritoa, 10);
		texte_ID_Salle->defTexte(&str);

		toucheRelachee = false;
		retour = false;
		pause = false;
		finAnimationDebut = false;
		finTransitionSalle = true;
		santeEstAffichee = true;
		compteurViePhysique = 0;

		cheminRecursif.push(Carte::obtInstance().salleActive->obtID());
		cheminLogique.push_back(Carte::obtInstance().salleActive->obtID());
		iterateur_x = 0;
		iterateur_z = 0;
		itemEquipe = nullptr;

		for (int i = 0; i < 4; ++i){
			unite[i] = '\0';
			dizaine[i] = '\0';
		}

		switch (difficulte)
		{
		case FACILE:
			tempsRestant = 2700;
			break;
		case NORMAL:
			tempsRestant = 1800;
			break;
		case HARDCORE:
			tempsRestant = 900;
			joueur->defSanteMentale(50);
			joueur->defSantePhysique(50);
			break;
		}

		mettreAJourtexteChrono();
		tempsJeu = Chrono();
		tempsAffichageID = Chrono();
		tempsPhysique = Chrono();
	}

	~PhaseJeu(){
		delete joueur;
		delete texteUtiliser;
		delete point;
		delete accesRapide;
		delete texteChrono;
		delete texte_ID_Salle;
		delete vie;
		delete vieMentale;
	}

	void rafraichir(float frameTime) {
		if (salleActive != nullptr)
			if (salleActive->obtID() == difficulte + 2)
				GestionnaireSucces::obtInstance().verifierPacifisme();
		GestionnaireSucces::obtInstance().obtSucces(2);
		if (pause)
			return;
		// Il vas falloir creer un bouton dans le gestionnaire de controles pour ça...
		if ((Clavier::toucheAppuyee(SDLK_q)) || Manette::boutonAppuyer(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)){
			if (itemEquipe != nullptr){
				itemEquipe->defEtat(EtatItem::DEPOSE);
				GestionnaireSucces::obtInstance().defItemOuiNonLache(joueur->obtInventaire()->obtObjetAccesRapide(joueur->obtInventaire()->obtItemSelectionne()));
				joueur->obtInventaire()->retirerObjetAccesRapide(joueur->obtInventaire()->obtItemSelectionne());
				GestionnaireSucces::obtInstance().defNbrItems(GestionnaireSucces::obtInstance().obtNbrItems() - 1);
				itemEquipe = nullptr;
			}
		}
		if (!this->pause) {
			if (Carte::obtInstance().salleActive->obtID() == (Carte::obtInstance().nombreDeSalle + 2)){
				Carte::obtInstance().salleActive->obtObjet(0)->defPosition(joueur->obtPosition());
				Carte::obtInstance().salleActive->obtObjet(0)->defCollisionInterne(true);
				GestionnaireSucces::obtInstance().obtSucces(12);
			}
			joueur->deplacement();
			appliquerPhysique(frameTime);
			joueur->obtInventaire()->actualiser();
			itemEquipe = joueur->obtInventaire()->obtObjetAccesRapide(joueur->obtInventaire()->obtItemSelectionne());
			if (itemEquipe != nullptr){
				Item* itemPrecedent = itemEquipe;
				short typePrecedent = itemPrecedent->obtType();
				itemEquipe->actualiser(Carte::obtInstance().salleActive, joueur, frameTime);
				if (itemPrecedent->obtType() > 29 && itemPrecedent->obtType() < 50 && itemPrecedent->obtEtat() == DEPOSE)
					GestionnaireSucces::obtInstance().defNbrItems(GestionnaireSucces::obtInstance().obtNbrItems() - 1);
				if (typePrecedent == 37 && itemPrecedent->obtEtat() == -17891602)//touchez pas à ça
					GestionnaireSucces::obtInstance().obtSucces(9);
			}
			accesRapide->actualiserAffichage();
			ControlleurAudio::obtInstance().jouer(COEUR, joueur);
			ControlleurAudio::obtInstance().jouer(PAS, joueur);
			detectionObjet();
			ControlleurAudio::obtInstance().jouerTout(joueur);

			// On regarde si les animation de début et de transisiton de salle sont fini pour ajouter les textes a afficher.
			if (!Carte::obtInstance().animationTransitionSalle(joueur, frameTime) && !finTransitionSalle){
				std::string str = SDL_uitoa(Carte::obtInstance().salleActive->obtID(), chritoa, 10);
				texte_ID_Salle->defTexte(&str);
				gfx::Gestionnaire2D::obtInstance().ajouterObjet(texte_ID_Salle);
				tempsAffichageID.repartir();
				finTransitionSalle = true;
			}

			if (!Carte::obtInstance().animationLeverLit(joueur, frameTime) && !finAnimationDebut){
				gfx::Gestionnaire2D::obtInstance().ajouterObjet(texte_ID_Salle);
				gfx::Gestionnaire2D().obtInstance().ajouterObjet(texteChrono);
				tempsAffichageID.repartir();
				finAnimationDebut = true;
			}

			if (tempsAffichageID.obtTempsEcoule().enSecondes() >= 4.0){
				gfx::Gestionnaire2D::obtInstance().retObjet(texte_ID_Salle);
				tempsAffichageID.repartir();
			}

			if (Carte::obtInstance().salleActive->obtID() != difficulte){
				if (difficulte != FACILE && santeEstAffichee){
					gfx::Gestionnaire2D::obtInstance().retObjet(vie);
					gfx::Gestionnaire2D::obtInstance().retObjet(vieMentale);
					santeEstAffichee = false;
				}
				else
					mettreAJourTextesSante();
				Item* masqueTmp = joueur->obtInventaire()->obtItemParType(50);
				if (masqueTmp != nullptr){
					MasqueGaz* masque = dynamic_cast<MasqueGaz*>(masqueTmp);
					if (masque->estEquipe())
						tempsRestant -= tempsJeu.obtTempsEcoule().enSecondes() * (100. - masque->obtDurabilite()) / 100;
					else
						tempsRestant -= tempsJeu.obtTempsEcoule().enSecondes();
				}
				else
					tempsRestant -= tempsJeu.obtTempsEcoule().enSecondes();
				compteurViePhysique += tempsJeu.obtTempsEcoule().enSecondes();
				if (compteurViePhysique >= 1){
					compteurViePhysique = 0;
					Item* itemTmp = joueur->obtInventaire()->obtItemParType(50);
					if (itemTmp != nullptr){
						MasqueGaz* tmp = dynamic_cast<MasqueGaz*>(itemTmp);
						if (tmp != nullptr){
							if (tmp->estEquipe()){
								tmp->user();
								mettreAJourGazRestant(tmp->obtDurabilite());
							}
						}
						else
							mettreAJourGazRestant(0);
					}
				}
				Item* itemTmp = joueur->obtInventaire()->obtItemParType(10);
				if (itemTmp != nullptr){
					Fusil* tmp = dynamic_cast<Fusil*>(itemTmp);
					mettreAJourMunitionRestant(tmp->obtballesRestantes(), tmp->obtChargeur());
				}
				else
					mettreAJourMunitionRestant(0, 8);
				itemTmp = joueur->obtInventaire()->obtItemParType(11);
				if (itemTmp != nullptr){
					Fusil* tmp = dynamic_cast<Fusil*>(itemTmp);
					mettreAJourMunitionRestant(tmp->obtballesRestantes(), tmp->obtChargeur());
				}
				else
					mettreAJourMunitionRestant(0, 20);
				if (joueur->obtSantePhysique() <= 0)
					GestionnaireSucces::obtInstance().obtSucces(14);
				mettreAJourtexteChrono();

				if (tempsRestant <= 0) {
					gfx::Gestionnaire2D::obtInstance().vider();
					GestionnairePhases::obtInstance().obtPhaseActive()->defPause(true);
					PhaseMenuFin* tmp = (dynamic_cast<PhaseMenuFin*>(GestionnairePhases::obtInstance().obtPhase(8)));
					if (tmp != nullptr)
						tmp->defPerdu(true);
					GestionnairePhases::obtInstance().retirerPhase();
					GestionnairePhases::obtInstance().defPhaseActive(MENUFIN);
					GestionnairePhases::obtInstance().obtPhaseActive()->defPause(false);
					GestionnairePhases::obtInstance().obtPhaseActive()->remplir();
					curseur->remplir();
					gfx::Gestionnaire3D::obtInstance().vider();
					return;
				}
			}
			tempsJeu.repartir();
		}
		if (tempsRestant > 0) {
			if (detectionObjet()){
				if ((Clavier::toucheRelachee(GestionnaireControle::obtInstance().touche(UTILISER)) && Manette::boutonRelacher(SDL_CONTROLLER_BUTTON_Y)) && toucheRelachee){
					if (objetVise->obtSiPorte()){
						if (!(dynamic_cast<Porte*>(objetVise))->obtVerrouillee()){
							if (Carte::obtInstance().salleActive->obtID() == Carte::obtInstance().nombreDeSalle + 1){
								if (objetVise->obtID()){
									Commutateur* com = nullptr;
									for (auto it : Carte::obtInstance().salleActive->obtListeObjet()){
										com = dynamic_cast<Commutateur*>(it);
										if (com){
											if (com->obtID() < 15){
												dizaine[com->obtID() - 11] = com->obtEtat() + 48;
											}
											else{
												dizaine[4] = '\0';
												unite[com->obtID() - 15] = com->obtEtat() + 48;
											}
										}
									}
									unite[4] = '\0';
									short diz, uni;
									diz = strtoull(dizaine, NULL, 2);
									uni = strtoull(unite, NULL, 2);
									Carte::obtInstance().ajouterLien(std::make_tuple(Carte::obtInstance().salleActive->obtID(), objetVise->obtID(), false), std::make_tuple(diz * 10 + uni, 0));
								}
							}
							Carte::obtInstance().destination(std::make_tuple(Carte::obtInstance().salleActive->obtID(), objetVise->obtID(), false), joueur);
							if (Carte::obtInstance().salleActive->obtID() != cheminRecursif.top()){
								for (int i = 0; i < cheminRecursif.size(); ++i)
									cheminRecursif.pop();
							}
							cheminRecursif.push(Carte::obtInstance().salleActive->obtID());
							cheminLogique.push_front(Carte::obtInstance().salleActive->obtID());
							santeMentale();
							finTransitionSalle = false;
						}
						else{ //a ajouter: verification si le joeueur a une cle
							(dynamic_cast<Porte*>(objetVise))->defVerrouillee(false);
						}
					}
					else if (dynamic_cast<Item*>(objetVise)){
						joueur->obtInventaire()->ajouterObjet((Item*)objetVise);
						GestionnaireSucces::obtInstance().defNbrItems(GestionnaireSucces::obtInstance().obtNbrItems() + 1);
						char* nom = dynamic_cast<Item*>(objetVise)->obtNom();
						GestionnaireSucces::obtInstance().verifierOuiNon((Item*)objetVise);
						GestionnaireSucces::obtInstance().obtSucces(1);
						if (nom == "Water bottle")
							GestionnaireSucces::obtInstance().obtSucces(18);
						if (nom == "HolyRod")
							GestionnaireSucces::obtInstance().obtSucces(17);
						if (nom == "Luger P08" || nom == "Thompson M1"){
							GestionnaireSucces::obtInstance().obtSucces(8);
							GestionnaireSucces::obtInstance().defPacifisme(false);
						}
						if (nom == "Grenade")
							GestionnaireSucces::obtInstance().obtSucces(9);
						if (nom == "Note")
							GestionnaireSucces::obtInstance().obtSucces(13);
						if (nom == "Corrections")
							GestionnaireSucces::obtInstance().obtSucces(24);
						if (nom == "Felix's thai box")
							GestionnaireSucces::obtInstance().obtSucces(21);
						if (nom == "Chicken drumstick")
							GestionnaireSucces::obtInstance().obtSucces(25);
						if (nom == "Companion")
							GestionnaireSucces::obtInstance().obtSucces(11);
						if (nom == "Exam")
							GestionnaireSucces::obtInstance().obtSucces(24);
						objetVise = nullptr;
					}
					else if (dynamic_cast<Commutateur*>(objetVise)){
						dynamic_cast<Commutateur*>(objetVise)->actioner();
					}
					toucheRelachee = false;
				}
				if ((Clavier::toucheAppuyee(GestionnaireControle::obtInstance().touche(UTILISER)) || Manette::boutonAppuyer(SDL_CONTROLLER_BUTTON_Y)))
					toucheRelachee = true;
			}
		}
		if ((GestionnaireSucces::obtInstance().obtChronoDeclenche()) && (GestionnaireSucces::obtInstance().obtChronoSanteMentale()->obtTempsEcoule().enMillisecondes() > 120000)){
			GestionnaireSucces::obtInstance().obtSucces(3);
		}
		if ((GestionnaireSucces::obtInstance().obtChronoDeclenche()) && (GestionnaireSucces::obtInstance().obtChronoSanteMentale()->obtTempsEcoule().enMillisecondes() > 180000)){
			GestionnaireSucces::obtInstance().obtSucces(4);
		}
		if ((GestionnaireSucces::obtInstance().obtChronoDeclenche()) && (GestionnaireSucces::obtInstance().obtChronoSanteMentale()->obtTempsEcoule().enMillisecondes() > 240000)){
			GestionnaireSucces::obtInstance().obtSucces(5);
		}
		if ((GestionnaireSucces::obtInstance().obtChronoDeclenche()) && (GestionnaireSucces::obtInstance().obtChronoSanteMentale()->obtTempsEcoule().enMillisecondes() > 300000)){
			GestionnaireSucces::obtInstance().obtSucces(6);
		}
	}

	void toucheAppuyee(SDL_Event &event){
		if (pause)
			return;
		if (retour){
			retour = false;
			return;
		}
		if ((event.key.keysym.sym == SDLK_ESCAPE) || Manette::boutonAppuyer(SDL_CONTROLLER_BUTTON_START)) {
			defPause(true);
			gfx::Gestionnaire3D::obtInstance().obtCamera()->bloquer();
			GestionnairePhases::obtInstance().defPhaseActive(MENUPAUSE);
			GestionnairePhases::obtInstance().obtPhaseActive()->defPause(false);
			GestionnairePhases::obtInstance().obtPhaseActive()->remplir();
			Curseur::defPosition(Vecteur2f(fenetre->obtTaille().x / 2, fenetre->obtTaille().y / 2));
			curseur->remplir();
		}
		if ((event.key.keysym.sym == SDLK_TAB) || Manette::boutonAppuyer(SDL_CONTROLLER_BUTTON_BACK)) {
			defPause(true);
			gfx::Gestionnaire3D::obtInstance().obtCamera()->bloquer();
			GestionnairePhases::obtInstance().defPhaseActive(MENUINVENTAIRE);
			GestionnairePhases::obtInstance().obtPhaseActive()->defPause(false);
			GestionnairePhases::obtInstance().obtPhaseActive()->remplir();
			Curseur::defPosition(Vecteur2f(fenetre->obtTaille().x / 2, fenetre->obtTaille().y / 2));
			curseur->remplir();
			accesRapide->vider();
		}
	}

	void remplir() {
		accesRapide->remplir();
	}

	void defPause(bool pause) {
		if (!pause){
			retour = true;
			gfx::Gestionnaire2D().obtInstance().ajouterObjet(texteChrono);
			gfx::Gestionnaire2D().obtInstance().ajouterObjet(point);
			gfx::Gestionnaire2D::obtInstance().ajouterObjet(vie);
			gfx::Gestionnaire2D::obtInstance().ajouterObjet(vieMentale);
			gfx::Gestionnaire2D::obtInstance().ajouterObjet(gazRestant);
			gfx::Gestionnaire2D::obtInstance().ajouterObjet(munitionLugerRestantes);
			gfx::Gestionnaire2D::obtInstance().ajouterObjet(munitionThompsonRestantes);
			gfx::Gestionnaire2D::obtInstance().ajouterObjet(compteurGaz);
			gfx::Gestionnaire2D::obtInstance().ajouterObjet(compteurMunitionLuger);
			gfx::Gestionnaire2D::obtInstance().ajouterObjet(compteurMunitionThompson);
		}
		this->pause = pause;
	}

	void actualiserEchelle(Vecteur2f vecteurEchelle) {
	}

	float obtTemps() {
		return tempsJeu.obtTempsEcoule().enSecondes();
	}

	double obtTempsRestant(void) {
		return tempsRestant;
	}

};

