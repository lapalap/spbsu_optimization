#pragma once
#include <vector>
#include <cmath>

/*! Base AREA class */
class AREA {
protected:
    std::vector<double> _bounds;
	unsigned int _dimention;
public:
    AREA(unsigned int dim, std::vector<double> bounds);
    const std::vector<double> get_bounds();
    const unsigned int get_dim(void);
    const bool is_in_area(const std::vector<double> x);
};
