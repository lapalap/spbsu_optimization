#define _USE_MATH_DEFINES
#include "FUNC.h"
#include "math.h"

double PI = 3.141592653589793238462643;

Parabolic::Parabolic(double a, double b)
{
	this->a = a;
	this->b = b;
}

const double Parabolic::val(const std::vector<double> x)
{
    return a*x[0] * x[0] + b * x[1] * x[1];
}

const int Parabolic::get_dim(void)
{
	return 2;
}

Wavy::Wavy()
{
}

const double Wavy::val(const std::vector<double> x)
{
    return (x[0]*x[0]+x[1]-11)*(x[0]*x[0]+x[1]-11)+(x[1]*x[1]+x[1]-7)*(x[1]*x[1]+x[1]-7);
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

Simple3D::Simple3D(double a, double b, double c)
{
	this->a = a;
	this->b = b;
	this->c = c;

}

const double Simple3D::val(const std::vector<double> x)
{
	return a*x[0] * x[0] + b * x[1] * x[1] + c*x[2] * x[2];;
}

const int Simple3D::get_dim(void)
{
	return 3;
}
