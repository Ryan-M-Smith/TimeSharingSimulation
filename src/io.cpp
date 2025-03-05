//
// Filename: io.cpp
// Description: Handle I/O operations
// Created: 3/3/25
//

#include <filesystem>

#include "io.hpp"

using std::string;
using std::vector;

namespace io {
	/**
	 * @brief Read the simulator's input file and parse burst times
	 *
	 * @param 	filename 	The input file to read
	 * @return 				A list of created processes
	 */
	const vector<Process*> readFile(const string& filename) noexcept(false) {
		std::ifstream file(filename); 	// Open the file
		vector<Process*> processes; 	// Create a place to store the processes

		if (!file.is_open()) {
			throw std::runtime_error("Error opening file");
		}

		string line;
		process_id_t pid = 0;

		// Read the burst times from a file
		while (std::getline(file, line)) {
			// Create a process with each burst time
			processes.push_back(new Process(++pid, std::stoi(line)));
			recordEvent(0, std::format("Process {} spawned", pid));
		}

		file.close();

		return processes;
	}

	/**
	 * @brief Create a new audit log
	 */
	void createLog() noexcept(false) {
		// If no log directory exists, create it
		std::filesystem::create_directory("logs");

		// Open the audit log, or create it if it doesn't exist
		std::ofstream file(LOG_PATH);

		if (!file.is_open()) {
			throw std::runtime_error("Error opening file");
		}

		std::time_t now = std::time(nullptr);
		char formatted[50];
		std::strftime(formatted, sizeof(formatted), "%D %T", std::localtime(&now));

		file << "Audit Log - " << formatted << "\n\n";

		file.close();
	}

	/**
	 * @brief Record an event to the audit log
	 *
	 * @param 	tick 		The tick the event occured at
	 * @param 	content 	The content to record
	 */
	void recordEvent(int tick, const string& content) noexcept(false) {
		std::ofstream file(LOG_PATH, std::ios::app);

		if (!file.is_open()) {
			throw std::runtime_error("Error opening file");
		}

		file << "[Tick " << tick << "] " << content << "\n";
		file.close();
	}
}