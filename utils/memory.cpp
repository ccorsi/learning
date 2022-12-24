/**
 * @file memory.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief These classes will be used to gather information about the running
 *      process and the system it is running on.  These can be used to allow
 *      the process to make better descisions on what to do next because of
 *      lack of memory and whatnot.
 *
 * @version 0.1
 * @date 2022-09-13
 * 
 * @copyright Copyright (c) 2022 Claudio Corsi
 * 
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "resources.h"

namespace valhalla {
    namespace util {
        memory::memory() {
#if defined(__APPLE__) || defined(__MACH__)

#elif defined(__linux__)
            sysinfo(&memInfo);

            // The following will gather the total virtual memory available on the system
            long long totalVirtualMem = memInfo.totalram;
            // we need to add other values in next statement to avoid int overflow on right hand side...
            totalVirtualMem += memInfo.totalswap;
            totalVirtualMem += memInfo.mem_unit;

            // The following will gather the current total virtual memory used on the system
            long long totalVirtualMemUsed = memInfo.totalram - memInfo.freeram;
            // we need to add other values in next statement to avoid int overflow on right hand side...
            totalVirtualMemUsed += memInfo.totalswap - memInfo.freeswap;
            totalVirtualMemUsed += memInfo.mem_unit;

            // The following will gather the current total virtual memory used by this process

#elif defined(_WIN32)
            /*
                The following code will gather different statistics about the memory usage of the systems and this process.
                This information can be used by different systems to be able to manage heap memory while trying to execute
                actions on data that is being processed.
            */
            memInfo.dwLength = sizeof(MEMORYSTATUSEX);
            GlobalMemoryStatusEx(&memInfo);
            
            // This is the total virtual memory size available that includes the swap file and total RAM
            mem_size_type totalVirtualMem = memInfo.ullTotalPageFile;
            
            // This is the total virtual memory size that is currently being used on the system
            mem_size_type virtualMemUsed = memInfo.ullTotalPageFile - memInfo.ullAvailPageFile;

            // The following set of code will gather information about the memory that is being used by this process
            PROCESS_MEMORY_COUNTERS_EX pmc;
            GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS *)&pmc, sizeof(pmc));
            
            SIZE_T virtualMemoryUsedByMe = pmc.PrivateUsage;
            
            // The following code will gather the total physical memory (RAM) available on the system
            mem_size_type totalPhysMem = memInfo.ullTotalPhys;
            
            // The following code will gather the total physical memory (RAM) used on the system
            mem_size_type physMemUsed =  memInfo.ullTotalPhys - memInfo.ullAvailPhys;
            
            // The following code will gather the total physical memory (RAM) used by this process
            mem_size_type phyMemUsedByMe = pmc.WorkingSetSize;
#endif
        }

        bool memory::operator()(const int limit) const {
            // insure that the limit is always between 0 and 100
            const int rlimit = max(min(100, limit), 0);
            if (limit != rlimit) {
                // Print a error message to the screen for the case that the passed limit is not between 0 and 100.
                std::cerr << "The passed limit: " << limit << " is not between 0 and 100." << std::endl;
                std::cerr << "The limit has been updated to " << rlimit << "." << std::endl;
            }

            mem_size_type total = this->operator()(TOTAL);
            mem_size_type system = this->operator()(SYSTEM);

            system *= 100;
            
            mem_size_type range = system / total; // This will result in a value between 0 and 100.

            // std::cout << "Total = " << total << " System = " << system << " Range = " << range << " Limit = " << limit << std::endl;

            return (range >= limit);
        }

        memory::mem_size_type memory::operator()(mem_type type) const {
            mem_size_type size = 0;

            switch(type) {
                case TOTAL:
                    size = get_total_memory();
                    break;
                case SYSTEM:
                    size = get_system_memory();
                    break;
                case PROCESS:
                    size = get_process_memory();
                    break;
            }

            return size;
        }

        memory::mem_size_type memory::get_total_memory() const {
            mem_size_type totalMemorySize = 0;
#if defined(__APPLE__) || defined(__MACH__)

#elif defined(__linux__)
            sysinfo(&memInfo);

            // The following will gather the total virtual memory available on the system
            long long totalVirtualMem = memInfo.totalram;
            // we need to add other values in next statement to avoid int overflow on right hand side...
            totalVirtualMem += memInfo.totalswap;
            totalVirtualMem += memInfo.mem_unit;

            // The following will gather the current total virtual memory used on the system
            long long totalVirtualMemUsed = memInfo.totalram - memInfo.freeram;
            // we need to add other values in next statement to avoid int overflow on right hand side...
            totalVirtualMemUsed += memInfo.totalswap - memInfo.freeswap;
            totalVirtualMemUsed += memInfo.mem_unit;

            // The following will gather the current total virtual memory used by this process

#elif defined(_WIN32)
            /*
                The following code will gather different statistics about the memory usage of the systems and this process.
                This information can be used by different systems to be able to manage heap memory while trying to execute
                actions on data that is being processed.
            */
            MEMORYSTATUSEX memInfo;
            memInfo.dwLength = sizeof(MEMORYSTATUSEX);
            GlobalMemoryStatusEx(&memInfo);
            
            // The following code will gather the total physical memory (RAM) available on the system
            totalMemorySize = memInfo.ullTotalPhys;
#endif
            return totalMemorySize;
        }

        memory::mem_size_type memory::get_system_memory() const {
            mem_size_type systemMemoryUsed = 0;
#if defined(__APPLE__) || defined(__MACH__)

#elif defined(__linux__)
            sysinfo(&memInfo);

            // The following will gather the total virtual memory available on the system
            long long totalVirtualMem = memInfo.totalram;
            // we need to add other values in next statement to avoid int overflow on right hand side...
            totalVirtualMem += memInfo.totalswap;
            totalVirtualMem += memInfo.mem_unit;

            // The following will gather the current total virtual memory used on the system
            long long totalVirtualMemUsed = memInfo.totalram - memInfo.freeram;
            // we need to add other values in next statement to avoid int overflow on right hand side...
            totalVirtualMemUsed += memInfo.totalswap - memInfo.freeswap;
            totalVirtualMemUsed += memInfo.mem_unit;

            // The following will gather the current total virtual memory used by this process

#elif defined(_WIN32)
            /*
                The following code will gather different statistics about the memory usage of the systems and this process.
                This information can be used by different systems to be able to manage heap memory while trying to execute
                actions on data that is being processed.
            */
            MEMORYSTATUSEX memInfo;
            memInfo.dwLength = sizeof(MEMORYSTATUSEX);
            GlobalMemoryStatusEx(&memInfo);
            
            // The following code will gather the total physical memory (RAM) used on the system
            systemMemoryUsed =  memInfo.ullTotalPhys - memInfo.ullAvailPhys;
#endif

            return systemMemoryUsed;
        }

        memory::mem_size_type memory::get_process_memory() const {
            mem_size_type processMemorySize = 0;
#if defined(__APPLE__) || defined(__MACH__)

#elif defined(__linux__)
            sysinfo(&memInfo);

            // The following will gather the total virtual memory available on the system
            long long totalVirtualMem = memInfo.totalram;
            // we need to add other values in next statement to avoid int overflow on right hand side...
            totalVirtualMem += memInfo.totalswap;
            totalVirtualMem += memInfo.mem_unit;

            // The following will gather the current total virtual memory used on the system
            long long totalVirtualMemUsed = memInfo.totalram - memInfo.freeram;
            // we need to add other values in next statement to avoid int overflow on right hand side...
            totalVirtualMemUsed += memInfo.totalswap - memInfo.freeswap;
            totalVirtualMemUsed += memInfo.mem_unit;

            // The following will gather the current total virtual memory used by this process

#elif defined(_WIN32)
            /*
                The following code will gather different statistics about the memory usage of the systems and this process.
                This information can be used by different systems to be able to manage heap memory while trying to execute
                actions on data that is being processed.
            */
            // The following set of code will gather information about the memory that is being used by this process
            PROCESS_MEMORY_COUNTERS_EX pmc;
            GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS *)&pmc, sizeof(pmc));
            
            // The following code will gather the total physical memory (RAM) used by this process
            processMemorySize = pmc.WorkingSetSize;
#endif
            return processMemorySize;
        }
    }
}