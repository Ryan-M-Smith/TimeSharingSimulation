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
	io::createLog();

	// Read the processes from the input file
	std::cout << "Reading processes from file...";
	auto processes = io::readFile("input.txt");
	std::cout << "Done\n\n";

	// Display the input data to the user
	std::cout << "Processes read:\n";
	for (const auto& process: processes) {
		std::cout << "Process ID: " << process->processID
				  << " | Burst time: " << process->burstTime
				  << "\n";
	}

	std::cout << "\nRunning simulation...\n";

	CPU cpu(processes); // Create the CPU
	cpu.roundRobin(5);	// Run the simulation

	std::cout << "Simulation complete. Audit log saved to " << io::LOG_PATH << ".\n";

	return 0;
}