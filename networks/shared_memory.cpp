/*
This file will contain code that can be used to generate a region of shared memory that can be accessed
acrossed processes on the same host.  The class will be defined to work on a Windows, Linux and MacOS
systems.
*/

/*
We've divided that includes by generalization such that the first ones are related to the standard
includes following by the operating system specifics include and finally ending with the project
implementation specific include files.
*/

// =================== Standard include files ==========================

#include <string>

// =================== Operating System Specific include files ===============

// =================== Project Implementation Specific include files ==========

#include "shared_memory.h"

// =================== Project Implementation ==================

using namespace std;

namespace valhalla {

shared_memory::shared_memory() : m_name("unknown") {
};

shared_memory::shared_memory(string name, bool is_server) : m_name(name) {
};

shared_memory::~shared_memory() {
};

}

