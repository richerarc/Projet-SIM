
template <class T>

class Vecteur {

public:

	T composanteX, 
	composanteY,
	composanteZ;

	T calculerNorme() {

		T composantesCarre = 0;

		composantesCarre += pow(composanteX, 2);
		composantesCarre += pow(composanteY, 2);
		composantesCarre += pow(composanteZ, 2);

		return sqrt(composantesCarre);
	}

	Vecteur(T compX, T compY, T compZ) {

		composanteX = compX;
		composanteY = compY;
		composanteZ = compZ;
		
	}

	void normaliserVecteur() {

		T norme = calculerNorme();

		composanteX /= norme;
		composanteY /= norme;
		composanteZ /= norme;
	}

	void ajouterVecteur(CVecteur<T>& vecteur) {

		
		composanteX += vecteur.composanteX;
		composanteY += vecteur.composanteY;
		composanteZ += vecteur.composanteZ;
	}

	void soustraireVecteur(CVecteur<T>& vecteur) {

		composanteX -= vecteur.composanteX;
		composanteY -= vecteur.composanteY;
		composanteZ -= vecteur.composanteZ;

	}

	void produitParScalaire(double scalaire) {

		composanteX *= scalaire;
		composanteY *= scalaire;
		composanteZ *= scalaire;
	}

	static CVecteur<T>* somme(CVecteur<T>& vecteur1, CVecteur<T>& vecteur2) {

		return new CVecteur<T>(m_NbrComposantes, vecteur1.composanteX + vecteur2.composanteX, vecteur1.composanteY + vecteur2.composanteY, vecteur1.composanteZ + vecteur2.composanteZ);

	}

	static CVecteur<T>* difference(CVecteur<T>& vecteur1, CVecteur<T>& vecteur2) {

		return new CVecteur<T>(vecteur1.ObtenirNbrComposante(), vecteur1.composanteX - vecteur2.composanteX, vecteur1.composanteY - vecteur2.composanteY, vecteur1.composanteZ - vecteur2.composanteZ);

	}

	static CVecteur<T>* produitVectoriel(CVecteur<T>& vecteur1, CVecteur<T>& vecteur2) {

		return new CVecteur<T>(vecteur1.ObtenirNbrComposante(), (vecteur1.composanteY * vecteur2.composanteZ) - (vecteur2.composanteZ * vecteur1.composanteY), (vecteur1.composanteZ * vecteur2.composanteX) - (vecteur2.composanteZ * vecteur1.composanteX), (vecteur1.composanteX * vecteur2.composanteY) - (vecteur2.composanteX * vecteur1.composanteY));
	}

	static double produitScalaire(CVecteur<T>& vecteur1, CVecteur<T>& vecteur2) {

		return ((vecteur1.composanteX * vecteur2.composanteX) + (vecteur1.composanteY * vecteur2.composanteY) + (vecteur1.composanteZ * vecteur2.composanteZ));

	}

};
