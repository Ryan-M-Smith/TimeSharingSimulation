//
// Filename: job.hpp
// Description: A basic process that can be run on the CPU
// Created: 3/3/25
//

#pragma once

#include "types.hpp"

/**
 * @brief A basic process that can be run on the CPU
 */
struct Process {
	/**
	 * @brief Create a new Process object
	 *
	 * @param 	processID 		The ID of the process
	 * @param 	burstTime 		The required runtime of the process
	 * @param 	arrivalTime 	The time the process arrives on the CPU
	 */
	Process(process_id_t processID, int burstTime, int arrivalTime = 0):
		processID(processID),
		burstTime(burstTime),
		remainingBurstTime(burstTime),
		arrivalTime(arrivalTime)
	{}

	process_id_t 	processID;
	int 			burstTime;
	int 			remainingBurstTime;
	int 			arrivalTime;
	int 			waitingTime;
	int 			turnAroundTime;
};
