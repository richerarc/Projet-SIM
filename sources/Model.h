#pragma once
#include <vector>
#include <queue>
#include <fstream>
#include <iostream>

class Model{
private:
	float* vertices;
	float* textures;
	float* normals;
	Vecteur3f Taille;
	unsigned int nbrVertices;
	unsigned int nbrFaces;
public:

	Model(){}

	~Model(){
		if (vertices)
			delete vertices;
		if (textures)
			delete textures;
		if (normals)
			delete normals;
	}

	bool Charger(const char* chemin){
		std::ifstream Fichier(chemin);
		if (Fichier.is_open()){
			char *X = new char(), *Y = new char(), *Z = new char(), *temp = new char();
			std::vector<float> tmpVertices;
			std::queue<float> Vertices;
			std::vector<float> tmpTextures;
			std::queue<float> Textures;
			std::vector<float> tmpNormals;
			std::queue<float> Normals;

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
						tmpNormals.push_back(SDL_atof(X));
						tmpNormals.push_back(SDL_atof(Y));
						tmpNormals.push_back(SDL_atof(Z));
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
										Normals.push(tmpNormals[(SDL_atoi(Ligne.c_str()) - 1) * 3 + k]);
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
			nbrFaces = nbrVertices / 3;

			if (nbrVertices){
				vertices = new float[nbrVertices];
				for (int i = 0; i < nbrVertices; i++)
				{
					vertices[i] = Vertices.front();
					Vertices.pop();
				}
			}
			else
			{ 
				vertices = nullptr;
				normals = nullptr;
				textures = nullptr;
				return false;
			}

			if (Textures.size()){
				textures = new float[Textures.size()];
				for (int i = 0; i < nbrFaces * 2; i++)
				{
					textures[i] = Textures.front();
					Textures.pop();
				}
			}
			else 
				textures = nullptr;

			if (Normals.size())
			{
				normals = new float[nbrVertices];
				for (int i = 0; i < nbrVertices; i++)
				{
					normals[i] = Normals.front();
					Normals.pop();
				}
			}
			else
				normals = nullptr;
			calculerTaille();
			return true;
		}
		vertices = nullptr;
		normals = nullptr;
		textures = nullptr;
		return false;
	}

	void calculerTaille(){
		float xMin = 0.0f, xMax = 0.0f, yMin = 0.0f, yMax = 0.0f, zMin = 0.0f, zMax = 0.0f;
		for (int i = 0; i < nbrVertices; i += 3)
		{
			if (vertices[i] > xMax)
				xMax = vertices[i];
			else if (vertices[i] < xMin)
				xMin = vertices[i];

			if (vertices[i + 1] > yMax)
				yMax = vertices[i + 1];
			else if (vertices[i + 1] < yMin)
				yMin = vertices[i + 1];

			if (vertices[i + 2] > zMax)
				zMax = vertices[i + 2];
			else if (vertices[i + 2] < zMin)
				zMin = vertices[i + 2];
		}
		Taille.x = xMax - xMin;
		Taille.y = yMax - yMin;
		Taille.z = zMax - zMin;
	}

	Vecteur3f obtTaille(){
		return Taille;
	}

	float* obtVertices(){
		return vertices;
	}

	float* obtTextures(){
		return textures;
	}

	float* obtNormales(){
		return normals;
	}

	unsigned int obtNbrVertices(){
		return nbrVertices;
	}

	unsigned int obtNbrFaces(){
		return nbrFaces;
	}

};