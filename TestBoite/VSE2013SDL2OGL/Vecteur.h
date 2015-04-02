#include <stdarg.h>
#include <math.h>
#define V3X 0
#define V3Y 1
#define V3Z 2
template<typename T>
class Vecteur{
private:
	T* tComposantes;
	unsigned short nbrComposantes;
public:
	Vecteur(unsigned short nbrComposantes,...){
		this->nbrComposantes = nbrComposantes;
		va_list composantes;
		va_start(composantes, nbrComposantes);
		tComposantes = new T[nbrComposantes];
		for (unsigned short pos = 0; pos < nbrComposantes; pos++){
			tComposantes[pos] = va_arg(composantes, T);
		}
		va_end(composantes);
	}
	void Composante(unsigned short composante, T valeur){
		tComposantes[composante] = valeur;
	}
	T Composante(unsigned short composante){
		return tComposantes[composante];
	}
	T* Composantes(){
		return tComposantes;
	}
	double Norme(){
		double norme = 0;
		for (unsigned short i = 0; i < nbrComposantes; i++){
			norme += exp2(tComposantes[i]);
		}
		return sqrt(norme);
	}
	void Normaliser(){
		double norme = Norme();
		for (unsigned short i = 0; i < nbrComposantes; i++){
			tComposantes[i] /= norme;
		}
	}
	void Ajouter(Vecteur<T> vecteur){
		for (unsigned short i = 0; i < nbrComposantes; i++){
			tComposantes[i] += vecteur.Composante(i);
		}
	}
	void Soustraire(Vecteur<T> vecteur){
		for (unsigned short i = 0; i < nbrComposantes; i++){
			tComposantes[i] -= vecteur.Composante(i);
		}
	}
	void Redimensionner(double ratio){
		for (unsigned short i = 0; i < nbrComposantes; i++){
			tComposantes[i] *= ratio;
		}
	}
	static Vecteur<T> Somme(Vecteur<T> v1, Vecteur<T> v2){
		for (unsigned short i = 0; i < v1.nbrComposantes; i++){
			v1.Composantes[i] += v2.Composante(i);
		}
		return v1;
	}
	static Vecteur<T> Différence(Vecteur<T> v1, Vecteur<T> v2){
		for (unsigned short i = 0; i < v1.nbrComposantes; i++){
			v1.Composantes[i] -= v2.Composante(i);
		}
		return v1;
	}

	static double ProduitScalaire(Vecteur<T> v1, Vecteur<T> v2){
		double produit;
		for (unsigned short i = 0; i < v1.nbrComposantes; i++){
			produit += v1.Composante(i) * v2.Composante(i);
		}
		return produit;
	}

	static Vecteur<T> ProduitVectoriel(Vecteur<T> v1, Vecteur<T> v2){
		Vecteur<T> produit = v1;
		produit.Composante(V3X) = v1.Composante(V3Y) * v2.Composante(V3Z) - v1.Composante(V3Z) * v2.Composante(V3Y);
		produit.Composante(V3Y) = v1.Composante(V3Z) * v2.Composante(V3X) - v1.Composante(V3X) * v2.Composante(V3Z);
		produit.Composante(V3Z) = v1.Composante(V3X) * v2.Composante(V3Y) - v1.Composante(V3Y) * v2.Composante(V3X);
		return produit;
	}
};