#pragma once

#include <vector>
#include <algorithm>

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



};