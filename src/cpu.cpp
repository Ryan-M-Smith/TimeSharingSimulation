//
// Filename: cpu.cpp
// Description: The CPU
// Created: 3/4/25
//

#include "cpu.hpp"

#include "io.hpp"

void CPU::roundRobin() {
	auto process = currentProcess, next = currentProcess->next;
	bool done = false;

	while (!done) {
		io::recordEvent(tick, std::format("Process {} running", process->data->processID));

		for (int ticks = quantum; process->data->remainingBurstTime > 0 && ticks > 0; ticks--) {
			doTick();
			process->data->remainingBurstTime--;
		}

		if (process->data->remainingBurstTime == 0) {
			io::recordEvent(tick, std::format("Process {} finished", process->data->processID));

			// Update the process statistics
			process->data->turnAroundTime = tick - process->data->arrivalTime;
			process->data->waitingTime = process->data->turnAroundTime - process->data->burstTime;

			// Move the process to the finished queue
			finishedQueue.insertAtEnd(process->data);

			if (process == next) {
				done = true;
			}
			else {
				readyQueue.deleteByValue(process->data);
			}
		}
		else {
			io::recordEvent(tick, std::format("Process {} blocking", process->data->processID));
		}

		io::recordEvent(tick, "Switching context");
		tick += overhead; // Simulate process-switching overhead

		if (!done) {
			process = next;
			next = process->next;
		}
	}

	io::recordEvent(tick, "All processes finished. Shutting down.");
	io::logProcesses(finishedQueue);
}