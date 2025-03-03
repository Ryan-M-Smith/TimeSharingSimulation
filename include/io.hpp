//
// Filename: io.hpp
// Description: Handle I/O operations
// Created: 3/3/25
//

#pragma once

#include <string>
#include <vector>

#include "process.hpp"
#include "types.hpp"

/**
 * @brief Manage I/O operations for the simulation
 */
namespace io {
	const std::vector<Process*> readFile(const std::string& filename) noexcept(false);
	void recordEvent(int tick, const std::string& content) noexcept(false);
}