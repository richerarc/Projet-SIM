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
		Vecteur3i indicesBoiteDeCollision[12];
		static Vecteur3f* normalesBoiteDeCollision;

		void calculerBoiteDeCollision(){
			std::vector<double> tmpX;
			std::vector<double> tmpY;
			std::vector<double> tmpZ;
			double xmax, xmin, ymax, ymin, zmax, zmin;
			for (unsigned int i = 0; i < nbrVertices / 3; ++i){
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

			indicesBoiteDeCollision[0] = Vecteur3i(0, 1, 2);
			indicesBoiteDeCollision[1] = Vecteur3i(0, 2, 3);
			indicesBoiteDeCollision[2] = Vecteur3i(4, 5, 6);
			indicesBoiteDeCollision[3] = Vecteur3i(4, 6, 7);
			indicesBoiteDeCollision[4] = Vecteur3i(0, 4, 3);
			indicesBoiteDeCollision[5] = Vecteur3i(3, 4, 7);
			indicesBoiteDeCollision[6] = Vecteur3i(1, 5, 2);
			indicesBoiteDeCollision[7] = Vecteur3i(2, 5, 7);
			indicesBoiteDeCollision[8] = Vecteur3i(0, 1, 4);
			indicesBoiteDeCollision[9] = Vecteur3i(4, 1, 5);
			indicesBoiteDeCollision[10] = Vecteur3i(3, 2, 7);
			indicesBoiteDeCollision[11] = Vecteur3i(7, 2, 6);

			if (!normalesBoiteDeCollision) {

				normalesBoiteDeCollision = new Vecteur3f[6];

				normalesBoiteDeCollision[0] = Vecteur3f(0, 0, 1);
				normalesBoiteDeCollision[1] = Vecteur3f(0, 0, -1);
				normalesBoiteDeCollision[2] = Vecteur3f(0, -1, 0);
				normalesBoiteDeCollision[3] = Vecteur3f(0, 1, 0);
				normalesBoiteDeCollision[4] = Vecteur3f(-1, 0, 0);
				normalesBoiteDeCollision[5] = Vecteur3f(1, 0, 0);
			}
		}

		void calculerTaille(){
			std::vector<double> tmpX;
			std::vector<double> tmpY;
			std::vector<double> tmpZ;
			for (unsigned int i = 0; i < nbrVertices / 3; ++i){
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
			pol++;
			charger(chemin);
		}

		Modele(double* vertices, double* textures, double* normales){
			pol++;
			this->vertices = vertices;
			this->textures = textures;
			this->normales = normales;
		}

		~Modele(){
			pol--;
			if (vertices)
			{
				
				delete[] vertices;
				vertices = nullptr;
			}
			if (textures){
				delete[] textures;
				textures = nullptr;
			}
			if (normales){
				delete[] normales;
				normales = nullptr;
			}
		}

		bool charger(const char* chemin){
			std::ifstream Fichier(chemin);
			if (Fichier.is_open()){
				char *X = new char[255], *Y = new char[255], *Z = new char[255], *temp = new char[255];
				std::vector<double> tmpVertices;
				std::queue<double> Vertices;
				std::vector<double> tmpTextures;
				std::queue<double> Textures;
				std::vector<double> tmpNormales;
				std::queue<double> Normales;

				while (!Fichier.eof())
				{
					Fichier >> temp;
					if (temp[0] == '#' || temp[0] == 'o' || temp[0] == 's')
					{
						Fichier.getline(temp, 256);
					}
					else if (temp[0] == 'v')
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
					else if (temp[0] == 'f')
					{

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
					for (unsigned int i = 0; i < nbrVertices; i++)
					{
						vertices[i] = Vertices.front();
						Vertices.pop();
					}
				}

				if (Textures.size()){
					textures = new double[Textures.size()];
					for (unsigned int i = 0; i < nbrVertices / 3 * 2; i++)
					{
						textures[i] = Textures.front();
						Textures.pop();
					}
				}

				if (Normales.size())
				{
					normales = new double[nbrVertices];
					for (unsigned int i = 0; i < nbrVertices; i++)
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

		Vecteur3i* obtIndidesBoiteDeCollision() {
			return indicesBoiteDeCollision;
		}

		Vecteur3f* obtNormalesBoiteDeCollision() {
			return normalesBoiteDeCollision;
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

	Vecteur3f* gfx::Modele::normalesBoiteDeCollision = nullptr;
}
