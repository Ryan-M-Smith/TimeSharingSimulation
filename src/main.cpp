//
// Filename: main.cpp
// Description: The main function
// Created: 3/3/25
//

#include <chrono>
#include <format>
#include <iostream>

#include "cpu.hpp"
#include "io.hpp"
#include "process.hpp"

namespace chrono = std::chrono;

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
	std::cout << "\nRunning simulation..." << std::flush;

	constexpr static unsigned int QUANTUM = 30;
	constexpr static unsigned int OVERHEAD = 2;

	CPU cpu(QUANTUM, OVERHEAD, processes); // Create the CPU

	// Run  and time the simulation
	auto start = chrono::high_resolution_clock::now();
	cpu.roundRobin();
	auto end = chrono::high_resolution_clock::now();

	auto duration = end - start;
	auto minutes = duration_cast<chrono::minutes>(duration).count();
    auto seconds = duration_cast<chrono::seconds>(duration % chrono::minutes(1)).count();

	std::cout << "\n\nSimulation complete in " << cpu.getTickCount() << " ticks "
			  << std::format("({}m {}s).", minutes, seconds)
			  << "\nAudit log saved to " << io::LOG_PATH << ".\n";

	return 0;
}