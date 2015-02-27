
template <class T>

class Vecteur {

public:

	T composanteX, 
	composanteY,
	composanteZ;

	T Norme() {
		return sqrt((composanteX * composanteX) + (composanteY * composanteY) + (composanteZ * composanteZ));
	}
	
	Vecteur(){
		composanteX = 0;
		composanteY = 0;
		composanteZ = 0;
	}

	Vecteur(T X, T Y, T Z) {
		composanteX = X;
		composanteY = Y;
		composanteZ = Z;
	}

	void normaliser() {

		T norme = Norme();
		composanteX /= norme;
		composanteY /= norme;
		composanteZ /= norme;
	}

	void inverser(){
		composanteX = -composanteX;
		composanteY = -composanteY;
		composanteZ = -composanteZ;
	}

	void ajouter(CVecteur<T>& vecteur) {
		composanteX += vecteur.composanteX;
		composanteY += vecteur.composanteY;
		composanteZ += vecteur.composanteZ;
	}

	void soustraire(CVecteur<T>& vecteur) {
		composanteX -= vecteur.composanteX;
		composanteY -= vecteur.composanteY;
		composanteZ -= vecteur.composanteZ;
	}

	void produitParScalaire(double scalaire) {

		composanteX *= scalaire;
		composanteY *= scalaire;
		composanteZ *= scalaire;
	}

	void divisionParScalaire(double scalaire) {
		composanteX /= scalaire;
		composanteY /= scalaire;
		composanteZ /= scalaire;
	}

	static CVecteur<T>* somme(CVecteur<T>& vecteur1, CVecteur<T>& vecteur2) {

		return new CVecteur<T>(vecteur1.composanteX + vecteur2.composanteX, vecteur1.composanteY + vecteur2.composanteY, vecteur1.composanteZ + vecteur2.composanteZ);

	}

	static CVecteur<T>* difference(CVecteur<T>& vecteur1, CVecteur<T>& vecteur2) {

		return new CVecteur<T>(vecteur1.composanteX - vecteur2.composanteX, vecteur1.composanteY - vecteur2.composanteY, vecteur1.composanteZ - vecteur2.composanteZ);

	}

	static CVecteur<T>* produitVectoriel(CVecteur<T>& vecteur1, CVecteur<T>& vecteur2) {

		return new CVecteur<T>((vecteur1.composanteY * vecteur2.composanteZ) - (vecteur2.composanteZ * vecteur1.composanteY), (vecteur1.composanteZ * vecteur2.composanteX) - (vecteur2.composanteZ * vecteur1.composanteX), (vecteur1.composanteX * vecteur2.composanteY) - (vecteur2.composanteX * vecteur1.composanteY));
	}

	static double produitScalaire(CVecteur<T>& vecteur1, CVecteur<T>& vecteur2) {

		return ((vecteur1.composanteX * vecteur2.composanteX) + (vecteur1.composanteY * vecteur2.composanteY) + (vecteur1.composanteZ * vecteur2.composanteZ));

	}

};
