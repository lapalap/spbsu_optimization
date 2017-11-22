#pragma once
#include <vector>
#include <math.h>

/*! Base STOP class */
class STOP {
public:
	virtual bool status() = 0;//! Virtual method to get current status
	virtual void update(std::vector<double> x_curr, std::vector<double> x_prev, double f_curr, double f_prev) = 0;//! Virtual method to update data
};

/*! Heir of STOP class: Stop by number of iterarions */
class Iterations : public STOP {
	unsigned int N_iter = 0, N_MAX;
public:
	Iterations(unsigned int MAX);
	bool status();

	void update(std::vector<double> x_curr, std::vector<double> x_prev, double f_curr, double f_prev);
};

/*! Heir of STOP class: Stop by vector norm */
class ArgNorm : public STOP {
	double eps;
	double sum;
	unsigned int N_iter = 0, N_MAX = 1000000;
public:
	ArgNorm(double eps);
	bool status();

	void update(std::vector<double> x_curr, std::vector<double> x_prev, double f_curr, double f_prev);
};