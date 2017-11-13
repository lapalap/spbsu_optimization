#pragma once
#include "stdafx.h"
#include <vector>
#include "math.h"

/*! Base FUNC class */
class FUNC {
public:
	virtual const double val( const std::vector<double> x) = 0; //! Virtual method to get value
	virtual const int get_dim(void) = 0; //! Virtual method to get dimention
};

/*! Heir of FUNC class: Ellips function */
class Ellips : public FUNC {
	double a, b;
public:
	Ellips(double a = 1, double b = 1);
	const double val(const std::vector<double> x);//! Virtual method to get value
	const int get_dim(void);//! Virtual method to get dimention
};
/*! Heir of FUNC class: Wawy function */
class Wavy : public FUNC {
	double a, b;
public:
	Wavy();

	const double val(const std::vector<double> x);//! Virtual method to get value
	const int get_dim(void);//! Virtual method to get dimention
};

/*! Heir of FUNC class: LeviN13 function */
class LeviN13 : public FUNC {
public:
	LeviN13();
	const double val(const std::vector<double> x);//! Virtual method to get value
	const int get_dim(void);//! Virtual method to get dimention
};


