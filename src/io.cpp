//
// Filename: io.cpp
// Description: Handle I/O operations
// Created: 3/3/25
//

#include <ctime>
#include <fstream>
#include <filesystem>
#include <format>
#include <ios>
#include <stdexcept>
#include <string>

#include "io.hpp"

namespace io {
	namespace {
		static const time_t __EPOCH = time(nullptr);
		static const std::string __AUDIT_LOG = std::format("logs/audit_log_{}.txt", __EPOCH);
	}

	/**
	 * @brief Read the simulator's input file and parse burst times
	 * 
	 * @param 	filename 	The input file to read
	 * @return 				A list of created processes
	 */
	const std::vector<Process*> readFile(const std::string& filename) noexcept(false) {
		std::ifstream file(filename); 		// Open the file
		std::vector<Process*> processes; 	// Create a place to store the processes

		if (file.is_open()) {
			std::string line;
			process_id_t pid = 0;

			// Read the burst times from a file
			while (std::getline(file, line)) {
				// Create a process with each burst time
				processes.push_back(new Process(++pid, std::stoi(line)));
				recordEvent(0, std::format("Process {} spawned", pid));
			}

			file.close();
		}
		else {
			throw std::runtime_error("Error opening file");
		}

		return processes;
	}

	/**
	 * @brief Record an event in the audit log
	 * 
	 * @param 	tick 		The tick the event occured at
	 * @param 	content 	The content to record
	 */
	void recordEvent(int tick, const std::string& content) noexcept(false) {
		// If no log directory exists, create it
		std::filesystem::create_directory("logs");
		
		// Open the audit log, or create it if it doesn't exist
		time_t epoch = time(nullptr);
		std::ofstream file(__AUDIT_LOG, std::ios::app);
		
		if (file.is_open()) {
			// Write to the log
			file << "[Tick \t" << tick << "] " << content << "\n";
		}
		else {
			throw std::runtime_error("Error opening file");
		}
		
		file.close();
	}
}