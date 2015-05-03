#pragma once
#define MATHS_PI 3.141592654
#define M_E  2.7182818284590452353602874713526624977572470936999595749669676277240766303535475945713821785251664274
#include <algorithm>
#include <vector>
class Maths{
public:
	static double obtValeurMax(std::vector<double> &nombres){
		double maximum = nombres[0];
		for (auto i : nombres)
			maximum = std::max(maximum, i);
		return maximum;
	}

	static double obtValeurMin(std::vector<double> &nombres){
		double minimum = nombres[0];
		for (auto i : nombres)
			minimum = std::min(minimum, i);
		return minimum;
	}
	static double degreARadian(double degre){
		return ((degre * MATHS_PI) / 180);
	}

	static double radianADegre(double radian){
		return ((radian * 180) / MATHS_PI);
	}

};