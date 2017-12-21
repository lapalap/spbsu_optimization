#include <random>


std::mt19937									_generator;
std::uniform_real_distribution<double>			_dis;

const double GetRandomNumber(const double bound = 1.0)
{
	return _dis(_generator) * bound;
}

const std::vector<double> GetRandomVector(const std::vector<double> bounds = { 0,1 }) {
	int N = bounds.size();
	std::vector<double> result;
	double temp = 0;
	for (int i = 0; i < N; i = i + 2) {
		temp = bounds[i + 1] - bounds[i];
		result.push_back(temp*GetRandomNumber() + bounds[i]);
	}
	return result;
}
