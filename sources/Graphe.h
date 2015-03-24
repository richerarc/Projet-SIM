namespace graphe{
	int arbrePont1a[1][1] = {3};
	int arbrePont1b[1][1] = {1};
	int arbrePont1c[1][1] = {0};
	int arbrePont2a[2][2] = {0, 1,
							 1, 1};
	int arbrePont2b[2][2] = {0, 1,
							 1, 0};
	int arbrePont2c[2][2] = {0, 1,
							 0, 0};
	int arbrePont3a[3][3] = {0, 1, 1,
							 0, 0, 1,
							 1, 0, 0};
	int arbrePont3b[3][3] = {0, 1, 0,
							 0, 0, 1,
							 1, 0, 0};
	int arbrePont3c[3][3] = {0, 0, 0,
							 1, 0, 0,
							 1, 0, 0};
	int arbrePont4a[4][4] = {0, 1, 1, 0,
							 1, 1, 0, 1,
							 1, 0, 0, 1,
							 0, 1, 1, 0};
	int arbrePont4b[4][4] = {0, 0, 1, 1,
							 0, 0, 0, 1,
							 0, 0, 0, 1,
							 1, 1, 0, 0};
	int arbrePont4c[4][4] = {0, 0, 0, 1,
							 0, 0, 1, 0,
							 1, 0, 0, 0,
							 0, 1, 0, 0};
	int arbrePont5a[5][5] = {0, 1, 1, 1, 0,
							 1, 0, 1, 0, 1,
							 0, 0, 0, 0, 1,
							 1, 0, 1, 0, 1,
							 0, 1, 0, 1, 0};
	int arbrePont5b[5][5] = {0, 0, 1, 1, 1,
							 0, 1, 1, 0, 0,
							 0, 1, 0, 0, 1,
							 1, 0, 0, 0, 1,
							 0, 0, 0, 1, 0};
	int arbrePont5c[5][5] = {0, 1, 0, 0, 0,
							 0, 0, 1, 0, 0,
							 1, 0, 0, 1, 0,
							 0, 0, 0, 0, 1,
							 0, 0, 1, 0, 0};
	int* arbresPonts[15] = {arbrePont1a[0], arbrePont1b[0], arbrePont1c[0], arbrePont2a[0], arbrePont2b[0], arbrePont2c[0], arbrePont3a[0], arbrePont3b[0], arbrePont3c[0], arbrePont4a[0], arbrePont4b[0], arbrePont4c[0], arbrePont5a[0], arbrePont5b[0], arbrePont5c[0] };
	
	class Graphe {
	private:
		int* sommetsMarques;
		int sommetsArbres[4];
		int itterateur;
		double ratio;
		
		int obtIndiceAleatoire(){
			int indice;
			for (int i = 0; i < nombreSommet; i++) {
				indice = obtIndiceAleatoire();
				if (sommetsMarques[indice] < 8)
					return indice;
			}
			return -1;
		}
		
		int obtIndiceAleatoireNonMarque(){
			int indice;
			for (int i = 0; i < nombreSommet; i++) {
				indice = obtIndiceAleatoire();
				if (sommetsMarques[indice] == 0)
					return indice;
			}
			return -1;  // erreur aucun indice non marqué
		}
		
		void creerArbre(int indice, int niveau, int nbrSommetParArbre){
			if (!niveau)
				sommetsArbres[itterateur] = indice;
			sommetsMarques[indice]++;
			int indiceTemp = obtIndiceAleatoireNonMarque();
			sommetsMarques[indiceTemp]++;
			matrice[(indice * nombreSommet) + indiceTemp]++;
			matrice[(indiceTemp * nombreSommet) + indice]++;
			if (++niveau < nbrSommetParArbre){
				if ((sommetsMarques[indice] >= 4) || (rand() %2)){
					creerArbre(indiceTemp, niveau, nbrSommetParArbre);
				}
				else{
					creerArbre(indice, niveau, nbrSommetParArbre);
				}
			}
			sommetsArbres[itterateur + 2] = indice;
		}
		
		void ajouterPont(){
			int sommetsRestant(0);
			for (int i = 0; i < nombreSommet; i++){
				if (!sommetsMarques[i]) sommetsRestant++;
			}
			// pont 1
			bool assigner(true);
			int* sommet = nullptr;
			int aleatoire = rand() % 15;
			switch (aleatoire) {
				case 14: case 13: case 12:
					if (!sommet){
						sommetsRestant -= 5;
						sommet = new int[5]();
						for (int i = 0; i < 5; i++) {
							sommet[i] = obtIndiceAleatoireNonMarque();
						}
					}
					if (assigner){
						matrice[(sommetsArbres[3] * nombreSommet) + sommet[4]]++; // connection arbre->pont
						assigner = false;
						sommetsMarques[sommet[4]]++;
					}
					matrice[sommet[0] * nombreSommet + sommet[4]] += (arbresPonts[aleatoire])[4];
					matrice[sommet[1] * nombreSommet + sommet[4]] += (arbresPonts[aleatoire])[9];
					matrice[sommet[2] * nombreSommet + sommet[4]] += (arbresPonts[aleatoire])[14];
					matrice[sommet[3] * nombreSommet + sommet[4]] += (arbresPonts[aleatoire])[19];
					matrice[sommet[4] * nombreSommet + sommet[4]] += (arbresPonts[aleatoire])[24];
					matrice[sommet[4] * nombreSommet + sommet[0]] += (arbresPonts[aleatoire])[20];
					matrice[sommet[4] * nombreSommet + sommet[1]] += (arbresPonts[aleatoire])[21];
					matrice[sommet[4] * nombreSommet + sommet[2]] += (arbresPonts[aleatoire])[22];
					matrice[sommet[4] * nombreSommet + sommet[3]] += (arbresPonts[aleatoire])[23];

				case 11: case 10: case 9:
					if (!sommet){
						sommetsRestant -= 4;
						sommet = new int[4]();
						for (int i = 0; i < 4; i++) {
							sommet[i] = obtIndiceAleatoireNonMarque();
						}
					}
					if (assigner){
						matrice[(sommetsArbres[3] * nombreSommet) + sommet[3]]++; // connection arbre->pont
						assigner = false;
						sommetsMarques[sommet[3]]++;
					}
					matrice[sommet[0] * nombreSommet + sommet[3]] += (arbresPonts[aleatoire])[3];
					matrice[sommet[1] * nombreSommet + sommet[3]] += (arbresPonts[aleatoire])[8];
					matrice[sommet[2] * nombreSommet + sommet[3]] += (arbresPonts[aleatoire])[13];
					matrice[sommet[3] * nombreSommet + sommet[3]] += (arbresPonts[aleatoire])[18];
					matrice[sommet[3] * nombreSommet + sommet[0]] += (arbresPonts[aleatoire])[15];
					matrice[sommet[3] * nombreSommet + sommet[1]] += (arbresPonts[aleatoire])[16];
					matrice[sommet[3] * nombreSommet + sommet[2]] += (arbresPonts[aleatoire])[17];
					
				case 8: case 7: case 6:
					if (!sommet){
						sommetsRestant -= 3;
						sommet = new int[3]();
						for (int i = 0; i < 3; i++) {
							sommet[i] = obtIndiceAleatoireNonMarque();
						}
					}
					if (assigner){
						matrice[(sommetsArbres[3] * nombreSommet) + sommet[2]]++; // connection arbre->pont
						assigner = false;
						sommetsMarques[sommet[2]]++;
					}
					matrice[sommet[0] * nombreSommet + sommet[2]] += (arbresPonts[aleatoire])[2];
					matrice[sommet[1] * nombreSommet + sommet[2]] += (arbresPonts[aleatoire])[7];
					matrice[sommet[2] * nombreSommet + sommet[2]] += (arbresPonts[aleatoire])[12];
					matrice[sommet[2] * nombreSommet + sommet[0]] += (arbresPonts[aleatoire])[10];
					matrice[sommet[2] * nombreSommet + sommet[1]] += (arbresPonts[aleatoire])[11];
					
				case 5: case 4: case 3:
					if (!sommet){
						sommetsRestant -= 2;
						sommet = new int[2]();
						for (int i = 0; i < 2; i++) {
							sommet[i] = obtIndiceAleatoireNonMarque();
						}
					}
					if (assigner){
						matrice[(sommetsArbres[3] * nombreSommet) + sommet[1]]++; // connection arbre->pont
						assigner = false;
						sommetsMarques[sommet[1]]++;
					}
					matrice[sommet[0] * nombreSommet + sommet[1]] += (arbresPonts[aleatoire])[1];
					matrice[sommet[1] * nombreSommet + sommet[1]] += (arbresPonts[aleatoire])[6];
					matrice[sommet[1] * nombreSommet + sommet[0]] += (arbresPonts[aleatoire])[5];
					matrice[0] += (arbresPonts[aleatoire])[0];
					
				default:
					if (!sommet){
						sommetsRestant--;
						sommet = new int[1]();
						sommet[0] = obtIndiceAleatoireNonMarque();
					}
					if (assigner){
						matrice[(sommetsArbres[3] * nombreSommet) + sommet[0]]++; // connection pont->arbre
						assigner = false;
						sommetMarques[sommet[0]];
					}
					matrice[(sommet[0] * nombreSommet) + sommetsArbres[2]]++; // connection pont->arbre
					break;
			}
			// pont 2
			assigner = true;
			sommet = nullptr;
			aleatoire = (sommetsRestant < 5) ? rand() % (3 * sommetsRestant) : rand() % 15;
				switch (aleatoire) {
				case 14: case 13: case 12:
					if (!sommet){
						sommetsRestant -= 5;
						sommet = new int[5]();
						for (int i = 0; i < 5; i++) {
							sommet[i] = obtIndiceAleatoireNonMarque();
						}
					}
					if (assigner){
						matrice[(sommet[4] * nombreSommet) + sommetsArbres[1]]++; // connection pont->arbre
						assigner = false;
						sommetsMarques[sommet[4]]++;
					}
					matrice[sommet[0] * nombreSommet + sommet[4]] += (arbresPonts[aleatoire])[4];
					matrice[sommet[1] * nombreSommet + sommet[4]] += (arbresPonts[aleatoire])[9];
					matrice[sommet[2] * nombreSommet + sommet[4]] += (arbresPonts[aleatoire])[14];
					matrice[sommet[3] * nombreSommet + sommet[4]] += (arbresPonts[aleatoire])[19];
					matrice[sommet[4] * nombreSommet + sommet[4]] += (arbresPonts[aleatoire])[24];
					matrice[sommet[4] * nombreSommet + sommet[0]] += (arbresPonts[aleatoire])[20];
					matrice[sommet[4] * nombreSommet + sommet[1]] += (arbresPonts[aleatoire])[21];
					matrice[sommet[4] * nombreSommet + sommet[2]] += (arbresPonts[aleatoire])[22];
					matrice[sommet[4] * nombreSommet + sommet[3]] += (arbresPonts[aleatoire])[23];

				case 11: case 10: case 9:
					if (!sommet){
						sommetsRestant -= 4;
						sommet = new int[4]();
						for (int i = 0; i < 4; i++) {
							sommet[i] = obtIndiceAleatoireNonMarque();
						}
					}
					if (assigner){
						matrice[(sommet[3] * nombreSommet) + sommetsArbres[1]]++; // connection pont->arbre
						assigner = false;
						sommetsMarques[sommet[3]]++;
					}
					matrice[sommet[0] * nombreSommet + sommet[3]] += (arbresPonts[aleatoire])[3];
					matrice[sommet[1] * nombreSommet + sommet[3]] += (arbresPonts[aleatoire])[8];
					matrice[sommet[2] * nombreSommet + sommet[3]] += (arbresPonts[aleatoire])[13];
					matrice[sommet[3] * nombreSommet + sommet[3]] += (arbresPonts[aleatoire])[18];
					matrice[sommet[3] * nombreSommet + sommet[0]] += (arbresPonts[aleatoire])[15];
					matrice[sommet[3] * nombreSommet + sommet[1]] += (arbresPonts[aleatoire])[16];
					matrice[sommet[3] * nombreSommet + sommet[2]] += (arbresPonts[aleatoire])[17];

				case 8: case 7: case 6:
					if (!sommet){
						sommetsRestant -= 3;
						sommet = new int[3]();
						for (int i = 0; i < 3; i++) {
							sommet[i] = obtIndiceAleatoireNonMarque();
						}
					}
					if (assigner){
						matrice[(sommet[2] * nombreSommet) + sommetsArbres[1]]++; // connection pont->arbre
						assigner = false;
						sommetsMarques[sommet[2]]++;
					}
					matrice[sommet[0] * nombreSommet + sommet[2]] += (arbresPonts[aleatoire])[2];
					matrice[sommet[1] * nombreSommet + sommet[2]] += (arbresPonts[aleatoire])[7];
					matrice[sommet[2] * nombreSommet + sommet[2]] += (arbresPonts[aleatoire])[12];
					matrice[sommet[2] * nombreSommet + sommet[0]] += (arbresPonts[aleatoire])[10];
					matrice[sommet[2] * nombreSommet + sommet[1]] += (arbresPonts[aleatoire])[11];

				case 5: case 4: case 3:
					if (!sommet){
						sommetsRestant -= 2;
						sommet = new int[2]();
						for (int i = 0; i < 2; i++) {
							sommet[i] = obtIndiceAleatoireNonMarque();
						}
					}
					if (assigner){
						matrice[(sommet[1] * nombreSommet) + sommetsArbres[1]]++; // connection pont->arbre
						assigner = false;
						sommetsMarques[sommet[1]]++;
					}
					matrice[sommet[0] * nombreSommet + sommet[1]] += (arbresPonts[aleatoire])[1];
					matrice[sommet[1] * nombreSommet + sommet[1]] += (arbresPonts[aleatoire])[6];
					matrice[sommet[1] * nombreSommet + sommet[0]] += (arbresPonts[aleatoire])[5];
					matrice[0] += (arbresPonts[aleatoire])[0];

				default:
					if (!sommet){=
						sommetsRestant--;
						sommet = new int[1]();
						sommet[0] = obtIndiceAleatoireNonMarque();
					}
					if (assigner){
						matrice[(sommet[0] * nombreSommet) + sommetsArbre[1]]++; // connection pont->arbre
						assigner = false;
						sommetMarques[sommet[0]]++;
					}
					matrice[(sommetsArbre[0] * nombreSommet) + sommet[0]]++; // connection arbre->Pont
					break;
			}
			// autres ponts
				int sommetLien1 , sommetLien2
				while (sommetsRestant > 0) {
					assigner = true;
					sommet = nullptr;
					aleatoire = (sommetsRestant < 5) ? rand() % (3 * sommetsRestant) : rand() % 15;
					switch (aleatoire) {
					case 14: case 13: case 12:
						if (!sommet){
							sommetsRestant -= 5;
							sommet = new int[5]();
							for (int i = 0; i < 5; i++) {
								sommet[i] = obtIndiceAleatoireNonMarque();
							}
							do
							{
								sommetLien1 = obtIndiceAleatoire();
							} while ((sommetLien1 == sommet[0]) || (sommetLien1 == sommet[1]) || (sommetLien1 == sommet[2]) || (sommetLien1 == sommet[3]) || (sommetLien1 == sommet[4]));
							do
							{
								sommetLien2 = obtIndiceAleatoire();
							} while ((sommetLien2 == sommetLien1) || (sommetLien2 == sommet[0]) || (sommetLien2 == sommet[1]) || (sommetLien2 == sommet[2]) || (sommetLien2 == sommet[3]) || (sommetLien2 == sommet[4]));
						}
						if (assigner){
							matrice[(sommet[4] * nombreSommet) + sommetLien1]++; // connection arbre->pont
							assigner = false;
							sommetsMarques[sommet[4]]++;
						}
						matrice[sommet[0] * nombreSommet + sommet[4]] += (arbresPonts[aleatoire])[4];
						matrice[sommet[1] * nombreSommet + sommet[4]] += (arbresPonts[aleatoire])[9];
						matrice[sommet[2] * nombreSommet + sommet[4]] += (arbresPonts[aleatoire])[14];
						matrice[sommet[3] * nombreSommet + sommet[4]] += (arbresPonts[aleatoire])[19];
						matrice[sommet[4] * nombreSommet + sommet[4]] += (arbresPonts[aleatoire])[24];
						matrice[sommet[4] * nombreSommet + sommet[0]] += (arbresPonts[aleatoire])[20];
						matrice[sommet[4] * nombreSommet + sommet[1]] += (arbresPonts[aleatoire])[21];
						matrice[sommet[4] * nombreSommet + sommet[2]] += (arbresPonts[aleatoire])[22];
						matrice[sommet[4] * nombreSommet + sommet[3]] += (arbresPonts[aleatoire])[23];

					case 11: case 10: case 9:
						if (!sommet){
							sommetsRestant -= 4;
							sommet = new int[4]();
							for (int i = 0; i < 4; i++) {
								sommet[i] = obtIndiceAleatoireNonMarque();
							}
							do
							{
								sommetLien1 = obtIndiceAleatoire();
							} while ((sommetLien1 == sommet[0]) || (sommetLien1 == sommet[1]) || (sommetLien1 == sommet[2]) || (sommetLien1 == sommet[3]));
							do
							{
								sommetLien2 = obtIndiceAleatoire();
							} while ((sommetLien2 == sommetLien1) || (sommetLien2 == sommet[0]) || (sommetLien2 == sommet[1]) || (sommetLien2 == sommet[2]) || (sommetLien2 == sommet[3]));
						}
						if (assigner){
							matrice[(sommet[3] * nombreSommet) + sommetLien1]++; // connection arbre->pont
							assigner = false;
							sommetsMarques[sommet[3]]++;
						}
						matrice[sommet[0] * nombreSommet + sommet[3]] += (arbresPonts[aleatoire])[3];
						matrice[sommet[1] * nombreSommet + sommet[3]] += (arbresPonts[aleatoire])[8];
						matrice[sommet[2] * nombreSommet + sommet[3]] += (arbresPonts[aleatoire])[13];
						matrice[sommet[3] * nombreSommet + sommet[3]] += (arbresPonts[aleatoire])[18];
						matrice[sommet[3] * nombreSommet + sommet[0]] += (arbresPonts[aleatoire])[15];
						matrice[sommet[3] * nombreSommet + sommet[1]] += (arbresPonts[aleatoire])[16];
						matrice[sommet[3] * nombreSommet + sommet[2]] += (arbresPonts[aleatoire])[17];

					case 8: case 7: case 6:
						if (!sommet){
							sommetsRestant -= 3;
							sommet = new int[3]();
							for (int i = 0; i < 3; i++) {
								sommet[i] = obtIndiceAleatoireNonMarque();
							}
							do
							{
								sommetLien1 = obtIndiceAleatoire();
							} while ((sommetLien1 == sommet[0]) || (sommetLien1 == sommet[1]) || (sommetLien1 == sommet[2]));
							do
							{
								sommetLien2 = obtIndiceAleatoire();
							} while ((sommetLien2 == sommetLien1) || (sommetLien2 == sommet[0]) || (sommetLien2 == sommet[1]) || (sommetLien2 == sommet[2]));
						}
						if (assigner){
							matrice[(sommet[2] * nombreSommet) + sommetLien1]++; // connection arbre->pont
							assigner = false;
							sommetsMarques[sommet[2]]++;
						}
						matrice[sommet[0] * nombreSommet + sommet[2]] += (arbresPonts[aleatoire])[2];
						matrice[sommet[1] * nombreSommet + sommet[2]] += (arbresPonts[aleatoire])[7];
						matrice[sommet[2] * nombreSommet + sommet[2]] += (arbresPonts[aleatoire])[12];
						matrice[sommet[2] * nombreSommet + sommet[0]] += (arbresPonts[aleatoire])[10];
						matrice[sommet[2] * nombreSommet + sommet[1]] += (arbresPonts[aleatoire])[11];

					case 5: case 4: case 3:
						if (!sommet){
							sommetsRestant -= 2;
							sommet = new int[2]();
							for (int i = 0; i < 2; i++) {
								sommet[i] = obtIndiceAleatoireNonMarque();
							}
							do
							{
								sommetLien1 = obtIndiceAleatoire();
							} while ((sommetLien1 == sommet[0]) || (sommetLien1 == sommet[1]));
							do
							{
								sommetLien1 = obtIndiceAleatoire();
							} while ((sommetLien2 == sommetLien1) || (sommetLien2 == sommet[0]) || (sommetLien2 == sommet[1]));
						}
						if (assigner){
							matrice[(sommet[1] * nombreSommet) + sommetLien1]++; // connection arbre->pont
							assigner = false;
							sommetsMarques[sommet[1]]++;
						}
						matrice[sommet[0] * nombreSommet + sommet[1]] += (arbresPonts[aleatoire])[1];
						matrice[sommet[1] * nombreSommet + sommet[1]] += (arbresPonts[aleatoire])[6];
						matrice[sommet[1] * nombreSommet + sommet[0]] += (arbresPonts[aleatoire])[5];
						matrice[0] += (arbresPonts[aleatoire])[0];

					default:
						if (!sommet){
							sommetsRestant--;
							sommet = new int[1]();
							sommet[0] = obtIndiceAleatoireNonMarque();
							do
							{
								sommetLien1 = obtIndiceAleatoire();
							} while (sommetLien1 == sommet[0]);
							do
							{
								sommetLien2 = obtIndiceAleatoire();
							} while ((sommetLien2 == sommetLien1) || (sommetLien2 == sommet[0]));
						}
						if (assigner){
							matrice[(sommet[0] * nombreSommet) + sommetLien1]++; // connection arbre->pont
							assigner = false;
							sommetMarques[sommet[0]]++;
						}
						matrice[sommetLien2 * nombreSommet) + sommet[0]]++; // connection pont->arbre
						break;
					}
				}
		}
		
	public:
		int* matrice;
		int nombreSommet;
		
		Graphe(int nbrSommet){
			nombreSommet = nbrSommet;
			matrice = new int[nbrSommet * nbrSommet];
			sommetsMarques = new int[nbrSommet];
			for (int i = 0; i < nbrSommet; i++){
				sommetsMarques[i] = 0;
			}
			for (int i = 0; i < nbrSommet * nbrSommet; i++){
				matrice[i] = 0;
			}
			ratio = (((rand() % 30) + 50.f) / 100);
			itterateur = 0;
			creerArbre(obtIndiceAleatoireNonMarque(), 0, ((nbrSommet * ratio) / 2));
			itterateur = 1;
			creerArbre(obtIndiceAleatoireNonMarque(), 0, ((nbrSommet * ratio) / 2));
			
		}
		
		int degre(int indice){
			return degreEntrant(indice) + degreSortant(indice);
		}
		int degreEntrant(int indice){
			int ittCompte = 0;
			for(int i = 0; i < nombreSommet; i++){
				if (matrice[(indice * nombreSommet) + i])
					ittCompte++;
			}
			return ittCompte;
		}
		int degreSortant(int indice){
			int ittCompte = 0;
			for(int i = 0; i < nombreSommet; i++){
				if (matrice[(i * nombreSommet) + indice])
					ittCompte++;
			}
			return ittCompte;
		}
	};
}