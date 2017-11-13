#include "stdafx.h"
#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <sstream>
#include <exception>
#include "AREA.h"
#include "FUNC.h"
#include "OPTIMISATION.h"
#include "STOP.h"

template<typename T>
std::string vec2str(T begin, T end)
{
	std::stringstream ss;
	bool first = true;
	for (; begin != end; begin++)
	{
		if (!first)
			ss << ", ";
		ss << *begin;
		first = false;
	}
	return ss.str();
}
void PrintName() {
	std::cout << " ___  ___  ___  _ _                  _    _         _            _    _           " << std::endl;
	std::cout << "/ __>| . >/ __>| | |      ___  ___ _| |_ <_>._ _ _ <_>.___ ___ _| |_ <_> ___ ._ _ " << std::endl;
	std::cout << "\\__ \\| . \\\\__ \\| ' | ___ / . \\| . \\ | |  | || ' ' || | / /<_> | | |  | |/ . \\| ' |" << std::endl;
	std::cout << "<___/|___/<___/`___'|___|\\___/|  _/ |_|  |_||_|_|_||_|/___<___| |_|  |_|\\___/|_|_|" << std::endl;
	std::cout << "                              | |                                                 " << std::endl;
	std::cout << "                              |_|                                                 " << std::endl;
	std::cout << "                                                                          ver 1.01" << std::endl;
	std::cout << "                                                                      Bykov Kirill" << std::endl;
}

int main() {
	int select = 1;
	double bound[4];
	std::string input;
	FUNC* func;
	AREA* A;
	STOP* stop;
	OPTIMISATION* search;
	PrintName();
	std::cout << "Please select function type number: (int: 1-3)                                    " << std::endl << std::endl;
	std::cout << "	1) Parabollic function" << std::endl;
	std::cout << "	2) Wawy function      " << std::endl;
	std::cout << "	3) Levy function N13  " << std::endl;
	std::cin >> select;
	std::getline(std::cin, input);
	switch (select)
	{
	case 1:
		func = new Ellips();
		break;
	case 2:
		func = new Wavy();
		break;
	case 3:
		func = new LeviN13();
		break;
	default:
		throw std::invalid_argument("Invalid selection");
	}

	std::cout << "Please write boundaries: [(x_l, x_r),(y_l, y_r)]" << std::endl << std::endl;

	std::getline(std::cin, input);
	std::stringstream stream(input);
	for (int i = 0; i < 4; ++i) {
		stream >> bound[i];
	}
	if ((bound[0] > bound[1]) || (bound[2] > bound[3])) {
		throw std::invalid_argument("Invalid selection");
	}
	A = new Rectangle(bound[0], bound[1], bound[2], bound[3]);
	std::cout << "Please stopping criterion: (int: 1-3)                                             " << std::endl << std::endl;
	std::cout << "	1) Iterations" << std::endl;
	std::cout << "	2) ArgNorm   " << std::endl;
	std::cin >> select;
	switch (select)
	{
	case 1:
		int n_iter;
		std::cout << "Please write number of iterations (int: 1-1.000.000)								" << std::endl << std::endl;
		std::cin >> n_iter;
		if ((n_iter < 1) || (n_iter > 1000000)) {
			throw std::invalid_argument("Invalid selection");
		}
		stop = new Iterations(n_iter);
		break;
	case 2:
		double precision;
		std::cout << "Please write precision (double: 1e-16:1e-1)										" << std::endl << std::endl;
		std::cin >> precision;
		if ((precision < 1e-16) || (precision > 1e-1)) {
			throw std::invalid_argument("Invalid selection");
		}
		stop = new ArgNorm(precision);
		break;
	default:
		throw std::invalid_argument("Invalid selection");
	}
	std::cout << "Please select optimization type: (int: 1-2)                                          " << std::endl << std::endl;
	std::cout << "	1) Random search" << std::endl;
	std::cout << "	2) Coordinate-wise (Ternary search)" << std::endl;
	std::cin >> select;
	std::cout << "Please write start point: [x, y]									                   " << std::endl << std::endl;
	double start[2];
	std::getline(std::cin, input);
	stream.str(input);
	for (int i = 0; i < 2; ++i) {
		stream >> start[i];
	}
	if (!A->is_in_area({start[0], start[1]})) {
		throw std::invalid_argument("Invalid selection");
	}
	switch (select)
	{
	case 1:
		search = new Random_search(func, A, stop);
		break;
	case 2:
		search = new Coordinate_wise(func, A, stop);
		break;
	default:
		throw std::invalid_argument("Invalid selection");
	}
	std::cout << "############################## LAUNCHING OPTIMIZATION ##############################" << std::endl << std::endl;
	search->optimise({ start[0], start[1] });
	std::cout << "##############################         RESULT         ##############################" << std::endl << std::endl;
	std::vector<double> args_res = search->get_arg();
	std::cout << "	ARGS: " << vec2str(args_res.begin(), args_res.end()) << std::endl;
	std::cout << "	MIN: " << search->get_val() << std::endl;
	std::cout << "	ITERATIONS: " << search->get_iterations()<<std::endl;

	std::cin.get();
	return 0;
}