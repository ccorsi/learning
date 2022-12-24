#ifndef __RESOURCES_H__
#define __RESOURCES_H__

/*
    This is used to include operating system specifics include files that can be used
    to determine the resources that are being used on a given system.
 */
#if defined(__APPLE__) || defined(__MACH__)

#elif defined(__linux__)

    #include "sys/types.h"
    #include "sys/sysinfo.h"

#elif defined(_WIN32)

    #include <windows.h>
    // This include is used to gather information about the current process
    #include <Psapi.h>

#else
    #error "Unale to determine the Operating System Type"
#endif

namespace valhalla {
    namespace util {
        /**
         * @brief The memory class will be used to determine the memory capacity of the
         *          running system.  It can be used to determine if there is enough RAM
         *          available to be able to continue to allocate memory or allow it to
         *          take actions to circumvent the issue.
         * 
         */
        class memory {
            // used to determine which types need to be used to be able to process a system RAM.
#if defined(__APPLE__) || defined(__MACH__)

#elif defined(__linux__)
            struct sysinfo memInfo;
#elif defined(_WIN32)
            MEMORYSTATUSEX memInfo;
#endif
        public:

            /**
             * @brief This enum is used to state what type of memory information that
             *      is requested.
             * 
             *      Currently, we have the following options:
             * 
             *          - TOTAL: total memory available on the system
             *          - SYSTEM: memory currently being used by the system
             *          - PROCESS: memory currently being used by this process
             * 
             */
            enum mem_type {
                SYSTEM,  // Get the current system memory used
                PROCESS, // Get the this process memory used
                TOTAL,   // Get the total memory available on the system
            };

#if defined(__APPLE__) || defined(__MACH__)
            using mem_size_type = int; // TBD
#elif defined(__linux__)
            using mem_size_type = int;
#elif defined(_WIN32)
            using mem_size_type = DWORDLONG;
#endif
            memory();

            /**
             * @brief Determines if the current amount of ram equals or exceeds the passed
             *          limit.
             * 
             * @param limit percentage of ram to compare with
             * @return true If the system is using equal or more ram than limit
             * @return false If the system is using less ram than limit
             */
            bool operator()(const int limit) const; // { return true; }

            /**
             * @brief This method will return the current memory usage of this process.
             * 
             * @return mem_size_type This process current memory usage
             */
            mem_size_type operator()() const { return 0; }

            /**
             * @brief This operator will return the current amount of memory for the 
             *      passed memory type.  Currently, it will return the amount of memory
             *      being used by the system or this process.
             * 
             * @param type The type of memory to return
             * @return mem_size_type The current amount of memory being used by the passed
             *          memory type
             */
            mem_size_type operator()(mem_type type) const;

        private:
            /**
             * @brief Get the process memory usage
             * 
             * @return mem_size_type 
             */
            mem_size_type get_process_memory() const;

            /**
             * @brief Get the system memory usage
             * 
             * @return mem_size_type 
             */
            mem_size_type get_system_memory() const;

            /**
             * @brief Get the total memory available on the system
             * 
             * @return mem_size_type 
             */
            mem_size_type get_total_memory() const;
        
        };
    }
}

#endif
