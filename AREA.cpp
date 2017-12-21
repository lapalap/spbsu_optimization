#include "AREA.h"

AREA::AREA(unsigned int dim, std::vector<double> bounds)
{
	this->_dimention = dim;
	for (int i = 0; i < 2*dim; ++i) {
		this->_bounds.push_back(bounds[i]);
	}
}

const bool AREA::is_in_area(const std::vector<double> x)
{
	for (int i = 0; i < this->_dimention; ++i) {
		if ((x[i] < _bounds[2*i])||(x[i] > _bounds[2 * i +1])) return false;
	}
	return true;
}

const unsigned int AREA::get_dim()
{
	return _dimention;
}

const std::vector<double> AREA::get_bounds()
{
	return _bounds;
}
