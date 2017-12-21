#pragma once
#include <vector>
#include <math.h>

/*! Base STOP class */
class STOP {
public:
	virtual bool status() = 0;//! Virtual method to get current status
	virtual void update(std::vector<double> x_curr, std::vector<double> x_prev, double f_curr, double f_prev) = 0;//! Virtual method to update data
    virtual void clear()=0;
};

/*! Heir of STOP class: Stop by number of iterarions */
class Iterations : public STOP {
private:
	unsigned int N_iter = 0, N_MAX;
public:
	Iterations(unsigned int MAX);
	bool status();
    void change_MAX(unsigned int newMAX);
	void update(std::vector<double> x_curr, std::vector<double> x_prev, double f_curr, double f_prev);
    void clear();
    int get_N_MAX();
};

/*! Heir of STOP class: Stop by vector norm */
class ArgNorm : public STOP {
private:
	double eps;
	double sum = 1;
    unsigned int N_iter = 0, N_MAX = 100000;
public:
	ArgNorm(double epsilon);
	bool status();
    void change_dist(double newEpsilon);
	void update(std::vector<double> x_curr, std::vector<double> x_prev, double f_curr, double f_prev);
    void clear();
};
