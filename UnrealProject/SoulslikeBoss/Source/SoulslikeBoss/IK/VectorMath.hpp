#pragma once
#include <stdexcept>
#include <string>
#include <vector>
//#include <iostream>

// Function declarations
double findMagnitude(const std::vector<double>& a);

std::vector<double> addingVectors(
	const std::vector<double>& a,
	const std::vector<double>& b
);

std::vector<double> subtractingVectors(
	const std::vector<double>& a,
	const std::vector<double>& b
);

std::vector<double> multiplyingByScalar(
	const std::vector<double>& a,
	double scalar
);

std::vector<double> normalizeVector(
	const std::vector<double>& a
);

double findDistance(
	const std::vector<double>& a,
	const std::vector<double>& b
);



// Class declaration 
class jointChain {
public:
	jointChain(
		int numJoints,
		double totalReach,
		std::vector<double> rootPosition,
		std::vector<std::vector<double>> jointPositions,
		std::vector<double> boneLengths);


	int numJoints;
	double totalReach;
	std::vector<double> rootPosition;
	std::vector<std::vector<double>> jointPositions;
	std::vector<double> boneLengths;
	void display();

	void updateJointPositions(const std::vector<std::vector<double>>& newPositions);

	void calculateNewPositions(const std::vector<double>& targetPosition, std::string algorithm = "FABRIK");

	std::vector<std::vector<double>> calculateFabrik(const std::vector<double>& targetPositions);
};