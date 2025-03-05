//
// Filename: main.cpp
// Description: The main function
// Created: 3/3/25
//

#include <iostream>

#include "cpu.hpp"
#include "io.hpp"
#include "process.hpp"

int main() {
	auto processes = io::readFile("input.txt");
	io::createLog();

	for (const auto& process: processes) {
		std::cout << process->processID << " " << process->burstTime << std::endl;
	}

	CPU cpu(processes);
	cpu.roundRobin(5);

	return 0;
}