//
// Filename: io.hpp
// Description: Handle I/O operations
// Created: 3/3/25
//

#pragma once

#include <ctime>
#include <fstream>
#include <format>
#include <ios>
#include <stdexcept>
#include <string>
#include <vector>

#include "circular_linked_list.hpp"
#include "process.hpp"
#include "types.hpp"

/**
 * @brief Manage I/O operations for the simulation
 */
namespace io {
	static const std::time_t EPOCH = time(nullptr);
	static const std::string LOG_PATH = std::format("logs/audit_log_{}.txt", EPOCH);

	const std::vector<Process*> readFile(const std::string& filename) noexcept(false);
	void createLog() noexcept(false);
	void recordEvent(int tick, const std::string& content) noexcept(false);

	/**
	 * @brief 	Write process statistics to the audit log
	 *
	 * @param 	processes 	The list of processes to log
	 */
	template<typename T>
	void logProcesses(const CircularLinkedList<T>& processes) noexcept(false) {
		const auto HEAD = processes.getHead();
		if (HEAD == nullptr) {
			return;
		}

		std::ofstream file(LOG_PATH, std::ios::app);

		if (!file.is_open()) {
			throw std::runtime_error("Error opening file");
		}


		// Write out statistics for each process
		auto iter = processes.getHead();
		do {
			file << "\nProcess ID: " 				<< iter->data->processID 								<< "\n"
				 << "Arrival Time: " 				<< iter->data->arrivalTime 								<< "\n"
				 << "Burst Time: " 					<< iter->data->burstTime 								<< "\n"
				 << "Waiting Time: " 				<< iter->data->waitingTime 								<< "\n"
				 << "Turnaround Time: " 			<< iter->data->turnAroundTime 							<< "\n"
				 << "Normalized Turnaround Time: " 	<< iter->data->turnAroundTime / iter->data->burstTime 	<< "\n";
		} while ((iter = iter->next) != HEAD);

	}
}