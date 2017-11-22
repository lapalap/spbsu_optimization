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
	bool error = false;

	int select = 1;
	std::vector<double> bounds;
	std::string input;

	FUNC* func = NULL;
	AREA* A = NULL;
	STOP* stop = NULL;
	OPTIMISATION* search = NULL;

	PrintName();
	while (true) {
		std::cout << "Please select function type number: (int: 1-3)                                    " << std::endl << std::endl;
		std::cout << "	1) Parabollic function" << std::endl;
		std::cout << "	2) Wawy function      " << std::endl;
		std::cout << "	3) Levy function N13  " << std::endl;
		std::cout << "	4) Simple 3D function  " << std::endl;

		std::cin >> select;
		switch (select)
		{
		case 1:
			func = new Ellips();
			error = false;
			break;
		case 2:
			func = new Wavy();
			error = false;
			break;
		case 3:
			func = new LeviN13();
			error = false;
			break;
		case 4:
			func = new Simple3D();
			error = false;
			break;
		default:
			try
			{
				throw std::invalid_argument("Invalid selection");
			}
			catch (std::exception& e)
			{
				error = true;
				std::cout << e.what() << '\n';
			}
		}
		if (!error) break;
	}
	std::getline(std::cin, input);
	while (true) {
		std::cout << "Number of dimentions: " << func->get_dim() << std::endl;
		std::cout << "Please write boundaries: x1_l, x1_r,...,xn_l,xn_r" << std::endl << std::endl;
		error = false;
		std::getline(std::cin, input);
		std::stringstream stream(input);
		double num;
		while (stream >> num) bounds.push_back(num);
		if (bounds.size() != 2 * func->get_dim()) error = true;
		for (int i = 0; i < func->get_dim(); ++i) {
			if (bounds[2*i] > bounds[2*i+1]) error = true;
		}
		if (error) {
			try
			{
				throw std::invalid_argument("Invalid selection");
			}
			catch (std::exception& e)
			{
				std::cout << e.what() << '\n';
			}
		}
		if (!error) break;
	}

	A = new Rectangle(func->get_dim(), bounds);

	while (true) {
		std::cout << "Please stopping criterion: (int: 1-3)                                             " << std::endl << std::endl;
		std::cout << "	1) Iterations" << std::endl;
		std::cout << "	2) ArgNorm   " << std::endl;
		error = false;
		std::cin >> select;

		try
		{
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
		}
		catch (std::exception& e)
		{
			error = true;
			std::cout << e.what() << '\n';
		}
		if (!error) break;
	};

	std::vector<double> start;
	while (true) {
		std::cout << "Please select optimization type: (int: 1-2)                                          " << std::endl << std::endl;
		std::cout << "	1) Random search" << std::endl;
		std::cout << "	2) Coordinate-wise (Ternary search)" << std::endl;
		error = false;
		std::cin >> select;
		std::cout << "Please write start point:									                   " << std::endl << std::endl;
		std::getline(std::cin, input);
		std::getline(std::cin, input);
		std::stringstream stream(input);
		stream.str(input);
		double num;
		while (stream >> num) start.push_back(num);
		if (start.size() != func->get_dim()) error = true;
		if ((!A->is_in_area(start))||(error)) {
			try
			{
				throw std::invalid_argument("Invalid selection");
			}
			catch (std::exception& e)
			{
				error = true;
				std::cout << e.what() << '\n';
			}
		}
		if (!error) break;
	}
	try
	{
		switch (select)
		{
		case 1:
			search = new Random_search(func, A, stop);
			break;
		case 2:
			search = new Coordinate_wise(func, A, stop);
			break;
		default:
			throw std::invalid_argument("Invalid selection of optimization type");
		}
	}
	catch (std::exception& e)
	{
		error = true;
		std::cout << e.what() << '\n';
	}

	std::cout << "############################## LAUNCHING OPTIMIZATION ##############################" << std::endl << std::endl;
	search->optimise(start);
	std::cout << "##############################         RESULT         ##############################" << std::endl << std::endl;
	std::vector<double> args_res = search->get_arg();
	std::cout << "	ARGS: " << vec2str(args_res.begin(), args_res.end()) << std::endl;
	std::cout << "	MIN: " << search->get_val() << std::endl;
	std::cout << "	ITERATIONS: " << search->get_iterations() << std::endl;

	std::cin.get();
	return 0;
}