#pragma once
#include <vector>
#include "math.h"
#include "AREA.h"

/*! Base FUNC class */
class FUNC {

protected:
public:
	virtual const double val( const std::vector<double> x) = 0; //! Virtual method to get value
	virtual const int get_dim(void) = 0; //! Virtual method to get dimention
};

/*! Heir of FUNC class: Parabolic function */
class Parabolic : public FUNC {
	double a, b;
public:
    Parabolic(double a = 2, double b = 5);
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

class Simple3D : public FUNC {
	double a, b, c;
public:
	Simple3D(double a = 1, double b = 1, double c = 1);
	const double val(const std::vector<double> x);//! Virtual method to get value
	const int get_dim(void);//! Virtual method to get dimention
};

