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

void Iterations::change_MAX(unsigned int newMAX)
{
    this->N_MAX = newMAX;
    this->N_iter = 0;
}


void Iterations::clear()
{
    this->N_iter = 0;
}

int Iterations::get_N_MAX()
{
    return this->N_MAX;
}

void ArgNorm::clear()
{
    this->N_iter = 0;
    this->sum = 1;
}

void Iterations::update(std::vector<double> x_curr, std::vector<double> x_prev , double f_curr, double f_prev)
{
	++(this->N_iter);
}

ArgNorm::ArgNorm(double epsilon)
{
	this->eps = epsilon;
	this->sum = 1;
}

bool ArgNorm::status()
{
	if ((this->sum < this->eps) || (this->N_iter >= this->N_MAX)) {
		return false;
	}
	return true;
}

void ArgNorm::change_dist(double newEpsilon)
{
    this->eps = newEpsilon;
    this->sum = 1;
    this->N_iter = 0;
}

void ArgNorm::update(std::vector<double> x_curr, std::vector<double> x_prev, double f_curr, double f_prev)
{
	this->sum = 0;
	++(this->N_iter);
	for (int i = 0; i < x_curr.size(); ++i) {
		this->sum += ((x_curr[i] - x_prev[i])*(x_curr[i] - x_prev[i]));
	}
	this->sum = sqrt(this->sum);
}
