// Copyright Ashish Kosana [2024]
#include <iostream>
#include <iomanip>  // For std::setprecision
#include <cstdlib>  // For system calls to get memory usage
#include <cstring>
#include "EDistance.hpp"
#include <SFML/System.hpp>

// Function to get current memory usage (in MB)
double getMemoryUsageMB() {
    double memoryUsage = 0.0;
    FILE* file = fopen("/proc/self/status", "r");
    if (file) {
        char line[128];
        while (fgets(line, 128, file) != NULL) {
            if (strncmp(line, "VmRSS:", 6) == 0) {
                memoryUsage = strtod(line + 6, NULL) / 1024.0;  // Convert KB to MB
                break;
            }
        }
        fclose(file);
    }
    return memoryUsage;
}

int main() {
    std::string x, y;
    std::cin >> x >> y;

    double initialMemory = getMemoryUsageMB();

    sf::Clock clock;
    EDistance ed(x, y);
    int distance = ed.optDistance();
    std::cout << "Edit distance = " << distance << std::endl;
    std::cout << ed.alignment();

    // Print memory usage in MB
    double finalMemory = getMemoryUsageMB();
    double memoryUsedMB = finalMemory - initialMemory;
    std::cout << "Memory used: " << std::fixed << std::setprecision(2)
              << memoryUsedMB << " MB" << std::endl;

    // Print edit distance again after the sequence
    std::cout << "Edit distance after sequence = " << distance << std::endl;

    sf::Time elapsed = clock.getElapsedTime();
    std::cout << "Execution time is " << std::fixed << std::setprecision(6)
              << elapsed.asSeconds() << " seconds" << std::endl;
    return 0;
}
