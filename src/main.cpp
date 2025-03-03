//
// Filename: main.cpp
// Description: The main function
// Created: 3/3/25
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "process.hpp"
#include "types.hpp"

const std::vector<Process*>& readFile(const std::string& filename) {
	std::ifstream file(filename); // Open the file
	std::vector<Process*> processes; // Create a place to store the processes

	if (file.is_open()) {
        std::string line;
		pid_t pid = 0;

		// Read the burst times from a file
        while (std::getline(file, line)) {
			// Create a process with each burst time
			processes.push_back(new Process(++pid, std::stoi(line)));
        }

        file.close();
    }
	else {
        std::cerr << "Error opening file" << std::endl;
        exit(1);
    }

	return processes;
}

int main() {
	auto processes = readFile("input.txt");
	
	return 0;
}