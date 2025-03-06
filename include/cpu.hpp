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
		CPU(unsigned int quantum, unsigned int overhead, const vector<Process*>& processes):
			quantum(quantum),
			overhead(overhead),
			readyQueue(processes),
			currentProcess(readyQueue.getHead())
		{}

		void roundRobin();

		inline unsigned int getTickCount() const {
			return tick;
		}
	private:
		void doTick() {
			std::this_thread::sleep_for(std::chrono::seconds(1));
			tick++;
		}

		unsigned int tick = 0;
		unsigned int quantum;
		unsigned int overhead;

		CircularLinkedList<Process*> readyQueue;
		CircularLinkedList<Process*> finishedQueue;
		Node<Process*>* currentProcess;
};