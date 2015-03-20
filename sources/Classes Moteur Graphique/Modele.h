#pragma once
#include "Vecteur3.h"
#include "Maths.h"

#include <fstream>
#include <queue>

namespace gfx{

	class Modele{
	private:
		float* vertices;
		float* textures;
		float* normales;
		Vecteur3f taille;
		unsigned int nbrVertices;
		Vecteur3f boiteDeCollision[8];

		void calculerBoiteDeCollision(){
			std::vector<float> tmpX;
			std::vector<float> tmpY;
			std::vector<float> tmpZ;
			float xmax, xmin, ymax, ymin, zmax, zmin;
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
			boiteDeCollision[0] = Vecteur3f(xmin, ymin, zmax);
			boiteDeCollision[1] = Vecteur3f(xmin, ymax, zmax);
			boiteDeCollision[2] = Vecteur3f(xmax, ymax, zmax);
			boiteDeCollision[3] = Vecteur3f(xmax, ymin, zmax);
			boiteDeCollision[4] = Vecteur3f(xmin, ymin, zmin);
			boiteDeCollision[5] = Vecteur3f(xmin, ymax, zmin);
			boiteDeCollision[6] = Vecteur3f(xmax, ymax, zmin);
			boiteDeCollision[7] = Vecteur3f(xmax, ymin, zmin);
		}

		void calculerTaille(){
			std::vector<float> tmpX;
			std::vector<float> tmpY;
			std::vector<float> tmpZ;
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
				std::vector<float> tmpVertices;
				std::queue<float> Vertices;
				std::vector<float> tmpTextures;
				std::queue<float> Textures;
				std::vector<float> tmpNormales;
				std::queue<float> Normales;

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
					vertices = new float[nbrVertices];
					for (int i = 0; i < nbrVertices; i++)
					{
						vertices[i] = Vertices.front();
						Vertices.pop();
					}
				}

				if (Textures.size()){
					textures = new float[Textures.size()];
					for (int i = 0; i < nbrVertices / 3 * 2; i++)
					{
						textures[i] = Textures.front();
						Textures.pop();
					}
				}

				if (Normales.size())
				{
					normales = new float[nbrVertices];
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

		Vecteur3f* obtBoiteDeCollision(){
			return boiteDeCollision;
		}

		Vecteur3f obtTaille(){
			return taille;
		}

		float* obtVertices(){
			return vertices;
		}

		float* obtTextures(){
			return textures;
		}

		float* obtNormales(){
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