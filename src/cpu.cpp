//
// Filename: cpu.cpp
// Description: The CPU
// Created: 3/4/25
//

#include "cpu.hpp"

#include "io.hpp"

void CPU::roundRobin(int quantum) {
	for (
		auto process = currentProcess, next = currentProcess->next;
		next != nullptr;
		process = next, next = process->next
	) {
		io::recordEvent(_tick, std::format("Process {} running", process->data->processID));

		for (int ticks = quantum; process->data->burstTime > 0 && ticks > 0; ticks--) {
			tick();
			process->data->burstTime--;
		}

		if (process->data->burstTime == 0) {
			io::recordEvent(_tick, std::format("Process {} finished", process->data->processID));

			// Move the process to the finished queue
			finishedQueue.insertAtEnd(process->data);
			readyQueue.deleteByValue(process->data);
		}
		else {
			io::recordEvent(_tick, std::format("Process {} blocking", process->data->processID));
		}

		io::recordEvent(_tick, "Switching context");
		_tick += OVERHEAD_TIME; // Simulate process-switching overhead
	}

	readyQueue.deleteAtFront(); // Make sure the head is fully removed
	
	io::recordEvent(_tick, "All processes finished. Shutting down.");
}