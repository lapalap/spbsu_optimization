#include "stdafx.h"
#include "OPTIMISATION.h"

Coordinate_wise::Coordinate_wise(FUNC * function,  AREA * a, STOP * stop_method, const  double N_samples, const  double p, const  double eps)
{
	this->_f = function;
	this->_area = a;
	this->_stop = stop_method;
	this->N_samples = N_samples;
	this->p = p;
	this->eps = eps;
}

const std::vector<double> Coordinate_wise::optimise(const std::vector<double> start)
{
	int count_inner = 0;
	double temp;
	std::vector <double> bound = _area->get_bounds();
	std::vector<double> curr_pos = start, argmin = start, prev_pos = start, vect_a , vect_b;
	double left, right, eps_inner;
	eps_inner = eps;
	while (_stop->status()) {
		for (int i = 0; i < start.size(); ++i) {
			prev_pos = argmin;
			curr_pos = argmin;
			left = bound[2 * i];
			right = bound[2 * i + 1];

			while ((right - left) > eps_inner) {
				vect_a = curr_pos;
				vect_a[i] = (left * 2 + right) / 3;
				vect_b = curr_pos;
				vect_b[i] = (left + right * 2) / 3;

				if (_f->val(vect_a) < _f->val(vect_b)) {
					right = vect_b[i];
				}
				else {
					left = vect_a[i];
				}
			}
			argmin[i] = (left + right) / 2.;
			++_iterations;
			}
			_stop->update(argmin, prev_pos, _f->val(argmin), _f->val(prev_pos));
		}
		this->_result = argmin;
		this->_val = _f->val(argmin);
		return argmin;
}

const std::vector<double> Coordinate_wise::get_arg()
{
	return _result;
}

const double Coordinate_wise::get_val()
{
	return _val;
}

const unsigned int Coordinate_wise::get_iterations()
{
	return _iterations;
}

Random_search::Random_search(FUNC * function, AREA * a, STOP * stop_method, const double p, const double eps)
{
	this->_f = function;
	this->_area = a;
	this->_stop = stop_method;
	this->p = p;
	this->eps = eps;

}

const std::vector<double> Random_search::optimise(const std::vector<double> start)
{
	std::vector<double> curr_pos = start, argmin =  start, eps_vec, temp;
	for (int i = 0; i < start.size(); ++i) {
		eps_vec.push_back(-eps);
		eps_vec.push_back(eps);
	}
	while (_stop->status()) {
		double q = GetRandomNumber();
		if (q < p) {
			curr_pos = GetRandomVector(_area->get_bounds());
		}
		else {
			temp = GetRandomVector(eps_vec);
			std::transform(temp.begin(), temp.end(), curr_pos.begin(), temp.begin(), std::plus<double>());
			if (_area->is_in_area(temp)) {
				curr_pos = temp;
			}
		}
		_stop->update(argmin,curr_pos, _f->val(argmin), _f->val(curr_pos));
		++_iterations;
		if (_f->val(argmin) > _f->val(curr_pos)) {
			argmin = curr_pos;
		}
//		printf_s("%lf %lf", curr_pos[0], curr_pos[1]);
	}
	this->_result = argmin;
	this->_val = _f->val(argmin);
	return	argmin;
}

const std::vector<double> Random_search::get_arg()
{
	return _result;
}

const double Random_search::get_val()
{
	return _val;
}

const unsigned int Random_search::get_iterations()
{
	return _iterations;
}