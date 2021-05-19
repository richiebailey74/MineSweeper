#include "RandomNumGen.h"
#include <ctime>

//don't need to be redefined as static since defined as static in the header files
//but static variables must be redeclared in global space (don't need to put static, it is implied)
//random number generator must be given a seed to kick start it
std::mt19937 RandomNumGen::randomNum(time(0));

//static function that yields random integer
int RandomNumGen::RandomInt(int min, int max) {

	std::uniform_int_distribution<int> range(min, max);
	return range(randomNum);
}

//static function that yields random float
float RandomNumGen::RandomFloat(float min, float max) {

	std::uniform_real_distribution<float> range(min, max);
	return range(randomNum);
}
