#ifndef DEBUG_H
#define DEBUG_H

#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

class Timer {
public:
    Timer(const std::string& message = "") : message(message) {
        start_time = std::chrono::high_resolution_clock::now();
    }

    ~Timer() {
        stop();
    }

    void stop() {
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration_micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
        auto duration_milli = std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(end_time - start_time).count();

        std::cout << message << " Duration: " << duration_micro << " microseconds (" << duration_milli << " milliseconds)" << std::endl;
    }

private:
    std::chrono::high_resolution_clock::time_point start_time;
    std::string message; // Member variable to store custom message
};

class Logger {
public:
    enum class LogLevel {
        INFO,
        WARNING,
        ERROR
    };

    static void log(const std::string& message, LogLevel level = LogLevel::INFO) {
        std::string prefix;
        switch (level) {
            case LogLevel::INFO:    prefix = "[INFO] "; break;
            case LogLevel::WARNING: prefix = "[WARNING] "; break;
            case LogLevel::ERROR:   prefix = "[ERROR] "; break;
        }
        std::cout << prefix << message << std::endl;
    }
};

class MemoryTracker {
public:
    static void trackAllocation(void* ptr, size_t size) {
        allocations.push_back({ptr, size});
        std::cout << "Allocated " << size << " bytes at " << ptr << std::endl;
    }

    static void trackDeallocation(void* ptr) {
        auto it = std::remove_if(allocations.begin(), allocations.end(), [ptr](const Allocation& alloc) {
            return alloc.ptr == ptr;
        });
        if (it != allocations.end()) {
            std::cout << "Deallocated " << it->size << " bytes from " << ptr << std::endl;
            allocations.erase(it, allocations.end());
        }
    }

    static size_t getTotalAllocatedMemory() {
    size_t total = 0;
    for (const auto& alloc : allocations) {
        total += alloc.size;
    }
    return total;
    }

private:
    struct Allocation {
        void* ptr;
        size_t size;
    };

    static std::vector<Allocation> allocations;
};

// Define the static member variable
std::vector<MemoryTracker::Allocation> MemoryTracker::allocations;

// Custom new and delete operators
// void* operator new(size_t size) {
//     void* ptr = malloc(size);
//     MemoryTracker::trackAllocation(ptr, size);
//     return ptr;
// }

// void operator delete(void* ptr) noexcept {
//     MemoryTracker::trackDeallocation(ptr);
//     free(ptr);
// }

// void* operator new[](size_t size) {
//     void* ptr = malloc(size);
//     MemoryTracker::trackAllocation(ptr, size);
//     return ptr;
// }

// void operator delete[](void* ptr) noexcept {
//     MemoryTracker::trackDeallocation(ptr);
//     free(ptr);
// }

#endif // DEBUG_H