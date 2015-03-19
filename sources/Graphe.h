namespace graphe{
	int arbrePont1a[1][1] = {3};
	int arbrePont1b[1][1] = {1};
	int arbrePont1c[1][1] = {0};
	int arbrePont2a[2][2] = {0, 1, 1, 1};
	int arbrePont2b[2][2] = {0, 2, 2, 0};
	int arbrePont2c[2][2] = {0, 1, 0, 0};
	int arbrePont3a[3][3] = {0, 1, 1, 0, 0, 1, 1, 0, 0};
	int arbrePont3b[3][3] = {0, 1, 0, 0, 0, 1, 1, 0, 0};
	int arbrePont3c[3][3] = {0, 0, 0, 1, 0, 0, 1, 0, 0};
	int arbrePont4a[4][4] = {0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0};
	int arbrePont4b[4][4] = {0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0};
	int arbrePont4c[4][4] = {0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0};
	int arbrePont5a[5][5] = {0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0};
	int arbrePont5b[5][5] = {0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0};
	int arbrePont5c[5][5] = {0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0};
	int* arbresPonts[15] = {arbrePont1a[0], arbrePont1b[0], arbrePont1c[0], arbrePont2a[0], arbrePont2b[0], arbrePont2c[0], arbrePont3a[0], arbrePont3b[0], arbrePont3c[0], arbrePont4a[0], arbrePont4b[0], arbrePont4c[0], arbrePont5a[0], arbrePont5b[0], arbrePont5c[0] };
	
	class Graphe {
	private:
		int* sommetsMarques;
		int sommetsArbres[4];
		int itterateur;
		double ratio;
		
		int obtIndiceAleatiore(){
			return rand() % nombreSommet;
		}
		
		int obtIndiceAleatioreNonMarque(){
			int indice;
			for (int i = 0; i < nombreSommet; i++) {
				indice = obtIndiceAleatiore();
				if (sommetsMarques[indice] == 0)
					return indice;
			}
			return -1;  // erreur aucun indice non marqué
		}
		
		void creerArbre(int indice, int niveau, int nbrSommetParArbre){
			if (!niveau)
				sommetsArbres[itterateur] = indice;
			sommetsMarques[indice]++;
			int indiceTemp = obtIndiceAleatioreNonMarque();
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
			bool assigner(true);
			int* sommet = nullptr;
			switch (rand() % 15) {
				case 14: case 13: case 12:
					if (!sommet){
						sommet = new int[5]();
						for (int i = 0; i < 5; i++) {
							sommet[i] = obtIndiceAleatioreNonMarque();
						}
					}
					if (assigner){
						matrice[(sommetsArbres[3] * nombreSommet) + sommet[4]]++;
						assigner = false;
						sommetsMarques[sommet[4]]++;
					}
					
				case 11: case 10: case 9:
					if (!sommet){
						sommet = new int[4]();
						for (int i = 0; i < 4; i++) {
							sommet[i] = obtIndiceAleatioreNonMarque();
						}
					}
					if (assigner){
						matrice[(sommetsArbres[3] * nombreSommet) + sommet[3]]++;
						assigner = false;
						sommetsMarques[sommet[3]]++;
					}
					
				case 8: case 7: case 6:
					if (!sommet){
						sommet = new int[3]();
						for (int i = 0; i < 3; i++) {
							sommet[i] = obtIndiceAleatioreNonMarque();
						}
					}
					if (assigner){
						matrice[(sommetsArbres[3] * nombreSommet) + sommet[2]]++;
						assigner = false;
						sommetsMarques[sommet[2]]++;
					}
					
				case 5: case 4: case 3:
					if (!sommet){
						sommet = new int[2]();
						for (int i = 0; i < 2; i++) {
							sommet[i] = obtIndiceAleatioreNonMarque();
						}
					}
					if (assigner){
						matrice[(sommetsArbres[3] * nombreSommet) + sommet[1]]++;
						assigner = false;
						sommetsMarques[sommet[1]]++;
					}
					
					break;
				default:
					
					break;
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
			creerArbre(obtIndiceAleatioreNonMarque(), 0, ((nbrSommet * ratio) / 2));
			itterateur = 1;
			creerArbre(obtIndiceAleatioreNonMarque(), 0, ((nbrSommet * ratio) / 2));
			
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