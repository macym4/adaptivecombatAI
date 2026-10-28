#pragma once
#include <stdexcept>
#include <string>
#include <vector>
#include "VectorMath.hpp"
//#include <iostream>

// Function declarations
void runTestCase(
	jointChain chain, 
	const std::vector<double>& target, 
	const std::vector<double>& answer
);

void visualize();