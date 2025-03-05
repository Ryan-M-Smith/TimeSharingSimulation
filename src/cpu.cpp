//
// Filename: cpu.cpp
// Description: The CPU
// Created: 3/4/25
//

#include "cpu.hpp"

#include "io.hpp"

void CPU::roundRobin(int quantum) {
	auto process = currentProcess, next = currentProcess->next;

	while (process != nullptr && process->data != nullptr) {
		io::recordEvent(_tick, std::format("Process {} running", process->data->processID));

		for (int ticks = quantum; process->data->remainingBurstTime > 0 && ticks > 0; ticks--) {
			tick();
			process->data->remainingBurstTime--;
		}

		if (process->data->remainingBurstTime == 0) {
			io::recordEvent(_tick, std::format("Process {} finished", process->data->processID));

			// Update the process statistics
			process->data->turnAroundTime = _tick - process->data->arrivalTime;
			process->data->waitingTime = process->data->turnAroundTime - process->data->burstTime;

			// Move the process to the finished queue
			finishedQueue.insertAtEnd(process->data);
			readyQueue.deleteByValue(process->data);
		}
		else {
			io::recordEvent(_tick, std::format("Process {} blocking", process->data->processID));
		}

		io::recordEvent(_tick, "Switching context");
		_tick += OVERHEAD_TIME; // Simulate process-switching overhead

		process = next;
		next = process->next;
	}

	io::recordEvent(_tick, "All processes finished. Shutting down.");
	io::logProcesses(finishedQueue);
}