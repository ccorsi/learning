#ifndef _VALHALLA_SHARED_MEMORY_H_
#define _VALHALLA_SHARED_MEMORY_H_

#include <string>

namespace valhalla {
    // Initial implementation will seperate the two implementation include a client and server
    // service.

    // This is the base class that will contain that common methods and data that will be 
    // available for the server and client service of the shared memory classes.
    class shared_memory {
    protected:
        #ifdef _WIN32
        const std::string m_name;
        #elif defined(__APPLE__) || defined(__MACH__) 
        const std::string m_name;
        #elif defined(__linux__)
        const std::string m_name;
        #endif
    public:
        shared_memory();
        shared_memory(std::string name, bool is_server = false);

        virtual ~shared_memory();

        virtual void* operator()() = 0;
        virtual char* operator[](size_t idx) = 0;

    };

    class shared_memory_server : public shared_memory {

    public:
        shared_memory_server(std::string name) : shared_memory(name) {
        }

        virtual void *operator()() {
            return nullptr;
        }
    };

    class shared_memory_client : public shared_memory {

    public:
        shared_memory_client(std::string name) : shared_memory(name) {
        }

        virtual void *operator()() {
            return nullptr;
        }
    };
}

#endif
