#pragma once

template<typename T>
class Singleton {
public:
	static T& obtInstance() {
		static T instance;
		return instance;
	}
};
