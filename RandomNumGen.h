#pragma once
#include <random>
class RandomNumGen {

	static std::mt19937 randomNum;

public:
	//one and only one of these
	static int RandomInt(int min, int max);
	static float RandomFloat(float min, float max);


};

