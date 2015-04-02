#pragma once
#include <chrono>
#include "Temps.h"
using namespace std::chrono;

class Chrono
{
public:
	Chrono(){
		this->dernierTemps = high_resolution_clock::now();
	}
	Temps obtTempsEcoule(){
		std::chrono::duration<double> span = duration_cast<duration<double>>(high_resolution_clock::now() - dernierTemps);
		return Temps(span.count());
	}
	Temps repartir(){
		double time = obtTempsEcoule().enSecondes();
		this->dernierTemps = high_resolution_clock::now();
		return Temps(time);
	}
private:
	high_resolution_clock::time_point dernierTemps;
};
