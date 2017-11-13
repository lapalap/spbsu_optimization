#define _USE_MATH_DEFINES
#include "stdafx.h"
#include "FUNC.h"
#include "math.h"

double PI = 3.141592653589793238462643;

Ellips::Ellips(double a, double b)
{
	this->a = a;
	this->b = b;
}

const double Ellips::val(const std::vector<double> x)
{
	return a*x[0] * x[0] + b * x[1] * x[1];
}

const int Ellips::get_dim(void)
{
	return 2;
}

Wavy::Wavy()
{
}

const double Wavy::val(const std::vector<double> x)
{
	return sin(x[0]) + cos(x[1]);
}

const int Wavy::get_dim(void)
{
	return 2;
}

LeviN13::LeviN13()
{
}

const double LeviN13::val(const std::vector<double> x)
{
	return (sin(3 * PI*x[0])*sin(3 * PI*x[0]) + (x[0] - 1)*(x[0] - 1)*(1 + sin(3 * PI*x[1])*sin(3 * PI*x[1])) + (x[1] - 1)*(x[1] - 1)*(1 + sin(2 * PI*x[1])*sin(2 * PI*x[1])));
}

const int LeviN13::get_dim(void)
{
	return 2;
}
