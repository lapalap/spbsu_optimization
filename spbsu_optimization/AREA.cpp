#include "stdafx.h"
#include "AREA.h"

Rectangle::Rectangle(double a1, double a2, double b1, double b2)
{
	this->_bounds.push_back(a1);
	this->_bounds.push_back(a2);
	this->_bounds.push_back(b1);
	this->_bounds.push_back(b2);

}

const bool Rectangle::is_in_area(const std::vector<double> x)
{
	if ((this->_bounds[0] < x[0] < this->_bounds[1])&(this->_bounds[2] < x[1] < this->_bounds[3])) {
		return true;
	}
	return false;
}

const unsigned int Rectangle::get_dim()
{
	return 2;
}

const std::vector<double> Rectangle::get_bounds()
{
	return _bounds;
}
