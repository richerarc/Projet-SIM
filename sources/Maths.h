#pragma once

#include <vector>
#include <algorithm>

#define MATHS_PI 3.141592654

class Maths{
public:
	static float obtValeurMax(std::vector<float> &nombres){
		float maximum = nombres[0];
		for (auto i : nombres)
			maximum = std::max(maximum, i);
		return maximum;
	}

	static float obtValeurMin(std::vector<float> &nombres){
		float minimum = nombres[0];
		for (auto i : nombres)
			minimum = std::min(minimum, i);
		return minimum;
	}
	static float degreARadian(float degre){
		return ((degre * MATHS_PI) / 180);
	}

	static float radianADegre(float radian){
		return ((degre * 180) / MATHS_PI);
	}

};