#pragma once
#include "stdafx.h"
#include "AREA.h"
#include "FUNC.h"
#include "STOP.h"
#include <vector>
#include "RNG.h"
#include <algorithm>
#include <functional>

/*! Base OPTIMISATION class */
class OPTIMISATION {
protected:
	FUNC* _f;																			/**<pointer to a FUNC */
	AREA* _area;																		/**<pointer to a AREA */
	STOP* _stop;																		/**<pointer to a STOP */
	std::vector<double> _curr_pos;														/**<Current position vector */
	std::vector<double> _result;														/**<Optimization result vector */
	double _val;																		/**<FUNC value of optimization result vector */
	unsigned int _iterations = 0;														/**<Number of iterations of algorithm */

public:
	virtual const std::vector<double> optimise(const std::vector<double> start) = 0;	//! Virtual method to argument for min value
	virtual const std::vector<double> get_arg() = 0;									//! Virtual method to get argument after optimization
	virtual const double get_val() = 0;													//! Virtual method to get min value after optimization
	virtual const unsigned int get_iterations() = 0;									//! Virtual method to get number of iterations of algorithm
};


/*! Heir of OPTIMISATION class: Coordinate-wise optimization */

class Coordinate_wise : public OPTIMISATION {
private:
	int N_samples;
	double p, eps;
public:
	Coordinate_wise(FUNC* function, AREA* a, STOP* stop_method, const double N_samples = 100000, const double p = 0.8, const double eps = 0.001);
	const std::vector<double> optimise(const std::vector<double> start);
	const std::vector<double> get_arg();
	const double get_val();
	const unsigned int get_iterations();

};


/*! Heir of OPTIMISATION class: Random_search optimization */

class Random_search : public OPTIMISATION {
private:
	double p = 0;
	double eps;
public:
	Random_search(FUNC* function, AREA* a,  STOP* stop_method, const double p = 0.8, const double eps = 0.0000001);
	const std::vector<double> optimise(const std::vector<double> start);
	const std::vector<double> get_arg();
	const double get_val();
	const unsigned int get_iterations();

};