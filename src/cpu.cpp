//
// Filename: cpu.cpp
// Description: The CPU
// Created: 3/4/25
//

#include "cpu.hpp"

#include "io.hpp"

void CPU::roundRobin() {
	Node<Process*> *process, *next;
	bool done = false;

	while (!done) {
		// Change for Project 2: The ready queue only stores processes of the current highest priority
		// If the ready queue is empty, unblock the next highest priorty processes
		if (readyQueue.isEmpty()) {
			auto blockedProcess = blockedQueue.getHead();
			int priority = blockedProcess->data->priority;

			while (blockedProcess != nullptr && blockedProcess->data != nullptr && blockedProcess->data->priority == priority) {
				io::recordEvent(tick, std::format(
					"Unblocking process {} (priority: {})",
					blockedProcess->data->processID,
					blockedProcess->data->priority
				));
				unblockProcess();
				blockedProcess = blockedQueue.getHead();
			}

			process = readyQueue.getHead();
			next = process->next;
		}

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
				readyQueue = {};
			}
			else {
				readyQueue.deleteByValue(process->data);
			}

			if (readyQueue.isEmpty() && blockedQueue.isEmpty()) {
				done = true;
			}
		}
		else {
			io::recordEvent(tick, std::format("Process {} blocking", process->data->processID));
		}

		io::recordEvent(tick, "Switching context");
		tick += overhead; // Simulate process-switching overhead

		if (!readyQueue.isEmpty()) {
			process = next;
			next = process->next;
		}
	}

	io::recordEvent(tick, "All processes finished. Shutting down.");
	io::logProcesses(finishedQueue);
}