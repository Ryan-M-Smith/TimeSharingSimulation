//
// Filename: cpu.hpp
// Description: The CPU
// Created: 3/4/25
//

#include <chrono>
#include <thread>
#include <vector>

#include "circular_linked_list.hpp"
#include "process.hpp"
#include "types.hpp"

using std::vector;

class CPU {
	public:
		explicit CPU(const vector<Process*>& processes):
			readyQueue(processes),
			currentProcess(readyQueue.getHead())
		{}

		void roundRobin(int quantum);
	private:
		void tick() {
			std::this_thread::sleep_for(std::chrono::seconds(1));
			_tick++;
		}

		unsigned int _tick = 0;
		constexpr static int OVERHEAD_TIME = 2;

		CircularLinkedList<Process*> readyQueue;
		CircularLinkedList<Process*> finishedQueue = {};

		typename decltype(readyQueue)::node_type currentProcess;
};