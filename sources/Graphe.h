namespace graphe{
	int arbrePont1[1][1] = { 3 };
	int arbrePont2a[2][2] = {0,1,1,1};
	int arbrePont2b[2][2] = { 0, 2, 2, 0 };
	int arbrePont3[3][3] = { 0, 1, 1, 0, 0, 1, 1, 0, 0 };
	int arbrePont4a[4][4] = { 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0 };
	int arbrePont4b[4][4] = { 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0 };
	int arbrePont5a[5][5] = { 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 };
	int arbrePont5b[5][5] = { 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0 };
	int arbrePont5c[5][5] = { 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0 };
	int* arbresPonts[9] = { arbrePont1[0], arbrePont2a[0], arbrePont2b[0], arbrePont3[0], arbrePont4a[0], arbrePont4b[0], arbrePont5a[0], arbrePont5b[0], arbrePont5c[0] };
	
	class Graphe {
	private:
		int* sommetsMarques;
		double ratio;
		int nbrSommetParArbre;
		
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
		
		void creerArbre(int indice, int niveau){
			sommetsMarques[indice]++;
			int indiceTemp = obtIndiceAleatioreNonMarque();
			sommetsMarques[indiceTemp]++;
			matrice[(indice * 36) + indiceTemp]++;
			matrice[(indiceTemp * 36) + indice]++;
			if (niveau < nbrSommetParArbre){
				if ((sommetsMarques[indice] < 8) || (rand() % 2)){
					creerArbre(indiceTemp, ++niveau);
				}
				else{
					creerArbre(indice, ++niveau);
				}
			}
		}
		
	public:
		int* matrice;
		int nombreSommet;
		
		Graphe(int nbrSommet){
			nombreSommet = nbrSommet;
			matrice = new int[nbrSommet * nbrSommet];
			sommetsMarques = new int[nbrSommet]();
			for (int i = 0; i < nbrSommet; i++){
				sommetsMarques[i] = 0;
			}
			ratio = (((rand() % 30) + 40.f) / 100);
			nbrSommetParArbre = (nbrSommet * ratio) / 2;
			
			creerArbre(obtIndiceAleatioreNonMarque(), 0);
			creerArbre(obtIndiceAleatioreNonMarque(), 0);
			
		}
		
		int degre(int indice){
			return degreEntrant(indice) + degreSortant(indice);
		}
		int degreEntrant(int indice){
			int ittCompte = 0;
			for(int i = 0; i < nombreSommet; i++){
				if (matrice[(indice * 36) + i])
					ittCompte++;
			}
			return ittCompte;
		}
		int degreSortant(int indice){
			int ittCompte = 0;
			for(int i = 0; i < nombreSommet; i++){
				if (matrice[(i * 36) + indice])
					ittCompte++;
			}
			return ittCompte;
		}
	};
}