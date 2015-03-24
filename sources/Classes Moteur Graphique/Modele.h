#pragma once
#include "Vecteur3.h"
#include "Maths.h"

#include <fstream>
#include <queue>

namespace gfx{

	class Modele{
	private:
		double* vertices;
		double* textures;
		double* normales;
		Vecteur3d taille;
		unsigned int nbrVertices;
		Vecteur3d boiteDeCollision[8];

		void calculerBoiteDeCollision(){
			std::vector<double> tmpX;
			std::vector<double> tmpY;
			std::vector<double> tmpZ;
			double xmax, xmin, ymax, ymin, zmax, zmin;
			for (int i = 0; i < nbrVertices/3; ++i){
				tmpX.push_back(vertices[i * 3]);
				tmpY.push_back(vertices[i * 3 + 1]);
				tmpZ.push_back(vertices[i * 3 + 2]);
			}
			xmax = Maths::obtValeurMax(tmpX);
			xmin = Maths::obtValeurMin(tmpX);
			ymax = Maths::obtValeurMax(tmpY);
			ymin = Maths::obtValeurMin(tmpY);
			zmax = Maths::obtValeurMax(tmpZ);
			zmin = Maths::obtValeurMin(tmpZ);
			boiteDeCollision[0] = Vecteur3d(xmin, ymin, zmax);
			boiteDeCollision[1] = Vecteur3d(xmin, ymax, zmax);
			boiteDeCollision[2] = Vecteur3d(xmax, ymax, zmax);
			boiteDeCollision[3] = Vecteur3d(xmax, ymin, zmax);
			boiteDeCollision[4] = Vecteur3d(xmin, ymin, zmin);
			boiteDeCollision[5] = Vecteur3d(xmin, ymax, zmin);
			boiteDeCollision[6] = Vecteur3d(xmax, ymax, zmin);
			boiteDeCollision[7] = Vecteur3d(xmax, ymin, zmin);
		}

		void calculerTaille(){
			std::vector<double> tmpX;
			std::vector<double> tmpY;
			std::vector<double> tmpZ;
			for (int i = 0; i < nbrVertices / 3; ++i){
				tmpX.push_back(vertices[i * 3]);
				tmpY.push_back(vertices[i * 3 + 1]);
				tmpZ.push_back(vertices[i * 3 + 2]);
			}
			taille.x = Maths::obtValeurMax(tmpX) - Maths::obtValeurMin(tmpX);
			taille.y = Maths::obtValeurMax(tmpY) - Maths::obtValeurMin(tmpY);
			taille.z = Maths::obtValeurMax(tmpZ) - Maths::obtValeurMin(tmpZ);
		}

	public:

		Modele(){}

		Modele(const char* chemin){
			charger(chemin);
		}

		~Modele(){
			//if (vertices)
			//	delete[] vertices;
			//if (textures)
			//	delete[] textures;
			//if (normales)
			//	delete[] normales;
		}

		bool charger(const char* chemin){
			std::ifstream Fichier(chemin);
			if (Fichier.is_open()){
				char *X = new char(), *Y = new char(), *Z = new char(), *temp = new char();
				std::vector<double> tmpVertices;
				std::queue<double> Vertices;
				std::vector<double> tmpTextures;
				std::queue<double> Textures;
				std::vector<double> tmpNormales;
				std::queue<double> Normales;

				while (!Fichier.eof()){
					Fichier >> temp;
					if (temp[0] == 'v')
					{
						if (temp[1] == 't'){
							Fichier >> X >> Y;
							tmpTextures.push_back(SDL_atof(X));
							tmpTextures.push_back(SDL_atof(Y));
						}
						else if (temp[1] == 'n'){
							Fichier >> X >> Y >> Z;
							tmpNormales.push_back(SDL_atof(X));
							tmpNormales.push_back(SDL_atof(Y));
							tmpNormales.push_back(SDL_atof(Z));
						}
						else if (temp[1] == NULL){
							Fichier >> X >> Y >> Z;
							tmpVertices.push_back(SDL_atof(X));
							tmpVertices.push_back(SDL_atof(Y));
							tmpVertices.push_back(SDL_atof(Z));
						}
					}
					else if (temp[0] == 'f'){

						Fichier >> X >> Y >> Z;
						int it;
						std::string Ligne, LigneTemp;
						for (int i = 0; i < 3; i++)
						{
							switch (i)
							{
							case 0:
								LigneTemp = X;
								break;
							case 1:
								LigneTemp = Y;
								break;
							case 2:
								LigneTemp = Z;
								break;
							}
							LigneTemp.append("/");
							for (int j = 0; j < 3; j++)
							{
								Ligne = LigneTemp;
								it = 0;

								while (Ligne[it] != '/')
									it++;

								Ligne.erase(it, Ligne.length());

								if (Ligne[0] != NULL)
								{
									switch (j)
									{
									case 0:
										for (int k = 0; k < 3; k++)
											Vertices.push(tmpVertices[(SDL_atoi(Ligne.c_str()) - 1) * 3 + k]);
										break;
									case 1:
										for (int k = 0; k < 2; k++)
											Textures.push(tmpTextures[(SDL_atoi(Ligne.c_str()) - 1) * 2 + k]);
										break;
									case 2:
										for (int k = 0; k < 3; k++)
											Normales.push(tmpNormales[(SDL_atoi(Ligne.c_str()) - 1) * 3 + k]);
										break;
									}
								}
								LigneTemp.erase(0, it + 1);
							}
						}
					}
				}
				Fichier.close();
				nbrVertices = Vertices.size();

				if (nbrVertices){
					vertices = new double[nbrVertices];
					for (int i = 0; i < nbrVertices; i++)
					{
						vertices[i] = Vertices.front();
						Vertices.pop();
					}
				}

				if (Textures.size()){
					textures = new double[Textures.size()];
					for (int i = 0; i < nbrVertices / 3 * 2; i++)
					{
						textures[i] = Textures.front();
						Textures.pop();
					}
				}

				if (Normales.size())
				{
					normales = new double[nbrVertices];
					for (int i = 0; i < nbrVertices; i++)
					{
						normales[i] = Normales.front();
						Normales.pop();
					}
				}
				calculerTaille();
				calculerBoiteDeCollision();
				return true;
			}
			return false;
		}

		Vecteur3d* obtBoiteDeCollision(){
			return boiteDeCollision;
		}

		Vecteur3d obtTaille(){
			return taille;
		}

		double* obtVertices(){
			return vertices;
		}

		double* obtTextures(){
			return textures;
		}

		double* obtNormales(){
			return normales;
		}

		unsigned int obtNbrVertices(){
			return nbrVertices;
		}

		unsigned int obtNbrSommets(){
			return  nbrVertices / 3;
		}

		unsigned int obtNbrFaces(){
			return nbrVertices / 9;
		}
	};
}