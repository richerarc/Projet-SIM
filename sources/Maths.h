#pragma once
#define MATHS_PI 3.141592654

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