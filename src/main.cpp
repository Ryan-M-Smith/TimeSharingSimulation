//
// Filename: main.cpp
// Description: The main function
// Created: 3/3/25
//

#include <iostream>

#include "io.hpp"
#include "process.hpp"

int main() {
	auto processes = io::readFile("input.txt");

	for (const auto& process: processes) {
		std::cout << process->processID << " " << process->burstTime << std::endl;
	}

	return 0;
}