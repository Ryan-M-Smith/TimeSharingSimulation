//
// Filename: main.cpp
// Description: The main function
// Created: 3/3/25
//

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "process.hpp"
#include "types.hpp"

const std::vector<Process*> readFile(const std::string& filename) noexcept(false) {
	std::ifstream file(filename); // Open the file
	std::vector<Process*> processes; // Create a place to store the processes

	if (file.is_open()) {
        std::string line;
		process_id_t pid = 0;

		// Read the burst times from a file
        while (std::getline(file, line)) {
			// Create a process with each burst time
			processes.push_back(new Process(++pid, std::stoi(line)));
        }

        file.close();
    }
	else {
        std::cerr << "Error opening file" << std::endl;
        throw std::runtime_error("Error opening file");
    }

	return processes;
}

int main() {
	auto processes = readFile("input.txt");

	for (const auto& process: processes) {
		std::cout << process->processID << " " << process->burstTime << std::endl;
	}

	return 0;
}