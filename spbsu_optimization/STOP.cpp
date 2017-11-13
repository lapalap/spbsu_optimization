#include "stdafx.h"
#include "STOP.h"

Iterations::Iterations(unsigned int MAX)
{
	this->N_MAX = MAX;
}

bool Iterations::status()
{
	if (this->N_iter < this->N_MAX) {
		return true;
	}
	return false;
}

void Iterations::update(std::vector<double> x_curr, std::vector<double> x_prev , double f_curr, double f_prev)
{
	++(this->N_iter);
}

ArgNorm::ArgNorm(double eps)
{
	this->eps = eps;
}

bool ArgNorm::status()
{
	return s;
}

void ArgNorm::update(std::vector<double> x_curr, std::vector<double> x_prev, double f_curr, double f_prev)
{
	double sum = 0;
	for (int i = 0; i < x_curr.size(); ++i) {
		sum += ((x_curr[i] - x_prev[i])*(x_curr[i] - x_prev[i]));
	}
	sum = sqrt(sum);
	if (sum < this->eps) {
		this->s = false;
	}
}
