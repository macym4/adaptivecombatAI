#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include "main.hpp"
#include "VectorMath.hpp"
using namespace std;

int main() {
    std::cout << "Adaptive Combat AI: IK Solver" << std::endl;
    std::cout << "Project initialized successfully!" << std::endl;

	//////////////////////////// FABRIK TEST CASES ////////////////////////////

	// TEST 1: Simple reachable target, 2D
	jointChain testchain1(
		3,
		2.0,
		{ 0.0, 0.0, 0.0 },
		{
			{0.0, 0.0, 0.0},
			{1.0, 0.0, 0.0},
			{2.0, 0.0, 0.0}
		},
		{ 1.0, 1.0 }
	);

	std::vector<double> target1 = { 1.0, 1.0, 0.0 };
	std::vector<double> answer1 = { 1.0, 1.0, 0.0 };


	// TEST 2: Unreachable target, straight extension
	jointChain testchain2(
		3,
		2.0,
		{ 0.0, 0.0, 0.0 },
		{
			{0.0, 0.0, 0.0},
			{1.0, 0.0, 0.0},
			{2.0, 0.0, 0.0}
		},
		{ 1.0, 1.0 }
	);

	std::vector<double> target2 = { 3.0, 0.0, 0.0 };
	std::vector<double> answer2 = { 2.0, 0.0, 0.0 };


	// TEST 3: Vertical target, requires rotation
	jointChain testchain3(
		3,
		2.0,
		{ 0.0, 0.0, 0.0 },
		{
			{0.0, 0.0, 0.0},
			{1.0, 0.0, 0.0},
			{2.0, 0.0, 0.0}
		},
		{ 1.0, 1.0 }
	);

	std::vector<double> target3 = { 0.0, 2.0, 0.0 };
	std::vector<double> answer3 = { 0.0, 2.0, 0.0 };


	// TEST 4: Reachable target in 3D space
	jointChain testchain4(
		3,
		2.0,
		{ 0.0, 0.0, 0.0 },
		{
			{0.0, 0.0, 0.0},
			{1.0, 0.0, 0.0},
			{2.0, 0.0, 0.0}
		},
		{ 1.0, 1.0 }
	);

	std::vector<double> target4 = { 0.5, 0.5, 1.0 };
	std::vector<double> answer4 = { 0.5, 0.5, 1.0 };


	// TEST 5: Unequal bone lengths
	jointChain testchain5(
		3,
		3.0,
		{ 0.0, 0.0, 0.0 },
		{
			{0.0, 0.0, 0.0},
			{2.0, 0.0, 0.0},
			{3.0, 0.0, 0.0}
		},
		{ 2.0, 1.0 }
	);

	std::vector<double> target5 = { 1.0, 2.0, 0.0 };
	std::vector<double> answer5 = { 1.0, 2.0, 0.0 };


	// TEST 6: Four-joint chain, complex 3D target
	jointChain testchain6(
		4,
		3.0,
		{ 0.0, 0.0, 0.0 },
		{
			{0.0, 0.0, 0.0},
			{1.0, 0.0, 0.0},
			{2.0, 0.0, 0.0},
			{3.0, 0.0, 0.0}
		},
		{ 1.0, 1.0, 1.0 }
	);

	std::vector<double> target6 = { 1.0, 1.5, 1.0 };
	std::vector<double> answer6 = { 1.0, 1.5, 1.0 };


	// TEST 7: Five-joint chain, offset root
	jointChain testchain7(
		5,
		4.0,
		{ 2.0, 1.0, 1.0 },
		{
			{2.0, 1.0, 1.0},
			{3.0, 1.0, 1.0},
			{4.0, 1.0, 1.0},
			{5.0, 1.0, 1.0},
			{6.0, 1.0, 1.0}
		},
		{ 1.0, 1.0, 1.0, 1.0 }
	);

	std::vector<double> target7 = { 3.0, 3.0, 2.0 };
	std::vector<double> answer7 = { 3.0, 3.0, 2.0 };


	// TEST 8: Six-joint chain, unequal lengths,
	// offset root, unreachable 3D target
	jointChain testchain8(
		6,
		7.0,
		{ -2.0, 1.0, 3.0 },
		{
			{-2.0, 1.0, 3.0},
			{-0.5, 1.0, 3.0},
			{ 0.5, 1.0, 3.0},
			{ 2.5, 1.0, 3.0},
			{ 3.5, 1.0, 3.0},
			{ 5.0, 1.0, 3.0}
		},
		{ 1.5, 1.0, 2.0, 1.0, 1.5 }
	);

	std::vector<double> target8 = { 4.0, 7.0, 9.0 };

	// Root-to-target distance = sqrt(108) = 10.3923
	// Maximum reach = 7
	// Expected endpoint lies 7 units toward target.
	std::vector<double> answer8 = {
		2.041451884,
		5.041451884,
		7.041451884
	};

	runTestCase(testchain1, target1, answer1);
	runTestCase(testchain2, target2, answer2);
	runTestCase(testchain3, target3, answer3);
	runTestCase(testchain4, target4, answer4);
	runTestCase(testchain5, target5, answer5);
	runTestCase(testchain6, target6, answer6);
	runTestCase(testchain7, target7, answer7);
	runTestCase(testchain8, target8, answer8);


	return 0;
}

////////////////////////////////// TEST CASES //////////////////////////////////

void runTestCase(jointChain chain, const std::vector<double>& target, const std::vector<double>& answer) {
	std::cout << "\n BEFORE FABRIK \n";
	chain.display();

	chain.calculateNewPositions(target);
	std::cout << "AFTER FABRIK: \n";
	chain.display();

	// calculate endpoint error
	double targetError = findDistance(chain.jointPositions.back(), target);
	
	std::cout << "Target Error" << targetError << "\n";

	// verify bone lengths were preserved
	bool bonesValid = true;
	for (std::size_t i = 0; i < chain.boneLengths.size(); ++i) {
		double actualLength = findDistance(
			chain.jointPositions[i],
			chain.jointPositions[i + 1]
		);

		double lengthError = std::abs(
			actualLength - chain.boneLengths[i]
		);

		std::cout << "Bone " << i
			<< " length: " << actualLength
			<< " (error: " << lengthError << ")\n";

		if (lengthError > 0.001) {
			bonesValid = false;
		}
	}
	std::cout << "Correct answer: (" << 
		answer[0] << ", " <<
		answer[1] << " ," <<
		answer[2] << ")\n";

	double expectedError = findDistance(
		chain.jointPositions.back(),
		answer
	);

	std::cout << "Expected Endpoint Error: "
		<< expectedError << "\n";

	// Verify the root has not moved.
	bool rootValid =
		findDistance(chain.jointPositions.front(),
			chain.rootPosition) <= 0.001;

	// Check endpoint accuracy.
	bool endpointValid = expectedError <= 0.001;

	if (endpointValid && bonesValid && rootValid) {
		std::cout << "\nTEST PASSED\n";
	}
	else {
		std::cout << "\nTEST FAILED\n";
	}
	std::cout << "################################## \n";
}
