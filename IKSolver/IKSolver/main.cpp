#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include "main.hpp"
using namespace std;

int main() {
    std::cout << "Adaptive Combat AI: IK Solver" << std::endl;
    std::cout << "Project initialized successfully!" << std::endl;

    // Test cases

	 //   vector<double> testVector1 = { 0, 0, 0 };
	 //   vector<double> testVector2 = { 3, 4, 0 };

	 //   std::cout << "Magnitude of testVector1: " << findMagnitude(testVector1) << std::endl; // Expected: 0
	 //   std::cout << "Magnitude of testVector2: " << findMagnitude(testVector2) << std::endl; // Expected: 5
		//vector<double> subVector = subtractingVectors(testVector2, testVector1);
		//std::cout << "Subtracting testVector1 from testVector2: " << subVector[0] << ", " << subVector[1] << ", " << subVector[2] << std::endl; // Expected: 3, 4, 0
	 //   vector<double> normalized = normalizeVector(testVector2);

	 //   std::cout << "Normalized testVector2: " << normalized[0] << ", " << normalized[1] << ", " << normalized[2] << std::endl;
    
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

	// reachable target
	std::vector<double> target = { 1.0, 1.0, 0.0 };

	std::cout << "\n BEFORE FABRIK";
	testchain1.display();

	

	testchain1.calculateNewPositions(target);
	std::cout << "AFTER FABRIK: \n";
	testchain1.display();

	// calculate endpoint error
	double error = findDistance(testchain1.jointPositions.back(), target);

	std::cout << "\nEndpoint Error" << error << "\n";

	// verify bone lengths were preserved
	for (std::size_t i = 0; i < testchain1.boneLengths.size(); ++i) {
		double length = findDistance(
			testchain1.jointPositions[i],
			testchain1.jointPositions[i + 1]
		);
		std::cout << "Bone" << i
			<< " length: " << length << "\n";
	}

	// FULLY EXTENDED CASE
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

	// reachable target
	std::vector<double> target2 = { 2.0, 0.0, 0.0 };

	std::cout << "\n BEFORE FABRIK";
	testchain2.display();



	testchain2.calculateNewPositions(target2);
	std::cout << "AFTER FABRIK: \n";
	testchain2.display();

	// calculate endpoint error
	double error2 = findDistance(testchain2.jointPositions.back(), target2);

	std::cout << "\nEndpoint Error" << error2 << "\n";

	// verify bone lengths were preserved
	for (std::size_t i = 0; i < testchain2.boneLengths.size(); ++i) {
		double length = findDistance(
			testchain2.jointPositions[i],
			testchain2.jointPositions[i + 1]
		);
		std::cout << "Bone" << i
			<< " length: " << length << "\n";
	}

	// UNREACHABLE CASE
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

	// unreachable target
	std::vector<double> target3 = { 4.0, 0.0, 0.0 };

	std::cout << "\n BEFORE FABRIK";
	testchain3.display();



	testchain3.calculateNewPositions(target3);
	std::cout << "AFTER FABRIK: \n";
	testchain3.display();

	// calculate endpoint error
	double error3 = findDistance(testchain3.jointPositions.back(), target3);

	std::cout << "\nEndpoint Error" << error3 << "\n";

	// verify bone lengths were preserved
	for (std::size_t i = 0; i < testchain3.boneLengths.size(); ++i) {
		double length = findDistance(
			testchain3.jointPositions[i],
			testchain3.jointPositions[i + 1]
		);
		std::cout << "Bone" << i
			<< " length: " << length << "\n";
	}


	// DEGENERATE INPUT
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

	// unreachable target
	std::vector<double> target4 = { 4.0, 0.0, 0.0 };

	std::cout << "\n BEFORE FABRIK";
	testchain4.display();



	testchain4.calculateNewPositions(target4);
	std::cout << "AFTER FABRIK: \n";
	testchain4.display();

	// calculate endpoint error
	double error4 = findDistance(testchain4.jointPositions.back(), target4);

	std::cout << "\nEndpoint Error" << error4 << "\n";

	// verify bone lengths were preserved
	for (std::size_t i = 0; i < testchain4.boneLengths.size(); ++i) {
		double length = findDistance(
			testchain4.jointPositions[i],
			testchain4.jointPositions[i + 1]
		);
		std::cout << "Bone" << i
			<< " length: " << length << "\n";
	}

	return 0;
}

////////////////////////////////// VECTOR MATH //////////////////////////////////


std::vector<double> addingVectors(const std::vector<double>& a, const std::vector<double>& b) {
    if (a.size() != b.size()) {
        throw std::invalid_argument("Vector sizes must match");
    }
    std::vector<double> result;
    for (std::size_t i = 0; i < a.size(); ++i) {
        result.push_back(a[i] + b[i]);
    }
    return result;
}

std::vector<double> subtractingVectors(const std::vector<double>& a, const std::vector<double>& b) {
    std::vector<double> result;
    if (a.size() != b.size()) {
        throw std::invalid_argument("Vector sizes must match");
    }
    for (std::size_t i = 0; i < a.size(); ++i) {
		result.push_back(a[i] - b[i]);
    }
    return result;
}

std::  vector<double> multiplyingByScalar(const std::vector<double>& a, double scalar) {
    vector<double> result;
    for (std::size_t i = 0; i < a.size(); ++i) {
		result.push_back(a[i] * scalar);
    }
    return result;
}

double findMagnitude(const std::vector<double>& a) {
    double sum = 0;
    for (std::size_t i = 0; i < a.size(); ++i) {
		sum += a[i] * a[i];
    }
    // square root of 0 should be 0 so no error thrown here ideally
    return sqrt(sum);
}


vector<double> normalizeVector(const std::vector<double>& a) {
	double magnitude = findMagnitude(a);
    if (magnitude == 0.0) {
        return vector<double>(a.size(), 0.0);
    }

	vector<double> result;
	for (std::size_t i = 0; i < a.size(); ++i) {
		result.push_back(a[i] / magnitude);
	}
	return result;
}

double findDistance(const std::vector<double>& a, const std::vector<double>& b) {
	if (a.size() != b.size()) {
		throw std::invalid_argument("Vector sizes must match");
	}
	
    double total = 0.0;
	for (size_t i = 0; i < a.size(); ++i) {
        double diff = a[i] - b[i];
		total += diff * diff;
	}

	return std::sqrt(total);
}


////////////////////////////////// JOINTCHAIN CLASS FUNCTIONS //////////////////////////////////


jointChain::jointChain(
	int numJoints,
	double totalReach,
	std::vector<double> rootPosition,
	std::vector<vector<double>> jointPositions,
	std::vector<double> boneLengths)
	: numJoints(numJoints),
	totalReach(totalReach),
	rootPosition(rootPosition),
	jointPositions(jointPositions),
	boneLengths(boneLengths)
{
	if (numJoints < 2 ||
		jointPositions.size() != static_cast<std::size_t>(numJoints) ||
		boneLengths.size() != static_cast<std::size_t>(numJoints - 1) ||
		rootPosition.size() != 3) {
		throw std::invalid_argument("Invalid joint chain");
	}
	for (const auto& position : jointPositions) {
		if (position.size() != 3) {
			throw std::invalid_argument("Each joint must have exactly 3 coordinates.");
		}
	}
	double lengthSum = 0.0;

	for (std::size_t i = 0; i < boneLengths.size(); ++i) {
		lengthSum += boneLengths[i];
		if (boneLengths[i] <= 0.0) {
			throw std::invalid_argument("Bone lengths must be positive.");
		}
	}

	if (std::abs(totalReach - lengthSum) > 0.000001) {
		throw std::invalid_argument("Total reach does not match bone lengths");
	}

	if (findDistance(rootPosition, jointPositions[0]) > 0.000001) {
		throw std::invalid_argument("Root position must match first joint");
	}

	for (std::size_t i = 0; i < boneLengths.size(); ++i) {
		double actualLength = findDistance(jointPositions[i], jointPositions[i + 1]);

		if (std::abs(actualLength - boneLengths[i]) > 0.0000001) {
			throw std::invalid_argument("Initial joint positions do not match bone lengths");
		}
	}
}

	// NOW THE METHODS FOR THE CLASS JOINTCHAIN
	void jointChain::updateJointPositions(const std::vector<std::vector<double>>& newPositions) {
		if (newPositions.size() != numJoints) {
			throw std::invalid_argument("New positions size must match number of joints");
		}

		if (newPositions.size() != jointPositions.size()) {
			throw std::invalid_argument("New positions size must match current joint positions size");
		}

		// because this is a class method, jointPositions refers to the vector stored inside the object
		jointPositions = newPositions;
		
	}

	void jointChain::calculateNewPositions(const std::vector<double>& targetPosition, std::string algorithm) {
		// this uses FABRIK algorithm to calculate new joint positions based on the target position
		if (targetPosition.size() != 3) {
			throw std::invalid_argument("Target position must be a 3D vector");
		}

		if (algorithm == "FABRIK") {
			std::vector<std::vector<double>> newPositions = calculateFabrik(targetPosition);
			updateJointPositions(newPositions);
		}
		else {
			throw std::invalid_argument("Unsupported algorithm: " + algorithm);
		}
	}


	std::vector<std::vector<double>> jointChain::calculateFabrik(const std::vector<double>& targetPosition) {

		const double tolerance = 0.001;
		const int max_iterations = 100;
		const double epsilon = 1e-12;


		// copy positions so we don't change original chain until calculation finishes
		auto positions = jointPositions;
		const int n = numJoints;
		double dist_root_target = findDistance(rootPosition, targetPosition);

		// TARGET WITHIN REACH
		if (dist_root_target <= totalReach) {

			for (int iteration = 0; iteration < max_iterations; ++iteration) {

				// FORWARD PASS
				// set end effector to the target
				positions[n - 1] = targetPosition;

				// work backward from end effector
				for (int i = n - 2; i >= 0; --i) {
					std::vector<double> offset = subtractingVectors(positions[i], positions[i + 1]);

					// don't normalize any 0 vectors
					if (findMagnitude(offset) < epsilon) {
						offset = { 1.0, 0.0, 0.0 };
					}

					auto direction = normalizeVector(offset);

					positions[i] = addingVectors(positions[i + 1], multiplyingByScalar(direction, boneLengths[i]));

				} // end forward pass

				// BACKWARDS PASS	
				// restore root to fixed position
				positions[0] = rootPosition;

				// work from start to end effector
				for (int i = 0; i < n - 1; ++i) {
					auto offset = subtractingVectors(positions[i + 1], positions[i]);

					// don't normalize any 0 vectors
					if (findMagnitude(offset) < epsilon) {
						offset = { 1.0, 0.0, 0.0 };
					}

					auto direction = normalizeVector(offset);

					positions[i + 1] = addingVectors(
						positions[i],
						multiplyingByScalar(direction, boneLengths[i])
					);

				} // end backwards pass
					// now check if the wrist reached the target
			
				// now check convergence for every point
				double error = findDistance(positions[n - 1], targetPosition);

				if (error <= tolerance) {
					break;
				}
				}
		}
		else {
			// target is beyond arm's max reach
			for (int i = 0; i < n - 1; ++i) {
				auto direction = normalizeVector(subtractingVectors(targetPosition, positions[i]));
				
				positions[i + 1] = addingVectors(positions[i], multiplyingByScalar(direction, boneLengths[i]));
			}
		}
		return positions;
	}

	void jointChain::display() {
		std::cout << "Displaying joint positions\n";

		for (std::size_t i = 0; i < jointPositions.size(); ++i) {
			const auto& position = jointPositions[i];

			std::cout << "Joint" << i << ": ("
				<< position[0] << ", "
				<< position[1] << ", "
				<< position[2] << ")\n";
		}

	}
