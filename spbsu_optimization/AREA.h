#pragma once
#include "stdafx.h"
#include <vector>
#include <cmath>

/*! Base AREA class */
class AREA {
protected:
	std::vector<double> _bounds; /**< vector of area bounds */
	unsigned int _dimention;
public:
	virtual const std::vector<double> get_bounds() = 0;//! Virtual method to get area bounds
	virtual const unsigned int get_dim(void) = 0; //! Virtual method to get dimention
	virtual const bool is_in_area(const std::vector<double> x) = 0;//! Virtual method to check if vector is in area
};
/*! Heir of AREA class: Rectangle */
class Rectangle : public AREA {
public:
	Rectangle(unsigned int dim, std::vector<double> bounds);//! Rectangle area constructor
	const bool is_in_area( const std::vector<double> x); //! Virtual method to check if vector is in area of rectangle
	const unsigned int get_dim();//! Virtual method to get dimention of rectangle
	const std::vector<double> get_bounds();//! Virtual method to get rectangle bounds
};