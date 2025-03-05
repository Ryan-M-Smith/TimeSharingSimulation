//
// Filename: cpu.hpp
// Description: The CPU
// Created: 3/4/25
//

#include <chrono>
#include <thread>
#include <vector>

#include "process.hpp"
#include "circular_linked_list.hpp"

using std::vector;

class CPU {
	public:
		explicit CPU(const vector<Process*>& processes):
			readyQueue(processes),
			currentProcess(readyQueue.getHead())
		{}

		void tick() {
			std::this_thread::sleep_for(std::chrono::seconds(1));
			_tick++;
		}
	
	private:
		unsigned int _tick = 0;
		
		CircularLinkedList<Process*> readyQueue;
		CircularLinkedList<Process*> finishedQueue = {};
		
		typename decltype(readyQueue)::node_type currentProcess;
};