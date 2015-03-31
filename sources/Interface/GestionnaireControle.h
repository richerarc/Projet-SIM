#include <map>
#include <iostream>
#include <fstream>
enum Action {
	AVANCER,RECULER,DROITE,GAUCHE,SAUTER,ACCROUPIR,COURIR,TIRER,UTILISER,INVENTAIRE
};
class GestionnaireControle: public Singleton<GestionnaireControle> {
private:
	std::map<int, int> Controles;

public:
	void lireControle(char* Emplacement) {
		char Evenement[15];
		char Touche[4];
		std::ifstream FichierDeLecture(Emplacement);
		if (FichierDeLecture.is_open()) {
			while (!FichierDeLecture.eof()) {
				FichierDeLecture >> Evenement;
				FichierDeLecture >> Touche;
				int EvenementEnInt = std::atoi(Evenement);
				int ToucheEnInt = std::atoi(Touche);

				switch (EvenementEnInt) {
				case 0:
					Controles[AVANCER] = ToucheEnInt;
					break;
				case 1:
					Controles[RECULER] = ToucheEnInt;
					break;
				case 2:
					Controles[DROITE] = ToucheEnInt;
					break;
				case 3:
					Controles[GAUCHE] = ToucheEnInt;
					break;
				case 4:
					Controles[SAUTER] = ToucheEnInt;
					break;
				case 5:
					Controles[ACCROUPIR] = ToucheEnInt;
					break;
				case 6:
					Controles[COURIR] = ToucheEnInt;
					break;
				case 7:
					Controles[TIRER] = ToucheEnInt;
					break;
				case 8:
					Controles[UTILISER] = ToucheEnInt;
					break;
				case 9:
					Controles[INVENTAIRE] = ToucheEnInt;
					break;
				}
				

					
			}

		}
	}
	void definirControle(Action Evenement, int Controle) {
		Controles[Evenement] = Controle;

		
	}

	void sauvegarderControle(char* Emplacement) {
		std::ofstream EcritureFichier(Emplacement);

		EcritureFichier << "AVANCER" << " " ;
		
		EcritureFichier << Controles[AVANCER] << std::endl;

		EcritureFichier << "RECULER" << " ";
		EcritureFichier << Controles[RECULER] << std::endl;

		EcritureFichier << "DROITE" << " ";
		EcritureFichier << Controles[DROITE] << std::endl;

		EcritureFichier << "GAUCHE" << " ";
		EcritureFichier << Controles[GAUCHE] << std::endl;

		EcritureFichier << "SAUTER" << " ";
		EcritureFichier << Controles[SAUTER] << std::endl;

		EcritureFichier << "ACCROUPIR" << " ";
		EcritureFichier << Controles[ACCROUPIR] << std::endl;

		EcritureFichier << "COURIR" << " ";
		EcritureFichier << Controles[COURIR] << std::endl;

		EcritureFichier << "TIRER" << " ";
		EcritureFichier << Controles[TIRER] << std::endl;

		EcritureFichier << "UTILISER" << " ";
		EcritureFichier << Controles[UTILISER] << std::endl;

		EcritureFichier << "INVENTAIRE" << " ";
		EcritureFichier << Controles[INVENTAIRE] << std::endl;


	}

	std::map<int,int> obtenirControles(void) {
		return Controles;
	}



};